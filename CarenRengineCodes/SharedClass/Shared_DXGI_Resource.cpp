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
#include "Shared_DXGI.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_DXGIResource)


// Métodos da interface proprietária(ICarenDXGIResource1)

/// <summary>
/// (CreateSharedHandle) - Cria uma Handle para um recurso compartilhado. Em seguida, você pode usar a Handle devolvida com vários dispositivos Direct3D.
/// </summary>
/// <param name="Param_Atributos">Uma estrutura CA_SECURITY_ATTRIBUTES que contém dois membros de dados separados, mas relacionados: um descritor de segurança opcional e 
/// um valor booleano que determina se os processos crianças podem herdar a Handle devolvida.
/// Defina esse parâmetro para NULO se desejar que os processos filhos que o aplicativo possa criar não herdem a Handle retornado por CreateSharedHandle e se 
/// desejar que o recurso associado ao identificador retornado obtenha um descritor de segurança padrão.</param>
/// <param name="Param_Acesso">Os direitos de acesso solicitados ao recurso. Você pode realizar um bitwise entre as enumerações CA_ACCESS_RIGHTS e CA_DXGI_SHARED_RESOURCE_RW 
/// para definir esse parametro.</param>
/// <param name="Param_Nome">O nome do recurso para compartilhar. O nome se limita a constante MAX_PATH. A comparação de nomes é sensível ao caso(CaseSensitive).
/// Você precisará do nome de recurso se ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhadoPorNome para acessar o recurso compartilhado pelo nome. Se você, 
/// em vez disso, ligar para o método ICarenD3D11Device1::AbrirRecursoCompartilhado1 para acessar o recurso compartilhado por cabo, defina este parâmetro para NULO.</param>
/// <param name="Param_Out_Handle">Recebe o ponteiro para uma variável que recebe o valor NT HANDLE para o recurso para compartilhar. Você pode usar esta Handle em 
/// chamadas para acessar o recurso.</param>
CarenResult Shared_DXGIResource::CreateSharedHandle(
	IDXGIResource1* Param_MyPointerWork,
	CA_SECURITY_ATTRIBUTES^ Param_Atributos,
	UInt64 Param_Acesso,
	String^ Param_Nome,
	[Out] IntPtr% Param_Out_Handle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	SECURITY_ATTRIBUTES* pSecAtributes = NULL;
	LPWSTR pNome = NULL;
	HANDLE pHandleShared = NULL;

	//Verifica se foi fornecido uma estrutura de segurança
	if (ObjetoGerenciadoValido(Param_Atributos))
	{
		//Converte a estrutura gerenciada para a nativa.
		pSecAtributes = Util.ConverterSECURITY_ATTRIBUTESManagedToUnamaged(Param_Atributos);
	}

	//Verifica se forneceu um nome
	if (!String::IsNullOrEmpty(Param_Nome))
	{
		//Obtém o nome
		pNome = Util.ConverterStringToWCHAR(Param_Nome);
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CreateSharedHandle(pSecAtributes, static_cast<DWORD>(Param_Acesso), pNome, &pHandleShared);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida
	Param_Out_Handle = Util.ConverterHandleToIntPtr(pHandleShared);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Limpa os dados e libera a memoria.
	DeletarEstruturaSafe(&pSecAtributes);
	if (ObjetoValido(pNome))
	{
		//Libera a memoria.
		delete pNome;
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (CreateSubresourceSurface) - Cria um objeto de superfície subrecurso.
/// </summary>
/// <param name="Param_Index">O índice do objeto de superfície do subrecurso a ser enumerado.</param>
/// <param name="Param_Out_DXGISurface2">Recebe um ponteiro para uma interface ICarenDXGISurface2 que representa o objeto de superfície do subrecurso criado na posição 
/// especificada pelo parâmetro (Param_Index). O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult Shared_DXGIResource::CreateSubresourceSurface(
	IDXGIResource1* Param_MyPointerWork,
	UInt32 Param_Index, 
	ICaren^ Param_Out_DXGISurface2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface2* pSurfaceDXGI2 = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CreateSubresourceSurface(Param_Index, &pSurfaceDXGI2);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da superfice na interface criada pelo usuário.
	Param_Out_DXGISurface2->AdicionarPonteiro(pSurfaceDXGI2);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface ICarenDXGIResource

/// <summary>
/// (GetEvictionPriority) - Obtenha a prioridade de despejo.
/// </summary>
/// <param name="Param_Out_PrioridadeDespejo">Recebe valores da enumeração CA_DXGI_RESOURCE_PRIORITY, que determinam quando o recurso pode ser despejado.</param>
CarenResult Shared_DXGIResource::GetEvictionPriority(
	IDXGIResource* Param_MyPointerWork, 
	[Out] CA_DXGI_RESOURCE_PRIORITY% Param_Out_PrioridadeDespejo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT OutPrioridade = 0;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetEvictionPriority(&OutPrioridade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define o valor no parametro de saida.
	Param_Out_PrioridadeDespejo = static_cast<CA_DXGI_RESOURCE_PRIORITY>(OutPrioridade);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetSharedHandle) - Obtém a Handle para um recurso compartilhado.
/// [A partir do Direct3D 11.1, recomendamos não usar o (GetSharedHandle) mais para recuperar a alça a um recurso compartilhado. Em vez disso, use o 
/// ICarenDXGIResource1::CreateSharedHandle para obter uma Handle para compartilhar. Para usar o ICarenDXGIResource1::CreateSharedHandle deve especificar 
/// que ele usa Handle NT (ou seja, você define a bandeira CA_D3D11_RESOURCE_MISC_SHARED_NTHANDLE). Também recomendamos que você crie recursos compartilhados que 
/// usam Handles NT para que você possa usar CloseHandle, DuplicateHandle, e assim por diante esses recursos compartilhados.]
/// </summary>
/// <param name="Param_Out_SharedHandle">Retorna um ponteiro para a Handle compartilhada.</param>
CarenResult Shared_DXGIResource::GetSharedHandle(
	IDXGIResource* Param_MyPointerWork, 
	[Out] IntPtr% Param_Out_SharedHandle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	HANDLE pHandleShared = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetSharedHandle(&pHandleShared);

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
	Param_Out_SharedHandle = Util.ConverterHandleToIntPtr(pHandleShared);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetUsage) - Obtenha o uso esperado de recursos.
/// </summary>
/// <param name="Param_Out_Usage">Recebe uma bandeira de uso(DXGI_USAGE). Para direct3D 10, uma superfície pode ser usada como entrada sombreadora ou uma saída de 
/// destino renderizado.</param>
CarenResult Shared_DXGIResource::GetUsage(
	IDXGIResource* Param_MyPointerWork, 
	[Out] CA_DXGI_USAGE% Param_Out_Usage)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DXGI_USAGE dxgiUsage;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetUsage(&dxgiUsage);

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
	Param_Out_Usage = static_cast<CA_DXGI_USAGE>(dxgiUsage);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetEvictionPriority) - Defina a prioridade para despejar o recurso da memória.
/// </summary>
/// <param name="Param_PrioridadeDespejo">Um valor da enumeração CA_DXGI_RESOURCE_PRIORITY que define a prioridade do despejo.</param>
CarenResult Shared_DXGIResource::SetEvictionPriority(
	IDXGIResource* Param_MyPointerWork, 
	CA_DXGI_RESOURCE_PRIORITY Param_PrioridadeDespejo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT Prioridade = static_cast<UINT>(Param_PrioridadeDespejo);

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetEvictionPriority(Prioridade);

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