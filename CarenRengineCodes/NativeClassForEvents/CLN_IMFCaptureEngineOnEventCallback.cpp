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
#include "CLN_IMFCaptureEngineOnEventCallback.h"

HRESULT __stdcall CLN_IMFCaptureEngineOnEventCallback::OnEvent(IMFMediaEvent* pEvent)
{
	//Entra na sessao critica de código.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_OnEvent))
		Resultado = Evento_OnEvent(pEvent);
	else
		Resultado = E_NOTIMPL;

	//Sai da sessão critica de código.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}
