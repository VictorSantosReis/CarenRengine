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

typedef void(__stdcall* CLN_IMMNotificationClient_EventoNativo_OnDefaultDeviceChanged)(_In_ EDataFlow flow, _In_ ERole role, _In_ LPCWSTR pwstrDefaultDeviceId);
typedef void(__stdcall* CLN_IMMNotificationClient_EventoNativo_OnDeviceAdded)(_In_ LPCWSTR pwstrDeviceId);
typedef void(__stdcall* CLN_IMMNotificationClient_EventoNativo_OnDeviceRemoved)(_In_ LPCWSTR pwstrDeviceId);
typedef void(__stdcall* CLN_IMMNotificationClient_EventoNativo_OnDeviceStateChanged)(_In_ LPCWSTR pwstrDeviceId, _In_ DWORD dwNewState);
typedef void(__stdcall* CLN_IMMNotificationClient_EventoNativo_OnPropertyValueChanged)(_In_ LPCWSTR pwstrDeviceId, _In_ const PROPERTYKEY key);


//Classe nativa responsável por gerar os eventos da interface IMMNotificationClient para a interface gerenciada.
class CLN_IMMNotificationClient : public IMMNotificationClient
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IMMNotificationClient()
	{
		//Inicia a sessão critica.
		InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IMMNotificationClient()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}


	//Contém todos os delegates que seram chamados para notificar o usuário.
public:
	CLN_IMMNotificationClient_EventoNativo_OnDefaultDeviceChanged Evento_OnDefaultDeviceChanged = NULL;
	CLN_IMMNotificationClient_EventoNativo_OnDeviceAdded Evento_OnDeviceAdded = NULL;
	CLN_IMMNotificationClient_EventoNativo_OnDeviceRemoved Evento_OnDeviceRemoved = NULL;
	CLN_IMMNotificationClient_EventoNativo_OnDeviceStateChanged Evento_OnDeviceStateChanged = NULL;
	CLN_IMMNotificationClient_EventoNativo_OnPropertyValueChanged Evento_OnPropertyValueChanged = NULL;


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
		else if (guid == __uuidof(IMMNotificationClient))
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


	//Métodos chamados pela interface IMMNotificationClient para gerar os eventos.
public:
	virtual HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(
		_In_  LPCWSTR pwstrDeviceId,
		_In_  DWORD dwNewState);

	virtual HRESULT STDMETHODCALLTYPE OnDeviceAdded(
		_In_  LPCWSTR pwstrDeviceId);

	virtual HRESULT STDMETHODCALLTYPE OnDeviceRemoved(
		_In_  LPCWSTR pwstrDeviceId);

	virtual HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(
		_In_  EDataFlow flow,
		_In_  ERole role,
		_In_  LPCWSTR pwstrDefaultDeviceId);

	virtual HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(
		_In_  LPCWSTR pwstrDeviceId,
		_In_  const PROPERTYKEY key);
};

