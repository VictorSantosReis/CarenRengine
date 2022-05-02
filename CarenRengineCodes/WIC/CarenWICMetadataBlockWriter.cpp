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
#include "CarenWICMetadataBlockWriter.h"

//Destruidor.
CarenWICMetadataBlockWriter::~CarenWICMetadataBlockWriter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICMetadataBlockWriter::CarenWICMetadataBlockWriter()
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
CarenResult CarenWICMetadataBlockWriter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataBlockWriter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataBlockWriter*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataBlockWriter**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataBlockWriter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataBlockWriter*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataBlockWriter**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataBlockWriter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataBlockWriter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICMetadataBlockWriter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICMetadataBlockWriter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICMetadataBlockWriter::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICMetadataBlockWriter::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICMetadataBlockWriter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICMetadataBlockWriter();
}



// Métodos da interface proprietária(ICarenWICMetadataBlockWriter)


/// <summary>
/// Adiciona um bloco de metadados de alto nível adicionando um ICarenWICMetadataWriter para ele. 
/// </summary>
/// <param name="Param_MetadataWriter">O escritor de metadados para adicionar à imagem.</param>
CarenResult CarenWICMetadataBlockWriter::AddWriter(ICarenWICMetadataWriter^ Param_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataWriter* vi_pMetadaWriter = Nulo;

	//Recupera o ponteiro para o escritor.
	Resultado = RecuperarPonteiroCaren(Param_MetadataWriter, &vi_pMetadaWriter);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddWriter(vi_pMetadaWriter);

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
/// Recupera o ICarenWICMetadataWriter que reside no índice especificado. 
/// </summary>
/// <param name="Param_Index">O índice do escritor de metadados a ser recuperado. Este índice é baseado em zero.</param>
/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados que reside no índice especificado.</param>
CarenResult CarenWICMetadataBlockWriter::GetWriterByIndex(
UInt32 Param_Index,
[Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataWriter* vi_pOutMetadataWriter = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWriterByIndex(Param_Index, &vi_pOutMetadataWriter);

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
	Param_Out_MetadataWriter = gcnew CarenWICMetadataWriter();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(vi_pOutMetadataWriter, Param_Out_MetadataWriter);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa um ICarenWICMetadataBlockWriter do dado ICarenWICMetadataBlockReader. Isso prepovoará o autor do bloco de metadados com todos os metadados no leitor de blocos de metadados. 
/// </summary>
/// <param name="Param_MetadataReader">Uma interface(ICarenWICMetadataBlockReader) que será usada para inicializar o escritor.</param>
CarenResult CarenWICMetadataBlockWriter::InitializeFromBlockReader(ICarenWICMetadataBlockReader^ Param_MetadataReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataBlockReader* vi_pMetadataBlockReader = Nulo;

	//Recupera o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_MetadataReader, &vi_pMetadataBlockReader);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromBlockReader(vi_pMetadataBlockReader);

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
/// Remove o escritor de metadados do local do índice especificado.
/// Depois de remover um escritor de metadados, espera-se que os escritores de metadados restantes se movam para ocupar o local desocupado. Os índices para itens de 
/// metadados restantes, bem como a contagem, mudarão.
/// </summary>
/// <param name="Param_Index">O índice do escritor de metadados para remover.</param>
CarenResult CarenWICMetadataBlockWriter::RemoveWriterByIndex(UInt32 Param_Index)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveWriterByIndex(Param_Index);

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
/// Substitui o escritor de metadados no local do índice especificado.
/// Normalmente, o escritor de metadados atuais no índice especificado será substituído pelo novo escritor. No entanto, o autor de metadados app0 não pode ser 
/// substituído dentro de um fluxo JPEG. Esta função não pode ser usada para adicionar escritores de metadados. Se não houver nenhum autor de metadados no índice especificado, a função falhará.
/// </summary>
/// <param name="Param_Index">A posição do índice para colocar o escritor de metadados. Este índice é baseado em zero.</param>
/// <param name="Param_MetadataWriter">A interface de escrita de metadados a ser definida no indice.</param>
CarenResult CarenWICMetadataBlockWriter::SetWriterByIndex(
UInt32 Param_Index,
ICarenWICMetadataWriter^ Param_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataWriter* vi_pMetadataWriter = Nulo;

	//Recupera o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_MetadataWriter, &vi_pMetadataWriter);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetWriterByIndex(Param_Index, vi_pMetadataWriter);

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




// Métodos da interface (ICarenWICMetadataBlockReader)


/// <summary>
/// Recupera o formato do recipiente do decodificador. 
/// </summary>
/// <param name="Param_Out_GuidFormatoContainer">Retorna o formato do contêiner do decodificador. </param>
CarenResult CarenWICMetadataBlockWriter::GetContainerFormat([Out] String^% Param_Out_GuidFormatoContainer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidFormato = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerFormat(&OutGuidFormato);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_GuidFormatoContainer = Util.ConverterGuidToString(OutGuidFormato);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o número de blocos de metadados de nível superior. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de blocos de metadados de nível superior.</param>
CarenResult CarenWICMetadataBlockWriter::GetCount([Out] UInt32% Param_Out_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	UINT32 OutCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCount(&OutCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_Quantidade = OutCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma enumeração dos objetos ICarenWICMetadataReader representando cada um dos blocos de metadados de nível superior. 
/// </summary>
/// <param name="Param_Out_EnumMetadata">Retorna uma interface(ICarenEnumUnknown) que contém um ponteiro para uma enumeração dos objetos ICarenWICMetadataReader.</param>
CarenResult CarenWICMetadataBlockWriter::GetEnumerator([Out] ICarenEnumUnknown^% Param_Out_EnumMetadata)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IEnumUnknown* pOutEnum = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEnumerator(&pOutEnum);

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
	Param_Out_EnumMetadata = gcnew CarenEnumUnknown();

	//Define ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutEnum, Param_Out_EnumMetadata);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera um ICarenWICMetadataReader para um bloco de metadados de nível superior especificado. 
/// </summary>
/// <param name="Param_Index">O índice do bloco de metadados de nível superior desejado para recuperar.</param>
/// <param name="Param_Out_MetadataReader">Retorna uma interface(ICarenWICMetadataReader) que contém um ponteiro para o ICarenWICMetadataReader especificado por (Param_Index).</param>
CarenResult CarenWICMetadataBlockWriter::GetReaderByIndex(
	UInt32 Param_Index,
	[Out] ICarenWICMetadataReader^% Param_Out_MetadataReader)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICMetadataReader* pOutMetadataReader = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetReaderByIndex(Param_Index, &pOutMetadataReader);

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
	Param_Out_MetadataReader = gcnew CarenWICMetadataReader();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutMetadataReader, Param_Out_MetadataReader);

Done:;
	//Retorna o resultado.
	return Resultado;
}