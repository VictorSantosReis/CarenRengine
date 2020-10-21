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
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "CarenDXGIAdapter.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::DXGI;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por implementar uma classe derivada para objetos DXGI que produzem dados de imagem. A interface expõe métodos para bloquear 
/// o processamento da CPU até que a GPU complete o processamento e ofereça recursos ao sistema operacional.
/// </summary>
public ref class CarenDXGIDevice2 : public ICarenDXGIDevice2
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDXGIDevice2).
	IDXGIDevice2* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenDXGIDevice2();


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
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenDXGIDevice2">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenDXGIDevice2^% Param_Out_CarenDXGIDevice2)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenDXGIDevice2 = gcnew CarenDXGIDevice2();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
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


	//Métodos da interface(ICarenDXGIDevice2)
public:
	/// <summary>
	/// (EnqueueSetEvent) - Libera quaisquer comandos de renderização pendentes e define o objeto de evento especificado para o estado sinalizado depois de todos os 
	/// comandos de renderização previamente enviados completos.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento. Todos os tipos de objetos de evento (manual-reset, auto-reset e assim por diante) são suportados. 
	/// A Handle deve ter a bandeira de direito de acesso (EVENT_MODIFY_STATE).</param>
	virtual CarenResult EnqueueDefinirEvento(ICarenWindowsEvent^ Param_HandleEvento);

	/// <summary>
	/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos descartando seu conteúdo.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
	/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
	/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
	virtual CarenResult OfertarRecursos(
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade);

	/// <summary>
	/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice2::OfertarRecursos.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Descartado) conjuntos de argumentos.</param>
	/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
	/// <param name="Param_Ref_Descartado">Uma matriz que recebe valores booleanos. Cada valor na matriz corresponde a um recurso no mesmo índice que o parâmetro 
	/// (Param_Recursos) especifica. O tempo de execução define cada valor booleano para TRUE se o conteúdo do recurso correspondente foi descartado e agora estiver 
	/// indefinido, ou para FALSE se o conteúdo antigo do recurso correspondente ainda estiver intacto. O chamador pode passar NULO, se o chamador pretende preencher 
	/// os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
	virtual CarenResult RecuperarRecursos(
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
	virtual CarenResult ObterLatenciaMaximaFrame([Out] UInt32% Param_Out_LatenciaMaxima);

	/// <summary>
	/// (SetMaximumFrameLatency) - Define o número de quadros que o sistema pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_LatenciaMaxima">O número máximo de quadros de buffer traseiro que um motorista pode fazer fila. O valor está inadimplente a 3, mas pode 
	/// variar de 1 a 16. Um valor de 0 redefinirá a latência ao padrão. Para dispositivos (per-head), esse valor é especificado por cabeça(Head).</param>
	virtual CarenResult DefinirLatenciaMaximaFrame(UInt32 Param_LatenciaMaxima);

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
	virtual CarenResult ObterAdaptador([Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (GetGPUThreadPriority) - Retorna a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Out_Prioridade">recebe um valor que indica a prioridade atual da Thread GPU. O valor será entre -7 e 7, inclusive, onde 0 representa prioridade normal.</param>
	virtual CarenResult ObterPrioridadeThreadGPU([Out] int% Param_Out_Prioridade);

	/// <summary>
	/// (QueryResourceResidency) - Obtém o status de residência de uma série de recursos.
	/// As informações devolvidas pelo conjunto de argumentos (Param_Ref_StatusResidencia) descrevem o status de residência no momento em que o método 
	/// (ObterStatusResidenciaRecurso) foi chamado. 
	/// [O status de residência mudará constantemente.]
	/// Se você ligar para o método (ObterStatusResidenciaRecurso) durante um estado removido do dispositivo, o argumento (Param_Ref_StatusResidencia) devolverá 
	/// a bandeira CA_DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY.
	/// </summary>
	/// <param name="Param_ArrayRecursos">Um array que contém uma série de interfaces(ICarenDXGIResource) a serem obtido o status de residência.</param>
	/// <param name="Param_Ref_StatusResidencia">Um Array que vai conter o status de residência(ResidencyStatus) de cada recurso no parametro(Param_ArrayRecursos).</param>
	/// <param name="Param_QuantidadeRecursos">A quantidade de elementos no array de recursos.</param>
	virtual CarenResult ObterStatusResidenciaRecurso(
		cli::array<ICarenDXGIResource^>^ Param_ArrayRecursos,
		cli::array<CA_DXGI_RESIDENCY>^% Param_Ref_StatusResidencia,
		UInt32 Param_QuantidadeRecursos);

	/// <summary>
	/// (SetGPUThreadPriority) - Define a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Prioridade">Um valor que especifica a prioridade necessária da Thread da GPU. Esse valor deve ser entre -7 e 7, inclusive, onde 0 representa 
	/// prioridade normal.</param>
	virtual CarenResult DefinrPrioridadeThreadGPU(int Param_Prioridade);


	//Métodos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// (GetParent) - Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterPaiObjeto(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// (SetPrivateData) - Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	virtual CarenResult DefinirDadosPrivados(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados);

	/// <summary>
	/// (GetPrivateData) - Obtém um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar
	/// a referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult ObterDadosPrivados(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados);

	/// <summary>
	/// (SetPrivateDataInterface) - Defina uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	virtual CarenResult DefinirDadosPrivadosInterface(String^ Param_GuidInterface, ICaren^ Param_Interface);
};