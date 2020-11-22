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
#include "CarenWICMetadataQueryWriter.h"

//Destruidor.
CarenWICMetadataQueryWriter::~CarenWICMetadataQueryWriter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICMetadataQueryWriter::CarenWICMetadataQueryWriter()
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
CarenResult CarenWICMetadataQueryWriter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICMetadataQueryWriter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICMetadataQueryWriter*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICMetadataQueryWriter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICMetadataQueryWriter*>(Param_PonteiroNativo);

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
CarenResult CarenWICMetadataQueryWriter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICMetadataQueryWriter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICMetadataQueryWriter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICMetadataQueryWriter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICMetadataQueryWriter::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICMetadataQueryWriter::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICMetadataQueryWriter::LiberarReferencia()
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
void CarenWICMetadataQueryWriter::LimparDados()
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
void CarenWICMetadataQueryWriter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICMetadataQueryWriter();
}



// Métodos da interface proprietária(ICarenWICMetadataQueryWriter)


/// <summary>
/// Remove um item de metadados de um local específico usando uma expressão de consulta de metadados.
/// Este método usa expressões de consulta de metadados para remover metadados. Se o item metadados for um bloco de metadados, ele será removido da hierarquia de metadados.
/// </summary>
/// <param name="Param_Nome">O nome do item metadados para remover.</param>
CarenResult CarenWICMetadataQueryWriter::RemoveMetadataByName(String^ Param_Nome)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNome = NULL;

	//Converte a string
	pNome = Util.ConverterStringToWCHAR(Param_Nome);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveMetadataByName(pNome);

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
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&pNome);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um item de metadados em um local específico. 
/// Este método usa expressões de consulta de metadados para remover metadados. Se o conjunto de valor é um bloco de metadados aninhados, use o tipo de variante 
/// (TP_PonteiroDesconhecido) e o (Param_Valor) apontando para o ICarenWICMetadataQueryWriter do novo bloco de metadados.
/// A encomenda de itens de metadados fica a critério do autor de consulta, uma vez que os locais relativos não são especificados.
/// </summary>
/// <param name="Param_Nome">O nome do item metadados.</param>
/// <param name="Param_Valor">Uma estrutura(CA_PropVariant) que contém o valor dos metadados para definir.</param>
CarenResult CarenWICMetadataQueryWriter::SetMetadataByName(
String^ Param_Nome,
CA_PropVariant^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNome = NULL;
	PROPVARIANT PropVar = {};

	//Converte a string
	pNome = Util.ConverterStringToWCHAR(Param_Nome);

	//Inicializa a propVariant.
	PropVariantInit(&PropVar);

	//Converte a propvariant
	bool ConvertPropVar = Util.ConvertPropVariantManagedToUnamaged(Param_Valor, PropVar);

	//Verifica o resultado
	if (!ConvertPropVar)
	{
		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_PROPVARIANT_CREATE_OR_CONVERSION, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetMetadataByName(pNome, &PropVar);

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

	//Libera a propVariant.
	PropVariantClear(&PropVar);

Done:;
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&pNome);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICMetadataQueryReader)


/// <summary>
/// Obtém o formato de contêiner de leitores de consulta de metadados. 
/// </summary>
/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID que representa o tipo do formato cointainer.</param>
CarenResult CarenWICMetadataQueryWriter::GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat)
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

	//Converte o guid e define no parametro de saida.
	Param_Out_GuidContainerFormat = Util.ConverterGuidToString(OutGuidContainer);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um enumerador de todos os itens de metadados na localização relativa atual dentro da hierarquia de metadados. 
/// </summary>
/// <param name="Param_Out_EnumString">Retorna uma interface(ICarenEnumString) que contém um ponteiro para o enumerador que contém Strings de consulta que pode ser usadas na 
/// interface (ICarenWICMetadataQueryReader) atual.</param>
CarenResult CarenWICMetadataQueryWriter::GetEnumerator([Out] ICarenEnumString^% Param_Out_EnumString)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IEnumString* pOutEnumString = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEnumerator(&pOutEnumString);

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
	Param_Out_EnumString = gcnew CarenEnumString();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutEnumString, Param_Out_EnumString);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o caminho atual em relação ao bloco de metadados raiz. Se o leitor de consulta for relativo ao topo da hierarquia de metadados, ele retornará uma sequência de char único.
/// Se o leitor de consulta for relativo a um bloco de metadados aninhados, este método retornará o caminho para o leitor de consulta atual.
/// Se você passar NULO para (Param_Ref_Namespace), o GetLocation ignorará o (Param_SizeString) e retorna o comprimento de buffer necessário para armazenar o caminho na variável 
/// a que o (Param_Out_SizeAtual) aponta.
/// </summary>
/// <param name="Param_SizeString">O comprimento da String em (Param_Ref_Namespace).</param>
/// <param name="Param_Ref_Namespace">Retorna uma string que contém a localização atual do namespace.</param>
/// <param name="Param_Out_SizeAtual">Retorna o comprimento real necessário pela String(Param_Ref_Namespace).</param>
CarenResult CarenWICMetadataQueryWriter::GetLocation(
	UInt32 Param_SizeString,
	String^% Param_Ref_Namespace,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNamespace = NULL; //Pode ser NULO para o usuário obter primeiro o size necessário para a string.
	UINT32 OutSizeAtual = 0;

	//Verifica se a string é valida.
	if (ObjetoGerenciadoValido(Param_Ref_Namespace))
	{
		//Aloca memória para a string.
		pOutNamespace = CriarStringCoTask<WCHAR>(Param_SizeString);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetLocation(Param_SizeString, pOutNamespace == NULL ? NULL : pOutNamespace, &OutSizeAtual);

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

	//Verifica se forneceu a string e adicona os dados.
	if (ObjetoValido(pOutNamespace))
	{
		//Inicializa a string com os dados obtidos.
		Param_Ref_Namespace = gcnew String(pOutNamespace);
	}

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringCoTaskSafe(&pOutNamespace);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o bloco de metadados ou item identificado por uma expressão de consulta de metadados.
/// Este método usa expressões de consulta de metadados para acessar metadados incorporados. Se existirem vários blocos ou itens expressos pela mesma expressão de consulta, 
/// o primeiro bloco de metadados ou item encontrado será devolvido.
/// </summary>
/// <param name="Param_Nome">A expressão de consulta ao bloco ou item de metadados solicitados.</param>
/// <param name="Param_Out_Valor">Retorna uma estrutura(CA_PropVariant) que armazena o bloco de metadados ou item solicitado.</param>
CarenResult CarenWICMetadataQueryWriter::GetMetadataByName(
	String^ Param_Nome,
	[Out] CA_PropVariant^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNome = NULL;
	PROPVARIANT OutPropVar = {};

	//Converte a string.
	pNome = Util.ConverterStringToWCHAR(Param_Nome);

	//Inicializa a propvariant
	PropVariantInit(&OutPropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataByName(pNome, &OutPropVar);

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

	//Converte a estrutura nativa para a gerenciada.
	Param_Out_Valor = Util.ConvertPropVariantUnmanagedToManaged(OutPropVar);

	//Libera a propvariant
	PropVariantClear(&OutPropVar);

Done:;
	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&pNome);

	//Retorna o resultado.
	return Resultado;
}