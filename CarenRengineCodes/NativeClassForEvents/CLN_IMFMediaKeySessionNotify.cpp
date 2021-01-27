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
#include "../pch.h"
#include "CLN_IMFMediaKeySessionNotify.h"

void STDMETHODCALLTYPE CLN_IMFMediaKeySessionNotify::KeyMessage(BSTR destinationURL, const BYTE* message, DWORD cb)
{
	//Entra na sessão critica do código.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento foi impelementado pelo usuário e chama para notificar na classe gerenciada.
	if (ObjetoValido(Evento_OnKeyMessage))
		Evento_OnKeyMessage(destinationURL, message, cb);

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);
}

void STDMETHODCALLTYPE CLN_IMFMediaKeySessionNotify::KeyAdded(void)
{
	//Verifica se o evento foi impelementado pelo usuário e chama para notificar na classe gerenciada.
	if (ObjetoValido(Evento_OnKeyAdded))
		Evento_OnKeyAdded();

}

void STDMETHODCALLTYPE CLN_IMFMediaKeySessionNotify::KeyError(USHORT code, DWORD systemCode)
{
	//Verifica se o evento foi impelementado pelo usuário e chama para notificar na classe gerenciada.
	if (ObjetoValido(Evento_OnKeyError))
		Evento_OnKeyError(code, systemCode);
}
