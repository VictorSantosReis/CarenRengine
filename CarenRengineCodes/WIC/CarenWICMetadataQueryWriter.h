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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"
#include "../Windows/CarenEnumString.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por expor métodos para definir ou remover itens e blocos de metadados em um codificador ou em seus quadros de imagem usando 
/// uma expressão de consulta de metadados.
/// </summary>
public ref class CarenWICMetadataQueryWriter : public ICarenWICMetadataQueryWriter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICMetadataQueryWriter).
	IWICMetadataQueryWriter* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICMetadataQueryWriter();
	
	~CarenWICMetadataQueryWriter();

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


	//Métodos da interface(ICarenWICMetadataQueryWriter)
public:
	/// <summary>
	/// Remove um item de metadados de um local específico usando uma expressão de consulta de metadados.
	/// Este método usa expressões de consulta de metadados para remover metadados. Se o item metadados for um bloco de metadados, ele será removido da hierarquia de metadados.
	/// </summary>
	/// <param name="Param_Nome">O nome do item metadados para remover.</param>
	virtual CarenResult RemoveMetadataByName(String^ Param_Nome);

	/// <summary>
	/// Define um item de metadados em um local específico. 
	/// Este método usa expressões de consulta de metadados para remover metadados. Se o conjunto de valor é um bloco de metadados aninhados, use o tipo de variante 
	/// (TP_PonteiroDesconhecido) e o (Param_Valor) apontando para o ICarenWICMetadataQueryWriter do novo bloco de metadados.
	/// A encomenda de itens de metadados fica a critério do autor de consulta, uma vez que os locais relativos não são especificados.
	/// </summary>
	/// <param name="Param_Nome">O nome do item metadados.</param>
	/// <param name="Param_Valor">Uma estrutura(CA_PropVariant) que contém o valor dos metadados para definir.</param>
	virtual CarenResult SetMetadataByName(
	String^ Param_Nome,
	CA_PropVariant^ Param_Valor);


	//Métodos da interface(ICarenWICMetadataQueryReader)
public:
	/// <summary>
	/// Obtém o formato de contêiner de leitores de consulta de metadados. 
	/// </summary>
	/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID que representa o tipo do formato cointainer.</param>
	virtual CarenResult GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat);

	/// <summary>
	/// Obtém um enumerador de todos os itens de metadados na localização relativa atual dentro da hierarquia de metadados. 
	/// </summary>
	/// <param name="Param_Out_EnumString">Retorna uma interface(ICarenEnumString) que contém um ponteiro para o enumerador que contém Strings de consulta que pode ser usadas na 
	/// interface (ICarenWICMetadataQueryReader) atual.</param>
	virtual CarenResult GetEnumerator([Out] ICarenEnumString^% Param_Out_EnumString);

	/// <summary>
	/// Recupera o caminho atual em relação ao bloco de metadados raiz. Se o leitor de consulta for relativo ao topo da hierarquia de metadados, ele retornará uma sequência de char único.
	/// Se o leitor de consulta for relativo a um bloco de metadados aninhados, este método retornará o caminho para o leitor de consulta atual.
	/// Se você passar NULO para (Param_Ref_Namespace), o GetLocation ignorará o (Param_SizeString) e retorna o comprimento de buffer necessário para armazenar o caminho na variável 
	/// a que o (Param_Out_SizeAtual) aponta.
	/// </summary>
	/// <param name="Param_SizeString">O comprimento da String em (Param_Ref_Namespace).</param>
	/// <param name="Param_Ref_Namespace">Retorna uma string que contém a localização atual do namespace.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o comprimento real necessário pela String(Param_Ref_Namespace).</param>
	virtual CarenResult GetLocation(
		UInt32 Param_SizeString,
		String^% Param_Ref_Namespace,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o bloco de metadados ou item identificado por uma expressão de consulta de metadados.
	/// Este método usa expressões de consulta de metadados para acessar metadados incorporados. Se existirem vários blocos ou itens expressos pela mesma expressão de consulta, 
	/// o primeiro bloco de metadados ou item encontrado será devolvido.
	/// </summary>
	/// <param name="Param_Nome">A expressão de consulta ao bloco ou item de metadados solicitados.</param>
	/// <param name="Param_Out_Valor">Retorna uma estrutura(CA_PropVariant) que armazena o bloco de metadados ou item solicitado.</param>
	virtual CarenResult GetMetadataByName(
		String^ Param_Nome,
		[Out] CA_PropVariant^% Param_Out_Valor);
};