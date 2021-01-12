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
#include "SDK_Windows.h"

///////////////////////////////////
//WIC - WINDOWS IMAGING COMPONENT//
///////////////////////////////////

//Importa os namespaces do SDK BASE do sistema.

using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Constantes;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::Windows;

//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace WIC
	{
		/// <summary>
		/// (IWICBitmapLock) - Interface responsável por expor métodos que suportam o método Lock.
		/// O lock bitmap é simplesmente uma abstração para uma janela de memória retangular no bitmap. Para o caso mais simples, um bitmap de memória do sistema, este é simplesmente 
		/// um ponteiro para o canto superior esquerdo do retângulo e um valor de pitch. Para liberar o conjunto de bloqueio exclusivo pelo método Lock e o objeto ICarenWICBitmapLock 
		/// associado, ligue para ICaren::LiberarReferencia no objeto ICarenWICBitmapLock.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("AF334370-F7CF-4767-8818-3A53D0E75463")]
		public interface class ICarenWICBitmapLock : ICaren
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
			/// Obtém o ponteiro para o pixel superior esquerdo no retângulo bloqueado.
			/// </summary>
			/// <param name="Param_Out_BufferSize">Retorna o tamanho do Buffer.</param>
			/// <param name="Param_Out_BufferData">Retorna uma interface(ICarenBuffer) que contém o ponteiro para o buffer.</param>
			CarenResult GetDataPointer(
				[Out] UInt32% Param_Out_BufferSize,
				[Out] ICarenBuffer^% Param_Out_BufferData);

			/// <summary>
			/// Obtém o formato de pixel para a área bloqueada dos pixels. Isso pode ser usado para calcular o número de bytes por pixel na área bloqueada.
			/// </summary>
			/// <param name="Param_Out_FormatoPixel">Recebe o formato de pixel GUID da área bloqueada.</param>
			CarenResult GetPixelFormat([Out] String^% Param_Out_FormatoPixel);

			/// <summary>
			/// Recupera a largura e a altura, em pixels, do retângulo bloqueado. 
			/// </summary>
			/// <param name="Param_Out_Width">Recebe a Largura do retângulo bloqueado.</param>
			/// <param name="Param_Out_Height">Recebe a Altura do retângulo bloqueado.</param>
			CarenResult GetSize(
				[Out] UInt32% Param_Out_Width,
				[Out] UInt32% Param_Out_Height);

			/// <summary>
			/// Fornece acesso ao valor do Stride para a memória.
			/// Note que o valor do Stride é específico para o ICarenWICBitmapLock, não para o bitmap. Por exemplo, dois bloqueios consecutivos no mesmo retângulo de um bitmap podem 
			/// retornar diferentes ponteiros e valores de Stride, dependendo da implementação interna.
			/// </summary>
			/// <param name="Param_Out_Stride">Retorna o valor do Stride para memoria.</param>
			CarenResult GetStride([Out] UInt32% Param_Out_Stride);
		};

		/// <summary>
		/// (IWICBitmapSource) - Interface responsável por expor métodos que se referem a uma fonte da qual os pixels são recuperados, mas não podem ser gravados novamente.
		/// Esta interface fornece uma maneira comum de acessar e vincular bitmaps, decodificadores, conversores de formato e scalers. Os componentes que implementam essa interface 
		/// podem ser conectados em um gráfico para extrair dados de imagem. Esta interface define apenas a noção de legibilidade ou ser capaz de produzir pixels. Modificar ou escrever
		/// para um bitmap é considerado uma especialização específica para bitmaps que têm armazenamento e é definida na interface descendente ICarenWICBitmap.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("5FF77727-D801-4EB9-AFD9-36D2579A8806")]
		public interface class ICarenWICBitmapSource : ICaren
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
			/// Recupera a tabela de cores para formatos de pixel indexados. 
			/// </summary>
			/// <param name="Param_Palette">Uma ICarenWICPalette. Uma paleta pode ser criada usando o método ICarenWICImagingFactory::CreatePalette.</param>
			CarenResult CopyPalette(ICaren^ Param_Palette);

			/// <summary>
			/// Instrui o objeto a produzir pixels. CopyPixels é uma das duas principais rotinas de processamento de imagens(a outra é Lock), acionando o processamento real.Ele instrui o 
			/// objeto a produzir pixels de acordo com seu algoritmo - isso pode envolver a decodificação de uma parte de um JPEG armazenado em disco, a cópia de um bloco de memória ou a 
			/// computação analítica de um gradiente complexo.O algoritmo é completamente dependente do objeto que implementa a interface.
			/// </summary>
			/// <param name="Param_RetanguloCopy">O retângulo para copiar. Um valor NULO especifica todo o bitmap.</param>
			/// <param name="Param_Stride">O Stride do bitmap</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer.</param>
			/// <param name="Param_Buffer">Um ponteiro para o buffer.</param>
			CarenResult CopyPixels(
				CA_WICRect^ Param_RetanguloCopy,
				UInt32 Param_Stride,
				UInt32 Param_TamanhoBuffer,
				ICarenBuffer^ Param_Buffer);
			
			/// <summary>
			/// Recupera o formato de pixel da fonte bitmap. O formato de pixel retornado por este método não é necessariamente o formato de pixel que a imagem é armazenada como. O codec pode 
			/// executar uma conversão de formato do formato pixel de armazenamento para um formato de pixel de saída.
			/// </summary>
			/// <param name="Param_Out_FormatoPixel">Recebe o GUID do formato de pixel em que o bitmap está armazenado.</param>
			CarenResult GetPixelFormat([Out] String^% Param_Out_FormatoPixel);

			/// <summary>
			/// Recupera a taxa de amostragem entre pixels e medições do mundo físico. 
			/// Alguns formatos, como GIF e ICO, não possuem suporte completo ao DPI. Para GIF, este método calcula os valores de DPI a partir da proporção, utilizando um DPI base de (96,0, 96,0).
			///  O formato ICO não suporta DPI em tudo, e o método sempre retorna (96.0.96.0) para imagens de ICO. Além disso, o próprio WIC não transforma imagens com base nos valores de DPI em uma 
			/// imagem. Cabe ao interlocutor transformar uma imagem baseada na resolução devolvida.
			/// </summary>
			/// <param name="Param_Out_DpiX">Recebe a resolução dpi do eixo X.</param>
			/// <param name="Param_Out_DpiY">Recebe a resolução dpi do eixo Y.</param>
			CarenResult GetResolution(
				[Out] double% Param_Out_DpiX,
				[Out] double% Param_Out_DpiY);

			/// <summary>
			/// Recupera a largura e a altura do bitmap. 
			/// </summary>
			/// <param name="Param_Out_PixelWidthBitmap">Recebe a Largura do pixel do bitmap.</param>
			/// <param name="Param_Out_PixelHeightBitmap">Recebe a Altura do pixel do bitmap.</param>
			CarenResult GetSize(
				[Out] UInt32% Param_Out_PixelWidthBitmap,
				[Out] UInt32% Param_Out_PixelHeightBitmap);
		};

		/// <summary>
		/// (IWICPalette) - Interface responsável por  expor métodos para acessar e criar uma tabela de cores, principalmente para formatos de pixel indexados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("B30C51E1-B2E6-461F-858A-3D8C5D9505DC")]
		public interface class ICarenWICPalette : ICaren
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
			/// Recupera o número de cores na tabela de cores. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Recebe o número de cores na tabela de cores.</param>
			CarenResult GetColorCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Obtéem a matriz de cores fornecida com as cores da tabela de cores internas. A matriz de cores deve ser dimensionada de acordo com os resultados de retorno do GetColorCount. 
			/// </summary>
			/// <param name="Param_Quantidade">O tamanho da matriz (Param_Out_Cores).</param>
			/// <param name="Param_Out_Cores">Uma matriz que recebe as cores da paleta.</param>
			/// <param name="Param_Out_CoresReais">Retorna o tamanho real necessário para obter as cores da paleta.</param>
			CarenResult GetColors(
				UInt32 Param_Quantidade,
				[Out] cli::array<UInt32>^% Param_Out_Cores,
				[Out] UInt32% Param_Out_CoresReais);

			/// <summary>
			/// Recupera o WICBitmapPaletteType que descreve a paleta. 
			/// WICBitmapPaletteCustom é usado para paletas inicializadas tanto do InitializeCustom quanto do InitializeFromBitmap. Não há distinção entre paletas otimizadas e personalizadas.
			/// </summary>
			/// <param name="Param_Out_PaletteType">Recebe o tipo de paleta do bimtap.</param>
			CarenResult GetType([Out] CA_WICBitmapPaletteType% Param_Out_PaletteType);

			/// <summary>
			/// Indica se a paleta contém uma entrada não-opaca (ou seja, uma entrada com um alfa menor que 1).
			/// Vários formatos de imagem suportam alfa de diferentes maneiras. PNG tem suporte alfa completo, suportando entradas de paleta parcialmente transparentes. O GIF armazena cores 
			/// como 24bpp, sem alfa, mas permite que uma entrada de paleta seja especificada como totalmente transparente. Se uma paleta tiver várias entradas totalmente transparentes (0x00RRGGBB),
			///  o GIF usará a última como seu índice transparente.
			/// </summary>
			/// <param name="Param_Out_HasAlfa">Recebe TRUE se a paleta contiver uma cor transparente; caso contrário, FALSE.</param>
			CarenResult HasAlpha([Out] Boolean% Param_Out_HasAlfa);

			/// <summary>
			/// Inicializa uma paleta para as entradas de cores personalizadas fornecidas. Se for necessária uma cor transparente, forneça-a como parte das entradas personalizadas. 
			/// Para adicionar um valor transparente à paleta, seu valor alfa deve ser 0 (0x00RRGGBB).
			/// A contagem de entradas é limitada a 256.
			/// </summary>
			/// <param name="Param_Cores">A matriz de cores.</param>
			/// <param name="Param_Quantidade">O número de cores em (Param_Cores).</param>
			CarenResult InitializeCustom(
				cli::array<UInt32>^ Param_Cores,
				UInt32 Param_Quantidade);

			/// <summary>
			///  Inicializa uma paleta usando um valor otimizado computado com base no bitmap de referência.
			/// A paleta resultante contém o número especificado de cores que melhor representam as cores presentes no bitmap. O algoritmo opera no valor opaco de cor RGB de cada pixel 
			/// no bitmap de referência e, portanto, ignora quaisquer valores alfa. Se for necessária uma cor transparente, defina o parâmetro (Param_AdicionarCorTransparente) para TRUE 
			/// e uma cor menos otimizada será calculada, reduzindo a (Param_Quantidade), e uma entrada de cor totalmente transparente será adicionada.
			/// </summary>
			/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) que contém um ponteiro para a fonte do bitmap.</param>
			/// <param name="Param_Quantidade">O número de cores para inicializar a paleta com.</param>
			/// <param name="Param_AdicionarCorTransparente">Um valor para indicar se deve adicionar uma cor transparente.</param>
			CarenResult InitializeFromBitmap(
				ICarenWICBitmapSource^ Param_FonteBitmap,
				UInt32 Param_Quantidade,
				Boolean Param_AdicionarCorTransparente);

			/// <summary>
			/// Inicialize a paleta com base em uma determinada paleta. 
			/// </summary>
			/// <param name="Param_Palette">Uma interface(ICarenWICPalette) que contém um ponteiro para paleta de origem.</param>
			CarenResult InitializeFromPalette(ICarenWICPalette^ Param_Palette);

			/// <summary>
			/// Inicializa a paleta para uma das paletas pré-definidas especificadas pelo WICBitmapPaletteType e, opcionalmente, adiciona uma cor transparente. 
			/// Se uma cor transparente for adicionada a uma paleta, a paleta não será mais predefinida e é devolvida como WICBitmapPaletteTypeCustom. Para paletas com menos de 256 entradas, 
			/// a entrada transparente é adicionada ao final da paleta (ou seja, uma paleta de 16 cores torna-se uma paleta de 17 cores). Para paletas com 256 cores, a entrada transparente 
			/// da paleta substituirá a última entrada na paleta pré-definida.
			/// </summary>
			/// <param name="Param_PaletteType">O tipo de paleta pré-definida desejada.</param>
			/// <param name="Param_AdicionarCorTransparente">A cor opcional transparente para adicionar à paleta. Se não for necessária uma cor transparente, use 0. Ao inicializar para uma 
			/// paleta em escala de cinza ou preto e branco, defina este 
			/// parâmetro como FALSE.</param>
			CarenResult InitializePredefined(
				CA_WICBitmapPaletteType Param_PaletteType,
				Boolean Param_AdicionarCorTransparente);

			/// <summary>
			/// Recupera um valor que descreve se a paleta é em preto e branco. Uma paleta é considerada em preto e branco apenas se contiver exatamente duas entradas, uma preta completa 
			/// (0xFF0000000) e uma branca completa (0xFFFFFFF).
			/// </summary>
			/// <param name="Param_Out_PretoBranco">Recebe um valor booleano que indica se a paleta é preto e branco. TRUE indica que a paleta é em preto e branco; caso contrário, FALSO.</param>
			CarenResult IsBlackWhite([Out] Boolean% Param_Out_PretoBranco);

			/// <summary>
			/// Recupera um valor que descreve se uma paleta é escala de cinza. 
			/// Uma paleta é considerada escala de cinza somente se, para cada entrada, o valor alfa for 0xFF e os valores vermelho, verde e azul coincidirem.
			/// </summary>
			/// <param name="Param_Out_EscalaCinza">Recebe um valor booleano que indica se a paleta é escala de cinza. TRUE indica que a paleta é escala de cinza; caso contrário FALSO.</param>
			CarenResult IsGrayscale([Out] Boolean% Param_Out_EscalaCinza);
		};

		/// <summary>
		/// (IWICBitmap) - Interface responsável por definir métodos que adicionam o conceito de gravabilidade e representações estáticas na memória de bitmaps ao ICarenWICBitmapSource.
		/// O ICarenWICBitmap herda do ICarenWICBitmapSource e, portanto, também herda o método CopyPixels. Quando os pixels precisam ser movidos para um novo local de memória, o 
		/// CopyPixels é frequentemente o mais eficiente. Devido à representação de memória interna implícita pelo IWICBitmap, a modificação e o processamento no local usando o Lock é mais
		///  eficiente do que o CopyPixels, geralmente reduzindo a um simples acesso de ponteiro diretamente à memória de propriedade do bitmap em vez de uma cópia. Isso é contrastado com 
		/// bitmaps processuais que implementam apenas CopyPixels porque não há representação interna de memória e seria necessário criar-se sob demanda para satisfazer uma chamada ao Lock.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("B85EC386-CAC2-45B0-84F8-F1236B1885C2")]
		public interface class ICarenWICBitmap : ICarenWICBitmapSource
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
			/// Fornece acesso a uma área retangular do bitmap. 
			/// Os bloqueios são exclusivos para escrita, mas podem ser compartilhados para leitura. Você não pode chamar CopyPixels enquanto o ICarenWICBitmap está bloqueado para gravação. 
			/// Isso retornará um erro, pois os bloqueios são exclusivos.
			/// </summary>
			/// <param name="Param_RetanguloLock">O retângulo a ser acessado.</param>
			/// <param name="Param_Flags">O modo de acesso que deseja obter para o bloqueio. Esta é uma combinação bitwise de CA_WICBitmapLockFlags para ler, escrever ou ler e escrever acesso.</param>
			/// <param name="Param_Out_LockMem">Retorna uma interface(ICarenWICBitmapLock) que contém um ponteiro para o local da memória bloqueada.</param>
			CarenResult Lock(
				CA_WICRect^ Param_RetanguloLock,
				CA_WICBitmapLockFlags Param_Flags,
				[Out] ICarenWICBitmapLock^% Param_Out_LockMem);

			/// <summary>
			/// Fornece acesso para modificações de paleta. 
			/// </summary>
			/// <param name="Param_Palette">A paleta para usar para alteração.</param>
			CarenResult SetPalette(ICarenWICPalette^ Param_Palette);

			/// <summary>
			/// Altera a resolução física da imagem. 
			/// </summary>
			/// <param name="Param_DpiX">A resolução Horizontal.</param>
			/// <param name="Param_DpiY">A resolução Vertical.</param>
			CarenResult SetResolution(
				double Param_DpiX,
				double Param_DpiY);
		};

		/// <summary>
		/// (IWICBitmapClipper) - Interface responsável por expor métodos que produzem uma versão cortada do bitmap de entrada para uma região retangular especificada de interesse.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("D8FB4FAA-8710-4D4C-892C-356454FDF4A9")]
		public interface class ICarenWICBitmapClipper : ICarenWICBitmapSource
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
			/// Inicializa o clipper de bitmap com os parâmetros fornecidos.
			/// </summary>
			/// <param name="Param_Source">A fonte de bitmap de entrada.</param>
			/// <param name="Param_RectClip">O retângulo da fonte bitmap para cortar.</param>
			CarenResult Initialize(
				ICarenWICBitmapSource^ Param_Source,
				CA_WICRect^ Param_RectClip);
		};

		/// <summary>
		/// (IWICStream) - Interface responsável por representar um fluxo WIC para referenciar conteúdo de imagem e metadados.
		/// Espera-se que os decodificados e os manipuladores de metadados criem sub-fluxos de qualquer fluxo que eles seguram ao entregar o controle de metadados incorporados para outro manipulador de metadados. 
		/// Se o fluxo não estiver restrito, use MAXLONGLONG como o tamanho máximo e deslocamento 0.
		/// Os métodos de interface ICarenWICStream não permitem que você forneça uma opção de compartilhamento de arquivos. Para criar um fluxo de arquivos para uma imagem, use a função SHCreateStreamOnFileEx. 
		/// Esse fluxo pode então ser usado para criar um ICarenWICBitmapDecoder usando o método (ICarenWICImagingFactory::CreateDecoderFromStream ).
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("0716152A-1EA2-4D90-A178-A1B952C73384")]
		public interface class ICarenWICStream : ICarenStream
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
			/// Inicializa um fluxo de um arquivo específico.
			/// </summary>
			/// <param name="Param_NomeArquivo">O arquivo usado para inicializar o fluxo.</param>
			/// <param name="Param_TipoAcesso">O modo de acesso ao arquivo desejado. </param>
			CarenResult InitializeFromFilename(
				String^ Param_NomeArquivo,
				CA_ACCESS_RIGHTS Param_TipoAcesso);

			/// <summary>
			/// Inicializa um fluxo de outro fluxo. Os direitos de acesso são herdados do fluxo subjacente.
			/// </summary>
			/// <param name="Param_Fluxo">O fluxo para inicializar este.</param>
			CarenResult InitializeFromIStream(ICarenStream^ Param_Fluxo);

			/// <summary>
			/// Inicializa o fluxo como um subfluxo de outro fluxo. O fluxo funciona com sua própria posição de fluxo, independente do fluxo subjacente, mas restrito a uma região. Todas as posições 
			/// de busca são relativas à sub-região. É permitido, embora não recomendado, ter vários sub streams graváveis ​​sobrepondo o mesmo intervalo.
			/// </summary>
			/// <param name="Param_Fluxo">O fluxo de entrada.</param>
			/// <param name="Param_Offset">O offset do fluxo usado para criar o novo fluxo.</param>
			/// <param name="Param_MaxSize">O tamanho máximo do fluxo.</param>
			CarenResult InitializeFromIStreamRegion(
				ICarenStream^ Param_Fluxo,
				UInt64 Param_Offset,
				UInt64 Param_MaxSize);

			/// <summary>
			/// Inicializa um fluxo para tratar um bloco de memória como um fluxo. O fluxo não pode crescer além do tamanho do buffer.
			/// Este método deve ser evitado sempre que possível. O responsável pela chamada é responsável por garantir que o bloco de memória seja válido por toda a vida do fluxo ao usar InitializeFromMemory. 
			/// Uma solução alternativa para esse comportamento é criar um ICarenStream e usar InitializeFromIStream para criar o ICarenWICStream.
			/// </summary>
			/// <param name="Param_MemoryBuffer">Uma interface(ICarenBuffer) que contém um ponteiro para o bloco de memória que será usado para iniciar o fluxo.</param>
			/// <param name="Param_BufferSize">O tamanho do buffer.</param>
			CarenResult InitializeFromMemory(
				ICarenBuffer^ Param_MemoryBuffer,
				UInt32 Param_BufferSize);
		};

		/// <summary>
		/// (IWICStreamProvider) - Interface responsável por expor métodos para um provedor de fluxo.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("F462B484-FA6A-4681-B763-44BFA56503CA")]
		public interface class ICarenWICStreamProvider : ICaren
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
			/// Obtém as opções de persistência usadas ao inicializar o componente com um fluxo.
			/// </summary>
			/// <param name="Param_Out_PersistOptions">Retorna as opções de persistência usadas ao inicializar o componente com um fluxo. Se nenhum for fornecido, o WICPersistOptionDefault será devolvido.</param>
			CarenResult GetPersistOptions([Out] CA_WICPersistOptions% Param_Out_PersistOptions);

			/// <summary>
			/// Recebe o GUID do fornecedor preferido.
			/// </summary>
			/// <param name="Param_Out_Guid">Retorna o GUID do fornecedor preferido.</param>
			CarenResult GetPreferredVendorGUID([Out] String^% Param_Out_Guid);

			/// <summary>
			/// Obtém o fluxo mantido pelo componente.
			/// </summary>
			/// <param name="Param_Out_Fluxo">Retorna uma interface(ICarenStream) que contém um ponteiro para o fluxo mantido pelo componente.</param>
			CarenResult GetStream([Out] ICarenStream^% Param_Out_Fluxo);

			/// <summary>
			/// Informa ao componente que o conteúdo do stream que ele está segurando pode ter mudado.O componente deve responder sujando qualquer informação em cache do fluxo.
			/// </summary>
			CarenResult RefreshStream();
		};

		/// <summary>
		/// (IWICComponentInfo) - Interface responsável por expor métodos que fornecem informações sobre componentes.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("170E40F6-BD5E-4480-8983-B5D297E5FE16")]
		public interface class ICarenWICComponentInfo : ICaren
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
			/// Recupera o nome do autor do componente. Se (Param_SizeAutorString) for 0 e (Param_Ref_Autor) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_SizeAutorString">O tamanho da String (Param_Ref_Autor).</param>
			/// <param name="Param_Ref_Autor">Recebe o nome do autor do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da instalação.
			///  Para componentes embutidos, essas Strings estão sempre em inglês.</param>
			/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome dos autores do componente. O nome do autor é opcional; se um nome autor não for especificado pelo componente,
			///  o comprimento devolvido será 0.</param>
			CarenResult GetAuthor(
				UInt32 Param_SizeAutorString,
				String^% Param_Ref_Autor,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o identificador de classe do componente (CLSID) 
			/// </summary>
			/// <param name="Param_Out_CLSID">Recebe o CLSID do componente.</param>
			CarenResult GetCLSID([Out] String^% Param_Out_CLSID);

			/// <summary>
			/// Recupera o CA_WICComponentType do componente. 
			/// </summary>
			/// <param name="Param_Out_Type">Recebe um enum CA_WICComponentType que define o tipo do componente.</param>
			CarenResult GetComponentType([Out] CA_WICComponentType% Param_Out_Type);

			/// <summary>
			/// Recupera o nome amigável do componente, que é um nome de exibição legível por humanos para o componente.
			/// Se (Param_SizeNomeString) for 0 e (Param_Ref_NomeAmigavel) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_SizeNomeString">O tamanho da String em (Param_Ref_NomeAmigavel).</param>
			/// <param name="Param_Ref_NomeAmigavel">Recebe o nome amigável do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da 
			/// instalação. Para componentes embutidos, essas cordas 
			/// estão sempre em inglês.</param>
			/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome amigável do componente.</param>
			CarenResult GetFriendlyName(
				UInt32 Param_SizeNomeString,
				String^% Param_Ref_NomeAmigavel,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o status de assinatura do componente. A assinatura não é usada pelo WIC. Portanto, todos os componentes WICComponentSigned. Esta função pode ser usada para 
			/// determinar se um componente não possui nenhum componente 
			/// binário ou foi adicionado à lista de componentes desabilitados no registro.
			/// </summary>
			/// <param name="Param_Out_Status">Retorna um enum que recebe o status do componente.</param>
			CarenResult GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status);

			/// <summary>
			/// Recupera a versão de especificação do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão spec.
			/// Se (Param_SizeSpecString) for 0 e (Param_Ref_SpecVersion) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_SizeSpecString">O tamanho da String em (Param_Ref_SpecVersion).</param>
			/// <param name="Param_Ref_SpecVersion">Retorna uma string que contém uma sequência de cultura invariente da versão de especificação do componente. O formulário de versão 
			/// é NN.NN.NN.NN.</param>
			/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão de especificação do componente. A versão de especificação é opcional; se um valor não for especificado
			///  pelo componente, o comprimento devolvido será 0.</param>
			CarenResult GetSpecVersion(
				UInt32 Param_SizeSpecString,
				String^% Param_Ref_SpecVersion,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o fornecedor GUID. 
			/// </summary>
			/// <param name="Param_Out_GuidVendor">Recebe o guid do fornecedor do componente.</param>
			CarenResult GetVendorGUID([Out] String^% Param_Out_GuidVendor);

			/// <summary>
			/// Recupera a versão do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão.
			/// Se (Param_SizeVersionString) for 0 e (Param_Ref_Version) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_SizeVersionString">O tamanho da String em (Param_Ref_Version).</param>
			/// <param name="Param_Ref_Version">Recebe uma sequência de cultura invariante da versão do componente.</param>
			/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão do componente. A versão é opcional; se um valor não for especificado pelo componente, o comprimento
			///  devolvido será 0.</param>
			CarenResult GetVersion(
				UInt32 Param_SizeVersionString,
				String^% Param_Ref_Version,
				[Out] UInt32% Param_Out_SizeAtual);
		};

		/// <summary>
		/// (IWICBitmapCodecInfo) - Interface responsável por expor métodos que fornecem informações sobre um codec específico.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("7022A879-8EF6-4600-8A7E-AB840020F393")]
		public interface class ICarenWICBitmapCodecInfo : ICarenWICComponentInfo
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
			/// Recupera um valor indicando se o codec suporta animação. 
			/// </summary>
			/// <param name="Param_Out_SuporteAnimacao">Recebe TRUE se o codec suporta imagens com informações de cronometragem; caso contrário, FALSO.</param>
			CarenResult DoesSupportAnimation([Out] Boolean% Param_Out_SuporteAnimacao);

			/// <summary>
			/// Recupera um valor indicando se o codec suporta chromakeys. 
			/// </summary>
			/// <param name="Param_Out_SuporteChromakey">Recebe TRUE se o codec suportar chromakeys; caso contrário, FALSO.</param>
			CarenResult DoesSupportChromakey([Out] Boolean% Param_Out_SuporteChromakey);

			/// <summary>
			/// Recupera um valor indicando se o codec suporta formatos sem perdas. 
			/// </summary>
			/// <param name="Param_Out_SuporteLossLess">Recebe TRUE se o codec suportar formatos sem perdas; caso contrário, FALSO.</param>
			CarenResult DoesSupportLossless([Out] Boolean% Param_Out_SuporteLossLess);

			/// <summary>
			/// Recupera um valor indicando se o codec suporta imagens de vários quadros. 
			/// </summary>
			/// <param name="Param_Out_SuporteMultiframe">Recebe TRUE se o codec suportar imagens de vários quadros; caso contrário, FALSO.</param>
			CarenResult DoesSupportMultiframe([Out] Boolean% Param_Out_SuporteMultiframe);

			/// <summary>
			/// Recupera o número da versão de manangement de cor que o codec suporta. 
			/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo 
			/// da versão de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_VersaoColorManagement) definido para NULO. Esta chamada define (Param_Out_SizeAtual)
			///  para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetColorManagementVersion com (Param_Size) definida para o tamanho do 
			/// buffer e (Param_Ref_VersaoColorManagement) definido para um buffer do tamanho apropriado recuperará os formatos de pixel
			/// </summary>
			/// <param name="Param_Size">O tamanho do buffer da versão. Use na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Ref_VersaoColorManagement">Recebe o número da versão de gerenciamento de cores. Use na primeira chamada para determinar o tamanho do buffer necessário</param>
			/// <param name="Param_Out_SizeAtual">Recebe tamanho real do buffer necessário para recuperar o número completo da versão de gerenciamento de cores.</param>
			CarenResult GetColorManagementVersion(
				UInt32 Param_Size,
				String^% Param_Ref_VersaoColorManagement,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o guid do contêiner associado ao codec.
			/// </summary>
			/// <param name="Param_Out_GuidFormatoContainer">Recebe o GUID do formato do container.</param>
			CarenResult GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer);

			/// <summary>
			/// Recupera o nome da fabricação do dispositivo associada ao codec.
			/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo da versão
			/// de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_ModelosDispositivo) definido para NULO. Esta chamada define (Param_Out_SizeAtual) 
			/// para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetDeviceManufacturer com (Param_Size) 
			/// definido para o tamanho do buffer e 
			/// (Param_Ref_ModelosDispositivo) definido para um buffer do tamanho apropriado recuperará os formatos de pixel.
			/// </summary>
			/// <param name="Param_Size">O tamanho do nome da fabricação do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário</param>
			/// <param name="Param_Ref_FabricanteDispositivo">Recebe o nome da fabricação do dispositivo. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar o nome do fabricante do dispositivo.</param>
			CarenResult GetDeviceManufacturer(
				UInt32 Param_Size,
				String^% Param_Ref_FabricanteDispositivo,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera uma lista delimitada de vírgula de modelos de dispositivos associados ao codec.
			/// Defina (Param_Size) para 0 e (Param_Ref_ModelosDispositivo) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_ModelosDispositivo)
			/// que deve ser definida em (Param_Size).
			/// </summary>
			/// <param name="Param_Size">O tamanho do buffer dos modelos do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Ref_ModelosDispositivo">Recebe uma lista delimitada de vírgula de nomes de modelos de dispositivos associados ao codec. Use NULO na primeira chamada para
			///  determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os nomes dos modelos do dispositivo.</param>
			CarenResult GetDeviceModels(
				UInt32 Param_Size,
				String^% Param_Ref_ModelosDispositivo,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera uma lista delimitada de vírgula das extensões de nome do arquivo associadas ao codec. A extensão padrão de um codificador de imagem é o primeiro item 
			/// da lista de extensões devolvidas. Defina (Param_Size) para 0 e (Param_Ref_ExtensoesArquivos) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário 
			/// do buffer(Param_Ref_ExtensoesArquivos) que deve ser definida em (Param_Size).
			/// </summary>
			/// <param name="Param_Size">O tamanho do buffer de extensão do nome do arquivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Ref_ExtensoesArquivos">Recebe uma lista delimitada de vírgula de extensões de nomes de arquivo associadas ao codec. Use NULO na primeira chamada para 
			/// determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todas as extensões de nome do arquivo associadas ao codec.</param>
			CarenResult GetFileExtensions(
				UInt32 Param_Size,
				String^% Param_Ref_ExtensoesArquivos,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera uma sequência delimitada de vírgula de tipos de mímicos associados ao codec. 
			/// Defina (Param_Size) para 0 e (Param_Ref_MimeTypes) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_MimeTypes) que 
			/// deve ser definida em (Param_Size).
			/// </summary>
			/// <param name="Param_Size">O tamanho do mímico tipo tampão. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Ref_MimeTypes">Recebe os tipos de mímica associados ao codec. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os tipos de mímica associados ao codec.</param>
			CarenResult GetMimeTypes(
				UInt32 Param_Size,
				String^% Param_Ref_MimeTypes,
				[Out] UInt32% Param_Out_SizeAtual);
			
			/// <summary>
			/// Recupera os formatos de pixel que o codec suporta.
			/// Defina (Param_Size) para 0 e (Param_Ref_FormatosPixel) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_FormatosPixel)
			///  que deve ser definida em (Param_Size).
			/// </summary>
			/// <param name="Param_Size">O tamanho da matriz (Param_Ref_FormatosPixel). Use 0 na primeira chamada para determinar o tamanho da matriz necessária.</param>
			/// <param name="Param_Ref_FormatosPixel">Recebe os formatos pixel suportados. Use NULO na primeira chamada para determinar o tamanho necessário da matriz</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho do array necessário para recuperar todos os formatos de pixel suportados.</param>
			CarenResult GetPixelFormats(
				UInt32 Param_Size,
				cli::array<String^>^% Param_Ref_FormatosPixel,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera um valor indicando se o tipo de mímica dado corresponde ao tipo mímico do codec. 
			/// </summary>
			/// <param name="Param_MimeType">O tipo do MimeType para comparar.</param>
			/// <param name="Param_Out_Corresponde">Recebe TRUE se os tipos de mímica correspondem; caso contrário, FALSO.</param>
			CarenResult MatchesMimeType(
				String^ Param_MimeType,
				[Out] Boolean% Param_Out_Corresponde);
		};

		/// <summary>
		/// (IWICBitmapCodecProgressNotification) - Interface responsável por expor métodos usados para notificação de progresso para codificadores e decodificadores.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("3E7B49AA-B5D1-4C53-B5C4-B27E36BD0C80")]
		public interface class ICarenWICBitmapCodecProgressNotification : ICaren
		{

			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Delegates

			delegate CarenResult Delegate_OnProgressNotification(
				ICarenBuffer^ Param_ComponenteData,
				UInt64 Param_NumeroFrame,
				CA_WICProgressOperation Param_Operacao,
				double Param_Progresso);


			//Eventos

			/// <summary>
			/// Evento chamado para notificar o progresso do componente do Codec.
			/// Este evento representa uma função de retorno de chamada nativa(PFNProgressNotification).
			/// </summary>
			event Delegate_OnProgressNotification^ OnProgressNotification;



			//Métodos


			/// <summary>
			/// Registra uma função de retorno de chamada de notificação de progresso. Permite que o usuário implemente seu proprio retorno de chamada sem precisar usar o evento disponivel nessa classe.
			/// Os aplicativos só podem registrar um único retorno de chamada. As chamadas de registro subsequentes substituirão o retorno de chamada previamente registrado. Para não registrar 
			/// um retorno de chamada, passe no NULO ou registre uma nova função de retorno de chamada. O progresso é relatado em uma ordem crescente entre 0,0 e 1.0. Se o (Param_FlagsProgresso) 
			/// incluir o WICProgressNotificationBegin, o retorno de chamada é garantido para ser chamado com o progresso 0.0. Se o (Param_FlagsProgresso) incluir o WICProgressNotificationEnd, 
			/// o retorno de chamada é garantido para ser chamado com o progresso 1.0. WICProgressNotificaçãoFrequent aumenta a frequência em que o retorno de chamada é chamado. Se uma operação 
			/// for esperada para levar mais de 30 segundos, o WICProgressNotificationFrequent deve ser adicionado ao (Param_FlagsProgresso).
			/// </summary>
			/// <param name="Param_CallbackPointer">Uma interface(ICaren) que contém um ponteiro de função para a função de chamada de notificação de progresso definida pelo aplicativo.</param>
			/// <param name="Param_ComponenteData">Uma interface(ICaren) que contém um ponteiro para componente de dados para o método de retorno de chamada.</param>
			/// <param name="Param_FlagsProgresso">As bandeiras CA_WICProgressOperation e CA_WICProgressNotification para uso para notificação de progresso.</param>
			CarenResult RegisterProgressNotification(
				ICaren^ Param_Callback,
				ICaren^ Param_ComponenteData,
				UInt32 Param_FlagsProgresso);


			//Métodos que registram e deletam os dados dos eventos.

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
		/// (IWICColorContext) - Interface responsável por expor métodos para gerenciamento de cores.
		/// Um contexto de cor é uma abstração para um perfil de cor. O perfil pode ser carregado a partir de um arquivo (como "sRGB Color Space Profile.icm"), lido a partir de 
		/// um buffer de memória ou pode ser definido por um espaço de cor EXIF. O diretório de perfil de cores do sistema pode ser obtido ligando para o GetColorDirectory do (Windows Color System).
		/// Depois que um contexto de cores é inicializado, ele não pode ser reinicializado.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("D3A24E8E-76E6-45AE-81AD-48B6C518915D")]
		public interface class ICarenWICColorContext : ICaren
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
			/// Recupera o contexto de cor do Arquivo de Imagem Exchangeable (EXIF). 
			/// Este método só deve ser usado quando o ICarenWICColorContext::GetType indica WICColorContextExifColorSpace.
			/// </summary>
			/// <param name="Param_Out_Valor">Recebe o contexto de cor exif de cores. 1 - Espaço de cores sRGB, 2 - Espaço de cores Adobe RGB, 3 a 65534 utilizadas.</param>
			CarenResult GetExifColorSpace([Out] UInt32% Param_Out_Valor);

			/// <summary>
			/// Recupera o perfil de contexto de cores. Use somente este método se o tipo de contexto for WICColorContextProfile.
			/// Chamar este método com (Param_Ref_Buffer) definido para NULO fará com que ele retorne o tamanho do buffer necessário no (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_SizeBuffer">O tamanho do buffer em (Param_Ref_Buffer).</param>
			/// <param name="Param_Ref_Buffer">Um ponteiro que recebe o perfil de contexto de cores.</param>
			/// <param name="Param_Out_SizeAtual">Recebe o tamanho real do buffer necessário para recuperar todo o perfil do contexto de cores.</param>
			CarenResult GetProfileBytes(
				UInt32 Param_SizeBuffer,
				ICarenBuffer^% Param_Ref_Buffer,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o tipo de contexto de cor. 
			/// </summary>
			/// <param name="Param_Out_Type">Recebe o enum CA_WICColorContextType do contexto de cores.</param>
			CarenResult GetType([Out] CA_WICColorContextType% Param_Out_Type);

			/// <summary>
			/// Inicializa o contexto de cores usando um espaço de cor EXIF (Exchangeable Image File, arquivo de imagem e imagem" do Arquivo de Imagem. 
			/// Uma vez iniciado um contexto de cor, ele não pode ser reinicializado.
			/// </summary>
			/// <param name="Param_Valor">O valor do espaço de cores EXIF. 1 - Espaço de cores sRGB, 2 - Espaço de cores Adobe RGB.</param>
			CarenResult InitializeFromExifColorSpace(UInt32 Param_Valor);

			/// <summary>
			/// Inicializa o contexto de cores a partir do arquivo dado. 
			/// </summary>
			/// <param name="Param_NomeArquivo">A url para o arquivo.</param>
			CarenResult InitializeFromFilename(String^ Param_NomeArquivo);

			/// <summary>
			/// Inicializa o contexto de cores a partir de um bloco de memória. 
			/// </summary>
			/// <param name="Param_Buffer">O buffer usado para inicializar o ICarenWICColorContext.</param>
			/// <param name="Param_SizeBuffer">O tamanho do buffer em (Param_Buffer).</param>
			CarenResult InitializeFromMemory(
				ICarenBuffer^ Param_Buffer,
				UInt32 Param_SizeBuffer);
		};

		/// <summary>
		/// (IWICBitmapDecoderInfo) - Interface responsável por expor métodos que fornecem informações sobre um decodificador.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("A7EE4A12-7E0C-49AB-8647-D76B71FD62EE")]
		public interface class ICarenWICBitmapDecoderInfo : ICarenWICBitmapCodecInfo
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
			/// Cria uma nova instância IWICBitmapDecoder. 
			/// </summary>
			/// <param name="Param_Out_IBitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para a nova instância do decodificador. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult CreateInstance(ICaren^ Param_Out_IBitmapDecoder);

			/// <summary>
			/// Recupera as assinaturas de padrão de arquivo suportadas pelo decodificador.
			/// Para recuperar todas as assinaturas de padrões, chame o método passando NULO para (Param_Ref_Patterns), isso vai fazer com que (Param_Out_QuantidadeRealArray) 
			/// devolva o real valor do tamanho da matriz, necessário
			/// no parametro (Param_TamanhoArray).
			/// </summary>
			/// <param name="Param_TamanhoArray">O tamanho da matriz em (Param_Ref_Patterns).</param>
			/// <param name="Param_Ref_Patterns">Recebe uma lista de objetos WICBitmapPattern suportados pelo decodificador.</param>
			/// <param name="Param_Out_QuantidadePatterns">Recebe o número de padrões que o decodificador suporta.</param>
			/// <param name="Param_Out_QuantidadeRealArray">Recebe o tamanho real do buffer necessário para recuperar todas as assinaturas de padrão suportadas pelo decodificador.</param>
			CarenResult GetPatterns(
				UInt32 Param_TamanhoArray,
				cli::array<CA_WICBitmapPattern^>^% Param_Ref_Patterns,
				[Out] UInt32% Param_Out_QuantidadePatterns,
				[Out] UInt32% Param_Out_QuantidadeRealArray);

			/// <summary>
			/// Recupera um valor que indica se o codec reconhece o padrão dentro de um fluxo especificado. 
			/// </summary>
			/// <param name="Param_Fluxo">O fluxo para o padrão corresponde dentro.</param>
			/// <param name="Param_Out_Corresponde">Recebe TRUE se os padrões coincidir; caso contrário, FALSO.</param>
			CarenResult MatchesPattern(
				ICarenStream^ Param_Fluxo,
				[Out] Boolean% Param_Out_Corresponde);
		};

		/// <summary>
		/// (IWICMetadataQueryReader) - Interface responsável por expor métodos para recuperar itens e blocos de metadados de um decodificador ou de seus quadros de imagem usando uma 
		/// expressão de consulta de metadados. Um leitor de consulta de metadados usa expressões de consulta de metadados para acessar metadados incorporados. O benefício do leitor 
		/// de consulta é a capacidade de acessar um item de metadados em uma única etapa. O leitor de consulta também fornece a maneira de atravessar todo o conjunto de hierarquia de 
		/// metadados com a ajuda do método GetEnumerator. No entanto, não é recomendável usar este método, uma vez que o ICarenWICMetadataBlockReader e o ICarenWICMetadataReader 
		/// fornecem uma maneira mais conveniente e mais barata.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("3189A2F2-5BC6-46FD-97B5-C495C544C90A")]
		public interface class ICarenWICMetadataQueryReader : ICaren
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
			/// Obtém o formato de contêiner de leitores de consulta de metadados. 
			/// </summary>
			/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID que representa o tipo do formato cointainer.</param>
			CarenResult GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat);

			/// <summary>
			/// Obtém um enumerador de todos os itens de metadados na localização relativa atual dentro da hierarquia de metadados. 
			/// </summary>
			/// <param name="Param_Out_EnumString">Retorna uma interface(ICarenEnumString) que contém um ponteiro para o enumerador que contém Strings de consulta que pode ser usadas na 
			/// interface (ICarenWICMetadataQueryReader) atual.</param>
			CarenResult GetEnumerator([Out] ICarenEnumString^% Param_Out_EnumString);

			/// <summary>
			/// Recupera o caminho atual em relação ao bloco de metadados raiz. Se o leitor de consulta for relativo ao topo da hierarquia de metadados, ele retornará uma sequência de char único.
			/// Se o leitor de consulta for relativo a um bloco de metadados aninhados, este método retornará o caminho para o leitor de consulta atual.
			/// Se você passar NULO para (Param_Ref_Namespace), o GetLocation ignorará o (Param_SizeString) e retorna o comprimento de buffer necessário para armazenar o caminho na variável 
			/// a que o (Param_Out_SizeAtual) aponta.
			/// </summary>
			/// <param name="Param_SizeString">O comprimento da String em (Param_Ref_Namespace).</param>
			/// <param name="Param_Ref_Namespace">Retorna uma string que contém a localização atual do namespace.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o comprimento real necessário pela String(Param_Ref_Namespace).</param>
			CarenResult GetLocation(
				UInt32 Param_SizeString,
				String^% Param_Ref_Namespace,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o bloco de metadados ou item identificado por uma expressão de consulta de metadados.
			/// Este método usa expressões de consulta de metadados para acessar metadados incorporados. Se existirem vários blocos ou itens expressos pela mesma expressão de consulta, 
			/// o primeiro bloco de metadados ou item encontrado será devolvido.
			/// </summary>
			/// <param name="Param_Nome">A expressão de consulta ao bloco ou item de metadados solicitados.</param>
			/// <param name="Param_Out_Valor">Retorna uma estrutura(CA_PROPVARIANT) que armazena o bloco de metadados ou item solicitado.</param>
			CarenResult GetMetadataByName(
				String^ Param_Nome,
				[Out] CA_PROPVARIANT^% Param_Out_Valor);
		};

		/// <summary>
		/// (IWICMetadataQueryWriter) - Interface responsável por expor métodos para definir ou remover itens e blocos de metadados em um codificador ou em seus quadros de imagem usando 
		/// uma expressão de consulta de metadados.
		/// Um escritor de consulta de metadados usa expressões de consulta de metadados para definir ou remover metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("7BD2296D-D72D-42A5-9F04-7ABA2FAE0174")]
		public interface class ICarenWICMetadataQueryWriter : ICarenWICMetadataQueryReader
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
			/// Remove um item de metadados de um local específico usando uma expressão de consulta de metadados.
			/// Este método usa expressões de consulta de metadados para remover metadados. Se o item metadados for um bloco de metadados, ele será removido da hierarquia de metadados.
			/// </summary>
			/// <param name="Param_Nome">O nome do item metadados para remover.</param>
			CarenResult RemoveMetadataByName(String^ Param_Nome);

			/// <summary>
			/// Define um item de metadados em um local específico. 
			/// Este método usa expressões de consulta de metadados para remover metadados. Se o conjunto de valor é um bloco de metadados aninhados, use o tipo de variante 
			/// (TP_PonteiroDesconhecido) e o (Param_Valor) apontando para o ICarenWICMetadataQueryWriter do novo bloco de metadados.
			/// A encomenda de itens de metadados fica a critério do autor de consulta, uma vez que os locais relativos não são especificados.
			/// </summary>
			/// <param name="Param_Nome">O nome do item metadados.</param>
			/// <param name="Param_Valor">Uma estrutura(CA_PROPVARIANT) que contém o valor dos metadados para definir.</param>
			CarenResult SetMetadataByName(
				String^ Param_Nome,
				CA_PROPVARIANT^ Param_Valor);
		};

		/// <summary>
		/// (IWICBitmapFrameDecode) - Interface responsável por definir métodos para decodificar frames de imagem individuais de um arquivo codificado.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("C6FC2831-D78E-45CE-8E6D-E22FF7214BF1")]
		public interface class ICarenWICBitmapFrameDecode : ICarenWICBitmapSource
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
			/// Recupera o ICarenWICColorContext associado ao frame de imagem.
			/// Se NULO for definido para (Param_Ref_ColorContexts), e 0 for para (Param_Quantidade), este método retornará o número total de contextos de cores na imagem no (Param_Out_TamanhoArrayAtual).
			/// </summary>
			/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
			/// <param name="Param_Ref_ColorContexts">Uma matriz que recebe ponteiros para a interface(ICarenWICColorContext).</param>
			/// <param name="Param_Out_TamanhoArrayAtual">Recebe o número de contextos de cores retornados na matriz (Param_Ref_ColorContexts).</param>
			CarenResult GetColorContexts(
				UInt32 Param_Quantidade,
				cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
				[Out] UInt32% Param_Out_TamanhoArrayAtual);

			/// <summary>
			/// Recupera um leitor de consulta de metadados para o frame.
			/// Para formatos de imagem com um frame (JPG, PNG, JPEG-XR), o leitor de consulta de nível de frame do primeiro frame é usado para acessar todos os metadados de imagem, 
			/// e o leitor de consulta de nível de decodificador não é usado. Para formatos com mais de um frames (GIF, TIFF), o leitor de consulta de nível de frame para um determinado 
			/// frame é usado para acessar metadados específicos desse frame, e no caso de GIF um leitor de metadados de nível de decodificador estará presente. Se o decodificador não suportar 
			/// metadados (BMP, ICO), isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
			/// </summary>
			/// <param name="Param_Out_MetadataReader">Retorna a interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o leitor de consulta de metadados do frame.</param>
			CarenResult GetMetadataQueryReader(
				[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataReader);

			/// <summary>
			/// Recupera uma pequena visualização do frame, se suportado pelo codec.
			/// </summary>
			/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) que contém um ponteiro para o objeto miniatura.</param>
			CarenResult GetThumbnail(
				[Out] ICarenWICBitmapSource^% Param_Out_Thumbnail);
		};

		/// <summary>
		/// (IWICBitmapDecoder) - Interface responsável por expor  métodos que representam um decodificador. A interface fornece acesso às propriedades do decodificador, como 
		/// miniaturas globais (se suportadas), frames e paleta. Há uma série de implemenações concretas desta interface representando cada um dos decodificadores padrão fornecidos 
		/// pela plataforma, incluindo bitmap (BMP), Portable Network Graphics (PNG), icon (ICO), Joint Photographic Experts Group (JPEG), Graphics Interchange Format (GIF), 
		/// Tagged Image File Format (TIFF) e Microsoft Windows Digital Photo (WDP). Esta interface pode ser sub-classificada para fornecer suporte para codecs de terceiros como 
		/// parte do modelo de extensibilidade. Os codecs escritos como formatos de contêiner TIFF que não são registrados serão decodificados como uma imagem TIFF. Os aplicativos 
		/// do cliente devem verificar se há uma contagem de quadros zero para determinar se o codec é válido. CLSID_WICHeifDecoder opera em imagens HEIF (High Efficiency Image Format).
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("29093567-621E-431B-8169-42C7C49B2F9C")]
		public interface class ICarenWICBitmapDecoder : ICaren
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
			/// Copia o ICarenWICPalette do decodificador.
			/// CopyPalette retorna uma paleta global (uma paleta que se aplica a todos os frames da imagem) se houver uma; caso contrário, ele retorna WINCODEC_ERR_PALETTEUNAVAILABLE. 
			/// Se uma imagem não tiver uma paleta global, ela ainda pode ter uma paleta de nível de frame, que pode ser recuperada usando ICarenWICBitmapFrameDecode::CopyPalette.
			/// </summary>
			/// <param name="Param_Palette">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a paleta global do decodificador. Use o 
			/// ICarenWICImagingFactory::CreatePalette para criar a paleta de destino antes de chamar o CopyPalette.</param>
			CarenResult CopyPalette(ICaren^ Param_Palette);

			/// <summary>
			/// Recupera os objetos ICarenWICColorContext da imagem. 
			/// </summary>
			/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
			/// <param name="Param_Ref_ColorContexts">Retorna uma matriz de interfaces (ICarenWICColorContext).</param>
			/// <param name="Param_Out_SizeAtual">Retorna o número real de interfaces na matriz (Param_Ref_ColorContexts).</param>
			CarenResult GetColorContexts(
				UInt32 Param_Quantidade,
				cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Recupera o formato do recipiente da imagem. 
			/// </summary>
			/// <param name="Param_Out_GuidContainerFormat">Retorna um GUID que representa o contêiner de formato da imagem.</param>
			CarenResult GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat);

			/// <summary>
			/// Recupera um ICarenWICBitmapDecoderInfo para a imagem. 
			/// </summary>
			/// <param name="Param_Out_DecoderInfo">Retorna uma interface(ICarenWICBitmapDecoderInfo) que contém um ponteiro para o objeto de informações do decodificador.</param>
			CarenResult GetDecoderInfo([Out] ICarenWICBitmapDecoderInfo^% Param_Out_DecoderInfo);

			/// <summary>
			/// Recupera o Frame especificado da imagem. 
			/// </summary>
			/// <param name="Param_Index">O quadro em particular para recuperar.</param>
			/// <param name="Param_Out_BitmapFrame">Retorna uma interface(ICarenWICBitmapFrameDecode) contém um ponteiro para o frame especificado.</param>
			CarenResult GetFrame(
				UInt32 Param_Index,
				[Out] ICarenWICBitmapFrameDecode^% Param_Out_BitmapFrame);

			/// <summary>
			/// Recupera o número total de frames na imagem. 
			/// </summary>
			/// <param name="Param_Out_QuantidadeFrames">Retorna o número total de frames na imagem.</param>
			CarenResult GetFrameCount([Out] UInt32% Param_Out_QuantidadeFrames);

			/// <summary>
			/// Recupera o leitor de consulta de metadados do decodificador. Se um formato de imagem não suportar metadados em nível de contêiner, isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
			/// O único formato de imagem fornecido pelo Windows que suporta metadados em nível de contêiner é o GIF. Em vez disso, use ICarenWICBitmapFrameDecode::GetMetadataQueryReader.
			/// </summary>
			/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) contém um ponteiro para o leitor de consulta de metadados do decodificador.</param>
			CarenResult GetMetadataQueryReader([Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader);

			/// <summary>
			/// Recupera uma imagem de visualização, se suportada. Nem todos os formatos suportam visualizações. Apenas as visualizações nativas do codec Microsoft Windows Digital Photo 
			/// (WDP) suportam visualizações.
			/// </summary>
			/// <param name="Param_Out_BitmapSource">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o bitmap de visualização se suportado.</param>
			CarenResult GetPreview([Out] ICarenWICBitmapSource^% Param_Out_BitmapSource);

			/// <summary>
			/// Recupera uma miniatura bitmap da imagem, se existir.
			/// A miniatura devolvida pode ser de qualquer tamanho, por isso o chamador deve dimensionar a miniatura para o tamanho desejado. Os únicos formatos de imagem fornecidos 
			/// pelo Windows que suportam miniaturas são JPEG, TIFF e JPEG-XR. Se a miniatura não estiver disponível, isso retornará WINCODEC_ERR_CODECNOTHUMBNAIL.
			/// </summary>
			/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o objeto de miniatura.</param>
			CarenResult GetThumbnail([Out] ICarenWICBitmapSource^% Param_Out_Thumbnail);

			/// <summary>
			/// Inicializa o decodificador com o fluxo fornecido. 
			/// </summary>
			/// <param name="Param_Stream">O fluxo a ser usado para a inicialização. O fluxo contém os pixels codificados que são decodificados cada vez que o método CopyPixels na 
			/// interface ICarenWICBitmapFrameDecode é invocado.</param>
			/// <param name="Param_OpcoesCache">Uma enumeração que especifica as opções do decodificador.</param>
			CarenResult Initialize(
				ICarenStream^ Param_Stream,
				CA_WICDecodeOptions Param_OpcoesCache);

			/// <summary>
			/// Recupera as capacidades do decodificador com base no fluxo especificado.
			/// As implementações de decodificadores personalizadas devem salvar a posição atual do (ICarenStream) especificado, ler quaisquer informações necessárias para determinar quais 
			/// recursos elas podem fornecer para o fluxo fornecido e restaurar a posição do fluxo.
			/// </summary>
			/// <param name="Param_Stream">O fluxo para recuperar as capacidades de decodificador.</param>
			/// <param name="Param_Out_Capacidades">Retorna uma enumerações que especifica as capacidades do decodificador para o fluxo informado.</param>
			CarenResult QueryCapability(
				ICarenStream^ Param_Stream,
				[Out] CA_WICBitmapDecoderCapabilities% Param_Out_Capacidades);
		};

		/// <summary>
		/// (IWICBitmapEncoderInfo) - Interface responsável por expor métodos que fornecem informações sobre um codificador.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("CC3B04D7-B092-4693-AC2D-566CA00998D6")]
		public interface class ICarenWICBitmapEncoderInfo : ICarenWICBitmapCodecInfo
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
			/// Cria uma nova instância da interface ICarenWICBitmapEncoder. 
			/// </summary>
			/// <param name="Param_Out_BitmapEncoder">Retorna uma interface(ICarenWICBitmapEncoder) que contém um ponteiro para o nova instância do encoder. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult CreateInstance(ICaren^ Param_Out_BitmapEncoder);
		};

		/// <summary>
		/// (IWICBitmapFrameEncode) - Interface responsável por representar os quadros(frames) de imagem individuais de um codificador.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("7C37F9D3-82D6-43F8-9151-5986F8129024")]
		public interface class ICarenWICBitmapFrameEncode : ICaren
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
			/// Confirma o frame para a imagem.
			/// Depois que o frame Commit for chamado, você não pode usar ou reiniciar o objeto ICarenWICBitmapFrameEncode e quaisquer objetos criados a partir dele.
			/// Para finalizar a imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que todos 
			/// os frames forem confirmados(Committed). 
			/// </summary>
			CarenResult Commit();

			/// <summary>
			/// Recebe o escritor de consulta de metadados para o frame do codificador. 
			/// Se você estiver configurando metadados no frame, você deve fazer isso antes de usar ICarenWICBitmapFrameEncode::WritePixels ou ICarenWICBitmapFrameEncode::WriteSource 
			/// para gravar quaisquer pixels de imagem no frame.
			/// </summary>
			/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados para o 
			/// frame do codificador.</param>
			CarenResult GetMetadataQueryWriter(
				[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);

			/// <summary>
			/// Inicializa o codificador de frames usando as propriedades dadas.
			/// Se você não quiser opções de codificação, passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe o ICarenPropertyBag2 fornecido pelo 
			/// ICarenWICBitmapEncoder::CreateNewFrame com valores atualizados. Voce pode acessar o GUIDs::GUIDs_WIC_CLSIDs_ENCODIFICADORES para obter uma lista de codificadores suportados.
			/// </summary>
			/// <param name="Param_OpcoesEncodificacao">O conjunto de propriedades a serem usados para inicialização do ICarenWICBitmapFrameEncode. e você não quiser opções de codificação, 
	        /// passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe um ICarenPropertyBag2 fornecido pelo ICarenWICBitmapEncoder::CreateNewFrame com valores 
	        /// atualizados.</param>
			CarenResult Initialize(ICarenPropertyBag2^ Param_OpcoesEncodificacao);

			/// <summary>
			/// Define um determinado número de perfis ICarenWICColorContext ao quadro. 
			/// </summary>
			/// <param name="Param_Quantidade">O número de perfis ICarenWICColorContext a definir na matriz (Param_ColorContexts).</param>
			/// <param name="Param_ColorContexts">Uma matriz de interfaces IWICColorContext contendo os perfis de contextos de cores a serem configurados para o frame.</param>
			CarenResult SetColorContexts(
				UInt32 Param_Quantidade,
				cli::array<ICarenWICColorContext^>^ Param_ColorContexts);

			/// <summary>
			/// Define o ICarenWICPalette para formatos de pixel indexados. 
			/// Este método não falha se chamado em um frame cujo formato de pixel é definido como um formato de pixel não indexado. Se o formato de pixel de destino for um formato não indexado, 
			/// a paleta será ignorada. Se você já ligou para ICarenWICBitmapEncoder::SetPalette para definir uma paleta global, este método substitui essa paleta para o frame atual.
			/// A paleta deve ser especificada antes da primeira chamada para WritePixels/WriteSource. Isso fará com que o WriteSource use a paleta especificada ao converter a imagem de origem 
			/// no formato de pixel do codificador. Se nenhuma paleta for especificada, uma paleta será gerada na primeira chamada para WriteSource.
			/// </summary>
			/// <param name="Param_Palette">A interface ICarenWICPalette para usar para formatos de pixel indexados. O codificador pode alterar a paleta para refletir os formatos de pixel que 
			/// o codificador suporta.</param>
			CarenResult SetPalette(ICarenWICPalette^ Param_Palette);

			/// <summary>
			/// Solicita que o codificador use o formato de pixel especificado.
			/// O codificador pode não suportar o formato de pixel solicitado. Caso não, o (Param_Ref_INOUT_GuidFormatoPixel) retorna a correspondência mais próxima no bloco de memória a que 
			/// (Param_Ref_INOUT_GuidFormatoPixel) aponta. Se o formato de pixel retornado não corresponder ao formato solicitado, você deve usar um objeto ICarenWICFormatConverter para 
			/// converter os dados do pixel.
			/// </summary>
			/// <param name="Param_Ref_INOUT_GuidFormatoPixel">Na entrada, o GUID de formato de pixel solicitado. Na saída, o GUID do formato de pixel mais próximo suportado pelo codificador; 
			/// isso pode ser diferente do formato solicitado. Consulte a estrutura Guids::GUIDs_WIC_NATIVE_PIXEL_FORMATS para obter uma lista de GUIDs com os formatos de pixel suportados pelo WIC.</param>
			CarenResult SetPixelFormat(String^% Param_Ref_INOUT_GuidFormatoPixel);

			/// <summary>
			/// Define a resolução física da imagem de saída.
			/// O Windows Imaging Component (WIC) não realiza nenhum processamento especial como resultado dos valores de resolução de DPI. Por exemplo, os dados retornados do 
			/// ICarenWICBitmapFonte::CopyPixels não é dimensionado pelo DPI. O aplicativo deve lidar com a resolução de DPI.
			/// </summary>
			/// <param name="Param_DpiX">O valor da resolução Horizontal.</param>
			/// <param name="Param_DpiY">O valor da resolução Vertical.</param>
			CarenResult SetResolution(
				double Param_DpiX,
				double Param_DpiY);

			/// <summary>
			/// Define as dimensões da imagem de saída para o quadro. 
			/// </summary>
			/// <param name="Param_Width">A Largura da imagem de saída.</param>
			/// <param name="Param_Height">A Altura da imagem de saída.</param>
			CarenResult SetSize(
				UInt32 Param_Width,
				UInt32 Param_Height);

			/// <summary>
			/// Define a miniatura do quadro se suportado pelo codec. 
			/// Recomendamos que você ligue para SetThumbnail antes de ligar para WritePixels ou WriteSource. A miniatura não será adicionada ao arquivo codificado se o SetThumbnail for 
			/// chamado após uma chamada para WritePixels ou WriteSource.
			/// </summary>
			/// <param name="Param_Thumbnail">A fonte bitmap para usar como miniatura.</param>
			CarenResult SetThumbnail(ICarenWICBitmapSource^ Param_Thumbnail);

			/// <summary>
			/// Copia dados da linha de varredura de um buffer fornecido pelo chamador para o objeto ICarenWICBitmapFrameEncode.
			/// Sucessivas chamadas WritePixels são consideradas de acesso sequencial à linha de varredura na imagem de saída.
			/// </summary>
			/// <param name="Param_QuantidadeLinhas">O número de linhas para codificar.</param>
			/// <param name="Param_Stride">O Stride dos pixels de imagem.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer de pixels.</param>
			/// <param name="Param_Pixels">Uma interface(ICarenBuffer) para os dados de pixels.</param>
			CarenResult WritePixels(
				UInt32 Param_QuantidadeLinhas,
				UInt32 Param_Stride,
				UInt32 Param_TamanhoBuffer,
				ICarenBuffer^ Param_Pixels);

			/// <summary>
			/// Codifica uma fonte de bitmap. 
			/// Se o SetSize não for chamado antes de chamar WriteSource, o tamanho dado no (Param_RetanguloBitmap) será usado se não for NULO. Caso contrário, o tamanho do ICarenWICBitmapSource
			///  dado em (Param_BitmapSource) é usado. Se o SetPixelFormat não for chamado antes de chamar WriteSource, o formato de pixel do ICarenWICBitmapSource dado no (Param_BitmapSource) é usado.
			/// Se o SetResolution não for chamado antes de chamar WriteSource, o formato pixel do (Param_BitmapSource) será usado.
			/// Se o SetPalette não for chamado antes de chamar WriteSource, o formato de pixel alvo será indexado, e o formato de pixel do (Param_BitmapSource) corresponde ao formato 
			/// de pixel do quadro do codificador, então o formato de pixel (Param_BitmapSource) é usado.
			/// </summary>
			/// <param name="Param_BitmapSource">A fonte do bitmap para codificar.</param>
			/// <param name="Param_RetanguloBitmap">O retângulo de tamanho da fonte do bitmap.</param>
			CarenResult WriteSource(
				ICarenWICBitmapSource^ Param_BitmapSource,
				CA_WICRect^ Param_RetanguloBitmap);
		};

		/// <summary>
		/// (IWICBitmapEncoder) - Interface responsável por definir métodos para definir as propriedades de um codificador, como miniaturas, quadros e paletas.
		/// Há uma série de implemenações concretas desta interface representando cada um dos codificadores padrão fornecidos pela plataforma, incluindo bitmap (BMP), Portable Network 
		/// Graphics (PNG), Joint Photographic Experts Group (JPEG), Graphics Interchange Format (GIF), Tagged Image File Format (TIFF) e Microsoft Windows Digital Photo (WDP). A tabela 
		/// a seguir inclui o identificador de classe (CLSID) para cada codificador nativo. Além disso, esta interface pode ser sub-classificada para fornecer suporte para codecs de terceiros 
		/// como parte do modelo de extensibilidade. CLSID_WICHeifDecoder opera em imagens HEIF (High Efficiency Image Format).
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("BE57F359-F07C-4E72-8D56-A6987715CE75")]
		public interface class ICarenWICBitmapEncoder : ICaren
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
			/// Confirma todas as alterações para a imagem e fecha o fluxo.
			/// Para finalizar uma imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que 
			/// todos os frames foram (Committed). Depois que o codificador foi cometido, ele não pode ser reiniciado ou reutilizado com outro fluxo. Uma nova interface de codificador 
			/// deve ser criada, por exemplo, com ICarenWICImagingFactory::CreateEncoder. Para que o codificador Comprometa-se a ter sucesso, você deve, no mínimo, chamar 
			/// ICarenWICBitmapEncoder::Initialize e ICarenWICBitmapFrameEncode::WriteSource ou ICarenWICBitmapFrameEncode::WritePixels.
			/// </summary>
			CarenResult Commit();

			/// <summary>
			/// Cria uma nova instância ICarenWICBitmapFrameEncode. 
			/// Para formatos que suportam codificação de vários frames (por exemplo, TIFF, JPEG-XR), você pode trabalhar em apenas um frame por vez. Isso significa que você deve 
			/// ligar para o IWICBitmapFrameEncode::Commit antes de chamar o CreateNewFrame novamente.
			/// </summary>
			/// <param name="Param_Out_FrameEncode">Retorna uma interface(ICarenWICBitmapFrameEncode) que contém um ponteiro para a nova instância do ICarenWICBitmapFrameEncode.</param>
			/// <param name="Param_Ref_OpcoesEncodificacao">(Opcional) Recebe as propriedades nomeadas para usar para inicialização subsequente do frame. O usuário deve inicializar a interface se desejar receber um ponteiro para a interface.</param>
			CarenResult CreateNewFrame(
				[Out] ICarenWICBitmapFrameEncode^% Param_Out_FrameEncode,
				ICarenPropertyBag2^% Param_Ref_OpcoesEncodificacao);

			/// <summary>
			/// Recupera o formato do recipiente do codificador. 
			/// </summary>
			/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID do formato de contêiner do codificador.</param>
			CarenResult GetContainerFormat(
				[Out] String^% Param_Out_GuidContainerFormat);

			/// <summary>
			/// Recupera um ICarenWICBitmapEncoderInfo para o codificador. 
			/// </summary>
			/// <param name="Param_Out_EncoderInfo">Retorna uma interface(ICarenWICBitmapEncoderInfo) que contém um ponteiro para o objeto de informações do codificador.</param>
			CarenResult GetEncoderInfo(
				[Out] ICarenWICBitmapEncoderInfo^% Param_Out_EncoderInfo);

			/// <summary>
			/// Recupera um escritor de consulta de metadados para o codificador. 
			/// </summary>
			/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados do codificador.</param>
			CarenResult GetMetadataQueryWriter(
				[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);

			/// <summary>
			/// Inicializa o codificador com um ICarenStream que diz ao codificador onde codificar os bits. 
			/// </summary>
			/// <param name="Param_Stream">O fluxo de saída.</param>
			/// <param name="Param_OpcoesCache">O WICBitmapEncoderCacheOption usado na inicialização.</param>
			CarenResult Initialize(
				ICarenStream^ Param_Stream,
				CA_WICBitmapEncoderCacheOption Param_OpcoesCache);

			/// <summary>
			/// Define os objetos ICarenWICColorContext para o codificador. 
			/// </summary>
			/// <param name="Param_Quantidade">O número de ICarenWICColorContext a definir.</param>
			/// <param name="Param_ColorContexts">Uma matriz de interfaces(ICarenWICColorContext) contendo os contextos de cor para definir para o codificador.</param>
			CarenResult SetColorContexts(
				UInt32 Param_Quantidade,
				cli::array<ICarenWICColorContext^>^ Param_ColorContexts);

			/// <summary>
			/// Define a paleta global para a imagem. 
			/// Apenas as imagens GIF suportam uma paleta global opcional, e você deve definir a paleta global antes de adicionar quaisquer frames à imagem. Você só precisa 
			/// definir a paleta para formatos de pixel indexados.
			/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
			/// </summary>
			/// <param name="Param_Palette">Uma interface(ICarenWICPalette) para usar como paleta global.</param>
			CarenResult SetPalette(
				ICarenWICPalette^ Param_Palette);

			/// <summary>
			/// Define a visualização global para a imagem. 
			/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
			/// </summary>
			/// <param name="Param_Preview">Uma interface(ICarenWICBitmapSource) para usar como pré-visualização global.</param>
			CarenResult SetPreview(
				ICarenWICBitmapSource^ Param_Preview);

			/// <summary>
			/// Define a miniatura global para a imagem. 
			/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
			/// </summary>
			/// <param name="Param_Thumbnail">Uma interface (ICarenWICBitmapSource) para definir como a miniatura global.</param>
			CarenResult SetThumbnail(
				ICarenWICBitmapSource^ Param_Thumbnail);
		};

		/// <summary>
		/// (IWICBitmapFlipRotator) - Interface responsável por expor métodos que produzem uma fonte de bitmap invertida (horizontal ou vertical) e / ou girada (em incrementos de 90 graus). 
		/// As rotações são feitas antes do flip.
		/// O ICarenWICBitmapFlipRotator solicita dados por pixel, enquanto os codecs WIC fornecem dados por linha de verificação. Isso faz com que o objeto fliprotator exiba o comportamento 
		/// n² se não houver buffer. Isso ocorre porque cada pixel na imagem transformada exige que uma linha de varredura inteira seja decodificada no arquivo. É recomendável que você 
		/// armazene em buffer a imagem usando o IWICBitmap ou gire / gire a imagem usando o Direct2D.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("D4CD88A6-8479-4DDF-B1AF-32510C0B5162")]
		public interface class ICarenWICBitmapFlipRotator : ICarenWICBitmapSource
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
			/// Inicializa o rotador bitmap flip com os parâmetros fornecidos.
			/// </summary>
			/// <param name="Param_BitmapEntrada">A fonte de bitmap de entrada.</param>
			/// <param name="Param_Opcoes">O WICBitmapTransformOptions para girar ou girar a imagem.</param>
			CarenResult Initialize(
				ICarenWICBitmapSource^ Param_BitmapEntrada,
				CA_WICBitmapTransformOptions Param_Opcoes);
		};		

		/// <summary>
		/// (IWICBitmapScaler) - Interface responsável por representar uma versão redimensionada do bitmap de entrada usando um algoritmo de reamostragem ou filtragem.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("B6B78368-E6F6-4D2B-B17E-EA732C1C9605")]
		public interface class ICarenWICBitmapScaler : ICarenWICBitmapSource
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
			/// Inicializa o scaler bitmap com os parâmetros fornecidos.
			/// O ICarenWICBitmapScaler não pode ser inicializado várias vezes. Por exemplo, ao dimensionar cada frame em uma imagem de vários frames, um novo ICarenWICBitmapScaler 
			/// deve ser criado e inicializado para cada frame.
			/// </summary>
			/// <param name="Param_BitmapEntrada">A fonte de bitmap de entrada.</param>
			/// <param name="Param_Width">A Largura do destino.</param>
			/// <param name="Param_Heigth">A Altura do destino.</param>
			/// <param name="Param_ModoInterpolacao">O CA_WICBitmapInterpolationMode para usar durante o dimensionamento.</param>
			CarenResult Initialize(
				ICarenWICBitmapSource^ Param_BitmapEntrada,
				UInt32 Param_Width,
				UInt32 Param_Heigth,
				CA_WICBitmapInterpolationMode Param_ModoInterpolacao);
		};

		/// <summary>
		/// (IWICBitmapSourceTransform) - Interface responsável por expor métodos para descarregar determinadas operações na implementação IWICBitmapSource subjacente.
		/// A interface ICarenWICBitmapSourceTransform é implementada por codecs que podem dimensionar, inverter, girar ou formatar nativamente os pixels de conversão 
		/// durante a decodificação. Como a transformação é combinada com o processo de decodificação, a transformação nativa geralmente oferece vantagens de desempenho 
		/// em relação às transformações não nativas. As implementações da caixa de entrada ICarenWICBitmapScaler, ICarenWICBitmapFlipRotator e ICarenWICFormatConverter 
		/// utilizam a interface ICarenWICBitmapSourceTransform quando são colocadas imediatamente após um ICarenWICBitmapFrameDecode suportado, portanto, no caso típico, 
		/// um aplicativo recebe automaticamente esse aumento de desempenho e não precisa usar diretamente essa interface. No entanto, ao encadear várias transformações ou 
		/// ao implementar uma transformação customizada, pode haver uma vantagem de desempenho ao usar a interface ICarenWICBitmapSourceTransform diretamente.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("859F2EEA-9CCC-4160-BAEF-43D3974EF3C8")]
		public interface class ICarenWICBitmapSourceTransform : ICaren
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
			/// Copia os dados de pixels usando os parâmetros de entrada fornecidos.
			/// Se NULO for passado para (Param_Retangulo), toda a imagem será copiada. Quando são solicitadas operações de transformação múltipla, o resultado depende da ordem 
			/// em que as operações são realizadas. Para garantir previsibilidade e consistência entre os CODECs, é importante que todos os CODECs executem essas operações na mesma ordem.
			/// A ordem recomendada dessas operações é: Escala -> Crop -> Flip/Rotate. A conversão do formato pixel pode ser realizada a qualquer momento, já que não tem efeito nas 
			/// outras transformações.
			/// </summary>
			/// <param name="Param_Retangulo">O retângulo de pixels para copiar.</param>
			/// <param name="Param_Width">A Largura para dimensionar o bitmap de origem. Este parâmetro deve ser igual ao valor obtido através do ICarenWICBitmapSourceTransform::GetClosestSize.</param>
			/// <param name="Param_Height">A Altura para dimensionar o bitmap fonte. Este parâmetro deve ser igual ao valor obtido através do ICarenWICBitmapSourceTransform::GetClosestSize.</param>
			/// <param name="Param_GuidFormatoDestino">O GUID do formato de pixel desejado no qual os pixels devem ser devolvidos. Este GUID deve ser um formato obtido através 
			/// de uma chamada GetClosestPixelFormat.</param>
			/// <param name="Param_TransformDestino">A rotação desejada ou o flip para executar antes da cópia dois pixels. A transformação deve ser uma operação suportada por 
			/// uma chamada DoSupportTransform. Se um (Param_TransformDestino) for especificado, o 
			/// (Param_Stride) é o stride transformado e é baseado no formato de pixel (Param_GuidFormatoDestino), não no formato de pixel da fonte original.</param>
			/// <param name="Param_Stride">O Stride do Buffer de destino.</param>
			/// <param name="Param_BufferSize">O tamanho do buffer de destino.</param>
			/// <param name="Param_Buffer">O buffer de saída.</param>
			CarenResult CopyPixels(
				CA_WICRect^ Param_Retangulo,
				UInt32 Param_Width,
				UInt32 Param_Height,
				String^ Param_GuidFormatoDestino,
				CA_WICBitmapTransformOptions Param_TransformDestino,
				UInt32 Param_Stride,
				UInt32 Param_BufferSize,
				ICarenBuffer^ Param_Buffer);

			/// <summary>
			/// Determina se uma opção de transformação específica é suportada nativamente pela implementação da interface ICarenWICBitmapSourceTransform. 
			/// </summary>
			/// <param name="Param_DestinoTransformacao">O WICBitmapTransformOptions para verificar se eles são suportados.</param>
			/// <param name="Param_Out_Suporte">Retorna um valor especificando se a opção de transformação é suportada.</param>
			CarenResult DoesSupportTransform(
				CA_WICBitmapTransformOptions Param_DestinoTransformacao,
				[Out] Boolean% Param_Out_Suporte);

			/// <summary>
			/// Recupera o formato de pixel mais próximo ao qual a implementação do ICarenWICBitmapSourceTransform pode copiar nativamente pixels, dado o formato desejado. 
			/// </summary>
			/// <param name="Param_Ref_INOUT_DestinoGuidFormato">Na entrada, o formato do pixel desejado, na saida, retorna o formato do pixel suportado mais proximo do desejado.</param>
			CarenResult GetClosestPixelFormat(String^% Param_Ref_INOUT_DestinoGuidFormato);

			/// <summary>
			/// Retorna as dimensões mais próximas que a implementação pode escalar nativamente para dadas as dimensões desejadas. 
			/// </summary>
			/// <param name="Param_Ref_INOUT_Width">A Largura desejada. Retorna a Largura suportada mais próxima.</param>
			/// <param name="Param_Ref_INOUT_Height">A Altura desejada. Retorna a Altura suportada mais próxima.</param>
			CarenResult GetClosestSize(
				UInt32% Param_Ref_INOUT_Width,
				UInt32% Param_Ref_INOUT_Height);
		};		

		/// <summary>
		/// (IWICColorTransform) - Interface responsável por expor métodos que transformam um ICarenWICBitmapSource de um contexto de cores para outro.
		/// Um IWICColorTransform é um componente de pipeline de criação de imagens que sabe como puxar pixels obtidos de um determinado ICarenWICBitmapSource por meio 
		/// de uma transformação de cores. A transformação de cores é definida pelo mapeamento de cores do contexto de cores de origem para o contexto de cores de destino 
		/// em um determinado formato de pixel de saída. Depois de inicializada, uma transformação de cores não pode ser reinicializada.Por esse motivo, uma transformação 
		/// de cores não pode ser usada com várias fontes ou parâmetros variáveis.
		/// </summary>
		[CategoryAttribute("WIC Interface")]
		[Guid("F3EEAD4C-C75C-4FE5-BDB7-B6073417B8A2")]
		public interface class ICarenWICColorTransform : ICarenWICBitmapSource
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
			/// Inicializa um ICarenWICColorTransform com um ICarenWICBitmapSource e transforma-o de um ICarenWICColorContext para outro. 
			/// </summary>
			/// <param name="Param_FonteBitmap">A fonte bitmap usada para inicializar a transformação de cor.</param>
			/// <param name="Param_FonteContexto">A fonte de contexto de cores.</param>
			/// <param name="Param_DestinoContexto">O destino do contexto de cores.</param>
			/// <param name="Param_GuidFormatoPixelDestino">O GUID do formato de pixel desejado. Este parâmetro está limitado a um subconjunto dos formatos de pixels WIC nativos, 
			/// consulte a estrutura Guids::GUIDs_WIC_NATIVE_PIXEL_FORMATS para obter uma lista.</param>
			CarenResult Initialize(
				ICarenWICBitmapSource^ Param_FonteBitmap,
				ICarenWICColorContext^ Param_FonteContexto,
				ICarenWICColorContext^ Param_DestinoContexto,
				String^ Param_GuidFormatoPixelDestino);
		};
		
		/// <summary>
		/// (IWICEnumMetadataItem) - Interface responsável por expor métodos que fornecem serviços de enumeração para itens de metadados individuais. 
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("744DDDCF-AA64-45DB-983C-38E1B79ED57C")]
		public interface class ICarenWICEnumMetadataItem : ICaren
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
			/// Cria uma cópia do ICarenWICEnumMetadataItem atual. 
			/// </summary>
			/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro que representa uma cópia da interface atual.</param>
			CarenResult Clone([Out] ICarenWICEnumMetadataItem^% Param_Out_EnumMetadata);

			/// <summary>
			/// Avança a posição atual na enumeração. 
			/// </summary>
			/// <param name="Param_Quantidade">O número de itens a serem recuperados.</param>
			/// <param name="Param_Ref_ArraySchemas">Retorna uma variedade de itens enumerados. Este parâmetro é opcional.</param>
			/// <param name="Param_Out_ArrayIds">Retorna uma variedade de itens enumerados.</param>
			/// <param name="Param_Ref_ArrayValores">Retorna uma variedade de itens enumerados. Este parâmetro é opcional.</param>
			/// <param name="Param_Out_QuantRecuperados">O número de itens que foram recuperados. Esse valor é sempre menor ou igual ao número de itens solicitados.</param>
			CarenResult Next(
				UInt64 Param_Quantidade,
				cli::array<CA_PROPVARIANT^>^% Param_Ref_ArraySchemas,
				[Out] cli::array<CA_PROPVARIANT^>^% Param_Out_ArrayIds,
				cli::array<CA_PROPVARIANT^>^% Param_Ref_ArrayValores,
				[Out] UInt64% Param_Out_QuantRecuperados);

			/// <summary>
			/// Redefine a posição atual para o início da enumeração. 
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// Pula para um número determinado de objetos.
			/// </summary>
			/// <param name="Param_Quantidade">O número de objetos para pular.</param>
			CarenResult Skip(UInt64 Param_Quantidade);
		};

		/// <summary>
		/// (IWICMetadataHandlerInfo) - Interface responsável por expor métodos que fornecem informações básicas sobre o manipulador de metadados registrado.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("6FD3753D-ADAC-4A98-93AD-1DB3B4CACF32")]
		public interface class ICarenWICMetadataHandlerInfo : ICarenWICComponentInfo
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
			/// Determina se o manipulador de metadados requer um tamanho fixo. 
			/// </summary>
			/// <param name="Param_Out_FixedSize">Retorna TRUE se um tamanho fixo for necessário; caso contrário, FALSO.</param>
			CarenResult DoesRequireFixedSize([Out] Boolean% Param_Out_FixedSize);

			/// <summary>
			/// Determina se o manipulador requer um fluxo completo. 
			/// </summary>
			/// <param name="Param_Out_RequerFullStream">Retorna TRUE se um fluxo completo for necessário; caso contrário, FALSO.</param>
			CarenResult DoesRequireFullStream([Out] Boolean% Param_Out_RequerFullStream);

			/// <summary>
			/// Determina se o manipulador de metadados suporta preenchimento. 
			/// </summary>
			/// <param name="Param_Out_SuportaPadding">Retorna TRUE se o preenchimento for suportado; caso contrário, FALSO.</param>
			CarenResult DoesSupportPadding([Out] Boolean% Param_Out_SuportaPadding);

			/// <summary>
			/// Recupera os formatos de contêiner suportados pelo manipulador de metadados. 
			/// </summary>
			/// <param name="Param_TamanhoArray"><O tamanho da matriz (Param_Out_ArrayGuidsFormatosContainer)./param>
			/// <param name="Param_Out_ArrayGuidsFormatosContainer">Retorna uma matriz que recebe os formatos de contêiner suportados pelo manipulador de metadados. O usuário deve criar matriz com a capacidade
            /// indicada no (Param_TamanhoArray).</param>
			/// <param name="Param_Out_QuantidadeRetornada">Retorna o número real de GUIDs adicionados à matriz. Para obter o número de formatos de contêiner suportados, 
			/// passe NULO para (Param_Out_ArrayGuidsFormatosContainer).</param>
			CarenResult GetContainerFormats(
				UInt32 Param_TamanhoArray,
				[Out] cli::array<String^>^% Param_Out_ArrayGuidsFormatosContainer,
				[Out] UInt32% Param_Out_QuantidadeRetornada);

			/// <summary>
			/// Recupera o fabricante do dispositivo do manipulador de metadados. 
			/// </summary>
			/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceManufacturer).</param>
			/// <param name="Param_Ref_DeviceManufacturer">Retorna a String que recebe o nome do fabricante do dispositivo.</param>
			/// <param name="Param_Out_LarguraReal">Retorna o comprimento real da sequência de strinds necessário para obter o nome inteiro do fabricante do dispositivo.</param>
			CarenResult GetDeviceManufacturer(
				UInt32 Param_TamanhoBufferString,
				String^% Param_Ref_DeviceManufacturer,
				[Out] UInt32% Param_Out_LarguraReal);
			
			/// <summary>
			/// Recupera os modelos do dispositivo que suportam o manipulador de metadados. 
			/// </summary>
			/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceModels).</param>
			/// <param name="Param_Out_DeviceModels">Retorna os modelos do dispositivo suportados pelo manipulador de metadados.</param>
			/// <param name="Param_Out_LarguraReal">Retorna o comprimento real necessário para recuperar os modelos do dispositivo.</param>
			CarenResult GetDeviceModels(
				UInt32 Param_TamanhoBufferString,
				String^% Param_Ref_DeviceModels,
				[Out] UInt32% Param_Out_LarguraReal);

			/// <summary>
			/// Recupera o formato de metadados do manipulador de metadados. 
			/// </summary>
			/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
			CarenResult GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata);
		};

		/// <summary>
		/// (IWICMetadataReader) - Interface responsável por expor métodos que fornecem acesso ao conteúdo de metadados sublinhado. Essa interface é implementada por fornecedores 
		/// independentes de software (ISVs) para criar novos leitores de metadados. Um leitor de metadados pode ser usado para acessar blocos de metadados e itens dentro de um bloco 
		/// de metadados em vez de usar um leitor de consulta. Para acessar diretamente o leitor de metadados, consulte um decodificador ou seus quadros para a interface 
		/// ICarenWICMetadataBlockReader para enumerar cada leitor de metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("8DE22A52-944E-4FA3-896F-67A3F131CC49")]
		public interface class ICarenWICMetadataReader : ICaren
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
			/// Obtém o número de itens de metadados dentro do leitor.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Recebe o número de itens de metadados dentro do leitor.</param>
			CarenResult GetCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Retorna um enumerador de todos os itens de metadados.
			/// </summary>
			/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o enumerador de metadados.</param>
			CarenResult GetEnumerator([Out] ICarenWICEnumMetadataItem^% Param_Out_EnumMetadata);

			/// <summary>
			/// Obtém o formato de metadados associado ao leitor.
			/// </summary>
			/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
			CarenResult GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata);

			/// <summary>
			/// Obtém as informações do manipulador de metadados associadas ao leitor.
			/// </summary>
			/// <param name="Param_Out_HandlerInfo">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o ICarenWICMetadataHandlerInfo.</param>
			CarenResult GetMetadataHandlerInfo([Out] ICarenWICMetadataHandlerInfo^% Param_Out_HandlerInfo);

			/// <summary>
			/// Obtém o valor do item metadados.
			/// </summary>
			/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
			/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
			/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
			CarenResult GetValue(
				CA_PROPVARIANT^ Param_Schema,
				CA_PROPVARIANT^ Param_Id,
				[Out] CA_PROPVARIANT^% Param_Out_Valor);

			/// <summary>
			/// Obtém o item metadados no índice dado.
			/// </summary>
			/// <param name="Param_Index">O índice do item metadados para recuperar.</param>
			/// <param name="Param_Out_Schema">Retorna uma estrutura para a propriedade do esquema do item de metadados.</param>
			/// <param name="Param_Out_Id">Retorna uma estrutra para o id do item metadados.</param>
			/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
			CarenResult GetValueByIndex(
				UInt32 Param_Index,
				[Out] CA_PROPVARIANT^% Param_Out_Schema,
				[Out] CA_PROPVARIANT^% Param_Out_Id,
				[Out] CA_PROPVARIANT^% Param_Out_Valor);
		};

		/// <summary>
		/// (IWICMetadataWriter) - Interface responsável por expor métodos que fornecem acesso à escrita de conteúdo de metadados. Isso é implementado por fornecedores de software 
		/// independentes (ISVs) para criar novos escritores de metadados. Um escritor de metadados pode ser usado para escrever blocos de metadados e itens dentro de um bloco de metadados 
		/// em vez de usar um escritor de consulta. Para acessar diretamente o escritor de metadados, consulte um codificador ou seus quadros para a interface ICarenWICMetadataBlockWriter 
		/// para enumerar cada escritor de metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("47227B49-9015-4817-ADD0-28C71A5D0773")]
		public interface class ICarenWICMetadataWriter : ICarenWICMetadataReader
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
			/// Remove o item metadados que corresponde aos parâmetros determinados. 
			/// </summary>
			/// <param name="Param_Schema">Uma estrutura para a propriedade do esquema de metadados.</param>
			/// <param name="Param_Id">Uma estrutura para a propriedade de id metadata.</param>
			CarenResult RemoveValue(
				CA_PROPVARIANT^ Param_Schema,
				CA_PROPVARIANT^ Param_Id);

			/// <summary>
			/// Remove o item metadados no índice especificado. 
			/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
			/// metadados restantes, bem como a contagem mudará.
			/// </summary>
			/// <param name="Param_Index">O índice do item metadados para remover.</param>
			CarenResult RemoveValueByIndex(UInt32 Param_Index);

			/// <summary>
			/// Define o item de metadados dado.
			/// </summary>
			/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
			/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
			/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
			CarenResult SetValue(
				CA_PROPVARIANT^ Param_Schema,
				CA_PROPVARIANT^ Param_Id,
				CA_PROPVARIANT^ Param_Valor);

			/// <summary>
			/// Define o item metadados no índice especificado.
			/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
			/// metadados restantes, bem como a contagem mudará.
			/// </summary>
			/// <param name="Param_Index">O índice do item metadados para definir.</param>
			/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
			/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
			/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
			CarenResult SetValueByIndex(
				UInt32 Param_Index,
				CA_PROPVARIANT^ Param_Schema,
				CA_PROPVARIANT^ Param_Id,
				CA_PROPVARIANT^ Param_Valor);
		};

		/// <summary>
		/// (IWICMetadataBlockReader) - Interface responsável por expor métodos que fornecem acesso a todos os blocos de metadados de nível superior do codec.
		/// ICarenWICMetadataBlockReader e ICarenWICMetadataBlockWriter operam apenas no nível raiz; ou seja, eles fornecem acesso de leitura e gravação, respectivamente, aos blocos 
		/// de metadados de nível superior. Eles são implementados pelo ICarenWICBitmapFrameDecode e pelo ICarenWICBitmapFrameEncode, respectivamente. Para lidar com quaisquer blocos de 
		/// metadados que não estejam no nível superior da hierarquia, use ICarenWICMetadataReader ou ICarenWICMetadataWriter.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("E1EC62C3-5B1C-4A9B-B496-6FBDB3606711")]
		public interface class ICarenWICMetadataBlockReader : ICaren
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
			/// Recupera o formato do recipiente do decodificador. 
			/// </summary>
			/// <param name="Param_Out_GuidFormatoContainer">Retorna o formato do contêiner do decodificador. </param>
			CarenResult GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer);

			/// <summary>
			/// Recupera o número de blocos de metadados de nível superior. 
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna o número de blocos de metadados de nível superior.</param>
			CarenResult GetCount([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// Recupera uma enumeração dos objetos ICarenWICMetadataReader representando cada um dos blocos de metadados de nível superior. 
			/// </summary>
			/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para uma enumeração dos objetos ICarenWICMetadataReader.</param>
			CarenResult GetEnumerator([Out] ICarenEnumUnknown^% Param_Out_EnumMetadata);

			/// <summary>
			/// Recupera um ICarenWICMetadataReader para um bloco de metadados de nível superior especificado. 
			/// </summary>
			/// <param name="Param_Index">O índice do bloco de metadados de nível superior desejado para recuperar.</param>
			/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o ICarenWICMetadataReader especificado por (Param_Index).</param>
			CarenResult GetReaderByIndex(
				UInt32 Param_Index,
				[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);
		};

		/// <summary>
		/// (IWICMetadataBlockWriter) - Interface responsável por expor métodos que permitem a codificação de metadados. Essa interface é implementada pelo decodificador e seus frames de imagem.
		/// Quando o codificador é instruído a se comprometer, ele passa por cada escritor de metadados e serializa o conteúdo de metadados no fluxo de codificação. Se o bloco de 
		/// metadados contiver metadados importantes para a integridade do arquivo, como a largura ou altura da imagem ou outras informações intrínsecas sobre a imagem, o codificador deve 
		/// definir os itens de metadados críticos antes de serializar os metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("2CE6D8B3-99DB-4058-A1F0-05B562522E45")]
		public interface class ICarenWICMetadataBlockWriter : ICarenWICMetadataBlockReader
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
			/// Adiciona um bloco de metadados de alto nível adicionando um ICarenWICMetadataWriter para ele. 
			/// </summary>
			/// <param name="Param_MetadataWriter">O escritor de metadados para adicionar à imagem.</param>
			CarenResult AddWriter(ICarenWICMetadataWriter^ Param_MetadataWriter);

			/// <summary>
			/// Recupera o ICarenWICMetadataWriter que reside no índice especificado. 
			/// </summary>
			/// <param name="Param_Index">O índice do escritor de metadados a ser recuperado. Este índice é baseado em zero.</param>
			/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados que reside no índice especificado.</param>
			CarenResult GetWriterByIndex(
				UInt32 Param_Index,
				[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

			/// <summary>
			/// Inicializa um ICarenWICMetadataBlockWriter do dado ICarenWICMetadataBlockReader. Isso prepovoará o autor do bloco de metadados com todos os metadados no leitor de blocos de metadados. 
			/// </summary>
			/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataBlockReader) que será usada para inicializar o escritor.</param>
			CarenResult InitializeFromBlockReader(ICarenWICMetadataBlockReader^ Param_MetadataReader);

			/// <summary>
			/// Remove o escritor de metadados do local do índice especificado.
			/// Depois de remover um escritor de metadados, espera-se que os escritores de metadados restantes se movam para ocupar o local desocupado. Os índices para itens de 
			/// metadados restantes, bem como a contagem, mudarão.
			/// </summary>
			/// <param name="Param_Index">O índice do escritor de metadados para remover.</param>
			CarenResult RemoveWriterByIndex(UInt32 Param_Index);

			/// <summary>
			/// Substitui o escritor de metadados no local do índice especificado.
			/// Normalmente, o escritor de metadados atuais no índice especificado será substituído pelo novo escritor. No entanto, o autor de metadados app0 não pode ser 
			/// substituído dentro de um fluxo JPEG. Esta função não pode ser usada para adicionar escritores de metadados. Se não houver nenhum autor de metadados no índice especificado, a função falhará.
			/// </summary>
			/// <param name="Param_Index">A posição do índice para colocar o escritor de metadados. Este índice é baseado em zero.</param>
			/// <param name="Param_MetadataWriter">A interface de escrita de metadados a ser definida no indice.</param>
			CarenResult SetWriterByIndex(
				UInt32 Param_Index,
				ICarenWICMetadataWriter^ Param_MetadataWriter);
		};

		/// <summary>
		/// (IWICFastMetadataEncoder) - Interface responsável por expor métodos usados para edição de metadados no local. Um codificador rápido de metadados permite adicionar 
		/// e remover metadados a uma imagem sem ter que recodificar totalmente a imagem.
		/// Nem todos os formatos de metadados suportam codificação rápida de metadados. Os manipuladores de metadados nativos que suportam metadados são IFD, Exif, XMP e GPS.
		/// Um decodificador deve ser criado usando o código WICDecodeOptions de valor WICDecodeMetadataCacheOnDemand para executar atualizações de metadados no local. O uso da 
		/// opção WICDecodeMetadataCacheOnLoad faz com que o decodificador libere o fluxo de arquivos necessário para realizar as atualizações de metadados.
		/// Se um codificador de metadados rápidos falhar, a imagem precisará ser totalmente recodificada para adicionar os metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("7D8CFBA3-0944-4D2D-970D-EDCBC37ABA7D")]
		public interface class ICarenWICFastMetadataEncoder : ICaren
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
			/// Finaliza as alterações de metadados no fluxo de imagem. 
			/// </summary>
			CarenResult Commit();

			/// <summary>
			/// Recupera um escritor de consulta de metadados para codificação rápida de metadados. 
			/// </summary>
			/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de 
			/// metadados de metadados rápidos do codificador.</param>
			CarenResult GetMetadataQueryWriter([Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);
		};

		/// <summary>
		/// (IWICFormatConverter) - Interface responsável por representar um ICarenWICBitmapSource que converte os dados da imagem de um formato de pixel para outro, 
		/// manipulando pontilhamento e meio-tom em formatos indexados, tradução de paleta e limiar alfa.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("A957812C-7826-479C-AF0D-981F5993A525")]
		public interface class ICarenWICFormatConverter : ICarenWICBitmapSource
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
			/// Determina se o formato de pixel de origem pode ser convertido para o formato de pixel de destino. 
			/// </summary>
			/// <param name="Param_GuidFormatoPixelOrigem">O formato de pixel de origem.</param>
			/// <param name="Param_GuidFormatoPixelDestino">O formato de pixel de destino.</param>
			/// <param name="Param_Out_Conversao">Retorna um valor indicando se o formato de pixel de origem pode ser convertido para o formato de pixel de destino.</param>
			CarenResult CanConvert(
				String^ Param_GuidFormatoPixelOrigem,
				String^ Param_GuidFormatoPixelDestino,
				[Out] Boolean% Param_Out_Conversao);

			/// <summary>
			/// Inicializa o conversor de formato. 
			/// Se você não tem uma paleta predefinida, você deve primeiro criar uma. Use ICarenWICPalette::InitializeFromBitmap para criar o objeto paleta e, em seguida, 
			/// passe-o junto com seus outros parâmetros. Param_Dither, Param_Paleta, Param_PorcentagemAlfa e Param_TipoPaletaConversao são usados para mitigar a perda de 
			/// cor ao converter para um formato de profundidade de bit reduzida. Para conversões que não precisam dessas configurações, devem ser utilizados os seguintes 
			/// parâmetros: Param_Dither defina para WICBitmapDitherTypeNone, Param_Paleta defina como NULO, Param_PorcentagemAlfa definido para 0.0f e Param_TipoPaletaConversao 
			/// para WICBitmapPaletteTypeCustom.
			/// </summary>
			/// <param name="Param_BitmapFonte">O bitmap de entrada para converter</param>
			/// <param name="Param_GuidFormatoPixelDestino">O formato de pixel de destino.</param>
			/// <param name="Param_Dither">O WICBitmapDitherType usado para conversão.</param>
			/// <param name="Param_Paleta">A paleta para usar para conversão.</param>
			/// <param name="Param_PorcentagemAlfa">O limiar alfa a ser usado para conversão.</param>
			/// <param name="Param_TipoPaletaConversao">O tipo de tradução da paleta para usar para conversão.</param>
			CarenResult Initialize(
				ICarenWICBitmapSource^ Param_BitmapFonte,
				String^ Param_GuidFormatoPixelDestino,
				CA_WICBitmapDitherType Param_Dither,
				ICarenWICPalette^ Param_Paleta,
				double Param_PorcentagemAlfa,
				CA_WICBitmapPaletteType Param_TipoPaletaConversao);
		};

		/// <summary>
		/// (IWICImageEncoder) - Interface responsável por Codificar interfaces ICarenD2D1Image para um ICarenWICBitmapEncoder. As imagens de entrada podem ser maiores do 
		/// que o tamanho máximo da textura do dispositivo.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("F5462A04-EAA5-4989-A52E-36C81563E4E7")]
		public interface class ICarenWICImageEncoder : ICaren
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
			/// Codifica a imagem para o frame dado pelo ICarenWICBitmapFrameEncode. 
			/// A imagem passada deve ser criada no mesmo dispositivo do ICarenWICImagingFactory2::CreateImageEncoder. Se os (Param_ParametrosAdicionais) não forem especificados,
			///  um conjunto de padrões úteis será assumido.
			/// Você deve ter configurado corretamente e de forma independente o ICarenWICBitmapFrameEncode antes de chamar esta API.
			/// </summary>
			/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
			/// <param name="Param_FrameEncode">Uma interface(ICarenWICBitmapFrameEncode) que representa o codificador de frames para o qual a imagem está escrita.</param>
			/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
			CarenResult WriteFrame(
				ICaren^ Param_D2D1Image,
				ICarenWICBitmapFrameEncode^ Param_FrameEncode,
				CA_WICImageParameters^ Param_ParametrosAdicionais);

			/// <summary>
			/// Codifica a imagem como uma miniatura do quadro dado pelo ICarenWICBitmapFrameEncode.
			/// A imagem passada deve ser criada no mesmo dispositivo do ICarenWICImagingFactory2::CreateImageEncoder. Se os (Param_ParametrosAdicionais) não forem especificados, um 
			/// conjunto de padrões úteis será assumido.
			/// Você deve ter configurado corretamente e de forma independente o ICarenWICBitmapFrameEncode antes de chamar esta API.
			/// </summary>
			/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
			/// <param name="Param_FrameEncode">Uma interface(ICarenWICBitmapFrameEncode) que representa o codificador de frames para o qual a miniatura está definida.</param>
			/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
			CarenResult WriteFrameThumbnail(
				ICaren^ Param_D2D1Image,
				ICarenWICBitmapFrameEncode^ Param_FrameEncode,
				CA_WICImageParameters^ Param_ParametrosAdicionais);

			/// <summary>
			/// Codifica a imagem dada como miniatura do codificador de bitmap WIC dado. 
			/// Você deve criar a imagem que você passa no mesmo dispositivo que no ICarenWICImagingFactory2::CreateImageEncoder. Se você não especificar parâmetros adicionais na 
			/// variável que (Param_ParametrosAdicionais) aponta, o codificador usará um conjunto de padrões úteis.
			/// Antes de chamar WriteThumbnail, você deve configurar a interface ICarenWICBitmapEncoder para o codificador no qual deseja definir a miniatura.
			/// Se o WriteThumbnail falhar, ele poderá retornar E_OUTOFMEMORY, D2DERR_WRONG_RESOURCE_DOMAIN ou outros códigos de erro do codificador.
			/// </summary>
			/// <param name="Param_D2D1Image">Uma interface(ICarenD2D1Image) que representa a imagem Direct2D que será codificada.</param>
			/// <param name="Param_BitmapEncoder">Uma interface(ICarenWICBitmapEncoder) que representa o codificador em que a miniatura está definida.</param>
			/// <param name="Param_ParametrosAdicionais">Parâmetros adicionais para controlar a codificação.</param>
			CarenResult WriteThumbnail(
				ICaren^ Param_D2D1Image,
				ICarenWICBitmapEncoder^ Param_BitmapEncoder,
				CA_WICImageParameters^ Param_ParametrosAdicionais);
		};

		/// <summary>
		/// (IWICImagingFactory) - Interface responsável por expor métodos usados para criar componentes para o WIC, como decodificadores, codificadores e conversores de formato de pixel.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("5F364FFC-9964-4E46-8A54-2F3B37F980B5")]
		public interface class ICarenWICImagingFactory : ICaren
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
			/// Cria um objeto ICarenWICBitmap. 
			/// </summary>
			/// <param name="Param_Width">A largura do novo bitmap .</param>
			/// <param name="Param_Height">A altura do novo bitmap.</param>
			/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap.</param>
			/// <param name="Param_OpcoesCache">As opções de criação de cache do novo bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmap(
				UInt32 Param_Width,
				UInt32 Param_Height,
				String^ Param_GuidFormatoPixel,
				CA_WICBitmapCreateCacheOption Param_OpcoesCache,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria uma nova instância de um objeto ICarenWICBitmapClipper. 
			/// </summary>
			/// <param name="Param_Out_BitmapClipper">Retorna uma interface(Param_Out_BitmapClipper) que contém um ponteiro para o novo Clipper.</param>
			CarenResult CreateBitmapClipper([Out] ICarenWICBitmapClipper^% Param_Out_BitmapClipper);

			/// <summary>
			/// Cria uma nova instância de um objeto ICarenWICBitmapFlipRotator. 
			/// </summary>
			/// <param name="Param_Out_BitmapFlipRotator">Retorna uma interface(ICarenWICBitmapFlipRotator) que contém um ponteiro para o novo rotacionador de bitmap.</param>
			CarenResult CreateBitmapFlipRotator([Out] ICarenWICBitmapFlipRotator^% Param_Out_BitmapFlipRotator);
			
			/// <summary>
			/// Cria um ICarenWICBitmap a partir de uma Handle para o bitmap. 
			/// </summary>
			/// <param name="Param_HandleBitmap">Uma handle para o bitmap para criar o bitmap.</param>
			/// <param name="Param_HandlePaleta">Uma handle para a palleta usada para criar o bitmap.</param>
			/// <param name="Param_OpcoesCanalAlfa">As opções do canal alfa para criar o bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromHBITMAP(
				IntPtr Param_HandleBitmap,
				IntPtr Param_HandlePaleta,
				CA_WICBitmapAlphaChannelOption Param_OpcoesCanalAlfa,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ICarenWICBitmap a partir de uma handle para o ícone. 
			/// </summary>
			/// <param name="Param_HandleIcon">Uma handle para o ícone para criar o bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromHICON(
				IntPtr Param_HandleIcon,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ICarenWICBitmap a partir de um bloco de memória. O tamanho do ICarenWICBitmap a ser criado deve ser menor ou igual ao tamanho da imagem em (Param_Buffer).
			/// O Stride do bitmap de destino será igual ao Stride dos dados de origem, independentemente da largura e altura especificados.
			/// O parâmetro (Param_GuidFormatoPixel) define o formato de pixel tanto para os dados de entrada quanto para o bitmap de saída.
			/// </summary>
			/// <param name="Param_Width">A largura do novo bitmap.</param>
			/// <param name="Param_Height">A altura do novo bitmap.</param>
			/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap. Consulte a estrutura (GUIDs_WIC_NATIVE_PIXEL_FORMATS) para obter uma lista de guids para esse parametro.</param>
			/// <param name="Param_Stride">O número de bytes entre linhas de varredura sucessivas em (Param_Buffer).</param>
			/// <param name="Param_BufferSize">O tamanho do (Param_Buffer).</param>
			/// <param name="Param_Buffer">O buffer usado para criar o bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromMemory(
				UInt32 Param_Width,
				UInt32 Param_Height,
				String^ Param_GuidFormatoPixel,
				UInt32 Param_Stride,
				UInt32 Param_BufferSize,
				ICarenBuffer^ Param_Buffer,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ICarenWICBitmap a partir de um ICarenWICBitmapSource. 
			/// </summary>
			/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
			/// <param name="Param_OpcoesCache">As opções de cache do novo bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromSource(
				ICarenWICBitmapSource^ Param_FonteBitmap,
				CA_WICBitmapCreateCacheOption Param_OpcoesCache,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria um ICarenWICBitmap a partir de um retângulo especificado de um ICarenWICBitmapSource. Fornecer um retângulo maior que a fonte produzirá resultados indefinidos.
			/// Este método sempre cria uma cópia separada da imagem de origem, semelhante à opção de cache WICBitmapCacheOnLoad.
			/// </summary>
			/// <param name="Param_FonteBitmap">>Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
			/// <param name="Param_X">A coordenada horizontal do canto superior esquerdo do retângulo.</param>
			/// <param name="Param_Y">A coordenada vertical do canto superior esquerdo do retângulo.</param>
			/// <param name="Param_Width">A largura do retângulo e o novo bitmap.</param>
			/// <param name="Param_Height">A altura do retângulo e o novo bitmap.</param>
			/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
			CarenResult CreateBitmapFromSourceRect(
				ICarenWICBitmapSource^ Param_FonteBitmap,
				UInt32 Param_X,
				UInt32 Param_Y,
				UInt32 Param_Width,
				UInt32 Param_Height,
				[Out] ICarenWICBitmap^% Param_Out_Bitmap);

			/// <summary>
			/// Cria uma nova instância de um IWICBitmapScaler. 
			/// </summary>
			/// <param name="Param_Out_BitmapScaler">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo redimensionador.</param>
			CarenResult CreateBitmapScaler([Out] ICarenWICBitmapScaler^% Param_Out_BitmapScaler);

			/// <summary>
			/// Cria uma nova instância da classe IWICColorContext. 
			/// </summary>
			/// <param name="Param_Out_WicColorContext">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo contexto de cores.</param>
			CarenResult CreateColorContext([Out] ICarenWICColorContext^% Param_Out_WicColorContext);

			/// <summary>
			/// Cria uma nova instância da classe IWICColorTransform. 
			/// </summary>
			/// <param name="Param_Out_WicColorTransform">Retorna uma interface(ICarenWICColorTransform) que contém um ponteiro para o novo transformado de contexto de cor.</param>
			CarenResult CreateColorTransformer([Out] ICarenWICColorTransform^% Param_Out_WicColorTransform);

			/// <summary>
			/// Cria um objeto IEnumUnknown dos tipos de componentes especificados. 
			/// Os tipos de componentes devem ser enumerados separadamente. Combinações de tipos de componentes e WICAllComponents não são suportadas.
			/// </summary>
			/// <param name="Param_TiposComponentes">Os tipos de WICComponentType para enumerar.</param>
			/// <param name="Param_OpcoesEnumeracao">As Opções WICComponentEnumerate utilizadas para enumerar os tipos de componentes dado.</param>
			/// <param name="Param_Out_Enumerador">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para um novo enumerador de componentes.</param>
			CarenResult CreateComponentEnumerator(
				CA_WICComponentType Param_TiposComponentes,
				CA_WICComponentEnumerateOptions Param_OpcoesEnumeracao,
				[Out] ICarenEnumUnknown^% Param_Out_Enumerador);

			/// <summary>
			/// Cria uma nova instância da classe IWICComponentInfo para o identificador de classe de componentes dado (CLSID). 
			/// </summary>
			/// <param name="Param_ClsidComponente">O CLSID para o componente desejado.</param>
			/// <param name="Param_Out_ComponenteInfo">Retorna uma interface(ICarenWICComponentInfo) que contém um ponteiro para um novo informador de componente.</param>
			CarenResult CreateComponentInfo(
				String^ Param_ClsidComponente,
				[Out] ICarenWICComponentInfo^% Param_Out_ComponenteInfo);

			/// <summary>
			/// Cria uma nova instância do ICarenWICBitmapDecoder. 
			/// </summary>
			/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado.</param>
			/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido.</param>
			/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador. Você deve inicializar este 
			/// ICarenWICBitmapDecoder em um fluxo usando o método (Initialize) mais tarde.</param>
			CarenResult CreateDecoder(
				String^ Param_GuidFormatoContainer,
				String^ Param_GuidVendor,
				[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);
			
			/// <summary>
			/// Cria uma nova instância do ICarenWICBitmapDecoder com base na handle de arquivo dada. 
			/// </summary>
			/// <param name="Param_HandleArquivo">A handle para o arquivo para ser utilizado para criar o decodifciador.</param>
			/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
			/// <param name="Param_OpcoesDecoder">As opções de código WIC para usar ao criar o decodificador.</param>
			/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
			CarenResult CreateDecoderFromFileHandle(
				UInt64 Param_HandleArquivo,
				String^ Param_GuidVendor,
				CA_WICDecodeOptions Param_OpcoesDecoder,
				[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no arquivo dado. 
			/// </summary>
			/// <param name="Param_UrlArquivo">Uma string que especifica o nome de um objeto para criar ou abrir.</param>
			/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
			/// <param name="Param_TipoAcesso">O acesso ao objeto, que pode ser lido, escrito ou ambos.</param>
			/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
			/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
			CarenResult CreateDecoderFromFilename(
				String^ Param_UrlArquivo,
				String^ Param_GuidVendor,
				CA_ACCESS_RIGHTS Param_TipoAcesso,
				CA_WICDecodeOptions Param_OpcoesMetadata,
				[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no ICarenStream dado. 
			/// </summary>
			/// <param name="Param_Fluxo">O fluxo para criar o decodificador.</param>
			/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULL se não houver fornecedor preferencial.</param>
			/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
			/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
			CarenResult CreateDecoderFromStream(
				ICarenStream^ Param_Fluxo,
				String^ Param_GuidVendor,
				CA_WICDecodeOptions Param_OpcoesMetadata,
				[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICBitmapDecoder. Os valores disponiveis para (Param_GuidFormatoContainer) e (Param_GuidVendor) listados aqui, não são os unicos disponiveis.
			/// Esses são apenas os valores suportados nativamente pelo sistema operacional e não incluem codecs de terceiros que possam está habilitados para o WIC.
			/// </summary>
			/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado. Consulte a estrutura (GUIDs_WIC_CONTAINERS_FORMATOS) para obter um dos codecs 
			/// suportados pelo OS nativamente.</param>
			/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido. Consulte a estrutura (GUIDs_WIC_VENDORS) paraobter um dos fornecedores de codificadores 
			/// suportados pelo OS nativamente.</param>
			/// <param name="Param_Out_BitmapEncoder">Retorna uma interface(ICarenWICBitmapEncoder) que contém um ponteiro para o novo codificador.</param>
			CarenResult CreateEncoder(
				String^ Param_GuidFormatoContainer,
				String^ Param_GuidVendor,
				[Out] ICarenWICBitmapEncoder^% Param_Out_BitmapEncoder);

			/// <summary>
			/// Cria uma nova instância do codificador de metadados rápidos baseado no determinado ICarenWICBitmapDecoder.
			/// Os codecs fornecidos pelo Windows não oferecem suporte à codificação rápida de metadados no nível do decodificador e apenas suportam codificação rápida de metadados no 
			/// nível do frame. Para criar um codificador de metadados rápido a partir de um frame, consulte o método CreateFastMetadataEncoderFromFrameDecode.
			/// </summary>
			/// <param name="Param_Decoder">O decodificador para criar o codificador de metadados rápidos.</param>
			/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
			CarenResult CreateFastMetadataEncoderFromDecoder(
				ICarenWICBitmapDecoder^ Param_Decoder,
				[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder);

			/// <summary>
			/// Cria uma nova instância do codificador de metadados rápidos com base no frame de imagem dado. 
			/// </summary>
			/// <param name="Param_BitmapFrameDecode">Um ICarenWICBitmapFrameDecode que será utilizado para criar o ICarenWICFastMetadataEncoder.</param>
			/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
			CarenResult CreateFastMetadataEncoderFromFrameDecode(
				ICarenWICBitmapFrameDecode^ Param_BitmapFrameDecode,
				[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICFormatConverter. 
			/// </summary>
			/// <param name="Param_Out_FormatConverter">Retorna uma interface(ICarenWICFormatConverter) que contém um ponteiro para o novo conversor de formato de pixels.</param>
			CarenResult CreateFormatConverter([Out] ICarenWICFormatConverter^% Param_Out_FormatConverter);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICPalette. 
			/// </summary>
			/// <param name="Param_Out_WicPaleta">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a nova tabela de cores.</param>
			CarenResult CreatePalette([Out] ICarenWICPalette^% Param_Out_WicPaleta);

			/// <summary>
			/// Cria uma nova instância de um escritor de consultas. 
			/// </summary>
			/// <param name="Param_GuidFormatoMetadata">O GUID para o formato de metadados desejado.</param>
			/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
			/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
			CarenResult CreateQueryWriter(
				String^ Param_GuidFormatoMetadata,
				String^ Param_GuidVendor,
				[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter);

			/// <summary>
			/// Cria uma nova instância de um escritor de consulta com base no leitor de consultas. O escritor de consultas será pré-povoado com metadados do leitor de consulta. 
			/// </summary>
			/// <param name="Param_QueryReader">O ICarenWICMetadataQueryReader para criar o ICarenWICMetadataQueryWriter.</param>
			/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
			/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
			CarenResult CreateQueryWriterFromReader(
				ICarenWICMetadataQueryReader^ Param_QueryReader,
				String^ Param_GuidVendor,
				[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter);

			/// <summary>
			/// Cria uma nova instância da classe ICarenWICStream. 
			/// </summary>
			/// <param name="Param_Out_WicStream">Retorna uma interface(ICarenWICStream) que contém um ponteiro para o novo fluxo WIC.</param>
			CarenResult CreateStream([Out] ICarenWICStream^% Param_Out_WicStream);
		};

		/// <summary>
		/// (IWICImagingFactory2) - A interface responsável por representar uma extensão da interface de fábrica WIC(ICarenWICImagingFactory) que inclui a capacidade de criar um 
		/// ICarenWICImageEncoder. Esta interface usa um dispositivo Direct2D e uma imagem de entrada para codificar para um ICarenWICBitmapEncoder de destino.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("372BB048-8207-4EDD-9D69-497A833DBD10")]
		public interface class ICarenWICImagingFactory2 : ICarenWICImagingFactory
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
			/// Cria um novo objeto codificador de imagem a paerti de um Dispositivo do Direct2D. Você deve criar imagens para passar para o codificador de imagem no mesmo dispositivo 
			/// Direct2D que você passa para este método.
			/// Você é responsável por configurar o codificador de bitmap em si através das APIs existentes do ICarenWICBitmapEncoder. O objeto ICarenWICBitmapEncoder ou o ICarenWICBitmapFrameEncode
			///  é passado para cada um dos métodos 
			/// ICarenWICImageEncoder::WriteThumbnail, WriteFrame e WriteFrameThumbnail.
			/// </summary>
			/// <param name="Param_D2DDevice">Uma interface(ICarenD2D1Device) do dispostivo do Direct2D no qual o codificador de imagem correspondente é criado.</param>
			/// <param name="Param_Out_ImageEncoder">Retorna uma interface(ICarenWICImageEncoder) que contém um ponteiro para o novo objeto codificador que você pode usar para codificar imagens do Direct2D.</param>
			CarenResult CreateImageEncoder(
				ICaren^ Param_D2DDevice,
				[Out] ICarenWICImageEncoder^% Param_Out_ImageEncoder);
		};

		/// <summary>
		/// (IWICComponentFactory) - Interface responsável por expor métodos que criam componentes usados pelos desenvolvedores de componentes. Isso inclui leitores de metadados, gravadores 
		/// e outros serviços para uso dos desenvolvedores de codec e manipuladores de metadados.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("E228CA43-06E1-4292-806D-6F3FF9FFB70D")]
		public interface class ICarenWICComponentFactory : ICarenWICImagingFactory
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
			/// Cria uma bag de propriedades do codificador. 
			/// </summary>
			/// <param name="Param_ArrayPropOptions">Uma matriz de estruturas(CA_PROPBAG2) usadas para criar a bag de propriedades do codificador.</param>
			/// <param name="Param_Quantidade">A quantidade de items na matriz em (Param_ArrayPropOptions).</param>
			/// <param name="Param_Out_PropertyBag">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a nova bag de propriedades do codificador.</param>
			CarenResult CreateEncoderPropertyBag(
				cli::array<CA_PROPBAG2^>^ Param_ArrayPropOptions,
				UInt32 Param_Quantidade,
				[Out] ICarenPropertyBag2^% Param_Out_PropertyBag);

			/// <summary>
			/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
			/// </summary>
			/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
			/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
			/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
			/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
			/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
			CarenResult CreateMetadataReader(
				String^ Param_GuidFormatoMetadata,
				String^ Param_GuidVendor,
				UInt32 Param_Opcoes,
				ICarenStream^ Param_Fluxo,
				[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);

			/// <summary>
			/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
			/// </summary>
			/// <param name="Param_GuidFormatoContainer">O formato de contêiner GUID para basear o leitor.</param>
			/// <param name="Param_GuidVendor">O fornecedor GUID do leitor de metadados.</param>
			/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
			/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
			/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
			CarenResult CreateMetadataReaderFromContainer(
				String^ Param_GuidFormatoContainer,
				String^ Param_GuidVendor,
				UInt32 Param_Opcoes,
				ICarenStream^ Param_Fluxo,
				[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);

			/// <summary>
			/// Cria um ICarenWICMetadataWriter baseado nos parâmetros determinados. 
			/// </summary>
			/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
			/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
			/// <param name="Param_OpcoesMetadata">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o escritor de metadados.</param>
			/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
			CarenResult CreateMetadataWriter(
				String^ Param_GuidFormatoMetadata,
				String^ Param_GuidVendor,
				UInt32 Param_OpcoesMetadata,
				[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

			/// <summary>
			/// Cria um ICarenWICMetadataWriter do dado ICarenWICMetadataReader. 
			/// </summary>
			/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataReader) para o leitor de metadados para basear o escritor de metadados.</param>
			/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
			/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
			CarenResult CreateMetadataWriterFromReader(
				ICarenWICMetadataReader^ Param_MetadataReader,
				String^ Param_GuidVendor,
				[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

			/// <summary>
			/// Cria um ICarenWICMetadataQueryReader a partir do ICarenWICMetadataBlockReader. 
			/// </summary>
			/// <param name="Param_MetadataBlockReader">Uma interface(ICarenWICMetadataQueryReader) para o leitor de bloco para basear o escritor de consulta.</param>
			/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o novo leitor de consulta de metadados.</param>
			CarenResult CreateQueryReaderFromBlockReader(
				ICarenWICMetadataBlockReader^ Param_MetadataBlockReader,
				[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader);

			/// <summary>
			/// Cria um ICarenWICMetadataQueryWriter do dado ICarenWICMetadataBlockWriter. 
			/// </summary>
			/// <param name="Param_MetadataBlockWriter">Uma interface(ICarenWICMetadataBlockWriter) para o escritor de bloco para basear o escritor de consulta.</param>
			/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consulta de metadados.</param>
			CarenResult CreateQueryWriterFromBlockWriter(
				ICarenWICMetadataBlockWriter^ Param_MetadataBlockWriter,
				[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);
		};		

		/// <summary>
		/// (IWICDdsDecoder) - Interface responsável por fornecer informações e funcionalidades específicas para o formato de imagem DDS.
		/// Esta interface é implementada pelo codec WIC DDS. Para obter esta interface, crie um ICarenWICBitmapDecoder usando o codec DDS e o ICaren::ConsultarInterface para ICarenWICDdsDecoder.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("9810B120-BD66-4B57-8F2A-EBC31032943E")]
		public interface class ICarenWICDdsDecoder : ICaren
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
			/// Recupera o frame especificado da imagem DDS. 
			/// Um arquivo DDS pode conter várias imagens organizadas em uma hierarquia de três níveis. Primeiro, o arquivo DDS pode conter múltiplas texturas em uma matriz de texturas. 
			/// Em segundo lugar, cada textura pode ter vários níveis de mip. 
			/// Por fim, a textura pode ser uma textura 3D (volume) e ter várias fatias, cada uma delas com textura 2D. Consulte a documentação do DDS para obter mais informações.
			/// </summary>
			/// <param name="Param_ArrayIndex">O índice solicitado dentro da matriz de texturas.</param>
			/// <param name="Param_MipLevel">O nível mip solicitado.</param>
			/// <param name="Param_SliceIndex">A fatia solicitada dentro da textura 3D.</param>
			/// <param name="Param_Out_BitmapFrame">Retorna uma interface(ICarenWICBitmapFrameDecode) que contém um ponteiro para a nova interface de decodificação de frames.</param>
			CarenResult GetFrame(
				UInt32 Param_ArrayIndex,
				UInt32 Param_MipLevel,
				UInt32 Param_SliceIndex,
				[Out] ICarenWICBitmapFrameDecode^% Param_Out_BitmapFrame);

			/// <summary>
			/// Obtém dados específicos do DDS. 
			/// </summary>
			/// <param name="Param_Out_Parametros">Retorna uam estrutura que contém informações especificas do DDS.</param>
			CarenResult GetParameters([Out] CA_WICDdsParameters^% Param_Out_Parametros);
		};
		
		
		/// <summary>
		/// (IWICDdsEncoder) - Interface responsável por permitir gravar informações específicas do formato DDS em um codificador.
		/// Esta interface é implementada pelo codec WIC DDS. Para obter esta interface, crie um ICarenWICBitmapEncoder usando o codec DDS e o ICaren::ConsultarInterface para ICarenWICDdsEncoder.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("BA4173AC-C585-49DD-8341-357EEBDB7E24")]
		public interface class ICarenWICDdsEncoder : ICaren
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
			/// Cria um novo frame para codificar. Isso equivale ao ICarenWICBitmapEncoder::CreateNewFrame, mas retorna informações adicionais sobre o índice de array, o nível de mip e 
			/// a fatia do quadro recém-criado. Em contraste com ICarenWICBitmapEncoder::CreateNewFrame, não há parâmetro ICarenPropertyBag2 porque os frames DDS individuais não têm propriedades separadas.
			/// </summary>
			/// <param name="Param_Out_FrameEncode">Retorna uma interface(ICarenWICBitmapFrameEncode) que contém um ponteiro para o novo frame.</param>
			/// <param name="Param_Out_ArrayIndex">Retorna o local onde o índice de matriz é devolvido. Opcional.</param>
			/// <param name="Param_Out_MipLevel">Retorna o local onde o índice de nível mip é devolvido. Opcional.</param>
			/// <param name="Param_Out_SliceIndex">Retorna o local onde o índice de fatia é devolvido. Opcional.</param>
			CarenResult CreateNewFrame(
				[Out] ICarenWICBitmapFrameEncode^% Param_Out_FrameEncode,
				[Out] UInt32% Param_Out_ArrayIndex,
				[Out] UInt32% Param_Out_MipLevel,
				[Out] UInt32% Param_Out_SliceIndex);

			/// <summary>
			/// Obtém dados específicos do DDS. Um aplicativo pode ligar para o GetParameters para obter os parâmetros DDS padrão, modificar alguns ou todos eles e, em seguida, chamar SetParameters.
			/// </summary>
			/// <param name="Param_Out_Parametros">Retorna uma estrutura que contém as informações do DDS.</param>
			CarenResult GetParameters([Out] CA_WICDdsParameters^% Param_Out_Parametros);

			/// <summary>
			/// Define dados específicos do DDS. Você não pode chamar esse método depois de começar a gravar dados de frame, por exemplo, chamando ICarenWICDdsEncoder::CreateNewFrame.
			/// A definição de parâmetros DDS usando este método fornece ao codificador DDS informações sobre o número esperado de frames e as dimensões e outros parâmetros de cada frame.
			/// </summary>
			/// <param name="Param_Parametros">Uma estrutura onde as informações a serem definidas estão contidas.</param>
			CarenResult SetParameters(CA_WICDdsParameters^ Param_Parametros);
		};

		/// <summary>
		/// (IWICDevelopRawNotificationCallback) - Interface responsável por expor um evento para notificações de alteração de imagem bruta.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("69E79AA6-0306-4AC4-AC45-4E0709B9A016")]
		public interface class ICarenWICDevelopRawNotificationCallback : ICaren
		{

			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//
			//Delegates
			//

			/// <summary>
			/// Delegate para o método nativo (IWICDevelopRawNotificaçãoCallback::Notify) da interface de rotorno de chamdas.
			/// </summary>
			delegate CarenResult Delegate_Notify(CA_WIC_IWICDevelopRawNotificationCallback Param_NotificationMask);


			//
			//Eventos
			//

			/// <summary>
			/// Evento chamado para notificações de alteração de parâmetros de imagem brutas.
			/// </summary>
			event Delegate_Notify^ OnNotify;



			//Métodos

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
		/// (IWICDevelopRaw) - Interface responsável por expor métodos que fornecem acesso aos recursos de um formato de codec bruto.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("010064F2-7710-41C6-890A-6EDA3BB84C79")]
		public interface class ICarenWICDevelopRaw : ICarenWICBitmapFrameDecode
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
			/// Obtém o valor de contraste da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Contraste">Retorna o valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. 
			/// O limite inferior de 0,0 não representa nenhum contraste aplicado à imagem, 
			/// enquanto o limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
			CarenResult GetContrast([Out] double% Param_Out_Contraste);

			/// <summary>
			/// Obtém o conjunto atual de parâmetros.
			/// </summary>
			/// <param name="Param_Out_ParametrosAtuais">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a bag que contém o conjunto atual de parametros.</param>
			CarenResult GetCurrentParameterSet([Out] ICarenPropertyBag2^% Param_Out_ParametrosAtuais);

			/// <summary>
			/// Obtém a compensação de exposição parar o valor da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_EV">Retorna o valor de parada de compensação de exposição. O padrão é a configuração "as-shot".</param>
			CarenResult GetExposureCompensation([Out] double% Param_Out_EV);

			/// <summary>
			/// Obtém a configuração gama atual da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Gamma">Retorna o valor da configuração gama atual.</param>
			CarenResult GetGamma([Out] double% Param_Out_Gamma);

			/// <summary>
			/// Obtém a informação sobre a atual gama Kelvin da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_MinKelvinTemp">Retorna a temperatura mínima de Kelvin.</param>
			/// <param name="Param_Out_MaxKelvinTemp">Retorna a temperatura máxima de Kelvin.</param>
			/// <param name="Param_Out_KelvinTempStepValue">Retorna a temperatura do Kelvin Step.</param>
			CarenResult GetKelvinRangeInfo(
				[Out] UInt32% Param_Out_MinKelvinTemp,
				[Out] UInt32% Param_Out_MaxKelvinTemp,
				[Out] UInt32% Param_Out_KelvinTempStepValue);

			/// <summary>
			/// Obtém o ponto branco da imagem bruta. Se os pontos brancos nomeados não forem suportados pela imagem bruta ou o arquivo bruto contiver pontos brancos nomeados que não 
			/// são suportados por esta API, o implementador codec ainda deve marcar essa capacidade como suportada. Se os pontos brancos nomeados não forem suportados pela imagem bruta, 
			/// um esforço melhor deve ser feito para ajustar a imagem ao ponto branco nomeado, mesmo quando não é um ponto branco pré-definido do arquivo bruto.
			/// Se o arquivo bruto contiver pontos brancos nomeados não suportados por esta API, o implementador codec deverá suportar os pontos brancos nomeados no CA_WICNamedWhitePoint.
			/// </summary>
			/// <param name="Param_Out_WhitePoint">Retorna a combinação bitwise dos valores de enumeração.</param>
			CarenResult GetNamedWhitePoint([Out] CA_WICNamedWhitePoint% Param_Out_WhitePoint);

			/// <summary>
			/// Obtém o valor de redução de ruído da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Noise">Retorna o valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para 
			/// redução de ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa 
			/// redução de ruído aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
			CarenResult GetNoiseReduction([Out] double% Param_Out_Noise);

			/// <summary>
			/// Obtém o CA_WICRawRenderMode atual. 
			/// </summary>
			/// <param name="Param_Out_ModoRender">Recebe uma enumeração que define o modo de renderização atual.</param>
			CarenResult GetRenderMode([Out] CA_WICRawRenderMode% Param_Out_ModoRender);

			/// <summary>
			/// Obtém o ângulo de rotação atual. 
			/// </summary>
			/// <param name="Param_Out_Rotacao">Retorna o ângulo de rotação atual.</param>
			CarenResult GetRotation([Out] double% Param_Out_Rotacao);

			/// <summary>
			/// Obtém o valor de saturação da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Saturacao">Retorna o valor de saturação da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para saturação é de 0,0 a 1,0. 
			/// Um valor de 0.0 representa uma imagem com uma imagem totalmente desaturada, 
			/// enquanto um valor de 1.0 representa a maior quantidade de saturação que pode ser aplicada.</param>
			CarenResult GetSaturation([Out] double% Param_Out_Saturacao);

			/// <summary>
			/// Obtém o valor de nitidez da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Shapness">Retorna o valor de nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0.
			///  O limite inferior de 0,0 não representa nenhum nitidez aplicado à imagem, enquanto 
			/// o limite superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
			CarenResult GetSharpness([Out] double% Param_Out_Shapness);

			/// <summary>
			/// Obtém o valor da tonalidade da imagem bruta. 
			/// </summary>
			/// <param name="Param_Out_Tint">Retorna o valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez 
			/// é de -1,0 a +1,0. O limite inferior de -1,0 representa um viés verde completo 
			/// para a imagem, enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
			CarenResult GetTint([Out] double% Param_Out_Tint);

			/// <summary>
			/// Obtém a curva de tom da imagem bruta. 
			/// </summary>
			/// <param name="Param_ToneCurveBufferSize">O tamanho da estrutura (Param_Ref_ToneCurve).</param>
			/// <param name="Param_Ref_ToneCurve">Retorna uma estrutura (CA_WICRawToneCurve) da imagem bruta. Define esse valor para NULO para obter o tamanho necessário para (Param_ToneCurveBufferSize).</param>
			/// <param name="Param_Out_ToneCurveBufferSizeAtual">Retorna o tamanho necessário para retornar a estrutura (Param_Ref_ToneCurve).</param>
			CarenResult GetToneCurve(
				UInt32 Param_ToneCurveBufferSize,
				CA_WICRawToneCurve^% Param_Ref_ToneCurve,
				[Out] UInt32% Param_Out_ToneCurveBufferSizeAtual);

			/// <summary>
			/// Obtém a temperatura Kelvin do ponto branco da imagem bruta.
			/// </summary>
			/// <param name="Param_Out_WhitePointKelvin">Retorna o valor da temperatura Kelvin do ponto branco da imagem bruta. O padrão é o valor de configuração "as-shot".</param>
			CarenResult GetWhitePointKelvin([Out] UInt32% Param_Out_WhitePointKelvin);

			/// <summary>
			/// Obtém os valores RGB do ponto branco. 
			/// </summary>
			/// <param name="Param_Out_Red">Retorna o valor do ponto branco vermelho.</param>
			/// <param name="Param_Out_Green">Retorna o valor do ponto branco verde.</param>
			/// <param name="Param_Out_Blue">Retorna o valor do ponto branco azul.</param>
			CarenResult GetWhitePointRGB(
				[Out] UInt32% Param_Out_Red,
				[Out] UInt32% Param_Out_Green,
				[Out] UInt32% Param_Out_Blue);

			/// <summary>
			/// Define a opção CA_WICRawParameterSet desejada. 
			/// </summary>
			/// <param name="Param_Parametros">Uma valor da opção(CA_WICRawParameterSet) a ser definido.</param>
			CarenResult LoadParameterSet(CA_WICRawParameterSet Param_Parametros);

			/// <summary>
			/// Recupera informações sobre quais recursos são suportados para uma imagem bruta. 
			/// Recomenda-se que um codec informe que uma capacidade é suportada mesmo que os resultados nos limites de alcance externo não sejam de perfeita qualidade.
			/// </summary>
			/// <param name="Param_Out_Info">Retorna uma estrutura (CA_WICRawCapabilitiesInfo) que fornece os recursos suportados pela imagem bruta.</param>
			CarenResult QueryRawCapabilitiesInfo([Out] CA_WICRawCapabilitiesInfo^% Param_Out_Info);

			/// <summary>
			/// Define o valor de contraste da imagem bruta. O implementador codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
			/// rotinas de processamento de imagem.
			/// </summary>
			/// <param name="Param_Contraste">O valor de contraste da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para contraste é de 0,0 a 1,0. O limite 
			/// inferior de 0,0 não representa nenhum contraste aplicado à imagem, enquanto o 
			/// limite superior de 1,0 representa a maior quantidade de contraste que pode ser aplicada.</param>
			CarenResult SetContrast(double Param_Contraste);

			/// <summary>
			/// Define o contexto de cores do destino. 
			/// </summary>
			/// <param name="Param_ColorContext">O contexto de cores do destino.</param>
			CarenResult SetDestinationColorContext(ICarenWICColorContext^ Param_ColorContext);

			/// <summary>
			/// Define o valor de parada da compensação de exposição. Recomenda - se que um codec informe que esse método é compatível, mesmo se os resultados nos limites da faixa externa 
			/// não forem de qualidade perfeita.
			/// </summary>
			/// <param name="Param_EV">O valor de compensação da exposição.O intervalo de valores para compensação de exposição é de - 5, 0 a + 5, 0, o que equivale a 10 pontos finais.</param>
			CarenResult SetExposureCompensation(double Param_EV);

			/// <summary>
			/// Define o valor gama desejado. 
			/// </summary>
			/// <param name="Param_Gamma">O valor gama desejado.</param>
			CarenResult SetGamma(double Param_Gamma);

			/// <summary>
			/// Define o ponto branco nomeado do arquivo bruto. 
			/// </summary>
			/// <param name="Param_WhitePoint">Uma combinação bitwise dos valores de enumeração.</param>
			CarenResult SetNamedWhitePoint(CA_WICNamedWhitePoint Param_WhitePoint);

			/// <summary>
			/// Define o valor de redução de ruído da imagem bruta. O implementador do codec deve determinar o que o valor do intervalo superior representa e deve determinar como mapear o 
			/// valor para suas rotinas de processamento de imagem.
			/// </summary>
			/// <param name="Param_Noise">O valor de redução de ruído da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para redução de
			///  ruído é de 0,0 a 1,0. O limite inferior de 0,0 não representa redução de ruído 
			/// aplicada à imagem, enquanto o limite superior de 1,0 representa a maior quantidade de redução de ruído que pode ser aplicada.</param>
			CarenResult SetNoiseReduction(double Param_Noise);

			/// <summary>
			/// Define o método de retorno de chamada de notificação. 
			/// </summary>
			/// <param name="Param_NotificationCallback">Uma interface de callback que vai receber as notificações.</param>
			CarenResult SetNotificationCallback(ICarenWICDevelopRawNotificationCallback^ Param_NotificationCallback);

			/// <summary>
			/// Define o WICRawRenderMode atual. 
			/// </summary>
			/// <param name="Param_ModoRender">O modo renderização a ser usado.</param>
			CarenResult SetRenderMode(CA_WICRawRenderMode Param_ModoRender);

			/// <summary>
			/// Define o ângulo de rotação desejado. 
			/// </summary>
			/// <param name="Param_Rotacao">O ângulo de rotação desejado.</param>
			CarenResult SetRotation(double Param_Rotacao);

			/// <summary>
			/// Define o valor de saturação da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor 
			/// para suas rotinas de processamento de imagem.
			/// </summary>
			/// <param name="Param_Saturacao">O valor de saturação da imagem bruta. A faixa de valor para saturação é de 0,0 a 1,0. Um valor de 0.0 representa uma imagem com uma imagem 
			/// totalmente desaturada, enquanto um valor de 1.0 representa a maior quantidade 
			/// de saturação que pode ser aplicada.</param>
			CarenResult SetSaturation(double Param_Saturacao);

			/// <summary>
			/// Define o valor de nitidez da imagem bruta. O implementador do codec deve determinar o que o valor da faixa superior representa e deve determinar como mapear o valor para suas 
			/// rotinas de processamento de imagem.
			/// </summary>
			/// <param name="Param_Sharpness">O valor da nitidez da imagem bruta. O valor padrão é a configuração "as-shot". A faixa de valor para nitidez é de 0,0 a 1,0. O limite inferior de 
			/// 0,0 não representa nenhum nitidez aplicado à imagem, enquanto o limite 
			/// superior de 1,0 representa a maior quantidade de nitidez que pode ser aplicada.</param>
			CarenResult SetSharpness(double Param_Sharpness);

			/// <summary>
			/// Define o valor da tonalidade da imagem bruta. O implementador do codec deve determinar quais são os valores de alcance externo e deve determinar como mapear os valores para suas 
			/// rotinas de processamento de imagem.
			/// </summary>
			/// <param name="Param_Tint">O valor da tonalidade da imagem bruta. O valor padrão é a configuração "as-shot" se ele existir ou 0.0. A faixa de valor para nitidez é de -1,0 a +1,0. 
			/// O limite inferior de -1,0 representa um viés verde completo para a imagem, 
			/// enquanto o limite superior de 1,0 representa um viés magenta completo.</param>
			CarenResult SetTint(double Param_Tint);

			/// <summary>
			/// Define a curva de tom para a imagem bruta. 
			/// </summary>
			/// <param name="Param_ToneCurveSizeStruct">O tamanho da estrutura (Param_ToneCurve).</param>
			/// <param name="Param_ToneCurve">A curva de tom desejada.</param>
			CarenResult SetToneCurve(
				UInt32 Param_ToneCurveSizeStruct,
				CA_WICRawToneCurve^ Param_ToneCurve);

			/// <summary>
			/// Define o valor do ponto branco kelvin. Os implementadores de codec devem ajustar fielmente a temperatura de cor dentro da faixa suportada nativamente pela imagem bruta. Para valores 
			/// fora da faixa de suporte nativa, o implementador codec deve fornecer uma representação de melhor esforço da imagem a essa temperatura de cor.
			/// Os implementadores de codec devem retornar WINCODEC_ERR_VALUEOUTOFRANGE se o valor estiver fora do intervalo aceitável definido.
			/// </summary>
			/// <param name="Param_WhitePointKelvin">O valor do ponto branco kelvin. Os valores aceitáveis de Kelvin são de 1.500 a 30.000.</param>
			CarenResult SetWhitePointKelvin(UInt32 Param_WhitePointKelvin);

			/// <summary>
			/// Define os valores RGB de ponto branco. Devido a outros métodos de configuração de ponto branco(por exemplo, SetWhitePointKelvin), deve - se tomar cuidado pelos implementadores 
			/// de codec para garantir a interoperabilidade adequada.Por exemplo, se o chamador define por meio de um ponto branco nomeado, o implementador do codec pode desabilitar a leitura 
			/// da temperatura Kelvin correspondente.Em casos específicos em que o implementador do codec deseja negar uma determinada ação por causa de chamadas anteriores, 
			/// WINCODEC_ERR_WRONGSTATE deve ser retornado.
			/// </summary>
			/// <param name="Param_Red">O valor do ponto branco vermelho.</param>
			/// <param name="Param_Green">O valor verde do ponto branco.</param>
			/// <param name="Param_Blue">O valor do ponto branco azul.</param>
			CarenResult SetWhitePointRGB(
				UInt32 Param_Red,
				UInt32 Param_Green,
				UInt32 Param_Blue);
		};

		/// <summary>
		/// (IWICDdsFrameDecode) - Interface responsável por fornecer acesso a um único quadro de dados de imagem DDS no formato DXGI_FORMAT nativo , além de informações sobre os dados da imagem.
		/// Esta interface é implementada pelo codec WIC DDS. Para obter esta interface, crie um ICarenWICBitmapFrameDecode usando o codec DDS e o (ICaren::ConsultarInterface) para IID_IWICDdsFrameDecode.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("923B94F7-E9ED-48AD-AA6B-227AB202AD8F")]
		public interface class ICarenWICDdsFrameDecode : ICaren
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
			/// Solicita dados de pixel, pois são armazenados nativamente no arquivo DDS. Se a textura não usar um DXGI_FORMAT compactado por bloco, este método se comporta de forma semelhante 
			/// ao IWICBitmapFonte::CopyPixels. No entanto, ele não executa qualquer conversão de formato de pixel e, em vez disso, produz os dados brutos do arquivo DDS.
			/// </summary>
			/// <param name="Param_RetanguloCopy">O retângulo para copiar da fonte. Um valor NULO especifica toda a textura. Se a textura usar um DXGI_FORMAT comprimido de bloco, todos os valores 
			/// do retângulo são expressos em número de blocos, não pixels.</param>
			/// <param name="Param_Stride">O Stride, em bytes, do Buffer de destino. Isso representa o número de bytes do Buffer para a próxima linha de dados. Se a textura usar uma DXGI_FORMAT
			///  compactada por bloco, uma "linha de dados" será definida como uma linha de blocos que contém várias linhas de varredura de pixels.</param>
			/// <param name="Param_BufferSize">O tamanho, em bytes, do buffer de destino.</param>
			/// <param name="Param_BufferDestino">Uma interface (ICarenBuffer) para o buffer de destino.</param>
			CarenResult CopyBlocks(
				CA_WICRect^ Param_RetanguloCopy,
				UInt32 Param_Stride,
				UInt32 Param_BufferSize,
				ICarenBuffer^ Param_BufferDestino);

			/// <summary>
			/// Obtém informações sobre o formato em que a imagem DDS é armazenada.
			/// Essas informações podem ser usadas para alocar memória ou construir recursos Direct3D ou Direct2D, por exemplo, usando ICarenD3D11Device::CreateTexture2D ou ICarenD2D1DeviceContext::CreateBitmap.
			/// </summary>
			/// <param name="Param_Out_FormatInfo">Retorna uma estrutura que contém as informações sobre o formato DDS.</param>
			CarenResult GetFormatInfo([Out] CA_WICDdsFormatInfo^% Param_Out_FormatInfo);

			/// <summary>
			/// Obtém a largura e a altura, em blocos, da imagem DDS.
			/// Para texturas compactadas de bloco, os valores de largura e altura retornados não definem completamente o tamanho da textura porque a imagem é acolchoada para se adequar 
			/// ao tamanho de bloco inteiro mais próximo.
			/// Se a textura não usar um DXGI_FORMAT comprimido de bloco, este método retorna o tamanho da textura em pixels; para esses formatos o tamanho do bloco devolvido pelo 
			/// ICarenWICDdsFrameDecoder::GetFormatInfo é 1x1.
			/// </summary>
			/// <param name="Param_Out_WidthInBlocks">Retorna a largura da imagem DDS em blocos.</param>
			/// <param name="Param_Out_HeightInBlocks">Retorna a altura da imagem DDS em blocos.</param>
			CarenResult GetSizeInBlocks(
				[Out] UInt32% Param_Out_WidthInBlocks,
				[Out] UInt32% Param_Out_HeightInBlocks);
		};

		/// <summary>
		/// (IWICFormatConverterInfo) - Interface responsável por expor métodos que fornecem informações sobre um conversor de formato de pixel. 
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("5714B116-38B9-424E-9F51-81D43687C6C8")]
		public interface class ICarenWICFormatConverterInfo : ICarenWICComponentInfo
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
			/// Cria uma nova instância IWICFormatConverter. 
			/// </summary>
			/// <param name="Param_Out_Converter">Retorna uma interface() que contém um ponteiro para a nova instância do conversor de formatos de pixels.</param>
			CarenResult CreateInstance([Out] ICarenWICFormatConverter^% Param_Out_Converter);

			/// <summary>
			/// Recupera uma lista de GUIDs que significam quais formatos de pixel o conversor suporta.
			/// O conversor de formato não garante necessariamente a simetria em relação à conversão; ou seja, um conversor pode ser capaz de converter DE um determinado formato sem realmente ser 
			/// capaz de converter para um determinado formato. Para testar a simetria, use o CanConvert.
			/// </summary>
			/// <param name="Param_Quantidade">O tamanho da matriz (Param_Ref_PixelFormatGuids).</param>
			/// <param name="Param_Ref_PixelFormatGuids">Retorna ma matriz GUID que recebe os formatos de pixel que o conversor suporta. Define esse valor para NULO se quiser obter o valor do 
			/// (Param_Quantidade) que será retornado em (Param_Out_QuantidadeAtual).</param>
			/// <param name="Param_Out_QuantidadeAtual">Retorna o tamanho real do array necessário para recuperar todos os formatos de pixel suportados pelo conversor.</param>
			CarenResult GetPixelFormats(
				UInt32 Param_Quantidade,
				cli::array<String^>^% Param_Ref_PixelFormatGuids,
				[Out] UInt32% Param_Out_QuantidadeAtual);
		};

		/// <summary>
		/// (IWICJpegFrameDecode) - Interface responsável por expor métodos para decodificar imagens JPEG. Fornece acesso ao cabeçalho Start Of Frame (SOF), cabeçalho Start of Scan (SOS), 
		/// tabelas Huffman e Quantization e dados JPEG JPEG compactados. Também permite a indexação para acesso aleatório eficiente.
		/// Obtenha esta interface chamando ICaren::ConsultarInterface na interface ICarenWICBitmapFrameDecoder fornecida pelo Windows para o decodificador JPEG.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("0228DE3C-B4BA-4D59-9A94-6A26756BA57C")]
		public interface class ICarenWICJpegFrameDecode : ICaren
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
			/// Remove a indexação de um JPEG que foi indexado usando ICarenWICJpegFrameDecode::SetIndexing. 
			/// </summary>
			CarenResult ClearIndexing();

			/// <summary>
			/// Recupera uma cópia do scan JPEG compactada diretamente do fluxo de saída do frame de decodificador WIC. 
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_ScanOffset">A posição byte nos dados de varredura para começar a copiar. Use 0 na primeira chamada. Se o tamanho do buffer de saída for insuficiente para 
			/// armazenar toda a varredura, este deslocamento permite que você retome a cópia do final da operação anterior da cópia.</param>
			/// <param name="Param_ScanDataSize">O tamanho, em bytes, da matriz (Param_Out_ScanDataBuffer).</param>
			/// <param name="Param_ScanDataBufferDestino">Uma interface (ICarenBuffer) que contém o buffer que vai receber os dados da tabela.. Esse parametro não pode ser nulo.</param>
			/// <param name="Param_Out_BufferSizeAtual">Retorna o tamanho dos dados de varredura realmente copiados em (Param_Out_ScanDataBuffer). O tamanho devolvido pode ser menor que o tamanho do (Param_ScanDataSize).</param>
			CarenResult CopyScan(
				UInt32 Param_ScanIndex,
				UInt32 Param_ScanOffset,
				UInt32 Param_ScanDataSize,
				ICarenBuffer^ Param_ScanDataBufferDestino,
				[Out] UInt32% Param_Out_BufferSizeAtual);

			/// <summary>
			/// Recupera um valor indicando se esse decodificador suporta indexação para acesso aleatório eficiente. A indexação só é suportada para alguns tipos de JPEG.
			/// </summary>
			/// <param name="Param_Out_Suporte">Retorna TRUE se a indexação for suportada; caso contrário, FALSE.</param>
			CarenResult DoesSupportIndexing([Out] Boolean% Param_Out_Suporte);

			/// <summary>
			/// Recupera uma cópia da tabela AC Huffman para a digitalização e a tabela especificadas. 
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
			/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
			/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetAcHuffmanTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_AC_HUFFMAN_TABLE^% Param_Out_ACHuffmanTable);

			/// <summary>
			/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas. 
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho de 
			/// varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
			/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetDcHuffmanTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_DC_HUFFMAN_TABLE^% Param_Out_DCHuffmanTable);

			/// <summary>
			/// Recupera dados de cabeçalho de todo o frame. O resultado inclui parâmetros do marcador Start Of Frame (SOF) para a varredura, bem como parâmetros derivados de outros metadados, 
			/// como o modelo de cor dos dados comprimidos.
			/// </summary>
			/// <param name="Param_Out_FrameHeader">Retrona uma estrutura que contém os dados do cabeçalho do frame.</param>
			CarenResult GetFrameHeader([Out] CA_WICJpegFrameHeader^% Param_Out_FrameHeader);

			/// <summary>
			/// Recupera uma cópia da tabela de quantização. 
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
			/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
			/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetQuantizationTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_QUANTIZATION_TABLE^% Param_Out_QuantizationTable);

			/// <summary>
			/// Recupera parâmetros do marcador START Of Scan (SOS) para o scan com o índice especificado. 
			/// </summary>
			/// <param name="Param_ScanIndex">O índice da varredura para a qual os dados do cabeçalho são recuperados.</param>
			/// <param name="Param_Out_ScanHeader">Retorna uma estrutura que contém os dados de cabeçalho do frame.</param>
			CarenResult GetScanHeader(
				UInt32 Param_ScanIndex,
				[Out] CA_WICJpegScanHeader^% Param_Out_ScanHeader);

			/// <summary>
			/// Permite a indexação do JPEG para acesso aleatório eficiente.
			/// Este método permite um acesso aleatório eficiente aos pixels de imagem em detrimento do uso da memória. A quantidade de memória necessária para a indexação depende da 
			/// granularidade do índice solicitado. A menos que o SetIndexing seja chamado, é muito mais eficiente acessar um JPEG progredindo através de seus pixels de cima para baixo 
			/// durante as chamadas para ICarenWICBitmapFonte::CopyPixels.
			/// Este método falhará se a indexação não for suportada no arquivo. IWICJpegFrameDecode::DoesSupportIndexing deve ser chamado primeiro para determinar se a indexação é suportada. 
			/// Se esse método for chamado várias vezes, a chamada final altera a granularidade do índice para o tamanho solicitado.
			/// </summary>
			/// <param name="Param_Opcoes">Um valor especificando se os índices devem ser gerados imediatamente ou diferidos até uma chamada futura para ICarenWICBitmapFonte::CopyPixels.</param>
			/// <param name="Param_HorizontalIntervalSize">A granularidade da indexação, em pixels.</param>
			CarenResult SetIndexing(
				CA_WICJpegIndexingOptions Param_Opcoes,
				UInt32 Param_HorizontalIntervalSize);
		};

		/// <summary>
		/// (IWICJpegFrameEncode) - Interface responsável por expor métodos para gravar dados de digitalização JPEG compactados diretamente no fluxo de saída do codificador WIC. Também fornece acesso 
		/// as tabelas de Huffman e quantização. Obtenha esta interface chamando ICaren::ConsultarInterface na interface ICarenWICBitmapFrameEncoder fornecida pelo Windows para o codificador JPEG.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("987CD1BB-532D-496C-91E3-C1BE79EC2CA5")]
		public interface class ICarenWICJpegFrameEncode : ICaren
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
			/// Recupera uma cópia da tabela AC Huffman para o scan e a tabela especificadas.
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar.</param>
			/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetAcHuffmanTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_AC_HUFFMAN_TABLE^% Param_Out_ACHuffmanTable);

			/// <summary>
			/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas.
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar.</param>
			/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetDcHuffmanTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_DC_HUFFMAN_TABLE^% Param_Out_DCHuffmanTable);

			/// <summary>
			/// Recupera uma cópia da tabela de quantização.
			/// </summary>
			/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
			/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar.</param>
			/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
			CarenResult GetQuantizationTable(
				UInt32 Param_ScanIndex,
				UInt32 Param_TableIndex,
				[Out] CA_DXGI_JPEG_QUANTIZATION_TABLE^% Param_Out_QuantizationTable);

			/// <summary>
			/// Grava dados de varredura em um frame JPEG. 
			/// WriteScan pode ser chamado várias vezes. Cada chamada anexa os dados de varredura especificados a quaisquer dados de varredura anteriores. Complete a varredura chamando 
			/// ICarenWICBitmapFrameEncode::Commit.
			/// </summary>
			/// <param name="Param_SizeBuffer">O tamanho do Buffer no parâmetro (Param_BufferScanData).</param>
			/// <param name="Param_BufferScanData">Os dados do scan para escrever.</param>
			CarenResult WriteScan(
				UInt32 Param_SizeBuffer,
				ICarenBuffer^ Param_BufferScanData);
		};
		
		/// <summary>
		/// (IWICMetadataReaderInfo) - Interface responsável por expor métodos que fornecem informações básicas sobre o leitor de metadados registrado.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("C6B06A90-38E4-417E-9C0C-71F7683D3DC5")]
		public interface class ICarenWICMetadataReaderInfo : ICarenWICMetadataHandlerInfo
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
			/// Cria uma instância de um ICarenWICMetadataReader. 
			/// </summary>
			/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o leitor de metadados.</param>
			CarenResult CreateInstance([Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);

			/// <summary>
			/// [MÉTODO COM PROBLEMA]Obtém os padrões de metadados associados ao leitor de metadados. 
			/// </summary>
			/// <param name="Param_GuidContainerFormat">O GUID para o formato do cointainer.</param>
			/// <param name="Param_SizeBytesPattern">O tamanho, em bytes, do buffer (Param_Out_Patterns).</param>
			/// <param name="Param_Out_Patterns">Retorna uma matriz de estrutura que recebem os padrões de metadados.</param>
			/// <param name="Param_Out_QuantidadePatterns">Retorna o número de padrões de metadados.</param>
			/// <param name="Param_Out_SizeBytesAtual">Retorna o tamanho, em bytes, necessário para obter os padrões de metadados.</param>
			CarenResult GetPatterns(
				String^ Param_GuidContainerFormat,
				UInt32 Param_SizeBytesPattern,
				[Out] cli::array<CA_WICMetadataPattern^>^% Param_Out_Patterns,
				[Out] UInt32% Param_Out_QuantidadePatterns,
				[Out] UInt32% Param_Out_SizeBytesAtual);

			/// <summary>
			/// Determina se um fluxo contém um padrão de itens de metadados. 
			/// </summary>
			/// <param name="Param_GuidContainerFormat">O formato do recipiente do item metadados.</param>
			/// <param name="Param_Stream">O fluxo para procurar o padrão de metadados.</param>
			/// <param name="Param_Out_Contem">Retorna TRUE se o fluxo contiver o padrão; Caso contrário FALSE.</param>
			CarenResult MatchesPattern(
				String^ Param_GuidContainerFormat,
				ICarenStream^ Param_Stream,
				[Out] Boolean% Param_Out_Contem);
		};

		/// <summary>
		/// (IWICMetadataWriterInfo) - Interface responsável por expor métodos que fornecem informações básicas sobre o gravador de metadados registrado.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("7BE64917-B3C4-47E6-9B03-998D83AEA345")]
		public interface class ICarenWICMetadataWriterInfo : ICarenWICMetadataHandlerInfo
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
			/// Cria uma instância de um ICarenWICMetadataWriter. 
			/// </summary>
			/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados.</param>
			CarenResult CreateInstance([Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

			/// <summary>
			/// Recebe o cabeçalho de metadados para o escritor de metadados. 
			/// </summary>
			/// <param name="Param_GuidContainerFormat">O GUID do contêiner de formato para o qual obter o cabeçalho.</param>
			/// <param name="Param_SizeHeader">O tamanho do buffer em (Param_Ref_Header).</param>
			/// <param name="Param_Ref_Header">Retorna uma estrutura com o header dos metadados. Defina como NULO para retornar o (SizeHeader) em (Param_Out_SizeAtual) necessário para o 
			/// parametro (Param_SizeHeader).</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do cabeçalho.</param>
			CarenResult GetHeader(
				String^ Param_GuidContainerFormat,
				UInt32 Param_SizeHeader,
				CA_WICMetadataHeader^% Param_Ref_Header,
				[Out] UInt32% Param_Out_SizeAtual);
		};
		
		/// <summary>
		/// (IWICPersistStream) - Interface responsável por expor métodos que fornecem carga adicional e salvam métodos que usam CA_WICPersistOptions.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("69084153-701C-48FD-8FDD-BEA1ADF4BBEA")]
		public interface class ICarenWICPersistStream : ICarenPersistStream
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
			/// Carrega dados de um fluxo de entrada usando os parâmetros determinados. 
			/// NULO pode ser passado para (Param_GuidPreferredVendor) para indicar nenhuma preferência.
			/// </summary>
			/// <param name="Param_Stream">O fluxo de entrada.</param>
			/// <param name="Param_GuidPreferredVendor">O GUID do fornecedor preferido.</param>
			/// <param name="Param_PersistOptions">O WICPersistOptions usado para carregar o fluxo.</param>
			CarenResult LoadEx(
				ICarenStream^ Param_Stream,
				String^ Param_GuidPreferredVendor,
				CA_WICPersistOptions Param_PersistOptions);

			/// <summary>
			/// Salva o ICaremWICPersistStream para o ICarenStream de entrada dado usando os parâmetros determinados.
			/// </summary>
			/// <param name="Param_Stream">O fluxo para salvar.</param>
			/// <param name="Param_PersistOptions">As WICPersistOptions a serem usadas ao salvar.</param>
			/// <param name="Param_ClearDirty">Indica se o valor "dirty" será limpo de todos os metadados após a salvação.</param>
			CarenResult SaveEx(
				ICarenStream^ Param_Stream,
				CA_WICPersistOptions Param_PersistOptions,
				Boolean Param_ClearDirty);
		};

		/// <summary>
		/// (IWICPixelFormatInfo) - Interface responsável por expor métodos que fornecem informações sobre um formato de pixel.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("006B5645-366B-437B-BD62-24D9BFE09303")]
		public interface class ICarenWICPixelFormatInfo : ICarenWICComponentInfo
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
			/// Obtém os bits por pixel (BPP) do formato pixel. 
			/// </summary>
			/// <param name="Param_Out_BitsPerPixel">Retorna o o BPP do formato pixel.</param>
			CarenResult GetBitsPerPixel([Out] UInt32% Param_Out_BitsPerPixel);

			/// <summary>
			/// Obtém o número de canais que o formato pixel contém. 
			/// </summary>
			/// <param name="Param_Out_ChannelCount">Retorna o número de canais.</param>
			CarenResult GetChannelCount([Out] UInt32% Param_Out_ChannelCount);

			/// <summary>
			/// Recebe a máscara de canal do formato pixel. 
			/// Se 0 e NULO forem passados ​​para Param_SizeMaskBuffer e Param_Ref_MaskBuffer, respectivamente, o tamanho do buffer necessário será retornado por meio de (Param_Out_SizeAtual).
			/// </summary>
			/// <param name="Param_ChannelIndex">O índice da máscara do canal para recuperar.</param>
			/// <param name="Param_SizeMaskBuffer">O tamanho do buffer (Param_Ref_MaskBuffer).</param>
			/// <param name="Param_Ref_MaskBuffer">Uma interface(ICarenBuffer) que vai receber o Buffer da máscara do canal.</param>
			/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para obter a máscara de canal.</param>
			CarenResult GetChannelMask(
				UInt32 Param_ChannelIndex,
				UInt32 Param_SizeMaskBuffer,
				ICarenBuffer^% Param_Ref_MaskBuffer,
				[Out] UInt32% Param_Out_SizeAtual);

			/// <summary>
			/// Obtém o ICarenWICColorContext do formato pixel. 
			/// O contexto de cores retornado é o espaço de cor padrão para o formato pixel. No entanto, se um ICarenWICBitmapSource especificar seu próprio contexto de cores, o contexto da fonte 
			/// deve ser preferido em relação ao padrão do formato pixel.
			/// </summary>
			/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenWICColorContext) que contém um ponteiro para o contexto de cores do formato do pixel.</param>
			CarenResult GetColorContext([Out] ICarenWICColorContext^% Param_Out_ColorContext);

			/// <summary>
			/// Obtém o GUID do formato de pixel. 
			/// </summary>
			/// <param name="Param_Out_Formato">Retorna o GUID para o formato do pixel.</param>
			CarenResult GetFormatGUID([Out] String^% Param_Out_Formato);
		};

		/// <summary>
		/// (IWICPixelFormatInfo2) - Interface responsável por estender ICarenWICPixelFormatInfo, fornecendo informações adicionais sobre um formato de pixel.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("B441879C-2FEF-4D09-9582-9CE5961246A4")]
		public interface class ICarenWICPixelFormatInfo2 : ICarenWICPixelFormatInfo
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
			/// Recupera o WICPixelFormatNumericRepresentation do formato de pixel.
			/// </summary>
			/// <param name="Param_Out_RepresentacaoNumerica">Retorna um valor da enumeração(CA_WICPixelFormatNumericRepresentation) que define a representação númerica do formato de pixel.</param>
			CarenResult GetNumericRepresentation([Out] CA_WICPixelFormatNumericRepresentation% Param_Out_RepresentacaoNumerica);

			/// <summary>
			/// Retorna se o formato suporta pixels transparentes. 
			/// </summary>
			/// <param name="Param_Out_SuporteTransparencia">Retornos TRUE se o formato pixel suportar transparência; caso contrário, FALSE.</param>
			CarenResult SupportsTransparency([Out] Boolean% Param_Out_SuporteTransparencia);
		};
		
		/// <summary>
		/// (IWICPlanarBitmapFrameEncode) - Interface responsável por permitir que pixels de imagem de componente planar sejam gravados em um codificador. Quando suportado pelo codificador, isso permite 
		/// que um aplicativo codifique dados de imagem de componente planar sem primeiro converter para um formato de pixel intercalado.
		/// Você pode usar (ICaren::ConsultarInterface) para obter essa interface da implementação fornecida pelo Windows de ICarenWICBitmapFrameEncode para o codificador JPEG.
		/// Codificar dados YCbCr usando ICarenWICPlanarBitmapFrameEncode é semelhante, mas não idêntico, à codificação de dados intercalados usando ICarenWICBitmapFrameEncode. A interface planar expõe 
		/// apenas a capacidade de gravar dados de imagem de frame planar, e você deve continuar a usar a interface de codificação de frame para definir metadados ou uma miniatura e fazer o commit 
		/// no final da operação.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("AF72C907-0B7E-414B-A74F-2E80AA7ABF52")]
		public interface class ICarenWICPlanarBitmapFrameEncode : ICaren
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
			/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
			/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
			/// As chamadas WritePixels sucessivas são assumidas adicionando linhas de varredura sequencialmente à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
			/// e ICarenWICBitmapFrameEncode::SetPixelFormat devem ser chamados antes deste método ou ele falhará.
			/// O formato de pixel intercalado definido via ICarenWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
			/// <param name="Param_LineCount">O número de linhas para codificar. Consulte a seção Observações para restrições específicas de contagem de linhas do WIC Jpeg.</param>
			/// <param name="Param_Planes">Especifica os buffers de origem para cada plano componente codificado.</param>
			/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_Planes).</param>
			CarenResult WritePixels(
				UInt32 Param_LineCount,
				cli::array<CA_WICBitmapPlane^>^ Param_Planes,
				UInt32 Param_QuantidadePlanes);

			/// <summary>
			/// Grava linhas dos planos de origem para o formato codificado. Se os planos e o retângulo de origem não atenderem aos requisitos, este método falha com WINCODEC_ERR_IMAGESIZEOUTOFRANGE. 
			/// Se o formato ICarenWICBitmapSource não atender aos requisitos do codificador, este método falhará com WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT.
			/// Sucessivas chamadas WriteSource são assumidas sequencialmente adicionando linhas de varredura à imagem de saída. ICarenWICBitmapFrameEncode::Initialize, ICarenWICBitmapFrameEncode::SetSize 
			/// e ICarenWICBitmapFrameEncode::SetPixelFormat deve ser chamado antes deste método ou ele falhará.
			/// O formato de pixel intercalado definido via IWICBitmapFrameEncode::SetPixelFormat e os parâmetros de codificação específicos do codec determinam os formatos planar suportados.
			/// </summary>
			/// <param name="Param_ArrayPlanes">Especifica uma matriz de interface (ICarenWICBitmapSource) que representam planos de imagem.</param>
			/// <param name="Param_QuantidadePlanes">O número de planos componentes especificados pelo parâmetro (Param_ArrayPlanes).</param>
			/// <param name="Param_RetanguloOrigem">O retângulo de origem de pixels para codificar a partir dos planos ICarenWICBitmapSource. Nulo indica toda a fonte. A largura de retificada de origem 
			/// deve corresponder à largura definida através do SetSize. Chamadas repetidas do WriteSource podem ser feitas desde que a altura total acumulada do retifice seja a mesma definida através do SetSize.</param>
			CarenResult WriteSource(
				cli::array<ICarenWICBitmapSource^>^ Param_ArrayPlanes,
				UInt32 Param_QuantidadePlanes,
				CA_WICRect^ Param_RetanguloOrigem);
		};
		
		/// <summary>
		/// (IWICPlanarBitmapSourceTransform) - Interface responsável por fornecer acesso a formatos de pixels planar Y'CbCr onde os componentes pixel são armazenados em planos componentes separados. 
		/// Esta interface também permite o acesso a outras otimizações codec para conversão de flip/rotativo, escala e formato para outros formatos planar Y'CbCr; isso é semelhante à interface 
		/// ICarenWICBitmapSourceTransform pré-existente.
		/// (ICaren::ConsultarInterface) pode ser usado para obter essa interface das implementações fornecidas pelo Windows de ICarenWICBitmapFrameDecode para o decodificador JPEG, ICarenWICBitmapScaler, 
		/// ICarenWICBitmapFlipRotator e ICarenWICColorTransform.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("672B83DD-6277-4D19-BCD1-DC5B36CEE079")]
		public interface class ICarenWICPlanarBitmapSourceTransform : ICaren
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
			/// Copia pixels nos planos de destino. Configurado pelos parâmetros de entrada fornecidos.
			/// Se uma conversão (Param_DestinoTransformacao), escala ou formato for especificada, o (CA_WICBitmapPlane::cbStride) é o stride transformado e é baseado no formato de pixel de destino do 
			/// parâmetro (Param_PlanosDestino),  não no formato de pixel da fonte original.
			/// </summary>
			/// <param name="Param_RetanguloOrigem">O retângulo de origem de pixels para copiar.</param>
			/// <param name="Param_Width">A largura para dimensionar o bitmap de origem. Este parâmetro deve ser igual a um valor obtido através do ICarenWICPlanarBitmapSourceTransform:: DoesSupportTransform.</param>
			/// <param name="Param_Height">A altura para dimensionar o bitmap fonte. Este parâmetro deve ser igual a um valor obtido através do ICarenWICPlanarBitmapSourceTransform:: DoesSupportTransform.</param>
			/// <param name="Param_DestinoTransformacao">A rotação ou o flip desejado para executar antes da cópia do pixel. Uma rotação pode ser combinada com um flip horizontal ou um flip vertical.</param>
			/// <param name="Param_OpcoesPlanar">Usado para especificar opções adicionais de configuração para a transformação. Decodificador WIC JPEG: WICPlanarOptionsPreserveSubsampling pode ser 
			/// especificado para manter as relações de subsamplagem quando a redução. Por padrão, o decodificador JPEG tenta preservar a qualidade baixando apenas o plano Y em alguns casos, alterando a imagem 
			/// para 4:4:4 chroma subsampling.</param>
			/// <param name="Param_PlanosDestino">Especifica o formato de pixel e o buffer de saída para cada plano componente. O número de planos e o formato de pixel de cada plano devem corresponder aos 
			/// valores obtidos através do ICarenWICPlanarBitmapSourceTransform::DoesSupportTransform.</param>
			/// <param name="Param_QuantidadePlanos">O número de planos componentes especificados pelo parâmetro (Param_PlanosDestino).</param>
			CarenResult CopyPixels(
				CA_WICRect^ Param_RetanguloOrigem,
				UInt32 Param_Width,
				UInt32 Param_Height,
				CA_WICBitmapTransformOptions Param_DestinoTransformacao,
				CA_WICPlanarOptions Param_OpcoesPlanar,
				cli::array<CA_WICBitmapPlane^>^ Param_PlanosDestino,
				UInt32 Param_QuantidadePlanos);

			/// <summary>
			/// Use este método para determinar se uma saída planar desejada é suportada e permiti que o chamador escolha um caminho de código otimizado, se for. Caso contrário, os chamadores devem recuar 
			/// para ICarenWICBitmapSourceTransform ou ICarenWICBitmapSource e recuperar pixels intercalados.
			/// Quando uma transformação é suportada, este método retorna a descrição dos planos resultantes no parâmetro (Param_Out_DescricaoPlanos).
			/// </summary>
			/// <param name="Param_Ref_INOUT_Width">Na entrada, a largura desejada. Na saída, a largura suportada mais próxima da largura desejada; este é o mesmo tamanho ou maior do que a largura desejada.</param>
			/// <param name="Param_Ref_INOUT_Height">Na entrada, a altura desejada. Na saída, a altura suportada mais próxima da altura desejada; este é o mesmo tamanho ou maior do que a largura desejada.</param>
			/// <param name="Param_DestinoTransformacao">A operação de rotação ou flip desejada. Várias opções de (CA_WICBitmapTransformOptions) podem ser combinadas neste parâmetro de bandeira.</param>
			/// <param name="Param_OpcoesPlanar">Usado para especificar opções adicionais de configuração para a transformação.</param>
			/// <param name="Param_GuidDestinoFormatos">Os formatos pixel solicitados dos respectivos planos.</param>
			/// <param name="Param_Out_DescricaoPlanos">Quando Param_Out_Suporte == TRUE, o conjunto de descrições do plano contém o tamanho e o formato de cada um dos planos. Decodificador WIC JPEG: Os planos 
			/// Cb e Cr podem ser de tamanho diferente dos valores devolvidos por (Param_Ref_INOUT_Width) e (Param_Ref_INOUT_Height) devido à subsamplagem de chroma.</param>
			/// <param name="Param_QuantidadePlanos">O número de componentes planares solicitados.</param>
			/// <param name="Param_Out_Suporte">Retorna TRUE se as transformações solicitadas forem apoiadas nativamente.</param>
			CarenResult DoesSupportTransform(
				UInt32% Param_Ref_INOUT_Width, 
				UInt32% Param_Ref_INOUT_Height,
				CA_WICBitmapTransformOptions Param_DestinoTransformacao,
				CA_WICPlanarOptions Param_OpcoesPlanar,
				cli::array<String^>^ Param_GuidDestinoFormatos,
				[Out] cli::array<CA_WICBitmapPlaneDescription^>^% Param_Out_DescricaoPlanos,
				UInt32 Param_QuantidadePlanos,
				[Out] Boolean% Param_Out_Suporte);
		};

		/// <summary>
		/// (IWICPlanarFormatConverter) - Interface responsável por permitir que um conversor de formato seja inicializado com uma fonte planar. Você pode usar (ICaren::ConsultarInterface) para obter essa 
		/// interface da implementação de ICarenWICFormatConverter fornecida pelo Windows.
		/// </summary>
		[CategoryAttribute("WIC Interface")]	
		[Guid("5FBDB0B4-2E31-4B77-B0EF-DE2F57C16408")]
		public interface class ICarenWICPlanarFormatConverter : ICarenWICBitmapSource
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
			/// Consulta se o conversor de formato pode converter de um formato para outro.
			/// Para especificar um formato de pixel de entrada intercalado, forneça uma matriz de comprimento 1 para (Param_ArrayGuidFormatosPixel).
			/// Se a conversão não for suportada, este método retorna SS_OK, mas (Param_Out_Conversao) está definido como FALSE.
			/// </summary>
			/// <param name="Param_ArrayGuidFormatosPixel">Uma matriz de formatos de pixels WIC que representa planos de imagem de origem.</param>
			/// <param name="Param_QuantidadeFormatos">O número de formatos de pixels de origem especificados pelo parâmetro (Param_ArrayGuidFormatosPixel).</param>
			/// <param name="Param_GuidPixelDestino">O formato de pixel intercalado de destino.</param>
			/// <param name="Param_Out_Conversao">Retorna TRUE se a conversão for suportada.</param>
			CarenResult CanConvert(
				cli::array<String^>^ Param_ArrayGuidFormatosPixel,
				UInt32 Param_QuantidadeFormatos,
				String^ Param_GuidPixelDestino,
				[Out] Boolean% Param_Out_Conversao);

			/// <summary>
			/// Inicializa um conversor de formato com uma fonte plana e especifica o formato de pixel de saída intercalado.
			/// </summary>
			/// <param name="Param_ArrayPlanes">Uma matriz de interfaces (ICarenWICBitmapSource) que representa planos de imagem.</param>
			/// <param name="Param_QuantidadeImagens">O número de planos componentes especificados pelo parâmetro (Param_ArrayPlanes).</param>
			/// <param name="Param_GuidFormatoPixelDestino">O formato de pixel intercalado de destino.</param>
			/// <param name="Param_Dither">O CA_WICBitmapDitherType usado para conversão.</param>
			/// <param name="Param_Paleta">A paleta para usar para conversão.</param>
			/// <param name="Param_PorcentagemAlfa">O limiar alfa a ser usado para conversão.</param>
			/// <param name="Param_PaletaConversao">O tipo de tradução da paleta para usar para conversão.</param>
			CarenResult Initialize(
				cli::array<ICarenWICBitmapSource^>^ Param_ArrayPlanes,
				UInt32 Param_QuantidadeImagens,
				String^ Param_GuidFormatoPixelDestino,
				CA_WICBitmapDitherType Param_Dither,
				ICarenWICPalette^ Param_Paleta,
				double Param_PorcentagemAlfa,
				CA_WICBitmapPaletteType Param_PaletaConversao);
		};

		/// <summary>
		/// (IWICProgressiveLevelControl) - Interface responsável por expor métodos para obter informações e controlar a decodificação progressiva.
		/// As imagens só podem ser progressivamente decodificadas se forem progressivamente codificadas. Imagens progressivas começam automaticamente no nível progressivo mais alto (melhor qualidade). 
		/// O chamador deve definir manualmente o decodificador para um nível progressivo mais baixo. ER_NOTIMPL é devolvida se o codec não suportar a decodificação de nível progressivo.
		/// </summary>
		[CategoryAttribute("WIC Interface")]		
		[Guid("E3912631-7DEA-4394-9720-86AA8F4E427B")]
		public interface class ICarenWICProgressiveLevelControl : ICaren
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
			/// Obtém o nível progressivo atual do decodificador. O nível sempre é padrão para o mais alto nível progressivo. Para decodificar um nível progressivo mais baixo, o SetCurrentLevel deve primeiro ser chamado.
			/// </summary>
			/// <param name="Param_Out_LevelAtual">Retorna o nível atual especificado.</param>
			CarenResult GetCurrentLevel([Out] UInt32% Param_Out_LevelAtual);

			/// <summary>
			/// Obtém o número de níveis de decodificação progressiva suportado pelo CODEC.
			/// Os usuários não devem usar essa função para iterar através dos níveis progressivos de uma imagem JPEG progressiva. Os níveis progressivos jpeg são determinados pela imagem e não têm uma 
			/// contagem de nível fixo. O uso deste método forçará o aplicativo a esperar que todos os níveis progressivos sejam baixados antes que ele possa retornar. Em vez disso, os aplicativos devem 
			/// usar o seguinte código para iterar através dos níveis progressivos de uma imagem JPEG progressiva.
			/// </summary>
			/// <param name="Param_Out_QuantLeveis">Retorna o número de níveis suportados pelo CODEC.</param>
			CarenResult GetLevelCount([Out] UInt32% Param_Out_QuantLeveis);

			/// <summary>
			/// Especifica o nível a ser recuperado na próxima chamada para ICarenWICBitmapSource::CopyPixels.
			/// Uma chamada não precisa solicitar todos os níveis suportados. Se um chamador solicitar o nível 1, sem ter solicitado anteriormente o nível 0, os bits retornados pela próxima chamada para 
			/// CopyPixels incluirão ambos os níveis.
			/// Os usuários devem usar esse método para iterar através dos níveis progressivos de uma imagem JPEG progressiva em vez do método GetCurrentLevel. Os níveis progressivos jpeg são determinados 
			/// pela imagem e não têm uma contagem de nível fixo. O uso do método GetCurrentLevel forçará o aplicativo a esperar que todos os níveis progressivos sejam baixados antes que ele possa retornar. 
			/// Em vez disso, os aplicativos devem usar o seguinte código para iterar através dos níveis progressivos de uma imagem JPEG progressiva.
			/// Se o nível solicitado for inválido, o erro devolvido será ER_WINCODEC_ERR_INVALIDPROGRESSIVELEVEL.
			/// </summary>
			/// <param name="Param_Level">Especifica qual nível retornará em seguida. Se for maior do que o número total de níveis suportados, um erro será devolvido.</param>
			CarenResult SetCurrentLevel(UInt32 Param_Level);
		};
	}
}