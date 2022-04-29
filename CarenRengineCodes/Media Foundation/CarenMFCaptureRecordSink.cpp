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
#include "CarenMFCaptureRecordSink.h"

//Destruidor.
CarenMFCaptureRecordSink::~CarenMFCaptureRecordSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFCaptureRecordSink::CarenMFCaptureRecordSink()
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
CarenResult CarenMFCaptureRecordSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFCaptureRecordSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFCaptureRecordSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFCaptureRecordSink**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFCaptureRecordSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFCaptureRecordSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFCaptureRecordSink**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFCaptureRecordSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFCaptureRecordSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFCaptureRecordSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFCaptureRecordSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFCaptureRecordSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFCaptureRecordSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFCaptureRecordSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFCaptureRecordSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFCaptureRecordSink();
}



// Métodos da interface proprietária(ICarenMFCaptureRecordSink)


/// <summary>
/// Obtém a rotação que está sendo aplicada ao fluxo de vídeo gravado.
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo. Você deve especificar uma transmissão de vídeo.</param>
/// <param name="Param_Out_RotationValue">Recebe a rotação da imagem, em graus.</param>
CarenResult CarenMFCaptureRecordSink::GetRotation(
UInt32 Param_StreamIndex,
[Out] UInt32% Param_Out_RotationValue)
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
	Param_Out_RotationValue = static_cast<UInt32>(vi_OutRotationValue);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um sink de mídia personalizada para gravação.
/// Este método substitui a seleção padrão do sink de mídia para gravação.
/// </summary>
/// <param name="Param_MediaSink">Uma interface ICarenMFMediaSink para o sink da mídia.</param>
CarenResult CarenMFCaptureRecordSink::SetCustomSink(ICarenMFMediaSink^ Param_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaSink* vi_pMediaSink = Nulo;

	//Recupera o ponteiro para a interface do Media Sink.
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
/// Especifica um fluxo de byte que receberá os dados para a gravação.
/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputFileName ou ICarenMFCaptureRecordSink::SetSampleCallback.
/// </summary>
/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O fluxo de byte deve suportar escrita.</param>
/// <param name="Param_GuidContainer">Um GUID que especifica o tipo de recipiente de arquivo. Os valores possíveis estão documentados no atributo MF_TRANSCODE_CONTAINERTYPE.</param>
CarenResult CarenMFCaptureRecordSink::SetOutputByteStream(
ICarenMFByteStream^ Param_ByteStream,
String^ Param_GuidContainer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	GUID vi_GuidContainer = GUID_NULL;

	//Recupera o ponteiro para a interface do byte stream.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Converte a string para o guid.
	vi_GuidContainer = Util.CreateGuidFromString(Param_GuidContainer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputByteStream(vi_pByteStream, vi_GuidContainer);

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
/// Especifica o nome do arquivo de saída para a gravação.
/// O mecanismo de captura usa a extensão do nome do arquivo para selecionar o tipo de contêiner para o arquivo de saída. Por exemplo, se a extensão do nome do arquivo for ." mp4", o mecanismo de captura cria um arquivo MP4.
/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetSampleCallback.
/// </summary>
/// <param name="Param_Url">Uma String que contém a URL do arquivo de saída.</param>
CarenResult CarenMFCaptureRecordSink::SetOutputFileName(String^ Param_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCWSTR vi_pUrlDestino = Nulo;

	//Converte a string gerenciada para a nativa.
	vi_pUrlDestino = Util.ConverterStringToConstWCHAR(Param_Url);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputFileName(vi_pUrlDestino);

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
	//Libera a memória para a string.
	DeletarStringAllocatedSafe(&vi_pUrlDestino);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Rotaciona o fluxo de vídeo gravado.
/// </summary>
/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo para girar. Você deve especificar uma transmissão de vídeo.</param>
/// <param name="Param_RotationValue">A quantidade para girar o vídeo, em graus. Os valores válidos são 0, 90, 180 e 270. O valor zero restaura o vídeo à sua orientação original.</param>
CarenResult CarenMFCaptureRecordSink::SetRotation(
UInt32 Param_StreamIndex,
UInt32 Param_RotationValue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRotation(static_cast<DWORD>(Param_StreamIndex), static_cast<DWORD>(Param_RotationValue));

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
/// Define um Callback para receber os dados de gravação de um fluxo.
/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetOutputFileName.
/// </summary>
/// <param name="Param_StreamSinkIndex">O índice baseado em zero do fluxo. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnSampleCallback. O usuário deve implementar esta interface.</param>
CarenResult CarenMFCaptureRecordSink::SetSampleCallback(
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




// Métodos da interface (ICarenMFCaptureSink)


/// <summary>
/// Conecta um fluxo da fonte de captura a esta pia de captura.
/// </summary>
/// <param name="Param_SourceStreamIndex">O fluxo de origem para se conectar. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
/// <param name="Param_MediaType">Uma ICarenMFMediaType que especifica o formato desejado do fluxo de saída.</param>
/// <param name="Param_Atributos">Uma interface ICarenMFAttributes para os atributos. Para fluxos comprimidos, você pode usar este parâmetro para configurar o codificador. Este parâmetro também pode ser Nulo.</param>
/// <param name="Param_Out_SinkStreamIndex">Recebe o índice do novo fluxo na pia de captura. Observe que este índice não corresponderá necessariamente ao valor do (Param_SourceStreamIndex).</param>
CarenResult CarenMFCaptureRecordSink::AddStream(
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
CarenResult CarenMFCaptureRecordSink::GetOutputMediaType(
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
CarenResult CarenMFCaptureRecordSink::GetService(
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
CarenResult CarenMFCaptureRecordSink::Prepare()
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
CarenResult CarenMFCaptureRecordSink::RemoveAllStreams()
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