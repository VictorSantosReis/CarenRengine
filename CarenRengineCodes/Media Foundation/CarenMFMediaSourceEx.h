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
#include "CarenMFPresentationDescriptor.h"
#include "CarenMFMediaEvent.h"
#include "CarenMFAttributes.h"
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
/// Estende a interface IMFMediaSource para fornecer recursos adicionais para uma fonte de mídia.
/// </summary>
public ref class CarenMFMediaSourceEx :public ICarenMFMediaSourceEx
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceReader).
	IMFMediaSourceEx* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFMediaSourceEx();


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


	//Métodos da interface ICarenMFMediaSourceEx
public:
	/// <summary>
	/// (GetSourceAttributes) - Obtém um armazenamento de atributo para a fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_AtributosFonteMidia">Recebe a interface que contém os atributos para a fonte de midia.</param>
	virtual CarenResult ObterAtributosFonteMidia([Out] ICarenMFAttributes^% Param_Out_AtributosFonteMidia);

	/// <summary>
	/// (GetStreamAttributes) - Obtém um armazenamento de atributo para um fluxo na fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_AtributosFluxoFonte">Recebe a interface que contém os atributos para um fluxo na fonte de midia.</param>
	/// <param name="Param_IdentificadorFluxo">O identificador do fluxo. Para obter o identificador, chame ICarenMFStreamDescriptor::ObterIdentificadorFluxo no descritor de fluxo.</param>
	virtual CarenResult ObterAtributosFluxoFonte(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxoFonte);

	/// <summary>
	/// (SetD3DManager) - Define um ponteiro para o Gerenciador de dispositivos do Microsoft DirectX Graphics infra-estrutura (DXGI) na fonte de mídia.
	/// </summary>
	/// <param name="Param_DXGIManager">O Gerenciador do DXGI que será utilizado.</param>
	virtual CarenResult DefinirGerenciadorDXGI(ICarenMFDXGIDeviceManager^ Param_DXGIManager);



	//Métodos da interface ICarenMFMediaSource
public:

	/// <summary>
	/// (CreatePresentationDescriptor) - Recupera uma cópia do descritor de apresentação da fonte de mídia. Os aplicativos usam o descritor de apresentação para selecionar fluxos e obter informações sobre o conteúdo de origem.
	/// </summary>
	/// <param name="Param_Out_DescritorApresentação">Recebe a interface para o descritor de apresentação.</param>
	virtual CarenResult CriarDescritorApresentação([Out] ICarenMFPresentationDescriptor^% Param_Out_DescritorApresentação);

	/// <summary>
	/// (GetCharacteristics) - Recupera as características da fonte de mídia.
	/// </summary>
	/// <param name="Param_Out_Caracteristicas">Recebe um OR de bit a bit de zero ou mais sinalizadores da enumeração (CA_CARACTERISTICAS_FONTE_MIDIA).</param>
	virtual CarenResult ObterCaracteristicas([Out] Enumeracoes::CA_CARACTERISTICAS_FONTE_MIDIA% Param_Out_Caracteristicas);

	/// <summary>
	/// (Start) - Inicia, procura ou reinicia a fonte de mídia especificando onde iniciar a reprodução.
	/// </summary>
	/// <param name="Param_DescritorApresentação">A interface de ICarenMFPresentationDescriptor de descritor de apresentação da fonte de mídia. Para obter o descritor de apresentação, chamade o método (ICarenMFPresentationDescriptor::CriarDescritorApresentação). 
	/// Você pode modificar o descritor de apresentação antes de chamar Iniciar, para selecionar ou desmarcar fluxos ou alterar os tipos de mídia.</param>
	/// <param name="Param_GuidTimeFormato">Um GUID que especifica o formato de hora. O formato de hora define as unidades para o parâmetro Param_PosiçãoInicio. Se o valor é NULL, o formato é definido como unidades de 100 nanossegundos. Algumas fontes de 
	/// mídia podem oferecer suporte o formato de hora adicional. Este parâmetro pode ser nulo. Se o valor for nulo, é equivalente a GUID_NULL.</param>
	/// <param name="Param_PosiçãoInicio">Especifica onde iniciar a reprodução. As unidades deste parâmetro são indicadas pelo formato tempo dado em Param_GuidTimeFormato. Se o formato de hora é GUID_NULL, o tipo de variante deve ser VT_I8 ou VT_EMPTY. Use VT_I8 
	/// para especificar uma nova posição inicial, em unidades de 100 nanossegundos. Use VT_EMPTY para começar a partir da posição atual. Outros formatos de hora podem usar outros tipos CA_PropVariant.</param>
	virtual CarenResult Iniciar(ICarenMFPresentationDescriptor^ Param_DescritorApresentação, String^ Param_GuidTimeFormato, Estruturas::CA_PropVariant^ Param_PosiçãoInicio);

	/// <summary>
	/// (Pause) - Pausa todos os fluxos ativos na fonte de mídia.
	/// </summary>
	virtual CarenResult Pausar();

	/// <summary>
	/// (Stop) - Interrompe todos os fluxos ativos na fonte de mídia.
	/// </summary>
	virtual CarenResult Parar();

	/// <summary>
	/// (Shutdown) - Desliga a fonte de mídia e libera os recursos que ela está usando.
	/// </summary>
	virtual CarenResult Desligar();


	//Métodos da interface (CarenMFMediaEventGenerator)
public:
	/// <summary>
	/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
	/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
	/// dependerá do valor de Param_Flags.
	/// </summary>
	/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult ObterEvento(Enumeracoes::CA_FLAGS_OBTER_EVENTO Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
	/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
	/// </summary>
	/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
	/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
	/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
	virtual CarenResult SolicitarProximoEvento(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido);

	/// <summary>
	/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
	/// </summary>
	/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
	/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
	virtual CarenResult ConcluirSolicitaçãoEvento(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

	/// <summary>
	/// (QueueEvent) - Coloca um novo evento na fila do objeto.
	/// </summary>
	/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.ObterTipo).</param>
	/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.ObterTipoExtendido) do evento.</param>
	/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterStatus) do evento.</param>
	/// <param name="Param_Dados">uma CA_PropVariant que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterValor) do evento.</param>
	virtual CarenResult InserirEventoFila(Enumeracoes::CA_TIPO_MIDIA_EVENT Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PropVariant^ Param_Dados);
};

