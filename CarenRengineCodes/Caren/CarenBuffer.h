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
#include "..\SDK_Base.h"
#include "..\SDK_Caren.h"

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
			if (p_Index >= Tamanho)
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
	virtual CarenResult CriarBuffer(UInt32 Param_TamanhoBuffer);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
	/// </summary>
	/// <param name="Param_BufferOrigem">Um ponteiro para o buffer de origem.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(ICarenBuffer^ Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
	/// </summary>
	/// <param name="Param_BufferOrigem">O ponteiro para o buffer de origem.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(IntPtr Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">A Matriz com o buffer que será copiado.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(MatrizBytes Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(Span<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Método responsável por criar o Buffer a parti de um Buffer já existente.
	/// </summary>
	/// <param name="Param_BufferOrigem">O memory somente leitura para a matriz de bytes que será copiada para criar o buffer.</param>
	/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
	/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
	/// <returns></returns>
	virtual CarenResult CriarBuffer(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O buffer de origem que será copiado.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">A quantidade de dados, em bytes, que será escrita.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(ICarenBuffer^ Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(MatrizBytes Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_TamanhoBufferOrigem">O tamanho total, em bytes, do buffer de origem.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(IntPtr Param_BufferOrigem, UInt32 Param_TamanhoBufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(Span<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(Memory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Escreve dados no buffer atual a parti de um Buffer de origem.
	/// </summary>
	/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
	/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
	/// <returns></returns>
	virtual CarenResult EscreverDados(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho);

	/// <summary>
	/// Obtém uma cópia de todos os dados do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
	/// </summary>
	/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia total do buffer.</param>
	/// <returns></returns>
	virtual CarenResult ObterBuffer([Out] MatrizBytes% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma cópia de uma região especifica do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia da região solicitada do buffer.</param>
	/// <returns></returns>
	virtual CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] MatrizBytes% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia. Qualquer alteração no buffer (Param_Out_Buffer) será refletido no buffer original.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
	/// <returns></returns>
	virtual CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] Span<Byte>% Param_Out_Buffer);

	/// <summary>
	/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia.
	/// </summary>
	/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
	/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
	/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
	/// <returns></returns>
	virtual CarenResult ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] ReadOnlySpan<Byte>% Param_Out_Buffer);

	/// <summary>
	/// Método responsável por recuperar o ponteiro para o buffer interno.
	/// </summary>
	/// <param name="Param_Ref_PonteiroBuffer">Retorna o ponteiro para o buffer nativo gerenciado pela interface.</param>
	/// <returns></returns>
	virtual CarenResult ObterPonteiroInterno(IntPtr% Param_Ref_PonteiroBuffer);

	/// <summary>
	/// Método responsável por definir a posição de escrita ou leitura no buffer.
	/// </summary>
	/// <param name="Param_Offset">O deslocamento, em bytes, que representa a nova posição para leitura ou escrita.</param>
	virtual void DefinirPosicao(UInt32 Param_Offset);

	/// <summary>
	/// Libera os dados alocados para o buffer criado pelo método(CriarBuffer).
	/// </summary>
	/// <returns></returns>
	virtual void ReleaseBuffer();

	/// <summary>
	/// Libera os dados alocados para o buffer criado pela função nativa (CoTaskMemAlloc).
	/// </summary>
	/// <returns></returns>
	virtual void ReleaseBufferWithCoTaskMemFree();
};