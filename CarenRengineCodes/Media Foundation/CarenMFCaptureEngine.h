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
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenMFCaptureSource.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por controlar um ou mais dispositivos de captura. O mecanismo de captura implementa esta interface. 
/// </summary>
public ref class CarenMFCaptureEngine : public ICarenMFCaptureEngine
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFCaptureEngine).
	IMFCaptureEngine* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFCaptureEngine();
	
	~CarenMFCaptureEngine();

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
			System::Console::WriteLine(String::Concat(ICarenMFCaptureEngine::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFCaptureEngine)
public:
	/// <summary>
	///  Obtém um ponteiro para um dos objetos do Sink de captura. Você pode usar os Sinks de captura para configurar a visualização, gravação ou captura de imagem parada.
	/// </summary>
	/// <param name="Param_CaptureSinkType">Um valor da enumeração CA_MF_CAPTURE_ENGINE_SINK_TYPE que especifica o sink de captura a ser recuperado.</param>
	/// <param name="Param_Ref_Sink">A interface que vai receber o sink de captura especificado. O usuário deve criar e é responsável por liberar quando não foi mais usar.</param>
	virtual CarenResult GetSink(
	CA_MF_CAPTURE_ENGINE_SINK_TYPE Param_CaptureSinkType,
	ICaren^% Param_Ref_Sink);

	/// <summary>
	/// Obtém um ponteiro para o objeto de origem de captura. Use a fonte de captura para configurar os dispositivos de captura. 
	/// </summary>
	/// <param name="Param_Out_CaptureSource">Retorna um ponteiro para a interface ICarenMFCaptureSource. O usuário é responsável por liberar a interface.</param>
	virtual CarenResult GetSource([Out] ICarenMFCaptureSource^% Param_Out_CaptureSource);

	/// <summary>
	/// Inicializa o motor de captura.
	/// Você deve chamar este método uma vez antes de usar o mecanismo de captura. Chamar o método de segunda vez retorna ER_MF_E_INVALIDREQUEST.
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_INITIALIZED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnEventCallback. O usuário deve implementar esta interface. O mecanismo de captura usa esta interface para enviar eventos assíncronos ao chamador.</param>
	/// <param name="Param_Atributos">Você pode usar este parâmetro para configurar o mecanismo de captura. Este parâmetro pode ser Nulo.</param>
	/// <param name="Param_AudioSource">Um ponteiro que especifica um dispositivo de captura de áudio. Este parâmetro pode ser Nulo.</param>
	/// <param name="Param_VideoSource">Um ponteiro que especifica um dispositivo de captura de vídeo. Este parâmetro pode ser Nulo.</param>
	virtual CarenResult Initialize(
	ICarenMFCaptureEngineOnEventCallback^ Param_Callback,
	ICarenMFAttributes^ Param_Atributos,
	ICaren^ Param_AudioSource,
	ICaren^ Param_VideoSource);

	/// <summary>
	/// Inicializa a pré-visualização. 
	/// Antes de chamar esse método, configure o Sink de visualização chamando ICarenMFCaptureSink::AddStream.
	/// Para obter um ponteiro para o Sink de visualização, ligue para o ICarenMFCaptureEngine::GetSink.
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PREVIEW_STARTED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	virtual CarenResult StartPreview();

	/// <summary>
	/// Começa a gravar áudio e/ou vídeo em um arquivo.
	/// Antes de chamar esse método, configure o Sink de gravação chamando IMFCaptureSink::AddStream. Para obter um ponteiro para o Sink de gravação, ligue para o ICarenMFCaptureEngine::GetSink.
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_RECORD_STARTED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	virtual CarenResult StartRecord();

	/// <summary>
	/// Interrompe a visualização.
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PREVIEW_STOPPED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	virtual CarenResult StopPreview();

	/// <summary>
	/// Para de gravar. 
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_RECORD_STOPPED evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	/// <param name="Param_Finalizar">Um valor booleano que especifica se deve finalizar o arquivo de saída. Para criar um arquivo de saída válido, especifique TRUE. Especifique FALSO somente se você quiser interromper a gravação e descartar o arquivo de saída. Se o valor for FALSO,a operação será concluída mais rapidamente, mas o arquivo não será jogável.</param>
	/// <param name="Param_FlushUnprocessedSamples">Um valor booleano que especifica se as amostras não processadas aguardando para serem codificadas devem ser liberadas.</param>
	virtual CarenResult StopRecord(
	Boolean Param_Finalizar,
	Boolean Param_FlushUnprocessedSamples);

	/// <summary>
	/// Captura uma imagem parada do fluxo de vídeo. 
	/// Este método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um MF_CAPTURE_ENGINE_PHOTO_TAKEN evento através do método ICarenMFCaptureEngineOnEventCallback::OnEvent. A operação pode falhar assincronicamente após o sucesso do método. Se assim for, o código de erro é transmitido através do método OnEvent.
	/// </summary>
	virtual CarenResult TakePhoto();
};