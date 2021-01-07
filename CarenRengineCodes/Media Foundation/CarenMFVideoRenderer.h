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
#include "CarenMFActivate.h"
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
/// Classe responsável por representar o EVR(Renderizador de Video Aprimorado).
/// </summary>
public ref class CarenMFVideoRenderer : public ICarenMFVideoRenderer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFVideoRenderer).
	IMFVideoRenderer* PonteiroTrabalho = NULL;

	//Construtor e Destruidor.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFVideoRenderer();

	~CarenMFVideoRenderer();


	//Conversões implicitas
public:
	static operator CarenMFVideoRenderer^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFVideoRenderer^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFVideoRenderer();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFVideoRenderer*>(Param_Pointer.ToPointer());

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

	//Cria uma instância dessa classe (Estático)
public:

	/// <summary>
	/// Método responsável por criar uma instância da classe atual.
	/// </summary>
	/// <param name="Param_IID_VideoRender">O GUID para a interface de serviço solictada.</param>
	/// <param name="Param_Out_VideoRender">Recebe a interface do renderizador de Vídeo.</param>
	static CarenResult CriarInstanciaVideoRender(String^ Param_IID_VideoRender, [Out] CarenMFVideoRenderer^% Param_Out_VideoRender)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas pelo método
		LPVOID *pVideoRender = NULL;
		CarenMFVideoRenderer^ InterfaceVideoRender = nullptr;
		Utilidades Util;
		GUID GuidService = GUID_NULL;

		//Chama o método para obter o guid.
		GuidService = Util.CreateGuidFromString(Param_IID_VideoRender);

		//Verifica se o guid foi criado com sucesso
		if (GuidService == GUID_NULL)
		{
			//O guid informado não é valido
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//Sai do método.
			goto Done;
		}

		//Chama o método que vai criar o Renderizador de Vídeo.
		Hr = MFCreateVideoRenderer(GuidService, (LPVOID*)&pVideoRender);
		
		//Verifica o resultado do método
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define que houve falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro.
		InterfaceVideoRender = gcnew CarenMFVideoRenderer();

		//Chama o método para definir o ponteiro de trablho.
		InterfaceVideoRender->AdicionarPonteiro(pVideoRender);

		//Define a interface criada no parametro de saida.
		Param_Out_VideoRender = InterfaceVideoRender;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar um objeto de ativação do Renderizador de Vídeo.
	/// </summary>
	/// <param name="Param_HandleVideoSuperfice">A handle para a superfice que vai conter o video a ser renderizado.</param>
	/// <param name="Param_Out_VideoRenderAtivador">Recebe a interface de ativação do objeto.</param>
	static CarenResult CriarInstanciaVideoRender(IntPtr Param_HandleVideoSuperfice, [Out] ICarenMFActivate^% Param_Out_VideoRenderAtivador)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas pelo método
		IMFActivate *pVideoRenderActivate = NULL;
		ICarenMFActivate^ InterfaceVideoRenderAtivador = nullptr;
		HWND HandleVideoSuperfice = NULL;
		Utilidades Util;
		
		//Chama o método para obter a handle nativa da janela que vai conter a renderização do vídeo.
		HandleVideoSuperfice = Util.ConverterIntPtrToHWND(Param_HandleVideoSuperfice);

		//Chama o método que vai criar o objeto de ativação do Renderizador.
		Hr = MFCreateVideoRendererActivate(HandleVideoSuperfice, &pVideoRenderActivate);

		//Verifica o resultado do método
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define que houve falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro.
		InterfaceVideoRenderAtivador = gcnew CarenMFActivate();

		//Chama o método para definir o ponteiro de trablho.
		InterfaceVideoRenderAtivador->AdicionarPonteiro(pVideoRenderActivate);

		//Define a interface criada no parametro de saida.
		Param_Out_VideoRenderAtivador = InterfaceVideoRenderAtivador;

		//Define sucesso na operação
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
			System::Console::WriteLine(String::Concat(ICarenMFVideoRenderer::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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





	//Métodos da interface (CarenMFVideoRenderer)
public:
	/// <summary>
	/// Define um novo mixer ou apresentador para o Processador de Vídeo Avançado(EVR).
	/// </summary>
	/// <param name="Param_VideoMixer">Ponteiro para a interface (IMFTransform) do mixer para usar. Este parâmetro pode ser (NULO). Se este parâmetro for (NULO), 
	/// o EVR usa seu misturador padrão.</param>
	/// <param name="Param_Apresentador">Ponteiro para a interface (IMFVideoPresenter) do apresentador para usar. Este parâmetro pode ser (NULO). Se este parâmetro 
	/// for NULL, o EVR usa seu apresentador padrão.</param>
	virtual CarenResult InitializeRenderer(ICarenMFTransform^ Param_VideoMixer, ICarenMFVideoPresenter^ Param_Apresentador);
};

