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
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_NotifyTopology)(IMFTopology*);
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_NotifyPresentationClock)(IMFPresentationClock*);
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_NotifyProcessInput)(IMFTopologyNode*, long, IMFSample*);
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_NotifyProcessOutput)(IMFTopologyNode*, long, IMFSample*);
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_NotifyQualityEvent)(IUnknown*, IMFMediaEvent*);
typedef HRESULT(__stdcall* CLN_IMFQualityManager_EventoNativo_Shutdown)(void);


/// <summary>
/// Classe responsável por implementar a interface (IMFQualityManager) para gerenciar os eventos de qualidade.
/// </summary>
class CLN_IMFQualityManager: public IMFQualityManager
{
    //Guarda a quantidade de referências.
    volatile long RefCount;

public:
    //Inicialização da classe.
    CLN_IMFQualityManager() : RefCount(1)
    {

    }

    //Destruição da classe.
    ~CLN_IMFQualityManager()
    {

    }

    //Contém todos os Eventos que seram chamados para notificar o usuário.
public:

    //Eventos nativos.
    CLN_IMFQualityManager_EventoNativo_NotifyTopology Evento_NotifyTopology = NULL;
    CLN_IMFQualityManager_EventoNativo_NotifyPresentationClock Evento_NotifyPresentationClock = NULL;
    CLN_IMFQualityManager_EventoNativo_NotifyProcessInput Evento_NotifyProcessInput = NULL;
    CLN_IMFQualityManager_EventoNativo_NotifyProcessInput Evento_NotifyProcessOutput = NULL;
    CLN_IMFQualityManager_EventoNativo_NotifyQualityEvent Evento_NotifyQualityEvent = NULL;
    CLN_IMFQualityManager_EventoNativo_Shutdown Evento_Shutdown = NULL;

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
        else if (__uuidof(IMFQualityManager) == guid)
        {
            AddRef();
            *pObj = (IMFQualityManager*)this;
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


    //Métodos da Interface IMFQualityManager 
public:
    virtual HRESULT STDMETHODCALLTYPE NotifyTopology(
        /* [in] */ IMFTopology* pTopology);

    virtual HRESULT STDMETHODCALLTYPE NotifyPresentationClock(
        /* [in] */ IMFPresentationClock* pClock);

    virtual HRESULT STDMETHODCALLTYPE NotifyProcessInput(
        /* [in] */ IMFTopologyNode* pNode,
        /* [in] */ long lInputIndex,
        /* [in] */ IMFSample* pSample);

    virtual HRESULT STDMETHODCALLTYPE NotifyProcessOutput(
        /* [in] */ IMFTopologyNode* pNode,
        /* [in] */ long lOutputIndex,
        /* [in] */ IMFSample* pSample);

    virtual HRESULT STDMETHODCALLTYPE NotifyQualityEvent(
        /* [in] */ IUnknown* pObject,
        /* [in] */ IMFMediaEvent* pEvent);

    virtual HRESULT STDMETHODCALLTYPE Shutdown(void);
};