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
#include "CarenMFByteStreamHandler.h"

//Destruidor.
CarenMFByteStreamHandler::~CarenMFByteStreamHandler()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFByteStreamHandler::CarenMFByteStreamHandler()
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
CarenResult CarenMFByteStreamHandler::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFByteStreamHandler::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFByteStreamHandler*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFByteStreamHandler**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFByteStreamHandler::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFByteStreamHandler*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFByteStreamHandler**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFByteStreamHandler::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFByteStreamHandler::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFByteStreamHandler::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFByteStreamHandler::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFByteStreamHandler::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFByteStreamHandler::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFByteStreamHandler::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFByteStreamHandler();
}



// Métodos da interface proprietária(ICarenMFByteStreamHandler)


/// <summary>
/// Começa uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
/// </summary>
/// <param name="Param_FluxoBytes">Ponteiro para a interface ICarenMFByteStream do fluxo de byte.</param>
/// <param name="Param_Url">String que contém a URL original do fluxo de bytes. Este parâmetro pode ser NULO.</param>
/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_SOURCE_RESOLVER_FLAGS.</param>
/// <param name="Param_Props">Ponteiro para a interface ICarenPropertyStore de uma loja de propriedades. O manipulador de fluxo de bytes pode usar esta loja de propriedades 
/// para configurar o objeto. Este parâmetro pode ser NULO.</param>
/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro IUnknown na interface ICaren ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona 
/// passando este ponteiro para o método ICarenMFByteStreamHandler::CancelObjectCreation. O chamador deve liberar a interface. Este parâmetro pode ser NULO.</param>
/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface.</param>
/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado.
/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
CarenResult CarenMFByteStreamHandler::BeginCreateObject(
ICarenMFByteStream^ Param_FluxoBytes,
String^ Param_Url,
CA_SOURCE_RESOLVER_FLAGS Param_Flags,
ICarenPropertyStore^ Param_Props,
[Out] ICaren^% Param_Out_CookieCancelamento,
ICarenMFAsyncCallback^ Param_Callback,
ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pFluxo = Nulo; //Pode ser NULO.
	PWSTR vi_pUrl = Nulo; //Pode ser NULO.
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);
	IPropertyStore* vi_pPropStore = Nulo; //Pode ser NULO.
	IUnknown* vi_pOutCookie = Nulo; //Pode ser NULO.
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjetoEstado = Nulo; //Pode ser NULO;

	//Recupera o ponteiro para o fluxo se forneceido.
	if (ObjetoGerenciadoValido(Param_FluxoBytes))
		CarenGetPointerFromICarenSafe(Param_FluxoBytes, vi_pFluxo);

	//Converte a string para a url se valida.
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToWCHAR(Param_Url);

	//Recupera o ponteiro para a interface de propriedades se forneceida.
	if (ObjetoGerenciadoValido(Param_Props))
		CarenGetPointerFromICarenSafe(Param_Props, vi_pPropStore);

	//Recupera o ponteiro para o callback implementado pelo usuário.
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Recupera o ponteiro para a interface do objeto de estado se fornecido.
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjetoEstado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginCreateObject
	(
		vi_pFluxo,
		vi_pUrl,
		vi_Flags,
		vi_pPropStore,
		&vi_pOutCookie,
		vi_pCallback,
		vi_pObjetoEstado
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se foi retornado um Cookie de cancelamento e cria a interface a retornar o cookie
	if (ObjetoValido(vi_pOutCookie))
	{
		//Cria a interface que vai retornar o cookie.
		Param_Out_CookieCancelamento = gcnew Caren();

		//Define o ponteiro na interface
		CarenSetPointerToICarenSafe(vi_pOutCookie, Param_Out_CookieCancelamento, true);
	}

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cancela o pedido atual para criar uma fonte de mídia.
/// </summary>
/// <param name="Param_CookieCancelamento">Ponteiro para a interface ICaren que foi retornada no parâmetro (Param_Out_CookieCancelamento) do método 
/// ICarenMFByteStreamHandler::BeginCreateObject.</param>
CarenResult CarenMFByteStreamHandler::CancelObjectCreation(ICaren^ Param_CookieCancelamento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pCookie = Nulo;

	//Recupera o ponteiro para o Cookie.
	CarenGetPointerFromICarenSafe(Param_CookieCancelamento, vi_pCookie);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CancelObjectCreation(vi_pCookie);

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
/// Completa um pedido assíncrono para criar uma fonte de mídia.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que seu objeto de retorno de chamada recebeu no método Invocar.</param>
/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
/// <param name="Param_Ref_InterfaceObjeto">Recebe um ponteiro para a interface da fonte de mídia. O chamador deve criar a interface que vai receber o ponteiro.
/// O chamador deve liberar a interface quando não for mais utilizar.</param>
CarenResult CarenMFByteStreamHandler::EndCreateObject(
ICarenMFAsyncResult^ Param_Resultado,
[Out] CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
ICaren^% Param_Ref_InterfaceObjeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* vi_pResultado = Nulo;
	MF_OBJECT_TYPE vi_OutTipoObjeto = MF_OBJECT_TYPE::MF_OBJECT_INVALID;
	IUnknown* vi_OutObjetoCriado = Nulo;

	//Recupera o ponteiro para o resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pResultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndCreateObject(vi_pResultado, &vi_OutTipoObjeto, &vi_OutObjetoCriado);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o tipo do objeto criado no parametro de saida.
	Param_Out_TipoObjeto = static_cast<CA_MF_OBJECT_TYPE>(vi_OutTipoObjeto);

	//Define o ponteiro na interface inicializada pelo usuário que vai receber os dados.
	CarenSetPointerToICarenSafe(vi_OutObjetoCriado, Param_Ref_InterfaceObjeto, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o número máximo de bytes necessários para criar a fonte de mídia ou determinar que o manipulador de fluxo de bytes não 
/// pode analisar este fluxo.
/// </summary>
/// <param name="Param_Ref_MaximoNumeroBytes">Recebe o número máximo de bytes necessários.</param>
CarenResult CarenMFByteStreamHandler::GetMaxNumberOfBytesRequiredForResolution(UInt64% Param_Ref_MaximoNumeroBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 vi_OutMaximum = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMaxNumberOfBytesRequiredForResolution(&vi_OutMaximum);

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
	Param_Ref_MaximoNumeroBytes = vi_OutMaximum;

Done:;
	//Retorna o resultado.
	return Resultado;
}