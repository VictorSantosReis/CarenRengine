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
#include "CarenMFMediaEngine.h"
#include "CarenMFMediaTimeRange.h"
#include "CarenMFMediaError.h"
#include "CarenMFMediaKeys.h"
#include "CarenMFMediaSourceExtension.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por estender a interface ICarenMFMediaEngineClassFactory.
/// </summary>
public ref class CarenMFMediaEngineClassFactoryEx : public ICarenMFMediaEngineClassFactoryEx
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaEngineClassFactoryEx).
	IMFMediaEngineClassFactoryEx* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaEngineClassFactoryEx();
	
	~CarenMFMediaEngineClassFactoryEx();


	//Conversões implicitas
public:
	static operator CarenMFMediaEngineClassFactoryEx^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFMediaEngineClassFactoryEx^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFMediaEngineClassFactoryEx();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFMediaEngineClassFactoryEx*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFMediaEngineClassFactoryEx::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFMediaEngineClassFactoryEx)
public:
	/// <summary>
	/// Cria um objeto de teclas de mídia com base no sistema de teclas especificado.
	/// </summary>
	/// <param name="Param_SystemKey">O sistema de chaves de mídia.</param>
	/// <param name="Param_CmdStorePath">Uma string que aponta para um local para armazenar dados do Módulo de Descriptografia de Conteúdo (MDL) que podem ser 
	/// bloqueados por vários processos e, portanto, podem ser incompatíveis com a suspensão do aplicativo da loja.</param>
	/// <param name="Param_Out_MediaKeys">Retorna um ponteiro para a interface de chaves da mídia.</param>
	virtual CarenResult CreateMediaKeys(
	String^ Param_SystemKey,
	String^ Param_CmdStorePath,
	[Out] ICarenMFMediaKeys^% Param_Out_MediaKeys);

	/// <summary>
	/// Cria uma instância do ICarenMFMediaSourceExtension.
	/// </summary>
	/// <param name="Param_Flags">Este parâmetro é reservado e deve ser definido como 0.</param>
	/// <param name="Param_Atributos">Os atributos para criação da extensão da fonte de midia.</param>
	/// <param name="Param_Out_ExtensaoFonteMidia">Retorna um ponteiro para a interface de extensão da fonte de mídia criada.</param>
	virtual CarenResult CreateMediaSourceExtension(
	UInt32 Param_Flags, 
	ICarenMFAttributes^ Param_Atributos, 
	[Out] ICarenMFMediaSourceExtension^% Param_Out_ExtensaoFonteMidia);

	/// <summary>
	/// Obtém um valor que indica se o sistema de tecla especificado suporta o tipo de mídia especificado.
	/// </summary>
	/// <param name="Param_MIMEType">O tipo MIME para verificar o suporte.</param>
	/// <param name="Param_SystemKey">O sistema-chave para verificar o suporte.</param>
	/// <param name="Param_Out_Suporte">Retorna TRUE se o tipo for suportado por (Param_SystemKey); caso contrário, FALSE.</param>
	virtual CarenResult IsTypeSupported(
	String^ Param_MIMEType,
	String^ Param_SystemKey,
	[Out] Boolean% Param_Out_Suporte);


	//Métodos da interface(ICarenMFMediaEngineClassFactory)
public:
	/// <summary>
	/// Cria um objeto de erro de mídia.
	/// </summary>
	/// <param name="Param_Out_MediaError">Retorna uma interface (ICarenMFMediaError) que contém o potneiro para um novo objeto de erro.</param>
	virtual CarenResult CreateError([Out] ICarenMFMediaError^% Param_Out_MediaError);

	/// <summary>
	/// Cria uma nova instância do Media Engine.
	/// </summary>
	/// <param name="Param_Flags">Um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_CREATEFLAGS.</param>
	/// <param name="Param_Atributos">Um ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos. Consulte a estrutura GUIDs_MFAtributes_MediaEngine
	/// para os atributos disponiveis para a Media Engine.</param>
	/// <param name="Param_Out_MediaEngine">Recebe um ponteiro para a interface ICarenMFMediaEngine. O chamador deve liberar a interface.</param>
	virtual CarenResult CreateInstance(
		CA_MF_MEDIA_ENGINE_CREATEFLAGS Param_Flags,
		ICarenMFAttributes^ Param_Atributos,
		[Out] ICarenMFMediaEngine^% Param_Out_MediaEngine);

	/// <summary>
	/// Cria um objeto de intervalo de tempo.
	/// </summary>
	/// <param name="Param_Out_TimeRange">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
	virtual CarenResult CreateTimeRange([Out] ICarenMFMediaTimeRange^% Param_Out_TimeRange);
};