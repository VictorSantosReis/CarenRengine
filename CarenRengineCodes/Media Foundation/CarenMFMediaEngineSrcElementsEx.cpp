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
#include "CarenMFMediaEngineSrcElementsEx.h"

//Destruidor.
CarenMFMediaEngineSrcElementsEx::~CarenMFMediaEngineSrcElementsEx()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineSrcElementsEx::CarenMFMediaEngineSrcElementsEx()
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
CarenResult CarenMFMediaEngineSrcElementsEx::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFMediaEngineSrcElementsEx::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngineSrcElementsEx*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaEngineSrcElementsEx::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngineSrcElementsEx*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaEngineSrcElementsEx::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngineSrcElementsEx::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngineSrcElementsEx::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaEngineSrcElementsEx::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaEngineSrcElementsEx::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineSrcElementsEx::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineSrcElementsEx::LiberarReferencia()
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
void CarenMFMediaEngineSrcElementsEx::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineSrcElementsEx();
}



// Métodos da interface proprietária(ICarenMFMediaEngineSrcElementsEx)


/// <summary>
/// Fornece uma versão aprimorada do ICarenMFMediaEngineSrcElements::AddElement para adicionar o sistema-chave destinado a ser usado com conteúdo a um elemento.
/// </summary>
/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
/// <param name="Param_KeySystem">A Key(Chave) da sessão de mídia.</param>
CarenResult CarenMFMediaEngineSrcElementsEx::AddElementEx(
String^ Param_Url,
String^ Param_Tipo,
String^ Param_Midia,
String^ Param_KeySystem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pUrl = Nulo;
	PWSTR vi_pTipo = Nulo;
	PWSTR vi_pMidia = Nulo;
	PWSTR vi_pKeySystem = Nulo;

	//Converte as strings se tiverem sido informadas
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToWCHAR(Param_Url);
	if (ObjetoGerenciadoValido(Param_Tipo))
		vi_pTipo = Util.ConverterStringToWCHAR(Param_Tipo);
	if (ObjetoGerenciadoValido(Param_Midia))
		vi_pMidia = Util.ConverterStringToWCHAR(Param_Midia);
	if (ObjetoGerenciadoValido(Param_KeySystem))
		vi_pKeySystem = Util.ConverterStringToWCHAR(Param_KeySystem);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddElementEx(vi_pUrl, vi_pTipo, vi_pMidia, vi_pKeySystem);

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
	//Libera a memória utilizada pelas strings.
	DeletarStringAllocatedSafe(&vi_pUrl);
	DeletarStringAllocatedSafe(&vi_pTipo);
	DeletarStringAllocatedSafe(&vi_pMidia);
	DeletarStringAllocatedSafe(&vi_pKeySystem);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o sistema-chave para o índice de elemento de origem dado.
/// </summary>
/// <param name="Param_Index">O índice de elementos de origem.</param>
/// <param name="Param_Out_MimeType">Recebe o tipo MIME do elemento fonte.</param>
CarenResult CarenMFMediaEngineSrcElementsEx::GetKeySystem(
UInt32 Param_Index, 
[Out] String^% Param_Out_MimeType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutMimeType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetKeySystem(static_cast<DWORD>(Param_Index), &vi_pOutMimeType);

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

	//Verifica se o tipo Mime retorna é valido e cria a string a ser retornada.
	if (ObjetoValido(vi_pOutMimeType))
		Param_Out_MimeType = gcnew String(vi_pOutMimeType);

Done:;
	//Libera a memória utilizada pela string.
	if (ObjetoValido(vi_pOutMimeType))
		SysFreeString(vi_pOutMimeType);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenMFMediaEngineSrcElements)


/// <summary>
/// Adiciona um elemento de origem ao final da lista.
/// </summary>
/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
CarenResult CarenMFMediaEngineSrcElementsEx::AddElement(
	String^ Param_Url,
	String^ Param_Tipo,
	String^ Param_Midia
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pUrl = Nulo;
	BSTR vi_pTipo = Nulo;
	BSTR vi_pMidia = Nulo;

	//Converte as strings se tiverem sido informadas
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToBSTR(Param_Url);
	if (ObjetoGerenciadoValido(Param_Tipo))
		vi_pTipo = Util.ConverterStringToBSTR(Param_Tipo);
	if (ObjetoGerenciadoValido(Param_Midia))
		vi_pMidia = Util.ConverterStringToBSTR(Param_Midia);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddElement(vi_pUrl, vi_pTipo, vi_pMidia);

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
	//Libera a memória utilizada pelas strings.
	DeletarStringBSTRSafe(&vi_pUrl);
	DeletarStringBSTRSafe(&vi_pTipo);
	DeletarStringBSTRSafe(&vi_pMidia);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de elementos de origem na lista.
/// </summary>
/// <param name="Param_Out_Quantidade">Recebe o numero de elementos presente na lista.</param>
void CarenMFMediaEngineSrcElementsEx::GetLength([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = static_cast<UInt32>(PonteiroTrabalho->GetLength());
}

/// <summary>
/// Obtém o tipo de mídia pretendido de um elemento na lista.
/// </summary>
/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_Midia">Recebe uma string que contém uma sequência de consulta de mídia. Se nenhum tipo de mídia for definido, este parâmetro receberá o valor NULO.</param>
CarenResult CarenMFMediaEngineSrcElementsEx::GetMedia(
	UInt32 Param_Index,
	[Out] String^% Param_Out_Midia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutMedia = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMedia(static_cast<DWORD>(Param_Index), &vi_pOutMedia);

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

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutMedia))
		Param_Out_Midia = gcnew String(vi_pOutMedia);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutMedia);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tipo MIME de um elemento na lista.
/// </summary>
/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_MimeType">Recebe uma string que contém o MIME Type. Se nenhum tipo de MIME for definido, este parâmetro receberá o valor NULO.</param>
CarenResult CarenMFMediaEngineSrcElementsEx::GetType(
	UInt32 Param_Index,
	[Out] String^% Param_Out_MimeType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutMimeType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetType(static_cast<DWORD>(Param_Index), &vi_pOutMimeType);

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

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutMimeType))
		Param_Out_MimeType = gcnew String(vi_pOutMimeType);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutMimeType);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a URL de um elemento na lista.
/// </summary>
/// <param name="Param_Index">>O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_Url">Recebe uma string que contém a URL do elemento de origem. Se nenhuma URL for definida, este parâmetro receberá o valor NULO</param>
CarenResult CarenMFMediaEngineSrcElementsEx::GetURL(
	UInt32 Param_Index,
	[Out] String^% Param_Out_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutUrl = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetURL(static_cast<DWORD>(Param_Index), &vi_pOutUrl);

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

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutUrl))
		Param_Out_Url = gcnew String(vi_pOutUrl);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os elementos de origem da lista.
/// </summary>
CarenResult CarenMFMediaEngineSrcElementsEx::RemoveAllElements()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAllElements();

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