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
#include "../SDK_MediaFoundationExtend.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::MediaFoundationExtended;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// Classe responsável por estender os métodos da interface (ICarenMFSourceReader), adicionando métodos para obter a quantidade de Fluxos e seus tipos na mídia carregada.
/// </summary>
public ref class CarenMFSourceReaderExtend : public ICarenMFSourceReaderExtend
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFSourceReader).
	IMFSourceReader* PonteiroTrabalho = NULL;


	//Contrutor e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFSourceReaderExtend();
	
	~CarenMFSourceReaderExtend();


	//Conversões implicitas
public:
	static operator CarenMFSourceReaderExtend^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMFSourceReaderExtend^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMFSourceReaderExtend();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMFSourceReader*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenMFSourceReaderExtend::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();


	//Métodos da interface(ICarenMFSourceReaderExtend)
public:
	/// <summary>
	/// (Extensão) - Método responsável por retornar a quantidade de fluxos na mídia carregada pelo leitor.
	/// </summary>
	/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na mídia carregada.</param>
	virtual CarenResult ExGetCountStreams(OutParam UInt32% Param_Out_QuantidadeFluxos);

	/// <summary>
	/// (Extensão) - Método responsável por retornar todos os tipos principais de mídia do arquivo carregado pelo leitor.
	/// </summary>
	/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de mídia no fluxo carregado</param>
	virtual CarenResult ExGetAllMediaTypesStream(OutParam List<Enumeracoes::CA_MAJOR_MEDIA_TYPES>^% Param_Out_TiposMidias);


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
	/// <param name="Param_GuidAtributo">Um GUID que identifica o atributo para recuperar. Se o Param_IdFluxo parâmetro é igual a ID_MF_SOURCE_READER_MEDIASOURCE, 
	/// Param_GuidAtributo pode especificar os atributos de: MFAtributos_DescritorApresentação, MF_SOURCE_READER_MEDIASOURCE_CHARACTERISTICS.
	/// Se Param_IdFluxo espeficifica um Fluxo, Param_GuidAtributo deve especificar um atributo do Descritor de Fluxo(GUIDs_MFAtributos_DescritorFluxo) </param>
	/// <param name="Param_Out_ValorAtributo">Retorna o valor do atributo solicitado</param>
	virtual CarenResult GetPresentationAttribute(UInt32 Param_IdFluxo, String^ Param_GuidAtributo, [Out] Estruturas::CA_PropVariant^% Param_Out_ValorAtributo);

	/// <summary>
	/// Consulta a fonte subjacente de mídia ou decodificador para uma interface.
	/// </summary>
	/// <param name="Param_IdFluxo">O fluxo ou objeto para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID). Se o valor for ID_MF_SOURCE_READER_MEDIASOURCE, 
	/// o método consultará a fonte de mídia. Caso contrário, ele consulta o decodificador que está associado com o fluxo especificado.</param>
	/// <param name="Param_GuidServiço">Um identificador de serviço GUID, consulte a estrutura(MFInterfacesServiço) para  obter um GUID. Se o valor for (NULO), 
	/// o método chama (ConsultarInterface) para obter a interface solicitada. Caso contrário, o método chama o ICarenMFGetService.ObterServiço.</param>
	/// <param name="Param_GuidInterface">O identificador de interface (IID) da interface que está sendo solicitada..</param>
	/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface que foi solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetServiceForStream(UInt32 Param_IdFluxo, String^ Param_GuidServiço, String^ Param_GuidInterface, ICaren^ Param_Out_InterfaceDesconhecida);

	/// <summary>
	/// Consulta se um determinado fluxo, baseado em seu (Id) está selecionado.
	/// </summary>
	/// <param name="Param_IdFluxo">O Fluxo para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
	/// <param name="Param_Out_ResultadoFluxoSelecionado">Recebe true se o fluxo é selecionado e irá gerar dados. Recebe false se o fluxo não está selecionado 
	/// e não irá gerar dados.</param>
	virtual CarenResult GetStreamSelection(UInt32 Param_IdFluxo, [Out] Boolean% Param_Out_ResultadoFluxoSelecionado);

	/// <summary>
	/// ‎Lê a próxima amostra disponivel da fonte de mídia.‎ 
	/// ‎Este método pode completar de forma sincrona ou assincrona. Se você fornecer um ponteiro de retorno de chamada(ICarenMFSourceReaderCallback) ao criar o leitor de origem, o método será assincrono. 
	/// Caso contrário, o método é sincrono.
	/// Para realizar uma chamada Assincrona, Ignore todos os parametros de saida(que contém o Out no nome). Caso contrario, o método retorna ER_E_INVALIDARG
	/// </summary>
	/// <param name="Param_StreamIndex">O index para o fluxo a ser extraido a amostra. Esse valor pode ser um UInt32 para um ID de fluxo valido ou um dos valores da enumeração (CA_SOURCE_READER_ID).</param>
	/// <param name="Param_ControlFlags">Um ‎‎Bitwise‎‎ OR de zero ou mais bandeiras da enumeração ‎‎(CA_MF_SOURCE_READER_CONTROL_FLAG).‎</param>
	/// <param name="Param_Out_ActualStreamIndex">Retorna o index baseado em zero para o fluxo atual.</param>
	/// <param name="Param_Out_StreamFlags">Retorna um ‎‎Bitwise‎‎ OR de zero ou mais bandeiras da enumeração ‎‎(‎‎MF_SOURCE_READER_FLAG) que indicam o status da chamada.</param>
	/// <param name="Param_Out_Timestamp">‎Retorna o carimbo de hora(Timestamp) da amostra ou a hora do evento de fluxo indicado em ‎‎(Param_Out_StreamFlags)‎‎. O tempo é dado em unidades de 100 nanossegundos.‎</param>
	/// <param name="Param_Out_Sample">Retorna uma interface (ICarenMFSample) ou (NULO). Se este parametro nao for NULO, o usuário é responsável por liberar a interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	virtual CarenResult ReadSample
	(
		UInt32 Param_StreamIndex,
		CA_MF_SOURCE_READER_CONTROL_FLAG Param_ControlFlags,
		CarenParameterResolver<UInt32> Param_Out_ActualStreamIndex,
		CarenParameterResolver<CA_MF_SOURCE_READER_FLAG> Param_Out_StreamFlags,
		CarenParameterResolver<Int64> Param_Out_Timestamp,
		CarenParameterResolver<ICarenMFSample^> Param_Out_Sample
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
};