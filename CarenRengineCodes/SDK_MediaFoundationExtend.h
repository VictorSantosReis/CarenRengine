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
#include "SDK_Base.h"
#include "SDK_MediaFoundation.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace da media foundation.
using namespace CarenRengine::MediaFoundation;


///////////////////////////////////////
// EXTEND MICROSOFT MEDIA FOUNDATION //
///////////////////////////////////////


//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace que contém as interfaces de extensões.
	namespace MediaFoundationExtended
	{
		/// <summary>
		/// (IMFMediaType) - Interface responsável por conter métodos que estedem a interface ICarenMFMediaType. 
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extensão")]
		[Guid("F3044D42-12B4-46C6-9B15-7E54A025242D")]
		public interface class ICarenMFMediaTypeExtend : ICarenMFMediaType
		{
			/// <summary>
			/// (Extensão) - Método responsável por obter o tipo principal da mídia. 
			/// </summary>
			/// <param name="Param_Out_TipoPrincipal">Recebe o tipo principal da mídia(Áudio ou Vídeo).</param>
			/// <param name="Param_Out_Guid">Recebe o Guid do formato principal.</param>
			CarenResult ExGetMajorMediaType(OutParam Enumeracoes::CA_MAJOR_MEDIA_TYPES% Param_Out_TipoPrincipal, OutParam String^% Param_Out_Guid);

			/// <summary>
			/// (Extensão) - Método responsável por retornar o formato do tipo principal da mídia. 
			/// </summary>
			/// <param name="Param_Out_FormatoMidia">Recebe o subtipo(Formato) da mídia principal.</param>
			/// <param name="Param_Out_GuidFormato">Recebe o Guid do subtipo(Formato).</param>
			CarenResult ExGetFormatSubtype(OutParam Enumeracoes::CA_MEDIA_SUBTYPES% Param_Out_FormatoMidia, OutParam String^% Param_Out_GuidFormato);
		};

		/// <summary>
		/// (IMFSourceReader) - Interface responsável por conter métodos que estedem a interface ICarenMFSourceReader.
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extensão")]
		[Guid("8E3B80BC-2993-4D7D-AAA0-D460B06ACE22")]
		public interface class ICarenMFSourceReaderExtend : ICarenMFSourceReader
		{
			/// <summary>
			/// (Extensão) - Método responsável por retornar a quantidade de fluxos na mídia carregada pelo leitor.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na mídia carregada.</param>
			CarenResult ExGetCountStreams(OutParam UInt32% Param_Out_QuantidadeFluxos);

			/// <summary>
			/// (Extensão) - Método responsável por retornar todos os tipos principais de mídia do arquivo carregado pelo leitor.
			/// </summary>
			/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de mídia no fluxo carregado</param>
			CarenResult ExGetAllMediaTypesStream(OutParam List<Enumeracoes::CA_MAJOR_MEDIA_TYPES>^% Param_Out_TiposMidias);

			/// <summary>
			/// Lê a próxima amostra disponivel da fonte de mídia de forma Assincrona.
			/// </summary>
			/// <param name="Param_StreamIndex">O index para o fluxo a ser extraido a amostra. Esse valor pode ser um UInt32 para um ID de fluxo valido ou um dos valores da enumeração (CA_SOURCE_READER_ID).</param>
			/// <returns></returns>
			CarenResult ExReadSampleAsync(UInt32 Param_StreamIndex);
		};
	}
}