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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace da media foundation.
using namespace CarenRengine::MediaFoundation;


///////////////////////////////////////
// EXTEND MICROSOFT MEDIA FOUNDATION //
///////////////////////////////////////


//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace que cont�m as interfaces de extens�es.
	namespace MediaFoundationExtended
	{
		/// <summary>
		/// (IMFMediaType) - Interface respons�vel por conter m�todos que estedem a interface ICarenMFMediaType. 
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extens�o")]
		[Guid("F3044D42-12B4-46C6-9B15-7E54A025242D")]
		public interface class ICarenMFMediaTypeExtend : ICarenMFMediaType
		{
			/// <summary>
			/// (Extens�o) - M�todo respons�vel por obter o tipo principal da m�dia. 
			/// </summary>
			/// <param name="Param_Out_TipoPrincipal">Recebe o tipo principal da m�dia(�udio ou V�deo).</param>
			/// <param name="Param_Out_Guid">Recebe o Guid do formato principal.</param>
			CarenResult ExGetMajorMediaType(OutParam Enumeracoes::CA_MAJOR_MEDIA_TYPES% Param_Out_TipoPrincipal, OutParam String^% Param_Out_Guid);

			/// <summary>
			/// (Extens�o) - M�todo respons�vel por retornar o formato do tipo principal da m�dia. 
			/// </summary>
			/// <param name="Param_Out_FormatoMidia">Recebe o subtipo(Formato) da m�dia principal.</param>
			/// <param name="Param_Out_GuidFormato">Recebe o Guid do subtipo(Formato).</param>
			CarenResult ExGetFormatSubtype(OutParam Enumeracoes::CA_MEDIA_SUBTYPES% Param_Out_FormatoMidia, OutParam String^% Param_Out_GuidFormato);
		};

		/// <summary>
		/// (IMFSourceReader) - Interface respons�vel por conter m�todos que estedem a interface ICarenMFSourceReader.
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extens�o")]
		[Guid("8E3B80BC-2993-4D7D-AAA0-D460B06ACE22")]
		public interface class ICarenMFSourceReaderExtend : ICarenMFSourceReader
		{
			/// <summary>
			/// (Extens�o) - M�todo respons�vel por retornar a quantidade de fluxos na m�dia carregada pelo leitor.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na m�dia carregada.</param>
			CarenResult ExGetCountStreams(OutParam UInt32% Param_Out_QuantidadeFluxos);

			/// <summary>
			/// (Extens�o) - M�todo respons�vel por retornar todos os tipos principais de m�dia do arquivo carregado pelo leitor.
			/// </summary>
			/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de m�dia no fluxo carregado</param>
			CarenResult ExGetAllMediaTypesStream(OutParam List<Enumeracoes::CA_MAJOR_MEDIA_TYPES>^% Param_Out_TiposMidias);
		};
	}
}