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
#include "CarenWICBitmapScaler.h"

//Destruidor.
CarenWICBitmapScaler::~CarenWICBitmapScaler()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapScaler::CarenWICBitmapScaler()
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
CarenResult CarenWICBitmapScaler::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapScaler::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapScaler*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapScaler**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICBitmapScaler::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICBitmapScaler*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICBitmapScaler**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapScaler::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICBitmapScaler::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICBitmapScaler::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICBitmapScaler::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapScaler::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapScaler::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICBitmapScaler::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICBitmapScaler();
}



// Métodos da interface proprietária(ICarenWICBitmapScaler)


/// <summary>
/// Inicializa o scaler bitmap com os parâmetros fornecidos.
/// O ICarenWICBitmapScaler não pode ser inicializado várias vezes. Por exemplo, ao dimensionar cada frame em uma imagem de vários frames, um novo ICarenWICBitmapScaler 
/// deve ser criado e inicializado para cada frame.
/// </summary>
/// <param name="Param_BitmapEntrada">A fonte de bitmap de entrada.</param>
/// <param name="Param_Width">A Largura do destino.</param>
/// <param name="Param_Heigth">A Altura do destino.</param>
/// <param name="Param_ModoInterpolacao">O CA_WICBitmapInterpolationMode para usar durante o dimensionamento.</param>
CarenResult CarenWICBitmapScaler::Initialize(
ICarenWICBitmapSource^ Param_BitmapEntrada,
UInt32 Param_Width,
UInt32 Param_Heigth,
CA_WICBitmapInterpolationMode Param_ModoInterpolacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pBitmapSource = NULL;
	WICBitmapInterpolationMode InterpolationMode = static_cast<WICBitmapInterpolationMode>(Param_ModoInterpolacao);

	//Recupera o ponteiro para a fonte do bitmap
	Resultado = RecuperarPonteiroCaren(Param_BitmapEntrada, &pBitmapSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(pBitmapSource, Param_Width, Param_Heigth, InterpolationMode);

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




// Métodos da interface (ICarenWICBitmapSource)


/// <summary>
/// Recupera a tabela de cores para formatos de pixel indexados. 
/// </summary>
/// <param name="Param_Palette">Uma ICarenWICPalette. Uma paleta pode ser criada usando o método ICarenWICImagingFactory::CreatePalette.</param>
CarenResult CarenWICBitmapScaler::CopyPalette(ICaren^ Param_Palette)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* pPaleta = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Palette, &pPaleta);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPalette(pPaleta);

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

/// <summary>
/// Instrui o objeto a produzir pixels. CopyPixels é uma das duas principais rotinas de processamento de imagens(a outra é Lock), acionando o processamento real.Ele instrui o 
/// objeto a produzir pixels de acordo com seu algoritmo - isso pode envolver a decodificação de uma parte de um JPEG armazenado em disco, a cópia de um bloco de memória ou a 
/// computação analítica de um gradiente complexo.O algoritmo é completamente dependente do objeto que implementa a interface.
/// </summary>
/// <param name="Param_RetanguloCopy">O retângulo para copiar. Um valor NULO especifica todo o bitmap.</param>
/// <param name="Param_Stride">O Stride do bitmap</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer.</param>
/// <param name="Param_Buffer">Um ponteiro para o buffer.</param>
CarenResult CarenWICBitmapScaler::CopyPixels(
	CA_WICRect^ Param_RetanguloCopy,
	UInt32 Param_Stride,
	UInt32 Param_TamanhoBuffer,
	ICarenBuffer^ Param_Buffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICRect* pRetanguloCopy = NULL; //Pode ser NULO.
	GenPointer pBufferDados = DefaultGenPointer;

	//Converte a estrutura se tiver sido informada.
	pRetanguloCopy = ObjetoGerenciadoValido(Param_RetanguloCopy) ? Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloCopy) : NULL;

	//Recupera o ponteiro para o buffer
	Resultado = Param_Buffer->GetInternalPointer(pBufferDados);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPixels(pRetanguloCopy, Param_Stride, Param_TamanhoBuffer, Util.ConverterIntPtrTo<PBYTE>(pBufferDados));

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

/// <summary>
/// Recupera o formato de pixel da fonte bitmap. O formato de pixel retornado por este método não é necessariamente o formato de pixel que a imagem é armazenada como. O codec pode 
/// executar uma conversão de formato do formato pixel de armazenamento para um formato de pixel de saída.
/// </summary>
/// <param name="Param_Out_FormatoPixel">Recebe o GUID do formato de pixel em que o bitmap está armazenado.</param>
CarenResult CarenWICBitmapScaler::GetPixelFormat([Out] String^% Param_Out_FormatoPixel)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidFormatPixel = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPixelFormat(&OutGuidFormatPixel);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o GUID para string e define no parametro de saida.
	Param_Out_FormatoPixel = Util.ConverterGuidToString(OutGuidFormatPixel);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a taxa de amostragem entre pixels e medições do mundo físico. 
/// Alguns formatos, como GIF e ICO, não possuem suporte completo ao DPI. Para GIF, este método calcula os valores de DPI a partir da proporção, utilizando um DPI base de (96,0, 96,0).
///  O formato ICO não suporta DPI em tudo, e o método sempre retorna (96.0.96.0) para imagens de ICO. Além disso, o próprio WIC não transforma imagens com base nos valores de DPI em uma 
/// imagem. Cabe ao interlocutor transformar uma imagem baseada na resolução devolvida.
/// </summary>
/// <param name="Param_Out_DpiX">Recebe a resolução dpi do eixo X.</param>
/// <param name="Param_Out_DpiY">Recebe a resolução dpi do eixo Y.</param>
CarenResult CarenWICBitmapScaler::GetResolution(
	[Out] double% Param_Out_DpiX,
	[Out] double% Param_Out_DpiY)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DOUBLE OutDpiX = 0;
	DOUBLE OutDpiY = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetResolution(&OutDpiX, &OutDpiY);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_DpiX = OutDpiX;
	Param_Out_DpiY = OutDpiY;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a largura e a altura do bitmap. 
/// </summary>
/// <param name="Param_Out_PixelWidthBitmap">Recebe a Largura do pixel do bitmap.</param>
/// <param name="Param_Out_PixelHeightBitmap">Recebe a Altura do pixel do bitmap.</param>
CarenResult CarenWICBitmapScaler::GetSize(
	[Out] UInt32% Param_Out_PixelWidthBitmap,
	[Out] UInt32% Param_Out_PixelHeightBitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32 OutPixelWidthBitmap = 0;
	UINT32 OutPixelHeightBitmap = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSize(&OutPixelWidthBitmap, &OutPixelHeightBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados nos parametros de saida.
	Param_Out_PixelWidthBitmap = OutPixelWidthBitmap;
	Param_Out_PixelHeightBitmap = OutPixelHeightBitmap;

Done:;
	//Retorna o resultado.
	return Resultado;
}