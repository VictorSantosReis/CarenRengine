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
/// (Concluido - Fase de Testes) - Classe responsável por gerenciar metadados para um objeto. Metadados são informações que descrevem um arquivo de mídia, fluxo ou outro conteúdo.
/// </summary>
public ref class CarenMFMetadata : public ICarenMFMetadata
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMetadata).
	IMFMetadata* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMetadata();
	
	~CarenMFMetadata();

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


	//Métodos da interface(ICarenMFMetadata)
public:
	/// <summary>
	/// Exclui uma propriedade de metadados.
	/// </summary>
	/// <param name="Param_NomePropriedade">Uma string contendo o nome da propriedade a ser deletada.</param>
	virtual CarenResult DeleteProperty(String^ Param_NomePropriedade);

	/// <summary>
	/// Obtém uma lista dos idiomas em que os metadados estão disponíveis.
	/// </summary>
	/// <param name="Param_Out_ListaIdiomas">Retorna uma CA_PropVariant com uma lista de idiomas. A lista é devolvida como uma matriz de seqüência de sequências de caracteres amplos. Cada string na matriz 
	/// é uma tag de idioma compatível com RFC 1766.</param>
	virtual CarenResult GetAllLanguages([Out] CA_PropVariant^% Param_Out_ListaIdiomas);

	/// <summary>
	/// Obtém uma lista de todos os nomes de propriedade de metadados neste objeto.
	/// </summary>
	/// <param name="Param_Out_ListaNomesProps">Retorna uma CA_PropVariant com os nomes de todas as propriedades. Se não houver propriedades disponíveis, o tipo CA_PropVariant será VT_EMPTY. Caso contrário,
	///  o tipo CA_PropVariant é VT_VECTOR | VT_LPWSTR. </param>
	virtual CarenResult GetAllPropertyNames([Out] CA_PropVariant^% Param_Out_ListaNomesProps);

	/// <summary>
	/// Obtém a configuração atual do idioma.
	/// </summary>
	/// <param name="Param_Out_IdiomaRFC1766">Recebe uma string contendo uma tag do idioma compatível com a RFC 1766.</param>
	virtual CarenResult GetLanguage([Out] String^% Param_Out_IdiomaRFC1766);

	/// <summary>
	/// Obtém o valor de uma propriedade de metadados.
	/// </summary>
	/// <param name="Param_NomePropriedade">Uma string que contém o nome da propriedade a ser recuperada o valor.</param>
	/// <param name="Param_Out_Valor">Recebe uma estrutura CA_PropVariant contendo o valor. O tipo CA_PropVariant depende da propriedade. Para propriedades multivalorizadas, o CA_PropVariant é 
	/// um tipo VT_VECTOR.</param>
	virtual CarenResult GetProperty(String^ Param_NomePropriedade, [Out] CA_PropVariant^% Param_Out_Valor);

	/// <summary>
	/// Define o idioma para definir e recuperar metadados.
	/// </summary>
	/// <param name="Param_IdiomaRFC1766">Uma string contendo uma tag de idioma compatível com o RFC 1766.</param>
	virtual CarenResult SetLanguage(String^ Param_IdiomaRFC1766);

	/// <summary>
	/// Define o valor de uma propriedade de metadados.
	/// </summary>
	/// <param name="Param_NomePropriedade">Uma string com o nome da propriedade.</param>
	/// <param name="Param_Valor">Uma CA_PropVariant que contém o valor da propriedade. Para propriedades multivalorizadas, use um CA_PropVariant com um tipo de VT_VECTOR.</param>
	virtual CarenResult SetProperty(String^ Param_NomePropriedade, CA_PropVariant^ Param_Valor);
};