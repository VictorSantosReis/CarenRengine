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
#include "../Media Foundation/CarenMFMediaSink.h"
#include "../Media Foundation/CarenMFVideoRenderer.h"
#include "../Media Foundation/CarenMFGetService.h"
#include "../Media Foundation/CarenMFVideoDisplayControl.h"
#include "../Media Foundation/CarenMFSample.h"
#include "../Direct3D/CarenDirect3DDeviceManager9.h"
#include "../Media Foundation/CarenMFVideoSampleAllocator.h"
#include "../Media Foundation/CarenMFMedia2DBuffer.h"
#include "../Media Foundation/CarenMFMedia2DBuffer2.h"
#include "../Media Foundation/CarenMFMediaSinkPreroll.h"
#include "../Media Foundation/CarenMFMediaEventGenerator.h"
#include "../Media Foundation/CarenMFPresentationTimeSource.h"
#include "../Media Foundation/CarenMFDXGIDeviceManager.h"
#include "../Media Foundation/CarenMFDXGIBuffer.h"
#include "../Media Foundation/CarenMFMediaSource.h"
#include "../Media Foundation/CarenMFMediaSourceEx.h"
#include "../Media Foundation/CarenMFAudioStreamVolume.h"
#include "../Media Foundation/CarenMFSimpleAudioVolume.h"
#include "../Direct3D/CarenD3D10Multithread.h"
#include "../Direct3D/CarenD3D11Texture1D.h"
#include "../Direct3D/CarenD3D11Texture2D.h"
#include "../Direct3D/CarenD3D11Texture3D.h"
#include "../Core Audio/CarenAudioClient.h"
#include "../Core Audio/CarenAudioRenderClient.h"
#include "../Core Audio/CarenChannelAudioVolume.h"
#include "../Core Audio/CarenAudioClock.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::GUIDs;

/// <summary>
/// Classe responsável por 'Converte' uma interface base entre interfaces da biblioteca.
/// </summary>
public ref class CastInterface abstract sealed
{
public:
	/// <summary>
	/// Método responsável por 'Converter' a Interface base para uma Interface Especifica do sistema.
	/// A referência para a interface atual, passada por referência, é deletada.
	/// </summary>
	/// <param name="Param_InterfaceBase">A interface a ser convetida para itnerface de destino.</param>
	/// <param name="Param_GuidInterfaceDestino">O Guid para a interface de destino.</param>
	/// <param name="Param_Out_Interface">O objeto que contém a interface solicitada.</param>
	static CarenResult CastInterfaceBase(ICaren^% Param_InterfaceBase, String^ Param_GuidInterfaceDestino, [Out] Object^% Param_Out_Interface)
	{
		//Variavel que vai retornar a interface
		Object^ InterfaceSolicitada = nullptr;

		//Variavel que vai conter o ponteiro.
		LPVOID pInterface = NULL;

		//Variavel que contém o resultado do método.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//OBtém o ponteiro
		Resultado = Param_InterfaceBase->RecuperarPonteiro(&pInterface);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Sai do método
			goto Done;
		}

		//Deixa a string toda em maiusculo
		Param_GuidInterfaceDestino = Param_GuidInterfaceDestino->ToUpper();

		//Verifica o guid e adiciona as chaves se não conter
		Param_GuidInterfaceDestino = VerificarGuidInterface(Param_GuidInterfaceDestino);

		//Compara a String.
		if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFMidiaSink))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMediaSink();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFAmostra))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFSample(false);

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFRenderizadorVideo))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFVideoRenderer();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFControladorVideo))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFVideoDisplayControl();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFApresentadorVideo))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFGetService();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFDXGIDeviceManager))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFDXGIDeviceManager();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_D3D11Device))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenD3D11Device();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_D3D10Multithread))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenD3D10Multithread();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFAlocadorAmostrasVideo))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFVideoSampleAllocator();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFMidia2DBuffer))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMedia2DBuffer();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFMidia2DBuffer2))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMedia2DBuffer2();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFMidiaSinkPreroll))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMediaSinkPreroll();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFGeradorEventosMidia))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMediaEventGenerator();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFFonteTempoRelogioApresentação))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFPresentationTimeSource(false);

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFFonteMidia))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMediaSource();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFFonteMidiaEx))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFMediaSourceEx();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFControladorAudioSimples))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFSimpleAudioVolume();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFControladorAudioFluxo))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFAudioStreamVolume();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_AudioCliente))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenAudioClient();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_AudioRenderCliente))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenAudioRenderClient();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_AudioCanalVolume))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenChannelAudioVolume();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_AudioRelogio))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenAudioClock();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_D3D11Texture2D))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenD3D11Texture2D();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else if (String::Equals(Param_GuidInterfaceDestino, GUIDs_CarenGuidInterfaces::GUID_CA_INTF_MFDXGIBuffer))
		{
			//Cria a interface.
			InterfaceSolicitada = gcnew CarenMFDXGIBuffer();

			//Define a interface
			((ICaren^)InterfaceSolicitada)->AdicionarPonteiro(pInterface);

			//Exclui a interface anterior
			Param_InterfaceBase = nullptr;
		}
		else
		{
			//Guid da interface não foi encontrado.
			Resultado.AdicionarCodigo(ResultCode::ER_E_NOINTERFACE, false);

			//Sai do método
			goto Done;
		}


		//Define o objeto de retorno no parametro
		Param_Out_Interface = InterfaceSolicitada;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado
		return Resultado;
	}

private:
	//Método que vai verificar a estrutura do guid da interface solicitada.
	static String^ VerificarGuidInterface(String^ Param_Guid)
	{
		//Verifica se o Guid já contém '{' e '}'
		if (!Param_Guid->Contains("{"))
		{
			//Insere a chave no inicio do guid.
			Param_Guid = Param_Guid->Insert(0, "{");
		}
		if (!Param_Guid->Contains("}"))
		{
			//Insere a chave no final.
			Param_Guid = Param_Guid + "}";
		}

		//Retorna o Guid.
		return Param_Guid;
	}
};

