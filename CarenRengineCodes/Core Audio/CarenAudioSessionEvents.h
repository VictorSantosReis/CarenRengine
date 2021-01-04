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
#include "../SDK_CoreAudio.h"
#include "../Caren/Caren.h"
#include "../NativeClassForEvents/CLN_IAudioSessionEvents.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da WSAPI.
using namespace CarenRengine::CoreAudio;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por fornecer notificações de eventos relacionados à sessão de áudio, como alterações no nível de volume, nome para exibição e estado da sessão.
/// </summary>
public ref class CarenAudioSessionEvents : public ICarenAudioSessionEvents
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IAudioSessionEvents).
	IAudioSessionEvents* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a interface e permite que o usuário decida se a biblioteca deve criar a interface ou vai iniciar sem um ponteiro 
	/// de trabalho. Se (Param_CriarInterface) for TRUE, o construtor vai criar uma implementação da interface ().
	/// </summary>
	/// <param name="Param_CriarInterface">Um valor booleano, TRUE indica que deve criar uma nova interface intermanete, caso contario, FALSE.</param>
	CarenAudioSessionEvents(Boolean Param_CriarInterface);

	~CarenAudioSessionEvents();


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
	/// O evento notifica o cliente que o nível de volume de um canal de áudio no submix de sessão foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnChannelVolumeChanged^ OnChannelVolumeChanged;

	/// <summary>
	/// O evento notifica o cliente que o nome de exibição para a sessão foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnDisplayNameChanged^ OnDisplayNameChanged;

	/// <summary>
	/// O evento notifica o cliente que o parâmetro de agrupamento para a sessão foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnGroupingParamChanged^ OnGroupingParamChanged;

	/// <summary>
	/// O evento notifica o cliente que o ícone de exibição para a sessão foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnIconPathChanged^ OnIconPathChanged;

	/// <summary>
	/// O evento notifica o cliente que a sessão de áudio foi desconectado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnSessionDisconnected^ OnSessionDisconnected;

	/// <summary>
	/// O evento notifica o cliente que o nível de volume ou o estado muting da sessão de áudio foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnSimpleVolumeChanged^ OnSimpleVolumeChanged;

	/// <summary>
	/// O evento notifica o cliente que o estado de atividade de fluxo da sessão foi alterado.
	/// </summary>
	virtual event ICarenAudioSessionEvents::Delegate_OnStateChanged^ OnStateChanged;



	//(DELEGATES).
private:

	////////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER OS EVENTOS NATIVOS DA CLASSE (CLN_IAudioSessionEvents)//
	////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnChannelVolumeChanged) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnChannelVolumeChanged(DWORD, float[], DWORD, LPCGUID);
	DelegateNativo_Evento_OnChannelVolumeChanged^ Callback_OnChannelVolumeChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDisplayNameChanged) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnDisplayNameChanged(LPCWSTR, LPCGUID);
	DelegateNativo_Evento_OnDisplayNameChanged^ Callback_OnDisplayNameChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnGroupingParamChanged) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnGroupingParamChanged(LPCGUID, LPCGUID);
	DelegateNativo_Evento_OnGroupingParamChanged^ Callback_OnGroupingParamChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnIconPathChanged) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnIconPathChanged(LPCWSTR, LPCGUID);
	DelegateNativo_Evento_OnIconPathChanged^ Callback_OnIconPathChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSessionDisconnected ) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnSessionDisconnected(AudioSessionDisconnectReason);
	DelegateNativo_Evento_OnSessionDisconnected^ Callback_OnSessionDisconnected = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnSimpleVolumeChange) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnSimpleVolumeChanged(float, BOOL, LPCGUID);
	DelegateNativo_Evento_OnSimpleVolumeChanged^ Callback_OnSimpleVolumeChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnStateChanged) nativo da classe (CLN_IAudioSessionEvents) para ser enviado ao usuário.
	/// </summary>
	delegate int DelegateNativo_Evento_OnStateChanged(AudioSessionState);
	DelegateNativo_Evento_OnStateChanged^ Callback_OnStateChanged = nullptr;




	//(HANDLES ALOCADAS DOS EVENTOS)
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnChannelVolumeChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnChannelVolumeChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDisplayNameChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnDisplayNameChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnGroupingParamChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnGroupingParamChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnIconPathChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnIconPathChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSessionDisconnected).
	/// </summary>
	GCHandle gHandle_Delegate_OnSessionDisconnected;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnSimpleVolumeChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnSimpleVolumeChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnStateChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnStateChanged;


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




	//Métodos da interface(ICarenAudioSessionEvents)
public:
	//Métodos que registram e deletam os dados dos eventos.

	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarEventos();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarEventos).
	/// </summary>
	virtual void CancelarRegistro();


	//Métodos que são utilizados para receberem os eventos da classe nativa (CLN_IAudioSessionEvents).
public:
	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnSimpleVolumeChanged(float NewVolume,  BOOL NewMute, LPCGUID EventContext);

	/// <summary>
	/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
	/// </summary>
	virtual int EncaminharEvento_OnStateChanged(AudioSessionState NewState);
};