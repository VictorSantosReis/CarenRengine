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
#include "CarenMFAsyncCallback.h"

//Destruidor.
CarenMFAsyncCallback::~CarenMFAsyncCallback()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Construtor
CarenMFAsyncCallback::CarenMFAsyncCallback(Boolean Param_CriarInterface)
{
	//Verifica se deve criar a classe ou não.
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFAsyncCallback();
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFAsyncCallback::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAsyncCallback::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAsyncCallback*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAsyncCallback**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFAsyncCallback::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFAsyncCallback*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFAsyncCallback**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAsyncCallback::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFAsyncCallback::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFAsyncCallback::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFAsyncCallback::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFAsyncCallback::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFAsyncCallback::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFAsyncCallback::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFAsyncCallback();
}




//Métodos da interface ICarenCarenAsyncCallback


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFAsyncCallback::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnGetParameters = gcnew DelegateNativo_Evento_OnGetParameters(this, &CarenMFAsyncCallback::EncaminharEvento_OnGetParameters);
	Callback_OnInvoke = gcnew DelegateNativo_Evento_OnInvoke(this, &CarenMFAsyncCallback::EncaminharEvento_OnInvoke);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnGetParameters = Util.ConverterDelegateToPointer(Callback_OnGetParameters);
	IntPtr Pointer_OnInvoke = Util.ConverterDelegateToPointer(Callback_OnInvoke);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnGetParameters = Util.AlocarPointerDelegate(Pointer_OnGetParameters);
	gHandle_Delegate_OnInvoke = Util.AlocarPointerDelegate(Pointer_OnInvoke);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
	((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnGetParameters = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFAsyncCallback_EventoNativo_GetParameters>(Pointer_OnGetParameters);
	((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnInvoke = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFAsyncCallback_EventoNativo_Invoke>(Pointer_OnInvoke);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFAsyncCallback::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnGetParameters.Free();
	gHandle_Delegate_OnInvoke.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnGetParameters))
	{
		//Descarta o delegate.
		((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnGetParameters = NULL;
	}
	if (ObjetoValido(((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnInvoke))
	{
		//Descarta o delegate.
		((CLN_IMFAsyncCallback*)PonteiroTrabalho)->Evento_OnInvoke = NULL;
	}
}



// Métodos de encaminhamento dos eventos


/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (GetParameters) na classe nativa.
/// </summary>
HRESULT CarenMFAsyncCallback::EncaminharEvento_OnGetParameters(__RPC__out DWORD* Param_Flags, __RPC__out DWORD* Param_Queue)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variavel a ser retornada.
	CarenResult Resultado = ResultCode::ER_FAIL;

	//Variaveis utilizadas.
	CA_MFASYNC_BEHAVIOR vi_OutFlags = CA_MFASYNC_BEHAVIOR::Zero;
	CA_MFASYNC_CALLBACK_QUEUE vi_OutQueue = CA_MFASYNC_CALLBACK_QUEUE::CA_MFASYNC_CALLBACK_QUEUE_MULTITHREADED;

	//Invoca o evento para o usuário definir os valores a serem retornado por referencia.
	Resultado = OnGetParameters(vi_OutFlags, vi_OutQueue);

	//Define os dados nos parametros de saida para o método nativo.
	*Param_Flags = static_cast<DWORD>(vi_OutFlags);
	*Param_Queue = static_cast<DWORD>(vi_OutQueue);

	//Retorna o resultado.
	return static_cast<HRESULT>(Resultado.HResult);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (Invoke) na classe nativa.
/// </summary>
HRESULT CarenMFAsyncCallback::EncaminharEvento_OnInvoke(IMFAsyncResult* Param_AsyncResult)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Variavel a ser retornada.
	CarenResult Resultado = ResultCode::ER_FAIL;

	//Variaveis utilizadas.
	ICarenMFAsyncResult^ vi_AsyncResult = nullptr;

	//Verifica se o ponteiro é valido
	if (ObjetoValido(Param_AsyncResult))
	{
		//Cria a interface a ser retornada.
		vi_AsyncResult = gcnew CarenMFAsyncResult();

		//Define o ponteiro na interface.
		vi_AsyncResult->AdicionarPonteiro(Param_AsyncResult);
	}

	//Chama o evento para notificar o usuário
	Resultado = OnInvoke(vi_AsyncResult);

	//Retorna o resultado.
	return Resultado.HResult;
}