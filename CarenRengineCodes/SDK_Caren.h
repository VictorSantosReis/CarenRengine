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
#include "pch.h"

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
}