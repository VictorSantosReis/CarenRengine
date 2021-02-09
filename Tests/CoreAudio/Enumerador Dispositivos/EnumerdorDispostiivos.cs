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

//Importa do SDK do Windows.
using CarenRengine.Windows;

namespace CoreAudio_EnumeradorDispositivos
{
    public partial class EnumerdorDispostiivos : Form
    {
        //PROJETO SIMPLES QUE TEM COMO OBJETO DESMONSTRAR COMO FUNCIONA A API DE ENUMERAÇÃO DE DISPOSITIVOS DE AUDIO(RENDER E CAPTURA).
        //O PROJETO UTILIZA DA API IMMDevice PARA ENUMERAR TODOS OS DISPOSITIVOS DE ÁUDIO NO SISTEMA ATUAL.
        //OBSERVE, ESSA API NÃO ENUMERA DISPOSITIVOS DE CAPTURA DE VIDEO, APENAS DE ÁUDIO PARA SEREM UTILIZADAS COM AS INTERFACE DA WASAPI
        //(ICarenAudioClient, ICarenAudioRenderClient, ICarenAudioCaptureClient)

        public EnumerdorDispostiivos()
        {
            InitializeComponent();
        }

        #region Estruturas     
        public struct MyInterfaces
        {
            public ICarenMMDeviceEnumerator Enumerador { get; set; }

            public ICarenMMDeviceCollection ColecaoDisposistivos { get; set; }
        }
        #endregion

        #region Variaveis
        MyInterfaces myEnumeradorDevices = new MyInterfaces();
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
            ICarenMMDevice OutDeviceCapture = null;
            ICarenPropertyStore OutPropStore = null;

            //Tenta recuperar o dispositivo de captura indicado pelo id.
            Resultado = myEnumeradorDevices.ColecaoDisposistivos.Item(Param_IdDevice, out OutDeviceCapture);

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
            Resultado = OutDeviceCapture.OpenPropertyStore(CA_STGMs.CA_STGM_READ, out OutPropStore);

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

        Done:;
            //Libera a interface.
            SafeReleaseInterface(OutDeviceCapture);
            SafeReleaseInterface(OutPropStore);

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            //Retorna o resultado.
            return NomeDispositivo;
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






        private void EnumerdorDispostiivos_Load(object sender, EventArgs e)
        {

        }

        private void Btn_EnumRenderAudio_Click(object sender, EventArgs e)
        {
            //Desativa o botão.
            Btn_EnumRenderAudio.Enabled = false;

            //Cria a interface de enumeração de dispositivos.
            myEnumeradorDevices.Enumerador = new CarenMMDeviceEnumerator(CA_CLSCTX.CLSCTX_INPROC_SERVER);

            //Inicializa a coleção que vai conter a lista de dispositivos.
            myEnumeradorDevices.ColecaoDisposistivos = new CarenMMDeviceCollection();

            //Lista todos os dispositivos de renderização de áudio (ATIVOS) no sistema atual.
            //A coleção contém ponteiros para a interface IMMDevice(ICarenMMDevice) que pode ser ativada para uma das interface da WASAPI, como a ICarenAudioClient que configura
            //e inicializa o dispositivo final.
            CarenResult Resultado = myEnumeradorDevices.Enumerador.EnumAudioEndpoints(
                CA_EDataFlow.eRender, //O tipo do dispositivo de áudio
                CA_DEVICE_STATE_XXX.CA_DEVICE_STATE_ACTIVE, //O estado do dispositivo a ser incluido na enumeração(Ativado, Desativado etc)
                myEnumeradorDevices.ColecaoDisposistivos); //A coleção que vai receber os dispositivos.

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar enumerar os dispositivos de renderização ativos no sistema operacional. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Verifica se encontrou algum dispositivo
            Resultado = myEnumeradorDevices.ColecaoDisposistivos.GetCount(out uint OutCountDevices);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar recuperar a quantidade de dispositivos enumerados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Verifica a quantidade
            if (OutCountDevices <= 0)
            {
                //Não há nenhum dispositivo com as caracteristicas dadas na enumeração disponivel.

                //Mostra uma mensagem de ino.
                ShowMensagem("Nenhum dispositivo de renderização de áudio ativo no sistema foi encontrado!");

                //Sai do laço.
                goto Done;
            }

            //Limpa a lista.
            Cbx_RenderAudioDevices.Items.Clear();

            //Abre um for para recuperar o nome de cada dispositivo e adicionar no combobox
            for (uint i = 0; i < OutCountDevices; i++)
            {
                //Obtém o nome e adiciona na lista.
                Cbx_RenderAudioDevices.Items.Add(ObterNomeDispositivoByIndex(i));
            }

            //Define o index zero do combobox.
            Cbx_RenderAudioDevices.SelectedIndex = 0;

        Done:;
            //Descarta todas as interfaces utilizadas.
            SafeReleaseInterface(myEnumeradorDevices.ColecaoDisposistivos);
            SafeReleaseInterface(myEnumeradorDevices.Enumerador);

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            //Ativa novamente o botão
            Btn_EnumRenderAudio.Enabled = true;
        }

        private void Btn_EnumCaptureAudio_Click(object sender, EventArgs e)
        {
            //Desativa o botão.
            Btn_EnumCaptureAudio.Enabled = false;

            //Cria a interface de enumeração de dispositivos.
            myEnumeradorDevices.Enumerador = new CarenMMDeviceEnumerator(CA_CLSCTX.CLSCTX_INPROC_SERVER);

            //Inicializa a coleção que vai conter a lista de dispositivos.
            myEnumeradorDevices.ColecaoDisposistivos = new CarenMMDeviceCollection();

            //Lista todos os dispositivos de renderização de áudio (ATIVOS) no sistema atual.
            //A coleção contém ponteiros para a interface IMMDevice(ICarenMMDevice) que pode ser ativada para uma das interface da WASAPI, como a ICarenAudioClient que configura
            //e inicializa o dispositivo final.
            CarenResult Resultado = myEnumeradorDevices.Enumerador.EnumAudioEndpoints(
                CA_EDataFlow.eCapture, //O tipo do dispositivo de áudio
                CA_DEVICE_STATE_XXX.CA_DEVICE_STATE_ACTIVE, //O estado do dispositivo a ser incluido na enumeração(Ativado, Desativado etc)
                myEnumeradorDevices.ColecaoDisposistivos); //A coleção que vai receber os dispositivos.

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar enumerar os dispositivos de renderização ativos no sistema operacional. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Verifica se encontrou algum dispositivo
            Resultado = myEnumeradorDevices.ColecaoDisposistivos.GetCount(out uint OutCountDevices);

            //Verifica se obteve sucesso
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar recuperar a quantidade de dispositivos enumerados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Verifica a quantidade
            if (OutCountDevices <= 0)
            {
                //Não há nenhum dispositivo com as caracteristicas dadas na enumeração disponivel.

                //Mostra uma mensagem de ino.
                ShowMensagem("Nenhum dispositivo de renderização de áudio ativo no sistema foi encontrado!");

                //Sai do laço.
                goto Done;
            }

            //Limpa a lista.
            Cbx_CaptureAudioDevices.Items.Clear();

            //Abre um for para recuperar o nome de cada dispositivo e adicionar no combobox
            for (uint i = 0; i < OutCountDevices; i++)
            {
                //Obtém o nome e adiciona na lista.
                Cbx_CaptureAudioDevices.Items.Add(ObterNomeDispositivoByIndex(i));
            }

            //Define o index zero do combobox.
            Cbx_CaptureAudioDevices.SelectedIndex = 0;

        Done:;
            //Descarta todas as interfaces utilizadas.
            SafeReleaseInterface(myEnumeradorDevices.ColecaoDisposistivos);
            SafeReleaseInterface(myEnumeradorDevices.Enumerador);

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            //Ativa novamente o botão
            Btn_EnumCaptureAudio.Enabled = true;
        }
    }
}
