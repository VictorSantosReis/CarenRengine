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
typedef HRESULT(__stdcall* CLN_IMFCaptureEngineOnSampleCallback2_EventoNativo_OnSynchronizedEvent)(_In_  IMFMediaEvent*);
typedef HRESULT(__stdcall* CLN_IMFCaptureEngineOnSampleCallback2_EventoNativo_OnSample)(_In_opt_  IMFSample*);


/// <summary>
/// Classe respons�vel por implementar a interface (IMFCaptureEngineOnSampleCallback2) que vai receber eventos da interface IMFCaptureEngine.
/// </summary>
class CLN_IMFCaptureEngineOnSampleCallback2 : public IMFCaptureEngineOnSampleCallback2
{
    //Guarda a quantidade de refer�ncias.
    volatile long RefCount;

public:
    //Inicializa��o da classe.
    CLN_IMFCaptureEngineOnSampleCallback2() : RefCount(1)
    {

    }

    //Destrui��o da classe.
    ~CLN_IMFCaptureEngineOnSampleCallback2()
    {

    }

    //Cont�m todos os Eventos que seram chamados para notificar o usu�rio.
public:

    //Eventos nativos.
    CLN_IMFCaptureEngineOnSampleCallback2_EventoNativo_OnSynchronizedEvent Evento_OnSynchronizedEvent = NULL;
    CLN_IMFCaptureEngineOnSampleCallback2_EventoNativo_OnSample Evento_OnSample = NULL;

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
        else if (__uuidof(IMFCaptureEngineOnSampleCallback2) == guid)
        {
            AddRef();
            *pObj = (IMFCaptureEngineOnSampleCallback2*)this;
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


    //M�todos da Interface IMFCaptureEngineOnSampleCallback2 
public:
    virtual HRESULT STDMETHODCALLTYPE OnSynchronizedEvent(
        /* [annotation][in] */
        _In_  IMFMediaEvent* pEvent);

    //M�todos da Interface IMFCaptureEngineOnSampleCallback
public:
    virtual HRESULT STDMETHODCALLTYPE OnSample(
        /* [annotation][in] */
        _In_opt_  IMFSample* pSample);

};