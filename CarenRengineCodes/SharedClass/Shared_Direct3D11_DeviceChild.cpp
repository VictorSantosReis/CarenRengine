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
#include "Shared_Direct3D11.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D3D11DeviceChild)

/// <summary>
/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
/// </summary>
/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
/// para transforma em sua interface original.</param>
CarenResult Shared_D3D11DeviceChild::GetDevice(
	ID3D11DeviceChild* Param_MyPointerWork, 
	ICaren^ Param_Out_DispositivoD3D11)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID3D11Device* pDevice = NULL;

	//Chama o método
	Param_MyPointerWork->GetDevice(&pDevice);

	//Verifica se a operação obteve sucesso.
	if (ObjetoValido(pDevice))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Define o ponteiro do dispositivo.
	Param_Out_DispositivoD3D11->AdicionarPonteiro(pDevice);

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (GetPrivateData) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
CarenResult Shared_D3D11DeviceChild::GetPrivateData(
	ID3D11DeviceChild* Param_MyPointerWork,
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_BufferDados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	LPVOID pDados = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Chama o método
	Hr = Param_MyPointerWork->GetPrivateData(GuidDados, &OutLarguraDados, &pDados);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o ponteiro de dados.
	Param_Out_BufferDados = gcnew CarenBuffer();

	//Define o ponteiro de dados na interface de buffer.
	Param_Out_BufferDados->CreateBuffer(IntPtr(pDados), false, OutLarguraDados, OutLarguraDados);

	//Define o tamanho real dos dados retornados.
	Param_Out_TamanhoBufferSaida = OutLarguraDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com os dados.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
CarenResult Shared_D3D11DeviceChild::SetPrivateData(
	ID3D11DeviceChild* Param_MyPointerWork,
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer, ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidDados = GUID_NULL;
	UINT OutLarguraDados = Param_TamanhoBuffer;
	PBYTE pDados = NULL;
	IntPtr PonteiroDados = IntPtr::Zero;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidDados = Util.CreateGuidFromString(Param_Guid);

	//Obtém o ponteiro para os dados.
	Resultado = Param_Buffer->GetInternalPointer(PonteiroDados);

	//Verifica se é valido
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.. O buffer não é valido.

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de dados.
	pDados = (PBYTE)PonteiroDados.ToPointer();

	//Chama o método que vai definir os dados.
	Hr = Param_MyPointerWork->SetPrivateData(GuidDados, Param_TamanhoBuffer, pDados);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
CarenResult Shared_D3D11DeviceChild::SetPrivateDataInterface(
	ID3D11DeviceChild* Param_MyPointerWork,
	String^ Param_Guid, 
	ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidAssociado = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Verifica se a string do guid é valido.
	if (String::IsNullOrEmpty(Param_Guid))
	{
		//Determina que o guid é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Cria o Guid
	GuidAssociado = Util.CreateGuidFromString(Param_Guid);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)pInterface);

	//Verifica se a interface não é invalida
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A interface é invalida

		//Sai do método
		goto Done;
	}

	//Chama o método para definir a interface.
	Hr = Param_MyPointerWork->SetPrivateDataInterface(GuidAssociado, pInterface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}