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
#include "CarenD2D1BlendTransform.h"
#include "CarenD2D1BorderTransform.h"
#include "CarenD2D1BoundsAdjustmentTransform.h"
#include "CarenD2D1ColorContext.h"
#include "CarenD2D1Effect.h"
#include "CarenD2D1OffsetTransform.h"
#include "CarenD2D1ResourceTexture.h"
#include "CarenD2D1TransformNode.h"
#include "CarenD2D1VertexBuffer.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por fornecer métodos de fábrica e outro gerenciamento de estado para efetuar e transformar autores.
/// </summary>
public ref class CarenD2D1EffectContext : public ICarenD2D1EffectContext
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1EffectContext).
	ID2D1EffectContext* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	CarenD2D1EffectContext();
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	~CarenD2D1EffectContext();

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


	//Métodos da interface(ICarenD2D1EffectContext)
public:
	/// <summary>
	/// Verifica se um recurso opcional é suportado pelo dispositivo D3D.
	/// </summary>
	/// <param name="Param_Feature">O recurso para consultar suporte.</param>
	/// <param name="Param_Out_FeatureSupportData">Uma estrutura indicando informações sobre como ou se o recurso é suportado.</param>
	/// <param name="Param_SizeFeatureData">O tamanho do parâmetro (Param_Out_FeatureSupportData).</param>
	virtual CarenResult CheckFeatureSupport(
	CA_D2D1_FEATURE Param_Feature,
	[Out] ICaren^% Param_Out_FeatureSupportData,
	UInt32 Param_SizeFeatureData);

	/// <summary>
	/// Cria uma mistura que pode ser inserida em um gráfico de transformação. 
	/// </summary>
	/// <param name="Param_NumeroEntradas">O número de entradas na transformação de mistura.</param>
	/// <param name="Param_DescBlend">Descreve a transformação de mistura que deve ser criada.</param>
	/// <param name="Param_Out_BlendTransform">Retorna uma interface para a transformação da mistura(blend).</param>
	virtual CarenResult CreateBlendTransform(
	UInt32 Param_NumeroEntradas,
	CA_D2D1_BLEND_DESCRIPTION^ Param_DescBlend,
	[Out] ICarenD2D1BlendTransform^% Param_Out_BlendTransform);

	/// <summary>
	/// Cria uma transformação que estende sua entrada infinitamente em todas as direções, com base na passada no modo de extensão.
	/// </summary>
	/// <param name="Param_ExtendModeX">O modo de extensão na direção do eixo X.</param>
	/// <param name="Param_ExtendModeY">O modo de extensão na direção do eixo Y.</param>
	/// <param name="Param_Out_BorderTransform">Retorna uma interface para a transformação devolvida.</param>
	virtual CarenResult CreateBorderTransform(
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
	virtual CarenResult CreateBoundsAdjustmentTransform(
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
	virtual CarenResult CreateColorContext(
	CA_D2D1_COLOR_SPACE Param_EspacoCor,
	ICarenBuffer^ Param_Profile,
	UInt32 Param_SizeProfileBuffer,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

	/// <summary>
	/// Cria um contexto de cor carregando-o a partir do nome de arquivo especificado. Os bytes de perfil são o conteúdo do arquivo especificado pelo (Param_UrlFilename). 
	/// </summary>
	/// <param name="Param_UrlFilename">O caminho para o arquivo contendo os bytes de perfil para inicializar o contexto de cores.</param>
	/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
	virtual CarenResult CreateColorContextFromFilename(
	String^ Param_UrlFilename,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext);

	/// <summary>
	/// Cria um contexto de cores a partir de um ICarenWICColorContext. O espaço D2D1ColorContext do contexto resultante varia.
	/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado 
	/// para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
	/// </summary>
	/// <param name="Param_WicColorContext">Um (ICarenWICColorContext) para inicializar o contexto de cores.</param>
	/// <param name="Param_Out_ColorContext">Retorna um ponteiro para a interface(ICarenD2D1ColorContext) como novo objeto de conexto de cor.</param>
	virtual CarenResult CreateColorContextFromWicColorContext(
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
	virtual CarenResult CreateEffect(
	String^ Param_IdEfeito,
	[Out] ICarenD2D1Effect^% Param_Out_Efeito);

	/// <summary>
	/// Cria e devolve uma transformação Offset.
	/// Uma transformação offset é usada para compensar um bitmap de entrada sem ter que inserir um passe de renderização. Uma transformação offset é automaticamente inserida por 
	/// uma transformação Affine se a transformação for avaliada em uma transformação alinhada a pixels.
	/// </summary>
	/// <param name="Param_Offset">O valor de deslocamento.</param>
	/// <param name="Param_Out_Transform">Retorna um ponteiro da interface(ICarenD2D1OffsetTransform) para um objeto de transformação Offset.</param>
	virtual CarenResult CreateOffsetTransform(
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
	virtual CarenResult CreateResourceTexture(
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
	virtual CarenResult CreateTransformNodeFromEffect(
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
	virtual CarenResult CreateVertexBuffer(
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
	virtual CarenResult FindResourceTexture(
	String^ Param_IdRecurso,
	[Out] ICarenD2D1ResourceTexture^% Param_Out_RecursoTextura);

	/// <summary>
	/// Encontra o buffer de vértice dado se ele já foi criado com ICarenD2D1EffectContext::CreateVertexBuffer com o mesmo GUID. 
	/// </summary>
	/// <param name="Param_IdRecurso">A identificação única que identifica o buffer de vértice.</param>
	/// <param name="Param_Out_VertexBuffer">Retorna um ponteiro para a interface(ICarenD2D1VertexBuffer) do buffer de vértice devolvido que pode ser usado como recurso 
	/// em um efeito Direct2D.</param>
	virtual CarenResult FindVertexBuffer(
	String^ Param_IdRecurso,
	[Out] ICarenD2D1VertexBuffer^% Param_Out_VertexBuffer);

	/// <summary>
	/// Obtém o mapeamento da unidade que um efeito usará para propriedades que podem estar em pontos por polegada (Dpi) ou pixels.
	/// Se o D2D1_UNIT_MODE for D2D1_UNIT_MODE_PIXELS, tanto o DPI_X quanto o DPI_Y serão definidos como 96.
	/// </summary>
	/// <param name="Param_Out_DpiX">O DPI no eixo X.</param>
	/// <param name="Param_Out_DpiY">O DPI no eixo Y.</param>
	virtual void GetDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY);

	/// <summary>
	/// Isso indica o nível máximo de recurso da lista fornecida que é suportada pelo dispositivo. Se nenhum dos níveis fornecidos for suportado, então esta API falhará com 
	/// D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES. 
	/// </summary>
	/// <param name="Param_NiveisRecurso">Os níveis de recurso fornecidos pelo aplicativo.</param>
	/// <param name="Param_QuantidadeNiveis">A contagem de níveis de recursos fornecidos pelo aplicativo</param>
	/// <param name="Param_Out_NivelRecursoMaximo">O nível máximo de recurso da lista (Param_NiveisRecurso), que é suportado pelo dispositivo D2D.</param>
	virtual CarenResult GetMaximumSupportedFeatureLevel(
	cli::array<CA_D3D_NIVEL_RECURSO>^ Param_NiveisRecurso,
	UInt32 Param_QuantidadeNiveis,
	[Out] CA_D3D_NIVEL_RECURSO% Param_Out_NivelRecursoMaximo);

	/// <summary>
	/// Indica se a precisão do buffer é suportada pelo dispositivo Direct2D subjacente.
	/// </summary>
	/// <param name="Param_BufferPrecision">A precisão do buffer para verificar.</param>
	/// <param name="Param_Out_Suporte">Retorna TRUE se a precisão do buffer for suportada. Retorna FALSE se a precisão do buffer não for suportada.</param>
	virtual void IsBufferPrecisionSupported(
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	[Out] Boolean% Param_Out_Suporte);

	/// <summary>
	/// Realiza um teste para ver se o shader fornecido está carregado.
	/// </summary>
	/// <param name="Param_ShaderId">A identificação única que identifica o sombreador.</param>
	/// <param name="Param_Out_Loaded">Retorna TRUE se o shader tiver sido carregado. Retorna FALSE se o shader não está carregado.</param>
	virtual void IsShaderLoaded(
	String^ Param_ShaderId,
	[Out] Boolean% Param_Out_Loaded);

	/// <summary>
	/// Carrega o sombreador dado pelo seu ID único. Carregar o sombreador várias vezes é ignorado. Quando o sombreador é carregado, ele também é entregue ao motorista 
	/// para JIT, se ainda não foi. O sombreador especificado deve ser compilado, não em código HLSL bruto.
	/// </summary>
	/// <param name="Param_IdRecurso">A identificação única que identifica o sombreador.</param>
	/// <param name="Param_ShaderBuffer">O buffer que contém o sombreador para registrar.</param>
	/// <param name="Param_ShaderBufferSize">O tamanho do Buffer em bytes.</param>
	virtual CarenResult LoadComputeShader(
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
	virtual CarenResult LoadPixelShader(
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
	virtual CarenResult LoadVertexShader(
	String^ Param_IdRecurso,
	ICarenBuffer^ Param_ShaderBuffer,
	UInt32 Param_ShaderBufferSize);
};