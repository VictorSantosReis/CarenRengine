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


//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// 
/// </summary>
class Shared_D2D1Resource
{
	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	static void GetFactory(ID2D1Resource* Param_MyPointerWork, ICaren^ Param_Out_Factory);
};

/// <summary>
/// 
/// </summary>
class Shared_D2D1ImageSource
{
	//Métodos da interface(ICarenD2D1ImageSource)
public:
	/// <summary>
	/// Permite que o sistema operacional livre a memória de vídeo dos recursos descartando seu conteúdo.
	/// </summary>
	static CarenResult OfferResources(ID2D1ImageSource* Param_MyPointerWork);

	/// <summary>
	/// Restaura o acesso aos recursos que foram oferecidos anteriormente pelo chamada OfferResources.
	/// </summary>
	/// <param name="Param_Out_RecursoDescartado">Retorna com TRUE se o conteúdo do recurso correspondente foi descartado e agora está indefinido ou FALSO se o conteúdo antigo do recurso correspondente ainda estiver intacto. 
	/// O chamador pode passar NULO, se o chamador pretende preencher os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
	static CarenResult TryReclaimResources(ID2D1ImageSource* Param_MyPointerWork, [Out] Boolean% Param_Out_RecursoDescartado);
};

/// <summary>
/// 
/// </summary>
class Shared_D2D1ColorContext
{
	//Métodos da interface(ICarenD2D1ColorContext1)
public:
	/// <summary>
	/// Recupera o tipo de contexto de cor.
	/// </summary>
	/// <param name="Param_Out_ColorContext">Retorna o tipo de contexto de cores.</param>
	static void GetColorContextType(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_D2D1_COLOR_CONTEXT_TYPE% Param_Out_ColorContext);

	/// <summary>
	/// Recupera o espaço de cores DXGI deste contexto. Retorna DXGI_COLOR_SPACE_CUSTOM quando o tipo de contexto de cor é ICC.
	/// </summary>
	/// <param name="Param_Out_DXGIColorSpace">Retorna o espaço de cor DXGI deste contexto.</param>
	static void GetDXGIColorSpace(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_DXGI_COLOR_SPACE_TYPE% Param_Out_DXGIColorSpace);

	/// <summary>
	/// Recupera um perfil de cor simples.
	/// </summary>
	/// <param name="Param_Out_ColorProfile">Retorna uma estrutura CA_D2D1_SIMPLE_COLOR_PROFILE que conterá o perfil de cor simples quando o método retornar.</param>
	static CarenResult GetSimpleColorProfile(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_D2D1_SIMPLE_COLOR_PROFILE^% Param_Out_ColorProfile);



	//Métodos da interface(ICarenD2D1ColorContext)
public:
	/// <summary>
	/// Obtém o espaço de cores do contexto de cores.
	/// </summary>
	/// <param name="Param_Out_EspacoCor">Retorna uma enumeração que contém o espaço de cores do contexto.</param>
	static void GetColorSpace(ID2D1ColorContext* Param_MyPointerWork, [Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);

	/// <summary>
	/// Obtém o bytes de perfil de cor para um ICarenD2D1ColorContext.
	/// </summary>
	/// <param name="Param_Out_ColorProfile">Retorna um buffer que contém o perfil de cores.</param>
	/// <param name="Param_ProfileSize">O tamanho do buffer de perfil.</param>
	static CarenResult GetProfile(
		ID2D1ColorContext* Param_MyPointerWork,
		[Out] cli::array<Byte>^% Param_Out_ColorProfile,
		UInt32 Param_ProfileSize);

	/// <summary>
	/// Obtém o tamanho do perfil de cor associado ao bitmap.
	/// </summary>
	/// <param name="Param_Out_ProfileSize">Retorna o tamanho do perfil em bytes.</param>
	static void GetProfileSize(ID2D1ColorContext* Param_MyPointerWork, [Out] UInt32% Param_Out_ProfileSize);
};

/// <summary>
/// 
/// </summary>
class Shared_D2D1Bitmap
{
	//Métodos da interface(ICarenD2D1Bitmap1)
public:
	/// <summary>
	/// Obtém as informações de contexto de cores associadas ao bitmap.
	/// </summary>
	/// <param name="Param_Out_ColorContext">Quando este método retorna, contém o endereço de um ponteiro para a interface de contexto de cor associada ao bitmap.</param>
	static CarenResult GetColorContext(
		ID2D1Bitmap1* Param_MyPointerWork,
		[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

	/// <summary>
	/// Obtém as opções usadas na criação do bitmap.
	/// </summary>
	/// <param name="Param_Out_BitmapOptions">Retorna as opções utilizadas.</param>
	static void GetOptions(
		ID2D1Bitmap1* Param_MyPointerWork,
		[Out] CA_D2D1_BITMAP_OPTIONS% Param_Out_BitmapOptions);

	/// <summary>
	/// Obtém a superfície especificada quando o bitmap foi criado, ou a superfície padrão criada quando o bitmap foi criado.
	/// O bitmap usado deve ter sido criado a partir de um alvo de renderização de superfície DXGI, um alvo de renderização derivada ou um contexto de dispositivo criado a partir de um ICarenD2D1Device. 
	/// A superfície devolvida pode ser usada com o Microsoft Direct3D ou qualquer outra API que interopera com superfícies compartilhadas.
	/// </summary>
	/// <param name="Param_Out_DxgiSurface">Retorna a superfície DXGI subjacente para o bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetSurface(
		ID2D1Bitmap1* Param_MyPointerWork, 
		ICaren^ Param_Out_DxgiSurface);

	/// <summary>
	/// Mapeia os dados do Bitmap na memória. O bitmap deve ter sido criado com a bandeira D2D1_BITMAP_OPTIONS_CPU_READ especificada para este método poder funcionar.
	/// [NOTA] Você não pode usar bitmaps para alguns propósitos enquanto mapeado. Particularmente, o método ICarenD2D1Bitmap::CopyFromBitmap não funciona se o bitmap de origem ou destino estiver mapeado.
	/// </summary>
	/// <param name="Param_Options">As opções utilizadas no mapeamento do bitmap na memória.</param>
	/// <param name="Param_Out_MappedRect">Quando este método retorna, contém uma referência ao retângulo que foi mapeado na memória. O usuário deve definir o tamanho do buffer(bits) dentro da estrutura antes de usar.</param>
	static CarenResult Map(
		ID2D1Bitmap1* Param_MyPointerWork,
		CA_D2D1_MAP_OPTIONS Param_Options,
		[Out] CA_D2D1_MAPPED_RECT^% Param_Out_MappedRect);

	/// <summary>
	/// Desmapeia o bitmap da memória. Qualquer memória retornada da chamada Mapa agora é inválida e pode ser recuperada pelo sistema operacional ou usada para outros fins. 
	/// O bitmap deve ter sido previamente mapeado.
	/// </summary>
	static CarenResult Unmap(ID2D1Bitmap1* Param_MyPointerWork);


	//Métodos da interface(ICarenD2D1Bitmap)
public:
	/// <summary>
	/// Copia a região especificada do bitmap especificado no bitmap atual.
	/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, observe que este método não executa a conversão de formato, 
	/// e falhará se os formatos bitmap não coincidirem.
	/// </summary>
	/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
	/// <param name="Param_Bitmap">O bitmap para copiar.</param>
	/// <param name="Param_SourceRect">A área de bitmap para copiar.</param>
	static CarenResult CopyFromBitmap(
		ID2D1Bitmap* Param_MyPointerWork,
		CA_D2D1_POINT_2U^ Param_PointDestino,
		ICarenD2D1Bitmap^ Param_Bitmap,
		CA_D2D1_RECT_U^ Param_SourceRect);

	/// <summary>
	/// Copie a região especificada da memória para o bitmap atual.
	/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, note que este método não realiza conversão de formato; os dois 
	/// formatos bitmap devem coincidir.
	/// </summary>
	/// <param name="Param_DestinoRect">No bitmap atual, o retângulo para o qual a região especificada pelo (Param_SourceData) é copiada.</param>
	/// <param name="Param_SourceData">Os dados para copiar.</param>
	/// <param name="Param_Pitch">O passo, ou arremesso, do bitmap de origem armazenado em srcData. O passo é a contagem de byte de uma linha de varredura (uma linha de pixels na memória). O passo pode ser computado a partir 
	/// da seguinte fórmula: largura de pixel * bytes por pixel + preenchimento de memória.</param>
	static CarenResult CopyFromMemory(
		ID2D1Bitmap* Param_MyPointerWork,
		CA_D2D1_RECT_U^ Param_DestinoRect,
		ICarenBuffer^ Param_SourceData,
		UInt32 Param_Pitch);

	/// <summary>
	/// Copia a região especificada do alvo de renderização especificado no bitmap atual.
	/// </summary>
	/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
	/// <param name="Param_D2D1RenderTarget">O alvo de renderização que contém a região para copiar.</param>
	/// <param name="Param_SourceRect">A área do (Param_D2D1RenderTarget) para copiar.</param>
	static CarenResult CopyFromRenderTarget(
		ID2D1Bitmap* Param_MyPointerWork,
		CA_D2D1_POINT_2U^ Param_PointDestino,
		ICaren^ Param_D2D1RenderTarget,
		CA_D2D1_RECT_U^ Param_SourceRect);

	/// <summary>
	/// Retorne os pontos por polegada (DPI) do bitmap.
	/// </summary>
	/// <param name="Param_Out_DpiX">Retorna o DPI horizontal da imagem.</param>
	/// <param name="Param_Out_DpiY">Retorna o DPI vertical da imagem.</param>
	static void GetDpi(
		ID2D1Bitmap* Param_MyPointerWork,
		[Out] float% Param_Out_DpiX,
		[Out] float% Param_Out_DpiY);

	/// <summary>
	/// Recupera o formato de pixel e o modo alfa do bitmap.
	/// </summary>
	/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do bitmap.</param>
	static void GetPixelFormat(
		ID2D1Bitmap* Param_MyPointerWork,
		[Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat);

	/// <summary>
	/// Retorna o tamanho, em unidades dependentes de dispositivos (pixels), do bitmap.
	/// </summary>
	/// <param name="Param_Out_PixelSize">Retorna o tamanho, em pixels, do bitmap.</param>
	static void GetPixelSize(
		ID2D1Bitmap* Param_MyPointerWork,
		[Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize);

	/// <summary>
	/// Retorna o tamanho, em pixels independentes do dispositivo (DIPs), do bitmap.
	/// Um DIP é de 1/96 de polegada. Para recuperar o tamanho dos pixels do dispositivo, use o método ICarenD2D1Bitmap::GetPixelSize.
	/// </summary>
	/// <param name="Param_Out_Size">Retorna o tamanho, em DIPs, do bitmap.</param>
	static void GetSize(
		ID2D1Bitmap* Param_MyPointerWork,
		[Out] CA_D2D1_SIZE_F^% Param_Out_Size);
};

/// <summary>
/// 
/// </summary>
class Shared_D2D1Brush
{
	//Métodos da interface(ICarenD2D1Brush)
public:
	/// <summary>
	/// Obtém o grau de opacidade deste pincel.
	/// </summary>
	/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
	/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
	static void GetOpacity(
		ID2D1Brush* Param_MyPointerWork, 
		[Out] float% Param_Out_Opacidade);

	/// <summary>
	/// A transformação é aplicada a este pincel.
	/// </summary>
	/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
	static void GetTransform(
		ID2D1Brush* Param_MyPointerWork, 
		[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix);

	/// <summary>
	/// Define o grau de opacidade deste pincel.
	/// </summary>
	/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
	/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
	static void SetOpacity(
		ID2D1Brush* Param_MyPointerWork, 
		float Param_Opacidade);

	/// <summary>
	/// Define a transformação aplicada ao pincel.
	/// </summary>
	/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
	static void SetTransform(
		ID2D1Brush* Param_MyPointerWork, 
		CA_D2D1_MATRIX_3X2_F^ Param_Transform);
};

/// <summary>
/// 
/// </summary>
class Shared_D2D1BitmapBrush
{
	//Métodos da interface(ICarenD2D1BitmapBrush1)
public:
	/// <summary>
	/// Retorna o modo de interpolação atual do pincel.
	/// </summary>
	/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação atual.</param>
	static void GetInterpolationMode1(ID2D1BitmapBrush1* Param_MyPointerWork, [Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolationMode);

	/// <summary>
	/// Define o modo de interpolação para o pincel.
	/// [NOTA] Se (Param_InterpolationMode) não é um membro válido de D2D1_INTERPOLATION_MODE, então este método ignora silenciosamente a chamada.
	/// </summary>
	/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado.</param>
	static void SetInterpolationMode1(ID2D1BitmapBrush1* Param_MyPointerWork, CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode);



	//Métodos da interface(ICarenD2D1BitmapBrush)
public:
	/// <summary>
	/// Obtém a fonte bitmap que este pincel usa para pintar.
	/// </summary>
	/// <param name="Param_Out_Bitmap">Quando este método retorna, contém o endereço a um ponteiro para o bitmap com o qual este pincel pinta.</param>
	static CarenResult GetBitmap(ID2D1BitmapBrush* Param_MyPointerWork, [Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Obtém o método pelo qual a escova inclina horizontalmente as áreas que se estendem além de seu bitmap.
	/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
	/// </summary>
	/// <param name="Param_Out_ExtendModeX">Retorna um valor que especifica como a escova horizontalmente ladrilhos(Tile) as áreas que se estendem além de seu bitmap.</param>
	static void GetExtendModeX(ID2D1BitmapBrush* Param_MyPointerWork, [Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX);

	/// <summary>
	/// Obtém o método pelo qual a escova corta verticalmente as áreas que se estendem além de seu bitmap.
	/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
	/// </summary>
	/// <param name="Param_Out_ExtendModeY">Retorna um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
	static void GetExtendModeY(ID2D1BitmapBrush* Param_MyPointerWork, [Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY);

	/// <summary>
	/// Obtém o método de interpolação usado quando o bitmap da escova é dimensionado ou girado.
	/// </summary>
	/// <param name="Param_Out_InterpolationMode">Retorna o método de interpolação utilizado quando o bitmap da escova é dimensionado ou girado.</param>
	static void GetInterpolationMode(ID2D1BitmapBrush* Param_MyPointerWork, [Out] CA_D2D1_BITMAP_INTERPOLATION_MODE% Param_Out_InterpolationMode);

	/// <summary>
	/// Especifica a fonte bitmap que este pincel usa para pintar.
	/// Este método especifica a fonte bitmap que este pincel usa para pintar. O bitmap não é redimensionado ou redimensionado automaticamente para se encaixar na geometria que preenche. 
	/// O bitmap permanece em seu tamanho nativo. Para redimensionar ou traduzir o bitmap, use o método ICarenD2D1Brush::SetTransform para aplicar uma transformação no pincel.
	/// O tamanho nativo de um bitmap é a largura e altura em pixels bitmap, dividido pelo DPI bitmap. Este tamanho nativo forma o Tile do pincel. Para ladrilar uma sub-região do bitmap, 
	/// você deve gerar um novo bitmap contendo esta sub-região e usar SetBitmap para aplicá-lo no Brush.
	/// </summary>
	/// <param name="Param_Bitmap">Retorna a fonte de bitmap usada pelo pincel.</param>
	static CarenResult SetBitmap(ID2D1BitmapBrush* Param_MyPointerWork, ICarenD2D1Bitmap^ Param_Bitmap);

	/// <summary>
	/// Especifica como o Brush inclina horizontalmente as áreas que se estendem além de seu bitmap.
	/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
	/// vertical(SetExtendModeY) para determinar como preencher a área restante.
	/// </summary>
	/// <param name="Param_ExtendModeX">Um valor que especifica como o pincel monitora horizontalmente as áreas que ultrapassam seu bitmap.</param>
	static void SetExtendModeX(ID2D1BitmapBrush* Param_MyPointerWork, CA_D2D1_EXTEND_MODE Param_ExtendModeX);

	/// <summary>
	/// Especifica como o Brush ladrilhou(Tiled) verticalmente as áreas que se estendem além de seu bitmap.
	/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
	/// vertical(SetExtendModeY) para determinar como preencher a área restante.
	/// </summary>
	/// <param name="Param_ExtendModeY">Um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
	static void SetExtendModeY(ID2D1BitmapBrush* Param_MyPointerWork, CA_D2D1_EXTEND_MODE Param_ExtendModeY);

	/// <summary>
	/// Especifica o modo de interpolação usado quando o bitmap da escova é dimensionado ou girado.
	/// D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR representa a filtragem do vizinho mais próximo. Ele olha o pixel bitmap mais próximo do pixel de renderização atual e escolhe sua cor exata.
	/// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR representa filtragem linear e interpola uma cor dos quatro pixels de bitmap mais próximos.
	/// O modo de interpolação de um bitmap também afeta traduções subpixel. Em uma tradução subpixel, a interpolação bilinear posiciona o bitmap mais precisamente às solicitações do aplicativo, mas desfoca o bitmap no processo.
	/// </summary>
	/// <param name="Param_InterpolationMode">O modo de interpolação usado quando o bitmap do Brush é dimensionado ou girado.</param>
	static void SetInterpolationMode(ID2D1BitmapBrush* Param_MyPointerWork, CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode);
};