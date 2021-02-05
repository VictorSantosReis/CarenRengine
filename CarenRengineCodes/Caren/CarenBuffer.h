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
#include "../SDK_Base.h"
#include "../SDK_Caren.h"

//Importa os namespaces base.
using namespace CarenRengine;
using namespace CarenRengine::SDKBase;

/// <summary>
/// Classe responsável pelo enumerador para a classe CarenBuffer;
/// </summary>
ref class CarenBufferEnumerator : public System::Collections::IEnumerator
{
private:
	PBYTE pBufferTeste = NULL;
	int position = -1;
	int LarguraBuffer = 0;

public:
	CarenBufferEnumerator(PBYTE Param_Buffer, int Param_LarguraBuffer)
	{
		pBufferTeste = Param_Buffer;
		LarguraBuffer = Param_LarguraBuffer;
	}
	~CarenBufferEnumerator()
	{
		pBufferTeste = NULL;
	}

	virtual bool MoveNext()
	{
		position++;

		if (position < LarguraBuffer)
			return true;
		else
			return false;
	}

	virtual void Reset()
	{
		position = -1;
	}

	virtual property Object^ Current
	{
		virtual Object^ get()
		{
			return (Byte)pBufferTeste[position];
		};
	}
};

/// <summary>
/// (Concluida - Fase de testes) - 
/// </summary>
public ref class CarenBuffer : public ICarenBuffer
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para o (PBYTE).
	PBYTE pBufferNativo = NULL;


	//Construtor e Destruidor da classe.
public:
	CarenBuffer() 
	{}
	~CarenBuffer() 
	{
		//Chama o finalizador.
		this->!CarenBuffer();
	}

protected:
	!CarenBuffer()
	{
		//Reseta os dados.
		Prop_Posição = 0;
		Prop_Tamanho = 0;
		Prop_TamanhoValido = 0;

		//Faz apenas uma limpeza.
		if (ObjetoValido(pBufferNativo))
			pBufferNativo = NULL;

		//Informa ao GC que a classe pode ser descartada.
		GC::SuppressFinalize(this);

		//Define que a classe foi descartada
		Prop_DisposedClasse = true;
	}


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da posição atual.
	UInt32 Prop_Posição = 0;

	//Variavel que contém o valor da largura maxima do buffer definido na criação.
	UInt32 Prop_Tamanho = 0;

	//Variavel que contém a largura 
	UInt32 Prop_TamanhoValido = 0;

	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;


	//Propriedades publicas
public:
	/// <summary>
	/// Propriedade que contém a posição atual do buffer.
	/// </summary>
	property UInt32 Posição
	{
		virtual UInt32 get()
		{
			//Retorna o valor.
			return Prop_Posição;
		}
	}

	/// <summary>
	/// Propriedade que contém o tamanho maximo do buffer.
	/// </summary>
	property UInt32 Tamanho
	{
		virtual UInt32 get()
		{
			//Retorna o valor.
			return Prop_Tamanho;
		}
		virtual void set(UInt32 Param_ValueSet)
		{
			Prop_Tamanho = Param_ValueSet;
		}
	}

	/// <summary>
	/// Propriedade que contém a largura em bytes de dados válidos no buffer.
	/// </summary>
	property UInt32 TamanhoValido
	{
		virtual UInt32 get()
		{
			//Retorna o valor.
			return Prop_TamanhoValido;
		}
		virtual void set(UInt32 Param_ValueSet)
		{
			Prop_TamanhoValido = Param_ValueSet;
		}
	}

	/// <summary>
	/// Propriedade que informa se a interface foi descartada.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}

	//Indexador para acessar e escrever.
    #pragma region Indexador
	property Byte default[int]
	{
		virtual Byte get(int p_Index)
		{
		//Retorna o valor no index.
		return pBufferNativo[p_Index];
		}

		virtual void set(int p_Index, Byte p_Valor)
	    {
			//Verifica o index informado.
			if (p_Index >= static_cast<int>(Tamanho))
				throw gcnew IndexOutOfRangeException("O index informado ultrapassava os limites da matriz.");

			//Define o valor na matriz.
			pBufferNativo[p_Index] = p_Valor;
		}
	}
    #pragma endregion


	//Método que retorna o enumerador de itens da classe.
public:
	virtual System::Collections::IEnumerator^ GetEnumerator()
	{
		//Retorna o enumerador da classe.
		return gcnew CarenBufferEnumerator(pBufferNativo, Tamanho);
	}

	//Conversões implicitas
public:
	static operator CarenBuffer^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenBuffer^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenBuffer();

		//Define o ponteiro na classe.
		ClassResultado->pBufferNativo = static_cast<PBYTE>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}

	static operator CarenBuffer^ (cli::array<Byte>^ Param_Buffer)
	{
		//Variavel a ser retornada.
		CarenBuffer^ ClassResultado = nullptr;

		//Verifica se o buffer não é invalido.
		if (!ObjetoGerenciadoValido(Param_Buffer))
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenBuffer();

		//Cria o buffer com os dados do array.
		ClassResultado->CreateBuffer(Param_Buffer, static_cast<UINT>(Param_Buffer->Length), static_cast<UINT>(Param_Buffer->Length));

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}

	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////

	//Métodos da interface(ICarenBuffer22)
public:
	/// <summary>
	/// Método responsável por alocar um novo buffer de tamanho especificado.
	/// </summary>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer a ser criado.</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(UInt32 Param_TamanhoBuffer);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
	/// </summary>
	/// <param name="Param_BufferOrigem">Um ponteiro para o buffer de origem.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(ICarenBuffer^ Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
	/// </summary>
	/// <param name="Param_BufferOrigem">O ponteiro para o buffer de origem.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(IntPtr Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">A Matriz com o buffer que será copiado.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(MatrizBytes Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(Span<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O memory somente leitura para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CreateBuffer(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O buffer de origem que será copiado.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">A quantidade de dados, em bytes, que será escrita.</param>
	/// <returns></returns>
	virtual CarenResult Write(ICarenBuffer^ Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(MatrizBytes Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_TamanhoBufferOrigem">O tamanho total, em bytes, do buffer de origem.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(IntPtr Param_BufferOrigem, UInt32 Param_TamanhoBufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(Span<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(Memory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult Write(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(SByte Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(Byte Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(Int16 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(Int32 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(Int64 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(UInt16 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(UInt32 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(UInt64 Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(float Param_Value);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
	/// </summary>
	/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
	/// <returns></returns>
	virtual CarenResult Write(Double Param_Value);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, Span<Byte>% Param_Ref_BufferDest);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, Memory<Byte>% Param_Ref_BufferDest);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, MatrizBytes% Param_Ref_BufferDest);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, ICarenBuffer^% Param_Ref_BufferDest);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, IntPtr Param_BufferDest);

	/// <summary>
	/// Escreve uma certa quantidade de dados do buffer atual em um buffer de destino.
	/// </summary>
	/// <param name="Param_StartIndex">O Index do inicio da cópia dos dados do buffer atual.</param>
	/// <param name="Param_Count">A quantidade de dados atuais a serem escritos no buffer de destino.</param>
	/// <param name="Param_Ref_BufferDest">O buffer de destino que vai receber os dados.</param>
	/// <returns></returns>
	virtual CarenResult WriteTo(UInt32 Param_StartIndex, UInt32 Param_Count, PBYTE Param_BufferDest);

	/// <summary>
	/// Obtém uma cópia de todos os dados do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
	/// </summary>
	/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia total do buffer.</param>
	/// <returns></returns>
	virtual CarenResult Get([Out] MatrizBytes% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma cópia de uma região especifica do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia da região solicitada do buffer.</param>
	/// <returns></returns>
	virtual CarenResult Get(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] MatrizBytes% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia. Qualquer alteração no buffer (Param_Out_Buffer) será refletido no buffer original.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
	/// <returns></returns>
	virtual CarenResult Get(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] Span<Byte>% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
	/// <returns></returns>
	virtual CarenResult Get(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] ReadOnlySpan<Byte>% Param_Out_Buffer);

	/// <summary>
	/// Método responsável por recuperar o ponteiro para o buffer interno.
	/// </summary>
	/// <param name="Param_Ref_PonteiroBuffer">Retorna o ponteiro para o buffer nativo gerenciado pela interface.</param>
	/// <returns></returns>
	virtual CarenResult GetInternalPointer(IntPtr% Param_Ref_PonteiroBuffer);

	/// <summary>
	/// Método responsável por retornar um valor que define se o ponteiro para o buffer atual é valido.
	/// </summary>
	/// <returns></returns>
	virtual CarenResult GetStatusPointer();

	/// <summary>
	/// Método responsável por preencher o buffer com ZEROS(0).
	/// </summary>
	virtual void FillBuffer();

	/// <summary>
	/// Método responsável por definir a posição de escrita ou leitura no buffer.
	/// </summary>
	/// <param name="Param_Offset">O deslocamento, em bytes, que representa a nova posição para leitura ou escrita.</param>
	virtual void SetPosition(UInt32 Param_Offset);

	/// <summary>
	/// Libera os dados alocados para o buffer criado pelo método(CreateBuffer).
	/// </summary>
	/// <returns></returns>
	virtual void ReleaseBuffer();

	/// <summary>
	/// Libera os dados alocados para o buffer criado pela função nativa (CoTaskMemAlloc).
	/// </summary>
	/// <returns></returns>
	virtual void ReleaseBufferWithCoTaskMemFree();
};