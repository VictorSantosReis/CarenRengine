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
#include "../Nativas/CLN_IMFClockStateSink.h"



//Eventos chamados.

HRESULT __stdcall CLN_IMFClockStateSink::OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnClockStart))
	{
		//Chama o evento
		Evento_OnClockStart(hnsSystemTime, llClockStartOffset);
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return S_OK;
}

HRESULT __stdcall CLN_IMFClockStateSink::OnClockStop(MFTIME hnsSystemTime)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnClockStop))
	{
		//Chama o evento
		Evento_OnClockStop(hnsSystemTime);
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return S_OK;
}

HRESULT __stdcall CLN_IMFClockStateSink::OnClockPause(MFTIME hnsSystemTime)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnClockPause))
	{
		//Chama o evento
		Evento_OnClockPause(hnsSystemTime);
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return S_OK;
}

HRESULT __stdcall CLN_IMFClockStateSink::OnClockRestart(MFTIME hnsSystemTime)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnClockRestart))
	{
		//Chama o evento
		Evento_OnClockRestart(hnsSystemTime);
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return S_OK;
}

HRESULT __stdcall CLN_IMFClockStateSink::OnClockSetRate(MFTIME hnsSystemTime, float flRate)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnClockSetRate))
	{
		//Chama o evento
		Evento_OnClockSetRate(hnsSystemTime, flRate);
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return S_OK;
}