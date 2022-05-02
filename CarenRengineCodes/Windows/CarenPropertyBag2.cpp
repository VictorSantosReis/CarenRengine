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
#include "CarenPropertyBag2.h"

//Destruidor.
CarenPropertyBag2::~CarenPropertyBag2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenPropertyBag2::CarenPropertyBag2()
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
CarenResult CarenPropertyBag2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenPropertyBag2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IPropertyBag2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IPropertyBag2**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenPropertyBag2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IPropertyBag2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IPropertyBag2**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenPropertyBag2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenPropertyBag2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenPropertyBag2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenPropertyBag2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenPropertyBag2::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenPropertyBag2::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenPropertyBag2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenPropertyBag2();
}



// Métodos da interface proprietária(ICarenPropertyBag2)


/// <summary>
/// (CountProperties) - Obtém o número de propriedades no bag da propriedade.
/// </summary>
/// <param name="Param_Out_Quantidade">Recebe o numero de propriedades presentes na bag.</param>
CarenResult CarenPropertyBag2::CountProperties([Out] UInt32% Param_Out_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ULONG vi_OutCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CountProperties(&vi_OutCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o valor e define no parametro de saida.
	Param_Out_Quantidade = static_cast<UInt32>(vi_OutCount);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetPropertyInfo) - Obtém informações para propriedades em um bag de propriedade sem realmente obter essas propriedades. 
/// </summary>
/// <param name="Param_ID">O índice baseado em zero da primeira propriedade para a qual as informações são solicitadas. Este argumento deve ser menor que o número de propriedades recuperadas por ICarenPropertyBag2::CountProperties.</param>
/// <param name="Param_Quantidade">O número de propriedades sobre as quais obter informações.Este argumento especifica o número de elementos da matriz em (Param_Out_ArrayPropBags).</param>
/// <param name="Param_Out_ArrayPropBags">Retorna uma matriz de estruturas CA_PROPBAG2 que recebem as informações para as propriedades.</param>
/// <param name="Param_Out_Quantiade">Recebe o número de propriedades para as quais as informações foram recuperadas na matriz (Param_Out_ArrayPropBags).</param>
CarenResult CarenPropertyBag2::GetPropertyInfo(
UInt32 Param_ID,
UInt32 Param_Quantidade,
[Out] cli::array<Estruturas::CA_PROPBAG2^>^% Param_Out_ArrayPropBags,
[Out] UInt32% Param_Out_Quantiade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PROPBAG2* vi_pOutArrayPropBags = CriarMatrizEstruturas<PROPBAG2>(Param_Quantidade);
	ULONG vi_OutCountProps = 0;

	//Inicializa os membros.
	for (UInt32 i = 0; i < Param_Quantidade; i++)
	{
		//Inicializa a estrutura no index.
		ZeroMemory(&vi_pOutArrayPropBags[i], sizeof(PROPBAG2));
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetPropertyInfo(
		static_cast<ULONG>(Param_ID), 
		static_cast<ULONG>(Param_Quantidade), 
		vi_pOutArrayPropBags,
		&vi_OutCountProps);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a matriz que vai retornar as informações
	Param_Out_ArrayPropBags = gcnew cli::array<Estruturas::CA_PROPBAG2^>(vi_OutCountProps);

	//Faz um for para converter os dados e LIBERAR A MEMÓRIA DO PARAMETRO (pstrName de cada estrutura na matriz gerenciada)
	for (ULONG i = 0; i < vi_OutCountProps; i++)
	{
		//Converte e define no parametro.
		Param_Out_ArrayPropBags[i] = Util.ConverterPROPBAG2UnmanagedToManaged(&vi_pOutArrayPropBags[i]);

		//Libera o membro pstrName
		if (ObjetoValido(vi_pOutArrayPropBags[i].pstrName))
			CoTaskMemFree(vi_pOutArrayPropBags[i].pstrName);
	}

	//Define a quantidade de elementos no array
	Param_Out_Quantiade = static_cast<UInt32>(vi_OutCountProps);

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarMatrizEstruturasSafe(&vi_pOutArrayPropBags);

	//Retorna o resultado.
	return Resultado;
}


/// <summary>
/// (LoadObject) - Faz com que o bag de propriedade instrua um objeto de propriedade que foi criado anteriormente e inicializado para ler suas propriedades persistentes. 
/// </summary>
/// <param name="Param_EnderecoNome">O do nome do objeto da propriedade.</param>
/// <param name="Param_Hint">Um valor inteiro que foi recuperado usando ICarenPropertyBag2::GetPropertyInfo. Este argumento é opcional e deve ser zero, se o valor não for conhecido ou usado.</param>
/// <param name="Param_UnkObjeto">O endereço da interface IUnknown do objeto. Este argumento não pode ser NULO.</param>
/// <param name="Param_ErrorLog">Uma interface IErrorlog na qual a bag de propriedade armazena quaisquer erros que ocorram durante a carga. Este argumento pode ser NULO; nesse caso, o chamador não recebe erros de registro.</param>
CarenResult CarenPropertyBag2::LoadObject(
String^ Param_EnderecoNome,
UInt32 Param_Hint,
ICaren^ Param_UnkObjeto,
ICaren^ Param_ErrorLog)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCOLESTR vi_pEnderecoNome = Nulo;
	IUnknown* vi_pUnkObjeto = Nulo;
	IErrorLog* vi_pErrorLog = Nulo; //Pode ser NULO.

	//Converte a string.
	vi_pEnderecoNome = Util.ConverterStringToBSTR(Param_EnderecoNome);

	//Recupera o ponteiro para a interface unknown
	CarenGetPointerFromICarenSafe(Param_UnkObjeto, vi_pUnkObjeto);

	//Recupera o ponteiro para a interface de log se fornecido.
	if(ObjetoGerenciadoValido(Param_ErrorLog))
		CarenGetPointerFromICarenSafe(Param_ErrorLog, vi_pErrorLog);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LoadObject(vi_pEnderecoNome, static_cast<DWORD>(Param_Hint), vi_pUnkObjeto, vi_pErrorLog);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringBSTRSafe(const_cast<OLECHAR**>(&vi_pEnderecoNome));

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Read) - Faz com que uma ou mais propriedades sejam lidas do bag de propriedade.
/// </summary>
/// <param name="Param_Quantidade">O número de propriedades para ler. Este argumento especifica o número de elementos nas matrizes Param_ArrayPropBagsRequest, Param_Out_VarValue e Param_Out_HRESULTArray.</param>
/// <param name="Param_ArrayPropBagsRequest">uma matriz de estruturas CA_PROPBAG2 que especificam as propriedades solicitadas. O membro vt e o membro pstrName dessas 
/// estruturas devem ser preenchidos antes que este método possa ser chamado. O membro dwHint dessas estruturas é opcional. Este argumento não pode ser NULO.</param>
/// <param name="Param_InterfaceErro">Uma interface IErrorlog na qual a bolsa de propriedade armazena quaisquer erros que ocorram durante as leituras. Este argumento pode ser NULO; 
/// nesse caso, o chamador não recebe erros de registro.</param>
/// <param name="Param_Out_VarValue">Retorna uma matriz de estruturas CA_VARIANT que recebem os valores da propriedade. O interlocutor não precisa inicializar essas estruturas antes de ligar para 
/// ICarenPropertyBag2::Read. O método ICarenPropertyBag2::Read preenche o campo de tipo e o campo de valor nessas estruturas antes de retornar.</param>
/// <param name="Param_Out_HRESULTArray">Retorna uma matriz de valores HRESULT que recebe o resultado de cada propriedade lido.</param>
CarenResult CarenPropertyBag2::Read(
	UInt32 Param_Quantidade,
	cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
	ICaren^ Param_InterfaceErro,
	[Out] cli::array<Estruturas::CA_VARIANT^>^% Param_Out_VarValue,
	[Out] cli::array<Int32>^% Param_Out_HRESULTArray)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PROPBAG2* vi_pArrayPropBagRequest = CriarMatrizEstruturas<PROPBAG2>(Param_Quantidade);
	PROPBAG2* vi_pAuxiliar = Nulo;
	IErrorLog* vi_pErrorLog = Nulo; //Pode ser NULO.
	VARIANT* vi_pOutArrayValues = CriarMatrizEstruturas<VARIANT>(Param_Quantidade);
	HRESULT* vi_pOutArrayHResults = CriarMatrizEstruturas<HRESULT>(Param_Quantidade);

	//COPIA OS DADOS DA MATRIZ GERENCIADA PARA NATIVA E INICIA AS VARIANTS DA MATRIZ DE SAIDA(vi_pOutArrayValues).
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte a estrutura no index especificado.
		vi_pAuxiliar = Util.ConverterPROPBAG2ManagedToUnamaged(Param_ArrayPropBagsRequest[i]);

		//Define no array nativo.
		vi_pArrayPropBagRequest[i] = *vi_pAuxiliar;

		//Libera a memória utilizada pela estrutura.
		DeletarEstruturaSafe(&vi_pAuxiliar);

		//Inicializa a variant da matriz de saida.
		VariantInit(&vi_pOutArrayValues[i]);
	}

	//Recupera o ponteiro para a interface de log se fornecido.
	if (ObjetoGerenciadoValido(Param_InterfaceErro))
		CarenGetPointerFromICarenSafe(Param_InterfaceErro, vi_pErrorLog);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Read(
		static_cast<ULONG>(Param_Quantidade),
		vi_pArrayPropBagRequest,
		vi_pErrorLog,
		vi_pOutArrayValues,
		vi_pOutArrayHResults);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria as matrizes que seram retornadas.
	Param_Out_VarValue = gcnew cli::array<CA_VARIANT^>(Param_Quantidade);
	Param_Out_HRESULTArray = gcnew cli::array<Int32>(Param_Quantidade);

	//FAZ UM FOR PARA CONVERTER OS DADOS DAS MATRIZES (vi_pOutArrayValues, vi_pOutArrayHResults) 
	//NATIVAS PARA A GERENCIADA E LIBERA OS DADOS DAS VARIANTS
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Cria uma cópia da variante.
		Param_Out_VarValue[i] = gcnew CA_VARIANT(&vi_pOutArrayValues[i], true);

		//Converte o valor da matriz de HRESULTS nativa para a gerenciada do parametro de saida.
		Param_Out_HRESULTArray[i] = static_cast<Int32>(vi_pOutArrayHResults[i]);
	}

	//Libera o array de variants
	ClearVariantArray(vi_pOutArrayValues, Param_Quantidade);

Done:;
	//Libera a memória utilizada pelas matrizes.
	DeletarMatrizEstruturasSafe(&vi_pArrayPropBagRequest);
	DeletarMatrizEstruturasSafe(&vi_pOutArrayValues);
	DeletarMatrizEstruturasSafe(&vi_pOutArrayHResults);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Write) - Faz com que uma ou mais propriedades sejam salvas no bag da propriedade.
/// </summary>
/// <param name="Param_Quantidade">O número de propriedades para salvar. Este argumento especifica o número de elementos nas matrizes Param_ArrayPropBagsRequest e Param_VarValue.</param>
/// <param name="Param_ArrayPropBagsRequest">Uma matriz de estruturas CA_PROPBAG2 que especificam as propriedades salvas. O membro pstrName dessas estruturas deve ser preenchido antes que este método seja 
/// chamado. O membro dwHint dessas estruturas é opcional. Este argumento não pode ser NULO.</param>
/// <param name="Param_VarValue">Uma matriz de estruturas CA_VARIANT que contêm os valores das propriedades para salvar. Este argumento não pode ser NULO.</param>
CarenResult CarenPropertyBag2::Write(
UInt32 Param_Quantidade,
cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
cli::array<Estruturas::CA_VARIANT^>^ Param_VarValue)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PROPBAG2* vi_pArrayPropBagRequest = CriarMatrizEstruturas<PROPBAG2>(Param_Quantidade);
	VARIANT* vi_pArrayValues = CriarMatrizEstruturas<VARIANT>(Param_Quantidade);
	PROPBAG2* vi_pAuxiliarBag = Nulo;
	VARIANT* vi_pAuxiliarValue = Nulo;

	//Faz um for para converter os dados das matrizes gerenciadas para suas nativas.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte os valores do index especificado para uma variavel auxiliar.
		vi_pAuxiliarBag = Util.ConverterPROPBAG2ManagedToUnamaged(Param_ArrayPropBagsRequest[i]);
		Param_VarValue[i]->CopyTo(&vi_pAuxiliarValue);

		//Define o valor nos index das matrizes nativas.
		vi_pArrayPropBagRequest[i] = *vi_pAuxiliarBag;
		vi_pArrayValues[i] = *vi_pAuxiliarValue;

		//Libera a memória utilizada pela variavel auxiliar bag.
		DeletarEstruturaSafe(&vi_pAuxiliarBag);

		//Nula a variant auxiliar de valor.
		vi_pAuxiliarValue = Nulo;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Write(static_cast<ULONG>(Param_Quantidade), vi_pArrayPropBagRequest, vi_pArrayValues);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória utilizada pelo array de bags.
	if (ObjetoValido(vi_pArrayPropBagRequest))
	{
		//Faz um for para liberar os dados de string da estrutura.
		for (UINT32 i = 0; i < Param_Quantidade; i++)
		{
			//Libera a memória para a string se valida.
			if (ObjetoValido(vi_pArrayPropBagRequest[i].pstrName))
				DeletarStringAllocatedSafe(&vi_pArrayPropBagRequest[i].pstrName);
		}

		//Libera a memória utilizada por sua matriz.
		DeletarMatrizEstruturasSafe(&vi_pArrayPropBagRequest);
	}
	//Libera a memória utilizada pelo array de variant.
	if (ObjetoValido(vi_pArrayValues))
	{
		//Faz um for para liberar todos os dados.
		for (UINT32 i = 0; i < Param_Quantidade; i++)
		{
			//Libera a variant.
			VariantClear(&vi_pArrayValues[i]);
		}

		//Libera a memória utilizada por sua matriz.
		DeletarMatrizEstruturasSafe(&vi_pArrayValues);
	}

	//Retorna o resultado.
	return Resultado;
}