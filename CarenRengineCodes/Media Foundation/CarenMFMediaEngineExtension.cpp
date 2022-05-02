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
#include "CarenMFMediaEngineExtension.h"

//Destruidor.
CarenMFMediaEngineExtension::~CarenMFMediaEngineExtension()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineExtension::CarenMFMediaEngineExtension()
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
CarenResult CarenMFMediaEngineExtension::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineExtension::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineExtension*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineExtension**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineExtension::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineExtension*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineExtension**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineExtension::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineExtension::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaEngineExtension::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaEngineExtension::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineExtension::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineExtension::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaEngineExtension::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineExtension();
}



// Métodos da interface proprietária(ICarenMFMediaEngineExtension)


/// <summary>
/// Começa uma solicitação assíncrona para criar um fluxo de byteou uma fonte de mídia.
/// </summary>
/// <param name="Param_Url">A URL do recurso de mídia.</param>
/// <param name="Param_FluxoBytes">Um ponteiro para a interface ICarenMFByteStream.</param>
/// <param name="Param_Tipo">Um membro da enumeração CA_MF_OBJECT_TYPE que especifica qual tipo de objeto criar.</param>
/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro para a interface IUnknown. Este ponteiro pode ser usado para cancelar a operação assíncrona, 
/// passando o ponteiro para o método ICarenMFMediaEngineExtension::CancelarCriacaoObjeto.</param>
/// <param name="Param_Callback">Um ponteiro para a interface ICarenMFAsyncCallback. Esta interface é usada para sinalizar a conclusão da operação assíncrona.</param>
/// <param name="Param_ObjetoEstado">Um ponteiro para um objeto de estado implementado pelo usuário. Você pode usar este objeto para conter informações do estado
/// para o retorno de chamada. O objeto é devolvido ao chamador quando o retorno de chamada é invocado. Este parâmetro pode ser NULO.</param>
CarenResult CarenMFMediaEngineExtension::BeginCreateObject(
String^ Param_Url,
ICarenMFByteStream^ Param_FluxoBytes,
CA_MF_OBJECT_TYPE Param_Tipo,
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
	BSTR vi_pUrl = Nulo;
	IMFByteStream* vi_pByteStream = Nulo;
	IUnknown* vi_pOutCookieCancel = Nulo;
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjetoEstado = Nulo;

	//Converte a string se fornecida
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToBSTR(Param_Url);

	//Recupera o ponteiro para o fluxo de bytes se fornecido.
	if (ObjetoGerenciadoValido(Param_FluxoBytes))
		CarenGetPointerFromICarenSafe(Param_FluxoBytes, vi_pByteStream);

	//Recupera o ponteiro para a interface de callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Recupera o ponteiro para o objeto de estado se fornecido.
	if(ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjetoEstado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginCreateObject(
		vi_pUrl,
		vi_pByteStream,
		static_cast<MF_OBJECT_TYPE>(Param_Tipo),
		&vi_pOutCookieCancel,
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

	//Cria a interface que vai retornar o Cookie de cancelamento
	Param_Out_CookieCancelamento = gcnew Caren();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutCookieCancel, Param_Out_CookieCancelamento, true);

Done:;
	//Libera a memória utilizada pela String BSTR.
	DeletarStringBSTRSafe(&vi_pUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cancela a solicitação atual para criar um objeto.
/// </summary>
/// <param name="Param_CookieCancelamento">O ponteiro que foi devolvido no parâmetro (Param_Out_CookieCancelamento) do método ICarenMFMediaEngineExtension::CriarObjetoAsync.</param>
CarenResult CarenMFMediaEngineExtension::CancelCreateObject(ICaren^ Param_CookieCancelamento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pCookieCancel = Nulo;

	//Recupera o ponteiro para a interface do cookie.
	CarenGetPointerFromICarenSafe(Param_CookieCancelamento, vi_pCookieCancel);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CancelObjectCreation(vi_pCookieCancel);

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
/// Verifica se o objeto pode carregar um tipo especificado de recurso de mídia.
/// </summary>
/// <param name="Param_AudioOnly">Se TRUE, o Media Engine será configurado para o modo somente áudio. Caso contrário, o Media Engine está configurado para o 
/// modo áudio-vídeo.</param>
/// <param name="Param_MimeType">Uma sequência que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
/// <param name="Param_Out_Resultado">Recebe um membro da enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
CarenResult CarenMFMediaEngineExtension::CanPlayType(
Boolean Param_AudioOnly,
String^ Param_MimeType,
[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pMimeType = Nulo;
	MF_MEDIA_ENGINE_CANPLAY vi_OutCanPlay = MF_MEDIA_ENGINE_CANPLAY::MF_MEDIA_ENGINE_CANPLAY_NOT_SUPPORTED;

	//Converte a string para a BSTR.
	vi_pMimeType = Util.ConverterStringToBSTR(Param_MimeType);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CanPlayType(Param_AudioOnly ? TRUE : FALSE, vi_pMimeType, &vi_OutCanPlay);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define o resultado no parametro de saida.
	Param_Out_Resultado = static_cast<CA_MF_MEDIA_ENGINE_CANPLAY>(vi_OutCanPlay);

Done:;
	//Libera a memória para a string BSTR.
	DeletarStringBSTRSafe(&vi_pMimeType);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Completa uma solicitação assíncrona para criar um fluxo de byteou fonte de mídia.
/// </summary>
/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult.</param>
/// <param name="Param_Ref_Objeto">Recebe um ponteiro para interface do Media Source ou Byte Stream de acordo com o solicitado. Esse paramêtro não pode ser NULO. 
/// O usuário é responsável por liberar a interface.</param>
CarenResult CarenMFMediaEngineExtension::EndCreateObject(
ICarenMFAsyncResult^ Param_Resultado,
ICaren^% Param_Ref_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* vi_pResultado = Nulo;
	IUnknown* vi_pOutObjetoCreated = Nulo;

	//Recupera o ponteiro para a interface do resultado.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pResultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndCreateObject(vi_pResultado, &vi_pOutObjetoCreated);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de destino criada pelo usuário.
	CarenSetPointerToICarenSafe(vi_pOutObjetoCreated, Param_Ref_Objeto, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}