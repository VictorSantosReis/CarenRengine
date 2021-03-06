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
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenDXGIAdapter.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por fornecer métodos atualizados para oferecer e recuperar recursos.
/// </summary>
public ref class CarenDXGIDevice4 : public ICarenDXGIDevice4
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIDevice4).
	IDXGIDevice4* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenDXGIDevice4();

	~CarenDXGIDevice4();


	//Conversões implicitas
public:
	static operator CarenDXGIDevice4^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenDXGIDevice4^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenDXGIDevice4();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IDXGIDevice4*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenDXGIDevice4::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenDXGIDevice4)
public:
	/// <summary>
	/// (OfferResources1) - Permite que o sistema operacional liberte a memória de vídeo dos recursos, incluindo tanto descartar o conteúdo quanto descomprometer a memória.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
	/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
	/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
	/// <param name="Param_Flags">Especifica o DXGI_OFFER_RESOURCE_FLAGS.</param>
	virtual CarenResult OfferResources1(
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade,
		CA_DXGI_OFFER_RESOURCE_FLAGS Param_Flags);

	/// <summary>
	/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice4::OfferResources.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Resultado) conjuntos de argumentos.</param>
	/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
	/// <param name="Param_Ref_Resultado">Uma matriz que recebe valores da enumeração CA_DXGI_RECLAIM_RESOURCE_RESULTS. Cada valor na matriz corresponde a um recurso 
	/// no mesmo índice que o parâmetro (Param_Recursos) especifica. O chamador pode passar em NULO, se o chamador pretende preencher os recursos com novos conteúdos, 
	/// independentemente de o conteúdo antigo ter sido descartado.</param>
	virtual CarenResult ReclaimResources1(
		Int32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		cli::array<CA_DXGI_RECLAIM_RESOURCE_RESULTS>^% Param_Ref_Resultado);


	//Métodos da interface(ICarenDXGIDevice3)
public:
	/// <summary>
	/// (Trim) - Apara a memória gráfica alocada pelo dispositivo DXGI ICarenDXGIDevice3 em nome do aplicativo.
	/// Para aplicativos que renderizam com o DirectX, os drivers gráficos alocam periodicamente buffers de memória interna, a fim de acelerar as solicitações de 
	/// renderização subsequentes. Essas alocações de memória contam com o uso de memória do aplicativo para PLM e, em geral, levam ao aumento do uso da memória pelo 
	/// sistema geral.
	/// A partir do Windows 8.1, os aplicativos que renderizam com Direct2D e/ou Direct3D (incluindo interop CoreWindow e XAML) devem ligar para trim em resposta ao 
	/// (PLM suspend callback.). O tempo de execução Direct3D e o driver gráfico descartarão buffers de memória interna alocados para o aplicativo, reduzindo sua pegada 
	/// de memória.
	/// Semelhante ao ICarenD3D11DeviceContext::Flush, os aplicativos devem ligar para ICarenD3D11DeviceContext::ClearState antes de ligar para (Trim). ClearState limpa as 
	/// ligações de gasodutos Direct3D, garantindo que o Direct3D não tenha referências aos objetos Direct3D que você está tentando liberar.
	/// </summary>
	virtual CarenResult Trim();


	//Métodos da interface(ICarenDXGIDevice2)
public:
	/// <summary>
	/// (EnqueueSetEvent) - Libera quaisquer comandos de renderização pendentes e define o objeto de evento especificado para o estado sinalizado depois de todos os 
	/// comandos de renderização previamente enviados completos.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento. Todos os tipos de objetos de evento (manual-reset, auto-reset e assim por diante) são suportados. 
	/// A Handle deve ter a bandeira de direito de acesso (EVENT_MODIFY_STATE).</param>
	virtual CarenResult EnqueueSetEvent(ICarenWindowsEvent^ Param_HandleEvento);

	/// <summary>
	/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos descartando seu conteúdo.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
	/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
	/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
	virtual CarenResult OfferResources(
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade);

	/// <summary>
	/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice2::OfferResources.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Descartado) conjuntos de argumentos.</param>
	/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
	/// <param name="Param_Ref_Descartado">Uma matriz que recebe valores booleanos. Cada valor na matriz corresponde a um recurso no mesmo índice que o parâmetro 
	/// (Param_Recursos) especifica. O tempo de execução define cada valor booleano para TRUE se o conteúdo do recurso correspondente foi descartado e agora estiver 
	/// indefinido, ou para FALSE se o conteúdo antigo do recurso correspondente ainda estiver intacto. O chamador pode passar NULO, se o chamador pretende preencher 
	/// os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
	virtual CarenResult ReclaimResources(
		Int32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		cli::array<bool>^% Param_Ref_Descartado);


	//Métodos da interface(ICarenDXGIDevice1)
public:
	/// <summary>
	/// (GetMaximumFrameLatency) - Obtém o número de quadros(Frames) que o sistema pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_Out_LatenciaMaxima">Esse valor é definido para o número de quadros que podem ser enfileirados para renderização. Esse valor está 
	/// inadimplente em 3, mas pode variar de 1 a 16.</param>
	virtual CarenResult GetMaximumFrameLatency([Out] UInt32% Param_Out_LatenciaMaxima);

	/// <summary>
	/// (SetMaximumFrameLatency) - Define o número de quadros que o sistema pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_LatenciaMaxima">O número máximo de quadros de buffer traseiro que um motorista pode fazer fila. O valor está inadimplente a 3, mas pode 
	/// variar de 1 a 16. Um valor de 0 redefinirá a latência ao padrão. Para dispositivos (per-head), esse valor é especificado por cabeça(Head).</param>
	virtual CarenResult SetMaximumFrameLatency(UInt32 Param_LatenciaMaxima);

	//Métodos da interface(ICarenDXGIDevice)
public:
	/// <summary>
	/// (CreateSurface)(Não é implementado) - Este método é usado internamente e você não deve chamá-lo diretamente em sua aplicação.
	/// </summary>
	virtual CarenResult CreateSurface();

	/// <summary>
	/// (GetAdapter) - Retorna o adaptador para o dispositivo especificado.
	/// </summary>
	/// <param name="Param_Out_Adaptador">Retorna um ponteiro para a interface(ICarenDXGIAdapter) do adaptador.</param>
	virtual CarenResult GetAdapter([Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (GetGPUThreadPriority) - Retorna a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Out_Prioridade">recebe um valor que indica a prioridade atual da Thread GPU. O valor será entre -7 e 7, inclusive, onde 0 representa prioridade normal.</param>
	virtual CarenResult GetGPUThreadPriority([Out] int% Param_Out_Prioridade);

	/// <summary>
	/// (QueryResourceResidency) - Obtém o status de residência de uma série de recursos.
	/// As informações devolvidas pelo conjunto de argumentos (Param_Ref_StatusResidencia) descrevem o status de residência no momento em que o método 
	/// (QueryResourceResidency) foi chamado. 
	/// [O status de residência mudará constantemente.]
	/// Se você ligar para o método (QueryResourceResidency) durante um estado removido do dispositivo, o argumento (Param_Ref_StatusResidencia) devolverá 
	/// a bandeira CA_DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY.
	/// </summary>
	/// <param name="Param_ArrayRecursos">Um array que contém uma série de interfaces(ICarenDXGIResource) a serem obtido o status de residência.</param>
	/// <param name="Param_Ref_StatusResidencia">Um Array que vai conter o status de residência(ResidencyStatus) de cada recurso no parametro(Param_ArrayRecursos).</param>
	/// <param name="Param_QuantidadeRecursos">A quantidade de elementos no array de recursos.</param>
	virtual CarenResult QueryResourceResidency(
		cli::array<ICarenDXGIResource^>^ Param_ArrayRecursos,
		cli::array<CA_DXGI_RESIDENCY>^% Param_Ref_StatusResidencia,
		UInt32 Param_QuantidadeRecursos);

	/// <summary>
	/// (SetGPUThreadPriority) - Define a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Prioridade">Um valor que especifica a prioridade necessária da Thread da GPU. Esse valor deve ser entre -7 e 7, inclusive, onde 0 representa 
	/// prioridade normal.</param>
	virtual CarenResult SetGPUThreadPriority(int Param_Prioridade);


	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// Define uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};