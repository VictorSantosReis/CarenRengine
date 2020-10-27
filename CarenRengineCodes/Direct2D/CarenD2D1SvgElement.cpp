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
#include "CarenD2D1SvgElement.h"

//Destruidor.
CarenD2D1SvgElement::~CarenD2D1SvgElement()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgElement::CarenD2D1SvgElement()
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
CarenResult CarenD2D1SvgElement::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenD2D1SvgElement::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgElement*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1SvgElement::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgElement*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1SvgElement::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SvgElement::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SvgElement::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1SvgElement::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SvgElement::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgElement::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgElement::LiberarReferencia()
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
void CarenD2D1SvgElement::LimparDados()
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
void CarenD2D1SvgElement::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1SvgElement();
}



// Métodos da interface proprietária(ICarenD2D1SvgElement)


/// <summary>
/// Anexa um elemento à lista de childs. Se o elemento já tiver um pai, ele será removido deste pai como parte da operação de anexação.
/// </summary>
/// <param name="Param_NewChild">O elemento para anexar.</param>
CarenResult CarenD2D1SvgElement::AppendChild(ICarenD2D1SvgElement^ Param_NewChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElement = NULL;

	//Recupera o ponteiro para o elemento svg.
	Resultado = RecuperarPonteiroCaren(Param_NewChild, &pSvgElement);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AppendChild(pSvgElement);

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
/// Cria um elemento a partir de um nome de etiqueta. O elemento é anexado à lista de childs. 
/// </summary>
/// <param name="Param_TagName">O nome da novo child. Uma sequência vazia é interpretada como um elemento de conteúdo de texto.</param>
/// <param name="Param_Out_NewChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o novo child.</param>
CarenResult CarenD2D1SvgElement::CreateChild(
String^ Param_TagName,
[Out] ICarenD2D1SvgElement^% Param_Out_NewChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pTagName = NULL;
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Converte a string
	pTagName = Util.ConverterStringToWCHAR(Param_TagName);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateChild(pTagName, &pOutSvgElement);

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
	Param_Out_NewChild = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface de saida.
	Resultado = DefinirPonteiroInterface(pOutSvgElement, Param_Out_NewChild);

Done:;
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pTagName);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como uma string.
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Tipo">O tipo de String.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
/// <param name="Param_SizeValor">O tamanho do valor em bytes.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE  Param_Tipo,
[Out] String^% Param_Out_Valor,
UInt32 Param_SizeValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_ATTRIBUTE_STRING_TYPE AttributeType = static_cast<D2D1_SVG_ATTRIBUTE_STRING_TYPE>(Param_Tipo);
	PWSTR pOutValor = CriarStringCoTask<WCHAR>(Param_SizeValor + 1);

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, AttributeType, pOutValor, Param_SizeValor);

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

	//Cria a string a ser retornada.
	Param_Out_Valor = gcnew String(pOutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);
	DeletarStringCoTaskSafe(&pOutValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um tipo de POD. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Tipo">O tipo POD do valor.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICaren) que contém o ponteiro para o objeto(void*). O usuário deve inicializar a interface antes de chamar este método.</param>
/// <param name="Param_SizeValorEmBytes">O tamanho do valor em bytes.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_ATTRIBUTE_POD_TYPE Param_Tipo,
ICaren^ Param_Out_Valor,
UInt32 Param_SizeValorEmBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_ATTRIBUTE_POD_TYPE AttributeType = static_cast<D2D1_SVG_ATTRIBUTE_POD_TYPE>(Param_Tipo);
	void* pOutValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, AttributeType, pOutValor, Param_SizeValorEmBytes);

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

	//Define o objeto na interface de saida.
	Resultado = Param_Out_Valor->AdicionarPonteiro(pOutValor);
	
Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um tipo de interface. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_RiidInterface">O ID de interface do valor do atributo.</param>
/// <param name="Param_Out_Valor">Retorna um(ICaren) com um ponteiro para a interface desejada. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
String^ Param_RiidInterface,
ICaren^ Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	GUID RiidInterface = GUID_NULL;
	void* pOutValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Cria o RIID da interface.
	RiidInterface = Util.CreateGuidFromString(Param_RiidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, RiidInterface, &pOutValor);

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

	//Define o objeto na interface de saida.
	Resultado = DefinirPonteiroInterface(reinterpret_cast<IUnknown*>(pOutValor), Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como um float. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] float% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	FLOAT OutValor = 0;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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

	//Define o no parametro de saida.
	Param_Out_Valor = OutValor;

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como uma string. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_COLOR_F^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_COLOR_F OutValor = {};

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para obter o valor das propriedades de regra de preenchimento ou regra de clipe. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_FILL_MODE% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_FILL_MODE OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_FILL_MODE>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_DISPLAY% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_DISPLAY OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_DISPLAY>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para obter o valor da propriedade de transbordamento. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_OVERFLOW% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_OVERFLOW OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_OVERFLOW>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de join de linha. Este método pode ser usado para obter o valor da propriedade stroke-linejoin. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_LINE_JOIN% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_LINE_JOIN OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_LINE_JOIN>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para obter o valor da propriedade stroke-linecap. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_LINE_CAP% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_LINE_CAP OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_LINE_CAP>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para obter o valor da propriedade de visibilidade. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_VISIBILITY% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_VISIBILITY OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_VISIBILITY>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como um valor matricial. Este método pode ser usado para obter o valor de um atributo Transform ou gradientTransform. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_MATRIX_3X2_F OutValor = {};

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de tipo unitário. Este método pode ser usado para obter o valor de um atributo gradientUNITs ou clipPathUnits. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_UNIT_TYPE% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_UNIT_TYPE OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_SVG_UNIT_TYPE>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para obter o valor de um atributo spreadMethod. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_EXTEND_MODE% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_EXTEND_MODE OutValor;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = static_cast<CA_D2D1_EXTEND_MODE>(OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para obter o valor de um atributo PreserveAspectRatio. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o vlaor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_PRESERVE_ASPECT_RATIO OutValor = {};

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = Util.ConverterD2D1_SVG_PRESERVE_ASPECT_RATIOUnmanagedToManaged(&OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como um valor de comprimento. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna o valor do atributo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] CA_D2D1_SVG_LENGTH^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_LENGTH OutValor = {};

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &OutValor);

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
	Param_Out_Valor = Util.ConverterD2D1_SVG_LENGTHUnmanagedToManaged(&OutValor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgAttribute) que contém um ponteiro para o valor do atributo especificado.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] ICarenD2D1SvgAttribute^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgAttribute* pOutSvgAttribute = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &pOutSvgAttribute);

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

	//Cria a interface que vai ser retornada.
	Param_Out_Valor = gcnew CarenD2D1SvgAttribute();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutSvgAttribute, Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como uma tinta. Este método pode ser usado para obter o valor das propriedades de preenchimento ou traçado. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o valor do atributo especificado.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] ICarenD2D1SvgPaint^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgPaint* pOutSvgPaint = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &pOutSvgPaint);

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

	//Cria a interface que vai ser retornada.
	Param_Out_Valor = gcnew CarenD2D1SvgPaint();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutSvgPaint, Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como uma matriz de traço de traço de traço. Este método pode ser usado para obter o valor da propriedade stroke-dasharray. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o valor do atributo especificado.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgStrokeDashArray* pOutSvgStrokeArray = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &pOutSvgStrokeArray);

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

	//Cria a interface que vai ser retornada.
	Param_Out_Valor = gcnew CarenD2D1SvgStrokeDashArray();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutSvgStrokeArray, Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe um atributo deste elemento como pontos. Este método pode ser usado para obter o valor do atributo de pontos em um polígono ou elemento polilinha. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPointCollection) que contém um ponteiro para o valor do atributo especificado.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] ICarenD2D1SvgPointCollection^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgPointCollection* pOutSvgPointCollection = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &pOutSvgPointCollection);

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

	//Cria a interface que vai ser retornada.
	Param_Out_Valor = gcnew CarenD2D1SvgPointCollection();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutSvgPointCollection, Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo desse elemento como dados de caminho. Este método pode ser usado para obter o valor do atributo d em um elemento de Path. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Valor">Retorna uma interface(ICarenD2D1SvgPathData) que contém um ponteiro para o valor do atributo especificado.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValue(
String^ Param_NomeAtributo,
[Out] ICarenD2D1SvgPathData^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgPathData* pOutSvgPathData = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValue(pNomeAtributo, &pOutSvgPathData);

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

	//Cria a interface que vai ser retornada.
	Param_Out_Valor = gcnew CarenD2D1SvgPathData();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutSvgPathData, Param_Out_Valor);

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o comprimento da sequência de um atributo deste elemento. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Tipo">O tipo de String do atributo.</param>
/// <param name="Param_Out_LarguraValor">Retorna o comprimento do atributo. O comprimento da corda retornado não inclui espaço para o exterminador nulo.</param>
CarenResult CarenD2D1SvgElement::GetAttributeValueLength(
String^ Param_NomeAtributo,
CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
[Out] UInt32% Param_Out_LarguraValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_ATTRIBUTE_STRING_TYPE AttributeType = static_cast<D2D1_SVG_ATTRIBUTE_STRING_TYPE>(Param_Tipo);
	UINT32 OutLargura = 0;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAttributeValueLength(pNomeAtributo, AttributeType, &OutLargura);

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

	//Define o valor da largura no parametor de saida.
	Param_Out_LarguraValor = OutLargura;

Done:;
	//Libera a memória alocada para as strings
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o documento que contém este elemento.
/// </summary>
/// <param name="Param_Out_Documento">Retorna uma interface(ICarenD2D1SvgDocument) com um ponteiro para o documento que contém este elemento. Este argumento será nulo se o elemento tiver sido 
/// removido da árvore.</param>
void CarenD2D1SvgElement::GetDocument([Out] ICarenD2D1SvgDocument^% Param_Out_Documento)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgDocument* pOutDocumento = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDocument(&pOutDocumento);

	//Cria a interface a ser retornada.
	Param_Out_Documento = gcnew CarenD2D1SvgDocument();

	//Define o ponteiro na interface.
	DefinirPonteiroInterface(pOutDocumento, Param_Out_Documento);
}

/// <summary>
/// Obtém o primeiro filho deste elemento. 
/// </summary>
/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) do primeiro child deste elemento.</param>
void CarenD2D1SvgElement::GetFirstChild([Out] ICarenD2D1SvgElement^% Param_Out_Child)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFirstChild(&pOutSvgElement);

	//Cria a interface a ser retornada.
	Param_Out_Child = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface.
	DefinirPonteiroInterface(pOutSvgElement, Param_Out_Child);
}

/// <summary>
/// Obtém o ultimo filho deste elemento.  
/// </summary>
/// <param name="Param_Out_Child">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para do ultimo child deste elemento.</param>
void CarenD2D1SvgElement::GetLastChild([Out] ICarenD2D1SvgElement^% Param_Out_Child)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetLastChild(&pOutSvgElement);

	//Cria a interface a ser retornada.
	Param_Out_Child = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface.
	DefinirPonteiroInterface(pOutSvgElement, Param_Out_Child);
}

/// <summary>
/// Obtém o próximo irmão do elemento (Param_ReferenciaChild). 
/// </summary>
/// <param name="Param_ReferenciaChild">A referênciaChild deve ser um child imediato deste elemento.</param>
/// <param name="Param_Out_ProximoChild">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
/// for o ultimo child, a saída é NULA.</param>
CarenResult CarenD2D1SvgElement::GetNextChild(
ICarenD2D1SvgElement^ Param_ReferenciaChild,
[Out] ICarenD2D1SvgElement^% Param_Out_ProximoChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElementReference = NULL;
	ID2D1SvgElement* pOutSvgElementNext = NULL;

	//Recupera o ponteiro para o svg de referencia.
	Resultado = RecuperarPonteiroCaren(Param_ReferenciaChild, &pSvgElementReference);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNextChild(pSvgElementReference, &pOutSvgElementNext);

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
	Param_Out_ProximoChild = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutSvgElementNext, Param_Out_ProximoChild);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o elemento pai. 
/// </summary>
/// <param name="Param_Out_Parent">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o elemento pai.</param>
void CarenD2D1SvgElement::GetParent([Out] ICarenD2D1SvgElement^% Param_Out_Parent)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElementParent = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetParent(&pOutSvgElementParent);

	//Cria a interface a ser retornada.
	Param_Out_Parent = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface.
	DefinirPonteiroInterface(pOutSvgElementParent, Param_Out_Parent);
}

/// <summary>
/// Recebe o child anterior do elemento (Param_ReferenciaChild). 
/// </summary>
/// <param name="Param_ReferenciaChild">>A referênciaChild deve ser um child imediato deste elemento.</param>
/// <param name="Param_Out_ChildAnterior">Retorna uma interface(ICarenD2D1SvgElement) com um ponteiro para o proximo child se o (Param_ReferenciaChild) tiver um irmão. Se a (Param_ReferenciaChild)
/// for o primeiro child, a saída é NULA. </param>
CarenResult CarenD2D1SvgElement::GetPreviousChild(
ICarenD2D1SvgElement^ Param_ReferenciaChild,
[Out] ICarenD2D1SvgElement^% Param_Out_ChildAnterior)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElementReference = NULL;
	ID2D1SvgElement* pOutSvgElementNext = NULL;

	//Recupera o ponteiro para o svg de referencia.
	Resultado = RecuperarPonteiroCaren(Param_ReferenciaChild, &pSvgElementReference);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPreviousChild(pSvgElementReference, &pOutSvgElementNext);

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
	Param_Out_ChildAnterior = gcnew CarenD2D1SvgElement();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutSvgElementNext, Param_Out_ChildAnterior);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna o número de atributos especificados neste elemento. Os atributos só são considerados especificados se estiverem explicitamente definidos no elemento ou presentes dentro de um 
/// estilo inline. As propriedades que recebem seu valor através da herança CSS não são consideradas especificadas. Um atributo pode ser especificado se for definido através de uma chamada 
/// de método. Ele pode se tornar não especificado se for removido via RemoveAttribute. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de atributos especificados neste elemento.</param>
void CarenD2D1SvgElement::GetSpecifiedAttributeCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetSpecifiedAttributeCount();
}

/// <summary>
/// Obtém o nome do atributo no índice dado. 
/// </summary>
/// <param name="Param_Indice">O índice do atributo.</param>
/// <param name="Param_Out_NomeAtributo">Retorna o nome do atributo.</param>
/// <param name="Param_LarguraNome">A largura da String retornada em (Param_Out_NomeAtributo).</param>
/// <param name="Param_Out_Herdado">Retorna um valor que define se o atributo está definido para o valor herdado</param>
CarenResult CarenD2D1SvgElement::GetSpecifiedAttributeName(
UInt32 Param_Indice,
[Out] String^% Param_Out_NomeAtributo,
UInt32 Param_LarguraNome,
[Out] Boolean% Param_Out_Herdado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pOutNome = CriarStringCoTask<WCHAR>(Param_LarguraNome + 1); //Aloca mémória para Sring.
	BOOL OutHerdado = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSpecifiedAttributeName(Param_Indice, pOutNome, Param_LarguraNome, &OutHerdado);

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

	//Converte a string gerenciada para nativa e define no parametro de saida.
	Param_Out_NomeAtributo = gcnew String(pOutNome);

	//Define o valor booleano no parametro de saida.
	Param_Out_Herdado = OutHerdado? true: false;

Done:;
	//Libera a String nativa.
	DeletarStringCoTaskSafe(&pOutNome);
	
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o comprimento da sequência do nome do atributo especificado no índice dado. O comprimento da sequência de saída não inclui espaço para o exterminador nulo. 
/// </summary>
/// <param name="Param_Indice">O índice do atributo.</param>
/// <param name="Param_Out_LarguraNome">Retorna a largura do nome do atributo no indice especificado.</param>
/// <param name="Param_Out_Herdado">Retorna um valor Booleano que indica se o atributo está definido no valor herdado.</param>
CarenResult CarenD2D1SvgElement::GetSpecifiedAttributeNameLength(
UInt32 Param_Indice,
[Out] UInt32% Param_Out_LarguraNome,
[Out] Boolean% Param_Out_Herdado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32 OutLarguraNome = 0;
	BOOL OutHerdado = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSpecifiedAttributeNameLength(Param_Indice, &OutLarguraNome, &OutHerdado);

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
	Param_Out_LarguraNome = OutLarguraNome;
	Param_Out_Herdado = OutHerdado ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o nome da Tag.
/// </summary>
/// <param name="Param_Out_NomeTag">Retorna o nome da Tag.</param>
/// <param name="Param_LarguraNomeTag">O comprimento da String em (Param_Out_NomeTag). Obtenha esse valor chamando o método (GetTagNameLength).</param>
CarenResult CarenD2D1SvgElement::GetTagName(
[Out] String^% Param_Out_NomeTag,
UInt32 Param_LarguraNomeTag)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pOutTagName = CriarStringCoTask<WCHAR>(Param_LarguraNomeTag);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTagName(pOutTagName, Param_LarguraNomeTag);

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

	//Cria a string que vai ser retornada e define o valor.
	Param_Out_NomeTag = gcnew String(pOutTagName);

Done:;
	//Libera a memória para string.
	DeletarStringCoTaskSafe(&pOutTagName);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o comprimento da String do nome da Tag. 
/// </summary>
/// <param name="Param_Out_LarguraNomeTag">Retorna o comprimento da String do nome da tag. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
void CarenD2D1SvgElement::GetTagNameLength([Out] UInt32% Param_Out_LarguraNomeTag)
{
	//Chama o método para realizar a operação.
	Param_Out_LarguraNomeTag = PonteiroTrabalho->GetTagNameLength();
}

/// <summary>
/// Obtém o valor de um elemento de conteúdo de texto. 
/// </summary>
/// <param name="Param_Out_ValorElemento">Retorna o valor do elemento de conteúdo texto.</param>
/// <param name="Param_LarguraValor">O comprimento da String em (Param_Out_ValorElemento). Obtenha esse valor chamando o método (GetTextValueLength).</param>
CarenResult CarenD2D1SvgElement::GetTextValue(
[Out] String^% Param_Out_ValorElemento,
UInt32 Param_LarguraValor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pOutTagName = CriarStringCoTask<WCHAR>(Param_LarguraValor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTextValue(pOutTagName, Param_LarguraValor);

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

	//Cria a string que vai ser retornada e define o valor.
	Param_Out_ValorElemento = gcnew String(pOutTagName);

Done:;
	//Libera a memória para string.
	DeletarStringCoTaskSafe(&pOutTagName);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o comprimento do valor do conteúdo do texto. 
/// </summary>
/// <param name="Param_Out_LarguraValorElemento">Retorna o comprimento do valor do conteúdo do texto. O comprimento da String retornado não inclui espaço para o terminador nulo.</param>
void CarenD2D1SvgElement::GetTextValueLength([Out] UInt32% Param_Out_LarguraValorElemento)
{
	//Chama o método para realizar a operação.
	Param_Out_LarguraValorElemento = PonteiroTrabalho->GetTextValueLength();
}

/// <summary>
/// Retorna um booleano indicando se esse elemento tem filhos. 
/// </summary>
/// <param name="Param_Out_ElementoCrianca">Retorna TRUE se este elemento tiver filhos.</param>
void CarenD2D1SvgElement::HasChildren([Out] Boolean% Param_Out_ElementoCrianca)
{
	//Variaveis a serem utilizadas.
	BOOL OutHasChildren = FALSE;

	//Chama o método para realizar a operação.
	OutHasChildren = PonteiroTrabalho->HasChildren();

	//Define no parametro de saida.
	Param_Out_ElementoCrianca = OutHasChildren ? true : false;
}

/// <summary>
/// Insere (Param_NewChild) como um child deste elemento, antes do elemento (Param_ReferenceChild). Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da inserção. 
/// </summary>
/// <param name="Param_NewChild">O elemento a ser inserido.</param>
/// <param name="Param_NewChild">O elemento que a child deve ser inserida antes. Se este parametro for NULO, o (Param_NewChild) será colocado como o último child. Se a (Param_ReferenceChild) não for NULA, deve ser um child imediato deste elemento.</param>
CarenResult CarenD2D1SvgElement::InsertChildBefore(
ICarenD2D1SvgElement^ Param_NewChild,
ICarenD2D1SvgElement^ Param_ReferenceChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pNewChild = NULL;
	ID2D1SvgElement* pReferenceChild = NULL;

	//Recupera o ponteiro para a nova interface a ser inserida.
	Resultado = RecuperarPonteiroCaren(Param_NewChild, &pNewChild);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a referencia.
	Resultado = RecuperarPonteiroCaren(Param_ReferenceChild, &pReferenceChild);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InsertChildBefore(pNewChild, pReferenceChild);

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
/// Retorna uma indicação booleana se o atributo estiver explicitamente definido no elemento. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo.</param>
/// <param name="Param_Out_Herdado">Retorna um valor booleano que indica se o atributo está definido para o valor herdado.</param>
/// <param name="Param_Out_Especificado">Retorna TRUE se o atributo é explicitamente definido no elemento ou se ele está presente dentro de um estilo inline. Retorna FALSE se o atributo não for um atributo válido neste elemento.</param>
void CarenD2D1SvgElement::IsAttributeSpecified(
String^ Param_NomeAtributo,
[Out] Boolean% Param_Out_Herdado,
[Out] Boolean% Param_Out_Especificado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	BOOL OutHerdado = FALSE;
	BOOL OutEspecificado = FALSE;

	//Converte o nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	OutEspecificado = PonteiroTrabalho->IsAttributeSpecified(pNomeAtributo, &OutHerdado);

	//Define os valores nos parametros de saida.
	Param_Out_Herdado = OutHerdado? true: false;
	Param_Out_Especificado = OutEspecificado ? true : false;

	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);
}

/// <summary>
/// Retorna um boolean indicando que este elemento representa conteúdo de texto. 
/// </summary>
/// <param name="Param_Out_Texto">Retorna TRUE se esse elemento representar conteúdo de texto, por exemplo, o conteúdo de um elemento 'título' ou 'desc'. O conteúdo do texto não tem um nome de tag.</param>
void CarenD2D1SvgElement::IsTextContent([Out] Boolean% Param_Out_Texto)
{
	//Variaveis a serem utilizadas.
	BOOL OutTexto = 0;

	//Chama o método para realizar a operação.
	OutTexto = PonteiroTrabalho->IsTextContent();

	//Define no parametro de saida.
	Param_Out_Texto = OutTexto ? true : false;
}

/// <summary>
/// Remove o atributo deste elemento. Também remove esse atributo de dentro de um estilo inline se presente. 
/// </summary>
/// <param name="Param_NomeAtributo">O nome do atributo para remover.</param>
CarenResult CarenD2D1SvgElement::RemoveAttribute(String^ Param_NomeAtributo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAttribute(pNomeAtributo);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove o (Param_OldChild) da árvore. Filhos de (Param_OldChild) permanecem filhos de (Param_OldChild). 
/// </summary>
/// <param name="Param_OldChild"></param>
CarenResult CarenD2D1SvgElement::RemoveChild(ICarenD2D1SvgElement^ Param_OldChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElement = NULL;

	//Recupera o ponteiro para a criança antiga.
	Resultado = RecuperarPonteiroCaren(Param_OldChild, &pSvgElement);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveChild(pSvgElement);

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
/// Substitui o elemento (Param_OldChild) pelo (Param_NewChild). Esta operação remove o (Param_OldChild) da árvore. Se o elemento (Param_NewChild) já tiver um pai, ele será removido deste pai como parte da operação de substituição.
/// </summary>
/// <param name="Param_NewChild">O elemento a ser inserido.</param>
/// <param name="Param_OldChild">O elemento child a ser substituído. O elemento (Param_OldChild) deve ser uma child imediata deste elemento.</param>
CarenResult CarenD2D1SvgElement::ReplaceChild(
ICarenD2D1SvgElement^ Param_NewChild,
ICarenD2D1SvgElement^ Param_OldChild)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElementNew = NULL;
	ID2D1SvgElement* pSvgElementOld = NULL;

	//Recupera o ponteiro para a criança nova.
	Resultado = RecuperarPonteiroCaren(Param_NewChild, &pSvgElementNew);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a criança antiga.
	Resultado = RecuperarPonteiroCaren(Param_OldChild, &pSvgElementOld);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReplaceChild(pSvgElementNew, pSvgElementOld);

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
/// Define um atributo deste elemento usando uma string. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Tipo">O tipo da String.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE Param_Tipo,
String^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_ATTRIBUTE_STRING_TYPE AttributeType = static_cast<D2D1_SVG_ATTRIBUTE_STRING_TYPE>(Param_Tipo);
	PWSTR pValor = NULL;

	//Converte as string.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);
	pValor = Util.ConverterStringToWCHAR(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, AttributeType, pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);
	DeletarTextoAlocadoSafe(&pValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento usando um tipo POD. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Tipo">O tipo POD do atributo.</param>
/// <param name="Param_Valor">Uma interface(ICaren) que contém um ponteiro(void*) do novo valor do atributo.</param>
/// <param name="Param_Size">O tamanho do novo valor em bytes.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_ATTRIBUTE_POD_TYPE Param_Tipo,
ICaren^ Param_Valor,
UInt32 Param_Size)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_ATTRIBUTE_POD_TYPE AttributeType = static_cast<D2D1_SVG_ATTRIBUTE_POD_TYPE>(Param_Tipo);
	PVOID pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Recupera o ponteiro para o valor.
	Resultado = RecuperarPonteiroCaren(Param_Valor, &pValor);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, AttributeType, pValor, Param_Size);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento usando uma interface. 
/// Um determinado objeto atributo só pode ser definido em um elemento em um local de atributo de cada vez.
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">Uma interface(ICarenD2D1SvgAttribute) que contém um ponteiro para o novo vlaor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
ICarenD2D1SvgAttribute^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	ID2D1SvgAttribute* pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Recupera o ponteiro para o valor.
	Resultado = RecuperarPonteiroCaren(Param_Valor, &pValor);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento usando um float. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
float Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, Param_Valor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como uma cor. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_COLOR_F^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_COLOR_F* pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Converte o valor da estrutura.
	pValor = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, *pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um modo de preenchimento. Este método pode ser usado para definir o valor das propriedades 'regra de preenchimento' ou 'regra de clipe'. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_FILL_MODE Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_FILL_MODE>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo deste elemento como um valor de exibição. Este método pode ser usado para obter o valor da propriedade de exibição. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_DISPLAY Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_DISPLAY>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de transbordamento. Este método pode ser usado para definir o valor da propriedade de transbordamento. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_OVERFLOW Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_OVERFLOW>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de join de linha. Este método pode ser usado para definir o valor da propriedade stroke-linejoin. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_LINE_JOIN Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_LINE_JOIN>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de limite de linha. Este método pode ser usado para definir o valor da propriedade stroke-linecap. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_LINE_CAP Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_LINE_CAP>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo desse elemento como um valor de visibilidade. Este método pode ser usado para definir o valor da propriedade de visibilidade. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_VISIBILITY Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_VISIBILITY>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo desse elemento como um valor de matriz. Este método pode ser usado para definir o valor de um atributo Transform ou gradientTransform. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_MATRIX_3X2_F^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_MATRIX_3X2_F* pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Converte a estrutura.
	pValor = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, *pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Libera a memória para estrutura
	DeletarEstruturaSafe(&pValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de tipo de unidade. Este método pode ser usado para definir o valor de um atributo gradientUNITs ou clipPathUnits. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_UNIT_TYPE Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_SVG_UNIT_TYPE>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de modo estendido. Este método pode ser usado para definir o valor de um atributo spreadMethod. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_EXTEND_MODE Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, static_cast<D2D1_EXTEND_MODE>(Param_Valor));

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Retorna o resultado.
	return Resultado;

}

/// <summary>
/// Define um atributo deste elemento como um valor de proporção de preservação. Este método pode ser usado para definir o valor de um atributo PreserveAspectRatio. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_PRESERVE_ASPECT_RATIO^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_PRESERVE_ASPECT_RATIO* pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Converte a estrutura.
	pValor = Util.ConverterD2D1_SVG_PRESERVE_ASPECT_RATIOManagedToUnmanaged(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, *pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Libera a memória para estrutura
	DeletarEstruturaSafe(&pValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define um atributo deste elemento como um valor de comprimento. 
/// </summary>
/// <param name="Param_NomeAtributo">Nome do atributo para definir.</param>
/// <param name="Param_Valor">O novo valor do atributo.</param>
CarenResult CarenD2D1SvgElement::SetAttributeValue(
String^ Param_NomeAtributo,
CA_D2D1_SVG_LENGTH^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeAtributo = NULL;
	D2D1_SVG_LENGTH* pValor = NULL;

	//Converte a string do nome do atributo.
	pNomeAtributo = Util.ConverterStringToWCHAR(Param_NomeAtributo);

	//Converte a estrutura.
	pValor = Util.ConverterD2D1_SVG_LENGTHManagedToUnmanaged(Param_Valor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAttributeValue(pNomeAtributo, *pValor);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pNomeAtributo);

	//Libera a memória para estrutura
	DeletarEstruturaSafe(&pValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o valor de um elemento de conteúdo de texto. 
/// </summary>
/// <param name="Param_Texto">O novo valor do elemento conteúdo de texto.</param>
/// <param name="Param_LarguraTexto">A largura da String em (Param_Texto).</param>
CarenResult CarenD2D1SvgElement::SetTextValue(
String^ Param_Texto,
UInt32 Param_LarguraTexto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pTexto = NULL;

	//Converte a string gerenciada para a nativa.
	pTexto = Util.ConverterStringToWCHAR(Param_Texto);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTextValue(pTexto, Param_LarguraTexto);

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
	//Libera a memória para a string.
	DeletarTextoAlocadoSafe(&pTexto);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgElement::GetFactory(ICaren^ Param_Out_Factory)
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