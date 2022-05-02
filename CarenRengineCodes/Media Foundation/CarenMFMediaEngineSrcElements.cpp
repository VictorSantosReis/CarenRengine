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
#include "CarenMFMediaEngineSrcElements.h"

//Destruidor.
CarenMFMediaEngineSrcElements::~CarenMFMediaEngineSrcElements()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineSrcElements::CarenMFMediaEngineSrcElements()
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
CarenResult CarenMFMediaEngineSrcElements::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineSrcElements::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineSrcElements*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineSrcElements**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineSrcElements::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineSrcElements*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineSrcElements**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineSrcElements::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineSrcElements::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaEngineSrcElements::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaEngineSrcElements::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineSrcElements::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineSrcElements::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaEngineSrcElements::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineSrcElements();
}



// Métodos da interface proprietária(ICarenMFMediaEngineSrcElements)


/// <summary>
/// Adiciona um elemento de origem ao final da lista.
/// </summary>
/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
CarenResult CarenMFMediaEngineSrcElements::AddElement(
	String^ Param_Url,
	String^ Param_Tipo,
	String^ Param_Midia
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pUrl = Nulo;
	BSTR vi_pTipo = Nulo;
	BSTR vi_pMidia = Nulo;

	//Converte as strings se tiverem sido informadas
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToBSTR(Param_Url);
	if (ObjetoGerenciadoValido(Param_Tipo))
		vi_pTipo = Util.ConverterStringToBSTR(Param_Tipo);
	if (ObjetoGerenciadoValido(Param_Midia))
		vi_pMidia = Util.ConverterStringToBSTR(Param_Midia);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddElement(vi_pUrl, vi_pTipo, vi_pMidia);

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
	//Libera a memória utilizada pelas strings.
	DeletarStringBSTRSafe(&vi_pUrl);
	DeletarStringBSTRSafe(&vi_pTipo);
	DeletarStringBSTRSafe(&vi_pMidia);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o número de elementos de origem na lista.
/// </summary>
/// <param name="Param_Out_Quantidade">Recebe o numero de elementos presente na lista.</param>
void CarenMFMediaEngineSrcElements::GetLength([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = static_cast<UInt32>(PonteiroTrabalho->GetLength());
}

/// <summary>
/// Obtém o tipo de mídia pretendido de um elemento na lista.
/// </summary>
/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_Midia">Recebe uma string que contém uma sequência de consulta de mídia. Se nenhum tipo de mídia for definido, este parâmetro receberá o valor NULO.</param>
CarenResult CarenMFMediaEngineSrcElements::GetMedia(
	UInt32 Param_Index,
	[Out] String^% Param_Out_Midia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutMedia = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMedia(static_cast<DWORD>(Param_Index), &vi_pOutMedia);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutMedia))
		Param_Out_Midia = gcnew String(vi_pOutMedia);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutMedia);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tipo MIME de um elemento na lista.
/// </summary>
/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_MimeType">Recebe uma string que contém o MIME Type. Se nenhum tipo de MIME for definido, este parâmetro receberá o valor NULO.</param>
CarenResult CarenMFMediaEngineSrcElements::GetType(
	UInt32 Param_Index,
	[Out] String^% Param_Out_MimeType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutMimeType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetType(static_cast<DWORD>(Param_Index), &vi_pOutMimeType);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutMimeType))
		Param_Out_MimeType = gcnew String(vi_pOutMimeType);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutMimeType);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a URL de um elemento na lista.
/// </summary>
/// <param name="Param_Index">>O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::GetLength.</param>
/// <param name="Param_Out_Url">Recebe uma string que contém a URL do elemento de origem. Se nenhuma URL for definida, este parâmetro receberá o valor NULO</param>
CarenResult CarenMFMediaEngineSrcElements::GetURL(
	UInt32 Param_Index,
	[Out] String^% Param_Out_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutUrl = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetURL(static_cast<DWORD>(Param_Index), &vi_pOutUrl);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se o objeto é valido e cria a string.
	if (ObjetoValido(vi_pOutUrl))
		Param_Out_Url = gcnew String(vi_pOutUrl);

Done:;
	//Libera a memória utilizada pela string BSTR
	DeletarStringBSTRSafe(&vi_pOutUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Remove todos os elementos de origem da lista.
/// </summary>
CarenResult CarenMFMediaEngineSrcElements::RemoveAllElements()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAllElements();

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