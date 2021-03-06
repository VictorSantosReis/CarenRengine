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
#include "CarenD2D1Bitmap.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por pintar uma área com um bitmap.
/// </summary>
public ref class CarenD2D1BitmapBrush : public ICarenD2D1BitmapBrush
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1BitmapBrush).
	ID2D1BitmapBrush* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1BitmapBrush();

	~CarenD2D1BitmapBrush();


	//Conversões implicitas
public:
	static operator CarenD2D1BitmapBrush^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenD2D1BitmapBrush^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenD2D1BitmapBrush();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<ID2D1BitmapBrush*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenD2D1BitmapBrush::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenD2D1BitmapBrush)
public:
	/// <summary>
	/// Obtém a fonte bitmap que este pincel usa para pintar.
	/// </summary>
	/// <param name="Param_Out_Bitmap">Quando este método retorna, contém o endereço a um ponteiro para o bitmap com o qual este pincel pinta.</param>
	virtual CarenResult GetBitmap([Out] ICarenD2D1Bitmap^% Param_Out_Bitmap);

	/// <summary>
	/// Obtém o método pelo qual a escova inclina horizontalmente as áreas que se estendem além de seu bitmap.
	/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
	/// </summary>
	/// <param name="Param_Out_ExtendModeX">Retorna um valor que especifica como a escova horizontalmente ladrilhos(Tile) as áreas que se estendem além de seu bitmap.</param>
	virtual void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX);

	/// <summary>
	/// Obtém o método pelo qual a escova corta verticalmente as áreas que se estendem além de seu bitmap.
	/// Como todos os pincéis, o ICarenD2D1BitmapBrush define um plano infinito de conteúdo. Como os bitmaps são finitos, ele conta com um modo de extensão para determinar como o avião é preenchido horizontal e verticalmente.
	/// </summary>
	/// <param name="Param_Out_ExtendModeY">Retorna um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
	virtual void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY);

	/// <summary>
	/// Obtém o método de interpolação usado quando o bitmap da escova é dimensionado ou girado.
	/// </summary>
	/// <param name="Param_Out_InterpolationMode">Retorna o método de interpolação utilizado quando o bitmap da escova é dimensionado ou girado.</param>
	virtual void GetInterpolationMode([Out] CA_D2D1_BITMAP_INTERPOLATION_MODE% Param_Out_InterpolationMode);

	/// <summary>
	/// Especifica a fonte bitmap que este pincel usa para pintar.
	/// Este método especifica a fonte bitmap que este pincel usa para pintar. O bitmap não é redimensionado ou redimensionado automaticamente para se encaixar na geometria que preenche. 
	/// O bitmap permanece em seu tamanho nativo. Para redimensionar ou traduzir o bitmap, use o método ICarenD2D1Brush::SetTransform para aplicar uma transformação no pincel.
	/// O tamanho nativo de um bitmap é a largura e altura em pixels bitmap, dividido pelo DPI bitmap. Este tamanho nativo forma o Tile do pincel. Para ladrilar uma sub-região do bitmap, 
	/// você deve gerar um novo bitmap contendo esta sub-região e usar SetBitmap para aplicá-lo no Brush.
	/// </summary>
	/// <param name="Param_Bitmap">Retorna a fonte de bitmap usada pelo pincel.</param>
	virtual CarenResult SetBitmap(ICarenD2D1Bitmap^ Param_Bitmap);

	/// <summary>
	/// Especifica como o Brush inclina horizontalmente as áreas que se estendem além de seu bitmap.
	/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
	/// vertical(SetExtendModeY) para determinar como preencher a área restante.
	/// </summary>
	/// <param name="Param_ExtendModeX">Um valor que especifica como o pincel monitora horizontalmente as áreas que ultrapassam seu bitmap.</param>
	virtual void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ExtendModeX);

	/// <summary>
	/// Especifica como o Brush ladrilhou(Tiled) verticalmente as áreas que se estendem além de seu bitmap.
	/// Às vezes, o bitmap para um pincel bitmap não preenche completamente a área que está sendo pintada. Quando isso acontece, o Direct2D usa as configurações de modo horizontais(SetExtendModeX) e 
	/// vertical(SetExtendModeY) para determinar como preencher a área restante.
	/// </summary>
	/// <param name="Param_ExtendModeY">Um valor que especifica como o pincel inclina verticalmente as áreas que se estendem além de seu bitmap.</param>
	virtual void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ExtendModeY);

	/// <summary>
	/// Especifica o modo de interpolação usado quando o bitmap da escova é dimensionado ou girado.
	/// D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR representa a filtragem do vizinho mais próximo. Ele olha o pixel bitmap mais próximo do pixel de renderização atual e escolhe sua cor exata.
	/// D2D1_BITMAP_INTERPOLATION_MODE_LINEAR representa filtragem linear e interpola uma cor dos quatro pixels de bitmap mais próximos.
	/// O modo de interpolação de um bitmap também afeta traduções subpixel. Em uma tradução subpixel, a interpolação bilinear posiciona o bitmap mais precisamente às solicitações do aplicativo, mas desfoca o bitmap no processo.
	/// </summary>
	/// <param name="Param_InterpolationMode">O modo de interpolação usado quando o bitmap do Brush é dimensionado ou girado.</param>
	virtual void SetInterpolationMode(CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode);


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