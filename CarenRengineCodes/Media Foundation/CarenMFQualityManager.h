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
#include "../NativeClassForEvents/CLN_IMFQualityManager.h"
#include "CarenMFSample.h"
#include "CarenMFTopology.h"
#include "CarenMFTopologyNode.h"
#include "CarenMFMediaEvent.h"
#include "CarenMFPresentationClock.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por ajustar a qualidade de reprodução. Esta interface é exposta pelo gerenciador de qualidade.
/// </summary>
public ref class CarenMFQualityManager : public ICarenMFQualityManager
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFQualityManager).
	IMFQualityManager* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa e cria a classe com uma implementação da interface nativa (IMFQualityManager) criada internamente ou Nulo.
	/// </summary>
	/// <param name="Param_CreateType">Um valor da enumeração (CA_MF_QUALITY_MANAGER_CREATE_TYPE) que informa como deve ser criado a classe.</param>
	CarenMFQualityManager(CA_MF_QUALITY_MANAGER_CREATE_TYPE Param_CreateType);
	
	~CarenMFQualityManager();

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
	/// Evento chamado quando a Sessão de Mídia seleciona um relógio de apresentação.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_NotifyPresentationClock^ OnNotifyPresentationClock;
	/// <summary>
	/// Evento chamado quando o processador de mídia está prestes a fornecer uma amostra de entrada para um componente de pipeline.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_NotifyProcessInput^ OnNotifyProcessInput;
	/// <summary>
	/// Evento chamado após o processador de mídia receber uma amostra de saída de um componente de pipeline.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_NotifyProcessOutput^ OnNotifyProcessOutput;
	/// <summary>
	/// Evento chamado quando um componente de pipeline envia um evento MEQualityNotify.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_NotifyQualityEvent^ OnNotifyQualityEvent;
	/// <summary>
	/// Evento chamado quando a Media Session está prestes a começar a tocar uma nova topologia.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_NotifyTopology^ OnNotifyTopology;
	/// <summary>
	/// Evento chamado quando a Sessão de Mídia está sendo encerrada.
	/// </summary>
	virtual event ICarenMFQualityManager::Delegate_Shutdown^ OnShutdown;

	//(DELEGATES).
private:

	//////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER OS EVENTOS NATIVOS DA CLASSE (CLN_IMFQualityManager)//
	//////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(NotifyPresentationClock) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnNotifyPresentationClock(IMFPresentationClock*);
	DelegateNativo_Evento_OnNotifyPresentationClock^ Callback_OnNotifyPresentationClock = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(NotifyProcessInput) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnNotifyProcessInput(
		IMFTopologyNode*,
		long,
		IMFSample*);
	DelegateNativo_Evento_OnNotifyProcessInput^ Callback_OnNotifyProcessInput = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(NotifyProcessOutput) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnNotifyProcessOutput(
		IMFTopologyNode*,
		long,
		IMFSample*);
	DelegateNativo_Evento_OnNotifyProcessOutput^ Callback_OnNotifyProcessOutput = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(NotifyQualityEvent) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnNotifyQualityEvent(
		IUnknown* pObject,
		IMFMediaEvent* pEvent);
	DelegateNativo_Evento_OnNotifyQualityEvent^ Callback_OnNotifyQualityEvent = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(NotifyTopology) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnNotifyTopology(IMFTopology*);
	DelegateNativo_Evento_OnNotifyTopology^ Callback_OnNotifyTopology = nullptr;
	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(Shutdown) nativo da classe (CLN_IMFQualityManager) para ser enviado ao usuário.
	/// </summary>
	delegate HRESULT DelegateNativo_Evento_OnShutdown();
	DelegateNativo_Evento_OnShutdown^ Callback_OnShutdown = nullptr;


	//(HANDLES ALOCADAS DOS EVENTOS)
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnNotifyPresentationClock).
	/// </summary>
	GCHandle gHandle_Delegate_OnNotifyPresentationClock;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnNotifyProcessInput).
	/// </summary>
	GCHandle gHandle_Delegate_OnNotifyProcessInput;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnNotifyProcessOutput).
	/// </summary>
	GCHandle gHandle_Delegate_OnNotifyProcessOutput;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnNotifyQualityEvent).
	/// </summary>
	GCHandle gHandle_Delegate_OnNotifyQualityEvent;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnNotifyTopology).
	/// </summary>
	GCHandle gHandle_Delegate_OnNotifyTopology;
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnShutdown).
	/// </summary>
	GCHandle gHandle_Delegate_OnShutdown;



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


	//Métodos da interface(ICarenMFQualityManager)
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();




	//Métodos que são utilizados para receberem os eventos da classe nativa ().
public:
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (NotifyTopology) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnNotifyTopology(IMFTopology* pTopology);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (NotifyPresentationClock) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnNotifyPresentationClock(IMFPresentationClock* pClock);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (NotifyProcessInput) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnNotifyProcessInput(
		IMFTopologyNode* pNode,
		long lInputIndex,
		IMFSample* pSample);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (NotifyProcessOutput) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnNotifyProcessOutput(
		IMFTopologyNode* pNode,
		long lOutputIndex,
		IMFSample* pSample);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (NotifyQualityEvent) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnNotifyQualityEvent(
		IUnknown* pObject,
		IMFMediaEvent* pEvent);
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método (Shutdown) na classe nativa.
	/// </summary>
	virtual HRESULT EncaminharEvento_OnShutdown();
};