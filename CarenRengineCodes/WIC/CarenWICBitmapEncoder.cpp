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
#include "CarenWICBitmapEncoder.h"

//Destruidor.
CarenWICBitmapEncoder::~CarenWICBitmapEncoder()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapEncoder::CarenWICBitmapEncoder()
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
CarenResult CarenWICBitmapEncoder::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICBitmapEncoder::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapEncoder*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICBitmapEncoder::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapEncoder*>(Param_PonteiroNativo);

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
CarenResult CarenWICBitmapEncoder::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapEncoder::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapEncoder::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICBitmapEncoder::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapEncoder::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapEncoder::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapEncoder::LiberarReferencia()
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
void CarenWICBitmapEncoder::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICBitmapEncoder();
}



// Métodos da interface proprietária(ICarenWICBitmapEncoder)


/// <summary>
/// Confirma todas as alterações para a imagem e fecha o fluxo.
/// Para finalizar uma imagem, tanto o frame Commit quanto o codificador Commit devem ser chamados. No entanto, apenas ligue para o método codificador Commit depois que 
/// todos os frames foram (Committed). Depois que o codificador foi cometido, ele não pode ser reiniciado ou reutilizado com outro fluxo. Uma nova interface de codificador 
/// deve ser criada, por exemplo, com ICarenWICImagingFactory::CreateEncoder. Para que o codificador Comprometa-se a ter sucesso, você deve, no mínimo, chamar 
/// ICarenWICBitmapEncoder::Initialize e ICarenWICBitmapFrameEncode::WriteSource ou ICarenWICBitmapFrameEncode::WritePixels.
/// </summary>
CarenResult CarenWICBitmapEncoder::Commit()
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
/// Cria uma nova instância ICarenWICBitmapFrameEncode. 
/// Para formatos que suportam codificação de vários frames (por exemplo, TIFF, JPEG-XR), você pode trabalhar em apenas um frame por vez. Isso significa que você deve 
/// ligar para o IWICBitmapFrameEncode::Commit antes de chamar o CreateNewFrame novamente.
/// </summary>
/// <param name="Param_Out_FrameEncode">Retorna uma interface(ICarenWICBitmapFrameEncode) que contém um ponteiro para a nova instância do ICarenWICBitmapFrameEncode.</param>
/// <param name="Param_Ref_OpcoesEncodificacao">(Opcional) Recebe as propriedades nomeadas para usar para inicialização subsequente do frame. O usuário deve inicializar a interface se desejar receber um ponteiro para a interface.</param>
CarenResult CarenWICBitmapEncoder::CreateNewFrame(
[Out] ICarenWICBitmapFrameEncode^% Param_Out_FrameEncode,
ICarenPropertyBag2^% Param_Ref_OpcoesEncodificacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapFrameEncode* pOutFrame = NULL;
	IPropertyBag2* pOutOptionsEncode = NULL; //O usuário pode desejar não receber está interface.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateNewFrame(&pOutFrame, Param_Ref_OpcoesEncodificacao == nullptr ? NULL: &pOutOptionsEncode);

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
	Param_Out_FrameEncode = gcnew CarenWICBitmapFrameEncode();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutFrame, Param_Out_FrameEncode);

	//Verifica se solicitou a interface de propriedades também
	if (ObjetoGerenciadoValido(Param_Ref_OpcoesEncodificacao))
	{
		//O usuário que deve inicializar a interface.

		//Define o ponteiro na interface
		Resultado = DefinirPonteiroInterface(pOutOptionsEncode, Param_Ref_OpcoesEncodificacao);
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o formato do recipiente do codificador. 
/// </summary>
/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID do formato de contêiner do codificador.</param>
CarenResult CarenWICBitmapEncoder::GetContainerFormat(
[Out] String^% Param_Out_GuidContainerFormat)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidContainer = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerFormat(&OutGuidContainer);

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

	//Converte o guid para string e define no parametro de saida.
	Param_Out_GuidContainerFormat = Util.ConverterGuidToString(OutGuidContainer);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um ICarenWICBitmapEncoderInfo para o codificador. 
/// </summary>
/// <param name="Param_Out_EncoderInfo">Retorna uma interface(ICarenWICBitmapEncoderInfo) que contém um ponteiro para o objeto de informações do codificador.</param>
CarenResult CarenWICBitmapEncoder::GetEncoderInfo(
[Out] ICarenWICBitmapEncoderInfo^% Param_Out_EncoderInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapEncoderInfo* pOutEncoInfo = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEncoderInfo(&pOutEncoInfo);

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
	Param_Out_EncoderInfo = gcnew CarenWICBitmapEncoderInfo();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutEncoInfo, Param_Out_EncoderInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um escritor de consulta de metadados para o codificador. 
/// </summary>
/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o escritor de consulta de metadados do codificador.</param>
CarenResult CarenWICBitmapEncoder::GetMetadataQueryWriter(
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
/// Inicializa o codificador com um ICarenStream que diz ao codificador onde codificar os bits. 
/// </summary>
/// <param name="Param_Stream">O fluxo de saída.</param>
/// <param name="Param_OpcoesCache">O WICBitmapEncoderCacheOption usado na inicialização.</param>
CarenResult CarenWICBitmapEncoder::Initialize(
ICarenStream^ Param_Stream,
CA_WICBitmapEncoderCacheOption Param_OpcoesCache)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pFluxo = NULL;
	WICBitmapEncoderCacheOption EncoCacheOptions = static_cast<WICBitmapEncoderCacheOption>(Param_OpcoesCache);

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Stream, &pFluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(pFluxo, EncoCacheOptions);

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
/// Define os objetos ICarenWICColorContext para o codificador. 
/// </summary>
/// <param name="Param_Quantidade">O número de ICarenWICColorContext a definir.</param>
/// <param name="Param_ColorContexts">Uma matriz de interfaces(ICarenWICColorContext) contendo os contextos de cor para definir para o codificador.</param>
CarenResult CarenWICBitmapEncoder::SetColorContexts(
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
/// Define a paleta global para a imagem. 
/// Apenas as imagens GIF suportam uma paleta global opcional, e você deve definir a paleta global antes de adicionar quaisquer frames à imagem. Você só precisa 
/// definir a paleta para formatos de pixel indexados.
/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
/// </summary>
/// <param name="Param_Palette">Uma interface(ICarenWICPalette) para usar como paleta global.</param>
CarenResult CarenWICBitmapEncoder::SetPalette(
ICarenWICPalette^ Param_Palette)
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
/// Define a visualização global para a imagem. 
/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
/// </summary>
/// <param name="Param_Preview">Uma interface(ICarenWICBitmapSource) para usar como pré-visualização global.</param>
CarenResult CarenWICBitmapEncoder::SetPreview(
ICarenWICBitmapSource^ Param_Preview)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pWicSource = NULL;

	//Recupera o ponteiro para a paleta
	Resultado = RecuperarPonteiroCaren(Param_Preview, &pWicSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPreview(pWicSource);

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
/// Define a miniatura global para a imagem. 
/// Retorna WINCODEC_ERR_UNSUPPORTEDOPERATION se o recurso não for suportado pelo codificador.
/// </summary>
/// <param name="Param_Thumbnail">Uma interface (ICarenWICBitmapSource) para definir como a miniatura global.</param>
CarenResult CarenWICBitmapEncoder::SetThumbnail(
ICarenWICBitmapSource^ Param_Thumbnail)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pWicSource = NULL;

	//Recupera o ponteiro para a paleta
	Resultado = RecuperarPonteiroCaren(Param_Thumbnail, &pWicSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetThumbnail(pWicSource);

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