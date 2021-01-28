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
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.Constantes;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.Estruturas;

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

            public ICarenMFMediaType AudioTypeMusic { get; set; }

            public ICarenMFMediaType AudioTypeSupportedRender { get; set; }

            public ICarenMMDevice DefaultAudioOutput { get; set; }

            public ICarenAudioClient AudioClientOutputConfig { get; set; }

            public ICarenAudioRenderClient AudioRenderShared { get; set; }

            public ICarenSimpleAudioVolume AudioVolumeControl { get; set; }

            public CA_WAVEFORMATEXEXTENSIBLE WavAudioOutputInfo { get; set; }

            public WindowsFunctions WinFuncs { get; set; }
        }
        #endregion

        #region Constantes

        #endregion

        #region Variaveis
        public MyAudioInterfacesRender MyRenderAudioTest = new MyAudioInterfacesRender();
        #endregion
    }
}
