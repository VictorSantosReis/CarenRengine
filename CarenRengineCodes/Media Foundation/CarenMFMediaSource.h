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
#include "CarenMFPresentationDescriptor.h"
#include "CarenMFMediaEvent.h" //Inclui PropVariantManager
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
/// (Conluido - Fase de testes) - Fontes de mídia são objetos que geram dados de mídia.Por exemplo, os dados podem vir de um arquivo de vídeo, um fluxo de rede ou um dispositivo de hardware, como uma câmera. 
/// Cada fonte de mídia contém um ou mais fluxos, e entrega de cada fluxo de dados de um tipo, como áudio ou vídeo.
/// </summary>
public ref class CarenMFMediaSource : public ICarenMFMediaSource
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaSource).
	IMFMediaSource* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaSource();

	/// <summary>
	/// Inicializa e cria uma fonte de mídia que agrega uma coleção de fontes de mídia.
	/// </summary>
	/// <param name="Param_SourceCollection">Uma interface (ICarenMFCollection) que contém uma coleção de fontes de mídia para serem agregadas.</param>
	CarenMFMediaSource(ICarenMFCollection^ Param_SourceCollection);

	/// <summary>
	/// Cria uma fonte de mídia para um dispositivo de captura de hardware.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface (ICarenMFAttributes) da loja de atributos, que é usada para selecionar o dispositivo de captura.</param>
	CarenMFMediaSource(ICarenMFAttributes^ Param_Atributos);

	~CarenMFMediaSource();


	//Conversões implicitas
public:
	static operator CarenMFMediaSource^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFMediaSource^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFMediaSource();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFMediaSource*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFMediaSource::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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





	//Métodos da interface ICarenMFMediaSource
public:
	
	/// <summary>
	/// (CreatePresentationDescriptor) - Recupera uma cópia do descritor de apresentação da fonte de mídia. Os aplicativos usam o descritor de apresentação para selecionar fluxos e obter informações sobre o conteúdo de origem.
	/// </summary>
	/// <param name="Param_Out_DescritorApresentação">Recebe a interface para o descritor de apresentação.</param>
	virtual CarenResult CreatePresentationDescriptor([Out] ICarenMFPresentationDescriptor^% Param_Out_DescritorApresentação);
	
	/// <summary>
	/// (GetCharacteristics) - Recupera as características da fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_Caracteristicas">Recebe um OR de bit a bit de zero ou mais sinalizadores da enumeração (CA_MFMEDIASOURCE_CHARACTERISTICS).</param>
	virtual CarenResult GetCharacteristics([Out] Enumeracoes::CA_MFMEDIASOURCE_CHARACTERISTICS% Param_Out_Caracteristicas);
	
	/// <summary>
	/// (Start) - Inicia, procura ou reinicia a fonte de mídia especificando onde iniciar a reprodução.
	/// </summary>
	/// <param name="Param_DescritorApresentação">A interface de ICarenMFPresentationDescriptor de descritor de apresentação da fonte de mídia. Para obter o descritor de apresentação, chamade o método (ICarenMFPresentationDescriptor::CreatePresentationDescriptor). 
	/// Você pode modificar o descritor de apresentação antes de chamar Start, para selecionar ou desmarcar fluxos ou alterar os tipos de mídia.</param>
	/// <param name="Param_GuidTimeFormato">Um GUID que especifica o formato de hora. O formato de hora define as unidades para o parâmetro Param_PosiçãoInicio. Se o valor é NULL, o formato é definido como unidades de 100 nanossegundos. Algumas fontes de 
	/// mídia podem oferecer suporte o formato de hora adicional. Este parâmetro pode ser nulo. Se o valor for nulo, é equivalente a GUID_NULL.</param>
	/// <param name="Param_PosiçãoInicio">Especifica onde iniciar a reprodução. As unidades deste parâmetro são indicadas pelo formato tempo dado em Param_GuidTimeFormato. Se o formato de hora é GUID_NULL, o tipo de variante deve ser VT_I8 ou VT_EMPTY. Use VT_I8 
	/// para especificar uma nova posição inicial, em unidades de 100 nanossegundos. Use VT_EMPTY para começar a partir da posição atual. Outros formatos de hora podem usar outros tipos CA_PROPVARIANT.</param>
	virtual CarenResult Start(ICarenMFPresentationDescriptor^ Param_DescritorApresentação, String^ Param_GuidTimeFormato, Estruturas::CA_PROPVARIANT^ Param_PosiçãoInicio);
	
	/// <summary>
	/// (Pause) - Pausa todos os fluxos ativos na fonte de mídia.
	/// </summary>
	virtual CarenResult Pause();

	/// <summary>
	/// (Stop) - Interrompe todos os fluxos ativos na fonte de mídia.
	/// </summary>
	virtual CarenResult Stop();

	/// <summary>
	/// (Shutdown) - Desliga a fonte de mídia e libera os recursos que ela está usando.
	/// </summary>
	virtual CarenResult Shutdown();



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

