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
#include "CarenMFSinkWriterCallback.h"


//Destruidor.
CarenMFSinkWriterCallback::~CarenMFSinkWriterCallback()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFSinkWriterCallback::CarenMFSinkWriterCallback(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar a classe.
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFSinkWriterCallback();
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
CarenResult CarenMFSinkWriterCallback::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSinkWriterCallback::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSinkWriterCallback*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSinkWriterCallback**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSinkWriterCallback::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSinkWriterCallback*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSinkWriterCallback**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSinkWriterCallback::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSinkWriterCallback::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFSinkWriterCallback::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFSinkWriterCallback::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSinkWriterCallback::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSinkWriterCallback::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSinkWriterCallback::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFSinkWriterCallback::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFSinkWriterCallback();
}






//
// Métodos da interface proprietaria
//

/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFSinkWriterCallback::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnFinalize = gcnew DelegateNativo_Evento_OnFinalize(this, &CarenMFSinkWriterCallback::EncaminharEvento_OnFinalize);
	Callback_OnMarker = gcnew DelegateNativo_Evento_OnMarker(this, &CarenMFSinkWriterCallback::EncaminharEvento_OnMarker);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnFinalize = Util.ConverterDelegateToPointer(Callback_OnFinalize);
	IntPtr Pointer_OnMarker = Util.ConverterDelegateToPointer(Callback_OnMarker);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnFinalize = Util.AlocarPointerDelegate(Pointer_OnFinalize);
	gHandle_Delegate_OnMarker = Util.AlocarPointerDelegate(Pointer_OnMarker);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSinkWriterCallback que envia os eventos.
	((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnFinalize = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSinkWriterCallback_EventoNativo_OnFinalize>(Pointer_OnFinalize);
	((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnMarker = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSinkWriterCallback_EventoNativo_OnMarker>(Pointer_OnMarker);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFSinkWriterCallback::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnFinalize.Free();
	gHandle_Delegate_OnMarker.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnFinalize))
	{
		//Descarta o delegate.
		((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnFinalize = NULL;
	}
	if (ObjetoValido(((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnMarker))
	{
		//Descarta o delegate.
		((CLN_IMFSinkWriterCallback*)PonteiroTrabalho)->Evento_OnMarker = NULL;
	}
}


//
// Métodos internos que são chamados pela classe nativa para notificar os eventos ocorridos.
//


/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFinalize) da classe (IMFSinkWriterCallback) para o usuário em classe gerenciada.
/// </summary>
void CarenMFSinkWriterCallback::EncaminharEvento_OnFinalize(HRESULT Param_HResultCode)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.


	//Chama o evento para notificar o usuário
	OnFinalize((int)Param_HResultCode);
}

/// <summary>
///Método responsável por encaminhar o (Evento) nativo (OnMarker) da classe (IMFSinkWriterCallback) para o usuário em classe gerenciada.
/// </summary>
void CarenMFSinkWriterCallback::EncaminharEvento_OnMarker(DWORD Param_FluxoID, LPVOID Param_ObjetoContexto)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.


	//Variveis utilizadas no método.
	ICaren^ ObjetoContexto = nullptr;

	//Verifica se expos um objeto e cria a interface que vai contê-lo.
	if (ObjetoValido(Param_ObjetoContexto))
	{
		//Cria a interface que vai conter o objeto
		ObjetoContexto = gcnew Caren();

		//Define o ponteiro para o objeto.
		ObjetoContexto->AdicionarPonteiro(Param_ObjetoContexto);
	}

	//Chama o evento para notificar o usuário
	OnMarker(Param_FluxoID, ObjetoContexto);
}
