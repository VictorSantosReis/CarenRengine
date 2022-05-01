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


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D3D11RasterizerState)

//Métodos da interface ICarenD3D11RasterizerState2

/// <summary>
/// (GetDesc2) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
/// </summary>
/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
CarenResult Shared_D3D11RasterizerState::GetDesc2(
	ID3D11RasterizerState2* Param_MyPointerWork, 
	[Out] Estruturas::CA_D3D11_RASTERIZER_DESC2^% Param_Out_DescRasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC2 DescRasterizador;

	//Chama o método para realizar a operação
	Param_MyPointerWork->GetDesc2(&DescRasterizador);

	//Converte e define no parametro de saida.
	Param_Out_DescRasterizador = Util.ConverterD3D11_RASTERIZER_DESC2UnManaged_ToManaged(&DescRasterizador);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}


//Métodos da interface ICarenD3D11RasterizerState1

/// <summary>
/// (GetDesc1) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
/// </summary>
/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
CarenResult Shared_D3D11RasterizerState::GetDesc1(
	ID3D11RasterizerState1* Param_MyPointerWork, 
	[Out] Estruturas::CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC1 DescRasterizador;

	//Chama o método para realizar a operação
	Param_MyPointerWork->GetDesc1(&DescRasterizador);

	//Converte e define no parametro de saida.
	Param_Out_DescRasterizador = Util.ConverterD3D11_RASTERIZER_DESC1UnManaged_ToManaged(&DescRasterizador);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}


//Métodos da interface ICarenD3D11RasterizerState

CarenResult Shared_D3D11RasterizerState::GetDesc(
	ID3D11RasterizerState* Param_MyPointerWork, 
	[Out] Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_Out_DescRasterizador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D3D11_RASTERIZER_DESC DescRasterizador;

	//Chama o método para realizar a operação
	Param_MyPointerWork->GetDesc(&DescRasterizador);

	//Converte e define no parametro de saida.
	Param_Out_DescRasterizador = Util.ConverterD3D11_RASTERIZER_DESCUnManaged_ToManaged(&DescRasterizador);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}
