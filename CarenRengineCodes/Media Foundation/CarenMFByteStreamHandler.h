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
/// (Concluido - Fase de Testes) - Classe responsável por criar uma fonte de mídia a partir de um fluxo de bytes.
/// </summary>
public ref class CarenMFByteStreamHandler : public ICarenMFByteStreamHandler
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFByteStreamHandler).
	IMFByteStreamHandler* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFByteStreamHandler();
	
	~CarenMFByteStreamHandler();

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


	//Métodos da interface(ICarenMFByteStreamHandler)
public:
	/// <summary>
	/// Começa uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
	/// </summary>
	/// <param name="Param_FluxoBytes">Ponteiro para a interface ICarenMFByteStream do fluxo de byte.</param>
	/// <param name="Param_Url">String que contém a URL original do fluxo de bytes. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_SOURCE_RESOLVER_FLAGS.</param>
	/// <param name="Param_Props">Ponteiro para a interface ICarenPropertyStore de uma loja de propriedades. O manipulador de fluxo de bytes pode usar esta loja de propriedades 
	/// para configurar o objeto. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro IUnknown na interface ICaren ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona 
	/// passando este ponteiro para o método ICarenMFByteStreamHandler::CancelObjectCreation. O chamador deve liberar a interface. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface.</param>
	/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado.
	/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	virtual CarenResult BeginCreateObject(
	ICarenMFByteStream^ Param_FluxoBytes,
	String^ Param_Url,
	CA_SOURCE_RESOLVER_FLAGS Param_Flags,
	ICarenPropertyStore^ Param_Props,
	[Out] ICaren^% Param_Out_CookieCancelamento,
	ICarenMFAsyncCallback^ Param_Callback,
	ICaren^ Param_ObjetoEstado);

	/// <summary>
	/// Cancela o pedido atual para criar uma fonte de mídia.
	/// </summary>
	/// <param name="Param_CookieCancelamento">Ponteiro para a interface ICaren que foi retornada no parâmetro (Param_Out_CookieCancelamento) do método 
	/// ICarenMFByteStreamHandler::BeginCreateObject.</param>
	virtual CarenResult CancelObjectCreation(ICaren^ Param_CookieCancelamento);

	/// <summary>
	/// Completa um pedido assíncrono para criar uma fonte de mídia.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que seu objeto de retorno de chamada recebeu no método Invocar.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Ref_InterfaceObjeto">Recebe um ponteiro para a interface da fonte de mídia. O chamador deve criar a interface que vai receber o ponteiro.
	/// O chamador deve liberar a interface quando não for mais utilizar.</param>
	virtual CarenResult EndCreateObject(
	ICarenMFAsyncResult^ Param_Resultado,
	[Out] CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
	ICaren^% Param_Ref_InterfaceObjeto);

	/// <summary>
	/// Recupera o número máximo de bytes necessários para criar a fonte de mídia ou determinar que o manipulador de fluxo de bytes não 
	/// pode analisar este fluxo.
	/// </summary>
	/// <param name="Param_Ref_MaximoNumeroBytes">Recebe o número máximo de bytes necessários.</param>
	virtual CarenResult GetMaxNumberOfBytesRequiredForResolution(UInt64% Param_Ref_MaximoNumeroBytes);
};