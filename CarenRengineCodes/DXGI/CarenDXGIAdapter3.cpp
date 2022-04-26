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
#include "CarenDXGIAdapter3.h"

//Destruidor.
CarenDXGIAdapter3::~CarenDXGIAdapter3()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenDXGIAdapter3::CarenDXGIAdapter3()
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
CarenResult CarenDXGIAdapter3::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIAdapter3::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIAdapter3*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenDXGIAdapter3::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIAdapter3*>(Param_PonteiroNativo);

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
CarenResult CarenDXGIAdapter3::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIAdapter3::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIAdapter3::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenDXGIAdapter3::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIAdapter3::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIAdapter3::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<IDXGIAdapter3*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIAdapter3::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<IDXGIAdapter3*>(PonteiroTrabalho))->Release();

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
void CarenDXGIAdapter3::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIAdapter3();
}


//
// Métodos da interface proprietária(ICarenDXGIAdapter3)
//

/// <summary>
/// (QueryVideoMemoryInfo) - Este método informa o processo de uso do orçamento e do processo atual.
/// </summary>
/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações da memória de vídeo são consultadas. Para operação de GPU única, coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de vídeo são consultadas.</param>
/// <param name="Param_GrupoSegmento">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
/// <param name="Param_Out_InfoMemoria">Recebe uma estrutura CA_DXGI_QUERY_VIDEO_MEMORY_INFO com os valores atuais.</param>
CarenResult CarenDXGIAdapter3::QueryVideoMemoryInfo(
				UInt32 Param_NodeId, 
				CA_DXGI_MEMORY_SEGMENT_GROUP Param_GrupoSegmento, 
				[Out] CA_DXGI_QUERY_VIDEO_MEMORY_INFO^% Param_Out_InfoMemoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_QUERY_VIDEO_MEMORY_INFO DxgiMemInfo = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueryVideoMemoryInfo(Param_NodeId, static_cast<DXGI_MEMORY_SEGMENT_GROUP>(Param_GrupoSegmento), &DxgiMemInfo);

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

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_InfoMemoria = Util.ConverterDXGI_QUERY_VIDEO_MEMORY_INFOUnManaged_ToManaged(&DxgiMemInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterHardwareContentProtectionTeardownStatusEvent) - Se registra para receber notificação de eventos de proteção de proteção de conteúdo de hardware.
/// </summary>
/// <param name="Param_Evento">Uma Handle para o objeto de evento que o sistema operacional define quando ocorre o (TearDown) de proteção de conteúdo de hardware. </param>
/// <param name="Param_Out_Cookie">um valor-chave que um aplicativo pode passar para o método ICarenDXGIAdapter3:::UnregisterHardwareContentProtectionTeardownStatus para 
/// descadastrar o evento de notificação que o Param_Evento especifica.</param>
CarenResult CarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent(ICarenEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera um ponteiro para o evento
	Resultado = Param_Evento->RecuperarEvento(&pHandEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterHardwareContentProtectionTeardownStatusEvent(pHandEvento, &OutCookie);

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

	//Converte o Cookie e define no parametro de saida.
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterVideoMemoryBudgetChangeNotificationEvent) - Este método estabelece uma correlação entre um objeto de sincronização da CPU e o evento de mudança orçamentária.
/// </summary>
/// <param name="Param_Evento">Uma Handle para o objeto de evento.</param>
/// <param name="Param_Out_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent
/// retorna esse valor.</param>
CarenResult CarenDXGIAdapter3::RegisterVideoMemoryBudgetChangeNotificationEvent(ICarenEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera um ponteiro para o evento
	Resultado = Param_Evento->RecuperarEvento(&pHandEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterVideoMemoryBudgetChangeNotificationEvent(pHandEvento, &OutCookie);

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

	//Converte o Cookie e define no parametro de saida.
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetVideoMemoryReservation) - Este método envia a memória física mínima necessária para uma aplicação, para o Sistema Operacional.
/// </summary>
/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações de memória de vídeo estão sendo definidas. Para operação de GPU única, 
/// coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de 
/// vídeo estão sendo definidas.</param>
/// <param name="Param_SegmentoGrupoMemoria">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
/// <param name="Param_ReversaMemoria">Especifica um UInt64 que define a memória física mínima necessária, em bytes.</param>
CarenResult CarenDXGIAdapter3::SetVideoMemoryReservation(
				UInt32 Param_NodeId, 
				CA_DXGI_MEMORY_SEGMENT_GROUP Param_SegmentoGrupoMemoria, 
				UInt64 Param_ReversaMemoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetVideoMemoryReservation(Param_NodeId, static_cast<DXGI_MEMORY_SEGMENT_GROUP>(Param_SegmentoGrupoMemoria), Param_ReversaMemoria);

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
/// (UnregisterHardwareContentProtectionTeardownStatus) - O Desregistra(Cancelar) um evento para impedi-lo de receber a notificação de eventos de proteção de 
/// conteúdo de hardware.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
/// retorna esse valor.</param>
CarenResult CarenDXGIAdapter3::UnregisterHardwareContentProtectionTeardownStatus(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UnregisterHardwareContentProtectionTeardownStatus(static_cast<DWORD>(Param_Cookie));

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterVideoMemoryBudgetChangeNotification) - Este método deixa de notificar um objeto de sincronização da CPU sempre que ocorre uma mudança orçamentária. Um aplicativo pode mudar para a votação regular das informações.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
/// retorna esse valor.</param>
CarenResult CarenDXGIAdapter3::UnregisterVideoMemoryBudgetChangeNotification(UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->UnregisterVideoMemoryBudgetChangeNotification(static_cast<DWORD>(Param_Cookie));

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}




//
// Métodos da interface ICarenDXGIAdapter2
//

/// <summary>
/// (GetDesc2) - Obtém uma descrição 1.2 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. 
/// Esta descrição inclui informações sobre a granularidade em que a unidade de processamento gráfico (GPU) pode ser impedida de realizar 
/// sua tarefa atual.
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC2 que descreve o adaptador. Este parâmetro não deve ser 
/// NULO.No hardware gráfico nível 9, versões anteriores do GetDesc2(GetDesc e GetDesc1) retorna zero para o 
/// PCI ID em e (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do adaptador e "Adaptador de Software" para a descrição 
/// do membro (Description). O GetDesc2 retorna os valores reais de hardware nível 9 nesses membros.</param>
CarenResult CarenDXGIAdapter3::GetDesc2([Out] CA_DXGI_ADAPTER_DESC2^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC2 AdapterDesc2 = { 0 };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc2(&AdapterDesc2);

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

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESC2UnManaged_ToManaged(&AdapterDesc2);

Done:;
	//Retorna o resultado.
	return Resultado;
}




//
// Métodos da interface ICarenDXGIAdapter1
//

/// <summary>
/// (GetDesc1) - Obtém uma descrição DXGI 1.1 de um adaptador (ou cartão de vídeo).
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC1 que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc1) retorna zeros para o 
/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC1 e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
CarenResult CarenDXGIAdapter3::GetDesc1([Out] CA_DXGI_ADAPTER_DESC1^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC1 DescAdaptador;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc1(&DescAdaptador);

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

	//Converte a esturutra e define no parametro de saida
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESC1UnManaged_ToManaged(&DescAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIAdapter
//

/// <summary>
/// (CheckInterfaceSupport) - Verifica se o sistema suporta uma interface do dispositivo para um componente gráfico.
/// </summary>
/// <param name="Param_GuidInterface">O GUID da interface da versão do dispositivo para a qual o suporte está sendo verificado.</param>
/// <param name="Param_Out_UMDVersion">A versão do motorista do modo de usuário do (Param_GuidInterface). Isso só é devolvido se a interface for suportada, caso contrário, este parâmetro será -12354.</param>
CarenResult CarenDXGIAdapter3::CheckInterfaceSupport(String^ Param_GuidInterface, [Out] Int64% Param_Out_UMDVersion)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	LARGE_INTEGER LargeDados = { 0 };

	//Cria o guid
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CheckInterfaceSupport(GuidInterface, &LargeDados);

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

	//Deifine os dados no parametro de saida.
	Param_Out_UMDVersion = LargeDados.QuadPart;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (EnumOutputs) - Saídas de adaptador enumerado (cartão de vídeo).
/// </summary>
/// <param name="Param_IndexSaida">O índice da saída.</param>
/// <param name="Param_Out_Saida">O endereço de um ponteiro para uma interface ICarenDXGIOutput na posição especificada pelo parâmetro (Param_IndexSaida).</param>
CarenResult CarenDXGIAdapter3::EnumOutputs(UInt32 Param_IndexSaida, [Out] ICarenDXGIOutput^% Param_Out_Saida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIOutput* pSaida = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumOutputs(Param_IndexSaida, &pSaida);

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
	Param_Out_Saida = gcnew CarenDXGIOutput();

	//Define o ponteiro de trabalho
	Param_Out_Saida->AdicionarPonteiro(pSaida);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Obtém uma descrição DXGI 1.0 de um adaptador (ou cartão de vídeo).
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc) retorna zeros para o 
/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
CarenResult CarenDXGIAdapter3::GetDesc([Out] CA_DXGI_ADAPTER_DESC^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC DescAdaptador;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc(&DescAdaptador);

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

	//Converte a esturutra e define no parametro de saida
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESCUnManaged_ToManaged(&DescAdaptador);

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
CarenResult CarenDXGIAdapter3::GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai)
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenDXGIAdapter3::SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados)
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
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIAdapter3::GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados)
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenDXGIAdapter3::SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface)
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}