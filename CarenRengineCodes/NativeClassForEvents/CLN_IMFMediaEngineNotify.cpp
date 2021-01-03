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
#include "../pch.h"
#include "../NativeClassForEvents/CLN_IMFMediaEngineNotify.h"

HRESULT __stdcall CLN_IMFMediaEngineNotify::EventNotify(DWORD evento, DWORD_PTR param1, DWORD param2)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o evento é valido e chama
	if (ObjetoValido(Evento_OnEventNotify))
		Resultado = Evento_OnEventNotify(evento, param1, param2);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}
