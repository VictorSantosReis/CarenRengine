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
#include "../SDK_Windows.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"
#include "../FunctionClass/GlobalFuncs.h"

//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Windows;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluida - Fase de Testes) - Classe responsável por representar um IStream que permite que você leia e escreva dados para transmitir objetos. Os objetos de fluxo contêm os 
/// dados em um objeto de armazenamento estruturado, onde os armazenamentos fornecem a estrutura.
/// </summary>
public ref class CarenStream : public ICarenStream
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IStream).
	IStream* PonteiroTrabalho = NULL;


	//Contrutores e destuidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenStream();

	/// <summary>
	/// Cria e inicializa ‎‎a classe‎‎ que envolve um fluxo byte da Microsoft Media Foundation.‎
	/// </summary>
	/// <param name="Param_ByteStream">‎Uma interface ‎‎ICarenMFByteStream‎‎ do fluxo byte da Media Foundation.‎</param>
	CarenStream(ICarenMFByteStream^ Param_ByteStream);

	/// <summary>
	/// Cria e inicializa a classe do Stream que se baseia em um fluxo de memória. Este construtor permite criar o fluxo a aprti 
	/// de dados iniciais.
	/// </summary>
	/// <param name="Param_BufferInicial">Uma interface (ICarenBuffer) para os dados iniciais. O conteúdo deste buffer é usado para definir o conteúdo inicial do fluxo de memória. 
	/// Se este parâmetro for NULO, o fluxo de memória retornado não terá nenhum conteúdo inicial.</param>
	/// <param name="Param_LarguraBuffer">O número de bytes no buffer apontado por (Param_BufferInicial). Se (Param_BufferInicial) estiver definido como NULO, (Param_LarguraBuffer) deve ser zero.</param>
	CarenStream(ICarenBuffer^ Param_BufferInicial, UInt32 Param_LarguraBuffer);
	
	/// <summary>
	/// Cria e inicializa a classe do Stream que se baseia em um fluxo de memória. Este construtor permite criar o fluxo a aprti 
	/// de dados iniciais.
	/// </summary>
	/// <param name="Param_BufferInicial">Uma matriz de bytes para os dados iniciais. O conteúdo deste buffer é usado para definir o conteúdo inicial do fluxo de memória. 
	/// Se este parâmetro for NULO, o fluxo de memória retornado não terá nenhum conteúdo inicial.</param>
	/// <param name="Param_LarguraBuffer">O número de bytes no buffer apontado por (Param_BufferInicial). Se (Param_BufferInicial) estiver definido como NULO, (Param_LarguraBuffer) deve ser zero.</param>
	CarenStream(MatrizBytes Param_BufferInicial, UInt32 Param_LarguraBuffer);

	~CarenStream();

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
			System::Console::WriteLine(String::Concat(ICarenStream::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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


	//Métodos da interface(ICarenStream)
public:
	/// <summary>
	/// O método Clone cria um novo objeto de fluxo com seu próprio ponteiro de busca que faz referência aos mesmos bytes do fluxo original.
	/// O método Clone cria um novo objeto de fluxo para acessar os mesmos bytes, mas usando um ponteiro de busca separado. O novo objeto de fluxo vê os mesmos dados do 
	/// objeto de fluxo de origem. As alterações escritas em um objeto são imediatamente visíveis no outro. O bloqueio de alcance é compartilhado entre os objetos do fluxo.
	/// A configuração inicial do ponteiro de busca na instância de fluxo clonado é a mesma da configuração atual do ponteiro de busca no fluxo original no momento da operação do clone.
	/// </summary>
	/// <param name="Param_Out_CloneInterface">Retorna uma interface (ICarenStream) clonada da interface atual.</param>
	virtual CarenResult Clone([Out] ICarenStream^% Param_Out_CloneInterface);

	/// <summary>
	/// O método Commit garante que quaisquer alterações feitas em um objeto de fluxo aberto no modo transacionado sejam refletidas no armazenamento pai. Se o objeto de fluxo
	/// estiver aberto no modo direto, o ICarenStream::Commit não tiver outro efeito além de direcionar todos os buffers de memória para o objeto de armazenamento de nível 
	/// próximo. A implementação de arquivos compostos COM de fluxos não suporta abertura de fluxos no modo transacionado.
	/// Se o fluxo estiver aberto no modo direto, este método garante que quaisquer buffers de memória tenham sido liberados para o objeto de armazenamento subjacente. 
	/// Isso é muito parecido com uma descarga nos sistemas de arquivos tradicionais.
	/// </summary>
	/// <param name="Param_CommitFlags">Controla como as alterações do objeto de fluxo são cometidas. Consulte a enumeração do STGC para obter uma definição desses valores.</param>
	virtual CarenResult Commit(CA_STGC Param_CommitFlags);

	/// <summary>
	/// O método CopyTo copia um número especificado de bytes do ponteiro de busca atual no fluxo para o ponteiro de busca atual em outro fluxo.
	/// O método CopyTo copia os bytes especificados de um fluxo para outro. Ele também pode ser usado para copiar um fluxo para si mesmo. O ponteiro de busca em cada 
	/// instância de fluxo é ajustado para o número de bytes lidos ou escritos.
	/// </summary>
	/// <param name="Param_StreamDestino">Um ponteiro para o fluxo de destino. O fluxo apontado pelo (Param_StreamDestino) pode ser um novo fluxo ou um clone do fluxo de origem.</param>
	/// <param name="Param_CountBytesCopy">O número de bytes para copiar a partir do fluxo de origem.</param>
	/// <param name="Param_Out_CountBytesReaded">Retorna o número real de bytes lidos a partir do fluxo de origem.</param>
	/// <param name="Param_Out_CountBytesWritten">Retorna o número real de bytes escritos para o fluxo de destino.</param>
	virtual CarenResult CopyTo(
	ICarenStream^ Param_StreamDestino,
	UInt64 Param_CountBytesCopy,
	[Out] UInt64% Param_Out_CountBytesReaded,
	[Out] UInt64% Param_Out_CountBytesWritten);

	/// <summary>
	/// O método LockRegion restringe o acesso a uma faixa especificada de bytes no fluxo. Suportar essa funcionalidade é opcional, uma vez que alguns sistemas de arquivos 
	/// não fornecem. A faixa de byte do fluxo pode ser estendida. Bloquear um intervalo estendido para o fluxo é útil como um método de comunicação entre diferentes instâncias 
	/// do fluxo sem alterar dados que realmente fazem parte do fluxo.
	/// Qualquer região bloqueada com ICarenStream::LockRegion deve ser desbloqueada explicitamente chamando ICarenStream::UnlockRegion com exatamente os mesmos valores para 
	/// os parâmetros Param_Offset, Param_CountBytes e Param_LockType.
	/// </summary>
	/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
	/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
	/// <param name="Param_LockType">Especifica as restrições solicitadas ao acessar o intervalo.</param>
	virtual CarenResult LockRegion(
	UInt64 Param_Offset,
	UInt64 Param_CountBytes,
	CA_LOCKTYPE Param_LockType);

	/// <summary>
	/// O método Revert descarta todas as alterações que foram feitas em um fluxo transacionado desde a última chamada ICarenStream::Commit. Em fluxos abertos no modo direto 
	/// e streams usando a implementação de arquivo composto COM do ICarenStream::Revert, este método não tem efeito.
	/// </summary>
	virtual CarenResult Revert();

	/// <summary>
	/// O método Seek altera o ponteiro de busca para um novo local. A nova localização é relativa ao início do fluxo, ao fim do fluxo ou ao ponteiro de busca atual.
	/// </summary>
	/// <param name="Param_Deslocamento">O deslocamento a ser adicionado ao local indicado pelo parâmetro (Param_Origem). Se (Param_Origem) é CA_STREAM_SEEK_SET, isso é 
	/// interpretado como um valor não assinado em vez de um valor assinado.</param>
	/// <param name="Param_Origem">A origem do deslocamento especificado em (Param_Deslocamento). A origem pode ser o início do arquivo(CA_STREAM_SEEK_SET), o ponteiro de 
	/// busca atual(CA_STREAM_SEEK_CUR), ou o final do arquivo(CA_STREAM_SEEK_END).</param>
	/// <param name="Param_Out_NovaPosicao">Retorna a nova posição do ponteiro de busca.</param>
	virtual CarenResult Seek(
	Int64 Param_Deslocamento,
	CA_STREAM_SEEK Param_Origem,
	[Out] UInt64% Param_Out_NovaPosicao);


	/// <summary>
	/// O método SetSize altera o tamanho do objeto de fluxo. O ponteiro de busca não é afetado pela mudança no tamanho do fluxo.
	/// Se o parâmetro (Param_NovoTamanho) for menor do que o fluxo atual, o fluxo será truncado ao tamanho indicado. 
	/// </summary>
	/// <param name="Param_NovoTamanho">Especifica o novo tamanho, em bytes, do fluxo.</param>
	virtual CarenResult SetSize(UInt64 Param_NovoTamanho);

	/// <summary>
	/// O método Stat recupera a estrutura CA_STATSTG para este fluxo.
	/// </summary>
	/// <param name="Param_Out_StaticsStream">Retorna uma estrutura STATSTG onde este método coloca informações sobre este objeto de fluxo.</param>
	/// <param name="Param_Flags">Especifica que este método não retorna alguns dos membros na estrutura STATSTG, salvando assim uma operação de alocação de memória. 
	/// Os valores são retirados da enumeração CA_STATFLAG.</param>
	virtual CarenResult Stat(
	[Out] CA_STATSTG^% Param_Out_StaticsStream,
	CA_STATFLAG Param_Flags);

	/// <summary>
	/// O método UnlockRegion remove a restrição de acesso em uma série de bytes previamente restritos com ICarenStream::LockRegion.
	/// </summary>
	/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
	/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
	/// <param name="Param_LockType">Especifica as restrições de acesso previamente colocadas no intervalo.</param>
	virtual CarenResult UnlockRegion(
	UInt64 Param_Offset,
	UInt64 Param_CountBytes,
	CA_LOCKTYPE Param_LockType);
};