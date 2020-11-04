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
#include "CarenWICBitmapEncoderInfo.h"
#include "CarenWICMetadataQueryWriter.h"
#include "CarenWICBitmapFrameEncode.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por definir métodos para definir as propriedades de um codificador, como miniaturas, quadros e paletas.
/// </summary>
public ref class CarenWICBitmapEncoder : public ICarenWICBitmapEncoder
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapEncoder).
	IWICBitmapEncoder* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapEncoder();
	
	~CarenWICBitmapEncoder();

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


	//Métodos da interface(ICarenWICBitmapEncoder)
public:
	/// <summary>
	/// Confirma todas as alterações para a imagem e fecha o fluxo.
	/// Para finalizar uma imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que 
	/// todos os frames foram (Committed). Depois que o codificador foi cometido, ele não pode ser reiniciado ou reutilizado com outro fluxo. Uma nova interface de codificador 
	/// deve ser criada, por exemplo, com ICarenWICImagingFactory::CreateEncoder. Para que o codificador Comprometa-se a ter sucesso, você deve, no mínimo, chamar 
	/// ICarenWICBitmapEncoder::Initialize e ICarenWICBitmapFrameEncode::WriteSource ou ICarenWICBitmapFrameEncode::WritePixels.
	/// </summary>
	virtual CarenResult Commit();

	/// <summary>
	/// Cria uma nova instância ICarenWICBitmapFrameEncode. 
	/// Para formatos que suportam codificação de vários frames (por exemplo, TIFF, JPEG-XR), você pode trabalhar em apenas um frame por vez. Isso significa que você deve 
	/// ligar para o IWICBitmapFrameEncode::Commit antes de chamar o CreateNewFrame novamente.
	/// </summary>
	/// <param name="Param_Out_FrameEncode">Retorna uma interface(ICarenWICBitmapFrameEncode) que contém um ponteiro para a nova instância do ICarenWICBitmapFrameEncode.</param>
	/// <param name="Param_Ref_OpcoesEncodificacao">(Opcional) Recebe as propriedades nomeadas para usar para inicialização subsequente do frame. O usuário deve inicializar a interface se desejar receber um ponteiro para a interface.</param>
	virtual CarenResult CreateNewFrame(
	[Out] ICarenWICBitmapFrameEncode^% Param_Out_FrameEncode,
	ICarenPropertyBag2^% Param_Ref_OpcoesEncodificacao);

	/// <summary>
	/// Recupera o formato do recipiente do codificador. 
	/// </summary>
	/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID do formato de contêiner do codificador.</param>
	virtual CarenResult GetContainerFormat(
	[Out] String^% Param_Out_GuidContainerFormat);

	/// <summary>
	/// Recupera um ICarenWICBitmapEncoderInfo para o codificador. 
	/// </summary>
	/// <param name="Param_Out_EncoderInfo">Retorna uma interface(ICarenWICBitmapEncoderInfo) que contém um ponteiro para o objeto de informações do codificador.</param>
	virtual CarenResult GetEncoderInfo(
	[Out] ICarenWICBitmapEncoderInfo^% Param_Out_EncoderInfo);

	/// <summary>
	/// Recupera um escritor de consulta de metadados para o codificador. 
	/// </summary>
	/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados do codificador.</param>
	virtual CarenResult GetMetadataQueryWriter(
	[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter);

	/// <summary>
	/// Inicializa o codificador com um ICarenStream que diz ao codificador onde codificar os bits. 
	/// </summary>
	/// <param name="Param_Stream">O fluxo de saída.</param>
	/// <param name="Param_OpcoesCache">O WICBitmapEncoderCacheOption usado na inicialização.</param>
	virtual CarenResult Initialize(
	ICarenStream^ Param_Stream,
	CA_WICBitmapEncoderCacheOption Param_OpcoesCache);

	/// <summary>
	/// Define os objetos ICarenWICColorContext para o codificador. 
	/// </summary>
	/// <param name="Param_Quantidade">O número de ICarenWICColorContext a definir.</param>
	/// <param name="Param_ColorContexts">Uma matriz de interfaces(ICarenWICColorContext) contendo os contextos de cor para definir para o codificador.</param>
	virtual CarenResult SetColorContexts(
	UInt32 Param_Quantidade,
	cli::array<ICarenWICColorContext^>^ Param_ColorContexts);

	/// <summary>
	/// Define a paleta global para a imagem. 
	/// Apenas as imagens GIF suportam uma paleta global opcional, e você deve definir a paleta global antes de adicionar quaisquer frames à imagem. Você só precisa 
	/// definir a paleta para formatos de pixel indexados.
	/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
	/// </summary>
	/// <param name="Param_Palette">Uma interface(ICarenWICPalette) para usar como paleta global.</param>
	virtual CarenResult SetPalette(
	ICarenWICPalette^ Param_Palette);

	/// <summary>
	/// Define a visualização global para a imagem. 
	/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
	/// </summary>
	/// <param name="Param_Preview">Uma interface(ICarenWICBitmapSource) para usar como pré-visualização global.</param>
	virtual CarenResult SetPreview(
	ICarenWICBitmapSource^ Param_Preview);

	/// <summary>
	/// Define a miniatura global para a imagem. 
	/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
	/// </summary>
	/// <param name="Param_Thumbnail">Uma interface (ICarenWICBitmapSource) para definir como a miniatura global.</param>
	virtual CarenResult SetThumbnail(
	ICarenWICBitmapSource^ Param_Thumbnail);
};