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
#include "CLN_IMFQualityManager.h"

HRESULT __stdcall CLN_IMFQualityManager::NotifyTopology(IMFTopology* pTopology)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_NotifyTopology))
		Resultado = Evento_NotifyTopology(pTopology);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFQualityManager::NotifyPresentationClock(IMFPresentationClock* pClock)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_NotifyPresentationClock))
		Resultado = Evento_NotifyPresentationClock(pClock);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFQualityManager::NotifyProcessInput(IMFTopologyNode* pNode, long lInputIndex, IMFSample* pSample)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_NotifyProcessInput))
		Resultado = Evento_NotifyProcessInput(pNode, lInputIndex, pSample);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFQualityManager::NotifyProcessOutput(IMFTopologyNode* pNode, long lOutputIndex, IMFSample* pSample)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_NotifyProcessOutput))
		Resultado = Evento_NotifyProcessOutput(pNode, lOutputIndex, pSample);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFQualityManager::NotifyQualityEvent(IUnknown* pObject, IMFMediaEvent* pEvent)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_NotifyQualityEvent))
		Resultado = Evento_NotifyQualityEvent(pObject, pEvent);
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}

HRESULT __stdcall CLN_IMFQualityManager::Shutdown(void)
{
	//Variavel que vai retornar o resultado.
	HRESULT Resultado = E_FAIL;

	//Verifica se o usuário cadastrou o evento.
	if (ObjetoValido(Evento_Shutdown))
		Resultado = Evento_Shutdown();
	else
		Resultado = E_NOTIMPL;

	//Retorna o resultado.
	return Resultado;
}
