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
typedef HRESULT(__stdcall* CLN_IMFNetProxyLocatorFactory_EventoNativo_OnCreateProxyLocator)(LPCWSTR, _Outptr_ IMFNetProxyLocator**);

/// <summary>
/// Classe respons�vel por implementar a interface nativa (IMFNetProxyLocatorFactory) possibilitando o usu�rio receber a chamada do m�todo (CreateProxyLocator) para poder criar
/// e configurar seu proxy personalizado.
/// </summary>
class CLN_IMFNetProxyLocatorFactory : public IMFNetProxyLocatorFactory
{
	//Guarda a quantidade de refer�ncias.
	volatile long RefCount;

public:
	//Inicializa��o da classe.
	CLN_IMFNetProxyLocatorFactory() : RefCount(1)
	{
	}

	~CLN_IMFNetProxyLocatorFactory()
	{

	}

	//M�todos da Interface IUnknown.
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
		else if (guid == IID_IMFNetProxyLocatorFactory)
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

	//Adiciona uma refer�ncia a classe.
	STDMETHODIMP_(ULONG) AddRef()
	{
		//Incrementa a quantidade de refer�ncias.
		return InterlockedIncrement(&RefCount);
	}

	//Libera uma refer�ncia a classe.
	STDMETHODIMP_(ULONG) Release()
	{
		//Desecrementa a quantidade de refer�ncias e verifica.
		ULONG result = InterlockedDecrement(&RefCount);
		if (result == 0) delete this;
		return result;
	}


	//Cont�m todos os delegates que seram chamados para notificar o usu�rio.
public:
	CLN_IMFNetProxyLocatorFactory_EventoNativo_OnCreateProxyLocator Evento_OnCreateProxyLocator = NULL;


	//M�todos da interface (IMFNetResourceFilter).
public:
	virtual HRESULT STDMETHODCALLTYPE CreateProxyLocator(
		LPCWSTR pszProtocol,
		_Outptr_  IMFNetProxyLocator** ppProxyLocator);

};

