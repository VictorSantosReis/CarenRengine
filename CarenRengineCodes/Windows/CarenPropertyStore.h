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
#include "..\SDK_Base.h"
#include "..\Caren\Caren.h"
#include "..\FunctionClass\PropVariantManager.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

/// <summary>
/// (Concluido - Fase de Testes) - Expõe métodos usados para enumerar e manipular valores de propriedade.
/// </summary>
public ref class CarenPropertyStore : public ICarenPropertyStore
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IPropertyStore).
	IPropertyStore* PonteiroTrabalho = NULL;

	//Destruidor da classe.
public:
	~CarenPropertyStore();


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


	//Cria uma instância da classe
public:
	/// <summary>
	/// Método responsável por criar uma instância da classe atual.
	/// </summary>
	/// <param name="Param_Out_PropertyStore">Recebe a interface de armazenamento de propriedades na memória.</param>
	static CarenResult CriarInstancia([Out]ICarenPropertyStore^% Param_Out_PropertyStore)
	{
		//Variavel que vai retornar o resultado do método.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		ICarenPropertyStore^ InterfaceSolicitada = nullptr;
		IPropertyStore* pStore = NULL;

		//Chama o método para criar um ponteiro para a interface.
		Hr = PSCreateMemoryPropertyStore(IID_PPV_ARGS(&pStore));

		//Verifica o resultado da operação
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define falha na operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro.
		InterfaceSolicitada = gcnew CarenPropertyStore();

		//Chama o método para definir o ponteiro.
		InterfaceSolicitada->AdicionarPonteiro(pStore);

		//Define a interface criada no parametro de saida.
		Param_Out_PropertyStore = InterfaceSolicitada;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
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





	//Métodos da interface ICarenPropertyStore
public:
	/// <summary>
	/// (Commit) - Depois que uma alteração foi feita, esse método salva as alterações.
	/// </summary>
	virtual CarenResult SalvarConfigurações();

	/// <summary>
	/// (GetAt) - Obtém uma chave de propriedade da matriz de propriedades de um item.
	/// </summary>
	/// <param name="Param_Id">O índice da chave Propriedade na matriz de estruturas CA_PROPERTYKEY. Este é um índice baseado em zero.</param>
	/// <param name="Param_Out_PropKey">TBD.</param>
	virtual CarenResult ObterKeyFromID(UInt32 Param_Id, [Out] Estruturas::CA_PROPERTYKEY^% Param_Out_PropKey);

	/// <summary>
	/// (GetCount) - Esse método retorna uma contagem do número de propriedades anexadas ao arquivo.
	/// </summary>
	/// <param name="Param_Out_CountProps">Retorna a contagem de propriedades.</param>
	virtual CarenResult ObterQuantidade([Out] UInt32% Param_Out_CountProps);

	/// <summary>
	/// (GetValue) - Este método recupera os dados para uma propriedade específica.
	/// </summary>
	/// <param name="Param_PropKey">TBD.</param>
	/// <param name="Param_Out_Valor">Depois que o método retorna com êxito, este parâmetro retorna a estrutura CA_PropVariant que contém dados sobre a propriedade.</param>
	virtual CarenResult ObterValor(Estruturas::CA_PROPERTYKEY^% Param_PropKey, [Out] Estruturas::CA_PropVariant^% Param_Out_Valor);

	/// <summary>
	/// (SetValue) - Este método define um valor de propriedade ou substitui ou remove um valor existente.
	/// </summary>
	/// <param name="Param_PropKey">TBD.</param>
	/// <param name="Param_PropValor">TBD.</param>
	virtual CarenResult DefinirValor(Estruturas::CA_PROPERTYKEY^% Param_PropKey, Estruturas::CA_PropVariant^ Param_PropValor);

};

