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
#include "CLN_IMFNetResourceFilter.h"

HRESULT __stdcall CLN_IMFNetResourceFilter::OnRedirect(_In_ LPCWSTR pszUrl, _Out_ VARIANT_BOOL* pvbCancel)
{
    //Resultado geral.
    HRESULT Resultado = E_FAIL;

    //Verifica se o evento é valido
    if (ObjetoValido(Evento_OnRedirect))
    {
       //Chama o evento
        Resultado = Evento_OnRedirect(pszUrl, pvbCancel);
    }
    else
    {
        //Não implementado.
        Resultado = E_NOTIMPL;
    }

    //Retorna o resultado
    return Resultado;
}

HRESULT __stdcall CLN_IMFNetResourceFilter::OnSendingRequest(_In_ LPCWSTR pszUrl)
{
    //Resultado geral.
    HRESULT Resultado = E_FAIL;

    //Verifica se o evento é valido
    if (ObjetoValido(Evento_OnSendingRequest))
    {
        //Chama o evento
        Resultado = Evento_OnSendingRequest(pszUrl);
    }
    else
    {
        //Não implementado.
        Resultado = E_NOTIMPL;
    }

    //Retorna o resultado
    return Resultado;
}
