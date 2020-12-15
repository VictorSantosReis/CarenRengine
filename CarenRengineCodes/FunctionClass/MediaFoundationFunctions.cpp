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
	Utilidades Util;
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
