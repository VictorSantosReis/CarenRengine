/*
Copyright 2020 Victor Santos Reis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "../pch.h"
#include "CarenStream.h"



//Destruidor.
CarenStream::~CarenStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenStream::CarenStream()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenStream::CarenStream(ICarenMFByteStream^ Param_ByteStream)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	IStream* vi_pOutStream = Nulo;

	//Verfifica se a interface do Stream é valida.
	if (!ObjetoGerenciadoValido(Param_ByteStream))
		throw gcnew NullReferenceException("A interface no parametro (Param_ByteStream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ByteStream, &vi_pByteStream);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");

	//Chama o método para criar a interface.
	Hr = MFCreateStreamOnMFByteStream(vi_pByteStream, &vi_pOutStream);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutStream;
}

CarenStream::CarenStream(ICarenBuffer^ Param_BufferInicial, UInt64 Param_LarguraBuffer)
{
	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferInicial = DefaultGenPointer; //Pode ser NULO | 0
	IStream* vi_pOutStream = Nulo;

	//Verifica se forneceu dados iniciais para a criação do buffer.
	if (ObjetoGerenciadoValido(Param_BufferInicial))
		Param_BufferInicial->ObterPonteiroInterno(vi_pBufferInicial);

	//Chama o método para criar a interface.
	vi_pOutStream = SHCreateMemStream(
		(vi_pBufferInicial != IntPtr::Zero)? const_cast<PBYTE>(Util.ConverterIntPtrTo<PBYTE>(vi_pBufferInicial)): Nulo,
		static_cast<UInt32>(Param_LarguraBuffer));

	//Verifica se não ocorreu erro no processo.
	if (!ObjetoValido(vi_pOutStream))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception("Ocorreu uma falha ao criar o Stream!");
	}

	//Define o tamanho do fluxo
	Prop_SizeStream = Param_LarguraBuffer;

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutStream;
}

CarenStream::CarenStream(MatrizBytes Param_BufferInicial, UInt64 Param_LarguraBuffer)
{
	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	PBYTE vi_pBufferInicial = Nulo; //Pode ser NULO
	IStream* vi_pOutStream = Nulo;

	//Verifica se forneceu dados iniciais para a criação do buffer.
	if (ObjetoGerenciadoValido(Param_BufferInicial))
	{
		//Cria o buffer que vai conter os dados.
		vi_pBufferInicial = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_LarguraBuffer));
		
		//Copia os dados da matriz gerenciada para a nativa.
		Util.CopiarBufferGerenciado_ToNativo(Param_BufferInicial, vi_pBufferInicial, static_cast<UInt32>(Param_LarguraBuffer));
	}

	//Chama o método para criar a interface.
	vi_pOutStream = SHCreateMemStream(vi_pBufferInicial, static_cast<UInt32>(Param_LarguraBuffer));

	//Verifica se não ocorreu erro no processo.
	if (!ObjetoValido(vi_pOutStream))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception("Ocorreu uma falha ao criar o Stream!");
	}

	//Define o tamanho do fluxo
	Prop_SizeStream = Param_LarguraBuffer;

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutStream;

	//Libera a memória para o buffer.
	DeletarMatrizUnidimensionalSafe(&vi_pBufferInicial);
}
CarenStream::CarenStream(const IStream* Param_FluxoNativo, UInt64 Param_LarguraBuffer)
{
	//Verifica se o fluxo é valido.
	if (!ObjetoValido(Param_FluxoNativo))
		throw gcnew NullReferenceException("O parametro (Param_FluxoNativo) não pode ser NULO!");

	//Define o tamanho do fluxo
	Prop_SizeStream = Param_LarguraBuffer;

	//Define a interface fornecida no ponteiro de trabalho.
	PonteiroTrabalho = const_cast<IStream*>(Param_FluxoNativo);
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IStream*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IStream*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenStream::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenStream::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenStream();
}



// Métodos da interface proprietária(ICarenStream)


/// <summary>
/// O método Clone cria um novo objeto de fluxo com seu próprio ponteiro de busca que faz referência aos mesmos bytes do fluxo original.
/// O método Clone cria um novo objeto de fluxo para acessar os mesmos bytes, mas usando um ponteiro de busca separado. O novo objeto de fluxo vê os mesmos dados do 
/// objeto de fluxo de origem. As alterações escritas em um objeto são imediatamente visíveis no outro. O bloqueio de alcance é compartilhado entre os objetos do fluxo.
/// A configuração inicial do ponteiro de busca na instância de fluxo clonado é a mesma da configuração atual do ponteiro de busca no fluxo original no momento da operação do clone.
/// </summary>
/// <param name="Param_Out_CloneInterface">Retorna uma interface (ICarenStream) clonada da interface atual.</param>
CarenResult CarenStream::Clone([Out] ICarenStream^% Param_Out_CloneInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_pOutCloneInterface = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Clone(&vi_pOutCloneInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_CloneInterface = gcnew CarenStream();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(vi_pOutCloneInterface, Param_Out_CloneInterface);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método Commit garante que quaisquer alterações feitas em um objeto de fluxo aberto no modo transacionado sejam refletidas no armazenamento pai. Se o objeto de fluxo
/// estiver aberto no modo direto, o ICarenStream::Commit não tiver outro efeito além de direcionar todos os buffers de memória para o objeto de armazenamento de nível 
/// próximo. A implementação de arquivos compostos COM de fluxos não suporta abertura de fluxos no modo transacionado.
/// Se o fluxo estiver aberto no modo direto, este método garante que quaisquer buffers de memória tenham sido liberados para o objeto de armazenamento subjacente. 
/// Isso é muito parecido com uma descarga nos sistemas de arquivos tradicionais.
/// </summary>
/// <param name="Param_CommitFlags">Controla como as alterações do objeto de fluxo são cometidas. Consulte a enumeração do STGC para obter uma definição desses valores.</param>
CarenResult CarenStream::Commit(CA_STGC Param_CommitFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Commit(static_cast<DWORD>(Param_CommitFlags));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método CopyTo copia um número especificado de bytes do ponteiro de busca atual no fluxo para o ponteiro de busca atual em outro fluxo.
/// O método CopyTo copia os bytes especificados de um fluxo para outro. Ele também pode ser usado para copiar um fluxo para si mesmo. O ponteiro de busca em cada 
/// instância de fluxo é ajustado para o número de bytes lidos ou escritos.
/// </summary>
/// <param name="Param_StreamDestino">Um ponteiro para o fluxo de destino. O fluxo apontado pelo (Param_StreamDestino) pode ser um novo fluxo ou um clone do fluxo de origem.</param>
/// <param name="Param_CountBytesCopy">O número de bytes para copiar a partir do fluxo de origem.</param>
/// <param name="Param_Out_CountBytesReaded">Retorna o número real de bytes lidos a partir do fluxo de origem.</param>
/// <param name="Param_Out_CountBytesWritten">Retorna o número real de bytes escritos para o fluxo de destino.</param>
CarenResult CarenStream::CopyTo(
ICarenStream^ Param_StreamDestino,
UInt64 Param_CountBytesCopy,
[Out] UInt64% Param_Out_CountBytesReaded,
[Out] UInt64% Param_Out_CountBytesWritten)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_pFluxoDestino = Nulo;
	ULARGE_INTEGER vi_CountBytesCopy = {};
	ULARGE_INTEGER vi_OutCountBytesReaded = {};
	ULARGE_INTEGER vi_OutCountBytesWritten = {};

	//Recupera o ponteiro para o fluxo de destino.
	Resultado = RecuperarPonteiroCaren(Param_StreamDestino, &vi_pFluxoDestino);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Define a quantidade de bytes a serem copiados.
	vi_CountBytesCopy.QuadPart = Param_CountBytesCopy;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyTo(vi_pFluxoDestino, vi_CountBytesCopy, &vi_OutCountBytesReaded, &vi_OutCountBytesWritten);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define a quantidade de dados lidos e escritos.
	Param_Out_CountBytesReaded = vi_OutCountBytesReaded.QuadPart;
	Param_Out_CountBytesWritten = vi_OutCountBytesWritten.QuadPart;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método LockRegion restringe o acesso a uma faixa especificada de bytes no fluxo. Suportar essa funcionalidade é opcional, uma vez que alguns sistemas de arquivos 
/// não fornecem. A faixa de byte do fluxo pode ser estendida. Bloquear um intervalo estendido para o fluxo é útil como um método de comunicação entre diferentes instâncias 
/// do fluxo sem alterar dados que realmente fazem parte do fluxo.
/// Qualquer região bloqueada com ICarenStream::LockRegion deve ser desbloqueada explicitamente chamando ICarenStream::UnlockRegion com exatamente os mesmos valores para 
/// os parâmetros Param_Offset, Param_CountBytes e Param_LockType.
/// </summary>
/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
/// <param name="Param_LockType">Especifica as restrições solicitadas ao acessar o intervalo.</param>
CarenResult CarenStream::LockRegion(
UInt64 Param_Offset,
UInt64 Param_CountBytes,
CA_LOCKTYPE Param_LockType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ULARGE_INTEGER vi_Offset = {};
	ULARGE_INTEGER vi_CountBytes = {};

	//Define os dados.
	vi_Offset.QuadPart = Param_Offset;
	vi_CountBytes.QuadPart = Param_CountBytes;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LockRegion(vi_Offset, vi_CountBytes, static_cast<DWORD>(Param_LockType));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método Revert descarta todas as alterações que foram feitas em um fluxo transacionado desde a última chamada ICarenStream::Commit. Em fluxos abertos no modo direto 
/// e streams usando a implementação de arquivo composto COM do ICarenStream::Revert, este método não tem efeito.
/// </summary>
CarenResult CarenStream::Revert()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Revert();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método Seek altera o ponteiro de busca para um novo local. A nova localização é relativa ao início do fluxo, ao fim do fluxo ou ao ponteiro de busca atual.
/// </summary>
/// <param name="Param_Deslocamento">O deslocamento a ser adicionado ao local indicado pelo parâmetro (Param_Origem). Se (Param_Origem) é CA_STREAM_SEEK_SET, isso é 
/// interpretado como um valor não assinado em vez de um valor assinado.</param>
/// <param name="Param_Origem">A origem do deslocamento especificado em (Param_Deslocamento). A origem pode ser o início do arquivo(CA_STREAM_SEEK_SET), o ponteiro de 
/// busca atual(CA_STREAM_SEEK_CUR), ou o final do arquivo(CA_STREAM_SEEK_END).</param>
/// <param name="Param_Out_NovaPosicao">Retorna a nova posição do ponteiro de busca.</param>
CarenResult CarenStream::Seek(
Int64 Param_Deslocamento,
CA_STREAM_SEEK Param_Origem,
[Out] UInt64% Param_Out_NovaPosicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LARGE_INTEGER vi_Deslocamento = { };
	ULARGE_INTEGER vi_OutNovaPosicao = { };

	//Define o dado de deslocamento
	vi_Deslocamento.QuadPart = Param_Deslocamento;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Seek(vi_Deslocamento, static_cast<DWORD>(Param_Origem), &vi_OutNovaPosicao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define a nova posição de busca no parametro de saida.
	Param_Out_NovaPosicao = vi_OutNovaPosicao.QuadPart;

Done:;
	//Retorna o resultado.
	return Resultado;
}


/// <summary>
/// O método SetSize altera o tamanho do objeto de fluxo. O ponteiro de busca não é afetado pela mudança no tamanho do fluxo.
/// Se o parâmetro (Param_NovoTamanho) for menor do que o fluxo atual, o fluxo será truncado ao tamanho indicado. 
/// </summary>
/// <param name="Param_NovoTamanho">Especifica o novo tamanho, em bytes, do fluxo.</param>
CarenResult CarenStream::SetSize(UInt64 Param_NovoTamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ULARGE_INTEGER vi_NovoTamanho = {};

	//Define o novo valor do tamanho do stream.
	vi_NovoTamanho.QuadPart = Param_NovoTamanho;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSize(vi_NovoTamanho);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método Stat recupera a estrutura CA_STATSTG para este fluxo.
/// </summary>
/// <param name="Param_Out_StaticsStream">Retorna uma estrutura STATSTG onde este método coloca informações sobre este objeto de fluxo.</param>
/// <param name="Param_Flags">Especifica que este método não retorna alguns dos membros na estrutura STATSTG, salvando assim uma operação de alocação de memória. 
/// Os valores são retirados da enumeração CA_STATFLAG.</param>
CarenResult CarenStream::Stat(
[Out] CA_STATSTG^% Param_Out_StaticsStream,
CA_STATFLAG Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	STATSTG vi_OutEstatistica = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Stat(&vi_OutEstatistica, static_cast<DWORD>(Param_Flags));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_StaticsStream = Util.ConverterWindows_STATSTGUnManaged_ToManaged(&vi_OutEstatistica);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O método UnlockRegion remove a restrição de acesso em uma série de bytes previamente restritos com ICarenStream::LockRegion.
/// </summary>
/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
/// <param name="Param_LockType">Especifica as restrições de acesso previamente colocadas no intervalo.</param>
CarenResult CarenStream::UnlockRegion(
UInt64 Param_Offset,
UInt64 Param_CountBytes,
CA_LOCKTYPE Param_LockType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ULARGE_INTEGER vi_Offset = {};
	ULARGE_INTEGER vi_CountBytes = {};

	//Define os dados.
	vi_Offset.QuadPart = Param_Offset;
	vi_CountBytes.QuadPart = Param_CountBytes;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnlockRegion(vi_Offset, vi_CountBytes, static_cast<DWORD>(Param_LockType));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenSequentialStream)


/// <summary>
/// Lê um número especificado de bytes do objeto de fluxo para a memória, começando pelo ponteiro de busca atual.
/// Este método lê bytes deste objeto de fluxo para a memória. O objeto de fluxo deve ser aberto no modo STGM_READ. Este método ajusta o ponteiro de busca pelo número real de bytes lidos.
/// </summary>
/// <param name="Param_Out_BufferDest">Uma interface ICarenBuffer que contém o ponteiro de destino dos dados a serem lidos. O usuário é responsável por criar esse buffer.</param>
/// <param name="Param_CountRead">O número de bytes de dados para ler a partir do objeto de fluxo.</param>
/// <param name="Param_Ref_TotalReadBytes">Na saída retorna o valor que representa a quantidade de bytes realmente lidos aparti do fluxo.
/// O número real de bytes lidos pode ser menor do que o número de bytes solicitados se ocorrer um erro ou se o final do fluxo for atingido durante a operação de leitura.</param>
/// <returns></returns>
CarenResult CarenStream::Read(ICarenBuffer^ Param_Out_BufferDest, UInt64 Param_CountRead, UInt64% Param_Ref_TotalReadBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pOutBufferDest = DefaultGenPointer;
	ULONG vi_OutCountReaded = 0;

	//Chama o método para recuperar o buffer de destino.
	Resultado = Param_Out_BufferDest->ObterPonteiroInterno(vi_pOutBufferDest);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		Sair; //Pula para o fim do método.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Read(
		Util.ConverterIntPtrTo<void*>(vi_pOutBufferDest),  //Pointer Buffer.
		static_cast<ULONG>(Param_CountRead),  //Count Read
		&vi_OutCountReaded); //Total Readed.

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define a quantidade total de bytes lidos no parametro de saida.
	Param_Ref_TotalReadBytes = static_cast<UInt64>(vi_OutCountReaded);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Grava um número especificado de bytes no objeto de fluxo começando no ponteiro de busca atual.
/// Write grava os dados especificados em um objeto de fluxo. O ponteiro de busca é ajustado para o número de bytes realmente escritos. O número de bytes realmente escritos é devolvido 
/// no parâmetro (Param_Ref_TotalWrittenBytes). Se a contagem de bytes é zero bytes, a operação de gravação não tem efeito.
/// </summary>
/// <param name="Param_BufferWrite">Uma interface ICarenBuffer que contém um ponteiro para os dados a serem escritos no buffer atual.</param>
/// <param name="Param_CountWrite">O número de bytes de dados para tentar escrever no fluxo. Esse valor pode ser zero.</param>
/// <param name="Param_Ref_TotalWrittenBytes">Na saída retorna o valor que representa a quantiade de bytes realmente escritas no fluxo. O parâmetro pode retornar um valor mesmo se ocorrer um erro.</param>
/// <returns></returns>
CarenResult CarenStream::Write(ICarenBuffer^ Param_BufferWrite, UInt64 Param_CountWrite, UInt64% Param_Ref_TotalWrittenBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferSource = DefaultGenPointer;
	ULONG vi_OutCountWritten = 0;

	//Chama o método para recuperar o buffer de origem.
	Resultado = Param_BufferWrite->ObterPonteiroInterno(vi_pBufferSource);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		Sair; //Pula para o fim do método.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Write(
		const_cast<void*>(Util.ConverterIntPtrTo<void*>(vi_pBufferSource)),
		static_cast<ULONG>(Param_CountWrite),
		&vi_OutCountWritten
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define a quantidade total de dados escritos no fluxo no parametro de saida.
	Param_Ref_TotalWrittenBytes = static_cast<UInt64>(vi_OutCountWritten);

Done:;
	//Retorna o resultado.
	return Resultado;
}