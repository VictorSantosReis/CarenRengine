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
#include "CarenMFMediaKeySessionNotify.h"


//Destruidor.
CarenMFMediaKeySessionNotify::~CarenMFMediaKeySessionNotify()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFMediaKeySessionNotify::CarenMFMediaKeySessionNotify(Boolean Param_CriarInterface)
{
	//Verifica se deve criar a interface ou não.
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFMediaKeySessionNotify();
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFMediaKeySessionNotify::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaKeySessionNotify::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaKeySessionNotify*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaKeySessionNotify::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaKeySessionNotify*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaKeySessionNotify::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaKeySessionNotify::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaKeySessionNotify::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaKeySessionNotify::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaKeySessionNotify::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaKeySessionNotify::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaKeySessionNotify::LiberarReferencia()
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
void CarenMFMediaKeySessionNotify::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaKeySessionNotify();
}



// Métodos da interface proprietária(ICarenMFMediaKeySessionNotify)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFMediaKeySessionNotify::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnKeyAdded = gcnew DelegateNativo_Evento_OnKeyAdded(this, &CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyAdded);
	Callback_OnKeyError = gcnew DelegateNativo_Evento_OnKeyError(this, &CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyError);
	Callback_OnKeyMessage = gcnew DelegateNativo_Evento_OnKeyMessage(this, &CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyMessage);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnKeyAdded = Util.ConverterDelegateToPointer(Callback_OnKeyAdded);
	IntPtr Pointer_OnKeyError = Util.ConverterDelegateToPointer(Callback_OnKeyError);
	IntPtr Pointer_OnKeyMessage = Util.ConverterDelegateToPointer(Callback_OnKeyMessage);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnKeyAdded = Util.AlocarPointerDelegate(Pointer_OnKeyAdded);
	gHandle_Delegate_OnKeyError = Util.AlocarPointerDelegate(Pointer_OnKeyError);
	gHandle_Delegate_OnKeyMessage = Util.AlocarPointerDelegate(Pointer_OnKeyMessage);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFMediaKeySessionNotify que envia os eventos.
	((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyAdded = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyAdded>(Pointer_OnKeyAdded);
	((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyError = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyError>(Pointer_OnKeyError);
	((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyMessage = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyMessage>(Pointer_OnKeyMessage);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFMediaKeySessionNotify::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnKeyAdded.Free();
	gHandle_Delegate_OnKeyError.Free();
	gHandle_Delegate_OnKeyMessage.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyAdded))
	{
		//Descarta o delegate.
		((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyAdded = NULL;
	}
	if (ObjetoValido(((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyError))
	{
		//Descarta o delegate.
		((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyError = NULL;
	}
	if (ObjetoValido(((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyMessage))
	{
		//Descarta o delegate.
		((CLN_IMFMediaKeySessionNotify*)PonteiroTrabalho)->Evento_OnKeyMessage = NULL;
	}
}


//Métodos que encaminham os eventos nativos gerado pela implementação da classe nativa.

void CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyAdded(void)
{
	//Chama o evento para notificar o usuário.
	OnKeyAdded();
}

void CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyError(
	_In_  USHORT code,
	_In_  DWORD systemCode)
{
	//chama o evento para notificar o usuário
	OnKeyError(code, static_cast<UInt32>(systemCode));
}

void CarenMFMediaKeySessionNotify::EncaminharEvento_OnKeyMessage(
	_In_opt_  BSTR destinationURL,
	_In_reads_bytes_(cb)  const BYTE* message,
	_In_  DWORD cb)
{
	//Variaveis a serem Utilizadas.
	Utilidades Util;
	String^ vi_DestinoUrl = nullptr;
	cli::array<Byte>^ vi_Mensagem = nullptr;

	//Verifica se o destino na url é valido e cria a string.
	if (ObjetoValido(destinationURL))
		vi_DestinoUrl = gcnew String(destinationURL);

	//Verifica se a mensagem é valida
	if (ObjetoValido(message))
	{
		//Cria a matriz gerenciada que vai guardar a mensagem.
		vi_Mensagem = gcnew cli::array<Byte>(static_cast<UInt32>(cb));

		//Copia os dados para a matriz gerenciada.
		Util.CopiarBufferNativo_ToGerenciado(const_cast<BYTE**>(&message), vi_Mensagem, static_cast<UINT32>(vi_Mensagem->Length));
	}
}
