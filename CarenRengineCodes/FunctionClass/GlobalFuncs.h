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

#pragma once
#include "../SDK_Base.h"
#include "../SDK_Caren.h"

//Importa o namespace base
using namespace CarenRengine;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;


//TypeDefs

//Typedef que verifica se a função falhou e pula para o label(Done:). Em caso de falha, define a variavel (Resultado) como ER_E_POINTER, caso contrario, não edita nada e deixa o método continuar.
#define SairOnError(ResultObj) if(ResultObj.StatusCode != ResultCode::SS_OK){ Resultado = CarenResult(ResultCode::ER_E_POINTER, false); goto Done; }

//Typedef que tenta recuperar um ponteiro nativo de uma interface que implementa ICaren. Pula para o label 'Done' se a interface não for valida ou ocorrer um erro na recuperação do ponteiro.
#define CarenGetPointerFromICarenSafe(CarenInterface, OutPointer) Resultado = RecuperarPonteiroCaren(CarenInterface, &OutPointer); SairOnError(Resultado); 

//Typedef que define de forma segura um ponteiro nativo em uma interface que implementa ICaren. O método pode liberar o ponteiro em caso de erro.
#define CarenSetPointerToICarenSafe(Pointer, CarenInterface, ReleasePointerOnError) Resultado = DefinirPonteiroInterface(Pointer, CarenInterface, ReleasePointerOnError);

//Typedef que tenta recuperar o ponteiro nativo para o buffer na interface (ICarenBufer). Pula para o label 'Done' se o buffer não for valido ou ocorrer um erro na recuperação do ponteiro.
#define CarenGetPointerFromICarenBufferSafe(CarenInterfaceBuffer, OutIntPtrBuffer) if(CarenInterfaceBuffer != nullptr){Resultado = CarenInterfaceBuffer->ObterPonteiroInterno(OutIntPtrBuffer); SairOnError(Resultado);}

//FUNCÕES GLOBAIS.

/// <summary>
/// Função responsável por definir um ponteiro nativo a uma interface gerenciada que tem como base a ICaren.
/// Permite informar se deve liberar o ponteiro em caso de erro.
/// </summary>
/// <param name="Param_NativePointer">O ponteiro nativo a ser definido na interface.</param>
/// <param name="Param_Destino">A interface de destino que vai receber o ponteiro.</param>
/// <param name="Param_ReleasePointerOnErro">Um valor booleano que indica se deve liberar o ponteiro em caso de falha ao definir.</param>
/// <returns></returns>
CarenResult DefinirPonteiroInterface(IUnknown* Param_NativePointer, ICaren^ Param_Destino, bool Param_ReleasePointerOnErro = true);

/// <summary>
/// Função responsável por iniciar corretamente uma estrutura PROPVARIANT.
/// </summary>
/// <param name="Param_PropPointerInit">Um ponteiro que leva a um endereço onde será criado um objeto PROPVARIANT.</param>
void IniciarPropVariant(LPPROPVARIANT* Param_PropPointerInit);

/// <summary>
/// Função responsável por deletar completamente os dados e a memória alocada para um objeto PROPVARIANT.
/// </summary>
/// <param name="Param_PropPointerInit">Um ponteiro que leva a um endereço onde está um objeto alocado PROPVARIANT.</param>
void DeletarPropVariant(LPPROPVARIANT* Param_PropPointer);

/// <summary>
/// Função responsável por iniciar corretamente uma estrutura VARIANT.
/// </summary>
/// <param name="Param_VariantPointerInit">Um ponteiro que leva a um endereço onde será criado um objeto VARIANT.</param>
void IniciarVariant(LPVARIANT* Param_VariantPointerInit);

/// <summary>
/// Função responsável por deletar completamente os dados e a memória alocada para um objeto VARIANT.
/// </summary>
/// <param name="Param_VariantPointer">Um ponteiro que leva a um endereço onde está um objeto alocado VARIANT.</param>
void DeletarVariant(LPVARIANT* Param_VariantPointer);

/// <summary>
/// Função resposável por recuperar o ponteiro nativo de uma interface baseada em ICaren.
/// </summary>
/// <typeparam name="NativePointerOut">O tipo da interface nativa de saida.</typeparam>
/// <param name="Param_Interface">A interface gerenciada que será obtida o ponteiro interno.</param>
/// <param name="Param_Out_Interface">Retorna o ponteiro para a interface nativa.</param>
/// <returns></returns>
template<class OutTypePointer> CarenResult RecuperarPonteiroCaren(ICaren^ Param_Interface, OutTypePointer** Param_Out_Interface)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se a interface gerenciada é valida
	if (!ObjetoGerenciadoValido(Param_Interface))
	{
		//Define erro.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false); 
		
		//Sai do método.
		Sair;
	}

	//Recupera o ponteiro
	Resultado = Param_Interface->RecuperarPonteiro((void**)Param_Out_Interface);

Done:;
	//Retorna
	return Resultado;
}

/// <summary>
/// Método responsável por verificar se um objeto generico é valido para um determinado tipo de destino.
/// </summary>
/// <typeparam name="T">O tipo do objeto de destino esperado.</typeparam>
/// <param name="Param_Objeto">O objeto a ser verificado.</param>
/// <returns></returns>
template<class T> BOOL VerificarGenericoValido(System::Object^ Param_Objeto)
{
	//Retorna se o objeto generico é valido para o tipo.
	return dynamic_cast<T>(Param_Objeto) != nullptr;
}