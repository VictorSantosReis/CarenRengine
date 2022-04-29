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


#include "../pch.h"
#include "CarenAudioSessionEvents.h"


//Destruidor.
CarenAudioSessionEvents::~CarenAudioSessionEvents()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioSessionEvents::CarenAudioSessionEvents(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Cria a implementação da interface
		PonteiroTrabalho = new CLN_IAudioSessionEvents();
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenAudioSessionEvents::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionEvents::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionEvents*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionEvents**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionEvents::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionEvents*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionEvents**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionEvents::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionEvents::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioSessionEvents::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioSessionEvents::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenAudioSessionEvents::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioSessionEvents::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioSessionEvents::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioSessionEvents::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioSessionEvents();
}





//
// Métodos da interface proprietária(ICarenAudioSessionEvents)
//

/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenAudioSessionEvents::RegistrarEventos()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnChannelVolumeChanged = gcnew DelegateNativo_Evento_OnChannelVolumeChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnChannelVolumeChanged);
	Callback_OnDisplayNameChanged = gcnew DelegateNativo_Evento_OnDisplayNameChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnDisplayNameChanged);
	Callback_OnGroupingParamChanged = gcnew DelegateNativo_Evento_OnGroupingParamChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnGroupingParamChanged);
	Callback_OnIconPathChanged = gcnew DelegateNativo_Evento_OnIconPathChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnIconPathChanged);
	Callback_OnSessionDisconnected = gcnew DelegateNativo_Evento_OnSessionDisconnected(this, &CarenAudioSessionEvents::EncaminharEvento_OnSessionDisconnected);
	Callback_OnSimpleVolumeChanged = gcnew DelegateNativo_Evento_OnSimpleVolumeChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnSimpleVolumeChanged);
	Callback_OnStateChanged = gcnew DelegateNativo_Evento_OnStateChanged(this, &CarenAudioSessionEvents::EncaminharEvento_OnStateChanged);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnChannelVolumeChanged = Util.ConverterDelegateToPointer(Callback_OnChannelVolumeChanged);
	IntPtr Pointer_OnDisplayNameChanged = Util.ConverterDelegateToPointer(Callback_OnDisplayNameChanged);
	IntPtr Pointer_OnGroupingParamChanged = Util.ConverterDelegateToPointer(Callback_OnGroupingParamChanged);
	IntPtr Pointer_OnIconPathChanged = Util.ConverterDelegateToPointer(Callback_OnIconPathChanged);
	IntPtr Pointer_OnSessionDisconnected = Util.ConverterDelegateToPointer(Callback_OnSessionDisconnected);
	IntPtr Pointer_OnSimpleVolumeChanged = Util.ConverterDelegateToPointer(Callback_OnSimpleVolumeChanged);
	IntPtr Pointer_OnStateChanged = Util.ConverterDelegateToPointer(Callback_OnStateChanged);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnChannelVolumeChanged = Util.AlocarPointerDelegate(Pointer_OnChannelVolumeChanged);
	gHandle_Delegate_OnDisplayNameChanged = Util.AlocarPointerDelegate(Pointer_OnDisplayNameChanged);
	gHandle_Delegate_OnGroupingParamChanged = Util.AlocarPointerDelegate(Pointer_OnGroupingParamChanged);
	gHandle_Delegate_OnIconPathChanged = Util.AlocarPointerDelegate(Pointer_OnIconPathChanged);
	gHandle_Delegate_OnSessionDisconnected = Util.AlocarPointerDelegate(Pointer_OnSessionDisconnected);
	gHandle_Delegate_OnSimpleVolumeChanged = Util.AlocarPointerDelegate(Pointer_OnSimpleVolumeChanged);
	gHandle_Delegate_OnStateChanged = Util.AlocarPointerDelegate(Pointer_OnStateChanged);

	//Registra os delegates criados para os delegates nativo na classe CLN_IAudioSessionEvents que envia os eventos.
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnChannelVolumeChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnChannelVolumeChanged>(Pointer_OnChannelVolumeChanged);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnDisplayNameChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnDisplayNameChanged>(Pointer_OnDisplayNameChanged);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnGroupingParamChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnGroupingParamChanged>(Pointer_OnGroupingParamChanged);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnIconPathChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnIconPathChanged>(Pointer_OnIconPathChanged);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSessionDisconnected = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnSessionDisconnected>(Pointer_OnSessionDisconnected);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSimpleVolumeChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnSimpleVolumeChanged>(Pointer_OnSimpleVolumeChanged);
	((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnStateChanged = Util.ConverterPointerDelegateToNativeDelegate<CLN_IAudioSessionEvents_EventoNativo_OnStateChanged>(Pointer_OnStateChanged);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarEventos).
/// </summary>
void CarenAudioSessionEvents::CancelarRegistro()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnChannelVolumeChanged.Free();
	gHandle_Delegate_OnDisplayNameChanged.Free();
	gHandle_Delegate_OnGroupingParamChanged.Free();
	gHandle_Delegate_OnIconPathChanged.Free();
	gHandle_Delegate_OnSessionDisconnected.Free();
	gHandle_Delegate_OnSimpleVolumeChanged.Free();
	gHandle_Delegate_OnStateChanged.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnChannelVolumeChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnChannelVolumeChanged = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnDisplayNameChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnDisplayNameChanged = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnGroupingParamChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnGroupingParamChanged = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnIconPathChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnIconPathChanged = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSessionDisconnected))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSessionDisconnected = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSimpleVolumeChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnSimpleVolumeChanged = NULL;
	}

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnStateChanged))
	{
		//Descarta o delegate.
		((CLN_IAudioSessionEvents*)PonteiroTrabalho)->Evento_OnStateChanged = NULL;
	}
}


//
//MÉTODOS QUE ENCAMINHAM O EVENTO NATIVO PARA O CLIENTE GERENCIADO.
//

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext)
{
	//Variaveis.
	Utilidades Util;
	cli::array<float>^ VolumesArray= gcnew cli::array<float>(ChannelCount);
	pin_ptr<float> Data_VolumesArrays = &VolumesArray[0];
	String^ GuidContextoEvento = nullptr;

	//Copia os dados para a memoria nativa que está fixada a memoria gerenciada.
	memcpy_s(Data_VolumesArrays, ChannelCount, NewChannelVolumeArray, ChannelCount);

	//Obtém o Guid do contexto do evento se ele não for nulo.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidContextoEvento = Util.ConverterGuidToString(*EventContext);
	}

	//Invoca e retorna o resultado do evento.
	return OnChannelVolumeChanged(ChannelCount, VolumesArray, ChangedChannel, GuidContextoEvento);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext)
{
	//Variaveis
	Utilidades Util;
	String^ NovoNomeVisivel = nullptr;
	String^ GuidContextoEvento = nullptr;

	//Obtém o novo nome
	NovoNomeVisivel = gcnew String(NewDisplayName);

	//Obtém o Guid do contexto do evento se ele não for nulo.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidContextoEvento = Util.ConverterGuidToString(*EventContext);
	}

	//Invoca e retorna o resultado do evento.
	return OnDisplayNameChanged(NovoNomeVisivel, GuidContextoEvento);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext)
{
	//Variaveis
	Utilidades Util;
	String^ GuidParametroAgrupamento = nullptr;
	String^ GuidContextoEvento = nullptr;

	//Obtém o novo guid do parametro de agrupamento se valido.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidParametroAgrupamento = Util.ConverterGuidToString(*NewGroupingParam);
	}

	//Obtém o Guid do contexto do evento se ele não for nulo.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidContextoEvento = Util.ConverterGuidToString(*EventContext);
	}

	//Invoca e retorna o resultado do evento.
	return OnGroupingParamChanged(GuidParametroAgrupamento, GuidContextoEvento);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext)
{
	//Variaveis
	Utilidades Util;
	String^ UrlIcone = nullptr;
	String^ GuidContextoEvento = nullptr;

	//Obtém a Url se ela for valida.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		UrlIcone = gcnew String(NewIconPath);
	}

	//Obtém o Guid do contexto do evento se ele não for nulo.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidContextoEvento = Util.ConverterGuidToString(*EventContext);
	}

	//Invoca e retorna o resultado do evento.
	return OnIconPathChanged(UrlIcone, GuidContextoEvento);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason)
{
	//Variavel que vai conter a enumeração da desconexao.
	CA_RAZAO_DESCONEXAO_SESSAO_AUDIO RazaoDesconexao = static_cast<CA_RAZAO_DESCONEXAO_SESSAO_AUDIO>(DisconnectReason);

	//Invoca e retorna o resultado do evento.
	return OnSessionDisconnected(RazaoDesconexao);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnSimpleVolumeChanged(float NewVolume, BOOL NewMute, LPCGUID EventContext)
{
	//Variaveis
	Utilidades Util;
	Boolean EstadoMudo = NewMute;
	String^ GuidContextoEvento = nullptr;

	//Obtém o Guid do contexto do evento se ele não for nulo.
	if (ObjetoValido(EventContext))
	{
		//Converte o guid para string
		GuidContextoEvento = Util.ConverterGuidToString(*EventContext);
	}

	//Invoca e retorna o resultado do evento.
	return OnSimpleVolumeChanged(NewVolume, EstadoMudo, GuidContextoEvento);
}

/// <summary>
/// Método responsável por chamar o evento gerenciado para notificar o usuário sobre uma chamada para o método () na classe nativa.
/// </summary>
int CarenAudioSessionEvents::EncaminharEvento_OnStateChanged(AudioSessionState NewState)
{
	//Obtém o novo estado da sessão.
	CA_ESTADO_SESSAO_AUDIO NovoEstadoSessao = static_cast<CA_ESTADO_SESSAO_AUDIO>(NewState);

	//Chama e retorna o resultado.
	return OnStateChanged(NovoEstadoSessao);
}