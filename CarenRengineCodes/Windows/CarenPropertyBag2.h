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
#include "../SDK_Windows.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Windows;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Em desenvolvimento) - 
/// </summary>
public ref class CarenPropertyBag2 : public ICarenPropertyBag2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IPropertyBag2).
	IPropertyBag2* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenPropertyBag2();
	
	~CarenPropertyBag2();

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


	//Métodos da interface(ICarenPropertyBag2)
public:
	/// <summary>
	/// (CountProperties) - Obtém o número de propriedades no bag da propriedade.
	/// </summary>
	/// <param name="Param_Out_Quantidade">Recebe o numero de propriedades presentes na bag.</param>
	virtual CarenResult CountProperties([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// (GetPropertyInfo) - Obtém informações para propriedades em um bag de propriedade sem realmente obter essas propriedades. 
	/// </summary>
	/// <param name="Param_ID">O índice baseado em zero da primeira propriedade para a qual as informações são solicitadas. Este argumento deve ser menor que o número de propriedades recuperadas por ICarenPropertyBag2::CountProperties.</param>
	/// <param name="Param_Quantidade">O número de propriedades sobre as quais obter informações.Este argumento especifica o número de elementos da matriz em (Param_Out_ArrayPropBags).</param>
	/// <param name="Param_Out_ArrayPropBags">Retorna uma matriz de estruturas CA_PROPBAG2 que recebem as informações para as propriedades.</param>
	/// <param name="Param_Out_Quantiade">Recebe o número de propriedades para as quais as informações foram recuperadas na matriz (Param_Out_ArrayPropBags).</param>
	virtual CarenResult GetPropertyInfo(
	UInt32 Param_ID,
	UInt32 Param_Quantidade,
	[Out] cli::array<Estruturas::CA_PROPBAG2^>^% Param_Out_ArrayPropBags,
	[Out] UInt32% Param_Out_Quantiade);


	/// <summary>
	/// (LoadObject) - Faz com que o bag de propriedade instrua um objeto de propriedade que foi criado anteriormente e inicializado para ler suas propriedades persistentes. 
	/// </summary>
	/// <param name="Param_EnderecoNome">O do nome do objeto da propriedade.</param>
	/// <param name="Param_Hint">Um valor inteiro que foi recuperado usando ICarenPropertyBag2::GetPropertyInfo. Este argumento é opcional e deve ser zero, se o valor não for conhecido ou usado.</param>
	/// <param name="Param_UnkObjeto">O endereço da interface IUnknown do objeto. Este argumento não pode ser NULO.</param>
	/// <param name="Param_ErrorLog">Uma interface IErrorlog na qual a bag de propriedade armazena quaisquer erros que ocorram durante a carga. Este argumento pode ser NULO; nesse caso, o chamador não recebe erros de registro.</param>
	virtual CarenResult LoadObject(
	String^ Param_EnderecoNome,
	UInt32 Param_Hint,
	ICaren^ Param_UnkObjeto,
	ICaren^ Param_ErrorLog);

	/// <summary>
	/// (Read) - Faz com que uma ou mais propriedades sejam lidas do bag de propriedade.
	/// </summary>
	/// <param name="Param_Quantidade">O número de propriedades para ler. Este argumento especifica o número de elementos nas matrizes Param_ArrayPropBagsRequest, Param_Out_VarValue e Param_Out_HRESULTArray.</param>
	/// <param name="Param_ArrayPropBagsRequest">uma matriz de estruturas CA_PROPBAG2 que especificam as propriedades solicitadas. O membro vt e o membro pstrName dessas 
	/// estruturas devem ser preenchidos antes que este método possa ser chamado. O membro dwHint dessas estruturas é opcional. Este argumento não pode ser NULO.</param>
	/// <param name="Param_InterfaceErro">Uma interface IErrorlog na qual a bolsa de propriedade armazena quaisquer erros que ocorram durante as leituras. Este argumento pode ser NULO; 
	/// nesse caso, o chamador não recebe erros de registro.</param>
	/// <param name="Param_Out_VarValue">Retorna uma matriz de estruturas CA_VARIANT que recebem os valores da propriedade. O interlocutor não precisa inicializar essas estruturas antes de ligar para 
	/// ICarenPropertyBag2::Read. O método ICarenPropertyBag2::Read preenche o campo de tipo e o campo de valor nessas estruturas antes de retornar.</param>
	/// <param name="Param_Out_HRESULTArray">Retorna uma matriz de valores HRESULT que recebe o resultado de cada propriedade lido.</param>
	virtual CarenResult Read(
	UInt32 Param_Quantidade,
	cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
	ICaren^ Param_InterfaceErro,
	[Out] cli::array<Estruturas::CA_VARIANT^>^% Param_Out_VarValue,
	[Out] cli::array<Int32>^% Param_Out_HRESULTArray);

	/// <summary>
	/// (Write) - Faz com que uma ou mais propriedades sejam salvas no bag da propriedade.
	/// </summary>
	/// <param name="Param_Quantidade">O número de propriedades para salvar. Este argumento especifica o número de elementos nas matrizes Param_ArrayPropBagsRequest e Param_VarValue.</param>
	/// <param name="Param_ArrayPropBagsRequest">Uma matriz de estruturas CA_PROPBAG2 que especificam as propriedades salvas. O membro pstrName dessas estruturas deve ser preenchido antes que este método seja 
	/// chamado. O membro dwHint dessas estruturas é opcional. Este argumento não pode ser NULO.</param>
	/// <param name="Param_VarValue">Uma matriz de estruturas CA_VARIANT que contêm os valores das propriedades para salvar. Este argumento não pode ser NULO.</param>
	virtual CarenResult Write(
	UInt32 Param_Quantidade,
	cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
	cli::array<Estruturas::CA_VARIANT^>^ Param_VarValue);
};