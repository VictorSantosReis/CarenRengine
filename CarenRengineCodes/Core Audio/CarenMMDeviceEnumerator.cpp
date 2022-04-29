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
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMDeviceEnumerator::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMDeviceEnumerator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMDeviceEnumerator**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMDeviceEnumerator::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMDeviceEnumerator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMDeviceEnumerator**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMDeviceEnumerator::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMDeviceEnumerator::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMMDeviceEnumerator::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
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
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMMDeviceEnumerator::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
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
/// liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
CarenResult CarenMMDeviceEnumerator::EnumAudioEndpoints(
	Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
	Enumeracoes::CA_DEVICE_STATE_XXX Param_EstadosPontoExtremidade,
	ICarenMMDeviceCollection^ Param_Out_ColeçãoDispotivios)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDeviceCollection* vi_OutpColecaoDispositivos = NULL;
	EDataFlow DirecaoFluxo = static_cast<EDataFlow>(Param_DireçãoFluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnumAudioEndpoints(DirecaoFluxo, (DWORD)Param_EstadosPontoExtremidade, &vi_OutpColecaoDispositivos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Chama o método que vai definir o ponteiro de trabalho na interface de destino.
	CarenSetPointerToICarenSafe(vi_OutpColecaoDispositivos, Param_Out_ColeçãoDispotivios, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDefaultAudioEndpoint) - O método recupera o ponto de extremidade de áudio padrão para a direção de fluxo de dados especificado e a função.
/// </summary>
/// <param name="Param_DireçãoFluxo">A direção de fluxo de dados para o dispositivo de ponto de extremidade.</param>
/// <param name="Param_FunçãoDispositivo">A direção do fluxo de dados para um dispositivo de renderização é eRender. A direção do fluxo de dados para um dispositivo de captura é eCapture.</param>
/// <param name="Param_Out_DispositivoDefault">Retorna o dispositivo de Audio padrão do sistema de acordo com sua função e direção. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
CarenResult CarenMMDeviceEnumerator::GetDefaultAudioEndpoint(
	Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
	Enumeracoes::CA_ERole Param_FunçãoDispositivo,
	ICarenMMDevice^ Param_Out_DispositivoDefault)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDevice* vi_OutpDispositivo = NULL;
	EDataFlow DirecaoFluxo = static_cast<EDataFlow>(Param_DireçãoFluxo);
	ERole FunctionDevice = static_cast<ERole>(Param_FunçãoDispositivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDefaultAudioEndpoint(DirecaoFluxo, FunctionDevice, &vi_OutpDispositivo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Chama o método para definir o ponteiro de trabalho na interface de destino.
	CarenSetPointerToICarenSafe(vi_OutpDispositivo, Param_Out_DispositivoDefault, true);

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
/// O chamador é responsável por liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
CarenResult CarenMMDeviceEnumerator::GetDevice(String^ Param_IDPontoExtremidade, ICarenMMDevice^ Param_Out_DispositivoSolicitado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMMDevice* vi_OutpDispositivo = NULL;
	LPCWSTR vi_pIdEndpoint = NULL;
	Utilidades Util;

	//Converte a String para o LPCWSTR
	vi_pIdEndpoint = Util.ConverterStringToConstWCHAR(Param_IDPontoExtremidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDevice(vi_pIdEndpoint, &vi_OutpDispositivo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Chama o método para definir o ponteiro de trabalho na interface de destino.
	CarenSetPointerToICarenSafe(vi_OutpDispositivo, Param_Out_DispositivoSolicitado, true);

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pIdEndpoint);
	
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

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}