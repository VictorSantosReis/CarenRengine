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
        }
        #endregion

        #region Constantes

        #endregion

        #region Variaveis
        public MyInterfacesForCaptureDevice myCaptureAudio = new MyInterfacesForCaptureDevice();

        public uint CountDevicesCapture = 0;

        ICarenStream StreamToFileDest = null;
        ICarenBuffer BufferWriter = null;
        const ulong countbytespersec = 352800;
        const ushort HeaderSize = 44;
        ulong TotalFileSize = (countbytespersec * 10) + HeaderSize;
        ulong outtotalwirter = 0;
        MediaFoundationFunctions mftfuncs = new MediaFoundationFunctions();
        #endregion

        private void AudioCaptureTest_Load(object sender, EventArgs e)
        {
            
        }

        private void Btn_ListarDispositivos_Click(object sender, EventArgs e)
        {
            //Cria o arquivo que vai receber os dados.
            StreamToFileDest = new CarenStream("C:\\Temp\\WavFile.wav", CA_STGMs.CA_STGM_READWRITE, CA_FILE_ATTRIBUTES.CA_FILE_ATTRIBUTE_NORMAL, true);
            if (StreamToFileDest is not null && StreamToFileDest.StatusPonteiro().StatusCode == ResultCode.SS_OK)
                MessageBox.Show("O arquivo Wav foi criado com sucesso!");
            else
                MessageBox.Show("Falhou ao tentar criar o arquivo!");

        }

        private void Btn_StartCapture_Click(object sender, EventArgs e)
        {
            //Define o tamanho total do arquivo.
            StreamToFileDest.SetSize(TotalFileSize);

            //Cria o buffer que vai conter os dados a serem escritos.
            BufferWriter = new CarenBuffer();

            //Cria o buffer para escrever os dados do header.
            BufferWriter.CriarBuffer(HeaderSize);

            //Escreve o Header.
            BufferWriter.Write(mftfuncs._FCC("RIFF"));
            BufferWriter.Write((uint)TotalFileSize);
            BufferWriter.Write(mftfuncs._FCC("WAVE"));
            BufferWriter.Write(mftfuncs._FCC("fmt "));
            BufferWriter.Write((uint)16);
            BufferWriter.Write((ushort)0x0003); //Formato dos dados = IEEE Float.
            BufferWriter.Write((ushort)2); //Quantidade de canais.
            BufferWriter.Write((uint)44100); //Sample Rate.
            BufferWriter.Write((uint)countbytespersec); //Bytes per sample.
            BufferWriter.Write((ushort)(32 * 2 / 8)); //Alinhamento de bloco.
            BufferWriter.Write((ushort)32); //Bitpersample
            BufferWriter.Write(mftfuncs._FCC("data")); //Marca inicio do buffer.
            BufferWriter.Write((uint)TotalFileSize - HeaderSize); //Tamanho total dos dados de audio.

            //Escreve o header no fluxo.
            CarenResult Resultado = StreamToFileDest.Write(BufferWriter, HeaderSize, ref outtotalwirter);

            //Libera o buffer antigo.
            BufferWriter.ReleaseBuffer();

            //Cria o buffer que vai conter os dados a serem escritos no arquivo.
            BufferWriter.CriarBuffer((uint)TotalFileSize - HeaderSize);

            //Preenche com zeros
            BufferWriter.FillBuffer();

            //Escreve os dados no fluxo.
            Resultado = StreamToFileDest.Write(BufferWriter, (uint)TotalFileSize - HeaderSize, ref outtotalwirter);
            Resultado = StreamToFileDest.Commit(CA_STGC.CA_STGC_CONSOLIDATE);
            StreamToFileDest.LiberarReferencia();
            StreamToFileDest.Finalizar();
            StreamToFileDest = null;

            
        }

        private void Btn_StopCapture_Click(object sender, EventArgs e)
        {

        }
    }
}
