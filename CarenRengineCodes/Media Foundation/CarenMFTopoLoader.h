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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenMFTopology.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Conluido - Fase de Testes) - Classe responsável por converter uma topologia parcial em uma topologia completa.
/// </summary>
public ref class CarenMFTopoLoader :public ICarenMFTopoLoader
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFTopoLoader).
	IMFTopoLoader* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a interface e permite que o usuário decida se a biblioteca deve criar a interface ou vai iniciar sem um ponteiro 
	/// de trabalho.
	/// </summary>
	/// <param name="Param_CriarInterface">Um valor booleano, TRUE indica que deve criar uma nova interface intermanete, caso contario, FALSE.</param>
	CarenMFTopoLoader(Boolean Param_CriarInterface);

	~CarenMFTopoLoader();


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
	/// Método responsável por criar o conversor de topologia.
	/// </summary>
	/// <param name="Param_Out_TopoLoader">Recebe um ponteiro para o conversor de topologia.</param>
	static CarenResult CriarInstancia([Out] ICarenMFTopoLoader^% Param_Out_TopoLoader)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que contém o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas no método.
		IMFTopoLoader* pTopoLoader = NULL;

		//Chama o método
		Hr = MFCreateTopoLoader(&pTopoLoader);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Erro
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface.
		Param_Out_TopoLoader = gcnew CarenMFTopoLoader();

		//Deifine o ponteiro
		Param_Out_TopoLoader->AdicionarPonteiro(pTopoLoader);

		//Define sucesso na operção.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_TopoLoader">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMFTopoLoader^% Param_Out_TopoLoader)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_TopoLoader = gcnew CarenMFTopoLoader();

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



	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// (Load) - Cria uma topologia totalmente carregada da topologia parcial de entrada.
	/// Esse método cria qualquer transformações intermediárias que são necessárias para concluir a topologia. Ele também define os tipos de mídia de entrada e saída em todos os objetos na topologia. 
	/// Se o método for bem-sucedido, a topologia completa será retornada no parâmetro Param_Out_TopologiaCompleta.
	/// </summary>
	/// <param name="Param_TopologiaParcial">Um ponteiro para a interface ICarenMFTopology da topologia parcial a ser resolvida.</param>
	/// <param name="Param_Out_TopologiaCompleta">Recebe um ponteiro para a interface ICarenMFTopology da topologia concluída. O chamador deve liberar a interface.</param>
	/// <param name="Param_TopologiaAnterior">Um ponteiro para a interface ICarenMFTopology da topologia completa anterior. O carregador de topologia pode reusar objetos dessa topologia na nova topologia. 
	/// Este parâmetro pode ser NULL.</param>
	virtual CarenResult Load(ICarenMFTopology^ Param_TopologiaParcial, [Out] ICarenMFTopology^% Param_Out_TopologiaCompleta, ICarenMFTopology^ Param_TopologiaAnterior);
};