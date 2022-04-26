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
#include "CarenD3D11Device5.h"

//Destruidor.
CarenD3D11Device5::~CarenD3D11Device5()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD3D11Device5::CarenD3D11Device5()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD3D11Device5::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Device5::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID3D11Device5*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Device5::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID3D11Device5*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Device5::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Device5::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD3D11Device5::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD3D11Device5::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11Device5::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11Device5::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<ID3D11Device5*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11Device5::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<ID3D11Device5*>(PonteiroTrabalho))->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD3D11Device5::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD3D11Device5();
}



//Métodos da interface proprietária(ICarenD3D11Device5)


/// <summary>
/// (CreateFence) - Cria um objeto de cerca. 
/// Essa função de membro é equivalente ao Direct3D 12 ID3D12Device::CreateFence função, e se aplica entre Direct3D 11 e Direct3D 12 em cenários interop.
/// </summary>
/// <param name="Param_DadosInicias">O valor inicial da cerca.</param>
/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_FENCE_FLAG que são combinados usando uma operação or bitwise. O valor resultante especifica opções para a vedação.</param>
/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface de cerca(ICarenD3D11Fence).</param>
/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence que é usado para acessar a cerca.</param>
CarenResult CarenD3D11Device5::CreateFence(
				UInt64 Param_DadosInicias, 
				CA_D3D11_FENCE_FLAG Param_Flags, 
				String^ Param_RIIDInterface, 
				ICarenD3D11Fence^% Param_Ref_FenceInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_FENCE_FLAG FenceFlag = static_cast<D3D11_FENCE_FLAG>(Param_Flags);
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);
	void* pOutFence = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateFence(Param_DadosInicias, FenceFlag, RiidInterface, &pOutFence);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Adiciona o ponteiro a interface disponibilizada pelo usuário.
	Param_Ref_FenceInterface->AdicionarPonteiro(pOutFence);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OpenSharedFence) - Abre uma alça para uma cerca compartilhada usando HANDLE e REFIID. Esta função de membro é uma versão limitada do Direct3D 12 ID3D12Device::OpenSharedHandle função membro, e se aplica entre 
/// Direct3D 11 e Direct3D 12 em cenários interop.Ao contrário do ID3D12Device::OpenSharedHandle que opera com recursos, montes e cercas, a função ICarenD3D11Device5::OpenSharedFence só funciona em cercas; 
/// no Direct3D 11, os recursos compartilhados são abertos com a função de membro ICarenD3D11Device1::OpenSharedResource1.
/// </summary>
/// <param name="Param_Handle">A handle que foi devolvida por uma chamada para ICarenD3D11Fence::CreateSharedHandle ou ID3D12Device::CreateSharedHandle.</param>
/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface ICarenD3D11Fence</param>
/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence.</param>
CarenResult CarenD3D11Device5::OpenSharedFence(
				IntPtr Param_Handle,
				String^ Param_RIIDInterface,
				ICarenD3D11Fence^% Param_Ref_FenceInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pSharedHandle = Util.ConverterIntPtrToHandle(Param_Handle);
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);
	void* pOutFence = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenSharedFence(pSharedHandle, RiidInterface, &pOutFence);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Adiciona o ponteiro da interface
	Param_Ref_FenceInterface->AdicionarPonteiro(pOutFence);

Done:;
	//Retorna o resultado.
	return Resultado;
}




//Métodos da interface ICarenD3D11Device4


/// <summary>
/// (RegisterDeviceRemovedEvent) - Registra o evento "dispositivo removido" e indica quando um dispositivo Direct3D foi removido por qualquer motivo, usando um mecanismo de notificação assíncrona.
/// </summary>
/// <param name="Param_HandleEvento">Uma Handle para ser utilizada pelo evento.</param>
/// <param name="Param_Out_Cookie">Recebe um valor para informações sobre o evento "dispositivo removido", que pode ser usado no (UnregisterDeviceRemoved) para cancelar o registro do evento.</param>
CarenResult CarenD3D11Device5::RegisterDeviceRemovedEvent(
	ICarenEvent^ Param_HandleEvento,
	[Out] UInt32 Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	HANDLE pHandleEvento = NULL;
	DWORD OutCookieEvent = 0;

	//Recupera o ponteiro para a handle do evento
	Resultado = Param_HandleEvento->RecuperarEvento(&pHandleEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro do evento é invalido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterDeviceRemovedEvent(pHandleEvento, &OutCookieEvent);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o Cookie no parametro de saida.
	Param_Out_Cookie = static_cast<UInt32>(OutCookieEvent);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterDeviceRemoved) - Desregistra o evento "dispositivo removido".
/// </summary>
/// <param name="Param_Cookie">Um valor sobre o evento "dispositivo removido", recuperadas durante uma chamada de RegisterDeviceRemovedEvent bem sucedida.</param>
CarenResult CarenD3D11Device5::UnregisterDeviceRemoved(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UnregisterDeviceRemoved(static_cast<DWORD>(Param_Cookie));

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface ICarenD3D11Device3


/// <summary>
/// (CreateDeferredContext3) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_Flags">Reservado para uso futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface do contexto diferido 3.</param>
CarenResult CarenD3D11Device5::CreateDeferredContext3(
	UInt32 Param_Flags,
	[Out] ICarenD3D11DeviceContext3^% Param_Out_ContextoDiferido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext3* pOutContextoDispositivo3 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeferredContext3(Param_Flags, &pOutContextoDispositivo3);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_ContextoDiferido = gcnew CarenD3D11DeviceContext3();

	//Define o ponteiro do contexto na interface.
	Param_Out_ContextoDiferido->AdicionarPonteiro(pOutContextoDispositivo3);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateQuery1) - Cria um objeto de consulta para consulta de informações da unidade de processamento gráfico (GPU).
/// </summary>
/// <param name="Param_DescQuery">Uma estrutura CA_D3D11_QUERY_DESC1 que representa uma descrição de consulta.</param>
/// <param name="Param_Ref_Query">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Query1 para o objeto de consulta criado. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateQuery1(
	CA_D3D11_QUERY_DESC1^ Param_DescQuery,
	ICarenD3D11Query1^% Param_Ref_Query)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_QUERY_DESC1* pDesc = NULL;
	ID3D11Query1* pInterfaceReturn = NULL;

	//Converte a estrutura.
	pDesc = Util.ConverterD3D11_QUERY_DESC1Managed_ToUnManaged(Param_DescQuery);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQuery1(pDesc, ObjetoGerenciadoValido(Param_Ref_Query) ? &pInterfaceReturn : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_Query))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_Query->AdicionarPonteiro(pInterfaceReturn);
	}

Done:;
	//Deleta a memoria para a estrutura se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateRasterizerState2) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de amostras enquanto o UAV renderiza ou rasteriza.
/// </summary>
/// <param name="Param_DescRasterizador">Uma estrutura CA_D3D11_RASTERIZER_DESC2 que descreve o estado rasterizador.</param>
/// <param name="Param_Ref_Rasterizador">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RasterizerState2 para o objeto de estado rasterizador criado. Defina este parâmetro 
/// como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateRasterizerState2(
	CA_D3D11_RASTERIZER_DESC2^ Param_DescRasterizador,
	ICarenD3D11RasterizerState2^% Param_Ref_Rasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC2* pDescRasterizer = Util.ConverterD3D11_RASTERIZER_DESC2Managed_ToUnManaged(Param_DescRasterizador);
	ID3D11RasterizerState2* pOutRasterizador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRasterizerState2(pDescRasterizer, ObjetoGerenciadoValido(Param_Ref_Rasterizador) ? &pOutRasterizador : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_Rasterizador))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_Rasterizador->AdicionarPonteiro(pOutRasterizador);
	}

Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescRasterizer);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateRenderTargetView1) - Cria uma visão de destino renderizado para acessar dados de recursos.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para a interface ICarenD3D11Resource que representa um destino de renderização. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_RENDER_TARGET.</param>
/// <param name="Param_DescRenderTarget">Uma estrutura CA_D3D11_RENDER_TARGET_VIEW_DESC1 que representa uma descrição de exibição de destino de renderização. Defina este parâmetro como NULO para criar uma exibição que 
/// acesse todos os subrecursos no nível 0 do mipmap.</param>
/// <param name="Param_Ref_RenderTarget">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RenderTargetView1 para a exibição de destino de renderização criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateRenderTargetView1(
	ICarenD3D11Resource^ Param_Recurso,
	CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_DescRenderTarget,
	ICarenD3D11RenderTargetView1^% Param_Ref_RenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_RENDER_TARGET_VIEW_DESC1* pDescRenderTarget = Util.ConverterD3D11_RENDER_TARGET_VIEW_DESC1Managed_ToUnManaged(Param_DescRenderTarget);
	ID3D11RenderTargetView1* pOutRenderTarget = NULL;

	//Recupera o ponteiro para a interface de recurso.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRenderTargetView1(pRecurso, pDescRenderTarget, ObjetoGerenciadoValido(Param_Ref_RenderTarget) ? &pOutRenderTarget : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_RenderTarget))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_RenderTarget->AdicionarPonteiro(pOutRenderTarget);
	}



Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescRenderTarget);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateShaderResourceView1) - Cria uma visão de recursos sombreadores para acessar dados em um recurso.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para o recurso que servirá como entrada para um sombreador. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_SHADER_RESOURCE.</param>
/// <param name="Param_DescShader">Uma estrutura CA_D3D11_SHADER_RESOURCE_VIEW_DESC1 que descreve uma visão de recursos mais sombreados. Defina esse parâmetro como NULO para criar uma exibição que acesse todo o 
/// recurso (usando o formato com o que o recurso foi criado).</param>
/// <param name="Param_Ref_Shader">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11ShaderResourceView1 para a exibição de recursos de sombreamento criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateShaderResourceView1(
	ICarenD3D11Resource^ Param_Recurso,
	CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_DescShader,
	ICarenD3D11ShaderResourceView1^% Param_Ref_Shader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_SHADER_RESOURCE_VIEW_DESC1* pDescShaderView = Util.ConverterD3D11_SHADER_RESOURCE_VIEW_DESC1Managed_ToUnManaged(Param_DescShader);
	ID3D11ShaderResourceView1* pOutSharedView = NULL;

	//Recupera o ponteiro para a interface de recurso.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateShaderResourceView1(pRecurso, pDescShaderView, ObjetoGerenciadoValido(Param_Ref_Shader) ? &pOutSharedView : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_Shader))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_Shader->AdicionarPonteiro(pOutSharedView);
	}



Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescShaderView);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateTexture2D1) - Método responsável por criar uma textura 2D.
/// </summary>
/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE2D_DESC1 que descreve um recurso de textura 2D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 2D. Os aplicativos não podem especificar NULO para 
/// (Param_DadosSubrecurso) ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
/// <param name="Param_Ref_Textura2D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture2D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateTexture2D1(
	CA_D3D11_TEXTURE2D_DESC1^ Param_DescTextura,
	cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
	ICarenD3D11Texture2D1^% Param_Ref_Textura2D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_TEXTURE2D_DESC1* pDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pArraySubresourceData = NULL;
	UINT32 QuantidadeItemsArray = ObjetoGerenciadoValido(Param_DadosSubrecurso) ? static_cast<UINT32>(Param_DadosSubrecurso->Length) : 0;
	ID3D11Texture2D1* pInterfaceReturn = NULL;
	D3D11_SUBRESOURCE_DATA* pGetSubData = NULL;

	//Converte a estrutura de descrição da textura
	pDesc = Util.ConverterD3D11_TEXTURE2D_DESC1Managed_ToUnManaged(Param_DescTextura);

	//Verfica se foi fornecido um array com os dados de subrecursos
	if (ObjetoGerenciadoValido(Param_DadosSubrecurso))
	{
		//Cria um array com a quantidade informada.
		pArraySubresourceData = CriarMatrizEstruturas<D3D11_SUBRESOURCE_DATA>(QuantidadeItemsArray);

		//Faz um for para converter todas as estruturas.
		for (UINT32 i = 0; i < QuantidadeItemsArray; i++)
		{
			//Converte a estrutura.
			pGetSubData = Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_DadosSubrecurso[i]);

			//Converte a estrutura e define no array nativo.
			pArraySubresourceData[i] = *pGetSubData;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&pGetSubData);
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTexture2D1(pDesc, pArraySubresourceData, ObjetoGerenciadoValido(Param_Ref_Textura2D) ? &pInterfaceReturn : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_Textura2D))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_Textura2D->AdicionarPonteiro(pInterfaceReturn);
	}



Done:;
	//Deleta as esturturas se elas forem validas
	DeletarEstruturaSafe(&pDesc);
	DeletarMatrizEstruturasSafe(&pArraySubresourceData);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateTexture3D1) - Método responsável por criar uma textura 3D.
/// </summary>
/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE3D_DESC1 que descreve um recurso de textura 3D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 3D. Os aplicativos não podem especificar NULO para (Param_DadosSubrecurso)
/// ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
/// <param name="Param_Ref_Textura3D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture3D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateTexture3D1(
	CA_D3D11_TEXTURE3D_DESC1^ Param_DescTextura,
	cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
	ICarenD3D11Texture3D1^% Param_Ref_Textura3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_TEXTURE3D_DESC1* pDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pArraySubresourceData = NULL;
	UINT32 QuantidadeItemsArray = ObjetoGerenciadoValido(Param_DadosSubrecurso) ? static_cast<UINT32>(Param_DadosSubrecurso->Length) : 0;
	ID3D11Texture3D1* pInterfaceReturn = NULL;
	D3D11_SUBRESOURCE_DATA* pGetSubData = NULL;

	//Converte a estrutura de descrição da textura
	pDesc = Util.ConverterD3D11_TEXTURE3D_DESC1Managed_ToUnManaged(Param_DescTextura);

	//Verfica se foi fornecido um array com os dados de subrecursos
	if (ObjetoGerenciadoValido(Param_DadosSubrecurso))
	{
		//Cria um array com a quantidade informada.
		pArraySubresourceData = CriarMatrizEstruturas<D3D11_SUBRESOURCE_DATA>(QuantidadeItemsArray);

		//Faz um for para converter todas as estruturas.
		for (UINT32 i = 0; i < QuantidadeItemsArray; i++)
		{
			//Converte a estrutura.
			pGetSubData = Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_DadosSubrecurso[i]);

			//Converte a estrutura e define no array nativo.
			pArraySubresourceData[i] = *pGetSubData;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&pGetSubData);
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTexture3D1(pDesc, pArraySubresourceData, ObjetoGerenciadoValido(Param_Ref_Textura3D) ? &pInterfaceReturn : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_Textura3D))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_Textura3D->AdicionarPonteiro(pInterfaceReturn);
	}



Done:;
	//Deleta as esturturas se elas forem validas
	DeletarEstruturaSafe(&pDesc);
	DeletarMatrizEstruturasSafe(&pArraySubresourceData);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateUnorderedAccessView1) - Cria uma visão para acessar um recurso de acesso não ordenado.
/// </summary>
/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC1) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
/// <param name="Param_Ref_ViewUnordered">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11UnorderedAccessView1 para a exibição de acesso não ordenado criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device5::CreateUnorderedAccessView1(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^% Param_DescSombreador,
	ICarenD3D11UnorderedAccessView1^% Param_Ref_ViewUnordered)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_UNORDERED_ACCESS_VIEW_DESC1* pDescUnorderedView = Util.ConverterD3D11_UNORDERED_ACCESS_VIEW_DESC1Managed_ToUnManaged(Param_DescSombreador);
	ID3D11UnorderedAccessView1* pOutUnorderedView = NULL;

	//Recupera o ponteiro para a interface de recurso.
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para a interface é invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateUnorderedAccessView1(pRecurso, pDescUnorderedView, ObjetoGerenciadoValido(Param_Ref_ViewUnordered) ? &pOutUnorderedView : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se o usuário especificou a interface de retorno valida.
	//Se não, a função não vai adicionar um ponteiro porque o método apenas valida os parametros.
	if (ObjetoGerenciadoValido(Param_Ref_ViewUnordered))
	{
		//Como o usuário especificou, que dizer que a função não vai validar os parametros e vai retornar a interface.

		//Define o ponteiro de trabalho
		Param_Ref_ViewUnordered->AdicionarPonteiro(pOutUnorderedView);
	}



Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDescUnorderedView);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetImmediateContext3) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface do contexto imediato ICarenD3D11DeviceContext3.</param>
CarenResult CarenD3D11Device5::GetImmediateContext3([Out] ICarenD3D11DeviceContext3^% Param_Out_Contexto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext3* pOutContextoDispositivo3 = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetImmediateContext3(&pOutContextoDispositivo3);

	//Verifica se a interface retornada é valida
	if (!ObjetoValido(pOutContextoDispositivo3))
	{
		//A interface retornada não é valida.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface que será retornada.
	Param_Out_Contexto = gcnew CarenD3D11DeviceContext3();

	//Define o ponteiro do contexto na interface.
	Param_Out_Contexto->AdicionarPonteiro(pOutContextoDispositivo3);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReadFromSubresource) - Copia dados de uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
/// </summary>
/// <param name="Param_BufferDestino">Um ponteiro para os dados de destino na memória.</param>
/// <param name="Param_DestinoPassoLinha">O tamanho de uma linha dos dados de destino.</param>
/// <param name="Param_DestinoPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de destino.</param>
/// <param name="Param_RecursoOrigem">Um ponteiro para o recurso de origem.</param>
/// <param name="Param_IndiceSubrecursoOrigem">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
/// <param name="Param_CaixaOrigem">Uma caixa que define a parte do subrecurso de destino para copiar os dados de recurso. Se NULO, os dados são lidos do subrecurso destino sem deslocamento. As dimensões do destino 
/// devem se adequar ao destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, 
/// ou o valor frontal for maior ou igual ao valor de trás. Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
CarenResult CarenD3D11Device5::ReadFromSubresource(
	ICarenBuffer^ Param_BufferDestino,
	UInt32 Param_DestinoPassoLinha,
	UInt32 Param_DestinoPassoProfundidade,
	ICarenD3D11Resource^ Param_RecursoOrigem,
	UInt32 Param_IndiceSubrecursoOrigem,
	CA_D3D11_BOX^ Param_CaixaOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PonteiroDados = IntPtr::Zero;
	PBYTE pBufferDestino = NULL;
	ID3D11Resource* pRecursoOrigem = NULL;
	D3D11_BOX* pBox = ObjetoGerenciadoValido(Param_CaixaOrigem) ? Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_CaixaOrigem) : NULL;

	//Recupera o ponteiro para o buffer de destino
	Resultado = Param_BufferDestino->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pBufferDestino = (PBYTE)PonteiroDados.ToPointer();

	//Recupera o ponteiro para o recurso de origem.
	Param_RecursoOrigem->RecuperarPonteiro((LPVOID*)&pRecursoOrigem);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ReadFromSubresource(
		pBufferDestino,
		Param_DestinoPassoLinha,
		Param_DestinoPassoProfundidade,
		pRecursoOrigem,
		Param_IndiceSubrecursoOrigem,
		pBox);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria 
	DeletarEstruturaSafe(&pBox);
	pBufferDestino = NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (WriteToSubresource) - Copia dados em uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
/// </summary>
/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_IndiceSubrecursoDestino">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
/// <param name="Param_CaixaDestino">Uma caixa que define a parte do subrecurso de destino para copiar os dados do recurso em. Se NULO, os dados são gravados no subrecurso destino sem deslocamento. As dimensões da fonte 
/// devem se encaixar no destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, ou 
/// o valor frontal for maior ou igual ao valor de trás.Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
/// <param name="Param_BufferOrigem">Um ponteiro para os dados de origem na memória.</param>
/// <param name="Param_OrigemPassoLinha">O tamanho de uma linha dos dados de origem.</param>
/// <param name="Param_OrigemPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de origem.</param>
CarenResult CarenD3D11Device5::WriteToSubresource(
	ICarenD3D11Resource^ Param_RecursoDestino,
	UInt32 Param_IndiceSubrecursoDestino,
	CA_D3D11_BOX^ Param_CaixaDestino,
	ICarenBuffer^ Param_BufferOrigem,
	UInt32 Param_OrigemPassoLinha,
	UInt32 Param_OrigemPassoProfundidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PonteiroDados = IntPtr::Zero;
	PBYTE pBufferOrigem = NULL;
	ID3D11Resource* pRecursoDestino = NULL;
	D3D11_BOX* pBox = ObjetoGerenciadoValido(Param_CaixaDestino) ? Util.ConverterD3D11_BOXManaged_ToUnManaged(Param_CaixaDestino) : NULL;

	//Recupera o ponteiro para o buffer de destino
	Resultado = Param_BufferOrigem->GetInternalPointer(PonteiroDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pBufferOrigem = (PBYTE)PonteiroDados.ToPointer();

	//Recupera o ponteiro para o recurso de origem.
	Param_RecursoDestino->RecuperarPonteiro((LPVOID*)&pRecursoDestino);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->WriteToSubresource(
		pRecursoDestino,
		Param_IndiceSubrecursoDestino,
		pBox,
		pBufferOrigem,
		Param_OrigemPassoLinha,
		Param_OrigemPassoProfundidade);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria 
	DeletarEstruturaSafe(&pBox);
	pBufferOrigem = NULL;

	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface ICarenD3D11Device2


/// <summary>
/// (CheckMultisampleQualityLevels1) - Obtenha o número de níveis de qualidade disponíveis durante a multiamostragem.
/// </summary>
/// <param name="Param_Formato">O formato de textura durante a multiamostragem.</param>
/// <param name="Param_QuantidadeSample">O número de amostras durante a multiamostragem.</param>
/// <param name="Param_Flags">Uma combinação de D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAGS valores que são combinados usando uma operação ou bitwise. 
/// Atualmente, apenas D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE é suportado.</param>
/// <param name="Param_Out_NiveisQualidade">Recebe o número de níveis de qualidade suportados pelo adaptador</param>
CarenResult CarenD3D11Device5::CheckMultisampleQualityLevels1(
	CA_DXGI_FORMAT Param_Formato,
	UInt32 Param_QuantidadeSample,
	CA_D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG Param_Flags,
	[Out] UInt32% Param_Out_NiveisQualidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_FORMAT dxgiFormato = static_cast<DXGI_FORMAT>(Param_Formato);
	D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG FlagsMetodo = static_cast<D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG>(Param_Flags);
	UINT32 OutNiveisQualidadeDisponiveis = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckMultisampleQualityLevels1(dxgiFormato, Param_QuantidadeSample, FlagsMetodo, &OutNiveisQualidadeDisponiveis);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_NiveisQualidade = OutNiveisQualidadeDisponiveis;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDeferredContext2) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto diferido.</param>
CarenResult CarenD3D11Device5::CreateDeferredContext2(
	UInt32 Param_ContextFlags,
	[Out] ICarenD3D11DeviceContext2^% Param_Out_ContextoDiferido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext2* pOutContextoDispositivo2 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeferredContext2(Param_ContextFlags, &pOutContextoDispositivo2);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_ContextoDiferido = gcnew CarenD3D11DeviceContext2();

	//Define o ponteiro do contexto na interface.
	Param_Out_ContextoDiferido->AdicionarPonteiro(pOutContextoDispositivo2);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetImmediateContext2) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto imediato.</param>
CarenResult CarenD3D11Device5::GetImmediateContext2([Out] ICarenD3D11DeviceContext2^% Param_Out_Contexto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext2* pOutContextoDispositivo2 = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetImmediateContext2(&pOutContextoDispositivo2);

	//Verifica se a operação obteve sucesso.
	if (!ObjetoValido(pOutContextoDispositivo2))
	{
		//O ponteiro da interface não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface que será retornada.
	Param_Out_Contexto = gcnew CarenD3D11DeviceContext2();

	//Define o ponteiro do contexto na interface.
	Param_Out_Contexto->AdicionarPonteiro(pOutContextoDispositivo2);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetResourceTiling) - Obtém informações sobre como um recurso de Tiles é dividido em blocos.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para a interface de recurso ICarenD3D11Resource a ser obtida as informações.</param>
/// <param name="Param_Out_NumeroTilesParaRecurso">Uma variável que recebe o número de Tiles necessárias para armazenar todo o recurso de Tiles.</param>
/// <param name="Param_Out_DescPackedMip">Uma estrutura CA_D3D11_PACKED_MIP_DESC que o (GetResourceTiling) preenche com informações sobre como os 
/// mipmaps do recurso de Tiles estão embalados.</param>
/// <param name="Param_Out_DescTileShape">Recebe uma estrutura CA_D3D11_TILE_SHAPE que (GetResourceTiling) preenche com informações sobre a forma do bloco. 
/// São informações sobre como os pixels se encaixam nos blocos, independentemente das dimensões do recurso em Tiles, sem incluir os mipmaps compactados. 
/// Se todo o recurso lado a lado estiver embalado, esse parâmetro não terá sentido porque o recurso lado a lado não possui layout definido para 
/// mipmaps compactados. Nessa situação, (GetResourceTiling) define os membros de CA_D3D11_TILE_SHAPE como zeros.</param>
/// <param name="Param_Ref_CountSubrecursoTile">Uma variável que contém o número de Tiles no subrecurso. Na entrada, este é o número de subrecursos para 
/// consulta de Tiles; na saída, este é o número que foi realmente recuperado em (Param_Out_DescTileShape) (fixado ao que está disponível).</param>
/// <param name="Param_PrimeiroSubrecursoObter">O número da primeira Tile do subrecursos para obter. (GetResourceTiling) ignora este parâmetro se o número 
/// que o (Param_Ref_CountSubrecursoTile) aponta é 0.</param>
/// <param name="Param_Out_DescTileSubrecurso">Recebe uma estrutura CA_D3D11_SUBRESOURCE_TILING que o (GetResourceTiling) preenche com informações sobre Tile 
/// de subrecursos.</param>
CarenResult CarenD3D11Device5::GetResourceTiling(
	ICarenD3D11Resource^ Param_Recurso,
	[Out] UInt32% Param_Out_NumeroTilesParaRecurso,
	[Out] CA_D3D11_PACKED_MIP_DESC^% Param_Out_DescPackedMip,
	[Out] CA_D3D11_TILE_SHAPE^% Param_Out_DescTileShape,
	UInt32% Param_Ref_CountSubrecursoTile,
	UInt32 Param_PrimeiroSubrecursoObter,
	[Out] CA_D3D11_SUBRESOURCE_TILING^% Param_Out_DescTileSubrecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	UINT OutNumeroTiles = 0;
	D3D11_PACKED_MIP_DESC OutPackedDesc = { 0 };
	D3D11_TILE_SHAPE OutTileShape = { 0 };
	UINT32 OutRefCountSubrecursoTile = Param_Ref_CountSubrecursoTile; //Define um dado na entrada e recebe outro na saida.
	D3D11_SUBRESOURCE_TILING OutSubresourceTiling = { 0 };

	//Recupera o ponteiro para o recurso
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não falhou
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o recurso é invalido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetResourceTiling(
		pRecurso,
		&OutNumeroTiles,
		&OutPackedDesc,
		&OutTileShape,
		&OutRefCountSubrecursoTile,
		Param_PrimeiroSubrecursoObter,
		&OutSubresourceTiling);

	//Define os dados nos paramêtros de saida.
	Param_Out_NumeroTilesParaRecurso = OutNumeroTiles;
	Param_Out_DescPackedMip = Util.ConverterD3D11_PACKED_MIP_DESCUnManaged_ToManaged(&OutPackedDesc);
	Param_Out_DescTileShape = Util.ConverterD3D11_TILE_SHAPEUnManaged_ToManaged(&OutTileShape);
	Param_Ref_CountSubrecursoTile = OutRefCountSubrecursoTile;
	Param_Out_DescTileSubrecurso = Util.ConverterD3D11_SUBRESOURCE_TILINGUnManaged_ToManaged(&OutSubresourceTiling);

Done:;
	//Retorna o resultado.
	return Resultado;
}




//Métodos da interface ICarenD3D11Device1


/// <summary>
/// (CreateBlendState1) - Cria um objeto de estado-mistura que encapsula o estado de mistura para o estágio de fusão de saída e permite a configuração 
/// de operações lógicas.
/// </summary>
/// <param name="Param_Out_DescBlend">Recebe uma estrutura CA_D3D11_BLEND_DESC1 que descreve o BlendSate(Misturador de estado).</param>
/// <param name="Param_Out_BlendState">Recebe um ponteiro para a interface ICarenD3D11BlendState1 do misturador de estado.</param>
CarenResult CarenD3D11Device5::CreateBlendState1([Out] CA_D3D11_BLEND_DESC1^% Param_Out_DescBlend, [Out] ICarenD3D11BlendState1^% Param_Out_BlendState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_BLEND_DESC1 OutDesc = { 0 };
	ID3D11BlendState1* pBlendState1 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBlendState1(&OutDesc, &pBlendState1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada para a nativa e define no parametro de saida.
	Param_Out_DescBlend = Util.ConverterD3D11_BLEND_DESC1UnManaged_ToManaged(&OutDesc);

	//Cria a interface a ser retornada
	Param_Out_BlendState = gcnew CarenD3D11BlendState1();

	//Define o ponteiro na interface
	Param_Out_BlendState->AdicionarPonteiro(pBlendState1);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDeferredContext1) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interfcace ICarenD3D11DeviceContext1 do contexto diferido.</param>
CarenResult CarenD3D11Device5::CreateDeferredContext1(UInt32 Param_ContextFlags, [Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoDiferido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext1* pContextoDiferido1 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeferredContext1(Param_ContextFlags, &pContextoDiferido1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada
	Param_Out_ContextoDiferido = gcnew CarenD3D11DeviceContext1();

	//Define o ponteiro na interface
	Param_Out_ContextoDiferido->AdicionarPonteiro(pContextoDiferido1);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDeviceContextState) - Cria um objeto de estado de contexto que detém todo o estado Microsoft Direct3D e algum comportamento Direct3D.
/// </summary>
/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG que são combinados usando uma operação ou bitwise. 
/// O valor resultante especifica como criar o objeto de estado de contexto. A bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADEDé atualmente é 
/// a única bandeira definida. Se o dispositivo original foi criado com D3D11_CREATE_DEVICE_SINGLETHREADED, você deve criar todos os objetos de estado 
/// de contexto daquele dispositivo com a bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADED.</param>
/// <param name="Param_NiveisRecurso">Uma matriz de valores CA_D3D_FEATURE_LEVEL. A matriz pode conter elementos da lista a seguir e determina a ordem dos 
/// níveis de recurso para os quais a criação é tentada. Ao contrário do D3D11CreateDevice, você não pode definir (Param_NiveisRecurso) para NULO porque 
/// não há um array padrão de nível de recurso.</param>
/// <param name="Param_QuantidadeNiveisRecurso">O número de elementos em (Param_NiveisRecurso). Ao contrário do D3D11CreateDevice, você deve definir os 
/// Níveis de Recursos para maiores de 0, porque você não pode definir (Param_NiveisRecurso) para NULO.</param>
/// <param name="Param_VersaoSDK">A versão SDK. Você deve definir este parâmetro para D3D11_SDK_VERSION.</param>
/// <param name="Param_RIIDInterfaceEmulada">O identificador globalmente único (GUID) para a interface emulada. Esse valor especifica o comportamento do 
/// dispositivo quando o objeto de estado de contexto está ativo.</param>
/// <param name="Param_Out_NivelRecursoDefinido">Recebe o nivel de recurso que foi aceito.</param>
/// <param name="Param_Out_EstadoContextoDispositivo">Recebe um ponteiro para um objeto ICarenD3DDeviceContextState que representa o estado de um dispositivo Direct3D.</param>
CarenResult CarenD3D11Device5::CreateDeviceContextState(
	CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG Param_Flags,
	cli::array<CA_D3D_FEATURE_LEVEL>^ Param_NiveisRecurso,
	UInt32 Param_QuantidadeNiveisRecurso,
	UInt32 Param_VersaoSDK,
	String^ Param_RIIDInterfaceEmulada,
	[Out] CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecursoDefinido,
	[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoContextoDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG StateFlag = static_cast<D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG>(Param_Flags);
	D3D_FEATURE_LEVEL* pArrayFeatures = CriarMatrizUnidimensional<D3D_FEATURE_LEVEL>(Param_QuantidadeNiveisRecurso);
	D3D_FEATURE_LEVEL OutNivelRecursoDefinido;
	ID3DDeviceContextState* pDispositivoEstado = NULL;
	GUID IdInterface = GUID_NULL;

	//Copia os niveis de recurso para a matriz nativa.
	Util.CopiarItensTo_ArrayNativo(&pArrayFeatures, Param_NiveisRecurso, Param_QuantidadeNiveisRecurso);

	//Cria o guid da interface
	IdInterface = Util.CreateGuidFromString(Param_RIIDInterfaceEmulada);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeviceContextState(StateFlag, pArrayFeatures, Param_QuantidadeNiveisRecurso, Param_VersaoSDK, IdInterface, &OutNivelRecursoDefinido, &pDispositivoEstado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o nivel de recurso que foi usado.
	Param_Out_NivelRecursoDefinido = static_cast<CA_D3D_FEATURE_LEVEL>(OutNivelRecursoDefinido);

	//Cria a interface a ser retornada
	Param_Out_EstadoContextoDispositivo = gcnew CarenD3DDeviceContextState();

	//Define o ponteiro na interface
	Param_Out_EstadoContextoDispositivo->AdicionarPonteiro(pDispositivoEstado);

Done:;
	//Libera a memoria para a matriz.
	DeletarMatrizUnidimensionalSafe(&pArrayFeatures);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateRasterizerState1) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de 
/// amostras enquanto o UAV renderiza ou rasteriza.
/// </summary>
/// <param name="Param_Out_DescRasterizer">Recebe uma estrutura com a descrição do rasterizador.</param>
/// <param name="Param_Out_Rasterizador">Recebe um ponteiro para a interface do rasterizador de estado.</param>
CarenResult CarenD3D11Device5::CreateRasterizerState1(
	[Out] CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizer,
	[Out] ICarenD3D11RasterizerState1^% Param_Out_Rasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC1 OutDescRasterizer;
	ID3D11RasterizerState1* pOutRasterizador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRasterizerState1(&OutDescRasterizer, &pOutRasterizador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para gerenciada e define no parametro de saida.
	Param_Out_DescRasterizer = Util.ConverterD3D11_RASTERIZER_DESC1UnManaged_ToManaged(&OutDescRasterizer);

	//Cria a interface a ser retornada
	Param_Out_Rasterizador = gcnew CarenD3D11RasterizerState1();

	//Define o ponteiro na interface
	Param_Out_Rasterizador->AdicionarPonteiro(pOutRasterizador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetImmediateContext1) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_ContextoImediato">Recebe um ponteiro para a interface ICarenD3D11DeviceContext1 do contexto imediato.</param>
CarenResult CarenD3D11Device5::GetImmediateContext1([Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoImediato)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext1* pOutContextoImdt1 = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetImmediateContext1(&pOutContextoImdt1);

	//Verifica se obteve com sucesso
	if (!ObjetoValido(pOutContextoImdt1))
	{
		//Define que o ponteiro retornado não é valido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface a ser retornada
	Param_Out_ContextoImediato = gcnew CarenD3D11DeviceContext1();

	//Define o ponteiro na interface
	Param_Out_ContextoImediato->AdicionarPonteiro(pOutContextoImdt1);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OpenSharedResource1) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado por uma alça e que foi criado em um dispositivo diferente.
/// </summary>
/// <param name="Param_HandleRecurso">Uma Handle para abrir o recurso. </param>
/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
/// não pode ser NULO.</param>
CarenResult CarenD3D11Device5::OpenSharedResource1(
	IntPtr Param_HandleRecurso,
	String^ Param_RIIDInterface,
	ICaren^% Param_Ref_InterfaceRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandleRecurso = Util.ConverterIntPtrToHandle(Param_HandleRecurso);
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);;
	void* pInterfaceRecurso = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenSharedResource1(pHandleRecurso, RiidInterface, &pInterfaceRecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro do recurso na interface fornecida.
	Param_Ref_InterfaceRecurso->AdicionarPonteiro(pInterfaceRecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OpenSharedResourceByName) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado pelo nome e que foi criado em um dispositivo 
/// diferente.
/// </summary>
/// <param name="Param_Nome">O nome do recurso para abrir. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_TipoAcesso">Os direitos de acesso solicitados ao recurso. Você pode utilizar as enumerações CA_ACCESS_RIGHTS e 
/// CA_DXGI_SHARED_RESOURCE_RW para definir este valor.</param>
/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
/// não pode ser NULO.</param>
CarenResult CarenD3D11Device5::OpenSharedResourceByName(
	String^ Param_Nome,
	UInt32 Param_TipoAcesso,
	String^ Param_RIIDInterface,
	ICaren^% Param_Ref_InterfaceRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPWSTR pNomeRecurso = Util.ConverterStringToWCHAR(Param_Nome);
	GUID RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);;
	void* pInterfaceRecurso = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenSharedResourceByName(pNomeRecurso, Param_TipoAcesso, RiidInterface, &pInterfaceRecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro do recurso na interface fornecida
	Param_Ref_InterfaceRecurso->AdicionarPonteiro(pInterfaceRecurso);

Done:;
	//Libera a memoria para o nome do recurso
	delete pNomeRecurso;

	//Retorna o resultado.
	return Resultado;
}






//Métodos da interface ICarenD3D11Device


/// <summary>
/// (CheckCounter) - Obtém o tipo, nome, unidades de medida e uma descrição de um contador existente.
/// </summary>
/// <param name="Param_DescContador">Ponteiro para uma descrição do contador (CA_D3D11_DESC_CONTADOR). Especifica qual contador informação é para ser obtida sobre.</param>
/// <param name="Param_Out_TipoDadoContador">Ponteiro para o tipo de dados de um contador (CA_D3D11_TIPO_DADO_CONTADOR). Especifica o tipo de dados do contador de ser obtido.</param>
/// <param name="Param_Out_NumeroContadores">Ponteiro para o número de contadores de hardware que são necessários para esse tipo de contador ser criado. Todas as instâncias do mesmo tipo contador usam os contadores de hardware mesmo.</param>
/// <param name="Param_Out_NomeContador">Sequência a ser preenchido com um nome breve para o contador. Pode ser NULL se o aplicativo não está interessado em nome do balcão.</param>
/// <param name="Param_Out_LarguraNomeContador">Comprimento da sequência de caracteres retornada para Param_Out_NomeContador. Pode ser nulo.</param>
/// <param name="Param_Out_NomeUnidadeMedidas">Nome das unidades de medidas um contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
/// <param name="Param_Out_LarguraNomeUnidade">Comprimento da sequência de caracteres retornado para o Param_Out_NomeUnidadeMedidas. Pode ser nulo.</param>
/// <param name="Param_Out_DescContador">Uma descrição do contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
/// <param name="Param_Out_LarguraDescContador">Comprimento da sequência de caracteres retornada para Param_Out_DescContador. Pode ser nulo.</param>
CarenResult CarenD3D11Device5::CheckCounter(
	Estruturas::CA_D3D11_DESC_CONTADOR^ Param_DescContador,
	[Out] Enumeracoes::CA_D3D11_TIPO_DADO_CONTADOR% Param_Out_TipoDadoContador,
	[Out] UInt32% Param_Out_NumeroContadores,
	[Out] String^% Param_Out_NomeContador,
	[Out] UInt32% Param_Out_LarguraNomeContador,
	[Out] String^% Param_Out_NomeUnidadeMedidas,
	[Out] UInt32% Param_Out_LarguraNomeUnidade,
	[Out] String^% Param_Out_DescContador,
	[Out] UInt32% Param_Out_LarguraDescContador
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_COUNTER_DESC* pDesc;
	D3D11_COUNTER_TYPE TipoContador;
	UINT pNumeroContadores = 0;
	LPSTR pNomeContador = NULL;
	UINT pLarguraNomeContador = 0;
	LPSTR pNomeUnidadeMedidas = NULL;
	UINT pLarguraUnidadeMedidas = 0;
	LPSTR pDescricaoContador = NULL;
	UINT pLarguraDescricaoContador = 0;

	//Converte a estrutura.
	pDesc = Util.ConverterD3D11_COUNTER_DESCManaged_ToUnManaged(Param_DescContador);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckCounter(pDesc, &TipoContador, &pNumeroContadores, pNomeContador, &pLarguraNomeContador, pNomeUnidadeMedidas, &pLarguraUnidadeMedidas, pDescricaoContador, &pLarguraDescricaoContador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_TipoDadoContador = static_cast<CA_D3D11_TIPO_DADO_CONTADOR>(TipoContador);
	Param_Out_NumeroContadores = pNumeroContadores;
	Param_Out_NomeContador = gcnew String(pNomeContador);
	Param_Out_LarguraNomeContador = pLarguraNomeContador;
	Param_Out_NomeUnidadeMedidas = gcnew String(pNomeUnidadeMedidas);
	Param_Out_LarguraNomeUnidade = pLarguraUnidadeMedidas;
	Param_Out_DescContador = gcnew String(pDescricaoContador);
	Param_Out_LarguraDescContador = pLarguraDescricaoContador;



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CheckCounterInfo) - Obter informações de um contador.
/// </summary>
/// <param name="Param_Out_InfoContador">Recebe uma estrutura com as informações do contador.</param>
CarenResult CarenD3D11Device5::CheckCounterInfo([Out] Estruturas::CA_D3D11_INFO_CONTADOR^% Param_Out_InfoContador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_COUNTER_INFO pCounterInfo;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CheckCounterInfo(&pCounterInfo);

	//Converte a estrutura para o parametro de saida.
	Param_Out_InfoContador = Util.ConverterD3D11_COUNTER_INFOUnManaged_ToManaged(&pCounterInfo);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CheckFeatureSupport) - Obtém informações sobre os recursos que são suportados pelo driver de gráficos atuais.
/// </summary>
/// <param name="Param_RecursoPesquisa">Um membro do CA_D3D11_RECURSO tipo enumerado que descreve qual recurso de consulta para apoio.</param>
/// <param name="Param_Out_SuporteRecurso">Após a conclusão do método, a passado estrutura é preenchida com dados que descreve o suporte para o recurso.</param>
/// <param name="Param_Out_TamanhoEstrutura">O tamanho da estrutura passado para o parâmetro Param_Out_SuporteRecurso.</param>
CarenResult CarenD3D11Device5::CheckFeatureSupport(
	Enumeracoes::CA_D3D11_RECURSO Param_RecursoPesquisa,
	[Out] Estruturas::CA_D3D11_FEATURE_DATA_THREADING^% Param_Out_SuporteRecurso,
	[Out] UInt32% Param_Out_TamanhoEstrutura
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_FEATURE FeatureEnum = static_cast<D3D11_FEATURE>(Param_RecursoPesquisa);
	D3D11_FEATURE_DATA_THREADING FeatureData;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckFeatureSupport(FeatureEnum, &FeatureData, sizeof(D3D11_FEATURE_DATA_THREADING));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para o parametro de saida.
	Param_Out_SuporteRecurso = Util.ConverterD3D11_FEATURE_DATA_THREADINGUnManaged_ToManaged(&FeatureData);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CheckFormatSupport) - Obter o apoio de um determinado formato do dispositivo de vídeo instalado.
/// </summary>
/// <param name="Param_Formato">Uma enumeração de CA_DXGI_FORMAT que descreve um formato para o qual deseja verificar se há suporte.</param>
/// <param name="Param_Out_RecursosSuportados">Um campo de bits de D3D11_FORMAT_SUPPORT valores de enumeração que descreve como o formato especificado 
/// é suportado no dispositivo instalado. Os valores são ORed juntos.</param>
CarenResult CarenD3D11Device5::CheckFormatSupport(
	Enumeracoes::CA_DXGI_FORMAT Param_Formato,
	[Out] Enumeracoes::CA_D3D11_FORMAT_SUPPORT% Param_Out_RecursosSuportados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT Formato = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT pFormatoD3D11Suportado = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckFormatSupport(Formato, &pFormatoD3D11Suportado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte o bitfield para sua enumeração correspondente.
	Param_Out_RecursosSuportados = static_cast<CA_D3D11_FORMAT_SUPPORT>(pFormatoD3D11Suportado);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CheckMultisampleQualityLevels) - Obter o número de níveis de qualidade disponíveis durante multisampling completo.
/// Quando multisampling uma textura, o número de níveis de qualidade disponíveis para um adaptador é dependente do formato de textura usado e o número de amostras 
/// solicitadas. O número máximo de níveis de qualidade é definido pelo D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT em D3D11.h. Se esse método retorna 0, a combinação de 
/// contagem de formato e amostra não tem suporte para o adaptador instalado.
/// </summary>
/// <param name="Param_Formato">O formato de textura. Consulte CA_DXGI_FORMAT.</param>
/// <param name="Param_NumeroAmostras">O número de amostras durante multisampling completo.</param>
/// <param name="Param_Out_NumeroNiveisQualidade">Recebe o número de níveis de qualidade suportada pelo adaptador.</param>
CarenResult CarenD3D11Device5::CheckMultisampleQualityLevels(
	Enumeracoes::CA_DXGI_FORMAT Param_Formato,
	UInt32 Param_NumeroAmostras,
	[Out] UInt32% Param_Out_NumeroNiveisQualidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT Formato = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT QuantidadeNiveisQualidade = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckMultisampleQualityLevels(Formato, Param_NumeroAmostras, &QuantidadeNiveisQualidade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o numero de niveis de qualidade no parametro de saida.
	Param_Out_NumeroNiveisQualidade = QuantidadeNiveisQualidade;



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateBlendState) - Crie um objeto de mistura-estado que encapsules o estado de combinação para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_DescMistura">Uma descrição do estado de mistura.</param>
/// <param name="Param_Out_BlendState">Recebe uma interface para o objeto de estado de mistura criado.</param>
CarenResult CarenD3D11Device5::CreateBlendState(
	Estruturas::CA_D3D11_BLEND_DESC^% Param_DescMistura,
	[Out] ICarenD3D11BlendState^% Param_Out_BlendState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_BLEND_DESC* pBlendDesc = NULL;
	ID3D11BlendState* pBlendState = NULL;

	//Converte a estrutura
	pBlendDesc = Util.ConverterD3D11_BLEND_DESCManaged_ToUnManaged(Param_DescMistura);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBlendState(pBlendDesc, &pBlendState);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada no parametro.
	Param_Out_BlendState = gcnew CarenD3D11BlendState();

	//Define o ponteiro de trabalho
	Param_Out_BlendState->AdicionarPonteiro(pBlendState);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateBuffer) - Cria um buffer (buffer de vértice, buffer de índice ou constante de sombreador buffer).
/// </summary>
/// <param name="Param_DescBuffer">Uma estrutura(CA_D3D11_BUFFER_DESC) que descreve o buffer.</param>
/// <param name="Param_DescDadosInit">uma estrutura(CA_D3D11_SUBRESOURCE_DATA) que descreve os dados de inicialização; Use NULL para alocar espaço só(com a exceção que não pode ser NULL se o sinalizador de 
/// uso é D3D11_USAGE_IMMUTABLE). Se você não passar nada para este paramêtro, o conteúdo inicial da memória para o buffer é indefinido. Neste caso, você precisa escrever o conteúdo do buffer de outra 
/// maneira, antes que o recurso é lido.</param>
/// <param name="Param_ValidarPametros">Defina como TRUE para validar os paramêtros de entrada do método. Se TRUE, Param_Out_InterfaceBuffer retorna NULO.</param>
/// <param name="Param_Out_InterfaceBuffer">Recebe a interface ICarenD3D11Buffer para o objeto de buffer criado.</param>
CarenResult CarenD3D11Device5::CreateBuffer(
	Estruturas::CA_D3D11_BUFFER_DESC^% Param_DescBuffer,
	Estruturas::CA_D3D11_SUBRESOURCE_DATA^% Param_DescDadosInit,
	Boolean Param_ValidarPametros,
	[Out] ICarenD3D11Buffer^% Param_Out_InterfaceBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_BUFFER_DESC* pBufferDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pSubresourceDesc = NULL;
	ID3D11Buffer* pBuffer = NULL;

	//Converte as estruturas.
	pBufferDesc = Util.ConverterD3D11_BUFFER_DESCManaged_ToUnmanaged(Param_DescBuffer);

	//Verifica se forneceu um estrutura de sub recursos
	if (ObjetoGerenciadoValido(Param_DescDadosInit))
	{
		//O usuário forneceu a estrutura.

		//Converte a estrutura gerenciada para a nativa.
		pSubresourceDesc = Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_DescDadosInit);
	}

	//Verifica se só está validando os dados.
	// e chama o método de acordo com cada situação.
	if (Param_ValidarPametros)
	{
		//Está tentando validar os parametros.
		//Como está tentando validar os dados, o ponteiro de retorno da interface é NULO.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateBuffer(pBufferDesc, ObjetoValido(pSubresourceDesc) ? pSubresourceDesc : NULL, NULL);
	}
	else
	{
		//Vai realizar a função normalmente esperando o retorno do buffer.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateBuffer(pBufferDesc, ObjetoValido(pSubresourceDesc) ? pSubresourceDesc : NULL, &pBuffer);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarPametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}



	//Cria a interface a ser retornada.
	Param_Out_InterfaceBuffer = gcnew CarenD3D11Buffer();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceBuffer->AdicionarPonteiro(pBuffer);



Done:;
	//Libera a memória para as estruturas criadas anteriormente.
	DeletarEstruturaSafe(&pBufferDesc);
	//Libera a memoria para a estrutura.
	DeletarEstruturaSafe(&pSubresourceDesc);


	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateClassLinkage) - Cria bibliotecas de enlace de classe para permitir a ligação de sombreador dinâmico.
/// </summary>
/// <param name="Param_Out_ClassLinkage">Recebe a interface(ICarenD3D11ClassLinkage) de ligação de classe.</param>
CarenResult CarenD3D11Device5::CreateClassLinkage([Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkage)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11ClassLinkage* pLinkage = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateClassLinkage(&pLinkage);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Cria a interface que será retornada no parametro.
	Param_Out_ClassLinkage = gcnew CarenD3D11ClassLinkage();

	//Define o ponteiro de trabalho
	Param_Out_ClassLinkage->AdicionarPonteiro(pLinkage);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateComputeShader) - Crie um sombreador de computação.
/// </summary>
/// <param name="Param_SombreadorCompilado">Um ponteiro para um objeto que contém um sombreador compilado. Geralmente se obtém esse ponteiro através do método (ICarenD3D10Blod::ObterPonteiroBuffer).</param>
/// <param name="Param_TamanhoSombreador">O Tamanho do sombreador no paramêtro(Param_SombreadorCompilado). Se está compilado com o ICarenD3D10Blod, utilize o método (ObterTamanhoBuffer) para recuperar esse valor.</param>
/// <param name="Param_ClasseLigação">Um ponteiro para um ICarenD3D11ClassLinkage, que representa a interface de ligação de classe; o valor pode ser NULO.</param>
/// <param name="Param_ValidarParametros">Se TRUE, o método vai validar os paramêtros de entrada. Se for validado com sucesso, o método retorna SS_FALSE em vez de S_OK.</param>
/// <param name="Param_Out_ComputeShader">Recebe a interface(ICarenD3D11ComputeShader). Se (Param_ValidarPametros) for TRUE, esse parametro retorna um objeto NULO.</param>
CarenResult CarenD3D11Device5::CreateComputeShader(
	ICaren^ Param_SombreadorCompilado,
	UInt64 Param_TamanhoSombreador,
	ICarenD3D11ClassLinkage^ Param_ClasseLigação,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pSombreadorCompilado = NULL;
	ID3D11ClassLinkage* pLinkage = NULL; //Pode ser NULO.
	ID3D11ComputeShader* pComputeShader = NULL;
	SIZE_T SizeSombreador = static_cast<SIZE_T>(Param_TamanhoSombreador);

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_SombreadorCompilado->RecuperarPonteiro(&pSombreadorCompilado);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_ClasseLigação))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_ClasseLigação->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateComputeShader(pSombreadorCompilado, SizeSombreador, ObjetoValido(pLinkage) ? pLinkage : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateComputeShader(pSombreadorCompilado, SizeSombreador, ObjetoValido(pLinkage) ? pLinkage : NULL, &pComputeShader);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_ComputeShader = gcnew CarenD3D11ComputeShader();

	//Define o ponteiro de trabalho
	Param_Out_ComputeShader->AdicionarPonteiro(pComputeShader);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateCounter) - Crie um objeto de contador para medir o desempenho de GPU.
/// </summary>
/// <param name="Param_DescContador">Uma estrutura que contém a descrição do contador a ser criado.</param>
/// <param name="Param_Out_ContadorGPU">Recebe a interface que contem uma descrição do contador.</param>
CarenResult CarenD3D11Device5::CreateCounter(
	Estruturas::CA_D3D11_DESC_CONTADOR^% Param_DescContador,
	[Out] ICarenD3D11Counter^% Param_Out_ContadorGPU)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_COUNTER_DESC* pDescCounter = NULL;
	ID3D11Counter* pCounter = NULL;

	//Converte a estrutura
	pDescCounter = Util.ConverterD3D11_COUNTER_DESCManaged_ToUnManaged(Param_DescContador);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCounter(pDescCounter, &pCounter);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se não retornou S_FALSE
	if (Hr == S_FALSE)
	{
		//Verifica se retornou a interface
		if (ObjetoValido(pCounter))
		{
			//Retornou a interface 
			
			//Cria a interface a ser retornada ao usuário
			Param_Out_ContadorGPU = gcnew CarenD3D11Counter();

			//Define o ponteiro de trabalho
			Param_Out_ContadorGPU->AdicionarPonteiro(pCounter);
		}
		else
		{
			//A interface é invalida
		}
	}

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memoria para a estrutura nativa.
	if (ObjetoValido(pDescCounter))
	{
		//Libera a memoria
		DeletarEstrutura(&pDescCounter);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDeferredContext) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_FlagsContexto">Reservado. Use 0.</param>
/// <param name="Param_Out_D3D11Contexto">Recebe a interface ICarenD3D11DeviceContext.</param>
CarenResult CarenD3D11Device5::CreateDeferredContext(
	UInt32 Param_FlagsContexto,
	[Out] ICarenD3D11DeviceContext^% Param_Out_D3D11Contexto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11DeviceContext* pContexto = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeferredContext(Param_FlagsContexto, &pContexto);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada para o usuário
	Param_Out_D3D11Contexto = gcnew CarenD3D11DeviceContext();

	//Define o ponteiro de trabalho
	Param_Out_D3D11Contexto->AdicionarPonteiro(pContexto);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDepthStencilState) - Crie um objeto de estado de profundidade-estêncil que encapsula as informações de teste de profundidade-estêncil para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_DepthStencil">Uma estrutura(CA_D3D11_DEPTH_STENCIL_DESC) que descreve o estado de profundidade do Stencil.</param>
/// <param name="Param_Out_InterfaceStencil">Recebe a interface (ICarenD3D11DepthStencilState) de estado de profundidade do Stencil.</param>
CarenResult CarenD3D11Device5::CreateDepthStencilState(
	Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_DepthStencil,
	[Out] ICarenD3D11DepthStencilState^% Param_Out_InterfaceStencil)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_DEPTH_STENCIL_DESC* pDescStencil = NULL;
	ID3D11DepthStencilState* pStencilState = NULL;

	//Converte a estrutura.
	pDescStencil = Util.ConverterD3D11_DEPTH_STENCIL_DESCManaged_ToUnManaged(Param_DepthStencil);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDepthStencilState(pDescStencil, &pStencilState);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada para o usuário
	Param_Out_InterfaceStencil = gcnew CarenD3D11DepthStencilState();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceStencil->AdicionarPonteiro(pStencilState);



Done:;
	//Libera a memoria para a estrutura nativa.
	DeletarEstruturaSafe(&pDescStencil);


	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDepthStencilView) - Crie uma exibição de profundidade-estêncil para acessar dados de recurso.
/// </summary>
/// <param name="Param_Resource">Ponteiro para o recurso que irá servir como a profundidade-superfície estêncil. Este recurso deve ter sido criado com o sinalizador (D3D11_BIND_DEPTH_STENCIL).</param>
/// <param name="Param_DepthStencilView">Ponteiro para uma descrição de profundidade-estêncil-vista. Defina este parâmetro como NULL para criar uma exibição que acessa o mipmap nível 0 do recurso 
/// inteiro (usando o recurso foi criado com o formato).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_InterfaceStencilView retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_InterfaceStencilView">Recebe a interface do Depth Stencil View do D3D11.</param>
CarenResult CarenD3D11Device5::CreateDepthStencilView(
	ICarenD3D11Resource^ Param_Resource,
	Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_DepthStencilView,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11DepthStencilView^% Param_Out_InterfaceStencilView
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_DEPTH_STENCIL_VIEW_DESC* pDescStencilView = NULL;
	ID3D11DepthStencilView* pStencilView = NULL;

	//Recupera o ponteiro para o recurso
	Param_Resource->RecuperarPonteiro((PVOID*)&pRecurso);

	//Verifica se forneceu uma estrutura.
	if (ObjetoGerenciadoValido(Param_DepthStencilView))
	{
		//Converte a estrutura.
		pDescStencilView = Util.ConverterD3D11_DEPTH_STENCIL_VIEW_DESCManaged_ToUnManaged(Param_DepthStencilView);
	}

	//Verifica como vai realizar a chamada para o método
	if (Param_ValidarParametros)
	{
		//Está validando os parametros, sendo assim, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateDepthStencilView(pRecurso, pDescStencilView ? pDescStencilView : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, sendo assim, deve retornar uma interface.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateDepthStencilView(pRecurso, pDescStencilView ? pDescStencilView : NULL, &pStencilView);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface que será retornada para o usuário
	Param_Out_InterfaceStencilView = gcnew CarenD3D11DepthStencilView();

	//Define o ponteiro de trabalho
	Param_Out_InterfaceStencilView->AdicionarPonteiro(pStencilView);

Done:;
	//Libera a memoria para a estrutura nativa se ela for valida.
	DeletarEstruturaSafe(&pDescStencilView);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateDomainShader) - Crie um sombreador de domínio.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_DomainShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_DomainShader">Recebe a interface do Domain Shader.</param>
CarenResult CarenD3D11Device5::CreateDomainShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11DomainShader^% Param_Out_DomainShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pShader = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11ClassLinkage* pLinkage = NULL;
	ID3D11DomainShader* pDomainShader = NULL;

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_ShaderByteCode->RecuperarPonteiro(&pShader);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateDomainShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateDomainShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, &pDomainShader);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_DomainShader = gcnew CarenD3D11DomainShader();

	//Define o ponteiro de trabalho
	Param_Out_DomainShader->AdicionarPonteiro(pDomainShader);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateGeometryShader) - Crie um sombreador de geometria.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
CarenResult CarenD3D11Device5::CreateGeometryShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pShader = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11ClassLinkage* pLinkage = NULL;
	ID3D11GeometryShader* pInterfaceReturn = NULL;

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_ShaderByteCode->RecuperarPonteiro(&pShader);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateGeometryShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateGeometryShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, &pInterfaceReturn);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}


	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_GeometryShader = gcnew CarenD3D11GeometryShader();

	//Define o ponteiro de trabalho
	Param_Out_GeometryShader->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateGeometryShaderWithStreamOutput) - Cria um sombreador de geometria que pode gravar em streaming de buffers de saída.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_SODeclarationArray">Uma matriz de CA_D3D11_SO_DECLARATION_ENTRY. Não pode ser NULO se Param_NumeroEntradas > 0.</param>
/// <param name="Param_NumeroEntradas">O número de entradas no fluxo de saída declaração (varia de 0 a D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT).</param>
/// <param name="Param_BufferStrideArray">Uma matriz de passos de reserva; cada passo é do tamanho de um elemento para o buffer.</param>
/// <param name="Param_NumeroStrides">O número de passos (ou buffers) em Param_BufferStrideArray (varia de 0 a D3D11_SO_BUFFER_SLOT_COUNT(4)).</param>
/// <param name="Param_NumeroIndicesFluxo">O número de índice do fluxo a ser enviado para o palco do rasterizador (varia de 0 a D3D11_SO_STREAM_COUNT - 1). Conjunto para D3D11_SO_NO_RASTERIZED_STREAM se nenhum fluxo for ser rasterizada.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
CarenResult CarenD3D11Device5::CreateGeometryShaderWithStreamOutput
(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	cli::array<Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^>^ Param_SODeclarationArray,
	UInt32 Param_NumeroEntradas,
	cli::array<UInt32>^ Param_BufferStrideArray,
	UInt32 Param_NumeroStrides,
	UInt32 Param_NumeroIndicesFluxo,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPVOID pShaderByteCode = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	D3D11_SO_DECLARATION_ENTRY* pArrayEntry = NULL; //Pode ser NULO.
	UINT32* pArrayStrides = CriarMatrizEstruturas<UINT32>(Param_NumeroStrides);
	ID3D11ClassLinkage* pLinkage = NULL; //Pode ser NULO.
	ID3D11GeometryShader* pInterfaceReturn = NULL;

	//Verifica se vai criar o array de SODeclarationArray.
	if (Param_NumeroEntradas > 0)
	{
		//vai criar o array.

		//Inicializa com a quantidade de entradas especificadas.
		pArrayEntry = CriarMatrizEstruturas<D3D11_SO_DECLARATION_ENTRY>(Param_NumeroEntradas);

		//Converte as estruturas gerenciadas para a nativa.
		for (UINT32 i = 0; i < Param_NumeroEntradas; i++)
		{
			//Converte a estrutura e define no array de estruturas nativas.
			pArrayEntry[i] = *Util.ConverterD3D11_SO_DECLARATION_ENTRYManaged_ToUnManaged(Param_SODeclarationArray[i]);
		}
	}

	//Preenche os dados do array de strides
	for (UINT32 i = 0; i < Param_NumeroStrides; i++)
	{
		//Define o valor de stride no array nativo.
		pArrayStrides[i] = Param_BufferStrideArray[i];
	}

	//Verifica se forneceu uma classe de ligação
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém o ponteiro para a classe de ligação
		Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica como o método vai ser chamado
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros. Portanto, a interface de saida deve ser NULL;
		Hr = PonteiroTrabalho->CreateGeometryShaderWithStreamOutput(pShaderByteCode,
			SizeShader,
			pArrayEntry ? pArrayEntry : NULL,
			Param_NumeroEntradas,
			pArrayStrides,
			Param_NumeroStrides,
			Param_NumeroIndicesFluxo,
			pLinkage ? pLinkage : NULL,
			NULL);
	}
	else
	{
		//Não está validando os parametros. Portanto, a interface de saida deve ser valida.
		Hr = PonteiroTrabalho->CreateGeometryShaderWithStreamOutput(pShaderByteCode,
			SizeShader,
			pArrayEntry ? pArrayEntry : NULL,
			Param_NumeroEntradas,
			pArrayStrides,
			Param_NumeroStrides,
			Param_NumeroIndicesFluxo,
			pLinkage ? pLinkage : NULL,
			&pInterfaceReturn);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}


	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_GeometryShader = gcnew CarenD3D11GeometryShader();

	//Define o ponteiro de trabalho
	Param_Out_GeometryShader->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Liberação de memória.

	//Verifica se o array de matriz é valido e libera a memoria para ele.
	if (ObjetoValido(pArrayEntry))
	{
		//Libera a memoria das strings que contém em cada estrutura.
		for (UINT32 i = 0; i < Param_NumeroEntradas; i++)
		{
			//Libera a memoria para a string.
			delete pArrayEntry[i].SemanticName;
		}

		//Libera a memoria geral do array.
		DeletarMatrizEstruturasSafe(&pArrayEntry);
	}
	DeletarMatrizEstruturasSafe(&pArrayStrides);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateHullShader) - Crie um sombreador de casco.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_Out_HullShader">Recebe a interface do Hull Shader.</param>
CarenResult CarenD3D11Device5::CreateHullShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	[Out] ICarenD3D11HullShader^% Param_Out_HullShader
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pShader = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11ClassLinkage* pLinkage = NULL;
	ID3D11HullShader* pHullShader = NULL;

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_ShaderByteCode->RecuperarPonteiro(&pShader);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateHullShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, &pHullShader);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_HullShader = gcnew CarenD3D11HullShader();

	//Define o ponteiro de trabalho
	Param_Out_HullShader->AdicionarPonteiro(pHullShader);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateInputLayout) - Crie um objeto de entrada-layout para descrever os dados do buffer de entrada para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_ArrayTiposDadosEntrada">Uma matriz de tipos de dados de entrada do estágio de entrada-montador; cada tipo é descrito por uma descrição do elemento</param>
/// <param name="Param_CountElementos">O número de tipos de dados de entrada na matriz de elementos de entrada.</param>
/// <param name="Param_ShaderByteCode">Um ponteiro para o shader compilado. O código compilado de sombreador contém uma assinatura de entrada que é validada contra a matriz de elementos.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Out_InputLayout">Recebe a interface do Input Layout.</param>
CarenResult CarenD3D11Device5::CreateInputLayout(
	cli::array<Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^>^ Param_ArrayTiposDadosEntrada,
	UInt32 Param_CountElementos,
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_INPUT_ELEMENT_DESC* pArrayDesc = CriarMatrizEstruturas<D3D11_INPUT_ELEMENT_DESC>(Param_CountElementos);
	LPVOID pShaderByteCode = NULL;
	SIZE_T SizeByteCode = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11InputLayout* pInterfaceReturn = NULL;

	//Obtém o ponteiro para o Shader Compilado.
	Param_ShaderByteCode->RecuperarPonteiro(&pShaderByteCode);

	//Converte as estruturas da matriz gerenciada para a nativa.
	for (UINT32 i = 0; i < Param_CountElementos; i++)
	{
		//Converte e define a estrutura no array nativo.
		pArrayDesc[i] = *Util.ConverterD3D11_INPUT_ELEMENT_DESCManaged_ToUnManaged(Param_ArrayTiposDadosEntrada[i]);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInputLayout(pArrayDesc, Param_CountElementos, pShaderByteCode, SizeByteCode, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada ao usuário.
	Param_Out_InputLayout = gcnew CarenD3D11InputLayout();

	//Define o ponteiro de trabalho
	Param_Out_InputLayout->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Verifica se o array de matriz é valido e libera a memoria para ele.
	if (ObjetoValido(pArrayDesc))
	{
		//Libera a memoria das strings que contém em cada estrutura.
		for (UINT32 i = 0; i < Param_CountElementos; i++)
		{
			//Libera a memoria para a string.
			delete pArrayDesc[i].SemanticName;
		}

		//Libera a memoria geral do array.
		DeletarMatrizEstruturasSafe(&pArrayDesc);
	}


	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreatePixelShader) - Crie um sombreador de pixel.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_PixelShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_PixelShader">Recebe a interface do Hull Shader.</param>
CarenResult CarenD3D11Device5::CreatePixelShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11PixelShader^% Param_Out_PixelShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pShader = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11ClassLinkage* pLinkage = NULL;
	ID3D11PixelShader* pPixelShader = NULL;

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_ShaderByteCode->RecuperarPonteiro(&pShader);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreatePixelShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreatePixelShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, &pPixelShader);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}




	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_PixelShader = gcnew CarenD3D11PixelShader();

	//Define o ponteiro de trabalho
	Param_Out_PixelShader->AdicionarPonteiro(pPixelShader);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreatePredicate) - Cria um predicado.
/// </summary>
/// <param name="Param_DescPredicado">Ponteiro para uma descrição de consulta onde o tipo de consulta deve ser uma D3D11_QUERY_SO_OVERFLOW_PREDICATE ou D3D11_QUERY_OCCLUSION_PREDICATE</param>
/// <param name="Param_Out_Predicado">Recebe a interface do Predicado criado.</param>
CarenResult CarenD3D11Device5::CriarPredicado(
	Estruturas::CA_D3D11_QUERY_DESC^% Param_DescPredicado,
	[Out] ICarenD3D11Predicate^% Param_Out_Predicado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_QUERY_DESC* pDesc = NULL;
	ID3D11Predicate* pInterfaceReturn = NULL;

	//Converte a estrutura.
	pDesc = Util.ConverterD3D11_QUERY_DESCManaged_ToUnManaged(Param_DescPredicado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePredicate(pDesc, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada
	Param_Out_Predicado = gcnew CarenD3D11Predicate();

	//Define o ponteiro de trabalho
	Param_Out_Predicado->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Deleta a memoria para a estrutura se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateQuery) - Essa interface encapsula métodos para consultar informações da GPU.
/// </summary>
/// <param name="Param_DescQuery">Uma descrição da interface de consulta a ser criada.</param>
/// <param name="Param_Out_Query">Recebe a interface de consulta criada.</param>
CarenResult CarenD3D11Device5::CreateQuery(
	Estruturas::CA_D3D11_QUERY_DESC^% Param_DescQuery,
	[Out] ICarenD3D11Query^% Param_Out_Query)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_QUERY_DESC* pDesc = NULL;
	ID3D11Query* pInterfaceReturn = NULL;

	//Converte a estrutura.
	pDesc = Util.ConverterD3D11_QUERY_DESCManaged_ToUnManaged(Param_DescQuery);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQuery(pDesc, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada
	Param_Out_Query = gcnew CarenD3D11Query();

	//Define o ponteiro de trabalho
	Param_Out_Query->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Deleta a memoria para a estrutura se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateRasterizerState) - Crie um objeto de estado rasterizador que informa o rasterizador de palco como se comportar.
/// </summary>
/// <param name="Param_DescRasterizador">Uma estrutura com a descrição do estado do rasterizador.</param>
/// <param name="Param_Out_Rasterizador">Recebe a interface de Rasterização criada.</param>
CarenResult CarenD3D11Device5::CreateRasterizerState(
	Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_DescRasterizador,
	[Out] ICarenD3D11RasterizerState^% Param_Out_Rasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC* pDesc = NULL;
	ID3D11RasterizerState* pInterfaceReturn = NULL;

	//Converte a estrutura.
	pDesc = Util.ConverterD3D11_RASTERIZER_DESCManaged_ToUnManaged(Param_DescRasterizador);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRasterizerState(pDesc, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada
	Param_Out_Rasterizador = gcnew CarenD3D11RasterizerState();

	//Define o ponteiro de trabalho
	Param_Out_Rasterizador->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Deleta a memoria para a estrutua se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateRenderTargetView) - Cria uma exibição de destino de processamento para acesso a dados de recurso.
/// </summary>
/// <param name="Param_Resource">Um ponteiro para interface ID3D11Resource que representa um destino de processamento. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_RENDER_TARGET .</param>
/// <param name="Param_DescRender">Uma estrutura D3D11_RENDER_TARGET_VIEW_DESC que representa uma descrição do modo de exibição render-alvo. Defina este parâmetro como NULL para criar uma exibição 
/// que acessa todos os sub-recursos mipmap nível 0.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ViewRender retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_ViewRender">Recebe a interface do visualizador de render.</param>
CarenResult CarenD3D11Device5::CreateRenderTargetView(
	ICarenD3D11Resource^ Param_Resource,
	Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11RenderTargetView^% Param_Out_ViewRender)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_RENDER_TARGET_VIEW_DESC* pDesc = NULL;
	ID3D11RenderTargetView* pInterfaceReturn = NULL;

	//Obtém a interface de recurso
	Resultado = Param_Resource->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha.

		//Sai do método
		Sair;
	}

	//Verifica se forneceu uma estrutura.
	if (ObjetoGerenciadoValido(Param_DescRender))
	{
		//Converte a estrutura.
		pDesc = Util.ConverterD3D11_RENDER_TARGET_VIEW_DESCManaged_ToUnManaged(Param_DescRender);
	}

	//Verifica como vai ser chamado a função do método.
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros.
		//Sendo assm, uma interface não será retornada e deve ser definida como NULL.
		Hr = PonteiroTrabalho->CreateRenderTargetView(pRecurso, pDesc ? pDesc : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros.
		//Sendo assim, deve esperar que uma interface seja retornada.
		Hr = PonteiroTrabalho->CreateRenderTargetView(pRecurso, pDesc ? pDesc : NULL, &pInterfaceReturn);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}


	//Cria a interface que vai ser retornada
	Param_Out_ViewRender = gcnew CarenD3D11RenderTargetView();

	//Chama o método para definir o ponteiro de trabalho
	Param_Out_ViewRender->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Deleta a memoria para a estrutua se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateSamplerState) - Crie um objeto de sampler-estado que encapsula as informações de amostragem para uma textura.
/// </summary>
/// <param name="Param_DescSampler">Uma descrição do estado do amostrador</param>
/// <param name="Param_Out_SamplerState">Recebe a interface do Sampler Sate.</param>
CarenResult CarenD3D11Device5::CreateSamplerState(
	Estruturas::CA_D3D11_SAMPLER_DESC^% Param_DescSampler,
	[Out] ICarenD3D11SamplerState^% Param_Out_SamplerState)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_SAMPLER_DESC* pDesc;
	ID3D11SamplerState* pInterfaceReturn = NULL;

	//Converte a estrutura
	pDesc = Util.ConverterD3D11_SAMPLER_DESCManaged_ToUnManaged(Param_DescSampler);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSamplerState(pDesc, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada
	Param_Out_SamplerState = gcnew CarenD3D11SamplerState();

	//Define o ponteiro de trabalho
	Param_Out_SamplerState->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Deleta a memoria para a estrutura se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateShaderResourceView) - Crie uma exibição de sombreador-recurso para acessar dados em um recurso.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para o recurso que irá servir como entrada para um sombreador. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_SHADER_RESOURCE .</param>
/// <param name="Param_DescExbi">Ponteiro para uma descrição de exibição de sombreador-recurso (veja D3D11_SHADER_RESOURCE_VIEW_DESC). Defina este parâmetro como NULL para criar uma 
/// exibição que acessa o recurso inteiro (usando o recurso foi criado com o formato).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ShaderView retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_ShaderView">Recebe a interface para o visualizador de Shader.</param>
CarenResult CarenD3D11Device5::CreateShaderResourceView(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_DescExbi,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11ShaderResourceView^% Param_Out_ShaderView)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc = NULL;
	ID3D11ShaderResourceView* pInterfaceReturn = NULL;

	//Obtém a interface de recurso
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha.

		//Sai do método
		Sair;
	}

	//Verifica se forneceu uma estrutura.
	if (ObjetoGerenciadoValido(Param_DescExbi))
	{
		//Converte a estrutura.
		pDesc = Util.ConverterD3D11_SHADER_RESOURCE_VIEW_DESCManaged_ToUnManaged(Param_DescExbi);
	}

	//Verifica como vai ser chamado a função do método.
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros.
		//Sendo assm, uma interface não será retornada e deve ser definida como NULL.
		Hr = PonteiroTrabalho->CreateShaderResourceView(pRecurso, pDesc ? pDesc : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros.
		//Sendo assim, deve esperar que uma interface seja retornada.
		Hr = PonteiroTrabalho->CreateShaderResourceView(pRecurso, pDesc ? pDesc : NULL, &pInterfaceReturn);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}


	//Cria a interface que vai ser retornada
	Param_Out_ShaderView = gcnew CarenD3D11ShaderResourceView();

	//Chama o método para definir o ponteiro de trabalho
	Param_Out_ShaderView->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Deleta a memoria para a estrutura se ela for valida
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateTexture1D) - Cria uma matriz de texturas 1D.
/// </summary>
/// <param name="Param_DescTextura1D">Uma estrutura CA_D3D11_TEXTURE1D_DESC que descreve um recurso de textura 1D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 1D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura1D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura1D">Recebe a interface que contém o buffer da interface de Textura 1D.</param>
CarenResult CarenD3D11Device5::CreateTexture1D(
	Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_DescTextura1D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture1D^% Param_Out_Textura1D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_TEXTURE1D_DESC* pDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pArraySubresourceData = NULL;
	ID3D11Texture1D* pInterfaceReturn = NULL;

	//Converte a estrutura de descrição da textura
	pDesc = Util.ConverterD3D11_TEXTURE1D_DESCManaged_ToUnManaged(Param_DescTextura1D);

	//Verfica se foi fornecido um array com os dados de subrecursos
	if (ObjetoGerenciadoValido(Param_ArrayDescSubRecursos))
	{
		//Cria um array com a quantidade informada.
		pArraySubresourceData = CriarMatrizEstruturas<D3D11_SUBRESOURCE_DATA>(Param_TamanhoArraySubRecursos);

		//Faz um for para converter todas as estruturas.
		for (UINT32 i = 0; i < Param_TamanhoArraySubRecursos; i++)
		{
			//Converte a estrutura e define no array nativo.
			pArraySubresourceData[i] = *Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_ArrayDescSubRecursos[i]);
		}
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture1D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture1D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, &pInterfaceReturn);
	}


	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		Sair;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_Textura1D = gcnew CarenD3D11Texture1D();

	//Define o ponteiro de trabalho
	Param_Out_Textura1D->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Deleta as esturturas se elas forem validas
	DeletarEstruturaSafe(&pDesc);
	DeletarMatrizEstruturasSafe(&pArraySubresourceData);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateTexture2D) - Crie uma matriz de texturas 2D.
/// </summary>
/// <param name="Param_DescTextura2D">Uma estrutura CA_D3D11_TEXTURE2D_DESC que descreve um recurso de textura 2D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 2D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura2D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura2D">Recebe a interface que contém o buffer da interface de Textura 2D.</param>
CarenResult CarenD3D11Device5::CreateTexture2D(
	Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_DescTextura2D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture2D^% Param_Out_Textura2D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_TEXTURE2D_DESC* pDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pArraySubresourceData = NULL;
	ID3D11Texture2D* pInterfaceReturn = NULL;

	//Converte a estrutura de descrição da textura
	pDesc = Util.ConverterD3D11_TEXTURE2D_DESCManaged_ToUnManaged(Param_DescTextura2D);

	//Verfica se foi fornecido um array com os dados de subrecursos
	if (ObjetoGerenciadoValido(Param_ArrayDescSubRecursos))
	{
		//Cria um array com a quantidade informada.
		pArraySubresourceData = CriarMatrizEstruturas<D3D11_SUBRESOURCE_DATA>(Param_TamanhoArraySubRecursos);

		//Faz um for para converter todas as estruturas.
		for (UINT32 i = 0; i < Param_TamanhoArraySubRecursos; i++)
		{
			//Converte a estrutura e define no array nativo.
			pArraySubresourceData[i] = *Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_ArrayDescSubRecursos[i]);
		}
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture2D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture2D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, &pInterfaceReturn);
	}


	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		Sair;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_Textura2D = gcnew CarenD3D11Texture2D();

	//Define o ponteiro de trabalho
	Param_Out_Textura2D->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Deleta as esturturas se elas forem validas
	DeletarEstruturaSafe(&pDesc);
	DeletarMatrizEstruturasSafe(&pArraySubresourceData);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateTexture3D) - Crie uma única textura 3D.
/// </summary>
/// <param name="Param_DescTextura3D">Uma estrutura CA_D3D11_TEXTURE3D_DESC que descreve um recurso de textura 3D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 3D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura3D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura3D">Recebe a interface que contém o buffer da interface de Textura 3D.</param>
CarenResult CarenD3D11Device5::CreateTexture3D(
	Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_DescTextura3D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture3D^% Param_Out_Textura3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_TEXTURE3D_DESC* pDesc = NULL;
	D3D11_SUBRESOURCE_DATA* pArraySubresourceData = NULL;
	ID3D11Texture3D* pInterfaceReturn = NULL;

	//Converte a estrutura de descrição da textura
	pDesc = Util.ConverterD3D11_TEXTURE3D_DESCManaged_ToUnManaged(Param_DescTextura3D);

	//Verfica se foi fornecido um array com os dados de subrecursos
	if (ObjetoGerenciadoValido(Param_ArrayDescSubRecursos))
	{
		//Cria um array com a quantidade informada.
		pArraySubresourceData = CriarMatrizEstruturas<D3D11_SUBRESOURCE_DATA>(Param_TamanhoArraySubRecursos);

		//Faz um for para converter todas as estruturas.
		for (UINT32 i = 0; i < Param_TamanhoArraySubRecursos; i++)
		{
			//Converte a estrutura e define no array nativo.
			pArraySubresourceData[i] = *Util.ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(Param_ArrayDescSubRecursos[i]);
		}
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture3D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateTexture3D(pDesc, pArraySubresourceData ? pArraySubresourceData : NULL, &pInterfaceReturn);
	}


	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		Sair;
	}



	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_Textura3D = gcnew CarenD3D11Texture3D();

	//Define o ponteiro de trabalho
	Param_Out_Textura3D->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Deleta as esturturas se elas forem validas
	DeletarEstruturaSafe(&pDesc);
	DeletarMatrizEstruturasSafe(&pArraySubresourceData);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateUnorderedAccessView) - Cria uma visão para acessar um recurso de acesso não ordenada.
/// </summary>
/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
/// <param name="Param_Out_Interface">Recebe a interface do Recurso de acesso não ordenado.</param>
CarenResult CarenD3D11Device5::CreateUnorderedAccessView(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_DescSombreador,
	[Out] ICarenD3D11UnorderedAccessView^% Param_Out_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID3D11Resource* pRecurso = NULL;
	D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc = NULL;
	ID3D11UnorderedAccessView* pInterfaceReturn = NULL;

	//Obtém a interface de recurso
	Resultado = Param_Recurso->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha.

		//Sai do método
		Sair;
	}

	//Verifica se forneceu uma estrutura
	if (ObjetoGerenciadoValido(Param_DescSombreador))
	{
		//Converte a estrutura.
		pDesc = Util.ConverterD3D11_UNORDERED_ACCESS_VIEW_DESCManaged_ToUnManaged(Param_DescSombreador);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateUnorderedAccessView(pRecurso, pDesc ? pDesc : NULL, &pInterfaceReturn);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada no parametro.
	Param_Out_Interface = gcnew CarenD3D11UnorderedAccessView();

	//Define o ponteiro de trabalho
	Param_Out_Interface->AdicionarPonteiro(pInterfaceReturn);



Done:;
	//Libera a memoria para a estrutura
	DeletarEstruturaSafe(&pDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateVertexShader) - Crie um objeto shader de vértice de um sombreador compilado.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_VertexShaderInterface retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_VertexShader">Recebe a interface do Vertex Shader.</param>
CarenResult CarenD3D11Device5::CreateVertexShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11VertexShader^% Param_Out_VertexShader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PVOID pShader = NULL;
	SIZE_T SizeShader = static_cast<SIZE_T>(Param_TamanhoByteCode);
	ID3D11ClassLinkage* pLinkage = NULL;
	ID3D11VertexShader* pVertexShader = NULL;

	//Obtém o ponteiro para o sombreador compilado.
	Resultado = Param_ShaderByteCode->RecuperarPonteiro(&pShader);

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Veririfica se forneceu o Class Linkage
	if (ObjetoGerenciadoValido(Param_Linkage))
	{
		//Obtém um ponteiro para a interface.
		Resultado = Param_Linkage->RecuperarPonteiro((LPVOID*)&pLinkage);
	}

	//Verifica se obteve com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o sombreador é invalido

		//Sai do método
		goto Done;
	}

	//Verifica se só vai validar os parametros
	//E chama a função corretamente para cada ocasião
	if (Param_ValidarParametros)
	{
		//Só está validando os parametros, portanto, a interface de retorno é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateVertexShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, NULL);
	}
	else
	{
		//Não está validando os parametros, portanto, a interface de retorno não é NULA.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->CreateVertexShader(pShader, SizeShader, ObjetoValido(pLinkage) ? pLinkage : NULL, &pVertexShader);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Verifica se só estava validando os parametros
	//Se sim, define SS_FALSE e pula para Done.
	if (Param_ValidarParametros)
	{
		//Define SS_FALSE como é necessário e não retorna nada para o usuario.

		//Define SS_FALSE.
		Resultado.AdicionarCodigo(ResultCode::SS_FALSE, false);

		//Sai do método
		goto Done;
	}




	//Cria a interface do parametro que vai ser retornada ao usuário
	Param_Out_VertexShader = gcnew CarenD3D11VertexShader();

	//Define o ponteiro de trabalho
	Param_Out_VertexShader->AdicionarPonteiro(pVertexShader);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCreationFlags) - Se os sinalizadores usados durante a chamada para criar o dispositivo com D3D11CreateDevice.
/// </summary>
/// <param name="Param_Out_Flags">Recebe um flags de bit a bits da enumerção (CA_D3D11_CREATE_DEVICE_FLAG) que contém o modo de criaçã do dispositivo.</param>
CarenResult CarenD3D11Device5::GetCreationFlags([Out] Enumeracoes::CA_D3D11_CREATE_DEVICE_FLAG% Param_Out_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_Out_Flags = static_cast<Enumeracoes::CA_D3D11_CREATE_DEVICE_FLAG>(PonteiroTrabalho->GetCreationFlags());

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDeviceRemovedReason) - A razão por que o dispositivo foi removido. Esse método retorna um (ResultCode) informando o motivo.
/// </summary>
CarenResult CarenD3D11Device5::GetDeviceRemovedReason()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceRemovedReason();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetExceptionMode) - Obter os sinalizadores de modo de exceção.
/// </summary>
/// <param name="Param_Out_Except">Um valor que contém um ou mais sinalizadores de exceção; Cada sinalizador especifica uma condição que fará com que uma exceção seja levantada. Os sinalizadores estão 
/// listados em D3D11_RAISE_FLAG. Um valor padrão de 0 significa que não há sinalizadores.</param>
CarenResult CarenD3D11Device5::GetExceptionMode([Out] Enumeracoes::CA_D3D11_RAISE_FLAG% Param_Out_Except)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_Out_Except = static_cast<Enumeracoes::CA_D3D11_RAISE_FLAG>(PonteiroTrabalho->GetExceptionMode());

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetFeatureLevel) - Obtém o nível de funcionalidade de dispositivo de hardware.
/// </summary>
/// <param name="Param_Out_NivelRecurso">Recebe um flag de bits a bits de um ou mais sinlizadores de niveis de recuso do dispositivo de hardware.</param>
CarenResult CarenD3D11Device5::GetFeatureLevel([Out] Enumeracoes::CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	D3D_FEATURE_LEVEL NivelRecursoHardware;

	//Chama o método para realizar a operação.
	NivelRecursoHardware = PonteiroTrabalho->GetFeatureLevel();

	//Define o nivel de recurso no parametro de saida
	Param_Out_NivelRecurso = static_cast<Enumeracoes::CA_D3D_FEATURE_LEVEL>(NivelRecursoHardware);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetImmediateContext) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_ImediateContextInterface">Recebe a interface do contexto do dispositivo.</param>
CarenResult CarenD3D11Device5::GetImmediateContext([Out] ICarenD3D11DeviceContext^% Param_Out_ImediateContextInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	ID3D11DeviceContext* pContexto = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetImmediateContext(&pContexto);

	//Verifica se a operação obteve sucesso.
	if (ObjetoValido(pContexto))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falha
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada no parametro.
	Param_Out_ImediateContextInterface = gcnew CarenD3D11DeviceContext();

	//Define o ponteiro de trabalho
	Param_Out_ImediateContextInterface->AdicionarPonteiro(pContexto);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetPrivateData) - Obtém dados application-defined de um dispositivo.
/// </summary>
/// <param name="Param_Guid">O Guid associado ao buffer.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer de saida.</param>
/// <param name="Param_Out_TamanhoBufferSaida">Recebe o tamanho que total do buffer no parametro (Param_Out_Buffer).</param>
/// <param name="Param_Out_Buffer">Recebe a interface que gerencia o buffer retornado.</param>
CarenResult CarenD3D11Device5::GetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidBuffer = GUID_NULL;
	UINT TamanhoBuffer = Param_TamanhoBuffer; //Define o tamanho do buffer que será retornado em (Param_Out_Buffer).
	PBYTE pData = NULL;

	//Cria o guid associado a interface.
	GuidBuffer = Util.CreateGuidFromString(Param_Guid);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPrivateData(GuidBuffer, &TamanhoBuffer, &pData);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o ponteiro de dados.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Define o ponteiro de dados na interface de buffer.
	Param_Out_Buffer->CreateBuffer(IntPtr(pData), false, TamanhoBuffer, TamanhoBuffer);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OpenSharedResource) - Dar um dispositivo de acesso a um recurso compartilhado, criado em um dispositivo diferente.
/// </summary>
/// <param name="Param_Handle">Um identificador de recurso.</param>
/// <param name="Param_GuidInterface">O identificador globalmente exclusivo (GUID) para a interface do recurso.</param>
/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface do recurso que foi ganhado acesso. O usuário deve criar a interfaces antes de chamar este método.</param>
CarenResult CarenD3D11Device5::OpenSharedResource(
	IntPtr Param_Handle,
	String^ Param_GuidInterface,
	ICaren^ Param_Out_InterfaceSolicitada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandle = NULL;
	GUID GuidInterface = GUID_NULL;
	LPVOID pInterface = NULL;

	//Obtém a handle
	pHandle = Util.ConverterIntPtrToHWND(Param_Handle);

	//Cria o guid associado a interface.
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenSharedResource(pHandle, GuidInterface, &pInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro de trabalho
	Param_Out_InterfaceSolicitada->AdicionarPonteiro(pInterface);



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetExceptionMode) - Obter os sinalizadores de modo de exceção.
/// </summary>
/// <param name="Param_RaiseFlags">Os flags de modo de exceção.</param>
CarenResult CarenD3D11Device5::SetExceptionMode(UInt32 Param_RaiseFlags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetExceptionMode(Param_RaiseFlags);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateData) - Define os dados para um dispositivo e associa esses dados a um guid.
/// </summary>
/// <param name="Param_Guid">O Guid associado ao buffer.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer de entrada.</param>
/// <param name="Param_Buffer">Ponteiro para os dados sejam armazenados com este dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer dados anteriormente associados com o 
/// guid serão destruídos.</param>
CarenResult CarenD3D11Device5::SetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer, 
	ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidBuffer = GUID_NULL;
	PBYTE pData = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;

	//Cria o guid associado a interface.
	GuidBuffer = Util.CreateGuidFromString(Param_Guid);

	//Obtém o ponteiro para os dados.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se é valido
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pData = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateData(GuidBuffer, Param_TamanhoBuffer, pData);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}



Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateDataInterface) - Associar uma interface IUnknown-derivado desta criança de dispositivo e associar essa interface com um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">O Guid associado a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface derivada de IUnknown para ser associado ao filho do dispositivo.</param>
CarenResult CarenD3D11Device5::SetPrivateDataInterface(
	String^ Param_Guid,
	ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Cria o guid associado a interface.
	GuidInterface = Util.CreateGuidFromString(Param_Guid);

	//Obtém a interface 
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)&pInterface);

	//Verifica se não falhou
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método.
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}



Done:;
	//Retorna o resultado.
	return Resultado;
}