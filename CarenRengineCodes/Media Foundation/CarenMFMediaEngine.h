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
#include "CarenMFMediaTimeRange.h"
#include "CarenMFMediaError.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por habilitar um aplicativo para reprodução de arquivos de áudio ou vídeo. 
/// </summary>
public ref class CarenMFMediaEngine : public ICarenMFMediaEngine
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaEngine).
	IMFMediaEngine* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaEngine();
	
	~CarenMFMediaEngine();

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
			System::Console::WriteLine(String::Concat(ICarenMFMediaEngine::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFMediaEngine)
public:
	/// <summary>
	/// Pergunta o quão provável é que o Media Engine possa reproduzir um tipo especificado de recurso de mídia.
	/// </summary>
	/// <param name="Param_TipoMime">Uma string que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
	/// <param name="Param_Out_CanPlay">Recebe um valor de enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
	virtual CarenResult CanPlayType(
	String^ Param_TipoMime,
	[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_CanPlay);

	/// <summary>
	///Pergunta se o Media Engine inicia automaticamente a reprodução.
	/// </summary>
	/// <param name="Param_Out_AutoPlay">Recebe um valor booleano que indica se a reprodução é iniciada automaticamente.</param>
	virtual void GetAutoPlay([Out] Boolean% Param_Out_AutoPlay);

	/// <summary>
	/// Consulta quantos dados de recursos o mecanismo de mídia bufferou.
	/// </summary>
	/// <param name="Param_Out_Buffered">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
	virtual CarenResult GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered);

	/// <summary>
	/// Obtém a URL do recurso de mídia atual ou uma sequência vazia se nenhum recurso de mídia estiver presente.
	/// </summary>
	/// <param name="Param_Out_Url">Recebe uma String que contém a URL do recurso de mídia atual. Se não houver recurso de mídia, Param_Out_Url recebe uma String vazia.</param>
	virtual CarenResult GetCurrentSource([Out] String^% Param_Out_Url);

	/// <summary>
	/// Obtém a posição de reprodução atual.
	/// </summary>
	/// <param name="Param_Out_PosicaoAtual">Obtém o valor da posição atual da reprodução.</param>
	virtual void GetCurrentTime([Out] double% Param_Out_PosicaoAtual);

	/// <summary>
	/// Obtém a taxa de reprodução padrão.
	/// </summary>
	/// <param name="Param_Out_DefaultRate">Obtém o valor que indica a taxa de reprodução padrão.</param>
	virtual void GetDefaultPlaybackRate([Out] double% Param_Out_DefaultRate);

	/// <summary>
	/// Obtém a duração do recurso de mídia.
	/// </summary>
	/// <param name="Param_Out_Duracao">Recupera o valor da duração do recurso de mídia.</param>
	virtual void GetDuration([Out] double% Param_Out_Duracao);

	/// <summary>
	/// Obtém o status de erro mais recente.
	/// </summary>
	/// <param name="Param_Out_Error">Recebe um ponteiro para a interface ICarenMFMediaError ou para o valor NULO. Se o valor não for NULO, o chamador deve liberar a interface.</param>
	virtual CarenResult GetError([Out] ICarenMFMediaError^% Param_Out_Error);

	/// <summary>
	/// Pergunta se o Media Engine fará a reprodução em loop.
	/// </summary>
	/// <param name="Param_Out_Loop">Obtém o valor booleano que indica o status da reprodução em loop.</param>
	virtual void GetLoop([Out] Boolean% Param_Out_Loop);

	/// <summary>
	/// Pergunta se o áudio está silenciado.
	/// </summary>
	/// <param name="Param_Out_Muted">Obtém um valor booleano que indica se o áudio está silenciado.</param>
	virtual void GetMuted([Out] Boolean% Param_Out_Muted);

	/// <summary>
	/// Obtém o tamanho do quadro de vídeo, ajustado para proporção.
	/// </summary>
	/// <param name="Param_Out_X">Retorna a Largura(X) do vídeo.</param>
	/// <param name="Param_Out_Y">Retorna a Altura(Y) do vídeo.</param>
	virtual CarenResult GetNativeVideoSize(
	[Out] UInt32% Param_Out_X, 
	[Out] UInt32% Param_Out_Y);

	/// <summary>
	/// Obtém o estado atual da rede do mecanismo de mídia.
	/// </summary>
	/// <param name="Param_Out_StateNetwork">Retornar um valor da enumeração CA_MF_MEDIA_ENGINE_NETWORK que indica o status da rede.</param>
	virtual void GetNetworkState([Out] CA_MF_MEDIA_ENGINE_NETWORK% Param_Out_StateNetwork);

	/// <summary>
	/// Obtém a taxa de reprodução atual.
	/// </summary>
	/// <param name="Param_Out_PlaybackRate">Obtém um valor que indica a taxa de reprodução atual.</param>
	virtual void GetPlaybackRate([Out] double% Param_Out_PlaybackRate);

	/// <summary>
	/// Obtém os intervalos de tempo que foram prestados.
	/// </summary>
	/// <param name="Param_Out_Played">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
	virtual CarenResult GetPlayed([Out] ICarenMFMediaTimeRange^% Param_Out_Played);

	/// <summary>
	/// Recebe a bandeira de pré-carga.
	/// </summary>
	/// <param name="Param_Out_Preload">Recebe um valor da enumeração CA_MF_MEDIA_ENGINE_PRELOAD.</param>
	virtual void GetPreload([Out] CA_MF_MEDIA_ENGINE_PRELOAD% Param_Out_Preload);

	/// <summary>
	/// Obtém o estado pronto, o que indica se o recurso de mídia atual pode ser renderizado.
	/// </summary>
	/// <param name="Param_Out_RadyState">Obtém uma ou mais bandeiras da enumeração CA_MF_MEDIA_ENGINE_READY que indica se o recurso pode ser renderizado.</param>
	virtual void GetReadyState([Out] CA_MF_MEDIA_ENGINE_READY% Param_Out_RadyState);

	/// <summary>
	/// Obtém os intervalos de tempo aos quais o Media Engine pode procurar atualmente.
	/// </summary>
	/// <param name="Param_Out_Seekable">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
	virtual CarenResult GetSeekable([Out] ICarenMFMediaTimeRange^% Param_Out_Seekable);

	/// <summary>
	/// Obtém a posição inicial de reprodução.
	/// </summary>
	/// <param name="Param_Out_PosicaoInicial">Obtém um valor que indica a posição inicial de reprodução.</param>
	virtual void GetStartTime([Out] double% Param_Out_PosicaoInicial);

	/// <summary>
	/// Obtém a proporção de imagem do fluxo de vídeo.
	/// </summary>
	/// <param name="Param_Out_X">Retonar o valor (X) do Aspect Ratio do fluxo do vídeo.</param>
	/// <param name="Param_Out_Y">Retonar o valor (Y) do Aspect Ratio do fluxo do vídeo.</param>
	virtual CarenResult GetVideoAspectRatio(
	[Out] UInt32% Param_Out_X,
	[Out] UInt32% Param_Out_Y);

	/// <summary>
	/// Obtém o nível de volume de áudio.
	/// </summary>
	/// <param name="Param_Out_Volume">Obtém um valor que indica o nível de volume do áudio.</param>
	virtual void GetVolume([Out] double% Param_Out_Volume);

	/// <summary>
	/// Pergunta se o recurso de mídia atual contém um fluxo de áudio.
	/// </summary>
	/// <param name="Param_Out_AudioPresente">Retornar um booleano TRUE se um fluxo de áudio estiver disponível na mídia. Caso contrario, FALSE.</param>
	virtual void HasAudio([Out] Boolean% Param_Out_AudioPresente);

	/// <summary>
	/// Pergunta se o recurso de mídia atual contém um fluxo de vídeo.
	/// </summary>
	/// <param name="Param_Out_VideoPresente">Retornar um booleano TRUE se um fluxo de vídeo estiver disponível na mídia. Caso contrario, FALSE.</param>
	virtual void HasVideo([Out] Boolean% Param_Out_VideoPresente);

	/// <summary>
	/// Verifica se a reprodução terminou.
	/// </summary>
	/// <param name="Param_Out_ReproducaoTerminada">Retornar um booleano TRUE se a reprodução tiver terminado. Caso contrario, FALSE.</param>
	virtual void IsEnded([Out] Boolean% Param_Out_ReproducaoTerminada);

	/// <summary>
	/// Verifica se a reprodução está pausada no momento.
	/// </summary>
	/// <param name="Param_Out_PauseStatus">Retorna um valor booleano indicando se a reprodução está pausada.</param>
	virtual void IsPaused([Out] Boolean% Param_Out_PauseStatus);

	/// <summary>
	/// Verifica se o Media Engine está atualmente buscando uma nova posição de reprodução.
	/// </summary>
	/// <param name="Param_Out_BuscandoPosicao">Retornar um valor booleano que indica se a Media Engine está buscando uma nova posição.</param>
	virtual void IsSeeking([Out] Boolean% Param_Out_BuscandoPosicao);

	/// <summary>
	/// Carrega a fonte de mídia atual.
	/// </summary>
	virtual CarenResult Load();

	/// <summary>
	/// Consulta o Media Engine para saber se um novo quadro de vídeo está pronto.
	/// </summary>
	/// <param name="Param_Out_TempoApresentacaoFrame">Retornar um valor valido e maior que 0 para o tempo de apresentação do frame se ele estiver pronto para renderização.</param>
	virtual CarenResult OnVideoStreamTick([Out] Int64% Param_Out_TempoApresentacaoFrame);

	/// <summary>
	/// Pausa a reprodução.
	/// </summary>
	virtual CarenResult Pause();

	/// <summary>
	/// Começa a reprodução.
	/// </summary>
	virtual CarenResult Play();

	/// <summary>
	/// Especifica se o Media Engine inicia automaticamente a reprodução.
	/// </summary>
	/// <param name="Param_AutoPlay">Um valor booleano que indica se vai reproduzir automaticamente.</param>
	virtual CarenResult SetAutoPlay(Boolean Param_AutoPlay);

	/// <summary>
	/// Busca uma nova posição de reprodução.
	/// </summary>
	/// <param name="Param_NovaPosicao">A novao posição a ser buscada.</param>
	virtual CarenResult SetCurrentTime(double Param_NovaPosicao);

	/// <summary>
	/// Define a taxa de reprodução padrão.
	/// </summary>
	/// <param name="Param_TaxaReproducaoDefault">O novo valor para taxa de reprodução padrão.</param>
	virtual CarenResult SetDefaultPlaybackRate(double Param_TaxaReproducaoDefault);

	/// <summary>
	/// Define o código de erro atual.
	/// </summary>
	/// <param name="Param_Error">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_ERR.</param>
	virtual CarenResult SetErrorCode(CA_MF_MEDIA_ENGINE_ERR Param_Error);

	/// <summary>
	/// Especifica se o Media Engine faz loop de reprodução.
	/// </summary>
	/// <param name="Param_Loop">Um valor booleano que vai indicar o loop de reprodução.</param>
	virtual CarenResult SetLoop(Boolean Param_Loop);

	/// <summary>
	/// Silencia ou ativar o áudio.
	/// </summary>
	/// <param name="Param_Mudo">Um valor booleano que vai definir se vai ou não silenciar o áudio.</param>
	virtual CarenResult SetMuted(Boolean Param_Mudo);

	/// <summary>
	/// Define a taxa de reprodução atual.
	/// </summary>
	/// <param name="Param_TaxaReproducaoAtual">Um valor para a nova taxa de reprodução atual.</param>
	virtual CarenResult SetPlaybackRate(double Param_TaxaReproducaoAtual);

	/// <summary>
	/// Defina o sinalizador de pré-carga.
	/// </summary>
	/// <param name="Param_Preload">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_PRELOAD que define o Preload da midia.</param>
	virtual CarenResult SetPreload(CA_MF_MEDIA_ENGINE_PRELOAD Param_Preload);

	/// <summary>
	/// Define a URL de um recurso de mídia.
	/// </summary>
	/// <param name="Param_Url">Uma string conténdo a URL para o recurso de mídia.</param>
	virtual CarenResult SetSource(String^ Param_Url);

	/// <summary>
	/// Define uma lista de fontes de mídia.
	/// </summary>
	/// <param name="Param_ElementosMidia">Um ponteiro para a interface ICarenMFMediaEngineSrcElements. O chamador deve implementar esta interface.</param>
	virtual CarenResult SetSourceElements(ICarenMFMediaEngineSrcElements^ Param_ElementosMidia);

	/// <summary>
	/// Define o nível de volume de áudio.
	/// </summary>
	/// <param name="Param_Volume">O novo valor para o nível de volume de áudio da mídia.</param>
	virtual CarenResult SetVolume(double Param_Volume);

	/// <summary>
	/// (Shutdown) - Desliga o Media Engine e libera os recursos que está usando.
	/// </summary>
	virtual CarenResult Shutdown();

	/// <summary>
	/// Copia o quadro de vídeo atual para um DXGI ou WIC bitmap.
	/// No modo frame-server, chame este método para colocar o quadro de vídeo em uma superfície DXGI ou WIC. O aplicativo pode chamar esse método a qualquer momento após o 
	/// Media Engine carregar um recurso de vídeo. Normalmente, no entanto, o aplicativo chama O ICarenMFMediaEngine::OnVideoStreamTick primeiro, para determinar se um novo quadro 
	/// está disponível. Se o OnVideoStreamTick retornar SS_OK, o aplicativo então chamará TransferirFrameVideo.
	/// Para conteúdo protegido, ligue para o método ICarenMFMediaEngineProtectedContent::TransferirFrameVideo em vez deste método.
	/// </summary>
	/// <param name="Param_SuperficeDestino">Um ponteiro para a interface da superfície de destino.</param>
	/// <param name="Param_RetanguloOrigem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem</param>
	/// <param name="Param_RetanguloDestino">Uma estrutura CA_RECT que especifica o retângulo de destino.</param>
	/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
	virtual CarenResult TransferVideoFrame(
	ICaren^ Param_SuperficeDestino, 
	CA_MFVideoNormalizedRect^ Param_RetanguloOrigem,
	CA_RECT^ Param_RetanguloDestino,
	CA_MFARGB^ Param_CorBorda);
};