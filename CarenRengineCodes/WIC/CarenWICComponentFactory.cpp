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
#include "CarenWICComponentFactory.h"


//Destruidor.
CarenWICComponentFactory::~CarenWICComponentFactory()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICComponentFactory::CarenWICComponentFactory()
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
CarenResult CarenWICComponentFactory::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenWICComponentFactory::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICComponentFactory*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenWICComponentFactory::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IWICComponentFactory*>(Param_PonteiroNativo);

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
CarenResult CarenWICComponentFactory::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenWICComponentFactory::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenWICComponentFactory::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenWICComponentFactory::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICComponentFactory::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICComponentFactory::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICComponentFactory::LiberarReferencia()
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
void CarenWICComponentFactory::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenWICComponentFactory();
}



// Métodos da interface proprietária(ICarenWICComponentFactory)


/// <summary>
/// Cria uma bag de propriedades do codificador. 
/// </summary>
/// <param name="Param_ArrayPropOptions">Uma matriz de estruturas(CA_PROPBAG2) usadas para criar a bag de propriedades do codificador.</param>
/// <param name="Param_Quantidade">A quantidade de items na matriz em (Param_ArrayPropOptions).</param>
/// <param name="Param_Out_PropertyBag">Retorna uma interface(ICarenPropertyBag2) que contém um ponteiro para a nova bag de propriedades do codificador.</param>
CarenResult CarenWICComponentFactory::CreateEncoderPropertyBag(
cli::array<CA_PROPBAG2^>^ Param_ArrayPropOptions,
UInt32 Param_Quantidade,
[Out] ICarenPropertyBag2^% Param_Out_PropertyBag)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PROPBAG2* vi_pMatrizBag = CriarMatrizEstruturas< PROPBAG2>(Param_Quantidade);
	IPropertyBag2* vi_pOutPropertyBag = Nulo;
	PROPBAG2* vi_BagAuxiliar = Nulo;

	//Abre um for para converter a bag e definir na matriz nativa.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte do gerenciado para o nativo.
		vi_BagAuxiliar = Util.ConverterPROPBAG2ManagedToUnamaged(Param_ArrayPropOptions[i]);

		//Define na matriz nativa.
		vi_pMatrizBag[i] = *vi_BagAuxiliar;

		//Libera a memória utilizada pela estrutura
		DeletarEstruturaSafe(&vi_BagAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateEncoderPropertyBag(vi_pMatrizBag, Param_Quantidade, &vi_pOutPropertyBag);

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
	Param_Out_PropertyBag = gcnew CarenPropertyBag2();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(vi_pOutPropertyBag, Param_Out_PropertyBag);

Done:;
	//Libera a memória utilizada pela matriz.
	DeletarMatrizEstruturasSafe(&vi_pMatrizBag);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
/// </summary>
/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
CarenResult CarenWICComponentFactory::CreateMetadataReader(
String^ Param_GuidFormatoMetadata,
String^ Param_GuidVendor,
UInt32 Param_Opcoes,
ICarenStream^ Param_Fluxo,
[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidMetadata = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IStream* vi_pFluxo = Nulo;
	IWICMetadataReader* vi_OutMetadataReader = Nulo;

	//Converte as strings para guid.
	vi_GuidMetadata = Util.CreateGuidFromString(Param_GuidFormatoMetadata);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &vi_pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMetadataReader(vi_GuidMetadata, &vi_GuidVendor, static_cast<DWORD>(Param_Opcoes), vi_pFluxo, &vi_OutMetadataReader);

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
	Param_Out_MetadataReader = gcnew CarenWICMetadataReader();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutMetadataReader, Param_Out_MetadataReader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataReader com base nos parâmetros determinados. 
/// </summary>
/// <param name="Param_GuidFormatoContainer">O formato de contêiner GUID para basear o leitor.</param>
/// <param name="Param_GuidVendor">O fornecedor GUID do leitor de metadados.</param>
/// <param name="Param_Opcoes">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o leitor de metadados.</param>
/// <param name="Param_Fluxo">Um fluxo no qual inicializa o leitor. Se NULO, o leitor de metadados estará vazio.</param>
/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o novo leitor de metadados.</param>
CarenResult CarenWICComponentFactory::CreateMetadataReaderFromContainer(
String^ Param_GuidFormatoContainer,
String^ Param_GuidVendor,
UInt32 Param_Opcoes,
ICarenStream^ Param_Fluxo,
[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidFormatoContainer = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IStream* vi_pFluxo = Nulo;
	IWICMetadataReader* vi_OutMetadataReader = Nulo;

	//Converte as strings para guid.
	vi_GuidFormatoContainer = Util.CreateGuidFromString(Param_GuidFormatoContainer);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &vi_pFluxo);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMetadataReaderFromContainer(vi_GuidFormatoContainer, &vi_GuidVendor, static_cast<DWORD>(Param_Opcoes), vi_pFluxo, &vi_OutMetadataReader);

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
	Param_Out_MetadataReader = gcnew CarenWICMetadataReader();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutMetadataReader, Param_Out_MetadataReader);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataWriter baseado nos parâmetros determinados. 
/// </summary>
/// <param name="Param_GuidFormatoMetadata">O GUID do formato de metadados desejado.</param>
/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
/// <param name="Param_OpcoesMetadata">As opções CA_WICPersistOptions e CA_WICMetadataCreationOptions para usar ao criar o escritor de metadados.</param>
/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
CarenResult CarenWICComponentFactory::CreateMetadataWriter(
String^ Param_GuidFormatoMetadata,
String^ Param_GuidVendor,
UInt32 Param_OpcoesMetadata,
[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidMetadata = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IWICMetadataWriter* vi_OutMetadataWriter = Nulo;

	//Converte as strings para guid.
	vi_GuidMetadata = Util.CreateGuidFromString(Param_GuidFormatoMetadata);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMetadataWriter(vi_GuidMetadata, &vi_GuidVendor, static_cast<DWORD>(Param_OpcoesMetadata), &vi_OutMetadataWriter);

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
	Param_Out_MetadataWriter = gcnew CarenWICMetadataWriter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutMetadataWriter, Param_Out_MetadataWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataWriter do dado ICarenWICMetadataReader. 
/// </summary>
/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataReader) para o leitor de metadados para basear o escritor de metadados.</param>
/// <param name="Param_GuidVendor">O GUID do fornecedor leitor de metadados desejado.</param>
/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o novo escritor de metadados.</param>
CarenResult CarenWICComponentFactory::CreateMetadataWriterFromReader(
ICarenWICMetadataReader^ Param_MetadataReader,
String^ Param_GuidVendor,
[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICMetadataReader* vi_pMetadataReader = Nulo;
	GUID vi_GuidVendor = GUID_NULL;
	IWICMetadataWriter* vi_OutMetadataWriter = Nulo;

	//Recupera o ponteiro para o leitor.
	Resultado = RecuperarPonteiroCaren(Param_MetadataReader, &vi_pMetadataReader);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a string para o guid.
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMetadataWriterFromReader(vi_pMetadataReader, &vi_GuidVendor, &vi_OutMetadataWriter);

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
	Param_Out_MetadataWriter = gcnew CarenWICMetadataWriter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutMetadataWriter, Param_Out_MetadataWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataQueryReader a partir do ICarenWICMetadataBlockReader. 
/// </summary>
/// <param name="Param_MetadataBlockReader">Uma interface(ICarenWICMetadataQueryReader) para o leitor de bloco para basear o escritor de consulta.</param>
/// <param name="Param_Out_MetadataQueryReader">Retorna uma interface(ICarenWICMetadataQueryReader) que contém um ponteiro para o novo leitor de consulta de metadados.</param>
CarenResult CarenWICComponentFactory::CreateQueryReaderFromBlockReader(
ICarenWICMetadataBlockReader^ Param_MetadataBlockReader,
[Out] ICarenWICMetadataQueryReader^% Param_Out_MetadataQueryReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataBlockReader* vi_BlockReader = Nulo;
	IWICMetadataQueryReader* vi_OutQueryReader = Nulo;

	//Recupera o ponteiro para o leitor de bloco de modo seguro.
	CarenGetPointerFromICarenSafe(Param_MetadataBlockReader, vi_OutQueryReader);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQueryReaderFromBlockReader(vi_BlockReader, &vi_OutQueryReader);

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
	Param_Out_MetadataQueryReader = gcnew CarenWICMetadataQueryReader();

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_OutQueryReader, Param_Out_MetadataQueryReader, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICMetadataQueryWriter do dado ICarenWICMetadataBlockWriter. 
/// </summary>
/// <param name="Param_MetadataBlockWriter">Uma interface(ICarenWICMetadataBlockWriter) para o escritor de bloco para basear o escritor de consulta.</param>
/// <param name="Param_Out_MetadataQueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consulta de metadados.</param>
CarenResult CarenWICComponentFactory::CreateQueryWriterFromBlockWriter(
ICarenWICMetadataBlockWriter^ Param_MetadataBlockWriter,
[Out] ICarenWICMetadataQueryWriter^% Param_Out_MetadataQueryWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataBlockWriter* vi_BlockWriter = Nulo;
	IWICMetadataQueryWriter* vi_OutQueryWriter = Nulo;

	//Recupera o ponteiro para o leitor de bloco de modo seguro.
	CarenGetPointerFromICarenSafe(Param_MetadataBlockWriter, vi_BlockWriter);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQueryWriterFromBlockWriter(vi_BlockWriter, &vi_OutQueryWriter);

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
	Param_Out_MetadataQueryWriter = gcnew CarenWICMetadataQueryWriter();

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_OutQueryWriter, Param_Out_MetadataQueryWriter, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICImagingFactory)


/// <summary>
/// Cria um objeto ICarenWICBitmap. 
/// </summary>
/// <param name="Param_Width">A largura do novo bitmap .</param>
/// <param name="Param_Height">A altura do novo bitmap.</param>
/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap.</param>
/// <param name="Param_OpcoesCache">As opções de criação de cache do novo bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmap(
	UInt32 Param_Width,
	UInt32 Param_Height,
	String^ Param_GuidFormatoPixel,
	CA_WICBitmapCreateCacheOption Param_OpcoesCache,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidPixel = GUID_NULL;
	WICBitmapCreateCacheOption vi_opcoesCache = static_cast<WICBitmapCreateCacheOption>(Param_OpcoesCache);
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Converte a string para o guid.
	vi_GuidPixel = Util.CreateGuidFromString(Param_GuidFormatoPixel);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(Param_Width, Param_Height, vi_GuidPixel, vi_opcoesCache, &vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância de um objeto ICarenWICBitmapClipper. 
/// </summary>
/// <param name="Param_Out_BitmapClipper">Retorna uma interface(Param_Out_BitmapClipper) que contém um ponteiro para o novo Clipper.</param>
CarenResult CarenWICComponentFactory::CreateBitmapClipper([Out] ICarenWICBitmapClipper^% Param_Out_BitmapClipper)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapClipper* vi_pOutBitmapClipper = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapClipper(&vi_pOutBitmapClipper);

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
	Param_Out_BitmapClipper = gcnew CarenWICBitmapClipper();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmapClipper, Param_Out_BitmapClipper);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância de um objeto ICarenWICBitmapFlipRotator. 
/// </summary>
/// <param name="Param_Out_BitmapFlipRotator">Retorna uma interface(ICarenWICBitmapFlipRotator) que contém um ponteiro para o novo rotacionador de bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFlipRotator([Out] ICarenWICBitmapFlipRotator^% Param_Out_BitmapFlipRotator)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapFlipRotator* vi_pOutBitmapFlip = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFlipRotator(&vi_pOutBitmapFlip);

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
	Param_Out_BitmapFlipRotator = gcnew CarenWICBitmapFlipRotator();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmapFlip, Param_Out_BitmapFlipRotator);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICBitmap a partir de uma Handle para o bitmap. 
/// </summary>
/// <param name="Param_HandleBitmap">Uma handle para o bitmap para criar o bitmap.</param>
/// <param name="Param_HandlePaleta">Uma handle para a palleta usada para criar o bitmap.</param>
/// <param name="Param_OpcoesCanalAlfa">As opções do canal alfa para criar o bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFromHBITMAP(
	IntPtr Param_HandleBitmap,
	IntPtr Param_HandlePaleta,
	CA_WICBitmapAlphaChannelOption Param_OpcoesCanalAlfa,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WICBitmapAlphaChannelOption vi_OpcoesAlfa = static_cast<WICBitmapAlphaChannelOption>(Param_OpcoesCanalAlfa);
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromHBITMAP(
		Util.ConverterIntPtrTo<HBITMAP>(Param_HandleBitmap),
		Util.ConverterIntPtrTo<HPALETTE>(Param_HandlePaleta),
		vi_OpcoesAlfa,
		&vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICBitmap a partir de uma handle para o ícone. 
/// </summary>
/// <param name="Param_HandleIcon">Uma handle para o ícone para criar o bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFromHICON(
	IntPtr Param_HandleIcon,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromHICON(Util.ConverterIntPtrTo<HICON>(Param_HandleIcon), &vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICBitmap a partir de um bloco de memória. O tamanho do ICarenWICBitmap a ser criado deve ser menor ou igual ao tamanho da imagem em (Param_Buffer).
/// O Stride do bitmap de destino será igual ao Stride dos dados de origem, independentemente da largura e altura especificados.
/// O parâmetro (Param_GuidFormatoPixel) define o formato de pixel tanto para os dados de entrada quanto para o bitmap de saída.
/// </summary>
/// <param name="Param_Width">A largura do novo bitmap.</param>
/// <param name="Param_Height">A altura do novo bitmap.</param>
/// <param name="Param_GuidFormatoPixel">O formato pixel do novo bitmap. Consulte a estrutura (GUIDs_WIC_NATIVE_PIXEL_FORMATS) para obter uma lista de guids para esse parametro.</param>
/// <param name="Param_Stride">O número de bytes entre linhas de varredura sucessivas em (Param_Buffer).</param>
/// <param name="Param_BufferSize">O tamanho do (Param_Buffer).</param>
/// <param name="Param_Buffer">O buffer usado para criar o bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFromMemory(
	UInt32 Param_Width,
	UInt32 Param_Height,
	String^ Param_GuidFormatoPixel,
	UInt32 Param_Stride,
	UInt32 Param_BufferSize,
	ICarenBuffer^ Param_Buffer,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidPixel = GUID_NULL;
	GenPointer vi_pBuffer = DefaultGenPointer;
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Converte a string para guid.
	vi_GuidPixel = Util.CreateGuidFromString(Param_GuidFormatoPixel);

	//Recupera o ponteiro para o buffer.
	Resultado = Param_Buffer->ObterPonteiroInterno(vi_pBuffer);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromMemory(
		Param_Width,
		Param_Height,
		vi_GuidPixel,
		Param_Stride,
		Param_BufferSize,
		Util.ConverterIntPtrTo<PBYTE>(vi_pBuffer),
		&vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICBitmap a partir de um ICarenWICBitmapSource. 
/// </summary>
/// <param name="Param_FonteBitmap">Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
/// <param name="Param_OpcoesCache">As opções de cache do novo bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFromSource(
	ICarenWICBitmapSource^ Param_FonteBitmap,
	CA_WICBitmapCreateCacheOption Param_OpcoesCache,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* vi_BitmapSource = Nulo;
	WICBitmapCreateCacheOption vi_CacheOptions = static_cast<WICBitmapCreateCacheOption>(Param_OpcoesCache);
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Recupera a fonte do bitmap
	Resultado = RecuperarPonteiroCaren(Param_FonteBitmap, &vi_BitmapSource);

	//Sai do método
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromSource(vi_BitmapSource, vi_CacheOptions, &vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenWICBitmap a partir de um retângulo especificado de um ICarenWICBitmapSource. Fornecer um retângulo maior que a fonte produzirá resultados indefinidos.
/// Este método sempre cria uma cópia separada da imagem de origem, semelhante à opção de cache WICBitmapCacheOnLoad.
/// </summary>
/// <param name="Param_FonteBitmap">>Uma interface(ICarenWICBitmapSource) para a fonte do bitmap a ser criado.</param>
/// <param name="Param_X">A coordenada horizontal do canto superior esquerdo do retângulo.</param>
/// <param name="Param_Y">A coordenada vertical do canto superior esquerdo do retângulo.</param>
/// <param name="Param_Width">A largura do retângulo e o novo bitmap.</param>
/// <param name="Param_Height">A altura do retângulo e o novo bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenWICBitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenWICComponentFactory::CreateBitmapFromSourceRect(
	ICarenWICBitmapSource^ Param_FonteBitmap,
	UInt32 Param_X,
	UInt32 Param_Y,
	UInt32 Param_Width,
	UInt32 Param_Height,
	[Out] ICarenWICBitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* vi_BitmapSource = Nulo;
	IWICBitmap* vi_pOutBitmap = Nulo;

	//Recupera a fonte do bitmap
	Resultado = RecuperarPonteiroCaren(Param_FonteBitmap, &vi_BitmapSource);

	//Sai do método
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromSourceRect(vi_BitmapSource, Param_X, Param_Y, Param_Width, Param_Height, &vi_pOutBitmap);

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
	Param_Out_Bitmap = gcnew CarenWICBitmap();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância de um IWICBitmapScaler. 
/// </summary>
/// <param name="Param_Out_BitmapScaler">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo redimensionador.</param>
CarenResult CarenWICComponentFactory::CreateBitmapScaler([Out] ICarenWICBitmapScaler^% Param_Out_BitmapScaler)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapScaler* vi_pOutBitmapScaler = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapScaler(&vi_pOutBitmapScaler);

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
	Param_Out_BitmapScaler = gcnew CarenWICBitmapScaler();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutBitmapScaler, Param_Out_BitmapScaler);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe IWICColorContext. 
/// </summary>
/// <param name="Param_Out_WicColorContext">Retorna uma interface(ICarenWICBitmapScaler) que contém um ponteiro para o novo contexto de cores.</param>
CarenResult CarenWICComponentFactory::CreateColorContext([Out] ICarenWICColorContext^% Param_Out_WicColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext* vi_pOutColorContext = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContext(&vi_pOutColorContext);

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
	Param_Out_WicColorContext = gcnew CarenWICColorContext();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutColorContext, Param_Out_WicColorContext);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe IWICColorTransform. 
/// </summary>
/// <param name="Param_Out_WicColorTransform">Retorna uma interface(ICarenWICColorTransform) que contém um ponteiro para o novo transformado de contexto de cor.</param>
CarenResult CarenWICComponentFactory::CreateColorTransformer([Out] ICarenWICColorTransform^% Param_Out_WicColorTransform)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorTransform* vi_OutpColorTransform = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorTransformer(&vi_OutpColorTransform);

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
	Param_Out_WicColorTransform = gcnew CarenWICColorTransform();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpColorTransform, Param_Out_WicColorTransform);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto IEnumUnknown dos tipos de componentes especificados. 
/// Os tipos de componentes devem ser enumerados separadamente. Combinações de tipos de componentes e WICAllComponents não são suportadas.
/// </summary>
/// <param name="Param_TiposComponentes">Os tipos de WICComponentType para enumerar.</param>
/// <param name="Param_OpcoesEnumeracao">As Opções WICComponentEnumerate utilizadas para enumerar os tipos de componentes dado.</param>
/// <param name="Param_Out_Enumerador">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para um novo enumerador de componentes.</param>
CarenResult CarenWICComponentFactory::CreateComponentEnumerator(
	CA_WICComponentType Param_TiposComponentes,
	CA_WICComponentEnumerateOptions Param_OpcoesEnumeracao,
	[Out] ICarenEnumUnknown^% Param_Out_Enumerador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IEnumUnknown* vi_OutpEnum = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateComponentEnumerator(static_cast<DWORD>(Param_TiposComponentes), static_cast<DWORD>(Param_OpcoesEnumeracao), &vi_OutpEnum);

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
	Param_Out_Enumerador = gcnew CarenEnumUnknown();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpEnum, Param_Out_Enumerador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe IWICComponentInfo para o identificador de classe de componentes dado (CLSID). 
/// </summary>
/// <param name="Param_ClsidComponente">O CLSID para o componente desejado.</param>
/// <param name="Param_Out_ComponenteInfo">Retorna uma interface(ICarenWICComponentInfo) que contém um ponteiro para um novo informador de componente.</param>
CarenResult CarenWICComponentFactory::CreateComponentInfo(
	String^ Param_ClsidComponente,
	[Out] ICarenWICComponentInfo^% Param_Out_ComponenteInfo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidComp = GUID_NULL;
	IWICComponentInfo* vi_OutpComponentInfo = Nulo;

	//Cria o guid do componente.
	vi_GuidComp = Util.CreateGuidFromString(Param_ClsidComponente);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateComponentInfo(vi_GuidComp, &vi_OutpComponentInfo);

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
	Param_Out_ComponenteInfo = gcnew CarenWICComponentInfo();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpComponentInfo, Param_Out_ComponenteInfo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância do ICarenWICBitmapDecoder. 
/// </summary>
/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado.</param>
/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido.</param>
/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador. Você deve inicializar este 
/// ICarenWICBitmapDecoder em um fluxo usando o método (Initialize) mais tarde.</param>
CarenResult CarenWICComponentFactory::CreateDecoder(
	String^ Param_GuidFormatoContainer,
	String^ Param_GuidVendor,
	[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidFormato = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IWICBitmapDecoder* vi_OutpBitmapDecoder = Nulo;

	//Cria os guids.
	vi_GuidFormato = Util.CreateGuidFromString(Param_GuidFormatoContainer);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDecoder(vi_GuidFormato, &vi_GuidVendor, &vi_OutpBitmapDecoder);

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
	Param_Out_BitmapDecoder = gcnew CarenWICBitmapDecoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpBitmapDecoder, Param_Out_BitmapDecoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância do ICarenWICBitmapDecoder com base na handle de arquivo dada. 
/// </summary>
/// <param name="Param_HandleArquivo">A handle para o arquivo para ser utilizado para criar o decodifciador.</param>
/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
/// <param name="Param_OpcoesDecoder">As opções de código WIC para usar ao criar o decodificador.</param>
/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
CarenResult CarenWICComponentFactory::CreateDecoderFromFileHandle(
	UInt64 Param_HandleArquivo,
	String^ Param_GuidVendor,
	CA_WICDecodeOptions Param_OpcoesDecoder,
	[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidVendor = GUID_NULL;
	IWICBitmapDecoder* vi_OutpBitmapDecoder = Nulo;

	//Cria o guid do Vendor.
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDecoderFromFileHandle(
		static_cast<ULONG_PTR>(Param_HandleArquivo),
		&vi_GuidVendor,
		static_cast<WICDecodeOptions>(Param_OpcoesDecoder),
		&vi_OutpBitmapDecoder);

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
	Param_Out_BitmapDecoder = gcnew CarenWICBitmapDecoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpBitmapDecoder, Param_Out_BitmapDecoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no arquivo dado. 
/// </summary>
/// <param name="Param_UrlArquivo">Uma string que especifica o nome de um objeto para criar ou abrir.</param>
/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULO se não houver fornecedor preferencial.</param>
/// <param name="Param_TipoAcesso">O acesso ao objeto, que pode ser lido, escrito ou ambos.</param>
/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
CarenResult CarenWICComponentFactory::CreateDecoderFromFilename(
	String^ Param_UrlArquivo,
	String^ Param_GuidVendor,
	CA_ACCESS_RIGHTS Param_TipoAcesso,
	CA_WICDecodeOptions Param_OpcoesMetadata,
	[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pUrlArquivo = Nulo;
	GUID vi_GuidVendor = GUID_NULL;
	IWICBitmapDecoder* vi_OutpBitmapDecoder = Nulo;

	//Converte a string para a url.
	vi_pUrlArquivo = Util.ConverterStringToWCHAR(Param_UrlArquivo);

	//Cria o guid do Vendor.
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDecoderFromFilename(
		vi_pUrlArquivo,
		&vi_GuidVendor,
		static_cast<DWORD>(Param_TipoAcesso),
		static_cast<WICDecodeOptions>(Param_OpcoesMetadata),
		&vi_OutpBitmapDecoder);

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
	Param_Out_BitmapDecoder = gcnew CarenWICBitmapDecoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpBitmapDecoder, Param_Out_BitmapDecoder);

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pUrlArquivo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICBitmapDecoder com base no ICarenStream dado. 
/// </summary>
/// <param name="Param_Fluxo">O fluxo para criar o decodificador.</param>
/// <param name="Param_GuidVendor">O GUID para o fornecedor decodificador preferido. Use NULL se não houver fornecedor preferencial.</param>
/// <param name="Param_OpcoesMetadata">As opções de código WIC para usar ao criar o decodificador.</param>
/// <param name="Param_Out_BitmapDecoder">Retorna uma interface(ICarenWICBitmapDecoder) que contém um ponteiro para o novo decodificador.</param>
CarenResult CarenWICComponentFactory::CreateDecoderFromStream(
	ICarenStream^ Param_Fluxo,
	String^ Param_GuidVendor,
	CA_WICDecodeOptions Param_OpcoesMetadata,
	[Out] ICarenWICBitmapDecoder^% Param_Out_BitmapDecoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IStream* vi_pFluxo = Nulo;
	GUID vi_GuidVendor = GUID_NULL;
	IWICBitmapDecoder* vi_OutpBitmapDecoder = Nulo;

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_Fluxo, &vi_pFluxo);

	//Saido método em caso de erro.
	SairOnError(Resultado);

	//Cria o guid do Vendor.
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDecoderFromStream(
		vi_pFluxo,
		&vi_GuidVendor,
		static_cast<WICDecodeOptions>(Param_OpcoesMetadata),
		&vi_OutpBitmapDecoder);

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
	Param_Out_BitmapDecoder = gcnew CarenWICBitmapDecoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpBitmapDecoder, Param_Out_BitmapDecoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICBitmapDecoder. Os valores disponiveis para (Param_GuidFormatoContainer) e (Param_GuidVendor) listados aqui, não são os unicos disponiveis.
/// Esses são apenas os valores suportados nativamente pelo sistema operacional e não incluem codecs de terceiros que possam está habilitados para o WIC.
/// </summary>
/// <param name="Param_GuidFormatoContainer">O GUID para o formato de contêiner desejado. Consulte a estrutura (GUIDs_WIC_CONTAINERS_FORMATOS) para obter um dos codecs 
/// suportados pelo OS nativamente.</param>
/// <param name="Param_GuidVendor">O GUID para o fornecedor de codificador preferido. Consulte a estrutura (GUIDs_WIC_VENDORS) paraobter um dos fornecedores de codificadores 
/// suportados pelo OS nativamente.</param>
/// <param name="Param_Out_BitmapEncoder">Retorna uma interface(ICarenWICBitmapEncoder) que contém um ponteiro para o novo codificador.</param>
CarenResult CarenWICComponentFactory::CreateEncoder(
	String^ Param_GuidFormatoContainer,
	String^ Param_GuidVendor,
	[Out] ICarenWICBitmapEncoder^% Param_Out_BitmapEncoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidFormato = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IWICBitmapEncoder* vi_OutpBitmapEncoder = Nulo;

	//Cria os guids.
	vi_GuidFormato = Util.CreateGuidFromString(Param_GuidFormatoContainer);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateEncoder(vi_GuidFormato, &vi_GuidVendor, &vi_OutpBitmapEncoder);

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
	Param_Out_BitmapEncoder = gcnew CarenWICBitmapEncoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutpBitmapEncoder, Param_Out_BitmapEncoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância do codificador de metadados rápidos baseado no determinado ICarenWICBitmapDecoder.
/// Os codecs fornecidos pelo Windows não oferecem suporte à codificação rápida de metadados no nível do decodificador e apenas suportam codificação rápida de metadados no 
/// nível do frame. Para criar um codificador de metadados rápido a partir de um frame, consulte o método CreateFastMetadataEncoderFromFrameDecode.
/// </summary>
/// <param name="Param_Decoder">O decodificador para criar o codificador de metadados rápidos.</param>
/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
CarenResult CarenWICComponentFactory::CreateFastMetadataEncoderFromDecoder(
	ICarenWICBitmapDecoder^ Param_Decoder,
	[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapDecoder* vi_BitmapDecoder = Nulo;
	IWICFastMetadataEncoder* vi_OutFastMetadata = Nulo;

	//Recupera o ponteiro para o decoder.
	Resultado = RecuperarPonteiroCaren(Param_Decoder, &vi_BitmapDecoder);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateFastMetadataEncoderFromDecoder(vi_BitmapDecoder, &vi_OutFastMetadata);

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
	Param_Out_FastEncoder = gcnew CarenWICFastMetadataEncoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutFastMetadata, Param_Out_FastEncoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância do codificador de metadados rápidos com base no frame de imagem dado. 
/// </summary>
/// <param name="Param_BitmapFrameDecode">Um ICarenWICBitmapFrameDecode que será utilizado para criar o ICarenWICFastMetadataEncoder.</param>
/// <param name="Param_Out_FastEncoder">Retorna uma interface(ICarenWICFastMetadataEncoder) que contém um ponteiro para o novo codificador rapido de metadados.</param>
CarenResult CarenWICComponentFactory::CreateFastMetadataEncoderFromFrameDecode(
	ICarenWICBitmapFrameDecode^ Param_BitmapFrameDecode,
	[Out] ICarenWICFastMetadataEncoder^% Param_Out_FastEncoder)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapFrameDecode* vi_BitmapFrameDecode = Nulo;
	IWICFastMetadataEncoder* vi_OutFastMetadata = Nulo;

	//Recupera o ponteiro para o decoder.
	Resultado = RecuperarPonteiroCaren(Param_BitmapFrameDecode, &vi_BitmapFrameDecode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateFastMetadataEncoderFromFrameDecode(vi_BitmapFrameDecode, &vi_OutFastMetadata);

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
	Param_Out_FastEncoder = gcnew CarenWICFastMetadataEncoder();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_OutFastMetadata, Param_Out_FastEncoder);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICFormatConverter. 
/// </summary>
/// <param name="Param_Out_FormatConverter">Retorna uma interface(ICarenWICFormatConverter) que contém um ponteiro para o novo conversor de formato de pixels.</param>
CarenResult CarenWICComponentFactory::CreateFormatConverter([Out] ICarenWICFormatConverter^% Param_Out_FormatConverter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICFormatConverter* vi_pOutWicFormatConverter = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateFormatConverter(&vi_pOutWicFormatConverter);

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
	Param_Out_FormatConverter = gcnew CarenWICFormatConverter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutWicFormatConverter, Param_Out_FormatConverter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICPalette. 
/// </summary>
/// <param name="Param_Out_WicPaleta">Retorna uma interface(ICarenWICPalette) que contém um ponteiro para a nova tabela de cores.</param>
CarenResult CarenWICComponentFactory::CreatePalette([Out] ICarenWICPalette^% Param_Out_WicPaleta)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICPalette* vi_pOutPaleta = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePalette(&vi_pOutPaleta);

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
	Param_Out_WicPaleta = gcnew CarenWICPalette();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutPaleta, Param_Out_WicPaleta);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância de um escritor de consultas. 
/// </summary>
/// <param name="Param_GuidFormatoMetadata">O GUID para o formato de metadados desejado.</param>
/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
CarenResult CarenWICComponentFactory::CreateQueryWriter(
	String^ Param_GuidFormatoMetadata,
	String^ Param_GuidVendor,
	[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidFormato = GUID_NULL;
	GUID vi_GuidVendor = GUID_NULL;
	IWICMetadataQueryWriter* vi_pOutMetadataWriter = Nulo;

	//Cria os guids.
	vi_GuidFormato = Util.CreateGuidFromString(Param_GuidFormatoMetadata);
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQueryWriter(vi_GuidFormato, &vi_GuidVendor, &vi_pOutMetadataWriter);

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
	Param_Out_QueryWriter = gcnew CarenWICMetadataQueryWriter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutMetadataWriter, Param_Out_QueryWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância de um escritor de consulta com base no leitor de consultas. O escritor de consultas será pré-povoado com metadados do leitor de consulta. 
/// </summary>
/// <param name="Param_QueryReader">O ICarenWICMetadataQueryReader para criar o ICarenWICMetadataQueryWriter.</param>
/// <param name="Param_GuidVendor">O GUID para o vendedor de metadata preferido. Use NULO se não houver fornecedor preferencial.</param>
/// <param name="Param_Out_QueryWriter">Retorna uma interface(ICarenWICMetadataQueryWriter) que contém um ponteiro para o novo escritor de consultas.</param>
CarenResult CarenWICComponentFactory::CreateQueryWriterFromReader(
	ICarenWICMetadataQueryReader^ Param_QueryReader,
	String^ Param_GuidVendor,
	[Out] ICarenWICMetadataQueryWriter^% Param_Out_QueryWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICMetadataQueryReader* vi_pMetadataReader = Nulo;
	GUID vi_GuidVendor = GUID_NULL;
	IWICMetadataQueryWriter* vi_pOutMetadataWriter = Nulo;

	//Recupera o ponteiro para a interface do leitor de metadados.
	Resultado = RecuperarPonteiroCaren(Param_QueryReader, &vi_pMetadataReader);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Cria o guid.
	vi_GuidVendor = Util.CreateGuidFromString(Param_GuidVendor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateQueryWriterFromReader(vi_pMetadataReader, &vi_GuidVendor, &vi_pOutMetadataWriter);

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
	Param_Out_QueryWriter = gcnew CarenWICMetadataQueryWriter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutMetadataWriter, Param_Out_QueryWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma nova instância da classe ICarenWICStream. 
/// </summary>
/// <param name="Param_Out_WicStream">Retorna uma interface(ICarenWICStream) que contém um ponteiro para o novo fluxo WIC.</param>
CarenResult CarenWICComponentFactory::CreateStream([Out] ICarenWICStream^% Param_Out_WicStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICStream* vi_pOutStream = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateStream(&vi_pOutStream);

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
	Param_Out_WicStream = gcnew CarenWICStream();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutStream, Param_Out_WicStream);

Done:;
	//Retorna o resultado.
	return Resultado;
}