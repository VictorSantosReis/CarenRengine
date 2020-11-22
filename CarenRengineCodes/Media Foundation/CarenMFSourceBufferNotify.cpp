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
	//CÓDIGO DE CRIAÇÃO.

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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
CarenResult CarenMFSourceBufferNotify::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceBufferNotify*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFSourceBufferNotify::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceBufferNotify*>(Param_PonteiroNativo);

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
CarenResult CarenMFSourceBufferNotify::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceBufferNotify::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceBufferNotify::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceBufferNotify::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenMFSourceBufferNotify::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
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
