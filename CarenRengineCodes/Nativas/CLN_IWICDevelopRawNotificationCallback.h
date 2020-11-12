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
/// Classe respons�vel por receber os eventos nativos da interface IWICDevelopRawNotificationCallback e chamar um Callback para ser 
/// notificado a classe gerenciada e encaminhada para o usu�rio.
/// </summary>
class CLN_IWICDevelopRawNotificationCallback : public IWICDevelopRawNotificationCallback
{
	//Guarda a quantidade de refer�ncias.
	volatile long RefCount;

	//Sess�o critica de c�digo.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicializa��o da classe.
	CLN_IWICDevelopRawNotificationCallback() : RefCount(1)
	{
		//Inicia a sess�o critica.
		BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IWICDevelopRawNotificationCallback()
	{
		//Deleta a sess�o critica
		DeleteCriticalSection(&SessaoCritica);
	}


	//M�todos da Interface IUnknown.
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

	//Adiciona uma refer�ncia a classe.
	STDMETHODIMP_(ULONG) AddRef()
	{
		//Incrementa a quantidade de refer�ncias.
		return InterlockedIncrement(&RefCount);
	}

	//Libera uma refer�ncia a classe.
	STDMETHODIMP_(ULONG) Release()
	{
		//Desecrementa a quantidade de refer�ncias e verifica.
		ULONG result = InterlockedDecrement(&RefCount);
		if (result == 0) delete this;
		return result;
	}


	//Cont�m todos os delegates que seram chamados para notificar o usu�rio.
public:
	CLN_IWICDevelopRawNotificationCallback_EventoNativo_Notify Evento_OnNotify = NULL;


	//M�todos da interface (IWICDevelopRawNotificationCallback).
public:
	virtual HRESULT STDMETHODCALLTYPE Notify(UINT NotificationMask);
};

