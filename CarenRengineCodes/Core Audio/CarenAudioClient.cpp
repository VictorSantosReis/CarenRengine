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
#include "CarenAudioClient.h"


//Destruidor.
CarenAudioClient::~CarenAudioClient()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioClient::CarenAudioClient()
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
CarenResult CarenAudioClient::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
CarenResult CarenAudioClient::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IAudioClient*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenAudioClient::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IAudioClient*>(Param_PonteiroNativo);

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
CarenResult CarenAudioClient::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenAudioClient::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenAudioClient::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenAudioClient::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenAudioClient::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioClient::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioClient::LiberarReferencia()
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
void CarenAudioClient::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioClient();
}





//Métodos da interface proprietaria(ICarenAudioClient)


/// <summary>
/// (GetBufferSize) - O método recupera o tamanho (capacidade máxima) do buffer de ponto de extremidade.
/// </summary>
/// <param name="Param_Out_NumeroFramesBuffer">Retorna o número de quadros de áudio que o buffer pode conter.</param>
CarenResult CarenAudioClient::GetBufferSize([Out] UInt32% Param_Out_NumeroFramesBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 CountFramesBuffer = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBufferSize(&CountFramesBuffer);

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

	//Define o resultado no parametro de saida
	Param_Out_NumeroFramesBuffer = CountFramesBuffer;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetCurrentPadding) - O método recupera o número de quadros de preenchimento no buffer de ponto de extremidade.
/// </summary>
/// <param name="Param_Out_NumeroQuadrosPreenchimento">Retorna a contagem de quadros (o número de quadros de áudio de preenchimento no buffer).</param>
CarenResult CarenAudioClient::GetCurrentPadding([Out] UInt32% Param_Out_NumeroQuadrosPreenchimento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 CountPaddingFrames = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentPadding(&CountPaddingFrames);

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
	Param_Out_NumeroQuadrosPreenchimento = CountPaddingFrames;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDevicePeriod) - O método recupera o comprimento do intervalo periódico separando o processamento sucessivo passa pelo mecanismo de áudio nos dados no buffer de ponto de extremidade.
/// </summary>
/// <param name="Param_Out_IntervaloPeriodicoDefault">Retorna um valor de tempo especificando o intervalo padrão entre o processamento periódico passa pelo mecanismo de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
/// <param name="Param_Out_IntervaloPeriodicoMinimo">Retorna um valor de tempo especificando o intervalo mínimo entre o processamento periódico passa pelo dispositivo de ponto de extremidade de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
CarenResult CarenAudioClient::GetDevicePeriod([Out] Int64% Param_Out_IntervaloPeriodicoDefault, [Out] Int64% Param_Out_IntervaloPeriodicoMinimo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	REFERENCE_TIME DefaultPeriodicTime = 0;
	REFERENCE_TIME MinimunPeriodicTime = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDevicePeriod(&DefaultPeriodicTime, &MinimunPeriodicTime);

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

	//Define os valores nos parametros de saida.
	Param_Out_IntervaloPeriodicoDefault = static_cast<Int64>(DefaultPeriodicTime);
	Param_Out_IntervaloPeriodicoMinimo = static_cast<Int64>(MinimunPeriodicTime);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetMixFormat) - O método recupera o formato de fluxo que o mecanismo de áudio usa para seu processamento interno de fluxos de modo compartilhado.
/// O formato de mixagem é o formato que o mecanismo de áudio usa internamente para processamento digital de fluxos de modo compartilhado. Este formato não é necessariamente um formato que suporta o 
/// dispositivo de ponto final de áudio.
/// </summary>
/// <param name="Param_Out_FormatoDispositivo">Retorna uma estrutura que contém os dados do formato de mixagem. Se o método falhar, este parametro é nulo.</param>
CarenResult CarenAudioClient::GetMixFormat([Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* pWaveFormat = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMixFormat((WAVEFORMATEX**)&pWaveFormat);

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

	//Cria e define a estrutura que vai ser retornada no parametro de saida.
	Param_Out_FormatoDispositivo = Util.ConverterWaveformatExtensibleUnmanagedToManaged(pWaveFormat);

Done:;
	//Libera o aramzenamento de (pWaveFormat) se este for valido.
	if (ObjetoValido(pWaveFormat))
	{
		//Libera os dados segundo a documentação deste método
		CoTaskMemFree(pWaveFormat);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetService) - O método acessa serviços adicionais do objeto de cliente de áudio.
/// </summary>
/// <param name="Param_RIID">A identificação de interface para o serviço solicitado.</param>
/// <param name="Param_Out_Interface">Retorna um ponteiro para a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenAudioClient::GetService(String^ Param_RIID, ICaren^ Param_Out_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IIDInterfaceRequested = GUID_NULL;
	LPVOID pInterfaceRequested = NULL;

	//Cria o guid a parti da String fornecida.
	IIDInterfaceRequested = Util.CreateGuidFromString(Param_RIID);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetService(IIDInterfaceRequested, &pInterfaceRequested);

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

	//Define o ponteiro de trabalho na interface
	Param_Out_Interface->AdicionarPonteiro(pInterfaceRequested);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetStreamLatency) - O método recupera a latência máxima para o fluxo atual e pode ser chamado a qualquer momento depois que o fluxo foi inicializado.
/// </summary>
/// <param name="Param_Out_Latencia">Retorna um valor de tempo que representa a latência. O tempo é expresso em unidades de 100 nanosegundos.</param>
CarenResult CarenAudioClient::GetStreamLatency([Out] Int64% Param_Out_Latencia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	REFERENCE_TIME LatencyStream = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamLatency(&LatencyStream);

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

	//Define o resultado no parametro de saida
	Param_Out_Latencia = static_cast<Int64>(LatencyStream);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Initialize) - Inicializa o fluxo de áudio.
/// </summary>
/// <param name="Param_ModoCompartilhamento">O modo de compartilhamento para a conexão. Por meio desse parâmetro, o cliente informa ao mecanismo de áudio se deseja compartilhar o dispositivo de ponto de extremidade de áudio com outros clientes.</param>
/// <param name="Param_FlagsFluxo">Sinalizadores para controlar a criação do fluxo. O cliente deve definir esse parâmetro como 0 ou para o bit ou OR de um ou mais das: AUDCLNT_STREAMFLAGS_XXX  ou AUDCLNT_SESSIONFLAGS_XXX constantes.</param>
/// <param name="Param_DuraçãoBuffer">A capacidade de buffer como um valor de tempo. Este parâmetro é do tipo REFERENCE_TIME(Int64) e é expresso em unidades de 100 nanossegundos. Este parâmetro contém o 
/// tamanho do buffer que o chamador solicita para o buffer que o aplicativo de áudio compartilhará com o mecanismo de áudio (no modo compartilhado) ou com o dispositivo de ponto de extremidade 
/// (no modo exclusivo). Se a chamada for bem-sucedida, o método aloca um buffer que é um mínimo este grande.</param>
/// <param name="Param_PeriodoDispositivo">O período do dispositivo. Este parâmetro pode ser diferente de zero somente no modo exclusivo. No modo compartilhado, sempre defina esse parâmetro como 0. No 
/// modo exclusivo, esse parâmetro especifica o período de agendamento solicitado para acessos de buffer sucessivos pelo dispositivo de ponto de extremidade de áudio. Se o período de dispositivo solicitado
/// estiver fora do intervalo que é definido pelo período mínimo do dispositivo e o período máximo do sistema, o método aperta o período para esse intervalo. Se este parâmetro for 0, o método define o 
/// período do dispositivo para seu valor padrão. Para obter o período de dispositivo padrão, chame o método ICarenAudioClient::GetDevicePeriod.</param>
/// <param name="Param_Formato">Uma estrutura que é um descritor do formato de áudio a ser processado. Este parâmetro deve apontar para um descritor de formato válido do tipo CA_WAVEFORMATEXEXTENSIBLE</param>
/// <param name="Param_GuidSessãoAudio">O guid da sessão audio. Este valor é um GUID que identifica a sessão de áudio que pertence o fluxo. Se o GUID identifica uma sessão que 
/// foi aberta anteriormente, o método adiciona o fluxo para essa sessão. Se o GUID não identifica uma sessão existente, o método abre uma nova sessão e adiciona o fluxo para essa sessão. O fluxo 
/// permanece um membro da mesma sessão para seu tempo de vida. Definindo esse parâmetro como NULO é equivalente a passar um ponteiro para um valor GUID_NULL.</param>
CarenResult CarenAudioClient::Initialize(
	Enumeracoes::CA_AUDIOCLIENTE_SHAREMODE Param_ModoCompartilhamento,
	UInt32 Param_FlagsFluxo,
	Int64 Param_DuraçãoBuffer,
	Int64 Param_PeriodoDispositivo,
	Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Formato,
	String^ Param_GuidSessãoAudio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* pWaveformat = NULL;
	AUDCLNT_SHAREMODE ModeShare = static_cast<AUDCLNT_SHAREMODE>(Param_ModoCompartilhamento);
	REFERENCE_TIME DurationBuffer = static_cast<REFERENCE_TIME>(Param_DuraçãoBuffer);
	REFERENCE_TIME PeridicDevice = static_cast<REFERENCE_TIME>(Param_PeriodoDispositivo);
	GUID GuidSessionAudio = GUID_NULL;

	//Verifica se foi especificado uma sessão de audio
	if (!String::IsNullOrEmpty(Param_GuidSessãoAudio))
	{
		//Gera o guid da sessão de audio
		GuidSessionAudio = Util.CreateGuidFromString(Param_GuidSessãoAudio);
	}

	//Cria o waveformatex a parti do informado pelo usuário.
	pWaveformat = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_Formato);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Initialize(ModeShare, (DWORD)Param_FlagsFluxo, DurationBuffer, PeridicDevice, (WAVEFORMATEX*)pWaveformat, &GuidSessionAudio);

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
	//Libera a memoria para (pWaveformat) convertido da classe gerenciada para não gerenciada.
	if(ObjetoValido(pWaveformat))
	{
		//Como a estrutura foi criada a parti do método (CriarEstrutura) ela deve ser deletada através de (DeletarEstrutura)
		DeletarEstrutura(&pWaveformat);
	}

	//Limpa os dados.
	GuidSessionAudio = GUID_NULL;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsFormatSupported) - Método indica se o dispositivo de ponto de extremidade de áudio oferece suporte a um formato de fluxo específico.
/// </summary>
/// <param name="Param_ModoCompartilhamento">O modo de compartilhamento para o Formatar de fluxo. Por meio desse parâmetro, o cliente indica se deseja usar o formato especificado no modo exclusivo ou no modo compartilhado.</param>
/// <param name="Param_Formato">O formato de fluxo especificado a ser verificado.</param>
/// <param name="Param_Out_FormatoMaisProximo">Retorna o formato mais proximo do formato especificado no paramêtro (Param_Formato).</param>
CarenResult CarenAudioClient::IsFormatSupported(
	Enumeracoes::CA_AUDIOCLIENTE_SHAREMODE Param_ModoCompartilhamento,
	Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Formato,
	[Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoMaisProximo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	AUDCLNT_SHAREMODE ModeShare = static_cast<_AUDCLNT_SHAREMODE>(Param_ModoCompartilhamento);
	WAVEFORMATEXTENSIBLE* pWaveformat;
	WAVEFORMATEXTENSIBLE* pWaveformatAproximado = NULL;

	//Cria o formato wave a parti da estrutura fornecida.
	pWaveformat = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_Formato);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsFormatSupported(ModeShare, (WAVEFORMATEX*)pWaveformat, (WAVEFORMATEX**)&pWaveformatAproximado);

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

	//Verifica se o ponteiro para o formato aproximado é valido
	if (ObjetoValido(pWaveformatAproximado))
	{
		//Cria a estrutura gerenciada a parti do formato aproximado retornado pelo método e defini no parametro de saida.
		Param_Out_FormatoMaisProximo = Util.ConverterWaveformatExtensibleUnmanagedToManaged(pWaveformatAproximado);
	}

Done:;
	//Libera a memoria das estruturas.
	if (ObjetoValido(pWaveformatAproximado))
	{
		//Libera a memoria.
		CoTaskMemFree(pWaveformatAproximado);
	}
	if (ObjetoValido(pWaveformat))
	{
		//Como a estrutura foi criada a parti do método (CriarEstrutura) ela deve ser deletada através de (DeletarEstrutura)
		DeletarEstrutura(&pWaveformat);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Reset) - O método redefine o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
/// Reset é um método de controle que o cliente chama para redefinir um fluxo de áudio interrompido. Reset o fluxo libera todos os dados pendentes e redefine a posição do fluxo de relógio de 
/// áudio para 0. Esse método falhará se ele é chamado em um fluxo que não é interrompido.
/// </summary>
CarenResult CarenAudioClient::Reset() {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Reset();

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
/// (SetEventHandle) - O método define o identificador de evento que o sistema sinaliza quando um buffer de áudio está pronto para ser processado pelo cliente.
/// </summary>
/// <param name="Param_EventHandle">O identificador de evento.</param>
CarenResult CarenAudioClient::SetEventHandle(ICarenEvent^ Param_EventHandle) 
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	HANDLE vi_EventHandle = Nulo;

	//Tenta recuperar o ponteiro para o evento.
	Resultado = Param_EventHandle->RecuperarEvento(&vi_EventHandle);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
		Sair;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetEventHandle(vi_EventHandle);

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
/// (Start) - O método inicia o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
/// Start é um método de controle que o cliente chama para iniciar o fluxo de áudio. Iniciando o fluxo faz com que a ICarenAudioClient interface para iniciar o streaming de dados entre o buffer de 
/// ponto de extremidade e o mecanismo de áudio. Ele também faz com que o fluxo de relógio de áudio para retomar a contagem de sua posição atual.
/// </summary>
CarenResult CarenAudioClient::Start() {
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Start();

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
/// (Stop) - O método interrompe o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
/// Stop é um método de controle que interrompe um fluxo de áudio em execução. Esse método interrompe a transmissão de dados por meio da conexão do cliente com o mecanismo de áudio. Interromper o fluxo 
/// congela o relógio de áudio do fluxo em sua posição atual do fluxo. Uma chamada subsequente para ICarenAudioClient::Start faz com que o fluxo retomar a execução a partir dessa posição. 
/// Se necessário, o cliente pode chamar o ICarenAudioClient::Reset método para redefinir a posição enquanto o fluxo é interrompido.
/// </summary>
CarenResult CarenAudioClient::Stop()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
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
	//Retorna o resultado.
	return Resultado;
}