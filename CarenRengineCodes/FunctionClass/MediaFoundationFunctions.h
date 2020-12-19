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


#pragma once
#include "../SDK_Base.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o SDK Base da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

/// <summary>
/// Classe responsável por conter funções nativas utilizada pela Api do Microsoft Media Foundation.
/// </summary>
public ref class MediaFoundationFunctions
{
	//Destruidor da classe.
public:
	MediaFoundationFunctions() {}
	~MediaFoundationFunctions()
	{
	}


	//Métodos da Media Foundation.
public:
	/// <summary>
	/// Método responsável por inicia a Api do Media Foundation.
	/// </summary>
	CarenResult _MFStartup();
	
	/// <summary>
	/// Método responsável por desligar a Api do Media Foundation.
	/// </summary>
	CarenResult _MFShutdown();

	/// <summary>
	/// ‎Cria um objeto ‎‎IRandomAccessStream‎‎ que envolve um fluxo byte da Microsoft Media Foundation.‎
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream para o fluxode bytes da Media Foundation.</param>
	/// <param name="Param_RIID">‎O identificador de interface (IID) da interface que está sendo solicitada.‎</param>
	/// <param name="Param_Out_Stream">Retorna uma interface base (ICaren) para a interface IRandomAccessStream do fluxo de bytes para a (ICarenMFByteStream).</param>
	/// <returns></returns>
	CarenResult _MFCreateStreamOnMFByteStreamEx(ICarenMFByteStream^ Param_ByteStream, String^ Param_RIID, ICaren^ Param_Out_Stream);

	/// <summary>
	/// Cria a fonte do sequenciador.
	/// </summary>
	/// <param name="Param_Reservado">Reservado. Deve ser NULO.</param>
	/// <param name="Param_Out_SequencerSource">Retorna a interface base (ICaren) para a interface (IMFSequencerSource[NÃO IMPLEMENTADA PELA DLL]) da fonte do sequenciador. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSequencerSource(ICaren^ Param_Reservado, ICaren^ Param_Out_SequencerSource);

	/// <summary>
	/// Cria um objeto de ativação para o Sample Grabber Media Sink(Sink de captura de amostras).
	/// </summary>
	/// <param name="Param_MediaType">Um interface ICarenMFMediaType, definindo o tipo de mídia para o fluxo de entrada do Sample Grabber(Capturador de amostras).</param>
	/// <param name="Param_SampleGrabberCallback">Uma interface IMFSampleGrabberSinkCallback[INTERFACE PENDENTE] para o callback. O usuário deve implementar esta interface.</param>
	/// <param name="Param_Out_Activate">Retorna uma interface (ICarenMFActivate) para o ativador. Use esta interface para completar a criação do Sample Grabber(Capturador de amostras). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSampleGrabberSinkActivate(ICarenMFMediaType^ Param_MediaType, ICaren^ Param_SampleGrabberCallback, ICarenMFActivate^ Param_Out_Activate);

	/// <summary>
	/// A copiadora de amostras é uma transformação da Media Foundation (MFT) que copia dados de amostras de entrada para amostras de saída sem modificar os dados. Os seguintes dados são copiados da amostra:
	/// Todos os atributos da amostra | O carimbo de tempo e duração | Bandeiras de amostra (ver ICarenMFSample::SetSampleFlags) | Os dados nos buffers de mídia. Se a amostra de entrada contiver vários buffers, 
	/// os dados são copiados em um único buffer na amostra de saída.
	/// </summary>
	/// <param name="Param_Out_CopierMFT">Recebe uma interface (ICarenMFTransform) para a transformação. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSampleCopierMFT(ICarenMFTransform^ Param_Out_CopierMFT);

	/// <summary>
	/// Cria um objeto de ativação genérico para transformações da Media Foundation (MFTs).
	/// </summary>
	/// <param name="Param_Out_Activate">Recebe uma interface (ICarenMFActivate) para o ativador da transformação. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTransformActivate(ICarenMFActivate^ Param_Out_Activate);

	/// <summary>
	/// Cria a misturadora de vídeo padrão para o renderizador de vídeo aprimorado (EVR).
	/// </summary>
	/// <param name="Param_Owner">Ponteiro para o dono deste objeto. Se o objeto for agregado, passe um ponteiro para a interface IUnknown do objeto agregador. Caso contrário, defina este parâmetro para NULO.</param>
	/// <param name="Param_RIIDDevice">Identificador de interface (IID) da interface do dispositivo de vídeo que será usado para processar o vídeo. Atualmente, o único valor suportado é IID_IDirect3DDevice9.</param>
	/// <param name="Param_RIID">IID da interface solicitada na mixer de vídeo. O mixer de vídeo expõe a interface ICarenMFTransform.</param>
	/// <param name="Param_Out_Objeto">Recebe a interface solicitada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoMixer(ICaren^ Param_Owner, String^ Param_RIIDDevice, String^ Param_RIID, ICaren^ Param_Out_Objeto);

	/// <summary>
	/// Cria um objeto IMFProtectedEnvironmentAccess[NÃO IMPLEMENTADA PELA DLL] que permite que sistemas de proteção de conteúdo realizem um handshake(aperto de mão) com o ambiente protegido.
	/// </summary>
	/// <param name="Param_Out_Access">Retorna uma interface base (ICaren) para a interface (IMFProtectedEnvironmentAccess[NÃO IMPLEMENTADA PELA DLL]). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateProtectedEnvironmentAccess(ICaren^ Param_Out_Access);

	/// <summary>
	/// Cria o objeto PMP (Protected Media Path, Caminho de Mídia Protegida (PMP).
	/// </summary>
	/// <param name="Param_Flags">Um membro da enumeração CA_MFPMPSESSION_CREATION_FLAGS que especifica como criar a sessão PMP.</param>
	/// <param name="Param_Out_PMPServer">Retorna uma interface base (ICaren) para a interface (IMFPMPServer[NÃO IMPLEMENTADA PELA DLL]). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreatePMPServer(CA_MFPMPSESSION_CREATION_FLAGS Param_Flags, ICaren^ Param_Out_PMPServer);
	
	/// <summary>
	/// Consulta um objeto para uma interface de serviço especificada.
	/// Esta função é uma função de ajudante que envolve o método ICarenMFGetService::GetService. A função consulta o objeto para a interface ICarenMFGetService e, se bem-sucedida, chama o GetService no objeto.
	/// </summary>
	/// <param name="Param_Objeto">A interface do objeto a ser consultado.</param>
	/// <param name="Param_GuidService">O identificador de serviço (SID) do serviço. Para obter uma lista de identificadores de serviço, consulte a estrutura (GUIDs::GUIDs_MF_SERVICE_INTERFACES)</param>
	/// <param name="Param_RIID">O identificador de interface (IID) da interface que está sendo solicitada.</param>
	/// <param name="Param_Out_InterfaceRequested">Retorna a interface solicitada se encontrada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFGetService(
		ICaren^ Param_Objeto, 
		String^ Param_GuidService,
		String^ Param_RIID, 
		ICaren^ Param_Out_InterfaceRequested);

	/// <summary>
	/// Cria um fluxo byte que é apoiado por um arquivo local temporário.
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado do arquivo temporário. O usuário é responsável por inicializar a interace antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTempFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode,
		CA_MF_FILE_OPENMODE Param_OpenMode,
		CA_MF_FILE_FLAGS Param_Flags,
		ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Cria um fluxo byte de um arquivo de forma sincrona.
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Url">Uma string que contém a url para o arquivo.</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado do arquivo. O usuário é responsável por inicializar a interace antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode,
		CA_MF_FILE_OPENMODE Param_OpenMode,
		CA_MF_FILE_FLAGS Param_Flags,
		String^ Param_Url,
		ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Começa uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// Quando a solicitação for concluída, o método ICarenMFAsyncCallback do objeto de chamada é chamado. O objeto de retorno de chamada deve então chamar a função _MFEndCreateFile para obter a interface para o fluxo byte(ICarenMFByteStream).
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Url">Uma string que contém a url para o arquivo.</param>
	/// <param name="Param_Callback">Uma interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface</param>
	/// <param name="Param_ObjectState">Uma interface IUnknown de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	/// <param name="Param_Out_CancelCookie">Recebe uma interface IUnknown ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona passando esta interface para a função _MFCancelCreateFile. O chamador deve liberar a interface. Este parâmetro é opcional e pode ser NULO.</param>
	/// <returns></returns>
	CarenResult _MFBeginCreateFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode, 
		CA_MF_FILE_OPENMODE Param_OpenMode, 
		CA_MF_FILE_FLAGS Param_Flags, 
		String^ Param_Url, 
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjectState,
		ICaren^ Param_Out_CancelCookie);

	/// <summary>
	/// Completa uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// </summary>
	/// <param name="Param_Result">Uma interface ICarenMFAsyncResult. Passe a mesma interface que seu objeto de retorno de chamada recebeu no método (Invoke).</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFEndCreateFile(ICarenMFAsyncResult^ Param_Result, ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Cancela uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// </summary>
	/// <param name="Param_CancelCookie">Uma interface IUnknown do objeto de cancelamento. Esta interface é recebida no parâmetro (Param_Out_CancelCookie) da função _MFBeginCreateFile.</param>
	/// <returns></returns>
	CarenResult _MFCancelCreateFile(ICaren^ Param_CancelCookie);

	/// <summary>
	/// Cria um objeto de ativação para uma classe do Windows Runtime.
	/// </summary>
	/// <param name="Param_ActivatableClassId">O identificador de classe que está associado à classe de tempo de execução ativável.</param>
	/// <param name="Param_Configuration">Um ponteiro para um objeto IPropertySet opcional, que é usado para configurar a classe do Windows Runtime. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_RIID">O identificador de interface(IID) da interface solicitada.O objeto de ativação criado por esta função suporta as seguintes interfaces: IClassFactory, ICarenMFActivate, ICarenPersisStream</param>
	/// <param name="Param_Out_Objeto">Recebe a interface que foi solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMediaExtensionActivate(String^ Param_ActivatableClassId, ICaren^ Param_Configuration, String^ Param_RIID, ICaren^ Param_Out_Objeto);

	/// <summary>
	/// Cria uma interface IMFContentDecryptorContext para o sistema de proteção de mídia especificado.
	/// </summary>
	/// <param name="Param_GuidMediaProtectionSystem">O identificador do sistema de proteção de mídia para o qual você deseja criar uma interface IMFContentDecryptorContext.</param>
	/// <param name="Param_DXGIManager">Uma interface ICarenMFDXGIDeviceManager que você deseja usar para compartilhar o dispositivo Direct3D 11.</param>
	/// <param name="Param_ProtectionDevice">A interface IMFContentProtectionDevice para o sistema de proteção de mídia especificado.</param>
	/// <param name="Param_Out_ContentDecryptorContext">Retorna um pontiro para a interface (IMFContentDecryptorContext) criada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateContentDecryptorContext(String^ Param_GuidMediaProtectionSystem, ICarenMFDXGIDeviceManager^ Param_DXGIManager, ICaren^ Param_ProtectionDevice, ICaren^ Param_Out_ContentDecryptorContext);

	/// <summary>
	/// Cria uma interface IMFContentProtectionDevice para o sistema de proteção de mídia especificado.
	/// </summary>
	/// <param name="Param_GuidMediaProtectionSystem">O identificador do sistema de proteção de mídia para o qual você deseja criar a interface IMFContentProtectionDevice.</param>
	/// <param name="Param_Out_ContentProtectionDevice">Retorna um pontiro para a interface (IMFContentProtectionDevice) criada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateContentProtectionDevice(String^ Param_GuidMediaProtectionSystem, ICaren^ Param_Out_ContentProtectionDevice);

	/// <summary>
	/// Cria um objeto de serviços DXVA (DirectX Video Acceleration, aceleração de vídeo directx). Ligue para esta função se o aplicativo usar O DXVA diretamente, sem usar o DirectShow ou a Media Foundation.
	/// </summary>
	/// <param name="Param_Direct3DDevice9">Umaa interface IDirect3DDevice9 de um dispositivo Direct3D.</param>
	/// <param name="Param_RIID">O identificador de interface (IID) da interface solicitada. Qualquer uma das seguintes interfaces pode ser suportada pelo dispositivo Direct3D: IDirectXVideoAcacelerationService | 
	/// IDirectXVideoDecoderService | IDirectXVideoProcessorService</param>
	/// <param name="Param_Out_VideoService">Recebe o ponteiro para a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _DXVA2CreateVideoService(ICaren^ Param_Direct3DDevice9, String^ Param_RIID, ICaren^ Param_Out_VideoService);

	/// <summary>
	/// Aloca a memória do sistema com um alinhamento de byte especificado e cria um buffer de mídia para gerenciar a memória.
	/// </summary>
	/// <param name="Param_MaxLenght">O tamanho do buffer, em bytes.</param>
	/// <param name="Param_Aligment">Especifica o alinhamento de memória para o buffer.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAlignedMemoryBuffer(UInt32 Param_MaxLenght, CA_MF_BYTE_ALIGNMENT Param_Aligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um buffer de mídia para gerenciar uma superfície DXGI (Microsoft DirectX Graphics Infrastructure).
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície DXGI. Este valor deve ser IID_ID3D11Texture2D.</param>
	/// <param name="Param_SuperficeDXGI">Uma interface IUnknown da superfície DXGI.</param>
	/// <param name="Param_SubresourceIndex">O índice baseado em zero de uma subrefonte da superfície. O objeto buffer de mídia está associado a essa subrefonte.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. Este objeto suporta as seguintes interfaces de buffer: ICarenMF2DBuffer, ICarenMF2DBuffer2, ICarenMFDXGIBuffer e ICarenMFMediaBuffer. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXGISurfaceBuffer(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_SubresourceIndex, Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia uma superfície Direct3D 9.
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície Direct3D 9. Atualmente esse valor deve ser IID_IDirect3DSurface9.</param>
	/// <param name="Param_SurfaceDX">Uma interface IUnknown da superfície DirectX.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXSurfaceBuffer(String^ Param_RIID, ICaren^ Param_SurfaceDX,  Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Aloca um buffer de memória do sistema que é ideal para um tipo de mídia especificado.
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType do tipo de mídia.</param>
	/// <param name="Param_Duration">A duração da amostra. Este valor é necessário para formatos de áudio.</param>
	/// <param name="Param_MinLenght">O tamanho mínimo do buffer, em bytes. O tamanho real do buffer pode ser maior. Especifique zero para alocar o tamanho padrão do buffer para o tipo de mídia.</param>
	/// <param name="Param_MinAligment">O alinhamento mínimo da memória para o buffer. Especifique zero para usar o alinhamento de memória padrão.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMediaBufferFromMediaType(ICarenMFMediaType^ Param_MediaType, Int64 Param_Duration, UInt32 Param_MinLenght, UInt32 Param_MinAligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia um bitmap do Windows Imaging Component (WIC).
	/// </summary>
	/// <param name="Param_RIID">O identificador da interface. Atualmente este parametro deve ser IID_IWICBitmap</param>
	/// <param name="Param_Surface">Uma interface IUnknown da superfície bitmap. A superfície bitmap deve ser um bitmap WIC que expõe a interface ICarenWICBitmap.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWICBitmapBuffer(String^ Param_RIID, ICaren^ Param_Surface, ICarenMFMediaBuffer^ Param_Out_Buffer);
	
	/// <summary>
	/// Invoca um método de retorno para completar uma operação assíncrona.
	/// </summary>
	/// <param name="Param_AsyncResult">Uma interface ICarenMFAsyncResult para completar a operação.</param>
	/// <returns></returns>
	CarenResult _MFInvokeCallback(ICarenMFAsyncResult^ Param_AsyncResult);

	/// <summary>
	/// Cria um ICarenMFAttributes descrevendo o conteúdo de substreams multiplexados.
	/// </summary>
	/// <param name="Param_ColecaoAtributosMuxStream">A coleção contendo os (IMFAttributes) para cada substream multiplexado.</param>
	/// <param name="Param_Out_Atribtuos">Retorna a interface contendo os atributos para os substreams multiplexados. O usuário deve inicializar a interface antes de chamar este método.</param>
	CarenResult _MFCreateMuxStreamAttributes(ICarenMFCollection^ Param_ColecaoAtributosMuxStream, ICarenMFAttributes^ Param_Out_Atribtuos);

	/// <summary>
	/// Cria um objeto de ativação para o (Streaming Audio Render).
	/// </summary>
	/// <param name="Param_Out_StreamingAudioRender">Retorna a interface (ICarenMFActivate) de ativação do (Streaming Audio Render). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAudioRendererActivate(ICarenMFActivate^ Param_Out_StreamingAudioRender);

	/// <summary>
	/// Cria um objeto de ativação para o (Enhanced Video Renderer (EVR)).
	/// </summary>
	/// <param name="Param_Hwnd">A handle para a janela que vai exibir o vídeo.</param>
	/// <param name="Param_Out_EnhancedVideoRenderer">Retorna a interface (ICarenMFActivate) de ativação do (Enhanced Video Renderer). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoRendererActivate(IntPtr Param_Hwnd, ICarenMFActivate^ Param_Out_EnhancedVideoRenderer);

	/// <summary>
	/// Cria uma nova instância do Media Sink para o SAR (Streaming Audio Render).
	/// </summary>
	/// <param name="Param_AudioAtributos">Uma interface ICarenMFAttributes, que é usada para configurar o renderizador de áudio. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) para o SAR. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAudioRenderer(ICarenMFAttributes^ Param_AudioAtributos, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do Media Sink do processador de vídeo aprimorado (EVR).
	/// </summary>
	/// <param name="Param_RIID">Identificador de interface (IID) da interface solicitada no EVR.</param>
	/// <param name="Param_Out_VideoRenderer">Recebe a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoRenderer(String^ Param_RIID, ICaren^ Param_Out_VideoRenderer);

	/// <summary>
	/// Cria um media sink para criar arquivos 3GP.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo 3GP para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia 3GP(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreate3GPMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do AC-3 media sink.
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo AC-3 para este fluxo de byte. O fluxo de byte deve ser escrito.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo de áudio AC-3. O tipo de mídia deve conter os seguintes atributos: MF_MT_MAJOR_TYPE & MF_MT_SUBTYPE</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia 3GP(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAC3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do media sink do fluxo de transporte de dados de áudio (ADTS).
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o fluxo ADTS para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo ADTS. O tipo de mídia deve conter os seguintes atributos: MF_MT_MAJOR_TYPE & MF_MT_SUBTYPE & MF_MT_AAC_PAYLOAD_TYPE</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateADTSMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor de arquivos WAVE. O coletor de arquivos WAVE pega o áudio e o grava em um arquivo .wav.
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o fluxo WAVE para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo WAVE.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia WAVE(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWAVEMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma nova instância do coletor de midia MP3(Media Sink).
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo mp3 para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMP3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um media sink para a criação de arquivos MP4 fragmentados.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo MP4 para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia MP4(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateFMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um media sink para a criação de arquivos MP4.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo AVI para este fluxo byte.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia AVI(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor Audio-Video Interleaved (AVI).
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo MP4 para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia MP4(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAVIMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor de mídia(Media Sink) genérico que envolve uma transformação multiplexadora do Microsoft Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_GuidOutputSubtype">O GUID do subtipo do tipo de saída para o MFT.</param>
	/// <param name="Param_OutputAttributes">Uma lista de atributos de formato para o tipo de saída MFT. Este parâmetro é opcional e pode ser NULO.</param>
	/// <param name="Param_OutputByteStream">uma interface ICarenMFByteStream de um fluxo de bytes. A saída do MFT é gravada neste fluxo de bytes. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMuxSink(String^ Param_GuidOutputSubtype, ICarenMFAttributes^ Param_OutputAttributes, ICarenMFByteStream^ Param_OutputByteStream, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um objeto de ativação que representa um dispositivo de captura de hardware.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface ICarenMFAttributes de uma loja de atributos, que é usada para selecionar o dispositivo de captura.</param>
	/// <param name="Param_Out_DispositivoCaptura">Retorna a interface (ICarenMFActivate) de ativação do dispositivo de captura. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDeviceSourceActivate(ICarenMFAttributes^ Param_Atributos, ICarenMFActivate^ Param_Out_DispositivoCaptura);

	/// <summary>
	/// Cria o objeto de ativação para um Sink de Transcodificação.
	/// O objeto de ativação do coletor de transcodificação pode ser usado para criar qualquer um dos seguintes coletores de arquivo: Coletor de arquivo 3GP, MP3 ou MP4.
	/// </summary>
	/// <param name="Param_Out_Transcode">Retorna uma interface ICarenMFActivate. Esta interface é usada para criar a instância do coletor de arquivos a partir do objeto de ativação. Antes de fazer isso, consulte o 
	/// ponteiro retornado para a interface ICarenMFTranscodeSinkInfoProvider e use essa interface para inicializar o objeto.  O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTranscodeSinkActivate(CarenMFActivate^ Param_Out_Transcode);

	/// <summary>
	/// Cria um objeto de ativação que pode ser usado para criar um codificador WMA (Windows Media Audio).
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType. Este parâmetro especifica o formato de saída codificado.</param>
	/// <param name="Param_EncodingProperties">Uma interface ICarenPropertyStore de uma loja de propriedades que contém parâmetros de codificação. Os parâmetros de codificação do codificador WMV são definidos no arquivo de cabeçalho wmcodecdsp.h. Se você tiver um objeto ASF ContentInfo que contenha um objeto de perfil ASF com todos os fluxos para o arquivo de saída, você pode obter a loja de propriedades ligando para IMFASFContentInfo::GetEncodingConfigurationPropertyStore.</param>
	/// <param name="Param_Out_Codificador">Retorna uma interface (ICarenMFActivate) do objeto de ativação para o codificador de áudio WMA. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWMAEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador);

	/// <summary>
	/// Cria um objeto de ativação que pode ser usado para criar um codificador WMV (Windows Media Video).
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType. Este parâmetro especifica o formato de saída codificado.</param>
	/// <param name="Param_EncodingProperties">Uma interface ICarenPropertyStore de uma loja de propriedades que contém parâmetros de codificação. Os parâmetros de codificação do codificador WMV são definidos no arquivo de cabeçalho wmcodecdsp.h. Se você tiver um objeto ASF ContentInfo que contenha um objeto de perfil ASF com todos os fluxos para o arquivo de saída, você pode obter a loja de propriedades ligando para IMFASFContentInfo::GetEncodingConfigurationPropertyStore.</param>
	/// <param name="Param_Out_Codificador">Retorna uma interface (ICarenMFActivate) do objeto de ativação para o codificador de áudio WMA. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWMVEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador);

	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult _MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	
	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult _MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEX^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	
	/// <summary>
	/// Inicializa um tipo de mídia de um WAVEFORMATEX estrutura.
	/// </summary>
	/// <param name="Param_WavFormato">Uma estrutura wav que contém as informações do tipo de midia a ser criado.</param>
	/// <param name="Param_SizeEstrutura">O tamanho da estrutura em bytes.</param>
	/// <param name="Param_Out_TipoMidia">Retorna o tipo de midia convertida da estrutura Wav. O usuário é responsável por inicializar a classe antes de chamar este método.</param>
	CarenResult CA_MFInitMediaTypeFromWaveFormatEx(
		CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, 
		UInt32 Param_SizeEstrutura, 
		ICarenMFMediaType^ Param_Out_TipoMidia);
};

