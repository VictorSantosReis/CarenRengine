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
#include "CarenMFMediaStream.h"

//Destruidor.
CarenMFMediaStream::~CarenMFMediaStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFMediaStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
		//A operação falhou.
		

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
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFMediaStream*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMFMediaStream*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFMediaStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
CarenResult CarenMFMediaStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

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
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaStream::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaStream::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenMFMediaStream::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFMediaStream();
}


//
//Métodos da interface Proprietaria
//

CarenResult CarenMFMediaStream::ObterFonteMidia(ICarenMFMediaSource^% Param_Out_FonteMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaSource* pFonte = NULL;
	ICarenMFMediaSource^ InterfaceFonte = nullptr;

	//Chama o método para obter a fonte de midia deste fluxo
	Hr = PonteiroTrabalho->GetMediaSource(&pFonte);

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

	//Cria a interface que vai conter o ponteiro
	InterfaceFonte = gcnew CarenMFMediaSource();

	//Define o ponteiro de trabalho
	InterfaceFonte->AdicionarPonteiro(pFonte);

	//Define a interface no parametro de saida.
	Param_Out_FonteMidia = InterfaceFonte;

Done:;
	//Retorna o resultado.
	return Resultado;
}

CarenResult CarenMFMediaStream::ObterDescritorFluxo(ICarenMFStreamDescriptor^% Param_Out_DescritorFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFStreamDescriptor* pStreamDesc = NULL;
	ICarenMFStreamDescriptor^ InterfaceSolicitada = nullptr;

	//Chama o método para recuperar o descritor de fluxo
	Hr = PonteiroTrabalho->GetStreamDescriptor(&pStreamDesc);

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

	//Cria a interface que vai conter o ponteiro
	InterfaceSolicitada = gcnew CarenMFStreamDescriptor();

	//Define o ponteiro de trabalho
	InterfaceSolicitada->AdicionarPonteiro(pStreamDesc);

	//Define a interface no parametro de saida.
	Param_Out_DescritorFluxo = InterfaceSolicitada;

Done:;
	//Retorna o resultado.
	return Resultado;
}

CarenResult CarenMFMediaStream::RequisitarAmostra(ICaren^ Param_Token)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* pToken = NULL;

	//Verifica se o Token foi fornecido
	if (Param_Token != nullptr)
	{
		//Obtém o Token
		Resultado = Param_Token->RecuperarPonteiro((LPVOID*)&pToken);

		//Verifica se não é invalido
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Interface não disponivel
			goto Done;
		}
	}

	//Chama o método para solicitar uma amostra.
	Hr = PonteiroTrabalho->RequestSample(pToken);

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

Done:;
	//Retorna o resultado.
	return Resultado;
}



//
//Métodos da interface ICarenMFGeradorEventosMidia
//

/// <summary>
/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
/// dependerá do valor de Param_Flags.
/// </summary>
/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaStream::ObterEvento(CA_FLAGS_OBTER_EVENTO Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	ICarenMFMediaEvent^ InterfaceSolictada = nullptr;
	IMFMediaEvent* pMediaEvent = NULL;

	//Chama o método para obter o evento.
	Hr = PonteiroTrabalho->GetEvent((UInt32)Param_Flags, &pMediaEvent);

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

	//Cria a interface que vai conter o evento
	InterfaceSolictada = gcnew CarenMFMediaEvent();

	//Chama o método para deifinir o ponteiro
	InterfaceSolictada->AdicionarPonteiro(pMediaEvent);

	//Define a interface criada no parametro de saida.
	Param_Out_MidiaEvent = InterfaceSolictada;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

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
CarenResult CarenMFMediaStream::SolicitarProximoEvento(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncCallback* pInterfaceCallback = NULL;
	IUnknown* pDadosObjeto = NULL;

	//Recupera o Callback
	Resultado = Param_Callback->RecuperarPonteiro((LPVOID*)& pInterfaceCallback);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Verifica se um objeto com dados foi especificado e obtém
	if (Param_ObjetoDesconhecido != nullptr)
	{
		//Obtém o objeto desconhecido.

		Resultado = Param_ObjetoDesconhecido->RecuperarPonteiro((LPVOID*)& pDadosObjeto);
	}

	//Verifica se não houve erro ao obter o objeto de dados.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para obter o proximo evento na fila.
	Hr = PonteiroTrabalho->BeginGetEvent(pInterfaceCallback, ObjetoValido(pDadosObjeto) ? pDadosObjeto : NULL);

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

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
/// </summary>
/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaStream::ConcluirSolicitaçãoEvento(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	IMFAsyncResult* pResultAsync = NULL;
	IMFMediaEvent* pMediaEvent = NULL;
	ICarenMFMediaEvent^ InterfaceMidiaEvent = nullptr;

	//Recupera o resultado assincrono.
	Resultado = Param_ResultAsync->RecuperarPonteiro((LPVOID*)& pResultAsync);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para concluir a operação assincrona e obter o Media Event com as informações
	//do evento concluido.
	Hr = PonteiroTrabalho->EndGetEvent(pResultAsync, &pMediaEvent);

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

	//Cria a interface que vai conter o evento
	InterfaceMidiaEvent = gcnew CarenMFMediaEvent();

	//Chama o método para deifinir o ponteiro
	InterfaceMidiaEvent->AdicionarPonteiro(pMediaEvent);

	//Define a interface criada no parametro de saida.
	Param_Out_MidiaEvent = InterfaceMidiaEvent;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado da operação.
	return Resultado;
}

/// <summary>
/// (QueueEvent) - Coloca um novo evento na fila do objeto.
/// </summary>
/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.ObterTipo).</param>
/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.ObterTipoExtendido) do evento.</param>
/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterStatus) do evento.</param>
/// <param name="Param_Dados">uma CA_PropVariant que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterValor) do evento.</param>
CarenResult CarenMFMediaStream::InserirEventoFila(Enumeracoes::CA_MediaEventType Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PropVariant^ Param_Dados) {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	Utilidades Util;
	
	MediaEventType MTypeEvento = static_cast<MediaEventType>(Param_TipoEvento);
	PROPVARIANT PropVar;
	bool PropVarConverted = false;
	GUID GuidExtendedType = GUID_NULL;
	HRESULT ValorResultEvento = Param_HResultCode;

	//Cria o Guid se ele for valido.
	if (!String::IsNullOrEmpty(Param_GuidExtendedType))
	{
		//Cria o Guid.
		GuidExtendedType = Util.CreateGuidFromString(Param_GuidExtendedType);
	}

	//Verifica se forneceu dados para o evento.
	if (Param_Dados != nullptr)
	{
		//Inicializa a PropVariant 
		PropVariantInit(&PropVar);

		//Converte os dados da propvariant gerenciada para a não gerenciada.
		PropVarConverted = Util.ConvertPropVariantManagedToUnamaged(Param_Dados, PropVar);

		//Verifica o resultado
		if (!PropVarConverted)
		{
			//A PropVariant não foi convertida com sucesso.
			//Sai do método
			goto Done;
		}
	}

	//Chama o método para adicionar o evento na lista
	Hr = PonteiroTrabalho->QueueEvent(MTypeEvento, GuidExtendedType != GUID_NULL ? GuidExtendedType : GUID_NULL, ValorResultEvento, Param_Dados != nullptr ? &PropVar : NULL);

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

Done:;
	//Libera a PropVariant
	PropVariantClear(&PropVar);

	//Limpa o guid
	GuidExtendedType = GUID_NULL;

	//Retorna o resultado da operação.
	return Resultado;
}