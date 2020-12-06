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
#include "CarenMFMediaType.h"
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
/// [Concluido - Fase de testes] - Falta documentar.
/// </summary>
public ref class CarenMFSinkWriter : public ICarenMFSinkWriter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSinkWriter).
	IMFSinkWriter* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFSinkWriter();

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
	/// Método responsável por criar uma instância do Escritor de Mídia a parti de um MidiaSink.
	/// </summary>
	/// <param name="Param_MidiaSink">O Midia Sink a ser utilizado para criar o SinkWriter.</param>
	/// <param name="Param_Atributos">Uma interface com atributos para a criação desse escritor. Esse valor pode ser NULO.</param>
	/// <param name="Param_Out_SinkWriter">Recebe a interface que contém o Escritor de mídia criado.</param>
	static CarenResult CriarInstanciaFromCarenMediaSink(ICarenMFMediaSink^ Param_MidiaSink, ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFSinkWriter^% Param_Out_SinkWriter)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		IMFMediaSink *pMediaSink = NULL;
		IMFSinkWriter *pSinkWriter = NULL;
		IMFAttributes *pAtributes = NULL;
		ICarenMFSinkWriter^ InterfaceMediaSinkWriter = nullptr;

		//Chama o método para recuperar o Media Sink que vai ser usado para criar a classe
		Resultado = Param_MidiaSink->RecuperarPonteiro((LPVOID*)&pMediaSink);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Sai do método
			goto Done;
		}

		//Chama o método que vai recueprar os atributos se o usuário tiver definido.
		//Este valor não é obrigatorio para criação do MediaSinkWriter.
		if (Param_Atributos != nullptr)
		{
			//Recuper o ponteiro.
			Param_Atributos->RecuperarPonteiro((LPVOID*)&pAtributes);
		}

		//Chama o método que vai criar o SinkWriter
		Hr = MFCreateSinkWriterFromMediaSink(pMediaSink, pAtributes != NULL ? pAtributes : NULL, &pSinkWriter);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//O método falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro
		InterfaceMediaSinkWriter = gcnew CarenMFSinkWriter();

		//Chama o método para determinar o ponteiro de trabalho
		InterfaceMediaSinkWriter->AdicionarPonteiro(pSinkWriter);

		//Define a interface no parametro de retorno.
		Param_Out_SinkWriter = InterfaceMediaSinkWriter;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
		
	Done:;
		//Retorna o resultado
		return Resultado;
	}

	/// <summary>
	/// [Em Desenvolvimento] Método responsável por criar uma instância do Escritor de Mídia a parti de um MidiaSink.
	/// </summary>
	/// <param name="Param_OutputUrlMidia">Uma string para a url de saida do arquivo de mídia. Esse valor pode ser NULO.</param>
	/// <param name="Param_ByteStream">[Atenção] - Interface não implementada ainda.</param>
	/// <param name="Param_Atributos">Uma interface com atributos para a criação desse escritor. Esse valor pode ser NULO.</param>
	/// <param name="Param_Out_SinkWriter">Recebe a interface que contém o Escritor de mídia criado.</param>
	static CarenResult CriarInstanciaFromMidiaUrl(String^ Param_OutputUrlMidia, Object^ Param_ByteStream, ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFSinkWriter^% Param_Out_SinkWriter)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas no método
		IMFSinkWriter *pSinkWriter = NULL;
		IMFAttributes *pAtributes = NULL;
		ICarenMFSinkWriter^ InterfaceMediaSinkWriter = nullptr;
		Utilidades Util;
		char* pBufferStringConvertido = NULL;
		LPCWSTR pBufferWchar = NULL;

		//Chama o método que vai criar a url para a midia de saida.
		pBufferStringConvertido = Util.ConverterStringToChar(Param_OutputUrlMidia);

		//Converte o char* para wchar*
		pBufferWchar = Util.ConverterConstCharToConstWCHAR(pBufferStringConvertido);

		//Chama o método que vai recueprar os atributos se o usuário tiver definido.
		//Este valor não é obrigatorio para criação do MediaSinkWriter.
		if (Param_Atributos != nullptr)
		{
			//Recupera o ponteiro.
			Param_Atributos->RecuperarPonteiro((LPVOID*)&pAtributes);
		}

		//Chama o método que vai criar o SinkWriter
		Hr = MFCreateSinkWriterFromURL(pBufferWchar, NULL, pAtributes ? pAtributes : NULL, &pSinkWriter);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//O método falhou
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro
		InterfaceMediaSinkWriter = gcnew CarenMFSinkWriter();

		//Chama o método para determinar o ponteiro de trabalho
		InterfaceMediaSinkWriter->AdicionarPonteiro(pSinkWriter);

		//Define a interface no parametro de retorno.
		Param_Out_SinkWriter = InterfaceMediaSinkWriter;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
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



	//Métodos da classe ICarenMFSinkWriter
public:
	/// <summary>
	/// (AddStream) - Adiciona um fluxo para o gravador de coletor.
	/// </summary>
	/// <param name="Param_TipoMidia">Esse tipo de mídia especifica o formato das amostras que serão gravados no arquivo ou Hardware. 
	/// Ele não precisa corresponder ao formato de entrada. Para definir o formato de entrada, chame o método :
	/// SetInputMediaType</param>
	/// <param name="Param_Out_IdFluxoAdicionado">Recebe o índice baseado em zero do novo fluxo.</param>
	virtual CarenResult AddStream(ICarenMFMediaType^ Param_TipoMidia, [Out] UInt32% Param_Out_IdFluxoAdicionado);

	/// <summary>
	/// (BeginWriting) - Inicializa o gravador de coletor para gravação.
	/// Chame esse método depois de configurar os fluxos de entrada e antes de enviar 
	/// os dados para o gravador de coletor.
	/// </summary>
	virtual CarenResult BeginWriting();

	/// <summary>
	/// (Finalize) - Conclui todas as operações de gravação no gravador de coletor.
	/// </summary>
	virtual CarenResult Finalize();

	/// <summary>
	/// (Flush) - Libera um ou mais fluxos.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo a ser liberado. Se (Param_TodosFluxos) for True, desconsidere esse valor.</param>
	/// <param name="Param_TodosFluxos">Define se deve liberar todos os fluxos deste escritor. Equivale ao valor: MF_SINK_WRITER_ALL_STREAMS</param>
	virtual CarenResult Flush(UInt32 Param_IdFluxo, Boolean Param_TodosFluxos);

	/// <summary>
	/// (GetServiceForStream) - Consulta o coletor de mídia subjacente ou codificador para uma interface.
	/// </summary>
	/// <param name="Param_IdFluxo">Um Indice baseado em zero de um fluxo para a consulta. Desconsidere esse valor se o parâmetro (Param_Escritor)
	/// for True.</param>
	/// <param name="Param_ConsultarColetor">Define que o objeto de consulta é o Coletor de Mídia associado. Esse valor representa o: MF_SINK_WRITER_MEDIASINK</param>
	/// <param name="Param_GuidServiço">O Guid para o (Identificador de Serviço). Se o valor for (NULO), o método chama (QueryInterface) para obter
	/// interface solicitada.</param>
	/// <param name="Param_GuidInterfaceSolicitada">O Guid para a interface solicitada.</param>
	/// <param name="Param_Out_Interface">Recebe a interface solicitada.</param>
	virtual CarenResult GetServiceForStream(
		UInt32 Param_IdFluxo,
		Boolean Param_ConsultarColetor,
		String^ Param_GuidServiço,
		String^ Param_GuidInterfaceSolicitada,
		ICaren^ Param_Out_Interface);

	/// <summary>
	/// (GetStatistics) - Obtém estatísticas sobre o desempenho do gravador de coletor.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo de consulta. Se (Param_ConsularColetor) for True, desconsidere esse valor.</param>
	/// <param name="Param_ConsultarColetor">Define se deve obter as estatísticas do (Coletor de Mídia) propriamente dito.</param>
	/// <param name="Param_Out_StatusDesempenho">Retorna a estrutura que contém todas as informações de sempenho </param>
	virtual CarenResult GetStatistics(UInt32 Param_IdFluxo, Boolean Param_ConsultarColetor, [Out] Estruturas::CA_MF_SINK_WRITER_STATISTICS^% Param_Out_StatusDesempenho);

	/// <summary>
	/// (NotifyEndOfSegment) - Notifica o coletor de mídia que um fluxo atingiu o final de um segmento.
	/// </summary>
	/// <param name="Param_IdFluxo">O indica para o fluxo que vai ser notificado que foi atingido o final de um segmento. Desconsidere esse valor se (Param_NotificarTodos)
	/// for True.</param>
	/// <param name="Param_NotificarTodos">Indica que vai notificar que todos os fluxos atingiram o final de um segmento.</param>
	virtual CarenResult NotifyEndOfSegment(UInt32 Param_IdFluxo, Boolean Param_NotificarTodos);

	/// <summary>
	/// Coloca um marcador no fluxo especificado.
	/// Para usar esse método, você deve fornecer um retorno de chamada assíncrono(MF_SINK_WRITER_ASYNC_CALLBACK) quando você cria o Gravador de Coletor(ICarenMFSinkWriter).
	/// Caso contrario, o método retorna o código: ER_MF_REQUISICAO_INVALIDA
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo que vai ter o marcador adicionado.</param>
	/// <param name="Param_Valor">A interface que contém o valor desconhecido a ser definido.</param>
	virtual CarenResult PlaceMarker(UInt32 Param_IdFluxo, ICaren^ Param_Valor);

	/// <summary>
	/// (SendStreamTick) - Indica uma lacuna em um fluxo de entrada.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.o.</param>
	/// <param name="Param_IdFluxo">A posição no fluxo onde ocorre a lacuna nos dados. O valor é fornecido em 100-nanosecond unidades, 
	/// em relação ao início do fluxo..</param>
	virtual CarenResult SendStreamTick(UInt32 Param_IdFluxo, Int64 Param_TimeStamp);

	/// <summary>
	/// (SetInputMediaType) - Define o Formatar de entrada para um fluxo no gravador de coletor.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
	/// <param name="Param_TipoMidia">A interface que representa o tipo da mídia. O tipo de mídia especifica o 
	/// formato de entrada.</param>
	/// <param name="Param_ParametrosEncode">Use o repositório de atributos para configurar o codificador. 
	/// Este parâmetro pode ser nulo.</param>
	virtual CarenResult SetInputMediaType(UInt32 Param_IdFluxo, ICarenMFMediaType^ Param_TipoMidia, ICarenMFAttributes^ Param_ParametrosEncode);

	/// <summary>
	/// (WriteSample) - Fornece uma amostra para o gravador de coletor.
	/// Você deve chamar o método (BeginWriting) antes de chamar esse método. Caso contrário, o método retornará 
	/// o código: ER_MF_REQUISICAO_INVALIDA.
	/// </summary>
	/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo para este exemplo.</param>
	/// <param name="Param_AmostraMidia">A interface que contém a amostra a ser escrita.</param>
	virtual CarenResult WriteSample(UInt32 Param_IdFluxo, ICarenMFSample^ Param_AmostraMidia);
};

