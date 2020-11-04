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
	namespace Windows
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

		/// <summary>
		/// (IEnumString) - Interface responsável por enumerar strings. LPWSTR é o tipo que indica um ponteiro para uma sequência de caracteres wide, ou Unicode.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("81EB331C-4725-464C-8A9A-E5B8F5A89EF6")]
		public interface class ICarenEnumString : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos


			/// <summary>
			/// Cria um novo enumerador que contém o mesmo estado de enumeração que o atual. Este método permite gravar um ponto na sequência de enumeração para retornar a esse ponto mais tarde.O interlocutor deve 
			/// liberar este novo enumerador separadamente do primeiro enumerador.
			/// </summary>
			/// <param name="Param_Out_EnumString">Retorna um ponteiro clonado da interface atual.</param>
			CarenResult Clone([Out] ICarenEnumString^% Param_Out_EnumString);

			/// <summary>
			/// Recupera o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_Quantidade">O número de itens a serem recuperados. Se houver menos do que o número solicitado de itens deixados na sequência, este método recupera os elementos restantes.</param>
			/// <param name="Param_Out_Itens">Retorna uma variedade de itens enumerados.</param>
			/// <param name="Param_Out_QuantidadeRetornada">Retorna o número de itens que foram recuperados. Este parâmetro é sempre menor ou igual ao número de itens solicitados.</param>
			CarenResult Next(
				UInt32 Param_Quantidade,
				[Out] cli::array<String^>^% Param_Out_Itens,
				[Out] UInt32% Param_Out_QuantidadeRetornada);

			/// <summary>
			/// Redefine a sequência de enumeração até o início.
			/// Não há garantia de que o mesmo conjunto de objetos será enumerado após a conclusão da operação de reset. Uma coleção estática é redefinida para o início, mas pode ser muito cara para algumas coleções, 
			/// como arquivos em um diretório, para garantir essa condição.
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// Ignora um número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_CountSkip">O número de itens a serem ignorados.</param>
			CarenResult Skip(UInt32 Param_CountSkip);
		};

		/// <summary>
		/// (IEnumUnknown) - Interface responsável por enumerar objetos com a interface IUnknown. Pode ser usado para enumerar através dos objetos em um componente contendo 
		/// vários objetos.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("A9957309-C57A-4A73-BA40-F7862771BF4C")]
		public interface class ICarenEnumUnknown : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// Cria um novo enumerador que contém o mesmo estado de enumeração que o atual. Este método permite gravar um ponto na sequência de enumeração para retornar a esse ponto mais tarde. O interlocutor deve 
			/// liberar este novo enumerador separadamente do primeiro enumerador.
			/// </summary>
			/// <param name="Param_Out_EnumClone">Retorna o ponteiro para o objeto enumerador clonado.</param>
			CarenResult Clone([Out] ICarenEnumUnknown^% Param_Out_EnumClone);

			/// <summary>
			/// Recupera o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_Quantidade">O número de itens a serem recuperados. Se houver menos do que o número solicitado de itens deixados na sequência, este método recupera os elementos restantes.</param>
			/// <param name="Param_Out_ItensEnumerados">Retorna uma variedade de itens enumerados. O chamador é responsável por liberar as interface depois de sua utilização.</param>
			/// <param name="Param_Out_QuantidadeRetornada">O número de itens que foram recuperados. Este parâmetro é sempre menor ou igual ao número de itens solicitados.</param>
			CarenResult Next(
				UInt32 Param_Quantidade,
				[Out] cli::array<ICaren^>^ Param_Out_ItensEnumerados,
				[Out] UInt32% Param_Out_QuantidadeRetornada);

			/// <summary>
			/// Redefine a sequência de enumeração até o início.
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// Ignora o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_QuantidadeSkip">O número de itens a serem ignorados.</param>
			CarenResult Skip(UInt32 Param_QuantidadeSkip);
		};
	}
}