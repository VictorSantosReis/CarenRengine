﻿/*
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
#include "Shared_DXGI.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_DXGIAdapter)

// Métodos da interface ICarenDXGIAdapter4

/// <summary>
/// (GetDesc3) - Obtém uma descrição 1.6 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. Esta descrição inclui 
/// informações sobre compatibilidade com ACG.
/// </summary>
/// <param name="Param_Out_DescAdaptador">Recebe uma estrutura CA_DXGI_ADAPTER_DESC3 que descreve o adaptador. Este parâmetro não deve ser NULO. No hardware gráfico nível 9, 
/// versões iniciais do GetDesc3(GetDesc1 GetDesc) retornam zeros para o ID PCI em (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do 
/// adaptador e "Adaptador de Software" para a string de descrição no membro (Description). GetDesc3 e GetDesc2 retornam os valores reais de hardware nível 9 
/// nesses membros.</param>
CarenResult Shared_DXGIAdapter::GetDesc3(IDXGIAdapter4* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC3^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC3 AdapterDesc3 = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc3(&AdapterDesc3);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESC3UnManaged_ToManaged(&AdapterDesc3);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIAdapter3

/// <summary>
/// (QueryVideoMemoryInfo) - Este método informa o processo de uso do orçamento e do processo atual.
/// </summary>
/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações da memória de vídeo são consultadas. Para operação de GPU única, coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de vídeo são consultadas.</param>
/// <param name="Param_GrupoSegmento">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
/// <param name="Param_Out_InfoMemoria">Recebe uma estrutura CA_DXGI_QUERY_VIDEO_MEMORY_INFO com os valores atuais.</param>
CarenResult Shared_DXGIAdapter::QueryVideoMemoryInfo(
	IDXGIAdapter3* Param_MyPointerWork,
	UInt32 Param_NodeId,
	CA_DXGI_MEMORY_SEGMENT_GROUP Param_GrupoSegmento,
	[Out] CA_DXGI_QUERY_VIDEO_MEMORY_INFO^% Param_Out_InfoMemoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_QUERY_VIDEO_MEMORY_INFO DxgiMemInfo = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->QueryVideoMemoryInfo(Param_NodeId, static_cast<DXGI_MEMORY_SEGMENT_GROUP>(Param_GrupoSegmento), &DxgiMemInfo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_InfoMemoria = Util.ConverterDXGI_QUERY_VIDEO_MEMORY_INFOUnManaged_ToManaged(&DxgiMemInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterHardwareContentProtectionTeardownStatusEvent) - Se registra para receber notificação de eventos de proteção de proteção de conteúdo de hardware.
/// </summary>
/// <param name="Param_Evento">Uma Handle para o objeto de evento que o sistema operacional define quando ocorre o (TearDown) de proteção de conteúdo de hardware. </param>
/// <param name="Param_Out_Cookie">um valor-chave que um aplicativo pode passar para o método ICarenDXGIAdapter3:::UnregisterHardwareContentProtectionTeardownStatus para 
/// descadastrar o evento de notificação que o Param_Evento especifica.</param>
CarenResult Shared_DXGIAdapter::RegisterHardwareContentProtectionTeardownStatusEvent(
	IDXGIAdapter3* Param_MyPointerWork, 
	ICarenEvent^ Param_Evento, 
	[Out] UInt32 Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera um ponteiro para o evento
	Resultado = Param_Evento->RecuperarEvento(&pHandEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->RegisterHardwareContentProtectionTeardownStatusEvent(pHandEvento, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o Cookie e define no parametro de saida.
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterVideoMemoryBudgetChangeNotificationEvent) - Este método estabelece uma correlação entre um objeto de sincronização da CPU e o evento de mudança orçamentária.
/// </summary>
/// <param name="Param_Evento">Uma Handle para o objeto de evento.</param>
/// <param name="Param_Out_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent
/// retorna esse valor.</param>
CarenResult Shared_DXGIAdapter::RegisterVideoMemoryBudgetChangeNotificationEvent(
	IDXGIAdapter3* Param_MyPointerWork, 
	ICarenEvent^ Param_Evento, 
	[Out] UInt32 Param_Out_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandEvento = NULL;
	DWORD OutCookie = 0;

	//Recupera um ponteiro para o evento
	Resultado = Param_Evento->RecuperarEvento(&pHandEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Ponteiro invalido.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->RegisterVideoMemoryBudgetChangeNotificationEvent(pHandEvento, &OutCookie);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o Cookie e define no parametro de saida.
	Param_Out_Cookie = static_cast<UInt32>(OutCookie);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetVideoMemoryReservation) - Este método envia a memória física mínima necessária para uma aplicação, para o Sistema Operacional.
/// </summary>
/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações de memória de vídeo estão sendo definidas. Para operação de GPU única, 
/// coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de 
/// vídeo estão sendo definidas.</param>
/// <param name="Param_SegmentoGrupoMemoria">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
/// <param name="Param_ReversaMemoria">Especifica um UInt64 que define a memória física mínima necessária, em bytes.</param>
CarenResult Shared_DXGIAdapter::SetVideoMemoryReservation(
	IDXGIAdapter3* Param_MyPointerWork,
	UInt32 Param_NodeId,
	CA_DXGI_MEMORY_SEGMENT_GROUP Param_SegmentoGrupoMemoria,
	UInt64 Param_ReversaMemoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetVideoMemoryReservation(Param_NodeId, static_cast<DXGI_MEMORY_SEGMENT_GROUP>(Param_SegmentoGrupoMemoria), Param_ReversaMemoria);

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
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterHardwareContentProtectionTeardownStatus) - O Desregistra(Cancelar) um evento para impedi-lo de receber a notificação de eventos de proteção de 
/// conteúdo de hardware.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
/// retorna esse valor.</param>
CarenResult Shared_DXGIAdapter::UnregisterHardwareContentProtectionTeardownStatus(
	IDXGIAdapter3* Param_MyPointerWork, 
	UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_MyPointerWork->UnregisterHardwareContentProtectionTeardownStatus(static_cast<DWORD>(Param_Cookie));

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterVideoMemoryBudgetChangeNotification) - Este método deixa de notificar um objeto de sincronização da CPU sempre que ocorre uma mudança orçamentária. Um aplicativo pode mudar para a votação regular das informações.
/// </summary>
/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
/// retorna esse valor.</param>
CarenResult Shared_DXGIAdapter::UnregisterVideoMemoryBudgetChangeNotification(
	IDXGIAdapter3* Param_MyPointerWork, 
	UInt32 Param_Cookie)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_MyPointerWork->UnregisterVideoMemoryBudgetChangeNotification(static_cast<DWORD>(Param_Cookie));

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIAdapter2

/// <summary>
/// (GetDesc2) - Obtém uma descrição 1.2 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. 
/// Esta descrição inclui informações sobre a granularidade em que a unidade de processamento gráfico (GPU) pode ser impedida de realizar 
/// sua tarefa atual.
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC2 que descreve o adaptador. Este parâmetro não deve ser 
/// NULO.No hardware gráfico nível 9, versões anteriores do GetDesc2(GetDesc e GetDesc1) retorna zero para o 
/// PCI ID em e (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do adaptador e "Adaptador de Software" para a descrição 
/// do membro (Description). O GetDesc2 retorna os valores reais de hardware nível 9 nesses membros.</param>
CarenResult Shared_DXGIAdapter::GetDesc2(IDXGIAdapter2* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC2^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC2 AdapterDesc2 = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc2(&AdapterDesc2);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESC2UnManaged_ToManaged(&AdapterDesc2);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIAdapter1

/// <summary>
/// (GetDesc1) - Obtém uma descrição DXGI 1.1 de um adaptador (ou cartão de vídeo).
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC1 que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc1) retorna zeros para o 
/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC1 e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
CarenResult Shared_DXGIAdapter::GetDesc1(IDXGIAdapter1* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC1^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC1 DescAdaptador;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc1(&DescAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a esturutra e define no parametro de saida
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESC1UnManaged_ToManaged(&DescAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIAdapter

/// <summary>
/// (CheckInterfaceSupport) - Verifica se o sistema suporta uma interface do dispositivo para um componente gráfico.
/// </summary>
/// <param name="Param_GuidInterface">O GUID da interface da versão do dispositivo para a qual o suporte está sendo verificado.</param>
/// <param name="Param_Out_UMDVersion">A versão do motorista do modo de usuário do (Param_GuidInterface). Isso só é devolvido se a interface for suportada, caso contrário, este parâmetro será -12354.</param>
CarenResult Shared_DXGIAdapter::CheckInterfaceSupport(IDXGIAdapter* Param_MyPointerWork, String^ Param_GuidInterface, [Out] Int64% Param_Out_UMDVersion)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	LARGE_INTEGER LargeDados = { 0 };

	//Cria o guid
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CheckInterfaceSupport(GuidInterface, &LargeDados);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Deifine os dados no parametro de saida.
	Param_Out_UMDVersion = LargeDados.QuadPart;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (EnumOutputs) - Saídas de adaptador enumerado (cartão de vídeo).
/// </summary>
/// <param name="Param_IndexSaida">O índice da saída.</param>
/// <param name="Param_Out_Saida">O endereço de um ponteiro para uma interface ICarenDXGIOutput na posição especificada pelo parâmetro (Param_IndexSaida).</param>
CarenResult Shared_DXGIAdapter::EnumOutputs(IDXGIAdapter* Param_MyPointerWork, UInt32 Param_IndexSaida, [Out] ICarenDXGIOutput^% Param_Out_Saida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIOutput* pSaida = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->EnumOutputs(Param_IndexSaida, &pSaida);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_Saida = gcnew CarenDXGIOutput();

	//Define o ponteiro de trabalho
	Param_Out_Saida->AdicionarPonteiro(pSaida);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Obtém uma descrição DXGI 1.0 de um adaptador (ou cartão de vídeo).
/// </summary>
/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc) retorna zeros para o 
/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
CarenResult Shared_DXGIAdapter::GetDesc(IDXGIAdapter* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC^% Param_Out_DescAdaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_ADAPTER_DESC DescAdaptador;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc(&DescAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a esturutra e define no parametro de saida
	Param_Out_DescAdaptador = Util.ConverterDXGI_ADAPTER_DESCUnManaged_ToManaged(&DescAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}