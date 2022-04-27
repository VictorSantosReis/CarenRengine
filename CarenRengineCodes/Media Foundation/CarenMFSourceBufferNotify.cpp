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
#include "CarenMFSourceBufferNotify.h"

//Destruidor.
CarenMFSourceBufferNotify::~CarenMFSourceBufferNotify()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFSourceBufferNotify::CarenMFSourceBufferNotify()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.

	//Cria a interface impelementada internamente.
	PonteiroTrabalho = new CLN_IMFSourceBufferNotify();
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFSourceBufferNotify::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceBufferNotify::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceBufferNotify*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceBufferNotify**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceBufferNotify::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceBufferNotify*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceBufferNotify**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceBufferNotify::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceBufferNotify::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFSourceBufferNotify::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFSourceBufferNotify::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSourceBufferNotify::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSourceBufferNotify::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceBufferNotify::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFSourceBufferNotify::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFSourceBufferNotify();
}



// Métodos da interface proprietária(ICarenMFSourceBufferNotify)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFSourceBufferNotify::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnAbort = gcnew DelegateNativo_Evento_OnAbort(this, &CarenMFSourceBufferNotify::EncaminharEvento_OnAbort);
	Callback_OnError = gcnew DelegateNativo_Evento_OnError(this, &CarenMFSourceBufferNotify::EncaminharEvento_OnError);
	Callback_OnUpdate = gcnew DelegateNativo_Evento_OnUpdate(this, &CarenMFSourceBufferNotify::EncaminharEvento_OnUpdate);
	Callback_OnUpdateStart = gcnew DelegateNativo_Evento_OnUpdateStart(this, &CarenMFSourceBufferNotify::EncaminharEvento_OnUpdateStart);
	Callback_OnUpdateEnd = gcnew DelegateNativo_Evento_OnUpdateEnd(this, &CarenMFSourceBufferNotify::EncaminharEvento_OnUpdateEnd);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnAbort = Util.ConverterDelegateToPointer(Callback_OnAbort);
	IntPtr Pointer_OnError = Util.ConverterDelegateToPointer(Callback_OnError);
	IntPtr Pointer_OnUpdate = Util.ConverterDelegateToPointer(Callback_OnUpdate);
	IntPtr Pointer_OnUpdateStart = Util.ConverterDelegateToPointer(Callback_OnUpdateStart);
	IntPtr Pointer_OnUpdateEnd = Util.ConverterDelegateToPointer(Callback_OnUpdateEnd);


	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnAbort = Util.AlocarPointerDelegate(Pointer_OnAbort);
	gHandle_Delegate_OnError = Util.AlocarPointerDelegate(Pointer_OnError);
	gHandle_Delegate_OnUpdate = Util.AlocarPointerDelegate(Pointer_OnUpdate);
	gHandle_Delegate_OnUpdateStart = Util.AlocarPointerDelegate(Pointer_OnUpdateStart);
	gHandle_Delegate_OnUpdateEnd = Util.AlocarPointerDelegate(Pointer_OnUpdateEnd);

	//Registra os delegates criados para os delegates nativo na classe CLN_IAudioSessionEvents que envia os eventos.
	((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnAbort = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceBufferNotify_EventoNativo_OnAbort>(Pointer_OnAbort);
	((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnError = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceBufferNotify_EventoNativo_OnError>(Pointer_OnError);
	((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdate = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceBufferNotify_EventoNativo_OnUpdate>(Pointer_OnUpdate);
	((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateStart = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceBufferNotify_EventoNativo_OnUpdateStart>(Pointer_OnUpdateStart);
	((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateEnd = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceBufferNotify_EventoNativo_OnUpdateEnd>(Pointer_OnUpdateEnd);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFSourceBufferNotify::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnAbort.Free();
	gHandle_Delegate_OnError.Free();
	gHandle_Delegate_OnUpdate.Free();
	gHandle_Delegate_OnUpdateStart.Free();
	gHandle_Delegate_OnUpdateEnd.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnAbort))
	{
		//Descarta o delegate.
		((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnAbort = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnError))
	{
		//Descarta o delegate.
		((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnError = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdate))
	{
		//Descarta o delegate.
		((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdate = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateStart))
	{
		//Descarta o delegate.
		((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateStart = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateEnd))
	{
		//Descarta o delegate.
		((CLN_IMFSourceBufferNotify*)PonteiroTrabalho)->Evento_OnUpdateEnd = NULL;
	}
}

//Métodos que encaminham os eventos nativos gerado pela implementação da classe nativa.

void CarenMFSourceBufferNotify::EncaminharEvento_OnUpdateStart()
{
	//Chama o evento para notificar o usuário.
	OnUpdateStart();
}

void CarenMFSourceBufferNotify::EncaminharEvento_OnAbort()
{
	//Chama o evento para notificar o usuário.
	OnAbort();
}

void CarenMFSourceBufferNotify::EncaminharEvento_OnError(_In_ HRESULT hr)
{
	//Chama o evento para notificar o usuário.
	OnError(CarenResult(hr, false));
}

void CarenMFSourceBufferNotify::EncaminharEvento_OnUpdate()
{
	//Chama o evento para notificar o usuário.
	OnUpdate();
}

void CarenMFSourceBufferNotify::EncaminharEvento_OnUpdateEnd()
{
	//Chama o evento para notificar o usuário.
	OnUpdateEnd();
}
