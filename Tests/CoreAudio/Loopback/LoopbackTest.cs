using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

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

//Importa as APIs do Windows.
using CarenRengine.Windows;

namespace CoreAudio_LoopbackTest
{
    public partial class LoopbackTest : Form
    {
        //ESTE PROJETO TEM COMO INTUITO MOSTRAR COMO SE DESENVOLVER UM APLICATIVO PARA LER DADOS DE ÁUDIO DE UM DISPOSTIVO DE RENDERIZAÇÃO FINAL.
        //O PROJETO UTILIZA DE BUFFERS ORIENTADOS POR EVENTOS, O QUE EXCLUI CHAMADAS PARA (NEXTPACKETSIZE) OU A UTILIZAÇÃO DA FUNÇÃO SLEEP OU AWAIT.
        //ESTE PROJETO É SEMELHANTE AO PROJETO (AudioCaptureTest), APENAS COM ALGUMAS MODIFICAÇÕES MINIMAS PARA FUNCIONAR EM MODO (LOOPBACK).
        //COMO IGUAL AO (AudioCaptureTest), O ARQUIVO DEVE SAIDA DEVE SER UM (.WAV) OBRIGATORIAMENTE.



        public LoopbackTest()
        {
            InitializeComponent();
        }

        #region Estruturas
        public struct MyInterfacesForCaptureDevice
        {
            public ICarenMMDeviceEnumerator EnumeradorDispositivos { get; set; }

            public ICarenMMDeviceCollection ColecaoDispositivos { get; set; }

            public ICarenMMDevice DispositivoCaptura { get; set; }

            public ICarenAudioClient AudioClientConfig { get; set; }

            public ICarenAudioCaptureClient AudioCapture { get; set; }

            public ICarenSimpleAudioVolume AudioCaptureVolume { get; set; }

            public ICarenEvent WinEventBufferAudio { get; set; }

            public ICarenStream StreamFile { get; set; }

            public ICarenBuffer BufferCapturedAudio;

            public CA_WAVEFORMATEXEXTENSIBLE WavFormatCapture { get; set; }

            public uint CountDevicesCaptureCollection { get; set; }

            /// <summary>
            /// Propriedade que indica o tamanho de um unico frame de áudio em bytes.
            /// </summary>
            public uint FrameSize { get; set; }

            public uint BufferSizeInFames { get; set; }

            public uint TaskIndex { get; set; }

            public IntPtr HandleTaskPrioridade { get; set; }
        }

        public struct MyHeaderInfoFile
        {
            /// <summary>
            /// Variavel constante que contém o tamanho do header.
            /// </summary>
            public const ushort HeaderSize = 44;

            /// <summary>
            /// Varivel constante que contém o tamanho do subheader.
            /// </summary>
            public const uint SubChunkSize = 16;

            /// <summary>
            /// Variavel que contém o tamanho total do arquivo junto com o header.
            /// </summary>
            public static UInt32 TotalFileSize = 0;

            /// <summary>
            /// Total de dados de áudio capturados, em bytes.
            /// </summary>
            public static UInt64 TotalLenghtCaptured = 0;

            public static ushort FormatAudioData = 0;

            public static ushort Canais = 0;

            public static ulong BytesPerSec = 0;

            public static uint SampleRate = 0;

            public static ushort BlockAlign = 0;

            public static ushort BitsPerSample = 0;
        }
        #endregion

        #region Constantes
        public const int SIZE_INITIAL_BUFFER = 100;

        public const uint REFTIMES_PER_SEC = 10000000;

        public static String GUID_SESSION_AUDIO = Guid.NewGuid().ToString();
        #endregion

        #region Variaveis
        MyInterfacesForCaptureDevice myCaptureAudio = new MyInterfacesForCaptureDevice();

        List<ICarenBuffer> ListaBuffersAudio { get; set; }

        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();

        WindowsFunctions WinFuncs = new WindowsFunctions();

        Task Task_EscritorDados { get; set; }

        Task Task_ReadDataDispositivo { get; set; }

        Boolean StatusEscritorDados { get; set; } = false;

        Boolean StatusGeral { get; set; } = false;

        Boolean StatusCapturandoDados { get; set; } = false;

        readonly object SyncList = new object();
        #endregion



        #region Métodos que vão listar, configurar e capturar os dados.
        public CarenResult ObterDispositivosRenderizacao()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Cria o enumerador de dispositivos.
            myCaptureAudio.EnumeradorDispositivos = new CarenMMDeviceEnumerator(CA_CLSCTX.CLSCTX_INPROC_SERVER);

            //Cria a interface que vai conter a coleção de dispositivos.
            myCaptureAudio.ColecaoDispositivos = new CarenMMDeviceCollection();

            //Chama o método para obter todos os dispositivos de captura.
            Resultado = myCaptureAudio.EnumeradorDispositivos.EnumAudioEndpoints(CA_EDataFlow.eRender, CA_DEVICE_STATE_XXX.CA_DEVICE_STATE_ACTIVE, myCaptureAudio.ColecaoDispositivos);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao listar os dispositivos de captura disponiveis atualmente. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Obtém a quantidade de dispositivos disponiveis.
            Resultado = myCaptureAudio.ColecaoDispositivos.GetCount(out uint CountTotalDevices);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a quantidade de disponiveis de captura obtidos. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define na propriedade na estrutura
            myCaptureAudio.CountDevicesCaptureCollection = CountTotalDevices;

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        public CarenResult AtivarDispositivoRenderForLoopbackByIndex(uint Param_IdDevice)
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Tenta recuperar o dispositivo de captura indicado pelo id.
            Resultado = myCaptureAudio.ColecaoDispositivos.Item(Param_IdDevice, out ICarenMMDevice OutDeviceCapture);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o dispositivo de captura indicado pelo Id. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define o dispositivo de captura no membro da estrutura.
            myCaptureAudio.DispositivoCaptura = OutDeviceCapture;

            //Cria a interface que vai ser ativada.
            myCaptureAudio.AudioClientConfig = new CarenAudioClient();

            //Tenta ativar o dispositivo.
            Resultado = OutDeviceCapture.Activate(GUIDs_InterfacesWASAPI.IID_IAudioClient, CA_CLSCTX.CLSCTX_INPROC_SERVER, null, myCaptureAudio.AudioClientConfig);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar ativar o dispositivo selecionado. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Obtém o formato que o dispostivo de captura suporta
            Resultado = myCaptureAudio.AudioClientConfig.GetMixFormat(out CA_WAVEFORMATEXEXTENSIBLE OutWaveFormatCapture);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o tipo de dados suportado pelo dispositivo de captura. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define na estrutura.
            myCaptureAudio.WavFormatCapture = OutWaveFormatCapture;

            //Calcula os dados do formato do áudio e define nas estruturas.
            myCaptureAudio.FrameSize = (uint)(OutWaveFormatCapture.Format.wBitsPerSample * OutWaveFormatCapture.Format.nChannels / 8);
            MyHeaderInfoFile.Canais = OutWaveFormatCapture.Format.nChannels;
            MyHeaderInfoFile.BitsPerSample = OutWaveFormatCapture.Format.wBitsPerSample;
            MyHeaderInfoFile.SampleRate = OutWaveFormatCapture.Format.nSamplesPerSec;
            MyHeaderInfoFile.BytesPerSec = OutWaveFormatCapture.Format.nSamplesPerSec * OutWaveFormatCapture.Format.wBitsPerSample * OutWaveFormatCapture.Format.nChannels / 8;
            MyHeaderInfoFile.BlockAlign = OutWaveFormatCapture.Format.nBlockAlign;
            MyHeaderInfoFile.FormatAudioData = OutWaveFormatCapture.SubFormato == GUIDs_MF_AUDIO_SUBTYPES.MFAudioFormat_PCM ? 0 : 0x0003; //0x0003 é o formato IEEE Float

            //O SISTEMA VAI USAR O MODO DE EVENTOS ORIENTADOS PARA O BUFFER. ISSO INDICA QUE O APP VAI LER OS DADOS DISPONIVEIS PELO DISPOSITIVO
            //QUANDO O MESMO SINALIZAR QUE HÁ DADOS DISPONIVEIS, ISSO MELHORA O DESEMPENHO COMO TODO. 
            //VOCÊ AINDA PODE INICIALIZAR SEM EVENTOS ORIENTADOS PARA O BUFFER TIRANDO A FLAG: CA_CoreAudio_AUDCLNT_STREAMFLAGS_XXX.CA_AUDCLNT_STREAMFLAGS_EVENTCALLBACK E REMOVENDO A CHAMADA PARA O MÉTODO
            //(SetEventHandle) ABAIXO. 
            //VOCÊ TERA QUE MUDAR TAMBÉM O LAÇO UTILIZADO PARA CAPTURAR OS DADOS, TIRANDO AS CHAMADAS PAR AO EVENTO (myCaptureAudio.WinEventBufferAudio) E ADICIONANDO ALGUM SLEEP JUNTO AO MÉTODO
            //(NextPacketSize) PARA DETERMINAR A HORA QUE SE DEVE OBTER OS DADOS DO DISPOSITIVO.


            //Inicializa a interface de eventos que vai ser sinalizada para processar as amostras.
            myCaptureAudio.WinEventBufferAudio = new CarenEvent();

            //Cria o evento para ser resetado automaticamente e define seu estado inicial para (NÃO SINALIZADO), necessário para funcionar corretamente.
            myCaptureAudio.WinEventBufferAudio.CriarEvento(null, false, false, "Evt_AudioBufferNotify");

           //Inicializa o dispositivo de renderização a ter os dados capturados no modo LOOPBACK.
           Resultado = myCaptureAudio.AudioClientConfig.Initialize(
                CA_AUDIOCLIENTE_SHAREMODE.AUDCLNT_SHAREMODE_SHARED,
                (uint)CA_CoreAudio_AUDCLNT_STREAMFLAGS_XXX.CA_AUDCLNT_STREAMFLAGS_LOOPBACK | //Define a flag para indicar que vai capturar os dados do renderizador.
                (uint)CA_CoreAudio_AUDCLNT_STREAMFLAGS_XXX.CA_AUDCLNT_STREAMFLAGS_EVENTCALLBACK, //Define a flag para indicar que vai usar buffers orientado por eventos.
                REFTIMES_PER_SEC,
                0,
                ref OutWaveFormatCapture,
                GUID_SESSION_AUDIO);
            
            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar inicializar o dispositivo de captura. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define o evento para o AudioCliente notificar quando novas amostras de dados estiverem disponiveis.
            Resultado = myCaptureAudio.AudioClientConfig.SetEventHandle(myCaptureAudio.WinEventBufferAudio);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao definir a interface de eventos que recebe as sinalizações da Audio Cliente para ler o buffer. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Obtém o tamanho do buffer selecionado pelo dispositivo.
            Resultado = myCaptureAudio.AudioClientConfig.GetBufferSize(out uint OutBufferInFrames);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o tamanho do buffer selecionado pelo dispositivo de captura. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define na estrutura,
            myCaptureAudio.BufferSizeInFames = OutBufferInFrames;

            //Inicializa a interface de captura que vai ser criada.
            myCaptureAudio.AudioCapture = new CarenAudioCaptureClient();

            //Chama o método para obter a interface de captura de áudio.
            Resultado = myCaptureAudio.AudioClientConfig.GetService(GUIDs_InterfacesWASAPI.IID_IAudioCaptureClient, myCaptureAudio.AudioCapture);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a interface responsável pela captura dos dados de áudio do dispositivo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Inicializa a interface de controle de volume
            myCaptureAudio.AudioCaptureVolume = new CarenSimpleAudioVolume();

            //Obtém a interface que controla o volume do áudio.
            Resultado = myCaptureAudio.AudioClientConfig.GetService(GUIDs_InterfacesWASAPI.IID_ISimpleAudioVolume, myCaptureAudio.AudioCaptureVolume);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a interface de controle de volume do áudio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        public CarenResult IniciarCapturaDados()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Define o volume de captura do volume.
            Resultado = myCaptureAudio.AudioCaptureVolume.SetMasterVolume(1.0f, GUID_SESSION_AUDIO);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar definir o volume de captura do dispositivo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Cria a task responsável pela captura dos dados do dispositivo.
            Task_ReadDataDispositivo = new Task(() =>
            {
                //Define que está capturando dados.
                StatusCapturandoDados = true;

                //Variavies utilizadas.
                uint SizeInBytesBuffer = 0;
                uint OutFramesReaded = 0;
                CA_AUDIOCLIENTE_BUFFERFLAGS FlagsBuffer = CA_AUDIOCLIENTE_BUFFERFLAGS.Zero;
                ICarenBuffer BufferSilence = new CarenBuffer();

                //Define que essa thread deve ter uma latencia menor.
                WinFuncs._AvSetMmThreadCharacteristicsW(CA_Windows_MMCSS_Multimedia_Name_Tasks.Pro_Audio, out uint OutTaskIndex);

                //Define a TaskIndex na estrutura
                myCaptureAudio.TaskIndex = OutTaskIndex;

                //Abre o laço que vai ficar capturando os dados.
                while (StatusCapturandoDados)
                {
                    //Chama o evento para aguradar o dispositivo notificar parar poder capturar os dados.
                    Resultado = myCaptureAudio.WinEventBufferAudio.AguardarObjetoUnico(3000);

                    //Verifica o resultado
                    if(Resultado.StatusCode != ResultCode.SS_WAIT_OBJECT_0)
                    {
                        //Ocorreu uma falha...

                        //Mostra uma mensagem de erro.
                        ShowMensagem(
                            "Ocorreu uma falha ao aguardar pelo dispositivo de renderização os dados a serem capturados. Mensagem de erro -> "
                            + Resultado.ObterMensagem((int)Resultado.HResult), true);

                        //Define que não está mais capturando
                        StatusCapturandoDados = false;

                        //Sai do laço
                        break;
                    }

                    //Chama o método para ler os dados do dispositivo.
                    Resultado = myCaptureAudio.AudioCapture.GetBuffer(
                        out myCaptureAudio.BufferCapturedAudio,
                        out OutFramesReaded,
                        out FlagsBuffer,
                        out _,
                        out _);

                    //Verifica se obteve sucesso
                    if (Resultado.StatusCode != ResultCode.SS_OK)
                    {
                        //A operação falhou.

                        //Mostra uma mensagem de erro.
                        ShowMensagem(
                            "Ocorreu uma falha ao tentar caturar os dados disponiveis no dispositivo de captura. Mensagem de erro -> "
                            + Resultado.ObterMensagem((int)Resultado.HResult), true);

                        //Sai do laço
                        break;
                    }

                    //Define o tamanho do buffer lido do dispositivo.
                    SizeInBytesBuffer = OutFramesReaded * myCaptureAudio.FrameSize;

                    //Verifica os Flags do buffer.
                    if ((FlagsBuffer & CA_AUDIOCLIENTE_BUFFERFLAGS.AUDCLNT_BUFFERFLAGS_SILENT) != 0)
                    {
                        //Cria o buffer do tamanho dos dados capturados.
                        BufferSilence.CreateBuffer(SizeInBytesBuffer);

                        //Preenche o buffer com zeros.
                        BufferSilence.FillBuffer();

                        //Envia o buffer para o escritor de dados.
                        EnviarAmostra(ref BufferSilence, SizeInBytesBuffer);

                        //Libera a memória utilizada pelo buffer de silencio.
                        BufferSilence.ReleaseBuffer();
                    }
                    else
                    {
                        //Define as informações no buffer capturado.
                        myCaptureAudio.BufferCapturedAudio.TamanhoValido = SizeInBytesBuffer;
                        myCaptureAudio.BufferCapturedAudio.Tamanho = SizeInBytesBuffer;
                        myCaptureAudio.BufferCapturedAudio.SetPosition(0);

                        //Envia o buffer para o escritor de dados.
                        EnviarAmostra(ref myCaptureAudio.BufferCapturedAudio, SizeInBytesBuffer);
                    }

                    //Chama o método para liberar o buffer.
                    Resultado = myCaptureAudio.AudioCapture.ReleaseBuffer(OutFramesReaded);

                    //Verifica se obteve sucesso
                    if (Resultado.StatusCode != ResultCode.SS_OK)
                    {
                        //A operação falhou.

                        //Mostra uma mensagem de erro.
                        ShowMensagem(
                            "Ocorreu uma falha ao tentar liberar o buffer capturado anteriormente. Mensagem de erro -> "
                            + Resultado.ObterMensagem((int)Resultado.HResult), true);

                        //Sai do laço
                        break;
                    }

                    //Incrementa a quantidade de dados capturados.
                    MyHeaderInfoFile.TotalLenghtCaptured += SizeInBytesBuffer;
                }
            });

            //Define um tempo menor para o delay do sistema.
            WinFuncs._TimeBeginPeriod(5);

            //Chama o método para iniciar o dispositivo de captura para obter os dados.
            Resultado = myCaptureAudio.AudioClientConfig.Start();

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao solicitar que o dispositivo de captura inicie a captura dos dados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Inicia a task de captura.
            Task_ReadDataDispositivo.Start();

        Done:;

            //Retorna o resultado.
            return Resultado;
        }

        public CarenResult PararCapturaDados()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Define para parar de capturar os dados.
            StatusCapturandoDados = false;

            //Aguarda um tempo até todos os dados tiverem sido escritos.
            while (Task_ReadDataDispositivo.Status == TaskStatus.Running)
            {
                WinFuncs.SleepNativo(100);
            }

            //Chama o método para parar o dispositivo de captura.
            Resultado = myCaptureAudio.AudioClientConfig.Stop();

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao pedir ao dispostivo de captura que parasse. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Aguarda o escritor de dados terminar de escrever todos os dados.
            while (ListaBuffersAudio.Count != 0)
            {
                WinFuncs.SleepNativo(100);
            }

            //Define para parar de escrveer dados.
            StatusGeral = false;
            StatusEscritorDados = false;

            //Faz um delay
            WinFuncs.SleepNativo(500);

            //Chama o método para finalizar a criação do arquivo.
            Resultado = FinalizarArquivoWav();

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao terminar de definir os dados do header do arquivo final. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação.
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

            //Reverte todas as informações.
            WinFuncs._AvRevertMmThreadCharacteristics(myCaptureAudio.HandleTaskPrioridade);
            WinFuncs._TimeEndPeriod(5);

        Done:;

            //Retorna o resultado.
            return Resultado;
        }
        #endregion

        #region Métodos para gerenciamento do arquivo Wav que vai receber os dados.
        /// <summary>
        /// Método responsável por criar e preparar o arquivo que vai receber os dados capturados do dispositivo de áudio.
        /// </summary>
        /// <param name="Param_Url">A url para o arquivo que será criado.</param>
        /// <returns></returns>
        public CarenResult CriarArquivoWav(String Param_Url)
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Variaveis
            ICarenBuffer BufferHeaderZero = null;
            ulong RefTotalWritten = 0;

            //Deleta o arquivo se ja existir.
            File.Delete(Param_Url);

            //Chama o construtor para criar o arquivo de destino.
            myCaptureAudio.StreamFile = new CarenStream(Param_Url, CA_STGMs.CA_STGM_READWRITE, CA_FILE_ATTRIBUTES.CA_FILE_ATTRIBUTE_NORMAL, true);

            //Verifica se não houve erro.
            if (myCaptureAudio.StreamFile is null)
            {
                //Define erro na operação.
                Resultado.AdicionarCodigo(ResultCode.ER_FAIL, false);

                //Sai do método.
                goto Done;
            }

            //Cria um buffer que vai conter o tamanho do HEADER do arquivo Wav, mais preenchidos com zero.
            BufferHeaderZero = new CarenBuffer();
            BufferHeaderZero.CreateBuffer(MyHeaderInfoFile.HeaderSize);

            //Preenche o buffer com Zeros.
            BufferHeaderZero.FillBuffer();

            //Escreve o tamanho do header no inicio do fluxo para poder reservar.
            Resultado = myCaptureAudio.StreamFile.Write(BufferHeaderZero, MyHeaderInfoFile.HeaderSize, ref RefTotalWritten);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao escrever o HEADER vazio no inicio do fluxo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna
            return Resultado;
        }

        /// <summary>
        /// Método responsável por terminar de configurar o header e finalizar o arquivo.
        /// </summary>
        /// <returns></returns>
        public CarenResult FinalizarArquivoWav()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Variaveis a serem utilizadas.
            ulong OutTotalWriter = 0;

            //Cria o buffer que vai conter os dados a serem escritos.
            ICarenBuffer BufferWriter = new CarenBuffer();

            //Cria o buffer para escrever os dados do header.
            BufferWriter.CreateBuffer(MyHeaderInfoFile.HeaderSize);

            //Calcula o tamanho total do arquivo.
            MyHeaderInfoFile.TotalFileSize = (uint)MyHeaderInfoFile.TotalLenghtCaptured + MyHeaderInfoFile.HeaderSize;

            //Escreve os dados do header.
            BufferWriter.Write(MFTFuncs._FCC("RIFF"));
            BufferWriter.Write(MyHeaderInfoFile.TotalFileSize);
            BufferWriter.Write(MFTFuncs._FCC("WAVE"));
            BufferWriter.Write(MFTFuncs._FCC("fmt "));
            BufferWriter.Write(MyHeaderInfoFile.SubChunkSize);
            BufferWriter.Write(MyHeaderInfoFile.FormatAudioData); //Formato dos dados = IEEE Float.
            BufferWriter.Write(MyHeaderInfoFile.Canais); //Quantidade de canais.
            BufferWriter.Write(MyHeaderInfoFile.SampleRate); //Sample Rate.
            BufferWriter.Write((uint)MyHeaderInfoFile.BitsPerSample * MyHeaderInfoFile.Canais * MyHeaderInfoFile.SampleRate / 8); //Bytes per sample.
            BufferWriter.Write((ushort)(MyHeaderInfoFile.BitsPerSample * MyHeaderInfoFile.Canais / 8)); //Alinhamento de bloco.
            BufferWriter.Write(MyHeaderInfoFile.BitsPerSample); //Bitpersample
            BufferWriter.Write(MFTFuncs._FCC("data")); //Marca inicio do buffer.
            BufferWriter.Write((uint)MyHeaderInfoFile.TotalLenghtCaptured); //Tamanho total dos dados de audio.

            //Define como posicação zero no fluxo.
            Resultado = myCaptureAudio.StreamFile.Seek(0, CA_STREAM_SEEK.CA_STREAM_SEEK_SET, out ulong NewSeekPos);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar definir uma posição no fluxo para escrita do header. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Chama o método para escrever os dados no fluxo.
            Resultado = myCaptureAudio.StreamFile.Write(BufferWriter, MyHeaderInfoFile.HeaderSize, ref OutTotalWriter);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar escrever os dados do header no fluxo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Consolida os dados do fluxo para o arquivo.
            Resultado = myCaptureAudio.StreamFile.Commit(CA_STGC.CA_STGC_CONSOLIDATE);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao consolidar os dados do header no fluxo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Libera o fluxo e sua referencia para o arquivo.
            myCaptureAudio.StreamFile.LiberarReferencia();
            myCaptureAudio.StreamFile.Finalizar();
            myCaptureAudio.StreamFile = null;

        Done:;

            //Retorna
            return Resultado;
        }

        /// <summary>
        /// Método responsável por criar a task que fica escrevendo os dados no buffer.
        /// </summary>
        public void IniciarEscritorDados()
        {
            //Cria o buffer que vai conter as amostras de áudio.
            ListaBuffersAudio = new List<ICarenBuffer>(SIZE_INITIAL_BUFFER);

            //Cria a task responsável por ficar escrever no arquivo.
            Task_EscritorDados = new Task(async () =>
            {
                //Variaveis
                CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);
                ICarenBuffer BufferNextWriter = null;
                ulong RefTotalWrittenBytes = 0;
                uint ActualSamplesWrited = 0;

                //Define que o escritor de dados está processando
                StatusEscritorDados = true;

                //Define o status geral para true.
                StatusGeral = true;

                //Abre um laço que vai ficar escrevendo os dados no arquivo.
                while (StatusEscritorDados)
                {
                    //Verifica se o Status geral não é false.
                    if (!StatusGeral)
                    {
                        //Define que o laço vai sair
                        StatusEscritorDados = false;

                        //Sai do laço.
                        break;
                    }

                    //Verifica se tém buffers para serem escritos
                    if (GetCountBuffersAudio() <= 0)
                        goto Done; //Pula para o Delay.

                    //Remove e obtém o proximo buffer da lista a ser escrito.
                    BufferNextWriter = ObterProximaAmostra();

                    //Verifica se a amostra não é nula.
                    if (BufferNextWriter is null)
                        goto Done; //O buffer é invalido.

                    //Chama o método para escrever os dados no fluxo.
                    Resultado = myCaptureAudio.StreamFile.Write(BufferNextWriter, BufferNextWriter.TamanhoValido, ref RefTotalWrittenBytes);

                    //Verifica se não houve erro.
                    if (Resultado.StatusCode != ResultCode.SS_OK)
                    {
                        //A operação de escrita falhou.

                        //Mostra uma mensagem de erro.
                        ShowMensagem(
                            "Ocorreu uma falha ao escrever os dados do buffer de áudio no arquivo de destino. Mensagem de erro -> "
                            + Resultado.ObterMensagem((int)Resultado.HResult), true);

                        //Define que o status geral é false.
                        StatusGeral = false;

                        //Define que vai sair do laço.
                        StatusEscritorDados = false;
                    }

                    //Libera o buffer.
                    BufferNextWriter.ReleaseBuffer();
                    BufferNextWriter = null;

                    //Incrementa a quantidade de amostras escritas.
                    ActualSamplesWrited++;

                    //Verifica a quantidade e chama o GC se necessário.
                    if (ActualSamplesWrited >= 300)
                    {
                        //Chama o GC.
                        GC.Collect();
                        GC.WaitForPendingFinalizers();
                        GC.Collect();

                        //Reseta a quantidade.
                        ActualSamplesWrited = 0;
                    }

                    //Chama o continue para pular o delay
                    continue;

                Done:;
                    await Task.Delay(5);
                }

                //Chama o GC.
                GC.Collect();
                GC.WaitForPendingFinalizers();
                GC.Collect();
            });

            //Inicia o escritor de dados.
            Task_EscritorDados.Start();
        }
        #endregion

        #region Métodos que gerenciam o buffer responsável por conter os dados a serem escritos.
        public void EnviarAmostra(ref ICarenBuffer Param_Buffer, uint Param_CountAudioBytes)
        {
            //Sincroniza o acesso a lista que contém os buffers de áudio.
            lock (SyncList)
            {
                //Novo buffer a ser adicionado.
                ICarenBuffer NewBuffer = new CarenBuffer();

                //Cria o buffer com a quantidade de dados validos.
                NewBuffer.CreateBuffer(Param_CountAudioBytes);

                //Cópia os dados do buffer do dispositivo de áudio para a amostra atual.
                NewBuffer.Write(Param_Buffer, 0, Param_CountAudioBytes);

                //Reseta a posição do buffer.
                NewBuffer.SetPosition(0);

                //Define as informações.
                NewBuffer.TamanhoValido = Param_CountAudioBytes;
                NewBuffer.Tamanho = Param_CountAudioBytes;

                //Adiciona na lista.
                ListaBuffersAudio.Add(NewBuffer);
            }
        }

        public ICarenBuffer ObterProximaAmostra()
        {
            //Sincroniza o acesso a lista que contém os buffers de áudio.
            lock (SyncList)
            {
                //Variavel a ser retornada.
                ICarenBuffer NextBuffer = null;

                //Verifica se a lista contém amostras.
                if (ListaBuffersAudio.Count <= 0)
                    goto Done; //Nenhuma amostra disponivel.

                //Obtém a amostra.
                NextBuffer = ListaBuffersAudio.ElementAtOrDefault(0);

                //Remove o buffer da lista.
                ListaBuffersAudio.RemoveAt(0);

            Done:;
                //Retorna a amostra.
                return NextBuffer;
            }
        }

        public int GetCountBuffersAudio()
        {
            //Sincroniza o acesso a lista que contém os buffers de áudio.
            lock (SyncList)
            {
                //Retorna a quantidade de buffers na lista.
                return ListaBuffersAudio.Count;
            }
        }
        #endregion

        #region Utilidades
        public void ShowMensagem(String Mensagem, Boolean ErrorMsg = false)
        {
            MessageBox.Show(Mensagem, "Audio Capture Test", MessageBoxButtons.OK, ErrorMsg ? MessageBoxIcon.Error : MessageBoxIcon.Information);
        }

        public String ObterNomeDispositivoByIndex(uint Param_IdDevice)
        {
            //Variavel que vai retornar o resultado.
            String NomeDispositivo = string.Empty;

            //Variaveis utilizadas.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);
            CA_PROPERTYKEY PropKey = new CA_PROPERTYKEY() { GUIDProp = GUIDs_CoreAudio_Propriedades.PKEY_Device_FriendlyName, PID = GUIDs_CoreAudio_Propriedades.PID_Device_FriendlyName };


            //Tenta recuperar o dispositivo de captura indicado pelo id.
            Resultado = myCaptureAudio.ColecaoDispositivos.Item(Param_IdDevice, out ICarenMMDevice OutDeviceCapture);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o dispositivo de captura indicado pelo Id. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Chama o método para obter a loja de propriedades do dispositivo.
            Resultado = OutDeviceCapture.OpenPropertyStore(CA_STGMs.CA_STGM_READ, out ICarenPropertyStore OutPropStore);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Libera a referencia para o dispositivo de captura.
                OutDeviceCapture.LiberarReferencia();
                OutDeviceCapture.Finalizar();
                OutDeviceCapture = null;

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter a interface de propriedades do dispositivo. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Chama o método para obter o nome do dispositivo de captura.
            Resultado = OutPropStore.GetValue(ref PropKey, out CA_PROPVARIANT OutPropValor);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Libera a referencia para o dispositivo de captura.
                OutDeviceCapture.LiberarReferencia();
                OutPropStore.LiberarReferencia();
                OutDeviceCapture.Finalizar();
                OutPropStore.Finalizar();
                OutDeviceCapture = null;
                OutPropStore = null;

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao obter o nome do dispositivo.. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define o nome do dispositivo na variavel de retorno.
            NomeDispositivo = OutPropValor.pwszVal;

            //Libera as interfaces e dados.
            OutDeviceCapture.LiberarReferencia();
            OutPropStore.LiberarReferencia();
            OutDeviceCapture.Finalizar();
            OutPropStore.Finalizar();
            OutDeviceCapture = null;
            OutPropStore = null;
            OutPropValor = null;

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

        Done:;

            //Retorna o resultado.
            return NomeDispositivo;
        }

        public void ReleaseAllInterfaces()
        {
            try
            {
                //Define os status para false.
                StatusCapturandoDados = false;
                StatusEscritorDados = false;
                StatusGeral = false;

                //Abre um While para liberar todas as amostras pendentes.
                while (true)
                {
                    //Verifica se a lista contém amostras ainda pendente.
                    if (ListaBuffersAudio is not null && ListaBuffersAudio.Count > 0)
                    {
                        //Obtém o buffer a ser removido.
                        ICarenBuffer TempBuffer = ObterProximaAmostra();

                        //Verifica se é valido e libera os dados.
                        if (TempBuffer is not null)
                        {
                            TempBuffer.ReleaseBuffer();
                            TempBuffer = null;
                        }
                    }
                    else
                    {
                        //Sai do laço.
                        break;
                    }
                }

                //Verifica a lista e limpa os dados.
                if (ListaBuffersAudio is not null)
                {
                    //Limpa a lista.
                    ListaBuffersAudio.Clear();
                    ListaBuffersAudio.Capacity = 1;
                    ListaBuffersAudio = null;
                }

                //Libera os media types e atributos.
                SafeReleaseInterface(myCaptureAudio.DispositivoCaptura);
                SafeReleaseInterface(myCaptureAudio.EnumeradorDispositivos);
                SafeReleaseInterface(myCaptureAudio.ColecaoDispositivos);
                SafeReleaseInterface(myCaptureAudio.AudioCapture);
                SafeReleaseInterface(myCaptureAudio.AudioCaptureVolume);
                SafeReleaseInterface(myCaptureAudio.AudioClientConfig);
                myCaptureAudio.WavFormatCapture = null;

                //Libera o fluxo se ainda for valido
                if (myCaptureAudio.StreamFile is not null)
                {
                    //Libera os dados.
                    myCaptureAudio.StreamFile.LiberarReferencia();
                    myCaptureAudio.StreamFile.Finalizar();
                    myCaptureAudio.StreamFile = null;
                }

                //Info.
                Debug.WriteLine("Todos os dados e interfaces foram liberadas.");
            }
            catch (Exception)
            {

            }
            finally
            {
                //Chama o GC para limpar tos dados.
                GC.Collect();
                GC.WaitForPendingFinalizers();
                GC.Collect();
            }
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





        private void LoopbackTest_Load(object sender, EventArgs e)
        {

        }

        private void Btn_ListarDispositivos_Click(object sender, EventArgs e)
        {
            //Obtém os dispostivos de captura.
            ObterDispositivosRenderizacao();

            //Lista os dispositivos.
            if (myCaptureAudio.CountDevicesCaptureCollection > 0)
            {
                //Limpa o combobox atual.
                Cbx_ListCaptureAudioDevices.Items.Clear();

                //Faz um for para adicionar os nomes de cada dispositivo.
                for (uint i = 0; i < myCaptureAudio.CountDevicesCaptureCollection; i++)
                {
                    //Obtém o nome do dispositivo e define no combobox.
                    Cbx_ListCaptureAudioDevices.Items.Add(ObterNomeDispositivoByIndex(i));
                }

                //Seleciona o Index 0.
                Cbx_ListCaptureAudioDevices.SelectedIndex = 0;
            }
            else
            {
                //Mostra uma mensagem de erro.
                ShowMensagem("Nenhum dispositivo de captura disponivel!!", true);
            }
        }

        private void Btn_AtivarDispositivo_Click(object sender, EventArgs e)
        {
            //Chama o método para ativar o dispositivo.
            CarenResult Resultado = AtivarDispositivoRenderForLoopbackByIndex((uint)Cbx_ListCaptureAudioDevices.SelectedIndex);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar ativar o dispositivo solicitado. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Mostra uma mensagem de sucesso.
            ShowMensagem($"O dispositivo de renderização a ser capturado '{Cbx_ListCaptureAudioDevices.Items[Cbx_ListCaptureAudioDevices.SelectedIndex]}' foi ativado e está pronto para uso!");

        Done:;
        }

        private void Btn_StartCapture_Click(object sender, EventArgs e)
        {
            //Desativa o botão.
            Btn_StartCapture.Enabled = false;

            //Verifica se foi informado a URL.
            if (String.IsNullOrEmpty(Txb_UrlOutputFile.Text))
                ShowMensagem("A url para o arquivo de destino que vai conter os dados capturados não pode ser NULA!", true);

            //Tenta criar o arquivo que vai receber os dados capturados.
            CarenResult Resultado = CriarArquivoWav(Txb_UrlOutputFile.Text);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar criar o arquivo que iria receber os dados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Inicia o esctitor responsável por escrever os dados
            IniciarEscritorDados();

            //Chama o método para iniciar a captura dos dados.
            IniciarCapturaDados();

            Btn_StartCapture.Text = "Capturando";

        Done:;
        }

        private void Btn_StopCapture_Click(object sender, EventArgs e)
        {
            //Desativa o botão.
            Btn_StopCapture.Enabled = false;

            //Chama o método para 
            CarenResult Resultado = PararCapturaDados();

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar parar de capturar os dados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }
            else
            {
                //Mostra uma mensagem.
                ShowMensagem("Os dados foram capturados com sucesso. Confira o arquivo na url> " + Txb_UrlOutputFile.Text);
            }

            //Libera todos os dados.
            ReleaseAllInterfaces();

        Done:;
            Btn_StartCapture.Enabled = true;
            Btn_StopCapture.Enabled = true;
            Btn_StartCapture.Text = "Capturar";
        }
    }
}
