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
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por ampliar a interface ICarenMFMediaEngineSrcElements para fornecer recursos adicionais.
/// </summary>
public ref class CarenMFMediaEngineSrcElementsEx : public ICarenMFMediaEngineSrcElementsEx
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaEngineSrcElementsEx).
	IMFMediaEngineSrcElementsEx* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaEngineSrcElementsEx();
	
	~CarenMFMediaEngineSrcElementsEx();

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


	//Métodos da interface(ICarenMFMediaEngineSrcElementsEx)
public:
	/// <summary>
	/// Fornece uma versão aprimorada do ICarenMFMediaEngineSrcElements::AddElement para adicionar o sistema-chave destinado a ser usado com conteúdo a um elemento.
	/// </summary>
	/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
	/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
	/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
	/// <param name="Param_KeySystem">A Key(Chave) da sessão de mídia.</param>
	virtual CarenResult AddElementEx(
	String^ Param_Url,
	String^ Param_Tipo,
	String^ Param_Midia,
	String^ Param_KeySystem);

	/// <summary>
	/// Obtém o sistema-chave para o índice de elemento de origem dado.
	/// </summary>
	/// <param name="Param_Index">O índice de elementos de origem.</param>
	/// <param name="Param_Out_MimeType">Recebe o tipo MIME do elemento fonte.</param>
	virtual CarenResult GetKeySystem(
	UInt32 Param_Index, 
	[Out] String^% Param_Out_MimeType);


	//Métodos da interface(ICarenMFMediaEngineSrcElements)
public:
	/// <summary>
	/// Adiciona um elemento de origem ao final da lista.
	/// </summary>
	/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
	/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
	/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
	virtual CarenResult AddElement(
		String^ Param_Url,
		String^ Param_Tipo,
		String^ Param_Midia
	);

	/// <summary>
	/// Obtém o número de elementos de origem na lista.
	/// </summary>
	/// <param name="Param_Out_Quantidade">Recebe o numero de elementos presente na lista.</param>
	virtual void GetLength([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtém o tipo de mídia pretendido de um elemento na lista.
	/// </summary>
	/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
	/// <param name="Param_Out_Midia">Recebe uma string que contém uma sequência de consulta de mídia. Se nenhum tipo de mídia for definido, este parâmetro receberá o valor NULO.</param>
	virtual CarenResult GetMedia(
		UInt32 Param_Index,
		[Out] String^% Param_Out_Midia);

	/// <summary>
	/// Obtém o tipo MIME de um elemento na lista.
	/// </summary>
	/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
	/// <param name="Param_Out_MimeType">Recebe uma string que contém o MIME Type. Se nenhum tipo de MIME for definido, este parâmetro receberá o valor NULO.</param>
	virtual CarenResult GetType(
		UInt32 Param_Index,
		[Out] String^% Param_Out_MimeType);

	/// <summary>
	/// Obtém a URL de um elemento na lista.
	/// </summary>
	/// <param name="Param_Index">>O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
	/// <param name="Param_Out_Url">Recebe uma string que contém a URL do elemento de origem. Se nenhuma URL for definida, este parâmetro receberá o valor NULO</param>
	virtual CarenResult GetURL(
		UInt32 Param_Index,
		[Out] String^% Param_Out_Url);

	/// <summary>
	/// Remove todos os elementos de origem da lista.
	/// </summary>
	virtual CarenResult RemoveAllElements();
};