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
CarenResult CarenMFPresentationClock::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenMFPresentationClock::LimparDados()
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
void CarenMFPresentationClock::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFPresentationClock();
}




//
// Métodos da interface ICarenRelogioApresentação
//


/// <summary>
/// Registra um objeto para ser notificado sempre que o relógio inicia, para, ou faz uma pausa ou muda a taxa.
/// </summary>
/// <param name="Param_InterfaceNotification">A interface que contém o objeto de notificação de eventos do Relógio.</param>
CarenResult CarenMFPresentationClock::RegistarObjetoNotificação(ICarenMFClockStateSink^ Param_InterfaceNotification)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFClockStateSink *pStateSink = NULL;

	//Chama o método para obter o relogio de notificação.
	Resultado = Param_InterfaceNotification->RecuperarPonteiro((LPVOID*)&pStateSink);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para definir o relogio de notificação
	Hr = PonteiroTrabalho->AddClockStateSink(pStateSink);

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
CarenResult CarenMFPresentationClock::ObterHora([Out] Int64% Param_Out_NsHoraRelogio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	INT64 HoraRecenteRelogio = 0;

	//Chama o método para recuperar a hora mais atual
	Hr = PonteiroTrabalho->GetTime(&HoraRecenteRelogio);

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

	//Define o valor na hora atual.
	Param_Out_NsHoraRelogio = safe_cast<Int64>(HoraRecenteRelogio);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a fonte de tempo de apresentação do relógio.
/// </summary>
/// <param name="Param_Out_TimeSource">Recebe a interface que contém a Fonte de apreentação do relógio.</param>
CarenResult CarenMFPresentationClock::ObterFonteTempo([Out] ICarenMFPresentationTimeSource^% Param_Out_TimeSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFPresentationTimeSource *pInterfaceRequisitada = NULL;
	ICarenMFPresentationTimeSource^ InterfaceRequisitada = nullptr;

	//Chama o método para obter a fonte de tempo
	Hr = PonteiroTrabalho->GetTimeSource(&pInterfaceRequisitada);

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

	//Cria a interface que vai conter o relogio
	InterfaceRequisitada = gcnew CarenMFPresentationTimeSource();

	//Chama o método para definir o ponteiro
	InterfaceRequisitada->AdicionarPonteiro(pInterfaceRequisitada);

	//Define a interface no parametro de saida.
	Param_Out_TimeSource = InterfaceRequisitada;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Pausa o tempo de apresentação. Enquanto o relógio está em pausa, o tempo do relógio não adianta,
/// e (ObterHora) do relógio retorna o tempo em que o relógio foi pausado.
/// </summary>
CarenResult CarenMFPresentationClock::PausarRelogio()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o métdo que vai pausar o relogio.
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
CarenResult CarenMFPresentationClock::CancelarRegistroObjetoNotificação(ICarenMFClockStateSink^ Param_InterfaceNotification)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFClockStateSink *pStateSink = NULL;

	//Chama o método para obter o relogio de notificação.
	Resultado = Param_InterfaceNotification->RecuperarPonteiro((LPVOID*)&pStateSink);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método que vai cancelar o registro de notificação para o objeto.
	Hr = PonteiroTrabalho->RemoveClockStateSink(pStateSink);

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
CarenResult CarenMFPresentationClock::DefinirFonteTempo(ICarenMFPresentationTimeSource^ Param_TimeSource)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFPresentationTimeSource *pTimeSource = NULL;

	//Chama o método para recuperar o presentation time source para ser definido
	Resultado = Param_TimeSource->RecuperarPonteiro((LPVOID*)&pTimeSource);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para definir a fonte de tempo de apresentação
	Hr = PonteiroTrabalho->SetTimeSource(pTimeSource);

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
CarenResult CarenMFPresentationClock::IniciarRelogio(Int64 Param_PosiçãoInicio, Boolean Param_PosiçãoAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Verifica se vai iniciar a parti da posição atual
	if (Param_PosiçãoAtual)
	{
		//Chama o método para iniciar o relogio a parti da posição atual do relogio.
		Hr = PonteiroTrabalho->Start(PRESENTATION_CURRENT_POSITION);
	}
	else
	{
		//Chama o método que vai iniciar o relógio a parti da posição especifiada pelo usuário.
		Hr = PonteiroTrabalho->Start(Param_PosiçãoInicio);
	}

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
/// (ObterHora) método do relógio retorna zero.
/// </summary>
CarenResult CarenMFPresentationClock::PararRelogio()
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


//
// Métodos da interface ICarenMFClock
//

/// <summary>
/// Recupera as características do relógio.
/// </summary>
/// <param name="Param_Out_CaracteristicasClock">Recebe os flags com as características do relógio.</param>
CarenResult CarenMFPresentationClock::RecuperarCaracteristicas([Out] Enumeracoes::CA_CLOCK_CARACTERISTICAS% Param_Out_CaracteristicasClock)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD CaracteristicasClock = 0;

	//Chama o método para obter as caracteristicas
	Hr = PonteiroTrabalho->GetClockCharacteristics(&CaracteristicasClock);

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
	Param_Out_CaracteristicasClock = (CA_CLOCK_CARACTERISTICAS)safe_cast<UInt32>(CaracteristicasClock);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// (Não Suportado Nativamente) - Recupera a chave de continuidade do relógio.
/// </summary>
/// <param name="Param_Out_Chave">Recebe a chave de continuidade.</param>
CarenResult CarenMFPresentationClock::RecuperarChaveContinuidade([Out] UInt32% Param_Out_Chave)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	DWORD ChaveRelogio = 0;

	//Chama o método para obter a chave de continuidade
	Hr = PonteiroTrabalho->GetContinuityKey(&ChaveRelogio);

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
	Param_Out_Chave = safe_cast<UInt32>(ChaveRelogio);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera a hora do último relógio que foi correlacionada com a hora do sistema.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_ClockTime">Recebe o último tempo de relógio conhecido, em unidades de freqüência do relógio.</param>
/// <param name="Param_NsSystemTime">Recebe a hora do sistema que corresponde ao tempo de relógio retornado em Param_Out_ClockTime, em unidades de 100 nanosegundos.</param>
CarenResult CarenMFPresentationClock::ObterHoraCorrelacionada(UInt32 Param_ValorReservado, [Out] Int64% Param_Out_ClockTime, [Out] Int64% Param_NsSystemTime)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	INT64 ClockTime = 0;
	INT64 NsSystemTime = 0;

	//Chama o método para obter a hora correlacionada
	Hr = PonteiroTrabalho->GetCorrelatedTime(Param_ValorReservado, &ClockTime, &NsSystemTime);

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
	Param_Out_ClockTime = ClockTime;
	Param_NsSystemTime = NsSystemTime;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera as propriedades do relógio.
/// </summary>
/// <param name="Param_Out_PropriedadesRelogio">Retorna a estrutura que contém as propriedades do relógio atual.</param>
CarenResult CarenMFPresentationClock::ObterPropriedades([Out] Estruturas::CA_MFCLOCK_PROPERTIES^% Param_Out_PropriedadesRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	MFCLOCK_PROPERTIES PropsRelogio;
	CA_MFCLOCK_PROPERTIES^ PropriedadesRelogio;
	Utilidades Util;

	//Chama o método para obter as propriedades do relogio.
	Hr = PonteiroTrabalho->GetProperties(&PropsRelogio);

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

	//Cria a estrutura
	PropriedadesRelogio = gcnew CA_MFCLOCK_PROPERTIES();

	//Define os valores na propriedade gerenciada
	PropriedadesRelogio->RL_CLOCK_FLAGS = PropsRelogio.dwClockFlags;
	PropriedadesRelogio->RL_CORRELATION_RATE = PropsRelogio.qwCorrelationRate;
	PropriedadesRelogio->RL_FREQUENCIA_CLOCK = PropsRelogio.qwClockFrequency;
	PropriedadesRelogio->RL_GUID_RELOGIO = Util.ConverterGuidToString(PropsRelogio.guidClockId);
	PropriedadesRelogio->RL_JITTER_CLOCK = PropsRelogio.dwClockJitter;
	PropriedadesRelogio->RL_TOLERANCIA_CLOCK = PropsRelogio.dwClockTolerance;

	//Define a estrutura no parametro de retorno.
	Param_Out_PropriedadesRelogio = PropriedadesRelogio;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Recupera o estado atual do relógio.
/// </summary>
/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
/// <param name="Param_Out_EstadoRelogio">Retorna o valor da enumeração que define o estado atual do relógio.</param>
CarenResult CarenMFPresentationClock::ObterEstado(UInt32 Param_ValorReservado, [Out] Enumeracoes::CA_CLOCK_ESTADO% Param_Out_EstadoRelogio)
{
	//Variavel que vai retorna o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel Com
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	MFCLOCK_STATE StateRelogio;
	CA_CLOCK_ESTADO EstadoRelogioRetorno;

	//Chama o método para obter o estado do relogio.
	Hr = PonteiroTrabalho->GetState(Param_ValorReservado, &StateRelogio);

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

	//Verifica o estado do relogio e define na variavel.
	switch (StateRelogio)
	{
	case MFCLOCK_STATE_INVALID:
		//Define o estado do relógio.
		EstadoRelogioRetorno = CA_CLOCK_ESTADO::CLOCK_INVALIDO;
		break;

	case MFCLOCK_STATE_RUNNING:
		//Define o estado do relógio.
		EstadoRelogioRetorno = CA_CLOCK_ESTADO::CLOCK_RODANDO;
		break;

	case MFCLOCK_STATE_STOPPED:
		//Define o estado do relógio.
		EstadoRelogioRetorno = CA_CLOCK_ESTADO::CLOCK_PARADO;
		break;

	case MFCLOCK_STATE_PAUSED:
		//Define o estado do relógio.
		EstadoRelogioRetorno = CA_CLOCK_ESTADO::CLOCK_PAUSADO;
		break;
	}

	//Define o estado no parametro de retorno.
	Param_Out_EstadoRelogio = EstadoRelogioRetorno;

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}