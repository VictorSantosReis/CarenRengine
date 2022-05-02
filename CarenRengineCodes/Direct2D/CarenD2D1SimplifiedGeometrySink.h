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

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por descrever um caminho geométrico que não contém curvas ou arcos quadráticos de Bézier.
/// </summary>
public ref class CarenD2D1SimplifiedGeometrySink : public ICarenD2D1SimplifiedGeometrySink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SimplifiedGeometrySink).
	ID2D1SimplifiedGeometrySink* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SimplifiedGeometrySink();

	~CarenD2D1SimplifiedGeometrySink();


	//Conversões implicitas
public:
	static operator CarenD2D1SimplifiedGeometrySink^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1SimplifiedGeometrySink^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1SimplifiedGeometrySink();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1SimplifiedGeometrySink*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;


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
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenD2D1SimplifiedGeometrySink::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenD2D1SimplifiedGeometrySink)
public:
	/// <summary>
	/// Cria uma sequência de curvas Cubicas de Bezier e as adiciona ao Geometry Sink.
	/// </summary>
	/// <param name="Param_ArrayBeziers">Uma matriz de segmentos Bezier que descreve as curvas bezier para criar. Uma curva é extraída do ponto atual do Geometry Sink (o ponto final do último segmento 
	/// desenhado ou o local especificado pela BeginFigure) até o ponto final do primeiro segmento Bezier na matriz. se a matriz contiver segmentos bezier adicionais, cada segmento Bezier subsequente usa
	/// o ponto final do segmento Bezier anterior como seu ponto de partida.</param>
	/// <param name="Param_QuantidadeBeziers">O número de segmentos Bezier na matriz (Param_ArrayBeziers).</param>
	virtual void AddBeziers(
	cli::array<CA_D2D1_BEZIER_SEGMENT^>^ Param_ArrayBeziers,
	UInt32 Param_QuantidadeBeziers);

	/// <summary>
	/// Cria uma sequência de linhas usando os pontos especificados e adiciona-os ao Geometry Sink. 
	/// </summary>
	/// <param name="Param_ArrayPoints">uma matriz de um ou mais pontos que descrevem as linhas a desenhar. Uma linha é desenhada do ponto atual do Geometry Sink (o ponto final do último segmento desenhado 
	/// ou o local especificado pela BeginFigure) até o primeiro ponto da matriz. se a matriz contiver pontos adicionais, uma linha é desenhada do primeiro ponto para o segundo ponto na matriz, do segundo ponto 
	/// ao terceiro ponto, e assim por diante.</param>
	/// <param name="Param_QuantidadePontos">O número de pontos na matriz (Param_ArrayPoints).</param>
	virtual void AddLines(
	cli::array<CA_D2D1_POINT_2F^>^ Param_ArrayPoints,
	UInt32 Param_QuantidadePontos);

	/// <summary>
	/// Inicia uma nova figura no ponto especificado. 
	/// Se esse método for chamado enquanto uma figura estiver em andamento, a interface será invalidada e todos os métodos futuros falharão.
	/// </summary>
	/// <param name="Param_StartPoint">O ponto para começar a nova figura.</param>
	/// <param name="Param_InicioFigura">Se a nova figura deve ser oca ou preenchida.</param>
	virtual void BeginFigure(
	CA_D2D1_POINT_2F^ Param_StartPoint,
	CA_D2D1_FIGURE_BEGIN Param_InicioFigura);

	/// <summary>
	/// Fecha o Geometry Sink, indica se está em estado de erro e redefine o estado de erro do Sink.
	/// Não feche o Geometry Sink enquanto uma figura ainda está em andamento; fazendo isso coloca o Geometry Sink em um estado de erro. Para que a operação seja bem sucedida, deve haver uma chamada EndFigure 
	/// para cada chamada para BeginFigure.
	/// </summary>
	virtual CarenResult Close();

	/// <summary>
	/// Termina a figura atual; opcionalmente, fecha-o.
	/// Chamar este método sem uma chamada correspondente ao BeginFigure coloca o Geometry Sink em um estado de erro; chamadas subsequentes são ignoradas, e a falha geral será devolvida quando o método 
	/// Close for chamado.
	/// </summary>
	/// <param name="Param_FinalFigura">Um valor que indica se o valor atual está fechado. Se o valor for fechado, uma linha será traçada entre o ponto atual e o ponto de partida especificado 
	/// pela BeginFigure.</param>
	virtual void EndFigure(CA_D2D1_FIGURE_END Param_FinalFigura);

	/// <summary>
	/// Especifica o método usado para determinar quais pontos estão dentro da geometria descrita por esta Geometry Sink e quais pontos estão fora. 
	/// O modo de preenchimento é padrão para D2D1_FILL_MODE_ALTERNATE. Para definir o modo de preenchimento, ligue para SetFillMode antes da primeira chamada para BeginFigure. Não fazer vai colocar o 
	/// Geometry Sink em um estado de erro.
	/// </summary>
	/// <param name="Param_ModoPreencher">O método utilizado para determinar se um determinado ponto faz parte da geometria.</param>
	virtual void SetFillMode(CA_D2D1_FILL_MODE Param_ModoPreencher);

	/// <summary>
	/// Especifica as opções de traçado e de adesão a serem aplicadas a novos segmentos adicionados ao Geometry Sink. 
	/// Após a chamada esse método, as bandeiras do segmento especificadas são aplicadas a cada segmento posteriormente adicionadas ao Sink. As bandeiras do segmento são aplicadas a cada segmento adicional até que 
	/// este método seja chamado novamente e um conjunto diferente de bandeiras do segmento seja especificado.
	/// </summary>
	/// <param name="Param_FlagsVertex">As opções do Stroke e o Join a serem aplicadas a novos segmentos adicionados ao Geometry Sink.</param>
	virtual void SetSegmentFlags(CA_D2D1_PATH_SEGMENT Param_FlagsVertex);
};