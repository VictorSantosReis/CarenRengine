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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um gráfico de nós de transformação.
/// </summary>
public ref class CarenD2D1TransformGraph : public ICarenD2D1TransformGraph
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1TransformGraph).
	ID2D1TransformGraph* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1TransformGraph();

	~CarenD2D1TransformGraph();

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
			System::Console::WriteLine(String::Concat(ICarenD2D1TransformGraph::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1TransformGraph)
public:
	/// <summary>
	/// Adiciona o nó fornecido ao gráfico de transformação.
	/// Um nó deve ser adicionado ao gráfico de transformação antes que ele possa ser interligado de qualquer forma.
	/// Um gráfico de transformação não pode ser adicionado diretamente a outro gráfico de transformação. Somente interfaces derivadas do ICarenD2D1TransformNode podem 
	/// ser adicionadas ao gráfico de transformação.
	/// </summary>
	/// <param name="Param_Node">O nó que será adicionado ao gráfico de transformação.</param>
	virtual CarenResult AddNode(ICarenD2D1TransformNode^ Param_Node);

	/// <summary>
	/// Limpa os nós de transformação e todas as conexões do gráfico de transformação. 
	/// </summary>
	virtual void Clear();

	/// <summary>
	/// Conecta dois nós dentro do gráfico de transformação. Ambos os nós já devem existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
	/// </summary>
	/// <param name="Param_FromNode">O nó a partir do qual a conexão será feita.</param>
	/// <param name="Param_ToNode">O nó para o qual a conexão será feita.</param>
	/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
	virtual CarenResult ConnectNode(
	ICarenD2D1TransformNode^ Param_FromNode,
	ICarenD2D1TransformNode^ Param_ToNode,
	UInt32 Param_ToNodeInputIndex);

	/// <summary>
	/// Conecta um nó de transformação dentro do gráfico à entrada de efeito correspondente do efeito encapsulamento. 
	/// </summary>
	/// <param name="Param_ToEffectInputIndex">A entrada de efeito à qual o nó de transformação será vinculado.</param>
	/// <param name="Param_Node">O nó para o qual a conexão será feita.</param>
	/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
	virtual CarenResult ConnectToEffectInput(
	UInt32 Param_ToEffectInputIndex,
	ICarenD2D1TransformNode^ Param_Node,
	UInt32 Param_ToNodeInputIndex);

	/// <summary>
	/// Retorna o número de entradas ao gráfico de transformação. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este gráfico de transformação.</param>
	virtual void GetInputCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Remove o nó fornecido do gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
	/// Quaisquer conexões com este nó serão removidas quando o nó for removido. Depois que o nó é removido, ele não pode ser usado pela interface até que tenha sido 
	/// adicionado ao gráfico por AddNode.
	/// </summary>
	/// <param name="Param_Node">O nó que será removido do gráfico de transformação.</param>
	virtual CarenResult RemoveNode(ICarenD2D1TransformNode^ Param_Node);

	/// <summary>
	/// Define o nó de saída para o gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
	/// </summary>
	/// <param name="Param_Node">O nó que será considerado a saída do nó de transformação.</param>
	virtual CarenResult SetOutputNode(ICarenD2D1TransformNode^ Param_Node);

	/// <summary>
	/// Usa a entrada especificada como saída de efeito. 
	/// </summary>
	/// <param name="Param_EffectInputIndex">O índice da entrada para o efeito.</param>
	virtual CarenResult SetPassthroughGraph(UInt32 Param_EffectInputIndex);

	/// <summary>
	/// Define um único nó de transformação como sendo equivalente a todo o gráfico. 
	/// Isso equivale a chamar ICarenD2D1TransformGraph::Clear, adicionar um único nó, conectar todas as entradas de nó às entradas de efeito em ordem e definir a 
	/// transformação não como saída de gráfico.
	/// </summary>
	/// <param name="Param_Node">O nó a ser definido.</param>
	virtual CarenResult SetSingleTransformNode(ICarenD2D1TransformNode^ Param_Node);
};