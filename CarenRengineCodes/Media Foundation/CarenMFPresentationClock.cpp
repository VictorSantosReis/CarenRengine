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
#include "CarenMFPresentationClock.h"


//Destruidor.
CarenMFPresentationClock::~CarenMFPresentationClock()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFPresentationClock::CarenMFPresentationClock(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFPresentationClock* vi_pOutPresentationClock = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreatePresentationClock(&vi_pOutPresentationClock);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutPresentationClock;
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
CarenResult CarenMFPresentationClock::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFPresentationClock::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFPresentationClock*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFPresentationClock::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFPresentationClock*>(Param_PonteiroNativo);

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
CarenResult CarenMFPresentationClock::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFPresentationClock::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFPresentationClock::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFPresentationClock::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFPresentationClock::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFPresentationClock::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFPresentationClock::LiberarReferencia()
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
void CarenMFPresentationClock::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFPresentationClock();
}





// Métodos da interface proprietaria ICarenMFPresentationClock


/// <summary>
/// Registra um objeto para ser notificado sempre que o relógio inicia, para, ou faz uma pausa ou muda a taxa.
/// </summary>
/// <param name="Param_InterfaceNotification">A interface que contém o objeto de notificação de eventos do Relógio.</param>
CarenResult CarenMFPresentationClock::AddClockStateSink(ICarenMFClockStateSink^ Param_InterfaceNotification)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFClockStateSink *vi_pClockStateSink = Nulo;

	//Obtém o ponteiro para a interface a ser adicionada.
	CarenGetPointerFromICarenSafe(Param_InterfaceNotification, vi_pClockStateSink);
	
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddClockStateSink(vi_pClockStateSink);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a hora mais recente.
/// </summary>
/// <param name="Param_Out_NsHoraRelogio">Recebe a hora do relógio atual em unidades de 100 nanosegundos.</param>
CarenResult CarenMFPresentationClock::GetTime([Out] Int64% Param_Out_NsHoraRelogio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	INT64 vi_OutTime = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTime(&vi_OutTime);

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
	Param_Out_NsHoraRelogio = vi_OutTime;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a fonte de tempo de apresentação do relógio.
/// </summary>
/// <param name="Param_Out_TimeSource">Recebe a interface que contém a Fonte de apreentação do relógio.</param>
CarenResult CarenMFPresentationClock::GetTimeSource([Out] ICarenMFPresentationTimeSource^% Param_Out_TimeSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFPresentationTimeSource *vi_pOutPresentationTime = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTimeSource(&vi_pOutPresentationTime);

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
	Param_Out_TimeSource = gcnew CarenMFPresentationTimeSource(false);

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutPresentationTime, Param_Out_TimeSource, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Pausa o tempo de apresentação. Enquanto o relógio está em pausa, o tempo do relógio não adianta,
/// e (GetTime) do relógio retorna o tempo em que o relógio foi pausado.
/// </summary>
CarenResult CarenMFPresentationClock::Pause()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Cancela o registro de um objeto que está recebendo notificações de alteração de estado do relógio.
/// </summary>
/// <param name="Param_InterfaceNotification">Cancela o registro de notificação do relógio presente na interface de eventos.</param>
CarenResult CarenMFPresentationClock::RemoveClockStateSink(ICarenMFClockStateSink^ Param_InterfaceNotification)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFClockStateSink *vi_pClockState = Nulo;

	//Recupera o ponteiro para a interface.
	CarenGetPointerFromICarenSafe(Param_InterfaceNotification, vi_pClockState);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveClockStateSink(vi_pClockState);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Define a fonte de tempo para o tempo de apresentação. A fonte de tempo é o objeto que 
/// impulsiona o relógio, fornecendo a hora atual.
/// </summary>
/// <param name="Param_TimeSource">Define o tempo na fonte de tempo do relógio de apresentação.</param>
CarenResult CarenMFPresentationClock::SetTimeSource(ICarenMFPresentationTimeSource^ Param_TimeSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFPresentationTimeSource *vi_pPresentationTimeSource = Nulo;

	//Recupera o ponteiro para a interface relogio de apresentação.
	CarenGetPointerFromICarenSafe(Param_TimeSource, vi_pPresentationTimeSource);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTimeSource(vi_pPresentationTimeSource);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Começa o tempo de apresentação.
/// </summary>
/// <param name="Param_PosiçãoInicio">A posição ou tempo de partida inicial do relógio. O valor deve ser expressados em 
/// unidades de 100 nanosegundos. Se (Param_PosiçãoAtual) for True, desconsidere esse valor.</param>
/// <param name="Param_PosiçãoAtual">Define se deve iniciar a parti da posição atual. O valor de (Param_PosiçãoInicio) é desconsiderado
/// se esse valor for True.</param>
CarenResult CarenMFPresentationClock::Start(Int64 Param_PosiçãoInicio, Boolean Param_PosiçãoAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Start(Param_PosiçãoAtual ? PRESENTATION_CURRENT_POSITION : Param_PosiçãoInicio);

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
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Para o relógio de apresentação. Enquanto o relógio estiver parado, não adianta a hora do relógio e 
/// (GetTime) método do relógio retorna zero.
/// </summary>
CarenResult CarenMFPresentationClock::Stop()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método que vai parar o relogio
	Hr = PonteiroTrabalho->Stop();

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
	//Retorna o resultado
	return Resultado;
}





// Métodos da interface (ICarenMFClock)


/// <summary>
/// Recupera as características do relógio.
/// </summary>
/// <param name="Param_Out_CaracteristicasClock">Recebe os flags com as características do relógio.</param>
CarenResult CarenMFPresentationClock::GetClockCharacteristics([Out] Enumeracoes::CA_MFCLOCK_CHARACTERISTICS_FLAGS% Param_Out_CaracteristicasClock)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutCharacteristicsClock = 0;

	//Chama o método para obter as caracteristicas
	Hr = PonteiroTrabalho->GetClockCharacteristics(&vi_OutCharacteristicsClock);

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

	//Define o valor no parametro de saida
	Param_Out_CaracteristicasClock = static_cast<CA_MFCLOCK_CHARACTERISTICS_FLAGS>(vi_OutCharacteristicsClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Não Suportado Nativamente) - Recupera a chave de continuidade do relógio.
/// </summary>
/// <param name="Param_Out_Chave">Recebe a chave de continuidade.</param>
CarenResult CarenMFPresentationClock::GetContinuityKey([Out] UInt32% Param_Out_Chave)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD vi_OutKeyClock = 0;

	//Chama o método para obter a chave de continuidade
	Hr = PonteiroTrabalho->GetContinuityKey(&vi_OutKeyClock);

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

	//Define o valor da chave no parametro de retorno.
	Param_Out_Chave = safe_cast<UInt32>(vi_OutKeyClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a hora do último relógio que foi correlacionada com a hora do sistema.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_ClockTime">Recebe o último tempo de relógio conhecido, em unidades de freqüência do relógio.</param>
/// <param name="Param_Out_NsSystemTime">Recebe a hora do sistema que corresponde ao tempo de relógio retornado em Param_Out_ClockTime, em unidades de 100 nanosegundos.</param>
CarenResult CarenMFPresentationClock::GetCorrelatedTime(UInt32 Param_ValorReservado, [Out] Int64% Param_Out_ClockTime, [Out] Int64% Param_Out_NsSystemTime)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	INT64 vi_OutClockTime = 0;
	INT64 vi_OutNsSystemTime = 0;

	//Chama o método para obter a hora correlacionada
	Hr = PonteiroTrabalho->GetCorrelatedTime(Param_ValorReservado, &vi_OutClockTime, &vi_OutNsSystemTime);

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

	//Define os parametros de saida
	Param_Out_ClockTime = vi_OutClockTime;
	Param_Out_NsSystemTime = vi_OutNsSystemTime;

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera as propriedades do relógio.
/// </summary>
/// <param name="Param_Out_PropriedadesRelogio">Retorna a estrutura que contém as propriedades do relógio atual.</param>
CarenResult CarenMFPresentationClock::GetProperties([Out] Estruturas::CA_MFCLOCK_PROPERTIES^% Param_Out_PropriedadesRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	MFCLOCK_PROPERTIES vi_OutPropsClock = { };

	//Chama o método para obter as propriedades do relogio.
	Hr = PonteiroTrabalho->GetProperties(&vi_OutPropsClock);

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

	//Converte a estrutura nativa para a gerenciada e define no parametro de saida.
	Param_Out_PropriedadesRelogio = Util.ConverterMFCLOCK_PROPERTIESUnamaged_ToManaged(&vi_OutPropsClock);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o estado atual do relógio.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_EstadoRelogio">Retorna o valor da enumeração que define o estado atual do relógio.</param>
CarenResult CarenMFPresentationClock::GetState(UInt32 Param_ValorReservado, [Out] Enumeracoes::CA_MFCLOCK_STATE% Param_Out_EstadoRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MFCLOCK_STATE vi_OutStateClock;

	//Chama o método para obter o estado do relogio.
	Hr = PonteiroTrabalho->GetState(Param_ValorReservado, &vi_OutStateClock);

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

	//Define o estado do relogio no parametro de saida.
	Param_Out_EstadoRelogio = static_cast<CA_MFCLOCK_STATE>(vi_OutStateClock);

Done:;
	//Retorna o resultado
	return Resultado;
}