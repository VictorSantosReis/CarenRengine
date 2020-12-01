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
#include "CarenMFPresentationTimeSource.h"
#include "../SDK_Utilidades.h"

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
/// [Concluido - Fase de testes] - Falta documentar.
/// </summary>
public ref class CarenMFPresentationClock : public ICarenMFPresentationClock
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFPresentationClock).
	IMFPresentationClock* PonteiroTrabalho = NULL;

	//Destruidor.
public:
	~CarenMFPresentationClock();

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
	/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface solicitada.</param>
	static CarenResult CriarInstancia([Out] ICarenMFPresentationClock^% Param_Out_InterfaceSolicitada)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		IMFPresentationClock *pRelogioPresentation = NULL;
		ICarenMFPresentationClock^ InterfaceSolicitada = nullptr;
		
		//Chama o método para criar o relogio de apresentação.
		Hr = MFCreatePresentationClock(&pRelogioPresentation);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Sai do método
			goto Done;
		}

		//Cria a interface que vai receber o ponteiro
		InterfaceSolicitada = gcnew CarenMFPresentationClock();

		//Chama o método para definir o ponteiro
		InterfaceSolicitada->AdicionarPonteiro(pRelogioPresentation);

		//Define a interface no parametro de retorno.
		Param_Out_InterfaceSolicitada = InterfaceSolicitada;

		//Deifne sucesso na operação
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
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();





	//Métodos da interface ICarenMFPresentationClock
public:
	/// <summary>
	/// Registra um objeto para ser notificado sempre que o relógio inicia, para, ou faz uma pausa ou muda a taxa.
	/// </summary>
	/// <param name="Param_InterfaceNotification">A interface que contém o objeto de notificação de eventos do Relógio.</param>
	virtual CarenResult AddClockStateSink(ICarenMFClockStateSink^ Param_InterfaceNotification);

	/// <summary>
	/// Recupera a hora mais recente.
	/// </summary>
	/// <param name="Param_Out_NsHoraRelogio">Recebe a hora do relógio atual em unidades de 100 nanosegundos.</param>
	virtual CarenResult GetTime([Out] Int64% Param_Out_NsHoraRelogio);

	/// <summary>
	/// Recupera a fonte de tempo de apresentação do relógio.
	/// </summary>
	/// <param name="Param_Out_TimeSource">Recebe a interface que contém a Fonte de apreentação do relógio.</param>
	virtual CarenResult GetTimeSource([Out] ICarenMFPresentationTimeSource^% Param_Out_TimeSource);

	/// <summary>
	/// Pausa o tempo de apresentação. Enquanto o relógio está em pausa, o tempo do relógio não adianta,
	/// e (GetTime) do relógio retorna o tempo em que o relógio foi pausado.
	/// </summary>
	virtual CarenResult Pause();

	/// <summary>
	/// Cancela o registro de um objeto que está recebendo notificações de alteração de estado do relógio.
	/// </summary>
	/// <param name="Param_InterfaceNotification">Cancela o registro de notificação do relógio presente na interface de eventos.</param>
	virtual CarenResult RemoveClockStateSink(ICarenMFClockStateSink^ Param_InterfaceNotification);

	/// <summary>
	/// Define a fonte de tempo para o tempo de apresentação. A fonte de tempo é o objeto que 
	/// impulsiona o relógio, fornecendo a hora atual.
	/// </summary>
	/// <param name="Param_TimeSource">Define o tempo na fonte de tempo do relógio de apresentação.</param>
	virtual CarenResult SetTimeSource(ICarenMFPresentationTimeSource^ Param_TimeSource);

	/// <summary>
	/// Começa o tempo de apresentação.
	/// </summary>
	/// <param name="Param_PosiçãoInicio">A posição ou tempo de partida inicial do relógio. O valor deve ser expressados em 
	/// unidades de 100 nanosegundos. Se (Param_PosiçãoAtual) for True, desconsidere esse valor.</param>
	/// <param name="Param_PosiçãoAtual">Define se deve iniciar a parti da posição atual. O valor de (Param_PosiçãoInicio) é desconsiderado
	/// se esse valor for True.</param>
	virtual CarenResult Start(Int64 Param_PosiçãoInicio, Boolean Param_PosiçãoAtual);

	/// <summary>
	/// Para o relógio de apresentação. Enquanto o relógio estiver parado, não adianta a hora do relógio e 
	/// (GetTime) método do relógio retorna zero.
	/// </summary>
	virtual CarenResult Stop();




	//Métodos da interface (ICarenMFClock)
public:
	/// <summary>
	/// Recupera as características do relógio.
	/// </summary>
	/// <param name="Param_Out_CaracteristicasClock">Recebe os flags com as características do relógio.</param>
	virtual CarenResult GetClockCharacteristics([Out] Enumeracoes::CA_CLOCK_CARACTERISTICAS% Param_Out_CaracteristicasClock);

	/// <summary>
	/// (Não Suportado) - Recupera a chave de continuidade do relógio.
	/// </summary>
	/// <param name="Param_Out_Chave">Recebe a chave de continuidade.</param>
	virtual CarenResult GetContinuityKey([Out] UInt32% Param_Out_Chave);

	/// <summary>
	/// Recupera a hora do último relógio que foi correlacionada com a hora do sistema.
	/// </summary>
	/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
	/// <param name="Param_Out_ClockTime">Recebe o último tempo de relógio conhecido, em unidades de freqüência do relógio.</param>
	/// <param name="Param_NsSystemTime">Recebe a hora do sistema que corresponde ao tempo de relógio retornado em Param_Out_ClockTime, em unidades de 100 nanosegundos.</param>
	virtual CarenResult GetCorrelatedTime(UInt32 Param_ValorReservado, [Out] Int64% Param_Out_ClockTime, [Out] Int64% Param_NsSystemTime);

	/// <summary>
	/// Recupera as propriedades do relógio.
	/// </summary>
	/// <param name="Param_Out_PropriedadesRelogio">Retorna a estrutura que contém as propriedades do relógio atual.</param>
	virtual CarenResult GetProperties([Out] Estruturas::CA_MFCLOCK_PROPERTIES^% Param_Out_PropriedadesRelogio);

	/// <summary>
	/// Recupera o estado atual do relógio.
	/// </summary>
	/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
	/// <param name="Param_Out_EstadoRelogio">Retorna o valor da enumeração que define o estado atual do relógio.</param>
	virtual CarenResult GetState(UInt32 Param_ValorReservado, [Out] Enumeracoes::CA_CLOCK_ESTADO% Param_Out_EstadoRelogio);
};

