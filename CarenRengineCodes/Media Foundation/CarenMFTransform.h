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
#include "../SDK_Utilidades.h"
#include "CarenMFAttributes.h"
#include "CarenMFMediaType.h"

//Importa o namespace que contém as interfaces da API primária.
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
/// (Concluido - Fase de testes) - Classe responsável por representar o modelo genérico para o processamento de dados de mídia.
/// Os MFTs(Media Foundation Transforms) são usados para decodificadores, codificadores e processadores de sinal digital (DSPs).
/// </summary>
public ref class CarenMFTransform : public ICarenMFTransform
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFTransform).
	IMFTransform* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFTransform();

	~CarenMFTransform();


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




	//Métodos da interface(ICarenMFTransform)
public:
	/// <summary>
	/// (AddInputStreams) - Adiciona um ou mais novos fluxos de entrada a esta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_Quantidade">Quantidade de fluxos a serem adicionados.</param> 
	/// <param name="Param_ArrayIdentificadores">Matriz de identificadores de fluxo. Os novos identificadores de fluxo não devem corresponder a nenhum fluxo de entrada existente.</param> 
	virtual CarenResult AddInputStreams(UInt32 Param_Quantidade, cli::array<UInt32>^ Param_ArrayIdentificadores);

	/// <summary>
	/// (DeleteInputStream) - Remove um fluxo de entrada desta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_FluxoID"> O Id do fluxo a ser removido.</param>
	virtual CarenResult DeleteInputStream(UInt32 Param_FluxoID);

	/// <summary>
	/// (GetAttributes ) - Recebe a loja global de atributos para esta transformação da Media Foundation (MFT).
	/// Use o ponteiro recuperado por este método para obter ou definir atributos que se aplicam a todo o MFT.
	/// </summary>
	/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface de atributos. O chamdor deve liberar a interface.</param>
	virtual CarenResult GetAttributes([Out] ICarenMFAttributes^% Param_Out_Atributos);

	/// <summary>
	/// (GetInputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
	/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
	virtual CarenResult GetInputAvailableType(UInt32 Param_IDFluxoEntrada, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

	/// <summary>
	/// (GetInputCurrentType) - Obtém o tipo de mídia atual para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
	virtual CarenResult GetInputCurrentType(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

	/// <summary>
	/// (GetInputStatus) - Consulta se um fluxo de entrada nesta transformação da Media Foundation (MFT) pode aceitar mais dados.
	/// Se o método retornar a bandeira CA_MFT_INPUT_STATUS_ACCEPT_DATA, você pode fornecer uma amostra de entrada para o fluxo 
	/// especificado ligando para ICarenMFTransform::ProcessInput. Se o método for bem sucedido, mas não devolver nenhuma 
	/// bandeira no parâmetro Param_Out_Flag, significa que o fluxo de entrada já tem o máximo de dados que pode aceitar.
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_INPUT_STATUS_FLAGS, ou zero. Se o valor for CA_MFT_INPUT_STATUS_ACCEPT_DATA, o fluxo especificado 
	/// no Param_IDFluxoEntrada pode aceitar mais dados de entrada.</param>
	virtual CarenResult GetInputStatus(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STATUS_FLAGS% Param_Out_Flag);

	/// <summary>
	/// (GetInputStreamAttributes) - Recebe a loja de atributos para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
	virtual CarenResult GetInputStreamAttributes(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo);

	/// <summary>
	/// (GetInputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_INPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de entrada.</param>
	virtual CarenResult GetInputStreamInfo(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STREAM_INFO^% Param_Out_InfoFluxo);

	/// <summary>
	/// (GetOutputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
	/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetOutputAvailableType(UInt32 Param_IDFluxoSaida, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

	/// <summary>
	/// (GetOutputCurrentType) - Obtém o tipo de mídia atual para um fluxo de saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
	virtual CarenResult GetOutputCurrentType(UInt32 Param_IDFluxoSaida, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

	/// <summary>
	/// (GetOutputStatus) - Questiona se a transformação da Media Foundation (MFT) está pronta para produzir dados de produção.
	/// Se o método devolver a bandeira CA_MFT_OUTPUT_STATUS_SAMPLE_READY, significa que você pode gerar uma ou mais amostras de produção ligando 
	/// para o ICarenMFTransform::ProcessOutput.
	/// </summary>
	/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_OUTPUT_STATUS_FLAGS, ou zero. Se o valor for MFT_OUTPUT_STATUS_SAMPLE_READY, o MFT pode produzir 
	/// uma amostra de saída.</param>
	virtual CarenResult GetOutputStatus([Out] CA_MFT_OUTPUT_STATUS_FLAGS% Param_Out_Flag);

	/// <summary>
	/// (GetOutputStreamAttributes) - Recebe a loja de atributos para um fluxo de saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
	virtual CarenResult GetOutputStreamAttributes(UInt32 Param_IDFluxoSaida, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo);

	/// <summary>
	/// (GetOutputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_OUTPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de saida.</param>
	virtual CarenResult GetOutputStreamInfo(UInt32 Param_IDFluxoSaida, [Out] CA_MFT_OUTPUT_STREAM_INFO^% Param_Out_InfoFluxo);

	/// <summary>
	/// (GetStreamCount) - Obtém o número atual de fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_Out_FluxoEntrada">Retorna a quantidade de fluxos de entrada.</param>
	/// <param name="Param_Out_FluxoSaida">Retorna a quantidade de fluxos de saida.</param>
	virtual CarenResult GetStreamCount([Out] UInt32% Param_Out_FluxoEntrada, [Out] UInt32% Param_Out_FluxoSaida);

	/// <summary>
	/// (GetStreamIDs) - Obtém os identificadores de fluxo para os fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_SizeMatrizFluxosEntrada">O tamanho da matriz que vai conter os IDs dos fluxos de entrada.</param>
	/// <param name="Param_MatrizFluxosEntrada">Uma matriz que vai receber todos os identificadores de fluxos de Entrada. O chamador é responsável por criar a matriz. 
	/// Chame o método ICarenMFTransform::GetStreamCount para descobrir o tamanho que deve ser essa matriz.</param>
	/// <param name="Param_SizeMatrizFluxosSaida">O tamanho da matriz que vai conter os IDs dos fluxos de Saida.</param>
	/// <param name="Param_MatrizFluxosSaida">Uma matriz que vai receber todos os identificadores de fluxos de Saida. O chamador é responsável por criar a matriz. 
	/// Chame o método ICarenMFTransform::GetStreamCount para descobrir o tamanho que deve ser essa matriz.</param>
	virtual CarenResult GetStreamIDs(
		UInt32 Param_SizeMatrizFluxosEntrada,
		cli::array<UInt32>^% Param_MatrizFluxosEntrada,  //REF
		UInt32 Param_SizeMatrizFluxosSaida,
		cli::array<UInt32>^% Param_MatrizFluxosSaida);   //REF

/// <summary>
/// (GetStreamLimits) - Obtém o número mínimo e máximo de fluxos de entrada e saída para esta transformação da Media Foundation (MFT).
/// Se o MFT tiver um número fixo de fluxos, os valores mínimos e máximos são os mesmos.
/// </summary>
/// <param name="Param_Out_FluxoEntradaMinimo">Recebe o número mínimo de fluxos de entrada.</param>
/// <param name="Param_Out_FluxoEntradaMaximo">Recebe o número máximo de fluxos de entrada. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
/// <param name="Param_Out_FluxoSaidaMinimo">Recebe o número mínimo de fluxos de saída.</param>
/// <param name="Param_Out_FluxoSaidaMaximo">Recebe o número máximo de fluxos de saída. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
	virtual CarenResult GetStreamLimits(
		[Out] UInt32% Param_Out_FluxoEntradaMinimo,
		[Out] UInt32% Param_Out_FluxoEntradaMaximo,
		[Out] UInt32% Param_Out_FluxoSaidaMinimo,
		[Out] UInt32% Param_Out_FluxoSaidaMaximo);

	/// <summary>
	/// (ProcessEvent) - Envia um evento para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Evento">Um ponteiro para a interface de eventos(ICarenMFMediaEvent).</param>
	virtual CarenResult ProcessEvent(UInt32 Param_IDFluxoEntrada, ICarenMFMediaEvent^ Param_Evento);

	/// <summary>
	/// (ProcessInput) - Fornece dados para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// Na maioria dos casos, se o método for bem sucedido, o MFT armazena a amostra e mantém uma contagem de referência no ponteiro ICarenMFSample. 
	/// Não reutilize a amostra até que o MFT libere a amostra. Em vez de armazenar a amostra, no entanto, um MFT pode copiar os dados da amostra em um novo buffer. 
	/// Nesse caso, o MFT deve definir a bandeira MFT_INPUT_STREAM_DOES_NOT_ADDREF no método ICarenMFTransform::GetInputStreamInfo.
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_Amostra">Um ponteiro para a interface de amostra de midia. A amostra deve conter pelo menos um Buffer de mídia que contém dados de entrada válidos.</param>
	/// <param name="Param_Flags">Reservado. Deixe como zero.</param>
	virtual CarenResult ProcessInput(UInt32 Param_IDFluxoEntrada, ICarenMFSample^ Param_Amostra, UInt32 Param_Flags);

	/// <summary>
	/// (ProcessMessage) - Envia uma mensagem para a Transformação da Fundação de Mídia (MFT).
	/// </summary>
	/// <param name="Param_Mensagem">A mensagem a enviar, especificada como membro da enumeração CA_MFT_MESSAGE_TYPE.</param>
	/// <param name="Param_ulPram">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
	virtual CarenResult ProcessMessage(CA_MFT_MESSAGE_TYPE Param_Mensagem, UInt32 Param_ulPram);

	/// <summary>
	/// (ProcessOutput) - Gera saída a partir dos dados de entrada atuais.
	/// </summary>
	/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_FLAGS.</param>
	/// <param name="Param_QuantidadeElementos">Número de elementos na matriz (Param_MatrizBuffersSaida). O valor deve ser de pelo menos 1.</param>
	/// <param name="Param_MatrizBuffersSaida">Uma matriz de estruturas CA_MFT_OUTPUT_DATA_BUFFER. O MFT usa este array para devolver dados de saída ao chamador.</param>
	/// <param name="Param_Out_Status">Recebe zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_STATUS.</param>
	virtual CarenResult ProcessOutput(
		CA_MFT_PROCESS_OUTPUT_FLAGS Param_Flags,
		UInt32 Param_QuantidadeElementos,
		cli::array<CA_MFT_OUTPUT_DATA_BUFFER^>^% Param_MatrizBuffersSaida, //REF
		[Out] CA_MFT_PROCESS_OUTPUT_STATUS% Param_Out_Status);

	/// <summary>
	/// (SetInputType) - Define, testa ou limpa o tipo de mídia para um fluxo de entrada nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de Entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
	/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
	virtual CarenResult SetInputType(
		UInt32 Param_IDFluxoEntrada,
		ICarenMFMediaType^ Param_TipoMidiaFluxo,
		CA_MFT_SET_TYPE_FLAGS Param_Flags);

	/// <summary>
	/// (SetOutputBounds) - Define a gama de carimbos de tempo que o cliente precisa para a saída.
	/// </summary>
	/// <param name="Param_HorarioAntigo">Especifica o carimbo de horário mais antigo. A Transformação da Media Foundation (MFT) aceitará a entrada até que possa produzir uma 
	/// amostra de saída que começa neste momento; ou até que possa produzir uma amostra que termina neste momento ou mais tarde. Se não houver limite inferior, use o 
	/// valor MFT_OUTPUT_BOUND_LOWER_UNBOUNDED(0).</param>
	/// <param name="Param_HorarioMaior">Especifica o último carimbo de tempo. O MFT não produzirá uma amostra de saída com carimbos de tempo mais tarde do que desta vez. Se 
	/// não houver limite superior, use o valor MFT_OUTPUT_BOUND_UPPER_UNBOUNDED(-1).</param>
	virtual CarenResult SetOutputBounds(Int64 Param_HorarioAntigo, Int64 Param_HorarioMaior);

	/// <summary>
	/// (SetOutputType) - Define, testa ou limpa o tipo de mídia para um fluxo de saída nesta transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::GetStreamIDs.</param>
	/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
	/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
	virtual CarenResult SetOutputType(
		UInt32 Param_IDFluxoSaida,
		ICarenMFMediaType^ Param_TipoMidiaFluxo,
		CA_MFT_SET_TYPE_FLAGS Param_Flags);
};