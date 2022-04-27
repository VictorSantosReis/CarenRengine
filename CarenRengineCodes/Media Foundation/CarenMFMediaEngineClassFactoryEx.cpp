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
#include "CarenMFMediaEngineClassFactoryEx.h"

//Destruidor.
CarenMFMediaEngineClassFactoryEx::~CarenMFMediaEngineClassFactoryEx()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineClassFactoryEx::CarenMFMediaEngineClassFactoryEx()
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
CarenResult CarenMFMediaEngineClassFactoryEx::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineClassFactoryEx*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineClassFactoryEx**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineClassFactoryEx*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineClassFactoryEx**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaEngineClassFactoryEx::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaEngineClassFactoryEx::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineClassFactoryEx::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineClassFactoryEx::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaEngineClassFactoryEx::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineClassFactoryEx();
}



// Métodos da interface proprietária(ICarenMFMediaEngineClassFactoryEx)


/// <summary>
/// Cria um objeto de teclas de mídia com base no sistema de teclas especificado.
/// </summary>
/// <param name="Param_SystemKey">O sistema de chaves de mídia.</param>
/// <param name="Param_CmdStorePath">Uma string que aponta para um local para armazenar dados do Módulo de Descriptografia de Conteúdo (MDL) que podem ser 
/// bloqueados por vários processos e, portanto, podem ser incompatíveis com a suspensão do aplicativo da loja.</param>
/// <param name="Param_Out_MediaKeys">Retorna um ponteiro para a interface de chaves da mídia.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::CreateMediaKeys(
String^ Param_SystemKey,
String^ Param_CmdStorePath,
[Out] ICarenMFMediaKeys^% Param_Out_MediaKeys)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pSystemKey = Nulo;
	BSTR vi_pStorePath = Nulo;
	IMFMediaKeys* vi_pOutMediaKeys = Nulo;

	//Converte as strings gerenciadas para os BSTRs se válidas.
	if (ObjetoGerenciadoValido(Param_SystemKey))
		vi_pSystemKey = Util.ConverterStringToBSTR(Param_SystemKey);
	if (ObjetoGerenciadoValido(Param_CmdStorePath))
		vi_pStorePath = Util.ConverterStringToBSTR(Param_CmdStorePath);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMediaKeys(vi_pSystemKey, vi_pStorePath, &vi_pOutMediaKeys);

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
	Param_Out_MediaKeys = gcnew CarenMFMediaKeys();

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaKeys, Param_Out_MediaKeys, true);

Done:;
	//Libera a memória utilizada pelas Strings BSTRs
	DeletarStringBSTRSafe(&vi_pSystemKey);
	DeletarStringBSTRSafe(&vi_pStorePath);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma instância do ICarenMFMediaSourceExtension.
/// </summary>
/// <param name="Param_Flags">Este parâmetro é reservado e deve ser definido como 0.</param>
/// <param name="Param_Atributos">Os atributos para criação da extensão da fonte de midia.</param>
/// <param name="Param_Out_ExtensaoFonteMidia">Retorna um ponteiro para a interface de extensão da fonte de mídia criada.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::CreateMediaSourceExtension(
UInt32 Param_Flags, 
ICarenMFAttributes^ Param_Atributos, 
[Out] ICarenMFMediaSourceExtension^% Param_Out_ExtensaoFonteMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAtributos = Nulo;
	IMFMediaSourceExtension* vi_pOutSourceExtension = Nulo;

	//Recupera o ponteiro para a interface de atributos se valida.
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pOutSourceExtension);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMediaSourceExtension(static_cast<DWORD>(Param_Flags), vi_pAtributos, &vi_pOutSourceExtension);

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

	//Cria a interface que vai ser retornada.
	Param_Out_ExtensaoFonteMidia = gcnew CarenMFMediaSourceExtension();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutSourceExtension, Param_Out_ExtensaoFonteMidia, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um valor que indica se o sistema de tecla especificado suporta o tipo de mídia especificado.
/// </summary>
/// <param name="Param_MIMEType">O tipo MIME para verificar o suporte.</param>
/// <param name="Param_SystemKey">O sistema-chave para verificar o suporte.</param>
/// <param name="Param_Out_Suporte">Retorna TRUE se o tipo for suportado por (Param_SystemKey); caso contrário, FALSE.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::IsTypeSupported(
String^ Param_MIMEType,
String^ Param_SystemKey,
[Out] Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pMimeType = Nulo;
	BSTR vi_pSystemKey = Nulo;
	BOOL vi_OutSuporte = FALSE;
	
	//Converte as strings gerenciadas para os BSTRs se válidas.
	if (ObjetoGerenciadoValido(Param_MIMEType))
		vi_pMimeType = Util.ConverterStringToBSTR(Param_MIMEType);
	if (ObjetoGerenciadoValido(Param_SystemKey))
		vi_pSystemKey = Util.ConverterStringToBSTR(Param_SystemKey);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsTypeSupported(vi_pMimeType, vi_pSystemKey, &vi_OutSuporte);

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

	//Define o resultado no parametro de saida.
	Param_Out_Suporte = vi_OutSuporte ? true : false;

Done:;
	//Libera a memória utilizada pelas Strings BSTRs
	DeletarStringBSTRSafe(&vi_pMimeType);
	DeletarStringBSTRSafe(&vi_pSystemKey);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenMFMediaEngineClassFactory)


/// <summary>
/// Cria um objeto de erro de mídia.
/// </summary>
/// <param name="Param_Out_MediaError">Retorna uma interface (ICarenMFMediaError) que contém o potneiro para um novo objeto de erro.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::CreateError([Out] ICarenMFMediaError^% Param_Out_MediaError)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaError* vi_pOutMediaError = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateError(&vi_pOutMediaError);

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
	Param_Out_MediaError = gcnew CarenMFMediaError();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaError, Param_Out_MediaError, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância do Media Engine.
/// </summary>
/// <param name="Param_Flags">Um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_CREATEFLAGS.</param>
/// <param name="Param_Atributos">Um ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos. Consulte a estrutura GUIDs_MFAtributes_MediaEngine
/// para os atributos disponiveis para a Media Engine.</param>
/// <param name="Param_Out_MediaEngine">Recebe um ponteiro para a interface ICarenMFMediaEngine. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::CreateInstance(
	CA_MF_MEDIA_ENGINE_CREATEFLAGS Param_Flags,
	ICarenMFAttributes^ Param_Atributos,
	[Out] ICarenMFMediaEngine^% Param_Out_MediaEngine)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAttributes* vi_pAtributos = Nulo;
	IMFMediaEngine* vi_pOutEngine = Nulo;

	//Recupera o ponteiro para a interface de atributos se valida
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAtributos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInstance(static_cast<DWORD>(Param_Flags), vi_pAtributos, &vi_pOutEngine);

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
	Param_Out_MediaEngine = gcnew CarenMFMediaEngine();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutEngine, Param_Out_MediaEngine, true);


Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de intervalo de tempo.
/// </summary>
/// <param name="Param_Out_TimeRange">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineClassFactoryEx::CreateTimeRange([Out] ICarenMFMediaTimeRange^% Param_Out_TimeRange)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaTimeRange* vi_pOutTimeRange = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTimeRange(&vi_pOutTimeRange);

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
	Param_Out_TimeRange = gcnew CarenMFMediaTimeRange();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutTimeRange, Param_Out_TimeRange, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}