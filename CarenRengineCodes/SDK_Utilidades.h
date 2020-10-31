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
using namespace CarenRengine::SDKBase::Interfaces;
      
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
			Utilidades()
			{
			}

			~Utilidades()
			{}

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
				//Verifica se o OLECHAR é valido e destroi
				if (DadosGuid != NULL)
				{
					//Libera os dados.
					delete[] DadosGuid;
				}

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
			void CopiarBufferNativo_ToGerenciado(TipoArrayNativo** Param_Buffer, cli::array<TipoArrayGerenciado>^% Param_BufferNativo, UINT32 Param_TamanhoBuffer)
			{
				//Cria um pin para o buffer gerenciado.
				pin_ptr<TipoArrayGerenciado> PinToIndexZeroBuffer = &Param_BufferNativo[0];

				//Converte o pinptr para um buffer do tipo de destino.
				TipoArrayNativo* pBufferDestino = static_cast<TipoArrayNativo*>(PinToIndexZeroBuffer);

				//Verifica se é valido
				if (!ObjetoValido(pBufferDestino))
					throw gcnew NullReferenceException("(CopiarBufferNativo_ToGerenciado) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

				//Copia os dados do nativo para o gerenciado.
				std::copy(*Param_Buffer, (*Param_Buffer) + Param_TamanhoBuffer, pBufferDestino);
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

			//Converte uma PropVariant Gerenciada para uma não gerenciada.
			bool ConvertPropVariantManagedToUnamaged(SDKBase::Estruturas::CA_PropVariant^ Param_PropVariantManaged, PROPVARIANT& Param_PropVariant)
			{
				//Variavel que vai retornar o resultado.
				bool EstruturaRetorno = false;

				//Variaveis
				GUID GuidChave = GUID_NULL;
				BLOB BlobData = {};
				IUnknown* pInterfaceDesconhecida = NULL;
				char* StringData = NULL;
				CarenResult EstruturaRetornoCode = CarenResult(ResultCode::ER_FAIL, false);

				//Abre um switch para definir na PropVariant o valor adicional.
				switch (Param_PropVariantManaged->_TipoDados)
				{
				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_CY:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DISPATCH:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_VARIANT:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_DECIMAL:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_BSTR_BLOB:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_VOID:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_EMPTY:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_NULL:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				case CarenRengine::SDKBase::Enumeracoes::CA_PropVariant_TYPE::TP_String:
					//Define o tipo da PropVariant
					Param_PropVariant.vt = VT_LPWSTR;

					//Converter a String.
					StringData = ConverterStringToChar(Param_PropVariantManaged->Var_String);

					//Converter para um WCHAR
					Param_PropVariant.pwszVal = (WCHAR*)ConverterConstCharToConstWCHAR(StringData);
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
					*Param_PropVariant.puuid = CreateGuidFromString(Param_PropVariantManaged->Var_Guid);
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
					EstruturaRetornoCode = Param_PropVariantManaged->Var_ICaren->RecuperarPonteiro((LPVOID*)&pInterfaceDesconhecida);

					//Verifica se obteve com sucesso
					if (EstruturaRetornoCode.StatusCode == ResultCode::SS_OK)
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
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;

				default:
					//Não suportado.
					EstruturaRetorno = false;

					//Sai do método
					goto Done;
					break;
				}

				//Define sucesso na operação
				EstruturaRetorno = true;

			Done:;
				//Verifica se não houve erro e limpa alguns dados.
				if (!EstruturaRetorno)
				{
					//Verifica se a string ainda é valida.
					if (StringData != NULL)
					{
						//Deleta a string.
						delete StringData;
					}
				}

				//Retorna o resultado.
				return EstruturaRetorno;
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




			//Converte uma estrutura gerenciada(CA_DXGI_RGBA) para um ponteiro que contém um array dos 4 componentes da cor RGBA.
			//Chame um (delete[]) quando não precisar mais do ponteiro.
			FLOAT* Converter_DXGIRGBATo_FloatColor(SDKBase::Estruturas::CA_DXGI_RGBA^ Param_RGBA)
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
			SDKBase::Estruturas::CA_DXGI_RGBA^ Converter_FloatColorTo_DXGIRGBA(FLOAT* pRGBAColor)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_RGBA^ ColorRGBA = gcnew SDKBase::Estruturas::CA_DXGI_RGBA();

				//Preenche os dados da estrutura.
				ColorRGBA->Vermelho = pRGBAColor[0]; //R
				ColorRGBA->Verde = pRGBAColor[1];    //G
				ColorRGBA->Azul = pRGBAColor[2];     //B
				ColorRGBA->Alfa = pRGBAColor[3];     //A

				//Retorna o resultado
				return ColorRGBA;
			}


			//Converte a estrutura não gerenciada(RECT) para sua correspondencia gerenciada(CA_RECT).
			SDKBase::Estruturas::CA_RECT^ ConverterRECTUnmanagedToManaged(PRECT Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_RECT^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_RECT();

				//Define os dados da estrutura.
				EstruturaRetorno->Direita = Param_Estrutura->right;
				EstruturaRetorno->Esquerda = Param_Estrutura->left;
				EstruturaRetorno->Fundo = Param_Estrutura->bottom;
				EstruturaRetorno->Topo = Param_Estrutura->top;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_RECT) para sua correspondencia não gerenciada(RECT).
			PRECT ConverterRECTManagedToUnmanaged(SDKBase::Estruturas::CA_RECT^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_LUID^ ConverterLUIDUnmanagedToManaged(PLUID Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_LUID^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_LUID();

				//Define os dados da estrutura.
				EstruturaRetorno->HighPart = Param_Estrutura->HighPart;
				EstruturaRetorno->LowPart = Param_Estrutura->LowPart;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_LUID) para sua correspondencia não gerenciada(LUID).
			PLUID ConverterLUIDManagedToUnmanaged(SDKBase::Estruturas::CA_LUID^ Param_Estrutura)
			{
				//Estrutura que será retornada ao usuário.
				PLUID EstruturaRetorno = CriarEstrutura<LUID>();

				//Define os dados na estrutura.
				EstruturaRetorno->HighPart = Param_Estrutura->HighPart;
				EstruturaRetorno->LowPart = Param_Estrutura->LowPart;

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte a estrutura não gerenciada(WAVEFORMATEX) para sua correspondencia gerenciada(CA_WAVEFORMATEX).
			SDKBase::Estruturas::CA_WAVEFORMATEX^ ConverterWaveFormatexUnmanagedToManaged(WAVEFORMATEX* pWaveFormat)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_WAVEFORMATEX^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_WAVEFORMATEX();

				//Define os dados na estrutura
				EstruturaRetorno->AlinhamentoBloco = static_cast<UInt16>(pWaveFormat->nBlockAlign);
				EstruturaRetorno->BitsPorAmostra = static_cast<UInt16>(pWaveFormat->wBitsPerSample);
				EstruturaRetorno->BytesPorSegundo = static_cast<UInt32>(pWaveFormat->nAvgBytesPerSec);
				EstruturaRetorno->Canais = static_cast<UInt16>(pWaveFormat->nChannels);
				EstruturaRetorno->AmostrasPorSegundo = static_cast<UInt32>(pWaveFormat->nSamplesPerSec);
				EstruturaRetorno->TagFormatoAudio = static_cast<UInt16>(pWaveFormat->wFormatTag);
				EstruturaRetorno->Size = static_cast<UInt16>(pWaveFormat->cbSize);
				EstruturaRetorno->TamanhoEstrutura = sizeof(WAVEFORMATEX);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_WAVEFORMATEX) para sua correspondencia não gerenciada(WAVEFORMATEX).
			WAVEFORMATEX* ConverterWaveFormatexManagedToUnamaged(SDKBase::Estruturas::CA_WAVEFORMATEX^ Param_WaveFormatex)
			{
				//Estrutura que será retornada ao usuário.
				WAVEFORMATEX* pWaveFormato = CriarEstrutura<WAVEFORMATEX>();

				//Define os dados na estrutura.
				pWaveFormato->cbSize = Param_WaveFormatex->Size;
				pWaveFormato->nAvgBytesPerSec = Param_WaveFormatex->BytesPorSegundo;
				pWaveFormato->nBlockAlign = Param_WaveFormatex->AlinhamentoBloco;
				pWaveFormato->nChannels = Param_WaveFormatex->Canais;
				pWaveFormato->nSamplesPerSec = Param_WaveFormatex->AmostrasPorSegundo;
				pWaveFormato->wBitsPerSample = Param_WaveFormatex->BitsPorAmostra;
				pWaveFormato->wFormatTag = Param_WaveFormatex->TagFormatoAudio;

				//Retorna a estrutura não gerenciada
				return pWaveFormato;
			}


			//Converte a estrutura não gerenciada(WAVEFORMATEXTENSIBLE) para sua correspondencia gerenciada(CA_WAVEFORMATEXEXTENSIBLE).
			SDKBase::Estruturas::CA_WAVEFORMATEXEXTENSIBLE^ ConverterWaveformatExtensibleUnmanagedToManaged(WAVEFORMATEXTENSIBLE* pWaveFormatExtensible)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_WAVEFORMATEXEXTENSIBLE^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_WAVEFORMATEXEXTENSIBLE();

				//Define os dados da estrutura WaveFormatex.
				EstruturaRetorno->Formato = ConverterWaveFormatexUnmanagedToManaged(&pWaveFormatExtensible->Format);

				//Define o restante dos dados.
				EstruturaRetorno->MascaraCanal = static_cast<UInt32>(pWaveFormatExtensible->dwChannelMask);
				EstruturaRetorno->BitsValidosPorAmostra = static_cast<UInt16>(pWaveFormatExtensible->Samples.wValidBitsPerSample);
				EstruturaRetorno->AmostrasPorBloco = static_cast<UInt16>(pWaveFormatExtensible->Samples.wSamplesPerBlock);
				EstruturaRetorno->SubFormato = ConverterGuidToString(pWaveFormatExtensible->SubFormat);
				EstruturaRetorno->Reservado = static_cast<UInt16>(pWaveFormatExtensible->Samples.wReserved);
				EstruturaRetorno->TamanhoEstrutura = sizeof(WAVEFORMATEXTENSIBLE);

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_WAVEFORMATEXEXTENSIBLE) para sua correspondencia não gerenciada(WAVEFORMATEXTENSIBLE).
			WAVEFORMATEXTENSIBLE* ConverterWaveformatExtensibleManagedToUnamaged(SDKBase::Estruturas::CA_WAVEFORMATEXEXTENSIBLE^ Param_WaveFormatex)
			{
				//Estrutura que será retornada ao usuário.
				WAVEFORMATEXTENSIBLE* pWaveFormatoEx = CriarEstrutura<WAVEFORMATEXTENSIBLE>();
				WAVEFORMATEX* pWaveFormato = ConverterWaveFormatexManagedToUnamaged(Param_WaveFormatex->Formato);

				//Preenche os dados da estrutura principal.
				pWaveFormatoEx->dwChannelMask = Param_WaveFormatex->MascaraCanal;
				pWaveFormatoEx->SubFormat = CreateGuidFromString(Param_WaveFormatex->SubFormato);
				pWaveFormatoEx->Samples.wSamplesPerBlock = Param_WaveFormatex->AmostrasPorBloco;
				pWaveFormatoEx->Samples.wValidBitsPerSample = Param_WaveFormatex->BitsValidosPorAmostra;
				pWaveFormatoEx->Samples.wReserved = Param_WaveFormatex->Reservado;

				//Preenche os dados da estrutura secundaria.
				pWaveFormatoEx->Format = *pWaveFormato;

				//Retorna a estrutura não gerenciada
				return pWaveFormatoEx;
			}


			//Converte uma enumeração nativa (_MF_ATTRIBUTE_TYPE) para sua correspondência gerenciada(CA_ATTRIBUTE_TYPE).
			SDKBase::Enumeracoes::CA_ATTRIBUTE_TYPE ConverterMF_ATTRIBUTE_TYPEUnmanagedToManaged(_MF_ATTRIBUTE_TYPE Param_TipoAtributo)
			{
				//Variavel que vai retornar.
				CA_ATTRIBUTE_TYPE Atributo;

				//Abre um switch para verificar o tipo do atributo e definir na variavel de retorno.
				switch (Param_TipoAtributo)
				{
				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::UINT32;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::UINT64;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::DOUBLE;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::GUID;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::STRING;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::BLOB;
				}
				break;

				case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_IUNKNOWN:
				{
					//Define o tipo do atributo.
					Atributo = CA_ATTRIBUTE_TYPE::IUNKNOWN;
				}
				break;

				default:
					break;
				}

				//Retorna o resultado
				return Atributo;
			}

			//Converte um GUID que define o subtipo de um midia principal para a enumeração gerenciada(CA_Midia_SubTipo).
			SDKBase::Enumeracoes::CA_Midia_SubTipo ConverterGUIDSubtipoMidia_ToMidia_SubTipo(GUID Param_GuidSubTipoMidia)
			{
				//Variavel que via conter o subtipo.
				CA_Midia_SubTipo FormatoTipoPrincipal;

				/////////////////////
				//FORMATOS DE AUDIO//
				/////////////////////

				if (MEDIASUBTYPE_RAW_AAC1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_RAW_ACC1;

				}
				else if (MFAudioFormat_AAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_AAC;

				}
				else if (MFAudioFormat_ADTS == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_ADTS;

				}
				else if (MFAudioFormat_ALAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_ALAC;

				}
				else if (MFAudioFormat_AMR_NB == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_AMR_NB;

				}
				else if (MFAudioFormat_AMR_WB == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_AMR_WB;

				}
				else if (MFAudioFormat_AMR_WP == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_AMR_WP;

				}
				else if (MFAudioFormat_Dolby_AC3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Dolby_AC3;

				}
				else if (MFAudioFormat_Dolby_AC3_SPDIF == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Dolby_AC3_SPDIF;

				}
				else if (MFAudioFormat_Dolby_DDPlus == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Dolby_DDPlus;

				}
				else if (MFAudioFormat_DRM == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_DRM;

				}
				else if (MFAudioFormat_DTS == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_DTS;

				}
				else if (MFAudioFormat_FLAC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_FLAC;

				}
				else if (MFAudioFormat_Float == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Float;

				}
				else if (MFAudioFormat_Float_SpatialObjects == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Float_SpatialObjects;

				}
				else if (MFAudioFormat_MP3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_MP3;

				}
				else if (MFAudioFormat_MPEG == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_MPEG;

				}
				else if (MFAudioFormat_MSP1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_MSP1;

				}
				else if (MFAudioFormat_Opus == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_Opus;

				}
				else if (MFAudioFormat_PCM == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_PCM;

				}
				else if (MFAudioFormat_WMASPDIF == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_WMASPDIF;

				}
				else if (MFAudioFormat_WMAudio_Lossless == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_WMAudio_Lossless;

				}
				else if (MFAudioFormat_WMAudioV8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_WMAudioV8;

				}
				else if (MFAudioFormat_WMAudioV9 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoAudio_WMAudioV9;

				}



				/////////////////////
				//FORMATOS DE VIDEO//
				/////////////////////

				else if (MFVideoFormat_RGB8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB8;

				}
				else if (MFVideoFormat_RGB555 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB555;

				}
				else if (MFVideoFormat_RGB565 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB565;

				}
				else if (MFVideoFormat_RGB24 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB24;

				}
				else if (MFVideoFormat_RGB32 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB32;

				}
				else if (MFVideoFormat_ARGB32 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_ARGB32;

				}
				else if (MFVideoFormat_A2R10G10B10 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_A2R10G10B10;

				}
				else if (MFVideoFormat_A16B16G16R16F == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_A16B16G16R16F;

				}
				else if (MFVideoFormat_AI44 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_AI44;

				}
				else if (MFVideoFormat_AYUV == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_AYUV;

				}
				else if (MFVideoFormat_I420 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_I420;

				}
				else if (MFVideoFormat_IYUV == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_IYUV;

				}
				else if (MFVideoFormat_NV11 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_NV11;

				}
				else if (MFVideoFormat_NV12 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_NV12;

				}
				else if (MFVideoFormat_UYVY == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_UYVY;

				}
				else if (MFVideoFormat_Y41P == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y41P;

				}
				else if (MFVideoFormat_Y41T == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y41T;

				}
				else if (MFVideoFormat_Y42T == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y42T;

				}
				else if (MFVideoFormat_YUY2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_YUY2;

				}
				else if (MFVideoFormat_YVU9 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_YVU9;

				}
				else if (MFVideoFormat_YV12 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_YV12;

				}
				else if (MFVideoFormat_YVYU == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_YVYU;

				}
				else if (MFVideoFormat_P010 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_P010;

				}
				else if (MFVideoFormat_P016 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_P016;

				}
				else if (MFVideoFormat_P210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_P210;

				}
				else if (MFVideoFormat_P216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_P216;

				}
				else if (MFVideoFormat_v210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_v210;

				}
				else if (MFVideoFormat_v216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_v216;

				}
				else if (MFVideoFormat_v410 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_v410;

				}
				else if (MFVideoFormat_Y210 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y210;

				}
				else if (MFVideoFormat_Y216 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y216;

				}
				else if (MFVideoFormat_Y410 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y410;

				}
				else if (MFVideoFormat_Y416 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_Y416;

				}
				else if (MFVideoFormat_L8 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_L8;

				}
				else if (MFVideoFormat_L16 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_L16;

				}
				else if (MFVideoFormat_D16 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_D16;

				}
				else if (MFVideoFormat_DV25 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DV25;

				}
				else if (MFVideoFormat_DV50 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DV50;

				}
				else if (MFVideoFormat_DVC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DVC;

				}
				else if (MFVideoFormat_DVH1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DVH1;

				}
				else if (MFVideoFormat_DVHD == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DVHD;

				}
				else if (MFVideoFormat_DVSD == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DVSD;

				}
				else if (MFVideoFormat_DVSL == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_DVSL;

				}
				else if (MFVideoFormat_H263 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_H263;

				}
				else if (MFVideoFormat_H264 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_H264;

				}
				else if (MFVideoFormat_H265 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_H265;

				}
				else if (MFVideoFormat_H264_ES == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_H264_ES;

				}
				else if (MFVideoFormat_HEVC == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_HEVC;

				}
				else if (MFVideoFormat_HEVC_ES == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_HEVC_ES;

				}
				else if (MFVideoFormat_M4S2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_M4S2;

				}
				else if (MFVideoFormat_MJPG == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MJPG;

				}
				else if (MFVideoFormat_MP43 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MP43;

				}
				else if (MFVideoFormat_MP4S == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MP4S;

				}
				else if (MFVideoFormat_MP4V == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MP4V;

				}
				else if (MFVideoFormat_MPEG2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_RGB8;

				}
				else if (MFVideoFormat_VP80 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_VP80;

				}
				else if (MFVideoFormat_VP90 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_VP90;

				}
				else if (MFVideoFormat_MPG1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MPG1;

				}
				else if (MFVideoFormat_MSS1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MSS1;

				}
				else if (MFVideoFormat_MSS2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_MSS2;

				}
				else if (MFVideoFormat_WMV1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_WMV1;

				}
				else if (MFVideoFormat_WMV2 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_WMV2;

				}
				else if (MFVideoFormat_WMV3 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_WMV3;

				}
				else if (MFVideoFormat_WVC1 == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_WVC1;

				}
				else if (MFVideoFormat_420O == Param_GuidSubTipoMidia)
				{
					//Define o formato principal da mídia e o seu Guid.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoVideo_420O;

				}
				else
				{
					//Formato desconhecido.
					FormatoTipoPrincipal = CA_Midia_SubTipo::FormatoMidia_Desconhecido;
				}

				//Retorna o formato da midia principal.
				return FormatoTipoPrincipal;
			}




			//Converte a estrutura não gerenciada(_MFT_INPUT_STREAM_INFO) para sua correspondencia gerenciada(CA_MFT_INPUT_STREAM_INFO).
			SDKBase::Estruturas::CA_MFT_INPUT_STREAM_INFO^ ConverterMFT_INPUT_STREAM_INFOUnmanagedToManaged(_MFT_INPUT_STREAM_INFO* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_MFT_INPUT_STREAM_INFO^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_MFT_INPUT_STREAM_INFO();

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
			_MFT_INPUT_STREAM_INFO* ConverterMFT_INPUT_STREAM_INFOManagedToUnamaged(SDKBase::Estruturas::CA_MFT_INPUT_STREAM_INFO^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_MFT_OUTPUT_STREAM_INFO^ ConverterMFT_OUTPUT_STREAM_INFOUnmanagedToManaged(_MFT_OUTPUT_STREAM_INFO* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_MFT_OUTPUT_STREAM_INFO^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_MFT_OUTPUT_STREAM_INFO();

				//Define os dados na estrutura.
				EstruturaRetorno->Alinhamento = Param_Estrutura->cbAlignment;
				EstruturaRetorno->Size = Param_Estrutura->cbSize;
				EstruturaRetorno->Flags = Param_Estrutura->dwFlags;

				//Retorna a estrutura
				return EstruturaRetorno;
			}

			//Covnerte uma estrutura gerenciada(CA_MFT_OUTPUT_STREAM_INFO) para sua correspondencia não gerenciada(_MFT_OUTPUT_STREAM_INFO).
			_MFT_OUTPUT_STREAM_INFO* ConverterMFT_OUTPUT_STREAM_INFOManagedToUnamaged(SDKBase::Estruturas::CA_MFT_OUTPUT_STREAM_INFO^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_MFT_OUTPUT_DATA_BUFFER^ ConverterMFT_OUTPUT_DATA_BUFFERUnmanagedToManaged(_MFT_OUTPUT_DATA_BUFFER* Param_Estrutura)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_MFT_OUTPUT_DATA_BUFFER^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_MFT_OUTPUT_DATA_BUFFER();

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
			_MFT_OUTPUT_DATA_BUFFER* ConverterMFT_OUTPUT_DATA_BUFFERManagedToUnamaged(SDKBase::Estruturas::CA_MFT_OUTPUT_DATA_BUFFER^ Param_Estrutura)
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
					Param_Estrutura->AmostraMidia->RecuperarPonteiro((LPVOID*)&pAmostra);

					//Define na estrutura.
					EstruturaRetorno->pSample = pAmostra;
				}
				if (ObjetoGerenciadoValido(Param_Estrutura->ColecaoEventos))
				{
					//Ponteiro para coleção.
					IMFCollection* pCollection = NULL;

					//Recupera o ponteiro
					Param_Estrutura->ColecaoEventos->RecuperarPonteiro((LPVOID*)&pCollection);

					//Define na estrutura.
					EstruturaRetorno->pEvents = pCollection;
				}

				//Retorna a estrutura não gerenciada
				return EstruturaRetorno;
			}


			//Converte a estrutura não gerenciada(SECURITY_ATTRIBUTES) para sua correspondencia gerenciada(CA_ATRIBUTOS_SEGURANCA).
			SDKBase::Estruturas::CA_ATRIBUTOS_SEGURANCA^ ConverterSECURITY_ATTRIBUTESUnmanagedToManaged(SECURITY_ATTRIBUTES* Param_AttrSeguranca)
			{
				//Cria a estrutura a ser retornada.
				SDKBase::Estruturas::CA_ATRIBUTOS_SEGURANCA^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_ATRIBUTOS_SEGURANCA();
				SDKBase::Estruturas::CA_DESCRITOR_SEGURANCA^ DescritorSegurança = nullptr;

				//Preenche os dados da estrutura principal
				EstruturaRetorno->bInheritHandle = Param_AttrSeguranca->bInheritHandle;
				EstruturaRetorno->SizeEstrutura = sizeof(SECURITY_ATTRIBUTES);

				//Verifica se for fornecido o descritor de segurança
				if (ObjetoValido(Param_AttrSeguranca->lpSecurityDescriptor))
				{
					//Cria a estrutura do descritor de segurança
					DescritorSegurança = gcnew SDKBase::Estruturas::CA_DESCRITOR_SEGURANCA();

					//Prenche os dados base
					DescritorSegurança->Control = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Control;
					DescritorSegurança->Revisao = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Revision;
					DescritorSegurança->Sbz1 = ((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Sbz1;

					//Preenche os dados dos ponteiros
					if (ObjetoValido(((SECURITY_DESCRIPTOR*)Param_AttrSeguranca->lpSecurityDescriptor)->Dacl))
					{
						//Cria a estrutura
						DescritorSegurança->Dacl = gcnew SDKBase::Estruturas::CA_ACL();

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
						DescritorSegurança->Dacl = gcnew SDKBase::Estruturas::CA_ACL();

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

			//Covnerte uma estrutura gerenciada(CA_ATRIBUTOS_SEGURANCA) para sua correspondencia não gerenciada(SECURITY_ATTRIBUTES).
			SECURITY_ATTRIBUTES* ConverterSECURITY_ATTRIBUTESManagedToUnamaged(SDKBase::Estruturas::CA_ATRIBUTOS_SEGURANCA^ Param_AttrSeguranca)
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


			//Converte uma estrutura gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE).
			MFTOPONODE_ATTRIBUTE_UPDATE* ConverterTopoNodeAttributesToUnamaged(SDKBase::Estruturas::CA_MFTOPONODE_ATTRIBUTE_UPDATE^ Param_ManagedStruct)
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
			SDKBase::Estruturas::CA_MFTOPONODE_ATTRIBUTE_UPDATE^ ConverterTopoNodeAttributesToManaged(MFTOPONODE_ATTRIBUTE_UPDATE* Param_EstruturaNativa)
			{
				//Variavel que vai ser retornada.
				SDKBase::Estruturas::CA_MFTOPONODE_ATTRIBUTE_UPDATE^ EstruturaConvertida = gcnew SDKBase::Estruturas::CA_MFTOPONODE_ATTRIBUTE_UPDATE();

				//Define os valores
				EstruturaConvertida->TipoAtributo = static_cast<SDKBase::Enumeracoes::CA_ATTRIBUTE_TYPE>(Param_EstruturaNativa->attrType);
				EstruturaConvertida->GUID = ConverterGuidToString(Param_EstruturaNativa->guidAttributeKey);
				EstruturaConvertida->NodeId = Param_EstruturaNativa->NodeId;
				EstruturaConvertida->d = Param_EstruturaNativa->d;
				EstruturaConvertida->u32 = Param_EstruturaNativa->u32;
				EstruturaConvertida->u64 = Param_EstruturaNativa->u64;

				//Retorna a estrutura.
				return EstruturaConvertida;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_FRAME_INFO) para sua correspondencia não gerenciada(DXGI_OUTDUPL_FRAME_INFO).
			DXGI_OUTDUPL_FRAME_INFO* ConverterDXGI_OUTDUPL_FRAME_INFOManaged_ToUnamaged(SDKBase::Estruturas::CA_DXGI_OUTDUPL_FRAME_INFO^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTDUPL_FRAME_INFO^ ConverterDXGI_OUTDUPL_FRAME_INFOUnamaged_ToManaged(DXGI_OUTDUPL_FRAME_INFO* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTDUPL_FRAME_INFO^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTDUPL_FRAME_INFO();

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


			//Converte uma estrutura gerenciada(CA_MIDIA_SINK_WRITER_ESTATISTICAS) para sua correspondencia não gerenciada(MF_SINK_WRITER_STATISTICS).
			MF_SINK_WRITER_STATISTICS* ConverterMF_SINK_WRITER_STATISTICSManagedToUnamaged(SDKBase::Estruturas::CA_MIDIA_SINK_WRITER_ESTATISTICAS^ Param_Estrutura)
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
			//Converte uma estrutura não gerenciada(MFTOPONODE_ATTRIBUTE_UPDATE) para sua correspondencia gerenciada(CA_MFTOPONODE_ATTRIBUTE_UPDATE).
			SDKBase::Estruturas::CA_MIDIA_SINK_WRITER_ESTATISTICAS^ ConverterMF_SINK_WRITER_STATISTICSUnamagedToManaged(MF_SINK_WRITER_STATISTICS* Param_Estrutura)
			{
				//Variavel que vai ser retornada.
				SDKBase::Estruturas::CA_MIDIA_SINK_WRITER_ESTATISTICAS^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_MIDIA_SINK_WRITER_ESTATISTICAS();

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
					Resultado = Param_Estrutura->bits->ObterPonteiroInterno(IntptrBuffer);
					
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
					EstruturaRetorno->bits->CriarBuffer(IntPtr(Param_Estrutura->bits), false, 0, 0);
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
					Param_Estrutura->colorContext->RecuperarPonteiro((LPVOID*)&pColorContext);
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
				Param_Estrutura->geometricMask->RecuperarPonteiro((LPVOID*)&pGeometryMask);
				Param_Estrutura->opacityBrush->RecuperarPonteiro((LPVOID*)&pBrushOpacity);

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
				EstruturaRetorno->geometricMask->AdicionarPonteiro(Param_Estrutura->geometricMask);
				EstruturaRetorno->opacityBrush->AdicionarPonteiro(Param_Estrutura->opacityBrush);

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
				Param_Estrutura->geometricMask->RecuperarPonteiro((LPVOID*)&pGeometryMask);
				Param_Estrutura->opacityBrush->RecuperarPonteiro((LPVOID*)&pBrushOpacity);

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
				EstruturaRetorno->geometricMask->AdicionarPonteiro(Param_Estrutura->geometricMask);
				EstruturaRetorno->opacityBrush->AdicionarPonteiro(Param_Estrutura->opacityBrush);

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
				Param_Estrutura->data->ObterPonteiroInterno(pBufferDados);

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
				EstruturaRetorno->data->CriarBuffer(IntPtr(const_cast<PBYTE>(Param_Estrutura->data)), false, EstruturaRetorno->byteWidth, EstruturaRetorno->byteWidth);
				
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
				Param_Estrutura->effect->RecuperarPonteiro((LPVOID*)&pMyEfeito);

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
				EstruturaRetorno->effect->AdicionarPonteiro(Param_Estrutura->effect);

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
				CarenResult Resultado = Param_Estrutura->fontFace->RecuperarPonteiro((LPVOID*)&pDwriteFontFace);

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
				CarenResult Resultado = EstruturaRetorno->fontFace->AdicionarPonteiro(Param_Estrutura->fontFace);

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
			SDKBase::Estruturas::CA_D3D11_BUFFER_DESC^ ConverterD3D11_BUFFER_DESCUnamaged_ToManaged(D3D11_BUFFER_DESC* Param_pBufferDesc)
			{
				//Variavel que vai ser retornada.
				SDKBase::Estruturas::CA_D3D11_BUFFER_DESC^ BufferDescManaged = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_DESC();

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
			D3D11_BUFFER_DESC* ConverterD3D11_BUFFER_DESCManaged_ToUnmanaged(SDKBase::Estruturas::CA_D3D11_BUFFER_DESC^ Param_BufferDesc)
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
			SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_DATA^ ConverterD3D11_SUBRESOURCE_DATAUnamaged_ToManaged(D3D11_SUBRESOURCE_DATA* Param_Estrutura, ICaren^% Param_ArmazemInitData)
			{
				//Variavel que vai ser retornada.
				SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_DATA^ EstruturaDestino = gcnew SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_DATA();

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
			D3D11_SUBRESOURCE_DATA* ConverterD3D11_SUBRESOURCE_DATAManaged_ToUnmanaged(SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_DATA^ Param_Estrutura)
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
					Param_Estrutura->SysMemoria->RecuperarPonteiro(&InitData);

					//Define o ponteiro no parametro
					EstruturaDestino->pSysMem = InitData;
				}

				//Retorna o ponteiro.
				return EstruturaDestino;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_BLEND_DESC) para sua correspondencia não gerenciada(D3D11_BLEND_DESC).
			D3D11_BLEND_DESC* ConverterD3D11_BLEND_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_BLEND_DESC^ Param_BlendDesc)
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
			SDKBase::Estruturas::CA_D3D11_BLEND_DESC^ ConverterD3D11_BLEND_DESCUnManaged_ToManaged(D3D11_BLEND_DESC* Param_pBlendDescNative)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_BLEND_DESC^ BlendDescManaged = gcnew SDKBase::Estruturas::CA_D3D11_BLEND_DESC();

				//Cria a estrutura Secundaria com um maximo de 8 entradas(0 - 7) validas.
				BlendDescManaged->RenderTarget = gcnew cli::array<SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_BLEND_DESC^>(8);


				//Preenche os dados da estrutura principal
				BlendDescManaged->BlendIndependente = Param_pBlendDescNative->IndependentBlendEnable ? true : false;
				BlendDescManaged->HabilitarAlphaCobertura = Param_pBlendDescNative->AlphaToCoverageEnable ? true : false;

				//Preenche os dados da estrutura secundaria
				//A estrutura secundaria contém 8 Entradas Maximas(0 - 7).

				//Faz um for para criar e definir a estrutura no array.
				for (int i = 0; i < 8; i++)
				{
					//Cria a estrutura no id especificado.
					BlendDescManaged->RenderTarget[i] = gcnew SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_BLEND_DESC();


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
			D3D11_BLEND_DESC1* ConverterD3D11_BLEND_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_BLEND_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_BLEND_DESC1^ ConverterD3D11_BLEND_DESC1UnManaged_ToManaged(D3D11_BLEND_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_BLEND_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_BLEND_DESC1();

				//Cria a estrutura Secundaria com um maximo de 8 entradas(0 - 7) validas.
				EstruturaRetorno->RenderTarget = gcnew cli::array<SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_BLEND_DESC1^>(8);


				//Preenche os dados da estrutura principal
				EstruturaRetorno->BlendIndependente = Param_Estrutura->IndependentBlendEnable ? true : false;
				EstruturaRetorno->HabilitarAlphaCobertura = Param_Estrutura->AlphaToCoverageEnable ? true : false;

				//Preenche os dados da estrutura secundaria
				//A estrutura secundaria contém 8 Entradas Maximas(0 - 7).

				//Faz um for para criar e definir a estrutura no array.
				for (int i = 0; i < 8; i++)
				{
					//Cria a estrutura no id especificado.
					EstruturaRetorno->RenderTarget[i] = gcnew SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_BLEND_DESC1();


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
			D3D11_CLASS_INSTANCE_DESC* ConverterD3D11_CLASS_INSTANCE_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_CLASS_INSTANCE_DESC^ Param_DescInstanceClasse)
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
			SDKBase::Estruturas::CA_D3D11_CLASS_INSTANCE_DESC^ ConverterD3D11_CLASS_INSTANCE_DESCUnManaged_ToManaged(D3D11_CLASS_INSTANCE_DESC* Param_pNativeDescInstance)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_CLASS_INSTANCE_DESC^ DesInstanciaClasse = gcnew SDKBase::Estruturas::CA_D3D11_CLASS_INSTANCE_DESC();

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
			D3D11_QUERY_DESC* ConverterD3D11_QUERY_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_QUERY_DESC^ Param_DescQuery)
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
			SDKBase::Estruturas::CA_D3D11_QUERY_DESC^ ConverterD3D11_QUERY_DESCUnManaged_ToManaged(D3D11_QUERY_DESC* Param_NativeDescQuery)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_QUERY_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_QUERY_DESC();

				//Preenche os dados da estrutura.
				ManagedDesc->MiscFlags = Param_NativeDescQuery->MiscFlags;
				ManagedDesc->Query = static_cast<SDKBase::Enumeracoes::CA_D3D11_QUERY>(UINT(Param_NativeDescQuery->Query));

				//Retorna a estrutura.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_QUERY_DESC1) para sua correspondencia não gerenciada(D3D11_QUERY_DESC1).
			D3D11_QUERY_DESC1* ConverterD3D11_QUERY_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_QUERY_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_QUERY_DESC1^ ConverterD3D11_QUERY_DESC1UnManaged_ToManaged(D3D11_QUERY_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_QUERY_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_QUERY_DESC1();

				//Preenche os dados da estrutura.
				EstruturaRetorno->MiscFlags = Param_Estrutura->MiscFlags;
				EstruturaRetorno->Query = static_cast<SDKBase::Enumeracoes::CA_D3D11_QUERY>(UINT(Param_Estrutura->Query));
				EstruturaRetorno->ContextType = static_cast<CA_D3D11_CONTEXT_TYPE>(Param_Estrutura->ContextType);

				//Retorna a estrutura.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_DEPTH_STENCIL_DESC) para sua correspondencia não gerenciada(D3D11_DEPTH_STENCIL_DESC).
			D3D11_DEPTH_STENCIL_DESC* ConverterD3D11_DEPTH_STENCIL_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^ Param_DescStencil)
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
			SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^ ConverterD3D11_DEPTH_STENCIL_DESCUnManaged_ToManaged(D3D11_DEPTH_STENCIL_DESC* Param_NativeDescStencil)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_DESC();

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
				ManagedDesc->FrontFace = gcnew SDKBase::Estruturas::CA_D3D11_DEPTH_STENCILOP_DESC();
				ManagedDesc->BackFace = gcnew SDKBase::Estruturas::CA_D3D11_DEPTH_STENCILOP_DESC();

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
			D3D11_DEPTH_STENCIL_VIEW_DESC* ConverterD3D11_DEPTH_STENCIL_VIEW_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ Param_DescStencilView)
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
			SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ ConverterD3D11_DEPTH_STENCIL_VIEW_DESCUnManaged_ToManaged(D3D11_DEPTH_STENCIL_VIEW_DESC* Param_NativeDescStencilView)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescStencilView->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_DSV_DIMENSION>(Param_NativeDescStencilView->ViewDimension);
				ManagedDesc->Flags = static_cast<SDKBase::Enumeracoes::CA_D3D11_DSV_FLAG>(Param_NativeDescStencilView->Flags);

				//Inicializa as estruturas secundarias
				ManagedDesc->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_DSV();
				ManagedDesc->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_DSV();
				ManagedDesc->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_DSV();
				ManagedDesc->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_DSV();
				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				ManagedDesc->Textura2DMSArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2DMS_ARRAY_DSV();

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
			D3D11_UNORDERED_ACCESS_VIEW_DESC* ConverterD3D11_UNORDERED_ACCESS_VIEW_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ Param_DescUnordered)
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
			SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ ConverterD3D11_UNORDERED_ACCESS_VIEW_DESCUnManaged_ToManaged(D3D11_UNORDERED_ACCESS_VIEW_DESC* Param_NativeDescUnordered)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescUnordered->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_UAV_DIMENSION>(Param_NativeDescUnordered->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_UAV();
				ManagedDesc->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_UAV();
				ManagedDesc->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_UAV();
				ManagedDesc->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_UAV();
				ManagedDesc->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_UAV();
				ManagedDesc->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_UAV();

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
			D3D11_UNORDERED_ACCESS_VIEW_DESC1* ConverterD3D11_UNORDERED_ACCESS_VIEW_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ ConverterD3D11_UNORDERED_ACCESS_VIEW_DESC1UnManaged_ToManaged(D3D11_UNORDERED_ACCESS_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_UAV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_UAV();
				EstruturaRetorno->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_UAV();
				EstruturaRetorno->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_UAV();
				EstruturaRetorno->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_UAV1();
				EstruturaRetorno->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_UAV1();
				EstruturaRetorno->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_UAV();

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
			D3D11_SAMPLER_DESC* ConverterD3D11_SAMPLER_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_SAMPLER_DESC^ Param_DescSampler)
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
			SDKBase::Estruturas::CA_D3D11_SAMPLER_DESC^ ConverterD3D11_SAMPLER_DESCUnManaged_ToManaged(D3D11_SAMPLER_DESC* Param_NativeDescSampler)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_SAMPLER_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_SAMPLER_DESC();

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
			D3D11_SHADER_RESOURCE_VIEW_DESC* ConverterD3D11_SHADER_RESOURCE_VIEW_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ Param_DescShader)
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
			SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ ConverterD3D11_SHADER_RESOURCE_VIEW_DESCUnManaged_ToManaged(D3D11_SHADER_RESOURCE_VIEW_DESC* Param_NativeDescShader)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescShader->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_SRV_DIMENSION>(Param_NativeDescShader->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_SRV();
				ManagedDesc->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_SRV();
				ManagedDesc->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_SRV();
				ManagedDesc->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_SRV();
				ManagedDesc->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_SRV();
				// Texture2DMS -> D3D11_TEX2DMS_SRV - Não há necessidade de criar.
				ManagedDesc->Textura2DMSArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2DMS_ARRAY_SRV();
				ManagedDesc->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_SRV();
				ManagedDesc->TexturaCube = gcnew  SDKBase::Estruturas::CA_D3D11_TEXCUBE_SRV();
				ManagedDesc->TexturaCubeArray = gcnew SDKBase::Estruturas::CA_D3D11_TEXCUBE_ARRAY_SRV();
				ManagedDesc->BufferEx = gcnew SDKBase::Estruturas::CA_D3D11_BUFFEREX_SRV();

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
			D3D11_SHADER_RESOURCE_VIEW_DESC1* ConverterD3D11_SHADER_RESOURCE_VIEW_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ ConverterD3D11_SHADER_RESOURCE_VIEW_DESC1UnManaged_ToManaged(D3D11_SHADER_RESOURCE_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC1();

				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_SRV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_SRV();
				EstruturaRetorno->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_SRV();
				EstruturaRetorno->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_SRV();
				EstruturaRetorno->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_SRV1();
				EstruturaRetorno->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_SRV1();

				// Texture2DMS -> D3D11_TEX2DMS_SRV - Não há necessidade de criar.
				EstruturaRetorno->Textura2DMSArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2DMS_ARRAY_SRV();
				EstruturaRetorno->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_SRV();
				EstruturaRetorno->TexturaCube = gcnew  SDKBase::Estruturas::CA_D3D11_TEXCUBE_SRV();
				EstruturaRetorno->TexturaCubeArray = gcnew SDKBase::Estruturas::CA_D3D11_TEXCUBE_ARRAY_SRV();
				EstruturaRetorno->BufferEx = gcnew SDKBase::Estruturas::CA_D3D11_BUFFEREX_SRV();

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
			D3D11_RASTERIZER_DESC* ConverterD3D11_RASTERIZER_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC^ Param_DescRasterizer)
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
			SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC^ ConverterD3D11_RASTERIZER_DESCUnManaged_ToManaged(D3D11_RASTERIZER_DESC* Param_NativeDescRasterizer)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC();

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
			D3D11_RASTERIZER_DESC1* ConverterD3D11_RASTERIZER_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC1^ ConverterD3D11_RASTERIZER_DESC1UnManaged_ToManaged(D3D11_RASTERIZER_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC1();

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
			D3D11_RASTERIZER_DESC2* ConverterD3D11_RASTERIZER_DESC2Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC2^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC2^ ConverterD3D11_RASTERIZER_DESC2UnManaged_ToManaged(D3D11_RASTERIZER_DESC2* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC2^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_RASTERIZER_DESC2();

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
			D3D11_RENDER_TARGET_VIEW_DESC* ConverterD3D11_RENDER_TARGET_VIEW_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender)
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
			SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ ConverterD3D11_RENDER_TARGET_VIEW_DESCUnManaged_ToManaged(D3D11_RENDER_TARGET_VIEW_DESC* Param_NativeDescRender)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC();


				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				ManagedDesc->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_NativeDescRender->Format);
				ManagedDesc->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_RTV_DIMENSION>(Param_NativeDescRender->ViewDimension);

				//Inicializa as estruturas secundarias
				ManagedDesc->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_RTV();
				ManagedDesc->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_RTV();
				ManagedDesc->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_RTV();
				ManagedDesc->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_RTV();
				ManagedDesc->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_RTV();
				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				ManagedDesc->Textura2DMSArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2DMS_ARRAY_RTV();
				ManagedDesc->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_RTV();

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
			D3D11_RENDER_TARGET_VIEW_DESC1* ConverterD3D11_RENDER_TARGET_VIEW_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC1^ ConverterD3D11_RENDER_TARGET_VIEW_DESC1UnManaged_ToManaged(D3D11_RENDER_TARGET_VIEW_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC1();


				//Define os dados da estrutura primaria.

				//Preenche os dados da estrutura gerenciada.
				EstruturaRetorno->Formato = static_cast<SDKBase::Enumeracoes::CA_DXGI_FORMAT>(Param_Estrutura->Format);
				EstruturaRetorno->ViewDimensao = static_cast<SDKBase::Enumeracoes::CA_D3D11_RTV_DIMENSION>(Param_Estrutura->ViewDimension);

				//Inicializa as estruturas secundarias
				EstruturaRetorno->Buffer = gcnew SDKBase::Estruturas::CA_D3D11_BUFFER_RTV();
				EstruturaRetorno->Textura1D = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_RTV();
				EstruturaRetorno->Textura1DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX1D_ARRAY_RTV();
				EstruturaRetorno->Textura2D = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_RTV1();
				EstruturaRetorno->Textura2DArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2D_ARRAY_RTV1();

				//EstruturaRetorno->Textura2DMS -> Essa estrutura não precisa ser criada porque não contém membros e não define nada.
				EstruturaRetorno->Textura2DMSArray = gcnew SDKBase::Estruturas::CA_D3D11_TEX2DMS_ARRAY_RTV();
				EstruturaRetorno->Textura3D = gcnew SDKBase::Estruturas::CA_D3D11_TEX3D_RTV();

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
			D3D11_TEXTURE1D_DESC* ConverterD3D11_TEXTURE1D_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TEXTURE1D_DESC^ Param_DescTex1D)
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
			SDKBase::Estruturas::CA_D3D11_TEXTURE1D_DESC^ ConverterD3D11_TEXTURE1D_DESCUnManaged_ToManaged(D3D11_TEXTURE1D_DESC* Param_NativeDescTex1D)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TEXTURE1D_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_TEXTURE1D_DESC();

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
			D3D11_TEXTURE2D_DESC* ConverterD3D11_TEXTURE2D_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC^ Param_DescTex2D)
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
			SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC^ ConverterD3D11_TEXTURE2D_DESCUnManaged_ToManaged(D3D11_TEXTURE2D_DESC* Param_NativeDescTex2D)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC();

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
				ManagedDesc->SampleDesc = gcnew SDKBase::Estruturas::CA_DXGI_SAMPLE_DESC();

				ManagedDesc->SampleDesc->Count = Param_NativeDescTex2D->SampleDesc.Count;
				ManagedDesc->SampleDesc->Quality = Param_NativeDescTex2D->SampleDesc.Quality;

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE2D_DESC1) para sua correspondencia não gerenciada(D3D11_TEXTURE2D_DESC1).
			D3D11_TEXTURE2D_DESC1* ConverterD3D11_TEXTURE2D_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC1^ ConverterD3D11_TEXTURE2D_DESC1UnManaged_ToManaged(D3D11_TEXTURE2D_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_TEXTURE2D_DESC1();

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
				EstruturaRetorno->SampleDesc = gcnew SDKBase::Estruturas::CA_DXGI_SAMPLE_DESC();
				EstruturaRetorno->SampleDesc->Count = Param_Estrutura->SampleDesc.Count;
				EstruturaRetorno->SampleDesc->Quality = Param_Estrutura->SampleDesc.Quality;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TEXTURE3D_DESC) para sua correspondencia não gerenciada(D3D11_TEXTURE3D_DESC).
			D3D11_TEXTURE3D_DESC* ConverterD3D11_TEXTURE3D_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC^ Param_DescTex3D)
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
			SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC^ ConverterD3D11_TEXTURE3D_DESCUnManaged_ToManaged(D3D11_TEXTURE3D_DESC* Param_NativeDescTex3D)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC();

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
			D3D11_TEXTURE3D_DESC1* ConverterD3D11_TEXTURE3D_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC1^ ConverterD3D11_TEXTURE3D_DESC1UnManaged_ToManaged(D3D11_TEXTURE3D_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_TEXTURE3D_DESC1();

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
			D3D11_COUNTER_DESC* ConverterD3D11_COUNTER_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_DESC_CONTADOR^ Param_Desc)
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
			SDKBase::Estruturas::CA_D3D11_DESC_CONTADOR^ ConverterD3D11_COUNTER_DESCUnManaged_ToManaged(D3D11_COUNTER_DESC* Param_NativeDesc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_DESC_CONTADOR^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_DESC_CONTADOR();

				//Preenche os dados da estrutura.
				ManagedDesc->ContadorType = static_cast<SDKBase::Enumeracoes::CA_D3D11_CONTADOR>(Param_NativeDesc->Counter);
				ManagedDesc->MiscFlags = Param_NativeDesc->MiscFlags;

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_INFO_CONTADOR) para sua correspondencia não gerenciada(D3D11_COUNTER_INFO).
			D3D11_COUNTER_INFO* ConverterD3D11_COUNTER_INFOManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_INFO_CONTADOR^ Param_Desc)
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
			SDKBase::Estruturas::CA_D3D11_INFO_CONTADOR^ ConverterD3D11_COUNTER_INFOUnManaged_ToManaged(D3D11_COUNTER_INFO* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_INFO_CONTADOR^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_INFO_CONTADOR();

				//Preenche os dados da estrutura.
				ManagedDesc->IDMaiorContadorDependente = static_cast<SDKBase::Enumeracoes::CA_D3D11_CONTADOR>(Param_Desc->LastDeviceDependentCounter);
				ManagedDesc->NumeroUnidadesParalelasDetectaveis = Param_Desc->NumDetectableParallelUnits;
				ManagedDesc->NumeroContadoresSimultaneos = Param_Desc->NumSimultaneousCounters;


				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_FEATURE_DATA_THREADING) para sua correspondencia não gerenciada(D3D11_FEATURE_DATA_THREADING).
			D3D11_FEATURE_DATA_THREADING* ConverterD3D11_FEATURE_DATA_THREADINGManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_FEATURE_DATA_THREADING^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_FEATURE_DATA_THREADING^ ConverterD3D11_FEATURE_DATA_THREADINGUnManaged_ToManaged(D3D11_FEATURE_DATA_THREADING* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_FEATURE_DATA_THREADING^ ManagedDesc = gcnew SDKBase::Estruturas::CA_D3D11_FEATURE_DATA_THREADING();

				//Preenche os dados da estrutura.
				ManagedDesc->DriverCommandLists = Param_Estrutura->DriverCommandLists;
				ManagedDesc->DriverConcurrentCreates = Param_Estrutura->DriverConcurrentCreates;
				ManagedDesc->TamanhoEstrutura = sizeof(D3D11_FEATURE_DATA_THREADING);

				//Retorna a variavel.
				return ManagedDesc;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_INPUT_ELEMENT_DESC) para sua correspondencia não gerenciada(D3D11_INPUT_ELEMENT_DESC).
			//Chame um (delete) no membro(SemanticName) para liberar a memoria para ele e depois libera a memoria da estrutura completa.
			D3D11_INPUT_ELEMENT_DESC* ConverterD3D11_INPUT_ELEMENT_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^ Param_Desc)
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
			SDKBase::Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^ ConverterD3D11_INPUT_ELEMENT_DESCUnManaged_ToManaged(D3D11_INPUT_ELEMENT_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^ pEstrutura = gcnew SDKBase::Estruturas::CA_D3D11_INPUT_ELEMENT_DESC();

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
			D3D11_SO_DECLARATION_ENTRY* ConverterD3D11_SO_DECLARATION_ENTRYManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^ Param_Desc)
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
			SDKBase::Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^ ConverterD3D11_SO_DECLARATION_ENTRYUnManaged_ToManaged(D3D11_SO_DECLARATION_ENTRY* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^ pEstrutura = gcnew SDKBase::Estruturas::CA_D3D11_SO_DECLARATION_ENTRY();

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
			D3D11_VIEWPORT* ConverterD3D11_VIEWPORTManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_VIEWPORT^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_VIEWPORT^ ConverterD3D11_VIEWPORTUnManaged_ToManaged(D3D11_VIEWPORT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_VIEWPORT^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_VIEWPORT();

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
			D3D11_BOX* ConverterD3D11_BOXManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_BOX^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_BOX^ ConverterD3D11_BOXUnManaged_ToManaged(D3D11_BOX* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_BOX^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_BOX();

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
				((ICarenBuffer^)Param_Estrutura->Param_BufferDados)->ObterPonteiroInterno(PointeiroBuffer);

				//Define o ponteiro na estrutura
				EstruturaRetorno->pData = (PBYTE)PointeiroBuffer.ToPointer();

				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(D3D11_MAPPED_SUBRESOURCE) para sua correspondencia gerenciada(CA_D3D11_MAPPED_SUBRESOURCE).
			SDKBase::Estruturas::CA_D3D11_MAPPED_SUBRESOURCE^ ConverterD3D11_MAPPED_SUBRESOURCEUnManaged_ToManaged(D3D11_MAPPED_SUBRESOURCE* Param_Estrutura, ICarenBuffer^% Param_BuffInterface)
			{
				//Variavel a ser retornada.
				CA_D3D11_MAPPED_SUBRESOURCE^ EstruturaRetorno = gcnew CA_D3D11_MAPPED_SUBRESOURCE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->LinhaPasso = Param_Estrutura->RowPitch;
				EstruturaRetorno->ProfundidadePasso = Param_Estrutura->DepthPitch;

				//Define o ponteiro de buffer.
				Param_BuffInterface->CriarBuffer(IntPtr(Param_Estrutura->pData), false, 0, 0); //Associa o ponteiro da estrutura ao da CarenBuffer.

				//Define a interface de buffer criada na estrutura.
				EstruturaRetorno->Param_BufferDados = Param_BuffInterface;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILED_RESOURCE_COORDINATE) para sua correspondencia não gerenciada(D3D11_TILED_RESOURCE_COORDINATE).
			D3D11_TILED_RESOURCE_COORDINATE* ConverterD3D11_TILED_RESOURCE_COORDINATEManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_TILED_RESOURCE_COORDINATE^ ConverterD3D11_TILED_RESOURCE_COORDINATEUnManaged_ToManaged(D3D11_TILED_RESOURCE_COORDINATE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TILED_RESOURCE_COORDINATE^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_TILED_RESOURCE_COORDINATE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->X = Param_Estrutura->X;
				EstruturaRetorno->Y = Param_Estrutura->Y;
				EstruturaRetorno->Z = Param_Estrutura->Z;
				EstruturaRetorno->Subresource = Param_Estrutura->Subresource;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILE_REGION_SIZE) para sua correspondencia não gerenciada(D3D11_TILE_REGION_SIZE).
			D3D11_TILE_REGION_SIZE* ConverterD3D11_TILE_REGION_SIZEManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TILE_REGION_SIZE^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_TILE_REGION_SIZE^ ConverterD3D11_TILE_REGION_SIZEUnManaged_ToManaged(D3D11_TILE_REGION_SIZE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TILE_REGION_SIZE^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_TILE_REGION_SIZE();

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
			D3D11_PACKED_MIP_DESC* ConverterD3D11_PACKED_MIP_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_PACKED_MIP_DESC^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_PACKED_MIP_DESC^ ConverterD3D11_PACKED_MIP_DESCUnManaged_ToManaged(D3D11_PACKED_MIP_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_PACKED_MIP_DESC^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_PACKED_MIP_DESC();

				//Preenche os dados da estrutura.
				EstruturaRetorno->NumPackedMips = Param_Estrutura->NumPackedMips;
				EstruturaRetorno->NumStandardMips = Param_Estrutura->NumStandardMips;
				EstruturaRetorno->NumTilesForPackedMips = Param_Estrutura->NumTilesForPackedMips;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_TILE_SHAPE) para sua correspondencia não gerenciada(D3D11_TILE_SHAPE).
			D3D11_TILE_SHAPE* ConverterD3D11_TILE_SHAPEManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_TILE_SHAPE^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_TILE_SHAPE^ ConverterD3D11_TILE_SHAPEUnManaged_ToManaged(D3D11_TILE_SHAPE* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_TILE_SHAPE^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_TILE_SHAPE();

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTexels = Param_Estrutura->DepthInTexels;
				EstruturaRetorno->HeightInTexels = Param_Estrutura->HeightInTexels;
				EstruturaRetorno->WidthInTexels = Param_Estrutura->WidthInTexels;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_D3D11_SUBRESOURCE_TILING) para sua correspondencia não gerenciada(D3D11_SUBRESOURCE_TILING).
			D3D11_SUBRESOURCE_TILING* ConverterD3D11_SUBRESOURCE_TILINGManaged_ToUnManaged(SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_TILING^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_TILING^ ConverterD3D11_SUBRESOURCE_TILINGUnManaged_ToManaged(D3D11_SUBRESOURCE_TILING* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_TILING^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_D3D11_SUBRESOURCE_TILING();

				//Preenche os dados da estrutura.
				EstruturaRetorno->DepthInTiles = Param_Estrutura->DepthInTiles;
				EstruturaRetorno->HeightInTiles = Param_Estrutura->HeightInTiles;
				EstruturaRetorno->StartTileIndexInOverallResource = Param_Estrutura->StartTileIndexInOverallResource;
				EstruturaRetorno->WidthInTiles = Param_Estrutura->WidthInTiles;

				//Retorna a variavel.
				return EstruturaRetorno;
			}





			
			///DXGI ESTRUTURAS
			

			//Converte uma estrutura gerenciada(CA_DXGI_SWAP_CHAIN_DESC) para sua correspondencia não gerenciada(DXGI_SWAP_CHAIN_DESC).
			DXGI_SWAP_CHAIN_DESC* ConverterDXGI_SWAP_CHAIN_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc)
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
			SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC^ ConverterDXGI_SWAP_CHAIN_DESCUnManaged_ToManaged(DXGI_SWAP_CHAIN_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC^ pEstrutura = gcnew SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC();

				//Preenche os dados da estrutura.
				pEstrutura->BufferCount = Param_Desc->BufferCount;
				pEstrutura->BufferUsage = static_cast<SDKBase::Enumeracoes::CA_DXGI_USAGE>(Param_Desc->BufferUsage);
				pEstrutura->Flags = static_cast<SDKBase::Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG>(Param_Desc->Flags);
				pEstrutura->OutputWindow = ConverterHWNDToIntPtr(Param_Desc->OutputWindow);
				pEstrutura->SwapEffect = static_cast<SDKBase::Enumeracoes::CA_DXGI_SWAP_EFFECT>(Param_Desc->SwapEffect);
				pEstrutura->Windowed = Param_Desc->Windowed ? true : false;

				//Cria as estruturas secundarias.
				pEstrutura->SampleDesc = gcnew SDKBase::Estruturas::CA_DXGI_SAMPLE_DESC();
				pEstrutura->BufferDesc = gcnew SDKBase::Estruturas::CA_DXGI_MODE_DESC();
				pEstrutura->BufferDesc->RefreshRate = gcnew SDKBase::Estruturas::CA_DXGI_RATIONAL();

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
			DXGI_SWAP_CHAIN_DESC1* ConverterDXGI_SWAP_CHAIN_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC1^ Param_Desc)
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
			SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC1^ ConverterDXGI_SWAP_CHAIN_DESC1UnManaged_ToManaged(DXGI_SWAP_CHAIN_DESC1* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC1^ pEstrutura = gcnew SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_DESC1();

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
				SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ pEstrutura = gcnew SDKBase::Estruturas::CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC();

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
			DXGI_FRAME_STATISTICS* ConverterDXGI_FRAME_STATISTICSManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_FRAME_STATISTICS^ Param_Desc)
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
			SDKBase::Estruturas::CA_DXGI_FRAME_STATISTICS^ ConverterDXGI_FRAME_STATISTICSUnManaged_ToManaged(DXGI_FRAME_STATISTICS* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_FRAME_STATISTICS^ pEstrutura = gcnew SDKBase::Estruturas::CA_DXGI_FRAME_STATISTICS();

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
			DXGI_OUTDUPL_DESC* ConverterDXGI_OUTDUPL_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_OUTDUPL_DESC^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTDUPL_DESC^ ConverterDXGI_OUTDUPL_DESCUnManaged_ToManaged(DXGI_OUTDUPL_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTDUPL_DESC^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTDUPL_DESC();

				//Preenche os dados da estrutura.
				EstruturaRetorno->Rotation = static_cast<CA_DXGI_MODE_ROTATION>(Param_Estrutura->Rotation);
				EstruturaRetorno->DesktopImageInSystemMemory = static_cast<bool>(Param_Estrutura->DesktopImageInSystemMemory);

				//Cria a estrutura e preenche os seus dados.
				EstruturaRetorno->ModeDesc = ConverterDXGI_MODE_DESCUnManaged_ToManaged(&Param_Estrutura->ModeDesc);
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTDUPL_MOVE_RECT) para sua correspondencia não gerenciada(DXGI_OUTDUPL_MOVE_RECT).
			DXGI_OUTDUPL_MOVE_RECT* ConverterDXGI_OUTDUPL_MOVE_RECTManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_OUTDUPL_MOVE_RECT^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTDUPL_MOVE_RECT^ ConverterDXGI_OUTDUPL_MOVE_RECTUnManaged_ToManaged(DXGI_OUTDUPL_MOVE_RECT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTDUPL_MOVE_RECT^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTDUPL_MOVE_RECT();

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
			DXGI_OUTDUPL_POINTER_SHAPE_INFO* ConverterDXGI_OUTDUPL_POINTER_SHAPE_INFOManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ ConverterDXGI_OUTDUPL_POINTER_SHAPE_INFOUnManaged_ToManaged(DXGI_OUTDUPL_POINTER_SHAPE_INFO* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO();



				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MODE_DESC) para sua correspondencia não gerenciada(DXGI_MODE_DESC).
			DXGI_MODE_DESC* ConverterDXGI_MODE_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_MODE_DESC^ Param_Desc)
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
			SDKBase::Estruturas::CA_DXGI_MODE_DESC^ ConverterDXGI_MODE_DESCUnManaged_ToManaged(DXGI_MODE_DESC* Param_Desc)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_MODE_DESC^ pEstrutura = gcnew SDKBase::Estruturas::CA_DXGI_MODE_DESC();

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
			DXGI_MODE_DESC1* ConverterDXGI_MODE_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_MODE_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_MODE_DESC1^ ConverterDXGI_MODE_DESC1UnManaged_ToManaged(DXGI_MODE_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_MODE_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_MODE_DESC1();

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
			DXGI_RGB* ConverterDXGI_RGBManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_RGB^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_RGB^ ConverterDXGI_RGBUnManaged_ToManaged(DXGI_RGB* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_RGB^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_RGB();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Vermelho = Param_Estrutura->Red;
				EstruturaRetorno->Verde = Param_Estrutura->Green;
				EstruturaRetorno->Azul = Param_Estrutura->Blue;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_RGBA) para sua correspondencia não gerenciada(DXGI_RGBA).
			DXGI_RGBA* ConverterDXGI_RGBAManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_RGBA^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_RGBA^ ConverterDXGI_RGBAUnManaged_ToManaged(DXGI_RGBA* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_RGBA^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_RGBA();

				//Preenche os dados da estrutura principal.
				EstruturaRetorno->Vermelho = Param_Estrutura->r;
				EstruturaRetorno->Verde = Param_Estrutura->g;
				EstruturaRetorno->Azul = Param_Estrutura->b;
				EstruturaRetorno->Alfa = Param_Estrutura->a;

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_GAMMA_CONTROL) para sua correspondencia não gerenciada(DXGI_GAMMA_CONTROL).
			DXGI_GAMMA_CONTROL* ConverterDXGI_GAMMA_CONTROLManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL^ ConverterDXGI_GAMMA_CONTROLUnManaged_ToManaged(DXGI_GAMMA_CONTROL* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL();

				//Esse valor é fixo segundo a MSDN.
				int LengCountGamma = 1025;

				//Inicializa o array
				EstruturaRetorno->GammaCurve = gcnew cli::array<SDKBase::Estruturas::CA_DXGI_RGB^>(LengCountGamma);

				//Copia os dados da estrutura principal.
				for (int i = 0; i < LengCountGamma; i++)
				{
					//Define os dados na estrutura.
					EstruturaRetorno->GammaCurve[i]->Vermelho = Param_Estrutura->GammaCurve[i].Red;
					EstruturaRetorno->GammaCurve[i]->Verde = Param_Estrutura->GammaCurve[i].Green;
					EstruturaRetorno->GammaCurve[i]->Azul = Param_Estrutura->GammaCurve[i].Blue;
				}

				//Cria as estruturas secundarias.
				EstruturaRetorno->Offset = gcnew SDKBase::Estruturas::CA_DXGI_RGB();
				EstruturaRetorno->Scale = gcnew SDKBase::Estruturas::CA_DXGI_RGB();

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
			DXGI_OUTPUT_DESC* ConverterDXGI_OUTPUT_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC^ ConverterDXGI_OUTPUT_DESCUnManaged_ToManaged(DXGI_OUTPUT_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC();

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
					EstruturaRetorno->Monitor->DefinirObjeto(Param_Estrutura->Monitor);
				}

				//Cria e preenche a estrutura secundaria.
				EstruturaRetorno->DesktopCoordinates = gcnew SDKBase::Estruturas::CA_RECT();

				//Define as coordenadas
				EstruturaRetorno->DesktopCoordinates->Topo = Param_Estrutura->DesktopCoordinates.top;
				EstruturaRetorno->DesktopCoordinates->Fundo = Param_Estrutura->DesktopCoordinates.bottom;
				EstruturaRetorno->DesktopCoordinates->Direita = Param_Estrutura->DesktopCoordinates.right;
				EstruturaRetorno->DesktopCoordinates->Esquerda = Param_Estrutura->DesktopCoordinates.left;


				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_OUTPUT_DESC1) para sua correspondencia não gerenciada(DXGI_OUTPUT_DESC1).
			DXGI_OUTPUT_DESC1* ConverterDXGI_OUTPUT_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC1^ ConverterDXGI_OUTPUT_DESC1UnManaged_ToManaged(DXGI_OUTPUT_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_OUTPUT_DESC1();

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
					EstruturaRetorno->Monitor->DefinirObjeto(Param_Estrutura->Monitor);
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
				EstruturaRetorno->DesktopCoordinates = gcnew SDKBase::Estruturas::CA_RECT();
				
				//Define as coordenadas
				EstruturaRetorno->DesktopCoordinates->Topo = Param_Estrutura->DesktopCoordinates.top;
				EstruturaRetorno->DesktopCoordinates->Fundo = Param_Estrutura->DesktopCoordinates.bottom;
				EstruturaRetorno->DesktopCoordinates->Direita = Param_Estrutura->DesktopCoordinates.right;
				EstruturaRetorno->DesktopCoordinates->Esquerda = Param_Estrutura->DesktopCoordinates.left;


				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_GAMMA_CONTROL_CAPABILITIES) para sua correspondencia não gerenciada(DXGI_GAMMA_CONTROL_CAPABILITIES).
			DXGI_GAMMA_CONTROL_CAPABILITIES* ConverterDXGI_GAMMA_CONTROL_CAPABILITIESManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ ConverterDXGI_GAMMA_CONTROL_CAPABILITIESUnManaged_ToManaged(DXGI_GAMMA_CONTROL_CAPABILITIES* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL_CAPABILITIES^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_GAMMA_CONTROL_CAPABILITIES();

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
			SDKBase::Estruturas::CA_DXGI_PRESENT_PARAMETERS^ ConverterDXGI_PRESENT_PARAMETERSUnManaged_ToManaged(DXGI_PRESENT_PARAMETERS* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_PRESENT_PARAMETERS^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_PRESENT_PARAMETERS();

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
			DXGI_ADAPTER_DESC* ConverterDXGI_ADAPTER_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC^ ConverterDXGI_ADAPTER_DESCUnManaged_ToManaged(DXGI_ADAPTER_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC();

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
			DXGI_ADAPTER_DESC1* ConverterDXGI_ADAPTER_DESC1Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC1^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC1^ ConverterDXGI_ADAPTER_DESC1UnManaged_ToManaged(DXGI_ADAPTER_DESC1* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC1^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC1();

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
			DXGI_ADAPTER_DESC2* ConverterDXGI_ADAPTER_DESC2Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC2^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC2^ ConverterDXGI_ADAPTER_DESC2UnManaged_ToManaged(DXGI_ADAPTER_DESC2* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC2^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC2();

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
			DXGI_ADAPTER_DESC3* ConverterDXGI_ADAPTER_DESC3Managed_ToUnManaged(SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC3^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC3^ ConverterDXGI_ADAPTER_DESC3UnManaged_ToManaged(DXGI_ADAPTER_DESC3* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC3^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_ADAPTER_DESC3();

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
			DXGI_SURFACE_DESC* ConverterDXGI_SURFACE_DESCManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_SURFACE_DESC^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_SURFACE_DESC^ ConverterDXGI_SURFACE_DESCUnManaged_ToManaged(DXGI_SURFACE_DESC* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_SURFACE_DESC^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_SURFACE_DESC();

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
			DXGI_MAPPED_RECT* ConverterDXGI_MAPPED_RECTManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_MAPPED_RECT^ Param_Estrutura)
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
					Param_Estrutura->Buffer->ObterPonteiroInterno(PointeiroBuffer);

					//Define o ponteiro.
					EstruturaRetorno->pBits = (BYTE*)PointeiroBuffer.ToPointer();
				}
				
				//Retorna
				return EstruturaRetorno;
			}

			//Converte uma estrutura não gerenciada(DXGI_MAPPED_RECT) para sua correspondencia gerenciada(CA_DXGI_MAPPED_RECT).
			SDKBase::Estruturas::CA_DXGI_MAPPED_RECT^ ConverterDXGI_MAPPED_RECTUnManaged_ToManaged(DXGI_MAPPED_RECT* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_MAPPED_RECT^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_MAPPED_RECT();

				//Define os dados na estrutura
				EstruturaRetorno->Largura = Param_Estrutura->Pitch;

				//Verifica se o buffer é valido e define na estrutura.
				if (ObjetoValido(Param_Estrutura->pBits))
				{
					//Cria a classe que vai conter o ponteiro para o buffer de memória.
					EstruturaRetorno->Buffer = gcnew CarenBuffer();

					//Cria e associa o ponteiro da estrutura a interface.
					EstruturaRetorno->Buffer->CriarBuffer(IntPtr(Param_Estrutura->pBits), false, (unsigned int)EstruturaRetorno->Largura, (unsigned int)EstruturaRetorno->Largura);

					//Define a posição para zero
					EstruturaRetorno->Buffer->DefinirPosicao(0);
				}
				
				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_QUERY_VIDEO_MEMORY_INFO) para sua correspondencia não gerenciada(DXGI_QUERY_VIDEO_MEMORY_INFO).
			DXGI_QUERY_VIDEO_MEMORY_INFO* ConverterDXGI_QUERY_VIDEO_MEMORY_INFOManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ ConverterDXGI_QUERY_VIDEO_MEMORY_INFOUnManaged_ToManaged(DXGI_QUERY_VIDEO_MEMORY_INFO* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_QUERY_VIDEO_MEMORY_INFO^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_QUERY_VIDEO_MEMORY_INFO();

				//Define os dados na estrutura
				EstruturaRetorno->AvailableForReservation = static_cast<UInt64>(Param_Estrutura->AvailableForReservation);
				EstruturaRetorno->Budget = static_cast<UInt64>(Param_Estrutura->Budget);
				EstruturaRetorno->CurrentReservation = static_cast<UInt64>(Param_Estrutura->CurrentReservation);
				EstruturaRetorno->CurrentUsage = static_cast<UInt64>(Param_Estrutura->CurrentUsage);

				//Retorna a variavel.
				return EstruturaRetorno;
			}


			//Converte uma estrutura gerenciada(CA_DXGI_MATRIX_3X2_F) para sua correspondencia não gerenciada(DXGI_MATRIX_3X2_F).
			DXGI_MATRIX_3X2_F* ConverterDXGI_MATRIX_3X2_FManaged_ToUnManaged(SDKBase::Estruturas::CA_DXGI_MATRIX_3X2_F^ Param_Estrutura)
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
			SDKBase::Estruturas::CA_DXGI_MATRIX_3X2_F^ ConverterDXGI_MATRIX_3X2_FUnManaged_ToManaged(DXGI_MATRIX_3X2_F* Param_Estrutura)
			{
				//Variavel a ser retornada.
				SDKBase::Estruturas::CA_DXGI_MATRIX_3X2_F^ EstruturaRetorno = gcnew SDKBase::Estruturas::CA_DXGI_MATRIX_3X2_F();

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


		};
	}
}