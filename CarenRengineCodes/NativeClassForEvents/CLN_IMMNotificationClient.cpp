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
#include "../NativeClassForEvents/CLN_IMMNotificationClient.h"


//
//Métodos da interfaces proprietaria
//

HRESULT STDMETHODCALLTYPE CLN_IMMNotificationClient::OnDeviceStateChanged(_In_ LPCWSTR pwstrDeviceId, _In_ DWORD dwNewState)
{
	//Entra na sessão critica.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido.
	if (ObjetoValido(Evento_OnDeviceStateChanged))
	{
		//Chama o evento
		Evento_OnDeviceStateChanged(pwstrDeviceId, dwNewState);
	}
	else
	{
		//O evento não foi configurado.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna sucesso
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLN_IMMNotificationClient::OnDeviceAdded(_In_ LPCWSTR pwstrDeviceId) 
{
	//Entra na sessão critica.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido.
	if (ObjetoValido(Evento_OnDeviceAdded))
	{
		//Chama o evento
		Evento_OnDeviceAdded(pwstrDeviceId);
	}
	else
	{
		//O evento não foi configurado.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna sucesso
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLN_IMMNotificationClient::OnDeviceRemoved(_In_ LPCWSTR pwstrDeviceId) 
{
	//Entra na sessão critica.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido.
	if (ObjetoValido(Evento_OnDeviceRemoved))
	{
		//Chama o evento
		Evento_OnDeviceRemoved(pwstrDeviceId);
	}
	else
	{
		//O evento não foi configurado.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna sucesso
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLN_IMMNotificationClient::OnDefaultDeviceChanged(
	_In_  EDataFlow flow,
	_In_  ERole role,
	_In_  LPCWSTR pwstrDefaultDeviceId) 
{
	//Entra na sessão critica.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido.
	if (ObjetoValido(Evento_OnDefaultDeviceChanged))
	{
		//Chama o evento
		Evento_OnDefaultDeviceChanged(flow, role, pwstrDefaultDeviceId);
	}
	else
	{
		//O evento não foi configurado.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna sucesso
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CLN_IMMNotificationClient::OnPropertyValueChanged(
	_In_  LPCWSTR pwstrDeviceId,
	_In_  const PROPERTYKEY key) 
{
	//Entra na sessão critica.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido.
	if (ObjetoValido(Evento_OnPropertyValueChanged))
	{
		//Chama o evento
		Evento_OnPropertyValueChanged(pwstrDeviceId, key);
	}
	else
	{
		//O evento não foi configurado.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna sucesso
	return S_OK;
}