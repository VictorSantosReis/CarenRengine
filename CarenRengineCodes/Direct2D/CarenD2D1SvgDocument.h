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
#include "CarenD2D1SvgPaint.h"
#include "CarenD2D1SvgPathData.h"
#include "CarenD2D1SvgPointCollection.h"
#include "CarenD2D1SvgStrokeDashArray.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um documento SVG.
/// </summary>
public ref class CarenD2D1SvgDocument : public ICarenD2D1SvgDocument
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SvgDocument).
	ID2D1SvgDocument* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SvgDocument();
	
	~CarenD2D1SvgDocument();


	//Conversões implicitas
public:
	static operator CarenD2D1SvgDocument^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1SvgDocument^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1SvgDocument();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1SvgDocument*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenD2D1SvgDocument::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenD2D1SvgDocument)
public:
	/// <summary>
	/// Cria um objeto de tinta que pode ser usado para definir as propriedades 'preenchimento' ou 'traçado'. 
	/// </summary>
	/// <param name="Param_PaintType">Especifica o tipo de objeto de tinta para criar.</param>
	/// <param name="Param_Cor">A cor usada se o (Param_PaintType) estiver D2D1_SVG_PAINT_TYPE_COLOR.</param>
	/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
	/// <param name="Param_Out_Paint">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o objeto de pintura criado.</param>
	virtual CarenResult CreatePaint(
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
	virtual CarenResult CreatePathData(
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
	virtual CarenResult CreatePointCollection(
	cli::array<CA_D2D1_POINT_2F^>^ Param_Points,
	UInt32 Param_QuantidadePoints,
	[Out] ICarenD2D1SvgPointCollection^% Param_Out_PointCollection);

	/// <summary>
	/// Cria um objeto de matriz de traço que pode ser usado para definir a propriedade stroke-dasharray. 
	/// </summary>
	/// <param name="Param_Dashes">Uma série de traços(dashes).</param>
	/// <param name="Param_QuantidadeDashes">A quantidade de dashes no array (Param_Dashes).</param>
	/// <param name="Param_Out_StrokeDashArray">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o objeto criado.</param>
	virtual CarenResult CreateStrokeDashArray(
	cli::array<CA_D2D1_SVG_LENGTH^>^ Param_Dashes,
	UInt32 Param_QuantidadeDashes,
	[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_StrokeDashArray);

	/// <summary>
	/// Deserializa uma subarvore do Stream. O fluxo deve ter apenas um elemento raiz, mas esse elemento raiz não precisa ser um elemento 'svg'. O elemento de saída não está inserido nesta árvore de documento. 
	/// </summary>
	/// <param name="Param_InputXmlStream">Um fluxo de entrada contendo a subárvore SVG XML.</param>
	/// <param name="Param_Out_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subárvore. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult Deserialize(
	ICarenStream^ Param_InputXmlStream,
	ICaren^ Param_Out_SvgElementSubTree);

	/// <summary>
	/// Obtém o elemento SVG com o ID especificado. 
	/// </summary>
	/// <param name="Param_Id">ID do elemento para recuperar.</param>
	/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento correspondente ao ID especificado. Se não for encontrado, esse valor será NULO. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult FindElementById(
	String^ Param_Id,
	ICaren^ Param_Out_SvgElement);

	/// <summary>
	/// Obtém o elemento raiz do documento. 
	/// </summary>
	/// <param name="Param_Out_SvgElementRoot">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento raiz do documento. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetRoot(ICaren^ Param_Out_SvgElementRoot);

	/// <summary>
	/// Retorna o tamanho do viewport inicial. 
	/// </summary>
	/// <param name="Param_Out_Size">Retorna o tamanho do viewport inicial</param>
	virtual void GetViewportSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size);

	/// <summary>
	/// Serializa um elemento e sua subárvore para XML. O XML de saída é codificado como UTF-8.
	/// </summary>
	/// <param name="Param_OutputXmlStream">Um fluxo de saída para conter a subárvore SVG XML.</param>
	/// <param name="Param_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subarvore. Se for NULO, todo o documento será serializado.</param>
	virtual CarenResult Serialize(
	ICarenStream^ Param_OutputXmlStream,
	ICaren^ Param_SvgElementSubTree);

	/// <summary>
	/// Define o elemento raiz do documento. 
	/// </summary>
	/// <param name="Param_SvgElementRoot">Uma interface(ICarenD2D1SvgElement) que define o novo elemento raiz do documento.</param>
	virtual CarenResult SetRoot(ICaren^ Param_SvgElementRoot);

	/// <summary>
	/// Define o tamanho da configuração inicial. 
	/// </summary>
	/// <param name="Param_ViewportSize">O tamanho da viewport.</param>
	virtual CarenResult SetViewportSize(CA_D2D1_SIZE_F^ Param_ViewportSize);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};