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

//MÉTODOS AUXILIARES.

_GUID PropVariantManager::CreateGuidFromString(String^ Param_DadosGuid)
{
	//Variavel que vai ser retornada.
	_GUID GuidRetorno = GUID_NULL;

	//Variavel que vai obter o resultado da criação do GUID.
	HRESULT ResultCreateCLSID = E_FAIL;

	//Variavel que vai conter os dados da String para o tipo não gerenciado.
	const char* DadosConvertidos = NULL;
	//Variavel que vai conter os dados a serem definidos no parametro de conversão da string para GUID.
	wchar_t* DadosGuid = NULL;
	//Context Marshal.
	marshal_context ctx;
	//Lagrura da string
	int LarguraString = 0;

	//Verifica se a string é valida.
	if (Param_DadosGuid != nullptr && !String::IsNullOrEmpty(Param_DadosGuid))
	{
		//Obtém a largura da String.
		LarguraString = Param_DadosGuid->Length + 1;

		//Converte os dados para um buffer de char.
		//O Proprio marshal_context destroi o buffer.
		DadosConvertidos = ctx.marshal_as<const char*>(Param_DadosGuid);

		//Aloca memoria para o Dados do Guid.
		DadosGuid = new wchar_t[LarguraString];

		//Copia os dados para o OLECHAR.
		mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

		//Chama o método que vai criar o CLSID adequado a aparti do guid
		ResultCreateCLSID = CLSIDFromString(DadosGuid, (LPCLSID)&GuidRetorno);
	}
	else
	{
		//A string não é valida
		goto Done;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (DadosGuid != NULL)
	{
		//Libera os dados.
		delete[] DadosGuid;
	}

	//Retorna o resultado
	return GuidRetorno;
}

String^ PropVariantManager::CreateStringFromGuid(_GUID Param_Guid)
{
	//Variavel a ser retornada.
	String^ RetornoDados = nullptr;

	//Variavel que vai conter os dados convertidos.
	LPOLESTR DadosConvertidos = NULL;

	//Chama o método para obter uma string a parti do GUID.
	ResultadoCOM Hr = StringFromCLSID((const IID)Param_Guid, &DadosConvertidos);

	//Verifica se obteve sucesso
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else
	{
		//A operação falhou.

		//Sai do método.
		goto Done;
	}

	//Cria e e definie os dados na String que vai conter o GUID para o usuário.
	RetornoDados = gcnew String(DadosConvertidos);

Done:;
	//Retorna os dados
	return RetornoDados;
}


//MÉTODOS DA CLASSE GERENCIADA.

PVOID PropVariantManager::ConverterPropVariantManaged_ToUnmanaged(CA_PROPVARIANT^ Param_Estrutura)
{
	//Variavel a ser retornada.
	PROPVARIANT* vi_Resultado = Nulo;

	//Variaveis utilizadas.
	VARTYPE vi_Vt = VARENUM::VT_EMPTY;
	ICaren^ vi_ICarenBaseTemp = nullptr;
	ICarenBuffer^ vi_BufferGenTemp = nullptr;
	IntPtr vi_PointerGenToNativeTemp = DefaultGenPointer;
	PVOID vi_NativePointerTemp = Nulo;
	CA_PROPVARIANT^ vi_PropVariantGenTemp = nullptr;
	CA_CAPROPVARIANT^ vi_CaPropVariantGenTemp = {};

	//Verifica se a variante não é invalida.
	if (ObjetoGerenciadoValido(Param_Estrutura))
		throw gcnew NullReferenceException("O parametro (Param_Estrutura) não pode ser NULO!");

	//Obtém o tipo da variante atual.
	vi_Vt = static_cast<VARTYPE>(Param_Estrutura->vt);

	//Inicializa a propvariant.
	PropVariantInit(vi_Resultado);

	//Define o tipo da variante.
	vi_Resultado->vt = vi_Vt;

	//Abre um swith para verificar o tipo dos dados na variante.
	switch (vi_Vt)
	{

		//TIPOS SIMPLES. 



		//(iVal) - Representa um valor inteiro assinado de 2 bytes. (Int16)
	case VT_I2:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->iVal = Param_Estrutura->iVal;
	}
		break;

		//(LVal) - Representa um valor inteiro assinado de 4 bytes. (Int32)
	case VT_I4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->lVal = static_cast<LONG>(Param_Estrutura->lVal);
	}
		break;

		//(fltVal) - Representa um valor de ponto flutuante de 4 bytes. (float)
	case VT_R4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->fltVal = Param_Estrutura->fltVal;
	}
		break;

		//(dblVal) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_R8:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->dblVal = Param_Estrutura->dblVal;
	}
		break;

		//(cVal) - Representa um valor assinado de 1 byte. (char)
	case VT_I1:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->cVal = Param_Estrutura->cVal;
	}
		break;

		//(bVal) - Representa um valor não assinado de 1 byte. (Byte)
	case VT_UI1:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->bVal = Param_Estrutura->bVal;
	}
		break;

		//(uiVal) - Representa um valor não assinado de 2 bytes. (UInt16)
	case VT_UI2:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->uiVal = Param_Estrutura->uiVal;
	}
		break;

		//(ulVal) - Representa um valor não assinado de 4 bytes. (UInt32)
	case VT_UI4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->ulVal = static_cast<ULONG>(Param_Estrutura->ulVal);
	}
		break;

		//(hVal) - Representa uma estrutra LARGE_INTEGER que contém dois valores que representam um inteiro assinado de 8 bytes. (CA_LARGE_INTEGER)
	case VT_I8:	
	{
		//Inicializa a estrutura.
		vi_Resultado->hVal = { };

		//Define os dados na estrutura.
		vi_Resultado->hVal.HighPart = Param_Estrutura->hVal.HighPart;
		vi_Resultado->hVal.LowPart = static_cast<DWORD>(Param_Estrutura->hVal.LowPart);
		vi_Resultado->hVal.QuadPart = Param_Estrutura->hVal.QuadPart;
	}
		break;

		//(uhVal) - RRepresenta uma estrutra ULARGE_INTEGER que contém dois valores que representam um inteiro não assinado de 8 bytes. (CA_ULARGE_INTEGER)
	case VT_UI8:
	{
		//Inicializa a estrutura.
		vi_Resultado->uhVal = { };

		//Define os dados na estrutura.
		vi_Resultado->uhVal.HighPart = static_cast<DWORD>(Param_Estrutura->uhVal.HighPart);
		vi_Resultado->uhVal.LowPart = static_cast<DWORD>(Param_Estrutura->uhVal.LowPart);
		vi_Resultado->uhVal.QuadPart = Param_Estrutura->uhVal.QuadPart;
	}
		break;

		//(intVal) - Representa um valor assinado de 4 bytes, equivalente ao VT_I4. (Int32)
	case VT_INT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->intVal = static_cast<INT>(Param_Estrutura->intVal);
	}
		break;

		//(uintVal) - Representa um valor não assinado de 4 bytes, equivalente ao VT_UI4. (UInt32)
	case VT_UINT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->uintVal = static_cast<UINT>(Param_Estrutura->uintVal);
	}
		break;

		//(cyVal) - Representa uma estrutura CY que contém 8 Bytes de dados para Moeda. (CA_CY)
	case VT_CY:
	{
		//Inicializa a estrutura.
		vi_Resultado->cyVal = { };

		//Define os dados na estrutura.
		vi_Resultado->cyVal.Hi = static_cast<LONG>(Param_Estrutura->cyVal.Hi);
		vi_Resultado->cyVal.int64 = Param_Estrutura->cyVal.int64;
		vi_Resultado->cyVal.Lo = static_cast<ULONG>(Param_Estrutura->cyVal.Lo);
	}
		break;

		//(date) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_DATE:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->date = Param_Estrutura->date;
	}
		break;

		//(filetime) - Representa uma estrutura FILETIME. (CA_FILETIME)
	case VT_FILETIME:
	{
		//Inicializa a estrutura.
		vi_Resultado->filetime = { };

		//Define os dados na estrutura.
		vi_Resultado->filetime.dwHighDateTime = static_cast<DWORD>(Param_Estrutura->filetime.dwHighDateTime);
		vi_Resultado->filetime.dwLowDateTime = static_cast<DWORD>(Param_Estrutura->filetime.dwLowDateTime);
	}
		break;

		//(bstrVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_BSTR:
	{
		//Verifica se a string é diferente de NULL e não vazia.
		if (!StringObjetoValido(Param_Estrutura->bstrVal))
			Sair; //O valor da string é invalido.

		//Converte a string para a bstr.
		vi_Resultado->bstrVal = reinterpret_cast<BSTR>(Marshal::StringToBSTR(Param_Estrutura->bstrVal).ToPointer());
	}
		break;

		//(pszVal) - Representa uma string de terminação NULA da tabela ANSI. (String.)
	case VT_LPSTR:
	{
		//Verifica se a string é diferente de NULL e não vazia.
		if (!StringObjetoValido(Param_Estrutura->pszVal))
			Sair; //O valor da string é invalido.

		//Converte a string para um LPSTR
		vi_Resultado->pszVal = reinterpret_cast<LPSTR>(Marshal::StringToCoTaskMemAnsi(Param_Estrutura->pszVal).ToPointer());
	}
		break;

		//(pwszVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_LPWSTR:
	{
		//Verifica se a string é diferente de NULL e não vazia.
		if (!StringObjetoValido(Param_Estrutura->pwszVal))
			Sair; //O valor da string é invalido.

		//Converte a string para um LPSTR
		vi_Resultado->pwszVal = reinterpret_cast<LPWSTR>(Marshal::StringToCoTaskMemUni(Param_Estrutura->pszVal).ToPointer());
	}
		break;

		//(scode) - Representa um valor assinado de 4 bytes. (Int32)
	case VT_ERROR:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->scode = static_cast<SCODE>(Param_Estrutura->scode);
	}
		break;

		//(boolVal) - Representa um valor pequeno de 1 byte que equivale a um Booleano. -1 == TRUE | 0 == FALSE
	case VT_BOOL:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->boolVal = Param_Estrutura->boolVal == true ? -1 : 0;
	}
		break;

		//(decVal) - Representa uma estrutura DECIMAL. (CA_DEC)
	case VT_DECIMAL:
	{
		//Inicializa a estrutura.
		vi_Resultado->decVal = { };

		//Define os dados na estrutura.
		vi_Resultado->decVal.Hi32 = static_cast<ULONG>(Param_Estrutura->decVal.Hi32);
		vi_Resultado->decVal.Lo32 = static_cast<ULONG>(Param_Estrutura->decVal.Lo32);
		vi_Resultado->decVal.Lo64 = Param_Estrutura->decVal.Lo64;
		vi_Resultado->decVal.Mid32 = static_cast<ULONG>(Param_Estrutura->decVal.Mid32);
		vi_Resultado->decVal.scale = Param_Estrutura->decVal.scale;
		vi_Resultado->decVal.sign = Param_Estrutura->decVal.sign;
		vi_Resultado->decVal.signscale = Param_Estrutura->decVal.signscale;
	}
		break;

		//(puuid) - Representa uma estrutura CLSID(Guid). (String)
	case VT_CLSID:
	{
		//Verifica se a string com o GUID é valido.
		if (!StringObjetoValido(Param_Estrutura->puuid))
			Sair; //A string com o guid não é valida.

		//Cria o CLSID a parti da string.
		vi_Resultado->puuid = &CreateGuidFromString(Param_Estrutura->puuid);
	}
		break;

		//(pclipdata) - Representa uma estrutura CLIPDATA. (CA_CLIPDATA)
	case VT_CF:
	{
		//Inicializa a estrutura.
		vi_Resultado->pclipdata = CriarEstrutura<tagCLIPDATA>();

		//Define os dados base na estrutura.
		vi_Resultado->pclipdata->cbSize = static_cast<ULONG>(Param_Estrutura->pclipdata.cbSize);
		vi_Resultado->pclipdata->ulClipFmt = static_cast<LONG>(Param_Estrutura->pclipdata.ulClipFmt);
		
		//Converte o objeto do buffer para uma interface ICarenBuffer.
		vi_BufferGenTemp = (ICarenBuffer^)Param_Estrutura->pclipdata.pClipData;

		//Obtém um ponteiro para o buffer.
		vi_BufferGenTemp->ObterPonteiroInterno(vi_PointerGenToNativeTemp);	

		//Converte para um ponteiro.
		vi_NativePointerTemp = vi_PointerGenToNativeTemp.ToPointer();

		//Cria o buffer de destino.
		vi_Resultado->pclipdata->pClipData = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->pclipdata.cbSize));

		//Copia a memória do buffer de origem para o de destino.
		CopiarMemoria(
			vi_Resultado->pclipdata->pClipData, //Buffer DESTINO
			vi_Resultado->pclipdata->cbSize,
			static_cast<PBYTE>(vi_NativePointerTemp), //Buffer ORIGEM
			Param_Estrutura->pclipdata.cbSize);

		//Limpa os dados.
		vi_BufferGenTemp = nullptr;
		vi_NativePointerTemp = Nulo;
		vi_PointerGenToNativeTemp = DefaultGenPointer;
	}
		break;

		//(blob) - Representa uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB:
	{
		//Inicializa a estrutura.
		vi_Resultado->blob = { };

		//Define os dados na estrutura.
		vi_Resultado->blob.cbSize = Param_Estrutura->blob.SizeData;

		//Converte o objeto do buffer para uma interface ICarenBuffer.
		vi_BufferGenTemp = (ICarenBuffer^)Param_Estrutura->blob.BufferDados;

		//Obtém um ponteiro para o buffer.
		vi_BufferGenTemp->ObterPonteiroInterno(vi_PointerGenToNativeTemp);

		//Converte para um ponteiro.
		vi_NativePointerTemp = vi_PointerGenToNativeTemp.ToPointer();

		//Cria o buffer de destino.
		vi_Resultado->blob.pBlobData = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->blob.SizeData));

		//Copia a memória do buffer de origem para o de destino.
		CopiarMemoria(
			vi_Resultado->blob.pBlobData, //Buffer DESTINO
			Param_Estrutura->blob.SizeData,
			static_cast<PBYTE>(vi_NativePointerTemp), //Buffer ORIGEM
			Param_Estrutura->blob.SizeData);

		//Limpa os dados.
		vi_BufferGenTemp = nullptr;
		vi_NativePointerTemp = Nulo;
		vi_PointerGenToNativeTemp = DefaultGenPointer;
	}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAM:
	{
		//Recupera o ponteiro para o IStream.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pStream))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->pStream = reinterpret_cast<IStream*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORAGE:
	{
		//Recupera o ponteiro para o IStorage.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pStorage))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->pStorage = reinterpret_cast<IStorage*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(blob) - Represneta uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB_OBJECT:
	{
		//Inicializa a estrutura.
		vi_Resultado->blob = { };

		//Define os dados na estrutura.
		vi_Resultado->blob.cbSize = Param_Estrutura->blob.SizeData;

		//Converte o objeto do buffer para uma interface ICarenBuffer.
		vi_BufferGenTemp = (ICarenBuffer^)Param_Estrutura->blob.BufferDados;

		//Obtém um ponteiro para o buffer.
		vi_BufferGenTemp->ObterPonteiroInterno(vi_PointerGenToNativeTemp);

		//Converte para um ponteiro.
		vi_NativePointerTemp = vi_PointerGenToNativeTemp.ToPointer();

		//Cria o buffer de destino.
		vi_Resultado->blob.pBlobData = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->blob.SizeData));

		//Copia a memória do buffer de origem para o de destino.
		CopiarMemoria(
			vi_Resultado->blob.pBlobData, //Buffer DESTINO
			Param_Estrutura->blob.SizeData,
			static_cast<PBYTE>(vi_NativePointerTemp), //Buffer ORIGEM
			Param_Estrutura->blob.SizeData);

		//Limpa os dados.
		vi_BufferGenTemp = nullptr;
		vi_NativePointerTemp = Nulo;
		vi_PointerGenToNativeTemp = DefaultGenPointer;
	}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAMED_OBJECT:
	{
		//Recupera o ponteiro para o IStream.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pStream))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->pStream = reinterpret_cast<IStream*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORED_OBJECT:
	{
		//Recupera o ponteiro para o IStorage.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pStorage))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->pStorage = reinterpret_cast<IStorage*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(pVersionedStream) - Representa uma estrutura TagVersionedStream que contém . (ICarenStream)
	case VT_VERSIONED_STREAM:
	{
		//Inicializa estrutura
		vi_Resultado->pVersionedStream = CriarEstrutura<tagVersionedStream>();

		//Converte o guid para o nativo.
		vi_Resultado->pVersionedStream->guidVersion = CreateGuidFromString(Param_Estrutura->pVersionedStream.guidVersion);

		//Recupera o ponteiro para o IStream.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pVersionedStream.pStream))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Define o IStream no membro da estrutura.
		vi_Resultado->pVersionedStream->pStream = reinterpret_cast<IStream*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(punkVal) - Representa um ponteiro para a interface base nativa IUnknown. (ICaren)
	case VT_UNKNOWN:
	{
		//Recupera o ponteiro para uma IUnknown.
		(reinterpret_cast<ICaren^>(Param_Estrutura->punkVal))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->punkVal = reinterpret_cast<IUnknown*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(pdispVal) - Representa um ponteiro para a interface nativa IDispatch. (ICaren)
	case VT_DISPATCH:
	{
		//Recupera o ponteiro para uma IDispatch.
		(reinterpret_cast<ICaren^>(Param_Estrutura->pdispVal))->RecuperarPonteiro(&vi_NativePointerTemp);

		//Converte e define no membro da estrutura a ser retornada.
		vi_Resultado->pdispVal = reinterpret_cast<IDispatch*>(vi_NativePointerTemp);

		//Limpa os dados.
		vi_NativePointerTemp = Nulo;
	}
		break;

		//(NÃO INFORMADO) - Representa um ponteiro para uma estrutura SAFEARRAY.
	case VT_SAFEARRAY:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->parray = Param_Estrutura->parray->PonteiroTrabalho;
	}
		break;
		
		//(NÃO INFORMADO) - Representa um erro HRESULT de 4 bytes. Deve ser do mesmo tipo que o (VT_ERROR) e o (VT_I4). (Int32)
	case VT_HRESULT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->scode = static_cast<SCODE>(Param_Estrutura->scode);
	}
		break;





		//Matrizes Contadas.. TIPO | VT_VECTOR. Todos os membros com um (ca) no inicio.



		//(cac) - Representa um estrutura CA_CAC que contém uma matriz de char.
	case VT_I1 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cac = {};

		//Define os dados na estrutura.
		vi_Resultado->cac.cElems = static_cast<ULONG>(Param_Estrutura->cac.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cac.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cac.pElems = CriarMatrizUnidimensional<CHAR>(static_cast<DWORD>(Param_Estrutura->cac.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cac.pElems, vi_Resultado->cac.pElems, Param_Estrutura->cac.cElems);
	}
		break;
		//(caub) - Representa um estrutura CA_CAUB que contém uma matriz de Bytes.
	case VT_UI1 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->caub = {};

		//Define os dados na estrutura.
		vi_Resultado->caub.cElems = static_cast<ULONG>(Param_Estrutura->caub.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->caub.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->caub.pElems = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->caub.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->caub.pElems, vi_Resultado->caub.pElems, Param_Estrutura->caub.cElems);
	}
		break;
		//(cai) - Representa um estrutura CA_CAI que contém uma matriz de inteiros assinados de 2 bytes(Int16).
	case VT_I2 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cai = {};

		//Define os dados na estrutura.
		vi_Resultado->cai.cElems = static_cast<ULONG>(Param_Estrutura->cai.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cai.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cai.pElems = CriarMatrizUnidimensional<SHORT>(static_cast<DWORD>(Param_Estrutura->cai.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cai.pElems, vi_Resultado->cai.pElems, Param_Estrutura->cai.cElems);
	}
		break;
		//(caui) - Representa um estrutura CA_CAUI que contém uma matriz de inteiros não assinados de 2 bytes(UInt16).
	case VT_UI2 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->caui = {};

		//Define os dados na estrutura.
		vi_Resultado->caui.cElems = static_cast<ULONG>(Param_Estrutura->caui.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->caui.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->caui.pElems = CriarMatrizUnidimensional<USHORT>(static_cast<DWORD>(Param_Estrutura->caui.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->caui.pElems, vi_Resultado->caui.pElems, Param_Estrutura->caui.cElems);
	}
		break;
		//(cal) - Representa um estrutura CA_CAL que contém uma matriz de inteiros assinados de 4 bytes(Int32).
	case VT_I4 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cal = {};

		//Define os dados na estrutura.
		vi_Resultado->cal.cElems = static_cast<ULONG>(Param_Estrutura->cal.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cal.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cal.pElems = CriarMatrizUnidimensional<LONG>(static_cast<DWORD>(Param_Estrutura->cal.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cal.pElems, vi_Resultado->cal.pElems, Param_Estrutura->cal.cElems);
	}
		break;
		//(caul) - Representa um estrutura CA_CAUL que contém uma matriz de inteiros não assinados de 4 bytes(UInt32).
	case VT_UI4 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->caul = {};

		//Define os dados na estrutura.
		vi_Resultado->caul.cElems = static_cast<ULONG>(Param_Estrutura->caul.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->caul.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->caul.pElems = CriarMatrizUnidimensional<ULONG>(static_cast<DWORD>(Param_Estrutura->caul.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->caul.pElems, vi_Resultado->caul.pElems, Param_Estrutura->caul.cElems);
	}
		break;
		//(cabool) - Representa um estrutura CA_CABOOL que contém uma matriz de valores Booleanos.
	case VT_BOOL | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cabool = {};

		//Define os dados na estrutura.
		vi_Resultado->cabool.cElems = static_cast<ULONG>(Param_Estrutura->cabool.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cabool.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cabool.pElems = CriarMatrizUnidimensional<SHORT>(static_cast<DWORD>(Param_Estrutura->cabool.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < Param_Estrutura->cabool.cElems; i++)
		{
			//Converte de Booleano para Short e define no array de destino.
			//-1 TRUE | 0 FALSE
			vi_Resultado->cabool.pElems[i] = Param_Estrutura->cabool.pElems[i] == true ? -1 : 0;
		}
	}
		break;
		//(caflt) - Representa um estrutura CA_CAFLT que contém uma matriz de valores reais de 4 bytes(float).
	case VT_R4 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->caflt = {};

		//Define os dados na estrutura.
		vi_Resultado->caflt.cElems = static_cast<ULONG>(Param_Estrutura->caflt.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->caflt.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->caflt.pElems = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_Estrutura->caflt.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->caflt.pElems, vi_Resultado->caflt.pElems, Param_Estrutura->caflt.cElems);
	}
		break;
		//(cadbl) - Representa um estrutura CA_CADBL que contém uma matriz de valores reais de 8 bytes(double).
	case VT_R8 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cadbl = {};

		//Define os dados na estrutura.
		vi_Resultado->cadbl.cElems = static_cast<ULONG>(Param_Estrutura->cadbl.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cadbl.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cadbl.pElems = CriarMatrizUnidimensional<double>(static_cast<DWORD>(Param_Estrutura->cadbl.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cadbl.pElems, vi_Resultado->cadbl.pElems, Param_Estrutura->cadbl.cElems);
	}
		break;
		//(cascode) - Representa um estrutura CA_CASCODE que contém uma matriz de inteiros assinados de 4 bytes(Int32).
	case VT_ERROR | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cascode = {};

		//Define os dados na estrutura.
		vi_Resultado->cascode.cElems = static_cast<ULONG>(Param_Estrutura->cascode.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cascode.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cascode.pElems = CriarMatrizUnidimensional<LONG>(static_cast<DWORD>(Param_Estrutura->cascode.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cascode.pElems, vi_Resultado->cascode.pElems, Param_Estrutura->cascode.cElems);
	}
		break;
		//(cauh) - Representa um estrutura CA_CAUH que contém uma matriz de estrutruas CA_ULARGE_INTERGER.
	case VT_UI8 | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cauh = {};

		//Define os dados na estrutura.
		vi_Resultado->cauh.cElems = static_cast<ULONG>(Param_Estrutura->cauh.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cauh.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cauh.pElems = CriarMatrizEstruturas<ULARGE_INTEGER>(static_cast<DWORD>(Param_Estrutura->cauh.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->cauh.cElems; i++)
		{
			//Inicializa a estrutura
			vi_Resultado->cauh.pElems[i] = { };

			//Define os dados.
			vi_Resultado->cauh.pElems[i].LowPart = Param_Estrutura->cauh.pElems[i].LowPart;
			vi_Resultado->cauh.pElems[i].HighPart = Param_Estrutura->cauh.pElems[i].HighPart;
			vi_Resultado->cauh.pElems[i].QuadPart = Param_Estrutura->cauh.pElems[i].QuadPart;
		}
	}
		break;
		//(cacy) - Representa um estrutura CA_CACY que contém uma matriz de estrutruas CA_CY.
	case VT_CY | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cacy = {};

		//Define os dados na estrutura.
		vi_Resultado->cacy.cElems = static_cast<ULONG>(Param_Estrutura->cacy.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cacy.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cacy.pElems = CriarMatrizEstruturas<CY>(static_cast<DWORD>(Param_Estrutura->cacy.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->cacy.cElems; i++)
		{
			//Inicializa a estrutura
			vi_Resultado->cacy.pElems[i] = { };

			//Define os dados.
			vi_Resultado->cacy.pElems[i].Hi = Param_Estrutura->cacy.pElems[i].Hi;
			vi_Resultado->cacy.pElems[i].Lo = Param_Estrutura->cacy.pElems[i].Lo;
			vi_Resultado->cacy.pElems[i].int64 = Param_Estrutura->cacy.pElems[i].int64;
		}
	}
		break;
		//(cadate) - Representa uma estrutura CA_CADATE que contém uma matriz de valores reais de 8 bytes cada.
	case VT_DATE | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cadate = {};

		//Define os dados na estrutura.
		vi_Resultado->cadate.cElems = static_cast<ULONG>(Param_Estrutura->cadate.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cadate.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cadate.pElems = CriarMatrizUnidimensional<double>(static_cast<DWORD>(Param_Estrutura->cadate.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		CopiarBufferGerenciadoToNativo(Param_Estrutura->cadate.pElems, vi_Resultado->cadate.pElems, Param_Estrutura->cadate.cElems);
	}
		break;
		//(cafiletime) - Representa uma estrutura CA_CAFILETIME que contém uma matriz de estrutruas CA_FILETIME.
	case VT_FILETIME | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cafiletime = {};

		//Define os dados na estrutura.
		vi_Resultado->cafiletime.cElems = static_cast<ULONG>(Param_Estrutura->cafiletime.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cafiletime.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cafiletime.pElems = CriarMatrizEstruturas<FILETIME>(static_cast<DWORD>(Param_Estrutura->cafiletime.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->cafiletime.cElems; i++)
		{
			//Inicializa a estrutura
			vi_Resultado->cafiletime.pElems[i] = { };

			//Define os dados.
			vi_Resultado->cafiletime.pElems[i].dwLowDateTime = Param_Estrutura->cafiletime.pElems[i].dwLowDateTime;
			vi_Resultado->cafiletime.pElems[i].dwHighDateTime = Param_Estrutura->cafiletime.pElems[i].dwHighDateTime;
		}
	}
		break;
		//(cauuid) - Representa uma estrutura CA_CACLSID que contém uma matriz de GUIDs, implementados como System::String no gerenciado.
	case VT_CLSID | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cauuid = {};

		//Define os dados na estrutura.
		vi_Resultado->cauuid.cElems = static_cast<ULONG>(Param_Estrutura->cauuid.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cauuid.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cauuid.pElems = CriarMatrizUnidimensional<CLSID>(static_cast<DWORD>(Param_Estrutura->cauuid.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->cauuid.cElems; i++)
		{
			//Converte e define os dados.
			vi_Resultado->cauuid.pElems[i] = CreateGuidFromString(Param_Estrutura->cauuid.pElems[i]);
		}
	}
		break;
		//(caclipdata) - Representa uma estrutura CA_CACLIPDATA que contém uma matriz de estruturas CA_CLIPDATA.
	case VT_CF | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->caclipdata = {};

		//Define os dados na estrutura.
		vi_Resultado->caclipdata.cElems = static_cast<ULONG>(Param_Estrutura->caclipdata.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->caclipdata.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->caclipdata.pElems = CriarMatrizEstruturas<CLIPDATA>(static_cast<DWORD>(Param_Estrutura->caclipdata.cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->caclipdata.cElems; i++)
		{
			//Inicializa a estrutura.
			vi_Resultado->caclipdata.pElems[i] = {};

			//Define os dados Base.
			vi_Resultado->caclipdata.pElems[i].cbSize = Param_Estrutura->caclipdata.pElems[i].cbSize;
			vi_Resultado->caclipdata.pElems[i].ulClipFmt = Param_Estrutura->caclipdata.pElems[i].ulClipFmt;

			//Verifica se o buffer é valido, se não for vai para o proximo laço de verificação.
			if (!ObjetoGerenciadoValido(Param_Estrutura->caclipdata.pElems[i].pClipData))
				continue; //Pula para o proximo laço

			//Obtém a interface que contém o buffer.
			vi_BufferGenTemp = (ICarenBuffer^)Param_Estrutura->caclipdata.pElems[i].pClipData;

			//Obtém um ponteiro para os dados.
			vi_BufferGenTemp->ObterPonteiroInterno(vi_PointerGenToNativeTemp);

			//Converte o intptr em um ponteiro nativo.
			vi_NativePointerTemp = vi_PointerGenToNativeTemp.ToPointer();

			//Cria o buffer de destino que vai receber os dados.
			vi_Resultado->caclipdata.pElems[i].pClipData = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(vi_Resultado->caclipdata.pElems[i].cbSize));

			//Copia os dados do buffer de origem para o buffer de destino.
			CopiarMemoria(
				vi_Resultado->caclipdata.pElems[i].pClipData, //Buffer de DESTINO.
				vi_Resultado->caclipdata.pElems[i].cbSize, 
				static_cast<BYTE*>(vi_NativePointerTemp), //Buffer de ORIGEM.
				vi_Resultado->caclipdata.pElems[i].cbSize);

			//Limpa os dados.
			vi_BufferGenTemp = nullptr;
			vi_PointerGenToNativeTemp = DefaultGenPointer;
			vi_NativePointerTemp = Nulo;
		}
	}
		break;
		//(cabstr) - Representa uma estrutura CA_CABSTR que contém uma matriz de strings BSTR Unicode, implementados como System::String no gerenciado. 
	case VT_BSTR | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->cabstr = {};

		//Define os dados na estrutura.
		vi_Resultado->cabstr.cElems = static_cast<ULONG>(Param_Estrutura->cabstr.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->cabstr.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->cabstr.pElems = CriarMatrizPonteiros<WCHAR>(Param_Estrutura->cabstr.cElems);

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->cabstr.cElems; i++)
		{
			//Converte e define os dados.
			vi_Resultado->cabstr.pElems[i] = static_cast<BSTR>(Marshal::StringToBSTR(Param_Estrutura->cabstr.pElems[i]).ToPointer());
		}
	}
		break;
		//(calpstr) - Representa uma estrutura CA_CALPSTR que contém uma matriz de char* ANSI, implementados como System::String no gerenciado. 
	case VT_LPSTR | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->calpstr = {};

		//Define os dados na estrutura.
		vi_Resultado->calpstr.cElems = static_cast<ULONG>(Param_Estrutura->calpstr.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->calpstr.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->calpstr.pElems = CriarMatrizPonteiros<CHAR>(Param_Estrutura->calpstr.cElems);

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->calpstr.cElems; i++)
		{
			//Converte e define os dados.
			vi_Resultado->calpstr.pElems[i] = static_cast<LPSTR>(Marshal::StringToCoTaskMemAnsi(Param_Estrutura->calpstr.pElems[i]).ToPointer());
		}
	}
		break;
		//(calpwstr) - Representa uma estrutura CA_CALPWSTR que contém uma matriz de WCHAR* Unicode, implementados como System::String no gerenciado. 
	case VT_LPWSTR | VT_VECTOR:
	{
		//Inicializa a estrutura.
		vi_Resultado->calpwstr = {};

		//Define os dados na estrutura.
		vi_Resultado->calpwstr.cElems = static_cast<ULONG>(Param_Estrutura->calpwstr.cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->calpwstr.pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->calpwstr.pElems = CriarMatrizPonteiros<WCHAR>(Param_Estrutura->calpwstr.cElems);

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->calpwstr.cElems; i++)
		{
			//Converte e define os dados.
			vi_Resultado->calpwstr.pElems[i] = static_cast<LPWSTR>(Marshal::StringToCoTaskMemUni(Param_Estrutura->calpwstr.pElems[i]).ToPointer());
		}
	}
		break;
		//(capropvar) - Representa uma estrutura CA_CAPROPVARIANT que contém uma matriz de estruturas CA_PROPVARIANT.
	case VT_VARIANT | VT_VECTOR:
	{
		//Converte o objeto para sua representação real.
		vi_CaPropVariantGenTemp = (CA_CAPROPVARIANT^)Param_Estrutura->capropvar;

		//Inicializa a estrutura.
		vi_Resultado->capropvar = {};

		//Define os dados na estrutura.
		vi_Resultado->capropvar.cElems = static_cast<ULONG>(vi_CaPropVariantGenTemp->cElems);

		//Verififica se o buffer de origem é valido.
		if (!ObjetoGerenciadoValido(vi_CaPropVariantGenTemp->pElems))
			Sair; // O buffer de origem não é valido.

		//Cria o buffer de destino.
		vi_Resultado->capropvar.pElems = CriarMatrizEstruturas<PROPVARIANT>(static_cast<DWORD>(vi_CaPropVariantGenTemp->cElems));

		//Cópia os dados do buffer de origem para o de destino.
		for (ULONG i = 0; i < vi_Resultado->capropvar.cElems; i++)
		{
			//Converte a estrutura e define no index de destino.
			vi_Resultado->capropvar.pElems[i] = *(static_cast<PROPVARIANT*>(ConverterPropVariantManaged_ToUnmanaged(vi_CaPropVariantGenTemp->pElems[i])));
		}
	}
		break;
		




		//SAFEARRAY.. TIPO | VT_ARRAY - TODOS OS TIPOS LEVAM PARA UM (SAFEARRAY), MEMBRO (Parray)



		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 1 byte (char).
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 1 byte (Byte).
	case VT_UI1 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 2 bytes (Int16).
	case VT_I2 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 2 bytes (UInt16).
	case VT_UI2 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 4 bytes (Int32).
	case VT_I4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 4 bytes (UInt32).
	case VT_UI4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 4 bytes (Int32).
	case VT_INT | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 4 bytes (UInt32). 
	case VT_UINT | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 4 bytes (float). 
	case VT_R4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 8 bytes (double).
	case VT_R8 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores booleanos (Boolean).
	case VT_BOOL | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas DECIMAL (CA_DEC).
	case VT_DECIMAL | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros de 4 bytes (Int32).
	case VT_ERROR | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas CY (CA_CY).
	case VT_CY | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 8 bytes (double).
	case VT_DATE | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de BSTRs da tabela Unicode (String).
	case VT_BSTR | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de ponteiros para a interface IDispatch (ICaren).
	case VT_DISPATCH | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de ponteiros para a interface IUnknown (ICaren).
	case VT_UNKNOWN | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas VARIANT (CA_VARIANT).
	case VT_VARIANT | VT_ARRAY:
	{}
		break;





		//TIPOS REFERENCIA. TIPO | VT_BYREF. Quase todos os membros com um (*p) no inicio.



		//(pcVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 1 byte (char).
	case VT_I1 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pcVal = new CHAR(const_cast<CHAR&>(Param_Estrutura->pcVal));
	}
	break;
	//(pbVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 1 byte (Byte).
	case VT_UI1 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pbVal = new UCHAR(const_cast<UCHAR&>(Param_Estrutura->pbVal));
	}
	break;
	//(piVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 2 bytes (Int16).
	case VT_I2 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->piVal = new SHORT(const_cast<SHORT&>(Param_Estrutura->piVal));
	}
	break;
	//(puiVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 2 bytes (UInt16).
	case VT_UI2 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->puiVal = new USHORT(const_cast<USHORT&>(Param_Estrutura->puiVal));
	}
	break;
	//(plVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_I4 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->plVal = new LONG(static_cast<LONG>(Param_Estrutura->plVal));
	}
	break;
	//(pulVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 4 bytes (UInt32).
	case VT_UI4 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pulVal = new ULONG(static_cast<ULONG>(Param_Estrutura->pulVal));
	}
	break;
	//(pintVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_INT | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pintVal = new INT(const_cast<int&>(Param_Estrutura->pintVal));
	}
	break;
	//(puintVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 4 bytes (UInt32).
	case VT_UINT | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->puintVal = new UINT(const_cast<UINT&>(Param_Estrutura->puintVal));
	}
	break;
	//(pfltVal) - Representa um ponteiro(referência) que leva para um valor real de 4 bytes (float).
	case VT_R4 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pfltVal = new FLOAT(const_cast<FLOAT&>(Param_Estrutura->pfltVal));
	}
	break;
	//(pdblVal) - Representa um ponteiro(referência) que leva para um valor real de 8 bytes (double).
	case VT_R8 | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pdblVal = new DOUBLE(const_cast<DOUBLE&>(Param_Estrutura->pdblVal));
	}
	break;
	//(pboolVal) - Representa um ponteiro(referência) que leva para um valor booleano (Boolean).
	case VT_BOOL | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pboolVal = new SHORT(Param_Estrutura->pboolVal == true ? -1 : 0);
	}
	break;
	//(pdecVal) - Representa um ponteiro(referência) que leva para uma estrutura DECIMAL (CA_DEC).
	case VT_DECIMAL | VT_BYREF:
	{
		//Inicializa a estrutura.
		vi_Resultado->pdecVal = new DECIMAL();

		//Define os dados.
		vi_Resultado->pdecVal->Hi32 = static_cast<ULONG>(Param_Estrutura->pdecVal.Hi32);
		vi_Resultado->pdecVal->Mid32 = static_cast<ULONG>(Param_Estrutura->pdecVal.Mid32);
		vi_Resultado->pdecVal->Lo32 = static_cast<ULONG>(Param_Estrutura->pdecVal.Lo32);
		vi_Resultado->pdecVal->Lo64 = Param_Estrutura->pdecVal.Lo64;
		vi_Resultado->pdecVal->scale = Param_Estrutura->pdecVal.scale;
		vi_Resultado->pdecVal->sign = Param_Estrutura->pdecVal.sign;
		vi_Resultado->pdecVal->signscale = Param_Estrutura->pdecVal.signscale;
	}
	break;
	//(pscode) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_ERROR | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pscode = new SCODE(static_cast<SCODE>(Param_Estrutura->pscode));
	}
	break;
	//(pcyVal) - Representa um ponteiro(referência) que leva para uma estrutura CY (CA_CY).
	case VT_CY | VT_BYREF:
	{
		//Inicializa a estrutura.
		vi_Resultado->pcyVal = new CY();

		//Define os dados.
		vi_Resultado->pcyVal->Hi = static_cast<LONG>(Param_Estrutura->pcyVal.Hi);
		vi_Resultado->pcyVal->Lo = static_cast<ULONG>(Param_Estrutura->pcyVal.Hi);
		vi_Resultado->pcyVal->int64 = Param_Estrutura->pcyVal.int64;
	}
	break;
	//(pdate) - Representa um ponteiro(referência) que leva para um valor real de 8 bytes (double).
	case VT_DATE | VT_BYREF:
	{
		//Define os dados no membro da estrutura.
		vi_Resultado->pdate = new DOUBLE(Param_Estrutura->pdate);
	}
	break;
	//(pbstrVal) - Representa um ponteiro(referência) que leva para um valor BSTR da tabela Unicode (String).
	case VT_BSTR | VT_BYREF:
	{
		//Verifica se os dados são validos.
		if (!ObjetoGerenciadoValido(Param_Estrutura->pbstrVal))
			Sair; //Ponteiro inválido.

		//Converte os dados e define no membro da estrutura
		vi_Resultado->pbstrVal = new BSTR(static_cast<BSTR>(Marshal::StringToBSTR(Param_Estrutura->pbstrVal).ToPointer()));
	}
	break;
	//(ppunkVal) - Representa um ponteiro(referência) que leva para um ponteiro que contém uma interface IUnknown (ICaren).
	case VT_UNKNOWN | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (Param_Estrutura->ppunkVal == IntPtr::Zero)
			Sair; //Ponteiro inválido.

		//Converte o IntPtr
		vi_NativePointerTemp = Param_Estrutura->ppunkVal.ToPointer();

		//Adiciona uma referência.
		((IUnknown*)vi_NativePointerTemp)->AddRef();

		//Define o ponteiro no membro da estrutura.
		vi_Resultado->ppunkVal = reinterpret_cast<IUnknown**>(&vi_NativePointerTemp);
	}
	break;
	//(ppdispVal) - Representa um ponteiro(referência) que leva para um ponteiro que contém uma interface IDispath (ICaren).
	case VT_DISPATCH | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (Param_Estrutura->ppdispVal == IntPtr::Zero)
			Sair; //Ponteiro inválido.

		//Converte o IntPtr
		vi_NativePointerTemp = Param_Estrutura->ppdispVal.ToPointer();

		//Adiciona uma referência.
		((IDispatch*)vi_NativePointerTemp)->AddRef();

		//Define o ponteiro no membro da estrutura.
		vi_Resultado->ppdispVal = reinterpret_cast<IDispatch**>(&vi_NativePointerTemp);
	}
	break;
	//(pparray) - Representa um ponteiro(referência) que leva para uma estrutura SAFEARRAY (CA_SAFEARRAY).
	case VT_ARRAY | VT_BYREF:
	{
		//Verifica se o objeto é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->pparray))
			Sair; //Objeto invalido.

		//Cria o safearray que vai conter os dados.
		vi_Resultado->pparray = new LPSAFEARRAY();

		//Cria uma copia do safe array.
		Param_Estrutura->pparray->CopyTo(vi_Resultado->pparray);
	}
	break;
	//(pvarVal) - Representa um ponteiro(referência) que leva para uma estrutura PROPVARIANT (CA_PROPVARIANT).
	case VT_VARIANT | VT_BYREF:
	{
		//Verifica se o objeto é valido.
		if (!ObjetoGerenciadoValido(Param_Estrutura->pvarVal))
			Sair; //Objeto invalido.

		//Converte e define no membro da estrutura.
		vi_Resultado->pvarVal = static_cast<PROPVARIANT*>(ConverterPropVariantManaged_ToUnmanaged(Param_Estrutura->pvarVal));
	}
	break;





		//TIPOS NÃO SUPORTADOS.

	case VT_BSTR_BLOB:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_BSTR_BLOB) não é valido porque é apenas de uso interno pelo sistema operacional.");
		break;

	case VT_VOID:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_VOID) não é suportado!");
		break;

	case VT_RECORD:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_RECORD) não é suportado atualmente. A documentação nativa não cita esse membro.");
		break;

	case VT_VARIANT:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_VARIANT) não é suportado puro. Esse valor deve ser usado com (VT_VECTOR ou VT_BYREF) com operador OR.");
		break;

	case VT_PTR:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_PTR) não é suportado!");
		break;

	case VT_INT_PTR:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_INT_PTR) não é suportado!");
		break;

	case VT_UINT_PTR:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_UINT_PTR) não é suportado!");
		break;

	case VT_CARRAY:
		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);

		//Chama uma exceção porque o tipo não é suportado.
		throw gcnew Exception("O tipo de variante (VT_CARRAY) não é suportado!");
		break;

	default:
		//TIPO DESCONHECIDO!!

		//Libera a propvariant criada anteriormente.
		PropVariantClear(vi_Resultado);
		break;
	}

Done:;

	//Retorna o resultado
	return vi_Resultado;
}

CA_PROPVARIANT^ PropVariantManager::ConverterPropVariantUnmanaged_ToManaged(PROPVARIANT* Param_Estrutura)
{
	//Variavel a ser retornada.
	CA_PROPVARIANT^ vi_Resultado = nullptr;

	//Variaveis utilizadas.
	VARTYPE vi_Vt = VARENUM::VT_EMPTY;
	tagSTATSTG vi_StatStream = {};
	CA_CAPROPVARIANT^ vi_TempCaPropVariant = nullptr;

	//Verifica se a variante não é invalida.
	if (ObjetoValido(Param_Estrutura))
		throw gcnew NullReferenceException("O parametro (Param_Estrutura) não pode ser NULO!");

	//Obtém o tipo da variante atual.
	vi_Vt = static_cast<VARTYPE>(Param_Estrutura->vt);

	//Cria a propvariant.
	vi_Resultado = gcnew CA_PROPVARIANT();

	//Define o tipo da propvariant.
	vi_Resultado->vt = static_cast<CA_VARTYPE>(vi_Vt);

	//Abre um swith para verificar o tipo dos dados na variante.
	switch (vi_Vt)
	{

		//TIPOS SIMPLES. 



		//(iVal) - Representa um valor inteiro assinado de 2 bytes. (Int16)
	case VT_I2:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->iVal = Param_Estrutura->iVal;
	}
	break;

	//(LVal) - Representa um valor inteiro assinado de 4 bytes. (Int32)
	case VT_I4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->lVal = static_cast<int>(Param_Estrutura->lVal);
	}
	break;

	//(fltVal) - Representa um valor de ponto flutuante de 4 bytes. (float)
	case VT_R4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->fltVal = Param_Estrutura->fltVal;
	}
	break;

	//(dblVal) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_R8:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->dblVal = Param_Estrutura->dblVal;
	}
	break;

	//(cVal) - Representa um valor assinado de 1 byte. (char)
	case VT_I1:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->cVal = Param_Estrutura->cVal;
	}
	break;

	//(bVal) - Representa um valor não assinado de 1 byte. (Byte)
	case VT_UI1:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->bVal = Param_Estrutura->bVal;
	}
	break;

	//(uiVal) - Representa um valor não assinado de 2 bytes. (UInt16)
	case VT_UI2:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->uiVal = Param_Estrutura->uiVal;
	}
	break;

	//(ulVal) - Representa um valor não assinado de 4 bytes. (UInt32)
	case VT_UI4:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->ulVal = static_cast<UInt32>(Param_Estrutura->ulVal);
	}
	break;

	//(hVal) - Representa uma estrutra LARGE_INTEGER que contém dois valores que representam um inteiro assinado de 8 bytes. (CA_LARGE_INTEGER)
	case VT_I8:
	{
		//Inicializa a estrutura.
		vi_Resultado->hVal = CA_LARGE_INTEGER();

		//Define os dados na estrutura.
		vi_Resultado->hVal.HighPart = static_cast<int>(Param_Estrutura->hVal.HighPart);
		vi_Resultado->hVal.LowPart = static_cast<UInt32>(Param_Estrutura->hVal.LowPart);
		vi_Resultado->hVal.QuadPart = Param_Estrutura->hVal.QuadPart;
	}
	break;

	//(uhVal) - RRepresenta uma estrutra ULARGE_INTEGER que contém dois valores que representam um inteiro não assinado de 8 bytes. (CA_ULARGE_INTEGER)
	case VT_UI8:
	{
		//Inicializa a estrutura.
		vi_Resultado->uhVal = CA_ULARGE_INTEGER();

		//Define os dados na estrutura.
		vi_Resultado->uhVal.HighPart = static_cast<UInt32>(Param_Estrutura->uhVal.HighPart);
		vi_Resultado->uhVal.LowPart = static_cast<UInt32>(Param_Estrutura->uhVal.LowPart);
		vi_Resultado->uhVal.QuadPart = Param_Estrutura->uhVal.QuadPart;
	}
	break;

	//(intVal) - Representa um valor assinado de 4 bytes, equivalente ao VT_I4. (Int32)
	case VT_INT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->intVal = static_cast<int>(Param_Estrutura->intVal);
	}
	break;

	//(uintVal) - Representa um valor não assinado de 4 bytes, equivalente ao VT_UI4. (UInt32)
	case VT_UINT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->uintVal = static_cast<UInt32>(Param_Estrutura->uintVal);
	}
	break;

	//(cyVal) - Representa uma estrutura CY que contém 8 Bytes de dados para Moeda. (CA_CY)
	case VT_CY:
	{
		//Inicializa a estrutura.
		vi_Resultado->cyVal = CA_CY();

		//Define os dados na estrutura.
		vi_Resultado->cyVal.Hi = static_cast<int>(Param_Estrutura->cyVal.Hi);
		vi_Resultado->cyVal.int64 = Param_Estrutura->cyVal.int64;
		vi_Resultado->cyVal.Lo = static_cast<UInt32>(Param_Estrutura->cyVal.Lo);
	}
	break;

	//(date) - Representa um valor de ponto flutuante de 8 bytes. (double)
	case VT_DATE:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->date = Param_Estrutura->date;
	}
	break;

	//(filetime) - Representa uma estrutura FILETIME. (CA_FILETIME)
	case VT_FILETIME:
	{
		//Inicializa a estrutura.
		vi_Resultado->filetime = CA_FILETIME();

		//Define os dados na estrutura.
		vi_Resultado->filetime.dwHighDateTime = static_cast<UInt32>(Param_Estrutura->filetime.dwHighDateTime);
		vi_Resultado->filetime.dwLowDateTime = static_cast<UInt32>(Param_Estrutura->filetime.dwLowDateTime);
	}
	break;

		//(bstrVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_BSTR:
	{
		//Verifica se os dados são validos
		if (!ObjetoValido(Param_Estrutura->bstrVal))
			Sair; //A string não é vãlida.

		//Define os dados na estrutura
		vi_Resultado->bstrVal = gcnew String(vi_Resultado->bstrVal);
	}
		break;

		//(pszVal) - Representa uma string de terminação NULA da tabela ANSI. (String.)
	case VT_LPSTR:
	{
		//Verifica se os dados são validos
		if (!ObjetoValido(Param_Estrutura->pszVal))
			Sair; //A string não é vãlida.

		//Define os dados na estrutura
		vi_Resultado->pszVal = Marshal::PtrToStringAnsi(IntPtr(Param_Estrutura->pszVal));
	}
		break;

		//(pwszVal) - Representa uma string de terminação NULA da tabela Unicode. (String)
	case VT_LPWSTR:
	{
		//Verifica se os dados são validos
		if (!ObjetoValido(Param_Estrutura->pwszVal))
			Sair; //A string não é vãlida.

		//Define os dados na estrutura
		vi_Resultado->pwszVal = Marshal::PtrToStringAnsi(IntPtr(Param_Estrutura->pwszVal));
	}
		break;

		//(scode) - Representa um valor assinado de 4 bytes. (Int32)
	case VT_ERROR:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->scode = static_cast<UInt32>(Param_Estrutura->scode);
	}
		break;

		//(boolVal) - Representa um valor pequeno de 1 byte que equivale a um Booleano. -1 == TRUE | 0 == FALSE
	case VT_BOOL:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->boolVal = Param_Estrutura->boolVal == -1? true: false;
	}
		break;

		//(decVal) - Representa uma estrutura DECIMAL. (CA_DEC)
	case VT_DECIMAL:
	{
		//Inicializa a estrutura.
		vi_Resultado->decVal = CA_DEC();

		//Define os dados na estrutura.
		vi_Resultado->decVal.Hi32 = static_cast<UInt32>(Param_Estrutura->decVal.Hi32);
		vi_Resultado->decVal.Lo32 = static_cast<UInt32>(Param_Estrutura->decVal.Lo32);
		vi_Resultado->decVal.Lo64 = Param_Estrutura->decVal.Lo64;
		vi_Resultado->decVal.Mid32 = static_cast<UInt32>(Param_Estrutura->decVal.Mid32);
		vi_Resultado->decVal.scale = Param_Estrutura->decVal.scale;
		vi_Resultado->decVal.sign = Param_Estrutura->decVal.sign;
		vi_Resultado->decVal.signscale = Param_Estrutura->decVal.signscale;
	}
		break;

		//(puuid) - Representa uma estrutura CLSID(Guid). (String)
	case VT_CLSID:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->puuid = CreateStringFromGuid(*Param_Estrutura->puuid);
	}
		break;

		//(pclipdata) - Representa uma estrutura CLIPDATA. (CA_CLIPDATA)
	case VT_CF:
	{
		//Inicializa a estrutura.
		vi_Resultado->pclipdata = CA_CLIPDATA();

		//Define os dados base na estrutura.
		vi_Resultado->pclipdata.cbSize = static_cast<UInt32>(Param_Estrutura->pclipdata->cbSize);
		vi_Resultado->pclipdata.ulClipFmt = static_cast<UInt32>(Param_Estrutura->pclipdata->ulClipFmt);

		//Cria o buffer de destino.
		vi_Resultado->pclipdata.pClipData = gcnew CarenBuffer();

		//Cria a interface que vai conter o buffer e realiza uma cópia dos dados.
		static_cast<ICarenBuffer^>(vi_Resultado->pclipdata.pClipData)->CriarBuffer(
			IntPtr(Param_Estrutura->pclipdata->pClipData), //Buffer de Origem.
			true, //Vai realizar uma copia.
			vi_Resultado->pclipdata.cbSize, //Tamanho do buffer
			vi_Resultado->pclipdata.cbSize); //Tamanho valido do buffer.
	}
		break;

		//(blob) - Representa uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB:
	{
		//Inicializa a estrutura.
		vi_Resultado->blob = CA_BlobData();

		//Define os dados.
		vi_Resultado->blob.SizeData = static_cast<UInt32>(Param_Estrutura->blob.cbSize);

		//Cria o buffer de destino.
		vi_Resultado->blob.BufferDados = gcnew CarenBuffer();

		//Cria a interface que vai conter o buffer e realiza uma cópia dos dados.
		static_cast<ICarenBuffer^>(vi_Resultado->blob.BufferDados)->CriarBuffer(
			IntPtr(Param_Estrutura->blob.pBlobData), //Buffer de Origem.
			true, //Vai realizar uma copia.
			vi_Resultado->blob.SizeData,  //Tamanho do buffer
			vi_Resultado->blob.SizeData); //Tamanho valido do buffer.
	}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAM:
	{
		//Verifica se o fluxo é válido.
		if (!ObjetoValido(Param_Estrutura->pStream))
			Sair; //O fluxo é invalido.

		//Recupera o tamanho do fluxo.
		Param_Estrutura->pStream->Stat(&vi_StatStream, 0);

		//Adiciona uma referencia ao fluxo.
		Param_Estrutura->pStream->AddRef();

		//Cria a interface e define o fluxo e seu tamanho.
		vi_Resultado->pStream = gcnew CarenStream(const_cast<IStream*>(Param_Estrutura->pStream), vi_StatStream.cbSize.QuadPart);
	}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORAGE:
	{
		//Verifica se o Storage é válido.
		if (!ObjetoValido(Param_Estrutura->pStorage))
			Sair; //O Storage é invalido.

		//Adiciona uma referencia ao Storage.
		Param_Estrutura->pStorage->AddRef();

		//Cria a interface que vai conter.
		vi_Resultado->pStorage = gcnew Caren();

		//Define o ponteiro na interface criada.
		static_cast<ICaren^>(vi_Resultado->pStorage)->AdicionarPonteiro(Param_Estrutura->pStorage);
	}
		break;

		//(blob) - Represneta uma estrutura TagBlob. (CA_BLOB)
	case VT_BLOB_OBJECT:
	{
		//Inicializa a estrutura.
		vi_Resultado->blob = CA_BlobData();

		//Define os dados.
		vi_Resultado->blob.SizeData = static_cast<UInt32>(Param_Estrutura->blob.cbSize);

		//Cria o buffer de destino.
		vi_Resultado->blob.BufferDados = gcnew CarenBuffer();

		//Cria a interface que vai conter o buffer e realiza uma cópia dos dados.
		static_cast<ICarenBuffer^>(vi_Resultado->blob.BufferDados)->CriarBuffer(
			IntPtr(Param_Estrutura->blob.pBlobData), //Buffer de Origem.
			true, //Vai realizar uma copia.
			vi_Resultado->blob.SizeData,  //Tamanho do buffer
			vi_Resultado->blob.SizeData); //Tamanho valido do buffer.
	}
		break;

		//(pStream) - Representa um ponteiro para a interface IStream. (ICarenStream)
	case VT_STREAMED_OBJECT:
	{
		//Verifica se o fluxo é válido.
		if (!ObjetoValido(Param_Estrutura->pStream))
			Sair; //O fluxo é invalido.

		//Recupera o tamanho do fluxo.
		Param_Estrutura->pStream->Stat(&vi_StatStream, 0);

		//Adiciona uma referencia ao fluxo.
		Param_Estrutura->pStream->AddRef();

		//Cria a interface e define o fluxo e seu tamanho.
		vi_Resultado->pStream = gcnew CarenStream(const_cast<IStream*>(Param_Estrutura->pStream), vi_StatStream.cbSize.QuadPart);
	}
		break;

		//(pStorage) - Representa um ponteiro para a interface IStorage. (ICaren)
	case VT_STORED_OBJECT:
	{
		//Verifica se o Storage é válido.
		if (!ObjetoValido(Param_Estrutura->pStorage))
			Sair; //O Storage é invalido.

		//Adiciona uma referencia ao Storage.
		Param_Estrutura->pStorage->AddRef();

		//Cria a interface que vai conter.
		vi_Resultado->pStorage = gcnew Caren();

		//Define o ponteiro na interface criada.
		static_cast<ICaren^>(vi_Resultado->pStorage)->AdicionarPonteiro(Param_Estrutura->pStorage);
	}
		break;

		//(pVersionedStream) - Representa uma estrutura TagVersionedStream que contém . (ICarenStream)
	case VT_VERSIONED_STREAM:
	{
		//Inicializa a estrutura.
		vi_Resultado->pVersionedStream = CA_VersionedStream();

		//Verifica se o fluxo é válido.
		if (!ObjetoValido(Param_Estrutura->pVersionedStream->pStream))
			Sair; //O fluxo é invalido.

		//Recupera o tamanho do fluxo.
		Param_Estrutura->pVersionedStream->pStream->Stat(&vi_StatStream, 0);

		//Adiciona uma referencia ao fluxo.
		Param_Estrutura->pVersionedStream->pStream->AddRef();

		//Cria a interface e define o fluxo e seu tamanho.
		vi_Resultado->pVersionedStream.pStream = gcnew CarenStream(const_cast<IStream*>(Param_Estrutura->pStream), vi_StatStream.cbSize.QuadPart);

		//Converte e define o Guid.
		vi_Resultado->pVersionedStream.guidVersion = CreateStringFromGuid(Param_Estrutura->pVersionedStream->guidVersion);
	}
		break;

		//(punkVal) - Representa um ponteiro para a interface base nativa IUnknown. (ICaren)
	case VT_UNKNOWN:
	{
		//Verifica se a interface é válida.
		if (!ObjetoValido(Param_Estrutura->punkVal))
			Sair; //A interface é invalida.

		//Adiciona uma referencia a interface.
		Param_Estrutura->punkVal->AddRef();

		//Cria a interface e define o fluxo e seu tamanho.
		vi_Resultado->punkVal = gcnew Caren();

		//Define o ponteiro na interface.
		static_cast<ICaren^>(vi_Resultado->punkVal)->AdicionarPonteiro(Param_Estrutura->punkVal);
	}
		break;

		//(pdispVal) - Representa um ponteiro para a interface nativa IDispatch. (ICaren)
	case VT_DISPATCH:
	{
		//Verifica se a interface é válida.
		if (!ObjetoValido(Param_Estrutura->pdispVal))
			Sair; //A interface é invalida.

		//Adiciona uma referencia a interface.
		Param_Estrutura->pdispVal->AddRef();

		//Cria a interface e define o fluxo e seu tamanho.
		vi_Resultado->pdispVal = gcnew Caren();

		//Define o ponteiro na interface.
		static_cast<ICaren^>(vi_Resultado->pdispVal)->AdicionarPonteiro(Param_Estrutura->pdispVal);
	}
		break;

		//(NÃO INFORMADO) - Representa um ponteiro para uma estrutura SAFEARRAY.
	case VT_SAFEARRAY:
	{
		//Verifica se o SAFEARRAY é valido.
		if (!ObjetoValido(Param_Estrutura->parray))
			Sair; //SafeArray Invalido.

		//Cria a estrutura e em seguida cria uma copia do SafeArray.
		vi_Resultado->parray = gcnew CA_SAFEARRAY(const_cast<LPSAFEARRAY>(Param_Estrutura->parray), true);
	}
		break;
		
		//(NÃO INFORMADO) - Representa um erro HRESULT de 4 bytes. Deve ser do mesmo tipo que o (VT_ERROR) e o (VT_I4). (Int32)
	case VT_HRESULT:
	{
		//Define os dados na estrutura a ser retornada.
		vi_Resultado->scode = static_cast<UInt32>(Param_Estrutura->scode);
	}
		break;





		//Matrizes Contadas.. TIPO | VT_VECTOR. Todos os membros com um (ca) no inicio.



		//(cac) - Representa um estrutura CA_CAC que contém uma matriz de char.
	case VT_I1 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cac = CA_CAC();

		//Define o tamanho do array.
		vi_Resultado->cac.cElems = Param_Estrutura->cac.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cac.pElems = gcnew cli::array<char>(vi_Resultado->cac.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cac.pElems, //Buffer ORIGEM
			vi_Resultado->cac.pElems,  //Buffer DESTINO
			vi_Resultado->cac.cElems);
	}
		break;
		//(caub) - Representa um estrutura CA_CAUB que contém uma matriz de Bytes.
	case VT_UI1 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->caub = CA_CAUB();

		//Define o tamanho do array.
		vi_Resultado->caub.cElems = Param_Estrutura->caub.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->caub.pElems = gcnew cli::array<Byte>(vi_Resultado->caub.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->caub.pElems, //Buffer ORIGEM
			vi_Resultado->caub.pElems,  //Buffer DESTINO
			vi_Resultado->caub.cElems);
	}
		break;
		//(cai) - Representa um estrutura CA_CAI que contém uma matriz de inteiros assinados de 2 bytes(Int16).
	case VT_I2 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cai = CA_CAI();

		//Define o tamanho do array.
		vi_Resultado->cai.cElems = Param_Estrutura->cai.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cai.pElems = gcnew cli::array<Int16>(vi_Resultado->cai.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cai.pElems, //Buffer ORIGEM
			vi_Resultado->cai.pElems,  //Buffer DESTINO
			vi_Resultado->cai.cElems);
	}
		break;
		//(caui) - Representa um estrutura CA_CAUI que contém uma matriz de inteiros não assinados de 2 bytes(UInt16).
	case VT_UI2 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->caui = CA_CAUI();

		//Define o tamanho do array.
		vi_Resultado->caui.cElems = Param_Estrutura->caui.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->caui.pElems = gcnew cli::array<UInt16>(vi_Resultado->caui.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->caui.pElems, //Buffer ORIGEM
			vi_Resultado->caui.pElems,  //Buffer DESTINO
			vi_Resultado->caui.cElems);
	}
		break;
		//(cal) - Representa um estrutura CA_CAL que contém uma matriz de inteiros assinados de 4 bytes(Int32).
	case VT_I4 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cal = CA_CAL();

		//Define o tamanho do array.
		vi_Resultado->cal.cElems = Param_Estrutura->cal.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cal.pElems = gcnew cli::array<Int32>(vi_Resultado->cal.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cal.pElems, //Buffer ORIGEM
			vi_Resultado->cal.pElems,  //Buffer DESTINO
			vi_Resultado->cal.cElems);
	}
		break;
		//(caul) - Representa um estrutura CA_CAUL que contém uma matriz de inteiros não assinados de 4 bytes(UInt32).
	case VT_UI4 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->caul = CA_CAUL();

		//Define o tamanho do array.
		vi_Resultado->caul.cElems = Param_Estrutura->caul.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->caul.pElems = gcnew cli::array<UInt32>(vi_Resultado->caul.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->caul.pElems, //Buffer ORIGEM
			vi_Resultado->caul.pElems,  //Buffer DESTINO
			vi_Resultado->caul.cElems);
	}
		break;
		//(cabool) - Representa um estrutura CA_CABOOL que contém uma matriz de valores Booleanos.
	case VT_BOOL | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cabool = CA_CABOOL();

		//Define o tamanho do array.
		vi_Resultado->cabool.cElems = Param_Estrutura->cabool.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cabool.pElems = gcnew cli::array<Boolean>(vi_Resultado->cabool.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cabool.cElems; i++)
		{
			//Converte e define no index especificado.
			vi_Resultado->cabool.pElems[i] = Param_Estrutura->cabool.pElems[i] == -1 ? true : false;
		}
	}
		break;
		//(caflt) - Representa um estrutura CA_CAFLT que contém uma matriz de valores reais de 4 bytes(float).
	case VT_R4 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->caflt = CA_CAFLT();

		//Define o tamanho do array.
		vi_Resultado->caflt.cElems = Param_Estrutura->caflt.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->caflt.pElems = gcnew cli::array<float>(vi_Resultado->caflt.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->caflt.pElems, //Buffer ORIGEM
			vi_Resultado->caflt.pElems,  //Buffer DESTINO
			vi_Resultado->caflt.cElems);
	}
		break;
		//(cadbl) - Representa um estrutura CA_CADBL que contém uma matriz de valores reais de 8 bytes(double).
	case VT_R8 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cadbl = CA_CADBL();

		//Define o tamanho do array.
		vi_Resultado->cadbl.cElems = Param_Estrutura->cadbl.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cadbl.pElems = gcnew cli::array<double>(vi_Resultado->cadbl.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cadbl.pElems, //Buffer ORIGEM
			vi_Resultado->cadbl.pElems,  //Buffer DESTINO
			vi_Resultado->cadbl.cElems);
	}
		break;
		//(cascode) - Representa um estrutura CA_CASCODE que contém uma matriz de inteiros assinados de 4 bytes(Int32).
	case VT_ERROR | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cascode = CA_CASCODE();

		//Define o tamanho do array.
		vi_Resultado->cascode.cElems = Param_Estrutura->cascode.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cascode.pElems = gcnew cli::array<Int32>(vi_Resultado->cascode.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cascode.pElems, //Buffer ORIGEM
			vi_Resultado->cascode.pElems,  //Buffer DESTINO
			vi_Resultado->cascode.cElems);
	}
		break;
		//(cauh) - Representa um estrutura CA_CAUH que contém uma matriz de estrutruas CA_ULARGE_INTERGER.
	case VT_UI8 | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cauh = CA_CAUH();

		//Define o tamanho do array.
		vi_Resultado->cauh.cElems = Param_Estrutura->cauh.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cauh.pElems = gcnew cli::array<CA_ULARGE_INTEGER>(vi_Resultado->cauh.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cauh.cElems; i++)
		{
			//Inicializa a estrutura.
			vi_Resultado->cauh.pElems[i] = CA_ULARGE_INTEGER();

			//Define os dados na estrutura.
			vi_Resultado->cauh.pElems[i].LowPart = Param_Estrutura->cauh.pElems[i].LowPart;
			vi_Resultado->cauh.pElems[i].HighPart = Param_Estrutura->cauh.pElems[i].HighPart;
			vi_Resultado->cauh.pElems[i].QuadPart = Param_Estrutura->cauh.pElems[i].QuadPart;
		}
	}
		break;
		//(cacy) - Representa um estrutura CA_CACY que contém uma matriz de estrutruas CA_CY.
	case VT_CY | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cacy = CA_CACY();

		//Define o tamanho do array.
		vi_Resultado->cacy.cElems = Param_Estrutura->cacy.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cacy.pElems = gcnew cli::array<CA_CY>(vi_Resultado->cacy.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cacy.cElems; i++)
		{
			//Inicializa a estrutura.
			vi_Resultado->cacy.pElems[i] = CA_CY();

			//Define os dados na estrutura.
			vi_Resultado->cacy.pElems[i].Hi = Param_Estrutura->cacy.pElems[i].Hi;
			vi_Resultado->cacy.pElems[i].int64 = Param_Estrutura->cacy.pElems[i].int64;
			vi_Resultado->cacy.pElems[i].Lo = Param_Estrutura->cacy.pElems[i].Lo;
		}
	}
		break;
		//(cadate) - Representa uma estrutura CA_CADATE que contém uma matriz de valores reais de 8 bytes cada.
	case VT_DATE | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cadate = CA_CADATE();

		//Define o tamanho do array.
		vi_Resultado->cadate.cElems = Param_Estrutura->cadate.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cadate.pElems = gcnew cli::array<double>(vi_Resultado->cadate.cElems);

		//Realiza a copia dos dados.
		CopiarBufferNativoToGerenciado(
			&Param_Estrutura->cadate.pElems, //Buffer ORIGEM
			vi_Resultado->cadate.pElems,  //Buffer DESTINO
			vi_Resultado->cadate.cElems);
	}
		break;
		//(cafiletime) - Representa uma estrutura CA_CAFILETIME que contém uma matriz de estrutruas CA_FILETIME.
	case VT_FILETIME | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cafiletime = CA_CAFILETIME();

		//Define o tamanho do array.
		vi_Resultado->cafiletime.cElems = Param_Estrutura->cafiletime.cElems;

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cafiletime.pElems = gcnew cli::array<CA_FILETIME>(vi_Resultado->cafiletime.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cafiletime.cElems; i++)
		{
			//Inicializa a estrutura.
			vi_Resultado->cafiletime.pElems[i] = CA_FILETIME();

			//Define os dados na estrutura.
			vi_Resultado->cafiletime.pElems[i].dwHighDateTime = static_cast<UInt32>(Param_Estrutura->cafiletime.pElems[i].dwHighDateTime);
			vi_Resultado->cafiletime.pElems[i].dwLowDateTime = static_cast<UInt32>(Param_Estrutura->cafiletime.pElems[i].dwLowDateTime);
		}
	}
		break;
		//(cauuid) - Representa uma estrutura CA_CACLSID que contém uma matriz de GUIDs, implementados como System::String no gerenciado.
	case VT_CLSID | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cauuid = CA_CACLSID();

		//Define o tamanho do array.
		vi_Resultado->cauuid.cElems = static_cast<UInt32>(Param_Estrutura->cauuid.cElems);

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cauuid.pElems = gcnew cli::array<String^>(vi_Resultado->cauuid.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cauuid.cElems; i++)
		{
			//Inicializa e define os dados no index especificado.
			vi_Resultado->cauuid.pElems[i] = CreateStringFromGuid(Param_Estrutura->cauuid.pElems[i]);
		}
	}
		break;
		//(caclipdata) - Representa uma estrutura CA_CACLIPDATA que contém uma matriz de estruturas CA_CLIPDATA.
	case VT_CF | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->caclipdata = CA_CACLIPDATA();

		//Define o tamanho do array.
		vi_Resultado->caclipdata.cElems = static_cast<UInt32>(Param_Estrutura->caclipdata.cElems);

		//Cria o buffer que vai conter os dados.
		vi_Resultado->caclipdata.pElems = gcnew cli::array<CA_CLIPDATA>(vi_Resultado->caclipdata.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->caclipdata.cElems; i++)
		{
			//Inicializa a estrutura
			vi_Resultado->caclipdata.pElems[i] = CA_CLIPDATA();

			//Define os dados na estrutura.
			vi_Resultado->caclipdata.pElems[i].cbSize = static_cast<UInt32>(Param_Estrutura->caclipdata.pElems[i].cbSize);
			vi_Resultado->caclipdata.pElems[i].ulClipFmt = static_cast<int>(Param_Estrutura->caclipdata.pElems[i].ulClipFmt);

			//Verifica se o buffer é valido
			if (!ObjetoValido(Param_Estrutura->caclipdata.pElems[i].pClipData))
				continue; //Vai para o proximo laço. O buffer desse index não é valido.

			//Cria o buffer que vai receber os dados.
			vi_Resultado->caclipdata.pElems[i].pClipData = gcnew CarenBuffer();

			//Cria o buffer e realizar uma copia dos dados.
			static_cast<ICarenBuffer^>(vi_Resultado->caclipdata.pElems[i].pClipData)->CriarBuffer
			(
				IntPtr(Param_Estrutura->caclipdata.pElems[i].pClipData), // Buffer ORIGEM
				true, // Deve realizar uma copia.
				vi_Resultado->caclipdata.pElems[i].cbSize, //Tamanho.
				vi_Resultado->caclipdata.pElems[i].cbSize //Tamanho válido.
			);
		}
	}
		break;
		//(cabstr) - Representa uma estrutura CA_CABSTR que contém uma matriz de strings BSTR Unicode, implementados como System::String no gerenciado. 
	case VT_BSTR | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->cabstr = CA_CABSTR();

		//Define o tamanho do array.
		vi_Resultado->cabstr.cElems = static_cast<UInt32>(Param_Estrutura->cabstr.cElems);

		//Cria o buffer que vai conter os dados.
		vi_Resultado->cabstr.pElems = gcnew cli::array<String^>(vi_Resultado->cabstr.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->cabstr.cElems; i++)
		{
			//Inicializa e define os dados no index especificado.
			vi_Resultado->cabstr.pElems[i] = gcnew String(Param_Estrutura->cabstr.pElems[i]);
		}
	}
		break;
		//(calpstr) - Representa uma estrutura CA_CALPSTR que contém uma matriz de char* ANSI, implementados como System::String no gerenciado. 
	case VT_LPSTR | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->calpstr = CA_CALPSTR();

		//Define o tamanho do array.
		vi_Resultado->calpstr.cElems = static_cast<UInt32>(Param_Estrutura->calpstr.cElems);

		//Cria o buffer que vai conter os dados.
		vi_Resultado->calpstr.pElems = gcnew cli::array<String^>(vi_Resultado->calpstr.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->calpstr.cElems; i++)
		{
			//Inicializa e define os dados no index especificado.
			vi_Resultado->calpstr.pElems[i] = Marshal::PtrToStringAnsi(IntPtr(Param_Estrutura->calpstr.pElems[i]));
		}
	}
		break;
		//(calpwstr) - Representa uma estrutura CA_CALPWSTR que contém uma matriz de WCHAR* Unicode, implementados como System::String no gerenciado. 
	case VT_LPWSTR | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->calpwstr = CA_CALPWSTR();

		//Define o tamanho do array.
		vi_Resultado->calpwstr.cElems = static_cast<UInt32>(Param_Estrutura->calpwstr.cElems);

		//Cria o buffer que vai conter os dados.
		vi_Resultado->calpwstr.pElems = gcnew cli::array<String^>(vi_Resultado->calpwstr.cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < Param_Estrutura->calpwstr.cElems; i++)
		{
			//Inicializa e define os dados no index especificado.
			vi_Resultado->calpwstr.pElems[i] = Marshal::PtrToStringUni(IntPtr(Param_Estrutura->calpwstr.pElems[i]));
		}
	}
		break;
		//(capropvar) - Representa uma estrutura CA_CAPROPVARIANT que contém uma matriz de estruturas CA_PROPVARIANT.
	case VT_VARIANT | VT_VECTOR:
	{
		//Inicializa a estrutura
		vi_Resultado->capropvar = gcnew CA_CAPROPVARIANT();

		//Converte a estrutura para uma variavel temporaria.
		vi_TempCaPropVariant = (CA_CAPROPVARIANT^)vi_Resultado->capropvar;

		//Define o tamanho do array.
		vi_TempCaPropVariant->cElems = static_cast<UInt32>(Param_Estrutura->capropvar.cElems);

		//Cria o buffer que vai conter os dados.
		vi_TempCaPropVariant->pElems = gcnew cli::array<CA_PROPVARIANT^>(vi_TempCaPropVariant->cElems);

		//Realiza a copia dos dados.
		for (ULONG i = 0; i < vi_TempCaPropVariant->cElems; i++)
		{
			//Converte e define no index a estrutura.
			vi_TempCaPropVariant->pElems[i] = ConverterPropVariantUnmanaged_ToManaged(&Param_Estrutura->capropvar.pElems[i]);
		}
	}
		break;
		




		//SAFEARRAY.. TIPO | VT_ARRAY - TODOS OS TIPOS LEVAM PARA UM (SAFEARRAY), MEMBRO (Parray)



		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 1 byte (char).
	case VT_I1 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 1 byte (Byte).
	case VT_UI1 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 2 bytes (Int16).
	case VT_I2 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 2 bytes (UInt16).
	case VT_UI2 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 4 bytes (Int32).
	case VT_I4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 4 bytes (UInt32).
	case VT_UI4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros assinados de 4 bytes (Int32).
	case VT_INT | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros não assinados de 4 bytes (UInt32). 
	case VT_UINT | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 4 bytes (float). 
	case VT_R4 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 8 bytes (double).
	case VT_R8 | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores booleanos (Boolean).
	case VT_BOOL | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas DECIMAL (CA_DEC).
	case VT_DECIMAL | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores inteiros de 4 bytes (Int32).
	case VT_ERROR | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas CY (CA_CY).
	case VT_CY | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de valores reais de 8 bytes (double).
	case VT_DATE | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de BSTRs da tabela Unicode (String).
	case VT_BSTR | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de ponteiros para a interface IDispatch (ICaren).
	case VT_DISPATCH | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de ponteiros para a interface IUnknown (ICaren).
	case VT_UNKNOWN | VT_ARRAY:
	{}
		break;
		//(Parray) - Representa um SAFEARRAY que contém uma matriz de estruturas VARIANT (CA_VARIANT).
	case VT_VARIANT | VT_ARRAY:
	{}
		break;





		//TIPOS REFERENCIA. TIPO | VT_BYREF. Quase todos os membros com um (*p) no inicio.



		//(pcVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 1 byte (char).
	case VT_I1 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pcVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pcVal = *Param_Estrutura->pcVal;
	}
		break;
		//(pbVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 1 byte (Byte).
	case VT_UI1 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pbVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pbVal = *Param_Estrutura->pbVal;
	}
		break;
		//(piVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 2 bytes (Int16).
	case VT_I2 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->piVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->piVal = *Param_Estrutura->piVal;
	}
		break;
		//(puiVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 2 bytes (UInt16).
	case VT_UI2 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->puiVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->puiVal = *Param_Estrutura->puiVal;
	}
		break;
		//(plVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_I4 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->plVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->plVal = static_cast<int>(*Param_Estrutura->plVal);
	}
		break;
		//(pulVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 4 bytes (UInt32).
	case VT_UI4 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pulVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pulVal = static_cast<UInt32>(*Param_Estrutura->pulVal);
	}
		break;
		//(pintVal) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_INT | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pintVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pintVal = static_cast<int>(*Param_Estrutura->pintVal);
	}
		break;
		//(puintVal) - Representa um ponteiro(referência) que leva para um valor inteiro não assinado de 4 bytes (UInt32).
	case VT_UINT | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->puintVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->puintVal = static_cast<UInt32>(*Param_Estrutura->puintVal);
	}
		break;
		//(pfltVal) - Representa um ponteiro(referência) que leva para um valor real de 4 bytes (float).
	case VT_R4 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pfltVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pfltVal = *Param_Estrutura->pfltVal;
	}
		break;
		//(pdblVal) - Representa um ponteiro(referência) que leva para um valor real de 8 bytes (double).
	case VT_R8 | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pdblVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pdblVal = *Param_Estrutura->pdblVal;
	}
		break;
		//(pboolVal) - Representa um ponteiro(referência) que leva para um valor booleano (Boolean).
	case VT_BOOL | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pboolVal))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pboolVal = (*Param_Estrutura->pboolVal) == -1? true: false;
	}
		break;
		//(pdecVal) - Representa um ponteiro(referência) que leva para uma estrutura DECIMAL (CA_DEC).
	case VT_DECIMAL | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pdecVal))
			Sair; //Ponteiro inválido.

		//Inicializa a estrutura.
		vi_Resultado->pdecVal = CA_DEC();

		//Define os dados.
		vi_Resultado->pdecVal.Hi32 = static_cast<UInt32>(Param_Estrutura->pdecVal->Hi32);
		vi_Resultado->pdecVal.Mid32 = static_cast<UInt32>(Param_Estrutura->pdecVal->Mid32);
		vi_Resultado->pdecVal.Lo32 = static_cast<UInt32>(Param_Estrutura->pdecVal->Lo32);
		vi_Resultado->pdecVal.Lo64 = Param_Estrutura->pdecVal->Lo64;
		vi_Resultado->pdecVal.scale = Param_Estrutura->pdecVal->scale;
		vi_Resultado->pdecVal.sign = Param_Estrutura->pdecVal->sign;
		vi_Resultado->pdecVal.signscale = Param_Estrutura->pdecVal->signscale;
	}
		break;
		//(pscode) - Representa um ponteiro(referência) que leva para um valor inteiro de 4 bytes (Int32).
	case VT_ERROR | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pscode))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pscode = *Param_Estrutura->pscode;
	}
		break;
		//(pcyVal) - Representa um ponteiro(referência) que leva para uma estrutura CY (CA_CY).
	case VT_CY | VT_BYREF:
	{}
		break;
		//(pdate) - Representa um ponteiro(referência) que leva para um valor real de 8 bytes (double).
	case VT_DATE | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pdate))
			Sair; //Ponteiro inválido.

		//Define os dados no membro da estrutura.
		vi_Resultado->pdate = *Param_Estrutura->pdate;
	}
		break;
		//(pbstrVal) - Representa um ponteiro(referência) que leva para um valor BSTR da tabela Unicode (String).
	case VT_BSTR | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pbstrVal))
			Sair; //Ponteiro inválido.

		//Converte os dados e define no membro da estrutura
		vi_Resultado->pbstrVal = gcnew String(*Param_Estrutura->pbstrVal);
	}
		break;
		//(ppunkVal) - Representa um ponteiro(referência) que leva para um ponteiro que contém uma interface IUnknown (ICaren).
	case VT_UNKNOWN | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->ppunkVal))
			Sair; //Ponteiro inválido.

		//Adiciona uma referência.
		(*Param_Estrutura->ppunkVal)->AddRef();

		//Define o ponteiro no membro da estrutura.
		vi_Resultado->ppunkVal = IntPtr(*Param_Estrutura->ppunkVal);
	}
		break;
		//(ppdispVal) - Representa um ponteiro(referência) que leva para um ponteiro que contém uma interface IDispath (ICaren).
	case VT_DISPATCH | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->ppdispVal))
			Sair; //Ponteiro inválido.

		//Adiciona uma referência.
		(*Param_Estrutura->ppdispVal)->AddRef();

		//Define o ponteiro no membro da estrutura.
		vi_Resultado->ppunkVal = IntPtr(*Param_Estrutura->ppdispVal);
	}
		break;
		//(pparray) - Representa um ponteiro(referência) que leva para uma estrutura SAFEARRAY (CA_SAFEARRAY).
	case VT_ARRAY | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pparray))
			Sair; //Ponteiro inválido.

		//Cria e define o safearray no membro da estrutura.
		vi_Resultado->pparray = gcnew CA_SAFEARRAY(
			const_cast<LPSAFEARRAY&>(*Param_Estrutura->pparray),
			true); //Cria uma copia do safearray.
	}
		break;
		//(pvarVal) - Representa um ponteiro(referência) que leva para uma estrutura PROPVARIANT (CA_PROPVARIANT).
	case VT_VARIANT | VT_BYREF:
	{
		//Verifica se o ponteiro é valido.
		if (!ObjetoValido(Param_Estrutura->pvarVal))
			Sair; //Ponteiro inválido.

		//Converte e define no membro da estrutura.
		vi_Resultado->pvarVal = ConverterPropVariantUnmanaged_ToManaged(Param_Estrutura->pvarVal);
	}
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
		throw gcnew Exception("O tipo de variante (VT_VARIANT) não é suportado puro. Esse valor deve ser usado com (VT_VECTOR ou VT_BYREF) com operador OR.");
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