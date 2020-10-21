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
#include "../Caren/Caren.h"

//CLN -> Classe Nativa.

using namespace CarenRengine::SDKBase::Interfaces;

//Typedefs dos eventos gerados pela classe.

typedef void(__stdcall* CLN_IMFSourceReaderCallback_EventoNativo_OnReadSample)(HRESULT, DWORD, DWORD, LONGLONG, IMFSample*);
typedef void(__stdcall* CLN_IMFSourceReaderCallback_EventoNativo_OnEvent)(DWORD, IMFMediaEvent*);
typedef void(__stdcall* CLN_IMFSourceReaderCallback_EventoNativo_OnFlush)(DWORD);

//Classe responsável por receber o eventos gerados da interface IMFSourceReaderCallback e encaminhar para a classe gerenciada para notificar o usuário.
class CLN_IMFSourceReaderCallback : public IMFSourceReaderCallback
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

	//Sessão critica de código.
	CRITICAL_SECTION SessaoCritica;

public:
	//Inicialização da classe.
	CLN_IMFSourceReaderCallback()
	{
		//Inicia a sessão critica.
		InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);
	}

	~CLN_IMFSourceReaderCallback()
	{
		//Deleta a sessão critica
		DeleteCriticalSection(&SessaoCritica);
	}

	//Ponteiro de Eventos.
public:
	CLN_IMFSourceReaderCallback_EventoNativo_OnReadSample Evento_OnReadSample = NULL;
	CLN_IMFSourceReaderCallback_EventoNativo_OnEvent Evento_OnEvent = NULL;
	CLN_IMFSourceReaderCallback_EventoNativo_OnFlush Evento_OnFlush = NULL;


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
		else if (guid == IID_IMFSourceReaderCallback)
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
	


	//Métodos da interface IMFSourceReaderCallback
public:
	STDMETHODIMP_(HRESULT) OnReadSample(HRESULT Param_HResultStatus, DWORD Param_FluxoID, DWORD Param_FluxoFlgs, LONGLONG Param_TimeSpanAmostra, IMFSample* Param_AmostraMidia)
	{	
		//Entra na sessão critica de codígo.
		EnterCriticalSection(&SessaoCritica);

		//Verifica.
		if (ObjetoValido(Evento_OnReadSample))
		{
			//Chama o evento.
			Evento_OnReadSample(Param_HResultStatus, Param_FluxoID, Param_FluxoFlgs, Param_TimeSpanAmostra, Param_AmostraMidia);
		}

		//Sai da sessão critica.
		LeaveCriticalSection(&SessaoCritica);

		//Retorna o resultado.
		return S_OK;
	}
	STDMETHODIMP_(HRESULT) OnEvent(DWORD Param_FluxoID, IMFMediaEvent* Param_EventoInterface)
	{
		//Entra na sessão critica de codígo.
		EnterCriticalSection(&SessaoCritica);

		//Verifica.
		if (ObjetoValido(Evento_OnEvent))
		{
			//Chama o evento.
			Evento_OnEvent(Param_FluxoID, Param_EventoInterface);
		}

		//Sai da sessão critica.
		LeaveCriticalSection(&SessaoCritica);

		//Retorna o resultado.
		return S_OK;
	}
	STDMETHODIMP_(HRESULT) OnFlush(DWORD Param_FluxoID)
	{
		//Entra na sessão critica de codígo.
		EnterCriticalSection(&SessaoCritica);

		//Verifica.
		if (ObjetoValido(Evento_OnFlush))
		{
			//Chama o evento.
			Evento_OnFlush(Param_FluxoID);
		}

		//Sai da sessão critica.
		LeaveCriticalSection(&SessaoCritica);
	
		//Retorna o resultado.
		return S_OK;
	}
};

