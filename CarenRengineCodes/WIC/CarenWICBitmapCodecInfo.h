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
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que fornecem informações sobre um codec específico.
/// </summary>
public ref class CarenWICBitmapCodecInfo : public ICarenWICBitmapCodecInfo
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICBitmapCodecInfo).
	IWICBitmapCodecInfo* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICBitmapCodecInfo();
	
	~CarenWICBitmapCodecInfo();

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
			System::Console::WriteLine(String::Concat(ICarenWICBitmapCodecInfo::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICBitmapCodecInfo)
public:
	/// <summary>
	/// Recupera um valor indicando se o codec suporta animação. 
	/// </summary>
	/// <param name="Param_Out_SuporteAnimacao">Recebe TRUE se o codec suporta imagens com informações de cronometragem; caso contrário, FALSO.</param>
	virtual CarenResult DoesSupportAnimation([Out] Boolean% Param_Out_SuporteAnimacao);

	/// <summary>
	/// Recupera um valor indicando se o codec suporta chromakeys. 
	/// </summary>
	/// <param name="Param_Out_SuporteChromakey">Recebe TRUE se o codec suportar chromakeys; caso contrário, FALSO.</param>
	virtual CarenResult DoesSupportChromakey([Out] Boolean% Param_Out_SuporteChromakey);

	/// <summary>
	/// Recupera um valor indicando se o codec suporta formatos sem perdas. 
	/// </summary>
	/// <param name="Param_Out_SuporteLossLess">Recebe TRUE se o codec suportar formatos sem perdas; caso contrário, FALSO.</param>
	virtual CarenResult DoesSupportLossless([Out] Boolean% Param_Out_SuporteLossLess);

	/// <summary>
	/// Recupera um valor indicando se o codec suporta imagens de vários quadros. 
	/// </summary>
	/// <param name="Param_Out_SuporteMultiframe">Recebe TRUE se o codec suportar imagens de vários quadros; caso contrário, FALSO.</param>
	virtual CarenResult DoesSupportMultiframe([Out] Boolean% Param_Out_SuporteMultiframe);

	/// <summary>
	/// Recupera o número da versão de manangement de cor que o codec suporta. 
	/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo 
	/// da versão de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_VersaoColorManagement) definido para NULO. Esta chamada define (Param_Out_SizeAtual)
	///  para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetColorManagementVersion com (Param_Size) definida para o tamanho do 
	/// buffer e (Param_Ref_VersaoColorManagement) definido para um buffer do tamanho apropriado recuperará os formatos de pixel
	/// </summary>
	/// <param name="Param_Size">O tamanho do buffer da versão. Use na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Ref_VersaoColorManagement">Recebe o número da versão de gerenciamento de cores. Use na primeira chamada para determinar o tamanho do buffer necessário</param>
	/// <param name="Param_Out_SizeAtual">Recebe tamanho real do buffer necessário para recuperar o número completo da versão de gerenciamento de cores.</param>
	virtual CarenResult GetColorManagementVersion(
	UInt32 Param_Size,
	String^% Param_Ref_VersaoColorManagement,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o guid do contêiner associado ao codec.
	/// </summary>
	/// <param name="Param_Out_GuidFormatoContainer">Recebe o GUID do formato do container.</param>
	virtual CarenResult GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer);

	/// <summary>
	/// Recupera o nome da fabricação do dispositivo associada ao codec.
	/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo da versão
	/// de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_ModelosDispositivo) definido para NULO. Esta chamada define (Param_Out_SizeAtual) 
	/// para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetDeviceManufacturer com (Param_Size) 
	/// definido para o tamanho do buffer e 
	/// (Param_Ref_ModelosDispositivo) definido para um buffer do tamanho apropriado recuperará os formatos de pixel.
	/// </summary>
	/// <param name="Param_Size">O tamanho do nome da fabricação do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário</param>
	/// <param name="Param_Ref_FabricanteDispositivo">Recebe o nome da fabricação do dispositivo. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar o nome do fabricante do dispositivo.</param>
	virtual CarenResult GetDeviceManufacturer(
	UInt32 Param_Size,
	String^% Param_Ref_FabricanteDispositivo,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera uma lista delimitada de vírgula de modelos de dispositivos associados ao codec.
	/// Defina (Param_Size) para 0 e (Param_Ref_ModelosDispositivo) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_ModelosDispositivo)
	/// que deve ser definida em (Param_Size).
	/// </summary>
	/// <param name="Param_Size">O tamanho do buffer dos modelos do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Ref_ModelosDispositivo">Recebe uma lista delimitada de vírgula de nomes de modelos de dispositivos associados ao codec. Use NULO na primeira chamada para
	///  determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os nomes dos modelos do dispositivo.</param>
	virtual CarenResult GetDeviceModels(
	UInt32 Param_Size,
	String^% Param_Ref_ModelosDispositivo,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera uma lista delimitada de vírgula das extensões de nome do arquivo associadas ao codec. A extensão padrão de um codificador de imagem é o primeiro item 
	/// da lista de extensões devolvidas. Defina (Param_Size) para 0 e (Param_Ref_ExtensoesArquivos) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário 
	/// do buffer(Param_Ref_ExtensoesArquivos) que deve ser definida em (Param_Size).
	/// </summary>
	/// <param name="Param_Size">O tamanho do buffer de extensão do nome do arquivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Ref_ExtensoesArquivos">Recebe uma lista delimitada de vírgula de extensões de nomes de arquivo associadas ao codec. Use NULO na primeira chamada para 
	/// determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todas as extensões de nome do arquivo associadas ao codec.</param>
	virtual CarenResult GetFileExtensions(
	UInt32 Param_Size,
	String^% Param_Ref_ExtensoesArquivos,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera uma sequência delimitada de vírgula de tipos de mímicos associados ao codec. 
	/// Defina (Param_Size) para 0 e (Param_Ref_MimeTypes) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_MimeTypes) que 
	/// deve ser definida em (Param_Size).
	/// </summary>
	/// <param name="Param_Size">O tamanho do mímico tipo tampão. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Ref_MimeTypes">Recebe os tipos de mímica associados ao codec. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os tipos de mímica associados ao codec.</param>
	virtual CarenResult GetMimeTypes(
	UInt32 Param_Size,
	String^% Param_Ref_MimeTypes,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera os formatos de pixel que o codec suporta.
	/// Defina (Param_Size) para 0 e (Param_Ref_FormatosPixel) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_FormatosPixel)
	///  que deve ser definida em (Param_Size).
	/// </summary>
	/// <param name="Param_Size">O tamanho da matriz (Param_Ref_FormatosPixel). Use 0 na primeira chamada para determinar o tamanho da matriz necessária.</param>
	/// <param name="Param_Ref_FormatosPixel">Recebe os formatos pixel suportados. Use NULO na primeira chamada para determinar o tamanho necessário da matriz</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho do array necessário para recuperar todos os formatos de pixel suportados.</param>
	virtual CarenResult GetPixelFormats(
	UInt32 Param_Size,
	cli::array<String^>^% Param_Ref_FormatosPixel,
	[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera um valor indicando se o tipo de mímica dado corresponde ao tipo mímico do codec. 
	/// </summary>
	/// <param name="Param_MimeType">O tipo do MimeType para comparar.</param>
	/// <param name="Param_Out_Corresponde">Recebe TRUE se os tipos de mímica correspondem; caso contrário, FALSO.</param>
	virtual CarenResult MatchesMimeType(
	String^ Param_MimeType,
	[Out] Boolean% Param_Out_Corresponde);


	//Métodos da interface(ICarenWICComponentInfo)
public:
	/// <summary>
	/// Recupera o nome do autor do componente. Se (Param_SizeAutorString) for 0 e (Param_Ref_Autor) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeAutorString">O tamanho da String (Param_Ref_Autor).</param>
	/// <param name="Param_Ref_Autor">Recebe o nome do autor do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da instalação.
	///  Para componentes embutidos, essas Strings estão sempre em inglês.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome dos autores do componente. O nome do autor é opcional; se um nome autor não for especificado pelo componente,
	///  o comprimento devolvido será 0.</param>
	virtual CarenResult GetAuthor(
		UInt32 Param_SizeAutorString,
		String^% Param_Ref_Autor,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o identificador de classe do componente (CLSID) 
	/// </summary>
	/// <param name="Param_Out_CLSID">Recebe o CLSID do componente.</param>
	virtual CarenResult GetCLSID([Out] String^% Param_Out_CLSID);

	/// <summary>
	/// Recupera o CA_WICComponentType do componente. 
	/// </summary>
	/// <param name="Param_Out_Type">Recebe um enum CA_WICComponentType que define o tipo do componente.</param>
	virtual CarenResult GetComponentType([Out] CA_WICComponentType% Param_Out_Type);

	/// <summary>
	/// Recupera o nome amigável do componente, que é um nome de exibição legível por humanos para o componente.
	/// Se (Param_SizeNomeString) for 0 e (Param_Ref_NomeAmigavel) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeNomeString">O tamanho da String em (Param_Ref_NomeAmigavel).</param>
	/// <param name="Param_Ref_NomeAmigavel">Recebe o nome amigável do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da 
	/// instalação. Para componentes embutidos, essas cordas 
	/// estão sempre em inglês.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome amigável do componente.</param>
	virtual CarenResult GetFriendlyName(
		UInt32 Param_SizeNomeString,
		String^% Param_Ref_NomeAmigavel,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o status de assinatura do componente. A assinatura não é usada pelo WIC. Portanto, todos os componentes WICComponentSigned. Esta função pode ser usada para 
	/// determinar se um componente não possui nenhum componente 
	/// binário ou foi adicionado à lista de componentes desabilitados no registro.
	/// </summary>
	/// <param name="Param_Out_Status">Retorna um enum que recebe o status do componente.</param>
	virtual CarenResult GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status);

	/// <summary>
	/// Recupera a versão de especificação do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão spec.
	/// Se (Param_SizeSpecString) for 0 e (Param_Ref_SpecVersion) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeSpecString">O tamanho da String em (Param_Ref_SpecVersion).</param>
	/// <param name="Param_Ref_SpecVersion">Retorna uma string que contém uma sequência de cultura invariente da versão de especificação do componente. O formulário de versão 
	/// é NN.NN.NN.NN.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão de especificação do componente. A versão de especificação é opcional; se um valor não for especificado
	///  pelo componente, o comprimento devolvido será 0.</param>
	virtual CarenResult GetSpecVersion(
		UInt32 Param_SizeSpecString,
		String^% Param_Ref_SpecVersion,
		[Out] UInt32% Param_Out_SizeAtual);

	/// <summary>
	/// Recupera o fornecedor GUID. 
	/// </summary>
	/// <param name="Param_Out_GuidVendor">Recebe o guid do fornecedor do componente.</param>
	virtual CarenResult GetVendorGUID([Out] String^% Param_Out_GuidVendor);

	/// <summary>
	/// Recupera a versão do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão.
	/// Se (Param_SizeVersionString) for 0 e (Param_Ref_Version) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
	/// </summary>
	/// <param name="Param_SizeVersionString">O tamanho da String em (Param_Ref_Version).</param>
	/// <param name="Param_Ref_Version">Recebe uma sequência de cultura invariante da versão do componente.</param>
	/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão do componente. A versão é opcional; se um valor não for especificado pelo componente, o comprimento
	///  devolvido será 0.</param>
	virtual CarenResult GetVersion(
		UInt32 Param_SizeVersionString,
		String^% Param_Ref_Version,
		[Out] UInt32% Param_Out_SizeAtual);
};