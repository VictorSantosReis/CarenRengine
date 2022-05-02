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
#include "CarenAudioClient3.h"

//Destruidor.
CarenAudioClient3::~CarenAudioClient3()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioClient3::CarenAudioClient3()
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
CarenResult CarenAudioClient3::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioClient3::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioClient3*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioClient3**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioClient3::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioClient3*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioClient3**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioClient3::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioClient3::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioClient3::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioClient3::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioClient3::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioClient3::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioClient3::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenAudioClient3();
}



// Métodos da interface proprietária(ICarenAudioClient3)


/// <summary>
/// (GetCurrentSharedModeEnginePeriod) - Retorna o formato atual e a periodicidade do motor de áudio. Este método permite que os clientes de áudio correspondam ao período atual do mecanismo de áudio. 
/// </summary>
/// <param name="Param_Out_Formato">Retorna o formato atual do dispositivo que está sendo usado pelo motor de áudio.</param>
/// <param name="Param_Out_PeriodoAtualEmFrames">Retorna o período atual do motor de áudio, em frames de áudio.</param>
CarenResult CarenAudioClient3::GetCurrentSharedModeEnginePeriod(
[Out] CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_Formato, 
[Out] UInt32% Param_Out_PeriodoAtualEmFrames)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* vi_pOutWavFormat = Nulo;
	UINT32 vi_OutPeriodActualFrames = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentSharedModeEnginePeriod(
		reinterpret_cast<WAVEFORMATEX**>(&vi_pOutWavFormat),
		&vi_OutPeriodActualFrames
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

	//Converte a estrutura nativa para a gerenciada.
	Param_Out_Formato = Util.ConverterWaveformatExtensibleUnmanagedToManaged(vi_pOutWavFormat);

	//Define o periodo em frames.
	Param_Out_PeriodoAtualEmFrames = vi_OutPeriodActualFrames;

Done:;
	//Libera a memória utilizada pela estrutura
	if (ObjetoValido(vi_pOutWavFormat))
		CoTaskMemFree(vi_pOutWavFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetSharedModeEnginePeriod) - Retorna a gama de periodicidades suportadas pelo motor para o formato de fluxo especificado. A periodicidade do motor é a taxa na qual o motor acorda um cliente de 
/// áudio orientado por eventos para transferir dados de áudio para ou do motor. Os valores retornados dependem das características do cliente de áudio especificadas através de uma chamada anterior 
/// para ICarenAudioClient2::SetClientProperties. 
/// </summary>
/// <param name="Param_Formato">O formato de fluxo para o qual as periodicidades suportadas são consultadas.</param>
/// <param name="Param_Out_PeriodoPadraoEmFrames">Retorna o período padrão com o qual o motor acordará o cliente para a transferência de amostras de áudio</param>
/// <param name="Param_Out_PeriodoFundamentalEmFrames">Retorna o período fundamental com o qual o motor acordará o cliente para a transferência de amostras de áudio. Ao definir a periodicidade do mecanismo
/// de áudio, você deve usar um múltiplo integral deste valor.</param>
/// <param name="Param_Out_PeriodoMinEmFrames">Retorna o menor período, em quadros de áudio, com o qual o motor de áudio acordará o cliente para a transferência de amostras de áudio.</param>
/// <param name="Param_Out_PeriodoMaxEmFrames">Retorna o período mais longo, em quadros de áudio, com o qual o motor de áudio acordará o cliente para a transferência de amostras de áudio.</param>
CarenResult CarenAudioClient3::GetSharedModeEnginePeriod(
CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato, 
[Out] UInt32% Param_Out_PeriodoPadraoEmFrames,
[Out] UInt32% Param_Out_PeriodoFundamentalEmFrames,
[Out] UInt32% Param_Out_PeriodoMinEmFrames,
[Out] UInt32% Param_Out_PeriodoMaxEmFrames)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* vi_pWavFormat = Nulo;
	UINT32 vi_OutPeriodDefaultInFrames = 0;
	UINT32 vi_OutPeriodFundamentalsInFrames = 0;
	UINT32 vi_OutPeriodMinInFrames = 0;
	UINT32 vi_OutPeriodMaxInFrames = 0;

	//Converte a estrutura gerenciada para a nativa.
	vi_pWavFormat = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_Formato);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSharedModeEnginePeriod(
		const_cast<WAVEFORMATEX*>(reinterpret_cast<WAVEFORMATEX*>(vi_pWavFormat)),
		&vi_OutPeriodDefaultInFrames,
		&vi_OutPeriodFundamentalsInFrames,
		&vi_OutPeriodMinInFrames,
		&vi_OutPeriodMaxInFrames
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

	//Define as informações no parametros de saida.
	Param_Out_PeriodoPadraoEmFrames = vi_OutPeriodDefaultInFrames;
	Param_Out_PeriodoFundamentalEmFrames = vi_OutPeriodFundamentalsInFrames;
	Param_Out_PeriodoMinEmFrames = vi_OutPeriodMinInFrames;
	Param_Out_PeriodoMaxEmFrames = vi_OutPeriodMaxInFrames;

Done:;
	//libera a memória para a estrutura.
	DeletarEstruturaSafe(&vi_pWavFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (InitializeSharedAudioStream) - Inicializa um fluxo compartilhado com a periodicidade especificada.
/// </summary>
/// <param name="Param_FlagsFluxo">Bandeiras para controlar a criação do fluxo. O cliente deve definir este parâmetro como 0 ou para o bitwise OR de uma ou mais das constantes 
/// CA_CoreAudio_AUDCLNT_STREAMFLAGS_XXX suportadas ou CA_CoreAudio_AUDCLNT_SESSIONFLAGS_XXX.</param>
/// <param name="Param_PeriodoEmFrames">Periodicidade solicitada pelo cliente. Esse valor deve ser um múltiplo integral do valor retornado no parâmetro (Param_Out_PeriodoFundamentalEmFrames) para 
/// ICarenAudioClient3::GetSharedModeEnginePeriod. Param_PeriodoEmFrames também devem ser maiores ou iguais ao valor retornado em (Param_Out_PeriodoMinEmFrames) e menor ou igual ao valor 
/// retornado em (Param_Out_PeriodoMaxEmFrames).</param>
/// <param name="Param_Formato">Este parâmetro deve apontar para um descritor de formato válido do tipo WAVEFORMATEXTENSIBLE.</param>
/// <param name="Param_GuidSessaoAudio">Uma string para a sessão GUID. Este parâmetro aponta para um valor GUID que identifica a sessão de áudio a que o fluxo pertence. Se o GUID identificar uma sessão 
/// aberta anteriormente, o método adicionará o fluxo a essa sessão. Se o GUID não identificar uma sessão existente, o método abrirá uma nova sessão e adicionará o fluxo a essa sessão. O fluxo permanece 
/// um membro da mesma sessão por toda a sua vida. Definir este parâmetro como NULO é equivalente a passar um ponteiro para um valor GUID_NULL.</param>
CarenResult CarenAudioClient3::InitializeSharedAudioStream(
UInt32 Param_FlagsFluxo, 
UInt32 Param_PeriodoEmFrames, 
CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato, 
String^ Param_GuidSessaoAudio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* vi_pWaveFormat = Nulo;
	GUID vi_GuidSessionAudio = GUID_NULL;

	//Converte a estrutura gerenciada para a nativa.
	vi_pWaveFormat = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_Formato);

	//Converte a string para o GUID se informado
	if (StringObjetoValido(Param_GuidSessaoAudio))
		vi_GuidSessionAudio = Util.CreateGuidFromString(Param_GuidSessaoAudio);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeSharedAudioStream(
	static_cast<DWORD>(Param_FlagsFluxo),
		Param_PeriodoEmFrames,
		const_cast<WAVEFORMATEX*>(reinterpret_cast<WAVEFORMATEX*>(vi_pWaveFormat)),
		&vi_GuidSessionAudio
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
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&vi_pWaveFormat);

	//Retorna o resultado.
	return Resultado;
}





// Métodos da interface (ICarenAudioClient2)


/// <summary>
/// (GetBufferSizeLimits) - Retorna os limites de tamanho de buffer do mecanismo de áudio de hardware em unidades de 100 nanossegundos.
/// </summary>
/// <param name="Param_Formato">Uma estrutura CA_WAVEFORMATEXEXTENSIBLE que descreve o formato de destino que está sendo consultado para o limite de tamanho do buffer.</param>
/// <param name="Param_EventDriven">Valor booleano para indicar se o fluxo pode ou não ser orientado por eventos.</param>
/// <param name="Param_Out_MinBufferDuration">Retorna o tamanho mínimo de buffer (em unidades de 100 nanossegundos) que é necessário para que o mecanismo de áudio de hardware subjacente funcione no formato especificado no parâmetro Param_Formato, sem falhas de áudio frequentes.</param>
/// <param name="Param_Out_MaxBufferDuration">Retorna o tamanho máximo do buffer (em unidades de 100 nanossegundos) que o mecanismo de áudio de hardware subjacente pode suportar para o formato especificado no parâmetro Param_Formato.</param>
CarenResult CarenAudioClient3::GetBufferSizeLimits(
	CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato,
	Boolean Param_EventDriven,
	[Out] Int64% Param_Out_MinBufferDuration,
	[Out] Int64% Param_Out_MaxBufferDuration)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	WAVEFORMATEXTENSIBLE* vi_pWavFormat = Nulo;
	INT64 vi_OutMinBuffer = 0;
	INT64 vi_OutMaxBuffer = 0;

	//Converte a estrutura gerenciada para a nativa.
	vi_pWavFormat = Util.ConverterWaveformatExtensibleManagedToUnamaged(Param_Formato);

	//Verifica se converteu com sucesso
	if (!ObjetoValido(vi_pWavFormat))
	{
		//Define erro na operação.
		Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_ESTRUTURA, false);

		//Sai do método.
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBufferSizeLimits(
		const_cast<WAVEFORMATEX*>(reinterpret_cast<WAVEFORMATEX*>(vi_pWavFormat)),
		Param_EventDriven ? true : false,
		&vi_OutMinBuffer,
		&vi_OutMaxBuffer
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

	//Define os dados nos parametros de saida.
	Param_Out_MinBufferDuration = vi_OutMinBuffer;
	Param_Out_MaxBufferDuration = vi_OutMaxBuffer;

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pWavFormat);

	//Retorna o resultado.
	return Resultado;
}


/// <summary>
/// Recupera informações sobre se o ponto final no qual um fluxo é criado é capaz de suportar um fluxo de áudio descarregado.
/// </summary>
/// <param name="Param_Categoria">Uma enumeração que especifica a categoria de um fluxo de áudio.</param>
/// <param name="Param_Out_OffloadCapable">Retorna um valor booleano. TRUE indica que o ponto final é capaz de descarregar. FALSE indica que o ponto final não é capaz de descarregar.</param>
CarenResult CarenAudioClient3::IsOffloadCapable(
	CA_AUDIO_STREAM_CATEGORY Param_Categoria,
	[Out] Boolean% Param_Out_OffloadCapable)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	BOOL vi_OutOffloadCapable = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsOffloadCapable(
		static_cast<_AUDIO_STREAM_CATEGORY>(Param_Categoria),
		&vi_OutOffloadCapable
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

	//Define o resultado no parametro de saida.
	Param_Out_OffloadCapable = vi_OutOffloadCapable ? true : false;

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetClientProperties) -  Define as propriedades do fluxo de áudio povoando uma estrutura CA_AudioClientProperties.
/// </summary>
/// <param name="Param_Propriedades">Uma estrutura CA_AudioClientProperties.</param>
CarenResult CarenAudioClient3::SetClientProperties(CA_AudioClientProperties^ Param_Propriedades)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	AudioClientProperties* vi_pAudioProps = Nulo;

	//Converte a estrutura gerenciada para a nativa.
	vi_pAudioProps = Util.ConverterCoreAudio_AudioClientPropertiesManagedToUnamaged(Param_Propriedades);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetClientProperties(const_cast<AudioClientProperties*>(vi_pAudioProps));

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
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&vi_pAudioProps);

	//Retorna o resultado.
	return Resultado;
}





//Métodos da interface (ICarenAudioClient)


/// <summary>
/// (GetBufferSize) - O método recupera o tamanho (capacidade máxima) do buffer de ponto de extremidade.
/// </summary>
/// <param name="Param_Out_NumeroFramesBuffer">Retorna o número de quadros de áudio que o buffer pode conter.</param>
CarenResult CarenAudioClient3::GetBufferSize([Out] UInt32% Param_Out_NumeroFramesBuffer)
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
CarenResult CarenAudioClient3::GetCurrentPadding([Out] UInt32% Param_Out_NumeroQuadrosPreenchimento)
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
CarenResult CarenAudioClient3::GetDevicePeriod([Out] Int64% Param_Out_IntervaloPeriodicoDefault, [Out] Int64% Param_Out_IntervaloPeriodicoMinimo)
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
CarenResult CarenAudioClient3::GetMixFormat([Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoDispositivo)
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
CarenResult CarenAudioClient3::GetService(String^ Param_RIID, ICaren^ Param_Out_Interface)
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
CarenResult CarenAudioClient3::GetStreamLatency([Out] Int64% Param_Out_Latencia)
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
CarenResult CarenAudioClient3::Initialize(
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

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memoria para (pWaveformat) convertido da classe gerenciada para não gerenciada.
	if (ObjetoValido(pWaveformat))
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
CarenResult CarenAudioClient3::IsFormatSupported(
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
CarenResult CarenAudioClient3::Reset() {
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
CarenResult CarenAudioClient3::SetEventHandle(ICarenEvent^ Param_EventHandle)
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
CarenResult CarenAudioClient3::Start() {
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
CarenResult CarenAudioClient3::Stop()
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

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}