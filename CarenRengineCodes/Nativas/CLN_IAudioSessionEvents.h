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
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnDisplayNameChanged)(LPCWSTR, LPCGUID);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnIconPathChanged)(LPCWSTR, LPCGUID);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnSimpleVolumeChanged)(float, BOOL, LPCGUID);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnChannelVolumeChanged)(DWORD, float[], DWORD, LPCGUID);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnGroupingParamChanged)(LPCGUID, LPCGUID);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnStateChanged)(AudioSessionState);
typedef int(__stdcall* CLN_IAudioSessionEvents_EventoNativo_OnSessionDisconnected)(AudioSessionDisconnectReason);

//Classe responsável por notificar o usuário em classe gerenciada de alterações na sessão de áudio.
class CLN_IAudioSessionEvents : public IAudioSessionEvents
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

public:
	//Inicialização da classe.
	CLN_IAudioSessionEvents() : RefCount(1)
	{
	}

	//Destruição da classe.
	~CLN_IAudioSessionEvents()
	{
	}

	//Contém todos os Eventos que seram chamados para notificar o usuário.
public:

	//Eventos nativos.
	CLN_IAudioSessionEvents_EventoNativo_OnDisplayNameChanged Evento_OnDisplayNameChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnIconPathChanged Evento_OnIconPathChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnSimpleVolumeChanged Evento_OnSimpleVolumeChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnChannelVolumeChanged Evento_OnChannelVolumeChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnGroupingParamChanged Evento_OnGroupingParamChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnStateChanged Evento_OnStateChanged = NULL;
	CLN_IAudioSessionEvents_EventoNativo_OnSessionDisconnected Evento_OnSessionDisconnected = NULL;


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
		else if (__uuidof(IAudioSessionEvents) == guid)
		{
			AddRef();
			*pObj = (IAudioSessionEvents*)this;
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


	//Métodos da Interface IAudioSessionEvents
public:
	virtual HRESULT STDMETHODCALLTYPE OnDisplayNameChanged(_In_  LPCWSTR NewDisplayName, LPCGUID EventContext);

	virtual HRESULT STDMETHODCALLTYPE OnIconPathChanged(_In_  LPCWSTR NewIconPath, LPCGUID EventContext);

	virtual HRESULT STDMETHODCALLTYPE OnSimpleVolumeChanged(_In_  float NewVolume, _In_  BOOL NewMute, LPCGUID EventContext);

	virtual HRESULT STDMETHODCALLTYPE OnChannelVolumeChanged(_In_  DWORD ChannelCount, _In_reads_(ChannelCount)  float NewChannelVolumeArray[], _In_  DWORD ChangedChannel, LPCGUID EventContext);

	virtual HRESULT STDMETHODCALLTYPE OnGroupingParamChanged(_In_  LPCGUID NewGroupingParam, LPCGUID EventContext);

	virtual HRESULT STDMETHODCALLTYPE OnStateChanged(_In_  AudioSessionState NewState);

	virtual HRESULT STDMETHODCALLTYPE OnSessionDisconnected(_In_  AudioSessionDisconnectReason DisconnectReason);
};

