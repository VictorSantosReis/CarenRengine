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
#include "CarenMFCapturePreviewSink.h"

//Destruidor.
CarenMFCapturePreviewSink::~CarenMFCapturePreviewSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFCapturePreviewSink::CarenMFCapturePreviewSink()
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
CarenResult CarenMFCapturePreviewSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFCapturePreviewSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFCapturePreviewSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFCapturePreviewSink**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFCapturePreviewSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFCapturePreviewSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFCapturePreviewSink**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFCapturePreviewSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFCapturePreviewSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFCapturePreviewSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFCapturePreviewSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFCapturePreviewSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFCapturePreviewSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFCapturePreviewSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFCapturePreviewSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFCapturePreviewSink();
}



// Métodos da interface proprietária(ICarenMFCapturePreviewSink)


/// <summary>
/// Obtém o estado de espelhamento atual da transmissão de visualização de vídeo.
/// </summary>
/// <param name="Param_Out_MirrorState">Recebe o valor TRUE se o espelhamento estiver ativado ou FALSE se o espelhamento for desativado.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::GetMirrorState(OutParam Boolean% Param_Out_MirrorState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutMirrorState = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMirrorState(&vi_OutMirrorState);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_MirrorState = vi_OutMirrorState ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a rotação do fluxo de visualização de vídeo.
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo. Você deve especificar uma transmissão de vídeo.</param>
/// <param name="Param_Out_RotacaoValue">Recebe a rotação da imagem, em graus.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::GetRotation(
UInt32 Param_StreamIndex,
OutParam UInt32% Param_Out_RotacaoValue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutRotationValue = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRotation(static_cast<DWORD>(Param_StreamIndex), &vi_OutRotationValue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_RotacaoValue = static_cast<UInt32>(Param_Out_RotacaoValue);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um sink de mídia personalizada para visualização.
/// </summary>
/// <param name="Param_MediaSink">Uma interface ICarenMFMediaSink com o ponteiro para o sink de mídia</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetCustomSink(ICarenMFMediaSink^ Param_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaSink* vi_pMediaSink = Nulo;

	//Recupera o ponteiro para o Media Sink.
	CarenGetPointerFromICarenSafe(Param_MediaSink, vi_pMediaSink);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCustomSink(vi_pMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

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
/// <param name="Param_MirrorState">Se TRUE, o espelhamento está ativado. Se FALSE, o espelho está desativado.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetMirrorState(Boolean Param_MirrorState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetMirrorState(Param_MirrorState ? TRUE : FALSE);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica uma Window(Handle) para visualização.
/// </summar
/// <param name="Param_HandleWindow">Uma Handle para a janela. O Sink de visualização desenha os quadros de vídeo dy>entro desta janela.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetRenderHandle(IntPtr Param_HandleWindow)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRenderHandle(Util.ConverterIntPtrToHandle(Param_HandleWindow));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica um visual Microsoft DirectComposition para visualização.
/// </summary>
/// <param name="Param_Surface">Uma interface ICaren que contém um ponteiro para um Visual DirectComposition que implementa a interface (IDCompositionVisual).</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetRenderSurface(ICaren^ Param_Surface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pSurface = Nulo;

	//Recupera o ponteiro para a superfice.
	CarenGetPointerFromICarenSafe(Param_Surface, vi_pSurface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRenderSurface(vi_pSurface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Rotaciona o fluxo de visualização de vídeo.
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo para girar. Você deve especificar uma transmissão de vídeo.</param>
/// <param name="Param_RotacaoValue">O valor para girar o vídeo, em graus. Os valores válidos são 0, 90, 180 e 270. O valor zero restaura o vídeo à sua orientação original.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetRotation(
UInt32 Param_StreamIndex,
UInt32 Param_RotacaoValue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRotation(static_cast<DWORD>(Param_StreamIndex), static_cast<DWORD>(Param_RotacaoValue));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um retorno de chamada para receber os dados de visualização de um fluxo.
/// Chamar este método substitui qualquer chamada anterior ao ICarenMFCapturePreviewSink::SetRenderHandle.
/// </summary>
/// <param name="Param_StreamSinkIndex">O índice baseado em zero do fluxo. O índice é devolvido no parâmetro (Param_Out_StreamSinkIndex) do método ICarenMFCaptureSink::AddStream.</param>
/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnSampleCallback que contém o ponteiro para o callback. O usuário deve implementar esta interface.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::SetSampleCallback(
UInt32 Param_StreamSinkIndex,
ICarenMFCaptureEngineOnSampleCallback^ Param_Callback)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFCaptureEngineOnSampleCallback* vi_pEngineCallback = Nulo;

	//Recupera o ponteiro para a interface de callback.
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pEngineCallback);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSampleCallback(static_cast<DWORD>(Param_StreamSinkIndex), vi_pEngineCallback);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza o quadro de vídeo. Ligue para este método quando a janela de visualização receber uma mensagem WM_PAINT ou WM_SIZE.
/// </summary>
/// <param name="Param_RectOrigem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem. O retângulo de origem define a área do quadro de vídeo que é exibido. Se este parâmetro for Nulo, todo o quadro de vídeo será exibido.</param>
/// <param name="Param_RectDestino">Uma estrutura CA_RECT que especifica o retângulo de destino. O retângulo de destino define a área da janela ou visual directcomposition onde o vídeo é desenhado.</param>
/// <param name="Param_CorBorda">A cor da borda a ser definida.</param>
/// <returns></returns>
CarenResult CarenMFCapturePreviewSink::UpdateVideo(
CA_MFVideoNormalizedRect^ Param_RectOrigem,
CA_RECT^ Param_RectDestino,
CA_MFARGB^ Param_CorBorda)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	MFVideoNormalizedRect* vi_pNormalizedRect = Nulo; //Pode ser Nulo.
	PRECT vi_pRectDestino = Nulo;
	COLORREF vi_CorBorda = 0;

	//Converte o retangulo de origem se informado.
	if (ObjetoGerenciadoValido(Param_RectOrigem))
		vi_pNormalizedRect = Util.ConverterMFVideoNormalizedRectManaged_ToUnamaged(Param_RectOrigem);

	//Converte a estrutura para o retangulo de destino.
	vi_pRectDestino = Util.ConverterRECTManagedToUnmanaged(Param_RectDestino);

	//Define os dados da cor da borda.
	vi_CorBorda = RGB(static_cast<DWORD>(Param_CorBorda->rgbRed), static_cast<DWORD>(Param_CorBorda->rgbGreen), static_cast<DWORD>(Param_CorBorda->rgbBlue));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateVideo(vi_pNormalizedRect, vi_pRectDestino, &vi_CorBorda);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pNormalizedRect);
	DeletarEstruturaSafe(&vi_pRectDestino);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenMFCaptureSink)


/// <summary>
/// Conecta um fluxo da fonte de captura a esta pia de captura.
/// </summary>
/// <param name="Param_SourceStreamIndex">O fluxo de origem para se conectar. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_MediaType">Uma ICarenMFMediaType que especifica o formato desejado do fluxo de saída.</param>
/// <param name="Param_Atributos">Uma interface ICarenMFAttributes para os atributos. Para fluxos comprimidos, você pode usar este parâmetro para configurar o codificador. Este parâmetro também pode ser Nulo.</param>
/// <param name="Param_Out_SinkStreamIndex">Recebe o índice do novo fluxo na pia de captura. Observe que este índice não corresponderá necessariamente ao valor do (Param_SourceStreamIndex).</param>
CarenResult CarenMFCapturePreviewSink::AddStream(
	UInt32 Param_SourceStreamIndex,
	ICarenMFMediaType^ Param_MediaType,
	ICarenMFAttributes^ Param_Atributos,
	[Out] UInt32% Param_Out_SinkStreamIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* vi_pMediaType = Nulo;
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser Nulo.
	DWORD vi_OutStreamSink = 0;

	//Recupera ao ponteiro para o Media Type
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Recupera um ponteiro para os atributos se informado
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddStream(static_cast<DWORD>(Param_SourceStreamIndex), vi_pMediaType, vi_pAttributes, &vi_OutStreamSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Defie o index do stream adicionado no parametro de saida.
	Param_Out_SinkStreamIndex = static_cast<UInt32>(vi_OutStreamSink);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o formato de saída para um fluxo nesta pia de captura.
/// </summary>
/// <param name="Param_SinkStreamIndex">O índice baseado em zero do fluxo para consulta. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
/// <param name="Param_Out_MediaType">Retorna uma interface ICarenMFMediaType com o formato do tipo de midia no fluxo especificado. O usuário é responsável por liberar a interface.</param>
CarenResult CarenMFCapturePreviewSink::GetOutputMediaType(
	UInt32 Param_SinkStreamIndex,
	[Out] ICarenMFMediaType^% Param_Out_MediaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputMediaType(static_cast<DWORD>(Param_SinkStreamIndex), &vi_pOutMediaType);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_MediaType = gcnew CarenMFMediaType(false);

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_MediaType, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Consulte o objeto Sink Writer(ICarenMFSourceReader) subjacente para uma interface.
/// </summary>
/// <param name="Param_SinkStreamIndex">O índice baseado em zero do fluxo para consulta. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
/// <param name="Param_GuidService">Um identificador de serviço GUID. Atualmente, o valor deve ser Nulo.</param>
/// <param name="Param_RIID">Um identificador de serviço GUID. Atualmente, o valor deve ser IID_IMFSinkWriter.</param>
/// <param name="Param_Ref_Interface">Retorna um ponteiro para a interface solicitada. O usuário é responsável por criar e liberar a interface.</param>
CarenResult CarenMFCapturePreviewSink::GetService(
	UInt32 Param_SinkStreamIndex,
	String^ Param_GuidService,
	String^ Param_RIID,
	ICaren^% Param_Ref_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidService = GUID_NULL; //Atualmente (07.12.2020) esse valor é Nulo.
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pOutInterface = Nulo;

	//Converte o guid de serviço se informado.
	if (StringObjetoValido(Param_GuidService))
		vi_GuidService = Util.CreateGuidFromString(Param_GuidService);

	//Converte a string para o guid da interface.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetService(static_cast<DWORD>(Param_SinkStreamIndex), vi_GuidService, vi_Riid, &vi_pOutInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

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
/// Prepara o sink de captura carregando quaisquer componentes de pipeline necessários, como codificadores, processadores de vídeo e coletores de mídia.
/// Chamar esse método é opcional. Este método dá ao aplicativo a oportunidade de configurar os componentes do pipeline antes de serem usados. O método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um evento MF_CAPTURE_SINK_PREPARED por meio do método ICarenMFCaptureEngineOnEventCallback::OnEvent. Depois que esse evento for recebido, chame ICarenMFCaptureSink::GetService para configurar componentes individuais.
/// </summary>
CarenResult CarenMFCapturePreviewSink::Prepare()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Prepare();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os fluxos do sink de captura. 
/// Você pode usar este método para reconfigurar o sink.
/// </summary>
CarenResult CarenMFCapturePreviewSink::RemoveAllStreams()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAllStreams();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}