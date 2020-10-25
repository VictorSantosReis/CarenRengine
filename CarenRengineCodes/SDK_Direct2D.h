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
#include "SDK_Base.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace Direct2D
	{
		/// <summary>
		/// (ID2D1Resource) - Interface responsável por representar um recurso de desenho Direct2D.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("31EC0474-6475-41B7-8E77-CBCF0FAE5F55")]
		public interface class ICarenD2D1Resource : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera a fábrica associada a este recurso.
			/// </summary>
			/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
			void GetFactory(ICaren^ Param_Out_Factory);
		};

		/// <summary>
		/// (ID2D1Image) - Interface responsável por representar um produtor de pixels que pode preencher um plano 2D arbitrário.
		/// Está interface é abstrata. Instâncias concretas podem ser criadas através de ICarenD2D1DeviceContext::CreateEffect e ICarenD2D1DeviceContext::CreateBitmap.
		/// As imagens são avaliadas preguiçosamente. Se o tipo de imagem passada é concreto, a imagem pode ser amostrada diretamente. Outras imagens podem atuar apenas como uma fonte de 
		/// pixels e podem produzir conteúdo apenas como resultado da chamada de ICarenD2D1DeviceContext::DrawImage.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("7B59073E-FA35-44F6-AABD-1A1850CFD633")]
		public interface class ICarenD2D1Image : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID2D1ImageSource) - Interface responsável por representar um produtor de pixels que pode encher um plano 2D arbitrário.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("2938DDA9-CDD6-41AA-9B2E-E8578995024E")]
		public interface class ICarenD2D1ImageSource : ICarenD2D1Image
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Permite que o sistema operacional livre a memória de vídeo dos recursos descartando seu conteúdo.
			/// </summary>
			CarenResult OfferResources();

			/// <summary>
			/// Restaura o acesso aos recursos que foram oferecidos anteriormente pelo chamada OfferResources.
			/// </summary>
			/// <param name="Param_Out_RecursoDescartado">Retorna com TRUE se o conteúdo do recurso correspondente foi descartado e agora está indefinido ou FALSO se o conteúdo antigo do recurso correspondente ainda estiver intacto. 
			/// O chamador pode passar NULO, se o chamador pretende preencher os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
			CarenResult TryReclaimResources([Out] Boolean% Param_Out_RecursoDescartado);
		};

		/// <summary>
		/// (ID2D1ImageSourceFromWic) - Interface responsável por produzir dados de pixels 2D que foram originários da API WIC.
		/// Crie uma instância desta interface utilizando o método ICarenD2D1DeviceContext2::CreateImageSourceFromWic.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9C92F870-C619-40BF-BF12-61E68F7AFD0C")]
		public interface class ICarenD2D1ImageSourceFromWic : ICarenD2D1ImageSource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Garante que uma região especificada do cache de origem da imagem seja preenchida. Este método pode ser usado para minimizar falhas realizando trabalhos caros para preencher caches fora de um loop de renderização. 
			/// Este método também pode ser usado para carregar especulativamente dados de imagem antes de serem necessários por meio do desenho de rotinas.
			/// </summary>
			/// <param name="Param_RegiaoRetangulo">Especifica a região da imagem, em pixels, que deve ser preenchida no cache. Por padrão, esta é toda a extensão da imagem.</param>
			CarenResult EnsureCached(CA_D2D1_RECT_U^ Param_RegiaoRetangulo);

			/// <summary>
			/// Recupera a fonte de imagem do bitmap subjacente do Componente de Imagem do Windows (WIC).
			/// </summary>
			/// <param name="Param_Out_WicBitmapSource">Retorna um ponteiro para a interface (ICarenWICBitmapSource) que representa a fonte do bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
			void GetSource(ICaren^ Param_Out_WicBitmapSource);

			/// <summary>
			/// Este método apara as regiões povoadas do cache de fonte de imagem apenas para o retângulo especificado.
			/// A região fornecida deve ser construída para incluir a escala em que a fonte de imagem será desenhada. Essas coordenadas devem ser fornecidas em coordenadas locais.
			/// Isso significa que eles devem ser ajustados antes de chamar a API de acordo com o DPI e outras transformações relevantes, que podem incluir a transformação do mundo e as transformações de pincel.
			/// </summary>
			/// <param name="Param_RegiaoPreservaRetangulo">Especifica a região da imagem, em pixels, que deve ser preservada no cache de fonte de imagem. Regiões que estão fora do retângulo são despejadas do cache. 
			/// Por padrão, este é um retângulo vazio, o que significa que toda a imagem é despejada do cache.</param>
			CarenResult TrimCache(CA_D2D1_RECT_U^ Param_RegiaoPreservaRetangulo);
		};

		/// <summary>
		/// (ID2D1TransformedImageSource) - Interface responsável por representar uma fonte de imagem que compartilha recursos com uma fonte de imagem original.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("3BC82F92-F306-4EA4-9B95-988043435D98")]
		public interface class ICarenD2D1TransformedImageSource : ICarenD2D1Image
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera as propriedades especificadas quando a fonte de imagem transformada foi criada. Esse valor corresponde ao valor repassado ao ICarenD2D1DeviceContext2::CreateTransformedImageSource.
			/// </summary>
			/// <param name="Param_Out_Propriedades">Retorna as propriedades especificadas quando a fonte de imagem transformada foi criada.</param>
			void GetProperties(
				[Out] CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^% Param_Out_Propriedades);

			/// <summary>
			/// Recupera a imagem de origem usada para criar a fonte de imagem transformada. Esse valor corresponde ao valor repassado ao ICarenD2D1DeviceContext2::CreateTransformedImageSource.
			/// </summary>
			/// <param name="Param_Out_ImageSource">Recupera a imagem de origem usada para criar a fonte de imagem transformada.</param>
			void GetSource([Out] ICarenD2D1ImageSource^% Param_Out_ImageSource);
		};

		/// <summary>
		/// (ID2D1ColorContext) - Interface responsável por representar um contexto de cores que pode ser usado com um objeto ICarenD2D1Bitmap1.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("5F0F541E-16D5-47B9-94D7-37C7082F23DC")]
		public interface class ICarenD2D1ColorContext : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o espaço de cores do contexto de cores.
			/// </summary>
			/// <param name="Param_Out_EspacoCor">Retorna uma enumeração que contém o espaço de cores do contexto.</param>
			void GetColorSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);

			/// <summary>
			/// Obtém o bytes de perfil de cor para um ICarenD2D1ColorContext.
			/// </summary>
			/// <param name="Param_Out_ColorProfile">Retorna um buffer que contém o perfil de cores.</param>
			/// <param name="Param_ProfileSize">O tamanho do buffer de perfil.</param>
			CarenResult GetProfile(
				[Out] cli::array<Byte>^% Param_Out_ColorProfile,
				UInt32 Param_ProfileSize);

			/// <summary>
			/// Obtém o tamanho do perfil de cor associado ao bitmap.
			/// </summary>
			/// <param name="Param_Out_ProfileSize">Retorna o tamanho do perfil em bytes.</param>
			void GetProfileSize([Out] UInt32% Param_Out_ProfileSize);
		};

		/// <summary>
		/// (ID2D1ColorContext1) - Interface responsável por representar um contexto de cor a ser usado com o Efeito de Gerenciamento de Cores.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("B0A5F066-851D-48E8-BD41-EF59D40C7E8E")]
		public interface class ICarenD2D1ColorContext1 : ICarenD2D1ColorContext
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o tipo de contexto de cor.
			/// </summary>
			/// <param name="Param_Out_ColorContext">Retorna o tipo de contexto de cores.</param>
			void GetColorContextType([Out] CA_D2D1_COLOR_CONTEXT_TYPE% Param_Out_ColorContext);

			/// <summary>
			/// Recupera o espaço de cores DXGI deste contexto. Retorna DXGI_COLOR_SPACE_CUSTOM quando o tipo de contexto de cor é ICC.
			/// </summary>
			/// <param name="Param_Out_DXGIColorSpace">Retorna o espaço de cor DXGI deste contexto.</param>
			void GetDXGIColorSpace([Out] CA_DXGI_COLOR_SPACE_TYPE% Param_Out_DXGIColorSpace);

			/// <summary>
			/// Recupera um perfil de cor simples.
			/// </summary>
			/// <param name="Param_Out_ColorProfile">Retorna uma estrutura CA_D2D1_SIMPLE_COLOR_PROFILE que conterá o perfil de cor simples quando o método retornar.</param>
			CarenResult GetSimpleColorProfile([Out] CA_D2D1_SIMPLE_COLOR_PROFILE^% Param_Out_ColorProfile);
		};

		/// <summary>
		/// (ID2D1Bitmap) - Interface responsável por representar um bitmap que foi vinculado a um ICarenD2D1RenderTarget.
		/// Um ID2D1Bitmap é um recurso dependente do dispositivo: seu aplicativo deve criar bitmaps depois de inicializar o alvo de renderização com o qual o bitmap será usado e recriar o bitmap sempre que o alvo de renderização precisar ser recriado. 
		/// Para criar um bitmap, use um dos seguintes métodos do alvo de renderização no qual o bitmap será desenhado: ICarenD2D1RenderTarget::CreateBitmap ou ICarenD2D1RenderTarget::CreateBitmapFromWicBitmap.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F10A66AE-CB42-40D7-ACFD-C13B74D99F28")]
		public interface class ICarenD2D1Bitmap : ICarenD2D1Image
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Copia a região especificada do bitmap especificado no bitmap atual.
			/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, observe que este método não executa a conversão de formato, 
			/// e falhará se os formatos bitmap não coincidirem.
			/// </summary>
			/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
			/// <param name="Param_Bitmap">O bitmap para copiar.</param>
			/// <param name="Param_SourceRect">A área de bitmap para copiar.</param>
			CarenResult CopyFromBitmap(
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
			CarenResult CopyFromMemory(
				CA_D2D1_RECT_U^ Param_DestinoRect,
				ICarenBuffer^ Param_SourceData,
				UInt32 Param_Pitch);

			/// <summary>
			/// Copia a região especificada do alvo de renderização especificado no bitmap atual.
			/// </summary>
			/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
			/// <param name="Param_D2D1RenderTarget">O alvo de renderização que contém a região para copiar.</param>
			/// <param name="Param_SourceRect">A área do (Param_D2D1RenderTarget) para copiar.</param>
			CarenResult CopyFromRenderTarget(
				CA_D2D1_POINT_2U^ Param_PointDestino,
				ICaren^ Param_D2D1RenderTarget,
				CA_D2D1_RECT_U^ Param_SourceRect);

			/// <summary>
			/// Retorne os pontos por polegada (DPI) do bitmap.
			/// </summary>
			/// <param name="Param_Out_DpiX">Retorna o DPI horizontal da imagem.</param>
			/// <param name="Param_Out_DpiY">Retorna o DPI vertical da imagem.</param>
			void GetDpi(
				[Out] float% Param_Out_DpiX,
				[Out] float% Param_Out_DpiY);

			/// <summary>
			/// Recupera o formato de pixel e o modo alfa do bitmap.
			/// </summary>
			/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do bitmap.</param>
			void GetPixelFormat(
				[Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat);

			/// <summary>
			/// Retorna o tamanho, em unidades dependentes de dispositivos (pixels), do bitmap.
			/// </summary>
			/// <param name="Param_Out_PixelSize">Retorna o tamanho, em pixels, do bitmap.</param>
			void GetPixelSize(
				[Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize);

			/// <summary>
			/// Retorna o tamanho, em pixels independentes do dispositivo (DIPs), do bitmap.
			/// Um DIP é de 1/96 de polegada. Para recuperar o tamanho dos pixels do dispositivo, use o método ICarenD2D1Bitmap::GetPixelSize.
			/// </summary>
			/// <param name="Param_Out_Size">Retorna o tamanho, em DIPs, do bitmap.</param>
			void GetSize(
				[Out] CA_D2D1_SIZE_F^% Param_Out_Size);

		};

		/// <summary>
		/// (ID2D1Bitmap1) - Interface responsável por representar um bitmap que pode ser usado como uma superfície para um ICarenD2D1DeviceContext ou mapeado na memória do sistema, e pode conter informações adicionais de 
		/// contexto de cores. Um ICarenD2D1Bitmap é um recurso dependente do dispositivo: seu aplicativo deve criar bitmaps depois de inicializar o alvo de renderização com o qual o bitmap será usado e recriar o bitmap sempre que o alvo de renderização 
		/// precisar ser recriado. Use um desses métodos para criar um objeto ID2D1Bitmap: ICarenD2D1RenderTarget::CreateBitmap ou ICarenD2D1RenderTarget::CreateBitmapFromWicBitmap.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("36301959-4060-412E-B008-F821FBE3187A")]
		public interface class ICarenD2D1Bitmap1 : ICarenD2D1Bitmap
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém as informações de contexto de cores associadas ao bitmap.
			/// </summary>
			/// <param name="Param_Out_ColorContext">Quando este método retorna, contém o endereço de um ponteiro para a interface de contexto de cor associada ao bitmap.</param>
			CarenResult GetColorContext(
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Obtém as opções usadas na criação do bitmap.
			/// </summary>
			/// <param name="Param_Out_BitmapOptions">Retorna as opções utilizadas.</param>
			void GetOptions(
				[Out] CA_D2D1_BITMAP_OPTIONS% Param_Out_BitmapOptions);

			/// <summary>
			/// Obtém a superfície especificada quando o bitmap foi criado, ou a superfície padrão criada quando o bitmap foi criado.
			/// O bitmap usado deve ter sido criado a partir de um alvo de renderização de superfície DXGI, um alvo de renderização derivada ou um contexto de dispositivo criado a partir de um ICarenD2D1Device. 
			/// A superfície devolvida pode ser usada com o Microsoft Direct3D ou qualquer outra API que interopera com superfícies compartilhadas.
			/// </summary>
			/// <param name="Param_Out_DxgiSurface">Retorna a superfície DXGI subjacente para o bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult GetSurface(ICaren^ Param_Out_DxgiSurface);

			/// <summary>
			/// Mapeia os dados do Bitmap na memória. O bitmap deve ter sido criado com a bandeira D2D1_BITMAP_OPTIONS_CPU_READ especificada para este método poder funcionar.
			/// [NOTA] Você não pode usar bitmaps para alguns propósitos enquanto mapeado. Particularmente, o método ICarenD2D1Bitmap::CopyFromBitmap não funciona se o bitmap de origem ou destino estiver mapeado.
			/// </summary>
			/// <param name="Param_Options">As opções utilizadas no mapeamento do bitmap na memória.</param>
			/// <param name="Param_Out_MappedRect">Quando este método retorna, contém uma referência ao retângulo que foi mapeado na memória. O usuário deve definir o tamanho do buffer(bits) dentro da estrutura antes de usar.</param>
			CarenResult Map(
				CA_D2D1_MAP_OPTIONS Param_Options,
				[Out] CA_D2D1_MAPPED_RECT^% Param_Out_MappedRect);

			/// <summary>
			/// Desmapeia o bitmap da memória. Qualquer memória retornada da chamada Mapa agora é inválida e pode ser recuperada pelo sistema operacional ou usada para outros fins. 
			/// O bitmap deve ter sido previamente mapeado.
			/// </summary>
			CarenResult Unmap();
		};

		/// <summary>
		/// (ID2D1Brush) - Interface responsável por definir um objeto que pinta uma área. Interfaces derivadas do ICarenD2D1Brush descrevem como a área é pintada.
		/// Um ICarenD2D1BitmapBrush é um recurso dependente do dispositivo: seu aplicativo deve criar pincéis bitmap depois de inicializar o alvo de renderização com o qual o Brush de bitmap será usada e recriar a Brush de bitmap 
		/// sempre que o alvo de renderização precisar ser recriado. 
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("7A7A0672-A71E-4DF5-B342-DDE0F786C681")]
		public interface class ICarenD2D1Brush : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o grau de opacidade deste pincel.
			/// </summary>
			/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
			/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
			void GetOpacity([Out] float% Param_Out_Opacidade);

			/// <summary>
			/// A transformação é aplicada a este pincel.
			/// </summary>
			/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
			void GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix);

			/// <summary>
			/// Define o grau de opacidade deste pincel.
			/// </summary>
			/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
			/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
			void SetOpacity(float Param_Opacidade);

			/// <summary>
			/// Define a transformação aplicada ao pincel.
			/// </summary>
			/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
			void SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);


		};

		/// <summary>
		/// (ID2D1BitmapBrush) - Interface responsável por pintar uma área com um bitmap.
		/// Um pincel bitmap é usado para preencher uma geometria com um bitmap. Como todos os pincéis, define um plano infinito de conteúdo. Como os bitmaps são finitos, o pincel conta com um "modo de extensão" para determinar como o 
		/// plano é preenchido horizontal e verticalmente.
		/// Para criar um pincel bitmap, use o método ICarenD2D1RenderTarget::CreateBitmapBrush.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("6FB27969-6832-4919-BE45-46EACA685B50")]
		public interface class ICarenD2D1BitmapBrush : ICarenD2D1Brush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a fonte bitmap que este pincel usa para pintar.
			/// </summary>
			/// <param name="Param_Out_Bitmap">Quando este método retorna, contém o endereço a um ponteiro para o bitmap com o qual este pincel pinta.</param>
			CarenResult GetBitmap([Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Obtém o método pelo qual a escova inclina horizontalmente as áreas que se estendem além de seu bitmap.
			/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
			/// </summary>
			/// <param name="Param_Out_ExtendModeX">Retorna um valor que especifica como a escova horizontalmente ladrilhos(Tile) as áreas que se estendem além de seu bitmap.</param>
			void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX);

			/// <summary>
			/// Obtém o método pelo qual a escova corta verticalmente as áreas que se estendem além de seu bitmap.
			/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
			/// </summary>
			/// <param name="Param_Out_ExtendModeY">Retorna um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
			void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY);

			/// <summary>
			/// Obtém o método de interpolação usado quando o bitmap da escova é dimensionado ou girado.
			/// </summary>
			/// <param name="Param_Out_InterpolationMode">Retorna o método de interpolação utilizado quando o bitmap da escova é dimensionado ou girado.</param>
			void GetInterpolationMode([Out] CA_D2D1_BITMAP_INTERPOLATION_MODE% Param_Out_InterpolationMode);

			/// <summary>
			/// Especifica a fonte bitmap que este pincel usa para pintar.
			/// Este método especifica a fonte bitmap que este pincel usa para pintar. O bitmap não é redimensionado ou redimensionado automaticamente para se encaixar na geometria que preenche. 
			/// O bitmap permanece em seu tamanho nativo. Para redimensionar ou traduzir o bitmap, use o método ICarenD2D1Brush::SetTransform para aplicar uma transformação no pincel.
			/// O tamanho nativo de um bitmap é a largura e altura em pixels bitmap, dividido pelo DPI bitmap. Este tamanho nativo forma o Tile do pincel. Para ladrilar uma sub-região do bitmap, 
			/// você deve gerar um novo bitmap contendo esta sub-região e usar SetBitmap para aplicá-lo no Brush.
			/// </summary>
			/// <param name="Param_Bitmap">Retorna a fonte de bitmap usada pelo pincel.</param>
			CarenResult SetBitmap(ICarenD2D1Bitmap^ Param_Bitmap);

			/// <summary>
			/// Especifica como o Brush inclina horizontalmente as áreas que se estendem além de seu bitmap.
			/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
			/// vertical(SetExtendModeY) para determinar como preencher a área restante.
			/// </summary>
			/// <param name="Param_ExtendModeX">Um valor que especifica como o pincel monitora horizontalmente as áreas que ultrapassam seu bitmap.</param>
			void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ExtendModeX);

			/// <summary>
			/// Especifica como o Brush ladrilhou(Tiled) verticalmente as áreas que se estendem além de seu bitmap.
			/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
			/// vertical(SetExtendModeY) para determinar como preencher a área restante.
			/// </summary>
			/// <param name="Param_ExtendModeY">Um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
			void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ExtendModeY);

			/// <summary>
			/// Especifica o modo de interpolação usado quando o bitmap da escova é dimensionado ou girado.
			/// D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR representa a filtragem do vizinho mais próximo. Ele olha o pixel bitmap mais próximo do pixel de renderização atual e escolhe sua cor exata.
			/// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR representa filtragem linear e interpola uma cor dos quatro pixels de bitmap mais próximos.
			/// O modo de interpolação de um bitmap também afeta traduções subpixel. Em uma tradução subpixel, a interpolação bilinear posiciona o bitmap mais precisamente às solicitações do aplicativo, mas desfoca o bitmap no processo.
			/// </summary>
			/// <param name="Param_InterpolationMode">O modo de interpolação usado quando o bitmap do Brush é dimensionado ou girado.</param>
			void SetInterpolationMode(CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode);
		};

		/// <summary>
		/// (ID2D1BitmapBrush1) - Interface responsável por pintar uma área com um bitmap.
		/// Um pincel bitmap é usado para preencher uma geometria com um bitmap. Como todos os pincéis, define um plano infinito de conteúdo. Como os bitmaps são finitos, o pincel conta com um "modo de extensão" para determinar como o 
		/// plano é preenchido horizontal e verticalmente.
		/// Para criar um pincel bitmap, use o método ICarenD2D1RenderTarget::CreateBitmapBrush.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8A1DA339-C4A5-4C7B-8177-82F4B7555492")]
		public interface class ICarenD2D1BitmapBrush1 : ICarenD2D1BitmapBrush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Retorna o modo de interpolação atual do pincel.
			/// </summary>
			/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação atual.</param>
			void GetInterpolationMode1([Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolationMode);

			/// <summary>
			/// Define o modo de interpolação para o pincel.
			/// [NOTA] Se (Param_InterpolationMode) não é um membro válido de D2D1_INTERPOLATION_MODE, então este método ignora silenciosamente a chamada.
			/// </summary>
			/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado.</param>
			void SetInterpolationMode1(CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode);
		};

		/// <summary>
		/// (ID2D1ImageBrush) - Interface responsável por representar um pincel baseado em um ICarenD2D1Image.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8490FC4F-AFC8-4161-B85A-CDD55177D909")]
		public interface class ICarenD2D1ImageBrush : ICarenD2D1Brush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o modo de extensão do pincel de imagem no eixo x. 
			/// </summary>
			/// <param name="Param_Out_ModeExtendidoX">Retorna o modo extendido no eixo X.</param>
			void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoX);

			/// <summary>
			/// Obtém o modo de extensão do pincel de imagem no eixo y da imagem. 
			/// </summary>
			/// <param name="Param_Out_ModeExtendidoY">Retorna o modo extendido no eixo Y.</param>
			void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoY);

			/// <summary>
			/// Obtém a imagem associada ao pincel de imagem. 
			/// </summary>
			/// <param name="Param_Out_Image">Quando este método retorna, contém o endereço de um ponteiro para a imagem associada a este pincel.</param>
			CarenResult GetImage([Out] ICarenD2D1Image^% Param_Out_Image);

			/// <summary>
			/// Obtém o modo de interpolação do pincel de imagem.
			/// </summary>
			/// <param name="Param_Out_InterpolatonMode">Retorna o modo de interpolação.</param>
			void GetInterpolationMode([Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolatonMode);

			/// <summary>
			/// Obtém o retângulo que será usado como os limites da imagem quando desenhado como um pincel de imagem. 
			/// </summary>
			/// <param name="Param_Out_RetanguloOrigem">Quando este método retorna, contém a estrutura do retângulo de origem de saída.</param>
			void GetSourceRectangle([Out] CA_D2D1_RECT_F^% Param_Out_RetanguloOrigem);

			/// <summary>
			/// Define como o conteúdo dentro do retângulo de origem no Brush de imagem será estendido no eixo X. 
			/// </summary>
			/// <param name="Param_ModeExtendidoX">O modo de extensão no eixo X da imagem.</param>
			void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ModeExtendidoX);

			/// <summary>
			/// Define o modo de extensão no eixo Y. 
			/// </summary>
			/// <param name="Param_ModeExtendidoY">O modo de extensão no eixo Y da imagem.</param>
			void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ModeExtendidoY);

			/// <summary>
			/// Define a imagem associada à escova de imagem fornecida. 
			/// </summary>
			/// <param name="Param_Image">A imagem a ser associada com o pincel de imagem.</param>
			CarenResult SetImage(ICarenD2D1Image^ Param_Image);

			/// <summary>
			/// Define o modo de interpolação para o pincel de imagem. 
			/// </summary>
			/// <param name="Param_InterpolationMode">Define como o conteúdo da imagem será interpolado para lidar com a transformação do pincel.</param>
			void SetInterpolationMode(CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode);

			/// <summary>
			/// Define o retângulo de origem na escova de imagem. 
			/// </summary>
			/// <param name="Param_OrigemRetangulo">O retângulo de origem que define a parte da imagem para ladrilho(Tile).</param>
			void SetSourceRectangle(CA_D2D1_RECT_F^ Param_OrigemRetangulo);
		};

		/// <summary>
		/// (ID2D1GradientStopCollection) - Interface responsável por representar uma coleção de objetos D2D1_GRADIENT_STOP para Brushs gradientes lineares e radiais.
		/// Uma coleção de parada de gradiente é um recurso dependente do dispositivo: seu aplicativo deve criar coleções de parada de gradiente depois de inicializar o alvo de renderização com o qual a coleção de parada de 
		/// gradiente será usada e recriar a coleção de parada de gradiente sempre que o alvo de renderização precisar ser recriado. 
		/// Para criar um ICarenD2D1GradientStopCollection, use o método ICarenD2D1RenderTarget::CreateGradientStopCollection.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("39CFC376-D2F0-42C5-B929-29C0C732EAFF")]
		public interface class ICarenD2D1GradientStopCollection : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Indica o espaço gama em que as paradas gradientes são interpoladas.
			/// </summary>
			/// <param name="Param_Out_GammaSpace">Retorna o espaço gama em que as paradas gradientes são interpoladas.</param>
			void GetColorInterpolationGamma([Out] CA_D2D1_GAMMA% Param_Out_GammaSpace);

			/// <summary>
			/// Indica o comportamento do gradiente fora da faixa de gradiente normalizada. 
			/// </summary>
			/// <param name="Param_Out_ExtendMode">Retorna o comportamento do gradiente fora da faixa de gradiente normalizada.</param>
			void GetExtendMode([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendMode);

			/// <summary>
			/// Recupera o número de paradas gradientes na coleção. 
			/// </summary>
			/// <param name="Param_Out_CountGradientes">Retorna o número de gradientes para na coleção.</param>
			void GetGradientStopCount([Out] UInt32% Param_Out_CountGradientes);

			/// <summary>
			/// Copia as paradas gradientes da coleção em uma matriz de estruturas D2D1_GRADIENT_STOP. 
			/// </summary>
			/// <param name="Param_Out_ArrayGradientStop">Uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP. Quando este método retorna, a matriz contém cópias do gradiente da coleção de parada.</param>
			/// <param name="Param_QuantidadeGradientes">Um valor indicando o número de paradas gradientes para copiar. Se o valor for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes 
			/// são omitidas. Se o valor for maior do que o número de paradas de gradiente na coleção, as paradas de gradiente extra são definidas como NULO. Para obter o número de paradas gradientes na coleção, use o método 
			/// GetGradientStopCount.</param>
			void GetGradientStops(
				[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
				UInt32 Param_QuantidadeGradientes);
		};

		/// <summary>
		/// (ID2D1GradientStopCollection1) - Interface responsável por representar uma coleção de objetos D2D1_GRADIENT_STOP para Brushs gradientes lineares e radiais.
		/// Está interface estende os métodos da interface ICarenD2D1GradientStopCollection.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("908ADAF9-B683-400D-8634-82CDD54684D6")]
		public interface class ICarenD2D1GradientStopCollection1 : ICarenD2D1GradientStopCollection
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a precisão do Buffer de gradiente. 
			/// Se esse objeto foi criado usando ICarenD2D1RenderTarget::CreateGradientStopCollection, este método retorna D2D1_BUFFER_PRECISION_8BPC_UNORM.
			/// </summary>
			/// <param name="Param_Out_PrecisaoBuffer">Retorna o Buffer de precisão do Gradiente.</param>
			void GetBufferPrecision([Out] CA_D2D1_BUFFER_PRECISION% Param_Out_PrecisaoBuffer);

			/// <summary>
			/// Recupera o modo de interpolação de cores que a coleção de parada de gradiente usa.
			/// </summary>
			/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação de cores.</param>
			void GetColorInterpolationMode([Out] CA_D2D1_COLOR_INTERPOLATION_MODE% Param_Out_InterpolationMode);

			/// <summary>
			/// Copia as paradas de gradiente da coleção para a memória. 
			/// </summary>
			/// <param name="Param_Out_ArrayGradientStop">Retorna uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP.</param>
			/// <param name="Param_QuantidadeGradientes">O número de gradientes para copiar. Se for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes sao omitidas. 
			/// Se Param_QuantidadeGradientes for maior do que o número de paradas gradientes na coleção, as paradas de gradiente extra são definidas como NULO.</param>
			void GetGradientStops1(
				[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
				UInt32 Param_QuantidadeGradientes);

			/// <summary>
			/// Obtém o espaço de cores após a interpolação. 
			/// </summary>
			/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
			void GetPostInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);

			/// <summary>
			/// Obtém o espaço de cores das cores de entrada, bem como o espaço em que as paradas gradientes são interpoladas. 
			/// </summary>
			/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
			void GetPreInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);
		};

		/// <summary>
		/// (ID2D1LinearGradientBrush) - Interface responsável por pintar uma área com um gradiente linear.
		/// Um ICarenD2D1LinearGradientBrush pinta uma área com um gradiente linear ao longo de uma linha entre o ponto de partida do Brush e o ponto final. O gradiente, definido pelo pincel ICarenD2D1GradientStopCollection, 
		/// é extrudado perpendicular a esta linha e, em seguida, transformado por uma transformação de pincel (se especificado).
		/// Para criar um Brush de gradiente linear, use o método ICarenD2D1RenderTarget::CreateLinearGradientBrush do alvo de renderização no qual o pincel será usado. O pincel só pode ser usado com o alvo render que o criou 
		/// ou com os alvos compatíveis para esse alvo de renderização.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("CE9A2448-5C7C-4D26-A660-5708DA026CA3")]
		public interface class ICarenD2D1LinearGradientBrush : ICarenD2D1Brush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera as coordenadas finais do gradiente linear. 
			/// </summary>
			/// <param name="Param_Out_EndPoint">Retorna as coordenadas bidimensionais finais do gradiente linear, no espaço de coordenadas do pincel.</param>
			void GetEndPoint([Out] CA_D2D1_POINT_2F^% Param_Out_EndPoint);

			/// <summary>
			/// Recupera a ICarenD2D1GradientStopCollection associada a este pincel gradiente linear. 
			/// ICarenD2D1GradientStopCollection contém uma série de estruturas e informações CA_D2D1_GRADIENT_STOP, como o modo de extensão e o modo de interpolação de cores.
			/// </summary>
			/// <param name="Param_Out_GradientStopCollection">Retorna a interface ID2D1GradientStopCollection associado a este objeto de pincel gradiente linear.</param>
			CarenResult GetGradientStopCollection(
				[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

			/// <summary>
			/// Recupera as coordenadas iniciais do gradiente linear.
			/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
			/// o ponto de partida e o ponto final do pincel também serão transformados.
			/// </summary>
			/// <param name="Param_Out_StartPoint">Retorna as coordenadas bidimensionais iniciais do gradiente linear, no espaço de coordenadas da escova.</param>
			void GetStartPoint([Out] CA_D2D1_POINT_2F^% Param_Out_StartPoint);

			/// <summary>
			/// Define as coordenadas finais do gradiente linear no espaço de coordenadas do Brush.
			/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
			/// o ponto de partida e o ponto final do pincel também serão transformados.
			/// </summary>
			/// <param name="Param_EndPoint">As coordenadas bidimensionais finais do gradiente linear, no espaço de coordenadas do pincel.</param>
			void SetEndPoint(CA_D2D1_POINT_2F^ Param_EndPoint);

			/// <summary>
			/// Define as coordenadas iniciais do gradiente linear no espaço de coordenadas do Brush.
			/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
			/// o ponto de partida e o ponto final do pincel também serão transformados.
			/// </summary>
			/// <param name="Param_StartPoint">As coordenadas bidimensionais iniciais do gradiente linear, no espaço de coordenadas da escova.</param>
			void SetStartPoint(CA_D2D1_POINT_2F^ Param_StartPoint);
		};

		/// <summary>
		/// (ID2D1RadialGradientBrush) - Interface responsável por pintar uma área com um gradiente radial.
		/// O ICarenD2D1RadialGradientBrush é semelhante ao ICarenD2D1LinearGradientBrush, na linha de chegada, pois ambos mapeiam uma coleção de paradas gradientes para um gradiente. No entanto, o gradiente linear tem um início 
		/// e um ponto final para definir o vetor gradiente, enquanto o gradiente radial usa uma elipse e uma origem gradiente para definir seu comportamento gradiente.
		/// Para criar um pincel gradiente radial, use o método ICarenD2D1RenderTarget::CreateRadialGradientBrush do alvo de renderização no qual o pincel será usado. O pincel só pode ser usado com o alvo renderizado que o criou 
		/// ou com os alvos compatíveis para esse alvo de renderização.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("E565A520-BF3B-4ABA-9734-471392A11EEA")]
		public interface class ICarenD2D1RadialGradientBrush : ICarenD2D1Brush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o centro da elipse gradiente.
			/// </summary>
			/// <param name="Param_Out_Center">Retorna o centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
			void GetCenter([Out] CA_D2D1_POINT_2F^% Param_Out_Center);

			/// <summary>
			/// Recupera o deslocamento da origem gradiente em relação ao centro da elipse gradiente. 
			/// </summary>
			/// <param name="Param_Out_GradientOriginOffset">Retorna A compensação da origem gradiente do centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
			void GetGradientOriginOffset([Out] CA_D2D1_POINT_2F^% Param_Out_GradientOriginOffset);

			/// <summary>
			/// Recupera a ICarenD2D1GradientStopCollection associada a este objeto do Brush de gradiente radial. 
			/// </summary>
			/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection associado a este objeto de pincel gradiente linear. Este parâmetro é passado unnitializado.</param>
			CarenResult GetGradientStopCollection(
				[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

			/// <summary>
			/// Recupera o raio X da elipse gradiente. 
			/// </summary>
			/// <param name="Param_Out_RadiusX">Retorna raio X da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
			void GetRadiusX([Out] float% Param_Out_RadiusX);

			/// <summary>
			/// Recupera o raio Y da elipse gradiente. 
			/// </summary>
			/// <param name="Param_Out_RadiusY">Retorna raio Y da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
			void GetRadiusY([Out] float% Param_Out_RadiusY);

			/// <summary>
			/// Especifica o centro da elipse gradiente no espaço de coordenadas do Brush. 
			/// </summary>
			/// <param name="Param_Center">O centro da elipse gradiente, no espaço de coordenadas do pincel.</param>
			void SetCenter(CA_D2D1_POINT_2F^ Param_Center);

			/// <summary>
			/// Especifica a compensação da origem gradiente em relação ao centro da elipse gradiente. 
			/// </summary>
			/// <param name="Param_GradientOriginOffset">A compensação da origem gradiente do centro da elipse gradiente.</param>
			void SetGradientOriginOffset(CA_D2D1_POINT_2F^ Param_GradientOriginOffset);

			/// <summary>
			/// Especifica o raio X da elipse gradiente, no espaço de coordenadas do Brush. 
			/// </summary>
			/// <param name="Param_RadiusX">O raio X da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
			void SetRadiusX(float Param_RadiusX);

			/// <summary>
			/// Especifica o raio Y da elipse gradiente, no espaço de coordenadas da escova. 
			/// </summary>
			/// <param name="Param_RadiusY">O raio Y da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
			void SetRadiusY(float Param_RadiusY);
		};

		/// <summary>
		/// (ID2D1SolidColorBrush) - Interface responsável por pintar uma área com uma cor sólida.
		/// Um Brush de cores sólidas é um recurso dependente do dispositivo.
		/// Para criar um pincel de cor sólida, use o método ICarenD2D1RenderTarget::CreateSolidColorBrush do alvo de renderização no qual o pincel será usado. O pincel só pode ser usado com o alvo render que o criou ou com 
		/// os alvos compatíveis para esse alvo de renderização.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("465E3340-BEDD-40B0-81DA-72F57FDFCD7A")]
		public interface class ICarenD2D1SolidColorBrush : ICarenD2D1Brush
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera a cor do pincel de cor sólida. 
			/// </summary>
			/// <param name="Param_Out_Cor">Recupera a cor sólida deste pincel.</param>
			void GetColor([Out] CA_D2D1_COLOR_F^% Param_Out_Cor);

			/// <summary>
			/// Especifica a cor deste pincel de cor sólida. 
			/// </summary>
			/// <param name="Param_Cor">A cor sólida a ser definida a este pincel.</param>
			void SetColor(CA_D2D1_COLOR_F^ Param_Cor);
		};

		/// <summary>
		/// (ID2D1StrokeStyle) - Interface responsável por descrever os Caps, limite de Miter, Line Join e informações de traço para um Stroke.
		/// Um Stroke Style é um recurso independente do dispositivo; você pode criá-lo uma vez, em seguida, retê-lo para a vida de sua aplicação.
		/// Para criar um Stroke Style, use o método ICarenD2D1Factory::CreateStrokeStyle.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("CF281B3C-688A-41FF-AF72-DC63150D1838")]
		public interface class ICarenD2D1StrokeStyle : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém um valor que especifica como as extremidades de cada traço são desenhadas.
			/// </summary>
			/// <param name="Param_Out_EndDashStyle">Retorna um valor que especifica como as extremidades de cada traço são desenhadas.</param>
			void GetDashCap([Out] CA_D2D1_CAP_STYLE% Param_Out_EndDashStyle);

			/// <summary>
			/// Copia o padrão do painel para a matriz especificada. 
			/// Os traços(Dashes) são especificados em unidades que são um múltiplo da largura do traçado, com membros subsequentes da matriz indicando os traços e lacunas entre traços: a primeira entrada indica 
			/// um traço preenchido, o segundo uma lacuna, e assim por diante.
			/// </summary>
			/// <param name="Param_Out_ArrayDashes">Retorna uma matriz que receberá o padrão de traço. A matriz deve ser capaz de conter pelo menos tantos elementos quanto especificado pelo Param_Quantidade.</param>
			/// <param name="Param_Quantidade">O número de traços para copiar. Se esse valor for menor do que o número de traços na matriz de traços de Stroke Style, os traços retornados são truncados para Param_Quantidade. 
			/// Se esse valor for maior do que o número de traços na matriz de Stroke Styles, os traços extras são definidos como 0.0f. Para obter o número real de traços na matriz de traços do estilo de traçado, 
			/// use o método GetDashesCount.</param>
			void GetDashes(
				[Out] cli::array<float>^% Param_Out_ArrayDashes,
				UInt32 Param_Quantidade);

			/// <summary>
			/// Recupera o número de entradas na matriz de traços. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de entradas na matriz de traços se o traçado for tracejado; caso contrário, 0.</param>
			void GetDashesCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera um valor que especifica até que ponto na sequência do painel o traçado começará. 
			/// </summary>
			/// <param name="Param_Out_Offset">Recupera um valor que especifica até que ponto na sequência do traço o traçado começará.</param>
			void GetDashOffset([Out] float% Param_Out_Offset);

			/// <summary>
			/// Obtém um valor que descreve o padrão de traço do traçado. 
			/// </summary>
			/// <param name="Param_Out_DashStyleUsado">Recupera um valor que descreve o padrão de traço predefinido usado ou D2D1_DASH_STYLE_CUSTOM de (CA_D2D1_DASH_STYLE) se um estilo de painel personalizado for usado.</param>
			void GetDashStyle([Out] CA_D2D1_DASH_STYLE% Param_Out_DashStyleUsado);

			/// <summary>
			/// Recupera o tipo de forma usada no final de um curso. 
			/// </summary>
			/// <param name="Param_Out_TipoEndShape">Retorna o tipo de forma usada no final de um curso.</param>
			void GetEndCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoEndShape);

			/// <summary>
			/// Recupera o tipo de articulação usada nos vértices do contorno de uma forma. 
			/// </summary>
			/// <param name="Param_Out_TipoJoint">Recupera um valor que especifica o tipo de articulação usada nos vértices do contorno de uma forma.</param>
			void GetLineJoin([Out] CA_D2D1_LINE_JOIN% Param_Out_TipoJoint);

			/// <summary>
			/// Recupera o limite na razão do comprimento do miter para metade da espessura do traçado. 
			/// </summary>
			/// <param name="Param_Out_Limite">Recupera um número positivo maior ou igual a 1.0f que descreve o limite na razão do comprimento do miter para metade da espessura do traçado.</param>
			void GetMiterLimit([Out] float% Param_Out_Limite);

			/// <summary>
			/// Recupera o tipo de forma usada no início de um Stroke. 
			/// </summary>
			/// <param name="Param_Out_TipoStartShape">Retorna o tipo de forma usada no início de um Stroke.</param>
			void GetStartCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoStartShape);
		};

		/// <summary>
		/// (ID2D1StrokeStyle1) - Interface responsável por descrever os Caps, limite de Miter, Line Join e informações de traço para um Stroke.
		/// Esta interface adiciona funcionalidade a ICarenD2D1StrokeStyle.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("92A2414C-C248-4803-A27C-4998A0117D53")]
		public interface class ICarenD2D1StrokeStyle1 : ICarenD2D1StrokeStyle
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recebe o tipo de transformação do Stroke.
			/// </summary>
			/// <param name="Param_Out_StrokeTransformType">Retorna o tipo de transformação de traçado.</param>
			void GetStrokeTransformType(
				[Out] CA_D2D1_STROKE_TRANSFORM_TYPE% Param_Out_StrokeTransformType);
		};

		/// <summary>
		/// (ID2D1InkStyle) - Interface responsável por representar uma coleção de propriedades de estilo a serem usadas por métodos como ICarenD2D1DeviceContext2::DrawInk ao renderizar tinta.
		///  O estilo de tinta define a forma de ponta de caneta e a transformação.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("0FB341B3-CAE5-4158-98AE-109F02AB0AB1")]
		public interface class ICarenD2D1InkStyle : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera a forma de ponta de nib pré-transformada para este estilo. 
			/// </summary>
			/// <param name="Param_Out_NibShape">Retorna a forma do nib pré-transformada para este estilo.</param>
			void GetNibShape([Out] CA_D2D1_INK_NIB_SHAPE% Param_Out_NibShape);

			/// <summary>
			/// Recupera a transformação a ser aplicada à forma de ponta deste estilo. 
			/// </summary>
			/// <param name="Param_Out_Transform">Retorna a transformação a ser aplicada a Style`s Nib Shape.</param>
			void GetNibTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform);

			/// <summary>
			/// Define a forma de ponta da Nib pré-transformada para este estilo. 
			/// </summary>
			/// <param name="Param_NibShape">A forma de ponta de nib pré-transformada para usar neste estilo.</param>
			void SetNibShape(CA_D2D1_INK_NIB_SHAPE Param_NibShape);

			/// <summary>
			/// Define a transformação para aplicar à forma de ponta deste estilo. 
			/// </summary>
			/// <param name="Param_Transform">A transformação para aplicar à forma de ponta deste estilo. Observe que os componentes de tradução da matriz de transformação são ignorados para fins de renderização.</param>
			void SetNibTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);
		};

		/// <summary>
		/// (ID2D1TessellationSink) - Interface responsável por povoar um objeto ICarenD2D1Mesh com triângulos.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9A7351B4-3A21-412C-B3EA-0A427C270A77")]
		public interface class ICarenD2D1TessellationSink : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Copia os triângulos especificados para o Sink. 
			/// </summary>
			/// <param name="Param_ArrayTriangulos">Uma série de estruturas CA_D2D1_TRIANGLE que descrevem os triângulos para adicionar ao Sink.</param>
			/// <param name="Param_QuantidadeTriangulos">O número de triângulos para copiar a partir da matriz (Param_ArrayTriangulos).</param>
			void AddTriangles(
				cli::array<CA_D2D1_TRIANGLE^>^ Param_ArrayTriangulos,
				UInt32 Param_QuantidadeTriangulos);

			/// <summary>
			/// Fecha o Sink e retorna seu status de erro. 
			/// </summary>
			CarenResult Close();
		};

		/// <summary>
		/// (ID2D1SimplifiedGeometrySink) - Interface responsável por descrever um caminho geométrico que não contém curvas ou arcos quadráticos de Bézier.
		/// Um Geometry Sink consiste em uma ou mais figuras. Cada figura é composta por um ou mais segmentos de linha ou curva Bezier. Para criar uma figura, ligue para o método BeginFigure e especifique o ponto de 
		/// partida da figura e use AddLines e AddBeziers para adicionar segmentos de linha e Bezier. Quando terminar de adicionar segmentos, ligue para o método EndFigure.
		/// Você pode repetir esta sequência para criar figuras adicionais. Quando terminar de criar números, ligue para o método Close.
		/// Para criar caminhos de geometria que possam conter arcos e curvas de Bezier quadráticas, use um ICarenD2D1GeometrySink.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8A6A45E1-C7CD-4700-9970-8DC3234D5874")]
		public interface class ICarenD2D1SimplifiedGeometrySink : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria uma sequência de curvas Cubicas de Bezier e as adiciona ao Geometry Sink.
			/// </summary>
			/// <param name="Param_ArrayBeziers">Uma matriz de segmentos Bezier que descreve as curvas bezier para criar. Uma curva é extraída do ponto atual do Geometry Sink (o ponto final do último segmento 
			/// desenhado ou o local especificado pela BeginFigure) até o ponto final do primeiro segmento Bezier na matriz. se a matriz contiver segmentos bezier adicionais, cada segmento Bezier subsequente usa
			/// o ponto final do segmento Bezier anterior como seu ponto de partida.</param>
			/// <param name="Param_QuantidadeBeziers">O número de segmentos Bezier na matriz (Param_ArrayBeziers).</param>
			void AddBeziers(
				cli::array<CA_D2D1_BEZIER_SEGMENT^>^ Param_ArrayBeziers,
				UInt32 Param_QuantidadeBeziers);

			/// <summary>
			/// Cria uma sequência de linhas usando os pontos especificados e adiciona-os ao Geometry Sink. 
			/// </summary>
			/// <param name="Param_ArrayPoints">uma matriz de um ou mais pontos que descrevem as linhas a desenhar. Uma linha é desenhada do ponto atual do Geometry Sink (o ponto final do último segmento desenhado 
			/// ou o local especificado pela BeginFigure) até o primeiro ponto da matriz. se a matriz contiver pontos adicionais, uma linha é desenhada do primeiro ponto para o segundo ponto na matriz, do segundo ponto 
			/// ao terceiro ponto, e assim por diante.</param>
			/// <param name="Param_QuantidadePontos">O número de pontos na matriz (Param_ArrayPoints).</param>
			void AddLines(
				cli::array<CA_D2D1_POINT_2F^>^ Param_ArrayPoints,
				UInt32 Param_QuantidadePontos);

			/// <summary>
			/// Inicia uma nova figura no ponto especificado. 
			/// Se esse método for chamado enquanto uma figura estiver em andamento, a interface será invalidada e todos os métodos futuros falharão.
			/// </summary>
			/// <param name="Param_StartPoint">O ponto para começar a nova figura.</param>
			/// <param name="Param_InicioFigura">Se a nova figura deve ser oca ou preenchida.</param>
			void BeginFigure(
				CA_D2D1_POINT_2F^ Param_StartPoint,
				CA_D2D1_FIGURE_BEGIN Param_InicioFigura);

			/// <summary>
			/// Fecha o Geometry Sink, indica se está em estado de erro e redefine o estado de erro do Sink.
			/// Não feche o Geometry Sink enquanto uma figura ainda está em andamento; fazendo isso coloca o Geometry Sink em um estado de erro. Para que a operação seja bem sucedida, deve haver uma chamada EndFigure 
			/// para cada chamada para BeginFigure.
			/// </summary>
			CarenResult Close();

			/// <summary>
			/// Termina a figura atual; opcionalmente, fecha-o.
			/// Chamar este método sem uma chamada correspondente ao BeginFigure coloca o Geometry Sink em um estado de erro; chamadas subsequentes são ignoradas, e a falha geral será devolvida quando o método 
			/// Close for chamado.
			/// </summary>
			/// <param name="Param_FinalFigura">Um valor que indica se o valor atual está fechado. Se o valor for fechado, uma linha será traçada entre o ponto atual e o ponto de partida especificado 
			/// pela BeginFigure.</param>
			void EndFigure(CA_D2D1_FIGURE_END Param_FinalFigura);

			/// <summary>
			/// Especifica o método usado para determinar quais pontos estão dentro da geometria descrita por esta Geometry Sink e quais pontos estão fora. 
			/// O modo de preenchimento é padrão para D2D1_FILL_MODE_ALTERNATE. Para definir o modo de preenchimento, ligue para SetFillMode antes da primeira chamada para BeginFigure. Não fazer vai colocar o 
			/// Geometry Sink em um estado de erro.
			/// </summary>
			/// <param name="Param_ModoPreencher">O método utilizado para determinar se um determinado ponto faz parte da geometria.</param>
			void SetFillMode(CA_D2D1_FILL_MODE Param_ModoPreencher);

			/// <summary>
			/// Especifica as opções de traçado e de adesão a serem aplicadas a novos segmentos adicionados ao Geometry Sink. 
			/// Após a chamada esse método, as bandeiras do segmento especificadas são aplicadas a cada segmento posteriormente adicionadas ao Sink. As bandeiras do segmento são aplicadas a cada segmento adicional até que 
			/// este método seja chamado novamente e um conjunto diferente de bandeiras do segmento seja especificado.
			/// </summary>
			/// <param name="Param_FlagsVertex">As opções do Stroke e o Join a serem aplicadas a novos segmentos adicionados ao Geometry Sink.</param>
			void SetSegmentFlags(CA_D2D1_PATH_SEGMENT Param_FlagsVertex);
		};

		/// <summary>
		/// (ID2D1GeometrySink) - Interface responsável por descrever um caminho geométrico que pode conter linhas, arcos, curvas búbicas de Bezier e curvas de Bezier quadráticas.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("E38F53EE-AF8A-49E7-A8A5-6550C9C9E99B")]
		public interface class ICarenD2D1GeometrySink : ICarenD2D1SimplifiedGeometrySink
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Adiciona um único arco à geometria do caminho. 
			/// </summary>
			/// <param name="Param_Arc">O segmento de arco para adicionar à figura.</param>
			void AddArc(CA_D2D1_ARC_SEGMENT^ Param_Arc);

			/// <summary>
			/// Cria uma curva bezier cúbica entre o ponto atual e o ponto final especificado.
			/// </summary>
			/// <param name="Param_Bezier">Uma estrutura que descreve os pontos de controle e o ponto final da curva Bezier para adicionar.</param>
			void AddBezier(CA_D2D1_BEZIER_SEGMENT^ Param_Bezier);

			/// <summary>
			/// Cria um segmento de linha entre o ponto atual e o ponto final especificado e adiciona-o à pia de geometria. 
			/// </summary>
			/// <param name="Param_Point">O ponto final da linha para desenhar.</param>
			void AddLine(CA_D2D1_POINT_2F^ Param_Point);

			/// <summary>
			/// Cria uma curva bezier quadrática entre o ponto atual e o ponto final especificado. 
			/// </summary>
			/// <param name="Param_Bezier">Uma estrutura que descreve o ponto de controle e o ponto final da curva quadrática de Bezier para adicionar.</param>
			void AddQuadraticBezier(CA_D2D1_QUADRATIC_BEZIER_SEGMENT^ Param_Bezier);

			/// <summary>
			/// Adiciona uma sequência de segmentos de Bezier quadráticos como uma matriz em uma única chamada. 
			/// </summary>
			/// <param name="Param_ArrayBeziers">Uma matriz de uma sequência de segmentos quadráticos de Bezier.</param>
			/// <param name="Param_QuantidadeBeziers">Um valor indicando o número de segmentos de Bezier quadráticos em beziers.</param>
			void AddQuadraticBeziers(
				cli::array<CA_D2D1_QUADRATIC_BEZIER_SEGMENT^>^ Param_ArrayBeziers,
				UInt32 Param_QuantidadeBeziers);
		};

		/// <summary>
		/// (ID2D1Mesh) - Interface responsável por representar um conjunto de vértices que formam uma lista de triângulos.
		/// Uma malha(Mesh) é um recurso dependente do dispositivo: seu aplicativo deve criar malhas depois de inicializar o alvo de renderização com o qual as malhas serão usadas e recriar as malhas sempre que 
		/// o alvo de renderização precisar ser recriado.
		/// Para criar uma malha, ligue para o método ICarenD2D1RenderTarget::CreateMesh no alvo de renderização com o qual a malha será usada. Uma malha só pode ser usada com o alvo renderizador que a criou e os 
		/// alvos compatíveis do alvo de renderização.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F92C71A9-A7E5-4B3A-AA70-830EEE10A021")]
		public interface class ICarenD2D1Mesh : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Abre a malha(Mesh) para a população. 
			/// </summary>
			/// <param name="Param_Out_TessellationSink">Retorna um ponteiro para um ICarenD2D1TessellationSink que é usado para preencher a malha.</param>
			CarenResult Open([Out] ICarenD2D1TessellationSink^% Param_Out_TessellationSink);
		};

		/// <summary>
		/// (ID2D1GradientMesh) - Interface responsável por representar uma representação dependente do dispositivo de uma malha(Mesh) gradiente composta de patches. Use o método ICarenD2D1DeviceContext2::CreateGradientMesh 
		/// para criar uma instância desta interface.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("11F0D922-D20E-4823-90DC-F5596A33D2B1")]
		public interface class ICarenD2D1GradientMesh : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Retorna o número de patches que compõem esta malha(Mesh) gradiente. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de patches que compõem esta malha gradiente.</param>
			void GetPatchCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Retorna um subconjunto das manchas(Subset) que compõem esta malha(Mesh) gradiente. 
			/// </summary>
			/// <param name="Param_StartIndex">Índice do primeiro patch a retornar.</param>
			/// <param name="Param_Out_ArrayPatches">Retorna uma matriz preenchida com os dados do patch.</param>
			/// <param name="Param_QuantidadePatches">O número de patches a serem devolvidos.</param>
			CarenResult GetPatches(
				UInt32 Param_StartIndex,
				[Out] cli::array<CA_D2D1_GRADIENT_MESH_PATCH^>^% Param_Out_ArrayPatches,
				UInt32 Param_QuantidadePatches);
		};

		/// <summary>
		/// (ID2D1Layer) - Interface responsável por representar um armazenamento de apoio necessária para renderizar uma camada(Layer).
		/// Uma camada é um recurso dependente do dispositivo: seu aplicativo deve criar camadas depois de inicializar o alvo de renderização com o qual as camadas serão usadas e recriar as camadas sempre que o 
		/// destino de renderização precisar ser recriado.
		/// Para desenhar para uma camada, empurre a camada para a pilha de destino renderizadora, chamando o método ICarenD2D1RenderTarget::PushLayer. Depois de terminar de desenhar para a camada, ligue para
		/// o método ICarenD2D1RenderTarget::PopLayer.
		/// Para criar uma camada, chame o método ICarenD2D1RenderTarget::CreateLayer do alvo de renderização onde a camada será usada.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("B7610C46-71F2-4406-AA3A-2356E98E797E")]
		public interface class ICarenD2D1Layer : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o tamanho da camada em pixels independentes do dispositivo.
			/// </summary>
			/// <param name="Param_Out_SizeLayer">Retorna o tamanho da camada em pixels independentes do dispositivo.</param>
			void GetSize([Out] CA_D2D1_SIZE_F^% Param_Out_SizeLayer);
		};

		/// <summary>
		/// (ID2D1Geometry) - Interface responsável por representar um recurso de geometria e define um conjunto de métodos auxiliares para manipular e medir formas geométricas. Interfaces que 
		/// herdam da ICarenD2D1Geometry definem formas específicas.
		/// Geometrias Direct2D permitem descrever figuras bidimensionais e também oferecem muitos usos, como definir regiões de teste de sucesso, regiões de clipe e até caminhos de animação.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pela ICarenD2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, 
		/// ou até que elas precisem ser modificadas.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("D5F5C620-D19D-4DAC-B51D-2FAD5A6640A8")]
		public interface class ICarenD2D1Geometry : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
			/// </summary>
			/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
			/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
			/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
			/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
			CarenResult CombineWithGeometry(
				ICarenD2D1Geometry^ Param_GeometriaEntrada,
				CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
				CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink);

			/// <summary>
			/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
			/// </summary>
			/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
			/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
			/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
			/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
			CarenResult CombineWithGeometry(
				ICarenD2D1Geometry^ Param_GeometriaEntrada,
				CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
				CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink
			);

			/// <summary>
			/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada utilizando-se a tolerância de achatamento especificada. 
			/// Ao interpretar o valor da relação retornada, é importante lembrar que o membro D2D1_GEOMETRY_RELATION_IS_CONTAINED do tipo de enumeração D2D1_GEOMETRY_RELATION significa que essa geometria está 
			/// contida dentro da (Param_GeometriaEntrada), não que esta geometria contenha (Param_GeometriaEntrada).
			/// </summary>
			/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
			/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
			/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
			CarenResult CompareWithGeometry(
				ICarenD2D1Geometry^ Param_GeometriaEntrada,
				CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
				float Param_FlatteningTolerance,
				[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao);

			/// <summary>
			/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada usando a tolerância de achatamento padrão. 
			/// </summary>
			/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
			/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
			/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
			CarenResult CompareWithGeometry(
				ICarenD2D1Geometry^ Param_GeometriaEntrada,
				CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
				[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao);

			/// <summary>
			/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância especificada. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais
			/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
			CarenResult ComputeArea(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				[Out] float% Param_Out_Area);

			/// <summary>
			/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância padrão. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
			/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
			CarenResult ComputeArea(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] float% Param_Out_Area);

			/// <summary>
			/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
			/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
			CarenResult ComputeLength(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				[Out] float% Param_Out_Length);

			/// <summary>
			/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
			/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
			CarenResult ComputeLength(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] float% Param_Out_Length);

			/// <summary>
			/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada.
			/// </summary>
			/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
			/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
			/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
			/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
			CarenResult ComputePointAtLength(
				float Param_Length,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
				CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector);

			/// <summary>
			/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
			/// </summary>
			/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
			/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
			/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
			/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
			CarenResult ComputePointAtLength(
				float Param_Length,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
				CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector);

			/// <summary>
			/// Indica se a área preenchida pela geometria conteria o ponto especificado dada a tolerância de achatamento especificada. 
			/// </summary>
			/// <param name="Param_Point">O ponto para testar.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
			/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam o preenchimento por menos do 
			/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
			CarenResult FillContainsPoint(
				CA_D2D1_POINT_2F^ Param_Point,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				[Out] Boolean% Param_Out_Contem);

			/// <summary>
			/// Indica se a área preenchida pela geometria conteria o ponto especificado. 
			/// </summary>
			/// <param name="Param_Point">O ponto para testar.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
			/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
			CarenResult FillContainsPoint(
				CA_D2D1_POINT_2F^ Param_Point,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] Boolean% Param_Out_Contem);

			/// <summary>
			/// Recupera os limites da geometria. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria antes de calcular seus limites.</param>
			/// <param name="Param_Out_Bounds">Retorna os limites desta geometria. Se os limites estiverem vazios, este parâmetro será um recamto onde os Bounds.Left > Bounds.Right.</param>
			CarenResult GetBounds(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

			/// <summary>
			/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
			/// </summary>
			/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
			/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
			/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
			/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
			CarenResult GetWidenedBounds(
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

			/// <summary>
			/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
			/// </summary>
			/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
			/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
			/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
			/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
			CarenResult GetWidenedBounds(
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

			/// <summary>
			/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink. 
			/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
			/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
			/// para criar sindicatos entre várias geometrias simultaneamente.
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
			/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
			CarenResult Outline(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink.
			/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
			/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
			/// para criar sindicatos entre várias geometrias simultaneamente.
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
			/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
			CarenResult Outline(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) Curvas Cubicas Bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
			/// </summary>
			/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
			/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
			CarenResult Simplify(
				CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) curvas búbicas bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
			/// </summary>
			/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
			/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
			CarenResult Simplify(
				CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado.
			/// </summary>
			/// <param name="Param_Point">O ponto para testar a contenção.</param>
			/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
			/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
			/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam ao derrame por menos do
			/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
			CarenResult StrokeContainsPoint(
				CA_D2D1_POINT_2F^ Param_Point,
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				[Out] Boolean% Param_Out_Contem);

			/// <summary>
			/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado. 
			/// </summary>
			/// <param name="Param_Point">O ponto para testar a contenção.</param>
			/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
			/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
			/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
			CarenResult StrokeContainsPoint(
				CA_D2D1_POINT_2F^ Param_Point,
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] Boolean% Param_Out_Contem);

			/// <summary>
			/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância especificada.
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
			/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
			CarenResult Tessellate(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1TessellationSink^ Param_TelassellationSink);

			/// <summary>
			/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância padrão. 
			/// </summary>
			/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
			/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
			CarenResult Tessellate(
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1TessellationSink^ Param_TelassellationSink);

			/// <summary>
			/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada. 
			/// </summary>
			/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
			/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
			/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
			/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
			CarenResult Widen(
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
			/// </summary>
			/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
			/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
			/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
			CarenResult Widen(
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);
		};

		/// <summary>
		/// (ID2D1EllipseGeometry) - Interface responsável por representar uma elipse.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pelo ICarenD2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, 
		/// ou até que elas precisem ser modificadas.
		/// Para criar uma geometria elipse, use o método ICarenD2D1Factory::CreateEllipseGeometry.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("79DCE84E-B17E-4AE2-8AF3-C71965AF6277")]
		public interface class ICarenD2D1EllipseGeometry : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a estrutura D2D1_ELLIPSE que descreve essa geometria de elipse. 
			/// </summary>
			/// <param name="Param_Out_Ellipse">Retrona uma estrutura (D2D1_ELLIPSE) que descreve o tamanho e a posição da elipse.</param>
			void GetEllipse([Out] CA_D2D1_ELLIPSE^% Param_Out_Ellipse);
		};

		/// <summary>
		/// (ID2D1RectangleGeometry) - Interface responsável por desvrever um retângulo bidimensional.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pelo ID2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, 
		/// ou até que elas precisem ser modificadas. Para criar uma geometria retângulo, use o método ICarenD2D1Factory::CreateRectangleGeometry.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("69052750-DB3D-4B8A-A1DA-D39432FB5CA0")]
		public interface class ICarenD2D1RectangleGeometry : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o retângulo que descreve as dimensões da geometria do retângulo. 
			/// </summary>
			/// <param name="Param_Out_Rect">Retorna uma estrutura (CA_D2D1_RECT_F) que descreve as dimensões da geometria do retângulo quando este método retorna.</param>
			void GetRect([Out] CA_D2D1_RECT_F^% Param_Out_Rect);
		};

		/// <summary>
		/// (ID2D1RoundedRectangleGeometry) - Interface responsável por descrever um retângulo arredondado.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pelo ID2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, ou até que elas precisem ser modificadas.
		/// Para criar uma geometria retângulo, use o método ICarenD2D1Factory::CreateRoundedRectangleGeometry.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F1845F8B-F336-4247-8D1B-E0F6CA792AD0")]
		public interface class ICarenD2D1RoundedRectangleGeometry : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera um retângulo arredondado que descreve este Rounded Rectangle Geometry.
			/// </summary>
			/// <param name="Param_Out_RoundedRect">Retorna a estrutura (CA_D2D1_ROUNDED_RECT) que descreve esta geometria retângulo arredondado.</param>
			void GetRoundedRect([Out] CA_D2D1_ROUNDED_RECT^% Param_Out_RoundedRect);
		};

		/// <summary>
		/// (ID2D1TransformedGeometry) - Interface responsável por representar uma geometria que foi transformada.
		/// Usar uma ICarenD2D1TransformedGeometry em vez de transformar uma geometria usando a transformação de um alvo de renderização permite que você transforme uma geometria sem transformar seu traçado.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pelo ID2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, ou até que elas precisem ser modificadas.
		/// Para criar um método ICarenD2D1TransformedGeometry, ligue para o método ICarenD2D1Factory::CreateTransformedGeometry.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("C1902B50-3308-4FB3-907B-7C598037A53E")]
		public interface class ICarenD2D1TransformedGeometry : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera a geometria de origem deste objeto de geometria transformado. 
			/// </summary>
			/// <param name="Param_Out_SourceGeometry">Retorna um ponteiro para a interface da geometria de origem para este objeto transformado.</param>
			CarenResult GetSourceGeometry([Out] ICarenD2D1Geometry^% Param_Out_SourceGeometry);

			/// <summary>
			/// Recupera a matriz usada para transformar a geometria de origem do objeto ICarenD2D1TransformedGeometry. 
			/// </summary>
			/// <param name="Param_Out_Transform">Retorna uma estrutura (CA_D2D1_MATRIX_3X2_F) que recebe a matriz usada para transformar a geometria de origem do objeto ICarenD2D1TransformedGeometry.</param>
			void GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform);
		};

		/// <summary>
		/// (ID2D1GeometryRealization) - Interface responsável por encapsular uma representação dependente de dispositivos e transformação de uma geometria preenchida ou acariciada. Os chamadores devem considerar a 
		/// criação de uma realização de geometria quando desejam acelerar a repetida renderização de uma determinada geometria. Esta interface não expõe métodos.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("DD84D871-F549-41B0-882E-402325C120F3")]
		public interface class ICarenD2D1GeometryRealization : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Essa interface não possui métodos.
		};

		/// <summary>
		/// (ID2D1GeometryGroup) - Interface responsável por representa uma geometria composta, composta por outros objetos ICarenD2D1Geometry.
		/// Grupos de geometria são uma maneira conveniente de agrupar várias geometrias simultaneamente para que todas as figuras de várias geometrias distintas sejam concatenadas em uma.
		/// Geometrias Direct2D são recursos imutáveis e independentes de dispositivos criados pelo ID2D1Factory. Em geral, você deve criar geometrias uma vez e retê-las para a vida útil da aplicação, ou até que 
		/// elas precisem ser modificadas.
		/// Para criar um objeto ICarenD2D1GeometryGroup, chame o método ICarenD2D1Factory::CreateGeometryGroup.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("95FEF116-40A5-45EE-89F8-5FB658956D15")]
		public interface class ICarenD2D1GeometryGroup : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Indica como as áreas de intersecção das geometrias contidas neste grupo de geometria são combinadas.
			/// </summary>
			/// <param name="Param_Out_FillMode">Retorna um valor que indica como as áreas interseccionais das geometrias contidas neste grupo de geometria são combinadas.</param>
			void GetFillMode([Out] CA_D2D1_FILL_MODE% Param_Out_FillMode);

			/// <summary>
			/// Recupera as geometrias no grupo de geometria.
			/// </summary>
			/// <param name="Param_Ref_Geometrias">Retorna um ponteiro para uma matriz de interfaces de geometrias a serem preenchidas por este método. O comprimento da matriz é especificado pelo parâmetro (Param_Quantidade). 
			/// Se a matriz for NULO, então este método não executa nenhuma operação. O Usuário deve inicializar as interfaces na matriz antes de chamar o método.</param>
			/// <param name="Param_Quantidade">Um valor indicando o número de geometrias a retornar na matriz (Param_Ref_Geometrias). Se esse valor for menor do que o número de geometrias no grupo de geometria, as demais
			/// geometrias são omitidas. Se esse valor for maior do que o número de geometrias no grupo de geometria, as geometrias extras ão definidas como NULO. Para obter o número de geometrias atualmente no grupo de geometria, 
			/// use o método GetSourceGeometryCount.</param>
			void GetSourceGeometries(
				cli::array<ICarenD2D1Geometry^>^ Param_Ref_Geometrias,
				UInt32 Param_Quantidade);

			/// <summary>
			/// Indica o número de objetos de geometria no grupo de geometria.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de geometrias no ICarenD2D1GeometryGroup</param>
			void GetSourceGeometryCount([Out] UInt32% Param_Out_Quantidade);
		};

		/// <summary>
		/// (ID2D1DrawingStateBlock) - Interface responsável por representar o estado de desenho de um alvo de renderização: o modo antialiasing, a transformação, as tags e as opções de renderização de texto.
		/// Um bloco de estado de desenho é um recurso independente do dispositivo; você pode criá-lo uma vez e retê-lo para a vida útil de sua aplicação.
		/// Para criar um ICarenD2D1DrawingStateBlock, use o método ICarenD2D1Factory::CreateDrawingStateBlock.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("7CA75583-FA93-47C1-BF3A-ADAB3BB7575A")]
		public interface class ICarenD2D1DrawingStateBlock : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o modo antialiasing, transforma e marca parte do estado de desenho. 
			/// </summary>
			/// <param name="Param_Out_DescEstado">Retorna uma estrutura que contém o modo antialiasing, transforma e marca parte do estado de desenho.</param>
			void GetDescription([Out] CA_D2D1_DRAWING_STATE_DESCRIPTION^% Param_Out_DescEstado);

			/// <summary>
			/// Recupera a configuração de renderização de texto do estado de desenho.
			/// </summary>
			/// <param name="Param_Out_TextRenderingParams">Retorna um ponteiro para a interface (IDWriteRenderingParams) que descreve a configuração de renderização de texto do estado de desenho. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams);

			/// <summary>
			/// Especifica o modo antialiasing, transforma e marca parte do estado de desenho.
			/// </summary>
			/// <param name="Param_DescEstado">Uma estrutura que descreve o modo antialiasing, transformar e tags do estado de desenho.</param>
			void SetDescription(CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescEstado);

			/// <summary>
			/// Especifica a configuração de renderização de texto do estado de desenho.
			/// </summary>
			/// <param name="Param_TextRenderingParams">Uma interface (IDWriteRenderingParams) para a configuração de renderização de texto do estado de desenho ou NULO para usar as configurações padrão.</param>
			CarenResult SetTextRenderingParams(ICaren^ Param_TextRenderingParams);
		};

		/// <summary>
		/// (ID2D1DrawingStateBlock1) - Interface responsável por implementação de um bloco de estado de desenho que adiciona a funcionalidade da mistura primitiva, além do modo antialias já existente, transformar, 
		/// tags e modo de renderização de texto.
		/// Você pode obter um ICarenD2D1DrawingStateBlock1 usando o método ICarenD2D1Factory::CreateDrawingStateBlock ou você pode usar o método ICaren::ConsultarInterface.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("7A2185D1-DE84-4B2A-A344-BB4120484FE5")]
		public interface class ICarenD2D1DrawingStateBlock1 : ICarenD2D1DrawingStateBlock
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o modo antialiasing, transformar, tags, mistura primitiva e parte do modo unitário do estado de desenho. 
			/// </summary>
			/// <param name="Param_Out_DescEstado">Retorna uma estrutura que contém o modo antialiasing, transformar, tags, mistura primitiva e parte do modo unitário do estado de desenho.</param>
			void GetDescription([Out] CA_D2D1_DRAWING_STATE_DESCRIPTION1^% Param_Out_DescEstado);

			/// <summary>
			/// Define a CA_D2D1_DRAWING_STATE_DESCRIPTION1 associada a este bloco de estado de desenho. 
			/// </summary>
			/// <param name="Param_DescEstado">Uma estrutura D2D1_DRAWING_STATE_DESCRIPTION1 a ser definida associada a este bloco de estado de desenho.</param>
			void SetDescription(CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescEstado);
		};

		/// <summary>
		/// (ID2D1RenderInfo) - Interface responsável por descrever as informações de renderização comuns a todas as várias implementações de transformação.
		/// Esta interface é usada por uma implementação de transformação para primeiro descrever e, em seguida, indicar alterações no passe de renderização que corresponde à transformação.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("72B9097A-9161-4147-A5CA-2BA8B2CFD749")]
		public interface class ICarenD2D1RenderInfo : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Especifica que a saída da transformação na qual as informações de renderização estão encapsuladas é ou não armazenada em cache. 
			/// </summary>
			/// <param name="Param_IsCached">TRUE se a saída da transformação for armazenada em cache; caso contrário, FALSO.</param>
			void SetCached(Boolean Param_IsCached);

			/// <summary>
			/// Define como uma entrada específica para a transformação deve ser tratada pelo renderizador em termos de amostragem. 
			/// </summary>
			/// <param name="Param_InputIndex">O índice da entrada que terá a descrição de entrada aplicada.</param>
			/// <param name="Param_InputDescription">A descrição da entrada a ser aplicada à transformação.</param>
			CarenResult SetInputDescription(
				UInt32 Param_InputIndex,
				CA_D2D1_INPUT_DESCRIPTION^ Param_InputDescription);

			/// <summary>
			/// Fornece uma sugestão estimada de custo de execução do sombreador para D2D. 
			/// A contagem de instruções pode ser definida de acordo com o número de instruções no sombreador. Essas informações são usadas como uma dica ao renderizar imagens extremamente grandes. Chamar esta API é opcional, 
			/// mas pode melhorar o desempenho se você fornecer um número preciso.
			/// [NOTA] As instruções que ocorrem em um loop devem ser contadas de acordo com o número de iterações em loop.
			/// </summary>
			/// <param name="Param_InstructionCount">Uma contagem aproximada de instruções do sombreador associado.</param>
			void SetInstructionCountHint(UInt32 Param_InstructionCount);

			/// <summary>
			/// Permite que um chamador controle a precisão de saída e a profundidade do canal da transformação em que as informações de renderização são encapsuladas. 
			/// Se a precisão de saída da transformação não for especificada, ela será padrão para a precisão especificada no contexto do dispositivo Direct2D. O máximo de 16bpc UNORM e 16bpc FLOAT é 32bpc FLOAT.
			/// A profundidade do canal de saída corresponderá ao máximo das profundidades do canal de entrada se a profundidade do canal estiver D2D1_CHANNEL_DEPTH_DEFAULT.
			/// Não há profundidade de canal de saída global, isso é sempre deixado para o controle das transformações.
			/// </summary>
			/// <param name="Param_BufferPrecision">O tipo de buffer que deve ser usado como saída a partir desta transformação.</param>
			/// <param name="Param_ChannelDepth">O número de canais que serão usados no buffer de saída.</param>
			CarenResult SetOutputBuffer(
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth);
		};

		/// <summary>
		/// (ID2D1RenderTarget) - Interface responsável por representar um objeto que pode receber comandos de desenho. Interfaces que herdam do ICarenD2D1RenderTarget tornam os comandos de desenho que recebem de diferentes maneiras.
		/// Seu aplicativo deve criar metas de renderização uma vez e segurá-los durante a vida útil do aplicativo ou até que o método EndDraw do alvo de renderização retorne o erro D2DERR_RECREATE_TARGET. 
		/// Quando você recebe esse erro, você precisa recriar o destino render (e quaisquer recursos que ele criou).
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9CC5EA15-EF72-4C45-99A2-0D2C3ABE000A")]
		public interface class ICarenD2D1RenderTarget : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Inicia o desenho deste alvo de renderização. 
			/// </summary>
			void BeginDraw();

			/// <summary>
			/// Limpa a área de desenho para a cor especificada. 
			/// </summary>
			/// <param name="Param_ClearColor"></param>
			void Clear(CA_D2D1_COLOR_F^ Param_ClearColor);

			/// <summary>
			/// Cria um bitmap do Direct2D de um ponteiro para dados de origem na memória. 
			/// </summary>
			/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
			/// <param name="Param_DadosOrigem">Um ponteiro para a localização da memória dos dados da imagem ou NULO para criar um bitmap não inicializado.</param>
			/// <param name="Param_Pitch">A contagem de bytes de cada linha de varredura, que é igual a (a largura da imagem em pixels × o número de bytes por pixel) + preenchimento de memória. Se (Param_DadosOrigem) é NULO, este valor é ignorado. (Note que o tom também é às vezes chamado de pitch.)</param>
			/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
			/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmap(
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
			CarenResult CreateBitmap(
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
			CarenResult CreateBitmapBrush(
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
				CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
				[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush);

			/// <summary>
			/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para seu modo de extensão, modo de interpolação, opacidade e transformação.
			/// </summary>
			/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
			/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
			CarenResult CreateBitmapBrush(
				ICarenD2D1Bitmap^ Param_Bitmap,
				[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush);

			/// <summary>
			/// Cria um ID2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para sua opacidade e transformação. 
			/// O Brush bitmap criado por este método tem uma opacidade de 1.0f e a matriz de identidade como sua transformação.
			/// </summary>
			/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
			/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel.</param>
			/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
			CarenResult CreateBitmapBrush(
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
			CarenResult CreateBitmapFromWicBitmap(
				ICaren^ Param_WicBitmapSource,
				CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
				[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ID2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
			/// </summary>
			/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
			/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromWicBitmap(
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
			CarenResult CreateCompatibleRenderTarget(
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
			CarenResult CreateCompatibleRenderTarget(ICaren^ Param_Out_BitmapRenderTarget);

			/// <summary>
			/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
			/// O alvo de renderização bitmap criado por este método não é compatível com o GDI.
			/// </summary>
			/// <param name="Param_DesiredSize">O tamanho desejado do novo destino de renderização em pixels independentes do dispositivo. O tamanho do pixel é calculado a partir do tamanho desejado usando o DPI pai de destino. 
			/// Se o tamanho desejado for mapeado para um tamanho de pixel inteiro, o DPI do destino de renderização compatível será o mesmo que o DPI pai do destino. Se o Tamanho desejado é mapeado para um tamanho de pixel 
			/// fracionário, o tamanho do pixel é arredondado para o número inteiro mais próximo e o DPI para o destino de renderização compatível é um pouco maior que o DPI do destino de renderização pai. Em todos os casos, 
			/// a coordenada (Param_DesiredSize.width, Param_DesiredSize.height) é mapeada para o canto inferior direito do destino de renderização compatível.</param>
			/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult CreateCompatibleRenderTarget(
				CA_D2D1_SIZE_F^ Param_DesiredSize,
				ICaren^ Param_Out_BitmapRenderTarget);

			/// <summary>
			/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
			/// </summary>
			/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
			/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
			/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult CreateCompatibleRenderTarget(
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
			CarenResult CreateCompatibleRenderTarget(
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
			CarenResult CreateGradientStopCollection(
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
			CarenResult CreateGradientStopCollection(
				cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
				UInt32 Param_QuantidadeGradientes,
				[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

			/// <summary>
			/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis.
			/// </summary>
			/// <param name="Param_Size">Se (0, 0) for especificado, nenhuma loja de backup será criada por trás do recurso de camada. O recurso de camada é alocado para o tamanho mínimo quando o PushLayer é chamado.</param>
			/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
			CarenResult CreateLayer(
				CA_D2D1_SIZE_F^ Param_Size,
				[Out] ICarenD2D1Layer^% Param_Out_Layer);

			/// <summary>
			/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis. 
			/// </summary>
			/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
			CarenResult CreateLayer([Out] ICarenD2D1Layer^% Param_Out_Layer);

			/// <summary>
			/// Cria um ICarenD2D1LinearGradientBrush que contém as GradientStops especificadas e tem a opacidade de transformação e base especificada. 
			/// </summary>
			/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
			/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel.</param>
			/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
			/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
			CarenResult CreateLinearGradientBrush(
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
			CarenResult CreateLinearGradientBrush(
				CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
				ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
				[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush);

			/// <summary>
			/// Crie uma malha(Mesh) que usa triângulos para descrever uma forma. 
			/// </summary>
			/// <param name="Param_Out_Mesh">Retorna uma interface ICarenD2D1Mesh que contém um ponteiro para a nova malha(Mesh).</param>
			CarenResult CreateMesh([Out] ICarenD2D1Mesh^% Param_Out_Mesh);

			/// <summary>
			/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados e tem a opacidade de transformação e base especificada.
			/// </summary>
			/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
			/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel(Brush).</param>
			/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
			/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
			CarenResult CreateRadialGradientBrush(
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
			CarenResult CreateRadialGradientBrush(
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
			CarenResult CreateSharedBitmap(
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
			CarenResult CreateSolidColorBrush(
				CA_D2D1_COLOR_F^ Param_Cor,
				CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
				[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush);

			/// <summary>
			/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor especificada e uma opacidade base de 1.0f.
			/// </summary>
			/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel(Brush).</param>
			/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
			CarenResult CreateSolidColorBrush(
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
			CarenResult DrawBitmap(
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
			CarenResult DrawEllipse(
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
			CarenResult DrawGeometry(
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
			CarenResult DrawGlyphRun(
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
			CarenResult DrawLine(
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
			CarenResult DrawRectangle(
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
			CarenResult DrawRoundedRectangle(
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
			CarenResult DrawText(
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
			CarenResult DrawTextLayout(
				CA_D2D1_POINT_2F^ Param_Origem,
				ICaren^ Param_TextLayout,
				ICarenD2D1Brush^ Param_DefaultFillBrush,
				CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes);

			/// <summary>
			/// Termina as operações de desenho no alvo de renderização e indica o estado de erro atual e as tags associadas. 
			/// </summary>
			/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
			/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
			CarenResult EndDraw(
				[Out] UInt64% Param_Out_Tag1,
				[Out] UInt64% Param_Out_Tag2);

			/// <summary>
			/// Pinta o interior da elipse especificada.
			/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
			/// ou ICarenD2D1RenderTarget::Flush.
			/// </summary>
			/// <param name="Param_Ellipse">A posição e o raio, em pixels independentes do dispositivo, da elipse para pintar.</param>
			/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior da elipse.</param>
			CarenResult FillEllipse(
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
			CarenResult FillGeometry(
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
			CarenResult FillMesh(
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
			CarenResult FillOpacityMask(
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
			CarenResult FillRectangle(
				CA_D2D1_RECT_F^ Param_Rect,
				ICarenD2D1Brush^ Param_Brush);

			/// <summary>
			/// Pinta o interior do retângulo arredondado especificado.
			/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
			/// ou ICarenD2D1RenderTarget::Flush.
			/// </summary>
			/// <param name="Param_Rect">As dimensões do retângulo arredondado para pintar, em pixels independentes do dispositivo.</param>
			/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo arredondado.</param>
			CarenResult FillRoundedRectangle(
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
			CarenResult Flush(
				[Out] UInt64% Param_Out_Tag1,
				[Out] UInt64% Param_Out_Tag2);

			/// <summary>
			/// Recupera o modo antialiasing atual para operações de desenho sem texto. 
			/// </summary>
			/// <param name="Param_Out_AntialiasMode">Retorna o modo antialiasing atual para operações de desenho sem texto.</param>
			void GetAntialiasMode([Out] CA_D2D1_ANTIALIAS_MODE% Param_Out_AntialiasMode);

			/// <summary>
			/// Retorne os pontos do alvo de renderização por polegada (DPI). 
			/// </summary>
			/// <param name="Param_Out_DpiX">Retorna o DPI horizontal do alvo de renderização.</param>
			/// <param name="Param_Out_DpiY">Retorna o DPI vertical do alvo de renderização. </param>
			void GetDpi(
				[Out] float% Param_Out_DpiX,
				[Out] float% Param_Out_DpiY);

			/// <summary>
			/// Obtém o tamanho máximo, em unidades dependentes de dispositivos (pixels), de qualquer dimensão de bitmap suportada pelo alvo de renderização.
			/// Este método retorna o tamanho máximo da textura do dispositivo Direct3D.
			/// O renderizador de software e os dispositivos WARP retornam o valor de 16 megapixels (16* 1024 * 1024). Você pode criar uma textura Direct2D que é deste tamanho, mas não uma textura Direct3D que 
			/// é deste tamanho.
			/// </summary>
			/// <param name="Param_Out_MaximumSize">Retorna o tamanho máximo, em pixels, de qualquer dimensão de bitmap suportada pelo alvo de renderização.</param>
			void GetMaximumBitmapSize([Out] UInt32% Param_Out_MaximumSize);

			/// <summary>
			/// Recupera o formato de pixel e o modo alfa do alvo de renderização. 
			/// </summary>
			/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do alvo de renderização.</param>
			void GetPixelFormat([Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat);

			/// <summary>
			/// Retorna o tamanho do alvo de renderização em pixels do dispositivo. 
			/// </summary>
			/// <param name="Param_Out_PixelSize">Retorna tamanho do alvo de renderização em pixels do dispositivo.</param>
			void GetPixelSize([Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize);

			/// <summary>
			/// Retorna o tamanho do alvo de renderização em pixels independentes do dispositivo.
			/// </summary>
			/// <param name="Param_Out_Size">Retorna tamanho atual do alvo de renderização em pixels independentes do dispositivo.</param>
			void GetSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size);

			/// <summary>
			/// Obtém o rótulo(Tags) para operações de desenho subsequentes. 
			/// </summary>
			/// <param name="Param_Out_Tag1">Retorna o primeiro rótulo para operações de desenho subsequentes.</param>
			/// <param name="Param_Out_Tag2">Retorna o segundo rótulo para operações de desenho subsequentes.</param>
			void GetTags(
				[Out] UInt64% Param_Out_Tag1,
				[Out] UInt64% Param_Out_Tag2);

			/// <summary>
			/// Obtém o modo antialiasing atual para operações de desenho de texto e glifo(Glyph). 
			/// </summary>
			/// <param name="Param_Out_TextAntialiasMode">Retorna o modo antialiasing atual para operações de desenho de texto e glifo(Glyph).</param>
			void GetTextAntialiasMode([Out] CA_D2D1_TEXT_ANTIALIAS_MODE% Param_Out_TextAntialiasMode);

			/// <summary>
			/// Recupera as opções de renderização de texto atual do alvo. 
			/// </summary>
			/// <param name="Param_Out_TextRenderingParams">Retorna a interface (IDWriteRenderingParams) que contém um ponteiro para as opções de renderização de texto atuais do destino. O usuário deve inicializar a interface antes de chamar este método.</param>
			void GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams);

			/// <summary>
			/// Obtém a transformação atual do alvo render. 
			/// </summary>
			/// <param name="Param_Out_Transform">Retorna a transformação atual do alvo de renderização.</param>
			void GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform);

			/// <summary>
			/// Indica se o alvo de renderização suporta as propriedades especificadas.
			/// Este método não avalia as configurações de DPI especificadas pelo parâmetro (Param_ProppriedadesRenderTarget).
			/// </summary>
			/// <param name="Param_ProppriedadesRenderTarget">As propriedades de destino de renderização para testar.</param>
			/// <param name="Param_Out_Suporta">Retorna um valor Booleano TRUE se as propriedades de destino de renderização especificadas forem suportadas por este alvo de renderização; caso contrário, FALSO.</param>
			void IsSupported(
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
			void PopAxisAlignedClip();

			/// <summary>
			/// Interrompe o redirecionamento das operações de desenho para a camada especificada pela última chamada do PushLayer.
			/// Um PopLayer deve corresponder a uma chamada pushlayer anterior.
			/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
			/// ou ICarenD2D1RenderTarget::Flush.
			/// </summary>
			void PopLayer();

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
			void PushAxisAlignedClip(
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
			void PushLayer(
				CA_D2D1_LAYER_PARAMETERS^ Param_ParametrosLayer,
				ICarenD2D1Layer^ Param_Layer);

			/// <summary>
			/// Define o estado de desenho do alvo de renderização ao do ID2D1DrawingStateBlock especificado.
			/// </summary>
			/// <param name="Param_DrawingStateBlock">O novo estado de desenho do alvo render.</param>
			CarenResult RestoreDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock);

			/// <summary>
			/// Salva o estado de desenho atual para o ID2D1DrawingStateBlock especificado. 
			/// </summary>
			/// <param name="Param_DrawingStateBlock">Retorna uma interface para o estado de desenho atual do alvo de renderização. Este parâmetro deve ser inicializado antes de passá-lo para o método.</param>
			CarenResult SaveDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock);

			/// <summary>
			/// Define o modo de antialiasing do alvo de renderização. O modo antialiasing aplica-se a todas as operações de desenho subsequentes, excluindo as operações de desenho de texto e glifo(Glyph). 
			/// Para especificar o modo antialiasing para operações de texto e glifos(Glyph), use o método SetTextAntialiasMode.
			/// </summary>
			/// <param name="Param_AntialiasMode">O modo antialiasing para futuras operações de desenho.</param>
			void SetAntialiasMode(CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode);

			/// <summary>
			/// Define os pontos por polegada (DPI) do alvo de renderização.
			/// Este método especifica o mapeamento do espaço pixel para o espaço independente do dispositivo para o alvo de renderização. Se tanto o DpiX quanto o DpiY forem 0, o DPI do sistema de leitura 
			/// de fábrica será escolhido. Se um parâmetro for zero e o outro não especificado, o DPI não será alterado.
			/// Para ICarenD2D1HwndRenderTarget, o DPI é padrão para o DPI mais recentemente do sistema de leitura de fábrica. O valor padrão para todas as outras metas de renderização é de 96 DPI.
			/// </summary>
			/// <param name="Param_DpiX">Um valor maior ou igual a zero que especifica o DPI horizontal do alvo de renderização.</param>
			/// <param name="Param_DpiY">Um valor maior ou igual a zero que especifica o DPI vertical do alvo de renderização.</param>
			void SetDpi(
				float Param_DpiX,
				float Param_DpiY);

			/// <summary>
			/// Especifica um rótulo(Tag) para operações de desenho subsequentes.
			/// As etiquetas(Tags) especificadas por este método são impressas por mensagens de erro depuração. Se nenhuma tag for definida, o valor padrão de cada tag é 0.
			/// </summary>
			/// <param name="Param_Tag1">Um rótulo para aplicar às operações de desenho subsequentes.</param>
			/// <param name="Param_Tag2">Um rótulo para aplicar às operações de desenho subsequentes.</param>
			void SetTags(
				UInt64 Param_Tag1,
				UInt64 Param_Tag2);

			/// <summary>
			/// Especifica o modo antialiasing a ser usado para operações subsequentes de desenho de texto e glifo(Glyph). 
			/// </summary>
			/// <param name="Param_TextAntialiasMode">O modo antialiasing para usar para operações subsequentes de desenho de texto e glifo(Glyph).</param>
			void SetTextAntialiasMode(CA_D2D1_TEXT_ANTIALIAS_MODE Param_TextAntialiasMode);

			/// <summary>
			/// Especifica as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho de texto e glifo(Glyph).
			/// Se as configurações especificadas por textRenderingParams forem incompatíveis com o modo antialiasing de texto do alvo de renderização (especificado por SetTextAntialiasMode), as operações 
			/// subsequentes de desenho de texto e glifo(Glyph) falharão e colocarão o alvo de renderização em um estado de erro.
			/// </summary>
			/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) para as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho 
			/// de texto e glifoGlyph); NULO para limpar as opções atuais de renderização de texto.</param>
			CarenResult SetTextRenderingParams(ICaren^ Param_TextRenderingParams);

			/// <summary>
			/// Aplica a transformação especificada ao alvo de renderização, substituindo a transformação existente. Todas as operações subsequentes de desenho ocorrem no espaço transformado. 
			/// </summary>
			/// <param name="Param_Transform">A transformação para aplicar ao alvo de renderização.</param>
			void SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);
		};

		/// <summary>
		/// (ID2D1DCRenderTarget) - Interface responsável por emitir comandos de desenho para um contexto de dispositivo GDI.
		/// Antes de renderizar com o alvo de renderização DC, você deve usar seu método BindDC para associá-lo a um GDI DC. Você faz isso cada vez que usa um DC diferente, ou o tamanho da área 
		/// que deseja desenhar para mudanças. Para permitir que o alvo de renderização DC funcione com o GDI, defina seu formato de pixel para DXGI_FORMAT_B8G8R8A8_UNORM e seu modo alfa para 
		/// D2D1_ALPHA_MODE_PREMULTIPLIED ou D2D1_ALPHA_MODE_IGNORE.
		/// Seu aplicativo deve criar metas de renderização uma vez e segurá-los durante a vida útil do aplicativo ou até que o método EndDraw do alvo de renderização retorne o erro D2DERR_RECREATE_TARGET. 
		/// Quando você recebe esse erro, você precisa recriar o destino render (e quaisquer recursos que ele criou).
		/// Para criar um ICarenD2D1DCRenderTarget, use o método ICarenD2D1Factory::CreateDCRenderTarget. Quando você usa um ID2D1DCRenderTarget, ele torna o conteúdo Direct2D em um bitmap interno e, 
		/// em seguida, torna o bitmap para o DC com GDI.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("C1615208-6F01-4094-97F4-AB5DE4A41676")]
		public interface class ICarenD2D1DCRenderTarget : ICarenD2D1RenderTarget
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Vincula o alvo de renderização ao contexto do dispositivo ao qual ele emite comandos de desenho.
			/// Antes de renderizar com o alvo de renderização DC, você deve usar seu método BindDC para associá-lo a um GDI DC. Você faz isso cada vez que usa um DC diferente, ou o tamanho da área 
			/// que deseja desenhar para mudanças.
			/// </summary>
			/// <param name="Param_Hdc">O contexto do dispositivo para o qual o alvo de renderização emite comandos de desenho.</param>
			/// <param name="Param_SubRect">As dimensões da Handle(Param_Hdc) para um contexto de dispositivo (HDC) a que o alvo de renderização está vinculado.</param>
			CarenResult BindDC(
				IntPtr Param_Hdc,
				CA_RECT^ Param_SubRect);
		};

		/// <summary>
		/// (ID2D1HwndRenderTarget) - Interface responsável por renderizar instruções de desenho para uma janela.
		/// Como é o caso de outros alvos de renderização, você deve chamar BeginDraw antes de emitir comandos de desenho. Depois de terminar de desenhar, ligue para o EndDraw para indicar que o 
		/// desenho está concluído e para liberar o acesso ao buffer que apoia o alvo de renderização.
		/// Para ICarenD2D1HwndRenderTarget, o único efeito colateral do BeginDraw é alterar o estado do alvo de renderização para permitir que os comandos de desenho sejam emitidos.
		/// Os objetos ICarenD2D1HwndRenderTarget são bufferados duplos, de modo que os comandos de desenho emitidos não aparecem imediatamente, mas sim são realizados em uma superfície fora da tela. 
		/// Quando o EndDraw é chamado, se não houver erros de renderização, o buffer offscreen será apresentado. Se houve erros de renderização no lote lavado pelo EndDraw, então o buffer não será 
		/// apresentado, e o aplicativo deve chamar BeginDraw e re-desenhar o quadro. O flush pode ser usado para verificar erros antes de ligar para o EndDraw se um aplicativo quiser que o quadro 
		/// seja apresentado independentemente de erros.
		/// O buffer traseiro de um alvo de renderização de hardware é o tamanho especificado pelo GetPixelSize. Se o EndDraw apresentar o buffer, este bitmap é estendido para cobrir a superfície 
		/// onde ele é apresentado: toda a área cliente da janela.
		/// Para criar um ICarenD2D1HwndRenderTarget, use o método ICarenD2D1Factory::CreateHwndRenderTarget.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("0851CEC7-69CF-4997-962F-5DF60D734493")]
		public interface class ICarenD2D1HwndRenderTarget : ICarenD2D1RenderTarget
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Indica se o HWND associado a este alvo de renderização está ocluído(occluded).
			/// Se a janela foi ocluída da última vez que o EndDraw foi chamado, da próxima vez que o alvo de renderização chamar CheckWindowState, ele retornará D2D1_WINDOW_STATE_OCCLUDED independentemente 
			/// do estado da janela atual. Se você quiser usar o CheckWindowState para determinar o estado de janela atual, você deve ligar para o CheckWindowState após cada chamada do EndDraw e ignorar seu 
			/// valor de retorno. Esta chamada garantirá que sua próxima chamada para o estado CheckWindowState retornará o estado real da janela.
			/// </summary>
			/// <param name="Param_Out_WindowState">Retorna um valor que indica se o HWND associado a este alvo de renderização é ocluído(occluded).</param>
			void CheckWindowState([Out] CA_D2D1_WINDOW_STATE% Param_Out_WindowState);

			/// <summary>
			/// Retorna o HWND associado a este alvo renderizador.
			/// </summary>
			/// <param name="Param_Out_Hwnd">Retorna o HWND associado a este alvo render.</param>
			void GetHwnd([Out] IntPtr% Param_Out_Hwnd);

			/// <summary>
			/// Altera o tamanho do alvo de renderização para o tamanho do pixel especificado. 
			/// </summary>
			/// <param name="Param_PixelSize">O novo tamanho do alvo de renderização em pixels do dispositivo.</param>
			CarenResult Resize(CA_D2D1_SIZE_U^ Param_PixelSize);


		};

		/// <summary>
		/// (ID2D1BitmapRenderTarget) - Interface responsável por renderizar para uma textura intermediária criada pelo método CreateCompatibleRenderTarget.
		/// Um ID2D1BitmapRenderTarget escreve para uma textura intermediária. É útil para criar padrões para uso com um ID2D1BitmapBrush ou dados de desenho de cache que serão usados repetidamente.
		/// Para escrever diretamente para um bitmap WIC, em vez disso, use o método ICarenD2D1Factory::CreateWicBitmapRenderTarget. Este método retorna um ICarenD2D1RenderTarget que grava para o bitmap 
		/// WIC especificado.
		/// Como outros alvos de renderização, um ICarenD2D1BitmapRenderTarget é um recurso dependente de dispositivos e deve ser recriado quando o dispositivo associado ficar indisponível.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("78E34653-B4B8-4192-80BA-3B428DCA2C57")]
		public interface class ICarenD2D1BitmapRenderTarget : ICarenD2D1RenderTarget
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o bitmap para este alvo renderizador. O bitmap retornado pode ser usado para operações de desenho.
			/// O DPI para o ID2D1Bitmap obtido do GetBitmap será o DPI do ICarenD2D1BitmapRenderTarget quando o alvo de renderização foi criado. Alterar o DPI do ICarenD2D1BitmapRenderTarget ligando 
			/// para SetDpi não afeta o DPI do bitmap, mesmo que o SetDpi seja chamado antes do GetBitmap. O uso do SetDpi para alterar o DPI do ID2D1BitmapRenderTarget afeta a forma como o conteúdo é 
			/// renderizado no bitmap: ele simplesmente não afeta o DPI do bitmap recuperado pelo GetBitmap.
			/// </summary>
			/// <param name="Param_Out_Bitmap">Retorna uma interface que contém um ponteiro para o bitmap para este destino renderizador.</param>
			CarenResult GetBitmap([Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);
		};

		/// <summary>
		/// (ID2D1TransformNode) - Interface responsável por descrever um nó em uma topologia de transformação.
		/// Os nós de transformação são sem tipo e apenas definem a noção de um objeto que aceita uma série de entradas e é uma saída. Esta interface limita uma topologia a um único nó de saída.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("1E617F53-2270-4BCD-B323-15042A64839B")]
		public interface class ICarenD2D1TransformNode : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o número de entradas para o nó de transformação. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este nó de transformação.</param>
			void GetInputCount([Out] UInt32% Param_Out_Quantidade);
		};

		/// <summary>
		/// (ID2D1ConcreteTransform) - Interface responsável por representar o conjunto de transformações implementadas pelo sistema de renderização de efeitos, que fornece funcionalidade fixa.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("1DB3C8FB-A14D-47FD-8AB5-571E9808DC7A")]
		public interface class ICarenD2D1ConcreteTransform : ICarenD2D1TransformNode
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Define se a saída da transformação especificada está armazenada em cache. 
			/// </summary>
			/// <param name="Param_IsCached">TRUE se a saída deve ser armazenada em cache; caso contrário, FALSO.</param>
			void SetCached(Boolean Param_IsCached);

			/// <summary>
			/// Define as propriedades do buffer de saída do nó de transformação especificado. 
			/// </summary>
			/// <param name="Param_BufferPrecision">O número de bits e o tipo de buffer de saída.</param>
			/// <param name="Param_ChannelDepth">O número de canais no buffer de saída (1 ou 4).</param>
			CarenResult SetOutputBuffer(
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth);
		};

		/// <summary>
		/// (ID2D1BlendTransform) - Interface responsável por fornecer métodos para permitir que uma operação de mistura seja inserida em um gráfico de transformação.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("2D05AF2F-6472-46A7-8975-B2DC5D004477")]
		public interface class ICarenD2D1BlendTransform : ICarenD2D1ConcreteTransform
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a descrição da mistura do objeto de transformação de mistura correspondente.
			/// </summary>
			/// <param name="Param_Out_Descricao">Retorna  a descrição da mistura especificada para a transformação da mistura.</param>
			void GetDescription([Out] CA_D2D1_BLEND_DESCRIPTION^% Param_Out_Descricao);

			/// <summary>
			/// Altera a descrição da mistura do objeto de transformação de mistura correspondente.
			/// </summary>
			/// <param name="Param_Descricao">A nova descrição da mistura especificada para a transformação da mistura.</param>
			void SetDescription(CA_D2D1_BLEND_DESCRIPTION^ Param_Descricao);
		};

		/// <summary>
		/// (ID2D1BorderTransform) - Interface responsável por estender o retângulo de entrada ao infinito usando os modos de extensão especificados.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("79686BFC-26D8-4F91-8F4A-6E4480DA1861")]
		public interface class ICarenD2D1BorderTransform : ICarenD2D1ConcreteTransform
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o modo de extensão na direção X.
			/// </summary>
			/// <param name="Param_Out_ExtendModeX">Retorna o modo de extensão na direção X.</param>
			void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX);

			/// <summary>
			/// Obtém o modo de extensão na direção Y.
			/// </summary>
			/// <param name="Param_Out_ExtendModeY">Retorna o modo de extensão na direção Y.</param>
			void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY);

			/// <summary>
			/// Define o modo de extensão na direção X.
			/// Se a enumeração do modo de extensão for inválida, esta operação será ignorada.
			/// </summary>
			/// <param name="Param_ExtendModeX">O modo de extensão na direção X.</param>
			void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ExtendModeX);

			/// <summary>
			/// Define o modo de extensão na direção Y.
			/// Se a enumeração do modo de extensão for inválida, esta operação será ignorada.
			/// </summary>
			/// <param name="Param_ExtendModeY">O modo de extensão na direção Y.</param>
			void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ExtendModeY);
		};

		/// <summary>
		/// (ID2D1Transform) - Interface responsável por representar a interface base para todas as transformações implementadas pelo autor da transformação.
		/// As transformações são agregadas por autores de efeitos. Esta interface fornece uma interface comum para implementar os cálculos do retângulo Shantzis, que é a base para todo 
		/// o processamento de transformação em extensões de imagem Direct2D.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8D335B2A-2A16-4CAA-8751-C5F1CAC10AF1")]
		public interface class ICarenD2D1Transform : ICarenD2D1TransformNode
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Realiza o mapeamento inverso para MapOutputRectToInputRects.
			/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
			/// Ao contrário das funções MapOutputRectToInputRects e MapInvalidRect, este método é explicitamente chamado pelo renderizador em um determinado lugar em seu algoritmo de renderização. A implementação 
			/// da transformação pode alterar seu estado com base nos retângulos de entrada e usar essas informações para controlar suas informações de renderização. Este método é sempre chamado antes dos métodos 
			/// MapInvalidRect e MapOutputRectToInputRects da transformação.
			/// </summary>
			/// <param name="Param_InputRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída. O parâmetro (Param_InputRects) é sempre igual aos limites de entrada.</param>
			/// <param name="Param_InputOpaqueSubRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída opaco.</param>
			/// <param name="Param_QuantidadeRetangulos">O número de entradas especificadas. A implementação garante que isso seja igual ao número de entradas especificadas na transformação.</param>
			/// <param name="Param_Out_OutputRect">Retorna o retângulo de saída que mapeia o retângulo de entrada correspondente.</param>
			/// <param name="Param_Out_OutputOpaqueSubRect">Retorna o retângulo de saída que mapeia o retângulo de entrada opaco correspondente.</param>
			CarenResult MapInputRectsToOutputRect(
				cli::array<CA_D2D1_RECT_L^>^ Param_InputRects,
				cli::array<CA_D2D1_RECT_L^>^ Param_InputOpaqueSubRects,
				UInt32 Param_QuantidadeRetangulos,
				[Out] CA_D2D1_RECT_L^% Param_Out_OutputRect,
				[Out] CA_D2D1_RECT_L^% Param_Out_OutputOpaqueSubRect);

			/// <summary>
			/// Define os retângulos de entrada para este passe de renderização na transformação.
			/// A implementação da transformação deve considerar o MapInvalidRect como puramente funcional. A implementação da transformação pode basear o retângulo de entrada mapeado no estado atual da implementação 
			/// da transformação, conforme especificado pelas propriedades de efeito encapsulamento. Mas a implementação da transformação não pode mudar seu próprio estado em resposta a uma chamada ao MapInvalidRect. 
			/// O Direct2D pode chamar esse método a qualquer momento e em qualquer sequência após uma chamada para o método MapInputRectsToOutputRect.
			/// </summary>
			/// <param name="Param_InputIndex">O índice do retângulo de entrada.</param>
			/// <param name="Param_InvalidInputRect">O retângulo de entrada inválido.</param>
			/// <param name="Param_Out_InvalidOutputRect">Retorna o retângulo de saída para o qual o retângulo de entrada deve ser mapeado.</param>
			CarenResult MapInvalidRect(
				UInt32 Param_InputIndex,
				CA_D2D1_RECT_L^ Param_InvalidInputRect,
				[Out] CA_D2D1_RECT_L^% Param_Out_InvalidOutputRect);

			/// <summary>
			/// Permite uma transformação para afirmar como mapearia um retângulo solicitado em sua saída para um conjunto de retângulos de amostra em sua entrada. 
			/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
			/// A implementação da transformação deve considerar esse método como puramente funcional. Ele pode basear os retângulos de entrada e saída mapeados em seu estado atual, conforme especificado pelas 
			/// propriedades de efeito encapsulamento. No entanto, não deve mudar seu próprio estado em resposta a este método que está sendo invocado. A implementação do renderizador Direct2D reserva-se o direito 
			/// de chamar este método a qualquer momento e em qualquer sequência.
			/// </summary>
			/// <param name="Param_OutputRect">O retângulo de saída do qual as entradas devem ser mapeadas.</param>
			/// <param name="Param_Out_InputRects">O conjunto correspondente de entradas. As entradas corresponderão diretamente aos insumos de transformação.</param>
			/// <param name="Param_InputRectsCount">O número de entradas especificadas. O Direct2D garante que isso seja igual ao número de entradas especificadas na transformação.</param>
			CarenResult MapOutputRectToInputRects(
				CA_D2D1_RECT_L^ Param_OutputRect,
				[Out] cli::array<CA_D2D1_RECT_L^>^% Param_Out_InputRects,
				UInt32 Param_InputRectsCount);
		};

		/// <summary>
		/// (ID2D1SourceTransform) - Interface responsável por representar um estágio de rasterização baseado em CPU no gráfico do pipeline de transformação.
		/// O ICarenD2D1SourceTransform é especializado na implementação dos cálculos de Shantzis para uma transformação implementada como fonte de um gráfico de efeitos com os dados sendo fornecidos a partir da memória do sistema.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("1C2AC575-217A-4161-90C0-174B1814CDCA")]
		public interface class ICarenD2D1SourceTransform : ICarenD2D1Transform
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Desenha a transformação para o pipeline do Direct2D baseado na unidade de processamento gráfico(GPU).
			/// A implementação do rasterizador garante que a adição da (Param_DrawRect) ao (Param_TargetOrigin) não excede os limites do bitmap.
			/// Se você definir a precisão do buffer manualmente no objeto ICarenD2D1RenderInfo associado, ele deve lidar com diferentes formatos de pixels neste método chamando ICarenD2D1Bitmap::GetPixelFormat. 
			/// Se você definir a precisão do buffer manualmente, então você pode confiar nesse formato sendo sempre o que você forneceu. 
			/// </summary>
			/// <param name="Param_Target">O alvo para o qual a transformação deve ser escrita.</param>
			/// <param name="Param_DrawRect">A área dentro da fonte a partir da qual a imagem deve ser desenhada.</param>
			/// <param name="Param_TargetOrigin">A origem dentro do bitmap de destino para o qual os dados de origem devem ser desenhados.</param>
			CarenResult Draw(
				ICarenD2D1Bitmap1^ Param_Target,
				CA_D2D1_RECT_L^ Param_DrawRect,
				CA_D2D1_POINT_2U^ Param_TargetOrigin);

			/// <summary>
			/// Define as informações de renderização para a transformação.
			/// Fornece uma interface de informações de renderização para a transformação de origem para permitir que ela especifique o estado para o sistema de renderização.
			/// </summary>
			/// <param name="Param_RenderInfo">A interface fornecida à transformação para permitir especificar a passagem de transformação baseada na CPU.</param>
			CarenResult SetRenderInfo(ICarenD2D1RenderInfo^ Param_RenderInfo);
		};

		/// <summary>
		/// (ID2D1BoundsAdjustmentTransform) - Interface responsável por uma transformação de suporte para efeitos para modificar o retângulo de saída do efeito anterior ou bitmap.
		/// A transformação de suporte pode ser usada por duas razões diferentes: Para indicar que uma região de sua imagem de entrada já é preto transparente. A área expandida será tratada como preta transparente. 
		/// Isso pode aumentar a eficiência para renderizar bitmaps.
		/// e Para aumentar o tamanho da imagem de entrada.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("ABDB2837-B1FC-4BA3-9CAA-06FCA57C3403")]
		public interface class ICarenD2D1BoundsAdjustmentTransform : ICarenD2D1TransformNode
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Retorna o retângulo de saída da transformação de suporte.
			/// </summary>
			/// <param name="Param_Out_RectL">Retorna os limites de saída.</param>
			void GetOutputBounds([Out] CA_D2D1_RECT_L^% Param_Out_RectL);

			/// <summary>
			/// Isso define os limites de saída para a transformação de suporte.
			/// </summary>
			/// <param name="Param_RectL">Os limites de saída.</param>
			void SetOutputBounds(CA_D2D1_RECT_L^ Param_RectL);
		};

		/// <summary>
		/// (ID2D1SpriteBatch) - Interface responsável por representar um único grupo de sprites com suas propriedades de desenho associadas.
		/// Sprites são uma maneira de os aplicativos desenharem um grande número de imagens com muita eficiência.Eles são comumente usados ​​para renderizar personagens e cenários em jogos 2D ou para renderizar 
		/// sistemas de partículas como fumaça e chamas.Se seu aplicativo exigir desempenho e precisar desenhar centenas ou milhares de imagens a cada quadro, considere aproveitar os lotes de sprites e o controle 
		/// refinado que eles oferecem, em vez do método DrawImage de uso geral.
		/// Crie um novo lote sprite usando ICarenD2D1DeviceContext3::CreateSpriteBatch. Use ICarenD2D1DeviceContext3::DrawSpriteBatch para desenhá-los.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("FE78B687-E4F1-4D34-8559-7D961E611452")]
		public interface class ICarenD2D1SpriteBatch : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Adiciona os sprites dado ao final deste lote sprite.
			/// No Direct2D, um sprite é definido por quatro propriedades: um retângulo de destino, um retângulo de origem, uma cor e uma transformação. Os retângulos de destino são obrigatórios, mas as demais 
			/// propriedades são opcionais.
			/// Sempre omitir ou passar um valor nulo para propriedades que você não deseja usar. Isso permite que o Direct2D evite armazenar valores para essas propriedades e pule totalmente seu manuseio, o 
			/// que melhora a velocidade de desenho.
			/// </summary>
			/// <param name="Param_QuantidadeSprites">O número de sprites a serem adicionados. Isso determina quantos passos em cada matriz direct2D será lido.</param>
			/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
			/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
			/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos 
			/// os sprites adicionados.</param>
			/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
			/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não mudará
			/// a cor de nenhum dos sprites adicionados.</param>
			/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que sejam
			/// atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites adicionados.</param>
			/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
			/// será usado para cada sprite adicionado.</param>
			/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
			/// de origem será usado para cada sprite adicionado.</param>
			/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
			/// adicionado.</param>
			/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
			/// será usada para cada sprite adicionado.</param>
			CarenResult AddSprites(
				UInt32 Param_QuantidadeSprites,
				cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
				cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
				cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
				cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
				UInt32 Param_DestinationRectanglesStride,
				UInt32 Param_SourceRectanglesStride,
				UInt32 Param_ColorsStride,
				UInt32 Param_TransformStride);

			/// <summary>
			/// Remove todos os sprites deste lote de sprite. 
			/// </summary>
			void Clear();

			/// <summary>
			/// Recupera o número de sprites neste lote sprite. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de sprites neste lote de sprites.</param>
			void GetSpriteCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera o subconjunto especificado de sprites deste lote sprite. Para obter o melhor desempenho, use NULL para propriedades que você não precisa recuperar. 
			/// </summary>
			/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para recuperar.</param>
			/// <param name="Param_QuantidadeSprites">O número de sprites para recuperar.</param>
			/// <param name="Param_Ref_RetangulosDestino">Retorna uma matriz contendo os retângulos de destino para os sprites recuperados.</param>
			/// <param name="Param_Ref_RetangulosOrigem">Retorna uma matriz contendo os retângulos de origem para os sprites recuperados. O InfiniteRectU é devolvido para quaisquer sprites que não foram atribuídos 
			/// a um retângulo de origem.</param>
			/// <param name="Param_Ref_Cores">Retorna uma matriz contendo as cores a serem aplicadas aos sprites recuperados. A cor {1.0f, 1.0f, 1.0f, 1.0f} é devolvida para quaisquer sprites que não foram 
			/// atribuídos uma cor.</param>
			/// <param name="Param_Ref_Transform">Retorna uma matriz contendo as transformações a serem aplicadas aos sprites recuperados. A matriz de identidade é devolvida para quaisquer sprites que não 
			/// foram atribuídos uma transformação.</param>
			CarenResult GetSprites(
				UInt32 Param_StartIndex,
				UInt32 Param_QuantidadeSprites,
				cli::array<CA_D2D1_RECT_F^>^% Param_Ref_RetangulosDestino,
				cli::array<CA_D2D1_RECT_U^>^% Param_Ref_RetangulosOrigem,
				cli::array<CA_D2D1_COLOR_F^>^% Param_Ref_Cores,
				cli::array<CA_D2D1_MATRIX_3X2_F^>^% Param_Ref_Transform);

			/// <summary>
			/// Atualiza as propriedades dos sprites especificados neste lote sprite. Fornecer um valor nulo para qualquer propriedade deixará essa propriedade não modificada para esse valor.
			/// </summary>
			/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para atualização.</param>
			/// <param name="Param_QuantidadeSprites">O número de sprites para atualizar com novas propriedades. Isso determina quantos passos em cada matriz direct2D será lido.</param>
			/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
			/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
			/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos os 
			/// sprites atualizados.</param>
			/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
			/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não 
			/// alterará a cor de nenhum dos sprites atualizados.</param>
			/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que 
			/// sejam atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites atualizados.</param>
			/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
			/// será usado para cada sprite atualizado.</param>
			/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
			/// de origem será usado para cada sprite atualizado.</param>
			/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
			/// atualizado.</param>
			/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
			/// será usada para cada sprite atualizado.</param>
			CarenResult SetSprites(
				UInt32 Param_StartIndex,
				UInt32 Param_QuantidadeSprites,
				cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
				cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
				cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
				cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
				UInt32 Param_DestinationRectanglesStride,
				UInt32 Param_SourceRectanglesStride,
				UInt32 Param_ColorsStride,
				UInt32 Param_TransformStride);
		};

		/// <summary>
		/// (ID2D1Ink) - Interface responsável por representar um único Stroke contínuo de tinta de largura variável, conforme definido por uma série de segmentos e larguras de Bezier.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("34B2FBD9-3D77-44D9-9771-C135B362361D")]
		public interface class ICarenD2D1Ink : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Adiciona os segmentos dado ao final deste objeto de tinta. 
			/// </summary>
			/// <param name="Param_Segments">Uma matriz de segmentos a serem adicionados a este objeto de tinta.</param>
			/// <param name="Param_Quantidade">O número de segmentos a serem adicionados a este objeto de tinta.</param>
			CarenResult AddSegments(
				cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^ Param_Segments,
				UInt32 Param_Quantidade);

			/// <summary>
			/// Recupere os limites da geometria, com uma transformação aplicada opcional. 
			/// </summary>
			/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação dos limites deste objeto de tinta.</param>
			/// <param name="Param_WorldTransform">A Wolrd Transform para ser usado na determinação dos limites deste objeto de tinta.</param>
			/// <param name="Param_Out_Bounds">Retorna os limites deste objeto de tinta.</param>
			CarenResult GetBounds(
				ICarenD2D1InkStyle^ Param_InkStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

			/// <summary>
			/// Retorna o número de segmentos neste objeto de tinta. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de segmentos neste objeto de tinta.</param>
			void GetSegmentCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera o subconjunto especificado de segmentos armazenados neste objeto de tinta. 
			/// </summary>
			/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser recuperado.</param>
			/// <param name="Param_Out_Segments">Retorna uma matriz de segmentos recuperados.</param>
			/// <param name="Param_Quantidade">O número de segmentos para recuperar. Observe que o (Param_Quantidade) deve ser menor ou igual ao número de segmentos no objeto de tinta menos (Param_StartSegments).</param>
			CarenResult GetSegments(
				UInt32 Param_StartSegments,
				[Out] cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Out_Segments,
				UInt32 Param_Quantidade);

			/// <summary>
			/// Recupera o ponto de partida para este objeto de tinta. 
			/// </summary>
			/// <param name="Param_Out_Point">Retorna o ponto de partida para este objeto de tinta.</param>
			void GetStartPoint([Out] CA_D2D1_INK_POINT^% Param_Out_Point);

			/// <summary>
			/// Remove o número dado de segmentos da extremidade deste objeto de tinta. 
			/// </summary>
			/// <param name="Param_QuantidadeSegments">O número de segmentos a serem removidos do final deste objeto de tinta. Observe que o (Param_QuantidadeSegments) deve ser menor ou igual ao número 
			/// de segmentos no objeto de tinta.</param>
			CarenResult RemoveSegmentsAtEnd(UInt32 Param_QuantidadeSegments);

			/// <summary>
			/// Atualiza o último segmento neste objeto de tinta com novos pontos de controle. 
			/// </summary>
			/// <param name="Param_Segment">Uma estrutura que contém os dados do segmento com os quais substituir o último segmento deste objeto de tinta. Observe que se não houver atualmente segmentos 
			/// no objeto de tinta, o SetSegmentsAtEnd retornará um erro.</param>
			CarenResult SetSegmentAtEnd(CA_D2D1_INK_BEZIER_SEGMENT^ Param_Segment);

			/// <summary>
			/// Atualiza os segmentos especificados neste objeto de tinta com novos pontos de controle. 
			/// </summary>
			/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser atualizado.</param>
			/// <param name="Param_Segments">Uma matriz com os dados do segmento a ser usado na atualização.</param>
			/// <param name="Param_Quantidade">O número de segmentos neste objeto de tinta que será atualizado com novos dados. Observe que o segmentsCount deve ser menor ou igual ao número de segmentos 
			/// no objeto de tinta menos (Param_StartSegments).</param>
			CarenResult SetSegments(
				UInt32 Param_StartSegments,
				cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Segments,
				UInt32 Param_Quantidade);

			/// <summary>
			/// Define o ponto de partida para este objeto de tinta. Isso determina onde este objeto de tinta começará a renderizar.
			/// </summary>
			/// <param name="Param_StartPoint">O novo ponto de partida para este objeto de tinta.</param>
			void SetStartPoint(CA_D2D1_INK_POINT^ Param_StartPoint);

			/// <summary>
			/// Recupera uma representação geométrica deste objeto de tinta. 
			/// </summary>
			/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
			/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica.</param>
			/// <param name="Param_FlatteningTolerance">O Flattening Tolerance a ser usada na determinação da representação geométrica.</param>
			/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
			CarenResult StreamAsGeometry(
				ICarenD2D1InkStyle^ Param_InkStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatteningTolerance,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

			/// <summary>
			/// Recupera uma representação geométrica deste objeto de tinta. 
			/// </summary>
			/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
			/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica</param>
			/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
			CarenResult StreamAsGeometry(
				ICarenD2D1InkStyle^ Param_InkStyle,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);
		};

		/// <summary>
		/// (ID2D1CommandSink) - O Command Sink é implementada por você para um aplicativo quando você deseja receber uma reprodução dos comandos gravados em uma lista de comando. Um uso típico será para transformar a 
		/// lista de comando em outro formato, como o XPS, quando algum grau de conversão entre os primitivos Direct2D e o formato de destino é necessário.
		/// Nem todos os métodos implementados pelo ICarenD2D1DeviceContext estão presentes.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("184A28BC-39D7-44E1-B28B-A0A36BFC8312")]
		public interface class ICarenD2D1CommandSink : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Delegates


			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnBeginDraw();
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnClear(CA_D2D1_COLOR_F^ Param_Cor);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawBitmap(
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				float Param_Opacidade,
				CA_D2D1_INTERPOLATION_MODE Param_ModoInterpolacao,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem,
				CA_D2D1_MATRIX_4X4_F^ Param_PespectiveTransform);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawGdiMetafile(
				ICaren^ Param_GdiMetafile,
				CA_D2D1_POINT_2F^ Param_TargetOffset);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawGeometry(
				ICarenD2D1Geometry^ Param_Geometria,
				ICarenD2D1Brush^ Param_Brush,
				float StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawGlyphRun(
				CA_D2D1_POINT_2F^ Param_Baseline,
				CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
				CA_DWRITE_GLYPH_RUN_DESCRIPTION^ Param_GlyphRunDescription,
				ICarenD2D1Brush^ Param_ForegroundBrush,
				CA_DWRITE_MEASURING_MODE Param_MeasuringMode);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawImage(
				ICarenD2D1Image^ Param_Imagem,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_RECT_F^ Param_RetanguloImagem,
				CA_D2D1_INTERPOLATION_MODE Param_ModoInterpolacao,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawLine(
				CA_D2D1_POINT_2F^ Param_Point0,
				CA_D2D1_POINT_2F^ Param_Point1,
				ICarenD2D1Brush^ Param_Brush,
				float StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawRectangle(
				CA_D2D1_RECT_F^ Param_Rect,
				ICarenD2D1Brush^ Param_Brush,
				float StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnEndDraw();
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnFillGeometry(
				ICarenD2D1Geometry^ Param_Geometria,
				ICarenD2D1Brush^ Param_Brush,
				ICarenD2D1Brush^ Param_BrushOpacidade);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnFillMesh(
				ICarenD2D1Mesh^ Param_Mesh,
				ICarenD2D1Brush^ Param_Brush);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnFillOpacityMask(
				ICarenD2D1Bitmap^ Param_OpacityMask,
				ICarenD2D1Brush^ Param_Brush,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnFillRectangle(
				CA_D2D1_RECT_F^ Param_Rect,
				ICarenD2D1Brush^ Param_Brush);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnPopAxisAlignedClip();
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnPopLayer();
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnPushAxisAlignedClip(
				CA_D2D1_RECT_F^ Param_ClipRect,
				CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnPushLayer(
				CA_D2D1_LAYER_PARAMETERS1^ Param_ParametrosLayer,
				ICarenD2D1Layer^ Param_Layer);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetAntialiasMode(CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetPrimitiveBlend(CA_D2D1_PRIMITIVE_BLEND Param_PrimitiveBlend);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetTags(
				UInt64 Param_Tag1,
				UInt64 Param_Tag2);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetTextAntialiasMode(
				CA_D2D1_TEXT_ANTIALIAS_MODE Param_TextAntialiasMode);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetTextRenderingParams(
				ICaren^ Param_TextRenderingParams);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetUnitMode(CA_D2D1_UNIT_MODE Param_UnitMode);




			//Eventos


			/// <summary>
			/// Evento chamado para notificar a implementação do Command Sink que o desenho está prestes a começar.
			/// </summary>
			event DelegateOnBeginDraw^ OnBeginDraw;
			/// <summary>
			/// Evento chamado para notificar que a área de desenho foi limpa para uma cor especificada.
			/// </summary>
			event DelegateOnClear^ OnClear;
			/// <summary>
			/// Evento chamado para notificar que foi feita uma chamada para desenhar(Draw) em um bitmap para o alvo de renderização.
			/// </summary>
			event DelegateOnDrawBitmap^ OnDrawBitmap;
			/// <summary>
			/// Evento chamado para notificar que foi feita uma chamada para desenhar(Draw) um metafile para o contexto do dispositivo.
			/// </summary>
			event DelegateOnDrawGdiMetafile^ OnDrawGdiMetafile;
			/// <summary>
			/// Evento chamado para notificar a geometria a ser desenhada para o coletor de comando(Command Sink).
			/// </summary>
			event DelegateOnDrawGeometry^ OnDrawGeometry;
			/// <summary>
			/// Evento chamado para notificar os glifos(Glyph) a serem desenhados.
			/// </summary>
			event DelegateOnDrawGlyphRun^ OnDrawGlyphRun;
			/// <summary>
			/// Evento chamado para notificar uma chamada para desenhar(Draw) uma imagem para o coletor de comandos.
			/// </summary>
			event DelegateOnDrawImage^ OnDrawImage;
			/// <summary>
			/// Evento chamado para notificar que foi feita uma chamada para desenhar(Draw) uma linha traçada entre dois pontos.
			/// </summary>
			event DelegateOnDrawLine^ OnDrawLine;
			/// <summary>
			/// Evento chamado para notificar o desenho de um retângulo.
			/// </summary>
			event DelegateOnDrawRectangle^ OnDrawRectangle;
			/// <summary>
			/// Evento chamado para notificar que uma operação de desenho foi concluida.
			/// </summary>
			event DelegateOnEndDraw^ OnEndDraw;
			/// <summary>
			/// Evento chamado para notificar um preenchimento(Fill) de uma geometria.
			/// </summary>
			event DelegateOnFillGeometry^ OnFillGeometry;
			/// <summary>
			/// Evento chamado para notificar uma malha(Mesh) a ser preenchida pelo coletor de comando.
			/// </summary>
			event DelegateOnFillMesh^ OnFillMesh;
			/// <summary>
			/// Evento chamado para notificar um preenchimento(Fill) de uma máscara de opacidade no coletor de comando.
			/// </summary>
			event DelegateOnFillOpacityMask^ OnFillOpacityMask;
			/// <summary>
			/// Evento chamado para notificar o preenchimento(Fill) de um retângulo.
			/// </summary>
			event DelegateOnFillRectangle^ OnFillRectangle;
			/// <summary>
			/// Evento chamado para notificar a remoção de um clipe alinhado ao eixo da camada e da pilha de clipes.
			/// </summary>
			event DelegateOnPopAxisAlignedClip^ OnPopAxisAlignedClip;
			/// <summary>
			/// Evento chamado para notificar a remoção de uma camada da camada e da pilha de clipes.
			/// </summary>
			event DelegateOnPopLayer^ OnPopLayer;
			/// <summary>
			/// Evento chamado para notificar a inclusão de um retângulo de recorte para o clipe e a pilha de camadas.
			/// </summary>
			event DelegateOnPushAxisAlignedClip^ OnPushAxisAlignedClip;
			/// <summary>
			/// Evento chamado para notificar adição de uma camada sobre o clipe e a pilha de camadas.
			/// </summary>
			event DelegateOnPushLayer^ OnPushLayer;
			/// <summary>
			/// Evento chamado para notificar a definição do modo antialiasing que será usado para renderizar qualquer geometria subsequente.
			/// </summary>
			event DelegateOnSetAntialiasMode^ OnSetAntialiasMode;
			/// <summary>
			/// Evento chamado para notificar a definição de um novo modo de mistura primitiva(PrimitiveBlend).
			/// </summary>
			event DelegateOnSetPrimitiveBlend^ OnSetPrimitiveBlend;
			/// <summary>
			/// Evento chamado para notificar a definição das tags que correspondem às tags no coletor de comando.
			/// </summary>
			event DelegateOnSetTags^ OnSetTags;
			/// <summary>
			/// Evento chamado para indidicar o novo modo antialiasing padrão para texto.
			/// </summary>
			event DelegateOnSetTextAntialiasMode^ OnSetTextAntialiasMode;
			/// <summary>
			/// Evento chamado para indicar parâmetros de renderização de texto mais detalhados. 
			/// </summary>
			event DelegateOnSetTextRenderingParams^ OnSetTextRenderingParams;
			/// <summary>
			/// Evento chamado para notificar uma nova transformação.
			/// </summary>
			event DelegateOnSetTransform^ OnSetTransform;
			/// <summary>
			/// Evento chamado para notificar a alteração do significado de unidades subsequentes de pixels independentes do dispositivo (DIPs) para pixels ou de outra maneira. O Colegor de comando não grava 
			/// um DPI, isso está implícito pelo contexto de reprodução ou outra interface de reprodução, como o ICarenD2D1PrintControl.  
			/// </summary>
			event DelegateOnSetUnitMode^ OnSetUnitMode;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (ID2D1CommandList) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("D7DBC679-1421-4D4F-B98E-2AD569DB2F0F")]
		public interface class ICarenD2D1CommandList : ICarenD2D1Image
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Instrui a lista de comandos a parar de aceitar comandos para que você possa usá-lo como uma entrada para um efeito ou em uma chamada para ICarenD2D1DeviceContext::DrawImage. 
			/// </summary>
			CarenResult Close();

			/// <summary>
			/// Transmite o conteúdo da lista de comando para o Command Sink especificada. 
			/// </summary>
			/// <param name="Param_Sink">O Sink para qual a lista de comando será transmitida.</param>
			CarenResult Stream(ICarenD2D1CommandSink^ Param_Sink);
		};

		/// <summary>
		/// (ID2D1CommandSink1) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("CA8E4B9A-E49F-40C7-A522-7633D37254DA")]
		public interface class ICarenD2D1CommandSink1 : ICarenD2D1CommandSink
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetPrimitiveBlend1(CA_D2D1_PRIMITIVE_BLEND Param_PrimitiveBlend);



			//Eventos

			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnSetPrimitiveBlend1^ OnSetPrimitiveBlend1;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (ID2D1CommandSink2) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando. 
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("CA57DE7E-D90B-493C-BA14-3960A0B4F6A0")]
		public interface class ICarenD2D1CommandSink2 : ICarenD2D1CommandSink1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawGdiMetafile1(
				ICaren^ Param_GdiMetafile,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawGradientMesh(ICarenD2D1GradientMesh^ Param_GradientMesh);
			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawInk(
				ICarenD2D1Ink^ Param_Ink,
				ICarenD2D1Brush^ Param_Brush,
				ICarenD2D1InkStyle^ Param_InkStyle);



			//Eventos

			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnDrawGdiMetafile^ OnDrawGdiMetafile;
			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnDrawGradientMesh^ OnDrawGradientMesh;
			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnDrawInk^ OnDrawInk;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();

		};

		/// <summary>
		/// (ID2D1CommandSink3) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9636A6BF-0DCC-4172-BD4A-77959519DB43")]
		public interface class ICarenD2D1CommandSink3 : ICarenD2D1CommandSink2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnDrawSpriteBatch(
				ICarenD2D1SpriteBatch^ Param_SpriteBatch,
				UInt32 Param_StartIndex,
				UInt32 Param_SpriteCount,
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_SPRITE_OPTIONS Param_SpriteOptions);


			//Eventos

			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnDrawSpriteBatch^ OnDrawSpriteBatch;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (ID2D1CommandSink4) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("C2C77CC3-6AEA-4FD1-A5DF-B35FE7556633")]
		public interface class ICarenD2D1CommandSink4 : ICarenD2D1CommandSink3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnSetPrimitiveBlend2(
				CA_D2D1_PRIMITIVE_BLEND Param_PrimitiveBlend);


			//Eventos

			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnSetPrimitiveBlend2^ OnSetPrimitiveBlend2;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (ID2D1CommandSink5) - Interface responsável por representar uma sequência de comandos que podem ser gravados e reproduzidos.
		/// A lista de comando não inclui cópias estáticas de recursos com o conjunto de comandos gravados. Todos os bitmaps, efeitos e geometrias são armazenados como referências ao recurso real e todos os pincéis são 
		/// armazenados por valor. Toda a criação e destruição de recursos acontece fora da lista de comando. A tabela a seguir lista os recursos e como eles são tratados dentro de uma lista de comando.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("1A3822EF-4921-4615-B072-DA253D9B0E95")]
		public interface class ICarenD2D1CommandSink5 : ICarenD2D1CommandSink4
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// 
			/// </summary>
			delegate void DelegateOnBlendImage(
				ICarenD2D1Image^ Param_Imagem,
				CA_D2D1_BLEND_MODE Param_BlendMode,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_RECT_F^ Param_RetanguloImagem,
				CA_D2D1_INTERPOLATION_MODE Param_ModoInterpolacao);


			//Eventos

			/// <summary>
			/// Evento chamado para notificar 
			/// </summary>
			event DelegateOnBlendImage^ OnBlendImage;


			//Metodos

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (ID2D1ResourceTexture) - Interface responsável por rastreiar uma textura de recurso criada por transformação.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("29623CEE-3ED0-40F2-B731-DAFB392BF1B9")]
		public interface class ICarenD2D1ResourceTexture : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Atualiza a textura específica do recurso dentro da faixa ou caixa específica usando os dados fornecidos. 
			/// </summary>
			/// <param name="Param_MinimumExtents">A extensão "esquerda" das atualizações se especificada; se NULO, toda a textura é atualizada.</param>
			/// <param name="Param_MaximumExtents">A extensão "direita" das atualizações, se especificada; se NULO, toda a textura é atualizada.</param>
			/// <param name="Param_Strides">O stride para avançar através dos dados de entrada, de acordo com a dimensão.</param>
			/// <param name="Param_Dimensoes">O número de dimensões na textura do recurso. Isso deve corresponder ao número usado para carregar a textura.</param>
			/// <param name="Param_Buffer">Os dados a serem colocados na textura do recurso.</param>
			/// <param name="Param_DataCount">O tamanho do buffer de dados a ser usado para atualizar a textura do recurso.</param>
			CarenResult Update(
				cli::array<UInt32>^ Param_MinimumExtents,
				cli::array<UInt32>^ Param_MaximumExtents,
				cli::array<UInt32>^ Param_Strides,
				UInt32 Param_Dimensoes,
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_DataCount);
		};

		/// <summary>
		/// (ID2D1ComputeInfo) - Interface responsável por permitir a especificação de informações para um pass de renderização de sombreamento de computação (compute-shader rendering).
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F0A63088-A4C2-4C32-A280-F7E281ED3F27")]
		public interface class ICarenD2D1ComputeInfo : ICarenD2D1RenderInfo
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Define o sombreador de cálculo ao recurso shader dado. O recurso deve ser carregado antes que esta chamada seja feita. 
			/// </summary>
			/// <param name="Param_ShaderId">O GUID do sombreador.</param>
			CarenResult SetComputeShader(String^ Param_ShaderId);

			/// <summary>
			/// Estabelece ou altera os dados de buffer constantes para essa transformação. 
			/// </summary>
			/// <param name="Param_Buffer">Os dados aplicados ao buffer constante.</param>
			/// <param name="Param_DataCount">O número de bytes de dados no buffer constante.</param>
			CarenResult SetComputeShaderConstantBuffer(
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_DataCount);

			/// <summary>
			/// Define a textura do recurso correspondente ao índice de textura do sombreador dado ao recurso de textura dado. O recurso de textura já deve ter sido carregado com o
			/// método ICarenD2D1EffectContext::CreateResourceTexture. Esta chamada falhará se o índice especificado se sobrepor a qualquer entrada. Os índices de entrada sempre 
			/// precedem os índices de textura LUT.
			/// </summary>
			/// <param name="Param_IndexTextura">O índice para definir a textura do recurso.</param>
			/// <param name="Param_ResourceTexture">O objeto de textura de recurso para definir no índice de textura do sombreador.</param>
			CarenResult SetResourceTexture(
				UInt32 Param_IndexTextura,
				ICarenD2D1ResourceTexture^ Param_ResourceTexture);
		};

		/// <summary>
		/// (ID2D1ComputeTransform) - Interface responsável por definir uma transformação que usa um sombreador de computação.
		/// A transformação implementa os métodos normais de Shatzis implementando ID2D1Transform. Além disso, o chamador recebe um ID2D1ComputeInfo para descrever a passagem de 
		/// computação que a transformação deve executar.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("6E992381-1C56-4EDB-A38C-280E7FBF0EA9")]
		public interface class ICarenD2D1ComputeTransform : ICarenD2D1Transform
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Este método permite que uma transformação baseada em sombreamento de computação selecione o número de grupos de segmentos para executar com base no número de pixels
			/// de saída que ele precisa preencher. Se essa chamada falhar, a instância ICarenD2D1Effect correspondente é colocada em um estado de erro e falha ao desenhar.
			/// </summary>
			/// <param name="Param_OutputRect">O retângulo de saída que será preenchido pela transformação computacional.</param>
			/// <param name="Param_Out_DimensaoX">O número de threads na dimensão X.</param>
			/// <param name="Param_Out_DimensaoY">O número de threads na dimensão Y.</param>
			/// <param name="Param_Out_DimensaoZ">O número de threads na dimensão Z.</param>
			CarenResult CalculateThreadgroups(
				CA_D2D1_RECT_L^ Param_OutputRect,
				[Out] UInt32% Param_Out_DimensaoX,
				[Out] UInt32% Param_Out_DimensaoY,
				[Out] UInt32% Param_Out_DimensaoZ);

			/// <summary>
			/// Define as informações de renderização usadas para especificar o pass de sombreador de computação.
			// Se esse método falhar, o ICarenD2D1TransformGraph::AddNode falhará.
			/// </summary>
			/// <param name="Param_ComputeInfo">O objeto de informação de renderização a ser definido.</param>
			CarenResult SetComputeInfo(ICarenD2D1ComputeInfo^ Param_ComputeInfo);
		};

		/// <summary>
		/// (ID2D1PrintControl) - Interface responsável por converter primitivos Direct2D armazenados em um ICarenD2D1CommandList em uma representação de página fixa. O subsistema de 
		/// impressão então consome os primitivos.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("B3DAAD3C-DCBA-4A0E-82B7-6811B8CABA9F")]
		public interface class ICarenD2D1PrintControl : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Converte primitivos Direct2D na lista de comandos passados em uma representação de página fixa para uso pelo subsistema de impressão. 
			/// </summary>
			/// <param name="Param_ListaComandos">A lista de comando que contém as operações de renderização.</param>
			/// <param name="Param_SizePagina">O tamanho da página para adicionar.</param>
			/// <param name="Param_PagePrintTicketStream">O fluxo de ingressos impressos.</param>
			/// <param name="Param_Out_Tag1">Quando retorna, contém o primeiro rótulo para operações de desenho subsequentes.</param>
			/// <param name="Param_Out_Tag2">Quando retorna, contém o segundo rótulo para operações de desenho subsequentes.</param>
			CarenResult AddPage(
				ICarenD2D1CommandList^ Param_ListaComandos,
				CA_D2D1_SIZE_F^ Param_SizePagina,
				ICarenStream^ Param_PagePrintTicketStream,
				[Out] UInt64% Param_Out_Tag1,
				[Out] UInt64% Param_Out_Tag2);

			/// <summary>
			/// Passa todos os recursos restantes para o subsistema de impressão e, em seguida, limpa e fecha o trabalho de impressão atual. 
			/// </summary>
			CarenResult Close();
		};

		/// <summary>
		/// (ID2D1Properties) - Interface responsável por representar um conjunto de propriedades vinculáveis e desacionáveis de tempo de execução que permitem que um aplicativo 
		/// orientado a dados modifique o estado de um efeito Direct2D. Esta interface suporta acesso através de índices ou nomes de propriedades. Além de propriedades de alto nível, cada propriedade 
		/// em um objeto ICarenD2D1Properties pode conter um objeto ICarenD2D1Properties, que armazena metadados descrevendo a propriedade pai.
		/// Está expõe um conjunto de propriedades vinculáveis e desapropriedade de tempo de execução que permitem que um aplicativo baseado em dados, como uma ferramenta de autoria de gráfico de 
		/// efeito ou um sistema de animação, modifique o estado de um efeito Direct2D.
		/// Os métodos que contém templates são mapeados para os genericos do Enum > CA_D2D1_MAPA_TIPOS_TEMPLATE
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("0DC04B4A-5B3E-4259-96C3-C0F3DC6E6846")]
		public interface class ICarenD2D1Properties : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o número de propriedades de alto nível. 
			/// </summary>
			/// <param name="Param_Out_Quantidade"> retorna o número de propriedades personalizadas (não-sistema) que podem ser acessadas pelo objeto.</param>
			void GetPropertyCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Obtém o índice correspondente ao nome da propriedade dada.
			/// Se a propriedade não existe, então esse método retorna D2D1_INVALID_PROPERTY_INDEX. Esse valor reservado nunca irá mapear para um índice válido, e fará com 
			/// que os valores NULO ou sentinela sejam devolvidos 
			/// de outras partes da interface da propriedade.
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para recuperar.</param>
			/// <param name="Param_Out_Index">Retorna o índice do nome da propriedade correspondente.</param>
			void GetPropertyIndex(
				String^ Param_NomePropriedade,
				[Out] UInt32% Param_Out_Index);

			/// <summary>
			/// Obtém o nome da propriedade que corresponde ao índice dado.
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade para a qual o nome está sendo devolvido.</param>
			/// <param name="Param_Out_Nome">Quando este método retorna, contém o nome que está sendo recuperado.</param>
			/// <param name="Param_SizeNome">O número de caracteres no (Param_Out_Nome).</param>
			CarenResult GetPropertyName(
				UInt32 Param_Index,
				[Out] String^% Param_Out_Nome,
				UInt32 Param_SizeNome);

			/// <summary>
			/// Obtém o número de caracteres para o nome da propriedade dado. 
			/// </summary>
			/// <param name="Param_Index">O índice do nome da propriedade para recuperar.</param>
			/// <param name="Param_Out_SizeNome">Retorna o tamanho em caracteres do nome correspondente ao índice de propriedade dado, ou zero se o índice de propriedade não existir.</param>
			void GetPropertyNameLength(
				UInt32 Param_Index,
				[Out] UInt32% Param_Out_SizeNome);

			/// <summary>
			/// Obtém as sub propriedades da propriedade fornecida por índice. 
			/// </summary>
			/// <param name="Param_Index">O índice das sub propriedades a serem recuperadas.</param>
			/// <param name="Param_Out_SubPropriedades">Quando este método retorna, contém um ponteiro para as subpropriedades na interface (ICarenD2D1Properties).</param>
			CarenResult GetSubProperties(
				UInt32 Param_Index,
				[Out] ICarenD2D1Properties^% Param_Out_SubPropriedades);

			/// <summary>
			/// Obtém a D2D1_PROPERTY_TYPE da propriedade selecionada. 
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade para o qual o tipo será recuperado.</param>
			/// <param name="Param_Out_Tipo">Retorna um enum(CA_D2D1_PROPERTY_TYPE) para o tipo da propriedade.</param>
			void GetType(
				UInt32 Param_Index,
				[Out] CA_D2D1_PROPERTY_TYPE% Param_Out_Tipo);

			/// <summary>
			/// Obtém o valor da propriedade especificada por índice. 
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
			/// <param name="Param_Tipo">TBD</param>
			/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
			CarenResult GetValue(
				UInt32 Param_Index,
				CA_D2D1_PROPERTY_TYPE Param_Tipo,
				[Out] ICarenBuffer^% Param_Out_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Obtém o valor da propriedade especificada por índice.
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
			/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
			CarenResult GetValue(
				UInt32 Param_Index,
				[Out] ICarenBuffer^% Param_Out_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Obtém o valor da propriedade pelo nome.
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
			/// <param name="Param_Tipo">TBD</param>
			/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
			CarenResult GetValueByName(
				String^ Param_NomePropriedade,
				CA_D2D1_PROPERTY_TYPE Param_Tipo,
				[Out] ICarenBuffer^% Param_Out_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Obtém o valor da propriedade pelo nome.
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
			/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
			CarenResult GetValueByName(
				String^ Param_NomePropriedade,
				[Out] ICarenBuffer^% Param_Out_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Obtém o tamanho do valor da propriedade em bytes, usando o índice de propriedade. 
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade.</param>
			/// <param name="Param_Out_Size">Retorna o tamanho do valor em bytes, usando o índice de propriedade</param>
			void GetValueSize(
				UInt32 Param_Index,
				[Out] UInt32% Param_Out_Size);

			/// <summary>
			/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
			/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade para definir.</param>
			/// <param name="Param_Tipo">TBD</param>
			/// <param name="Param_Buffer">Os dados a serem definidos.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
			CarenResult SetValue(
				UInt32 Param_Index,
				CA_D2D1_PROPERTY_TYPE Param_Tipo,
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
			/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
			/// </summary>
			/// <param name="Param_Index">O índice da propriedade para definir.</param>
			/// <param name="Param_Buffer">Os dados a serem definidos.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
			CarenResult SetValue(
				UInt32 Param_Index,
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Define a propriedade nomeada ao valor dado. 
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
			/// <param name="Param_Tipo">TBD</param>
			/// <param name="Param_Buffer">Os dados a serem definidos.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
			CarenResult SetValueByName(
				String^ Param_NomePropriedade,
				CA_D2D1_PROPERTY_TYPE Param_Tipo,
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Define a propriedade nomeada ao valor dado. 
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
			/// <param name="Param_Buffer">Os dados a serem definidos.</param>
			/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
			CarenResult SetValueByName(
				String^ Param_NomePropriedade,
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);
			
			/// <summary>
			/// (Templete - SetValueByName(PCWSTR,T)) - Define a propriedade nomeada ao valor dado. Esta é uma sobrecarga de modelo. 
			/// </summary>
			/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
			/// <param name="Param_Valor">Os dados a serem definidos. Como o método converte os dados para um BYTE*, não a necessidade de um ICaren.</param>
			CarenResult SetValueByName(
				String^ Param_NomePropriedade,
				ICarenBuffer^ Param_Valor);
		};

		/// <summary>
		/// (ID2D1Effect) - Interface responsável por representar um construtor básico de processamento de imagem no Direct2D.
		/// Um efeito leva zero ou mais imagens de entrada, e tem uma imagem de saída. As imagens que são entradas e saídas de um efeito são preguiçosamente avaliadas. 
		/// Essa definição é suficiente para permitir que um gráfico arbitrário de efeitos seja criado a partir do aplicativo, alimentando imagens de saída na imagem de entrada do próximo efeito na cadeia.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("FAFD259D-26C1-4C39-9F42-3D54A14F3A6F")]
		public interface class ICarenD2D1Effect : ICarenD2D1Properties
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a imagem de entrada dada por índice. 
			/// </summary>
			/// <param name="Param_Index">O índice da imagem para recuperar.</param>
			/// <param name="Param_Out_Entrada">Quando este método retorna, contém o endereço de um ponteiro para a imagem identificada pelo (Param_Index).</param>
			void GetInput(
				UInt32 Param_Index,
				[Out] ICarenD2D1Image^% Param_Out_Entrada);

			/// <summary>
			/// Obtém o número de entradas para o efeito. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de entradas ao efeito.</param>
			void GetInputCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Obtém a imagem de saída do efeito. 
			/// A imagem de saída pode ser definida como uma entrada para outro efeito, ou pode ser transmitida diretamente para o ICarenD2D1DeviceContext, a fim de tornar o efeito.
			/// Também é possível usar o (ICaren::ConsultarInterface) para recuperar a mesma imagem de saída.
			/// </summary>
			/// <param name="Param_Out_SaidaImagem">Quando este método retorna, contém o endereço de um ponteiro para a imagem de saída para o efeito.</param>
			void GetOutput([Out] ICarenD2D1Image^% Param_Out_SaidaImagem);

			/// <summary>
			/// Define a imagem de entrada dada por índice. 
			/// Se o índice de entrada estiver fora de alcance, a imagem de entrada será ignorada.
			/// </summary>
			/// <param name="Param_Index">O índice da imagem a definir.</param>
			/// <param name="Param_Entrada">A imagem de entrada a ser definida.</param>
			/// <param name="Param_Invalidar">Se invalidar o gráfico na localização da entrada de efeito</param>
			void SetInput(
				UInt32 Param_Index,
				ICarenD2D1Image^ Param_Entrada,
				Boolean Param_Invalidar);

			/// <summary>
			/// Permite que o aplicativo altere o número de entradas para um efeito. 
			/// A maioria dos efeitos não suporta um número variável de entradas. Use ICarenD2D1Properties::GetValue com os valores D2D1_PROPERTY_MIN_INPUTS e D2D1_PROPERTY_MAX_INPUTS
			/// para determinar o número de entradas suportadas por um efeito.
			/// Se o método falhar, a contagem de entrada e entrada existente permanecerá inalterada.
			/// </summary>
			/// <param name="Param_Quantidade">O número de entradas para o efeito.</param>
			CarenResult SetInputCount(UInt32 Param_Quantidade);

			/// <summary>
			/// Define o efeito de entrada dado por índice. 
			/// Este método obtém a saída do efeito dado e, em seguida, passa a imagem de saída para o método SetInput.
			/// </summary>
			/// <param name="Param_Index">O índice da entrada para definir.</param>
			/// <param name="Param_EfeitoEntrada">O efeito de entrada a ser definido.</param>
			/// <param name="Param_Invalidar">Se invalidar o gráfico na localização da entrada de efeito</param>
			void SetInputEffect(
				UInt32 Param_Index,
				ICarenD2D1Effect^ Param_EfeitoEntrada,
				Boolean Param_Invalidar);
		};
		
		/// <summary>
		/// (ID2D1VertexBuffer) - Interface responsável por definir um buffer de vértice unidimensional mapeável.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("72360B6E-708D-45E7-8E1D-6A6740CD01F0")]
		public interface class ICarenD2D1VertexBuffer : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Mapeia os dados fornecidos na memória do usuário. 
			/// Se os dados forem maiores que (Param_BufferSize), este método falhará.
			/// </summary>
			/// <param name="Param_Out_BufferData">Quando este método retorna, contém o endereço de um ponteiro para o buffer disponível.</param>
			/// <param name="Param_BufferSize">O tamanho desejado do buffer.</param>
			CarenResult Map(
				[Out] ICarenBuffer^% Param_Out_BufferData,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Desmapeia os dados do buffer anterormente mapeados na chamada (Map).
			/// </summary>
			CarenResult Unmap();
		};

		/// <summary>
		/// (ID2D1DrawInfo) - Interface responsável por descrever um passe de renderização de GPU em um vértice ou sombreador de pixels. É passado para ICarenD2D1DrawTransform.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("4F2C7757-1B04-4175-8EA5-2D60E4BBC8E1")]
		public interface class ICarenD2D1DrawInfo : ICarenD2D1RenderInfo
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Defina as instruções do sombreador para esta transformação. 
			/// </summary>
			/// <param name="Param_ShaderId">O ID de recurso para o sombreador.</param>
			/// <param name="Param_PixelOptions">Informações adicionais fornecidas ao renderizador para indicar as operações que o sombreador de pixel faz.</param>
			CarenResult SetPixelShader(
				String^ Param_ShaderId,
				CA_D2D1_PIXEL_OPTIONS Param_PixelOptions);

			/// <summary>
			/// Define o buffer constante para o sombreador de pixels desta transformação. 
			/// </summary>
			/// <param name="Param_Buffer">Os dados aplicados ao buffer constante.</param>
			/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante</param>
			CarenResult SetPixelShaderConstantBuffer(
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);

			/// <summary>
			/// Define a textura do recurso correspondente ao índice de textura do sombreador dado. 
			/// </summary>
			/// <param name="Param_IndexTextura">O índice da textura está ligado ao sombreador de pixels.</param>
			/// <param name="Param_ResourceTexture">A textura de recursos criado.</param>
			CarenResult SetResourceTexture(
				UInt32 Param_IndexTextura,
				ICarenD2D1ResourceTexture^ Param_ResourceTexture);

			/// <summary>
			/// Define um buffer de vértice, um sombreador de vértice correspondente e opções para controlar como os vértices devem ser manuseados pelo contexto Direct2D. 
			/// Os sombreadores de vértice associados ao buffer de vértice através do sombreador de vértice GUID devem ter sido carregados através do método ICarenD2D1EffectContext::LoadVertexShader 
			/// antes que esta chamada seja feita.
			/// Se esta chamada falhar, a instância ICarenD2D1Effect correspondente será colocada em um estado de erro e falha ao desenhar.
			/// </summary>
			/// <param name="Param_VertexBuffer">O buffer de vértice, se isso for limpo, será usado o sombreador de vértice padrão e o mapeamento para os retângulos de transformação.</param>
			/// <param name="Param_VertexOptions">Opções que influenciam como o renderizador interagirá com o sombreador de vértice.</param>
			/// <param name="Param_DescricaoBlend">Como os vértices serão misturados com a textura de saída.</param>
			/// <param name="Param_VertexRange">O conjunto de vértices para usar a partir do buffer.</param>
			/// <param name="Param_GuidVertexShader">O GUID do sombreador de vértice.</param>
			CarenResult SetVertexProcessing(
				ICarenD2D1VertexBuffer^ Param_VertexBuffer,
				CA_D2D1_VERTEX_OPTIONS Param_VertexOptions,
				CA_D2D1_BLEND_DESCRIPTION^ Param_DescricaoBlend,
				CA_D2D1_VERTEX_RANGE^ Param_VertexRange,
				String^ Param_GuidVertexShader);

			/// <summary>
			/// Define o buffer constante para o sombreador de vértice desta transformação. 
			/// </summary>
			/// <param name="Param_Buffer">Os dados aplicados ao buffer constante</param>
			/// <param name="Param_BufferSize">O número de bytes de dados no buffer constante.</param>
			CarenResult SetVertexShaderConstantBuffer(
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_BufferSize);
		};

		/// <summary>
		/// (ID2D1DrawTransform) - Interface responsável por Uma implementação especializada dos cálculos de Shantzis para uma transformação implementada na GPU. Esses cálculos são 
		/// descritos no artigo <a href="https://dl.acm.org/doi/10.1145/192161.192191">Um modelo para computação de imagem eficiente e flexível</a>.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("554A7480-9AD5-4F16-AE5F-AD4487EDC0F3")]
		public interface class ICarenD2D1DrawTransform : ICarenD2D1Transform
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Fornece a interface de informações de renderização GPU para a implementação da transformação.
			/// A transformação pode manter uma referência a esta interface para sua vida útil. Se alguma alteração de propriedades na transformação, ela poderá aplicar essas 
			/// alterações na interface (Param_DrawInfo) correspondente.
			/// Isso também é usado para determinar que os nós correspondentes no gráfico estão sujos.
			/// </summary>
			/// <param name="Param_DrawInfo">A interface é fornecida de volta ao método de chamada para permitir a especificação do passe de transformação baseado em GPU.</param>
			CarenResult SetDrawInfo(ICarenD2D1DrawInfo^ Param_DrawInfo);
		};

		/// <summary>
		/// (ID2D1OffsetTransform) - Interface responsável por instruir o sistema de renderização de efeitos para compensar um bitmap de entrada sem inserir um passe de renderização.
		/// Como um passe de renderização não é necessário, a interface deriva de um nó de transformação. Isso permite que ele seja inserido em um gráfico, mas não permite que um 
		/// buffer de saída seja especificado.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("7F704B30-298E-4532-82EB-97F39F4FAE01")]
		public interface class ICarenD2D1OffsetTransform : ICarenD2D1TransformNode
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém o deslocamento atualmente na transformação de deslocamento. 
			/// </summary>
			/// <param name="Param_Out_Offset">Retorna o deslocamento da transformação atual.</param>
			void GetOffset([Out] CA_D2D1_POINT_2L^% Param_Out_Offset);

			/// <summary>
			/// Define o deslocamento na transformação de deslocamento atual. 
			/// </summary>
			/// <param name="Param_Offset">A estrutura para definir o deslocamento da transformação atual.</param>
			void SetOffset(CA_D2D1_POINT_2L^ Param_Offset);
		};

		/// <summary>
		/// (ID2D1TransformGraph) - Interface responsável por representar um gráfico de nós de transformação.
		/// Essa interface permite que um gráfico de nós de transformação seja especificado. Essa interface é passada para ICarenD2D1EffectImpl::Initialize para permitir que uma 
		/// implementação de efeito especifique um gráfico de transformações ou uma única transformação.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("70858B8C-08E6-488E-9333-F2918FD0B49A")]
		public interface class ICarenD2D1TransformGraph : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Adiciona o nó fornecido ao gráfico de transformação.
			/// Um nó deve ser adicionado ao gráfico de transformação antes que ele possa ser interligado de qualquer forma.
			/// Um gráfico de transformação não pode ser adicionado diretamente a outro gráfico de transformação. Somente interfaces derivadas do ICarenD2D1TransformNode podem 
			/// ser adicionadas ao gráfico de transformação.
			/// </summary>
			/// <param name="Param_Node">O nó que será adicionado ao gráfico de transformação.</param>
			CarenResult AddNode(ICarenD2D1TransformNode^ Param_Node);

			/// <summary>
			/// Limpa os nós de transformação e todas as conexões do gráfico de transformação. 
			/// </summary>
			void Clear();

			/// <summary>
			/// Conecta dois nós dentro do gráfico de transformação. Ambos os nós já devem existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
			/// </summary>
			/// <param name="Param_FromNode">O nó a partir do qual a conexão será feita.</param>
			/// <param name="Param_ToNode">O nó para o qual a conexão será feita.</param>
			/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
			CarenResult ConnectNode(
				ICarenD2D1TransformNode^ Param_FromNode,
				ICarenD2D1TransformNode^ Param_ToNode,
				UInt32 Param_ToNodeInputIndex);

			/// <summary>
			/// Conecta um nó de transformação dentro do gráfico à entrada de efeito correspondente do efeito encapsulamento. 
			/// </summary>
			/// <param name="Param_ToEffectInputIndex">A entrada de efeito à qual o nó de transformação será vinculado.</param>
			/// <param name="Param_Node">O nó para o qual a conexão será feita.</param>
			/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
			CarenResult ConnectToEffectInput(
				UInt32 Param_ToEffectInputIndex,
				ICarenD2D1TransformNode^ Param_Node,
				UInt32 Param_ToNodeInputIndex);

			/// <summary>
			/// Retorna o número de entradas ao gráfico de transformação. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este gráfico de transformação.</param>
			void GetInputCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Remove o nó fornecido do gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
			/// Quaisquer conexões com este nó serão removidas quando o nó for removido. Depois que o nó é removido, ele não pode ser usado pela interface até que tenha sido 
			/// adicionado ao gráfico por AddNode.
			/// </summary>
			/// <param name="Param_Node">O nó que será removido do gráfico de transformação.</param>
			CarenResult RemoveNode(ICarenD2D1TransformNode^ Param_Node);

			/// <summary>
			/// Define o nó de saída para o gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
			/// </summary>
			/// <param name="Param_Node">O nó que será considerado a saída do nó de transformação.</param>
			CarenResult SetOutputNode(ICarenD2D1TransformNode^ Param_Node);

			/// <summary>
			/// Usa a entrada especificada como saída de efeito. 
			/// </summary>
			/// <param name="Param_EffectInputIndex">O índice da entrada para o efeito.</param>
			CarenResult SetPassthroughGraph(UInt32 Param_EffectInputIndex);

			/// <summary>
			/// Define um único nó de transformação como sendo equivalente a todo o gráfico. 
			/// Isso equivale a chamar ICarenD2D1TransformGraph::Clear, adicionar um único nó, conectar todas as entradas de nó às entradas de efeito em ordem e definir a 
			/// transformação não como saída de gráfico.
			/// </summary>
			/// <param name="Param_Node">O nó a ser definido.</param>
			CarenResult SetSingleTransformNode(ICarenD2D1TransformNode^ Param_Node);
		};

		/// <summary>
		/// (ID2D1LookupTable3D) - Interface responsável por um contêiner para dados de tabela de pesquisa 3D que podem ser passados para o efeito LookupTable3D.
		/// Uma instância ICarenD2DLookupTable3D é criada usando ICarenD2D1DeviceContext2::CreateLookupTable3D ou ICarenD2D1EffectContext1::CreateLookupTable3D.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("ECBAD1DF-F112-45CB-BDEB-93EC4C8D1A1A")]
		public interface class ICarenD2D1LookupTable3D : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Essa interface não possui métodos proprios.
		};
		
		/// <summary>
		/// (ID2D1EffectContext) - Interface responsável por fornecer métodos de fábrica e outro gerenciamento de estado para efetuar e transformar autores.
		/// Essa interface é passada para uma implementação de efeito por meio do método ICarenD2D1EffectImpl::Initialize. Para impedir que os aplicativos obtenham acesso casual a essa
		/// interface e separar as contagens de referência entre as interfaces pública e privada, não é possível chamar (ConsultarInterface) entre o ICarenD2D1DeviceContext e o ICarenD2D1EffectContext.
		/// Cada chamada para ICarenD2D1Effect::Initialize receberá uma interface ICarenD2D1EffectContext diferente. Essa interface controla alocações de recursos para o efeito. Quando o 
		/// efeito é liberado, as alocações correspondentes também serão liberadas.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("1C2850BE-940A-465D-B22C-4DC2EE1F23B2")]
		public interface class ICarenD2D1EffectContext : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Verifica se um recurso opcional é suportado pelo dispositivo D3D.
			/// </summary>
			/// <param name="Param_Feature">O recurso para consultar suporte.</param>
			/// <param name="Param_Out_FeatureSupportData">Uma estrutura indicando informações sobre como ou se o recurso é suportado.</param>
			/// <param name="Param_SizeFeatureData">O tamanho do parâmetro (Param_Out_FeatureSupportData).</param>
			CarenResult CheckFeatureSupport(
				CA_D2D1_FEATURE Param_Feature,
				[Out] ICaren^% Param_Out_FeatureSupportData,
				UInt32 Param_SizeFeatureData);

			/// <summary>
			/// Cria uma mistura que pode ser inserida em um gráfico de transformação. 
			/// </summary>
			/// <param name="Param_NumeroEntradas">O número de entradas na transformação de mistura.</param>
			/// <param name="Param_DescBlend">Descreve a transformação de mistura que deve ser criada.</param>
			/// <param name="Param_Out_BlendTransform">Retorna uma interface para a transformação da mistura(blend).</param>
			CarenResult CreateBlendTransform(
				UInt32 Param_NumeroEntradas,
				CA_D2D1_BLEND_DESCRIPTION^ Param_DescBlend,
				[Out] ICarenD2D1BlendTransform^% Param_Out_BlendTransform);

			/// <summary>
			/// Cria uma transformação que estende sua entrada infinitamente em todas as direções, com base na passada no modo de extensão.
			/// </summary>
			/// <param name="Param_ExtendModeX">O modo de extensão na direção do eixo X.</param>
			/// <param name="Param_ExtendModeY">O modo de extensão na direção do eixo Y.</param>
			/// <param name="Param_Out_BorderTransform">Retorna uma interface para a transformação devolvida.</param>
			CarenResult CreateBorderTransform(
				CA_D2D1_EXTEND_MODE Param_ExtendModeX,
				CA_D2D1_EXTEND_MODE Param_ExtendModeY,
				[Out] ICarenD2D1BorderTransform^% Param_Out_BorderTransform);

			/// <summary>
			/// Cria e retorna uma transformação de ajuste de limites. Uma transformação de suporte pode ser usada por duas razões diferentes:
			/// Para indicar que uma região de sua imagem de entrada já é preto transparente. Isso pode aumentar a eficiência para renderizar bitmaps ou Para aumentar o tamanho da imagem 
			/// de entrada. A área expandida será tratada como preta transparente
			/// </summary>
			/// <param name="Param_RetanguloSaida">O retângulo de saída inicial para a transformação de ajuste dos limites.</param>
			/// <param name="Param_Out_Transform">Retorna um ponteiro para a interface de ajuste dos limites da transformação.</param>
			CarenResult CreateBoundsAdjustmentTransform(
				CA_D2D1_RECT_L^ Param_RetanguloSaida,
				[Out] ICarenD2D1BoundsAdjustmentTransform^% Param_Out_Transform);

			/// <summary>
			/// Cria um contexto de cores a partir de um espaço de cores. Se o espaço de cor for Personalizado, o contexto será inicializado a partir dos parâmetros (Param_Profile) e 
			/// (Param_SizeProfileBuffer). 
			/// Se o espaço de cor não for Personalizado, o contexto é inicializado com os bytes de perfil associados ao espaço de cor. Os parâmetros de (Param_Profile) e 
			/// (Param_SizeProfileBuffer) são ignorados.
			/// </summary>
			/// <param name="Param_EspacoCor">O espaço do contexto de cores para criar.</param>
			/// <param name="Param_Profile">Um buffer contendo os bytes de perfil ICC usados para inicializar o contexto de cor quando o espaço é D2D1_COLOR_SPACE_CUSTOM. Para outros tipos, 
			/// o parâmetro é ignorado e deve ser definido como NULO.</param>
			/// <param name="Param_SizeProfileBuffer">O tamanho em bytes de (Param_Profile).</param>
			/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
			CarenResult CreateColorContext(
				CA_D2D1_COLOR_SPACE Param_EspacoCor,
				ICarenBuffer^ Param_Profile,
				UInt32 Param_SizeProfileBuffer,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um contexto de cor carregando-o a partir do nome de arquivo especificado. Os bytes de perfil são o conteúdo do arquivo especificado pelo (Param_UrlFilename). 
			/// </summary>
			/// <param name="Param_UrlFilename">O caminho para o arquivo contendo os bytes de perfil para inicializar o contexto de cores.</param>
			/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
			CarenResult CreateColorContextFromFilename(
				String^ Param_UrlFilename,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um contexto de cores a partir de um ICarenWICColorContext. O espaço D2D1ColorContext do contexto resultante varia.
			/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado 
			/// para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
			/// </summary>
			/// <param name="Param_WicColorContext">Um (ICarenWICColorContext) para inicializar o contexto de cores.</param>
			/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
			CarenResult CreateColorContextFromWicColorContext(
				ICaren^ Param_WicColorContext,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um efeito Direct2D para o ID de classe especificado. Isso é o mesmo que ICarenD2D1DeviceContext::CreateEffect para que os efeitos personalizados possam criar outros efeitos
			/// e envolvê-los em uma transformação. 
			/// O efeito criado não faz referência à contagem do DLL a partir do qual o efeito foi criado. Se o chamador não recarregar um efeito enquanto esse efeito estiver carregado, o comportamento
			/// resultante será imprevisível.
			/// </summary>
			/// <param name="Param_IdEfeito">O ID de efeito embutido ou registrado para criar o efeito. Consulte os GUIDs de efeitos do Direct2D para obter um ID para este parametro.</param>
			/// <param name="Param_Out_Efeito">Retorna um ponteiro para a interface(ICarenD2D1Effect) do efeito especificado.</param>
			CarenResult CreateEffect(
				String^ Param_IdEfeito,
				[Out] ICarenD2D1Effect^% Param_Out_Efeito);

			/// <summary>
			/// Cria e devolve uma transformação Offset.
			/// Uma transformação offset é usada para compensar um bitmap de entrada sem ter que inserir um passe de renderização. Uma transformação offset é automaticamente inserida por 
			/// uma transformação Affine se a transformação for avaliada em uma transformação alinhada a pixels.
			/// </summary>
			/// <param name="Param_Offset">O valor de deslocamento.</param>
			/// <param name="Param_Out_Transform">Retorna um ponteiro da interface(ICarenD2D1OffsetTransform) para um objeto de transformação Offset.</param>
			CarenResult CreateOffsetTransform(
				CA_D2D1_POINT_2L^ Param_Offset,
				[Out] ICarenD2D1OffsetTransform^% Param_Out_Transform);

			/// <summary>
			/// Cria ou encontra a textura do recurso dada, dependendo se um id de recurso é especificado. Também inicializa opcionalmente a textura com os dados especificados. 
			/// </summary>
			/// <param name="Param_IdRecurso">Um GUID opcional para o ID exclusivo que identifica a Lookup Table.</param>
			/// <param name="Param_PropsRecursoTextura">As propriedades usadas para criar a textura do recurso.</param>
			/// <param name="Param_Dados">Os dados opcionais a serem carregados na textura do recurso.</param>
			/// <param name="Param_Strides">Um array de strides para avançar através da textura do recurso, de acordo com a dimensão.</param>
			/// <param name="Param_SizeDados">O tamanho, em bytes, dos dados.</param>
			/// <param name="Param_Out_RecursoTextura">Retorna um ponteiro para a interface(ICarenD2D1ResourceTexture) da textura devolvida para ser usada como recurso ou efeito pelo Direct2D. </param>
			CarenResult CreateResourceTexture(
				String^ Param_IdRecurso,
				CA_D2D1_RESOURCE_TEXTURE_PROPERTIES^ Param_PropsRecursoTextura,
				ICarenBuffer^ Param_Dados,
				cli::array<UInt32>^ Param_Strides,
				UInt32 Param_SizeDados,
				[Out] ICarenD2D1ResourceTexture^% Param_Out_RecursoTextura);

			/// <summary>
			/// Embrulha um gráfico de efeito em um único nó de transformação e, em seguida, inserido em um gráfico de transformação. Isso permite um efeito para agregar outros efeitos. 
			/// Isso normalmente será feito para permitir que as propriedades de efeito sejam ree expressas com um contrato diferente, ou para permitir que diferentes componentes integrem 
			/// os efeitos uns dos outros. 
			/// </summary>
			/// <param name="Param_Efeito">O efeito a ser embrulhado em um nó de transformação.</param>
			/// <param name="Param_Out_TransformNode">Retorna um ponteiro para a interface(ICarenD2D1TransformNode) do nó de transformação que encapsulao gráficode efeito. </param>
			CarenResult CreateTransformNodeFromEffect(
				ICarenD2D1Effect^ Param_Efeito,
				[Out] ICarenD2D1TransformNode^% Param_Out_TransformNode);

			/// <summary>
			/// Cria um buffer de vértice ou encontra um buffer de vértice padrão e, opcionalmente, inicializa-o com vértices. O buffer retornado pode ser especificado nas 
			/// informações de renderização para especificar tanto um sombreador de vértice quanto ou passar vértices personalizados para o sombreador de vértice padrão usado pelo Direct2D. 
			/// </summary>
			/// <param name="Param_PropsVertexBuffer">As propriedades usadas para descrever o amortecedor de vértice e o sombreador de vértices.</param>
			/// <param name="Param_IdRecurso">A identificação única que identifica o buffer de vértice.</param>
			/// <param name="Param_PropsCustomVertexBuffer">As propriedades usadas para definir um buffer de vértice personalizado. Se você usar um sombreador de vértice embutido, 
			/// você não precisa especificar esta propriedade.</param>
			/// <param name="Param_Out_VertexBuffer">Retorna um ponteiro para a interface(ICarenD2D1VertexBuffer) do buffer de vertices devolvido.</param>
			CarenResult CreateVertexBuffer(
				CA_D2D1_VERTEX_BUFFER_PROPERTIES^ Param_PropsVertexBuffer,
				String^ Param_IdRecurso,
				CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES^ Param_PropsCustomVertexBuffer,
				[Out] ICarenD2D1VertexBuffer^% Param_Out_VertexBuffer);

			/// <summary>
			/// Encontra a textura de recurso dada se ela já foi criada com ICarenD2D1EffectContext::CreateResourceTexture com o mesmo GUID.
			/// </summary>
			/// <param name="Param_IdRecurso">A identificação única que identifica a textura do recurso.</param>
			/// <param name="Param_Out_RecursoTextura">Retorna um ponteiro para a interface(ICarenD2D1ResourceTexture) da textura devolvida que pode ser usada como recurso 
			/// ou em um efeito Direct2D.</param>
			CarenResult FindResourceTexture(
				String^ Param_IdRecurso,
				[Out] ICarenD2D1ResourceTexture^% Param_Out_RecursoTextura);

			/// <summary>
			/// Encontra o buffer de vértice dado se ele já foi criado com ICarenD2D1EffectContext::CreateVertexBuffer com o mesmo GUID. 
			/// </summary>
			/// <param name="Param_IdRecurso">A identificação única que identifica o buffer de vértice.</param>
			/// <param name="Param_Out_VertexBuffer">Retorna um ponteiro para a interface(ICarenD2D1VertexBuffer) do buffer de vértice devolvido que pode ser usado como recurso 
			/// em um efeito Direct2D.</param>
			CarenResult FindVertexBuffer(
				String^ Param_IdRecurso,
				[Out] ICarenD2D1VertexBuffer^% Param_Out_VertexBuffer);

			/// <summary>
			/// Obtém o mapeamento da unidade que um efeito usará para propriedades que podem estar em pontos por polegada (Dpi) ou pixels.
			/// Se o D2D1_UNIT_MODE for D2D1_UNIT_MODE_PIXELS, tanto o DPI_X quanto o DPI_Y serão definidos como 96.
			/// </summary>
			/// <param name="Param_Out_DpiX">O DPI no eixo X.</param>
			/// <param name="Param_Out_DpiY">O DPI no eixo Y.</param>
			void GetDpi(
				[Out] float% Param_Out_DpiX,
				[Out] float% Param_Out_DpiY);

			/// <summary>
			/// Isso indica o nível máximo de recurso da lista fornecida que é suportada pelo dispositivo. Se nenhum dos níveis fornecidos for suportado, então esta API falhará com 
			/// D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES. 
			/// </summary>
			/// <param name="Param_NiveisRecurso">Os níveis de recurso fornecidos pelo aplicativo.</param>
			/// <param name="Param_QuantidadeNiveis">A contagem de níveis de recursos fornecidos pelo aplicativo</param>
			/// <param name="Param_Out_NivelRecursoMaximo">O nível máximo de recurso da lista (Param_NiveisRecurso), que é suportado pelo dispositivo D2D.</param>
			CarenResult GetMaximumSupportedFeatureLevel(
				cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso,
				UInt32 Param_QuantidadeNiveis,
				[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoMaximo);

			/// <summary>
			/// Indica se a precisão do buffer é suportada pelo dispositivo Direct2D subjacente.
			/// </summary>
			/// <param name="Param_BufferPrecision">A precisão do buffer para verificar.</param>
			/// <param name="Param_Out_Suporte">Retorna TRUE se a precisão do buffer for suportada. Retorna FALSE se a precisão do buffer não for suportada.</param>
			void IsBufferPrecisionSupported(
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				[Out] Boolean% Param_Out_Suporte);

			/// <summary>
			/// Realiza um teste para ver se o shader fornecido está carregado.
			/// </summary>
			/// <param name="Param_ShaderId">A identificação única que identifica o sombreador.</param>
			/// <param name="Param_Out_Loaded">Retorna TRUE se o shader tiver sido carregado. Retorna FALSE se o shader não está carregado.</param>
			void IsShaderLoaded(
				String^ Param_ShaderId,
				[Out] Boolean% Param_Out_Loaded);

			/// <summary>
			/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
			/// para JIT, se ainda não foi. O sombreador especificado deve ser compilado, não em código HLSL bruto.
			/// </summary>
			/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
			/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
			/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
			CarenResult LoadComputeShader(
				String^ Param_IdRecurso,
				ICarenBuffer^ Param_ShaderBuffer,
				UInt32 Param_ShaderBufferSize);

			/// <summary>
			/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
			/// para JIT, se ainda não foi.
			/// O sombreador especificado deve ser compilado, não em código HLSL bruto.
			/// </summary>
			/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
			/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
			/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
			CarenResult LoadPixelShader(
				String^ Param_IdRecurso,
				ICarenBuffer^ Param_ShaderBuffer,
				UInt32 Param_ShaderBufferSize);

			/// <summary>
			/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
			/// para JIT, se ainda não foi. 
			/// O sombreador especificado deve ser compilado, não em código HLSL bruto.
			/// </summary>
			/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
			/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
			/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
			CarenResult LoadVertexShader(
				String^ Param_IdRecurso,
				ICarenBuffer^ Param_ShaderBuffer,
				UInt32 Param_ShaderBufferSize);
		};

		/// <summary>
		/// (ID2D1EffectContext1) - Interface responsável por fornecer métodos de fábrica e outro gerenciamento de estado para efetuar e transformar autores.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F690F3BF-90F3-468E-8328-1AC00619FA23")]
		public interface class ICarenD2D1EffectContext1 : ICarenD2D1EffectContext
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria uma tabela de pesquisa 3D para mapear uma entrada de 3 canais para uma saída de 3 canais. Os dados da tabela devem ser fornecidos em formato de 4 canais. 
			/// </summary>
			/// <param name="Param_BufferPrecision">Precisão dos dados da tabela de pesquisa de entrada.</param>
			/// <param name="Param_Extents">Número de elementos de tabela de procuração por dimensão (X, Y, Z).</param>
			/// <param name="Param_Data">Buffer segurando os dados da tabela de pesquisa.</param>
			/// <param name="Param_DataSize">Tamanho do buffer de dados da tabela de pesquisa.</param>
			/// <param name="Param_Strides">Uma matriz contendo dois valores. O primeiro valor é o tamanho em bytes de uma linha (dimensão X) de dados LUT para a próxima. O segundo valor
			/// é o tamanho em bytes de um plano de dados LUT (dimensões X e Y) para o próximo.</param>
			/// <param name="Param_Out_LookupTable3D">Recebe um ponteiro para a interface(ICarenD2D1LookupTable3D) de tabela de procuração 3D. </param>
			CarenResult CreateLookupTable3D(
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				cli::array<UInt32>^ Param_Extents,
				ICarenBuffer^ Param_Data,
				UInt32 Param_DataSize,
				cli::array<UInt32>^ Param_Strides,
				[Out] ICarenD2D1LookupTable3D^% Param_Out_LookupTable3D);
		};

		/// <summary>
		/// (ID2D1EffectImpl) - Interface responsável por permitir que a interface e o comportamento de um efeito personalizado sejam especificados pelo autor do efeito.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("39FB7253-B646-4CA1-980A-215DB622D15C")]
		public interface class ICarenD2D1EffectImpl : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// O efeito pode usar este método para fazer tarefas de inicialização uma vez.
			/// Isso move o custo de criação de recursos para a chamada CreateEffect, em vez de durante a renderização.
			/// Se a implementação falhar nesta chamada, a chamada correspondente ICarenD2D1DeviceContext::CreateEffect também falhará.
			/// </summary>
			/// <param name="Param_ContextoEfeito">Uma interface de contexto interna que cria e retorna tipos centrados no autor de efeitos.</param>
			/// <param name="Param_TransformGraph">O efeito pode povoar o gráfico de transformação com uma topologia e pode atualizá-lo mais tarde.</param>
			CarenResult Initialize(
				ICarenD2D1EffectContext^ Param_ContextoEfeito,
				ICarenD2D1TransformGraph^ Param_TransformGraph);

			/// <summary>
			/// Prepara um efeito para o processo de renderização.
			/// Este método é chamado pelo renderizador quando o efeito está dentro de um gráfico de efeito que é desenhado.
			/// A maioria dos efeitos adia a criação de recursos ou a especificação de uma topologia até que esta chamada seja feita. Eles armazenam suas propriedades e mapeiam-nas 
			/// para um conjunto concreto de técnicas de renderização quando desenhadas pela primeira vez.
			/// </summary>
			/// <param name="Param_ChangeType">Indica o tipo de mudança que o efeito deve esperar.</param>
			CarenResult PrepareForRender(CA_D2D1_CHANGE_TYPE Param_ChangeType);

			/// <summary>
			/// O renderizador chama esse método para fornecer a implementação do efeito com uma maneira de especificar seu gráfico de transformação e transformar alterações de gráficos. 
			/// </summary>
			/// <param name="Param_TransformGraph">O gráfico para o qual o efeito descreve sua topologia de transformação através da chamada SetDescription.</param>
			CarenResult SetGraph(ICarenD2D1TransformGraph^ Param_TransformGraph);
		};

		/// <summary>
		/// (ID2D1PathGeometry) - Interface responsável por representar uma forma complexa que pode ser composta de arcos, curvas e linhas.
		/// Um objeto ICarenD2D1PathGeometry permite que você descreva um caminho geométrico. Para descrever o caminho de um objeto ICarenD2D1PathGeometry, use o método 
		/// ICarenD2D1PathGeometry::Open do objeto para recuperar um ICarenD2D1GeometrySink. Use o Sink para preencher a geometria do caminho com figuras e segmentos.
		/// Para criar uma ICarenD2D1PathGeometry, use o método ICarenD2D1Factory::CreatePathGeometry.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8252975A-E99F-4C78-ADF1-9021F8A2EF38")]
		public interface class ICarenD2D1PathGeometry : ICarenD2D1Geometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o número de figuras na Geometry Path. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de figuras na Geometry Path.</param>
			CarenResult GetFigureCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera o número de segmentos na Geometry Path. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de segmentos na Geometry Path.</param>
			CarenResult GetSegmentCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera o Sink de geometria que é usada para preencher a Geometry Path com figuras e segmentos. 
			/// Como as Geometry Path são imutáveis e só podem ser povoadas uma vez, é um erro chamar o método Open em uma Geometry Path mais de uma vez.
			/// Observe que o modo de preenchimento é padrão para D2D1_FILL_MODE_ALTERNATE. Para definir o modo de preenchimento, ligue para SetFillMode antes da primeira chamada para 
			/// BeginFigure. Se não o fizer, colocará o Geometry Sink em um estado de erro.
			/// </summary>
			/// <param name="Param_Out_GeometrySink">Retorna uma interface(ICarenD2D1GeometrySink) que contém o ponteiro para o GeometrySink que é usada para preencher o Geometry Path 
			/// com figuras e segmentos.</param>
			CarenResult Open([Out] ICarenD2D1GeometrySink^% Param_Out_GeometrySink);

			/// <summary>
			/// Copie o conteúdo da Geometry Path para o Geometry Sink especificado. 
			/// </summary>
			/// <param name="Param_GeometrySink">O Sink para a qual o conteúdo da Geometry Path é copiado. Modificar este Sink não altera o conteúdo desta Geometry Path.</param>
			CarenResult Stream(ICarenD2D1GeometrySink^ Param_GeometrySink);
		};

		/// <summary>
		/// (ID2D1PathGeometry1) - Interface responsável por adicionar funcionalidade à ICarenD2D1PathGeometry. Em particular, fornece o método ComputePointAndSegmentAtLength específico 
		/// para geometria.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("C11D945A-5820-42D4-A674-99BD93DCA23E")]
		public interface class ICarenD2D1PathGeometry1 : ICarenD2D1PathGeometry
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Calcula o ponto que existe a uma determinada distância ao longo da Geometry Path, juntamente com o índice do segmento em que o ponto está e o vetor direcional naquele ponto.
			/// </summary>
			/// <param name="Param_Length">A distância para caminhar ao longo do Path.</param>
			/// <param name="Param_StartSegment">O índice do segmento para começar a andar. Nota: Este índice é global para todo o Path, não apenas uma figura particular.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar ao Path antes de caminhar.</param>
			/// <param name="Param_FlatterningTolerance">A tolerância ao achatamento para usar ao caminhar ao longo de um arco ou segmento Bezier. A tolerância de achatamento é o erro 
			/// máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do que a tolerância ao 
			/// achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
			/// <param name="Param_Out_PointDesc">Retorna uma estrutura que contém a descrição do ponto que pode ser encontrado no local dado.</param>
			CarenResult ComputePointAndSegmentAtLength(
				float Param_Length,
				UInt32 Param_StartSegment,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_FlatterningTolerance,
				[Out] CA_D2D1_POINT_DESCRIPTION^% Param_Out_PointDesc);

			/// <summary>
			/// Calcula o ponto que existe a uma determinada distância ao longo da Geometry Path, juntamente com o índice do segmento em que o ponto está e o vetor direcional naquele ponto. 
			/// </summary>
			/// <param name="Param_Length">A distância para caminhar ao longo do Path.</param>
			/// <param name="Param_StartSegment">O índice do segmento para começar a andar. Nota: Este índice é global para todo o Path, não apenas uma figura particular.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar ao Path antes de caminhar.</param>
			/// <param name="Param_Out_PointDesc">Retorna uma estrutura que contém a descrição do ponto que pode ser encontrado no local dado.</param>
			CarenResult ComputePointAndSegmentAtLength(
				float Param_Length,
				UInt32 Param_StartSegment,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				[Out] CA_D2D1_POINT_DESCRIPTION^% Param_Out_PointDesc);
		};

		/// <summary>
		/// (ID2D1Multithread) - Interface responsável por representar um mecanismo de bloqueio de uma fábrica Direct2D que o Direct2D usa para controlar o acesso exclusivo de recursos em um 
		/// aplicativo que usa vários segmentos.
		/// Você deve usar esta interface enquanto faz qualquer operação em uma superfície Direct3D/DXGI. O Direct2D aguardará qualquer chamada até sair da seção crítica.
		/// Nota: A renderização normal é guardada automaticamente por uma trava Direct2D interna.
		/// Você pode obter um objeto ICarenD2D1Multithread consultando-o a partir de um objeto ICarenD2D1Factory.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("64814511-B9A9-4378-8D94-2D9062D4FD93")]
		public interface class ICarenD2D1Multithread : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Entra na seção crítica da API Direct2D, se ela existir. 
			/// </summary>
			void Enter();

			/// <summary>
			/// Retorna se a fábrica Direct2D foi criada com a bandeira D2D1_FACTORY_TYPE_MULTI_THREADED. 
			/// </summary>
			/// <param name="Param_Out_MultithreadSuporte">Retorna TRUE se a fábrica Direct2D foi criada como multi-threaded ou FALSE se foi criada como Thread única.</param>
			void GetMultithreadProtected([Out] Boolean% Param_Out_MultithreadSuporte);

			/// <summary>
			/// Deixa a seção crítica da API Direct2D, se ela existir. 
			/// </summary>
			void Leave();
		};

		/// <summary>
		/// (ID2D1SvgAttribute) - Interface responsável por descrever um atributo SVG.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("E4C39CEE-64EE-4C51-A793-83FFD083B8E9")]
		public interface class ICarenD2D1SvgAttribute : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
			/// </summary>
			/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
			CarenResult Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface);

			/// <summary>
			/// Retorna o elemento no qual este atributo é definido. Retorna nulo se o atributo não estiver definido em nenhum elemento. 
			/// </summary>
			/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém um ponteiro parao elemtno no qual este atributo é definido. O usuário deve inicializar a interface antes de chamar este método.</param>
			void GetElement(ICaren^ Param_Out_SvgElement);
		};

		/// <summary>
		/// (ID2D1SvgGlyphStyle) - Interface responsável por fornecer os valores para preenchimento de contexto, contexto-curso e valor de contexto que são usados ao renderizar glifos SVG.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("4FBAD4A1-6D2E-4A1F-BF61-B0E8DCABF20B")]
		public interface class ICarenD2D1SvgGlyphStyle : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Retorna os parâmetros de preenchimento solicitados. 
			/// </summary>
			/// <param name="Param_Out_Brush">Retorna o Brush que desve como a área é pintada.</param>
			void GetFill([Out] ICarenD2D1Brush^% Param_Out_Brush);

			/// <summary>
			/// Retorna os parâmetros de curso solicitados. Quaisquer parâmetros que não sejam nulos receberão o valor do parâmetro solicitado.
			/// </summary>
			/// <param name="Param_Out_Brush">Retorna o Brush que indica como o Stroke é pintado.</param>
			/// <param name="Param_Out_StrokeWidth">O "valor de contexto" para a propriedade 'largura de traçado'.</param>
			/// <param name="Param_Out_Dashes">O "valor de contexto" para a propriedade 'stroke-dasharray'.</param>
			/// <param name="Param_QuantidadeDashes">O número de Dasges na matriz (Param_Out_Dashes).</param>
			/// <param name="Param_Out_DashOffset">O "valor de contexto" para a propriedade 'stroke-dashoffset'.</param>
			void GetStroke(
				[Out] ICarenD2D1Brush^% Param_Out_Brush,
				[Out] float% Param_Out_StrokeWidth,
				[Out] cli::array<float>^% Param_Out_Dashes,
				UInt32 Param_QuantidadeDashes,
				[Out] float% Param_Out_DashOffset);

			/// <summary>
			/// Retorna o número de traços(Dashes) na matriz de traços. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número dashes na matriz.</param>
			void GetStrokeDashesCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Fornece valores a um glifo SVG para preenchimento. 
			/// </summary>
			/// <param name="Param_Brush">O Brush que descreve como a área é pintada. Um pincel nulo fará com que o valor de preenchimento de contexto venha do ICarenD2D1DeviceContext4::DrawText. 
			/// Se o (ICarenD2D1DeviceContext4::DrawText) Também ser nulo, o valor de preenchimento de contexto será 'nenhum'. Para definir o valor de "preenchimento de contexto", este método usa 
			/// o pincel fornecido com sua opacidade definida para 1. Para definir o valor "contexto-preenchimento-opacidade", este método utiliza a opacidade do pincel fornecido.</param>
			CarenResult SetFill(ICarenD2D1Brush^ Param_Brush);

			/// <summary>
			/// Fornece valores a um glifo SVG para propriedades de traçado. O pincel com opacidade definido para 1 é usado como o "traçado de contexto". A opacidade do pincel é usada como o valor 
			/// "contexto-traçado-opacidade". 
			/// </summary>
			/// <param name="Param_Brush">O Brush que descreve como o Stroke é pintado. Um pincel nulo fará com que o valor do traçado do contexto não seja nenhum.</param>
			/// <param name="Param_StrokeWidth">Especifica o 'valor de contexto' para a propriedade 'largura de traçado'.</param>
			/// <param name="Param_Dashes">Especifica o 'valor de contexto' para a propriedade 'stroke-dasharray'. Um valor nulo fará com que o traçado-dasharray seja definido como "nenhum".</param>
			/// <param name="Param_QuantidadeDashes">O número de Dashes na matriz (Param_Dashes).</param>
			/// <param name="Param_DashOffset">Especifica o 'valor de contexto' para a propriedade 'stroke-dashoffset'.</param>
			CarenResult SetStroke(
				ICarenD2D1Brush^ Param_Brush,
				float Param_StrokeWidth,
				cli::array<float>^ Param_Dashes,
				UInt32 Param_QuantidadeDashes,
				float Param_DashOffset);
		};

		/// <summary>
		/// (ID2D1SvgPaint) - Interface responsável por 
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("0E43644D-C6A2-4D6A-84AD-6934713E2E03")]
		public interface class ICarenD2D1SvgPaint : ICarenD2D1SvgAttribute
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR. 
			/// </summary>
			/// <param name="Param_Out_Color">Retorna a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR.</param>
			void GetColor([Out] CA_D2D1_COLOR_F^% Param_Out_Color);

			/// <summary>
			/// Obtém o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
			/// </summary>
			/// <param name="Param_Out_Id">O elemento id que atua como o servidor de tinta.</param>
			/// <param name="Param_IdCount">A largura do Id do elemento a ser retornado. Chame o método (GetIdLength) para obter esse valor.</param>
			CarenResult GetId(
				[Out] String^% Param_Out_Id,
				UInt32 Param_IdCount);

			/// <summary>
			/// Obtém o comprimento da sequência do id do elemento que age como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
			/// </summary>
			/// <param name="Param_Out_Largura">Retorna o comprimento da sequência do id elemento que age como o servidor de tinta. O comprimento da corda retornado não inclui 
			/// espaço para o exterminador nulo.</param>
			void GetIdLength([Out] UInt32% Param_Out_Largura);

			/// <summary>
			/// Obtém o tipo de tinta. 
			/// </summary>
			/// <param name="Param_Out_PaintType">Retorna um Enum para o tipo de tinta.</param>
			void GetPaintType([Out] CA_D2D1_SVG_PAINT_TYPE% Param_Out_PaintType);

			/// <summary>
			/// Define a cor da tinta usada se o tipo de tinta estiver D2D1_SVG_PAINT_TYPE_COLOR. 
			/// </summary>
			/// <param name="Param_Color">Uma estrutura(CA_D2D1_COLOR_F) com a nova cor da tinta.</param>
			CarenResult SetColor(CA_D2D1_COLOR_F^ Param_Color);

			/// <summary>
			/// Define o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
			/// </summary>
			/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
			CarenResult SetId(String^ Param_Id);

			/// <summary>
			/// Define o tipo de tinta. 
			/// </summary>
			/// <param name="Param_PaintType">Um enum que define o novo tipo de tinta.</param>
			CarenResult SetPaintType(CA_D2D1_SVG_PAINT_TYPE Param_PaintType);
		};

		/// <summary>
		/// (ID2D1SvgPathData) - Interface responsável por descrever os dados do Path SVG. Os Path Data podem ser definidos como o atributo 'd' em um elemento 'path'.
		/// O conjunto de Path Data é fatorado em duas matrizes. A matriz de dados do segmento armazena todos os números e a matriz de comandos armazena o conjunto 
		/// de comandos. Diferentemente do conjunto de dados da cadeia no atributo d, cada comando nesta representação usa um número fixo de elementos na matriz de dados do 
		/// segmento. Portanto, o path 'M 0,0 100,0 0,100 Z' é representado como: 'M0,0 L100,0 L0,100 Z'. Isso é dividido em duas matrizes, com os dados do segmento contendo 
		/// '0,0 100,0 0,100' e os comandos contendo 'M L L Z'.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("11C9C153-9A96-46E2-8976-606F34042CD3")]
		public interface class ICarenD2D1SvgPathData : ICarenD2D1SvgAttribute
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto de Path Geometry representando os Path Data. 
			/// </summary>
			/// <param name="Param_FillMode">Modo de preenchimento para o Path Geometry.</param>
			/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry1) contendo um ponteiro para para o objeto criado. </param>
			CarenResult CreatePathGeometry(
				CA_D2D1_FILL_MODE Param_FillMode,
				[Out] ICarenD2D1PathGeometry1^% Param_Out_PathGeometry);

			/// <summary>
			/// Recebe comandos da matriz de comandos. 
			/// </summary>
			/// <param name="Param_Out_Comandos">Buffer para conter os comandos.</param>
			/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
			/// <param name="Param_StartIndex">O índice dos primeiros comandos para recuperar.</param>
			CarenResult GetCommands(
				[Out] cli::array<CA_D2D1_SVG_PATH_COMMAND>^% Param_Out_Comandos,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Obtém o tamanho da matriz de comandos. 
			/// </summary>
			/// <param name="Param_Out_QuantidadeComandos">Retorna o tamanho da matriz de comandos.</param>
			void GetCommandsCount([Out] UInt32% Param_Out_QuantidadeComandos);

			/// <summary>
			/// Obtém dados do conjunto de dados do segmento. 
			/// </summary>
			/// <param name="Param_Out_Dados">Buffer para conter o conjunto de dados do segmento.</param>
			/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
			/// <param name="Param_StartIndex">O índice dos dados do primeiro segmento para recuperar.</param>
			CarenResult GetSegmentData(
				[Out] cli::array<float>^% Param_Out_Dados,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Obtém o tamanho do conjunto de dados do segmento. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o tamanho do conjunto de dados do segmento.</param>
			void GetSegmentDataCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Remove comandos do final da matriz de comandos. 
			/// </summary>
			/// <param name="Param_QuantidadeComandos">Especifica quantos comandos deve remover.</param>
			CarenResult RemoveCommandsAtEnd(UInt32 Param_QuantidadeComandos);

			/// <summary>
			/// Remove dados do conjunto de dados do segmento. 
			/// </summary>
			/// <param name="Param_DataCount">Especifica quantos dados deve remover.</param>
			CarenResult RemoveSegmentDataAtEnd(UInt32 Param_DataCount);

			/// <summary>
			/// Atualiza o conjunto de comandos. Os comandos existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos comandos. 
			/// </summary>
			/// <param name="Param_Comandos">A matriz de comandos.</param>
			/// <param name="Param_Quantidade">O número de comandos para atualizar.</param>
			/// <param name="Param_StartIndex">O índice para começar a atualizar comandos. Deve ser menor ou igual ao tamanho da matriz de comandos.</param>
			CarenResult UpdateCommands(
				cli::array<CA_D2D1_SVG_PATH_COMMAND>^ Param_Comandos,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Atualiza o conjunto de dados do segmento. Os dados do segmento existentes não atualizados por este método são preservados. O array é redimensionado maior, 
			/// se necessário, para acomodar os dados do novo segmento. 
			/// </summary>
			/// <param name="Param_Dados">O conjunto de dados.</param>
			/// <param name="Param_Quantidade">O número de dados para atualizar.</param>
			/// <param name="Param_StartIndex">O índice para começar a atualizar os dados do segmento. Deve ser menor ou igual ao tamanho do conjunto de dados do segmento.</param>
			CarenResult UpdateSegmentData(
				cli::array<float>^ Param_Dados,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);
		};

		/// <summary>
		/// (ID2D1SvgPointCollection) - Interface responsável por descrever um valor de pontos SVG em um elemento de polilinha ou polígono.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("5C11CB50-132F-4B6D-9042-2E4709EDC615")]
		public interface class ICarenD2D1SvgPointCollection : ICarenD2D1SvgAttribute
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Obtém pontos da matriz de pontos. 
			/// </summary>
			/// <param name="Param_Out_Points">O array que vai conter os pontos.</param>
			/// <param name="Param_Quantidade">A contagem de elementos no array.</param>
			/// <param name="Param_StartIndex">O índice do primeiro ponto a ser recuperado.</param>
			CarenResult GetPoints(
				[Out] cli::array<CA_D2D1_POINT_2F^>^% Param_Out_Points,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Obtém o número de pontos na matriz. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de pontos na matriz.</param>
			void GetPointsCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Remove pontos do final da matriz. 
			/// </summary>
			/// <param name="Param_Points">Especifica quantos pontos remover.</param>
			CarenResult RemovePointsAtEnd(UInt32 Param_Points);

			/// <summary>
			/// Atualiza o conjunto de pontos. Os pontos existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos pontos. 
			/// </summary>
			/// <param name="Param_Points">A matriz de pontos.</param>
			/// <param name="Param_Quantidade">O número de pontos a serem atualizados.</param>
			/// <param name="Param_StartIndex">O índice para começar a atualizar pontos. Deve ser menor ou igual ao tamanho da matriz.</param>
			CarenResult UpdatePoints(
				cli::array<CA_D2D1_POINT_2F^>^ Param_Points,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);
		};

		/// <summary>
		/// (ID2D1SvgStrokeDashArray) - Interface responsável por descrever um valor SVG stroke-dasharray.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("C01AFFC8-A1D5-4B8F-893F-C9913C42F03A")]
		public interface class ICarenD2D1SvgStrokeDashArray : ICarenD2D1SvgAttribute
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recebe traços(dashes) da matriz. 
			/// </summary>
			/// <param name="Param_Out_Dashes">O array que vai conter o dashes.</param>
			/// <param name="Param_Quantidade">A contagem de elementos da matriz no argumento dashes.</param>
			/// <param name="Param_StartIndex">O índice do primeiro traço a ser recuperado.</param>
			CarenResult GetDashes(
				[Out] cli::array<float>^% Param_Out_Dashes,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Recebe traços(dashes) da matriz.  
			/// </summary>
			/// <param name="Param_Out_Dashes">O array que vai conter o dashes.</param>
			/// <param name="Param_Quantidade">A contagem de elementos da matriz no argumento dashes.</param>
			/// <param name="Param_StartIndex">O índice do primeiro traço a ser recuperado.</param>
			CarenResult GetDashes(
				[Out] cli::array<CA_D2D1_SVG_LENGTH^>^% Param_Out_Dashes,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Obtém o número dos traços(dashes) na matriz. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de traços(dashes) na matriz.</param>
			void GetDashesCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Remove traços(dashes) da extremidade da matriz. 
			/// </summary>
			/// <param name="Param_DashesCount">Especifica quantos traços(dashes) para remover.</param>
			CarenResult RemoveDashesAtEnd(UInt32 Param_DashesCount);

			/// <summary>
			/// Atualiza o array. Os traços(dashes) existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos traços. 
			/// </summary>
			/// <param name="Param_Dashes">A matriz de traços.</param>
			/// <param name="Param_Quantidade">O número de traços para atualizar.</param>
			/// <param name="Param_StartIndex">O índice para começar a atualizar traços. Deve ser menor ou igual ao tamanho da matriz.</param>
			CarenResult UpdateDashes(
				cli::array<float>^ Param_Dashes,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);

			/// <summary>
			/// Atualiza o array. Os traços(dashes) existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos traços. 
			/// </summary>
			/// <param name="Param_Dashes">A matriz de traços.</param>
			/// <param name="Param_Quantidade">O número de traços para atualizar.</param>
			/// <param name="Param_StartIndex">O índice para começar a atualizar traços. Deve ser menor ou igual ao tamanho da matriz.</param>
			CarenResult UpdateDashes(
				cli::array<CA_D2D1_SVG_LENGTH^>^ Param_Dashes,
				UInt32 Param_Quantidade,
				UInt32 Param_StartIndex);
		};

		/// <summary>
		/// (ID2D1SvgDocument) - Interface responsável por representar um documento SVG.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("3694BCFB-8A52-4789-909D-CDABD0BDFC99")]
		public interface class ICarenD2D1SvgDocument : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto de tinta que pode ser usado para definir as propriedades 'preenchimento' ou 'traçado'. 
			/// </summary>
			/// <param name="Param_PaintType">Especifica o tipo de objeto de tinta para criar.</param>
			/// <param name="Param_Cor">A cor usada se o (Param_PaintType) estiver D2D1_SVG_PAINT_TYPE_COLOR.</param>
			/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
			/// <param name="Param_Out_Paint">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o objeto de pintura criado.</param>
			CarenResult CreatePaint(
				CA_D2D1_SVG_PAINT_TYPE Param_PaintType,
				CA_D2D1_COLOR_F^ Param_Cor,
				String^ Param_Id,
				[Out] ICarenD2D1SvgPaint^% Param_Out_Paint);

			/// <summary>
			/// Cria um objeto de dados de caminho que pode ser usado para definir um atributo 'd' em um elemento 'path'. 
			/// </summary>
			/// <param name="Param_SegmentData">Uma série de dados do segmento.</param>
			/// <param name="Param_QuantidadeSegments">Número de itens no (Param_SegmentData).</param>
			/// <param name="Param_Comandos">Uma série de comandos de Path.</param>
			/// <param name="Param_QuantidadeComandos">O número de itens em (Param_Comandos).</param>
			/// <param name="Param_Out_PathData">Retorna uma interface(ICarenD2D1SvgPathData) que contém um ponteiro para os PathData criados.</param>
			CarenResult CreatePathData(
				cli::array<float>^ Param_SegmentData,
				UInt32 Param_QuantidadeSegments,
				cli::array<CA_D2D1_SVG_PATH_COMMAND>^ Param_Comandos,
				UInt32 Param_QuantidadeComandos,
				[Out] ICarenD2D1SvgPathData^% Param_Out_PathData);

			/// <summary>
			/// Cria um objeto de pontos que pode ser usado para definir um atributo de pontos em um polígono ou elemento polilinha. 
			/// </summary>
			/// <param name="Param_Points">Os pontos na coleção de pontos.</param>
			/// <param name="Param_QuantidadePoints">O numero de pontos em (Param_Points)</param>
			/// <param name="Param_Out_PointCollection">Retorna uma interface(ICarenD2D1SvgPointCollection) que contém um ponteiro para o objeto criado.</param>
			CarenResult CreatePointCollection(
				cli::array<CA_D2D1_POINT_2F^>^ Param_Points,
				UInt32 Param_QuantidadePoints,
				[Out] ICarenD2D1SvgPointCollection^% Param_Out_PointCollection);

			/// <summary>
			/// Cria um objeto de matriz de traço que pode ser usado para definir a propriedade stroke-dasharray. 
			/// </summary>
			/// <param name="Param_Dashes">Uma série de traços(dashes).</param>
			/// <param name="Param_QuantidadeDashes">A quantidade de dashes no array (Param_Dashes).</param>
			/// <param name="Param_Out_StrokeDashArray">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o objeto criado.</param>
			CarenResult CreateStrokeDashArray(
				cli::array<CA_D2D1_SVG_LENGTH^>^ Param_Dashes,
				UInt32 Param_QuantidadeDashes,
				[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_StrokeDashArray);

			/// <summary>
			/// Deserializa uma subarvore do Stream. O fluxo deve ter apenas um elemento raiz, mas esse elemento raiz não precisa ser um elemento 'svg'. O elemento de saída não está inserido nesta árvore de documento. 
			/// </summary>
			/// <param name="Param_InputXmlStream">Um fluxo de entrada contendo a subárvore SVG XML.</param>
			/// <param name="Param_Out_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subárvore. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult Deserialize(
				ICarenStream^ Param_InputXmlStream,
				ICaren^ Param_Out_SvgElementSubTree);

			/// <summary>
			/// Obtém o elemento SVG com o ID especificado. 
			/// </summary>
			/// <param name="Param_Id">ID do elemento para recuperar.</param>
			/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento correspondente ao ID especificado. Se não for encontrado, esse valor será NULO. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult FindElementById(
				String^ Param_Id,
				ICaren^ Param_Out_SvgElement);

			/// <summary>
			/// Obtém o elemento raiz do documento. 
			/// </summary>
			/// <param name="Param_Out_SvgElementRoot">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento raiz do documento. O usuário deve inicializar a interface antes de chamar este método.</param>
			void GetRoot(ICaren^ Param_Out_SvgElementRoot);

			/// <summary>
			/// Retorna o tamanho do viewport inicial. 
			/// </summary>
			/// <param name="Param_Out_Size">Retorna o tamanho do viewport inicial</param>
			void GetViewportSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size);

			/// <summary>
			/// Serializa um elemento e sua subárvore para XML. O XML de saída é codificado como UTF-8.
			/// </summary>
			/// <param name="Param_OutputXmlStream">Um fluxo de saída para conter a subárvore SVG XML.</param>
			/// <param name="Param_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subarvore. Se for NULO, todo o documento será serializado.</param>
			CarenResult Serialize(
				ICarenStream^ Param_OutputXmlStream,
				ICaren^ Param_SvgElementSubTree);

			/// <summary>
			/// Define o elemento raiz do documento. 
			/// </summary>
			/// <param name="Param_SvgElementRoot">Uma interface(ICarenD2D1SvgElement) que define o novo elemento raiz do documento.</param>
			CarenResult SetRoot(ICaren^ Param_SvgElementRoot);

			/// <summary>
			/// Define o tamanho da configuração inicial. 
			/// </summary>
			/// <param name="Param_ViewportSize">O tamanho da viewport.</param>
			CarenResult SetViewportSize(CA_D2D1_SIZE_F^ Param_ViewportSize);
		};

		/// <summary>
		/// (ID2D1SvgElement) - Interface responsável por representar todos os elementos SVG.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("6191205A-BED1-42BD-8A1C-B248B2F2600A")]
		public interface class ICarenD2D1SvgElement : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Anexa um elemento à lista de childs. Se o elemento já tiver um pai, ele será removido deste pai como parte da operação de anexação.
			/// </summary>
			/// <param name="Param_NewChild">O elemento para anexar.</param>
			void AppendChild(ICarenD2D1SvgElement^ Param_NewChild);

			/// <summary>
			/// Cria um elemento a partir de um nome de etiqueta. O elemento é anexado à lista de childs. 
			/// </summary>
			/// <param name="Param_TagName">O nome da novo child. Uma sequência vazia é interpretada como um elemento de conteúdo de texto.</param>
			/// <param name="Param_Out_NewChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o novo child.</param>
			void CreateChild(
				String^ Param_TagName,
				[Out] ICarenD2D1SvgElement^% Param_Out_NewChild);

			/// <summary>
			/// Recebe um atributo deste elemento como uma string.
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Tipo">O tipo de String.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			/// <param name="Param_SizeValor">O tamanho do valor em bytes.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				D2D1_SVG_ATTRIBUTE_STRING_TYPE  Param_Tipo,
				[Out] String^% Param_Out_Valor,
				UInt32 Param_SizeValor);

			/// <summary>
			/// Obtém um atributo deste elemento como um tipo de POD. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Tipo">O tipo POD do valor.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICaren) que contém o ponteiro para o objeto(void*). O usuário deve inicializar a interface antes de chamar este método.</param>
			/// <param name="Param_SizeValorEmBytes">O tamanho do valor em bytes.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_ATTRIBUTE_POD_TYPE Param_Tipo,
				ICaren^ Param_Out_Valor,
				UInt32 Param_SizeValorEmBytes);

			/// <summary>
			/// Obtém um atributo deste elemento como um tipo de interface. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_RiidInterface">O ID de interface do valor do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna um(ICaren) com um ponteiro para a interface desejada. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				String^ Param_RiidInterface,
				ICaren^ Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como um float. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] float% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como uma string. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_COLOR_F^% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para obter o valor das propriedades de regra de preenchimento ou regra de clipe. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_FILL_MODE% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_DISPLAY% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para obter o valor da propriedade de transbordamento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_OVERFLOW% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de join de linha. Este método pode ser usado para obter o valor da propriedade stroke-linejoin. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_LINE_JOIN% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para obter o valor da propriedade stroke-linecap. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_LINE_CAP% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para obter o valor da propriedade de visibilidade. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_VISIBILITY% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como um valor matricial. Este método pode ser usado para obter o valor de um atributo Transform ou gradientTransform. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de tipo unitário. Este método pode ser usado para obter o valor de um atributo gradientUNITs ou clipPathUnits. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_UNIT_TYPE% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para obter o valor de um atributo spreadMethod. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_EXTEND_MODE% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para obter o valor de um atributo PreserveAspectRatio. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como um valor de comprimento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] CA_D2D1_SVG_LENGTH^% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgAttribute) que contém um ponteiro para o valor do atributo especificado.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] ICarenD2D1SvgAttribute^% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como uma tinta. Este método pode ser usado para obter o valor das propriedades de preenchimento ou traçado. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o valor do atributo especificado.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] ICarenD2D1SvgPaint^% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como uma matriz de traço de traço de traço. Este método pode ser usado para obter o valor da propriedade stroke-dasharray. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o valor do atributo especificado.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_Valor);

			/// <summary>
			/// Recebe um atributo deste elemento como pontos. Este método pode ser usado para obter o valor do atributo de pontos em um polígono ou elemento polilinha. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPointCollection) que contém um ponteiro para o valor do atributo especificado.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] ICarenD2D1SvgPointCollection^% Param_Out_Valor);

			/// <summary>
			/// Obtém um atributo desse elemento como dados de caminho. Este método pode ser usado para obter o valor do atributo d em um elemento de Path. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPathData) que contém um ponteiro para o valor do atributo especificado.</param>
			CarenResult GetAttributeValue(
				String^ Param_NomeAtributo,
				[Out] ICarenD2D1SvgPathData^% Param_Out_Valor);

			/// <summary>
			/// Obtém o comprimento da sequência de um atributo deste elemento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Tipo">O tipo de String do atributo.</param>
			/// <param name="Param_Out_LarguraValor">Retorna o comprimento do atributo. O comprimento da corda retornado não inclui espaço para o exterminador nulo.</param>
			CarenResult GetAttributeValueLength(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
				[Out] UInt32% Param_Out_LarguraValor);

			/// <summary>
			/// Obtém o documento que contém este elemento.
			/// </summary>
			/// <param name="Param_Out_Documento">Retorna uma interface(ICarenD2D1SvgDocument) com um ponteiro para o documento que contém este elemento. Este argumento será nulo se o elemento tiver sido 
			/// removido da árvore.</param>
			void GetDocument([Out] ICarenD2D1SvgDocument^% Param_Out_Documento);

			/// <summary>
			/// Obtém o primeiro filho deste elemento. 
			/// </summary>
			/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) do primeiro child deste elemento.</param>
			void GetFirstChild([Out] ICarenD2D1SvgElement^% Param_Out_Child);

			/// <summary>
			/// Obtém o ultimo filho deste elemento.  
			/// </summary>
			/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para do ultimo child deste elemento.</param>
			void GetLastChild([Out] ICarenD2D1SvgElement^% Param_Out_Child);

			/// <summary>
			/// Obtém o próximo irmão do elemento (Param_ReferenciaChild). 
			/// </summary>
			/// <param name="Param_ReferenciaChild">A referênciaChild deve ser um child imediato deste elemento.</param>
			/// <param name="Param_Out_ProximoChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
			/// for o ultimo child, a saída é NULA.</param>
			CarenResult GetNextChild(
				ICarenD2D1SvgElement^ Param_ReferenciaChild,
				[Out] ICarenD2D1SvgElement^% Param_Out_ProximoChild);

			/// <summary>
			/// Obtém o elemento pai. 
			/// </summary>
			/// <param name="Param_Out_Parent">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o elemento pai.</param>
			CarenResult GetParent([Out] ICarenD2D1SvgElement^% Param_Out_Parent);

			/// <summary>
			/// Recebe o child anterior do elemento (Param_ReferenciaChild). 
			/// </summary>
			/// <param name="Param_ReferenciaChild">>A referênciaChild deve ser um child imediato deste elemento.</param>
			/// <param name="Param_Out_ChildAnterior">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
			/// for o primeiro child, a saída é NULA. </param>
			CarenResult GetPreviousChild(
				ICarenD2D1SvgElement^ Param_ReferenciaChild,
				[Out] ICarenD2D1SvgElement^% Param_Out_ChildAnterior);

			/// <summary>
			/// Retorna o número de atributos especificados neste elemento. Os atributos só são considerados especificados se estiverem explicitamente definidos no elemento ou presentes dentro de um 
			/// estilo inline. As propriedades que recebem seu valor através da herança CSS não são consideradas especificadas. Um atributo pode ser especificado se for definido através de uma chamada 
			/// de método. Ele pode se tornar não especificado se for removido via RemoveAttribute. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de atributos especificados neste elemento.</param>
			void GetSpecifiedAttributeCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Obtém o nome do atributo no índice dado. 
			/// </summary>
			/// <param name="Param_Indice">O índice do atributo.</param>
			/// <param name="Param_Out_NomeAtributo">Retorna o nome do atributo.</param>
			/// <param name="Param_LarguraNome">A largura da String retornada em (Param_Out_NomeAtributo).</param>
			/// <param name="Param_Out_Herdado">Retorna um valor que define se o atributo está definido para o valor herdado</param>
			CarenResult GetSpecifiedAttributeName(
				UInt32 Param_Indice,
				[Out] String^% Param_Out_NomeAtributo,
				UInt32 Param_LarguraNome,
				[Out] Boolean% Param_Out_Herdado);

			/// <summary>
			/// Obtém o comprimento da sequência do nome do atributo especificado no índice dado. O comprimento da sequência de saída não inclui espaço para o exterminador nulo. 
			/// </summary>
			/// <param name="Param_Indice">O índice do atributo.</param>
			/// <param name="Param_Out_LarguraNome">Retorna a largura do nome do atributo no indice especificado.</param>
			/// <param name="Param_Out_Herdado">Retorna um valor Booleano que indica se o atributo está definido no valor herdado.</param>
			CarenResult GetSpecifiedAttributeNameLength(
				UInt32 Param_Indice,
				[Out] UInt32% Param_Out_LarguraNome,
				[Out] Boolean% Param_Out_Herdado);

			/// <summary>
			/// Obtém o nome da Tag.
			/// </summary>
			/// <param name="Param_Out_NomeTag">Retorna o nome da Tag.</param>
			/// <param name="Param_LarguraNomeTag">O comprimento da String em (Param_Out_NomeTag). Obtenha esse valor chamando o método (GetTagNameLength).</param>
			CarenResult GetTagName(
				[Out] String^% Param_Out_NomeTag,
				UInt32 Param_LarguraNomeTag);

			/// <summary>
			/// Obtém o comprimento da String do nome da Tag. 
			/// </summary>
			/// <param name="Param_Out_LarguraNomeTag">Retorna o comprimento da String do nome da tag. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
			void GetTagNameLength([Out] UInt32% Param_Out_LarguraNomeTag);

			/// <summary>
			/// Obtém o valor de um elemento de conteúdo de texto. 
			/// </summary>
			/// <param name="Param_Out_ValorElemento">Retorna o valor do elemento de conteúdo texto.</param>
			/// <param name="Param_LarguraValor">O comprimento da String em (Param_Out_ValorElemento). Obtenha esse valor chamando o método (GetTextValueLength).</param>
			CarenResult GetTextValue(
				[Out] String^% Param_Out_ValorElemento,
				UInt32 Param_LarguraValor);

			/// <summary>
			/// Obtém o comprimento do valor do conteúdo do texto. 
			/// </summary>
			/// <param name="Param_Out_LarguraValorElemento">Retorna o comprimento do valor do conteúdo do texto. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
			void GetTextValueLength([Out] UInt32% Param_Out_LarguraValorElemento);

			/// <summary>
			/// Retorna um booleano indicando se esse elemento tem filhos. 
			/// </summary>
			/// <param name="Param_Out_ElementoCrianca">Retorna TRUE se este elemento tiver filhos.</param>
			void HasChildren([Out] Boolean% Param_Out_ElementoCrianca);

			/// <summary>
			/// Insere (Param_NewChild) como um child deste elemento, antes do elemento (Param_ReferenceChild). Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da inserção. 
			/// </summary>
			/// <param name="Param_NewChild">O elemento a ser inserido.</param>
			/// <param name="Param_NewChild">O elemento que a child deve ser inserida antes. Se este parametro for NULO, o (Param_NewChild) será colocado como o último child. Se a (Param_ReferenceChild) não for NULA, deve ser um child imediato deste elemento.</param>
			CarenResult InsertChildBefore(
				ICarenD2D1SvgElement^ Param_NewChild,
				ICarenD2D1SvgElement^ Param_ReferenceChild);

			/// <summary>
			/// Retorna uma indicação booleana se o atributo estiver explicitamente definido no elemento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo.</param>
			/// <param name="Param_Out_Herdado">Retorna um valor booleano que indica se o atributo está definido para o valor herdado.</param>
			/// <param name="Param_Out_Especificado">Retorna TRUE se o atributo é explicitamente definido no elemento ou se ele está presente dentro de um estilo inline. Retorna FALSE se o atributo não for um atributo válido neste elemento.</param>
			CarenResult IsAttributeSpecified(
				String^ Param_NomeAtributo,
				[Out] Boolean% Param_Out_Herdado,
				[Out] Boolean% Param_Out_Especificado);

			/// <summary>
			/// Retorna um boolean indicando que este elemento representa conteúdo de texto. 
			/// </summary>
			/// <param name="Param_Out_Texto">Retorna TRUE se esse elemento representar conteúdo de texto, por exemplo, o conteúdo de um elemento 'título' ou 'desc'. O conteúdo do texto não tem um nome de tag.</param>
			void IsTextContent([Out] Boolean% Param_Out_Texto);

			/// <summary>
			/// Remove o atributo deste elemento. Também remove esse atributo de dentro de um estilo inline se presente. 
			/// </summary>
			/// <param name="Param_NomeAtributo">O nome do atributo para remover.</param>
			CarenResult RemoveAttribute(String^ Param_NomeAtributo);

			/// <summary>
			/// Remove o (Param_OldChild) da árvore. Filhos de (Param_OldChild) permanecem filhos de (Param_OldChild). 
			/// </summary>
			/// <param name="Param_OldChild"></param>
			CarenResult RemoveChild(ICarenD2D1SvgElement^ Param_OldChild);

			/// <summary>
			/// Substitui o elemento (Param_OldChild) pelo (Param_NewChild). Esta operação remove o (Param_OldChild) da árvore. Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da operação de substituição.
			/// </summary>
			/// <param name="Param_NewChild">O elemento a ser inserido.</param>
			/// <param name="Param_OldChild">O elemento child a ser substituído. O elemento (Param_OldChild) deve ser uma child imediata deste elemento.</param>
			CarenResult ReplaceChild(
				ICarenD2D1SvgElement^ Param_NewChild,
				ICarenD2D1SvgElement^ Param_OldChild);

			/// <summary>
			/// Define um atributo deste elemento usando uma string. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Tipo">O tipo da String.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
				String^ Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento usando um tipo POD. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Tipo">O tipo POD do atributo.</param>
			/// <param name="Param_Valor">Uma interface(ICaren) que contém um ponteiro(void*) do novo valor do atributo.</param>
			/// <param name="Param_Size">O tamanho do novo valor em bytes.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_ATTRIBUTE_POD_TYPE Param_Tipo,
				ICaren^ Param_Valor,
				UInt32 Param_Size);

			/// <summary>
			/// Define um atributo deste elemento usando uma interface. 
			/// Um determinado objeto atributo só pode ser definido em um elemento em um local de atributo de cada vez.
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">Uma interface(ICarenD2D1SvgAttribute) que contém um ponteiro para o novo vlaor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				ICarenD2D1SvgAttribute^ Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento usando um float. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				float Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como uma cor. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_COLOR_F^ Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para definir o valor das propriedades 'regra de preenchimento' ou 'regra de clipe'. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_FILL_MODE Param_Valor);

			/// <summary>
			/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_DISPLAY Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para definir o valor da propriedade de transbordamento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_OVERFLOW Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de join de linha. Este método pode ser usado para definir o valor da propriedade stroke-linejoin. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_LINE_JOIN Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para definir o valor da propriedade stroke-linecap. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_LINE_CAP Param_Valor);

			/// <summary>
			/// Define um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para definir o valor da propriedade de visibilidade. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_VISIBILITY Param_Valor);

			/// <summary>
			/// Define um atributo desse elemento como um valor de matriz. Este método pode ser usado para definir o valor de um atributo Transform ou gradientTransform. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_MATRIX_3X2_F^ Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de tipo de unidade. Este método pode ser usado para definir o valor de um atributo gradientUNITs ou clipPathUnits. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_UNIT_TYPE Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para definir o valor de um atributo spreadMethod. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_EXTEND_MODE Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para definir o valor de um atributo PreserveAspectRatio. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ Param_Valor);

			/// <summary>
			/// Define um atributo deste elemento como um valor de comprimento. 
			/// </summary>
			/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
			/// <param name="Param_Valor">O novo valor do atributo.</param>
			CarenResult SetAttributeValue(
				String^ Param_NomeAtributo,
				CA_D2D1_SVG_LENGTH^ Param_Valor);

			/// <summary>
			/// Define o valor de um elemento de conteúdo de texto. 
			/// </summary>
			/// <param name="Param_Texto">O novo valor do elemento conteúdo de texto.</param>
			/// <param name="Param_LarguraTexto">A largura da String em (Param_Texto).</param>
			CarenResult SetTextValue(
				String^ Param_Texto,
				UInt32 Param_LarguraTexto);
		};

		/// <summary>
		/// (ID2D1DeviceContext) - Interface responsável por representar um conjunto de buffers de estado e comando que são usados para renderizar um alvo.
		/// O contexto do dispositivo pode renderizar-se a um bitmap de destino ou a uma lista de comando.
		/// Qualquer recurso criado a partir de um contexto de dispositivo pode ser compartilhado com qualquer outro recurso criado a partir de um contexto de dispositivo quando ambos os contextos são criados no mesmo dispositivo.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("BB7E8387-F15D-44BF-BB5A-285D83568210")]
		public interface class ICarenD2D1DeviceContext : ICarenD2D1RenderTarget
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um bitmap que pode ser usado como uma superfície de destino, para leitura de volta para a CPU, ou como uma fonte para os APIs ICarenD2D1DeviceContext::DrawBitmap e ICarenD2D1BitmapBrush. Além disso, informações de contexto de cores podem ser passadas para o bitmap.
			/// O novo bitmap pode ser usado como um alvo para ICarenD2D1DeviceContext::SetTarget se for criado com D2D1_BITMAP_OPTIONS_TARGET.
			/// </summary>
			/// <param name="Param_Size">O tamanho do pixel do bitmap a ser criado.</param>
			/// <param name="Param_SourceData">Os dados iniciais que serão carregados no bitmap.</param>
			/// <param name="Param_Pitch">O Pitch dos dados de origem, se especificado.</param>
			/// <param name="Param_PropsBitmap">As propriedades do bitmap a serem criados.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para o novo objeto bitmap.</param>
			CarenResult CreateBitmap(
				CA_D2D1_SIZE_U^ Param_Size,
				ICarenBuffer^ Param_SourceData,
				UInt32 Param_Pitch,
				CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
				[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D. 
			/// </summary>
			/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
			/// <param name="Param_PropsBitmapBrush">Uma estrutura de propriedades de pincel bitmap.</param>
			/// <param name="Param_PropsBrush">Uma estrutura de propriedades do Brush.</param>
			/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
			CarenResult CreateBitmapBrush(
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ Param_PropsBitmapBrush,
				CA_D2D1_BRUSH_PROPERTIES^ Param_PropsBrush,
				[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush);

			/// <summary>
			/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D.
			/// </summary>
			/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
			/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
			CarenResult CreateBitmapBrush(
				ICarenD2D1Bitmap^ Param_Bitmap,
				[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush);

			/// <summary>
			/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D. 
			/// </summary>
			/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
			/// <param name="Param_PropsBrush">Uma estrutura de propriedades de pincel bitmap.</param>
			/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
			CarenResult CreateBitmapBrush(
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ Param_PropsBrush,
				[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush
			);

			/// <summary>
			/// Cria um bitmap a partir de uma superfície DXGI que pode ser definida como uma superfície alvo ou ter informações adicionais de contexto de cores especificadas.
			/// </summary>
			/// <param name="Param_DxgiSurface">A superfície DXGI a partir da qual o bitmap pode ser criado. [NOTA] A superfície DXGI deve ter sido criada a partir do mesmo dispositivo Direct3D com o que o contexto do dispositivo Direct2D está associado. </param>
			/// <param name="Param_PropsBitmap">As propriedades do bitmap especificadas além da superfície.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
			CarenResult CreateBitmapFromDxgiSurface(
				ICarenDXGISurface^ Param_DxgiSurface,
				CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
				ICarenD2D1Bitmap1^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um bitmap Direct2D copiando um bitmap WIC.
			/// </summary>
			/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) da fonte de bitmap WIC para copiar.</param>
			/// <param name="Param_PropsBitmap">Uma estrutura de propriedades bitmap que especifica opções de criação de bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
			CarenResult CreateBitmapFromWicBitmap(
				ICaren^ Param_WicBitmapSource,
				CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
				[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ICarenD2D1Bitmap1 copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
			/// </summary>
			/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) da fonte de bitmap WIC para copiar.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
			CarenResult CreateBitmapFromWicBitmap(
				ICaren^ Param_WicBitmapSource,
				[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um contexto de cores. O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado.
			/// Quando o espaço é D2D1_COLOR_SPACE_CUSTOM, o (Param_Profile) e o (Param_ProfileSize) devem ser especificados. Caso contrário, esses parâmetros devem ser definidos como NULO e zero, respectivamente. 
			/// Quando o espaço é D2D1_COLOR_SPACE_CUSTOM, o campo modelo do cabeçalho do (Param_Profile) é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço permanece personalizado.
			/// </summary>
			/// <param name="Param_EspacoCor">O espaço do contexto de cores para criar.</param>
			/// <param name="Param_Profile">Um buffer contendo os bytes de perfil ICC usados para inicializar o contexto de cor quando o espaço é D2D1_COLOR_SPACE_CUSTOM. Para outros tipos, o parâmetro é ignorado e deve ser definido como NULO.</param>
			/// <param name="Param_ProfileSize">O tamanho em bytes de (Param_Profile).</param>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
			CarenResult CreateColorContext(
				CA_D2D1_COLOR_SPACE Param_EspacoCor,
				ICarenBuffer^ Param_Profile,
				UInt32 Param_ProfileSize,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um contexto de cor carregando-o a partir do nome de arquivo especificado. Os bytes de perfil são o conteúdo do arquivo especificado pelo (Param_UrlArquivo).
			/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
			/// </summary>
			/// <param name="Param_UrlArquivo">O caminho para o arquivo contendo os bytes de perfil para inicializar o contexto de cores com.</param>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
			CarenResult CreateColorContextFromFilename(
				String^ Param_UrlArquivo,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um contexto de cores a partir de um ICarenWICColorContext.
			/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
			/// </summary>
			/// <param name="Param_WicColorContext">Uma interface(ICarenWICColorContext) usado para inicializar o contexto de cores.</param>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
			CarenResult CreateColorContextFromWicColorContext(
				ICaren^ Param_WicColorContext,
				[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um objeto ICarenD2D1CommandList que representa uma lista de comandos.
			/// Um ID2D1CommandList pode armazenar comandos Direct2D a serem exibidos posteriormente através do ICarenD2D1DeviceContext::DrawImage ou através de um pincel de imagem.
			/// </summary>
			/// <param name="Param_Out_CommandList">Retorna uma interface(ICarenD2D1CommandList) que contém um ponteiro para a nova lista de comandos criadas.</param>
			CarenResult CreateCommandList(
				[Out] ICarenD2D1CommandList^% Param_Out_CommandList);

			/// <summary>
			/// Cria um efeito para o ID de classe especificado.
			/// </summary>
			/// <param name="Param_IdEfeito">A ID de classe do efeito para criar. Consulte (GUIDs::GUIDs_D2D_CLSIDs_EFEITOS) para obter uma lista de IDs de efeitos disponiveis.</param>
			/// <param name="Param_Out_Efeito">Retorna uma interface(ICarenD2D1Effect) que contém um ponteiro para o novo efeito criado.</param>
			CarenResult CreateEffect(
				String^ Param_IdEfeito,
				[Out] ICarenD2D1Effect^% Param_Out_Efeito);

			/// <summary>
			/// Cria um Gradient Stop Collection, permitindo que o gradiente contenha canais de cores com valores fora de [0,1] e também permitindo renderização para um alvo de renderização de alta cor com interpolação no espaço sRGB.
			/// Este método interpola linearmente entre as paradas de cor. Uma conversão de espaço de cor opcional é aplicada após a interpolação. Se e como essa conversão gama é aplicada é determinada pela pré e pós-interpolação. Este método falhará se o contexto do dispositivo não suportar a precisão do buffer solicitada.
			/// Para obter o resultado desejado, você precisa garantir que as entradas sejam especificadas no espaço de cores correto.
			/// Você sempre deve especificar cores em alfa reto, independentemente do modo de interpolação ser pré - multiplicado ou reto.O modo de interpolação afeta apenas os valores interpolados.Da mesma forma, as paradas retornadas por ID2D1GradientStopCollection::GetGradientStops sempre terão alfa direto.
			/// </summary>
			/// <param name="Param_AlphaGradientStops">Uma matriz de valores de cor e compensações.</param>
			/// <param name="Param_Quantidade">A quantidade de elementos em (Param_AlphaGradientStops).</param>
			/// <param name="Param_PreInterpolationSpace">Especifica tanto o espaço de cor de entrada quanto o espaço em que ocorre a interpolação de cores.</param>
			/// <param name="Param_PosInterpolationSpace">O espaço de cor para o qual as cores serão convertidas após a interpolação ocorre.</param>
			/// <param name="Param_BufferPrecision">A precisão da textura usada para conter valores interpolados.  Este método falhará se o dispositivo Direct3D subjacente não suportar a precisão do buffer solicitada. Use ICarenD2D1DeviceContext::IsBufferPrecisionSupported para determinar o que é suportado.</param>
			/// <param name="Param_ExtendMode">Define como são determinadas cores fora do intervalo definidas pela coleção stop.</param>
			/// <param name="Param_ColorInterPolationMode">Define como as cores são interpoladas. D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED é o padrão.</param>
			/// <param name="Param_Out_GradientStopCollection">Retorna uma interface(ICarenD2D1GradientStopCollection1) que contém um ponteiro para o novo GradientStopCollection criado.</param>
			CarenResult CreateGradientStopCollection(
				cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_AlphaGradientStops,
				UInt32 Param_Quantidade,
				CA_D2D1_COLOR_SPACE Param_PreInterpolationSpace,
				CA_D2D1_COLOR_SPACE Param_PosInterpolationSpace,
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				CA_D2D1_EXTEND_MODE Param_ExtendMode,
				CA_D2D1_COLOR_INTERPOLATION_MODE Param_ColorInterPolationMode,
				[Out] ICarenD2D1GradientStopCollection1^% Param_Out_GradientStopCollection
			);

			/// <summary>
			/// Cria um pincel de imagem. A imagem de entrada pode ser qualquer tipo de imagem, incluindo um bitmap, efeito ou uma lista de comando.
			/// O pincel de imagem pode ser usado para preencher uma geometria arbitrária, uma máscara de opacidade ou texto.
			/// </summary>
			/// <param name="Param_Image">A imagem a ser usada como fonte para o pincel de imagem.</param>
			/// <param name="Param_PropsImageBrush">As propriedades específicas de um pincel de imagem.</param>
			/// <param name="Param_PropsBrush">Propriedades comuns a todos os pincéis.</param>
			/// <param name="Param_Out_ImageBrush">Retorna uma interface(ICarenD2D1ImageBrush) que contém um ponteiro para o novo Image Brush.</param>
			CarenResult CreateImageBrush(
				ICarenD2D1Image^ Param_Image,
				CA_D2D1_IMAGE_BRUSH_PROPERTIES^ Param_PropsImageBrush,
				CA_D2D1_BRUSH_PROPERTIES^ Param_PropsBrush,
				[Out] ICarenD2D1ImageBrush^% Param_Out_ImageBrush);

			/// <summary>
			/// Cria um pincel de imagem. A imagem de entrada pode ser qualquer tipo de imagem, incluindo um bitmap, efeito ou uma lista de comando.
			/// O pincel de imagem pode ser usado para preencher uma geometria arbitrária, uma máscara de opacidade ou texto.
			/// </summary>
			/// <param name="Param_Image"> imagem a ser usada como fonte para o pincel de imagem.</param>
			/// <param name="Param_PropsImageBrush">As propriedades específicas de um pincel de imagem.</param>
			/// <param name="Param_Out_ImageBrush">Retorna uma interface(ICarenD2D1ImageBrush) que contém um ponteiro para o novo Image Brush.</param>
			CarenResult CreateImageBrush(
				ICarenD2D1Image^ Param_Image,
				CA_D2D1_IMAGE_BRUSH_PROPERTIES^ Param_PropsImageBrush,
				[Out] ICarenD2D1ImageBrush^% Param_Out_ImageBrush);

			/// <summary>
			/// Desenha um bitmap para o alvo de renderização.
			/// O parâmetro (Param_RetanguloDestino) define o retângulo no alvo onde o bitmap aparecerá (em pixels independentes do dispositivo (DIPs)). Isso é afetado pela transformação atualmente definida e pela transformação da perspectiva, se definida. Se NULO for especificado, então o retângulo de destino é (esquerda=0, top=0, direita = largura (Param_RetanguloOrigem), inferior = altura (Param_RetanguloOrigem)).
			/// O parâmetro (Param_RetanguloOrigem) define o sub-retângulo do bitmap de origem (em DIPs). DrawBitmap irá cortar este retângulo para o tamanho do bitmap de origem, tornando assim impossível a amostra fora do bitmap. Se NULO for especificado, então o retângulo de origem será considerado o tamanho do bitmap de origem.
			/// </summary>
			/// <param name="Param_Bitmap">O bitmap para desenhar.</param>
			/// <param name="Param_RetanguloDestino">O retângulo de destino. O padrão é o tamanho do bitmap e o local é o canto superior esquerdo do alvo de renderização.</param>
			/// <param name="Param_Opacidade">A opacidade do bitmap.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação para usar.</param>
			/// <param name="Param_RetanguloOrigem">Um retângulo de origem opcional.</param>
			/// <param name="Param_PerspectiveTransform">Uma transformação opcional de perspectiva.</param>
			CarenResult DrawBitmap(
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				float Param_Opacidade,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem,
				CA_D2D1_MATRIX_4X4_F^ Param_PerspectiveTransform
			);

			/// <summary>
			/// Desenha um metafile para o contexto do dispositivo.
			/// </summary>
			/// <param name="Param_GdiMetafile">Uma interface(ID2D1GdiMetafile)[NAO IMPLEMENTADA PELA DLL] metafile para desenhar.</param>
			/// <param name="Param_TargetOffset">O deslocamento do canto superior esquerdo do alvo render.</param>
			CarenResult DrawGdiMetafile(
				ICaren^ Param_GdiMetafile,
				CA_D2D1_POINT_2F^ Param_TargetOffset);

			/// <summary>
			/// Desenha uma série de glifos(Glyphs) para o contexto do dispositivo.
			/// O (Param_GlyphRunDesc) é ignorado na prestação de serviços, mas pode ser útil para impressão e serialização de comandos de renderização, como em um arquivo XPS ou SVG. Isso estende o ICarenD2D1RenderTarget::DrawGlyphRun, que não tinha a descrição de execução do glifo.
			/// </summary>
			/// <param name="Param_BaseLineOrigin">Origem do primeiro glifo da série.</param>
			/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
			/// <param name="Param_GlyphRunDesc">Informações da série glifo suplementar.</param>
			/// <param name="Param_ForegroundBrush">O pincel que define a cor do texto.</param>
			/// <param name="Param_ModoMedicao">O modo de medição da série glifo, usado para determinar os avanços e deslocamentos. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
			CarenResult DrawGlyphRun(
				CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
				CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
				CA_DWRITE_GLYPH_RUN_DESCRIPTION^ Param_GlyphRunDesc,
				ICarenD2D1Brush^ Param_ForegroundBrush,
				CA_DWRITE_MEASURING_MODE Param_ModoMedicao);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
			/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
			/// <param name="Param_RetanguloImagem">O retângulo correspondente no espaço da imagem será mapeado para as origens dadas ao processar a imagem. Este valor padrão é NULO.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
			CarenResult DrawImage(
				ICarenD2D1Image^ Param_Image,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_RECT_F^ Param_RetanguloImagem,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao
			);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
			/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
			/// <param name="Param_RetanguloImagem">O retângulo correspondente no espaço da imagem será mapeado para as origens dadas ao processar a imagem. Este valor padrão é NULO.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
			CarenResult DrawImage(
				ICarenD2D1Effect^ Param_Efeito,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_RECT_F^ Param_RetanguloImagem,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// Se a (CA_D2D1_INTERPOLATION_MODE) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
			/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
			/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
			/// </summary>
			/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
			CarenResult DrawImage(
				ICarenD2D1Image^ Param_Image,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao
			);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
			/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
			/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
			/// </summary>
			/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
			CarenResult DrawImage(
				ICarenD2D1Effect^ Param_Efeito,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
			/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
			/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
			/// </summary>
			/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
			/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER.</param>
			CarenResult DrawImage(
				ICarenD2D1Image^ Param_Image,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao);

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo.
			/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
			/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
			/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
			/// </summary>
			/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
			/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
			/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
			/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER.</param>
			CarenResult DrawImage(
				ICarenD2D1Effect^ Param_Efeito,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
				CA_D2D1_COMPOSITE_MODE Param_ModoComposicao);

			/// <summary>
			/// Preencha usando o canal alfa do bitmap da máscara de opacidade fornecido.A opacidade do pincel será modulada pela máscara.O modo de antialiasing do destino de renderização deve ser definido como alias.
			/// </summary>
			/// <param name="Param_MascaraOpacidade">O bitmap que age como a máscara de opacidade</param>
			/// <param name="Param_Brush">O pincel a ser usado para preencher o primitivo.</param>
			/// <param name="Param_RetanguloDestino">O retângulo de destino para saída para dentro do alvo renderização</param>
			/// <param name="Param_RetanguloOrigem">O retângulo de origem do bitmap da máscara de opacidade.</param>
			CarenResult FillOpacityMask(
				ICarenD2D1Bitmap^ Param_MascaraOpacidade,
				ICarenD2D1Brush^ Param_Brush,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem);

			/// <summary>
			/// Obtém o dispositivo associado a um contexto de dispositivo.
			/// O aplicativo pode recuperar o dispositivo mesmo que ele seja criado a partir de um caminho de código de destino de renderização anterior. O aplicativo deve usar uma interface ICarenD2D1DeviceContext e, em seguida, chamar GetDevice. Algumas funcionalidades para controlar todos os recursos para um conjunto de contextos de dispositivos são mantidas apenas em um objeto ICarenD2D1Device.
			/// </summary>
			/// <param name="Param_Out_Dispositivo">Retorna uma interface(ICarenD2D1Device) que contém um ponteiro para um dispositivo Direct2D associado a este contexto do dispositivo.  O usuário deve inicializar a interface antes de chamar o método.</param>
			CarenResult GetDevice(ICaren^ Param_Out_Dispositivo);

			/// <summary>
			/// Obtém o número de retângulos de saída inválidos que se acumularam sobre o efeito.
			/// </summary>
			/// <param name="Param_Efeito">O efeito para contar os retângulos inválidos.</param>
			/// <param name="Param_Out_QuantidadeRetangulos">Retorna a contagem de retângulos devolvidos.</param>
			CarenResult GetEffectInvalidRectangleCount(
				ICarenD2D1Effect^ Param_Efeito,
				[Out] UInt32% Param_Out_QuantidadeRetangulos);

			/// <summary>
			/// Obtém os retângulos inválidos que se acumularam desde a última vez que o efeito foi desenhado e o EndDraw foi então chamado no contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Efeito">O efeito para obter os retângulos inválidos.</param>
			/// <param name="Param_Out_ArrayRetangulos">Retorna uma matriz de estruturas D2D1_RECT_F.</param>
			/// <param name="Param_QuantidadeRetangulos">O número de retângulos a serem devolvidos em (Param_Out_ArrayRetangulos).</param>
			CarenResult GetEffectInvalidRectangles(
				ICarenD2D1Effect^ Param_Efeito,
				[Out] cli::array<CA_D2D1_RECT_F^>^% Param_Out_ArrayRetangulos,
				UInt32 Param_QuantidadeRetangulos);

			/// <summary>
			/// Retorna os retângulos de entrada que são necessários para serem fornecidos pelo chamador para produzir o retângulo de saída dado.
			/// O chamador deve ter muito cuidado para não confiar nos retângulos de entrada necessários devolvidos. Pequenas alterações para correção do comportamento de um efeito podem resultar em diferentes retângulos sendo devolvidos. Além disso, diferentes tipos de otimização aplicada dentro da renderização também podem influenciar o resultado.
			/// </summary>
			/// <param name="Param_Efeito">A imagem cuja saída está sendo renderizada.</param>
			/// <param name="Param_RenderImageRectangle">A porção da imagem de saída cujos inputs estão sendo inspecionados.</param>
			/// <param name="Param_DescInputs">Uma lista dos insumos que estão retângulos estão sendo consultados.</param>
			/// <param name="Param_Out_InputRects">Retorna uma matriz com os retângulos de entrada.</param>
			/// <param name="Param_QuantidadeInput">O número de entradas.</param>
			CarenResult GetEffectRequiredInputRectangles(
				ICarenD2D1Effect^ Param_Efeito,
				CA_D2D1_RECT_F^ Param_RenderImageRectangle,
				cli::array<CA_D2D1_EFFECT_INPUT_DESCRIPTION^>^ Param_DescInputs,
				[Out] cli::array <CA_D2D1_RECT_F^>^% Param_Out_InputRects,
				UInt32 Param_QuantidadeInput
			);

			/// <summary>
			/// Obtém os limites do espaço do mundo(World-space Bounds) nos DIPs da execução do glifo usando o DPI do contexto do dispositivo.
			/// Os limites de imagem refletem o DPI atual, o modo unitário e a transformação mundial do contexto.
			/// </summary>
			/// <param name="Param_BaseLineOrigin">A origem da linha de base para a execução do glifo.</param>
			/// <param name="Param_GlypRun">O glifo que é executado para renderizar.</param>
			/// <param name="Param_MeasuringMode">O modo de medição DirectWrite que indica como as métricas de glifo são usadas para medir o texto quando ele é formatado.</param>
			/// <param name="Param_Out_Bounds">Retorna os limites do glifo são executados nos DIPs e no espaço do mundo(World-space Bounds).</param>
			CarenResult GetGlyphRunWorldBounds(
				CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
				CA_DWRITE_GLYPH_RUN^ Param_GlypRun,
				CA_DWRITE_MEASURING_MODE Param_MeasuringMode,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds
			);

			/// <summary>
			/// Obtém os limites de uma imagem sem a transformação mundial do contexto aplicado.
			/// Os limites de imagem não incluem multiplicação pelo Wolrd Transform. Eles refletem o DPI atual, o modo unitário e o modo de interpolação do contexto.
			/// Para obter os limites que incluem a World Transform, use ICarenD2D1DeviceContext::GetImageWorldBounds.
			/// Os limites retornados refletem quais pixels seriam impactados chamando DrawImage com um deslocamento de alvo de (0,0) e uma matriz de World Transform da identidade. Eles não refletem o retângulo de clipe atual definido no contexto do dispositivo ou a extensão da imagem alvo atual do contexto.
			/// </summary>
			/// <param name="Param_Image">A imagem cujos limites serão calculados.</param>
			/// <param name="Param_Out_LocalBounds">Retorna os limites da imagem em pixels independentes do dispositivo (DIPs) e no espaço local.</param>
			CarenResult GetImageLocalBounds(
				ICarenD2D1Image^ Param_Image,
				[Out] CA_D2D1_RECT_F^% Param_Out_LocalBounds
			);

			/// <summary>
			/// Obtém com os limites de uma imagem com a World Transform do contexto aplicado.
			/// Os limites de imagem refletem o DPI atual, o modo unitário e a World Transform do contexto. Para obter limites que não incluem a World Transform, use ICarenD2D1DeviceContext::GetImageLocalBounds.
			/// Os limites retornados refletem quais pixels seriam impactados chamando DrawImage com a mesma imagem e um deslocamento de alvo de (0,0). Eles não refletem o retângulo de clipe atual definido no contexto do dispositivo ou a extensão da imagem alvo atual do contexto.
			/// </summary>
			/// <param name="Param_Image">A imagem cujos limites serão calculados.</param>
			/// <param name="Param_Out_WorldBounds">Retorna os limites da imagem em pixels independentes do dispositivo (DIPs).</param>
			CarenResult GetImageWorldBounds(
				ICarenD2D1Image^ Param_Image,
				[Out] CA_D2D1_RECT_F^% Param_Out_WorldBounds
			);

			/// <summary>
			/// Retorna a mistura primitiva(PrimitiveBlend) atualmente definida usada pelo contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Out_PrimitiveBlend">Retorna A mistura primitiva atual. O valor padrão é D2D1_PRIMITIVE_BLEND_SOURCE_OVER.</param>
			CarenResult GetPrimitiveBlend(
				[Out] CA_D2D1_PRIMITIVE_BLEND% Param_Out_PrimitiveBlend
			);

			/// <summary>
			/// Obtém os controles de renderização que foram aplicados ao contexto.
			/// </summary>
			/// <param name="Param_Out_ControlesRenderizacao">Retorna os controles de renderização para este contexto.</param>
			CarenResult GetRenderingControls(
				[Out] CA_D2D1_RENDERING_CONTROLS^% Param_Out_ControlesRenderizacao
			);

			/// <summary>
			/// Obtém o alvo atualmente associado ao contexto do dispositivo.
			/// Se um alvo não estiver associado ao contexto do dispositivo, o alvo retornado será NULO.
			/// Não é possível que uma aplicação destrua esses bitmaps. Todos esses bitmaps são vinculáveis como alvos bitmap. No entanto, nem todos esses bitmaps podem ser usados como fontes de bitmap para métodos ICarenD2D1RenderTarget.
			/// </summary>
			/// <param name="Param_Out_Image">Retorna uma interface(ICarenD2D1Image) que contém um ponteiro para o alvo atualmente associado ao contexto do dispositivo.</param>
			CarenResult GetTarget(
				[Out] ICarenD2D1Image^% Param_Out_Image
			);

			/// <summary>
			/// Obtém o modo que está sendo usado para interpretar valores pelo contexto do dispositivo.
			/// </summary>
			/// <param name="Param_Out_Unit">Retorna O modo unitário.</param>
			CarenResult GetUnitMode([Out] CA_D2D1_UNIT_MODE Param_Out_Unit);

			/// <summary>
			/// Define que uma parte da entrada de um efeito é inválida. Este método pode ser chamado muitas vezes.
			/// Você pode usar este método para propagar retângulos inválidos através de um gráfico de efeito. Você pode consultar o Direct2D usando o método GetEffectInvalidRectangles.
			/// Você também pode usar este método para invalidar caches que acumularam ao renderizar efeitos que têm a propriedade D2D1_PROPERTY_CACHED definida como verdadeira.
			/// </summary>
			/// <param name="Param_Efeito">O efeito para invalidar.</param>
			/// <param name="Param_InputIndex">O índice de entrada.</param>
			/// <param name="Param_InputRectangle">O retangulo para invalidar.</param>
			CarenResult InvalidateEffectInputRectangle(
				ICarenD2D1Effect^ Param_Efeito,
				UInt32 Param_InputIndex,
				CA_D2D1_RECT_F^ Param_InputRectangle
			);

			/// <summary>
			/// Indica se a precisão do buffer é suportada pelo dispositivo Direct3D subjacente.
			/// </summary>
			/// <param name="Param_BufferPrecision">A precisão do buffer para verificar.</param>
			/// <param name="Param_Out_Suporte">Retorna TRUE se a precisão do buffer for suportada. Retorna FALSE se a precisão do buffer não for suportada.</param>
			void IsBufferPrecisionSupported(
				CA_D2D1_BUFFER_PRECISION  Param_BufferPrecision,
				[Out] Boolean% Param_Out_Suporte
			);

			/// <summary>
			/// Verifica se o formato é suportado pelo contexto do dispositivo. Os formatos suportados geralmente são determinados pelo hardware subjacente.
			/// Você pode usar formatos suportados na estrutura D2D1_PIXEL_FORMAT para criar bitmaps e renderizar alvos.
			/// O Direct2D não suporta todos os formatos DXGI, embora eles possam ter algum nível de suporte Direct3D pelo hardware.
			/// </summary>
			/// <param name="Param_DxgiFormato">O formato DXGI para verificar.</param>
			/// <param name="Param_Out_Suporte">Retorna TRUE se o formato for suportado. Retorna FALSE se o formato não for suportado.</param>
			CarenResult IsDxgiFormatSupported(
				CA_DXGI_FORMATO  Param_DxgiFormato,
				[Out] Boolean% Param_Out_Suporte
			);

			/// <summary>
			/// Empurre uma camada sobre o clipe e a pilha de camadas do contexto do dispositivo.
			/// </summary>
			/// <param name="Param_ParametrosLayer">Os parâmetros que definem a camada.</param>
			/// <param name="Param_Layer">O recurso de camada para empurrar o contexto do dispositivo que recebe operações de desenho subsequentes. [Nota] Se uma camada não for especificada, o Direct2D gerencia automaticamente o recurso de camada.</param>
			void PushLayer(
				CA_D2D1_LAYER_PARAMETERS1^ Param_ParametrosLayer,
				ICarenD2D1Layer^ Param_Layer);

			/// <summary>
			/// Altera o modo de mistura primitiva que é usado para todas as operações de renderização no contexto do dispositivo.
			/// </summary>
			/// <param name="Param_PrimitiveBlend">A mistura primitiva para usar.</param>
			void SetPrimitiveBlend(CA_D2D1_PRIMITIVE_BLEND Param_PrimitiveBlend);

			/// <summary>
			/// Define os controles de renderização para o contexto do dispositivo dado.
			/// Os controles de renderização permitem que o aplicativo ajuste a precisão, o desempenho e o uso de recursos das operações de renderização.
			/// </summary>
			/// <param name="Param_ControlesRenderizacao">Os controles de renderização a serem aplicados.</param>
			void SetRenderingControls(CA_D2D1_RENDERING_CONTROLS^ Param_ControlesRenderizacao);

			/// <summary>
			/// Define o bitmap ou lista de comando para a qual o contexto do dispositivo Direct2D será renderizado agora.
			/// O alvo pode ser alterado a qualquer momento, inclusive enquanto o contexto estiver desenhando.
			/// O alvo pode ser um bitmap criado com a bandeira D2D1_BITMAP_OPTIONS_TARGET, ou pode ser uma lista de comando. Outros tipos de imagens não podem ser definidas como um alvo. Por exemplo, você não pode definir a saída de um efeito como alvo. Se o alvo não for válido, o contexto entrará no estado de erro D2DERR_INVALID_TARGET.
			/// Você não pode usar o SetTarget para renderizar a uma lista de bitmap/comando a partir de vários contextos de dispositivo simultaneamente. Uma imagem é considerada "sendo renderizada" se alguma vez foi definida em um contexto de dispositivo dentro de um timespan BeginDraw/EndDraw.
			/// Se uma tentativa for feita para renderizar uma imagem através de vários contextos de dispositivo, todos os contextos subsequentes do dispositivo após o primeiro entrarão em um estado de erro.
			/// </summary>
			/// <param name="Param_Imagem">A superfície ou lista de comandos na qual o contexto do dispositivo Direct2D será renderizado.</param>
			void SetTarget(ICarenD2D1Image^ Param_Imagem);

			/// <summary>
			/// Define quais unidades serão usadas para interpretar valores passados no contexto do dispositivo.
			/// Este método afetará todas as propriedades e parâmetros afetados pelo ICarenD2D1RenderTarget::SetDpi e ICarenD2D1RenderTarget::GetDpi. Isso afeta todas as coordenadas, comprimentos e outras propriedades que não são explicitamente definidas como sendo em outra unidade.
			/// SetUnitMode afetará uma coordenada passada em ICarenD2D1DeviceContext::DrawLine, e o dimensionamento de uma geometria passou para ICarenD2D1DeviceContext::FillGeometry.
			/// SetUnitMode não afetará o valor devolvido pelo ICarenD2D1Bitmap::GetPixelSize.
			/// </summary>
			/// <param name="Param_UnitMode">Uma enumeração definindo como as unidades de passagem serão interpretadas pelo contexto do dispositivo.</param>
			void SetUnitMode(CA_D2D1_UNIT_MODE Param_UnitMode);
		};

		/// <summary>
		/// (ID2D1DeviceContext1) - Interface responsável por permitir a criação e o desenho de objetos de realização de geometria.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("4B28F5B8-D77D-48B4-804E-A77857CA337F")]
		public interface class ICarenD2D1DeviceContext1 : ICarenD2D1DeviceContext
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria uma representação dependente do dispositivo do preenchimento da geometria que pode ser posteriormente renderizada.
			/// </summary>
			/// <param name="Param_Geometria">A geometria para realizar.</param>
			/// <param name="Param_FlatterningTolerance">A tolerância de achatamento para usar ao converter Beziers em segmentos de linha. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
			/// <param name="Param_Out_GeometryRealization">Retorna uma interface(ICarenD2D1GeometryRealization) que contém um ponteiro para o novo objeto de realização.</param>
			CarenResult CreateFilledGeometryRealization(
				ICarenD2D1Geometry^ Param_Geometria,
				float Param_FlatterningTolerance,
				[Out] ICarenD2D1GeometryRealization^% Param_Out_GeometryRealization);

			/// <summary>
			/// Cria uma representação dependente do dispositivo do curso de uma geometria que pode ser posteriormente renderizada.
			/// </summary>
			/// <param name="Param_Geometria">A geometria para realizar.</param>
			/// <param name="Param_FlatterningTolerance">A tolerância de achatamento para usar ao converter Beziers em segmentos de linha. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
			/// <param name="Param_StrokeWidth">A largura do traçado. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
			/// <param name="Param_StrokeStyle">O estilo de traçado (opcional).</param>
			/// <param name="Param_Out_GeometryRealization">Retorna uma interface(ICarenD2D1GeometryRealization) que contém um ponteiro para o novo objeto de realização.</param>
			CarenResult CreateStrokedGeometryRealization(
				ICarenD2D1Geometry^ Param_Geometria,
				float Param_FlatterningTolerance,
				float Param_StrokeWidth,
				ICarenD2D1StrokeStyle^ Param_StrokeStyle,
				[Out] ICarenD2D1GeometryRealization^% Param_Out_GeometryRealization);

			/// <summary>
			/// Obtém uma dada realização de geometria ao alvo com o pincel especificado.
			/// Este método respeita todo o estado definido atualmente (transformação, DPI, modo de unidade, imagem de destino, clipes, camadas); no entanto, artefatos como faceta podem aparecer ao renderizar as realizações com uma escala efetiva grande (por meio da transformação ou do DPI). Os chamadores devem criar suas realizações com uma tolerância de nivelamento apropriada usando D2D1_DEFAULT_FLATTENING_TOLERANCE ou ComputeFlatteningTolerance para compensar isso.
			/// </summary>
			/// <param name="Param_GeometryRealization">A realização da geometria a ser feita.</param>
			/// <param name="Param_Brush">O pincel para renderizar a realização.</param>
			void DrawGeometryRealization(
				ICarenD2D1GeometryRealization^ Param_GeometryRealization,
				ICarenD2D1Brush^ Param_Brush);
		};

		/// <summary>
		/// (ID2D1DeviceContext2) - Interface responsável por executar todas as mesmas funções que a interface ID2D1DeviceContext1, além disso, permite funcionalidades como renderização de tinta, renderização de malha gradiente e carregamento de imagem melhorado.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("598CEBF3-36E4-44FE-B7D4-3F2DB1D9872E")]
		public interface class ICarenD2D1DeviceContext2 : ICarenD2D1DeviceContext1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria uma nova instância ID2D1GradientMesh usando a matriz dada de patches.
			/// </summary>
			/// <param name="Param_Patches">Uma matriz contendo as manchas a serem usadas nesta malha.</param>
			/// <param name="Param_QuantidadePatches">O número de patches nos patches argumenta para ler.</param>
			/// <param name="Param_Out_GradientMesh">Retorna uma intterface(ICarenD2D1GradientMesh) que contém um ponteiro para a nova malha de gradiente.</param>
			CarenResult CreateGradientMesh(
				cli::array<CA_D2D1_GRADIENT_MESH_PATCH^>^ Param_Patches,
				UInt32 Param_QuantidadePatches,
				[Out] ICarenD2D1GradientMesh^% Param_Out_GradientMesh
			);

			/// <summary>
			/// Cria uma fonte de imagem a partir de um conjunto de superfícies DXGI. As superfícies YCbCr são convertidas automaticamente para RGBA durante o desenho subsequente.
			/// A GPU também deve ter suporte suficiente para que um formato de pixel seja suportado por D2D. Para determinar se o D2D suporta um formato, ligue para o IsDxgiFormatSupported.
			/// Esta API converte formatos YCbCr em sRGB usando o tipo e as opções de espaço de cores fornecidas. Presume-se que os dados RGBA estejam no espaço desejado e o D2D não aplique nenhuma conversão.
			/// </summary>
			/// <param name="Param_DxgiSurfaces">Uma matriz superfices do DXGI para serem usadas.</param>
			/// <param name="Param_QuantidadeSuperficesDXGI">O número de superfícies fornecidas; deve ser entre um e três.</param>
			/// <param name="Param_EspacoCor">O espaço de cor da entrada.</param>
			/// <param name="Param_Opcoes">Opções controlando conversões de espaço de cores.</param>
			/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSource) que contém um ponteiro para a nova fonte de imagem.</param>
			CarenResult CreateImageSourceFromDxgi(
				cli::array<ICaren^>^ Param_DxgiSurfaces,
				UInt32 Param_QuantidadeSuperficesDXGI,
				CA_DXGI_COLOR_SPACE_TYPE Param_EspacoCor,
				CA_D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1ImageSource^% Param_Out_ImageSource
			);

			/// <summary>
			/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
			/// Este método cria uma fonte de imagem que pode ser usada para desenhar a imagem.
			/// Este método suporta imagens que excedem o tamanho máximo da textura. Grandes imagens são armazenadas internamente dentro de um cache de ladrilhos esparsos.
			/// </summary>
			/// <param name="Param_WicBitmapSource">A fonte de bitmap WIC para criar a fonte de imagem.</param>
			/// <param name="Param_OpcoesCarregamento">Opções para criar a fonte de imagem. As opções padrão são usadas se NULO.</param>
			/// <param name="Param_ModoAlfa">O modo alfa da imagem; isso é determinado automaticamente a partir do formato de pixel da fonte se D2D1_ALPHA_MODE_UNKNOWN for aprovada.</param>
			/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
			CarenResult CreateImageSourceFromWic(
				ICaren^ Param_WicBitmapSource,
				CA_D2D1_IMAGE_SOURCE_LOADING_OPTIONS Param_OpcoesCarregamento,
				CA_D2D1_ALPHA_MODE Param_ModoAlfa,
				[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
			);

			/// <summary>
			/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
			/// </summary>
			/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) que representa a fonte de bitmap WIC para criar a fonte de imagem.</param>
			/// <param name="Param_OpcoesCarregamento">Opções para criar a fonte de imagem. As opções padrão são usadas se NULO.</param>
			/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
			CarenResult CreateImageSourceFromWic(
				ICaren^ Param_WicBitmapSource,
				CA_D2D1_IMAGE_SOURCE_LOADING_OPTIONS Param_OpcoesCarregamento,
				[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
			);

			/// <summary>
			/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
			/// Este método cria uma fonte de imagem que pode ser usada para desenhar a imagem.
			/// Este método suporta imagens que excedem o tamanho máximo da textura. Grandes imagens são armazenadas internamente dentro de um cache de ladrilhos esparsos.
			/// Esta API suporta o mesmo conjunto de formatos de pixels e modos alfa suportados pelo CreateBitmapFromWicBitmap.
			/// </summary>
			/// <param name="Param_WicBitmapSource">A fonte de bitmap WIC para criar a fonte de imagem.</param>
			/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
			CarenResult CreateImageSourceFromWic(
				ICaren^ Param_WicBitmapSource,
				[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
			);

			/// <summary>
			/// Cria um novo objeto ICarenD2D1Ink que começa no ponto determinado.
			/// </summary>
			/// <param name="Param_StartPoint"> O ponto de partida do primeiro segmento do primeiro curso no novo objeto de tinta.</param>
			/// <param name="Param_Out_Ink">Retorna uma interface(ICarenD2D1Ink) que contém um ponteiro para um novo objeto de tinta.</param>
			CarenResult CreateInk(
				CA_D2D1_INK_POINT^ Param_StartPoint,
				[Out] ICarenD2D1Ink^% Param_Out_Ink
			);

			/// <summary>
			/// Cria um novo objeto ICarenD2D1InkStyle, para uso com métodos de renderização de tinta, como o DrawInk.
			/// </summary>
			/// <param name="Param_PropsInkStyle">As propriedades do estilo de tinta a serem criadas.</param>
			/// <param name="Param_Out_InkStyle">Retorna uma interface(ICarenD2D1InkStyle) que contém um ponteiro para um novo objeto de estilo de tinta.</param>
			CarenResult CreateInkStyle(
				CA_D2D1_INK_STYLE_PROPERTIES^ Param_PropsInkStyle,
				[Out] ICarenD2D1InkStyle^% Param_Out_InkStyle
			);

			/// <summary>
			/// Cria uma tabela de pesquisa 3D para mapear uma entrada de 3 canais para uma saída de 3 canais. Os dados da tabela devem ser fornecidos em formato de 4 canais.
			/// </summary>
			/// <param name="Param_BufferPrecision">Precisão dos dados da tabela de pesquisa de entrada.</param>
			/// <param name="Param_Extents">Número de elementos de tabela de procuração por dimensão (X, Y, Z).</param>
			/// <param name="Param_Data">Buffer segurando os dados da tabela de pesquisa.</param>
			/// <param name="Param_BufferSize">Tamanho do buffer de dados da tabela de pesquisa.</param>
			/// <param name="Param_Strides">Uma matriz contendo dois valores. O primeiro valor é o tamanho em bytes de uma linha (dimensão X) de dados LUT para a próxima. O segundo valor é o tamanho em bytes de um plano de dados LUT (dimensões X e Y) para o próximo.</param>
			/// <param name="Param_Out_LookupTable">Retorna uma interface(ICarenD2D1LookupTable3D) que contém um ponteiro para a nova tabela de procuração.</param>
			CarenResult CreateLookupTable3D(
				CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
				cli::array<UInt32>^ Param_Extents,
				ICarenBuffer^ Param_Data,
				UInt32 Param_BufferSize,
				cli::array<UInt32>^ Param_Strides,
				[Out] ICarenD2D1LookupTable3D^% Param_Out_LookupTable
			);

			/// <summary>
			/// Cria uma fonte de imagem que compartilha recursos com um original.
			/// </summary>
			/// <param name="Param_FonteImagem">A imagem original.</param>
			/// <param name="Param_Propriedades">Propriedades para a imagem de origem.</param>
			/// <param name="Param_Out_TransformedImageSource">Retorna uma interface(ICarenD2D1TransformedImageSource) que contém um ponteiro para a nova fonte de imagem.</param>
			CarenResult CreateTransformedImageSource(
				ICarenD2D1ImageSource^ Param_FonteImagem,
				CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^ Param_Propriedades,
				[Out] ICarenD2D1TransformedImageSource^% Param_Out_TransformedImageSource
			);

			/// <summary>
			/// Desenha um metafile para o contexto do dispositivo usando os retângulos de origem e destino dado.
			/// </summary>
			/// <param name="Param_GdiMetafile">O metafile para desenhar.</param>
			/// <param name="Param_RetanguloDestino">O retângulo no alvo onde o metafile será desenhado, em relação ao canto superior esquerdo (definido em DIPs) do alvo render. Se null for especificado, o retângulo de destino é {0, 0, w, h}, onde w e h são a largura e altura do metafile conforme relatado pelo ICarenD2D1GdiMetafile::GetBounds.</param>
			/// <param name="Param_RetanguloOrigem">O retângulo do metafile de origem que será desenhado, em relação ao canto superior esquerdo (definido em DIPs) do metafile. Se null for especificado, o retângulo de origem é o valor devolvido pelo ICarenD2D1GdiMetafile1::GetSourceBounds.</param>
			void DrawGdiMetafile(
				ICaren^ Param_GdiMetafile,
				CA_D2D1_RECT_F^ Param_RetanguloDestino,
				CA_D2D1_RECT_F^ Param_RetanguloOrigem
			);

			/// <summary>
			/// Renderiza uma determinada malha gradiente ao alvo.
			/// </summary>
			/// <param name="Param_GradientMesh">A malha de gradiente a ser renderizada.</param>
			void DrawGradientMesh(
				ICarenD2D1GradientMesh^ Param_GradientMesh
			);

			/// <summary>
			/// Renderiza o objeto de tinta dado usando o estilo pincel e tinta dado.
			/// </summary>
			/// <param name="Param_Ink">O objeto de tinta a ser renderizado.</param>
			/// <param name="Param_Brush">O pincel com o qual renderizar o objeto de tinta.</param>
			/// <param name="Param_InkStyle">O estilo de tinta a ser usado ao renderizar o objeto de tinta.</param>
			void DrawInk(
				ICarenD2D1Ink^ Param_Ink,
				ICarenD2D1Brush^ Param_Brush,
				ICarenD2D1InkStyle^ Param_InkStyle
			);

			/// <summary>
			/// Obtém o World de uma determinada malha gradiente.
			/// </summary>
			/// <param name="Param_GradientMesh">A malha de gradiente cujos limites mundiais serão calculados.</param>
			/// <param name="Param_Out_Bounds">Retorna uma estrutura que contém os limites da malha gradiente, em pixels independentes do dispositivo (DIPs).</param>
			CarenResult GetGradientMeshWorldBounds(
				ICarenD2D1GradientMesh^ Param_GradientMesh,
				[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);
		};

		/// <summary>
		/// (ID2D1DeviceContext3) - Interface responsável por executar todas as mesmas funções da interface ID2D1DeviceContext2, além de permitir a funcionalidade para criar e desenhar lotes sprite.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8403E13C-8C57-48D7-8756-8B9CB084B51B")]
		public interface class ICarenD2D1DeviceContext3 : ICarenD2D1DeviceContext2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um novo lote de sprite vazio. Depois de criar um lote sprite, use ICarenD2D1SpriteBatch::AddSprites para adicionar sprites a ele e, em seguida, use ICarenD2D1DeviceContext3::DrawSpriteBatch para desenhá-lo.
			/// </summary>
			/// <param name="Param_Out_SpriteBatch">Retorna uma interface(ICarenD2D1SpriteBatch) que contém um ponteiro para o novo lote de sprites vazio para ser preenchido.</param>
			CarenResult CreateSpriteBatch(
				[Out] ICarenD2D1SpriteBatch^% Param_Out_SpriteBatch);

			/// <summary>
			/// Renderiza todos os sprites no lote sprite dado ao contexto do dispositivo usando as opções de desenho especificadas.
			/// </summary>		
			/// <param name="Param_SpriteBatch">>O lote de sprite para desenhar.</param>
			/// <param name="Param_StartIndex">O índice do primeiro sprite no lote sprite para desenhar.</param>
			/// <param name="Param_QuantidadeSprite">O número de sprites para desenhar.</param>
			/// <param name="Param_Bitmap">O bitmap do qual os sprites devem ser originários. O retângulo de cada fonte de sprite refere-se a uma parte deste bitmap.</param>
			/// <param name="Param_ModoInterpolacao">O modo de interpolação a ser usado ao desenhar este lote sprite. Isso determina como o Direct2D interpola os pixels dentro dos sprites desenhados se o dimensionamento for realizado.</param>
			/// <param name="Param_OpcoesSprite">As opções adicionais de desenho, se houver, a serem usadas para este lote sprite.</param>
			void DrawSpriteBatch(
				ICarenD2D1SpriteBatch^ Param_SpriteBatch,
				UInt32 Param_StartIndex,
				UInt32 Param_QuantidadeSprite,
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_INTERPOLATION_MODE Param_ModoInterpolacao,
				CA_D2D1_SPRITE_OPTIONS Param_OpcoesSprite
			);

			/// <summary>
			/// Renderiza parte ou todo o lote sprite dado ao contexto do dispositivo usando as opções de desenho especificadas.
			/// </summary>
			/// <param name="Param_SpriteBatch">O lote de sprite para desenhar.</param>
			/// <param name="Param_Bitmap">O bitmap do qual os sprites devem ser originários. O retângulo de cada fonte de sprite refere-se a uma parte deste bitmap.</param>
			/// <param name="Param_ModoInterpolacao">O modo de interpolação a ser usado ao desenhar este lote sprite. Isso determina como o Direct2D interpola os pixels dentro dos sprites desenhados se o dimensionamento for realizado.</param>
			/// <param name="Param_OpcoesSprite">As opções adicionais de desenho, se houver, a serem usadas para este lote sprite.</param>
			void DrawSpriteBatch(
				ICarenD2D1SpriteBatch^ Param_SpriteBatch,
				ICarenD2D1Bitmap^ Param_Bitmap,
				CA_D2D1_BITMAP_INTERPOLATION_MODE Param_ModoInterpolacao,
				CA_D2D1_SPRITE_OPTIONS Param_OpcoesSprite
			);
		};

		/// <summary>
		/// (ID2D1DeviceContext4) - Interface responsável por executar todas as mesmas funções da interface ICarenD2D1DeviceContext3, além de permitir a funcionalidade para lidar com novos tipos de glifos de fonte de cor.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("DF6632AC-3E0A-4084-B215-A55748F761DD")]
		public interface class ICarenD2D1DeviceContext4 : ICarenD2D1DeviceContext3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto estilo glifo SVG.
			/// </summary>
			/// <param name="Param_Out_SvgGlyphStyle">Retorna uma interface(ICarenD2D1SvgGlyphStyle) que contém um ponteiro para o novo Glyph Style.</param>
			CarenResult CreateSvgGlyphStyle(
				[Out] ICarenD2D1SvgGlyphStyle^% Param_Out_SvgGlyphStyle);

			/// <summary>
			/// Desenha uma cor bitmap glifo executado usando um dos formatos bitmap.
			/// </summary>
			/// <param name="Param_GlyphImageFormat">Especifica o formato da imagem glifo. Os formatos suportados são DWRITE_GLYPH_IMAGE_FORMATS_PNG, DWRITE_GLYPH_IMAGE_FORMATS_JPEG, DWRITE_GLYPH_IMAGE_FORMATS_TIFF ou DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8. Este método resultará em um erro se a execução do glifo de cor não contiver o formato solicitado.
			/// Apenas um formato pode ser especificado de cada vez, combinações de bandeiras não são entradas válidas.</param>
			/// <param name="Param_BaselineOrigin">A origem da linha de base para a corrida do glifo.</param>
			/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
			/// <param name="Param_MeasuringMode">Indica o método de medição.</param>
			/// <param name="Param_BitmapSnapOption">Especifica a política de estalo de pixels ao renderizar glifos bitmap de cor.</param>
			void DrawColorBitmapGlyphRun(
				CA_DWRITE_GLYPH_IMAGE_FORMATS Param_GlyphImageFormat,
				CA_D2D1_POINT_2F^ Param_BaselineOrigin,
				CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
				CA_DWRITE_MEASURING_MODE Param_MeasuringMode,
				CA_D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION Param_BitmapSnapOption);

			/// <summary>
			/// Desenha uma tira glifo colorida que tem o formato de DWRITE_GLYPH_IMAGE_FORMATS_SVG. 
			/// </summary>
			/// <param name="Param_BaselineOrigin">A origem da linha de base para a corrida do glifo.</param>
			/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
			/// <param name="Param_DefaultFillBrush">O pincel usado para pintar os glifos especificados.</param>
			/// <param name="Param_SvgGlyphStyle">Valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
			/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor. Observe que isso não é o mesmo que a paletaIndex na estrutura DWRITE_COLOR_GLYPH_RUN, o que não é relevante para os glifos SVG.</param>
			/// <param name="Param_MeasuringMode">Indica o método de medição usado para layout de texto.</param>
			void DrawSvgGlyphRun(
				CA_D2D1_POINT_2F^ Param_BaselineOrigin,
				CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
				ICarenD2D1Brush^ Param_DefaultFillBrush,
				ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
				UInt32 Param_ColorPaletteIndex,
				CA_DWRITE_MEASURING_MODE Param_MeasuringMode);

			/// <summary>
			/// Desenha o texto dentro do retângulo de layout dado. Por padrão, este método executa o snapping da linha de base e torna as versões coloridas de glifos em fontes coloridas.
			/// </summary>
			/// <param name="Param_Texto">Uma string que contém a sequencia para desenhar.</param>
			/// <param name="Param_LarguraTexto">O número de caracteres em (Param_Texto).</param>
			/// <param name="Param_FormatoTexto">Uma interface(IDWriteTextFormat)[SDK PENDENTE] que descreve a formatação de detalhes do texto para desenhar, como a fonte, o tamanho da fonte e a direção do fluxo.</param>
			/// <param name="Param_LayoutRect">O tamanho e a posição da área em que o texto é desenhado.</param>
			/// <param name="Param_DefaultFillBrush">O pincel usado para pintar o texto.</param>
			/// <param name="Param_SvgGlyphStyle">Valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
			/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor.</param>
			/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
			/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
			void DrawText(
				String^ Param_Texto,
				UInt32 Param_LarguraTexto,
				ICaren^ Param_FormatoTexto,
				CA_D2D1_RECT_F^ Param_LayoutRect,
				ICarenD2D1Brush^ Param_DefaultFillBrush,
				ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
				UInt32 Param_ColorPaletteIndex,
				CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes,
				CA_DWRITE_MEASURING_MODE Param_MeasuringMode);

			/// <summary>
			/// Desenha um objeto de layout de texto. Se o layout não for alterado posteriormente, isso pode ser mais eficiente do que o DrawText ao desenhar o mesmo layout repetidamente. 
			/// </summary>
			/// <param name="Param_Origin">O ponto, descrito em pixels independentes do dispositivo, no qual o canto superior esquerdo do texto descrito pelo (Param_TextLayout) é desenhado.</param>
			/// <param name="Param_TextLayout">Uma interface(IDWriteTextLayout)[SDK PENDENTE] que representa o texto formatado para desenhar. Quaisquer efeitos de desenho que não herdem do ICarenD2D1Resource são ignorados. Se houver efeitos de desenho que herdam do ICarenD2D1Resource que não são pincéis, este método falhará e o alvo de renderização é colocado em um estado de erro.</param>
			/// <param name="Param_DefaultFillBrush">O pincel usado para pintar o texto.</param>
			/// <param name="Param_SvgGlyphStyle">Os valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
			/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor.</param>
			/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
			void DrawTextLayout(
				CA_D2D1_POINT_2F^ Param_Origin,
				ICaren^ Param_TextLayout,
				ICarenD2D1Brush^ Param_DefaultFillBrush,
				ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
				UInt32 Param_ColorPaletteIndex,
				CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes);

			/// <summary>
			/// Recupera uma imagem do glifo bitmap de cor do cache glifo de cor. Se o cache ainda não contiver o recurso solicitado, ele será criado. Este método pode ser usado para estender a vida útil de uma imagem glifo mesmo depois de ser despejado do cache glifo de cor.
			/// </summary>
			/// <param name="Param_GlyphImageFormat">O formato da imagem glifo. Se não houver dados de imagem no formato solicitado para o glifo solicitado, este método retornará um erro.</param>
			/// <param name="Param_GlyphOrigin">A origem do glifo.</param>
			/// <param name="Param_FontFace">Uma interface(IDWriteFontFace)[SDK PENDENTE] que faz referência a uma face de fonte que contém o tipo de fonte, referências de arquivo apropriadas, dados de identificação de faces e vários dados de fontes, como métricas, nomes e contornos de glifos.</param>
			/// <param name="Param_FontSize">O tamanho da fonte especificado afeta a escolha de qual bitmap usar a partir da fonte. Também afeta o glifo de saídaTransforme, fazendo com que ele dimensione adequadamente o glifo.</param>
			/// <param name="Param_GlyphIndex">Índice do glifo.</param>
			/// <param name="Param_IsSideways">Se for verdade, especifica que os glifos são girados 90 graus para a esquerda e as métricas verticais são usadas. A escrita vertical é obtida especificando isSideways como verdadeiro e girando toda a corrida 90 graus para a direita através de uma transformação rotativa.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à imagem. Essa transformação de entrada afeta a escolha de qual bitmap usar a partir da fonte. Também é levado em conta o glifo de saídaTransform.</param>
			/// <param name="Param_DpiX">Pontos por polegada ao longo do eixo X.</param>
			/// <param name="Param_DpiY">Pontos por polegada ao longo do eixo Y.</param>
			/// <param name="Param_Out_GlyphTransform">Retorna a transformação de saída, que se transforma do espaço do glifo para o mesmo espaço de saída que o mundoTransforme. Isso inclui o gliforgin de entrada, o deslocamento do glifo do glifo e quaisquer outras transformações necessárias.</param>
			/// <param name="Param_Out_GlyphImage">Retorna uma interface(ICarenD2D1Image) que contém um ponteiro para a image glifo recuperada.</param>
			CarenResult GetColorBitmapGlyphImage(
				CA_DWRITE_GLYPH_IMAGE_FORMATS Param_GlyphImageFormat,
				CA_D2D1_POINT_2F^ Param_GlyphOrigin,
				ICaren^ Param_FontFace,
				float Param_FontSize,
				UInt16 Param_GlyphIndex,
				Boolean Param_IsSideways,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				float Param_DpiX,
				float Param_DpiY,
				[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_GlyphTransform,
				[Out] ICarenD2D1Image^% Param_Out_GlyphImage);

			/// <summary>
			/// Recupera uma imagem do glifo SVG do cache glifo de cor. Se o cache ainda não contiver o recurso solicitado, ele será criado. Este método pode ser usado para estender a vida útil de uma imagem glifo mesmo depois de ser despejado do cache glifo de cor.
			/// </summary>
			/// <param name="Param_GlyphOrigin">Origem do glifo.</param>
			/// <param name="Param_FontFace">Uma interface(IDWriteFontFace)[SDK PENDENTE] que faz referência a uma face de fonte que contém o tipo de fonte, referências de arquivo apropriadas, dados de identificação de faces e vários dados de fontes, como métricas, nomes e contornos de glifos.</param>
			/// <param name="Param_FontSize">O tamanho da fonte especificado afeta o glifo de saídaTransforme, fazendo com que ele dimensione corretamente o glifo.</param>
			/// <param name="Param_GlyphIndex">Índice do glifo para recuperar.</param>
			/// <param name="Param_IsSideways">Se for verdade, especifica que os glifos são girados 90 graus para a esquerda e as métricas verticais são usadas. A escrita vertical é obtida especificando isSideways como verdadeiro e girando toda a corrida 90 graus para a direita através de uma transformação rotativa.</param>
			/// <param name="Param_WorldTransform">A transformação para aplicar à imagem.</param>
			/// <param name="Param_DefaultFillBrush">Descreve como a área é pintada.</param>
			/// <param name="Param_SvgGlyphStyle">Os valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
			/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor. Observe que isso não é o mesmo que a paletaIndex na estrutura DWRITE_COLOR_GLYPH_RUN, o que não é relevante para os glifos SVG.</param>
			/// <param name="Param_Out_GlyphTransform">Retorna transformação de saída, que se transforma do espaço do glifo para o mesmo espaço de saída que o mundoTransforme. Isso inclui o gliforgin de entrada, o deslocamento do glifo do glifo e quaisquer outras transformações necessárias.</param>
			/// <param name="Param_Out_GlyphImage">Retorna uma interface(ICarenD2D1CommandList) que contém um ponteiro para a imagem glifo recuperada.</param>
			CarenResult GetSvgGlyphImage(
				CA_D2D1_POINT_2F^ Param_GlyphOrigin,
				ICaren^ Param_FontFace,
				float Param_FontSize,
				UInt16 Param_GlyphIndex,
				Boolean Param_IsSideways,
				CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
				ICarenD2D1Brush^ Param_DefaultFillBrush,
				ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
				UInt32 Param_ColorPaletteIndex,
				[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_GlyphTransform,
				[Out] ICarenD2D1CommandList^% Param_Out_GlyphImage);
		};

		/// <summary>
		/// (ID2D1DeviceContext5) - Interface responsável por executar todas as mesmas funções da interface ICarenD2D1DeviceContext4, além de permitir a criação de contextos de cores e documentos Svg.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("68ADE011-AF56-4BB2-B054-6250B5172112")]
		public interface class ICarenD2D1DeviceContext5 : ICarenD2D1DeviceContext4
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um contexto de cor a partir de um tipo de espaço de cor DXGI. Só é válido usá-lo com o efeito de gerenciamento de cores no modo 'Melhor'.
			/// </summary>
			/// <param name="Param_EspacoCor">O espaço de cores para criar o contexto de cores a partir de.</param>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateColorContextFromDxgiColorSpace(
				CA_DXGI_COLOR_SPACE_TYPE Param_EspacoCor,
				[Out] ICarenD2D1ColorContext1^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um contexto de cores a partir de um perfil de cor simples. Só é válido usá-lo com o efeito de gerenciamento de cores no modo 'Melhor'.
			/// </summary>
			/// <param name="Param_SimpleProfile">O perfil de cor simples para criar o contexto de cores a partir de.</param>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateColorContextFromSimpleColorProfile(
				CA_D2D1_SIMPLE_COLOR_PROFILE^ Param_SimpleProfile,
				[Out] ICarenD2D1ColorContext1^% Param_Out_ColorContext);

			/// <summary>
			/// Cria um documento SVG a partir de um fluxo. 
			/// </summary>
			/// <param name="Param_InputXmlStream">Um fluxo de entrada contendo o documento SVG XML. Se for nulo, um documento vazio será criado.</param>
			/// <param name="Param_Viewportsize">Tamanho da visualização inicial do documento.</param>
			/// <param name="Param_Out_SvgDocumento">Retorna uma interface(ICarenD2D1SvgDocument) que contém um ponteiro para o novo documento SVG criado.</param>
			CarenResult CreateSvgDocument(
				ICarenStream^ Param_InputXmlStream,
				CA_D2D1_SIZE_F^ Param_Viewportsize,
				[Out] ICarenD2D1SvgDocument^% Param_Out_SvgDocumento);

			/// <summary>
			/// Desenha um documento SVG. 
			/// </summary>
			/// <param name="Param_SvgDocumento">O documento SVG para desenhar.</param>
			void DrawSvgDocument(ICarenD2D1SvgDocument^ Param_SvgDocumento);
		};

		/// <summary>
		/// (ID2D1DeviceContext6) - Interface responsável por executar todas as mesmas funções da interface ICarenD2D1DeviceContext5 existente, além disso permite o acesso ao método BlendImage.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("34E8E8EC-097A-4662-BB21-72A35B0D30D6")]
		public interface class ICarenD2D1DeviceContext6 : ICarenD2D1DeviceContext5
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Desenha uma imagem para o contexto do dispositivo usando o modo de mistura especificado. Os resultados são equivalentes ao uso do efeito Blendembutido do Direct2D. 
			/// </summary>
			/// <param name="Param_Imagem">A imagem a ser desenhada para o contexto do dispositivo.</param>
			/// <param name="Param_BlendMode">O modo de mistura a ser usado.</param>
			/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. O valor padrão é NULO.</param>
			/// <param name="Param_RetanguloImagem">O retângulo correspondente no espaço da imagem será mapeado para as origens dadas ao processar a imagem. O valor padrão é NULO.</param>
			/// <param name="Param_ModoInterpolacao">O modo de interpolação que será usado para dimensionar a imagem, se necessário. O valor padrão é D2D1_INTERPOLATION_MODE_LINEAR.</param>
			void BlendImage(
				ICarenD2D1Image^ Param_Imagem,
				CA_D2D1_BLEND_MODE Param_BlendMode,
				CA_D2D1_POINT_2F^ Param_TargetOffset,
				CA_D2D1_RECT_F^ Param_RetanguloImagem,
				CA_D2D1_INTERPOLATION_MODE Param_ModoInterpolacao);
		};

		/// <summary>
		/// (ID2D1Device) - Interface responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("E06463FD-19C3-45EA-96E5-0642133CE488")]
		public interface class ICarenD2D1Device : ICarenD2D1Resource
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Libera todos os recursos de renderização utilizados pelo Direct2D.
			/// </summary>
			/// <param name="Param_Miliseconds">Descarta apenas recursos que não foram usados por mais do que o tempo especificado em milissegundos. O padrão é de 0 milissegundos.</param>
			CarenResult ClearResources(UInt32 Param_Miliseconds);

			/// <summary>
			/// Cria um novo contexto de dispositivo a partir de um dispositivo Direct2D.
			/// O novo contexto do dispositivo não terá um bitmap de destino selecionado. O chamador deve criar e selecionar um bitmap como a superfície alvo do contexto.
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo">Retorna uma interface(ICarenD2D1DeviceContext) que contém um ponteiro para o novo contexto do dispositivo. </param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext^% Param_Out_ContextoDispositivo);

			/// <summary>
			/// Cria um objeto ICarenD2D1PrintControl que converte primitivos Direct2D armazenados no ICarenD2D1CommandList em uma representação de página fixa. O subsistema de impressão então consome os primitivos.
			/// </summary>
			/// <param name="Param_WicImagingFactory">Uma interface(ICarenWICImagingFactory) que representa a fábrica de imagens WIC.</param>
			/// <param name="Param_PrintDocumentPackage">Uma interface(IPrintDocumentPackageTarget)[NAO IMPLEMENTADA POR ESSA API] que representa o alvo de trabalho de impressão.</param>
			/// <param name="Param_PropsControlPrint">As opções a serem aplicadas ao controle de impressão.</param>
			/// <param name="Param_Out_PrintControl">Retorna uma interface(ICarenD2D1PrintControl) que contém um ponteiro para o objeto D2D1PrintControl.</param>
			CarenResult CreatePrintControl(
				ICaren^ Param_WicImagingFactory,
				ICaren^ Param_PrintDocumentPackage,
				CA_D2D1_PRINT_CONTROL_PROPERTIES^ Param_PropsControlPrint,
				[Out] ICarenD2D1PrintControl^% Param_Out_PrintControl);


			/// <summary>
			/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
			/// </summary>
			/// <param name="Param_Out_MaxSizeMemory">Retorna a quantidade máxima de memória de textura em bytes.</param>
			CarenResult GetMaximumTextureMemory([Out] UInt64% Param_Out_MaxSizeMemory);

			/// <summary>
			/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
			///  O Direct2D pode exceder a memória de textura máxima que você define com este método para um único quadro, se necessário, para renderizar o quadro.
			/// </summary>
			/// <param name="Param_MaxSizeMemory">A nova quantidade máxima de memória em bytes para a textura.</param>
			CarenResult SetMaximumTextureMemory(UInt64 Param_MaxSizeMemory);
		};

		/// <summary>
		/// (ID2D1Device1) - Interface responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device 
		/// existente. Ele também permite o controle da prioridade de renderização do dispositivo.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("CF31E136-7A7B-42F4-97ED-58824CC91D2A")]
		public interface class ICarenD2D1Device1 : ICarenD2D1Device
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera a prioridade de renderização atual do dispositivo.
			/// </summary>
			/// <param name="Param_Out_Prioridade">Retorna a prioridade de renderização atual do dispositivo.</param>
			void GetRenderingPriority(
				[Out] CA_D2D1_RENDERING_PRIORITY% Param_Out_Prioridade);

			/// <summary>
			/// Define a prioridade das operações de renderização Direct2D realizadas em qualquer contexto de dispositivo associado ao dispositivo.
			/// </summary>
			/// <param name="Param_Prioridade">A prioridade de renderização desejada para o dispositivo e contextos associados.</param>
			void SetRenderingPriority(CA_D2D1_RENDERING_PRIORITY Param_Prioridade);
		};

		/// <summary>
		/// (ID2D1Device2) - Interface responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device1
		/// existente. Ele também permite a criação de objetos ICarenD2D1DeviceContext2.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("8ECD31E5-834D-44D0-B229-C716E868F917")]
		public interface class ICarenD2D1Device2 : ICarenD2D1Device1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um novo ICarenD2D1DeviceContext2 a partir de um dispositivo Direct2D.
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo2">Retorna uma interface(ICarenD2D1DeviceContext2) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext2^% Param_Out_ContextoDispositivo2);

			/// <summary>
			/// Limpa todos os contextos do dispositivo que fazem referência a um determinado bitmap.
			/// </summary>
			/// <param name="Param_Bitmap">O bitmap, criado neste dispositivo, para o qual todos os contextos do dispositivo de referência serão limpos.</param>
			void FlushDeviceContexts(ICarenD2D1Bitmap^ Param_Bitmap);

			/// <summary>
			/// Retorna o dispositivo DXGI associado a este dispositivo Direct2D.
			/// </summary>
			/// <param name="Param_Out_DxgiDevice">Retorna uma interface(ICarenDXGIDevice) que contém um ponteiro para o dispositivo DXGI associado a este dispositivo Direct2D.</param>
			CarenResult GetDxgiDevice([Out] ICarenDXGIDevice^% Param_Out_DxgiDevice);
		};

		/// <summary>
		/// (ID2D1Device3) - Interface responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device2. 
		/// Ele também permite a criação de objetos ICarenD2D1DeviceContext3.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("895B32CF-9719-4349-8F9C-08B831E3F6D2")]
		public interface class ICarenD2D1Device3 : ICarenD2D1Device2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um novo ICarenD2D1DeviceContext3 a partir deste dispositivo Direct2D.
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo3">Retorna uma interface(ICarenD2D1DeviceContext3) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext3^% Param_Out_ContextoDispositivo3);

		};

		/// <summary>
		/// (ID2D1Device4) - Interface responsável por Representa um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device3. 
		/// Ele também permite a criação de objetos ICarenD2D1DeviceContext4.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("040418A6-3400-4852-9BAF-0E310946DAC0")]
		public interface class ICarenD2D1Device4 : ICarenD2D1Device3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um novo ICarenD2D1DeviceContext4 a partir deste dispositivo Direct2D.
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo4">Retorna uma interface(ICarenD2D1DeviceContext4) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext4^% Param_Out_ContextoDispositivo4);

			/// <summary>
			/// Obtém a capacidade máxima do cache Glyph colorido.
			/// </summary>
			/// <param name="Param_Out_MaximoInBytes">Retorna a capacidade máxima do cache glifo de cor em bytes.</param>
			void GetMaximumColorGlyphCacheMemory([Out] UInt64% Param_Out_MaximoInBytes);

			/// <summary>
			/// Define a capacidade máxima do cache Glyph de cor.
			/// O cache glifo de cor é usado para armazenar glifos de bitmap de cor e glifos SVG, permitindo um desempenho mais rápido se os mesmos glifos forem necessários novamente. A capacidade determina a quantidade de memória que o D2D 
			/// pode usar para armazenar glifos que o aplicativo ainda não faz referência. Se o aplicativo fizer referência a um glifo usando o ICarenD2D1DeviceContext4::GetColorBitmapGlyphImage ou o ICarenD2D1DeviceContext4::GetSvgGlyphImage, 
			/// depois de despejado, este glifo não conta para a capacidade de cache.
			/// </summary>
			/// <param name="Param_MaximumInBytes">A capacidade máxima do cache glifo colorido.</param>
			void SetMaximumColorGlyphCacheMemory(UInt64 Param_MaximumInBytes);

		};

		/// <summary>
		/// (ID2D1Device5) - Interface responsável por Representa um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device4. 
		/// Ele também permite a criação de objetos ICarenD2D1DeviceContext5.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("2171B533-790E-4862-AA7F-EFDE64869119")]
		public interface class ICarenD2D1Device5 : ICarenD2D1Device4
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um novo contexto de dispositivo sem um alvo inicialmente atribuído.
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo5">Retorna uma interface(ICarenD2D1DeviceContext5) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext5^% Param_Out_ContextoDispositivo5);
		};

		/// <summary>
		/// (ID2D1Device6) - Interface responsável por representar um domínio de recursos cujos objetos e contextos de dispositivos podem ser usados em conjunto. Esta interface executa todas as mesmas funções da interface ICarenD2D1Device5, 
		/// além disso permite a criação de objetos ICarenD2D1DeviceContext6.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9CB33160-3905-41E8-8377-2FFF9D2CB3B2")]
		public interface class ICarenD2D1Device6 : ICarenD2D1Device5
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// 
			/// </summary>
			/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
			/// <param name="Param_Out_ContextoDispositivo6">Retorna uma interface(ICarenD2D1DeviceContext6) que contém um ponteiro para o novo contexto do dispositivo.</param>
			CarenResult CreateDeviceContext(
				CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
				[Out] ICarenD2D1DeviceContext6^% Param_Out_ContextoDispositivo6);
		};

		/// <summary>
		/// (ID2D1Factory) - Interface responsável por criar recursos do Direct2D. A interface ICarenD2D1Factory é o ponto de partida para o uso do Direct2D; é o que você usa para criar outros recursos Direct2D que você pode usar para 
		/// desenhar ou descrever formas.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("0177991E-573F-4EF4-B548-8BE92F7C55BD")]
		public interface class ICarenD2D1Factory : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um alvo de renderização que atrai o contexto do dispositivo GDI (Windows Graphics Device Interface, interface do dispositivo gráfico do Windows).
			/// </summary>
			/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware. Para habilitar o objetivo 
			/// de renderização do contexto do dispositivo (DC) para funcionar com o GDI, defina o formato DXGI para DXGI_FORMAT_B8G8R8A8_UNORM e o modo alfa para D2D1_ALPHA_MODE_PREMULTIPLIED ou D2D1_ALPHA_MODE_IGNORE</param>
			/// <param name="Param_Out_DcRenderTarget">Retorna uma interface(ICarenD2D1DCRenderTarget) que contém um ponteiro para o novo alvo de renderização DC.</param>
			CarenResult CreateDCRenderTarget(
				CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
				[Out] ICarenD2D1DCRenderTarget^% Param_Out_DcRenderTarget);

			/// <summary>
			/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
			/// </summary>
			/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
			/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) que contém parâmetros de texto opcionais que indicam como o texto deve ser renderizado.</param>
			/// <param name="Param_Out_StateBlock">>Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
			CarenResult CreateDrawingStateBlock(
				CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
				ICaren^ Param_TextRenderingParams,
				[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock
			);

			/// <summary>
			/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
			/// </summary>
			/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
			/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
			CarenResult CreateDrawingStateBlock(
				CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
				[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock);

			/// <summary>
			/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
			/// </summary>
			/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
			CarenResult CreateDrawingStateBlock([Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock);

			/// <summary>
			/// Cria um alvo de renderização que atrai uma superfície DXGI (DirectX Graphics Infrastructure, infraestrutura gráfica do DirectX).
			/// </summary>
			/// <param name="Param_DxgiSurface">Uma interface(ICarenDXGISurface) para o qual o alvo de renderização irá desenhar.</param>
			/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
			/// <param name="Param_Out_RenderTarget">Retorna uma interface(ICarenD2D1RenderTarget) que contém um ponteiro para o objeto criado.</param>
			CarenResult CreateDxgiSurfaceRenderTarget(
				[Out] ICarenDXGISurface^% Param_DxgiSurface,
				CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
				[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget);

			/// <summary>
			/// Cria uma ICarenD2D1EllipseGeometry.
			/// </summary>
			/// <param name="Param_Ellipse">Um valor que descreve o ponto central, raio x e raio y da geometria da elipse.</param>
			/// <param name="Param_Out_EllipseGeometry">Retorna uma interface(ICarenD2D1EllipseGeometry) que contém um ponteiro para a nova geometria de elipse criada.</param>
			CarenResult CreateEllipseGeometry(
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
			CarenResult CreateGeometryGroup(
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
			CarenResult CreateHwndRenderTarget(
				CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
				CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ Param_PropsHwndRenderTarget,
				[Out] ICarenD2D1HwndRenderTarget^% Param_Out_HwndRenderTarget);

			/// <summary>
			/// Cria uma ICarenD2D1PathGeometry vazio.
			/// </summary>
			/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry) que contém um ponteiro para o Path Geometry criado pelo método.</param>
			CarenResult CreatePathGeometry(
				[Out] ICarenD2D1PathGeometry^% Param_Out_PathGeometry);

			/// <summary>
			/// Cria uma ICarenD2D1RectangleGeometry.
			/// </summary>
			/// <param name="Param_Retangulo">As coordenadas da geometria do retângulo.</param>
			/// <param name="Param_Out_RectangleGeometry">Retorna uma interface(ICarenD2D1RectangleGeometry) que contém um ponteiro para a geometria retângulo criada.</param>
			CarenResult CreateRectangleGeometry(
				CA_D2D1_RECT_F^ Param_Retangulo,
				[Out] ICarenD2D1RectangleGeometry^% Param_Out_RectangleGeometry);

			/// <summary>
			/// Cria uma ID2D1RoundedRectangleGeometry.
			/// </summary>
			/// <param name="Param_RoundedRectangle">As coordenadas e os raios de canto da geometria do retângulo arredondado.</param>
			/// <param name="Param_Out_RoundedRectangleGeometry">Retorna uma interface(ICarenD2D1RoundedRectangleGeometry) que contém um ponteiro  para a geometria do retângulo arredondado criada.</param>
			CarenResult CreateRoundedRectangleGeometry(
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
			CarenResult CreateStrokeStyle(
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
			CarenResult CreateTransformedGeometry(
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
			CarenResult CreateWicBitmapRenderTarget(
				ICaren^ Param_WicBitmapTarget,
				CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
				[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget);

			/// <summary>
			/// Recupera os pontos de desktop atuais por polegada (DPI). Para atualizar esse valor, ligue para o ReloadSystemMetrics.
			/// Use este método para obter o DPI do sistema ao definir valores de pixels físicos, como quando você especifica o tamanho de uma janela.
			/// </summary>
			/// <param name="Param_Out_DpiX">Retorna o DPI Horizontal da área de trabalho.</param>
			/// <param name="Param_Out_DpiY">Retorna o DPI Vertical da área de trabalho.</param>
			void GetDesktopDpi(
				[Out] float% Param_Out_DpiX,
				[Out] float% Param_Out_DpiY);

			/// <summary>
			/// Força o Factory a atualizar quaisquer padrões do sistema que possa ter mudado desde a criação do Factory.
			/// Você deve chamar este método antes de chamar o método GetDesktopDpi, para garantir que o DPI do sistema esteja atualizado.
			/// </summary>
			CarenResult ReloadSystemMetrics();
		};

		/// <summary>
		/// (ID2D1Factory1) - Interface responsável por criar recursos Direct2D.
		/// A interface ID2D1Factory1 é usada para criar dispositivos, registrar e não registrar efeitos e enumerar propriedades de efeitos. Os efeitos são registrados e não registrados globalmente. As APIs de registro são colocadas
		/// nesta interface por conveniência.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("97850A9F-90B6-43CA-BED1-2836EA7925DD")]
		public interface class ICarenD2D1Factory1 : ICarenD2D1Factory
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device.
			/// O dispositivo Direct2D define um domínio de recursos no qual um conjunto de objetos Direct2D e contextos de dispositivo Direct2D podem ser usados em conjunto. Cada chamada para CreateDevice retorna um objeto ICarenD2D1Device exclusivo, mesmo que você passe o mesmo ICarenDXGIDevice várias vezes.
			/// </summary>
			/// <param name="Param_DxgiDevice">Um objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device^% Param_Out_D2DDispositivo
			);

			/// <summary>
			/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
			/// </summary>
			/// <param name="Param_DescDrawingState">A estrutura de descrição do estado de desenho.</param>
			/// <param name="Param_TextRenderingParams">Uma ponteiro para a interface(IDWriteRenderingParams)[SDK PENDENTE] que contém os parametros de renderização do DirectWrite.</param>
			/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>
			CarenResult CreateDrawingStateBlock(
				CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescDrawingState,
				ICaren^ Param_TextRenderingParams,
				[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock
			);

			/// <summary>
			/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
			/// </summary>
			/// <param name="Param_DescDrawingState">A estrutura de descrição do estado de desenho.</param>
			/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>		
			CarenResult CreateDrawingStateBlock(
				CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescDrawingState,
				[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock
			);

			/// <summary>
			/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
			/// </summary>
			/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>
			CarenResult CreateDrawingStateBlock(
				[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock);

			/// <summary>
			/// Cria um novo objeto ID2D1GdiMetafile que você pode usar para reproduzir conteúdo metafilado.
			/// </summary>
			/// <param name="Param_MetaFileStream">Um objeto de fluxo que tem os dados do metafile.</param>
			/// <param name="Param_Out_GdiMetafile">Retorna uma interface(ID2D1GdiMetafile)[NAO IMPLEMENTADA PELA DLL] que contém um ponteiro para o novo objeto de metafile GDI recém-criado. O usuário deve inicializar a interface antes de chamar este método.</param>			
			CarenResult CreateGdiMetafile(
				ICarenStream^ Param_MetaFileStream,
				ICaren^ Param_Out_GdiMetafile
			);
			
			/// <summary>
			/// Cria um objeto ICarenD2D1PathGeometry1.
			/// </summary>
			/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry1) que contém um ponteiro para o nova Path Geometry criada.</param>		
			CarenResult CreatePathGeometry(
				[Out] ICarenD2D1PathGeometry1^% Param_Out_PathGeometry
			);

			/// <summary>
			/// Cria um objeto ICarenD2D1StrokeStyle1.
			/// </summary>
			/// <param name="Param_PropsStrokeStyle">As propriedades de estilo de traçado para serem aplicadas.</param>
			/// <param name="Param_Dashes">Uma variedade de larguras para os traços e lacunas.</param>
			/// <param name="Param_QuantidadeDashes">A quantidade de itens na matriz(Param_Dashes).</param>
			/// <param name="Param_Out_StrokeStyle">Retorna uma interface(ICarenD2D1StrokeStyle1) que contém um ponteiro para o novo Stroke Style criado.</param>
			CarenResult CreateStrokeStyle(
				CA_D2D1_STROKE_STYLE_PROPERTIES1^ Param_PropsStrokeStyle,
				cli::array<float>^ Param_Dashes,
				UInt32 Param_QuantidadeDashes,
				[Out] ICarenD2D1StrokeStyle1^% Param_Out_StrokeStyle
			);

			/// <summary>
			/// Recupera as propriedades de um efeito.
			/// Este método não pode ser usado para retornar as propriedades para qualquer efeito não visível ao ICarenD2D1DeviceContext::CreateEffect.
			/// </summary>
			/// <param name="Param_IdEfeito">A ID do efeito para recuperar propriedades de.</param>
			/// <param name="Param_Out_Propriedades">Retorna uma interface(ICarenD2D1Properties) que contém um ponteiro para a interface de propriedade que pode ser usado para consultar os metadados do efeito.</param>		
			CarenResult GetEffectProperties(
				String^ Param_IdEfeito,
				[Out] ICarenD2D1Properties^% Param_Out_Propriedades
			);

			/// <summary>
			/// Retorna as IDs de classe dos efeitos atualmente registrados e efeitos globais nesta Factory.
			/// O conjunto de IDs de classe será devolvido atomicamente pela API. O conjunto não será interrompido por outros tópicos que registram ou não registram efeitos.
			/// Se os (Param_Out_QuantidadeEfeitosRegistrados) for maior que o (Param_QuantidadeEfeitos), a matriz fornecida ainda será preenchida à capacidade com o conjunto atual de efeitos registrados. Este método retorna os CLSIDs para todos os efeitos globais e todos os efeitos registrados nesta fábrica.
			/// </summary>
			/// <param name="Param_Out_Efeitos">Retorna uma matriz com os CLSID dos efeitos. NULO se nenhum efeito for recuperado.</param>
			/// <param name="Param_QuantidadeEfeitos">A quantidade de itens que a matriz(Param_Out_Efeitos) vai retornar.</param>
			/// <param name="Param_Out_QuantidadeEfeitosRetornados">Retorna a quantidade real de efeitos retornados.</param>
			/// <param name="Param_Out_QuantidadeEfeitosRegistrados">Retorna a quantidade de efeitos atualmente registrados no sistema.</param>
			CarenResult GetRegisteredEffects(
				[Out] cli::array<String^>^% Param_Out_Efeitos,
				UInt32 Param_QuantidadeEfeitos,
				[Out] UInt32% Param_Out_QuantidadeEfeitosRetornados,
				[Out] UInt32% Param_Out_QuantidadeEfeitosRegistrados
			);

			/// <summary>
			/// Registra um efeito dentro da instância de fábrica com a propriedade XML especificada como um fluxo.
			/// Os efeitos Direct2D devem definir suas propriedades no momento do registro via XML de registro. Um efeito declara várias propriedades necessárias do sistema, e também pode declarar propriedades personalizadas.
			/// Além dos efeitos incorporados(built-in effects) registrados globalmente, esta API registra efeitos apenas para esta Factory e interfaces de contexto de dispositivos e dispositivos derivados.
			/// </summary>
			/// <param name="Param_ClassId">O identificador do efeito a ser registrado.</param>	
			/// <param name="Param_StreamPropertyXml">Um Stream para a lista das propriedades de efeito, tipos e metadados.</param>
			/// <param name="Param_Bindings">Uma variedade de propriedades e métodos. Isso vincula uma propriedade por nome a um método específico implementado pelo autor do efeito para lidar com a propriedade. O nome deve ser encontrado na (Param_StreamPropertyXml)</param>
			/// <param name="Param_QuantidadeBindings">O número de Bindings na matriz(Param_Bindings).</param>
			/// <param name="Param_CallbackEffectFactory">Um ponteiro para um Factory estatico para criar oefeito correspondente.</param>	
			CarenResult RegisterEffectFromStream(
				String^ Param_ClassId,
				ICarenStream^ Param_StreamPropertyXml,
				cli::array<CA_D2D1_PROPERTY_BINDING^>^ Param_Bindings,
				UInt32 Param_QuantidadeBindings,
				ICaren^ Param_CallbackEffectFactory
			);

			/// <summary>
			/// Registra um efeito dentro da instância de fábrica com a propriedade XML especificada como uma sequência.
			/// Os efeitos Direct2D devem definir suas propriedades no momento do registro via XML de registro. Um efeito declara várias propriedades necessárias do sistema, e também pode declarar propriedades personalizadas.
			/// Além dos efeitos incorporados(built-in effects) registrados globalmente, esta API registra efeitos apenas para esta Factory e interfaces de contexto de dispositivos e dispositivos derivados.
			/// </summary>
			/// <param name="Param_ClassId">O identificador do efeito a ser registrado.</param>	
			/// <param name="Param_PropertyXml">Uma String para uma lista das propriedades de efeito, tipos e metadados.</param>
			/// <param name="Param_Bindings">Uma variedade de propriedades e métodos. Isso vincula uma propriedade por nome a um método específico implementado pelo autor do efeito para lidar com a propriedade. O nome deve ser encontrado na (Param_PropertyXml)</param>
			/// <param name="Param_QuantidadeBindings">O número de Bindings na matriz(Param_Bindings).</param>
			/// <param name="Param_CallbackEffectFactory">Um ponteiro para um Factory estatico para criar oefeito correspondente.</param>	
			CarenResult RegisterEffectFromString(
				String^ Param_ClassId,
				String^ Param_PropertyXml,
				cli::array<CA_D2D1_PROPERTY_BINDING^>^ Param_Bindings,
				UInt32 Param_QuantidadeBindings,
				ICaren^ Param_CallbackEffectFactory
			);

			/// <summary>
			/// Desfaz o registro de um efeito dentro da instância da Factory que corresponde ao (Param_ClassId) fornecido.
			/// Para que o efeito seja totalmente cancelado, você deve chamar o (UnregisterEffect) do mesmo número de vezes que você registrou o efeito.
			/// O método (UnregisterEffect) cancela o registro apenas dos efeitos registrados na mesma Factory. Não pode ser usado para cancelar o registro de um efeito interno.
			/// </summary>
			/// <param name="Param_ClassId">O identificador do efeito não está registrado.</param>		
			CarenResult UnregisterEffect(
				String^ Param_ClassId
			);
		};

		/// <summary>
		/// (ID2D1Factory2) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device1.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("3ACF0478-F648-49F0-94A4-7CADEF600BDE")]
		public interface class ICarenD2D1Factory2 : ICarenD2D1Factory1
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device1.
			/// O dispositivo Direct2D define um domínio de recursos no qual um conjunto de objetos Direct2D e contextos de dispositivo Direct2D podem ser usados em conjunto. Cada chamada para CreateDevice retorna um objeto ICarenD2D1Device1 exclusivo, mesmo que você passe o mesmo ICarenDXGIDevice várias vezes.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device1.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device1) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device1^% Param_Out_D2DDispositivo
			);
		};

		/// <summary>
		/// (ID2D1Factory3) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device2.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("115A9A6B-00EC-433D-B72E-0AE71C567AC9")]
		public interface class ICarenD2D1Factory3 : ICarenD2D1Factory2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device2.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device2.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device2) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device2^% Param_Out_D2DDispositivo
			);
		};

		/// <summary>
		/// (ID2D1Factory4) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device3.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("9EEA35E7-91ED-4296-AB3F-F68F2E4C7D1F")]
		public interface class ICarenD2D1Factory4 : ICarenD2D1Factory3
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device3.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device3.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device3) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device3^% Param_Out_D2DDispositivo
			);
		};

		/// <summary>
		/// (ID2D1Factory5) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device4.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("E6AE4988-CCA1-4945-B144-DFA1DD40A025")]
		public interface class ICarenD2D1Factory5 : ICarenD2D1Factory4
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device4.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device4.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device4) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device4^% Param_Out_D2DDispositivo
			);
		};

		/// <summary>
		/// (ID2D1Factory6) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device5.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("EEE487B5-4FAD-468C-A6E9-6BF44F87AC2A")]
		public interface class ICarenD2D1Factory6 : ICarenD2D1Factory5
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device5.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device5.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device5) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device5^% Param_Out_D2DDispositivo
			);
		};

		/// <summary>
		/// (ID2D1Factory7) - Interface responsável por criar recursos Direct2D. Esta interface também permite a criação de objetos ICarenD2D1Device6.
		/// </summary>
		[CategoryAttribute("Interface D2D")]
		[Guid("F4AAD5BE-CE1F-408F-8715-ED3FFF689449")]
		public interface class ICarenD2D1Factory7 : ICarenD2D1Factory6
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Cria um objeto ICarenD2D1Device6.
			/// </summary>
			/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device6.</param>
			/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device6) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>	
			CarenResult CreateDevice(
				ICarenDXGIDevice^ Param_DxgiDevice,
				[Out] ICarenD2D1Device6^% Param_Out_D2DDispositivo
			);
		};		
	}
}
