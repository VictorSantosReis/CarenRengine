﻿/*
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
typedef HRESULT(__stdcall* CLN_IMFNetResourceFilter_EventoNativo_OnRedirect)(LPCWSTR, VARIANT_BOOL*);
typedef HRESULT(__stdcall* CLN_IMFNetResourceFilter_EventoNativo_OnSendingRequest)(LPCWSTR);

/// <summary>
/// Classe responsável por implementar a interface nativa (IMFNetResourceFilter) para receber e enviar os eventos para a classe gerenciada.
/// </summary>
class CLN_IMFNetResourceFilter : public IMFNetResourceFilter
{
	//Guarda a quantidade de referências.
	volatile long RefCount;

public:
	//Inicialização da classe.
	CLN_IMFNetResourceFilter() : RefCount(1)
	{
	}

	~CLN_IMFNetResourceFilter()
	{

	}

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
		else if (guid == IID_IMFNetResourceFilter)
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


	//Contém todos os delegates que seram chamados para notificar o usuário.
public:
	CLN_IMFNetResourceFilter_EventoNativo_OnRedirect Evento_OnRedirect = NULL;
	CLN_IMFNetResourceFilter_EventoNativo_OnSendingRequest Evento_OnSendingRequest = NULL;


	//Métodos da interface (IMFNetResourceFilter).
public:
	virtual HRESULT STDMETHODCALLTYPE OnRedirect(
		_In_  LPCWSTR pszUrl,
		_Out_  VARIANT_BOOL* pvbCancel);

	virtual HRESULT STDMETHODCALLTYPE OnSendingRequest(
		_In_  LPCWSTR pszUrl);

};

