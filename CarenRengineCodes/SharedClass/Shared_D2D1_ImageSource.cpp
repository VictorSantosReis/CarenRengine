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

//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D2D1ImageSource)

// Métodos da interface (ICarenD2D1ImageSource)


/// <summary>
/// Permite que o sistema operacional livre a memória de vídeo dos recursos descartando seu conteúdo.
/// </summary>
CarenResult Shared_D2D1ImageSource::OfferResources(ID2D1ImageSource* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->OfferResources();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Restaura o acesso aos recursos que foram oferecidos anteriormente pelo chamada OfferResources.
/// </summary>
/// <param name="Param_Out_RecursoDescartado">Retorna com TRUE se o conteúdo do recurso correspondente foi descartado e agora está indefinido ou FALSO se o conteúdo antigo do recurso correspondente ainda estiver intacto. 
/// O chamador pode passar NULO, se o chamador pretende preencher os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
CarenResult Shared_D2D1ImageSource::TryReclaimResources(
	ID2D1ImageSource* Param_MyPointerWork, 
	[Out] Boolean% Param_Out_RecursoDescartado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutBool = FALSE;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->TryReclaimResources(&OutBool);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o bool e define no parametro de saida.
	Param_Out_RecursoDescartado = static_cast<Boolean>(OutBool);

Done:;
	//Retorna o resultado.
	return Resultado;
}

