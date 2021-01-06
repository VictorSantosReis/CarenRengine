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
#include "../Windows/CarenEnumUnknown.h"
#include "CarenWICMetadataReader.h"
#include "CarenWICMetadataWriter.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::WIC;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por expor métodos que permitem a codificação de metadados. Essa interface é implementada pelo decodificador e seus frames 
/// de imagem.
/// </summary>
public ref class CarenWICMetadataBlockWriter : public ICarenWICMetadataBlockWriter
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IWICMetadataBlockWriter).
	IWICMetadataBlockWriter* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenWICMetadataBlockWriter();
	
	~CarenWICMetadataBlockWriter();

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
			System::Console::WriteLine(String::Concat(ICarenWICMetadataBlockWriter::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenWICMetadataBlockWriter)
public:
	/// <summary>
	/// Adiciona um bloco de metadados de alto nível adicionando um ICarenWICMetadataWriter para ele. 
	/// </summary>
	/// <param name="Param_MetadataWriter">O escritor de metadados para adicionar à imagem.</param>
	virtual CarenResult AddWriter(ICarenWICMetadataWriter^ Param_MetadataWriter);

	/// <summary>
	/// Recupera o ICarenWICMetadataWriter que reside no índice especificado. 
	/// </summary>
	/// <param name="Param_Index">O índice do escritor de metadados a ser recuperado. Este índice é baseado em zero.</param>
	/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados que reside no índice especificado.</param>
	virtual CarenResult GetWriterByIndex(
	UInt32 Param_Index,
	[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter);

	/// <summary>
	/// Inicializa um ICarenWICMetadataBlockWriter do dado ICarenWICMetadataBlockReader. Isso prepovoará o autor do bloco de metadados com todos os metadados no leitor de blocos de metadados. 
	/// </summary>
	/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataBlockReader) que será usada para inicializar o escritor.</param>
	virtual CarenResult InitializeFromBlockReader(ICarenWICMetadataBlockReader^ Param_MetadataReader);

	/// <summary>
	/// Remove o escritor de metadados do local do índice especificado.
	/// Depois de remover um escritor de metadados, espera-se que os escritores de metadados restantes se movam para ocupar o local desocupado. Os índices para itens de 
	/// metadados restantes, bem como a contagem, mudarão.
	/// </summary>
	/// <param name="Param_Index">O índice do escritor de metadados para remover.</param>
	virtual CarenResult RemoveWriterByIndex(UInt32 Param_Index);

	/// <summary>
	/// Substitui o escritor de metadados no local do índice especificado.
	/// Normalmente, o escritor de metadados atuais no índice especificado será substituído pelo novo escritor. No entanto, o autor de metadados app0 não pode ser 
	/// substituído dentro de um fluxo JPEG. Esta função não pode ser usada para adicionar escritores de metadados. Se não houver nenhum autor de metadados no índice especificado, a função falhará.
	/// </summary>
	/// <param name="Param_Index">A posição do índice para colocar o escritor de metadados. Este índice é baseado em zero.</param>
	/// <param name="Param_MetadataWriter">A interface de escrita de metadados a ser definida no indice.</param>
	virtual CarenResult SetWriterByIndex(
	UInt32 Param_Index,
	ICarenWICMetadataWriter^ Param_MetadataWriter);


	//Métodos da interface(ICarenWICMetadataBlockReader)
public:
	/// <summary>
	/// Recupera o formato do recipiente do decodificador. 
	/// </summary>
	/// <param name="Param_Out_GuidFormatoContainer">Retorna o formato do contêiner do decodificador. </param>
	virtual CarenResult GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer);

	/// <summary>
	/// Recupera o número de blocos de metadados de nível superior. 
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna o número de blocos de metadados de nível superior.</param>
	virtual CarenResult GetCount([Out] UInt32% Param_Out_Quantidade);

	/// <summary>
	/// Recupera uma enumeração dos objetos ICarenWICMetadataReader representando cada um dos blocos de metadados de nível superior. 
	/// </summary>
	/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para uma enumeração dos objetos ICarenWICMetadataReader.</param>
	virtual CarenResult GetEnumerator([Out] ICarenEnumUnknown^% Param_Out_EnumMetadata);

	/// <summary>
	/// Recupera um ICarenWICMetadataReader para um bloco de metadados de nível superior especificado. 
	/// </summary>
	/// <param name="Param_Index">O índice do bloco de metadados de nível superior desejado para recuperar.</param>
	/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o ICarenWICMetadataReader especificado por (Param_Index).</param>
	virtual CarenResult GetReaderByIndex(
		UInt32 Param_Index,
		[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader);
};