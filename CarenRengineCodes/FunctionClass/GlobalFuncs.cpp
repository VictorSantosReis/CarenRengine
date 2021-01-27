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
#include "../FunctionClass/GlobalFuncs.h"


#pragma region FUNÇÕES GLOBAIS
CarenResult DefinirPonteiroInterface(IUnknown* Param_NativePointer, ICaren^ Param_Destino, bool Param_ReleasePointerOnErro)
{
	//Variavel que retorna o resultado.
	CarenResultado Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se as interfaces são validas.
	if (!ObjetoGerenciadoValido(Param_Destino))
	{
		//Libera o ponteiro nativo se solicitado.
		if (Param_ReleasePointerOnErro)
			Param_NativePointer->Release(); Param_NativePointer = Nulo;

		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}
	if (!ObjetoValido(Param_NativePointer))
	{
		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface.
	Resultado = Param_Destino->AdicionarPonteiro(Param_NativePointer);

	//Verifica o resultado.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Verifica se deve liberar o ponteiro.
		if (Param_ReleasePointerOnErro)
		{
			//Libera o ponteiro.
			Param_NativePointer->Release();
			Param_NativePointer = NULL;
			Param_Destino->Finalizar();
			Param_Destino = nullptr;
		}
	}

Done:;
	//Retorna
	return Resultado;
}

void IniciarPropVariant(LPPROPVARIANT* Param_PropPointerInit)
{
	//Verifica se o ponteiro é válido.
	if (!ObjetoValido(Param_PropPointerInit))
		throw gcnew NullReferenceException("(IniciarPropVariant) - O ponteiro para a PROPVARIANT nativa fornecido era inválido!");

	//Aloca memória para o objeto.
	*Param_PropPointerInit = new PROPVARIANT();

	//Preenche os bytes com 0 da propvariant.
	memset(*Param_PropPointerInit, 0, sizeof(tagPROPVARIANT));
}

void DeletarPropVariant(LPPROPVARIANT* Param_PropPointer)
{
	//Verifica se o ponteiro para o ponteiro ~e valido.
	if (!ObjetoValido(Param_PropPointer))
		throw gcnew NullReferenceException("(DeletarPropVariant) - O ponteiro para a PROPVARIANT nativa fornecido era inválido!");

	//Verifica se o ponteiro aponta para uma memória que seja válida contendo a estrutura PROPVARIANT.
	if (!ObjetoValido(*Param_PropPointer))
		goto Done; //O ponteiro não leva a uma memória valida.

	//Chama o método para liberar os dados.
	PropVariantClear(*Param_PropPointer);

	//Deleta a memória utilizada para criar a variante.
	delete* Param_PropPointer;

	//Limpa
	*Param_PropPointer = Nulo;
	Param_PropPointer = Nulo;

Done:;
	//Deixa o método continuar.
}

void IniciarVariant(LPVARIANT* Param_VariantPointerInit)
{
	//Verifica se o ponteiro é válido.
	if (!ObjetoValido(Param_VariantPointerInit))
		throw gcnew NullReferenceException("(IniciarVariant) - O ponteiro para a VARIANT nativa fornecido era inválido!");

	//Aloca memória para o objeto.
	*Param_VariantPointerInit = new VARIANT();

	//Preenche os bytes com 0 da propvariant.
	memset(*Param_VariantPointerInit, 0, sizeof(tagVARIANT));
}

void DeletarVariant(LPVARIANT* Param_VariantPointer)
{
	//Verifica se o ponteiro para o ponteiro ~e valido.
	if (!ObjetoValido(Param_VariantPointer))
		throw gcnew NullReferenceException("(DeletarVariant) - O ponteiro para a PROPVARIANT nativa fornecido era inválido!");

	//Verifica se o ponteiro aponta para uma memória que seja válida contendo a estrutura PROPVARIANT.
	if (!ObjetoValido(*Param_VariantPointer))
		goto Done; //O ponteiro não leva a uma memória valida.

	//Chama o método para liberar os dados.
	VariantClear(*Param_VariantPointer);

	//Deleta a memória utilizada para criar a variante.
	delete* Param_VariantPointer;

	//Limpa
	*Param_VariantPointer = Nulo;
	Param_VariantPointer = Nulo;

Done:;
	//Deixa o método continuar.
}
#pragma endregion