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
#include "../SDK_WIC.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos para decodificar imagens JPEG. Fornece acesso ao cabeçalho Start Of Frame (SOF), cabeçalho Start of Scan (SOS), 
/// tabelas Huffman e Quantization e dados JPEG JPEG compactados.
/// </summary>
public ref class CarenWICJpegFrameDecode : public ICarenWICJpegFrameDecode
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICJpegFrameDecode).
	IWICJpegFrameDecode* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICJpegFrameDecode();
	
	~CarenWICJpegFrameDecode();


	//Conversões implicitas
public:
	static operator CarenWICJpegFrameDecode^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICJpegFrameDecode^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICJpegFrameDecode();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICJpegFrameDecode*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenWICJpegFrameDecode::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICJpegFrameDecode)
public:
	/// <summary>
	/// Remove a indexação de um JPEG que foi indexado usando ICarenWICJpegFrameDecode::SetIndexing. 
	/// </summary>
	virtual CarenResult ClearIndexing();

	/// <summary>
	/// Recupera uma cópia do scan JPEG compactada diretamente do fluxo de saída do frame de decodificador WIC. 
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_ScanOffset">A posição byte nos dados de varredura para começar a copiar. Use 0 na primeira chamada. Se o tamanho do buffer de saída for insuficiente para 
	/// armazenar toda a varredura, este deslocamento permite que você retome a cópia do final da operação anterior da cópia.</param>
	/// <param name="Param_ScanDataSize">O tamanho, em bytes, da matriz (Param_Out_ScanDataBuffer).</param>
	/// <param name="Param_ScanDataBufferDestino">Uma interface (ICarenBuffer) que contém o buffer que vai receber os dados da tabela.. Esse parametro não pode ser nulo.</param>
	/// <param name="Param_Out_BufferSizeAtual">Retorna o tamanho dos dados de varredura realmente copiados em (Param_Out_ScanDataBuffer). O tamanho devolvido pode ser menor que o tamanho do (Param_ScanDataSize).</param>
	virtual CarenResult CopyScan(
	UInt32 Param_ScanIndex,
	UInt32 Param_ScanOffset,
	UInt32 Param_ScanDataSize,
	ICarenBuffer^ Param_ScanDataBufferDestino,
	[Out] UInt32% Param_Out_BufferSizeAtual);

	/// <summary>
	/// Recupera um valor indicando se esse decodificador suporta indexação para acesso aleatório eficiente. A indexação só é suportada para alguns tipos de JPEG.
	/// </summary>
	/// <param name="Param_Out_Suporte">Retorna TRUE se a indexação for suportada; caso contrário, FALSE.</param>
	virtual CarenResult DoesSupportIndexing([Out] Boolean% Param_Out_Suporte);

	/// <summary>
	/// Recupera uma cópia da tabela AC Huffman para a digitalização e a tabela especificadas. 
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
	/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
	/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetAcHuffmanTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_AC_HUFFMAN_TABLE^% Param_Out_ACHuffmanTable);

	/// <summary>
	/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas. 
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho de 
	/// varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
	/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetDcHuffmanTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_DC_HUFFMAN_TABLE^% Param_Out_DCHuffmanTable);

	/// <summary>
	/// Recupera dados de cabeçalho de todo o frame. O resultado inclui parâmetros do marcador Start Of Frame (SOF) para a varredura, bem como parâmetros derivados de outros metadados, 
	/// como o modelo de cor dos dados comprimidos.
	/// </summary>
	/// <param name="Param_Out_FrameHeader">Retrona uma estrutura que contém os dados do cabeçalho do frame.</param>
	virtual CarenResult GetFrameHeader([Out] CA_WICJpegFrameHeader^% Param_Out_FrameHeader);

	/// <summary>
	/// Recupera uma cópia da tabela de quantização. 
	/// </summary>
	/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
	/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
	/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
	/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
	virtual CarenResult GetQuantizationTable(
	UInt32 Param_ScanIndex,
	UInt32 Param_TableIndex,
	[Out] CA_DXGI_JPEG_QUANTIZATION_TABLE^% Param_Out_QuantizationTable);

	/// <summary>
	/// Recupera parâmetros do marcador START Of Scan (SOS) para o scan com o índice especificado. 
	/// </summary>
	/// <param name="Param_ScanIndex">O índice da varredura para a qual os dados do cabeçalho são recuperados.</param>
	/// <param name="Param_Out_ScanHeader">Retorna uma estrutura que contém os dados de cabeçalho do frame.</param>
	virtual CarenResult GetScanHeader(
	UInt32 Param_ScanIndex,
	[Out] CA_WICJpegScanHeader^% Param_Out_ScanHeader);

	/// <summary>
	/// Permite a indexação do JPEG para acesso aleatório eficiente.
	/// Este método permite um acesso aleatório eficiente aos pixels de imagem em detrimento do uso da memória. A quantidade de memória necessária para a indexação depende da 
	/// granularidade do índice solicitado. A menos que o SetIndexing seja chamado, é muito mais eficiente acessar um JPEG progredindo através de seus pixels de cima para baixo 
	/// durante as chamadas para ICarenWICBitmapFonte::CopyPixels.
	/// Este método falhará se a indexação não for suportada no arquivo. IWICJpegFrameDecode::DoesSupportIndexing deve ser chamado primeiro para determinar se a indexação é suportada. 
	/// Se esse método for chamado várias vezes, a chamada final altera a granularidade do índice para o tamanho solicitado.
	/// </summary>
	/// <param name="Param_Opcoes">Um valor especificando se os índices devem ser gerados imediatamente ou diferidos até uma chamada futura para ICarenWICBitmapFonte::CopyPixels.</param>
	/// <param name="Param_HorizontalIntervalSize">A granularidade da indexação, em pixels.</param>
	virtual CarenResult SetIndexing(
	CA_WICJpegIndexingOptions Param_Opcoes,
	UInt32 Param_HorizontalIntervalSize);
};