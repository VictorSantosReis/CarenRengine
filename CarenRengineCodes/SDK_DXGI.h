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
#include "..\SDK_Base.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace DXGI
	{
		/// <summary>
		/// (IDXGIObject) - Representa a interface base para todos os objetos DXGI; O ICarenDXGIObject suporta associar -Private Data 
		/// (dados privados) com um objeto e recuperação de uma interface ao objeto pai.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Interface base para todos os objetos DXGI.")]
		[Guid("0A3A8723-DA55-44F1-A912-3055F9BEA6E4")]
		public interface class ICarenDXGIObject :ICaren
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
			/// (GetParent) - Recupera o objeto pai deste objeto.
			/// </summary>
			/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
			/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult ObterPaiObjeto(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

			/// <summary>
			/// (SetPrivateData) - Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
			/// </summary>
			/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
			/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
			/// <param name="Param_Dados">Ponteiro para os dados.</param>
			CarenResult DefinirDadosPrivados(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

			/// <summary>
			/// (GetPrivateData) - Obtém um ponteiro para os dados do objeto.
			/// </summary>
			/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
			/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
			/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por 
			/// liberar a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult ObterDadosPrivados(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

			/// <summary>
			/// (SetPrivateDataInterface) - Defina uma interface nos dados privados do objeto.
			/// </summary>
			/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
			/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
			CarenResult DefinirDadosPrivadosInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
		};

		/// <summary>
		/// (IDXGIDeviceSubObject) - Interface responsável por permitir que objetos herdados que estão ligados ao dispositivo para que 
		/// possam recuperar um ponteiro para ele.
		/// Está interface recupera um ponteiro para o dispositivo pai responsável do objeto DXGI atual.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Recupera o dispositivo de um objeto DXGI.")]
		[Guid("DC74E569-D95A-4AE8-9F0C-412DEBD95792")]
		public interface class ICarenDXGIDeviceSubObject : ICarenDXGIObject
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
			/// (GetDevice) - Recupera o dispositivo.
			/// </summary>
			/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
			/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult ObterDispositivo(String^ Param_RIIDInterface, ICaren^ Param_Out_Objeto);
		};

		/// <summary>
		/// (IDXGIResource) - Interface responsável por permitir o compartilhamento de recursos e identifica a memória em que um recurso reside.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Permite compartilhamento de recursos e identifica a memória em que o recurso reside.")]
		[Guid("39858A42-1671-443D-858B-ECEF57F9ACD2")]
		public interface class ICarenDXGIResource : ICarenDXGIDeviceSubObject
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
			/// (GetEvictionPriority) - Obtenha a prioridade de despejo.
			/// </summary>
			/// <param name="Param_Out_PrioridadeDespejo">Recebe valores da enumeração CA_DXGI_RESOURCE_PRIORITY, que determinam quando o recurso pode ser despejado.</param>
			CarenResult ObterPrioridadeDespejo([Out] CA_DXGI_RESOURCE_PRIORITY% Param_Out_PrioridadeDespejo);

			/// <summary>
			/// (GetSharedHandle) - Obtém a Handle para um recurso compartilhado.
			/// [A partir do Direct3D 11.1, recomendamos não usar o (ObterHandleCompartilhada) mais para recuperar a alça a um recurso compartilhado. Em vez disso, use o 
			/// ICarenDXGIResource1::CriarHandleCompartilhada para obter uma Handle para compartilhar. Para usar o ICarenDXGIResource1::CriarHandleCompartilhada deve especificar 
			/// que ele usa Handle NT (ou seja, você define a bandeira CA_D3D11_RESOURCE_MISC_SHARED_NTHANDLE). Também recomendamos que você crie recursos compartilhados que 
			/// usam Handles NT para que você possa usar CloseHandle, DuplicateHandle, e assim por diante esses recursos compartilhados.]
			/// </summary>
			/// <param name="Param_Out_SharedHandle">Retorna um ponteiro para a Handle compartilhada.</param>
			CarenResult ObterHandleCompartilhada([Out] IntPtr% Param_Out_SharedHandle);

			/// <summary>
			/// (GetUsage) - Obtenha o uso esperado de recursos.
			/// </summary>
			/// <param name="Param_Out_Usage">Recebe uma bandeira de uso(DXGI_USAGE). Para direct3D 10, uma superfície pode ser usada como entrada sombreadora ou uma saída de 
			/// destino renderizado.</param>
			CarenResult ObterUso([Out] CA_DXGI_USAGE% Param_Out_Usage);

			/// <summary>
			/// (SetEvictionPriority) - Defina a prioridade para despejar o recurso da memória.
			/// </summary>
			/// <param name="Param_PrioridadeDespejo">Um valor da enumeração CA_DXGI_RESOURCE_PRIORITY que define a prioridade do despejo.</param>
			CarenResult DefinirPrioridadeDespejo(CA_DXGI_RESOURCE_PRIORITY Param_PrioridadeDespejo);
		};

		/// <summary>
		/// (IDXGIResource1) - Interface responsável por estender a interface ICarenDXGIResource adicionando suporte para criar um objeto de superfície de subrecurso e 
		/// para criar uma Handle para um recurso compartilhado.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Permite compartilhamento de recursos e identifica a memória em que o recurso reside.")]
		[Guid("AE64A18D-9A54-49FD-BEA8-7735E91DFAEF")]
		public interface class ICarenDXGIResource1 : ICarenDXGIResource
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
			/// (CreateSharedHandle) - Cria uma Handle para um recurso compartilhado. Em seguida, você pode usar a Handle devolvida com vários dispositivos Direct3D.
			/// </summary>
			/// <param name="Param_Atributos">Uma estrutura CA_ATRIBUTOS_SEGURANCA que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e 
			/// um valor booleano que determina se os processos crianças podem herdar a Handle devolvida.
			/// Defina esse parâmetro para NULO se desejar que os processos filhos que o aplicativo possa criar não herdem a Handle retornado por CriarHandleCompartilhada e se 
			/// desejar que o recurso associado ao identificador retornado obtenha um descritor de segurança padrão.</param>
			/// <param name="Param_Acesso">Os direitos de acesso solicitados ao recurso. Você pode realizar um bitwise entre as enumerações CA_ACCESS_RIGHTS e CA_DXGI_SHARED_RESOURCE_RW 
			/// para definir esse parametro.</param>
			/// <param name="Param_Nome">O nome do recurso para compartilhar. O nome se limita a constante MAX_PATH. A comparação de nomes é sensível ao caso(CaseSensitive).
			/// Você precisará do nome de recurso se ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhadoPorNome para acessar o recurso compartilhado pelo nome. Se você, 
			/// em vez disso, ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhado1 para acessar o recurso compartilhado por cabo, defina este parâmetro para NULO.</param>
			/// <param name="Param_Out_Handle">Recebe o ponteiro para uma variável que recebe o valor NT HANDLE para o recurso para compartilhar. Você pode usar esta Handle em 
			/// chamadas para acessar o recurso.</param>
			CarenResult CriarHandleCompartilhada(
				CA_ATRIBUTOS_SEGURANCA^ Param_Atributos,
				UInt64 Param_Acesso,
				String^ Param_Nome,
				[Out] IntPtr% Param_Out_Handle);

			/// <summary>
			/// (CreateSubresourceSurface) - Cria um objeto de superfície subrecurso.
			/// </summary>
			/// <param name="Param_Index">O índice do objeto de superfície do subrecurso a ser enumerado.</param>
			/// <param name="Param_Out_DXGISurface2">Recebe um ponteiro para uma interface ICarenDXGISurface2 que representa o objeto de superfície do subrecurso criado na posição 
			/// especificada pelo parâmetro (Param_Index).  O usuário deve inicializar a interface antes de chamar este método. </param>
			CarenResult CriarSuperficeSubrecurso(UInt32 Param_Index, ICaren^ Param_Out_DXGISurface2);
		};

		/// <summary>
		/// (IDXGISurface) - Interface responsável por implementar métodos para objetos de dados de imagem.
		/// Um objeto de dados de imagem é uma seção 2D de memória, comumente chamada de superfície. Você pode utilizar a ICarenDXGIOutput::ObterDadosSuperficeExibicaoAtual
		/// para obter uma superfice a parti de uma saida(Output).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Superfice para dados de imagem 2D.")]
		[Guid("19BADCEE-6074-4DF0-B6D8-CFADACFDD367")]
		public interface class ICarenDXGISurface : ICarenDXGIDeviceSubObject
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
			/// (GetDesc) - Método responsável por obter uma descrição da superfície.
			/// </summary>
			/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
			CarenResult ObterDescricao([Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice);

			/// <summary>
			/// (Map) - Método responsável por obter um ponteiro para os dados contidos na superfície e negue o acesso da GPU à superfície.
			/// </summary>
			/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
			/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que contém os dados mapeados da superfice.</param>
			CarenResult Mapear(CA_DXGI_MAP_FLAGS Param_Flags, [Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado);

			/// <summary>
			/// (Unmap) - Método responsável por invalidar o ponteiro para a superfície recuperada pelo ICarenDXGISurface::Mapear e 
			/// reativar o acesso GPU ao recurso.
			/// </summary>
			CarenResult Desmapear();
		};

		/// <summary>
		/// (IDXGISurface1) - Interface responsável por estender a ICarenDXGISurface adicionando suporte para usar a Interface de Dispositivo 
		/// Gráfico Windows (GDI) para renderizar a uma superfície de Infraestrutura Gráfica Microsoft DirectX (DXGI).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Superfice para dados de imagem 2D.")]
		[Guid("8E0EDE31-EA20-463A-988B-C670BE104A06")]
		public interface class ICarenDXGISurface1 : ICarenDXGISurface
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
			/// (GetDC) - Retorna um contexto de dispositivo (DC) que permite que você se torne uma superfície de Infraestrutura Gráfica Microsoft DirectX (DXGI) usando a Interface do Dispositivo Gráfico windows (GDI).
			/// </summary>
			/// <param name="Param_Descartar">Um valor booleano que especifica se deve preservar o conteúdo Direct3D no GDI DC. 
			/// TRUE direciona o tempo de execução para não preservar o conteúdo Direct3D no GDI DC; ou seja, o tempo de execução 
			/// descarta o conteúdo Direct3D. False garante que o conteúdo Direct3D esteja disponível no GDI DC.</param>
			/// <param name="Param_Out_HDCHandle">Recebe um ponteiro para uma Handle(Alça) HDC que representa o contexto atual do dispositivo para renderização GDI.</param>
			CarenResult ObterDC(Boolean Param_Descartar, [Out] IntPtr% Param_Out_HDCHandle);

			/// <summary>
			/// (ReleaseDC) - Libera o contexto do dispositivo GDI (DC) que está associado à superfície atual e permite que você use o Direct3D para renderizar.
			/// </summary>
			/// <param name="Param_Regiao">Um ponteiro para uma estrutura rect que identifica a região suja da superfície. Uma região suja é qualquer 
			/// parte da superfície que você usou para renderização GDI e que você quer preservar.Esta área é usada como uma dica de desempenho para 
			/// subsistema gráfico em certos cenários.Não utilize este parâmetro para restringir a renderização à região retangular especificada. 
			/// Se você passar NULO, LiberarDC considera toda a superfície como suja. Caso contrário, o (LiberarDC) usa a área especificada pelo CA_RECT
			/// como uma dica de desempenho para indicar quais áreas foram manipuladas pela renderização GDI. Você pode passar um ponteiro para uma 
			/// estrutura rect vazia(um retângulo sem posição ou área) se você não alterar qualquer conteúdo.</param>
			CarenResult LiberarDC(CA_RECT^ Param_Regiao);
		};

		/// <summary>
		/// (IDXGISurface2) - Interface responsável por estender a interface ICarenDXGISurface1 adicionando suporte para superfícies de 
		/// subrecursos e obtendo uma alça a um recurso compartilhado. Qualquer objeto que suporte o ICarenDXGISurface também suporta 
		/// ICarenDXGISurface2.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Superfice para dados de imagem 2D.")]
		[Guid("4C85474A-81D3-4F7F-B43F-7420A9BA44FA")]
		public interface class ICarenDXGISurface2 : ICarenDXGISurface1
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
			/// (GetResource) - Obtém o índice de recursos parentais e subrecursos que suportam uma superfície de subrecursos.
			/// Os objetos atuais que implementam o IDXGISurface são recursos ou visualizações. GetResource para esses objetos retorna "this" ou o 
			/// recurso que suporta a exibição, respectivamente. Nesta situação, o índice de subrecursos é 0.
			/// </summary>
			/// <param name="Param_RIID">O identificador globalmente único (GUID) do tipo de interface solicitado.</param>
			/// <param name="Param_Out_ObjetoRecurso">Recebe um ponteiro para um buffer que recebe um ponteiro para o objeto de recurso pai para a superfície do subrecurso.  O usuário deve inicializar a interface antes de chamar este método.</param>
			/// <param name="Param_Ref_IndexSubrecurso">Recebe o índice da superfície do subrecurso.</param>
			CarenResult ObterRecurso(String^ Param_RIID, ICaren^ Param_Out_ObjetoRecurso, UInt32% Param_Ref_IndexSubrecurso);
		};

		/// <summary>
		/// (IDXGIOutputDuplication) - Interface responsável por acessar e manipular a imagem de desktop duplicada.
		/// Um aplicativo de colaboração pode usar o ICarenDXGIOutputDuplication para acessar a imagem da área de trabalho. ICarenDXGIOutputDuplication 
		/// é suportado no Desktop Window Manager (DWM) em modos de tela cheia(FullScreen) Directx não-8bpp e modos de tela cheia OpenGL não-8bpp. 
		/// Os modos de desktop GDI não DWM de 16 bits ou 32 bits não são suportados. Um aplicativo pode usar ICarenDXGIOutputDuplication em um thread 
		/// separado para receber as imagens de desktop e alimentá-las em seu pipeline específico de processamento de imagens.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Manipula dados da imagem do Desktop duplicado.")]
		[Guid("7ED62634-50F3-4827-8C4E-3479FD4FDD93")]
		public interface class ICarenDXGIOutputDuplication : ICarenDXGIObject
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
			/// (AcquireNextFrame) - Indica que o aplicativo está pronto para processar a próxima imagem de desktop.
			/// </summary>
			/// <param name="Param_TimeOutMilliSeconds">O intervalo de tempo limite, em milissegundos. Este intervalo especifica a quantidade de tempo que este método espera por um novo 
			/// quadro antes de retornar ao chamador. Este método retorna se o intervalo expirar e uma nova imagem da área de trabalho não estiver disponível.</param>
			/// <param name="Param_Out_FrameInfo">Recebe a estrutura CA_DXGI_OUTDUPL_FRAME_INFO que descreve estatísticas de tempo e apresentação para um quadro.</param>
			/// <param name="Param_Out_DesktopResource">Recebe um ponteiro para a interface ICarenDXGIResource da superfície que contém o bitmap desktop.</param>
			CarenResult AdquirirProximoFrame(
				UInt32 Param_TimeOutMilliSeconds,
				[Out] CA_DXGI_OUTDUPL_FRAME_INFO^% Param_Out_FrameInfo,
				[Out] ICarenDXGIResource^% Param_Out_DesktopResource);

			/// <summary>
			/// (GetDesc) - Recupera uma descrição de uma saída duplicada. Esta descrição especifica as dimensões da superfície que contém a imagem da área de trabalho.
			/// </summary>
			/// <param name="Param_Out_Desc">Recebe uma estrutura CA_DXGI_OUTDUPL_DESC que descreve a saída duplicada.</param>
			CarenResult ObterDescricao([Out] CA_DXGI_OUTDUPL_DESC^% Param_Out_Desc);

			/// <summary>
			/// (GetFrameDirtyRects) - Obtém informações sobre retângulos sujos para o quadro(Frame) de desktop atual.
			/// </summary>
			/// <param name="Param_SizeMatrizRetangulos">O tamanho em bytes do buffer que o chamador passou para o parâmetro Param_Out_MatrizRetangulosSujos.</param>
			/// <param name="Param_Out_MatrizRetangulosSujos">Recebe uma série de estruturas CA_RECT que identifica as regiões de retângulo sujo para o quadro de desktop.</param>
			/// <param name="Param_Out_SizeMatrizRetangulos">Recebe o número de bytes que (ObterFrameDirtyRects) precisa armazenar informações sobre regiões sujas 
			/// no buffer em (Param_Out_MatrizRetangulosSujos).</param>
			CarenResult ObterFrameDirtyRects(
				UInt32 Param_SizeMatrizRetangulos,
				[Out] cli::array<CA_RECT^>^% Param_Out_MatrizRetangulosSujos,
				[Out] UInt32% Param_Out_SizeMatrizRetangulos);

			/// <summary>
			/// (GetFrameMoveRects) - Obtém informações sobre os retângulos movidos para o quadro(Frame) de desktop atual.
			/// </summary>
			/// <param name="Param_SizeMatrizMoveRects">O tamanho em bytes do buffer que o chamador passou para o parâmetro Param_Out_MatrizMoveRects.</param>
			/// <param name="Param_Out_MatrizMoveRects">Recebe uma matriz de estruturas CA_DXGI_OUTDUPL_MOVE_RECT que identifica as regiões de retângulo movido para o 
			/// quadro de desktop.</param>
			/// <param name="Param_Out_SizeMatrizMoveRects">Recebe o número de bytes que (ObterFrameMoveRects) precisa para armazenar informações sobre regiões movidas no buffer 
			/// no Param_Out_MatrizMoveRects.</param>
			CarenResult ObterFrameMoveRects(
				UInt32 Param_SizeMatrizMoveRects, 
				[Out] cli::array<CA_DXGI_OUTDUPL_MOVE_RECT^>^% Param_Out_MatrizMoveRects,
				[Out] UInt32% Param_Out_SizeMatrizMoveRects);

			/// <summary>
			/// (GetFramePointerShape) - Obtém informações sobre a nova forma do ponteiro para o quadro(Frame) de desktop atual.
			/// </summary>
			/// <param name="Param_SizeBufferShape">O tamanho em bytes do buffer que o chamador passou para o parâmetro (Param_Ref_ShapePointerBuffer).</param>
			/// <param name="Param_Ref_ShapePointerBuffer">Um ponteiro para um buffer para o qual o (ObterFramePointerShape) copia e retorna dados de pixels para a nova 
			/// forma do ponteiro.</param>
			/// <param name="Param_Out_SizeBufferShapeRequerido">Recebe o número de bytes que o (ObterFramePointerShape) precisa para armazenar os novos dados de pixel de 
			/// forma de ponteiro no buffer em (Param_Ref_ShapePointerBuffer).</param>
			/// <param name="Param_Out_PointerShapeInfo">Recebe uma estrutura CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO que contém as informações de forma do ponteiro.</param>
			CarenResult ObterFramePointerShape(
				UInt32 Param_SizeBufferShape,
				ICarenBuffer^% Param_Ref_ShapePointerBuffer,
				[Out] UInt32% Param_Out_SizeBufferShapeRequerido,
				[Out] CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^% Param_Out_PointerShapeInfo);

			/// <summary>
			/// (MapDesktopSurface) - Fornece a CPU acesso eficiente a uma imagem desktop se essa imagem de desktop já estiver na memória do sistema.
			/// </summary>
			/// <param name="Param_Out_MapData">Retorna uma estrutura CA_DXGI_MAPPED_RECT que recebe os dados superficiais que a CPU precisa para acessar diretamente 
			/// os dados da superfície.</param>
			CarenResult MapearSuperficeDesktop([Out] CA_DXGI_MAPPED_RECT^% Param_Out_MapData);

			/// <summary>
			/// (ReleaseFrame) - Indica que o aplicativo terminou de processar o quadro(Frame).
			/// </summary>
			CarenResult LiberarFrame();

			/// <summary>
			/// (UnMapDesktopSurface) - Invalida o ponteiro para a imagem de desktop que foi recuperada usando ICarenDXGIOutputDuplication::MapearSuperficeDesktop.
			/// </summary>
			CarenResult UnMapearSuperficeDesktop();
		};
	
		/// <summary>
		/// (IDXGIOutput) - Interface responsável por representar uma saída de adaptador(como um monitor).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("55B6B862-E3AF-4759-A376-0B8F500B0DD0")]
		public interface class ICarenDXGIOutput : ICarenDXGIObject
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
			/// (FindClosestMatchingMode) - Encontra o modo de exibição que mais se corresponde ao modo de exibição solicitado.
			/// </summary>
			/// <param name="Param_ModoDesc">O modo de exibição desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC não podem ser especificados indicando nenhuma preferência por esse membro. Um valor de 0 para largura ou altura indica 
			/// que o valor não é especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que não é especificado. Outros membros da DXGI_MODE_DESC têm valores de enumeração indicando 
			/// que o membro não é especificado. Se (Param_Dispositivo3D) é NULO, formatonão pode ser DXGI_FORMAT_UNKNOWN.</param>
			/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
			/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro é NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) serão devolvidos; caso contrário, apenas os formatos que 
			/// são suportados para digitalização pelo dispositivo são devolvidos.</param>
			CarenResult EncontrarModoExibicaoAdequado(CA_DXGI_MODE_DESC^ Param_ModoDesc, [Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, ICaren^ Param_Dispositivo3D);

			/// <summary>
			/// (GetDesc) - Obter uma descrição da saída.
			/// </summary>
			/// <param name="Param_Out_DescSaida">Retorna uma estrutura que contém a descrição da saida.</param>
			CarenResult ObterDescricao([Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida);

			/// <summary>
			/// (GetDisplayModeList) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
			/// </summary>
			/// <param name="Param_Formato">O formato de cor.</param>
			/// <param name="Param_Flags">Opções para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibição que exigem escala. Os modos centrados, que não exigem escala e correspondentes diretamente à 
			/// saída da tela, são enumerados por padrão.</param>
			/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDescModos). Na saida contém a quantidade de dados de (Param_Out_MatrizDescModos).</param>
			/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
			/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibição.</param>
			CarenResult ObterListaModosExibicao(
				CA_DXGI_FORMATO Param_Formato, 
				CA_DXGI_ENUM_MODES Param_Flags, 
				Boolean Param_RecuperaQuantidadeModos,
				UInt32% Param_Ref_QuantidadeModos,
				[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos);

			/// <summary>
			/// (GetDisplaySurfaceData) - Obtém uma cópia da superfície de exibição atual.
			/// O método só pode ser chamado quando uma saída está no modo de tela cheia. Se o método for bem-sucedido, a DXGI preenche a superfície do destino.
			/// </summary>
			/// <param name="Param_SuperficeDestino">Um ponteiro para uma superfície de destino que vai receber a superfice.</param>
			CarenResult ObterDadosSuperficeExibicaoAtual(ICarenDXGISurface^% Param_SuperficeDestino);

			/// <summary>
			/// (GetFrameStatistics) - Obtém estatísticas sobre quadros recentemente renderizados.
			/// </summary>
			/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informações.</param>
			CarenResult ObterEstatisticasFrame([Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame);

			/// <summary>
			/// (GetGammaControl) - Obtém as configurações de controle gama.
			/// </summary>
			/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que contém as informações do controle gamma.</param>
			CarenResult ObterControleGamma([Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma);

			/// <summary>
			/// (GetGammaControlCapabilities) - Obtém uma descrição das capacidades de controle gama.
			/// </summary>
			/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que contém as descrições das capcidades do controle Gamma.</param>
			CarenResult ObterDescricaoCapacidadesControleGamma([Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps);

			/// <summary>
			/// (ReleaseOwnership) - Libera a propriedade da saída.
			/// </summary>
			CarenResult LiberarPropriedadeSaida();

			/// <summary>
			/// (SetDisplaySurface) - Altera o modo de exibição.
			/// </summary>
			/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
			CarenResult DefinirSuperficeDisplay(ICarenDXGISurface^% Param_Superfice);

			/// <summary>
			/// (SetGammaControl) - Define os controles gama.
			/// </summary>
			/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
			CarenResult DefinirControlesGamma(CA_DXGI_GAMMA_CONTROL^ Param_ControleGama);

			/// <summary>
			/// (TakeOwnership) - Toma posse de uma saída. Quando você terminar com a saída, chame o método ICarenDXGIOutput::LiberarPropriedadeSaida().
			/// Este método não deve ser chamado diretamente por aplicativos, uma vez que os resultados serão imprevisíveis. É chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transições em tela cheia, e não deve ser usado como 
			/// um substituto para métodos de cadeia de swap.
			/// </summary>
			/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
			/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros tópicos ou aplicativos para assumir a propriedade do dispositivo; caso contrário, definido como FALSE.</param>
			CarenResult ObterPosseSaida(ICaren^ Param_DispositivoD3D, Boolean Param_Exclusivo);

			/// <summary>
			/// (WaitForVBlank ) - Pare um Thread até que o próximo espaço em branco vertical ocorra.
			/// </summary>
			CarenResult AguardarForVBlank();
		};

		/// <summary>
		/// (IDXGIOutput1) - Interface responsável por representar uma saída de adaptador(como um monitor).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("257056E1-0601-4411-B201-F6ECDE6ECC89")]
		public interface class ICarenDXGIOutput1 : ICarenDXGIOutput
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
			/// (DuplicateOutput) - Cria uma interface de duplicação de desktop a partir da interface ICarenDXGIOutput1 que representa uma saída de 
			/// adaptador.
			/// </summary>
			/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída está conectada.</param>
			/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
			CarenResult DuplicarSaida(ICaren^ Param_Dispositivo3D, [Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada);

			/// <summary>
			/// (FindClosestMatchingMode1) - Encontra o modo de exibição que mais combina com o modo de exibição solicitado.
			/// </summary>
			/// <param name="Param_DescCombine">Uma estrutura CA_DXGI_MODE_DESC1 que descreve o modo de exibição para combinar. Os membros da CA_DXGI_MODE_DESC1 
			/// podem ser não especificados, o que indica que não há preferência por esse membro. Um valor de 0 para Largura ou Altura indica que o valor
			/// não está especificado. Se largura ou altura for 0, ambos devem ser 0. Um numerador e denominador de 0 no RefreshRate indicam que ele não 
			/// está especificado. Outros membros do CA_DXGI_MODE_DESC1 possuem valores de enumeração que indicam que o membro não está especificado. 
			/// Se o (Param_Dispositivo3D) for NULO, o membro (Formato) em CA_DXGI_MODE_DESC1 não pode ser CA_DXGI_FORMAT_UNKNOWN.</param>
			/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro for NULO, o (EncontrarModoExibicaoAdequado1) 
			/// retorna apenas modos cujo formato corresponde ao do Param_DescCombine; caso contrário, o (EncontrarModoExibicaoAdequado1) retorna apenas 
			/// aos formatos suportados para escaneamento pelo dispositivo.</param>
			/// <param name="Param_Out_DescCorrespondente"> Recebe uma estrutura CA_DXGI_MODE_DESC1 que contém uma descrição do modo de exibição que 
			/// mais corresponde ao modo de exibição descrito no Param_DescCombine.</param>
			CarenResult EncontrarModoExibicaoAdequado1(
				CA_DXGI_MODE_DESC1^ Param_DescCombine, 
				ICaren^ Param_Dispositivo3D, 
				[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente);

			/// <summary>
			/// (GetDisplayModeList1) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
			/// </summary>
			/// <param name="Param_Formato">Um valor CA_DXGI_FORMATO digitado para o formato de cor.</param>
			/// <param name="Param_Flags">Uma combinação de valores CA_DXGI_ENUM_MODES digitados que são combinados usando uma operação ou bitwise. O valor 
			/// resultante especifica opções para modos de exibição para incluir. Você deve especificar CA_DXGI_ENUM_MODES_SCALING para expor os modos 
			/// de exibição que requerem dimensionamento. Os modos centrados que não requerem escala e correspondem diretamente à saída do display são 
			/// enumerados por padrão.</param>
			/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
			/// <param name="Param_Ref_QuantidadeModos">Recebe o número de modos de exibição que o (ObterListaModosExibicao1) retorna no bloco de memória
			/// para o qual o (Param_Out_MatrizDecModos) aponta. Defina (Param_Out_MatrizDecModos) para NULO para que o (Param_Ref_QuantidadeModos) 
			/// retorne o número de modos de exibição que correspondam ao formato e às opções. Caso contrário, o (Param_Ref_QuantidadeModos) retorna o 
			/// número de modos de exibição devolvidos no (Param_Out_MatrizDecModos).</param>
			/// <param name="Param_Out_MatrizDecModos">Recebe uma lista de modos de exibição.</param>
			CarenResult ObterListaModosExibicao1(
				CA_DXGI_FORMATO Param_Formato, 
				CA_DXGI_ENUM_MODES Param_Flags, 
				Boolean Param_RecuperaQuantidadeModos,
				UInt32% Param_Ref_QuantidadeModos, 
				[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDecModos);

			/// <summary>
			/// (GetDisplaySurfaceData1) - Copia a superfície do display(buffer frontal) para um recurso fornecido pelo usuário.
			/// </summary>
			/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
			/// (ObterDadosSuperficeExibicaoAtual1) copia a superfície do display. A interface não pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
			CarenResult ObterDadosSuperficeExibicaoAtual1(ICarenDXGIResource^ Param_SuperficeDestino);
		};

		/// <summary>
		/// (IDXGIOutput2) - Interface responsável por representar uma saída de adaptador (como um monitor). A interface ICarenDXGIOutput2 
		/// expõe um método para verificar se há suporte de sobreposição multiplano no adaptador de saída primária.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("802A77EB-B023-4414-B14C-97A26CDF30E0")]
		public interface class ICarenDXGIOutput2 : ICarenDXGIOutput1
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
			/// (SupportsOverlays) - Consulta uma saída de adaptador para suporte de sobreposição multiplano.
			/// </summary>
			/// <param name="Param_Out_Suporte">Recebe TRUE se o adaptador de saída é o adaptador primário e suporta sobreposições multiplanárias, caso 
			/// contrário retorna FALSE.</param>
			CarenResult SuporteOverlay([Out] Boolean Param_Out_Suporte);
		};

		/// <summary>
		/// (IDXGIOutput3) - Interface responsável por representar uma saída de adaptador (como um monitor). A interface ICarenDXGIOutput3
		/// expõe um método para verificar se há suporte sobreposição.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("B84DBF7C-5DE4-424F-BE3E-8F04E163E633")]
		public interface class ICarenDXGIOutput3 : ICarenDXGIOutput2
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
			/// (CheckOverlaySupport) - Verifica o apoio ao Overlay(Sobrepor).
			/// </summary>
			/// <param name="Param_Formato">Um valor CA_DXGI_FORMATO digitado para o formato de cor.</param>
			/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O (ChecarSuporteOverlay)
			/// retorna apenas informações de suporte sobre este dispositivo de varredura.</param>
			/// <param name="Param_Out_Flags">Recebe uma variável que recebe uma combinação de valores digitados 
			/// CA_DXGI_OVERLAY_SUPPORT_FLAGque são combinados usando uma operação ou bitwise. O valor resultante especifica 
			/// opções de suporte sobreposição.</param>
			CarenResult ChecarSuporteOverlay(
				CA_DXGI_FORMATO Param_Formato, 
				ICaren^ Param_DispositivoD3D, 
				[Out] CA_DXGI_OVERLAY_SUPPORT_FLAG% Param_Out_Flags);
		};

		/// <summary>
		/// (IDXGIOutput4) - Interface responsável por representar uma saída de adaptador (como um monitor). A interface ICarenDXGIOutput4 
		/// expõe um método para verificar se há suporte ao espaço de cores sobreposição.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("EECDE14C-FA4D-47D2-BD18-6768EDFAB701")]
		public interface class ICarenDXGIOutput4 : ICarenDXGIOutput3
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
			/// (CheckOverlayColorSpaceSupport) - Verifica se há suporte ao espaço de cores.
			/// </summary>
			/// <param name="Param_Formato">Um valor CA_DXGI_FORMATO digitado para o formato de cor.</param>
			/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE digitado que especifica o tipo de espaço de cor 
			/// para verificar o suporte de sobreposição.</param>
			/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O 
			/// (VerificarSuporteOverlayColorSpace) retorna apenas informações de suporte sobre este dispositivo de varredura.</param>
			/// <param name="Param_Out_Flags">Recebe uma variável que recebe uma combinação de valores tipo tipo de 
			/// CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG que são combinados usando uma operação ou bitwise. O valor resultante 
			/// especifica opções para suporte ao espaço de cores sobreposição.</param>
			CarenResult VerificarSuporteOverlayColorSpace(
				CA_DXGI_FORMATO Param_Formato,
				CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace,
				ICaren^ Param_DispositivoD3D, 
				[Out] CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG% Param_Out_Flags);
		};

		/// <summary>
		/// (IDXGIOutput5) - Interface responsável por representar uma saída de adaptador (como um monitor). A interface ICarenDXGIOutput5
		/// expõe um único método para especificar uma lista de formatos suportados para superfícies de tela cheia(FullScreen).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("519304AE-2C56-448F-8D5F-F9E94AE9CBB2")]
		public interface class ICarenDXGIOutput5 : ICarenDXGIOutput4
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
			/// (DuplicateOutput1) - 
			/// </summary>
			/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para 
			/// processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída 
			/// está conectada.</param>
			/// <param name="Param_Flags">Reservado para uso futuro. Deixe como 0.</param>
			/// <param name="Param_QuantidadeFormatosSuportados">Especifica o número de formatos suportados.</param>
			/// <param name="Param_ListaFormatosSuportados">Uma matriz de formatos suportados que tem como contagem igual a (Param_QuantidadeFormatosSuportados).</param>
			/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
			CarenResult DuplicarSaida1(
				ICaren^ Param_Dispositivo3D, 
				UInt32 Param_Flags,
				UInt32 Param_QuantidadeFormatosSuportados,
				cli::array<CA_DXGI_FORMATO>^ Param_ListaFormatosSuportados,
				[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada);
		};

		/// <summary>
		/// (IDXGIOutput6) - Interface responsável por representar uma saída de adaptador (como um monitor). A interface ICarenDXGIOutput6 
		/// expõe métodos para fornecer recursos específicos de monitor.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma saida de adaptador.")]
		[Guid("F65C6B2A-A2F2-45BA-9321-BD45138CCB84")]
		public interface class ICarenDXGIOutput6 : ICarenDXGIOutput5
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
			/// (CheckHardwareCompositionSupport) - Notifica aplicativos de que o alongamento de hardware é suportado.
			/// </summary>
			/// <param name="Param_Out_FlagsSuporte">Retorna um bitfield de CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS valores de 
			/// enumeração descrevendo quais tipos de composição de hardware são suportados. Os valores são bitwise OR juntos.</param>
			CarenResult VerificarSuporteHardwareComposition(
				[Out] CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS% Param_Out_FlagsSuporte);

			/// <summary>
			/// (GetDesc1) - Obtém uma descrição estendida da saída que inclui características de cores e tipo de conexão.
			/// </summary>
			/// <param name="Param_Out_Desc">Retorna uma estrutura com a descrição da saida.</param>
			CarenResult ObterDescricao1([Out] CA_DXGI_OUTPUT_DESC1^% Param_Out_Desc);
		};

		/// <summary>
		/// (IDXGIAdapter) - Interface responsável por representar um subsistema de exibição (incluindo uma ou mais GPU's, DACs e 
		/// memória de vídeo).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa um adaptador(subsistema de exibição).")]
		[Guid("201BFF3D-BF69-4AE8-9A09-B92D6A663895")]
		public interface class ICarenDXGIAdapter : ICarenDXGIObject
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
			/// (CheckInterfaceSupport) - Verifica se o sistema suporta uma interface do dispositivo para um componente gráfico.
			/// </summary>
			/// <param name="Param_GuidInterface">O GUID da interface da versão do dispositivo para a qual o suporte está sendo verificado.</param>
			/// <param name="Param_Out_UMDVersion">A versão do motorista do modo de usuário do (Param_GuidInterface). Isso só é devolvido se a interface for suportada, caso contrário, este parâmetro será -12354.</param>
			CarenResult ChecarSuporteInterface(String^ Param_GuidInterface, [Out] Int64% Param_Out_UMDVersion);

			/// <summary>
			/// (EnumOutputs) - Saídas de adaptador enumerado (cartão de vídeo).
			/// </summary>
			/// <param name="Param_IndexSaida">O índice da saída.</param>
			/// <param name="Param_Out_Saida">O endereço de um ponteiro para uma interface ICarenDXGIOutput na posição especificada pelo parâmetro (Param_IndexSaida).</param>
			CarenResult EnumerarSaidas(UInt32 Param_IndexSaida, [Out] ICarenDXGIOutput^% Param_Out_Saida);

			/// <summary>
			/// (GetDesc) - Obtém uma descrição DXGI 1.0 de um adaptador (ou cartão de vídeo).
			/// </summary>
			/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (ObterDescricao) retorna zeros para o 
			/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
			CarenResult ObterDescricao([Out] CA_DXGI_ADAPTER_DESC^% Param_Out_DescAdaptador);
		};

		/// <summary>
		/// (IDXGIAdapter1) - Interface responsável por representar um subsistema de exibição (incluindo uma ou mais GPU's, DACs e 
		/// memória de vídeo).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa um adaptador(subsistema de exibição).")]
		[Guid("E7DFDC56-B104-434C-AE8C-75D31921F8B7")]
		public interface class ICarenDXGIAdapter1 : ICarenDXGIAdapter
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
			/// (GetDesc1) - Obtém uma descrição DXGI 1.1 de um adaptador (ou cartão de vídeo).
			/// </summary>
			/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC1 que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (ObterDescricao1) retorna zeros para o 
			/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC1 e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
			CarenResult ObterDescricao1([Out] CA_DXGI_ADAPTER_DESC1^% Param_Out_DescAdaptador);
		};

		/// <summary>
		/// (IDXGIAdapter2) - Interface responsável por representar um subsistema de exibição (incluindo uma ou mais GPU's, DACs e 
		/// memória de vídeo).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa um adaptador(subsistema de exibição).")]
		[Guid("77589733-91B2-4886-BB1B-1F3D543414FA")]
		public interface class ICarenDXGIAdapter2 : ICarenDXGIAdapter1
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
			/// (GetDesc2) - Obtém uma descrição 1.2 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. 
			/// Esta descrição inclui informações sobre a granularidade em que a unidade de processamento gráfico (GPU) pode ser impedida de realizar 
			/// sua tarefa atual.
			/// </summary>
			/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC2 que descreve o adaptador. Este parâmetro não deve ser 
			/// NULO.No hardware gráfico nível 9, versões anteriores do ObterDescricao2(ObterDescricao e ObterDescricao1) retorna zero para o 
			/// PCI ID em e (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do adaptador e "Adaptador de Software" para a descrição 
			/// do membro (Description). O ObterDescricao2 retorna os valores reais de hardware nível 9 nesses membros.</param>
			CarenResult ObterDescricao2([Out] CA_DXGI_ADAPTER_DESC2^% Param_Out_DescAdaptador);
		};
		
		/// <summary>
		/// (IDXGIAdapter3) - Interface responsável por adicionar alguns métodos de residência de memória, para orçar e reservar memória 
		/// física.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa um adaptador(subsistema de exibição).")]
		[Guid("A3C19C98-7943-4F3E-9035-A31C447A987C")]
		public interface class ICarenDXGIAdapter3 : ICarenDXGIAdapter2
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
			/// (QueryVideoMemoryInfo) - Este método informa o processo de uso do orçamento e do processo atual.
			/// </summary>
			/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações da memória de vídeo são consultadas. Para operação de GPU única, coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de vídeo são consultadas.</param>
			/// <param name="Param_GrupoSegmento">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
			/// <param name="Param_Out_InfoMemoria">Recebe uma estrutura CA_DXGI_QUERY_VIDEO_MEMORY_INFO com os valores atuais.</param>
			CarenResult ConsultarInfoMemoriaVideo(
				UInt32 Param_NodeId, 
				CA_DXGI_MEMORY_SEGMENT_GROUP Param_GrupoSegmento, 
				[Out] CA_DXGI_QUERY_VIDEO_MEMORY_INFO^% Param_Out_InfoMemoria);

			/// <summary>
			/// (RegisterHardwareContentProtectionTeardownStatusEvent) - Se registra para receber notificação de eventos de proteção de proteção de conteúdo de hardware.
			/// </summary>
			/// <param name="Param_Evento">Uma Handle para o objeto de evento que o sistema operacional define quando ocorre o (TearDown) de proteção de conteúdo de hardware. </param>
			/// <param name="Param_Out_Cookie">um valor-chave que um aplicativo pode passar para o método ICarenDXGIAdapter3:::CancelarHardwareContentProtectionTeardownStatus para 
			/// descadastrar o evento de notificação que o Param_Evento especifica.</param>
			CarenResult RegistrarHardwareContentProtectionTeardownStatusEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

			/// <summary>
			/// (RegisterVideoMemoryBudgetChangeNotificationEvent) - Este método estabelece uma correlação entre um objeto de sincronização da CPU e o evento de mudança orçamentária.
			/// </summary>
			/// <param name="Param_Evento">Uma Handle para o objeto de evento.</param>
			/// <param name="Param_Out_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent
			/// retorna esse valor.</param>
			CarenResult RegistrarVideoMemoryBudgetChangeNotificationEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

			/// <summary>
			/// (SetVideoMemoryReservation) - Este método envia a memória física mínima necessária para uma aplicação, para o Sistema Operacional.
			/// </summary>
			/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações de memória de vídeo estão sendo definidas. Para operação de GPU única, 
			/// coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de 
			/// vídeo estão sendo definidas.</param>
			/// <param name="Param_SegmentoGrupoMemoria">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
			/// <param name="Param_ReversaMemoria">Especifica um UInt64 que define a memória física mínima necessária, em bytes.</param>
			CarenResult DefinirReversaMemoriaVideo(
				UInt32 Param_NodeId, 
				CA_DXGI_MEMORY_SEGMENT_GROUP Param_SegmentoGrupoMemoria, 
				UInt64 Param_ReversaMemoria);

			/// <summary>
			/// (UnregisterHardwareContentProtectionTeardownStatus) - O Desregistra(Cancelar) um evento para impedi-lo de receber a notificação de eventos de proteção de 
			/// conteúdo de hardware.
			/// </summary>
			/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent 
			/// retorna esse valor.</param>
			CarenResult CancelarHardwareContentProtectionTeardownStatus(UInt32 Param_Cookie);

			/// <summary>
			/// (UnregisterVideoMemoryBudgetChangeNotification) - Este método deixa de notificar um objeto de sincronização da CPU sempre que ocorre uma mudança orçamentária. Um aplicativo pode mudar para a votação regular das informações.
			/// </summary>
			/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegistrarHardwareContentProtectionTeardownStatusEvent 
			/// retorna esse valor.</param>
			CarenResult CancelarVideoMemoryBudgetChangeNotification(UInt32 Param_Cookie);
		};

		/// <summary>
		/// (IDXGIAdapter4) - Interface responsável por representar um subsistema de exibição, e estende essa família de interfaces para 
		/// expor um método para verificar a compatibilidade de um adaptador com o Arbitrary Code Guard(ACG).
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa um adaptador(subsistema de exibição).")]
		[Guid("54318C46-2D2E-4B07-8689-6E2B659376B7")]
		public interface class ICarenDXGIAdapter4 : ICarenDXGIAdapter3
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
			/// (GetDesc3) - Obtém uma descrição 1.6 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. Esta descrição inclui 
			/// informações sobre compatibilidade com ACG.
			/// </summary>
			/// <param name="Param_Out_DescAdaptador">Recebe uma estrutura CA_DXGI_ADAPTER_DESC3 que descreve o adaptador. Este parâmetro não deve ser NULO. No hardware gráfico nível 9, 
			/// versões iniciais do ObterDescricao3(ObterDescricao1 ObterDescricao) retornam zeros para o ID PCI em (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do 
			/// adaptador e "Adaptador de Software" para a string de descrição no membro (Description). ObterDescricao3 e ObterDescricao2 retornam os valores reais de hardware nível 9 
			/// nesses membros.</param>
			CarenResult ObterDescricao3([Out] CA_DXGI_ADAPTER_DESC3^% Param_Out_DescAdaptador);
		};

		/// <summary>
		/// (IDXGISwapChain) - Interface responsável por implementar uma ou mais superfícies para armazenar dados processados antes de apresentá-los a uma saída.
		/// Utilize as interfaces (IDXGIFactory) para criar uma cadeia de swap de acordo com sua necessidade, ou obtenha durante a criação de um dispositivo do Direct3D 11; no entanto, você só pode acessar o subconjunto de funcionalidade 
		/// de cadeia de swaps que a interface ICarenDXGISwapChain fornece.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma cadeia de troca DXGI.")]
		[Guid("327EAE57-8309-4FAE-B98D-4D863E393799")]
		public interface class ICarenDXGISwapChain : ICarenDXGIDeviceSubObject
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
			/// (GetBuffer) - Acessa um dos buffers de volta da cadeia de swaps.
			/// </summary>
			/// <param name="Param_IndexBuffer">O Indince para o buffer de volta(Back-Buffer).</param>
			/// <param name="Param_RiidInterface">O tipo de interface usada para manipular o buffer.</param>
			/// <param name="Param_Out_InterfaceBuffer">Retorna a interface que gerencia o Buffer de volta(Back-Buffer). O Usuário é responsável por criar a interface que será retornada.</param>
			CarenResult ObterBuffer(UInt32 Param_IndexBuffer, String^ Param_RiidInterface, ICaren^ Param_Out_InterfaceBuffer);

			/// <summary>
			/// (GetContainingOutput) - Obtém a saída (o monitor de exibição) que contém a maior parte da área do cliente da janela alvo.
			/// Se o método for bem-sucedido, a interface de saída será preenchida e sua contagem de referência incrementada. Quando você terminar com ele, não se esqueça de liberar a interface para evitar um vazamento de memória.
			/// </summary>
			/// <param name="Param_Out_MonitorSaida">Retorna a interface para o monitor de exbicão de saida.</param>
			CarenResult ObterMonitorExebicaoSaida([Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

			/// <summary>
			/// (GetDesc) - Obtém uma descrição da cadeia de swaps.
			/// </summary>
			/// <param name="Param_Out_DescricaoCadeiaSwap">Retorna uma estrutura com a descrição da cadeia de troca.</param>
			CarenResult ObterDescricao([Out] Estruturas::CA_DXGI_SWAP_CHAIN_DESC^% Param_Out_DescricaoCadeiaSwap);

			/// <summary>
			/// (GetFrameStatistics) - Obtém estatísticas de desempenho sobre o último quadro render.
			/// </summary>
			/// <param name="Param_Out_FrameEstatisticas">Retorna uma estrutura com as estatiticas do frame.</param>
			CarenResult ObterEstatisticasFrame([Out] Estruturas::CA_DXGI_FRAME_STATISTICS^% Param_Out_FrameEstatisticas);

			/// <summary>
			/// (GetFullscreenState) - Associe o estado ao modo de tela cheia.
			/// </summary>
			/// <param name="Param_Out_EstadoFullScreen">Retorna o estado do FullScreen. Se TRUE, a cadeia de swap está no modo de tela cheia. Se FALSE, a cadeia de swap está em modo de janela.</param>
			/// <param name="Param_Out_MonitorSaida">Retorna um ponteiro para o monitor de saida quando em modo de Tela Cheia(FullScreen); caso contrario retorna NULO.</param>
			CarenResult ObterEstadoFullScreen([Out] Boolean% Param_Out_EstadoFullScreen, [Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

			/// <summary>
			/// (GetLastPresentCount) - Obtém o número de vezes que o método ICarenDXGISwapChain::Apresentar ou ICarenDXGISwapChain1::Apresentar1 foi chamado.
			/// </summary>
			/// <param name="Param_Out_QuantidadeChamadas">Retorna a quantidade de chamadas para o método Apresentar ou Apresentar1.</param>
			CarenResult ObterQuantidadeChamadasPresent([Out] UInt32% Param_Out_QuantidadeChamadas);

			/// <summary>
			/// (Present) - Apresenta uma imagem renderizada ao usuário.
			/// </summary>
			/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
			/// <param name="Param_Flags">Um valor inteiro que contém opções de apresentação em cadeia de swaps. Essas opções são definidas pela enumeração (CA_DXGI_PRESENT).</param>
			CarenResult Apresentar(UInt32 Param_IntervaloSincronizacao, Enumeracoes::CA_DXGI_PRESENT Param_Flags);

			/// <summary>
			/// (ResizeBuffers) - Altera o tamanho, o formato e o número de buffers da cadeia de swap. Isso deve ser chamado quando a janela do aplicativo é redimensionada.
			/// Você não pode redimensionar uma cadeia de swap sem que libere todas as referências pendentes aos seus buffers traseiros. Você deve liberar todas as suas referências diretas e indiretas nos buffers de volta para que 
			/// o (AlterarTamanhoBuffers) tenha sucesso.
			/// </summary>
			/// <param name="Param_NumeroBuffers">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e dianteiros). Este número pode ser diferente do número de buffers com os quais você criou a cadeia de swap. 
			/// Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o número existente de amortecedores na cadeia de swaps.</param>
			/// <param name="Param_Largura">A nova largura do amortecedor traseiro. Se você especificar zero, DXGI usará a largura da área do cliente da janela do alvo.</param>
			/// <param name="Param_Altura">A nova altura do amortecedor traseiro. Se você especificar zero, DXGI usará a altura da área do cliente da janela do alvo. </param>
			/// <param name="Param_NovoFormato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN para preservar o formato existente do buffer traseiro.</param>
			/// <param name="Param_SwapChainFlags">Uma combinação de CA_DXGI_SWAP_CHAIN_FLAG- digitado valores que são combinados usando um bitwise ou operação. O valor resultante especifica opções para o comportamento da cadeia de swaps</param>
			CarenResult AlterarTamanhoBuffers(UInt32 Param_NumeroBuffers, UInt32 Param_Largura, UInt32 Param_Altura, Enumeracoes::CA_DXGI_FORMATO Param_NovoFormato, Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags);

			/// <summary>
			/// (ResizeTarget) - Redimensiona a meta de saída.
			/// </summary>
			/// <param name="Param_NovaDesc">A estrutura CA_DXGI_MODE_DESC que descreve o modo, que especifica a nova largura, altura, formato e taxa de atualização do alvo. Se o formato for DXGI_FORMAT_UNKNOWN, o método (RedimensionarSaida)
			/// utilizara o formato existente. Recomendamos apenas que você use DXGI_FORMAT_UNKNOWN quando a cadeia de swap está em modo de tela cheia, pois este método não é seguro para o segmento.</param>
			CarenResult RedimensionarSaida(Estruturas::CA_DXGI_MODE_DESC^ Param_NovaDesc);

			/// <summary>
			/// (SetFullscreenState) - Define o estado de exibição para janelas ou tela cheia.
			/// </summary>
			/// <param name="Param_EstadoFullScreen">Um valor booleano que especifica se deve definir o estado de exibição para janelas ou tela cheia. VERDADE para tela cheia, e FALSO para janelas.</param>
			/// <param name="Param_MonitorSaida">Se você passar o TRUE para o parâmetro (Param_EstadoFullScreen) para definir o estado de exibição para tela cheia, você pode definir opcionalmente este parâmetro para um ponteiro para uma interface
			/// IDXGIOutput para o alvo de saída que contém a cadeia de swap. Se você definir este parâmetro para NULO, DXGI escolherá a saída com base no dispositivo da cadeia de swap e na colocação da janela de saída. Se você passar FALSE 
			/// para (Param_EstadoFullScreen), você deve definir este parâmetro para NULO.</param>
			CarenResult DefinirEstadoFullScreen(Boolean Param_EstadoFullScreen, ICarenDXGIOutput^ Param_MonitorSaida);
		};

		/// <summary>
		/// (IDXGISwapChain1) - Interface responsável por fornecer recursos de apresentação que são aprimorados a partir de IDXGISwapChain. Esses recursos de apresentação consistem em especificar 
		/// retângulos sujos e retângulo de rolagem para otimizar a apresentação.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma cadeia de troca DXGI.")]
		[Guid("CCB4AB47-075B-4441-A57A-ACB137C2AB00")]
		public interface class ICarenDXGISwapChain1 : ICarenDXGISwapChain
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
			/// (GetBackgroundColor) - Recupera a cor de fundo da cadeia de swaps.
			/// </summary>
			/// <param name="Param_Out_Cor">Retorna uma estrutura que contém as informações de cor do Background.</param>
			CarenResult ObterCorBackground([Out] CA_DXGI_RGBA^% Param_Out_Cor);

			/// <summary>
			/// (GetCoreWindow) - Recupera o objeto CoreWindow subjacente para este objeto de cadeia de swap.
			/// </summary>
			/// <param name="Param_RIID">Um ponteiro para o identificador globalmente único(GUID) do objeto CoreWindow que é referenciado pelo parâmetro Param_Out_CoreWindow.</param>
			/// <param name="Param_Out_CoreWindow">Retorna o ponteiro do objeto para a CoreWindow. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult ObterCoreWindow(String^ Param_RIID, ICaren^ Param_Out_CoreWindow);

			/// <summary>
			/// (GetDesc1) - Obtém uma descrição da cadeia de swaps.
			/// </summary>
			/// <param name="Param_Out_Desc">Retorna uma estrutura que contém a descrição da cadeia de Swap.</param>
			CarenResult ObterDescricao1([Out] CA_DXGI_SWAP_CHAIN_DESC1^% Param_Out_Desc);

			/// <summary>
			/// (GetFullscreenDesc) - Obtém uma descrição de uma cadeia de troca em tela cheia.
			/// </summary>
			/// <param name="Param_Out_DescFullScreenSwap">Retorna uma estrutura que contém a descrição no modo FullScreen na cadeia de Swap.</param>
			CarenResult ObterDescricaoFullScreen([Out] CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^% Param_Out_DescFullScreenSwap);

			/// <summary>
			/// (GetHwnd) - Recupera o HWND subjacente para este objeto de cadeia de swap.
			/// </summary>
			/// <param name="Param_Out_HWND">Retorna um ponteiro para o HWND do objeto de cadeia de Swap.</param>
			CarenResult ObterHwnd([Out] IntPtr% Param_Out_HWND);

			/// <summary>
			/// (GetRestrictToOutput) - Obtém a saída (o monitor de exibição) ao qual você pode restringir o conteúdo de uma operação atual.
			/// </summary>
			/// <param name="Param_Out_Saida">Um ponteiro para um buffer que recebe um ponteiro para a interface IDXGIOutput para a saída de restrição.  Um aplicativo passa este ponteiro para 
			/// ICarenDXGIOutput em uma chamada para o ICarenDXGIFactory2::CreateSwapChainForHwnd, ICarenDXGIFactory2::CreateSwapChainForCoreWindow, ou ICarenDXGIFactory2::CreateSwapChainForComposition</param>
			CarenResult ObterSaidaParaRestricao([Out] ICarenDXGIOutput^% Param_Out_Saida);

			/// <summary>
			/// (GetRotation) - Obtém a rotação dos buffers traseiros para a cadeia de swaps.
			/// </summary>
			/// <param name="Param_Out_Rotacao">Retorna uma enumeração que define a rotação do Buffer Traseiro(BackBuffer).</param>
			CarenResult ObterRotacao([Out] CA_DXGI_MODE_ROTATION% Param_Out_Rotacao);

			/// <summary>
			/// (IsTemporaryMonoSupported) - Determina se uma cadeia de swap suporta "mono temporário".
			/// </summary>
			/// <param name="Param_Out_Suporte">Retorna um Booleano que define o suporte ao mono.</param>
			CarenResult IsSuporteMonoTemporario([Out] Boolean% Param_Out_Suporte);

			/// <summary>
			/// (Present1) - Apresenta um Frame a tela de exibição.
			/// </summary>
			/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
			/// <param name="Param_FlagsApresentacao">Um valor inteiro que contém opções de apresentação em cadeia de swaps.</param>
			/// <param name="Param_ParametrosApresentacao">uma estrutura CA_DXGI_PRESENT_PARAMETERS que descreve retângulos atualizados e rolar informações do quadro para apresentar.</param>
			CarenResult Apresentar1(UInt32 Param_IntervaloSincronizacao, CA_DXGI_PRESENT Param_FlagsApresentacao, CA_DXGI_PRESENT_PARAMETERS^ Param_ParametrosApresentacao);

			/// <summary>
			/// (SetBackgroundColor) - Muda a cor de fundo da cadeia de swaps.
			/// </summary>
			/// <param name="Param_Cor">A nova cor para o Background do buffer traseiro.</param>
			CarenResult DefinirCorBackground(CA_DXGI_RGBA^ Param_Cor);

			/// <summary>
			/// (SetRotation) - Define a rotação dos buffers de volta para a cadeia de swap.
			/// </summary>
			/// <param name="Param_Rotacao">A nova rotação dos Buffers Traseiro(BackBuffers).</param>
			CarenResult DefinirRotacao(CA_DXGI_MODE_ROTATION Param_Rotacao);
		};

		/// <summary>
		/// (IDXGISwapChain2) - Interface responsável por estender ICarenDXGISwapChain1 com métodos para suportar o dimensionamento de 
		/// buffer de swap de volta e cadeias de swap de latência mais baixa.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma cadeia de troca DXGI.")]
		[Guid("8F2F18C5-E079-4037-8A55-99015A592023")]
		public interface class ICarenDXGISwapChain2 : ICarenDXGISwapChain1
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
			/// (GetFrameLatencyWaitableObject) - Retorna uma Handle aguardavel que sinaliza quando o adaptador DXGI terminar de apresentar um novo quadro.
			/// O Windows 8.1 introduz novas APIs que permitem renderização de menor latência esperando até que o quadro anterior seja apresentado ao display antes de desenhar o 
			/// quadro seguinte. Para usar este método, primeiro crie a cadeia de swap DXGI com o conjunto de bandeiras CA_DXGI_SWAP_CHAIN_FLAG::CA_DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT, 
			/// em seguida, ligue para ObterFrameLatencyWaitableObject para recuperar a handle aguardavel. Chame o método ICarenWindowsEvent::AguardarObjetoUnicoEx para sincronizar a 
			/// renderização de cada novo quadro com o final do quadro anterior. Para cada quadro que renderiza, o aplicativo deve esperar por essa alça antes de iniciar qualquer operação 
			/// de renderização.
			/// </summary>
			/// <param name="Param_Out_HandleEvento">Recebe a interface que gerencia a Handle aguardavel.</param>
			CarenResult ObterFrameLatencyWaitableObject([Out] ICarenWindowsEvent^% Param_Out_HandleEvento);

			/// <summary>
			/// (GetMatrixTransform) - Obtém a matriz de transformação que será aplicada a uma cadeia de troca de composição no proximo (Present).
			/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel,
			/// que pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
			/// Os métodos ObterMatrixTransform e DefinirMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
			/// Apenas elementos simples de escala/tradução na matriz são permitidos  a chamada falhará se a matriz contiver elementos de distorção/rotação.
			/// </summary>
			/// <param name="Param_Out_Matriz_32"></param>
			CarenResult ObterMatrixTransform([Out] CA_DXGI_MATRIX_3X2_F^% Param_Out_Matriz_32);
		
			/// <summary>
			/// (GetMaximumFrameLatency) - Obtém o número de quadros que a cadeia de swap pode enfileirar para renderização.
			/// </summary>
			/// <param name="Param_Out_LatenciaMaxima">Recebe o número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Esse valor é 1 por padrão, 
			/// mas deve ser definido para 2 se a cena demorar mais do que leva para uma atualização vertical (normalmente cerca de 16ms) para desenhar.</param>
			CarenResult ObterMaximumFrameLatency([Out] UInt32% Param_Out_LatenciaMaxima);
		
			/// <summary>
			/// (GetSourceSize) - Obtém a região de origem é usada para a cadeia de swap.
			/// Use o (ObterSourceSize) para obter a parte da cadeia de swap da qual o sistema operacional apresenta. O retângulo de origem é sempre definido pela região 
			/// [0, 0, Largura, Altura]. Use o (DefinirSourceSize) para definir esta parte da cadeia de swap.
			/// </summary>
			/// <param name="Param_Out_Largura">Recebe a largura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 até a largura geral da cadeia de swap.</param>
			/// <param name="Param_Out_Altura">Recebe a altura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 a altura global da cadeia de swap.</param>
			CarenResult ObterSourceSize([Out] UInt32% Param_Out_Largura, [Out] UInt32% Param_Out_Altura);
		
			/// <summary>
			/// (SetMatrixTransform) - Define a matriz de transformação que será aplicada a uma cadeia de troca de composição no próximo (Present).
			/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel, que 
			/// pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
			/// Os métodos ObterMatrixTransform e DefinirMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
			/// Apenas elementos simples de escala/tradução na matriz são permitidos  a chamada falhará se a matriz contiver elementos de distorção/rotação.
			/// </summary>
			/// <param name="Param_Matriz_32">A matriz de transformação para usar para o dimensionamento e tradução em cadeia de swap. Esta função só pode ser usada com cadeias de troca de 
			/// composição(Composition) criadas por ICarenDXGIFactory2::CreateSwapChainForComposition. Somente componentes de escala e tradução são permitidos na matriz.</param>
			CarenResult DefinirMatrixTransform(CA_DXGI_MATRIX_3X2_F^ Param_Matriz_32);
		
			/// <summary>
			/// (SetMaximumFrameLatency) - Define o número de quadros que a cadeia de swap pode fazer fila para renderização.
			/// </summary>
			/// <param name="Param_MaximoBackBufferLatencia">O número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Este valor é 1 por padrão.</param>
			CarenResult DefinirMaximumFrameLatency(UInt32 Param_MaximoBackBufferLatencia);
		
			/// <summary>
			/// (SetSourceSize) - Define a região de origem para ser usada para a cadeia de swap.
			/// Use o DefinirSourceSize para especificar a parte da cadeia de swap da qual o sistema operacional apresenta. Isso permite um redimensionamento eficaz sem chamar o método 
			/// (ICarenDXGISwapChain::AlterarTamanhoBuffers) que é mais caro. Antes do Windows 8.1, ligar para ICarenDXGISwapChain::AlterarTamanhoBuffers era a única maneira de 
			/// redimensionar a cadeia de swap. O retângulo de origem é sempre definido pela região [0, 0, Largura, Altura].
			/// </summary>
			/// <param name="Param_Largura">Largura de fonte para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à largura global 
			/// da cadeia de swap.</param>
			/// <param name="Param_Altura">Altura de origem para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à altura global da 
			/// cadeia de swap.</param>
			CarenResult DefinirSourceSize(UInt32 Param_Largura, UInt32 Param_Altura);
		};

		/// <summary>
		/// (IDXGISwapChain3) - Interface responsável por estender ICarenDXGISwapChain2 com métodos para suportar obter o índice do 
		/// buffer traseiro atual da cadeia de swap e suporte para espaço de cores.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma cadeia de troca DXGI.")]
		[Guid("6C400DD0-14B9-42E7-AF28-86DB32D2CDE3")]
		public interface class ICarenDXGISwapChain3 : ICarenDXGISwapChain2
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
			/// (CheckColorSpaceSupport) - Verifica o suporte da cadeia de swap para espaço de cores.
			/// </summary>
			/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE que especifica o tipo de espaço de cor para verificar o suporte.</param>
			/// <param name="Param_Out_ColorSpaceSuporte">Recebe Zero ou mais bandeiras da enumeração CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG são combinados usando uma operação ou 
			/// bitwise. O valor resultante especifica opções de suporte ao espaço colorido.</param>
			CarenResult ChecarSuporteEspacoCores(CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace, [Out] CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG% Param_Out_ColorSpaceSuporte);

			/// <summary>
			/// (GetCurrentBackBufferIndex) - Obtém o índice do buffer atual da cadeia de swap.
			/// </summary>
			/// <param name="Param_Out_IndexBackBuffer">Retorna o indice do buffer traseiro(BackBuffer) atual.</param>
			CarenResult ObterIndexBackBufferAtual([Out] UInt32% Param_Out_IndexBackBuffer);

			/// <summary>
			/// (ResizeBuffers1) - Altera o tamanho do buffer traseiro da cadeia de swap, formato e número de buffers, onde a cadeia de swap foi criada usando uma fila de 
			/// comando D3D12 como um dispositivo de entrada. Isso deve ser chamado quando a janela de aplicação for redimensionada.
			/// </summary>
			/// <param name="Param_CountBuffer">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e frontais). Este número pode ser diferente do número de 
			/// buffers com os quais você criou a cadeia de swap. Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o 
			/// número existente de buffers na cadeia de swap. Você não pode especificar menos de dois buffers para o modelo de apresentação flip.</param>
			/// <param name="Param_Largura">A nova largura do buffer traseiro. Se você especificar zero, o DXGI usará a largura da área do cliente da janela de destino. Você não pode 
			/// especificar a largura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
			/// <param name="Param_Altura">A nova altura do tampão traseiro. Se você especificar zero, o DXGI usará a altura da área do cliente da janela de destino. Você não pode 
			/// especificar a altura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
			/// <param name="Param_Formato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN preservar o formato existente do buffer traseiro. O modelo 
			/// de apresentação flip suporta um conjunto mais restrito de formatos do que o modelo de transferência de bit-block (bitblt).</param>
			/// <param name="Param_SwapChainFlags">Uma combinação de valores da enumeração CA_valoresDXGI_SWAP_CHAIN_FLAG que são combinados usando uma operação ou bitwise. O valor 
			/// resultante especifica opções para comportamento em cadeia de swap.</param>
			/// <param name="Param_ArrayNodeMask">Uma matriz de UInt32, de tamanho total Param_CountBuffer, onde o valor indica em qual nó o buffer traseiro deve ser criado. Buffers 
			/// criados usando AlterarTamanhoBuffers1 com um conjunto (Param_ArrayNodeMask) não-nulo são visíveis para todos os nós.</param>
			/// <param name="Param_ArrayD3D12CommandQueue">Uma série de filas de comando (ID3D12CommandQueue), de tamanho total Param_CountBuffer. Cada fila fornecida deve coincidir com a 
			/// máscara de nó de criação correspondente especificada na matriz Param_ArrayNodeMask. Quando o (ICarenDXGISwapChain::Apresentar) é chamado, além de girar para o próximo 
			/// buffer para o próximo quadro, a cadeia de swap também girará através dessas filas de comando. Isso permite que o aplicativo controle qual fila requer sincronização para 
			/// uma determinada operação presente.</param>
			CarenResult AlterarTamanhoBuffers1(
				UInt32 Param_CountBuffer,
				UInt32 Param_Largura,
				UInt32 Param_Altura,
				CA_DXGI_FORMATO Param_Formato,
				CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags,
				cli::array<UInt32>^ Param_ArrayNodeMask,
				cli::array<ICaren^>^ Param_ArrayD3D12CommandQueue);

			/// <summary>
			/// (SetColorSpace1) - Define o espaço de cores usado pela cadeia de swap.
			/// </summary>
			/// <param name="Param_ColorSpace">Um valor de CA_DXGI_COLOR_SPACE_TYPE que especifica o espaço de cores para definir.</param>
			CarenResult DefinirEspacoCores1(CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace);
		};

		/// <summary>
		/// (IDXGISwapChain4) - Interface responsável por expor um único método para definir metadados de vídeo.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma cadeia de troca DXGI.")]
		[Guid("BD3F55DE-853A-4B26-8824-F93B8184C6C8")]
		public interface class ICarenDXGISwapChain4 : ICarenDXGISwapChain3
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
			/// (SetHDRMetaData) - Este método estabelece metadados de cabeçalho High Dynamic Range (HDR) e Wide Color Gamut (WCG).
			/// </summary>
			/// <param name="Param_MetadataType">Especifica um membro da enumeração CA_DXGI_HDR_METADATA_TYPE.</param>
			/// <param name="Param_Size">Especifica o tamanho do (Param_Metadata), em bytes.</param>
			/// <param name="Param_Metadata">Especifica um ponteiro vazio que faz referência aos metadados, se ele existe.</param>
			CarenResult DefinirHDRMetadata(
				CA_DXGI_HDR_METADATA_TYPE Param_MetadataType,
				UInt32 Param_Size,
				ICaren^ Param_Metadata);
		};

		/// <summary>
		/// (IDXGIFactory) - Interface responsável por implementar métodos para gerar objetos DXGI (que lidam com transições de tela cheia).
		/// Como você pode criar um dispositivo Direct3D sem criar uma cadeia de swap, você pode precisar recuperar a fábrica que é usada
		/// para criar o dispositivo para criar uma cadeia de swap. Você pode solicitar a interface ICarenDXGIDevice do dispositivo Direct3D
		/// e, em seguida, usar o método ICarenDXGIObject::ObterPaiObjeto para localizar a fábrica.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("CE36B162-C863-481D-91CF-496FE9300709")]
		public interface class ICarenDXGIFactory : ICarenDXGIObject
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
			/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
			/// </summary>
			/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
			/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
			CarenResult CriarAdaptadorSofware(IntPtr Param_ModuleHandle, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

			/// <summary>
			/// (CreateSwapChain) - Cria uma cadeia de swaps.
			/// [Começando com o Direct3D 11.1, recomendamos não usar mais o (CriarSwapChain) para criar uma cadeia de swaps. Em vez disso, use CriarSwapChainForHwnd, CriarSwapChainForCoreWindow, ou 
			/// CriarSwapChainForComposition dependendo de como você quer criar a cadeia de swap.]
			/// </summary>
			/// <param name="Param_Dispositivo3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. Para Direct3D 12 este é 
			/// um ponteiro para uma fila de comando direto(D3D12CommandQueue). Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_Desc">Uma estrutura CA_DXGI_SWAP_CHAIN_DESC para a descrição da cadeia de swap. Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_Out_SwapChain">Recebe um ponteiro para a interface do SwapChain.</param>
			CarenResult CriarSwapChain(ICaren^ Param_Dispositivo3D, CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc, [Out] ICarenDXGISwapChain^% Param_Out_SwapChain);

			/// <summary>
			/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
			/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
			/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
			/// </summary>
			/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
			/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
			CarenResult EnumerarAdaptadores(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

			/// <summary>
			/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
			/// </summary>
			/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
			CarenResult ObterWindowAssociation([Out] IntPtr% Param_HandleJanela);

			/// <summary>
			/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
			/// para tela cheia ou vice-versa).
			/// </summary>
			/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
			/// <param name="Param_Flags"></param>
			CarenResult CriarWindowAssociation(IntPtr Param_HandleJanela, CA_DXGI_MWA_FLAGS Param_Flags);
		};

		/// <summary>
		/// (IDXGIFactory1) - Interface responsável por implementar métodos para gerar objetos DXGI.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("1C0E40FA-10FD-4690-ACA8-9E44C7230934")]
		public interface class ICarenDXGIFactory1 : ICarenDXGIFactory
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
			/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
			/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
			/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
			/// </summary>
			/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
			/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
			CarenResult EnumerarAdaptadores1(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter1^% Param_Out_Adaptador);

			/// <summary>
			/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
			/// </summary>
			/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
			CarenResult Atual([Out] Boolean% Param_Out_Atual);
		};
	
		/// <summary>
		/// (IDXGIFactory2) - Interface responsável por incluir métodos para criar uma cadeia de swap de versão mais recente com mais recursos
		/// do que o ICarenDXGISwapChain e monitorar recursos 3D estereoscópicos.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("A9988070-4AB2-4F03-B4D9-2038F1602B34")]
		public interface class ICarenDXGIFactory2 : ICarenDXGIFactory1
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
			/// (CreateSwapChainForComposition) - Cria uma cadeia de swaps que você pode usar para enviar conteúdo Direct3D para a API de Composição Direta ou a estrutura Windows.UI.Xaml para compor em uma janela.
			/// </summary>
			/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
			/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
			/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
			/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.
			/// Você deve especificar o valor DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL no membro SwapEffect da CA_DXGI_SWAP_CHAIN_DESC1 porque o método (CriarSwapChainForComposition) suporta 
			/// apenas um modelo de apresentação de flip.
			/// Você também deve especificar o valor DXGI_SCALING_STRETCH no membro de Scale de CA_DXGI_SWAP_CHAIN_DESC1.</param>
			/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
			/// quiser restringir o conteúdo a uma meta de saída.
			/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Apresentar1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
			/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
			/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
			/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CriarSwapChainForComposition) cria.</param>
			CarenResult CriarSwapChainForComposition(
				ICaren^ Param_DispositivoDirect3D, 
				CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap, 
				ICarenDXGIOutput^ Param_SaidaRestrita, 
				[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

			/// <summary>
			/// (CreateSwapChainForCoreWindow) - Cria uma cadeia de swaps que está associada ao objeto CoreWindow para a janela de saída para a cadeia de swap.
			/// </summary>
			/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
			/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
			/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
			/// <param name="Param_CoreWindow">Um ponteiro para o objeto CoreWindow que está associado com a cadeia de swap que (CriarSwapChainForCoreWindow) cria.</param>
			/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput que a cadeia de swap é restrito. Se a cadeia de swaps for movida para uma saída diferente, 
			/// o conteúdo é preto. Você pode definir opcionalmente este parâmetro para uma meta de saída que usa DXGI_PRESENT_RESTRICT_TO_OUTPUT para restringir o conteúdo dessa saída. 
			/// Se você não definir este parâmetro para restringir o conteúdo em uma meta de saída, você pode defini-lo para NULO.</param>
			/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CriarSwapChainForCoreWindow) cria.</param>
			CarenResult CriarSwapChainForCoreWindow(
				ICaren^ Param_DispositivoDirect3D, 
				ICaren^ Param_CoreWindow, 
				CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap, 
				ICarenDXGIOutput^ Param_SaidaRestrita,
				[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

			/// <summary>
			/// (CreateSwapChainForHwnd) - Cria uma cadeia de swap que esteja associada a uma alça HWND à janela de saída para a cadeia de swaps.
			/// </summary>
			/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
			/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
			/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
			/// <param name="Param_Handle">A alça(HWND - HANDLE) que está associado com a cadeia de swap que (CriarSwapChainForHwnd) cria. Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
			/// <param name="Param_DescFullScreen">Uma estrutura CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC para a descrição de uma cadeia de swap de tela cheia. Você pode definir opcionalmente 
			/// este parâmetro para criar uma cadeia de swap de tela cheia. Configurá-lo para NULO para criar uma cadeia de swap em modo Janela.</param>
			/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
			/// quiser restringir o conteúdo a uma meta de saída.
			/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Apresentar1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
			/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
			/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
			/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CriarSwapChainForHwnd) cria.</param>
			CarenResult CriarSwapChainForHwnd(
				ICaren^ Param_DispositivoDirect3D,
				IntPtr Param_Handle,
				CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
				CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_DescFullScreen,
				ICarenDXGIOutput^ Param_SaidaRestrita,
				[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

			/// <summary>
			/// (GetSharedResourceAdapterLuid) - Identifica o adaptador no qual um objeto de recurso compartilhado foi criado.
			/// </summary>
			/// <param name="Param_HandleRecurso">Uma alça para um objeto de recurso compartilhado. O método ICarenDXGIResource1::CriarHandleCompartilhada devolve essa alça.</param>
			/// <param name="Param_Out_Luid">Retorna uma variavel que recebe um identificador localmente único(LUID). Valor que identifica o adaptador. Um CA_LUID é um valor de 64 bits 
			/// que é garantido para ser único apenas no sistema operacional em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema operacional seja 
			/// reiniciado.</param>
			CarenResult ObterRecursoCompartilhadoAdaptadorLuid(IntPtr Param_HandleRecurso, [Out] CA_LUID^% Param_Out_Luid);

			/// <summary>
			/// (IsWindowedStereoEnabled) - Determina se deve usar o modo estéreo.
			/// </summary>
			/// <param name="Param_Out_ModoEstereoHabilitado">Retorna um valor que indica se deve usar o modo estéreo. TRUE indica que você pode usar o modo estéreo; se não, FALSO.</param>
			CarenResult WindowedStereoHabilitado([Out] Boolean% Param_Out_ModoEstereoHabilitado);

			/// <summary>
			/// (RegisterOcclusionStatusEvent) - Registra-se para receber notificação de alterações no status de oclusão usando a sinalização do evento.
			/// </summary>
			/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status de oclusão. 
			/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
			/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::DesregistrarOcclusionStatus para cancelar o 
			/// registro do evento de notificação que (Param_Evento) especifica.</param>
			CarenResult RegistrarOcclusionStatusEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie);

			/// <summary>
			/// (RegisterOcclusionStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações do status de oclusão.
			/// </summary>
			/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração de status de oclusão.</param>
			/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
			/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::DesregistrarOcclusionStatus para cancelar o registro da mensagem 
			/// de notificação que (Param_WinMensagemCode) especifica.</param>
			CarenResult RegistrarOcclusionStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie);

			/// <summary>
			/// (RegisterStereoStatusEvent) - Registra-se para receber notificação de alterações no status estéreo usando a sinalização do evento.
			/// </summary>
			/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status do modo Stereo. 
			/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
			/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::DesregistrarStereoStatus para cancelar o 
			/// registro do evento de notificação que (Param_Evento) especifica.</param>
			CarenResult RegistrarStereoStatusEvent(ICarenWindowsEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie);

			/// <summary>
			/// (RegisterStereoStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações de status estéreo.
			/// </summary>
			/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração do modo Stereo.</param>
			/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
			/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::DesregistrarStereoStatus para cancelar o registro da mensagem 
			/// de notificação que (Param_WinMensagemCode) especifica.</param>
			CarenResult RegistrarStereoStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie);

			/// <summary>
			/// (UnregisterOcclusionStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status de oclusão muda.
			/// </summary>
			/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
			CarenResult DesregistrarOcclusionStatus(UInt32 Param_Cookie);

			/// <summary>
			/// (UnregisterStereoStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status estéreo muda.
			/// </summary>
			/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
			CarenResult DesregistrarStereoStatus(UInt32 Param_Cookie);
		};

		/// <summary>
		/// (IDXGIFactory3) - Interface responsável por implementar métodos para gerar objetos DXGI.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("8A65A0D9-5701-4A0A-9538-9FEE1A37F280")]
		public interface class ICarenDXGIFactory3 : ICarenDXGIFactory2
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
			/// (GetCreationFlags) - Recebe as bandeiras que foram usadas quando um objeto Microsoft DirectX Graphics Infrastructure (DXGI) foi criado.
			/// </summary>
			/// <param name="Param_Out_Flags">Retorna o flag utilizada na criação da fabrica(DXGIFactory).</param>
			CarenResult ObterFlagsCriacao([Out] UInt32% Param_Out_Flags);
		};

		/// <summary>
		/// (IDXGIFactory4) - Interface responsável por implementar métodos para gerar objetos DXGI.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("439EA390-CF3D-4BF5-9D92-BF9309A17105")]
		public interface class ICarenDXGIFactory4 : ICarenDXGIFactory3
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
			/// (EnumAdapterByLuid) - Enumera saídas do ICarenDXGIAdapter para o LUID especificado.
			/// </summary>
			/// <param name="Param_LUID">Um valor único que identifica o adaptador.</param>
			/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
			/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
			CarenResult EnumerarAdaptadoresPorLUID(CA_LUID^ Param_LUID, String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter);

			/// <summary>
			/// (EnumWarpAdapter) - Fornece um adaptador que pode ser fornecido a função D3D12CreateDevice para usar o renderizador WARP.
			/// </summary>
			/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
			/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
			CarenResult EnumerarWarpAdapter(String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter);
		};

		/// <summary>
		/// (IDXGIFactory5) - Interface responsável pot permitir que um único método verifque o suporte a displays de taxa de atualização variável.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("4F61D54D-CD2B-4EF3-811A-F841CE3B8ABA")]
		public interface class ICarenDXGIFactory5 : ICarenDXGIFactory4
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
			/// (CheckFeatureSupport) - Usado para verificar se há suporte ao recurso de hardware.
			/// </summary>
			/// <param name="Param_Recurso">Especifica um membro da CA_DXGI_FEATURE para consultar o suporte.</param>
			/// <param name="Param_SizeBuffer">O tamanho de Param_Ref_BufferDescFeature, em bytes.</param>
			/// <param name="Param_Ref_BufferDescFeature">Especifica um ponteiro para um buffer que será preenchido com dados que descrevem o suporte ao recurso.</param>
			CarenResult ChecarSuporteRecurso(CA_DXGI_FEATURE Param_Recurso, UInt32 Param_SizeBuffer, ICarenBuffer^% Param_Ref_BufferDescFeature);
		};

		/// <summary>
		/// (IDXGIFactory6) - Interface responsável por permitir que um único método enumere adaptadores gráficos com base em uma 
		/// determinada preferência de GPU.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("6104659D-9287-4C74-BF53-A0F16CC7BCFC")]
		public interface class ICarenDXGIFactory6 : ICarenDXGIFactory5
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
			/// (EnumAdapterByGpuPreference) - Enumera adaptadores gráficos com base em uma determinada preferência de GPU.
			/// </summary>
			/// <param name="Param_IndexAdaptador">O índice do adaptador para enumerar. Os índices estão por ordem da preferência especificada no CA_DXGI_GPU_PREFERENCE  por exemplo, 
			/// se CA_DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE for especificado, então o adaptador de maior desempenho está no índice 0, o segundo mais alto está no índice 1, e assim 
			/// por diante.</param>
			/// <param name="Param_PreferenciaGPU">A preferência da GPU pelo aplicativo</param>
			/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro Param_Out_Adaptador.</param>
			/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface ICarenDXGIAdapter do adaptador.</param>
			CarenResult EnumerarAdaptadorPorPreferenciaGPU(
				UInt32 Param_IndexAdaptador,
				CA_DXGI_GPU_PREFERENCE Param_PreferenciaGPU,
				String^ Param_RIID,
				ICaren^ Param_Out_Adaptador);
		};

		/// <summary>
		/// (IDXGIFactory7) - Interface responsável por permitir o registro de notificações para detectar alterações no estado de 
		/// enumeração do adaptador.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Representa uma fabrica que gera objetos DXGI.")]
		[Guid("FBC0D0DB-8007-4DE6-822A-1FCDA9B87334")]
		public interface class ICarenDXGIFactory7 : ICarenDXGIFactory6
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
			/// (RegisterAdaptersChangedEvent) - Registra-se para receber notificação de alterações sempre que o estado de enumeração do adaptador muda.
			/// </summary>
			/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento.</param>
			/// <param name="Param_Out_Cookie">Recebe um valor da chave para o evento registrado.</param>
			CarenResult RegistrarEventoModificacaoAdaptador(ICarenWindowsEvent^ Param_HandleEvento, [Out] UInt32% Param_Out_Cookie);

			/// <summary>
			/// (UnregisterAdaptersChangedEvent) - Cancela o registro do evento para parar de receber notificações quando o estado de enumeração do adaptador muda.
			/// </summary>
			/// <param name="Param_Cookie">O valor da chave do evento registrado para ser cancelado. Esse valor é obtido do método (RegistrarEventoModificacaoAdaptador).</param>
			CarenResult CancelarEventoModificacaoAdaptador(UInt32 Param_Cookie);
		};

		/// <summary>
		/// (IDXGIDevice) - Interface responsável por implementar uma classe derivada para objetos DXGI que produzem dados de imagem.
		/// A interface ICarenDXGIDevice foi projetada para uso por objetos DXGI que precisam de acesso a outros objetos DXGI. Esta interface 
		/// é útil para aplicativos que não usam o Direct3D para se comunicar com o DXGI. As funções do dispositivo de criação Direct3D 
		/// retornam um objeto do dispositivo Direct3D.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Classe derivada para objetos DXGI que poduzem dados de imagem.")]
		[Guid("097B7DAB-A49E-4644-9277-0566B7E80B30")]
		public interface class ICarenDXGIDevice : ICarenDXGIObject
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
			/// (CreateSurface)(Não é implementado) - Este método é usado internamente e você não deve chamá-lo diretamente em sua aplicação.
			/// </summary>
			CarenResult CreateSurface();

			/// <summary>
			/// (GetAdapter) - Retorna o adaptador para o dispositivo especificado.
			/// </summary>
			/// <param name="Param_Out_Adaptador">Retorna um ponteiro para a interface(ICarenDXGIAdapter) do adaptador.</param>
			CarenResult ObterAdaptador([Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

			/// <summary>
			/// (GetGPUThreadPriority) - Retorna a prioridade da Thread GPU.
			/// </summary>
			/// <param name="Param_Out_Prioridade">recebe um valor que indica a prioridade atual da Thread GPU. O valor será entre -7 e 7, inclusive, onde 0 representa prioridade normal.</param>
			CarenResult ObterPrioridadeThreadGPU([Out] int% Param_Out_Prioridade);

			/// <summary>
			/// (QueryResourceResidency) - Obtém o status de residência de uma série de recursos.
			/// As informações devolvidas pelo conjunto de argumentos (Param_Ref_StatusResidencia) descrevem o status de residência no momento em que o método 
			/// (ObterStatusResidenciaRecurso) foi chamado. 
			/// [O status de residência mudará constantemente.]
			/// Se você ligar para o método (ObterStatusResidenciaRecurso) durante um estado removido do dispositivo, o argumento (Param_Ref_StatusResidencia) devolverá 
			/// a bandeira CA_DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY.
			/// </summary>
			/// <param name="Param_ArrayRecursos">Um array que contém uma série de interfaces(ICarenDXGIResource) a serem obtido o status de residência.</param>
			/// <param name="Param_Ref_StatusResidencia">Um Array que vai conter o status de residência(ResidencyStatus) de cada recurso no parametro(Param_ArrayRecursos).</param>
			/// <param name="Param_QuantidadeRecursos">A quantidade de elementos no array de recursos.</param>
			CarenResult ObterStatusResidenciaRecurso(
				cli::array<ICarenDXGIResource^>^ Param_ArrayRecursos, 
				cli::array<CA_DXGI_RESIDENCY>^% Param_Ref_StatusResidencia, 
				UInt32 Param_QuantidadeRecursos);

			/// <summary>
			/// (SetGPUThreadPriority) - Define a prioridade da Thread GPU.
			/// </summary>
			/// <param name="Param_Prioridade">Um valor que especifica a prioridade necessária da Thread da GPU. Esse valor deve ser entre -7 e 7, inclusive, onde 0 representa 
			/// prioridade normal.</param>
			CarenResult DefinrPrioridadeThreadGPU(int Param_Prioridade);
		};

		/// <summary>
		/// (IDXGIDevice1) - Interface responsável por implementar uma classe derivada para objetos DXGI que produzem dados de imagem.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Classe derivada para objetos DXGI que poduzem dados de imagem.")]
		[Guid("9BB5D6A6-FDA0-4B27-A6A4-4738C5EEE438")]
		public interface class ICarenDXGIDevice1 : ICarenDXGIDevice
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
			/// (GetMaximumFrameLatency) - Obtém o número de quadros(Frames) que o sistema pode fazer fila para renderização.
			/// </summary>
			/// <param name="Param_Out_LatenciaMaxima">Esse valor é definido para o número de quadros que podem ser enfileirados para renderização. Esse valor está 
			/// inadimplente em 3, mas pode variar de 1 a 16.</param>
			CarenResult ObterLatenciaMaximaFrame([Out] UInt32% Param_Out_LatenciaMaxima);

			/// <summary>
			/// (SetMaximumFrameLatency) - Define o número de quadros que o sistema pode fazer fila para renderização.
			/// </summary>
			/// <param name="Param_LatenciaMaxima">O número máximo de quadros de buffer traseiro que um motorista pode fazer fila. O valor está inadimplente a 3, mas pode 
			/// variar de 1 a 16. Um valor de 0 redefinirá a latência ao padrão. Para dispositivos (per-head), esse valor é especificado por cabeça(Head).</param>
			CarenResult DefinirLatenciaMaximaFrame(UInt32 Param_LatenciaMaxima);
		};

		/// <summary>
		/// (IDXGIDevice2) - Interface responsável por implementar uma classe derivada para objetos DXGI que produzem dados de imagem. 
		/// A interface expõe métodos para bloquear o processamento da CPU até que a GPU complete o processamento e ofereça recursos 
		/// ao sistema operacional.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Classe derivada para objetos DXGI que poduzem dados de imagem.")]
		[Guid("2B7FD3A5-11B4-42F3-984F-5E5EF1E5DB31")]
		public interface class ICarenDXGIDevice2 : ICarenDXGIDevice1
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
			/// (EnqueueSetEvent) - Libera quaisquer comandos de renderização pendentes e define o objeto de evento especificado para o estado sinalizado depois de todos os 
			/// comandos de renderização previamente enviados completos.
			/// </summary>
			/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento. Todos os tipos de objetos de evento (manual-reset, auto-reset e assim por diante) são suportados. 
			/// A Handle deve ter a bandeira de direito de acesso (EVENT_MODIFY_STATE).</param>
			CarenResult EnqueueDefinirEvento(ICarenWindowsEvent^ Param_HandleEvento);

			/// <summary>
			/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos descartando seu conteúdo.
			/// </summary>
			/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
			/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
			/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
			CarenResult OfertarRecursos(
				UInt32 Param_QuantidadeRecursos,
				cli::array<ICarenDXGIResource^>^ Param_Recursos,
				CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade);

			/// <summary>
			/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice2::OfertarRecursos.
			/// </summary>
			/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Descartado) conjuntos de argumentos.</param>
			/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
			/// <param name="Param_Ref_Descartado">Uma matriz que recebe valores booleanos. Cada valor na matriz corresponde a um recurso no mesmo índice que o parâmetro 
			/// (Param_Recursos) especifica. O tempo de execução define cada valor booleano para TRUE se o conteúdo do recurso correspondente foi descartado e agora estiver 
			/// indefinido, ou para FALSE se o conteúdo antigo do recurso correspondente ainda estiver intacto. O chamador pode passar NULO, se o chamador pretende preencher 
			/// os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
			CarenResult RecuperarRecursos(
				Int32 Param_QuantidadeRecursos, 
				cli::array<ICarenDXGIResource^>^ Param_Recursos,
				cli::array<bool>^% Param_Ref_Descartado);
		};

		/// <summary>
		/// (IDXGIDevice3) - Interface responsável por implementar uma classe derivada para objetos DXGI que produzem dados de imagem
		/// A interface expõe um método para aparar o uso da memória gráfica pelo dispositivo DXGI.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Classe derivada para objetos DXGI que poduzem dados de imagem.")]
		[Guid("152B0A4D-1FDF-4C3D-A53D-CFD8D9E4F479")]
		public interface class ICarenDXGIDevice3 : ICarenDXGIDevice2
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
			/// (Trim) - Apara a memória gráfica alocada pelo dispositivo DXGI ICarenDXGIDevice3 em nome do aplicativo.
			/// Para aplicativos que renderizam com o DirectX, os drivers gráficos alocam periodicamente buffers de memória interna, a fim de acelerar as solicitações de 
			/// renderização subsequentes. Essas alocações de memória contam com o uso de memória do aplicativo para PLM e, em geral, levam ao aumento do uso da memória pelo 
			/// sistema geral.
			/// A partir do Windows 8.1, os aplicativos que renderizam com Direct2D e/ou Direct3D (incluindo interop CoreWindow e XAML) devem ligar para trim em resposta ao 
			/// (PLM suspend callback.). O tempo de execução Direct3D e o driver gráfico descartarão buffers de memória interna alocados para o aplicativo, reduzindo sua pegada 
			/// de memória.
			/// Semelhante ao ICarenD3D11DeviceContext::Flush, os aplicativos devem ligar para ICarenD3D11DeviceContext::ClearState antes de ligar para (Trim). ClearState limpa as 
			/// ligações de gasodutos Direct3D, garantindo que o Direct3D não tenha referências aos objetos Direct3D que você está tentando liberar.
			/// </summary>
			CarenResult Trim();
		};

		/// <summary>
		/// (IDXGIDevice4) - Interface responsável por fornecer métodos atualizados para oferecer e recuperar recursos.
		/// </summary>
		[CategoryAttribute("Interface DXGI")]
		[DescriptionAttribute("Classe derivada para objetos DXGI que poduzem dados de imagem.")]
		[Guid("4F4697D0-5D8E-4447-A77D-5B1E231E1A07")]
		public interface class ICarenDXGIDevice4 : ICarenDXGIDevice3
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
			/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos, incluindo tanto descartar o conteúdo quanto descomprometer a memória.
			/// </summary>
			/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
			/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
			/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
			/// <param name="Param_Flags">Especifica o DXGI_OFFER_RESOURCE_FLAGS.</param>
			CarenResult OfertarRecursos1(
				UInt32 Param_QuantidadeRecursos,
				cli::array<ICarenDXGIResource^>^ Param_Recursos,
				CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade,
				CA_DXGI_OFFER_RESOURCE_FLAGS Param_Flags);

			/// <summary>
			/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice4::OfertarRecursos1.
			/// </summary>
			/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Resultado) conjuntos de argumentos.</param>
			/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
			/// <param name="Param_Ref_Resultado">Yma matriz que recebe valores da enumeração CA_DXGI_RECLAIM_RESOURCE_RESULTS. Cada valor na matriz corresponde a um recurso 
			/// no mesmo índice que o parâmetro (Param_Recursos) especifica. O chamador pode passar em NULO, se o chamador pretende preencher os recursos com novos conteúdos, 
			/// independentemente de o conteúdo antigo ter sido descartado.</param>
			CarenResult RecuperarRecursos1(
				Int32 Param_QuantidadeRecursos,
				cli::array<ICarenDXGIResource^>^ Param_Recursos,
				cli::array<CA_DXGI_RECLAIM_RESOURCE_RESULTS>^% Param_Ref_Resultado);
		};
	}
}