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
typedef void(__stdcall* CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyAdded)(void);
typedef void(__stdcall* CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyError)(_In_  USHORT, _In_  DWORD);
typedef void(__stdcall* CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyMessage)(_In_opt_  BSTR, _In_reads_bytes_(cb)  const BYTE*, _In_  DWORD);

/// <summary>
/// Classe respons�vel por implementar a interface nativa (IMFMediaKeySessionNotify) que vai receber eventos de notifica��o para serem enviados ao usu�rio.
/// </summary>
class CLN_IMFMediaKeySessionNotify : public IMFMediaKeySessionNotify
{
	//Guarda a quantidade de refer�ncias.
	volatile long RefCount;

	//Sess�o critica de c�digo.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicializa��o da classe.
	CLN_IMFMediaKeySessionNotify() : RefCount(1)
	{
		//Inicia a sess�o critica.
		InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IMFMediaKeySessionNotify()
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
		else if (guid == IID_IMFMediaKeySessionNotify)
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
	CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyAdded Evento_OnKeyAdded = NULL;
	CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyError Evento_OnKeyError = NULL;
	CLN_IMFMediaKeySessionNotify_EventoNativo_OnKeyMessage Evento_OnKeyMessage = NULL;


	//M�todos da interface (IMFNetResourceFilter).
public:
	virtual void STDMETHODCALLTYPE KeyMessage(
		_In_opt_  BSTR destinationURL,
		_In_reads_bytes_(cb)  const BYTE* message,
		_In_  DWORD cb);

	virtual void STDMETHODCALLTYPE KeyAdded(void);

	virtual void STDMETHODCALLTYPE KeyError(
		_In_  USHORT code,
		_In_  DWORD systemCode);

};

