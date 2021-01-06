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
#include "CarenWICPixelFormatInfo2.h"

//Destruidor.
CarenWICPixelFormatInfo2::~CarenWICPixelFormatInfo2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICPixelFormatInfo2::CarenWICPixelFormatInfo2()
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
CarenResult CarenWICPixelFormatInfo2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICPixelFormatInfo2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPixelFormatInfo2*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICPixelFormatInfo2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICPixelFormatInfo2*>(Param_PonteiroNativo);

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
CarenResult CarenWICPixelFormatInfo2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICPixelFormatInfo2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICPixelFormatInfo2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICPixelFormatInfo2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICPixelFormatInfo2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICPixelFormatInfo2::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICPixelFormatInfo2::LiberarReferencia()
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
void CarenWICPixelFormatInfo2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICPixelFormatInfo2();
}



// Métodos da interface proprietária(ICarenWICPixelFormatInfo2)


/// <summary>
/// Recupera o WICPixelFormatNumericRepresentation do formato de pixel.
/// </summary>
/// <param name="Param_Out_RepresentacaoNumerica">Retorna um valor da enumeração(CA_WICPixelFormatNumericRepresentation) que define a representação númerica do formato de pixel.</param>
CarenResult CarenWICPixelFormatInfo2::GetNumericRepresentation([Out] CA_WICPixelFormatNumericRepresentation% Param_Out_RepresentacaoNumerica)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICPixelFormatNumericRepresentation vi_OutFormatRepresentation = WICPixelFormatNumericRepresentationUnspecified;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNumericRepresentation(&vi_OutFormatRepresentation);

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
	Param_Out_RepresentacaoNumerica = static_cast<CA_WICPixelFormatNumericRepresentation>(vi_OutFormatRepresentation);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna se o formato suporta pixels transparentes. 
/// </summary>
/// <param name="Param_Out_SuporteTransparencia">Retornos TRUE se o formato pixel suportar transparência; caso contrário, FALSE.</param>
CarenResult CarenWICPixelFormatInfo2::SupportsTransparency([Out] Boolean% Param_Out_SuporteTransparencia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutSuporteTransparencia = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SupportsTransparency(&vi_OutSuporteTransparencia);

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

	//Define no parametro de saida o resultado.
	Param_Out_SuporteTransparencia = vi_OutSuporteTransparencia ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICPixelFormatInfo)


/// <summary>
/// Obtém os bits por pixel (BPP) do formato pixel. 
/// </summary>
/// <param name="Param_Out_BitsPerPixel">Retorna o o BPP do formato pixel.</param>
CarenResult CarenWICPixelFormatInfo2::GetBitsPerPixel([Out] UInt32% Param_Out_BitsPerPixel)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutBitsPerPixel = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBitsPerPixel(&vi_OutBitsPerPixel);

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
	Param_Out_BitsPerPixel = vi_OutBitsPerPixel;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de canais que o formato pixel contém. 
/// </summary>
/// <param name="Param_Out_ChannelCount">Retorna o número de canais.</param>
CarenResult CarenWICPixelFormatInfo2::GetChannelCount([Out] UInt32% Param_Out_ChannelCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutChannelCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetChannelCount(&vi_OutChannelCount);

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
	Param_Out_ChannelCount = vi_OutChannelCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe a máscara de canal do formato pixel. 
/// Se 0 e NULO forem passados ​​para Param_SizeMaskBuffer e Param_Ref_MaskBuffer, respectivamente, o tamanho do buffer necessário será retornado por meio de (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_ChannelIndex">O índice da máscara do canal para recuperar.</param>
/// <param name="Param_SizeMaskBuffer">O tamanho do buffer (Param_Ref_MaskBuffer).</param>
/// <param name="Param_Ref_MaskBuffer">Uma interface(ICarenBuffer) que vai receber o Buffer da máscara do canal.</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do buffer necessário para obter a máscara de canal.</param>
CarenResult CarenWICPixelFormatInfo2::GetChannelMask(
	UInt32 Param_ChannelIndex,
	UInt32 Param_SizeMaskBuffer,
	ICarenBuffer^% Param_Ref_MaskBuffer,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_OutMaskBuffer = DefaultGenPointer; //O usuário pode definir para NULO para recuperar o size.
	UINT32 vi_OutSizeAtual = 0;

	//Verifica se forneceu o buffer e tenta recuperar o ponteiro.
	CarenGetPointerFromICarenBufferSafe(Param_Ref_MaskBuffer, vi_OutMaskBuffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetChannelMask(
		Param_ChannelIndex,
		Param_SizeMaskBuffer,
		ObjetoGerenciadoValido(Param_Ref_MaskBuffer) ? Util.ConverterIntPtrTo<PBYTE>(vi_OutMaskBuffer) : Nulo,
		&vi_OutSizeAtual);

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

	//Define o size atual do buffer no parametro de saida.
	Param_Out_SizeAtual = vi_OutSizeAtual;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o ICarenWICColorContext do formato pixel. 
/// O contexto de cores retornado é o espaço de cor padrão para o formato pixel. No entanto, se um ICarenWICBitmapSource especificar seu próprio contexto de cores, o contexto da fonte 
/// deve ser preferido em relação ao padrão do formato pixel.
/// </summary>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenWICColorContext) que contém um ponteiro para o contexto de cores do formato do pixel.</param>
CarenResult CarenWICPixelFormatInfo2::GetColorContext([Out] ICarenWICColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext* vi_OutColorContext = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorContext(&vi_OutColorContext);

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
	Param_Out_ColorContext = gcnew CarenWICColorContext();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_OutColorContext, Param_Out_ColorContext, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o GUID do formato de pixel. 
/// </summary>
/// <param name="Param_Out_Formato">Retorna o GUID para o formato do pixel.</param>
CarenResult CarenWICPixelFormatInfo2::GetFormatGUID([Out] String^% Param_Out_Formato)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_OutGuidFormato = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFormatGUID(&vi_OutGuidFormato);

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
	Param_Out_Formato = Util.ConverterGuidToString(vi_OutGuidFormato);

Done:;
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
CarenResult CarenWICPixelFormatInfo2::GetAuthor(
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
CarenResult CarenWICPixelFormatInfo2::GetCLSID([Out] String^% Param_Out_CLSID)
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
CarenResult CarenWICPixelFormatInfo2::GetComponentType([Out] CA_WICComponentType% Param_Out_Type)
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
CarenResult CarenWICPixelFormatInfo2::GetFriendlyName(
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
CarenResult CarenWICPixelFormatInfo2::GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status)
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
CarenResult CarenWICPixelFormatInfo2::GetSpecVersion(
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
CarenResult CarenWICPixelFormatInfo2::GetVendorGUID([Out] String^% Param_Out_GuidVendor)
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
CarenResult CarenWICPixelFormatInfo2::GetVersion(
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