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
#include "CarenMFSourceReaderCallback.h"


//Destruidor.
CarenMFSourceReaderCallback::~CarenMFSourceReaderCallback()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFSourceReaderCallback::CarenMFSourceReaderCallback(Boolean Param_CriarInterface)
{
	//Verifica se deve criar a interface ou não.
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFSourceReaderCallback();
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
CarenResult CarenMFSourceReaderCallback::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenMFSourceReaderCallback::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceReaderCallback*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenMFSourceReaderCallback::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IMFSourceReaderCallback*>(Param_PonteiroNativo);

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
CarenResult CarenMFSourceReaderCallback::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceReaderCallback::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenMFSourceReaderCallback::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenMFSourceReaderCallback::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSourceReaderCallback::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSourceReaderCallback::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceReaderCallback::LiberarReferencia()
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
void CarenMFSourceReaderCallback::LimparDados()
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
void CarenMFSourceReaderCallback::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenMFSourceReaderCallback();
}






//
// Métodos da interface proprietaria
//

/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFSourceReaderCallback::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.
	
	//Cria todos os delegates.
	Callback_OnReadSample = gcnew DelegateNativo_Evento_OnReadSample(this, &CarenMFSourceReaderCallback::EncaminharEvento_OnReadSample);
	Callback_OnEvent = gcnew DelegateNativo_Evento_OnEvent(this, &CarenMFSourceReaderCallback::EncaminharEvento_OnEvent);
	Callback_OnFlush = gcnew DelegateNativo_Evento_OnFlush(this, &CarenMFSourceReaderCallback::EncaminharEvento_OnFlush);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnReadSample = Util.ConverterDelegateToPointer(Callback_OnReadSample);
	IntPtr Pointer_OnEvent = Util.ConverterDelegateToPointer(Callback_OnEvent);
	IntPtr Pointer_OnFlush = Util.ConverterDelegateToPointer(Callback_OnFlush);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnReadSample = Util.AlocarPointerDelegate(Pointer_OnReadSample);
	gHandle_Delegate_OnEvent = Util.AlocarPointerDelegate(Pointer_OnEvent);
	gHandle_Delegate_OnFlush = Util.AlocarPointerDelegate(Pointer_OnFlush);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFSourceReaderCallback que envia os eventos.
	((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnReadSample = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceReaderCallback_EventoNativo_OnReadSample>(Pointer_OnReadSample);
	((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnEvent = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceReaderCallback_EventoNativo_OnEvent>(Pointer_OnEvent);
	((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnFlush = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFSourceReaderCallback_EventoNativo_OnFlush>(Pointer_OnFlush);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFSourceReaderCallback::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnReadSample.Free();
	gHandle_Delegate_OnEvent.Free();
	gHandle_Delegate_OnFlush.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnReadSample))
	{
		//Descarta o delegate.
		((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnReadSample = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnEvent))
	{
		//Descarta o delegate.
		((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnEvent = NULL;
	}
	if (ObjetoValido(((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnFlush))
	{
		//Descarta o delegate.
		((CLN_IMFSourceReaderCallback*)PonteiroTrabalho)->Evento_OnFlush = NULL;
	}
}


//
// Métodos internos que são chamados pela classe nativa para notificar os eventos ocorridos.
//


/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnReadSample) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
/// </summary>
void CarenMFSourceReaderCallback::EncaminharEvento_OnReadSample(HRESULT Param_HResultStatus, DWORD Param_FluxoID, DWORD Param_FluxoFlgs, LONGLONG Param_TimeSpanAmostra, IMFSample* Param_AmostraMidia)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.


	//Variveis utilizadas no método.
	ICarenMFSample^ InterfaceAmostra = nullptr;
	CA_MF_SOURCE_READER_FLAG FlagsLeitura = (CA_MF_SOURCE_READER_FLAG)Param_FluxoFlgs;
	CA_SAMPLE_READ_RESULT ResultadoLeitura = CA_SAMPLE_READ_RESULT::Erro;
	ResultCode Resultado = ResultCode::SS_FALSE;
	CarenResult ResultadoSetPointer;

	//Verifica se o método obteve sucesso
	if (Sucesso(Param_HResultStatus))
	{
		//Deixa o método continuar.
	}
	else if (Param_HResultStatus == MF_E_INVALIDREQUEST)
	{
		//Define que a requisição é invalida
		Resultado = ResultCode::ER_MF_E_INVALIDREQUEST;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}
	else if (Param_HResultStatus == MF_E_INVALIDSTREAMNUMBER)
	{
		//Define que o id especificado é invalido.
		Resultado = ResultCode::ER_MF_E_INVALIDSTREAMNUMBER;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}
	else if (Param_HResultStatus == MF_E_NOTACCEPTING)
	{
		//Define que uma chamada para Flush é pendente.
		Resultado = ResultCode::ER_MF_E_NOTACCEPTING;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}
	else if (Param_HResultStatus == E_INVALIDARG)
	{
		//Define que algum argumento é invalido.
		Resultado = ResultCode::ER_E_INVALIDARG;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}
	else
	{
		//Define falha no método.
		Resultado = ResultCode::ER_FAIL;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Verifica os Flags para determina o retorno

	//Determina que o tipo de dados(Formato) foi modificado.
	if (Param_FluxoFlgs & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
	{
		//Determina que o tipo da midia foi modificado.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::TipoModificado;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Indica que já alcançou o final de fluxo e não há mais Simples a serem lidas.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_ENDOFSTREAM)
	{
		//Determina que chegou ao final do fluxo.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::FimFluxo;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Indica que houve um erro ao ler os dados.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_ERROR)
	{
		//Determina que houve uma falha ao ler os dados da midia.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::Erro;

		//Define sucesso na operação.
		Resultado = ResultCode::ER_FAIL;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Indica que houve uma lacuna no fluxo.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_STREAMTICK)
	{
		//Define que houve uma lacuna no fluxo.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::LacunaFluxo;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Indica que o tipo da midia nativa foi modificada.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED)
	{
		//Define que o tipo nativo foi modificado.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::TipoNativoModificado;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Indica que o decodificador definido pelo usuário foi removido manualmente ou devido a uma modificação do tipo da midia sendo lida.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_ALLEFFECTSREMOVED)
	{
		//Define que o decodificador foi removido
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::DecodificadorRemovido;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//(MF_SOURCE_READERF_NEWSTREAM) Indica que novos fluxos de midia foram adicionados. O usuário deve selecionar novamente o fluxo a ser decodificado.
	else if (Param_FluxoFlgs & MF_SOURCE_READERF_NEWSTREAM)
	{
		//Define que um novo Stream de midia foi adicionado e que é necessário selcionar novamente o fluxo de midia desejado.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::NovoFluxo;

		//Define sucesso na operação.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		goto Done;
	}

	//Pode continuar normalmente.
	else
	{
		//Deixa o método continuar.
	}

	//Indica que não há amostra de midia na posição lida. Deve ler a proxima amostra de mídia.
	if (Param_AmostraMidia == NULL)
	{
		//Determina que não há dados e que deve ler a proxima amostra de mídia.
		ResultadoLeitura = CA_SAMPLE_READ_RESULT::NoData;

		//Define sucesso na operação mesmo com o ponteiro sem dados.
		Resultado = ResultCode::SS_OK;

		//Chama o evento para notificar o usuário.
		OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		Sair;
	}

	//Se chegar aqui é porque a amostra de mídia é valida.

	//Cria a interface que vai conter a amostra de mídia
	InterfaceAmostra = gcnew CarenMFSample(false);

	//Chama o método para definir o ponteiro da amostra de midia.
	ResultadoSetPointer = InterfaceAmostra->AdicionarPonteiro(Param_AmostraMidia);

	//Verifica se não ocorreu erro
	if (!CarenSucesso(ResultadoSetPointer))
	{
		//Ocorreu uma falha ao definir o ponteiro.

		//Libera a referência para a amostra.
		Param_AmostraMidia->Release();
		Param_AmostraMidia = NULL;
		InterfaceAmostra->Finalizar();
		InterfaceAmostra = nullptr;	

		//Chama o evento para notificar o usuário sobre o erro.
		OnReadSample(E_FAIL, ResultadoSetPointer.StatusCode, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, nullptr);

		//Sai do método
		Sair;
	}

	//Determina que há dados para serem processados.
	ResultadoLeitura = CA_SAMPLE_READ_RESULT::Sucesso;

	//Define sucesso na operação
	Resultado = ResultCode::SS_OK;

	//Chama o evento para notificar o usuário.
	OnReadSample(Param_HResultStatus, Resultado, ResultadoLeitura, FlagsLeitura, Param_FluxoID, Param_TimeSpanAmostra, InterfaceAmostra);

Done:;
	//Verifica se a interface é valida e libera
	if (InterfaceAmostra != nullptr)
	{
		//Exclui a interface.
		InterfaceAmostra = nullptr;
	}
}

/// <summary>
///Método responsável por encaminhar o (Evento) nativo (OnEvent) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
/// </summary>
void CarenMFSourceReaderCallback::EncaminharEvento_OnEvent(DWORD Param_FluxoID, IMFMediaEvent *Param_pEvento)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Verifica se o ponteiro do evento gerado é valido.
	if (Param_pEvento != NULL)
	{
		//Cria a classe do evento
		ICarenMFMediaEvent^ LeitorEvento = gcnew CarenMFMediaEvent();

		//Chama o método para definir o ponteiro para o evento.
		LeitorEvento->AdicionarPonteiro(Param_pEvento);

		//Chama o evento para notificar o usuário
		OnEvent(Param_FluxoID, LeitorEvento);


		//Limpa os dados.

		//Deleta a interface.
		LeitorEvento = nullptr;
	}
	else
	{
		//Como o evento não tem um ponteiro para o tipo e dado do evento, o método só vai enviar o ID do fluxo que gerou o evento.
		OnEvent(Param_FluxoID, nullptr);
	}
}

/// <summary>
/// Método responsável por encaminhar o (Evento) nativo (OnFlush) da classe (IMFSourceReaderCallback) para o usuário em classe gerenciada.
/// </summary>
void CarenMFSourceReaderCallback::EncaminharEvento_OnFlush(DWORD Param_FluxoID)
{
	//Não é preciso verificar se o evento é uma referência valida.
	//Em C++ CLI, caso o evento não seja valido, a função não será chamada.

	//Chama o evento para notificaro usuário
	OnFlush(Param_FluxoID);
}
