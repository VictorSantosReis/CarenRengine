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
#include "CarenMFQualityManager.h"



//Destruidor.
CarenMFQualityManager::~CarenMFQualityManager()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFQualityManager::CarenMFQualityManager(CA_MF_QUALITY_MANAGER_CREATE_TYPE Param_CreateType)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFQualityManager* vi_pOutQualityManagerDefault = Nulo;

	//Abre um switch para verificar e criar da forma solicitada a classe.
	switch (Param_CreateType)
	{
	case CarenRengine::SDKBase::Enumeracoes::CA_MF_QUALITY_MANAGER_CREATE_TYPE::MF_NULL:
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
		break;
	case CarenRengine::SDKBase::Enumeracoes::CA_MF_QUALITY_MANAGER_CREATE_TYPE::MF_CREATE_TYPE_STANDARD:
		//Chama o método para criar a interface.
		Hr = MFCreateStandardQualityManager(&vi_pOutQualityManagerDefault);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutQualityManagerDefault;
		break;
	case CarenRengine::SDKBase::Enumeracoes::CA_MF_QUALITY_MANAGER_CREATE_TYPE::MF_CREATE_TYPE_INTERNAL:
		//Cria uma implementação interna.
		PonteiroTrabalho = new CLN_IMFQualityManager(); 
		break;
	default:
		throw gcnew Exception("Um valor desconhecido ou um erro interno impediram a criação da classe.");
		break;
	}
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFQualityManager::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFQualityManager::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFQualityManager*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFQualityManager::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFQualityManager*>(Param_PonteiroNativo);

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
CarenResult CarenMFQualityManager::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenMFQualityManager::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
CarenResult CarenMFQualityManager::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFQualityManager::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFQualityManager::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFQualityManager::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFQualityManager::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

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
void CarenMFQualityManager::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFQualityManager();
}



// Métodos da interface proprietária(ICarenMFQualityManager)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFQualityManager::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnNotifyPresentationClock = gcnew DelegateNativo_Evento_OnNotifyPresentationClock(this, &CarenMFQualityManager::EncaminharEvento_OnNotifyPresentationClock);
	Callback_OnNotifyTopology = gcnew DelegateNativo_Evento_OnNotifyTopology(this, &CarenMFQualityManager::EncaminharEvento_OnNotifyTopology);
	Callback_OnNotifyProcessInput = gcnew DelegateNativo_Evento_OnNotifyProcessInput(this, &CarenMFQualityManager::EncaminharEvento_OnNotifyProcessInput);
	Callback_OnNotifyProcessOutput = gcnew DelegateNativo_Evento_OnNotifyProcessOutput(this, &CarenMFQualityManager::EncaminharEvento_OnNotifyProcessOutput);
	Callback_OnNotifyQualityEvent = gcnew DelegateNativo_Evento_OnNotifyQualityEvent(this, &CarenMFQualityManager::EncaminharEvento_OnNotifyQualityEvent);
	Callback_OnShutdown = gcnew DelegateNativo_Evento_OnShutdown(this, &CarenMFQualityManager::EncaminharEvento_OnShutdown);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnNotifyPresentationClock = Util.ConverterDelegateToPointer(Callback_OnNotifyPresentationClock);
	IntPtr Pointer_OnNotifyTopology = Util.ConverterDelegateToPointer(Callback_OnNotifyTopology);
	IntPtr Pointer_OnNotifyProcessInput = Util.ConverterDelegateToPointer(Callback_OnNotifyProcessInput);
	IntPtr Pointer_OnNotifyProcessOutput = Util.ConverterDelegateToPointer(Callback_OnNotifyProcessOutput);
	IntPtr Pointer_OnNotifyQualityEvent = Util.ConverterDelegateToPointer(Callback_OnNotifyQualityEvent);
	IntPtr Pointer_OnShutdown = Util.ConverterDelegateToPointer(Callback_OnShutdown);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnNotifyPresentationClock = Util.AlocarPointerDelegate(Pointer_OnNotifyPresentationClock);
	gHandle_Delegate_OnNotifyTopology = Util.AlocarPointerDelegate(Pointer_OnNotifyTopology);
	gHandle_Delegate_OnNotifyProcessInput = Util.AlocarPointerDelegate(Pointer_OnNotifyProcessInput);
	gHandle_Delegate_OnNotifyProcessOutput = Util.AlocarPointerDelegate(Pointer_OnNotifyProcessOutput);
	gHandle_Delegate_OnNotifyQualityEvent = Util.AlocarPointerDelegate(Pointer_OnNotifyQualityEvent);
	gHandle_Delegate_OnShutdown = Util.AlocarPointerDelegate(Pointer_OnShutdown);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFQualityManager que envia os eventos.
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_NotifyPresentationClock = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_NotifyPresentationClock>(Pointer_OnNotifyPresentationClock);
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_NotifyTopology = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_NotifyTopology>(Pointer_OnNotifyTopology);
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_NotifyProcessInput = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_NotifyProcessInput>(Pointer_OnNotifyProcessInput);
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_NotifyProcessOutput = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_NotifyProcessOutput>(Pointer_OnNotifyProcessOutput);
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_NotifyQualityEvent = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_NotifyQualityEvent>(Pointer_OnNotifyQualityEvent);
	((CLN_IMFQualityManager*)PonteiroTrabalho)->Evento_Shutdown = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFQualityManager_EventoNativo_Shutdown>(Pointer_OnShutdown);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFQualityManager::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnNotifyPresentationClock.Free();
	gHandle_Delegate_OnNotifyTopology.Free();
	gHandle_Delegate_OnNotifyProcessInput.Free();
	gHandle_Delegate_OnNotifyProcessOutput.Free();
	gHandle_Delegate_OnNotifyQualityEvent.Free();
	gHandle_Delegate_OnShutdown.Free();

	//Libera os ponteiro da classe nativa

	//Ponteiro trabalho.
	CLN_IMFQualityManager* vi_pPonteiroTrabalho = static_cast<CLN_IMFQualityManager*>(PonteiroTrabalho);

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_NotifyPresentationClock))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_NotifyPresentationClock = NULL;
	}
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_NotifyTopology))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_NotifyTopology = NULL;
	}
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_NotifyProcessInput))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_NotifyProcessInput = NULL;
	}
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_NotifyProcessOutput))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_NotifyProcessOutput = NULL;
	}
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_NotifyQualityEvent))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_NotifyQualityEvent = NULL;
	}
	if (ObjetoValido(vi_pPonteiroTrabalho->Evento_Shutdown))
	{
		//Descarta o delegate.
		vi_pPonteiroTrabalho->Evento_Shutdown = NULL;
	}
}


//Métodos que encaminham os eventos nativos gerado pela implementação da classe nativa.

HRESULT CarenMFQualityManager::EncaminharEvento_OnNotifyTopology(IMFTopology* pTopology)
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variveis a serem utilizadas.
	ICarenMFTopology^ vi_TopologyManaged = nullptr;

	//Verifica se o parametro é valido e cria a interface e define os dados.
	if (ObjetoValido(pTopology))
	{
		//Cria a interface.
		vi_TopologyManaged = gcnew CarenMFTopology(false);

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pTopology, vi_TopologyManaged, false);
	}

	//Chama o evento para notificar o usuário
	Resultado = OnNotifyTopology(vi_TopologyManaged);

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}

HRESULT CarenMFQualityManager::EncaminharEvento_OnNotifyPresentationClock(IMFPresentationClock* pClock)
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variveis a serem utilizadas.
	ICarenMFPresentationClock^ vi_PresentationClockManaged = nullptr;

	//Verifica se o parametro é valido e cria a interface e define os dados.
	if (ObjetoValido(pClock))
	{
		//Cria a interface.
		vi_PresentationClockManaged = gcnew CarenMFPresentationClock(false);

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pClock, vi_PresentationClockManaged, false);
	}

	//Chama o evento para notificar o usuário.
	Resultado = OnNotifyPresentationClock(vi_PresentationClockManaged);

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}

HRESULT CarenMFQualityManager::EncaminharEvento_OnNotifyProcessInput(IMFTopologyNode* pNode, long lInputIndex, IMFSample* pSample)
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variveis a serem utilizadas.
	ICarenMFTopologyNode^ vi_TopologyNodeManaged = nullptr;
	ICarenMFSample^ vi_SampleManaged = nullptr;

	//Verifica se o no da tapologia é valido e cria a interface e define seu ponteiro.
	if (ObjetoValido(pNode))
	{
		//Cria a interface.
		vi_TopologyNodeManaged = gcnew CarenMFTopologyNode();

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pNode, vi_TopologyNodeManaged, false);
	}

	//Verifica se a amostra é valida e cria a interface e define seu ponteiro.
	if (ObjetoValido(pSample))
	{
		//Cria a interface.
		vi_SampleManaged = gcnew CarenMFSample(false);

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pSample, vi_SampleManaged, false);
	}

	//Chama o evento para notificar o usuário.
	Resultado = OnNotifyProcessInput(vi_TopologyNodeManaged, static_cast<int>(lInputIndex), vi_SampleManaged);

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}

HRESULT CarenMFQualityManager::EncaminharEvento_OnNotifyProcessOutput(IMFTopologyNode* pNode, long lOutputIndex, IMFSample* pSample)
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variveis a serem utilizadas.
	ICarenMFTopologyNode^ vi_TopologyNodeManaged = nullptr;
	ICarenMFSample^ vi_SampleManaged = nullptr;

	//Verifica se o no da tapologia é valido e cria a interface e define seu ponteiro.
	if (ObjetoValido(pNode))
	{
		//Cria a interface.
		vi_TopologyNodeManaged = gcnew CarenMFTopologyNode();

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pNode, vi_TopologyNodeManaged, false);
	}

	//Verifica se a amostra é valida e cria a interface e define seu ponteiro.
	if (ObjetoValido(pSample))
	{
		//Cria a interface.
		vi_SampleManaged = gcnew CarenMFSample(false);

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pSample, vi_SampleManaged, false);
	}

	//Chama o evento para notificar o usuário.
	Resultado = OnNotifyProcessInput(vi_TopologyNodeManaged, static_cast<int>(lOutputIndex), vi_SampleManaged);

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}

HRESULT CarenMFQualityManager::EncaminharEvento_OnNotifyQualityEvent(IUnknown* pObject, IMFMediaEvent* pEvent)
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variveis a serem utilizadas.
	ICaren^ vi_ObjetoManaged = nullptr;
	ICarenMFMediaEvent^ vi_EventManaged = nullptr;

	//Verifica se o objeto é valido e cria a interface e define seu ponteiro.
	if (ObjetoValido(pObject))
	{
		//Cria a interface.
		vi_ObjetoManaged = gcnew Caren();

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pObject, vi_ObjetoManaged, false);
	}

	//Verifica se o evento é valido e cria a interface e define seu ponteiro.
	if (ObjetoValido(pEvent))
	{
		//Cria a interface.
		vi_EventManaged = gcnew CarenMFMediaEvent();

		//Define o ponteiro na interface.
		CarenSetPointerToICarenSafe(pEvent, vi_EventManaged, false);
	}

	//Chama o evento para notificar o usuário.
	Resultado = OnNotifyQualityEvent(vi_ObjetoManaged, vi_EventManaged);

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}

HRESULT CarenMFQualityManager::EncaminharEvento_OnShutdown()
{
	//Variavel que vai retornar o resultado
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Chama o evento para notificar o usuário.
	Resultado = OnShutdown();

	//Retorna o resultado.
	return static_cast<ResultadoCOM>(Resultado.HResult);
}
