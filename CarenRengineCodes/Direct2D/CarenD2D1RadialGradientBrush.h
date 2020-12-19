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
#include "CarenD2D1GradientStopCollection.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por pintar uma área com um gradiente radial.
/// </summary>
public ref class CarenD2D1RadialGradientBrush : public ICarenD2D1RadialGradientBrush
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1RadialGradientBrush).
	ID2D1RadialGradientBrush* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenD2D1RadialGradientBrush();


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
	/// <param name="Param_Out_CarenD2D1RadialGradientBrush">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1RadialGradientBrush^% Param_Out_CarenD2D1RadialGradientBrush)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1RadialGradientBrush = gcnew CarenD2D1RadialGradientBrush();

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


	//Métodos da interface(ICarenD2D1RadialGradientBrush)
public:
	/// <summary>
	/// Recupera o centro da elipse gradiente.
	/// </summary>
	/// <param name="Param_Out_Center">Retorna o centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
	virtual void GetCenter([Out] CA_D2D1_POINT_2F^% Param_Out_Center);

	/// <summary>
	/// Recupera o deslocamento da origem gradiente em relação ao centro da elipse gradiente. 
	/// </summary>
	/// <param name="Param_Out_GradientOriginOffset">Retorna A compensação da origem gradiente do centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
	virtual void GetGradientOriginOffset([Out] CA_D2D1_POINT_2F^% Param_Out_GradientOriginOffset);

	/// <summary>
	/// Recupera a ICarenD2D1GradientStopCollection associada a este objeto do Brush de gradiente radial. 
	/// </summary>
	/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection associado a este objeto de pincel gradiente linear. Este parâmetro é passado unnitializado.</param>
	virtual CarenResult GetGradientStopCollection(
	[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection);

	/// <summary>
	/// Recupera o raio X da elipse gradiente. 
	/// </summary>
	/// <param name="Param_Out_RadiusX">Retorna raio X da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
	virtual void GetRadiusX([Out] float% Param_Out_RadiusX);

	/// <summary>
	/// Recupera o raio Y da elipse gradiente. 
	/// </summary>
	/// <param name="Param_Out_RadiusY">Retorna raio Y da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
	virtual void GetRadiusY([Out] float% Param_Out_RadiusY);

	/// <summary>
	/// Especifica o centro da elipse gradiente no espaço de coordenadas do Brush. 
	/// </summary>
	/// <param name="Param_Center">O centro da elipse gradiente, no espaço de coordenadas do pincel.</param>
	virtual void SetCenter(CA_D2D1_POINT_2F^ Param_Center);

	/// <summary>
	/// Especifica a compensação da origem gradiente em relação ao centro da elipse gradiente. 
	/// </summary>
	/// <param name="Param_GradientOriginOffset">A compensação da origem gradiente do centro da elipse gradiente.</param>
	virtual void SetGradientOriginOffset(CA_D2D1_POINT_2F^ Param_GradientOriginOffset);

	/// <summary>
	/// Especifica o raio X da elipse gradiente, no espaço de coordenadas do Brush. 
	/// </summary>
	/// <param name="Param_RadiusX">O raio X da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
	virtual void SetRadiusX(float Param_RadiusX);

	/// <summary>
	/// Especifica o raio Y da elipse gradiente, no espaço de coordenadas da escova. 
	/// </summary>
	/// <param name="Param_RadiusY">O raio Y da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
	virtual void SetRadiusY(float Param_RadiusY);


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