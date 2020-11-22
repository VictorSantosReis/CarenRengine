/*
Copyright 2020 Victor Santos Reis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#pragma once
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../Caren/CarenBuffer.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes)
/// </summary>
public ref class CarenMFVideoDisplayControl :public ICarenMFVideoDisplayControl
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFVideoDisplayControl).
	IMFVideoDisplayControl* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFVideoDisplayControl();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}



	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////

	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();





	//Métodos da interface ICarenMFVideoDisplayControl
public:
	/// <summary>
	/// (GetAspectRatioMode) - Consulta como o processador de vídeo avançado (EVR) lida com a relação de aspecto da fonte de vídeo.
	/// </summary>
	/// <param name="Param_Out_AspectRatio">Recebe um ou mais bit de sinalizadores da enumeração: CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE</param>
	virtual CarenResult ObterAspectRatio([Out] Enumeracoes::CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE% Param_Out_AspectRatio);

	/// <summary>
	/// (GetBorderColor) - Obtém a cor da borda para o vídeo.
	/// </summary>
	/// <param name="Param_Out_CorHexadecimalBorda">Recebe o valor que especifica em hexadecimal, uma cor RGB.</param>
	virtual CarenResult ObterCorBorda([Out] UInt32% Param_Out_CorHexadecimalBorda);

	/// <summary>
	/// (GetCurrentImage) - Obtém uma cópia da imagem atual sendo exibida pelo processador de vídeo.
	/// </summary>
	/// <param name="Param_Out_BimapInfoHeader">Recebe uma estrutura que contém uma descrição do bitmap</param>
	/// <param name="Param_Out_BufferImagem">Interface que contém um buffer que contém um bitmap independente de dispositivo do Windows compactado (DIB).
	/// O chamador deve liberar a memória para o bitmap chamando: CoTaskMemFree</param>
	/// <param name="Param_Out_BufferLargura">Contém a largura do buffer retornado em: Param_Out_BufferImagem.</param>
	/// <param name="Param_Out_TimeStamp">Recebe o carimbo de data/hora da imagem capturada. O valor é em unidades de 100 nanosegundos.</param>
	virtual CarenResult ObterCopiaImagemAtual(
		[Out] Estruturas::CA_BITMAPINFOHEADER^% Param_Out_BimapInfoHeader,
		[Out] ICarenBuffer^% Param_Out_BufferImagem,
		[Out] UInt32% Param_Out_BufferLargura,
		[Out] Int64% Param_Out_TimeStamp);

	/// <summary>
	/// (GetFullscreen) - Consulta se o processador de vídeo avançado (EVR) está atualmente no modo de tela cheia.
	/// </summary>
	/// <param name="Param_Out_FullScreen">Recebe o valor que define se o vídeo está sendo renderizado em FullScreen.</param>
	virtual CarenResult ObterEstadoFullScreen([Out] Boolean% Param_Out_FullScreen);

	/// <summary>
	/// (GetIdealVideoSize) - Obtém o intervalo de tamanhos, que o processador de vídeo avançado (EVR) pode exibir sem degradar 
	/// significativamente a qualidade de imagem ou o desempenho.
	/// </summary>
	/// <param name="Param_Out_Minimo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Minimos) da Largura e Altura (Ideias) para o vídeo.</param>
	/// <param name="Param_Out_Maximo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Maximos) da Largura e Altura (Ideias) para o vídeo.</param>
	virtual CarenResult ObterSizeIdealVideo(
		[Out] Estruturas::CA_SIZE^% Param_Out_Minimo_VideoSizeIdeal,
		[Out] Estruturas::CA_SIZE^% Param_Out_Maximo_VideoSizeIdeal);

	/// <summary>
	/// (GetNativeVideoSize) - Obtém o tamanho e a taxa de proporção do vídeo, antes de qualquer alongamento pelo (Processador de Vídeo).
	/// </summary>
	/// <param name="Param_Out_VideoSize">Recebe a estrutura que contém a Largura e Altura (Nativas) para o vídeo.</param>
	/// <param name="Param_Out_TaxaProporcaoVideo">Recebe a estrutura que contém a (Taxa de proporção) do vídeo.</param>
	virtual CarenResult ObterSizeNativoVideo(
		[Out] Estruturas::CA_SIZE^% Param_Out_VideoSize,
		[Out] Estruturas::CA_SIZE^% Param_Out_TaxaProporcaoVideo);

	/// <summary>
	/// (GetRenderingPrefs) - Obtém várias configurações de processamento de vídeo.
	/// </summary>
	/// <param name="Param_Out_Sinalizadores">Recebe um bit ou zero ou mais sinalizadores da enumeração: CA_VIDEO_RENDER_CONFIGURACOES</param>
	virtual CarenResult ObterConfiguraçãoRenderização([Out] Enumeracoes::CA_VIDEO_RENDER_CONFIGURACOES% Param_Out_Sinalizadores);

	/// <summary>
	/// (GetVideoPosition) - Obtém os retângulos de origem e de destino para o Vídeo.
	/// </summary>
	/// <param name="Param_Out_RetanguloNormalized">Recebe uma estrutura que contém o retângulo de origem.</param>
	/// <param name="Param_Out_RetanguloDestino">Recebe uma estrutura com o retângulo de destino atual.</param>
	virtual CarenResult ObterPosiçãoVideo(
		[Out] Estruturas::CA_MFVideoNormalizedRect^% Param_Out_RetanguloNormalized,
		[Out] Estruturas::CA_RECT^% Param_Out_RetanguloDestino);

	/// <summary>
	/// (GetVideoWindow) - Obtém a janela de recorte para o vídeo. A janela de recorte é a (Handle) do componente que está
	/// hospedando a renderização do vídeo para o usuário.
	/// </summary>
	/// <param name="Param_Out_HandleJanela">Recebe a handle da janela que a qual o vídeo está sendo renderizado.</param>
	virtual CarenResult ObterJanelaVideo([Out] IntPtr% Param_Out_HandleJanela);

	/// <summary>
	/// (RepaintSuperfice) - Redesenha o quadro de vídeo atual. Chame esse método sempre que a interface do usuário
	/// sofre uma atualização da interface.
	/// </summary>
	virtual CarenResult RedesenharSuperfice();

	/// <summary>
	/// (SetAspectRatioMode) - Especifica como o processador de vídeo avançado (EVR) lida com a relação de aspecto 
	/// da fonte de vídeo.
	/// </summary>
	/// <param name="Param_AspectRatio">Bit a bit ou de um ou mais sinalizadores da enumeração: CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE</param>
	virtual CarenResult DefinirModoAspectRatio(Enumeracoes::CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE Param_AspectRatio);

	/// <summary>
	/// (SetBorderColor) - Define a cor da borda para o vídeo.
	/// </summary>
	/// <param name="Param_ColorRef">Especifica a cor da borda como um valor UInt32</param>
	virtual CarenResult DefinirCorBorda(UInt32 Param_ColorRef);

	/// <summary>
	/// [Esta API não é suportada e pode ser alterada ou indisponível no futuro.]
	/// (SetFullScreen) - Define o modo de renderização de tela cheia.
	/// Para implementar a reprodução em tela inteira, um aplicativo deve simplesmente redimensionar a janela de vídeo para cobrir toda a área do monitor.Também definir a janela
	/// para ser uma (Janela Superior), para que o aplicativo possa receber todas as mensagens de clique do mouse.
	/// </summary>
	/// <param name="Param_EstadoFullScreen">Se true, o renderizador de vídeo aprimorado (EVR) usará o modo de tela inteira. Se false, o EVR desenha o vídeo na 
	/// janela de recorte fornecido pelo aplicativo.</param>
	virtual CarenResult DefinirFullScreen(Boolean Param_EstadoFullScreen);

	/// <summary>
	/// (SetRenderingPrefs)Define preferências diversas, relacionadas com a processamento de vídeo.
	/// </summary>
	virtual CarenResult DefinirConfiguraçãoRenderização(Enumeracoes::CA_VIDEO_RENDER_CONFIGURACOES Param_RenderConfigs);

	/// <summary>
	/// (SetVideoPosition) - Define os retângulos de origem e de destino para o vídeo.
	/// O retângulo de origem define qual parte do vídeo é exibida. Ele é especificado em coordenadas normalizadas. Para obter mais informações, 
	/// consulte estrutura MFVideoNormalizedRect. Para exibir a imagem de vídeo inteira, defina o retângulo de origem como {0, 0, 1, 1}. O retângulo de origem padrão é {0, 0, 1, 1}.
	/// O retângulo de destino define um retângulo dentro da janela de recorte onde o vídeo é exibido. Ele é especificado em pixels, em relação à área do cliente da janela.
	/// Para preencher a janela inteira, defina o retângulo de destino como {0, 0, Largura, Altura}, onde Largura e Altura são dimensões da área do cliente da janela. O retângulo 
	/// de destino padrão é {0, 0, 0, 0}.
	/// </summary>
	/// <param name="Param_RetanguloNormalized">Estrutura que especifica o retângulo origem. Este parâmetro pode ser NULO. Se este parâmetro é NULO, o 
	/// retângulo de origem não é alterado.</param>
	/// <param name="Param_RetanguloDestino">Especifica o retângulo de destino. Este parâmetro pode ser NULL. Se este parâmetro é NULL, o retângulo 
	/// de destino não é alterado.</param>
	virtual CarenResult DefinirPosiçãoVideo(
		Estruturas::CA_MFVideoNormalizedRect^ Param_RetanguloNormalized,
		Estruturas::CA_RECT^ Param_RetanguloDestino);

	/// <summary>
	/// (SetVideoWindow) - Define a janela de recorte para o vídeo. Está é a janela que vai hospedar o vídeo que será
	/// renderizado para visualização do usuário. A Janela refere-se a (Handle) de um componente na GUI
	/// do usuário.
	/// </summary>
	/// <param name="Param_JanelaVideo"></param>
	virtual CarenResult DefinirJanelaVideo(IntPtr Param_JanelaVideo);
};

