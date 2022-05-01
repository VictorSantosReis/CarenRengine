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
#include "../DXGI\CarenDXGISwapChain1.h"

//Destruidor.
CarenDXGISwapChain1::~CarenDXGISwapChain1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGISwapChain1::CarenDXGISwapChain1()
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
CarenResult CarenDXGISwapChain1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISwapChain1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISwapChain1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISwapChain1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISwapChain1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISwapChain1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISwapChain1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISwapChain1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISwapChain1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGISwapChain1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGISwapChain1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGISwapChain1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGISwapChain1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGISwapChain1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGISwapChain1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGISwapChain1();
}






//
// Métodos da interface proprietária(ICarenDXGISwapChain1)
//

/// <summary>
/// (GetBackgroundColor) - Recupera a cor de fundo da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Cor">Retorna uma estrutura que contém as informações de cor do Background.</param>
CarenResult CarenDXGISwapChain1::GetBackgroundColor([Out] CA_DXGI_RGBA^% Param_Out_Cor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_RGBA dxgiRGBAColor = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBackgroundColor(&dxgiRGBAColor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a cor no parametro.
	Param_Out_Cor = Util.ConverterDXGI_RGBAUnManaged_ToManaged(&dxgiRGBAColor);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCoreWindow) - Recupera o objeto CoreWindow subjacente para este objeto de cadeia de swap.
/// </summary>
/// <param name="Param_RIID">Um ponteiro para o identificador globalmente único(GUID) do objeto CoreWindow que é referenciado pelo parâmetro Param_Out_CoreWindow.</param>
/// <param name="Param_Out_CoreWindow">Retorna o ponteiro do objeto para a CoreWindow.  O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain1::GetCoreWindow(String^ Param_RIID, ICaren^ Param_Out_CoreWindow)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidCoreWin = GUID_NULL;
	PVOID pCoreWin = NULL;

	//Gera o guid a parti da string
	GuidCoreWin = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCoreWindow(GuidCoreWin, &pCoreWin);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do CoreWindow.
	Param_Out_CoreWindow->AdicionarPonteiro(pCoreWin);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc1) - Obtém uma descrição da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Desc">Retorna uma estrutura que contém a descrição da cadeia de Swap.</param>
CarenResult CarenDXGISwapChain1::GetDesc1([Out] CA_DXGI_SWAP_CHAIN_DESC1^% Param_Out_Desc)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_SWAP_CHAIN_DESC1 DescSwap = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc1(&DescSwap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida a estrutura convertida.
	Param_Out_Desc = Util.ConverterDXGI_SWAP_CHAIN_DESC1UnManaged_ToManaged(&DescSwap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFullscreenDesc) - Obtém uma descrição de uma cadeia de troca em tela cheia.
/// </summary>
/// <param name="Param_Out_DescFullScreenSwap">Retorna uma estrutura que contém a descrição no modo FullScreen na cadeia de Swap.</param>
CarenResult CarenDXGISwapChain1::GetFullscreenDesc([Out] CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^% Param_Out_DescFullScreenSwap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC DescFullScreen = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFullscreenDesc(&DescFullScreen);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida a estrutura gerenciada.
	Param_Out_DescFullScreenSwap = Util.ConverterDXGI_SWAP_CHAIN_FULLSCREEN_DESCUnManaged_ToManaged(&DescFullScreen);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetHwnd) - Recupera o HWND subjacente para este objeto de cadeia de swap.
/// </summary>
/// <param name="Param_Out_HWND">Retorna um ponteiro para o HWND do objeto de cadeia de Swap.</param>
CarenResult CarenDXGISwapChain1::GetHwnd([Out] IntPtr% Param_Out_HWND)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HWND pHandle = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetHwnd(&pHandle);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida
	Param_Out_HWND = Util.ConverterHWNDToIntPtr(pHandle);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetRestrictToOutput) - Obtém a saída (o monitor de exibição) ao qual você pode restringir o conteúdo de uma operação atual.
/// </summary>
/// <param name="Param_Out_Saida">Um ponteiro para um buffer que recebe um ponteiro para a interface IDXGIOutput para a saída de restrição.  Um aplicativo passa este ponteiro para 
/// ICarenDXGIOutput em uma chamada para o ICarenDXGIFactory2::CreateSwapChainForHwnd, ICarenDXGIFactory2::CreateSwapChainForCoreWindow, ou ICarenDXGIFactory2::CreateSwapChainForComposition</param>
CarenResult CarenDXGISwapChain1::GetRestrictToOutput([Out] ICarenDXGIOutput^% Param_Out_Saida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIOutput* pSaida = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRestrictToOutput(&pSaida);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada para o usuario.
	Param_Out_Saida = gcnew CarenDXGIOutput();

	//Define o ponteiro de trabalho.
	Param_Out_Saida->AdicionarPonteiro(pSaida);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetRotation) - Obtém a rotação dos buffers traseiros para a cadeia de swaps.
/// </summary>
/// <param name="Param_Out_Rotacao">Retorna uma enumeração que define a rotação do Buffer Traseiro(BackBuffer).</param>
CarenResult CarenDXGISwapChain1::GetRotation([Out] CA_DXGI_MODE_ROTATION% Param_Out_Rotacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_MODE_ROTATION Rotation;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRotation(&Rotation);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_Rotacao = static_cast<CA_DXGI_MODE_ROTATION>(Rotation);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsTemporaryMonoSupported) - Determina se uma cadeia de swap suporta "mono temporário".
/// </summary>
/// <param name="Param_Out_Suporte">Retorna um Booleano que define o suporte ao mono.</param>
CarenResult CarenDXGISwapChain1::IsTemporaryMonoSupported([Out] Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL Suported = FALSE;

	//Chama o método para realizar a operação.
	Suported = PonteiroTrabalho->IsTemporaryMonoSupported();

	//Define o resultado no parametro de saida
	Param_Out_Suporte = Suported ? true : false;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Present1) - Apresenta um Frame a tela de exibição.
/// </summary>
/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
/// <param name="Param_FlagsApresentacao">Um valor inteiro que contém opções de apresentação em cadeia de swaps.</param>
/// <param name="Param_ParametrosApresentacao">uma estrutura CA_DXGI_PRESENT_PARAMETERS que descreve retângulos atualizados e rolar informações do quadro para apresentar.</param>
CarenResult CarenDXGISwapChain1::Present1(UInt32 Param_IntervaloSincronizacao, CA_DXGI_PRESENT Param_FlagsApresentacao, CA_DXGI_PRESENT_PARAMETERS^ Param_ParametrosApresentacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT DxgiPresentFrameFlag = static_cast<UINT>(Param_FlagsApresentacao);
	DXGI_PRESENT_PARAMETERS* pParametrosApresentacao = NULL;

	//Converte a estrutura gerenciada
	pParametrosApresentacao = Util.ConverterDXGI_PRESENT_PARAMETERSManaged_ToUnManaged(Param_ParametrosApresentacao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Present1(Param_IntervaloSincronizacao, DxgiPresentFrameFlag, pParametrosApresentacao);

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
	//Libera a memoria para a estrutura de parametros de apresentação
	DeletarEstruturaSafe(&pParametrosApresentacao->pDirtyRects);
	DeletarEstruturaSafe(&pParametrosApresentacao->pScrollOffset);
	DeletarEstruturaSafe(&pParametrosApresentacao->pScrollRect);
	DeletarEstruturaSafe(&pParametrosApresentacao); //Deleta a memória para a estrutura principal.


	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetBackgroundColor) - Muda a cor de fundo da cadeia de swaps.
/// </summary>
/// <param name="Param_Cor">A nova cor para o Background do buffer traseiro.</param>
CarenResult CarenDXGISwapChain1::SetBackgroundColor(CA_DXGI_RGBA^ Param_Cor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_RGBA *pCorRGBA = NULL;

	//Converte a estrutura gerenciada
	pCorRGBA = Util.ConverterDXGI_RGBAManaged_ToUnManaged(Param_Cor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetBackgroundColor(pCorRGBA);

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
	//Libera a memoria para a estrutura.
	DeletarEstruturaSafe(&pCorRGBA);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetRotation) - Define a rotação dos buffers de volta para a cadeia de swap.
/// </summary>
/// <param name="Param_Rotacao">A nova rotação dos Buffers Traseiro(BackBuffers).</param>
CarenResult CarenDXGISwapChain1::SetRotation(CA_DXGI_MODE_ROTATION Param_Rotacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_MODE_ROTATION ModeRotation = static_cast<DXGI_MODE_ROTATION>(Param_Rotacao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRotation(ModeRotation);

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
// Métodos da interface proprietária(ICarenDXGISwapChain)
//

/// <summary>
/// (GetBuffer) - Acessa um dos buffers de volta da cadeia de swaps.
/// </summary>
/// <param name="Param_IndexBuffer">O Indince para o buffer de volta(Back-Buffer).</param>
/// <param name="Param_RiidInterface">O tipo de interface usada para manipular o buffer.</param>
/// <param name="Param_Out_InterfaceBuffer">Retorna a interface que gerencia o Buffer de volta(Back-Buffer). O Usuário é responsável por criar a interface que será retornada.</param>
CarenResult CarenDXGISwapChain1::GetBuffer(UInt32 Param_IndexBuffer, String^ Param_RiidInterface, ICaren^ Param_Out_InterfaceBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = GUID_NULL;
	LPVOID pInterfaceReturn = NULL;

	//Cria o Riid de identificação da superfice
	RiidInterface = Util.CreateGuidFromString(Param_RiidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBuffer(Param_IndexBuffer, RiidInterface, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro de trabalho
	Param_Out_InterfaceBuffer->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetContainingOutput) - Obtém a saída (o monitor de exibição) que contém a maior parte da área do cliente da janela alvo.
/// Se o método for bem-sucedido, a interface de saída será preenchida e sua contagem de referência incrementada. Quando você terminar com ele, não se esqueça de liberar a interface para evitar um vazamento de memória.
/// </summary>
/// <param name="Param_Out_MonitorSaida">Retorna a interface para o monitor de exbicão de saida.</param>
CarenResult CarenDXGISwapChain1::GetContainingOutput([Out] ICarenDXGIOutput^% Param_Out_MonitorSaida)

{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIOutput* pInterfaceReturn = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainingOutput(&pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada ao cliente.
	Param_Out_MonitorSaida = gcnew CarenDXGIOutput();

	//Define o ponteiro de saida
	Param_Out_MonitorSaida->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Obtém uma descrição da cadeia de swaps.
/// </summary>
/// <param name="Param_Out_DescricaoCadeiaSwap">Retorna uma estrutura com a descrição da cadeia de troca.</param>
CarenResult CarenDXGISwapChain1::GetDesc([Out] Estruturas::CA_DXGI_SWAP_CHAIN_DESC^% Param_Out_DescricaoCadeiaSwap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_SWAP_CHAIN_DESC DescSwap;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc(&DescSwap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_DescricaoCadeiaSwap = Util.ConverterDXGI_SWAP_CHAIN_DESCUnManaged_ToManaged(&DescSwap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFrameStatistics) - Obtém estatísticas de desempenho sobre o último quadro render.
/// </summary>
/// <param name="Param_Out_FrameEstatisticas">Retorna uma estrutura com as estatiticas do frame.</param>
CarenResult CarenDXGISwapChain1::GetFrameStatistics([Out] Estruturas::CA_DXGI_FRAME_STATISTICS^% Param_Out_FrameEstatisticas)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FRAME_STATISTICS DescFrame;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameStatistics(&DescFrame);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a estrutura no parametro de saida.
	Param_Out_FrameEstatisticas = Util.ConverterDXGI_FRAME_STATISTICSUnManaged_ToManaged(&DescFrame);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFullscreenState) - Associe o estado ao modo de tela cheia.
/// </summary>
/// <param name="Param_Out_EstadoFullScreen">Retorna o estado do FullScreen. Se TRUE, a cadeia de swap está no modo de tela cheia. Se FALSE, a cadeia de swap está em modo de janela.</param>
/// <param name="Param_Out_MonitorSaida">Retorna um ponteiro para o monitor de saida quando em modo de Tela Cheia(FullScreen); caso contrario retorna NULO.</param>
CarenResult CarenDXGISwapChain1::GetFullscreenState([Out] Boolean% Param_Out_EstadoFullScreen, [Out] ICarenDXGIOutput^% Param_Out_MonitorSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BOOL StateFullScreen = FALSE;
	IDXGIOutput* pInterfaceReturn = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFullscreenState(&StateFullScreen, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//A interface de retorno pode ou não ser valida.
	//Ela será valida apenas quando o modo tiver em FullScreen.
	if (StateFullScreen)
	{
		//Cria a interface porque o modo é de tela cheia.
		Param_Out_MonitorSaida = gcnew CarenDXGIOutput();

		//Define o ponteiro de trabalho.
		Param_Out_MonitorSaida->AdicionarPonteiro(pInterfaceReturn);
	}
	else
	{
		//O modo não é de tela cheia, portanto, não retorna a interface.
		Param_Out_MonitorSaida = nullptr;
	}

	//Define o estado do fullscreen
	Param_Out_EstadoFullScreen = StateFullScreen ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetLastPresentCount) - Obtém o número de vezes que o método ICarenDXGISwapChain::Apresentar ou ICarenDXGISwapChain1::Present1 foi chamado.
/// </summary>
/// <param name="Param_Out_QuantidadeChamadas">Retorna a quantidade de chamadas para o método Apresentar ou Present1.</param>
CarenResult CarenDXGISwapChain1::GetLastPresentCount([Out] UInt32% Param_Out_QuantidadeChamadas)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT CountPresentCalled = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetLastPresentCount(&CountPresentCalled);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a quantidade no parametro de saida.
	Param_Out_QuantidadeChamadas = CountPresentCalled;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Present) - Apresenta uma imagem renderizada ao usuário.
/// </summary>
/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
/// <param name="Param_Flags">Um valor inteiro que contém opções de apresentação em cadeia de swaps. Essas opções são definidas pela enumeração (CA_DXGI_PRESENT).</param>
CarenResult CarenDXGISwapChain1::Present(UInt32 Param_IntervaloSincronizacao, Enumeracoes::CA_DXGI_PRESENT Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT FlagsPresent = static_cast<UINT>(Param_Flags);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Present(Param_IntervaloSincronizacao, FlagsPresent);

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
CarenResult CarenDXGISwapChain1::ResizeBuffers(UInt32 Param_NumeroBuffers, UInt32 Param_Largura, UInt32 Param_Altura, Enumeracoes::CA_DXGI_FORMAT Param_NovoFormato, Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_NovoFormato);
	DXGI_SWAP_CHAIN_FLAG FlagSwap = static_cast<DXGI_SWAP_CHAIN_FLAG>(Param_SwapChainFlags);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ResizeBuffers(Param_NumeroBuffers, Param_Largura, Param_Altura, FormatoDXGI, FlagSwap);

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
/// (ResizeTarget) - Redimensiona a meta de saída.
/// </summary>
/// <param name="Param_NovaDesc">A estrutura CA_DXGI_MODE_DESC que descreve o modo, que especifica a nova largura, altura, formato e taxa de atualização do alvo. Se o formato for DXGI_FORMAT_UNKNOWN, o método (ResizeTarget)
/// utilizara o formato existente. Recomendamos apenas que você use DXGI_FORMAT_UNKNOWN quando a cadeia de swap está em modo de tela cheia, pois este método não é seguro para o segmento.</param>
CarenResult CarenDXGISwapChain1::ResizeTarget(Estruturas::CA_DXGI_MODE_DESC^ Param_NovaDesc)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_MODE_DESC* pDesc = NULL;

	//Converte a estrutura
	pDesc = Util.ConverterDXGI_MODE_DESCManaged_ToUnManaged(Param_NovaDesc);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ResizeTarget(pDesc);

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
/// (SetFullscreenState) - Define o estado de exibição para janelas ou tela cheia.
/// </summary>
/// <param name="Param_EstadoFullScreen">Um valor booleano que especifica se deve definir o estado de exibição para janelas ou tela cheia. VERDADE para tela cheia, e FALSO para janelas.</param>
/// <param name="Param_MonitorSaida">Se você passar o TRUE para o parâmetro (Param_EstadoFullScreen) para definir o estado de exibição para tela cheia, você pode definir opcionalmente este parâmetro para um ponteiro para uma interface
/// IDXGIOutput para o alvo de saída que contém a cadeia de swap. Se você definir este parâmetro para NULO, DXGI escolherá a saída com base no dispositivo da cadeia de swap e na colocação da janela de saída. Se você passar FALSE 
/// para (Param_EstadoFullScreen), você deve definir este parâmetro para NULO.</param>
CarenResult CarenDXGISwapChain1::SetFullscreenState(Boolean Param_EstadoFullScreen, ICarenDXGIOutput^ Param_MonitorSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BOOL StateFullScreen = Param_EstadoFullScreen ? TRUE : FALSE;
	IDXGIOutput* pSaida = NULL; //Pode ser NULO.

	//Verifica se forneceu um monitor de saida
	if (ObjetoGerenciadoValido(Param_MonitorSaida))
	{
		//Obtém o ponteiro para o objeto
		Param_MonitorSaida->RecuperarPonteiro((LPVOID*)&pSaida);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetFullscreenState(StateFullScreen, pSaida ? pSaida : NULL);

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



// Métodos da interface proprietária(ICarenDXGIDeviceSubObject)


/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISwapChain1::GetDevice(
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
CarenResult CarenDXGISwapChain1::GetParent(
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
CarenResult CarenDXGISwapChain1::SetPrivateData(
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
CarenResult CarenDXGISwapChain1::GetPrivateData(
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
CarenResult CarenDXGISwapChain1::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}