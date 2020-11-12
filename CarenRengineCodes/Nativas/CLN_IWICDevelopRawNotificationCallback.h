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
typedef HRESULT(__stdcall* CLN_IWICDevelopRawNotificationCallback_EventoNativo_Notify)(UINT);



/// <summary>
/// Classe responsável por receber os eventos nativos da interface IWICDevelopRawNotificationCallback e chamar um Callback para ser 
/// notificado a classe gerenciada e encaminhada para o usuário.
/// </summary>
class CLN_IWICDevelopRawNotificationCallback : public IWICDevelopRawNotificationCallback
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IWICDevelopRawNotificationCallback() : RefCount(1)
	{
		//Inicia a sessão critica.
		BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IWICDevelopRawNotificationCallback()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}


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
		else if (guid == IID_IWICDevelopRawNotificationCallback)
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


	//Contém todos os delegates que seram chamados para notificar o usuário.
public:
	CLN_IWICDevelopRawNotificationCallback_EventoNativo_Notify Evento_OnNotify = NULL;


	//Métodos da interface (IWICDevelopRawNotificationCallback).
public:
	virtual HRESULT STDMETHODCALLTYPE Notify(UINT NotificationMask);
};

