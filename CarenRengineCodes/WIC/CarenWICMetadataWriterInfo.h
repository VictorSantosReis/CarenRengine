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
#include "CarenWICMetadataWriter.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que fornecem informações básicas sobre o gravador de metadados registrado.
/// </summary>
public ref class CarenWICMetadataWriterInfo : public ICarenWICMetadataWriterInfo
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICMetadataWriterInfo).
	IWICMetadataWriterInfo* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICMetadataWriterInfo();
	
	~CarenWICMetadataWriterInfo();


	//Conversões implicitas
public:
	static operator CarenWICMetadataWriterInfo^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenWICMetadataWriterInfo^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenWICMetadataWriterInfo();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IWICMetadataWriterInfo*>(Param_Pointer.ToPointer());

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
			System::Console::WriteLine(String::Concat(ICarenWICMetadataWriterInfo::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICMetadataWriterInfo)
public:
	/// <summary>
	/// Cria uma instância de um ICarenWICMetadataWriter. 
	/// </summary>
	/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados.</param>
	virtual CarenResult CreateInstance([Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

	/// <summary>
	/// Recebe o cabeçalho de metadados para o escritor de metadados. 
	/// </summary>
	/// <param name="Param_GuidContainerFormat">O GUID do contêiner de formato para o qual obter o cabeçalho.</param>
	/// <param name="Param_SizeHeader">O tamanho do buffer em (Param_Ref_Header).</param>
	/// <param name="Param_Ref_Header">Retorna uma estrutura com o header dos metadados. Defina como NULO para retornar o (SizeHeader) em (Param_Out_SizeAtual) necessário para o 
	/// parametro (Param_SizeHeader).</param>
	/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do cabeçalho.</param>
	virtual CarenResult GetHeader(
	String^ Param_GuidContainerFormat,
	UInt32 Param_SizeHeader,
	CA_WICMetadataHeader^% Param_Ref_Header,
	[Out] UInt32% Param_Out_SizeAtual);


	//Métodos da interface(ICarenWICMetadataHandlerInfo)
public:
	/// <summary>
	/// Determina se o manipulador de metadados requer um tamanho fixo. 
	/// </summary>
	/// <param name="Param_Out_FixedSize">Retorna TRUE se um tamanho fixo for necessário; caso contrário, FALSO.</param>
	virtual CarenResult DoesRequireFixedSize([Out] Boolean% Param_Out_FixedSize);

	/// <summary>
	/// Determina se o manipulador requer um fluxo completo. 
	/// </summary>
	/// <param name="Param_Out_RequerFullStream">Retorna TRUE se um fluxo completo for necessário; caso contrário, FALSO.</param>
	virtual CarenResult DoesRequireFullStream([Out] Boolean% Param_Out_RequerFullStream);

	/// <summary>
	/// Determina se o manipulador de metadados suporta preenchimento. 
	/// </summary>
	/// <param name="Param_Out_SuportaPadding">Retorna TRUE se o preenchimento for suportado; caso contrário, FALSO.</param>
	virtual CarenResult DoesSupportPadding([Out] Boolean% Param_Out_SuportaPadding);

	/// <summary>
	/// Recupera os formatos de contêiner suportados pelo manipulador de metadados. 
	/// </summary>
	/// <param name="Param_TamanhoArray"><O tamanho da matriz (Param_Out_ArrayGuidsFormatosContainer).</param>
	/// <param name="Param_Ref_Out_ArrayGuidsFormatosContainer">Retorna uma matriz que recebe os formatos de contêiner suportados pelo manipulador de metadados. O usuário deve criar matriz com a capacidade
	/// indicada no (Param_TamanhoArray).</param>
	/// <param name="Param_Out_QuantidadeRetornada">Retorna o número real de GUIDs adicionados à matriz. Para obter o número de formatos de contêiner suportados, 
	/// passe NULO para (Param_Out_ArrayGuidsFormatosContainer).</param>
	virtual CarenResult GetContainerFormats(
		UInt32 Param_TamanhoArray,
		cli::array<String^>^% Param_Ref_Out_ArrayGuidsFormatosContainer,
		[Out] UInt32% Param_Out_QuantidadeRetornada);

	/// <summary>
	/// Recupera o fabricante do dispositivo do manipulador de metadados. 
	/// </summary>
	/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceManufacturer).</param>
	/// <param name="Param_Ref_DeviceManufacturer">Retorna a String que recebe o nome do fabricante do dispositivo.</param>
	/// <param name="Param_Out_LarguraReal">Retorna o comprimento real da sequência de strinds necessário para obter o nome inteiro do fabricante do dispositivo.</param>
	virtual CarenResult GetDeviceManufacturer(
		UInt32 Param_TamanhoBufferString,
		String^% Param_Ref_DeviceManufacturer,
		[Out] UInt32% Param_Out_LarguraReal);

	/// <summary>
	/// Recupera os modelos do dispositivo que suportam o manipulador de metadados. 
	/// </summary>
	/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceModels).</param>
	/// <param name="Param_Ref_DeviceModels">Retorna os modelos do dispositivo suportados pelo manipulador de metadados.</param>
	/// <param name="Param_Out_LarguraReal">Retorna o comprimento real necessário para recuperar os modelos do dispositivo.</param>
	virtual CarenResult GetDeviceModels(
		UInt32 Param_TamanhoBufferString,
		String^% Param_Ref_DeviceModels,
		[Out] UInt32% Param_Out_LarguraReal);

	/// <summary>
	/// Recupera o formato de metadados do manipulador de metadados. 
	/// </summary>
	/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
	virtual CarenResult GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata);


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