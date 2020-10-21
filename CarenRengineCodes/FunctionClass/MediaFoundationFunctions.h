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
#include "../Caren/Caren.h"
#include "../Media Foundation/CarenMFMediaType.h"
#include "../SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

/// <summary>
/// Classe responsável por conter os métodos nativos utilizados pela Api do Media Foundation.
/// </summary>
public ref class MediaFoundationFunctions
{
	//Destruidor da classe.
public:
	~MediaFoundationFunctions()
	{
	}


	//Métodos da Media Foundation.
public:
	/// <summary>
	/// Método responsável por inicia a Api do Media Foundation.
	/// </summary>
	CarenResult IniciarMediaFoundation();
	

	/// <summary>
	/// Método responsável por desligar a Api do Media Foundation.
	/// </summary>
	CarenResult DesligarMediaFoundation();


	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult CA_MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	

	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult CA_MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEX^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	


	/// <summary>
	/// Inicializa um tipo de mídia de um WAVEFORMATEX estrutura.
	/// </summary>
	/// <param name="Param_WavFormato">Uma estrutura wav que contém as informações do tipo de midia a ser criado.</param>
	/// <param name="Param_SizeEstrutura">O tamanho da estrutura em bytes.</param>
	/// <param name="Param_Out_TipoMidia">Retorna o tipo de midia convertida da estrutura Wav.</param>
	CarenResult CA_MFInitMediaTypeFromWaveFormatEx(
		CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, 
		UInt32 Param_SizeEstrutura, 
		[Out] ICarenMFMediaType^% Param_Out_TipoMidia);
};

