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
#include "../SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

/// <summary>
/// Classe responsável por conter funções auxiliares para a Api do DirectX.
/// </summary>
public ref class DirectxFunctions
{
	//Construtor & Destruidor.
public:
	DirectxFunctions() {};
	~DirectxFunctions() {};

	//Métodos
public:
	/// <summary>
	/// Calcula um índice de subrecurso para uma textura.
	/// </summary>
	/// <param name="Param_MipSlice">Um índice baseado em zero para o nível mipmap para endereçamento; 0 indica o primeiro e mais detalhado nível mipmap.</param>
	/// <param name="Param_ArraySlice">O índice baseado em zero para o nível de matriz a ser abordado; use sempre 0 para texturas de volume (3D).</param>
	/// <param name="Param_MipLevels">Número de níveis de mipmap no recurso.</param>
	/// <returns></returns>
	UInt32 _D3D11CalcSubresource(
		UInt32 Param_MipSlice,
		UInt32 Param_ArraySlice,
		UInt32 Param_MipLevels
	);

};

