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
#include "../Nativas/CLN_IAudioSessionEvents.h"

//SEGUNDO A DOCUMENTACAO - OS MÉTODOS NAO DEVEM USAR SECÕES CRITICAS DE CÓDIGOS OU QUALQUER FUNCAO QUE PRENDA(THREAD-SAFE) OS MÉTODOS.

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnDisplayNameChanged(_In_  LPCWSTR NewDisplayName, LPCGUID EventContext)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnDisplayNameChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnDisplayNameChanged(NewDisplayName, EventContext);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnIconPathChanged(_In_  LPCWSTR NewIconPath, LPCGUID EventContext)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnIconPathChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnIconPathChanged(NewIconPath, EventContext);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnSimpleVolumeChanged(_In_  float NewVolume, _In_  BOOL NewMute, LPCGUID EventContext)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnSimpleVolumeChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnSimpleVolumeChanged(NewVolume, NewMute, EventContext);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnChannelVolumeChanged(_In_  DWORD ChannelCount, _In_reads_(ChannelCount)  float NewChannelVolumeArray[], _In_  DWORD ChangedChannel, LPCGUID EventContext)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnChannelVolumeChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnChannelVolumeChanged(ChannelCount, NewChannelVolumeArray, ChangedChannel, EventContext);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnGroupingParamChanged(_In_  LPCGUID NewGroupingParam, LPCGUID EventContext)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnGroupingParamChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnGroupingParamChanged(NewGroupingParam, EventContext);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnStateChanged(_In_  AudioSessionState NewState)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnStateChanged))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnStateChanged(NewState);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}

HRESULT STDMETHODCALLTYPE CLN_IAudioSessionEvents::OnSessionDisconnected(_In_  AudioSessionDisconnectReason DisconnectReason)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnSessionDisconnected))
	{
		//Evento valido.

		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnSessionDisconnected(DisconnectReason);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		//Não implementado.
		Resultado = E_NOTIMPL;
	}

	//Retorna
	return Resultado;
}