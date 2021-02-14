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
#include "../NativeClassForEvents/CLN_IMFAsyncCallback.h"


// Métodos da Interface IMFAsyncCallback


//Obtém as configurações deste sistema assincrono.
HRESULT __stdcall CLN_IMFAsyncCallback::GetParameters(DWORD* pdwFlags, DWORD* pdwQueue)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnGetParameters))
	{
		//Evento valido.

		//Chama o evento para notificar o cliente.
		Resultado = Evento_OnGetParameters(pdwFlags, pdwQueue);
	}
	else
	{
		//O evento não foi implementado.. Deixa continuar.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}

//Notifica o usuário sobre a conclusão de uma operação assincrona.
HRESULT __stdcall CLN_IMFAsyncCallback::Invoke(IMFAsyncResult* pAsyncResult)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnInvoke))
	{
		//Evento valido.

		//Chama o evento para notificar o cliente.
		Resultado = Evento_OnInvoke(pAsyncResult);
	}
	else
	{
		//O evento não foi implementado.. Deixa continuar.
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}
