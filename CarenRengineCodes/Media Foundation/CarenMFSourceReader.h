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
/// Classe responsável por realizar a leitura de amostras de mídia de um Arquivo, Nuvem ou Camera.
/// Essa classe implementa a interface(ICarenMFSourceReader), que implementa os métodos de IMFSourceReader.
/// </summary>
public ref class CarenMFSourceReader : public ICarenMFSourceReader
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceReader).
	IMFSourceReader* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFSourceReader();


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
	/// Cria uma instância do leitor de mídia(IMFSourceReader), utilizado para leitura de amostras e dados de Vídeo e Áudio.
	/// A criação é default e não utiliza os atributos.
	/// </summary>
	/// <param name="Param_UrlMidia">A url para a mídia a ser carregada pelo leitor de mídia.</param>
	/// <param name="Param_Out_LeitorMidia">Recebe o ponteiro para o leitor de mídia.</param>
	static CarenResult CriarInstancia(String^ Param_UrlMidia, [Out] ICarenMFSourceReader^% Param_Out_LeitorMidia)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que vai conter o resultado COM.
		ResultadoCOM Hr;

		//Variavel que vai ser retornada.
		IMFSourceReader *pSourceReader = NULL;

		//Variaveis utilizadas pelo método.
		Utilidades Util;
		char* pBufferStringConvertido = NULL;
		LPCWSTR pBufferWchar = NULL;

		//Chama o método que vai criar a url para a mídia a ser aberta.
		pBufferStringConvertido = Util.ConverterStringToChar(Param_UrlMidia);

		//Converte o char* para wchar*
		pBufferWchar = Util.ConverterConstCharToConstWCHAR(pBufferStringConvertido);

		//Chama o método para criar o leitor de mídia.
		Hr = MFCreateSourceReaderFromURL(pBufferWchar, NULL, &pSourceReader);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}

		//Cria a instância da classe
		Param_Out_LeitorMidia = gcnew CarenMFSourceReader();

		//Chama o método para definir o ponteiro de trabalho na interface a ser retornada.
		Param_Out_LeitorMidia->AdicionarPonteiro(pSourceReader);

	Done:;
		//Deleta os buffers convertidos da string.
		if (pBufferStringConvertido == NULL)
		{
			//Deleta o buffer de alocado.
			delete pBufferStringConvertido;
		}
		if (pBufferWchar == NULL)
		{
			//Deleta o buffer de alocado.
			delete pBufferWchar;
		}

		//Retorna o resultado.
		return Resultado;
	}

	/// <summary>
	/// Cria uma instância do leitor de mídia(IMFSourceReader), utilizado para leitura de amostras e dados de Vídeo e Áudio.
	/// Permite especificar atributos para criação do leitor.
	/// </summary>
	/// <param name="Param_UrlMidia">A url para a mídia a ser carregada pelo leitor de mídia.</param>
	/// <param name="Param_Atributos">A interface com os atributos para a criação do leitor de mídia.</param>
	/// <param name="Param_Out_LeitorMidia">Recebe o ponteiro para o leitor de mídia.</param>
	static CarenResult CriarInstancia(String^ Param_UrlMidia, ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFSourceReader^% Param_Out_LeitorMidia)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que vai conter o resultado COM.
		ResultadoCOM Hr;

		//Variavel que vai conter o SourceReader.
		IMFSourceReader *pSourceReader = NULL;

		//Variaveis utilizadas pelo método.
		Utilidades Util;
		char* pBufferStringConvertido = NULL;
		LPCWSTR pBufferWchar = NULL;
		IMFAttributes *pAtributos = NULL;

		//Chama o método que vai criar a url para a mídia a ser aberta.
		pBufferStringConvertido = Util.ConverterStringToChar(Param_UrlMidia);

		//Converte o char* para wchar*
		pBufferWchar = Util.ConverterConstCharToConstWCHAR(pBufferStringConvertido);

		//Obtém o ponteiro para os atributos.
		Param_Atributos->RecuperarPonteiro((LPVOID*)&pAtributos);

		//Chama o método para criar o leitor de mídia.
		Hr = MFCreateSourceReaderFromURL(pBufferWchar, pAtributos, &pSourceReader);

		//Processa o resultado da chamada.
		Resultado.ProcessarCodigoOperacao(Hr);

		//Verifica se obteve sucesso na operação.
		if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
		{
			//Falhou ao realizar a operação.

			//Sai do método
			Sair;
		}

		//Cria a instância da classe
		Param_Out_LeitorMidia = gcnew CarenMFSourceReader();

		//Chama o método para definir o ponteiro de trabalho na interface a ser retornada.
		Param_Out_LeitorMidia->AdicionarPonteiro(pSourceReader);

	Done:;
		//Deleta os buffers convertidos da string.
		if (pBufferStringConvertido == NULL)
		{
			//Deleta o buffer de alocado.
			delete pBufferStringConvertido;
		}
		if (pBufferWchar == NULL)
		{
			//Deleta o buffer de alocado.
			delete pBufferWchar;
		}

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





	//Métodos da interface ICarenMFSourceReader
public:
	/// <summary>
	/// Obtém o tipo de mídia atual para um fluxo.
	/// </summary>
	/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
	/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
	virtual CarenResult GetCurrentMediaType(UInt32 Param_IdFluxo, [Out] ICarenMFMediaType^% Param_Out_TipoMidia);

	/// <summary>
	/// Obtém um formato que é suportado nativamente pelo fonte de mídia.
	/// Este método consulta a fonte de mídia subjacente para seu (Formato) de (Saída Nativo). 
	/// Potencialmente, cada fluxo de origem pode produzir mais de um formato de saída. 
	/// Use o parâmetro Param_IdMediaTypeIndice para percorrer os formatos disponíveis
	/// </summary>
	/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
	/// <param name="Param_IdMediaTypeIndice">O Id para o tipo de mídia na lista a ser obtida. O valor pode ser qualquer um dos seguintes. Indice baseado em 0 ou o valor: 0xffffffff que representa o tipo da mídia nativa atual. </param>
	/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
	virtual CarenResult GetNativeMediaType(UInt32 Param_IdFluxo, UInt32 Param_IdMediaTypeIndice, [Out] ICarenMFMediaType^% Param_Out_TipoMidia);

	/// <summary>
	/// Obtém um determinado atributo da fonte de mídia atual.
	/// </summary>
	/// <param name="Param_IdFluxo">O fluxo ou objeto de consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID) para espeficar um valor padrão ao sistema.</param>
	/// <param name="Param_GuidAtributo">Um GUID que identifica o atributo para recuperar. Se o Param_IdFluxo parâmetro é igual a ID_FONTE_MIDIA, 
	/// Param_GuidAtributo pode especificar os atributos de: MFAtributos_DescritorApresentação, MF_SOURCE_READER_MEDIASOURCE_CHARACTERISTICS.
	/// Se Param_IdFluxo espeficifica um Fluxo, Param_GuidAtributo deve especificar um atributo do Descritor de Fluxo(GUIDs_MFAtributos_DescritorFluxo) </param>
	/// <param name="Param_Out_ValorAtributo">Retorna o valor do atributo solicitado</param>
	virtual CarenResult GetPresentationAttribute(UInt32 Param_IdFluxo, String^ Param_GuidAtributo, [Out] Estruturas::CA_PropVariant^% Param_Out_ValorAtributo);

	/// <summary>
	/// Consulta a fonte subjacente de mídia ou decodificador para uma interface.
	/// </summary>
	/// <param name="Param_IdFluxo">O fluxo ou objeto para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID). Se o valor for ID_FONTE_MIDIA, 
	/// o método consultará a fonte de mídia. Caso contrário, ele consulta o decodificador que está associado com o fluxo especificado.</param>
	/// <param name="Param_GuidServiço">Um identificador de serviço GUID, consulte a estrutura(MFInterfacesServiço) para  obter um GUID. Se o valor for (NULO), 
	/// o método chama (ConsultarInterface) para obter a interface solicitada. Caso contrário, o método chama o ICarenMFGetService.ObterServiço.</param>
	/// <param name="Param_GuidInterface">O identificador de interface (IID) da interface que está sendo solicitada..</param>
	/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface que foi solicitada. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetServiceForStream(UInt32 Param_IdFluxo, String^ Param_GuidServiço, String^ Param_GuidInterface, ICaren^ Param_Out_InterfaceDesconhecida);

	/// <summary>
	/// Consulta se um determinado fluxo, baseado em seu (Id) está selecionado.
	/// </summary>
	/// <param name="Param_IdFluxo">O Fluxo para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	/// <param name="Param_Out_ResultadoFluxoSelecionado">Recebe true se o fluxo é selecionado e irá gerar dados. Recebe false se o fluxo não está selecionado 
	/// e não irá gerar dados.</param>
	virtual CarenResult GetStreamSelection(UInt32 Param_IdFluxo, [Out] Boolean% Param_Out_ResultadoFluxoSelecionado);

	/// <summary>
	/// Método responsável por ler a proxima amostra de mídia disponivel na fonte de mídia. Defina todos os parametros (out) ou (ref) como 0 e Nulo para chamar o método em modo assincrono.
	/// Esse método pode retornar (Sucesso) e ainda assim retornar uma amostra de mídia (NULA).
	/// Consulte o resultado do parametro (Param_Out_FlagsLeituraAmostra) que vai indicar o resultado da leitura e o que se deve fazer.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id do fluxo que vai extrair os dados de mídia. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	/// <param name="Param_ControlFlag">Um flag para realizar a leitura da amostra de mídia. Pode deixar Zero, ou definir um valor da enumeração(CA_SOURCE_READER_CONTROL_FLAG)</param>
	/// <param name="Param_Out_ResultadoLeitura">Retorna o resultado da leitura de uma amostra.</param>
	/// <param name="Param_Out_IdFluxoLido">Retorna o Id do fluxo que foi extraido a amostra de mídia.</param>
	/// <param name="Param_Out_FlagsLeituraAmostra">Retorna um (Flag) que indca um resultado adicional a leitura da amostra. Utilize essa valor para decidir como deve processar o resultado do método.</param>
	/// <param name="Param_Out_TimSpanAmostra">Retorna o (TimeSpan) da amostra de mídia lida. TimeSpan indica a Data/Hora que deve iniciar uma amostra. Esse valor é dado em (unidades de 100 Nanosegundos).</param>
	/// <param name="Param_Ref_Amostra">Retorna a interface que contém a amostra de mídia que foi lida. O usuário deve inicializar a interface antes de chamar o método em modo sincrono.</param>
	virtual CarenResult ReadSample
	(
		UInt32 Param_IdFluxo, 
		UInt32 Param_ControlFlag, 
		[Out] Enumeracoes::CA_SAMPLE_READ_RESULT% Param_Out_ResultadoLeitura, 
		[Out] UInt32% Param_Out_IdFluxoLido, [Out] Enumeracoes::CA_SOURCE_READER_FLAGS% Param_Out_FlagsLeituraAmostra, 
		[Out] Int64% Param_Out_TimSpanAmostra, 
		ICarenMFSample^% Param_Ref_Amostra
	);

	/// <summary>
	/// Define o tipo de mídia para um fluxo.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo a ter o tipo de mídia definido. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	/// <param name="Param_ValorReservado">Valor reservado. Define como: 0</param>
	/// <param name="Param_TipoMidia">A interface com o (Tipo Mídia) a ser definida como o tipo atual.</param>
	virtual CarenResult SetCurrentMediaType(UInt32 Param_IdFluxo, UInt32 Param_ValorReservado, ICarenMFMediaType^ Param_TipoMidia);

	/// <summary>
	/// Define uma nova posição para ler as amostras de midia com base no tempo
	/// da apresentação.
	/// </summary>
	/// <param name="Param_PosiçãoNanoSegundos">A posição para leitura dos dados. O valor é dado em unidades de 100 nanosegundos.</param>
	virtual CarenResult SetCurrentPosition(Int64 Param_PosiçãoNanoSegundos);

	/// <summary>
	/// Seleciona ou Desseleciona um ou mais fluxos.
	/// [ATENCAO] - Se você (não vai precisar) de (dados) de um dos (Fluxos), é uma boa ideia para cancelar a seleção desse fluxo. Se o fluxo for 
	/// seleccionado, a fonte de mídia pode segurar uma fila de dados não lidos, e a fila pode crescer indefinidamente, consumindo memória e 
	/// consequentemente, gerando um Vazamento de memória(Memory Leak).
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo a ser selecionado. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	/// <param name="Param_EstadoSeleção">Define se deve (Selecionar) ou (Desselecionar) o fluxo especificado.</param>
	virtual CarenResult SetStreamSelection(UInt32 Param_IdFluxo, Boolean Param_EstadoSeleção);


	/// <summary>
	/// Libera um ou mais fluxos.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o fluxo a ser (Liberado). Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	virtual CarenResult Flush(UInt32 Param_IdFluxo);


	//Métodos da interface de (Extensão) ICarenLeitorMidiaExtensões
public:
	/// <summary>
	/// (Extensão) - Método responsável por retornar a quantidade de fluxos na mídia carregada pelo leitor.
	/// </summary>
	/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na mídia carregada.</param>
	virtual CarenResult ExRecuperarQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos);

	/// <summary>
	/// (Extensão) - Método responsável por retornar todos os tipos principais de mídia do arquivo carregado pelo leitor.
	/// </summary>
	/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de mídia no fluxo carregado</param>
	virtual CarenResult ExRecuperarTiposMidia([Out] System::Collections::Generic::List<CA_Midia_TipoPrincipal>^% Param_Out_TiposMidias);
};

