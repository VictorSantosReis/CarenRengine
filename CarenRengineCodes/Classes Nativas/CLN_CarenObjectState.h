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
#include "../Header.h"
#include "../SDK_Utilidades.h"
#include <initguid.h>

//NA -> NATIVE

#ifndef __INACarenObjectState_INTERFACE_DEFINED__
#define __INACarenObjectState_INTERFACE_DEFINED__

//DECLARAÇÃO DO IID DA INTERFACE.

// {F26DDE8E-4E7C-416D-A05B-0B81CB9B17BE}
DEFINE_GUID(IID_INACarenObjectState,
	0xf26dde8e, 0x4e7c, 0x416d, 0xa0, 0x5b, 0xb, 0x81, 0xcb, 0x9b, 0x17, 0xbe);


//DECLARAÇÃO DA INTERFACE

MIDL_INTERFACE("F26DDE8E-4E7C-416D-A05B-0B81CB9B17BE")
INACarenObjectState : public IUnknown
{
public:
	/// <summary>
	/// Retorna o nome do objeto de estado atual se válido.
	/// </summary>
	/// <param name="Param_Out_NameObjet">Retorna o nome do objeto atual. Chame o método (DeletarStringAllocatedSafe) quando não for mais usar os dados.</param>
	/// <returns></returns>
	virtual HRESULT STDMETHODCALLTYPE GetName(_Out_ PWSTR* Param_Out_NameObjet) = 0;

	/// <summary>
	/// Retorna a largura do nome do objeto de estado atual.
	/// </summary>
	/// <param name="Param_Out_Size">Retorna a largura da string.</param>
	/// <returns></returns>
	virtual HRESULT STDMETHODCALLTYPE GetLenghtName(_Out_ UINT32* Param_Out_Size) = 0;

	/// <summary>
	/// Define um novo nome para o objeto de estado atual.
	/// </summary>
	/// <param name="Param_NameObject">O novo nome do objeto.</param>
	/// <param name="Param_SizeName">A largura do novo nome.</param>
	/// <returns></returns>
	virtual HRESULT STDMETHODCALLTYPE SetName(_In_ const PWSTR& Param_NameObject, _In_ UINT32 Param_SizeName) = 0;
};
#endif

/// <summary>
/// Classe nativa responsável por representar um (Objeto Estado) utilizado pela classe gerenciada CarenObjectState.
/// </summary>
class CLN_CarenObjectState : public INACarenObjectState
{
	//Guarda a quantidade de referências.
	volatile long RefCount;


private:
	//Variavel global que contém o nome do objeto de estado atual.
	PWSTR vi_Global_Name = Nulo;

	//Variavel global que contém a largura do nome do objeto de estado atual.
	UINT32 vi_Global_SizeName = 0;

	//Construtor & Destruidor
public:
	/// <summary>
	/// Inicializa a classe do objeto de estado sem nenhum nome associado.
	/// </summary>
	CLN_CarenObjectState() : 
		RefCount(1), 
		vi_Global_Name(NULL), 
		vi_Global_SizeName(0)
	{
		//Inicializa a classe sem nenhum dado.
	}

	/// <summary>
	/// Inicializa a classe e permite passar o nome do objeto atual.
	/// </summary>
	/// <param name="Param_NameObject">Uma constante para o nome do objeto atual. Se Param_Size for igual a 0(ZERO), esse construtor se comporta como o default
	/// e nenhum dado será vinculado a classe.</param>
	/// <param name="Param_Size">A largura da string no parametro (Param_NameObject).</param>
	CLN_CarenObjectState(const PWSTR& Param_NameObject, UINT32 Param_Size) :
		RefCount(1)
	{
		//Verifica se o tamanho é valido
		if (Param_Size > 0)
		{
			//Define na variavel global da classe o nome.
			vi_Global_Name = Param_NameObject;

			//Define o Size.
			vi_Global_SizeName = Param_Size + 1;
		}
	}

	//Destruição da classe.
	~CLN_CarenObjectState()
	{
		//Verifica se o nome nativo do objeto é valido e libera a memória.
		DeletarStringAllocatedSafe(&vi_Global_Name);

		//Limpa.
		vi_Global_Name = Nulo;

		//Zera o size.
		vi_Global_SizeName = 0;
	}


	//Métodos da interface base IUnknown.
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
		else if (guid == IID_INACarenObjectState)
		{
			AddRef();
			*pObj = static_cast<INACarenObjectState*>(this);
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

	//Métodos da interface ICarenObjectState
public:
	STDMETHODIMP GetName(_Out_ PWSTR* Param_Out_NameObjet);

	STDMETHODIMP GetLenghtName(_Out_ UINT32* Param_Out_Size);

	STDMETHODIMP SetName(_In_ const PWSTR& Param_NameObject, _In_ UINT32 Param_SizeName);
};

