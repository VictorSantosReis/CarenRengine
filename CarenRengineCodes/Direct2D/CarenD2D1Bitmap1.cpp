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
#include "CarenD2D1Bitmap1.h"

//Destruidor.
CarenD2D1Bitmap1::~CarenD2D1Bitmap1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1Bitmap1::CarenD2D1Bitmap1()
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
CarenResult CarenD2D1Bitmap1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Bitmap1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Bitmap1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Bitmap1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Bitmap1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Bitmap1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Bitmap1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Bitmap1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Bitmap1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1Bitmap1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1Bitmap1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1Bitmap1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Bitmap1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Bitmap1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1Bitmap1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Bitmap1();
}



// Métodos da interface proprietária(ICarenD2D1Bitmap1)


/// <summary>
/// Obtém as informações de contexto de cores associadas ao bitmap.
/// </summary>
/// <param name="Param_Out_ColorContext">Quando este método retorna, contém o endereço de um ponteiro para a interface de contexto de cor associada ao bitmap.</param>
CarenResult CarenD2D1Bitmap1::GetColorContext(
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
	PonteiroTrabalho->GetColorContext(&pColorContext);

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
void CarenD2D1Bitmap1::GetOptions(
[Out] CA_D2D1_BITMAP_OPTIONS% Param_Out_BitmapOptions)
{
	//Variaveis a serem utilizadas.
	D2D1_BITMAP_OPTIONS OutBitmapOption;

	//Chama o método para realizar a operação.
	OutBitmapOption = PonteiroTrabalho->GetOptions();

	//Converte e define no parametro de saida.
	Param_Out_BitmapOptions = ConverterPara<CA_D2D1_BITMAP_OPTIONS>(OutBitmapOption);
}

/// <summary>
/// Obtém a superfície especificada quando o bitmap foi criado, ou a superfície padrão criada quando o bitmap foi criado.
/// O bitmap usado deve ter sido criado a partir de um alvo de renderização de superfície DXGI, um alvo de renderização derivada ou um contexto de dispositivo criado a partir de um ICarenD2D1Device. 
/// A superfície devolvida pode ser usada com o Microsoft Direct3D ou qualquer outra API que interopera com superfícies compartilhadas.
/// </summary>
/// <param name="Param_Out_DxgiSurface">Retorna a superfície DXGI subjacente para o bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1Bitmap1::GetSurface(ICaren^ Param_Out_DxgiSurface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pSurface = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSurface(&pSurface);

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
CarenResult CarenD2D1Bitmap1::Map(
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
	Hr = PonteiroTrabalho->Map(MapOptions, &OutMapped);

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
CarenResult CarenD2D1Bitmap1::Unmap()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Unmap();

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
CarenResult CarenD2D1Bitmap1::CopyFromBitmap(
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
	Hr = PonteiroTrabalho->CopyFromBitmap(pPointDestino, pBitmapOrigem, pSourceRect);

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
CarenResult CarenD2D1Bitmap1::CopyFromMemory(
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
	Hr = PonteiroTrabalho->CopyFromMemory(pDestRect, pBufferSourceCopy, Param_Pitch);

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
CarenResult CarenD2D1Bitmap1::CopyFromRenderTarget(
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
	Hr = PonteiroTrabalho->CopyFromRenderTarget(pPointDestino, pRenderTarget, pSourceRect);

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
void CarenD2D1Bitmap1::GetDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY)
{
	//Variaveis.
	FLOAT DpiX, DpiY = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDpi(&DpiX, &DpiY);

	//Define nos parametros de saida.
	Param_Out_DpiX = DpiX;
	Param_Out_DpiY = DpiY;
}

/// <summary>
/// Recupera o formato de pixel e o modo alfa do bitmap.
/// </summary>
/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do bitmap.</param>
void CarenD2D1Bitmap1::GetPixelFormat(
	[Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_PIXEL_FORMAT OutPixelFormat = {  };

	//Chama o método para realizar a operação.
	OutPixelFormat = PonteiroTrabalho->GetPixelFormat();

	//Converte e define no parametro de saida.
	Param_Out_PixelFormat = Util.ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&OutPixelFormat);
}

/// <summary>
/// Retorna o tamanho, em unidades dependentes de dispositivos (pixels), do bitmap.
/// </summary>
/// <param name="Param_Out_PixelSize">Retorna o tamanho, em pixels, do bitmap.</param>
void CarenD2D1Bitmap1::GetPixelSize(
	[Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U OutPixelSize = {};

	//Chama o método para realizar a operação.
	OutPixelSize = PonteiroTrabalho->GetPixelSize();

	//Converte e define no parametro de saida.
	Param_Out_PixelSize = Util.ConverterD2D1_SIZE_UUnmanagedToManaged(&OutPixelSize);
}

/// <summary>
/// Retorna o tamanho, em pixels independentes do dispositivo (DIPs), do bitmap.
/// Um DIP é de 1/96 de polegada. Para recuperar o tamanho dos pixels do dispositivo, use o método ICarenD2D1Bitmap1::GetPixelSize.
/// </summary>
/// <param name="Param_Out_Size">Retorna o tamanho, em DIPs, do bitmap.</param>
void CarenD2D1Bitmap1::GetSize(
	[Out] CA_D2D1_SIZE_F^% Param_Out_Size)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F OutSize = {};

	//Chama o método para realizar a operação.
	OutSize = PonteiroTrabalho->GetSize();

	//Converte e define no parametro de saida.
	Param_Out_Size = Util.ConverterD2D1_SIZE_FUnmanagedToManaged(&OutSize);
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1Bitmap1::GetFactory(ICaren^ Param_Out_Factory)
{
	//Variaveis a serem utilizadas.
	ID2D1Factory* pFactory = NULL;

	//Variavel de resultados
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFactory(&pFactory);

	//Verifica se o ponteiro é válido
	if (!ObjetoValido(pFactory))
		Sair;

	//Adiciona o ponteiro na interface informada.
	Resultado = Param_Out_Factory->AdicionarPonteiro(pFactory);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera o ponteiro recuperado anteriormente.
		pFactory->Release();
		pFactory = NULL;

		//Chama uma execeção para indicar o erro.
		throw gcnew Exception(String::Format("Ocorreu uma falha ao definir o ponteiro nativo na interface gerenciada. Código de erro > {0}", Resultado.StatusCode));
	}

Done:;
}