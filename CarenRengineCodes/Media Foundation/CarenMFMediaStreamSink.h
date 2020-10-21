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
#include "CarenMFMediaTypeHandler.h"
#include "CarenMFMediaEvent.h"
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
/// [Concluido - Fase de Testes]
/// </summary>
public ref class CarenMFMediaStreamSink :public ICarenMFMediaStreamSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFStreamSink).
	IMFStreamSink* PonteiroTrabalho = NULL;

	//Destruidor.
public:
	~CarenMFMediaStreamSink();

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





	//
	//ICarenMFMediaStreamSink
	//


	//Métodos da interface (ICarenMFMediaStreamSink)
public:
	/// <summary>
	/// Recupera o (Coletor de Mídia) que possui esse (Coletor de Fluxo).
	/// </summary>
	/// <param name="Param_Out_MidiaSink">Recebe a interface(ICarenMFMediaSink) do (Coletor de Mídia) responsável por esse (Coletor de Fluxo). O usuário deve criar a interface antes de chamar o método.</param>
	virtual CarenResult RecuperarMediaSink(ICaren^ Param_Out_MidiaSink);

	/// <summary>
	/// Fornece uma amostra para o fluxo. O coletor de mídia processa o exemplo.
	/// Esse método pode retornar (ER_MF_AMOSTRA_TIME_SPAN_INVALIDO) por vários motivos, dependendo da implementação do coletor de mídia:
	/// 1 > Carimbos de hora negativos.
	/// 2 > Carimbos de tempo que saltam para trás (dentro do mesmo fluxo).
	/// 3 > Os carimbos de hora de um fluxo se afastaram muito dos registros de tempo em outro fluxo no mesmo coletor de mídia 
	/// (por exemplo, um coletor de arquivamento que multiplexa os fluxos).
	/// </summary>
	/// <param name="Param_AmostraMidia">A amostra de mídia a ser processada.</param>
	virtual CarenResult ProcessarAmostraMidia(ICarenMFSample^ Param_AmostraMidia);

	/// <summary>
	/// Recupera o identificador de fluxo para este coletor de fluxo.
	/// </summary>
	/// <param name="Param_Out_IdentificadorFluxo">Retorna o identificador deste fluxo.</param>
	virtual CarenResult ObterIdentificador([Out] UInt32% Param_Out_IdentificadorFluxo);

	/// <summary>
	/// Recupera o manipulador de tipo de mídia para o coletor de fluxo. 
	/// Você pode usar o manipulador de tipo de mídia para localizar quais
	/// formatos o fluxo oferece suporte e para definir o tipo de mídia no fluxo.
	/// </summary>
	/// <param name="Param_Out_MidiaHandle">Recebe a interface que possui o (Manipulador de Mídia).</param>
	virtual CarenResult ObterMediaTypeHandle([Out] ICarenMFMediaTypeHandler^% Param_Out_MidiaHandle);

	/// <summary>
	/// Coloca um marcador no fluxo.
	/// O método placemarker coloca um marcador no fluxo entre amostras. O MFSTREAMSINK_MARKER_TYPE enumeração define o 
	/// tipo de marcador e o tipo de informações associadas com o marcador.
	/// </summary>
	/// <param name="Param_Marcador">Especifica o tipo de marcador, como um membro da enumeração: CA_MIDIA_STREAM_SINK_MARCADORES</param>
	/// <param name="Param_ValorAdicional">Um valor que contém informações adicionais relacionadas ao marcador. Esse parâmetro pode ser (NULO).</param>
	/// <param name="Param_DadosAnexoEvento">Valor que é anexado junto ao evento(MEStreamSinkMarker). Chame o método (ObterValor) na interface 
	/// de evento para obter esse valor. Esse parâmetro pode ser (NULO).</param>
	virtual CarenResult AdicionarMarcador(Enumeracoes::CA_MIDIA_STREAM_SINK_MARCADORES Param_Marcador, Estruturas::CA_PropVariant^ Param_ValorAdicional, Estruturas::CA_PropVariant^ Param_DadosAnexoEvento);

	/// <summary>
	/// Faz com que o coletor de fluxo para descartar todas as amostras que ele 
	/// recebeu e ainda não processado.
	/// </summary>
	virtual CarenResult Flush();





	//
	// ICarenMFGeradorEventosMidia
	//



	//Métodos da interface (ICarenMFGeradorEventosMidia)
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

