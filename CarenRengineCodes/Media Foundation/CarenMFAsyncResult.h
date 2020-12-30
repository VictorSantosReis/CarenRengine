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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por fornecer informações sobre o resultado de uma operação assíncroda
/// </summary>
public ref class CarenMFAsyncResult : ICarenMFAsyncResult
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFAsyncResult).
	IMFAsyncResult* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	/// </summary>
	CarenMFAsyncResult();

	/// <summary>
	/// Inicializa a classe com um novo objeto de resutlado Assincrono implementado internamente.
	/// </summary>
	/// <param name="Param_ObjetoDados">Interface para o objeto armazenado no resultado assíncrono. Essa Interface é retornado pelo método (ICarenMFAsyncResult.GetObject). Este parâmetro pode ser MULO.</param>
	/// <param name="Param_Callback">A interface que é implementada pelo usuário para receber os eventos do sistema.</param>
	/// <param name="Param_ObjetoEstado">Uma interface de um objeto de estado. Esse valor é fornecido pelo chamador do método assíncrono. Este parâmetro pode ser NULO.</param>
	CarenMFAsyncResult(ICaren^ Param_ObjetoDados, ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoEstado);

	~CarenMFAsyncResult();


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



	//
	// ICarenMFAsyncResult
	//

	//Métodos da interface proprietaria
public:
	/// <summary>
	/// (GetObject) - Retorna um objeto associado à operação assíncrona. O tipo de objeto, se houver, depende do método assíncrono que foi chamado.
	/// </summary>
	/// <param name="Param_Out_Objeto">Recebe a interface com o objeto desconhecido. Se nenhum objeto estiver associado à operação, esse parâmetro receberá o valor NULO. 
	/// Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetObject(ICaren^ Param_Out_Objeto);

	/// <summary>
	/// (GetState) - Retorna o objeto de estado especificado pelo chamador no método Begin assíncrono.
	/// O chamador do método assíncrono especifica o objeto de estado e pode usá-lo para qualquer finalidade definida pelo responsável da chamada. O objeto de estado pode ser NULO.
	/// </summary>
	/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetState(ICaren^ Param_Out_ObjetoEstado);

	/// <summary>
	/// (GetStateNoAddRef) - Retorna o objeto de estado especificado pelo chamador no método assíncrono Begin, sem incrementar a contagem de referência do objeto.
	/// </summary>
	/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetStateNoAddRef(ICaren^ Param_Out_ObjetoEstado);

	/// <summary>
	/// (GetStatus) - Retorna o status da operação assíncrona.
	/// </summary>
	virtual CarenResult GetStatus();

	/// <summary>
	/// (SetStatus) - Define o status da operação assíncrona.
	/// </summary>
	/// <param name="Param_HRESULT">O código HRESULT que vai definir o status geral da operação.</param>
	virtual CarenResult SetStatus(int Param_HRESULT);
};

