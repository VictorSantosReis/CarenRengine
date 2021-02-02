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

CarenResult MediaFoundationFunctions::_MFStartup()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para inciar o MF.
	HRESULT Hr = MFStartup(MF_VERSION);

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
CarenResult MediaFoundationFunctions::_MFShutdown()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para desligar a media foundation.
	HRESULT Hr = MFShutdown();

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
CarenResult MediaFoundationFunctions::_MFAddPeriodicCallback(IntPtr Param_Callback, ICaren^ Param_Context, OutParam UInt32% Param_Out_Key)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	MFPERIODICCALLBACK vi_pCallback = Nulo;
	IUnknown* vi_pObjectContext = Nulo; //Pode ser Nulo;
	DWORD vi_OutKey = 0;

	//Converte o int ptr para o callback.
	vi_pCallback = Util.ConverterIntPtrTo<MFPERIODICCALLBACK>(Param_Callback);

	//Verifica se forneceu uma interface de contexto e recupera o ponteiro.
	if (ObjetoGerenciadoValido(Param_Context))
		CarenGetPointerFromICarenSafe(Param_Context, vi_pObjectContext);

	//Chama o método para realizar a operação.
	Hr = MFAddPeriodicCallback(vi_pCallback, vi_pObjectContext, &vi_OutKey);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a key gerada no parametro de saida.
	Param_Out_Key = static_cast<UInt32>(vi_OutKey);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFRemovePeriodicCallback(UInt32 Param_Key)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	DWORD vi_Key = static_cast<DWORD>(Param_Key);

	//Chama o método para realizar a operação.
	Hr = MFRemovePeriodicCallback(vi_Key);

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
CarenResult MediaFoundationFunctions::_MFAverageTimePerFrameToFrameRate(UInt64 Param_AverageTimePerFrame, OutParam UInt32% Param_Out_Numerator, OutParam UInt32% Param_Out_Denominator)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	UINT32 vi_OutNumerator = 0;
	UINT32 vi_OutDenominator = 0;

	//Chama o método para realizar a operação.
	Hr = MFAverageTimePerFrameToFrameRate(Param_AverageTimePerFrame, &vi_OutNumerator, &vi_OutDenominator);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_Numerator = vi_OutNumerator;
	Param_Out_Denominator = vi_OutDenominator;

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFFrameRateToAverageTimePerFrame(UInt32 Param_Numerator, UInt32 Param_Denominator, OutParam UInt64% Param_Out_AverageTimePerFrame)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	UINT64 vi_OutAverageTimePerFrame = 0;

	//Chama o método para realizar a operação.
	Hr = MFFrameRateToAverageTimePerFrame(Param_Numerator, Param_Denominator, &vi_OutAverageTimePerFrame);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_AverageTimePerFrame = vi_OutAverageTimePerFrame;

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCalculateBitmapImageSize(CA_BITMAPINFOHEADER^ Param_BmpHeader, UInt32 Param_Size, OutParam UInt32% Param_Out_SizeImage, OutParam Boolean% Param_Out_Known)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	PBITMAPINFOHEADER vi_pBitmapInfo = Nulo;
	UINT32 vi_OutSizeImagem = 0;
	BOOL vi_OutKnow = FALSE;

	//Converte a estrutura gerenciada para a nativa.
	vi_pBitmapInfo = Util.ConverterBITMAPINFOHEADERManaged_ToUnamaged(Param_BmpHeader);

	//Chama o método para realizar a operação.
	Hr = MFCalculateBitmapImageSize(const_cast<PBITMAPINFOHEADER>(vi_pBitmapInfo), Param_Size, &vi_OutSizeImagem, &vi_OutKnow);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_SizeImage = vi_OutSizeImagem;
	Param_Out_Known = vi_OutKnow ? true : false;

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&vi_pBitmapInfo);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCalculateImageSize(String^ Param_GuidSubtypeVideo, UInt32 Param_Width, UInt32 Param_Height, OutParam UInt32% Param_Out_SizeImage)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidSubtype = GUID_NULL;
	UINT32 vi_OutSizeImage = 0;

	//Converte a string para o guid.
	vi_GuidSubtype = Util.CreateGuidFromString(Param_GuidSubtypeVideo);

	//Chama o método para realizar a operação.
	Hr = MFCalculateImageSize(vi_GuidSubtype, Param_Width, Param_Height, &vi_OutSizeImage);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o dado no parametro de saida.
	Param_Out_SizeImage = vi_OutSizeImage;

Done:;

	//Retorna o resultado
	return Resultado;
}
Boolean MediaFoundationFunctions::_MFCompareFullToPartialMediaType(ICarenMFMediaType^ Param_TypeFull, ICarenMFMediaType^ Param_PartialType)
{
	//Variavel a ser retornada.
	Boolean Resultado = false;

	//Resultado de CarenResult.
	CarenResult CrResult = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	IMFMediaType* vi_pTypeFull = Nulo;
	IMFMediaType* vi_pTypeParcial = Nulo;

	//Recupera o ponteiro para o tipo de midia completo.
	CrResult = RecuperarPonteiroCaren(Param_TypeFull, &vi_pTypeFull);
	
	//Verifica se não houve erro.
	if (!CarenSucesso(CrResult))
		throw gcnew Exception("Falhou ao recuperar o ponteiro para o tipo de mídia completo.");

	//Recupera o ponteiro para o tipo de midia parcial.
	CrResult = RecuperarPonteiroCaren(Param_PartialType, &vi_pTypeParcial);

	//Verifica se não houve erro.
	if (!CarenSucesso(CrResult))
		throw gcnew Exception("Falhou ao recuperar o ponteiro para o tipo de mídia parcial.");

	//Chama o método para realizar a operação.
	Resultado = MFCompareFullToPartialMediaType(vi_pTypeFull, vi_pTypeParcial);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFConvertFromFP16Array(cli::array<float>^% Param_Ref_Dest, cli::array<UInt16>^ Param_Source, UInt32 Param_Count)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	pin_ptr<float> vi_pinToZeroIndexRefArrayDest = &Param_Ref_Dest[0]; //Pin para o buffer de destino que vai receber os dados para evitar copiar desnecessarias.
	pin_ptr<WORD> vi_pinToZeroIndexArraySource = &Param_Source[0];
	WORD* vi_ArraySourceTemp = reinterpret_cast<WORD*>(vi_pinToZeroIndexArraySource); //Array temporario até o pin sair do escopo.
	DWORD vi_Count = static_cast<DWORD>(Param_Count);


	//Chama o método para realizar a operação.
	Hr = MFConvertFromFP16Array(reinterpret_cast<float*>(vi_pinToZeroIndexRefArrayDest), const_cast<WORD*>(vi_ArraySourceTemp), vi_Count);

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
CarenResult MediaFoundationFunctions::_MFConvertToFP16Array(cli::array<UInt16>^% Param_Ref_Dest, cli::array<float>^ Param_Source, UInt32 Param_Count)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	pin_ptr<WORD> vi_pinToZeroIndexRefArrayDest = &Param_Ref_Dest[0]; //Pin para o buffer de destino que vai receber os dados para evitar copias desnecessarias.
	pin_ptr<float> vi_PintoZeroIndexArraySource = &Param_Source[0]; //Pin para o buffer de origem que vai ser convetido para evitar copias desnecessarias
    float* vi_ArraySourceTemp = reinterpret_cast<float*>(vi_PintoZeroIndexArraySource);//Array temporario até o pin sair do escopo.
	DWORD vi_Count = static_cast<DWORD>(Param_Count);

	//Chama o método para realizar a operação.
	Hr = MFConvertToFP16Array(reinterpret_cast<WORD*>(vi_pinToZeroIndexRefArrayDest), const_cast<float*>(vi_ArraySourceTemp), vi_Count);

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
CarenResult MediaFoundationFunctions::_MFCopyImage(
	ICarenBuffer^ Param_BufferDestino,
	Int32 Param_DestStride,
	ICarenBuffer^ Param_BufferOrigem,
	Int32 Param_SrcStride,
	UInt32 Param_WidthInBytes,
	UInt32 Param_Lines)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferDest = DefaultGenPointer;
	GenPointer vi_pBufferSource = DefaultGenPointer;

	//Recupera o ponteiro para o buffer de destino se valido.
	CarenGetPointerFromICarenBufferSafe(Param_BufferDestino, vi_pBufferDest);

	//Recupera o ponteiro para o buffer de origem se valido.
	CarenGetPointerFromICarenBufferSafe(Param_BufferOrigem, vi_pBufferSource);

	//Chama o método para realizar a operação.
	Hr = MFCopyImage(
		Util.ConverterIntPtrTo<PBYTE>(vi_pBufferDest),
		Param_DestStride,
		const_cast<PBYTE>(Util.ConverterIntPtrTo<PBYTE>(vi_pBufferSource)),
		Param_SrcStride,
		static_cast<DWORD>(Param_WidthInBytes),
		static_cast<DWORD>(Param_Lines)
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
CarenResult MediaFoundationFunctions::_MFCreatePropertiesFromMediaType(ICarenMFMediaType^ Param_MediaType, String^ Param_RIID, ICaren^ Param_Out_Object)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaType = Nulo;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutObject = Nulo;

	//Recupera o ponteiro para o Media Type
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Converte a string para o riid da interface requisitada.
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreatePropertiesFromMediaType(vi_pMediaType, vi_RIID, reinterpret_cast<void**>(&vi_pOutObject));

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
CarenResult MediaFoundationFunctions::_MFTranscodeGetAudioOutputAvailableTypes(
	String^ Param_GuidSubtype, 
	CA_MFT_ENUM_FLAG Param_Flags, 
	ICarenMFAttributes^ Param_Atributos, 
	ICarenMFCollection^ Param_Out_Availebletypes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidAudioSubtype = GUID_NULL;
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);
	IMFAttributes* vi_pAttributes = Nulo; //Pode ser NULO.
	IMFCollection* vi_pOutCollection = Nulo;

	//Converte a string para o guid do subtipo do audio.
	vi_GuidAudioSubtype = Util.CreateGuidFromString(Param_GuidSubtype);

	//Verifica se forneceu a interface de atributos e obtém o ponteiro.
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Chama o método para realizar a operação.
	Hr = MFTranscodeGetAudioOutputAvailableTypes(
		vi_GuidAudioSubtype,
		vi_Flags,
		vi_pAttributes,
		&vi_pOutCollection
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

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutCollection, Param_Out_Availebletypes, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFSerializeAttributesToStream(ICarenMFAttributes^ Param_AtributosSerialize, CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS Param_Flags, ICarenStream^ Param_StreamDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFAttributes* vi_pAttributesToStream = Nulo;
	IStream* vi_pStreamDestino = Nulo;
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);

	//Recupera o ponteiro para a interface de atributos.
	CarenGetPointerFromICarenSafe(Param_AtributosSerialize, vi_pAttributesToStream);

	//Recupera o ponteiro para o Fluxo que vai conter os dados serializados.
	CarenGetPointerFromICarenSafe(Param_StreamDestino, vi_pStreamDestino);

	//Chama o método para realizar a operação.
	Hr = MFSerializeAttributesToStream(vi_pAttributesToStream, vi_Flags, vi_pStreamDestino);

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
CarenResult MediaFoundationFunctions::_MFSerializePresentationDescriptor(ICarenMFPresentationDescriptor^ Param_PD, OutParam UInt32% Param_Out_SizeBuffer, OutParam ICarenBuffer^% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFPresentationDescriptor* vi_PDSerialize = Nulo;
	DWORD vi_OutSizeBuffer = Nulo;
	PBYTE vi_pOutBufferSerializado = Nulo; 

	//Recupera o ponteiro para o descritor de apresentação
	CarenGetPointerFromICarenSafe(Param_PD, vi_PDSerialize);

	//Chama o método para realizar a operação.
	Hr = MFSerializePresentationDescriptor(vi_PDSerialize, &vi_OutSizeBuffer, &vi_pOutBufferSerializado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a largura dos dados no parametro de saida.
	Param_Out_SizeBuffer = static_cast<UInt32>(vi_OutSizeBuffer);

	//Cria a interface a ser retornada.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Associa a matriz de bytes na interface de saida do buffer.
	Resultado = Param_Out_Buffer->CriarBuffer(IntPtr(vi_pOutBufferSerializado), false, Param_Out_SizeBuffer, Param_Out_SizeBuffer);

	//Verifica se não falhou e libera o buffer.
	if (!CarenSucesso(Resultado))
		CoTaskMemFree(vi_pOutBufferSerializado);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFDeserializeAttributesFromStream(ICarenMFAttributes^ Param_Atributos, CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS Param_Flags, ICarenStream^ Param_Stream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFAttributes* vi_pAttributes = Nulo; //Não pode ser NULO.
	IStream* vi_pStream = Nulo; //Não pode ser NULO.
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);

	//Recupera o ponteiro para a interface de atributos que vai receber os dados.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Recupera o ponteiro para o fluxo que contém os dados a serem deserializados.
	CarenGetPointerFromICarenSafe(Param_Stream, vi_pStream);

	//Chama o método para realizar a operação.
	Hr = MFDeserializeAttributesFromStream(vi_pAttributes, vi_Flags, vi_pStream);

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
CarenResult MediaFoundationFunctions::_MFDeserializePresentationDescriptor(UInt32 Param_BufferSize, ICarenBuffer^ Param_Buffer, ICarenMFPresentationDescriptor^ Param_Out_PresentationDescriptor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	DWORD vi_SizeBuffer = static_cast<DWORD>(Param_BufferSize);
	GenPointer vi_pBuffer = DefaultGenPointer;
	IMFPresentationDescriptor* vi_pOutPD = Nulo;

	//Recupera o ponteiro para o buffer com os dados serializados.
	CarenGetPointerFromICarenBufferSafe(Param_Buffer, vi_pBuffer);

	//Chama o método para realizar a operação.
	Hr = MFDeserializePresentationDescriptor(vi_SizeBuffer, Util.ConverterIntPtrTo<PBYTE>(vi_pBuffer), &vi_pOutPD);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface no parametro de saida.
	CarenSetPointerToICarenSafe(vi_pOutPD, Param_Out_PresentationDescriptor, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFEnumDeviceSources(
	ICarenMFAttributes^ Param_Atributos, 
	OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArraySourceActivate,
	OutParam UInt32% Param_Out_SizeArray)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFAttributes* vi_pAttributes = Nulo;
	IMFActivate** vi_pOutArraySourceActivate = Nulo; //Release CoTaskMemFree.
	UINT32 vi_OutSizeArray = 0;

	//Recupera o ponteiro para a interface de atributos.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Chama o método para realizar a operação.
	Hr = MFEnumDeviceSources(vi_pAttributes, &vi_pOutArraySourceActivate, &vi_OutSizeArray);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a quantidade retornada não é igual a ZERO e sai do método.
	if (vi_OutSizeArray == 0)
	{
		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL,false);

		//Sai do método
		Sair;
	}

	//Cria o array que vai retornar as interfaces.
	Param_Out_ArraySourceActivate = gcnew cli::array<ICarenMFActivate^>(vi_OutSizeArray);

	//Faz um for para inicializar os dados e definir o ponteiro em cada interface
	for (UINT32 i = 0; i < vi_OutSizeArray; i++)
	{
		//Cria a interface.
		Param_Out_ArraySourceActivate[i] = gcnew CarenMFActivate();

		//Define o ponteiro na interface.
		Param_Out_ArraySourceActivate[i]->AdicionarPonteiro(vi_pOutArraySourceActivate[i]);
	}

	//Define a quantidade de interfaces na matriz.
	Param_Out_SizeArray = vi_OutSizeArray;

Done:;
	//Libera a memória para o array de ponteiros.
	//Vai apenas liberar a memória que o método (MFEnumDeviceSources) aloca internamente para definir os ponteiros.
	//As interfaces são de responsabilidade do usuário liberá-las.
	if (ObjetoValido(vi_pOutArraySourceActivate))
		CoTaskMemFree(vi_pOutArraySourceActivate);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetStrideForBitmapInfoHeader(CA_D3DFORMAT Param_Format, UInt32 Param_Width, OutParam Int32% Param_Out_Stride)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	DWORD vi_Format = static_cast<DWORD>(Param_Format);
	DWORD vi_Width = static_cast<DWORD>(Param_Width);
	LONG vi_OutStride = 0;

	//Chama o método para realizar a operação.
	Hr = MFGetStrideForBitmapInfoHeader(vi_Format, vi_Width, &vi_OutStride);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o stride no parametro de saida.
	Param_Out_Stride = vi_OutStride;

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetSupportedMimeTypes(OutParam CA_PROPVARIANT^% Param_Out_Mimes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_PropVar = Nulo;

	//Inicializa a propvariant.
	IniciarPropVariant(&vi_PropVar);

	//Chama o método para realizar a operação.
	Hr = MFGetSupportedMimeTypes(vi_PropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a propvariant nativa para a gerenciada e define no parametro de saida.
	Param_Out_Mimes = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_PropVar);

Done:;
	//Libera a memória utilizada pela propvariant.
	if (ObjetoValido(vi_PropVar))
		DeletarPropVariant(&vi_PropVar);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetSupportedSchemes(OutParam CA_PROPVARIANT^% Param_Out_Schemes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_PropVar = Nulo;

	//Inicializa a propvariant.
	IniciarPropVariant(&vi_PropVar);

	//Chama o método para realizar a operação.
	Hr = MFGetSupportedSchemes(vi_PropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a propvariant nativa para a gerenciada e define no parametro de saida.
	Param_Out_Schemes = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_PropVar);

Done:;
	//Libera a memória utilizada pela propvariant.
	if (ObjetoValido(vi_PropVar))
		DeletarPropVariant(&vi_PropVar);

	//Retorna o resultado
	return Resultado;
}
Int64 MediaFoundationFunctions::_MFGetSystemTime()
{
	//Retorna o horario do sistema em unidades de 100 Nanosegundos.
	return MFGetSystemTime();
}
CarenResult MediaFoundationFunctions::_MFGetTopoNodeCurrentType(ICarenMFTopologyNode^ Param_Node, UInt32 Param_StreamIndex, Boolean Param_Output, ICarenMFMediaType^ Param_Out_MediaType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFTopologyNode* vi_pNode = Nulo;
	BOOL vi_Output = Param_Output ? TRUE : FALSE;
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Recupera o ponteiro para o nó na topologia.
	CarenGetPointerFromICarenSafe(Param_Node, vi_pNode);

	//Chama o método para realizar a operação.
	Hr = MFGetTopoNodeCurrentType(
		vi_pNode,
		static_cast<DWORD>(Param_StreamIndex),
		vi_Output,
		&vi_pOutMediaType
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

	//Define o ponteiro na interface de saida
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_MediaType, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetAttributesAsBlobSize(ICarenMFAttributes^ Param_Atributos, OutParam UInt32% Param_Out_SizeBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFMediaType* vi_pMediaType = Nulo;
	UINT32 vi_OutSizeBuffer = 0;

	//Recupera o ponteiro para a interface de atributos a obter o tamanho do buffer necessário.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pMediaType);

	//Chama o método para realizar a operação.
	Hr = MFGetAttributesAsBlobSize(vi_pMediaType, &vi_OutSizeBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o tamanho do buffer necessário.
	Param_Out_SizeBuffer = static_cast<UInt32>(vi_OutSizeBuffer);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetAttributesAsBlob(ICarenMFAttributes^ Param_AtributosToBlob, ICarenBuffer^ Param_BufferDest, UInt32 Param_SizeBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaTypeSerialize = Nulo;
	GenPointer vi_pBufferDest = DefaultGenPointer;

	//Recupera o ponteiro para a interface de atributos a ser serializada.
	CarenGetPointerFromICarenSafe(Param_AtributosToBlob, vi_pMediaTypeSerialize);

	//Recupera o ponteiro para o buffer de destino.
	CarenGetPointerFromICarenBufferSafe(Param_BufferDest, vi_pBufferDest);

	//Chama o método para realizar a operação.
	Hr = MFGetAttributesAsBlob(vi_pMediaTypeSerialize, Util.ConverterIntPtrTo<PBYTE>(vi_pBufferDest), Param_SizeBuffer);

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
CarenResult MediaFoundationFunctions::_MFInitAttributesFromBlob(ICarenMFAttributes^ Param_Atributos, ICarenBuffer^ Param_Buffer, UInt32 Param_SizeBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaType = Nulo;
	GenPointer vi_pBufferSource = DefaultGenPointer;

	//Recupera o ponteiro para a interface de atributos a ser preenchida com os dados.
	CarenGetPointerFromICarenSafe(Param_Atributos, vi_pMediaType);

	//Recupera o ponteiro para o buffer de destino.
	CarenGetPointerFromICarenBufferSafe(Param_Buffer, vi_pBufferSource);

	//Chama o método para realizar a operação.
	Hr = MFInitAttributesFromBlob(vi_pMediaType, Util.ConverterIntPtrTo<PBYTE>(vi_pBufferSource), Param_SizeBuffer);

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
CarenResult MediaFoundationFunctions::_MFGetLocalId(ICarenBuffer^ Param_Verifier, UInt32 Param_Size, OutParam String^% Param_Out_ID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GenPointer vi_pBuffer = DefaultGenPointer;
	LPWSTR vi_pOutID = Nulo;

	//Recupera o ponteiro para o buffer.
	CarenGetPointerFromICarenBufferSafe(Param_Verifier, vi_pBuffer);

	//Chama o método para realizar a operação.
	Hr = MFGetLocalId(const_cast<PBYTE>(Util.ConverterIntPtrTo<PBYTE>(vi_pBuffer)), Param_Size, &vi_pOutID);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ID no parametro de saida.
	Param_Out_ID = gcnew String(vi_pOutID);

Done:;
	//Libera a memória para a string se valida.
	DeletarStringCoTaskSafe(&vi_pOutID);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetPlaneSize(CA_D3DFORMAT Param_VideoFormat, UInt32 Param_Width, UInt32 Param_Height, OutParam UInt32% Param_Out_PlaneSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	DWORD vi_Format = static_cast<DWORD>(Param_VideoFormat);
	DWORD vi_Width = static_cast<DWORD>(Param_Width);
	DWORD vi_Height = static_cast<DWORD>(Param_Height);
	DWORD vi_OutPlaneSize = 0;

	//Chama o método para realizar a operação.
	Hr = MFGetPlaneSize(vi_Format, vi_Width, vi_Height, &vi_OutPlaneSize);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o tamanho do frame no parametro de saida. 
	Param_Out_PlaneSize = static_cast<UInt32>(vi_OutPlaneSize);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFIsContentProtectionDeviceSupported(String^ Param_ProtectionSystemID, OutParam Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidProtectionSystemID = GUID_NULL;
	BOOL vi_OutSuporte = FALSE;

	//Converte a string gerenciada para o ID.
	vi_GuidProtectionSystemID = Util.CreateGuidFromString(Param_ProtectionSystemID);

	//Chama o método para realizar a operação.
	Hr = MFIsContentProtectionDeviceSupported(vi_GuidProtectionSystemID, &vi_OutSuporte);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_Suporte = vi_OutSuporte ? true : false;

Done:;

	//Retorna o resultado
	return Resultado;
}
CA_D3DFORMAT MediaFoundationFunctions::_MFMapDXGIFormatToDX9Format(CA_DXGI_FORMAT Param_Format)
{
	//Chama o método para realizar a operação.
	DWORD vi_ConvertD3D9Format = MFMapDXGIFormatToDX9Format(static_cast<DXGI_FORMAT>(Param_Format));

	//Retorna o formato
	return static_cast<CA_D3DFORMAT>(vi_ConvertD3D9Format);
}
CarenResult MediaFoundationFunctions::_MFRegisterLocalByteStreamHandler(String^ Param_FileExtension, String^ Param_MIMEType, ICarenMFActivate^ Param_Activate)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	LPWSTR vi_pFileExtension = Nulo;
	LPWSTR vi_pMIMEType = Nulo;
	IMFActivate* vi_pActivate = Nulo;

	//Converte as strings para os valores nativos.
	vi_pFileExtension = Util.ConverterStringToWCHAR(Param_FileExtension);
	vi_pMIMEType = Util.ConverterStringToWCHAR(Param_MIMEType);

	//Recupera o ponteiro para o ativador.
	CarenGetPointerFromICarenSafe(Param_Activate, vi_pActivate);

	//Chama o método para realizar a operação.
	Hr = MFRegisterLocalByteStreamHandler(vi_pFileExtension, vi_pMIMEType, vi_pActivate);

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
	//Libera a memória utilizada pelas string.
	DeletarStringAllocatedSafe(&vi_pFileExtension);
	DeletarStringAllocatedSafe(&vi_pMIMEType);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFRegisterLocalSchemeHandler(String^ Param_Scheme, ICarenMFActivate^ Param_Activate)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	LPWSTR vi_pSheme = Nulo;
	IMFActivate* vi_pActivate = Nulo;

	//Converte as strings para os valores nativos.
	vi_pSheme = Util.ConverterStringToWCHAR(Param_Scheme);

	//Recupera o ponteiro para o ativador.
	CarenGetPointerFromICarenSafe(Param_Activate, vi_pActivate);

	//Chama o método para realizar a operação.
	Hr = MFRegisterLocalSchemeHandler(vi_pSheme, vi_pActivate);

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
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pSheme);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFRequireProtectedEnvironment(ICarenMFPresentationDescriptor^ Param_PresentationDesc)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFPresentationDescriptor* vi_pPD = Nulo;

	//Recupera o ponteiro para o descritor de apresentação.
	CarenGetPointerFromICarenSafe(Param_PresentationDesc, vi_pPD);

	//Chama o método para realizar a operação.
	Hr = MFRequireProtectedEnvironment(vi_pPD);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//NÃO VERIFICA O RESULTADO PORQUE NÃO É NECESSÁRIO NESSE CASO.
	//A FUNÇÃO RETORNA UM HRESULT QUE REPRESENTA UM BOOLEANO(TRUE: SS_OK | FALSE: E_FAIL).

Done:;

	//Retorna o resultado
	return Resultado;
}
UInt64 MediaFoundationFunctions::_PackRatio(Int32 Param_Numerador, UInt32 Param_Denominador)
{
	//Chama a função para realizar o processo.
	return PackRatio(Param_Numerador, Param_Denominador);
}
UInt64 MediaFoundationFunctions::_PackSize(UInt32 Param_Width, UInt32 Param_Height)
{
	//Chama a função para realizar o processo.
	return PackSize(Param_Width, Param_Height);
}
void MediaFoundationFunctions::_UnpackRatio(UInt64 Param_UnPacked, OutParam Int32% Param_Out_Numerador, OutParam UInt32% Param_Out_Denominador)
{
	//Variaveis que vao receber os valores.
	INT32 vi_OutNum = 0;
	UINT32 vi_OutDeno = 0;

	//Chama a função para realizar o processo.
	UnpackRatio(Param_UnPacked, &vi_OutNum, &vi_OutDeno);

	//Define nos parametros de saida.
	Param_Out_Numerador = vi_OutNum;
	Param_Out_Denominador = vi_OutDeno;
}
void MediaFoundationFunctions::_UnpackSize(UInt64 Param_UnPacked, OutParam UInt32% Param_Out_Width, OutParam UInt32% Param_Out_Height)
{
	//Variaveis que vao receber os valores.
	UINT32 vi_OutWidth = 0;
	UINT32 vi_OutHeight = 0;

	//Chama a função para realizar o processo.
	UnpackSize(Param_UnPacked, &vi_OutWidth, &vi_OutHeight);

	//Define nos parametros de saida.
	Param_Out_Width = vi_OutWidth;
	Param_Out_Height = vi_OutHeight;
}
void MediaFoundationFunctions::_Unpack2UINT32AsUINT64(UInt64 Param_UnPacked, OutParam UInt32% Param_Out_High, OutParam UInt32% Param_Out_Low)
{
	//Variaveis que vao receber os valores.
	UINT32 vi_OutHigh = 0;
	UINT32 vi_OutLow = 0;

	//Chama a função para realizar o processo.
	Unpack2UINT32AsUINT64(Param_UnPacked, &vi_OutHigh, &vi_OutLow);

	//Define nos parametros de saida.
	Param_Out_High = vi_OutHigh;
	Param_Out_Low = vi_OutLow;
}
CarenResult MediaFoundationFunctions::_MFShutdownObject(ICaren^ Param_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IUnknown* vi_pObject = Nulo;

	//Recupera o ponteiro para a interface a ser desligada.
	CarenGetPointerFromICarenSafe(Param_Objeto, vi_pObject);
	
	//Chama o método para realizar a operação.
	Hr = MFShutdownObject(vi_pObject);

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
CarenResult MediaFoundationFunctions::_MFTGetInfo(
	String^ Param_ClsidMFT,
	CarenParameterResolver<String^>% Param_Out_NomeMFT, //Ref Value
	CarenParameterResolver<cli::array<CA_MFT_REGISTER_TYPE_INFO^>^>% Param_Out_ArrayInputTypes, //Ref Value
	OutParam UInt32% Param_Out_CountArrayInputTypes,
	CarenParameterResolver<cli::array<CA_MFT_REGISTER_TYPE_INFO^>^>% Param_Out_ArrayOutputTypes, //Ref Value
	OutParam UInt32% Param_Out_CountArrayOutputTypes,
	ICarenMFAttributes^ Param_Out_Atributos
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_ClsidMFT = GUID_NULL;
	PWSTR vi_pOutName = Nulo; //Opcional.
	MFT_REGISTER_TYPE_INFO* vi_pOutArrayInput = Nulo; //Opcional.
	UINT32 vi_OutCountArrayInput = 0;
	MFT_REGISTER_TYPE_INFO* vi_pOutArrayOutput = Nulo; //Opcional.
	UINT32 vi_OutCountArrayOutput = 0;
	IMFAttributes* vi_pOutAtributes = Nulo; //Opcional.

	//Cria o CLSID do MFT.
	vi_ClsidMFT = Util.CreateGuidFromString(Param_ClsidMFT);

	//Chama o método para realizar a operação.
	Hr = MFTGetInfo(
		vi_ClsidMFT,
		Param_Out_NomeMFT.IgnoreParameter ? Nulo : &vi_pOutName,
		Param_Out_ArrayInputTypes.IgnoreParameter ? Nulo : &vi_pOutArrayInput,
		&vi_OutCountArrayInput,
		Param_Out_ArrayOutputTypes.IgnoreParameter ? Nulo : &vi_pOutArrayOutput,
		&vi_OutCountArrayOutput,
		ObjetoGerenciadoValido(Param_Out_Atributos) ? &vi_pOutAtributes : Nulo
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

	//Cria a string que vai retornar o nome amigavel do MFT se desejado.
	if (!Param_Out_NomeMFT.IgnoreParameter)
		Param_Out_NomeMFT.ObjetoParametro = gcnew String(vi_pOutName);

	//Cria o array com os tipos de entrada se desejado.
	if (!Param_Out_ArrayInputTypes.IgnoreParameter && vi_OutCountArrayInput > 0)
	{
		//Cria o array a ser retornado ao usuário.
		Param_Out_ArrayInputTypes.ObjetoParametro = gcnew cli::array<CA_MFT_REGISTER_TYPE_INFO^>(vi_OutCountArrayInput);

		//Abre um for para converter os dados nativos e definir no array gerenciado.
		for (UINT32 i = 0; i < vi_OutCountArrayInput; i++)
		{
			//Converte e define o resultado no index da estrutura.
			Param_Out_ArrayInputTypes.ObjetoParametro[i] = Util.ConverterMFT_REGISTER_TYPE_INFOUnamaged_ToManaged(&vi_pOutArrayInput[i]);		
		}
	}

	//Define a quantidade de tipos de entrada no array
	Param_Out_CountArrayInputTypes = vi_OutCountArrayInput;

	//Cria o array com os tipos de saida se desejado.
	if (!Param_Out_ArrayOutputTypes.IgnoreParameter && vi_OutCountArrayOutput > 0)
	{
		//Cria o array a ser retornado ao usuário.
		Param_Out_ArrayOutputTypes.ObjetoParametro = gcnew cli::array<CA_MFT_REGISTER_TYPE_INFO^>(vi_OutCountArrayOutput);

		//Abre um for para converter os dados nativos e definir no array gerenciado.
		for (UINT32 i = 0; i < vi_OutCountArrayOutput; i++)
		{
			//Converte e define o resultado no index da estrutura.
			Param_Out_ArrayOutputTypes.ObjetoParametro[i] = Util.ConverterMFT_REGISTER_TYPE_INFOUnamaged_ToManaged(&vi_pOutArrayOutput[i]);
		}
	}

	//Define a quantidade de tipos de saida no array
	Param_Out_CountArrayOutputTypes = vi_OutCountArrayInput;

	//Define o ponteiro na interface se desejado
	if (ObjetoGerenciadoValido(Param_Out_Atributos) && ObjetoValido(vi_pOutAtributes))
		CarenSetPointerToICarenSafe(vi_pOutAtributes, Param_Out_Atributos, true);
Done:;
	//Libera a memória utilizada pelos arrays
	if (ObjetoValido(vi_pOutArrayInput))
		CoTaskMemFree(vi_pOutArrayInput); // By MSDN Documentation.
	if (ObjetoValido(vi_pOutArrayOutput))
		CoTaskMemFree(vi_pOutArrayOutput); // By MSDN Documentation.

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTEnum2(
	String^ Param_GuidCategory,
	CA_MFT_ENUM_FLAG Param_Flags, 
	CA_MFT_REGISTER_TYPE_INFO^ Param_InputType, 
	CA_MFT_REGISTER_TYPE_INFO^ Param_OutputType, 
	ICarenMFAttributes^ Param_Atributos, 
	OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArrayMFTActivate, 
	OutParam UInt32% Param_Out_CountMFTs)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidCategory = GUID_NULL;
	UINT32 vi_Flags = static_cast<UINT32>(Param_Flags);
	MFT_REGISTER_TYPE_INFO* vi_pInputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pOutputType = Nulo; //Pode ser NULO.
	IMFAttributes* vi_pAttributes = Nulo;
	IMFActivate** vi_pOutArrayMFTs = Nulo; //Alocado pela função atraves do CoTaskMemAlloc.
	UINT32 vi_OutCountMFTs = 0;

	//Converte a string para o guid nativo
	vi_GuidCategory = Util.CreateGuidFromString(Param_GuidCategory);

	//Converte a estrutura que indica o tipo de entrada se informada.
	if (ObjetoGerenciadoValido(Param_InputType))
		vi_pInputType = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_InputType);

	//Converte a estrutura que indica otipo de saida se informada
	if(ObjetoGerenciadoValido(Param_OutputType))
		vi_pOutputType = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_OutputType);

	//Recupera o ponteiro para a interface de atributos se valida
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Chama o método para realizar a operação.
	Hr = MFTEnum2(
		vi_GuidCategory,
		vi_Flags,
		ObjetoValido(vi_pInputType)? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pInputType): Nulo,
		ObjetoValido(vi_pOutputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pOutputType) : Nulo,
		vi_pAttributes,
		&vi_pOutArrayMFTs,
		&vi_OutCountMFTs
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

	//Define a quantidade de MFTs listados no parametro de saida.
	Param_Out_CountMFTs = vi_OutCountMFTs;

	//Verifica se a quantiade de MFTs listado não é zero e sai da função.
	if (vi_OutCountMFTs == 0)
		Sair;

	//Cria o array que será retornado para o usuário.
	Param_Out_ArrayMFTActivate = gcnew cli::array<ICarenMFActivate^>(vi_OutCountMFTs);

	//Faz um for para criar as interfaces e adicionar os ponteiros.
	for (UINT32 i = 0; i < vi_OutCountMFTs; i++)
	{
		//Cria a interface no index especificado.
		Param_Out_ArrayMFTActivate[i] = gcnew CarenMFActivate();

		//Define o ponteiro na interface
		Param_Out_ArrayMFTActivate[i]->AdicionarPonteiro(vi_pOutArrayMFTs[i]);
	}
	
Done:;
	//Libera a memória utilizada pela função para criar o array de ponteiros.
	//vai apenas liberar a memória do array. Os ponteiros é de responsábilidade do usuário.
	if (ObjetoValido(vi_pOutArrayMFTs))
		CoTaskMemFree(vi_pOutArrayMFTs);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTEnumEx(
	String^ Param_GuidCategory, 
	CA_MFT_ENUM_FLAG Param_Flags, 
	CA_MFT_REGISTER_TYPE_INFO^ Param_InputType, 
	CA_MFT_REGISTER_TYPE_INFO^ Param_OutputType, 
	OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArrayMFTActivate, 
	OutParam UInt32% Param_Out_CountMFTs)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_GuidCategory = GUID_NULL;
	UINT32 vi_Flags = static_cast<UINT32>(Param_Flags);
	MFT_REGISTER_TYPE_INFO* vi_pInputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pOutputType = Nulo; //Pode ser NULO.
	IMFActivate** vi_pOutArrayMFTs = Nulo; //Alocado pela função atraves do CoTaskMemAlloc.
	UINT32 vi_OutCountMFTs = 0;

	//Converte a string para o guid nativo
	vi_GuidCategory = Util.CreateGuidFromString(Param_GuidCategory);

	//Converte a estrutura que indica o tipo de entrada se informada.
	if (ObjetoGerenciadoValido(Param_InputType))
		vi_pInputType = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_InputType);

	//Converte a estrutura que indica otipo de saida se informada
	if (ObjetoGerenciadoValido(Param_OutputType))
		vi_pOutputType = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_OutputType);

	//Chama o método para realizar a operação.
	Hr = MFTEnumEx(
		vi_GuidCategory,
		vi_Flags,
		ObjetoValido(vi_pInputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pInputType) : Nulo,
		ObjetoValido(vi_pOutputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pOutputType) : Nulo,
		&vi_pOutArrayMFTs,
		&vi_OutCountMFTs
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

	//Define a quantidade de MFTs listados no parametro de saida.
	Param_Out_CountMFTs = vi_OutCountMFTs;

	//Verifica se a quantiade de MFTs listado não é zero e sai da função.
	if (vi_OutCountMFTs == 0)
		Sair;

	//Cria o array que será retornado para o usuário.
	Param_Out_ArrayMFTActivate = gcnew cli::array<ICarenMFActivate^>(vi_OutCountMFTs);

	//Faz um for para criar as interfaces e adicionar os ponteiros.
	for (UINT32 i = 0; i < vi_OutCountMFTs; i++)
	{
		//Cria a interface no index especificado.
		Param_Out_ArrayMFTActivate[i] = gcnew CarenMFActivate();

		//Define o ponteiro na interface
		Param_Out_ArrayMFTActivate[i]->AdicionarPonteiro(vi_pOutArrayMFTs[i]);
	}

Done:;
	//Libera a memória utilizada pela função para criar o array de ponteiros.
	//vai apenas liberar a memória do array. Os ponteiros é de responsábilidade do usuário.
	if (ObjetoValido(vi_pOutArrayMFTs))
		CoTaskMemFree(vi_pOutArrayMFTs);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTRegister(
	String^ Param_ClsidMFT,
	String^ Param_GuidCategory,
	String^ Param_Name,
	CA_MFT_ENUM_FLAG Param_Flags,
	UInt32 Param_CountInputTypes,
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes,
	UInt32 Param_CountOutputTypes,
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes,
	ICarenMFAttributes^ Param_Atributos
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_ClsidMFT = GUID_NULL;
	GUID vi_GuidCategory = GUID_NULL;
	PWSTR vi_pNameMFT = Nulo;
	UINT32 vi_Flags = static_cast<UINT32>(Param_Flags);
	MFT_REGISTER_TYPE_INFO* vi_pArrayInputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pArrayOutputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pAuxiliar = Nulo;
	IMFAttributes* vi_pAttributes = Nulo;

	//Converte as string para os guids nativos.
	vi_ClsidMFT = Util.CreateGuidFromString(Param_ClsidMFT);
	vi_GuidCategory = Util.CreateGuidFromString(Param_GuidCategory);

	//Converte a string com o nome amigavel no MFT.
	vi_pNameMFT = Util.ConverterStringToWCHAR(Param_Name);

	//Verifica se forneceu o array com os tipos de entrada e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayInputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayInputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountInputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountInputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayInputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayInputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Verifica se forneceu o array com os tipos de saida e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayOutputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayOutputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountOutputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountOutputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayOutputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayOutputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Recupera o ponteiro para a interface de atributos se fornecida
	if (ObjetoGerenciadoValido(Param_Atributos))
		CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAttributes);

	//Chama o método para realizar a operação.
	Hr = MFTRegister(
		vi_ClsidMFT,
		vi_GuidCategory,
		vi_pNameMFT,
		vi_Flags,
		Param_CountInputTypes,
		vi_pArrayInputType,
		Param_CountOutputTypes,
		vi_pArrayOutputType,
		vi_pAttributes
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
	//Libera a memória utilizado pelo nome amigavel do mft se valido.
	DeletarStringAllocatedSafe(&vi_pNameMFT);

	//Libera a memória utilizada para criar o array das estruturas
	DeletarMatrizEstruturasSafe(&vi_pArrayInputType);
	DeletarMatrizEstruturasSafe(&vi_pArrayOutputType);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTRegisterLocal(
	ICaren^ Param_ClassFactoryMFT, 
	String^ Param_GuidCategory, 
	String^ Param_Name, 
	CA_MFT_ENUM_FLAG Param_Flags, 
	UInt32 Param_CountInputTypes, 
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes, 
	UInt32 Param_CountOutputTypes, 
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IClassFactory* vi_pFactoryMFT = Nulo;
	GUID vi_GuidCategory = GUID_NULL;
	PWSTR vi_pNameMFT = Nulo;
	UINT32 vi_Flags = static_cast<UINT32>(Param_Flags);
	MFT_REGISTER_TYPE_INFO* vi_pArrayInputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pArrayOutputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pAuxiliar = Nulo;

	//Recupera o ponteiro para a Class Factory responsável por criar o MFT.
	CarenGetPointerFromICarenSafe(Param_ClassFactoryMFT, vi_pFactoryMFT);

	//Converte a string com a categoria do mft para o guid.
	vi_GuidCategory = Util.CreateGuidFromString(Param_GuidCategory);

	//Converte a string com o nome amigavel no MFT.
	vi_pNameMFT = Util.ConverterStringToWCHAR(Param_Name);

	//Verifica se forneceu o array com os tipos de entrada e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayInputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayInputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountInputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountInputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayInputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayInputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Verifica se forneceu o array com os tipos de saida e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayOutputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayOutputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountOutputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountOutputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayOutputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayOutputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Chama o método para realizar a operação.
	Hr = MFTRegisterLocal(
		vi_pFactoryMFT,
		const_cast<GUID&>(vi_GuidCategory),
		vi_pNameMFT,
		vi_Flags,
		Param_CountInputTypes,
		ObjetoValido(vi_pArrayInputType)? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pArrayInputType): Nulo,
		Param_CountOutputTypes,
		ObjetoValido(vi_pArrayOutputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pArrayOutputType) : Nulo
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
	//Libera a memória utilizado pelo nome amigavel do mft se valido.
	DeletarStringAllocatedSafe(&vi_pNameMFT);

	//Libera a memória utilizada para criar o array das estruturas
	DeletarMatrizEstruturasSafe(&vi_pArrayInputType);
	DeletarMatrizEstruturasSafe(&vi_pArrayOutputType);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTRegisterLocalByCLSID(
	String^ Param_ClsidMFT,
	String^ Param_GuidCategory,
	String^ Param_Name,
	CA_MFT_ENUM_FLAG Param_Flags,
	UInt32 Param_CountInputTypes,
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes,
	UInt32 Param_CountOutputTypes,
	cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_ClsidMFT = GUID_NULL;
	GUID vi_GuidCategory = GUID_NULL;
	PWSTR vi_pNameMFT = Nulo;
	UINT32 vi_Flags = static_cast<UINT32>(Param_Flags);
	MFT_REGISTER_TYPE_INFO* vi_pArrayInputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pArrayOutputType = Nulo; //Pode ser NULO.
	MFT_REGISTER_TYPE_INFO* vi_pAuxiliar = Nulo;

	//Converte as string para os guids nativos.
	vi_ClsidMFT = Util.CreateGuidFromString(Param_ClsidMFT);
	vi_GuidCategory = Util.CreateGuidFromString(Param_GuidCategory);

	//Converte a string com o nome amigavel no MFT.
	vi_pNameMFT = Util.ConverterStringToWCHAR(Param_Name);

	//Verifica se forneceu o array com os tipos de entrada e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayInputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayInputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountInputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountInputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayInputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayInputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Verifica se forneceu o array com os tipos de saida e converte para os dados nativos.
	if (ObjetoGerenciadoValido(Param_ArrayOutputTypes))
	{
		//Cria a matriz nativa que vai conter os dados.
		vi_pArrayOutputType = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_CountOutputTypes);

		//Faz um for para converter os dados gerenciados e definir na matriz.
		for (UINT32 i = 0; i < Param_CountOutputTypes; i++)
		{
			//Converte a estrutura.
			vi_pAuxiliar = Util.ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(Param_ArrayOutputTypes[i]);

			//Define os dados na matriz no indice especificado.
			vi_pArrayOutputType[i] = *vi_pAuxiliar;

			//Libera a memória para a estrutura.
			DeletarEstruturaSafe(&vi_pAuxiliar);
		}
	}

	//Chama o método para realizar a operação.
	Hr = MFTRegisterLocalByCLSID(
		const_cast<GUID&>(vi_ClsidMFT),
		const_cast<GUID&>(vi_GuidCategory),
		vi_pNameMFT,
		vi_Flags,
		Param_CountInputTypes,
		ObjetoValido(vi_pArrayInputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pArrayInputType) : Nulo,
		Param_CountOutputTypes,
		ObjetoValido(vi_pArrayOutputType) ? const_cast<MFT_REGISTER_TYPE_INFO*>(vi_pArrayOutputType) : Nulo
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
	//Libera a memória utilizado pelo nome amigavel do mft se valido.
	DeletarStringAllocatedSafe(&vi_pNameMFT);

	//Libera a memória utilizada para criar o array das estruturas
	DeletarMatrizEstruturasSafe(&vi_pArrayInputType);
	DeletarMatrizEstruturasSafe(&vi_pArrayOutputType);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFTUnregister(String^ Param_ClsidMFT)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_ClsidMFT = GUID_NULL;

	//Converte a string para o guid.
	vi_ClsidMFT = Util.CreateGuidFromString(Param_ClsidMFT);

	//Chama o método para realizar a operação.
	Hr = MFTUnregister(vi_ClsidMFT);

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
CarenResult MediaFoundationFunctions::_MFTUnregisterLocal(ICaren^ Param_ClassFactoryMFT)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IClassFactory* vi_pClassFactory = Nulo; //Pode ser NULO.

	//Verifica se forneceu a interface de criação de classe.
	if (ObjetoGerenciadoValido(Param_ClassFactoryMFT))
		CarenGetPointerFromICarenSafe(Param_ClassFactoryMFT, vi_pClassFactory);

	//Chama o método para realizar a operação.
	Hr = MFTUnregisterLocal(vi_pClassFactory);

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
CarenResult MediaFoundationFunctions::_MFTUnregisterLocalByCLSID(String^ Param_ClsidMFT)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_ClsidMFT = GUID_NULL;

	//Converte a string para o guid.
	vi_ClsidMFT = Util.CreateGuidFromString(Param_ClsidMFT);

	//Chama o método para realizar a operação.
	Hr = MFTUnregisterLocalByCLSID(vi_ClsidMFT);

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
CarenResult MediaFoundationFunctions::_MFCreateVideoMixerAndPresenter(
	ICaren^ Param_MixerOwner, 
	ICaren^ Param_PresenterOwner, 
	String^ Param_RiidMixer, 
	ICaren^ Param_Out_Mixer, 
	String^ Param_RiidPresenter, 
	ICaren^ Param_Out_Presenter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IUnknown* vi_pMixerOwner = Nulo; //Pode ser Nulo;
	IUnknown* vi_pPresenterOwner = Nulo; //Pode ser Nulo;
	GUID vi_RiidMixer = GUID_NULL;
	GUID vi_RiidPresenter = GUID_NULL;
	IUnknown* vi_pOutMixer = Nulo;
	IUnknown* vi_pOutPresenter = Nulo;

	//Recupera o ponteiro para o dono do mixer se informado
	if (ObjetoGerenciadoValido(Param_MixerOwner))
		CarenGetPointerFromICarenSafe(Param_MixerOwner, vi_pMixerOwner);

	//Recupera o ponteiro para o dono do apresentador se informado.
	if (ObjetoGerenciadoValido(Param_PresenterOwner))
		CarenGetPointerFromICarenSafe(Param_PresenterOwner, vi_pPresenterOwner);

	//Converte as strings para os guids nativos.
	vi_RiidMixer = Util.CreateGuidFromString(Param_RiidMixer);
	vi_RiidPresenter = Util.CreateGuidFromString(Param_RiidPresenter);

	//Chama o método para realizar a operação.
	Hr = MFCreateVideoMixerAndPresenter(
		vi_pMixerOwner,
		vi_pPresenterOwner,
		const_cast<GUID&>(vi_RiidMixer),
		reinterpret_cast<void**>(&vi_pOutMixer),
		const_cast<GUID&>(vi_RiidPresenter),
		reinterpret_cast<void**>(&vi_pOutPresenter)
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

	//Define os ponteiros nos parametros de saida.
	CarenSetPointerToICarenSafe(vi_pOutMixer, Param_Out_Mixer, true);
	CarenSetPointerToICarenSafe(vi_pOutPresenter, Param_Out_Presenter, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateEventQueue(ICaren^ Param_Out_EventQueue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaEventQueue* vi_pOutEventQueue = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateEventQueue(&vi_pOutEventQueue);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutEventQueue, Param_Out_EventQueue, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateVideoSampleAllocator(String^ Param_RIID, ICaren^ Param_Out_SampleAllocator)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutObject = Nulo;

	//Converte o RIID da interface solicitada.
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateVideoSampleAllocator(vi_RIID, reinterpret_cast<void**>(&vi_pOutObject));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_SampleAllocator, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateVideoSampleAllocatorEx(String^ Param_RIID, ICaren^ Param_Out_SampleAllocator)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutObject = Nulo;

	//Converte o RIID da interface solicitada.
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateVideoSampleAllocatorEx(vi_RIID, reinterpret_cast<void**>(&vi_pOutObject));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_SampleAllocator, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateStreamOnMFByteStreamEx(ICarenMFByteStream^ Param_ByteStream, String^ Param_RIID, ICaren^ Param_Out_Stream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutObject = Nulo;

	//Recupera o ponteiro para o fluxo de bytes da media foundation.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);	

	//Converte o RIID da interface solicitada.
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateStreamOnMFByteStreamEx(vi_pByteStream, vi_RIID, reinterpret_cast<void**>(&vi_pOutObject));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_Stream, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateSequencerSource(ICaren^ Param_Reservado, ICaren^ Param_Out_SequencerSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IUnknown* vi_pReserved = Nulo;
	IMFSequencerSource* vi_pOutSequencerSource = Nulo;

	//Recupera o ponteiro para o parametro reservado se informado
	if (ObjetoGerenciadoValido(Param_Reservado))
		CarenGetPointerFromICarenSafe(Param_Reservado, vi_pOutSequencerSource);

	//Chama o método para realizar a operação.
	Hr = MFCreateSequencerSource(vi_pReserved, &vi_pOutSequencerSource);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutSequencerSource, Param_Out_SequencerSource, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateSampleGrabberSinkActivate(ICarenMFMediaType^ Param_MediaType, ICaren^ Param_SampleGrabberCallback, ICarenMFActivate^ Param_Out_Activate)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFMediaType* vi_pMediaType = Nulo;
	IMFSampleGrabberSinkCallback* vi_pSampleCallback = Nulo;
	IMFActivate* vi_pOutAtivador = Nulo;

	//Recupera o ponteiro para o tipo de midia.
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Recupera o ponteiro para o callback de samples.
	CarenGetPointerFromICarenSafe(Param_SampleGrabberCallback, vi_pSampleCallback);

	//Chama o método para realizar a operação.
	Hr = MFCreateSampleGrabberSinkActivate(vi_pMediaType, vi_pSampleCallback, &vi_pOutAtivador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutAtivador, Param_Out_Activate, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateSampleCopierMFT(ICarenMFTransform^ Param_Out_CopierMFT)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFTransform* vi_pOutTransformCopier = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateSampleCopierMFT(&vi_pOutTransformCopier);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutTransformCopier, Param_Out_CopierMFT, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateTransformActivate(ICarenMFActivate^ Param_Out_Activate)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFActivate* vi_pOutActivateMFT = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateTransformActivate(&vi_pOutActivateMFT);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutActivateMFT, Param_Out_Activate, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateVideoMixer(ICaren^ Param_Owner, String^ Param_RIIDDevice, String^ Param_RIID, ICaren^ Param_Out_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IUnknown* vi_pOwner = Nulo; //Pode ser nulo.
	GUID vi_RIIDDevice = GUID_NULL;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutObject = Nulo;

	//Recupera o ponteiro para o dono do objeto se fornecido.
	if (ObjetoGerenciadoValido(Param_Owner))
		CarenGetPointerFromICarenSafe(Param_Owner, vi_pOwner);

	//Converte as string para o guids nativos.
	vi_RIIDDevice = Util.CreateGuidFromString(Param_RIIDDevice);
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateVideoMixer(vi_pOwner, vi_RIIDDevice, vi_RIID, reinterpret_cast<void**>(&vi_pOutObject));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_Objeto, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateProtectedEnvironmentAccess(ICaren^ Param_Out_Access)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFProtectedEnvironmentAccess* vi_pOutAccess = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateProtectedEnvironmentAccess(&vi_pOutAccess);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutAccess, Param_Out_Access, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreatePMPServer(CA_MFPMPSESSION_CREATION_FLAGS Param_Flags, ICaren^ Param_Out_PMPServer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	DWORD vi_FlagsCreate = static_cast<DWORD>(Param_Flags);
	IMFPMPServer* vi_pOutPMPServer = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreatePMPServer(vi_FlagsCreate, &vi_pOutPMPServer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutPMPServer, Param_Out_PMPServer, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFGetService(ICaren^ Param_Objeto, String^ Param_GuidService, String^ Param_RIID, ICaren^ Param_Out_InterfaceRequested)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IUnknown* vi_pInterfaceBase = Nulo;
	GUID vi_GuidService = GUID_NULL;
	GUID vi_RIID = GUID_NULL;
	IUnknown* vi_pOutServiceInterface = Nulo;

	//Recupera o ponteiro para a interface base na qual será obtido o serviço.
	CarenGetPointerFromICarenSafe(Param_Objeto, vi_pInterfaceBase);

	//Converte as string para o guids nativos.
	vi_GuidService = Util.CreateGuidFromString(Param_GuidService);
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFGetService(vi_pInterfaceBase, vi_GuidService, vi_RIID, reinterpret_cast<void**>(&vi_pOutServiceInterface));
	
	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutServiceInterface, Param_Out_InterfaceRequested, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateTempFile(CA_MF_FILE_ACCESSMODE Param_AccessMode, CA_MF_FILE_OPENMODE Param_OpenMode, CA_MF_FILE_FLAGS Param_Flags, ICarenMFByteStream^ Param_Out_ByteStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	MF_FILE_ACCESSMODE vi_ModoAcesso = static_cast<MF_FILE_ACCESSMODE>(Param_AccessMode);
	MF_FILE_OPENMODE vi_ModoAbertura = static_cast<MF_FILE_OPENMODE>(Param_OpenMode);
	MF_FILE_FLAGS vi_Flags = static_cast<MF_FILE_FLAGS>(Param_Flags);
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateTempFile(
		vi_ModoAcesso,
		vi_ModoAbertura,
		vi_Flags,
		&vi_pOutByteStream);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutByteStream, Param_Out_ByteStream, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateFile(CA_MF_FILE_ACCESSMODE Param_AccessMode, CA_MF_FILE_OPENMODE Param_OpenMode, CA_MF_FILE_FLAGS Param_Flags, String^ Param_Url, ICarenMFByteStream^ Param_Out_ByteStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	MF_FILE_ACCESSMODE vi_ModoAcesso = static_cast<MF_FILE_ACCESSMODE>(Param_AccessMode);
	MF_FILE_OPENMODE vi_ModoAbertura = static_cast<MF_FILE_OPENMODE>(Param_OpenMode);
	MF_FILE_FLAGS vi_Flags = static_cast<MF_FILE_FLAGS>(Param_Flags);
	PWSTR vi_pUrlArquivo = Nulo;
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Converte a string para a URL.
	vi_pUrlArquivo = Util.ConverterStringToWCHAR(Param_Url);

	//Chama o método para realizar a operação.
	Hr = MFCreateFile(
		vi_ModoAcesso,
		vi_ModoAbertura,
		vi_Flags,
		const_cast<LPCWSTR>(vi_pUrlArquivo),
		&vi_pOutByteStream);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutByteStream, Param_Out_ByteStream, true);

Done:;
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&vi_pUrlArquivo);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFBeginCreateFile(CA_MF_FILE_ACCESSMODE Param_AccessMode, CA_MF_FILE_OPENMODE Param_OpenMode, CA_MF_FILE_FLAGS Param_Flags, String^ Param_Url, ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjectState, ICaren^ Param_Out_CancelCookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	MF_FILE_ACCESSMODE vi_ModoAcesso = static_cast<MF_FILE_ACCESSMODE>(Param_AccessMode);
	MF_FILE_OPENMODE vi_ModoAbertura = static_cast<MF_FILE_OPENMODE>(Param_OpenMode);
	MF_FILE_FLAGS vi_Flags = static_cast<MF_FILE_FLAGS>(Param_Flags);
	PWSTR vi_pUrlArquivo = Nulo;
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjectState = Nulo;
	IUnknown* vi_pOutCancelCookie = Nulo;

	//Converte a string para a URL.
	vi_pUrlArquivo = Util.ConverterStringToWCHAR(Param_Url);

	//Recupera o ponteiro para o callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Recupera o ponteiro para o objeto de estado se informado.
	if (ObjetoGerenciadoValido(Param_ObjectState))
		CarenGetPointerFromICarenSafe(Param_ObjectState, vi_pObjectState);

	//Chama o método para realizar a operação.
	Hr = MFBeginCreateFile(
		vi_ModoAcesso,
		vi_ModoAbertura,
		vi_Flags,
		const_cast<LPCWSTR>(vi_pUrlArquivo),
		vi_pCallback,
		vi_pObjectState,
		ObjetoGerenciadoValido(Param_Out_CancelCookie)? &vi_pOutCancelCookie: Nulo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o cookie de cancelamento se o usuário tiver requisitado
	if (ObjetoValido(vi_pOutCancelCookie))
		CarenSetPointerToICarenSafe(vi_pOutCancelCookie, Param_Out_CancelCookie, true);

Done:;
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&vi_pUrlArquivo);

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFEndCreateFile(ICarenMFAsyncResult^ Param_Result, ICarenMFByteStream^ Param_Out_ByteStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFAsyncResult* vi_pResult = Nulo;
	IMFByteStream* vi_pOutByteStream = Nulo;

	//Recupera o ponteiro para o resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_Result, vi_pResult);

	//Chama o método para realizar a operação.
	Hr = MFEndCreateFile(vi_pResult, &vi_pOutByteStream);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutByteStream, Param_Out_ByteStream, true);

Done:;

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCancelCreateFile(ICaren^ Param_CancelCookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IUnknown* vi_pCookieCancelamento = Nulo;

	//Recupera o ponteiro para o cookie de cancelamento.
	CarenGetPointerFromICarenSafe(Param_CancelCookie, vi_pCookieCancelamento);

	//Chama o método para realizar a operação.
	Hr = MFCancelCreateFile(vi_pCookieCancelamento);

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
CarenResult MediaFoundationFunctions::_MFCreateMediaExtensionActivate(String^ Param_ActivatableClassId, ICaren^ Param_Configuration, String^ Param_RIID, ICaren^ Param_Out_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	PCWSTR vi_pClassID = Nulo;
	IUnknown* vi_pConfigInterface = Nulo; //Pode ser NULO.
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pOutObjeto = Nulo;

	//Converte a string para a Class Id.
	vi_pClassID = Util.ConverterStringToConstWCHAR(Param_ActivatableClassId);

	//Recupera a interface IPropertySet se fonecida no parametro (Param_Configuration).
	if(ObjetoGerenciadoValido(Param_Configuration))
		CarenGetPointerFromICarenSafe(Param_Configuration, vi_pConfigInterface)

	//Converte a string para o guid.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateMediaExtensionActivate(vi_pClassID, vi_pConfigInterface, vi_Riid, reinterpret_cast<void**>(&vi_pOutObjeto));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutObjeto, Param_Out_Objeto, true);

Done:;
	//Libera memória para a string.
	DeletarStringAllocatedSafe(const_cast<PWSTR*>(&vi_pClassID));

	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateContentDecryptorContext(String^ Param_GuidMediaProtectionSystem, ICarenMFDXGIDeviceManager^ Param_DXGIManager, ICaren^ Param_ProtectionDevice, ICaren^ Param_Out_ContentDecryptorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IMFDXGIDeviceManager* vi_pDevice = Nulo;
	IMFContentProtectionDevice* vi_pProtectionDevice = Nulo;
	IMFContentDecryptorContext* vi_pOutContext = Nulo;

	//Converte a string para o guid.
	vi_Riid = Util.CreateGuidFromString(Param_GuidMediaProtectionSystem);

	//Recupera o ponteiro para a interface do dispositivo.
	CarenGetPointerFromICarenSafe(Param_DXGIManager, vi_pDevice);

	//Recupera o ponteiro para a interface de protecao do dispositivo de midia.
	CarenGetPointerFromICarenSafe(Param_ProtectionDevice, vi_pProtectionDevice);

	//Chama o método para realizar a operação.
	Hr = MFCreateContentDecryptorContext(vi_Riid, vi_pDevice, vi_pProtectionDevice, &vi_pOutContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutContext, Param_Out_ContentDecryptorContext, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateContentProtectionDevice(String^ Param_GuidMediaProtectionSystem, ICaren^ Param_Out_ContentProtectionDevice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IMFContentProtectionDevice* vi_pOutProtectionDevice = Nulo;

	//Converte a string para o guid.
	vi_Riid = Util.CreateGuidFromString(Param_GuidMediaProtectionSystem);

	//Chama o método para realizar a operação.
	Hr = MFCreateContentProtectionDevice(vi_Riid, &vi_pOutProtectionDevice);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutProtectionDevice, Param_Out_ContentProtectionDevice, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_DXVA2CreateVideoService(ICaren^ Param_Direct3DDevice9, String^ Param_RIID, ICaren^ Param_Out_VideoService)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IDirect3DDevice9* vi_pDevice = Nulo;
	IUnknown* vi_pOutVideoService = Nulo;

	//Recupera o ponteiro para a interface do dispositivo.
	CarenGetPointerFromICarenSafe(Param_Direct3DDevice9, vi_pDevice);

	//Cria o riid da superfice da interface DXGI.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = DXVA2CreateVideoService(vi_pDevice, vi_Riid, reinterpret_cast<void**>(&vi_pDevice));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutVideoService, Param_Out_VideoService, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateAlignedMemoryBuffer(UInt32 Param_MaxLenght, CA_MF_BYTE_ALIGNMENT Param_Aligment, ICarenMFMediaBuffer^ Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	DWORD vi_Alinhamento = static_cast<DWORD>(Param_Aligment);
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Chama o método para realizar a operação.
	HRESULT Hr = MFCreateAlignedMemoryBuffer(static_cast<DWORD>(Param_MaxLenght), vi_Alinhamento, &vi_pOutMediaBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaBuffer, Param_Out_Buffer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateDXGISurfaceBuffer(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_SubresourceIndex, Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pSuperficeDXGI = Nulo;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Cria o riid da superfice da interface DXGI.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Recupera o ponteiro para a interface dxgi.
	CarenGetPointerFromICarenSafe(Param_SuperficeDXGI, vi_pSuperficeDXGI);
	
	//Chama o método para realizar a operação.
	Hr = MFCreateDXGISurfaceBuffer(vi_Riid, vi_pSuperficeDXGI, Param_SubresourceIndex, Param_BottomUpWhenLinear ? TRUE : FALSE, &vi_pOutMediaBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaBuffer, Param_Out_Buffer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateDXSurfaceBuffer(String^ Param_RIID, ICaren^ Param_SurfaceDX, Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pSuperficeD3D9 = Nulo;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Cria o riid da superfice da interface DXGI.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Recupera o ponteiro para a interface dxgi.
	CarenGetPointerFromICarenSafe(Param_SurfaceDX, vi_pSuperficeD3D9);

	//Chama o método para realizar a operação.
	Hr = MFCreateDXSurfaceBuffer(vi_Riid, vi_pSuperficeD3D9, Param_BottomUpWhenLinear ? TRUE : FALSE, &vi_pOutMediaBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaBuffer, Param_Out_Buffer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateMediaBufferFromMediaType(ICarenMFMediaType^ Param_MediaType, Int64 Param_Duration, UInt32 Param_MinLenght, UInt32 Param_MinAligment, ICarenMFMediaBuffer^ Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFMediaType* vi_pMediaType = Nulo;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Recupera o ponteiro para o Media Type
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);
	
	//Chama o método para realizar a operação.
	Hr = MFCreateMediaBufferFromMediaType(vi_pMediaType, Param_Duration, Param_MinLenght, Param_MinAligment, &vi_pOutMediaBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaBuffer, Param_Out_Buffer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateWICBitmapBuffer(String^ Param_RIID, ICaren^ Param_Surface, ICarenMFMediaBuffer^ Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pSuperfice = Nulo;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Cria o riid da superfice da interface DXGI.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Recupera o ponteiro para a interface dxgi.
	CarenGetPointerFromICarenSafe(Param_Surface, vi_pSuperfice);

	//Chama o método para realizar a operação.
	Hr = MFCreateWICBitmapBuffer(vi_Riid, vi_pSuperfice, &vi_pOutMediaBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaBuffer, Param_Out_Buffer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFInvokeCallback(ICarenMFAsyncResult^ Param_AsyncResult)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	IMFAsyncResult* vi_pResult = Nulo;

	//Recupera o ponteiro para o AsyncResult.
	CarenGetPointerFromICarenSafe(Param_AsyncResult, vi_pResult);

	//Chama o método para criar a interface.
	HRESULT Hr = MFInvokeCallback(vi_pResult);

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
CarenResult MediaFoundationFunctions::_MFCreateMuxStreamAttributes(ICarenMFCollection^ Param_ColecaoAtributosMuxStream, ICarenMFAttributes^ Param_Out_Atributos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	IMFCollection* vi_pColecao = Nulo;
	IMFAttributes* vi_pOutAtributos = Nulo;

	//Verifica se o ponteiro fornecido é valido.
	if (!ObjetoGerenciadoValido(Param_ColecaoAtributosMuxStream))
	{
		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método 
		Sair;
	}

	//Recupera o ponteiro para a coleção.
	CarenGetPointerFromICarenSafe(Param_ColecaoAtributosMuxStream, vi_pColecao);

	//Chama o método para criar a interface.
	HRESULT Hr = MFCreateMuxStreamAttributes(vi_pColecao, &vi_pOutAtributos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutAtributos, Param_Out_Atributos, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateAudioRendererActivate(ICarenMFActivate^ Param_Out_StreamingAudioRender)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	IMFActivate* vi_pOutSAR = Nulo;

	//Chama o método para realizar a operação.
	HRESULT Hr = MFCreateAudioRendererActivate(&vi_pOutSAR);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutSAR, Param_Out_StreamingAudioRender, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateVideoRendererActivate(IntPtr Param_Hwnd, ICarenMFActivate^ Param_Out_EnhancedVideoRenderer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	IMFActivate* vi_pOutEVR = Nulo;

	//Chama o método para realizar a operação.
	HRESULT Hr = MFCreateVideoRendererActivate(Util.ConverterIntPtrToHWND(Param_Hwnd), &vi_pOutEVR);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutEVR, Param_Out_EnhancedVideoRenderer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateAudioRenderer(ICarenMFAttributes^ Param_AudioAtributos, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFAttributes* vi_pAudioAtributos = Nulo;
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para a interface de atributos se valida.
	if (ObjetoGerenciadoValido(Param_AudioAtributos))
		CarenGetPointerFromICarenSafe(Param_AudioAtributos, vi_pAudioAtributos);

	//Chama o método para realizar a operação.
	Hr = MFCreateAudioRenderer(vi_pAudioAtributos, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateVideoRenderer(String^ Param_RIID, ICaren^ Param_Out_VideoRenderer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_Riid = GUID_NULL;
	IUnknown* vi_pOutVideoRenderer = Nulo;

	//Converte a string com o guid.
	vi_Riid = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = MFCreateVideoRenderer(vi_Riid, reinterpret_cast<void**>(&vi_pOutVideoRenderer));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutVideoRenderer, Param_Out_VideoRenderer, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreate3GPMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo; //Pode ser NULO - Se vi_pVideoType != NULO
	IMFMediaType* vi_pVideoType = Nulo; //Pode ser NULO - Se vi_pAudioType != NULO
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Verifica se a interface para o tipo de VÍDEO é válida.
	if (ObjetoGerenciadoValido(Param_VideoType))
		CarenGetPointerFromICarenSafe(Param_VideoType, vi_pVideoType);

	//Verifica se a interface para o tipo de ÁUDIO é válida.
	if (ObjetoGerenciadoValido(Param_AudioType))
		CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreate3GPMediaSink(vi_pByteStream, vi_pVideoType, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateAC3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo;
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Recupera o ponteiro para o tipo de áudio.
	CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateAC3MediaSink(vi_pByteStream, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateADTSMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo;
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Recupera o ponteiro para o tipo de áudio.
	CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateADTSMediaSink(vi_pByteStream, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateWAVEMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo;
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Recupera o ponteiro para o tipo de áudio.
	CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateWAVEMediaSink(vi_pByteStream, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateMP3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Chama o método para realizar a operação.
	Hr = MFCreateMP3MediaSink(vi_pByteStream, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateFMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo; //Pode ser NULO - Se vi_pVideoType != NULO
	IMFMediaType* vi_pVideoType = Nulo; //Pode ser NULO - Se vi_pAudioType != NULO
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Verifica se a interface para o tipo de VÍDEO é válida.
	if (ObjetoGerenciadoValido(Param_VideoType))
		CarenGetPointerFromICarenSafe(Param_VideoType, vi_pVideoType);

	//Verifica se a interface para o tipo de ÁUDIO é válida.
	if (ObjetoGerenciadoValido(Param_AudioType))
		CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateFMPEG4MediaSink(vi_pByteStream, vi_pVideoType, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo; //Pode ser NULO - Se vi_pVideoType != NULO
	IMFMediaType* vi_pVideoType = Nulo; //Pode ser NULO - Se vi_pAudioType != NULO
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Verifica se a interface para o tipo de VÍDEO é válida.
	if (ObjetoGerenciadoValido(Param_VideoType))
		CarenGetPointerFromICarenSafe(Param_VideoType, vi_pVideoType);

	//Verifica se a interface para o tipo de ÁUDIO é válida.
	if (ObjetoGerenciadoValido(Param_AudioType))
		CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateMPEG4MediaSink(vi_pByteStream, vi_pVideoType, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateAVIMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFByteStream* vi_pByteStream = Nulo;
	IMFMediaType* vi_pAudioType = Nulo; //Pode ser NULO - Se vi_pVideoType != NULO
	IMFMediaType* vi_pVideoType = Nulo; //Pode ser NULO - Se vi_pAudioType != NULO
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_ByteStream, vi_pByteStream);

	//Verifica se a interface para o tipo de VÍDEO é válida.
	if (ObjetoGerenciadoValido(Param_VideoType))
		CarenGetPointerFromICarenSafe(Param_VideoType, vi_pVideoType);

	//Verifica se a interface para o tipo de ÁUDIO é válida.
	if (ObjetoGerenciadoValido(Param_AudioType))
		CarenGetPointerFromICarenSafe(Param_AudioType, vi_pAudioType);

	//Chama o método para realizar a operação.
	Hr = MFCreateAVIMediaSink(vi_pByteStream, vi_pVideoType, vi_pAudioType, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateMuxSink(String^ Param_GuidOutputSubtype, ICarenMFAttributes^ Param_OutputAttributes, ICarenMFByteStream^ Param_OutputByteStream, ICarenMFMediaSink^ Param_Out_MediaSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_OutputGuidSubtype = GUID_NULL;
	IMFAttributes* vi_pOutputAttributes = Nulo; //Pode ser Nulo.
	IMFByteStream* vi_pOutputByteStream = Nulo; //Pode ser Nulo.
	IMFMediaSink* vi_pOutMediaSink = Nulo;

	//Converte a string com o guid.
	vi_OutputGuidSubtype = Util.CreateGuidFromString(Param_GuidOutputSubtype);

	//Recupera o ponteiro para a interface de atributos se valida.
	if (ObjetoGerenciadoValido(Param_OutputAttributes))
		CarenGetPointerFromICarenSafe(Param_OutputAttributes, vi_pOutputAttributes);

	//Recupera o ponteiro para a interface do byte stream se valida.
	if (ObjetoGerenciadoValido(Param_OutputByteStream))
		CarenGetPointerFromICarenSafe(Param_OutputByteStream, vi_pOutputByteStream);

	//Chama o método para realizar a operação.
	Hr = MFCreateMuxSink(vi_OutputGuidSubtype, vi_pOutputAttributes, vi_pOutputByteStream, &vi_pOutMediaSink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro do Media Sink criado na interface.
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MediaSink, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateDeviceSourceActivate(ICarenMFAttributes^ Param_Atributos, ICarenMFActivate^ Param_Out_DispositivoCaptura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFAttributes* vi_pAtributos = Nulo;
	IMFActivate* vi_pOutDeviceCapture = Nulo;

	//Recupera o ponteiro para a interface de atributos.
	Resultado = CarenGetPointerFromICarenSafe(Param_Atributos, vi_pAtributos);

	//Chama o método para realizar a operação.
	Hr = MFCreateDeviceSourceActivate(vi_pAtributos, &vi_pOutDeviceCapture);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutDeviceCapture, Param_Out_DispositivoCaptura, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateTranscodeSinkActivate(CarenMFActivate^ Param_Out_Transcode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	IMFActivate* vi_pOutTranscode = Nulo;

	//Chama o método para realizar a operação.
	Hr = MFCreateTranscodeSinkActivate(&vi_pOutTranscode);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutTranscode, Param_Out_Transcode, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateWMAEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaType = Nulo;
	IPropertyStore* vi_pStore = Nulo;
	IMFActivate* vi_pOutEncoder = Nulo;

	//Recupera o ponteiro para o tipo de midia.
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Recupera o ponteiro para a loja de propriedades
	CarenGetPointerFromICarenSafe(Param_EncodingProperties, vi_pStore);

	//Chama o método para realizar a operação.
	Hr = MFCreateWMAEncoderActivate(vi_pMediaType, vi_pStore, &vi_pOutEncoder);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutEncoder, Param_Out_Codificador, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateWMVEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	IMFMediaType* vi_pMediaType = Nulo;
	IPropertyStore* vi_pStore = Nulo;
	IMFActivate* vi_pOutEncoder = Nulo;

	//Recupera o ponteiro para o tipo de midia.
	CarenGetPointerFromICarenSafe(Param_MediaType, vi_pMediaType);

	//Recupera o ponteiro para a loja de propriedades
	CarenGetPointerFromICarenSafe(Param_EncodingProperties, vi_pStore);

	//Chama o método para realizar a operação.
	Hr = MFCreateWMVEncoderActivate(vi_pMediaType, vi_pStore, &vi_pOutEncoder);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutEncoder, Param_Out_Codificador, true);

Done:;
	//Retorna o resultado
	return Resultado;
}
CarenResult MediaFoundationFunctions::_MFCreateWaveFormatExFromMFMediaType(ICarenMFMediaType^ Param_TipoMidia, CA_MFWaveFormatExConvertFlags Param_FlagsConversão, CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_WavFormato, UInt32% Param_Out_Size)
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
CarenResult MediaFoundationFunctions::_MFCreateWaveFormatExFromMFMediaType(ICarenMFMediaType^ Param_TipoMidia, CA_MFWaveFormatExConvertFlags Param_FlagsConversão, CA_WAVEFORMATEX^% Param_Out_WavFormato, UInt32% Param_Out_Size)
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
CarenResult MediaFoundationFunctions::_MFInitMediaTypeFromWaveFormatEx(CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, UInt32 Param_SizeEstrutura, ICarenMFMediaType^ Param_Out_TipoMidia)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel que vai conter o resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFMediaType* vi_pOutTipoMidia = NULL;
	WAVEFORMATEXTENSIBLE* vi_pWavFormato = NULL;
	UINT32 SizeStructure = Param_SizeEstrutura;

	//Cria a estrutura não gerenciada wav
	vi_pWavFormato = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_WavFormato);

	//Cria o Tipo de midia para armazenar as informações
	Hr = MFCreateMediaType(&vi_pOutTipoMidia);

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
	Hr = MFInitMediaTypeFromWaveFormatEx(vi_pOutTipoMidia, (WAVEFORMATEX*)vi_pWavFormato, SizeStructure);

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

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutTipoMidia, Param_Out_TipoMidia, true);

Done:;
	//Libera a memoria da estrutura
	DeletarEstruturaSafe(&vi_pWavFormato);

	//Retorna o resultado
	return Resultado;
}