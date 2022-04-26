using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Windows.Forms;

//Importa os SDKs base.
using CarenRengine;
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.Estruturas;
using CarenRengine.SDKBase.GUIDs;
using CarenRengine.CarenStatus;

//Importa o SDK da Media Foundation.
using CarenRengine.MediaFoundation;

namespace MediaSessionPlaybackTest
{
    public partial class MediaSessionPlayback : Form
    {
        public MediaSessionPlayback()
        {
            InitializeComponent();
        }

        #region Estruturas & Enumerações 
        private struct MyMediaSessionConfig
        {
            public ICarenMFSourceResolver ResolvedorMidia { get; set; }
            public ICarenMFMediaSource SourceMidia { get; set; }
            public ICarenMFTopology Topologia { get; set; }
            public ICarenMFAsyncCallback CallbackMediaSession { get; set; }
            public ICarenMFAsyncCallback CallbackCreateMediaSource { get; set; }
            public ICarenMFMediaSession MediaSession { get; set; }
            public ICarenMFPresentationDescriptor DescritorMidia;
            public ICarenMFClock Relogio;
            public ICarenMFPresentationClock RelogioApresentacao { get; set; }
            public ICarenMFVideoDisplayControl DisplayPlaybackControl { get; set; }
            public ICarenMFSimpleAudioVolume AudioVolumePlayback { get; set; }


            public UInt64 TotalTimeMidiaNs { get; set; }
            public UInt64 TotalTimeMidiaSegundos { get; set; }
            public UInt32 TotalStreamMediaSource;
            public String UrlMidia { get; set; }
            public IntPtr HandleVideoPlayback { get; set; }

        }

        private enum StatusRendering
        {
            NoStarted,

            Rendering,

            Paused,

            Stoped,

            Closed
        }
        #endregion

        #region Variaveis
        MyMediaSessionConfig myMediaSession = new MyMediaSessionConfig();

        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();

        StatusRendering StatusPlayback = StatusRendering.NoStarted;

        private readonly object Obj_SyncVolume = new object();

        private readonly object Obj_SyncVideoPos = new object();

        private UInt64 REFTIME_1_SEGUNDO = (UInt64)Math.Pow(10, 7); //Valor que se refere a 1 segundo de mídia em unidades de 100 nanossegundos.
        #endregion


        #region Métodos de configuração
        /// <summary>
        /// Inicializa a configuração basica da Media Session, configura enventos e inicia a solicitação para a criação do arquivo de mídia de forma assincrona.
        /// </summary>
        /// <returns></returns>
        public CarenResult IniciarConfiguração()
        {
            //Variavel que vai retornar o resultado da operação.
            CarenResult Resultado = ResultCode.SS_OK;

            //Inicia a plataforma da Media Foundation.
            MFTFuncs._MFStartup();

            //Cria uma instância da media session.
            myMediaSession.MediaSession = new CarenMFMediaSession(null);

            //Cria as interfaces de Callback.
            myMediaSession.CallbackMediaSession = new CarenMFAsyncCallback(true);
            myMediaSession.CallbackCreateMediaSource = new CarenMFAsyncCallback(true);

            //Configura os eventos da Media Session
            myMediaSession.CallbackMediaSession.OnInvoke += CallbackMediaSession_OnInvoke;
            myMediaSession.CallbackMediaSession.OnGetParameters += CallbackMediaSession_OnGetParameters;

            //Configura os eventos do Source Resolver.
            myMediaSession.CallbackCreateMediaSource.OnGetParameters += CallbackCreateMediaSource_OnGetParameters;
            myMediaSession.CallbackCreateMediaSource.OnInvoke += CallbackCreateMediaSource_OnInvoke;

            //Registra os eventos para receber as notificações.
            myMediaSession.CallbackMediaSession.RegistrarCallback();
            myMediaSession.CallbackCreateMediaSource.RegistrarCallback();

            //Inicia uma solicitação assíncrona para o proximo evento na fila para a Media Session.
            Resultado = myMediaSession.MediaSession.BeginGetEvent(myMediaSession.CallbackMediaSession, null);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar definir o callback na media session1", true);

                //Sai do método.
                goto Done;
            }

            //Define a url.
            myMediaSession.UrlMidia = Txb_Url.Text;
            //Define a handle da janela de video.
            myMediaSession.HandleVideoPlayback = PanelRender.Handle;

            //Cria o resolvedor de midia para criar o media source.
            myMediaSession.ResolvedorMidia = new CarenMFSourceResolver(true);

            //Chama o método para criar o Media Source a parti da url.
            Resultado = myMediaSession.ResolvedorMidia.BeginCreateObjectFromURL(
                myMediaSession.UrlMidia,
                CA_SOURCE_RESOLVER_FLAGS.MF_RESOLUTION_MEDIASOURCE,
                null, 
                new CarenParamResolver<ICaren>(true),
                myMediaSession.CallbackCreateMediaSource, //Configura o Callback da fonte de midia.
                null);

            //Verifica se não houve erro
            if(Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar criar uma fonte de mídia para a URL informada!", true);

                //Sai do método.
                goto Done;
            }

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// O método responsável por chamar as funções para configurar os nós de entrada e saida para os fluxos do arquivo a ser renderizado.
        /// </summary>
        /// <returns></returns>
        public CarenResult ConfigurarTopologia()
        {
            //Variavel que vai retornar o resultado da operação.
            CarenResult Resultado = ResultCode.SS_OK;

            //Cria a topologia
            myMediaSession.Topologia = new CarenMFTopology(true);

            //Cria um for para criar os nós de topologia para os fluxos da midia carregada.
            for (uint i = 0; i < myMediaSession.TotalStreamMediaSource; i++)
            {
                //Chama o método para configurar os nós de entrada e saida.
                Resultado = Configurar_Nodes_Topologia(i);

                //Verifica se não houve erro.
                if (Resultado.StatusCode != ResultCode.SS_OK)
                    break;
            }

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Método responsável por configurar o Media Sink(Dissipador/Decoder) para o fluxo selecionado e conectar o nó de entra ao de saída.
        /// </summary>
        /// <param name="Param_Id">O ID do fluxo a ser criado o Media Sink adequado.</param>
        /// <returns></returns>
        public CarenResult Configurar_Nodes_Topologia(uint Param_Id)
        {
            //Variavel que vai retornar o resultado da operação.
            CarenResult Resultado = ResultCode.SS_OK;

            //Variaveis utilizadas.
            ICarenMFStreamDescriptor OutStreamIdDescriptor = null;
            ICarenMFActivate OutSinkActivator = null;
            ICarenMFTopologyNode OutSourceNode = null;
            ICarenMFTopologyNode OutOutputNode = null;

            //Recupera a interface para o descritor do fluxo no id.
            Resultado = myMediaSession.DescritorMidia.GetStreamDescriptorByIndex(Param_Id, out bool OutSelecionado, out OutStreamIdDescriptor);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar obter o descritor de fluxo para a midia carregada!", true);

                //Sai do método.
                goto Done;
            }

            //Verifica se está selecionado e configura.
            if(!OutSelecionado)
            {
                //Não está selecionado..

                //Sai do método
                goto Done;
            }

            //Cria um ativador para o media sink
            CreateMediaSinkByStream(OutStreamIdDescriptor, out OutSinkActivator);

            //Cria e adiciona o nó de entrada.
            CreateSourceNodeToTopology(OutStreamIdDescriptor, out OutSourceNode);

            //Cria e adiciona o nó de saida.
            CreateOutputNodeToTopology(OutSinkActivator, out OutOutputNode);

            //Conecta o nó de entrada ao nó de saida.
            Resultado = OutSourceNode.ConnectOutput(0, OutOutputNode, 0);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar conectar o nó de entrada ao nó de saida!", true);

                //Sai do método.
                goto Done;
            }

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Cria um Ativador para o Media Sink apropriado com base no descritor de fluxo. O ativador pode ser um (SAR - Streaming Audio Render) ou o EVR(Enhanced Video Renderer)
        /// </summary>
        /// <param name="Param_StreamDesc">O descritor do fluxo a ter o ativador de midia criado.</param>
        /// <param name="OutAtivador">Retorna o ativador de midia apropriado para o descritor de midia informado.</param>
        /// <returns></returns>
        public CarenResult CreateMediaSinkByStream(ICarenMFStreamDescriptor Param_StreamDesc, out ICarenMFActivate Param_OutAtivador)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Variaveis utilizadas.
            ICarenMFMediaTypeHandler MediaTypeHandler = null;
            Param_OutAtivador = null;

            //Recupera o type handler para o descritor de fluxo.
            Resultado = Param_StreamDesc.GetMediaTypeHandler(out MediaTypeHandler);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recuperar o Type Handler para o descritor de fluxo informado.", true);

                //Sai do método.
                goto Done;
            }

            //Obtém o tipo principal da midia 
            Resultado = MediaTypeHandler.GetMajorType(out _, out CA_MAJOR_MEDIA_TYPES OutTipoPrincipal);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recupera o tipo principal da midia no desctitor de fluxo.", true);

                //Sai do método.
                goto Done;
            }

            //Verifica o tipo principal da midia e cria o ativador com base no valor.
            if(OutTipoPrincipal == CA_MAJOR_MEDIA_TYPES.TP_Audio)
            {
                //Cria um ativador para o media sink do SAR.
                Resultado = MFTFuncs._MFCreateAudioRendererActivate(Param_OutAtivador = new CarenMFActivate());

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Falhou ao realizar a operação.

                    //Chama uma mensagem de erro.
                    ShowMensagem("Ocorreu uma falha ao tentar criar o SAR.", true);

                    //Sai do método.
                    goto Done;
                }
            }
            else if (OutTipoPrincipal == CA_MAJOR_MEDIA_TYPES.TP_Video)
            {
                //Cria um ativador para o media sink do EVR.
                Resultado = MFTFuncs._MFCreateVideoRendererActivate(myMediaSession.HandleVideoPlayback, Param_OutAtivador = new CarenMFActivate());

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Falhou ao realizar a operação.

                    //Chama uma mensagem de erro.
                    ShowMensagem("Ocorreu uma falha ao tentar criar o EVR.", true);

                    //Sai do método.
                    goto Done;
                }
            }
            else
            {
                //Chama uma mensagem de erro.
                ShowMensagem("O tipo do fluxo principal não é suportado!!", true);

                //Sai do método.
                goto Done;
            }

        Done:;
            //Libera as interfaces.
            SafeReleaseInterface(MediaTypeHandler);

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Cria o Source Node(Nó de entrada) para um determinado fluxo no arquivo a ser renderizado.
        /// </summary>
        /// <param name="Param_StreamDesc">O Descritor para o fluxo no arquivo carregado.</param>
        /// <param name="Param_OutNode">Retorna uma interface para o nó de entrada.</param>
        /// <returns></returns>
        public CarenResult CreateSourceNodeToTopology(ICarenMFStreamDescriptor Param_StreamDesc, out ICarenMFTopologyNode Param_OutNode)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Cria o nó de origem.
            Param_OutNode = new CarenMFTopologyNode(CA_MF_TOPOLOGY_TYPE.MF_TOPOLOGY_SOURCESTREAM_NODE);

            //Define os atributos no nó.
            Param_OutNode.SetUnknown(GUIDs_MFAttributes_TopologyNode.MF_TOPONODE_SOURCE, myMediaSession.SourceMidia);
            Param_OutNode.SetUnknown(GUIDs_MFAttributes_TopologyNode.MF_TOPONODE_PRESENTATION_DESCRIPTOR, myMediaSession.DescritorMidia);
            Param_OutNode.SetUnknown(GUIDs_MFAttributes_TopologyNode.MF_TOPONODE_STREAM_DESCRIPTOR, Param_StreamDesc);

            //Adiciona o nó a topologia.
            Resultado = myMediaSession.Topologia.AddNode(Param_OutNode);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar adicionar o nó de origem a topologia.", true);

                //Sai do método.
                goto Done;
            }

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Cria o Output Node(Nó de saída), node responsável pelo codificador de audio ou video para o fluxo no arquivo carregado.
        /// </summary>
        /// <param name="Param_Sink">Uma interface de ativação para um Media Sink(Dissipador/Decoder) que representa o SAR(Áudio) ou o EVR(Vídeo).</param>
        /// <param name="Param_OutNode">Retorna uma interface para o nó de saída.</param>
        /// <returns></returns>
        public CarenResult CreateOutputNodeToTopology(ICarenMFActivate Param_Sink, out ICarenMFTopologyNode Param_OutNode)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Cria o nó de destino.
            Param_OutNode = new CarenMFTopologyNode(CA_MF_TOPOLOGY_TYPE.MF_TOPOLOGY_OUTPUT_NODE);

            //Adiciona o Sink ao nó
            Resultado = Param_OutNode.SetObject(Param_Sink);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar adicionar o Sink ao nó de saida!", true);

                //Sai do método.
                goto Done;
            }

            //Adiciona o nó a topologia.
            Resultado = myMediaSession.Topologia.AddNode(Param_OutNode);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar adicionar o nó de saida a topologia.", true);

                //Sai do método.
                goto Done;
            }

            //Informa um atributo que indica que a Media Session para não desligar o objeto que pertence a este nó de topologia.
            Resultado = Param_OutNode.SetUINT32(GUIDs_MFAttributes_TopologyNode.MF_TOPONODE_NOSHUTDOWN_ON_REMOVE, 1); // 1 - TRUE | 0 - FALSE

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Método responsável por recuperar as interfaces de controle da midia(Audio, Video).
        /// </summary>
        /// <returns></returns>
        public CarenResult ObterInterfacesControle()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Recupera a interface de controle da Audio 
            Resultado = MFTFuncs._MFGetService(myMediaSession.MediaSession, GUIDs_MF_SERVICE_INTERFACES.MR_POLICY_VOLUME_SERVICE, GUIDs_InterfacesMediaFoundation.IID_IMFSimpleAudioVolume, myMediaSession.AudioVolumePlayback = new CarenMFSimpleAudioVolume());

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recuperar a interface de controle de volume!", true);

                //Sai do método.
                goto Done;
            }

            //Recupera a interface de controle de vídeo.
            Resultado = MFTFuncs._MFGetService(myMediaSession.MediaSession, GUIDs_MF_SERVICE_INTERFACES.MR_VIDEO_RENDER_SERVICE, GUIDs_InterfacesMediaFoundation.IID_IMFVideoDisplayControl, myMediaSession.DisplayPlaybackControl = new CarenMFVideoDisplayControl());

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recupera a interface de controle de video!", true);

                //Sai do método.
                goto Done;
            }

            //Recupera o relogio Associado.
            Resultado = myMediaSession.MediaSession.GetClock(out myMediaSession.Relogio);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recupera o relogio associado a reprodução!", true);

                //Sai do método.
                goto Done;
            }

            //Obtém o relogio de apresentação.
            myMediaSession.Relogio.ConsultarInterface(GUIDs_InterfacesMediaFoundation.IID_IMFPresentationClock, myMediaSession.RelogioApresentacao = new CarenMFPresentationClock(false));

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar recupera o relogio de apresentação da mídia!", true);

                //Sai do método.
                goto Done;
            }

        Done:;

            //Retorna o resultado.
            return Resultado;
        }
        #endregion

        #region Métodos de processamento dos eventos da Media Session
        private void ProcessarEventoMediaSession(CA_MediaEventType Param_EventType, ref ICarenMFMediaEvent Param_Event)
        {
            //Variaveis
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Verifica o tipo do evento.
            switch (Param_EventType)
            {
                case CA_MediaEventType.MEUnknown:
                    break;
                case CA_MediaEventType.MEError:
                    break;
                case CA_MediaEventType.MEExtendedType:
                    break;
                case CA_MediaEventType.MENonFatalError:
                    break;
                case CA_MediaEventType.MESessionUnknown:
                    break;
                case CA_MediaEventType.MESessionTopologySet:
                    break;
                case CA_MediaEventType.MESessionTopologiesCleared:
                    break;
                case CA_MediaEventType.MESessionStarted:
                    //Define que está renderizando.
                    StatusPlayback = StatusRendering.Rendering;
                    break;
                case CA_MediaEventType.MESessionPaused:
                    //Define que está pausado.
                    StatusPlayback = StatusRendering.Paused;
                    break;
                case CA_MediaEventType.MESessionStopped:
                    //Define que a sessão de mídia foi parada.
                    StatusPlayback = StatusRendering.Stoped;

                    //Chama o método para fechar a Media Session.
                    Resultado = myMediaSession.MediaSession.Close();

                    //Verifica se não houve erro
                    if (Resultado.StatusCode != ResultCode.SS_OK)
                    {
                        //Falhou ao realizar a operação.

                        //Chama uma mensagem de erro.
                        ShowMensagem("Ocorreu uma falha ao tentar fechar a Media Session.", true);
                    }
                    break;
                case CA_MediaEventType.MESessionClosed:
                    //Define que a media session foi fechada.
                    StatusPlayback = StatusRendering.Closed;

                    //Chama o método para concluir a liberação de todas as interfaces.
                    LiberarInterfaces();
                    break;
                case CA_MediaEventType.MESessionEnded:
                    break;
                case CA_MediaEventType.MESessionRateChanged:
                    break;
                case CA_MediaEventType.MESessionScrubSampleComplete:
                    break;
                case CA_MediaEventType.MESessionCapabilitiesChanged:
                    break;
                case CA_MediaEventType.MESessionTopologyStatus:
                    {
                        //Variaveis utilizadas.
                        CA_MF_TOPOSTATUS OutStatusTopology = CA_MF_TOPOSTATUS.MF_TOPOSTATUS_INVALID;

                        //Obtém o atributo que indica o status da topologia no evento.
                        Resultado = Param_Event.GetUINT32(GUIDs_MFAttributes_Events.MF_EVENT_TOPOLOGY_STATUS, out uint OutStatus);

                        //Verifica se obteve sucesso na operação.
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                            goto Done;

                        //Converte o status
                        OutStatusTopology = (CA_MF_TOPOSTATUS)OutStatus;

                        //Verifica o status da topologia.
                        switch (OutStatusTopology)
                        {
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_INVALID:
                                //Topologia em estado invalido.
                                break;
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_READY:
                                //A topologia está pronta.

                                //Chama o método para recuperar as interfaces de serviços que seram utilizadas.
                                ObterInterfacesControle();

                                //Chama o método para iniciar a reprodução.
                                Resultado = myMediaSession.MediaSession.Start(null, new CA_PROPVARIANT() { vt = CA_VARTYPE.VT_EMPTY });

                                //Verifica se obteve sucesso.
                                if(Resultado.StatusCode != ResultCode.SS_OK)
                                {
                                    //Ocorreu uma falha ao tentar iniciar a reprodução da midia.

                                    //Chama uma mensagem de erro.
                                    ShowMensagem("Ocorreu uma falha ao tentar iniciar a reprodução da mídia!", true);

                                    //Sai do método
                                    goto Done;
                                }

                                break;
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_STARTED_SOURCE:
                                //A topologia começou a ler os dados.
                                break;
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_DYNAMIC_CHANGED:
                                break;
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_SINK_SWITCHED:
                                break;
                            case CA_MF_TOPOSTATUS.MF_TOPOSTATUS_ENDED:
                                //A topologia chegou ao fim.
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case CA_MediaEventType.MESessionNotifyPresentationTime:
                    break;
                case CA_MediaEventType.MESessionStreamSinkFormatChanged:
                    break;
                case CA_MediaEventType.MENewPresentation:
                    break;
                
                default:
                    break;
            }

        Done:;

            //Informa o evento gerado.
            Debug.WriteLine("Evento gerado: " + Param_EventType.ToString());
        }
        #endregion

        #region Métodos para obter informações sobre a renderização e controlar os dados.

        /// <summary>
        /// Retorna o tempo total da midia em unidades de 100 nanossegundos.
        /// </summary>
        /// <returns></returns>
        public UInt64 ObterTempoTotalMidia()
        {
            //Variavel a ser retornada.
            UInt64 TotalTimeRender = 0;

            //Obtém o tempo total da midia.
            CarenResult Resultado = myMediaSession.DescritorMidia.GetUINT64(GUIDs_MFAttributes_PresentationDescriptor.MF_PD_DURATION, out TotalTimeRender);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Define erro.
                TotalTimeRender = 0;
            }

            //Retorna o resultado.
            return TotalTimeRender;
        }

        /// <summary>
        /// Retorna o tempo atual de reprodução em unidades de 100 nanossegundos.
        /// </summary>
        /// <returns></returns>
        public Int64 ObterPosicaoRelogioApresentacao()
        {
            //Variavel a ser retornada.
            Int64 CurrentPosition = 0;

            //Chama o método para recuperar o tempo atual de reprodução.
            CarenResult Resultado = myMediaSession.RelogioApresentacao.GetTime(out CurrentPosition);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Define erro.
                CurrentPosition = -1;
            }

            //Retorna o resultado
            return CurrentPosition;
        }

        /// <summary>
        /// Define uma nova posição de reprodução da midia.
        /// </summary>
        /// <param name="Param_NovaPosition">O valor da nova posição de reprodução em unidades de 100 nanossegundos.</param>
        /// <returns></returns>
        public CarenResult DefinirNovaPosicaoReproducao(Int64 Param_NovaPosition)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Variaveis
            CA_PROPVARIANT PropVar = new CA_PROPVARIANT() { vt = CA_VARTYPE.VT_I8, hVal = new CA_LARGE_INTEGER() { QuadPart = Param_NovaPosition } };

            //Chama o método para definir a nova posição de reprodução.
            Resultado = myMediaSession.MediaSession.Start(null, PropVar);

            //Retorna o resultado.
            return Resultado;
        }
        #endregion

        #region Métodos Auxiliares
        public void ShowMensagem(String Mensagem, Boolean ErrorMsg = false)
        {
            MessageBox.Show(Mensagem, "Media Session Playback Test", MessageBoxButtons.OK, ErrorMsg ? MessageBoxIcon.Error : MessageBoxIcon.Information);
        }

        public void SafeReleaseInterface(ICaren Param_Base)
        {
            //Verifica se a interface é valida.
            if (Param_Base is not null)
            {
                //Verifica se é valido e libera o ponteiro.
                if (Param_Base.StatusPonteiro().StatusCode == ResultCode.SS_OK)
                    Param_Base.LiberarReferencia();

                //Chama o finalizador.
                Param_Base.Finalizar();
            }
        }

        public void LiberarInterfaces()
        {
            //Libera as interfaces de callback.
            SafeReleaseInterface(myMediaSession.CallbackMediaSession);
            SafeReleaseInterface(myMediaSession.CallbackCreateMediaSource);

            //Verifica se a fonte de midia é valida ainda e libera seus dados.
            if (myMediaSession.MediaSession is not null & myMediaSession.MediaSession.StatusPonteiro().StatusCode == ResultCode.SS_OK)
            {
                //Libera as interfaces auxiliares.
                SafeReleaseInterface(myMediaSession.AudioVolumePlayback);
                SafeReleaseInterface(myMediaSession.DisplayPlaybackControl);
                SafeReleaseInterface(myMediaSession.RelogioApresentacao);
                SafeReleaseInterface(myMediaSession.Relogio);
                SafeReleaseInterface(myMediaSession.DescritorMidia);
                SafeReleaseInterface(myMediaSession.Topologia);

                //Limpa a topologia da media session.
                myMediaSession.MediaSession.ClearTopologies();

                //Verifica se a Media Session chamou o Metodo Close, se não vai chamar.
                if (StatusPlayback != StatusRendering.Closed)
                    myMediaSession.MediaSession.Close();

                //Chama o shutdown na media session.
                myMediaSession.MediaSession.Shutdown();

                //Libera seu ponteiro.
                SafeReleaseInterface(myMediaSession.MediaSession);
            }

            //Libera a fonte de midia utilizada pela Media Session
            if(myMediaSession.SourceMidia is not null & myMediaSession.SourceMidia.StatusPonteiro().StatusCode == ResultCode.SS_OK)
            {
                //Desliga a fonte de midia.
                myMediaSession.SourceMidia.Shutdown();

                //Libera seu ponteiro.
                SafeReleaseInterface(myMediaSession.SourceMidia);
            }

            //Libera o restante das interfaces.
            SafeReleaseInterface(myMediaSession.ResolvedorMidia);

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

        }
        #endregion

        #region Eventos das interfaces de Caren.

        //Media Session Callback

        private CarenResult CallbackMediaSession_OnInvoke(ICarenMFAsyncResult Param_AsyncResult)
        {
            //Variavel que vai ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Variaveis utilizadas.
            ICarenMFMediaEvent OutEvent = null;
            CA_MediaEventType OutEventType = CA_MediaEventType.MEUnknown;

            //Obtém o evento gerado.
            Resultado = myMediaSession.MediaSession.EndGetEvent(Param_AsyncResult, out OutEvent);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar obter o evento da media session!", true);

                //Sai do método.
                goto Done;
            }

            //Obtém o tipo do evento.
            Resultado = OutEvent.GetType(out OutEventType);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar obter o tipo do evento da media session!", true);

                //Sai do método.
                goto Done;
            }

            //Chama o método para processar o evento
            ProcessarEventoMediaSession(OutEventType, ref OutEvent);

            //Verifica se a media session não foi fechada antes de requisitar o proximo evento.
            if (StatusPlayback != StatusRendering.Closed)
            {
                //Chama o proximo evento na lista.
                Resultado = myMediaSession.MediaSession.BeginGetEvent(myMediaSession.CallbackMediaSession, null);

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Falhou ao realizar a operação.

                    //Chama uma mensagem de erro.
                    ShowMensagem("Ocorreu uma falha ao tentar solicitar o proximo evento assincrona da Media Session!", true);

                    //Sai do método.
                    goto Done;
                }
            }

        Done:;
            //Libera o ponteiro para o evento.
            SafeReleaseInterface(OutEvent);

            //Retorna o resultado.
            return Resultado;
        }
        private CarenResult CallbackMediaSession_OnGetParameters(ref CA_MFASYNC_BEHAVIOR Param_Flags, ref CA_MFASYNC_CALLBACK_QUEUE Param_Queue)
        {
            Param_Flags = CA_MFASYNC_BEHAVIOR.Zero;
            Param_Queue = CA_MFASYNC_CALLBACK_QUEUE.CA_MFASYNC_CALLBACK_QUEUE_MULTITHREADED;

            return ResultCode.SS_OK;
        }


        //Source Resolver Callback

        private CarenResult CallbackCreateMediaSource_OnInvoke(ICarenMFAsyncResult Param_AsyncResult)
        {
            //Variavel que vai ser retornada.
            CarenResult Resultado = ResultCode.SS_OK;

            //Variaveis utilizadas.
            CA_MF_OBJECT_TYPE OutTypeObject = CA_MF_OBJECT_TYPE.MF_OBJECT_INVALID;

            //Conclui a operação assincrona.
            Resultado = myMediaSession.ResolvedorMidia.EndCreateObjectFromURL(Param_AsyncResult, out OutTypeObject, myMediaSession.SourceMidia = new CarenMFMediaSource());

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar concluir a operação assincrona de criação da mídia!", true);

                //Sai do método.
                goto Done;
            }

            //Cria o Presentation Source.
            Resultado = myMediaSession.SourceMidia.CreatePresentationDescriptor(out myMediaSession.DescritorMidia);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha criar o descritor de apresetação para a mídia carregada!", true);

                //Sai do método.
                goto Done;
            }

            //Obtém a quantidade de stream no media source.
            Resultado = myMediaSession.DescritorMidia.GetStreamDescriptorCount(out myMediaSession.TotalStreamMediaSource);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao obter a quantidade de fluxos na mídia carregada!", true);

                //Sai do método.
                goto Done;
            }

            //Chama o método para criar e configurar a topologia
            ConfigurarTopologia();

            //Define a topologia na Sessao da mídia.
            Resultado = myMediaSession.MediaSession.SetTopology(CA_MFSESSION_SETTOPOLOGY_FLAGS.Zero, myMediaSession.Topologia);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao definir a topologia na sessao de mídia!", true);

                //Sai do método.
                goto Done;
            }

            //Obtém o tempo total da mídia.
            myMediaSession.TotalTimeMidiaNs = ObterTempoTotalMidia();
            myMediaSession.TotalTimeMidiaSegundos = myMediaSession.TotalTimeMidiaNs / REFTIME_1_SEGUNDO;

        Done:;
            //Retorna o resultado.
            return Resultado;
        }
        private CarenResult CallbackCreateMediaSource_OnGetParameters(ref CA_MFASYNC_BEHAVIOR Param_Flags, ref CA_MFASYNC_CALLBACK_QUEUE Param_Queue)
        {
            Param_Flags = CA_MFASYNC_BEHAVIOR.Zero;
            Param_Queue = CA_MFASYNC_CALLBACK_QUEUE.CA_MFASYNC_CALLBACK_QUEUE_MULTITHREADED;

            return ResultCode.SS_OK;
        }

        #endregion

        #region Eventos dos controles do formulario.
        private void TrackBarVolume_ValueChanged(object sender, EventArgs e)
        {
            //Sincroniza o acesso ao controle de volume.
            lock (Obj_SyncVolume)
            {
                //Verifica se o controle de volume é valido.
                if (myMediaSession.AudioVolumePlayback is not null && myMediaSession.AudioVolumePlayback.StatusPonteiro().StatusCode == ResultCode.SS_OK)
                    myMediaSession.AudioVolumePlayback.SetMasterVolume((TrackBarVolume.Value == 0? 0.0f: ( (float)(TrackBarVolume.Value) / TrackBarVolume.Maximum) )); //Define o nivel de volume maximo. O valor vai de (0.0 A 1.0)
            }
        }

        private void PanelRender_SizeChanged(object sender, EventArgs e)
        {
            //Sincroniza o acesso.
            lock (Obj_SyncVideoPos)
            {
                //Verifica se o vídeo está sendo reproduzido antes de realizar a operação.
                if (StatusPlayback == StatusRendering.Rendering)
                {
                    //Pausa a Media Session.
                    myMediaSession.MediaSession.Pause();

                    //Define a nova posicação dos retangulos do video.
                    CarenResult Resultado = myMediaSession.DisplayPlaybackControl.SetVideoPosition(new CA_MFVideoNormalizedRect() { right = 1, bottom = 1 }, new CA_RECT() { Rigth = PanelRender.Width, Left = 0, Bottom = PanelRender.Height, Top = 0 });

                    //Repinta a superfice.
                    myMediaSession.DisplayPlaybackControl.RepaintSuperfice();

                    //Inicia novamente a media session.
                    myMediaSession.MediaSession.Start(null, new CA_PROPVARIANT() { vt = CA_VARTYPE.VT_EMPTY });
                }
            }
        }

        private void PanelRender_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (PanelControlPlayback.Visible)
                PanelControlPlayback.Visible = false;
            else
                PanelControlPlayback.Visible = true;
        }

        private void MediaSessionPlayback_Load(object sender, EventArgs e)
        {

        }

        private void Btn_Start_Click(object sender, EventArgs e)
        {
            if (StatusPlayback == StatusRendering.NoStarted)
            {
                //Inicia o processo para configurar a reprodução.
                IniciarConfiguração();
            }
            else if (StatusPlayback == StatusRendering.Paused)
            {
                //Inicia novamente a reprodução do ponto que parou..
                //O Guid nulo e o vt como VT_EMPTY especificam que deve iniciar do ponto que parou ou do inicio.
                myMediaSession.MediaSession.Start(null, new CA_PROPVARIANT() { vt = CA_VARTYPE.VT_EMPTY });
            }
            else
            {

            }
        }

        private void Btn_Pause_Click(object sender, EventArgs e)
        {
            if (StatusPlayback == StatusRendering.Rendering & StatusPlayback != StatusRendering.NoStarted)
            {
                //Chama o método para pausar a reprodução.
                CarenResult Resultado = myMediaSession.MediaSession.Pause();

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Falhou ao realizar a operação.

                    //Chama uma mensagem de erro.
                    ShowMensagem("Ocorreu uma falha ao tentar pausar a reprodução atual!", true);
                }
            }
        }

        private void Btn_Stop_Click(object sender, EventArgs e)
        {
            if (StatusPlayback == StatusRendering.Rendering & StatusPlayback != StatusRendering.NoStarted)
            {
                //Chama o método para pausar a reprodução.
                CarenResult Resultado = myMediaSession.MediaSession.Stop();

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Falhou ao realizar a operação.

                    //Chama uma mensagem de erro.
                    ShowMensagem("Ocorreu uma falha ao tentar parar a reprodução atual!", true);
                }
            }
        }

        private void Btn_Advance_Click(object sender, EventArgs e)
        {
            long SecondsAdvance = (long)REFTIME_1_SEGUNDO * 60;
            long CurrentPos = ObterPosicaoRelogioApresentacao();
            long NewPos = CurrentPos + SecondsAdvance;
            DefinirNovaPosicaoReproducao(NewPos);
        }

        private void Btn_Back_Click(object sender, EventArgs e)
        {
            long SecondsBack = (long)REFTIME_1_SEGUNDO * 30;
            long CurrentPos = ObterPosicaoRelogioApresentacao();
            long NewPos = (CurrentPos - SecondsBack) < 0 ? 0 : CurrentPos - SecondsBack;
            DefinirNovaPosicaoReproducao(NewPos);
        }
        #endregion
    }
}
