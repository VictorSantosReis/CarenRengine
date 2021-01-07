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
#include "Header.h"
#include "SDK_Base.h"

//Importa os namespaces base.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Abre o namespace principal
namespace CarenRengine
{
	/// <summary>
	/// Interface responsável por representar a base de todas as demais interfaces da biblioteca. Espelha a interface nativa IUnknown.
	/// ICaren permite gerenciar a existência de um objeto nativo(COM) associado a ela e entrega ao usuário a possibilidade de obter ponteiros
	/// para outras interfaces do objeto COM associado.
	/// Está interface permite associar quaisquer ponteiros que não seje direta ou indiretamente um objeto COM. Restringindo apenas os métodos
	/// que competem a objetos COM.
	/// Essa interface serve de "ponte" para demais APIs e como uma extensão, permitindo ao usuário criar e associar suas próprias interfaces
	/// nativas a uma interface específica da biblioteca.
	/// </summary>
	[CategoryAttribute("Caren Interface")]
	[DescriptionAttribute("Interface base da biblioteca de Mulitimédia.")]
	[Guid("7E4D91F6-7189-4837-B279-E3E23AFCA893")]
	public interface class ICaren
	{
		/// <summary>
		/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
		/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
		/// interface depois de adicionar uma nova referência(AddRef).
		/// </summary>
		/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
		/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
		CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

		/// <summary>
		/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
		/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
		/// </summary>
		/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
		CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

		/// <summary>
		/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
		/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
		/// </summary>
		/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
		CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

		/// <summary>
		/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar CarenResult::ER_PONTEIRO.
		/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
		/// </summary>
		/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
		CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

		/// <summary>
		/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar CarenResult::ER_PONTEIRO.
		/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
		/// </summary>
		/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
		CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

		/// <summary>
		/// Método responsável por retornar a quantidade de referências do objeto COM atual.
		/// </summary>
		/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
		CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

		/// <summary>
		/// Método responsável por indicar se o ponteiro COM atual é válido.
		/// </summary>
		CarenResult StatusPonteiro();

		/// <summary>
		/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
		/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
		/// </summary>
		Int32 ObterCodigoErro();

		/// <summary>
		/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
		/// você fazer uma cópia de um ponteiro de interface.
		/// </summary>
		void AdicionarReferencia();

		/// <summary>
		/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
		/// </summary>
		void LiberarReferencia();

		/// <summary>
		/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
		/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
		/// </summary>
		/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
		/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
		/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
		generic <typename TypeClass, typename TypeInterface>
		TypeInterface As(cli::array<Object^>^ Param_Args);

		/// <summary>
		/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
		/// Este método pode ser escrito de forma diferente para cada interface.
		/// </summary>
		void Finalizar();
	};

	/// <summary>
	/// (INACarenObjectState) - Interface responsável por representar um objeto de estado que pode ser utilizadas por métodos nativos para operações assincronas.
	/// </summary>
	[CategoryAttribute("Caren Interface")]
	[Guid("F26DDE8E-4E7C-416D-A05B-0B81CB9B17BE")] //IGUAL AO DA NATIVA.
	public interface class ICarenObjectState : ICaren
	{
		/// <summary>
		/// Propriedade que define se a classe foi descartada.
		/// </summary>
		property Boolean DisposedClasse
		{
			virtual Boolean get();
		}


		//Métodos

		/// <summary>
		/// Retorna o nome do objeto de estado atual se válido.
		/// </summary>
		/// <param name="Param_Out_NomeObjeto">Recebe o nome do objeto atual.</param>
		/// <returns></returns>
		CarenResult GetName(OutParam String^% Param_Out_NomeObjeto);

		/// <summary>
		/// Retorna a largura do nome do objeto de estado atual.
		/// </summary>
		/// <param name="Param_Out_Size">Recebe a largura da string.</param>
		/// <returns></returns>
		CarenResult GetNameLenght(OutParam UInt32% Param_Out_Size);

		/// <summary>
		///  Define um novo nome para o objeto de estado atual.
		/// </summary>
		/// <param name="Param_Nome">O novo nome do objeto.</param>
		/// <param name="Param_SizeNome">A largura do novo nome.</param>
		/// <returns></returns>
		CarenResult SetName(String^ Param_Nome, UInt32 Param_SizeNome);
	};

	/// <summary>
	/// [TESTE] - Nova interface de Buffer.
	/// </summary>
	[CategoryAttribute("Caren Interface")]
	[Guid("2587F0D9-6A15-4901-BB55-42B36C3BCBAF")]
	public interface class ICarenBuffer : System::Collections::IEnumerable
	{
		/// <summary>
		/// Propriedade que contém a posição atual do buffer.
		/// </summary>
		property UInt32 Posição
		{
			virtual UInt32 get();
		}

		/// <summary>
		/// Propriedade que contém o tamanho maximo do buffer.
		/// </summary>
		property UInt32 Tamanho
		{
			virtual UInt32 get();
			virtual void set(UInt32);
		}

		/// <summary>
		/// Propriedade que contém a largura em bytes de dados válidos no buffer.
		/// </summary>
		property UInt32 TamanhoValido
		{
			virtual UInt32 get();
			virtual void set(UInt32);
		}

		/// <summary>
		/// Propriedade que informa se a interface foi descartada.
		/// </summary>
		property Boolean DisposedClasse
		{
			virtual Boolean get();
		}

		//Indexador para acessar e gravar diretamente no buffer.
#pragma region Indexador
		property Byte default[int]
		{
			virtual Byte get(int p_Index);
			virtual void set(int, Byte);
		}
#pragma endregion


			//Métodos

			/// <summary>
			/// Método responsável por alocar um novo buffer de tamanho especificado.
			/// </summary>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer a ser criado.</param>
			/// <returns></returns>
		CarenResult CriarBuffer(UInt32 Param_TamanhoBuffer);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
		/// </summary>
		/// <param name="Param_BufferOrigem">Um ponteiro para o buffer de origem.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(ICarenBuffer^ Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
		/// </summary>
		/// <param name="Param_BufferOrigem">O ponteiro para o buffer de origem.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(IntPtr Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente.
		/// </summary>
		/// <param name="Param_BufferOrigem">A Matriz com o buffer que será copiado.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(MatrizBytes Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(Span<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Método responsável por criar o Buffer a parti de um Buffer já existente.
		/// </summary>
		/// <param name="Param_BufferOrigem">O memory somente leitura para a matriz de bytes que será copiada para criar o buffer.</param>
		/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
		/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
		/// <returns></returns>
		CarenResult CriarBuffer(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O buffer de origem que será copiado.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">A quantidade de dados, em bytes, que será escrita.</param>
		/// <returns></returns>
		CarenResult EscreverDados(ICarenBuffer^ Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(MatrizBytes Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_TamanhoBufferOrigem">O tamanho total, em bytes, do buffer de origem.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(IntPtr Param_BufferOrigem, UInt32 Param_TamanhoBufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(Span<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(Memory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Escreve dados no buffer atual a parti de um Buffer de origem.
		/// </summary>
		/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
		/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
		/// <returns></returns>
		CarenResult EscreverDados(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

		/// <summary>
		/// Obtém uma cópia de todos os dados do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
		/// </summary>
		/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia total do buffer.</param>
		/// <returns></returns>
		CarenResult ObterBuffer([Out] MatrizBytes% Param_Out_Buffer);

		/// <summary>
		/// Obtém uma cópia de uma região especifica do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
		/// </summary>
		/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
		/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia da região solicitada do buffer.</param>
		/// <returns></returns>
		CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] MatrizBytes% Param_Out_Buffer);

		/// <summary>
		/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia. Qualquer alteração no buffer (Param_Out_Buffer) será refletido no buffer original.
		/// </summary>
		/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
		/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
		/// <returns></returns>
		CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] Span<Byte>% Param_Out_Buffer);

		/// <summary>
		/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia.
		/// </summary>
		/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
		/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
		/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
		/// <returns></returns>
		CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] ReadOnlySpan<Byte>% Param_Out_Buffer);

		/// <summary>
		/// Método responsável por recuperar o ponteiro para o buffer interno.
		/// </summary>
		/// <param name="Param_Ref_PonteiroBuffer">Retorna o ponteiro para o buffer nativo gerenciado pela interface.</param>
		/// <returns></returns>
		CarenResult ObterPonteiroInterno(IntPtr% Param_Ref_PonteiroBuffer);

		/// <summary>
		/// Método responsável por definir a posição de escrita ou leitura no buffer.
		/// </summary>
		/// <param name="Param_Offset">O deslocamento, em bytes, que representa a nova posição para leitura ou escrita.</param>
		void DefinirPosicao(UInt32 Param_Offset);

		/// <summary>
		/// Libera os dados alocados para o buffer criado pelo método(CriarBuffer).
		/// </summary>
		/// <returns></returns>
		void ReleaseBuffer();

		/// <summary>
		/// Libera os dados alocados para o buffer criado pela função nativa (CoTaskMemAlloc).
		/// </summary>
		/// <returns></returns>
		void ReleaseBufferWithCoTaskMemFree();
	};

	/// <summary>
	/// Interface responsável por criar e gerenciar um evento nativo do Windows.
	/// </summary>
	[CategoryAttribute("Caren Interface")]
	[Guid("CCC5A485-8664-474D-A88D-B9DE3512AE0D")]
	public interface class ICarenWindowsEvent
	{
		/// <summary>
		/// Propriedade que define se a classe foi descartada.
		/// </summary>
		property Boolean DisposedClasse
		{
			virtual Boolean get();
		}


		//Métodos

		/// <summary>
		/// (CreateEventW) - Cria ou abre um objeto de evento nomeado ou sem nome.
		/// </summary>
		/// <param name="Param_AtributosEvento">Uma estrutura CA_SECURITY_ATTRIBUTES. Se este parâmetro é NULO, o evento não pode 
		/// ser herdado por um processo filho.
		/// A estrutura especifica um descritor de segurança para o novo evento. Sendo NULO, o evento recebe um descritor de 
		/// segurança padrão. Os ACLs no descritor de segurança padrão para um evento vêm do símbolo primário ou de representação 
		/// do criador.</param>
		/// <param name="Param_ManualReset">Se este parâmetro for TRUE,a função cria um objeto de evento de redefinição manual,
		/// que requer o uso da função (ResetarEvento) para definir o estado do evento para não sinalizado. Se este parâmetro for 
		/// FALSE, a função cria um objeto de evento de redefinição automática e o sistema redefine automaticamente o estado do evento
		/// para não sinalizado após a lançamento de um único thread.</param>
		/// <param name="Param_EstadoInicial">Se este parâmetro é TRUE,o estado inicial do objeto do evento é sinalizado; caso contrário, não é sinalizado.</param>
		/// <param name="Param_NomeObjetoEvento">O nome do objeto do evento. O nome é limitado a 260(MAX_PATH) caracteres. A comparação do nome é sensível ao caso(Case-Sensitive).
		/// Se o (Param_NomeObjetoEvento) corresponde ao nome de um objeto de evento nomeado existente, esta função solicita o 
		/// EVENT_ALL_ACCESS direito de acesso. Neste caso, os parâmetros (Param_ManualReset) e (Param_EstadoInicial) são ignorados porque já foram definidos pelo processo de criação. 
		/// Se o parâmetro (Param_AtributosEvento) não é NULO, ele determina se o identificador pode ser herdado, mas seu membro descritor de segurança é ignorado.
		/// Se o parâmetro (Param_NomeObjetoEvento) corresponde ao nome de outro tipo de objeto no mesmo espaço de nome (como um semáforo existente, mutex, temporâmico, trabalho ou 
		/// objeto de mapeamento de arquivos), a função falha.</param>
		CarenResult CriarEvento(
			CA_SECURITY_ATTRIBUTES^ Param_AtributosEvento,
			Boolean Param_ManualReset,
			Boolean Param_EstadoInicial,
			String^ Param_NomeObjetoEvento);

		/// <summary>
		/// (CreateEventExW) - Cria ou abre um objeto de evento nomeado ou sem nome. Permite especificar a mascara de acesso para o objeto.
		/// </summary>
		/// <param name="Param_AtributosEvento">Uma estrutura CA_SECURITY_ATTRIBUTES. Se este parâmetro é NULO, o evento não pode 
		/// ser herdado por um processo filho.
		/// A estrutura especifica um descritor de segurança para o novo evento. Sendo NULO, o evento recebe um descritor de 
		/// segurança padrão. Os ACLs no descritor de segurança padrão para um evento vêm do símbolo primário ou de representação 
		/// do criador.</param>
		/// <param name="Param_NomeObjetoEvento">O nome do objeto do evento. O nome é limitado a 260(MAX_PATH) caracteres. A comparação do nome é sensível ao caso(Case-Sensitive).
		/// Se o (Param_NomeObjetoEvento) corresponde ao nome de um objeto de evento nomeado existente, esta função solicita o 
		/// EVENT_ALL_ACCESS direito de acesso. Neste caso, os parâmetros (Param_ManualReset) e (Param_EstadoInicial) são ignorados porque já foram definidos pelo processo de criação. 
		/// Se o parâmetro (Param_AtributosEvento) não é NULO, ele determina se o identificador pode ser herdado, mas seu membro descritor de segurança é ignorado.
		/// Se o parâmetro (Param_NomeObjetoEvento) corresponde ao nome de outro tipo de objeto no mesmo espaço de nome (como um semáforo existente, mutex, temporâmico, trabalho ou 
		/// objeto de mapeamento de arquivos), a função falha.</param>
		/// <param name="Param_Flags">Flags para criação do evento.</param>
		/// <param name="Param_MascaraAcesso">A máscara de acesso para o objeto do evento. Consulte o (Synchronization Object Security and Access Rights) para saber os possiveis valores
		/// para esse paramêtro.</param>
		CarenResult CriarEventoEx(
			CA_SECURITY_ATTRIBUTES^ Param_AtributosEvento,
			String^ Param_NomeObjetoEvento,
			CA_WIN_EVENT_FLAGS Param_Flags,
			UInt32 Param_MascaraAcesso);

		/// <summary>
		/// Associa um determinado evento a classe atual.
		/// O método vai retornar o código de erro(ER_FALHA), se um evento já existir.
		/// </summary>
		/// <param name="Param_PonteiroEvento">O ponteiro para um evento já criado.</param>
		CarenResult AssociarEvento(IntPtr Param_PonteiroEvento);

		/// <summary>
		/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
		/// </summary>
		/// <param name="Param_Out_Evento">O ponteiro para um evento já criado.</param>
		CarenResult RecuperarEvento([Out] IntPtr% Param_Out_Evento);

		/// <summary>
		/// Recupera o evento atual da classe. Se o evento não for um objeto valido, o método retorna ER_PONTEIRO.
		/// </summary>
		/// <param name="Param_Out_Evento">O ponteiro para a handle do evento.</param>
		CarenResult RecuperarEvento(LPVOID* Param_Out_Evento);

		/// <summary>
		/// (WaitForSingleObject) - Espera até que o objeto especificado esteja no estado sinalizado ou o intervalo do intervalo do tempo limite decorra.
		/// </summary>
		/// <param name="Param_TempoMilliseconds">O intervalo de tempo, em milissegundos. Se um valor não zero for especificado, a função aguarda até que o objeto seja sinalizado ou o intervalo 
		/// decorra. Se (Param_TempoMilliseconds) é zero, a função não entra em um estado de espera se o objeto não for sinalizado; ele sempre retorna imediatamente. Se Param_TempoMilliseconds é 
		/// infinito(1e+300 * 1e+300), a função retornará somente quando o objeto é sinalizado.</param>
		CarenResult AguardarObjetoUnico(UInt32 Param_TempoMilliseconds);

		/// <summary>
		/// (WaitForSingleObjectEx) - Espera até que o objeto especificado está no estado sinalizado, uma rotina de conclusão I / O ou chamada procedimento assíncrono (APC) é enfileirado para o 
		/// segmento(Thread), ou o intervalo de intervalo de tempo decorrido.
		/// </summary>
		/// <param name="Param_TempoMilliseconds">O intervalo de tempo, em milissegundos. Se um valor não zero for especificado, a função aguarda até que o objeto seja sinalizado ou o intervalo 
		/// decorra. Se (Param_TempoMilliseconds) é zero, a função não entra em um estado de espera se o objeto não for sinalizado; ele sempre retorna imediatamente. Se Param_TempoMilliseconds é 
		/// infinito(1e+300 * 1e+300), a função retornará somente quando o objeto é sinalizado.</param>
		/// <param name="Param_Alertavel">Se este parâmetro é TRUE e a linha está no estado de espera, a função retorna quando o sistema enfileira uma rotina da conclusão de I/O ou Um APC, e a 
		/// linha funciona a rotina ou a função. Caso contrário, a função não retorna, e a rotina de conclusão ou a função APC não é executada.
		/// Uma rotina de conclusão é enfileirada quando a função ReadFileEx ou WriteFileEx na qual foi especificada foi concluída. </param>
		CarenResult AguardarObjetoUnicoEx(UInt32 Param_TempoMilliseconds, Boolean Param_Alertavel);

		/// <summary>
		/// (ResetEvent) - Define o objeto de evento da classe atual para o estado não sinalizado.
		/// </summary>
		CarenResult ResetarEvento();

		/// <summary>
		/// (SetEvent) - Define o objeto do evento da classe atual para o estado sinalizado.
		/// </summary>
		CarenResult SinalizarEvento();

		/// <summary>
		/// (CloseHandle) - Fecha a alça do evento criado ou aberto anteriormente.
		/// </summary>
		CarenResult LiberarEvento();
	};
}