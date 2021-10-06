using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;

//SDK
using CarenRengine;
using CarenRengine.SDKBase.Estruturas;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.GUIDs;
using CarenRengine.CarenCodesStatus;
using CarenRengine.Direct3D11;
using CarenRengine.DXGI;
using CarenRengine.MediaFoundation;
using System.Linq;

namespace CarenDX11Render
{
    /// <summary>
    /// Classe que tem como objetivo demonstrar como utilizar o Direct3D 11 para renderizar em uma janela(Window).
    /// </summary>
    public class CarenDX11Render
    {
        #region Estruturas
        private struct MyDirectXDados
        {
            public ICarenD3D11Device D3D11Device;
            public ICarenD3D11DeviceContext DeviceContext;
            public ICarenDXGIDevice DXGIDevice;
            public ICarenDXGISwapChain1 SwapChainDevice;
            public ICarenD3D11RenderTargetView RenderTargetView;
            public ICarenD3D11DepthStencilView DepthStencilView;
            public ICarenD3D11Texture2D BackBufferTexture;
            public ICarenD3D11Texture2D DepthStencilBufferTexture;
            public ICarenD3D10Multithread MultihreadDevice;
            public ICarenDXGIFactory2 FactoryDXGI;
            public CA_D3D_FEATURE_LEVEL LevelFeature;
            public CA_DXGI_SWAP_CHAIN_DESC1 DescSwapTexture;
            public CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC DescSwapTextureInFullScreen;
            public CA_D3D11_DEPTH_STENCIL_VIEW_DESC DescDepthView;
            public CA_D3D11_TEXTURE2D_DESC DescTextureDepthView;
            public CA_D3D11_VIEWPORT Viewport;
        }

        private struct MyVideoInfo
        {
            public uint Height;
            public uint Width;
            public IntPtr HandleDestRender;
        }

        private struct MyBufferManager
        {
            public List<MyVideoBufferSample> ListSampleBuffers;
            public int MaximumBuffersInList;
            public Object Sync_ListBuffer;
            public uint CountBuffers;
        }

        private struct MyClockRender
        {
            /// <summary>
            /// O tempo que o relogio foi iniciado.
            /// </summary>
            public long PresentationTimeStarted;

            /// <summary>
            /// O tempo de apresentação atual.
            /// </summary>
            public long PresentationTimeElapsed;

            /// <summary>
            /// O buffer para o proximo dado a ser renderizado.
            /// </summary>
            public MyVideoBufferSample NextBuffer;

            /// <summary>
            /// Task resonsável por verificar o relogio e enviar as amostras para renderização.
            /// </summary>
            public Task TaskClock;

            /// <summary>
            /// Classe responsável por acessar o Query Performance.
            /// </summary>
            public WindowsFunctions Relogio;

            /// <summary>
            /// Indica que tem permissão para entrar no laço.
            /// </summary>
            public Boolean PermissionClock;
        }    
        #endregion

        #region Variaveis
        private MyDirectXDados D3DDados = new ();
        private MyVideoInfo VideoInfo = new ();
        private MyBufferManager BufferManager = new();
        private MyClockRender ClockRender = new MyClockRender();
        private Boolean TaskRequestSamples = false;
        #endregion

        #region Declaração de eventos Públicos
        public delegate Boolean DelegateFor_RequestSample();
        /// <summary>
        /// Evento chamado quando o renderizador necessita de mais amostras de vídeo.
        /// </summary>
        public event DelegateFor_RequestSample RequestSample;
        #endregion

        #region Declaração de eventos Privados
        private delegate void DelegateFor_NewSampleReceived(ICarenMFSample Param_Sample);
        /// <summary>
        /// Evento privado que indica que uma nova amostra foi recebida e deve ser adicionada a lista.
        /// </summary>
        private event DelegateFor_NewSampleReceived NewSampleReceived;

        private delegate void DelegateFor_RenderSample(MyVideoBufferSample Param_SampleRender);
        /// <summary>
        /// Evento privado que indica que deve renderizar a amostra informada no parametro.
        /// </summary>
        private event DelegateFor_RenderSample RenderSample;
        #endregion

        #region Inicializadores da classe
        /// <summary>
        /// Inicializa a classe em default. A classe vai criar o Dispositivo (D3D11Device).
        /// </summary>
        /// <param name="Param_HandleDestRender">A handle para a janela(Window) de destino que vai renderizar as imagens.</param>
        public CarenDX11Render(IntPtr Param_HandleDestRender)
        {
            //Define os dados.
            VideoInfo.HandleDestRender = Param_HandleDestRender;

            //Configura os eventos.
            RenderSample += CarenDX11Render_RenderSample;
            NewSampleReceived += CarenDX11Render_NewSampleReceived;

            //Configura o buffer.
            ConfigurarBuffer(10);

            //Chama o método para configurar o renderizador.
            ConfigurarRenderizador();
        }

        /// <summary>
        /// Inicializa a classe permitindo passar o dispositivo(D3D11Device) a ser utilizado.
        /// </summary>
        /// <param name="Param_Device">O dispositivo a ser utilizado. Esse paramêtro não pode ser NULO!</param>
        /// <param name="Param_HandleDestRender">A handle para a janela(Window) de destino que vai renderizar as imagens.</param>
        public CarenDX11Render(ICarenD3D11Device Param_Device, IntPtr Param_HandleDestRender)
        {
            //Define os dados.
            D3DDados.D3D11Device = Param_Device;
            VideoInfo.HandleDestRender = Param_HandleDestRender;

            //Configura os eventos.
            RenderSample += CarenDX11Render_RenderSample;
            NewSampleReceived += CarenDX11Render_NewSampleReceived;

            //Configura o buffer.
            ConfigurarBuffer(10);

            //Chama o método para configurar o renderizador.
            ConfigurarRenderizador();
        }
        #endregion

        #region Métodos publicos
        public void Play()
        { }

        public void Pause()
        { }

        public void Stop()
        { }

        /// <summary>
        /// Envia uma nova amostra ao buffer de amostras.
        /// </summary>
        /// <param name="Param_Amostra">A nova amostra de vídeo a ser adicionada.</param>
        public void SendBuffer(ICarenMFSample Param_Amostra)
        {
            //Invoca o evento para adicionar a nova amostra.
            NewSampleReceived.Invoke(Param_Amostra);
        }

        /// <summary>
        /// Configura a Altura-Largura e o tipo da amostra de vídeo que o renderizador vai receber.
        /// </summary>
        /// <returns></returns>
        public CarenResult ConfigurarRenderizador()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;



        Done:;
            //Retorna o resultado
            return Resultado;
        }
        #endregion



        #region Eventos privados
        private void CarenDX11Render_NewSampleReceived(ICarenMFSample Param_Sample)
        {
            //Chama o método para adicionar a nova amostra.
            AddBuffer(ref Param_Sample);
        }

        private void CarenDX11Render_RenderSample(MyVideoBufferSample Param_SampleRender)
        {
            //Copia os dados para o buffer traseiro.
            CopyBufferToBackBuffer(Param_SampleRender.Texture2D);

            //Renderiza o frame.
            RenderFrame();
        }
        #endregion

        #region Funções para configurar o Renderizador
        /// <summary>
        /// Configura o buffer que vai receber as amostras.
        /// </summary>
        private void ConfigurarBuffer(int Param_CountBuffer)
        {
            //Cria a lista que vai conter os dados.
            BufferManager.ListSampleBuffers = new List<MyVideoBufferSample>(Param_CountBuffer);

            //Cria o sincronizador de acesso ao buffer.
            BufferManager.Sync_ListBuffer = new object();

            //Define a quantidade de buffers como ZERO.
            BufferManager.CountBuffers = 0;

            //Inicializa todos os buffers.
            InitializeBuffers();
        }

        /// <summary>
        /// Método responsável por configurar o renderizador.
        /// </summary>
        private void ConfigurarRenderizador()
        {

        }

        /// <summary>
        /// Task que fica responsável por verificar e requisitar amostras para o usuário.
        /// </summary>
        private void SystemRequestSample()
        {
            //Cria uma task que vai ficar requisitando as amostras.
            Task.Factory.StartNew(async() =>
            {
                //Define que vai requisitar as amostras.
                TaskRequestSamples = true;

                //Abre o laço para ficar requisitando.
                while (TaskRequestSamples)
                {
                    //Verifica a quantidade de amostras.
                    if (BufferManager.CountBuffers <= 5)
                    {
                        //Invoca o evento para o usuário enviar uma nova amostra.
                        Boolean EndSamples = RequestSample.Invoke();

                        //Verifica se deve parar de requisitar os dados.
                        if(EndSamples)
                        {
                            //Define que a task de requisição deve parar.
                            TaskRequestSamples = false;

                            //Sai do laço.
                            break;
                        }
                    }
                    else
                    {
                        //Realiza um delay.
                        await Task.Delay(50);
                    }
                }
            });
        }
        #endregion

        #region Funções para renderização do Video.
        /// <summary>
        /// Método responsável por copiar os dados do buffer de origem para o Back Buffer a ser apresentado.
        /// </summary>
        /// <param name="Param_ResourceCopy">O recurso a ser copiado. Esse parametro deve ser uma ICarenD3D11Texture2D.</param>
        /// <returns></returns>
        private CarenResult CopyBufferToBackBuffer(ICarenD3D11Resource Param_ResourceCopy)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new ();

            //Chama o método para copiar o recurso de origem para o de destino.
            Resultado = D3DDados.DeviceContext.CopySubresourceRegion(D3DDados.BackBufferTexture, 0, 0, 0, 0, Param_ResourceCopy, 0, null);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Sai do método
                goto Done;
            }

        Done:;
            //Retorna o resultado
            return Resultado;
        }

        /// <summary>
        /// Método responsável por fazer a renderização do BackBuffer que contém os frames a serem apresentados.
        /// </summary>
        /// <returns></returns>
        private CarenResult RenderFrame()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Chama o método que vai apresentar o Frame do Buffer traseiro para a handle especificada.
            Resultado = D3DDados.SwapChainDevice.Present(0, CA_DXGI_PRESENT.Zero);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Sai do método
                goto Done;
            }

        Done:;
            //Retorna o resultado
            return Resultado;
        }
        #endregion

        #region Relogio de renderização.
        private void IniciarRelogio()
        {
            //Cria a task que vai ficar processando
            ClockRender.TaskClock = new Task(() =>
            {
                //Variaveis
                long AproximacaoNS_Video = 2000000; //2 ms

                //Cria a classe de funções
                ClockRender.Relogio = new WindowsFunctions();

                //Indica que vai entrar no laço.
                ClockRender.PermissionClock = true;

                //Obtém o tick de inicio do relogio.
                ClockRender.Relogio._QueryPerformanceCounter(out ClockRender.PresentationTimeStarted);

                //Abre o laço para ficar processando.
                while (ClockRender.PermissionClock)
                {
                    //Obtém o tick atual do relogio.
                    ClockRender.Relogio._QueryPerformanceCounter(out long OutTickAtual);

                    //Verifica e calcula o tempo em nanossegundos.
                    if(OutTickAtual > 0)
                    {
                        //Calcula a quantidade de tempo passada desde o inicio e converte em nanossegundos.
                        ClockRender.PresentationTimeElapsed = (OutTickAtual - ClockRender.PresentationTimeStarted) * 100;
                    }
                    else
                    {
                        //Tick invalido
                        goto Done;
                    }

                    //Obtém o buffer a ser renderizado se nulo
                    if (ClockRender.NextBuffer is null)
                    {
                        //Obtém o proximo buffer.
                        ClockRender.NextBuffer = GetNextBuffer();
                    }

                    //Verifica se o buffer é valido e verifica seu tempo de apresentação.
                    if(ClockRender.NextBuffer is not null)
                    {
                        //Verifica o tempo do relogio com o tempo do buffer
                        if(ClockRender.NextBuffer.PresentationTime == 0)
                        {
                            //O buffer é renderizado no inicio.
                            RenderSample.Invoke(ClockRender.NextBuffer);

                            //Libera o buffer.
                            LiberarBuffer(ref ClockRender.NextBuffer);

                            //Nula.
                            ClockRender.NextBuffer = null;
                        }
                        else if( (ClockRender.NextBuffer.PresentationTime + AproximacaoNS_Video) >= ClockRender.PresentationTimeElapsed)
                        {
                            //Invoca o evento interno para renderizar o buffer.
                            RenderSample.Invoke(ClockRender.NextBuffer);

                            //Libera o buffer.
                            LiberarBuffer(ref ClockRender.NextBuffer);

                            //Nula.
                            ClockRender.NextBuffer = null;
                        }
                        else
                        {
                            //o relogio não alcançou o tempo de renderização da amostra ainda.
                        }
                    }
                    else
                    {
                        //Não há amostra para ser renderizada ou houve erro.
                        ClockRender.Relogio.SleepNativo(5);
                    }

                Done:;
                }
            });

            //Inicia a Task.
            ClockRender.TaskClock.Start();
        }
        #endregion

        #region Métodos para criar e configurar o D3D11
        /// <summary>
        /// Cria um novo dispositivo D3D11.
        /// </summary>
        /// <returns></returns>
        private CarenResult CreateD3D11Device()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Variaveis a serem utilizadas.
            CA_D3D_FEATURE_LEVEL OutFeatureLevel = CA_D3D_FEATURE_LEVEL.D3D_FEATURE_LEVEL_10_0;
            CA_D3D_FEATURE_LEVEL[] LevsFeature = new CA_D3D_FEATURE_LEVEL[] {
                CA_D3D_FEATURE_LEVEL.D3D_FEATURE_LEVEL_11_1,
                CA_D3D_FEATURE_LEVEL.D3D_FEATURE_LEVEL_11_0,
                CA_D3D_FEATURE_LEVEL.D3D_FEATURE_LEVEL_10_1,
                CA_D3D_FEATURE_LEVEL.D3D_FEATURE_LEVEL_10_0};

            //Cria a interface que vai receber o ponteiro para o DeviceContext.
            D3DDados.DeviceContext = new CarenD3D11DeviceContext();

            //Cria o dispositivo.
            D3DDados.D3D11Device = new CarenD3D11Device(
                 null,
                 LevsFeature,
                 CA_D3D_DRIVER_TYPE.D3D_DRIVER_TYPE_HARDWARE,
                 CA_D3D11_CREATE_DEVICE_FLAG.D3D11_CREATE_DEVICE_BGRA_SUPPORT | CA_D3D11_CREATE_DEVICE_FLAG.D3D11_CREATE_DEVICE_VIDEO_SUPPORT,
                 out OutFeatureLevel,
                 new CarenParamResolver<ICarenD3D11DeviceContext>(D3DDados.DeviceContext, false));

            //Verifica se não houve erro
            if (D3DDados.D3D11Device.StatusPonteiro().StatusCode != ResultCode.SS_OK)
            {
                //Chama uma exceção
                CallException("Ocorreu uma falha ao tentar criar um dispositivo D3D11.");

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado = ResultCode.SS_OK;

        Done:;
            //Retorna
            return Resultado;
        }

        /// <summary>
        /// Método responsável por configurar o Multithread para o dispositivo D3D11.
        /// </summary>
        private CarenResult ConfigureMulthreadDevice()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Cria a interface de multihread para receber o ponteiro a parti do D3D11
            D3DDados.MultihreadDevice = new CarenD3D10Multithread();

            //Chama o método para recuperar um ponteiro para a interface
            Resultado = D3DDados.D3D11Device.ConsultarInterface(GUIDs_InterfacesDirect3D10.IID_ID3D10Multithread, D3DDados.MultihreadDevice);

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Ocorreu uma falha..

                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Sai do método
                goto Done;
            }

            //Define que o dispositivo vai funcionar em Multithread
            D3DDados.MultihreadDevice.SetMultithreadProtected(true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Método responsável por criar e configurar o SwapChain para o Dispositivo D3D11.
        /// </summary>
        /// <param name="Param_HeightTexture">A altura da textura, geralmente, esse valor é igual a altura do video.</param>
        /// <param name="Param_WidthTexture">A largura da textura, geralmente, esse valor é igual a largura do video.</param>
        /// <param name="Param_RefrestRate">Uma estrutura (CA_DXGI_RATIONAL) que vai definir o frame rate e atualização.</param>
        /// <param name="Param_DescTexture">Uma estrutura (CA_DXGI_SWAP_CHAIN_DESC) que descreve o tipo da textura para a superfice 
        /// do video a ser criada ou NULO.</param>
        /// <param name="Param_DescTextureFullScreen">Uma estrutura (CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC) que descreve o tipo da textura 
        /// para a superfice do video em FullScreen a ser criada ou NULO.</param>
        /// <returns></returns>
        private CarenResult CreateSwapChain(
            uint Param_HeightTexture,
            uint Param_WidthTexture,
            CA_DXGI_RATIONAL Param_RefrestRate,
            CA_DXGI_SWAP_CHAIN_DESC Param_DescTexture = null,
            CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC Param_DescTextureFullScreen = null
            )
        {
            //Variavel a ser retornada.
            CarenResult Resultado =  ResultCode.ER_FAIL;

            //Verifica se informou a estrutura do RefreshRate
            if(Param_RefrestRate is null)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção.
                CallException("O parâmetro (Param_RefrestRate) não pode ser NULO!");
            }

            //Verifica se as estruturas de descrição estão NULAS e define como default.
            if (Param_DescTexture is null)
            {
                //Cria e configura como default a estrutura.
                D3DDados.DescSwapTexture = new CA_DXGI_SWAP_CHAIN_DESC1()
                {
                    BufferCount = 2,
                    BufferUsage = CA_DXGI_USAGE.CA_DXGI_USAGE_RENDER_TARGET_OUTPUT | CA_DXGI_USAGE.CA_DXGI_USAGE_SHADER_INPUT,
                    Flags = 0,
                    SwapEffect = CA_DXGI_SWAP_EFFECT.CA_DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
                    AlphaMode = CA_DXGI_ALPHA_MODE.DXGI_ALPHA_MODE_IGNORE,
                    Format = CA_DXGI_FORMAT.DXGI_FORMAT_B8G8R8A8_UNORM,
                    Height = Param_HeightTexture,
                    Width = Param_WidthTexture,
                    Scaling = CA_DXGI_SCALING.DXGI_SCALING_STRETCH,
                    Stereo = false,
                    SampleDesc = new CA_DXGI_SAMPLE_DESC() { Count = 1, Quality = 0 },
                };
            }
            if (Param_DescTextureFullScreen is null)
            {
                //Cria e configura como default a estrutura.
                D3DDados.DescSwapTextureInFullScreen = new CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC()
                {
                    Scaling = CA_DXGI_MODE_SCALING.CA_DXGI_MODE_SCALING_STRETCHED,
                    ScanlineOrdering = CA_DXGI_MODE_SCANLINE_ORDER.CA_DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE,
                    Windowed = true,
                    RefreshRate = Param_RefrestRate
                };
            }

            //Cria a fabrica
            D3DDados.FactoryDXGI = new CarenDXGIFactory2(0); //Define 0 para não solicitar a dll de Debug do dxgi.

            //Verifica se não houve erro.
            if (D3DDados.FactoryDXGI.StatusPonteiro().StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar uma fabrica do DXGI!");

                //Sai do método
                goto Done;
            }

            //Cria o SwapChain para a handle que vai receber os dados renderizados
            Resultado = D3DDados.FactoryDXGI.CreateSwapChainForHwnd(
                D3DDados.D3D11Device,
                VideoInfo.HandleDestRender,
                D3DDados.DescSwapTexture,
                D3DDados.DescSwapTextureInFullScreen,
                null,
                out D3DDados.SwapChainDevice);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar o SwapChain!");

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private CarenResult CreateBackBuffer()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Cria uma instância da interface de buffer.
            D3DDados.BackBufferTexture = new CarenD3D11Texture2D();

            //Chama o método para criar um BackBuffer.
            Resultado = D3DDados.SwapChainDevice.GetBuffer(0, GUIDs_InterfacesDirect3D11.IID_ID3D11Texture2D, D3DDados.BackBufferTexture);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar um BackBuffer!");

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private CarenResult CreateRenderTargetView()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Chama o método para criar a interface do Render Target.
            Resultado = D3DDados.D3D11Device.CreateRenderTargetView(D3DDados.BackBufferTexture, null, false, out D3DDados.RenderTargetView);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar o RenderTarget!");

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        private CarenResult CreateDepthStencilView()
        {
            //Cria e configura a descrição do buffer stencil.
            D3DDados.DescTextureDepthView = new CA_D3D11_TEXTURE2D_DESC()
            {
                Formato = CA_DXGI_FORMAT.DXGI_FORMAT_D24_UNORM_S8_UINT,
                BindFlags = CA_D3D11_BIND_FLAG.D3D11_BIND_DEPTH_STENCIL,
                Usage = CA_D3D11_USAGE.D3D11_USAGE_DEFAULT,
                Height = D3DDados.DescSwapTexture.Height,
                Width = D3DDados.DescSwapTexture.Width,
                MipLevels = 1,
                ArraySize = 1,
                SampleDesc = new CA_DXGI_SAMPLE_DESC() { Count = 1, Quality = 0 },
                CPUAccessFlags = 0,
                MiscFlags = 0
            };
            //Cria e configura a descrião do Depth View Stencil.
            D3DDados.DescDepthView = new CA_D3D11_DEPTH_STENCIL_VIEW_DESC()
            {
                Formato = CA_DXGI_FORMAT.DXGI_FORMAT_D24_UNORM_S8_UINT,
                ViewDimensao = CA_D3D11_DSV_DIMENSION.D3D11_DSV_DIMENSION_TEXTURE2D,
                Textura2D = new CA_D3D11_TEX2D_DSV() { MipSlice = 0 }
            };

            //Chama o método para criar a textura
            CarenResult Resultado = D3DDados.D3D11Device.CreateTexture2D(
                ref D3DDados.DescTextureDepthView, 
                null, 
                0,
                false, 
                out D3DDados.DepthStencilBufferTexture);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar o buffer para o Depth Stencil View!");

                //Sai do método
                goto Done;
            }

            //Cria o Depth View.
            Resultado = D3DDados.D3D11Device.CreateDepthStencilView(
                D3DDados.DepthStencilBufferTexture, 
                ref D3DDados.DescDepthView, 
                false, 
                out D3DDados.DepthStencilView);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção ao tentar criar o Depth Stencil View!");

                //Sai do método
                goto Done;
            }

            //Define sucesso.
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Define ou atualiza uma viewport.
        /// </summary>
        /// <param name="Param_NewViewport">A nova viewport a ser definida ou NULO. Se NULO, será configurar como default.</param>
        /// <returns></returns>
        public CarenResult ConfigurarViewport(CA_D3D11_VIEWPORT Param_NewViewport)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Verifica se a viewport informado é NULO e configura como default.
            if(Param_NewViewport is null)
            {
                //Cria a estrutura default.
                D3DDados.Viewport = new CA_D3D11_VIEWPORT()
                {
                    CantoSuperiorEsquerdoX = 0.0f,
                    CantoSuperiorEsquerdoY = 0.0f,
                    ProfundidadeMaxima = 1,
                    ProfundidadeMinima = 0
                };
            }

            //Define altura e largura segundo o  buffer traseiro.
            D3DDados.Viewport.Altura = D3DDados.DescSwapTexture.Height;
            D3DDados.Viewport.Largura = D3DDados.DescSwapTexture.Width;

            //Define a viewport para o dispositivo
            Resultado = D3DDados.DeviceContext.RSSetViewports(1, new CA_D3D11_VIEWPORT[1] { D3DDados.Viewport });

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção tentar definir ou ajustar as definições da Viewport!");

                //Sai do método
                goto Done;
            }

            //Define sucesso.
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public CarenResult SetRenderTargetDest()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = ResultCode.ER_FAIL;

            //Chama o método para criar a interface do Render Target.
            Resultado = D3DDados.DeviceContext.OMSetRenderTargets(1, new ICarenD3D11RenderTargetView[1] { D3DDados.RenderTargetView }, D3DDados.DepthStencilView);

            //Verifica se não houve erro.
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Libera todas as interfaces.
                ReleaseAllInterfaces();

                //Chama uma exceção
                CallException("Ocorreu uma exceção tentar definir a interface RenderTargetView no contexto do Dispositivo do D3D11!");

                //Sai do método
                goto Done;
            }

            //Define sucesso na operação
            Resultado.AdicionarCodigo(ResultCode.SS_OK, true);

        Done:;
            //Retorna o resultado.
            return Resultado;
        }
        #endregion

        #region Métodos responsáveis por gerenciar a lista de buffer.
        /// <summary>
        /// Inicializa todos os buffers.
        /// </summary>
        private void InitializeBuffers()
        {
            //Abre um for para inicializar os buffers.
            for (int i = 0; i < BufferManager.MaximumBuffersInList; i++)
            {
                //Cria o buffer.
                MyVideoBufferSample newVideoSample = new MyVideoBufferSample()
                {
                    IsFree = true,
                    IsOperating = false
                };

                //Adiciona na lista.
                BufferManager.ListSampleBuffers.Add(newVideoSample);
            }
        }

        /// <summary>
        /// Método responsável por retornar a quatidade total de buffrs livres.
        /// </summary>
        /// <returns></returns>
        public Int32 GetAllEmptyBuffer()
        {
            lock (BufferManager.Sync_ListBuffer)
            {
                //Variavel a ser retornada.
                Int32 TotalBufferLivre = 0;

                //Executa uma função para verificar
                for (int i = 0; i < BufferManager.MaximumBuffersInList; i++)
                {
                    //Verifica se o buffer está livre e incrementa a variavel.
                    if (BufferManager.ListSampleBuffers[i].IsFree)
                        TotalBufferLivre++;
                }

                //Retorna
                return TotalBufferLivre;
            }
        }

        /// <summary>
        /// Método responsável por retornar um buffer livre.
        /// </summary>
        /// <returns></returns>
        private MyVideoBufferSample GetClassBufferFree()
        {
            return BufferManager.ListSampleBuffers.FirstOrDefault(new Func<MyVideoBufferSample, bool>((x => x.IsFree)));
        }

        private void AddBuffer(ref ICarenMFSample Param_Amostra)
        {
            //Sincroniza o acesso a lista de buffers.
            lock (BufferManager.Sync_ListBuffer)
            {
                //Obtém o buffer a ser preenchido.
                MyVideoBufferSample AddBuffer = GetClassBufferFree();

                //Adiciona uma referencia a amostra.
                Param_Amostra.AdicionarReferencia();

                //Define os dados.
                AddBuffer.Amostra = Param_Amostra;
                AddBuffer.IsFree = false;
                AddBuffer.IsOperating = false;

                //Recupera o PresentionTime.
                AddBuffer.Amostra.GetSampleTime(out AddBuffer.PresentationTime);

                //Variveis
                ICarenD3D11Texture2D RecursoTextura2D = new CarenD3D11Texture2D();
                ICarenMFDXGIBuffer DxgiBuffer = new CarenMFDXGIBuffer();
                ICarenMFMediaBuffer OutMediaBuffer = null;

                //Obtém o Media buffer.
                CarenResult Resultado = Param_Amostra.ConvertToContiguousBuffer(out OutMediaBuffer);

                //Verifica o resultado.
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Chama uma exceção.
                    throw new Exception("Falhou ao tentar obter a interface do Media Buffer.");
                }

                //Obtém o DXGI Buffer.
                Resultado = OutMediaBuffer.ConsultarInterface(GUIDs_InterfacesMediaFoundation.IID_IMFDXGIBuffer, DxgiBuffer);

                //Verifica o resultado.
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Chama uma exceção.
                    throw new Exception("Falhou ao tentar obter a interface do Buffer DXGI..");
                }

                //Obtém a textura 2D.
                Resultado = DxgiBuffer.GetResource(GUIDs_InterfacesDirect3D11.IID_ID3D11Texture2D, RecursoTextura2D);

                //Verifica o resultado.
                if (Resultado.StatusCode != ResultCode.SS_OK)
                {
                    //Chama uma exceção.
                    throw new Exception("Falhou ao tentar obter a interface para a textura 2D.");
                }

                //Adiciona uma referencia a Textura 2D.
                RecursoTextura2D.AdicionarReferencia();

                //Adiciona os dados na amostra.
                AddBuffer.Texture2D = RecursoTextura2D;

                //Incrementa a quantidade de buffers.
                BufferManager.CountBuffers++;

                //Libera algumas referencias que não seram usadas.
                if (DxgiBuffer is not null)
                {
                    //Libera os dados.
                    DxgiBuffer.LiberarReferencia();
                    DxgiBuffer = null;
                }
                if (OutMediaBuffer is not null)
                {
                    //Libera os dados.
                    OutMediaBuffer.LiberarReferencia();
                    OutMediaBuffer = null;
                }
            }
        }

        private MyVideoBufferSample GetNextBuffer()
        {
            //Sincroniza o acesso a lista de buffers.
            lock (BufferManager.Sync_ListBuffer)
            {
                //Variavel a ser retornada.
                MyVideoBufferSample NextBuffer = null;

                //Variavel que guarda o tempo da apresentação.
                long LastPresentationTime = 0;

                //Obtém o proximo buffer de menor tempo se houver
                for (int i = 0; i < BufferManager.MaximumBuffersInList; i++)
                {
                    //Verifica se a amostra é valida.
                    if (!BufferManager.ListSampleBuffers[i].IsFree && !BufferManager.ListSampleBuffers[i].IsOperating)
                    {
                        //Obtém o tempo de apresentação.
                        LastPresentationTime = BufferManager.ListSampleBuffers[i].PresentationTime;

                        //Faz um for para procurar um valor menor.
                        for (int a = 0; a < BufferManager.MaximumBuffersInList; a++)
                        {
                            if (BufferManager.ListSampleBuffers[a].PresentationTime < LastPresentationTime && BufferManager.ListSampleBuffers[a].Amostra is not null)
                                break;
                            else if (a == (BufferManager.MaximumBuffersInList) - 1)
                                NextBuffer = BufferManager.ListSampleBuffers.ElementAtOrDefault(i);
                        }

                        //Verifica se encontrou o buffer.
                        if (NextBuffer is not null)
                        {
                            //Define que o buffer está ocupado
                            NextBuffer.IsOperating = true;

                            //Sai do laço
                            break;
                        }
                    }
                }

                //Retorna o reusltado
                return NextBuffer;
            }
        }

        private void LiberarBuffer(ref MyVideoBufferSample Param_VideoSample)
        {
            SafeReleaseInterface(Param_VideoSample.Texture2D);
            SafeReleaseInterface(Param_VideoSample.Amostra);
            Param_VideoSample.PresentationTime = 0;
            Param_VideoSample.IsOperating = false;
            Param_VideoSample.IsFree = true;

            //Diminui a quantidade de buffers na lista.
            BufferManager.CountBuffers++;
        }
        #endregion

        #region Métodos auxiliares
        private void CallException(String Param_Mensagem)
        {
            throw new Exception(Param_Mensagem);
        }

        private void ReleaseAllInterfaces()
        { }

        private void SafeReleaseInterface(ICaren Param_Base)
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

    internal class MyVideoBufferSample
    {
        /// <summary>
        /// Contém a amostra de vídeo.
        /// </summary>
        public ICarenMFSample Amostra;

        /// <summary>
        /// Contém a textura 2d da amostra.
        /// </summary>
        public ICarenD3D11Texture2D Texture2D;

        /// <summary>
        /// O tempo de apresentação que o buffer deve ser renderizado em nanossegundos já convertido.
        /// </summary>
        public long PresentationTime;

        /// <summary>
        /// Inidica se esse buffer está livre.
        /// </summary>
        public bool IsFree;

        /// <summary>
        /// Inidica se o buffer está sendo usado no momento.
        /// </summary>
        public bool IsOperating;
    }
}
