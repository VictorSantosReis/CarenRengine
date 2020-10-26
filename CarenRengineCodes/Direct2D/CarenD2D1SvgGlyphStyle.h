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
#include "../FunctionClass/GlobalFuncs.h"
#include "CarenD2D1Brush.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por fornecer os valores para preenchimento de contexto, contexto-curso e valor de contexto que são usados ao renderizar glifos SVG.
/// </summary>
public ref class CarenD2D1SvgGlyphStyle : public ICarenD2D1SvgGlyphStyle
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SvgGlyphStyle).
	ID2D1SvgGlyphStyle* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	CarenD2D1SvgGlyphStyle();
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	~CarenD2D1SvgGlyphStyle();

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


	//Métodos da interface(ICarenD2D1SvgGlyphStyle)
public:
	/// <summary>
	/// Retorna os parâmetros de preenchimento solicitados. 
	/// </summary>
	/// <param name="Param_Out_Brush">Retorna o Brush que desve como a área é pintada.</param>
	virtual void GetFill([Out] ICarenD2D1Brush^% Param_Out_Brush);

	/// <summary>
	/// Retorna os parâmetros de curso solicitados. Quaisquer parâmetros que não sejam nulos receberão o valor do parâmetro solicitado.
	/// </summary>
	/// <param name="Param_Out_Brush">Retorna o Brush que indica como o Stroke é pintado.</param>
	/// <param name="Param_Out_StrokeWidth">O "valor de contexto" para a propriedade 'largura de traçado'.</param>
	/// <param name="Param_Out_Dashes">O "valor de contexto" para a propriedade 'stroke-dasharray'.</param>
	/// <param name="Param_QuantidadeDashes">O número de Dasges na matriz (Param_Out_Dashes).</param>
	/// <param name="Param_Out_DashOffset">O "valor de contexto" para a propriedade 'stroke-dashoffset'.</param>
	virtual void GetStroke(
	[Out] ICarenD2D1Brush^% Param_Out_Brush,
	[Out] float% Param_Out_StrokeWidth,
	[Out] cli::array<float>^% Param_Out_Dashes,
	UInt32 Param_QuantidadeDashes,
	[Out] float% Param_Out_DashOffset);

	/// <summary>
	/// Retorna o número de traços(Dashes) na matriz de traços. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número dashes na matriz.</param>
	virtual void GetStrokeDashesCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Fornece valores a um glifo SVG para preenchimento. 
	/// </summary>
	/// <param name="Param_Brush">O Brush que descreve como a área é pintada. Um pincel nulo fará com que o valor de preenchimento de contexto venha do ICarenD2D1DeviceContext4::DrawText. 
	/// Se o (ICarenD2D1DeviceContext4::DrawText) Também ser nulo, o valor de preenchimento de contexto será 'nenhum'. Para definir o valor de "preenchimento de contexto", este método usa 
	/// o pincel fornecido com sua opacidade definida para 1. Para definir o valor "contexto-preenchimento-opacidade", este método utiliza a opacidade do pincel fornecido.</param>
	virtual CarenResult SetFill(ICarenD2D1Brush^ Param_Brush);

	/// <summary>
	/// Fornece valores a um glifo SVG para propriedades de traçado. O pincel com opacidade definido para 1 é usado como o "traçado de contexto". A opacidade do pincel é usada como o valor 
	/// "contexto-traçado-opacidade". 
	/// </summary>
	/// <param name="Param_Brush">O Brush que descreve como o Stroke é pintado. Um pincel nulo fará com que o valor do traçado do contexto não seja nenhum.</param>
	/// <param name="Param_StrokeWidth">Especifica o 'valor de contexto' para a propriedade 'largura de traçado'.</param>
	/// <param name="Param_Dashes">Especifica o 'valor de contexto' para a propriedade 'stroke-dasharray'. Um valor nulo fará com que o traçado-dasharray seja definido como "nenhum".</param>
	/// <param name="Param_QuantidadeDashes">O número de Dashes na matriz (Param_Dashes).</param>
	/// <param name="Param_DashOffset">Especifica o 'valor de contexto' para a propriedade 'stroke-dashoffset'.</param>
	virtual CarenResult SetStroke(
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	cli::array<float>^ Param_Dashes,
	UInt32 Param_QuantidadeDashes,
	float Param_DashOffset);


	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};