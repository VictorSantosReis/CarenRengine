﻿/*
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
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../DXGI\CarenDXGISwapChain.h"
#include "../DXGI\CarenDXGISwapChain1.h"
#include "CarenDXGIAdapter.h"
#include "CarenDXGIAdapter1.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por permitir o registro de notificações para detectar alterações no estado de enumeração 
/// do adaptador.
/// </summary>
public ref class CarenDXGIFactory7 : public ICarenDXGIFactory7
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIFactory7).
	IDXGIFactory7* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenDXGIFactory7();

	~CarenDXGIFactory7();


	//Conversões implicitas
public:
	static operator CarenDXGIFactory7^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenDXGIFactory7^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenDXGIFactory7();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IDXGIFactory7*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenDXGIFactory7::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenDXGIFactory7)
public:
	/// <summary>
	/// (RegisterAdaptersChangedEvent) - Registra-se para receber notificação de alterações sempre que o estado de enumeração do adaptador muda.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento.</param>
	/// <param name="Param_Out_Cookie">Recebe um valor da chave para o evento registrado.</param>
	virtual CarenResult RegisterAdaptersChangedEvent(ICarenEvent^ Param_HandleEvento, [Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (UnregisterAdaptersChangedEvent) - Cancela o registro do evento para parar de receber notificações quando o estado de enumeração do adaptador muda.
	/// </summary>
	/// <param name="Param_Cookie">O valor da chave do evento registrado para ser cancelado. Esse valor é obtido do método (RegisterAdaptersChangedEvent).</param>
	virtual CarenResult UnregisterAdaptersChangedEvent(UInt32 Param_Cookie);



	//Métodos da interface(ICarenDXGIFactory6)
public:
	/// <summary>
	/// (EnumAdapterByGpuPreference) - Enumera adaptadores gráficos com base em uma determinada preferência de GPU.
	/// </summary>
	/// <param name="Param_IndexAdaptador">O índice do adaptador para enumerar. Os índices estão por ordem da preferência especificada no CA_DXGI_GPU_PREFERENCE - por exemplo, 
	/// se CA_DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE for especificado, então o adaptador de maior desempenho está no índice 0, o segundo mais alto está no índice 1, e assim 
	/// por diante.</param>
	/// <param name="Param_PreferenciaGPU">A preferência da GPU pelo aplicativo</param>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro Param_Out_Adaptador.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface ICarenDXGIAdapter do adaptador.</param>
	virtual CarenResult EnumAdapterByGpuPreference(
		UInt32 Param_IndexAdaptador,
		CA_DXGI_GPU_PREFERENCE Param_PreferenciaGPU,
		String^ Param_RIID,
		ICaren^ Param_Out_Adaptador);



	//Métodos da interface(ICarenDXGIFactory5)
public:
	/// <summary>
	/// (CheckFeatureSupport) - Usado para verificar se há suporte ao recurso de hardware.
	/// </summary>
	/// <param name="Param_Recurso">Especifica um membro da CA_DXGI_FEATURE para consultar o suporte.</param>
	/// <param name="Param_SizeBuffer">O tamanho de Param_Ref_BufferDescFeature, em bytes.</param>
	/// <param name="Param_Ref_BufferDescFeature">Especifica um ponteiro para um buffer que será preenchido com dados que descrevem o suporte ao recurso.</param>
	virtual CarenResult CheckFeatureSupport(CA_DXGI_FEATURE Param_Recurso, UInt32 Param_SizeBuffer, ICarenBuffer^% Param_Ref_BufferDescFeature);



	//Métodos da interface(ICarenDXGIFactory4)
public:
	/// <summary>
	/// (EnumAdapterByLuid) - Enumera saídas do ICarenDXGIAdapter para o LUID especificado.
	/// </summary>
	/// <param name="Param_LUID">Um valor único que identifica o adaptador.</param>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
	/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
	virtual CarenResult EnumAdapterByLuid(CA_LUID^ Param_LUID, String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter);

	/// <summary>
	/// (EnumWarpAdapter) - Fornece um adaptador que pode ser fornecido a função D3D12CreateDevice para usar o renderizador WARP.
	/// </summary>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
	/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador. </param>
	virtual CarenResult EnumWarpAdapter(String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter);


	//Métodos da interface(ICarenDXGIFactory3)
public:
	/// <summary>
	/// (GetCreationFlags) - Recebe as bandeiras que foram usadas quando um objeto Microsoft DirectX Graphics Infrastructure (DXGI) foi criado.
	/// </summary>
	/// <param name="Param_Out_Flags">Retorna o flag utilizada na criação da fabrica(DXGIFactory).</param>
	virtual CarenResult GetCreationFlags([Out] UInt32% Param_Out_Flags);


	//Métodos da interface(ICarenDXGIFactory2)
public:
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
	virtual CarenResult CreateSwapChainForComposition(
		ICaren^ Param_DispositivoDirect3D,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

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
	virtual CarenResult CreateSwapChainForCoreWindow(
		ICaren^ Param_DispositivoDirect3D,
		ICaren^ Param_CoreWindow,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

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
	virtual CarenResult CreateSwapChainForHwnd(
		ICaren^ Param_DispositivoDirect3D,
		IntPtr Param_Handle,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_DescFullScreen,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

	/// <summary>
	/// (GetSharedResourceAdapterLuid) - Identifica o adaptador no qual um objeto de recurso compartilhado foi criado.
	/// </summary>
	/// <param name="Param_HandleRecurso">Uma alça para um objeto de recurso compartilhado. O método ICarenDXGIResource1::CreateSharedHandle devolve essa alça.</param>
	/// <param name="Param_Out_Luid">Retorna uma variavel que recebe um identificador localmente único(LUID). Valor que identifica o adaptador. Um CA_LUID é um valor de 64 bits 
	/// que é garantido para ser único apenas no sistema operacional em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema operacional seja 
	/// reiniciado.</param>
	virtual CarenResult GetSharedResourceAdapterLuid(IntPtr Param_HandleRecurso, [Out] CA_LUID^% Param_Out_Luid);

	/// <summary>
	/// (IsWindowedStereoEnabled) - Determina se deve usar o modo estéreo.
	/// </summary>
	/// <param name="Param_Out_ModoEstereoHabilitado">Retorna um valor que indica se deve usar o modo estéreo. TRUE indica que você pode usar o modo estéreo; se não, FALSO.</param>
	virtual CarenResult IsWindowedStereoEnabled([Out] Boolean% Param_Out_ModoEstereoHabilitado);

	/// <summary>
	/// (RegisterOcclusionStatusEvent) - Registra-se para receber notificação de alterações no status de oclusão usando a sinalização do evento.
	/// </summary>
	/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status de oclusão. 
	/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o 
	/// registro do evento de notificação que (Param_Evento) especifica.</param>
	virtual CarenResult RegisterOcclusionStatusEvent(ICarenEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterOcclusionStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações do status de oclusão.
	/// </summary>
	/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração de status de oclusão.</param>
	/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o registro da mensagem 
	/// de notificação que (Param_WinMensagemCode) especifica.</param>
	virtual CarenResult RegisterOcclusionStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterStereoStatusEvent) - Registra-se para receber notificação de alterações no status estéreo usando a sinalização do evento.
	/// </summary>
	/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status do modo Stereo. 
	/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o 
	/// registro do evento de notificação que (Param_Evento) especifica.</param>
	virtual CarenResult RegisterStereoStatusEvent(ICarenEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterStereoStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações de status estéreo.
	/// </summary>
	/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração do modo Stereo.</param>
	/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o registro da mensagem 
	/// de notificação que (Param_WinMensagemCode) especifica.</param>
	virtual CarenResult RegisterStereoStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (UnregisterOcclusionStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status de oclusão muda.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
	virtual CarenResult UnregisterOcclusionStatus(UInt32 Param_Cookie);

	/// <summary>
	/// (UnregisterStereoStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status estéreo muda.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
	virtual CarenResult UnregisterStereoStatus(UInt32 Param_Cookie);


	//Métodos da interface(ICarenDXGIFactory1)
public:
	/// <summary>
	/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
	/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
	/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
	/// </summary>
	/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
	virtual CarenResult EnumAdapters1(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter1^% Param_Out_Adaptador);

	/// <summary>
	/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
	/// </summary>
	/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
	virtual CarenResult IsCurrent([Out] Boolean% Param_Out_Atual);


	//Métodos da interface(ICarenDXGIFactory)
public:
	/// <summary>
	/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
	/// </summary>
	/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
	virtual CarenResult CreateSoftwareAdapter(IntPtr Param_ModuleHandle, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (CreateSwapChain) - Cria uma cadeia de swaps.
	/// [Começando com o Direct3D 11.1, recomendamos não usar mais o CreateSwapChain para criar uma cadeia de swaps. Em vez disso, use CreateSwapChainForHwnd, CreateSwapChainForCoreWindow, ou 
	/// CreateSwapChainForComposition dependendo de como você quer criar a cadeia de swap.]
	/// </summary>
	/// <param name="Param_Dispositivo3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. Para Direct3D 12 este é 
	/// um ponteiro para uma fila de comando direto(D3D12CommandQueue). Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_Desc">Uma estrutura CA_DXGI_SWAP_CHAIN_DESC para a descrição da cadeia de swap. Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_Out_SwapChain">Recebe um ponteiro para a interface do SwapChain.</param>
	virtual CarenResult CreateSwapChain(ICaren^ Param_Dispositivo3D, CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc, [Out] ICarenDXGISwapChain^% Param_Out_SwapChain);

	/// <summary>
	/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
	/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
	/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
	/// </summary>
	/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
	virtual CarenResult EnumAdapters(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
	/// </summary>
	/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
	virtual CarenResult GetWindowAssociation([Out] IntPtr% Param_HandleJanela);

	/// <summary>
	/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
	/// para tela cheia ou vice-versa).
	/// </summary>
	/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
	/// <param name="Param_Flags"></param>
	virtual CarenResult MakeWindowAssociation(IntPtr Param_HandleJanela, CA_DXGI_MWA_FLAGS Param_Flags);


	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// Define uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};