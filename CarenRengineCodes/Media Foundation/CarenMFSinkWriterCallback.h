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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "../Nativas/CLN_IMFSinkWriterCallback.h"

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
/// (Concluido - Fase de Testes) - Classe responsável por conter os eventos chamados pelo coletor de Gravador para notificar o usuário sobre a conclusão
/// dos métodos assincronos (Finalizar e PlaceMarker).
/// </summary>
public ref class CarenMFSinkWriterCallback :public ICarenMFSinkWriterCallback
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFAttributes).
	IMFSinkWriterCallback* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a interface e permite que o usuário decida se a biblioteca deve criar a interface ou vai iniciar sem um ponteiro 
	/// de trabalho. Se (Param_CriarInterface) for TRUE, o construtor vai criar uma implementação interna da (IMFSinkWriterCallback).
	/// </summary>
	/// <param name="Param_CriarInterface">Um valor booleano, TRUE indica que deve criar uma nova interface intermanete, caso contario, FALSE.</param>
	CarenMFSinkWriterCallback(Boolean Param_CriarInterface);

	~CarenMFSinkWriterCallback();


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


	//Eventos
public:
	/////////////////////////////////////////////
	//EVENTOS CHAMADOS PARA NOTIFICAR O USUÁRIO//
	/////////////////////////////////////////////


	/// <summary>
	/// Evento chamado quando a operação assincrono do método (ICarenMFSinkWriter.Finalize) é conlcuido.
	/// </summary>
	virtual event ICarenMFSinkWriterCallback::Delegate_OnFinalize^ OnFinalize;

	/// <summary>
	/// Evento chamado quando a operação assincrono do método (ICarenMFSinkWriter.PlaceMarker) é conlcuido.
	/// </summary>
	virtual event ICarenMFSinkWriterCallback::Delegate_OnMarker^ OnMarker;



	//Delegates para uso nativo.
private:

	///////////////////////////////////////////////////////////////////////////////////////////
	//DELEGATES UTILIZADOS PARA RECEBER O EVENTO NATIVO DA CLASSE (CLN_IMFSinkWriterCallback)//
	///////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnFinalize) nativo da classe (CLN_IMFSourceReaderCallback) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnFinalize(HRESULT Param_HResultCode);
	DelegateNativo_Evento_OnFinalize^ Callback_OnFinalize = nullptr;

	/// <summary>
	/// Delegate nativo que vai conter o método que vai receber o evento(OnMarker) nativo da classe (CLN_IMFSourceReaderCallback) para ser enviado ao usuário.
	/// </summary>
	delegate void DelegateNativo_Evento_OnMarker(DWORD Param_FluxoID, LPVOID Param_ObjetoContexto);
	DelegateNativo_Evento_OnMarker^ Callback_OnMarker = nullptr;



	//Handles alocadas de cada Delegate.
private:
	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnFinalize).
	/// </summary>
	GCHandle gHandle_Delegate_OnFinalize;

	/// <summary>
	/// Contém a Handle alocada para o delegate (DelegateNativo_Evento_OnMarker).
	/// </summary>
	GCHandle gHandle_Delegate_OnMarker;


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
	/// Método responsável por encaminhar o (Evento) nativo (OnFinalize) da classe (IMFSinkWriterCallback) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnFinalize(HRESULT Param_HResultCode);

	/// <summary>
	///Método responsável por encaminhar o (Evento) nativo (OnMarker) da classe (IMFSinkWriterCallback) para o usuário em classe gerenciada.
	/// </summary>
	virtual void EncaminharEvento_OnMarker(DWORD Param_FluxoID, LPVOID Param_ObjetoContexto);

};
