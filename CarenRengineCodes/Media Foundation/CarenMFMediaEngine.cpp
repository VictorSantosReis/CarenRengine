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
#include "CarenMFMediaEngine.h"

//Destruidor.
CarenMFMediaEngine::~CarenMFMediaEngine()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngine::CarenMFMediaEngine()
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
CarenResult CarenMFMediaEngine::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFMediaEngine::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngine*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFMediaEngine::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFMediaEngine*>(Param_PonteiroNativo);

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
CarenResult CarenMFMediaEngine::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngine::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFMediaEngine::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFMediaEngine::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaEngine::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngine::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngine::LiberarReferencia()
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
void CarenMFMediaEngine::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngine();
}



// Métodos da interface proprietária(ICarenMFMediaEngine)


/// <summary>
/// Pergunta o quão provável é que o Media Engine possa reproduzir um tipo especificado de recurso de mídia.
/// </summary>
/// <param name="Param_TipoMime">Uma string que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
/// <param name="Param_Out_CanPlay">Recebe um valor de enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
CarenResult CarenMFMediaEngine::CanPlayType(
String^ Param_TipoMime,
[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_CanPlay)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pMimeType = Nulo;
	MF_MEDIA_ENGINE_CANPLAY vi_OutCanPlay = MF_MEDIA_ENGINE_CANPLAY::MF_MEDIA_ENGINE_CANPLAY_NOT_SUPPORTED;

	//Converte a string gerenciada para a nativa.
	vi_pMimeType = Util.ConverterStringToBSTR(Param_TipoMime);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CanPlayType(vi_pMimeType, &vi_OutCanPlay);

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

	//Converte e define o resultado no parametro de saida.
	Param_Out_CanPlay = static_cast<CA_MF_MEDIA_ENGINE_CANPLAY>(vi_OutCanPlay);

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringBSTRSafe(&vi_pMimeType);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
///Pergunta se o Media Engine inicia automaticamente a reprodução.
/// </summary>
/// <param name="Param_Out_AutoPlay">Recebe um valor booleano que indica se a reprodução é iniciada automaticamente.</param>
void CarenMFMediaEngine::GetAutoPlay([Out] Boolean% Param_Out_AutoPlay)
{
	//Chama o método para realizar a operação.
	Param_Out_AutoPlay = static_cast<Boolean>(PonteiroTrabalho->GetAutoPlay());
}

/// <summary>
/// Consulta quantos dados de recursos o mecanismo de mídia bufferou.
/// </summary>
/// <param name="Param_Out_Buffered">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngine::GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaTimeRange* vi_pOutTimeRange = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBuffered(&vi_pOutTimeRange);

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
	Param_Out_Buffered = gcnew CarenMFMediaTimeRange();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutTimeRange, Param_Out_Buffered, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a URL do recurso de mídia atual ou uma sequência vazia se nenhum recurso de mídia estiver presente.
/// </summary>
/// <param name="Param_Out_Url">Recebe uma String que contém a URL do recurso de mídia atual. Se não houver recurso de mídia, Param_Out_Url recebe uma String vazia.</param>
CarenResult CarenMFMediaEngine::GetCurrentSource([Out] String^% Param_Out_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BSTR vi_pOutpUrl = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentSource(&vi_pOutpUrl);

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

	//Cria a string que será retornada com a url.
	Param_Out_Url = gcnew String(vi_pOutpUrl);

Done:;
	//Libera a memória para a string.
	DeletarStringBSTRSafe(&vi_pOutpUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a posição de reprodução atual.
/// </summary>
/// <param name="Param_Out_PosicaoAtual">Obtém o valor da posição atual da reprodução.</param>
void CarenMFMediaEngine::GetCurrentTime([Out] double% Param_Out_PosicaoAtual)
{
	//Chama o método para realizar a operação.
	Param_Out_PosicaoAtual = PonteiroTrabalho->GetCurrentTime();
}

/// <summary>
/// Obtém a taxa de reprodução padrão.
/// </summary>
/// <param name="Param_Out_DefaultRate">Obtém o valor que indica a taxa de reprodução padrão.</param>
void CarenMFMediaEngine::GetDefaultPlaybackRate([Out] double% Param_Out_DefaultRate)
{
	//Chama o método para realizar a operação.
	Param_Out_DefaultRate = PonteiroTrabalho->GetDefaultPlaybackRate();
}

/// <summary>
/// Obtém a duração do recurso de mídia.
/// </summary>
/// <param name="Param_Out_Duracao">Recupera o valor da duração do recurso de mídia.</param>
void CarenMFMediaEngine::GetDuration([Out] double% Param_Out_Duracao)
{
	//Chama o método para realizar a operação.
	Param_Out_Duracao = PonteiroTrabalho->GetDuration();
}

/// <summary>
/// Obtém o status de erro mais recente.
/// </summary>
/// <param name="Param_Out_Error">Recebe um ponteiro para a interface ICarenMFMediaError ou para o valor NULO. Se o valor não for NULO, o chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngine::GetError([Out] ICarenMFMediaError^% Param_Out_Error)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaError* vi_pOutMediaError = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetError(&vi_pOutMediaError);

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
	Param_Out_Error = gcnew CarenMFMediaError();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutMediaError, Param_Out_Error, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pergunta se o Media Engine fará a reprodução em loop.
/// </summary>
/// <param name="Param_Out_Loop">Obtém o valor booleano que indica o status da reprodução em loop.</param>
void CarenMFMediaEngine::GetLoop([Out] Boolean% Param_Out_Loop)
{
	//Chama o método para realizar a operação.
	Param_Out_Loop = static_cast<Boolean>(PonteiroTrabalho->GetLoop());
}

/// <summary>
/// Pergunta se o áudio está silenciado.
/// </summary>
/// <param name="Param_Out_Muted">Obtém um valor booleano que indica se o áudio está silenciado.</param>
void CarenMFMediaEngine::GetMuted([Out] Boolean% Param_Out_Muted)
{
	//Chama o método para realizar a operação.
	Param_Out_Muted = static_cast<Boolean>(PonteiroTrabalho->GetMuted());
}

/// <summary>
/// Obtém o tamanho do quadro de vídeo, ajustado para proporção.
/// </summary>
/// <param name="Param_Out_X">Retorna a Largura(X) do vídeo.</param>
/// <param name="Param_Out_Y">Retorna a Altura(Y) do vídeo.</param>
CarenResult CarenMFMediaEngine::GetNativeVideoSize(
[Out] UInt32% Param_Out_X, 
[Out] UInt32% Param_Out_Y)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutX, vi_OutY = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNativeVideoSize(&vi_OutX, &vi_OutY);

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

	//Converte e define nos parametros de saida.
	Param_Out_X = static_cast<DWORD>(vi_OutX);
	Param_Out_Y = static_cast<DWORD>(vi_OutY);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o estado atual da rede do mecanismo de mídia.
/// </summary>
/// <param name="Param_Out_StateNetwork">Retornar um valor da enumeração CA_MF_MEDIA_ENGINE_NETWORK que indica o status da rede.</param>
void CarenMFMediaEngine::GetNetworkState([Out] CA_MF_MEDIA_ENGINE_NETWORK% Param_Out_StateNetwork)
{
	//Chama o método para realizar a operação.
	Param_Out_StateNetwork = static_cast<CA_MF_MEDIA_ENGINE_NETWORK>(PonteiroTrabalho->GetNetworkState());
}

/// <summary>
/// Obtém a taxa de reprodução atual.
/// </summary>
/// <param name="Param_Out_PlaybackRate">Obtém um valor que indica a taxa de reprodução atual.</param>
void CarenMFMediaEngine::GetPlaybackRate([Out] double% Param_Out_PlaybackRate)
{
	//Chama o método para realizar a operação.
	Param_Out_PlaybackRate = PonteiroTrabalho->GetPlaybackRate();
}

/// <summary>
/// Obtém os intervalos de tempo que foram prestados.
/// </summary>
/// <param name="Param_Out_Played">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngine::GetPlayed([Out] ICarenMFMediaTimeRange^% Param_Out_Played)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaTimeRange* vi_pOutTimeRange = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPlayed(&vi_pOutTimeRange);

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
	Param_Out_Played = gcnew CarenMFMediaTimeRange();

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutTimeRange, Param_Out_Played, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe a bandeira de pré-carga.
/// </summary>
/// <param name="Param_Out_Preload">Recebe um valor da enumeração CA_MF_MEDIA_ENGINE_PRELOAD.</param>
void CarenMFMediaEngine::GetPreload([Out] CA_MF_MEDIA_ENGINE_PRELOAD% Param_Out_Preload)
{
	//Variaveis a serem utilizadas.
	MF_MEDIA_ENGINE_PRELOAD vi_OutPreLoad = MF_MEDIA_ENGINE_PRELOAD::MF_MEDIA_ENGINE_PRELOAD_NONE;

	//Chama o método para realizar a operação.
	vi_OutPreLoad = PonteiroTrabalho->GetPreload();

	//Converte e define no parametro de saida.
	Param_Out_Preload = static_cast<CA_MF_MEDIA_ENGINE_PRELOAD>(vi_OutPreLoad);
}

/// <summary>
/// Obtém o estado pronto, o que indica se o recurso de mídia atual pode ser renderizado.
/// </summary>
/// <param name="Param_Out_RadyState">Obtém uma ou mais bandeiras da enumeração CA_MF_MEDIA_ENGINE_READY que indica se o recurso pode ser renderizado.</param>
void CarenMFMediaEngine::GetReadyState([Out] CA_MF_MEDIA_ENGINE_READY% Param_Out_RadyState)
{
	//Chama o método para realizar a operação.
	Param_Out_RadyState = static_cast<CA_MF_MEDIA_ENGINE_READY>(PonteiroTrabalho->GetReadyState());
}

/// <summary>
/// Obtém os intervalos de tempo aos quais o Media Engine pode procurar atualmente.
/// </summary>
/// <param name="Param_Out_Seekable">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngine::GetSeekable([Out] ICarenMFMediaTimeRange^% Param_Out_Seekable)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaTimeRange* vi_pOutRimeRange = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSeekable(&vi_pOutRimeRange);

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
	Param_Out_Seekable = gcnew CarenMFMediaTimeRange();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutRimeRange, Param_Out_Seekable, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a posição inicial de reprodução.
/// </summary>
/// <param name="Param_Out_PosicaoInicial">Obtém um valor que indica a posição inicial de reprodução.</param>
void CarenMFMediaEngine::GetStartTime([Out] double% Param_Out_PosicaoInicial)
{
	//Chama o método para realizar a operação.
	Param_Out_PosicaoInicial = PonteiroTrabalho->GetStartTime();
}

/// <summary>
/// Obtém a proporção de imagem do fluxo de vídeo.
/// </summary>
/// <param name="Param_Out_X">Retonar o valor (X) do Aspect Ratio do fluxo do vídeo.</param>
/// <param name="Param_Out_Y">Retonar o valor (Y) do Aspect Ratio do fluxo do vídeo.</param>
CarenResult CarenMFMediaEngine::GetVideoAspectRatio(
[Out] UInt32% Param_Out_X,
[Out] UInt32% Param_Out_Y)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutX, vi_OutY = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVideoAspectRatio(&vi_OutX, &vi_OutY);

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

	//Converte e define nos parametros de saida.
	Param_Out_X = static_cast<DWORD>(vi_OutX);
	Param_Out_Y = static_cast<DWORD>(vi_OutY);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o nível de volume de áudio.
/// </summary>
/// <param name="Param_Out_Volume">Obtém um valor que indica o nível de volume do áudio.</param>
void CarenMFMediaEngine::GetVolume([Out] double% Param_Out_Volume)
{
	//Chama o método para realizar a operação.
	Param_Out_Volume = PonteiroTrabalho->GetVolume();
}

/// <summary>
/// Pergunta se o recurso de mídia atual contém um fluxo de áudio.
/// </summary>
/// <param name="Param_Out_AudioPresente">Retornar um booleano TRUE se um fluxo de áudio estiver disponível na mídia. Caso contrario, FALSE.</param>
void CarenMFMediaEngine::HasAudio([Out] Boolean% Param_Out_AudioPresente)
{
	//Chama o método para realizar a operação.
	Param_Out_AudioPresente = static_cast<Boolean>(PonteiroTrabalho->HasAudio());
}

/// <summary>
/// Pergunta se o recurso de mídia atual contém um fluxo de vídeo.
/// </summary>
/// <param name="Param_Out_VideoPresente">Retornar um booleano TRUE se um fluxo de vídeo estiver disponível na mídia. Caso contrario, FALSE.</param>
void CarenMFMediaEngine::HasVideo([Out] Boolean% Param_Out_VideoPresente)
{
	//Chama o método para realizar a operação.
	Param_Out_VideoPresente = static_cast<Boolean>(PonteiroTrabalho->HasVideo());
}

/// <summary>
/// Verifica se a reprodução terminou.
/// </summary>
/// <param name="Param_Out_ReproducaoTerminada">Retornar um booleano TRUE se a reprodução tiver terminado. Caso contrario, FALSE.</param>
void CarenMFMediaEngine::IsEnded([Out] Boolean% Param_Out_ReproducaoTerminada)
{
	//Chama o método para realizar a operação.
	Param_Out_ReproducaoTerminada = static_cast<Boolean>(PonteiroTrabalho->IsEnded());
}

/// <summary>
/// Verifica se a reprodução está pausada no momento.
/// </summary>
/// <param name="Param_Out_PauseStatus">Retorna um valor booleano indicando se a reprodução está pausada.</param>
void CarenMFMediaEngine::IsPaused([Out] Boolean% Param_Out_PauseStatus)
{
	//Chama o método para realizar a operação.
	Param_Out_PauseStatus = static_cast<Boolean>(PonteiroTrabalho->IsPaused());
}

/// <summary>
/// Verifica se o Media Engine está atualmente buscando uma nova posição de reprodução.
/// </summary>
/// <param name="Param_Out_BuscandoPosicao">Retornar um valor booleano que indica se a Media Engine está buscando uma nova posição.</param>
void CarenMFMediaEngine::IsSeeking([Out] Boolean% Param_Out_BuscandoPosicao)
{
	//Chama o método para realizar a operação.
	Param_Out_BuscandoPosicao = static_cast<Boolean>(PonteiroTrabalho->IsSeeking());
}

/// <summary>
/// Carrega a fonte de mídia atual.
/// </summary>
CarenResult CarenMFMediaEngine::Load()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Load();

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

/// <summary>
/// Consulta o Media Engine para saber se um novo quadro de vídeo está pronto.
/// </summary>
/// <param name="Param_Out_TempoApresentacaoFrame">Retornar um valor valido e maior que 0 para o tempo de apresentação do frame se ele estiver pronto para renderização.</param>
CarenResult CarenMFMediaEngine::OnVideoStreamTick([Out] Int64% Param_Out_TempoApresentacaoFrame)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LONGLONG vi_OutFramePresentationTime = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OnVideoStreamTick(&vi_OutFramePresentationTime);

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

	//Define o valor no parametro de saida.
	Param_Out_TempoApresentacaoFrame = vi_OutFramePresentationTime;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pausa a reprodução.
/// </summary>
CarenResult CarenMFMediaEngine::Pause()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Pause();

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

/// <summary>
/// Começa a reprodução.
/// </summary>
CarenResult CarenMFMediaEngine::Play()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Play();

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

/// <summary>
/// Especifica se o Media Engine inicia automaticamente a reprodução.
/// </summary>
/// <param name="Param_AutoPlay">Um valor booleano que indica se vai reproduzir automaticamente.</param>
CarenResult CarenMFMediaEngine::SetAutoPlay(Boolean Param_AutoPlay)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAutoPlay(Param_AutoPlay ? TRUE : FALSE);

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

/// <summary>
/// Busca uma nova posição de reprodução.
/// </summary>
/// <param name="Param_NovaPosicao">A novao posição a ser buscada.</param>
CarenResult CarenMFMediaEngine::SetCurrentTime(double Param_NovaPosicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentTime(Param_NovaPosicao);

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

/// <summary>
/// Define a taxa de reprodução padrão.
/// </summary>
/// <param name="Param_TaxaReproducaoDefault">O novo valor para taxa de reprodução padrão.</param>
CarenResult CarenMFMediaEngine::SetDefaultPlaybackRate(double Param_TaxaReproducaoDefault)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDefaultPlaybackRate(Param_TaxaReproducaoDefault);

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

/// <summary>
/// Define o código de erro atual.
/// </summary>
/// <param name="Param_Error">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_ERR.</param>
CarenResult CarenMFMediaEngine::SetErrorCode(CA_MF_MEDIA_ENGINE_ERR Param_Error)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetErrorCode(static_cast<MF_MEDIA_ENGINE_ERR>(Param_Error));

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

/// <summary>
/// Especifica se o Media Engine faz loop de reprodução.
/// </summary>
/// <param name="Param_Loop">Um valor booleano que vai indicar o loop de reprodução.</param>
CarenResult CarenMFMediaEngine::SetLoop(Boolean Param_Loop)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetLoop(Param_Loop ? TRUE : FALSE);

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

/// <summary>
/// Silencia ou ativar o áudio.
/// </summary>
/// <param name="Param_Mudo">Um valor booleano que vai definir se vai ou não silenciar o áudio.</param>
CarenResult CarenMFMediaEngine::SetMuted(Boolean Param_Mudo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetMuted(Param_Mudo ? TRUE : FALSE);

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

/// <summary>
/// Define a taxa de reprodução atual.
/// </summary>
/// <param name="Param_TaxaReproducaoAtual">Um valor para a nova taxa de reprodução atual.</param>
CarenResult CarenMFMediaEngine::SetPlaybackRate(double Param_TaxaReproducaoAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPlaybackRate(Param_TaxaReproducaoAtual);

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

/// <summary>
/// Defina o sinalizador de pré-carga.
/// </summary>
/// <param name="Param_Preload">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_PRELOAD que define o Preload da midia.</param>
CarenResult CarenMFMediaEngine::SetPreload(CA_MF_MEDIA_ENGINE_PRELOAD Param_Preload)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPlaybackRate(static_cast<MF_MEDIA_ENGINE_PRELOAD>(Param_Preload));

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

/// <summary>
/// Define a URL de um recurso de mídia.
/// </summary>
/// <param name="Param_Url">Uma string conténdo a URL para o recurso de mídia.</param>
CarenResult CarenMFMediaEngine::SetSource(String^ Param_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BSTR vi_pUrl = Nulo;

	//Converte a string gerenciada para a nativa.
	vi_pUrl = Util.ConverterStringToBSTR(Param_Url);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSource(vi_pUrl);

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
	//Libera a memória para a string.
	DeletarStringBSTRSafe(&vi_pUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define uma lista de fontes de mídia.
/// </summary>
/// <param name="Param_ElementosMidia">Um ponteiro para a interface ICarenMFMediaEngineSrcElements. O chamador deve implementar esta interface.</param>
CarenResult CarenMFMediaEngine::SetSourceElements(ICarenMFMediaEngineSrcElements^ Param_ElementosMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaEngineSrcElements* vi_pEngineSrcElements = Nulo;

	//Recupera o ponteiro para a interface de elementos.
	CarenGetPointerFromICarenSafe(Param_ElementosMidia, vi_pEngineSrcElements);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSourceElements(vi_pEngineSrcElements);

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

/// <summary>
/// Define o nível de volume de áudio.
/// </summary>
/// <param name="Param_Volume">O novo valor para o nível de volume de áudio da mídia.</param>
CarenResult CarenMFMediaEngine::SetVolume(double Param_Volume)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetVolume(Param_Volume);

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

/// <summary>
/// (Shutdown) - Desliga o Media Engine e libera os recursos que está usando.
/// </summary>
CarenResult CarenMFMediaEngine::Shutdown()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Shutdown();

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

/// <summary>
/// Copia o quadro de vídeo atual para um DXGI ou WIC bitmap.
/// No modo frame-server, chame este método para colocar o quadro de vídeo em uma superfície DXGI ou WIC. O aplicativo pode chamar esse método a qualquer momento após o 
/// Media Engine carregar um recurso de vídeo. Normalmente, no entanto, o aplicativo chama O ICarenMFMediaEngine::OnVideoStreamTick primeiro, para determinar se um novo quadro 
/// está disponível. Se o OnVideoStreamTick retornar SS_OK, o aplicativo então chamará TransferirFrameVideo.
/// Para conteúdo protegido, ligue para o método ICarenMFMediaEngineProtectedContent::TransferVideoFrame em vez deste método.
/// </summary>
/// <param name="Param_SuperficeDestino">Um ponteiro para a interface da superfície de destino.</param>
/// <param name="Param_RetanguloOrigem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem</param>
/// <param name="Param_RetanguloDestino">Uma estrutura CA_RECT que especifica o retângulo de destino.</param>
/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
CarenResult CarenMFMediaEngine::TransferVideoFrame(
ICaren^ Param_SuperficeDestino, 
CA_MFVideoNormalizedRect^ Param_RetanguloOrigem,
CA_RECT^ Param_RetanguloDestino,
CA_MFARGB^ Param_CorBorda)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* vi_pSuperficeDestino = Nulo;
	MFVideoNormalizedRect* vi_pRectOrigem = Nulo;
	PRECT vi_pRectDestino = Nulo;
	MFARGB* vi_pCorBorda = Nulo;

	//Recupera o ponteiro para a interface de superfice de destino.
	CarenGetPointerFromICarenSafe(Param_SuperficeDestino, vi_pSuperficeDestino);

	//Converte as estruturas.
	vi_pRectOrigem = Util.ConverterMFVideoNormalizedRectManaged_ToUnamaged(Param_RetanguloOrigem);
	vi_pRectDestino = Util.ConverterRECTManagedToUnmanaged(Param_RetanguloDestino);
	vi_pCorBorda = Util.ConverterMFARGBManaged_ToUnamaged(Param_CorBorda);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TransferVideoFrame(vi_pSuperficeDestino, vi_pRectOrigem, vi_pRectDestino, vi_pCorBorda);

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
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&vi_pRectOrigem);
	DeletarEstruturaSafe(&vi_pRectDestino);
	DeletarEstruturaSafe(&vi_pCorBorda);

	//Retorna o resultado.
	return Resultado;
}