#include "../pch.h"
#include "CarenMFVideoPresenter.h"


//Destruidor.
CarenMFVideoPresenter::~CarenMFVideoPresenter()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFVideoPresenter::CarenMFVideoPresenter()
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
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O cliente é responsável por liberar a interface.</param>
CarenResult CarenMFVideoPresenter::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
	Hr = (reinterpret_cast<IMFVideoPresenter*>(PonteiroTrabalho))->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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
	Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

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
CarenResult CarenMFVideoPresenter::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFVideoPresenter*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFVideoPresenter::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFVideoPresenter*>(Param_PonteiroNativo);

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
CarenResult CarenMFVideoPresenter::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFVideoPresenter::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFVideoPresenter::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFVideoPresenter::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFVideoPresenter::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFVideoPresenter::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<IMFVideoPresenter*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFVideoPresenter::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<IMFVideoPresenter*>(PonteiroTrabalho))->Release();

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
void CarenMFVideoPresenter::LimparDados()
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
void CarenMFVideoPresenter::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFVideoPresenter();
}



// Métodos da interface proprietária(ICarenMFVideoPresenter)


/// <summary>
/// Recupera o tipo de mídia do apresentador. 
/// Este método retorna o tipo de mídia que o apresentador define para o tipo de saída do misturador. Descreve o formato da imagem composta.
/// </summary>
/// <param name="Param_Out_TipoVideo">Retorna uma interface para o tipo de midia de video do apresentador.</param>
/// <returns></returns>
CarenResult CarenMFVideoPresenter::GetCurrentMediaType([Out] ICarenMFVideoMediaType^% Param_Out_TipoVideo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFVideoMediaType* pMediaTypeSaida = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentMediaType(&pMediaTypeSaida);

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

	//Cria a interface que vai ser retornada.
	Param_Out_TipoVideo = gcnew CarenMFVideoMediaType();

	//Define o ponteiro de trabalho
	Param_Out_TipoVideo->AdicionarPonteiro(pMediaTypeSaida);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Envia uma mensagem para o apresentador de vídeo. As mensagens são usadas para sinalizar ao apresentador que ele deve realizar alguma ação, ou que algum evento ocorreu.
/// </summary>
/// <param name="Param_Mensagem">Especifica a mensagem como membro da enumeração CA_MFVP_MESSAGE_TYPE.</param>
/// <param name="Param_UlParam">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
/// <returns></returns>
CarenResult CarenMFVideoPresenter::ProcessMessage(CA_MFVP_MESSAGE_TYPE Param_Mensagem, UInt64 Param_UlParam)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ProcessMessage(static_cast<MFVP_MESSAGE_TYPE>(Param_Mensagem), static_cast<ULONG_PTR>(Param_UlParam));

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



//Métodos que registram e liberam os eventos da classe.

/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFVideoPresenter::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnClockStart = gcnew DelegateNativo_Evento_OnClockStart(this, &CarenMFVideoPresenter::EncaminharEvento_OnClockStart);
	Callback_OnClockPause = gcnew DelegateNativo_Evento_OnClockPause(this, &CarenMFVideoPresenter::EncaminharEvento_OnClockPause);
	Callback_OnClockRestart = gcnew DelegateNativo_Evento_OnClockRestart(this, &CarenMFVideoPresenter::EncaminharEvento_OnClockRestart);
	Callback_OnClockStop = gcnew DelegateNativo_Evento_OnClockStop(this, &CarenMFVideoPresenter::EncaminharEvento_OnClockStop);
	Callback_OnClockSetRate = gcnew DelegateNativo_Evento_OnClockSetRate(this, &CarenMFVideoPresenter::EncaminharEvento_OnClockSetRate);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnClockStart = Util.ConverterDelegateToPointer(Callback_OnClockStart);
	IntPtr Pointer_OnClockPause = Util.ConverterDelegateToPointer(Callback_OnClockPause);
	IntPtr Pointer_OnClockRestart = Util.ConverterDelegateToPointer(Callback_OnClockRestart);
	IntPtr Pointer_OnClockStop = Util.ConverterDelegateToPointer(Callback_OnClockStop);
	IntPtr Pointer_OnClockSetRate = Util.ConverterDelegateToPointer(Callback_OnClockSetRate);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnClockStart = Util.AlocarPointerDelegate(Pointer_OnClockStart);
	gHandle_Delegate_OnClockPause = Util.AlocarPointerDelegate(Pointer_OnClockPause);
	gHandle_Delegate_OnClockRestart = Util.AlocarPointerDelegate(Pointer_OnClockRestart);
	gHandle_Delegate_OnClockStop = Util.AlocarPointerDelegate(Pointer_OnClockStop);
	gHandle_Delegate_OnClockSetRate = Util.AlocarPointerDelegate(Pointer_OnClockSetRate);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFClockStateSink que envia os eventos.
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockStart>(Pointer_OnClockStart);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockPause>(Pointer_OnClockPause);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockRestart>(Pointer_OnClockRestart);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockStop>(Pointer_OnClockStop);
	((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFClockStateSink_EventoNativo_OnClockSetRate>(Pointer_OnClockSetRate);
}


/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFVideoPresenter::UnRegisterCallback()
{
	//Libera todas as handles alocadas para os eventos.
	gHandle_Delegate_OnClockStart.Free();
	gHandle_Delegate_OnClockPause.Free();
	gHandle_Delegate_OnClockRestart.Free();
	gHandle_Delegate_OnClockStop.Free();
	gHandle_Delegate_OnClockSetRate.Free();

	//Libera os eventos da classe não gerenciada (CLN_IMFClockStateSink)
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStart = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockPause = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockRestart = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockStop = NULL;
	}
	if (ObjetoValido(((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate))
	{
		//Exclui o objeto de evento.
		((CLN_IMFClockStateSink*)PonteiroTrabalho)->Evento_OnClockSetRate = NULL;
	}
}






//Métodos que recebem os eventos da classe nativa(CLN_IMFClockStateSink)


void CarenMFVideoPresenter::EncaminharEvento_OnClockStart(MFTIME hnsSystemTime, LONGLONG llClockStartOffset)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockStart(hnsSystemTime, llClockStartOffset);
}

void CarenMFVideoPresenter::EncaminharEvento_OnClockStop(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockStop(hnsSystemTime);
}

void CarenMFVideoPresenter::EncaminharEvento_OnClockPause(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockPause(hnsSystemTime);
}

void CarenMFVideoPresenter::EncaminharEvento_OnClockRestart(MFTIME hnsSystemTime)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockRestart(hnsSystemTime);
}

void CarenMFVideoPresenter::EncaminharEvento_OnClockSetRate(MFTIME hnsSystemTime, float flRate)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.
	OnClockSetRate(hnsSystemTime, flRate);
}