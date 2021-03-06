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
/// (Concluido - Fase de Testes) - Classe responsável por descrever os Caps, limite de Miter, Line Join e informações de traço para um Stroke.
/// </summary>
public ref class CarenD2D1StrokeStyle1 : public ICarenD2D1StrokeStyle1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1StrokeStyle1).
	ID2D1StrokeStyle1* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1StrokeStyle1();

	~CarenD2D1StrokeStyle1();


	//Conversões implicitas
public:
	static operator CarenD2D1StrokeStyle1^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1StrokeStyle1^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1StrokeStyle1();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1StrokeStyle1*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenD2D1StrokeStyle1::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1StrokeStyle1)
public:
	/// <summary>
	/// Recebe o tipo de transformação do Stroke.
	/// </summary>
	/// <param name="Param_Out_StrokeTransformType">Retorna o tipo de transformação de traçado.</param>
	virtual void GetStrokeTransformType(
	[Out] CA_D2D1_STROKE_TRANSFORM_TYPE% Param_Out_StrokeTransformType);


	//Métodos da interface(ICarenD2D1StrokeStyle)
public:
	/// <summary>
	/// Obtém um valor que especifica como as extremidades de cada traço são desenhadas.
	/// </summary>
	/// <param name="Param_Out_EndDashStyle">Retorna um valor que especifica como as extremidades de cada traço são desenhadas.</param>
	virtual void GetDashCap([Out] CA_D2D1_CAP_STYLE% Param_Out_EndDashStyle);

	/// <summary>
	/// Copia o padrão do painel para a matriz especificada. 
	/// Os traços(Dashes) são especificados em unidades que são um múltiplo da largura do traçado, com membros subsequentes da matriz indicando os traços e lacunas entre traços: a primeira entrada indica 
	/// um traço preenchido, o segundo uma lacuna, e assim por diante.
	/// </summary>
	/// <param name="Param_Out_ArrayDashes">Retorna uma matriz que receberá o padrão de traço. A matriz deve ser capaz de conter pelo menos tantos elementos quanto especificado pelo Param_Quantidade.</param>
	/// <param name="Param_Quantidade">O número de traços para copiar. Se esse valor for menor do que o número de traços na matriz de traços de Stroke Style, os traços retornados são truncados para Param_Quantidade. 
	/// Se esse valor for maior do que o número de traços na matriz de Stroke Styles, os traços extras são definidos como 0.0f. Para obter o número real de traços na matriz de traços do estilo de traçado, 
	/// use o método GetDashesCount.</param>
	virtual void GetDashes(
		[Out] cli::array<float>^% Param_Out_ArrayDashes,
		UInt32 Param_Quantidade);

	/// <summary>
	/// Recupera o número de entradas na matriz de traços. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de entradas na matriz de traços se o traçado for tracejado; caso contrário, 0.</param>
	virtual void GetDashesCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Recupera um valor que especifica até que ponto na sequência do painel o traçado começará. 
	/// </summary>
	/// <param name="Param_Out_Offset">Recupera um valor que especifica até que ponto na sequência do traço o traçado começará.</param>
	virtual void GetDashOffset([Out] float% Param_Out_Offset);

	/// <summary>
	/// Obtém um valor que descreve o padrão de traço do traçado. 
	/// </summary>
	/// <param name="Param_Out_DashStyleUsado">Recupera um valor que descreve o padrão de traço predefinido usado ou D2D1_DASH_STYLE_CUSTOM de (CA_D2D1_DASH_STYLE) se um estilo de painel personalizado for usado.</param>
	virtual void GetDashStyle([Out] CA_D2D1_DASH_STYLE% Param_Out_DashStyleUsado);

	/// <summary>
	/// Recupera o tipo de forma usada no final de um curso. 
	/// </summary>
	/// <param name="Param_Out_TipoEndShape">Retorna o tipo de forma usada no final de um curso.</param>
	virtual void GetEndCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoEndShape);

	/// <summary>
	/// Recupera o tipo de articulação usada nos vértices do contorno de uma forma. 
	/// </summary>
	/// <param name="Param_Out_TipoJoint">Recupera um valor que especifica o tipo de articulação usada nos vértices do contorno de uma forma.</param>
	virtual void GetLineJoin([Out] CA_D2D1_LINE_JOIN% Param_Out_TipoJoint);

	/// <summary>
	/// Recupera o limite na razão do comprimento do miter para metade da espessura do traçado. 
	/// </summary>
	/// <param name="Param_Out_Limite">Recupera um número positivo maior ou igual a 1.0f que descreve o limite na razão do comprimento do miter para metade da espessura do traçado.</param>
	virtual void GetMiterLimit([Out] float% Param_Out_Limite);

	/// <summary>
	/// Recupera o tipo de forma usada no início de um Stroke. 
	/// </summary>
	/// <param name="Param_Out_TipoStartShape">Retorna o tipo de forma usada no início de um Stroke.</param>
	virtual void GetStartCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoStartShape);



	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};