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
#include "CarenWICEnumMetadataItem.h"

//Destruidor.
CarenWICEnumMetadataItem::~CarenWICEnumMetadataItem()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICEnumMetadataItem::CarenWICEnumMetadataItem()
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
CarenResult CarenWICEnumMetadataItem::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICEnumMetadataItem::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICEnumMetadataItem*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICEnumMetadataItem::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICEnumMetadataItem*>(Param_PonteiroNativo);

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
CarenResult CarenWICEnumMetadataItem::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICEnumMetadataItem::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICEnumMetadataItem::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICEnumMetadataItem::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICEnumMetadataItem::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICEnumMetadataItem::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICEnumMetadataItem::LiberarReferencia()
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
void CarenWICEnumMetadataItem::LimparDados()
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
void CarenWICEnumMetadataItem::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICEnumMetadataItem();
}



// Métodos da interface proprietária(ICarenWICEnumMetadataItem)


/// <summary>
/// Cria uma cópia do ICarenWICEnumMetadataItem atual. 
/// </summary>
/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro que representa uma cópia da interface atual.</param>
CarenResult CarenWICEnumMetadataItem::Clone([Out] ICarenWICEnumMetadataItem^% Param_Out_EnumMetadata)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICEnumMetadataItem* pEnumMetadata = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Clone(&pEnumMetadata);

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
	Param_Out_EnumMetadata = gcnew CarenWICEnumMetadataItem();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pEnumMetadata, Param_Out_EnumMetadata);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Avança a posição atual na enumeração. 
/// </summary>
/// <param name="Param_Quantidade">O número de itens a serem recuperados.</param>
/// <param name="Param_Ref_ArraySchemas">Retorna uma variedade de itens enumerados. Este parâmetro é opcional.</param>
/// <param name="Param_Out_ArrayIds">Retorna uma variedade de itens enumerados.</param>
/// <param name="Param_Ref_ArrayValores">Retorna uma variedade de itens enumerados. Este parâmetro é opcional.</param>
/// <param name="Param_Out_QuantRecuperados">O número de itens que foram recuperados. Esse valor é sempre menor ou igual ao número de itens solicitados.</param>
CarenResult CarenWICEnumMetadataItem::Next(
UInt64 Param_Quantidade,
cli::array<CA_PropVariant^>^% Param_Ref_ArraySchemas,
[Out] cli::array<CA_PropVariant^>^% Param_Out_ArrayIds,
cli::array<CA_PropVariant^>^% Param_Ref_ArrayValores,
[Out] UInt64% Param_Out_QuantRecuperados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PROPVARIANT* pOutArraySchemas = Nulo; //Pode ser NULO.
	PROPVARIANT* pOutArrayIds = Nulo;
	PROPVARIANT* pOutArrayValores = Nulo; //Pode ser NULO.
	ULONG OutCountRecuperada = 0;

	//Cria o array de SCHEMAS se fornecido.
	if (ObjetoGerenciadoValido(Param_Ref_ArraySchemas))
	{
		//Cria a matriz
		pOutArraySchemas = CriarMatrizEstruturas<PROPVARIANT>(static_cast<UINT32>(Param_Quantidade));
	}

	//Cria o array de VALORES se fornecido.
	if (ObjetoGerenciadoValido(Param_Ref_ArrayValores))
	{
		//Cria a matriz
		pOutArrayValores = CriarMatrizEstruturas<PROPVARIANT>(static_cast<UINT32>(Param_Quantidade));
	}

	//Cria a matriz obrigatoria que retorna o array de ids.
	pOutArrayIds = CriarMatrizEstruturas<PROPVARIANT>(static_cast<UINT32>(Param_Quantidade));


	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Next(
		static_cast<ULONG>(Param_Quantidade),
		pOutArraySchemas == Nulo ? Nulo : pOutArraySchemas, 
		pOutArrayIds, 
		pOutArrayValores == Nulo ? Nulo: pOutArrayValores, &OutCountRecuperada);
	
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

	//Cria a matriz de IDs que é a obrigatoria a retornar.
	Param_Out_ArrayIds = gcnew cli::array<CA_PropVariant^>(OutCountRecuperada);

	//Faz um for definir os dados.
	for (ULONG i = 0; i < OutCountRecuperada; i++)
	{
		//Converte e define no id especificado.
		Param_Out_ArrayIds[i] = Util.ConvertPropVariantUnmanagedToManaged(pOutArrayIds[i]);
	}

	//Cria o array de SCHEMAS se pedido para retornar.
	if (ObjetoGerenciadoValido(Param_Ref_ArraySchemas))
	{
		//Cria a matriz
		Param_Ref_ArraySchemas = gcnew cli::array<CA_PropVariant^>(OutCountRecuperada);

		//Faz um for definir os dados.
		for (ULONG i = 0; i < OutCountRecuperada; i++)
		{
			//Converte e define no id especificado.
			Param_Ref_ArraySchemas[i] = Util.ConvertPropVariantUnmanagedToManaged(pOutArraySchemas[i]);
		}
	}

	//Cria o array de VALORES se pedido para retornar.
	if (ObjetoGerenciadoValido(Param_Ref_ArrayValores))
	{
		//Cria a matriz
		Param_Ref_ArrayValores = gcnew cli::array<CA_PropVariant^>(OutCountRecuperada);

		//Faz um for definir os dados.
		for (ULONG i = 0; i < OutCountRecuperada; i++)
		{
			//Converte e define no id especificado.
			Param_Ref_ArrayValores[i] = Util.ConvertPropVariantUnmanagedToManaged(pOutArrayValores[i]);
		}
	}

	//Define a quantidade de dados retornados.
	Param_Out_QuantRecuperados = static_cast<UInt64>(OutCountRecuperada);

Done:;
	//Libera a memória utilizada pelos propvariants e suas matrizes.

	//Verifica se o objeto é valido.
	if (ObjetoValido(pOutArraySchemas))
	{
		//Chama o método nativo para liberar cada item do array
		ClearPropVariantArray(pOutArraySchemas, static_cast<UINT>(OutCountRecuperada));

		//Libera a memória utilizada pela matriz.
		DeletarMatrizEstruturasSafe(&pOutArraySchemas);
	}
	//Verifica se o objeto é valido.
	if (ObjetoValido(pOutArrayIds))
	{
		//Chama o método nativo para liberar cada item do array
		ClearPropVariantArray(pOutArrayIds, static_cast<UINT>(OutCountRecuperada));

		//Libera a memória utilizada pela matriz.
		DeletarMatrizEstruturasSafe(&pOutArrayIds);
	}
	//Verifica se o objeto é valido.
	if (ObjetoValido(pOutArrayValores))
	{
		//Chama o método nativo para liberar cada item do array
		ClearPropVariantArray(pOutArrayValores, static_cast<UINT>(OutCountRecuperada));

		//Libera a memória utilizada pela matriz.
		DeletarMatrizEstruturasSafe(&pOutArrayValores);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Redefine a posição atual para o início da enumeração. 
/// </summary>
CarenResult CarenWICEnumMetadataItem::Reset()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Reset();

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
/// Pula para um número determinado de objetos.
/// </summary>
/// <param name="Param_Quantidade">O número de objetos para pular.</param>
CarenResult CarenWICEnumMetadataItem::Skip(UInt64 Param_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Skip(static_cast<ULONG>(Param_Quantidade));

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