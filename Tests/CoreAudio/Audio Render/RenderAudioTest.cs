using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Importa os namespaces base.
using CarenRengine;
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.Constantes;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.Estruturas;
using CarenRengine.SDKBase.GUIDs;

//Importa o namespace de resultados.
using CarenRengine.CarenCodesStatus;

//Importa o SDK da CoreAudio.
using CarenRengine.CoreAudio;

//Importa o SDK da Media Foundation para ler amostras.
using CarenRengine.MediaFoundation;
using CarenRengine.MediaFoundationExtended;

namespace CoreAudio_RenderAudioTest
{
    public partial class RenderAudioTest : Form
    {
        public RenderAudioTest()
        {
            InitializeComponent();
        }

        #region Estruturas   
        public struct MyAudioInterfacesRender
        {
            public ICarenMFSourceReaderExtend LeitorAmostras { get; set; }

            public ICarenMFSourceReaderCallback CallbackReadSamples { get; set; }

            public ICarenMFAttributes AtributosLeitor { get; set; }

            public ICarenMFMediaType AudioTypeSupportedRenderComplete { get; set; }

            public ICarenMFMediaType AudioTypeSupportedRenderPartial { get; set; }

            public ICarenMMDevice DefaultAudioOutput { get; set; }

            public ICarenMMDeviceEnumerator EnumeradorAudioDevices { get; set; }

            public ICarenAudioClient AudioClientOutputConfig { get; set; }

            public ICarenAudioRenderClient AudioRenderShared { get; set; }

            public ICarenSimpleAudioVolume AudioVolumeControl { get; set; }

            public CA_WAVEFORMATEXEXTENSIBLE WavAudioOutputInfo { get; set; }

            public WindowsFunctions WinFuncs { get; set; }

            public MediaFoundationFunctions MFTFuncs { get; set; }

            public long FrequencyComputer { get; set; }

            public Guid GuidAudioSession { get; set; }
        }

        public struct MyBufferAudioData
        {
            public long TimeStampRender;

            public ICarenMFSample AudioSample;

            public ICarenMFMediaBuffer MediaBuffer;

            public ICarenBuffer BufferNativo;           
        }
        #endregion

        #region Constantes
        const uint REFTIMES_PER_SEC = 10000000;

        const uint SIZE_LIST_BUFFER = 10;
        #endregion

        #region Variaveis
        public MyAudioInterfacesRender MyRenderAudioTest = new MyAudioInterfacesRender();

        public List<MyBufferAudioData> ListBuffer { get; set; }

        public Task TaskRenderData { get; set; }

        public Task TaskSamplesGet { get; set; }

        public Boolean StatusRequisicaoAmostra { get; set; } = false;

        public Boolean ProcessandoAmostras { get; set; } = false;
        #endregion

        public CarenResult ConfigurarBase()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Cria as classes necessárias.
            MyRenderAudioTest.WinFuncs = new WindowsFunctions();
            MyRenderAudioTest.MFTFuncs = new MediaFoundationFunctions();
            MyRenderAudioTest.AtributosLeitor = new CarenMFAttributes(1);
            MyRenderAudioTest.EnumeradorAudioDevices = new CarenMMDeviceEnumerator(CA_CLSCTX.CLSCTX_INPROC_SERVER);
            MyRenderAudioTest.GuidAudioSession = Guid.NewGuid();

            //Inicia a plataforma da Media Foundation
            MyRenderAudioTest.MFTFuncs._MFStartup();

            //Modifica o tempo minimo que o sistema fica em espera por uma chamada (Sleep).
            MyRenderAudioTest.WinFuncs.CA_TimeBeginPeriod(5);

            //Obtém a frequencia atual do computador.
            MyRenderAudioTest.WinFuncs.CA_QueryPerformanceFrequency(out long OutFrequency);

            //Obtém o dispositivo default de saida de audio do computador atual.
            Resultado = MyRenderAudioTest.EnumeradorAudioDevices.GetDefaultAudioEndpoint(CA_EDataFlow.eRender, CA_ERole.eMultimedia, out ICarenMMDevice OutDevice);

            //Verifica se não houve erro
            if(Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o dispositivo de saida de audio padrao. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult));

                //Sai do método
                goto Done;
            }

            //Define a interface criada na estrutura.
            MyRenderAudioTest.DefaultAudioOutput = OutDevice;
            MyRenderAudioTest.DefaultAudioOutput.AdicionarReferencia();

            //Libera o enumerador de dispositivos.
            MyRenderAudioTest.EnumeradorAudioDevices.LiberarReferencia();
            MyRenderAudioTest.EnumeradorAudioDevices = null;

            //Cria a interface que gerencia o dispositivo de audio e vai receber o ponteiro.
            MyRenderAudioTest.AudioClientOutputConfig = new CarenAudioClient();

            //Ativa o dispositivo de áudio para obter a interface ICarenAudioClient.
            Resultado = MyRenderAudioTest.DefaultAudioOutput.Activate(GUIDs_InterfacesWASAPI.IID_IAudioClient, CA_CLSCTX.CLSCTX_INPROC_SERVER, null, MyRenderAudioTest.AudioClientOutputConfig);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao ativar o dispositivo de saida de áudio de destino. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult));

                //Sai do método
                goto Done;
            }

            //Cria a interface que vai receber os eventos de leitura de amostras.
            MyRenderAudioTest.CallbackReadSamples = new CarenMFSourceReaderCallback(true);

            //Configura os eventos da interface.
            MyRenderAudioTest.CallbackReadSamples.OnReadSample += CallbackReadSamples_OnReadSample;
            MyRenderAudioTest.CallbackReadSamples.OnEvent += CallbackReadSamples_OnEvent;
            MyRenderAudioTest.CallbackReadSamples.OnFlush += CallbackReadSamples_OnFlush;

            //Registra os eventos internamente.
            MyRenderAudioTest.CallbackReadSamples.RegistrarCallback();

            //Define a interface de eventos criada na interface de abributos que será usada para criar o leitor de amostras.
            Resultado = MyRenderAudioTest.AtributosLeitor.SetUnknown(GUIDs_MFAtributos_SourceReader.MF_SOURCE_READER_ASYNC_CALLBACK, MyRenderAudioTest.CallbackReadSamples);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao definir a interface de eventos na lista de atributos do leitor. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult));

                //Sai do método
                goto Done;
            }

            //Cria o leitor de amostras com a interface de atributos criada e a url para a musica.
            MyRenderAudioTest.LeitorAmostras = new CarenMFSourceReader
                (Txb_UrlMusic.Text, MyRenderAudioTest.AtributosLeitor).As<ICarenMFSourceReaderExtend, CarenMFSourceReaderExtend>(null);

            //Verifica se não houve erro
            if(MyRenderAudioTest.LeitorAmostras is null)
            {
                //Mostra uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha ao tentar criar um leitor de mídia para a url informada.");

                //Define erro.
                Resultado.AdicionarCodigo(ResultCode.ER_FAIL, false);

                //Sai do método
                goto Done;
            }

            //Define sucesso na operção
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;

            //Retorna o resultado das operações.
            return Resultado;
        }

        public CarenResult ConfigurarCoreAudio()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Obtém o formato de áudio suportado nativamente pelo dispositivo de audio de saida.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.GetMixFormat(out CA_WAVEFORMATEXEXTENSIBLE OutSupportedData);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o tipo de mídia nativa suportado pelo dispositivo de saida de áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define a estrutura na propriedade.
            MyRenderAudioTest.WavAudioOutputInfo = OutSupportedData;

            //Inicia a interface de tipo de mídia que vai receber os dados.
            MyRenderAudioTest.AudioTypeSupportedRenderPartial = new CarenMFMediaType(true);

            //Converte os dados da estrutura Wav para uma interface ICarenMFMediaType.
            Resultado = MyRenderAudioTest.MFTFuncs.CA_MFInitMediaTypeFromWaveFormatEx(
                ref OutSupportedData,
                OutSupportedData.TamanhoEstrutura,
                MyRenderAudioTest.AudioTypeSupportedRenderPartial);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Não foi possivel criar um tipo de mídia para o tipo pedido pelo dispositivo de saida de áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Inicia o dispostivo de saida de áudio no modo compartilhado.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.Initialize(
                CA_AUDIOCLIENTE_SHAREMODE.AUDCLNT_SHAREMODE_SHARED, //Modo de reprodução (Acesso ao buffer de audio)
                0,
                REFTIMES_PER_SEC, //DURAÇÃO DO BUFFER DE ÁUDIO.
                0,
                ref OutSupportedData, //Tipo dos dados de áudio a serem recebidos.
                MyRenderAudioTest.GuidAudioSession.ToString());

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar iniciar o dispositivo de saida de áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Cria a interface de renderização para receber o ponteiro.
            MyRenderAudioTest.AudioRenderShared = new CarenAudioRenderClient();

            //Recupera a interface de serviço responsável pela renderização de audio.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.GetService(
                GUIDs_InterfacesWASAPI.IID_IAudioRenderClient, 
                MyRenderAudioTest.AudioRenderShared);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a interface de renderização de dados de áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Cria a interface de controle de áudio para receber o ponteiro.
            MyRenderAudioTest.AudioVolumeControl = new CarenSimpleAudioVolume();

            //Recupera a interface de serviço responsável pelo controle de áudio.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.GetService(
                GUIDs_InterfacesWASAPI.IID_ISimpleAudioVolume, 
                MyRenderAudioTest.AudioVolumeControl);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a interface responsável pelo controle de áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;

            //Retorna o resultado das operações.
            return Resultado;
        }

        public CarenResult ConfigurarLeitor()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Desseleciona todos os fluxos que estiverem selecionados.
            MyRenderAudioTest.LeitorAmostras.SetStreamSelection(CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_ALL_STREAMS, false);

            //Define o tipo de midia de saida convertido da estrutura Wav para uma interface ICarenMFMediaType.
            Resultado = MyRenderAudioTest.LeitorAmostras.SetCurrentMediaType(
                CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, //Define o ID do primeiro fluxo de audio.
                0, //Valor reservado.
                MyRenderAudioTest.AudioTypeSupportedRenderPartial //O tipo partial convertido da estrutura.
                );
            
            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Não foi possivel configurar o tipo de midia de saida. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Obtém o tipo completo definido pelo leitor de amostras.
            Resultado = MyRenderAudioTest.LeitorAmostras.GetCurrentMediaType(
                CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, //Define o ID do primeiro fluxo de audio.
                out ICarenMFMediaType OutCompleteMediaType //Retorba i tipo completo.
                );

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Não foi possivel obter o tipo completo de mídia. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define o tipo completo na estrutura.
            MyRenderAudioTest.AudioTypeSupportedRenderComplete = OutCompleteMediaType;

            //Define o fluxo do arquivo de mídia que será processado pelo leitor.
            Resultado = MyRenderAudioTest.LeitorAmostras.SetStreamSelection(CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, true);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Não foi possivel selecionar o fluxo de mídia a ser renderizada a parti do leitor. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;

            //Retorna o resultado das operações.
            return Resultado;
        }

        private void IniciarGerenciadorAmostras()
        {
            //Cria a lista que vai conter os buffer de audio.
            ListBuffer = new List<MyBufferAudioData>(SIZE_LIST_BUFFER);

            //Define o status da requisição de amostras para false.
            StatusRequisicaoAmostra = false;

            //Cria a task que vai ficar requisitando as amostras.
            TaskSamplesGet = new Task(async () => 
            {
                //Define que está processando as amostras.
                ProcessandoAmostras = true;

                //Abre um laço que vai ficar requisitando as amostras ao leitor.
                while (ProcessandoAmostras)
                {

                }
            });

            //Inicia a task.
            TaskSamplesGet.Start();
        }

        private void RenderizarAudio()
        {
            //Cria a task responsável pela renderização dos dados.
            TaskRenderData = new Task(async () =>
            {

            });

            //Inicia a task.
            TaskRenderData.Start();
        }

        public CarenResult Iniciar()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);



        Done:;

            //Retorna o resultado das operações.
            return Resultado;
        }

        #region Eventos
        private void CallbackReadSamples_OnReadSample(int Param_HResult, ResultCode Param_ResultadoGeral, CA_SAMPLE_READ_RESULT Param_ResultadoLeitura, CA_MF_SOURCE_READER_FLAG Param_FlagsLeituraAmostra, uint Param_IdFluxo, ulong Param_TimeSpan, ICarenMFSample Param_Amostra)
        {
            throw new NotImplementedException();
        }

        private void CallbackReadSamples_OnFlush(uint Param_FluxoID)
        {
            throw new NotImplementedException();
        }

        private void CallbackReadSamples_OnEvent(uint Param_FluxoID, ICarenMFMediaEvent Param_CarenMidiaEvent)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Utilidades
        public void ShowMensagem(String Mensagem, Boolean ErrorMsg = false)
        {
            MessageBox.Show(Mensagem, "Audio Render Test", MessageBoxButtons.OK, ErrorMsg? MessageBoxIcon.Error: MessageBoxIcon.Information);
        }

        public void ReleaseAllInterfaces()
        {
            try
            {

            }
            catch (Exception)
            {

            }
            finally
            {


                //Desliga a plataforma da media foundation.
                MyRenderAudioTest.MFTFuncs._MFShutdown();

                //Reseta o tempo minimo de espera do sistema.
                MyRenderAudioTest.WinFuncs.CA_TimeEndPeriod(5);
            }
        }
        #endregion




        private void Btn_PlayMusic_Click(object sender, EventArgs e)
        {
            //Verifica se a url é invalida.
            if (String.IsNullOrEmpty(Txb_UrlMusic.Text))
                throw new Exception("A URL para a musica deve ser informada!!");

            //Chama o método base para iniciar as configurações base.
            CarenResult Resultado = ConfigurarBase();

            //Vefifica se não falhou
            if (Resultado.StatusCode != ResultCode.SS_OK)
                goto Done; //Sai do método.

            //Chama o método para configurar a core audio.
            Resultado = ConfigurarCoreAudio();

            //Vefifica se não falhou
            if (Resultado.StatusCode != ResultCode.SS_OK)
                goto Done; //Sai do método.

            //Chama o método para configurar o leitor.
            Resultado = ConfigurarLeitor();

            //Vefifica se não falhou
            if (Resultado.StatusCode != ResultCode.SS_OK)
                goto Done; //Sai do método.




            Done:;
        }
    }
}
