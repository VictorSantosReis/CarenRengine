#pragma once
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


#pragma comment(lib, "Mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "MFSRCSNK.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "evr.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "mscoree.lib")
#pragma comment(lib, "Propsys.lib")
#pragma comment(lib, "Avrt.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "Dxva2.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3D10.lib")
#pragma comment(lib, "D3d9.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Uuid.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "OleAut32.lib")



#include <winerror.h>
#include <iostream>
#include <ObjIdl.h>
#include <math.h>
#include <WTypesbase.h>
#include <array>
#include <vector>
#include <assert.h>
#include <Propidl.h>
#include <propvarutil.h>
#include <profileapi.h>
#include <sysinfoapi.h>
#include <timeapi.h>
#include <mfidl.h>
#include <mfapi.h>
#include <mferror.h>
#include <mfobjects.h>
#include <mfreadwrite.h>
#include <mftransform.h>
#include <mfmp2dlna.h>
#include <mfmediaengine.h>
#include <mfcaptureengine.h>
#include <wmcontainer.h>
#include <Shlwapi.h>
#include <evr.h>
#include <mmreg.h>
#include <wmcodecdsp.h>
#include <codecapi.h>
#include <OCIdl.h>
#include <dvdmedia.h>
#include <propkey.h>
#include <Windows.h>
#include <WinUser.h>
#include <chrono>
#include <windef.h>
#include <propsys.h>
#include <atlsafe.h>
#include <vcclr.h>
#include <msclr/marshal.h>
#include <combaseapi.h>
#include <avrt.h>
#include <synchapi.h>
#include <inspectable.h>
#include <oleauto.h>

//Errros Hresult
#include <comdef.h>

//Processamento de audio pela api CoreAudio.

#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <audiopolicy.h>
#include <functiondiscoverykeys_devpkey.h>

//Start os guids
#include <initguid.h>

//Directx and DXGI
#include <d3d9.h>
#include <d3d9types.h>
#include <d3d10_1.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>
#include <dxva2api.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>

//Direct2D
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_2.h>
#include <d2d1_3.h>
#include <d2d1svg.h>
#include <d2d1effects.h>
#include <d2d1effects_1.h>
#include <d2d1effects_2.h>
#include <d2d1helper.h>
#include <d2d1_1helper.h>
#include <d2d1_2helper.h>
#include <d2d1effectauthor.h>
#include <d2d1effectauthor_1.h>

//WIC
#include <wincodec.h>
#include <wincodecsdk.h>

//DWrite
#include <dwrite.h>

//PrintDocuments
#include <DocumentTarget.h>


//Namespaces
using namespace System;
using namespace System::ComponentModel;
using namespace System::Buffers;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::Serialization;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace msclr::interop;
using namespace std;



//Definições
#define Sucesso(hr) (((HRESULT)(hr)) >= 0)
#define Falha(hr) (((HRESULT)(hr)) < 0)
#define ObjetoValido(ObjCheck) (ObjCheck != NULL)
#define ObjetoGerenciadoValido(ObjetoCheck)(ObjetoCheck != nullptr)
#define StringObjetoValido(ObjetoCheck)(!String::IsNullOrEmpty(ObjetoCheck))
#define Sair goto Done;
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

//Typedefs
typedef HRESULT ResultadoCOM;
typedef cli::array<Byte>^ MatrizBytes;
typedef System::IntPtr GenPointer;
#define DefaultGenPointer IntPtr::Zero;
#define OutParam [Out]

#ifndef Nulo
#ifdef __cplusplus
#define Nulo 0
#else
#define nulo ((void *)0)
#endif
#endif


//Funções.

//Deleta um IMFMediaType corretamente sem gerar execeções.
template <class MediaType> void DeleteMediaType(MediaType** pType)
{
	//Verifica se é valido
	if (*pType)
	{
		//Vai conter a quantidade de itens.
		UINT32 ItensCount = 0;

		//Se não houver nenhum item, vai excluir apenas com o (NULL), caso contrario, Chama um SafeRelease.
		(*pType)->GetCount(&ItensCount);

		//Verifica a quantidade de itens
		if (ItensCount > 0)
		{
			//Libera os dados.
			(*pType)->Release();

			//Exclui o ponteiro.
			*pType = NULL;
		}
		else
		{
			//Exclui o ponteiro
			*pType = NULL;
		}
	}
}

//Libera um determinado ponteiro de forma segura.
template <class T> void SafeReleasePointer(T** ppT)
{
	//Verifica se o ponteiro é valido.
	if (*ppT)
	{
		//Libera os dados.
		(*ppT)->Release();

		//Exclui o ponteiro.
		*ppT = NULL;
	}
}

//Libera a memoria um determinado objeto. O método chama (delete).
template <class T> void SafeDeleteMemory(T** ppT)
{
	//Verifica se é valido.
	if (*ppT)
	{
		//Libera a memoria.
		delete *ppT;

		//Exclui o ponteiro.
		*ppT = NULL;
	}
	else
	{
		//Objeto invalido.
	}
}

//Libera a memória alocada para uma String que foi convertida utilizando os métodos da classe Utilidades.
template <class T> void DeletarStringAllocatedSafe(T** Param_Texto)
{
	//Verifica se o ponteiro é valido.
	if (*Param_Texto)
	{
		//Libera a memória.
		delete* Param_Texto;
	}
}

//Libera a memória alocada por (CoTaskMemAlloc) para uma string.
template <class T> void DeletarStringCoTaskSafe(T** Param_Texto)
{
	//Verifica se o ponteiro é valido.
	if (*Param_Texto)
	{
		//Libera a memória.
		CoTaskMemFree(*Param_Texto);

		//Limpa
		*Param_Texto = NULL;
	}
}

//Aloca memória para um tipo de string usando o CoTaskMemAlloc. Utilize o método DeletarStringCoTaskSafe para liberar a memória.
template <class T> T* CriarStringCoTask(UInt32 Param_LarguraString)
{
	//Aloca e retorna o ponteiro para o usuário.
	return (T*)CoTaskMemAlloc(static_cast<SIZE_T>(Param_LarguraString));
}

//Libera a memória alocada por (SysAllocString) para uma string BSTR.
template <class T> void DeletarStringBSTRSafe(T** Param_Texto)
{
	//Verifica se o ponteiro é valido.
	if (*Param_Texto)
	{
		//Libera a memória.
		SysFreeString(*Param_Texto);

		//Limpa
		*Param_Texto = NULL;
	}
}

//Cria e inicializa uma estrutura corretamente.
template <class T> T* CriarEstrutura()
{
	//Cria a estrutura.
	T* pEstrutura = new T();

	//Retorna
	return pEstrutura;
}

//Cria e inicializa uma estrutura corretamente.
template <class T> T* CriarMatrizEstruturas(UINT32 Param_CountItems)
{
	//Cria uma matriz de estruturas.
	T* pEstrutura = new T[Param_CountItems];

	//Retorna
	return pEstrutura;
}

//Libera a memoria para uma estrutura que tenha sido criada com o método (CriarEstrutura)
template <class T> void DeletarEstrutura(T** Param_Estrutura)
{
	//Deleta o ponteiro.
	delete *Param_Estrutura;

	//NULA o ponteiro.
	*Param_Estrutura = NULL;
}

//Libera a memoria para uma estrutura que tenha sido criada com o método(CriarEstrutura)
//O método já verifica se a estrutura é valida.
template <class T> void DeletarEstruturaSafe(T** Param_Estrutura)
{
	//Verifica se o ponteiro para a estrutura é valido.
	if (*Param_Estrutura)
	{
		//Deleta a estrutura.
		delete *Param_Estrutura;

		//Exclui o ponteiro.
		*Param_Estrutura = NULL;
	}
}

//Libera a memoria para uma matriz de estrturas que foi criada com o (CriarMatrizEstrutura)
//O método já verifica se a estrutura é valida.
template <class T> void DeletarMatrizEstruturasSafe(T** Param_Estrutura)
{
	//Verifica se o ponteiro para a estrutura é valido.
	if (*Param_Estrutura)
	{
		//Deleta o array de estruturas.
		delete[] *Param_Estrutura;

		//Exclui o ponteiro.
		*Param_Estrutura = NULL;
	}
}

//Cria e inicializa uma matriz de ponteiros.
template <class T> T** CriarMatrizPonteiros(UINT32 Param_Quantidade)
{
	//Variavel a ser retornada.
	T** MatrizPonteiros = NULL;

	//Cria a matriz de ponteiros.
	MatrizPonteiros = new T*[Param_Quantidade];

	//Retorna a matriz.
	return MatrizPonteiros;
}

//Método responável por deletar uma matriz de ponteiros.
template<class T> void DeletarMatrizPonteirosSafe(T*** Param_PointToMatriz)
{
	if (*Param_PointToMatriz)
	{
		//Deleta a matriz.
		delete[] *Param_PointToMatriz;

		//exclui o ponteiro.
		*Param_PointToMatriz = NULL;
	}
}

//Método responsável por criar uma matriz unidimensional.
//Chama o método (DeletarMatrizUnidimensional) quando não for mais utilizar.
template<class T> T* CriarMatrizUnidimensional(DWORD Param_Quantidade)
{
	//Cria e retorna uma matriz unidimensional dinamica.
	return new T[Param_Quantidade];
}

//Método responsável por deletar uma matriz unidimensional criada pelo método (CriarMatrizUnidimensional).
template<class T> void DeletarMatrizUnidimensional(T* Param_Matriz)
{
	delete[] Param_Matriz;
}

//Método responsável por deletar uma matriz unidimensional criada pelo método (CriarMatrizUnidimensional).
template<class T> void DeletarMatrizUnidimensionalSafe(T** Param_Matriz)
{
	//Verifica se o ponteiro para a estrutura é valido.
	if (*Param_Matriz)
	{
		//Deleta a estrutura.
		delete[] *Param_Matriz;

		//Exclui o ponteiro.
		*Param_Matriz = NULL;
	}
}

//Método responsável por deletar uma matriz unidimensional criada pelo método (CriarMatrizUnidimensional).
template<class T> void DeletarMatrizDePonteirosUnidimensionalSafe(T** Param_Matriz, UINT32 Param_QuantidadeElementos)
{
	//Verifica se o ponteiro para a estrutura é valido.
	if (*Param_Matriz)
	{
		//Deleta cada item na matriz.
		for (UINT32 i = 0; i < Param_QuantidadeElementos; i++)
		{
			//Deleta o pointeiro na matriz.
			delete Param_Matriz[i];
		}

		//Deleta a matriz.
		delete[] * Param_Matriz;

		//Exclui o ponteiro.
		*Param_Matriz = NULL;
	}

}

//Método responsável por converter tipo de dados simples usando o static_cast
template<class Destino, class Source> Destino ConverterPara(Source Param_Tipo)
{
	return static_cast<Destino>(Param_Tipo);
}




//INCLUSÕES ORIGINAIS DA BIBLIOTECA.
#include "CodeResults.h"

//NAMESPACES ORIGINAIS DA BIBLIOTECA
using namespace CarenRengine::CarenCodesStatus;
typedef CarenResult CarenResultado;


inline void SetCarenSucesso(CarenResultado% Param_Resultado)
{
	Param_Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
}
inline void SetCarenSucesso(CarenResultado% Param_Resultado, ResultCode Param_CodeStatus)
{
	Param_Resultado.AdicionarCodigo(Param_CodeStatus, true);
}
inline void SetCarenErro(CarenResultado% Param_Resultado, ResultCode Param_CodeStatus)
{
	Param_Resultado.AdicionarCodigo(Param_CodeStatus, false);
}
inline void SetCarenErro(CarenResultado% Param_Resultado, HRESULT Param_CodeStatus)
{
	Param_Resultado.AdicionarCodigo(Param_CodeStatus, false);
}
inline BOOL CarenSucesso(CarenResultado Param_Status)
{
	return Param_Status.StatusCode == ResultCode::SS_OK ? TRUE : FALSE;
}
inline void DeletarEstruturaGerenciadaSafe(Object^% Param_Objeto)
{
	//Verifica se a referencia para a estrutura é valida.
	if (ObjetoGerenciadoValido(Param_Objeto))
	{
		//Deleta a estrutura.
		Param_Objeto = nullptr;
	}
}