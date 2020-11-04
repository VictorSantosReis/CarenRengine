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
#include "CarenWICEnumMetadataItem.h"
#include "CarenWICMetadataHandlerInfo.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que fornecem acesso à escrita de conteúdo de metadados. Isso é implementado por fornecedores de software 
/// independentes (ISVs) para criar novos escritores de metadados.
/// </summary>
public ref class CarenWICMetadataWriter : public ICarenWICMetadataWriter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICMetadataWriter).
	IWICMetadataWriter* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICMetadataWriter();
	
	~CarenWICMetadataWriter();

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


	//Métodos da interface(ICarenWICMetadataWriter)
public:
	/// <summary>
	/// Remove o item metadados que corresponde aos parâmetros determinados. 
	/// </summary>
	/// <param name="Param_Schema">Uma estrutura para a propriedade do esquema de metadados.</param>
	/// <param name="Param_Id">Uma estrutura para a propriedade de id metadata.</param>
	virtual CarenResult RemoveValue(
	CA_PropVariant^ Param_Schema,
	CA_PropVariant^ Param_Id);

	/// <summary>
	/// Remove o item metadados no índice especificado. 
	/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
	/// metadados restantes, bem como a contagem mudará.
	/// </summary>
	/// <param name="Param_Index">O índice do item metadados para remover.</param>
	virtual CarenResult RemoveValueByIndex(UInt32 Param_Index);

	/// <summary>
	/// Define o item de metadados dado.
	/// </summary>
	/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
	/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
	/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
	virtual CarenResult SetValue(
	CA_PropVariant^ Param_Schema,
	CA_PropVariant^ Param_Id,
	CA_PropVariant^ Param_Valor);

	/// <summary>
	/// Define o item metadados no índice especificado.
	/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
	/// metadados restantes, bem como a contagem mudará.
	/// </summary>
	/// <param name="Param_Index">O índice do item metadados para definir.</param>
	/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
	/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
	/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
	virtual CarenResult SetValueByIndex(
	UInt32 Param_Index,
	CA_PropVariant^ Param_Schema,
	CA_PropVariant^ Param_Id,
	CA_PropVariant^ Param_Valor);


	//Métodos da interface(ICarenWICMetadataReader)
public:
	/// <summary>
	/// Obtém o número de itens de metadados dentro do leitor.
	/// </summary>
	/// <param name="Param_Out_Quantidade">Recebe o número de itens de metadados dentro do leitor.</param>
	virtual CarenResult GetCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Retorna um enumerador de todos os itens de metadados.
	/// </summary>
	/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o enumerador de metadados.</param>
	virtual CarenResult GetEnumerator([Out] ICarenWICEnumMetadataItem^% Param_Out_EnumMetadata);

	/// <summary>
	/// Obtém o formato de metadados associado ao leitor.
	/// </summary>
	/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
	virtual CarenResult GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata);

	/// <summary>
	/// Obtém as informações do manipulador de metadados associadas ao leitor.
	/// </summary>
	/// <param name="Param_Out_HandlerInfo">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o ICarenWICMetadataHandlerInfo.</param>
	virtual CarenResult GetMetadataHandlerInfo([Out] ICarenWICMetadataHandlerInfo^% Param_Out_HandlerInfo);

	/// <summary>
	/// Obtém o valor do item metadados.
	/// </summary>
	/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
	/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
	/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
	virtual CarenResult GetValue(
		CA_PropVariant^ Param_Schema,
		CA_PropVariant^ Param_Id,
		[Out] CA_PropVariant^% Param_Out_Valor);

	/// <summary>
	/// Obtém o item metadados no índice dado.
	/// </summary>
	/// <param name="Param_Index">O índice do item metadados para recuperar.</param>
	/// <param name="Param_Out_Schema">Retorna uma estrutura para a propriedade do esquema do item de metadados.</param>
	/// <param name="Param_Out_Id">Retorna uma estrutra para o id do item metadados.</param>
	/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
	virtual CarenResult GetValueByIndex(
		UInt32 Param_Index,
		[Out] CA_PropVariant^% Param_Out_Schema,
		[Out] CA_PropVariant^% Param_Out_Id,
		[Out] CA_PropVariant^% Param_Out_Valor);
};