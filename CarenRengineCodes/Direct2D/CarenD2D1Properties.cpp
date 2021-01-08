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
#include "CarenD2D1Properties.h"

//Destruidor.
CarenD2D1Properties::~CarenD2D1Properties()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1Properties::CarenD2D1Properties()
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
CarenResult CarenD2D1Properties::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenD2D1Properties::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1Properties*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1Properties::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1Properties*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1Properties::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1Properties::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1Properties::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1Properties::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1Properties::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Properties::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Properties::LiberarReferencia()
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
void CarenD2D1Properties::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Properties();
}



// Métodos da interface proprietária(ICarenD2D1Properties)


/// <summary>
/// Obtém o número de propriedades de alto nível. 
/// </summary>
/// <param name="Param_Out_Quantidade"> retorna o número de propriedades personalizadas (não-sistema) que podem ser acessadas pelo objeto.</param>
void CarenD2D1Properties::GetPropertyCount([Out] UInt32% Param_Out_Quantidade)
{
	//Variaveis a serem utilizadas.
	UINT32 OutPropCount = 0;

	//Chama o método para realizar a operação.
	OutPropCount = PonteiroTrabalho->GetPropertyCount();

	//Define no parametro de saida.
	Param_Out_Quantidade = OutPropCount;
}

/// <summary>
/// Obtém o índice correspondente ao nome da propriedade dada.
/// Se a propriedade não existe, então esse método retorna D2D1_INVALID_PROPERTY_INDEX. Esse valor reservado nunca irá mapear para um índice válido, e fará com 
/// que os valores NULO ou sentinela sejam devolvidos 
/// de outras partes da interface da propriedade.
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para recuperar.</param>
/// <param name="Param_Out_Index">Retorna o índice do nome da propriedade correspondente.</param>
void CarenD2D1Properties::GetPropertyIndex(
String^ Param_NomePropriedade,
[Out] UInt32% Param_Out_Index)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomePropriedade = NULL;
	UINT32 OutIndex = 0;

	//Converte a string para a nativa.
	pNomePropriedade = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Chama o método para realizar a operação.
	OutIndex = PonteiroTrabalho->GetPropertyIndex(pNomePropriedade);

	//Define no parametro de saida.
	Param_Out_Index = OutIndex;

	//Libera a memória para a  string
	DeletarStringAllocatedSafe(&pNomePropriedade);
}

/// <summary>
/// Obtém o nome da propriedade que corresponde ao índice dado.
/// </summary>
/// <param name="Param_Index">O índice da propriedade para a qual o nome está sendo devolvido.</param>
/// <param name="Param_Out_Nome">Quando este método retorna, contém o nome que está sendo recuperado.</param>
/// <param name="Param_SizeNome">O número de caracteres no (Param_Out_Nome).</param>
CarenResult CarenD2D1Properties::GetPropertyName(
UInt32 Param_Index,
[Out] String^% Param_Out_Nome,
UInt32 Param_SizeNome)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pInOutNomePropriedade = NULL;

	//Aloca a string que vai conter os dados.
	pInOutNomePropriedade = (WCHAR*)CoTaskMemAlloc(static_cast<SIZE_T>(Param_SizeNome + 1));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPropertyName(Param_Index, pInOutNomePropriedade, Param_SizeNome);

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

	//Converte a string nativa para gerenciada.
	Param_Out_Nome = gcnew String(pInOutNomePropriedade);

Done:;
	//Libera a memória para o wchar*
	if (ObjetoValido(pInOutNomePropriedade))
	{
		//Libera a memória alocada.
		CoTaskMemFree(pInOutNomePropriedade);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de caracteres para o nome da propriedade dado. 
/// </summary>
/// <param name="Param_Index">O índice do nome da propriedade para recuperar.</param>
/// <param name="Param_Out_SizeNome">Retorna o tamanho em caracteres do nome correspondente ao índice de propriedade dado, ou zero se o índice de propriedade não existir.</param>
void CarenD2D1Properties::GetPropertyNameLength(
UInt32 Param_Index,
[Out] UInt32% Param_Out_SizeNome)
{
	//Variaveis a serem utilizadas.
	UINT32 OutNameLenght = 0;

	//Chama o método para realizar a operação.
	OutNameLenght = PonteiroTrabalho->GetPropertyNameLength(Param_Index);

	//Define o valor no parametro de saida.
	Param_Out_SizeNome = OutNameLenght;
}

/// <summary>
/// Obtém as sub propriedades da propriedade fornecida por índice. 
/// </summary>
/// <param name="Param_Index">O índice das sub propriedades a serem recuperadas.</param>
/// <param name="Param_Out_SubPropriedades">Quando este método retorna, contém um ponteiro para as subpropriedades na interface (ICarenD2D1Properties).</param>
CarenResult CarenD2D1Properties::GetSubProperties(
UInt32 Param_Index,
[Out] ICarenD2D1Properties^% Param_Out_SubPropriedades)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Properties* pOutProps = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSubProperties(Param_Index, &pOutProps);

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
	Param_Out_SubPropriedades = gcnew CarenD2D1Properties();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutProps,Param_Out_SubPropriedades, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a D2D1_PROPERTY_TYPE da propriedade selecionada. 
/// </summary>
/// <param name="Param_Index">O índice da propriedade para o qual o tipo será recuperado.</param>
/// <param name="Param_Out_Tipo">Retorna um enum(CA_D2D1_PROPERTY_TYPE) para o tipo da propriedade.</param>
void CarenD2D1Properties::GetType(
UInt32 Param_Index,
[Out] CA_D2D1_PROPERTY_TYPE% Param_Out_Tipo)
{
	//Variaveis a serem utilizadas.
	D2D1_PROPERTY_TYPE OutPropType;

	//Chama o método para realizar a operação.
	OutPropType = PonteiroTrabalho->GetType(Param_Index);

	//Converte e define no parametro de saida.
	Param_Out_Tipo = static_cast<CA_D2D1_PROPERTY_TYPE>(OutPropType);
}

/// <summary>
/// Obtém o valor da propriedade especificada por índice. 
/// </summary>
/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
/// <param name="Param_Tipo">TBD</param>
/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
CarenResult CarenD2D1Properties::GetValue(
UInt32 Param_Index,
CA_D2D1_PROPERTY_TYPE Param_Tipo,
[Out] ICarenBuffer^% Param_Out_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PointerToBuffer = IntPtr::Zero;

	//Cria a interface de buffer que vai receber os dados.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Cria o ponteiro para o buffer.
	Param_Out_Buffer->CriarBuffer(Param_BufferSize);

	//Recupera um ponteiro para o buffer.
	Resultado = Param_Out_Buffer->ObterPonteiroInterno(PointerToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValue(Param_Index, static_cast<D2D1_PROPERTY_TYPE>(Param_Tipo), Util.ConverterIntPtrTo<PBYTE>(PointerToBuffer), Param_BufferSize);

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
/// Obtém o valor da propriedade especificada por índice.
/// </summary>
/// <param name="Param_Index">O índice da propriedade a partir do qual os dados devem ser obtidos.</param>
/// <param name="Param_Out_Buffer">Quando este método retorna, contém um ponteiro aos dados solicitados.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
CarenResult CarenD2D1Properties::GetValue(
UInt32 Param_Index,
[Out] ICarenBuffer^% Param_Out_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PointerToBuffer = IntPtr::Zero;

	//Cria a interface de buffer que vai receber os dados.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Cria o ponteiro para o buffer.
	Param_Out_Buffer->CriarBuffer(Param_BufferSize);

	//Recupera um ponteiro para o buffer.
	Resultado = Param_Out_Buffer->ObterPonteiroInterno(PointerToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValue(Param_Index, Util.ConverterIntPtrTo<PBYTE>(PointerToBuffer), Param_BufferSize);

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
/// Obtém o valor da propriedade pelo nome.
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
/// <param name="Param_Tipo">TBD</param>
/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
CarenResult CarenD2D1Properties::GetValueByName(
String^ Param_NomePropriedade,
CA_D2D1_PROPERTY_TYPE Param_Tipo,
[Out] ICarenBuffer^% Param_Out_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeProp = NULL;
	D2D1_PROPERTY_TYPE TipoProp = static_cast<D2D1_PROPERTY_TYPE>(Param_Tipo);
	IntPtr PointerToBuffer = IntPtr::Zero;

	//Converte a string gerenciada para a nativa.
	pNomeProp = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Cria a interface para o buffer que vai receber os dados.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Cria o buffer com o tamanho indicado pelo user.
	Resultado = Param_Out_Buffer->CriarBuffer(Param_BufferSize);

	//Sai do método em caso de erro
	SairOnError(Resultado);	

	//Recupera o ponteiro para o buffer.
	Resultado = Param_Out_Buffer->ObterPonteiroInterno(PointerToBuffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValueByName(pNomeProp, TipoProp, Util.ConverterIntPtrTo<PBYTE>(PointerToBuffer), Param_BufferSize);

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
	DeletarStringAllocatedSafe(&pNomeProp);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor da propriedade pelo nome.
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para conseguir.</param>
/// <param name="Param_Out_Buffer">Quando este método retorna, contém o buffer com o valor de dados.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem recuperados.</param>
CarenResult CarenD2D1Properties::GetValueByName(
String^ Param_NomePropriedade,
[Out] ICarenBuffer^% Param_Out_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeProp = NULL;
	IntPtr PointerToBuffer = IntPtr::Zero;

	//Converte a string gerenciada para a nativa.
	pNomeProp = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Cria a interface para o buffer que vai receber os dados.
	Param_Out_Buffer = gcnew CarenBuffer();

	//Cria o buffer com o tamanho indicado pelo user.
	Resultado = Param_Out_Buffer->CriarBuffer(Param_BufferSize);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o buffer.
	Resultado = Param_Out_Buffer->ObterPonteiroInterno(PointerToBuffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValueByName(pNomeProp, Util.ConverterIntPtrTo<PBYTE>(PointerToBuffer), Param_BufferSize);

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
	DeletarStringAllocatedSafe(&pNomeProp);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tamanho do valor da propriedade em bytes, usando o índice de propriedade. 
/// </summary>
/// <param name="Param_Index">O índice da propriedade.</param>
/// <param name="Param_Out_Size">Retorna o tamanho do valor em bytes, usando o índice de propriedade</param>
void CarenD2D1Properties::GetValueSize(
UInt32 Param_Index,
[Out] UInt32% Param_Out_Size)
{
	//Chama o método para realizar a operação.
	Param_Out_Size = PonteiroTrabalho->GetValueSize(Param_Index);
}

/// <summary>
/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
/// </summary>
/// <param name="Param_Index">O índice da propriedade para definir.</param>
/// <param name="Param_Tipo">TBD</param>
/// <param name="Param_Buffer">Os dados a serem definidos.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
CarenResult CarenD2D1Properties::SetValue(
UInt32 Param_Index,
CA_D2D1_PROPERTY_TYPE Param_Tipo,
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_PROPERTY_TYPE TipoProp = static_cast<D2D1_PROPERTY_TYPE>(Param_Tipo);
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Recuper ao ponteiro para o buffer.
	Resultado = Param_Buffer->ObterPonteiroInterno(PonteiroToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValue(Param_Index, TipoProp, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer), Param_BufferSize);

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
/// Define a propriedade correspondente por índice. Se a propriedade não existir, o pedido é ignorado e D2DERR_INVALID_PROPERTY é devolvido.
/// Qualquer erro que não esteja no conjunto padrão retornado por uma implementação de propriedade será mapeado na faixa de erro padrão.
/// </summary>
/// <param name="Param_Index">O índice da propriedade para definir.</param>
/// <param name="Param_Buffer">Os dados a serem definidos.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
CarenResult CarenD2D1Properties::SetValue(
UInt32 Param_Index,
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Recuper ao ponteiro para o buffer.
	Resultado = Param_Buffer->ObterPonteiroInterno(PonteiroToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValue(Param_Index, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer), Param_BufferSize);

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
/// Define a propriedade nomeada ao valor dado. 
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
/// <param name="Param_Tipo">TBD</param>
/// <param name="Param_Buffer">Os dados a serem definidos.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
CarenResult CarenD2D1Properties::SetValueByName(
String^ Param_NomePropriedade,
CA_D2D1_PROPERTY_TYPE Param_Tipo,
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeProp = NULL;
	D2D1_PROPERTY_TYPE TipoProp = static_cast<D2D1_PROPERTY_TYPE>(Param_Tipo);
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Converte a string gerenciada para a nativa.
	pNomeProp = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Recuper ao ponteiro para o buffer.
	Resultado = Param_Buffer->ObterPonteiroInterno(PonteiroToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValueByName(pNomeProp, TipoProp, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer), Param_BufferSize);

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
	DeletarStringAllocatedSafe(&pNomeProp);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define a propriedade nomeada ao valor dado. 
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
/// <param name="Param_Buffer">Os dados a serem definidos.</param>
/// <param name="Param_BufferSize">O número de bytes nos dados a serem definidos.</param>
CarenResult CarenD2D1Properties::SetValueByName(
String^ Param_NomePropriedade,
ICarenBuffer^ Param_Buffer,
UInt32 Param_BufferSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeProp = NULL;
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Converte a string gerenciada para a nativa.
	pNomeProp = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Recuper ao ponteiro para o buffer.
	Resultado = Param_Buffer->ObterPonteiroInterno(PonteiroToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValueByName(pNomeProp, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer), Param_BufferSize);

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
	DeletarStringAllocatedSafe(&pNomeProp);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Templete - SetValueByName(PCWSTR,T)) - Define a propriedade nomeada ao valor dado. Esta é uma sobrecarga de modelo. 
/// </summary>
/// <param name="Param_NomePropriedade">O nome da propriedade para definir.</param>
/// <param name="Param_Valor">Os dados a serem definidos. Como o método converte os dados para um BYTE*, não a necessidade de um ICaren.</param>
CarenResult CarenD2D1Properties::SetValueByName(
String^ Param_NomePropriedade,
ICarenBuffer^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pNomeProp = NULL;
	IntPtr PonteiroToBuffer = IntPtr::Zero;

	//Converte a string gerenciada para a nativa.
	pNomeProp = Util.ConverterStringToWCHAR(Param_NomePropriedade);

	//Recuper ao ponteiro para o buffer.
	Resultado = Param_Valor->ObterPonteiroInterno(PonteiroToBuffer);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValueByName(pNomeProp, Util.ConverterIntPtrTo<PBYTE>(PonteiroToBuffer));

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
	DeletarStringAllocatedSafe(&pNomeProp);

	//Retorna o resultado.
	return Resultado;
}