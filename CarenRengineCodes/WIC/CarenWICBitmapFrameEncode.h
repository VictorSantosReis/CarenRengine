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
#include "CarenWICMetadataQueryWriter.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responável responsável por representar os quadros(frames) de imagem individuais de um codificador.
/// </summary>
public ref class CarenWICBitmapFrameEncode : public ICarenWICBitmapFrameEncode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapFrameEncode).
	IWICBitmapFrameEncode* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapFrameEncode();
	
	~CarenWICBitmapFrameEncode();

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


	//Métodos da interface(ICarenWICBitmapFrameEncode)
public:
	/// <summary>
	/// Confirma o frame para a imagem.
	/// Depois que o frame Commit for chamado, você não pode usar ou reiniciar o objeto ICarenWICBitmapFrameEncode e quaisquer objetos criados a partir dele.
	/// Para finalizar a imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que todos 
	/// os frames forem confirmados(Committed). 
	/// </summary>
	virtual CarenResult Commit();

	/// <summary>
	/// Recebe o escritor de consulta de metadados para o frame do codificador. 
	/// Se você estiver configurando metadados no frame, você deve fazer isso antes de usar ICarenWICBitmapFrameEncode::WritePixels ou ICarenWICBitmapFrameEncode::WriteSource 
	/// para gravar quaisquer pixels de imagem no frame.
	/// </summary>
	/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados para o 
	/// frame do codificador.</param>
	virtual CarenResult GetMetadataQueryWriter(
	[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);

	/// <summary>
	/// Inicializa o codificador de frames usando as propriedades dadas.
	/// Se você não quiser opções de codificação, passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe o ICarenPropertyBag2 fornecido pelo 
	/// ICarenWICBitmapEncoder::CreateNewFrame com valores atualizados. Voce pode acessar o GUIDs::GUIDs_WIC_CLSIDs_ENCODIFICADORES para obter uma lista de codificadores suportados.
	/// </summary>
	/// <param name="Param_OpcoesEncodificacao">O conjunto de propriedades a serem usados para inicialização do ICarenWICBitmapFrameEncode. e você não quiser opções de codificação, 
	/// passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe um ICarenPropertyBag2 fornecido pelo ICarenWICBitmapEncoder::CreateNewFrame com valores 
	/// atualizados.</param>
	virtual CarenResult Initialize(ICarenPropertyBag2^ Param_OpcoesEncodificacao);

	/// <summary>
	/// Define um determinado número de perfis ICarenWICColorContext ao quadro. 
	/// </summary>
	/// <param name="Param_Quantidade">O número de perfis ICarenWICColorContext a definir na matriz (Param_ColorContexts).</param>
	/// <param name="Param_ColorContexts">Uma matriz de interfaces IWICColorContext contendo os perfis de contextos de cores a serem configurados para o frame.</param>
	virtual CarenResult SetColorContexts(
	UInt32 Param_Quantidade,
	cli::array<ICarenWICColorContext^>^ Param_ColorContexts);

	/// <summary>
	/// Define o ICarenWICPalette para formatos de pixel indexados. 
	/// Este método não falha se chamado em um frame cujo formato de pixel é definido como um formato de pixel não indexado. Se o formato de pixel de destino for um formato não indexado, 
	/// a paleta será ignorada. Se você já ligou para ICarenWICBitmapEncoder::SetPalette para definir uma paleta global, este método substitui essa paleta para o frame atual.
	/// A paleta deve ser especificada antes da primeira chamada para WritePixels/WriteSource. Isso fará com que o WriteSource use a paleta especificada ao converter a imagem de origem 
	/// no formato de pixel do codificador. Se nenhuma paleta for especificada, uma paleta será gerada na primeira chamada para WriteSource.
	/// </summary>
	/// <param name="Param_Palette">A interface ICarenWICPalette para usar para formatos de pixel indexados. O codificador pode alterar a paleta para refletir os formatos de pixel que 
	/// o codificador suporta.</param>
	virtual CarenResult SetPalette(ICarenWICPalette^ Param_Palette);

	/// <summary>
	/// Solicita que o codificador use o formato de pixel especificado.
	/// O codificador pode não suportar o formato de pixel solicitado. Caso não, o (Param_Ref_INOUT_GuidFormatoPixel) retorna a correspondência mais próxima no bloco de memória a que 
	/// (Param_Ref_INOUT_GuidFormatoPixel) aponta. Se o formato de pixel retornado não corresponder ao formato solicitado, você deve usar um objeto ICarenWICFormatConverter para 
	/// converter os dados do pixel.
	/// </summary>
	/// <param name="Param_Ref_INOUT_GuidFormatoPixel">Na entrada, o GUID de formato de pixel solicitado. Na saída, o GUID do formato de pixel mais próximo suportado pelo codificador; 
	/// isso pode ser diferente do formato solicitado. Consulte a estrutura Guids::GUIDs_WIC_NATIVE_PIXEL_FORMATS para obter uma lista de GUIDs com os formatos de pixel suportados pelo WIC.</param>
	virtual CarenResult SetPixelFormat(String^% Param_Ref_INOUT_GuidFormatoPixel);

	/// <summary>
	/// Define a resolução física da imagem de saída.
	/// O Windows Imaging Component (WIC) não realiza nenhum processamento especial como resultado dos valores de resolução de DPI. Por exemplo, os dados retornados do 
	/// ICarenWICBitmapFonte::CopyPixels não é dimensionado pelo DPI. O aplicativo deve lidar com a resolução de DPI.
	/// </summary>
	/// <param name="Param_DpiX">O valor da resolução Horizontal.</param>
	/// <param name="Param_DpiY">O valor da resolução Vertical.</param>
	virtual CarenResult SetResolution(
	double Param_DpiX,
	double Param_DpiY);

	/// <summary>
	/// Define as dimensões da imagem de saída para o quadro. 
	/// </summary>
	/// <param name="Param_Width">A Largura da imagem de saída.</param>
	/// <param name="Param_Height">A Altura da imagem de saída.</param>
	virtual CarenResult SetSize(
	UInt32 Param_Width,
	UInt32 Param_Height);

	/// <summary>
	/// Define a miniatura do quadro se suportado pelo codec. 
	/// Recomendamos que você ligue para SetThumbnail antes de ligar para WritePixels ou WriteSource. A miniatura não será adicionada ao arquivo codificado se o SetThumbnail for 
	/// chamado após uma chamada para WritePixels ou WriteSource.
	/// </summary>
	/// <param name="Param_Thumbnail">A fonte bitmap para usar como miniatura.</param>
	virtual CarenResult SetThumbnail(ICarenWICBitmapSource^ Param_Thumbnail);

	/// <summary>
	/// Copia dados da linha de varredura de um buffer fornecido pelo chamador para o objeto ICarenWICBitmapFrameEncode.
	/// Sucessivas chamadas WritePixels são consideradas de acesso sequencial à linha de varredura na imagem de saída.
	/// </summary>
	/// <param name="Param_QuantidadeLinhas">O número de linhas para codificar.</param>
	/// <param name="Param_Stride">O Stride dos pixels de imagem.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer de pixels.</param>
	/// <param name="Param_Pixels">Uma interface(ICarenBuffer) para os dados de pixels.</param>
	virtual CarenResult WritePixels(
	UInt32 Param_QuantidadeLinhas,
	UInt32 Param_Stride,
	UInt32 Param_TamanhoBuffer,
	ICarenBuffer^ Param_Pixels);

	/// <summary>
	/// Codifica uma fonte de bitmap. 
	/// Se o SetSize não for chamado antes de chamar WriteSource, o tamanho dado no (Param_RetanguloBitmap) será usado se não for NULO. Caso contrário, o tamanho do ICarenWICBitmapSource
	///  dado em (Param_BitmapSource) é usado. Se o SetPixelFormat não for chamado antes de chamar WriteSource, o formato de pixel do ICarenWICBitmapSource dado no (Param_BitmapSource) é usado.
	/// Se o SetResolution não for chamado antes de chamar WriteSource, o formato pixel do (Param_BitmapSource) será usado.
	/// Se o SetPalette não for chamado antes de chamar WriteSource, o formato de pixel alvo será indexado, e o formato de pixel do (Param_BitmapSource) corresponde ao formato 
	/// de pixel do quadro do codificador, então o formato de pixel (Param_BitmapSource) é usado.
	/// </summary>
	/// <param name="Param_BitmapSource">A fonte do bitmap para codificar.</param>
	/// <param name="Param_RetanguloBitmap">O retângulo de tamanho da fonte do bitmap.</param>
	virtual CarenResult WriteSource(
	ICarenWICBitmapSource^ Param_BitmapSource,
	CA_WICRect^ Param_RetanguloBitmap);
};