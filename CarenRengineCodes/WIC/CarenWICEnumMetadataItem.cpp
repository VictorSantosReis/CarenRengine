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
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICEnumMetadataItem::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICEnumMetadataItem*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICEnumMetadataItem**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICEnumMetadataItem::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICEnumMetadataItem*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICEnumMetadataItem**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICEnumMetadataItem::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICEnumMetadataItem::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICEnumMetadataItem::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
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
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICEnumMetadataItem::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
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
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

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
cli::array<CA_PROPVARIANT^>^% Param_Ref_ArraySchemas,
[Out] cli::array<CA_PROPVARIANT^>^% Param_Out_ArrayIds,
cli::array<CA_PROPVARIANT^>^% Param_Ref_ArrayValores,
[Out] UInt64% Param_Out_QuantRecuperados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
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

		//Sai do método
		Sair;
	}

	//Cria a matriz de IDs que é a obrigatoria a retornar.
	Param_Out_ArrayIds = gcnew cli::array<CA_PROPVARIANT^>(OutCountRecuperada);

	//Faz um for definir os dados.
	for (ULONG i = 0; i < OutCountRecuperada; i++)
	{
		//Converte e define no id especificado.
		Param_Out_ArrayIds[i] = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(&pOutArrayIds[i]);
	}

	//Cria o array de SCHEMAS se pedido para retornar.
	if (ObjetoGerenciadoValido(Param_Ref_ArraySchemas))
	{
		//Cria a matriz
		Param_Ref_ArraySchemas = gcnew cli::array<CA_PROPVARIANT^>(OutCountRecuperada);

		//Faz um for definir os dados.
		for (ULONG i = 0; i < OutCountRecuperada; i++)
		{
			//Converte e define no id especificado.
			Param_Ref_ArraySchemas[i] = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(&pOutArraySchemas[i]);
		}
	}

	//Cria o array de VALORES se pedido para retornar.
	if (ObjetoGerenciadoValido(Param_Ref_ArrayValores))
	{
		//Cria a matriz
		Param_Ref_ArrayValores = gcnew cli::array<CA_PROPVARIANT^>(OutCountRecuperada);

		//Faz um for definir os dados.
		for (ULONG i = 0; i < OutCountRecuperada; i++)
		{
			//Converte e define no id especificado.
			Param_Ref_ArrayValores[i] = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(&pOutArrayValores[i]);
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

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}