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
#include "CLN_IMFSourceBufferNotify.h"

void __stdcall CLN_IMFSourceBufferNotify::OnUpdateStart(void)
{
    //Verifica se o evento foi implementado e chama.
    if (ObjetoValido(Evento_OnUpdateStart))
        Evento_OnUpdateStart();
}

void __stdcall CLN_IMFSourceBufferNotify::OnAbort(void)
{
    //Verifica se o evento foi implementado e chama.
    if (ObjetoValido(Evento_OnAbort))
        Evento_OnAbort();
}

void __stdcall CLN_IMFSourceBufferNotify::OnError(_In_ HRESULT hr)
{
    //Verifica se o evento foi implementado e chama.
    if (ObjetoValido(Evento_OnError))
        Evento_OnError(hr);
}

void __stdcall CLN_IMFSourceBufferNotify::OnUpdate(void)
{
    //Verifica se o evento foi implementado e chama.
    if (ObjetoValido(Evento_OnUpdate))
        Evento_OnUpdate();
}

void __stdcall CLN_IMFSourceBufferNotify::OnUpdateEnd(void)
{
    //Verifica se o evento foi implementado e chama.
    if (ObjetoValido(Evento_OnUpdateEnd))
        Evento_OnUpdateEnd();
}
