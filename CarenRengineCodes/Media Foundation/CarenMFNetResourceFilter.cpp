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
#include "CarenMFNetResourceFilter.h"

//Destruidor.
CarenMFNetResourceFilter::~CarenMFNetResourceFilter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFNetResourceFilter::CarenMFNetResourceFilter()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.

	//Cria a interace a parti da classe nativa implementada internamente.
	IMFNetResourceFilter* vi_pNetPointer = new CLN_IMFNetResourceFilter();
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFNetResourceFilter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetResourceFilter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetResourceFilter*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetResourceFilter**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetResourceFilter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetResourceFilter*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetResourceFilter**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetResourceFilter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetResourceFilter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetResourceFilter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetResourceFilter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetResourceFilter::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetResourceFilter::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetResourceFilter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetResourceFilter();
}



// Métodos da interface proprietária(ICarenMFNetResourceFilter)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFNetResourceFilter::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnRedirect = gcnew DelegateNativo_Evento_OnRedirect(this, &CarenMFNetResourceFilter::EncaminharEvento_OnRedirect);
	Callback_OnSendingRequest = gcnew DelegateNativo_Evento_OnSendingRequest(this, &CarenMFNetResourceFilter::EncaminharEvento_OnSendingRequest);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnRedirect = Util.ConverterDelegateToPointer(Callback_OnRedirect);
	IntPtr Pointer_OnSendingRequest = Util.ConverterDelegateToPointer(Callback_OnSendingRequest);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnRedirect = Util.AlocarPointerDelegate(Pointer_OnRedirect);
	gHandle_Delegate_OnSendingRequest = Util.AlocarPointerDelegate(Pointer_OnSendingRequest);

	//Registra os delegates criados para os delegates nativo na classe CLN_IAudioSessionEvents que envia os eventos.
	((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnRedirect = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFNetResourceFilter_EventoNativo_OnRedirect>(Pointer_OnRedirect);
	((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnSendingRequest = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFNetResourceFilter_EventoNativo_OnSendingRequest>(Pointer_OnSendingRequest);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFNetResourceFilter::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnRedirect.Free();
	gHandle_Delegate_OnSendingRequest.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnRedirect))
	{
		//Descarta o delegate.
		((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnRedirect = NULL;
	}
	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnSendingRequest))
	{
		//Descarta o delegate.
		((CLN_IMFNetResourceFilter*)PonteiroTrabalho)->Evento_OnSendingRequest = NULL;
	}
}


//Métodos que encaminham os eventos nativos gerado pela implementação da classe nativa.

HRESULT CarenMFNetResourceFilter::EncaminharEvento_OnRedirect(_In_ LPCWSTR pszUrl, _Out_ VARIANT_BOOL* pvbCancel)
{
	//Variavel de resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	String^ vi_Url = nullptr;
	Boolean vi_InOutCancel = pvbCancel == 0 ? false : true;

	//Verifica se a string é valida e cria a string a ser enviado no evento.
	if (ObjetoValido(pszUrl))
		vi_Url = gcnew String(vi_Url);

	//Chama o evento para notificar o usuário.
	Resultado = OnRedirect(vi_Url, vi_InOutCancel);

	//Define o valor Booleano na saida agora.
	*pvbCancel = vi_InOutCancel ? -1 : 0;

	//Retorna o resultado
	return static_cast<HRESULT>(Resultado.HResult);
}

HRESULT CarenMFNetResourceFilter::EncaminharEvento_OnSendingRequest(_In_ LPCWSTR pszUrl)
{
	//Variavel de resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	String^ vi_Url = nullptr;

	//Verifica se a string é valida e cria a string a ser enviado no evento.
	if (ObjetoValido(pszUrl))
		vi_Url = gcnew String(vi_Url);

	//Chama o evento para notificar o usuário.
	Resultado = OnSendingRequest(vi_Url);

	//Retorna o resultado
	return static_cast<HRESULT>(Resultado.HResult);
}
