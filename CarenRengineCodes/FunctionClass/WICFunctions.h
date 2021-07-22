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
#include "../SDK_WIC.h"
#include "../SDK_Windows.h"
#include "../SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o SDK do WIC.
using namespace CarenRengine::WIC;

/// <summary>
/// Classe responsável por conter funções nativas auxiliares da biblioteca da Api do WIC(Windows Imaging Component).
/// </summary>
public ref class WICFunctions
{
	//Construtor & Destruidor
public:
	WICFunctions() {};
	~WICFunctions() {};

	//Métodos da classe.
public:

	/// <summary>
	/// Obtém um ICarenWICBitmapSource no formato de pixel desejado a partir de um determinado ICarenWICBitmapSource.
	/// Se o bitmap (Param_BmpSource) já estiver no formato desejado, então o (Param_BmpSource) será copiado para o ponteiro bitmap de destino e uma referência é adicionada. 
	/// </summary>
	/// <param name="Param_PixelGuidDest">O formato pixel para converter.</param>
	/// <param name="Param_BmpSource">O bitmap fonte.</param>
	/// <param name="Param_Out_BmpDst">Retorna uma interface (ICarenWICBitmapSource) para o bitmap de destino. O usuário é responsável por inicializar a interface antes de chamar este metódo.</param>
	CarenResult _WICConvertBitmapSource(
		String^ Param_PixelGuidDest,
		ICarenWICBitmapSource^ Param_BmpSource,
		ICarenWICBitmapSource^ Param_Out_BmpDst);

	/// <summary>
	/// ‎Retorna uma ICarenWICBitmapSource‎‎ que é apoiada pelos pixels de uma Handle de seção GDI (Windows Graphics Device Interface, interface de dispositivo gráficos do Windows).‎
	/// </summary>
	/// <param name="Param_Width">A largura dos pixels do bitmap.</param>
	/// <param name="Param_Height">A altura dos pixels do bitmap.</param>
	/// <param name="Param_PixelFormat">O formato pixel do bitmap.</param>
	/// <param name="Param_Section">A Handle da seção. Esta é uma alça de objeto de mapeamento de arquivos devolvida pela função _CreateFileMappingW na Classe de funções do Windows.</param>
	/// <param name="Param_Stride">A contagem de byte de cada scanline.</param>
	/// <param name="Param_Offset">O deslocamento para a seção.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface (ICarenWICBitmap) para o bitmap. O usuário é responsável por inicializar a interface antes de chamar este metódo.</param>
	CarenResult _WICCreateBitmapFromSection(
		UInt32 Param_Width,
		UInt32 Param_Height,
		String^ Param_PixelFormat,
		IntPtr Param_Section,
		UInt32 Param_Stride,
		UInt32 Param_Offset,
		ICarenWICBitmap^ Param_Out_Bitmap);

	/// <summary>
	/// ‎Retorna uma ICarenWICBitmapSource‎‎ que é apoiada pelos pixels de uma Handle de seção GDI (Windows Graphics Device Interface, interface de dispositivo gráficos do Windows).‎
	/// </summary>
	/// <param name="Param_Width">A largura dos pixels do bitmap.</param>
	/// <param name="Param_Height">A altura dos pixels do bitmap.</param>
	/// <param name="Param_PixelFormat">O formato pixel do bitmap.</param>
	/// <param name="Param_Section">A Handle da seção. Esta é uma alça de objeto de mapeamento de arquivos devolvida pela função _CreateFileMappingW na Classe de funções do Windows.</param>
	/// <param name="Param_Stride">A contagem de byte de cada scanline.</param>
	/// <param name="Param_Offset">O deslocamento para a seção.</param>
	/// <param name="Param_AccessLevel">‎O nível de acesso desejado.‎</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface (ICarenWICBitmap) para o bitmap. O usuário é responsável por inicializar a interface antes de chamar este metódo.</param>
	CarenResult _WICCreateBitmapFromSectionEx(
		UInt32 Param_Width,
		UInt32 Param_Height,
		String^ Param_PixelFormat,
		IntPtr Param_Section,
		UInt32 Param_Stride,
		UInt32 Param_Offset,
		CA_WICSectionAccessLevel Param_AccessLevel,
		ICarenWICBitmap^ Param_Out_Bitmap);

	/// <summary>
	/// Retorna o tamanho do conteúdo de metadados contido pelo ICarenWICMetadataWriter especificado . O tamanho devolvido explica o cabeçalho e o comprimento dos metadados.
	/// </summary>
	/// <param name="Param_GuidContainer">O contêiner GUID.</param>
	/// <param name="Param_Writer">O ICarenWICMetadataWriter que contém o conteúdo.</param>
	/// <param name="Param_Out_Size">Retorna o tamanho do conteúdo de metadados.</param>
	CarenResult _WICGetMetadataContentSize(
		String^ Param_GuidContainer,
		ICarenWICMetadataWriter^ Param_Writer,
		OutParam UInt64% Param_Out_Size);

	/// <summary>
	/// Obtém o nome curto associado a um determinado GUID.
	/// </summary>
	/// <param name="Param_Guid">O GUID para recuperar o nome curto.</param>
	/// <param name="Param_SizeName">O tamanho do buffer em (Param_SizeName). Defina como 0 para receber o valor necessário em (Param_Out_SizeAtual).</param>
	/// <param name="Param_Out_Name">Recebe o nome curto associado ao GUID. Ignore esse valor para receber o tamanho necessário de (Param_SizeName) em (Param_Out_SizeAtual).</param>
	/// <param name="Param_Out_SizeAtual">Retorna tamanho real necessário para recuperar todo o nome curto associado ao GUID.</param>
	CarenResult _WICMapGuidToShortName(
		String^ Param_Guid,
		UInt32 Param_SizeName,
		CarenParamResolver<String^>^% Param_Out_Name,
		OutParam UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Obtém o nome associado a um determinado esquema.
	/// </summary>
	/// <param name="Param_Guid">O formato de metadados GUID.</param>
	/// <param name="Param_Schema">A sequência URI do esquema para o qual o nome deve ser recuperado.</param>
	/// <param name="Param_SizeName">O tamanho do buffer em (Param_SizeName). Defina como 0 para receber o valor necessário em (Param_Out_SizeAtual).</param>
	/// <param name="Param_Out_Name">Retorna o nome do esquema. Ignore esse valor para receber o tamanho necessário de (Param_SizeName) em (Param_Out_SizeAtual).</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real necessário para recuperar todo o nome do esquema.</param>
	CarenResult _WICMapSchemaToName(
		String^ Param_Guid,
		String^ Param_Schema,
		UInt32 Param_SizeName,
		CarenParamResolver<String^>^% Param_Out_Name,
		OutParam UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Obtém o GUID associado ao nome curto dado.
	/// </summary>
	/// <param name="Param_Name">O nome curto.</param>
	/// <param name="Param_Out_Guid">Retorna o GUID associado ao nome curto dado.</param>
	CarenResult _WICMapShortNameToGuid(
		String^ Param_Name,
		OutParam String^% Param_Out_Guid);

	/// <summary>
	/// Obtém um formato de metadados GUID para um formato de contêiner especificado e fornecedor que melhor corresponda ao conteúdo dentro de um determinado fluxo.
	/// </summary>
	/// <param name="Param_GuidContainer">O GUID do formato do contêiner.</param>
	/// <param name="Param_GuidVendor">O GuID do fornecedor.</param>
	/// <param name="Param_Stream">O fluxo de conteúdo para combinar com um formato de metadados.</param>
	/// <param name="Param_Out_Guid">Retorna um formato de metadados GUID para os parâmetros determinados.</param>
	CarenResult _WICMatchMetadataContent(
		String^ Param_GuidContainer,
		String^ Param_GuidVendor,
		ICarenStream^ Param_Stream,
		OutParam String^% Param_Out_Guid);
	
	/// <summary>
	/// Escreve metadados em um determinado fluxo.
	/// </summary>
	/// <param name="Param_GuidContainer">O formato do contêiner GUID.</param>
	/// <param name="Param_Writer">O escritor de metadados para escrever metadados para o córrego.</param>
	/// <param name="Param_PersistOptions">As opções CA_WICPersistOptions para usar ao escrever os metadados.</param>
	/// <param name="Param_Stream">O fluxo de destino que vai receber os dados.</param>
	CarenResult _WICSerializeMetadataContent(
		String^ Param_GuidContainer,
		ICarenWICMetadataWriter^ Param_Writer,
		CA_WICPersistOptions Param_PersistOptions,
		ICarenStream^ Param_Stream);
};