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

//
// Métodos da Interface IMFAsyncCallback
//


//Obtém as configurações deste sistema assincrono.
HRESULT __stdcall CLN_IMFAsyncCallback::GetParameters(DWORD* pdwFlags, DWORD* pdwQueue)
{
	//Entra na sessão critica de codígo.
	EnterCriticalSection(&SessaoCritica);

	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_NOTIMPL;

	//Variavel que vai conter se o evento está implementado ou não.
	//Se sim, o variavel retorna o valor 1, se não, retorna 0.
	int ResultadoGetParameters = 0;

	//Verifica se o evento é valido
	if (ObjetoValido(Evento_OnGetParameters))
	{
		//Evento valido.

		//Chama o método para notificar o usuário que 
		ResultadoGetParameters = Evento_OnGetParameters();

		//Verifica se o usuário implementou o evento.
		if (ResultadoGetParameters == 1)
		{
			//O usuário chamou o método (SetParameters) e definiu as configurações.

			//Define os valores nos parametros de saida.
			*pdwFlags = GetParameters_dwFlags;
			*pdwQueue = GetParameters_pdwQueue;

			//Define sucesso na operação.
			Resultado = S_OK;
		}
		else
		{
			//Este método não foi implementado pelo usuário.
			Resultado = E_NOTIMPL;
		}
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
		//Chama o evento para notificar a classe gerenciada base.
		Evento_OnInvoke(pAsyncResult);

		//Define sucesso
		Resultado = S_OK;
	}
	else
	{
		Resultado = E_NOTIMPL;
	}

	//Sai da sessão critica.
	LeaveCriticalSection(&SessaoCritica);

	//Retorna o resultado.
	return Resultado;
}



//
// Método auxiliar para o método(GetParameters) da interface IMFAsyncCallback
//

//Método responsável por definir as configurações do sistema Assincrono para ser retornado pelo método (GetParameters)
void CLN_IMFAsyncCallback::SetParameters(DWORD dwFlags, DWORD dwQueue)
{
	//Define os valores.
	GetParameters_dwFlags = dwFlags;
	GetParameters_pdwQueue = dwQueue;
}
