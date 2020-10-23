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
#include "pch.h"
#include "SDK_Caren.h"

//Abre o namespace principal
namespace CarenRengine
{
	/// <summary>
	/// Interface responsável por representar um IStream. 
	/// Está interface da suporte a métodos que necessitam de um fluxo para um arquivo ou memória local.
	/// </summary>
	[CategoryAttribute("Caren Interface")]
	[Guid("66BE0CDF-F0F1-4260-B64B-CBBAC152B4A4")]
	public interface class ICarenStream : ICaren
	{
		/// <summary>
		/// Propriedade que define se a classe foi descartada.
		/// </summary>
		property Boolean DisposedClasse
		{
			virtual Boolean get();
		}


		//Métodos

	};

	public interface class ICarenPersist
	{

	};

	public interface class ICarenPersistStream : ICarenPersist
	{

	};

	public interface class ICarenInspectable : ICaren
	{

	};

	public interface class ICarenRandomAcessStream : ICarenInspectable
	{

	};
}