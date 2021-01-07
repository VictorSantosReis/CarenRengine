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
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

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



	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a interface e permite que o usuário decida se a biblioteca deve criar a interface ou vai iniciar sem um ponteiro 
	/// de trabalho. Se (Param_CriarInterface) for TRUE, o construtor ‎cria um resolvedor de origem, que é usado para criar uma fonte de 
	/// mídia a partir de uma URL ou fluxo byte.‎
	/// </summary>
	/// <param name="Param_CriarInterface">Um valor booleano, TRUE indica que deve criar uma nova interface intermanete, caso contario, FALSE.</param>
	CarenMFSourceResolver(Boolean Param_CriarInterface);

	~CarenMFSourceResolver();


	//Conversões implicitas
public:
	static operator CarenMFSourceResolver^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFSourceResolver^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFSourceResolver(false);

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFSourceResolver*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenMFSourceResolver::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

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
	/// de ICarenMFSourceResolver::CancelObjectCreation. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
	/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
	/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
	virtual CarenResult BeginCreateObjectFromByteStream
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
	/// de ICarenMFSourceResolver::CancelObjectCreation. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
	/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
	/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
	virtual CarenResult BeginCreateObjectFromURL
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
	/// <param name="Param_ObjetoCancel">Ponteiro para a interface ICaren que foi retornada no parâmetro Param_ObjetoCancel do método ICarenMFSourceResolver::BeginCreateObjectFromByteStream 
	/// ou ICarenMFSourceResolver::BeginCreateObjectFromURL. </param>
	virtual CarenResult CancelObjectCreation(ICaren^ Param_ObjetoCancel);

	/// <summary>
	/// (CreateObjectFromByteStream) - Cria uma fonte de mídia de um fluxo de bytes. Este método é síncrono.
	/// </summary>
	/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
	/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
	/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
	/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateObjectFromByteStream
	(
		ICarenMFByteStream^ Param_FluxoBytes,
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (CreateObjectFromURL) - Cria uma fonte de mídia ou um fluxo de bytes de um URL. Este método é síncrono.
	/// </summary>
	/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
	/// <param name="Param_Flags">OR bit a bit de um ou mais bandeiras.</param>
	/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
	/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult CreateObjectFromURL
	(
		String^ Param_Url,
		Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
		ICarenPropertyStore^ Param_Propriedades,
		[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (EndCreateObjectFromByteStream) - Conclui uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult EndCreateObjectFromByteStream
	(
		ICarenMFAsyncResult^ Param_Resultado,
		[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);

	/// <summary>
	/// (EndCreateObjectFromURL) - Conclui uma solicitação assíncrona para criar um objeto a partir de um URL.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
	/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
	/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult EndCreateObjectFromURL
	(
		ICarenMFAsyncResult^ Param_Resultado,
		[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
		ICaren^ Param_Out_FonteMidia
	);
};

