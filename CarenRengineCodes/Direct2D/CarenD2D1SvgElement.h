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
#include "CarenD2D1SvgElement.h"
#include "CarenD2D1SvgAttribute.h"
#include "CarenD2D1SvgPaint.h"
#include "CarenD2D1SvgStrokeDashArray.h"
#include "CarenD2D1SvgPointCollection.h"
#include "CarenD2D1SvgPathData.h"
#include "CarenD2D1SvgDocument.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar todos os elementos SVG.
/// </summary>
public ref class CarenD2D1SvgElement : public ICarenD2D1SvgElement
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SvgElement).
	ID2D1SvgElement* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SvgElement();

	~CarenD2D1SvgElement();


	//Conversões implicitas
public:
	static operator CarenD2D1SvgElement^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1SvgElement^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1SvgElement();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1SvgElement*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenD2D1SvgElement::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1SvgElement)
public:
	/// <summary>
	/// Anexa um elemento à lista de childs. Se o elemento já tiver um pai, ele será removido deste pai como parte da operação de anexação.
	/// </summary>
	/// <param name="Param_NewChild">O elemento para anexar.</param>
	virtual CarenResult AppendChild(ICarenD2D1SvgElement^ Param_NewChild);

	/// <summary>
	/// Cria um elemento a partir de um nome de etiqueta. O elemento é anexado à lista de childs. 
	/// </summary>
	/// <param name="Param_TagName">O nome da novo child. Uma sequência vazia é interpretada como um elemento de conteúdo de texto.</param>
	/// <param name="Param_Out_NewChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o novo child.</param>
	virtual CarenResult CreateChild(
	String^ Param_TagName,
	[Out] ICarenD2D1SvgElement^% Param_Out_NewChild);

	/// <summary>
	/// Recebe um atributo deste elemento como uma string.
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Tipo">O tipo de String.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	/// <param name="Param_SizeValor">O tamanho do valor em bytes.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE  Param_Tipo,
	[Out] String^% Param_Out_Valor,
	UInt32 Param_SizeValor);

	/// <summary>
	/// Obtém um atributo deste elemento como um tipo de POD. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Tipo">O tipo POD do valor.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICaren) que contém o ponteiro para o objeto(void*). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <param name="Param_SizeValorEmBytes">O tamanho do valor em bytes.</param>
	virtual CarenResult GetAttributeValue(
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
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	String^ Param_RiidInterface,
	ICaren^ Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como um float. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] float% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como uma string. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_COLOR_F^% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para obter o valor das propriedades de regra de preenchimento ou regra de clipe. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_FILL_MODE% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_DISPLAY% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para obter o valor da propriedade de transbordamento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_OVERFLOW% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de join de linha. Este método pode ser usado para obter o valor da propriedade stroke-linejoin. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_LINE_JOIN% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para obter o valor da propriedade stroke-linecap. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_LINE_CAP% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para obter o valor da propriedade de visibilidade. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_VISIBILITY% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como um valor matricial. Este método pode ser usado para obter o valor de um atributo Transform ou gradientTransform. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de tipo unitário. Este método pode ser usado para obter o valor de um atributo gradientUNITs ou clipPathUnits. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_UNIT_TYPE% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para obter o valor de um atributo spreadMethod. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_EXTEND_MODE% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para obter o valor de um atributo PreserveAspectRatio. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como um valor de comprimento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] CA_D2D1_SVG_LENGTH^% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgAttribute) que contém um ponteiro para o valor do atributo especificado.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] ICarenD2D1SvgAttribute^% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como uma tinta. Este método pode ser usado para obter o valor das propriedades de preenchimento ou traçado. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o valor do atributo especificado.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] ICarenD2D1SvgPaint^% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como uma matriz de traço de traço de traço. Este método pode ser usado para obter o valor da propriedade stroke-dasharray. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o valor do atributo especificado.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_Valor);

	/// <summary>
	/// Recebe um atributo deste elemento como pontos. Este método pode ser usado para obter o valor do atributo de pontos em um polígono ou elemento polilinha. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPointCollection) que contém um ponteiro para o valor do atributo especificado.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] ICarenD2D1SvgPointCollection^% Param_Out_Valor);

	/// <summary>
	/// Obtém um atributo desse elemento como dados de caminho. Este método pode ser usado para obter o valor do atributo d em um elemento de Path. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPathData) que contém um ponteiro para o valor do atributo especificado.</param>
	virtual CarenResult GetAttributeValue(
	String^ Param_NomeAtributo,
	[Out] ICarenD2D1SvgPathData^% Param_Out_Valor);

	/// <summary>
	/// Obtém o comprimento da sequência de um atributo deste elemento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Tipo">O tipo de String do atributo.</param>
	/// <param name="Param_Out_LarguraValor">Retorna o comprimento do atributo. O comprimento da corda retornado não inclui espaço para o exterminador nulo.</param>
	virtual CarenResult GetAttributeValueLength(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
	[Out] UInt32% Param_Out_LarguraValor);

	/// <summary>
	/// Obtém o documento que contém este elemento.
	/// </summary>
	/// <param name="Param_Out_Documento">Retorna uma interface(ICarenD2D1SvgDocument) com um ponteiro para o documento que contém este elemento. Este argumento será nulo se o elemento tiver sido 
	/// removido da árvore.</param>
	virtual void GetDocument([Out] ICarenD2D1SvgDocument^% Param_Out_Documento);

	/// <summary>
	/// Obtém o primeiro filho deste elemento. 
	/// </summary>
	/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) do primeiro child deste elemento.</param>
	virtual void GetFirstChild([Out] ICarenD2D1SvgElement^% Param_Out_Child);

	/// <summary>
	/// Obtém o ultimo filho deste elemento.  
	/// </summary>
	/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para do ultimo child deste elemento.</param>
	virtual void GetLastChild([Out] ICarenD2D1SvgElement^% Param_Out_Child);

	/// <summary>
	/// Obtém o próximo irmão do elemento (Param_ReferenciaChild). 
	/// </summary>
	/// <param name="Param_ReferenciaChild">A referênciaChild deve ser um child imediato deste elemento.</param>
	/// <param name="Param_Out_ProximoChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
	/// for o ultimo child, a saída é NULA.</param>
	virtual CarenResult GetNextChild(
	ICarenD2D1SvgElement^ Param_ReferenciaChild,
	[Out] ICarenD2D1SvgElement^% Param_Out_ProximoChild);

	/// <summary>
	/// Obtém o elemento pai. 
	/// </summary>
	/// <param name="Param_Out_Parent">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o elemento pai.</param>
	virtual void GetParent([Out] ICarenD2D1SvgElement^% Param_Out_Parent);

	/// <summary>
	/// Recebe o child anterior do elemento (Param_ReferenciaChild). 
	/// </summary>
	/// <param name="Param_ReferenciaChild">>A referênciaChild deve ser um child imediato deste elemento.</param>
	/// <param name="Param_Out_ChildAnterior">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
	/// for o primeiro child, a saída é NULA. </param>
	virtual CarenResult GetPreviousChild(
	ICarenD2D1SvgElement^ Param_ReferenciaChild,
	[Out] ICarenD2D1SvgElement^% Param_Out_ChildAnterior);

	/// <summary>
	/// Retorna o número de atributos especificados neste elemento. Os atributos só são considerados especificados se estiverem explicitamente definidos no elemento ou presentes dentro de um 
	/// estilo inline. As propriedades que recebem seu valor através da herança CSS não são consideradas especificadas. Um atributo pode ser especificado se for definido através de uma chamada 
	/// de método. Ele pode se tornar não especificado se for removido via RemoveAttribute. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de atributos especificados neste elemento.</param>
	virtual void GetSpecifiedAttributeCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtém o nome do atributo no índice dado. 
	/// </summary>
	/// <param name="Param_Indice">O índice do atributo.</param>
	/// <param name="Param_Out_NomeAtributo">Retorna o nome do atributo.</param>
	/// <param name="Param_LarguraNome">A largura da String retornada em (Param_Out_NomeAtributo).</param>
	/// <param name="Param_Out_Herdado">Retorna um valor que define se o atributo está definido para o valor herdado</param>
	virtual CarenResult GetSpecifiedAttributeName(
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
	virtual CarenResult GetSpecifiedAttributeNameLength(
	UInt32 Param_Indice,
	[Out] UInt32% Param_Out_LarguraNome,
	[Out] Boolean% Param_Out_Herdado);

	/// <summary>
	/// Obtém o nome da Tag.
	/// </summary>
	/// <param name="Param_Out_NomeTag">Retorna o nome da Tag.</param>
	/// <param name="Param_LarguraNomeTag">O comprimento da String em (Param_Out_NomeTag). Obtenha esse valor chamando o método (GetTagNameLength).</param>
	virtual CarenResult GetTagName(
	[Out] String^% Param_Out_NomeTag,
	UInt32 Param_LarguraNomeTag);

	/// <summary>
	/// Obtém o comprimento da String do nome da Tag. 
	/// </summary>
	/// <param name="Param_Out_LarguraNomeTag">Retorna o comprimento da String do nome da tag. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
	virtual void GetTagNameLength([Out] UInt32% Param_Out_LarguraNomeTag);

	/// <summary>
	/// Obtém o valor de um elemento de conteúdo de texto. 
	/// </summary>
	/// <param name="Param_Out_ValorElemento">Retorna o valor do elemento de conteúdo texto.</param>
	/// <param name="Param_LarguraValor">O comprimento da String em (Param_Out_ValorElemento). Obtenha esse valor chamando o método (GetTextValueLength).</param>
	virtual CarenResult GetTextValue(
	[Out] String^% Param_Out_ValorElemento,
	UInt32 Param_LarguraValor);

	/// <summary>
	/// Obtém o comprimento do valor do conteúdo do texto. 
	/// </summary>
	/// <param name="Param_Out_LarguraValorElemento">Retorna o comprimento do valor do conteúdo do texto. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
	virtual void GetTextValueLength([Out] UInt32% Param_Out_LarguraValorElemento);

	/// <summary>
	/// Retorna um booleano indicando se esse elemento tem filhos. 
	/// </summary>
	/// <param name="Param_Out_ElementoCrianca">Retorna TRUE se este elemento tiver filhos.</param>
	virtual void HasChildren([Out] Boolean% Param_Out_ElementoCrianca);

	/// <summary>
	/// Insere (Param_NewChild) como um child deste elemento, antes do elemento (Param_ReferenceChild). Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da inserção. 
	/// </summary>
	/// <param name="Param_NewChild">O elemento a ser inserido.</param>
	/// <param name="Param_NewChild">O elemento que a child deve ser inserida antes. Se este parametro for NULO, o (Param_NewChild) será colocado como o último child. Se a (Param_ReferenceChild) não for NULA, deve ser um child imediato deste elemento.</param>
	virtual CarenResult InsertChildBefore(
	ICarenD2D1SvgElement^ Param_NewChild,
	ICarenD2D1SvgElement^ Param_ReferenceChild);

	/// <summary>
	/// Retorna uma indicação booleana se o atributo estiver explicitamente definido no elemento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo.</param>
	/// <param name="Param_Out_Herdado">Retorna um valor booleano que indica se o atributo está definido para o valor herdado.</param>
	/// <param name="Param_Out_Especificado">Retorna TRUE se o atributo é explicitamente definido no elemento ou se ele está presente dentro de um estilo inline. Retorna FALSE se o atributo não for um atributo válido neste elemento.</param>
	virtual void IsAttributeSpecified(
	String^ Param_NomeAtributo,
	[Out] Boolean% Param_Out_Herdado,
	[Out] Boolean% Param_Out_Especificado);

	/// <summary>
	/// Retorna um boolean indicando que este elemento representa conteúdo de texto. 
	/// </summary>
	/// <param name="Param_Out_Texto">Retorna TRUE se esse elemento representar conteúdo de texto, por exemplo, o conteúdo de um elemento 'título' ou 'desc'. O conteúdo do texto não tem um nome de tag.</param>
	virtual void IsTextContent([Out] Boolean% Param_Out_Texto);

	/// <summary>
	/// Remove o atributo deste elemento. Também remove esse atributo de dentro de um estilo inline se presente. 
	/// </summary>
	/// <param name="Param_NomeAtributo">O nome do atributo para remover.</param>
	virtual CarenResult RemoveAttribute(String^ Param_NomeAtributo);

	/// <summary>
	/// Remove o (Param_OldChild) da árvore. Filhos de (Param_OldChild) permanecem filhos de (Param_OldChild). 
	/// </summary>
	/// <param name="Param_OldChild"></param>
	virtual CarenResult RemoveChild(ICarenD2D1SvgElement^ Param_OldChild);

	/// <summary>
	/// Substitui o elemento (Param_OldChild) pelo (Param_NewChild). Esta operação remove o (Param_OldChild) da árvore. Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da operação de substituição.
	/// </summary>
	/// <param name="Param_NewChild">O elemento a ser inserido.</param>
	/// <param name="Param_OldChild">O elemento child a ser substituído. O elemento (Param_OldChild) deve ser uma child imediata deste elemento.</param>
	virtual CarenResult ReplaceChild(
	ICarenD2D1SvgElement^ Param_NewChild,
	ICarenD2D1SvgElement^ Param_OldChild);

	/// <summary>
	/// Define um atributo deste elemento usando uma string. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Tipo">O tipo da String.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
	String^ Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento usando um tipo POD. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Tipo">O tipo POD do atributo.</param>
	/// <param name="Param_Valor">Uma interface(ICaren) que contém um ponteiro(void*) do novo valor do atributo.</param>
	/// <param name="Param_Size">O tamanho do novo valor em bytes.</param>
	virtual CarenResult SetAttributeValue(
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
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	ICarenD2D1SvgAttribute^ Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento usando um float. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	float Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como uma cor. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_COLOR_F^ Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para definir o valor das propriedades 'regra de preenchimento' ou 'regra de clipe'. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_FILL_MODE Param_Valor);

	/// <summary>
	/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_DISPLAY Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para definir o valor da propriedade de transbordamento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_OVERFLOW Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de join de linha. Este método pode ser usado para definir o valor da propriedade stroke-linejoin. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_LINE_JOIN Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para definir o valor da propriedade stroke-linecap. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_LINE_CAP Param_Valor);

	/// <summary>
	/// Define um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para definir o valor da propriedade de visibilidade. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_VISIBILITY Param_Valor);

	/// <summary>
	/// Define um atributo desse elemento como um valor de matriz. Este método pode ser usado para definir o valor de um atributo Transform ou gradientTransform. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_MATRIX_3X2_F^ Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de tipo de unidade. Este método pode ser usado para definir o valor de um atributo gradientUNITs ou clipPathUnits. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_UNIT_TYPE Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para definir o valor de um atributo spreadMethod. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_EXTEND_MODE Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para definir o valor de um atributo PreserveAspectRatio. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ Param_Valor);

	/// <summary>
	/// Define um atributo deste elemento como um valor de comprimento. 
	/// </summary>
	/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
	/// <param name="Param_Valor">O novo valor do atributo.</param>
	virtual CarenResult SetAttributeValue(
	String^ Param_NomeAtributo,
	CA_D2D1_SVG_LENGTH^ Param_Valor);

	/// <summary>
	/// Define o valor de um elemento de conteúdo de texto. 
	/// </summary>
	/// <param name="Param_Texto">O novo valor do elemento conteúdo de texto.</param>
	/// <param name="Param_LarguraTexto">A largura da String em (Param_Texto).</param>
	virtual CarenResult SetTextValue(
	String^ Param_Texto,
	UInt32 Param_LarguraTexto);



	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};