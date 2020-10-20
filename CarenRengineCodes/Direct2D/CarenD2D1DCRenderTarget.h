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
#include "SDK_Direct2D.h"
#include "..\SDK_Caren.h"
#include "..\SDK_Utilidades.h"
#include "CarenD2D1Bitmap.h"
#include "CarenD2D1BitmapBrush.h"
#include "CarenD2D1GradientStopCollection.h"
#include "CarenD2D1Layer.h"
#include "CarenD2D1LinearGradientBrush.h"
#include "CarenD2D1RadialGradientBrush.h"
#include "CarenD2D1Mesh.h"
#include "CarenD2D1SolidColorBrush.h"
#include "GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por emitir comandos de desenho para um contexto de dispositivo GDI.
/// </summary>
public ref class CarenD2D1DCRenderTarget : public ICarenD2D1DCRenderTarget
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1DCRenderTarget).
	ID2D1DCRenderTarget* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenD2D1DCRenderTarget();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenD2D1DCRenderTarget">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1DCRenderTarget^% Param_Out_CarenD2D1DCRenderTarget)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1DCRenderTarget = gcnew CarenD2D1DCRenderTarget();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
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


	//Métodos da interface(ICarenD2D1DCRenderTarget)
public:
	/// <summary>
	/// Vincula o alvo de renderização ao contexto do dispositivo ao qual ele emite comandos de desenho.
	/// Antes de renderizar com o alvo de renderização DC, você deve usar seu método BindDC para associá-lo a um GDI DC. Você faz isso cada vez que usa um DC diferente, ou o tamanho da área 
	/// que deseja desenhar para mudanças.
	/// </summary>
	/// <param name="Param_Hdc">O contexto do dispositivo para o qual o alvo de renderização emite comandos de desenho.</param>
	/// <param name="Param_SubRect">As dimensões da Handle(Param_Hdc) para um contexto de dispositivo (HDC) a que o alvo de renderização está vinculado.</param>
	virtual CarenResult BindDC(
	IntPtr Param_Hdc,
	CA_RECT^ Param_SubRect);


	//Métodos da interface(ICarenD2D1RenderTarget)
public:
	/// <summary>
	/// Inicia o desenho deste alvo de renderização. 
	/// </summary>
	virtual void BeginDraw();

	/// <summary>
	/// Limpa a área de desenho para a cor especificada. 
	/// </summary>
	/// <param name="Param_ClearColor"></param>
	virtual void Clear(CA_D2D1_COLOR_F^ Param_ClearColor);

	/// <summary>
	/// Cria um bitmap do Direct2D de um ponteiro para dados de origem na memória. 
	/// </summary>
	/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
	/// <param name="Param_DadosOrigem">Um ponteiro para a localização da memória dos dados da imagem ou NULO para criar um bitmap não inicializado.</param>
	/// <param name="Param_Pitch">A contagem de bytes de cada linha de varredura, que é igual a (a largura da imagem em pixels × o número de bytes por pixel) + preenchimento de memória. Se (Param_DadosOrigem) é NULO, este valor é ignorado. (Note que o tom também é às vezes chamado de pitch.)</param>
	/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
	/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmap(
		CA_D2D1_SIZE_U^ Param_Size,
		ICarenBuffer^ Param_DadosOrigem,
		UInt32 Param_Pitch,
		CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
		[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um bitmap do Direct2D não inicializado. 
	/// </summary>
	/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
	/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
	/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmap(
		CA_D2D1_SIZE_U^ Param_Size,
		CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
		[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. 
	/// </summary>
	/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel(Brush).</param>
	/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,a escova padrão para o D2D1_EXTEND_MODE_CLAMP 
	/// modos de extensão horizontal e vertical e o modo de interpolação D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.</param>
	/// <param name="Param_PropriedadesBrush">Uma estrutura que contenha a opacidade e a transformação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,o pincel define o membro da opacidade 
	/// para 1.0F e o membro de transformação para a matriz de identidade.</param>
	/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
	virtual CarenResult CreateBitmapBrush(
		ICarenD2D1Bitmap^ Param_Bitmap,
		CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
		CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
		[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush);

	/// <summary>
	/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para seu modo de extensão, modo de interpolação, opacidade e transformação.
	/// </summary>
	/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
	/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
	virtual CarenResult CreateBitmapBrush(
		ICarenD2D1Bitmap^ Param_Bitmap,
		[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush);

	/// <summary>
	/// Cria um ID2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para sua opacidade e transformação. 
	/// O Brush bitmap criado por este método tem uma opacidade de 1.0f e a matriz de identidade como sua transformação.
	/// </summary>
	/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
	/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel.</param>
	/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
	virtual CarenResult CreateBitmapBrush(
		ICarenD2D1Bitmap^ Param_Bitmap,
		CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
		[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush);

	/// <summary>
	/// Cria um ICarenD2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC). 
	/// </summary>
	/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
	/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. O formato pixel deve corresponder ao formato de pixel do wicBitmapSource, ou o método falhará. Para evitar uma 
	/// incompatibilidade, você pode passar NULO ou passar o valor obtido ligando para a função de ajudante D2D1::PixelFormat sem especificar nenhum valor de parâmetro. Se o dpiX e o dpiY forem 0,0f, o 
	/// DPI padrão, 96, será usado. As informações de DPI incorporadas no (Param_WicBitmapSource) são ignoradas.</param>
	/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromWicBitmap(
		ICaren^ Param_WicBitmapSource,
		CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
		[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ID2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
	/// </summary>
	/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
	/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromWicBitmap(
		ICaren^ Param_WicBitmapSource,
		[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
	/// </summary>
	/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará 
	/// o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
	/// <param name="Param_Opcoes">Um valor que especifica se o novo alvo de renderização deve ser compatível com o GDI.</param>
	/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateCompatibleRenderTarget(
		CA_D2D1_SIZE_F^ Param_DesiredSize,
		CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
		CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
		CA_D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS Param_Opcoes,
		ICaren^ Param_Out_BitmapRenderTarget);

	/// <summary>
	/// Cria um novo alvo de renderização bitmap para uso durante o desenho offscreen intermediário que é compatível com o alvo de renderização atual e tem o mesmo tamanho, DPI e formato de pixel 
	/// (mas não o modo alfa) como o alvo de renderização atual. 
	/// O alvo de renderização bitmap criado por este método não é compatível com o GDI, e tem um modo alfa de D2D1_ALPHA_MODE_PREMULTIPLIED.
	/// </summary>
	/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateCompatibleRenderTarget(ICaren^ Param_Out_BitmapRenderTarget);

	/// <summary>
	/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
	/// O alvo de renderização bitmap criado por este método não é compatível com o GDI.
	/// </summary>
	/// <param name="Param_DesiredSize">O tamanho desejado do novo destino de renderização em pixels independentes do dispositivo. O tamanho do pixel é calculado a partir do tamanho desejado usando o DPI pai de destino. 
	/// Se o tamanho desejado for mapeado para um tamanho de pixel inteiro, o DPI do destino de renderização compatível será o mesmo que o DPI pai do destino. Se o Tamanho desejado é mapeado para um tamanho de pixel 
	/// fracionário, o tamanho do pixel é arredondado para o número inteiro mais próximo e o DPI para o destino de renderização compatível é um pouco maior que o DPI do destino de renderização pai. Em todos os casos, 
	/// a coordenada (Param_DesiredSize.width, Param_DesiredSize.height) é mapeada para o canto inferior direito do destino de renderização compatível.</param>
	/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateCompatibleRenderTarget(
		CA_D2D1_SIZE_F^ Param_DesiredSize,
		ICaren^ Param_Out_BitmapRenderTarget);

	/// <summary>
	/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
	/// </summary>
	/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateCompatibleRenderTarget(
		CA_D2D1_SIZE_F^ Param_DesiredSize,
		CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
		ICaren^ Param_Out_BitmapRenderTarget);

	/// <summary>
	/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
	/// </summary>
	/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
	/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
	/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateCompatibleRenderTarget(
		CA_D2D1_SIZE_F^ Param_DesiredSize,
		CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
		CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
		ICaren^ Param_Out_BitmapRenderTarget);

	/// <summary>
	/// Cria uma interface de coleção ICarenD2D1GradientStop a partir do conjunto especificado de estruturas CA_D2D1_GRADIENT_STOP. 
	/// </summary>
	/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
	/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
	/// <param name="Param_ColorInterpolationGamma">O espaço em que a interpolação de cores entre as paradas gradientes é realizada.</param>
	/// <param name="Param_ModoExtendido">O comportamento do gradiente fora da faixa [0,1] normalizada.</param>
	/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
	virtual CarenResult CreateGradientStopCollection(
		cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
		UInt32 Param_QuantidadeGradientes,
		CA_D2D1_GAMMA Param_ColorInterpolationGamma,
		CA_D2D1_EXTEND_MODE Param_ModoExtendido,
		[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

	/// <summary>
	///  Cria uma interface de coleção ICarenD2D1GradientStop a partir das estruturas GradientStops especificadas que usa o gama de interpolação de cores D2D1_GAMMA_2_2 e o modo de extensão do Clamp. 
	/// </summary>
	/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
	/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
	/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
	virtual CarenResult CreateGradientStopCollection(
		cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
		UInt32 Param_QuantidadeGradientes,
		[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

	/// <summary>
	/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis.
	/// </summary>
	/// <param name="Param_Size">Se (0, 0) for especificado, nenhuma loja de backup será criada por trás do recurso de camada. O recurso de camada é alocado para o tamanho mínimo quando o PushLayer é chamado.</param>
	/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
	virtual CarenResult CreateLayer(
		CA_D2D1_SIZE_F^ Param_Size,
		[Out] ICarenD2D1Layer^% Param_Out_Layer);

	/// <summary>
	/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis. 
	/// </summary>
	/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
	virtual CarenResult CreateLayer([Out] ICarenD2D1Layer^% Param_Out_Layer);

	/// <summary>
	/// Cria um ICarenD2D1LinearGradientBrush que contém as GradientStops especificadas e tem a opacidade de transformação e base especificada. 
	/// </summary>
	/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
	/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel.</param>
	/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
	/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
	virtual CarenResult CreateLinearGradientBrush(
		CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
		CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
		ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
		[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush);

	/// <summary>
	/// Cria um ICarenD2D1LinearGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
	/// </summary>
	/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
	/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
	/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
	virtual CarenResult CreateLinearGradientBrush(
		CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
		ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
		[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush);

	/// <summary>
	/// Crie uma malha(Mesh) que usa triângulos para descrever uma forma. 
	/// </summary>
	/// <param name="Param_Out_Mesh">Retorna uma interface ICarenD2D1Mesh que contém um ponteiro para a nova malha(Mesh).</param>
	virtual CarenResult CreateMesh([Out] ICarenD2D1Mesh^% Param_Out_Mesh);

	/// <summary>
	/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados e tem a opacidade de transformação e base especificada.
	/// </summary>
	/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
	/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel(Brush).</param>
	/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
	/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
	virtual CarenResult CreateRadialGradientBrush(
		CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
		CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
		ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
		[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush);

	/// <summary>
	/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
	/// </summary>
	/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
	/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
	/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
	virtual CarenResult CreateRadialGradientBrush(
		CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
		ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
		[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush);

	/// <summary>
	/// Cria um ICarenD2D1Bitmap cujos dados são compartilhados com outro recurso. 
	/// </summary>
	/// <param name="Param_Riid">O ID de interface do objeto que fornece os dados de origem.</param>
	/// <param name="Param_InterfaceDados">Uma ICarenD2D1Bitmap, ICarenDXGISurface ou uma ICarenWICBitmapLock que contém os dados para compartilhar com o novo ICarenD2D1Bitmap. </param>
	/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. A DXGI_FORMAT parte do formato pixel deve corresponder à DXGI_FORMAT de dados ou o método falhará, mas os modos alfa 
	/// não precisam coincidir. Para evitar uma incompatibilidade, você pode passar NULO ou o valor obtido da função auxiliar D2D1::PixelFormat. As configurações de DPI não têm que coincidir com as dos dados. 
	/// Se o dpiX e o dpiY forem 0,0f, o DPI do alvo de renderização será usado.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateSharedBitmap(
		String^ Param_Riid,
		ICaren^ Param_InterfaceDados,
		CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
		[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor e a opacidade especificados.
	/// </summary>
	/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel.</param>
	/// <param name="Param_PropriedadesBrush">A opacidade base do pincel.</param>
	/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
	virtual CarenResult CreateSolidColorBrush(
		CA_D2D1_COLOR_F^ Param_Cor,
		CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
		[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush);

	/// <summary>
	/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor especificada e uma opacidade base de 1.0f.
	/// </summary>
	/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel(Brush).</param>
	/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
	virtual CarenResult CreateSolidColorBrush(
		CA_D2D1_COLOR_F^ Param_Cor,
		[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush);

	/// <summary>
	/// Desenha o bitmap especificado depois de dimensioná-lo para o tamanho do retângulo especificado. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawBitmap) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw 
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Bitmap">O bitmap para renderizar.</param>
	/// <param name="Param_RetanguloDestino">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do alvo de renderização, da área para a qual o bitmap é desenhado. 
	/// Se o retângulo não for bem ordenado, nada é desenhado, mas o alvo de renderização não entra em um estado de erro.</param>
	/// <param name="Param_Opacidade">Um valor entre 0,0f e 1,0f, inclusive, que especifica um valor de opacidade para aplicar ao bitmap; este valor é multiplicado em relação aos valores alfa do 
	/// conteúdo do bitmap.</param>
	/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado se o bitmap for dimensionado ou girado pela operação de desenho.</param>
	/// <param name="Param_RetanguloOrigem">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do bitmap, da área dentro do bitmap para desenhar.</param>
	virtual CarenResult DrawBitmap(
		ICarenD2D1Bitmap^ Param_Bitmap,
		CA_D2D1_RECT_F^ Param_RetanguloDestino,
		float Param_Opacidade,
		CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode,
		CA_D2D1_RECT_F^ Param_RetanguloOrigem);

	/// <summary>
	/// Desenha o contorno(Outline) da elipse especificada usando o estilo de traçado especificado. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Ellipse">A posição e o raio da elipse para desenhar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno da elipse.</param>
	/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão 
	/// para 1.0f. O golpe está centrado na linha.</param>
	/// <param name="Param_StrokeStyle">O estilo do Stroke para aplicar ao contorno(Outline) da elipse, ou NULO para pintar um traço sólido.</param>
	virtual CarenResult DrawEllipse(
		CA_D2D1_ELLIPSE^ Param_Ellipse,
		ICarenD2D1Brush^ Param_Brush,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle);

	/// <summary>
	/// Desenha o contorno da geometria especificada usando o estilo de traçado especificado. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Geometria">A geometria para desenhar.</param>
	/// <param name="Param_Brush">O pincel(Brush) para pintar o traço(Stroke) da geometria.</param>
	/// <param name="Param_StrokeWidth">A largura do traçado, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão
	/// para 1.0f. O golpe está centrado na linha.</param>
	/// <param name="Param_StrokeStyle">O estilo de traçado(Stroke) para aplicar ao contorno(Outline) da geometria, ou NULO para pintar um traço(Stroke) sólido.</param>
	virtual CarenResult DrawGeometry(
		ICarenD2D1Geometry^ Param_Geometria,
		ICarenD2D1Brush^ Param_Brush,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle);

	/// <summary>
	/// Desenha os glifos(Glyph) especificados.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGlyphRun) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_BaseLineOrigin">A origem, em pixels independentes de dispositivos, da linha de base dos glifos(Glyph).</param>
	/// <param name="Param_GlyphRun">Os glifos(Glyph) para renderizar.</param>
	/// <param name="Param_ForegroundBrush">O pincel(Brush) usado para pintar os glifos(Glyph) especificados.</param>
	/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
	virtual CarenResult DrawGlyphRun(
		CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
		CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
		ICarenD2D1Brush^ Param_ForegroundBrush,
		CA_DWRITE_MEASURING_MODE Param_MeasuringMode);

	/// <summary>
	/// Desenha uma linha entre os pontos especificados usando o estilo de traçado especificado. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawLine) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Point0">O ponto de partida da linha, em pixels independentes de dispositivos.</param>
	/// <param name="Param_Point1">O ponto final da linha, em pixels independentes de dispositivos.</param>
	/// <param name="Param_Brush">O pincel(Brush) para pintar o traço da linha.</param>
	/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo.O valor deve ser maior ou igual a 0, 0f.Se esse parâmetro não for especificado, o padrão será 1.0f. 
	/// O Stroke é centralizado na linha.</param>
	/// <param name="Param_StrokeStyle">O estilo de Stroke para pintar, ou NULO para pintar uma linha sólida.</param>
	virtual CarenResult DrawLine(
		CA_D2D1_POINT_2F^ Param_Point0,
		CA_D2D1_POINT_2F^ Param_Point1,
		ICarenD2D1Brush^ Param_Brush,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle);

	/// <summary>
	/// Desenha o contorno(Outline) de um retângulo que tem as dimensões especificadas e o estilo de traçado.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Rect">As dimensões do retângulo para desenhar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o curso do retângulo.</param>
	/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, 
	/// o padrão será 1.0f. O traço(Stroke) é centralizado na linha.</param>
	/// <param name="Param_StrokeStyle">O estilo do traço(Stroke) para pintar ou NULO para pintar um traçado sólido.</param>
	virtual CarenResult DrawRectangle(
		CA_D2D1_RECT_F^ Param_Rect,
		ICarenD2D1Brush^ Param_Brush,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle);

	/// <summary>
	/// Desenha o contorno(Outline) do retângulo arredondado especificado usando o estilo de traçado especificado. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_RoundedRect">As dimensões do retângulo arredondado para desenhar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno do retângulo arredondado.</param>
	/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, o padrão 
	/// será 1.0f. O traço(Stroke) é centralizado na linha.</param>
	/// <param name="Param_StrokeStyle">O estilo do traçado do retângulo arredondado, ou NULO para pintar um traço sólido. O valor padrão é NULO.</param>
	virtual CarenResult DrawRoundedRectangle(
		CA_D2D1_ROUNDED_RECT^ Param_RoundedRect,
		ICarenD2D1Brush^ Param_Brush,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle);

	/// <summary>
	/// Desenha o texto especificado usando as informações de formato fornecidas por um objeto ICarenDWriteTextFormat. 
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawText) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Texto">Uma string de caracteres Unicode para desenhar.</param>
	/// <param name="Param_TamanhoTexto">O número de caracteres em (Param_Texto).</param>
	/// <param name="Param_TextFormat">Uma interface(ICarenDWriteTextFormat) que descreve a formatação de detalhes do texto para desenhar, como a fonte, o tamanho da fonte e a direção do fluxo.</param>
	/// <param name="Param_LayoutRect">O tamanho e a posição da área em que o texto é desenhado.</param>
	/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar o texto.</param>
	/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
	/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
	/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
	virtual CarenResult DrawText(
		String^ Param_Texto,
		UInt32 Param_TamanhoTexto,
		ICaren^ Param_TextFormat,
		CA_D2D1_RECT_F^ Param_LayoutRect,
		ICarenD2D1Brush^ Param_DefaultFillBrush,
		CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes,
		CA_DWRITE_MEASURING_MODE Param_MeasuringMode);

	/// <summary>
	/// Desenha o texto formatado descrito pelo objeto ICarenDWriteTextLayout especificado.
	/// Ao desenhar o mesmo texto repetidamente, o uso do método DrawTextLayout é mais eficiente do que usar o método DrawText porque o texto não precisa ser formatado e o layout processado a cada chamada.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawTextLayout) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Origem">O ponto, descrito em pixels independentes do dispositivo, no qual o canto superior esquerdo do texto descrito pelo (Param_TextLayout) é desenhado.</param>
	/// <param name="Param_TextLayout">Uma interface(ICarenDWriteTextLayout) com o texto formatado para desenhar. Quaisquer efeitos de desenho que não herdem do ID2D1Resource são ignorados. Se houver 
	/// efeitos de desenho que herdam do ICarenD2D1Resource que não são pincéis, este método falhará e o alvo de renderização é colocado em um estado de erro.</param>
	/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar qualquer texto no (Param_TextLayout) que ainda não tenha um pincel associado a ele como efeito de desenho (especificado pelo 
	/// método ICarenDWriteTextLayout::SetDrawingEffect).</param>
	/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
	/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
	virtual CarenResult DrawTextLayout(
		CA_D2D1_POINT_2F^ Param_Origem,
		ICaren^ Param_TextLayout,
		ICarenD2D1Brush^ Param_DefaultFillBrush,
		CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes);

	/// <summary>
	/// Termina as operações de desenho no alvo de renderização e indica o estado de erro atual e as tags associadas. 
	/// </summary>
	/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
	/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
	virtual CarenResult EndDraw(
		[Out] UInt64% Param_Out_Tag1,
		[Out] UInt64% Param_Out_Tag2);

	/// <summary>
	/// Pinta o interior da elipse especificada.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Ellipse">A posição e o raio, em pixels independentes do dispositivo, da elipse para pintar.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior da elipse.</param>
	virtual CarenResult FillEllipse(
		CA_D2D1_ELLIPSE^ Param_Ellipse,
		ICarenD2D1Brush^ Param_Brush);

	/// <summary>
	/// Pinta o interior da geometria especificada.
	/// Se o parâmetro (Param_OpacityBrush) não for NULO, o valor alfa de cada pixel da opacidade mapeadaBrush é usado para determinar a opacidade resultante de cada pixel correspondente da geometria. 
	/// Apenas o valor alfa de cada cor no Brush é usado para este processamento; todas as outras informações de cores são ignoradas.
	/// O valor alfa especificado pelo Brush é multiplicado pelo valor alfa da geometria após a geometria ter sido pintada pelo Brush.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Geometria">A geometria para pintar.</param>
	/// <param name="Param_Brush">O pincel(Brush) para pintar o interior da geometria.</param>
	/// <param name="Param_OpacityBrush">A máscara de opacidade para aplicar à geometria, ou NULO para nenhuma máscara de opacidade. Se uma máscara de opacidade (o parâmetro Param_OpacityBrush) for especificada, 
	/// o (Param_Brush) deve ser um ICarenD2D1BitmapBrush que tem seus modos x e y-extend definidos para D2D1_EXTEND_MODE_CLAMP.</param>
	virtual CarenResult FillGeometry(
		ICarenD2D1Geometry^ Param_Geometria,
		ICarenD2D1Brush^ Param_Brush,
		ICarenD2D1Brush^ Param_OpacityBrush);

	/// <summary>
	/// Pinta o interior da malha especificada.
	/// O modo antialias atual do alvo de renderização deve ser D2D1_ANTIALIAS_MODE_ALIASED quando FillMesh é chamado. Para alterar o modo antialias do alvo de renderização, use o método SetAntialiasMode.
	/// FillMesh não espera uma ordem de enrolamento específica para os triângulos no ID2D1Mesh; tanto no sentido horário quanto no sentido anti-horário funcionará.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillMesh) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Mesh">A malha para pintar.</param>
	/// <param name="Param_Brush">O pincel(Brush) para pintar a malha.</param>
	virtual CarenResult FillMesh(
		ICarenD2D1Mesh^ Param_Mesh,
		ICarenD2D1Brush^ Param_Brush);

	/// <summary>
	/// Aplica a máscara de opacidade descrita pelo bitmap especificado em um pincel e usa esse pincel para pintar uma região do alvo de renderização.
	/// Para que este método funcione corretamente, o alvo de renderização deve estar usando o modo D2D1_ANTIALIAS_MODE_ALIASED antialiasing. Você pode definir o modo antialiasing chamando o método 
	/// ICarenD2D1RenderTarget::SetAntialiasMode método.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillOpacityMask) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_OpacityMask">A máscara de opacidade para aplicar no pincel. O valor alfa de cada pixel na região especificado pelo (Param_RetanguloOrigem) é multiplicado com o valor alfa do 
	/// Brush após o pincel(Brush) ter sido mapeado para a área definida pelo (Param_RetanguloDestino).</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar a região do alvo de render especificado pelo (Param_RetanguloDestino).</param>
	/// <param name="Param_Content">O tipo de conteúdo que a máscara de opacidade contém. O valor é usado para determinar o espaço de cor no qual a máscara de opacidade é misturada.
	/// A partir do Windows 8, o D2D1_OPACITY_MASK_CONTENT não é necessário. Consulte o método ICarenD2D1DeviceContext::FillOpacityMask, que não tem parâmetro D2D1_OPACITY_MASK_CONTENT.</param>
	/// <param name="Param_RetanguloDestino">A região do alvo de renderização para pintar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_RetanguloOrigem">A região do bitmap para usar como máscara de opacidade, em pixels independentes de dispositivos.</param>
	virtual CarenResult FillOpacityMask(
		ICarenD2D1Bitmap^ Param_OpacityMask,
		ICarenD2D1Brush^ Param_Brush,
		CA_D2D1_OPACITY_MASK_CONTENT Param_Content,
		CA_D2D1_RECT_F^ Param_RetanguloDestino,
		CA_D2D1_RECT_F^ Param_RetanguloOrigem);

	/// <summary>
	/// Pinta o interior do retângulo especificado.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Rect">A dimensão do retângulo para pintar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo.</param>
	virtual CarenResult FillRectangle(
		CA_D2D1_RECT_F^ Param_Rect,
		ICarenD2D1Brush^ Param_Brush);

	/// <summary>
	/// Pinta o interior do retângulo arredondado especificado.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_Rect">As dimensões do retângulo arredondado para pintar, em pixels independentes do dispositivo.</param>
	/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo arredondado.</param>
	virtual CarenResult FillRoundedRectangle(
		CA_D2D1_ROUNDED_RECT^ Param_Rect,
		ICarenD2D1Brush^ Param_Brush);

	/// <summary>
	/// Executa todos os comandos de desenho pendentes.
	/// Este comando não libera o contexto do dispositivo Direct3D que está associado ao alvo de renderização.
	/// Chamar este método redefine o estado de erro do alvo de renderização.
	/// Se o método for bem sucedido, ele retorna SS_OK. Caso contrário, ele retorna um código de erro HRESULT e define Tag1 e Tag2 para as tags que estavam ativas quando o erro ocorreu. Se não ocorreu nenhum erro, 
	/// este método define o estado de Tags de erro (0,0).
	/// </summary>
	/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
	/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
	virtual CarenResult Flush(
		[Out] UInt64% Param_Out_Tag1,
		[Out] UInt64% Param_Out_Tag2);

	/// <summary>
	/// Recupera o modo antialiasing atual para operações de desenho sem texto. 
	/// </summary>
	/// <param name="Param_Out_AntialiasMode">Retorna o modo antialiasing atual para operações de desenho sem texto.</param>
	virtual void GetAntialiasMode([Out] CA_D2D1_ANTIALIAS_MODE% Param_Out_AntialiasMode);

	/// <summary>
	/// Retorne os pontos do alvo de renderização por polegada (DPI). 
	/// </summary>
	/// <param name="Param_Out_DpiX">Retorna o DPI horizontal do alvo de renderização.</param>
	/// <param name="Param_Out_DpiY">Retorna o DPI vertical do alvo de renderização. </param>
	virtual void GetDpi(
		[Out] float% Param_Out_DpiX,
		[Out] float% Param_Out_DpiY);

	/// <summary>
	/// Obtém o tamanho máximo, em unidades dependentes de dispositivos (pixels), de qualquer dimensão de bitmap suportada pelo alvo de renderização.
	/// Este método retorna o tamanho máximo da textura do dispositivo Direct3D.
	/// O renderizador de software e os dispositivos WARP retornam o valor de 16 megapixels (16* 1024 * 1024). Você pode criar uma textura Direct2D que é deste tamanho, mas não uma textura Direct3D que 
	/// é deste tamanho.
	/// </summary>
	/// <param name="Param_Out_MaximumSize">Retorna o tamanho máximo, em pixels, de qualquer dimensão de bitmap suportada pelo alvo de renderização.</param>
	virtual void GetMaximumBitmapSize([Out] UInt32% Param_Out_MaximumSize);

	/// <summary>
	/// Recupera o formato de pixel e o modo alfa do alvo de renderização. 
	/// </summary>
	/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do alvo de renderização.</param>
	virtual void GetPixelFormat([Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat);

	/// <summary>
	/// Retorna o tamanho do alvo de renderização em pixels do dispositivo. 
	/// </summary>
	/// <param name="Param_Out_PixelSize">Retorna tamanho do alvo de renderização em pixels do dispositivo.</param>
	virtual void GetPixelSize([Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize);

	/// <summary>
	/// Retorna o tamanho do alvo de renderização em pixels independentes do dispositivo.
	/// </summary>
	/// <param name="Param_Out_Size">Retorna tamanho atual do alvo de renderização em pixels independentes do dispositivo.</param>
	virtual void GetSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size);

	/// <summary>
	/// Obtém o rótulo(Tags) para operações de desenho subsequentes. 
	/// </summary>
	/// <param name="Param_Out_Tag1">Retorna o primeiro rótulo para operações de desenho subsequentes.</param>
	/// <param name="Param_Out_Tag2">Retorna o segundo rótulo para operações de desenho subsequentes.</param>
	virtual void GetTags(
		[Out] UInt64% Param_Out_Tag1,
		[Out] UInt64% Param_Out_Tag2);

	/// <summary>
	/// Obtém o modo antialiasing atual para operações de desenho de texto e glifo(Glyph). 
	/// </summary>
	/// <param name="Param_Out_TextAntialiasMode">Retorna o modo antialiasing atual para operações de desenho de texto e glifo(Glyph).</param>
	virtual void GetTextAntialiasMode([Out] CA_D2D1_TEXT_ANTIALIAS_MODE% Param_Out_TextAntialiasMode);

	/// <summary>
	/// Recupera as opções de renderização de texto atual do alvo. 
	/// </summary>
	/// <param name="Param_Out_TextRenderingParams">Retorna a interface (IDWriteRenderingParams) que contém um ponteiro para as opções de renderização de texto atuais do destino. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams);

	/// <summary>
	/// Obtém a transformação atual do alvo render. 
	/// </summary>
	/// <param name="Param_Out_Transform">Retorna a transformação atual do alvo de renderização.</param>
	virtual void GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform);

	/// <summary>
	/// Indica se o alvo de renderização suporta as propriedades especificadas.
	/// Este método não avalia as configurações de DPI especificadas pelo parâmetro (Param_ProppriedadesRenderTarget).
	/// </summary>
	/// <param name="Param_ProppriedadesRenderTarget">As propriedades de destino de renderização para testar.</param>
	/// <param name="Param_Out_Suporta">Retorna um valor Booleano TRUE se as propriedades de destino de renderização especificadas forem suportadas por este alvo de renderização; caso contrário, FALSO.</param>
	virtual void IsSupported(
		CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_ProppriedadesRenderTarget,
		[Out] Boolean% Param_Out_Suporta);

	/// <summary>
	/// Remove o último clipe alinhado ao eixo do alvo de renderização. Depois que este método é chamado, o clipe não é mais aplicado às operações de desenho subsequentes.
	/// PopAxisAlignedClip deve ser chamado uma vez para cada chamada para PushAxisAlignedClip.
	/// Um par PushAxisAlignedClip/PopAxisAlignedClip pode ocorrer ao redor ou dentro de um par PushLayer/PopLayer, mas pode não se sobrepor. Por exemplo, uma sequência PushAxisAlignedClip, PushLayer, PopLayer, 
	/// PopAxisAlignedClip é válida, mas uma sequência PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer não é.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	virtual void PopAxisAlignedClip();

	/// <summary>
	/// Interrompe o redirecionamento das operações de desenho para a camada especificada pela última chamada do PushLayer.
	/// Um PopLayer deve corresponder a uma chamada pushlayer anterior.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	virtual void PopLayer();

	/// <summary>
	/// Especifica um retângulo ao qual todas as operações de desenho subsequentes são cortadas.
	/// O PushAxisAlignedClip e o PopAxisAlignedClip devem coincidir. Caso contrário, o estado de erro está definido. Para que o alvo de renderização continue recebendo novos comandos, você pode chamar 
	/// Flush para limpar o erro.
	/// Um par PushAxisAlignedClip e PopAxisAlignedClip pode ocorrer em torno ou dentro de um PushLayer e PopLayer, mas não pode se sobrepor. Por exemplo, a sequência de PushAxisAlignedClip, PushLayer, 
	/// PopLayer, PopAxisAlignedClip é válida, mas a sequência de PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer é inválida.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_ClipRect">O tamanho e a posição da área de recorte, em pixels independentes do dispositivo.</param>
	/// <param name="Param_AntialiasMode">O modo antialiasing que é usado para desenhar as bordas das retagens de clipe que têm limites de subpixel, e para misturar o clipe com o conteúdo da cena. A mistura 
	/// é realizada uma vez quando o método PopAxisAlignedClip é chamado, e não se aplica a cada primitivo dentro da camada.</param>
	virtual void PushAxisAlignedClip(
		CA_D2D1_RECT_F^ Param_ClipRect,
		CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode);

	/// <summary>
	/// Adicione a camada especificada ao destino renderização para que ela receba todas as operações de desenho subsequentes até que o PopLayer seja chamado. 
	/// O método PushLayer permite que um chamador comece a redirecionar a renderização para uma camada. Todas as operações de renderização são válidas em uma camada. A localização da camada é afetada 
	/// pela transformação mundial definida na meta de renderização.
	/// Cada PushLayer deve ter uma chamada PopLayer correspondente. Se houver mais chamadas do PopLayer do que chamadas PushLayer, o alvo de renderização será colocado em um estado de erro. Se flush 
	/// for chamado antes de todas as camadas pendentes serem estouradas, o alvo de renderização será colocado em um estado de erro e um erro será retornado. O estado de erro pode ser liberado por uma chamada para EndDraw.
	/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
	/// ou ICarenD2D1RenderTarget::Flush.
	/// </summary>
	/// <param name="Param_ParametrosLayer">Os limites de conteúdo, máscara geométrica, opacidade, máscara de opções de opções de opções antialiasing para a camada.</param>
	/// <param name="Param_Layer">A camada que recebe operações de desenho subsequentes. Começando pelo Windows 8, este parâmetro é opcional. Se uma camada não for especificada, o Direct2D gerencia 
	/// automaticamente o recurso de camada.</param>
	virtual void PushLayer(
		CA_D2D1_LAYER_PARAMETERS^ Param_ParametrosLayer,
		ICarenD2D1Layer^ Param_Layer);

	/// <summary>
	/// Define o estado de desenho do alvo de renderização ao do ID2D1DrawingStateBlock especificado.
	/// </summary>
	/// <param name="Param_DrawingStateBlock">O novo estado de desenho do alvo render.</param>
	virtual CarenResult RestoreDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock);

	/// <summary>
	/// Salva o estado de desenho atual para o ID2D1DrawingStateBlock especificado. 
	/// </summary>
	/// <param name="Param_DrawingStateBlock">Retorna uma interface para o estado de desenho atual do alvo de renderização. Este parâmetro deve ser inicializado antes de passá-lo para o método.</param>
	virtual CarenResult SaveDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock);

	/// <summary>
	/// Define o modo de antialiasing do alvo de renderização. O modo antialiasing aplica-se a todas as operações de desenho subsequentes, excluindo as operações de desenho de texto e glifo(Glyph). 
	/// Para especificar o modo antialiasing para operações de texto e glifos(Glyph), use o método SetTextAntialiasMode.
	/// </summary>
	/// <param name="Param_AntialiasMode">O modo antialiasing para futuras operações de desenho.</param>
	virtual void SetAntialiasMode(CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode);

	/// <summary>
	/// Define os pontos por polegada (DPI) do alvo de renderização.
	/// Este método especifica o mapeamento do espaço pixel para o espaço independente do dispositivo para o alvo de renderização. Se tanto o DpiX quanto o DpiY forem 0, o DPI do sistema de leitura 
	/// de fábrica será escolhido. Se um parâmetro for zero e o outro não especificado, o DPI não será alterado.
	/// Para ICarenD2D1HwndRenderTarget, o DPI é padrão para o DPI mais recentemente do sistema de leitura de fábrica. O valor padrão para todas as outras metas de renderização é de 96 DPI.
	/// </summary>
	/// <param name="Param_DpiX">Um valor maior ou igual a zero que especifica o DPI horizontal do alvo de renderização.</param>
	/// <param name="Param_DpiY">Um valor maior ou igual a zero que especifica o DPI vertical do alvo de renderização.</param>
	virtual void SetDpi(
		float Param_DpiX,
		float Param_DpiY);

	/// <summary>
	/// Especifica um rótulo(Tag) para operações de desenho subsequentes.
	/// As etiquetas(Tags) especificadas por este método são impressas por mensagens de erro depuração. Se nenhuma tag for definida, o valor padrão de cada tag é 0.
	/// </summary>
	/// <param name="Param_Tag1">Um rótulo para aplicar às operações de desenho subsequentes.</param>
	/// <param name="Param_Tag2">Um rótulo para aplicar às operações de desenho subsequentes.</param>
	virtual void SetTags(
		UInt64 Param_Tag1,
		UInt64 Param_Tag2);

	/// <summary>
	/// Especifica o modo antialiasing a ser usado para operações subsequentes de desenho de texto e glifo(Glyph). 
	/// </summary>
	/// <param name="Param_TextAntialiasMode">O modo antialiasing para usar para operações subsequentes de desenho de texto e glifo(Glyph).</param>
	virtual void SetTextAntialiasMode(CA_D2D1_TEXT_ANTIALIAS_MODE Param_TextAntialiasMode);

	/// <summary>
	/// Especifica as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho de texto e glifo(Glyph).
	/// Se as configurações especificadas por textRenderingParams forem incompatíveis com o modo antialiasing de texto do alvo de renderização (especificado por SetTextAntialiasMode), as operações 
	/// subsequentes de desenho de texto e glifo(Glyph) falharão e colocarão o alvo de renderização em um estado de erro.
	/// </summary>
	/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) para as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho 
	/// de texto e glifoGlyph); NULO para limpar as opções atuais de renderização de texto.</param>
	virtual CarenResult SetTextRenderingParams(ICaren^ Param_TextRenderingParams);

	/// <summary>
	/// Aplica a transformação especificada ao alvo de renderização, substituindo a transformação existente. Todas as operações subsequentes de desenho ocorrem no espaço transformado. 
	/// </summary>
	/// <param name="Param_Transform">A transformação para aplicar ao alvo de renderização.</param>
	virtual void SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};