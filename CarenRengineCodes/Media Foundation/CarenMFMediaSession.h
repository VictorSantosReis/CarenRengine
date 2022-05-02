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
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenMFActivate.h"
#include "CarenMFClock.h"
#include "CarenMFTopology.h"
#include "CarenMFMediaEvent.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// Classe responsável por fornecer controles de reprodução para conteúdo protegido e desprotegido. A sessão de mídia e os objetos de sessão do caminho de mídia protegida (PMP) 
/// expõem essa classe(Interface).
/// </summary>
public ref class CarenMFMediaSession :public ICarenMFMediaSession
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaSession).
	IMFMediaSession* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaSession();

	/// <summary>
	/// Inicializa e cria a Sessão de Mídia no processo do aplicativo.
	/// </summary>
	/// <param name="Param_ConfigAtributos">Uma interface com os atributos de configuração para a Media Session. Este parâmetro pode ser NULO.</param>
	CarenMFMediaSession(ICarenMFAttributes^ Param_ConfigAtributos);

	/// <summary>
	/// Inicializa e cria uma instância da Sessão de Mídia dentro de um processo PMP (Protected Media Path, caminho de mídia protegido).
	/// </summary>
	/// <param name="Param_Fags">Um membro da enumeração CA_MFPMPSESSION_CREATION_FLAGS que especifica como criar o objeto de sessão.</param>
	/// <param name="Param_ConfigAtributos">Uma interface com os atributos de configuração para a Media Session. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_Ativador">Recebe a interface ICarenMFActivate ou o valor NULO. Se não-NULO, o chamador deve liberar a interface.</param>
	CarenMFMediaSession(CA_PMPSESSION_CREATION_FLAGS Param_Fags, ICarenMFAttributes^ Param_ConfigAtributos, ICarenMFActivate^ Param_Out_Ativador);

	~CarenMFMediaSession();


	//Conversões implicitas
public:
	static operator CarenMFMediaSession^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFMediaSession^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFMediaSession();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFMediaSession*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;


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
			System::Console::WriteLine(String::Concat(ICarenMFMediaSession::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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



	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// (ClearTopologies) - Limpa todas as apresentações que estão enfileiradas para reprodução na sessão de mídia.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento (MESessionTopologiesCleared).
	/// </summary>
	virtual CarenResult ClearTopologies();

	/// <summary>
	/// (Close) - Fecha a sessão de mídia e libera todos os recursos que ele está usando.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento(MESessionClosed) .
	/// </summary>
	virtual CarenResult Close();

	/// <summary>
	/// (GetClock) - Recupera o relógio de apresentação da sessão de mídia.
	/// </summary>
	/// <param name="Param_Out_Relogio">Recebe o ponteiro para o relogio de apresentação. O chamador deve liberar a interface.</param>
	virtual CarenResult GetClock([Out] ICarenMFClock^% Param_Out_Relogio);

	/// <summary>
	/// (GetFullTopology) - Obtém uma topologia da sessão de mídia.
	/// </summary>
	/// <param name="Param_Flags">Zero ou mais sinalizadores da enumeração CA_MESESSION_GETFULLTOPOLOGY_FLAGS .</param>
	/// <param name="Param_TopoId">O identificador da topologia. Este parâmetro será ignorado se o (Param_Flags) parâmetro contém o MFSESSION_GETFULLTOPOLOGY_CURRENT sinalizador.</param>
	/// <param name="Param_Out_TopologiaCompleta">Recebe um ponteiro para a topologia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetFullTopology(Enumeracoes::CA_MFSESSION_GETFULLTOPOLOGY_FLAGS Param_Flags, UInt64 Param_TopoId, [Out] ICarenMFTopology^% Param_Out_TopologiaCompleta);

	/// <summary>
	/// (GetSessionCapabilities) - Recupera os recursos da sessão de mídia, com base na apresentação atual.
	/// </summary>
	/// <param name="Param_Out_Recursos">Recebe um OU de bit ou de ZERO ou mais dos sinalizadores da enumeração(CA_MFSESSIONCAP).</param>
	virtual CarenResult GetSessionCapabilities([Out] Enumeracoes::CA_MFSESSIONCAP% Param_Out_Recursos);

	/// <summary>
	/// (Pause) - Pausa a sessão de mídia.
	/// Este método pausa o relógio de apresentação. Esse método é assíncrono.Quando a operação for concluída, a sessão de mídia enviará um evento MESessionPaused.
	/// </summary>
	virtual CarenResult Pause();

	/// <summary>
	/// (SetTopology) - Define uma topologia na sessão de mídia.
	/// </summary>
	/// <param name="Param_Flags">Os flags que determinam o comportamento do método.</param>
	/// <param name="Param_Topologia">Um ponteiro para a topologia a ser definida.</param>
	virtual CarenResult SetTopology(Enumeracoes::CA_MFSESSION_SETTOPOLOGY_FLAGS Param_Flags, ICarenMFTopology^ Param_Topologia);

	/// <summary>
	/// (Shutdown) - Desliga a sessão de mídia e libera todos os recursos usados pela sessão de mídia.
	/// Chame esse método quando você terminar de usar a sessão de mídia, antes da chamada final para ICaren::LiberarReferencia. Caso contrário, seu aplicativo irá vazar memória.
	/// </summary>
	virtual CarenResult Shutdown();

	/// <summary>
	/// (Start) - Inicia a sessão de mídia.
	/// Quando esse método é chamado, a sessão de mídia inicia o relógio de apresentação e começa a processar exemplos de mídia. Esse método é assíncrono. Quando o método for concluído, 
	/// a sessão de mídia envia o evento MESessionStarted.
	/// </summary>
	/// <param name="Param_GuidFormatoTempo">um GUID que especifica o formato de hora para o (Param_PosicaoInicio) parâmetro. Este parâmetro pode ser NULO. O valor NULO é equivalente 
	/// a passar em GUID_NULL.</param>
	/// <param name="Param_PosicaoInicio">Uma CA_PROPVARIANT que especifica a posição inicial para reprodução. O significado e o tipo de dados desse parâmetro são indicados pelo 
	/// (Param_GuidFormatoTempo) parâmetro.</param>
	virtual CarenResult Start(String^ Param_GuidFormatoTempo, Estruturas::CA_PROPVARIANT^ Param_PosicaoInicio);

	/// <summary>
	/// (Stop) - Interrompe a sessão de mídia.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento MESessionStopped. 
	/// </summary>
	virtual CarenResult Stop();



	//Métodos da interface (ICarenMFMediaEventGenerator)
public:
	/// <summary>
	/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
	/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
	/// dependerá do valor de Param_Flags.
	/// </summary>
	/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult GetEvent(Enumeracoes::CA_MF_GET_FLAGS_EVENT Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
	/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
	/// </summary>
	/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
	/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
	/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
	virtual CarenResult BeginGetEvent(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido);

	/// <summary>
	/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
	/// </summary>
	/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult EndGetEvent(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (QueueEvent) - Coloca um novo evento na fila do objeto.
	/// </summary>
	/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.GetType).</param>
	/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.GetExtendedType) do evento.</param>
	/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetStatus) do evento.</param>
	/// <param name="Param_Dados">uma CA_PROPVARIANT que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetValue) do evento.</param>
	virtual CarenResult QueueEvent(Enumeracoes::CA_MediaEventType Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PROPVARIANT^ Param_Dados);
};

