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
#include "..\SDK_Base.h"

//typedef dos delegates responsáveis pelo eventos registrados pela classe nativa.

typedef void(__stdcall* CLN_IMFSinkWriterCallback_EventoNativo_OnFinalize)(HRESULT);
typedef void(__stdcall* CLN_IMFSinkWriterCallback_EventoNativo_OnMarker)(DWORD, LPVOID);

//Classe responsável por invocar os eventos notificando os eventos gerados pelo SinkWriter que são enviados pela interface IMFSinkWriterCallback.
class CLN_IMFSinkWriterCallback : public IMFSinkWriterCallback
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IMFSinkWriterCallback()
	{
		//Inicia a sessão critica.
		BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IMFSinkWriterCallback()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}

	//Ponteiro de Eventos.
public:
	CLN_IMFSinkWriterCallback_EventoNativo_OnFinalize Evento_OnFinalize = NULL;
	CLN_IMFSinkWriterCallback_EventoNativo_OnMarker Evento_OnMarker = NULL;


	//Métodos da Interface IUnknown.
public:
	//Procura uma determinada interface nessa classe.
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
		else if (guid == IID_IMFSinkWriterCallback)
		{
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
		return InterlockedIncrement(&RefCount);
	}

	//Libera uma referência a classe.
	STDMETHODIMP_(ULONG) Release()
	{
		ULONG result = InterlockedDecrement(&RefCount);
		if (result == 0) delete this;
		return result;
	}



	//Métodos da interface IMFSinkWriterCallback
public:
	//Retorna o resultado do método (Finalize)
	HRESULT STDMETHODCALLTYPE OnFinalize(_In_  HRESULT hrStatus);

	//Retorna o resultado do método (PlaceMarker)
	HRESULT STDMETHODCALLTYPE OnMarker(_In_  DWORD dwStreamIndex, _In_  LPVOID pvContext);
};

