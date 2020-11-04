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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por  expor métodos para acessar e criar uma tabela de cores, principalmente para formatos de pixel indexados.
/// </summary>
public ref class CarenWICPalette : public ICarenWICPalette
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICPalette).
	IWICPalette* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICPalette();
	
	~CarenWICPalette();

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


	//Métodos da interface(ICarenWICPalette)
public:
	/// <summary>
	/// Recupera o número de cores na tabela de cores. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Recebe o número de cores na tabela de cores.</param>
	virtual CarenResult GetColorCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtéem a matriz de cores fornecida com as cores da tabela de cores internas. A matriz de cores deve ser dimensionada de acordo com os resultados de retorno do GetColorCount. 
	/// </summary>
	/// <param name="Param_Quantidade">O tamanho da matriz (Param_Out_Cores).</param>
	/// <param name="Param_Out_Cores">Uma matriz que recebe as cores da paleta.</param>
	/// <param name="Param_Out_CoresReais">Retorna o tamanho real necessário para obter as cores da paleta.</param>
	virtual CarenResult GetColors(
	UInt32 Param_Quantidade,
	[Out] cli::array<UInt32>^% Param_Out_Cores,
	[Out] UInt32% Param_Out_CoresReais);

	/// <summary>
	/// Recupera o WICBitmapPaletteType que descreve a paleta. 
	/// WICBitmapPaletteCustom é usado para paletas inicializadas tanto do InitializeCustom quanto do InitializeFromBitmap. Não há distinção entre paletas otimizadas e personalizadas.
	/// </summary>
	/// <param name="Param_Out_PaletteType">Recebe o tipo de paleta do bimtap.</param>
	virtual CarenResult GetType([Out] CA_WICBitmapPaletteType% Param_Out_PaletteType);

	/// <summary>
	/// Indica se a paleta contém uma entrada não-opaca (ou seja, uma entrada com um alfa menor que 1).
	/// Vários formatos de imagem suportam alfa de diferentes maneiras. PNG tem suporte alfa completo, suportando entradas de paleta parcialmente transparentes. O GIF armazena cores 
	/// como 24bpp, sem alfa, mas permite que uma entrada de paleta seja especificada como totalmente transparente. Se uma paleta tiver várias entradas totalmente transparentes (0x00RRGGBB),
	///  o GIF usará a última como seu índice transparente.
	/// </summary>
	/// <param name="Param_Out_HasAlfa">Recebe TRUE se a paleta contiver uma cor transparente; caso contrário, FALSE.</param>
	virtual CarenResult HasAlpha([Out] Boolean% Param_Out_HasAlfa);

	/// <summary>
	/// Inicializa uma paleta para as entradas de cores personalizadas fornecidas. Se for necessária uma cor transparente, forneça-a como parte das entradas personalizadas. 
	/// Para adicionar um valor transparente à paleta, seu valor alfa deve ser 0 (0x00RRGGBB).
	/// A contagem de entradas é limitada a 256.
	/// </summary>
	/// <param name="Param_Cores">A matriz de cores.</param>
	/// <param name="Param_Quantidade">O número de cores em (Param_Cores).</param>
	virtual CarenResult InitializeCustom(
	cli::array<UInt32>^ Param_Cores,
	UInt32 Param_Quantidade);

	/// <summary>
	///  Inicializa uma paleta usando um valor otimizado computado com base no bitmap de referência.
	/// A paleta resultante contém o número especificado de cores que melhor representam as cores presentes no bitmap. O algoritmo opera no valor opaco de cor RGB de cada pixel 
	/// no bitmap de referência e, portanto, ignora quaisquer valores alfa. Se for necessária uma cor transparente, defina o parâmetro (Param_AdicionarCorTransparente) para TRUE 
	/// e uma cor menos otimizada será calculada, reduzindo a (Param_Quantidade), e uma entrada de cor totalmente transparente será adicionada.
	/// </summary>
	/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) que contém um ponteiro para a fonte do bitmap.</param>
	/// <param name="Param_Quantidade">O número de cores para inicializar a paleta com.</param>
	/// <param name="Param_AdicionarCorTransparente">Um valor para indicar se deve adicionar uma cor transparente.</param>
	virtual CarenResult InitializeFromBitmap(
	ICarenWICBitmapSource^ Param_FonteBitmap,
	UInt32 Param_Quantidade,
	Boolean Param_AdicionarCorTransparente);

	/// <summary>
	/// Inicialize a paleta com base em uma determinada paleta. 
	/// </summary>
	/// <param name="Param_Palette">Uma interface(ICarenWICPalette) que contém um ponteiro para paleta de origem.</param>
	virtual CarenResult InitializeFromPalette(ICarenWICPalette^ Param_Palette);

	/// <summary>
	/// Inicializa a paleta para uma das paletas pré-definidas especificadas pelo WICBitmapPaletteType e, opcionalmente, adiciona uma cor transparente. 
	/// Se uma cor transparente for adicionada a uma paleta, a paleta não será mais predefinida e é devolvida como WICBitmapPaletteTypeCustom. Para paletas com menos de 256 entradas, 
	/// a entrada transparente é adicionada ao final da paleta (ou seja, uma paleta de 16 cores torna-se uma paleta de 17 cores). Para paletas com 256 cores, a entrada transparente 
	/// da paleta substituirá a última entrada na paleta pré-definida.
	/// </summary>
	/// <param name="Param_PaletteType">O tipo de paleta pré-definida desejada.</param>
	/// <param name="Param_AdicionarCorTransparente">A cor opcional transparente para adicionar à paleta. Se não for necessária uma cor transparente, use 0. Ao inicializar para uma 
	/// paleta em escala de cinza ou preto e branco, defina este 
	/// parâmetro como FALSE.</param>
	virtual CarenResult InitializePredefined(
	CA_WICBitmapPaletteType Param_PaletteType,
	Boolean Param_AdicionarCorTransparente);

	/// <summary>
	/// Recupera um valor que descreve se a paleta é em preto e branco. Uma paleta é considerada em preto e branco apenas se contiver exatamente duas entradas, uma preta completa 
	/// (0xFF0000000) e uma branca completa (0xFFFFFFF).
	/// </summary>
	/// <param name="Param_Out_PretoBranco">Recebe um valor booleano que indica se a paleta é preto e branco. TRUE indica que a paleta é em preto e branco; caso contrário, FALSO.</param>
	virtual CarenResult IsBlackWhite([Out] Boolean% Param_Out_PretoBranco);

	/// <summary>
	/// Recupera um valor que descreve se uma paleta é escala de cinza. 
	/// Uma paleta é considerada escala de cinza somente se, para cada entrada, o valor alfa for 0xFF e os valores vermelho, verde e azul coincidirem.
	/// </summary>
	/// <param name="Param_Out_EscalaCinza">Recebe um valor booleano que indica se a paleta é escala de cinza. TRUE indica que a paleta é escala de cinza; caso contrário FALSO.</param>
	virtual CarenResult IsGrayscale([Out] Boolean% Param_Out_EscalaCinza);
};