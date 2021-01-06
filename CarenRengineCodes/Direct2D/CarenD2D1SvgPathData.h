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
#include "CarenD2D1SvgAttribute.h"
#include "CarenD2D1PathGeometry1.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por descrever os dados do Path SVG. Os Path Data podem ser definidos como o atributo 'd' em um elemento 'path'.
/// </summary>
public ref class CarenD2D1SvgPathData : public ICarenD2D1SvgPathData
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SvgPathData).
	ID2D1SvgPathData* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SvgPathData();

	~CarenD2D1SvgPathData();

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
			System::Console::WriteLine(String::Concat(ICarenD2D1SvgPathData::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1SvgPathData)
public:
	/// <summary>
	/// Cria um objeto de Path Geometry representando os Path Data. 
	/// </summary>
	/// <param name="Param_FillMode">Modo de preenchimento para o Path Geometry.</param>
	/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry1) contendo um ponteiro para para o objeto criado. </param>
	virtual CarenResult CreatePathGeometry(
	CA_D2D1_FILL_MODE Param_FillMode,
	[Out] ICarenD2D1PathGeometry1^% Param_Out_PathGeometry);

	/// <summary>
	/// Recebe comandos da matriz de comandos. 
	/// </summary>
	/// <param name="Param_Out_Comandos">Buffer para conter os comandos.</param>
	/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
	/// <param name="Param_StartIndex">O índice dos primeiros comandos para recuperar.</param>
	virtual CarenResult GetCommands(
	[Out] cli::array<CA_D2D1_SVG_PATH_COMMAND>^% Param_Out_Comandos,
	UInt32 Param_Quantidade,
	UInt32 Param_StartIndex);

	/// <summary>
	/// Obtém o tamanho da matriz de comandos. 
	/// </summary>
	/// <param name="Param_Out_QuantidadeComandos">Retorna o tamanho da matriz de comandos.</param>
	virtual void GetCommandsCount([Out] UInt32% Param_Out_QuantidadeComandos);

	/// <summary>
	/// Obtém dados do conjunto de dados do segmento. 
	/// </summary>
	/// <param name="Param_Out_Dados">Buffer para conter o conjunto de dados do segmento.</param>
	/// <param name="Param_Quantidade">A contagem de elementos do buffer.</param>
	/// <param name="Param_StartIndex">O índice dos dados do primeiro segmento para recuperar.</param>
	virtual CarenResult GetSegmentData(
	[Out] cli::array<float>^% Param_Out_Dados,
	UInt32 Param_Quantidade,
	UInt32 Param_StartIndex);

	/// <summary>
	/// Obtém o tamanho do conjunto de dados do segmento. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o tamanho do conjunto de dados do segmento.</param>
	virtual void GetSegmentDataCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Remove comandos do final da matriz de comandos. 
	/// </summary>
	/// <param name="Param_QuantidadeComandos">Especifica quantos comandos deve remover.</param>
	virtual CarenResult RemoveCommandsAtEnd(UInt32 Param_QuantidadeComandos);

	/// <summary>
	/// Remove dados do conjunto de dados do segmento. 
	/// </summary>
	/// <param name="Param_DataCount">Especifica quantos dados deve remover.</param>
	virtual CarenResult RemoveSegmentDataAtEnd(UInt32 Param_DataCount);

	/// <summary>
	/// Atualiza o conjunto de comandos. Os comandos existentes não atualizados por este método são preservados. A matriz é redimensionada maior se necessário para acomodar os novos comandos. 
	/// </summary>
	/// <param name="Param_Comandos">A matriz de comandos.</param>
	/// <param name="Param_Quantidade">O número de comandos para atualizar.</param>
	/// <param name="Param_StartIndex">O índice para começar a atualizar comandos. Deve ser menor ou igual ao tamanho da matriz de comandos.</param>
	virtual CarenResult UpdateCommands(
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
	virtual CarenResult UpdateSegmentData(
	cli::array<float>^ Param_Dados,
	UInt32 Param_Quantidade,
	UInt32 Param_StartIndex);



	//Métodos da interface(ICarenD2D1SvgAttribute)
public:
	/// <summary>
	/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
	/// </summary>
	/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
	virtual CarenResult Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface);

	/// <summary>
	/// Retorna o elemento no qual este atributo é definido. Retorna nulo se o atributo não estiver definido em nenhum elemento. 
	/// </summary>
	/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém um ponteiro parao elemtno no qual este atributo é definido. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetElement(ICaren^ Param_Out_SvgElement);



	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};