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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por estender o retângulo de entrada ao infinito usando os modos de extensão especificados.
/// </summary>
public ref class CarenD2D1BorderTransform : public ICarenD2D1BorderTransform
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1BorderTransform).
	ID2D1BorderTransform* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenD2D1BorderTransform();


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
	/// <param name="Param_Out_CarenD2D1BorderTransform">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenD2D1BorderTransform^% Param_Out_CarenD2D1BorderTransform)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

		//Cria a interface
		Param_Out_CarenD2D1BorderTransform = gcnew CarenD2D1BorderTransform();

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


	//Métodos da interface(ICarenD2D1BorderTransform)
public:
	/// <summary>
	/// Obtém o modo de extensão na direção X.
	/// </summary>
	/// <param name="Param_Out_ExtendModeX">Retorna o modo de extensão na direção X.</param>
	virtual void GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeX);

	/// <summary>
	/// Obtém o modo de extensão na direção Y.
	/// </summary>
	/// <param name="Param_Out_ExtendModeY">Retorna o modo de extensão na direção Y.</param>
	virtual void GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendModeY);

	/// <summary>
	/// Define o modo de extensão na direção X.
	/// Se a enumeração do modo de extensão for inválida, esta operação será ignorada.
	/// </summary>
	/// <param name="Param_ExtendModeX">O modo de extensão na direção X.</param>
	virtual void SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ExtendModeX);

	/// <summary>
	/// Define o modo de extensão na direção Y.
	/// Se a enumeração do modo de extensão for inválida, esta operação será ignorada.
	/// </summary>
	/// <param name="Param_ExtendModeY">O modo de extensão na direção Y.</param>
	virtual void SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ExtendModeY);


	//Métodos da interface(ICarenD2D1ConcreteTransform)
public:
	/// <summary>
	/// Define se a saída da transformação especificada está armazenada em cache. 
	/// </summary>
	/// <param name="Param_IsCached">TRUE se a saída deve ser armazenada em cache; caso contrário, FALSO.</param>
	virtual void SetCached(Boolean Param_IsCached);

	/// <summary>
	/// Define as propriedades do buffer de saída do nó de transformação especificado. 
	/// </summary>
	/// <param name="Param_BufferPrecision">O número de bits e o tipo de buffer de saída.</param>
	/// <param name="Param_ChannelDepth">O número de canais no buffer de saída (1 ou 4).</param>
	virtual CarenResult SetOutputBuffer(
		CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
		CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth);


	//Métodos da interface(ICarenD2D1TransformNode)
public:
	/// <summary>
	/// Obtém o número de entradas para o nó de transformação. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este nó de transformação.</param>
	virtual void GetInputCount([Out] UInt32% Param_Out_Quantidade);
};