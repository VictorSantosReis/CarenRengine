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


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_DXGIOutput)


// Métodos da interface ICarenDXGIOutput6

/// <summary>
/// (CheckHardwareCompositionSupport) - Notifica aplicativos de que o alongamento de hardware é suportado.
/// </summary>
/// <param name="Param_Out_FlagsSuporte">Retorna um bitfield de CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS valores de 
/// enumeração descrevendo quais tipos de composição de hardware são suportados. Os valores são bitwise OR juntos.</param>
CarenResult Shared_DXGIOutput::CheckHardwareCompositionSupport(
	IDXGIOutput6* Param_MyPointerWork,
	[Out] CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS% Param_Out_FlagsSuporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT OutFlags = 0;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CheckHardwareCompositionSupport(&OutFlags);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os flags no parametro de saida do método.
	Param_Out_FlagsSuporte = static_cast<CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS>(OutFlags);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc1) - Obtém uma descrição estendida da saída que inclui características de cores e tipo de conexão.
/// </summary>
/// <param name="Param_Out_Desc">Retorna uma estrutura com a descrição da saida.</param>
CarenResult Shared_DXGIOutput::GetDesc1(
	IDXGIOutput6* Param_MyPointerWork, 
	[Out] CA_DXGI_OUTPUT_DESC1^% Param_Out_Desc)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_OUTPUT_DESC1 OutDesc = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc1(&OutDesc);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para gerenciada e define no parametro de saida.
	Param_Out_Desc = Util.ConverterDXGI_OUTPUT_DESC1UnManaged_ToManaged(&OutDesc);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIOutput5

/// <summary>
/// Permite especificar uma lista de formatos suportados para superfícies fullscreen que podem ser devolvidas pelo objeto ICarenDXGIOutputDuplication.
/// </summary>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para 
/// processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída 
/// está conectada.</param>
/// <param name="Param_Flags">Reservado para uso futuro. Deixe como 0.</param>
/// <param name="Param_QuantidadeFormatosSuportados">Especifica o número de formatos suportados.</param>
/// <param name="Param_ListaFormatosSuportados">Uma matriz de formatos suportados que tem como contagem igual a (Param_QuantidadeFormatosSuportados).</param>
/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
CarenResult Shared_DXGIOutput::DuplicateOutput1(
	IDXGIOutput5* Param_MyPointerWork,
	ICaren^ Param_Dispositivo3D,
	UInt32 Param_Flags,
	UInt32 Param_QuantidadeFormatosSuportados,
	cli::array<CA_DXGI_FORMAT>^ Param_ListaFormatosSuportados,
	[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivoD3D = NULL;
	UINT Flags = static_cast<UINT>(Param_Flags);
	UINT CountFormatos = 0;
	DXGI_FORMAT* pArrayFormatosDXGI = CriarMatrizUnidimensional<DXGI_FORMAT>(CountFormatos);
	IDXGIOutputDuplication* pOutDuplication;

	//Copia os dados do array gerenciado para o nativo.
	Util.CopiarItensTo_ArrayNativo(&pArrayFormatosDXGI, Param_ListaFormatosSuportados, CountFormatos);

	//Recupera o ponteiro para o dispositivo D3D
	Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

	//Verifica se recuperou com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Error.. A interface não é valida.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->DuplicateOutput1(pDispositivoD3D, Flags, CountFormatos, pArrayFormatosDXGI, &pOutDuplication);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornado no parametro de saida do método
	Param_Out_SaidaDuplicada = gcnew CarenDXGIOutputDuplication();

	//Adiciona o ponteiro.
	Param_Out_SaidaDuplicada->AdicionarPonteiro(pOutDuplication);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para o array nativo se valido
	DeletarMatrizUnidimensionalSafe(&pArrayFormatosDXGI);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface ICarenDXGIOutput4


/// <summary>
/// (CheckOverlayColorSpaceSupport) - Verifica se há suporte ao espaço de cores.
/// </summary>
/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE digitado que especifica o tipo de espaço de cor 
/// para verificar o suporte de sobreposição.</param>
/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O 
/// (CheckOverlayColorSpaceSupport) retorna apenas informações de suporte sobre este dispositivo de varredura.</param>
/// <param name="Param_Out_Flags">Recebe uma variável que recebe uma combinação de valores tipo tipo de 
/// CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG que são combinados usando uma operação ou bitwise. O valor resultante 
/// especifica opções para suporte ao espaço de cores sobreposição.</param>
CarenResult Shared_DXGIOutput::CheckOverlayColorSpaceSupport(
	IDXGIOutput4* Param_MyPointerWork,
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace,
	ICaren^ Param_DispositivoD3D,
	[Out] CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG% Param_Out_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	DXGI_COLOR_SPACE_TYPE ColorSpaceType = static_cast<DXGI_COLOR_SPACE_TYPE>(Param_ColorSpace);
	IUnknown* pDispositivoD3D = NULL;
	UINT OutOverlayColorSpaceFlagSuporte = 0;

	//Recupera o ponteiro para o dispositivo
	Resultado = Param_DispositivoD3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

	//Verifica se recuperou com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Error.. A interface não é valida.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CheckOverlayColorSpaceSupport(FormatoDXGI, ColorSpaceType, pDispositivoD3D, &OutOverlayColorSpaceFlagSuporte);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a flag e define no parametro de saida do método
	Param_Out_Flags = static_cast<CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG>(OutOverlayColorSpaceFlagSuporte);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIOutput3

/// <summary>
/// (CheckOverlaySupport) - Verifica o apoio ao Overlay(Sobrepor).
/// </summary>
/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O (CheckOverlaySupport)
/// retorna apenas informações de suporte sobre este dispositivo de varredura.</param>
/// <param name="Param_Out_Flags">Recebe uma variável que recebe uma combinação de valores digitados 
/// CA_DXGI_OVERLAY_SUPPORT_FLAGque são combinados usando uma operação ou bitwise. O valor resultante especifica 
/// opções de suporte sobreposição.</param>
CarenResult Shared_DXGIOutput::CheckOverlaySupport(
	IDXGIOutput3* Param_MyPointerWork,
	CA_DXGI_FORMAT Param_Formato,
	ICaren^ Param_DispositivoD3D,
	[Out] CA_DXGI_OVERLAY_SUPPORT_FLAG% Param_Out_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	IUnknown* pDispositivoD3D = NULL;
	UINT OutOverlayFlagSuporte;

	//Recupera o ponteiro para o dispositivo
	Resultado = Param_DispositivoD3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

	//Verifica se recuperou com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Error.. A interface não é valida.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CheckOverlaySupport(FormatoDXGI, pDispositivoD3D, &OutOverlayFlagSuporte);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a flag e define no parametro de saida do método
	Param_Out_Flags = static_cast<CA_DXGI_OVERLAY_SUPPORT_FLAG>(OutOverlayFlagSuporte);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIOutput2

/// <summary>
/// (SupportsOverlays) - Consulta uma saída de adaptador para suporte de sobreposição multiplano.
/// </summary>
/// <param name="Param_Out_Suporte">Recebe TRUE se o adaptador de saída é o adaptador primário e suporta sobreposições multiplanárias, caso 
/// contrário retorna FALSE.</param>
CarenResult Shared_DXGIOutput::SupportsOverlays(
	IDXGIOutput2* Param_MyPointerWork, 
	[Out] Boolean Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	BOOL SuporteInfo = FALSE;

	//Chama o método para realizar a operação.
	SuporteInfo = Param_MyPointerWork->SupportsOverlays();

	//Define no parametro de saida
	Param_Out_Suporte = SuporteInfo ? true : false;

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIOutput1

/// <summary>
/// (DuplicateOutput) - Cria uma interface de duplicação de desktop a partir da interface ICarenDXGIOutput1 que representa uma saída de 
/// adaptador.
/// </summary>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída está conectada.</param>
/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
CarenResult Shared_DXGIOutput::DuplicateOutput(
	IDXGIOutput1* Param_MyPointerWork, 
	ICaren^ Param_Dispositivo3D, 
	[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* pDispositivoD3D = NULL;
	IDXGIOutputDuplication* pOutputDuplication = NULL;

	//Recupera o ponteiro para o dispositivo
	Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

	//Verifica se recuperou com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Error.. A interface não é valida.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->DuplicateOutput(pDispositivoD3D, &pOutputDuplication);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada pelo parametro
	Param_Out_SaidaDuplicada = gcnew CarenDXGIOutputDuplication();

	//Define o ponteiro de trabalho na interface.
	Param_Out_SaidaDuplicada->AdicionarPonteiro(pOutputDuplication);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (FindClosestMatchingMode1) - Encontra o modo de exibição que mais combina com o modo de exibição solicitado.
/// </summary>
/// <param name="Param_DescCombine">Uma estrutura CA_DXGI_MODE_DESC1 que descreve o modo de exibição para combinar. Os membros da CA_DXGI_MODE_DESC1 
/// podem ser não especificados, o que indica que não há preferência por esse membro. Um valor de 0 para Largura ou Altura indica que o valor
/// não está especificado. Se largura ou altura for 0, ambos devem ser 0. Um numerador e denominador de 0 no RefreshRate indicam que ele não 
/// está especificado. Outros membros do CA_DXGI_MODE_DESC1 possuem valores de enumeração que indicam que o membro não está especificado. 
/// Se o (Param_Dispositivo3D) for NULO, o membro (Formato) em CA_DXGI_MODE_DESC1 não pode ser CA_DXGI_FORMAT_UNKNOWN.</param>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro for NULO, o (FindClosestMatchingMode1) 
/// retorna apenas modos cujo formato corresponde ao do Param_DescCombine; caso contrário, o (FindClosestMatchingMode1) retorna apenas 
/// aos formatos suportados para escaneamento pelo dispositivo.</param>
/// <param name="Param_Out_DescCorrespondente"> Recebe uma estrutura CA_DXGI_MODE_DESC1 que contém uma descrição do modo de exibição que 
/// mais corresponde ao modo de exibição descrito no Param_DescCombine.</param>
CarenResult Shared_DXGIOutput::FindClosestMatchingMode1(
	IDXGIOutput1* Param_MyPointerWork,
	CA_DXGI_MODE_DESC1^ Param_DescCombine,
	ICaren^ Param_Dispositivo3D,
	[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivoD3D = NULL;
	DXGI_MODE_DESC1* pDescCombine;
	DXGI_MODE_DESC1 OutDescCorrespondente = { 0 };

	//Obtém um ponteiro para o dispositivo D3D se ele for valido.
	if (ObjetoGerenciadoValido(Param_Dispositivo3D))
	{
		//Obtém um ponteiro para o dispositivo.
		Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//O usuário especificou um dispositivo mais o seu ponteiro era invalido.
			//Vai sair do método para notificar.

			//Sai do método
			goto Done;
		}
	}

	//Converte a estrutura que será usada para verificar o modo de exibição.
	pDescCombine = Util.ConverterDXGI_MODE_DESC1Managed_ToUnManaged(Param_DescCombine);

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->FindClosestMatchingMode1(pDescCombine, &OutDescCorrespondente, pDispositivoD3D);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa retornada pelo método e define no parametro de saida.
	Param_Out_DescCorrespondente = Util.ConverterDXGI_MODE_DESC1UnManaged_ToManaged(&OutDescCorrespondente);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplayModeList1) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
/// </summary>
/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
/// <param name="Param_Flags">Uma combinação de valores CA_DXGI_ENUM_MODES digitados que são combinados usando uma operação ou bitwise. O valor 
/// resultante especifica opções para modos de exibição para incluir. Você deve especificar CA_DXGI_ENUM_MODES_SCALING para expor os modos 
/// de exibição que requerem dimensionamento. Os modos centrados que não requerem escala e correspondem diretamente à saída do display são 
/// enumerados por padrão.</param>
/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
/// <param name="Param_Ref_QuantidadeModos">Recebe o número de modos de exibição que o (GetDisplayModeList1) retorna no bloco de memória
/// para o qual o (Param_Out_MatrizDescModos) aponta. Defina (Param_Out_MatrizDescModos) para NULO para que o (Param_Ref_QuantidadeModos) 
/// retorne o número de modos de exibição que correspondam ao formato e às opções. Caso contrário, o (Param_Ref_QuantidadeModos) retorna o 
/// número de modos de exibição devolvidos no (Param_Out_MatrizDescModos).</param>
/// <param name="Param_Out_MatrizDescModos">Recebe uma lista de modos de exibição.</param>
CarenResult Shared_DXGIOutput::GetDisplayModeList1(
	IDXGIOutput1* Param_MyPointerWork,
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDescModos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT FlagsEnumMode = static_cast<UINT>(Param_Flags);
	UINT CountModos = static_cast<UINT>(Param_Ref_QuantidadeModos);
	DXGI_MODE_DESC1* pArrayDXGIMode = NULL;

	//Verifica se está recuperando a quantidade de modos
	if (Param_RecuperaQuantidadeModos)
	{
		//Está recuperando a quantidade de modos.
		//O array de modos é NULO.

		//Chama o método para realizar a operação.
		Hr = Param_MyPointerWork->GetDisplayModeList1(FormatoDXGI, FlagsEnumMode, &CountModos, NULL);
	}
	else
	{
		//Cria a matriz que vai conter os dados.
		pArrayDXGIMode = CriarMatrizUnidimensional<DXGI_MODE_DESC1>(CountModos);

		//Chama o método para realizar a operação.
		Hr = Param_MyPointerWork->GetDisplayModeList1(FormatoDXGI, FlagsEnumMode, &CountModos, pArrayDXGIMode);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se está recuperando a quantidade de modos e define só os parametros necessários.
	if (Param_RecuperaQuantidadeModos)
	{
		//Está recuperando a quantidade de modos.

		//Define a quantidade de modos no parametro REF do método.
		Param_Ref_QuantidadeModos = static_cast<UInt32>(CountModos);
	}
	else
	{
		//Está recuperando tudo.

		//Cria a matriz que vai conter os dados de cada matriz.
		Param_Out_MatrizDescModos = gcnew cli::array<CA_DXGI_MODE_DESC1^>(CountModos);

		//Faz um for para adicionar cada estrutura na matriz do parametro de saida.
		for (UINT i = 0; i < CountModos; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no indice.
			Param_Out_MatrizDescModos[i] = Util.ConverterDXGI_MODE_DESC1UnManaged_ToManaged(&pArrayDXGIMode[i]);
		}

		//Define a quantidade de modos no parametro REF do método.
		Param_Ref_QuantidadeModos = static_cast<UInt32>(CountModos);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Chama o método para liberar a memoria para a matriz.
	DeletarMatrizUnidimensionalSafe(&pArrayDXGIMode);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplaySurfaceData1) - Copia a superfície do display(buffer frontal) para um recurso fornecido pelo usuário.
/// </summary>
/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
/// (GetDisplaySurfaceData1) copia a superfície do display. A interface não pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
CarenResult Shared_DXGIOutput::GetDisplaySurfaceData1(
	IDXGIOutput1* Param_MyPointerWork, 
	ICarenDXGIResource^ Param_SuperficeDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIResource* pRecurso = NULL;

	//Recupera o ponteiro para o recurso
	Resultado = Param_SuperficeDestino->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o recurso não é valido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDisplaySurfaceData1(pRecurso);

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




// Métodos da interface ICarenDXGIOutput

/// <summary>
/// (FindClosestMatchingMode) - Encontra o modo de exibição que mais se corresponde ao modo de exibição solicitado.
/// </summary>
/// <param name="Param_ModoDesc">O modo de exibição desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC não podem ser especificados indicando nenhuma preferência por esse membro. Um valor de 0 para largura ou altura indica 
/// que o valor não é especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que não é especificado. Outros membros da DXGI_MODE_DESC têm valores de enumeração indicando 
/// que o membro não é especificado. Se (Param_Dispositivo3D) é NULO, formatonão pode ser DXGI_FORMAT_UNKNOWN.</param>
/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro é NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) serão devolvidos; caso contrário, apenas os formatos que 
/// são suportados para digitalização pelo dispositivo são devolvidos.</param>
CarenResult Shared_DXGIOutput::FindClosestMatchingMode(
	IDXGIOutput* Param_MyPointerWork, 
	CA_DXGI_MODE_DESC^ Param_ModoDesc, 
	[Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, 
	ICaren^ Param_Dispositivo3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_MODE_DESC* pDxgiDesc;
	DXGI_MODE_DESC dxgiDescAproxaimado = {};
	IUnknown* pDispositivo3D = NULL; //Pode ser NULO.

	//Converte a estrutura.
	pDxgiDesc = Util.ConverterDXGI_MODE_DESCManaged_ToUnManaged(Param_ModoDesc);

	//Verifica se forneceu um dispositivo.
	if (ObjetoGerenciadoValido(Param_Dispositivo3D))
	{
		//Recupera o ponteiro para o dispositivo.
		Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D);
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->FindClosestMatchingMode(pDxgiDesc, &dxgiDescAproxaimado, pDispositivo3D ? pDispositivo3D : NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura do modo aproximado se valido
	Param_Out_ModoMaisAproximado = Util.ConverterDXGI_MODE_DESCUnManaged_ToManaged(&dxgiDescAproxaimado);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a estrutura.
	DeletarEstruturaSafe(&pDxgiDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Obter uma descrição da saída.
/// </summary>
/// <param name="Param_Out_DescSaida">Retorna uma estrutura que contém a descrição da saida.</param>
CarenResult Shared_DXGIOutput::GetDesc(
	IDXGIOutput* Param_MyPointerWork, 
	[Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_OUTPUT_DESC OutDesc = {};

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDesc(&OutDesc);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_DescSaida = Util.ConverterDXGI_OUTPUT_DESCUnManaged_ToManaged(&OutDesc);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplayModeList) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
/// </summary>
/// <param name="Param_Formato">O formato de cor.</param>
/// <param name="Param_Flags">Opções para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibição que exigem escala. Os modos centrados, que não exigem escala e correspondentes diretamente à 
/// saída da tela, são enumerados por padrão.</param>
/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDescModos). Na saida contém a quantidade de dados de (Param_Out_MatrizDescModos).</param>
/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibição.</param>
CarenResult Shared_DXGIOutput::GetDisplayModeList(
	IDXGIOutput* Param_MyPointerWork,
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT Flags = static_cast<UINT>(Param_Flags);
	UINT QuantidadeModos = Param_Ref_QuantidadeModos; //Valor que é usado na entrada e na saida.
	DXGI_MODE_DESC* pArrayModeDesc = NULL;

	//Verifica como vai ser chamado o método
	if (Param_RecuperaQuantidadeModos)
	{
		//Neste caso o array é NULO e se obtém apenas a quantidade de modos.

		//Chama o método para realizar a operação
		Hr = Param_MyPointerWork->GetDisplayModeList(FormatoDXGI, Flags, &QuantidadeModos, NULL);
	}
	else
	{
		//Neste caso o array é valido e se obtém o array e a quantidade de itens no array.

		//Cria a matriz com a quantidade informada pelo usuário.
		pArrayModeDesc = CriarMatrizEstruturas<DXGI_MODE_DESC>(QuantidadeModos);

		//Chama o método para realizar a operação
		Hr = Param_MyPointerWork->GetDisplayModeList(FormatoDXGI, Flags, &QuantidadeModos, pArrayModeDesc);
	}

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os valores de saida.
	Param_Ref_QuantidadeModos = QuantidadeModos;

	//Verifica se vai retornar a matriz de modos.
	if (!Param_RecuperaQuantidadeModos)
	{
		//Vai retornar a matriz também.

		//Cria a matriz que vai conter os modos
		Param_Out_MatrizDescModos = gcnew cli::array<CA_DXGI_MODE_DESC^>(QuantidadeModos);

		//Converte os dados da estrutura nativa para a gerenciada
		for (UINT i = 0; i < QuantidadeModos; i++)
		{
			//Converte e define na matriz.
			Param_Out_MatrizDescModos[i] = Util.ConverterDXGI_MODE_DESCUnManaged_ToManaged(&pArrayModeDesc[i]);
		}
	}

Done:;
	//Libera a memoria para a matriz se valida
	DeletarMatrizEstruturasSafe(&pArrayModeDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplaySurfaceData) - Obtém uma cópia da superfície de exibição atual.
/// O método só pode ser chamado quando uma saída está no modo de tela cheia. Se o método for bem-sucedido, a DXGI preenche a superfície do destino.
/// </summary>
/// <param name="Param_SuperficeDestino">Um ponteiro para uma superfície de destino que vai receber a superfice.</param>
CarenResult Shared_DXGIOutput::GetDisplaySurfaceData(
	IDXGIOutput* Param_MyPointerWork, 
	ICarenDXGISurface^% Param_SuperficeDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pSuperfice = NULL;

	//Recupera o ponteiro para a superfice que ira receber os dados.
	Resultado = Param_SuperficeDestino->RecuperarPonteiro((LPVOID*)&pSuperfice);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetDisplaySurfaceData(pSuperfice);

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
/// (GetFrameStatistics) - Obtém estatísticas sobre quadros recentemente renderizados.
/// </summary>
/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informações.</param>
CarenResult Shared_DXGIOutput::GetFrameStatistics(
	IDXGIOutput* Param_MyPointerWork, 
	[Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FRAME_STATISTICS FrameStatistics = {};

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetFrameStatistics(&FrameStatistics);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define na estrutura de saida.
	Param_Out_EstatisticasFrame = Util.ConverterDXGI_FRAME_STATISTICSUnManaged_ToManaged(&FrameStatistics);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGammaControl) - Obtém as configurações de controle gama.
/// </summary>
/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que contém as informações do controle gamma.</param>
CarenResult Shared_DXGIOutput::GetGammaControl(
	IDXGIOutput* Param_MyPointerWork, 
	[Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL ControleGamma = DXGI_GAMMA_CONTROL();

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetGammaControl(&ControleGamma);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_ControleGamma = Util.ConverterDXGI_GAMMA_CONTROLUnManaged_ToManaged(&ControleGamma);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGammaControlCapabilities) - Obtém uma descrição das capacidades de controle gama.
/// </summary>
/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que contém as descrições das capcidades do controle Gamma.</param>
CarenResult Shared_DXGIOutput::GetGammaControlCapabilities(
	IDXGIOutput* Param_MyPointerWork, 
	[Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL_CAPABILITIES CapGammaControl = {};

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetGammaControlCapabilities(&CapGammaControl);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida
	Param_Out_GammaCaps = Util.ConverterDXGI_GAMMA_CONTROL_CAPABILITIESUnManaged_ToManaged(&CapGammaControl);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseOwnership) - Libera a propriedade da saída.
/// </summary>
CarenResult Shared_DXGIOutput::ReleaseOwnership(IDXGIOutput* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Param_MyPointerWork->ReleaseOwnership();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetDisplaySurface) - Altera o modo de exibição.
/// </summary>
/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
CarenResult Shared_DXGIOutput::SetDisplaySurface(
	IDXGIOutput* Param_MyPointerWork, 
	ICarenDXGISurface^% Param_Superfice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGISurface* pSuperfice = NULL;

	//Recupera o ponteiro para a superfice
	Resultado = Param_Superfice->RecuperarPonteiro((LPVOID*)&pSuperfice);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetDisplaySurface(pSuperfice);

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
/// (SetGammaControl) - Define os controles gama.
/// </summary>
/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
CarenResult Shared_DXGIOutput::SetGammaControl(
	IDXGIOutput* Param_MyPointerWork, 
	CA_DXGI_GAMMA_CONTROL^ Param_ControleGama)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL* pGControl;

	//Converte a estrutura.
	pGControl = Util.ConverterDXGI_GAMMA_CONTROLManaged_ToUnManaged(Param_ControleGama);

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetGammaControl(pGControl);

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
	//Libera a memoria para o ponteiro
	DeletarEstruturaSafe(&pGControl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (TakeOwnership) - Toma posse de uma saída. Quando você terminar com a saída, chame o método ICarenDXGIOutput::ReleaseOwnership().
/// Este método não deve ser chamado diretamente por aplicativos, uma vez que os resultados serão imprevisíveis. É chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transições em tela cheia, e não deve ser usado como 
/// um substituto para métodos de cadeia de swap.
/// </summary>
/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros tópicos ou aplicativos para assumir a propriedade do dispositivo; caso contrário, definido como FALSE.</param>
CarenResult Shared_DXGIOutput::TakeOwnership(
	IDXGIOutput* Param_MyPointerWork, 
	ICaren^ Param_DispositivoD3D, 
	Boolean Param_Exclusivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositovo3D = NULL;
	BOOL Exclusivo = Param_Exclusivo ? TRUE : FALSE;

	//Recupera o dispositivo.
	Resultado = Param_DispositivoD3D->RecuperarPonteiro((LPVOID*)&pDispositovo3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->TakeOwnership(pDispositovo3D, Exclusivo);

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
/// (WaitForVBlank ) - Pare um Thread até que o próximo espaço em branco vertical ocorra.
/// </summary>
CarenResult Shared_DXGIOutput::WaitForVBlank(IDXGIOutput* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->WaitForVBlank();

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