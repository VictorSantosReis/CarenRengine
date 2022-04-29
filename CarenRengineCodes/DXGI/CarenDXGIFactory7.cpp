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


#include "../pch.h"
#include "CarenDXGIFactory7.h"

//Destruidor.
CarenDXGIFactory7::~CarenDXGIFactory7()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGIFactory7::CarenDXGIFactory7()
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
CarenResult CarenDXGIFactory7::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory7::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory7*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory7**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory7::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory7*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory7**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory7::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory7::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIFactory7::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIFactory7::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIFactory7::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIFactory7::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIFactory7::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIFactory7::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIFactory7();
}


//
// Métodos da interface proprietária(ICarenDXGIFactory7)
//

/// <summary>
/// (RegisterAdaptersChangedEvent) - Registra-se para receber notificação de alterações sempre que o estado de enumeração do adaptador muda.
/// </summary>
/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento.</param>
/// <param name="Param_Out_Cookie">Recebe um valor da chave para o evento registrado.</param>
CarenResult CarenDXGIFactory7::RegisterAdaptersChangedEvent(ICarenEvent^ Param_HandleEvento, [Out] UInt32% Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandleEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera o ponteiro para o evento criado pelo usuário
	Resultado = Param_HandleEvento->RecuperarEvento(&pHandleEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha ao recuperar o evento.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterAdaptersChangedEvent(pHandleEvento, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Cookie gerado no parametro de saida.
	Param_Out_Cookie = OutCookie;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterAdaptersChangedEvent) - Cancela o registro do evento para parar de receber notificações quando o estado de enumeração do adaptador muda.
/// </summary>
/// <param name="Param_Cookie">O valor da chave do evento registrado para ser cancelado. Esse valor é obtido do método (RegisterAdaptersChangedEvent).</param>
CarenResult CarenDXGIFactory7::UnregisterAdaptersChangedEvent(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnregisterAdaptersChangedEvent(static_cast<DWORD>(Param_Cookie));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory6
//

/// <summary>
/// (EnumAdapterByGpuPreference) - Enumera adaptadores gráficos com base em uma determinada preferência de GPU.
/// </summary>
/// <param name="Param_IndexAdaptador">O índice do adaptador para enumerar. Os índices estão por ordem da preferência especificada no CA_DXGI_GPU_PREFERENCE - por exemplo, 
/// se CA_DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE for especificado, então o adaptador de maior desempenho está no índice 0, o segundo mais alto está no índice 1, e assim 
/// por diante.</param>
/// <param name="Param_PreferenciaGPU">A preferência da GPU pelo aplicativo</param>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro Param_Out_Adaptador.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface ICarenDXGIAdapter do adaptador.</param>
CarenResult CarenDXGIFactory7::EnumAdapterByGpuPreference(
	UInt32 Param_IndexAdaptador,
	CA_DXGI_GPU_PREFERENCE Param_PreferenciaGPU,
	String^ Param_RIID,
	ICaren^ Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIID);
	DXGI_GPU_PREFERENCE GpuPreference = static_cast<DXGI_GPU_PREFERENCE>(Param_PreferenciaGPU);
	PVOID pAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAdapterByGpuPreference(Param_IndexAdaptador, GpuPreference, RiidInterface, &pAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	Param_Out_Adaptador->AdicionarPonteiro(pAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory5
//

/// <summary>
/// (CheckFeatureSupport) - Usado para verificar se há suporte ao recurso de hardware.
/// </summary>
/// <param name="Param_Recurso">Especifica um membro da CA_DXGI_FEATURE para consultar o suporte.</param>
/// <param name="Param_SizeBuffer">O tamanho de Param_Ref_BufferDescFeature, em bytes.</param>
/// <param name="Param_Ref_BufferDescFeature">Especifica um ponteiro para um buffer que será preenchido com dados que descrevem o suporte ao recurso.</param>
CarenResult CarenDXGIFactory7::CheckFeatureSupport(CA_DXGI_FEATURE Param_Recurso, UInt32 Param_SizeBuffer, ICarenBuffer^% Param_Ref_BufferDescFeature)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PonteiroBuffer = IntPtr::Zero;
	DXGI_FEATURE Feature = static_cast<DXGI_FEATURE>(Param_Recurso);

	//Recupera o ponteiro para o buffer que vai ser preenchido com os dados.
	Resultado = Param_Ref_BufferDescFeature->GetInternalPointer(PonteiroBuffer);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao recuperar um ponteiro para o buffer.

		//Sai do método.
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckFeatureSupport(Feature, PonteiroBuffer.ToPointer(), Param_SizeBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory4
//

/// <summary>
/// (EnumAdapterByLuid) - Enumera saídas do ICarenDXGIAdapter para o LUID especificado.
/// </summary>
/// <param name="Param_LUID">Um valor único que identifica o adaptador.</param>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
CarenResult CarenDXGIFactory7::EnumAdapterByLuid(CA_LUID^ Param_LUID, String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LUID* pLuidEnum = Util.ConverterLUIDManagedToUnmanaged(Param_LUID);
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIID);
	PVOID pAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAdapterByLuid(*pLuidEnum, RiidInterface, &pAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai retornar o adaptador.
	Param_Out_InterfaceAdapter = gcnew Caren();

	//Define o ponteiro para o adaptador.
	Param_Out_InterfaceAdapter->AdicionarPonteiro(pAdaptador);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pLuidEnum);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (EnumWarpAdapter) - Fornece um adaptador que pode ser fornecido a função D3D12CreateDevice para usar o renderizador WARP.
/// </summary>
/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador. </param>
CarenResult CarenDXGIFactory7::EnumWarpAdapter(String^ Param_RIID, [Out] ICaren^ Param_Out_InterfaceAdapter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID pRIIDInterface = Util.CreateGuidFromString(Param_RIID);
	PVOID pAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumWarpAdapter(pRIIDInterface, &pAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai retornar o adaptador.
	Param_Out_InterfaceAdapter = gcnew Caren();

	//Define o ponteiro do adaptador.
	Param_Out_InterfaceAdapter->AdicionarPonteiro(pAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory3
//

/// <summary>
/// (GetCreationFlags) - Recebe as bandeiras que foram usadas quando um objeto Microsoft DirectX Graphics Infrastructure (DXGI) foi criado.
/// </summary>
/// <param name="Param_Out_Flags">Retorna o flag utilizada na criação da fabrica(DXGIFactory).</param>
CarenResult CarenDXGIFactory7::GetCreationFlags([Out] UInt32% Param_Out_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	UINT FlagsCreate = PonteiroTrabalho->GetCreationFlags();

	//Define os flags no parametro de saida.
	Param_Out_Flags = FlagsCreate;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}


//
// Métodos da interface ICarenDXGIFactory2
//

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
CarenResult CarenDXGIFactory7::CreateSwapChainForComposition(
	ICaren^ Param_DispositivoDirect3D,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivo3D = NULL;
	DXGI_SWAP_CHAIN_DESC1* pDescSwapChain = NULL;
	IDXGIOutput* pSaidaRestrita = NULL;
	IDXGISwapChain1* pSwapChain1 = NULL;

	//Recupera o ponteiro

	//Obtém o ponteiro para o dispositivo.
	Resultado = Param_DispositivoDirect3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada para nativa da descrição do Swap.
	pDescSwapChain = Util.ConverterDXGI_SWAP_CHAIN_DESC1Managed_ToUnManaged(Param_DescSwap);

	//Verifica se forneceu uma interface para restringir a saida
	if (ObjetoGerenciadoValido(Param_SaidaRestrita))
	{
		//Recupera o objeto
		Resultado = Param_SaidaRestrita->RecuperarPonteiro((LPVOID*)&pSaidaRestrita);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou...

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSwapChainForComposition(pDispositivo3D, pDescSwapChain, pSaidaRestrita ? pSaidaRestrita : NULL, &pSwapChain1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface gerenciada que vai conter o ponteiro para a nativa
	Param_Out_SwapChain = gcnew CarenDXGISwapChain1();

	//Define o ponteiro de trabalho
	Param_Out_SwapChain->AdicionarPonteiro(pSwapChain1);

Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescSwapChain);

	//Retorna o resultado.
	return Resultado;
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
CarenResult CarenDXGIFactory7::CreateSwapChainForCoreWindow(
	ICaren^ Param_DispositivoDirect3D,
	ICaren^ Param_CoreWindow,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivo3D = NULL;
	IUnknown* pCoreWindow = NULL;
	DXGI_SWAP_CHAIN_DESC1* pDescSwapChain = NULL;
	IDXGIOutput* pSaidaRestrita = NULL;
	IDXGISwapChain1* pSwapChain1 = NULL;

	//Recupera o ponteiro

	//Obtém o ponteiro para o dispositivo.
	Resultado = Param_DispositivoDirect3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para o CoreWindow.
	Resultado = Param_CoreWindow->RecuperarPonteiro((LPVOID*)&pCoreWindow);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada para nativa da descrição do Swap.
	pDescSwapChain = Util.ConverterDXGI_SWAP_CHAIN_DESC1Managed_ToUnManaged(Param_DescSwap);

	//Verifica se forneceu uma interface para restringir a saida
	if (ObjetoGerenciadoValido(Param_SaidaRestrita))
	{
		//Recupera o objeto
		Resultado = Param_SaidaRestrita->RecuperarPonteiro((LPVOID*)&pSaidaRestrita);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou...

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSwapChainForCoreWindow(pDispositivo3D, pCoreWindow, pDescSwapChain, pSaidaRestrita ? pSaidaRestrita : NULL, &pSwapChain1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface gerenciada que vai conter o ponteiro para a nativa
	Param_Out_SwapChain = gcnew CarenDXGISwapChain1();

	//Define o ponteiro de trabalho
	Param_Out_SwapChain->AdicionarPonteiro(pSwapChain1);

Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescSwapChain);

	//Retorna o resultado.
	return Resultado;
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
CarenResult CarenDXGIFactory7::CreateSwapChainForHwnd(
	ICaren^ Param_DispositivoDirect3D,
	IntPtr Param_Handle,
	CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
	CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_DescFullScreen,
	ICarenDXGIOutput^ Param_SaidaRestrita,
	[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivo3D = NULL;
	HWND pHandle = NULL;
	DXGI_SWAP_CHAIN_DESC1* pDescSwapChain = { 0 };
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDescFullScreen = { 0 };
	IDXGIOutput* pSaidaRestrita = NULL;
	IDXGISwapChain1* pSwapChain1 = NULL;

	//Obtém o ponteiro para o dispositivo.
	Resultado = Param_DispositivoDirect3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou...

		//Sai do método
		Sair;
	}

	//Obtém a Handle.
	pHandle = Util.ConverterIntPtrToHWND(Param_Handle);

	//Converte a estrutura gerenciada para nativa da descrição do Swap.
	pDescSwapChain = Util.ConverterDXGI_SWAP_CHAIN_DESC1Managed_ToUnManaged(Param_DescSwap);

	//Verifica se forneceu uma descrição para o swap em modo full Screen.
	if (ObjetoGerenciadoValido(Param_DescFullScreen))
	{
		//Converte a descrição da cadeia Swap em modo FullScreen do gerenciado para o nativo.
		pDescFullScreen = Util.ConverterDXGI_SWAP_CHAIN_FULLSCREEN_DESCManaged_ToUnManaged(Param_DescFullScreen);
	}

	//Verifica se forneceu uma interface para restringir a saida
	if (ObjetoGerenciadoValido(Param_SaidaRestrita))
	{
		//Recupera o objeto
		Resultado = Param_SaidaRestrita->RecuperarPonteiro((LPVOID*)&pSaidaRestrita);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Falhou...

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSwapChainForHwnd(pDispositivo3D, pHandle, pDescSwapChain, pDescFullScreen, pSaidaRestrita ? pSaidaRestrita : NULL, &pSwapChain1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_SwapChain = gcnew CarenDXGISwapChain1();

	//Define o ponteiro de trabalho
	Param_Out_SwapChain->AdicionarPonteiro(pSwapChain1);

Done:;
	//Libera a memoria para as estruturas.
	DeletarEstruturaSafe(&pDescSwapChain);
	DeletarEstruturaSafe(&pDescFullScreen);

	//Limpa os dados
	pHandle = NULL;
	pSaidaRestrita = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetSharedResourceAdapterLuid) - Identifica o adaptador no qual um objeto de recurso compartilhado foi criado.
/// </summary>
/// <param name="Param_HandleRecurso">Uma alça para um objeto de recurso compartilhado. O método ICarenDXGIResource1::CreateSharedHandle devolve essa alça.</param>
/// <param name="Param_Out_Luid">Retorna uma variavel que recebe um identificador localmente único(LUID). Valor que identifica o adaptador. Um CA_LUID é um valor de 64 bits 
/// que é garantido para ser único apenas no sistema operacional em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema operacional seja 
/// reiniciado.</param>
CarenResult CarenDXGIFactory7::GetSharedResourceAdapterLuid(IntPtr Param_HandleRecurso, [Out] CA_LUID^% Param_Out_Luid)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LUID LuidData = { 0 };
	HANDLE pHandle = Util.ConverterIntPtrToHandle(Param_HandleRecurso);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSharedResourceAdapterLuid(pHandle, &LuidData);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura do luid para uma gerenciada e define no parametro de saida.
	Param_Out_Luid = Util.ConverterLUIDUnmanagedToManaged(&LuidData);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsWindowedStereoEnabled) - Determina se deve usar o modo estéreo.
/// </summary>
/// <param name="Param_Out_ModoEstereoHabilitado">Retorna um valor que indica se deve usar o modo estéreo. TRUE indica que você pode usar o modo estéreo; se não, FALSO.</param>
CarenResult CarenDXGIFactory7::IsWindowedStereoEnabled([Out] Boolean% Param_Out_ModoEstereoHabilitado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	BOOL ResultWinStereo = FALSE;

	//Chama o método para realizar a operação.
	ResultWinStereo = PonteiroTrabalho->IsWindowedStereoEnabled();

	//Converte e define no parametro de saida
	Param_Out_ModoEstereoHabilitado = ResultWinStereo ? true : false;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterOcclusionStatusEvent) - Registra-se para receber notificação de alterações no status de oclusão usando a sinalização do evento.
/// </summary>
/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status de oclusão. 
/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o 
/// registro do evento de notificação que (Param_Evento) especifica.</param>
CarenResult CarenDXGIFactory7::RegisterOcclusionStatusEvent(ICarenEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE HandleEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera a handle do evento
	Resultado = Param_Evento->RecuperarEvento((LPVOID*)&HandleEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro do evento é invalido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterOcclusionStatusEvent(HandleEvento, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Cookie no parametro de saida
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterOcclusionStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações do status de oclusão.
/// </summary>
/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração de status de oclusão.</param>
/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o registro da mensagem 
/// de notificação que (Param_WinMensagemCode) especifica.</param>
CarenResult CarenDXGIFactory7::RegisterOcclusionStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HWND pHandleJanela = Util.ConverterIntPtrToHWND(Param_HandleJanela);
	DWORD OutCookie = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterOcclusionStatusWindow(pHandleJanela, Param_WinMensagemCode, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Cookie no parametro de saida
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterStereoStatusEvent) - Registra-se para receber notificação de alterações no status estéreo usando a sinalização do evento.
/// </summary>
/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status do modo Stereo. 
/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o 
/// registro do evento de notificação que (Param_Evento) especifica.</param>
CarenResult CarenDXGIFactory7::RegisterStereoStatusEvent(ICarenEvent^ Param_Evento, [Out] UInt32% Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE HandleEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera a handle do evento
	Resultado = Param_Evento->RecuperarEvento((LPVOID*)&HandleEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro do evento é invalido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterStereoStatusEvent(HandleEvento, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Cookie no parametro de saida
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterStereoStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações de status estéreo.
/// </summary>
/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração do modo Stereo.</param>
/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o registro da mensagem 
/// de notificação que (Param_WinMensagemCode) especifica.</param>
CarenResult CarenDXGIFactory7::RegisterStereoStatusWindow(IntPtr Param_HandleJanela, UInt32 Param_WinMensagemCode, [Out] UInt32% Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HWND pHandleJanela = Util.ConverterIntPtrToHWND(Param_HandleJanela);
	DWORD OutCookie = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterStereoStatusWindow(pHandleJanela, Param_WinMensagemCode, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Cookie no parametro de saida
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterOcclusionStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status de oclusão muda.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
CarenResult CarenDXGIFactory7::UnregisterOcclusionStatus(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UnregisterOcclusionStatus(Param_Cookie);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterStereoStatus) - Desregistrar uma janela ou um evento para impedi-lo de receber notificação quando o status estéreo muda.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
CarenResult CarenDXGIFactory7::UnregisterStereoStatus(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UnregisterStereoStatus(Param_Cookie);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory1
//

/// <summary>
/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory7::EnumAdapters1(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter1^% Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIAdapter1* pVideoCardAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAdapters1(Param_IdAdaptador, &pVideoCardAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada
	Param_Out_Adaptador = gcnew CarenDXGIAdapter1();

	//Define o ponteiro de trabalho
	Param_Out_Adaptador->AdicionarPonteiro(pVideoCardAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
/// </summary>
/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
CarenResult CarenDXGIFactory7::IsCurrent([Out] Boolean% Param_Out_Atual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	BOOL Result = FALSE;

	//Chama o método para realizar a operação.
	Result = PonteiroTrabalho->IsCurrent();

	//Define no parametro de saida.
	Param_Out_Atual = Result ? TRUE : FALSE;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIFactory
//

/// <summary>
/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
/// </summary>
/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
CarenResult CarenDXGIFactory7::CreateSoftwareAdapter(IntPtr Param_ModuleHandle, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIAdapter* pAdaptador = NULL;
	HMODULE ModuleDll = static_cast<HMODULE>(Param_ModuleHandle.ToPointer());

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSoftwareAdapter(ModuleDll, &pAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada
	Param_Out_Adaptador = gcnew CarenDXGIAdapter();

	//Deifne o ponteiro de trabalho
	Param_Out_Adaptador->AdicionarPonteiro(pAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
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
CarenResult CarenDXGIFactory7::CreateSwapChain(ICaren^ Param_Dispositivo3D, CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc, [Out] ICarenDXGISwapChain^% Param_Out_SwapChain)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivoDirect3D = NULL;
	DXGI_SWAP_CHAIN_DESC* pDescSwap = NULL;
	IDXGISwapChain* pSwapChain = NULL;

	//Recupera o ponteiro para o dispositivo.
	Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoDirect3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada
	pDescSwap = Util.ConverterDXGI_SWAP_CHAIN_DESCManaged_ToUnManaged(Param_Desc);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSwapChain(pDispositivoDirect3D, pDescSwap, &pSwapChain);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_SwapChain = gcnew CarenDXGISwapChain();

	//Define o ponteiro de trabalho
	Param_Out_SwapChain->AdicionarPonteiro(pSwapChain);

Done:;
	//Libera a memoria para a estrutura.
	DeletarEstruturaSafe(&pDescSwap);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory7::EnumAdapters(UInt32 Param_IdAdaptador, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIAdapter* pVideoCardAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAdapters(Param_IdAdaptador, &pVideoCardAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada
	Param_Out_Adaptador = gcnew CarenDXGIAdapter();

	//Define o ponteiro de trabalho
	Param_Out_Adaptador->AdicionarPonteiro(pVideoCardAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
/// </summary>
/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
CarenResult CarenDXGIFactory7::GetWindowAssociation([Out] IntPtr% Param_HandleJanela)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HWND pWinAssociation = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWindowAssociation(&pWinAssociation);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a handle no parametro de saida.
	Param_HandleJanela = Util.ConverterHWNDToIntPtr(pWinAssociation);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
/// para tela cheia ou vice-versa).
/// </summary>
/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
/// <param name="Param_Flags"></param>
CarenResult CarenDXGIFactory7::MakeWindowAssociation(IntPtr Param_HandleJanela, CA_DXGI_MWA_FLAGS Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HWND pWinAssociation = NULL;
	UINT Flags = static_cast<UINT>(Param_Flags);

	//Obtém a handle.
	pWinAssociation = Util.ConverterIntPtrToHWND(Param_HandleJanela);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MakeWindowAssociation(pWinAssociation, Flags);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}


// Métodos da interface ICarenDXGIObject


/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIFactory7::GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = GUID_NULL;
	LPVOID pInterfaceReturn = NULL;

	//Cria o guid da interface.
	RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetParent(RiidInterface, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro de trabalho na interface de saida.
	Param_Out_ObjetoPai->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGIFactory7::SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;

	//Cria o guid
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Recupera o ponteiro para os dados.
	Resultado = Param_Dados->RecuperarPonteiro(&pDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou. O ponteiro não era valido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateData(GuidIndent, Param_TamanhoDados, pDados);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIFactory7::GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;
	UINT SizeDados = NULL;

	//Cria o guid a parti da string.
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPrivateData(GuidIndent, &SizeDados, &pDados);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro para os dados.
	Param_Out_Dados->AdicionarPonteiro(pDados);

	//Adiciona o tamanho dos dados
	Param_Ref_TamanhoDados = SizeDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGIFactory7::SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Cria o guid
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)&pInterface);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateDataInterface(GuidInterface, pInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}