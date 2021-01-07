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
#include "../NativeClassForEvents/CLN_IMFSourceBufferNotify.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por fornecer funcionalidades para chamar eventos associados ao ICarenMFSourceBuffer. 
/// </summary>
public ref class CarenMFSourceBufferNotify : public ICarenMFSourceBufferNotify
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceBufferNotify).
	IMFSourceBufferNotify* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe com uma implementação da interface nativa (IMFSourceBufferNotify) criada internamente.
	/// </summary>
	CarenMFSourceBufferNotify();
	
	~CarenMFSourceBufferNotify();


	//Conversões implicitas
public:
	static operator CarenMFSourceBufferNotify^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFSourceBufferNotify^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFSourceBufferNotify();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFSourceBufferNotify*>(Param_Pointer.ToPointer());

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


	//(EVENTOS)
public:

	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////

	/// <summary>
	/// Evento chamado para indicar que o buffer de origem começou a ser atualizado.
	/// </summary>
	virtual event ICarenMFSourceBufferNotify::Delegate_OnUpdateStart^ OnUpdateStart;
	/// <summary>
	/// Evento chamado para indicar que o buffer de origem foi abortado.
	/// </summary>
	virtual event ICarenMFSourceBufferNotify::Delegate_OnAbort^ OnAbort;
	/// <summary>
	/// Evento chamado para indicar que ocorreu um erro com o buffer de origem.
	/// </summary>
	virtual event ICarenMFSourceBufferNotify::Delegate_OnError^ OnError;
	/// <summary>
	/// Evento chamado para indicar que o buffer de origem está sendo atualizado.
	/// </summary>
	virtual event ICarenMFSourceBufferNotify::Delegate_OnUpdate^ OnUpdate;
	/// <summary>
	/// Evento chamado para indicar que o buffer de origem terminou de atualizar.
	/// </summary>
	virtual event ICarenMFSourceBufferNotify::Delegate_OnUpdateEnd^ OnUpdateEnd;


	//(DELEGATES).
private:

	//////////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER OS EVENTOS NATIVOS DA CLASSE (CLN_IMFSourceBufferNotify)//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnUpdateStart) nativo da classe (CLN_IMFSourceBufferNotify) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnUpdateStart();
	DelegateNativo_Evento_OnUpdateStart^ Callback_OnUpdateStart = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnAbort) nativo da classe (CLN_IMFSourceBufferNotify) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnAbort();
	DelegateNativo_Evento_OnAbort^ Callback_OnAbort = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnError) nativo da classe (CLN_IMFSourceBufferNotify) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnError(_In_ HRESULT);
	DelegateNativo_Evento_OnError^ Callback_OnError = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnUpdate) nativo da classe (CLN_IMFSourceBufferNotify) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnUpdate();
	DelegateNativo_Evento_OnUpdate^ Callback_OnUpdate = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnUpdateEnd) nativo da classe (CLN_IMFSourceBufferNotify) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnUpdateEnd();
	DelegateNativo_Evento_OnUpdateEnd^ Callback_OnUpdateEnd = nullptr;

	//(HANDLES ALOCADAS DOS EVENTOS)
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnUpdateStart).
	/// </summary>
	GCHandle gHandle_Delegate_OnUpdateStart;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnAbort).
	/// </summary>
	GCHandle gHandle_Delegate_OnAbort;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnError).
	/// </summary>
	GCHandle gHandle_Delegate_OnError;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnUpdate).
	/// </summary>
	GCHandle gHandle_Delegate_OnUpdate;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnUpdateEnd).
	/// </summary>
	GCHandle gHandle_Delegate_OnUpdateEnd;

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
			System::Console::WriteLine(String::Concat(ICarenMFSourceBufferNotify::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFSourceBufferNotify)
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();

	//Métodos que são utilizados para receberem os eventos da classe nativa (CLN_IMFSourceBufferNotify).
public:
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (OnUpdateStart) na classe nativa.
	/// </summary>
	virtual void EncaminharEvento_OnUpdateStart();
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (OnAbort) na classe nativa.
	/// </summary>
	virtual void EncaminharEvento_OnAbort();
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (OnError) na classe nativa.
	/// </summary>
	virtual void EncaminharEvento_OnError(_In_ HRESULT hr);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (OnUpdate) na classe nativa.
	/// </summary>
	virtual void EncaminharEvento_OnUpdate();
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (OnUpdateEnd) na classe nativa.
	/// </summary>
	virtual void EncaminharEvento_OnUpdateEnd();
};