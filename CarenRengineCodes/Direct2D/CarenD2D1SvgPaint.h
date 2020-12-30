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
#include "CarenD2D1SvgAttribute.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por descrever um valor de Fill(Preenchimento) ou Stroke(Traçado) SVG.
/// </summary>
public ref class CarenD2D1SvgPaint : public ICarenD2D1SvgPaint
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1SvgPaint).
	ID2D1SvgPaint* PonteiroTrabalho = NULL;


	//Construtor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenD2D1SvgPaint();

	~CarenD2D1SvgPaint();

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


	//Métodos da interface(ICarenD2D1SvgPaint)
public:
	/// <summary>
	/// Obtém a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR. 
	/// </summary>
	/// <param name="Param_Out_Color">Retorna a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR.</param>
	virtual void GetColor([Out] CA_D2D1_COLOR_F^% Param_Out_Color);

	/// <summary>
	/// Obtém o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
	/// </summary>
	/// <param name="Param_Out_Id">O elemento id que atua como o servidor de tinta.</param>
	/// <param name="Param_IdCount">A largura do Id do elemento a ser retornado. Chame o método (GetIdLength) para obter esse valor.</param>
	virtual CarenResult GetId(
	[Out] String^% Param_Out_Id,
	UInt32 Param_IdCount);

	/// <summary>
	/// Obtém o comprimento da sequência do id do elemento que age como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
	/// </summary>
	/// <param name="Param_Out_Largura">Retorna o comprimento da sequência do id elemento que age como o servidor de tinta. O comprimento da corda retornado não inclui 
	/// espaço para o exterminador nulo.</param>
	virtual void GetIdLength([Out] UInt32% Param_Out_Largura);

	/// <summary>
	/// Obtém o tipo de tinta. 
	/// </summary>
	/// <param name="Param_Out_PaintType">Retorna um Enum para o tipo de tinta.</param>
	virtual void GetPaintType([Out] CA_D2D1_SVG_PAINT_TYPE% Param_Out_PaintType);

	/// <summary>
	/// Define a cor da tinta usada se o tipo de tinta estiver D2D1_SVG_PAINT_TYPE_COLOR. 
	/// </summary>
	/// <param name="Param_Color">Uma estrutura(CA_D2D1_COLOR_F) com a nova cor da tinta.</param>
	virtual CarenResult SetColor(CA_D2D1_COLOR_F^ Param_Color);

	/// <summary>
	/// Define o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
	/// </summary>
	/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
	virtual CarenResult SetId(String^ Param_Id);

	/// <summary>
	/// Define o tipo de tinta. 
	/// </summary>
	/// <param name="Param_PaintType">Um enum que define o novo tipo de tinta.</param>
	virtual CarenResult SetPaintType(CA_D2D1_SVG_PAINT_TYPE Param_PaintType);



	//Métodos da interface(ICarenD2D1SvgAttribute)
public:
	/// <summary>
	/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
	/// </summary>
	/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
	virtual CarenResult Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface);

	/// <summary>
	/// Retorna o elemento no qual este atributo é definido. Retorna nulo se o atributo não estiver definido em nenhum elemento. 
	/// </summary>
	/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém um ponteiro parao elemtno no qual este atributo é definido. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetElement(ICaren^ Param_Out_SvgElement);



	//Métodos da interface(ICarenD2D1Resource)
public:
	/// <summary>
	/// Recupera a fábrica associada a este recurso.
	/// </summary>
	/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual void GetFactory(ICaren^ Param_Out_Factory);
};