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
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um único Stroke contínuo de tinta de largura variável, conforme definido por uma série de segmentos e larguras de Bezier.
/// </summary>
public ref class CarenD2D1Ink : public ICarenD2D1Ink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Ink).
	ID2D1Ink* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1Ink();

	~CarenD2D1Ink();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenD2D1Ink">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1Ink^% Param_Out_CarenD2D1Ink)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1Ink = gcnew CarenD2D1Ink();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
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


	//Métodos da interface(ICarenD2D1Ink)
public:
	/// <summary>
	/// Adiciona os segmentos dado ao final deste objeto de tinta. 
	/// </summary>
	/// <param name="Param_Segments">Uma matriz de segmentos a serem adicionados a este objeto de tinta.</param>
	/// <param name="Param_Quantidade">O número de segmentos a serem adicionados a este objeto de tinta.</param>
	virtual CarenResult AddSegments(
	cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^ Param_Segments,
	UInt32 Param_Quantidade);

	/// <summary>
	/// Recupere os limites da geometria, com uma transformação aplicada opcional. 
	/// </summary>
	/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação dos limites deste objeto de tinta.</param>
	/// <param name="Param_WorldTransform">A Wolrd Transform para ser usado na determinação dos limites deste objeto de tinta.</param>
	/// <param name="Param_Out_Bounds">Retorna os limites deste objeto de tinta.</param>
	virtual CarenResult GetBounds(
	ICarenD2D1InkStyle^ Param_InkStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

	/// <summary>
	/// Retorna o número de segmentos neste objeto de tinta. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de segmentos neste objeto de tinta.</param>
	virtual void GetSegmentCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Recupera o subconjunto especificado de segmentos armazenados neste objeto de tinta. 
	/// </summary>
	/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser recuperado.</param>
	/// <param name="Param_Out_Segments">Retorna uma matriz de segmentos recuperados.</param>
	/// <param name="Param_Quantidade">O número de segmentos para recuperar. Observe que o (Param_Quantidade) deve ser menor ou igual ao número de segmentos no objeto de tinta menos (Param_StartSegments).</param>
	virtual CarenResult GetSegments(
	UInt32 Param_StartSegments,
	[Out] cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Out_Segments,
	UInt32 Param_Quantidade);

	/// <summary>
	/// Recupera o ponto de partida para este objeto de tinta. 
	/// </summary>
	/// <param name="Param_Out_Point">Retorna o ponto de partida para este objeto de tinta.</param>
	virtual void GetStartPoint([Out] CA_D2D1_INK_POINT^% Param_Out_Point);

	/// <summary>
	/// Remove o número dado de segmentos da extremidade deste objeto de tinta. 
	/// </summary>
	/// <param name="Param_QuantidadeSegments">O número de segmentos a serem removidos do final deste objeto de tinta. Observe que o (Param_QuantidadeSegments) deve ser menor ou igual ao número 
	/// de segmentos no objeto de tinta.</param>
	virtual CarenResult RemoveSegmentsAtEnd(UInt32 Param_QuantidadeSegments);

	/// <summary>
	/// Atualiza o último segmento neste objeto de tinta com novos pontos de controle. 
	/// </summary>
	/// <param name="Param_Segment">Uma estrutura que contém os dados do segmento com os quais substituir o último segmento deste objeto de tinta. Observe que se não houver atualmente segmentos 
	/// no objeto de tinta, o SetSegmentsAtEnd retornará um erro.</param>
	virtual CarenResult SetSegmentAtEnd(CA_D2D1_INK_BEZIER_SEGMENT^ Param_Segment);

	/// <summary>
	/// Atualiza os segmentos especificados neste objeto de tinta com novos pontos de controle. 
	/// </summary>
	/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser atualizado.</param>
	/// <param name="Param_Segments">Uma matriz com os dados do segmento a ser usado na atualização.</param>
	/// <param name="Param_Quantidade">O número de segmentos neste objeto de tinta que será atualizado com novos dados. Observe que o segmentsCount deve ser menor ou igual ao número de segmentos 
	/// no objeto de tinta menos (Param_StartSegments).</param>
	virtual CarenResult SetSegments(
	UInt32 Param_StartSegments,
	cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Segments,
	UInt32 Param_Quantidade);

	/// <summary>
	/// Define o ponto de partida para este objeto de tinta. Isso determina onde este objeto de tinta começará a renderizar.
	/// </summary>
	/// <param name="Param_StartPoint">O novo ponto de partida para este objeto de tinta.</param>
	virtual void SetStartPoint(CA_D2D1_INK_POINT^ Param_StartPoint);

	/// <summary>
	/// Recupera uma representação geométrica deste objeto de tinta. 
	/// </summary>
	/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
	/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica.</param>
	/// <param name="Param_FlatteningTolerance">O Flattening Tolerance a ser usada na determinação da representação geométrica.</param>
	/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
	virtual CarenResult StreamAsGeometry(
	ICarenD2D1InkStyle^ Param_InkStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Recupera uma representação geométrica deste objeto de tinta. 
	/// </summary>
	/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
	/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica</param>
	/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
	virtual CarenResult StreamAsGeometry(
	ICarenD2D1InkStyle^ Param_InkStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};