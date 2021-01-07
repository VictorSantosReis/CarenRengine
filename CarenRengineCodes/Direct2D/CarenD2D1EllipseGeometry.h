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
/// (Concluido - Fase de Testes) - Classe responsável por representar uma elipse.
/// </summary>
public ref class CarenD2D1EllipseGeometry : public ICarenD2D1EllipseGeometry
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1EllipseGeometry).
	ID2D1EllipseGeometry* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1EllipseGeometry();

	~CarenD2D1EllipseGeometry();


	//Conversões implicitas
public:
	static operator CarenD2D1EllipseGeometry^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1EllipseGeometry^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1EllipseGeometry();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1EllipseGeometry*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
			System::Console::WriteLine(String::Concat(ICarenD2D1EllipseGeometry::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1EllipseGeometry)
public:
	/// <summary>
	/// Obtém a estrutura D2D1_ELLIPSE que descreve essa geometria de elipse. 
	/// </summary>
	/// <param name="Param_Out_Ellipse">Retrona uma estrutura (D2D1_ELLIPSE) que descreve o tamanho e a posição da elipse.</param>
	virtual void GetEllipse([Out] CA_D2D1_ELLIPSE^% Param_Out_Ellipse);



	//Métodos da interface(ICarenD2D1Geometry)
public:
	/// <summary>
	/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
	/// </summary>
	/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
	/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
	/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
	/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
	virtual CarenResult CombineWithGeometry(
		ICarenD2D1Geometry^ Param_GeometriaEntrada,
		CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
		CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
		float Param_FlatteningTolerance,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink);

	/// <summary>
	/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
	/// </summary>
	/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
	/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
	/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
	/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
	virtual CarenResult CombineWithGeometry(
		ICarenD2D1Geometry^ Param_GeometriaEntrada,
		CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
		CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink
	);

	/// <summary>
	/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada utilizando-se a tolerância de achatamento especificada. 
	/// Ao interpretar o valor da relação retornada, é importante lembrar que o membro D2D1_GEOMETRY_RELATION_IS_CONTAINED do tipo de enumeração D2D1_GEOMETRY_RELATION significa que essa geometria está 
	/// contida dentro da (Param_GeometriaEntrada), não que esta geometria contenha (Param_GeometriaEntrada).
	/// </summary>
	/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
	/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
	/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
	virtual CarenResult CompareWithGeometry(
		ICarenD2D1Geometry^ Param_GeometriaEntrada,
		CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
		float Param_FlatteningTolerance,
		[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao);

	/// <summary>
	/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada usando a tolerância de achatamento padrão. 
	/// </summary>
	/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
	/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
	/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
	virtual CarenResult CompareWithGeometry(
		ICarenD2D1Geometry^ Param_GeometriaEntrada,
		CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
		[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao);

	/// <summary>
	/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância especificada. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais
	/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
	virtual CarenResult ComputeArea(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		[Out] float% Param_Out_Area);

	/// <summary>
	/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância padrão. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
	/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
	virtual CarenResult ComputeArea(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] float% Param_Out_Area);

	/// <summary>
	/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
	/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
	virtual CarenResult ComputeLength(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		[Out] float% Param_Out_Length);

	/// <summary>
	/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
	/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
	virtual CarenResult ComputeLength(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] float% Param_Out_Length);

	/// <summary>
	/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada.
	/// </summary>
	/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
	/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
	/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
	/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
	virtual CarenResult ComputePointAtLength(
		float Param_Length,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
		CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector);

	/// <summary>
	/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
	/// </summary>
	/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
	/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
	/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
	/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
	virtual CarenResult ComputePointAtLength(
		float Param_Length,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
		CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector);

	/// <summary>
	/// Indica se a área preenchida pela geometria conteria o ponto especificado dada a tolerância de achatamento especificada. 
	/// </summary>
	/// <param name="Param_Point">O ponto para testar.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
	/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam o preenchimento por menos do 
	/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
	virtual CarenResult FillContainsPoint(
		CA_D2D1_POINT_2F^ Param_Point,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		[Out] Boolean% Param_Out_Contem);

	/// <summary>
	/// Indica se a área preenchida pela geometria conteria o ponto especificado. 
	/// </summary>
	/// <param name="Param_Point">O ponto para testar.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
	/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
	virtual CarenResult FillContainsPoint(
		CA_D2D1_POINT_2F^ Param_Point,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] Boolean% Param_Out_Contem);

	/// <summary>
	/// Recupera os limites da geometria. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria antes de calcular seus limites.</param>
	/// <param name="Param_Out_Bounds">Retorna os limites desta geometria. Se os limites estiverem vazios, este parâmetro será um recamto onde os Bounds.Left > Bounds.Right.</param>
	virtual CarenResult GetBounds(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

	/// <summary>
	/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
	/// </summary>
	/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
	/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
	/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
	/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
	virtual CarenResult GetWidenedBounds(
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

	/// <summary>
	/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
	/// </summary>
	/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
	/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
	/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
	/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
	virtual CarenResult GetWidenedBounds(
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] CA_D2D1_RECT_F^% Param_Out_Bounds);

	/// <summary>
	/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink. 
	/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
	/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
	/// para criar sindicatos entre várias geometrias simultaneamente.
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
	/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
	virtual CarenResult Outline(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink.
	/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
	/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
	/// para criar sindicatos entre várias geometrias simultaneamente.
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
	/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
	virtual CarenResult Outline(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) Curvas Cubicas Bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
	/// </summary>
	/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
	/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
	virtual CarenResult Simplify(
		CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) curvas búbicas bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
	/// </summary>
	/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
	/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
	virtual CarenResult Simplify(
		CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado.
	/// </summary>
	/// <param name="Param_Point">O ponto para testar a contenção.</param>
	/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
	/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
	/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam ao derrame por menos do
	/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
	virtual CarenResult StrokeContainsPoint(
		CA_D2D1_POINT_2F^ Param_Point,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		[Out] Boolean% Param_Out_Contem);

	/// <summary>
	/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado. 
	/// </summary>
	/// <param name="Param_Point">O ponto para testar a contenção.</param>
	/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
	/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
	/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
	virtual CarenResult StrokeContainsPoint(
		CA_D2D1_POINT_2F^ Param_Point,
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		[Out] Boolean% Param_Out_Contem);

	/// <summary>
	/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância especificada.
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
	/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
	virtual CarenResult Tessellate(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		ICarenD2D1TessellationSink^ Param_TelassellationSink);

	/// <summary>
	/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância padrão. 
	/// </summary>
	/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
	/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
	virtual CarenResult Tessellate(
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		ICarenD2D1TessellationSink^ Param_TelassellationSink);

	/// <summary>
	/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada. 
	/// </summary>
	/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
	/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
	/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
	/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
	/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
	virtual CarenResult Widen(
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
		CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
		float Param_FlatteningTolerance,
		ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink);

	/// <summary>
	/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
	/// </summary>
	/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
	/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
	/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
	/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
	virtual CarenResult Widen(
		float Param_StrokeWidth,
		ICarenD2D1StrokeStyle^ Param_StrokeStyle,
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