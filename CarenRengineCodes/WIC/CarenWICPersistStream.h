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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que fornecem carga adicional e salvam métodos que usam CA_WICPersistOptions.
/// </summary>
public ref class CarenWICPersistStream : public ICarenWICPersistStream
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICPersistStream).
	IWICPersistStream* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICPersistStream();
	
	~CarenWICPersistStream();

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


	//Métodos da interface(ICarenWICPersistStream)
public:
	/// <summary>
	/// Carrega dados de um fluxo de entrada usando os parâmetros determinados. 
	/// NULO pode ser passado para (Param_GuidPreferredVendor) para indicar nenhuma preferência.
	/// </summary>
	/// <param name="Param_Stream">O fluxo de entrada.</param>
	/// <param name="Param_GuidPreferredVendor">O GUID do fornecedor preferido.</param>
	/// <param name="Param_PersistOptions">O WICPersistOptions usado para carregar o fluxo.</param>
	virtual CarenResult LoadEx(
	ICarenStream^ Param_Stream,
	String^ Param_GuidPreferredVendor,
	CA_WICPersistOptions Param_PersistOptions);

	/// <summary>
	/// Salva o ICaremWICPersistStream para o ICarenStream de entrada dado usando os parâmetros determinados.
	/// </summary>
	/// <param name="Param_Stream">O fluxo para salvar.</param>
	/// <param name="Param_PersistOptions">As WICPersistOptions a serem usadas ao salvar.</param>
	/// <param name="Param_ClearDirty">Indica se o valor "dirty" será limpo de todos os metadados após a salvação.</param>
	virtual CarenResult SaveEx(
	ICarenStream^ Param_Stream,
	CA_WICPersistOptions Param_PersistOptions,
	Boolean Param_ClearDirty);

	//Métodos da interface(ICarenPersistStream)
public:
	/// <summary>
	/// Recupera o tamanho do fluxo necessário para salvar o objeto.
	/// Este método retorna o tamanho necessário para salvar um objeto. Você pode chamar este método para determinar o tamanho e definir os 
	/// buffers necessários antes de chamar o método ICarenPersistStream::Save.
	/// </summary>
	/// <param name="Param_Out_Size">Retorna o tamanho em bytes do fluxo necessário para salvar este objeto, em bytes.</param>
	/// <returns></returns>
	virtual CarenResult GetSizeMax(UInt64% Param_Out_Size);

	/// <summary>
	/// Determina se um objeto mudou desde que foi salvo pela última vez em seu fluxo.
	/// Este método retorna SS_OK para indicar que o objeto foi alterado. Caso contrário, ele retorna SS_FALSE.
	/// Você deve tratar quaisquer códigos de retorno de erro como uma indicação de que o objeto foi alterado. A menos que este método retorne 
	/// explicitamente SS_FALSE, assuma que o objeto deve ser salvo.
	/// </summary>
	/// <returns></returns>
	virtual CarenResult IsDirty();

	/// <summary>
	/// Inicializa um objeto do fluxo onde ele foi salvo anteriormente.
	/// </summary>
	/// <param name="Param_Fluxo">Um ICarenStream para o fluxo a partir do qual o objeto deve ser carregado.</param>
	/// <returns></returns>
	virtual CarenResult Load(ICarenStream^ Param_Fluxo);

	/// <summary>
	/// Salva um objeto para o fluxo especificado.
	/// </summary>
	/// <param name="Param_Fluxo">Um ICarenStream para o fluxo no qual o objeto deve ser salvo.</param>
	/// <param name="Param_ClearDirty">Indica se o sinalizador sujo deve ser limpo após a conclusão do salvamento.Se TRUE, o sinalizador deve ser apagado. Se FALSE, o 
	/// sinalizador deve ser deixado inalterado.</param>
	/// <returns></returns>
	virtual CarenResult Save(ICarenStream^ Param_Fluxo, Boolean Param_ClearDirty);


	//Métodos da interface(ICarenPersist)
public:
	/// <summary>
	/// Recupera o identificador de classe (CLSID) do objeto.
	/// </summary>
	/// <param name="Param_Out_ClassID">Retorna o CLSID do objeto atual.</param>
	/// <returns></returns>
	virtual CarenResult GetClassID([Out] String^% Param_Out_ClassID);
};