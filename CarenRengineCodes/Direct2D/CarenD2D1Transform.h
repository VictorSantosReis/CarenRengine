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
#include "..\SDK_Direct2D.h"
#include "..\SDK_Caren.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por representar a interface base para todas as transformações implementadas pelo autor da transformação.
/// </summary>
public ref class CarenD2D1Transform : public ICarenD2D1Transform
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Transform).
	ID2D1Transform* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenD2D1Transform();


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
	/// <param name="Param_Out_CarenD2D1Transform">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1Transform^% Param_Out_CarenD2D1Transform)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1Transform = gcnew CarenD2D1Transform();

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


	//Métodos da interface(ICarenD2D1Transform)
public:
	/// <summary>
	/// Realiza o mapeamento inverso para MapOutputRectToInputRects.
	/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
	/// Ao contrário das funções MapOutputRectToInputRects e MapInvalidRect, este método é explicitamente chamado pelo renderizador em um determinado lugar em seu algoritmo de renderização. A implementação 
	/// da transformação pode alterar seu estado com base nos retângulos de entrada e usar essas informações para controlar suas informações de renderização. Este método é sempre chamado antes dos métodos 
	/// MapInvalidRect e MapOutputRectToInputRects da transformação.
	/// </summary>
	/// <param name="Param_InputRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída. O parâmetro (Param_InputRects) é sempre igual aos limites de entrada.</param>
	/// <param name="Param_InputOpaqueSubRects">Uma matriz de retângulos de entrada a serem mapeados para o retângulo de saída opaco.</param>
	/// <param name="Param_QuantidadeRetangulos">O número de entradas especificadas. A implementação garante que isso seja igual ao número de entradas especificadas na transformação.</param>
	/// <param name="Param_Out_OutputRect">Retorna o retângulo de saída que mapeia o retângulo de entrada correspondente.</param>
	/// <param name="Param_Out_OutputOpaqueSubRect">Retorna o retângulo de saída que mapeia o retângulo de entrada opaco correspondente.</param>
	virtual CarenResult MapInputRectsToOutputRect(
	cli::array<CA_D2D1_RECT_L^>^ Param_InputRects,
	cli::array<CA_D2D1_RECT_L^>^ Param_InputOpaqueSubRects,
	UInt32 Param_QuantidadeRetangulos,
	[Out] CA_D2D1_RECT_L^% Param_Out_OutputRect,
	[Out] CA_D2D1_RECT_L^% Param_Out_OutputOpaqueSubRect);

	/// <summary>
	/// Define os retângulos de entrada para este passe de renderização na transformação.
	/// A implementação da transformação deve considerar o MapInvalidRect como puramente funcional. A implementação da transformação pode basear o retângulo de entrada mapeado no estado atual da implementação 
	/// da transformação, conforme especificado pelas propriedades de efeito encapsulamento. Mas a implementação da transformação não pode mudar seu próprio estado em resposta a uma chamada ao MapInvalidRect. 
	/// O Direct2D pode chamar esse método a qualquer momento e em qualquer sequência após uma chamada para o método MapInputRectsToOutputRect.
	/// </summary>
	/// <param name="Param_InputIndex">O índice do retângulo de entrada.</param>
	/// <param name="Param_InvalidInputRect">O retângulo de entrada inválido.</param>
	/// <param name="Param_Out_InvalidOutputRect">Retorna o retângulo de saída para o qual o retângulo de entrada deve ser mapeado.</param>
	virtual CarenResult MapInvalidRect(
	UInt32 Param_InputIndex,
	CA_D2D1_RECT_L^ Param_InvalidInputRect,
	[Out] CA_D2D1_RECT_L^% Param_Out_InvalidOutputRect);

	/// <summary>
	/// Permite uma transformação para afirmar como mapearia um retângulo solicitado em sua saída para um conjunto de retângulos de amostra em sua entrada. 
	/// A implementação da transformação deve garantir que qualquer implementação de chamada de pixel ou software que forneça honre este cálculo.
	/// A implementação da transformação deve considerar esse método como puramente funcional. Ele pode basear os retângulos de entrada e saída mapeados em seu estado atual, conforme especificado pelas 
	/// propriedades de efeito encapsulamento. No entanto, não deve mudar seu próprio estado em resposta a este método que está sendo invocado. A implementação do renderizador Direct2D reserva-se o direito 
	/// de chamar este método a qualquer momento e em qualquer sequência.
	/// </summary>
	/// <param name="Param_OutputRect">O retângulo de saída do qual as entradas devem ser mapeadas.</param>
	/// <param name="Param_Out_InputRects">O conjunto correspondente de entradas. As entradas corresponderão diretamente aos insumos de transformação.</param>
	/// <param name="Param_InputRectsCount">O número de entradas especificadas. O Direct2D garante que isso seja igual ao número de entradas especificadas na transformação.</param>
	virtual CarenResult MapOutputRectToInputRects(
	CA_D2D1_RECT_L^ Param_OutputRect,
	[Out] cli::array<CA_D2D1_RECT_L^>^% Param_Out_InputRects,
	UInt32 Param_InputRectsCount);


	//Métodos da interface(ICarenD2D1TransformNode)
public:
	/// <summary>
	/// Obtém o número de entradas para o nó de transformação. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este nó de transformação.</param>
	virtual void GetInputCount([Out] UInt32% Param_Out_Quantidade);
};