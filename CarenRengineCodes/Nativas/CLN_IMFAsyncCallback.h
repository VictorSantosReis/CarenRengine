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


#pragma once
#include "../SDK_Base.h"

//Typedefs que definem os delegates de eventos que seram chamados para notificar o usuario.
typedef void(__stdcall* CLN_IMFAsyncCallback_EventoNativo_Invoke)(__RPC__in_opt IMFAsyncResult*);
typedef int(__stdcall* CLN_IMFAsyncCallback_EventoNativo_GetParameters)();

//Classe responsável por notificar o usuário em classe gerenciada de uma operação assincrona.
class CLN_IMFAsyncCallback : public IMFAsyncCallback
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IMFAsyncCallback()
	{
		//Inicia a sessão critica.
		BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);

		//Verifica o resultado
		if (Resultado)
		{

		}
	}

	~CLN_IMFAsyncCallback()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}

	//Variaveis que vão conter o valor para o método (GetParameters) definido pelo usuario.
public:
	DWORD GetParameters_dwFlags = 0;
	DWORD GetParameters_pdwQueue = 0;

	//Contém todos os delegates que seram chamados para notificar uma operação assincrona.
public:
	//O Evento notifica a conclusão de uma operação assincrona.
	CLN_IMFAsyncCallback_EventoNativo_Invoke Evento_OnInvoke = NULL;
	
	//Evento responsável por notificar o usuário que uma chamada está requisitando as configurações do sistema Assincrono.
	//O cliente deve chamar o método (SetParameters) nesta classe para definir os valores durante a chamada deste evento.
	//Atenção: Se o evento retorna 1, indica que o usuário chamou(SetParameters) e configurou o evento, se não, o método não foi configurado e retorna E_NOTIMPL.
	CLN_IMFAsyncCallback_EventoNativo_GetParameters Evento_OnGetParameters = NULL;



	//Métodos da Interface IUnknown.
public:
	//Procura uma determina interface nessa classe.
	STDMETHODIMP QueryInterface(REFIID guid, void** pObj)
	{
		if (pObj == NULL)
		{
			return E_POINTER;
		}
		else if (guid == IID_IUnknown) {
			*pObj = this;
			AddRef();
			return S_OK;
		}
		else if (guid == IID_IMFAsyncCallback)
		{
			*pObj = this;
			AddRef();
			return S_OK;
		}
		else
		{
			*pObj = NULL;
			return E_NOINTERFACE;
		}
	}

	//Adiciona uma referência a classe.
	STDMETHODIMP_(ULONG) AddRef()
	{
		//Incrementa a quantidade de referências.
		return InterlockedIncrement(&RefCount);
	}

	//Libera uma referência a classe.
	STDMETHODIMP_(ULONG) Release()
	{
		//Desecrementa a quantidade de referências e verifica.
		ULONG result = InterlockedDecrement(&RefCount);
		if (result == 0) delete this;
		return result;
	}


	//Métodos da Interface IMFAsyncCallback
public:
	virtual HRESULT STDMETHODCALLTYPE GetParameters(__RPC__out DWORD* pdwFlags, __RPC__out DWORD* pdwQueue);

	virtual HRESULT STDMETHODCALLTYPE Invoke(__RPC__in_opt IMFAsyncResult* pAsyncResult);


	//Método utilizado para definir os valores que seram retornados durante a chamada do evento (Evento_OnGetParameters)
public:
	//Método responsável por definir as configurações do sistema Assincrono para ser retornado pelo método (GetParameters)
	virtual void SetParameters(DWORD dwFlags, DWORD dwQueue);
};

