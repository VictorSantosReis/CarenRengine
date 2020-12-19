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

CarenResult MediaFoundationFunctions::CA_MFInitMediaTypeFromWaveFormatEx(CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, UInt32 Param_SizeEstrutura, ICarenMFMediaType^ Param_Out_TipoMidia)
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
