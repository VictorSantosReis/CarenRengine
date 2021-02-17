#pragma once
#include "../SDK_MediaFoundation.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenMFVideoMediaType.h"
#include "../NativeClassForEvents/CLN_IMFClockStateSink.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// Classe responsável por representar um apresentador de vídeo.
/// </summary>
public ref class CarenMFVideoPresenter : public ICarenMFVideoPresenter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFVideoPresenter).
	IMFVideoPresenter* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFVideoPresenter();

	~CarenMFVideoPresenter();


	//Conversões implicitas
public:
	static operator CarenMFVideoPresenter^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFVideoPresenter^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFVideoPresenter();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFVideoPresenter*>(Param_Pointer.ToPointer());

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



	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////

	/// <summary>
	/// Chamado quando o relógio de apresentação é iniciado.
	/// </summary>
	virtual event ICarenMFClockStateSink::Delegate_OnClockStart^ OnClockStart;

	/// <summary>
	/// Chamado quando o relógio de apresentação para.
	/// </summary>
	virtual event ICarenMFClockStateSink::Delegate_OnClockStop^ OnClockStop;

	/// <summary>
	/// Chamado quando o relógio de apresentação faz uma pausa.
	/// </summary>
	virtual event ICarenMFClockStateSink::Delegate_OnClockPause^ OnClockPause;

	/// <summary>
	/// Chamado quando o relógio de apresentação é reiniciado da mesma posição durante a pausa.
	/// </summary>
	virtual event ICarenMFClockStateSink::Delegate_OnClockRestart^ OnClockRestart;

	/// <summary>
	/// Chamado quando a taxa é alterada no relógio de apresentação.
	/// </summary>
	virtual event ICarenMFClockStateSink::Delegate_OnClockSetRate^ OnClockSetRate;



	//Delegates para uso nativo.
private:

	///////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_IMFClockStateSink)//
	///////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClockStart) nativo da classe (CLN_IMFClockStateSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset);
	DelegateNativo_Evento_OnClockStart^ Callback_OnClockStart = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClockStop) nativo da classe (CLN_IMFClockStateSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClockStop(MFTIME hnsSystemTime);
	DelegateNativo_Evento_OnClockStop^ Callback_OnClockStop = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClockPause) nativo da classe (CLN_IMFClockStateSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClockPause(MFTIME hnsSystemTime);
	DelegateNativo_Evento_OnClockPause^ Callback_OnClockPause = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClockRestart) nativo da classe (CLN_IMFClockStateSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClockRestart(MFTIME hnsSystemTime);
	DelegateNativo_Evento_OnClockRestart^ Callback_OnClockRestart = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnClockSetRate) nativo da classe (CLN_IMFClockStateSink) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnClockSetRate(MFTIME hnsSystemTime, float flRate);
	DelegateNativo_Evento_OnClockSetRate^ Callback_OnClockSetRate = nullptr;


	//Handles alocadas de cada Delegate.
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnReadSample).
	/// </summary>
	GCHandle gHandle_Delegate_OnClockStart;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnClockStop).
	/// </summary>
	GCHandle gHandle_Delegate_OnClockStop;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnClockPause).
	/// </summary>
	GCHandle gHandle_Delegate_OnClockPause;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnClockRestart).
	/// </summary>
	GCHandle gHandle_Delegate_OnClockRestart;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnClockSetRate).
	/// </summary>
	GCHandle gHandle_Delegate_OnClockSetRate;


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
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O cliente é responsável por liberar a interface.</param>
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
			System::Console::WriteLine(String::Concat(ICarenMFVideoPresenter::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFVideoPresenter)
public:
	/// <summary>
	/// Recupera o tipo de mídia do apresentador. 
	/// Este método retorna o tipo de mídia que o apresentador define para o tipo de saída do misturador. Descreve o formato da imagem composta.
	/// </summary>
	/// <param name="Param_Out_TipoVideo">Retorna uma interface para o tipo de midia de video do apresentador.</param>
	/// <returns></returns>
	virtual CarenResult GetCurrentMediaType([Out] ICarenMFVideoMediaType^% Param_Out_TipoVideo);

	/// <summary>
	/// Envia uma mensagem para o apresentador de vídeo. As mensagens são usadas para sinalizar ao apresentador que ele deve realizar alguma ação, ou que algum evento ocorreu.
	/// </summary>
	/// <param name="Param_Mensagem">Especifica a mensagem como membro da enumeração CA_MFVP_MESSAGE_TYPE.</param>
	/// <param name="Param_UlParam">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
	/// <returns></returns>
	virtual CarenResult ProcessMessage(CA_MFVP_MESSAGE_TYPE Param_Mensagem, UInt64 Param_UlParam);


	//Métodos da interface proprietaria.
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();


	//Métodos que recebem os eventos da classe nativa(CLN_IMFClockStateSink)
public:
	virtual void EncaminharEvento_OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset);

	virtual void EncaminharEvento_OnClockStop(MFTIME hnsSystemTime);

	virtual void EncaminharEvento_OnClockPause(MFTIME hnsSystemTime);

	virtual void EncaminharEvento_OnClockRestart(MFTIME hnsSystemTime);

	virtual void EncaminharEvento_OnClockSetRate(MFTIME hnsSystemTime, float flRate);
};