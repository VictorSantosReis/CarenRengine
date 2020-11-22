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
typedef void(__stdcall* CLN_IMFMediaEngineNeedKeyNotify_EventoNativo_OnNeedKeys)(_In_reads_bytes_opt_(cb)  const BYTE*, _In_  DWORD);



/// <summary>
/// Classe respons�vel por implementar a interface (IMFMediaEngineNeedKeyNotify) que vai receber os eventos e encaminha para o usu�rio na classe gerenciada.
/// </summary>
class CLN_IMFMediaEngineNeedKeyNotify : public IMFMediaEngineNeedKeyNotify
{
    //Guarda a quantidade de refer�ncias.
    volatile long RefCount;

    //Sess�o critica de c�digo.
    CRITICAL_SECTION SessaoCritica;

public:
    //Inicializa��o da classe.
    CLN_IMFMediaEngineNeedKeyNotify() : RefCount(1)
    {
        //Inicia a sess�o critica.
        BOOL Resultado = InitializeCriticalSectionAndSpinCount(&SessaoCritica, 0x00000400);

        //Verifica o resultado
        if (Resultado)
        {

        }
    }

    //Destrui��o da classe.
    ~CLN_IMFMediaEngineNeedKeyNotify()
    {
        //Deleta a sess�o critica
        DeleteCriticalSection(&SessaoCritica);
    }

    //Cont�m todos os Eventos que seram chamados para notificar o usu�rio.
public:

    //Eventos nativos.
    CLN_IMFMediaEngineNeedKeyNotify_EventoNativo_OnNeedKeys Evento_OnNeedKeys = NULL;


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
        else if (__uuidof(IMFMediaEngineNeedKeyNotify) == guid)
        {
            AddRef();
            *pObj = (IMFMediaEngineNeedKeyNotify*)this;
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


    //M�todos da Interface IMFMediaEngineNeedKeyNotify
public:
    virtual void STDMETHODCALLTYPE NeedKey(
        _In_reads_bytes_opt_(cb)  const BYTE* initData,
        _In_  DWORD cb);
};