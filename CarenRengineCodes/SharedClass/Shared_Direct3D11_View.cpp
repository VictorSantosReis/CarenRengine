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
#include "Shared_Direct3D11.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D3D11View)

/// <summary>
/// (GetResource) - Obtém o recurso que é acessado por meio dessa visualização.
/// </summary>
/// <param name="Param_Out_Recurso">Retorna um ponteiro para o recurso que é acessado através desta vista.</param>
CarenResult Shared_D3D11View::GetResource(ID3D11View* Poaram_MyPointerWork, [Out] ICarenD3D11Resource^% Param_Out_Recurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Resource* pRecurso = NULL;

	//Chama o método para realizar a operação
	Poaram_MyPointerWork->GetResource(&pRecurso);

	//Verifica se o objeto é valido
	if (ObjetoValido(pRecurso))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define falha na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface que vai ser retornada pelo parametro.
	Param_Out_Recurso = gcnew CarenD3D11Resource();

	//Define o ponteiro de trabalho
	Param_Out_Recurso->AdicionarPonteiro(pRecurso);

Done:;
	//Retorna o resultado.
	return Resultado;
}
