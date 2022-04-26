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
#include "CarenWICStream.h"

//Destruidor.
CarenWICStream::~CarenWICStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICStream::CarenWICStream()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenWICStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICStream*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICStream*>(Param_PonteiroNativo);

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
CarenResult CarenWICStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICStream::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICStream::LiberarReferencia()
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
void CarenWICStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICStream();
}



// Métodos da interface proprietária(ICarenWICStream)


/// <summary>
/// Inicializa um fluxo de um arquivo específico.
/// </summary>
/// <param name="Param_NomeArquivo">O arquivo usado para inicializar o fluxo.</param>
/// <param name="Param_TipoAcesso">O modo de acesso ao arquivo desejado. </param>
CarenResult CarenWICStream::InitializeFromFilename(
String^ Param_NomeArquivo,
CA_ACCESS_RIGHTS Param_TipoAcesso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pUrlArquivo = Nulo;
	DWORD TipoAcesso = static_cast<DWORD>(Param_TipoAcesso);

	//Converte a string para a url nativa.
	vi_pUrlArquivo = Util.ConverterStringToWCHAR(Param_NomeArquivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromFilename(vi_pUrlArquivo, TipoAcesso);

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
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&vi_pUrlArquivo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa um fluxo de outro fluxo. Os direitos de acesso são herdados do fluxo subjacente.
/// </summary>
/// <param name="Param_Fluxo">O fluxo para inicializar este.</param>
CarenResult CarenWICStream::InitializeFromIStream(ICarenStream^ Param_Fluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_pFluxo = Nulo;

	//Recupera o ponteiro para a itnerface do fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &vi_pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromIStream(vi_pFluxo);

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
/// Inicializa o fluxo como um subfluxo de outro fluxo. O fluxo funciona com sua própria posição de fluxo, independente do fluxo subjacente, mas restrito a uma região. Todas as posições 
/// de busca são relativas à sub-região. É permitido, embora não recomendado, ter vários sub streams graváveis ​​sobrepondo o mesmo intervalo.
/// </summary>
/// <param name="Param_Fluxo">O fluxo de entrada.</param>
/// <param name="Param_Offset">O offset do fluxo usado para criar o novo fluxo.</param>
/// <param name="Param_MaxSize">O tamanho máximo do fluxo.</param>
CarenResult CarenWICStream::InitializeFromIStreamRegion(
ICarenStream^ Param_Fluxo,
UInt64 Param_Offset,
UInt64 Param_MaxSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* vi_pFluxo = Nulo;
	ULARGE_INTEGER vi_Offset = {};
	ULARGE_INTEGER vi_MaxSize = {};

	//Recupera o ponteiro para a itnerface do fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &vi_pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Define os valores da regiao a ser inicializada.
	vi_Offset.QuadPart = Param_Offset;
	vi_MaxSize.QuadPart = Param_MaxSize;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromIStreamRegion(vi_pFluxo, vi_Offset, vi_MaxSize);

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
/// Inicializa um fluxo para tratar um bloco de memória como um fluxo. O fluxo não pode crescer além do tamanho do buffer.
/// Este método deve ser evitado sempre que possível. O responsável pela chamada é responsável por garantir que o bloco de memória seja válido por toda a vida do fluxo ao usar InitializeFromMemory. 
/// Uma solução alternativa para esse comportamento é criar um ICarenStream e usar InitializeFromIStream para criar o ICarenWICStream.
/// </summary>
/// <param name="Param_MemoryBuffer">Uma interface(ICarenBuffer) que contém um ponteiro para o bloco de memória que será usado para iniciar o fluxo.</param>
/// <param name="Param_BufferSize">O tamanho do buffer.</param>
CarenResult CarenWICStream::InitializeFromMemory(
ICarenBuffer^ Param_MemoryBuffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer pBufferMemory = DefaultGenPointer;

	//Recupera o ponteiro para o fluxo.
	Resultado = Param_MemoryBuffer->GetInternalPointer(pBufferMemory);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromMemory(Util.ConverterIntPtrTo<PBYTE>(pBufferMemory), static_cast<DWORD>(Param_BufferSize));

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




// Métodos da interface (ICarenStream)


/// <summary>
/// O método Clone cria um novo objeto de fluxo com seu próprio ponteiro de busca que faz referência aos mesmos bytes do fluxo original.
/// O método Clone cria um novo objeto de fluxo para acessar os mesmos bytes, mas usando um ponteiro de busca separado. O novo objeto de fluxo vê os mesmos dados do 
/// objeto de fluxo de origem. As alterações escritas em um objeto são imediatamente visíveis no outro. O bloqueio de alcance é compartilhado entre os objetos do fluxo.
/// A configuração inicial do ponteiro de busca na instância de fluxo clonado é a mesma da configuração atual do ponteiro de busca no fluxo original no momento da operação do clone.
/// </summary>
/// <param name="Param_Out_CloneInterface">Retorna uma interface (ICarenStream) clonada da interface atual.</param>
CarenResult CarenWICStream::Clone([Out] ICarenStream^% Param_Out_CloneInterface)
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
CarenResult CarenWICStream::Commit(CA_STGC Param_CommitFlags)
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
CarenResult CarenWICStream::CopyTo(
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
CarenResult CarenWICStream::LockRegion(
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
CarenResult CarenWICStream::Revert()
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
CarenResult CarenWICStream::Seek(
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
CarenResult CarenWICStream::SetSize(UInt64 Param_NovoTamanho)
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
CarenResult CarenWICStream::Stat(
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
CarenResult CarenWICStream::UnlockRegion(
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
CarenResult CarenWICStream::Read(ICarenBuffer^ Param_Out_BufferDest, UInt64 Param_CountRead, UInt64% Param_Ref_TotalReadBytes)
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
	Resultado = Param_Out_BufferDest->GetInternalPointer(vi_pOutBufferDest);

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
CarenResult CarenWICStream::Write(ICarenBuffer^ Param_BufferWrite, UInt64 Param_CountWrite, UInt64% Param_Ref_TotalWrittenBytes)
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
	Resultado = Param_BufferWrite->GetInternalPointer(vi_pBufferSource);

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