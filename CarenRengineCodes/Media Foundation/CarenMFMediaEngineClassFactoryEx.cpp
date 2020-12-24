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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
CarenResult CarenMFMediaEngineClassFactoryEx::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngineClassFactoryEx*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaEngineClassFactoryEx::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngineClassFactoryEx*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngineClassFactoryEx::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineClassFactoryEx::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenMFMediaEngineClassFactoryEx::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
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
/// <param name="Param_Atributos">Um ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos. Consulte a estrutura GUIDs_MFAtributos_MediaEngine
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