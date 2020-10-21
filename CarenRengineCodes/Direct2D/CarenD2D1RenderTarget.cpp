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
#include "CarenD2D1RenderTarget.h"

//Destruidor.
CarenD2D1RenderTarget::~CarenD2D1RenderTarget()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD2D1RenderTarget::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RenderTarget::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1RenderTarget*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1RenderTarget::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1RenderTarget*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1RenderTarget::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1RenderTarget::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1RenderTarget::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1RenderTarget::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1RenderTarget::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1RenderTarget::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1RenderTarget::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenD2D1RenderTarget::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1RenderTarget::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1RenderTarget();
}



// Métodos da interface proprietária(ICarenD2D1RenderTarget)


/// <summary>
/// Inicia o desenho deste alvo de renderização. 
/// </summary>
void CarenD2D1RenderTarget::BeginDraw()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->BeginDraw();
}

/// <summary>
/// Limpa a área de desenho para a cor especificada. 
/// </summary>
/// <param name="Param_ClearColor"></param>
void CarenD2D1RenderTarget::Clear(CA_D2D1_COLOR_F^ Param_ClearColor)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_ClearColor);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Clear(pColorF);


	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pColorF);
}

/// <summary>
/// Cria um bitmap do Direct2D de um ponteiro para dados de origem na memória. 
/// </summary>
/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
/// <param name="Param_DadosOrigem">Um ponteiro para a localização da memória dos dados da imagem ou NULO para criar um bitmap não inicializado.</param>
/// <param name="Param_Pitch">A contagem de bytes de cada linha de varredura, que é igual a (a largura da imagem em pixels × o número de bytes por pixel) + preenchimento de memória. Se (Param_DadosOrigem) é NULO, este valor é ignorado. (Note que o tom também é às vezes chamado de pitch.)</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1RenderTarget::CreateBitmap(
CA_D2D1_SIZE_U^ Param_Size,
ICarenBuffer^ Param_DadosOrigem,
UInt32 Param_Pitch,
CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL;
	IntPtr pBufferOrigem = IntPtr::Zero;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Converte as estruturas gerenciadas para as nativas.
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Size);
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap);

	//Obtém o ponteiro para a memória de origem.
	Resultado = Param_DadosOrigem->ObterPonteiroInterno(pBufferOrigem);

	//Verifica se não falhou.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(*pSizeU, pBufferOrigem.ToPointer(), Param_Pitch, pBitmapProps, &pOutBitmap);

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

	//Cria a interface que será retornada
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro na interface de saida.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera o ponteiro
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um bitmap do Direct2D não inicializado. 
/// </summary>
/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1RenderTarget::CreateBitmap(
CA_D2D1_SIZE_U^ Param_Size,
CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Converte as estruturas gerenciadas para as nativas.
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Size);
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(*pSizeU, *pBitmapProps, &pOutBitmap);

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

	//Cria a interface que será retornada
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro na interface de saida.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera o ponteiro
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. 
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel(Brush).</param>
/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,a escova padrão para o D2D1_EXTEND_MODE_CLAMP 
/// modos de extensão horizontal e vertical e o modo de interpolação D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.</param>
/// <param name="Param_PropriedadesBrush">Uma estrutura que contenha a opacidade e a transformação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,o pincel define o membro da opacidade 
/// para 1.0F e o membro de transformação para a matriz de identidade.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateBitmapBrush(
ICarenD2D1Bitmap^ Param_Bitmap,
CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES* pBitmapBrushProps = NULL; //Pode ser NULO.
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL; //Pode ser NULO.
	ID2D1BitmapBrush* pOutBrush = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte as estruturas gerenciadas para a nativa se validas.
	pBitmapBrushProps = ObjetoGerenciadoValido(Param_PropriedadesBitmapBrush)? Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmapBrush): NULL;
	pBrushProps = ObjetoGerenciadoValido(Param_PropriedadesBrush) ? Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, pBitmapBrushProps, pBrushProps, &pOutBrush);

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

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pBitmapBrushProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para seu modo de extensão, modo de interpolação, opacidade e transformação.
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateBitmapBrush(
ICarenD2D1Bitmap^ Param_Bitmap,
[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmap = NULL;
	ID2D1BitmapBrush* pOutBrush = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, &pOutBrush);

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

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ID2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para sua opacidade e transformação. 
/// O Brush bitmap criado por este método tem uma opacidade de 1.0f e a matriz de identidade como sua transformação.
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateBitmapBrush(
ICarenD2D1Bitmap^ Param_Bitmap,
CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	ID2D1BitmapBrush* pOutBrush = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES* pBitmapBrushProps = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte as estruturas gerenciadas para a nativa se validas.
	pBitmapBrushProps = Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmapBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, *pBitmapBrushProps, &pOutBrush);

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

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC). 
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. O formato pixel deve corresponder ao formato de pixel do wicBitmapSource, ou o método falhará. Para evitar uma 
/// incompatibilidade, você pode passar NULO ou passar o valor obtido ligando para a função de ajudante D2D1::PixelFormat sem especificar nenhum valor de parâmetro. Se o dpiX e o dpiY forem 0,0f, o 
/// DPI padrão, 96, será usado. As informações de DPI incorporadas no (Param_WicBitmapSource) são ignoradas.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1RenderTarget::CreateBitmapFromWicBitmap(
ICaren^ Param_WicBitmapSource,
CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource* pWicBitmapSource = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL; //Pode ser NULO.
	ID2D1Bitmap* pOutBitmap = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_WicBitmapSource->RecuperarPonteiro((LPVOID*)&pWicBitmapSource);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada para a nativa se valida.
	pBitmapProps = ObjetoGerenciadoValido(Param_PropriedadesBitmap)? Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWicBitmapSource, pBitmapProps, &pOutBitmap);

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

	//Cria a classe a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ID2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1RenderTarget::CreateBitmapFromWicBitmap(
ICaren^ Param_WicBitmapSource,
[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pWicBitmapSource = NULL;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_WicBitmapSource->RecuperarPonteiro((LPVOID*)&pWicBitmapSource);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWicBitmapSource, &pOutBitmap);

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

	//Cria a classe a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará 
/// o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
/// <param name="Param_Opcoes">Um valor que especifica se o novo alvo de renderização deve ser compatível com o GDI.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1RenderTarget::CreateCompatibleRenderTarget(
CA_D2D1_SIZE_F^ Param_DesiredSize,
CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
CA_D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS Param_Opcoes,
ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_PIXEL_FORMAT* pPixelFormat = NULL;
	D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS OptonsRender = static_cast<D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS>(Param_Opcoes);
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);
	pPixelFormat = Util.ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(DesiredFormat);
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, *pPixelFormat, &pOutRenderTarget);

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

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget, true));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pPixelFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo alvo de renderização bitmap para uso durante o desenho offscreen intermediário que é compatível com o alvo de renderização atual e tem o mesmo tamanho, DPI e formato de pixel 
/// (mas não o modo alfa) como o alvo de renderização atual. 
/// O alvo de renderização bitmap criado por este método não é compatível com o GDI, e tem um modo alfa de D2D1_ALPHA_MODE_PREMULTIPLIED.
/// </summary>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1RenderTarget::CreateCompatibleRenderTarget(ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CreateCompatibleRenderTarget(&pOutRenderTarget);

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

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget, true));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// O alvo de renderização bitmap criado por este método não é compatível com o GDI.
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo destino de renderização em pixels independentes do dispositivo. O tamanho do pixel é calculado a partir do tamanho desejado usando o DPI pai de destino. 
/// Se o tamanho desejado for mapeado para um tamanho de pixel inteiro, o DPI do destino de renderização compatível será o mesmo que o DPI pai do destino. Se o Tamanho desejado é mapeado para um tamanho de pixel 
/// fracionário, o tamanho do pixel é arredondado para o número inteiro mais próximo e o DPI para o destino de renderização compatível é um pouco maior que o DPI do destino de renderização pai. Em todos os casos, 
/// a coordenada (Param_DesiredSize.width, Param_DesiredSize.height) é mapeada para o canto inferior direito do destino de renderização compatível.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1RenderTarget::CreateCompatibleRenderTarget(
CA_D2D1_SIZE_F^ Param_DesiredSize,
ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte a estrutura.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, &pOutRenderTarget);

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

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1RenderTarget::CreateCompatibleRenderTarget(
CA_D2D1_SIZE_F^ Param_DesiredSize,
CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, &pOutRenderTarget);

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

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1RenderTarget::CreateCompatibleRenderTarget(
CA_D2D1_SIZE_F^ Param_DesiredSize,
CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_PIXEL_FORMAT* pPixelFormat = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);
	pPixelFormat = Util.ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(DesiredFormat);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, *pPixelFormat, &pOutRenderTarget);

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

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pPixelFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma interface de coleção ICarenD2D1GradientStop a partir do conjunto especificado de estruturas CA_D2D1_GRADIENT_STOP. 
/// </summary>
/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
/// <param name="Param_ColorInterpolationGamma">O espaço em que a interpolação de cores entre as paradas gradientes é realizada.</param>
/// <param name="Param_ModoExtendido">O comportamento do gradiente fora da faixa [0,1] normalizada.</param>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
CarenResult CarenD2D1RenderTarget::CreateGradientStopCollection(
cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
UInt32 Param_QuantidadeGradientes,
CA_D2D1_GAMMA Param_ColorInterpolationGamma,
CA_D2D1_EXTEND_MODE Param_ModoExtendido,
[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_GRADIENT_STOP* pMatrizGradientes = CriarMatrizEstruturas<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);
	D2D1_GAMMA Gamma = static_cast<D2D1_GAMMA>(Param_ColorInterpolationGamma);
	D2D1_EXTEND_MODE ExtendMode = static_cast<D2D1_EXTEND_MODE>(Param_ModoExtendido);
	ID2D1GradientStopCollection* pOutGradientCollection = NULL;

	//Copia os dados da matriz gerenciada para a nativa.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		//Inicializa a estrutura no index especifico.
		ZeroMemory(&pMatrizGradientes[i], sizeof(D2D1_GRADIENT_STOP));

		//Define os dados.
		pMatrizGradientes[i].position = Param_MatrizGraientStops[i]->position;

		//Define os dados ARGB.
		pMatrizGradientes->color.a = Param_MatrizGraientStops[i]->color->a;
		pMatrizGradientes->color.r = Param_MatrizGraientStops[i]->color->r;
		pMatrizGradientes->color.g = Param_MatrizGraientStops[i]->color->g;
		pMatrizGradientes->color.b = Param_MatrizGraientStops[i]->color->b;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientStopCollection(pMatrizGradientes, Param_QuantidadeGradientes, Gamma, ExtendMode, &pOutGradientCollection);

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

	//Cria a interface de saida.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutGradientCollection, Param_Out_GradientStopCollection));

Done:;
	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizGradientes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
///  Cria uma interface de coleção ICarenD2D1GradientStop a partir das estruturas GradientStops especificadas que usa o gama de interpolação de cores D2D1_GAMMA_2_2 e o modo de extensão do Clamp. 
/// </summary>
/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
CarenResult CarenD2D1RenderTarget::CreateGradientStopCollection(
cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
UInt32 Param_QuantidadeGradientes,
[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_STOP* pMatrizGradientes = CriarMatrizEstruturas<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);
	ID2D1GradientStopCollection* pOutGradientCollection = NULL;

	//Copia os dados da matriz gerenciada para a nativa.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		//Inicializa a estrutura no index especifico.
		ZeroMemory(&pMatrizGradientes[i], sizeof(D2D1_GRADIENT_STOP));

		//Define os dados.
		pMatrizGradientes[i].position = Param_MatrizGraientStops[i]->position;

		//Define os dados ARGB.
		pMatrizGradientes->color.a = Param_MatrizGraientStops[i]->color->a;
		pMatrizGradientes->color.r = Param_MatrizGraientStops[i]->color->r;
		pMatrizGradientes->color.g = Param_MatrizGraientStops[i]->color->g;
		pMatrizGradientes->color.b = Param_MatrizGraientStops[i]->color->b;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientStopCollection(pMatrizGradientes, Param_QuantidadeGradientes, &pOutGradientCollection);

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

	//Cria a interface de saida.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutGradientCollection, Param_Out_GradientStopCollection));

Done:;
	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizGradientes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis.
/// </summary>
/// <param name="Param_Size">Se (0, 0) for especificado, nenhuma loja de backup será criada por trás do recurso de camada. O recurso de camada é alocado para o tamanho mínimo quando o PushLayer é chamado.</param>
/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
CarenResult CarenD2D1RenderTarget::CreateLayer(
CA_D2D1_SIZE_F^ Param_Size,
[Out] ICarenD2D1Layer^% Param_Out_Layer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	ID2D1Layer* pOutLayer = NULL;

	//Converte a estrutura.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLayer(pSizeF, &pOutLayer);

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

	//Cria a interface de saida.
	Param_Out_Layer = gcnew CarenD2D1Layer();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLayer, Param_Out_Layer));

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pSizeF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis. 
/// </summary>
/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
CarenResult CarenD2D1RenderTarget::CreateLayer([Out] ICarenD2D1Layer^% Param_Out_Layer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Layer* pOutLayer = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLayer(&pOutLayer);

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

	//Cria a interface de saida.
	Param_Out_Layer = gcnew CarenD2D1Layer();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLayer, Param_Out_Layer));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1LinearGradientBrush que contém as GradientStops especificadas e tem a opacidade de transformação e base especificada. 
/// </summary>
/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateLinearGradientBrush(
CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* pLinearGradientProps = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1LinearGradientBrush* pOutLinearGradientBrush = NULL;

	//Converte as estruturas.
	pLinearGradientProps = Util.ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesLinerarGradientBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLinearGradientBrush(pLinearGradientProps, pBrushProps, pGradientStopCollection, &pOutLinearGradientBrush);

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

	//Cria a interface de saida.
	Param_Out_LinearGradientBrush = gcnew CarenD2D1LinearGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLinearGradientBrush, Param_Out_LinearGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pLinearGradientProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1LinearGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
/// </summary>
/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateLinearGradientBrush(
CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* pLinearGradientProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1LinearGradientBrush* pOutLinearGradientBrush = NULL;

	//Converte a estrutura.
	pLinearGradientProps = Util.ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesLinerarGradientBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLinearGradientBrush(*pLinearGradientProps, pGradientStopCollection, &pOutLinearGradientBrush);

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

	//Cria a interface de saida.
	Param_Out_LinearGradientBrush = gcnew CarenD2D1LinearGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLinearGradientBrush, Param_Out_LinearGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pLinearGradientProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Crie uma malha(Mesh) que usa triângulos para descrever uma forma. 
/// </summary>
/// <param name="Param_Out_Mesh">Retorna uma interface ICarenD2D1Mesh que contém um ponteiro para a nova malha(Mesh).</param>
CarenResult CarenD2D1RenderTarget::CreateMesh([Out] ICarenD2D1Mesh^% Param_Out_Mesh)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Mesh* pOutMesh = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMesh(&pOutMesh);

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

	//Cria a interface de saida.
	Param_Out_Mesh = gcnew CarenD2D1Mesh();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutMesh, Param_Out_Mesh));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados e tem a opacidade de transformação e base especificada.
/// </summary>
/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel(Brush).</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateRadialGradientBrush(
CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* pRadialGradientProps = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1RadialGradientBrush* pOutRadialGradientBrush = NULL;

	//Converte as estruturas.
	pRadialGradientProps = Util.ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesRadialGradientBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRadialGradientBrush(pRadialGradientProps, pBrushProps, pGradientStopCollection, &pOutRadialGradientBrush);

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

	//Cria a interface de saida.
	Param_Out_RadialGradientBrush = gcnew CarenD2D1RadialGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRadialGradientBrush, Param_Out_RadialGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRadialGradientProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
/// </summary>
/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateRadialGradientBrush(
CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* pRadialGradientProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1RadialGradientBrush* pOutRadialGradientBrush = NULL;

	//Converte a estrutura.
	pRadialGradientProps = Util.ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesRadialGradientBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRadialGradientBrush(*pRadialGradientProps, pGradientStopCollection, &pOutRadialGradientBrush);

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

	//Cria a interface de saida.
	Param_Out_RadialGradientBrush = gcnew CarenD2D1RadialGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRadialGradientBrush, Param_Out_RadialGradientBrush));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1Bitmap cujos dados são compartilhados com outro recurso. 
/// </summary>
/// <param name="Param_Riid">O ID de interface do objeto que fornece os dados de origem.</param>
/// <param name="Param_InterfaceDados">Uma ICarenD2D1Bitmap, ICarenDXGISurface ou uma ICarenWICBitmapLock que contém os dados para compartilhar com o novo ICarenD2D1Bitmap. </param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. A DXGI_FORMAT parte do formato pixel deve corresponder à DXGI_FORMAT de dados ou o método falhará, mas os modos alfa 
/// não precisam coincidir. Para evitar uma incompatibilidade, você pode passar NULO ou o valor obtido da função auxiliar D2D1::PixelFormat. As configurações de DPI não têm que coincidir com as dos dados. 
/// Se o dpiX e o dpiY forem 0,0f, o DPI do alvo de renderização será usado.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1RenderTarget::CreateSharedBitmap(
String^ Param_Riid,
ICaren^ Param_InterfaceDados,
CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID Riid = GUID_NULL;
	PVOID pInterfaceDados = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL; //Poder ser NULO.
	ID2D1Bitmap* pOutBitmap = NULL;

	//Cria e converte os dados necessários.
	Riid = Util.CreateGuidFromString(Param_Riid);
	pBitmapProps = ObjetoGerenciadoValido(Param_PropriedadesBitmap) ? Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap) : NULL;

	//Recupera o ponteiro para a interface de dados.
	Resultado = RecuperarPonteiroCaren(Param_InterfaceDados, &pInterfaceDados);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSharedBitmap(Riid, pInterfaceDados, pBitmapProps, &pOutBitmap);

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

	//Cria a interface de saida.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutBitmap, Param_Out_Bitmap));

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor e a opacidade especificados.
/// </summary>
/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel.</param>
/// <param name="Param_PropriedadesBrush">A opacidade base do pincel.</param>
/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateSolidColorBrush(
CA_D2D1_COLOR_F^ Param_Cor,
CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1SolidColorBrush* pOutSolidColorBrush = NULL;

	//Converte as estruturas.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Cor);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSolidColorBrush(pColorF, pBrushProps, &pOutSolidColorBrush);

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

	//Cria a interface de saida.
	Param_Out_SolidColorBrush = gcnew CarenD2D1SolidColorBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutSolidColorBrush, Param_Out_SolidColorBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pColorF);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor especificada e uma opacidade base de 1.0f.
/// </summary>
/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel(Brush).</param>
/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1RenderTarget::CreateSolidColorBrush(
CA_D2D1_COLOR_F^ Param_Cor,
[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;
	ID2D1SolidColorBrush* pOutSolidColorBrush = NULL;

	//Converte a estrutura.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Cor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSolidColorBrush(*pColorF, &pOutSolidColorBrush);

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

	//Cria a interface de saida.
	Param_Out_SolidColorBrush = gcnew CarenD2D1SolidColorBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutSolidColorBrush, Param_Out_SolidColorBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pColorF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o bitmap especificado depois de dimensioná-lo para o tamanho do retângulo especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawBitmap) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw 
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Bitmap">O bitmap para renderizar.</param>
/// <param name="Param_RetanguloDestino">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do alvo de renderização, da área para a qual o bitmap é desenhado. 
/// Se o retângulo não for bem ordenado, nada é desenhado, mas o alvo de renderização não entra em um estado de erro.</param>
/// <param name="Param_Opacidade">Um valor entre 0,0f e 1,0f, inclusive, que especifica um valor de opacidade para aplicar ao bitmap; este valor é multiplicado em relação aos valores alfa do 
/// conteúdo do bitmap.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado se o bitmap for dimensionado ou girado pela operação de desenho.</param>
/// <param name="Param_RetanguloOrigem">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do bitmap, da área dentro do bitmap para desenhar.</param>
CarenResult CarenD2D1RenderTarget::DrawBitmap(
ICarenD2D1Bitmap^ Param_Bitmap,
CA_D2D1_RECT_F^ Param_RetanguloDestino,
float Param_Opacidade,
CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode,
CA_D2D1_RECT_F^ Param_RetanguloOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmapRender = NULL;
	D2D1_RECT_F* pRectDestinoF = NULL;
	D2D1_RECT_F* pRectOrigemF = NULL;
	D2D1_BITMAP_INTERPOLATION_MODE BitmapInterpolationMode = static_cast<D2D1_BITMAP_INTERPOLATION_MODE>(Param_InterpolationMode);

	//Recupera o ponteiro para o bitmap
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmapRender);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pRectDestinoF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pRectOrigemF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawBitmap(pBitmapRender, pRectDestinoF, Param_Opacidade, BitmapInterpolationMode, pRectOrigemF);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRectDestinoF);
	DeletarEstruturaSafe(&pRectOrigemF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) da elipse especificada usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Ellipse">A posição e o raio da elipse para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno da elipse.</param>
/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão 
/// para 1.0f. O golpe está centrado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do Stroke para aplicar ao contorno(Outline) da elipse, ou NULO para pintar um traço sólido.</param>
CarenResult CarenD2D1RenderTarget::DrawEllipse(
CA_D2D1_ELLIPSE^ Param_Ellipse,
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ELLIPSE* pEllipse = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL; //Pode ser NULO.

	//Recupera o ponteiro para o Brush.
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Converte a estrutura.
	pEllipse = Util.ConverterD2D1_ELLIPSEManagedToUnmanaged(Param_Ellipse);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawEllipse(pEllipse, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pEllipse);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno da geometria especificada usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Geometria">A geometria para desenhar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o traço(Stroke) da geometria.</param>
/// <param name="Param_StrokeWidth">A largura do traçado, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão
/// para 1.0f. O golpe está centrado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado(Stroke) para aplicar ao contorno(Outline) da geometria, ou NULO para pintar um traço(Stroke) sólido.</param>
CarenResult CarenD2D1RenderTarget::DrawGeometry(
ICarenD2D1Geometry^ Param_Geometria,
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometryRender = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a gemetria.
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pGeometryRender);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Brush.
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGeometry(pGeometryRender, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha os glifos(Glyph) especificados.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGlyphRun) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_BaseLineOrigin">A origem, em pixels independentes de dispositivos, da linha de base dos glifos(Glyph).</param>
/// <param name="Param_GlyphRun">Os glifos(Glyph) para renderizar.</param>
/// <param name="Param_ForegroundBrush">O pincel(Brush) usado para pintar os glifos(Glyph) especificados.</param>
/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
CarenResult CarenD2D1RenderTarget::DrawGlyphRun(
CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
ICarenD2D1Brush^ Param_ForegroundBrush,
CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	DWRITE_GLYPH_RUN* pGlyphRun = NULL;
	ID2D1Brush* pBrush = NULL;
	DWRITE_MEASURING_MODE DWriteMeasuringMode = static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode);

	//Converte as estruturas.
	pPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaseLineOrigin);
	pGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlyphRun);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_ForegroundBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGlyphRun(*pPoint, pGlyphRun, pBrush, DWriteMeasuringMode);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as matrizes.
	DeletarEstruturaSafe(&pPoint);
	if (ObjetoValido(pGlyphRun))
	{
		//Libera as matrizes internas da estrutura.
		DeletarMatrizUnidimensionalSafe(&pGlyphRun->glyphIndices);
		DeletarMatrizUnidimensionalSafe(&pGlyphRun->glyphAdvances);
		DeletarMatrizEstruturasSafe(&pGlyphRun->glyphOffsets);
	}
	DeletarEstruturaSafe(&pGlyphRun);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha uma linha entre os pontos especificados usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawLine) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Point0">O ponto de partida da linha, em pixels independentes de dispositivos.</param>
/// <param name="Param_Point1">O ponto final da linha, em pixels independentes de dispositivos.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o traço da linha.</param>
/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo.O valor deve ser maior ou igual a 0, 0f.Se esse parâmetro não for especificado, o padrão será 1.0f. 
/// O Stroke é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo de Stroke para pintar, ou NULO para pintar uma linha sólida.</param>
CarenResult CarenD2D1RenderTarget::DrawLine(
CA_D2D1_POINT_2F^ Param_Point0,
CA_D2D1_POINT_2F^ Param_Point1,
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint0 = NULL;
	D2D1_POINT_2F* pPoint1 = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte as estruturas.
	pPoint0 = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point0);
	pPoint1 = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point1);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawLine(*pPoint0, *pPoint1, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPoint0);
	DeletarEstruturaSafe(&pPoint1);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) de um retângulo que tem as dimensões especificadas e o estilo de traçado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">As dimensões do retângulo para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o curso do retângulo.</param>
/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, 
/// o padrão será 1.0f. O traço(Stroke) é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do traço(Stroke) para pintar ou NULO para pintar um traçado sólido.</param>
CarenResult CarenD2D1RenderTarget::DrawRectangle(
CA_D2D1_RECT_F^ Param_Rect,
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pRectF = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte a estrutura.
	pRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_Rect);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawRectangle(pRectF, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) do retângulo arredondado especificado usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_RoundedRect">As dimensões do retângulo arredondado para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno do retângulo arredondado.</param>
/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, o padrão 
/// será 1.0f. O traço(Stroke) é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do traçado do retângulo arredondado, ou NULO para pintar um traço sólido. O valor padrão é NULO.</param>
CarenResult CarenD2D1RenderTarget::DrawRoundedRectangle(
CA_D2D1_ROUNDED_RECT^ Param_RoundedRect,
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ROUNDED_RECT* pRoundedRect = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte a estrutura.
	pRoundedRect = Util.ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(Param_RoundedRect);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawRoundedRectangle(pRoundedRect, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRoundedRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o texto especificado usando as informações de formato fornecidas por um objeto ICarenDWriteTextFormat. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawText) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Texto">Uma string de caracteres Unicode para desenhar.</param>
/// <param name="Param_TamanhoTexto">O número de caracteres em (Param_Texto).</param>
/// <param name="Param_TextFormat">Uma interface(ICarenDWriteTextFormat) que descreve a formatação de detalhes do texto para desenhar, como a fonte, o tamanho da fonte e a direção do fluxo.</param>
/// <param name="Param_LayoutRect">O tamanho e a posição da área em que o texto é desenhado.</param>
/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar o texto.</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
CarenResult CarenD2D1RenderTarget::DrawText(
String^ Param_Texto,
UInt32 Param_TamanhoTexto,
ICaren^ Param_TextFormat,
CA_D2D1_RECT_F^ Param_LayoutRect,
ICarenD2D1Brush^ Param_DefaultFillBrush,
CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes,
CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWCHAR pTexto = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	D2D1_RECT_F* pLayoutRectF = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_DRAW_TEXT_OPTIONS DrawTextOptions = static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes);
	DWRITE_MEASURING_MODE MeasuringMode = static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode);

	//Verifica se a string é valida
	if (!ObjetoGerenciadoValido(Param_Texto))
		throw gcnew NullReferenceException("O texto a ser desenhado não pode ser NULO!");

	//Converte a string para wchar
	pTexto = Util.ConverterStringToWCHAR(Param_Texto);

	//Recupera o ponteiro para a interface de formato do texto.
	Resultado = RecuperarPonteiroCaren(Param_TextFormat, &pTextFormat);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_DefaultFillBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pLayoutRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_LayoutRect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawText(pTexto, Param_TamanhoTexto, pTextFormat, pLayoutRectF, pBrush, DrawTextOptions, MeasuringMode);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	
Done:;
	//Libera a memória para os dados.
	DeletarTextoAlocadoSafe(&pTexto);
	DeletarEstruturaSafe(&pLayoutRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o texto formatado descrito pelo objeto ICarenDWriteTextLayout especificado.
/// Ao desenhar o mesmo texto repetidamente, o uso do método DrawTextLayout é mais eficiente do que usar o método DrawText porque o texto não precisa ser formatado e o layout processado a cada chamada.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawTextLayout) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Origem">O ponto, descrito em pixels independentes do dispositivo, no qual o canto superior esquerdo do texto descrito pelo (Param_TextLayout) é desenhado.</param>
/// <param name="Param_TextLayout">Uma interface(ICarenDWriteTextLayout) com o texto formatado para desenhar. Quaisquer efeitos de desenho que não herdem do ID2D1Resource são ignorados. Se houver 
/// efeitos de desenho que herdam do ICarenD2D1Resource que não são pincéis, este método falhará e o alvo de renderização é colocado em um estado de erro.</param>
/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar qualquer texto no (Param_TextLayout) que ainda não tenha um pincel associado a ele como efeito de desenho (especificado pelo 
/// método ICarenDWriteTextLayout::SetDrawingEffect).</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
CarenResult CarenD2D1RenderTarget::DrawTextLayout(
CA_D2D1_POINT_2F^ Param_Origem,
ICaren^ Param_TextLayout,
ICarenD2D1Brush^ Param_DefaultFillBrush,
CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPointOrigem = NULL;
	IDWriteTextLayout* pDwriterTextLayout = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_DRAW_TEXT_OPTIONS DrawTextOptions = static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes);

	//Recupera o ponteiro para a interface de formato do texto.
	Resultado = RecuperarPonteiroCaren(Param_TextLayout, &pDwriterTextLayout);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_DefaultFillBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pPointOrigem = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Origem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawTextLayout(*pPointOrigem, pDwriterTextLayout, pBrush, DrawTextOptions);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pPointOrigem);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Termina as operações de desenho no alvo de renderização e indica o estado de erro atual e as tags associadas. 
/// </summary>
/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
CarenResult CarenD2D1RenderTarget::EndDraw(
[Out] UInt64% Param_Out_Tag1,
[Out] UInt64% Param_Out_Tag2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 OutTag1 = 0;
	UINT64 OutTag2 = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndDraw(&OutTag1, &OutTag2);

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

	//Define os valores nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da elipse especificada.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Ellipse">A posição e o raio, em pixels independentes do dispositivo, da elipse para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior da elipse.</param>
CarenResult CarenD2D1RenderTarget::FillEllipse(
CA_D2D1_ELLIPSE^ Param_Ellipse,
ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ELLIPSE* pEllipse = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pEllipse = Util.ConverterD2D1_ELLIPSEManagedToUnmanaged(Param_Ellipse);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillEllipse(pEllipse, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pEllipse);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da geometria especificada.
/// Se o parâmetro (Param_OpacityBrush) não for NULO, o valor alfa de cada pixel da opacidade mapeadaBrush é usado para determinar a opacidade resultante de cada pixel correspondente da geometria. 
/// Apenas o valor alfa de cada cor no Brush é usado para este processamento; todas as outras informações de cores são ignoradas.
/// O valor alfa especificado pelo Brush é multiplicado pelo valor alfa da geometria após a geometria ter sido pintada pelo Brush.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Geometria">A geometria para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o interior da geometria.</param>
/// <param name="Param_OpacityBrush">A máscara de opacidade para aplicar à geometria, ou NULO para nenhuma máscara de opacidade. Se uma máscara de opacidade (o parâmetro Param_OpacityBrush) for especificada, 
/// o (Param_Brush) deve ser um ICarenD2D1BitmapBrush que tem seus modos x e y-extend definidos para D2D1_EXTEND_MODE_CLAMP.</param>
CarenResult CarenD2D1RenderTarget::FillGeometry(
ICarenD2D1Geometry^ Param_Geometria,
ICarenD2D1Brush^ Param_Brush,
ICarenD2D1Brush^ Param_OpacityBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Geometry* pGeometry = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1Brush* pOpacityBrush = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface de Geometria.
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pGeometry);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Verifica se forneceu o Brush de opacidade
	if (ObjetoGerenciadoValido(Param_OpacityBrush))
	{
		//Recupera o ponteiro para a interface do Brush de opacidade.
		RecuperarPonteiroCaren(Param_OpacityBrush, &pOpacityBrush);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillGeometry(pGeometry, pBrush, pOpacityBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da malha especificada.
/// O modo antialias atual do alvo de renderização deve ser D2D1_ANTIALIAS_MODE_ALIASED quando FillMesh é chamado. Para alterar o modo antialias do alvo de renderização, use o método SetAntialiasMode.
/// FillMesh não espera uma ordem de enrolamento específica para os triângulos no ID2D1Mesh; tanto no sentido horário quanto no sentido anti-horário funcionará.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillMesh) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Mesh">A malha para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar a malha.</param>
CarenResult CarenD2D1RenderTarget::FillMesh(
ICarenD2D1Mesh^ Param_Mesh,
ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Mesh* pMesh = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Mesh
	Resultado = RecuperarPonteiroCaren(Param_Mesh, &pMesh);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillMesh(pMesh, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Aplica a máscara de opacidade descrita pelo bitmap especificado em um pincel e usa esse pincel para pintar uma região do alvo de renderização.
/// Para que este método funcione corretamente, o alvo de renderização deve estar usando o modo D2D1_ANTIALIAS_MODE_ALIASED antialiasing. Você pode definir o modo antialiasing chamando o método 
/// ICarenD2D1RenderTarget::SetAntialiasMode método.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillOpacityMask) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_OpacityMask">A máscara de opacidade para aplicar no pincel. O valor alfa de cada pixel na região especificado pelo (Param_RetanguloOrigem) é multiplicado com o valor alfa do 
/// Brush após o pincel(Brush) ter sido mapeado para a área definida pelo (Param_RetanguloDestino).</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar a região do alvo de render especificado pelo (Param_RetanguloDestino).</param>
/// <param name="Param_Content">O tipo de conteúdo que a máscara de opacidade contém. O valor é usado para determinar o espaço de cor no qual a máscara de opacidade é misturada.
/// A partir do Windows 8, o D2D1_OPACITY_MASK_CONTENT não é necessário. Consulte o método ICarenD2D1DeviceContext::FillOpacityMask, que não tem parâmetro D2D1_OPACITY_MASK_CONTENT.</param>
/// <param name="Param_RetanguloDestino">A região do alvo de renderização para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_RetanguloOrigem">A região do bitmap para usar como máscara de opacidade, em pixels independentes de dispositivos.</param>
CarenResult CarenD2D1RenderTarget::FillOpacityMask(
ICarenD2D1Bitmap^ Param_OpacityMask,
ICarenD2D1Brush^ Param_Brush,
CA_D2D1_OPACITY_MASK_CONTENT Param_Content,
CA_D2D1_RECT_F^ Param_RetanguloDestino,
CA_D2D1_RECT_F^ Param_RetanguloOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pOpacityMaskBitmap = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_OPACITY_MASK_CONTENT OpacityMask = static_cast<D2D1_OPACITY_MASK_CONTENT>(Param_Content);
	D2D1_RECT_F* pRectDestinoF = NULL;
	D2D1_RECT_F* pRectOrigemF = NULL;

	//Recupera o ponteiro para a interface do Opacity Mask
	Resultado = RecuperarPonteiroCaren(Param_OpacityMask, &pOpacityMaskBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pRectDestinoF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pRectOrigemF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillOpacityMask(pOpacityMaskBitmap, pBrush, OpacityMask, pRectDestinoF, pRectOrigemF);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRectDestinoF);
	DeletarEstruturaSafe(&pRectOrigemF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior do retângulo especificado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">A dimensão do retângulo para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo.</param>
CarenResult CarenD2D1RenderTarget::FillRectangle(
CA_D2D1_RECT_F^ Param_Rect,
ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pRectF= NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_Rect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillRectangle(pRectF, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior do retângulo arredondado especificado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">As dimensões do retângulo arredondado para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo arredondado.</param>
CarenResult CarenD2D1RenderTarget::FillRoundedRectangle(
CA_D2D1_ROUNDED_RECT^ Param_Rect,
ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ROUNDED_RECT* pRoundedRectF = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pRoundedRectF = Util.ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(Param_Rect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillRoundedRectangle(pRoundedRectF, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRoundedRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Executa todos os comandos de desenho pendentes.
/// Este comando não libera o contexto do dispositivo Direct3D que está associado ao alvo de renderização.
/// Chamar este método redefine o estado de erro do alvo de renderização.
/// Se o método for bem sucedido, ele retorna SS_OK. Caso contrário, ele retorna um código de erro HRESULT e define Tag1 e Tag2 para as tags que estavam ativas quando o erro ocorreu. Se não ocorreu nenhum erro, 
/// este método define o estado de Tags de erro (0,0).
/// </summary>
/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
CarenResult CarenD2D1RenderTarget::Flush(
[Out] UInt64% Param_Out_Tag1,
[Out] UInt64% Param_Out_Tag2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 OutTag1 = 0;
	UINT64 OutTag2 = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Flush(&OutTag1, &OutTag2);

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

	//Define os valores nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o modo antialiasing atual para operações de desenho sem texto. 
/// </summary>
/// <param name="Param_Out_AntialiasMode">Retorna o modo antialiasing atual para operações de desenho sem texto.</param>
void CarenD2D1RenderTarget::GetAntialiasMode([Out] CA_D2D1_ANTIALIAS_MODE% Param_Out_AntialiasMode)
{
	//Variaveis a serem utilizadas.
	D2D1_ANTIALIAS_MODE OutAliasMode;

	//Chama o método para realizar a operação.
	OutAliasMode = PonteiroTrabalho->GetAntialiasMode();

	//Define no parametro de saida.
	Param_Out_AntialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(OutAliasMode);
}

/// <summary>
/// Retorne os pontos do alvo de renderização por polegada (DPI). 
/// </summary>
/// <param name="Param_Out_DpiX">Retorna o DPI horizontal do alvo de renderização.</param>
/// <param name="Param_Out_DpiY">Retorna o DPI vertical do alvo de renderização. </param>
void CarenD2D1RenderTarget::GetDpi(
[Out] float% Param_Out_DpiX,
[Out] float% Param_Out_DpiY)
{
	//Variaveis a serem utilizadas.
	FLOAT OutDpiX;
	FLOAT OutDpiY;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDpi(&OutDpiX, &OutDpiY);

	//Define nos parametros de saida.
	Param_Out_DpiX = OutDpiX;
	Param_Out_DpiY = OutDpiY;
}

/// <summary>
/// Obtém o tamanho máximo, em unidades dependentes de dispositivos (pixels), de qualquer dimensão de bitmap suportada pelo alvo de renderização.
/// Este método retorna o tamanho máximo da textura do dispositivo Direct3D.
/// O renderizador de software e os dispositivos WARP retornam o valor de 16 megapixels (16* 1024 * 1024). Você pode criar uma textura Direct2D que é deste tamanho, mas não uma textura Direct3D que 
/// é deste tamanho.
/// </summary>
/// <param name="Param_Out_MaximumSize">Retorna o tamanho máximo, em pixels, de qualquer dimensão de bitmap suportada pelo alvo de renderização.</param>
void CarenD2D1RenderTarget::GetMaximumBitmapSize([Out] UInt32% Param_Out_MaximumSize)
{
	//Chama o método para realizar a operação.
	Param_Out_MaximumSize = PonteiroTrabalho->GetMaximumBitmapSize();
}

/// <summary>
/// Recupera o formato de pixel e o modo alfa do alvo de renderização. 
/// </summary>
/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do alvo de renderização.</param>
void CarenD2D1RenderTarget::GetPixelFormat([Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_PIXEL_FORMAT OutPixelFormat;

	//Chama o método para realizar a operação.
	OutPixelFormat = PonteiroTrabalho->GetPixelFormat();

	//Converte e define no parametro de saida.
	Param_Out_PixelFormat = Util.ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&OutPixelFormat);
}

/// <summary>
/// Retorna o tamanho do alvo de renderização em pixels do dispositivo. 
/// </summary>
/// <param name="Param_Out_PixelSize">Retorna tamanho do alvo de renderização em pixels do dispositivo.</param>
void CarenD2D1RenderTarget::GetPixelSize([Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U OutSizeU;

	//Chama o método para realizar a operação.
	OutSizeU = PonteiroTrabalho->GetPixelSize();

	//Converte e define no parametro de saida.
	Param_Out_PixelSize = Util.ConverterD2D1_SIZE_UUnmanagedToManaged(&OutSizeU);
}

/// <summary>
/// Retorna o tamanho do alvo de renderização em pixels independentes do dispositivo.
/// </summary>
/// <param name="Param_Out_Size">Retorna tamanho atual do alvo de renderização em pixels independentes do dispositivo.</param>
void CarenD2D1RenderTarget::GetSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F OutSizeF;

	//Chama o método para realizar a operação.
	OutSizeF = PonteiroTrabalho->GetSize();

	//Converte e define no parametro de saida.
	Param_Out_Size = Util.ConverterD2D1_SIZE_FUnmanagedToManaged(&OutSizeF);
}

/// <summary>
/// Obtém o rótulo(Tags) para operações de desenho subsequentes. 
/// </summary>
/// <param name="Param_Out_Tag1">Retorna o primeiro rótulo para operações de desenho subsequentes.</param>
/// <param name="Param_Out_Tag2">Retorna o segundo rótulo para operações de desenho subsequentes.</param>
void CarenD2D1RenderTarget::GetTags(
[Out] UInt64% Param_Out_Tag1,
[Out] UInt64% Param_Out_Tag2)
{
	//Variaveis a serem utilizadas.
	UINT64 OutTag1;
	UINT64 OutTag2;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTags(&OutTag1, &OutTag2);

	//Define nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;
}

/// <summary>
/// Obtém o modo antialiasing atual para operações de desenho de texto e glifo(Glyph). 
/// </summary>
/// <param name="Param_Out_TextAntialiasMode">Retorna o modo antialiasing atual para operações de desenho de texto e glifo(Glyph).</param>
void CarenD2D1RenderTarget::GetTextAntialiasMode([Out] CA_D2D1_TEXT_ANTIALIAS_MODE% Param_Out_TextAntialiasMode)
{
	//Variaveis a serem utilizadas.
	D2D1_TEXT_ANTIALIAS_MODE OutTextAliasMode;

	//Chama o método para realizar a operação.
	OutTextAliasMode = PonteiroTrabalho->GetTextAntialiasMode();

	//Converte e define no parametro de saida.
	Param_Out_TextAntialiasMode = static_cast<CA_D2D1_TEXT_ANTIALIAS_MODE>(OutTextAliasMode);
}

/// <summary>
/// Recupera as opções de renderização de texto atual do alvo. 
/// </summary>
/// <param name="Param_Out_TextRenderingParams">Retorna a interface (IDWriteRenderingParams) que contém um ponteiro para as opções de renderização de texto atuais do destino. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1RenderTarget::GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams)
{
	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pDWriteRendParams = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTextRenderingParams(&pDWriteRendParams);

	//Define na interface de destino no parametro.
	Param_Out_TextRenderingParams->AdicionarPonteiro(pDWriteRendParams);
}

/// <summary>
/// Obtém a transformação atual do alvo render. 
/// </summary>
/// <param name="Param_Out_Transform">Retorna a transformação atual do alvo de renderização.</param>
void CarenD2D1RenderTarget::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F OutMatrix = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTransform(&OutMatrix);

	//Converte e define no parametro de saida.
	Param_Out_Transform = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutMatrix);
}

/// <summary>
/// Indica se o alvo de renderização suporta as propriedades especificadas.
/// Este método não avalia as configurações de DPI especificadas pelo parâmetro (Param_ProppriedadesRenderTarget).
/// </summary>
/// <param name="Param_ProppriedadesRenderTarget">As propriedades de destino de renderização para testar.</param>
/// <param name="Param_Out_Suporta">Retorna um valor Booleano TRUE se as propriedades de destino de renderização especificadas forem suportadas por este alvo de renderização; caso contrário, FALSO.</param>
void CarenD2D1RenderTarget::IsSupported(
CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_ProppriedadesRenderTarget,
[Out] Boolean% Param_Out_Suporta)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDER_TARGET_PROPERTIES *pRenderTargetProps = NULL;
	BOOL IsSuported = FALSE;

	//Converte a estrutura.
	pRenderTargetProps = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_ProppriedadesRenderTarget);

	//Chama o método para realizar a operação.
	IsSuported = PonteiroTrabalho->IsSupported(pRenderTargetProps);

	//Define no parametro de saida.
	Param_Out_Suporta = IsSuported ? true : false;

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRenderTargetProps);
}

/// <summary>
/// Remove o último clipe alinhado ao eixo do alvo de renderização. Depois que este método é chamado, o clipe não é mais aplicado às operações de desenho subsequentes.
/// PopAxisAlignedClip deve ser chamado uma vez para cada chamada para PushAxisAlignedClip.
/// Um par PushAxisAlignedClip/PopAxisAlignedClip pode ocorrer ao redor ou dentro de um par PushLayer/PopLayer, mas pode não se sobrepor. Por exemplo, uma sequência PushAxisAlignedClip, PushLayer, PopLayer, 
/// PopAxisAlignedClip é válida, mas uma sequência PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer não é.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
void CarenD2D1RenderTarget::PopAxisAlignedClip()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->PopAxisAlignedClip();
}

/// <summary>
/// Interrompe o redirecionamento das operações de desenho para a camada especificada pela última chamada do PushLayer.
/// Um PopLayer deve corresponder a uma chamada pushlayer anterior.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
void CarenD2D1RenderTarget::PopLayer()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->PopLayer();
}

/// <summary>
/// Especifica um retângulo ao qual todas as operações de desenho subsequentes são cortadas.
/// O PushAxisAlignedClip e o PopAxisAlignedClip devem coincidir. Caso contrário, o estado de erro está definido. Para que o alvo de renderização continue recebendo novos comandos, você pode chamar 
/// Flush para limpar o erro.
/// Um par PushAxisAlignedClip e PopAxisAlignedClip pode ocorrer em torno ou dentro de um PushLayer e PopLayer, mas não pode se sobrepor. Por exemplo, a sequência de PushAxisAlignedClip, PushLayer, 
/// PopLayer, PopAxisAlignedClip é válida, mas a sequência de PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer é inválida.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_ClipRect">O tamanho e a posição da área de recorte, em pixels independentes do dispositivo.</param>
/// <param name="Param_AntialiasMode">O modo antialiasing que é usado para desenhar as bordas das retagens de clipe que têm limites de subpixel, e para misturar o clipe com o conteúdo da cena. A mistura 
/// é realizada uma vez quando o método PopAxisAlignedClip é chamado, e não se aplica a cada primitivo dentro da camada.</param>
void CarenD2D1RenderTarget::PushAxisAlignedClip(
CA_D2D1_RECT_F^ Param_ClipRect,
CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pClipRect = NULL;
	D2D1_ANTIALIAS_MODE AliasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_AntialiasMode);

	//Converte a estrutura.
	pClipRect = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_ClipRect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PushAxisAlignedClip(pClipRect,AliasMode);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pClipRect);
}

/// <summary>
/// Adicione a camada especificada ao destino renderização para que ela receba todas as operações de desenho subsequentes até que o PopLayer seja chamado. 
/// O método PushLayer permite que um chamador comece a redirecionar a renderização para uma camada. Todas as operações de renderização são válidas em uma camada. A localização da camada é afetada 
/// pela transformação mundial definida na meta de renderização.
/// Cada PushLayer deve ter uma chamada PopLayer correspondente. Se houver mais chamadas do PopLayer do que chamadas PushLayer, o alvo de renderização será colocado em um estado de erro. Se flush 
/// for chamado antes de todas as camadas pendentes serem estouradas, o alvo de renderização será colocado em um estado de erro e um erro será retornado. O estado de erro pode ser liberado por uma chamada para EndDraw.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_ParametrosLayer">Os limites de conteúdo, máscara geométrica, opacidade, máscara de opções de opções de opções antialiasing para a camada.</param>
/// <param name="Param_Layer">A camada que recebe operações de desenho subsequentes. Começando pelo Windows 8, este parâmetro é opcional. Se uma camada não for especificada, o Direct2D gerencia 
/// automaticamente o recurso de camada.</param>
void CarenD2D1RenderTarget::PushLayer(
CA_D2D1_LAYER_PARAMETERS^ Param_ParametrosLayer,
ICarenD2D1Layer^ Param_Layer)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LAYER_PARAMETERS* pLayerParams = NULL;
	ID2D1Layer* pLayer = NULL; //Pode ser NULO.

	//Converte a estrutura.
	pLayerParams = Util.ConverterD2D1_LAYER_PARAMETERSManagedToUnmanaged(Param_ParametrosLayer);

	//Verifica se forneceu a camada
	if (ObjetoGerenciadoValido(Param_Layer))
	{
		//Recupera o ponteiro para a interface da Layer
		RecuperarPonteiroCaren(Param_Layer, &pLayer);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PushLayer(pLayerParams, pLayer);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pLayerParams);
}

/// <summary>
/// Define o estado de desenho do alvo de renderização ao do ID2D1DrawingStateBlock especificado.
/// </summary>
/// <param name="Param_DrawingStateBlock">O novo estado de desenho do alvo render.</param>
CarenResult CarenD2D1RenderTarget::RestoreDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock* pStateBlock = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_DrawingStateBlock, &pStateBlock);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RestoreDrawingState(pStateBlock);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Salva o estado de desenho atual para o ID2D1DrawingStateBlock especificado. 
/// </summary>
/// <param name="Param_DrawingStateBlock">Retorna uma interface para o estado de desenho atual do alvo de renderização. Este parâmetro deve ser inicializado antes de passá-lo para o método.</param>
CarenResult CarenD2D1RenderTarget::SaveDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock* pStateBlock = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_DrawingStateBlock, &pStateBlock);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SaveDrawingState(pStateBlock);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o modo de antialiasing do alvo de renderização. O modo antialiasing aplica-se a todas as operações de desenho subsequentes, excluindo as operações de desenho de texto e glifo(Glyph). 
/// Para especificar o modo antialiasing para operações de texto e glifos(Glyph), use o método SetTextAntialiasMode.
/// </summary>
/// <param name="Param_AntialiasMode">O modo antialiasing para futuras operações de desenho.</param>
void CarenD2D1RenderTarget::SetAntialiasMode(CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetAntialiasMode(static_cast<D2D1_ANTIALIAS_MODE>(Param_AntialiasMode));
}

/// <summary>
/// Define os pontos por polegada (DPI) do alvo de renderização.
/// Este método especifica o mapeamento do espaço pixel para o espaço independente do dispositivo para o alvo de renderização. Se tanto o DpiX quanto o DpiY forem 0, o DPI do sistema de leitura 
/// de fábrica será escolhido. Se um parâmetro for zero e o outro não especificado, o DPI não será alterado.
/// Para ICarenD2D1HwndRenderTarget, o DPI é padrão para o DPI mais recentemente do sistema de leitura de fábrica. O valor padrão para todas as outras metas de renderização é de 96 DPI.
/// </summary>
/// <param name="Param_DpiX">Um valor maior ou igual a zero que especifica o DPI horizontal do alvo de renderização.</param>
/// <param name="Param_DpiY">Um valor maior ou igual a zero que especifica o DPI vertical do alvo de renderização.</param>
void CarenD2D1RenderTarget::SetDpi(
float Param_DpiX,
float Param_DpiY)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetDpi(Param_DpiX, Param_DpiY);
}

/// <summary>
/// Especifica um rótulo(Tag) para operações de desenho subsequentes.
/// As etiquetas(Tags) especificadas por este método são impressas por mensagens de erro depuração. Se nenhuma tag for definida, o valor padrão de cada tag é 0.
/// </summary>
/// <param name="Param_Tag1">Um rótulo para aplicar às operações de desenho subsequentes.</param>
/// <param name="Param_Tag2">Um rótulo para aplicar às operações de desenho subsequentes.</param>
void CarenD2D1RenderTarget::SetTags(
UInt64 Param_Tag1,
UInt64 Param_Tag2)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTags(Param_Tag1, Param_Tag2);
}

/// <summary>
/// Especifica o modo antialiasing a ser usado para operações subsequentes de desenho de texto e glifo(Glyph). 
/// </summary>
/// <param name="Param_TextAntialiasMode">O modo antialiasing para usar para operações subsequentes de desenho de texto e glifo(Glyph).</param>
void CarenD2D1RenderTarget::SetTextAntialiasMode(CA_D2D1_TEXT_ANTIALIAS_MODE Param_TextAntialiasMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTextAntialiasMode(static_cast<D2D1_TEXT_ANTIALIAS_MODE>(Param_TextAntialiasMode));
}

/// <summary>
/// Especifica as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho de texto e glifo(Glyph).
/// Se as configurações especificadas por textRenderingParams forem incompatíveis com o modo antialiasing de texto do alvo de renderização (especificado por SetTextAntialiasMode), as operações 
/// subsequentes de desenho de texto e glifo(Glyph) falharão e colocarão o alvo de renderização em um estado de erro.
/// </summary>
/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) para as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho 
/// de texto e glifoGlyph); NULO para limpar as opções atuais de renderização de texto.</param>
CarenResult CarenD2D1RenderTarget::SetTextRenderingParams(ICaren^ Param_TextRenderingParams)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pDwriteParams = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_TextRenderingParams, &pDwriteParams);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTextRenderingParams(pDwriteParams);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Aplica a transformação especificada ao alvo de renderização, substituindo a transformação existente. Todas as operações subsequentes de desenho ocorrem no espaço transformado. 
/// </summary>
/// <param name="Param_Transform">A transformação para aplicar ao alvo de renderização.</param>
void CarenD2D1RenderTarget::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrix = NULL;

	//Converte a estrutura.
	pMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTransform(pMatrix);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMatrix);
}


// Métodos da interface proprietária(ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void  CarenD2D1RenderTarget::GetFactory(ICaren^ Param_Out_Factory)
{
	//Variaveis a serem utilizadas.
	ID2D1Factory* pFactory = NULL;

	//Variavel de resultados.
	CarenResult Resultado;

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