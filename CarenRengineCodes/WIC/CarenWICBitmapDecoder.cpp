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
#include "CarenWICBitmapDecoder.h"

//Destruidor.
CarenWICBitmapDecoder::~CarenWICBitmapDecoder()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapDecoder::CarenWICBitmapDecoder()
{
	//CÓDIGO DE CRIAÇÃO.
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenWICBitmapDecoder::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICBitmapDecoder::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapDecoder*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICBitmapDecoder::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapDecoder*>(Param_PonteiroNativo);

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
CarenResult CarenWICBitmapDecoder::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapDecoder::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapDecoder::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICBitmapDecoder::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapDecoder::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapDecoder::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapDecoder::LiberarReferencia()
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
void CarenWICBitmapDecoder::LimparDados()
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
void CarenWICBitmapDecoder::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICBitmapDecoder();
}



// Métodos da interface proprietária(ICarenWICBitmapDecoder)


/// <summary>
/// Copia o ICarenWICPalette do decodificador.
/// CopyPalette retorna uma paleta global (uma paleta que se aplica a todos os frames da imagem) se houver uma; caso contrário, ele retorna WINCODEC_ERR_PALETTEUNAVAILABLE. 
/// Se uma imagem não tiver uma paleta global, ela ainda pode ter uma paleta de nível de frame, que pode ser recuperada usando ICarenWICBitmapFrameDecode::CopyPalette.
/// </summary>
/// <param name="Param_Palette">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a paleta global do decodificador. Use o 
/// ICarenWICImagingFactory::CreatePalette para criar a paleta de destino antes de chamar o CopyPalette.</param>
CarenResult CarenWICBitmapDecoder::CopyPalette(ICaren^ Param_Palette)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* pWicPalette = NULL;

	//Obtém o ponteiro da paleta
	Resultado = RecuperarPonteiroCaren(Param_Palette, &pWicPalette);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CopyPalette(pWicPalette);

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
/// Recupera os objetos ICarenWICColorContext da imagem. 
/// </summary>
/// <param name="Param_Quantidade">O número de contextos de cores para recuperar. Este valor deve ser do tamanho, ou menor do que, o tamanho disponível para (Param_Ref_ColorContexts).</param>
/// <param name="Param_Ref_ColorContexts">Retorna uma matriz de interfaces (ICarenWICColorContext).</param>
/// <param name="Param_Out_SizeAtual">Retorna o número real de interfaces na matriz (Param_Ref_ColorContexts).</param>
CarenResult CarenWICBitmapDecoder::GetColorContexts(
UInt32 Param_Quantidade,
cli::array<ICarenWICColorContext^>^% Param_Ref_ColorContexts,
[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext** pOutArrayColorContexts = NULL; //Pode ser NULO para o usuário obter a quantidade necessária para resgatar as interfaces.
	UINT32 OutTamanhoArrayAtual = 0;

	//Verifica se o usuário informou o array.
	if (ObjetoGerenciadoValido(Param_Ref_ColorContexts))
	{
		//Cria a matriz de interfaces
		pOutArrayColorContexts = CriarMatrizPonteiros<IWICColorContext>(Param_Quantidade);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorContexts(Param_Quantidade, pOutArrayColorContexts == NULL ? NULL : pOutArrayColorContexts, &OutTamanhoArrayAtual);

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

	//Verifica se o array de interfaces é valido e define os dados.
	if (ObjetoValido(pOutArrayColorContexts))
	{
		//Abre um for para criar as interfaces e definir os ponteiros.
		for (UINT32 i = 0; i < OutTamanhoArrayAtual; i++)
		{
			//Cria a interface no index.
			Param_Ref_ColorContexts[i] = gcnew CarenWICColorContext();

			//Define o ponteiro na interface
			DefinirPonteiroInterface(pOutArrayColorContexts[i], Param_Ref_ColorContexts[i]);
		}
	}

	//Define a quantidade de dados no array.
	Param_Out_SizeAtual = OutTamanhoArrayAtual;

Done:;
	//Libera a memória utilizada pelo array de interfaces.
	DeletarMatrizPonteirosSafe(&pOutArrayColorContexts);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o formato do recipiente da imagem. 
/// </summary>
/// <param name="Param_Out_GuidContainerFormat">Retorna um GUID que representa o contêiner de formato da imagem.</param>
CarenResult CarenWICBitmapDecoder::GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutContainer = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerFormat(&OutContainer);

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

	//Converte e define no parametor de saida.
	Param_Out_GuidContainerFormat = Util.ConverterGuidToString(OutContainer);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um ICarenWICBitmapDecoderInfo para a imagem. 
/// </summary>
/// <param name="Param_Out_DecoderInfo">Retorna uma interface(ICarenWICBitmapDecoderInfo) que contém um ponteiro para o objeto de informações do decodificador.</param>
CarenResult CarenWICBitmapDecoder::GetDecoderInfo([Out] ICarenWICBitmapDecoderInfo^% Param_Out_DecoderInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapDecoderInfo* pOutDecodeInfo = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDecoderInfo(&pOutDecodeInfo);

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
	Param_Out_DecoderInfo = gcnew CarenWICBitmapDecoderInfo();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDecodeInfo, Param_Out_DecoderInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o Frame especificado da imagem. 
/// </summary>
/// <param name="Param_Index">O quadro em particular para recuperar.</param>
/// <param name="Param_Out_BitmapFrame">Retorna uma interface(ICarenWICBitmapFrameDecode) contém um ponteiro para o frame especificado.</param>
CarenResult CarenWICBitmapDecoder::GetFrame(
UInt32 Param_Index,
[Out] ICarenWICBitmapFrameDecode^% Param_Out_BitmapFrame)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapFrameDecode* pOutFrame = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrame(Param_Index, &pOutFrame);

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

	//Cria a interface a ser retronada.
	Param_Out_BitmapFrame = gcnew CarenWICBitmapFrameDecode();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutFrame, Param_Out_BitmapFrame);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o número total de frames na imagem. 
/// </summary>
/// <param name="Param_Out_QuantidadeFrames">Retorna o número total de frames na imagem.</param>
CarenResult CarenWICBitmapDecoder::GetFrameCount([Out] UInt32% Param_Out_QuantidadeFrames)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 OutCountFrames = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameCount(&OutCountFrames);

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

	//Define a quantidade de frames no parametro de saida.
	Param_Out_QuantidadeFrames = OutCountFrames;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o leitor de consulta de metadados do decodificador. Se um formato de imagem não suportar metadados em nível de contêiner, isso retornará WINCODEC_ERR_UNSUPPORTEDOPERATION.
/// O único formato de imagem fornecido pelo Windows que suporta metadados em nível de contêiner é o GIF. Em vez disso, use ICarenWICBitmapFrameDecode::GetMetadataQueryReader.
/// </summary>
/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) contém um ponteiro para o leitor de consulta de metadados do decodificador.</param>
CarenResult CarenWICBitmapDecoder::GetMetadataQueryReader([Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataQueryReader* pOutMetadaReader = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataQueryReader(&pOutMetadaReader);

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
	Param_Out_MetadataQueryReader = gcnew CarenWICMetadataQueryReader();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutMetadaReader, Param_Out_MetadataQueryReader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma imagem de visualização, se suportada. Nem todos os formatos suportam visualizações. Apenas as visualizações nativas do codec Microsoft Windows Digital Photo 
/// (WDP) suportam visualizações.
/// </summary>
/// <param name="Param_Out_BitmapSource">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o bitmap de visualização se suportado.</param>
CarenResult CarenWICBitmapDecoder::GetPreview([Out] ICarenWICBitmapSource^% Param_Out_BitmapSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pOutBitmapSource = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPreview(&pOutBitmapSource);

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
	Param_Out_BitmapSource = gcnew CarenWICBitmapSource();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmapSource, Param_Out_BitmapSource);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma miniatura bitmap da imagem, se existir.
/// A miniatura devolvida pode ser de qualquer tamanho, por isso o chamador deve dimensionar a miniatura para o tamanho desejado. Os únicos formatos de imagem fornecidos 
/// pelo Windows que suportam miniaturas são JPEG, TIFF e JPEG-XR. Se a miniatura não estiver disponível, isso retornará WINCODEC_ERR_CODECNOTHUMBNAIL.
/// </summary>
/// <param name="Param_Out_Thumbnail">Retorna uma interface(ICarenWICBitmapSource) contém um ponteiro para o objeto de miniatura.</param>
CarenResult CarenWICBitmapDecoder::GetThumbnail([Out] ICarenWICBitmapSource^% Param_Out_Thumbnail)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pOutBitmapSource = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetThumbnail(&pOutBitmapSource);

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
	Param_Out_Thumbnail = gcnew CarenWICBitmapSource();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmapSource, Param_Out_Thumbnail);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o decodificador com o fluxo fornecido. 
/// </summary>
/// <param name="Param_Stream">O fluxo a ser usado para a inicialização. O fluxo contém os pixels codificados que são decodificados cada vez que o método CopyPixels na 
/// interface ICarenWICBitmapFrameDecode é invocado.</param>
/// <param name="Param_OpcoesCache">Uma enumeração que especifica as opções do decodificador.</param>
CarenResult CarenWICBitmapDecoder::Initialize(
ICarenStream^ Param_Stream,
CA_WICDecodeOptions Param_OpcoesCache)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pFluxo = NULL;
	WICDecodeOptions WicDecoOptions = static_cast<WICDecodeOptions>(Param_OpcoesCache);

	//Recupera o ponteiro para o fluxo
	Resultado = RecuperarPonteiroCaren(Param_Stream, &pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(pFluxo, WicDecoOptions);

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
/// Recupera as capacidades do decodificador com base no fluxo especificado.
/// As implementações de decodificadores personalizadas devem salvar a posição atual do (ICarenStream) especificado, ler quaisquer informações necessárias para determinar quais 
/// recursos elas podem fornecer para o fluxo fornecido e restaurar a posição do fluxo.
/// </summary>
/// <param name="Param_Stream">O fluxo para recuperar as capacidades de decodificador.</param>
/// <param name="Param_Out_Capacidades">Retorna uma enumerações que especifica as capacidades do decodificador para o fluxo informado.</param>
CarenResult CarenWICBitmapDecoder::QueryCapability(
ICarenStream^ Param_Stream,
[Out] CA_WICBitmapDecoderCapabilities% Param_Out_Capacidades)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IStream* pFluxo = NULL;
	DWORD OutWicDecoCaps;

	//Recupera o ponteiro para o fluxo
	Resultado = RecuperarPonteiroCaren(Param_Stream, &pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueryCapability(pFluxo, &OutWicDecoCaps);

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
	Param_Out_Capacidades = static_cast<CA_WICBitmapDecoderCapabilities>(Param_Out_Capacidades);

Done:;
	//Retorna o resultado.
	return Resultado;
}