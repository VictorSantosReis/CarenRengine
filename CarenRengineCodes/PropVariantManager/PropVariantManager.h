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

/// <summary>
/// Classe responsável pela conversão da estrutura (PROPVARIANT) entre suas representações NATIVA e GERENCIADA.
/// </summary>
class PropVariantManager
{
	//Construtor & Destruidor da classe.
public:
	PropVariantManager(){}
	~PropVariantManager(){}

	//Métodos
public:
	/// <summary>
	/// Método responsável por converter uma estrutura (CA_PROPVARIANT) GERENCIADA em sua representação NATIVA.
	/// Retorna NULO se a conversão não for suportada ou algum valor necessário for invalido.
	/// </summary>
	/// <param name="Param_Estrutura">A estrutura GERENCIADA a ser convertida.</param>
	/// <returns></returns>
	PROPVARIANT* ConverterPropVariantManaged_ToUnmanaged(CA_PROPVARIANT^ Param_Estrutura);

	/// <summary>
	/// Método responsável por converter uma estrutura (PROPVARIANT) NATIVA em sua representação GERENCIADA.
	/// Retorna NULO se a conversão não for suportada ou algum valor necessário for invalido.
	/// </summary>
	/// <param name="Param_Estrutura">A estrutura NATIVA  ser convertida.</param>
	/// <returns></returns>
	CA_PROPVARIANT^ ConverterPropVariantUnmanaged_ToManaged(PROPVARIANT* Param_Estrutura);
};