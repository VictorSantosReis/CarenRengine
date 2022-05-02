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
#include "CarenWICMetadataWriterInfo.h"

//Destruidor.
CarenWICMetadataWriterInfo::~CarenWICMetadataWriterInfo()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICMetadataWriterInfo::CarenWICMetadataWriterInfo()
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
CarenResult CarenWICMetadataWriterInfo::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataWriterInfo::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataWriterInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataWriterInfo**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataWriterInfo::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataWriterInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataWriterInfo**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataWriterInfo::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataWriterInfo::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICMetadataWriterInfo::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICMetadataWriterInfo::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICMetadataWriterInfo::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICMetadataWriterInfo::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICMetadataWriterInfo::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICMetadataWriterInfo();
}



// Métodos da interface proprietária(ICarenWICMetadataWriterInfo)


/// <summary>
/// Cria uma instância de um ICarenWICMetadataWriter. 
/// </summary>
/// <param name="Param_Out_MetadataWriter">Retorna uma interface(ICarenWICMetadataWriter) que contém um ponteiro para o escritor de metadados.</param>
CarenResult CarenWICMetadataWriterInfo::CreateInstance([Out] ICarenWICMetadataWriter^% Param_Out_MetadataWriter)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICMetadataWriter* vi_OutWriter = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInstance(&vi_OutWriter);

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

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_OutWriter, Param_Out_MetadataWriter, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe o cabeçalho de metadados para o escritor de metadados. 
/// </summary>
/// <param name="Param_GuidContainerFormat">O GUID do contêiner de formato para o qual obter o cabeçalho.</param>
/// <param name="Param_SizeHeader">O tamanho do buffer em (Param_Ref_Header).</param>
/// <param name="Param_Ref_Header">Retorna uma estrutura com o header dos metadados. Defina como NULO para retornar o (SizeHeader) em (Param_Out_SizeAtual) necessário para o 
/// parametro (Param_SizeHeader).</param>
/// <param name="Param_Out_SizeAtual">Retorna o tamanho real do cabeçalho.</param>
CarenResult CarenWICMetadataWriterInfo::GetHeader(
String^ Param_GuidContainerFormat,
UInt32 Param_SizeHeader,
CA_WICMetadataHeader^% Param_Ref_Header,
[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID vi_GuidFormat = GUID_NULL;
	WICMetadataHeader vi_OutHeader = {}; // Pode ser NULO para o usuário recuperar o size para o parametro (Param_SizeHeader).
	UINT32 vi_OutSizeAtual = 0;

	//Converte a string para guid
	vi_GuidFormat = Util.CreateGuidFromString(Param_GuidContainerFormat);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetHeader(vi_GuidFormat, Param_SizeHeader, ObjetoGerenciadoValido(Param_Ref_Header) ? &vi_OutHeader : Nulo, &vi_OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se vai retornar o Metadata header e converte os dados.
	if (ObjetoGerenciadoValido(Param_Ref_Header))
		Param_Ref_Header = Util.ConverterWICMetadataHeaderUnmanaged_ToManaged(&vi_OutHeader);

	//Define o valor do size atual do header.
	Param_Out_SizeAtual = vi_OutSizeAtual;

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICMetadataHandlerInfo)


/// <summary>
/// Determina se o manipulador de metadados requer um tamanho fixo. 
/// </summary>
/// <param name="Param_Out_FixedSize">Retorna TRUE se um tamanho fixo for necessário; caso contrário, FALSO.</param>
CarenResult CarenWICMetadataWriterInfo::DoesRequireFixedSize([Out] Boolean% Param_Out_FixedSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutFixedSize = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesRequireFixedSize(&OutFixedSize);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_FixedSize = OutFixedSize;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se o manipulador requer um fluxo completo. 
/// </summary>
/// <param name="Param_Out_RequerFullStream">Retorna TRUE se um fluxo completo for necessário; caso contrário, FALSO.</param>
CarenResult CarenWICMetadataWriterInfo::DoesRequireFullStream([Out] Boolean% Param_Out_RequerFullStream)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutRequerFullStream = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesRequireFullStream(&OutRequerFullStream);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_RequerFullStream = OutRequerFullStream;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se o manipulador de metadados suporta preenchimento. 
/// </summary>
/// <param name="Param_Out_SuportaPadding">Retorna TRUE se o preenchimento for suportado; caso contrário, FALSO.</param>
CarenResult CarenWICMetadataWriterInfo::DoesSupportPadding([Out] Boolean% Param_Out_SuportaPadding)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DoesSupportPadding(&OutSuporte);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado no parametro de saida.
	Param_Out_SuportaPadding = OutSuporte;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera os formatos de contêiner suportados pelo manipulador de metadados. 
/// </summary>
/// <param name="Param_TamanhoArray"><O tamanho da matriz (Param_Out_ArrayGuidsFormatosContainer).</param>
/// <param name="Param_Ref_Out_ArrayGuidsFormatosContainer">Retorna uma matriz que recebe os formatos de contêiner suportados pelo manipulador de metadados. O usuário deve criar matriz com a capacidade
/// indicada no (Param_TamanhoArray).</param>
/// <param name="Param_Out_QuantidadeRetornada">Retorna o número real de GUIDs adicionados à matriz. Para obter o número de formatos de contêiner suportados, 
/// passe NULO para (Param_Ref_Out_ArrayGuidsFormatosContainer).</param>
CarenResult CarenWICMetadataWriterInfo::GetContainerFormats(
	UInt32 Param_TamanhoArray,
	cli::array<String^>^% Param_Ref_Out_ArrayGuidsFormatosContainer,
	[Out] UInt32% Param_Out_QuantidadeRetornada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID* pArrayGuidsFormatos = Nulo; //Pode ser NULO para o usuário obter a quantidade necessária para conter os guids.
	UINT32 OutCountRetornada = 0;

	//Verifica se forneceu o array para obter os dados.
	if (ObjetoGerenciadoValido(Param_Ref_Out_ArrayGuidsFormatosContainer))
	{
		//Cria a matriz nativa.
		pArrayGuidsFormatos = CriarMatrizEstruturas<GUID>(Param_TamanhoArray);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetContainerFormats(Param_Out_QuantidadeRetornada, pArrayGuidsFormatos, &OutCountRetornada);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Faz um for para converter os dados e definir na matriz de saida.
	for (UINT32 i = 0; i < OutCountRetornada; i++)
	{
		//Converte e define no index especificado.
		Param_Ref_Out_ArrayGuidsFormatosContainer[i] = Util.ConverterGuidToString(pArrayGuidsFormatos[i]);
	}

Done:;
	//Libera a memória utilizada pela matriz.
	DeletarMatrizEstruturasSafe(&pArrayGuidsFormatos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o fabricante do dispositivo do manipulador de metadados. 
/// </summary>
/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceManufacturer).</param>
/// <param name="Param_Ref_DeviceManufacturer">Retorna a String que recebe o nome do fabricante do dispositivo.</param>
/// <param name="Param_Out_LarguraReal">Retorna o comprimento real da sequência de strinds necessário para obter o nome inteiro do fabricante do dispositivo.</param>
CarenResult CarenWICMetadataWriterInfo::GetDeviceManufacturer(
	UInt32 Param_TamanhoBufferString,
	String^% Param_Ref_DeviceManufacturer,
	[Out] UInt32% Param_Out_LarguraReal)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pOutDeviceManufacturer = Nulo; // Pode ser nulo para retornar o tamanho necessário para a string.
	UINT32 OutSizeReal = 0;

	//Verifica se a string de retorno é valida e aloca os dados.
	if (ObjetoGerenciadoValido(Param_Ref_DeviceManufacturer))
	{
		//Aloca memória para a string.
		pOutDeviceManufacturer = CriarStringCoTask<WCHAR>(Param_TamanhoBufferString);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceManufacturer(Param_TamanhoBufferString, pOutDeviceManufacturer == Nulo ? Nulo : pOutDeviceManufacturer, &OutSizeReal);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string foi fornecida para ser retornada.
	if (ObjetoValido(pOutDeviceManufacturer))
	{
		//Converte a string e define no parametro de saida.
		Param_Ref_DeviceManufacturer = gcnew String(pOutDeviceManufacturer);
	}

	//Define a largura real da string.
	Param_Out_LarguraReal = OutSizeReal;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera os modelos do dispositivo que suportam o manipulador de metadados. 
/// </summary>
/// <param name="Param_TamanhoBufferString">O tamanho da String em (Param_Ref_DeviceModels).</param>
/// <param name="Param_Ref_DeviceModels">Retorna os modelos do dispositivo suportados pelo manipulador de metadados.</param>
/// <param name="Param_Out_LarguraReal">Retorna o comprimento real necessário para recuperar os modelos do dispositivo.</param>
CarenResult CarenWICMetadataWriterInfo::GetDeviceModels(
	UInt32 Param_TamanhoBufferString,
	String^% Param_Ref_DeviceModels,
	[Out] UInt32% Param_Out_LarguraReal)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PWSTR pOutDeviceModels = Nulo; // Pode ser nulo para retornar o tamanho necessário para a string.
	UINT32 OutSizeReal = 0;

	//Verifica se a string de retorno é valida e aloca os dados.
	if (ObjetoGerenciadoValido(Param_Ref_DeviceModels))
	{
		//Aloca memória para a string.
		pOutDeviceModels = CriarStringCoTask<WCHAR>(Param_TamanhoBufferString);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDeviceModels(Param_TamanhoBufferString, pOutDeviceModels == Nulo ? Nulo : pOutDeviceModels, &OutSizeReal);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string foi fornecida para ser retornada.
	if (ObjetoValido(pOutDeviceModels))
	{
		//Converte a string e define no parametro de saida.
		Param_Ref_DeviceModels = gcnew String(pOutDeviceModels);
	}

	//Define a largura real da string.
	Param_Out_LarguraReal = OutSizeReal;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o formato de metadados do manipulador de metadados. 
/// </summary>
/// <param name="Param_Out_GuidFormatoMetadata">Retorna o GUID do formato metadados.</param>
CarenResult CarenWICMetadataWriterInfo::GetMetadataFormat([Out] String^% Param_Out_GuidFormatoMetadata)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutFormatoMetadata = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataFormat(&OutFormatoMetadata);

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
	Param_Out_GuidFormatoMetadata = Util.ConverterGuidToString(OutFormatoMetadata);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenWICComponentInfo)


/// <summary>
/// Recupera o nome do autor do componente. Se (Param_SizeAutorString) for 0 e (Param_Ref_Autor) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeAutorString">O tamanho da String (Param_Ref_Autor).</param>
/// <param name="Param_Ref_Autor">Recebe o nome do autor do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da instalação.
///  Para componentes embutidos, essas Strings estão sempre em inglês.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome dos autores do componente. O nome do autor é opcional; se um nome autor não for especificado pelo componente,
///  o comprimento devolvido será 0.</param>
CarenResult CarenWICMetadataWriterInfo::GetAuthor(
	UInt32 Param_SizeAutorString,
	String^% Param_Ref_Autor,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNomeAutor = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar o nome do autor.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeAutorString > 0)
		pOutNomeAutor = CriarStringCoTask<WCHAR>(Param_SizeAutorString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAuthor(Param_SizeAutorString, Param_SizeAutorString == 0 ? NULL : pOutNomeAutor, &OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutNomeAutor))
		Param_Ref_Autor = gcnew String(pOutNomeAutor);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutNomeAutor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o identificador de classe do componente (CLSID) 
/// </summary>
/// <param name="Param_Out_CLSID">Recebe o CLSID do componente.</param>
CarenResult CarenWICMetadataWriterInfo::GetCLSID([Out] String^% Param_Out_CLSID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutCLSID = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCLSID(&OutCLSID);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o Guid em String.
	Param_Out_CLSID = Util.ConverterGuidToString(OutCLSID);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o CA_WICComponentType do componente. 
/// </summary>
/// <param name="Param_Out_Type">Recebe um enum CA_WICComponentType que define o tipo do componente.</param>
CarenResult CarenWICMetadataWriterInfo::GetComponentType([Out] CA_WICComponentType% Param_Out_Type)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICComponentType OutCompType;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetComponentType(&OutCompType);

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
	Param_Out_Type = static_cast<CA_WICComponentType>(OutCompType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o nome amigável do componente, que é um nome de exibição legível por humanos para o componente.
/// Se (Param_SizeNomeString) for 0 e (Param_Ref_NomeAmigavel) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeNomeString">O tamanho da String em (Param_Ref_NomeAmigavel).</param>
/// <param name="Param_Ref_NomeAmigavel">Recebe o nome amigável do componente. A localização da sequência depende do valor que o codec escreveu para o registro no momento da 
/// instalação. Para componentes embutidos, essas cordas 
/// estão sempre em inglês.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real do nome amigável do componente.</param>
CarenResult CarenWICMetadataWriterInfo::GetFriendlyName(
	UInt32 Param_SizeNomeString,
	String^% Param_Ref_NomeAmigavel,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutNomeAmigavel = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar o nome amigavel.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeNomeString > 0)
		pOutNomeAmigavel = CriarStringCoTask<WCHAR>(Param_SizeNomeString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFriendlyName(Param_SizeNomeString, Param_SizeNomeString == 0 ? NULL : pOutNomeAmigavel, &OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutNomeAmigavel))
		Param_Ref_NomeAmigavel = gcnew String(pOutNomeAmigavel);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutNomeAmigavel);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o status de assinatura do componente. A assinatura não é usada pelo WIC. Portanto, todos os componentes WICComponentSigned. Esta função pode ser usada para 
/// determinar se um componente não possui nenhum componente 
/// binário ou foi adicionado à lista de componentes desabilitados no registro.
/// </summary>
/// <param name="Param_Out_Status">Retorna um enum que recebe o status do componente.</param>
CarenResult CarenWICMetadataWriterInfo::GetSigningStatus([Out] CA_WICComponentSigning% Param_Out_Status)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD OutCompSigning;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSigningStatus(&OutCompSigning);

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
	Param_Out_Status = static_cast<CA_WICComponentSigning>(OutCompSigning);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a versão de especificação do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão spec.
/// Se (Param_SizeSpecString) for 0 e (Param_Ref_SpecVersion) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeSpecString">O tamanho da String em (Param_Ref_SpecVersion).</param>
/// <param name="Param_Ref_SpecVersion">Retorna uma string que contém uma sequência de cultura invariente da versão de especificação do componente. O formulário de versão 
/// é NN.NN.NN.NN.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão de especificação do componente. A versão de especificação é opcional; se um valor não for especificado
///  pelo componente, o comprimento devolvido será 0.</param>
CarenResult CarenWICMetadataWriterInfo::GetSpecVersion(
	UInt32 Param_SizeSpecString,
	String^% Param_Ref_SpecVersion,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutSpecVersion = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a versão de especificação.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeSpecString > 0)
		pOutSpecVersion = CriarStringCoTask<WCHAR>(Param_SizeSpecString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSpecVersion(Param_SizeSpecString, Param_SizeSpecString == 0 ? NULL : pOutSpecVersion, &OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutSpecVersion))
		Param_Ref_SpecVersion = gcnew String(pOutSpecVersion);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutSpecVersion);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o fornecedor GUID. 
/// </summary>
/// <param name="Param_Out_GuidVendor">Recebe o guid do fornecedor do componente.</param>
CarenResult CarenWICMetadataWriterInfo::GetVendorGUID([Out] String^% Param_Out_GuidVendor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID OutGuidVendor = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVendorGUID(&OutGuidVendor);

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
	Param_Out_GuidVendor = Util.ConverterGuidToString(OutGuidVendor);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a versão do componente. Todos os componentes embutidos retornam "1.0.0.0", exceto os formatos pixel, que não possuem uma versão.
/// Se (Param_SizeVersionString) for 0 e (Param_Ref_Version) for NULO, o tamanho do buffer necessário é devolvido em (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeVersionString">O tamanho da String em (Param_Ref_Version).</param>
/// <param name="Param_Ref_Version">Recebe uma sequência de cultura invariante da versão do componente.</param>
/// <param name="Param_Out_SizeAtual">Recebe o comprimento real da versão do componente. A versão é opcional; se um valor não for especificado pelo componente, o comprimento
///  devolvido será 0.</param>
CarenResult CarenWICMetadataWriterInfo::GetVersion(
	UInt32 Param_SizeVersionString,
	String^% Param_Ref_Version,
	[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutVersion = NULL; // O usuário pode definir NULO para recuperar o tamanho necessário para retornar a versão.
	UINT32 OutSizeAtual = 0;

	//Aloca o tamanho necessário para a string se (Param_SizeAutorString) for maior que 0.
	if (Param_SizeVersionString > 0)
		pOutVersion = CriarStringCoTask<WCHAR>(Param_SizeVersionString);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVersion(Param_SizeVersionString, Param_SizeVersionString == 0 ? NULL : pOutVersion, &OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se a string é valida e define no parametro de saida.
	if (ObjetoValido(pOutVersion))
		Param_Ref_Version = gcnew String(pOutVersion);

	//Define a largura atual da string.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Libera a memória utilizada pela string
	DeletarStringCoTaskSafe(&pOutVersion);

	//Retorna o resultado.
	return Resultado;
}