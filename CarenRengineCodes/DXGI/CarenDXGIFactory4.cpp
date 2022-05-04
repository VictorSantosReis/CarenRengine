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
#include "CarenDXGIFactory4.h"


//Destruidor.
CarenDXGIFactory4::~CarenDXGIFactory4()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGIFactory4::CarenDXGIFactory4()
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
CarenResult CarenDXGIFactory4::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory4::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory4**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory4::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory4**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory4::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory4::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIFactory4::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIFactory4::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIFactory4::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIFactory4::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIFactory4::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIFactory4();
}


// Métodos da interface ICarenDXGIFactory4

/// <summary>
/// (EnumAdapterByLuid) - Enumera saídas do ICarenDXGIAdapter para o LUID especificado.
/// </summary>
/// <param name="Param_LUID">Um valor único que identifica o adaptador.</param>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
CarenResult CarenDXGIFactory4::EnumAdapterByLuid(
	CA_LUID^ Param_LUID, 
	String^ Param_RIID, 
	[Out] ICaren^ Param_Out_InterfaceAdapter)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumAdapterByLuid(PonteiroTrabalho,
		Param_LUID,
		Param_RIID,
		Param_Out_InterfaceAdapter
	);
}

/// <summary>
/// (EnumWarpAdapter) - Fornece um adaptador que pode ser fornecido a função D3D12CreateDevice para usar o renderizador WARP.
/// </summary>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador. </param>
CarenResult CarenDXGIFactory4::EnumWarpAdapter(
	String^ Param_RIID, 
	[Out] ICaren^ Param_Out_InterfaceAdapter)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumWarpAdapter(PonteiroTrabalho,
		Param_RIID,
		Param_Out_InterfaceAdapter
	);
}



// Métodos da interface ICarenDXGIFactory3

/// <summary>
/// (GetCreationFlags) - Recebe as bandeiras que foram usadas quando um objeto Microsoft DirectX Graphics Infrastructure (DXGI) foi criado.
/// </summary>
/// <param name="Param_Out_Flags">Retorna o flag utilizada na criação da fabrica(DXGIFactory).</param>
CarenResult CarenDXGIFactory4::GetCreationFlags(
	[Out] UInt32% Param_Out_Flags)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::GetCreationFlags(PonteiroTrabalho,
		Param_Out_Flags
	);
}


// Métodos da interface ICarenDXGIFactory2

/// <summary>
/// (CreateSwapChainForComposition) - Cria uma cadeia de swaps que você pode usar para enviar conteúdo Direct3D para a API de Composição Direta ou a estrutura Windows.UI.Xaml para compor em uma janela.
/// </summary>
/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.
/// Você deve especificar o valor DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL no membro SwapEffect da CA_DXGI_SWAP_CHAIN_DESC1 porque o método (CreateSwapChainForComposition) suporta 
/// apenas um modelo de apresentação de flip.
/// Você também deve especificar o valor DXGI_SCALING_STRETCH no membro de Scale de CA_DXGI_SWAP_CHAIN_DESC1.</param>
/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
/// quiser restringir o conteúdo a uma meta de saída.
/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Present1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForComposition) cria.</param>
CarenResult CarenDXGIFactory4::CreateSwapChainForComposition(
	ICaren^ Param_DispositivoDirect3D,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSwapChainForComposition(PonteiroTrabalho,
		Param_DispositivoDirect3D,
		Param_DescSwap,
		Param_SaidaRestrita,
		Param_Out_SwapChain
	);
}

/// <summary>
/// (CreateSwapChainForCoreWindow) - Cria uma cadeia de swaps que está associada ao objeto CoreWindow para a janela de saída para a cadeia de swap.
/// </summary>
/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
/// <param name="Param_CoreWindow">Um ponteiro para o objeto CoreWindow que está associado com a cadeia de swap que (CreateSwapChainForCoreWindow) cria.</param>
/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput que a cadeia de swap é restrito. Se a cadeia de swaps for movida para uma saída diferente, 
/// o conteúdo é preto. Você pode definir opcionalmente este parâmetro para uma meta de saída que usa DXGI_PRESENT_RESTRICT_TO_OUTPUT para restringir o conteúdo dessa saída. 
/// Se você não definir este parâmetro para restringir o conteúdo em uma meta de saída, você pode defini-lo para NULO.</param>
/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForCoreWindow) cria.</param>
CarenResult CarenDXGIFactory4::CreateSwapChainForCoreWindow(
	ICaren^ Param_DispositivoDirect3D,
	ICaren^ Param_CoreWindow,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSwapChainForCoreWindow(PonteiroTrabalho,
		Param_DispositivoDirect3D,
		Param_CoreWindow,
		Param_DescSwap,
		Param_SaidaRestrita,
		Param_Out_SwapChain
	);
}

/// <summary>
/// (CreateSwapChainForHwnd) - Cria uma cadeia de swap que esteja associada a uma alça HWND à janela de saída para a cadeia de swaps.
/// </summary>
/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
/// <param name="Param_Handle">A alça(HWND - HANDLE) que está associado com a cadeia de swap que (CreateSwapChainForHwnd) cria. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_DescFullScreen">Uma estrutura CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC para a descrição de uma cadeia de swap de tela cheia. Você pode definir opcionalmente 
/// este parâmetro para criar uma cadeia de swap de tela cheia. Configurá-lo para NULO para criar uma cadeia de swap em modo Janela.</param>
/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
/// quiser restringir o conteúdo a uma meta de saída.
/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Present1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForHwnd) cria.</param>
CarenResult CarenDXGIFactory4::CreateSwapChainForHwnd(
	ICaren^ Param_DispositivoDirect3D,
	IntPtr Param_Handle,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_DescFullScreen,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSwapChainForHwnd(PonteiroTrabalho,
		Param_DispositivoDirect3D,
		Param_Handle,
		Param_DescSwap,
		Param_DescFullScreen,
		Param_SaidaRestrita,
		Param_Out_SwapChain
	);
}

/// <summary>
/// (GetSharedResourceAdapterLuid) - Identifica o adaptador no qual um objeto de recurso compartilhado foi criado.
/// </summary>
/// <param name="Param_HandleRecurso">Uma alça para um objeto de recurso compartilhado. O método ICarenDXGIResource1::CreateSharedHandle devolve essa alça.</param>
/// <param name="Param_Out_Luid">Retorna uma variavel que recebe um identificador localmente único(LUID). Valor que identifica o adaptador. Um CA_LUID é um valor de 64 bits 
/// que é garantido para ser único apenas no sistema operacional em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema operacional seja 
/// reiniciado.</param>
CarenResult CarenDXGIFactory4::GetSharedResourceAdapterLuid(
	IntPtr Param_HandleRecurso, 
	[Out] CA_LUID^% Param_Out_Luid)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::GetSharedResourceAdapterLuid(PonteiroTrabalho,
		Param_HandleRecurso,
		Param_Out_Luid
	);
}

/// <summary>
/// (IsWindowedStereoEnabled) - Determina se deve usar o modo estéreo.
/// </summary>
/// <param name="Param_Out_ModoEstereoHabilitado">Retorna um valor que indica se deve usar o modo estéreo. TRUE indica que você pode usar o modo estéreo; se não, FALSO.</param>
CarenResult CarenDXGIFactory4::IsWindowedStereoEnabled(
	[Out] Boolean% Param_Out_ModoEstereoHabilitado)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::IsWindowedStereoEnabled(PonteiroTrabalho,
		Param_Out_ModoEstereoHabilitado
	);
}

/// <summary>
/// (RegisterOcclusionStatusEvent) - Registra-se para receber notificação de alterações no status de oclusão usando a sinalização do evento.
/// </summary>
/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status de oclusão. 
/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o 
/// registro do evento de notificação que (Param_Evento) especifica.</param>
CarenResult CarenDXGIFactory4::RegisterOcclusionStatusEvent(
	ICarenEvent^ Param_Evento, 
	[Out] UInt32% Param_Out_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::RegisterOcclusionStatusEvent(PonteiroTrabalho,
		Param_Evento,
		Param_Out_Cookie
	);
}

/// <summary>
/// (RegisterOcclusionStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações do status de oclusão.
/// </summary>
/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração de status de oclusão.</param>
/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o registro da mensagem 
/// de notificação que (Param_WinMensagemCode) especifica.</param>
CarenResult CarenDXGIFactory4::RegisterOcclusionStatusWindow(
	IntPtr Param_HandleJanela, 
	UInt32 Param_WinMensagemCode, 
	[Out] UInt32% Param_Out_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::RegisterOcclusionStatusWindow(PonteiroTrabalho,
		Param_HandleJanela,
		Param_WinMensagemCode,
		Param_Out_Cookie
	);
}

/// <summary>
/// (RegisterStereoStatusEvent) - Registra-se para receber notificação de alterações no status estéreo usando a sinalização do evento.
/// </summary>
/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status do modo Stereo. 
/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o 
/// registro do evento de notificação que (Param_Evento) especifica.</param>
CarenResult CarenDXGIFactory4::RegisterStereoStatusEvent(
	ICarenEvent^ Param_Evento, 
	[Out] UInt32% Param_Out_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::RegisterStereoStatusEvent(PonteiroTrabalho,
		Param_Evento,
		Param_Out_Cookie
	);
}

/// <summary>
/// (RegisterStereoStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações de status estéreo.
/// </summary>
/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração do modo Stereo.</param>
/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o registro da mensagem 
/// de notificação que (Param_WinMensagemCode) especifica.</param>
CarenResult CarenDXGIFactory4::RegisterStereoStatusWindow(
	IntPtr Param_HandleJanela, 
	UInt32 Param_WinMensagemCode, 
	[Out] UInt32% Param_Out_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::RegisterStereoStatusWindow(PonteiroTrabalho,
		Param_HandleJanela,
		Param_WinMensagemCode,
		Param_Out_Cookie
	);
}

/// <summary>
/// (UnregisterOcclusionStatus) - Remove o registro feito por uma chamada (RegisterOcclusionStatusWindow) para uma janela ou um evento para impedi-lo de receber notificação quando o status de oclusão muda.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
CarenResult CarenDXGIFactory4::UnregisterOcclusionStatus(
	UInt32 Param_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::UnregisterOcclusionStatus(PonteiroTrabalho,
		Param_Cookie
	);
}

/// <summary>
/// (UnregisterStereoStatus) - Remove o registro feito por uma chamada (RegisterOcclusionStatusWindow) para uma janela ou um evento para impedi-lo de receber notificação quando o status estéreo muda.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
CarenResult CarenDXGIFactory4::UnregisterStereoStatus(
	UInt32 Param_Cookie)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::UnregisterStereoStatus(PonteiroTrabalho,
		Param_Cookie
	);
}



// Métodos da interface ICarenDXGIFactory1

/// <summary>
/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory4::EnumAdapters1(
	UInt32 Param_IdAdaptador, 
	[Out] ICarenDXGIAdapter1^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumAdapters1(PonteiroTrabalho,
		Param_IdAdaptador,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
/// </summary>
/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
CarenResult CarenDXGIFactory4::IsCurrent(
	[Out] Boolean% Param_Out_Atual)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::IsCurrent(PonteiroTrabalho,
		Param_Out_Atual
	);
}



// Métodos da interface ICarenDXGIFactory

/// <summary>
/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
/// </summary>
/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
CarenResult CarenDXGIFactory4::CreateSoftwareAdapter(
	IntPtr Param_ModuleHandle, 
	[Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSoftwareAdapter(PonteiroTrabalho,
		Param_ModuleHandle,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (CreateSwapChain) - Cria uma cadeia de swaps.
/// [Começando com o Direct3D 11.1, recomendamos não usar mais o CreateSwapChain para criar uma cadeia de swaps. Em vez disso, use CreateSwapChainForHwnd, CreateSwapChainForCoreWindow, ou 
/// CreateSwapChainForComposition dependendo de como você quer criar a cadeia de swap.]
/// </summary>
/// <param name="Param_Dispositivo3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. Para Direct3D 12 este é 
/// um ponteiro para uma fila de comando direto(D3D12CommandQueue). Este parâmetro não pode ser NULO.</param>
/// <param name="Param_Desc">Uma estrutura CA_DXGI_SWAP_CHAIN_DESC para a descrição da cadeia de swap. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_Out_SwapChain">Recebe um ponteiro para a interface do SwapChain.</param>
CarenResult CarenDXGIFactory4::CreateSwapChain(
	ICaren^ Param_Dispositivo3D, 
	CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc, 
	[Out] ICarenDXGISwapChain^% Param_Out_SwapChain)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSwapChain(PonteiroTrabalho,
		Param_Dispositivo3D,
		Param_Desc,
		Param_Out_SwapChain
	);
}

/// <summary>
/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory4::EnumAdapters(
	UInt32 Param_IdAdaptador, 
	[Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumAdapters(PonteiroTrabalho,
		Param_IdAdaptador,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
/// </summary>
/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
CarenResult CarenDXGIFactory4::GetWindowAssociation(
	[Out] IntPtr% Param_HandleJanela)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::GetWindowAssociation(PonteiroTrabalho,
		Param_HandleJanela
	);
}

/// <summary>
/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
/// para tela cheia ou vice-versa).
/// </summary>
/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
/// <param name="Param_Flags"></param>
CarenResult CarenDXGIFactory4::MakeWindowAssociation(
	IntPtr Param_HandleJanela, 
	CA_DXGI_MWA_FLAGS Param_Flags)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::MakeWindowAssociation(PonteiroTrabalho,
		Param_HandleJanela,
		Param_Flags
	);
}



// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIFactory4::GetParent(
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
CarenResult CarenDXGIFactory4::SetPrivateData(
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
CarenResult CarenDXGIFactory4::GetPrivateData(
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
CarenResult CarenDXGIFactory4::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}