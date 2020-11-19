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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenWICBitmap.h"
#include "CarenWICBitmapClipper.h"
#include "CarenWICBitmapFlipRotator.h"
#include "CarenWICBitmapScaler.h"
#include "CarenWICColorContext.h"
#include "CarenWICColorTransform.h"
#include "CarenWICComponentInfo.h"
#include "CarenWICBitmapDecoder.h"
#include "CarenWICBitmapEncoder.h"
#include "CarenWICFastMetadataEncoder.h"
#include "CarenWICFormatConverter.h"
#include "CarenWICPalette.h"
#include "CarenWICMetadataQueryWriter.h"
#include "CarenWICMetadataReader.h"
#include "CarenWICMetadataWriter.h"
#include "CarenWicStream.h"
#include "../Windows/CarenEnumUnknown.h"
#include "../Windows/CarenPropertyBag2.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que criam componentes usados pelos desenvolvedores de componentes. Isso inclui leitores de metadados, gravadores 
/// e outros serviços para uso dos desenvolvedores de codec e manipuladores de metadados.
/// </summary>
public ref class CarenWICComponentFactory : public ICarenWICComponentFactory
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICComponentFactory).
	IWICComponentFactory* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICComponentFactory();
	
	~CarenWICComponentFactory();

	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}


	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenWICComponentFactory)
public:
	/// <summary>
	/// Cria uma bag de propriedades do codificador. 
	/// </summary>
	/// <param name="Param_ArrayPropOptions">Uma matriz de estruturas(CA_PROPBAG2) usadas para criar a bag de propriedades do codificador.</param>
	/// <param name="Param_Quantidade">A quantidade de items na matriz em (Param_ArrayPropOptions).</param>
	/// <param name="Param_Out_PropertyBag">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a nova bag de propriedades do codificador.</param>
	virtual CarenResult CreateEncoderPropertyBag(
	cli::array<CA_PROPBAG2^>^ Param_ArrayPropOptions,
	UInt32 Param_Quantidade,
	[Out] ICarenPropertyBag2^% Param_Out_PropertyBag);

	/// <summary>
	/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
	/// </summary>
	/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
	/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
	/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
	/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
	/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
	virtual CarenResult CreateMetadataReader(
	String^ Param_GuidFormatoMetadata,
	String^ Param_GuidVendor,
	UInt32 Param_Opcoes,
	ICarenStream^ Param_Fluxo,
	[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);

	/// <summary>
	/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
	/// </summary>
	/// <param name="Param_GuidFormatoContainer">O formato de contêiner GUID para basear o leitor.</param>
	/// <param name="Param_GuidVendor">O fornecedor GUID do leitor de metadados.</param>
	/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
	/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
	/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
	virtual CarenResult CreateMetadataReaderFromContainer(
	String^ Param_GuidFormatoContainer,
	String^ Param_GuidVendor,
	UInt32 Param_Opcoes,
	ICarenStream^ Param_Fluxo,
	[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);

	/// <summary>
	/// Cria um ICarenWICMetadataWriter baseado nos parâmetros determinados. 
	/// </summary>
	/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
	/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
	/// <param name="Param_OpcoesMetadata">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o escritor de metadados.</param>
	/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
	virtual CarenResult CreateMetadataWriter(
	String^ Param_GuidFormatoMetadata,
	String^ Param_GuidVendor,
	UInt32 Param_OpcoesMetadata,
	[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

	/// <summary>
	/// Cria um ICarenWICMetadataWriter do dado ICarenWICMetadataReader. 
	/// </summary>
	/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataReader) para o leitor de metadados para basear o escritor de metadados.</param>
	/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
	/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
	virtual CarenResult CreateMetadataWriterFromReader(
	ICarenWICMetadataReader^ Param_MetadataReader,
	String^ Param_GuidVendor,
	[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

	/// <summary>
	/// Cria um ICarenWICMetadataQueryReader a partir do ICarenWICMetadataBlockReader. 
	/// </summary>
	/// <param name="Param_MetadataBlockReader">Uma interface(ICarenWICMetadataQueryReader) para o leitor de bloco para basear o escritor de consulta.</param>
	/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o novo leitor de consulta de metadados.</param>
	virtual CarenResult CreateQueryReaderFromBlockReader(
	ICarenWICMetadataBlockReader^ Param_MetadataBlockReader,
	[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader);

	/// <summary>
	/// Cria um ICarenWICMetadataQueryWriter do dado ICarenWICMetadataBlockWriter. 
	/// </summary>
	/// <param name="Param_MetadataBlockWriter">Uma interface(ICarenWICMetadataBlockWriter) para o escritor de bloco para basear o escritor de consulta.</param>
	/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consulta de metadados.</param>
	virtual CarenResult CreateQueryWriterFromBlockWriter(
	ICarenWICMetadataBlockWriter^ Param_MetadataBlockWriter,
	[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);


	//Métodos da interface(ICarenWICImagingFactory)
public:
	/// <summary>
	/// Cria um objeto ICarenWICBitmap. 
	/// </summary>
	/// <param name="Param_Width">A largura do novo bitmap .</param>
	/// <param name="Param_Height">A altura do novo bitmap.</param>
	/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap.</param>
	/// <param name="Param_OpcoesCache">As opções de criação de cache do novo bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmap(
		UInt32 Param_Width,
		UInt32 Param_Height,
		String^ Param_GuidFormatoPixel,
		CA_WICBitmapCreateCacheOption Param_OpcoesCache,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria uma nova instância de um objeto ICarenWICBitmapClipper. 
	/// </summary>
	/// <param name="Param_Out_BitmapClipper">Retorna uma interface(Param_Out_BitmapClipper) que contém um ponteiro para o novo Clipper.</param>
	virtual CarenResult CreateBitmapClipper([Out] ICarenWICBitmapClipper^% Param_Out_BitmapClipper);

	/// <summary>
	/// Cria uma nova instância de um objeto ICarenWICBitmapFlipRotator. 
	/// </summary>
	/// <param name="Param_Out_BitmapFlipRotator">Retorna uma interface(ICarenWICBitmapFlipRotator) que contém um ponteiro para o novo rotacionador de bitmap.</param>
	virtual CarenResult CreateBitmapFlipRotator([Out] ICarenWICBitmapFlipRotator^% Param_Out_BitmapFlipRotator);

	/// <summary>
	/// Cria um ICarenWICBitmap a partir de uma Handle para o bitmap. 
	/// </summary>
	/// <param name="Param_HandleBitmap">Uma handle para o bitmap para criar o bitmap.</param>
	/// <param name="Param_HandlePaleta">Uma handle para a palleta usada para criar o bitmap.</param>
	/// <param name="Param_OpcoesCanalAlfa">As opções do canal alfa para criar o bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromHBITMAP(
		IntPtr Param_HandleBitmap,
		IntPtr Param_HandlePaleta,
		CA_WICBitmapAlphaChannelOption Param_OpcoesCanalAlfa,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ICarenWICBitmap a partir de uma handle para o ícone. 
	/// </summary>
	/// <param name="Param_HandleIcon">Uma handle para o ícone para criar o bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromHICON(
		IntPtr Param_HandleIcon,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ICarenWICBitmap a partir de um bloco de memória. O tamanho do ICarenWICBitmap a ser criado deve ser menor ou igual ao tamanho da imagem em (Param_Buffer).
	/// O Stride do bitmap de destino será igual ao Stride dos dados de origem, independentemente da largura e altura especificados.
	/// O parâmetro (Param_GuidFormatoPixel) define o formato de pixel tanto para os dados de entrada quanto para o bitmap de saída.
	/// </summary>
	/// <param name="Param_Width">A largura do novo bitmap.</param>
	/// <param name="Param_Height">A altura do novo bitmap.</param>
	/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap. Consulte a estrutura (GUIDs_WIC_NATIVE_PIXEL_FORMATS) para obter uma lista de guids para esse parametro.</param>
	/// <param name="Param_Stride">O número de bytes entre linhas de varredura sucessivas em (Param_Buffer).</param>
	/// <param name="Param_BufferSize">O tamanho do (Param_Buffer).</param>
	/// <param name="Param_Buffer">O buffer usado para criar o bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromMemory(
		UInt32 Param_Width,
		UInt32 Param_Height,
		String^ Param_GuidFormatoPixel,
		UInt32 Param_Stride,
		UInt32 Param_BufferSize,
		ICarenBuffer^ Param_Buffer,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ICarenWICBitmap a partir de um ICarenWICBitmapSource. 
	/// </summary>
	/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
	/// <param name="Param_OpcoesCache">As opções de cache do novo bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromSource(
		ICarenWICBitmapSource^ Param_FonteBitmap,
		CA_WICBitmapCreateCacheOption Param_OpcoesCache,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria um ICarenWICBitmap a partir de um retângulo especificado de um ICarenWICBitmapSource. Fornecer um retângulo maior que a fonte produzirá resultados indefinidos.
	/// Este método sempre cria uma cópia separada da imagem de origem, semelhante à opção de cache WICBitmapCacheOnLoad.
	/// </summary>
	/// <param name="Param_FonteBitmap">>Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
	/// <param name="Param_X">A coordenada horizontal do canto superior esquerdo do retângulo.</param>
	/// <param name="Param_Y">A coordenada vertical do canto superior esquerdo do retângulo.</param>
	/// <param name="Param_Width">A largura do retângulo e o novo bitmap.</param>
	/// <param name="Param_Height">A altura do retângulo e o novo bitmap.</param>
	/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
	virtual CarenResult CreateBitmapFromSourceRect(
		ICarenWICBitmapSource^ Param_FonteBitmap,
		UInt32 Param_X,
		UInt32 Param_Y,
		UInt32 Param_Width,
		UInt32 Param_Height,
		[Out] ICarenWICBitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Cria uma nova instância de um IWICBitmapScaler. 
	/// </summary>
	/// <param name="Param_Out_BitmapScaler">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo redimensionador.</param>
	virtual CarenResult CreateBitmapScaler([Out] ICarenWICBitmapScaler^% Param_Out_BitmapScaler);

	/// <summary>
	/// Cria uma nova instância da classe IWICColorContext. 
	/// </summary>
	/// <param name="Param_Out_WicColorContext">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo contexto de cores.</param>
	virtual CarenResult CreateColorContext([Out] ICarenWICColorContext^% Param_Out_WicColorContext);

	/// <summary>
	/// Cria uma nova instância da classe IWICColorTransform. 
	/// </summary>
	/// <param name="Param_Out_WicColorTransform">Retorna uma interface(ICarenWICColorTransform) que contém um ponteiro para o novo transformado de contexto de cor.</param>
	virtual CarenResult CreateColorTransformer([Out] ICarenWICColorTransform^% Param_Out_WicColorTransform);

	/// <summary>
	/// Cria um objeto IEnumUnknown dos tipos de componentes especificados. 
	/// Os tipos de componentes devem ser enumerados separadamente. Combinações de tipos de componentes e WICAllComponents não são suportadas.
	/// </summary>
	/// <param name="Param_TiposComponentes">Os tipos de WICComponentType para enumerar.</param>
	/// <param name="Param_OpcoesEnumeracao">As Opções WICComponentEnumerate utilizadas para enumerar os tipos de componentes dado.</param>
	/// <param name="Param_Out_Enumerador">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para um novo enumerador de componentes.</param>
	virtual CarenResult CreateComponentEnumerator(
		CA_WICComponentType Param_TiposComponentes,
		CA_WICComponentEnumerateOptions Param_OpcoesEnumeracao,
		[Out] ICarenEnumUnknown^% Param_Out_Enumerador);

	/// <summary>
	/// Cria uma nova instância da classe IWICComponentInfo para o identificador de classe de componentes dado (CLSID). 
	/// </summary>
	/// <param name="Param_ClsidComponente">O CLSID para o componente desejado.</param>
	/// <param name="Param_Out_ComponenteInfo">Retorna uma interface(ICarenWICComponentInfo) que contém um ponteiro para um novo informador de componente.</param>
	virtual CarenResult CreateComponentInfo(
		String^ Param_ClsidComponente,
		[Out] ICarenWICComponentInfo^% Param_Out_ComponenteInfo);

	/// <summary>
	/// Cria uma nova instância do ICarenWICBitmapDecoder. 
	/// </summary>
	/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado.</param>
	/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido.</param>
	/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador. Você deve inicializar este 
	/// ICarenWICBitmapDecoder em um fluxo usando o método (Initialize) mais tarde.</param>
	virtual CarenResult CreateDecoder(
		String^ Param_GuidFormatoContainer,
		String^ Param_GuidVendor,
		[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

	/// <summary>
	/// Cria uma nova instância do ICarenWICBitmapDecoder com base na handle de arquivo dada. 
	/// </summary>
	/// <param name="Param_HandleArquivo">A handle para o arquivo para ser utilizado para criar o decodifciador.</param>
	/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
	/// <param name="Param_OpcoesDecoder">As opções de código WIC para usar ao criar o decodificador.</param>
	/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
	virtual CarenResult CreateDecoderFromFileHandle(
		UInt64 Param_HandleArquivo,
		String^ Param_GuidVendor,
		CA_WICDecodeOptions Param_OpcoesDecoder,
		[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no arquivo dado. 
	/// </summary>
	/// <param name="Param_UrlArquivo">Uma string que especifica o nome de um objeto para criar ou abrir.</param>
	/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
	/// <param name="Param_TipoAcesso">O acesso ao objeto, que pode ser lido, escrito ou ambos.</param>
	/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
	/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
	virtual CarenResult CreateDecoderFromFilename(
		String^ Param_UrlArquivo,
		String^ Param_GuidVendor,
		CA_ACCESS_RIGHTS Param_TipoAcesso,
		CA_WICDecodeOptions Param_OpcoesMetadata,
		[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no ICarenStream dado. 
	/// </summary>
	/// <param name="Param_Fluxo">O fluxo para criar o decodificador.</param>
	/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULL se não houver fornecedor preferencial.</param>
	/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
	/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
	virtual CarenResult CreateDecoderFromStream(
		ICarenStream^ Param_Fluxo,
		String^ Param_GuidVendor,
		CA_WICDecodeOptions Param_OpcoesMetadata,
		[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICBitmapDecoder. Os valores disponiveis para (Param_GuidFormatoContainer) e (Param_GuidVendor) listados aqui, não são os unicos disponiveis.
	/// Esses são apenas os valores suportados nativamente pelo sistema operacional e não incluem codecs de terceiros que possam está habilitados para o WIC.
	/// </summary>
	/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado. Consulte a estrutura (GUIDs_WIC_CONTAINERS_FORMATOS) para obter um dos codecs 
	/// suportados pelo OS nativamente.</param>
	/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido. Consulte a estrutura (GUIDs_WIC_VENDORS) paraobter um dos fornecedores de codificadores 
	/// suportados pelo OS nativamente.</param>
	/// <param name="Param_Out_BitmapEncoder">Retorna uma interface(ICarenWICBitmapEncoder) que contém um ponteiro para o novo codificador.</param>
	virtual CarenResult CreateEncoder(
		String^ Param_GuidFormatoContainer,
		String^ Param_GuidVendor,
		[Out] ICarenWICBitmapEncoder^% Param_Out_BitmapEncoder);

	/// <summary>
	/// Cria uma nova instância do codificador de metadados rápidos baseado no determinado ICarenWICBitmapDecoder.
	/// Os codecs fornecidos pelo Windows não oferecem suporte à codificação rápida de metadados no nível do decodificador e apenas suportam codificação rápida de metadados no 
	/// nível do frame. Para criar um codificador de metadados rápido a partir de um frame, consulte o método CreateFastMetadataEncoderFromFrameDecode.
	/// </summary>
	/// <param name="Param_Decoder">O decodificador para criar o codificador de metadados rápidos.</param>
	/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
	virtual CarenResult CreateFastMetadataEncoderFromDecoder(
		ICarenWICBitmapDecoder^ Param_Decoder,
		[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder);

	/// <summary>
	/// Cria uma nova instância do codificador de metadados rápidos com base no frame de imagem dado. 
	/// </summary>
	/// <param name="Param_BitmapFrameDecode">Um ICarenWICBitmapFrameDecode que será utilizado para criar o ICarenWICFastMetadataEncoder.</param>
	/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
	virtual CarenResult CreateFastMetadataEncoderFromFrameDecode(
		ICarenWICBitmapFrameDecode^ Param_BitmapFrameDecode,
		[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICFormatConverter. 
	/// </summary>
	/// <param name="Param_Out_FormatConverter">Retorna uma interface(ICarenWICFormatConverter) que contém um ponteiro para o novo conversor de formato de pixels.</param>
	virtual CarenResult CreateFormatConverter([Out] ICarenWICFormatConverter^% Param_Out_FormatConverter);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICPalette. 
	/// </summary>
	/// <param name="Param_Out_WicPaleta">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a nova tabela de cores.</param>
	virtual CarenResult CreatePalette([Out] ICarenWICPalette^% Param_Out_WicPaleta);

	/// <summary>
	/// Cria uma nova instância de um escritor de consultas. 
	/// </summary>
	/// <param name="Param_GuidFormatoMetadata">O GUID para o formato de metadados desejado.</param>
	/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
	/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
	virtual CarenResult CreateQueryWriter(
		String^ Param_GuidFormatoMetadata,
		String^ Param_GuidVendor,
		[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter);

	/// <summary>
	/// Cria uma nova instância de um escritor de consulta com base no leitor de consultas. O escritor de consultas será pré-povoado com metadados do leitor de consulta. 
	/// </summary>
	/// <param name="Param_QueryReader">O ICarenWICMetadataQueryReader para criar o ICarenWICMetadataQueryWriter.</param>
	/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
	/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
	virtual CarenResult CreateQueryWriterFromReader(
		ICarenWICMetadataQueryReader^ Param_QueryReader,
		String^ Param_GuidVendor,
		[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter);

	/// <summary>
	/// Cria uma nova instância da classe ICarenWICStream. 
	/// </summary>
	/// <param name="Param_Out_WicStream">Retorna uma interface(ICarenWICStream) que contém um ponteiro para o novo fluxo WIC.</param>
	virtual CarenResult CreateStream([Out] ICarenWICStream^% Param_Out_WicStream);
};