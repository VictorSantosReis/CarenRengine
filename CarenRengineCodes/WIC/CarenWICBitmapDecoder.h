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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenWICColorContext.h"
#include "CarenWICBitmapDecoderInfo.h"
#include "CarenWICBitmapFrameDecode.h"
#include "CarenWICMetadataQueryReader.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor  métodos que representam um decodificador. A interface fornece acesso às propriedades do decodificador, como 
/// miniaturas globais (se suportadas), frames e paleta.
/// </summary>
public ref class CarenWICBitmapDecoder : public ICarenWICBitmapDecoder
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapDecoder).
	IWICBitmapDecoder* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapDecoder();
	
	~CarenWICBitmapDecoder();

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


	//Métodos da interface(ICarenWICBitmapDecoder)
public:
	/// <summary>
	/// Copia o ICarenWICPalette do decodificador.
	/// CopyPalette retorna uma paleta global (uma paleta que se aplica a todos os frames da imagem) se houver uma; caso contrário, ele retorna WINCODEC_ERR_PALETTEUNAVAILABLE. 
	/// Se uma imagem não tiver uma paleta global, ela ainda pode ter uma paleta de nível de frame, que pode ser recuperada usando ICarenWICBitmapFrameDecode::CopyPalette.
	/// </summary>
	/// <param name="Param_Palette">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a paleta global do decodificador. Use o 
	/// ICarenWICImagingFactory::CreatePalette para criar a paleta de destino antes de chamar o CopyPalette.</param>
	virtual CarenResult CopyPalette(ICaren^ Param_Palette);

	/// <summary>
	/// Recupera os objetos ICarenWICColorContext da imagem. 
	/// </summary>
	/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
	/// <param name="Param_Ref_ColorContexts">Retorna uma matriz de interfaces (ICarenWICColorContext).</param>
	/// <param name="Param_Out_SizeAtual">Retorna o número real de interfaces na matriz (Param_Ref_ColorContexts).</param>
	virtual CarenResult GetColorContexts(
	UInt32 Param_Quantidade,
	cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o formato do recipiente da imagem. 
	/// </summary>
	/// <param name="Param_Out_GuidContainerFormat">Retorna um GUID que representa o contêiner de formato da imagem.</param>
	virtual CarenResult GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat);

	/// <summary>
	/// Recupera um ICarenWICBitmapDecoderInfo para a imagem. 
	/// </summary>
	/// <param name="Param_Out_DecoderInfo">Retorna uma interface(ICarenWICBitmapDecoderInfo) que contém um ponteiro para o objeto de informações do decodificador.</param>
	virtual CarenResult GetDecoderInfo([Out] ICarenWICBitmapDecoderInfo^% Param_Out_DecoderInfo);

	/// <summary>
	/// Recupera o Frame especificado da imagem. 
	/// </summary>
	/// <param name="Param_Index">O quadro em particular para recuperar.</param>
	/// <param name="Param_Out_BitmapFrame">Retorna uma interface(ICarenWICBitmapFrameDecode) contém um ponteiro para o frame especificado.</param>
	virtual CarenResult GetFrame(
	UInt32 Param_Index,
	[Out] ICarenWICBitmapFrameDecode^% Param_Out_BitmapFrame);

	/// <summary>
	/// Recupera o número total de frames na imagem. 
	/// </summary>
	/// <param name="Param_Out_QuantidadeFrames">Retorna o número total de frames na imagem.</param>
	virtual CarenResult GetFrameCount([Out] UInt32% Param_Out_QuantidadeFrames);

	/// <summary>
	/// Recupera o leitor de consulta de metadados do decodificador. Se um formato de imagem não suportar metadados em nível de contêiner, isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
	/// O único formato de imagem fornecido pelo Windows que suporta metadados em nível de contêiner é o GIF. Em vez disso, use ICarenWICBitmapFrameDecode::GetMetadataQueryReader.
	/// </summary>
	/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) contém um ponteiro para o leitor de consulta de metadados do decodificador.</param>
	virtual CarenResult GetMetadataQueryReader([Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader);

	/// <summary>
	/// Recupera uma imagem de visualização, se suportada. Nem todos os formatos suportam visualizações. Apenas as visualizações nativas do codec Microsoft Windows Digital Photo 
	/// (WDP) suportam visualizações.
	/// </summary>
	/// <param name="Param_Out_BitmapSource">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o bitmap de visualização se suportado.</param>
	virtual CarenResult GetPreview([Out] ICarenWICBitmapSource^% Param_Out_BitmapSource);

	/// <summary>
	/// Recupera uma miniatura bitmap da imagem, se existir.
	/// A miniatura devolvida pode ser de qualquer tamanho, por isso o chamador deve dimensionar a miniatura para o tamanho desejado. Os únicos formatos de imagem fornecidos 
	/// pelo Windows que suportam miniaturas são JPEG, TIFF e JPEG-XR. Se a miniatura não estiver disponível, isso retornará WINCODEC_ERR_CODECNOTHUMBNAIL.
	/// </summary>
	/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o objeto de miniatura.</param>
	virtual CarenResult GetThumbnail([Out] ICarenWICBitmapSource^% Param_Out_Thumbnail);

	/// <summary>
	/// Inicializa o decodificador com o fluxo fornecido. 
	/// </summary>
	/// <param name="Param_Stream">O fluxo a ser usado para a inicialização. O fluxo contém os pixels codificados que são decodificados cada vez que o método CopyPixels na 
	/// interface ICarenWICBitmapFrameDecode é invocado.</param>
	/// <param name="Param_OpcoesCache">Uma enumeração que especifica as opções do decodificador.</param>
	virtual CarenResult Initialize(
	ICarenStream^ Param_Stream,
	CA_WICDecodeOptions Param_OpcoesCache);

	/// <summary>
	/// Recupera as capacidades do decodificador com base no fluxo especificado.
	/// As implementações de decodificadores personalizadas devem salvar a posição atual do (ICarenStream) especificado, ler quaisquer informações necessárias para determinar quais 
	/// recursos elas podem fornecer para o fluxo fornecido e restaurar a posição do fluxo.
	/// </summary>
	/// <param name="Param_Stream">O fluxo para recuperar as capacidades de decodificador.</param>
	/// <param name="Param_Out_Capacidades">Retorna uma enumerações que especifica as capacidades do decodificador para o fluxo informado.</param>
	virtual CarenResult QueryCapability(
	ICarenStream^ Param_Stream,
	[Out] CA_WICBitmapDecoderCapabilities% Param_Out_Capacidades);
};