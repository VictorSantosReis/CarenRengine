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
#include "../SDK_Direct2D.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenD2D1DCRenderTarget.h"
#include "CarenD2D1RenderTarget.h"
#include "CarenD2D1HwndRenderTarget.h"
#include "CarenD2D1DrawingStateBlock.h"
#include "CarenD2D1Geometry.h"
#include "CarenD2D1TransformedGeometry.h"
#include "CarenD2D1RoundedRectangleGeometry.h"
#include "CarenD2D1RectangleGeometry.h"
#include "CarenD2D1EllipseGeometry.h"
#include "CarenD2D1PathGeometry.h"
#include "CarenD2D1GeometryGroup.h"
#include "CarenD2D1StrokeStyle.h"
#include "../DXGI/CarenDXGISurface.h"



//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por criar recursos do Direct2D. A interface ICarenD2D1Factory é o ponto de partida para o uso do Direct2D; é o que você usa 
/// para criar outros recursos Direct2D que você pode usar para desenhar ou descrever formas.
/// </summary>
public ref class CarenD2D1Factory : public ICarenD2D1Factory
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Factory).
	ID2D1Factory* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1Factory();
	
	~CarenD2D1Factory();

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


	//Métodos da interface(ICarenD2D1Factory)
public:
	/// <summary>
	/// Cria um alvo de renderização que atrai o contexto do dispositivo GDI (Windows Graphics Device Interface, interface do dispositivo gráfico do Windows).
	/// </summary>
	/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware. Para habilitar o objetivo 
	/// de renderização do contexto do dispositivo (DC) para funcionar com o GDI, defina o formato DXGI para DXGI_FORMAT_B8G8R8A8_UNORM e o modo alfa para D2D1_ALPHA_MODE_PREMULTIPLIED ou D2D1_ALPHA_MODE_IGNORE</param>
	/// <param name="Param_Out_DcRenderTarget">Retorna uma interface(ICarenD2D1DCRenderTarget) que contém um ponteiro para o novo alvo de renderização DC.</param>
	virtual CarenResult CreateDCRenderTarget(
	CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
	[Out] ICarenD2D1DCRenderTarget^% Param_Out_DcRenderTarget);

	/// <summary>
	/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
	/// </summary>
	/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
	/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) que contém parâmetros de texto opcionais que indicam como o texto deve ser renderizado.</param>
	/// <param name="Param_Out_StateBlock">>Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
	virtual CarenResult CreateDrawingStateBlock(
	CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
	ICaren^ Param_TextRenderingParams,
	[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock
);

	/// <summary>
	/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
	/// </summary>
	/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
	/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
	virtual CarenResult CreateDrawingStateBlock(
	CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
	[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock);

	/// <summary>
	/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
	/// </summary>
	/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
	virtual CarenResult CreateDrawingStateBlock([Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock);

	/// <summary>
	/// Cria um alvo de renderização que atrai uma superfície DXGI (DirectX Graphics Infrastructure, infraestrutura gráfica do DirectX).
	/// </summary>
	/// <param name="Param_DxgiSurface">Uma interface(ICarenDXGISurface) para o qual o alvo de renderização irá desenhar.</param>
	/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
	/// <param name="Param_Out_RenderTarget">Retorna uma interface(ICarenD2D1RenderTarget) que contém um ponteiro para o objeto criado.</param>
	virtual CarenResult CreateDxgiSurfaceRenderTarget(
	[Out] ICarenDXGISurface^% Param_DxgiSurface,
	CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
	[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget);

	/// <summary>
	/// Cria uma ICarenD2D1EllipseGeometry.
	/// </summary>
	/// <param name="Param_Ellipse">Um valor que descreve o ponto central, raio x e raio y da geometria da elipse.</param>
	/// <param name="Param_Out_EllipseGeometry">Retorna uma interface(ICarenD2D1EllipseGeometry) que contém um ponteiro para a nova geometria de elipse criada.</param>
	virtual CarenResult CreateEllipseGeometry(
	CA_D2D1_ELLIPSE^ Param_Ellipse,
	[Out] ICarenD2D1EllipseGeometry^% Param_Out_EllipseGeometry);

	/// <summary>
	/// Cria um ICarenD2D1GeometryGroup, que é um objeto que contém outras geometrias.
	/// Grupos de geometria são uma maneira conveniente de agrupar várias geometrias simultaneamente para que todas as figuras de várias geometrias distintas sejam concatenadas em uma.
	/// </summary>
	/// <param name="Param_FiilMode">Um valor que especifica a regra que uma forma composta usa para determinar se um determinado ponto faz parte da geometria.</param>
	/// <param name="Param_Geometrias">Uma matriz contendo os objetos de geometria para adicionar ao grupo de geometria. O número de elementos nesta matriz é indicado pelo parâmetro (Param_QuantidadeGeometrias).</param>
	/// <param name="Param_QuantidadeGeometrias">O número de elementos em (Param_Geometrias).</param>
	/// <param name="Param_Out_GeometryGroup">Retorna uma interface(ICarenD2D1GeometryGroup) que contém um ponteiro para o novo grupo de geometria.</param>
	virtual CarenResult CreateGeometryGroup(
	CA_D2D1_FILL_MODE Param_FiilMode,
	cli::array<ICarenD2D1Geometry^>^ Param_Geometrias,
	UInt32 Param_QuantidadeGeometrias,
	[Out] ICarenD2D1GeometryGroup^% Param_Out_GeometryGroup);

	/// <summary>
	/// Cria um ICarenD2D1HwndRenderTarget, um alvo de renderização que renderiza uma janela.
	/// Quando você cria um alvo de renderização e a aceleração de hardware está disponível, você aloca recursos na GPU do computador. Ao criar um alvo de renderização uma vez e retê-lo o maior tempo possível, você ganha benefícios 
	/// de desempenho. Seu aplicativo deve criar metas de renderização uma vez e segurá-los durante a vida útil do aplicativo ou até que o erro D2DERR_RECREATE_TARGET seja recebido. Quando você recebe esse erro, você precisa recriar o 
	/// destino render (e quaisquer recursos que ele criou).
	/// </summary>
	/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
	/// <param name="Param_PropsHwndRenderTarget">A handle da janela, tamanho inicial (em pixels) e as opções atuais.</param>
	/// <param name="Param_Out_HwndRenderTarget">Retorna uma interface(ICarenD2D1HwndRenderTarget) que contém um ponteiro para o objeto criado.</param>
	virtual CarenResult CreateHwndRenderTarget(
	CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
	CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ Param_PropsHwndRenderTarget,
	[Out] ICarenD2D1HwndRenderTarget^% Param_Out_HwndRenderTarget);

	/// <summary>
	/// Cria uma ICarenD2D1PathGeometry vazio.
	/// </summary>
	/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry) que contém um ponteiro para o Path Geometry criado pelo método.</param>
	virtual CarenResult CreatePathGeometry(
	[Out] ICarenD2D1PathGeometry^% Param_Out_PathGeometry);

	/// <summary>
	/// Cria uma ICarenD2D1RectangleGeometry.
	/// </summary>
	/// <param name="Param_Retangulo">As coordenadas da geometria do retângulo.</param>
	/// <param name="Param_Out_RectangleGeometry">Retorna uma interface(ICarenD2D1RectangleGeometry) que contém um ponteiro para a geometria retângulo criada.</param>
	virtual CarenResult CreateRectangleGeometry(
	CA_D2D1_RECT_F^ Param_Retangulo,
	[Out] ICarenD2D1RectangleGeometry^% Param_Out_RectangleGeometry);

	/// <summary>
	/// Cria uma ID2D1RoundedRectangleGeometry.
	/// </summary>
	/// <param name="Param_RoundedRectangle">As coordenadas e os raios de canto da geometria do retângulo arredondado.</param>
	/// <param name="Param_Out_RoundedRectangleGeometry">Retorna uma interface(ICarenD2D1RoundedRectangleGeometry) que contém um ponteiro  para a geometria do retângulo arredondado criada.</param>
	virtual CarenResult CreateRoundedRectangleGeometry(
	CA_D2D1_ROUNDED_RECT^ Param_RoundedRectangle,
	[Out] ICarenD2D1RoundedRectangleGeometry^% Param_Out_RoundedRectangleGeometry);

	/// <summary>
	/// Cria um ICarenD2D1StrokeStyle que descreve tampa inicial, padrão de traço e outras características de um traçado.
	/// </summary>
	/// <param name="Param_PropsStrokeStyle">Uma estrutura que descreve o limite de linha do traçado, o deslocamento do traço e outros detalhes de um traçado.</param>
	/// <param name="Param_Dashes">Uma matriz cujos elementos são definidos para o comprimento de cada traço e espaço no padrão de traço.O primeiro elemento define o comprimento de um traço, o segundo elemento define o comprimento 
	/// de um espaço, o terceiro elemento define o comprimento de um traço e assim por diante.O comprimento de cada traço e espaço no padrão de traço é o produto do valor do elemento na matriz e a largura do traço.</param>
	/// <param name="Param_QuantidadeDashes">A quantidade de elementos na matriz (Param_Dashes).</param>
	/// <param name="Param_Out_StrokeStyle">Retorna uma interface(ICarenD2D1StrokeStyle) que contém um ponteiro para o estilo de traçado criado.</param>
	virtual CarenResult CreateStrokeStyle(
	CA_D2D1_STROKE_STYLE_PROPERTIES^ Param_PropsStrokeStyle,
	cli::array<float>^ Param_Dashes,
	UInt32 Param_QuantidadeDashes,
	[Out] ICarenD2D1StrokeStyle^% Param_Out_StrokeStyle);

	/// <summary>
	/// Transforma a geometria especificada e armazena o resultado como um objeto ICarenD2D1TransformedGeometry.
	/// </summary>
	/// <param name="Param_GeometriaOrigem">A geometria para transformar.</param>
	/// <param name="Param_Transform">A transformação para aplicar.</param>
	/// <param name="Param_Out_TransformedGeometry">Retorna uma interface(ICarenD2D1TransformedGeometry) que contém um ponteiro para o novo objeto de geometria transformado. A geometria transformada armazena o resultado da 
	/// transformação da (Param_GeometriaOrigem) por (Param_Transform).</param>
	virtual CarenResult CreateTransformedGeometry(
	ICarenD2D1Geometry^ Param_GeometriaOrigem,
	CA_D2D1_MATRIX_3X2_F^ Param_Transform,
	[Out] ICarenD2D1TransformedGeometry^% Param_Out_TransformedGeometry);

	/// <summary>
	/// Cria um alvo de renderização que renderiza um bitmap do WIC(Microsoft Windows Imaging Component).
	/// Você deve usar D2D1_FEATURE_LEVEL_DEFAULT para o membro minLevel do parâmetro (CA_D2D1_RENDER_TARGET_PROPERTIES) com este método.
	/// </summary>
	/// <param name="Param_WicBitmapTarget">O bitmap que recebe a saída de renderização do alvo renderizador.</param>
	/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
	/// <param name="Param_Out_RenderTarget">Retorna uma interface(ICarenD2D1RenderTarget) que contém um ponteiro para o objeto criado.</param>
	virtual CarenResult CreateWicBitmapRenderTarget(
	ICaren^ Param_WicBitmapTarget,
	CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
	[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget);

	/// <summary>
	/// Recupera os pontos de desktop atuais por polegada (DPI). Para atualizar esse valor, ligue para o ReloadSystemMetrics.
	/// Use este método para obter o DPI do sistema ao definir valores de pixels físicos, como quando você especifica o tamanho de uma janela.
	/// </summary>
	/// <param name="Param_Out_DpiX">Retorna o DPI Horizontal da área de trabalho.</param>
	/// <param name="Param_Out_DpiY">Retorna o DPI Vertical da área de trabalho.</param>
	virtual void GetDesktopDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY);

	/// <summary>
	/// Força o Factory a atualizar quaisquer padrões do sistema que possa ter mudado desde a criação do Factory.
	/// Você deve chamar este método antes de chamar o método GetDesktopDpi, para garantir que o DPI do sistema esteja atualizado.
	/// </summary>
	virtual CarenResult ReloadSystemMetrics();
};