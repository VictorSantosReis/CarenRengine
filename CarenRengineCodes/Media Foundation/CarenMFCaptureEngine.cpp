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
#include "CarenMFCaptureEngine.h"


//Destruidor.
CarenMFCaptureEngine::~CarenMFCaptureEngine()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFCaptureEngine::CarenMFCaptureEngine()
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
CarenResult CarenMFCaptureEngine::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFCaptureEngine::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFCaptureEngine*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFCaptureEngine::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFCaptureEngine*>(Param_PonteiroNativo);

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
CarenResult CarenMFCaptureEngine::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFCaptureEngine::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFCaptureEngine::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFCaptureEngine::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFCaptureEngine::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFCaptureEngine::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFCaptureEngine::LiberarReferencia()
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
void CarenMFCaptureEngine::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFCaptureEngine();
}



// Métodos da interface proprietária(ICarenMFCaptureEngine)


/// <summary>
///  Obtém um ponteiro para um dos objetos do Sink de captura. Você pode usar os Sinks de captura para configurar a visualização, gravação ou captura de imagem parada.
/// </summary>
/// <param name="Param_CaptureSinkType">Um valor da enumeração CA_MF_CAPTURE_ENGINE_SINK_TYPE que especifica o sink de captura a ser recuperado.</param>
/// <param name="Param_Ref_Sink">A interface que vai receber o sink de captura especificado. O usuário deve criar e é responsável por liberar quando não foi mais usar.</param>
CarenResult CarenMFCaptureEngine::GetSink(
CA_MF_CAPTURE_ENGINE_SINK_TYPE Param_CaptureSinkType,
ICaren^% Param_Ref_Sink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFCaptureSink* vi_pOutSink = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSink(static_cast<MF_CAPTURE_ENGINE_SINK_TYPE>(Param_CaptureSinkType), &vi_pOutSink);

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

	//Define o sink na interface criada pelo usuário.
	CarenSetPointerToICarenSafe(vi_pOutSink, Param_Ref_Sink, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um ponteiro para o objeto de origem de captura. Use a fonte de captura para configurar os dispositivos de captura. 
/// </summary>
/// <param name="Param_Out_CaptureSource">Retorna um ponteiro para a interface ICarenMFCaptureSource. O usuário é responsável por liberar a interface.</param>
CarenResult CarenMFCaptureEngine::GetSource([Out] ICarenMFCaptureSource^% Param_Out_CaptureSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFCaptureSource* vi_pOutCaptureSource = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSource(&vi_pOutCaptureSource);

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
	Param_Out_CaptureSource = gcnew CarenMFCaptureSource();

	//Define o ponteiro na interface a ser retornada.
	CarenSetPointerToICarenSafe(vi_pOutCaptureSource, Param_Out_CaptureSource, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o motor de captura.
/// Você deve chamar este método uma vez antes de usar o mecanismo de captura. Chamar o método de segunda vez retorna ER_MF_E_INVALIDREQUEST.
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_INITIALIZED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnEventCallback. O usuário deve implementar esta interface. O mecanismo de captura usa esta interface para enviar eventos assíncronos ao chamador.</param>
/// <param name="Param_Atributos">Você pode usar este parâmetro para configurar o mecanismo de captura. Este parâmetro pode ser Nulo.</param>
/// <param name="Param_AudioSource">Um ponteiro que especifica um dispositivo de captura de áudio. Este parâmetro pode ser Nulo.</param>
/// <param name="Param_VideoSource">Um ponteiro que especifica um dispositivo de captura de vídeo. Este parâmetro pode ser Nulo.</param>
CarenResult CarenMFCaptureEngine::Initialize(
ICarenMFCaptureEngineOnEventCallback^ Param_Callback,
ICarenMFAttributes^ Param_Atributos,
ICaren^ Param_AudioSource,
ICaren^ Param_VideoSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFCaptureEngineOnEventCallback* vi_pEngineCallback = Nulo;
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	IUnknown* vi_pAudioSource = Nulo; //Pode ser Nulo.
	IUnknown* vi_pVideoSource = Nulo; //Pode ser Nulo.

	//Recupera o ponteiro para o Callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pEngineCallback);

	//Recupera o ponteiro para os Atributos se valido.
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Recupera o ponteiro para o Audio Source se informado.
	if (ObjetoGerenciadoValido(Param_AudioSource))
		CarenGetPointerFromICarenSafe(Param_AudioSource, vi_pAudioSource);

	//Recupera o ponteiro para o Video Source se informado.
	if (ObjetoGerenciadoValido(Param_VideoSource))
		CarenGetPointerFromICarenSafe(Param_VideoSource, vi_pVideoSource);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(
		vi_pEngineCallback,
		vi_pAttributes,
		vi_pAudioSource,
		vi_pVideoSource);

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
/// Inicializa a pré-visualização. 
/// Antes de chamar esse método, configure o Sink de visualização chamando ICarenMFCaptureSink::AddStream.
/// Para obter um ponteiro para o Sink de visualização, ligue para o ICarenMFCaptureEngine::GetSink.
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PREVIEW_STARTED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
CarenResult CarenMFCaptureEngine::StartPreview()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StartPreview();

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
/// Começa a gravar áudio e/ou vídeo em um arquivo.
/// Antes de chamar esse método, configure o Sink de gravação chamando IMFCaptureSink::AddStream. Para obter um ponteiro para o Sink de gravação, ligue para o ICarenMFCaptureEngine::GetSink.
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_RECORD_STARTED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
CarenResult CarenMFCaptureEngine::StartRecord()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StartRecord();

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
/// Interrompe a visualização.
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PREVIEW_STOPPED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
CarenResult CarenMFCaptureEngine::StopPreview()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StopPreview();

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
/// Para de gravar. 
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_RECORD_STOPPED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
/// <param name="Param_Finalizar">Um valor booleano que especifica se deve finalizar o arquivo de saída. Para criar um arquivo de saída válido, especifique TRUE. Especifique FALSO somente se você quiser interromper a gravação e descartar o arquivo de saída. Se o valor for FALSO,a operação será concluída mais rapidamente, mas o arquivo não será jogável.</param>
/// <param name="Param_FlushUnprocessedSamples">Um valor booleano que especifica se as amostras não processadas aguardando para serem codificadas devem ser liberadas.</param>
CarenResult CarenMFCaptureEngine::StopRecord(
Boolean Param_Finalizar,
Boolean Param_FlushUnprocessedSamples)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StopRecord(Param_Finalizar ? TRUE : FALSE, Param_FlushUnprocessedSamples ? TRUE : FALSE);

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
/// Captura uma imagem parada do fluxo de vídeo. 
/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PHOTO_TAKEN evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
/// </summary>
CarenResult CarenMFCaptureEngine::TakePhoto()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TakePhoto();

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