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
#include "CarenMFByteStream.h"


//Destruidor.
CarenMFByteStream::~CarenMFByteStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFByteStream::CarenMFByteStream()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenMFByteStream::CarenMFByteStream(ICarenStream^ Param_Stream)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IStream* vi_pStream = Nulo;
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Verfifica se a interface do Stream é valida.
	if (!ObjetoGerenciadoValido(Param_Stream))
		throw gcnew NullReferenceException("A interface no parametro (Param_Stream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_Stream, &vi_pStream);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");

	//Chama o método para criar a interface.
	Hr = MFCreateMFByteStreamOnStream(vi_pStream, &vi_pOutByteStream);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutByteStream;
}

CarenMFByteStream::CarenMFByteStream(ICarenMFByteStream^ Param_MFStream)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStreamBase = Nulo;
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Verfifica se a interface do fluxo de bytes original é valida.
	if (!ObjetoGerenciadoValido(Param_MFStream))
		throw gcnew NullReferenceException("A interface no parametro (Param_MFStream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_MFStream, &vi_pByteStreamBase);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");

	//Chama o método para criar a interface.
	Hr = MFCreateMFByteStreamWrapper(vi_pByteStreamBase, &vi_pOutByteStream);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutByteStream;
}

CarenMFByteStream::CarenMFByteStream(ICaren^ Param_UnkStream)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IUnknown* vi_pRandomStream = Nulo;
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Verfifica se a interface do fluxo de bytes original é valida.
	if (!ObjetoGerenciadoValido(Param_UnkStream))
		throw gcnew NullReferenceException("A interface no parametro (Param_UnkStream) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_UnkStream, &vi_pRandomStream);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface do fluxo de bytes.");

	//Chama o método para criar a interface.
	Hr = MFCreateMFByteStreamOnStreamEx(vi_pRandomStream, &vi_pOutByteStream);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutByteStream;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFByteStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
	Hr = (reinterpret_cast<IMFByteStream*>(PonteiroTrabalho))->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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
	Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}

	//Retorna o resultado
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFByteStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFByteStream*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFByteStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFByteStream*>(Param_PonteiroNativo);

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
CarenResult CarenMFByteStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFByteStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFByteStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFByteStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFByteStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFByteStream::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<IMFByteStream*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFByteStream::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<IMFByteStream*>(PonteiroTrabalho))->Release();

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
void CarenMFByteStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFByteStream();
}


//
// Métodos da interface proprietária(ICarenMFByteStream)
//

/// <summary>
/// (BeginRead) - Inicia uma operação de leitura assíncrona do fluxo.
/// Quando todos os dados forem lidos no buffer, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
/// ICarenMFByteStream::EndRead para concluir a solicitação assíncrona.
/// </summary>
/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar o buffer.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
CarenResult CarenMFByteStream::BeginRead(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_TamanhoBuffer,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PBYTE pBufferDestino = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;
	ULONG LarguraBuffer = static_cast<ULONG>(Param_TamanhoBuffer);
	IMFAsyncCallback* pCallback = NULL;
	IUnknown* pObjetoEstado = NULL;

	//Recupera o ponteiro para o buffer que vai conter os dados lidos.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer é invalido

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pBufferDestino = (PBYTE)PonteiroDados.ToPointer();

	//Recupera o ponteiro para a interface de retorno de chamada
	Resultado = Param_Callback->RecuperarPonteiro((LPVOID*)&pCallback);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Verifcia se forneceu um objeto de estado(OPICIONAL)
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
	{
		//Recupera o ponteiro para o objeto.
		Resultado = Param_ObjetoEstado->RecuperarPonteiro((LPVOID*)&pObjetoEstado);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//O ponteiro para o objeto de estado é invalido.

			//Sai do método
			goto Done;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginRead(pBufferDestino, LarguraBuffer, pCallback, pObjetoEstado);

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
/// (BeginWrite) - Inicia uma operação de gravação assíncrona no fluxo.
/// Quando todos os dados foram gravados no fluxo, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
/// ICarenMFByteStream::EndWrite para concluir a solicitação assíncrona.
/// </summary>
/// <param name="Param_Buffer">Um ponteiro para o buffer a ser escrito no fluxo.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
CarenResult CarenMFByteStream::BeginWrite(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_TamanhoBuffer,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PBYTE pBufferOrigem = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;
	ULONG LarguraBuffer = static_cast<ULONG>(Param_TamanhoBuffer);
	IMFAsyncCallback* pCallback = NULL;
	IUnknown* pObjetoEstado = NULL;

	//Recupera o ponteiro para o buffer que contem os dados a serem escritos.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer é invalido

		//Sai do método
		goto Done;
	}

	pBufferOrigem = (PBYTE)PonteiroDados.ToPointer();

	//Recupera o ponteiro para a interface de retorno de chamada
	Resultado = Param_Callback->RecuperarPonteiro((LPVOID*)&pCallback);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Verifcia se forneceu um objeto de estado(OPICIONAL)
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
	{
		//Recupera o ponteiro para o objeto.
		Resultado = Param_ObjetoEstado->RecuperarPonteiro((LPVOID*)&pObjetoEstado);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//O ponteiro para o objeto de estado é invalido.

			//Sai do método
			goto Done;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginWrite(pBufferOrigem, LarguraBuffer, pCallback, pObjetoEstado);

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
/// (Close) - Fecha o fluxo e libera todos os recursos associados ao fluxo, como soquetes ou identificadores de arquivo. Esse método também cancela todas as solicitações
/// de E / S assíncronas pendentes.
/// </summary>
CarenResult CarenMFByteStream::Close()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Close();

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
/// (EndRead) - Conclui uma operação de leitura assíncrona.
/// </summary>
/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
/// ICarenMFAsyncCallback::Invoke.</param>
/// <param name="Param_Out_TotalLido">Recebe o total de bytes que foi lido do fluxo.</param>
CarenResult CarenMFByteStream::EndRead(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalLido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* pResultado = NULL;
	ULONG TotalLido = 0;

	//Recupera o ponteiro para a interface de resultado do método assicnrono.
	Resultado = Param_Resultado->RecuperarPonteiro((LPVOID*)&pResultado);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndRead(pResultado, &TotalLido);

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

	//Define o total lido no parametro de saida.
	Param_Out_TotalLido = static_cast<UInt64>(TotalLido);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (EndWrite) - Conclui uma operação de gravação assíncrona.
/// </summary>
/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
/// ICarenMFAsyncCallback::Invoke.</param>
/// <param name="Param_Out_TotalEscrito">Recebe o número de bytes que foram escritos.</param>
CarenResult CarenMFByteStream::EndWrite(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalEscrito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* pResultado = NULL;
	ULONG TotalEscrito = 0;

	//Recupera o ponteiro para a interface de resultado do método assicnrono.
	Resultado = Param_Resultado->RecuperarPonteiro((LPVOID*)&pResultado);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndWrite(pResultado, &TotalEscrito);

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

	//Define o total lido no parametro de saida.
	Param_Out_TotalEscrito = static_cast<UInt64>(TotalEscrito);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Flush) - Limpa todos os buffers internos usados pelo fluxo. Se você estiver gravando no fluxo, os dados em buffer serão gravados no arquivo ou dispositivo subjacente.
/// </summary>
CarenResult CarenMFByteStream::Flush()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Flush();

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
/// (GetCapabilities) - Recupera as características do fluxo de bytes.
/// </summary>
/// <param name="Param_Out_CaracteristicasFluxo">Retorna uma ou mais bandeiras da enumeração (CA_MFBYTESTREAM_CHARACTERISTICS) que definem as caracteristicas do fluxo de bytes.</param>
CarenResult CarenMFByteStream::GetCapabilities([Out] CA_MFBYTESTREAM_CHARACTERISTICS% Param_Out_CaracteristicasFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD CaracteristicasFluxo = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCapabilities(&CaracteristicasFluxo);

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

	//Define as caracteristicas no parametro de saida.
	Param_Out_CaracteristicasFluxo = static_cast<CA_MFBYTESTREAM_CHARACTERISTICS>(CaracteristicasFluxo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCurrentPosition) - Recupera a posição atual de leitura ou gravação no fluxo.
/// </summary>
/// <param name="Param_Out_Posicao">Retorna a posição atual, em bytes.</param>
CarenResult CarenMFByteStream::GetCurrentPosition([Out] UInt64% Param_Out_Posicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	QWORD CurrentPosition = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentPosition(&CurrentPosition);

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

	//Converte de define a posição atual no parametro de saida.
	Param_Out_Posicao = static_cast<UInt64>(CurrentPosition);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetLength) - Recupera o comprimento do fluxo.
/// </summary>
/// <param name="Param_Out_Largura">Recebe o comprimento do fluxo, em bytes. Se o comprimento for desconhecido, este valor é -1.</param>
CarenResult CarenMFByteStream::GetLength([Out] UInt64% Param_Out_Largura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	QWORD LarguraFluxo = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetLength(&LarguraFluxo);

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

	//Converte e define o valor da largura do fluxo no parametro de saida.
	Param_Out_Largura = static_cast<UInt64>(LarguraFluxo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsEndOfStream) - Consulta se a posição atual atingiu o final do fluxo.
/// </summary>
/// <param name="Param_Out_FinalFluxo">Retorna o valor TRUE se a posiçao atual for o final do fluxo, caso contrário FALSE.</param>
CarenResult CarenMFByteStream::IsEndOfStream([Out] Boolean% Param_Out_FinalFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL ResultadoEndFluxo = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsEndOfStream(&ResultadoEndFluxo);

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

	//Converte e define o resultado da verificação do final do fluxo.
	Param_Out_FinalFluxo = static_cast<Boolean>(ResultadoEndFluxo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Read) - Lê dados do fluxo.
/// </summary>
/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar esse buffer.</param>
/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
/// <param name="Param_Out_TotalLido">Recebe o número de bytes lidos no buffer.</param>
CarenResult CarenMFByteStream::Read(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_Tamanho,
				[Out] UInt64% Param_Out_TotalLido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PBYTE pBufferDestino = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;
	ULONG LarguraBuffer = static_cast<ULONG>(Param_Tamanho);
	ULONG OutTotalLido = 0;

	//Recupera o ponteiro para o buffer que vai conter os dados a serem lidos.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer é invalido

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pBufferDestino = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Read(pBufferDestino, LarguraBuffer, &OutTotalLido);

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

	//Define o total que foi lido do fluxo no parametro de saida.
	Param_Out_TotalLido = static_cast<UInt64>(OutTotalLido);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Seek) - Move a posição atual no fluxo por um deslocamento especificado.
/// </summary>
/// <param name="Param_Origem">Especifica a origem da busca como membro da enumeração CA_MFBYTESTREAM_SEEK_ORIGIN. O deslocamento é calculado em relação a esta posição.</param>
/// <param name="Param_Offset">Especifica a nova posição, como um byte offset da origem da busca.</param>
/// <param name="Param_Flags">Especifica zero ou mais bandeiras da enumeração CA_MFBYTESTREAM_SEEK_FLAGS.</param>
/// <param name="Param_Out_NovaPosicao">Recebe a nova posição após a busca.</param>
CarenResult CarenMFByteStream::Seek(
				CA_MFBYTESTREAM_SEEK_ORIGIN Param_Origem,
				Int64 Param_Offset,
				CA_MFBYTESTREAM_SEEK_FLAGS Param_Flags,
				[Out] UInt64% Param_Out_NovaPosicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MFBYTESTREAM_SEEK_ORIGIN SeekOrigin = static_cast<MFBYTESTREAM_SEEK_ORIGIN>(Param_Origem);
	DWORD Flags = static_cast<DWORD>(Param_Flags);
	QWORD OutCurrentPosition = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Seek(SeekOrigin, Param_Offset, Flags, &OutCurrentPosition);

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

	//Define a nova posição do fluxo no parametro de saida.
	Param_Out_NovaPosicao = static_cast<UInt64>(OutCurrentPosition);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetCurrentPosition) - Define a posição atual de leitura ou gravação.
/// </summary>
/// <param name="Param_Posicao">Nova posição no fluxo, como um byte offset desde o início do fluxo.</param>
CarenResult CarenMFByteStream::SetCurrentPosition(UInt64 Param_Posicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentPosition(static_cast<QWORD>(Param_Posicao));

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
/// (SetLength) - Define o comprimento do fluxo.
/// </summary>
/// <param name="Param_LarguraFluxo">A largura do fluxo em bytes.</param>
CarenResult CarenMFByteStream::SetLength(UInt64 Param_LarguraFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetLength(static_cast<QWORD>(Param_LarguraFluxo));

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
/// (Write) - Grava dados no fluxo.
/// </summary>
/// <param name="Param_Buffer">Um ponteiro para o buffer que contém os dados a serem escritos.</param>
/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
/// <param name="Param_Out_TotalEscrito">Recebe o numero de bytes que foram escritos no buffer.</param>
CarenResult CarenMFByteStream::Write(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_Tamanho,
				[Out] UInt64% Param_Out_TotalEscrito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PBYTE pBufferOrigem = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;
	ULONG LarguraBuffer = static_cast<ULONG>(Param_Tamanho);
	ULONG OutTotalEscrito = 0;

	//Recupera o ponteiro para o buffer que vai conter os dados a serem lidos.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer é invalido

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pBufferOrigem = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Write(pBufferOrigem, LarguraBuffer, &OutTotalEscrito);

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

	//Define o total escrito no parametro de saida.
	Param_Out_TotalEscrito = static_cast<UInt64>(OutTotalEscrito);

Done:;
	//Retorna o resultado.
	return Resultado;
}