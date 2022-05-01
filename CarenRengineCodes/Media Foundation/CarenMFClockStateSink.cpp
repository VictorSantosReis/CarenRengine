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
#include "CarenMFClockStateSink.h"


//Destruidor.
CarenMFClockStateSink::~CarenMFClockStateSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFClockStateSink::CarenMFClockStateSink(Boolean Param_CriarInterface)
{
	//Verifica se deve criar a classe ou não.
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFClockStateSink();
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFClockStateSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFClockStateSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFClockStateSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFClockStateSink**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFClockStateSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFClockStateSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFClockStateSink**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFClockStateSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFClockStateSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFClockStateSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFClockStateSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFClockStateSink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFClockStateSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFClockStateSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFClockStateSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFClockStateSink();
}





// Métodos da interface proprietaria (ICarenMFClockStateSink)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFClockStateSink::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnClockStart = gcnew DelegateNativo_Evento_OnClockStart(this, &CarenMFClockStateSink::EncaminharEvento_OnClockStart);
	Callback_OnClockPause = gcnew DelegateNativo_Evento_OnClockPause(this, &CarenMFClockStateSink::EncaminharEvento_OnClockPause);
	Callback_OnClockRestart = gcnew DelegateNativo_Evento_OnClockRestart(this, &CarenMFClockStateSink::EncaminharEvento_OnClockRestart);
	Callback_OnClockStop = gcnew DelegateNativo_Evento_OnClockStop(this, &CarenMFClockStateSink::EncaminharEvento_OnClockStop);
	Callback_OnClockSetRate = gcnew DelegateNativo_Evento_OnClockSetRate(this, &CarenMFClockStateSink::EncaminharEvento_OnClockSetRate);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnClockStart = Util.ConverterDelegateToPointer(Callback_OnClockStart);
	IntPtr Pointer_OnClockPause = Util.ConverterDelegateToPointer(Callback_OnClockPause);
	IntPtr Pointer_OnClockRestart = Util.ConverterDelegateToPointer(Callback_OnClockRestart);
	IntPtr Pointer_OnClockStop = Util.ConverterDelegateToPointer(Callback_OnClockStop);
	IntPtr Pointer_OnClockSetRate = Util.ConverterDelegateToPointer(Callback_OnClockSetRate);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnClockStart = Util.AlocarPointerDelegate(Pointer_OnClockStart);
	gHandle_Delegate_OnClockPause = Util.AlocarPointerDelegate(Pointer_OnClockPause);
	gHandle_Delegate_OnClockRestart = Util.AlocarPointerDelegate(Pointer_OnClockRestart);
	gHandle_Delegate_OnClockStop = Util.AlocarPointerDelegate(Pointer_OnClockStop);
	gHandle_Delegate_OnClockSetRate = Util.AlocarPointerDelegate(Pointer_OnClockSetRate);


	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockStart>(Pointer_OnClockStart);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockPause>(Pointer_OnClockPause);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockRestart>(Pointer_OnClockRestart);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockStop>(Pointer_OnClockStop);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockSetRate>(Pointer_OnClockSetRate);
}


/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFClockStateSink::UnRegisterCallback()
{
	//Libera todas as handles alocadas para os eventos.
	gHandle_Delegate_OnClockStart.Free();
	gHandle_Delegate_OnClockPause.Free();
	gHandle_Delegate_OnClockRestart.Free();
	gHandle_Delegate_OnClockStop.Free();
	gHandle_Delegate_OnClockSetRate.Free();

	//Libera os eventos da classe não gerenciada (CLN_IMFClockStateSink)
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate = NULL;
	}
}





//Métodos que recebem os eventos da classe nativa(CLN_IMFClockStateSink)


void CarenMFClockStateSink::EncaminharEvento_OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockStart(hnsSystemTime, llClockStartOffset);
}

void CarenMFClockStateSink::EncaminharEvento_OnClockStop(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockStop(hnsSystemTime);
}

void CarenMFClockStateSink::EncaminharEvento_OnClockPause(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockPause(hnsSystemTime);
}

void CarenMFClockStateSink::EncaminharEvento_OnClockRestart(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockRestart(hnsSystemTime);
}

void CarenMFClockStateSink::EncaminharEvento_OnClockSetRate(MFTIME hnsSystemTime, float flRate)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockSetRate(hnsSystemTime, flRate);
}
