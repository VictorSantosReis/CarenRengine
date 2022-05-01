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
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"


//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// 
/// </summary>
class Shared_DXGIObject
{
	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetParent(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_RIIDInterface, 
		ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	static CarenResult SetPrivateData(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidIdentificao, 
		UInt32 Param_TamanhoDados, 
		ICaren^ Param_Dados);

	/// <summary>
	/// Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetPrivateData(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidIdentificao, 
		UInt32% Param_Ref_TamanhoDados, 
		ICaren^ Param_Out_Dados);

	/// <summary>
	/// Define uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	static CarenResult SetPrivateDataInterface(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidInterface, 
		ICaren^ Param_Interface);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIDeviceSubObject
{
	//Métodos da interface(ICarenDXGIDeviceSubObject)
public:
	/// <summary>
	/// Recupera o dispositivo.
	/// </summary>
	/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
	/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetDevice(
		IDXGIDeviceSubObject* Param_MyPointerWork, 
		String^ Param_RIIDInterface, 
		ICaren^ Param_Out_Objeto);
};