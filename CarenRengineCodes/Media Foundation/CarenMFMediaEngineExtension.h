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

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por habilitar um aplicativo para carregar recursos de mídia no Media Engine. 
/// </summary>
public ref class CarenMFMediaEngineExtension : public ICarenMFMediaEngineExtension
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaEngineExtension).
	IMFMediaEngineExtension* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFMediaEngineExtension();
	
	~CarenMFMediaEngineExtension();


	//Conversões implicitas
public:
	static operator CarenMFMediaEngineExtension^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFMediaEngineExtension^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFMediaEngineExtension();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFMediaEngineExtension*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenMFMediaEngineExtension::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFMediaEngineExtension)
public:
	/// <summary>
	/// Começa uma solicitação assíncrona para criar um fluxo de byteou uma fonte de mídia.
	/// </summary>
	/// <param name="Param_Url">A URL do recurso de mídia.</param>
	/// <param name="Param_FluxoBytes">Um ponteiro para a interface ICarenMFByteStream.</param>
	/// <param name="Param_Tipo">Um membro da enumeração CA_MF_OBJECT_TYPE que especifica qual tipo de objeto criar.</param>
	/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro para a interface IUnknown. Este ponteiro pode ser usado para cancelar a operação assíncrona, 
	/// passando o ponteiro para o método ICarenMFMediaEngineExtension::CancelarCriacaoObjeto.</param>
	/// <param name="Param_Callback">Um ponteiro para a interface ICarenMFAsyncCallback. Esta interface é usada para sinalizar a conclusão da operação assíncrona.</param>
	/// <param name="Param_ObjetoEstado">Um ponteiro para um objeto de estado implementado pelo usuário. Você pode usar este objeto para conter informações do estado
	/// para o retorno de chamada. O objeto é devolvido ao chamador quando o retorno de chamada é invocado. Este parâmetro pode ser NULO.</param>
	virtual CarenResult BeginCreateObject(
	String^ Param_Url,
	ICarenMFByteStream^ Param_FluxoBytes,
	CA_MF_OBJECT_TYPE Param_Tipo,
	[Out] ICaren^% Param_Out_CookieCancelamento,
	ICarenMFAsyncCallback^ Param_Callback,
	ICaren^ Param_ObjetoEstado);

	/// <summary>
	/// Cancela a solicitação atual para criar um objeto.
	/// </summary>
	/// <param name="Param_CookieCancelamento">O ponteiro que foi devolvido no parâmetro (Param_Out_CookieCancelamento) do método ICarenMFMediaEngineExtension::CriarObjetoAsync.</param>
	virtual CarenResult CancelCreateObject(ICaren^ Param_CookieCancelamento);

	/// <summary>
	/// Verifica se o objeto pode carregar um tipo especificado de recurso de mídia.
	/// </summary>
	/// <param name="Param_AudioOnly">Se TRUE, o Media Engine será configurado para o modo somente áudio. Caso contrário, o Media Engine está configurado para o 
	/// modo áudio-vídeo.</param>
	/// <param name="Param_MimeType">Uma sequência que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
	/// <param name="Param_Out_Resultado">Recebe um membro da enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
	virtual CarenResult CanPlayType(
	Boolean Param_AudioOnly,
	String^ Param_MimeType,
	[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_Resultado);

	/// <summary>
	/// Completa uma solicitação assíncrona para criar um fluxo de byteou fonte de mídia.
	/// </summary>
	/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult.</param>
	/// <param name="Param_Ref_Objeto">Recebe um ponteiro para interface do Media Source ou Byte Stream de acordo com o solicitado. Esse paramêtro não pode ser NULO. 
	/// O usuário é responsável por liberar a interface.</param>
	virtual CarenResult EndCreateObject(
	ICarenMFAsyncResult^ Param_Resultado,
	ICaren^% Param_Ref_Objeto);
};