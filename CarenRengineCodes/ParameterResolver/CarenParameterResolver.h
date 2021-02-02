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
#include "../Header.h"

namespace CarenRengine
{
	/// <summary>
	/// Uma estrutura que serve como resolvedor de parametros opcionais.
	/// </summary>
	/// <typeparam name="TypeObject">O tipo do objeto a ser passado para o parametro.</typeparam>
	generic<typename TypeObject>
		public value struct CarenParameterResolver
		{
			//Variaveis que guardam os valores das propriedades da estrutura.
		private:
			TypeObject var_Objeto;
			Boolean var_IgnoreParamter;

			//Construtor
		public:
			/// <summary>
			/// Inicializa a estrutura passando os dados do parametro.
			/// </summary>
			/// <param name="Param_Objeto">O objeto original a ser passado para o método.</param>
			/// <param name="Param_IgnoreParameter">Um valor booleano que define se o parametro será ignorado ou não.</param>
			CarenParameterResolver(TypeObject Param_Objeto, Boolean Param_IgnoreParameter)
			{
				//Define os dados nas variaveis das propriedades abaixo.
				var_Objeto = Param_Objeto;
				var_IgnoreParamter = Param_IgnoreParameter;
			}
			/// <summary>
			/// Inicializa a estrutura e internamente define para ignorar o parametro.
			/// </summary>
			/// <param name="Param_IgnoreParamter">Esse valor sempre será TRUE.</param>
			CarenParameterResolver(Boolean Param_IgnoreParamter)
			{
				//Define que deve ignorar o parametro
				var_IgnoreParamter = true;
			}

			//Propriedades
		public:
			/// <summary>
			/// Propriedade que armazena o objeto do parametro.
			/// </summary>
			property TypeObject ObjetoParametro
			{
				//Obtém o objeto.
				TypeObject get()
				{
					return var_Objeto;
				}

				//Define o objeto.
				void set(TypeObject var)
				{
					var_Objeto = var;
				}
			}

			/// <summary>
			/// Propriedade que indica se deve igonorar o parametro ou não.
			/// </summary>
			property Boolean IgnoreParameter
			{
				//Retorna o valor.
				Boolean get() { return var_IgnoreParamter; }
			}
		};
}