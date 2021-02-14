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
typedef HRESULT(__stdcall* CLN_IMFAsyncCallback_EventoNativo_Invoke)(__RPC__in_opt IMFAsyncResult*);
typedef HRESULT(__stdcall* CLN_IMFAsyncCallback_EventoNativo_GetParameters)(__RPC__out DWORD*, __RPC__out DWORD*);

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
		if (!Resultado)
			throw gcnew Exception("Não foi possivel inicializar a 'Sessão Criticca' de código para sincronização de chamadas!");
	}

	~CLN_IMFAsyncCallback()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}

	//Contém todos os delegates que seram chamados para notificar uma operação assincrona.
public:
	CLN_IMFAsyncCallback_EventoNativo_Invoke Evento_OnInvoke = NULL;	
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
};

