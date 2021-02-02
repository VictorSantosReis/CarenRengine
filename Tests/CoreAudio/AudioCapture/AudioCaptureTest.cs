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
        #endregion

        private void AudioCaptureTest_Load(object sender, EventArgs e)
        {

        }

        private void Btn_ListarDispositivos_Click(object sender, EventArgs e)
        {

        }

        private void Btn_StartCapture_Click(object sender, EventArgs e)
        {

        }

        private void Btn_StopCapture_Click(object sender, EventArgs e)
        {

        }
    }
}
