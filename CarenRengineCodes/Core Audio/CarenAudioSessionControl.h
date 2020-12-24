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
#include "CarenAudioSessionEvents.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da WSAPI.
using namespace CarenRengine::CoreAudio;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por permitir que um cliente configure os parâmetros de controle para uma sessão de áudio e para monitorar eventos na sessão.
/// </summary>
public ref class CarenAudioSessionControl : public ICarenAudioSessionControl
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IAudioSessionControl).
	IAudioSessionControl* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenAudioSessionControl();


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
	/// <param name="Param_Out_CarenAudioControleSessao">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenAudioSessionControl^% Param_Out_CarenAudioControleSessao)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenAudioControleSessao = gcnew CarenAudioSessionControl();

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




	//Métodos da interface(ICarenAudioSessionControl)
public:
	/// <summary>
	/// (GetDisplayName) - O método recupera o nome de exibição para a sessão de áudio.
	/// Se o cliente não tiver chamado (ICarenAudioSessionControl::SetDisplayName) para definir o nome de exibição, a sequência de caracteres estará vazia. 
	/// </summary>
	/// <param name="Param_Out_Nome">Retorna o nome de exbição da sessão de áudio.</param>
	virtual CarenResult GetDisplayName([Out] String^% Param_Out_Nome);

	/// <summary>
	/// (GetGroupingParam) - O método recupera o parâmetro de agrupamento da sessão de áudio.
	/// </summary>
	/// <param name="Param_Out_GUID">Retorna um GUID do paramêtro de agrupamento.</param>
	virtual CarenResult GetGroupingParam([Out] String^% Param_Out_GUID);

	/// <summary>
	/// (GetIconPath) - O método recupera o caminho para o ícone de exibição para a sessão de áudio.
	/// </summary>
	/// <param name="Param_Out_Url">Retorna o caminho completo completo para o .ico, .exe, .dll que contenha um icone para a sessão de áudio.</param>
	virtual CarenResult GetIconPath([Out] String^% Param_Out_Url);

	/// <summary>
	/// (GetState) - O método recupera o estado atual da sessão de áudio.
	/// </summary>
	/// <param name="Param_Out_Estado">Retorna o estado da sessão de áudio atual.</param>
	virtual CarenResult GetState([Out] Enumeracoes::CA_ESTADO_SESSAO_AUDIO% Param_Out_Estado);

	/// <summary>
	/// (RegisterAudioSessionNotification) - O método registra o cliente para receber notificações de eventos de sessão, incluindo as alterações no estado de fluxo.
	/// </summary>
	/// <param name="Param_Notificador">Ponteiro para uma interface IAudioSessionEvents, implementada pelo cliente. Se o método for bem-sucedido, ele chama o AddRef método na interface do 
	/// cliente IAudioSessionEvents.</param>
	virtual CarenResult RegisterAudioSessionNotification(ICarenAudioSessionEvents^ Param_Notificador);

	/// <summary>
	/// (SetDisplayName) - O método atribui um nome de exibição para a sessão atual.
	/// </summary>
	/// <param name="Param_Nome">O novo nome para exibição da sessão de áudio.</param>
	/// <param name="Param_GuidContextoEvento">Uma string para o evento-contexto GUID. Se uma chamada para esse método gera um evento de alteração de nome, o Gerenciador de sessão envia 
	/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
	/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de ContextoEvento.
	/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
	/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
	virtual CarenResult SetDisplayName(String^ Param_Nome, String^ Param_GuidContextoEvento);

	/// <summary>
	/// (SetGroupingParam) - O método atribui uma sessão a um agrupamento de sessões.
	/// </summary>
	/// <param name="Param_GuidNovoParametro">O novo GUID para o parâmetro de agrupamento.</param>
	/// <param name="Param_ContextoEvento">Uma string com o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de agrupamento, o Gerenciador de sessão 
	/// envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
	/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
	/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
	/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
	virtual CarenResult SetGroupingParam(String^ Param_GuidNovoParametro, String^ Param_ContextoEvento);

	/// <summary>
	/// (SetIconPath) - O método atribui um ícone de exibir para a sessão atual.
	/// </summary>
	/// <param name="Param_UrlCompletaIco">Sequência de caracteres largos que especifica o caminho e nome de arquivo de um arquivo .ico, .dll ou .exe que contém o ícone.</param>
	/// <param name="Param_ContextoEvento">Uma string para o GUID do (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de ícone, o Gerenciador de sessão envia 
	/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) com 
	/// cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
	/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro,
	/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
	virtual CarenResult SetIconPath(String^ Param_UrlCompletaIco, String^ Param_ContextoEvento);

	/// <summary>
	/// (UnregisterAudioSessionNotification) - O método exclui um registro anterior pelo cliente para receber notificações.
	/// </summary>
	/// <param name="Param_Notificador">Ponteiro para a interface IAudioSessionEvents implementada pelo cliente. O cliente passou esse mesmo ponteiro de interface para o Gerenciador de sessão 
	/// em uma chamada anterior para o método ICarenAudioSessionControl::RegisterAudioSessionNotification. Se o (UnregisterAudioSessionNotification) método for bem-sucedido, ele chama o 
	/// método Release na interface IAudioSessionEvents do cliente.</param>
	virtual CarenResult UnregisterAudioSessionNotification(ICarenAudioSessionEvents^% Param_Notificador);
};