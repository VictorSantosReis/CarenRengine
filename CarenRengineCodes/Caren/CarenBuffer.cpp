#include "../pch.h"
#include "CarenBuffer.h"

//
// Métodos da interface ICarenBuffer
//

/// <summary>
/// Método responsável por alocar um novo buffer de tamanho especificado.
/// </summary>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer a ser criado.</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(UInt32 Param_TamanhoBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Define e inicializa a estrutura que vai conter informações da memoria do sistema para saber se tem espaço disponivel.
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);

	//Obtém o status da memoria
	BOOL GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

	//Verifica se obteve as informações com sucesso.
	if (GetMemStatus)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao realizar a operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se tem memoria disponivel para criar o buffer.
	if (Param_TamanhoBuffer >= MemStatus.ullAvailPhys)
	{
		//Define falha por falta de memoria.
		Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

		//Sai do método
		goto Done;
	}

	//Aloca a quantidade de dados requisitada pelo usuário para o buffer.
	pBufferNativo = new BYTE[Param_TamanhoBuffer];

	//Define as propriedades
	Prop_Posição = 0;
	Tamanho = Param_TamanhoBuffer;
	TamanhoValido = 0;
	Prop_DisposedClasse = false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
/// </summary>
/// <param name="Param_BufferOrigem">Um ponteiro para o buffer de origem.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(ICarenBuffer^ Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	IntPtr PonteiroBufferOrigem = IntPtr::Zero;
	PBYTE pBufferOrigemNativo = NULL;
	BOOL GetMemStatus = FALSE;

	//Recupera o ponteiro para o buffer do origem
	Resultado = Param_BufferOrigem->ObterPonteiroInterno(PonteiroBufferOrigem);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao obter o ponteiro interno.

		//Sai do método
		Sair;
	}

	//Converte o ponteiro gerenciado para o nativo.
	pBufferOrigemNativo = static_cast<PBYTE>(PonteiroBufferOrigem.ToPointer());

	//Abre um switch para verificar se será copiado ou apenas associado.
	switch (Param_Copiar)
	{
	case true:
		//Vai realizar uma copia dos dados. Mais vai verificar antes se há memoria suficiente para o processo.
		MEMORYSTATUSEX MemStatus;
		MemStatus.dwLength = sizeof(MemStatus);	

		//Obtém o status da memoria
		GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

		//Verifica se obteve as informações com sucesso.
		if (GetMemStatus)
		{
			//Deixa o método continuar.
		}
		else
		{
			//Falhou ao realizar a operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método.
			goto Done;
		}

		//Verifica se tem memoria disponivel para criar o buffer.
		if (Param_Tamanho >= MemStatus.ullAvailPhys)
		{
			//Define falha por falta de memoria.
			Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

			//Sai do método
			goto Done;
		}
		else
		{
			//Deixa o método continuar.
		}

		//Cria o buffer nativo da interface.
		pBufferNativo = new BYTE[Param_Tamanho];

		//Realiza a copia dos dados.
		std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

		//Define as propriedade da classe.
		Tamanho = Param_Tamanho;
		TamanhoValido = Param_TamanhoDadosValidos;
		Prop_Posição = 0;
		Prop_DisposedClasse = false;

		//Deixa o método continuar para retorna o resultado.
		break;


	case false:
		//Vai apenas associar o ponteiro a interface.
		
		//Associa o ponteiro de origem.
		pBufferNativo = pBufferOrigemNativo;

		//Define as propriedade da classe.
		Tamanho = Param_Tamanho;
		TamanhoValido = Param_TamanhoDadosValidos;
		Prop_Posição = 0;
		Prop_DisposedClasse = false;

		//Deixa o método continuar para retorna o resultado.
		break;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente. Permite especifica se deve realizar uma cópia do Buffer ou apenas associar o ponteiro a interface.
/// </summary>
/// <param name="Param_BufferOrigem">O ponteiro para o buffer de origem.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_Copiar">Um valor Booleano que indica se o método deve fazer uma cópia do buffer de origem, ou se deve apenas associar seu ponteiro a este buffer.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(IntPtr Param_BufferOrigem, Boolean Param_Copiar, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	PBYTE pBufferOrigemNativo = NULL;
	BOOL GetMemStatus = FALSE;

	//Converte o ponteiro gerenciado para o nativo.
	pBufferOrigemNativo = static_cast<PBYTE>(Param_BufferOrigem.ToPointer());

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//Ponteiro valido.. Deixa o método continuar.
	}
	else
	{
		//Ponteiro é invalido..

		//Define erro
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Abre um switch para verificar se será copiado ou apenas associado.
	switch (Param_Copiar)
	{
	case true:
		//Vai realizar uma copia dos dados. Mais vai verificar antes se há memoria suficiente para o processo.
		MEMORYSTATUSEX MemStatus;
		MemStatus.dwLength = sizeof(MemStatus);

		//Obtém o status da memoria
		GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

		//Verifica se obteve as informações com sucesso.
		if (GetMemStatus)
		{
			//Deixa o método continuar.
		}
		else
		{
			//Falhou ao realizar a operação.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método.
			goto Done;
		}

		//Verifica se tem memoria disponivel para criar o buffer.
		if (Param_Tamanho >= MemStatus.ullAvailPhys)
		{
			//Define falha por falta de memoria.
			Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

			//Sai do método
			goto Done;
		}
		else
		{
			//Deixa o método continuar.
		}

		//Cria o buffer nativo da interface.
		pBufferNativo = new BYTE[Param_Tamanho];

		//Realiza a copia dos dados.
		std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

		//Define as propriedade da classe.
		Tamanho = Param_Tamanho;
		TamanhoValido = Param_TamanhoDadosValidos;
		Prop_Posição = 0;
		Prop_DisposedClasse = false;

		//Deixa o método continuar para retorna o resultado.
		break;


	case false:
		//Vai apenas associar o ponteiro a interface.

		//Associa o ponteiro de origem.
		pBufferNativo = pBufferOrigemNativo;

		//Define as propriedade da classe.
		Tamanho = Param_Tamanho;
		TamanhoValido = Param_TamanhoDadosValidos;
		Prop_Posição = 0;
		Prop_DisposedClasse = false;

		//Deixa o método continuar para retorna o resultado.
		break;
	}

	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente.
/// </summary>
/// <param name="Param_BufferOrigem">A Matriz com o buffer que será copiado.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(MatrizBytes Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	pin_ptr<Byte> PinToBufferOrigem = nullptr;
	PBYTE pBufferOrigemNativo = NULL;
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);

	//Obtém o status da memoria
	BOOL GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

	//Verifica se obteve as informações com sucesso.
	if (GetMemStatus)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao realizar a operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se tem memoria disponivel para criar o buffer.
	if (Param_Tamanho >= MemStatus.ullAvailPhys)
	{
		//Define falha por falta de memoria.
		Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Deixa o método continuar.
	}

	//Obtém um pin para o buffer que será copiado.
	PinToBufferOrigem = &Param_BufferOrigem[0];

	//Converte para o buffer nativo.
	pBufferOrigemNativo = static_cast<BYTE*>(PinToBufferOrigem);

	//Verifica se o buffer é valido
	if (ObjetoValido(pBufferOrigemNativo))
	{
	}
	else
	{
		//O buffer não foi convertido com sucesso

		//Define erro
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método
		goto Done;
	}

	//Cria o buffer nativo da interface.
	pBufferNativo = new BYTE[Param_Tamanho];

	//Realiza a copia dos dados.
	std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

	//Define as propriedade da classe.
	Tamanho = Param_Tamanho;
	TamanhoValido = Param_TamanhoDadosValidos;
	Prop_Posição = 0;
	Prop_DisposedClasse = false;


	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente.
/// </summary>
/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(Span<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	pin_ptr<Byte> pinIndex0Buffer = nullptr;
	PBYTE pBufferOrigemNativo = NULL;
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);
	BOOL GetMemStatus = FALSE;

	//Cria um pin para o index 0 do buffer no span.
	pinIndex0Buffer = &Param_BufferOrigem.GetPinnableReference();

	//Converte o pin para um ponteiro nativo de fato.
	pBufferOrigemNativo = static_cast<BYTE*>(pinIndex0Buffer);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//Ponteiro valido.. Deixa o método continuar.
	}
	else
	{
		//Ponteiro é invalido..

		//Define erro
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método
		goto Done;
	}

	//Obtém o status da memoria
	GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

	//Verifica se obteve as informações com sucesso.
	if (GetMemStatus)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao realizar a operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se tem memoria disponivel para criar o buffer.
	if (Param_Tamanho >= MemStatus.ullAvailPhys)
	{
		//Define falha por falta de memoria.
		Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Deixa o método continuar.
	}

	//Cria o buffer nativo da interface.
	pBufferNativo = new BYTE[Param_Tamanho];

	//Realiza a copia dos dados.
	std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

	//Define as propriedade da classe.
	Tamanho = Param_Tamanho;
	TamanhoValido = Param_TamanhoDadosValidos;
	Prop_Posição = 0;
	Prop_DisposedClasse = false;

	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente.
/// </summary>
/// <param name="Param_BufferOrigem">O Span para a matriz de bytes que será copiada para criar o buffer.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	pin_ptr<Byte> pinIndex0Buffer = nullptr;
	PBYTE pBufferOrigemNativo = NULL;
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);
	BOOL GetMemStatus = FALSE;

	//Cria um pin para o index 0 do buffer no span.
	pinIndex0Buffer = &MemoryMarshal::GetReference(Param_BufferOrigem);

	//Converte o pin para um ponteiro nativo de fato.
	pBufferOrigemNativo = static_cast<BYTE*>(pinIndex0Buffer);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//Ponteiro valido.. Deixa o método continuar.
	}
	else
	{
		//Ponteiro é invalido..

		//Define erro
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Obtém o status da memoria
	GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

	//Verifica se obteve as informações com sucesso.
	if (GetMemStatus)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao realizar a operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se tem memoria disponivel para criar o buffer.
	if (Param_Tamanho >= MemStatus.ullAvailPhys)
	{
		//Define falha por falta de memoria.
		Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Deixa o método continuar.
	}

	//Cria o buffer nativo da interface.
	pBufferNativo = new BYTE[Param_Tamanho];

	//Realiza a copia dos dados.
	std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

	//Define as propriedade da classe.
	Tamanho = Param_Tamanho;
	TamanhoValido = Param_TamanhoDadosValidos;
	Prop_Posição = 0;
	Prop_DisposedClasse = false;

	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por criar o Buffer a parti de um Buffer já existente.
/// </summary>
/// <param name="Param_BufferOrigem">O memory somente leitura para a matriz de bytes que será copiada para criar o buffer.</param>
/// <param name="Param_Tamanho">O tamanho do buffer de origem.</param>
/// <param name="Param_TamanhoDadosValidos">O total, em bytes, de dados validos no buffer. Se todos forem validos, esse valor deve ser igual ao do parametro (Param_Tamanho).</param>
/// <returns></returns>
CarenResult CarenBuffer::CriarBuffer(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Tamanho, UInt32 Param_TamanhoDadosValidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	PBYTE pBufferOrigemNativo = NULL;
	Memory<Byte> MemoryToBuffer = nullptr;
	pin_ptr<Byte> pinIndex0Buffer = nullptr;
	MEMORYSTATUSEX MemStatus;
	MemStatus.dwLength = sizeof(MemStatus);
	BOOL GetMemStatus = FALSE;

	//Converte o readonly para um Memory para poder acessar o ponteiro para a refererencia.
	MemoryToBuffer = MemoryMarshal::AsMemory(Param_BufferOrigem);

	//Obtém um pin para o index 0 do buffer de origem.
	pinIndex0Buffer = &MemoryToBuffer.Span.GetPinnableReference();

	//Converte o pin para um ponteiro nativo de fato.
	pBufferOrigemNativo = static_cast<BYTE*>(pinIndex0Buffer);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//Ponteiro valido.. Deixa o método continuar.
	}
	else
	{
		//Ponteiro é invalido..

		//Define erro
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Obtém o status da memoria
	GetMemStatus = GlobalMemoryStatusEx(&MemStatus);

	//Verifica se obteve as informações com sucesso.
	if (GetMemStatus)
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou ao realizar a operação.
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Sai do método.
		goto Done;
	}

	//Verifica se tem memoria disponivel para criar o buffer.
	if (Param_Tamanho >= MemStatus.ullAvailPhys)
	{
		//Define falha por falta de memoria.
		Resultado.AdicionarCodigo(ResultCode::ER_E_OUTOFMEMORY, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Deixa o método continuar.
	}

	//Cria o buffer nativo da interface.
	pBufferNativo = new BYTE[Param_Tamanho];

	//Realiza a copia dos dados.
	std::copy(pBufferOrigemNativo, pBufferOrigemNativo + Param_Tamanho, pBufferNativo);

	//Define as propriedade da classe.
	Tamanho = Param_Tamanho;
	TamanhoValido = Param_TamanhoDadosValidos;
	Prop_Posição = 0;
	Prop_DisposedClasse = false;

	//Define sucesso na operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}



/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O buffer de origem que será copiado.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">A quantidade de dados, em bytes, que será escrita.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(ICarenBuffer^ Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	IntPtr pBufferOrigem = IntPtr::Zero;
	PBYTE pBufferOrigemNativo = NULL;

	//Recupera o ponteiro para o buffer de origem que será escrito.
	Resultado = Param_BufferOrigem->ObterPonteiroInterno(pBufferOrigem);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao obter o ponteiro interno.

		//Sai do método
		Sair;
	}

	//Define obuffer de origem nativo.
	pBufferOrigemNativo = static_cast<PBYTE>(pBufferOrigem.ToPointer());

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > Param_BufferOrigem->Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else 
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0? pBufferNativo + Posição: pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(MatrizBytes Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variveis.
	pin_ptr<Byte> pPinToBufferOrigemIndex0 = &Param_BufferOrigem[0];
	PBYTE pBufferOrigemNativo = NULL;

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > static_cast<unsigned int>(Param_BufferOrigem->Length))
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converte o Pin para o buffer nativo
	pBufferOrigemNativo = static_cast<BYTE*>(pPinToBufferOrigemIndex0);

	//Verifica se o buffer foi convertido com sucesso.
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//O buffer foi convertido com sucesso. 
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.. A operação falhou.

		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método.
		goto Done;
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_TamanhoBufferOrigem">O tamanho total, em bytes, do buffer de origem.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(IntPtr Param_BufferOrigem, UInt32 Param_TamanhoBufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	PBYTE pBufferOrigemNativo = static_cast<PBYTE>(Param_BufferOrigem.ToPointer());

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > Param_TamanhoBufferOrigem)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Span<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);
	
	//Variaveis.
	pin_ptr<BYTE> pBufferIndex0 = nullptr;
	PBYTE pBufferOrigemNativo = NULL;

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > static_cast<unsigned int>(Param_BufferOrigem.Length))
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Obtém um ponteiro para o index 0 do span.
	pBufferIndex0 = &Param_BufferOrigem.GetPinnableReference();

	//Converte para um buffer nativo
	pBufferOrigemNativo = static_cast<BYTE*>(pBufferIndex0);

	//Verifica se o buffer foi convertido com sucesso.
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//O buffer foi convertido com sucesso. 
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.. A operação falhou.

		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método.
		goto Done;
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Memory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis.
	pin_ptr<BYTE> pBufferIndex0 = nullptr;
	PBYTE pBufferOrigemNativo = NULL;

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > static_cast<unsigned int>(Param_BufferOrigem.Length))
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Obtém um ponteiro para o index 0 do span.
	pBufferIndex0 = &Param_BufferOrigem.Span.GetPinnableReference();

	//Converte para um buffer nativo
	pBufferOrigemNativo = static_cast<BYTE*>(pBufferIndex0);

	//Verifica se o buffer foi convertido com sucesso.
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//O buffer foi convertido com sucesso. 
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.. A operação falhou.

		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método.
		goto Done;
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(ReadOnlySpan<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis.
	pin_ptr<Byte> PinReadOnlyIndex0 = nullptr;
	PBYTE pBufferOrigemNativo = NULL;

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > static_cast<unsigned int>(Param_BufferOrigem.Length))
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Obtém uma referencia para o index 0 do span.
	PinReadOnlyIndex0 = &MemoryMarshal::GetReference(Param_BufferOrigem);

	//Converte para um buffer nativo
	pBufferOrigemNativo = static_cast<BYTE*>(PinReadOnlyIndex0);

	//Verifica se o buffer foi convertido com sucesso.
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//O buffer foi convertido com sucesso. 
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.. A operação falhou.

		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método.
		goto Done;
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um Buffer de origem.
/// </summary>
/// <param name="Param_BufferOrigem">O Buffer de dados que será escrito.</param>
/// <param name="Param_Start">O deslocamento de bytes baseado em zero em (Param_BufferOrigem) do qual será iniciada a cópia de bytes no Buffer.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram escritos.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(ReadOnlyMemory<Byte> Param_BufferOrigem, UInt32 Param_Start, UInt32 Param_Tamanho)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis.
	pin_ptr<BYTE> pBufferIndex0 = nullptr;
	Memory<Byte> MemoryBufferOrigem = nullptr;
	PBYTE pBufferOrigemNativo = NULL;

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados definida no parâmetro (Param_Tamanho).");
	}
	else if ((Param_Start + Param_Tamanho) > static_cast<unsigned int>(Param_BufferOrigem.Length))
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer de origem mais o tamanho dos dados a serem escritos ultrapassava os limites do mesmo.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converte o ReadOnly para Memory
	MemoryBufferOrigem = MemoryMarshal::AsMemory(Param_BufferOrigem);

	//Obtém um pin para o index 0 do memory
	pBufferIndex0 = &MemoryBufferOrigem.Span.GetPinnableReference();

	//Converte para um buffer nativo
	pBufferOrigemNativo = static_cast<BYTE*>(pBufferIndex0);

	//Verifica se o buffer foi convertido com sucesso.
	if (ObjetoValido(pBufferOrigemNativo))
	{
		//O buffer foi convertido com sucesso. 
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.. A operação falhou.

		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO, false);

		//Sai do método.
		goto Done;
	}

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(pBufferOrigemNativo + Param_Start, pBufferOrigemNativo + Param_Start + Param_Tamanho, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += Param_Tamanho;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(SByte Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Byte Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Int16 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Int32 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Int64 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(UInt16 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(UInt32 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(UInt64 Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(float Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Escreve dados no buffer atual a parti de um valor simples que será convertido para um array de bytes.
/// </summary>
/// <param name="Param_Value">O valor a ser convertido e defnido no buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::Write(Double Param_Value)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis a serem utilizadas.
	vector<BYTE> vi_VetorBytes;
	PBYTE vi_pBufferNativoFromVector = Nulo;
	int vi_SizeTypeValue = sizeof(Param_Value);

	//Verifica se os ranges e offsets não ultrapassam os limites dos buffers.
	if (Posição + vi_SizeTypeValue > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posicão do buffer atual não suportava escrever a quantidade de dados necessária.");
	}
	else
	{
		//Deixa continuar para realizar a escrita dos dados.
	}

	//Converter o valor para um array de bytes.
	vi_VetorBytes = ConvertValueToByteArray(Param_Value);

	//Obtém o ponteiro interno do vetor.
	vi_pBufferNativoFromVector = vi_VetorBytes.data();

	//Realiza a escrita dos dados a parti do buffer informado.
	std::copy(vi_pBufferNativoFromVector, vi_pBufferNativoFromVector + vi_SizeTypeValue, Posição > 0 ? pBufferNativo + Posição : pBufferNativo);

	//Avança a posição do buffer.
	Prop_Posição += vi_SizeTypeValue;

	//Libera o vetor e os dados.
	vi_VetorBytes.clear();
	vi_VetorBytes.shrink_to_fit();

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}



/// <summary>
/// Obtém uma cópia de todos os dados do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
/// </summary>
/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia total do buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::ObterBuffer([Out] MatrizBytes% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	pin_ptr<Byte> PinToBuffer = nullptr;
	MatrizBytes CopiaBuffer = gcnew cli::array<Byte>(Tamanho);

	//Faz um pin para o buffer que será retornado.
	PinToBuffer = &CopiaBuffer[0];

	//Realiza a copia dos dados.
	std::copy(pBufferNativo, pBufferNativo + Tamanho, (BYTE*)PinToBuffer);

	//Define a matriz copiada no buffer de saida.
	Param_Out_Buffer = CopiaBuffer;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma cópia de uma região especifica do Buffer. Este método não é recomendado porque cria uma cópia do Buffer na memória. Se possível, utilize os métodos que retornam um Span.
/// </summary>
/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
/// <param name="Param_Out_Buffer">Retorna uma matriz de bytes que representa uma cópia da região solicitada do buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] MatrizBytes% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	pin_ptr<Byte> PinToBuffer = nullptr;
	MatrizBytes CopiaBuffer = nullptr;

	//Verifica se os offset não ultrapassam os limites do buffer.
	if (Param_Start + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posição de inicio mais o tamanho requisitado ultrapassam os limites do buffer atual.");
	}
	else
	{
		//Deixa o método continuar.
	}

	//Cria o buffer com o tamanho especificado.
	CopiaBuffer = gcnew cli::array<Byte>(Param_Tamanho);

	//Faz um pin para o buffer que será retornado.
	PinToBuffer = &CopiaBuffer[0];

	//Realiza a copia dos dados.
	std::copy(pBufferNativo + Param_Start, pBufferNativo + Param_Start + Tamanho, (BYTE*)PinToBuffer);

	//Define a matriz copiada no buffer de saida.
	Param_Out_Buffer = CopiaBuffer;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia. Qualquer alteração no buffer (Param_Out_Buffer) será refletido no buffer original.
/// </summary>
/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] Span<Byte>% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	Span<Byte> BufferSpan = nullptr;

	//Verifica se os offset não ultrapassam os limites do buffer.
	if (Param_Start + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posição de inicio mais o tamanho requisitado ultrapassam os limites do buffer atual.");
	}
	else
	{
		//Deixa o método continuar.
	}

	//Obtém um span para o buffer nativo.
	BufferSpan = Span<Byte>(pBufferNativo, Tamanho);

	//Define o span no intervalo especificado no buffer de saida.
	Param_Out_Buffer = BufferSpan.Slice(Param_Start, Param_Tamanho);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma região especifica do Buffer. Este método não realiza nenhum tipo de cópia. Qualquer alteração no buffer (Param_Out_Buffer) será refletido no buffer original.
/// </summary>
/// <param name="Param_Start">O index no buffer de origem para iniciar a operação.</param>
/// <param name="Param_Tamanho">O tamanho dos dados, em bytes, que seram obtidos.</param>
/// <param name="Param_Out_Buffer">Retorna um Span de bytes que representa diretamente a região solicitada do Buffer.</param>
/// <returns></returns>
CarenResult CarenBuffer::ObterBuffer(UInt32 Param_Start, UInt32 Param_Tamanho, [Out] ReadOnlySpan<Byte>% Param_Out_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variaveis
	ReadOnlySpan<Byte> BufferReadOnlySpan = nullptr;

	//Verifica se os offset não ultrapassam os limites do buffer.
	if (Param_Start + Param_Tamanho > Tamanho)
	{
		//Chama uma exceção e informado o motivo.
		throw gcnew IndexOutOfRangeException("A posição de inicio mais o tamanho requisitado ultrapassam os limites do buffer atual.");
	}
	else
	{
		//Deixa o método continuar.
	}

	//Obtém um span somente leitura para o buffer nativo.
	BufferReadOnlySpan = ReadOnlySpan<Byte>(pBufferNativo, Tamanho);

	//Define o span no intervalo especificado no buffer de saida.
	Param_Out_Buffer = BufferReadOnlySpan.Slice(Param_Start, Param_Tamanho);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}



/// <summary>
/// Método responsável por recuperar o ponteiro para o buffer interno.
/// </summary>
/// <param name="Param_Ref_PonteiroBuffer">Retorna o ponteiro para o buffer nativo gerenciado pela interface.</param>
/// <returns></returns>
CarenResult CarenBuffer::ObterPonteiroInterno(IntPtr% Param_Ref_PonteiroBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o buffer é valido
	if (ObjetoValido(pBufferNativo))
	{
		//Deixa o método continuar.
	}
	else
	{
		//O buffer não é valido.
		Resultado.AdicionarCodigo(ResultCode::ER_CARENBUFFER_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro para o buffer no parametro.
	Param_Ref_PonteiroBuffer = IntPtr(pBufferNativo);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Método responsável por preencher o buffer com ZEROS(0).
/// </summary>
void CarenBuffer::FillBuffer()
{
	//Verifica se o buffer atual é valido e preenche com zeros.
	if (ObjetoValido(pBufferNativo))
		ZeroMemory(pBufferNativo, Tamanho);
}

/// <summary>
/// Método responsável por definir a posição de escrita ou leitura no buffer.
/// </summary>
/// <param name="Param_Offset">O deslocamento, em bytes, que representa a nova posição para leitura ou escrita.</param>
void CarenBuffer::DefinirPosicao(UInt32 Param_Offset)
{
	//Verifica se o offset não ultrapassa ou é igual ao tamanho do buffer.
	if (Param_Offset >= Tamanho)
	{
		//Chama uma exceção.
		throw gcnew IndexOutOfRangeException("O Offset informado ultrapassava os limites do buffer.");
	}

	//Define a nova posição 
	Prop_Posição = Param_Offset;
}

/// <summary>
/// Libera os dados alocados para o buffer criado pelo método(CriarBuffer).
/// </summary>
/// <returns></returns>
void CarenBuffer::ReleaseBuffer()
{
	//Verifica se é valido e deleta o buffer.
	if (ObjetoValido(pBufferNativo))
	{
		//Libera a memória alocada para o buffer.
		delete pBufferNativo;
		pBufferNativo = NULL;

		//Zera as propriedades
		Tamanho = 0;
		TamanhoValido = 0;
		Prop_Posição = 0;
	}
}

/// <summary>
/// Libera os dados alocados para o buffer criado pela função nativa (CoTaskMemAlloc).
/// </summary>
/// <returns></returns>
void CarenBuffer::ReleaseBufferWithCoTaskMemFree()
{
	//Verifica se é valido e deleta o buffer.
	if (ObjetoValido(pBufferNativo))
	{
		//Libera a memória alocada para o buffer.
		CoTaskMemFree(pBufferNativo);
		pBufferNativo = NULL;

		//Zera as propriedades
		Tamanho = 0;
		TamanhoValido = 0;
		Prop_Posição = 0;
	}
}