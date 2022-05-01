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


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D3D11Resource)


//Métodos da interface proprietaria(ICarenD3D11Resource)

/// <summary>
/// (GetEvictionPriority) - Obtém a prioridade de despejo de um recurso.
/// </summary>
/// <param name="Param_Out_Prioridade">Retorna a prioridade do recurso que está sendo usado.</param>
CarenResult Shared_D3D11Resource::GetEvictionPriority(ID3D11Resource* Param_MyPointerWork, [Out] Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO% Param_Out_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	UINT PrioriadeEnum = 0;

	//Chama o método para realizar a operação.
	PrioriadeEnum = Param_MyPointerWork->GetEvictionPriority();

	//Converte para enumeração.
	Param_Out_Prioridade = static_cast<CA_DXGI_PRIORIDADE_RECURSO>(PrioriadeEnum);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetType) - Obtém o tipo de recurso.
/// </summary>
/// <param name="Param_Out_TipoRecurso">Retorna o tipo do recurso usado.</param>
CarenResult Shared_D3D11Resource::GetType(ID3D11Resource* Param_MyPointerWork, [Out] Enumeracoes::CA_D3D11_TIPO_RECURSO% Param_Out_TipoRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	D3D11_RESOURCE_DIMENSION TipoRecurso = D3D11_RESOURCE_DIMENSION::D3D11_RESOURCE_DIMENSION_UNKNOWN;

	//Chama o método para realizar a operação.
	Param_MyPointerWork->GetType(&TipoRecurso);

	//Converte para enumeração.
	Param_Out_TipoRecurso = static_cast<CA_D3D11_TIPO_RECURSO>(TipoRecurso);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetEvictionPriority) - Define a prioridade de despejo de um recurso.
/// Prioridades de recursos determinam qual recurso despejo de memória de vídeo quando o sistema ficou sem memória de vídeo. O recurso não será perdido; será removido da memória de vídeo e colocado na 
/// memória do sistema ou possivelmente colocado no disco rígido. O recurso será carregado volta na memória de vídeo quando for necessário.
/// </summary>
/// <param name="Param_PrioridadeRecurso">Define o tipo do recurso sendo usado.</param>
CarenResult Shared_D3D11Resource::SetEvictionPriority(ID3D11Resource* Param_MyPointerWork, Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO Param_PrioridadeRecurso)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	UINT PrioriadeEnum = static_cast<UINT>(Param_PrioridadeRecurso);

	//Chama o método para realizar a operação.
	Param_MyPointerWork->SetEvictionPriority(PrioriadeEnum);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}
