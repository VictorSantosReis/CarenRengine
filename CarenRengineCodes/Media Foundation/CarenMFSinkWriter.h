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
#include "../SDK_MediaFoundation.h"
#include "CarenMFMediaType.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por enviar os dados de mídia dos (Coletores de Mídia) para um Arquivo ou Hardware. 
/// </summary>
public ref class CarenMFSinkWriter : public ICarenMFSinkWriter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSinkWriter).
	IMFSinkWriter* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFSinkWriter();

	/// <summary>
	/// Inicializa e cria o Sink Wiriter a parti de um Media Sink.
	/// </summary>
	/// <param name="Param_MediaSink">A interface para o sink de mídia a ser utilizado.</param>
	/// <param name="Param_Atributos">Uma interface com atributos. Você pode usar este parâmetro para configurar o Sink Writer. Este parâmetro pode ser NULO.</param>
	CarenMFSinkWriter(ICarenMFMediaSink^ Param_MediaSink, ICarenMFAttributes^ Param_Atributos);

	/// <summary>
	/// Inicializa e cria o Sink Writer a parti de uma URL ou um fluxo de bytes.
	/// </summary>
	/// <param name="Param_OutputUrl">Uma url para o arquivo de saida. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Stream">Uma interface ICarenMFByteStream de um fluxo byte. Este parâmetro pode ser NULO. Se este parâmetro for válido, o Sink Writer escreve para o fluxo byte fornecido (O fluxo de byte deve suportar escrita). 
	/// Caso contrário, se (Param_Stream) for NULO, o Sink Writer cria um novo arquivo chamado (Param_OutputUrl).</param>
	/// <param name="Param_Atributos">Uma interface com atributos. Você pode usar este parâmetro para configurar o Sink Writer. Este parâmetro pode ser NULO.</param>
	CarenMFSinkWriter(String^ Param_OutputUrl, ICarenMFByteStream^ Param_Stream, ICarenMFAttributes^ Param_Atributos);

	~CarenMFSinkWriter();


	//Conversões implicitas
public:
	static operator CarenMFSinkWriter^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFSinkWriter^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFSinkWriter();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFSinkWriter*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFSinkWriter::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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



	//Métodos da classe ICarenMFSinkWriter
public:
	/// <summary>
	/// (AddStream) - Adiciona um fluxo para o gravador de coletor.
	/// </summary>
	/// <param name="Param_TipoMidia">Esse tipo de mídia especifica o formato das amostras que serão gravados no arquivo ou Hardware. 
	/// Ele não precisa corresponder ao formato de entrada. Para definir o formato de entrada, chame o método :
	/// SetInputMediaType</param>
	/// <param name="Param_Out_IdFluxoAdicionado">Recebe o índice baseado em zero do novo fluxo.</param>
	virtual CarenResult AddStream(ICarenMFMediaType^ Param_TipoMidia, [Out] UInt32% Param_Out_IdFluxoAdicionado);

	/// <summary>
	/// (BeginWriting) - Inicializa o gravador de coletor para gravação.
	/// Chame esse método depois de configurar os fluxos de entrada e antes de enviar 
	/// os dados para o gravador de coletor.
	/// </summary>
	virtual CarenResult BeginWriting();

	/// <summary>
	/// (Finalize) - Conclui todas as operações de gravação no gravador de coletor.
	/// </summary>
	virtual CarenResult _Finalize();

	/// <summary>
	/// (Flush) - Libera um ou mais fluxos.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo a ser liberado. Se (Param_TodosFluxos) for True, desconsidere esse valor.</param>
	/// <param name="Param_TodosFluxos">Define se deve liberar todos os fluxos deste escritor. Equivale ao valor: MF_SINK_WRITER_ALL_STREAMS</param>
	virtual CarenResult Flush(UInt32 Param_IdFluxo, Boolean Param_TodosFluxos);

	/// <summary>
	/// (GetServiceForStream) - Consulta o coletor de mídia subjacente ou codificador para uma interface.
	/// </summary>
	/// <param name="Param_IdFluxo">Um Indice baseado em zero de um fluxo para a consulta. Desconsidere esse valor se o parâmetro (Param_Escritor)
	/// for True.</param>
	/// <param name="Param_ConsultarColetor">Define que o objeto de consulta é o Coletor de Mídia associado. Esse valor representa o: MF_SINK_WRITER_MEDIASINK</param>
	/// <param name="Param_GuidServiço">O Guid para o (Identificador de Serviço). Se o valor for (NULO), o método chama (QueryInterface) para obter
	/// interface solicitada.</param>
	/// <param name="Param_GuidInterfaceSolicitada">O Guid para a interface solicitada.</param>
	/// <param name="Param_Out_Interface">Recebe a interface solicitada.</param>
	virtual CarenResult GetServiceForStream(
		UInt32 Param_IdFluxo,
		Boolean Param_ConsultarColetor,
		String^ Param_GuidServiço,
		String^ Param_GuidInterfaceSolicitada,
		ICaren^ Param_Out_Interface);

	/// <summary>
	/// (GetStatistics) - Obtém estatísticas sobre o desempenho do gravador de coletor.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo de consulta. Se (Param_ConsularColetor) for True, desconsidere esse valor.</param>
	/// <param name="Param_ConsultarColetor">Define se deve obter as estatísticas do (Coletor de Mídia) propriamente dito.</param>
	/// <param name="Param_Out_StatusDesempenho">Retorna a estrutura que contém todas as informações de sempenho </param>
	virtual CarenResult GetStatistics(UInt32 Param_IdFluxo, Boolean Param_ConsultarColetor, [Out] Estruturas::CA_MF_SINK_WRITER_STATISTICS^% Param_Out_StatusDesempenho);

	/// <summary>
	/// (NotifyEndOfSegment) - Notifica o coletor de mídia que um fluxo atingiu o final de um segmento.
	/// </summary>
	/// <param name="Param_IdFluxo">O indica para o fluxo que vai ser notificado que foi atingido o final de um segmento. Desconsidere esse valor se (Param_NotificarTodos)
	/// for True.</param>
	/// <param name="Param_NotificarTodos">Indica que vai notificar que todos os fluxos atingiram o final de um segmento.</param>
	virtual CarenResult NotifyEndOfSegment(UInt32 Param_IdFluxo, Boolean Param_NotificarTodos);

	/// <summary>
	/// Coloca um marcador no fluxo especificado.
	/// Para usar esse método, você deve fornecer um retorno de chamada assíncrono(MF_SINK_WRITER_ASYNC_CALLBACK) quando você cria o Gravador de Coletor(ICarenMFSinkWriter).
	/// Caso contrario, o método retorna o código: ER_MF_REQUISICAO_INVALIDA
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo que vai ter o marcador adicionado.</param>
	/// <param name="Param_Valor">A interface que contém o valor desconhecido a ser definido.</param>
	virtual CarenResult PlaceMarker(UInt32 Param_IdFluxo, ICaren^ Param_Valor);

	/// <summary>
	/// (SendStreamTick) - Indica uma lacuna em um fluxo de entrada.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.o.</param>
	/// <param name="Param_IdFluxo">A posição no fluxo onde ocorre a lacuna nos dados. O valor é fornecido em 100-nanosecond unidades, 
	/// em relação ao início do fluxo..</param>
	virtual CarenResult SendStreamTick(UInt32 Param_IdFluxo, Int64 Param_TimeStamp);

	/// <summary>
	/// (SetInputMediaType) - Define o Formatar de entrada para um fluxo no gravador de coletor.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
	/// <param name="Param_TipoMidia">A interface que representa o tipo da mídia. O tipo de mídia especifica o 
	/// formato de entrada.</param>
	/// <param name="Param_ParametrosEncode">Use o repositório de atributos para configurar o codificador. 
	/// Este parâmetro pode ser nulo.</param>
	virtual CarenResult SetInputMediaType(UInt32 Param_IdFluxo, ICarenMFMediaType^ Param_TipoMidia, ICarenMFAttributes^ Param_ParametrosEncode);

	/// <summary>
	/// (WriteSample) - Fornece uma amostra para o gravador de coletor.
	/// Você deve chamar o método (BeginWriting) antes de chamar esse método. Caso contrário, o método retornará 
	/// o código: ER_MF_REQUISICAO_INVALIDA.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo para este exemplo.</param>
	/// <param name="Param_AmostraMidia">A interface que contém a amostra a ser escrita.</param>
	virtual CarenResult WriteSample(UInt32 Param_IdFluxo, ICarenMFSample^ Param_AmostraMidia);
};

