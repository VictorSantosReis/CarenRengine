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
using System.Diagnostics;

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
            public ICarenMFSourceReader LeitorAmostras { get; set; }

            public ICarenMFSourceReaderCallback CallbackReadSamples { get; set; }

            public ICarenMFAttributes AtributosLeitor { get; set; }

            public ICarenMFMediaType AudioTypeSupportedRenderComplete { get; set; }

            public ICarenMFMediaType AudioTypeSupportedRenderPartial { get; set; }

            public ICarenMMDevice DefaultAudioOutput { get; set; }

            public ICarenMMDeviceEnumerator EnumeradorAudioDevices { get; set; }

            public ICarenAudioClient AudioClientOutputConfig { get; set; }

            public ICarenAudioRenderClient AudioRenderShared { get; set; }

            public ICarenSimpleAudioVolume AudioVolumeControl { get; set; }

            public ICarenBuffer BufferDeviceTemp;

            public CA_WAVEFORMATEXEXTENSIBLE WavAudioOutputInfo { get; set; }

            public WindowsFunctions WinFuncs { get; set; }

            public MediaFoundationFunctions MFTFuncs { get; set; }

            public CarenWindowsEvent WinEventRenderBuffer { get; set; }

            public long FrequencyComputer { get; set; }

            public uint MaximumFrameBufferRender { get; set; }

            public Guid GuidAudioSession { get; set; }
        }
        #endregion

        #region Enumeraçoes
        public enum EnumStatusRenderAudio
        {
            Rendering = 1,

            Paused,

            Stoped,

            EndOfStream,
            
            nostarted
        }
        #endregion

        #region Constantes
        const uint REFTIMES_PER_SEC = 10000000;

        const int SIZE_LIST_BUFFER = 10;
        #endregion

        #region Variaveis
        public MyAudioInterfacesRender MyRenderAudioTest = new MyAudioInterfacesRender();

        public List<MyBufferAudioData> ListBuffer { get; set; }

        public Task TaskRenderData { get; set; }

        public Task TaskSamplesGet { get; set; }

        public Task TaskClockRenderNotify { get; set; }

        public Boolean StatusRequisicaoAmostra { get; set; } = false;

        public Boolean ProcessandoAmostras { get; set; } = false;

        public Boolean RenderizandoAmostras { get; set; } = false;

        public EnumStatusRenderAudio StatusProcessAudio { get; set; } = EnumStatusRenderAudio.nostarted;

        readonly object ObjSyncBuffer = new object();
        #endregion


        #region Métodos de configuração e renderização do áudio.   

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

            //Define o status do processo de audio.
            StatusProcessAudio = EnumStatusRenderAudio.nostarted;

            //Inicia a plataforma da Media Foundation
            MyRenderAudioTest.MFTFuncs._MFStartup();

            //Modifica o tempo minimo que o sistema fica em espera por uma chamada (Sleep).
            MyRenderAudioTest.WinFuncs.CA_TimeBeginPeriod(5);

            //Obtém a frequencia atual do computador.
            MyRenderAudioTest.WinFuncs.CA_QueryPerformanceFrequency(out long OutFrequency);

            //Obtém o dispositivo default de saida de audio do computador atual.
            Resultado = MyRenderAudioTest.EnumeradorAudioDevices.GetDefaultAudioEndpoint(CA_EDataFlow.eRender, CA_ERole.eMultimedia, out ICarenMMDevice OutDevice);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
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
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

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
            MyRenderAudioTest.LeitorAmostras = new CarenMFSourceReader(
                Txb_UrlMusic.Text, 
                MyRenderAudioTest.AtributosLeitor);

            //Verifica se não houve erro
            if (MyRenderAudioTest.LeitorAmostras is null)
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

            //Recupera o tamanho real do buffer que segura os dados a serem renderizados.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.GetBufferSize(out uint CountFramesMaximumBuffer);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao tentar obter o tamanho configurado do buffer que segura os dados a serem renderizados. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Define o tamanho na estrutura.
            MyRenderAudioTest.MaximumFrameBufferRender = CountFramesMaximumBuffer;

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
            MyRenderAudioTest.LeitorAmostras.SetStreamSelection((uint)CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_ALL_STREAMS, false);

            //Define o tipo de midia de saida convertido da estrutura Wav para uma interface ICarenMFMediaType.
            Resultado = MyRenderAudioTest.LeitorAmostras.SetCurrentMediaType(
                (uint)CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, //Define o ID do primeiro fluxo de audio.
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
                (uint)CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, //Define o ID do primeiro fluxo de audio.
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
            Resultado = MyRenderAudioTest.LeitorAmostras.SetStreamSelection((uint)CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM, true);

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
            //Variavel que resultados.
            CarenResult Resultado = new(ResultCode.ER_FAIL, false);

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
                    //Verifica se foi informado para parar o laço.
                    if (StatusProcessAudio == EnumStatusRenderAudio.Stoped)
                        break; //Sai do laço.

                    //Verifica se o fluxo não chegou ao fim
                    if (StatusProcessAudio == EnumStatusRenderAudio.EndOfStream)
                        break; //O fluxo chegou ao fim.

                    //Verifica a quantidade de amostras atuais.
                    //Se o valor for igual ou maior que o maximo não ira requisitar amostras.
                    if (ListBuffer.Count >= SIZE_LIST_BUFFER)
                        goto Done; //Pula para o fim do laço.

                    //Define que está requisitando uma amostra.
                    StatusRequisicaoAmostra = true;

                    //Chama o método para requisitar a proxima amostra de mídia disponivel.
                    Resultado = MyRenderAudioTest.LeitorAmostras.ReadSample(
                        (uint)CA_SOURCE_READER_ID.ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM,
                        CA_MF_SOURCE_READER_CONTROL_FLAG.Zero,
                        ResolverParametro<uint>(0, true),
                        ResolverParametro<CA_MF_SOURCE_READER_FLAG>(0, true),
                        ResolverParametro<long>(0, true),
                        ResolverParametro<ICarenMFSample>(null, true)
                        );

                    //Verifica se não houve erro
                    if (Resultado.StatusCode != ResultCode.SS_OK)
                    {
                        //Falhou ao requisitar a proxima amostra.

                        //Exibe uma mensagem de erro.
                        ShowMensagem("Ocorreu uma falha ao requisitar a proxima amostra ao leitor. Mensagem de erro -> "
                            + Resultado.ObterMensagem((int)Resultado.HResult), true);

                        //Sai do laço
                        break;
                    }

                    //Abre um laço para agurdar o fim do processamento para requisitar a proxima.
                    while (StatusRequisicaoAmostra)
                    {
                        //Faz um delay minimo.
                        await Task.Delay(1);
                    }

                    //Chama um continue para pular o Sleep já que o buffer não está completo.
                    continue;

                Done:;
                    //Faz um Sleep para verificar a proxima amostra.
                    await Task.Delay(5);
                }

                //Define que não está mais processando as amostras.
                ProcessandoAmostras = false;
            });

            //Inicia a task.
            TaskSamplesGet.Start();
        }

        private void IniciarRenderizadorAudio()
        {
            //Cria a task responsável pela renderização dos dados.
            TaskRenderData = new Task(async() =>
            {
                //Define que está processando os dados de audio.
                RenderizandoAmostras = true;

                //Variaveis
                CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);
                MyBufferAudioData BufferRender = null;
                int CountBuffers = 0;
                uint FrameSize = (uint)MyRenderAudioTest.WavAudioOutputInfo.Formato.Canais * MyRenderAudioTest.WavAudioOutputInfo.Formato.BitsPorAmostra;
                FrameSize /= 8;

                //Abre o laço que vai ser responsável por está renderizando.
                while (RenderizandoAmostras)
                {
                    //Verifica se foi informado para parar o laço.
                    if (StatusProcessAudio == EnumStatusRenderAudio.Stoped)
                        break; //Sai do laço.

                    //Verifica se o status informa que deve renderizar.
                    if (StatusProcessAudio != EnumStatusRenderAudio.Rendering)
                        goto Done; //Pula para o fim do laço.

                    //Obtém a quantidade de buffers.
                    CountBuffers = GetCountItensInBuffer();

                    //Verifica a quantidade de buffers e se o fluxo já nao alcançou ao fim.
                    if (CountBuffers == 0 && StatusProcessAudio == EnumStatusRenderAudio.EndOfStream)
                    {
                        //Define fim da reprodução.
                        StatusProcessAudio = EnumStatusRenderAudio.Stoped;

                        //Faz um Sleep para o relogio parar.
                        MyRenderAudioTest.WinFuncs.SleepNativo(1000);

                        //Chama o método para liberar todos as interfaces
                        ReleaseAllInterfaces();

                        //Mostra uma mensagem.
                        ShowMensagem("O fluxo chegou ao fim!");

                        //Sai do laço.
                        break;
                    }

                    //Aguarda o evento de novo buffer. O valor (2500) é o tempo que o método aguarda o evento ser notificado até retornar
                    //um TimeOut, não defina esse valor muito baixo, caso contrario, o laço vai repetir novamente de forma desnecessaria.
                    Resultado = MyRenderAudioTest.WinEventRenderBuffer.AguardarObjetoUnico(2500);

                    //Verifica o resultado
                    if (Resultado.Resultado && Resultado.StatusCode == ResultCode.SS_WAIT_OBJECT_0)
                    {
                        //Evento notificado. 

                        //Obtém o proximo buffer a ser renderizado.
                        BufferRender = GetNextBuffer();

                        //Verifica se o buffer não é invalido
                        if (BufferRender is null)
                            goto Done; //O buffer era invalido.

                        //Abre um laço para verificar se tem espaço suficiente para escrever o buffer no dispositivo
                        //de renderização para reproduzir o audio.
                        while (GetFramesAvailable() < BufferRender.FramesCount)
                        {
                            //Aguarda o dispositivo reproduzir dados para escrever os novos dados no buffer.
                            await Task.Delay(1);
                        }

                        //Recupera o buffer onde será escrito os dados.
                        Resultado = MyRenderAudioTest.AudioRenderShared.GetBuffer(BufferRender.FramesCount, FrameSize, out MyRenderAudioTest.BufferDeviceTemp);

                        //Verifica se não houve erro
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //A operação falhou.

                            //Mostra uma mensagem de erro.
                            ShowMensagem(
                                "Ocorreu uma falha ao obter o buffer de renderização. Mensagem de erro -> "
                                + Resultado.ObterMensagem((int)Resultado.HResult), true);

                            //Sai do método
                            goto Done;
                        }

                        //Escreve os dados no buffer de destino.
                        Resultado = MyRenderAudioTest.BufferDeviceTemp.EscreverDados(BufferRender.BufferNativo, 0, BufferRender.SizeBufferNativo);

                        //Verifica se não houve erro
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //A operação falhou.

                            //Mostra uma mensagem de erro.
                            ShowMensagem(
                                "Ocorreu uma falha ao escrever os dados da amostra no buffer de destino. Mensagem de erro -> "
                                + Resultado.ObterMensagem((int)Resultado.HResult), true);

                            //Sai do método
                            goto Done;
                        }

                        //Libera o buffer para ser renderizado.
                        Resultado = MyRenderAudioTest.AudioRenderShared.ReleaseBuffer(BufferRender.FramesCount, CA_AUDIOCLIENTE_BUFFERFLAGS.Zero);

                        //Verifica se não houve erro
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //A operação falhou.

                            //Mostra uma mensagem de erro.
                            ShowMensagem(
                                "Ocorreu uma falha ao liberar o buffer para ser renderizado pelo dispositivo de reprodução de áudio. Mensagem de erro -> "
                                + Resultado.ObterMensagem((int)Resultado.HResult), true);

                            //Sai do método
                            goto Done;
                        }

                        //Libera o buffer atual.
                        RemoveBufferAndRelease(ref BufferRender);
                    }
                    else if (Resultado.StatusCode == ResultCode.SS_WAIT_TIMEOUT)
                    {
                        //Tempo esgotado.
                    }
                    else
                    {
                        //Deixa continuar.
                    }

                Done:;

                    //Faz um delay minimo.
                    await Task.Delay(3);
                }

                //Define que não está mais renderizando as amostras.
                RenderizandoAmostras = false;
            });

            //Inicia a task.
            TaskRenderData.Start();
        }

        public CarenResult Iniciar()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new CarenResult(ResultCode.ER_FAIL, false);

            //Cria a classe de evento para notificação de renderização de amostras.
            MyRenderAudioTest.WinEventRenderBuffer = new CarenWindowsEvent();

            //Cria o evento.
            Resultado = MyRenderAudioTest.WinEventRenderBuffer.CriarEvento(null, false, false, "Evt_RenderAudio");

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao criar o evento de notificação de renderização de amostra. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Cria a task do relogio de notificação de renderização de amostras.
            TaskClockRenderNotify = new Task(() => 
            {
                //Variaveis a serem utilizadas.
                long TickInicialRelogio = 0;
                long TicksTotaisPassados = 0;
                long NanoSegundosTotaisPassados = 0; //Nanosegundo, segundo o SI(Sistema internacional de unidades). 1 segundo = (10 elevado a 9 potencia).
                long TempoApresentacaoEmNS = 0;
                long OutTicksAtuais = 0;
                long AproximacaoNS_Audio = 1000000; //2 ms
                long NextTimestampRender = 0;
                long LastTimeStampRender = -1;

                //Obtém o primeiro tick
                MyRenderAudioTest.WinFuncs.CA_QueryPerformanceCounter(out TickInicialRelogio);

                //Abre o laço responsável pelas notificações.
                while (true)
                {
                    //Obtém o Tick Atual.
                    MyRenderAudioTest.WinFuncs.CA_QueryPerformanceCounter(out OutTicksAtuais);

                    //Calcula a quantiade de ticks desde o inicio.
                    TicksTotaisPassados = (OutTicksAtuais - TickInicialRelogio);

                    //Calcula os nanosegundos totais passados.
                    //Para converter de Ticks para nanossegundos basta mutiplicar: Ticks * 100.
                    NanoSegundosTotaisPassados = TicksTotaisPassados > 0 ? TicksTotaisPassados * 100 : 0;

                    //Verifica se o TimeStamp atual não é valido.
                    if (NextTimestampRender == -1)
                    {
                        //Obtém o proximo stamp a ser renderizado.
                        NextTimestampRender = GetNextTimeStampRender();
                    }    

                    //Converte o tempo de apresentação em Nanossegundos.
                    TempoApresentacaoEmNS = NextTimestampRender > 0 ? NextTimestampRender * 100 : 0;

                    //Verifica se está na hora de renderizar ou quase perto
                    if (TempoApresentacaoEmNS == 0)
                    {
                        //Define o TimeStamp atual como o ultimo timestamp.
                        LastTimeStampRender = NextTimestampRender;

                        //Notifica o cliente para renderizar a amostra.
                        MyRenderAudioTest.WinEventRenderBuffer.SinalizarEvento();

                        MyRenderAudioTest.WinFuncs.SleepNativo(1);

                        //Info Render.
                        Debug.WriteLine($"\r\nAudio - \r\nPresentation Time: {0}\r\nRelogio Time: {0}");

                        //Define que o timestamp é invalido.
                        NextTimestampRender = -1;
                    }
                    else if ((NanoSegundosTotaisPassados + AproximacaoNS_Audio) >= TempoApresentacaoEmNS)
                    {
                        //Define o TimeStamp atual como o ultimo timestamp.
                        LastTimeStampRender = NextTimestampRender;

                        //Notifica o cliente para renderizar a amostra.
                        MyRenderAudioTest.WinEventRenderBuffer.SinalizarEvento();

                        //Info Render.
                        Debug.WriteLine($"\r\nAudio - \r\nPresentation Time: {TempoApresentacaoEmNS}\r\nRelogio Time: {NanoSegundosTotaisPassados}");

                        //Define que o timestamp é invalido.
                        NextTimestampRender = -1;
                    }
                    else
                    {
                        //Deixa o laço continuar.

                    }

                    //Realiza um Sleep.
                    MyRenderAudioTest.WinFuncs.SleepNativo(5);

                    //Verifica se finalizou
                    if (StatusProcessAudio == EnumStatusRenderAudio.Stoped)
                        break;
                }
            });

            //Inicia o dispositivo de reprodução de audio antes de iniciar o relogio de sinalização.
            Resultado = MyRenderAudioTest.AudioClientOutputConfig.Start();

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao iniciar o dispositivo de reprodução de audio. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Inicia o relogio de notificação.
            TaskClockRenderNotify.Start();

            //Define o volume de reprodução
            Resultado = MyRenderAudioTest.AudioVolumeControl.SetMasterVolume(0.5f, null);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Ocorreu uma falha ao definir o volume de audio default. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

            }

            //Define que deve iniciar o processamento.
            StatusProcessAudio = EnumStatusRenderAudio.Rendering;

        Done:;

            //Retorna o resultado das operações.
            return Resultado;
        }

        #endregion

        #region Métodos que controlam o buffer de dados de áudio.
        public int GetCountItensInBuffer()
        {
            //Abre um lock para sincronização de acesso ao buffer.
            lock (ObjSyncBuffer)
            {
                //Retorna a quantidade de buffers.
                return ListBuffer.Count;
            }
        }

        public void AddNewBuffer(ref ICarenMFSample Param_SampleAudio, long Param_TimeStamp)
        {
            //Abre um lock para sincronização de acesso ao buffer.
            lock (ObjSyncBuffer)
            {
                //Novo buffer a ser adicionado.
                MyBufferAudioData NewBuffer = new();

                //Incrementa a quantidade de referencias.
                Param_SampleAudio.AdicionarReferencia();

                //Define os dados base.
                NewBuffer.AudioSample = Param_SampleAudio;
                NewBuffer.TimeStampRender = Param_TimeStamp;

                //Recupera o Media Buffer que contém a matriz de dados de áudio.
                CarenResult Resultado = Param_SampleAudio.ConvertToContiguousBuffer(out NewBuffer.MediaBuffer);

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //A operação falhou.

                    //Libera a referencia adicionada.
                    Param_SampleAudio.LiberarReferencia();

                    //Nula o buffer.
                    NewBuffer = null;

                    //Sai do método
                    goto Done;
                }

                //Recupera o ponteiro para a matriz de dados.
                Resultado = NewBuffer.MediaBuffer.Lock(out NewBuffer.BufferNativo, out _, out NewBuffer.SizeBufferNativo);

                //Verifica se não houve erro
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //A operação falhou.

                    //Libera as referencias adicionadas.
                    NewBuffer.MediaBuffer.LiberarReferencia();
                    Param_SampleAudio.LiberarReferencia();

                    //Nula o buffer.
                    NewBuffer = null;

                    //Sai do método
                    goto Done;
                }

                //Define a quantidade de frames da amostra.
                //A quantiade de frames é definida pela divisão (LarguraBuffer / (Canais * BitsPerSample / 8))
                NewBuffer.FramesCount = (uint)(NewBuffer.SizeBufferNativo / (MyRenderAudioTest.WavAudioOutputInfo.Formato.Canais * MyRenderAudioTest.WavAudioOutputInfo.Formato.BitsPorAmostra / 8));

                //Define o buffer na lista.
                ListBuffer.Add(NewBuffer);

                //Ordena o buffer pelo timestamp(Menor para Maior).
                ListBuffer = ListBuffer.OrderBy(x => x.TimeStampRender).ToList();

            Done:;
            }
        }

        public MyBufferAudioData GetNextBuffer()
        {
            //Abre um lock para sincronização de acesso ao buffer.
            lock (ObjSyncBuffer)
            {
                //Variavel a ser retornada.
                MyBufferAudioData BufferReturn = null;

                //Verifica se tem buffer disponivel.
                if (ListBuffer.Count == 0)
                    goto Done; //Pula para o fim.

                //Obtém o buffer do index 0
                BufferReturn = ListBuffer.ElementAtOrDefault(0);

                //Remove da lista.
                ListBuffer.RemoveAt(0);

            Done:;

                //Retorna
                return BufferReturn;
            }
        }

        public long GetNextTimeStampRender()
        {
            //Abre um lock para sincronização de acesso ao buffer.
            lock (ObjSyncBuffer)
            {
                //Variavel a ser retornada.
                long ProximoTimeStamp = 0;

                //Verifica se contém amostras.
                if (ListBuffer.Count == 0)
                {
                    //Define que não há buffer.
                    ProximoTimeStamp = -1;

                    //Sai do método.
                    goto Done;
                }

                //Obtém o timestamp do proximo buffer.
                ProximoTimeStamp = ListBuffer[0].TimeStampRender;

                Done:;
                //Retorna o valor
                return ProximoTimeStamp;
            }
        }

        public void RemoveBufferAndRelease(ref MyBufferAudioData Param_BufferRemove)
        {
            //Abre um lock para sincronização de acesso ao buffer.
            lock (ObjSyncBuffer)
            {
                //Limpa todos os dados.
                Param_BufferRemove.MediaBuffer.Unlock();
                Param_BufferRemove.MediaBuffer.LiberarReferencia();
                Param_BufferRemove.AudioSample.LiberarReferencia();
                Param_BufferRemove.BufferNativo = null;
                Param_BufferRemove.MediaBuffer = null;
                Param_BufferRemove.AudioSample = null;
                Param_BufferRemove = null;
            }
        }
        #endregion

        #region Eventos
        private void CallbackReadSamples_OnReadSample(
            int Param_HResult, 
            ResultCode Param_ResultadoGeral, 
            CA_SAMPLE_READ_RESULT Param_ResultadoLeitura, 
            CA_MF_SOURCE_READER_FLAG Param_FlagsLeituraAmostra, 
            uint Param_IdFluxo, 
            ulong Param_TimeSpan, 
            ICarenMFSample Param_Amostra)
        {
            try
            {
                //Esse método já é ThreadSafe

                //Verifica os flags da leitura.
                if (Param_FlagsLeituraAmostra == CA_MF_SOURCE_READER_FLAG.NONE)
                {
                    //Nenhum flag foi definido. Nenhuma operação precisa ser realizada.
                }
                else if (Param_FlagsLeituraAmostra == CA_MF_SOURCE_READER_FLAG.MF_SOURCE_READERF_ENDOFSTREAM)
                {
                    //Define que o fluxo chegou ao fim
                    StatusProcessAudio = EnumStatusRenderAudio.EndOfStream;

                    //O final do fluxo foi atingido
                    ShowMensagem("O fim do fluxo foi alcançado!");

                    //Finaliza a operação.
                    goto Done;
                }
                else if (Param_FlagsLeituraAmostra == CA_MF_SOURCE_READER_FLAG.MF_SOURCE_READERF_STREAMTICK)
                {
                    //Lacuna no fluxo.
                }
                else
                {

                }

                //Verifica se a amostra é valida e adiciona no buffer.
                //A amostra pode ser nula mesmo o método tendo sido bem sucedido.
                if (Param_Amostra != null)
                {
                    //Adiciona o buffer
                    AddNewBuffer(ref Param_Amostra, (long)Param_TimeSpan);
                }

            Done:;
            }
            catch (Exception Er)
            {
                //Chama uma mensagem de erro.
                ShowMensagem("Ocorreu uma falha no evento de leitura de amostras. Mensagem de erro -> " + Er.Message, true);
            }
            finally
            {
                //Define que a requisição pode solicitar a proxima amostra se necessário.
                StatusRequisicaoAmostra = false;
            }
        }

        private void CallbackReadSamples_OnFlush(uint Param_FluxoID)
        {
           
        }

        private void CallbackReadSamples_OnEvent(uint Param_FluxoID, ICarenMFMediaEvent Param_CarenMidiaEvent)
        {
            
        }

        private void TrackVolumeMusic_ValueChanged(object sender, EventArgs e)
        {
            //Modifica o volume de audio se disponivel
            if(MyRenderAudioTest.AudioVolumeControl is not null)
            {
                //Define o volume principal do audio.
                MyRenderAudioTest.AudioVolumeControl.SetMasterVolume((float)TrackVolumeMusic.Value / TrackVolumeMusic.Maximum, null);
            }
        }
        #endregion

        #region Utilidades
        public void ShowMensagem(String Mensagem, Boolean ErrorMsg = false)
        {
            MessageBox.Show(Mensagem, "Audio Render Test", MessageBoxButtons.OK, ErrorMsg ? MessageBoxIcon.Error : MessageBoxIcon.Information);
        }

        public void ReleaseAllInterfaces()
        {
            try
            {
                //Abre um While para liberar todas as amostras pendentes.
                while (true)
                {
                    //Verifica se a lista contém amostras ainda pendente.
                    if (ListBuffer is not null && ListBuffer.Count > 0)
                    {
                        //Obtém o buffer a ser removido.
                        MyBufferAudioData TempBuffer = ListBuffer.ElementAt(0);

                        //Remove o buffer.
                        RemoveBufferAndRelease(ref TempBuffer);
                    }
                    else
                    {
                        //Sai do laço.
                        break;
                    }
                }

                //Libera os media types e atributos.
                SafeReleaseInterface(MyRenderAudioTest.AtributosLeitor);
                SafeReleaseInterface(MyRenderAudioTest.AudioTypeSupportedRenderComplete);
                SafeReleaseInterface(MyRenderAudioTest.AudioTypeSupportedRenderPartial);

                //Libera o Callback e o leitor de amostras.
                MyRenderAudioTest.CallbackReadSamples?.UnRegisterCallback();
                SafeReleaseInterface(MyRenderAudioTest.CallbackReadSamples);
                SafeReleaseInterface(MyRenderAudioTest.LeitorAmostras);

                //Libera as APIs da core audio.
                SafeReleaseInterface(MyRenderAudioTest.AudioRenderShared);
                SafeReleaseInterface(MyRenderAudioTest.AudioVolumeControl);
                MyRenderAudioTest.AudioClientOutputConfig.Stop();
                SafeReleaseInterface(MyRenderAudioTest.AudioClientOutputConfig);
                SafeReleaseInterface(MyRenderAudioTest.DefaultAudioOutput);

                //Desliga a plataforma da media foundation.
                MyRenderAudioTest.MFTFuncs._MFShutdown();

                //Reseta o tempo minimo de espera do sistema.
                MyRenderAudioTest.WinFuncs.CA_TimeEndPeriod(5);

                //Libera as classes.
                MyRenderAudioTest.MFTFuncs = null;
                MyRenderAudioTest.WinFuncs = null;
                MyRenderAudioTest.WinEventRenderBuffer?.LiberarEvento();
                MyRenderAudioTest.WinEventRenderBuffer = null;
                MyRenderAudioTest.WavAudioOutputInfo = null;
                MyRenderAudioTest.GuidAudioSession = Guid.Empty;
                MyRenderAudioTest.BufferDeviceTemp = null;
               
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

        public CarenParameterResolver<T> ResolverParametro<T>(T Param_Obj, Boolean Ignorar)
        {
            return new CarenParameterResolver<T>(Param_Obj, Ignorar);
        }

        public uint GetFramesAvailable()
        {
            //Variavel que retorna a quantidade de frames.
            uint CountFrames = 0;

            //Chama um método para obter a quantidade de FRAMES esperando para serem renderizados.
            CarenResult Resultado = MyRenderAudioTest.AudioClientOutputConfig.GetCurrentPadding(out uint FramesPendente);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //A operação falhou.

                //Define erro.
                CountFrames = 0;

                //Mostra uma mensagem de erro.
                ShowMensagem(
                    "Não foi possivel obter a quantidade de frames pendentes. Mensagem de erro -> "
                    + Resultado.ObterMensagem((int)Resultado.HResult), true);

                //Sai do método
                goto Done;
            }

            //Calcula a quantidade de frames disponiveis com base no tamanho do buffer total disponivel.
            CountFrames = MyRenderAudioTest.MaximumFrameBufferRender - FramesPendente;

        Done:;
            //Retorna
            return CountFrames;
        }

        public void SafeReleaseInterface(ICaren Param_Base)
        {
            //Verifica se a interface é valida.
            if(Param_Base is not null)
            {
                //Verifica se é valido e libera o ponteiro.
                if (Param_Base.StatusPonteiro().StatusCode == ResultCode.SS_OK)
                    Param_Base.LiberarReferencia();

                //Chama o finalizador.
                Param_Base.Finalizar();
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

            //Chama o método para iniciar o gerenciador de amostras.
            IniciarGerenciadorAmostras();

            //Chama o método para iniciar o renderizador de amostras.
            IniciarRenderizadorAudio();

            //Chama o método para iniciar a reprodução da musica.
            Resultado = Iniciar();

            //Vefifica se não falhou
            if (Resultado.StatusCode != ResultCode.SS_OK)
                goto Done; //Sai do método.

            Done:;
        }
    }

    public class MyBufferAudioData
    {
        public long TimeStampRender;

        public uint SizeBufferNativo;

        public uint FramesCount;

        public ICarenMFSample AudioSample;

        public ICarenMFMediaBuffer MediaBuffer;

        public ICarenBuffer BufferNativo;
    }
}
