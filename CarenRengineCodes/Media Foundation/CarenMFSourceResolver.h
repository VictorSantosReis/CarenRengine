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
#include "..\SDK_MediaFoundation.h"
#include "..\Caren\Caren.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de testes) - Classe responsável por criar uma fonte de mídia a parti de uma URL ou fluxo de bytes. 
/// </summary>
public ref class CarenMFSourceResolver : public ICarenMFSourceResolver
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceResolver).
	IMFSourceResolver* PonteiroTrabalho = NULL;



	//Contrutor e destruidor da classe.
public:
	~CarenMFSourceResolver();


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



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Método responsável por criar uma instância da interface de resolução de fontes.
	/// </summary>
	/// <param name="Param_Out_ResolvedorFonte">Recebe a interface do resolvedor de fontes.</param>
	static CarenResult CriarInstancia([Out] ICarenMFSourceResolver^% Param_Out_ResolvedorFonte)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que contém o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variavel que vai ser retornada.
		IMFSourceResolver* pResolvedorFonte = NULL;
		ICarenMFSourceResolver^ InterfaceResolvedorFonte = nullptr;

		//Chama o método que vai criar o resolvedor de fonte
		Hr = MFCreateSourceResolver(&pResolvedorFonte);

		//Verifica se obteve sucesso
		if (Sucesso(Hr))
		{
			//Deixa continuar.
		}
		else
		{
			//A operação falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai receber o ponteiro
		InterfaceResolvedorFonte = gcnew CarenMFSourceResolver();

		//Define a interface de trabalho.
		InterfaceResolvedorFonte->AdicionarPonteiro(pResolvedorFonte);

		//Define a interface no parametro de saida.
		Param_Out_ResolvedorFonte = InterfaceResolvedorFonte;

		//Define sucesso na operção.
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




	//Métodos da interface(ICarenMFSourceResolver)
public:
	/// <summary>
	/// (BeginCreateObjectFromByteStream) - Inicia uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
	/// </summary>
	/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
	/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
	/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
	/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_ObjetoCancel">Recebe um ponteiro ICaren ou o valor nulo. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
	/// de ICarenMFSourceResolver::CancelarCriaçãoObjeto. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
	/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
	/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
	virtual CarenResult CriarObjetoFromByteStreamAsync
	(
		ICarenMFByteStream^ Param_FluxoBytes,
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		ICaren^ Param_ObjetoCancel,
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjetoEstado
	);

	/// <summary>
	/// (BeginCreateObjectFromURL) - Inicia uma solicitação assíncrona para criar uma fonte de mídia ou um fluxo de bytes de uma URL.
	/// </summary>
	/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
	/// <param name="Param_Flags">OR bit a bit dos sinalizadores.</param>
	/// <param name="Param_Propriedades">Ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o esquema manipulador ou 
	/// manipulador de fluxo de bytes que cria o objeto. O manipulador pode usar o armazenamento de propriedade para configurar o objeto. Este parâmetro pode ser nulo</param>
	/// <param name="Param_ObjetoCancel">Recebe um ponteiro ICaren ou o valor nulo. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
	/// de ICarenMFSourceResolver::CancelarCriaçãoObjeto. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
	/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
	/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
	virtual CarenResult CriarObjetoFromUrlAsync
	(
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		ICaren^ Param_ObjetoCancel,
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjetoEstado
	);

	/// <summary>
	/// (CancelObjectCreation) - Cancela uma solicitação assíncrona para criar um objeto.
	/// </summary>
	/// <param name="Param_ObjetoCancel">Ponteiro para a interface ICaren que foi retornada no parâmetro Param_ObjetoCancel do método ICarenMFSourceResolver::CriarObjetoFromByteStreamAsync 
	/// ou ICarenMFSourceResolver::CriarObjetoFromUrlAsync. </param>
	virtual CarenResult CancelarCriaçãoObjeto(ICaren^ Param_ObjetoCancel);

	/// <summary>
	/// (CreateObjectFromByteStream) - Cria uma fonte de mídia de um fluxo de bytes. Este método é síncrono.
	/// </summary>
	/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
	/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
	/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
	/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult CriarObjetoFromByteStream
	(
		ICarenMFByteStream^ Param_FluxoBytes,
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (CreateObjectFromURL) - Cria uma fonte de mídia ou um fluxo de bytes de um URL. Este método é síncrono.
	/// </summary>
	/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
	/// <param name="Param_Flags">OR bit a bit de um ou mais bandeiras.</param>
	/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
	/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult CriarObjetoFromUrl
	(
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (EndCreateObjectFromByteStream) - Conclui uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult ConcluirCriaçãoObjetoFromByteStream
	(
		ICarenMFAsyncResult^ Param_Resultado,
		[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (EndCreateObjectFromURL) - Conclui uma solicitação assíncrona para criar um objeto a partir de um URL.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult ConcluirCriaçãoObjetoFromUrl
	(
		ICarenMFAsyncResult^ Param_Resultado,
		[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);
};

