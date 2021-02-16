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
#include "SDK_Base.h"
#include "../Caren/Caren.h"
#include "../Caren/CarenBuffer.h"

//Importa o namespace base
using namespace CarenRengine;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Constantes;
      
//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace que contém as classes e funções de utilidades.
	namespace SDKUtilidades
	{
		//Classe que contém utilidades gerais para toda a plataforma.
		//Conversões - Estruturas - Copias - Alocações
		class Utilidades
		{
		public:
			Utilidades(){}
			~Utilidades(){}

			//Converte uma (String) gerenciada para um tipo não gerenciado (char*).
			//Utilize apenas o (delete) para excluir o ponteiro para os dados quando não for mais usar.
			char* ConverterStringToChar(String^ Param_Valor)
			{
				//Variavel que vai conter os dados convertidos.
				const char* CharConvertido;

				//Variavel que vai conter os dados de retorno.
				char* DadosRetorno = NULL;

				//Context Marshal.
				marshal_context ctx;

				//Obtém a largura dos dados.
				int Leng = Param_Valor->Length + 1;

				//Converte os dados.
				CharConvertido = ctx.marshal_as<const char*>(Param_Valor);

				//Cria os dados
				DadosRetorno = new char[Leng];

				//Copia os dados
				memcpy_s(DadosRetorno, Leng, CharConvertido, Leng);

				//O marshal_context é responsável por deletar a variavel que recebeu os dados convertidos.

				//Retorna o resultado.
				return DadosRetorno;
			}

			//Converte uma const char* valor para um WCHAR* valor.
			//Utilize apenas o (delete) para excluir o ponteiro para os dados quando não for mais usar.
			const WCHAR* ConverterConstCharToConstWCHAR(const char* Param_Valor)
			{
				//Variavel que vai receber o valor Convertido.
				const WCHAR* ConvertedData;

				//Obtém a quantidade de chars.
				int nChars = MultiByteToWideChar(CP_ACP, 0, Param_Valor, -1, NULL, 0);

				//Alocca os dados.
				ConvertedData = new WCHAR[nChars];

				//Converte os dados.
				MultiByteToWideChar(CP_ACP, 0, Param_Valor, -1, (LPWSTR)ConvertedData, nChars);

				//Retorna.
				return ConvertedData;
			}

			//Converte uma const char* valor para um WCHAR* valor.
			//Utilize apenas o (delete) para excluir o ponteiro para os dados quando não for mais usar.
			WCHAR* ConverterConstCharToWCHAR(const char* Param_Valor)
			{
				//Variavel que vai receber o valor Convertido.
				WCHAR* ConvertedData;

				//Obtém a quantidade de chars.
				int nChars = MultiByteToWideChar(CP_ACP, 0, Param_Valor, -1, NULL, 0);

				//Alocca os dados.
				ConvertedData = new WCHAR[nChars];

				//Converte os dados.
				MultiByteToWideChar(CP_ACP, 0, Param_Valor, -1, (LPWSTR)ConvertedData, nChars);

				//Retorna.
				return ConvertedData;
			}

			//Converte uma String gerenciada para um const WCHAR.
			//Utilize apenas o (delete) para excluir o ponteiro para os dados quando não for mais usar.
			const WCHAR* ConverterStringToConstWCHAR(String^ Param_Valor)
			{
				//Converte para char*
				char* Data01 = ConverterStringToChar(Param_Valor);

				//Converte para WCHAR*
				const WCHAR* DadosConvertidos = ConverterConstCharToConstWCHAR(Data01);

				//Deleta os dados01
				delete Data01;

				//Retorna o resultado
				return DadosConvertidos;
			}

			//Converte uma String gerenciada para um WCHAR.
			//Utilize apenas o (delete) para excluir o ponteiro para os dados quando não for mais usar.
			WCHAR* ConverterStringToWCHAR(String^ Param_Valor)
			{
				//Converte para char*
				char* Data01 = ConverterStringToChar(Param_Valor);
			
				//Converte para WCHAR*
				WCHAR* DadosConvertidos = ConverterConstCharToWCHAR(Data01);

				//Deleta os dados01
				delete Data01;

				//Retorna o resultado
				return DadosConvertidos;
			}

			//Converte uma String gerenciada para BSTR. Libere a string utilizando o método SysFreeString.
			BSTR ConverterStringToBSTR(String^ Param_Valor)
			{
				//Variavel que vai retornar o resultado.
				BSTR vi_BstrString = Nulo;

				//Converte a string para BSTR.
				vi_BstrString = reinterpret_cast<BSTR>(Marshal::StringToBSTR(Param_Valor).ToPointer());

				//Retorna o resultado.
				return vi_BstrString;
			}

			//Cria um Guid a parti de uma determinada String.
			_GUID CreateGuidFromString(String^ Param_DadosGuid)
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
				//Verifica se o OLECHAR é valido e libera a memória utilizada.
				if (ObjetoValido(DadosGuid))
					delete[] DadosGuid;

				//Retorna o resultado
				return GuidRetorno;
			}

			//Converte um determinado GUID para uma representação de String gerenciada.
			String^ ConverterGuidToString(_GUID Param_Guid)
			{
				//Variavel a ser retornada.
				String^ RetornoDados = nullptr;

				//Variavel que vai conter os dados convertidos.
				LPOLESTR DadosConvertidos = NULL;

				//Chama o método para obter uma string a parti do GUID.
				ResultadoCOM Hr = StringFromCLSID(const_cast<IID&>(Param_Guid), &DadosConvertidos);

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
				//Libera a memória utilizada pela String.
				if (ObjetoValido(DadosConvertidos))
					CoTaskMemFree(DadosConvertidos);

				//Retorna os dados
				return RetornoDados;
			}

			//Método responsável por traduzir em mensagem o código de erro.
			String^ TranslateCodeResult(HRESULT Param_HResultCode)
			{
				//Variavel que vai conter a mensagem.
				LPCTSTR MensagemHResult = NULL;;
				String^ MsgHResult = nullptr;

				//Variavel que vai ser utilizada para obter a mensagem.
				_com_error Err = (Param_HResultCode);

				//Verifica se existe algum erro
				if (Param_HResultCode == 0)
				{
					//Sai do método.
					goto Done;
				}

				//Obtém a mensagem de erro.
				MensagemHResult = Err.ErrorMessage();

				//Verifica se é valida
				if (MensagemHResult != NULL)
				{
					//Define a mensagem de retorno.
					MsgHResult = gcnew String(MensagemHResult);
				}
				else
				{
					//Mensagem não disponivel.
				}

			Done:;
				//Retorna o resultado.
				return MsgHResult;
			}

			//Função que copia dados da memoria de um buffer para outro de destino. Essa função permite definir um Index onde será iniciado
			//a copia dos dados para o buffer de destino.
			template<typename T>
			errno_t CopiarMemoria(T* Param_BufferDestino, unsigned int Param_SizeBufferDestino, T* Param_BufferOrigem, unsigned int Param_Index, unsigned int Param_QuantidadeElementos)
			{
				//Realiza a copia da memoria.
				return memcpy_s(Param_BufferDestino, Param_SizeBufferDestino, Param_BufferOrigem + Param_Index, Param_QuantidadeElementos * sizeof(T));
			}

			//Função que copia dados da memoria de um buffer para outro de destino.
			template<typename T>
			errno_t CopiarMemoria(T* Param_BufferDestino, unsigned int Param_SizeBufferDestino, T* Param_BufferOrigem, unsigned int Param_QuantidadeElementos)
			{
				//Realiza a copia da memoria.
				return memcpy_s(Param_BufferDestino, Param_SizeBufferDestino, Param_BufferOrigem, Param_QuantidadeElementos * sizeof(T));
			}

			//Método responsável por copiar itens de tipo(SIMPLES) de um array GERENCIADO para o NATIVO.
			template<typename TypeArray, typename TypeGerenciado>
			void CopiarItensTo_ArrayNativo(TypeArray** Param_ArrayNativo, cli::array<TypeGerenciado>^ Param_ArrayGerenciado, UINT32 Param_CountItens)
			{
				//Faz um for para realizar a copia.
				for (UINT32 i = 0; i < Param_CountItens; i++)
				{
					//Converte e define o valor do array gerenciado no nativo.
					(*Param_ArrayNativo)[i] = static_cast<TypeArray>(Param_ArrayGerenciado[i]);
				}
			}

			//Método responsável por copiar itens de tipo (SIMPLES) de um array NATIVO para o GERENCIADO.
			template<typename TipoArrayNativo, typename TipoGerenciado>
			void CopiarItensTo_ArrayGerenciado(cli::array<TipoGerenciado>^% Param_RefArrayGerenciado, TipoArrayNativo* Param_ArrayNativo, UINT32 Param_CountItens)
			{
				//Faz um for para realizar a copia.
				for (UINT32 i = 0; i < Param_CountItens; i++)
				{
					//Converte e define no array gerenciado os dados do nativo.
					Param_RefArrayGerenciado[i] = static_cast<TipoGerenciado>(Param_ArrayNativo[i]);
				}
			}

			//(MÉTODO EXPERIMENTAL)
			template<typename TipoArrayNativo, typename TipoArrayGerenciado>
			void CopiarBufferNativo_ToGerenciado(TipoArrayNativo** Param_Buffer, cli::array<TipoArrayGerenciado>^% Param_BufferGerenciado, UINT32 Param_TamanhoBuffer)
			{
				//Cria um pin para o buffer gerenciado.
				pin_ptr<TipoArrayGerenciado> PinToIndexZeroBuffer = &Param_BufferGerenciado[0];

				//Converte o pinptr para um buffer do tipo de destino.
				TipoArrayNativo* pBufferDestino = reinterpret_cast<TipoArrayNativo*>(PinToIndexZeroBuffer);

				//Verifica se é valido
				if (!ObjetoValido(pBufferDestino))
					throw gcnew NullReferenceException("(CopiarBufferNativo_ToGerenciado) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

				//Copia os dados do nativo para o gerenciado.
				std::copy(*Param_Buffer, (*Param_Buffer) + Param_TamanhoBuffer, pBufferDestino);
			}
		
			//(MÉTODO EXPERIMENTAL)
			template<typename TipoArrayNativo, typename TipoArrayGerenciado>
			void CopiarBufferGerenciado_ToNativo(cli::array<TipoArrayGerenciado>^% Param_BufferGerenciado, TipoArrayNativo* Param_BufferDestino, UINT32 Param_TamanhoBuffer)
			{
				//Cria um pin para o buffer gerenciado.
				pin_ptr<TipoArrayGerenciado> PinToIndexZeroBuffer = &Param_BufferGerenciado[0];

				//Converte o pinptr para o buffer de origem.
				TipoArrayNativo* pBufferOrigem = reinterpret_cast<TipoArrayNativo*>(PinToIndexZeroBuffer);

				//Verifica se é valido
				if (!ObjetoValido(pBufferOrigem))
					throw gcnew NullReferenceException("(CopiarBufferGerenciado_ToNativo) - Houve uma falha ao criar uma ligação para o buffer de origem gerenciado através do (pin_ptr).");

				//Copia os dados do nativo para o gerenciado.
				std::copy(pBufferOrigem, (pBufferOrigem) + Param_TamanhoBuffer, Param_BufferDestino);
			}

			//(MÉTODO EXPERIMENTAL) Método responsável por obter o ponteiro nativo na interface gerenciada e definir em uma matriz de ponteiros do mesmo tipo nativo.
			template<typename TipoInterfaceNativa, typename TipoInterfaceGerenciada>
			void CopiarPonteirosGerenciado_ToNativo(TipoInterfaceNativa** Param_ArrayDestinoNativo, cli::array<TipoInterfaceGerenciada^>^% Param_ArrayInterfacesGerenciado, UINT32 Param_Quantidade)
			{
				//Faz um for para copiar os dados.
				for (UINT32 i = 0; i < Param_Quantidade; i++)
				{
					//Recupera o ponteiro para a interface.
					RecuperarPonteiroCaren(reinterpret_cast<ICaren^>(Param_ArrayInterfacesGerenciado[i]), &(Param_ArrayDestinoNativo[i]));
				}
			}

			//(MÉTODO EXPERIMENTAL)
			template<typename TipoInterfaceNativa, typename TipoInterfaceGerenciada>
			void CopiarPonteirosNativo_ToGerenciado(cli::array<TipoInterfaceGerenciada^>^ Param_ArrayInterfacesDestino, TipoInterfaceNativa** Param_ArrayInterfacesNativas, UINT32 Param_Quantidade)
			{
				//Faz um for para definir os ponteiros nativos na interfaces gerenciadas.
				for (UINT32 i = 0; i < Param_Quantidade; i++)
				{
					(reinterpret_cast<ICaren^>(Param_ArrayInterfacesDestino[i]))->AdicionarPonteiro(Param_ArrayInterfacesNativas[i]);
				}
			}

			//Converte um ponteiro gerenciado para um ponteiro nativo.
			LPVOID ConverterPonteiroGerenciadorParaNativo(IntPtr Param_Ponteiro)
			{
				//Retorna o ponteiro nativo encapsulado pelo ponteiro gerenciado.
				return Param_Ponteiro.ToPointer();
			}

			//Converte um ponteiro nativo para um ponteiro gerenciado.
			IntPtr ConverterPonteiroNativoParaGerenciado(LPVOID Param_Ponteiro)
			{
				//Cria um ponteiro gerenciado para o ponteiro nativo.
				return IntPtr(Param_Ponteiro);
			}

			//Converte um IntPtr para uma HWND
			HWND ConverterIntPtrToHWND(IntPtr Param_WindowsHandleManaged)
			{
				//Converte o ponteiro para uma handle.
				return (HWND)Param_WindowsHandleManaged.ToPointer();
			}

			//Converte um IntPtr para uma Handle
			HANDLE ConverterIntPtrToHandle(IntPtr Param_WindowsHandleManaged)
			{
				//Converte o ponteiro para uma handle.
				return Param_WindowsHandleManaged.ToPointer();
			}

			//Converte uma HWND para IntPtr.
			IntPtr ConverterHWNDToIntPtr(HWND Param_HandleConverte)
			{
				//Retorna o IntPtr.
				return IntPtr(Param_HandleConverte);
			}

			//Converte uma Handle para IntPtr.
			IntPtr ConverterHandleToIntPtr(HANDLE Param_HandleConverte)
			{
				//Retorna o IntPtr.
				return IntPtr(Param_HandleConverte);
			}

			//Converte um delegate para um Ponteiro.
			IntPtr ConverterDelegateToPointer(Delegate^ Param_Delegate)
			{
				//Converte e retorna o ponteiro.
				return Marshal::GetFunctionPointerForDelegate(Param_Delegate);
			}

			//Converte um IntPtr para um tipo de ponteiro especificado.
			template<class ToClasse>
			ToClasse ConverterIntPtrTo(IntPtr Param_Pointer)
			{
				return static_cast<ToClasse>(Param_Pointer.ToPointer());
			}

			//Aloca um ponteiro para um delegate e retorna a handle alocada.
			GCHandle AlocarPointerDelegate(IntPtr Param_DelegateAlloc)
			{
				//Aloca e retorna a a handle.
				return GCHandle::Alloc(Param_DelegateAlloc);
			}

			template<class ToClasse>
			//Método responsável por converter um ponteiro de delegate em um delegate nativo.
			ToClasse ConverterPointerDelegateToNativeDelegate(IntPtr Param_PointerDelegate)
			{
				//Converte e retorna o resultado.
				return static_cast<ToClasse>(Param_PointerDelegate.ToPointer());
			}




			// CONVERSÕES DE ESTRUTURAS AUXILIARES.


			//Converte uma estrutura gerenciada(CA_DXGI_RGBA) para um ponteiro que contém um array dos 4 componentes da cor RGBA.
			//Chame um (delete[]) quando não precisar mais do ponteiro.
			FLOAT* Converter_DXGIRGBATo_FloatColor(CA_DXGI_RGBA^ Param_RGBA)
			{
				//Variavel que vai retornar os dados.
				FLOAT* pRGBAColor = new FLOAT[4];

				//Define os dados no ponteiro
				pRGBAColor[0] = Param_RGBA->Vermelho; //R
				pRGBAColor[1] = Param_RGBA->Verde;    //G
				pRGBAColor[2] = Param_RGBA->Azul;     //B
				pRGBAColor[3] = Param_RGBA->Alfa;     //A

				//Retorna o valor.
				return pRGBAColor;
			}

			//Converte uma estrutura gerenciada(CA_DXGI_RGBA) para um ponteiro que contém um array dos 4 componentes da cor RGBA.
			CA_DXGI_RGBA^ Converter_FloatColorTo_DXGIRGBA(FLOAT* pRGBAColor)
			{
				//Variavel a ser retornada.
				CA_DXGI_RGBA^ ColorRGBA = gcnew CA_DXGI_RGBA();

				//Preenche os dados da estrutura.
				ColorRGBA->Vermelho = pRGBAColor[0]; //R
				ColorRGBA->Verde = pRGBAColor[1];    //G
				ColorRGBA->Azul = pRGBAColor[2];     //B
				ColorRGBA->Alfa = pRGBAColor[3];     //A

				//Retorna o resultado
				return ColorRGBA;
			}


			//Converte a estrutura não gerenciada(RECT) para sua correspondencia gerenciada(CA_RECT).
			CA_RECT^ ConverterRECTUnmanagedToManaged(PRECT Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_RECT^ EstruturaRetorno = gcnew CA_RECT();

				//Define os dados da estrutura.
				EstruturaRetorno->Direita = Param_Estrutura->right;
				EstruturaRetorno->Esquerda = Param_Estrutura->left;
				EstruturaRetorno->Fundo = Param_Estrutura->bottom;
				EstruturaRetorno->Topo = Param_Estrutura->top;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_RECT) para sua correspondencia não gerenciada(RECT).
			PRECT ConverterRECTManagedToUnmanaged(CA_RECT^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				PRECT EstruturaRetorno = CriarEstrutura<RECT>();

				//Define os dados na estrutura.
				EstruturaRetorno->right = Param_Estrutura->Direita;
				EstruturaRetorno->left = Param_Estrutura->Esquerda;
				EstruturaRetorno->bottom = Param_Estrutura->Fundo;
				EstruturaRetorno->top = Param_Estrutura->Topo;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte a estrutura não gerenciada(LUID) para sua correspondencia gerenciada(CA_LUID).
			CA_LUID^ ConverterLUIDUnmanagedToManaged(PLUID Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_LUID^ EstruturaRetorno = gcnew CA_LUID();

				//Define os dados da estrutura.
				EstruturaRetorno->HighPart = Param_Estrutura->HighPart;
				EstruturaRetorno->LowPart = Param_Estrutura->LowPart;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_LUID) para sua correspondencia não gerenciada(LUID).
			PLUID ConverterLUIDManagedToUnmanaged(CA_LUID^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				PLUID EstruturaRetorno = CriarEstrutura<LUID>();

				//Define os dados na estrutura.
				EstruturaRetorno->HighPart = Param_Estrutura->HighPart;
				EstruturaRetorno->LowPart = Param_Estrutura->LowPart;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}

			//Converte a estrutura não gerenciada(BITMAPINFOHEADER) para sua correspondencia gerenciada(CA_BITMAPINFOHEADER).
			CA_BITMAPINFOHEADER^ ConverterBITMAPINFOHEADERUnmanaged_ToManaged(BITMAPINFOHEADER* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_BITMAPINFOHEADER^ EstruturaRetorno = gcnew CA_BITMAPINFOHEADER();

				//Define os dados da estrutura.
				EstruturaRetorno->biSize = static_cast<UInt32>(Param_Estrutura->biSize);
				EstruturaRetorno->biWidth = Param_Estrutura->biWidth;
				EstruturaRetorno->biHeight = Param_Estrutura->biHeight;
				EstruturaRetorno->biPlanes = Param_Estrutura->biPlanes;
				EstruturaRetorno->biBitCount = Param_Estrutura->biBitCount;
				EstruturaRetorno->biCompression = static_cast<UInt32>(Param_Estrutura->biCompression);
				EstruturaRetorno->biSizeImage = static_cast<UInt32>(Param_Estrutura->biSizeImage);
				EstruturaRetorno->biXPelsPerMeter = Param_Estrutura->biXPelsPerMeter;
				EstruturaRetorno->biYPelsPerMeter = Param_Estrutura->biYPelsPerMeter;
				EstruturaRetorno->biClrUsed = static_cast<UInt32>(Param_Estrutura->biClrUsed);
				EstruturaRetorno->biClrImportant = static_cast<UInt32>(Param_Estrutura->biClrImportant);

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_BITMAPINFOHEADER) para sua correspondencia não gerenciada(BITMAPINFOHEADER).
			BITMAPINFOHEADER* ConverterBITMAPINFOHEADERManaged_ToUnamaged(CA_BITMAPINFOHEADER^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				BITMAPINFOHEADER* EstruturaRetorno = CriarEstrutura<BITMAPINFOHEADER>();

				//Define os dados da estrutura.
				EstruturaRetorno->biSize = static_cast<DWORD>(Param_Estrutura->biSize);
				EstruturaRetorno->biWidth = Param_Estrutura->biWidth;
				EstruturaRetorno->biHeight = Param_Estrutura->biHeight;
				EstruturaRetorno->biPlanes = Param_Estrutura->biPlanes;
				EstruturaRetorno->biBitCount = Param_Estrutura->biBitCount;
				EstruturaRetorno->biCompression = static_cast<DWORD>(Param_Estrutura->biCompression);
				EstruturaRetorno->biSizeImage = static_cast<DWORD>(Param_Estrutura->biSizeImage);
				EstruturaRetorno->biXPelsPerMeter = Param_Estrutura->biXPelsPerMeter;
				EstruturaRetorno->biYPelsPerMeter = Param_Estrutura->biYPelsPerMeter;
				EstruturaRetorno->biClrUsed = static_cast<DWORD>(Param_Estrutura->biClrUsed);
				EstruturaRetorno->biClrImportant = static_cast<DWORD>(Param_Estrutura->biClrImportant);

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}

			//Converte um GUID que define o subtipo de um midia principal para a enumeração gerenciada(CA_MEDIA_SUBTYPES).
			SDKBase::Enumeracoes::CA_MEDIA_SUBTYPES ConverterGUIDSubtipoMidia_ToMidia_SubTipo(GUID Param_GuidSubTipoMidia)
			{
				//Variavel que via conter o subtipo.
				CA_MEDIA_SUBTYPES FormatoTipoPrincipal;

				/////////////////////
				//FORMATOS DE AUDIO//
				/////////////////////

				if (MEDIASUBTYPE_RAW_AAC1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_RAW_ACC1;

				}
				else if (MFAudioFormat_AAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_AAC;

				}
				else if (MFAudioFormat_ADTS == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_ADTS;

				}
				else if (MFAudioFormat_ALAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_ALAC;

				}
				else if (MFAudioFormat_AMR_NB == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_AMR_NB;

				}
				else if (MFAudioFormat_AMR_WB == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_AMR_WB;

				}
				else if (MFAudioFormat_AMR_WP == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_AMR_WP;

				}
				else if (MFAudioFormat_Dolby_AC3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Dolby_AC3;

				}
				else if (MFAudioFormat_Dolby_AC3_SPDIF == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Dolby_AC3_SPDIF;

				}
				else if (MFAudioFormat_Dolby_DDPlus == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Dolby_DDPlus;

				}
				else if (MFAudioFormat_DRM == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_DRM;

				}
				else if (MFAudioFormat_DTS == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_DTS;

				}
				else if (MFAudioFormat_FLAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_FLAC;

				}
				else if (MFAudioFormat_Float == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Float;

				}
				else if (MFAudioFormat_Float_SpatialObjects == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Float_SpatialObjects;

				}
				else if (MFAudioFormat_MP3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_MP3;

				}
				else if (MFAudioFormat_MPEG == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_MPEG;

				}
				else if (MFAudioFormat_MSP1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_MSP1;

				}
				else if (MFAudioFormat_Opus == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_Opus;

				}
				else if (MFAudioFormat_PCM == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_PCM;

				}
				else if (MFAudioFormat_WMASPDIF == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_WMASPDIF;

				}
				else if (MFAudioFormat_WMAudio_Lossless == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_WMAudio_Lossless;

				}
				else if (MFAudioFormat_WMAudioV8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_WMAudioV8;

				}
				else if (MFAudioFormat_WMAudioV9 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFAudioFormat_WMAudioV9;

				}



				/////////////////////
				//FORMATOS DE VIDEO//
				/////////////////////

				else if (MFVideoFormat_RGB8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB8;

				}
				else if (MFVideoFormat_RGB555 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB555;

				}
				else if (MFVideoFormat_RGB565 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB565;

				}
				else if (MFVideoFormat_RGB24 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB24;

				}
				else if (MFVideoFormat_RGB32 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB32;

				}
				else if (MFVideoFormat_ARGB32 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_ARGB32;

				}
				else if (MFVideoFormat_A2R10G10B10 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_A2R10G10B10;

				}
				else if (MFVideoFormat_A16B16G16R16F == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_A16B16G16R16F;

				}
				else if (MFVideoFormat_AI44 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_AI44;

				}
				else if (MFVideoFormat_AYUV == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_AYUV;

				}
				else if (MFVideoFormat_I420 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_I420;

				}
				else if (MFVideoFormat_IYUV == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_IYUV;

				}
				else if (MFVideoFormat_NV11 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_NV11;

				}
				else if (MFVideoFormat_NV12 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_NV12;

				}
				else if (MFVideoFormat_UYVY == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_UYVY;

				}
				else if (MFVideoFormat_Y41P == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y41P;

				}
				else if (MFVideoFormat_Y41T == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y41T;

				}
				else if (MFVideoFormat_Y42T == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y42T;

				}
				else if (MFVideoFormat_YUY2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_YUY2;

				}
				else if (MFVideoFormat_YVU9 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_YVU9;

				}
				else if (MFVideoFormat_YV12 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_YV12;

				}
				else if (MFVideoFormat_YVYU == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_YVYU;

				}
				else if (MFVideoFormat_P010 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_P010;

				}
				else if (MFVideoFormat_P016 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_P016;

				}
				else if (MFVideoFormat_P210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_P210;

				}
				else if (MFVideoFormat_P216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_P216;

				}
				else if (MFVideoFormat_v210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_v210;

				}
				else if (MFVideoFormat_v216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_v216;

				}
				else if (MFVideoFormat_v410 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_v410;

				}
				else if (MFVideoFormat_Y210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y210;

				}
				else if (MFVideoFormat_Y216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y216;

				}
				else if (MFVideoFormat_Y410 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y410;

				}
				else if (MFVideoFormat_Y416 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_Y416;

				}
				else if (MFVideoFormat_L8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_L8;

				}
				else if (MFVideoFormat_L16 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_L16;

				}
				else if (MFVideoFormat_D16 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_D16;

				}
				else if (MFVideoFormat_DV25 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DV25;

				}
				else if (MFVideoFormat_DV50 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DV50;

				}
				else if (MFVideoFormat_DVC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DVC;

				}
				else if (MFVideoFormat_DVH1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DVH1;

				}
				else if (MFVideoFormat_DVHD == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DVHD;

				}
				else if (MFVideoFormat_DVSD == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DVSD;

				}
				else if (MFVideoFormat_DVSL == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_DVSL;

				}
				else if (MFVideoFormat_H263 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_H263;

				}
				else if (MFVideoFormat_H264 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_H264;

				}
				else if (MFVideoFormat_H265 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_H265;

				}
				else if (MFVideoFormat_H264_ES == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_H264_ES;

				}
				else if (MFVideoFormat_HEVC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_HEVC;

				}
				else if (MFVideoFormat_HEVC_ES == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_HEVC_ES;

				}
				else if (MFVideoFormat_M4S2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_M4S2;

				}
				else if (MFVideoFormat_MJPG == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MJPG;

				}
				else if (MFVideoFormat_MP43 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MP43;

				}
				else if (MFVideoFormat_MP4S == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MP4S;

				}
				else if (MFVideoFormat_MP4V == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MP4V;

				}
				else if (MFVideoFormat_MPEG2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_RGB8;

				}
				else if (MFVideoFormat_VP80 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_VP80;

				}
				else if (MFVideoFormat_VP90 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_VP90;

				}
				else if (MFVideoFormat_MPG1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MPG1;

				}
				else if (MFVideoFormat_MSS1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MSS1;

				}
				else if (MFVideoFormat_MSS2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_MSS2;

				}
				else if (MFVideoFormat_WMV1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_WMV1;

				}
				else if (MFVideoFormat_WMV2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_WMV2;

				}
				else if (MFVideoFormat_WMV3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_WMV3;

				}
				else if (MFVideoFormat_WVC1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_WVC1;

				}
				else if (MFVideoFormat_420O == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::MFVideoFormat_420O;

				}
				else
				{
					//Formato desconhecido.
					FormatoTipoPrincipal = CA_MEDIA_SUBTYPES::FormatoMidia_Desconhecido;
				}

				//Retorna o formato da midia principal.
				return FormatoTipoPrincipal;
			}

			//Converte a estrutura não gerenciada(PROPBAG2) para sua correspondencia gerenciada(CA_PROPBAG2).
			CA_PROPBAG2^ ConverterPROPBAG2UnmanagedToManaged(PROPBAG2* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_PROPBAG2^ EstruturaRetorno = gcnew CA_PROPBAG2();

				//Define o restante dos dados.
				EstruturaRetorno->dwType = Param_Estrutura->dwType;
				EstruturaRetorno->vt = Param_Estrutura->vt;
				EstruturaRetorno->dwHint = Param_Estrutura->dwHint;
				EstruturaRetorno->cfType = Param_Estrutura->cfType;
				EstruturaRetorno->pstrName = ObjetoValido(Param_Estrutura->pstrName) ? gcnew String(Param_Estrutura->pstrName) : nullptr;
				EstruturaRetorno->clsid = Param_Estrutura->clsid == GUID_NULL ? ConverterGuidToString(Param_Estrutura->clsid) : nullptr;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_PROPBAG2) para sua correspondencia não gerenciada(PROPBAG2).
			PROPBAG2* ConverterPROPBAG2ManagedToUnamaged(CA_PROPBAG2^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				PROPBAG2* EstruturaRetorno = CriarEstrutura<PROPBAG2>();

				//Define o restante dos dados.
				EstruturaRetorno->dwType = Param_Estrutura->dwType;
				EstruturaRetorno->vt = Param_Estrutura->vt;
				EstruturaRetorno->dwHint = Param_Estrutura->dwHint;
				EstruturaRetorno->cfType = Param_Estrutura->cfType;
				EstruturaRetorno->pstrName = StringObjetoValido(Param_Estrutura->pstrName) ? ConverterStringToWCHAR(Param_Estrutura->pstrName) : NULL;
				EstruturaRetorno->clsid = StringObjetoValido(Param_Estrutura->clsid) ? CreateGuidFromString(Param_Estrutura->clsid) : GUID_NULL;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}

			//Converte a estrutura não gerenciada(SECURITY_ATTRIBUTES) para sua correspondencia gerenciada(CA_SECURITY_ATTRIBUTES).
			CA_SECURITY_ATTRIBUTES^ ConverterSECURITY_ATTRIBUTESUnmanagedToManaged(SECURITY_ATTRIBUTES* Param_AttrSeguranca)
			{
				//Cria a estrutura a ser retornada.
				CA_SECURITY_ATTRIBUTES^ EstruturaRetorno = gcnew CA_SECURITY_ATTRIBUTES();
				CA_SECURITY_DESCRIPTOR^ DescritorSegurança = nullptr;

				//Preenche os dados da estrutura principal
				EstruturaRetorno->bInheritHandle = Param_AttrSeguranca->bInheritHandle;
				EstruturaRetorno->SizeEstrutura = sizeof(SECURITY_ATTRIBUTES);

				//Verifica se for fornecido o descritor de segurança
				if (ObjetoValido(Param_AttrSeguranca->lpSecurityDescriptor))
				{
					//Cria a estrutura do descritor de segurança
					DescritorSegurança = gcnew CA_SECURITY_DESCRIPTOR();

					//Prenche os dados base
					DescritorSegurança->Control = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Control;
					DescritorSegurança->Revisao = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Revision;
					DescritorSegurança->Sbz1 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sbz1;

					//Preenche os dados dos ponteiros
					if (ObjetoValido(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl))
					{
						//Cria a estrutura
						DescritorSegurança->Dacl = gcnew CA_ACL();

						//Preenche os dados.
						DescritorSegurança->Dacl->AceCount = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl->AceCount;
						DescritorSegurança->Dacl->AclRevision = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl->AclRevision;
						DescritorSegurança->Dacl->AclSize = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl->AclSize;
						DescritorSegurança->Dacl->Sbz1 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl->Sbz1;
						DescritorSegurança->Dacl->Sbz2 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl->Sbz2;
					}
					if (ObjetoValido(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl))
					{
						//Cria a estrutura
						DescritorSegurança->Dacl = gcnew CA_ACL();

						//Preenche os dados.
						DescritorSegurança->Sacl->AceCount = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl->AceCount;
						DescritorSegurança->Sacl->AclRevision = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl->AclRevision;
						DescritorSegurança->Sacl->AclSize = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl->AclSize;
						DescritorSegurança->Sacl->Sbz1 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl->Sbz1;
						DescritorSegurança->Sacl->Sbz2 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sacl->Sbz2;
					}
					if (ObjetoValido(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Group))
					{
						//Converte o ponteiro e define na estrutura.
						DescritorSegurança->Group = ConverterPonteiroNativoParaGerenciado(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Group);
					}
					if (ObjetoValido(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Owner))
					{
						//Converte o ponteiro e define na estrutura.
						DescritorSegurança->Owner = ConverterPonteiroNativoParaGerenciado(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Owner);
					}
				}
				else
				{
					//Não foi forneceido o descritor de segurança
					EstruturaRetorno->lpSecurityDescriptor = nullptr;
				}

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_SECURITY_ATTRIBUTES) para sua correspondencia não gerenciada(SECURITY_ATTRIBUTES).
			SECURITY_ATTRIBUTES* ConverterSECURITY_ATTRIBUTESManagedToUnamaged(CA_SECURITY_ATTRIBUTES^ Param_AttrSeguranca)
			{
				//Estrutura que será retornada ao usuário.
				SECURITY_ATTRIBUTES* pAtributosSeguranca = CriarEstrutura<SECURITY_ATTRIBUTES>();
				SECURITY_DESCRIPTOR* pDescritorSeguranca = NULL;

				//Preenche tudo com zero e inicializa a estrutura principal.
				ZeroMemory(pAtributosSeguranca, sizeof(pAtributosSeguranca));

				//Preenche os dados da estrutura Principal.
				pAtributosSeguranca->bInheritHandle = static_cast<BOOL>(Param_AttrSeguranca->bInheritHandle);
				pAtributosSeguranca->nLength = sizeof(SECURITY_ATTRIBUTES);

				//Verifica se foi fornencido um descritor de segurança personalizado
				if (ObjetoGerenciadoValido(Param_AttrSeguranca->lpSecurityDescriptor))
				{
					//Cria a estrutura para o descritor de segurança.
					pDescritorSeguranca = CriarEstrutura<SECURITY_DESCRIPTOR>();

					//Preenche tudo com zero e inicializa a estrutura.
					ZeroMemory(pDescritorSeguranca, sizeof(pDescritorSeguranca));

					//Preenche os dados da estrutura do descritor de segurança
					pDescritorSeguranca->Control = Param_AttrSeguranca->lpSecurityDescriptor->Control;
					pDescritorSeguranca->Revision = Param_AttrSeguranca->lpSecurityDescriptor->Revisao;
					if (ObjetoGerenciadoValido(Param_AttrSeguranca->lpSecurityDescriptor->Dacl))
					{
						//Cria a estrutura.
						pDescritorSeguranca->Dacl = CriarEstrutura<ACL>();

						//Preenche os dados.
						pDescritorSeguranca->Dacl->AceCount = Param_AttrSeguranca->lpSecurityDescriptor->Dacl->AceCount;
						pDescritorSeguranca->Dacl->AclRevision = Param_AttrSeguranca->lpSecurityDescriptor->Dacl->AclRevision;
						pDescritorSeguranca->Dacl->AclSize = Param_AttrSeguranca->lpSecurityDescriptor->Dacl->AclSize;
						pDescritorSeguranca->Dacl->Sbz1 = Param_AttrSeguranca->lpSecurityDescriptor->Dacl->Sbz1;
						pDescritorSeguranca->Dacl->Sbz2 = Param_AttrSeguranca->lpSecurityDescriptor->Dacl->Sbz2;
					}
					if (ObjetoGerenciadoValido(Param_AttrSeguranca->lpSecurityDescriptor->Dacl))
					{
						//Cria a estrutura.
						pDescritorSeguranca->Sacl = CriarEstrutura<ACL>();

						//Preenche os dados.
						pDescritorSeguranca->Sacl->AceCount = Param_AttrSeguranca->lpSecurityDescriptor->Sacl->AceCount;
						pDescritorSeguranca->Sacl->AclRevision = Param_AttrSeguranca->lpSecurityDescriptor->Sacl->AclRevision;
						pDescritorSeguranca->Sacl->AclSize = Param_AttrSeguranca->lpSecurityDescriptor->Sacl->AclSize;
						pDescritorSeguranca->Sacl->Sbz1 = Param_AttrSeguranca->lpSecurityDescriptor->Sacl->Sbz1;
						pDescritorSeguranca->Sacl->Sbz2 = Param_AttrSeguranca->lpSecurityDescriptor->Sacl->Sbz2;
					}
					if (Param_AttrSeguranca->lpSecurityDescriptor->Owner != IntPtr::Zero)
					{
						//Converte o ponteiro gerenciado para o nativo.
						pDescritorSeguranca->Owner = ConverterPonteiroGerenciadorParaNativo(Param_AttrSeguranca->lpSecurityDescriptor->Owner);
					}
					if (Param_AttrSeguranca->lpSecurityDescriptor->Group != IntPtr::Zero)
					{
						//Converte o ponteiro gerenciado para o nativo.
						pDescritorSeguranca->Owner = ConverterPonteiroGerenciadorParaNativo(Param_AttrSeguranca->lpSecurityDescriptor->Group);
					}

					//Define a estrutura secundaria na primaria
					pAtributosSeguranca->lpSecurityDescriptor = pDescritorSeguranca;
				}
				else
				{
					//Não foi fornecido um descritor de segurança
					pAtributosSeguranca->lpSecurityDescriptor = NULL;
				}

				//Retorna a estrutura não gerenciada
				return pAtributosSeguranca;
			}



			// CORE AUDIO ESTRUTURAS

			//Converte a estrutura não gerenciada(WAVEFORMATEX) para sua correspondencia gerenciada(CA_WAVEFORMATEX).
			CA_WAVEFORMATEX^ ConverterWaveFormatexUnmanagedToManaged(WAVEFORMATEX* pWaveFormat)
			{
				//Cria a estrutura a ser retornada.
				CA_WAVEFORMATEX^ EstruturaRetorno = gcnew CA_WAVEFORMATEX();

				//Define os dados na estrutura
				EstruturaRetorno->nBlockAlign = static_cast<UInt16>(pWaveFormat->nBlockAlign);
				EstruturaRetorno->wBitsPerSample = static_cast<UInt16>(pWaveFormat->wBitsPerSample);
				EstruturaRetorno->nAvgBytesPerSec = static_cast<UInt32>(pWaveFormat->nAvgBytesPerSec);
				EstruturaRetorno->nChannels = static_cast<UInt16>(pWaveFormat->nChannels);
				EstruturaRetorno->nSamplesPerSec = static_cast<UInt32>(pWaveFormat->nSamplesPerSec);
				EstruturaRetorno->wFormatTag = static_cast<UInt16>(pWaveFormat->wFormatTag);
				EstruturaRetorno->cbSize = static_cast<UInt16>(pWaveFormat->cbSize);
				EstruturaRetorno->TamanhoEstrutura = sizeof(WAVEFORMATEX);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_WAVEFORMATEX) para sua correspondencia não gerenciada(WAVEFORMATEX).
			WAVEFORMATEX* ConverterWaveFormatexManagedToUnamaged(CA_WAVEFORMATEX^ Param_WaveFormatex)
			{
				//Estrutura que será retornada ao usuário.
				WAVEFORMATEX* pWaveFormato = CriarEstrutura<WAVEFORMATEX>();

				//Define os dados na estrutura.
				pWaveFormato->cbSize = Param_WaveFormatex->cbSize;
				pWaveFormato->nAvgBytesPerSec = Param_WaveFormatex->nAvgBytesPerSec;
				pWaveFormato->nBlockAlign = Param_WaveFormatex->nBlockAlign;
				pWaveFormato->nChannels = Param_WaveFormatex->nChannels;
				pWaveFormato->nSamplesPerSec = Param_WaveFormatex->nSamplesPerSec;
				pWaveFormato->wBitsPerSample = Param_WaveFormatex->wBitsPerSample;
				pWaveFormato->wFormatTag = Param_WaveFormatex->wFormatTag;

				//Retorna a estrutura não gerenciada
				return pWaveFormato;
			}


			//Converte a estrutura não gerenciada(WAVEFORMATEXTENSIBLE) para sua correspondencia gerenciada(CA_WAVEFORMATEXEXTENSIBLE).
			CA_WAVEFORMATEXEXTENSIBLE^ ConverterWaveformatExtensibleUnmanagedToManaged(WAVEFORMATEXTENSIBLE* pWaveFormatExtensible)
			{
				//Cria a estrutura a ser retornada.
				CA_WAVEFORMATEXEXTENSIBLE^ EstruturaRetorno = gcnew CA_WAVEFORMATEXEXTENSIBLE();

				//Define os dados da estrutura WaveFormatex.
				EstruturaRetorno->Format = ConverterWaveFormatexUnmanagedToManaged(&pWaveFormatExtensible->Format);

				//Define o restante dos dados.
				EstruturaRetorno->dwChannelMask = static_cast<UInt32>(pWaveFormatExtensible->dwChannelMask);
				EstruturaRetorno->wValidBitsPerSample = static_cast<UInt16>(pWaveFormatExtensible->Samples.wValidBitsPerSample);
				EstruturaRetorno->wSamplesPerBlock = static_cast<UInt16>(pWaveFormatExtensible->Samples.wSamplesPerBlock);
				EstruturaRetorno->SubFormato = ConverterGuidToString(pWaveFormatExtensible->SubFormat);
				EstruturaRetorno->Reservado = static_cast<UInt16>(pWaveFormatExtensible->Samples.wReserved);
				EstruturaRetorno->TamanhoEstrutura = sizeof(WAVEFORMATEXTENSIBLE);

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_WAVEFORMATEXEXTENSIBLE) para sua correspondencia não gerenciada(WAVEFORMATEXTENSIBLE).
			WAVEFORMATEXTENSIBLE* ConverterWaveformatExtensibleManagedToUnamaged(CA_WAVEFORMATEXEXTENSIBLE^ Param_WaveFormatex)
			{
				//Estrutura que será retornada ao usuário.
				WAVEFORMATEXTENSIBLE* pWaveFormatoEx = CriarEstrutura<WAVEFORMATEXTENSIBLE>();
				WAVEFORMATEX* vi_pWavFormatTemp = ConverterWaveFormatexManagedToUnamaged(Param_WaveFormatex->Format);

				//Preenche os dados da estrutura principal.
				pWaveFormatoEx->dwChannelMask = Param_WaveFormatex->dwChannelMask;
				pWaveFormatoEx->SubFormat = CreateGuidFromString(Param_WaveFormatex->SubFormato);
				pWaveFormatoEx->Samples.wSamplesPerBlock = Param_WaveFormatex->wSamplesPerBlock;
				pWaveFormatoEx->Samples.wValidBitsPerSample = Param_WaveFormatex->wValidBitsPerSample;
				pWaveFormatoEx->Samples.wReserved = Param_WaveFormatex->Reservado;

				//Preenche os dados da estrutura secundaria.
				pWaveFormatoEx->Format = *vi_pWavFormatTemp;

				//Libera a memória utilizada pela estrutura
				DeletarEstruturaSafe(&vi_pWavFormatTemp);

				//Retorna a estrutura não gerenciada
				return pWaveFormatoEx;
			}


			//Converte a estrutura não gerenciada(AudioClientProperties) para sua correspondencia gerenciada(CA_AudioClientProperties).
			CA_AudioClientProperties^ ConverterCoreAudio_AudioClientPropertiesUnmanagedToManaged(AudioClientProperties* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_AudioClientProperties^ EstruturaRetorno = gcnew CA_AudioClientProperties();

				//Define os dados na estrutura
				EstruturaRetorno->bIsOffload = static_cast<Boolean>(Param_Estrutura->bIsOffload);
				EstruturaRetorno->cbSize = static_cast<unsigned int>(Param_Estrutura->cbSize);
				EstruturaRetorno->Options = static_cast<CA_AUDCLNT_STREAMOPTIONS>(Param_Estrutura->Options);
				EstruturaRetorno->eCategory = static_cast<CA_AUDIO_STREAM_CATEGORY>(Param_Estrutura->eCategory);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_AudioClientProperties) para sua correspondencia não gerenciada(AudioClientProperties).
			AudioClientProperties* ConverterCoreAudio_AudioClientPropertiesManagedToUnamaged(CA_AudioClientProperties^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				AudioClientProperties* EstruturaRetorno = CriarEstrutura<AudioClientProperties>();

				//Define os dados na estrutura.
				EstruturaRetorno->bIsOffload = static_cast<Boolean>(Param_Estrutura->bIsOffload);
				EstruturaRetorno->cbSize = static_cast<unsigned int>(Param_Estrutura->cbSize);
				EstruturaRetorno->Options = static_cast<AUDCLNT_STREAMOPTIONS>(Param_Estrutura->Options);
				EstruturaRetorno->eCategory = static_cast<AUDIO_STREAM_CATEGORY>(Param_Estrutura->eCategory);

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}




			// MEDIA FOUNDATION ESTRUTURAS


			//Converte a estrutura não gerenciada(_MFT_INPUT_STREAM_INFO) para sua correspondencia gerenciada(CA_MFT_INPUT_STREAM_INFO).
			CA_MFT_INPUT_STREAM_INFO^ ConverterMFT_INPUT_STREAM_INFOUnmanagedToManaged(_MFT_INPUT_STREAM_INFO* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_MFT_INPUT_STREAM_INFO^ EstruturaRetorno = gcnew CA_MFT_INPUT_STREAM_INFO();

				//Define os dados na estrutura.
				EstruturaRetorno->Alinhamento = Param_Estrutura->cbAlignment;
				EstruturaRetorno->MaxLookahead = Param_Estrutura->cbMaxLookahead;
				EstruturaRetorno->Size = Param_Estrutura->cbSize;
				EstruturaRetorno->Flags = Param_Estrutura->dwFlags;
				EstruturaRetorno->LatenciaMaxima = Param_Estrutura->hnsMaxLatency;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_MFT_INPUT_STREAM_INFO) para sua correspondencia não gerenciada(_MFT_INPUT_STREAM_INFO).
			_MFT_INPUT_STREAM_INFO* ConverterMFT_INPUT_STREAM_INFOManagedToUnamaged(CA_MFT_INPUT_STREAM_INFO^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				_MFT_INPUT_STREAM_INFO* EstruturaRetorno = CriarEstrutura<_MFT_INPUT_STREAM_INFO>();

				//Define os dados na estrutura.
				EstruturaRetorno->cbAlignment = Param_Estrutura->Alinhamento;
				EstruturaRetorno->cbMaxLookahead = Param_Estrutura->MaxLookahead;
				EstruturaRetorno->cbSize = Param_Estrutura->Size;
				EstruturaRetorno->dwFlags = Param_Estrutura->Flags;
				EstruturaRetorno->hnsMaxLatency = Param_Estrutura->LatenciaMaxima;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte a estrutura não gerenciada(_MFT_OUTPUT_STREAM_INFO) para sua correspondencia gerenciada(CA_MFT_OUTPUT_STREAM_INFO).
			CA_MFT_OUTPUT_STREAM_INFO^ ConverterMFT_OUTPUT_STREAM_INFOUnmanagedToManaged(_MFT_OUTPUT_STREAM_INFO* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_MFT_OUTPUT_STREAM_INFO^ EstruturaRetorno = gcnew CA_MFT_OUTPUT_STREAM_INFO();

				//Define os dados na estrutura.
				EstruturaRetorno->Alinhamento = Param_Estrutura->cbAlignment;
				EstruturaRetorno->Size = Param_Estrutura->cbSize;
				EstruturaRetorno->Flags = Param_Estrutura->dwFlags;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_MFT_OUTPUT_STREAM_INFO) para sua correspondencia não gerenciada(_MFT_OUTPUT_STREAM_INFO).
			_MFT_OUTPUT_STREAM_INFO* ConverterMFT_OUTPUT_STREAM_INFOManagedToUnamaged(CA_MFT_OUTPUT_STREAM_INFO^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				_MFT_OUTPUT_STREAM_INFO* EstruturaRetorno = CriarEstrutura<_MFT_OUTPUT_STREAM_INFO>();

				//Define os dados na estrutura.
				EstruturaRetorno->cbAlignment = Param_Estrutura->Alinhamento;
				EstruturaRetorno->cbSize = Param_Estrutura->Size;
				EstruturaRetorno->dwFlags = Param_Estrutura->Flags;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte a estrutura não gerenciada(_MFT_OUTPUT_DATA_BUFFER) para sua correspondencia gerenciada(CA_MFT_OUTPUT_DATA_BUFFER).
			CA_MFT_OUTPUT_DATA_BUFFER^ ConverterMFT_OUTPUT_DATA_BUFFERUnmanagedToManaged(_MFT_OUTPUT_DATA_BUFFER* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				CA_MFT_OUTPUT_DATA_BUFFER^ EstruturaRetorno = gcnew CA_MFT_OUTPUT_DATA_BUFFER();

				//Define os dados na estrutura.
				EstruturaRetorno->Status = static_cast<CA_MFT_OUTPUT_DATA_BUFFER_FLAGS>(Param_Estrutura->dwStatus);
				EstruturaRetorno->FluxoID = Param_Estrutura->dwStreamID;
				if (ObjetoValido(Param_Estrutura->pSample))
				{
					//Variavel que vai conter o ponteiro para a amostra.
					ICaren^ AmostraMidia = gcnew Caren();

					//Define o ponteiro da amostra
					AmostraMidia->AdicionarPonteiro(Param_Estrutura->pSample);
				}
				if (ObjetoValido(Param_Estrutura->pEvents))
				{
					//Variavel que vai conter o ponteiro para a IMFCollection.
					ICaren^ Collection = gcnew Caren();

					//Define o ponteiro da coleção.
					Collection->AdicionarPonteiro(Param_Estrutura->pEvents);
				}

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_MFT_OUTPUT_DATA_BUFFER) para sua correspondencia não gerenciada(_MFT_OUTPUT_DATA_BUFFER).
			_MFT_OUTPUT_DATA_BUFFER* ConverterMFT_OUTPUT_DATA_BUFFERManagedToUnamaged(CA_MFT_OUTPUT_DATA_BUFFER^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				_MFT_OUTPUT_DATA_BUFFER* EstruturaRetorno = CriarEstrutura<_MFT_OUTPUT_DATA_BUFFER>();

				//Define os dados na estrutura.
				EstruturaRetorno->dwStatus = static_cast<DWORD>(Param_Estrutura->Status);
				EstruturaRetorno->dwStreamID = Param_Estrutura->FluxoID;
				if (ObjetoGerenciadoValido(Param_Estrutura->AmostraMidia))
				{
					//Ponteiro para a amostra.
					IMFSample* pAmostra = NULL;

					//Recupera o ponteiro
					reinterpret_cast<ICaren^>(Param_Estrutura->AmostraMidia)->RecuperarPonteiro((LPVOID*)&pAmostra);

					//Define na estrutura.
					EstruturaRetorno->pSample = pAmostra;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->ColecaoEventos))
				{
					//Ponteiro para coleção.
					IMFCollection* pCollection = NULL;

					//Recupera o ponteiro
					static_cast<ICaren^>(Param_Estrutura->ColecaoEventos)->RecuperarPonteiro((LPVOID*)&pCollection);

					//Define na estrutura.
					EstruturaRetorno->pEvents = pCollection;
				}

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE).
			MFTOPONODE_ATTRIBUTE_UPDATE* ConverterTopoNodeAttributesToUnamaged(CA_MFTOPONODE_ATTRIBUTE_UPDATE^ Param_ManagedStruct)
			{
				//Variavel que vai ser retornada.
				MFTOPONODE_ATTRIBUTE_UPDATE* pConvertedStruct = CriarEstrutura<MFTOPONODE_ATTRIBUTE_UPDATE>();

				//Define os valores
				pConvertedStruct->attrType = static_cast<MF_ATTRIBUTE_TYPE>(Param_ManagedStruct->TipoAtributo);
				pConvertedStruct->d = Param_ManagedStruct->d;
				pConvertedStruct->guidAttributeKey = CreateGuidFromString(Param_ManagedStruct->GUID);
				pConvertedStruct->NodeId = Param_ManagedStruct->NodeId;
				pConvertedStruct->u32 = Param_ManagedStruct->u32;
				pConvertedStruct->u64 = Param_ManagedStruct->u64;

				//Retorna a estrutura.
				return pConvertedStruct;
			}

			//Converte uma estrutura não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE).
			CA_MFTOPONODE_ATTRIBUTE_UPDATE^ ConverterTopoNodeAttributesToManaged(MFTOPONODE_ATTRIBUTE_UPDATE* Param_EstruturaNativa)
			{
				//Variavel que vai ser retornada.
				CA_MFTOPONODE_ATTRIBUTE_UPDATE^ EstruturaConvertida = gcnew CA_MFTOPONODE_ATTRIBUTE_UPDATE();

				//Define os valores
				EstruturaConvertida->TipoAtributo = static_cast<SDKBase::Enumeracoes::CA_MF_ATTRIBUTE_TYPE>(Param_EstruturaNativa->attrType);
				EstruturaConvertida->GUID = ConverterGuidToString(Param_EstruturaNativa->guidAttributeKey);
				EstruturaConvertida->NodeId = Param_EstruturaNativa->NodeId;
				EstruturaConvertida->d = Param_EstruturaNativa->d;
				EstruturaConvertida->u32 = Param_EstruturaNativa->u32;
				EstruturaConvertida->u64 = Param_EstruturaNativa->u64;

				//Retorna a estrutura.
				return EstruturaConvertida;
			}


			//Converte uma estrutura gerenciada(CA_MF_SINK_WRITER_STATISTICS) para sua correspondencia não gerenciada(MF_SINK_WRITER_STATISTICS).
			MF_SINK_WRITER_STATISTICS* ConverterMF_SINK_WRITER_STATISTICSManagedToUnamaged(CA_MF_SINK_WRITER_STATISTICS^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MF_SINK_WRITER_STATISTICS* EstruturaRetorno = CriarEstrutura<MF_SINK_WRITER_STATISTICS>();

				//Define os valores
				EstruturaRetorno->cb = Param_Estrutura->ES_DIMENSIONAR;
				EstruturaRetorno->dwByteCountQueued = Param_Estrutura->ES_BYTES_AGURDANDO;
				EstruturaRetorno->qwByteCountProcessed = Param_Estrutura->ES_BYTES_TOTAL_ENVIDO;
				EstruturaRetorno->qwNumSamplesEncoded = Param_Estrutura->ES_NUM_AMOSTRAS_CODIFICADAS;
				EstruturaRetorno->qwNumSamplesProcessed = Param_Estrutura->ES_NUM_AMOSTRAS_PROCESSADAS;
				EstruturaRetorno->qwNumSamplesReceived = Param_Estrutura->ES_NUM_AMOSTRAS_RECEBIDAS;
				EstruturaRetorno->dwNumOutstandingSinkSampleRequests = static_cast<DWORD>(Param_Estrutura->ES_NUM_SOLICITACOES_PENDENTES);
				EstruturaRetorno->qwNumStreamTicksReceived = Param_Estrutura->ES_NUM_TICKS_FLUXO_RECEBIDOS;
				EstruturaRetorno->dwAverageSampleRateEncoded = static_cast<DWORD>(Param_Estrutura->ES_TAXA_MEDIA_AMOSTRAS_CODIFICADS);
				EstruturaRetorno->dwAverageSampleRateReceived = static_cast<DWORD>(Param_Estrutura->ES_TAXA_MEDIA_AMOSTRAS_ENVIADAS);
				EstruturaRetorno->dwAverageSampleRateProcessed = static_cast<DWORD>(Param_Estrutura->ES_TAXA_MEDIA_AMOSTRAS_ENVIDAS_COLETOR_MIDIA);
				EstruturaRetorno->llLastTimestampEncoded = Param_Estrutura->ES_TIMESPAN_AMOSTRA_RECENTE_CODIFICADA;
				EstruturaRetorno->llLastTimestampReceived = Param_Estrutura->ES_TIMESPAN_AMOSTRA_RECENTE_ENVIADA;
				EstruturaRetorno->llLastTimestampProcessed = Param_Estrutura->ES_TIMESPAN_AMOSTRA_RECENTE_PROCESSADA;
				EstruturaRetorno->llLastSinkSampleRequest = Param_Estrutura->ES_TIMESPAN_AMOSTRA_SOLICITACAO_RECENTE;
				EstruturaRetorno->llLastStreamTickReceived = Param_Estrutura->ES_TIMESPAN_TICK_FLUXO_RECENTE;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MF_SINK_WRITER_STATISTICS) para sua correspondencia gerenciada(CA_MF_SINK_WRITER_STATISTICS).
			CA_MF_SINK_WRITER_STATISTICS^ ConverterMF_SINK_WRITER_STATISTICSUnamagedToManaged(MF_SINK_WRITER_STATISTICS* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MF_SINK_WRITER_STATISTICS^ EstruturaRetorno = gcnew CA_MF_SINK_WRITER_STATISTICS();

				//Define os valores
				EstruturaRetorno->ES_DIMENSIONAR = Param_Estrutura->cb;
				EstruturaRetorno->ES_BYTES_AGURDANDO = Param_Estrutura->dwByteCountQueued;
				EstruturaRetorno->ES_BYTES_TOTAL_ENVIDO = Param_Estrutura->qwByteCountProcessed;
				EstruturaRetorno->ES_NUM_AMOSTRAS_CODIFICADAS = Param_Estrutura->qwNumSamplesEncoded;
				EstruturaRetorno->ES_NUM_AMOSTRAS_PROCESSADAS = Param_Estrutura->qwNumSamplesProcessed;
				EstruturaRetorno->ES_NUM_AMOSTRAS_RECEBIDAS = Param_Estrutura->qwNumSamplesReceived;
				EstruturaRetorno->ES_NUM_SOLICITACOES_PENDENTES = Param_Estrutura->dwNumOutstandingSinkSampleRequests;
				EstruturaRetorno->ES_NUM_TICKS_FLUXO_RECEBIDOS = Param_Estrutura->qwNumStreamTicksReceived;
				EstruturaRetorno->ES_TAXA_MEDIA_AMOSTRAS_CODIFICADS = Param_Estrutura->dwAverageSampleRateEncoded;
				EstruturaRetorno->ES_TAXA_MEDIA_AMOSTRAS_ENVIADAS = Param_Estrutura->dwAverageSampleRateReceived;
				EstruturaRetorno->ES_TAXA_MEDIA_AMOSTRAS_ENVIDAS_COLETOR_MIDIA = Param_Estrutura->dwAverageSampleRateProcessed;
				EstruturaRetorno->ES_TIMESPAN_AMOSTRA_RECENTE_CODIFICADA = Param_Estrutura->llLastTimestampEncoded;
				EstruturaRetorno->ES_TIMESPAN_AMOSTRA_RECENTE_ENVIADA = Param_Estrutura->llLastTimestampReceived;
				EstruturaRetorno->ES_TIMESPAN_AMOSTRA_RECENTE_PROCESSADA = Param_Estrutura->llLastTimestampProcessed;
				EstruturaRetorno->ES_TIMESPAN_AMOSTRA_SOLICITACAO_RECENTE = Param_Estrutura->llLastSinkSampleRequest;
				EstruturaRetorno->ES_TIMESPAN_TICK_FLUXO_RECENTE = Param_Estrutura->llLastStreamTickReceived;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MF_TRANSCODE_SINK_INFO) para sua correspondencia não gerenciada(MF_TRANSCODE_SINK_INFO).
			MF_TRANSCODE_SINK_INFO* ConverterMF_TRANSCODE_SINK_INFOManaged_ToUnamaged(CA_MF_TRANSCODE_SINK_INFO^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MF_TRANSCODE_SINK_INFO* EstruturaRetorno = CriarEstrutura<MF_TRANSCODE_SINK_INFO>();
			
				//Define os valores
				EstruturaRetorno->dwAudioStreamID = Param_Estrutura->dwAudioStreamID;
				EstruturaRetorno->dwVideoStreamID = Param_Estrutura->dwVideoStreamID;

				//Recupera os ponteiros para da interface de atributos para audio e vídeo se validas.
				if (ObjetoGerenciadoValido(Param_Estrutura->pVideoMediaType))
				{
					//Recupera o ponteiro dos atributos para o video.
					static_cast<ICaren^>(Param_Estrutura->pVideoMediaType)->RecuperarPonteiro((LPVOID*)&EstruturaRetorno->pVideoMediaType);
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->pAudioMediaType))
				{
					//Recupera o ponteiro dos atributos para o video.
					static_cast<ICaren^>(Param_Estrutura->pAudioMediaType)->RecuperarPonteiro((LPVOID*)&EstruturaRetorno->pAudioMediaType);
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MF_TRANSCODE_SINK_INFO) para sua correspondencia gerenciada(CA_MF_TRANSCODE_SINK_INFO).
			CA_MF_TRANSCODE_SINK_INFO^ ConverterMF_TRANSCODE_SINK_INFOUnamaged_ToManaged(MF_TRANSCODE_SINK_INFO* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MF_TRANSCODE_SINK_INFO^ EstruturaRetorno = gcnew CA_MF_TRANSCODE_SINK_INFO();

				//Define os valores
				EstruturaRetorno->dwAudioStreamID = Param_Estrutura->dwAudioStreamID;
				EstruturaRetorno->dwVideoStreamID = Param_Estrutura->dwVideoStreamID;
				
				//Verifica se as intefaces de atributos são validas e define seu ponteiro nas gerenciadas.
				if (ObjetoValido(Param_Estrutura->pVideoMediaType))
				{
					//Cria a interface
					EstruturaRetorno->pVideoMediaType = gcnew Caren();

					//Define o ponteiro na interface
					static_cast<ICaren^>(EstruturaRetorno->pVideoMediaType)->AdicionarPonteiro(Param_Estrutura->pVideoMediaType);
				}
				if (ObjetoValido(Param_Estrutura->pAudioMediaType))
				{
					//Cria a interface
					EstruturaRetorno->pAudioMediaType = gcnew Caren();

					//Define o ponteiro na interface
					static_cast<ICaren^>(EstruturaRetorno->pAudioMediaType)->AdicionarPonteiro(Param_Estrutura->pAudioMediaType);
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFNetCredentialManagerGetParam) para sua correspondencia não gerenciada(MFNetCredentialManagerGetParam).
			MFNetCredentialManagerGetParam* ConverterMFNetCredentialManagerGetParamManaged_ToUnamaged(CA_MFNetCredentialManagerGetParam^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFNetCredentialManagerGetParam* EstruturaRetorno = CriarEstrutura<MFNetCredentialManagerGetParam>();

				//Define os valores
				EstruturaRetorno->hrOp = static_cast<HRESULT>(Param_Estrutura->hrOp);
				EstruturaRetorno->fAllowLoggedOnUser = static_cast<BOOL>(Param_Estrutura->fAllowLoggedOnUser);
				EstruturaRetorno->fClearTextPackage = static_cast<BOOL>(Param_Estrutura->fClearTextPackage);

				//Define possiveis valores.
				if (ObjetoGerenciadoValido(Param_Estrutura->pszUrl))
					EstruturaRetorno->pszUrl = ConverterStringToWCHAR(Param_Estrutura->pszUrl);
				if (ObjetoGerenciadoValido(Param_Estrutura->pszRealm))
					EstruturaRetorno->pszRealm = ConverterStringToWCHAR(Param_Estrutura->pszRealm);
				if (ObjetoGerenciadoValido(Param_Estrutura->pszPackage))
					EstruturaRetorno->pszPackage = ConverterStringToWCHAR(Param_Estrutura->pszPackage);
				if (ObjetoGerenciadoValido(Param_Estrutura->pszSite))
					EstruturaRetorno->pszSite = ConverterStringToWCHAR(Param_Estrutura->pszSite);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFNetCredentialManagerGetParam) para sua correspondencia gerenciada(CA_MFNetCredentialManagerGetParam).
			CA_MFNetCredentialManagerGetParam^ ConverterMFNetCredentialManagerGetParamUnamaged_ToManaged(MFNetCredentialManagerGetParam* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFNetCredentialManagerGetParam^ EstruturaRetorno = gcnew CA_MFNetCredentialManagerGetParam();

				//Define os valores
				EstruturaRetorno->hrOp = static_cast<long>(Param_Estrutura->hrOp);
				EstruturaRetorno->fAllowLoggedOnUser = static_cast<bool>(Param_Estrutura->fAllowLoggedOnUser);
				EstruturaRetorno->fClearTextPackage = static_cast<bool>(Param_Estrutura->fClearTextPackage);

				//Define possiveis valores.
				if (ObjetoValido(Param_Estrutura->pszUrl))
					EstruturaRetorno->pszUrl = gcnew String(Param_Estrutura->pszUrl);
				if (ObjetoValido(Param_Estrutura->pszRealm))
					EstruturaRetorno->pszRealm = gcnew String(Param_Estrutura->pszRealm);
				if (ObjetoValido(Param_Estrutura->pszPackage))
					EstruturaRetorno->pszPackage = gcnew String(Param_Estrutura->pszPackage);
				if (ObjetoValido(Param_Estrutura->pszSite))
					EstruturaRetorno->pszSite = gcnew String(Param_Estrutura->pszSite);


				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFT_REGISTER_TYPE_INFO) para sua correspondencia não gerenciada(MFT_REGISTER_TYPE_INFO).
			MFT_REGISTER_TYPE_INFO* ConverterMFT_REGISTER_TYPE_INFOManaged_ToUnamaged(CA_MFT_REGISTER_TYPE_INFO^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFT_REGISTER_TYPE_INFO* EstruturaRetorno = CriarEstrutura<MFT_REGISTER_TYPE_INFO>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os valores
				EstruturaRetorno->guidMajorType = CreateGuidFromString(Param_Estrutura->guidMajorType);
				EstruturaRetorno->guidSubtype = CreateGuidFromString(Param_Estrutura->guidSubtype);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFT_REGISTER_TYPE_INFO) para sua correspondencia gerenciada(CA_MFT_REGISTER_TYPE_INFO).
			CA_MFT_REGISTER_TYPE_INFO^ ConverterMFT_REGISTER_TYPE_INFOUnamaged_ToManaged(MFT_REGISTER_TYPE_INFO* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFT_REGISTER_TYPE_INFO^ EstruturaRetorno = gcnew CA_MFT_REGISTER_TYPE_INFO();

				//Define os valores
				EstruturaRetorno->guidMajorType = ConverterGuidToString(Param_Estrutura->guidMajorType);
				EstruturaRetorno->guidSubtype = ConverterGuidToString(Param_Estrutura->guidSubtype);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFT_REGISTRATION_INFO) para sua correspondencia não gerenciada(MFT_REGISTRATION_INFO).
			MFT_REGISTRATION_INFO* ConverterMFT_REGISTRATION_INFOManaged_ToUnamaged(CA_MFT_REGISTRATION_INFO^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFT_REGISTRATION_INFO* EstruturaRetorno = CriarEstrutura<MFT_REGISTRATION_INFO>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Variaveis.
				MFT_REGISTER_TYPE_INFO* vi_MatrizInTypes = Nulo;
				MFT_REGISTER_TYPE_INFO* vi_MatrizOutTypes = Nulo;

				//Define os valores
				EstruturaRetorno->clsid = CreateGuidFromString(Param_Estrutura->clsid);
				EstruturaRetorno->guidCategory = CreateGuidFromString(Param_Estrutura->guidCategory);
				EstruturaRetorno->uiFlags = static_cast<UINT32>(Param_Estrutura->uiFlags);
				EstruturaRetorno->pszName = ConverterStringToWCHAR(Param_Estrutura->pszName);
				EstruturaRetorno->cInTypes = static_cast<DWORD>(Param_Estrutura->cInTypes);
				EstruturaRetorno->cOutTypes = static_cast<DWORD>(Param_Estrutura->cOutTypes);

				//Verifica se foi forneceida as matrizes. Se sim, vai criar e definir os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->pInTypes))
				{
					//Cria a matriz que vai conter as informações do tipo de entrada.
					vi_MatrizInTypes = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_Estrutura->cInTypes);

					//Abre um for para preeencher as matriz com os dados
					for (UINT32 i = 0; i < Param_Estrutura->cInTypes; i++)
					{
						//Inicializa a estrutura no index.
						vi_MatrizInTypes[i] = {};

						//Converte as string no index para um GUID na matriz nativa.
						vi_MatrizInTypes[i].guidMajorType = CreateGuidFromString(Param_Estrutura->pInTypes[i]->guidMajorType);
						vi_MatrizInTypes[i].guidSubtype = CreateGuidFromString(Param_Estrutura->pInTypes[i]->guidSubtype);
					}
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->pOutTypes))
				{
					//Cria a matriz que vai conter as informações do tipo de entrada.
					vi_MatrizOutTypes = CriarMatrizEstruturas<MFT_REGISTER_TYPE_INFO>(Param_Estrutura->cOutTypes);

					//Abre um for para preeencher as matriz com os dados
					for (UINT32 i = 0; i < Param_Estrutura->cOutTypes; i++)
					{
						//Inicializa a estrutura no index.
						vi_MatrizOutTypes[i] = {};

						//Converte as string no index para um GUID na matriz nativa.
						vi_MatrizOutTypes[i].guidMajorType = CreateGuidFromString(Param_Estrutura->pOutTypes[i]->guidMajorType);
						vi_MatrizOutTypes[i].guidSubtype = CreateGuidFromString(Param_Estrutura->pOutTypes[i]->guidSubtype);
					}
				}
				
				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFT_REGISTRATION_INFO) para sua correspondencia gerenciada(CA_MFT_REGISTRATION_INFO).
			CA_MFT_REGISTRATION_INFO^ ConverterMFT_REGISTRATION_INFOUnamaged_ToManaged(MFT_REGISTRATION_INFO* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFT_REGISTRATION_INFO^ EstruturaRetorno = gcnew CA_MFT_REGISTRATION_INFO();

				//Define os valores
				EstruturaRetorno->clsid = ConverterGuidToString(Param_Estrutura->clsid);
				EstruturaRetorno->guidCategory = ConverterGuidToString(Param_Estrutura->guidCategory);
				EstruturaRetorno->uiFlags = static_cast<CA_MFT_ENUM_FLAG>(Param_Estrutura->uiFlags);
				EstruturaRetorno->pszName = gcnew String(Param_Estrutura->pszName);
				EstruturaRetorno->cInTypes = static_cast<UInt32>(Param_Estrutura->cInTypes);
				EstruturaRetorno->cOutTypes = static_cast<UInt32>(Param_Estrutura->cOutTypes);

				//Verifica se foi forneceida as matrizes. Se sim, vai criar e definir os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->pInTypes))
				{
					//Cria a matriz que vai conter as informações do tipo de entrada.
					EstruturaRetorno->pInTypes = gcnew cli::array<CA_MFT_REGISTER_TYPE_INFO^>(EstruturaRetorno->cInTypes);

					//Abre um for para preeencher as matriz com os dados
					for (UINT32 i = 0; i < EstruturaRetorno->cInTypes; i++)
					{
						//Inicializa a estrutura no index.
						EstruturaRetorno->pInTypes[i] = gcnew CA_MFT_REGISTER_TYPE_INFO();

						//Converte as string no index para um GUID na matriz nativa.
						EstruturaRetorno->pInTypes[i]->guidMajorType = ConverterGuidToString(Param_Estrutura->pInTypes[i].guidMajorType);
						EstruturaRetorno->pInTypes[i]->guidSubtype = ConverterGuidToString(Param_Estrutura->pInTypes[i].guidSubtype);
					}
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->pOutTypes))
				{
					//Cria a matriz que vai conter as informações do tipo de entrada.
					EstruturaRetorno->pOutTypes = gcnew cli::array<CA_MFT_REGISTER_TYPE_INFO^>(EstruturaRetorno->cOutTypes);

					//Abre um for para preeencher as matriz com os dados
					for (UINT32 i = 0; i < EstruturaRetorno->cOutTypes; i++)
					{
						//Inicializa a estrutura no index.
						EstruturaRetorno->pOutTypes[i] = gcnew CA_MFT_REGISTER_TYPE_INFO();

						//Converte as string no index para um GUID na matriz nativa.
						EstruturaRetorno->pOutTypes[i]->guidMajorType = ConverterGuidToString(Param_Estrutura->pOutTypes[i].guidMajorType);
						EstruturaRetorno->pOutTypes[i]->guidSubtype = ConverterGuidToString(Param_Estrutura->pOutTypes[i].guidSubtype);
					}
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFARGB) para sua correspondencia não gerenciada(MFARGB).
			MFARGB* ConverterMFARGBManaged_ToUnamaged(CA_MFARGB^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFARGB* EstruturaRetorno = CriarEstrutura<MFARGB>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MFARGB));

				//Define os valores
				EstruturaRetorno->rgbAlpha = Param_Estrutura->rgbAlpha;
				EstruturaRetorno->rgbBlue = Param_Estrutura->rgbBlue;
				EstruturaRetorno->rgbGreen = Param_Estrutura->rgbGreen;
				EstruturaRetorno->rgbRed = Param_Estrutura->rgbRed;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFARGB) para sua correspondencia gerenciada(CA_MFARGB).
			CA_MFARGB^ ConverterMFARGBUnamaged_ToManaged(MFARGB* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFARGB^ EstruturaRetorno = gcnew CA_MFARGB();

				//Define os valores
				EstruturaRetorno->rgbAlpha = Param_Estrutura->rgbAlpha;
				EstruturaRetorno->rgbBlue = Param_Estrutura->rgbBlue;
				EstruturaRetorno->rgbGreen = Param_Estrutura->rgbGreen;
				EstruturaRetorno->rgbRed = Param_Estrutura->rgbRed;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFVideoNormalizedRect) para sua correspondencia não gerenciada(MFVideoNormalizedRect).
			MFVideoNormalizedRect* ConverterMFVideoNormalizedRectManaged_ToUnamaged(CA_MFVideoNormalizedRect^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFVideoNormalizedRect* EstruturaRetorno = CriarEstrutura<MFVideoNormalizedRect>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MFVideoNormalizedRect));

				//Define os valores
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;
				EstruturaRetorno->bottom = Param_Estrutura->bottom;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFVideoNormalizedRect) para sua correspondencia gerenciada(CA_MFVideoNormalizedRect).
			CA_MFVideoNormalizedRect^ ConverterMFVideoNormalizedRectUnamaged_ToManaged(MFVideoNormalizedRect* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFVideoNormalizedRect^ EstruturaRetorno = gcnew CA_MFVideoNormalizedRect();

				//Define os valores
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;
				EstruturaRetorno->bottom = Param_Estrutura->bottom;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MF_LEAKY_BUCKET_PAIR) para sua correspondencia não gerenciada(MF_LEAKY_BUCKET_PAIR).
			MF_LEAKY_BUCKET_PAIR* ConverterMF_LEAKY_BUCKET_PAIRManaged_ToUnamaged(CA_MF_LEAKY_BUCKET_PAIR^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MF_LEAKY_BUCKET_PAIR* EstruturaRetorno = CriarEstrutura<MF_LEAKY_BUCKET_PAIR>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MF_LEAKY_BUCKET_PAIR));

				//Define os valores
				EstruturaRetorno->dwBitrate = static_cast<DWORD>(Param_Estrutura->dwBitrate);
				EstruturaRetorno->msBufferWindow = static_cast<DWORD>(Param_Estrutura->msBufferWindow);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MF_LEAKY_BUCKET_PAIR) para sua correspondencia gerenciada(CA_MF_LEAKY_BUCKET_PAIR).
			CA_MF_LEAKY_BUCKET_PAIR^ ConverterMF_LEAKY_BUCKET_PAIRUnamaged_ToManaged(MF_LEAKY_BUCKET_PAIR* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MF_LEAKY_BUCKET_PAIR^ EstruturaRetorno = gcnew CA_MF_LEAKY_BUCKET_PAIR();

				//Define os valores
				EstruturaRetorno->dwBitrate = static_cast<UInt32>(Param_Estrutura->dwBitrate);
				EstruturaRetorno->msBufferWindow = static_cast<UInt32>(Param_Estrutura->msBufferWindow);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFBYTESTREAM_BUFFERING_PARAMS) para sua correspondencia não gerenciada(MFBYTESTREAM_BUFFERING_PARAMS).
			MFBYTESTREAM_BUFFERING_PARAMS* ConverterMFBYTESTREAM_BUFFERING_PARAMSManaged_ToUnamaged(CA_MFBYTESTREAM_BUFFERING_PARAMS^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFBYTESTREAM_BUFFERING_PARAMS* EstruturaRetorno = CriarEstrutura<MFBYTESTREAM_BUFFERING_PARAMS>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MFBYTESTREAM_BUFFERING_PARAMS));

				//Variaveis a serem utilizadas.
				MF_LEAKY_BUCKET_PAIR* vi_pAuxiliar = Nulo;

				//Define os valores
				EstruturaRetorno->cbTotalFileSize = Param_Estrutura->cbTotalFileSize;
				EstruturaRetorno->cbPlayableDataSize = Param_Estrutura->cbPlayableDataSize;
				EstruturaRetorno->cBuckets = static_cast<DWORD>(Param_Estrutura->cBuckets);
				EstruturaRetorno->qwNetBufferingTime = Param_Estrutura->qwNetBufferingTime;
				EstruturaRetorno->qwExtraBufferingTimeDuringSeek = Param_Estrutura->qwExtraBufferingTimeDuringSeek;
				EstruturaRetorno->qwPlayDuration = Param_Estrutura->qwPlayDuration;
				EstruturaRetorno->dRate = Param_Estrutura->dRate;

				//Verifica se contém dados o array e cria com a quantidade especificada.
				if(Param_Estrutura->cBuckets >= 1)
					EstruturaRetorno->prgBuckets = CriarMatrizUnidimensional<MF_LEAKY_BUCKET_PAIR>(EstruturaRetorno->cBuckets);

				//Copia os dados para a matriz nativa se valida.
				if (ObjetoValido(EstruturaRetorno->prgBuckets))
				{
					//Faz um for para copiar os dados para a matriz nativa.
					for (DWORD i = 0; i < EstruturaRetorno->cBuckets; i++)
					{
						//Converte a estrutura gerenciada.
						vi_pAuxiliar = ConverterMF_LEAKY_BUCKET_PAIRManaged_ToUnamaged(Param_Estrutura->prgBuckets[i]);

						//Define na estrutura nativa.
						EstruturaRetorno->prgBuckets[i] = *vi_pAuxiliar;

						//Libera a memória utilizada pela estrutura.
						DeletarEstruturaSafe(&vi_pAuxiliar);
					}
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFBYTESTREAM_BUFFERING_PARAMS) para sua correspondencia gerenciada(CA_MFBYTESTREAM_BUFFERING_PARAMS).
			CA_MFBYTESTREAM_BUFFERING_PARAMS^ ConverterMFBYTESTREAM_BUFFERING_PARAMSUnamaged_ToManaged(MFBYTESTREAM_BUFFERING_PARAMS* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFBYTESTREAM_BUFFERING_PARAMS^ EstruturaRetorno = gcnew CA_MFBYTESTREAM_BUFFERING_PARAMS();

				//Define os valores
				EstruturaRetorno->cbTotalFileSize = static_cast<UInt64>(Param_Estrutura->cbTotalFileSize);
				EstruturaRetorno->cbPlayableDataSize = static_cast<UInt64>(Param_Estrutura->cbPlayableDataSize);
				EstruturaRetorno->cBuckets = static_cast<UInt32>(Param_Estrutura->cBuckets);
				EstruturaRetorno->qwNetBufferingTime = static_cast<UInt64>(Param_Estrutura->qwNetBufferingTime);
				EstruturaRetorno->qwExtraBufferingTimeDuringSeek = static_cast<UInt64>(Param_Estrutura->qwExtraBufferingTimeDuringSeek);
				EstruturaRetorno->qwPlayDuration = static_cast<UInt64>(Param_Estrutura->qwPlayDuration);
				EstruturaRetorno->dRate = Param_Estrutura->dRate;
				
				//Verifica se contém dados o array e cria com a quantidade especificada.
				if (Param_Estrutura->cBuckets >= 1)
					EstruturaRetorno->prgBuckets = gcnew cli::array<CA_MF_LEAKY_BUCKET_PAIR^>(EstruturaRetorno->cBuckets);

				//Copia os dados para a matriz gerenciada se valida.
				if (ObjetoGerenciadoValido(EstruturaRetorno->prgBuckets))
				{
					//Faz um for para copiar os dados para a matriz gerenciada.
					for (UInt32 i = 0; i < EstruturaRetorno->cBuckets; i++)
					{
						//Define na estrutura gerenciada.
						EstruturaRetorno->prgBuckets[i] = ConverterMF_LEAKY_BUCKET_PAIRUnamaged_ToManaged(&Param_Estrutura->prgBuckets[i]);
					}
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MF_BYTE_STREAM_CACHE_RANGE) para sua correspondencia não gerenciada(MF_BYTE_STREAM_CACHE_RANGE).
			MF_BYTE_STREAM_CACHE_RANGE* ConverterMF_BYTE_STREAM_CACHE_RANGEManaged_ToUnamaged(CA_MF_BYTE_STREAM_CACHE_RANGE^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MF_BYTE_STREAM_CACHE_RANGE* EstruturaRetorno = CriarEstrutura<MF_BYTE_STREAM_CACHE_RANGE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MF_BYTE_STREAM_CACHE_RANGE));

				//Define os valores
				EstruturaRetorno->qwStartOffset = Param_Estrutura->qwStartOffset;
				EstruturaRetorno->qwEndOffset = Param_Estrutura->qwEndOffset;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MF_BYTE_STREAM_CACHE_RANGE) para sua correspondencia gerenciada(CA_MF_BYTE_STREAM_CACHE_RANGE).
			CA_MF_BYTE_STREAM_CACHE_RANGE^ ConverterMF_BYTE_STREAM_CACHE_RANGEUnamaged_ToManaged(MF_BYTE_STREAM_CACHE_RANGE* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MF_BYTE_STREAM_CACHE_RANGE^ EstruturaRetorno = gcnew CA_MF_BYTE_STREAM_CACHE_RANGE();

				//Define os valores
				EstruturaRetorno->qwStartOffset = static_cast<Int64>(Param_Estrutura->qwStartOffset);
				EstruturaRetorno->qwEndOffset = static_cast<Int64>(Param_Estrutura->qwEndOffset);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFCLOCK_PROPERTIES) para sua correspondencia não gerenciada(_MFCLOCK_PROPERTIES).
			_MFCLOCK_PROPERTIES* ConverterMFCLOCK_PROPERTIESManaged_ToUnamaged(CA_MFCLOCK_PROPERTIES^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				_MFCLOCK_PROPERTIES* EstruturaRetorno = CriarEstrutura<_MFCLOCK_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(_MFCLOCK_PROPERTIES));

				//Define os valores
				EstruturaRetorno->qwCorrelationRate = static_cast<ULONG64>(Param_Estrutura->qwCorrelationRate);
				EstruturaRetorno->guidClockId = CreateGuidFromString(Param_Estrutura->guidClockId);
				EstruturaRetorno->dwClockFlags = static_cast<DWORD>(Param_Estrutura->dwClockFlags);
				EstruturaRetorno->qwClockFrequency = static_cast<ULONG64>(Param_Estrutura->qwClockFrequency);
				EstruturaRetorno->dwClockTolerance = static_cast<DWORD>(Param_Estrutura->dwClockTolerance);
				EstruturaRetorno->dwClockJitter = static_cast<DWORD>(Param_Estrutura->dwClockJitter);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(_MFCLOCK_PROPERTIES) para sua correspondencia gerenciada(CA_MFCLOCK_PROPERTIES).
			CA_MFCLOCK_PROPERTIES^ ConverterMFCLOCK_PROPERTIESUnamaged_ToManaged(_MFCLOCK_PROPERTIES* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFCLOCK_PROPERTIES^ EstruturaRetorno = gcnew CA_MFCLOCK_PROPERTIES();

				//Define os valores
				EstruturaRetorno->qwCorrelationRate = static_cast<UInt64>(Param_Estrutura->qwCorrelationRate);
				EstruturaRetorno->guidClockId = ConverterGuidToString(Param_Estrutura->guidClockId);
				EstruturaRetorno->dwClockFlags = static_cast<CA_MFCLOCK_RELATIONAL_FLAG>(Param_Estrutura->dwClockFlags);
				EstruturaRetorno->qwClockFrequency = static_cast<UInt64>(Param_Estrutura->qwClockFrequency);
				EstruturaRetorno->dwClockTolerance = static_cast<UInt32>(Param_Estrutura->dwClockTolerance);
				EstruturaRetorno->dwClockJitter = static_cast<UInt32>(Param_Estrutura->dwClockJitter);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE).
			MFTOPONODE_ATTRIBUTE_UPDATE* ConverterMFTOPONODE_ATTRIBUTE_UPDATEManaged_ToUnamaged(CA_MFTOPONODE_ATTRIBUTE_UPDATE^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				MFTOPONODE_ATTRIBUTE_UPDATE* EstruturaRetorno = CriarEstrutura<MFTOPONODE_ATTRIBUTE_UPDATE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(MFTOPONODE_ATTRIBUTE_UPDATE));

				//Define os valores
				EstruturaRetorno->NodeId = Param_Estrutura->NodeId;
				EstruturaRetorno->guidAttributeKey = StringObjetoValido(Param_Estrutura->guidAttributeKey) ? CreateGuidFromString(Param_Estrutura->guidAttributeKey) : GUID_NULL;
				EstruturaRetorno->attrType = static_cast<MF_ATTRIBUTE_TYPE>(Param_Estrutura->attrType);
				EstruturaRetorno->u32 = Param_Estrutura->u32;
				EstruturaRetorno->u64 = Param_Estrutura->u64;
				EstruturaRetorno->d = Param_Estrutura->d;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE).
			CA_MFTOPONODE_ATTRIBUTE_UPDATE^ ConverterMFTOPONODE_ATTRIBUTE_UPDATEUnamaged_ToManaged(MFTOPONODE_ATTRIBUTE_UPDATE* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_MFTOPONODE_ATTRIBUTE_UPDATE^ EstruturaRetorno = gcnew CA_MFTOPONODE_ATTRIBUTE_UPDATE();

				//Define os valores
				EstruturaRetorno->NodeId = Param_Estrutura->NodeId;
				EstruturaRetorno->guidAttributeKey = Param_Estrutura->guidAttributeKey == GUID_NULL ? nullptr: ConverterGuidToString(Param_Estrutura->guidAttributeKey);
				EstruturaRetorno->attrType = static_cast<CA_MF_ATTRIBUTE_TYPE>(Param_Estrutura->attrType);
				EstruturaRetorno->u32 = Param_Estrutura->u32;
				EstruturaRetorno->u64 = Param_Estrutura->u64;
				EstruturaRetorno->d = Param_Estrutura->d;			

				//Retorna a estrutura.
				return EstruturaRetorno;
			}








			//D2D ESTRUTURAS


			//Converte uma estrutura gerenciada(CA_D2D1_COLOR_F) para sua correspondencia não gerenciada(D2D1_COLOR_F).
			D2D1_COLOR_F* ConverterD2D1_COLOR_FManagedToUnmanaged(CA_D2D1_COLOR_F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_COLOR_F* EstruturaRetorno = CriarEstrutura<D2D1_COLOR_F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->a = Param_Estrutura->a;
				EstruturaRetorno->r = Param_Estrutura->r;
				EstruturaRetorno->g = Param_Estrutura->g;
				EstruturaRetorno->b = Param_Estrutura->b;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_COLOR_F) para sua correspondencia gerenciada(CA_D2D1_COLOR_F).
			CA_D2D1_COLOR_F^ ConverterD2D1_COLOR_FUnmanagedToManaged(D2D1_COLOR_F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_COLOR_F^ EstruturaRetorno = gcnew CA_D2D1_COLOR_F();

				//Define os dados.
				EstruturaRetorno->a = Param_Estrutura->a;
				EstruturaRetorno->r = Param_Estrutura->r;
				EstruturaRetorno->g = Param_Estrutura->g;
				EstruturaRetorno->b = Param_Estrutura->b;
				
				//Retorna o resultado
				return EstruturaRetorno;
			}

			
			//Converte uma estrutura gerenciada(CA_D2D1_RECT_U) para sua correspondencia não gerenciada(D2D1_RECT_U).
			D2D1_RECT_U* ConverterD2D1_RECT_UManagedToUnmanaged(CA_D2D1_RECT_U^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RECT_U* EstruturaRetorno = CriarEstrutura<D2D1_RECT_U>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RECT_U) para sua correspondencia gerenciada(CA_D2D1_RECT_U).
			CA_D2D1_RECT_U^ ConverterD2D1_RECT_UUnmanagedToManaged(D2D1_RECT_U* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RECT_U^ EstruturaRetorno = gcnew CA_D2D1_RECT_U();

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RECT_F) para sua correspondencia não gerenciada(D2D1_RECT_F).
			D2D1_RECT_F* ConverterD2D1_RECT_FManagedToUnmanaged(CA_D2D1_RECT_F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RECT_F* EstruturaRetorno = CriarEstrutura<D2D1_RECT_F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RECT_F) para sua correspondencia gerenciada(CA_D2D1_RECT_F).
			CA_D2D1_RECT_F^ ConverterD2D1_RECT_FUnmanagedToManaged(D2D1_RECT_F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RECT_F^ EstruturaRetorno = gcnew CA_D2D1_RECT_F();

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RECT_L) para sua correspondencia não gerenciada(D2D1_RECT_L).
			D2D1_RECT_L* ConverterD2D1_RECT_LManagedToUnmanaged(CA_D2D1_RECT_L^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RECT_L* EstruturaRetorno = CriarEstrutura<D2D1_RECT_L>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_RECT_L));

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RECT_L) para sua correspondencia gerenciada(CA_D2D1_RECT_L).
			CA_D2D1_RECT_L^ ConverterD2D1_RECT_LUnmanagedToManaged(D2D1_RECT_L* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RECT_L^ EstruturaRetorno = gcnew CA_D2D1_RECT_L();

				//Define os dados.
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->left = Param_Estrutura->left;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->top = Param_Estrutura->top;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES) para sua correspondencia não gerenciada(D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES).
			D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* ConverterD2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIESManagedToUnmanaged(CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->interpolationMode = static_cast<D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);
				EstruturaRetorno->options = static_cast<D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS>(Param_Estrutura->options);
				EstruturaRetorno->orientation = static_cast<D2D1_ORIENTATION>(Param_Estrutura->orientation);
				EstruturaRetorno->scaleX = Param_Estrutura->scaleX;
				EstruturaRetorno->scaleY = Param_Estrutura->scaleY;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES).
			CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^ ConverterD2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIESUnmanagedToManaged(D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->interpolationMode = static_cast<CA_D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);
				EstruturaRetorno->options = static_cast<CA_D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS>(Param_Estrutura->options);
				EstruturaRetorno->orientation = static_cast<CA_D2D1_ORIENTATION>(Param_Estrutura->orientation);
				EstruturaRetorno->scaleX = Param_Estrutura->scaleX;
				EstruturaRetorno->scaleY = Param_Estrutura->scaleY;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(D2D1_POINT_2F) para sua correspondencia não gerenciada(CA_D2D1_POINT_2F).
			D2D1_POINT_2F* ConverterD2D1_POINT_2FManagedToUnmanaged(CA_D2D1_POINT_2F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_POINT_2F* EstruturaRetorno = CriarEstrutura<D2D1_POINT_2F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;


				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_POINT_2F) para sua correspondencia gerenciada(CA_D2D1_POINT_2F).
			CA_D2D1_POINT_2F^ ConverterD2D1_POINT_2FUnmanagedToManaged(D2D1_POINT_2F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_POINT_2F^ EstruturaRetorno = gcnew CA_D2D1_POINT_2F();

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_POINT_2U) para sua correspondencia não gerenciada(D2D1_POINT_2U).
			D2D1_POINT_2U* ConverterD2D1_POINT_2UManagedToUnmanaged(CA_D2D1_POINT_2U^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_POINT_2U* EstruturaRetorno = CriarEstrutura<D2D1_POINT_2U>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_POINT_2U) para sua correspondencia gerenciada(CA_D2D1_POINT_2U).
			CA_D2D1_POINT_2U^ ConverterD2D1_POINT_2UUnmanagedToManaged(D2D1_POINT_2U* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_POINT_2U^ EstruturaRetorno = gcnew CA_D2D1_POINT_2U();

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_POINT_2L) para sua correspondencia não gerenciada(D2D1_POINT_2L).
			D2D1_POINT_2L* ConverterD2D1_POINT_2LManagedToUnmanaged(CA_D2D1_POINT_2L^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_POINT_2L* EstruturaRetorno = CriarEstrutura<D2D1_POINT_2L>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_POINT_2L));

				//Define os dados.
				EstruturaRetorno->x = static_cast<LONG>(Param_Estrutura->x);
				EstruturaRetorno->y = static_cast<LONG>(Param_Estrutura->y);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_POINT_2L) para sua correspondencia gerenciada(CA_D2D1_POINT_2L).
			CA_D2D1_POINT_2L^ ConverterD2D1_POINT_2LUnmanagedToManaged(D2D1_POINT_2L* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_POINT_2L^ EstruturaRetorno = gcnew CA_D2D1_POINT_2L();

				//Define os dados.
				EstruturaRetorno->x = static_cast<int>(Param_Estrutura->x);
				EstruturaRetorno->y = static_cast<int>(Param_Estrutura->y);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_POINT_DESCRIPTION) para sua correspondencia não gerenciada(D2D1_POINT_DESCRIPTION).
			D2D1_POINT_DESCRIPTION* ConverterD2D1_POINT_DESCRIPTIONManagedToUnmanaged(CA_D2D1_POINT_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_POINT_DESCRIPTION* EstruturaRetorno = CriarEstrutura<D2D1_POINT_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_POINT_DESCRIPTION));

				//Variaveis
				D2D1_POINT_2F* pPoint = NULL;
				D2D1_POINT_2F* pUnitTangentVector = NULL;

				//Converte as estruturas
				pPoint = ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->point);
				pUnitTangentVector = ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->unitTangentVector);

				//Define os dados.
				EstruturaRetorno->point = *pPoint;
				EstruturaRetorno->unitTangentVector = *pUnitTangentVector;
				EstruturaRetorno->endSegment = Param_Estrutura->endSegment;
				EstruturaRetorno->endFigure = Param_Estrutura->endFigure;
				EstruturaRetorno->lengthToEndSegment = Param_Estrutura->lengthToEndSegment;
				
				//Libera a memória para as estruturas
				DeletarEstruturaSafe(&pPoint);
				DeletarEstruturaSafe(&pUnitTangentVector);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_POINT_DESCRIPTION) para sua correspondencia gerenciada(CA_D2D1_POINT_DESCRIPTION).
			CA_D2D1_POINT_DESCRIPTION^ ConverterD2D1_POINT_DESCRIPTIONUnmanagedToManaged(D2D1_POINT_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_POINT_DESCRIPTION^ EstruturaRetorno = gcnew CA_D2D1_POINT_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->point = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point);
				EstruturaRetorno->unitTangentVector = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->unitTangentVector);
				EstruturaRetorno->endSegment = Param_Estrutura->endSegment;
				EstruturaRetorno->endFigure = Param_Estrutura->endFigure;
				EstruturaRetorno->lengthToEndSegment = Param_Estrutura->lengthToEndSegment;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura gerenciada(CA_D2D1_SIZE_U) para sua correspondencia não gerenciada(D2D1_SIZE_U).
			D2D1_SIZE_U* ConverterD2D1_SIZE_UManagedToUnmanaged(CA_D2D1_SIZE_U^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_SIZE_U* EstruturaRetorno = CriarEstrutura<D2D1_SIZE_U>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->height = Param_Estrutura->height;
				EstruturaRetorno->width = Param_Estrutura->width;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_SIZE_U) para sua correspondencia gerenciada(CA_D2D1_SIZE_U).
			CA_D2D1_SIZE_U^ ConverterD2D1_SIZE_UUnmanagedToManaged(D2D1_SIZE_U* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_SIZE_U^ EstruturaRetorno = gcnew CA_D2D1_SIZE_U();

				//Define os dados.
				EstruturaRetorno->height = Param_Estrutura->height;
				EstruturaRetorno->width = Param_Estrutura->width;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_SIZE_F) para sua correspondencia não gerenciada(D2D1_SIZE_F).
			D2D1_SIZE_F* ConverterD2D1_SIZE_FManagedToUnmanaged(CA_D2D1_SIZE_F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_SIZE_F* EstruturaRetorno = CriarEstrutura<D2D1_SIZE_F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->height = Param_Estrutura->height;
				EstruturaRetorno->width = Param_Estrutura->width;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_SIZE_F) para sua correspondencia gerenciada(CA_D2D1_SIZE_F).
			CA_D2D1_SIZE_F^ ConverterD2D1_SIZE_FUnmanagedToManaged(D2D1_SIZE_F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_SIZE_F^ EstruturaRetorno = gcnew CA_D2D1_SIZE_F();

				//Define os dados.
				EstruturaRetorno->height = Param_Estrutura->height;
				EstruturaRetorno->width = Param_Estrutura->width;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_SIMPLE_COLOR_PROFILE) para sua correspondencia não gerenciada(D2D1_SIMPLE_COLOR_PROFILE).
			D2D1_SIMPLE_COLOR_PROFILE* ConverterD2D1_SIMPLE_COLOR_PROFILEManagedToUnmanaged(CA_D2D1_SIMPLE_COLOR_PROFILE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_SIMPLE_COLOR_PROFILE* EstruturaRetorno = CriarEstrutura<D2D1_SIMPLE_COLOR_PROFILE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Converte as estruturas
				D2D1_POINT_2F* pRed = Param_Estrutura->redPrimary ? ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->redPrimary) : NULL;
				D2D1_POINT_2F* pGreen = Param_Estrutura->greenPrimary ? ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->greenPrimary) : NULL;
				D2D1_POINT_2F* pBlue = Param_Estrutura->bluePrimary ? ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->bluePrimary) : NULL;
				D2D1_POINT_2F* pWhitePoint = Param_Estrutura->whitePointXZ ? ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Estrutura->whitePointXZ) : NULL;

				//Define os dados
				EstruturaRetorno->gamma = ConverterPara<D2D1_GAMMA1>(Param_Estrutura->gamma);
				EstruturaRetorno->redPrimary = pRed ? *pRed : D2D1_POINT_2F();
				EstruturaRetorno->greenPrimary = pGreen ? *pGreen : D2D1_POINT_2F();
				EstruturaRetorno->bluePrimary = pBlue ? *pBlue : D2D1_POINT_2F();
				EstruturaRetorno->whitePointXZ = pWhitePoint ? *pWhitePoint : D2D1_POINT_2F();

				//Libera os ponteiros.
				DeletarEstruturaSafe(&pRed);
				DeletarEstruturaSafe(&pGreen);
				DeletarEstruturaSafe(&pBlue);
				DeletarEstruturaSafe(&pWhitePoint);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_SIMPLE_COLOR_PROFILE) para sua correspondencia gerenciada(CA_D2D1_SIMPLE_COLOR_PROFILE).
			CA_D2D1_SIMPLE_COLOR_PROFILE^ ConverterD2D1_SIMPLE_COLOR_PROFILEUnmanagedToManaged(D2D1_SIMPLE_COLOR_PROFILE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_SIMPLE_COLOR_PROFILE^ EstruturaRetorno = gcnew CA_D2D1_SIMPLE_COLOR_PROFILE();

				//Define os dados.
				EstruturaRetorno->gamma = ConverterPara<CA_D2D1_GAMMA1>(Param_Estrutura->gamma);
				EstruturaRetorno->redPrimary = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->redPrimary);
				EstruturaRetorno->greenPrimary = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->greenPrimary);
				EstruturaRetorno->bluePrimary = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->bluePrimary);
				EstruturaRetorno->whitePointXZ = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->whitePointXZ);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_PIXEL_FORMAT) para sua correspondencia não gerenciada(D2D1_PIXEL_FORMAT).
			D2D1_PIXEL_FORMAT* ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(CA_D2D1_PIXEL_FORMAT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_PIXEL_FORMAT* EstruturaRetorno = CriarEstrutura<D2D1_PIXEL_FORMAT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->format = ConverterPara<DXGI_FORMAT>(Param_Estrutura->format);
				EstruturaRetorno->alphaMode = ConverterPara<D2D1_ALPHA_MODE>(Param_Estrutura->alphaMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_PIXEL_FORMAT) para sua correspondencia gerenciada(CA_D2D1_PIXEL_FORMAT).
			CA_D2D1_PIXEL_FORMAT^ ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(D2D1_PIXEL_FORMAT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_PIXEL_FORMAT^ EstruturaRetorno = gcnew CA_D2D1_PIXEL_FORMAT();

				//Define os dados.
				EstruturaRetorno->format = ConverterPara<CA_DXGI_FORMAT>(Param_Estrutura->format);
				EstruturaRetorno->alphaMode = ConverterPara<CA_D2D1_ALPHA_MODE>(Param_Estrutura->alphaMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_MAPPED_RECT) para sua correspondencia não gerenciada(D2D1_MAPPED_RECT).
			D2D1_MAPPED_RECT* ConverterD2D1_MAPPED_RECTManagedToUnmanaged(CA_D2D1_MAPPED_RECT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_MAPPED_RECT* EstruturaRetorno = CriarEstrutura<D2D1_MAPPED_RECT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Variaveis utilizadas.
				CarenResult Resultado;
				IntPtr IntptrBuffer;

				//Define os dados.
				EstruturaRetorno->pitch = Param_Estrutura->pitch;
				if (ObjetoGerenciadoValido(Param_Estrutura->bits))
				{
					//Tenta obter o buffer.
					Resultado = static_cast<ICarenBuffer^>(Param_Estrutura->bits)->GetInternalPointer(IntptrBuffer);
					
					//Verifica se obteve sucesso
					if (!CarenSucesso(Resultado))
					{
						//Chama uma exceção.
						throw gcnew Exception(String::Format("Não foi possivel recuperar o ponteiro interno do buffer nativo na (ICarenBuffer). Código de erro > {0}", Resultado.StatusCode));
					}

					//Define o ponteiro do buffer.
					EstruturaRetorno->bits = ConverterIntPtrTo<PBYTE>(IntptrBuffer);
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_MAPPED_RECT) para sua correspondencia gerenciada(CA_D2D1_MAPPED_RECT).
			CA_D2D1_MAPPED_RECT^ ConverterD2D1_MAPPED_RECTUnmanagedToManaged(D2D1_MAPPED_RECT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_MAPPED_RECT^ EstruturaRetorno = gcnew CA_D2D1_MAPPED_RECT();

				//Define os dados.
				EstruturaRetorno->pitch = Param_Estrutura->pitch;
				if (ObjetoValido(Param_Estrutura->bits))
				{
					//Inicializa a classe de buffer.
					EstruturaRetorno->bits = gcnew CarenBuffer();

					//Cria o buffer com base no ponteiro.
					static_cast<ICarenBuffer^>(EstruturaRetorno->bits)->CreateBuffer(IntPtr(Param_Estrutura->bits), false, 0, 0);
				}
				
				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_MATRIX_3X2_F) para sua correspondencia não gerenciada(D2D1_MATRIX_3X2_F).
			D2D1_MATRIX_3X2_F* ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(CA_D2D1_MATRIX_3X2_F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_MATRIX_3X2_F* EstruturaRetorno = CriarEstrutura<D2D1_MATRIX_3X2_F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados.
				EstruturaRetorno->dx = Param_Estrutura->dx;
				EstruturaRetorno->dy = Param_Estrutura->dy;
				EstruturaRetorno->m11 = Param_Estrutura->m11;
				EstruturaRetorno->m12 = Param_Estrutura->m12;
				EstruturaRetorno->m21 = Param_Estrutura->m21;
				EstruturaRetorno->m22 = Param_Estrutura->m22;
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;

				//Copia os dados para o array Jagged
				for (UINT32 Linhas = 0; Linhas < 3; Linhas++)
				{
					for (UINT32 Colunas = 0; Colunas < 2; Colunas++)
					{
						EstruturaRetorno->m[Linhas][Colunas] = EstruturaRetorno->m[Linhas][Colunas];
					}
				}
			
				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_MATRIX_3X2_F) para sua correspondencia gerenciada(CA_D2D1_MATRIX_3X2_F).
			CA_D2D1_MATRIX_3X2_F^ ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(D2D1_MATRIX_3X2_F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_MATRIX_3X2_F^ EstruturaRetorno = gcnew CA_D2D1_MATRIX_3X2_F();

				//Define os dados.
				EstruturaRetorno->dx = Param_Estrutura->dx;
				EstruturaRetorno->dy = Param_Estrutura->dy;
				EstruturaRetorno->m11 = Param_Estrutura->m11;
				EstruturaRetorno->m12 = Param_Estrutura->m12;
				EstruturaRetorno->m21 = Param_Estrutura->m21;
				EstruturaRetorno->m22 = Param_Estrutura->m22;
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;

				//Cria o array Jagged - Linhas
				EstruturaRetorno->m = gcnew cli::array<cli::array<float>^>(3); //3 Linhas
				for (int i = 0; i < 2; i++)
				{
					EstruturaRetorno->m[i] = gcnew cli::array<float>(2);//2 colunas
				}

				//Copia os dados para o array Jagged
				for (UINT32 Linhas = 0; Linhas < 3; Linhas++)
				{
					for (UINT32 Colunas = 0; Colunas < 2; Colunas++)
					{
						EstruturaRetorno->m[Linhas][Colunas] = EstruturaRetorno->m[Linhas][Colunas];
					}
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_MATRIX_4X4_F) para sua correspondencia não gerenciada(D2D1_MATRIX_4X4_F).
			D2D1_MATRIX_4X4_F* ConverterD2D1_MATRIX_4X4_FManagedToUnmanaged(CA_D2D1_MATRIX_4X4_F^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_MATRIX_4X4_F* EstruturaRetorno = CriarEstrutura<D2D1_MATRIX_4X4_F>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_MATRIX_4X4_F));

				//Define os dados.
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;
				EstruturaRetorno->_33 = Param_Estrutura->_33;
				EstruturaRetorno->_34 = Param_Estrutura->_34;
				EstruturaRetorno->_41 = Param_Estrutura->_41;
				EstruturaRetorno->_42 = Param_Estrutura->_42;
				EstruturaRetorno->_43 = Param_Estrutura->_43;
				EstruturaRetorno->_44 = Param_Estrutura->_44;

				//Copia os dados para o array Jagged
				for (UINT32 Linhas = 0; Linhas < 4; Linhas++)
				{
					for (UINT32 Colunas = 0; Colunas < 4; Colunas++)
					{
						EstruturaRetorno->m[Linhas][Colunas] = EstruturaRetorno->m[Linhas][Colunas];
					}
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_MATRIX_4X4_F) para sua correspondencia gerenciada(CA_D2D1_MATRIX_4X4_F).
			CA_D2D1_MATRIX_4X4_F^ ConverterD2D1_MATRIX_4X4_FUnmanagedToManaged(D2D1_MATRIX_4X4_F* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_MATRIX_4X4_F^ EstruturaRetorno = gcnew CA_D2D1_MATRIX_4X4_F();

				//Define os dados.
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;
				EstruturaRetorno->_33 = Param_Estrutura->_33;
				EstruturaRetorno->_34 = Param_Estrutura->_34;
				EstruturaRetorno->_41 = Param_Estrutura->_41;
				EstruturaRetorno->_42 = Param_Estrutura->_42;
				EstruturaRetorno->_43 = Param_Estrutura->_43;
				EstruturaRetorno->_44 = Param_Estrutura->_44;

				//Cria o array Jagged - Linhas
				EstruturaRetorno->m = gcnew cli::array<cli::array<float>^>(4); //4 Linhas
				for (int i = 0; i < 4; i++)
				{
					EstruturaRetorno->m[i] = gcnew cli::array<float>(4);//4 colunas
				}

				//Copia os dados para o array Jagged
				for (UINT32 Linhas = 0; Linhas < 4; Linhas++)
				{
					for (UINT32 Colunas = 0; Colunas < 4; Colunas++)
					{
						EstruturaRetorno->m[Linhas][Colunas] = EstruturaRetorno->m[Linhas][Colunas];
					}
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_TRIANGLE) para sua correspondencia não gerenciada(D2D1_TRIANGLE).
			D2D1_TRIANGLE* ConverterD2D1_TRIANGLEManagedToUnmanaged(CA_D2D1_TRIANGLE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_TRIANGLE* EstruturaRetorno = CriarEstrutura<D2D1_TRIANGLE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_TRIANGLE));

				//Define os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->point1))
				{
					EstruturaRetorno->point1.x = Param_Estrutura->point1->x;
					EstruturaRetorno->point1.y = Param_Estrutura->point1->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point2))
				{
					EstruturaRetorno->point2.x = Param_Estrutura->point2->x;
					EstruturaRetorno->point2.y = Param_Estrutura->point2->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point3))
				{
					EstruturaRetorno->point3.x = Param_Estrutura->point3->x;
					EstruturaRetorno->point3.y = Param_Estrutura->point3->y;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_TRIANGLE) para sua correspondencia gerenciada(CA_D2D1_TRIANGLE).
			CA_D2D1_TRIANGLE^ ConverterD2D1_TRIANGLEUnmanagedToManaged(D2D1_TRIANGLE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_TRIANGLE^ EstruturaRetorno = gcnew CA_D2D1_TRIANGLE();

				//Cria as estruturas.
				EstruturaRetorno->point1 = gcnew CA_D2D1_POINT_2F();
				EstruturaRetorno->point2 = gcnew CA_D2D1_POINT_2F();
				EstruturaRetorno->point3 = gcnew CA_D2D1_POINT_2F();

				//Define os dados.

				//1
				EstruturaRetorno->point1->x = Param_Estrutura->point1.x;
				EstruturaRetorno->point1->y = Param_Estrutura->point1.y;

				//2
				EstruturaRetorno->point2->x = Param_Estrutura->point2.x;
				EstruturaRetorno->point2->y = Param_Estrutura->point2.y;

				//3
				EstruturaRetorno->point3->x = Param_Estrutura->point3.x;
				EstruturaRetorno->point3->y = Param_Estrutura->point3.y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BEZIER_SEGMENT) para sua correspondencia não gerenciada(D2D1_BEZIER_SEGMENT).
			D2D1_BEZIER_SEGMENT* ConverterD2D1_BEZIER_SEGMENTManagedToUnmanaged(CA_D2D1_BEZIER_SEGMENT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BEZIER_SEGMENT* EstruturaRetorno = CriarEstrutura<D2D1_BEZIER_SEGMENT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BEZIER_SEGMENT));

				//Define os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->point1))
				{
					EstruturaRetorno->point1.x = Param_Estrutura->point1->x;
					EstruturaRetorno->point1.y = Param_Estrutura->point1->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point2))
				{
					EstruturaRetorno->point2.x = Param_Estrutura->point2->x;
					EstruturaRetorno->point2.y = Param_Estrutura->point2->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point3))
				{
					EstruturaRetorno->point3.x = Param_Estrutura->point3->x;
					EstruturaRetorno->point3.y = Param_Estrutura->point3->y;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BEZIER_SEGMENT) para sua correspondencia gerenciada(CA_D2D1_BEZIER_SEGMENT).
			CA_D2D1_BEZIER_SEGMENT^ ConverterD2D1_BEZIER_SEGMENTUnmanagedToManaged(D2D1_TRIANGLE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BEZIER_SEGMENT^ EstruturaRetorno = gcnew CA_D2D1_BEZIER_SEGMENT();

				//Cria as estruturas.
				EstruturaRetorno->point1 = gcnew CA_D2D1_POINT_2F();
				EstruturaRetorno->point2 = gcnew CA_D2D1_POINT_2F();
				EstruturaRetorno->point3 = gcnew CA_D2D1_POINT_2F();

				//Define os dados.

				//1
				EstruturaRetorno->point1->x = Param_Estrutura->point1.x;
				EstruturaRetorno->point1->y = Param_Estrutura->point1.y;

				//2
				EstruturaRetorno->point2->x = Param_Estrutura->point2.x;
				EstruturaRetorno->point2->y = Param_Estrutura->point2.y;

				//3
				EstruturaRetorno->point3->x = Param_Estrutura->point3.x;
				EstruturaRetorno->point3->y = Param_Estrutura->point3.y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_ARC_SEGMENT) para sua correspondencia não gerenciada(D2D1_ARC_SEGMENT).
			D2D1_ARC_SEGMENT* ConverterD2D1_ARC_SEGMENTManagedToUnmanaged(CA_D2D1_ARC_SEGMENT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_ARC_SEGMENT* EstruturaRetorno = CriarEstrutura<D2D1_ARC_SEGMENT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_ARC_SEGMENT));

				//Define os dados.
				EstruturaRetorno->arcSize = static_cast<D2D1_ARC_SIZE>(Param_Estrutura->arcSize);
				EstruturaRetorno->rotationAngle = Param_Estrutura->rotationAngle;
				EstruturaRetorno->sweepDirection = static_cast<D2D1_SWEEP_DIRECTION>(Param_Estrutura->sweepDirection);

				//Define os valores das demais estruturas.
				if (ObjetoGerenciadoValido(Param_Estrutura->point))
				{
					//Define os pontos.
					EstruturaRetorno->point.x = Param_Estrutura->point->x;
					EstruturaRetorno->point.y = Param_Estrutura->point->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->size))
				{
					//Define os pontos.
					EstruturaRetorno->size.height = Param_Estrutura->size->height;
					EstruturaRetorno->size.width = Param_Estrutura->size->width;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_ARC_SEGMENT) para sua correspondencia gerenciada(CA_D2D1_ARC_SEGMENT).
			CA_D2D1_ARC_SEGMENT^ ConverterD2D1_ARC_SEGMENTUnmanagedToManaged(D2D1_ARC_SEGMENT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_ARC_SEGMENT^ EstruturaRetorno = gcnew CA_D2D1_ARC_SEGMENT();

				//Define os dados.
				EstruturaRetorno->arcSize = static_cast<CA_D2D1_ARC_SIZE>(Param_Estrutura->arcSize);
				EstruturaRetorno->rotationAngle = Param_Estrutura->rotationAngle;
				EstruturaRetorno->sweepDirection = static_cast<CA_D2D1_SWEEP_DIRECTION>(Param_Estrutura->sweepDirection);

				//Define os valores das demais estruturas.
				EstruturaRetorno->point = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point);
				EstruturaRetorno->size = ConverterD2D1_SIZE_FUnmanagedToManaged(&Param_Estrutura->size);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_QUADRATIC_BEZIER_SEGMENT) para sua correspondencia não gerenciada(D2D1_QUADRATIC_BEZIER_SEGMENT).
			D2D1_QUADRATIC_BEZIER_SEGMENT* ConverterD2D1_QUADRATIC_BEZIER_SEGMENTManagedToUnmanaged(CA_D2D1_QUADRATIC_BEZIER_SEGMENT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_QUADRATIC_BEZIER_SEGMENT* EstruturaRetorno = CriarEstrutura<D2D1_QUADRATIC_BEZIER_SEGMENT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_QUADRATIC_BEZIER_SEGMENT));

				//Define os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->point1))
				{
					EstruturaRetorno->point1.x = Param_Estrutura->point1->x;
					EstruturaRetorno->point1.y = Param_Estrutura->point1->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point2))
				{
					EstruturaRetorno->point2.x = Param_Estrutura->point2->x;
					EstruturaRetorno->point2.y = Param_Estrutura->point2->y;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_QUADRATIC_BEZIER_SEGMENT) para sua correspondencia gerenciada(CA_D2D1_QUADRATIC_BEZIER_SEGMENT).
			CA_D2D1_QUADRATIC_BEZIER_SEGMENT^ ConverterD2D1_QUADRATIC_BEZIER_SEGMENTUnmanagedToManaged(D2D1_QUADRATIC_BEZIER_SEGMENT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_QUADRATIC_BEZIER_SEGMENT^ EstruturaRetorno = gcnew CA_D2D1_QUADRATIC_BEZIER_SEGMENT();

				//Define os dados.
				EstruturaRetorno->point1 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point1);
				EstruturaRetorno->point2 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point2);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_GRADIENT_MESH_PATCH) para sua correspondencia não gerenciada(D2D1_GRADIENT_MESH_PATCH).
			D2D1_GRADIENT_MESH_PATCH* ConverterD2D1_GRADIENT_MESH_PATCHManagedToUnmanaged(CA_D2D1_GRADIENT_MESH_PATCH^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_GRADIENT_MESH_PATCH* EstruturaRetorno = CriarEstrutura<D2D1_GRADIENT_MESH_PATCH>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_GRADIENT_MESH_PATCH));

				//Define os dados.

				// - Define os dados de pontos.
				if (ObjetoGerenciadoValido(Param_Estrutura->point00))
				{
					//Define os dados do point.
					EstruturaRetorno->point00.x = Param_Estrutura->point00->x;
					EstruturaRetorno->point00.y = Param_Estrutura->point00->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point01))
				{
					//Define os dados do point.
					EstruturaRetorno->point01.x = Param_Estrutura->point01->x;
					EstruturaRetorno->point01.y = Param_Estrutura->point01->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point02))
				{
					//Define os dados do point.
					EstruturaRetorno->point02.x = Param_Estrutura->point02->x;
					EstruturaRetorno->point02.y = Param_Estrutura->point02->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point03))
				{
					//Define os dados do point.
					EstruturaRetorno->point03.x = Param_Estrutura->point03->x;
					EstruturaRetorno->point03.y = Param_Estrutura->point03->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point10))
				{
					//Define os dados do point.
					EstruturaRetorno->point10.x = Param_Estrutura->point10->x;
					EstruturaRetorno->point10.y = Param_Estrutura->point10->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point11))
				{
					//Define os dados do point.
					EstruturaRetorno->point11.x = Param_Estrutura->point11->x;
					EstruturaRetorno->point11.y = Param_Estrutura->point11->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point12))
				{
					//Define os dados do point.
					EstruturaRetorno->point12.x = Param_Estrutura->point12->x;
					EstruturaRetorno->point12.y = Param_Estrutura->point12->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point13))
				{
					//Define os dados do point.
					EstruturaRetorno->point13.x = Param_Estrutura->point13->x;
					EstruturaRetorno->point13.y = Param_Estrutura->point13->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point20))
				{
					//Define os dados do point.
					EstruturaRetorno->point20.x = Param_Estrutura->point20->x;
					EstruturaRetorno->point20.y = Param_Estrutura->point20->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point21))
				{
					//Define os dados do point.
					EstruturaRetorno->point21.x = Param_Estrutura->point21->x;
					EstruturaRetorno->point21.y = Param_Estrutura->point21->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point22))
				{
					//Define os dados do point.
					EstruturaRetorno->point22.x = Param_Estrutura->point22->x;
					EstruturaRetorno->point22.y = Param_Estrutura->point22->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point23))
				{
					//Define os dados do point.
					EstruturaRetorno->point23.x = Param_Estrutura->point23->x;
					EstruturaRetorno->point23.y = Param_Estrutura->point23->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point30))
				{
					//Define os dados do point.
					EstruturaRetorno->point30.x = Param_Estrutura->point30->x;
					EstruturaRetorno->point30.y = Param_Estrutura->point30->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point31))
				{
					//Define os dados do point.
					EstruturaRetorno->point31.x = Param_Estrutura->point31->x;
					EstruturaRetorno->point31.y = Param_Estrutura->point31->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point32))
				{
					//Define os dados do point.
					EstruturaRetorno->point32.x = Param_Estrutura->point32->x;
					EstruturaRetorno->point32.y = Param_Estrutura->point32->y;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->point33))
				{
					//Define os dados do point.
					EstruturaRetorno->point33.x = Param_Estrutura->point33->x;
					EstruturaRetorno->point33.y = Param_Estrutura->point33->y;
				}
				
				// - Define os dados de cor.
				if (ObjetoGerenciadoValido(Param_Estrutura->color00))
				{
					EstruturaRetorno->color00.r = Param_Estrutura->color00->r;
					EstruturaRetorno->color00.g = Param_Estrutura->color00->g;
					EstruturaRetorno->color00.b = Param_Estrutura->color00->b;
					EstruturaRetorno->color00.a = Param_Estrutura->color00->a;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->color03))
				{
					EstruturaRetorno->color03.r = Param_Estrutura->color03->r;
					EstruturaRetorno->color03.g = Param_Estrutura->color03->g;
					EstruturaRetorno->color03.b = Param_Estrutura->color03->b;
					EstruturaRetorno->color03.a = Param_Estrutura->color03->a;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->color30))
				{
					EstruturaRetorno->color30.r = Param_Estrutura->color30->r;
					EstruturaRetorno->color30.g = Param_Estrutura->color30->g;
					EstruturaRetorno->color30.b = Param_Estrutura->color30->b;
					EstruturaRetorno->color30.a = Param_Estrutura->color30->a;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->color33))
				{
					EstruturaRetorno->color33.r = Param_Estrutura->color33->r;
					EstruturaRetorno->color33.g = Param_Estrutura->color33->g;
					EstruturaRetorno->color33.b = Param_Estrutura->color33->b;
					EstruturaRetorno->color33.a = Param_Estrutura->color33->a;
				}

				// - Define os dados das enumerações.
				EstruturaRetorno->rightEdgeMode = static_cast<D2D1_PATCH_EDGE_MODE>(Param_Estrutura->rightEdgeMode);
				EstruturaRetorno->leftEdgeMode = static_cast<D2D1_PATCH_EDGE_MODE>(Param_Estrutura->leftEdgeMode);
				EstruturaRetorno->topEdgeMode = static_cast<D2D1_PATCH_EDGE_MODE>(Param_Estrutura->topEdgeMode);
				EstruturaRetorno->bottomEdgeMode = static_cast<D2D1_PATCH_EDGE_MODE>(Param_Estrutura->bottomEdgeMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_GRADIENT_MESH_PATCH) para sua correspondencia gerenciada(CA_D2D1_GRADIENT_MESH_PATCH).
			CA_D2D1_GRADIENT_MESH_PATCH^ ConverterD2D1_GRADIENT_MESH_PATCHUnmanagedToManaged(D2D1_GRADIENT_MESH_PATCH* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_GRADIENT_MESH_PATCH^ EstruturaRetorno = gcnew CA_D2D1_GRADIENT_MESH_PATCH();

				//Define os dados.

				// - Define os dados de pontos.
				EstruturaRetorno->point00 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point00);
				EstruturaRetorno->point01 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point01);
				EstruturaRetorno->point02 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point02);
				EstruturaRetorno->point03 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point03);
				EstruturaRetorno->point10 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point10);
				EstruturaRetorno->point11 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point11);
				EstruturaRetorno->point12 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point12);
				EstruturaRetorno->point13 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point13);
				EstruturaRetorno->point20 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point20);
				EstruturaRetorno->point21 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point21);
				EstruturaRetorno->point22 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point22);
				EstruturaRetorno->point23 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point23);
				EstruturaRetorno->point30 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point30);
				EstruturaRetorno->point31 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point31);
				EstruturaRetorno->point32 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point32);
				EstruturaRetorno->point33 = ConverterD2D1_POINT_2FUnmanagedToManaged(&Param_Estrutura->point33);

				// - Define os dados de cor.
				EstruturaRetorno->color00 = ConverterD2D1_COLOR_FUnmanagedToManaged(&Param_Estrutura->color00);
				EstruturaRetorno->color03 = ConverterD2D1_COLOR_FUnmanagedToManaged(&Param_Estrutura->color03);
				EstruturaRetorno->color30 = ConverterD2D1_COLOR_FUnmanagedToManaged(&Param_Estrutura->color30);
				EstruturaRetorno->color33 = ConverterD2D1_COLOR_FUnmanagedToManaged(&Param_Estrutura->color33);
				
				// - Define os dados das enumerações.
				EstruturaRetorno->rightEdgeMode = static_cast<CA_D2D1_PATCH_EDGE_MODE>(Param_Estrutura->rightEdgeMode);
				EstruturaRetorno->leftEdgeMode = static_cast<CA_D2D1_PATCH_EDGE_MODE>(Param_Estrutura->leftEdgeMode);
				EstruturaRetorno->topEdgeMode = static_cast<CA_D2D1_PATCH_EDGE_MODE>(Param_Estrutura->topEdgeMode);
				EstruturaRetorno->bottomEdgeMode = static_cast<CA_D2D1_PATCH_EDGE_MODE>(Param_Estrutura->bottomEdgeMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_ELLIPSE) para sua correspondencia não gerenciada(D2D1_ELLIPSE).
			D2D1_ELLIPSE* ConverterD2D1_ELLIPSEManagedToUnmanaged(CA_D2D1_ELLIPSE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_ELLIPSE* EstruturaRetorno = CriarEstrutura<D2D1_ELLIPSE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_ELLIPSE));

				//Define os dados.
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;
				if (ObjetoGerenciadoValido(Param_Estrutura->point))
				{
					EstruturaRetorno->point.x = Param_Estrutura->point->x;
					EstruturaRetorno->point.y = Param_Estrutura->point->y;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_ELLIPSE) para sua correspondencia gerenciada(CA_D2D1_ELLIPSE).
			CA_D2D1_ELLIPSE^ ConverterD2D1_ELLIPSEUnmanagedToManaged(D2D1_ELLIPSE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_ELLIPSE^ EstruturaRetorno = gcnew CA_D2D1_ELLIPSE();

				//Cria as estruturas secundarias
				EstruturaRetorno->point = gcnew CA_D2D1_POINT_2F();

				//Define os dados.
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;
				EstruturaRetorno->point->x = Param_Estrutura->point.x;
				EstruturaRetorno->point->y = Param_Estrutura->point.y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_ROUNDED_RECT) para sua correspondencia não gerenciada(D2D1_ROUNDED_RECT).
			D2D1_ROUNDED_RECT* ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(CA_D2D1_ROUNDED_RECT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_ROUNDED_RECT* EstruturaRetorno = CriarEstrutura<D2D1_ROUNDED_RECT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_ROUNDED_RECT));

				//Define os dados.
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;
				
				//Define a estrutura rect se valida
				if (ObjetoGerenciadoValido(Param_Estrutura->rect))
				{
					//Define os dados.
					EstruturaRetorno->rect.top = Param_Estrutura->rect->top;
					EstruturaRetorno->rect.right = Param_Estrutura->rect->right;
					EstruturaRetorno->rect.left = Param_Estrutura->rect->left;
					EstruturaRetorno->rect.bottom = Param_Estrutura->rect->bottom;
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_ROUNDED_RECT) para sua correspondencia gerenciada(CA_D2D1_ROUNDED_RECT).
			CA_D2D1_ROUNDED_RECT^ ConverterD2D1_ROUNDED_RECTUnmanagedToManaged(D2D1_ROUNDED_RECT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_ROUNDED_RECT^ EstruturaRetorno = gcnew CA_D2D1_ROUNDED_RECT();

				//Cria as estruturas secundarias
				EstruturaRetorno->rect = gcnew CA_D2D1_RECT_F();

				//Define os dados.
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;

				//Define os dados da estrutura rect
				EstruturaRetorno->rect->top = Param_Estrutura->rect.top;
				EstruturaRetorno->rect->right = Param_Estrutura->rect.right;
				EstruturaRetorno->rect->left = Param_Estrutura->rect.left;
				EstruturaRetorno->rect->bottom = Param_Estrutura->rect.bottom;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_DRAWING_STATE_DESCRIPTION) para sua correspondencia não gerenciada(D2D1_DRAWING_STATE_DESCRIPTION).
			D2D1_DRAWING_STATE_DESCRIPTION* ConverterD2D1_DRAWING_STATE_DESCRIPTIONManagedToUnmanaged(CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_DRAWING_STATE_DESCRIPTION* EstruturaRetorno = CriarEstrutura<D2D1_DRAWING_STATE_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_DRAWING_STATE_DESCRIPTION));

				//Variriaveis
				D2D1_MATRIX_3X2_F *pMatrix = NULL;

				//Define os dados.
				EstruturaRetorno->antialiasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_Estrutura->antialiasMode);
				EstruturaRetorno->textAntialiasMode = static_cast<D2D1_TEXT_ANTIALIAS_MODE>(Param_Estrutura->textAntialiasMode);
				EstruturaRetorno->tag1 = static_cast<D2D1_TAG>(Param_Estrutura->tag1);
				EstruturaRetorno->tag2 = static_cast<D2D1_TAG>(Param_Estrutura->tag2);
				if (ObjetoGerenciadoValido(Param_Estrutura->transform))
				{
					//Converte para o nativo.
					pMatrix = ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->transform);
					
					//Define os dados a parti do ponteiro.
					EstruturaRetorno->transform = *pMatrix;

					//Exclui a estrutura nativa.
					DeletarEstruturaSafe(&pMatrix);
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_DRAWING_STATE_DESCRIPTION) para sua correspondencia gerenciada(CA_D2D1_DRAWING_STATE_DESCRIPTION).
			CA_D2D1_DRAWING_STATE_DESCRIPTION^ ConverterD2D1_DRAWING_STATE_DESCRIPTIONUnmanagedToManaged(D2D1_DRAWING_STATE_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_DRAWING_STATE_DESCRIPTION^ EstruturaRetorno = gcnew CA_D2D1_DRAWING_STATE_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->antialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(Param_Estrutura->antialiasMode);
				EstruturaRetorno->textAntialiasMode = static_cast<CA_D2D1_TEXT_ANTIALIAS_MODE>(Param_Estrutura->textAntialiasMode);
				EstruturaRetorno->tag1 = static_cast<unsigned long long>(Param_Estrutura->tag1);
				EstruturaRetorno->tag2 = static_cast<unsigned long long>(Param_Estrutura->tag2);
				EstruturaRetorno->transform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->transform);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_DRAWING_STATE_DESCRIPTION1) para sua correspondencia não gerenciada(D2D1_DRAWING_STATE_DESCRIPTION1).
			D2D1_DRAWING_STATE_DESCRIPTION1* ConverterD2D1_DRAWING_STATE_DESCRIPTION1ManagedToUnmanaged(CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_DRAWING_STATE_DESCRIPTION1* EstruturaRetorno = CriarEstrutura<D2D1_DRAWING_STATE_DESCRIPTION1>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_DRAWING_STATE_DESCRIPTION1));

				//Variriaveis
				D2D1_MATRIX_3X2_F* pMatrix = NULL;

				//Define os dados.
				EstruturaRetorno->antialiasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_Estrutura->antialiasMode);
				EstruturaRetorno->textAntialiasMode = static_cast<D2D1_TEXT_ANTIALIAS_MODE>(Param_Estrutura->textAntialiasMode);
				EstruturaRetorno->tag1 = static_cast<D2D1_TAG>(Param_Estrutura->tag1);
				EstruturaRetorno->tag2 = static_cast<D2D1_TAG>(Param_Estrutura->tag2);
				EstruturaRetorno->primitiveBlend = static_cast<D2D1_PRIMITIVE_BLEND>(Param_Estrutura->primitiveBlend);
				EstruturaRetorno->unitMode = static_cast<D2D1_UNIT_MODE>(Param_Estrutura->unitMode);
				if (ObjetoGerenciadoValido(Param_Estrutura->transform))
				{
					//Converte para o nativo.
					pMatrix = ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->transform);

					//Define os dados a parti do ponteiro.
					EstruturaRetorno->transform = *pMatrix;

					//Exclui a estrutura nativa.
					DeletarEstruturaSafe(&pMatrix);
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_DRAWING_STATE_DESCRIPTION1) para sua correspondencia gerenciada(CA_D2D1_DRAWING_STATE_DESCRIPTION1).
			CA_D2D1_DRAWING_STATE_DESCRIPTION1^ ConverterD2D1_DRAWING_STATE_DESCRIPTION1UnmanagedToManaged(D2D1_DRAWING_STATE_DESCRIPTION1* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_DRAWING_STATE_DESCRIPTION1^ EstruturaRetorno = gcnew CA_D2D1_DRAWING_STATE_DESCRIPTION1();

				//Define os dados.
				EstruturaRetorno->antialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(Param_Estrutura->antialiasMode);
				EstruturaRetorno->textAntialiasMode = static_cast<CA_D2D1_TEXT_ANTIALIAS_MODE>(Param_Estrutura->textAntialiasMode);
				EstruturaRetorno->tag1 = static_cast<unsigned long long>(Param_Estrutura->tag1);
				EstruturaRetorno->tag2 = static_cast<unsigned long long>(Param_Estrutura->tag2);
				EstruturaRetorno->primitiveBlend = static_cast<CA_D2D1_PRIMITIVE_BLEND>(Param_Estrutura->primitiveBlend);
				EstruturaRetorno->unitMode = static_cast<CA_D2D1_UNIT_MODE>(Param_Estrutura->unitMode);
				EstruturaRetorno->transform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->transform);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_INPUT_DESCRIPTION) para sua correspondencia não gerenciada(D2D1_INPUT_DESCRIPTION).
			D2D1_INPUT_DESCRIPTION* ConverterD2D1_INPUT_DESCRIPTIONManagedToUnmanaged(CA_D2D1_INPUT_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_INPUT_DESCRIPTION* EstruturaRetorno = CriarEstrutura<D2D1_INPUT_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_INPUT_DESCRIPTION));

				//Define os dados.
				EstruturaRetorno->filter = static_cast<D2D1_FILTER>(Param_Estrutura->filter);
				EstruturaRetorno->levelOfDetailCount = Param_Estrutura->levelOfDetailCount;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_INPUT_DESCRIPTION) para sua correspondencia gerenciada(CA_D2D1_INPUT_DESCRIPTION).
			CA_D2D1_INPUT_DESCRIPTION^ ConverterD2D1_INPUT_DESCRIPTIONUnmanagedToManaged(D2D1_INPUT_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_INPUT_DESCRIPTION^ EstruturaRetorno = gcnew CA_D2D1_INPUT_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->filter = static_cast<CA_D2D1_FILTER>(Param_Estrutura->filter);
				EstruturaRetorno->levelOfDetailCount = Param_Estrutura->levelOfDetailCount;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BITMAP_PROPERTIES) para sua correspondencia não gerenciada(D2D1_BITMAP_PROPERTIES).
			D2D1_BITMAP_PROPERTIES* ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(CA_D2D1_BITMAP_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BITMAP_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_BITMAP_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BITMAP_PROPERTIES));

				//Variaveis
				D2D1_PIXEL_FORMAT* pPixelFormato = NULL;

				//Converte a estrutura do formato de pixel para a nativa.
				pPixelFormato = ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(Param_Estrutura->pixelFormat);

				//Define os dados.
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->pixelFormat = *pPixelFormato;

				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pPixelFormato);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BITMAP_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_BITMAP_PROPERTIES).
			CA_D2D1_BITMAP_PROPERTIES^ ConverterD2D1_BITMAP_PROPERTIESUnmanagedToManaged(D2D1_BITMAP_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BITMAP_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_BITMAP_PROPERTIES();

				//Variaveis
				CA_D2D1_PIXEL_FORMAT^ PixelFormato = nullptr;

				//Converte a estrutura do formato de pixel para a nativa.
				PixelFormato = ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&Param_Estrutura->pixelFormat);

				//Define os dados.
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->pixelFormat = PixelFormato;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BITMAP_PROPERTIES1) para sua correspondencia não gerenciada(D2D1_BITMAP_PROPERTIES1).
			D2D1_BITMAP_PROPERTIES1* ConverterD2D1_BITMAP_PROPERTIES1ManagedToUnmanaged(CA_D2D1_BITMAP_PROPERTIES1^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BITMAP_PROPERTIES1* EstruturaRetorno = CriarEstrutura<D2D1_BITMAP_PROPERTIES1>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BITMAP_PROPERTIES1));

				//Variaveis
				D2D1_PIXEL_FORMAT* pPixelFormato = NULL;
				ID2D1ColorContext* pColorContext = NULL;

				//Converte a estrutura do formato de pixel para a nativa.
				pPixelFormato = ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(Param_Estrutura->pixelFormat);

				//Recupera o ponteiro para a interface de cor do contexto se fornecido
				if (ObjetoGerenciadoValido(Param_Estrutura->colorContext))
				{
					//Recupera o ponteiro para a interface.
					static_cast<ICaren^>(Param_Estrutura->colorContext)->RecuperarPonteiro((LPVOID*)&pColorContext);
				}

				//Define os dados.
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->pixelFormat = *pPixelFormato;
				EstruturaRetorno->bitmapOptions = static_cast<D2D1_BITMAP_OPTIONS>(Param_Estrutura->bitmapOptions);
				EstruturaRetorno->colorContext = pColorContext;

				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pPixelFormato);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BITMAP_PROPERTIES1) para sua correspondencia gerenciada(CA_D2D1_BITMAP_PROPERTIES1).
			CA_D2D1_BITMAP_PROPERTIES1^ ConverterD2D1_BITMAP_PROPERTIES1UnmanagedToManaged(D2D1_BITMAP_PROPERTIES1* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BITMAP_PROPERTIES1^ EstruturaRetorno = gcnew CA_D2D1_BITMAP_PROPERTIES1();

				//Variaveis
				CA_D2D1_PIXEL_FORMAT^ PixelFormato = nullptr;
				ICaren^ D2dColorContext = nullptr;

				//Converte a estrutura do formato de pixel para a nativa.
				PixelFormato = ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&Param_Estrutura->pixelFormat);

				//Verifica se forneceu a interface de contexto de cor.
				if (ObjetoValido(Param_Estrutura->colorContext))
				{
					//Cria a interface que vai segurar o ponteiro.
					D2dColorContext = gcnew Caren();

					//Adiciona o ponteiro.
					D2dColorContext->AdicionarPonteiro(Param_Estrutura->colorContext);

					//Adiciona uma Referencia
					D2dColorContext->AdicionarReferencia();
				}

				//Define os dados.
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->pixelFormat = PixelFormato;
				EstruturaRetorno->bitmapOptions = static_cast<CA_D2D1_BITMAP_OPTIONS>(Param_Estrutura->bitmapOptions);
				EstruturaRetorno->colorContext = D2dColorContext;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BITMAP_BRUSH_PROPERTIES) para sua correspondencia não gerenciada(D2D1_BITMAP_BRUSH_PROPERTIES).
			D2D1_BITMAP_BRUSH_PROPERTIES* ConverterD2D1_BITMAP_BRUSH_PROPERTIESManagedToUnmanaged(CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BITMAP_BRUSH_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_BITMAP_BRUSH_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BITMAP_BRUSH_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<D2D1_BITMAP_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BITMAP_BRUSH_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_BITMAP_BRUSH_PROPERTIES).
			CA_D2D1_BITMAP_BRUSH_PROPERTIES^ ConverterD2D1_BITMAP_BRUSH_PROPERTIESUnmanagedToManaged(D2D1_BITMAP_BRUSH_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BITMAP_BRUSH_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_BITMAP_BRUSH_PROPERTIES();
			
				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<CA_D2D1_BITMAP_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BITMAP_BRUSH_PROPERTIES1) para sua correspondencia não gerenciada(D2D1_BITMAP_BRUSH_PROPERTIES1).
			D2D1_BITMAP_BRUSH_PROPERTIES1* ConverterD2D1_BITMAP_BRUSH_PROPERTIES1ManagedToUnmanaged(CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BITMAP_BRUSH_PROPERTIES1* EstruturaRetorno = CriarEstrutura<D2D1_BITMAP_BRUSH_PROPERTIES1>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BITMAP_BRUSH_PROPERTIES1));

				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BITMAP_BRUSH_PROPERTIES1) para sua correspondencia gerenciada(CA_D2D1_BITMAP_BRUSH_PROPERTIES1).
			CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ ConverterD2D1_BITMAP_BRUSH_PROPERTIES1UnmanagedToManaged(D2D1_BITMAP_BRUSH_PROPERTIES1* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ EstruturaRetorno = gcnew CA_D2D1_BITMAP_BRUSH_PROPERTIES1();

				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<CA_D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura gerenciada(CA_D2D1_BRUSH_PROPERTIES) para sua correspondencia não gerenciada(D2D1_BRUSH_PROPERTIES).
			D2D1_BRUSH_PROPERTIES* ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(CA_D2D1_BRUSH_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BRUSH_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_BRUSH_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BRUSH_PROPERTIES));

				//Variaveis
				D2D1_MATRIX_3X2_F* pTransform = NULL;

				//Converte a tranformação se valida.
				pTransform = ObjetoGerenciadoValido(Param_Estrutura->transform)? ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->transform) : NULL;

				//Define os dados.
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->transform = *pTransform;

				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pTransform);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BRUSH_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_BRUSH_PROPERTIES).
			CA_D2D1_BRUSH_PROPERTIES^ ConverterD2D1_BRUSH_PROPERTIESUnmanagedToManaged(D2D1_BRUSH_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BRUSH_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_BRUSH_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->transform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->transform);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES) para sua correspondencia não gerenciada(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES).
			D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->startPoint.x = Param_Estrutura->startPoint->x;
				EstruturaRetorno->startPoint.y = Param_Estrutura->startPoint->y;
				EstruturaRetorno->endPoint.x = Param_Estrutura->endPoint->x;
				EstruturaRetorno->endPoint.y = Param_Estrutura->endPoint->y;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES).
			CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESUnmanagedToManaged(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->startPoint->x = Param_Estrutura->startPoint.x;
				EstruturaRetorno->startPoint->y = Param_Estrutura->startPoint.y;
				EstruturaRetorno->endPoint->x = Param_Estrutura->endPoint.x;
				EstruturaRetorno->endPoint->y = Param_Estrutura->endPoint.y;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES) para sua correspondencia não gerenciada(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES).
			D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->center.x = Param_Estrutura->center->x;
				EstruturaRetorno->center.y = Param_Estrutura->center->y;
				EstruturaRetorno->gradientOriginOffset.x = Param_Estrutura->gradientOriginOffset->x;
				EstruturaRetorno->gradientOriginOffset.y = Param_Estrutura->gradientOriginOffset->y;
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES).
			CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESUnmanagedToManaged(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->center->x = Param_Estrutura->center.x;
				EstruturaRetorno->center->y = Param_Estrutura->center.y;
				EstruturaRetorno->gradientOriginOffset->x = Param_Estrutura->gradientOriginOffset.x;
				EstruturaRetorno->gradientOriginOffset->y = Param_Estrutura->gradientOriginOffset.y;
				EstruturaRetorno->radiusX = Param_Estrutura->radiusX;
				EstruturaRetorno->radiusY = Param_Estrutura->radiusY;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RENDER_TARGET_PROPERTIES) para sua correspondencia não gerenciada(D2D1_RENDER_TARGET_PROPERTIES).
			D2D1_RENDER_TARGET_PROPERTIES* ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RENDER_TARGET_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_RENDER_TARGET_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_RENDER_TARGET_PROPERTIES));

				//Variaveis.
				D2D1_PIXEL_FORMAT* pPixelFormato = NULL;

				//Converte a estrutura.
				pPixelFormato = ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(Param_Estrutura->pixelFormat);

				//Define os dados.
				EstruturaRetorno->type = static_cast<D2D1_RENDER_TARGET_TYPE>(Param_Estrutura->type);
				EstruturaRetorno->pixelFormat = *pPixelFormato;
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->minLevel = static_cast<D2D1_FEATURE_LEVEL>(Param_Estrutura->minLevel);
				EstruturaRetorno->usage = static_cast<D2D1_RENDER_TARGET_USAGE>(Param_Estrutura->usage);

				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pPixelFormato);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RENDER_TARGET_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_RENDER_TARGET_PROPERTIES).
			CA_D2D1_RENDER_TARGET_PROPERTIES^ ConverterD2D1_RENDER_TARGET_PROPERTIESUnmanagedToManaged(D2D1_RENDER_TARGET_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RENDER_TARGET_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_RENDER_TARGET_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->type = static_cast<CA_D2D1_RENDER_TARGET_TYPE>(Param_Estrutura->type);
				EstruturaRetorno->pixelFormat = ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&Param_Estrutura->pixelFormat);
				EstruturaRetorno->dpiX = Param_Estrutura->dpiX;
				EstruturaRetorno->dpiY = Param_Estrutura->dpiY;
				EstruturaRetorno->minLevel = static_cast<CA_D2D1_FEATURE_LEVEL>(Param_Estrutura->minLevel);
				EstruturaRetorno->usage = static_cast<CA_D2D1_RENDER_TARGET_USAGE>(Param_Estrutura->usage);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_HWND_RENDER_TARGET_PROPERTIES) para sua correspondencia não gerenciada(D2D1_HWND_RENDER_TARGET_PROPERTIES).
			D2D1_HWND_RENDER_TARGET_PROPERTIES* ConverterD2D1_HWND_RENDER_TARGET_PROPERTIESManagedToUnmanaged(CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_HWND_RENDER_TARGET_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_HWND_RENDER_TARGET_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_HWND_RENDER_TARGET_PROPERTIES));

				//Variaveis.
				D2D1_SIZE_U* pPixelSize = NULL;

				//Converte a estrutura.
				pPixelSize = ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Estrutura->pixelSize);

				//Define os dados.
				EstruturaRetorno->hwnd = ConverterIntPtrToHWND(Param_Estrutura->hwnd);
				EstruturaRetorno->pixelSize = *pPixelSize;
				EstruturaRetorno->presentOptions = static_cast<D2D1_PRESENT_OPTIONS>(Param_Estrutura->presentOptions);

				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pPixelSize);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_HWND_RENDER_TARGET_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_HWND_RENDER_TARGET_PROPERTIES).
			CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ ConverterD2D1_HWND_RENDER_TARGET_PROPERTIESUnmanagedToManaged(D2D1_HWND_RENDER_TARGET_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_HWND_RENDER_TARGET_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->hwnd = ConverterHWNDToIntPtr(Param_Estrutura->hwnd);
				EstruturaRetorno->pixelSize = ConverterD2D1_SIZE_UUnmanagedToManaged(&Param_Estrutura->pixelSize);
				EstruturaRetorno->presentOptions = static_cast<CA_D2D1_PRESENT_OPTIONS>(Param_Estrutura->presentOptions);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_LAYER_PARAMETERS) para sua correspondencia não gerenciada(D2D1_LAYER_PARAMETERS).
			D2D1_LAYER_PARAMETERS* ConverterD2D1_LAYER_PARAMETERSManagedToUnmanaged(CA_D2D1_LAYER_PARAMETERS^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_LAYER_PARAMETERS* EstruturaRetorno = CriarEstrutura<D2D1_LAYER_PARAMETERS>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_LAYER_PARAMETERS));

				//Variaveis
				D2D1_RECT_F* pRectF = NULL;
				D2D1_MATRIX_3X2_F* pMatrix = NULL;
				ID2D1Geometry* pGeometryMask = NULL;
				ID2D1Brush* pBrushOpacity = NULL;

				//Converte as estruturas.
				pRectF = ConverterD2D1_RECT_FManagedToUnmanaged(Param_Estrutura->contentBounds);
				pMatrix = ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->maskTransform);

				//Recupera os ponteiros.
				static_cast<ICaren^>(Param_Estrutura->geometricMask)->RecuperarPonteiro((LPVOID*)&pGeometryMask);
				static_cast<ICaren^>(Param_Estrutura->opacityBrush)->RecuperarPonteiro((LPVOID*)&pBrushOpacity);

				//Define os dados.
				EstruturaRetorno->contentBounds = *pRectF;
				EstruturaRetorno->geometricMask = pGeometryMask;
				EstruturaRetorno->maskAntialiasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_Estrutura->maskAntialiasMode);
				EstruturaRetorno->maskTransform = *pMatrix;
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->opacityBrush = pBrushOpacity;
				EstruturaRetorno->layerOptions = static_cast<D2D1_LAYER_OPTIONS>(Param_Estrutura->layerOptions);

				//Libera a memória para as estruturas.
				DeletarEstruturaSafe(&pRectF);
				DeletarEstruturaSafe(&pMatrix);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_LAYER_PARAMETERS) para sua correspondencia gerenciada(CA_D2D1_LAYER_PARAMETERS).
			CA_D2D1_LAYER_PARAMETERS^ ConverterD2D1_LAYER_PARAMETERSUnmanagedToManaged(D2D1_LAYER_PARAMETERS* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_LAYER_PARAMETERS^ EstruturaRetorno = gcnew CA_D2D1_LAYER_PARAMETERS();

				//Define os dados.
				EstruturaRetorno->contentBounds = ConverterD2D1_RECT_FUnmanagedToManaged(&Param_Estrutura->contentBounds);
				EstruturaRetorno->geometricMask = gcnew Caren();
				EstruturaRetorno->maskAntialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(Param_Estrutura->maskAntialiasMode);
				EstruturaRetorno->maskTransform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->maskTransform);
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->opacityBrush = gcnew Caren();
				EstruturaRetorno->layerOptions = static_cast<CA_D2D1_LAYER_OPTIONS>(Param_Estrutura->layerOptions);

				//Define os ponteiros nativos.
				static_cast<ICaren^>(EstruturaRetorno->geometricMask)->AdicionarPonteiro(Param_Estrutura->geometricMask);
				static_cast<ICaren^>(EstruturaRetorno->opacityBrush)->AdicionarPonteiro(Param_Estrutura->opacityBrush);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_LAYER_PARAMETERS) para sua correspondencia não gerenciada(D2D1_LAYER_PARAMETERS1).
			D2D1_LAYER_PARAMETERS1* ConverterD2D1_LAYER_PARAMETERS1ManagedToUnmanaged(CA_D2D1_LAYER_PARAMETERS1^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_LAYER_PARAMETERS1* EstruturaRetorno = CriarEstrutura<D2D1_LAYER_PARAMETERS1>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_LAYER_PARAMETERS1));

				//Variaveis
				D2D1_RECT_F* pRectF = NULL;
				D2D1_MATRIX_3X2_F* pMatrix = NULL;
				ID2D1Geometry* pGeometryMask = NULL;
				ID2D1Brush* pBrushOpacity = NULL;

				//Converte as estruturas.
				pRectF = ConverterD2D1_RECT_FManagedToUnmanaged(Param_Estrutura->contentBounds);
				pMatrix = ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->maskTransform);

				//Recupera os ponteiros.
				static_cast<ICaren^>(Param_Estrutura->geometricMask)->RecuperarPonteiro((LPVOID*)&pGeometryMask);
				static_cast<ICaren^>(Param_Estrutura->opacityBrush)->RecuperarPonteiro((LPVOID*)&pBrushOpacity);

				//Define os dados.
				EstruturaRetorno->contentBounds = *pRectF;
				EstruturaRetorno->geometricMask = pGeometryMask;
				EstruturaRetorno->maskAntialiasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_Estrutura->maskAntialiasMode);
				EstruturaRetorno->maskTransform = *pMatrix;
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->opacityBrush = pBrushOpacity;
				EstruturaRetorno->layerOptions = static_cast<D2D1_LAYER_OPTIONS1>(Param_Estrutura->layerOptions);

				//Libera a memória para as estruturas.
				DeletarEstruturaSafe(&pRectF);
				DeletarEstruturaSafe(&pMatrix);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_LAYER_PARAMETERS1) para sua correspondencia gerenciada(CA_D2D1_LAYER_PARAMETERS).
			CA_D2D1_LAYER_PARAMETERS1^ ConverterD2D1_LAYER_PARAMETERS1UnmanagedToManaged(D2D1_LAYER_PARAMETERS1* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_LAYER_PARAMETERS1^ EstruturaRetorno = gcnew CA_D2D1_LAYER_PARAMETERS1();

				//Define os dados.
				EstruturaRetorno->contentBounds = ConverterD2D1_RECT_FUnmanagedToManaged(&Param_Estrutura->contentBounds);
				EstruturaRetorno->geometricMask = gcnew Caren();
				EstruturaRetorno->maskAntialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(Param_Estrutura->maskAntialiasMode);
				EstruturaRetorno->maskTransform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->maskTransform);
				EstruturaRetorno->opacity = Param_Estrutura->opacity;
				EstruturaRetorno->opacityBrush = gcnew Caren();
				EstruturaRetorno->layerOptions = static_cast<CA_D2D1_LAYER_OPTIONS1>(Param_Estrutura->layerOptions);

				//Define os ponteiros nativos.
				static_cast<ICaren^>(EstruturaRetorno->geometricMask)->AdicionarPonteiro(Param_Estrutura->geometricMask);
				static_cast<ICaren^>(EstruturaRetorno->opacityBrush)->AdicionarPonteiro(Param_Estrutura->opacityBrush);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_BLEND_DESCRIPTION) para sua correspondencia não gerenciada(D2D1_BLEND_DESCRIPTION).
			D2D1_BLEND_DESCRIPTION* ConverterD2D1_BLEND_DESCRIPTIONManagedToUnmanaged(CA_D2D1_BLEND_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_BLEND_DESCRIPTION* EstruturaRetorno = CriarEstrutura<D2D1_BLEND_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_BLEND_DESCRIPTION));

				//Define os dados.
				EstruturaRetorno->sourceBlend = static_cast<D2D1_BLEND>(Param_Estrutura->sourceBlend);
				EstruturaRetorno->destinationBlend = static_cast<D2D1_BLEND>(Param_Estrutura->destinationBlend);
				EstruturaRetorno->blendOperation = static_cast<D2D1_BLEND_OPERATION>(Param_Estrutura->blendOperation);
				EstruturaRetorno->sourceBlendAlpha = static_cast<D2D1_BLEND>(Param_Estrutura->sourceBlendAlpha);
				EstruturaRetorno->destinationBlendAlpha = static_cast<D2D1_BLEND>(Param_Estrutura->destinationBlendAlpha);
				EstruturaRetorno->blendOperationAlpha = static_cast<D2D1_BLEND_OPERATION>(Param_Estrutura->blendOperationAlpha);
				
				//Define os dados do Array.
				EstruturaRetorno->blendFactor[0] = Param_Estrutura->blendFactor[0];
				EstruturaRetorno->blendFactor[1] = Param_Estrutura->blendFactor[1];
				EstruturaRetorno->blendFactor[2] = Param_Estrutura->blendFactor[2];
				EstruturaRetorno->blendFactor[3] = Param_Estrutura->blendFactor[3];

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_BLEND_DESCRIPTION) para sua correspondencia gerenciada(CA_D2D1_BLEND_DESCRIPTION).
			CA_D2D1_BLEND_DESCRIPTION^ ConverterD2D1_BLEND_DESCRIPTIONUnmanagedToManaged(D2D1_BLEND_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_BLEND_DESCRIPTION^ EstruturaRetorno = gcnew CA_D2D1_BLEND_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->sourceBlend = static_cast<CA_D2D1_BLEND>(Param_Estrutura->sourceBlend);
				EstruturaRetorno->destinationBlend = static_cast<CA_D2D1_BLEND>(Param_Estrutura->destinationBlend);
				EstruturaRetorno->blendOperation = static_cast<CA_D2D1_BLEND_OPERATION>(Param_Estrutura->blendOperation);
				EstruturaRetorno->sourceBlendAlpha = static_cast<CA_D2D1_BLEND>(Param_Estrutura->sourceBlendAlpha);
				EstruturaRetorno->destinationBlendAlpha = static_cast<CA_D2D1_BLEND>(Param_Estrutura->destinationBlendAlpha);
				EstruturaRetorno->blendOperationAlpha = static_cast<CA_D2D1_BLEND_OPERATION>(Param_Estrutura->blendOperationAlpha);

				//Cria o array
				EstruturaRetorno->blendFactor = gcnew cli::array<float>(4);

				//Define os dados do Array.
				EstruturaRetorno->blendFactor[0] = Param_Estrutura->blendFactor[0];
				EstruturaRetorno->blendFactor[1] = Param_Estrutura->blendFactor[1];
				EstruturaRetorno->blendFactor[2] = Param_Estrutura->blendFactor[2];
				EstruturaRetorno->blendFactor[3] = Param_Estrutura->blendFactor[3];
				
				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_INK_POINT) para sua correspondencia não gerenciada(D2D1_INK_POINT).
			D2D1_INK_POINT* ConverterD2D1_INK_POINTManagedToUnmanaged(CA_D2D1_INK_POINT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_INK_POINT* EstruturaRetorno = CriarEstrutura<D2D1_INK_POINT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_INK_POINT));

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;
				EstruturaRetorno->radius = Param_Estrutura->radius;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_INK_POINT) para sua correspondencia gerenciada(CA_D2D1_INK_POINT).
			CA_D2D1_INK_POINT^ ConverterD2D1_INK_POINTUnmanagedToManaged(D2D1_INK_POINT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_INK_POINT^ EstruturaRetorno = gcnew CA_D2D1_INK_POINT();

				//Define os dados.
				EstruturaRetorno->x = Param_Estrutura->x;
				EstruturaRetorno->y = Param_Estrutura->y;
				EstruturaRetorno->radius = Param_Estrutura->radius;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_INK_STYLE_PROPERTIES) para sua correspondencia não gerenciada(D2D1_INK_STYLE_PROPERTIES).
			D2D1_INK_STYLE_PROPERTIES* ConverterD2D1_INK_STYLE_PROPERTIESManagedToUnmanaged(CA_D2D1_INK_STYLE_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_INK_STYLE_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_INK_STYLE_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_INK_STYLE_PROPERTIES));

				//Variaveis
				D2D1_MATRIX_3X2_F* pNibTransform = NULL;

				//Converte a estrutura
				pNibTransform = ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Estrutura->nibTransform);

				//Define os dados.
				EstruturaRetorno->nibShape = static_cast<D2D1_INK_NIB_SHAPE>(Param_Estrutura->nibShape);
				EstruturaRetorno->nibTransform = *pNibTransform;

				//libera a memória para a matrix.
				DeletarEstruturaSafe(&pNibTransform);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_INK_STYLE_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_INK_STYLE_PROPERTIES).
			CA_D2D1_INK_STYLE_PROPERTIES^ ConverterD2D1_INK_STYLE_PROPERTIESUnmanagedToManaged(D2D1_INK_STYLE_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_INK_STYLE_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_INK_STYLE_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->nibShape = static_cast<CA_D2D1_INK_NIB_SHAPE>(Param_Estrutura->nibShape);
				EstruturaRetorno->nibTransform = ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&Param_Estrutura->nibTransform);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_INK_BEZIER_SEGMENT) para sua correspondencia não gerenciada(D2D1_INK_BEZIER_SEGMENT).
			D2D1_INK_BEZIER_SEGMENT* ConverterD2D1_INK_BEZIER_SEGMENTManagedToUnmanaged(CA_D2D1_INK_BEZIER_SEGMENT^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_INK_BEZIER_SEGMENT* EstruturaRetorno = CriarEstrutura<D2D1_INK_BEZIER_SEGMENT>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_INK_BEZIER_SEGMENT));

				//Variaveis
				D2D1_INK_POINT *pInk01, *pInk02, *pInk03;

				//Converte as estruturas se informada.
				pInk01 = ObjetoGerenciadoValido(Param_Estrutura->point1) ? ConverterD2D1_INK_POINTManagedToUnmanaged(Param_Estrutura->point1) : NULL;
				pInk02 = ObjetoGerenciadoValido(Param_Estrutura->point2) ? ConverterD2D1_INK_POINTManagedToUnmanaged(Param_Estrutura->point2) : NULL;
				pInk03 = ObjetoGerenciadoValido(Param_Estrutura->point3) ? ConverterD2D1_INK_POINTManagedToUnmanaged(Param_Estrutura->point3) : NULL;

				//Define os dados.
				EstruturaRetorno->point1 = *pInk01;
				EstruturaRetorno->point2 = *pInk02;
				EstruturaRetorno->point3 = *pInk03;

				//Libera a memória para as estruturas.
				DeletarEstruturaSafe(&pInk01);
				DeletarEstruturaSafe(&pInk02);
				DeletarEstruturaSafe(&pInk03);
				
				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_INK_BEZIER_SEGMENT) para sua correspondencia gerenciada(CA_D2D1_INK_BEZIER_SEGMENT).
			CA_D2D1_INK_BEZIER_SEGMENT^ ConverterD2D1_INK_BEZIER_SEGMENTUnmanagedToManaged(D2D1_INK_BEZIER_SEGMENT* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_INK_BEZIER_SEGMENT^ EstruturaRetorno = gcnew CA_D2D1_INK_BEZIER_SEGMENT();

				//Define os dados.
				EstruturaRetorno->point1 = ConverterD2D1_INK_POINTUnmanagedToManaged(&Param_Estrutura->point1);
				EstruturaRetorno->point2 = ConverterD2D1_INK_POINTUnmanagedToManaged(&Param_Estrutura->point2);
				EstruturaRetorno->point3 = ConverterD2D1_INK_POINTUnmanagedToManaged(&Param_Estrutura->point3);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_VERTEX_RANGE) para sua correspondencia não gerenciada(D2D1_VERTEX_RANGE).
			D2D1_VERTEX_RANGE* ConverterD2D1_VERTEX_RANGEManagedToUnmanaged(CA_D2D1_VERTEX_RANGE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_VERTEX_RANGE* EstruturaRetorno = CriarEstrutura<D2D1_VERTEX_RANGE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_VERTEX_RANGE));

				//Define os dados.
				EstruturaRetorno->startVertex = Param_Estrutura->startVertex;
				EstruturaRetorno->vertexCount = Param_Estrutura->vertexCount;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_VERTEX_RANGE) para sua correspondencia gerenciada(CA_D2D1_VERTEX_RANGE).
			CA_D2D1_VERTEX_RANGE^ ConverterD2D1_VERTEX_RANGEUnmanagedToManaged(D2D1_VERTEX_RANGE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_VERTEX_RANGE^ EstruturaRetorno = gcnew CA_D2D1_VERTEX_RANGE();

				//Define os dados.
				EstruturaRetorno->startVertex = Param_Estrutura->startVertex;
				EstruturaRetorno->vertexCount = Param_Estrutura->vertexCount;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RESOURCE_TEXTURE_PROPERTIES) para sua correspondencia não gerenciada(D2D1_RESOURCE_TEXTURE_PROPERTIES).
			D2D1_RESOURCE_TEXTURE_PROPERTIES* ConverterD2D1_RESOURCE_TEXTURE_PROPERTIESManagedToUnmanaged(CA_D2D1_RESOURCE_TEXTURE_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RESOURCE_TEXTURE_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_RESOURCE_TEXTURE_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_RESOURCE_TEXTURE_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->extents = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Estrutura->dimensions));
				EstruturaRetorno->dimensions = Param_Estrutura->dimensions;
				EstruturaRetorno->bufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_Estrutura->bufferPrecision);
				EstruturaRetorno->channelDepth = static_cast<D2D1_CHANNEL_DEPTH>(Param_Estrutura->channelDepth);
				EstruturaRetorno->filter = static_cast<D2D1_FILTER>(Param_Estrutura->filter);
				EstruturaRetorno->extendModes = CriarMatrizUnidimensional<D2D1_EXTEND_MODE>(static_cast<DWORD>(Param_Estrutura->dimensions));

				//Copia os dados para os arrays.
				CopiarItensTo_ArrayNativo(const_cast<UINT32**>(&EstruturaRetorno->extents), Param_Estrutura->extents, EstruturaRetorno->dimensions);
				CopiarItensTo_ArrayNativo(const_cast<D2D1_EXTEND_MODE**>(&EstruturaRetorno->extendModes), Param_Estrutura->extendModes, EstruturaRetorno->dimensions);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RESOURCE_TEXTURE_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_RESOURCE_TEXTURE_PROPERTIES).
			CA_D2D1_RESOURCE_TEXTURE_PROPERTIES^ ConverterD2D1_RESOURCE_TEXTURE_PROPERTIESUnmanagedToManaged(D2D1_RESOURCE_TEXTURE_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RESOURCE_TEXTURE_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_RESOURCE_TEXTURE_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->extents = gcnew cli::array<UInt32>(Param_Estrutura->dimensions);
				EstruturaRetorno->dimensions = Param_Estrutura->dimensions;
				EstruturaRetorno->bufferPrecision = static_cast<CA_D2D1_BUFFER_PRECISION>(Param_Estrutura->bufferPrecision);
				EstruturaRetorno->channelDepth = static_cast<CA_D2D1_CHANNEL_DEPTH>(Param_Estrutura->channelDepth);
				EstruturaRetorno->filter = static_cast<CA_D2D1_FILTER>(Param_Estrutura->filter);
				EstruturaRetorno->extendModes = gcnew cli::array<CA_D2D1_EXTEND_MODE>(Param_Estrutura->dimensions);
				
				//Copia os dados para os arrays.
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->extents, const_cast<UINT32*>(Param_Estrutura->extents), EstruturaRetorno->dimensions);
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->extendModes, const_cast<D2D1_EXTEND_MODE*>(Param_Estrutura->extendModes), EstruturaRetorno->dimensions);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_INPUT_ELEMENT_DESC) para sua correspondencia não gerenciada(D2D1_INPUT_ELEMENT_DESC).
			D2D1_INPUT_ELEMENT_DESC* ConverterD2D1_INPUT_ELEMENT_DESCManagedToUnmanaged(CA_D2D1_INPUT_ELEMENT_DESC^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_INPUT_ELEMENT_DESC* EstruturaRetorno = CriarEstrutura<D2D1_INPUT_ELEMENT_DESC>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_INPUT_ELEMENT_DESC));

				//Define os dados.
				EstruturaRetorno->semanticName = ConverterStringToChar(Param_Estrutura->semanticName);
				EstruturaRetorno->semanticIndex = Param_Estrutura->semanticIndex;
				EstruturaRetorno->format = static_cast<DXGI_FORMAT>(Param_Estrutura->format);
				EstruturaRetorno->inputSlot = Param_Estrutura->inputSlot;
				EstruturaRetorno->alignedByteOffset = Param_Estrutura->alignedByteOffset;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_INPUT_ELEMENT_DESC) para sua correspondencia gerenciada(CA_D2D1_INPUT_ELEMENT_DESC).
			CA_D2D1_INPUT_ELEMENT_DESC^ ConverterD2D1_INPUT_ELEMENT_DESCUnmanagedToManaged(D2D1_INPUT_ELEMENT_DESC* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_INPUT_ELEMENT_DESC^ EstruturaRetorno = gcnew CA_D2D1_INPUT_ELEMENT_DESC();

				//Define os dados.
				EstruturaRetorno->semanticName = gcnew String(Param_Estrutura->semanticName);
				EstruturaRetorno->semanticIndex = Param_Estrutura->semanticIndex;
				EstruturaRetorno->format = static_cast<CA_DXGI_FORMAT>(Param_Estrutura->format);
				EstruturaRetorno->inputSlot = Param_Estrutura->inputSlot;
				EstruturaRetorno->alignedByteOffset = Param_Estrutura->alignedByteOffset;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_VERTEX_BUFFER_PROPERTIES) para sua correspondencia não gerenciada(D2D1_VERTEX_BUFFER_PROPERTIES).
			D2D1_VERTEX_BUFFER_PROPERTIES* ConverterD2D1_VERTEX_BUFFER_PROPERTIESManagedToUnmanaged(CA_D2D1_VERTEX_BUFFER_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_VERTEX_BUFFER_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_VERTEX_BUFFER_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_VERTEX_BUFFER_PROPERTIES));

				//Variaveis
				IntPtr pBufferDados = IntPtr::Zero;

				//Define os dados.
				EstruturaRetorno->inputCount = Param_Estrutura->inputCount;
				EstruturaRetorno->usage = static_cast<D2D1_VERTEX_USAGE>(Param_Estrutura->usage);
				EstruturaRetorno->byteWidth = Param_Estrutura->byteWidth;

				//Recupera o ponteiro para o buffer.
				static_cast<ICarenBuffer^>(Param_Estrutura->data)->GetInternalPointer(pBufferDados);

				//Define o ponteiro na estrutura.
				EstruturaRetorno->data = ConverterIntPtrTo<PBYTE>(pBufferDados);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_VERTEX_BUFFER_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_VERTEX_BUFFER_PROPERTIES).
			CA_D2D1_VERTEX_BUFFER_PROPERTIES^ ConverterD2D1_VERTEX_BUFFER_PROPERTIESUnmanagedToManaged(D2D1_VERTEX_BUFFER_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_VERTEX_BUFFER_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_VERTEX_BUFFER_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->inputCount = Param_Estrutura->inputCount;
				EstruturaRetorno->usage = static_cast<CA_D2D1_VERTEX_USAGE>(Param_Estrutura->usage);
				EstruturaRetorno->byteWidth = Param_Estrutura->byteWidth;
				EstruturaRetorno->data = gcnew CarenBuffer();

				//Define os dados no buffer.
				static_cast<ICarenBuffer^>(EstruturaRetorno->data)->CreateBuffer(IntPtr(const_cast<PBYTE>(Param_Estrutura->data)), false, EstruturaRetorno->byteWidth, EstruturaRetorno->byteWidth);
				
				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES) para sua correspondencia não gerenciada(D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES).
			D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES* ConverterD2D1_CUSTOM_VERTEX_BUFFER_PROPERTIESManagedToUnmanaged(CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES));

				//Variaveis
				D2D1_INPUT_ELEMENT_DESC* pMatrizElementos = CriarMatrizEstruturas<D2D1_INPUT_ELEMENT_DESC>(Param_Estrutura->elementCount);
				D2D1_INPUT_ELEMENT_DESC* pInputDescAuxiliar = NULL;

				//Define os dados.
				EstruturaRetorno->shaderBufferWithInputSignature = CriarMatrizUnidimensional<const BYTE>(static_cast<DWORD>(Param_Estrutura->shaderBufferSize));
				EstruturaRetorno->shaderBufferSize = Param_Estrutura->shaderBufferSize;
				EstruturaRetorno->inputElements = pMatrizElementos;
				EstruturaRetorno->elementCount = Param_Estrutura->elementCount;

				//Copia os dados para a matriz de shader
				CopiarItensTo_ArrayNativo(const_cast<BYTE**>(&EstruturaRetorno->shaderBufferWithInputSignature), Param_Estrutura->shaderBufferWithInputSignature, Param_Estrutura->shaderBufferSize);

				//Copia os dados para a matriz de descrição de elemento.
				for (UINT32 i = 0; i < Param_Estrutura->elementCount; i++)
				{
					//Converte a estrutura.
					pInputDescAuxiliar = ConverterD2D1_INPUT_ELEMENT_DESCManagedToUnmanaged(Param_Estrutura->inputElements[i]);

					//Define os dados na matriz nativa.
					pMatrizElementos[i] = *pInputDescAuxiliar;
					
					//Libera a memória.
					DeletarEstruturaSafe(&pInputDescAuxiliar);
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES).
			CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES^ ConverterD2D1_CUSTOM_VERTEX_BUFFER_PROPERTIESUnmanagedToManaged(D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->shaderBufferWithInputSignature = gcnew cli::array<Byte>(Param_Estrutura->shaderBufferSize);
				EstruturaRetorno->shaderBufferSize = Param_Estrutura->shaderBufferSize;
				EstruturaRetorno->inputElements = gcnew cli::array<CA_D2D1_INPUT_ELEMENT_DESC^>(Param_Estrutura->elementCount);
				EstruturaRetorno->elementCount = Param_Estrutura->elementCount;

				//Copia os dados para a matriz do shader.
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->shaderBufferWithInputSignature, const_cast<BYTE*>(Param_Estrutura->shaderBufferWithInputSignature), Param_Estrutura->shaderBufferSize);

				//Copia os dados para a matriz de descrição de elementos.
				for (UINT32 i = 0; i < Param_Estrutura->elementCount; i++)
				{
					//Converte e define no id especificado.
					EstruturaRetorno->inputElements[i] = ConverterD2D1_INPUT_ELEMENT_DESCUnmanagedToManaged(const_cast<D2D1_INPUT_ELEMENT_DESC*>(&Param_Estrutura->inputElements[i]));
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_SVG_LENGTH) para sua correspondencia não gerenciada(D2D1_SVG_LENGTH).
			D2D1_SVG_LENGTH* ConverterD2D1_SVG_LENGTHManagedToUnmanaged(CA_D2D1_SVG_LENGTH^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_SVG_LENGTH* EstruturaRetorno = CriarEstrutura<D2D1_SVG_LENGTH>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_SVG_LENGTH));

				//Define os dados.
				EstruturaRetorno->units = static_cast<D2D1_SVG_LENGTH_UNITS>(Param_Estrutura->units);
				EstruturaRetorno->value = Param_Estrutura->value;
				
				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_SVG_LENGTH) para sua correspondencia gerenciada(CA_D2D1_SVG_LENGTH).
			CA_D2D1_SVG_LENGTH^ ConverterD2D1_SVG_LENGTHUnmanagedToManaged(D2D1_SVG_LENGTH* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_SVG_LENGTH^ EstruturaRetorno = gcnew CA_D2D1_SVG_LENGTH();

				//Define os dados.
				EstruturaRetorno->units = static_cast<CA_D2D1_SVG_LENGTH_UNITS>(Param_Estrutura->units);
				EstruturaRetorno->value = Param_Estrutura->value;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_SVG_PRESERVE_ASPECT_RATIO) para sua correspondencia não gerenciada(D2D1_SVG_PRESERVE_ASPECT_RATIO).
			D2D1_SVG_PRESERVE_ASPECT_RATIO* ConverterD2D1_SVG_PRESERVE_ASPECT_RATIOManagedToUnmanaged(CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_SVG_PRESERVE_ASPECT_RATIO* EstruturaRetorno = CriarEstrutura<D2D1_SVG_PRESERVE_ASPECT_RATIO>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_SVG_PRESERVE_ASPECT_RATIO));

				//Define os dados.
				EstruturaRetorno->defer = Param_Estrutura->defer ? TRUE : FALSE;
				EstruturaRetorno->align = static_cast<D2D1_SVG_ASPECT_ALIGN>(Param_Estrutura->align);
				EstruturaRetorno->meetOrSlice = static_cast<D2D1_SVG_ASPECT_SCALING>(Param_Estrutura->meetOrSlice);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_SVG_PRESERVE_ASPECT_RATIO) para sua correspondencia gerenciada(CA_D2D1_SVG_PRESERVE_ASPECT_RATIO).
			CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ ConverterD2D1_SVG_PRESERVE_ASPECT_RATIOUnmanagedToManaged(D2D1_SVG_PRESERVE_ASPECT_RATIO* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ EstruturaRetorno = gcnew CA_D2D1_SVG_PRESERVE_ASPECT_RATIO();

				//Define os dados.
				EstruturaRetorno->defer = Param_Estrutura->defer ? true : false;
				EstruturaRetorno->align = static_cast<CA_D2D1_SVG_ASPECT_ALIGN>(Param_Estrutura->align);
				EstruturaRetorno->meetOrSlice = static_cast<CA_D2D1_SVG_ASPECT_SCALING>(Param_Estrutura->meetOrSlice);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_GRADIENT_STOP) para sua correspondencia não gerenciada(D2D1_GRADIENT_STOP).
			D2D1_GRADIENT_STOP* ConverterD2D1_GRADIENT_STOPManagedToUnmanaged(CA_D2D1_GRADIENT_STOP^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_GRADIENT_STOP* EstruturaRetorno = CriarEstrutura<D2D1_GRADIENT_STOP>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_GRADIENT_STOP));

				//Variaveis
				D2D1_COLOR_F* pColor = NULL;

				//Covnerte a estrutura de cor.
				pColor = ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Estrutura->color);

				//Define os dados.
				EstruturaRetorno->position = Param_Estrutura->position;
				EstruturaRetorno->color = *pColor;

				//Libera a memória para a estrutura
				DeletarEstruturaSafe(&pColor);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_GRADIENT_STOP) para sua correspondencia gerenciada(CA_D2D1_GRADIENT_STOP).
			CA_D2D1_GRADIENT_STOP^ ConverterD2D1_GRADIENT_STOPUnmanagedToManaged(D2D1_GRADIENT_STOP* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_GRADIENT_STOP^ EstruturaRetorno = gcnew CA_D2D1_GRADIENT_STOP();

				//Define os dados.
				EstruturaRetorno->position = Param_Estrutura->position;
				EstruturaRetorno->color = ConverterD2D1_COLOR_FUnmanagedToManaged(&Param_Estrutura->color);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_IMAGE_BRUSH_PROPERTIES) para sua correspondencia não gerenciada(D2D1_IMAGE_BRUSH_PROPERTIES).
			D2D1_IMAGE_BRUSH_PROPERTIES* ConverterD2D1_IMAGE_BRUSH_PROPERTIESManagedToUnmanaged(CA_D2D1_IMAGE_BRUSH_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_IMAGE_BRUSH_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_IMAGE_BRUSH_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_IMAGE_BRUSH_PROPERTIES));

				//Variaveis
				D2D1_RECT_F* pRect = NULL;

				//Covnerte a estrutura de cor.
				pRect = ConverterD2D1_RECT_FManagedToUnmanaged(Param_Estrutura->sourceRectangle);

				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);
				EstruturaRetorno->sourceRectangle = *pRect;
				
				//Libera a memória para a estrutura
				DeletarEstruturaSafe(&pRect);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_IMAGE_BRUSH_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_IMAGE_BRUSH_PROPERTIES).
			CA_D2D1_IMAGE_BRUSH_PROPERTIES^ ConverterD2D1_IMAGE_BRUSH_PROPERTIESUnmanagedToManaged(D2D1_IMAGE_BRUSH_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_IMAGE_BRUSH_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_IMAGE_BRUSH_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->extendModeX = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeX);
				EstruturaRetorno->extendModeY = static_cast<CA_D2D1_EXTEND_MODE>(Param_Estrutura->extendModeY);
				EstruturaRetorno->interpolationMode = static_cast<CA_D2D1_INTERPOLATION_MODE>(Param_Estrutura->interpolationMode);
				EstruturaRetorno->sourceRectangle = ConverterD2D1_RECT_FUnmanagedToManaged(&Param_Estrutura->sourceRectangle);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_EFFECT_INPUT_DESCRIPTION) para sua correspondencia não gerenciada(D2D1_EFFECT_INPUT_DESCRIPTION).
			D2D1_EFFECT_INPUT_DESCRIPTION* ConverterD2D1_EFFECT_INPUT_DESCRIPTIONManagedToUnmanaged(CA_D2D1_EFFECT_INPUT_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_EFFECT_INPUT_DESCRIPTION* EstruturaRetorno = CriarEstrutura<D2D1_EFFECT_INPUT_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_EFFECT_INPUT_DESCRIPTION));

				//Variaveis
				ID2D1Effect* pMyEfeito = NULL;
				D2D1_RECT_F* pInputRect = NULL;

				//Recupera o ponteiro para o efeito.
				static_cast<ICaren^>(Param_Estrutura->effect)->RecuperarPonteiro((LPVOID*)&pMyEfeito);

				//Converte a estrutura.
				pInputRect = ConverterD2D1_RECT_FManagedToUnmanaged(Param_Estrutura->inputRectangle);

				//Define os dados.
				EstruturaRetorno->effect = pMyEfeito;
				EstruturaRetorno->inputIndex = Param_Estrutura->inputIndex;
				EstruturaRetorno->inputRectangle = *pInputRect;

				//Libera a memória para a estrurua
				DeletarEstruturaSafe(&pInputRect);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_EFFECT_INPUT_DESCRIPTION) para sua correspondencia gerenciada(CA_D2D1_EFFECT_INPUT_DESCRIPTION).
			CA_D2D1_EFFECT_INPUT_DESCRIPTION^ ConverterD2D1_EFFECT_INPUT_DESCRIPTIONUnmanagedToManaged(D2D1_EFFECT_INPUT_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_EFFECT_INPUT_DESCRIPTION^ EstruturaRetorno = gcnew CA_D2D1_EFFECT_INPUT_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->effect = gcnew Caren();
				EstruturaRetorno->inputIndex = Param_Estrutura->inputIndex;
				EstruturaRetorno->inputRectangle = ConverterD2D1_RECT_FUnmanagedToManaged(&Param_Estrutura->inputRectangle);

				//Define o ponteiro do efeito na interface.
				static_cast<ICaren^>(EstruturaRetorno->effect)->AdicionarPonteiro(Param_Estrutura->effect);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_RENDERING_CONTROLS) para sua correspondencia não gerenciada(D2D1_RENDERING_CONTROLS).
			D2D1_RENDERING_CONTROLS* ConverterD2D1_RENDERING_CONTROLSManagedToUnmanaged(CA_D2D1_RENDERING_CONTROLS^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_RENDERING_CONTROLS* EstruturaRetorno = CriarEstrutura<D2D1_RENDERING_CONTROLS>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_RENDERING_CONTROLS));

				//Variaveis
				D2D1_SIZE_U* pSizeTile = NULL;

				//Converte a estrutura
				pSizeTile = ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Estrutura->tileSize);

				//Define os dados.
				EstruturaRetorno->bufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_Estrutura->bufferPrecision);
				EstruturaRetorno->tileSize = *pSizeTile;
				
				//Libera a memória para a estrutura.
				DeletarEstruturaSafe(&pSizeTile);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_RENDERING_CONTROLS) para sua correspondencia gerenciada(CA_D2D1_RENDERING_CONTROLS).
			CA_D2D1_RENDERING_CONTROLS^ ConverterD2D1_RENDERING_CONTROLSUnmanagedToManaged(D2D1_RENDERING_CONTROLS* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_RENDERING_CONTROLS^ EstruturaRetorno = gcnew CA_D2D1_RENDERING_CONTROLS();

				//Define os dados.
				EstruturaRetorno->bufferPrecision = static_cast<CA_D2D1_BUFFER_PRECISION>(Param_Estrutura->bufferPrecision);
				EstruturaRetorno->tileSize = ConverterD2D1_SIZE_UUnmanagedToManaged(&Param_Estrutura->tileSize);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_PRINT_CONTROL_PROPERTIES) para sua correspondencia não gerenciada(D2D1_PRINT_CONTROL_PROPERTIES).
			D2D1_PRINT_CONTROL_PROPERTIES* ConverterD2D1_PRINT_CONTROL_PROPERTIESManagedToUnmanaged(CA_D2D1_PRINT_CONTROL_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_PRINT_CONTROL_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_PRINT_CONTROL_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_PRINT_CONTROL_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->colorSpace = static_cast<D2D1_COLOR_SPACE>(Param_Estrutura->colorSpace);
				EstruturaRetorno->fontSubset = static_cast<D2D1_PRINT_FONT_SUBSET_MODE>(Param_Estrutura->fontSubset);
				EstruturaRetorno->rasterDPI = Param_Estrutura->rasterDPI;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_PRINT_CONTROL_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_PRINT_CONTROL_PROPERTIES).
			CA_D2D1_PRINT_CONTROL_PROPERTIES^ ConverterD2D1_PRINT_CONTROL_PROPERTIESUnmanagedToManaged(D2D1_PRINT_CONTROL_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_PRINT_CONTROL_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_PRINT_CONTROL_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->colorSpace = static_cast<CA_D2D1_COLOR_SPACE>(Param_Estrutura->colorSpace);
				EstruturaRetorno->fontSubset = static_cast<CA_D2D1_PRINT_FONT_SUBSET_MODE>(Param_Estrutura->fontSubset);
				EstruturaRetorno->rasterDPI = Param_Estrutura->rasterDPI;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_STROKE_STYLE_PROPERTIES) para sua correspondencia não gerenciada(D2D1_STROKE_STYLE_PROPERTIES).
			D2D1_STROKE_STYLE_PROPERTIES* ConverterD2D1_STROKE_STYLE_PROPERTIESManagedToUnmanaged(CA_D2D1_STROKE_STYLE_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_STROKE_STYLE_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_STROKE_STYLE_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_STROKE_STYLE_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->startCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->startCap);
				EstruturaRetorno->endCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->endCap);
				EstruturaRetorno->dashCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->dashCap);
				EstruturaRetorno->lineJoin = static_cast<D2D1_LINE_JOIN>(Param_Estrutura->lineJoin);
				EstruturaRetorno->miterLimit = Param_Estrutura->miterLimit;
				EstruturaRetorno->dashStyle = static_cast<D2D1_DASH_STYLE>(Param_Estrutura->dashStyle);
				EstruturaRetorno->dashOffset = Param_Estrutura->dashOffset;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_STROKE_STYLE_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_STROKE_STYLE_PROPERTIES).
			CA_D2D1_STROKE_STYLE_PROPERTIES^ ConverterD2D1_STROKE_STYLE_PROPERTIESUnmanagedToManaged(D2D1_STROKE_STYLE_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_STROKE_STYLE_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_STROKE_STYLE_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->startCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->startCap);
				EstruturaRetorno->endCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->endCap);
				EstruturaRetorno->dashCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->dashCap);
				EstruturaRetorno->lineJoin = static_cast<CA_D2D1_LINE_JOIN>(Param_Estrutura->lineJoin);
				EstruturaRetorno->miterLimit = Param_Estrutura->miterLimit;
				EstruturaRetorno->dashStyle = static_cast<CA_D2D1_DASH_STYLE>(Param_Estrutura->dashStyle);
				EstruturaRetorno->dashOffset = Param_Estrutura->dashOffset;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_STROKE_STYLE_PROPERTIES1) para sua correspondencia não gerenciada(D2D1_STROKE_STYLE_PROPERTIES1).
			D2D1_STROKE_STYLE_PROPERTIES1* ConverterD2D1_STROKE_STYLE_PROPERTIES1ManagedToUnmanaged(CA_D2D1_STROKE_STYLE_PROPERTIES1^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_STROKE_STYLE_PROPERTIES1* EstruturaRetorno = CriarEstrutura<D2D1_STROKE_STYLE_PROPERTIES1>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_STROKE_STYLE_PROPERTIES1));

				//Define os dados.
				EstruturaRetorno->startCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->startCap);
				EstruturaRetorno->endCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->endCap);
				EstruturaRetorno->dashCap = static_cast<D2D1_CAP_STYLE>(Param_Estrutura->dashCap);
				EstruturaRetorno->lineJoin = static_cast<D2D1_LINE_JOIN>(Param_Estrutura->lineJoin);
				EstruturaRetorno->miterLimit = Param_Estrutura->miterLimit;
				EstruturaRetorno->dashStyle = static_cast<D2D1_DASH_STYLE>(Param_Estrutura->dashStyle);
				EstruturaRetorno->dashOffset = Param_Estrutura->dashOffset;
				EstruturaRetorno->transformType = static_cast<D2D1_STROKE_TRANSFORM_TYPE>(Param_Estrutura->transformType);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_STROKE_STYLE_PROPERTIES1) para sua correspondencia gerenciada(CA_D2D1_STROKE_STYLE_PROPERTIES1).
			CA_D2D1_STROKE_STYLE_PROPERTIES1^ ConverterD2D1_STROKE_STYLE_PROPERTIES1UnmanagedToManaged(D2D1_STROKE_STYLE_PROPERTIES1* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_STROKE_STYLE_PROPERTIES1^ EstruturaRetorno = gcnew CA_D2D1_STROKE_STYLE_PROPERTIES1();

				//Define os dados.
				EstruturaRetorno->startCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->startCap);
				EstruturaRetorno->endCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->endCap);
				EstruturaRetorno->dashCap = static_cast<CA_D2D1_CAP_STYLE>(Param_Estrutura->dashCap);
				EstruturaRetorno->lineJoin = static_cast<CA_D2D1_LINE_JOIN>(Param_Estrutura->lineJoin);
				EstruturaRetorno->miterLimit = Param_Estrutura->miterLimit;
				EstruturaRetorno->dashStyle = static_cast<CA_D2D1_DASH_STYLE>(Param_Estrutura->dashStyle);
				EstruturaRetorno->dashOffset = Param_Estrutura->dashOffset;
				EstruturaRetorno->transformType = static_cast<CA_D2D1_STROKE_TRANSFORM_TYPE>(Param_Estrutura->transformType);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_PROPERTY_BINDING) para sua correspondencia não gerenciada(D2D1_PROPERTY_BINDING).
			D2D1_PROPERTY_BINDING* ConverterD2D1_PROPERTY_BINDINGManagedToUnmanaged(CA_D2D1_PROPERTY_BINDING^ Param_Estrutura, PD2D1_PROPERTY_SET_FUNCTION Param_SetFunc, PD2D1_PROPERTY_GET_FUNCTION Param_GetFunc)
			{
				//Estrutura a ser retornada.
				D2D1_PROPERTY_BINDING* EstruturaRetorno = CriarEstrutura<D2D1_PROPERTY_BINDING>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_PROPERTY_BINDING));

				//Define os dados.
				EstruturaRetorno->propertyName = ConverterStringToConstWCHAR(Param_Estrutura->propertyName);
				EstruturaRetorno->setFunction = Param_SetFunc;
				EstruturaRetorno->getFunction = Param_GetFunc;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_PROPERTY_BINDING) para sua correspondencia gerenciada(CA_D2D1_PROPERTY_BINDING).
			CA_D2D1_PROPERTY_BINDING^ ConverterD2D1_PROPERTY_BINDINGUnmanagedToManaged(D2D1_PROPERTY_BINDING* Param_Estrutura, Object^ Param_PropertyFuncs)
			{
				//Estrutura a ser retornada.
				CA_D2D1_PROPERTY_BINDING^ EstruturaRetorno = gcnew CA_D2D1_PROPERTY_BINDING();

				//Define os dados.
				EstruturaRetorno->propertyName = gcnew String(Param_Estrutura->propertyName);
				EstruturaRetorno->setFunction_and_getFunction = Param_PropertyFuncs;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_CREATION_PROPERTIES) para sua correspondencia não gerenciada(D2D1_CREATION_PROPERTIES).
			D2D1_CREATION_PROPERTIES* ConverterD2D1_CREATION_PROPERTIESManagedToUnmanaged(CA_D2D1_CREATION_PROPERTIES^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_CREATION_PROPERTIES* EstruturaRetorno = CriarEstrutura<D2D1_CREATION_PROPERTIES>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_CREATION_PROPERTIES));

				//Define os dados.
				EstruturaRetorno->debugLevel = static_cast<D2D1_DEBUG_LEVEL>(Param_Estrutura->debugLevel);
				EstruturaRetorno->options = static_cast<D2D1_DEVICE_CONTEXT_OPTIONS>(Param_Estrutura->options);
				EstruturaRetorno->threadingMode = static_cast<D2D1_THREADING_MODE>(Param_Estrutura->threadingMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_CREATION_PROPERTIES) para sua correspondencia gerenciada(CA_D2D1_CREATION_PROPERTIES).
			CA_D2D1_CREATION_PROPERTIES^ ConverterD2D1_CREATION_PROPERTIESUnmanagedToManaged(D2D1_CREATION_PROPERTIES* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_D2D1_CREATION_PROPERTIES^ EstruturaRetorno = gcnew CA_D2D1_CREATION_PROPERTIES();

				//Define os dados.
				EstruturaRetorno->debugLevel = static_cast<CA_D2D1_DEBUG_LEVEL>(Param_Estrutura->debugLevel);
				EstruturaRetorno->options = static_cast<CA_D2D1_DEVICE_CONTEXT_OPTIONS>(Param_Estrutura->options);
				EstruturaRetorno->threadingMode = static_cast<CA_D2D1_THREADING_MODE>(Param_Estrutura->threadingMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D2D1_FACTORY_OPTIONS) para sua correspondencia não gerenciada(D2D1_FACTORY_OPTIONS).
			D2D1_FACTORY_OPTIONS* ConverterD2D1_FACTORY_OPTIONSManagedToUnmanaged(CA_D2D1_FACTORY_OPTIONS^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				D2D1_FACTORY_OPTIONS* EstruturaRetorno = CriarEstrutura<D2D1_FACTORY_OPTIONS>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(D2D1_FACTORY_OPTIONS));

				//Define os dados.
				EstruturaRetorno->debugLevel = static_cast<D2D1_DEBUG_LEVEL>(Param_Estrutura->debugLevel);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(D2D1_FACTORY_OPTIONS) para sua correspondencia gerenciada(CA_D2D1_FACTORY_OPTIONS).
			CA_D2D1_FACTORY_OPTIONS^ ConverterD2D1_FACTORY_OPTIONSUnmanagedToManaged(D2D1_FACTORY_OPTIONS* Param_Estrutura, Object^ Param_PropertyFuncs)
			{
				//Estrutura a ser retornada.
				CA_D2D1_FACTORY_OPTIONS^ EstruturaRetorno = gcnew CA_D2D1_FACTORY_OPTIONS();

				//Define os dados.
				EstruturaRetorno->debugLevel = static_cast<CA_D2D1_DEBUG_LEVEL>(Param_Estrutura->debugLevel);

				//Retorna o resultado
				return EstruturaRetorno;
			}



			//DWRITE ESTRUTURAS


			//Converte uma estrutura gerenciada(CA_DWRITE_GLYPH_RUN) para sua correspondencia não gerenciada(DWRITE_GLYPH_RUN).
			DWRITE_GLYPH_RUN* ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(CA_DWRITE_GLYPH_RUN^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				DWRITE_GLYPH_RUN* EstruturaRetorno = CriarEstrutura<DWRITE_GLYPH_RUN>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(DWRITE_GLYPH_RUN));

				//Variaveis.
				IDWriteFontFace* pDwriteFontFace = NULL;
				UInt16* pMatrizIndices = CriarMatrizUnidimensional<UInt16>(Param_Estrutura->glyphCount);
				float* pMatrizGlyphAdvances = CriarMatrizUnidimensional<float>(Param_Estrutura->glyphCount);
				DWRITE_GLYPH_OFFSET* pMatrizGlyphOffset = CriarMatrizEstruturas<DWRITE_GLYPH_OFFSET>(Param_Estrutura->glyphCount);

				//Recupera o ponteiro para a interface.
				CarenResult Resultado = static_cast<ICaren^>(Param_Estrutura->fontFace)->RecuperarPonteiro((LPVOID*)&pDwriteFontFace);

				//Verifica se não falhou
				if (!CarenSucesso(Resultado))
				{
					//Chama uma exceção.
					throw gcnew NullReferenceException("O membro (fontFace) dentro da estrutura (CA_DWRITE_GLYPH_RUN) era NULO!");
				}

				//Copia os dados das matrizes simples.
				CopiarItensTo_ArrayNativo(&pMatrizIndices, Param_Estrutura->glyphIndices, Param_Estrutura->glyphCount);
				CopiarItensTo_ArrayNativo(&pMatrizGlyphAdvances, Param_Estrutura->glyphAdvances, Param_Estrutura->glyphCount);

				//Obtém os dados da matriz de estruturas.
				for (UInt32 i = 0; i < Param_Estrutura->glyphCount; i++)
				{
					//Inicializa a estrutura.
					ZeroMemory(&pMatrizGlyphOffset[i], sizeof(DWRITE_GLYPH_OFFSET));

					//Define os dados da estrutura.
					pMatrizGlyphOffset[i].advanceOffset = Param_Estrutura->glyphOffsets[i]->advanceOffset;
					pMatrizGlyphOffset[i].ascenderOffset = Param_Estrutura->glyphOffsets[i]->ascenderOffset;
				}

				//Define os dados.
				EstruturaRetorno->fontFace = pDwriteFontFace;
				EstruturaRetorno->fontEmSize = Param_Estrutura->fontEmSize;
				EstruturaRetorno->glyphCount = Param_Estrutura->glyphCount;
				EstruturaRetorno->glyphIndices = pMatrizIndices;
				EstruturaRetorno->glyphAdvances = pMatrizGlyphAdvances;
				EstruturaRetorno->glyphOffsets = pMatrizGlyphOffset;
				EstruturaRetorno->bidiLevel = Param_Estrutura->bidiLevel;
				EstruturaRetorno->isSideways = Param_Estrutura->isSideways ? TRUE : FALSE;

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//Converte uma estrutura não gerenciada(DWRITE_GLYPH_RUN) para sua correspondencia gerenciada(CA_DWRITE_GLYPH_RUN).
			CA_DWRITE_GLYPH_RUN^ ConverterDWRITE_GLYPH_RUNUnmanagedToManaged(DWRITE_GLYPH_RUN* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_DWRITE_GLYPH_RUN^ EstruturaRetorno = gcnew CA_DWRITE_GLYPH_RUN();

				//Variaveis.
				EstruturaRetorno->fontFace = gcnew Caren();
				EstruturaRetorno->glyphIndices = gcnew cli::array<UInt16>(Param_Estrutura->glyphCount);
				EstruturaRetorno->glyphAdvances = gcnew cli::array<float>(Param_Estrutura->glyphCount);
				EstruturaRetorno->glyphOffsets = gcnew cli::array<CA_DWRITE_GLYPH_OFFSET^>(Param_Estrutura->glyphCount);

				//Define o ponteiro.
				CarenResult Resultado = static_cast<ICaren^>(EstruturaRetorno->fontFace)->AdicionarPonteiro(Param_Estrutura->fontFace);

				//Copia os dados das matrizes simples.
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->glyphIndices, Param_Estrutura->glyphIndices, Param_Estrutura->glyphCount);
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->glyphAdvances, Param_Estrutura->glyphAdvances, Param_Estrutura->glyphCount);

				//Obtém os dados da matriz de estruturas.
				for (UInt32 i = 0; i < Param_Estrutura->glyphCount; i++)
				{
					//Inicializa a estrutura.
					EstruturaRetorno->glyphOffsets[i] = gcnew CA_DWRITE_GLYPH_OFFSET();

					//Define os dados da estrutura.
					EstruturaRetorno->glyphOffsets[i]->advanceOffset = Param_Estrutura->glyphOffsets[i].advanceOffset;
					EstruturaRetorno->glyphOffsets[i]->ascenderOffset = Param_Estrutura->glyphOffsets[i].ascenderOffset;
				}

				//Define os dados restantes
				EstruturaRetorno->fontEmSize = Param_Estrutura->fontEmSize;
				EstruturaRetorno->glyphCount = Param_Estrutura->glyphCount;
				EstruturaRetorno->bidiLevel = Param_Estrutura->bidiLevel;
				EstruturaRetorno->isSideways = Param_Estrutura->isSideways ? true : false;

				//Retorna o resultado
				return EstruturaRetorno;
			}



			//(VERIFICAR O ARRAY CLUSTERMAP)Converte uma estrutura gerenciada(CA_DWRITE_GLYPH_RUN_DESCRIPTION) para sua correspondencia não gerenciada(DWRITE_GLYPH_RUN_DESCRIPTION).
			DWRITE_GLYPH_RUN_DESCRIPTION* ConverterDWRITE_GLYPH_RUN_DESCRIPTIONManagedToUnmanaged(CA_DWRITE_GLYPH_RUN_DESCRIPTION^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				DWRITE_GLYPH_RUN_DESCRIPTION* EstruturaRetorno = CriarEstrutura<DWRITE_GLYPH_RUN_DESCRIPTION>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(DWRITE_GLYPH_RUN_DESCRIPTION));

				//Define os dados.
				EstruturaRetorno->localeName = ObjetoGerenciadoValido(Param_Estrutura->localeName) ? ConverterStringToConstWCHAR(Param_Estrutura->localeName) : NULL;
				EstruturaRetorno->string = ObjetoGerenciadoValido(Param_Estrutura->string) ? ConverterStringToConstWCHAR(Param_Estrutura->string) : NULL;
				EstruturaRetorno->stringLength = Param_Estrutura->stringLength;
				EstruturaRetorno->textPosition = Param_Estrutura->textPosition;
				
				//Cria o array
				EstruturaRetorno->clusterMap = CriarMatrizUnidimensional<UINT16>(Param_Estrutura->stringLength); //VERIFIQUE A QUANTIDADE DE DADOS REAIS NO ARRAY.
				
				//Define os dados no array
				CopiarItensTo_ArrayNativo(const_cast<UINT16**>(&EstruturaRetorno->clusterMap), Param_Estrutura->clusterMap, Param_Estrutura->clusterMap->Length);

				//Retorna o resultado
				return EstruturaRetorno;
			}
			//(VERIFICAR O ARRAY CLUSTERMAP)Converte uma estrutura não gerenciada(DWRITE_GLYPH_RUN_DESCRIPTION) para sua correspondencia gerenciada(CA_DWRITE_GLYPH_RUN_DESCRIPTION).
			CA_DWRITE_GLYPH_RUN_DESCRIPTION^ ConverterDWRITE_GLYPH_RUN_DESCRIPTIONUnmanagedToManaged(DWRITE_GLYPH_RUN_DESCRIPTION* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_DWRITE_GLYPH_RUN_DESCRIPTION^ EstruturaRetorno = gcnew CA_DWRITE_GLYPH_RUN_DESCRIPTION();

				//Define os dados.
				EstruturaRetorno->localeName = ObjetoValido(Param_Estrutura->localeName) ? gcnew String(Param_Estrutura->localeName) : nullptr;
				EstruturaRetorno->string = ObjetoValido(Param_Estrutura->string) ? gcnew String(Param_Estrutura->string): nullptr;
				EstruturaRetorno->stringLength = Param_Estrutura->stringLength;
				EstruturaRetorno->textPosition = Param_Estrutura->textPosition;
				
				//Cria o array
				EstruturaRetorno->clusterMap = gcnew cli::array<UInt16>(Param_Estrutura->stringLength); //VERIFIQUE A QUANTIDADE DE DADOS REAIS NO ARRAY.

				//Define os dados no array
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->clusterMap, Param_Estrutura->clusterMap, Param_Estrutura->stringLength);
				
				//Retorna o resultado
				return EstruturaRetorno;
			}






			//D3D11 ESTRUTURAS
			

			//Converte uma estrutura não gerenciada(D3D11_BUFFER_DESC) para sua correspondencia gerenciada(CA_D3D11_BUFFER_DESC).
			CA_D3D11_BUFFER_DESC^ ConverterD3D11_BUFFER_DESCUnamaged_ToManaged(D3D11_BUFFER_DESC* Param_pBufferDesc)
			{
				//Variavel que vai ser retornada.
				CA_D3D11_BUFFER_DESC^ BufferDescManaged = gcnew CA_D3D11_BUFFER_DESC();

				//Define os valores na estrutura gerenciada.
				BufferDescManaged->TamanhoElementosEstruturaBufferStride = Param_pBufferDesc->StructureByteStride;
				BufferDescManaged->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>((UINT)Param_pBufferDesc->BindFlags);
				BufferDescManaged->CpuAcessoFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>((UINT)Param_pBufferDesc->CPUAccessFlags);
				BufferDescManaged->DescBufferUse = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>((UINT)Param_pBufferDesc->Usage);
				BufferDescManaged->MiscFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_RESOURCE_MISC_FLAG>((UINT)Param_pBufferDesc->MiscFlags);
				BufferDescManaged->TamanhoBuffer = Param_pBufferDesc->ByteWidth;

				//Retorna a estrutura
				return BufferDescManaged;
			}

			//Converte uma estrutura gerenciada(CA_D3D11_BUFFER_DESC) para sua correspondencia não gerenciada(D3D11_BUFFER_DESC).
			D3D11_BUFFER_DESC* ConverterD3D11_BUFFER_DESCManaged_ToUnmanaged(CA_D3D11_BUFFER_DESC^ Param_BufferDesc)
			{
				//Variavel que vai ser retornada.
				D3D11_BUFFER_DESC* EstruturaRetorno = new D3D11_BUFFER_DESC();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados na estrutura nativa.
				EstruturaRetorno->StructureByteStride = static_cast<UINT>(Param_BufferDesc->TamanhoElementosEstruturaBufferStride);
				EstruturaRetorno->ByteWidth = static_cast<UINT>(Param_BufferDesc->TamanhoBuffer);
				EstruturaRetorno->BindFlags = static_cast<D3D11_BIND_FLAG>(Param_BufferDesc->BindFlags);
				EstruturaRetorno->CPUAccessFlags = static_cast<D3D11_CPU_ACCESS_FLAG>(Param_BufferDesc->CpuAcessoFlags);
				EstruturaRetorno->Usage = static_cast<D3D11_USAGE>(Param_BufferDesc->DescBufferUse);
				EstruturaRetorno->MiscFlags = static_cast<D3D11_RESOURCE_MISC_FLAG>(Param_BufferDesc->MiscFlags);

				//Retorna o ponteiro.
				return EstruturaRetorno;
			}


			//Converte uma estrutura não gerenciada(D3D11_SUBRESOURCE_DATA) para sua correspondencia gerenciada(CA_D3D11_SUBRESOURCE_DATA).
			CA_D3D11_SUBRESOURCE_DATA^ ConverterD3D11_SUBRESOURCE_DATAUnamaged_ToManaged(D3D11_SUBRESOURCE_DATA* Param_Estrutura, ICaren^% Param_ArmazemInitData)
			{
				//Variavel que vai ser retornada.
				CA_D3D11_SUBRESOURCE_DATA^ EstruturaDestino = gcnew CA_D3D11_SUBRESOURCE_DATA();

				//Ponteiro para os dados iniciais.
				PVOID InitData = NULL;

				//Define os valores na estrutura gerenciada.
				EstruturaDestino->StrideMemoria = Param_Estrutura->SysMemPitch;
				EstruturaDestino->StrideProfundidadeMemoria = Param_Estrutura->SysMemSlicePitch;

				//Verifica se contém dados inicais
				if (ObjetoValido(Param_Estrutura->pSysMem))
				{
					//Contém dados inciais.

					//Define os dados na interface fornecida.
					Param_ArmazemInitData->AdicionarPonteiro(const_cast<void*>(Param_Estrutura->pSysMem));

					//Define a interface na estrutura.
					EstruturaDestino->SysMemoria = Param_ArmazemInitData;
				}

				//Retorna a estrutura
				return EstruturaDestino;
			}

			//Converte uma estrutura gerenciada(CA_D3D11_SUBRESOURCE_DATA) para sua correspondencia não gerenciada(D3D11_SUBRESOURCE_DATA).
			D3D11_SUBRESOURCE_DATA* ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(CA_D3D11_SUBRESOURCE_DATA^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				D3D11_SUBRESOURCE_DATA* EstruturaDestino = new D3D11_SUBRESOURCE_DATA();

				//Variavel que vai conter os dados iniciais se houver.
				PVOID InitData = NULL;

				//Define os dados na estrutura nativa.
				EstruturaDestino->SysMemPitch = Param_Estrutura->StrideMemoria;
				EstruturaDestino->SysMemSlicePitch = Param_Estrutura->StrideProfundidadeMemoria;

				//Verifica se tem dados iniciais.
				if (Param_Estrutura->SysMemoria != nullptr)
				{
					//Contém dados inicias.

					//Obtém o ponteiro (Void*) para os dados.
					static_cast<ICaren^>(Param_Estrutura->SysMemoria)->RecuperarPonteiro(&InitData);

					//Define o ponteiro no parametro
					EstruturaDestino->pSysMem = InitData;
				}

				//Retorna o ponteiro.
				return EstruturaDestino;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_BLEND_DESC) para sua correspondencia não gerenciada(D3D11_BLEND_DESC).
			D3D11_BLEND_DESC* ConverterD3D11_BLEND_DESCManaged_ToUnManaged(CA_D3D11_BLEND_DESC^ Param_BlendDesc)
			{
				//Variavel a ser retornada.
				D3D11_BLEND_DESC* pNativeBlendDesc = CriarEstrutura<D3D11_BLEND_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeBlendDesc, sizeof(pNativeBlendDesc));

				//Variaveis utilizadas no método.
				int CountItemsRenderTarget = 0;

				//Preenche a estrutura principal.
				pNativeBlendDesc->AlphaToCoverageEnable = Param_BlendDesc->HabilitarAlphaCobertura ? TRUE : FALSE;
				pNativeBlendDesc->IndependentBlendEnable = Param_BlendDesc->BlendIndependente ? TRUE : FALSE;

				//Preenche a estrutura secundaria

				//Obtém a quantidade de itens no RenderTarget
				CountItemsRenderTarget = Param_BlendDesc->RenderTarget->Length;

				//Faz um laço para criar e preencher cada estrutura no array.
				for (int i = 0; i < CountItemsRenderTarget; i++)
				{
					//Cria a estrutura.
					D3D11_RENDER_TARGET_BLEND_DESC BlendDesc = {};

					//Preenche a estrutura.
					BlendDesc.BlendEnable = Param_BlendDesc->RenderTarget[i]->HabilitarMistura ? TRUE : FALSE;
					BlendDesc.BlendOp = static_cast<D3D11_BLEND_OP>(Param_BlendDesc->RenderTarget[i]->DefMisturasOp);
					BlendDesc.BlendOpAlpha = static_cast<D3D11_BLEND_OP>(Param_BlendDesc->RenderTarget[i]->DefMisturasOpAlfa);
					BlendDesc.DestBlend = static_cast<D3D11_BLEND>(Param_BlendDesc->RenderTarget[i]->MisturaDestino);
					BlendDesc.DestBlendAlpha = static_cast<D3D11_BLEND>(Param_BlendDesc->RenderTarget[i]->DestinoOperaçõesMisturaAtualAlfa);
					BlendDesc.RenderTargetWriteMask = Param_BlendDesc->RenderTarget[i]->MascaraGravação;
					BlendDesc.SrcBlend = static_cast<D3D11_BLEND>(Param_BlendDesc->RenderTarget[i]->MisturaOrigem);
					BlendDesc.SrcBlendAlpha = static_cast<D3D11_BLEND>(Param_BlendDesc->RenderTarget[i]->OrigemOperaçõesMisturaValorAlfa);

					//Define na estrutura nativa.
					pNativeBlendDesc->RenderTarget[i] = BlendDesc;
				}

				//Retorna a estrutura.
				return pNativeBlendDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_BLEND_DESC) para sua correspondencia gerenciada(CA_D3D11_BLEND_DESC).
			CA_D3D11_BLEND_DESC^ ConverterD3D11_BLEND_DESCUnManaged_ToManaged(D3D11_BLEND_DESC* Param_pBlendDescNative)
			{
				//Variavel a ser retornada.
				CA_D3D11_BLEND_DESC^ BlendDescManaged = gcnew CA_D3D11_BLEND_DESC();

				//Cria a estrutura Secundaria com um maximo de 8 entradas(0 - 7) validas.
				BlendDescManaged->RenderTarget = gcnew cli::array<CA_D3D11_RENDER_TARGET_BLEND_DESC^>(8);


				//Preenche os dados da estrutura principal
				BlendDescManaged->BlendIndependente = Param_pBlendDescNative->IndependentBlendEnable ? true : false;
				BlendDescManaged->HabilitarAlphaCobertura = Param_pBlendDescNative->AlphaToCoverageEnable ? true : false;

				//Preenche os dados da estrutura secundaria
				//A estrutura secundaria contém 8 Entradas Maximas(0 - 7).

				//Faz um for para criar e definir a estrutura no array.
				for (int i = 0; i < 8; i++)
				{
					//Cria a estrutura no id especificado.
					BlendDescManaged->RenderTarget[i] = gcnew CA_D3D11_RENDER_TARGET_BLEND_DESC();


					//Define os dados na estrutura.
					BlendDescManaged->RenderTarget[i]->HabilitarMistura = Param_pBlendDescNative->RenderTarget[i].BlendEnable ? true : false;
					BlendDescManaged->RenderTarget[i]->MisturaOrigem = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_pBlendDescNative->RenderTarget[i].SrcBlend);
					BlendDescManaged->RenderTarget[i]->MisturaDestino = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_pBlendDescNative->RenderTarget[i].DestBlend);
					BlendDescManaged->RenderTarget[i]->DefMisturasOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND_OP>((int)Param_pBlendDescNative->RenderTarget[i].BlendOp);
					BlendDescManaged->RenderTarget[i]->DefMisturasOpAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND_OP>((int)Param_pBlendDescNative->RenderTarget[i].BlendOpAlpha);
					BlendDescManaged->RenderTarget[i]->DestinoOperaçõesMisturaAtualAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_pBlendDescNative->RenderTarget[i].DestBlendAlpha);
					BlendDescManaged->RenderTarget[i]->OrigemOperaçõesMisturaValorAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_pBlendDescNative->RenderTarget[i].SrcBlendAlpha);
					BlendDescManaged->RenderTarget[i]->MascaraGravação = Param_pBlendDescNative->RenderTarget[i].RenderTargetWriteMask;
				}


				//Retorna a estrutura.
				return BlendDescManaged;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_BLEND_DESC1) para sua correspondencia não gerenciada(D3D11_BLEND_DESC1).
			D3D11_BLEND_DESC1* ConverterD3D11_BLEND_DESC1Managed_ToUnManaged(CA_D3D11_BLEND_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_BLEND_DESC1* EstruturaRetornada = CriarEstrutura<D3D11_BLEND_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetornada, sizeof(EstruturaRetornada));

				//Variaveis utilizadas no método.
				int CountItemsRenderTarget = 0;

				//Preenche a estrutura principal.
				EstruturaRetornada->AlphaToCoverageEnable = Param_Estrutura->HabilitarAlphaCobertura ? TRUE : FALSE;
				EstruturaRetornada->IndependentBlendEnable = Param_Estrutura->BlendIndependente ? TRUE : FALSE;

				//Preenche a estrutura secundaria

				//Obtém a quantidade de itens no RenderTarget
				CountItemsRenderTarget = Param_Estrutura->RenderTarget->Length;

				//Faz um laço para criar e preencher cada estrutura no array.
				for (int i = 0; i < CountItemsRenderTarget; i++)
				{
					//Cria a estrutura.
					D3D11_RENDER_TARGET_BLEND_DESC1 BlendDesc = {};

					//Preenche a estrutura.
					BlendDesc.BlendEnable = Param_Estrutura->RenderTarget[i]->HabilitarMistura ? TRUE : FALSE;
					BlendDesc.LogicOpEnable = Param_Estrutura->RenderTarget[i]->HabilitarOperacaoLogica ? TRUE : FALSE;
					BlendDesc.BlendOp = static_cast<D3D11_BLEND_OP>(Param_Estrutura->RenderTarget[i]->DefMisturasOp);
					BlendDesc.BlendOpAlpha = static_cast<D3D11_BLEND_OP>(Param_Estrutura->RenderTarget[i]->DefMisturasOpAlfa);
					BlendDesc.DestBlend = static_cast<D3D11_BLEND>(Param_Estrutura->RenderTarget[i]->MisturaDestino);
					BlendDesc.DestBlendAlpha = static_cast<D3D11_BLEND>(Param_Estrutura->RenderTarget[i]->DestinoOperaçõesMisturaAtualAlfa);
					BlendDesc.RenderTargetWriteMask = Param_Estrutura->RenderTarget[i]->MascaraGravação;
					BlendDesc.SrcBlend = static_cast<D3D11_BLEND>(Param_Estrutura->RenderTarget[i]->MisturaOrigem);
					BlendDesc.SrcBlendAlpha = static_cast<D3D11_BLEND>(Param_Estrutura->RenderTarget[i]->OrigemOperaçõesMisturaValorAlfa);
					BlendDesc.LogicOp = static_cast<D3D11_LOGIC_OP>(Param_Estrutura->RenderTarget[i]->OpLogica);

					//Define na estrutura nativa.
					EstruturaRetornada->RenderTarget[i] = BlendDesc;
				}

				//Retorna a estrutura.
				return EstruturaRetornada;
			}

			//Converte uma estrutura não gerenciada(D3D11_BLEND_DESC1) para sua correspondencia gerenciada(CA_D3D11_BLEND_DESC1).
			CA_D3D11_BLEND_DESC1^ ConverterD3D11_BLEND_DESC1UnManaged_ToManaged(D3D11_BLEND_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_BLEND_DESC1^ EstruturaRetorno = gcnew CA_D3D11_BLEND_DESC1();

				//Cria a estrutura Secundaria com um maximo de 8 entradas(0 - 7) validas.
				EstruturaRetorno->RenderTarget = gcnew cli::array<CA_D3D11_RENDER_TARGET_BLEND_DESC1^>(8);


				//Preenche os dados da estrutura principal
				EstruturaRetorno->BlendIndependente = Param_Estrutura->IndependentBlendEnable ? true : false;
				EstruturaRetorno->HabilitarAlphaCobertura = Param_Estrutura->AlphaToCoverageEnable ? true : false;

				//Preenche os dados da estrutura secundaria
				//A estrutura secundaria contém 8 Entradas Maximas(0 - 7).

				//Faz um for para criar e definir a estrutura no array.
				for (int i = 0; i < 8; i++)
				{
					//Cria a estrutura no id especificado.
					EstruturaRetorno->RenderTarget[i] = gcnew CA_D3D11_RENDER_TARGET_BLEND_DESC1();


					//Define os dados na estrutura.
					EstruturaRetorno->RenderTarget[i]->HabilitarMistura = Param_Estrutura->RenderTarget[i].BlendEnable ? true : false;
					EstruturaRetorno->RenderTarget[i]->HabilitarOperacaoLogica = Param_Estrutura->RenderTarget[i].LogicOpEnable ? true : false;
					EstruturaRetorno->RenderTarget[i]->MisturaOrigem = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_Estrutura->RenderTarget[i].SrcBlend);
					EstruturaRetorno->RenderTarget[i]->MisturaDestino = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_Estrutura->RenderTarget[i].DestBlend);
					EstruturaRetorno->RenderTarget[i]->DefMisturasOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND_OP>((int)Param_Estrutura->RenderTarget[i].BlendOp);
					EstruturaRetorno->RenderTarget[i]->DefMisturasOpAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND_OP>((int)Param_Estrutura->RenderTarget[i].BlendOpAlpha);
					EstruturaRetorno->RenderTarget[i]->DestinoOperaçõesMisturaAtualAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_Estrutura->RenderTarget[i].DestBlendAlpha);
					EstruturaRetorno->RenderTarget[i]->OrigemOperaçõesMisturaValorAlfa = static_cast<SDKBase::Enumeracoes::CA_D3D11_BLEND>((int)Param_Estrutura->RenderTarget[i].SrcBlendAlpha);
					EstruturaRetorno->RenderTarget[i]->OpLogica = static_cast<CA_D3D11_LOGIC_OP>(Param_Estrutura->RenderTarget[i].LogicOp);
					EstruturaRetorno->RenderTarget[i]->MascaraGravação = Param_Estrutura->RenderTarget[i].RenderTargetWriteMask;
				}


				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_CLASS_INSTANCE_DESC) para sua correspondencia não gerenciada(D3D11_CLASS_INSTANCE_DESC).
			D3D11_CLASS_INSTANCE_DESC* ConverterD3D11_CLASS_INSTANCE_DESCManaged_ToUnManaged(CA_D3D11_CLASS_INSTANCE_DESC^ Param_DescInstanceClasse)
			{
				//Varivel que vai ser retornada.
				D3D11_CLASS_INSTANCE_DESC* pNativeDescInstance = CriarEstrutura<D3D11_CLASS_INSTANCE_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDescInstance, sizeof(pNativeDescInstance));

				//Preenche os dados da estrutura gerenciada.
				pNativeDescInstance->BaseConstantBufferOffset = Param_DescInstanceClasse->DeslocamentoBaseBufferConstante;
				pNativeDescInstance->BaseSampler = Param_DescInstanceClasse->AmostradorBase;
				pNativeDescInstance->BaseTexture = Param_DescInstanceClasse->TexturaBase;
				pNativeDescInstance->ConstantBuffer = Param_DescInstanceClasse->BufferConstante;
				pNativeDescInstance->Created = Param_DescInstanceClasse->Criado ? TRUE : FALSE;
				pNativeDescInstance->InstanceId = Param_DescInstanceClasse->IDInstancia;
				pNativeDescInstance->InstanceIndex = Param_DescInstanceClasse->IndiceInstancia;
				pNativeDescInstance->TypeId = Param_DescInstanceClasse->TipoID;

				//Retorna o resultado
				return pNativeDescInstance;
			}

			//Converte uma estrutura não gerenciada(D3D11_CLASS_INSTANCE_DESC) para sua correspondencia gerenciada(CA_D3D11_CLASS_INSTANCE_DESC).
			CA_D3D11_CLASS_INSTANCE_DESC^ ConverterD3D11_CLASS_INSTANCE_DESCUnManaged_ToManaged(D3D11_CLASS_INSTANCE_DESC* Param_pNativeDescInstance)
			{
				//Variavel a ser retornada.
				CA_D3D11_CLASS_INSTANCE_DESC^ DesInstanciaClasse = gcnew CA_D3D11_CLASS_INSTANCE_DESC();

				//Preenche os dados da estrutura.
				DesInstanciaClasse->DeslocamentoBaseBufferConstante = Param_pNativeDescInstance->BaseConstantBufferOffset;
				DesInstanciaClasse->AmostradorBase = Param_pNativeDescInstance->BaseSampler;
				DesInstanciaClasse->TexturaBase = Param_pNativeDescInstance->BaseTexture;
				DesInstanciaClasse->BufferConstante = Param_pNativeDescInstance->ConstantBuffer;
				DesInstanciaClasse->Criado = Param_pNativeDescInstance->Created ? true : false;
				DesInstanciaClasse->IDInstancia = Param_pNativeDescInstance->InstanceId;
				DesInstanciaClasse->IndiceInstancia = Param_pNativeDescInstance->InstanceIndex;
				DesInstanciaClasse->TipoID = Param_pNativeDescInstance->TypeId;

				//Retorna a estrutura.
				return DesInstanciaClasse;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_QUERY_DESC) para sua correspondencia não gerenciada(D3D11_QUERY_DESC).
			D3D11_QUERY_DESC* ConverterD3D11_QUERY_DESCManaged_ToUnManaged(CA_D3D11_QUERY_DESC^ Param_DescQuery)
			{
				//Variavel a ser retornada.
				D3D11_QUERY_DESC* EstruturaRetorno = CriarEstrutura<D3D11_QUERY_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->MiscFlags = Param_DescQuery->MiscFlags;
				EstruturaRetorno->Query = static_cast<D3D11_QUERY>(Param_DescQuery->Query);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_QUERY_DESC) para sua correspondencia gerenciada(CA_D3D11_QUERY_DESC).
			CA_D3D11_QUERY_DESC^ ConverterD3D11_QUERY_DESCUnManaged_ToManaged(D3D11_QUERY_DESC* Param_NativeDescQuery)
			{
				//Variavel a ser retornada.
				CA_D3D11_QUERY_DESC^ ManagedDesc = gcnew CA_D3D11_QUERY_DESC();

				//Preenche os dados da estrutura.
				ManagedDesc->MiscFlags = Param_NativeDescQuery->MiscFlags;
				ManagedDesc->Query = static_cast<SDKBase::Enumeracoes::CA_D3D11_QUERY>(UINT(Param_NativeDescQuery->Query));

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_QUERY_DESC1) para sua correspondencia não gerenciada(D3D11_QUERY_DESC1).
			D3D11_QUERY_DESC1* ConverterD3D11_QUERY_DESC1Managed_ToUnManaged(CA_D3D11_QUERY_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_QUERY_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_QUERY_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->MiscFlags = Param_Estrutura->MiscFlags;
				EstruturaRetorno->Query = static_cast<D3D11_QUERY>(Param_Estrutura->Query);
				EstruturaRetorno->ContextType = static_cast<D3D11_CONTEXT_TYPE>(Param_Estrutura->ContextType);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_QUERY_DESC1) para sua correspondencia gerenciada(CA_D3D11_QUERY_DESC1).
			CA_D3D11_QUERY_DESC1^ ConverterD3D11_QUERY_DESC1UnManaged_ToManaged(D3D11_QUERY_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_QUERY_DESC1^ EstruturaRetorno = gcnew CA_D3D11_QUERY_DESC1();

				//Preenche os dados da estrutura.
				EstruturaRetorno->MiscFlags = Param_Estrutura->MiscFlags;
				EstruturaRetorno->Query = static_cast<SDKBase::Enumeracoes::CA_D3D11_QUERY>(UINT(Param_Estrutura->Query));
				EstruturaRetorno->ContextType = static_cast<CA_D3D11_CONTEXT_TYPE>(Param_Estrutura->ContextType);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_DEPTH_STENCIL_DESC) para sua correspondencia não gerenciada(D3D11_DEPTH_STENCIL_DESC).
			D3D11_DEPTH_STENCIL_DESC* ConverterD3D11_DEPTH_STENCIL_DESCManaged_ToUnManaged(CA_D3D11_DEPTH_STENCIL_DESC^ Param_DescStencil)
			{
				//Variavel a ser retornada.
				D3D11_DEPTH_STENCIL_DESC* pNativeDesc = CriarEstrutura<D3D11_DEPTH_STENCIL_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				pNativeDesc->DepthEnable = Param_DescStencil->HabilitarDepth ? TRUE : FALSE;
				pNativeDesc->DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(Param_DescStencil->DepthWriterMask);
				pNativeDesc->DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(Param_DescStencil->DepthFunc);
				pNativeDesc->StencilEnable = Param_DescStencil->HabilitarStencil ? TRUE : FALSE;
				pNativeDesc->StencilReadMask = Param_DescStencil->StencilReadMask;
				pNativeDesc->StencilWriteMask = Param_DescStencil->StencilWriteMask;


				//Define os dados das estrutura secundarias.

				//Inicializa as estruturas.
				pNativeDesc->FrontFace = {};
				pNativeDesc->BackFace = {};

				//Preenche os dados de cada estrutura.
				pNativeDesc->FrontFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->FrontFace->StencilDepthFailOp);
				pNativeDesc->FrontFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->FrontFace->StencilFailOp);
				pNativeDesc->FrontFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->FrontFace->StencilPassOp);
				pNativeDesc->FrontFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(Param_DescStencil->FrontFace->StencilFunc);

				pNativeDesc->BackFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->BackFace->StencilDepthFailOp);
				pNativeDesc->BackFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->BackFace->StencilFailOp);
				pNativeDesc->BackFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(Param_DescStencil->BackFace->StencilPassOp);
				pNativeDesc->BackFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(Param_DescStencil->BackFace->StencilFunc);


				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(CA_D3D11_DEPTH_STENCIL_DESC) para sua correspondencia gerenciada(CA_D3D11_DEPTH_STENCIL_DESC).
			CA_D3D11_DEPTH_STENCIL_DESC^ ConverterD3D11_DEPTH_STENCIL_DESCUnManaged_ToManaged(D3D11_DEPTH_STENCIL_DESC* Param_NativeDescStencil)
			{
				//Variavel a ser retornada.
				CA_D3D11_DEPTH_STENCIL_DESC^ ManagedDesc = gcnew CA_D3D11_DEPTH_STENCIL_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->HabilitarDepth = Param_NativeDescStencil->DepthEnable ? true : false;
				ManagedDesc->DepthWriterMask = static_cast<SDKBase::Enumeracoes::CA_D3D11_DEPTH_WRITE_MASK>(Param_NativeDescStencil->DepthWriteMask);
				ManagedDesc->DepthFunc = static_cast<SDKBase::Enumeracoes::CA_D3D11_COMPARISON_FUNC>(Param_NativeDescStencil->DepthFunc);
				ManagedDesc->HabilitarStencil = Param_NativeDescStencil->StencilEnable ? true : false;
				ManagedDesc->StencilReadMask = Param_NativeDescStencil->StencilReadMask;
				ManagedDesc->StencilWriteMask = Param_NativeDescStencil->StencilWriteMask;

				//Define os dados das estrutura secundarias.

				//Inicializa as estruturas.
				ManagedDesc->FrontFace = gcnew CA_D3D11_DEPTH_STENCILOP_DESC();
				ManagedDesc->BackFace = gcnew CA_D3D11_DEPTH_STENCILOP_DESC();

				//Preenche os dados de cada estrutura.
				ManagedDesc->FrontFace->StencilDepthFailOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->FrontFace.StencilDepthFailOp);
				ManagedDesc->FrontFace->StencilFailOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->FrontFace.StencilFailOp);
				ManagedDesc->FrontFace->StencilPassOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->FrontFace.StencilPassOp);
				ManagedDesc->FrontFace->StencilFunc = static_cast<SDKBase::Enumeracoes::CA_D3D11_COMPARISON_FUNC>(Param_NativeDescStencil->FrontFace.StencilFunc);

				ManagedDesc->BackFace->StencilDepthFailOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->BackFace.StencilDepthFailOp);
				ManagedDesc->BackFace->StencilFailOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->BackFace.StencilFailOp);
				ManagedDesc->BackFace->StencilPassOp = static_cast<SDKBase::Enumeracoes::CA_D3D11_STENCIL_OP>(Param_NativeDescStencil->BackFace.StencilPassOp);
				ManagedDesc->BackFace->StencilFunc = static_cast<SDKBase::Enumeracoes::CA_D3D11_COMPARISON_FUNC>(Param_NativeDescStencil->BackFace.StencilFunc);


				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_DEPTH_STENCIL_VIEW_DESC) para sua correspondencia não gerenciada(D3D11_DEPTH_STENCIL_VIEW_DESC).
			D3D11_DEPTH_STENCIL_VIEW_DESC* ConverterD3D11_DEPTH_STENCIL_VIEW_DESCManaged_ToUnManaged(CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ Param_DescStencilView)
			{
				//Variavel a ser retornada.
				D3D11_DEPTH_STENCIL_VIEW_DESC* pNativeDesc = CriarEstrutura<D3D11_DEPTH_STENCIL_VIEW_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescStencilView->Formato);
				pNativeDesc->ViewDimension = static_cast<D3D11_DSV_DIMENSION>(Param_DescStencilView->ViewDimensao);
				pNativeDesc->Flags = static_cast<UINT>(Param_DescStencilView->Flags);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_DescStencilView->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture1D.MipSlice = Param_DescStencilView->Textura1D->MipSlice;
				}
				if (Param_DescStencilView->Textura1DArray != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture1DArray.ArraySize = Param_DescStencilView->Textura1DArray->ArraySize;
					pNativeDesc->Texture1DArray.FirstArraySlice = Param_DescStencilView->Textura1DArray->FirstArraySlice;
					pNativeDesc->Texture1DArray.MipSlice = Param_DescStencilView->Textura1DArray->MipSlice;
				}
				if (Param_DescStencilView->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2D.MipSlice = Param_DescStencilView->Textura2D->MipSlice;
				}
				if (Param_DescStencilView->Textura2DArray != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2DArray.ArraySize = Param_DescStencilView->Textura2DArray->ArraySize;
					pNativeDesc->Texture2DArray.FirstArraySlice = Param_DescStencilView->Textura2DArray->FirstArraySlice;
					pNativeDesc->Texture2DArray.MipSlice = Param_DescStencilView->Textura2DArray->MipSlice;
				}
				if (Param_DescStencilView->Textura2DMS != nullptr)
				{
					//Essa estrutura não define nada.
				}
				if (Param_DescStencilView->Textura2DMSArray != nullptr)
				{
					//Essa estrutura não define nada.
					pNativeDesc->Texture2DMSArray.ArraySize = Param_DescStencilView->Textura2DMSArray->ArraySize;
					pNativeDesc->Texture2DMSArray.FirstArraySlice = Param_DescStencilView->Textura2DMSArray->FirstArraySlice;
				}

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_DEPTH_STENCIL_VIEW_DESC) para sua correspondencia gerenciada(CA_D3D11_DEPTH_STENCIL_VIEW_DESC).
			CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ ConverterD3D11_DEPTH_STENCIL_VIEW_DESCUnManaged_ToManaged(D3D11_DEPTH_STENCIL_VIEW_DESC* Param_NativeDescStencilView)
			{
				//Variavel a ser retornada.
				CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ ManagedDesc = gcnew CA_D3D11_DEPTH_STENCIL_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescStencilView->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_DSV_DIMENSION>(Param_NativeDescStencilView->ViewDimension);
				ManagedDesc->Flags = static_cast<SDKBase::Enumeracoes::CA_D3D11_DSV_FLAG>(Param_NativeDescStencilView->Flags);

				//Inicializa as estruturas secundarias
				ManagedDesc->Textura1D = gcnew CA_D3D11_TEX1D_DSV();
				ManagedDesc->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_DSV();
				ManagedDesc->Textura2D = gcnew CA_D3D11_TEX2D_DSV();
				ManagedDesc->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_DSV();
				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				ManagedDesc->Textura2DMSArray = gcnew CA_D3D11_TEX2DMS_ARRAY_DSV();

				//Preenche as estruturas.
				ManagedDesc->Textura1D->MipSlice = Param_NativeDescStencilView->Texture1D.MipSlice;
				ManagedDesc->Textura1DArray->ArraySize = Param_NativeDescStencilView->Texture1DArray.ArraySize;
				ManagedDesc->Textura1DArray->FirstArraySlice = Param_NativeDescStencilView->Texture1DArray.FirstArraySlice;
				ManagedDesc->Textura1DArray->MipSlice = Param_NativeDescStencilView->Texture1DArray.MipSlice;
				ManagedDesc->Textura2D->MipSlice = Param_NativeDescStencilView->Texture2D.MipSlice;
				ManagedDesc->Textura2DArray->ArraySize = Param_NativeDescStencilView->Texture2DArray.ArraySize;
				ManagedDesc->Textura2DArray->FirstArraySlice = Param_NativeDescStencilView->Texture2DArray.FirstArraySlice;
				ManagedDesc->Textura2DArray->MipSlice = Param_NativeDescStencilView->Texture2DArray.MipSlice;
				ManagedDesc->Textura2DMSArray->ArraySize = Param_NativeDescStencilView->Texture2DMSArray.ArraySize;
				ManagedDesc->Textura2DMSArray->FirstArraySlice = Param_NativeDescStencilView->Texture2DMSArray.FirstArraySlice;

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC) para sua correspondencia não gerenciada(D3D11_UNORDERED_ACCESS_VIEW_DESC).
			D3D11_UNORDERED_ACCESS_VIEW_DESC* ConverterD3D11_UNORDERED_ACCESS_VIEW_DESCManaged_ToUnManaged(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ Param_DescUnordered)
			{
				//Variavel a ser retornada.
				D3D11_UNORDERED_ACCESS_VIEW_DESC* pNativeDesc = CriarEstrutura<D3D11_UNORDERED_ACCESS_VIEW_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescUnordered->Formato);
				pNativeDesc->ViewDimension = static_cast<D3D11_UAV_DIMENSION>(Param_DescUnordered->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_DescUnordered->Buffer != nullptr)
				{
					pNativeDesc->Buffer.FirstElement = Param_DescUnordered->Buffer->FirstElement;
					pNativeDesc->Buffer.NumElements = Param_DescUnordered->Buffer->NumElements;
					pNativeDesc->Buffer.Flags = Param_DescUnordered->Buffer->Flags;
				}
				if (Param_DescUnordered->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture1D.MipSlice = Param_DescUnordered->Textura1D->MipSlice;
				}
				if (Param_DescUnordered->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture1DArray.ArraySize = Param_DescUnordered->Textura1DArray->ArraySize;
					pNativeDesc->Texture1DArray.FirstArraySlice = Param_DescUnordered->Textura1DArray->FirstArraySlice;
					pNativeDesc->Texture1DArray.MipSlice = Param_DescUnordered->Textura1DArray->MipSlice;
				}
				if (Param_DescUnordered->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2D.MipSlice = Param_DescUnordered->Textura2D->MipSlice;
				}
				if (Param_DescUnordered->Textura2DArray != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2DArray.ArraySize = Param_DescUnordered->Textura2DArray->ArraySize;
					pNativeDesc->Texture2DArray.FirstArraySlice = Param_DescUnordered->Textura2DArray->FirstArraySlice;
					pNativeDesc->Texture2DArray.MipSlice = Param_DescUnordered->Textura2DArray->MipSlice;
				}
				if (Param_DescUnordered->Textura3D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture3D.FirstWSlice = Param_DescUnordered->Textura3D->FirstWSlice;
					pNativeDesc->Texture3D.MipSlice = Param_DescUnordered->Textura3D->MipSlice;
					pNativeDesc->Texture3D.WSize = Param_DescUnordered->Textura3D->WSize;
				}

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_UNORDERED_ACCESS_VIEW_DESC) para sua correspondencia gerenciada(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC).
			CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ ConverterD3D11_UNORDERED_ACCESS_VIEW_DESCUnManaged_ToManaged(D3D11_UNORDERED_ACCESS_VIEW_DESC* Param_NativeDescUnordered)
			{
				//Variavel a ser retornada.
				CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ ManagedDesc = gcnew CA_D3D11_UNORDERED_ACCESS_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescUnordered->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_UAV_DIMENSION>(Param_NativeDescUnordered->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew CA_D3D11_BUFFER_UAV();
				ManagedDesc->Textura1D = gcnew CA_D3D11_TEX1D_UAV();
				ManagedDesc->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_UAV();
				ManagedDesc->Textura2D = gcnew CA_D3D11_TEX2D_UAV();
				ManagedDesc->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_UAV();
				ManagedDesc->Textura3D = gcnew CA_D3D11_TEX3D_UAV();

				//Preenche as estruturas.
				ManagedDesc->Buffer->FirstElement = Param_NativeDescUnordered->Buffer.FirstElement;
				ManagedDesc->Buffer->NumElements = Param_NativeDescUnordered->Buffer.NumElements;
				ManagedDesc->Buffer->Flags = Param_NativeDescUnordered->Buffer.Flags;
				ManagedDesc->Textura1D->MipSlice = Param_NativeDescUnordered->Texture1D.MipSlice;
				ManagedDesc->Textura1DArray->ArraySize = Param_NativeDescUnordered->Texture1DArray.ArraySize;
				ManagedDesc->Textura1DArray->FirstArraySlice = Param_NativeDescUnordered->Texture1DArray.FirstArraySlice;
				ManagedDesc->Textura1DArray->MipSlice = Param_NativeDescUnordered->Texture1DArray.MipSlice;
				ManagedDesc->Textura2D->MipSlice = Param_NativeDescUnordered->Texture2D.MipSlice;
				ManagedDesc->Textura2DArray->ArraySize = Param_NativeDescUnordered->Texture2DArray.ArraySize;
				ManagedDesc->Textura2DArray->FirstArraySlice = Param_NativeDescUnordered->Texture2DArray.FirstArraySlice;
				ManagedDesc->Textura2DArray->MipSlice = Param_NativeDescUnordered->Texture2DArray.MipSlice;
				ManagedDesc->Textura3D->FirstWSlice = Param_NativeDescUnordered->Texture3D.FirstWSlice;
				ManagedDesc->Textura3D->MipSlice = Param_NativeDescUnordered->Texture3D.MipSlice;
				ManagedDesc->Textura3D->WSize = Param_NativeDescUnordered->Texture3D.WSize;

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1) para sua correspondencia não gerenciada(D3D11_UNORDERED_ACCESS_VIEW_DESC1).
			D3D11_UNORDERED_ACCESS_VIEW_DESC1* ConverterD3D11_UNORDERED_ACCESS_VIEW_DESC1Managed_ToUnManaged(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_UNORDERED_ACCESS_VIEW_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_UNORDERED_ACCESS_VIEW_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->ViewDimension = static_cast<D3D11_UAV_DIMENSION>(Param_Estrutura->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_Estrutura->Buffer != nullptr)
				{
					EstruturaRetorno->Buffer.FirstElement = Param_Estrutura->Buffer->FirstElement;
					EstruturaRetorno->Buffer.NumElements = Param_Estrutura->Buffer->NumElements;
					EstruturaRetorno->Buffer.Flags = Param_Estrutura->Buffer->Flags;
				}
				if (Param_Estrutura->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture1D.MipSlice = Param_Estrutura->Textura1D->MipSlice;
				}
				if (Param_Estrutura->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture1DArray.ArraySize = Param_Estrutura->Textura1DArray->ArraySize;
					EstruturaRetorno->Texture1DArray.FirstArraySlice = Param_Estrutura->Textura1DArray->FirstArraySlice;
					EstruturaRetorno->Texture1DArray.MipSlice = Param_Estrutura->Textura1DArray->MipSlice;
				}
				if (Param_Estrutura->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture2D.MipSlice = Param_Estrutura->Textura2D->MipSlice;
					EstruturaRetorno->Texture2D.PlaneSlice = Param_Estrutura->Textura2D->PlaneSlice;
				}
				if (Param_Estrutura->Textura2DArray != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture2DArray.ArraySize = Param_Estrutura->Textura2DArray->ArraySize;
					EstruturaRetorno->Texture2DArray.FirstArraySlice = Param_Estrutura->Textura2DArray->FirstArraySlice;
					EstruturaRetorno->Texture2DArray.MipSlice = Param_Estrutura->Textura2DArray->MipSlice;
					EstruturaRetorno->Texture2DArray.PlaneSlice = Param_Estrutura->Textura2DArray->PlaneSlice;
				}
				if (Param_Estrutura->Textura3D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture3D.FirstWSlice = Param_Estrutura->Textura3D->FirstWSlice;
					EstruturaRetorno->Texture3D.MipSlice = Param_Estrutura->Textura3D->MipSlice;
					EstruturaRetorno->Texture3D.WSize = Param_Estrutura->Textura3D->WSize;
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_UNORDERED_ACCESS_VIEW_DESC1) para sua correspondencia gerenciada(CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1).
			CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ ConverterD3D11_UNORDERED_ACCESS_VIEW_DESC1UnManaged_ToManaged(D3D11_UNORDERED_ACCESS_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ EstruturaRetorno = gcnew CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_UAV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew CA_D3D11_BUFFER_UAV();
				EstruturaRetorno->Textura1D = gcnew CA_D3D11_TEX1D_UAV();
				EstruturaRetorno->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_UAV();
				EstruturaRetorno->Textura2D = gcnew CA_D3D11_TEX2D_UAV1();
				EstruturaRetorno->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_UAV1();
				EstruturaRetorno->Textura3D = gcnew CA_D3D11_TEX3D_UAV();

				//Preenche as estruturas.
				EstruturaRetorno->Buffer->FirstElement = Param_Estrutura->Buffer.FirstElement;
				EstruturaRetorno->Buffer->NumElements = Param_Estrutura->Buffer.NumElements;
				EstruturaRetorno->Buffer->Flags = Param_Estrutura->Buffer.Flags;
				EstruturaRetorno->Textura1D->MipSlice = Param_Estrutura->Texture1D.MipSlice;
				EstruturaRetorno->Textura1DArray->ArraySize = Param_Estrutura->Texture1DArray.ArraySize;
				EstruturaRetorno->Textura1DArray->FirstArraySlice = Param_Estrutura->Texture1DArray.FirstArraySlice;
				EstruturaRetorno->Textura1DArray->MipSlice = Param_Estrutura->Texture1DArray.MipSlice;
				EstruturaRetorno->Textura2D->MipSlice = Param_Estrutura->Texture2D.MipSlice;
				EstruturaRetorno->Textura2D->PlaneSlice = Param_Estrutura->Texture2D.PlaneSlice;
				EstruturaRetorno->Textura2DArray->ArraySize = Param_Estrutura->Texture2DArray.ArraySize;
				EstruturaRetorno->Textura2DArray->FirstArraySlice = Param_Estrutura->Texture2DArray.FirstArraySlice;
				EstruturaRetorno->Textura2DArray->MipSlice = Param_Estrutura->Texture2DArray.MipSlice;
				EstruturaRetorno->Textura2DArray->PlaneSlice = Param_Estrutura->Texture2DArray.PlaneSlice;
				EstruturaRetorno->Textura3D->FirstWSlice = Param_Estrutura->Texture3D.FirstWSlice;
				EstruturaRetorno->Textura3D->MipSlice = Param_Estrutura->Texture3D.MipSlice;
				EstruturaRetorno->Textura3D->WSize = Param_Estrutura->Texture3D.WSize;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SAMPLER_DESC) para sua correspondencia não gerenciada(D3D11_SAMPLER_DESC).
			D3D11_SAMPLER_DESC* ConverterD3D11_SAMPLER_DESCManaged_ToUnManaged(CA_D3D11_SAMPLER_DESC^ Param_DescSampler)
			{
				//Variavel a ser retornada.
				D3D11_SAMPLER_DESC* pNativeDesc = CriarEstrutura<D3D11_SAMPLER_DESC>();

				//Preenche os dados da estrutura principal.
				pNativeDesc->Filter = static_cast<D3D11_FILTER>(Param_DescSampler->Filter);
				pNativeDesc->AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(Param_DescSampler->AddressU);
				pNativeDesc->AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(Param_DescSampler->AddressU);
				pNativeDesc->AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(Param_DescSampler->AddressU);
				pNativeDesc->ComparisonFunc = static_cast<D3D11_COMPARISON_FUNC>(Param_DescSampler->ComparisonFunc);
				pNativeDesc->MipLODBias = Param_DescSampler->MipLODBias;
				pNativeDesc->MaxAnisotropy = Param_DescSampler->MaxAnisotropy;
				pNativeDesc->MinLOD = Param_DescSampler->MinLOD;
				pNativeDesc->MaxLOD = Param_DescSampler->MaxLOD;

				//Verifica se vai definir a fronteira da cor da borda.
				if (Param_DescSampler->BorderColor != nullptr)
				{
					//O array deve ter 4 entradas fixas.
					pNativeDesc->BorderColor[0] = Param_DescSampler->BorderColor[0];
					pNativeDesc->BorderColor[1] = Param_DescSampler->BorderColor[1];
					pNativeDesc->BorderColor[2] = Param_DescSampler->BorderColor[2];
					pNativeDesc->BorderColor[3] = Param_DescSampler->BorderColor[3];
				}

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_SAMPLER_DESC) para sua correspondencia gerenciada(CA_D3D11_SAMPLER_DESC).
			CA_D3D11_SAMPLER_DESC^ ConverterD3D11_SAMPLER_DESCUnManaged_ToManaged(D3D11_SAMPLER_DESC* Param_NativeDescSampler)
			{
				//Variavel a ser retornada.
				CA_D3D11_SAMPLER_DESC^ ManagedDesc = gcnew CA_D3D11_SAMPLER_DESC();

				//Preenche os dados da estrutura
				ManagedDesc->Filter = static_cast<SDKBase::Enumeracoes::CA_D3D11_FILTER>(Param_NativeDescSampler->Filter);
				ManagedDesc->AddressU = static_cast<SDKBase::Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE>(Param_NativeDescSampler->AddressU);
				ManagedDesc->AddressV = static_cast<SDKBase::Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE>(Param_NativeDescSampler->AddressV);
				ManagedDesc->AddressW = static_cast<SDKBase::Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE>(Param_NativeDescSampler->AddressW);
				ManagedDesc->ComparisonFunc = static_cast<SDKBase::Enumeracoes::CA_D3D11_COMPARISON_FUNC>(Param_NativeDescSampler->ComparisonFunc);
				ManagedDesc->MipLODBias = Param_NativeDescSampler->MipLODBias;
				ManagedDesc->MaxAnisotropy = Param_NativeDescSampler->MaxAnisotropy;
				ManagedDesc->MinLOD = Param_NativeDescSampler->MinLOD;
				ManagedDesc->MaxLOD = Param_NativeDescSampler->MaxLOD;

				//Cria o array que vai conter o array de floats.
				//O array nativo é um constante de 4 valores.
				ManagedDesc->BorderColor = gcnew cli::array<float>(4);

				//Define os valores no array
				ManagedDesc->BorderColor[0] = Param_NativeDescSampler->BorderColor[0];
				ManagedDesc->BorderColor[1] = Param_NativeDescSampler->BorderColor[1];
				ManagedDesc->BorderColor[2] = Param_NativeDescSampler->BorderColor[2];
				ManagedDesc->BorderColor[3] = Param_NativeDescSampler->BorderColor[3];


				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SHADER_RESOURCE_VIEW_DESC) para sua correspondencia não gerenciada(D3D11_SHADER_RESOURCE_VIEW_DESC).
			D3D11_SHADER_RESOURCE_VIEW_DESC* ConverterD3D11_SHADER_RESOURCE_VIEW_DESCManaged_ToUnManaged(CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ Param_DescShader)
			{
				//Variavel a ser retornada.
				D3D11_SHADER_RESOURCE_VIEW_DESC* pNativeDesc = CriarEstrutura<D3D11_SHADER_RESOURCE_VIEW_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescShader->Formato);
				pNativeDesc->ViewDimension = static_cast<D3D11_SRV_DIMENSION>(Param_DescShader->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_DescShader->Buffer != nullptr)
				{
					//Define os dados na estrutura.
					pNativeDesc->Buffer.FirstElement = Param_DescShader->Buffer->FirstElement;
					pNativeDesc->Buffer.NumElements = Param_DescShader->Buffer->NumElements;
					pNativeDesc->Buffer.ElementOffset = Param_DescShader->Buffer->ElementOffset;
					pNativeDesc->Buffer.ElementWidth = Param_DescShader->Buffer->ElementWidth;
				}
				if (Param_DescShader->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture1D.MipLevels = Param_DescShader->Textura1D->MipLevels;
					pNativeDesc->Texture1D.MostDetailedMip = Param_DescShader->Textura1D->MostDetailedMip;
				}
				if (Param_DescShader->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture1DArray.ArraySize = Param_DescShader->Textura1DArray->ArraySize;
					pNativeDesc->Texture1DArray.FirstArraySlice = Param_DescShader->Textura1DArray->FirstArraySlice;
					pNativeDesc->Texture1DArray.MipLevels = Param_DescShader->Textura1DArray->MipLevels;
					pNativeDesc->Texture1DArray.MostDetailedMip = Param_DescShader->Textura1DArray->MostDetailedMip;
				}
				if (Param_DescShader->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2D.MipLevels = Param_DescShader->Textura2D->MipLevels;
					pNativeDesc->Texture2D.MostDetailedMip = Param_DescShader->Textura2D->MostDetailedMip;
				}
				if (Param_DescShader->Textura2DArray != nullptr)
				{
					//Define o dados da estrutura.
					pNativeDesc->Texture2DArray.ArraySize = Param_DescShader->Textura2DArray->ArraySize;
					pNativeDesc->Texture2DArray.FirstArraySlice = Param_DescShader->Textura2DArray->FirstArraySlice;
					pNativeDesc->Texture2DArray.MipLevels = Param_DescShader->Textura2DArray->MipLevels;
					pNativeDesc->Texture2DArray.MostDetailedMip = Param_DescShader->Textura2DArray->MostDetailedMip;
				}
				if (Param_DescShader->Textura2DMSArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture2DMSArray.ArraySize = Param_DescShader->Textura2DMSArray->ArraySize;
					pNativeDesc->Texture2DMSArray.FirstArraySlice = Param_DescShader->Textura2DMSArray->FirstArraySlice;
				}
				if (Param_DescShader->Textura3D != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture3D.MipLevels = Param_DescShader->Textura3D->MipLevels;
					pNativeDesc->Texture3D.MostDetailedMip = Param_DescShader->Textura3D->MostDetailedMip;
				}
				if (Param_DescShader->TexturaCube != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->TextureCube.MipLevels = Param_DescShader->TexturaCube->MipLevels;
					pNativeDesc->TextureCube.MostDetailedMip = Param_DescShader->TexturaCube->MostDetailedMip;
				}
				if (Param_DescShader->TexturaCubeArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->TextureCubeArray.First2DArrayFace = Param_DescShader->TexturaCubeArray->First2DArrayFace;
					pNativeDesc->TextureCubeArray.NumCubes = Param_DescShader->TexturaCubeArray->NumCubes;
					pNativeDesc->TextureCubeArray.MipLevels = Param_DescShader->TexturaCubeArray->MipLevels;
					pNativeDesc->TextureCubeArray.MostDetailedMip = Param_DescShader->TexturaCubeArray->MostDetailedMip;
				}
				if (Param_DescShader->BufferEx != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->BufferEx.FirstElement = Param_DescShader->BufferEx->FirstElement;
					pNativeDesc->BufferEx.NumElements = Param_DescShader->BufferEx->NumElements;
					pNativeDesc->BufferEx.Flags = Param_DescShader->BufferEx->Flags;
				}

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_SHADER_RESOURCE_VIEW_DESC) para sua correspondencia gerenciada(CA_D3D11_SHADER_RESOURCE_VIEW_DESC).
			CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ ConverterD3D11_SHADER_RESOURCE_VIEW_DESCUnManaged_ToManaged(D3D11_SHADER_RESOURCE_VIEW_DESC* Param_NativeDescShader)
			{
				//Variavel a ser retornada.
				CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ ManagedDesc = gcnew CA_D3D11_SHADER_RESOURCE_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescShader->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_SRV_DIMENSION>(Param_NativeDescShader->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew CA_D3D11_BUFFER_SRV();
				ManagedDesc->Textura1D = gcnew CA_D3D11_TEX1D_SRV();
				ManagedDesc->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_SRV();
				ManagedDesc->Textura2D = gcnew CA_D3D11_TEX2D_SRV();
				ManagedDesc->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_SRV();
				// Texture2DMS -> D3D11_TEX2DMS_SRV - Não há necessidade de criar.
				ManagedDesc->Textura2DMSArray = gcnew CA_D3D11_TEX2DMS_ARRAY_SRV();
				ManagedDesc->Textura3D = gcnew CA_D3D11_TEX3D_SRV();
				ManagedDesc->TexturaCube = gcnew  CA_D3D11_TEXCUBE_SRV();
				ManagedDesc->TexturaCubeArray = gcnew CA_D3D11_TEXCUBE_ARRAY_SRV();
				ManagedDesc->BufferEx = gcnew CA_D3D11_BUFFEREX_SRV();

				//Preenche as estruturas com as informações da nativa.
				ManagedDesc->Buffer->FirstElement = Param_NativeDescShader->Buffer.FirstElement;
				ManagedDesc->Buffer->NumElements = Param_NativeDescShader->Buffer.NumElements;
				ManagedDesc->Buffer->ElementOffset = Param_NativeDescShader->Buffer.ElementOffset;
				ManagedDesc->Buffer->ElementWidth = Param_NativeDescShader->Buffer.ElementWidth;
				ManagedDesc->Textura1D->MipLevels = Param_NativeDescShader->Texture1D.MipLevels;
				ManagedDesc->Textura1D->MostDetailedMip = Param_NativeDescShader->Texture1D.MostDetailedMip;
				ManagedDesc->Textura1DArray->ArraySize = Param_NativeDescShader->Texture1DArray.ArraySize;
				ManagedDesc->Textura1DArray->FirstArraySlice = Param_NativeDescShader->Texture1DArray.FirstArraySlice;
				ManagedDesc->Textura1DArray->MipLevels = Param_NativeDescShader->Texture1DArray.MipLevels;
				ManagedDesc->Textura1DArray->MostDetailedMip = Param_NativeDescShader->Texture1DArray.MostDetailedMip;
				ManagedDesc->Textura2D->MipLevels = Param_NativeDescShader->Texture2D.MipLevels;
				ManagedDesc->Textura2D->MostDetailedMip = Param_NativeDescShader->Texture2D.MostDetailedMip;
				ManagedDesc->Textura2DArray->ArraySize = Param_NativeDescShader->Texture2DArray.ArraySize;
				ManagedDesc->Textura2DArray->FirstArraySlice = Param_NativeDescShader->Texture2DArray.FirstArraySlice;
				ManagedDesc->Textura2DArray->MipLevels = Param_NativeDescShader->Texture2DArray.MipLevels;
				ManagedDesc->Textura2DArray->MostDetailedMip = Param_NativeDescShader->Texture2DArray.MostDetailedMip;
				ManagedDesc->Textura2DMSArray->ArraySize = Param_NativeDescShader->Texture2DMSArray.ArraySize;
				ManagedDesc->Textura2DMSArray->FirstArraySlice = Param_NativeDescShader->Texture2DMSArray.FirstArraySlice;
				ManagedDesc->Textura3D->MipLevels = Param_NativeDescShader->Texture3D.MipLevels;
				ManagedDesc->Textura3D->MostDetailedMip = Param_NativeDescShader->Texture3D.MostDetailedMip;
				ManagedDesc->TexturaCube->MipLevels = Param_NativeDescShader->TextureCube.MipLevels;
				ManagedDesc->TexturaCube->MostDetailedMip = Param_NativeDescShader->TextureCube.MostDetailedMip;
				ManagedDesc->TexturaCubeArray->First2DArrayFace = Param_NativeDescShader->TextureCubeArray.First2DArrayFace;
				ManagedDesc->TexturaCubeArray->MipLevels = Param_NativeDescShader->TextureCubeArray.MipLevels;
				ManagedDesc->TexturaCubeArray->MostDetailedMip = Param_NativeDescShader->TextureCubeArray.MostDetailedMip;
				ManagedDesc->TexturaCubeArray->NumCubes = Param_NativeDescShader->TextureCubeArray.NumCubes;
				ManagedDesc->BufferEx->FirstElement = Param_NativeDescShader->BufferEx.FirstElement;
				ManagedDesc->BufferEx->NumElements = Param_NativeDescShader->BufferEx.NumElements;
				ManagedDesc->BufferEx->Flags = Param_NativeDescShader->BufferEx.Flags;

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SHADER_RESOURCE_VIEW_DESC1) para sua correspondencia não gerenciada(D3D11_SHADER_RESOURCE_VIEW_DESC1).
			D3D11_SHADER_RESOURCE_VIEW_DESC1* ConverterD3D11_SHADER_RESOURCE_VIEW_DESC1Managed_ToUnManaged(CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_SHADER_RESOURCE_VIEW_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_SHADER_RESOURCE_VIEW_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->ViewDimension = static_cast<D3D11_SRV_DIMENSION>(Param_Estrutura->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_Estrutura->Buffer != nullptr)
				{
					//Define os dados na estrutura.
					EstruturaRetorno->Buffer.FirstElement = Param_Estrutura->Buffer->FirstElement;
					EstruturaRetorno->Buffer.NumElements = Param_Estrutura->Buffer->NumElements;
					EstruturaRetorno->Buffer.ElementOffset = Param_Estrutura->Buffer->ElementOffset;
					EstruturaRetorno->Buffer.ElementWidth = Param_Estrutura->Buffer->ElementWidth;
				}
				if (Param_Estrutura->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture1D.MipLevels = Param_Estrutura->Textura1D->MipLevels;
					EstruturaRetorno->Texture1D.MostDetailedMip = Param_Estrutura->Textura1D->MostDetailedMip;
				}
				if (Param_Estrutura->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture1DArray.ArraySize = Param_Estrutura->Textura1DArray->ArraySize;
					EstruturaRetorno->Texture1DArray.FirstArraySlice = Param_Estrutura->Textura1DArray->FirstArraySlice;
					EstruturaRetorno->Texture1DArray.MipLevels = Param_Estrutura->Textura1DArray->MipLevels;
					EstruturaRetorno->Texture1DArray.MostDetailedMip = Param_Estrutura->Textura1DArray->MostDetailedMip;
				}
				if (Param_Estrutura->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture2D.MipLevels = Param_Estrutura->Textura2D->MipLevels;
					EstruturaRetorno->Texture2D.MostDetailedMip = Param_Estrutura->Textura2D->MostDetailedMip;
					EstruturaRetorno->Texture2D.PlaneSlice = Param_Estrutura->Textura2D->PlaneSlice;
				}
				if (Param_Estrutura->Textura2DArray != nullptr)
				{
					//Define o dados da estrutura.
					EstruturaRetorno->Texture2DArray.ArraySize = Param_Estrutura->Textura2DArray->ArraySize;
					EstruturaRetorno->Texture2DArray.FirstArraySlice = Param_Estrutura->Textura2DArray->FirstArraySlice;
					EstruturaRetorno->Texture2DArray.MipLevels = Param_Estrutura->Textura2DArray->MipLevels;
					EstruturaRetorno->Texture2DArray.MostDetailedMip = Param_Estrutura->Textura2DArray->MostDetailedMip;
					EstruturaRetorno->Texture2DArray.PlaneSlice = Param_Estrutura->Textura2DArray->PlaneSlice;
				}
				if (Param_Estrutura->Textura2DMSArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture2DMSArray.ArraySize = Param_Estrutura->Textura2DMSArray->ArraySize;
					EstruturaRetorno->Texture2DMSArray.FirstArraySlice = Param_Estrutura->Textura2DMSArray->FirstArraySlice;
				}
				if (Param_Estrutura->Textura3D != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture3D.MipLevels = Param_Estrutura->Textura3D->MipLevels;
					EstruturaRetorno->Texture3D.MostDetailedMip = Param_Estrutura->Textura3D->MostDetailedMip;
				}
				if (Param_Estrutura->TexturaCube != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->TextureCube.MipLevels = Param_Estrutura->TexturaCube->MipLevels;
					EstruturaRetorno->TextureCube.MostDetailedMip = Param_Estrutura->TexturaCube->MostDetailedMip;
				}
				if (Param_Estrutura->TexturaCubeArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->TextureCubeArray.First2DArrayFace = Param_Estrutura->TexturaCubeArray->First2DArrayFace;
					EstruturaRetorno->TextureCubeArray.NumCubes = Param_Estrutura->TexturaCubeArray->NumCubes;
					EstruturaRetorno->TextureCubeArray.MipLevels = Param_Estrutura->TexturaCubeArray->MipLevels;
					EstruturaRetorno->TextureCubeArray.MostDetailedMip = Param_Estrutura->TexturaCubeArray->MostDetailedMip;
				}
				if (Param_Estrutura->BufferEx != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->BufferEx.FirstElement = Param_Estrutura->BufferEx->FirstElement;
					EstruturaRetorno->BufferEx.NumElements = Param_Estrutura->BufferEx->NumElements;
					EstruturaRetorno->BufferEx.Flags = Param_Estrutura->BufferEx->Flags;
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_SHADER_RESOURCE_VIEW_DESC1) para sua correspondencia gerenciada(CA_D3D11_SHADER_RESOURCE_VIEW_DESC1).
			CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ ConverterD3D11_SHADER_RESOURCE_VIEW_DESC1UnManaged_ToManaged(D3D11_SHADER_RESOURCE_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ EstruturaRetorno = gcnew CA_D3D11_SHADER_RESOURCE_VIEW_DESC1();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_SRV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew CA_D3D11_BUFFER_SRV();
				EstruturaRetorno->Textura1D = gcnew CA_D3D11_TEX1D_SRV();
				EstruturaRetorno->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_SRV();
				EstruturaRetorno->Textura2D = gcnew CA_D3D11_TEX2D_SRV1();
				EstruturaRetorno->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_SRV1();

				// Texture2DMS -> D3D11_TEX2DMS_SRV - Não há necessidade de criar.
				EstruturaRetorno->Textura2DMSArray = gcnew CA_D3D11_TEX2DMS_ARRAY_SRV();
				EstruturaRetorno->Textura3D = gcnew CA_D3D11_TEX3D_SRV();
				EstruturaRetorno->TexturaCube = gcnew  CA_D3D11_TEXCUBE_SRV();
				EstruturaRetorno->TexturaCubeArray = gcnew CA_D3D11_TEXCUBE_ARRAY_SRV();
				EstruturaRetorno->BufferEx = gcnew CA_D3D11_BUFFEREX_SRV();

				//Preenche as estruturas com as informações da nativa.
				EstruturaRetorno->Buffer->FirstElement = Param_Estrutura->Buffer.FirstElement;
				EstruturaRetorno->Buffer->NumElements = Param_Estrutura->Buffer.NumElements;
				EstruturaRetorno->Buffer->ElementOffset = Param_Estrutura->Buffer.ElementOffset;
				EstruturaRetorno->Buffer->ElementWidth = Param_Estrutura->Buffer.ElementWidth;
				EstruturaRetorno->Textura1D->MipLevels = Param_Estrutura->Texture1D.MipLevels;
				EstruturaRetorno->Textura1D->MostDetailedMip = Param_Estrutura->Texture1D.MostDetailedMip;
				EstruturaRetorno->Textura1DArray->ArraySize = Param_Estrutura->Texture1DArray.ArraySize;
				EstruturaRetorno->Textura1DArray->FirstArraySlice = Param_Estrutura->Texture1DArray.FirstArraySlice;
				EstruturaRetorno->Textura1DArray->MipLevels = Param_Estrutura->Texture1DArray.MipLevels;
				EstruturaRetorno->Textura1DArray->MostDetailedMip = Param_Estrutura->Texture1DArray.MostDetailedMip;
				EstruturaRetorno->Textura2D->MipLevels = Param_Estrutura->Texture2D.MipLevels;
				EstruturaRetorno->Textura2D->MostDetailedMip = Param_Estrutura->Texture2D.MostDetailedMip;
				EstruturaRetorno->Textura2D->PlaneSlice = Param_Estrutura->Texture2D.PlaneSlice;
				EstruturaRetorno->Textura2DArray->ArraySize = Param_Estrutura->Texture2DArray.ArraySize;
				EstruturaRetorno->Textura2DArray->FirstArraySlice = Param_Estrutura->Texture2DArray.FirstArraySlice;
				EstruturaRetorno->Textura2DArray->MipLevels = Param_Estrutura->Texture2DArray.MipLevels;
				EstruturaRetorno->Textura2DArray->MostDetailedMip = Param_Estrutura->Texture2DArray.MostDetailedMip;
				EstruturaRetorno->Textura2DArray->PlaneSlice = Param_Estrutura->Texture2DArray.PlaneSlice;
				EstruturaRetorno->Textura2DMSArray->ArraySize = Param_Estrutura->Texture2DMSArray.ArraySize;
				EstruturaRetorno->Textura2DMSArray->FirstArraySlice = Param_Estrutura->Texture2DMSArray.FirstArraySlice;
				EstruturaRetorno->Textura3D->MipLevels = Param_Estrutura->Texture3D.MipLevels;
				EstruturaRetorno->Textura3D->MostDetailedMip = Param_Estrutura->Texture3D.MostDetailedMip;
				EstruturaRetorno->TexturaCube->MipLevels = Param_Estrutura->TextureCube.MipLevels;
				EstruturaRetorno->TexturaCube->MostDetailedMip = Param_Estrutura->TextureCube.MostDetailedMip;
				EstruturaRetorno->TexturaCubeArray->First2DArrayFace = Param_Estrutura->TextureCubeArray.First2DArrayFace;
				EstruturaRetorno->TexturaCubeArray->MipLevels = Param_Estrutura->TextureCubeArray.MipLevels;
				EstruturaRetorno->TexturaCubeArray->MostDetailedMip = Param_Estrutura->TextureCubeArray.MostDetailedMip;
				EstruturaRetorno->TexturaCubeArray->NumCubes = Param_Estrutura->TextureCubeArray.NumCubes;
				EstruturaRetorno->BufferEx->FirstElement = Param_Estrutura->BufferEx.FirstElement;
				EstruturaRetorno->BufferEx->NumElements = Param_Estrutura->BufferEx.NumElements;
				EstruturaRetorno->BufferEx->Flags = Param_Estrutura->BufferEx.Flags;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_RASTERIZER_DESC) para sua correspondencia não gerenciada(D3D11_RASTERIZER_DESC).
			D3D11_RASTERIZER_DESC* ConverterD3D11_RASTERIZER_DESCManaged_ToUnManaged(CA_D3D11_RASTERIZER_DESC^ Param_DescRasterizer)
			{
				//Variavel a ser retornada.
				D3D11_RASTERIZER_DESC* pNativeDesc = CriarEstrutura<D3D11_RASTERIZER_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->AntialiasedLineEnable = Param_DescRasterizer->AntialiasedLineEnable ? TRUE : FALSE;
				pNativeDesc->CullMode = static_cast<D3D11_CULL_MODE>(Param_DescRasterizer->CullMode);
				pNativeDesc->DepthBias = Param_DescRasterizer->DepthBias;
				pNativeDesc->DepthBiasClamp = Param_DescRasterizer->DepthBiasClamp;
				pNativeDesc->DepthClipEnable = Param_DescRasterizer->DepthClipEnable ? TRUE : FALSE;
				pNativeDesc->FillMode = static_cast<D3D11_FILL_MODE>(Param_DescRasterizer->FillMode);
				pNativeDesc->FrontCounterClockwise = Param_DescRasterizer->FrontCounterClockwise ? TRUE : FALSE;
				pNativeDesc->MultisampleEnable = Param_DescRasterizer->MultisampleEnable ? TRUE : FALSE;
				pNativeDesc->ScissorEnable = Param_DescRasterizer->ScissorEnable ? TRUE : FALSE;
				pNativeDesc->SlopeScaledDepthBias = Param_DescRasterizer->SlopeScaledDepthBias;

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_RASTERIZER_DESC) para sua correspondencia gerenciada(CA_D3D11_RASTERIZER_DESC).
			CA_D3D11_RASTERIZER_DESC^ ConverterD3D11_RASTERIZER_DESCUnManaged_ToManaged(D3D11_RASTERIZER_DESC* Param_NativeDescRasterizer)
			{
				//Variavel a ser retornada.
				CA_D3D11_RASTERIZER_DESC^ ManagedDesc = gcnew CA_D3D11_RASTERIZER_DESC();

				//Preenche os dados da estrutura.
				ManagedDesc->AntialiasedLineEnable = Param_NativeDescRasterizer->AntialiasedLineEnable ? true : false;
				ManagedDesc->CullMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_CULL_MODE>(Param_NativeDescRasterizer->CullMode);
				ManagedDesc->DepthBias = Param_NativeDescRasterizer->DepthBias;
				ManagedDesc->DepthBiasClamp = Param_NativeDescRasterizer->DepthBiasClamp;
				ManagedDesc->DepthClipEnable = Param_NativeDescRasterizer->DepthClipEnable ? true : false;
				ManagedDesc->FillMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_FILL_MODE>(Param_NativeDescRasterizer->FillMode);
				ManagedDesc->FrontCounterClockwise = Param_NativeDescRasterizer->FrontCounterClockwise ? true : false;
				ManagedDesc->MultisampleEnable = Param_NativeDescRasterizer->MultisampleEnable ? true : false;
				ManagedDesc->ScissorEnable = Param_NativeDescRasterizer->ScissorEnable ? true : false;
				ManagedDesc->SlopeScaledDepthBias = Param_NativeDescRasterizer->SlopeScaledDepthBias;

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_RASTERIZER_DESC1) para sua correspondencia não gerenciada(D3D11_RASTERIZER_DESC1).
			D3D11_RASTERIZER_DESC1* ConverterD3D11_RASTERIZER_DESC1Managed_ToUnManaged(CA_D3D11_RASTERIZER_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_RASTERIZER_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_RASTERIZER_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura.
				EstruturaRetorno->AntialiasedLineEnable = Param_Estrutura->AntialiasedLineEnable ? TRUE : FALSE;
				EstruturaRetorno->CullMode = static_cast<D3D11_CULL_MODE>(Param_Estrutura->CullMode);
				EstruturaRetorno->DepthBias = Param_Estrutura->DepthBias;
				EstruturaRetorno->DepthBiasClamp = Param_Estrutura->DepthBiasClamp;
				EstruturaRetorno->DepthClipEnable = Param_Estrutura->DepthClipEnable ? TRUE : FALSE;
				EstruturaRetorno->FillMode = static_cast<D3D11_FILL_MODE>(Param_Estrutura->FillMode);
				EstruturaRetorno->FrontCounterClockwise = Param_Estrutura->FrontCounterClockwise ? TRUE : FALSE;
				EstruturaRetorno->MultisampleEnable = Param_Estrutura->MultisampleEnable ? TRUE : FALSE;
				EstruturaRetorno->ScissorEnable = Param_Estrutura->ScissorEnable ? TRUE : FALSE;
				EstruturaRetorno->SlopeScaledDepthBias = Param_Estrutura->SlopeScaledDepthBias;
				EstruturaRetorno->ForcedSampleCount = Param_Estrutura->ForcedSampleCount;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_RASTERIZER_DESC1) para sua correspondencia gerenciada(CA_D3D11_RASTERIZER_DESC1).
			CA_D3D11_RASTERIZER_DESC1^ ConverterD3D11_RASTERIZER_DESC1UnManaged_ToManaged(D3D11_RASTERIZER_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_RASTERIZER_DESC1^ EstruturaRetorno = gcnew CA_D3D11_RASTERIZER_DESC1();

				//Preenche os dados da estrutura.
				EstruturaRetorno->AntialiasedLineEnable = Param_Estrutura->AntialiasedLineEnable ? true : false;
				EstruturaRetorno->CullMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_CULL_MODE>(Param_Estrutura->CullMode);
				EstruturaRetorno->DepthBias = Param_Estrutura->DepthBias;
				EstruturaRetorno->DepthBiasClamp = Param_Estrutura->DepthBiasClamp;
				EstruturaRetorno->DepthClipEnable = Param_Estrutura->DepthClipEnable ? true : false;
				EstruturaRetorno->FillMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_FILL_MODE>(Param_Estrutura->FillMode);
				EstruturaRetorno->FrontCounterClockwise = Param_Estrutura->FrontCounterClockwise ? true : false;
				EstruturaRetorno->MultisampleEnable = Param_Estrutura->MultisampleEnable ? true : false;
				EstruturaRetorno->ScissorEnable = Param_Estrutura->ScissorEnable ? true : false;
				EstruturaRetorno->SlopeScaledDepthBias = Param_Estrutura->SlopeScaledDepthBias;
				EstruturaRetorno->ForcedSampleCount = Param_Estrutura->ForcedSampleCount;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_RASTERIZER_DESC2) para sua correspondencia não gerenciada(D3D11_RASTERIZER_DESC2).
			D3D11_RASTERIZER_DESC2* ConverterD3D11_RASTERIZER_DESC2Managed_ToUnManaged(CA_D3D11_RASTERIZER_DESC2^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_RASTERIZER_DESC2* EstruturaRetorno = CriarEstrutura<D3D11_RASTERIZER_DESC2>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura.
				EstruturaRetorno->AntialiasedLineEnable = Param_Estrutura->AntialiasedLineEnable ? TRUE : FALSE;
				EstruturaRetorno->CullMode = static_cast<D3D11_CULL_MODE>(Param_Estrutura->CullMode);
				EstruturaRetorno->DepthBias = Param_Estrutura->DepthBias;
				EstruturaRetorno->DepthBiasClamp = Param_Estrutura->DepthBiasClamp;
				EstruturaRetorno->DepthClipEnable = Param_Estrutura->DepthClipEnable ? TRUE : FALSE;
				EstruturaRetorno->FillMode = static_cast<D3D11_FILL_MODE>(Param_Estrutura->FillMode);
				EstruturaRetorno->FrontCounterClockwise = Param_Estrutura->FrontCounterClockwise ? TRUE : FALSE;
				EstruturaRetorno->MultisampleEnable = Param_Estrutura->MultisampleEnable ? TRUE : FALSE;
				EstruturaRetorno->ScissorEnable = Param_Estrutura->ScissorEnable ? TRUE : FALSE;
				EstruturaRetorno->SlopeScaledDepthBias = Param_Estrutura->SlopeScaledDepthBias;
				EstruturaRetorno->ForcedSampleCount = Param_Estrutura->ForcedSampleCount;
				EstruturaRetorno->ConservativeRaster = static_cast<D3D11_CONSERVATIVE_RASTERIZATION_MODE>(Param_Estrutura->ConservativeRaster);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_RASTERIZER_DESC2) para sua correspondencia gerenciada(CA_D3D11_RASTERIZER_DESC2).
			CA_D3D11_RASTERIZER_DESC2^ ConverterD3D11_RASTERIZER_DESC2UnManaged_ToManaged(D3D11_RASTERIZER_DESC2* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_RASTERIZER_DESC2^ EstruturaRetorno = gcnew CA_D3D11_RASTERIZER_DESC2();

				//Preenche os dados da estrutura.
				EstruturaRetorno->AntialiasedLineEnable = Param_Estrutura->AntialiasedLineEnable ? true : false;
				EstruturaRetorno->CullMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_CULL_MODE>(Param_Estrutura->CullMode);
				EstruturaRetorno->DepthBias = Param_Estrutura->DepthBias;
				EstruturaRetorno->DepthBiasClamp = Param_Estrutura->DepthBiasClamp;
				EstruturaRetorno->DepthClipEnable = Param_Estrutura->DepthClipEnable ? true : false;
				EstruturaRetorno->FillMode = static_cast<SDKBase::Enumeracoes::CA_D3D11_FILL_MODE>(Param_Estrutura->FillMode);
				EstruturaRetorno->FrontCounterClockwise = Param_Estrutura->FrontCounterClockwise ? true : false;
				EstruturaRetorno->MultisampleEnable = Param_Estrutura->MultisampleEnable ? true : false;
				EstruturaRetorno->ScissorEnable = Param_Estrutura->ScissorEnable ? true : false;
				EstruturaRetorno->SlopeScaledDepthBias = Param_Estrutura->SlopeScaledDepthBias;
				EstruturaRetorno->ForcedSampleCount = Param_Estrutura->ForcedSampleCount;
				EstruturaRetorno->ConservativeRaster = static_cast<CA_D3D11_CONSERVATIVE_RASTERIZATION_MODE>(Param_Estrutura->ConservativeRaster);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_RENDER_TARGET_VIEW_DESC) para sua correspondencia não gerenciada(D3D11_RENDER_TARGET_VIEW_DESC).
			D3D11_RENDER_TARGET_VIEW_DESC* ConverterD3D11_RENDER_TARGET_VIEW_DESCManaged_ToUnManaged(CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender)
			{
				//Variavel a ser retornada.
				D3D11_RENDER_TARGET_VIEW_DESC* pNativeDesc = CriarEstrutura<D3D11_RENDER_TARGET_VIEW_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescRender->Formato);
				pNativeDesc->ViewDimension = static_cast<D3D11_RTV_DIMENSION>(Param_DescRender->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_DescRender->Buffer != nullptr)
				{
					pNativeDesc->Buffer.FirstElement = Param_DescRender->Buffer->FirstElement;
					pNativeDesc->Buffer.NumElements = Param_DescRender->Buffer->NumElements;
					pNativeDesc->Buffer.ElementOffset = Param_DescRender->Buffer->ElementOffset;
					pNativeDesc->Buffer.ElementWidth = Param_DescRender->Buffer->ElementWidth;
				}
				if (Param_DescRender->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture1D.MipSlice = Param_DescRender->Textura1D->MipSlice;
				}
				if (Param_DescRender->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture1DArray.ArraySize = Param_DescRender->Textura1DArray->ArraySize;
					pNativeDesc->Texture1DArray.FirstArraySlice = Param_DescRender->Textura1DArray->FirstArraySlice;
					pNativeDesc->Texture1DArray.MipSlice = Param_DescRender->Textura1DArray->MipSlice;
				}
				if (Param_DescRender->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2D.MipSlice = Param_DescRender->Textura2D->MipSlice;
				}
				if (Param_DescRender->Textura2DArray != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture2DArray.ArraySize = Param_DescRender->Textura2DArray->ArraySize;
					pNativeDesc->Texture2DArray.FirstArraySlice = Param_DescRender->Textura2DArray->FirstArraySlice;
					pNativeDesc->Texture2DArray.MipSlice = Param_DescRender->Textura2DArray->MipSlice;
				}
				if (Param_DescRender->Textura2DMSArray != nullptr)
				{
					//Define os dados da estrutura.
					pNativeDesc->Texture2DMSArray.ArraySize = Param_DescRender->Textura2DMSArray->ArraySize;
					pNativeDesc->Texture2DMSArray.FirstArraySlice = Param_DescRender->Textura2DMSArray->FirstArraySlice;
				}
				if (Param_DescRender->Textura3D != nullptr)
				{
					//Define o dado da estrutura.
					pNativeDesc->Texture3D.FirstWSlice = Param_DescRender->Textura3D->FirstWSlice;
					pNativeDesc->Texture3D.MipSlice = Param_DescRender->Textura3D->MipSlice;
					pNativeDesc->Texture3D.WSize = Param_DescRender->Textura3D->WSize;
				}

				//Retorna a estrutura.
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_RENDER_TARGET_VIEW_DESC) para sua correspondencia gerenciada(CA_D3D11_RENDER_TARGET_VIEW_DESC).
			CA_D3D11_RENDER_TARGET_VIEW_DESC^ ConverterD3D11_RENDER_TARGET_VIEW_DESCUnManaged_ToManaged(D3D11_RENDER_TARGET_VIEW_DESC* Param_NativeDescRender)
			{
				//Variavel a ser retornada.
				CA_D3D11_RENDER_TARGET_VIEW_DESC^ ManagedDesc = gcnew CA_D3D11_RENDER_TARGET_VIEW_DESC();


				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescRender->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_RTV_DIMENSION>(Param_NativeDescRender->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew CA_D3D11_BUFFER_RTV();
				ManagedDesc->Textura1D = gcnew CA_D3D11_TEX1D_RTV();
				ManagedDesc->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_RTV();
				ManagedDesc->Textura2D = gcnew CA_D3D11_TEX2D_RTV();
				ManagedDesc->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_RTV();
				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				ManagedDesc->Textura2DMSArray = gcnew CA_D3D11_TEX2DMS_ARRAY_RTV();
				ManagedDesc->Textura3D = gcnew CA_D3D11_TEX3D_RTV();

				//Preenche as estruturas.
				ManagedDesc->Buffer->FirstElement = Param_NativeDescRender->Buffer.FirstElement;
				ManagedDesc->Buffer->NumElements = Param_NativeDescRender->Buffer.NumElements;
				ManagedDesc->Buffer->ElementOffset = Param_NativeDescRender->Buffer.ElementOffset;
				ManagedDesc->Buffer->ElementWidth = Param_NativeDescRender->Buffer.ElementWidth;
				ManagedDesc->Textura1D->MipSlice = Param_NativeDescRender->Texture1D.MipSlice;
				ManagedDesc->Textura1DArray->ArraySize = Param_NativeDescRender->Texture1DArray.ArraySize;
				ManagedDesc->Textura1DArray->FirstArraySlice = Param_NativeDescRender->Texture1DArray.FirstArraySlice;
				ManagedDesc->Textura1DArray->MipSlice = Param_NativeDescRender->Texture1DArray.MipSlice;
				ManagedDesc->Textura2D->MipSlice = Param_NativeDescRender->Texture2D.MipSlice;
				ManagedDesc->Textura2DArray->ArraySize = Param_NativeDescRender->Texture2DArray.ArraySize;
				ManagedDesc->Textura2DArray->FirstArraySlice = Param_NativeDescRender->Texture2DArray.FirstArraySlice;
				ManagedDesc->Textura2DArray->MipSlice = Param_NativeDescRender->Texture2DArray.MipSlice;
				ManagedDesc->Textura2DMSArray->ArraySize = Param_NativeDescRender->Texture2DMSArray.ArraySize;
				ManagedDesc->Textura2DMSArray->FirstArraySlice = Param_NativeDescRender->Texture2DMSArray.FirstArraySlice;

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_RENDER_TARGET_VIEW_DESC) para sua correspondencia não gerenciada(D3D11_RENDER_TARGET_VIEW_DESC1).
			D3D11_RENDER_TARGET_VIEW_DESC1* ConverterD3D11_RENDER_TARGET_VIEW_DESC1Managed_ToUnManaged(CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_RENDER_TARGET_VIEW_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_RENDER_TARGET_VIEW_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura nativa.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->ViewDimension = static_cast<D3D11_RTV_DIMENSION>(Param_Estrutura->ViewDimensao);


				//Preenche os dados de cada estrutura(se valida) que estão presente na união.
				if (Param_Estrutura->Buffer != nullptr)
				{
					EstruturaRetorno->Buffer.FirstElement = Param_Estrutura->Buffer->FirstElement;
					EstruturaRetorno->Buffer.NumElements = Param_Estrutura->Buffer->NumElements;
					EstruturaRetorno->Buffer.ElementOffset = Param_Estrutura->Buffer->ElementOffset;
					EstruturaRetorno->Buffer.ElementWidth = Param_Estrutura->Buffer->ElementWidth;
				}
				if (Param_Estrutura->Textura1D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture1D.MipSlice = Param_Estrutura->Textura1D->MipSlice;
				}
				if (Param_Estrutura->Textura1DArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture1DArray.ArraySize = Param_Estrutura->Textura1DArray->ArraySize;
					EstruturaRetorno->Texture1DArray.FirstArraySlice = Param_Estrutura->Textura1DArray->FirstArraySlice;
					EstruturaRetorno->Texture1DArray.MipSlice = Param_Estrutura->Textura1DArray->MipSlice;
				}
				if (Param_Estrutura->Textura2D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture2D.MipSlice = Param_Estrutura->Textura2D->MipSlice;
					EstruturaRetorno->Texture2D.PlaneSlice = Param_Estrutura->Textura2D->PlaneSlice;
				}
				if (Param_Estrutura->Textura2DArray != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture2DArray.ArraySize = Param_Estrutura->Textura2DArray->ArraySize;
					EstruturaRetorno->Texture2DArray.FirstArraySlice = Param_Estrutura->Textura2DArray->FirstArraySlice;
					EstruturaRetorno->Texture2DArray.MipSlice = Param_Estrutura->Textura2DArray->MipSlice;
					EstruturaRetorno->Texture2DArray.PlaneSlice = Param_Estrutura->Textura2DArray->PlaneSlice;
				}
				if (Param_Estrutura->Textura2DMSArray != nullptr)
				{
					//Define os dados da estrutura.
					EstruturaRetorno->Texture2DMSArray.ArraySize = Param_Estrutura->Textura2DMSArray->ArraySize;
					EstruturaRetorno->Texture2DMSArray.FirstArraySlice = Param_Estrutura->Textura2DMSArray->FirstArraySlice;
				}
				if (Param_Estrutura->Textura3D != nullptr)
				{
					//Define o dado da estrutura.
					EstruturaRetorno->Texture3D.FirstWSlice = Param_Estrutura->Textura3D->FirstWSlice;
					EstruturaRetorno->Texture3D.MipSlice = Param_Estrutura->Textura3D->MipSlice;
					EstruturaRetorno->Texture3D.WSize = Param_Estrutura->Textura3D->WSize;
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_RENDER_TARGET_VIEW_DESC1) para sua correspondencia gerenciada(CA_D3D11_RENDER_TARGET_VIEW_DESC).
			CA_D3D11_RENDER_TARGET_VIEW_DESC1^ ConverterD3D11_RENDER_TARGET_VIEW_DESC1UnManaged_ToManaged(D3D11_RENDER_TARGET_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_RENDER_TARGET_VIEW_DESC1^ EstruturaRetorno = gcnew CA_D3D11_RENDER_TARGET_VIEW_DESC1();


				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_RTV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew CA_D3D11_BUFFER_RTV();
				EstruturaRetorno->Textura1D = gcnew CA_D3D11_TEX1D_RTV();
				EstruturaRetorno->Textura1DArray = gcnew CA_D3D11_TEX1D_ARRAY_RTV();
				EstruturaRetorno->Textura2D = gcnew CA_D3D11_TEX2D_RTV1();
				EstruturaRetorno->Textura2DArray = gcnew CA_D3D11_TEX2D_ARRAY_RTV1();

				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				EstruturaRetorno->Textura2DMSArray = gcnew CA_D3D11_TEX2DMS_ARRAY_RTV();
				EstruturaRetorno->Textura3D = gcnew CA_D3D11_TEX3D_RTV();

				//Preenche as estruturas.
				EstruturaRetorno->Buffer->FirstElement = Param_Estrutura->Buffer.FirstElement;
				EstruturaRetorno->Buffer->NumElements = Param_Estrutura->Buffer.NumElements;
				EstruturaRetorno->Buffer->ElementOffset = Param_Estrutura->Buffer.ElementOffset;
				EstruturaRetorno->Buffer->ElementWidth = Param_Estrutura->Buffer.ElementWidth;
				EstruturaRetorno->Textura1D->MipSlice = Param_Estrutura->Texture1D.MipSlice;
				EstruturaRetorno->Textura1DArray->ArraySize = Param_Estrutura->Texture1DArray.ArraySize;
				EstruturaRetorno->Textura1DArray->FirstArraySlice = Param_Estrutura->Texture1DArray.FirstArraySlice;
				EstruturaRetorno->Textura1DArray->MipSlice = Param_Estrutura->Texture1DArray.MipSlice;
				EstruturaRetorno->Textura2D->MipSlice = Param_Estrutura->Texture2D.MipSlice;
				EstruturaRetorno->Textura2D->PlaneSlice = Param_Estrutura->Texture2D.PlaneSlice;
				EstruturaRetorno->Textura2DArray->ArraySize = Param_Estrutura->Texture2DArray.ArraySize;
				EstruturaRetorno->Textura2DArray->FirstArraySlice = Param_Estrutura->Texture2DArray.FirstArraySlice;
				EstruturaRetorno->Textura2DArray->MipSlice = Param_Estrutura->Texture2DArray.MipSlice;
				EstruturaRetorno->Textura2DArray->PlaneSlice = Param_Estrutura->Texture2DArray.PlaneSlice;
				EstruturaRetorno->Textura2DMSArray->ArraySize = Param_Estrutura->Texture2DMSArray.ArraySize;
				EstruturaRetorno->Textura2DMSArray->FirstArraySlice = Param_Estrutura->Texture2DMSArray.FirstArraySlice;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE1D_DESC) para sua correspondencia não gerenciada(D3D11_TEXTURE1D_DESC).
			D3D11_TEXTURE1D_DESC* ConverterD3D11_TEXTURE1D_DESCManaged_ToUnManaged(CA_D3D11_TEXTURE1D_DESC^ Param_DescTex1D)
			{
				//Variavel a ser retornada.
				D3D11_TEXTURE1D_DESC* pNativeDesc = CriarEstrutura<D3D11_TEXTURE1D_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescTex1D->Formato);
				pNativeDesc->Width = Param_DescTex1D->Width;
				pNativeDesc->ArraySize = Param_DescTex1D->ArraySize;
				pNativeDesc->MipLevels = Param_DescTex1D->MipLevels;
				pNativeDesc->CPUAccessFlags = static_cast<UINT>(Param_DescTex1D->CPUAccessFlags);
				pNativeDesc->Usage = static_cast<D3D11_USAGE>(Param_DescTex1D->Usage);
				pNativeDesc->BindFlags = static_cast<UINT>(Param_DescTex1D->BindFlags);
				pNativeDesc->MiscFlags = static_cast<UINT>(Param_DescTex1D->MiscFlags);

				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_TEXTURE1D_DESC) para sua correspondencia gerenciada(CA_D3D11_TEXTURE1D_DESC).
			CA_D3D11_TEXTURE1D_DESC^ ConverterD3D11_TEXTURE1D_DESCUnManaged_ToManaged(D3D11_TEXTURE1D_DESC* Param_NativeDescTex1D)
			{
				//Variavel a ser retornada.
				CA_D3D11_TEXTURE1D_DESC^ ManagedDesc = gcnew CA_D3D11_TEXTURE1D_DESC();

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescTex1D->Format);
				ManagedDesc->Width = Param_NativeDescTex1D->Width;
				ManagedDesc->ArraySize = Param_NativeDescTex1D->ArraySize;
				ManagedDesc->MipLevels = Param_NativeDescTex1D->MipLevels;
				ManagedDesc->CPUAccessFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>(Param_NativeDescTex1D->CPUAccessFlags);
				ManagedDesc->Usage = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>(Param_NativeDescTex1D->Usage);
				ManagedDesc->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>(Param_NativeDescTex1D->BindFlags);
				ManagedDesc->MiscFlags = Param_NativeDescTex1D->MiscFlags;

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE2D_DESC) para sua correspondencia não gerenciada(D3D11_TEXTURE2D_DESC).
			D3D11_TEXTURE2D_DESC* ConverterD3D11_TEXTURE2D_DESCManaged_ToUnManaged(CA_D3D11_TEXTURE2D_DESC^ Param_DescTex2D)
			{
				//Variavel a ser retornada.
				D3D11_TEXTURE2D_DESC* pNativeDesc = CriarEstrutura<D3D11_TEXTURE2D_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescTex2D->Formato);
				pNativeDesc->Width = Param_DescTex2D->Width;
				pNativeDesc->Height = Param_DescTex2D->Height;
				pNativeDesc->ArraySize = Param_DescTex2D->ArraySize;
				pNativeDesc->MipLevels = Param_DescTex2D->MipLevels;
				pNativeDesc->CPUAccessFlags = static_cast<UINT>(Param_DescTex2D->CPUAccessFlags);
				pNativeDesc->Usage = static_cast<D3D11_USAGE>(Param_DescTex2D->Usage);
				pNativeDesc->BindFlags = static_cast<UINT>(Param_DescTex2D->BindFlags);
				pNativeDesc->MiscFlags = static_cast<UINT>(Param_DescTex2D->MiscFlags);

				//Define a estrutura secundaria
				if (Param_DescTex2D->SampleDesc != nullptr)
				{
					//Define os dados.
					pNativeDesc->SampleDesc.Count = Param_DescTex2D->SampleDesc->Count;
					pNativeDesc->SampleDesc.Quality = Param_DescTex2D->SampleDesc->Quality;
				}


				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_TEXTURE2D_DESC) para sua correspondencia gerenciada(CA_D3D11_TEXTURE2D_DESC).
			CA_D3D11_TEXTURE2D_DESC^ ConverterD3D11_TEXTURE2D_DESCUnManaged_ToManaged(D3D11_TEXTURE2D_DESC* Param_NativeDescTex2D)
			{
				//Variavel a ser retornada.
				CA_D3D11_TEXTURE2D_DESC^ ManagedDesc = gcnew CA_D3D11_TEXTURE2D_DESC();

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescTex2D->Format);
				ManagedDesc->Width = Param_NativeDescTex2D->Width;
				ManagedDesc->Height = Param_NativeDescTex2D->Height;
				ManagedDesc->ArraySize = Param_NativeDescTex2D->ArraySize;
				ManagedDesc->MipLevels = Param_NativeDescTex2D->MipLevels;
				ManagedDesc->CPUAccessFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>(Param_NativeDescTex2D->CPUAccessFlags);
				ManagedDesc->Usage = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>(Param_NativeDescTex2D->Usage);
				ManagedDesc->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>(Param_NativeDescTex2D->BindFlags);
				ManagedDesc->MiscFlags = Param_NativeDescTex2D->MiscFlags;

				//Define os dados da estrutura secundaria

				//Inicializa a estrutura.
				ManagedDesc->SampleDesc = gcnew CA_DXGI_SAMPLE_DESC();

				ManagedDesc->SampleDesc->Count = Param_NativeDescTex2D->SampleDesc.Count;
				ManagedDesc->SampleDesc->Quality = Param_NativeDescTex2D->SampleDesc.Quality;

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE2D_DESC1) para sua correspondencia não gerenciada(D3D11_TEXTURE2D_DESC1).
			D3D11_TEXTURE2D_DESC1* ConverterD3D11_TEXTURE2D_DESC1Managed_ToUnManaged(CA_D3D11_TEXTURE2D_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_TEXTURE2D_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_TEXTURE2D_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->ArraySize = Param_Estrutura->ArraySize;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->CPUAccessFlags = static_cast<UINT>(Param_Estrutura->CPUAccessFlags);
				EstruturaRetorno->Usage = static_cast<D3D11_USAGE>(Param_Estrutura->Usage);
				EstruturaRetorno->BindFlags = static_cast<UINT>(Param_Estrutura->BindFlags);
				EstruturaRetorno->MiscFlags = static_cast<UINT>(Param_Estrutura->MiscFlags);
				EstruturaRetorno->TextureLayout = static_cast<D3D11_TEXTURE_LAYOUT>(Param_Estrutura->TextureLayout);

				//Define a estrutura secundaria
				if (Param_Estrutura->SampleDesc != nullptr)
				{
					//Define os dados.
					EstruturaRetorno->SampleDesc.Count = Param_Estrutura->SampleDesc->Count;
					EstruturaRetorno->SampleDesc.Quality = Param_Estrutura->SampleDesc->Quality;
				}


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_TEXTURE2D_DESC1) para sua correspondencia gerenciada(CA_D3D11_TEXTURE2D_DESC1).
			CA_D3D11_TEXTURE2D_DESC1^ ConverterD3D11_TEXTURE2D_DESC1UnManaged_ToManaged(D3D11_TEXTURE2D_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_TEXTURE2D_DESC1^ EstruturaRetorno = gcnew CA_D3D11_TEXTURE2D_DESC1();

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->ArraySize = Param_Estrutura->ArraySize;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->CPUAccessFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>(Param_Estrutura->CPUAccessFlags);
				EstruturaRetorno->Usage = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>(Param_Estrutura->Usage);
				EstruturaRetorno->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>(Param_Estrutura->BindFlags);
				EstruturaRetorno->MiscFlags = Param_Estrutura->MiscFlags;
				EstruturaRetorno->TextureLayout = static_cast<CA_D3D11_TEXTURE_LAYOUT>(Param_Estrutura->TextureLayout);

				//Define os dados da estrutura secundaria

				//Inicializa a estrutura.
				EstruturaRetorno->SampleDesc = gcnew CA_DXGI_SAMPLE_DESC();
				EstruturaRetorno->SampleDesc->Count = Param_Estrutura->SampleDesc.Count;
				EstruturaRetorno->SampleDesc->Quality = Param_Estrutura->SampleDesc.Quality;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE3D_DESC) para sua correspondencia não gerenciada(D3D11_TEXTURE3D_DESC).
			D3D11_TEXTURE3D_DESC* ConverterD3D11_TEXTURE3D_DESCManaged_ToUnManaged(CA_D3D11_TEXTURE3D_DESC^ Param_DescTex3D)
			{
				//Variavel a ser retornada.
				D3D11_TEXTURE3D_DESC* pNativeDesc = CriarEstrutura<D3D11_TEXTURE3D_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->Format = static_cast<DXGI_FORMAT>(Param_DescTex3D->Formato);
				pNativeDesc->Width = Param_DescTex3D->Width;
				pNativeDesc->Height = Param_DescTex3D->Height;
				pNativeDesc->Depth = Param_DescTex3D->Depth;
				pNativeDesc->MipLevels = Param_DescTex3D->MipLevels;
				pNativeDesc->CPUAccessFlags = static_cast<UINT>(Param_DescTex3D->CPUAccessFlags);
				pNativeDesc->Usage = static_cast<D3D11_USAGE>(Param_DescTex3D->Usage);
				pNativeDesc->BindFlags = static_cast<UINT>(Param_DescTex3D->BindFlags);
				pNativeDesc->MiscFlags = static_cast<UINT>(Param_DescTex3D->MiscFlags);

				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_TEXTURE3D_DESC) para sua correspondencia gerenciada(CA_D3D11_TEXTURE3D_DESC).
			CA_D3D11_TEXTURE3D_DESC^ ConverterD3D11_TEXTURE3D_DESCUnManaged_ToManaged(D3D11_TEXTURE3D_DESC* Param_NativeDescTex3D)
			{
				//Variavel a ser retornada.
				CA_D3D11_TEXTURE3D_DESC^ ManagedDesc = gcnew CA_D3D11_TEXTURE3D_DESC();

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescTex3D->Format);
				ManagedDesc->Width = Param_NativeDescTex3D->Width;
				ManagedDesc->Height = Param_NativeDescTex3D->Height;
				ManagedDesc->Depth = Param_NativeDescTex3D->Depth;
				ManagedDesc->MipLevels = Param_NativeDescTex3D->MipLevels;
				ManagedDesc->CPUAccessFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>(Param_NativeDescTex3D->CPUAccessFlags);
				ManagedDesc->Usage = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>(Param_NativeDescTex3D->Usage);
				ManagedDesc->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>(Param_NativeDescTex3D->BindFlags);
				ManagedDesc->MiscFlags = Param_NativeDescTex3D->MiscFlags;

				//Retorna a variavel.
				return ManagedDesc;
			}

			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE3D_DESC1) para sua correspondencia não gerenciada(D3D11_TEXTURE3D_DESC1).
			D3D11_TEXTURE3D_DESC1* ConverterD3D11_TEXTURE3D_DESC1Managed_ToUnManaged(CA_D3D11_TEXTURE3D_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_TEXTURE3D_DESC1* EstruturaRetorno = CriarEstrutura<D3D11_TEXTURE3D_DESC1>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(EstruturaRetorno));

				//Preenche os dados da estrutura.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->CPUAccessFlags = static_cast<UINT>(Param_Estrutura->CPUAccessFlags);
				EstruturaRetorno->Usage = static_cast<D3D11_USAGE>(Param_Estrutura->Usage);
				EstruturaRetorno->BindFlags = static_cast<UINT>(Param_Estrutura->BindFlags);
				EstruturaRetorno->MiscFlags = static_cast<UINT>(Param_Estrutura->MiscFlags);
				EstruturaRetorno->TextureLayout = static_cast<D3D11_TEXTURE_LAYOUT>(Param_Estrutura->TextureLayout);

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_TEXTURE3D_DESC1) para sua correspondencia gerenciada(CA_D3D11_TEXTURE3D_DESC1).
			CA_D3D11_TEXTURE3D_DESC1^ ConverterD3D11_TEXTURE3D_DESC1UnManaged_ToManaged(D3D11_TEXTURE3D_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_TEXTURE3D_DESC1^ EstruturaRetorno = gcnew CA_D3D11_TEXTURE3D_DESC1();

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->CPUAccessFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG>(Param_Estrutura->CPUAccessFlags);
				EstruturaRetorno->Usage = static_cast<SDKBase::Enumeracoes::CA_D3D11_USAGE>(Param_Estrutura->Usage);
				EstruturaRetorno->BindFlags = static_cast<SDKBase::Enumeracoes::CA_D3D11_BIND_FLAG>(Param_Estrutura->BindFlags);
				EstruturaRetorno->MiscFlags = Param_Estrutura->MiscFlags;
				EstruturaRetorno->TextureLayout = static_cast<CA_D3D11_TEXTURE_LAYOUT>(Param_Estrutura->TextureLayout);

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_DESC_CONTADOR) para sua correspondencia não gerenciada(D3D11_COUNTER_DESC).
			D3D11_COUNTER_DESC* ConverterD3D11_COUNTER_DESCManaged_ToUnManaged(CA_D3D11_DESC_CONTADOR^ Param_Desc)
			{
				//Variavel a ser retornada.
				D3D11_COUNTER_DESC* pNativeDesc = CriarEstrutura<D3D11_COUNTER_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->Counter = static_cast<D3D11_COUNTER>(Param_Desc->ContadorType);
				pNativeDesc->MiscFlags = Param_Desc->MiscFlags;

				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_COUNTER_DESC) para sua correspondencia gerenciada(CA_D3D11_DESC_CONTADOR).
			CA_D3D11_DESC_CONTADOR^ ConverterD3D11_COUNTER_DESCUnManaged_ToManaged(D3D11_COUNTER_DESC* Param_NativeDesc)
			{
				//Variavel a ser retornada.
				CA_D3D11_DESC_CONTADOR^ ManagedDesc = gcnew CA_D3D11_DESC_CONTADOR();

				//Preenche os dados da estrutura.
				ManagedDesc->ContadorType = static_cast<SDKBase::Enumeracoes::CA_D3D11_CONTADOR>(Param_NativeDesc->Counter);
				ManagedDesc->MiscFlags = Param_NativeDesc->MiscFlags;

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_INFO_CONTADOR) para sua correspondencia não gerenciada(D3D11_COUNTER_INFO).
			D3D11_COUNTER_INFO* ConverterD3D11_COUNTER_INFOManaged_ToUnManaged(CA_D3D11_INFO_CONTADOR^ Param_Desc)
			{
				//Variavel a ser retornada.
				D3D11_COUNTER_INFO* pNativeDesc = CriarEstrutura<D3D11_COUNTER_INFO>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(D3D11_COUNTER_INFO));

				//Preenche os dados da estrutura.
				pNativeDesc->LastDeviceDependentCounter = static_cast<D3D11_COUNTER>(Param_Desc->IDMaiorContadorDependente);
				pNativeDesc->NumDetectableParallelUnits = Param_Desc->NumeroUnidadesParalelasDetectaveis;
				pNativeDesc->NumSimultaneousCounters = Param_Desc->NumeroContadoresSimultaneos;

				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_COUNTER_INFO) para sua correspondencia gerenciada(CA_D3D11_INFO_CONTADOR).
			CA_D3D11_INFO_CONTADOR^ ConverterD3D11_COUNTER_INFOUnManaged_ToManaged(D3D11_COUNTER_INFO* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_D3D11_INFO_CONTADOR^ ManagedDesc = gcnew CA_D3D11_INFO_CONTADOR();

				//Preenche os dados da estrutura.
				ManagedDesc->IDMaiorContadorDependente = static_cast<SDKBase::Enumeracoes::CA_D3D11_CONTADOR>(Param_Desc->LastDeviceDependentCounter);
				ManagedDesc->NumeroUnidadesParalelasDetectaveis = Param_Desc->NumDetectableParallelUnits;
				ManagedDesc->NumeroContadoresSimultaneos = Param_Desc->NumSimultaneousCounters;


				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_FEATURE_DATA_THREADING) para sua correspondencia não gerenciada(D3D11_FEATURE_DATA_THREADING).
			D3D11_FEATURE_DATA_THREADING* ConverterD3D11_FEATURE_DATA_THREADINGManaged_ToUnManaged(CA_D3D11_FEATURE_DATA_THREADING^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_FEATURE_DATA_THREADING* pNativeDesc = CriarEstrutura<D3D11_FEATURE_DATA_THREADING>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(pNativeDesc, sizeof(pNativeDesc));

				//Preenche os dados da estrutura.
				pNativeDesc->DriverCommandLists = Param_Estrutura->DriverCommandLists;
				pNativeDesc->DriverConcurrentCreates = Param_Estrutura->DriverConcurrentCreates;

				//Retorna
				return pNativeDesc;
			}

			//Converte uma estrutura não gerenciada(D3D11_FEATURE_DATA_THREADING) para sua correspondencia gerenciada(CA_D3D11_FEATURE_DATA_THREADING).
			CA_D3D11_FEATURE_DATA_THREADING^ ConverterD3D11_FEATURE_DATA_THREADINGUnManaged_ToManaged(D3D11_FEATURE_DATA_THREADING* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_FEATURE_DATA_THREADING^ ManagedDesc = gcnew CA_D3D11_FEATURE_DATA_THREADING();

				//Preenche os dados da estrutura.
				ManagedDesc->DriverCommandLists = Param_Estrutura->DriverCommandLists;
				ManagedDesc->DriverConcurrentCreates = Param_Estrutura->DriverConcurrentCreates;
				ManagedDesc->TamanhoEstrutura = sizeof(D3D11_FEATURE_DATA_THREADING);

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_INPUT_ELEMENT_DESC) para sua correspondencia não gerenciada(D3D11_INPUT_ELEMENT_DESC).
			//Chame um (delete) no membro(SemanticName) para liberar a memoria para ele e depois libera a memoria da estrutura completa.
			D3D11_INPUT_ELEMENT_DESC* ConverterD3D11_INPUT_ELEMENT_DESCManaged_ToUnManaged(CA_D3D11_INPUT_ELEMENT_DESC^ Param_Desc)
			{
				//Variavel a ser retornada.
				D3D11_INPUT_ELEMENT_DESC* pEstrutura = CriarEstrutura<D3D11_INPUT_ELEMENT_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(D3D11_INPUT_ELEMENT_DESC));

				//Preenche os dados da estrutura.
				pEstrutura->AlignedByteOffset = Param_Desc->AlignedByteOffset;
				pEstrutura->Format = static_cast<DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->InputSlot = Param_Desc->InputSlot;
				pEstrutura->InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(Param_Desc->InputSlotClass);
				pEstrutura->InstanceDataStepRate = Param_Desc->InstanceDataStepRate;
				pEstrutura->SemanticIndex = Param_Desc->SemanticIndex;
				pEstrutura->SemanticName = ConverterStringToChar(Param_Desc->SemanticName);

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(D3D11_INPUT_ELEMENT_DESC) para sua correspondencia gerenciada(CA_D3D11_INPUT_ELEMENT_DESC).
			CA_D3D11_INPUT_ELEMENT_DESC^ ConverterD3D11_INPUT_ELEMENT_DESCUnManaged_ToManaged(D3D11_INPUT_ELEMENT_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_D3D11_INPUT_ELEMENT_DESC^ pEstrutura = gcnew CA_D3D11_INPUT_ELEMENT_DESC();

				//Preenche os dados da estrutura.
				pEstrutura->AlignedByteOffset = Param_Desc->AlignedByteOffset;
				pEstrutura->Format = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->InputSlot = Param_Desc->InputSlot;
				pEstrutura->InputSlotClass = static_cast<SDKBase::Enumeracoes::CA_D3D11_INPUT_CLASSIFICATION>(Param_Desc->InputSlotClass);
				pEstrutura->InstanceDataStepRate = Param_Desc->InstanceDataStepRate;
				pEstrutura->SemanticIndex = Param_Desc->SemanticIndex;
				pEstrutura->SemanticName = gcnew String(Param_Desc->SemanticName);

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SO_DECLARATION_ENTRY) para sua correspondencia não gerenciada(D3D11_SO_DECLARATION_ENTRY).
			//Chame um (delete) no membro(SemanticName) para liberar a memoria para ele e depois libera a memoria da estrutura completa.
			D3D11_SO_DECLARATION_ENTRY* ConverterD3D11_SO_DECLARATION_ENTRYManaged_ToUnManaged(CA_D3D11_SO_DECLARATION_ENTRY^ Param_Desc)
			{
				//Variavel a ser retornada.
				D3D11_SO_DECLARATION_ENTRY* pEstrutura = CriarEstrutura<D3D11_SO_DECLARATION_ENTRY>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(D3D11_SO_DECLARATION_ENTRY));

				//Preenche os dados da estrutura.
				pEstrutura->ComponentCount = Param_Desc->ComponentCount;
				pEstrutura->OutputSlot = Param_Desc->OutputSlot;
				pEstrutura->SemanticIndex = Param_Desc->SemanticIndex;
				pEstrutura->SemanticName = ConverterStringToChar(Param_Desc->SemanticName);
				pEstrutura->StartComponent = Param_Desc->StartComponent;
				pEstrutura->Stream = Param_Desc->Stream;

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(D3D11_SO_DECLARATION_ENTRY) para sua correspondencia gerenciada(CA_D3D11_SO_DECLARATION_ENTRY).
			CA_D3D11_SO_DECLARATION_ENTRY^ ConverterD3D11_SO_DECLARATION_ENTRYUnManaged_ToManaged(D3D11_SO_DECLARATION_ENTRY* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_D3D11_SO_DECLARATION_ENTRY^ pEstrutura = gcnew CA_D3D11_SO_DECLARATION_ENTRY();

				//Preenche os dados da estrutura.
				pEstrutura->ComponentCount = Param_Desc->ComponentCount;
				pEstrutura->OutputSlot = Param_Desc->OutputSlot;
				pEstrutura->SemanticIndex = Param_Desc->SemanticIndex;
				pEstrutura->SemanticName = gcnew String(Param_Desc->SemanticName);
				pEstrutura->StartComponent = Param_Desc->StartComponent;
				pEstrutura->Stream = Param_Desc->Stream;

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_VIEWPORT) para sua correspondencia não gerenciada(D3D11_VIEWPORT).
			D3D11_VIEWPORT* ConverterD3D11_VIEWPORTManaged_ToUnManaged(CA_D3D11_VIEWPORT^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_VIEWPORT* EstruturaRetorno = CriarEstrutura<D3D11_VIEWPORT>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_VIEWPORT));

				//Preenche os dados da estrutura.
				EstruturaRetorno->Height = Param_Estrutura->Altura;
				EstruturaRetorno->Width = Param_Estrutura->Largura;
				EstruturaRetorno->MaxDepth = Param_Estrutura->ProfundidadeMaxima;
				EstruturaRetorno->MinDepth = Param_Estrutura->ProfundidadeMinima;
				EstruturaRetorno->TopLeftX = Param_Estrutura->CantoSuperiorEsquerdoX;
				EstruturaRetorno->TopLeftY = Param_Estrutura->CantoSuperiorEsquerdoY;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_VIEWPORT) para sua correspondencia gerenciada(CA_D3D11_VIEWPORT).
			CA_D3D11_VIEWPORT^ ConverterD3D11_VIEWPORTUnManaged_ToManaged(D3D11_VIEWPORT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_VIEWPORT^ EstruturaRetorno = gcnew CA_D3D11_VIEWPORT();

				//Preenche os dados da estrutura.
				EstruturaRetorno->Altura = Param_Estrutura->Height;
				EstruturaRetorno->Largura = Param_Estrutura->Width;
				EstruturaRetorno->ProfundidadeMaxima = Param_Estrutura->MaxDepth;
				EstruturaRetorno->ProfundidadeMinima = Param_Estrutura->MinDepth;
				EstruturaRetorno->CantoSuperiorEsquerdoX = Param_Estrutura->TopLeftX;
				EstruturaRetorno->CantoSuperiorEsquerdoY = Param_Estrutura->TopLeftY;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_BOX) para sua correspondencia não gerenciada(D3D11_BOX).
			D3D11_BOX* ConverterD3D11_BOXManaged_ToUnManaged(CA_D3D11_BOX^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_BOX* EstruturaRetorno = CriarEstrutura<D3D11_BOX>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_BOX));

				//Preenche os dados da estrutura.
				EstruturaRetorno->back = Param_Estrutura->back;
				EstruturaRetorno->front = Param_Estrutura->front;
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->top = Param_Estrutura->top;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->left = Param_Estrutura->left;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_BOX) para sua correspondencia gerenciada(CA_D3D11_BOX).
			CA_D3D11_BOX^ ConverterD3D11_BOXUnManaged_ToManaged(D3D11_BOX* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_BOX^ EstruturaRetorno = gcnew CA_D3D11_BOX();

				//Preenche os dados da estrutura.
				EstruturaRetorno->back = Param_Estrutura->back;
				EstruturaRetorno->front = Param_Estrutura->front;
				EstruturaRetorno->bottom = Param_Estrutura->bottom;
				EstruturaRetorno->top = Param_Estrutura->top;
				EstruturaRetorno->right = Param_Estrutura->right;
				EstruturaRetorno->left = Param_Estrutura->left;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_MAPPED_SUBRESOURCE) para sua correspondencia não gerenciada(D3D11_MAPPED_SUBRESOURCE).
			D3D11_MAPPED_SUBRESOURCE* ConverterD3D11_MAPPED_SUBRESOURCEManaged_ToUnManaged(CA_D3D11_MAPPED_SUBRESOURCE^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_MAPPED_SUBRESOURCE* EstruturaRetorno = CriarEstrutura<D3D11_MAPPED_SUBRESOURCE>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_MAPPED_SUBRESOURCE));

				//Variveis
				IntPtr PointeiroBuffer = IntPtr::Zero;

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthPitch = Param_Estrutura->ProfundidadePasso;
				EstruturaRetorno->RowPitch = Param_Estrutura->LinhaPasso;

				//Obtém o ponteiro para o buffer.
				((ICarenBuffer^)Param_Estrutura->Param_BufferDados)->GetInternalPointer(PointeiroBuffer);

				//Define o ponteiro na estrutura
				EstruturaRetorno->pData = (PBYTE)PointeiroBuffer.ToPointer();

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_MAPPED_SUBRESOURCE) para sua correspondencia gerenciada(CA_D3D11_MAPPED_SUBRESOURCE).
			CA_D3D11_MAPPED_SUBRESOURCE^ ConverterD3D11_MAPPED_SUBRESOURCEUnManaged_ToManaged(D3D11_MAPPED_SUBRESOURCE* Param_Estrutura, ICarenBuffer^% Param_BuffInterface)
			{
				//Variavel a ser retornada.
				CA_D3D11_MAPPED_SUBRESOURCE^ EstruturaRetorno = gcnew CA_D3D11_MAPPED_SUBRESOURCE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->LinhaPasso = Param_Estrutura->RowPitch;
				EstruturaRetorno->ProfundidadePasso = Param_Estrutura->DepthPitch;

				//Define o ponteiro de buffer.
				Param_BuffInterface->CreateBuffer(IntPtr(Param_Estrutura->pData), false, 0, 0); //Associa o ponteiro da estrutura ao da CarenBuffer.

				//Define a interface de buffer criada na estrutura.
				EstruturaRetorno->Param_BufferDados = Param_BuffInterface;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILED_RESOURCE_COORDINATE) para sua correspondencia não gerenciada(D3D11_TILED_RESOURCE_COORDINATE).
			D3D11_TILED_RESOURCE_COORDINATE* ConverterD3D11_TILED_RESOURCE_COORDINATEManaged_ToUnManaged(CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_TILED_RESOURCE_COORDINATE* EstruturaRetorno = CriarEstrutura<D3D11_TILED_RESOURCE_COORDINATE>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_TILED_RESOURCE_COORDINATE));

				//Preenche os dados da estrutura.
				EstruturaRetorno->X = Param_Estrutura->X;
				EstruturaRetorno->Y = Param_Estrutura->Y;
				EstruturaRetorno->Z = Param_Estrutura->Z;
				EstruturaRetorno->Subresource = Param_Estrutura->Subresource;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_TILED_RESOURCE_COORDINATE) para sua correspondencia gerenciada(CA_D3D11_TILED_RESOURCE_COORDINATE).
			CA_D3D11_TILED_RESOURCE_COORDINATE^ ConverterD3D11_TILED_RESOURCE_COORDINATEUnManaged_ToManaged(D3D11_TILED_RESOURCE_COORDINATE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_TILED_RESOURCE_COORDINATE^ EstruturaRetorno = gcnew CA_D3D11_TILED_RESOURCE_COORDINATE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->X = Param_Estrutura->X;
				EstruturaRetorno->Y = Param_Estrutura->Y;
				EstruturaRetorno->Z = Param_Estrutura->Z;
				EstruturaRetorno->Subresource = Param_Estrutura->Subresource;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILE_REGION_SIZE) para sua correspondencia não gerenciada(D3D11_TILE_REGION_SIZE).
			D3D11_TILE_REGION_SIZE* ConverterD3D11_TILE_REGION_SIZEManaged_ToUnManaged(CA_D3D11_TILE_REGION_SIZE^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_TILE_REGION_SIZE* EstruturaRetorno = CriarEstrutura<D3D11_TILE_REGION_SIZE>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_TILE_REGION_SIZE));

				//Preenche os dados da estrutura.
				EstruturaRetorno->bUseBox = Param_Estrutura->bUseBox? TRUE: FALSE;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->NumTiles = Param_Estrutura->NumTiles;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_TILE_REGION_SIZE) para sua correspondencia gerenciada(CA_D3D11_TILE_REGION_SIZE).
			CA_D3D11_TILE_REGION_SIZE^ ConverterD3D11_TILE_REGION_SIZEUnManaged_ToManaged(D3D11_TILE_REGION_SIZE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_TILE_REGION_SIZE^ EstruturaRetorno = gcnew CA_D3D11_TILE_REGION_SIZE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->bUseBox = Param_Estrutura->bUseBox ? true : false;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->NumTiles = Param_Estrutura->NumTiles;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_PACKED_MIP_DESC) para sua correspondencia não gerenciada(D3D11_PACKED_MIP_DESC).
			D3D11_PACKED_MIP_DESC* ConverterD3D11_PACKED_MIP_DESCManaged_ToUnManaged(CA_D3D11_PACKED_MIP_DESC^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_PACKED_MIP_DESC* EstruturaRetorno = CriarEstrutura<D3D11_PACKED_MIP_DESC>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_PACKED_MIP_DESC));

				//Preenche os dados da estrutura.
				EstruturaRetorno->NumPackedMips = Param_Estrutura->NumPackedMips;
				EstruturaRetorno->NumStandardMips = Param_Estrutura->NumStandardMips;
				EstruturaRetorno->NumTilesForPackedMips = Param_Estrutura->NumTilesForPackedMips;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_PACKED_MIP_DESC) para sua correspondencia gerenciada(CA_D3D11_PACKED_MIP_DESC).
			CA_D3D11_PACKED_MIP_DESC^ ConverterD3D11_PACKED_MIP_DESCUnManaged_ToManaged(D3D11_PACKED_MIP_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_PACKED_MIP_DESC^ EstruturaRetorno = gcnew CA_D3D11_PACKED_MIP_DESC();

				//Preenche os dados da estrutura.
				EstruturaRetorno->NumPackedMips = Param_Estrutura->NumPackedMips;
				EstruturaRetorno->NumStandardMips = Param_Estrutura->NumStandardMips;
				EstruturaRetorno->NumTilesForPackedMips = Param_Estrutura->NumTilesForPackedMips;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILE_SHAPE) para sua correspondencia não gerenciada(D3D11_TILE_SHAPE).
			D3D11_TILE_SHAPE* ConverterD3D11_TILE_SHAPEManaged_ToUnManaged(CA_D3D11_TILE_SHAPE^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_TILE_SHAPE* EstruturaRetorno = CriarEstrutura<D3D11_TILE_SHAPE>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_TILE_SHAPE));

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTexels = Param_Estrutura->DepthInTexels;
				EstruturaRetorno->HeightInTexels = Param_Estrutura->HeightInTexels;
				EstruturaRetorno->WidthInTexels = Param_Estrutura->WidthInTexels;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_TILE_SHAPE) para sua correspondencia gerenciada(CA_D3D11_TILE_SHAPE).
			CA_D3D11_TILE_SHAPE^ ConverterD3D11_TILE_SHAPEUnManaged_ToManaged(D3D11_TILE_SHAPE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_TILE_SHAPE^ EstruturaRetorno = gcnew CA_D3D11_TILE_SHAPE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTexels = Param_Estrutura->DepthInTexels;
				EstruturaRetorno->HeightInTexels = Param_Estrutura->HeightInTexels;
				EstruturaRetorno->WidthInTexels = Param_Estrutura->WidthInTexels;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SUBRESOURCE_TILING) para sua correspondencia não gerenciada(D3D11_SUBRESOURCE_TILING).
			D3D11_SUBRESOURCE_TILING* ConverterD3D11_SUBRESOURCE_TILINGManaged_ToUnManaged(CA_D3D11_SUBRESOURCE_TILING^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				D3D11_SUBRESOURCE_TILING* EstruturaRetorno = CriarEstrutura<D3D11_SUBRESOURCE_TILING>();

				//Preenche tudo com zero e inicializa as estruturas contidas no union.
				ZeroMemory(EstruturaRetorno, sizeof(D3D11_SUBRESOURCE_TILING));

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTiles = Param_Estrutura->DepthInTiles;
				EstruturaRetorno->HeightInTiles = Param_Estrutura->HeightInTiles;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;
				EstruturaRetorno->WidthInTiles = Param_Estrutura->WidthInTiles;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_SUBRESOURCE_TILING) para sua correspondencia gerenciada(CA_D3D11_SUBRESOURCE_TILING).
			CA_D3D11_SUBRESOURCE_TILING^ ConverterD3D11_SUBRESOURCE_TILINGUnManaged_ToManaged(D3D11_SUBRESOURCE_TILING* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_D3D11_SUBRESOURCE_TILING^ EstruturaRetorno = gcnew CA_D3D11_SUBRESOURCE_TILING();

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTiles = Param_Estrutura->DepthInTiles;
				EstruturaRetorno->HeightInTiles = Param_Estrutura->HeightInTiles;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;
				EstruturaRetorno->WidthInTiles = Param_Estrutura->WidthInTiles;

				//Retorna a variavel.
				return EstruturaRetorno;
			}





			
			///DXGI ESTRUTURAS

			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_FRAME_INFO) para sua correspondencia não gerenciada(DXGI_OUTDUPL_FRAME_INFO).
			DXGI_OUTDUPL_FRAME_INFO* ConverterDXGI_OUTDUPL_FRAME_INFOManaged_ToUnamaged(CA_DXGI_OUTDUPL_FRAME_INFO^ Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				DXGI_OUTDUPL_FRAME_INFO* EstruturaRetorno = CriarEstrutura<DXGI_OUTDUPL_FRAME_INFO>();

				//Define os valores
				EstruturaRetorno->AccumulatedFrames = Param_Estrutura->AccumulatedFrames;
				EstruturaRetorno->LastMouseUpdateTime = { 0 };
				EstruturaRetorno->LastMouseUpdateTime.QuadPart = static_cast<LONGLONG>(Param_Estrutura->LastMouseUpdateTime);
				EstruturaRetorno->LastPresentTime = { 0 };
				EstruturaRetorno->LastPresentTime.QuadPart = static_cast<LONGLONG>(Param_Estrutura->LastPresentTime);
				EstruturaRetorno->PointerShapeBufferSize = Param_Estrutura->PointerShapeBufferSize;
				EstruturaRetorno->ProtectedContentMaskedOut = Param_Estrutura->ProtectedContentMaskedOut ? TRUE : FALSE;
				EstruturaRetorno->RectsCoalesced = Param_Estrutura->RectsCoalesced ? TRUE : FALSE;
				EstruturaRetorno->TotalMetadataBufferSize = Param_Estrutura->TotalMetadataBufferSize;

				//Define as estruturas secundarias
				if (ObjetoGerenciadoValido(Param_Estrutura->PointerPosition))
				{
					//Inicia a estrutura.
					EstruturaRetorno->PointerPosition = { 0 };
					EstruturaRetorno->PointerPosition.Position = { 0 };

					//Define os dados.
					EstruturaRetorno->PointerPosition.Visible = Param_Estrutura->PointerPosition->Visible ? TRUE : FALSE;
					EstruturaRetorno->PointerPosition.Position.x = Param_Estrutura->PointerPosition->Position->X;
					EstruturaRetorno->PointerPosition.Position.y = Param_Estrutura->PointerPosition->Position->Y;
				}

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTDUPL_FRAME_INFO) para sua correspondencia gerenciada(CA_DXGI_OUTDUPL_FRAME_INFO).
			CA_DXGI_OUTDUPL_FRAME_INFO^ ConverterDXGI_OUTDUPL_FRAME_INFOUnamaged_ToManaged(DXGI_OUTDUPL_FRAME_INFO* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				CA_DXGI_OUTDUPL_FRAME_INFO^ EstruturaRetorno = gcnew CA_DXGI_OUTDUPL_FRAME_INFO();

				//Define os valores base.
				EstruturaRetorno->AccumulatedFrames = Param_Estrutura->AccumulatedFrames;
				EstruturaRetorno->LastMouseUpdateTime = static_cast<long long>(Param_Estrutura->LastMouseUpdateTime.QuadPart);
				EstruturaRetorno->LastPresentTime = static_cast<long long>(Param_Estrutura->LastPresentTime.QuadPart);
				EstruturaRetorno->PointerShapeBufferSize = Param_Estrutura->PointerShapeBufferSize;
				EstruturaRetorno->ProtectedContentMaskedOut = Param_Estrutura->ProtectedContentMaskedOut ? true : false;
				EstruturaRetorno->RectsCoalesced = Param_Estrutura->RectsCoalesced ? true : false;
				EstruturaRetorno->TotalMetadataBufferSize = Param_Estrutura->TotalMetadataBufferSize;

				//Cria a estrutura secundaria
				EstruturaRetorno->PointerPosition = gcnew CA_DXGI_OUTDUPL_POINTER_POSITION();
				EstruturaRetorno->PointerPosition->Position = gcnew CA_POINT();

				//Define os dados.
				EstruturaRetorno->PointerPosition->Visible = Param_Estrutura->PointerPosition.Visible ? true : false;
				EstruturaRetorno->PointerPosition->Position->X = Param_Estrutura->PointerPosition.Position.x;
				EstruturaRetorno->PointerPosition->Position->Y = Param_Estrutura->PointerPosition.Position.y;

				//Retorna a estrutura.
				return EstruturaRetorno;
			}
			

			//Converte uma estrutura gerenciada(CA_DXGI_SWAP_CHAIN_DESC) para sua correspondencia não gerenciada(DXGI_SWAP_CHAIN_DESC).
			DXGI_SWAP_CHAIN_DESC* ConverterDXGI_SWAP_CHAIN_DESCManaged_ToUnManaged(CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc)
			{
				//Variavel a ser retornada.
				DXGI_SWAP_CHAIN_DESC* pEstrutura = CriarEstrutura<DXGI_SWAP_CHAIN_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(DXGI_SWAP_CHAIN_DESC));

				//Preenche os dados da estrutura principal.
				pEstrutura->BufferCount = Param_Desc->BufferCount;
				pEstrutura->BufferUsage = static_cast<DXGI_USAGE>(Param_Desc->BufferUsage);
				pEstrutura->Flags = static_cast<UINT>(Param_Desc->Flags);
				pEstrutura->OutputWindow = ConverterIntPtrToHWND(Param_Desc->OutputWindow);
				pEstrutura->SwapEffect = static_cast<DXGI_SWAP_EFFECT>(Param_Desc->SwapEffect);
				pEstrutura->Windowed = Param_Desc->Windowed ? TRUE : FALSE;

				//Preenche os dados das estruturas secundarias
				pEstrutura->SampleDesc.Count = Param_Desc->SampleDesc->Count;
				pEstrutura->SampleDesc.Quality = Param_Desc->SampleDesc->Quality;
				pEstrutura->BufferDesc.Format = static_cast<DXGI_FORMAT>(Param_Desc->BufferDesc->Format);
				pEstrutura->BufferDesc.Height = Param_Desc->BufferDesc->Height;
				pEstrutura->BufferDesc.Width = Param_Desc->BufferDesc->Width;
				pEstrutura->BufferDesc.Scaling = static_cast<DXGI_MODE_SCALING>(Param_Desc->BufferDesc->Scaling);
				pEstrutura->BufferDesc.ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>(Param_Desc->BufferDesc->ScanlineOrdering);
				pEstrutura->BufferDesc.RefreshRate.Denominator = Param_Desc->BufferDesc->RefreshRate->Denominador;
				pEstrutura->BufferDesc.RefreshRate.Numerator = Param_Desc->BufferDesc->RefreshRate->Numerador;

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(DXGI_SWAP_CHAIN_DESC) para sua correspondencia gerenciada(CA_DXGI_SWAP_CHAIN_DESC).
			CA_DXGI_SWAP_CHAIN_DESC^ ConverterDXGI_SWAP_CHAIN_DESCUnManaged_ToManaged(DXGI_SWAP_CHAIN_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_DXGI_SWAP_CHAIN_DESC^ pEstrutura = gcnew CA_DXGI_SWAP_CHAIN_DESC();

				//Preenche os dados da estrutura.
				pEstrutura->BufferCount = Param_Desc->BufferCount;
				pEstrutura->BufferUsage = static_cast<SDKBase::Enumeracoes::CA_DXGI_USAGE>(Param_Desc->BufferUsage);
				pEstrutura->Flags = static_cast<SDKBase::Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG>(Param_Desc->Flags);
				pEstrutura->OutputWindow = ConverterHWNDToIntPtr(Param_Desc->OutputWindow);
				pEstrutura->SwapEffect = static_cast<SDKBase::Enumeracoes::CA_DXGI_SWAP_EFFECT>(Param_Desc->SwapEffect);
				pEstrutura->Windowed = Param_Desc->Windowed ? true : false;

				//Cria as estruturas secundarias.
				pEstrutura->SampleDesc = gcnew CA_DXGI_SAMPLE_DESC();
				pEstrutura->BufferDesc = gcnew CA_DXGI_MODE_DESC();
				pEstrutura->BufferDesc->RefreshRate = gcnew CA_DXGI_RATIONAL();

				//Preenche os dados das estruturas secundarias
				pEstrutura->SampleDesc->Count = Param_Desc->SampleDesc.Count;
				pEstrutura->SampleDesc->Quality = Param_Desc->SampleDesc.Quality;
				pEstrutura->BufferDesc->Format = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Desc->BufferDesc.Format);
				pEstrutura->BufferDesc->Height = Param_Desc->BufferDesc.Height;
				pEstrutura->BufferDesc->Width = Param_Desc->BufferDesc.Width;
				pEstrutura->BufferDesc->Scaling = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCALING>(Param_Desc->BufferDesc.Scaling);
				pEstrutura->BufferDesc->ScanlineOrdering = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER>(Param_Desc->BufferDesc.ScanlineOrdering);
				pEstrutura->BufferDesc->RefreshRate->Denominador = Param_Desc->BufferDesc.RefreshRate.Denominator;
				pEstrutura->BufferDesc->RefreshRate->Numerador = Param_Desc->BufferDesc.RefreshRate.Numerator;

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_SWAP_CHAIN_DESC1) para sua correspondencia não gerenciada(DXGI_SWAP_CHAIN_DESC1).
			DXGI_SWAP_CHAIN_DESC1* ConverterDXGI_SWAP_CHAIN_DESC1Managed_ToUnManaged(CA_DXGI_SWAP_CHAIN_DESC1^ Param_Desc)
			{
				//Variavel a ser retornada.
				DXGI_SWAP_CHAIN_DESC1* pEstrutura = CriarEstrutura<DXGI_SWAP_CHAIN_DESC1>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(DXGI_SWAP_CHAIN_DESC1));

				//Preenche os dados da estrutura principal.
				pEstrutura->Format = static_cast<DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->Height = Param_Desc->Height;
				pEstrutura->Width = Param_Desc->Width;
				pEstrutura->Stereo = Param_Desc->Stereo ? TRUE : FALSE;
				pEstrutura->BufferCount = Param_Desc->BufferCount;
				pEstrutura->BufferUsage = static_cast<DXGI_USAGE>(Param_Desc->BufferUsage);
				pEstrutura->SwapEffect = static_cast<DXGI_SWAP_EFFECT>(Param_Desc->SwapEffect);
				pEstrutura->AlphaMode = static_cast<DXGI_ALPHA_MODE>(Param_Desc->AlphaMode);
				pEstrutura->Flags = static_cast<UINT>(Param_Desc->Flags);
				pEstrutura->Scaling = static_cast<DXGI_SCALING>(Param_Desc->Scaling);

				//Verifica se a estrutura é valida e preenche os dados na nativa.
				if (ObjetoGerenciadoValido(Param_Desc->SampleDesc))
				{
					//Preenche os dados da estrutura.
					pEstrutura->SampleDesc.Count = Param_Desc->SampleDesc->Count;
					pEstrutura->SampleDesc.Quality = Param_Desc->SampleDesc->Quality;
				}

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(DXGI_SWAP_CHAIN_DESC1) para sua correspondencia gerenciada(CA_DXGI_SWAP_CHAIN_DESC1).
			CA_DXGI_SWAP_CHAIN_DESC1^ ConverterDXGI_SWAP_CHAIN_DESC1UnManaged_ToManaged(DXGI_SWAP_CHAIN_DESC1* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_DXGI_SWAP_CHAIN_DESC1^ pEstrutura = gcnew CA_DXGI_SWAP_CHAIN_DESC1();

				//Preenche os dados da estrutura.
				pEstrutura->Format = static_cast<CA_DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->Height = Param_Desc->Height;
				pEstrutura->Width = Param_Desc->Width;
				pEstrutura->Stereo = Param_Desc->Stereo ? TRUE : FALSE;
				pEstrutura->BufferCount = Param_Desc->BufferCount;
				pEstrutura->BufferUsage = static_cast<CA_DXGI_USAGE>(Param_Desc->BufferUsage);
				pEstrutura->SwapEffect = static_cast<CA_DXGI_SWAP_EFFECT>(Param_Desc->SwapEffect);
				pEstrutura->AlphaMode = static_cast<CA_DXGI_ALPHA_MODE>(Param_Desc->AlphaMode);
				pEstrutura->Flags = static_cast<CA_DXGI_SWAP_CHAIN_FLAG>(Param_Desc->Flags);
				pEstrutura->Scaling = static_cast<CA_DXGI_SCALING>(Param_Desc->Scaling);

				//Cria a estrutura do SampleDesc.
				pEstrutura->SampleDesc = gcnew CA_DXGI_SAMPLE_DESC();

				//Preenche os dados da estrutura.
				pEstrutura->SampleDesc->Count = Param_Desc->SampleDesc.Count;
				pEstrutura->SampleDesc->Quality = Param_Desc->SampleDesc.Quality;

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC) para sua correspondencia não gerenciada(DXGI_SWAP_CHAIN_FULLSCREEN_DESC).
			DXGI_SWAP_CHAIN_FULLSCREEN_DESC* ConverterDXGI_SWAP_CHAIN_FULLSCREEN_DESCManaged_ToUnManaged(CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_Desc)
			{
				//Variavel a ser retornada.
				DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pEstrutura = CriarEstrutura<DXGI_SWAP_CHAIN_FULLSCREEN_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));

				//Preenche os dados da estrutura principal.
				pEstrutura->ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>(Param_Desc->ScanlineOrdering);
				pEstrutura->Scaling = static_cast<DXGI_MODE_SCALING>(Param_Desc->Scaling);
				pEstrutura->Windowed = Param_Desc->Windowed ? TRUE : FALSE;

				//Verifica se forneceu a estrutura do Refresh Rate.
				if (ObjetoGerenciadoValido(Param_Desc->RefreshRate))
				{
					//Preenche os dados da estrutura na nativa.
					pEstrutura->RefreshRate.Denominator = Param_Desc->RefreshRate->Denominador;
					pEstrutura->RefreshRate.Numerator = Param_Desc->RefreshRate->Numerador;
				}

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(DXGI_SWAP_CHAIN_FULLSCREEN_DESC) para sua correspondencia gerenciada(CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC).
			CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ ConverterDXGI_SWAP_CHAIN_FULLSCREEN_DESCUnManaged_ToManaged(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ pEstrutura = gcnew CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC();

				//Preenche os dados da estrutura.
				pEstrutura->ScanlineOrdering = static_cast<CA_DXGI_MODE_SCANLINE_ORDER>(Param_Desc->ScanlineOrdering);
				pEstrutura->Scaling = static_cast<CA_DXGI_MODE_SCALING>(Param_Desc->Scaling);
				pEstrutura->Windowed = Param_Desc->Windowed ? true : false;

				//Cria a estrutura do Refresh rate
				pEstrutura->RefreshRate = gcnew CA_DXGI_RATIONAL();

				//Preenche os dados da estrutura.
				pEstrutura->RefreshRate->Denominador = Param_Desc->RefreshRate.Denominator;
				pEstrutura->RefreshRate->Numerador = Param_Desc->RefreshRate.Numerator;

				//Retorna
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_FRAME_STATISTICS) para sua correspondencia não gerenciada(DXGI_FRAME_STATISTICS).
			DXGI_FRAME_STATISTICS* ConverterDXGI_FRAME_STATISTICSManaged_ToUnManaged(CA_DXGI_FRAME_STATISTICS^ Param_Desc)
			{
				//Variavel a ser retornada.
				DXGI_FRAME_STATISTICS* pEstrutura = CriarEstrutura<DXGI_FRAME_STATISTICS>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(DXGI_FRAME_STATISTICS));

				//Preenche os dados da estrutura principal.
				pEstrutura->PresentCount = Param_Desc->PresentCount;
				pEstrutura->PresentRefreshCount = Param_Desc->PresentRefreshCount;
				pEstrutura->SyncGPUTime.QuadPart = Param_Desc->SyncGPUTime;
				pEstrutura->SyncQPCTime.QuadPart = Param_Desc->SyncQPCTime;
				pEstrutura->SyncRefreshCount = Param_Desc->SyncRefreshCount;

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(DXGI_FRAME_STATISTICS) para sua correspondencia gerenciada(CA_DXGI_FRAME_STATISTICS).
			CA_DXGI_FRAME_STATISTICS^ ConverterDXGI_FRAME_STATISTICSUnManaged_ToManaged(DXGI_FRAME_STATISTICS* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_DXGI_FRAME_STATISTICS^ pEstrutura = gcnew CA_DXGI_FRAME_STATISTICS();

				//Preenche os dados da estrutura.
				pEstrutura->PresentCount = Param_Desc->PresentCount;
				pEstrutura->PresentRefreshCount = Param_Desc->PresentRefreshCount;
				pEstrutura->SyncGPUTime = Param_Desc->SyncGPUTime.QuadPart;
				pEstrutura->SyncQPCTime = Param_Desc->SyncQPCTime.QuadPart;
				pEstrutura->SyncRefreshCount = Param_Desc->SyncRefreshCount;

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_DESC) para sua correspondencia não gerenciada(DXGI_OUTDUPL_DESC).
			DXGI_OUTDUPL_DESC* ConverterDXGI_OUTDUPL_DESCManaged_ToUnManaged(CA_DXGI_OUTDUPL_DESC^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_OUTDUPL_DESC* EstruturaRetorno = CriarEstrutura<DXGI_OUTDUPL_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_OUTDUPL_DESC));

				//Variaveis
				DXGI_MODE_DESC* pDxgiModeDesc = NULL;

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DesktopImageInSystemMemory = static_cast<BOOL>(Param_Estrutura->DesktopImageInSystemMemory);
				EstruturaRetorno->Rotation = static_cast<DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);

				//Verifica se a estrutura secundaria é valida e converte os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->ModeDesc))
				{
					//Converte a estrutura.
					pDxgiModeDesc = ConverterDXGI_MODE_DESCManaged_ToUnManaged(Param_Estrutura->ModeDesc);

					//Obtém uma copia dos dados.
					memcpy_s(&EstruturaRetorno->ModeDesc, sizeof(DXGI_MODE_DESC), pDxgiModeDesc, sizeof(DXGI_MODE_DESC));
				}

				//Libera a memória da estrutura convertida temporariamente.
				DeletarEstruturaSafe(&pDxgiModeDesc);

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTDUPL_DESC) para sua correspondencia gerenciada(CA_DXGI_OUTDUPL_DESC).
			CA_DXGI_OUTDUPL_DESC^ ConverterDXGI_OUTDUPL_DESCUnManaged_ToManaged(DXGI_OUTDUPL_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_OUTDUPL_DESC^ EstruturaRetorno = gcnew CA_DXGI_OUTDUPL_DESC();

				//Preenche os dados da estrutura.
				EstruturaRetorno->Rotation = static_cast<CA_DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);
				EstruturaRetorno->DesktopImageInSystemMemory = static_cast<bool>(Param_Estrutura->DesktopImageInSystemMemory);

				//Cria a estrutura e preenche os seus dados.
				EstruturaRetorno->ModeDesc = ConverterDXGI_MODE_DESCUnManaged_ToManaged(&Param_Estrutura->ModeDesc);
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_MOVE_RECT) para sua correspondencia não gerenciada(DXGI_OUTDUPL_MOVE_RECT).
			DXGI_OUTDUPL_MOVE_RECT* ConverterDXGI_OUTDUPL_MOVE_RECTManaged_ToUnManaged(CA_DXGI_OUTDUPL_MOVE_RECT^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_OUTDUPL_MOVE_RECT* EstruturaRetorno = CriarEstrutura<DXGI_OUTDUPL_MOVE_RECT>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_OUTDUPL_MOVE_RECT));

				//Verifica se as estruturas são validas e define os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->DestinationRect))
				{
					//Inicia a estrutura.
					EstruturaRetorno->DestinationRect = { 0 };

					//Define os dados.
					EstruturaRetorno->DestinationRect.left = Param_Estrutura->DestinationRect->Esquerda;
					EstruturaRetorno->DestinationRect.right = Param_Estrutura->DestinationRect->Direita;
					EstruturaRetorno->DestinationRect.top = Param_Estrutura->DestinationRect->Topo;
					EstruturaRetorno->DestinationRect.bottom = Param_Estrutura->DestinationRect->Fundo;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->SourcePoint))
				{
					//Inicia a estrutura.
					EstruturaRetorno->SourcePoint = { 0 };

					//Define os dados.
					EstruturaRetorno->SourcePoint.x = Param_Estrutura->SourcePoint->X;
					EstruturaRetorno->SourcePoint.y = Param_Estrutura->SourcePoint->Y;
				}

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTDUPL_MOVE_RECT) para sua correspondencia gerenciada(CA_DXGI_OUTDUPL_MOVE_RECT).
			CA_DXGI_OUTDUPL_MOVE_RECT^ ConverterDXGI_OUTDUPL_MOVE_RECTUnManaged_ToManaged(DXGI_OUTDUPL_MOVE_RECT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_OUTDUPL_MOVE_RECT^ EstruturaRetorno = gcnew CA_DXGI_OUTDUPL_MOVE_RECT();

				//Cria as estruturas secundarias
				EstruturaRetorno->DestinationRect = gcnew CA_RECT();
				EstruturaRetorno->SourcePoint = gcnew CA_POINT();

				//Define os dados na estrutura de destino do retangulo.
				EstruturaRetorno->DestinationRect->Direita = Param_Estrutura->DestinationRect.right;
				EstruturaRetorno->DestinationRect->Esquerda = Param_Estrutura->DestinationRect.left;
				EstruturaRetorno->DestinationRect->Topo = Param_Estrutura->DestinationRect.top;
				EstruturaRetorno->DestinationRect->Fundo = Param_Estrutura->DestinationRect.bottom;

				//Define os dados na estrutura de ponto
				EstruturaRetorno->SourcePoint->X = Param_Estrutura->SourcePoint.x;
				EstruturaRetorno->SourcePoint->Y = Param_Estrutura->SourcePoint.y;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO) para sua correspondencia não gerenciada(DXGI_OUTDUPL_POINTER_SHAPE_INFO).
			DXGI_OUTDUPL_POINTER_SHAPE_INFO* ConverterDXGI_OUTDUPL_POINTER_SHAPE_INFOManaged_ToUnManaged(CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_OUTDUPL_POINTER_SHAPE_INFO* EstruturaRetorno = CriarEstrutura<DXGI_OUTDUPL_POINTER_SHAPE_INFO>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_OUTDUPL_POINTER_SHAPE_INFO));

				//Define os dados na estrutura.
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Pitch = Param_Estrutura->Pitch;
				EstruturaRetorno->Type = static_cast<UINT>(Param_Estrutura->Type);

				//Verifica se a estrutura é valida e define na estrutura de retorno
				if (ObjetoGerenciadoValido(Param_Estrutura->HotSpot))
				{
					//Inicializa a estrutura.
					EstruturaRetorno->HotSpot = { 0 };
					EstruturaRetorno->HotSpot.x = Param_Estrutura->HotSpot->X;
					EstruturaRetorno->HotSpot.y = Param_Estrutura->HotSpot->Y;
				}


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTDUPL_POINTER_SHAPE_INFO) para sua correspondencia gerenciada(CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO).
			CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ ConverterDXGI_OUTDUPL_POINTER_SHAPE_INFOUnManaged_ToManaged(DXGI_OUTDUPL_POINTER_SHAPE_INFO* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ EstruturaRetorno = gcnew CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO();



				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MODE_DESC) para sua correspondencia não gerenciada(DXGI_MODE_DESC).
			DXGI_MODE_DESC* ConverterDXGI_MODE_DESCManaged_ToUnManaged(CA_DXGI_MODE_DESC^ Param_Desc)
			{
				//Variavel a ser retornada.
				DXGI_MODE_DESC* pEstrutura = CriarEstrutura<DXGI_MODE_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(pEstrutura, sizeof(DXGI_MODE_DESC));

				//Preenche os dados da estrutura principal.
				pEstrutura->Format = static_cast<DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->Height = Param_Desc->Height;
				pEstrutura->Width = Param_Desc->Width;
				pEstrutura->RefreshRate.Denominator = Param_Desc->RefreshRate->Denominador;
				pEstrutura->RefreshRate.Numerator = Param_Desc->RefreshRate->Numerador;
				pEstrutura->Scaling = static_cast<DXGI_MODE_SCALING>(Param_Desc->Scaling);
				pEstrutura->ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>(Param_Desc->ScanlineOrdering);

				//Retorna
				return pEstrutura;
			}

			//Converte uma estrutura não gerenciada(DXGI_MODE_DESC) para sua correspondencia gerenciada(CA_DXGI_MODE_DESC).
			CA_DXGI_MODE_DESC^ ConverterDXGI_MODE_DESCUnManaged_ToManaged(DXGI_MODE_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				CA_DXGI_MODE_DESC^ pEstrutura = gcnew CA_DXGI_MODE_DESC();

				//Preenche os dados da estrutura principal.
				pEstrutura->Format = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Desc->Format);
				pEstrutura->Height = Param_Desc->Height;
				pEstrutura->Width = Param_Desc->Width;
				pEstrutura->RefreshRate->Denominador = Param_Desc->RefreshRate.Denominator;
				pEstrutura->RefreshRate->Numerador = Param_Desc->RefreshRate.Numerator;
				pEstrutura->Scaling = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCALING>(Param_Desc->Scaling);
				pEstrutura->ScanlineOrdering = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER>(Param_Desc->ScanlineOrdering);

				//Retorna a variavel.
				return pEstrutura;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MODE_DESC1) para sua correspondencia não gerenciada(DXGI_MODE_DESC1).
			DXGI_MODE_DESC1* ConverterDXGI_MODE_DESC1Managed_ToUnManaged(CA_DXGI_MODE_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_MODE_DESC1* EstruturaRetorno = CriarEstrutura<DXGI_MODE_DESC1>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_MODE_DESC1));

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->RefreshRate.Denominator = Param_Estrutura->RefreshRate->Denominador;
				EstruturaRetorno->RefreshRate.Numerator = Param_Estrutura->RefreshRate->Numerador;
				EstruturaRetorno->Scaling = static_cast<DXGI_MODE_SCALING>(Param_Estrutura->Scaling);
				EstruturaRetorno->ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>(Param_Estrutura->ScanlineOrdering);
				EstruturaRetorno->Stereo = static_cast<BOOL>(Param_Estrutura->Stereo);

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_MODE_DESC1) para sua correspondencia gerenciada(CA_DXGI_MODE_DESC1).
			CA_DXGI_MODE_DESC1^ ConverterDXGI_MODE_DESC1UnManaged_ToManaged(DXGI_MODE_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_MODE_DESC1^ EstruturaRetorno = gcnew CA_DXGI_MODE_DESC1();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Format = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->RefreshRate->Denominador = Param_Estrutura->RefreshRate.Denominator;
				EstruturaRetorno->RefreshRate->Numerador = Param_Estrutura->RefreshRate.Numerator;
				EstruturaRetorno->Scaling = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCALING>(Param_Estrutura->Scaling);
				EstruturaRetorno->ScanlineOrdering = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER>(Param_Estrutura->ScanlineOrdering);
				EstruturaRetorno->Stereo = static_cast<Boolean>(Param_Estrutura->Stereo);

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_RGB) para sua correspondencia não gerenciada(DXGI_RGB).
			DXGI_RGB* ConverterDXGI_RGBManaged_ToUnManaged(CA_DXGI_RGB^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_RGB* EstruturaRetorno = CriarEstrutura<DXGI_RGB>();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Red = Param_Estrutura->Vermelho;
				EstruturaRetorno->Green = Param_Estrutura->Verde;
				EstruturaRetorno->Blue = Param_Estrutura->Azul;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_RGB) para sua correspondencia gerenciada(CA_DXGI_RGB).
			CA_DXGI_RGB^ ConverterDXGI_RGBUnManaged_ToManaged(DXGI_RGB* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_RGB^ EstruturaRetorno = gcnew CA_DXGI_RGB();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Vermelho = Param_Estrutura->Red;
				EstruturaRetorno->Verde = Param_Estrutura->Green;
				EstruturaRetorno->Azul = Param_Estrutura->Blue;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_RGBA) para sua correspondencia não gerenciada(DXGI_RGBA).
			DXGI_RGBA* ConverterDXGI_RGBAManaged_ToUnManaged(CA_DXGI_RGBA^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_RGBA* EstruturaRetorno = CriarEstrutura<DXGI_RGBA>();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->r = Param_Estrutura->Vermelho;
				EstruturaRetorno->g = Param_Estrutura->Verde;
				EstruturaRetorno->b = Param_Estrutura->Azul;
				EstruturaRetorno->a = Param_Estrutura->Alfa;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_RGBA) para sua correspondencia gerenciada(CA_DXGI_RGBA).
			CA_DXGI_RGBA^ ConverterDXGI_RGBAUnManaged_ToManaged(DXGI_RGBA* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_RGBA^ EstruturaRetorno = gcnew CA_DXGI_RGBA();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Vermelho = Param_Estrutura->r;
				EstruturaRetorno->Verde = Param_Estrutura->g;
				EstruturaRetorno->Azul = Param_Estrutura->b;
				EstruturaRetorno->Alfa = Param_Estrutura->a;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_GAMMA_CONTROL) para sua correspondencia não gerenciada(DXGI_GAMMA_CONTROL).
			DXGI_GAMMA_CONTROL* ConverterDXGI_GAMMA_CONTROLManaged_ToUnManaged(CA_DXGI_GAMMA_CONTROL^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_GAMMA_CONTROL* EstruturaRetorno = CriarEstrutura<DXGI_GAMMA_CONTROL>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_GAMMA_CONTROL));

				//Preenche os dados da estrutura
				if (ObjetoGerenciadoValido(Param_Estrutura->Offset))
				{
					//Cria a estrutura com os dados.
					EstruturaRetorno->Offset.Red = Param_Estrutura->Offset->Vermelho;
					EstruturaRetorno->Offset.Green = Param_Estrutura->Offset->Verde;
					EstruturaRetorno->Offset.Blue = Param_Estrutura->Offset->Azul;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->Scale))
				{
					//Cria a estrutura com os dados.
					EstruturaRetorno->Scale.Red = Param_Estrutura->Scale->Vermelho;
					EstruturaRetorno->Scale.Green = Param_Estrutura->Scale->Verde;
					EstruturaRetorno->Scale.Blue = Param_Estrutura->Scale->Azul;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->GammaCurve))
				{
					//Esse valor é fixo para o membro (GammaCurve)
					int CountLengGamma = 1025;

					//Copia os dados para a estrutura.
					for (int i = 0; i < CountLengGamma; i++)
					{
						//Define os dados na estrutura.
						EstruturaRetorno->GammaCurve[i].Red = Param_Estrutura->GammaCurve[i]->Vermelho;
						EstruturaRetorno->GammaCurve[i].Green = Param_Estrutura->GammaCurve[i]->Verde;
						EstruturaRetorno->GammaCurve[i].Blue = Param_Estrutura->GammaCurve[i]->Azul;
					}
				}

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_GAMMA_CONTROL) para sua correspondencia gerenciada(CA_DXGI_GAMMA_CONTROL).
			CA_DXGI_GAMMA_CONTROL^ ConverterDXGI_GAMMA_CONTROLUnManaged_ToManaged(DXGI_GAMMA_CONTROL* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_GAMMA_CONTROL^ EstruturaRetorno = gcnew CA_DXGI_GAMMA_CONTROL();

				//Esse valor é fixo segundo a MSDN.
				int LengCountGamma = 1025;

				//Inicializa o array
				EstruturaRetorno->GammaCurve = gcnew cli::array<CA_DXGI_RGB^>(LengCountGamma);

				//Copia os dados da estrutura principal.
				for (int i = 0; i < LengCountGamma; i++)
				{
					//Define os dados na estrutura.
					EstruturaRetorno->GammaCurve[i]->Vermelho = Param_Estrutura->GammaCurve[i].Red;
					EstruturaRetorno->GammaCurve[i]->Verde = Param_Estrutura->GammaCurve[i].Green;
					EstruturaRetorno->GammaCurve[i]->Azul = Param_Estrutura->GammaCurve[i].Blue;
				}

				//Cria as estruturas secundarias.
				EstruturaRetorno->Offset = gcnew CA_DXGI_RGB();
				EstruturaRetorno->Scale = gcnew CA_DXGI_RGB();

				//Define os dados das estruturas secundarias.
				EstruturaRetorno->Offset->Vermelho = Param_Estrutura->Offset.Red;
				EstruturaRetorno->Offset->Verde = Param_Estrutura->Offset.Green;
				EstruturaRetorno->Offset->Azul = Param_Estrutura->Offset.Blue;

				EstruturaRetorno->Scale->Vermelho = Param_Estrutura->Scale.Red;
				EstruturaRetorno->Scale->Verde = Param_Estrutura->Scale.Green;
				EstruturaRetorno->Scale->Azul = Param_Estrutura->Scale.Blue;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTPUT_DESC) para sua correspondencia não gerenciada(DXGI_OUTPUT_DESC).
			DXGI_OUTPUT_DESC* ConverterDXGI_OUTPUT_DESCManaged_ToUnManaged(CA_DXGI_OUTPUT_DESC^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_OUTPUT_DESC* EstruturaRetorno = CriarEstrutura<DXGI_OUTPUT_DESC>();
				int LarguraNomeDispositivo = Param_Estrutura->DeviceName->Length;

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_OUTPUT_DESC));

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->AttachedToDesktop = Param_Estrutura->AttachedToDesktop ? TRUE : FALSE;
				EstruturaRetorno->Rotation = static_cast<DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);
				EstruturaRetorno->DeviceName[32]; //Inicia o array de WCHAR. O valor 32 é fixo segundo a documentação. 
			
				//Abre um for para definir o nome do dispositivo.
				for (int i = 0; i < LarguraNomeDispositivo; i++)   //32 É o valor fixo para a variavel.
				{
					//Define o wchar_t no nome do dispostivo.
					EstruturaRetorno->DeviceName[i] = Param_Estrutura->DeviceName[i];
				}
				//Define o código de finalização da matriz.
				EstruturaRetorno->DeviceName[LarguraNomeDispositivo + 1] = '\0';

				//Recupera o monitor se valido
				if (ObjetoGerenciadoValido(Param_Estrutura->Monitor))
				{
					//Recupera o ponteiro para o monitor.
					Param_Estrutura->Monitor->RecuperarObjeto(&EstruturaRetorno->Monitor);
				}

				//Preenche a estrutura secundaria se valida
				if (ObjetoGerenciadoValido(Param_Estrutura->DesktopCoordinates))
				{
					//Preenche os dados.
					EstruturaRetorno->DesktopCoordinates.top = Param_Estrutura->DesktopCoordinates->Topo;
					EstruturaRetorno->DesktopCoordinates.bottom = Param_Estrutura->DesktopCoordinates->Fundo;
					EstruturaRetorno->DesktopCoordinates.right = Param_Estrutura->DesktopCoordinates->Direita;
					EstruturaRetorno->DesktopCoordinates.left = Param_Estrutura->DesktopCoordinates->Esquerda;
				}

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTPUT_DESC) para sua correspondencia gerenciada(CA_DXGI_OUTPUT_DESC).
			CA_DXGI_OUTPUT_DESC^ ConverterDXGI_OUTPUT_DESCUnManaged_ToManaged(DXGI_OUTPUT_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_OUTPUT_DESC^ EstruturaRetorno = gcnew CA_DXGI_OUTPUT_DESC();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->AttachedToDesktop = Param_Estrutura->AttachedToDesktop ? true : false;
				EstruturaRetorno->DeviceName = gcnew String(Param_Estrutura->DeviceName);
				EstruturaRetorno->Rotation = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);

				//Verifica se o Monitor é valido e cria a interface e define o ponteiro.
				if (ObjetoValido(Param_Estrutura->Monitor))
				{
					//Cria a classe do monitor.
					EstruturaRetorno->Monitor = gcnew CarenHMONITOR();

					//Define o ponteiro.
					EstruturaRetorno->Monitor->SetObject(Param_Estrutura->Monitor);
				}

				//Cria e preenche a estrutura secundaria.
				EstruturaRetorno->DesktopCoordinates = gcnew CA_RECT();

				//Define as coordenadas
				EstruturaRetorno->DesktopCoordinates->Topo = Param_Estrutura->DesktopCoordinates.top;
				EstruturaRetorno->DesktopCoordinates->Fundo = Param_Estrutura->DesktopCoordinates.bottom;
				EstruturaRetorno->DesktopCoordinates->Direita = Param_Estrutura->DesktopCoordinates.right;
				EstruturaRetorno->DesktopCoordinates->Esquerda = Param_Estrutura->DesktopCoordinates.left;


				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTPUT_DESC1) para sua correspondencia não gerenciada(DXGI_OUTPUT_DESC1).
			DXGI_OUTPUT_DESC1* ConverterDXGI_OUTPUT_DESC1Managed_ToUnManaged(CA_DXGI_OUTPUT_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_OUTPUT_DESC1* EstruturaRetorno = CriarEstrutura<DXGI_OUTPUT_DESC1>();
				int LarguraNomeDispositivo = Param_Estrutura->DeviceName->Length;
				HMONITOR pMonitor = NULL;

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_OUTPUT_DESC1));

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->AttachedToDesktop = Param_Estrutura->AttachedToDesktop ? TRUE : FALSE;
				EstruturaRetorno->Rotation = static_cast<DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);
				EstruturaRetorno->BitsPerColor = static_cast<UINT>(Param_Estrutura->BitsPerColor);
				EstruturaRetorno->ColorSpace = static_cast<DXGI_COLOR_SPACE_TYPE>(Param_Estrutura->ColorSpace);
				EstruturaRetorno->MinLuminance = Param_Estrutura->MinLuminance;
				EstruturaRetorno->MaxLuminance = Param_Estrutura->MaxLuminance;
				EstruturaRetorno->MaxLuminance = Param_Estrutura->MaxFullFrameLuminance;
				EstruturaRetorno->DeviceName[32]; //Inicia o array de WCHAR. O valor 32 é fixo segundo a documentação. 

				//Abre um for para definir o nome do dispositivo.
				for (int i = 0; i < LarguraNomeDispositivo; i++)   //32 É o valor fixo para a variavel.
				{
					//Define o wchar_t no nome do dispostivo.
					EstruturaRetorno->DeviceName[i] = Param_Estrutura->DeviceName[i];
				}
		
				//Define o código de finalização da matriz.
				EstruturaRetorno->DeviceName[LarguraNomeDispositivo + 1] = '\0';

				//Copia as matrizes.

				//Verifica as matrizes validas e define os valores
				if (ObjetoGerenciadoValido(Param_Estrutura->RedPrimary))
				{
					//Preenche os dados.
					EstruturaRetorno->RedPrimary[0] = Param_Estrutura->RedPrimary[0];
					EstruturaRetorno->RedPrimary[1] = Param_Estrutura->RedPrimary[1];
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->GreenPrimary))
				{
					//Preenche os dados.
					EstruturaRetorno->GreenPrimary[0] = Param_Estrutura->GreenPrimary[0];
					EstruturaRetorno->GreenPrimary[1] = Param_Estrutura->GreenPrimary[1];
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->BluePrimary))
				{
					//Preenche os dados.
					EstruturaRetorno->BluePrimary[0] = Param_Estrutura->BluePrimary[0];
					EstruturaRetorno->BluePrimary[1] = Param_Estrutura->BluePrimary[1];
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->WhitePoint))
				{
					//Preenche os dados.
					EstruturaRetorno->WhitePoint[0] = Param_Estrutura->WhitePoint[0];
					EstruturaRetorno->WhitePoint[1] = Param_Estrutura->WhitePoint[1];
				}


				//Recupera o monitor se valido
				if (ObjetoGerenciadoValido(Param_Estrutura->Monitor))
				{
					//Recupera o ponteiro para o monitor e define na estrutura.
					Param_Estrutura->Monitor->RecuperarObjeto(&EstruturaRetorno->Monitor);			
				}

				//Preenche a estrutura secundaria se valida
				if (ObjetoGerenciadoValido(Param_Estrutura->DesktopCoordinates))
				{
					//Inicia a estrutura.
					EstruturaRetorno->DesktopCoordinates = { 0 };

					//Preenche os dados.
					EstruturaRetorno->DesktopCoordinates.top = Param_Estrutura->DesktopCoordinates->Topo;
					EstruturaRetorno->DesktopCoordinates.bottom = Param_Estrutura->DesktopCoordinates->Fundo;
					EstruturaRetorno->DesktopCoordinates.right = Param_Estrutura->DesktopCoordinates->Direita;
					EstruturaRetorno->DesktopCoordinates.left = Param_Estrutura->DesktopCoordinates->Esquerda;
				}

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_OUTPUT_DESC1) para sua correspondencia gerenciada(CA_DXGI_OUTPUT_DESC1).
			CA_DXGI_OUTPUT_DESC1^ ConverterDXGI_OUTPUT_DESC1UnManaged_ToManaged(DXGI_OUTPUT_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_OUTPUT_DESC1^ EstruturaRetorno = gcnew CA_DXGI_OUTPUT_DESC1();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->AttachedToDesktop = Param_Estrutura->AttachedToDesktop ? true : false;
				EstruturaRetorno->DeviceName = gcnew String(Param_Estrutura->DeviceName);
				EstruturaRetorno->Rotation = static_cast<SDKBase::Enumeracoes::CA_DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);
				EstruturaRetorno->BitsPerColor = static_cast<UInt32>(Param_Estrutura->BitsPerColor);
				EstruturaRetorno->ColorSpace = static_cast<CA_DXGI_COLOR_SPACE_TYPE>(Param_Estrutura->ColorSpace);
				EstruturaRetorno->MinLuminance = Param_Estrutura->MinLuminance;
				EstruturaRetorno->MaxLuminance = Param_Estrutura->MaxLuminance;
				EstruturaRetorno->MaxLuminance = Param_Estrutura->MaxFullFrameLuminance;

				//Verifica se o HMONITOR é valido e define.
				if (ObjetoValido(Param_Estrutura->Monitor))
				{
					//Cria a classe do monitor.
					EstruturaRetorno->Monitor = gcnew CarenHMONITOR();

					//Define o ponteiro.
					EstruturaRetorno->Monitor->SetObject(Param_Estrutura->Monitor);
				}

				//Cria os arrays
				EstruturaRetorno->RedPrimary = gcnew cli::array<float>(2);
				EstruturaRetorno->GreenPrimary = gcnew cli::array<float>(2);
				EstruturaRetorno->BluePrimary = gcnew cli::array<float>(2);
				EstruturaRetorno->WhitePoint = gcnew cli::array<float>(2);

				//Preenche os dados.
				//RED
				EstruturaRetorno->RedPrimary[0] = Param_Estrutura->RedPrimary[0];
				EstruturaRetorno->RedPrimary[1] = Param_Estrutura->RedPrimary[1];
				//GREEN
				EstruturaRetorno->GreenPrimary[0] = Param_Estrutura->GreenPrimary[0];
				EstruturaRetorno->GreenPrimary[1] = Param_Estrutura->GreenPrimary[1];
				//BLUE
				EstruturaRetorno->BluePrimary[0] = Param_Estrutura->BluePrimary[0];
				EstruturaRetorno->BluePrimary[1] = Param_Estrutura->BluePrimary[1];
				//WHITE POINT
				EstruturaRetorno->WhitePoint[0] = Param_Estrutura->WhitePoint[0];
				EstruturaRetorno->WhitePoint[1] = Param_Estrutura->WhitePoint[1];

				//Cria e preenche a estrutura secundaria.
				EstruturaRetorno->DesktopCoordinates = gcnew CA_RECT();
				
				//Define as coordenadas
				EstruturaRetorno->DesktopCoordinates->Topo = Param_Estrutura->DesktopCoordinates.top;
				EstruturaRetorno->DesktopCoordinates->Fundo = Param_Estrutura->DesktopCoordinates.bottom;
				EstruturaRetorno->DesktopCoordinates->Direita = Param_Estrutura->DesktopCoordinates.right;
				EstruturaRetorno->DesktopCoordinates->Esquerda = Param_Estrutura->DesktopCoordinates.left;


				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_GAMMA_CONTROL_CAPABILITIES) para sua correspondencia não gerenciada(DXGI_GAMMA_CONTROL_CAPABILITIES).
			DXGI_GAMMA_CONTROL_CAPABILITIES* ConverterDXGI_GAMMA_CONTROL_CAPABILITIESManaged_ToUnManaged(CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_GAMMA_CONTROL_CAPABILITIES* EstruturaRetorno = CriarEstrutura<DXGI_GAMMA_CONTROL_CAPABILITIES>();
				int CountItensArray = 0;

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_GAMMA_CONTROL_CAPABILITIES));

				//Preenche os dados da estrutura principal.

				//Verifica se o array de points é valido
				if (ObjetoGerenciadoValido(Param_Estrutura->ControlPointPositions))
				{
					//Obtém a quantidade de itens.
					CountItensArray = Param_Estrutura->ControlPointPositions->Length;

					//Copia os dados para o array nativo.
					for (int i = 0; i < CountItensArray; i++)
					{
						//Define o valor.
						EstruturaRetorno->ControlPointPositions[i] = Param_Estrutura->ControlPointPositions[i];
					}
				}
				EstruturaRetorno->MaxConvertedValue = Param_Estrutura->MaxConvertedValue;
				EstruturaRetorno->MinConvertedValue = Param_Estrutura->MinConvertedValue;
				EstruturaRetorno->NumGammaControlPoints = Param_Estrutura->NumGammaControlPoints;
				EstruturaRetorno->ScaleAndOffsetSupported = Param_Estrutura->ScaleAndOffsetSupported ? TRUE : FALSE;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_GAMMA_CONTROL_CAPABILITIES) para sua correspondencia gerenciada(CA_DXGI_GAMMA_CONTROL_CAPABILITIES).
			CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ ConverterDXGI_GAMMA_CONTROL_CAPABILITIESUnManaged_ToManaged(DXGI_GAMMA_CONTROL_CAPABILITIES* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ EstruturaRetorno = gcnew CA_DXGI_GAMMA_CONTROL_CAPABILITIES();

				//Cria o array de gamma control points.
				EstruturaRetorno->ControlPointPositions = gcnew cli::array<float>(Param_Estrutura->NumGammaControlPoints);

				//Preenche os dados da estrutura principal.
				//NumGammaControlPoints contém a quantidade de itens no array.
				for (UINT i = 0; i < Param_Estrutura->NumGammaControlPoints; i++)
				{
					//Define o valor.
					EstruturaRetorno->ControlPointPositions[i] = Param_Estrutura->ControlPointPositions[i];
				}
				EstruturaRetorno->MaxConvertedValue = Param_Estrutura->MaxConvertedValue;
				EstruturaRetorno->MinConvertedValue = Param_Estrutura->MinConvertedValue;
				EstruturaRetorno->NumGammaControlPoints = Param_Estrutura->NumGammaControlPoints;
				EstruturaRetorno->ScaleAndOffsetSupported = Param_Estrutura->ScaleAndOffsetSupported ? true : false;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_PRESENT_PARAMETERS) para sua correspondencia não gerenciada(DXGI_PRESENT_PARAMETERS).
			DXGI_PRESENT_PARAMETERS* ConverterDXGI_PRESENT_PARAMETERSManaged_ToUnManaged(CA_DXGI_PRESENT_PARAMETERS^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_PRESENT_PARAMETERS* EstruturaRetorno = CriarEstrutura<DXGI_PRESENT_PARAMETERS>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_PRESENT_PARAMETERS));

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DirtyRectsCount = Param_Estrutura->DirtyRectsCount;

				//Define os dados das estruturas secundarias.

				//Verifica se a estrutura dos Rects é valida e obtém os dados.
				if (ObjetoGerenciadoValido(Param_Estrutura->pDirtyRects))
				{
					//Cria a estrutura nativa.
					EstruturaRetorno->pDirtyRects = CriarMatrizEstruturas<RECT>(EstruturaRetorno->DirtyRectsCount);

					//Faz um for para adicionar os dados a matriz de rects.
					for (UINT i = 0; i < EstruturaRetorno->DirtyRectsCount; i++)
					{
						EstruturaRetorno->pDirtyRects[i].bottom = Param_Estrutura->pDirtyRects[i]->Fundo;
						EstruturaRetorno->pDirtyRects[i].top = Param_Estrutura->pDirtyRects[i]->Topo;
						EstruturaRetorno->pDirtyRects[i].right = Param_Estrutura->pDirtyRects[i]->Direita;
						EstruturaRetorno->pDirtyRects[i].left = Param_Estrutura->pDirtyRects[i]->Esquerda;
					}
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pDirtyRects = NULL;
				}

				//Verifica se foi fornececido a estrutura de rolagem
				if (ObjetoGerenciadoValido(Param_Estrutura->pScrollRect))
				{
					//Converte e define o ponteiro para a estrutura.
					EstruturaRetorno->pScrollRect = ConverterRECTManagedToUnmanaged(Param_Estrutura->pScrollRect);
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pScrollRect = NULL;
				}

				//Verifica se foi fornecido a estrutura de pontos para a estrutura de rolagem.
				if (ObjetoGerenciadoValido(Param_Estrutura->pScrollOffset))
				{
					//Cria a estrutura.
					EstruturaRetorno->pScrollOffset = CriarEstrutura<POINT>();

					//Preenche os dados.
					EstruturaRetorno->pScrollOffset->x = Param_Estrutura->pScrollOffset->X;
					EstruturaRetorno->pScrollOffset->y = Param_Estrutura->pScrollOffset->Y;
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pScrollOffset = NULL;
				}

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_PRESENT_PARAMETERS) para sua correspondencia gerenciada(CA_DXGI_PRESENT_PARAMETERS).
			CA_DXGI_PRESENT_PARAMETERS^ ConverterDXGI_PRESENT_PARAMETERSUnManaged_ToManaged(DXGI_PRESENT_PARAMETERS* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_PRESENT_PARAMETERS^ EstruturaRetorno = gcnew CA_DXGI_PRESENT_PARAMETERS();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DirtyRectsCount = Param_Estrutura->DirtyRectsCount;

				//Verifica se a estrutura dos Rects é valida e obtém os dados.
				if (ObjetoValido(Param_Estrutura->pDirtyRects))
				{
					//Cria a estrutura nativa.
					EstruturaRetorno->pDirtyRects = gcnew cli::array<CA_RECT^>(EstruturaRetorno->DirtyRectsCount);

					//Faz um for para adicionar os dados a matriz de rects.
					for (UINT i = 0; i < EstruturaRetorno->DirtyRectsCount; i++)
					{
						//Define os dados na estrutura.
						EstruturaRetorno->pDirtyRects[i]->Fundo = Param_Estrutura->pDirtyRects[i].bottom;
						EstruturaRetorno->pDirtyRects[i]->Topo = Param_Estrutura->pDirtyRects[i].top;
						EstruturaRetorno->pDirtyRects[i]->Direita = Param_Estrutura->pDirtyRects[i].right;
						EstruturaRetorno->pDirtyRects[i]->Esquerda = Param_Estrutura->pDirtyRects[i].left;
					}
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pDirtyRects = nullptr;
				}

				//Verifica se foi fornececido a estrutura de rolagem
				if (ObjetoValido(Param_Estrutura->pScrollRect))
				{
					//Converte e define o ponteiro para a estrutura.
					EstruturaRetorno->pScrollRect = ConverterRECTUnmanagedToManaged(Param_Estrutura->pScrollRect);
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pScrollRect = nullptr;
				}

				//Verifica se foi fornecido a estrutura de pontos para a estrutura de rolagem.
				if (ObjetoValido(Param_Estrutura->pScrollOffset))
				{
					//Cria a estrutura.
					EstruturaRetorno->pScrollOffset = gcnew CA_POINT();

					//Preenche os dados.
					EstruturaRetorno->pScrollOffset->X = Param_Estrutura->pScrollOffset->x;
					EstruturaRetorno->pScrollOffset->Y = Param_Estrutura->pScrollOffset->y;
				}
				else
				{
					//Define como NULL.
					EstruturaRetorno->pScrollOffset = nullptr;
				}

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_ADAPTER_DESC) para sua correspondencia não gerenciada(DXGI_ADAPTER_DESC).
			DXGI_ADAPTER_DESC* ConverterDXGI_ADAPTER_DESCManaged_ToUnManaged(CA_DXGI_ADAPTER_DESC^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_ADAPTER_DESC* EstruturaRetorno = CriarEstrutura<DXGI_ADAPTER_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_ADAPTER_DESC));

				//Variveis
				int LengDescption = Param_Estrutura->Description->Length;

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;

				//Define os dados da descrição
				for (int i = 0; i < LengDescption; i++)
				{
					//Define os dados na descrição nativa.
					EstruturaRetorno->Description[i] = Param_Estrutura->Description[i];
				}

				//Define o sinalizador de fim de caracter
				EstruturaRetorno->Description[LengDescption] = '\0';

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid.HighPart = Param_Estrutura->AdapterLuid->HighPart;
				EstruturaRetorno->AdapterLuid.LowPart = Param_Estrutura->AdapterLuid->LowPart;


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_ADAPTER_DESC) para sua correspondencia gerenciada(CA_DXGI_ADAPTER_DESC).
			CA_DXGI_ADAPTER_DESC^ ConverterDXGI_ADAPTER_DESCUnManaged_ToManaged(DXGI_ADAPTER_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_ADAPTER_DESC^ EstruturaRetorno = gcnew CA_DXGI_ADAPTER_DESC();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;
				EstruturaRetorno->Description = gcnew String(Param_Estrutura->Description);

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid = gcnew CA_LUID();
				EstruturaRetorno->AdapterLuid->HighPart = Param_Estrutura->AdapterLuid.HighPart;
				EstruturaRetorno->AdapterLuid->LowPart = Param_Estrutura->AdapterLuid.LowPart;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_ADAPTER_DESC1) para sua correspondencia não gerenciada(DXGI_ADAPTER_DESC1).
			DXGI_ADAPTER_DESC1* ConverterDXGI_ADAPTER_DESC1Managed_ToUnManaged(CA_DXGI_ADAPTER_DESC1^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_ADAPTER_DESC1* EstruturaRetorno = CriarEstrutura<DXGI_ADAPTER_DESC1>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_ADAPTER_DESC1));

				//Variveis
				int LengDescption = Param_Estrutura->Description->Length;

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;
				EstruturaRetorno->Flags = static_cast<UINT>(Param_Estrutura->Flags);

				//Define os dados da descrição
				for (int i = 0; i < LengDescption; i++)
				{
					//Define os dados na descrição nativa.
					EstruturaRetorno->Description[i] = Param_Estrutura->Description[i];
				}

				//Define o sinalizador de fim de caracter
				EstruturaRetorno->Description[LengDescption] = '\0';

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid.HighPart = Param_Estrutura->AdapterLuid->HighPart;
				EstruturaRetorno->AdapterLuid.LowPart = Param_Estrutura->AdapterLuid->LowPart;


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_ADAPTER_DESC1) para sua correspondencia gerenciada(CA_DXGI_ADAPTER_DESC1).
			CA_DXGI_ADAPTER_DESC1^ ConverterDXGI_ADAPTER_DESC1UnManaged_ToManaged(DXGI_ADAPTER_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_ADAPTER_DESC1^ EstruturaRetorno = gcnew CA_DXGI_ADAPTER_DESC1();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;
				EstruturaRetorno->Description = gcnew String(Param_Estrutura->Description);
				EstruturaRetorno->Flags = static_cast<CA_DXGI_ADAPTER_FLAG>(Param_Estrutura->Flags);

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid = gcnew CA_LUID();
				EstruturaRetorno->AdapterLuid->HighPart = Param_Estrutura->AdapterLuid.HighPart;
				EstruturaRetorno->AdapterLuid->LowPart = Param_Estrutura->AdapterLuid.LowPart;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_ADAPTER_DESC2) para sua correspondencia não gerenciada(DXGI_ADAPTER_DESC2).
			DXGI_ADAPTER_DESC2* ConverterDXGI_ADAPTER_DESC2Managed_ToUnManaged(CA_DXGI_ADAPTER_DESC2^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_ADAPTER_DESC2* EstruturaRetorno = CriarEstrutura<DXGI_ADAPTER_DESC2>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_ADAPTER_DESC2));

				//Variveis
				int LengDescption = Param_Estrutura->Description->Length;

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;
				EstruturaRetorno->GraphicsPreemptionGranularity = static_cast<DXGI_GRAPHICS_PREEMPTION_GRANULARITY>(Param_Estrutura->GraphicsPreemptionGranularity);
				EstruturaRetorno->ComputePreemptionGranularity = static_cast<DXGI_COMPUTE_PREEMPTION_GRANULARITY>(Param_Estrutura->ComputePreemptionGranularity);
				EstruturaRetorno->Flags = static_cast<UINT>(Param_Estrutura->Flags);

				//Define os dados da descrição
				for (int i = 0; i < LengDescption; i++)
				{
					//Define os dados na descrição nativa.
					EstruturaRetorno->Description[i] = Param_Estrutura->Description[i];
				}

				//Define o sinalizador de fim de caracter
				EstruturaRetorno->Description[LengDescption] = '\0';

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid.HighPart = Param_Estrutura->AdapterLuid->HighPart;
				EstruturaRetorno->AdapterLuid.LowPart = Param_Estrutura->AdapterLuid->LowPart;


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_ADAPTER_DESC2) para sua correspondencia gerenciada(CA_DXGI_ADAPTER_DESC2).
			CA_DXGI_ADAPTER_DESC2^ ConverterDXGI_ADAPTER_DESC2UnManaged_ToManaged(DXGI_ADAPTER_DESC2* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_ADAPTER_DESC2^ EstruturaRetorno = gcnew CA_DXGI_ADAPTER_DESC2();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->GraphicsPreemptionGranularity = static_cast<CA_DXGI_GRAPHICS_PREEMPTION_GRANULARITY>(Param_Estrutura->GraphicsPreemptionGranularity);
				EstruturaRetorno->ComputePreemptionGranularity = static_cast<CA_DXGI_COMPUTE_PREEMPTION_GRANULARITY>(Param_Estrutura->ComputePreemptionGranularity);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;

				EstruturaRetorno->Description = gcnew String(Param_Estrutura->Description);
				EstruturaRetorno->Flags = static_cast<CA_DXGI_ADAPTER_FLAG>(Param_Estrutura->Flags);

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid = gcnew CA_LUID();
				EstruturaRetorno->AdapterLuid->HighPart = Param_Estrutura->AdapterLuid.HighPart;
				EstruturaRetorno->AdapterLuid->LowPart = Param_Estrutura->AdapterLuid.LowPart;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_ADAPTER_DESC3) para sua correspondencia não gerenciada(DXGI_ADAPTER_DESC3).
			DXGI_ADAPTER_DESC3* ConverterDXGI_ADAPTER_DESC3Managed_ToUnManaged(CA_DXGI_ADAPTER_DESC3^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_ADAPTER_DESC3* EstruturaRetorno = CriarEstrutura<DXGI_ADAPTER_DESC3>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_ADAPTER_DESC3));

				//Variveis
				int LengDescption = Param_Estrutura->Description->Length;

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<SIZE_T>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<SIZE_T>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;
				EstruturaRetorno->GraphicsPreemptionGranularity = static_cast<DXGI_GRAPHICS_PREEMPTION_GRANULARITY>(Param_Estrutura->GraphicsPreemptionGranularity);
				EstruturaRetorno->ComputePreemptionGranularity = static_cast<DXGI_COMPUTE_PREEMPTION_GRANULARITY>(Param_Estrutura->ComputePreemptionGranularity);
				EstruturaRetorno->Flags = static_cast<DXGI_ADAPTER_FLAG3>(Param_Estrutura->Flags);

				//Define os dados da descrição
				for (int i = 0; i < LengDescption; i++)
				{
					//Define os dados na descrição nativa.
					EstruturaRetorno->Description[i] = Param_Estrutura->Description[i];
				}

				//Define o sinalizador de fim de caracter
				EstruturaRetorno->Description[LengDescption] = '\0';

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid.HighPart = Param_Estrutura->AdapterLuid->HighPart;
				EstruturaRetorno->AdapterLuid.LowPart = Param_Estrutura->AdapterLuid->LowPart;


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_ADAPTER_DESC3) para sua correspondencia gerenciada(CA_DXGI_ADAPTER_DESC3).
			CA_DXGI_ADAPTER_DESC3^ ConverterDXGI_ADAPTER_DESC3UnManaged_ToManaged(DXGI_ADAPTER_DESC3* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_ADAPTER_DESC3^ EstruturaRetorno = gcnew CA_DXGI_ADAPTER_DESC3();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->DedicatedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedSystemMemory);
				EstruturaRetorno->DedicatedVideoMemory = static_cast<unsigned long long>(Param_Estrutura->DedicatedVideoMemory);
				EstruturaRetorno->SharedSystemMemory = static_cast<unsigned long long>(Param_Estrutura->SharedSystemMemory);
				EstruturaRetorno->GraphicsPreemptionGranularity = static_cast<CA_DXGI_GRAPHICS_PREEMPTION_GRANULARITY>(Param_Estrutura->GraphicsPreemptionGranularity);
				EstruturaRetorno->ComputePreemptionGranularity = static_cast<CA_DXGI_COMPUTE_PREEMPTION_GRANULARITY>(Param_Estrutura->ComputePreemptionGranularity);
				EstruturaRetorno->DeviceId = Param_Estrutura->DeviceId;
				EstruturaRetorno->Revision = Param_Estrutura->Revision;
				EstruturaRetorno->SubSysId = Param_Estrutura->SubSysId;
				EstruturaRetorno->VendorId = Param_Estrutura->VendorId;

				EstruturaRetorno->Description = gcnew String(Param_Estrutura->Description);
				EstruturaRetorno->Flags = static_cast<CA_DXGI_ADAPTER_FLAG3>(Param_Estrutura->Flags);

				//Define os dados da estrutura secundaria.
				EstruturaRetorno->AdapterLuid = gcnew CA_LUID();
				EstruturaRetorno->AdapterLuid->HighPart = Param_Estrutura->AdapterLuid.HighPart;
				EstruturaRetorno->AdapterLuid->LowPart = Param_Estrutura->AdapterLuid.LowPart;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_SURFACE_DESC) para sua correspondencia não gerenciada(DXGI_SURFACE_DESC).
			DXGI_SURFACE_DESC* ConverterDXGI_SURFACE_DESCManaged_ToUnManaged(CA_DXGI_SURFACE_DESC^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_SURFACE_DESC* EstruturaRetorno = CriarEstrutura<DXGI_SURFACE_DESC>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_SURFACE_DESC));

				//Define os dados na estrutura principal.
				EstruturaRetorno->Format = static_cast<DXGI_FORMAT>(Param_Estrutura->Formato);
				EstruturaRetorno->Width = Param_Estrutura->Largura;
				EstruturaRetorno->Height = Param_Estrutura->Altura;
				
				//Verifica se as estruturas secundarias são validas e define
				if (ObjetoGerenciadoValido(Param_Estrutura->DescParametrosMultiamostragem))
				{
					//Define os dados na estrutura.
					EstruturaRetorno->SampleDesc.Count = Param_Estrutura->DescParametrosMultiamostragem->Count;
					EstruturaRetorno->SampleDesc.Quality = Param_Estrutura->DescParametrosMultiamostragem->Quality;
				}
				
				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_SURFACE_DESC) para sua correspondencia gerenciada(CA_DXGI_SURFACE_DESC).
			CA_DXGI_SURFACE_DESC^ ConverterDXGI_SURFACE_DESCUnManaged_ToManaged(DXGI_SURFACE_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_SURFACE_DESC^ EstruturaRetorno = gcnew CA_DXGI_SURFACE_DESC();

				//Define os dados na estrutura principal.
				EstruturaRetorno->Formato = static_cast<CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->Largura = Param_Estrutura->Width;
				EstruturaRetorno->Altura = Param_Estrutura->Height;

				//Inicializa a estrutura secundaria e define os dados
				EstruturaRetorno->DescParametrosMultiamostragem = gcnew CA_DXGI_SAMPLE_DESC();

				//Define os dados.
				EstruturaRetorno->DescParametrosMultiamostragem->Count = Param_Estrutura->SampleDesc.Count;
				EstruturaRetorno->DescParametrosMultiamostragem->Quality = Param_Estrutura->SampleDesc.Quality;
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MAPPED_RECT) para sua correspondencia não gerenciada(DXGI_MAPPED_RECT).
			DXGI_MAPPED_RECT* ConverterDXGI_MAPPED_RECTManaged_ToUnManaged(CA_DXGI_MAPPED_RECT^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_MAPPED_RECT* EstruturaRetorno = CriarEstrutura<DXGI_MAPPED_RECT>();

				//Ponteiro para o buffer.
				IntPtr PointeiroBuffer = IntPtr::Zero;

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_MAPPED_RECT));

				//Define os dados na estrutura
				EstruturaRetorno->Pitch = Param_Estrutura->Largura;

				//Verifica se o buffer é valido e define na estrutura.
				if (ObjetoGerenciadoValido(Param_Estrutura->Buffer))
				{
					//Recupera o ponteiro do buffer para a estrutura.
					static_cast<ICarenBuffer^>(Param_Estrutura->Buffer)->GetInternalPointer(PointeiroBuffer);

					//Define o ponteiro.
					EstruturaRetorno->pBits = (BYTE*)PointeiroBuffer.ToPointer();
				}
				
				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_MAPPED_RECT) para sua correspondencia gerenciada(CA_DXGI_MAPPED_RECT).
			CA_DXGI_MAPPED_RECT^ ConverterDXGI_MAPPED_RECTUnManaged_ToManaged(DXGI_MAPPED_RECT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_MAPPED_RECT^ EstruturaRetorno = gcnew CA_DXGI_MAPPED_RECT();

				//Define os dados na estrutura
				EstruturaRetorno->Largura = Param_Estrutura->Pitch;

				//Verifica se o buffer é valido e define na estrutura.
				if (ObjetoValido(Param_Estrutura->pBits))
				{
					//Cria a classe que vai conter o ponteiro para o buffer de memória.
					EstruturaRetorno->Buffer = gcnew CarenBuffer();

					//Cria e associa o ponteiro da estrutura a interface.
					static_cast<ICarenBuffer^>(EstruturaRetorno->Buffer)->CreateBuffer(IntPtr(Param_Estrutura->pBits), false, (unsigned int)EstruturaRetorno->Largura, (unsigned int)EstruturaRetorno->Largura);

					//Define a posição para zero
					static_cast<ICarenBuffer^>(EstruturaRetorno->Buffer)->SetPosition(0);
				}
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_QUERY_VIDEO_MEMORY_INFO) para sua correspondencia não gerenciada(DXGI_QUERY_VIDEO_MEMORY_INFO).
			DXGI_QUERY_VIDEO_MEMORY_INFO* ConverterDXGI_QUERY_VIDEO_MEMORY_INFOManaged_ToUnManaged(CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_QUERY_VIDEO_MEMORY_INFO* EstruturaRetorno = CriarEstrutura<DXGI_QUERY_VIDEO_MEMORY_INFO>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_QUERY_VIDEO_MEMORY_INFO));

				//Define os dados na estrutura
				EstruturaRetorno->AvailableForReservation = static_cast<UINT64>(Param_Estrutura->AvailableForReservation);
				EstruturaRetorno->Budget = static_cast<UINT64>(Param_Estrutura->Budget);
				EstruturaRetorno->CurrentReservation = static_cast<UINT64>(Param_Estrutura->CurrentReservation);
				EstruturaRetorno->CurrentUsage = static_cast<UINT64>(Param_Estrutura->CurrentUsage);

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_QUERY_VIDEO_MEMORY_INFO) para sua correspondencia gerenciada(CA_DXGI_QUERY_VIDEO_MEMORY_INFO).
			CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ ConverterDXGI_QUERY_VIDEO_MEMORY_INFOUnManaged_ToManaged(DXGI_QUERY_VIDEO_MEMORY_INFO* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ EstruturaRetorno = gcnew CA_DXGI_QUERY_VIDEO_MEMORY_INFO();

				//Define os dados na estrutura
				EstruturaRetorno->AvailableForReservation = static_cast<UInt64>(Param_Estrutura->AvailableForReservation);
				EstruturaRetorno->Budget = static_cast<UInt64>(Param_Estrutura->Budget);
				EstruturaRetorno->CurrentReservation = static_cast<UInt64>(Param_Estrutura->CurrentReservation);
				EstruturaRetorno->CurrentUsage = static_cast<UInt64>(Param_Estrutura->CurrentUsage);

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MATRIX_3X2_F) para sua correspondencia não gerenciada(DXGI_MATRIX_3X2_F).
			DXGI_MATRIX_3X2_F* ConverterDXGI_MATRIX_3X2_FManaged_ToUnManaged(CA_DXGI_MATRIX_3X2_F^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				DXGI_MATRIX_3X2_F* EstruturaRetorno = CriarEstrutura<DXGI_MATRIX_3X2_F>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_MATRIX_3X2_F));

				//Define os dados na estrutura
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_MATRIX_3X2_F) para sua correspondencia gerenciada(CA_DXGI_MATRIX_3X2_F).
			CA_DXGI_MATRIX_3X2_F^ ConverterDXGI_MATRIX_3X2_FUnManaged_ToManaged(DXGI_MATRIX_3X2_F* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_DXGI_MATRIX_3X2_F^ EstruturaRetorno = gcnew CA_DXGI_MATRIX_3X2_F();

				//Define os dados na estrutura
				EstruturaRetorno->_11 = Param_Estrutura->_11;
				EstruturaRetorno->_12 = Param_Estrutura->_12;
				EstruturaRetorno->_21 = Param_Estrutura->_21;
				EstruturaRetorno->_22 = Param_Estrutura->_22;
				EstruturaRetorno->_31 = Param_Estrutura->_31;
				EstruturaRetorno->_32 = Param_Estrutura->_32;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_JPEG_AC_HUFFMAN_TABLE) para sua correspondencia não gerenciada(DXGI_JPEG_AC_HUFFMAN_TABLE).
			DXGI_JPEG_AC_HUFFMAN_TABLE* ConverterDXGI_JPEG_AC_HUFFMAN_TABLEManaged_ToUnmanaged(CA_DXGI_JPEG_AC_HUFFMAN_TABLE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				DXGI_JPEG_AC_HUFFMAN_TABLE* EstruturaRetorno = CriarEstrutura<DXGI_JPEG_AC_HUFFMAN_TABLE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_JPEG_AC_HUFFMAN_TABLE));

				//Define os dados.
				
				//Faz um for para definir os dados no array de Code Counts.
				for (UINT32 i = 0; i < 16; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->CodeCounts[i] = Param_Estrutura->ArrayCodeCounts[i];
				}
				
				//Faz um for para definir os dados no array de Code Values.
				for (UINT32 i = 0; i < 162; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->CodeValues[i] = Param_Estrutura->ArrayCodeValues[i];
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_JPEG_AC_HUFFMAN_TABLE) para sua correspondencia gerenciada(CA_DXGI_JPEG_AC_HUFFMAN_TABLE).
			CA_DXGI_JPEG_AC_HUFFMAN_TABLE^ ConverterDXGI_JPEG_AC_HUFFMAN_TABLEUnmanaged_ToManaged(DXGI_JPEG_AC_HUFFMAN_TABLE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_DXGI_JPEG_AC_HUFFMAN_TABLE^ EstruturaRetorno = gcnew CA_DXGI_JPEG_AC_HUFFMAN_TABLE();

				//Define os dados.

				//Cria as matrizes.
				EstruturaRetorno->ArrayCodeCounts = gcnew cli::array<Byte>(16);
				EstruturaRetorno->ArrayCodeValues = gcnew cli::array<Byte>(162);

				//Faz um for para definir os dados no array de Code Counts.
				for (UINT32 i = 0; i < 16; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->ArrayCodeCounts[i] = Param_Estrutura->CodeCounts[i];
				}

				//Faz um for para definir os dados no array de Code Values.
				for (UINT32 i = 0; i < 162; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->ArrayCodeValues[i] = Param_Estrutura->CodeValues[i];
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_JPEG_DC_HUFFMAN_TABLE) para sua correspondencia não gerenciada(DXGI_JPEG_DC_HUFFMAN_TABLE).
			DXGI_JPEG_DC_HUFFMAN_TABLE* ConverterDXGI_JPEG_DC_HUFFMAN_TABLEManaged_ToUnmanaged(CA_DXGI_JPEG_DC_HUFFMAN_TABLE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				DXGI_JPEG_DC_HUFFMAN_TABLE* EstruturaRetorno = CriarEstrutura<DXGI_JPEG_DC_HUFFMAN_TABLE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_JPEG_DC_HUFFMAN_TABLE));

				//Define os dados.

				//Faz um for para definir os dados no array de Code Counts.
				for (UINT32 i = 0; i < 12; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->CodeCounts[i] = Param_Estrutura->ArrayCodeCounts[i];
					EstruturaRetorno->CodeValues[i] = Param_Estrutura->ArrayCodeValues[i];
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_JPEG_DC_HUFFMAN_TABLE) para sua correspondencia gerenciada(CA_DXGI_JPEG_DC_HUFFMAN_TABLE).
			CA_DXGI_JPEG_DC_HUFFMAN_TABLE^ ConverterDXGI_JPEG_DC_HUFFMAN_TABLEUnmanaged_ToManaged(DXGI_JPEG_DC_HUFFMAN_TABLE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_DXGI_JPEG_DC_HUFFMAN_TABLE^ EstruturaRetorno = gcnew CA_DXGI_JPEG_DC_HUFFMAN_TABLE();

				//Define os dados.

				//Cria as matrizes.
				EstruturaRetorno->ArrayCodeCounts = gcnew cli::array<Byte>(12);
				EstruturaRetorno->ArrayCodeValues = gcnew cli::array<Byte>(12);

				//Faz um for para definir os dados no array de Code Counts.
				for (UINT32 i = 0; i < 12; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->ArrayCodeCounts[i] = Param_Estrutura->CodeCounts[i];
					EstruturaRetorno->ArrayCodeValues[i] = Param_Estrutura->CodeValues[i];
				}


				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_JPEG_QUANTIZATION_TABLE) para sua correspondencia não gerenciada(DXGI_JPEG_QUANTIZATION_TABLE).
			DXGI_JPEG_QUANTIZATION_TABLE* ConverterDXGI_JPEG_QUANTIZATION_TABLEManaged_ToUnmanaged(CA_DXGI_JPEG_QUANTIZATION_TABLE^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				DXGI_JPEG_QUANTIZATION_TABLE* EstruturaRetorno = CriarEstrutura<DXGI_JPEG_QUANTIZATION_TABLE>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(DXGI_JPEG_QUANTIZATION_TABLE));

				//Define os dados.

				//Faz um for para definir os dados no array de elementos.
				for (UINT32 i = 0; i < 64; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->Elements[i] = Param_Estrutura->ArrayElementos[i];
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_JPEG_QUANTIZATION_TABLE) para sua correspondencia gerenciada(CA_DXGI_JPEG_QUANTIZATION_TABLE).
			CA_DXGI_JPEG_QUANTIZATION_TABLE^ ConverterDXGI_JPEG_QUANTIZATION_TABLEUnmanaged_ToManaged(DXGI_JPEG_QUANTIZATION_TABLE* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_DXGI_JPEG_QUANTIZATION_TABLE^ EstruturaRetorno = gcnew CA_DXGI_JPEG_QUANTIZATION_TABLE();

				//Define os dados.

				//Cria a matriz
				EstruturaRetorno->ArrayElementos = gcnew cli::array<Byte>(64);

				//Faz um for para definir os dados no array de elementos.
				for (UINT32 i = 0; i < 64; i++)
				{
					//Define os dados na matriz.
					EstruturaRetorno->ArrayElementos[i] = Param_Estrutura->Elements[i];
				}

				//Retorna o resultado
				return EstruturaRetorno;
			}




			// WIC - ESTRUTURAS


			//Converte uma estrutura gerenciada(CA_WICRect) para sua correspondencia não gerenciada(WICRect).
			WICRect* ConverterWICRectManaged_ToUnManaged(CA_WICRect^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				WICRect* EstruturaRetorno = CriarEstrutura<WICRect>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(WICRect));

				//Define os dados na estrutura
				EstruturaRetorno->X = Param_Estrutura->X;
				EstruturaRetorno->Y = Param_Estrutura->Y;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICRect) para sua correspondencia gerenciada(CA_WICRect).
			CA_WICRect^ ConverterWICBitmapPatternUnManaged_ToManaged(WICRect* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_WICRect^ EstruturaRetorno = gcnew CA_WICRect();

				//Define os dados na estrutura
				EstruturaRetorno->X = Param_Estrutura->X;
				EstruturaRetorno->Y = Param_Estrutura->Y;
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;

				//Retorna a variavel.
				return EstruturaRetorno;
			}



			//Converte uma estrutura gerenciada(CA_WICBitmapPattern) para sua correspondencia não gerenciada(WICBitmapPattern).
			WICBitmapPattern* ConverterWICBitmapPatternManaged_ToUnManaged(CA_WICBitmapPattern^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				WICBitmapPattern* EstruturaRetorno = CriarEstrutura<WICBitmapPattern>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(WICBitmapPattern));

				//Variveis
				GenPointer pBufferPattern = DefaultGenPointer;
				GenPointer pBufferMask = DefaultGenPointer;

				//Recupera o ponteiro dos buffers acima.
				static_cast<ICarenBuffer^>(Param_Estrutura->Pattern)->GetInternalPointer(pBufferPattern);
				static_cast<ICarenBuffer^>(Param_Estrutura->Mask)->GetInternalPointer(pBufferMask);

				//Define os dados na estrutura
				EstruturaRetorno->Length = static_cast<ULONG>(Param_Estrutura->Length);
				EstruturaRetorno->Position.QuadPart = Param_Estrutura->Position;
				EstruturaRetorno->Pattern = ConverterIntPtrTo<BYTE*>(pBufferPattern);
				EstruturaRetorno->Mask = ConverterIntPtrTo<BYTE*>(pBufferMask);
				EstruturaRetorno->EndOfStream = Param_Estrutura->EndOfStream ? TRUE : FALSE;

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICBitmapPattern) para sua correspondencia gerenciada(CA_WICBitmapPattern).
			CA_WICBitmapPattern^ ConverterWICBitmapPatternUnManaged_ToManaged(WICBitmapPattern* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_WICBitmapPattern^ EstruturaRetorno = gcnew CA_WICBitmapPattern();

				//Define os dados na estrutura
				EstruturaRetorno->Length = static_cast<UINT64>(Param_Estrutura->Length);
				EstruturaRetorno->Position = Param_Estrutura->Position.QuadPart;
				EstruturaRetorno->Pattern = gcnew CarenBuffer();
				EstruturaRetorno->Mask = gcnew CarenBuffer();
				EstruturaRetorno->EndOfStream = Param_Estrutura->EndOfStream ? TRUE : FALSE;
				
				//Define os dados no buffer.
				static_cast<ICarenBuffer^>(EstruturaRetorno->Pattern)->CreateBuffer(IntPtr(Param_Estrutura->Pattern), false, safe_cast<UInt32>(EstruturaRetorno->Length), safe_cast<UInt32>(EstruturaRetorno->Length));
				static_cast<ICarenBuffer^>(EstruturaRetorno->Mask)->CreateBuffer(IntPtr(Param_Estrutura->Mask), false, 0, 0);

				//Retorna a variavel.
				return EstruturaRetorno;
			}



			//Converte uma estrutura gerenciada(CA_WICImageParameters) para sua correspondencia não gerenciada(WICImageParameters).
			WICImageParameters* ConverterWICImageParametersManaged_ToUnManaged(CA_WICImageParameters^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				WICImageParameters* EstruturaRetorno = CriarEstrutura<WICImageParameters>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(WICImageParameters));

				//Variaveis
				D2D1_PIXEL_FORMAT* vi_pPixelFormat = Nulo;

				//Converte a estrutura
				vi_pPixelFormat = ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(Param_Estrutura->PixelFormat);

				//Define os dados na estrutura
				EstruturaRetorno->PixelFormat = *vi_pPixelFormat;
				EstruturaRetorno->DpiX = Param_Estrutura->DpiX;
				EstruturaRetorno->DpiY = Param_Estrutura->DpiY;
				EstruturaRetorno->Left = Param_Estrutura->Left;
				EstruturaRetorno->Top = Param_Estrutura->Top;
				EstruturaRetorno->PixelHeight = Param_Estrutura->PixelHeight;
				EstruturaRetorno->PixelWidth = Param_Estrutura->PixelWidth;

				//Libera a memória utilizada pela estrutura
				DeletarEstruturaSafe(&vi_pPixelFormat);

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICImageParameters) para sua correspondencia gerenciada(CA_WICImageParameters).
			CA_WICImageParameters^ ConverterWICImageParametersUnManaged_ToManaged(WICImageParameters* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_WICImageParameters^ EstruturaRetorno = gcnew CA_WICImageParameters();

				//Define os dados na estrutura
				EstruturaRetorno->PixelFormat = ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&Param_Estrutura->PixelFormat);
				EstruturaRetorno->DpiX = Param_Estrutura->DpiX;
				EstruturaRetorno->DpiY = Param_Estrutura->DpiY;
				EstruturaRetorno->Left = Param_Estrutura->Left;
				EstruturaRetorno->Top = Param_Estrutura->Top;
				EstruturaRetorno->PixelHeight = Param_Estrutura->PixelHeight;
				EstruturaRetorno->PixelWidth = Param_Estrutura->PixelWidth;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICDdsParameters) para sua correspondencia não gerenciada(WICDdsParameters).
			WICDdsParameters* ConverterWICDdsParametersManaged_ToUnmanaged(CA_WICDdsParameters^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICDdsParameters* EstruturaRetorno = CriarEstrutura<WICDdsParameters>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICDdsParameters));

				//Define os dados.
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->ArraySize = Param_Estrutura->ArraySize;
				EstruturaRetorno->DxgiFormat = static_cast<DXGI_FORMAT>(Param_Estrutura->DxgiFormat);
				EstruturaRetorno->Dimension = static_cast<WICDdsDimension>(Param_Estrutura->Dimension);
				EstruturaRetorno->AlphaMode = static_cast<WICDdsAlphaMode>(Param_Estrutura->AlphaMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICDdsParameters) para sua correspondencia gerenciada(CA_WICDdsParameters).
			CA_WICDdsParameters^ ConverterWICDdsParametersUnmanaged_ToManaged(WICDdsParameters* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICDdsParameters^ EstruturaRetorno = gcnew CA_WICDdsParameters();

				//Define os dados.
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Depth = Param_Estrutura->Depth;
				EstruturaRetorno->MipLevels = Param_Estrutura->MipLevels;
				EstruturaRetorno->ArraySize = Param_Estrutura->ArraySize;
				EstruturaRetorno->DxgiFormat = static_cast<CA_DXGI_FORMAT>(Param_Estrutura->DxgiFormat);
				EstruturaRetorno->Dimension = static_cast<CA_WICDdsDimension>(Param_Estrutura->Dimension);
				EstruturaRetorno->AlphaMode = static_cast<CA_WICDdsAlphaMode>(Param_Estrutura->AlphaMode);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICRawToneCurve) para sua correspondencia não gerenciada(WICRawToneCurvePoint).
			WICRawToneCurvePoint* ConverterWICRawToneCurvePointManaged_ToUnmanaged(CA_WICRawToneCurvePoint^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICRawToneCurvePoint* EstruturaRetorno = CriarEstrutura<WICRawToneCurvePoint>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICRawToneCurvePoint));

				//Define os dados.
				EstruturaRetorno->Input = Param_Estrutura->Input;
				EstruturaRetorno->Output = Param_Estrutura->Output;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICRawToneCurvePoint) para sua correspondencia gerenciada(CA_WICRawToneCurve).
			CA_WICRawToneCurvePoint^ ConverterWICRawToneCurvePointUnmanaged_ToManaged(WICRawToneCurvePoint* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICRawToneCurvePoint^ EstruturaRetorno = gcnew CA_WICRawToneCurvePoint();

				//Define os dados.
				EstruturaRetorno->Input = Param_Estrutura->Input;
				EstruturaRetorno->Output = Param_Estrutura->Output;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICRawToneCurve) para sua correspondencia não gerenciada(WICRawToneCurve).
			WICRawToneCurve* ConverterWICRawToneCurveManaged_ToUnmanaged(CA_WICRawToneCurve^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICRawToneCurve* EstruturaRetorno = CriarEstrutura<WICRawToneCurve>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICRawToneCurve));

				//Define os dados.
				EstruturaRetorno->cPoints = Param_Estrutura->cPoints;
				EstruturaRetorno->aPoints[0] = {};
				EstruturaRetorno->aPoints[0].Input = Param_Estrutura->aPoints[0]->Input;
				EstruturaRetorno->aPoints[0].Output = Param_Estrutura->aPoints[0]->Output;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICRawToneCurve) para sua correspondencia gerenciada(CA_WICRawToneCurve).
			CA_WICRawToneCurve^ ConverterWICRawToneCurveUnmanaged_ToManaged(WICRawToneCurve* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICRawToneCurve^ EstruturaRetorno = gcnew CA_WICRawToneCurve();

				//Define os dados.
				EstruturaRetorno->cPoints = Param_Estrutura->cPoints;
				EstruturaRetorno->aPoints = gcnew cli::array<CA_WICRawToneCurvePoint^>(1);
				EstruturaRetorno->aPoints[0] = ConverterWICRawToneCurvePointUnmanaged_ToManaged(&Param_Estrutura->aPoints[0]);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICRawCapabilitiesInfo) para sua correspondencia não gerenciada(WICRawCapabilitiesInfo).
			WICRawCapabilitiesInfo* ConverterWICRawCapabilitiesInfoManaged_ToUnmanaged(CA_WICRawCapabilitiesInfo^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICRawCapabilitiesInfo* EstruturaRetorno = CriarEstrutura<WICRawCapabilitiesInfo>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICRawCapabilitiesInfo));

				//Define os dados.
				EstruturaRetorno->cbSize = Param_Estrutura->cbSize;
				EstruturaRetorno->CodecMinorVersion = Param_Estrutura->CodecMinorVersion;
				EstruturaRetorno->CodecMajorVersion = Param_Estrutura->CodecMajorVersion;
				EstruturaRetorno->ExposureCompensationSupport = static_cast<WICRawCapabilities>(Param_Estrutura->CodecMajorVersion);
				EstruturaRetorno->ContrastSupport = static_cast<WICRawCapabilities>(Param_Estrutura->ContrastSupport);
				EstruturaRetorno->RGBWhitePointSupport = static_cast<WICRawCapabilities>(Param_Estrutura->RGBWhitePointSupport);
				EstruturaRetorno->NamedWhitePointSupport = static_cast<WICRawCapabilities>(Param_Estrutura->NamedWhitePointSupport);
				EstruturaRetorno->NamedWhitePointSupportMask = Param_Estrutura->NamedWhitePointSupportMask;
				EstruturaRetorno->KelvinWhitePointSupport = static_cast<WICRawCapabilities>(Param_Estrutura->KelvinWhitePointSupport);
				EstruturaRetorno->GammaSupport = static_cast<WICRawCapabilities>(Param_Estrutura->GammaSupport);
				EstruturaRetorno->TintSupport = static_cast<WICRawCapabilities>(Param_Estrutura->TintSupport);
				EstruturaRetorno->SaturationSupport = static_cast<WICRawCapabilities>(Param_Estrutura->SaturationSupport);
				EstruturaRetorno->SharpnessSupport = static_cast<WICRawCapabilities>(Param_Estrutura->SharpnessSupport);
				EstruturaRetorno->NoiseReductionSupport = static_cast<WICRawCapabilities>(Param_Estrutura->NoiseReductionSupport);
				EstruturaRetorno->DestinationColorProfileSupport = static_cast<WICRawCapabilities>(Param_Estrutura->DestinationColorProfileSupport);
				EstruturaRetorno->ToneCurveSupport = static_cast<WICRawCapabilities>(Param_Estrutura->ToneCurveSupport);
				EstruturaRetorno->RotationSupport = static_cast<WICRawRotationCapabilities>(Param_Estrutura->RotationSupport);
				EstruturaRetorno->RenderModeSupport = static_cast<WICRawCapabilities>(Param_Estrutura->RenderModeSupport);

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICRawCapabilitiesInfo) para sua correspondencia gerenciada(CA_WICRawCapabilitiesInfo).
			CA_WICRawCapabilitiesInfo^ ConverterWICRawCapabilitiesInfoUnmanaged_ToManaged(WICRawCapabilitiesInfo* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICRawCapabilitiesInfo^ EstruturaRetorno = gcnew CA_WICRawCapabilitiesInfo();

				//Define os dados.
				EstruturaRetorno->cbSize = Param_Estrutura->cbSize;
				EstruturaRetorno->CodecMinorVersion = Param_Estrutura->CodecMinorVersion;
				EstruturaRetorno->CodecMajorVersion = Param_Estrutura->CodecMajorVersion;
				EstruturaRetorno->ExposureCompensationSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->CodecMajorVersion);
				EstruturaRetorno->ContrastSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->ContrastSupport);
				EstruturaRetorno->RGBWhitePointSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->RGBWhitePointSupport);
				EstruturaRetorno->NamedWhitePointSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->NamedWhitePointSupport);
				EstruturaRetorno->NamedWhitePointSupportMask = Param_Estrutura->NamedWhitePointSupportMask;
				EstruturaRetorno->KelvinWhitePointSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->KelvinWhitePointSupport);
				EstruturaRetorno->GammaSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->GammaSupport);
				EstruturaRetorno->TintSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->TintSupport);
				EstruturaRetorno->SaturationSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->SaturationSupport);
				EstruturaRetorno->SharpnessSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->SharpnessSupport);
				EstruturaRetorno->NoiseReductionSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->NoiseReductionSupport);
				EstruturaRetorno->DestinationColorProfileSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->DestinationColorProfileSupport);
				EstruturaRetorno->ToneCurveSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->ToneCurveSupport);
				EstruturaRetorno->RotationSupport = static_cast<CA_WICRawRotationCapabilities>(Param_Estrutura->RotationSupport);
				EstruturaRetorno->RenderModeSupport = static_cast<CA_WICRawCapabilities>(Param_Estrutura->RenderModeSupport);


				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICDdsFormatInfo) para sua correspondencia não gerenciada(WICDdsFormatInfo).
			WICDdsFormatInfo* ConverterWICDdsFormatInfoManaged_ToUnmanaged(CA_WICDdsFormatInfo^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICDdsFormatInfo* EstruturaRetorno = CriarEstrutura<WICDdsFormatInfo>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICDdsFormatInfo));

				//Define os dados.
				EstruturaRetorno->DxgiFormat = static_cast<DXGI_FORMAT>(Param_Estrutura->DxgiFormat);
				EstruturaRetorno->BlockWidth = Param_Estrutura->BlockWidth;
				EstruturaRetorno->BlockHeight = Param_Estrutura->BlockHeight;
				EstruturaRetorno->BytesPerBlock = Param_Estrutura->BytesPerBlock;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICDdsFormatInfo) para sua correspondencia gerenciada(CA_WICDdsFormatInfo).
			CA_WICDdsFormatInfo^ ConverterWICDdsFormatInfoUnmanaged_ToManaged(WICDdsFormatInfo* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICDdsFormatInfo^ EstruturaRetorno = gcnew CA_WICDdsFormatInfo();

				//Define os dados.
				EstruturaRetorno->DxgiFormat = static_cast<CA_DXGI_FORMAT>(Param_Estrutura->DxgiFormat);
				EstruturaRetorno->BlockWidth = Param_Estrutura->BlockWidth;
				EstruturaRetorno->BlockHeight = Param_Estrutura->BlockHeight;
				EstruturaRetorno->BytesPerBlock = Param_Estrutura->BytesPerBlock;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICJpegFrameHeader) para sua correspondencia não gerenciada(WICJpegFrameHeader).
			WICJpegFrameHeader* ConverterWICJpegFrameHeaderManaged_ToUnmanaged(CA_WICJpegFrameHeader^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICJpegFrameHeader* EstruturaRetorno = CriarEstrutura<WICJpegFrameHeader>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICJpegFrameHeader));

				//Define os dados.
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->TransferMatrix = static_cast<WICJpegTransferMatrix>(Param_Estrutura->TransferMatrix);
				EstruturaRetorno->ScanType = static_cast<WICJpegScanType>(Param_Estrutura->ScanType);
				EstruturaRetorno->cComponents = Param_Estrutura->cComponents;
				EstruturaRetorno->ComponentIdentifiers = Param_Estrutura->ComponentIdentifiers;
				EstruturaRetorno->SampleFactors = static_cast<DWORD>(Param_Estrutura->SampleFactors);
				EstruturaRetorno->QuantizationTableIndices = static_cast<DWORD>(Param_Estrutura->QuantizationTableIndices);

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICJpegFrameHeader) para sua correspondencia gerenciada(CA_WICJpegFrameHeader).
			CA_WICJpegFrameHeader^ ConverterWICJpegFrameHeaderUnmanaged_ToManaged(WICJpegFrameHeader* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICJpegFrameHeader^ EstruturaRetorno = gcnew CA_WICJpegFrameHeader();

				//Define os dados.
				EstruturaRetorno->Width = Param_Estrutura->Width;
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->TransferMatrix = static_cast<CA_WICJpegTransferMatrix>(Param_Estrutura->TransferMatrix);
				EstruturaRetorno->ScanType = static_cast<CA_WICJpegScanType>(Param_Estrutura->ScanType);
				EstruturaRetorno->cComponents = Param_Estrutura->cComponents;
				EstruturaRetorno->ComponentIdentifiers = Param_Estrutura->ComponentIdentifiers;
				EstruturaRetorno->SampleFactors = static_cast<CA_WIC_IWICJpegFrameDecode>(Param_Estrutura->SampleFactors);
				EstruturaRetorno->QuantizationTableIndices = static_cast<CA_WIC_IWICJpegFrameDecode>(Param_Estrutura->QuantizationTableIndices);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICJpegScanHeader) para sua correspondencia não gerenciada(WICJpegScanHeader).
			WICJpegScanHeader* ConverterWICJpegScanHeaderManaged_ToUnmanaged(CA_WICJpegScanHeader^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICJpegScanHeader* EstruturaRetorno = CriarEstrutura<WICJpegScanHeader>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICJpegScanHeader));

				//Define os dados.
				EstruturaRetorno->cComponents = Param_Estrutura->cComponents;
				EstruturaRetorno->RestartInterval = Param_Estrutura->RestartInterval;
				EstruturaRetorno->ComponentSelectors = Param_Estrutura->ComponentSelectors;
				EstruturaRetorno->HuffmanTableIndices = static_cast<DWORD>(Param_Estrutura->HuffmanTableIndices);
				EstruturaRetorno->StartSpectralSelection = Param_Estrutura->StartSpectralSelection;
				EstruturaRetorno->EndSpectralSelection = Param_Estrutura->EndSpectralSelection;
				EstruturaRetorno->SuccessiveApproximationHigh = Param_Estrutura->SuccessiveApproximationHigh;
				EstruturaRetorno->SuccessiveApproximationLow = Param_Estrutura->SuccessiveApproximationLow;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICJpegScanHeader) para sua correspondencia gerenciada(CA_WICJpegScanHeader).
			CA_WICJpegScanHeader^ ConverterWICJpegScanHeaderUnmanaged_ToManaged(WICJpegScanHeader* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICJpegScanHeader^ EstruturaRetorno = gcnew CA_WICJpegScanHeader();

				//Define os dados.
				EstruturaRetorno->cComponents = Param_Estrutura->cComponents;
				EstruturaRetorno->RestartInterval = Param_Estrutura->RestartInterval;
				EstruturaRetorno->ComponentSelectors = Param_Estrutura->ComponentSelectors;
				EstruturaRetorno->HuffmanTableIndices =  static_cast<CA_WIC_IWICJpegFrameDecode>(Param_Estrutura->HuffmanTableIndices);
				EstruturaRetorno->StartSpectralSelection = Param_Estrutura->StartSpectralSelection;
				EstruturaRetorno->EndSpectralSelection = Param_Estrutura->EndSpectralSelection;
				EstruturaRetorno->SuccessiveApproximationHigh = Param_Estrutura->SuccessiveApproximationHigh;
				EstruturaRetorno->SuccessiveApproximationLow = Param_Estrutura->SuccessiveApproximationLow;

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICMetadataPattern) para sua correspondencia não gerenciada(WICMetadataPattern).
			//Libere a memória dos buffers nativos(Pattern & Mask) antes de liberar a estrutura.
			WICMetadataPattern* ConverterWICMetadataPatternManaged_ToUnmanaged(CA_WICMetadataPattern^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICMetadataPattern* EstruturaRetorno = CriarEstrutura<WICMetadataPattern>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICMetadataPattern));

				//Define os dados.
				EstruturaRetorno->Position.QuadPart = Param_Estrutura->Position;
				EstruturaRetorno->DataOffset.QuadPart = Param_Estrutura->DataOffset;
				EstruturaRetorno->Length = static_cast<ULONG>(Param_Estrutura->Length);

				//Aloca memória para os Bytes.
				//(ATENÇÃO) Parece que segundo a documentação a largua do (EstruturaRetorno->Mask) é igual ao do (EstruturaRetorno->Pattern) 
				EstruturaRetorno->Pattern = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->Length));
				EstruturaRetorno->Mask = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->Length));

				//Copia os dados para o array nativo.
				CopiarItensTo_ArrayNativo(&EstruturaRetorno->Pattern, Param_Estrutura->Pattern, static_cast<UINT32>(Param_Estrutura->Length));
				CopiarItensTo_ArrayNativo(&EstruturaRetorno->Mask, Param_Estrutura->Mask, static_cast<UINT32>(Param_Estrutura->Length));

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICMetadataPattern) para sua correspondencia gerenciada(CA_WICMetadataPattern).
			CA_WICMetadataPattern^ ConverterWICMetadataPatternUnmanaged_ToManaged(WICMetadataPattern* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICMetadataPattern^ EstruturaRetorno = gcnew CA_WICMetadataPattern();

				//Define os dados.
				EstruturaRetorno->Position = Param_Estrutura->Position.QuadPart;
				EstruturaRetorno->DataOffset = Param_Estrutura->DataOffset.QuadPart;
				EstruturaRetorno->Length = static_cast<UInt64>(Param_Estrutura->Length);

				//Cria as matrizes
				//(ATENÇÃO) Parece que segundo a documentação a largua do (EstruturaRetorno->Mask) é igual ao do (EstruturaRetorno->Pattern) 
				EstruturaRetorno->Pattern = gcnew cli::array<Byte>(static_cast<int>(EstruturaRetorno->Length));
				EstruturaRetorno->Mask = gcnew cli::array<Byte>(static_cast<int>(EstruturaRetorno->Length));

				//Copia os dados para as matrizes.
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->Pattern, Param_Estrutura->Pattern, static_cast<UINT32>(EstruturaRetorno->Length));
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->Mask, Param_Estrutura->Mask, static_cast<UINT32>(EstruturaRetorno->Length));

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICJpegScanHeader) para sua correspondencia não gerenciada(WICMetadataHeader).
			WICMetadataHeader* ConverterWICMetadataHeaderManaged_ToUnmanaged(CA_WICMetadataHeader^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICMetadataHeader* EstruturaRetorno = CriarEstrutura<WICMetadataHeader>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICMetadataHeader));

				//Define os dados.
				EstruturaRetorno->Length = static_cast<ULONG>(Param_Estrutura->Length);
				EstruturaRetorno->Position.QuadPart = Param_Estrutura->Position;
				EstruturaRetorno->DataOffset.QuadPart = Param_Estrutura->DataOffset;

				//Aloca memória para o buffer.
				EstruturaRetorno->Header = CriarMatrizUnidimensional<BYTE>(static_cast<DWORD>(Param_Estrutura->Length));

				//Copia os dados par ao buffer nativo.
				CopiarItensTo_ArrayNativo(&EstruturaRetorno->Header, Param_Estrutura->Header, static_cast<UINT32>(Param_Estrutura->Length));

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICMetadataHeader) para sua correspondencia gerenciada(CA_WICJpegScanHeader).
			CA_WICMetadataHeader^ ConverterWICMetadataHeaderUnmanaged_ToManaged(WICMetadataHeader* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICMetadataHeader^ EstruturaRetorno = gcnew CA_WICMetadataHeader();

				//Define os dados.
				EstruturaRetorno->Length = Param_Estrutura->Length;
				EstruturaRetorno->Position = Param_Estrutura->Position.QuadPart;
				EstruturaRetorno->DataOffset = Param_Estrutura->DataOffset.QuadPart;

				//Cria a matriz de bytes.
				EstruturaRetorno->Header = gcnew cli::array<Byte>(static_cast<int>(EstruturaRetorno->Length));

				//Copia os dados para a matriz gerenciada.
				CopiarItensTo_ArrayGerenciado(EstruturaRetorno->Header, Param_Estrutura->Header, static_cast<UINT32>(EstruturaRetorno->Length));

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICBitmapPlane) para sua correspondencia não gerenciada(WICBitmapPlane).
			WICBitmapPlane* ConverterWICBitmapPlaneManaged_ToUnmanaged(CA_WICBitmapPlane^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICBitmapPlane* EstruturaRetorno = CriarEstrutura<WICBitmapPlane>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICBitmapPlane));

				//Variaveis.
				GenPointer pBuffer = DefaultGenPointer;

				//Recupera o ponteiro para o buffer.
				static_cast<ICarenBuffer^>(Param_Estrutura->pbBuffer)->GetInternalPointer(pBuffer);

				//Define os dados.
				EstruturaRetorno->Format = CreateGuidFromString(Param_Estrutura->Format);
				EstruturaRetorno->cbBufferSize = Param_Estrutura->cbBufferSize;
				EstruturaRetorno->cbStride = Param_Estrutura->cbStride;
				EstruturaRetorno->pbBuffer = ConverterIntPtrTo<PBYTE>(pBuffer);

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICBitmapPlane) para sua correspondencia gerenciada(CA_WICBitmapPlane).
			CA_WICBitmapPlane^ ConverterWICBitmapPlaneUnmanaged_ToManaged(WICBitmapPlane* Param_Estrutura, bool Param_CopyBuffer = false)
			{
				//Estrutura a ser retornada.
				CA_WICBitmapPlane^ EstruturaRetorno = gcnew CA_WICBitmapPlane();

				//Define os dados.
				EstruturaRetorno->Format = ConverterGuidToString(Param_Estrutura->Format);
				EstruturaRetorno->cbBufferSize = Param_Estrutura->cbBufferSize;
				EstruturaRetorno->cbStride = Param_Estrutura->cbStride;

				//Cria a interface que vai conter o buffer.
				EstruturaRetorno->pbBuffer = gcnew CarenBuffer();

				//Define o ponteiro na interface.
				static_cast<ICarenBuffer^>(EstruturaRetorno->pbBuffer)->CreateBuffer(IntPtr(Param_Estrutura->pbBuffer), Param_CopyBuffer, EstruturaRetorno->cbBufferSize, EstruturaRetorno->cbBufferSize);

				//Retorna o resultado
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_WICBitmapPlaneDescription) para sua correspondencia não gerenciada(WICBitmapPlaneDescription).
			WICBitmapPlaneDescription* ConverterWICBitmapPlaneDescriptionManaged_ToUnmanaged(CA_WICBitmapPlaneDescription^ Param_Estrutura)
			{
				//Estrutura a ser retornada.
				WICBitmapPlaneDescription* EstruturaRetorno = CriarEstrutura<WICBitmapPlaneDescription>();

				//Preenche tudo com zero e inicializa as estruturas e unions se houver.
				ZeroMemory(EstruturaRetorno, sizeof(WICBitmapPlaneDescription));

				//Define os dados.
				EstruturaRetorno->Format = CreateGuidFromString(Param_Estrutura->Format);
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;

				//Retorna o resultado
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(WICBitmapPlaneDescription) para sua correspondencia gerenciada(CA_WICBitmapPlaneDescription).
			CA_WICBitmapPlaneDescription^ ConverterWICBitmapPlaneDescriptionUnmanaged_ToManaged(WICBitmapPlaneDescription* Param_Estrutura)
			{
				//Estrutura a ser retornada.
				CA_WICBitmapPlaneDescription^ EstruturaRetorno = gcnew CA_WICBitmapPlaneDescription();

				//Define os dados.
				EstruturaRetorno->Format = ConverterGuidToString(Param_Estrutura->Format);
				EstruturaRetorno->Height = Param_Estrutura->Height;
				EstruturaRetorno->Width = Param_Estrutura->Width;

				//Retorna o resultado
				return EstruturaRetorno;
			}








			// Windows Estruturas

			//Converte uma estrutura gerenciada(CA_STATSTG) para sua correspondencia não gerenciada(STATSTG).
			STATSTG* ConverterWindows_STATSTGManaged_ToUnManaged(CA_STATSTG^ Param_Estrutura)
			{
				//Variavel a ser retornada.
				STATSTG* EstruturaRetorno = CriarEstrutura<STATSTG>();

				//Inicializa todos os itens da estrutura com NULL.
				ZeroMemory(EstruturaRetorno, sizeof(STATSTG));

				//Variaveis
				ULARGE_INTEGER SizeStream = { 0 };
				_FILETIME FileTime_m = { 0 };
				_FILETIME FileTime_c = { 0 };
				_FILETIME FileTime_a = { 0 };

				//Define os dados das variaveis
				SizeStream.QuadPart = Param_Estrutura->cbSize;

				//Define os dados dos times.
				FileTime_m.dwLowDateTime = Param_Estrutura->mtime->dwLowDateTime;
				FileTime_m.dwHighDateTime = Param_Estrutura->mtime->dwHighDateTime;

				FileTime_c.dwLowDateTime = Param_Estrutura->ctime->dwLowDateTime;
				FileTime_c.dwHighDateTime = Param_Estrutura->ctime->dwHighDateTime;

				FileTime_a.dwLowDateTime = Param_Estrutura->atime->dwLowDateTime;
				FileTime_a.dwHighDateTime = Param_Estrutura->atime->dwHighDateTime;

				//Define os dados na estrutura
				EstruturaRetorno->pwcsName = StringObjetoValido(Param_Estrutura->pwcsName) ? ConverterStringToWCHAR(Param_Estrutura->pwcsName) : Nulo;
				EstruturaRetorno->type = static_cast<STGTY>(Param_Estrutura->type);
				EstruturaRetorno->cbSize = SizeStream;
				EstruturaRetorno->atime = FileTime_a;
				EstruturaRetorno->ctime = FileTime_c;
				EstruturaRetorno->mtime = FileTime_m;
				EstruturaRetorno->grfMode = static_cast<DWORD>(Param_Estrutura->grfMode);
				EstruturaRetorno->grfLocksSupported = static_cast<DWORD>(Param_Estrutura->grfLocksSupported);
				EstruturaRetorno->grfStateBits = static_cast<DWORD>(Param_Estrutura->grfStateBits);
				EstruturaRetorno->clsid = StringObjetoValido(Param_Estrutura->clsid) ? CreateGuidFromString(Param_Estrutura->clsid) : GUID_NULL;


				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(STATSTG) para sua correspondencia gerenciada(CA_STATSTG).
			CA_STATSTG^ ConverterWindows_STATSTGUnManaged_ToManaged(STATSTG* Param_Estrutura)
			{
				//Variavel a ser retornada.
				CA_STATSTG^ EstruturaRetorno = gcnew CA_STATSTG();

				//Define os dados na estrutura
				EstruturaRetorno->pwcsName = ObjetoValido(Param_Estrutura->pwcsName) ? gcnew String(Param_Estrutura->pwcsName) : nullptr;
				EstruturaRetorno->type = static_cast<CA_STGTY>(Param_Estrutura->type);
				EstruturaRetorno->cbSize = Param_Estrutura->cbSize.QuadPart;
				EstruturaRetorno->atime = gcnew CA_FILETIME();
				EstruturaRetorno->ctime = gcnew CA_FILETIME();
				EstruturaRetorno->mtime = gcnew CA_FILETIME();
				EstruturaRetorno->grfMode = static_cast<UInt32>(Param_Estrutura->grfMode);
				EstruturaRetorno->grfLocksSupported = static_cast<CA_LOCKTYPE>(Param_Estrutura->grfLocksSupported);
				EstruturaRetorno->grfStateBits = static_cast<UInt32>(Param_Estrutura->grfStateBits);
				EstruturaRetorno->clsid = Param_Estrutura->clsid == GUID_NULL ? ConverterGuidToString(Param_Estrutura->clsid) : nullptr;

				//Define os dados dos filetimes.
				EstruturaRetorno->atime->dwLowDateTime = Param_Estrutura->atime.dwLowDateTime;
				EstruturaRetorno->atime->dwHighDateTime = Param_Estrutura->atime.dwHighDateTime;

				EstruturaRetorno->ctime->dwLowDateTime = Param_Estrutura->ctime.dwLowDateTime;
				EstruturaRetorno->ctime->dwHighDateTime = Param_Estrutura->ctime.dwHighDateTime;

				EstruturaRetorno->mtime->dwLowDateTime = Param_Estrutura->mtime.dwLowDateTime;
				EstruturaRetorno->mtime->dwHighDateTime = Param_Estrutura->mtime.dwHighDateTime;
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}

		};
	}
}