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
#include "CarenMFSourceResolver.h"


//Destruidor.
CarenMFSourceResolver::~CarenMFSourceResolver()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFSourceResolver::CarenMFSourceResolver(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFSourceResolver* vi_pOutSourceResolver = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreateSourceResolver(&vi_pOutSourceResolver);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutSourceResolver;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFSourceResolver::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceResolver::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceResolver*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceResolver**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceResolver::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceResolver*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceResolver**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceResolver::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceResolver::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFSourceResolver::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFSourceResolver::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSourceResolver::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceResolver::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFSourceResolver::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFSourceResolver();
}



//
// Métodos da interface proprietaria
//

/// <summary>
/// (BeginCreateObjectFromByteStream) - Inicia uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
/// </summary>
/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
/// <param name="Param_Out_ObjetoCancel">Recebe um ponteiro ICaren ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
/// de ICarenMFSourceResolver::CancelObjectCreation. O chamador deve liberar a interface. Ignore esse valor se não deseja receber a interface de cancelamento.</param>
/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
CarenResult CarenMFSourceResolver::BeginCreateObjectFromByteStream
(
	ICarenMFByteStream^ Param_FluxoBytes,
	String^ Param_Url,
	Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
	ICarenPropertyStore^ Param_Propriedades,
	CarenParamResolver<ICaren^> Param_Out_ObjetoCancel,
	ICarenMFAsyncCallback^ Param_Callback,
	ICaren^ Param_ObjetoEstado
)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFByteStream* vi_pByteStream = NULL;
	LPCWSTR vi_pUrl = Nulo; //Pode ser Nulo.
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);
	IPropertyStore *vi_pPropertyStore = Nulo; //Pode ser Nulo.
	IUnknown* vi_pOutObjectCancel = Nulo; //Pode ser IGNORADO.
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjectState = Nulo; //Pode ser Nulo.

	//Tenta recuperar o ponteiro para as interfaces obrigatorias.
	CarenGetPointerFromICarenSafe(Param_FluxoBytes, vi_pByteStream);
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Converte a URL se fornecido
	if (StringObjetoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToConstWCHAR(Param_Url);

	//Verifica se forneceu a interface de propriedades e recupera o seu ponteiro.
	if (ObjetoGerenciadoValido(Param_Propriedades))
		CarenGetPointerFromICarenSafe(Param_Propriedades, vi_pPropertyStore);

	//Verifica se forneceu o objeto de estado devolvido na conclusão da operação assincrona.
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjectState);

	//Chama o método para Resolver a midia
	Hr = PonteiroTrabalho->BeginCreateObjectFromByteStream(
		vi_pByteStream,
		vi_pUrl,
		vi_Flags,
		vi_pPropertyStore,
		Param_Out_ObjetoCancel.IgnoreParameter? Nulo: &vi_pOutObjectCancel,
		vi_pCallback,
		vi_pObjectState
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

	//Verifica se o método retornou uma interface de cancelamento e define no parametro.
	if (ObjetoValido(vi_pOutObjectCancel))
		CarenSetPointerToICarenSafe(vi_pOutObjectCancel, Param_Out_ObjetoCancel.ObjetoParametro, true);

Done:;
	//Libera a memória para a string se ela for valida
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (BeginCreateObjectFromURL) - Inicia uma solicitação assíncrona para criar uma fonte de mídia ou um fluxo de bytes de uma URL.
/// </summary>
/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
/// <param name="Param_Flags">OR bit a bit dos sinalizadores.</param>
/// <param name="Param_Propriedades">Ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o esquema manipulador ou 
/// manipulador de fluxo de bytes que cria o objeto. O manipulador pode usar o armazenamento de propriedade para configurar o objeto. Este parâmetro pode ser nulo</param>
/// <param name="Param_Out_ObjetoCancel">Recebe um ponteiro ICaren ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
/// de ICarenMFSourceResolver::CancelObjectCreation. O chamador deve liberar a interface. Ignore esse valor se não deseja receber a interface de cancelamento.</param>
/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
CarenResult CarenMFSourceResolver::BeginCreateObjectFromURL
(
	String^ Param_Url,
	Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
	ICarenPropertyStore^ Param_Propriedades,
	CarenParamResolver<ICaren^> Param_Out_ObjetoCancel,
	ICarenMFAsyncCallback^ Param_Callback,
	ICaren^ Param_ObjetoEstado
)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	LPCWSTR vi_pUrl = Nulo; //Pode ser Nulo.
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);
	IPropertyStore* vi_pPropertyStore = Nulo; //Pode ser Nulo.
	IUnknown* vi_pOutObjectCancel = Nulo; //Pode ser IGNORADO.
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjectState = Nulo; //Pode ser Nulo.

	//Converte a string contendo a url para o arquivo a ser criado.
	vi_pUrl = Util.ConverterStringToConstWCHAR(Param_Url);

	//Recupera o ponteiro para a interface de callback.
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Verifica se forneceu a interface de propriedades e recupera o seu ponteiro.
	if (ObjetoGerenciadoValido(Param_Propriedades))
		CarenGetPointerFromICarenSafe(Param_Propriedades, vi_pPropertyStore);

	//Verifica se forneceu o objeto de estado devolvido na conclusão da operação assincrona.
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjectState);

	//Chama o método para executar a operação
	Hr = PonteiroTrabalho->BeginCreateObjectFromURL(
		vi_pUrl,
		vi_Flags,
		vi_pPropertyStore,
		Param_Out_ObjetoCancel.IgnoreParameter? Nulo: &vi_pOutObjectCancel,
		vi_pCallback,
		vi_pObjectState
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

	//Verifica se o método retornou uma interface de cancelamento e define no parametro.
	if (ObjetoValido(vi_pOutObjectCancel))
		CarenSetPointerToICarenSafe(vi_pOutObjectCancel, Param_Out_ObjetoCancel.ObjetoParametro, true);

Done:;
	//Libera a memória para a string se ela for valida
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (CancelObjectCreation) - Cancela uma solicitação assíncrona para criar um objeto.
/// </summary>
/// <param name="Param_ObjetoCancel">Ponteiro para a interface ICaren que foi retornada no parâmetro Param_ObjetoCancel do método ICarenMFSourceResolver::BeginCreateObjectFromByteStream 
/// ou ICarenMFSourceResolver::BeginCreateObjectFromURL. </param>
CarenResult CarenMFSourceResolver::CancelObjectCreation(ICaren^ Param_ObjetoCancel)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IUnknown* vi_pObjectCancel = Nulo;

	//Recupera o ponteiro para o objeto de cancelamento da operação.
	CarenGetPointerFromICarenSafe(Param_ObjetoCancel, vi_pObjectCancel);

	//Chama o método para cancelar a operação
	Hr = PonteiroTrabalho->CancelObjectCreation(vi_pObjectCancel);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (CreateObjectFromByteStream) - Cria uma fonte de mídia de um fluxo de bytes. Este método é síncrono.
/// </summary>
/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceResolver::CreateObjectFromByteStream
(
	ICarenMFByteStream^ Param_FluxoBytes,
	String^ Param_Url,
	Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
	ICarenPropertyStore^ Param_Propriedades,
	[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
	ICaren^ Param_Out_FonteMidia
)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	LPCWSTR vi_pUrl = Nulo; //Pode ser Nulo.
	DWORD vi_Flags  = static_cast<DWORD>(Param_Flags);
	IPropertyStore* vi_pPropertyStore = Nulo; //Pode ser Nulo.
	MF_OBJECT_TYPE vi_OutTipoObjeto = MF_OBJECT_TYPE::MF_OBJECT_INVALID;
	IUnknown* vi_pOutSource = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_FluxoBytes, vi_pByteStream);
	
	//Verifica se forneceu a URL e converte a string.
	if (StringObjetoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToConstWCHAR(Param_Url);

	//Verifica se forneceu a interface de propriedades e recupera o seu ponteiro.
	if (ObjetoGerenciadoValido(Param_Propriedades))
		CarenGetPointerFromICarenSafe(Param_Propriedades, vi_pPropertyStore);

	//Chama o método para executar a operação
	Hr = PonteiroTrabalho->CreateObjectFromByteStream(
		vi_pByteStream,
		vi_pUrl,
		vi_Flags,
		vi_pPropertyStore,
		&vi_OutTipoObjeto,
		&vi_pOutSource
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

	//Define o tipo do objeto criado no parametro de saida.
	Param_Out_TipoObjeto = static_cast<CA_MF_OBJECT_TYPE>(vi_OutTipoObjeto);

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutSource, Param_Out_FonteMidia, true);

Done:;
	//Libera a memória utilizada pela string se válida.
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (CreateObjectFromURL) - Cria uma fonte de mídia ou um fluxo de bytes de um URL. Este método é síncrono.
/// </summary>
/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
/// <param name="Param_Flags">OR bit a bit de um ou mais bandeiras.</param>
/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceResolver::CreateObjectFromURL
(
	String^ Param_Url,
	Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
	ICarenPropertyStore^ Param_Propriedades,
	[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
	ICaren^ Param_Out_FonteMidia
)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	LPCWSTR vi_pUrl = Nulo;
	DWORD vi_Flags = static_cast<DWORD>(Param_Flags);
	IPropertyStore* vi_pPropertyStore = Nulo; //Pode ser Nulo.
	MF_OBJECT_TYPE vi_OutTipoObjeto = MF_OBJECT_TYPE::MF_OBJECT_INVALID;
	IUnknown* vi_pOutObject = Nulo;

	//Converte a string contendo a url para o arquivo.
	vi_pUrl = Util.ConverterStringToConstWCHAR(Param_Url);

	//Verifica se forneceu a interface de propriedades e recupera o seu ponteiro.
	if (ObjetoGerenciadoValido(Param_Propriedades))
		CarenGetPointerFromICarenSafe(Param_Propriedades, vi_pPropertyStore);

	//Chama o método para executar a operação
	Hr = PonteiroTrabalho->CreateObjectFromURL(
		vi_pUrl,
		vi_Flags,
		vi_pPropertyStore,
		&vi_OutTipoObjeto,
		&vi_pOutObject
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
	
	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_FonteMidia, true);

Done:;
	//Libera a memória utilizada pela string se válida.
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (EndCreateObjectFromByteStream) - Conclui uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceResolver::EndCreateObjectFromByteStream
(
	ICarenMFAsyncResult^ Param_Resultado,
	[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
	ICaren^ Param_Out_FonteMidia
)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFAsyncResult* vi_pAsyncResult = Nulo;
	MF_OBJECT_TYPE vi_OutTipoObjeto = MF_OBJECT_TYPE::MF_OBJECT_INVALID;
	IUnknown* vi_pOutObject = Nulo;

	//Recupera o ponteiro para a interface de resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pAsyncResult);

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->EndCreateObjectFromByteStream(
		vi_pAsyncResult, 
		&vi_OutTipoObjeto,
		&vi_pOutObject);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_FonteMidia, true);

	//Define o tipo do objeto criado no parmetro de saida.
	Param_Out_TipoObjeto = static_cast<CA_MF_OBJECT_TYPE>(vi_OutTipoObjeto);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (EndCreateObjectFromURL) - Conclui uma solicitação assíncrona para criar um objeto a partir de um URL.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_MF_OBJECT_TYPE, especificando o tipo de objeto que foi criado.</param>
/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFSourceResolver::EndCreateObjectFromURL
(
	ICarenMFAsyncResult^ Param_Resultado,
	[Out] Enumeracoes::CA_MF_OBJECT_TYPE% Param_Out_TipoObjeto,
	ICaren^ Param_Out_FonteMidia
) 
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	IMFAsyncResult* vi_pAsyncResult = Nulo;
	MF_OBJECT_TYPE vi_OutTipoObjeto = MF_OBJECT_TYPE::MF_OBJECT_INVALID;
	IUnknown* vi_pOutObject = Nulo;

	//Recupera o ponteiro para a interface de resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pAsyncResult);

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->EndCreateObjectFromByteStream(
		vi_pAsyncResult,
		&vi_OutTipoObjeto,
		&vi_pOutObject);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_FonteMidia, true);

	//Define o tipo do objeto criado no parmetro de saida.
	Param_Out_TipoObjeto = static_cast<CA_MF_OBJECT_TYPE>(vi_OutTipoObjeto);

Done:;
	//Retorna o resultado
	return Resultado;
}