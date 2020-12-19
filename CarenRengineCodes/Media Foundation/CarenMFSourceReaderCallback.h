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
#include "../Nativas/CLN_IMFSourceReaderCallback.h"
#include "../Caren/Caren.h"
#include "CarenMFMediaEvent.h"
#include "CarenMFSample.h"
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
/// Classe responsável por conter os eventos gerados pelo Leitor de Midia(ICarenMFSourceReader).
/// </summary>
public ref class CarenMFSourceReaderCallback : public ICarenMFSourceReaderCallback
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceReaderCallback).
	IMFSourceReaderCallback* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	~CarenMFSourceReaderCallback();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que contém o valor da propriedade (ColetarEventLixo)
	Boolean Prop_ColetarEventLixo = false;

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

	/// <summary>
	/// Propriedade que vai força  o coletor de lixo agir para liberar interfaces em conclusões de eventos.
	/// </summary>
	property Boolean ColetarLixoEvento
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_ColetarEventLixo;
		}

		virtual void set(Boolean value)
		{
			//Define o valor.
			Prop_ColetarEventLixo = value;
		}
	}


	//Eventos
public:
	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////


	/// <summary>
	/// Evento chamado quando o método (ICarenMFSourceReader.ReadAmostraAsync) é concluido.
	/// </summary>
	virtual event ICarenMFSourceReaderCallback::Delegate_OnReadSample^ OnReadSample;

	/// <summary>
	/// Evento chamado quando o método (ICarenMFSourceReader.Flush) é completado.
	/// </summary>
	virtual event ICarenMFSourceReaderCallback::Delegate_OnFlush^ OnFlush;

	/// <summary>
	/// Evento chamado quando o Leitor de Midia recebe determinados eventos da Fonte de Midia.
	/// </summary>
	virtual event ICarenMFSourceReaderCallback::Delegate_OnEvent^ OnEvent;


	//Delegates para uso nativo.
private:

	/////////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_IMFSourceReaderCallback)//
	/////////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnReadSample) nativo da classe (CLN_IMFSourceReaderCallback) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnReadSample(HRESULT Param_HResultStatus, DWORD Param_FluxoID, DWORD Param_FluxoFlgs, LONGLONG Param_TimeSpanAmostra, IMFSample* Param_AmostraMidia);
	DelegateNativo_Evento_OnReadSample^ Callback_OnReadSample = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnEvent) nativo da classe (CLN_IMFSourceReaderCallback) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnEvent(DWORD Param_FluxoID, IMFMediaEvent *Param_pEvento);
	DelegateNativo_Evento_OnEvent^ Callback_OnEvent = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFlush) nativo da classe (CLN_IMFSourceReaderCallback) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFlush(DWORD Param_FluxoID);
	DelegateNativo_Evento_OnFlush^ Callback_OnFlush = nullptr;


	//Handles alocadas de cada Delegate.
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnReadSample).
	/// </summary>
	GCHandle gHandle_Delegate_OnReadSample;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnEvent).
	/// </summary>
	GCHandle gHandle_Delegate_OnEvent;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFlush).
	/// </summary>
	GCHandle gHandle_Delegate_OnFlush;




	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Cria uma instância da interface responsável por notificar os eventos ocorrridos com o leitor de mídia.
	/// </summary>
	/// <param name="Param_Out_Callback">Recebe a interface que possui a classe de notificação de eventos.</param>
	static CarenResult CriarInstanciaCallback([Out] ICarenMFSourceReaderCallback^% Param_Out_Callback)
	{
		//Variavel que vai retornar o resultado do método.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		CLN_IMFSourceReaderCallback *pPonteiroCallback = NULL;

		//Cria o ponteiro da classe nativa
		pPonteiroCallback = new CLN_IMFSourceReaderCallback();

		//Cria a interface a ser retornada.
		Param_Out_Callback = gcnew CarenMFSourceReaderCallback();

		//Define o ponteiro nativo na interface.
		Param_Out_Callback->AdicionarPonteiro(pPonteiroCallback);

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

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


	//Métodos que recebem os eventos da classe nativa (CLN_IMFSourceReaderCallback)
public:
	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnReadSample) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnReadSample(HRESULT Param_HResultStatus, DWORD Param_FluxoID, DWORD Param_FluxoFlgs, LONGLONG Param_TimeSpanAmostra, IMFSample* Param_pAmostraMidia);

	/// <summary>
	///Método responsável por encaminhar o (Evento) nativo (OnEvent) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnEvent(DWORD Param_FluxoID, IMFMediaEvent *Param_pEvento);

	/// <summary>
	/// Método responsável por encaminhar o (Evento) nativo (OnFlush) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFlush(DWORD Param_FluxoID);
};

