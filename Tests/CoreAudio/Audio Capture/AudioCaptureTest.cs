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

//Importa o SDK da Media Foundation para ler amostras.
using CarenRengine.MediaFoundation;
using CarenRengine.MediaFoundationExtended;

using CarenRengine.Windows;

namespace CoreAudio_AudioCaptureTest
{
    public partial class AudioCaptureTest : Form
    {
        public AudioCaptureTest()
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

            public ICarenStream StreamFile { get; set; }

            public ICarenBuffer BufferCapturedAudio { get; set; }

            public ICarenBuffer BufferSlinceAudio { get; set; }

            public CA_WAVEFORMATEXEXTENSIBLE WavFormatCapture { get; set; }

            public uint CountDevicesCaptureCollection { get; set; }

            /// <summary>
            /// Propriedade que indica o tamanho de um unico frame de áudio em bytes.
            /// </summary>
            public uint FrameSize { get; set; }
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
        public const int SIZE_MAX_BUFFER = 0;
        #endregion

        #region Variaveis
        MyInterfacesForCaptureDevice myCaptureAudio = new MyInterfacesForCaptureDevice();

        List<ICarenBuffer> ListaBuffersAudio = new List<ICarenBuffer>(SIZE_MAX_BUFFER);

        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();
        
        Task Task_EscritorDados = null;

        Boolean StatusEscritorDados = false;

        Boolean StatusGeral =  false;

        Boolean ReadStartCapture { get; set; } = false;

        readonly object SyncList = new object();
        #endregion



        #region Métodos que vão listar, configurar e capturar os dados.
        public CarenResult ObterDispositivosCaptura()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Cria o enumerador de dispositivos.
            myCaptureAudio.EnumeradorDispositivos = new CarenMMDeviceEnumerator(CA_CLSCTX.CLSCTX_INPROC_SERVER);

            //Cria a interface que vai conter a coleção de dispositivos.
            myCaptureAudio.ColecaoDispositivos = new CarenMMDeviceCollection();

            //Chama o método para obter todos os dispositivos de captura.
            Resultado = myCaptureAudio.EnumeradorDispositivos.EnumAudioEndpoints(CA_EDataFlow.eCapture, CA_DEVICE_STATE_XXX.CA_DEVICE_STATE_ACTIVE, myCaptureAudio.ColecaoDispositivos);

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

        public CarenResult AtivarDispositivoCapturaByIndex(uint Param_IdDevice)
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

            //Calcula os dados do formato do áudio e define nas estruturas.
            myCaptureAudio.FrameSize = (uint)(OutWaveFormatCapture.Format.wBitsPerSample * OutWaveFormatCapture.Format.nChannels / 8);
            MyHeaderInfoFile.Canais = OutWaveFormatCapture.Format.nChannels;
            MyHeaderInfoFile.BitsPerSample = OutWaveFormatCapture.Format.wBitsPerSample;
            MyHeaderInfoFile.SampleRate = OutWaveFormatCapture.Format.nSamplesPerSec;
            MyHeaderInfoFile.BytesPerSec = OutWaveFormatCapture.Format.nSamplesPerSec * OutWaveFormatCapture.Format.wBitsPerSample * OutWaveFormatCapture.Format.nChannels / 8;
            MyHeaderInfoFile.BlockAlign = OutWaveFormatCapture.Format.nBlockAlign;

        Done:;

            //Retorna o resultado.
            return Resultado;
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

            //Chama o construtor para criar o arquivo de destino.
            myCaptureAudio.StreamFile = new CarenStream(Param_Url, CA_STGMs.CA_STGM_READWRITE, CA_FILE_ATTRIBUTES.CA_FILE_ATTRIBUTE_NORMAL, true);

            //Verifica se não houve erro.
            if(myCaptureAudio.StreamFile is null)
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
            ICarenBuffer BufferWriter = null;
            ulong OutTotalWriter = 0;

            //Cria o buffer que vai conter os dados a serem escritos.
            BufferWriter = new CarenBuffer();

            //Cria o buffer para escrever os dados do header.
            BufferWriter.CreateBuffer(MyHeaderInfoFile.HeaderSize);

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
            //Cria a task responsável por ficar escrever no arquivo.
            Task_EscritorDados = new Task(async() =>
            {
                //Variaveis
                CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);
                ICarenBuffer BufferNextWriter = null;
                ulong RefTotalWrittenBytes = 0;

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
                    if(Resultado.StatusCode != ResultCode.SS_OK)
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

                Done:;

                    //Faz um pequeno delay.
                    await Task.Delay(5);
                }
            });
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
        #endregion






        private void AudioCaptureTest_Load(object sender, EventArgs e)
        {
 
        }

        private void Btn_ListarDispositivos_Click(object sender, EventArgs e)
        {
            //Obtém os dispostivos de captura.
            ObterDispositivosCaptura();

            //Lista os dispositivos.
            if(myCaptureAudio.CountDevicesCaptureCollection > 0)
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
        }

        private void Btn_AtivarDispositivo_Click(object sender, EventArgs e)
        {
            //Chama o método para ativar o dispositivo.
            CarenResult Resultado = AtivarDispositivoCapturaByIndex((uint)Cbx_ListCaptureAudioDevices.SelectedIndex);

            //Verifica o resultado
            if(Resultado.StatusCode == ResultCode.SS_OK)
            {
                //Mostra uma mensagem de sucesso.
                ShowMensagem($"O dispositivo de captura '{Cbx_ListCaptureAudioDevices.Items[Cbx_ListCaptureAudioDevices.SelectedIndex].ToString()}' foi ativado e está pronto para uso!");
            }


        }

        private void Btn_StartCapture_Click(object sender, EventArgs e)
        {

        }

        private void Btn_StopCapture_Click(object sender, EventArgs e)
        {

        }
    }
}
