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

//MÉTODOS DA CLASSE COMPARTILHADA (Shared_D2D1Bitmap)


// Métodos da interface (ICarenD2D1Bitmap1)

/// <summary>
/// Obtém as informações de contexto de cores associadas ao bitmap.
/// </summary>
/// <param name="Param_Out_ColorContext">Quando este método retorna, contém o endereço de um ponteiro para a interface de contexto de cor associada ao bitmap.</param>
CarenResult Shared_D2D1Bitmap::GetColorContext(
	ID2D1Bitmap1* Param_MyPointerWork,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1ColorContext* pColorContext = NULL;

	//Chama o método para realizar a operação.
	Param_MyPointerWork->GetColorContext(&pColorContext);

	//Verifica se a interface é valida
	if (!ObjetoValido(pColorContext))
	{
		//Falhou ao obter um ponteiro para a interface.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retonada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define um ponteiro para a interface.
	Resultado = Param_Out_ColorContext->AdicionarPonteiro(pColorContext);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Ocorreu uma falha ao definir o ponteiro.

		//Libera a referência obtida.
		pColorContext->Release();
		pColorContext = NULL;

		//Limpa a interface criada.
		Param_Out_ColorContext->Finalizar();
		Param_Out_ColorContext = nullptr;

		//Deixa continuar.
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém as opções usadas na criação do bitmap.
/// </summary>
/// <param name="Param_Out_BitmapOptions">Retorna as opções utilizadas.</param>
void Shared_D2D1Bitmap::GetOptions(
	ID2D1Bitmap1* Param_MyPointerWork,
	[Out] CA_D2D1_BITMAP_OPTIONS% Param_Out_BitmapOptions)
{
	//Variaveis a serem utilizadas.
	D2D1_BITMAP_OPTIONS OutBitmapOption;

	//Chama o método para realizar a operação.
	OutBitmapOption = Param_MyPointerWork->GetOptions();

	//Converte e define no parametro de saida.
	Param_Out_BitmapOptions = ConverterPara<CA_D2D1_BITMAP_OPTIONS>(OutBitmapOption);
}

/// <summary>
/// Obtém a superfície especificada quando o bitmap foi criado, ou a superfície padrão criada quando o bitmap foi criado.
/// O bitmap usado deve ter sido criado a partir de um alvo de renderização de superfície DXGI, um alvo de renderização derivada ou um contexto de dispositivo criado a partir de um ICarenD2D1Device. 
/// A superfície devolvida pode ser usada com o Microsoft Direct3D ou qualquer outra API que interopera com superfícies compartilhadas.
/// </summary>
/// <param name="Param_Out_DxgiSurface">Retorna a superfície DXGI subjacente para o bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult Shared_D2D1Bitmap::GetSurface(
	ID2D1Bitmap1* Param_MyPointerWork, 
	ICaren^ Param_Out_DxgiSurface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pSurface = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetSurface(&pSurface);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro nativo na interface fornecida.
	Resultado = Param_Out_DxgiSurface->AdicionarPonteiro(pSurface);

	//Verifica se não ocorreu erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera a referência criada.
		pSurface->Release();
		pSurface = NULL;

		//Deixa o método continuar.
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Mapeia os dados do Bitmap na memória. O bitmap deve ter sido criado com a bandeira D2D1_BITMAP_OPTIONS_CPU_READ especificada para este método poder funcionar.
/// [NOTA] Você não pode usar bitmaps para alguns propósitos enquanto mapeado. Particularmente, o método ICarenD2D1Bitmap1::CopyFromBitmap não funciona se o bitmap de origem ou destino estiver mapeado.
/// </summary>
/// <param name="Param_Options">As opções utilizadas no mapeamento do bitmap na memória.</param>
/// <param name="Param_Out_MappedRect">Quando este método retorna, contém uma referência ao retângulo que foi mapeado na memória. O usuário deve definir o tamanho do buffer(bits) dentro da estrutura antes de usar.</param>
CarenResult Shared_D2D1Bitmap::Map(
	ID2D1Bitmap1* Param_MyPointerWork,
	CA_D2D1_MAP_OPTIONS Param_Options,
	[Out] CA_D2D1_MAPPED_RECT^% Param_Out_MappedRect)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MAP_OPTIONS MapOptions = ConverterPara<D2D1_MAP_OPTIONS>(Param_Options);
	D2D1_MAPPED_RECT OutMapped = { };

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->Map(MapOptions, &OutMapped);

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
	Param_Out_MappedRect = Util.ConverterD2D1_MAPPED_RECTUnmanagedToManaged(&OutMapped);
Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desmapeia o bitmap da memória. Qualquer memória retornada da chamada Mapa agora é inválida e pode ser recuperada pelo sistema operacional ou usada para outros fins. 
/// O bitmap deve ter sido previamente mapeado.
/// </summary>
CarenResult Shared_D2D1Bitmap::Unmap(ID2D1Bitmap1* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->Unmap();

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



// Métodos da interface (ICarenD2D1Bitmap1)

/// <summary>
/// Copia a região especificada do bitmap especificado no bitmap atual.
/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, observe que este método não executa a conversão de formato, 
/// e falhará se os formatos bitmap não coincidirem.
/// </summary>
/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
/// <param name="Param_Bitmap">O bitmap para copiar.</param>
/// <param name="Param_SourceRect">A área de bitmap para copiar.</param>
CarenResult Shared_D2D1Bitmap::CopyFromBitmap(
	ID2D1Bitmap* Param_MyPointerWork,
	CA_D2D1_POINT_2U^ Param_PointDestino,
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_RECT_U^ Param_SourceRect)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2U* pPointDestino = NULL;
	D2D1_RECT_U* pSourceRect = NULL;
	ID2D1Bitmap* pBitmapOrigem = NULL;

	//Converte as estruturas.
	pPointDestino = Util.ConverterD2D1_POINT_2UManagedToUnmanaged(Param_PointDestino);
	pSourceRect = Util.ConverterD2D1_RECT_UManagedToUnmanaged(Param_SourceRect);

	//Verifica se as estruturas  são validas
	if (ObjetoValido(pPointDestino) && ObjetoValido(pSourceRect))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Não foi possivel converter uma ou mais estruturas necessárias.

		//Define o código de erro.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_ESTRUTURA, false);

		//Sai do método
		Sair;
	}

	//Obtém um ponteiro para o bitmap a ser copiado.
	Resultado = Param_Bitmap->RecuperarPonteiro((void**)&pBitmapOrigem);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CopyFromBitmap(pPointDestino, pBitmapOrigem, pSourceRect);

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
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPointDestino);
	DeletarEstruturaSafe(&pSourceRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Copie a região especificada da memória para o bitmap atual.
/// Este método não atualiza o tamanho do bitmap atual. Se o conteúdo do bitmap de origem não se encaixar no bitmap atual, este método falhará. Além disso, note que este método não realiza conversão de formato; os dois 
/// formatos bitmap devem coincidir.
/// </summary>
/// <param name="Param_DestinoRect">No bitmap atual, o retângulo para o qual a região especificada pelo (Param_SourceData) é copiada.</param>
/// <param name="Param_SourceData">Os dados para copiar.</param>
/// <param name="Param_Pitch">O passo, ou arremesso, do bitmap de origem armazenado em srcData. O passo é a contagem de byte de uma linha de varredura (uma linha de pixels na memória). O passo pode ser computado a partir 
/// da seguinte fórmula: largura de pixel * bytes por pixel + preenchimento de memória.</param>
CarenResult Shared_D2D1Bitmap::CopyFromMemory(
	ID2D1Bitmap* Param_MyPointerWork,
	CA_D2D1_RECT_U^ Param_DestinoRect,
	ICarenBuffer^ Param_SourceData,
	UInt32 Param_Pitch)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_U* pDestRect = NULL;
	IntPtr SourcePointerBuffer = IntPtr::Zero;
	PVOID pBufferSourceCopy = NULL;

	//Converte a estrutura.
	pDestRect = Util.ConverterD2D1_RECT_UManagedToUnmanaged(Param_DestinoRect);

	//Verifica se a estrutura é valida.
	if (ObjetoValido(pDestRect))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Não foi possivel converter uma ou mais estruturas necessárias.

		//Define o código de erro.
		SetCarenErro(Resultado, ResultCode::ER_CONVERSAO_ESTRUTURA);

		//Sai do método
		Sair;
	}

	//Obtém o ponteiro para os dados na memória.
	Resultado = Param_SourceData->GetInternalPointer(SourcePointerBuffer);

	//Verifica se obteve com sucesso o ponteiro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro para a memoria a ser copiada.

		//Sai do método.
		Sair;
	}

	//Converte o intptr para o buffer.
	pBufferSourceCopy = Util.ConverterIntPtrTo<PVOID>(SourcePointerBuffer);

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CopyFromMemory(pDestRect, pBufferSourceCopy, Param_Pitch);

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
	//Libera a memoria dos dados utilizados.
	DeletarEstruturaSafe(&pDestRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Copia a região especificada do alvo de renderização especificado no bitmap atual.
/// </summary>
/// <param name="Param_PointDestino">No bitmap atual, o canto superior esquerdo da área para a qual a região especificada pelo (Param_SourceRect) é copiada.</param>
/// <param name="Param_D2D1RenderTarget">O alvo de renderização que contém a região para copiar.</param>
/// <param name="Param_SourceRect">A área do (Param_D2D1RenderTarget) para copiar.</param>
CarenResult Shared_D2D1Bitmap::CopyFromRenderTarget(
	ID2D1Bitmap* Param_MyPointerWork,
	CA_D2D1_POINT_2U^ Param_PointDestino,
	ICaren^ Param_D2D1RenderTarget,
	CA_D2D1_RECT_U^ Param_SourceRect)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2U* pPointDestino = NULL;
	D2D1_RECT_U* pSourceRect = NULL;
	ID2D1RenderTarget* pRenderTarget = NULL;

	//Converte as estruturas.
	pPointDestino = Util.ConverterD2D1_POINT_2UManagedToUnmanaged(Param_PointDestino);
	pSourceRect = Util.ConverterD2D1_RECT_UManagedToUnmanaged(Param_SourceRect);

	//Verifica se as estruturas  são validas
	if (ObjetoValido(pPointDestino) && ObjetoValido(pSourceRect))
	{
		//Deixa o método continuar.
	}
	else
	{
		//Falhou.. Não foi possivel converter uma ou mais estruturas necessárias.

		//Define o código de erro.
		SetCarenErro(Resultado, ResultCode::ER_CONVERSAO_ESTRUTURA);

		//Sai do método
		Sair;
	}

	//Obtém um ponteiro para o render target.
	Resultado = Param_D2D1RenderTarget->RecuperarPonteiro((void**)&pRenderTarget);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->CopyFromRenderTarget(pPointDestino, pRenderTarget, pSourceRect);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPointDestino);
	DeletarEstruturaSafe(&pSourceRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorne os pontos por polegada (DPI) do bitmap.
/// </summary>
/// <param name="Param_Out_DpiX">Retorna o DPI horizontal da imagem.</param>
/// <param name="Param_Out_DpiY">Retorna o DPI vertical da imagem.</param>
void Shared_D2D1Bitmap::GetDpi(
	ID2D1Bitmap* Param_MyPointerWork,
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY)
{
	//Variaveis.
	FLOAT DpiX, DpiY = 0;

	//Chama o método para realizar a operação.
	Param_MyPointerWork->GetDpi(&DpiX, &DpiY);

	//Define nos parametros de saida.
	Param_Out_DpiX = DpiX;
	Param_Out_DpiY = DpiY;
}

/// <summary>
/// Recupera o formato de pixel e o modo alfa do bitmap.
/// </summary>
/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do bitmap.</param>
void Shared_D2D1Bitmap::GetPixelFormat(
	ID2D1Bitmap* Param_MyPointerWork,
	[Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_PIXEL_FORMAT OutPixelFormat = {  };

	//Chama o método para realizar a operação.
	OutPixelFormat = Param_MyPointerWork->GetPixelFormat();

	//Converte e define no parametro de saida.
	Param_Out_PixelFormat = Util.ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&OutPixelFormat);
}

/// <summary>
/// Retorna o tamanho, em unidades dependentes de dispositivos (pixels), do bitmap.
/// </summary>
/// <param name="Param_Out_PixelSize">Retorna o tamanho, em pixels, do bitmap.</param>
void Shared_D2D1Bitmap::GetPixelSize(
	ID2D1Bitmap* Param_MyPointerWork,
	[Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U OutPixelSize = {};

	//Chama o método para realizar a operação.
	OutPixelSize = Param_MyPointerWork->GetPixelSize();

	//Converte e define no parametro de saida.
	Param_Out_PixelSize = Util.ConverterD2D1_SIZE_UUnmanagedToManaged(&OutPixelSize);
}

/// <summary>
/// Retorna o tamanho, em pixels independentes do dispositivo (DIPs), do bitmap.
/// Um DIP é de 1/96 de polegada. Para recuperar o tamanho dos pixels do dispositivo, use o método ICarenD2D1Bitmap1::GetPixelSize.
/// </summary>
/// <param name="Param_Out_Size">Retorna o tamanho, em DIPs, do bitmap.</param>
void Shared_D2D1Bitmap::GetSize(
	ID2D1Bitmap* Param_MyPointerWork,
	[Out] CA_D2D1_SIZE_F^% Param_Out_Size)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F OutSize = {};

	//Chama o método para realizar a operação.
	OutSize = Param_MyPointerWork->GetSize();

	//Converte e define no parametro de saida.
	Param_Out_Size = Util.ConverterD2D1_SIZE_FUnmanagedToManaged(&OutSize);
}