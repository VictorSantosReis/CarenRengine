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
/// (Concluido - Fase de Testes) - Classe responsável por definir e recuperar informações sobre o nome de usuário e senha para fins de autenticação.
/// </summary>
public ref class CarenMFNetCredential : public ICarenMFNetCredential
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFNetCredential).
	IMFNetCredential* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFNetCredential();
	
	~CarenMFNetCredential();

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


	//Métodos da interface(ICarenMFNetCredential)
public:
	/// <summary>
	/// Recupera a senha.
	/// </summary>
	/// <param name="Param_Ref_Senha">Um buffer de bytes que recebe a (SENHA). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
	/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados. O usuário é responsável por inicializar o buffer
/// com o tamanho necessário para ser retornado.</param>
	/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Senha), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
	/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
	/// <param name="Param_Criptografada">Se TRUE, o método retorna uma sequência criptografada. Caso contrário, o método retorna uma sequência não criptografada.</param>
	virtual CarenResult GetPassword(
	cli::array<Byte>^% Param_Ref_Senha,
	UInt32% Param_Ref_LarguraDados,
	Boolean Param_Criptografada);

	/// <summary>
	/// Recupera o nome de usuário.
	/// </summary>
	/// <param name="Param_Ref_Usuario">Um buffer de bytes que recebe o (USUÁRIO). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
	/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados. O usuário é responsável por inicializar o buffer
/// com o tamanho necessário para ser retornado.</param>
	/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Usuario), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
	/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
	/// <param name="Param_Criptografada">Se TRUE,o método retorna uma seqüência criptografada. Caso contrário, o método retorna uma seqüência não criptografada.</param>
	virtual CarenResult GetUser(
	cli::array<Byte>^% Param_Ref_Usuario,	
	UInt32% Param_Ref_LarguraDados,
	Boolean Param_Criptografada);

	/// <summary>
	/// Verifica se as credenciais registradas devem ser usadas.
	/// </summary>
	/// <param name="Param_Out_Resultado">Recebe um valor booleano. Se as credenciais registradas devem ser usadas, o valor é TRUE. Caso contrário, o valor é FALSO.</param>
	virtual CarenResult LoggedOnUser([Out] Boolean% Param_Out_Resultado);

	/// <summary>
	/// Define a senha.
	/// </summary>
	/// <param name="Param_Senha">Um buffer de bytes que contém a (SENHA). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
	/// buffer contém dados criptografados.</param>
	/// <param name="Param_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
	/// <param name="Param_Criptografar">Se TRUE, a senha será criptografada. Caso contrário, a senha não é criptografada.</param>
	virtual CarenResult SetPassword(
	cli::array<Byte>^ Param_Senha,
	UInt32 Param_LarguraDados,
	Boolean Param_Criptografar);

	/// <summary>
	/// Define o nome de usuário.
	/// </summary>
	/// <param name="Param_Usuario">Um buffer de bytes que contém o (USUÁRIO). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
	/// buffer contém dados criptografados.</param>
	/// <param name="Param_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
	/// <param name="Param_Criptografar">Se TRUE, o usuário será criptografado. Caso contrário, o usuário não é criptografado.</param>
	virtual CarenResult SetUser(
	cli::array<Byte>^ Param_Usuario,
	UInt32 Param_LarguraDados,
	Boolean Param_Criptografar);
};