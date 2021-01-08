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
#include "CarenMMDeviceEnumerator.h"


//Destruidor.
CarenMMDeviceEnumerator::~CarenMMDeviceEnumerator()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMMDeviceEnumerator::CarenMMDeviceEnumerator()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenMMDeviceEnumerator::CarenMMDeviceEnumerator(CA_CLSCTX Param_Context)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMMDeviceEnumerator* vi_pOutDeviceEnumerator = Nulo;
	const CLSID vi_ClsidDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const GUID vi_RiidEnumerator = __uuidof(IMMDeviceEnumerator);

	//Chama o método para criar a interface.
	Hr = CoCreateInstance(
		vi_ClsidDeviceEnumerator,
		Nulo,
		static_cast<DWORD>(Param_Context),
		vi_RiidEnumerator,
		reinterpret_cast<void**>(&vi_pOutDeviceEnumerator)
	);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutDeviceEnumerator;
}



// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMMDeviceEnumerator::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
		//A operação falhou.
		

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
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMDeviceEnumerator::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMMDeviceEnumerator*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMMDeviceEnumerator::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMMDeviceEnumerator*>(Param_PonteiroNativo);

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
CarenResult CarenMMDeviceEnumerator::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMMDeviceEnumerator::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMMDeviceEnumerator::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMMDeviceEnumerator::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMMDeviceEnumerator::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMMDeviceEnumerator::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMMDeviceEnumerator::LiberarReferencia()
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
void CarenMMDeviceEnumerator::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMMDeviceEnumerator();
}




//Métodos da interface proprietaria



/// <summary>
/// (EnumAudioEndpoints) - O método gera uma coleção de dispositivos de ponto de extremidade de áudio que atendem aos critérios especificados.
/// </summary>
/// <param name="Param_DireçãoFluxo">A direção do fluxo de dados para os dispositivos de ponto de extremidade na coleção. Se o chamador especifica eAll, o método inclui os pontos de extremidade de 
/// renderização e captura na coleção.</param>
/// <param name="Param_EstadosPontoExtremidade">O estado ou Estados dos pontos de extremidade que devem ser incluídos na coleção. O chamador deve definir esse parâmetro para o bit a OR de um ou mais da
/// enumeração.</param>
/// <param name="Param_Out_ColeçãoDispotivios">Recebe a coleção de dispositivos solicitados. Por meio desse método, o chamador obtém uma referência contada para a interface. O chamador é responsável por 
/// liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
CarenResult CarenMMDeviceEnumerator::EnumAudioEndpoints(
	Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
	Enumeracoes::CA_DEVICE_STATE_XXX Param_EstadosPontoExtremidade,
	[Out] ICarenMMDeviceCollection^% Param_Out_ColeçãoDispotivios)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDeviceCollection* pColecaoDispositivos = NULL;
	EDataFlow DirecaoFluxo = static_cast<EDataFlow>(Param_DireçãoFluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAudioEndpoints(DirecaoFluxo, (DWORD)Param_EstadosPontoExtremidade, &pColecaoDispositivos);

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
	Param_Out_ColeçãoDispotivios = gcnew CarenMMDeviceCollection();

	//Chama o método que vai definir o ponteiro de trabalho
	Param_Out_ColeçãoDispotivios->AdicionarPonteiro(pColecaoDispositivos);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDefaultAudioEndpoint) - O método recupera o ponto de extremidade de áudio padrão para a direção de fluxo de dados especificado e a função.
/// </summary>
/// <param name="Param_DireçãoFluxo">A direção de fluxo de dados para o dispositivo de ponto de extremidade.</param>
/// <param name="Param_FunçãoDispositivo">A direção do fluxo de dados para um dispositivo de renderização é eRender. A direção do fluxo de dados para um dispositivo de captura é eCapture.</param>
/// <param name="Param_Out_DispositivoDefault">Retorna o dispositivo de Audio padrão do sistema de acordo com sua função e direção.</param>
CarenResult CarenMMDeviceEnumerator::GetDefaultAudioEndpoint(
	Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
	Enumeracoes::CA_ERole Param_FunçãoDispositivo,
	[Out] ICarenMMDevice^% Param_Out_DispositivoDefault)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDevice* pDispositivo = NULL;
	EDataFlow DirecaoFluxo = static_cast<EDataFlow>(Param_DireçãoFluxo);
	ERole FunctionDevice = static_cast<ERole>(Param_FunçãoDispositivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDefaultAudioEndpoint(DirecaoFluxo, FunctionDevice, &pDispositivo);

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

	//Cria a interface que será retornada ao usuário
	Param_Out_DispositivoDefault = gcnew CarenMMDevice();

	//Chama o método para definir o ponteiro de trabalho.
	Param_Out_DispositivoDefault->AdicionarPonteiro(pDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDevice) - O método recupera um dispositivo de ponto de extremidade de áudio que é identificado por uma cadeia de caracteres de ID de ponto de extremidade.
/// </summary>
/// <param name="Param_IDPontoExtremidade">Ponteiro para uma seqüência de caracteres que contém o ID de ponto de extremidade. O chamador normalmente obtém essa seqüência de caracteres a partir de 
/// ICarenMMDevice::ObterId método ou de um dos métodos na ICarenMMNotificationClient interface.</param>
/// <param name="Param_Out_DispositivoSolicitado">Recebe um ponteiro para a interface do dispositivo solicitado. Por meio desse método, o chamador obtém uma referência contada para a interface. 
/// O chamador é responsável por liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
CarenResult CarenMMDeviceEnumerator::GetDevice(String^ Param_IDPontoExtremidade, [Out] ICarenMMDevice^% Param_Out_DispositivoSolicitado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDevice* pDispositivo = NULL;
	LPCWSTR pIdEndpoint = NULL;
	Utilidades Util;

	//Converte a String para o LPCWSTR
	pIdEndpoint = Util.ConverterStringToConstWCHAR(Param_IDPontoExtremidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDevice(pIdEndpoint, &pDispositivo);

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

	//Cria a interface que será retornada ao usuário
	Param_Out_DispositivoSolicitado = gcnew CarenMMDevice();

	//Chama o método para definir o ponteiro de trabalho.
	Param_Out_DispositivoSolicitado->AdicionarPonteiro(pDispositivo);

Done:;
	//Exclui os dados alocados para a string se eles forem validos.
	if (ObjetoValido(pIdEndpoint))
	{
		//Deleta os dados da memoria
		delete pIdEndpoint;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterEndpointNotificationCallback) - O método registra a interface de retorno de chamada de notificação do cliente.
/// </summary>
/// <param name="Param_Cliente">A interface que será registrada para receber as notificações.</param>
CarenResult CarenMMDeviceEnumerator::RegisterEndpointNotificationCallback(ICarenMMNotificationClient^ Param_Cliente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMNotificationClient* pNotifyCliente = NULL;

	//Chama o método para recuperar o ponteiro para a interface.
	Resultado = Param_Cliente->RecuperarPonteiro((LPVOID*)&pNotifyCliente);

	//Verifica o resultado da recuperação do ponteiro.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface não existe.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterEndpointNotificationCallback(pNotifyCliente);

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
/// (UnregisterEndpointNotificationCallback) - O método exclui o registro de uma interface de notificação que o cliente registrado em uma chamada anterior para o IMMDeviceEnumerator::RegisterEndpointNotificationCallback método.
/// </summary>
/// <param name="Param_Cliente">A interface que será removida para não receber mais notificações.</param>
CarenResult CarenMMDeviceEnumerator::UnregisterEndpointNotificationCallback(ICarenMMNotificationClient^ Param_Cliente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMNotificationClient* pNotifyCliente = NULL;

	//Chama o método para recuperar o ponteiro para a interface.
	Resultado = Param_Cliente->RecuperarPonteiro((LPVOID*)&pNotifyCliente);

	//Verifica o resultado da recuperação do ponteiro.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface não existe.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnregisterEndpointNotificationCallback(pNotifyCliente);

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