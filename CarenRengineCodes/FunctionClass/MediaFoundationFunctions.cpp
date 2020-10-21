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
#include "MediaFoundationFunctions.h"

CarenResult MediaFoundationFunctions::IniciarMediaFoundation()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para inciar o MF.
	HRESULT HR = MFStartup(MF_VERSION);

	//Verifica o resultado
	if (Sucesso(HR))
	{
		//Define que foi iniciado com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}

CarenResult MediaFoundationFunctions::DesligarMediaFoundation()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para desligar a media foundation.
	HRESULT HR = MFShutdown();

	//Verifica o resultado
	if (Sucesso(HR))
	{
		//Define que foi iniciado com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

Done:;
	//Retorna o resultado
	return Resultado;
}

CarenResult MediaFoundationFunctions::CA_MFCreateWaveFormatExFromMFMediaType(ICarenMFMediaType^ Param_TipoMidia, CA_MFWaveFormatExConvertFlags Param_FlagsConversão, CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_WavFormato, UInt32% Param_Out_Size)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel que vai conter o resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFMediaType* pTipoMidia = NULL;
	MFWaveFormatExConvertFlags FlagsConvert = static_cast<MFWaveFormatExConvertFlags>(Param_FlagsConversão);
	WAVEFORMATEXTENSIBLE* pWavFormato = NULL;
	UINT32 SizeWavStruct = 0;

	//Chama o método para recuperar o ponteiro
	Resultado = Param_TipoMidia->RecuperarPonteiro((LPVOID*)&pTipoMidia);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface não contém ponteiro valido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a função.
	Hr = MFCreateWaveFormatExFromMFMediaType(pTipoMidia, (WAVEFORMATEX**)&pWavFormato, &SizeWavStruct, FlagsConvert);

	//Verifica se a função obteve sucesso
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else
	{
		//A função falhou
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Converte e define no parametro de saida a estrutura e os dados.
	Param_Out_WavFormato = Util.ConverterWaveformatExtensibleUnmanagedToManaged(pWavFormato);
	Param_Out_Size = SizeWavStruct;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria da estrutura
	if (ObjetoValido(pWavFormato))
	{
		//Libera a memoria da estrutura.
		CoTaskMemFree(pWavFormato);
	}

	//Retorna o resultado
	return Resultado;
}

CarenResult MediaFoundationFunctions::CA_MFCreateWaveFormatExFromMFMediaType(ICarenMFMediaType^ Param_TipoMidia, CA_MFWaveFormatExConvertFlags Param_FlagsConversão, CA_WAVEFORMATEX^% Param_Out_WavFormato, UInt32% Param_Out_Size)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel que vai conter o resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFMediaType* pTipoMidia = NULL;
	MFWaveFormatExConvertFlags FlagsConvert = static_cast<MFWaveFormatExConvertFlags>(Param_FlagsConversão);
	WAVEFORMATEX* pWavFormato = NULL;
	UINT32 SizeWavStruct = 0;

	//Chama o método para recuperar o ponteiro
	Resultado = Param_TipoMidia->RecuperarPonteiro((LPVOID*)&pTipoMidia);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface não contém ponteiro valido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a função.
	Hr = MFCreateWaveFormatExFromMFMediaType(pTipoMidia, &pWavFormato, &SizeWavStruct, FlagsConvert);

	//Verifica se a função obteve sucesso
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else
	{
		//A função falhou
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Converte e define no parametro de saida a estrutura e os dados.
	Param_Out_WavFormato = Util.ConverterWaveFormatexUnmanagedToManaged(pWavFormato);
	Param_Out_Size = SizeWavStruct;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria da estrutura
	if (ObjetoValido(pWavFormato))
	{
		//Libera a memoria da estrutura.
		CoTaskMemFree(pWavFormato);
	}

	//Nula o ponteiro de tipo de midia.
	if (ObjetoValido(pTipoMidia))
	{
		//Limpa a variavel.
		pTipoMidia = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

CarenResult MediaFoundationFunctions::CA_MFInitMediaTypeFromWaveFormatEx(CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, UInt32 Param_SizeEstrutura, ICarenMFMediaType^% Param_Out_TipoMidia)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel que vai conter o resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFMediaType* pTipoMidia = NULL;
	WAVEFORMATEXTENSIBLE* pWavFormato = NULL;
	UINT32 SizeStructure = Param_SizeEstrutura;

	//Cria a estrutura não gerenciada wav
	pWavFormato = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_WavFormato);

	//Cria o Tipo de midia para armazenar as informações
	Hr = MFCreateMediaType(&pTipoMidia);

	//Verifica se a função obteve sucesso
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else
	{
		//A função falhou
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Chama a função
	Hr = MFInitMediaTypeFromWaveFormatEx(pTipoMidia, (WAVEFORMATEX*)pWavFormato, SizeStructure);

	//Verifica se a função obteve sucesso
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else
	{
		//A função falhou
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método
		goto Done;
	}

	//Cria a interface e retorna ao usuário
	Param_Out_TipoMidia = gcnew CarenMFMediaType();

	//Chama o método para definir o ponteiro de trabalho
	Param_Out_TipoMidia->AdicionarPonteiro(pTipoMidia);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria da estrutura
	if (ObjetoValido(pWavFormato))
	{
		//Libera a memoria da estrutura.
		DeletarEstrutura(&pWavFormato);
	}

	//Retorna o resultado
	return Resultado;
}
