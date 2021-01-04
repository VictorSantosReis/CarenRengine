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
#include "../SDK_Direct2D.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um único grupo de sprites com suas propriedades de desenho associadas.
/// </summary>
public ref class CarenD2D1SpriteBatch : public ICarenD2D1SpriteBatch
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SpriteBatch).
	ID2D1SpriteBatch* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SpriteBatch();

	~CarenD2D1SpriteBatch();


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


	//Métodos da interface(ICarenD2D1SpriteBatch)
public:
	/// <summary>
	/// Adiciona os sprites dado ao final deste lote sprite.
	/// No Direct2D, um sprite é definido por quatro propriedades: um retângulo de destino, um retângulo de origem, uma cor e uma transformação. Os retângulos de destino são obrigatórios, mas as demais 
	/// propriedades são opcionais.
	/// Sempre omitir ou passar um valor nulo para propriedades que você não deseja usar. Isso permite que o Direct2D evite armazenar valores para essas propriedades e pule totalmente seu manuseio, o 
	/// que melhora a velocidade de desenho.
	/// </summary>
	/// <param name="Param_QuantidadeSprites">O número de sprites a serem adicionados. Isso determina quantos passos em cada matriz direct2D será lido.</param>
	/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
	/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
	/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos 
	/// os sprites adicionados.</param>
	/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
	/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não mudará
	/// a cor de nenhum dos sprites adicionados.</param>
	/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que sejam
	/// atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites adicionados.</param>
	/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
	/// será usado para cada sprite adicionado.</param>
	/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
	/// de origem será usado para cada sprite adicionado.</param>
	/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
	/// adicionado.</param>
	/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
	/// será usada para cada sprite adicionado.</param>
	virtual CarenResult AddSprites(
	UInt32 Param_QuantidadeSprites,
	cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
	cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
	cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
	cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
	UInt32 Param_DestinationRectanglesStride,
	UInt32 Param_SourceRectanglesStride,
	UInt32 Param_ColorsStride,
	UInt32 Param_TransformStride);

	/// <summary>
	/// Remove todos os sprites deste lote de sprite. 
	/// </summary>
	virtual void Clear();

	/// <summary>
	/// Recupera o número de sprites neste lote sprite. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de sprites neste lote de sprites.</param>
	virtual void GetSpriteCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Recupera o subconjunto especificado de sprites deste lote sprite. Para obter o melhor desempenho, use NULL para propriedades que você não precisa recuperar. 
	/// </summary>
	/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para recuperar.</param>
	/// <param name="Param_QuantidadeSprites">O número de sprites para recuperar.</param>
	/// <param name="Param_Ref_RetangulosDestino">Retorna uma matriz contendo os retângulos de destino para os sprites recuperados.</param>
	/// <param name="Param_Ref_RetangulosOrigem">Retorna uma matriz contendo os retângulos de origem para os sprites recuperados. O InfiniteRectU é devolvido para quaisquer sprites que não foram atribuídos 
	/// a um retângulo de origem.</param>
	/// <param name="Param_Ref_Cores">Retorna uma matriz contendo as cores a serem aplicadas aos sprites recuperados. A cor {1.0f, 1.0f, 1.0f, 1.0f} é devolvida para quaisquer sprites que não foram 
	/// atribuídos uma cor.</param>
	/// <param name="Param_Ref_Transform">Retorna uma matriz contendo as transformações a serem aplicadas aos sprites recuperados. A matriz de identidade é devolvida para quaisquer sprites que não 
	/// foram atribuídos uma transformação.</param>
	virtual CarenResult GetSprites(
	UInt32 Param_StartIndex,
	UInt32 Param_QuantidadeSprites,
	cli::array<CA_D2D1_RECT_F^>^% Param_Ref_RetangulosDestino,
	cli::array<CA_D2D1_RECT_U^>^% Param_Ref_RetangulosOrigem,
	cli::array<CA_D2D1_COLOR_F^>^% Param_Ref_Cores,
	cli::array<CA_D2D1_MATRIX_3X2_F^>^% Param_Ref_Transform);

	/// <summary>
	/// Atualiza as propriedades dos sprites especificados neste lote sprite. Fornecer um valor nulo para qualquer propriedade deixará essa propriedade não modificada para esse valor.
	/// </summary>
	/// <param name="Param_StartIndex">O índice do primeiro sprite neste lote sprite para atualização.</param>
	/// <param name="Param_QuantidadeSprites">O número de sprites para atualizar com novas propriedades. Isso determina quantos passos em cada matriz direct2D será lido.</param>
	/// <param name="Param_RetangulosDestino">Uma matriz contendo os retângulos de destino especificando onde desenhar os sprites no contexto do dispositivo de destino.</param>
	/// <param name="Param_RetangulosOrigem">Uma matriz contendo os retângulos de origem especificando as regiões do bitmap de origem para desenhar como sprites. O Direct2D usará todo o bitmap de origem 
	/// para sprites que recebem um valor nulo ou o InfiniteRectU. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D usará todo o bitmap de origem para todos os 
	/// sprites atualizados.</param>
	/// <param name="Param_Cores">Uma matriz contendo as cores para aplicar a cada sprite. A cor de saída é o resultado da multiplicação em termos de componentes da cor bitmap de origem e da cor fornecida. 
	/// A cor da saída não está presa. O Direct2D não mudará a cor dos sprites que recebem um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não 
	/// alterará a cor de nenhum dos sprites atualizados.</param>
	/// <param name="Param_Transform">Uma matriz contendo as transformações para aplicar ao retângulo de destino de cada sprite. O Direct2D não transformará o retângulo de destino de quaisquer sprites que 
	/// sejam atribuídos a um valor nulo. Se este parâmetro for omitido inteiramente ou definido para um valor nulo, então o Direct2D não transformará o retângulo de destino de nenhum dos sprites atualizados.</param>
	/// <param name="Param_DestinationRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz destinationRectangles. Se você fornecer um passo de 0, então o mesmo retângulo de destino 
	/// será usado para cada sprite atualizado.</param>
	/// <param name="Param_SourceRectanglesStride">Especifica a distância, em bytes, entre cada retângulo na matriz sourceRectangles (se essa matriz for dada). Se você fornecer um passo de 0, então o mesmo retângulo
	/// de origem será usado para cada sprite atualizado.</param>
	/// <param name="Param_ColorsStride">Especifica a distância, em bytes, entre cada cor na matriz de cores (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma cor será usada para cada sprite 
	/// atualizado.</param>
	/// <param name="Param_TransformStride">Especifica a distância, em bytes, entre cada transformação na matriz de transformações (se essa matriz for dada). Se você fornecer um passo de 0, então a mesma transformação
	/// será usada para cada sprite atualizado.</param>
	virtual CarenResult SetSprites(
	UInt32 Param_StartIndex,
	UInt32 Param_QuantidadeSprites,
	cli::array<CA_D2D1_RECT_F^>^ Param_RetangulosDestino,
	cli::array<CA_D2D1_RECT_U^>^ Param_RetangulosOrigem,
	cli::array<CA_D2D1_COLOR_F^>^ Param_Cores,
	cli::array<CA_D2D1_MATRIX_3X2_F^>^ Param_Transform,
	UInt32 Param_DestinationRectanglesStride,
	UInt32 Param_SourceRectanglesStride,
	UInt32 Param_ColorsStride,
	UInt32 Param_TransformStride);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};