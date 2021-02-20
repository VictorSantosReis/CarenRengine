using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Importa os SDKs base.
using CarenRengine;
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.Estruturas;
using CarenRengine.SDKBase.GUIDs;
using CarenRengine.CarenCodesStatus;

//Importa o SDK da Media Foundation.
using CarenRengine.MediaFoundation;
using System.Diagnostics;

namespace MediaSessionPlaybackTest
{
    public partial class MediaSessionPlayback : Form
    {
        public MediaSessionPlayback()
        {
            InitializeComponent();
        }

        #region Estruturas & Enumerações 
        private struct MysMediaSessionConfig
        {
            public ICarenMFSourceResolver ResolvedorMidia { get; set; }
            public ICarenMFMediaSource SourceMidia { get; set; }
            public ICarenMFTopology TopologiaCompleta { get; set; }
            public ICarenMFAsyncCallback CallbackMediaSession { get; set; }
            public ICarenMFAsyncCallback CallbackCreateMediaSource { get; set; }
            public ICarenMFMediaSession MediaSession { get; set; }

            public ICarenMFPresentationDescriptor DescritorMidia;
            public ICarenMFVideoDisplayControl DisplayPlaybackControl { get; set; }



            public UInt64 TotalTimeMidiaSegundos { get; set; }
            public UInt32 TotalStreamMediaSource;
            public String UrlMidia { get; set; }
            public IntPtr HandleVideoPlayback { get; set; }

        }
        #endregion

        #region Variaveis
        MysMediaSessionConfig myMediaSession = new MysMediaSessionConfig();

        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();
        #endregion


        #region Métodos de configuração
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

            //Define o callback na media session.
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
                new CarenParameterResolver<ICaren>(true),
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

        public CarenResult ConfigurarTopologia()
        {
            //Variavel que vai retornar o resultado da operação.
            CarenResult Resultado = ResultCode.SS_OK;

            //Cria a topologia
            myMediaSession.TopologiaCompleta = new CarenMFTopology(true);

            //Cria um for para criar os nós de topologia para os fluxos da midia carregada.
            for (uint i = 0; i < myMediaSession.TotalStreamMediaSource; i++)
            {
                //Chama o método para configurar os nós.
                Resultado = Configurar_Nodes_Topologia(i);
                if (Resultado.StatusCode != ResultCode.SS_OK)
                    break;
            }

            //Retorna o resultado.
            return Resultado;
        }

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
            Resultado = myMediaSession.TopologiaCompleta.AddNode(Param_OutNode);

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
            Resultado = myMediaSession.TopologiaCompleta.AddNode(Param_OutNode);

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

            //Verifica o tipo do evento.
            if(OutEventType == CA_MediaEventType.MESessionClosed)
            { }
            if (OutEventType == CA_MediaEventType.MESessionTopologyStatus)
            {
                Resultado = myMediaSession.MediaSession.Start(null, new CA_PROPVARIANT() { vt = CA_VARTYPE.VT_EMPTY });
            }
            else
            {
                //Obtém o proximo evento.
                myMediaSession.MediaSession.BeginGetEvent(myMediaSession.CallbackMediaSession, null);
            }

            //Informa o evento gerado.
            Debug.WriteLine("Evento gerado: " + OutEventType.ToString());

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
            Resultado = myMediaSession.MediaSession.SetTopology(CA_MFSESSION_SETTOPOLOGY_FLAGS.Zero, myMediaSession.TopologiaCompleta);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Falhou ao realizar a operação.

                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao definir a topologia na sessao de mídia!", true);

                //Sai do método.
                goto Done;
            }

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

        private void MediaSessionPlayback_Load(object sender, EventArgs e)
        {
           
        }

        private void Btn_Start_Click(object sender, EventArgs e)
        {
            IniciarConfiguração();
        }
    }
}
