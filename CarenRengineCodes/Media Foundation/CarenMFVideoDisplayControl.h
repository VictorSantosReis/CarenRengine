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
#include "../Caren/CarenBuffer.h"
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
/// (Concluido - Fase de Testes) - Classe responsável por controlar como o Vídeo é exbido pelo EVR (Renderizador de Vídeo Aprimorado). 
/// </summary>
public ref class CarenMFVideoDisplayControl :public ICarenMFVideoDisplayControl
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFVideoDisplayControl).
	IMFVideoDisplayControl* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFVideoDisplayControl();

	~CarenMFVideoDisplayControl();


	//Conversões implicitas
public:
	static operator CarenMFVideoDisplayControl^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFVideoDisplayControl^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFVideoDisplayControl();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFVideoDisplayControl*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFVideoDisplayControl::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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





	//Métodos da interface ICarenMFVideoDisplayControl
public:
	/// <summary>
	/// (GetAspectRatioMode) - Consulta como o processador de vídeo avançado (EVR) lida com a relação de aspecto da fonte de vídeo.
	/// </summary>
	/// <param name="Param_Out_AspectRatio">Recebe um ou mais bit de sinalizadores da enumeração: CA_MFVideoAspectRatioMode</param>
	virtual CarenResult GetAspectRatioMode([Out] Enumeracoes::CA_MFVideoAspectRatioMode% Param_Out_AspectRatio);

	/// <summary>
	/// (GetBorderColor) - Obtém a cor da borda para o vídeo.
	/// </summary>
	/// <param name="Param_Out_CorHexadecimalBorda">Recebe o valor que especifica em hexadecimal, uma cor RGB.</param>
	virtual CarenResult GetBorderColor([Out] UInt32% Param_Out_CorHexadecimalBorda);

	/// <summary>
	/// (GetCurrentImage) - Obtém uma cópia da imagem atual sendo exibida pelo processador de vídeo.
	/// </summary>
	/// <param name="Param_Out_BimapInfoHeader">Recebe uma estrutura que contém uma descrição do bitmap</param>
	/// <param name="Param_Out_BufferImagem">Interface que contém um buffer que contém um bitmap independente de dispositivo do Windows compactado (DIB).
	/// O chamador deve liberar a memória para o bitmap chamando: CoTaskMemFree</param>
	/// <param name="Param_Out_BufferLargura">Contém a largura do buffer retornado em: Param_Out_BufferImagem.</param>
	/// <param name="Param_Out_TimeStamp">Recebe o carimbo de data/hora da imagem capturada. O valor é em unidades de 100 nanosegundos.</param>
	virtual CarenResult GetCurrentImage(
		[Out] Estruturas::CA_BITMAPINFOHEADER^% Param_Out_BimapInfoHeader,
		[Out] ICarenBuffer^% Param_Out_BufferImagem,
		[Out] UInt32% Param_Out_BufferLargura,
		[Out] Int64% Param_Out_TimeStamp);

	/// <summary>
	/// (GetFullscreen) - Consulta se o processador de vídeo avançado (EVR) está atualmente no modo de tela cheia.
	/// </summary>
	/// <param name="Param_Out_FullScreen">Recebe o valor que define se o vídeo está sendo renderizado em FullScreen.</param>
	virtual CarenResult GetFullscreen([Out] Boolean% Param_Out_FullScreen);

	/// <summary>
	/// (GetIdealVideoSize) - Obtém o intervalo de tamanhos, que o processador de vídeo avançado (EVR) pode exibir sem degradar 
	/// significativamente a qualidade de imagem ou o desempenho.
	/// </summary>
	/// <param name="Param_Out_Minimo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Minimos) da Largura e Altura (Ideias) para o vídeo.</param>
	/// <param name="Param_Out_Maximo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Maximos) da Largura e Altura (Ideias) para o vídeo.</param>
	virtual CarenResult GetIdealVideoSize(
		[Out] Estruturas::CA_SIZE^% Param_Out_Minimo_VideoSizeIdeal,
		[Out] Estruturas::CA_SIZE^% Param_Out_Maximo_VideoSizeIdeal);

	/// <summary>
	/// (GetNativeVideoSize) - Obtém o tamanho e a taxa de proporção do vídeo, antes de qualquer alongamento pelo (Processador de Vídeo).
	/// </summary>
	/// <param name="Param_Out_VideoSize">Recebe a estrutura que contém a Largura e Altura (Nativas) para o vídeo.</param>
	/// <param name="Param_Out_TaxaProporcaoVideo">Recebe a estrutura que contém a (Taxa de proporção) do vídeo.</param>
	virtual CarenResult GetNativeVideoSize(
		[Out] Estruturas::CA_SIZE^% Param_Out_VideoSize,
		[Out] Estruturas::CA_SIZE^% Param_Out_TaxaProporcaoVideo);

	/// <summary>
	/// (GetRenderingPrefs) - Obtém várias configurações de processamento de vídeo.
	/// </summary>
	/// <param name="Param_Out_Sinalizadores">Recebe um bit ou zero ou mais sinalizadores da enumeração: CA_MFVideoRenderPrefs</param>
	virtual CarenResult GetRenderingPrefs([Out] Enumeracoes::CA_MFVideoRenderPrefs% Param_Out_Sinalizadores);

	/// <summary>
	/// (GetVideoPosition) - Obtém os retângulos de origem e de destino para o Vídeo.
	/// </summary>
	/// <param name="Param_Out_RetanguloNormalized">Recebe uma estrutura que contém o retângulo de origem.</param>
	/// <param name="Param_Out_RetanguloDestino">Recebe uma estrutura com o retângulo de destino atual.</param>
	virtual CarenResult GetVideoPosition(
		[Out] Estruturas::CA_MFVideoNormalizedRect^% Param_Out_RetanguloNormalized,
		[Out] Estruturas::CA_RECT^% Param_Out_RetanguloDestino);

	/// <summary>
	/// (GetVideoWindow) - Obtém a janela de recorte para o vídeo. A janela de recorte é a (Handle) do componente que está
	/// hospedando a renderização do vídeo para o usuário.
	/// </summary>
	/// <param name="Param_Out_HandleJanela">Recebe a handle da janela que a qual o vídeo está sendo renderizado.</param>
	virtual CarenResult GetVideoWindow([Out] IntPtr% Param_Out_HandleJanela);

	/// <summary>
	/// (RepaintSuperfice) - Redesenha o quadro de vídeo atual. Chame esse método sempre que a interface do usuário
	/// sofre uma atualização da interface.
	/// </summary>
	virtual CarenResult RepaintSuperfice();

	/// <summary>
	/// (SetAspectRatioMode) - Especifica como o processador de vídeo avançado (EVR) lida com a relação de aspecto 
	/// da fonte de vídeo.
	/// </summary>
	/// <param name="Param_AspectRatio">Bit a bit ou de um ou mais sinalizadores da enumeração: CA_MFVideoAspectRatioMode</param>
	virtual CarenResult SetAspectRatioMode(Enumeracoes::CA_MFVideoAspectRatioMode Param_AspectRatio);

	/// <summary>
	/// (SetBorderColor) - Define a cor da borda para o vídeo.
	/// </summary>
	/// <param name="Param_ColorRef">Especifica a cor da borda como um valor UInt32</param>
	virtual CarenResult SetBorderColor(UInt32 Param_ColorRef);

	/// <summary>
	/// [Esta API não é suportada e pode ser alterada ou indisponível no futuro.]
	/// (SetFullScreen) - Define o modo de renderização de tela cheia.
	/// Para implementar a reprodução em tela inteira, um aplicativo deve simplesmente redimensionar a janela de vídeo para cobrir toda a área do monitor.Também definir a janela
	/// para ser uma (Janela Superior), para que o aplicativo possa receber todas as mensagens de clique do mouse.
	/// </summary>
	/// <param name="Param_EstadoFullScreen">Se true, o renderizador de vídeo aprimorado (EVR) usará o modo de tela inteira. Se false, o EVR desenha o vídeo na 
	/// janela de recorte fornecido pelo aplicativo.</param>
	virtual CarenResult SetFullScreen(Boolean Param_EstadoFullScreen);

	/// <summary>
	/// (SetRenderingPrefs)Define preferências diversas, relacionadas com a processamento de vídeo.
	/// </summary>
	virtual CarenResult SetRenderingPrefs(Enumeracoes::CA_MFVideoRenderPrefs Param_RenderConfigs);

	/// <summary>
	/// (SetVideoPosition) - Define os retângulos de origem e de destino para o vídeo.
	/// O retângulo de origem define qual parte do vídeo é exibida. Ele é especificado em coordenadas normalizadas. Para obter mais informações, 
	/// consulte estrutura MFVideoNormalizedRect. Para exibir a imagem de vídeo inteira, defina o retângulo de origem como {0, 0, 1, 1}. O retângulo de origem padrão é {0, 0, 1, 1}.
	/// O retângulo de destino define um retângulo dentro da janela de recorte onde o vídeo é exibido. Ele é especificado em pixels, em relação à área do cliente da janela.
	/// Para preencher a janela inteira, defina o retângulo de destino como {0, 0, Largura, Altura}, onde Largura e Altura são dimensões da área do cliente da janela. O retângulo 
	/// de destino padrão é {0, 0, 0, 0}.
	/// </summary>
	/// <param name="Param_RetanguloNormalized">Estrutura que especifica o retângulo origem. Este parâmetro pode ser NULO. Se este parâmetro é NULO, o 
	/// retângulo de origem não é alterado.</param>
	/// <param name="Param_RetanguloDestino">Especifica o retângulo de destino. Este parâmetro pode ser NULL. Se este parâmetro é NULL, o retângulo 
	/// de destino não é alterado.</param>
	virtual CarenResult SetVideoPosition(
		Estruturas::CA_MFVideoNormalizedRect^ Param_RetanguloNormalized,
		Estruturas::CA_RECT^ Param_RetanguloDestino);

	/// <summary>
	/// (SetVideoWindow) - Define a janela de recorte para o vídeo. Está é a janela que vai hospedar o vídeo que será
	/// renderizado para visualização do usuário. A Janela refere-se a (Handle) de um componente na GUI
	/// do usuário.
	/// </summary>
	/// <param name="Param_JanelaVideo"></param>
	virtual CarenResult SetVideoWindow(IntPtr Param_JanelaVideo);
};

