﻿/*
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
#include "CarenWICMetadataQueryReader.h"

//Destruidor.
CarenWICMetadataQueryReader::~CarenWICMetadataQueryReader()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICMetadataQueryReader::CarenWICMetadataQueryReader()
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
CarenResult CarenWICMetadataQueryReader::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataQueryReader::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataQueryReader*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataQueryReader**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICMetadataQueryReader::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICMetadataQueryReader*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICMetadataQueryReader**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataQueryReader::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICMetadataQueryReader::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICMetadataQueryReader::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICMetadataQueryReader::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICMetadataQueryReader::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICMetadataQueryReader::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICMetadataQueryReader::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICMetadataQueryReader();
}



// Métodos da interface proprietária(ICarenWICMetadataQueryReader)


/// <summary>
/// Obtém o formato de contêiner de leitores de consulta de metadados. 
/// </summary>
/// <param name="Param_Out_GuidContainerFormat">Recebe o GUID que representa o tipo do formato cointainer.</param>
CarenResult CarenWICMetadataQueryReader::GetContainerFormat([Out] String^% Param_Out_GuidContainerFormat)
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
CarenResult CarenWICMetadataQueryReader::GetEnumerator([Out] ICarenEnumString^% Param_Out_EnumString)
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
CarenResult CarenWICMetadataQueryReader::GetLocation(
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
/// <param name="Param_Out_Valor">Retorna uma estrutura(CA_PROPVARIANT) que armazena o bloco de metadados ou item solicitado.</param>
CarenResult CarenWICMetadataQueryReader::GetMetadataByName(
String^ Param_Nome,
[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	PWSTR pNome = NULL;
	LPPROPVARIANT vi_OutPropVar = Nulo;

	//Converte a string.
	pNome = Util.ConverterStringToWCHAR(Param_Nome);

	//Inicializa a propvariant
	IniciarPropVariant(&vi_OutPropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMetadataByName(pNome, vi_OutPropVar);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura nativa para a gerenciada.
	Param_Out_Valor = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutPropVar);

Done:;
	//Libera a propvariant
	DeletarPropVariantSafe(&vi_OutPropVar);

	//Libera a memória utilizada pela string
	DeletarStringAllocatedSafe(&pNome);

	//Retorna o resultado.
	return Resultado;
}