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
#include "../NativeClassForEvents/CLN_WicBitmapProgress.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos usados para notificação de progresso para codificadores e decodificadores. 
/// </summary>
public ref class CarenWICBitmapCodecProgressNotification : public ICarenWICBitmapCodecProgressNotification
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapCodecProgressNotification).
	IWICBitmapCodecProgressNotification* PonteiroTrabalho = NULL;

	//Ponteiro para classe auxiliar que recebe os eventos de notificação.
	CLN_WicBitmapProgress* pWicBitmapProgresClass = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapCodecProgressNotification();
	
	~CarenWICBitmapCodecProgressNotification();


	//Conversões implicitas
public:
	static operator CarenWICBitmapCodecProgressNotification^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICBitmapCodecProgressNotification^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICBitmapCodecProgressNotification();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICBitmapCodecProgressNotification*>(Param_Pointer.ToPointer());

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

	//Eventos
public:
	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////


	/// <summary>
	/// Evento chamado para notificar o progresso de decoficação ou codificação.
	/// </summary>
	virtual event ICarenWICBitmapCodecProgressNotification::Delegate_OnProgressNotification^ OnProgressNotification;



	//Delegates para uso nativo.
private:

	///////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_WicBitmapProgress)//
	///////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnProgressNotification) nativo da classe (CLN_WicBitmapProgress) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnProgressNotification(__RPC__in LPVOID pvData, ULONG uFrameNum, WICProgressOperation operation, double dblProgress);
	DelegateNativo_Evento_OnProgressNotification^ Callback_OnProgressNotification = nullptr;


	//Handles alocadas de cada Delegate.
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnProgressNotification).
	/// </summary>
	GCHandle gHandle_Delegate_OnProgressNotification;


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
			System::Console::WriteLine(String::Concat(ICarenWICBitmapCodecProgressNotification::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICBitmapCodecProgressNotification)
public:
	/// <summary>
	/// Registra uma função de retorno de chamada de notificação de progresso. Permite que o usuário implemente seu proprio retorno de chamada sem precisar usar o evento disponivel nessa classe.
	/// Os aplicativos só podem registrar um único retorno de chamada. As chamadas de registro subsequentes substituirão o retorno de chamada previamente registrado. Para não registrar 
	/// um retorno de chamada, passe no NULO ou registre uma nova função de retorno de chamada. O progresso é relatado em uma ordem crescente entre 0,0 e 1.0. Se o (Param_FlagsProgresso) 
	/// incluir o WICProgressNotificationBegin, o retorno de chamada é garantido para ser chamado com o progresso 0.0. Se o (Param_FlagsProgresso) incluir o WICProgressNotificationEnd, 
	/// o retorno de chamada é garantido para ser chamado com o progresso 1.0. WICProgressNotificaçãoFrequent aumenta a frequência em que o retorno de chamada é chamado. Se uma operação 
	/// for esperada para levar mais de 30 segundos, o WICProgressNotificationFrequent deve ser adicionado ao (Param_FlagsProgresso).
	/// </summary>
	/// <param name="Param_Callback">Uma interface(ICaren) que contém um ponteiro de função para a função de chamada de notificação de progresso definida pelo aplicativo.</param>
	/// <param name="Param_ComponenteData">Uma interface(ICaren) que contém um ponteiro para componente de dados para o método de retorno de chamada.</param>
	/// <param name="Param_FlagsProgresso">As bandeiras CA_WICProgressOperation e CA_WICProgressNotification para uso para notificação de progresso.</param>
	virtual CarenResult RegisterProgressNotification(
	ICaren^ Param_Callback,
	ICaren^ Param_ComponenteData,
	UInt32 Param_FlagsProgresso);

	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();


internal:
	virtual HRESULT EncaminharEvento_OnProgressNotification(
		__RPC__in LPVOID pvData,
		ULONG uFrameNum,
		WICProgressOperation operation,
		double dblProgress);
};