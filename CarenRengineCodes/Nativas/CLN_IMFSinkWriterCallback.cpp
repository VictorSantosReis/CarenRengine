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


#include "..\pch.h"
#include "..\Nativas\CLN_IMFSinkWriterCallback.h"

HRESULT __stdcall CLN_IMFSinkWriterCallback::OnFinalize(HRESULT hrStatus)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado do método.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento foi configurado
	if (Evento_OnFinalize != NULL)
	{
		//Invoca o evento.
		Evento_OnFinalize(hrStatus);

		//Define suecesso
		Resultado = S_OK;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFSinkWriterCallback::OnMarker(DWORD dwStreamIndex, LPVOID pvContext)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado do método.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento foi configurado
	if (Evento_OnMarker != NULL)
	{
		//Invoca o evento.
		Evento_OnMarker(dwStreamIndex, pvContext);

		//Define suecesso
		Resultado = S_OK;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}
