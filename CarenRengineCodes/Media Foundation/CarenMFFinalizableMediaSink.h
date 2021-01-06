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
#include "CarenMFPresentationClock.h"
#include "CarenMFActivate.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe opcionalmente suportada por sinks de mídia para executar tarefas necessárias antes do desligamento.
/// </summary>
public ref class CarenMFFinalizableMediaSink : public ICarenMFFinalizableMediaSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFFinalizableMediaSink).
	IMFFinalizableMediaSink* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFFinalizableMediaSink();
	
	~CarenMFFinalizableMediaSink();

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
			System::Console::WriteLine(String::Concat(ICarenMFFinalizableMediaSink::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenMFFinalizableMediaSink)
public:
	/// <summary>
	/// Notifica a mídia para tomar as medidas assíncronas que precisa para terminar suas tarefas.
	/// </summary>
	/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto assíncrono. O chamador deve implementar esta interface.</param>
	/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
	/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	virtual CarenResult BeginFinalize(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoEstado);

	/// <summary>
	/// Completa uma operação de finalização assíncrona.
	/// </summary>
	/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
	/// ICarenMFAsyncCallback::Invoke.</param>
	virtual CarenResult EndFinalize(ICarenMFAsyncResult^ Param_Resultado);


	//Métodos da interface (ICarenMFMediaSink)
public:
	/// <summary>
	/// Adiciona um novo coletor de fluxo para o coletor de mídia.
	/// O método retorna uma interface para o StreamSink adicionado.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">Um (Identificador) para o fluxo. O valor é (Arbitrário), mas deve ser exclusivo.</param>
	/// <param name="Param_TipoMidia">Uma interface com o tipo de mídia do Stream a ser adicionado. Esse valor pode ser (NULO).</param>
	/// <param name="Param_Out_FluxoSink">Retorna uma interface para o fluxo adicionado.</param>
	virtual CarenResult AddStreamSink(UInt32 Param_IdentificadorFluxo, ICarenMFMediaType^ Param_TipoMidia, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém as características do coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_Caracteristicas">Retorna as características desse (Coletor de mídia).</param>
	virtual CarenResult GetCharacteristics([Out] Enumeracoes::CA_MEDIASINK_CHARACTERISTICS% Param_Out_Caracteristicas);

	/// <summary>
	/// Obtém o relógio de apresentação que foi definido no coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_RelogioApresentação">Recebe a interface que contém o Relogio de Apresentação(IMFPresentationClock)</param>
	virtual CarenResult GetPresentationClock([Out] ICarenMFPresentationClock^% Param_Out_RelogioApresentação);

	/// <summary>
	/// Obtém um coletor de fluxo, especificado pelo identificador de fluxo.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">O Identificador para o fluxo a ser obtido.</param>
	/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o Stream Sink requisitado pelo seu (Identificador)</param>
	virtual CarenResult GetStreamSinkById(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém um coletor de fluxo, especificado por index.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o coletor de fluxo a ser obtido.</param>
	/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o coletor de fluxo requisitado.</param>
	virtual CarenResult GetStreamSinkByIndex(UInt32 Param_IdFluxo, [Out] ICarenMFStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém o número de coletores de fluxo neste coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_QuantidadeSinks">Retorna a quantidade de (Coletores de Fluxos) presente nesse (Coletor de mídia)</param>
	virtual CarenResult GetStreamSinkCount([Out] UInt32% Param_Out_QuantidadeSinks);

	/// <summary>
	/// Remove um coletor de fluxo do coletor de mídia.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">O Identificador do fluxo a ser removido.</param>
	virtual CarenResult RemoveStreamSink(UInt32 Param_IdentificadorFluxo);

	/// <summary>
	/// Define o relógio de apresentação no coletor de mídia.
	/// </summary>
	/// <param name="Param_RelogioApresentação">A interface que contém o relógio de apresentação a ser definido.
	/// O valor pode ser (NULO). Se NULL, o (Coletor de Mídia) para de escutar o relógio de apresentação
	/// que foi definido anteriormente, se houver.</param>
	virtual CarenResult SetPresentationClock(ICarenMFPresentationClock^ Param_RelogioApresentação);

	/// <summary>
	/// Desliga o coletor de mídia e libera os recursos que ele está usando.
	/// </summary>
	virtual CarenResult Shutdown();
};