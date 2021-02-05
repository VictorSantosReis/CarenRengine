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
#include "CarenWICBitmapFrameEncode.h"

//Destruidor.
CarenWICBitmapFrameEncode::~CarenWICBitmapFrameEncode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapFrameEncode::CarenWICBitmapFrameEncode()
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
CarenResult CarenWICBitmapFrameEncode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICBitmapFrameEncode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapFrameEncode*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICBitmapFrameEncode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapFrameEncode*>(Param_PonteiroNativo);

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
CarenResult CarenWICBitmapFrameEncode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapFrameEncode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapFrameEncode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICBitmapFrameEncode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapFrameEncode::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapFrameEncode::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapFrameEncode::LiberarReferencia()
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
void CarenWICBitmapFrameEncode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICBitmapFrameEncode();
}



// Métodos da interface proprietária(ICarenWICBitmapFrameEncode)


/// <summary>
/// Confirma o frame para a imagem.
/// Depois que o frame Commit for chamado, você não pode usar ou reiniciar o objeto ICarenWICBitmapFrameEncode e quaisquer objetos criados a partir dele.
/// Para finalizar a imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que todos 
/// os frames forem confirmados(Committed). 
/// </summary>
CarenResult CarenWICBitmapFrameEncode::Commit()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Commit();

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
/// Recebe o escritor de consulta de metadados para o frame do codificador. 
/// Se você estiver configurando metadados no frame, você deve fazer isso antes de usar ICarenWICBitmapFrameEncode::WritePixels ou ICarenWICBitmapFrameEncode::WriteSource 
/// para gravar quaisquer pixels de imagem no frame.
/// </summary>
/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados para o 
/// frame do codificador.</param>
CarenResult CarenWICBitmapFrameEncode::GetMetadataQueryWriter(
[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataQueryWriter* pOutMetadataWriter = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataQueryWriter(&pOutMetadataWriter);

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

	//Cria a interface a ser retornada.
	Param_Out_MetadataQueryWriter = gcnew CarenWICMetadataQueryWriter();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutMetadataWriter, Param_Out_MetadataQueryWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o codificador de frames usando as propriedades dadas.
/// Se você não quiser opções de codificação, passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe o ICarenPropertyBag2 fornecido pelo 
/// ICarenWICBitmapEncoder::CreateNewFrame com valores atualizados. Voce pode acessar o GUIDs::GUIDs_WIC_CLSIDs_ENCODIFICADORES para obter uma lista de codificadores suportados.
/// </summary>
/// <param name="Param_OpcoesEncodificacao">O conjunto de propriedades a serem usados para inicialização do ICarenWICBitmapFrameEncode. e você não quiser opções de codificação, 
/// passe NULO para (Param_OpcoesEncodificacao). Caso contrário, passe um ICarenPropertyBag2 fornecido pelo ICarenWICBitmapEncoder::CreateNewFrame com valores 
/// atualizados.</param>
CarenResult CarenWICBitmapFrameEncode::Initialize(ICarenPropertyBag2^ Param_OpcoesEncodificacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IPropertyBag2* pPropertyBag = NULL;

	//Recupera o ponteiro para a bag
	Resultado = RecuperarPonteiroCaren(Param_OpcoesEncodificacao, &pPropertyBag);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(pPropertyBag);

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
/// Define um determinado número de perfis ICarenWICColorContext ao quadro. 
/// </summary>
/// <param name="Param_Quantidade">O número de perfis ICarenWICColorContext a definir na matriz (Param_ColorContexts).</param>
/// <param name="Param_ColorContexts">Uma matriz de interfaces IWICColorContext contendo os perfis de contextos de cores a serem configurados para o frame.</param>
CarenResult CarenWICBitmapFrameEncode::SetColorContexts(
UInt32 Param_Quantidade,
cli::array<ICarenWICColorContext^>^ Param_ColorContexts)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICColorContext** pArrayColorContexts = CriarMatrizPonteiros<IWICColorContext>(Param_Quantidade);

	//Copia os ponteiros para o array nativo.
	Util.CopiarPonteirosGerenciado_ToNativo(pArrayColorContexts, Param_ColorContexts, Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetColorContexts(Param_Quantidade, pArrayColorContexts);

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
	//Libera a memória utilizada pela matriz de ponteiros
	DeletarMatrizPonteirosSafe(&pArrayColorContexts);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o ICarenWICPalette para formatos de pixel indexados. 
/// Este método não falha se chamado em um frame cujo formato de pixel é definido como um formato de pixel não indexado. Se o formato de pixel de destino for um formato não indexado, 
/// a paleta será ignorada. Se você já ligou para ICarenWICBitmapEncoder::SetPalette para definir uma paleta global, este método substitui essa paleta para o frame atual.
/// A paleta deve ser especificada antes da primeira chamada para WritePixels/WriteSource. Isso fará com que o WriteSource use a paleta especificada ao converter a imagem de origem 
/// no formato de pixel do codificador. Se nenhuma paleta for especificada, uma paleta será gerada na primeira chamada para WriteSource.
/// </summary>
/// <param name="Param_Palette">A interface ICarenWICPalette para usar para formatos de pixel indexados. O codificador pode alterar a paleta para refletir os formatos de pixel que 
/// o codificador suporta.</param>
CarenResult CarenWICBitmapFrameEncode::SetPalette(ICarenWICPalette^ Param_Palette)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* pWicPalette = NULL;

	//Recupera o ponteiro para a paleta
	Resultado = RecuperarPonteiroCaren(Param_Palette, &pWicPalette);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPalette(pWicPalette);

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
/// Solicita que o codificador use o formato de pixel especificado.
/// O codificador pode não suportar o formato de pixel solicitado. Caso não, o (Param_Ref_INOUT_GuidFormatoPixel) retorna a correspondência mais próxima no bloco de memória a que 
/// (Param_Ref_INOUT_GuidFormatoPixel) aponta. Se o formato de pixel retornado não corresponder ao formato solicitado, você deve usar um objeto ICarenWICFormatConverter para 
/// converter os dados do pixel.
/// </summary>
/// <param name="Param_Ref_INOUT_GuidFormatoPixel">Na entrada, o GUID de formato de pixel solicitado. Na saída, o GUID do formato de pixel mais próximo suportado pelo codificador; 
/// isso pode ser diferente do formato solicitado. Consulte a estrutura Guids::GUIDs_WIC_NATIVE_PIXEL_FORMATS para obter uma lista de GUIDs com os formatos de pixel suportados pelo WIC.</param>
CarenResult CarenWICBitmapFrameEncode::SetPixelFormat(String^% Param_Ref_INOUT_GuidFormatoPixel)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID InOut = GUID_NULL; //Definido na entrada pelo usuário e na saida pelo método.

	//Converte o guid
	InOut = Util.CreateGuidFromString(Param_Ref_INOUT_GuidFormatoPixel);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPixelFormat(&InOut);

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

	//Define o valor de saida no parametro de saida.
	Param_Ref_INOUT_GuidFormatoPixel = Util.ConverterGuidToString(InOut);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define a resolução física da imagem de saída.
/// O Windows Imaging Component (WIC) não realiza nenhum processamento especial como resultado dos valores de resolução de DPI. Por exemplo, os dados retornados do 
/// ICarenWICBitmapFonte::CopyPixels não é dimensionado pelo DPI. O aplicativo deve lidar com a resolução de DPI.
/// </summary>
/// <param name="Param_DpiX">O valor da resolução Horizontal.</param>
/// <param name="Param_DpiY">O valor da resolução Vertical.</param>
CarenResult CarenWICBitmapFrameEncode::SetResolution(
double Param_DpiX,
double Param_DpiY)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetResolution(Param_DpiX, Param_DpiY);

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
/// Define as dimensões da imagem de saída para o quadro. 
/// </summary>
/// <param name="Param_Width">A Largura da imagem de saída.</param>
/// <param name="Param_Height">A Altura da imagem de saída.</param>
CarenResult CarenWICBitmapFrameEncode::SetSize(
UInt32 Param_Width,
UInt32 Param_Height)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSize(Param_Width, Param_Height);

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
/// Define a miniatura do quadro se suportado pelo codec. 
/// Recomendamos que você ligue para SetThumbnail antes de ligar para WritePixels ou WriteSource. A miniatura não será adicionada ao arquivo codificado se o SetThumbnail for 
/// chamado após uma chamada para WritePixels ou WriteSource.
/// </summary>
/// <param name="Param_Thumbnail">A fonte bitmap para usar como miniatura.</param>
CarenResult CarenWICBitmapFrameEncode::SetThumbnail(ICarenWICBitmapSource^ Param_Thumbnail)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pBitmapSource = NULL;

	//Recupera o ponteiro para a fonte do bitmap.
	Resultado = RecuperarPonteiroCaren(Param_Thumbnail, &pBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetThumbnail(pBitmapSource);

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
/// Copia dados da linha de varredura de um buffer fornecido pelo chamador para o objeto ICarenWICBitmapFrameEncode.
/// Sucessivas chamadas WritePixels são consideradas de acesso sequencial à linha de varredura na imagem de saída.
/// </summary>
/// <param name="Param_QuantidadeLinhas">O número de linhas para codificar.</param>
/// <param name="Param_Stride">O Stride dos pixels de imagem.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer de pixels.</param>
/// <param name="Param_Pixels">Uma interface(ICarenBuffer) para os dados de pixels.</param>
CarenResult CarenWICBitmapFrameEncode::WritePixels(
UInt32 Param_QuantidadeLinhas,
UInt32 Param_Stride,
UInt32 Param_TamanhoBuffer,
ICarenBuffer^ Param_Pixels)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer pPixelsWrite = DefaultGenPointer;

	//Recupera o ponteiro para o buffer de pixels a serem escritos.
	Resultado = Param_Pixels->GetInternalPointer(pPixelsWrite);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WritePixels(Param_QuantidadeLinhas, Param_Stride, Param_TamanhoBuffer, Util.ConverterIntPtrTo<PBYTE>(pPixelsWrite));

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
/// Codifica uma fonte de bitmap. 
/// Se o SetSize não for chamado antes de chamar WriteSource, o tamanho dado no (Param_RetanguloBitmap) será usado se não for NULO. Caso contrário, o tamanho do ICarenWICBitmapSource
///  dado em (Param_BitmapSource) é usado. Se o SetPixelFormat não for chamado antes de chamar WriteSource, o formato de pixel do ICarenWICBitmapSource dado no (Param_BitmapSource) é usado.
/// Se o SetResolution não for chamado antes de chamar WriteSource, o formato pixel do (Param_BitmapSource) será usado.
/// Se o SetPalette não for chamado antes de chamar WriteSource, o formato de pixel alvo será indexado, e o formato de pixel do (Param_BitmapSource) corresponde ao formato 
/// de pixel do quadro do codificador, então o formato de pixel (Param_BitmapSource) é usado.
/// </summary>
/// <param name="Param_BitmapSource">A fonte do bitmap para codificar.</param>
/// <param name="Param_RetanguloBitmap">O retângulo de tamanho da fonte do bitmap.</param>
CarenResult CarenWICBitmapFrameEncode::WriteSource(
ICarenWICBitmapSource^ Param_BitmapSource,
CA_WICRect^ Param_RetanguloBitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource* pBitmapSource = NULL;
	WICRect* pRectBitmap = NULL;

	//Recupera o potneiro para a fonte do bitmap.
	Resultado = RecuperarPonteiroCaren(Param_BitmapSource, &pBitmapSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura
	pRectBitmap = Util.ConverterWICRectManaged_ToUnManaged(Param_RetanguloBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WriteSource(pBitmapSource, pRectBitmap);

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
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pRectBitmap);

	//Retorna o resultado.
	return Resultado;
}