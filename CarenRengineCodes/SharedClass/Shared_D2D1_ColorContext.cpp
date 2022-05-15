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

//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D2D1ColorContext)


// Métodos da interface (ICarenD2D1ColorContext1)

/// <summary>
/// Recupera o tipo de contexto de cor.
/// </summary>
/// <param name="Param_Out_ColorContext">Retorna o tipo de contexto de cores.</param>
void Shared_D2D1ColorContext::GetColorContextType(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_D2D1_COLOR_CONTEXT_TYPE% Param_Out_ColorContext)
{
	//Variaveis a serem utilizadas.
	D2D1_COLOR_CONTEXT_TYPE OutColorContext;

	//Chama o método para realizar a operação.
	OutColorContext = Param_MyPointerWork->GetColorContextType();

	//Define no parametro de saida.
	Param_Out_ColorContext = static_cast<CA_D2D1_COLOR_CONTEXT_TYPE>(OutColorContext);
}

/// <summary>
/// Recupera o espaço de cores DXGI deste contexto. Retorna DXGI_COLOR_SPACE_CUSTOM quando o tipo de contexto de cor é ICC.
/// </summary>
/// <param name="Param_Out_DXGIColorSpace">Retorna o espaço de cor DXGI deste contexto.</param>
void Shared_D2D1ColorContext::GetDXGIColorSpace(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_DXGI_COLOR_SPACE_TYPE% Param_Out_DXGIColorSpace)
{
	//Variaveis a serem utilizadas.
	DXGI_COLOR_SPACE_TYPE OutDxgiColorSpace;

	//Chama o método para realizar a operação.
	OutDxgiColorSpace = Param_MyPointerWork->GetDXGIColorSpace();

	//Define no parametro de saida.
	Param_Out_DXGIColorSpace = ConverterPara<CA_DXGI_COLOR_SPACE_TYPE>(OutDxgiColorSpace);
}

/// <summary>
/// Recupera um perfil de cor simples.
/// </summary>
/// <param name="Param_Out_ColorProfile">Retorna uma estrutura CA_D2D1_SIMPLE_COLOR_PROFILE que conterá o perfil de cor simples quando o método retornar.</param>
CarenResult Shared_D2D1ColorContext::GetSimpleColorProfile(ID2D1ColorContext1* Param_MyPointerWork, [Out] CA_D2D1_SIMPLE_COLOR_PROFILE^% Param_Out_ColorProfile)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIMPLE_COLOR_PROFILE OutColorProfile = { 0 };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetSimpleColorProfile(&OutColorProfile);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_ColorProfile = Util.ConverterD2D1_SIMPLE_COLOR_PROFILEUnmanagedToManaged(&OutColorProfile);

Done:;
	//Retorna o resultado.
	return Resultado;
}





// Métodos da interface (ICarenD2D1ColorContext)

/// <summary>
/// Obtém o espaço de cores do contexto de cores.
/// </summary>
/// <param name="Param_Out_EspacoCor">Retorna uma enumeração que contém o espaço de cores do contexto.</param>
void Shared_D2D1ColorContext::GetColorSpace(ID2D1ColorContext* Param_MyPointerWork, [Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor)
{
	//Variaveis a serem utilizadas.
	D2D1_COLOR_SPACE ColorSpace;

	//Chama o método para realizar a operação.
	ColorSpace = Param_MyPointerWork->GetColorSpace();

	//Define o espaço de cor no parametro de saida.
	Param_Out_EspacoCor = static_cast<CA_D2D1_COLOR_SPACE>(ColorSpace);
}

/// <summary>
/// Obtém o bytes de perfil de cor para um ICarenD2D1ColorContext1.
/// </summary>
/// <param name="Param_Out_ColorProfile">Retorna um buffer que contém o perfil de cores.</param>
/// <param name="Param_ProfileSize">O tamanho do buffer de perfil.</param>
CarenResult Shared_D2D1ColorContext::GetProfile(
	ID2D1ColorContext* Param_MyPointerWork,
	[Out] cli::array<Byte>^% Param_Out_ColorProfile,
	UInt32 Param_ProfileSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PBYTE pColorProfile = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetProfile(pColorProfile, Param_ProfileSize);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a matriz que vai ser retornada ao usuário.
	Param_Out_ColorProfile = gcnew cli::array<Byte>(Param_ProfileSize);

	//Copia os dados do buffer nativo para o gerenciado.
	Util.CopiarBufferNativo_ToGerenciado(&pColorProfile, Param_Out_ColorProfile, Param_ProfileSize);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tamanho do perfil de cor associado ao bitmap.
/// </summary>
/// <param name="Param_Out_ProfileSize">Retorna o tamanho do perfil em bytes.</param>
void Shared_D2D1ColorContext::GetProfileSize(ID2D1ColorContext* Param_MyPointerWork, [Out] UInt32% Param_Out_ProfileSize)
{
	//Chama o método para realizar a operação.
	Param_Out_ProfileSize = Param_MyPointerWork->GetProfileSize();
}