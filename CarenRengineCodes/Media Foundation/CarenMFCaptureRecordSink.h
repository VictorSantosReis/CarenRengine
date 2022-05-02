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
#include "CarenMFMediaType.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por controlar um Sink(Dissipador) de gravação. O Record Sink cria arquivos compactados de áudio/vídeo ou fluxos de áudio/vídeo comprimidos. 
/// </summary>
public ref class CarenMFCaptureRecordSink : public ICarenMFCaptureRecordSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFCaptureRecordSink).
	IMFCaptureRecordSink* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFCaptureRecordSink();
	
	~CarenMFCaptureRecordSink();


	//Conversões implicitas
public:
	static operator CarenMFCaptureRecordSink^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFCaptureRecordSink^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFCaptureRecordSink();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFCaptureRecordSink*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFCaptureRecordSink::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFCaptureRecordSink)
public:
	/// <summary>
	/// Obtém a rotação que está sendo aplicada ao fluxo de vídeo gravado.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_Out_RotationValue">Recebe a rotação da imagem, em graus.</param>
	virtual CarenResult GetRotation(
	UInt32 Param_StreamIndex,
	[Out] UInt32% Param_Out_RotationValue);

	/// <summary>
	/// Define um sink de mídia personalizada para gravação.
	/// Este método substitui a seleção padrão do sink de mídia para gravação.
	/// </summary>
	/// <param name="Param_MediaSink">Uma interface ICarenMFMediaSink para o sink da mídia.</param>
	virtual CarenResult SetCustomSink(ICarenMFMediaSink^ Param_MediaSink);

	/// <summary>
	/// Especifica um fluxo de byte que receberá os dados para a gravação.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputFileName ou ICarenMFCaptureRecordSink::SetSampleCallback.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O fluxo de byte deve suportar escrita.</param>
	/// <param name="Param_GuidContainer">Um GUID que especifica o tipo de recipiente de arquivo. Os valores possíveis estão documentados no atributo MF_TRANSCODE_CONTAINERTYPE.</param>
	virtual CarenResult SetOutputByteStream(
	ICarenMFByteStream^ Param_ByteStream,
	String^ Param_GuidContainer);

	/// <summary>
	/// Especifica o nome do arquivo de saída para a gravação.
	/// O mecanismo de captura usa a extensão do nome do arquivo para selecionar o tipo de contêiner para o arquivo de saída. Por exemplo, se a extensão do nome do arquivo for ." mp4", o mecanismo de captura cria um arquivo MP4.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetSampleCallback.
	/// </summary>
	/// <param name="Param_Url">Uma String que contém a URL do arquivo de saída.</param>
	virtual CarenResult SetOutputFileName(String^ Param_Url);

	/// <summary>
	/// Rotaciona o fluxo de vídeo gravado.
	/// </summary>
	/// <param name="Param_StreamIndex">O índice baseado em zero do fluxo para girar. Você deve especificar uma transmissão de vídeo.</param>
	/// <param name="Param_RotationValue">A quantidade para girar o vídeo, em graus. Os valores válidos são 0, 90, 180 e 270. O valor zero restaura o vídeo à sua orientação original.</param>
	virtual CarenResult SetRotation(
	UInt32 Param_StreamIndex,
	UInt32 Param_RotationValue);

	/// <summary>
	/// Define um Callback para receber os dados de gravação de um fluxo.
	/// Chamar este método substitui qualquer chamada anterior para ICarenMFCaptureRecordSink::SetOutputByteStream ou ICarenMFCaptureRecordSink::SetOutputFileName.
	/// </summary>
	/// <param name="Param_StreamSinkIndex">O índice baseado em zero do fluxo. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
	/// <param name="Param_Callback">Uma interface ICarenMFCaptureEngineOnSampleCallback. O usuário deve implementar esta interface.</param>
	virtual CarenResult SetSampleCallback(
	UInt32 Param_StreamSinkIndex,
	ICarenMFCaptureEngineOnSampleCallback^ Param_Callback);


	//Métodos da interface(ICarenMFCaptureSink)
public:
	/// <summary>
	/// Conecta um fluxo da fonte de captura a esta pia de captura.
	/// </summary>
	/// <param name="Param_SourceStreamIndex">O fluxo de origem para se conectar. Esse valor pode ser um dois valores da enumeração (MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX) ou O índice baseado em zero de um fluxo. Para obter o número de fluxos, ligue para o método ICarenMFCaptureSource::GetDeviceStreamCount.</param>
	/// <param name="Param_MediaType">Uma ICarenMFMediaType que especifica o formato desejado do fluxo de saída.</param>
	/// <param name="Param_Atributos">Uma interface ICarenMFAttributes para os atributos. Para fluxos comprimidos, você pode usar este parâmetro para configurar o codificador. Este parâmetro também pode ser Nulo.</param>
	/// <param name="Param_Out_SinkStreamIndex">Recebe o índice do novo fluxo na pia de captura. Observe que este índice não corresponderá necessariamente ao valor do (Param_SourceStreamIndex).</param>
	virtual CarenResult AddStream(
		UInt32 Param_SourceStreamIndex,
		ICarenMFMediaType^ Param_MediaType,
		ICarenMFAttributes^ Param_Atributos,
		[Out] UInt32% Param_Out_SinkStreamIndex);

	/// <summary>
	/// Obtém o formato de saída para um fluxo nesta pia de captura.
	/// </summary>
	/// <param name="Param_SinkStreamIndex">O índice baseado em zero do fluxo para consulta. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
	/// <param name="Param_Out_MediaType">Retorna uma interface ICarenMFMediaType com o formato do tipo de midia no fluxo especificado. O usuário é responsável por liberar a interface.</param>
	virtual CarenResult GetOutputMediaType(
		UInt32 Param_SinkStreamIndex,
		[Out] ICarenMFMediaType^% Param_Out_MediaType);

	/// <summary>
	/// Consulte o objeto Sink Writer(ICarenMFSourceReader) subjacente para uma interface.
	/// </summary>
	/// <param name="Param_SinkStreamIndex">O índice baseado em zero do fluxo para consulta. O índice é devolvido no parâmetro (Param_Out_SinkStreamIndex) do método ICarenMFCaptureSink::AddStream.</param>
	/// <param name="Param_GuidService">Um identificador de serviço GUID. Atualmente, o valor deve ser Nulo.</param>
	/// <param name="Param_RIID">Um identificador de serviço GUID. Atualmente, o valor deve ser IID_IMFSinkWriter.</param>
	/// <param name="Param_Ref_Interface">Retorna um ponteiro para a interface solicitada. O usuário é responsável por criar e liberar a interface.</param>
	virtual CarenResult GetService(
		UInt32 Param_SinkStreamIndex,
		String^ Param_GuidService,
		String^ Param_RIID,
		ICaren^% Param_Ref_Interface);

	/// <summary>
	/// Prepara o sink de captura carregando quaisquer componentes de pipeline necessários, como codificadores, processadores de vídeo e coletores de mídia.
	/// Chamar esse método é opcional. Este método dá ao aplicativo a oportunidade de configurar os componentes do pipeline antes de serem usados. O método é assíncrono. Se o método retornar um código de sucesso, o chamador receberá um evento MF_CAPTURE_SINK_PREPARED por meio do método ICarenMFCaptureEngineOnEventCallback::OnEvent. Depois que esse evento for recebido, chame ICarenMFCaptureSink::GetService para configurar componentes individuais.
	/// </summary>
	virtual CarenResult Prepare();

	/// <summary>
	/// Remove todos os fluxos do sink de captura. 
	/// Você pode usar este método para reconfigurar o sink.
	/// </summary>
	virtual CarenResult RemoveAllStreams();
};