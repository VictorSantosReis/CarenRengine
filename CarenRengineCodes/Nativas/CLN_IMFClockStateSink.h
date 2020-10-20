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


//Typedefs dos delegates que seram expostos por essa classe para a notificação.

typedef void(__stdcall* CLN_IMFClockStateSink_EventoNativo_OnClockStart)(MFTIME, LONGLONG);
typedef void(__stdcall* CLN_IMFClockStateSink_EventoNativo_OnClockStop)(MFTIME);
typedef void(__stdcall* CLN_IMFClockStateSink_EventoNativo_OnClockPause)(MFTIME);
typedef void(__stdcall* CLN_IMFClockStateSink_EventoNativo_OnClockRestart)(MFTIME);
typedef void(__stdcall* CLN_IMFClockStateSink_EventoNativo_OnClockSetRate)(MFTIME, float);


//Classe nativa responsável por chamar os eventos gerados pela interface nativa (IMFClockStateSink)
class CLN_IMFClockStateSink : public IMFClockStateSink
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IMFClockStateSink()
	{
		//Inicia a sessão critica.
		BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IMFClockStateSink()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}

	//Contém todos os delegates que seram chamados para notificar alterações no relogio de apresentação.
public:
	CLN_IMFClockStateSink_EventoNativo_OnClockStart Evento_OnClockStart = NULL;
	CLN_IMFClockStateSink_EventoNativo_OnClockStop Evento_OnClockStop = NULL;
	CLN_IMFClockStateSink_EventoNativo_OnClockPause  Evento_OnClockPause = NULL;
	CLN_IMFClockStateSink_EventoNativo_OnClockRestart Evento_OnClockRestart = NULL;
	CLN_IMFClockStateSink_EventoNativo_OnClockSetRate Evento_OnClockSetRate = NULL;

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
		else if (guid == IID_IMFClockStateSink)
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



	//Métodos da interface (IMFClockStateSink).
public:
	virtual HRESULT STDMETHODCALLTYPE OnClockStart(MFTIME hnsSystemTime,LONGLONG llClockStartOffset);

	virtual HRESULT STDMETHODCALLTYPE OnClockStop(MFTIME hnsSystemTime);

	virtual HRESULT STDMETHODCALLTYPE OnClockPause(MFTIME hnsSystemTime);

	virtual HRESULT STDMETHODCALLTYPE OnClockRestart(MFTIME hnsSystemTime);

	virtual HRESULT STDMETHODCALLTYPE OnClockSetRate(MFTIME hnsSystemTime,float flRate);
};

