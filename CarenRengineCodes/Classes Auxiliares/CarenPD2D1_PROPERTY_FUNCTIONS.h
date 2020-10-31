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
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Em fase de verificação.
/// </summary>
public ref class CarenPD2D1_PROPERTY_FUNCTIONS
{
	//////////////////////////////////////
	//PONTEIROS NATIVOS PARA OS EVENTOS.//
	//////////////////////////////////////

	PD2D1_PROPERTY_SET_FUNCTION* PonteiroTrabalho_SET = NULL;
	PD2D1_PROPERTY_GET_FUNCTION* PonteiroTrabalho_GET = NULL;

	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenPD2D1_PROPERTY_FUNCTIONS();	

	~CarenPD2D1_PROPERTY_FUNCTIONS();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}


	// EVENTOS E DELEGATES
public:
	/// <summary>
	/// 
	/// </summary>
	delegate CarenResult DelegateOnPropertySetFunction(ICaren^ Param_Efeito, ICarenBuffer^% Param_Dados, UInt32 Param_DadosSize);

	/// <summary>
	/// 
	/// </summary>
	delegate CarenResult DelegateOnPropertyGetFunction(ICaren^% Param_Efeito, ICarenBuffer^ Param_Dados, UInt32 Param_DadosSize, UInt32 Param_DadosSizeAtual);


	/// <summary>
	/// (PD2D1_PROPERTY_SET_FUNCTION) - Evento chamado para notificar ao usuário que o Direct2D está informando os dados a serem escritos para uma propriedade.
	/// </summary>
	event DelegateOnPropertySetFunction^ OnPropertySetFunction;

	/// <summary>
	/// (PD2D1_PROPERTY_GET_FUNCTION) - Evento chamado para notificar ao usuário que o Direct2D está requsitando dados para uma propriedade.
	/// </summary>
	event DelegateOnPropertyGetFunction^ OnPropertyGetFunction;


	// DELEGATES E HANDLES NATIVAS PARA OS EVENTOS.
private:

	//Delegates

	/// <summary>
	/// Delegate nativo que vai receber a função PD2D1_PROPERTY_SET_FUNCTION.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnPropertySetFunction(
		_In_ IUnknown* effect,
		_In_reads_(dataSize) const BYTE* data,
		UINT32 dataSize);
	DelegateNativo_Evento_OnPropertySetFunction^ Callback_OnPropertySetFunction = nullptr;

	/// <summary>
	/// Delegate nativo que vai receber a função PD2D1_PROPERTY_GET_FUNCTION.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnPropertyGetFunction(
		_In_ const IUnknown* effect,
		_Out_writes_opt_(dataSize) BYTE* data,
		UINT32 dataSize,
		_Out_opt_ UINT32* actualSize);
	DelegateNativo_Evento_OnPropertyGetFunction^ Callback_OnPropertyGetFunction = nullptr;



	// Handles para os delegates

	/// <summary>
	/// Contém a Handle alocada para o delegate (Callback_OnPropertySetFunction).
	/// </summary>
	GCHandle gHandle_Delegate_OnPropertySetFunction;

	/// <summary>
	/// Contém a Handle alocada para o delegate (Callback_OnPropertyGetFunction).
	/// </summary>
	GCHandle gHandle_Delegate_OnPropertyGetFunction;



	//Métodos publicos da classe.
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();


	//Métodos internos utilizados pela biblioteca.
internal:

	//Métodos para recuperar as funções GET e SET.

	virtual PD2D1_PROPERTY_SET_FUNCTION RecuperarSetFunction();

	virtual PD2D1_PROPERTY_GET_FUNCTION RecuperarGetFunction();

	virtual void DefinirSetFunction(PD2D1_PROPERTY_SET_FUNCTION* Param_SetFunc);

	virtual void DefinirGetFunction(PD2D1_PROPERTY_GET_FUNCTION* Param_GetFunc);

	//Métodos de encaminhamento dos eventos.
	virtual HRESULT EncaminharEvento_OnPropertySetFunction(
		_In_ IUnknown* effect,
		_In_reads_(dataSize) const BYTE* data,
		UINT32 dataSize);

	virtual HRESULT EncaminharEvento_OnPropertyGetFunction(
		_In_ const IUnknown* effect,
		_Out_writes_opt_(dataSize) BYTE* data,
		UINT32 dataSize,
		_Out_opt_ UINT32* actualSize);
	
};