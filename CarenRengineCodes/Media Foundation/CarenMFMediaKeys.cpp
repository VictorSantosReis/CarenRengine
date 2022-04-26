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
#include "CarenMFMediaKeys.h"

//Destruidor.
CarenMFMediaKeys::~CarenMFMediaKeys()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaKeys::CarenMFMediaKeys()
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
CarenResult CarenMFMediaKeys::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaKeys::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaKeys*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaKeys::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaKeys*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaKeys::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaKeys::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaKeys::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaKeys::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaKeys::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaKeys::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaKeys::LiberarReferencia()
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
void CarenMFMediaKeys::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaKeys();
}



// Métodos da interface proprietária(ICarenMFMediaKeys)


/// <summary>
/// Cria um objeto de sessão de chave de mídia usando os dados de inicialização especificados e dados personalizados. .
/// </summary>
/// <param name="Param_MimeType">O tipo MIME do recipiente de mídia usado para o conteúdo.</param>
/// <param name="Param_DadosIniciais">Os dados de inicialização do sistema chave.</param>
/// <param name="Param_CountDadosInicias">A contagem em bytes em Param_DadosIniciais.</param>
/// <param name="Param_DadosPersonalizados">Dados personalizados enviados para o sistema-chave.</param>
/// <param name="Param_CountDadosPersonalizados">A contagem em bytes de Param_DadosPersonalizados.</param>
/// <param name="Param_Notify">Um ponteiro para a interface de notificação.</param>
/// <param name="Param_Out_KeySession">Retorna um ponteiro para a interface de sessão-chave da mídia.</param>
CarenResult CarenMFMediaKeys::CreateSession(
String^ Param_MimeType,
cli::array<Byte>^ Param_DadosIniciais,
UInt32 Param_CountDadosInicias,
cli::array<Byte>^ Param_DadosPersonalizados,
UInt32 Param_CountDadosPersonalizados,
ICarenMFMediaKeySessionNotify^ Param_Notify,
[Out] ICarenMFMediaKeySession^% Param_Out_KeySession)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_MimeType = Nulo;
	PBYTE vi_pDadosIniciais = Nulo;
	DWORD vi_CountDadosIniciais = static_cast<DWORD>(Param_CountDadosInicias);
	PBYTE vi_pDadosPersonalizados = Nulo;
	DWORD vi_CountDadosPersonalizados = static_cast<DWORD>(Param_CountDadosPersonalizados);
	IMFMediaKeySessionNotify* vi_pKeySessionNotify = Nulo;
	IMFMediaKeySession* vi_pOutKeySession = Nulo;

	//Converte a string para o tipo MIME.
	vi_MimeType = Util.ConverterStringToBSTR(Param_MimeType);

	//Aloca memória para as matrizes de bytes.
	vi_pDadosIniciais = CriarMatrizUnidimensional<BYTE>(vi_CountDadosIniciais);
	vi_pDadosPersonalizados = CriarMatrizUnidimensional<BYTE>(vi_CountDadosPersonalizados);

	//Copia os dados das matrizes gerenciadas para suas representações nativas.
	Util.CopiarBufferGerenciado_ToNativo(Param_DadosIniciais, vi_pDadosIniciais, Param_CountDadosInicias);
	Util.CopiarBufferGerenciado_ToNativo(Param_DadosPersonalizados, vi_pDadosPersonalizados, Param_CountDadosPersonalizados);

	//Recupera o ponteiro para a interface de notificação da sessão.
	CarenGetPointerFromICarenSafe(Param_Notify, vi_pKeySessionNotify);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSession
	(
		vi_MimeType,
		vi_pDadosIniciais,
		vi_CountDadosIniciais,
		vi_pDadosPersonalizados,
		vi_CountDadosPersonalizados,
		vi_pKeySessionNotify,
		&vi_pOutKeySession
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

	//Cria a interface a ser retornada.
	Param_Out_KeySession = gcnew CarenMFMediaKeySession();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutKeySession, Param_Out_KeySession, true);

Done:;
	//Libera a memória utlizada pela string BSTR
	DeletarStringBSTRSafe(&vi_MimeType);

	//Libera a memória utilizada pelas matrizes.
	DeletarMatrizUnidimensionalSafe(&vi_pDadosIniciais);
	DeletarMatrizUnidimensionalSafe(&vi_pDadosPersonalizados);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma string de teclas do sistema com qual o objeto ICarenMFMediaKeys foi criado.
/// </summary>
/// <param name="Param_Out_KeySystem">Retorna o nome da string do sistema de chaves.</param>
CarenResult CarenMFMediaKeys::get_KeySystem([Out] String^% Param_Out_KeySystem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutKeySystem = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->get_KeySystem(&vi_pOutKeySystem);

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

	//Cria a string que vai retornar os dados.
	Param_Out_KeySystem = gcnew String(vi_pOutKeySystem);

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringBSTRSafe(&vi_pOutKeySystem);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a interface de notificação de suspensão do Content Decryption Module(CDM).
/// </summary>
/// <param name="Param_Out_Notify">Retorna um ponteiro para a interface de notificação de suspensão do Content Decryption Module(CDM).</param>
CarenResult CarenMFMediaKeys::GetSuspendNotify([Out] ICarenMFCdmSuspendNotify^% Param_Out_Notify)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFCdmSuspendNotify* vi_pOutNotify = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSuspendNotify(&vi_pOutNotify);

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
	Param_Out_Notify = gcnew CarenMFCdmSuspendNotify();

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutNotify, Param_Out_Notify, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// O desligamento deve ser chamado pelo aplicativo antes do lançamento final. A referência do Content Decryption Module(CDM) e quaisquer outros 
/// recursos são liberados neste momento. No entanto, as sessões relacionadas não são liberadas ou fechadas.
/// </summary>
CarenResult CarenMFMediaKeys::Shutdown()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Shutdown();

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