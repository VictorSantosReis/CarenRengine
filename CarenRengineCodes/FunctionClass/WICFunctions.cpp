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
#include "../pch.h"
#include "WICFunctions.h"

CarenResult WICFunctions::_WICConvertBitmapSource(
	String^ Param_PixelGuidDest,
	ICarenWICBitmapSource^ Param_BmpSource, 
	ICarenWICBitmapSource^ Param_Out_BmpDst)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_PixelGuid = GUID_NULL;
	IWICBitmapSource* vi_pBitmapSrc = Nulo;
	IWICBitmapSource* vi_pOutBitmapDest = Nulo;

	//Converte a string para o guid.
	vi_PixelGuid = Util.CreateGuidFromString(Param_PixelGuidDest);

	//Recupera o ponteiro para o bitmap de origem.
	CarenGetPointerFromICarenSafe(Param_BmpSource, vi_pBitmapSrc);

	//Chama o método para realizar a operação.
	Hr = WICConvertBitmapSource(vi_PixelGuid, vi_pBitmapSrc, &vi_pOutBitmapDest);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do bitmap retornado na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutBitmapDest, Param_Out_BmpDst, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICCreateBitmapFromSection(
	UInt32 Param_Width,
	UInt32 Param_Height,
	String^ Param_PixelFormat,
	IntPtr Param_Section, 
	UInt32 Param_Stride,
	UInt32 Param_Offset, 
	ICarenWICBitmap^ Param_Out_Bitmap)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_PixelGuid = GUID_NULL;
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Converte a string para o guid.
	vi_PixelGuid = Util.CreateGuidFromString(Param_PixelFormat);

	//Chama o método para realizar a operação.
	Hr = WICCreateBitmapFromSection(
		Param_Width,
		Param_Height,
		vi_PixelGuid,
		Util.ConverterIntPtrToHandle(Param_Section),
		Param_Stride,
		Param_Offset,
		&vi_pOutBitmap
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Bitmap criado na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutBitmap, Param_Out_Bitmap, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICCreateBitmapFromSectionEx(
	UInt32 Param_Width,
	UInt32 Param_Height, 
	String^ Param_PixelFormat,
	IntPtr Param_Section,
	UInt32 Param_Stride, 
	UInt32 Param_Offset, 
	CA_WICSectionAccessLevel Param_AccessLevel, 
	ICarenWICBitmap^ Param_Out_Bitmap)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_PixelGuid = GUID_NULL;
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Converte a string para o guid.
	vi_PixelGuid = Util.CreateGuidFromString(Param_PixelFormat);

	//Chama o método para realizar a operação.
	Hr = WICCreateBitmapFromSectionEx(
		Param_Width,
		Param_Height,
		vi_PixelGuid,
		Util.ConverterIntPtrToHandle(Param_Section),
		Param_Stride,
		Param_Offset,
		static_cast<WICSectionAccessLevel>(Param_AccessLevel),
		&vi_pOutBitmap
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o Bitmap criado na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutBitmap, Param_Out_Bitmap, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICGetMetadataContentSize(
	String^ Param_GuidContainer, 
	ICarenWICMetadataWriter^ Param_Writer, 
	OutParam UInt64% Param_Out_Size)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidContainer = GUID_NULL;
	IWICMetadataWriter* vi_pWriter = Nulo;
	ULARGE_INTEGER vi_OutSize = { 0 };

	//Converte a string para o guid.
	vi_GuidContainer = Util.CreateGuidFromString(Param_GuidContainer);

	//Recupera o ponteiro para o Escritor de metadata.
	CarenGetPointerFromICarenSafe(Param_Writer, vi_pWriter);

	//Chama o método para realizar a operação.
	Hr = WICGetMetadataContentSize(const_cast<GUID&>(vi_GuidContainer), vi_pWriter, &vi_OutSize);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o size no parametro de saida.
	Param_Out_Size = vi_OutSize.QuadPart;

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICMapGuidToShortName(
	String^ Param_Guid, 
	UInt32 Param_SizeName, 
	CarenParameterResolver<String^>^% Param_Out_Name, 
	OutParam UInt32% Param_Out_SizeAtual)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_Guid = GUID_NULL;
	PWSTR vi_pOutName = Nulo; //Pode ser Nulo para recuperar o size necessário para o parametro (Param_SizeName).
	UINT32 vi_OutSizeAtual = Nulo;

	//Converte a string para o guid.
	vi_Guid = Util.CreateGuidFromString(Param_Guid);

	//Aloca memória para a String se informada
	if (Param_SizeName > 0)
		vi_pOutName = new WCHAR[Param_SizeName];

	//Chama o método para realizar a operação.
	Hr = WICMapGuidToShortName(
		const_cast<GUID&>(vi_Guid),
		Param_SizeName,
		Param_Out_Name->IgnoreParameter? Nulo: vi_pOutName,
		&vi_OutSizeAtual
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e cria no parametro de saida.
	if (ObjetoValido(vi_pOutName))
		Param_Out_Name->ObjetoParametro = gcnew String(vi_pOutName);

	//Define o size atual do nome.
	Param_Out_SizeAtual = vi_OutSizeAtual;

Done:;
	//Libera a memória para a string se valida.
	DeletarStringAllocatedSafe(&vi_pOutName);

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICMapSchemaToName(
	String^ Param_Guid, 
	String^ Param_Schema, 
	UInt32 Param_SizeName, 
	CarenParameterResolver<String^>^% Param_Out_Name, 
	OutParam UInt32% Param_Out_SizeAtual)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_Guid = GUID_NULL;
	PWSTR vi_pSchema = Nulo;
	PWSTR vi_pOutName = Nulo; //Pode ser Nulo para recuperar o size necessário para o parametro (Param_SizeName).
	UINT32 vi_OutSizeAtual = Nulo;

	//Converte a string para o guid.
	vi_Guid = Util.CreateGuidFromString(Param_Guid);

	//Converte a string para a nativa do schema.
	vi_pSchema = Util.ConverterStringToWCHAR(Param_Schema);

	//Aloca memória para a String se informada
	if (Param_SizeName > 0)
		vi_pOutName = new WCHAR[Param_SizeName];

	//Chama o método para realizar a operação.
	Hr = WICMapSchemaToName(
		const_cast<GUID&>(vi_Guid),
		vi_pSchema,
		Param_SizeName,
		Param_Out_Name->IgnoreParameter ? Nulo : vi_pOutName,
		&vi_OutSizeAtual
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e cria no parametro de saida.
	if (ObjetoValido(vi_pOutName))
		Param_Out_Name->ObjetoParametro = gcnew String(vi_pOutName);

	//Define o size atual do nome.
	Param_Out_SizeAtual = vi_OutSizeAtual;

Done:;
	//Libera a memória para a string se valida.
	DeletarStringAllocatedSafe(&vi_pOutName);

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICMapShortNameToGuid(
	String^ Param_Name,
	OutParam String^% Param_Out_Guid)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pName = Nulo;
	GUID vi_OutGuid = GUID_NULL;

	//Converte a string gerenciada para a nativa como nome.
	vi_pName = Util.ConverterStringToWCHAR(Param_Name);

	//Chama o método para realizar a operação.
	Hr = WICMapShortNameToGuid(vi_pName, &vi_OutGuid);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a string do parametro de saida com o guid retornado.
	Param_Out_Guid = Util.ConverterGuidToString(vi_OutGuid);

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICMatchMetadataContent(
	String^ Param_GuidContainer,
	String^ Param_GuidVendor, 
	ICarenStream^ Param_Stream, 
	OutParam String^% Param_Out_Guid)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidContainer = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IStream* vi_pStream = Nulo;
	GUID vi_OutGuid = GUID_NULL;

	//Converte os guids
	vi_GuidContainer = Util.CreateGuidFromString(Param_GuidContainer);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Stream, vi_pStream);

	//Chama o método para realizar a operação.
	Hr = WICMatchMetadataContent(
		const_cast<GUID&>(vi_GuidContainer),
		const_cast<GUID*>(&vi_GuidVendor),
		vi_pStream,
		&vi_OutGuid
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a string do parametro de saida com o guid retornado.
	Param_Out_Guid = Util.ConverterGuidToString(vi_OutGuid);

Done:;

	//Retorna o resultado
	return Resultado;
}

CarenResult WICFunctions::_WICSerializeMetadataContent(
	String^ Param_GuidContainer, 
	ICarenWICMetadataWriter^ Param_Writer, 
	CA_WICPersistOptions Param_PersistOptions, 
	ICarenStream^ Param_Stream)
{
	//Variavel de resultado a ser retornado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidContainer = GUID_NULL;
	IWICMetadataWriter* vi_pWriter = Nulo;
	IStream* vi_pStream = Nulo;

	//Converte a string para o guid.
	vi_GuidContainer = Util.CreateGuidFromString(Param_GuidContainer);

	//Recupera o ponteiro para o escritor de metadata.
	CarenGetPointerFromICarenSafe(Param_Writer, vi_pWriter);

	//Recupera o ponteiro para o fluxo.
	CarenGetPointerFromICarenSafe(Param_Stream, vi_pStream);

	//Chama o método para realizar a operação.
	Hr = WICSerializeMetadataContent(
		const_cast<GUID&>(vi_GuidContainer),
		vi_pWriter,
		static_cast<DWORD>(Param_PersistOptions),
		vi_pStream
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;

	//Retorna o resultado
	return Resultado;
}
