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
#include "../SDK_DXGI.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenDXGIOutput.h"

//Importa o namespace que contém as interfaces do Microsoft DirectX Graphics Infrastructure(DXGI).
using namespace CarenRengine::DXGI;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Teste) - Classe responsável por fornecer recursos de apresentação que são aprimorados a partir de IDXGISwapChain. Esses recursos de apresentação consistem em especificar retângulos 
/// sujos e retângulo de rolagem para otimizar a apresentação.
/// </summary>
public ref class CarenDXGISwapChain1 : public ICarenDXGISwapChain1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGISwapChain1).
	IDXGISwapChain1* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenDXGISwapChain1();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenDXGISwapChain1">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenDXGISwapChain1^% Param_Out_CarenDXGISwapChain1)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenDXGISwapChain1 = gcnew CarenDXGISwapChain1();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
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
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();




	//Métodos da interface(ICarenDXGISwapChain1)
public:
	/// <summary>
	/// (GetBackgroundColor) - Recupera a cor de fundo da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Cor">Retorna uma estrutura que contém as informações de cor do Background.</param>
	virtual CarenResult GetBackgroundColor([Out] CA_DXGI_RGBA^% Param_Out_Cor);

	/// <summary>
	/// (GetCoreWindow) - Recupera o objeto CoreWindow subjacente para este objeto de cadeia de swap.
	/// </summary>
	/// <param name="Param_RIID">Um ponteiro para o identificador globalmente único(GUID) do objeto CoreWindow que é referenciado pelo parâmetro Param_Out_CoreWindow.</param>
	/// <param name="Param_Out_CoreWindow">Retorna o ponteiro do objeto para a CoreWindow.  O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetCoreWindow(String^ Param_RIID, ICaren^ Param_Out_CoreWindow);

	/// <summary>
	/// (GetDesc1) - Obtém uma descrição da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Desc">Retorna uma estrutura que contém a descrição da cadeia de Swap.</param>
	virtual CarenResult GetDesc1([Out] CA_DXGI_SWAP_CHAIN_DESC1^% Param_Out_Desc);

	/// <summary>
	/// (GetFullscreenDesc) - Obtém uma descrição de uma cadeia de troca em tela cheia.
	/// </summary>
	/// <param name="Param_Out_DescFullScreenSwap">Retorna uma estrutura que contém a descrição no modo FullScreen na cadeia de Swap.</param>
	virtual CarenResult GetFullscreenDesc([Out] CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^% Param_Out_DescFullScreenSwap);

	/// <summary>
	/// (GetHwnd) - Recupera o HWND subjacente para este objeto de cadeia de swap.
	/// </summary>
	/// <param name="Param_Out_HWND">Retorna um ponteiro para o HWND do objeto de cadeia de Swap.</param>
	virtual CarenResult GetHwnd([Out] IntPtr% Param_Out_HWND);

	/// <summary>
	/// (GetRestrictToOutput) - Obtém a saída (o monitor de exibição) ao qual você pode restringir o conteúdo de uma operação atual.
	/// </summary>
	/// <param name="Param_Out_Saida">Um ponteiro para um buffer que recebe um ponteiro para a interface IDXGIOutput para a saída de restrição.  Um aplicativo passa este ponteiro para 
	/// ICarenDXGIOutput em uma chamada para o ICarenDXGIFactory2::CreateSwapChainForHwnd, ICarenDXGIFactory2::CreateSwapChainForCoreWindow, ou ICarenDXGIFactory2::CreateSwapChainForComposition</param>
	virtual CarenResult GetRestrictToOutput([Out] ICarenDXGIOutput^% Param_Out_Saida);

	/// <summary>
	/// (GetRotation) - Obtém a rotação dos buffers traseiros para a cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Rotacao">Retorna uma enumeração que define a rotação do Buffer Traseiro(BackBuffer).</param>
	virtual CarenResult GetRotation([Out] CA_DXGI_MODE_ROTATION% Param_Out_Rotacao);

	/// <summary>
	/// (IsTemporaryMonoSupported) - Determina se uma cadeia de swap suporta "mono temporário".
	/// </summary>
	/// <param name="Param_Out_Suporte">Retorna um Booleano que define o suporte ao mono.</param>
	virtual CarenResult IsTemporaryMonoSupported([Out] Boolean% Param_Out_Suporte);

	/// <summary>
	/// (Present1) - Apresenta um Frame a tela de exibição.
	/// </summary>
	/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
	/// <param name="Param_FlagsApresentacao">Um valor inteiro que contém opções de apresentação em cadeia de swaps.</param>
	/// <param name="Param_ParametrosApresentacao">uma estrutura CA_DXGI_PRESENT_PARAMETERS que descreve retângulos atualizados e rolar informações do quadro para apresentar.</param>
	virtual CarenResult Present1(UInt32 Param_IntervaloSincronizacao, CA_DXGI_PRESENT Param_FlagsApresentacao, CA_DXGI_PRESENT_PARAMETERS^ Param_ParametrosApresentacao);

	/// <summary>
	/// (SetBackgroundColor) - Muda a cor de fundo da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Cor">A nova cor para o Background do buffer traseiro.</param>
	virtual CarenResult SetBackgroundColor(CA_DXGI_RGBA^ Param_Cor);

	/// <summary>
	/// (SetRotation) - Define a rotação dos buffers de volta para a cadeia de swap.
	/// </summary>
	/// <param name="Param_Rotacao">A nova rotação dos Buffers Traseiro(BackBuffers).</param>
	virtual CarenResult SetRotation(CA_DXGI_MODE_ROTATION Param_Rotacao);



	//Métodos da interface(ICarenDXGISwapChain)
public:
	/// <summary>
	/// (GetBuffer) - Acessa um dos buffers de volta da cadeia de swaps.
	/// </summary>
	/// <param name="Param_IndexBuffer">O Indince para o buffer de volta(Back-Buffer).</param>
	/// <param name="Param_RiidInterface">O tipo de interface usada para manipular o buffer.</param>
	/// <param name="Param_Out_InterfaceBuffer">Retorna a interface que gerencia o Buffer de volta(Back-Buffer). O Usuário é responsável por criar a interface que será retornada.</param>
	virtual CarenResult GetBuffer(UInt32 Param_IndexBuffer, String^ Param_RiidInterface, ICaren^ Param_Out_InterfaceBuffer);

	/// <summary>
	/// (GetContainingOutput) - Obtém a saída (o monitor de exibição) que contém a maior parte da área do cliente da janela alvo.
	/// Se o método for bem-sucedido, a interface de saída será preenchida e sua contagem de referência incrementada. Quando você terminar com ele, não se esqueça de liberar a interface para evitar um vazamento de memória.
	/// </summary>
	/// <param name="Param_Out_MonitorSaida">Retorna a interface para o monitor de exbicão de saida.</param>
	virtual CarenResult GetContainingOutput([Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

	/// <summary>
	/// (GetDesc) - Obtém uma descrição da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_DescricaoCadeiaSwap">Retorna uma estrutura com a descrição da cadeia de troca.</param>
	virtual CarenResult GetDesc([Out] Estruturas::CA_DXGI_SWAP_CHAIN_DESC^% Param_Out_DescricaoCadeiaSwap);

	/// <summary>
	/// (GetFrameStatistics) - Obtém estatísticas de desempenho sobre o último quadro render.
	/// </summary>
	/// <param name="Param_Out_FrameEstatisticas">Retorna uma estrutura com as estatiticas do frame.</param>
	virtual CarenResult GetFrameStatistics([Out] Estruturas::CA_DXGI_FRAME_STATISTICS^% Param_Out_FrameEstatisticas);

	/// <summary>
	/// (GetFullscreenState) - Associe o estado ao modo de tela cheia.
	/// </summary>
	/// <param name="Param_Out_EstadoFullScreen">Retorna o estado do FullScreen. Se TRUE, a cadeia de swap está no modo de tela cheia. Se FALSE, a cadeia de swap está em modo de janela.</param>
	/// <param name="Param_Out_MonitorSaida">Retorna um ponteiro para o monitor de saida quando em modo de Tela Cheia(FullScreen); caso contrario retorna NULO.</param>
	virtual CarenResult GetFullscreenState([Out] Boolean% Param_Out_EstadoFullScreen, [Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

	/// <summary>
	/// (GetLastPresentCount) - Obtém o número de vezes que o método ICarenDXGISwapChain::Apresentar ou ICarenDXGISwapChain1::Present1 foi chamado.
	/// </summary>
	/// <param name="Param_Out_QuantidadeChamadas">Retorna a quantidade de chamadas para o método Apresentar ou Present1.</param>
	virtual CarenResult GetLastPresentCount([Out] UInt32% Param_Out_QuantidadeChamadas);

	/// <summary>
	/// (Present) - Apresenta uma imagem renderizada ao usuário.
	/// </summary>
	/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
	/// <param name="Param_Flags">Um valor inteiro que contém opções de apresentação em cadeia de swaps. Essas opções são definidas pela enumeração (CA_DXGI_PRESENT).</param>
	virtual CarenResult Present(UInt32 Param_IntervaloSincronizacao, Enumeracoes::CA_DXGI_PRESENT Param_Flags);

	/// <summary>
	/// (ResizeBuffers) - Altera o tamanho, o formato e o número de buffers da cadeia de swap. Isso deve ser chamado quando a janela do aplicativo é redimensionada.
	/// Você não pode redimensionar uma cadeia de swap sem que libere todas as referências pendentes aos seus buffers traseiros. Você deve liberar todas as suas referências diretas e indiretas nos buffers de volta para que 
	/// o (AlterarTamanhoBuffers) tenha sucesso.
	/// </summary>
	/// <param name="Param_NumeroBuffers">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e dianteiros). Este número pode ser diferente do número de buffers com os quais você criou a cadeia de swap. 
	/// Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o número existente de amortecedores na cadeia de swaps.</param>
	/// <param name="Param_Largura">A nova largura do amortecedor traseiro. Se você especificar zero, DXGI usará a largura da área do cliente da janela do alvo.</param>
	/// <param name="Param_Altura">A nova altura do amortecedor traseiro. Se você especificar zero, DXGI usará a altura da área do cliente da janela do alvo. </param>
	/// <param name="Param_NovoFormato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN para preservar o formato existente do buffer traseiro.</param>
	/// <param name="Param_SwapChainFlags">Uma combinação de CA_DXGI_SWAP_CHAIN_FLAG- digitado valores que são combinados usando um bitwise ou operação. O valor resultante especifica opções para o comportamento da cadeia de swaps</param>
	virtual CarenResult ResizeBuffers(UInt32 Param_NumeroBuffers, UInt32 Param_Largura, UInt32 Param_Altura, Enumeracoes::CA_DXGI_FORMAT Param_NovoFormato, Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags);

	/// <summary>
	/// (ResizeTarget) - Redimensiona a meta de saída.
	/// </summary>
	/// <param name="Param_NovaDesc">A estrutura CA_DXGI_MODE_DESC que descreve o modo, que especifica a nova largura, altura, formato e taxa de atualização do alvo. Se o formato for DXGI_FORMAT_UNKNOWN, o método (ResizeTarget)
	/// utilizara o formato existente. Recomendamos apenas que você use DXGI_FORMAT_UNKNOWN quando a cadeia de swap está em modo de tela cheia, pois este método não é seguro para o segmento.</param>
	virtual CarenResult ResizeTarget(Estruturas::CA_DXGI_MODE_DESC^ Param_NovaDesc);

	/// <summary>
	/// (SetFullscreenState) - Define o estado de exibição para janelas ou tela cheia.
	/// </summary>
	/// <param name="Param_EstadoFullScreen">Um valor booleano que especifica se deve definir o estado de exibição para janelas ou tela cheia. VERDADE para tela cheia, e FALSO para janelas.</param>
	/// <param name="Param_MonitorSaida">Se você passar o TRUE para o parâmetro (Param_EstadoFullScreen) para definir o estado de exibição para tela cheia, você pode definir opcionalmente este parâmetro para um ponteiro para uma interface
	/// IDXGIOutput para o alvo de saída que contém a cadeia de swap. Se você definir este parâmetro para NULO, DXGI escolherá a saída com base no dispositivo da cadeia de swap e na colocação da janela de saída. Se você passar FALSE 
	/// para (Param_EstadoFullScreen), você deve definir este parâmetro para NULO.</param>
	virtual CarenResult SetFullscreenState(Boolean Param_EstadoFullScreen, ICarenDXGIOutput^ Param_MonitorSaida);



	//Métodos da interface(ICarenDXGIDeviceSubObject)
public:
	/// <summary>
	/// (GetDevice) - Recupera o dispositivo.
	/// </summary>
	/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
	/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterDispositivo(String^ Param_RIIDInterface, ICaren^ Param_Out_Objeto);


	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// (GetParent) - Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// (SetPrivateData) - Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult DefinirDadosPrivados(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// (GetPrivateData) - Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterDadosPrivados(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// (SetPrivateDataInterface) - Defina uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult DefinirDadosPrivadosInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};