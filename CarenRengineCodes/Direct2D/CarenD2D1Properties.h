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

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct2D;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responável por representar um conjunto de propriedades vinculáveis e desacionáveis de tempo de execução que permitem que um aplicativo 
/// orientado a dados modifique o estado de um efeito Direct2D.
/// </summary>
public ref class CarenD2D1Properties : public ICarenD2D1Properties
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (ID2D1Properties).
	ID2D1Properties* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	CarenD2D1Properties();
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	~CarenD2D1Properties();

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


	//Métodos da interface(ICarenD2D1Properties)
public:
	/// <summary>
	/// Obtém o número de propriedades de alto nível. 
	/// </summary>
	/// <param name="Param_Out_Quantidade"> retorna o número de propriedades personalizadas (não-sistema) que podem ser acessadas pelo objeto.</param>
	virtual void GetPropertyCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Obtém o índice correspondente ao nome da propriedade dada.
	/// Se a propriedade não existe, então esse método retorna D2D1_INVALID_PROPERTY_INDEX. Esse valor reservado nunca irá mapear para um índice válido, e fará com 
	/// que os valores NULO ou sentinela sejam devolvidos 
	/// de outras partes da interface da propriedade.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para recuperar.</param>
	/// <param name="Param_Out_Index">Retorna o índice do nome da propriedade correspondente.</param>
	virtual void GetPropertyIndex(
	String^ Param_NomePropriedade,
	[Out] UInt32% Param_Out_Index);

	/// <summary>
	/// Obtém o nome da propriedade que corresponde ao índice dado.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para a qual o nome está sendo devolvido.</param>
	/// <param name="Param_Out_Nome">Quando este método retorna, contém o nome que está sendo recuperado.</param>
	/// <param name="Param_SizeNome">O número de caracteres no (Param_Out_Nome).</param>
	virtual CarenResult GetPropertyName(
	UInt32 Param_Index,
	[Out] String^% Param_Out_Nome,
	UInt32 Param_SizeNome);

	/// <summary>
	/// Obtém o número de caracteres para o nome da propriedade dado. 
	/// </summary>
	/// <param name="Param_Index">O índice do nome da propriedade para recuperar.</param>
	/// <param name="Param_Out_SizeNome">Retorna o tamanho em caracteres do nome correspondente ao índice de propriedade dado, ou zero se o índice de propriedade não existir.</param>
	virtual void GetPropertyNameLength(
	UInt32 Param_Index,
	[Out] UInt32% Param_Out_SizeNome);

	/// <summary>
	/// Obtém as sub propriedades da propriedade fornecida por índice. 
	/// </summary>
	/// <param name="Param_Index">O índice das sub propriedades a serem recuperadas.</param>
	/// <param name="Param_Out_SubPropriedades">Quando este método retorna, contém um ponteiro para as subpropriedades na interface (ICarenD2D1Properties).</param>
	virtual CarenResult GetSubProperties(
	UInt32 Param_Index,
	[Out] ICarenD2D1Properties^% Param_Out_SubPropriedades);

	/// <summary>
	/// Obtém a D2D1_PROPERTY_TYPE da propriedade selecionada. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para o qual o tipo será recuperado.</param>
	/// <param name="Param_Out_Tipo">Retorna um enum(CA_D2D1_PROPERTY_TYPE) para o tipo da propriedade.</param>
	virtual void GetType(
	UInt32 Param_Index,
	[Out] CA_D2D1_PROPERTY_TYPE% Param_Out_Tipo);

	/// <summary>
	/// Obtém o valor da propriedade especificada por índice. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValue(
	UInt32 Param_Index,
	CA_D2D1_PROPERTY_TYPE Param_Tipo,
	[Out] ICarenBuffer^% Param_Out_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade especificada por índice.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValue(
	UInt32 Param_Index,
	[Out] ICarenBuffer^% Param_Out_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade pelo nome.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValueByName(
	String^ Param_NomePropriedade,
	CA_D2D1_PROPERTY_TYPE Param_Tipo,
	[Out] ICarenBuffer^% Param_Out_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o valor da propriedade pelo nome.
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
	/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
	virtual CarenResult GetValueByName(
	String^ Param_NomePropriedade,
	[Out] ICarenBuffer^% Param_Out_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Obtém o tamanho do valor da propriedade em bytes, usando o índice de propriedade. 
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade.</param>
	/// <param name="Param_Out_Size">Retorna o tamanho do valor em bytes, usando o índice de propriedade</param>
	virtual void GetValueSize(
	UInt32 Param_Index,
	[Out] UInt32% Param_Out_Size);

	/// <summary>
	/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
	/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para definir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValue(
	UInt32 Param_Index,
	CA_D2D1_PROPERTY_TYPE Param_Tipo,
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
	/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
	/// </summary>
	/// <param name="Param_Index">O índice da propriedade para definir.</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValue(
	UInt32 Param_Index,
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade nomeada ao valor dado. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Tipo">TBD</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValueByName(
	String^ Param_NomePropriedade,
	CA_D2D1_PROPERTY_TYPE Param_Tipo,
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// Define a propriedade nomeada ao valor dado. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Buffer">Os dados a serem definidos.</param>
	/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
	virtual CarenResult SetValueByName(
	String^ Param_NomePropriedade,
	ICarenBuffer^ Param_Buffer,
	UInt32 Param_BufferSize);

	/// <summary>
	/// (Templete - SetValueByName(PCWSTR,T)) - Define a propriedade nomeada ao valor dado. Esta é uma sobrecarga de modelo. 
	/// </summary>
	/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
	/// <param name="Param_Valor">Os dados a serem definidos. Como o método converte os dados para um BYTE*, não a necessidade de um ICaren.</param>
	virtual CarenResult SetValueByName(
	String^ Param_NomePropriedade,
	ICarenBuffer^ Param_Valor);
};