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
#include "CarenWICJpegFrameEncode.h"

//Destruidor.
CarenWICJpegFrameEncode::~CarenWICJpegFrameEncode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICJpegFrameEncode::CarenWICJpegFrameEncode()
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
CarenResult CarenWICJpegFrameEncode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICJpegFrameEncode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICJpegFrameEncode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICJpegFrameEncode**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICJpegFrameEncode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICJpegFrameEncode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICJpegFrameEncode**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICJpegFrameEncode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICJpegFrameEncode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICJpegFrameEncode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICJpegFrameEncode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICJpegFrameEncode::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICJpegFrameEncode::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICJpegFrameEncode::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICJpegFrameEncode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICJpegFrameEncode();
}



// Métodos da interface proprietária(ICarenWICJpegFrameEncode)


/// <summary>
/// Recupera uma cópia da tabela AC Huffman para o scan e a tabela especificadas.
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela AC Huffman para recuperar.</param>
/// <param name="Param_Out_ACHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameEncode::GetAcHuffmanTable(
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
	DXGI_JPEG_AC_HUFFMAN_TABLE vi_OutTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAcHuffmanTable(Param_ScanIndex, Param_TableIndex, &vi_OutTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_ACHuffmanTable = Util.ConverterDXGI_JPEG_AC_HUFFMAN_TABLEUnmanaged_ToManaged(&vi_OutTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia da tabela DC Huffman para a digitalização e a tabela especificadas.
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela DC Huffman para recuperar.</param>
/// <param name="Param_Out_DCHuffmanTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameEncode::GetDcHuffmanTable(
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
	DXGI_JPEG_DC_HUFFMAN_TABLE vi_OutTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDcHuffmanTable(Param_ScanIndex, Param_TableIndex, &vi_OutTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_DCHuffmanTable = Util.ConverterDXGI_JPEG_DC_HUFFMAN_TABLEUnmanaged_ToManaged(&vi_OutTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma cópia da tabela de quantização.
/// </summary>
/// <param name="Param_ScanIndex">O índice baseado em zero da varredura para a qual os dados são recuperados.</param>
/// <param name="Param_TableIndex">O índice da tabela de quantização para recuperar.</param>
/// <param name="Param_Out_QuantizationTable">Retorna uma estrutura que contém os dados da tabela.</param>
CarenResult CarenWICJpegFrameEncode::GetQuantizationTable(
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
	DXGI_JPEG_QUANTIZATION_TABLE vi_OutJpegTable = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetQuantizationTable(Param_ScanIndex, Param_TableIndex, &vi_OutJpegTable);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_QuantizationTable = Util.ConverterDXGI_JPEG_QUANTIZATION_TABLEUnmanaged_ToManaged(&vi_OutJpegTable);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Grava dados de varredura em um frame JPEG. 
/// WriteScan pode ser chamado várias vezes. Cada chamada anexa os dados de varredura especificados a quaisquer dados de varredura anteriores. Complete a varredura chamando 
/// ICarenWICBitmapFrameEncode::Commit.
/// </summary>
/// <param name="Param_SizeBuffer">O tamanho do Buffer no parâmetro (Param_BufferScanData).</param>
/// <param name="Param_BufferScanData">Os dados do scan para escrever.</param>
CarenResult CarenWICJpegFrameEncode::WriteScan(
UInt32 Param_SizeBuffer,
ICarenBuffer^ Param_BufferScanData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferScanData = DefaultGenPointer;

	//Recupera o potneiro para o buffer.
	Resultado = Param_BufferScanData->GetInternalPointer(vi_pBufferScanData);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteScan(Param_SizeBuffer, Util.ConverterIntPtrTo<BYTE*>(vi_pBufferScanData));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}