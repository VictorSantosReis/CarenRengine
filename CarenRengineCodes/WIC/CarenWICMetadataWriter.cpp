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
#include "CarenWICMetadataWriter.h"

//Destruidor.
CarenWICMetadataWriter::~CarenWICMetadataWriter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICMetadataWriter::CarenWICMetadataWriter()
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
CarenResult CarenWICMetadataWriter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICMetadataWriter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICMetadataWriter*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICMetadataWriter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICMetadataWriter*>(Param_PonteiroNativo);

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
CarenResult CarenWICMetadataWriter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICMetadataWriter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICMetadataWriter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICMetadataWriter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICMetadataWriter::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICMetadataWriter::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICMetadataWriter::LiberarReferencia()
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
void CarenWICMetadataWriter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICMetadataWriter();
}



// Métodos da interface proprietária(ICarenWICMetadataWriter)


/// <summary>
/// Remove o item metadados que corresponde aos parâmetros determinados. 
/// </summary>
/// <param name="Param_Schema">Uma estrutura para a propriedade do esquema de metadados.</param>
/// <param name="Param_Id">Uma estrutura para a propriedade de id metadata.</param>
CarenResult CarenWICMetadataWriter::RemoveValue(
CA_PROPVARIANT^ Param_Schema,
CA_PROPVARIANT^ Param_Id)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_pVariantSchema = Nulo;
	LPPROPVARIANT vi_pVariantId = Nulo;

	//Converte as variants
	vi_pVariantSchema = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Schema));
	vi_pVariantId = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Id));

	//Verifica se não ocorreu um erro na conversão.
	if (!ObjetoValido(vi_pVariantSchema) || !ObjetoValido(vi_pVariantId))
	{
		//Falhou ao converter a propvariant.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveValue(vi_pVariantSchema, vi_pVariantId);

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
	//Libera a memória utilizada pelas propvariants.
	DeletarPropVariantSafe(&vi_pVariantSchema);
	DeletarPropVariantSafe(&vi_pVariantId);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove o item metadados no índice especificado. 
/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
/// metadados restantes, bem como a contagem mudará.
/// </summary>
/// <param name="Param_Index">O índice do item metadados para remover.</param>
CarenResult CarenWICMetadataWriter::RemoveValueByIndex(UInt32 Param_Index)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveValueByIndex(Param_Index);

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
/// Define o item de metadados dado.
/// </summary>
/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
CarenResult CarenWICMetadataWriter::SetValue(
CA_PROPVARIANT^ Param_Schema,
CA_PROPVARIANT^ Param_Id,
CA_PROPVARIANT^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_pVariantSchema = Nulo;
	LPPROPVARIANT vi_pVariantId = Nulo;
	LPPROPVARIANT vi_pVariantValor = Nulo;

	//Converte as variants
	vi_pVariantSchema = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Schema));
	vi_pVariantId = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Id));
	vi_pVariantValor = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Valor));

	//Verifica se não ocorreu um erro na conversão.
	if (!ObjetoValido(vi_pVariantSchema) || !ObjetoValido(vi_pVariantId) || !ObjetoValido(vi_pVariantValor))
	{
		//Falhou ao converter a propvariant.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValue(vi_pVariantSchema, vi_pVariantId, vi_pVariantValor);

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
	//Libera a memória utilizada pelas propvariants.
	DeletarPropVariantSafe(&vi_pVariantSchema);
	DeletarPropVariantSafe(&vi_pVariantId);
	DeletarPropVariantSafe(&vi_pVariantValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o item metadados no índice especificado.
/// Depois de remover um item, espere que os itens de metadados restantes se movam para ocupar o local do item metadados desocupados. Portanto, os índices para itens de 
/// metadados restantes, bem como a contagem mudará.
/// </summary>
/// <param name="Param_Index">O índice do item metadados para definir.</param>
/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
/// <param name="Param_Valor">Estrutura que contém o valor dos metadados.</param>
CarenResult CarenWICMetadataWriter::SetValueByIndex(
UInt32 Param_Index,
CA_PROPVARIANT^ Param_Schema,
CA_PROPVARIANT^ Param_Id,
CA_PROPVARIANT^ Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_pVariantSchema = Nulo;
	LPPROPVARIANT vi_pVariantId = Nulo;
	LPPROPVARIANT vi_pVariantValor = Nulo;

	//Converte as variants
	vi_pVariantSchema = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Schema));
	vi_pVariantId = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Id));
	vi_pVariantValor = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Valor));

	//Verifica se não ocorreu um erro na conversão.
	if (!ObjetoValido(vi_pVariantSchema) || !ObjetoValido(vi_pVariantId) || !ObjetoValido(vi_pVariantValor))
	{
		//Falhou ao converter a propvariant.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetValueByIndex(Param_Index, vi_pVariantSchema, vi_pVariantId, vi_pVariantValor);

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
	//Libera a memória utilizada pelas propvariants.
	DeletarPropVariantSafe(&vi_pVariantSchema);
	DeletarPropVariantSafe(&vi_pVariantId);
	DeletarPropVariantSafe(&vi_pVariantValor);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICMetadataReader)


/// <summary>
/// Obtém o número de itens de metadados dentro do leitor.
/// </summary>
/// <param name="Param_Out_Quantidade">Recebe o número de itens de metadados dentro do leitor.</param>
CarenResult CarenWICMetadataWriter::GetCount([Out] UInt32% Param_Out_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 OutCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCount(&OutCount);

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
	Param_Out_Quantidade = OutCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna um enumerador de todos os itens de metadados.
/// </summary>
/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o enumerador de metadados.</param>
CarenResult CarenWICMetadataWriter::GetEnumerator([Out] ICarenWICEnumMetadataItem^% Param_Out_EnumMetadata)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICEnumMetadataItem* pOutEnumMetadata = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEnumerator(&pOutEnumMetadata);

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

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutEnumMetadata, Param_Out_EnumMetadata);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o formato de metadados associado ao leitor.
/// </summary>
/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
CarenResult CarenWICMetadataWriter::GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidMetadaFormat = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataFormat(&GuidMetadaFormat);

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
	Param_Out_GuidFormatoMetadata = Util.ConverterGuidToString(GuidMetadaFormat);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém as informações do manipulador de metadados associadas ao leitor.
/// </summary>
/// <param name="Param_Out_HandlerInfo">Retorna uma interface(ICarenWICEnumMetadataItem) que contém um ponteiro para o ICarenWICMetadataHandlerInfo.</param>
CarenResult CarenWICMetadataWriter::GetMetadataHandlerInfo([Out] ICarenWICMetadataHandlerInfo^% Param_Out_HandlerInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataHandlerInfo* pOutMetadataHandler = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataHandlerInfo(&pOutMetadataHandler);

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
	Param_Out_HandlerInfo = gcnew CarenWICMetadataHandlerInfo();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutMetadataHandler, Param_Out_HandlerInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o valor do item metadados.
/// </summary>
/// <param name="Param_Schema">Estrutura para a propriedade do esquema do item de metadados.</param>
/// <param name="Param_Id">Estrutura para o id do item metadados.</param>
/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
CarenResult CarenWICMetadataWriter::GetValue(
	CA_PROPVARIANT^ Param_Schema,
	CA_PROPVARIANT^ Param_Id,
	[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_pVariantSchema = Nulo;
	LPPROPVARIANT vi_pVariantId = Nulo;
	LPPROPVARIANT vi_OutVariantValor = Nulo;

	//Converte as variants
	vi_pVariantSchema = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Schema));
	vi_pVariantId = static_cast<PROPVARIANT*>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_Id));

	//Verifica se não ocorreu um erro na conversão.
	if (!ObjetoValido(vi_pVariantSchema) || !ObjetoValido(vi_pVariantId))
	{
		//Falhou ao converter a propvariant.

		//Define falha.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

		//Sai do método
		Sair;
	}

	//Inicia a PropVariant que vai receber os dados.
	IniciarPropVariant(&vi_OutVariantValor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValue(vi_pVariantSchema, vi_pVariantId, vi_OutVariantValor);

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

	//Converte a variante para gerenciada e define no parametro de saida.
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutVariantValor);

Done:;
	//Libera a memória utilizada pelas propvariants.
	DeletarPropVariantSafe(&vi_pVariantSchema);
	DeletarPropVariantSafe(&vi_pVariantId);
	DeletarPropVariantSafe(&vi_OutVariantValor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o item metadados no índice dado.
/// </summary>
/// <param name="Param_Index">O índice do item metadados para recuperar.</param>
/// <param name="Param_Out_Schema">Retorna uma estrutura para a propriedade do esquema do item de metadados.</param>
/// <param name="Param_Out_Id">Retorna uma estrutra para o id do item metadados.</param>
/// <param name="Param_Out_Valor">Retorna uma estrutura que contém o valor dos metadados.</param>
CarenResult CarenWICMetadataWriter::GetValueByIndex(
	UInt32 Param_Index,
	[Out] CA_PROPVARIANT^% Param_Out_Schema,
	[Out] CA_PROPVARIANT^% Param_Out_Id,
	[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_OutVariantSchema = Nulo;
	LPPROPVARIANT vi_OutVariantId = Nulo;
	LPPROPVARIANT vi_OutVariantValor = Nulo;

	//Inicializa as propvariants
	IniciarPropVariant(&vi_OutVariantSchema);
	IniciarPropVariant(&vi_OutVariantId);
	IniciarPropVariant(&vi_OutVariantValor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetValueByIndex(Param_Index, vi_OutVariantSchema, vi_OutVariantId, vi_OutVariantValor);

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

	//Converte as PropVariants para gerenciada e define nos parametros de saida.
	Param_Out_Schema = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutVariantSchema);
	Param_Out_Id = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutVariantId);
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutVariantValor);

Done:;
	//Libera a memória utilizada pelas variants.
	DeletarPropVariantSafe(&vi_OutVariantSchema);
	DeletarPropVariantSafe(&vi_OutVariantId);
	DeletarPropVariantSafe(&vi_OutVariantValor);

	//Retorna o resultado.
	return Resultado;
}