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
#include "CarenD2D1Image.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar um pincel baseado em um ICarenD2D1Image.
/// </summary>
public ref class CarenD2D1ImageBrush : public ICarenD2D1ImageBrush
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1ImageBrush).
	ID2D1ImageBrush* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1ImageBrush();

	~CarenD2D1ImageBrush();


	//Conversões implicitas
public:
	static operator CarenD2D1ImageBrush^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1ImageBrush^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1ImageBrush();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1ImageBrush*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenD2D1ImageBrush::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1ImageBrush)
public:
	/// <summary>
	/// Obtém o modo de extensão do pincel de imagem no eixo x. 
	/// </summary>
	/// <param name="Param_Out_ModeExtendidoX">Retorna o modo extendido no eixo X.</param>
	virtual void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoX);

	/// <summary>
	/// Obtém o modo de extensão do pincel de imagem no eixo y da imagem. 
	/// </summary>
	/// <param name="Param_Out_ModeExtendidoY">Retorna o modo extendido no eixo Y.</param>
	virtual void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoY);

	/// <summary>
	/// Obtém a imagem associada ao pincel de imagem. 
	/// </summary>
	/// <param name="Param_Out_Image">Quando este método retorna, contém o endereço de um ponteiro para a imagem associada a este pincel.</param>
	virtual CarenResult GetImage([Out] ICarenD2D1Image^% Param_Out_Image);

	/// <summary>
	/// Obtém o modo de interpolação do pincel de imagem.
	/// </summary>
	/// <param name="Param_Out_InterpolatonMode">Retorna o modo de interpolação.</param>
	virtual void GetInterpolationMode([Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolatonMode);

	/// <summary>
	/// Obtém o retângulo que será usado como os limites da imagem quando desenhado como um pincel de imagem. 
	/// </summary>
	/// <param name="Param_Out_RetanguloOrigem">Quando este método retorna, contém a estrutura do retângulo de origem de saída.</param>
	virtual void GetSourceRectangle([Out] CA_D2D1_RECT_F^% Param_Out_RetanguloOrigem);

	/// <summary>
	/// Define como o conteúdo dentro do retângulo de origem no Brush de imagem será estendido no eixo X. 
	/// </summary>
	/// <param name="Param_ModeExtendidoX">O modo de extensão no eixo X da imagem.</param>
	virtual void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ModeExtendidoX);

	/// <summary>
	/// Define o modo de extensão no eixo Y. 
	/// </summary>
	/// <param name="Param_ModeExtendidoY">O modo de extensão no eixo Y da imagem.</param>
	virtual void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ModeExtendidoY);

	/// <summary>
	/// Define a imagem associada à escova de imagem fornecida. 
	/// </summary>
	/// <param name="Param_Image">A imagem a ser associada com o pincel de imagem.</param>
	virtual CarenResult SetImage(ICarenD2D1Image^ Param_Image);

	/// <summary>
	/// Define o modo de interpolação para o pincel de imagem. 
	/// </summary>
	/// <param name="Param_InterpolationMode">Define como o conteúdo da imagem será interpolado para lidar com a transformação do pincel.</param>
	virtual void SetInterpolationMode(CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode);

	/// <summary>
	/// Define o retângulo de origem na escova de imagem. 
	/// </summary>
	/// <param name="Param_OrigemRetangulo">O retângulo de origem que define a parte da imagem para ladrilho(Tile).</param>
	virtual void SetSourceRectangle(CA_D2D1_RECT_F^ Param_OrigemRetangulo);


	//Métodos da interface(ICarenD2D1Brush)
public:
	/// <summary>
	/// Obtém o grau de opacidade deste pincel.
	/// </summary>
	/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
	/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
	virtual void GetOpacity([Out] float% Param_Out_Opacidade);

	/// <summary>
	/// A transformação é aplicada a este pincel.
	/// </summary>
	/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
	virtual void GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix);

	/// <summary>
	/// Define o grau de opacidade deste pincel.
	/// </summary>
	/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
	/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
	virtual void SetOpacity(float Param_Opacidade);

	/// <summary>
	/// Define a transformação aplicada ao pincel.
	/// </summary>
	/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
	virtual void SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};