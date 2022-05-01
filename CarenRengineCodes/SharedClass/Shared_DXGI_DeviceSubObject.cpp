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
#include "Shared_DXGI.h"


//MÉTODOS DA CLASSE COMPARTILHADA ()


// Métodos da interface proprietária(ICarenDXGIDeviceSubObject)

/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult Shared_DXGIDeviceSubObject::GetDevice(
	IDXGIDeviceSubObject* Param_MyPointerWork, 
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = GUID_NULL;
	LPVOID pInterfaceRequest = NULL;

	//Obtém o Guid
	RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);

	//Verifica se o guid não é invalido
	if (RiidInterface == GUID_NULL)
	{
		//Define erro.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método.
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDevice(RiidInterface, &pInterfaceRequest);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro para a interface a ser retornada no parametro de saida.
	Param_Out_Objeto->AdicionarPonteiro(pInterfaceRequest);

Done:;
	//Retorna o resultado.
	return Resultado;
}