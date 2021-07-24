using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//SDKs utilizados
using CarenRengine;
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.GUIDs;
using CarenRengine.CarenCodesStatus;
using CarenRengine.MediaFoundation;
using CarenRengine.MediaFoundationExtended;

namespace WebCamCapture
{
    /*
     * ESTE PROJETO TEM COMO OBJETO DEMONSTRAR OS PASSOS NECESSÁRIOS PARA LISTAR UM DISPOSITIVO DE CAPTURA DE VÍDEO QUE SERÁ UTILIZADO
     * PARA CAPTURAR IMAGENS E RENDERIZAR UTILIZANDO AS APIS DA MEDIA FOUNDATION.
     */


    public partial class WebCamCapture : Form
    {
        public WebCamCapture()
        {
            InitializeComponent();
        }

        #region Estruturas
        public struct InterfacesMF
        {
            public ICarenMFSourceReaderExtend LeitorMF;
            public ICarenMFMediaSource MediaSource;
            public ICarenMFSourceReaderCallback CallbackLeitorMF;
        }

        public struct InterfacesD3D11 
        {

        }

        public struct InterfacesDXGI
        {

        }

        public struct DadosGlobais
        {
            public List<ICarenMFActivate> WebCamAtivadores;
            public uint QuantidadeDispositivos;
        }
        #endregion

        #region Variaveis
        private DadosGlobais Dados = new DadosGlobais();
        private MediaFoundationFunctions MFFuncs = new MediaFoundationFunctions();
        #endregion

        #region Load Formulario
        private void WebCamCapture_Load(object sender, EventArgs e)
        {

        }
        #endregion

        #region Botões da interface
        private void Btn_ListarDevices_Click(object sender, EventArgs e)
        {
            //Inicia a plataforma da Media Foundation.
            MFFuncs._MFStartup();

            //Lista os dispositivos de captura de Video.
            ListarDispositivosCapturaVideo();
        }

        private void Btn_Start_Click(object sender, EventArgs e)
        {

        }

        private void Btn_Parar_Click(object sender, EventArgs e)
        {

        }
        #endregion

        #region Métodos para listar dispositivos de captura de video
        private CarenResult ListarDispositivosCapturaVideo()
        {
            //Variavel que vai retornar o resultado.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Variveis a serem utilizadas
            ICarenMFAttributes AtributosPesquisaDispositivos = new CarenMFAttributes(1);
            ICarenMFActivate[] ListaDispositivos = null;
            UInt32 CountDevices = 0;

            //Cria a lista que vai receber os dispositivos.
            Dados.WebCamAtivadores = new List<ICarenMFActivate>();

            //Adiciona o atributo de pesquisa para dispositivo de video.
            Resultado = AtributosPesquisaDispositivos.SetGUID(
                GUIDs_MFAttributes_CaptureDevice.MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
                GUIDs_MFAttributes_CaptureDevice.MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);

            //Verifica se não houve erro
            if(Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Ocorreu uma falha
                MessageBox.Show(
                    $"Ocorreu uma falha ao adicionar os atributos de pesquisa! \r\n Codigo de erro: {Resultado.StatusCode}", 
                    "WebCamCapture", MessageBoxButtons.OK, MessageBoxIcon.Error);

                //Pula para o fim.
                goto Done;
            }

            //Chama o método para listar os dispositivos.
            Resultado = MFFuncs._MFEnumDeviceSources(AtributosPesquisaDispositivos, out ListaDispositivos, out CountDevices);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Ocorreu uma falha
                MessageBox.Show(
                    $"Ocorreu uma falha ao listar os dispositivos de captura de video! \r\n Codigo de erro: {Resultado.StatusCode}",
                    "WebCamCapture", MessageBoxButtons.OK, MessageBoxIcon.Error);

                //Pula para o fim.
                goto Done;
            }

            //Verifica se a quantidade de dispositivos não é zero.
            if(CountDevices == 0)
            {
                //Nenhum dispositivo encontrado.
                MessageBox.Show("Nenhum dispositivo de captura de video habilitado no sistema foi encontrado!",
                    "WebCamCapture", MessageBoxButtons.OK, MessageBoxIcon.Warning);

                //Pula para o fim.
                goto Done;
            }

            //Adiciona os dispositivos listado na lista global.
            Dados.WebCamAtivadores.AddRange(ListaDispositivos);

            //Faz um for para obter o nome dos dispositivos.
            foreach (var AtivadorDevice in Dados.WebCamAtivadores)
            {
                //Obtém o nome do dispositivo.
                String s = ObterNomeDispositivo(AtivadorDevice);

                //Define na combobox
                Cbx_ListaWebCams.Items.Add(s);
            }

            //Define o dispositivo no Combobox como 0
            Cbx_ListaWebCams.SelectedIndex = 0;

            //Define a quantidade de dispositivos
            Dados.QuantidadeDispositivos = CountDevices;

            //Define como sucesso operação.
            Resultado = ResultCode.SS_OK;

        Done:;
            //Libera a interface de atributos.
            SafeReleaseInterface(AtributosPesquisaDispositivos);

            //Retorna o resultado.
            return Resultado;
        }

        private String ObterNomeDispositivo(ICarenMFActivate Device)
        {
            //Obtém o nome do dispositivo.
            CarenResult Resultado = Device.GetAllocatedString(
                GUIDs_MFAttributes_CaptureDevice.MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, 
                out String OutNameDevice, 
                out _);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Ocorreu uma falha
                MessageBox.Show(
                    $"Ocorreu uma falha ao tentar obter o nome do dispositivo de captura de video! \r\n Codigo de erro: {Resultado.StatusCode}",
                    "WebCamCapture", MessageBoxButtons.OK, MessageBoxIcon.Error);

                //Pula para o fim.
                goto Done;
            }

        Done:;
            //Retorna o nome do dispositivo.
            return OutNameDevice;
        }
        #endregion

        #region Métodos Auxiliares
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
    }
}
