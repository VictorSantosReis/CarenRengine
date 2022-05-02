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
#include "CarenMMNotificationClient.h"


//Destruidor.
CarenMMNotificationClient::~CarenMMNotificationClient()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMMNotificationClient::CarenMMNotificationClient(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Cria a implementação da interface
		PonteiroTrabalho = new CLN_IMMNotificationClient();
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
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
CarenResult CarenMMNotificationClient::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMNotificationClient::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMNotificationClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMNotificationClient**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMNotificationClient::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMNotificationClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMNotificationClient**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMNotificationClient::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMNotificationClient::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMMNotificationClient::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMMNotificationClient::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMMNotificationClient::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMMNotificationClient::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMMNotificationClient::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMMNotificationClient();
}


//
//Métodos da interface ICarenMMNotificaçãoDispositivoAudioCliente
//


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMMNotificationClient::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnDefaultDeviceChanged = gcnew DelegateNativo_Evento_OnDefaultDeviceChanged(this, &CarenMMNotificationClient::EncaminharEvento_OnDefaultDeviceChanged);
	Callback_OnDeviceAdded = gcnew DelegateNativo_Evento_OnDeviceAdded(this, &CarenMMNotificationClient::EncaminharEvento_OnDeviceAdded);
	Callback_OnDeviceRemoved = gcnew DelegateNativo_Evento_OnDeviceRemoved(this, &CarenMMNotificationClient::EncaminharEvento_OnDeviceRemoved);
	Callback_OnDeviceStateChanged = gcnew DelegateNativo_Evento_OnDeviceStateChanged(this, &CarenMMNotificationClient::EncaminharEvento_OnDeviceStateChanged);
	Callback_OnPropertyValueChanged = gcnew DelegateNativo_Evento_OnPropertyValueChanged(this, &CarenMMNotificationClient::EncaminharEvento_OnPropertyValueChanged);


	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnDefaultDeviceChanged = Util.ConverterDelegateToPointer(Callback_OnDefaultDeviceChanged);
	IntPtr Pointer_OnDeviceAdded = Util.ConverterDelegateToPointer(Callback_OnDeviceAdded);
	IntPtr Pointer_OnDeviceRemoved = Util.ConverterDelegateToPointer(Callback_OnDeviceRemoved);
	IntPtr Pointer_OnDeviceStateChanged = Util.ConverterDelegateToPointer(Callback_OnDeviceStateChanged);
	IntPtr Pointer_OnPropertyValueChanged = Util.ConverterDelegateToPointer(Callback_OnPropertyValueChanged);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnDefaultDeviceChanged = Util.AlocarPointerDelegate(Pointer_OnDefaultDeviceChanged);
	gHandle_Delegate_OnDeviceAdded = Util.AlocarPointerDelegate(Pointer_OnDeviceAdded);
	gHandle_Delegate_OnDeviceRemoved = Util.AlocarPointerDelegate(Pointer_OnDeviceRemoved);
	gHandle_Delegate_OnDeviceStateChanged = Util.AlocarPointerDelegate(Pointer_OnDeviceStateChanged);
	gHandle_Delegate_OnPropertyValueChanged = Util.AlocarPointerDelegate(Pointer_OnPropertyValueChanged);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMMNotificationClient que envia os eventos.
	((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDefaultDeviceChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMMNotificationClient_EventoNativo_OnDefaultDeviceChanged>(Pointer_OnDefaultDeviceChanged);
	((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceAdded = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMMNotificationClient_EventoNativo_OnDeviceAdded>(Pointer_OnDeviceAdded);
	((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceRemoved = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMMNotificationClient_EventoNativo_OnDeviceRemoved>(Pointer_OnDeviceRemoved);
	((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceStateChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMMNotificationClient_EventoNativo_OnDeviceStateChanged>(Pointer_OnDeviceStateChanged);
	((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnPropertyValueChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMMNotificationClient_EventoNativo_OnPropertyValueChanged>(Pointer_OnPropertyValueChanged);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMMNotificationClient::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnDefaultDeviceChanged.Free();
	gHandle_Delegate_OnDeviceAdded.Free();
	gHandle_Delegate_OnDeviceRemoved.Free();
	gHandle_Delegate_OnDeviceStateChanged.Free();
	gHandle_Delegate_OnPropertyValueChanged.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDefaultDeviceChanged))
	{
		//Descarta o delegate.
		((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDefaultDeviceChanged = NULL;
	}
	if (ObjetoValido(((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceAdded))
	{
		//Descarta o delegate.
		((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceAdded = NULL;
	}
	if (ObjetoValido(((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceRemoved))
	{
		//Descarta o delegate.
		((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceRemoved = NULL;
	}
	if (ObjetoValido(((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceStateChanged))
	{
		//Descarta o delegate.
		((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnDeviceStateChanged = NULL;
	}
	if (ObjetoValido(((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnPropertyValueChanged))
	{
		//Descarta o delegate.
		((CLN_IMMNotificationClient*)PonteiroTrabalho)->Evento_OnPropertyValueChanged = NULL;
	}
}





//
// Métodos internos que são chamados pela classe nativa para notificar os eventos ocorridos.
//

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDefaultDeviceChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
/// </summary>
void CarenMMNotificationClient::EncaminharEvento_OnDefaultDeviceChanged(_In_ EDataFlow flow, _In_ ERole role, _In_ LPCWSTR pwstrDefaultDeviceId) 
{
	//Thread-Safe

	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variaveis
	CA_EDataFlow DirecaoFluxo = static_cast<CA_EDataFlow>(flow);
	CA_ERole FunctionDevice = static_cast<CA_ERole>(role);
	String^ IDDispositivo = nullptr;

	//Verifica se a String enviada pelo método é valida
	if (ObjetoValido(pwstrDefaultDeviceId))
	{
		//Cria a String com base no enviado pelo método
		IDDispositivo = gcnew String(pwstrDefaultDeviceId);
	}
	else
	{
		//A string não é valida

		//Define que a String retornada é nula.
		IDDispositivo = gcnew String("NULO");
	}

	//Chama o evento para notifica o usuário
	OnDefaultDeviceChanged(DirecaoFluxo, FunctionDevice, IDDispositivo);

	//Libera a String se ela for valida ainda
	if (!String::IsNullOrEmpty(IDDispositivo))
	{
		//Libera a String
		IDDispositivo = "";
		IDDispositivo = nullptr;
	}
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDeviceAdded) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
/// </summary>
void CarenMMNotificationClient::EncaminharEvento_OnDeviceAdded(_In_ LPCWSTR pwstrDeviceId) 
{
	//Thread-Safe

	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variaveis
	String^ IDDispositivo = nullptr;

	//Verifica se a String enviada pelo método é valida
	if (ObjetoValido(pwstrDeviceId))
	{
		//Cria a String com base no enviado pelo método
		IDDispositivo = gcnew String(pwstrDeviceId);
	}
	else
	{
		//A string não é valida

		//Define que a String retornada é nula.
		IDDispositivo = gcnew String("NULO");
	}

	//Chama o evento para notifica o usuário
	OnDeviceAdded(IDDispositivo);

	//Libera a String se ela for valida ainda
	if (!String::IsNullOrEmpty(IDDispositivo))
	{
		//Libera a String
		IDDispositivo = "";
		IDDispositivo = nullptr;
	}
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDeviceRemoved) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
/// </summary>
void CarenMMNotificationClient::EncaminharEvento_OnDeviceRemoved(_In_ LPCWSTR pwstrDeviceId) 
{
	//Thread-Safe

	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variaveis
	String^ IDDispositivo = nullptr;

	//Verifica se a String enviada pelo método é valida
	if (ObjetoValido(pwstrDeviceId))
	{
		//Cria a String com base no enviado pelo método
		IDDispositivo = gcnew String(pwstrDeviceId);
	}
	else
	{
		//A string não é valida

		//Define que a String retornada é nula.
		IDDispositivo = gcnew String("NULO");
	}

	//Chama o evento para notifica o usuário
	OnDeviceRemoved(IDDispositivo);

	//Libera a String se ela for valida ainda
	if (!String::IsNullOrEmpty(IDDispositivo))
	{
		//Libera a String
		IDDispositivo = "";
		IDDispositivo = nullptr;
	}
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnDeviceStateChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
/// </summary>
void CarenMMNotificationClient::EncaminharEvento_OnDeviceStateChanged(_In_ LPCWSTR pwstrDeviceId, _In_ DWORD dwNewState) 
{
	//Thread-Safe

	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variaveis
	String^ IDDispositivo = nullptr;
	CA_DEVICE_STATE_XXX StateDeviceAudio = static_cast<CA_DEVICE_STATE_XXX>(dwNewState);

	//Verifica se a String enviada pelo método é valida
	if (ObjetoValido(pwstrDeviceId))
	{
		//Cria a String com base no enviado pelo método
		IDDispositivo = gcnew String(pwstrDeviceId);
	}
	else
	{
		//A string não é valida

		//Define que a String retornada é nula.
		IDDispositivo = gcnew String("NULO");
	}

	//Chama o evento para notifica o usuário
	OnDeviceStateChanged(IDDispositivo, StateDeviceAudio);

	//Libera a String se ela for valida ainda
	if (!String::IsNullOrEmpty(IDDispositivo))
	{
		//Libera a String
		IDDispositivo = "";
		IDDispositivo = nullptr;
	}
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnPropertyValueChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
/// </summary>
void CarenMMNotificationClient::EncaminharEvento_OnPropertyValueChanged(_In_ LPCWSTR pwstrDeviceId, _In_ const PROPERTYKEY key)
{
	//Thread-Safe

	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variaveis
	String^ IDDispositivo = nullptr;
	CA_PROPERTYKEY^ KeyPropriedade = gcnew CA_PROPERTYKEY();
	Utilidades Util;

	//Verifica se a String enviada pelo método é valida
	if (ObjetoValido(pwstrDeviceId))
	{
		//Cria a String com base no enviado pelo método
		IDDispositivo = gcnew String(pwstrDeviceId);
	}
	else
	{
		//A string não é valida

		//Define que a String retornada é nula.
		IDDispositivo = gcnew String("NULO");
	}

	//Define os dados na estrutura
	KeyPropriedade->PID = key.pid;
	KeyPropriedade->GUIDProp = Util.ConverterGuidToString(key.fmtid);

	//Chama o evento para notifica o usuário
	OnPropertyValueChanged(IDDispositivo, KeyPropriedade);

	//Libera a String se ela for valida ainda
	if (!String::IsNullOrEmpty(IDDispositivo))
	{
		//Libera a String
		IDDispositivo = "";
		IDDispositivo = nullptr;
	}

	//Descarta a estrutura
	KeyPropriedade->GUIDProp = "";
	KeyPropriedade->GUIDProp = nullptr;
	KeyPropriedade->PID = 0;
}