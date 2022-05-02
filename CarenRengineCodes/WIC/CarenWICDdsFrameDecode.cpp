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
#include "CarenWICDdsFrameDecode.h"

//Destruidor.
CarenWICDdsFrameDecode::~CarenWICDdsFrameDecode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICDdsFrameDecode::CarenWICDdsFrameDecode()
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
CarenResult CarenWICDdsFrameDecode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDdsFrameDecode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDdsFrameDecode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDdsFrameDecode**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICDdsFrameDecode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICDdsFrameDecode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICDdsFrameDecode**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDdsFrameDecode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICDdsFrameDecode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICDdsFrameDecode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICDdsFrameDecode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICDdsFrameDecode::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICDdsFrameDecode::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICDdsFrameDecode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICDdsFrameDecode();
}



// Métodos da interface proprietária(ICarenWICDdsFrameDecode)


/// <summary>
/// Solicita dados de pixel, pois são armazenados nativamente no arquivo DDS. Se a textura não usar um DXGI_FORMAT compactado por bloco, este método se comporta de forma semelhante 
/// ao IWICBitmapFonte::CopyPixels. No entanto, ele não executa qualquer conversão de formato de pixel e, em vez disso, produz os dados brutos do arquivo DDS.
/// </summary>
/// <param name="Param_RetanguloCopy">O retângulo para copiar da fonte. Um valor NULO especifica toda a textura. Se a textura usar um DXGI_FORMAT comprimido de bloco, todos os valores 
/// do retângulo são expressos em número de blocos, não pixels.</param>
/// <param name="Param_Stride">O Stride, em bytes, do Buffer de destino. Isso representa o número de bytes do Buffer para a próxima linha de dados. Se a textura usar uma DXGI_FORMAT
///  compactada por bloco, uma "linha de dados" será definida como uma linha de blocos que contém várias linhas de varredura de pixels.</param>
/// <param name="Param_BufferSize">O tamanho, em bytes, do buffer de destino.</param>
/// <param name="Param_BufferDestino">Uma interface (ICarenBuffer) para o buffer de destino.</param>
CarenResult CarenWICDdsFrameDecode::CopyBlocks(
CA_WICRect^ Param_RetanguloCopy,
UInt32 Param_Stride,
UInt32 Param_BufferSize,
ICarenBuffer^ Param_BufferDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRect* vi_RectCopy = Nulo; //Pode ser Nulo.
	GenPointer vi_BufferDestino = DefaultGenPointer;

	//Converte a estrutura se informada.
	vi_RectCopy = ObjetoGerenciadoValido(Param_RetanguloCopy) ? Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloCopy) : Nulo;

	//Recupera o potneiro para o buffer de destino.
	Resultado = Param_BufferDestino->GetInternalPointer(vi_BufferDestino);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyBlocks(vi_RectCopy, Param_Stride, Param_BufferSize, Util.ConverterIntPtrTo<PBYTE>(vi_BufferDestino));

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_RectCopy);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém informações sobre o formato em que a imagem DDS é armazenada.
/// Essas informações podem ser usadas para alocar memória ou construir recursos Direct3D ou Direct2D, por exemplo, usando ICarenD3D11Device::CreateTexture2D ou ICarenD2D1DeviceContext::CreateBitmap.
/// </summary>
/// <param name="Param_Out_FormatInfo">Retorna uma estrutura que contém as informações sobre o formato DDS.</param>
CarenResult CarenWICDdsFrameDecode::GetFormatInfo([Out] CA_WICDdsFormatInfo^% Param_Out_FormatInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICDdsFormatInfo vi_OutFormatInfo = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFormatInfo(&vi_OutFormatInfo);

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
	Param_Out_FormatInfo = Util.ConverterWICDdsFormatInfoUnmanaged_ToManaged(&vi_OutFormatInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a largura e a altura, em blocos, da imagem DDS.
/// Para texturas compactadas de bloco, os valores de largura e altura retornados não definem completamente o tamanho da textura porque a imagem é acolchoada para se adequar 
/// ao tamanho de bloco inteiro mais próximo.
/// Se a textura não usar um DXGI_FORMAT comprimido de bloco, este método retorna o tamanho da textura em pixels; para esses formatos o tamanho do bloco devolvido pelo 
/// ICarenWICDdsFrameDecoder::GetFormatInfo é 1x1.
/// </summary>
/// <param name="Param_Out_WidthInBlocks">Retorna a largura da imagem DDS em blocos.</param>
/// <param name="Param_Out_HeightInBlocks">Retorna a altura da imagem DDS em blocos.</param>
CarenResult CarenWICDdsFrameDecode::GetSizeInBlocks(
[Out] UInt32% Param_Out_WidthInBlocks,
[Out] UInt32% Param_Out_HeightInBlocks)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT vi_OutWidth, vi_OutHeight = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSizeInBlocks(&vi_OutWidth, &vi_OutHeight);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define nos parametros de saida os valores.
	Param_Out_WidthInBlocks = vi_OutWidth;
	Param_Out_HeightInBlocks = vi_OutHeight;

Done:;
	//Retorna o resultado.
	return Resultado;
}