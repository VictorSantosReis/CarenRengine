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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar uma coleção de objetos D2D1_GRADIENT_STOP para Brushs gradientes lineares e radiais.
/// </summary>
public ref class CarenD2D1GradientStopCollection1 : public ICarenD2D1GradientStopCollection1
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1GradientStopCollection1).
	ID2D1GradientStopCollection1* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenD2D1GradientStopCollection1();


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
	/// <param name="Param_Out_CarenD2D1GradientStopCollection1">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1GradientStopCollection1^% Param_Out_CarenD2D1GradientStopCollection1)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1GradientStopCollection1 = gcnew CarenD2D1GradientStopCollection1();

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


	//Métodos da interface(ICarenD2D1GradientStopCollection1)
public:
	/// <summary>
	/// Obtém a precisão do Buffer de gradiente. 
	/// Se esse objeto foi criado usando ICarenD2D1RenderTarget::CreateGradientStopCollection, este método retorna D2D1_BUFFER_PRECISION_8BPC_UNORM.
	/// </summary>
	/// <param name="Param_Out_PrecisaoBuffer">Retorna o Buffer de precisão do Gradiente.</param>
	virtual void GetBufferPrecision([Out] CA_D2D1_BUFFER_PRECISION% Param_Out_PrecisaoBuffer);

	/// <summary>
	/// Recupera o modo de interpolação de cores que a coleção de parada de gradiente usa.
	/// </summary>
	/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação de cores.</param>
	virtual void GetColorInterpolationMode([Out] CA_D2D1_COLOR_INTERPOLATION_MODE% Param_Out_InterpolationMode);

	/// <summary>
	/// Copia as paradas de gradiente da coleção para a memória. 
	/// </summary>
	/// <param name="Param_Out_ArrayGradientStop">Retorna uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP.</param>
	/// <param name="Param_QuantidadeGradientes">O número de gradientes para copiar. Se for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes sao omitidas. 
	/// Se Param_QuantidadeGradientes for maior do que o número de paradas gradientes na coleção, as paradas de gradiente extra são definidas como NULO.</param>
	virtual void GetGradientStops1(
	[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
	UInt32 Param_QuantidadeGradientes);

	/// <summary>
	/// Obtém o espaço de cores após a interpolação. 
	/// </summary>
	/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
	virtual void GetPostInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);

	/// <summary>
	/// Obtém o espaço de cores das cores de entrada, bem como o espaço em que as paradas gradientes são interpoladas. 
	/// </summary>
	/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
	virtual void GetPreInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor);


	//Métodos da interface(ICarenD2D1GradientStopCollection)
public:
	/// <summary>
	/// Indica o espaço gama em que as paradas gradientes são interpoladas.
	/// </summary>
	/// <param name="Param_Out_GammaSpace">Retorna o espaço gama em que as paradas gradientes são interpoladas.</param>
	virtual void GetColorInterpolationGamma([Out] CA_D2D1_GAMMA% Param_Out_GammaSpace);

	/// <summary>
	/// Indica o comportamento do gradiente fora da faixa de gradiente normalizada. 
	/// </summary>
	/// <param name="Param_Out_ExtendMode">Retorna o comportamento do gradiente fora da faixa de gradiente normalizada.</param>
	virtual void GetExtendMode([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendMode);

	/// <summary>
	/// Recupera o número de paradas gradientes na coleção. 
	/// </summary>
	/// <param name="Param_Out_CountGradientes">Retorna o número de gradientes para na coleção.</param>
	virtual void GetGradientStopCount([Out] UInt32% Param_Out_CountGradientes);

	/// <summary>
	/// Copia as paradas gradientes da coleção em uma matriz de estruturas D2D1_GRADIENT_STOP. 
	/// </summary>
	/// <param name="Param_Out_ArrayGradientStop">Uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP. Quando este método retorna, a matriz contém cópias do gradiente da coleção de parada.</param>
	/// <param name="Param_QuantidadeGradientes">Um valor indicando o número de paradas gradientes para copiar. Se o valor for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes 
	/// são omitidas. Se o valor for maior do que o número de paradas de gradiente na coleção, as paradas de gradiente extra são definidas como NULO. Para obter o número de paradas gradientes na coleção, use o método 
	/// GetGradientStopCount.</param>
	virtual void GetGradientStops(
		[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
		UInt32 Param_QuantidadeGradientes);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};