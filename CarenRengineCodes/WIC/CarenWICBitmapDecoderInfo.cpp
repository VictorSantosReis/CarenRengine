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
#include "CarenWICBitmapDecoderInfo.h"

//Destruidor.
CarenWICBitmapDecoderInfo::~CarenWICBitmapDecoderInfo()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICBitmapDecoderInfo::CarenWICBitmapDecoderInfo()
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
CarenResult CarenWICBitmapDecoderInfo::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICBitmapDecoderInfo::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapDecoderInfo*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICBitmapDecoderInfo::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICBitmapDecoderInfo*>(Param_PonteiroNativo);

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
CarenResult CarenWICBitmapDecoderInfo::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapDecoderInfo::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICBitmapDecoderInfo::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICBitmapDecoderInfo::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICBitmapDecoderInfo::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICBitmapDecoderInfo::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICBitmapDecoderInfo::LiberarReferencia()
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
void CarenWICBitmapDecoderInfo::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICBitmapDecoderInfo();
}



// Métodos da interface proprietária(ICarenWICBitmapDecoderInfo)


/// <summary>
/// Cria uma nova instância IWICBitmapDecoder. 
/// </summary>
/// <param name="Param_Out_IBitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para a nova instância do decodificador. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenWICBitmapDecoderInfo::CreateInstance(ICaren^ Param_Out_IBitmapDecoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapDecoder* pOutDecoder = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInstance(&pOutDecoder);

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

	//Define o ponteiro na interface fornecida pelo usuário.
	Resultado = DefinirPonteiroInterface(pOutDecoder, Param_Out_IBitmapDecoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera as assinaturas de padrão de arquivo suportadas pelo decodificador.
/// Para recuperar todas as assinaturas de padrões, chame o método passando NULO para (Param_Ref_Patterns), isso vai fazer com que (Param_Out_QuantidadeRealArray) 
/// devolva o real valor do tamanho da matriz, necessário
/// no parametro (Param_TamanhoArray).
/// </summary>
/// <param name="Param_TamanhoArray">O tamanho da matriz em (Param_Ref_Patterns).</param>
/// <param name="Param_Ref_Patterns">Recebe uma lista de objetos WICBitmapPattern suportados pelo decodificador.</param>
/// <param name="Param_Out_QuantidadePatterns">Recebe o número de padrões que o decodificador suporta.</param>
/// <param name="Param_Out_QuantidadeRealArray">Recebe o tamanho real do buffer necessário para recuperar todas as assinaturas de padrão suportadas pelo decodificador.</param>
CarenResult CarenWICBitmapDecoderInfo::GetPatterns(
UInt32 Param_TamanhoArray,
cli::array<CA_WICBitmapPattern^>^% Param_Ref_Patterns,
[Out] UInt32% Param_Out_QuantidadePatterns,
[Out] UInt32% Param_Out_QuantidadeRealArray)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICBitmapPattern* pOutArrayPatterns = NULL; //Poder ser NULO para obter a quantidade de items que seram devolvidos.
	UINT32 OutCountPatterns = 0;
	UINT32 OutCountRealArray = 0;

	//Verifica se o array que vai receber os dados foi informado.
	if (ObjetoGerenciadoValido(Param_Ref_Patterns))
	{
		//Cria a matriz de estruturas.
		pOutArrayPatterns = CriarMatrizEstruturas<WICBitmapPattern>(Param_TamanhoArray);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPatterns(Param_TamanhoArray, pOutArrayPatterns == NULL ? NULL : pOutArrayPatterns, &OutCountPatterns, &OutCountRealArray);

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

	//Define os dados no array de saida se tiver sido informado
	if (ObjetoGerenciadoValido(Param_Ref_Patterns))
	{
		//Faz um for para copiar os dados para o array
		for (UINT32 i = 0; i < Param_TamanhoArray; i++)
		{
			//Converte e define no index do array
			Param_Ref_Patterns[i] = Util.ConverterWICBitmapPatternUnManaged_ToManaged(&(pOutArrayPatterns[i]));
		}
	}

	//Define os valores de quantidade e tamanho
	Param_Out_QuantidadePatterns = OutCountPatterns;
	Param_Out_QuantidadeRealArray = OutCountRealArray;

Done:;
	//Libera a memória utilizada pela matriz
	DeletarMatrizEstruturasSafe(&pOutArrayPatterns);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor que indica se o codec reconhece o padrão dentro de um fluxo especificado. 
/// </summary>
/// <param name="Param_Fluxo">O fluxo para o padrão corresponde dentro.</param>
/// <param name="Param_Out_Corresponde">Recebe TRUE se os padrões coincidir; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::MatchesPattern(
ICarenStream^ Param_Fluxo,
[Out] Boolean% Param_Out_Corresponde)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pFluxo = NULL;
	BOOL OutCorrresponde = FALSE;

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &pFluxo);

	//Saido método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MatchesPattern(pFluxo, &OutCorrresponde);

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
	Param_Out_Corresponde = OutCorrresponde ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICBitmapCodecInfo)


/// <summary>
/// Recupera um valor indicando se o codec suporta animação. 
/// </summary>
/// <param name="Param_Out_SuporteAnimacao">Recebe TRUE se o codec suporta imagens com informações de cronometragem; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::DoesSupportAnimation([Out] Boolean% Param_Out_SuporteAnimacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL Outsuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportAnimation(&Outsuporte);

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

	//Define no parametro de saida.
	Param_Out_SuporteAnimacao = Outsuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor indicando se o codec suporta chromakeys. 
/// </summary>
/// <param name="Param_Out_SuporteChromakey">Recebe TRUE se o codec suportar chromakeys; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::DoesSupportChromakey([Out] Boolean% Param_Out_SuporteChromakey)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL Outsuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportChromakey(&Outsuporte);

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

	//Define no parametro de saida.
	Param_Out_SuporteChromakey = Outsuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor indicando se o codec suporta formatos sem perdas. 
/// </summary>
/// <param name="Param_Out_SuporteLossLess">Recebe TRUE se o codec suportar formatos sem perdas; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::DoesSupportLossless([Out] Boolean% Param_Out_SuporteLossLess)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL Outsuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportLossless(&Outsuporte);

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

	//Define no parametro de saida.
	Param_Out_SuporteLossLess = Outsuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor indicando se o codec suporta imagens de vários quadros. 
/// </summary>
/// <param name="Param_Out_SuporteMultiframe">Recebe TRUE se o codec suportar imagens de vários quadros; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::DoesSupportMultiframe([Out] Boolean% Param_Out_SuporteMultiframe)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL Outsuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportMultiframe(&Outsuporte);

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

	//Define no parametro de saida.
	Param_Out_SuporteMultiframe = Outsuporte ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o número da versão de manangement de cor que o codec suporta. 
/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo 
/// da versão de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_VersaoColorManagement) definido para NULO. Esta chamada define (Param_Out_SizeAtual)
/// para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetColorManagementVersion com (Param_Size) definida para o tamanho do 
/// buffer e (Param_Ref_VersaoColorManagement) definido para um buffer do tamanho apropriado recuperará os formatos de pixel
/// </summary>
/// <param name="Param_Size">O tamanho do buffer da versão. Use na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Ref_VersaoColorManagement">Recebe o número da versão de gerenciamento de cores. Use na primeira chamada para determinar o tamanho do buffer necessário</param>
/// <param name="Param_Out_SizeAtual">Recebe tamanho real do buffer necessário para recuperar o número completo da versão de gerenciamento de cores.</param>
CarenResult CarenWICBitmapDecoderInfo::GetColorManagementVersion(
	UInt32 Param_Size,
	String^% Param_Ref_VersaoColorManagement,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutVersion = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a versão.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_Size) for maior que 0.
	if (Param_Size > 0)
		pOutVersion = CriarStringCoTask<WCHAR>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorManagementVersion(Param_Size, Param_Size == 0 ? NULL : pOutVersion, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutVersion))
		Param_Ref_VersaoColorManagement = gcnew String(pOutVersion);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutVersion);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o guid do contêiner associado ao codec.
/// </summary>
/// <param name="Param_Out_GuidFormatoContainer">Recebe o GUID do formato do container.</param>
CarenResult CarenWICBitmapDecoderInfo::GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutContainerGuid = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerFormat(&OutContainerGuid);

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
	Param_Out_GuidFormatoContainer = Util.ConverterGuidToString(OutContainerGuid);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o nome da fabricação do dispositivo associada ao codec.
/// O padrão de uso para este método é um processo de duas chamadas. A primeira chamada recupera o tamanho do buffer necessário para recuperar o número completo da versão
/// de gerenciamento de cores, chamando-o com (Param_Size) definido para 0 e (Param_Ref_ModelosDispositivo) definido para NULO. Esta chamada define (Param_Out_SizeAtual) 
/// para o tamanho do buffer necessário. Uma vez determinado o tamanho do buffer necessário, uma segunda chamada GetDeviceManufacturer com (Param_Size) 
/// definido para o tamanho do buffer e 
/// (Param_Ref_ModelosDispositivo) definido para um buffer do tamanho apropriado recuperará os formatos de pixel.
/// </summary>
/// <param name="Param_Size">O tamanho do nome da fabricação do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário</param>
/// <param name="Param_Ref_FabricanteDispositivo">Recebe o nome da fabricação do dispositivo. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar o nome do fabricante do dispositivo.</param>
CarenResult CarenWICBitmapDecoderInfo::GetDeviceManufacturer(
	UInt32 Param_Size,
	String^% Param_Ref_FabricanteDispositivo,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNome = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar o nome de fabricação.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_Size) for maior que 0.
	if (Param_Size > 0)
		pOutNome = CriarStringCoTask<WCHAR>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceManufacturer(Param_Size, Param_Size == 0 ? NULL : pOutNome, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutNome))
		Param_Ref_FabricanteDispositivo = gcnew String(pOutNome);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutNome);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma lista delimitada de vírgula de modelos de dispositivos associados ao codec.
/// Defina (Param_Size) para 0 e (Param_Ref_ModelosDispositivo) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_ModelosDispositivo)
/// que deve ser definida em (Param_Size).
/// </summary>
/// <param name="Param_Size">O tamanho do buffer dos modelos do dispositivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Ref_ModelosDispositivo">Recebe uma lista delimitada de vírgula de nomes de modelos de dispositivos associados ao codec. Use NULO na primeira chamada para
///  determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os nomes dos modelos do dispositivo.</param>
CarenResult CarenWICBitmapDecoderInfo::GetDeviceModels(
	UInt32 Param_Size,
	String^% Param_Ref_ModelosDispositivo,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutModelos = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a lista de modelos separados por virgula.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_Size) for maior que 0.
	if (Param_Size > 0)
		pOutModelos = CriarStringCoTask<WCHAR>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceModels(Param_Size, Param_Size == 0 ? NULL : pOutModelos, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutModelos))
		Param_Ref_ModelosDispositivo = gcnew String(pOutModelos);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutModelos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma lista delimitada de vírgula das extensões de nome do arquivo associadas ao codec. A extensão padrão de um codificador de imagem é o primeiro item 
/// da lista de extensões devolvidas. Defina (Param_Size) para 0 e (Param_Ref_ExtensoesArquivos) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário 
/// do buffer(Param_Ref_ExtensoesArquivos) que deve ser definida em (Param_Size).
/// </summary>
/// <param name="Param_Size">O tamanho do buffer de extensão do nome do arquivo. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Ref_ExtensoesArquivos">Recebe uma lista delimitada de vírgula de extensões de nomes de arquivo associadas ao codec. Use NULO na primeira chamada para 
/// determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todas as extensões de nome do arquivo associadas ao codec.</param>
CarenResult CarenWICBitmapDecoderInfo::GetFileExtensions(
	UInt32 Param_Size,
	String^% Param_Ref_ExtensoesArquivos,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutExtensoes = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a lista de extensões separadas por virgula.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_Size) for maior que 0.
	if (Param_Size > 0)
		pOutExtensoes = CriarStringCoTask<WCHAR>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFileExtensions(Param_Size, Param_Size == 0 ? NULL : pOutExtensoes, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutExtensoes))
		Param_Ref_ExtensoesArquivos = gcnew String(pOutExtensoes);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutExtensoes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma sequência delimitada de vírgula de tipos de mímicos associados ao codec. 
/// Defina (Param_Size) para 0 e (Param_Ref_MimeTypes) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_MimeTypes) que 
/// deve ser definida em (Param_Size).
/// </summary>
/// <param name="Param_Size">O tamanho do mímico tipo tampão. Use 0 na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Ref_MimeTypes">Recebe os tipos de mímica associados ao codec. Use NULO na primeira chamada para determinar o tamanho do buffer necessário.</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para recuperar todos os tipos de mímica associados ao codec.</param>
CarenResult CarenWICBitmapDecoderInfo::GetMimeTypes(
	UInt32 Param_Size,
	String^% Param_Ref_MimeTypes,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutMimes = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a lista de mimes types separados por virgula.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_Size) for maior que 0.
	if (Param_Size > 0)
		pOutMimes = CriarStringCoTask<WCHAR>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMimeTypes(Param_Size, Param_Size == 0 ? NULL : pOutMimes, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutMimes))
		Param_Ref_MimeTypes = gcnew String(pOutMimes);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutMimes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera os formatos de pixel que o codec suporta.
/// Defina (Param_Size) para 0 e (Param_Ref_FormatosPixel) para NULO, isso vai retornar em (Param_Out_SizeAtual) a largura necessário do buffer(Param_Ref_FormatosPixel)
///  que deve ser definida em (Param_Size).
/// </summary>
/// <param name="Param_Size">O tamanho da matriz (Param_Ref_FormatosPixel). Use 0 na primeira chamada para determinar o tamanho da matriz necessária.</param>
/// <param name="Param_Ref_FormatosPixel">Recebe os formatos pixel suportados. Use NULO na primeira chamada para determinar o tamanho necessário da matriz</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho do array necessário para recuperar todos os formatos de pixel suportados.</param>
CarenResult CarenWICBitmapDecoderInfo::GetPixelFormats(
	UInt32 Param_Size,
	cli::array<String^>^% Param_Ref_FormatosPixel,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID* pOutPixelFormats = NULL;
	UINT32 OutSizeAtual = 0;

	//Verifica se informou o size e cria a matriz de guids
	if (Param_Size > 0)
		pOutPixelFormats = CriarMatrizEstruturas<GUID>(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPixelFormats(Param_Size, Param_Size == 0 ? NULL : pOutPixelFormats, &OutSizeAtual);

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

	//Verifica se a matriz de guids é valida e cria e define a de retorno gerenciado para o usuário.
	if (ObjetoValido(pOutPixelFormats))
	{
		//Cria a matriz gerenciada.
		Param_Ref_FormatosPixel = gcnew cli::array<String^>(Param_Size);

		//Faz um for para definir os dados na matriz.
		for (UINT32 i = 0; i < Param_Size; i++)
		{
			//Converte e define no index especificado.
			Param_Ref_FormatosPixel[i] = Util.ConverterGuidToString(pOutPixelFormats[i]);
		}
	}

	//Define a quantidade de guids atuais.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pOutPixelFormats);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um valor indicando se o tipo de mímica dado corresponde ao tipo mímico do codec. 
/// </summary>
/// <param name="Param_MimeType">O tipo do MimeType para comparar.</param>
/// <param name="Param_Out_Corresponde">Recebe TRUE se os tipos de mímica correspondem; caso contrário, FALSO.</param>
CarenResult CarenWICBitmapDecoderInfo::MatchesMimeType(
	String^ Param_MimeType,
	[Out] Boolean% Param_Out_Corresponde)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PCWSTR pMimeType = NULL;
	BOOL OutCorresponde = FALSE;

	//Converte a string
	pMimeType = Util.ConverterStringToConstWCHAR(Param_MimeType);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->MatchesMimeType(pMimeType, &OutCorresponde);

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
	Param_Out_Corresponde = OutCorresponde ? true : false;

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&pMimeType);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICComponentInfo)


/// <summary>
/// Recupera o nome do autor do componente. Se (Param_SizeAutorString) for 0 e (Param_Ref_Autor) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeAutorString">O tamanho da String (Param_Ref_Autor).</param>
/// <param name="Param_Ref_Autor">Recebe o nome do autor do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da instalação.
///  Para componentes embutidos, essas Strings estão sempre em inglês.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome dos autores do componente. O nome do autor é opcional; se um nome autor não for especificado pelo componente,
///  o comprimento devolvido será 0.</param>
CarenResult CarenWICBitmapDecoderInfo::GetAuthor(
	UInt32 Param_SizeAutorString,
	String^% Param_Ref_Autor,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNomeAutor = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar o nome do autor.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeAutorString > 0)
		pOutNomeAutor = CriarStringCoTask<WCHAR>(Param_SizeAutorString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAuthor(Param_SizeAutorString, Param_SizeAutorString == 0 ? NULL : pOutNomeAutor, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutNomeAutor))
		Param_Ref_Autor = gcnew String(pOutNomeAutor);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutNomeAutor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o identificador de classe do componente (CLSID) 
/// </summary>
/// <param name="Param_Out_CLSID">Recebe o CLSID do componente.</param>
CarenResult CarenWICBitmapDecoderInfo::GetCLSID([Out] String^% Param_Out_CLSID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutCLSID = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCLSID(&OutCLSID);

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

	//Converte o Guid em String.
	Param_Out_CLSID = Util.ConverterGuidToString(OutCLSID);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o CA_WICComponentType do componente. 
/// </summary>
/// <param name="Param_Out_Type">Recebe um enum CA_WICComponentType que define o tipo do componente.</param>
CarenResult CarenWICBitmapDecoderInfo::GetComponentType([Out] CA_WICComponentType% Param_Out_Type)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICComponentType OutCompType;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetComponentType(&OutCompType);

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
	Param_Out_Type = static_cast<CA_WICComponentType>(OutCompType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o nome amigável do componente, que é um nome de exibição legível por humanos para o componente.
/// Se (Param_SizeNomeString) for 0 e (Param_Ref_NomeAmigavel) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeNomeString">O tamanho da String em (Param_Ref_NomeAmigavel).</param>
/// <param name="Param_Ref_NomeAmigavel">Recebe o nome amigável do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da 
/// instalação. Para componentes embutidos, essas cordas 
/// estão sempre em inglês.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome amigável do componente.</param>
CarenResult CarenWICBitmapDecoderInfo::GetFriendlyName(
	UInt32 Param_SizeNomeString,
	String^% Param_Ref_NomeAmigavel,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNomeAmigavel = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar o nome amigavel.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeNomeString > 0)
		pOutNomeAmigavel = CriarStringCoTask<WCHAR>(Param_SizeNomeString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFriendlyName(Param_SizeNomeString, Param_SizeNomeString == 0 ? NULL : pOutNomeAmigavel, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutNomeAmigavel))
		Param_Ref_NomeAmigavel = gcnew String(pOutNomeAmigavel);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutNomeAmigavel);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o status de assinatura do componente. A assinatura não é usada pelo WIC. Portanto, todos os componentes WICComponentSigned. Esta função pode ser usada para 
/// determinar se um componente não possui nenhum componente 
/// binário ou foi adicionado à lista de componentes desabilitados no registro.
/// </summary>
/// <param name="Param_Out_Status">Retorna um enum que recebe o status do componente.</param>
CarenResult CarenWICBitmapDecoderInfo::GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD OutCompSigning;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSigningStatus(&OutCompSigning);

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
	Param_Out_Status = static_cast<CA_WICComponentSigning>(OutCompSigning);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a versão de especificação do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão spec.
/// Se (Param_SizeSpecString) for 0 e (Param_Ref_SpecVersion) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeSpecString">O tamanho da String em (Param_Ref_SpecVersion).</param>
/// <param name="Param_Ref_SpecVersion">Retorna uma string que contém uma sequência de cultura invariente da versão de especificação do componente. O formulário de versão 
/// é NN.NN.NN.NN.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão de especificação do componente. A versão de especificação é opcional; se um valor não for especificado
///  pelo componente, o comprimento devolvido será 0.</param>
CarenResult CarenWICBitmapDecoderInfo::GetSpecVersion(
	UInt32 Param_SizeSpecString,
	String^% Param_Ref_SpecVersion,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutSpecVersion = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a versão de especificação.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeSpecString > 0)
		pOutSpecVersion = CriarStringCoTask<WCHAR>(Param_SizeSpecString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSpecVersion(Param_SizeSpecString, Param_SizeSpecString == 0 ? NULL : pOutSpecVersion, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutSpecVersion))
		Param_Ref_SpecVersion = gcnew String(pOutSpecVersion);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutSpecVersion);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o fornecedor GUID. 
/// </summary>
/// <param name="Param_Out_GuidVendor">Recebe o guid do fornecedor do componente.</param>
CarenResult CarenWICBitmapDecoderInfo::GetVendorGUID([Out] String^% Param_Out_GuidVendor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidVendor = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVendorGUID(&OutGuidVendor);

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
	Param_Out_GuidVendor = Util.ConverterGuidToString(OutGuidVendor);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a versão do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão.
/// Se (Param_SizeVersionString) for 0 e (Param_Ref_Version) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeVersionString">O tamanho da String em (Param_Ref_Version).</param>
/// <param name="Param_Ref_Version">Recebe uma sequência de cultura invariante da versão do componente.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão do componente. A versão é opcional; se um valor não for especificado pelo componente, o comprimento
///  devolvido será 0.</param>
CarenResult CarenWICBitmapDecoderInfo::GetVersion(
	UInt32 Param_SizeVersionString,
	String^% Param_Ref_Version,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutVersion = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a versão.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeVersionString > 0)
		pOutVersion = CriarStringCoTask<WCHAR>(Param_SizeVersionString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVersion(Param_SizeVersionString, Param_SizeVersionString == 0 ? NULL : pOutVersion, &OutSizeAtual);

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

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutVersion))
		Param_Ref_Version = gcnew String(pOutVersion);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutVersion);

	//Retorna o resultado.
	return Resultado;
}