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

#include "../pch.h"
#include "CarenWICJpegFrameDecode.h"

//Destruidor.
CarenWICJpegFrameDecode::~CarenWICJpegFrameDecode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICJpegFrameDecode::CarenWICJpegFrameDecode()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenWICJpegFrameDecode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICJpegFrameDecode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IWICJpegFrameDecode*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICJpegFrameDecode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IWICJpegFrameDecode*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICJpegFrameDecode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICJpegFrameDecode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICJpegFrameDecode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICJpegFrameDecode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICJpegFrameDecode::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICJpegFrameDecode::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICJpegFrameDecode::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICJpegFrameDecode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICJpegFrameDecode();
}



// Métodos da interface proprietária(ICarenWICJpegFrameDecode)


/// <summary>
/// Remove a indexação de um JPEG que foi indexado usando ICarenWICJpegFrameDecode::SetIndexing. 
/// </summary>
CarenResult CarenWICJpegFrameDecode::ClearIndexing()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ClearIndexing();

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia do scan JPEG compactada diretamente do fluxo de saída do frame de decodificador WIC. 
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_ScanOffset">A posição byte nos dados de varredura para começar a copiar. Use 0 na primeira chamada. Se o tamanho do buffer de saída for insuficiente para 
/// armazenar toda a varredura, este deslocamento permite que você retome a cópia do final da operação anterior da cópia.</param>
/// <param name="Param_ScanDataSize">O tamanho, em bytes, da matriz (Param_Out_ScanDataBuffer).</param>
/// <param name="Param_ScanDataBufferDestino">Uma interface (ICarenBuffer) que contém o buffer que vai receber os dados da tabela.. Esse parametro não pode ser nulo.</param>
/// <param name="Param_Out_BufferSizeAtual">Retorna o tamanho dos dados de varredura realmente copiados em (Param_Out_ScanDataBuffer). O tamanho devolvido pode ser menor que o tamanho do (Param_ScanDataSize).</param>
CarenResult CarenWICJpegFrameDecode::CopyScan(
UInt32 Param_ScanIndex,
UInt32 Param_ScanOffset,
UInt32 Param_ScanDataSize,
ICarenBuffer^ Param_ScanDataBufferDestino,
[Out] UInt32% Param_Out_BufferSizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferDestino = DefaultGenPointer;
	UINT vi_OutBufferSizeAtual = 0;

	//Recupera o ponteiro para o buffer de destino.
	Resultado = Param_ScanDataBufferDestino->GetInternalPointer(vi_pBufferDestino);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyScan(Param_ScanIndex, Param_ScanOffset,Param_ScanDataSize, Util.ConverterIntPtrTo<PBYTE>(vi_pBufferDestino), &vi_OutBufferSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor real dos dados no buffer.
	Param_Out_BufferSizeAtual = vi_OutBufferSizeAtual;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor indicando se esse decodificador suporta indexação para acesso aleatório eficiente. A indexação só é suportada para alguns tipos de JPEG.
/// </summary>
/// <param name="Param_Out_Suporte">Retorna TRUE se a indexação for suportada; caso contrário, FALSE.</param>
CarenResult CarenWICJpegFrameDecode::DoesSupportIndexing([Out] Boolean% Param_Out_Suporte)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportIndexing(&vi_OutSuporte);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o valor no parametro de saida.
	Param_Out_Suporte = vi_OutSuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia da tabela AC Huffman para a digitalização e a tabela especificadas. 
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameDecode::GetAcHuffmanTable(
UInt32 Param_ScanIndex,
UInt32 Param_TableIndex,
[Out] CA_DXGI_JPEG_AC_HUFFMAN_TABLE^% Param_Out_ACHuffmanTable)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_JPEG_AC_HUFFMAN_TABLE vi_OutDxgiJpegTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAcHuffmanTable(Param_ScanIndex, Param_TableIndex, &vi_OutDxgiJpegTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_ACHuffmanTable = Util.ConverterDXGI_JPEG_AC_HUFFMAN_TABLEUnmanaged_ToManaged(&vi_OutDxgiJpegTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas. 
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho de 
/// varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameDecode::GetDcHuffmanTable(
UInt32 Param_ScanIndex,
UInt32 Param_TableIndex,
[Out] CA_DXGI_JPEG_DC_HUFFMAN_TABLE^% Param_Out_DCHuffmanTable)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_JPEG_DC_HUFFMAN_TABLE vi_OutDxgiJpegTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDcHuffmanTable(Param_ScanIndex, Param_TableIndex, &vi_OutDxgiJpegTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_DCHuffmanTable = Util.ConverterDXGI_JPEG_DC_HUFFMAN_TABLEUnmanaged_ToManaged(&vi_OutDxgiJpegTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera dados de cabeçalho de todo o frame. O resultado inclui parâmetros do marcador Start Of Frame (SOF) para a varredura, bem como parâmetros derivados de outros metadados, 
/// como o modelo de cor dos dados comprimidos.
/// </summary>
/// <param name="Param_Out_FrameHeader">Retrona uma estrutura que contém os dados do cabeçalho do frame.</param>
CarenResult CarenWICJpegFrameDecode::GetFrameHeader([Out] CA_WICJpegFrameHeader^% Param_Out_FrameHeader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICJpegFrameHeader vi_OutFrameHeader = {  };

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameHeader(&vi_OutFrameHeader);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_FrameHeader = Util.ConverterWICJpegFrameHeaderUnmanaged_ToManaged(&vi_OutFrameHeader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia da tabela de quantização. 
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar. Índices válidos para uma determinada varredura podem ser determinados recuperando o cabeçalho 
/// de varredura com ICarenWICJpegFrameDecode::GetScanHeader.</param>
/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameDecode::GetQuantizationTable(
UInt32 Param_ScanIndex,
UInt32 Param_TableIndex,
[Out] CA_DXGI_JPEG_QUANTIZATION_TABLE^% Param_Out_QuantizationTable)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_JPEG_QUANTIZATION_TABLE vi_OutDxgiTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetQuantizationTable(Param_ScanIndex, Param_TableIndex, &vi_OutDxgiTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_QuantizationTable = Util.ConverterDXGI_JPEG_QUANTIZATION_TABLEUnmanaged_ToManaged(&vi_OutDxgiTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera parâmetros do marcador START Of Scan (SOS) para o scan com o índice especificado. 
/// </summary>
/// <param name="Param_ScanIndex">O índice da varredura para a qual os dados do cabeçalho são recuperados.</param>
/// <param name="Param_Out_ScanHeader">Retorna uma estrutura que contém os dados de cabeçalho do frame.</param>
CarenResult CarenWICJpegFrameDecode::GetScanHeader(
UInt32 Param_ScanIndex,
[Out] CA_WICJpegScanHeader^% Param_Out_ScanHeader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICJpegScanHeader vi_OutScanHeader = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetScanHeader(Param_ScanIndex, &vi_OutScanHeader);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_ScanHeader = Util.ConverterWICJpegScanHeaderUnmanaged_ToManaged(&vi_OutScanHeader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

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
CarenResult CarenWICJpegFrameDecode::SetIndexing(
CA_WICJpegIndexingOptions Param_Opcoes,
UInt32 Param_HorizontalIntervalSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetIndexing(static_cast<WICJpegIndexingOptions>(Param_Opcoes), Param_HorizontalIntervalSize);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}