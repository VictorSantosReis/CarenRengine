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
#include "../Caren/Caren.h"
#include "../SDK_CoreAudio.h"
#include "../Nativas/CLN_IMMNotificationClient.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Core Audio Api
using namespace CarenRengine::CoreAudio;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// Classe responsável por chamar eventos de notificação sobre um determinado dispositivo de áudio a qual a interface foi vinculada.
/// </summary>
public ref class CarenMMNotificationClient : public ICarenMMNotificationClient
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface.
	IMMNotificationClient* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenMMNotificationClient();


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


	//Cria instância da classe atual.
public:
	/// <summary>
	/// Cria uma instância vazia da classe de notificação de dispositivos de áudio.
	/// </summary>
	/// <param name="Param_Out_Interface">Retorna a interface vazia. Chamadas para está interface vai resultar em exceção
	/// se nenhum ponteiro for definido.</param>
	static CarenResult CriarInstanciaVazia([Out] CarenMMNotificationClient^% Param_Out_Interface)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface e retorna ao usuário.
		Param_Out_Interface = gcnew CarenMMNotificationClient();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
		return Resultado;
	}



	//Eventos
public:
	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////

	/// <summary>
	/// O evento notifica o cliente que o dispositivo de ponto de extremidade de áudio padrão para uma função de dispositivo específico foi alterado.
	/// </summary>
	virtual event ICarenMMNotificationClient::Delegate_OnDefaultDeviceChanged^ OnDefaultDeviceChanged;

	/// <summary>
	/// O evento notifica que um novo dispositivo de ponto de extremidade de áudio foi adicionado.
	/// </summary>
	virtual event ICarenMMNotificationClient::Delegate_OnDeviceAdded^ OnDeviceAdded;

	/// <summary>
	/// O evento notifica que um dispositivo de ponto de extremidade de áudio foi removido.
	/// </summary>
	virtual event ICarenMMNotificationClient::Delegate_OnDeviceRemoved^ OnDeviceRemoved;

	/// <summary>
	/// O evento notifica que o estado de um dispositivo de ponto de extremidade de áudio foi alterado.
	/// </summary>
	virtual event ICarenMMNotificationClient::Delegate_OnDeviceStateChanged^ OnDeviceStateChanged;

	/// <summary>
	/// O evento notifica que o valor de uma propriedade pertencente a um dispositivo de ponto de extremidade de áudio foi alterado.
	/// </summary>
	virtual event ICarenMMNotificationClient::Delegate_OnPropertyValueChanged^ OnPropertyValueChanged;


	//Delegates para uso nativo.
private:

	///////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_IMMNotificationClient)//
	///////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDefaultDeviceChanged) nativo da classe (CLN_IMMNotificationClient) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDefaultDeviceChanged(_In_ EDataFlow flow, _In_ ERole role, _In_ LPCWSTR pwstrDefaultDeviceId);
	DelegateNativo_Evento_OnDefaultDeviceChanged^ Callback_OnDefaultDeviceChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDeviceAdded) nativo da classe (CLN_IMMNotificationClient) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDeviceAdded(_In_ LPCWSTR pwstrDeviceId);
	DelegateNativo_Evento_OnDeviceAdded^ Callback_OnDeviceAdded = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDeviceRemoved) nativo da classe (CLN_IMMNotificationClient) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDeviceRemoved(_In_ LPCWSTR pwstrDeviceId);
	DelegateNativo_Evento_OnDeviceRemoved^ Callback_OnDeviceRemoved = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnDeviceStateChanged) nativo da classe (CLN_IMMNotificationClient) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnDeviceStateChanged(_In_ LPCWSTR pwstrDeviceId, _In_ DWORD dwNewState);
	DelegateNativo_Evento_OnDeviceStateChanged^ Callback_OnDeviceStateChanged = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnPropertyValueChanged) nativo da classe (CLN_IMMNotificationClient) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnPropertyValueChanged(_In_ LPCWSTR pwstrDeviceId, _In_ const PROPERTYKEY key);
	DelegateNativo_Evento_OnPropertyValueChanged^ Callback_OnPropertyValueChanged = nullptr;


	//Handles alocadas de cada Delegate.
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDefaultDeviceChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnDefaultDeviceChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDeviceAdded).
	/// </summary>
	GCHandle gHandle_Delegate_OnDeviceAdded;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDeviceRemoved).
	/// </summary>
	GCHandle gHandle_Delegate_OnDeviceRemoved;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnDeviceStateChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnDeviceStateChanged;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnPropertyValueChanged).
	/// </summary>
	GCHandle gHandle_Delegate_OnPropertyValueChanged;



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




	//Métodos da interface proprietaria.
public:
	/// <summary>
	/// Método responsável por registrar os eventos da interface.
	/// </summary>
	virtual void RegistrarCallback();

	/// <summary>
	/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
	/// </summary>
	virtual void UnRegisterCallback();



	//Métodos que recebem os eventos da classe nativa ()
public:
	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDefaultDeviceChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDefaultDeviceChanged(_In_ EDataFlow flow, _In_ ERole role, _In_ LPCWSTR pwstrDefaultDeviceId);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDeviceAdded) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDeviceAdded(_In_ LPCWSTR pwstrDeviceId);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDeviceRemoved) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDeviceRemoved(_In_ LPCWSTR pwstrDeviceId);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnDeviceStateChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnDeviceStateChanged(_In_ LPCWSTR pwstrDeviceId, _In_ DWORD dwNewState);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnPropertyValueChanged) da classe (CLN_IMMNotificationClient) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnPropertyValueChanged(_In_ LPCWSTR pwstrDeviceId, _In_ const PROPERTYKEY key);
};