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
#include "CarenMFActivate.h"
#include "CarenMFClock.h"
#include "CarenMFTopology.h"
#include "CarenMFMediaEvent.h"

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
/// (Concluido - Fase de Testes) - Classe responsável por fornecer controles de reprodução para conteúdo protegido e desprotegido. A sessão de mídia e os objetos de sessão do caminho de mídia protegida (PMP) 
/// expõem essa classe(Interface).
/// </summary>
public ref class CarenMFMediaSession :public ICarenMFMediaSession
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaSession).
	IMFMediaSession* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenMFMediaSession();


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
	/// <param name="Param_Out_MediaSession">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMFMediaSession^% Param_Out_MediaSession)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_MediaSession = gcnew CarenMFMediaSession();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar uma sessão de midia não PMP.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface de atributos para adicionar configurações extras a criação da sessão de midia. Esse paramêtro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSession">Recebe um ponteiro para a interface de sessão de midia.</param>
	static CarenResult CriarInstancia(ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFMediaSession^% Param_Out_MediaSession)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//HResult
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas no método
		IMFAttributes* pAtributosAdicionais = NULL;
		IMFMediaSession* pMediaSession = NULL;

		//Verifica se especificou atributos e obtém a interface nativa
		if (Param_Atributos != nullptr)
		{
			//Recupera o ponteiro.
			Resultado = Param_Atributos->RecuperarPonteiro((LPVOID*)&pAtributosAdicionais);

			//Verifica o resultado
			if (Resultado.StatusCode != ResultCode::SS_OK)
			{
				//Falhou...

				//Sai do método
				goto Done;
			}
		}

		//Chama o método para realizar a operação
		Hr = MFCreateMediaSession(ObjetoValido(pAtributosAdicionais) ? pAtributosAdicionais : NULL, &pMediaSession);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//A operação falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface a ser retornada.
		Param_Out_MediaSession = gcnew CarenMFMediaSession();

		//Define o ponteiro
		Param_Out_MediaSession->AdicionarPonteiro(&pMediaSession);

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar uma sessão de midia PMP. 
	/// </summary>
	/// <param name="Param_Flags"></param>
	/// <param name="Param_Atributos">Uma interface de atributos para adicionar configurações extras a criação da sessão de midia. Esse paramêtro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSession">Recebe um ponteiro para a interface de sessão de midia. O chamador deve liberar a interface. Antes de liberar a última referência para a interface, 
	/// o chamador deve chamar o método(Shutdown).</param>	
	/// <param name="Param_Out_EnablerAtivador">Recebe um ponteiro para o ativador de objeto. Esse valor pode ser NULO. Se não NULO, o chamador deve liberar a interface.</param>
	static CarenResult CriarInstanciaPMP(CA_PMPSESSION_CREATION_FLAGS Param_Flags, ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFMediaSession^% Param_Out_MediaSession, [Out] ICarenMFActivate^% Param_Out_EnablerAtivador)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//HResult
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas no método
		IMFAttributes* pAtributosAdicionais = NULL;
		IMFMediaSession* pMediaSessionPMP = NULL;
		IMFActivate* pEnablerAtivador = NULL;
		MFPMPSESSION_CREATION_FLAGS FlagsCreateMediaSession = static_cast<MFPMPSESSION_CREATION_FLAGS>(Param_Flags);

		//Verifica se especificou atributos e obtém a interface nativa
		if (Param_Atributos != nullptr)
		{
			//Recupera o ponteiro.
			Resultado = Param_Atributos->RecuperarPonteiro((LPVOID*)& pAtributosAdicionais);

			//Verifica o resultado
			if (Resultado.StatusCode != ResultCode::SS_OK)
			{
				//Falhou...

				//Sai do método
				goto Done;
			}
		}

		//Chama o método para realizar a operação
		Hr = MFCreatePMPMediaSession(FlagsCreateMediaSession, ObjetoValido(pAtributosAdicionais) ? pAtributosAdicionais : NULL, &pMediaSessionPMP, &pEnablerAtivador);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//A operação falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface a ser retornada.
		Param_Out_MediaSession = gcnew CarenMFMediaSession();

		//Define o ponteiro
		Param_Out_MediaSession->AdicionarPonteiro(&pMediaSessionPMP);

		//Verifica se o ativador é valido e define
		if (ObjetoValido(pEnablerAtivador))
		{
			//Objeto é valido..

			//Cria a interface do ativador.
			Param_Out_EnablerAtivador = gcnew CarenMFActivate();

			//Define o ponteiro
			Param_Out_EnablerAtivador->AdicionarPonteiro(pEnablerAtivador);
		}
		else
		{
			//Define como NULO 
			Param_Out_EnablerAtivador = nullptr;
		}

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
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



	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// (ClearTopologies) - Limpa todas as apresentações que estão enfileiradas para reprodução na sessão de mídia.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento (MESessionTopologiesCleared).
	/// </summary>
	virtual CarenResult ClearTopologies();

	/// <summary>
	/// (Close) - Fecha a sessão de mídia e libera todos os recursos que ele está usando.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento(MESessionClosed) .
	/// </summary>
	virtual CarenResult Close();

	/// <summary>
	/// (GetClock) - Recupera o relógio de apresentação da sessão de mídia.
	/// </summary>
	/// <param name="Param_Out_Relogio">Recebe o ponteiro para o relogio de apresentação. O chamador deve liberar a interface.</param>
	virtual CarenResult GetClock([Out] ICarenMFClock^% Param_Out_Relogio);

	/// <summary>
	/// (GetFullTopology) - Obtém uma topologia da sessão de mídia.
	/// </summary>
	/// <param name="Param_Flags">Zero ou mais sinalizadores da enumeração CA_MESESSION_GETFULLTOPOLOGY_FLAGS .</param>
	/// <param name="Param_TopoId">O identificador da topologia. Este parâmetro será ignorado se o (Param_Flags) parâmetro contém o MFSESSION_GETFULLTOPOLOGY_CURRENT sinalizador.</param>
	/// <param name="Param_Out_TopologiaCompleta">Recebe um ponteiro para a topologia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetFullTopology(Enumeracoes::CA_MFSESSION_GETFULLTOPOLOGY_FLAGS Param_Flags, UInt64 Param_TopoId, [Out] ICarenMFTopology^% Param_Out_TopologiaCompleta);

	/// <summary>
	/// (GetSessionCapabilities) - Recupera os recursos da sessão de mídia, com base na apresentação atual.
	/// </summary>
	/// <param name="Param_Out_Recursos">Recebe um OU de bit ou de ZERO ou mais dos sinalizadores da enumeração(CA_RECURSOS_SESSAO_MIDIA).</param>
	virtual CarenResult GetSessionCapabilities([Out] Enumeracoes::CA_RECURSOS_SESSAO_MIDIA% Param_Out_Recursos);

	/// <summary>
	/// (Pause) - Pausa a sessão de mídia.
	/// Este método pausa o relógio de apresentação. Esse método é assíncrono.Quando a operação for concluída, a sessão de mídia enviará um evento MESessionPaused.
	/// </summary>
	virtual CarenResult Pause();

	/// <summary>
	/// (SetTopology) - Define uma topologia na sessão de mídia.
	/// </summary>
	/// <param name="Param_Flags">Os flags que determinam o comportamento do método.</param>
	/// <param name="Param_Topologia">Um ponteiro para a topologia a ser definida.</param>
	virtual CarenResult SetTopology(Enumeracoes::CA_MFSESSION_SETTOPOLOGY_FLAGS Param_Flags, ICarenMFTopology^ Param_Topologia);

	/// <summary>
	/// (Shutdown) - Desliga a sessão de mídia e libera todos os recursos usados pela sessão de mídia.
	/// Chame esse método quando você terminar de usar a sessão de mídia, antes da chamada final para ICaren::LiberarReferencia. Caso contrário, seu aplicativo irá vazar memória.
	/// </summary>
	virtual CarenResult Shutdown();

	/// <summary>
	/// (Start) - Inicia a sessão de mídia.
	/// Quando esse método é chamado, a sessão de mídia inicia o relógio de apresentação e começa a processar exemplos de mídia. Esse método é assíncrono. Quando o método for concluído, 
	/// a sessão de mídia envia o evento MESessionStarted.
	/// </summary>
	/// <param name="Param_GuidFormatoTempo">um GUID que especifica o formato de hora para o (Param_PosicaoInicio) parâmetro. Este parâmetro pode ser NULO. O valor NULO é equivalente 
	/// a passar em GUID_NULL.</param>
	/// <param name="Param_PosicaoInicio">Uma CA_PropVariant que especifica a posição inicial para reprodução. O significado e o tipo de dados desse parâmetro são indicados pelo 
	/// (Param_GuidFormatoTempo) parâmetro.</param>
	virtual CarenResult Start(String^ Param_GuidFormatoTempo, Estruturas::CA_PropVariant^ Param_PosicaoInicio);

	/// <summary>
	/// (Stop) - Interrompe a sessão de mídia.
	/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento MESessionStopped. 
	/// </summary>
	virtual CarenResult Stop();




	//Metodos da interface ICarenMFGeradorEventosMidia
public:
	/// <summary>
	/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
	/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
	/// dependerá do valor de Param_Flags.
	/// </summary>
	/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult GetEvent(Enumeracoes::CA_FLAGS_OBTER_EVENTO Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
	/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
	/// </summary>
	/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
	/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
	/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
	virtual CarenResult BeginGetEvent(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido);

	/// <summary>
	/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
	/// </summary>
	/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult EndGetEvent(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (QueueEvent) - Coloca um novo evento na fila do objeto.
	/// </summary>
	/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.GetType).</param>
	/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.GetExtendedType) do evento.</param>
	/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetStatus) do evento.</param>
	/// <param name="Param_Dados">uma CA_PropVariant que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetValue) do evento.</param>
	virtual CarenResult InserirEventoFila(Enumeracoes::CA_MediaEventType Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PropVariant^ Param_Dados);
};

