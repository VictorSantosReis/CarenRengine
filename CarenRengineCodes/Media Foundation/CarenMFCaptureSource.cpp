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
#include "CarenMFCaptureSource.h"

//Destruidor.
CarenMFCaptureSource::~CarenMFCaptureSource()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFCaptureSource::CarenMFCaptureSource()
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
CarenResult CarenMFCaptureSource::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFCaptureSource::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFCaptureSource*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFCaptureSource::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFCaptureSource*>(Param_PonteiroNativo);

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
CarenResult CarenMFCaptureSource::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFCaptureSource::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFCaptureSource::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFCaptureSource::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFCaptureSource::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFCaptureSource::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFCaptureSource::LiberarReferencia()
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
void CarenMFCaptureSource::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFCaptureSource();
}



// Métodos da interface proprietária(ICarenMFCaptureSource)


/// <summary>
/// Adiciona um efeito a um fluxo de captura.
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_Efeito">Uma interface que contém o ponteiro para o efeito. Essa interface pode ser uma ICarenMFTransform ou ICarenActivate.</param>
CarenResult CarenMFCaptureSource::AddEffect(
UInt32 Param_SourceStreamIndex,
ICaren^ Param_Efeito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pEfeito = Nulo;

	//Recupera o ponteiro para a interface do efeito.
	CarenGetPointerFromICarenSafe(Param_Efeito, vi_pEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddEffect(static_cast<DWORD>(Param_SourceStreamIndex), vi_pEfeito);

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
/// Obtém um formato que é suportado por um dos fluxos de captura.
/// Para enumerar todos os formatos disponíveis em um fluxo, chame este método em um loop enquanto incrementa o (Param_MediaTypeIndex), até que o método retorne ER_MF_E_NO_MORE_TYPES.
/// Algumas câmeras podem suportar uma série de taxas de quadros. As taxas mínimas e máximas de quadros são armazenadas nos atributos MF_MT_FRAME_RATE_RANGE_MIN e MF_MT_FRAME_RATE_RANGE_MAX no tipo de mídia.
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_MediaTypeIndex">O índice baseado em zero do tipo de mídia para recuperar.</param>
/// <param name="Param_Out_MediaType">Recebe um ponteiro para a interface IMFMediaType. O chamador deve liberar a interface.</param>
CarenResult CarenMFCaptureSource::GetAvailableDeviceMediaType(
UInt32 Param_SourceStreamIndex,
UInt32 Param_MediaTypeIndex,
[Out] ICarenMFMediaType^% Param_Out_MediaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAvailableDeviceMediaType(static_cast<DWORD>(Param_SourceStreamIndex), static_cast<DWORD>(Param_MediaTypeIndex), &vi_pOutMediaType);

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
	Param_Out_MediaType = gcnew CarenMFMediaType(false);

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_MediaType, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o ponteiro para a interface ICarenMFActivate do dispositivo de captura atual.
/// </summary>
/// <param name="Param_CaptureDeviceType">O tipo de dispositivo do motor de captura.</param>
/// <param name="Param_Out_Activate">Recebe a interface ICarenMFActivate que representa o dispositivo.</param>
CarenResult CarenMFCaptureSource::GetCaptureDeviceActivate(
CA_MF_CAPTURE_ENGINE_DEVICE_TYPE Param_CaptureDeviceType,
[Out] ICarenMFActivate^% Param_Out_Activate)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFActivate* vi_pOutActivate = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCaptureDeviceActivate(static_cast<MF_CAPTURE_ENGINE_DEVICE_TYPE>(Param_CaptureDeviceType), &vi_pOutActivate);

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
	Param_Out_Activate = gcnew CarenMFActivate();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutActivate, Param_Out_Activate, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o ponteiro para a interface ICarenMFMediaSource do dispositivo de captura atual
/// </summary>
/// <param name="Param_CaptureDeviceType">O tipo de dispositivo do motor de captura.</param>
/// <param name="Param_Out_MediaSource">Recebe a interface ICarenMFMediaSource que representa o dispositivo.</param>
CarenResult CarenMFCaptureSource::GetCaptureDeviceSource(
CA_MF_CAPTURE_ENGINE_DEVICE_TYPE Param_CaptureDeviceType,
[Out] ICarenMFMediaSource^% Param_Out_MediaSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaSource* vi_pOutMediaSource = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCaptureDeviceSource(static_cast<MF_CAPTURE_ENGINE_DEVICE_TYPE>(Param_CaptureDeviceType), &vi_pOutMediaSource);

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
	Param_Out_MediaSource = gcnew CarenMFMediaSource();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaSource, Param_Out_MediaSource, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tipo de mídia atual para um fluxo de captura. 
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_Out_MediaType">Recebe a interface ICarenMFMediaType. O chamador deve liberar a interface.</param>
CarenResult CarenMFCaptureSource::GetCurrentDeviceMediaType(
UInt32 Param_SourceStreamIndex,
[Out] ICarenMFMediaType^% Param_Out_MediaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentDeviceMediaType(static_cast<DWORD>(Param_SourceStreamIndex), &vi_pOutMediaType);

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
	Param_Out_MediaType = gcnew CarenMFMediaType(false);

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_MediaType, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a categoria de fluxo para o índice de fluxo de origem especificado. 
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_Out_StreamCategory">Recebe um valor da enumeração (CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY) do fluxo de origem especificado.</param>
CarenResult CarenMFCaptureSource::GetDeviceStreamCategory(
UInt32 Param_SourceStreamIndex,
[Out] CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY% Param_Out_StreamCategory)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MF_CAPTURE_ENGINE_STREAM_CATEGORY vi_OutCategory = MF_CAPTURE_ENGINE_STREAM_CATEGORY::MF_CAPTURE_ENGINE_STREAM_CATEGORY_UNSUPPORTED;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceStreamCategory(static_cast<DWORD>(Param_SourceStreamIndex), &vi_OutCategory);

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

	//Converte e define no parametro de saida o resultado.
	Param_Out_StreamCategory = static_cast<CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY>(vi_OutCategory);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de fluxos de dispositivos. 
/// </summary>
/// <param name="Param_Out_StreamCount">Recebe o número de fluxos de dispositivos.</param>
CarenResult CarenMFCaptureSource::GetDeviceStreamCount([Out] UInt32% Param_Out_StreamCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutStreamCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceStreamCount(&vi_OutStreamCount);

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
	Param_Out_StreamCount = static_cast<UInt32>(vi_OutStreamCount);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o estado de espelhamento atual da transmissão de visualização de vídeo. 
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo.</param>
/// <param name="Param_Out_MirrorState">Recebe o valor TRUE se o espelhamento estiver ativado ou FALSE se o espelhamento for desativado.</param>
CarenResult CarenMFCaptureSource::GetMirrorState(
UInt32 Param_StreamIndex,
[Out] Boolean% Param_Out_MirrorState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutStateMirror = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMirrorState(static_cast<DWORD>(Param_StreamIndex), &vi_OutStateMirror);

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

	//Converte e define o resultado no parametro de saida.
	Param_Out_MirrorState = vi_OutStateMirror ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um ponteiro para o objeto Source Reader(ICarenMFSourceReader) subjacente. 
/// </summary>
/// <param name="Param_GuidServico">Um identificador de serviço GUID. Atualmente, o valor deve ser IID_IMFSourceReader ou Nulo.</param>
/// <param name="Param_RIIDInterface">O identificador de interface (IID) da interface que está sendo solicitada. O valor deve ser IID_IMFSourceReader. Se o valor não estiver definido para IID_IMFSourceReader,a chamada falhará e retornará ER_E_INVALIDARG.</param>
/// <param name="Param_Ref_Interface">Recebe um ponteiro para a interface solicitada. O usuário é responsável por inicializar a interface.</param>
CarenResult CarenMFCaptureSource::GetService(
String^ Param_GuidServico,
String^ Param_RIID,
ICaren^% Param_Ref_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidService = GUID_NULL; //Pode ser Nulo.
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pOutInterface = Nulo;

	//Cria o guid de serviço se for valido.
	if (StringObjetoValido(Param_GuidServico))
		vi_GuidService = Util.CreateGuidFromString(Param_GuidServico);

	//Cria o RIID da interface a ser criada.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetService(vi_GuidService, vi_Riid, &vi_pOutInterface);

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

	//Define o ponteiro na interface criada pelo usuário.
	CarenSetPointerToICarenSafe(vi_pOutInterface, Param_Ref_Interface, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o índice de fluxo real do dispositivo traduzido de um nome de fluxo amigável. 
/// </summary>
/// <param name="Param_NomeAmigavel">O nome amigável. Esse valor pode ser os valores da enumeração (CA_MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou outros valores. Veja na documentação do método.</param>
/// <param name="Param_Out_StreamIndexAtual">Recebe o valor do índice de fluxo que corresponde ao nome amigável.</param>
CarenResult CarenMFCaptureSource::GetStreamIndexFromFriendlyName(
UInt32 Param_NomeAmigavel,
[Out] UInt32% Param_Out_StreamIndexAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutStreamIndexAtual = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamIndexFromFriendlyName(Param_NomeAmigavel, &vi_OutStreamIndexAtual);

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

	//Define o valor no parametro de saida.
	Param_Out_StreamIndexAtual = static_cast<UInt32>(vi_OutStreamIndexAtual);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os efeitos de um fluxo de captura.
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
CarenResult CarenMFCaptureSource::RemoveAllEffects(UInt32 Param_SourceStreamIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAllEffects(static_cast<DWORD>(Param_SourceStreamIndex));

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
/// Remove um efeito de um fluxo de captura.
/// Este método remove um efeito que foi adicionado anteriormente usando o método ICarenMFCaptureSource::AddEffect.
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_Efeito">O ponteiro para a interface que contém o efeito a ser removido.</param>
CarenResult CarenMFCaptureSource::RemoveEffect(
UInt32 Param_SourceStreamIndex,
ICaren^ Param_Efeito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pEfeito = Nulo;

	//Recupera o ponteiro par ao efeito a ser removido.
	CarenGetPointerFromICarenSafe(Param_Efeito, vi_pEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveEffect(static_cast<DWORD>(Param_SourceStreamIndex), vi_pEfeito);

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
/// Define o formato de saída para um fluxo de captura.
/// Este método define o tipo de saída nativa no dispositivo de captura. O dispositivo deve suportar o formato especificado. Para obter a lista de formatos disponíveis, ligue para o ICarenMFCaptureSource::GetAvailableDeviceMediaType.
/// </summary>
/// <param name="Param_SourceStreamIndex">Index para o fluxo de captura. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_MediaType">Uma interface ICarenMFMediaType para o formato de saída para o fluxo de captura.</param>
CarenResult CarenMFCaptureSource::SetCurrentDeviceMediaType(
UInt32 Param_SourceStreamIndex,
ICarenMFMediaType^ Param_MediaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaType = Nulo;

	//Recupera o ponteiro para o media type atual.
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentDeviceMediaType(static_cast<DWORD>(Param_SourceStreamIndex), vi_pMediaType);

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
/// Habilita ou desativa o espelhamento da transmissão de visualização de vídeo. 
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo.</param>
/// <param name="Param_MirrorState">Se TRUE, o espelhamento estiver ativado; se FALSO, o espelhamento é desativado.</param>
CarenResult CarenMFCaptureSource::SetMirrorState(
UInt32 Param_StreamIndex,
Boolean Param_MirrorState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetMirrorState(static_cast<DWORD>(Param_StreamIndex), Param_MirrorState ? true : false);

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