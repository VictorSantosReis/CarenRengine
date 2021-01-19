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
#include "../pch.h"
#include "PropVariantManager.h"

//Importa o namespace da classe atual.
using namespace CarenRengine::PropVariant;


PVOID PropVariantManager::ConverterPropVariantManaged_ToUnmanaged(CA_PROPVARIANT^ Param_Estrutura)
{
	//Variavel a ser retornada.
	PROPVARIANT* vi_Resultado = Nulo;


	//Variaveis utilizadas.
	Utilidades Util;
	VARTYPE vi_Vt = VARENUM::VT_EMPTY;

	//Verifica se a variante não é invalida.
	if (ObjetoGerenciadoValido(Param_Estrutura))
		throw gcnew NullReferenceException("O parametro (Param_Estrutura) não pode ser NULO!");

	//Obtém o tipo da variante atual.
	vi_Vt = static_cast<VARENUM>(Param_Estrutura->vt);


	//Abre um swith para verificar o tipo dos dados na variante.
	switch (vi_Vt)
	{

		//TIPOS SIMPLES.


		//(iVal) - Representa um valor inteiro assinado de 2 bytes. (Int16)
	case VT_I2:
		break;

		//(LVal) - Representa um valor inteiro assinado de 4 bytes. (Int32)
	case VT_I4:
		break;

		//(fltVal) - Representa um valor de ponto flutuante de 4 bytes. (float)
	case VT_R4:
		break;

		//(dblVal) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_R8:
		break;

		//(cVal) - Representa um valor assinado de 1 byte. (char)
	case VT_I1:
		break;

		//(bVal) - Representa um valor não assinado de 1 byte. (Byte)
	case VT_UI1:
		break;

		//(uiVal) - Representa um valor não assinado de 2 bytes. (UInt16)
	case VT_UI2:
		break;

		//(ulVal) - Representa um valor não assinado de 4 bytes. (UInt32)
	case VT_UI4:
		break;

		//(hVal) - Representa um valor assinado de 8 bytes. (Int64)
	case VT_I8:
		break;

		//(uhVal) - Representa um valor não assinado de 8 bytes. (UInt64)
	case VT_UI8:
		break;

		//(intVal) - Representa um valor assinado de 4 bytes, equivalente ao VT_I4. (Int32)
	case VT_INT:
		break;

		//(uintVal) - Representa um valor não assinado de 4 bytes, equivalente ao VT_UI4. (UInt32)
	case VT_UINT:
		break;

		//(cyVal) - Representa uma estrutura CY que contém 8 Bytes de dados para Moeda. (CA_CY)
	case VT_CY:
		break;

		//(date) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_DATE:
		break;

		//(bstrVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_BSTR:
		break;

		//(pszVal) - Representa uma string de terminação NULA da tabela ANSI. (String.)
	case VT_LPSTR:
		break;

		//(pwszVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_LPWSTR:
		break;

		//(scode) - Representa um valor assinado de 4 bytes. (Int32)
	case VT_ERROR:
		break;

		//(boolVal) - Representa um valor pequeno de 1 byte que equivale a um Booleano. -1 == TRUE | 0 == FALSE
	case VT_BOOL:
		break;

		//(decVal) - Representa uma estrutura DECIMAL. (CA_DEC)
	case VT_DECIMAL:
		break;

		//(puuid) - Representa uma estrutura CLSID(Guid). (String)
	case VT_CLSID:
		break;

		//(pclipdata) - Representa uma estrutura CLIPDATA. (CA_CLIPDATA)
	case VT_CF:
		break;

		//(blob) - Representa uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB:
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAM:
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORAGE:
		break;

	case VT_BLOB_OBJECT:
		break;

	case VT_STREAMED_OBJECT:
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORED_OBJECT:
		break;;

		//(pVersionedStream) - Representa uma estrutura TagVersionedStream que contém . (ICarenStream)
	case VT_VERSIONED_STREAM:
		break;

		//(NÃO INFORMADO) - Representa um erro HRESULT de 4 bytes. Deve ser do mesmo tipo que o (VT_ERROR) e o (VT_I4). (Int32)
	case VT_HRESULT:
		break;


	case VT_DISPATCH:
		break;

	case VT_VARIANT:
		break;
	case VT_UNKNOWN:
		break;
	case VT_VOID:
		break;
	case VT_PTR:
		break;
	case VT_SAFEARRAY:
		break;
	case VT_CARRAY:
		break;
	case VT_RECORD:
		break;
	case VT_INT_PTR:
		break;
	case VT_UINT_PTR:
		break;
	case VT_FILETIME:
		break;
	case VT_BLOB:
		break;
	case VT_STREAM:
		break;
	case VT_STORAGE:
		break;
	





		break;
	case VT_BSTR_BLOB:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_BSTR_BLOB) não é valido porque é apenas de uso interno pelo sistema operacional.");
		break;
	default:
		break;
	}

Done:;

	//Retorna o resultado
	return vi_Resultado;
}

CA_PROPVARIANT^ PropVariantManager::ConverterPropVariantUnmanaged_ToManaged(PROPVARIANT* Param_Estrutura)
{
	return nullptr;
}
