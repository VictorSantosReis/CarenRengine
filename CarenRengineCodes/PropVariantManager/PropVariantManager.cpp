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
	{}
		break;

		//(LVal) - Representa um valor inteiro assinado de 4 bytes. (Int32)
	case VT_I4:
		{}
		break;

		//(fltVal) - Representa um valor de ponto flutuante de 4 bytes. (float)
	case VT_R4:
		{}
		break;

		//(dblVal) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_R8:
	{}
		break;

		//(cVal) - Representa um valor assinado de 1 byte. (char)
	case VT_I1:
	{}
		break;

		//(bVal) - Representa um valor não assinado de 1 byte. (Byte)
	case VT_UI1:
	{}
		break;

		//(uiVal) - Representa um valor não assinado de 2 bytes. (UInt16)
	case VT_UI2:
	{}
		break;

		//(ulVal) - Representa um valor não assinado de 4 bytes. (UInt32)
	case VT_UI4:
	{}
		break;

		//(hVal) - Representa uma estrutra LARGE_INTEGER que contém dois valores que representam um inteiro assinado de 8 bytes. (CA_LARGE_INTEGER)
	case VT_I8:	
	{}
		break;

		//(uhVal) - RRepresenta uma estrutra ULARGE_INTEGER que contém dois valores que representam um inteiro não assinado de 8 bytes. (CA_ULARGE_INTEGER)
	case VT_UI8:
	{}
		break;

		//(intVal) - Representa um valor assinado de 4 bytes, equivalente ao VT_I4. (Int32)
	case VT_INT:
	{}
		break;

		//(uintVal) - Representa um valor não assinado de 4 bytes, equivalente ao VT_UI4. (UInt32)
	case VT_UINT:
	{}
		break;

		//(cyVal) - Representa uma estrutura CY que contém 8 Bytes de dados para Moeda. (CA_CY)
	case VT_CY:
	{}
		break;

		//(date) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_DATE:
	{}
		break;

		//(filetime) - Representa uma estrutura FILETIME. (CA_FILETIME)
	case VT_FILETIME:
	{}
		break;

		//(bstrVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_BSTR:
	{}
		break;

		//(pszVal) - Representa uma string de terminação NULA da tabela ANSI. (String.)
	case VT_LPSTR:
	{}
		break;

		//(pwszVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_LPWSTR:
	{}
		break;

		//(scode) - Representa um valor assinado de 4 bytes. (Int32)
	case VT_ERROR:
	{}
		break;

		//(boolVal) - Representa um valor pequeno de 1 byte que equivale a um Booleano. -1 == TRUE | 0 == FALSE
	case VT_BOOL:
	{}
		break;

		//(decVal) - Representa uma estrutura DECIMAL. (CA_DEC)
	case VT_DECIMAL:
	{}
		break;

		//(puuid) - Representa uma estrutura CLSID(Guid). (String)
	case VT_CLSID:
	{}
		break;

		//(pclipdata) - Representa uma estrutura CLIPDATA. (CA_CLIPDATA)
	case VT_CF:
	{}
		break;

		//(blob) - Representa uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB:
	{}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAM:
	{}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORAGE:
	{}
		break;

		//(blob) - Represneta uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB_OBJECT:
	{}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAMED_OBJECT:
	{}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORED_OBJECT:
	{}
		break;

		//(pVersionedStream) - Representa uma estrutura TagVersionedStream que contém . (ICarenStream)
	case VT_VERSIONED_STREAM:
	{}
		break;

		//(punkVal) - Representa um ponteiro para a interface base nativa IUnknown. (ICaren)
	case VT_UNKNOWN:
	{}
		break;

		//(pdispVal) - Representa um ponteiro para a interface nativa IDispatch. (ICaren)
	case VT_DISPATCH:
	{}
		break;

		//(NÃO INFORMADO) - Representa um ponteiro para uma estrutura SAFEARRAY.
	case VT_SAFEARRAY:
	{}
		break;
		
		//(NÃO INFORMADO) - Representa um erro HRESULT de 4 bytes. Deve ser do mesmo tipo que o (VT_ERROR) e o (VT_I4). (Int32)
	case VT_HRESULT:
	{}
		break;





		//Matrizes Contadas.. TIPO | VT_VECTOR



		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_VECTOR:
	{}
		break;
		




		//SAFEARRAY.. TIPO | VT_ARRAY - TODOS OS TIPOS LEVAM PARA UM (SAFEARRAY), MEMBRO (Parray)



		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_ARRAY:
	{}
		break;





		//TIPOS REFERENCIA. TIPO | VT_BYREF



		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;
		//() - Representa um valor inteiro  
	case VT_I1 | VT_BYREF:
	{}
		break;





		//TIPOS NÃO SUPORTADOS.

	case VT_BSTR_BLOB:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_BSTR_BLOB) não é valido porque é apenas de uso interno pelo sistema operacional.");
		break;

	case VT_VOID:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_VOID) não é suportado!");
		break;

	case VT_RECORD:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_RECORD) não é suportado atualmente. A documentação nativa não cita esse membro.");
		break;

	case VT_VARIANT:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_VARIANT) não é suportado puro. esse valor deve ser usado com (VT_VECTOR Ou VT_BYREF‎‎) com operador OR.");
		break;

	case VT_PTR:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_PTR) não é suportado!");
		break;

	case VT_INT_PTR:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_INT_PTR) não é suportado!");
		break;

	case VT_UINT_PTR:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_UINT_PTR) não é suportado!");
		break;

	case VT_CARRAY:
		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_CARRAY) não é suportado!");
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
