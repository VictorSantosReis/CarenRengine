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
#include "CarenMFVideoDisplayControl.h"


//Destruidor.
CarenMFVideoDisplayControl::~CarenMFVideoDisplayControl()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFVideoDisplayControl::CarenMFVideoDisplayControl()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFVideoDisplayControl::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A operação falhou.
		

		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}


	//Retorna o resultado
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFVideoDisplayControl::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFVideoDisplayControl*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFVideoDisplayControl::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFVideoDisplayControl*>(Param_PonteiroNativo);

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
CarenResult CarenMFVideoDisplayControl::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFVideoDisplayControl::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFVideoDisplayControl::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFVideoDisplayControl::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFVideoDisplayControl::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFVideoDisplayControl::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFVideoDisplayControl::LiberarReferencia()
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
void CarenMFVideoDisplayControl::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFVideoDisplayControl();
}




//
// Métodos da interface proprietaria
//




/// <summary>
/// (GetAspectRatioMode) - Consulta como o processador de vídeo avançado (EVR) lida com a relação de aspecto da fonte de vídeo.
/// </summary>
/// <param name="Param_Out_AspectRatio">Recebe um ou mais bit de sinalizadores da enumeração: CA_MFVideoAspectRatioMode</param>
CarenResult CarenMFVideoDisplayControl::GetAspectRatioMode([Out] Enumeracoes::CA_MFVideoAspectRatioMode% Param_Out_AspectRatio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD AspectRatioMode = 0;

	//Chama o método para obter o modo do AspectRatio
	Hr = PonteiroTrabalho->GetAspectRatioMode(&AspectRatioMode);

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

	//Define o modo do Aspect Ratio no parametro de retorno.
	Param_Out_AspectRatio = (CA_MFVideoAspectRatioMode)safe_cast<UInt32>(AspectRatioMode);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetBorderColor) - Obtém a cor da borda para o vídeo.
/// </summary>
/// <param name="Param_Out_CorHexadecimalBorda">Recebe o valor que especifica em hexadecimal, uma cor RGB.</param>
CarenResult CarenMFVideoDisplayControl::GetBorderColor([Out] UInt32% Param_Out_CorHexadecimalBorda)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	COLORREF CorHexBorda = 0;

	//Chama o método para obter a cor da borda
	Hr = PonteiroTrabalho->GetBorderColor(&CorHexBorda);

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

	//Define o valor hexadecimal da cor da borda
	Param_Out_CorHexadecimalBorda = safe_cast<UInt32>(CorHexBorda);

Done:;
	//Retorna o resultado
	return Resultado;
}


/// <summary>
/// (GetCurrentImage) - Obtém uma cópia da imagem atual sendo exibida pelo processador de vídeo.
/// </summary>
/// <param name="Param_Out_BimapInfoHeader">Recebe uma estrutura que contém uma descrição do bitmap</param>
/// <param name="Param_Out_BufferImagem">Interface que contém um buffer que contém um bitmap independente de dispositivo do Windows compactado (DIB).
/// O chamador deve liberar a memória para o bitmap chamando: CoTaskMemFree</param>
/// <param name="Param_Out_BufferLargura">Contém a largura do buffer retornado em: Param_Out_BufferImagem.</param>
/// <param name="Param_Out_TimeStamp">Recebe o carimbo de data/hora da imagem capturada. O valor é em unidades de 100 nanosegundos.</param>
CarenResult CarenMFVideoDisplayControl::GetCurrentImage(
	[Out] Estruturas::CA_BITMAPINFOHEADER^% Param_Out_BimapInfoHeader,
	[Out] ICarenBuffer^% Param_Out_BufferImagem,
	[Out] UInt32% Param_Out_BufferLargura,
	[Out] Int64% Param_Out_TimeStamp)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	PBYTE pBufferData = NULL;
	DWORD LarguraBufferData = 0;
	MFTIME TimeSpamImagem = 0;
	BITMAPINFOHEADER bmpHeader = {};
	ICarenBuffer^ CarenBufferInterface = nullptr;
	CA_BITMAPINFOHEADER^ BitmapHeader = nullptr;

	//Define a largura da estrutura do bitmapheader
	bmpHeader.biSize = sizeof(BITMAPINFOHEADER);

	//Chama o método que vai obter a imagem atual.
	Hr = PonteiroTrabalho->GetCurrentImage(&bmpHeader, &pBufferData, &LarguraBufferData, &TimeSpamImagem);

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

	//Cria a interface que vai conter o buffer.
	CarenBufferInterface = gcnew CarenBuffer();
	//Cria a estrutura que vai conter os dados do bitmap.
	BitmapHeader = gcnew CA_BITMAPINFOHEADER();


	//Define o ponteiro de buffer.

	//Associa o ponteiro de buffer com a classe.
	CarenBufferInterface->CriarBuffer(IntPtr(pBufferData), false, LarguraBufferData, LarguraBufferData);


	//Define os dados do bipmapheader.

	//Deifne os dados na estrutura gerenciada.
	BitmapHeader->biSize = bmpHeader.biSize;
	BitmapHeader->biSizeImage = bmpHeader.biSizeImage;
	BitmapHeader->biCompression = bmpHeader.biCompression;
	BitmapHeader->biHeight = bmpHeader.biHeight;
	BitmapHeader->biWidth = bmpHeader.biWidth;
	BitmapHeader->biYPelsPerMeter = bmpHeader.biYPelsPerMeter;
	BitmapHeader->biXPelsPerMeter = bmpHeader.biXPelsPerMeter;
	BitmapHeader->biPlanes = bmpHeader.biPlanes;
	BitmapHeader->biBitCount = bmpHeader.biBitCount;
	BitmapHeader->biClrUsed = bmpHeader.biClrUsed;
	BitmapHeader->biClrImportant = bmpHeader.biClrImportant;
	
	//Define os dados nos parametros de retorno.
	Param_Out_BimapInfoHeader = BitmapHeader;
	Param_Out_BufferImagem = CarenBufferInterface;
	Param_Out_BufferLargura = LarguraBufferData;
	Param_Out_TimeStamp = TimeSpamImagem;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetFullscreen) - Consulta se o processador de vídeo avançado (EVR) está atualmente no modo de tela cheia.
/// </summary>
/// <param name="Param_Out_FullScreen">Recebe o valor que define se o vídeo está sendo renderizado em FullScreen.</param>
CarenResult CarenMFVideoDisplayControl::GetFullscreen([Out] Boolean% Param_Out_FullScreen)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	BOOL EstadoFullScreen = FALSE;

	//Chama o método para obter o estado do FullScreen
	Hr = PonteiroTrabalho->GetFullscreen(&EstadoFullScreen);

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

	//Define o estado do FullScreen.
	Param_Out_FullScreen = EstadoFullScreen ? true : false;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetIdealVideoSize) - Obtém o intervalo de tamanhos, que o processador de vídeo avançado (EVR) pode exibir sem degradar 
/// significativamente a qualidade de imagem ou o desempenho.
/// </summary>
/// <param name="Param_Out_Minimo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Minimos) da Largura e Altura (Ideias) para o vídeo.</param>
/// <param name="Param_Out_Maximo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Maximos) da Largura e Altura (Ideias) para o vídeo.</param>
CarenResult CarenMFVideoDisplayControl::GetIdealVideoSize(
	[Out] Estruturas::CA_SIZE^% Param_Out_Minimo_VideoSizeIdeal,
	[Out] Estruturas::CA_SIZE^% Param_Out_Maximo_VideoSizeIdeal)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	SIZE SzMinimo = {};
	SIZE SzMaximo = {};
	CA_SIZE^ szCAMinimo = nullptr;
	CA_SIZE^ szCAMaximo = nullptr;

	//Chama o método para obter o Size minimo e maximo ideais para o video.
	Hr = PonteiroTrabalho->GetIdealVideoSize(&SzMinimo, &SzMaximo);

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

	//Cria as estruturas que vão retornar os valores.
	szCAMinimo = gcnew CA_SIZE();
	szCAMaximo = gcnew CA_SIZE();

	//Define os dados das estruturas não gerenciadas nas gerenciadas.

	//Define os dados minimos
	szCAMinimo->SZ_X = SzMinimo.cx;
	szCAMinimo->SZ_Y = SzMinimo.cy;
	
	//Define os dados maximos
	szCAMaximo->SZ_X = SzMaximo.cx;
	szCAMaximo->SZ_Y = SzMaximo.cy;

	//Define os dados nos parametros de retorno.
	Param_Out_Minimo_VideoSizeIdeal = szCAMinimo;
	Param_Out_Maximo_VideoSizeIdeal = szCAMaximo;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetNativeVideoSize) - Obtém o tamanho e a taxa de proporção do vídeo, antes de qualquer alongamento pelo (Processador de Vídeo).
/// </summary>
/// <param name="Param_Out_VideoSize">Recebe a estrutura que contém a Largura e Altura (Nativas) para o vídeo.</param>
/// <param name="Param_Out_TaxaProporcaoVideo">Recebe a estrutura que contém a (Taxa de proporção) do vídeo.</param>
CarenResult CarenMFVideoDisplayControl::GetNativeVideoSize(
	[Out] Estruturas::CA_SIZE^% Param_Out_VideoSize,
	[Out] Estruturas::CA_SIZE^% Param_Out_TaxaProporcaoVideo)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	SIZE SzVideoSize = {};
	SIZE SzTaxaProporcao = {};
	CA_SIZE^ szCAVideoSize = nullptr;
	CA_SIZE^ szCATaxaProporcao = nullptr;

	//Chama o método para obter os dados nativos adequados.
	Hr = PonteiroTrabalho->GetIdealVideoSize(&SzVideoSize, &SzTaxaProporcao);

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

	//Cria as estruturas que vão retornar os valores.
	szCAVideoSize = gcnew CA_SIZE();
	szCATaxaProporcao = gcnew CA_SIZE();

	//Define os dados das estruturas não gerenciadas nas gerenciadas.

	//Define os dados minimos
	szCAVideoSize->SZ_X = SzVideoSize.cx;
	szCAVideoSize->SZ_Y = SzVideoSize.cy;

	//Define os dados maximos
	szCATaxaProporcao->SZ_X = SzTaxaProporcao.cx;
	szCATaxaProporcao->SZ_Y = SzTaxaProporcao.cy;

	//Define os dados nos parametros de retorno.
	Param_Out_VideoSize = szCAVideoSize;
	Param_Out_TaxaProporcaoVideo = szCATaxaProporcao;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetRenderingPrefs) - Obtém várias configurações de processamento de vídeo.
/// </summary>
/// <param name="Param_Out_Sinalizadores">Recebe um bit ou zero ou mais sinalizadores da enumeração: CA_MFVideoRenderPrefs</param>
CarenResult CarenMFVideoDisplayControl::GetRenderingPrefs([Out] Enumeracoes::CA_MFVideoRenderPrefs% Param_Out_Sinalizadores)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD RenderPrefs = 0;

	//Chama o método para obter as configurações de renderização.
	Hr = PonteiroTrabalho->GetRenderingPrefs(&RenderPrefs);

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

	//Converte e define os flags no parametro de saida.
	Param_Out_Sinalizadores = (CA_MFVideoRenderPrefs)RenderPrefs;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetVideoPosition) - Obtém os retângulos de origem e de destino para o Vídeo.
/// </summary>
/// <param name="Param_Out_RetanguloNormalized">Recebe uma estrutura que contém o retângulo de origem.</param>
/// <param name="Param_Out_RetanguloDestino">Recebe uma estrutura com o retângulo de destino atual.</param>
CarenResult CarenMFVideoDisplayControl::GetVideoPosition(
	[Out] Estruturas::CA_MFVideoNormalizedRect^% Param_Out_RetanguloNormalized,
	[Out] Estruturas::CA_RECT^% Param_Out_RetanguloDestino)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	Utilidades Util;
	MFVideoNormalizedRect vi_OutNormalizedRect = {};
	RECT vi_OutRectDestino = {};

	//Chama ó método que vai recuperar a posição do video.
	Hr = PonteiroTrabalho->GetVideoPosition(&vi_OutNormalizedRect, &vi_OutRectDestino);

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

	//Converte as estruturas e definem nos parametros de saida.
	Param_Out_RetanguloNormalized = Util.ConverterMFVideoNormalizedRectUnamaged_ToManaged(&vi_OutNormalizedRect);
	Param_Out_RetanguloDestino = Util.ConverterRECTUnmanagedToManaged(&vi_OutRectDestino);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (GetVideoWindow) - Obtém a janela de recorte para o vídeo. A janela de recorte é a (Handle) do componente que está
/// hospedando a renderização do vídeo para o usuário.
/// </summary>
/// <param name="Param_Out_HandleJanela">Recebe a handle da janela que a qual o vídeo está sendo renderizado.</param>
CarenResult CarenMFVideoDisplayControl::GetVideoWindow([Out] IntPtr% Param_Out_HandleJanela)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	HWND HandJanelaVideo = NULL;

	//Chama o método que vai obter a handle da jenela de reprodução do video.
	Hr = PonteiroTrabalho->GetVideoWindow(&HandJanelaVideo);

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
	Param_Out_HandleJanela = safe_cast<IntPtr>(HandJanelaVideo);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (RepaintSuperfice) - Redesenha o quadro de vídeo atual. Chame esse método sempre que a interface do usuário
/// sofre uma atualização da interface.
/// </summary>
CarenResult CarenMFVideoDisplayControl::RepaintSuperfice()
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para repintar a superfice de video
	Hr = PonteiroTrabalho->RepaintVideo();

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetAspectRatioMode) - Especifica como o processador de vídeo avançado (EVR) lida com a relação de aspecto 
/// da fonte de vídeo.
/// </summary>
/// <param name="Param_AspectRatio">Bit a bit ou de um ou mais sinalizadores da enumeração: CA_MFVideoAspectRatioMode</param>
CarenResult CarenMFVideoDisplayControl::SetAspectRatioMode(Enumeracoes::CA_MFVideoAspectRatioMode Param_AspectRatio) {
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir o AspectRatio.
	Hr = PonteiroTrabalho->SetAspectRatioMode((UInt32)Param_AspectRatio);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetBorderColor) - Define a cor da borda para o vídeo.
/// </summary>
/// <param name="Param_ColorRef">Especifica a cor da borda como um valor UInt32</param>
CarenResult CarenMFVideoDisplayControl::SetBorderColor(UInt32 Param_ColorRef)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir a cor da borda
	Hr = PonteiroTrabalho->SetBorderColor(Param_ColorRef);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// [Esta API não é suportada e pode ser alterada ou indisponível no futuro.]
/// (SetFullScreen) - Define o modo de renderização de tela cheia.
/// Para implementar a reprodução em tela inteira, um aplicativo deve simplesmente redimensionar a janela de vídeo para cobrir toda a área do monitor.Também definir a janela
/// para ser uma (Janela Superior), para que o aplicativo possa receber todas as mensagens de clique do mouse.
/// </summary>
/// <param name="Param_EstadoFullScreen">Se true, o renderizador de vídeo aprimorado (EVR) usará o modo de tela inteira. Se false, o EVR desenha o vídeo na 
/// janela de recorte fornecido pelo aplicativo.</param>
CarenResult CarenMFVideoDisplayControl::SetFullScreen(Boolean Param_EstadoFullScreen)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para definir o estado do FullScreen.
	Hr = PonteiroTrabalho->SetFullscreen(Param_EstadoFullScreen ? TRUE : FALSE);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetRenderingPrefs)Define preferências diversas, relacionadas com a processamento de vídeo.
/// </summary>
CarenResult CarenMFVideoDisplayControl::SetRenderingPrefs(Enumeracoes::CA_MFVideoRenderPrefs Param_RenderConfigs)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD FlagsRender = 0;

	//Converte os dados de flags
	FlagsRender = safe_cast<DWORD>(Param_RenderConfigs);

	//Chama o método que vai definir os flags para as configurações de renderização.
	Hr = PonteiroTrabalho->SetRenderingPrefs(FlagsRender);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetVideoPosition) - Define os retângulos de origem e de destino para o vídeo.
/// O retângulo de origem define qual parte do vídeo é exibida. Ele é especificado em coordenadas normalizadas. Para obter mais informações, 
/// consulte estrutura MFVideoNormalizedRect. Para exibir a imagem de vídeo inteira, defina o retângulo de origem como {0, 0, 1, 1}. O retângulo de origem padrão é {0, 0, 1, 1}.
/// O retângulo de destino define um retângulo dentro da janela de recorte onde o vídeo é exibido. Ele é especificado em pixels, em relação à área do cliente da janela.
/// Para preencher a janela inteira, defina o retângulo de destino como {0, 0, Largura, Altura}, onde Largura e Altura são dimensões da área do cliente da janela. O retângulo 
/// de destino padrão é {0, 0, 0, 0}.
/// </summary>
/// <param name="Param_RetanguloNormalized">Estrutura que especifica o retângulo origem. Este parâmetro pode ser NULO. Se este parâmetro é NULO, o 
/// retângulo de origem não é alterado.</param>
/// <param name="Param_RetanguloDestino">Especifica o retângulo de destino. Este parâmetro pode ser NULL. Se este parâmetro é NULL, o retângulo 
/// de destino não é alterado.</param>
CarenResult CarenMFVideoDisplayControl::SetVideoPosition(
	Estruturas::CA_MFVideoNormalizedRect^ Param_RetanguloNormalized,
	Estruturas::CA_RECT^ Param_RetanguloDestino)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	Utilidades Util;
	MFVideoNormalizedRect* vi_pRectNormalized = Nulo;
	PRECT vi_pRectDestino = Nulo;

	//Converte a estrutura do retangulo normalizado se valida.
	if (ObjetoGerenciadoValido(Param_RetanguloNormalized))
		vi_pRectNormalized = Util.ConverterMFVideoNormalizedRectManaged_ToUnamaged(Param_RetanguloNormalized);

	//Converte a estrutura do retangulo de destino se valida.
	if (ObjetoGerenciadoValido(Param_RetanguloDestino))
		vi_pRectDestino = Util.ConverterRECTManagedToUnmanaged(Param_RetanguloDestino);

	//Chama o método que vai definir os valores
	Hr = PonteiroTrabalho->SetVideoPosition(vi_pRectNormalized, vi_pRectDestino);

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
	//Libera a memória utilizada pelas estruturas.
	DeletarEstruturaSafe(&vi_pRectNormalized);
	DeletarEstruturaSafe(&vi_pRectDestino);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (SetVideoWindow) - Define a janela de recorte para o vídeo. Está é a janela que vai hospedar o vídeo que será
/// renderizado para visualização do usuário. A Janela refere-se a (Handle) de um componente na GUI
/// do usuário.
/// </summary>
/// <param name="Param_JanelaVideo"></param>
CarenResult CarenMFVideoDisplayControl::SetVideoWindow(IntPtr Param_JanelaVideo)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;
	Utilidades Util;
	HWND HandleVideo = NULL;

	//Chama o método para obter a janela de video
	HandleVideo = Util.ConverterIntPtrToHWND(Param_JanelaVideo);

	//Chama o método para definir a janela de video.
	Hr = PonteiroTrabalho->SetVideoWindow(HandleVideo);

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
	//Retorna o resultado
	return Resultado;
}