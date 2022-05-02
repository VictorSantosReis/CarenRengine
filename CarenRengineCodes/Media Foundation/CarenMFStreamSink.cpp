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
#include "CarenMFStreamSink.h"


//Destruidor.
CarenMFStreamSink::~CarenMFStreamSink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFStreamSink::CarenMFStreamSink()
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
CarenResult CarenMFStreamSink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFStreamSink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFStreamSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFStreamSink**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFStreamSink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFStreamSink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFStreamSink**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFStreamSink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFStreamSink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFStreamSink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFStreamSink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFStreamSink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFStreamSink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFStreamSink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFStreamSink();
}





// Métodos da interface proprietaria (ICarenMFStreamSink)


/// <summary>
/// Recupera o (Coletor de Mídia) que possui esse (Coletor de Fluxo).
/// </summary>
/// <param name="Param_Out_MidiaSink">Recebe a interface(ICarenMFMediaSink) do (Coletor de Mídia) responsável por esse (Coletor de Fluxo). O usuário deve criar a interface antes de chamar o método.</param>
CarenResult CarenMFStreamSink::GetMediaSink(ICaren^ Param_Out_MidiaSink)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::SS_OK, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas pelo método
	IMFMediaSink* vi_pOutMediaSink = NULL;
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMediaSink(&vi_pOutMediaSink);

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
	CarenSetPointerToICarenSafe(vi_pOutMediaSink, Param_Out_MidiaSink, true);
	
Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Fornece uma amostra para o fluxo. O coletor de mídia processa o exemplo.
/// Esse método pode retornar (ER_MF_AMOSTRA_TIME_SPAN_INVALIDO) por vários motivos, dependendo da implementação do coletor de mídia:
/// 1 > Carimbos de hora negativos.
/// 2 > Carimbos de tempo que saltam para trás (dentro do mesmo fluxo).
/// 3 > Os carimbos de hora de um fluxo se afastaram muito dos registros de tempo em outro fluxo no mesmo coletor de mídia 
/// (por exemplo, um coletor de arquivamento que multiplexa os fluxos).
/// </summary>
/// <param name="Param_AmostraMidia">A amostra de mídia a ser processada.</param>
CarenResult CarenMFStreamSink::ProcessSample(ICarenMFSample^ Param_AmostraMidia)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas pelo método
	IMFSample *vi_pSample = Nulo;

	//Recupera o ponteiro para a amostra de mídia
	CarenGetPointerFromICarenSafe(Param_AmostraMidia, vi_pSample);

	//Chama o método para processar a amostra
	Hr = PonteiroTrabalho->ProcessSample(vi_pSample);

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
/// Recupera o identificador de fluxo para este coletor de fluxo.
/// </summary>
/// <param name="Param_Out_IdentificadorFluxo">Retorna o identificador deste fluxo.</param>
CarenResult CarenMFStreamSink::GetIdentifier([Out] UInt32% Param_Out_IdentificadorFluxo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	DWORD vi_OutIdentficadorFluxo = 0;

	//Chama o método para recuperar o identificador deste fluxo.
	Hr = PonteiroTrabalho->GetIdentifier(&vi_OutIdentficadorFluxo);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o resultado.
	Param_Out_IdentificadorFluxo = safe_cast<UInt32>(vi_OutIdentficadorFluxo);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o manipulador de tipo de mídia para o coletor de fluxo. 
/// Você pode usar o manipulador de tipo de mídia para localizar quais
/// formatos o fluxo oferece suporte e para definir o tipo de mídia no fluxo.
/// </summary>
/// <param name="Param_Out_MidiaHandle">Recebe a interface que possui o (Manipulador de Mídia).</param>
CarenResult CarenMFStreamSink::GetMediaTypeHandler([Out] ICarenMFMediaTypeHandler^% Param_Out_MidiaHandle)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaTypeHandler *vi_pOutMediaTypeHandler = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMediaTypeHandler(&vi_pOutMediaTypeHandler);

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
	Param_Out_MidiaHandle = gcnew CarenMFMediaTypeHandler(false);
	
	//Define o ponteiro na interface a ser retornada.
	CarenSetPointerToICarenSafe(vi_pOutMediaTypeHandler, Param_Out_MidiaHandle, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Coloca um marcador no fluxo.
/// O método placemarker coloca um marcador no fluxo entre amostras. O CA_MFSTREAMSINK_MARKER_TYPE enumeração define o 
/// tipo de marcador e o tipo de informações associadas com o marcador.
/// </summary>
/// <param name="Param_Marcador">Especifica o tipo de marcador, como um membro da enumeração: CA_MFSTREAMSINK_MARKER_TYPE</param>
/// <param name="Param_ValorAdicional">Um valor que contém informações adicionais relacionadas ao marcador. Esse parâmetro pode ser (NULO).</param>
/// <param name="Param_DadosAnexoEvento">Valor que é anexado junto ao evento(MEStreamSinkMarker). Chame o método (GetValue) na interface 
/// de evento para obter esse valor. Esse parâmetro pode ser (NULO).</param>
CarenResult CarenMFStreamSink::PlaceMarker(Enumeracoes::CA_MFSTREAMSINK_MARKER_TYPE Param_Marcador, Estruturas::CA_PROPVARIANT^ Param_ValorAdicional, Estruturas::CA_PROPVARIANT^ Param_DadosAnexoEvento)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variveis utilizadas no método
	MFSTREAMSINK_MARKER_TYPE vi_MarkerType = static_cast<MFSTREAMSINK_MARKER_TYPE>(Param_Marcador);
	LPPROPVARIANT vi_pValueAdicional = Nulo; //Pode ser Nulo.
	LPPROPVARIANT vi_pDadosEvento = Nulo; //Pode ser Nulo.

	//Converte a PROPVARIANT gerenciada para nativa com os dados do valor adicional se fornecido.
	if (ObjetoGerenciadoValido(Param_ValorAdicional))
		CarenConvertPropvariantToNativeSafe(Param_ValorAdicional, vi_pValueAdicional);

	//Converte a PROPVARIANT gerenciada para nativa com os dados do de anexo do evento se fornecido.
	if (ObjetoGerenciadoValido(Param_DadosAnexoEvento))
		CarenConvertPropvariantToNativeSafe(Param_DadosAnexoEvento, vi_pDadosEvento);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->PlaceMarker(
		vi_MarkerType,
		ObjetoValido(vi_pValueAdicional)? const_cast<LPPROPVARIANT>(vi_pValueAdicional) : Nulo,
		ObjetoValido(vi_pDadosEvento) ? const_cast<LPPROPVARIANT>(vi_pDadosEvento) : Nulo
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

Done:;
	//Limpa as PropVariants
	DeletarPropVariantSafe(&vi_pValueAdicional);
	DeletarPropVariantSafe(&vi_pDadosEvento);

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Faz com que o coletor de fluxo para descartar todas as amostras que ele 
/// recebeu e ainda não processado.
/// </summary>
CarenResult CarenMFStreamSink::Flush()
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação
	Hr = PonteiroTrabalho->Flush();

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





// Métodos da interface proprietaria (ICarenMFMediaEventGenerator)


/// <summary>
/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
/// dependerá do valor de Param_Flags.
/// </summary>
/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFStreamSink::GetEvent(CA_MF_GET_FLAGS_EVENT Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFMediaEvent* vi_pOutMediaEvent = NULL;

	//Chama o método para obter o evento.
	Hr = PonteiroTrabalho->GetEvent(static_cast<DWORD>(Param_Flags), &vi_pOutMediaEvent);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada no parametro de saida.
	Param_Out_MidiaEvent = gcnew CarenMFMediaEvent();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaEvent, Param_Out_MidiaEvent, true);

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
/// </summary>
/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
CarenResult CarenMFStreamSink::BeginGetEvent(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncCallback* vi_pCallback = NULL;
	IUnknown* vi_pDadosObjeto = NULL; //Pode ser Nulo.

	//Recupera o ponteiro para a interface de Callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Verifica se forneceu uma interface de dados e recupera o ponteiro
	if (ObjetoGerenciadoValido(Param_ObjetoDesconhecido))
		CarenGetPointerFromICarenSafe(Param_ObjetoDesconhecido, vi_pDadosObjeto);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginGetEvent(vi_pCallback, vi_pDadosObjeto);

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
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
/// </summary>
/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFStreamSink::EndGetEvent(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncResult* vi_pResultAsync = Nulo;
	IMFMediaEvent* vi_pOutMediaEvent = Nulo;

	//Recupera o ponteiro para a interface de resultado assincrono.
	CarenGetPointerFromICarenSafe(Param_ResultAsync, vi_pResultAsync);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndGetEvent(vi_pResultAsync, &vi_pOutMediaEvent);

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
	Param_Out_MidiaEvent = gcnew CarenMFMediaEvent();

	//Define o ponteiro na interface a ser retornada.
	CarenSetPointerToICarenSafe(vi_pOutMediaEvent, Param_Out_MidiaEvent, true);

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (QueueEvent) - Coloca um novo evento na fila do objeto.
/// </summary>
/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.GetType).</param>
/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.GetExtendedType) do evento.</param>
/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetStatus) do evento.</param>
/// <param name="Param_Dados">uma CA_PROPVARIANT que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.GetValue) do evento.</param>
CarenResult CarenMFStreamSink::QueueEvent(
	Enumeracoes::CA_MediaEventType Param_TipoEvento,
	String^ Param_GuidExtendedType,
	Int32 Param_HResultCode,
	Estruturas::CA_PROPVARIANT^ Param_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MediaEventType vi_TypeEvent = static_cast<MediaEventType>(Param_TipoEvento);
	GUID vi_GuidExtendEvent = GUID_NULL; //Pode ser NULO.
	HRESULT vi_Hresult = static_cast<HRESULT>(Param_HResultCode);
	PROPVARIANT* vi_Propvar = Nulo; //Pode ser NULO.

	 //Converte a string para o GUID se fornecido.
	if (StringObjetoValido(Param_GuidExtendedType))
	{
		//Cria o GUID.
		CarenCreateGuidFromStringSafe(Param_GuidExtendedType, vi_GuidExtendEvent);
	}

	//Verifica se forneceu uma estrutura PROPVARIANT com o valor do evento.
	if (ObjetoGerenciadoValido(Param_Dados))
		CarenConvertPropvariantToNativeSafe(Param_Dados, vi_Propvar); //Converte CA_PROPVARIANT

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueueEvent(
		vi_TypeEvent,
		vi_GuidExtendEvent,
		vi_Hresult,
		ObjetoValido(vi_Propvar) ? const_cast<PROPVARIANT*>(vi_Propvar) : Nulo
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

Done:;
	//Libera a memória utilizada pela propvariant.
	DeletarPropVariantSafe(&vi_Propvar);

	//Retorna o resultado da operação.
	return Resultado;
}