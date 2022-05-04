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


#include "../pch.h"
#include "../DXGI\CarenDXGISwapChain4.h"

//Destruidor.
CarenDXGISwapChain4::~CarenDXGISwapChain4()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGISwapChain4::CarenDXGISwapChain4()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenDXGISwapChain4::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISwapChain4::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISwapChain4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISwapChain4**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISwapChain4::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISwapChain4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISwapChain4**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISwapChain4::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISwapChain4::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGISwapChain4::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGISwapChain4::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGISwapChain4::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGISwapChain4::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGISwapChain4::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGISwapChain4();
}



// Métodos da interface proprietária(ICarenDXGISwapChain4)


/// <summary>
/// (SetHDRMetaData) - Este método estabelece metadados de cabeçalho High Dynamic Range (HDR) e Wide Color Gamut (WCG).
/// </summary>
/// <param name="Param_MetadataType">Especifica um membro da enumeração CA_DXGI_HDR_METADATA_TYPE.</param>
/// <param name="Param_Size">Especifica o tamanho do (Param_Metadata), em bytes.</param>
/// <param name="Param_Metadata">Especifica um ponteiro vazio que faz referência aos metadados, se ele existe.</param>
CarenResult CarenDXGISwapChain4::SetHDRMetaData(
				CA_DXGI_HDR_METADATA_TYPE Param_MetadataType,
				UInt32 Param_Size,
				ICaren^ Param_Metadata)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetHDRMetaData(PonteiroTrabalho,
		Param_MetadataType,
		Param_Size,
		Param_Metadata
	);
}



// Métodos da interface ICarenDXGISwapChain3


/// <summary>
/// (CheckColorSpaceSupport) - Verifica o suporte da cadeia de swap para espaço de cores.
/// </summary>
/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE que especifica o tipo de espaço de cor para verificar o suporte.</param>
/// <param name="Param_Out_ColorSpaceSuporte">Recebe Zero ou mais bandeiras da enumeração CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG são combinados usando uma operação ou 
/// bitwise. O valor resultante especifica opções de suporte ao espaço colorido.</param>
CarenResult CarenDXGISwapChain4::CheckColorSpaceSupport(
	CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace, 
	[Out] CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG% Param_Out_ColorSpaceSuporte)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::CheckColorSpaceSupport(PonteiroTrabalho,
		Param_ColorSpace,
		Param_Out_ColorSpaceSuporte
	);
}

/// <summary>
/// (GetCurrentBackBufferIndex) - Obtém o índice do buffer atual da cadeia de swap.
/// </summary>
/// <param name="Param_Out_IndexBackBuffer">Retorna o indice do buffer traseiro(BackBuffer) atual.</param>
CarenResult CarenDXGISwapChain4::GetCurrentBackBufferIndex([Out] UInt32% Param_Out_IndexBackBuffer)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetCurrentBackBufferIndex(PonteiroTrabalho,
		Param_Out_IndexBackBuffer
	);
}

/// <summary>
/// (ResizeBuffers1) - Altera o tamanho do buffer traseiro da cadeia de swap, formato e número de buffers, onde a cadeia de swap foi criada usando uma fila de 
/// comando D3D12 como um dispositivo de entrada. Isso deve ser chamado quando a janela de aplicação for redimensionada.
/// </summary>
/// <param name="Param_CountBuffer">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e frontais). Este número pode ser diferente do número de 
/// buffers com os quais você criou a cadeia de swap. Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o 
/// número existente de buffers na cadeia de swap. Você não pode especificar menos de dois buffers para o modelo de apresentação flip.</param>
/// <param name="Param_Largura">A nova largura do buffer traseiro. Se você especificar zero, o DXGI usará a largura da área do cliente da janela de destino. Você não pode 
/// especificar a largura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
/// <param name="Param_Altura">A nova altura do tampão traseiro. Se você especificar zero, o DXGI usará a altura da área do cliente da janela de destino. Você não pode 
/// especificar a altura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
/// <param name="Param_Formato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN preservar o formato existente do buffer traseiro. O modelo 
/// de apresentação flip suporta um conjunto mais restrito de formatos do que o modelo de transferência de bit-block (bitblt).</param>
/// <param name="Param_SwapChainFlags">Uma combinação de valores da enumeração CA_valoresDXGI_SWAP_CHAIN_FLAG que são combinados usando uma operação ou bitwise. O valor 
/// resultante especifica opções para comportamento em cadeia de swap.</param>
/// <param name="Param_ArrayNodeMask">Uma matriz de UInt32, de tamanho total Param_CountBuffer, onde o valor indica em qual nó o buffer traseiro deve ser criado. Buffers 
/// criados usando ResizeBuffers1 com um conjunto (Param_ArrayNodeMask) não-nulo são visíveis para todos os nós.</param>
/// <param name="Param_ArrayD3D12CommandQueue">Uma série de filas de comando (ID3D12CommandQueue), de tamanho total Param_CountBuffer. Cada fila fornecida deve coincidir com a 
/// máscara de nó de criação correspondente especificada na matriz Param_ArrayNodeMask. Quando o (ICarenDXGISwapChain::Apresentar) é chamado, além de girar para o próximo 
/// buffer para o próximo quadro, a cadeia de swap também girará através dessas filas de comando. Isso permite que o aplicativo controle qual fila requer sincronização para 
/// uma determinada operação presente.</param>
CarenResult CarenDXGISwapChain4::ResizeBuffers1(
	UInt32 Param_CountBuffer,
	UInt32 Param_Largura,
	UInt32 Param_Altura,
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags,
	cli::array<UInt32>^ Param_ArrayNodeMask,
	cli::array<ICaren^>^ Param_ArrayD3D12CommandQueue)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::ResizeBuffers1(PonteiroTrabalho,
		Param_CountBuffer,
		Param_Largura,
		Param_Altura,
		Param_Formato,
		Param_SwapChainFlags,
		Param_ArrayNodeMask,
		Param_ArrayD3D12CommandQueue
	);
}

/// <summary>
/// (SetColorSpace1) - Define o espaço de cores usado pela cadeia de swap.
/// </summary>
/// <param name="Param_ColorSpace">Um valor de CA_DXGI_COLOR_SPACE_TYPE que especifica o espaço de cores para definir.</param>
CarenResult CarenDXGISwapChain4::SetColorSpace1(CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetColorSpace1(PonteiroTrabalho,
		Param_ColorSpace
	);
}



// Métodos da interface ICarenDXGISwapChain2

/// <summary>
/// (GetFrameLatencyWaitableObject) - Retorna uma Handle aguardavel que sinaliza quando o adaptador DXGI terminar de apresentar um novo quadro.
/// O Windows 8.1 introduz novas APIs que permitem renderização de menor latência esperando até que o quadro anterior seja apresentado ao display antes de desenhar o 
/// quadro seguinte. Para usar este método, primeiro crie a cadeia de swap DXGI com o conjunto de bandeiras CA_DXGI_SWAP_CHAIN_FLAG::CA_DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT, 
/// em seguida, ligue para GetFrameLatencyWaitableObject para recuperar a handle aguardavel. Chame o método ICarenEvent::AguardarObjetoUnicoEx para sincronizar a 
/// renderização de cada novo quadro com o final do quadro anterior. Para cada quadro que renderiza, o aplicativo deve esperar por essa alça antes de iniciar qualquer operação 
/// de renderização.
/// </summary>
/// <param name="Param_Out_HandleEvento">Recebe a interface que gerencia a Handle aguardavel.</param>
CarenResult CarenDXGISwapChain4::GetFrameLatencyWaitableObject([Out] ICarenEvent^% Param_Out_HandleEvento)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetFrameLatencyWaitableObject(PonteiroTrabalho,
		Param_Out_HandleEvento
	);
}

/// <summary>
/// (GetMatrixTransform) - Obtém a matriz de transformação que será aplicada a uma cadeia de troca de composição no proximo (Present).
/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel,
/// que pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
/// Os métodos GetMatrixTransform e SetMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
/// Apenas elementos simples de escala/tradução na matriz são permitidos - a chamada falhará se a matriz contiver elementos de distorção/rotação.
/// </summary>
/// <param name="Param_Out_Matriz_32"></param>
CarenResult CarenDXGISwapChain4::GetMatrixTransform([Out] CA_DXGI_MATRIX_3X2_F^% Param_Out_Matriz_32)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetMatrixTransform(PonteiroTrabalho,
		Param_Out_Matriz_32
	);
}

/// <summary>
/// (GetMaximumFrameLatency) - Obtém o número de quadros que a cadeia de swap pode enfileirar para renderização.
/// </summary>
/// <param name="Param_Out_LatenciaMaxima">Recebe o número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Esse valor é 1 por padrão, 
/// mas deve ser definido para 2 se a cena demorar mais do que leva para uma atualização vertical (normalmente cerca de 16ms) para desenhar.</param>
CarenResult CarenDXGISwapChain4::GetMaximumFrameLatency([Out] UInt32% Param_Out_LatenciaMaxima)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetMaximumFrameLatency(PonteiroTrabalho,
		Param_Out_LatenciaMaxima
	);
}

/// <summary>
/// (GetSourceSize) - Obtém a região de origem é usada para a cadeia de swap.
/// Use o (GetSourceSize) para obter a parte da cadeia de swap da qual o sistema operacional apresenta. O retângulo de origem é sempre definido pela região 
/// [0, 0, Largura, Altura]. Use o (SetSourceSize) para definir esta parte da cadeia de swap.
/// </summary>
/// <param name="Param_Out_Largura">Recebe a largura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 até a largura geral da cadeia de swap.</param>
/// <param name="Param_Out_Altura">Recebe a altura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 a altura global da cadeia de swap.</param>
CarenResult CarenDXGISwapChain4::GetSourceSize(
	[Out] UInt32% Param_Out_Largura, 
	[Out] UInt32% Param_Out_Altura)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetSourceSize(PonteiroTrabalho,
		Param_Out_Largura,
		Param_Out_Altura
	);
}

/// <summary>
/// (SetMatrixTransform) - Define a matriz de transformação que será aplicada a uma cadeia de troca de composição no próximo (Present).
/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel, que 
/// pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
/// Os métodos GetMatrixTransform e SetMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
/// Apenas elementos simples de escala/tradução na matriz são permitidos - a chamada falhará se a matriz contiver elementos de distorção/rotação.
/// </summary>
/// <param name="Param_Matriz_32">A matriz de transformação para usar para o dimensionamento e tradução em cadeia de swap. Esta função só pode ser usada com cadeias de troca de 
/// composição(Composition) criadas por ICarenDXGIFactory2::CreateSwapChainForComposition. Somente componentes de escala e tradução são permitidos na matriz.</param>
CarenResult CarenDXGISwapChain4::SetMatrixTransform(CA_DXGI_MATRIX_3X2_F^ Param_Matriz_32)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetMatrixTransform(PonteiroTrabalho,
		Param_Matriz_32
	);
}

/// <summary>
/// (SetMaximumFrameLatency) - Define o número de quadros que a cadeia de swap pode fazer fila para renderização.
/// </summary>
/// <param name="Param_MaximoBackBufferLatencia">O número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Este valor é 1 por padrão.</param>
CarenResult CarenDXGISwapChain4::SetMaximumFrameLatency(UInt32 Param_MaximoBackBufferLatencia)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetMaximumFrameLatency(PonteiroTrabalho,
		Param_MaximoBackBufferLatencia
	);
}

/// <summary>
/// (SetSourceSize) - Define a região de origem para ser usada para a cadeia de swap.
/// Use o SetSourceSize para especificar a parte da cadeia de swap da qual o sistema operacional apresenta. Isso permite um redimensionamento eficaz sem chamar o método 
/// (ICarenDXGISwapChain::AlterarTamanhoBuffers) que é mais caro. Antes do Windows 8.1, ligar para ICarenDXGISwapChain::AlterarTamanhoBuffers era a única maneira de 
/// redimensionar a cadeia de swap. O retângulo de origem é sempre definido pela região [0, 0, Largura, Altura].
/// </summary>
/// <param name="Param_Largura">Largura de fonte para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à largura global 
/// da cadeia de swap.</param>
/// <param name="Param_Altura">Altura de origem para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à altura global da 
/// cadeia de swap.</param>
CarenResult CarenDXGISwapChain4::SetSourceSize(UInt32 Param_Largura, UInt32 Param_Altura)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetSourceSize(PonteiroTrabalho,
		Param_Largura,
		Param_Altura
	);
}



// Métodos da interface ICarenDXGISwapChain1


/// <summary>
/// (GetBackgroundColor) - Recupera a cor de fundo da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Cor">Retorna uma estrutura que contém as informações de cor do Background.</param>
CarenResult CarenDXGISwapChain4::GetBackgroundColor([Out] CA_DXGI_RGBA^% Param_Out_Cor)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetBackgroundColor(PonteiroTrabalho,
		Param_Out_Cor
	);
}

/// <summary>
/// (GetCoreWindow) - Recupera o objeto CoreWindow subjacente para este objeto de cadeia de swap.
/// </summary>
/// <param name="Param_RIID">Um ponteiro para o identificador globalmente único(GUID) do objeto CoreWindow que é referenciado pelo parâmetro Param_Out_CoreWindow.</param>
/// <param name="Param_Out_CoreWindow">Retorna o ponteiro do objeto para a CoreWindow.  O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain4::GetCoreWindow(String^ Param_RIID, ICaren^ Param_Out_CoreWindow)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetCoreWindow(PonteiroTrabalho,
		Param_RIID,
		Param_Out_CoreWindow
	);
}

/// <summary>
/// (GetDesc1) - Obtém uma descrição da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Desc">Retorna uma estrutura que contém a descrição da cadeia de Swap.</param>
CarenResult CarenDXGISwapChain4::GetDesc1([Out] CA_DXGI_SWAP_CHAIN_DESC1^% Param_Out_Desc)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetDesc1(PonteiroTrabalho,
		Param_Out_Desc
	);
}

/// <summary>
/// (GetFullscreenDesc) - Obtém uma descrição de uma cadeia de troca em tela cheia.
/// </summary>
/// <param name="Param_Out_DescFullScreenSwap">Retorna uma estrutura que contém a descrição no modo FullScreen na cadeia de Swap.</param>
CarenResult CarenDXGISwapChain4::GetFullscreenDesc([Out] CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^% Param_Out_DescFullScreenSwap)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetFullscreenDesc(PonteiroTrabalho,
		Param_Out_DescFullScreenSwap
	);
}

/// <summary>
/// (GetHwnd) - Recupera o HWND subjacente para este objeto de cadeia de swap.
/// </summary>
/// <param name="Param_Out_HWND">Retorna um ponteiro para o HWND do objeto de cadeia de Swap.</param>
CarenResult CarenDXGISwapChain4::GetHwnd([Out] IntPtr% Param_Out_HWND)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetHwnd(PonteiroTrabalho,
		Param_Out_HWND
	);
}

/// <summary>
/// (GetRestrictToOutput) - Obtém a saída (o monitor de exibição) ao qual você pode restringir o conteúdo de uma operação atual.
/// </summary>
/// <param name="Param_Out_Saida">Um ponteiro para um buffer que recebe um ponteiro para a interface IDXGIOutput para a saída de restrição.  Um aplicativo passa este ponteiro para 
/// ICarenDXGIOutput em uma chamada para o ICarenDXGIFactory2::CreateSwapChainForHwnd, ICarenDXGIFactory2::CreateSwapChainForCoreWindow, ou ICarenDXGIFactory2::CreateSwapChainForComposition</param>
CarenResult CarenDXGISwapChain4::GetRestrictToOutput([Out] ICarenDXGIOutput^% Param_Out_Saida)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetRestrictToOutput(PonteiroTrabalho,
		Param_Out_Saida
	);
}

/// <summary>
/// (GetRotation) - Obtém a rotação dos buffers traseiros para a cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Rotacao">Retorna uma enumeração que define a rotação do Buffer Traseiro(BackBuffer).</param>
CarenResult CarenDXGISwapChain4::GetRotation([Out] CA_DXGI_MODE_ROTATION% Param_Out_Rotacao)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetRotation(PonteiroTrabalho,
		Param_Out_Rotacao
	);
}

/// <summary>
/// (IsTemporaryMonoSupported) - Determina se uma cadeia de swap suporta "mono temporário".
/// </summary>
/// <param name="Param_Out_Suporte">Retorna um Booleano que define o suporte ao mono.</param>
CarenResult CarenDXGISwapChain4::IsTemporaryMonoSupported([Out] Boolean% Param_Out_Suporte)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::IsTemporaryMonoSupported(PonteiroTrabalho,
		Param_Out_Suporte
	);
}

/// <summary>
/// (Present1) - Apresenta um Frame a tela de exibição.
/// </summary>
/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
/// <param name="Param_FlagsApresentacao">Um valor inteiro que contém opções de apresentação em cadeia de swaps.</param>
/// <param name="Param_ParametrosApresentacao">uma estrutura CA_DXGI_PRESENT_PARAMETERS que descreve retângulos atualizados e rolar informações do quadro para apresentar.</param>
CarenResult CarenDXGISwapChain4::Present1(
	UInt32 Param_IntervaloSincronizacao, 
	CA_DXGI_PRESENT Param_FlagsApresentacao, 
	CA_DXGI_PRESENT_PARAMETERS^ Param_ParametrosApresentacao)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::Present1(PonteiroTrabalho,
		Param_IntervaloSincronizacao,
		Param_FlagsApresentacao,
		Param_ParametrosApresentacao
	);
}

/// <summary>
/// (SetBackgroundColor) - Muda a cor de fundo da cadeia de swaps.
/// </summary>
/// <param name="Param_Cor">A nova cor para o Background do buffer traseiro.</param>
CarenResult CarenDXGISwapChain4::SetBackgroundColor(CA_DXGI_RGBA^ Param_Cor)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetBackgroundColor(PonteiroTrabalho,
		Param_Cor
	);
}

/// <summary>
/// (SetRotation) - Define a rotação dos buffers de volta para a cadeia de swap.
/// </summary>
/// <param name="Param_Rotacao">A nova rotação dos Buffers Traseiro(BackBuffers).</param>
CarenResult CarenDXGISwapChain4::SetRotation(CA_DXGI_MODE_ROTATION Param_Rotacao)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetRotation(PonteiroTrabalho,
		Param_Rotacao
	);
}





// Métodos da interface ICarenDXGISwapChain


/// <summary>
/// (GetBuffer) - Acessa um dos buffers de volta da cadeia de swaps.
/// </summary>
/// <param name="Param_IndexBuffer">O Indince para o buffer de volta(Back-Buffer).</param>
/// <param name="Param_RiidInterface">O tipo de interface usada para manipular o buffer.</param>
/// <param name="Param_Out_InterfaceBuffer">Retorna a interface que gerencia o Buffer de volta(Back-Buffer). O Usuário é responsável por criar a interface que será retornada.</param>
CarenResult CarenDXGISwapChain4::GetBuffer(
	UInt32 Param_IndexBuffer, 
	String^ Param_RiidInterface, 
	ICaren^ Param_Out_InterfaceBuffer)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetBuffer(PonteiroTrabalho,
		Param_IndexBuffer,
		Param_RiidInterface,
		Param_Out_InterfaceBuffer
	);
}

/// <summary>
/// (GetContainingOutput) - Obtém a saída (o monitor de exibição) que contém a maior parte da área do cliente da janela alvo.
/// Se o método for bem-sucedido, a interface de saída será preenchida e sua contagem de referência incrementada. Quando você terminar com ele, não se esqueça de liberar a interface para evitar um vazamento de memória.
/// </summary>
/// <param name="Param_Out_MonitorSaida">Retorna a interface para o monitor de exbicão de saida.</param>
CarenResult CarenDXGISwapChain4::GetContainingOutput([Out] ICarenDXGIOutput^% Param_Out_MonitorSaida)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetContainingOutput(PonteiroTrabalho,
		Param_Out_MonitorSaida
	);
}

/// <summary>
/// (GetDesc) - Obtém uma descrição da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_DescricaoCadeiaSwap">Retorna uma estrutura com a descrição da cadeia de troca.</param>
CarenResult CarenDXGISwapChain4::GetDesc([Out] Estruturas::CA_DXGI_SWAP_CHAIN_DESC^% Param_Out_DescricaoCadeiaSwap)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetDesc(PonteiroTrabalho,
		Param_Out_DescricaoCadeiaSwap
	);
}

/// <summary>
/// (GetFrameStatistics) - Obtém estatísticas de desempenho sobre o último quadro render.
/// </summary>
/// <param name="Param_Out_FrameEstatisticas">Retorna uma estrutura com as estatiticas do frame.</param>
CarenResult CarenDXGISwapChain4::GetFrameStatistics([Out] Estruturas::CA_DXGI_FRAME_STATISTICS^% Param_Out_FrameEstatisticas)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetFrameStatistics(PonteiroTrabalho,
		Param_Out_FrameEstatisticas
	);
}

/// <summary>
/// (GetFullscreenState) - Associe o estado ao modo de tela cheia.
/// </summary>
/// <param name="Param_Out_EstadoFullScreen">Retorna o estado do FullScreen. Se TRUE, a cadeia de swap está no modo de tela cheia. Se FALSE, a cadeia de swap está em modo de janela.</param>
/// <param name="Param_Out_MonitorSaida">Retorna um ponteiro para o monitor de saida quando em modo de Tela Cheia(FullScreen); caso contrario retorna NULO.</param>
CarenResult CarenDXGISwapChain4::GetFullscreenState(
	[Out] Boolean% Param_Out_EstadoFullScreen, 
	[Out] ICarenDXGIOutput^% Param_Out_MonitorSaida)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetFullscreenState(PonteiroTrabalho,
		Param_Out_EstadoFullScreen,
		Param_Out_MonitorSaida
	);
}

/// <summary>
/// (GetLastPresentCount) - Obtém o número de vezes que o método ICarenDXGISwapChain::Apresentar ou ICarenDXGISwapChain1::Present1 foi chamado.
/// </summary>
/// <param name="Param_Out_QuantidadeChamadas">Retorna a quantidade de chamadas para o método Apresentar ou Present1.</param>
CarenResult CarenDXGISwapChain4::GetLastPresentCount([Out] UInt32% Param_Out_QuantidadeChamadas)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::GetLastPresentCount(PonteiroTrabalho,
		Param_Out_QuantidadeChamadas
	);
}

/// <summary>
/// (Present) - Apresenta uma imagem renderizada ao usuário.
/// </summary>
/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
/// <param name="Param_Flags">Um valor inteiro que contém opções de apresentação em cadeia de swaps. Essas opções são definidas pela enumeração (CA_DXGI_PRESENT).</param>
CarenResult CarenDXGISwapChain4::Present(
	UInt32 Param_IntervaloSincronizacao, 
	Enumeracoes::CA_DXGI_PRESENT Param_Flags)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::Present(PonteiroTrabalho,
		Param_IntervaloSincronizacao,
		Param_Flags
	);
}

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
CarenResult CarenDXGISwapChain4::ResizeBuffers(
	UInt32 Param_NumeroBuffers, 
	UInt32 Param_Largura, 
	UInt32 Param_Altura, 
	Enumeracoes::CA_DXGI_FORMAT Param_NovoFormato, 
	Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::ResizeBuffers(PonteiroTrabalho,
		Param_NumeroBuffers,
		Param_Largura,
        Param_Altura,
        Param_NovoFormato,
        Param_SwapChainFlags
	);
}

/// <summary>
/// (ResizeTarget) - Redimensiona a meta de saída.
/// </summary>
/// <param name="Param_NovaDesc">A estrutura CA_DXGI_MODE_DESC que descreve o modo, que especifica a nova largura, altura, formato e taxa de atualização do alvo. Se o formato for DXGI_FORMAT_UNKNOWN, o método (ResizeTarget)
/// utilizara o formato existente. Recomendamos apenas que você use DXGI_FORMAT_UNKNOWN quando a cadeia de swap está em modo de tela cheia, pois este método não é seguro para o segmento.</param>
CarenResult CarenDXGISwapChain4::ResizeTarget(Estruturas::CA_DXGI_MODE_DESC^ Param_NovaDesc)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::ResizeTarget(PonteiroTrabalho,
		Param_NovaDesc
	);
}

/// <summary>
/// (SetFullscreenState) - Define o estado de exibição para janelas ou tela cheia.
/// </summary>
/// <param name="Param_EstadoFullScreen">Um valor booleano que especifica se deve definir o estado de exibição para janelas ou tela cheia. VERDADE para tela cheia, e FALSO para janelas.</param>
/// <param name="Param_MonitorSaida">Se você passar o TRUE para o parâmetro (Param_EstadoFullScreen) para definir o estado de exibição para tela cheia, você pode definir opcionalmente este parâmetro para um ponteiro para uma interface
/// IDXGIOutput para o alvo de saída que contém a cadeia de swap. Se você definir este parâmetro para NULO, DXGI escolherá a saída com base no dispositivo da cadeia de swap e na colocação da janela de saída. Se você passar FALSE 
/// para (Param_EstadoFullScreen), você deve definir este parâmetro para NULO.</param>
CarenResult CarenDXGISwapChain4::SetFullscreenState(
	Boolean Param_EstadoFullScreen, 
	ICarenDXGIOutput^ Param_MonitorSaida)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISwapChain::SetFullscreenState(PonteiroTrabalho,
		Param_EstadoFullScreen,
		Param_MonitorSaida
	);
}




// Métodos da interface ICarenDXGIDeviceSubObject

/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain4::GetDevice(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_Objeto)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIDeviceSubObject::GetDevice(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_Objeto
	);
}




// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain4::GetParent(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_ObjetoPai)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetParent(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_ObjetoPai
	);
}

/// <summary>
/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGISwapChain4::SetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32 Param_TamanhoDados, 
	ICaren^ Param_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_TamanhoDados,
		Param_Dados
	);
}

/// <summary>
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain4::GetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32% Param_Ref_TamanhoDados, 
	ICaren^ Param_Out_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_Ref_TamanhoDados,
		Param_Out_Dados
	);
}

/// <summary>
/// Define uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGISwapChain4::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}