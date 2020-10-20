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
#include "..\SDK_Base.h"
#include "..\Caren\Caren.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

class PropVariantManager
{

public:
	PropVariantManager()
	{}

	~PropVariantManager()
	{}

	//Converte uma PropVariant Gerenciada para uma não gerenciada.
	bool ConvertPropVariantManagedToUnamaged(CA_PropVariant^ Param_PropVariantManaged, PROPVARIANT& Param_PropVariant)
	{
		//Variavel que vai retornar o resultado.
		bool Resultado = false;

		//Variaveis
		Utilidades Util;
		GUID GuidChave = GUID_NULL;
		BLOB BlobData = {};
		IUnknown* pInterfaceDesconhecida = NULL;
		char* StringData = NULL;
		CarenResult ResultadoCode = CarenResult(ResultCode::ER_FAIL, false);

		//Abre um switch para definir na PropVariant o valor adicional.
		switch (Param_PropVariantManaged->_TipoDados)
		{
		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_CY:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DISPATCH:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_VARIANT:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DECIMAL:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_BSTR_BLOB:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_VOID:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_EMPTY:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_NULL:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_String:
			//Define o tipo da PropVariant
			Param_PropVariant.vt = VT_LPWSTR;

			//Converter a String.
			StringData = Util.ConverterStringToChar(Param_PropVariantManaged->Var_String);

			//Converter para um WCHAR
			Param_PropVariant.pwszVal = (WCHAR*)Util.ConverterConstCharToConstWCHAR(StringData);
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int16:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_I2;

			//Define o valor da PropVariant.
			Param_PropVariant.iVal = Param_PropVariantManaged->Var_Int16;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int32:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_I4;

			//Define o valor da PropVariant.
			Param_PropVariant.lVal = Param_PropVariantManaged->Var_Int32;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int64:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_I8;

			//Define o valor da PropVariant.
			Param_PropVariant.hVal.QuadPart = Param_PropVariantManaged->Var_Int64;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt16:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UI2;

			//Define o valor da PropVariant.
			Param_PropVariant.uiVal = Param_PropVariantManaged->Var_UInt16;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt32:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UI4;

			//Define o valor da PropVariant.
			Param_PropVariant.ulVal = Param_PropVariantManaged->Var_UInt32;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt64:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UI8;

			//Define o valor da PropVariant.
			Param_PropVariant.uhVal.QuadPart = Param_PropVariantManaged->Var_UInt64;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Float:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_R4;

			//Define o valor da PropVariant.
			Param_PropVariant.fltVal = Param_PropVariantManaged->Var_Float;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Double:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_R8;

			//Define o valor da PropVariant.
			Param_PropVariant.dblVal = Param_PropVariantManaged->Var_Double;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Bool:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_BOOL;

			//Define o valor da PropVariant.
			// -1 > TRUE | 0 > FALSE
			Param_PropVariant.boolVal = Param_PropVariantManaged->Var_Bool ? -1 : 0;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Byte:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UI1;

			//Define o valor da PropVariant.
			Param_PropVariant.bVal = Param_PropVariantManaged->Var_Byte;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_SByte:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_I1;

			//Define o valor da PropVariant.
			Param_PropVariant.cVal = Param_PropVariantManaged->Var_SByte;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Blob:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_BLOB;

			//Define a largura
			BlobData.cbSize = Param_PropVariantManaged->Var_Blob->SizeData;

			//Cria o array que vai conter os dados
			BlobData.pBlobData = new BYTE[BlobData.cbSize];

			//Copia os dados para o buffer não gerenciado.
			Marshal::Copy(Param_PropVariantManaged->Var_Blob->BufferDados, 0, IntPtr(BlobData.pBlobData), BlobData.cbSize);

			//Define o valor da PropVariant.
			Param_PropVariant.blob = BlobData;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Guid:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_CLSID;

			//Cria o ponteiro par ao guid.
			Param_PropVariant.puuid = new GUID();

			//Define o valor da PropVariant
			*Param_PropVariant.puuid = Util.CreateGuidFromString(Param_PropVariantManaged->Var_Guid);
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Data:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_R8;

			//Define o valor da PropVariant.
			Param_PropVariant.dblVal = Param_PropVariantManaged->Var_Double;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_ERROR:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UI4;

			//Define o valor da PropVariant.
			Param_PropVariant.ulVal = Param_PropVariantManaged->Var_UInt32;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_HRESULT:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_I4;

			//Define o valor da PropVariant.
			Param_PropVariant.lVal = Param_PropVariantManaged->Var_Int32;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_PonteiroDesconhecido:
			//Define o tipo da PropVariant.
			Param_PropVariant.vt = VT_UNKNOWN;

			//Obtem o potneiro para a interface desconhecida.
			ResultadoCode = ((ICaren^)Param_PropVariantManaged->Var_ICaren)->RecuperarPonteiro((LPVOID*)& pInterfaceDesconhecida);

			//Verifica se obteve com sucesso
			if (ResultadoCode.StatusCode == ResultCode::SS_OK)
			{
				//Deixa o método continuar.
			}
			else
			{
				//A interface não é valida
				//Sai do método
				goto Done;
			}

			//Define o valor da PropVariant.
			Param_PropVariant.punkVal = pInterfaceDesconhecida;
			break;

		case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Desconhecido:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;

		default:
			//Não suportado.
			Resultado = false;

			//Sai do método
			goto Done;
			break;
		}

		//Define sucesso na operação
		Resultado = true;

	Done:;
		//Verifica se não houve erro e limpa alguns dados.
		if (!Resultado)
		{
			//Verifica se a string ainda é valida.
			if (StringData != NULL)
			{
				//Deleta a string.
				delete StringData;
			}
		}

		//Retorna o resultado.
		return Resultado;
	}

	//Converte uma PropVariant não gerenciada para uma gerenciada.
	CA_PropVariant^ ConvertPropVariantUnmanagedToManaged(PROPVARIANT& Param_PropVariant)
	{
		//Variavel que vai ser retornada.
		CA_PropVariant^ EstruturaRetorno = nullptr;

		//Variaveis utilziadas no método
		Utilidades Util;
		VARENUM TipoPropVar;
		CA_BlobData^ BlobBuffer;
		GUID GuidChave = GUID_NULL;

		//Obtém o tipo da variante.
		TipoPropVar = (VARENUM)Param_PropVariant.vt;

		//Cria a PropVariant
		EstruturaRetorno = gcnew CA_PropVariant();

		//Atenção: Nem todos os tipos em (VARENUM) é suportado aqui.
		//O sistema vai da suporte aos tipos principais.

		//Faz um switch para verificar o tipo do valor.
		switch (TipoPropVar)
		{

		case VT_EMPTY:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_EMPTY;
			break;

		case VT_NULL:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_NULL;
			break;

		case VT_I2: //Int16 - 2 Bytes
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int16;

			//Define o valor do dado.
			EstruturaRetorno->Var_Int16 = Param_PropVariant.iVal;
			break;

		case VT_I4: //Int32 - 4 Bytes
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int32;

			//Define o valor do dado.
			EstruturaRetorno->Var_Int32 = Param_PropVariant.lVal;
			break;

		case VT_R4: //32 Bit Float -> Double
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Double;

			//Define o valor do dado.
			EstruturaRetorno->Var_Double = Param_PropVariant.fltVal;
			break;

		case VT_R8: //64 Bit Float-> Double
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Double;

			//Define o valor do dado.
			EstruturaRetorno->Var_Double = Param_PropVariant.dblVal;
			break;

		case VT_CY: // Não Suportado.
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_CY;
			break;

		case VT_DATE:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Data;

			//Define o valor do dado.
			EstruturaRetorno->Var_Double = Param_PropVariant.dblVal; //O valor VT_DATE é representado pelo VT_R8 que é um double.
			break;

		case VT_BSTR:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_String;

			//Define o valor do dado.
			EstruturaRetorno->Var_String = gcnew String(Param_PropVariant.bstrVal);
			break;

		case VT_DISPATCH:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DISPATCH;
			break;

		case VT_ERROR: //Uint32
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_ERROR;

			//Define o valor do dado.
			EstruturaRetorno->Var_UInt32 = Param_PropVariant.scode;
			break;

		case VT_BOOL:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Bool;

			//Define o valor do dado.
			EstruturaRetorno->Var_Bool = Param_PropVariant.boolVal == -1 ? true : false;
			break;

		case VT_VARIANT:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_VARIANT;
			break;

		case VT_UNKNOWN:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_PonteiroDesconhecido;

			//Cria a classe que vai conter o ponteiro.
			EstruturaRetorno->Var_ICaren = gcnew Caren();

			//Define o valor do dado.
			((Caren^)EstruturaRetorno->Var_ICaren)->AdicionarPonteiro(Param_PropVariant.punkVal);
			break;

		case VT_DECIMAL:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DECIMAL;
			break;

		case VT_I1: //Inteiro de 1 Byte -> SByte
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_SByte;

			//Define o valor do dado.
			EstruturaRetorno->Var_SByte = Param_PropVariant.cVal;
			break;

		case VT_UI1: //Inteiro não assinado de 1 Byte -> Byte
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Byte;

			//Define o valor do dado.
			EstruturaRetorno->Var_Byte = Param_PropVariant.bVal;
			break;

		case VT_UI2: //UInt16
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt16;

			//Define o valor do dado.
			EstruturaRetorno->Var_UInt16 = Param_PropVariant.uiVal;
			break;

		case VT_UI4: //UInt32
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt32;

			//Define o valor do dado.
			EstruturaRetorno->Var_UInt32 = Param_PropVariant.ulVal;
			break;

		case VT_I8: //Int64
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int64;

			//Define o valor do dado.
			EstruturaRetorno->Var_Int64 = Param_PropVariant.hVal.QuadPart;
			break;

		case VT_UI8:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt64;

			//Define o valor do dado.
			EstruturaRetorno->Var_UInt64 = Param_PropVariant.uhVal.QuadPart;
			break;

		case VT_INT: //Int32 -> Mesmo valor que o VT_I4
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Int32;

			//Define o valor do dado.
			EstruturaRetorno->Var_Int32 = Param_PropVariant.intVal;
			break;

		case VT_UINT: //UInt32 -> Mesmo valor que o VT_UI4
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_UInt32;

			//Define o valor do dado.
			EstruturaRetorno->Var_UInt32 = Param_PropVariant.uintVal;
			break;

		case VT_VOID:
			break;
		case VT_HRESULT:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_HRESULT;

			//Define o valor do dado.
			EstruturaRetorno->Var_Int32 = Param_PropVariant.intVal;
			break;
		case VT_PTR:
			break;
		case VT_SAFEARRAY:
			break;
		case VT_CARRAY:
			break;
		case VT_USERDEFINED:
			break;
		case VT_LPSTR:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_String;

			//Define o valor do dado.
			EstruturaRetorno->Var_String = gcnew String(Param_PropVariant.pszVal);
			break;
		case VT_LPWSTR:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_String;

			//Define o valor do dado.
			EstruturaRetorno->Var_String = gcnew String(Param_PropVariant.pwszVal);
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
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Blob;

			//Cria a estrutura que vai conter os dados do buffer.
			BlobBuffer = gcnew CA_BlobData();

			//Define a largura do buffer
			BlobBuffer->SizeData = Param_PropVariant.blob.cbSize;

			//Cria o array que vai conter o buffer.
			BlobBuffer->BufferDados = gcnew cli::array<Byte>(BlobBuffer->SizeData);

			//Copia os dados para o buffer
			Marshal::Copy(IntPtr((void*)Param_PropVariant.blob.pBlobData), BlobBuffer->BufferDados, 0, BlobBuffer->SizeData);

			break;
		case VT_STREAM:
			break;
		case VT_STORAGE:
			break;
		case VT_STREAMED_OBJECT:
			break;
		case VT_STORED_OBJECT:
			break;
		case VT_BLOB_OBJECT:
			break;
		case VT_CF:
			break;
		case VT_CLSID:
			//Define o tipo de dado.
			EstruturaRetorno->_TipoDados = CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_Guid;

			//Define o valor do dado.
			EstruturaRetorno->Var_Guid = Util.ConverterGuidToString(*Param_PropVariant.puuid);
			break;
		case VT_VERSIONED_STREAM:
			break;
		case VT_BSTR_BLOB:
			break;
		case VT_VECTOR:
			break;
		case VT_ARRAY:
			break;
		case VT_BYREF:
			break;
		case VT_RESERVED:
			break;
		case VT_ILLEGAL:
			break;
		default:
			break;
		}

		//Retorna o resultado.
		return EstruturaRetorno;
	}
};
