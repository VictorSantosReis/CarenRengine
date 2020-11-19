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
#include "CLN_IMFNetProxyLocatorFactory.h"

HRESULT __stdcall CLN_IMFNetProxyLocatorFactory::CreateProxyLocator(LPCWSTR pszProtocol, _Outptr_  IMFNetProxyLocator** ppProxyLocator)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o evento foi criado pelo usu�rio
	if (ObjetoValido(Evento_OnCreateProxyLocator))
	{
		//Chama o evento que vai notificar o usu�rio para criar o ProxyLocator.
		Resultado = Evento_OnCreateProxyLocator(pszProtocol, ppProxyLocator);
	}
	else
	{
		//Define que o m�todo n�o foi implementado pelo usu�rio.
		Resultado = E_NOTIMPL;
	}

	//Retorna o resultado.
	return Resultado;
}
