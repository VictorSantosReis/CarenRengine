﻿/*
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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenMFMediaType.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// Classe responsável por representar um nó em uma topologia.
/// </summary>
public ref class CarenMFTopologyNode :public ICarenMFTopologyNode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFTopologyNode).
	IMFTopologyNode* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFTopologyNode();

	/// <summary>
	/// Inicializa e cria um novo nó de topologia.
	/// </summary>
	/// <param name="Param_TypeNode">‎O tipo de nó a ser criado, especificado como membro da enumeração ‎‎(CA_MF_TOPOLOGY_TYPE).‎</param>
	CarenMFTopologyNode(CA_MF_TOPOLOGY_TYPE Param_TypeNode);

	~CarenMFTopologyNode();


	//Conversões implicitas
public:
	static operator CarenMFTopologyNode^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFTopologyNode^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFTopologyNode();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFTopologyNode*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFTopologyNode::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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



	//Métodos da interface (ICarenMFTopologyNode)
public:
	/// <summary>
	/// (CloneFrom) - Copia os dados de outro nó de topologia para este nó.
	/// </summary>
	/// <param name="Param_NodeClone">O nó que vai ter os dados copiados para esse.</param>
	virtual CarenResult CloneFrom(ICarenMFTopologyNode^ Param_NodeClone);

	/// <summary>
	/// (ConnectOutput) - Conecta um fluxo de saída deste nó para o fluxo de entrada de outro nó.
	/// As conexões de nó representam o fluxo de dados de um nó para o próximo. Os fluxos são lógicos e são especificados pelo índice. Se o nó já estiver conectado na saída especificada, o método interrompe a conexão existente.
	/// </summary>
	/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de saída neste nó.</param>
	/// <param name="Param_NoConexao">Ponteiro para a interface ICarenMFTopologyNode do nó ao qual se conectar.</param>
	/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de entrada no outro nó.</param>
	virtual CarenResult ConnectOutput(UInt32 Param_IndexFluxoSaida, ICarenMFTopologyNode^ Param_NoConexao, UInt32 Param_IndexFluxoEntrada);

	/// <summary>
	/// (DisconnectOutput) - Desconecta um fluxo de saída neste nó.
	/// </summary>
	/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de saída para se desconectar.</param>
	virtual CarenResult DisconnectOutput(UInt32 Param_IndexSaida);

	/// <summary>
	/// (GetInput) - Recupera o nó que está conectado a um fluxo de entrada especificado neste nó.
	/// </summary>
	/// <param name="Param_IndexEntrada">Índice baseado em zero de um fluxo de entrada neste nó.</param>
	/// <param name="Param_Out_NoConectado">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de entrada especificado. O chamador deve liberar a interface.</param>
	/// <param name="Param_Out_IndexFluxoSaida">Recebe o índice do fluxo de saída que está conectado ao fluxo de entrada deste nó.</param>
	virtual CarenResult GetInput(UInt32 Param_IndexEntrada, [Out] ICarenMFTopologyNode^% Param_Out_NoConectado, [Out] UInt32% Param_Out_IndexFluxoSaida);

	/// <summary>
	/// (GetInputCount) - Recupera o número de fluxos de entrada que existem atualmente neste nó.
	/// </summary>
	/// <param name="Param_Out_QuantidadeFluxosEntrada">Recebe o número de fluxos de entrada.</param>
	virtual CarenResult GetInputCount([Out] UInt32% Param_Out_QuantidadeFluxosEntrada);

	/// <summary>
	/// (GetInputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de entrada neste nó.
	/// </summary>
	/// <param name="Param_IndexEntrada">Índice baseado em zero do fluxo de Entrada.</param>
	/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para IMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetInputPrefType(UInt32 Param_IndexEntrada, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial);

	/// <summary>
	/// (GetNodeType) - Recupera o tipo de nó.
	/// </summary>
	/// <param name="Param_Out_TipoNode">Recebe um valor de enumeração que define o tipo do nó na topologia.</param>
	virtual CarenResult GetNodeType([Out] Enumeracoes::CA_MF_TOPOLOGY_TYPE% Param_Out_TipoNode);

	/// <summary>
	/// (GetObject) - Obtém o objeto associado a este nó.
	/// </summary>
	/// <param name="Param_Out_Objeto">Recebe uma interface que está associada a esse nó. O usuário deve criar a interfaces antes de chamar este método.</param>
	virtual CarenResult GetObject(ICaren^ Param_Out_Objeto);

	/// <summary>
	/// (GetOutput) - Recupera o nó que está conectado a um fluxo de saída especificado neste nó.
	/// </summary>
	/// <param name="Param_IndexSaidaFluxo">Índice baseado em zero de um fluxo de saída neste nó.</param>
	/// <param name="Param_Out_NodeConexao">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de saída especificado. O chamador deve liberar a interface.</param>
	/// <param name="Param_Out_IndexEntradaFluxo">Recebe o índice do fluxo de entrada que está conectado ao fluxo de saída deste nó.</param>
	virtual CarenResult GetOutput(UInt32 Param_IndexSaidaFluxo, [Out] ICarenMFTopologyNode^% Param_Out_NodeConexao, [Out] UInt32% Param_Out_IndexEntradaFluxo);

	/// <summary>
	/// (GetOutputCount) - Recupera o número de fluxos de saída que existem atualmente neste nó.
	/// </summary>
	/// <param name="Param_Out_QuantidadeFluxosSaida">Recebe o número de fluxos de saída.</param>
	virtual CarenResult GetOutputCount([Out] UInt32% Param_Out_QuantidadeFluxosSaida);

	/// <summary>
	/// (GetOutputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de saída neste nó.
	/// </summary>
	/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de Saida.</param>
	/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para ICarenMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetOutputPrefType(UInt32 Param_IndexSaida, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial);

	/// <summary>
	/// (GetTopoNodeID) - Recupera o identificador do nó.
	/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Os identificadores de nó são exclusivos dentro de uma topologia, mas podem ser reutilizados 
	/// em várias topologias.
	/// </summary>
	/// <param name="Param_Out_IdentificadorNode">Recebe o identificador deste nó.</param>
	virtual CarenResult GetTopoNodeID([Out] UInt64% Param_Out_IdentificadorNode);

	/// <summary>
	/// (SetInputPrefType) - Define o tipo de mídia preferencial para um fluxo de entrada neste nó.
	/// </summary>
	/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de Entrada.</param>
	/// <param name="Param_TipoMidia">Ponteiro para ICarenMFMediaType do tipo de mídia.</param>
	virtual CarenResult SetInputPrefType(UInt32 Param_IndexFluxoEntrada, ICarenMFMediaType^ Param_TipoMidia);

	/// <summary>
	/// (SetObject) - Define o objeto associado a este nó.
	/// </summary>
	/// <param name="Param_Objeto">A interface a ser associada a este nó. Defina como NULO para limpar o objeto definido anteriormente.</param>
	virtual CarenResult SetObject(ICaren^ Param_Objeto);

	/// <summary>
	/// (SetOutputPrefType) - Define o tipo de mídia preferencial para um fluxo de saída neste nó.
	/// </summary>
	/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de Saida.</param>
	/// <param name="Param_TipoMidia">A interface ICarenMFMediaType que contém o ponteiro para o tipo de midia..</param>
	virtual CarenResult SetOutputPrefType(UInt32 Param_IndexFluxoSaida, ICarenMFMediaType^ Param_TipoMidia);

	/// <summary>
	/// (SetTopoNodeID) - Define o identificador para o nó.
	/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Normalmente, não há nenhuma razão para um aplicativo substituir o identificador.
	/// </summary>
	/// <param name="Param_IdentificadorNode">O novo identificador para este nó.</param>
	virtual CarenResult SetTopoNodeID(UInt64 Param_IdentificadorNode);



	//Métodos da interface(ICarenMFAttributes)
public:
	/// <summary>
	/// Compara os atributos neste objeto com os atributos em outro objeto.
	/// </summary>
	/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
	/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
	virtual CarenResult Compare(ICarenMFAttributes^ Param_InterfaceCompare, Enumeracoes::CA_MF_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, [Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PROPVARIANT.
	/// CA_PROPVARIANT é um Wrapper da PropVariant não gerenciada.
	/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PROPVARIANT) é diferente do (Valor) no Atributo,
	/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
	/// </summary>
	/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
	/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
	/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
	virtual CarenResult CompareItem(String^ Param_GuidChave, Estruturas::CA_PROPVARIANT^ Param_Valor, [Out] Boolean% Param_Out_Resultado);


	/// <summary>
	/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
	/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
	/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
	/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
	/// </summary>
	/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
	virtual CarenResult CopyAllItems(ICarenMFAttributes^ Param_Out_InterfaceDestino);


	/// <summary>
	/// Remove todos os pares chave/valor da lista de atributos do objeto.
	/// </summary>
	virtual CarenResult DeleteAllItems();


	/// <summary>
	/// Remove um emparelhar chave/valor da lista de atributos do objeto.
	/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
	/// </summary>
	/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
	virtual CarenResult DeleteItem(String^ Param_GuidChave);



	//Métodos (GET) da interface IMFAttributes.



	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
	/// memória para a matriz.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	virtual CarenResult GetAllocatedBlob(String^ Param_GuidChave, [Out] Estruturas::CA_BlobData% Param_Out_Buffer);


	/// <summary>
	/// Obtém uma seqüência de caracteres largos associada a uma chave. 
	/// Este método aloca a memória para a seqüência de caracteres.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
	/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
	virtual CarenResult GetAllocatedString(String^ Param_GuidChave, [Out] String^% Param_Out_String, [Out] UInt32% Param_Out_LarguraString);


	/// <summary>
	/// Recupera uma matriz de byte associada a uma chave. 
	/// Esse método copia a matriz em um buffer alocado pelo chamador.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
	/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
	/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (GetBlobSize) para obter o valor para esse parametro.</param>
	virtual CarenResult GetBlob(String^ Param_GuidChave, UInt32 Param_TamanhoBuffer, [Out] Estruturas::CA_BlobData% Param_Out_Buffer);


	/// <summary>
	/// Recupera o comprimento de uma matriz de byte associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
	/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
	virtual CarenResult GetBlobSize(String^ Param_GuidChave, [Out] UInt32% Param_TamanhoBuffer);


	/// <summary>
	/// Recupera o número de atributos que são definidos neste objeto.
	/// </summary>
	/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
	virtual CarenResult GetCount([Out] UInt32% Param_QuantidadeAtributos);


	/// <summary>
	/// Recupera um valor (Double) associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetDouble(String^ Param_GuidChave, [Out] Double% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor GUID associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetGUID(String^ Param_GuidChave, [Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o valor desconhecido associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PROPVARIANT) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetItem(String^ Param_GuidChave, [Out] Estruturas::CA_PROPVARIANT^% Param_Out_Valor);


	/// <summary>
	/// Recupera um atributo no índice especificado.
	/// </summary>
	/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
	/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetItemByIndex(UInt32 Param_IdItem, [Out] String^% Param_Out_GuidChave, [Out] Estruturas::CA_PROPVARIANT^% Param_Out_Valor);


	/// <summary>
	/// Recupera o tipo de dados do valor associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
	/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
	virtual CarenResult GetItemType(String^ Param_GuidChave, [Out] Enumeracoes::CA_MF_ATTRIBUTE_TYPE% Param_Out_TipoDado);


	/// <summary>
	/// Recupera uma sequência de caracteres largos associada a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: GetStringLength</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
	virtual CarenResult GetString(String^ Param_GuidChave, UInt32 Param_LagruraString, [Out] String^% Param_Out_Valor);


	/// <summary>
	/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
	/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
	/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
	virtual CarenResult GetStringLength(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura);


	/// <summary>
	/// Recupera um valor de UINT32 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT32) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetUINT32(String^ Param_GuidChave, [Out] UInt32% Param_Out_Valor);


	/// <summary>
	/// Recupera um valor de UInt64 associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
	/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
	virtual CarenResult GetUINT64(String^ Param_GuidChave, [Out] UInt64% Param_Out_Valor);

	/// <summary>
	/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
	/// Ese método recuperar o Numerador e Denominador de uma chave.
	/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
	/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
	/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
	virtual CarenResult _MFGetAttributeRatio(String^ Param_GuidChave, [Out] UInt32% Param_Out_Numerador, [Out] UInt32% Param_Out_Denominador);

	/// <summary>
	/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
	/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
	/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro para o objeto desconhecido. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetUnknown(String^ Param_GuidChave, String^ Param_GuidInterfaceSolicitada, ICaren^ Param_Out_InterfaceDesconhecida);

	/// <summary>
	/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
	/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
	/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
	virtual CarenResult _MFGetAttributeSize(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura, [Out] UInt32% Param_Out_Altura);

	/// <summary>
	/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
	/// </summary>
	virtual CarenResult LockStore();




	//Métodos (SET) da interface IMFAttributes.




	/// <summary>
	/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Buffer">Uma interface (ICarenBuffer) que contém os dados a serem associados a chave especificada.</param>
	virtual CarenResult SetBlob(String^ Param_GuidChave, ICarenBuffer^ Param_Buffer);


	/// <summary>
	/// Associa um valor duplo com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult SetDouble(String^ Param_GuidChave, Double Param_Valor);


	/// <summary>
	/// RAssocia um valor GUID com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult SetGUID(String^ Param_GuidChave, String^ Param_Valor);


	/// <summary>
	/// Adiciona um valor de atributo com uma chave especificada.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
	virtual CarenResult SetItem(String^ Param_GuidChave, Estruturas::CA_PROPVARIANT^ Param_PropVariantValor);


	/// <summary>
	/// Associa uma seqüência de caracteres largos com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult SetString(String^ Param_GuidChave, String^ Param_Valor);


	/// <summary>
	/// Associa um valor de UINT32 com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult SetUINT32(String^ Param_GuidChave, UInt32 Param_Valor);


	/// <summary>
	/// Associa um UINT64 valor com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
	virtual CarenResult SetUINT64(String^ Param_GuidChave, UInt64 Param_Valor);

	/// <summary>
	/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
	/// Esse método define no valor da chave uma razão(Numerador e Denominador).
	/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Numerador">Define o valor do: Numerador</param>
	/// <param name="Param_Denominador">Define o valor do: Denominador</param>
	virtual CarenResult _MFSetAttributeRatio(String^ Param_GuidChave, UInt32 Param_Numerador, UInt32 Param_Denominador);

	/// <summary>
	/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
	/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
	/// largura e altura em um único valor de UInt64 .
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
	/// <param name="Param_Largura">A largura do vídeo em pixels.</param>
	/// <param name="Param_Altura">A altura do vídeo em pixels.</param>
	virtual CarenResult _MFSetAttributeSize(String^ Param_GuidChave, UInt32 Param_Largura, UInt32 Param_Altura);

	/// <summary>
	/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
	/// </summary>
	/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
	/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
	virtual CarenResult SetUnknown(String^ Param_GuidChave, ICaren^ Param_InterfaceDesconhecida);


	/// <summary>
	/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
	/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
	/// </summary>
	virtual CarenResult UnlockStore();
};