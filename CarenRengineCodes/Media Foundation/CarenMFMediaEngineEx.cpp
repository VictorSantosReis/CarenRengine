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
#include "CarenMFMediaEngineEx.h"

//Destruidor.
CarenMFMediaEngineEx::~CarenMFMediaEngineEx()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFMediaEngineEx::CarenMFMediaEngineEx()
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
CarenResult CarenMFMediaEngineEx::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineEx::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineEx*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineEx**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaEngineEx::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaEngineEx*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaEngineEx**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineEx::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaEngineEx::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaEngineEx::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaEngineEx::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaEngineEx::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaEngineEx::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaEngineEx::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaEngineEx::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaEngineEx();
}



// Métodos da interface proprietária(ICarenMFMediaEngineEx)


/// <summary>
/// Aplica as seleções de fluxo de chamadas anteriores para SetStreamSelection.
/// </summary>
CarenResult CarenMFMediaEngineEx::ApplyStreamSelections()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ApplyStreamSelections();

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
/// Cancela o próximo marcador de linha do tempo pendente.
/// </summary>
CarenResult CarenMFMediaEngineEx::CancelTimelineMarkerTimer()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CancelTimelineMarkerTimer();

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
/// Ativa ou desativa o espelhamento do vídeo.
/// </summary>
/// <param name="Param_Ativar">Se TRUE,o vídeo é espelhado horizontalmente. Caso contrário, o vídeo é exibido normalmente.</param>
CarenResult CarenMFMediaEngineEx::EnableHorizontalMirrorMode(Boolean Param_Ativar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnableHorizontalMirrorMode(Param_Ativar? TRUE: FALSE);

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
/// Ativa ou desativa o temporizador de atualização de tempo.
/// </summary>
/// <param name="Param_AtivarTime">Se TRUE, o temporizador de atualização estar ativado. Caso contrário, o temporizador está desativado.</param>
CarenResult CarenMFMediaEngineEx::EnableTimeUpdateTimer(Boolean Param_AtivarTime)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnableTimeUpdateTimer(Param_AtivarTime? TRUE: FALSE);

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
/// Ativa ou desativa o modo de cadeia de swap sem janelas.
/// </summary>
/// <param name="Param_Ativar">Se TRUE, o modo Windowless Swap-chain está ativado.</param>
CarenResult CarenMFMediaEngineEx::EnableWindowlessSwapchainMode(Boolean Param_Ativar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EnableWindowlessSwapchainMode(Param_Ativar? TRUE: FALSE);

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
/// Dá um passo para frente ou para trás.
/// </summary>
/// <param name="Param_Avancar">Especifique TRUE para dar um passo em FRENTE ou FALSE para dar um passo para TRÀS.</param>
CarenResult CarenMFMediaEngineEx::FrameStep(Boolean Param_Avancar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FrameStep(Param_Avancar? TRUE: FALSE);

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
/// Obtém a função de ponto final do dispositivo de áudio usada para a próxima chamada para SetSource ou Load.
/// </summary>
/// <param name="Param_Out_Role">Recebe a função de ponto final de áudio.</param>
CarenResult CarenMFMediaEngineEx::GetAudioEndpointRole([Out] CA_ERole% Param_Out_Role)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutRole = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAudioEndpointRole(&vi_OutRole);

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

	//Converte e define no parametro de saida.
	Param_Out_Role = static_cast<CA_ERole>(vi_OutRole);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a categoria de fluxo de áudio usada para a próxima chamada para SetSource ou Load.
/// </summary>
/// <param name="Param_Out_Categoria">Recebe a categoria de fluxo de áudio.</param>
CarenResult CarenMFMediaEngineEx::GetAudioStreamCategory([Out] CA_AUDIO_STREAM_CATEGORY% Param_Out_Categoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 vi_OutCategoriaAudio = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAudioStreamCategory(&vi_OutCategoriaAudio);

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

	//Converte e define no parametro de saida.
	Param_Out_Categoria = static_cast<CA_AUDIO_STREAM_CATEGORY>(vi_OutCategoriaAudio);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o equilíbrio de áudio.
/// </summary>
/// <param name="Param_Out_Balance">Devolve o equilíbrio de áudio. O valor pode ser qualquer número na faixa seguinte faixa(-1 a 1). Se o valor for zero, 
/// os canais esquerdo e direito estão em volumes iguais. O valor padrão é zero.</param>
void CarenMFMediaEngineEx::GetBalance([Out] double% Param_Out_Balance)
{
	//Chama o método para realizar a operação.
	Param_Out_Balance = PonteiroTrabalho->GetBalance();
}

/// <summary>
/// Obtém o número de fluxos no recurso de mídia.
/// </summary>
/// <param name="Param_Out_NumFluxos">Retorna o número de fluxos no recurso de mídia.</param>
CarenResult CarenMFMediaEngineEx::GetNumberOfStreams([Out] UInt32% Param_Out_NumFluxos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutNumFluxos = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNumberOfStreams(&vi_OutNumFluxos);

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

	//Converte e define no parametro de saida.
	Param_Out_NumFluxos = static_cast<UInt32>(vi_OutNumFluxos);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo de apresentação do recurso de mídia.
/// </summary>
/// <param name="Param_GuidMFAtributos">O atributo a ser consultado. Para obter uma lista de atributos de apresentação, consulte a estrutura: 
/// GUIDs_MFAttributes_PresentationDescriptor</param>
/// <param name="Param_Out_ValorAtributo">Retrona uma CA_PROPVARIANT com os dados do atributo.</param>
CarenResult CarenMFMediaEngineEx::GetPresentationAttribute(
String^ Param_GuidMFAtributos, 
[Out] CA_PROPVARIANT^% Param_Out_ValorAtributo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_GuidAtributo = GUID_NULL;
	LPPROPVARIANT vi_PropVar = Nulo;

	//Converte a string para o Guid.
	vi_GuidAtributo = Util.CreateGuidFromString(Param_GuidMFAtributos);

	//Inicializa a propvariant.
	IniciarPropVariant(&vi_PropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPresentationAttribute(vi_GuidAtributo, vi_PropVar);

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

	//Converte a propvariant para gerenciada e define no parametro de saida.
	Param_Out_ValorAtributo = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_PropVar);

Done:;
	//Libera a PROPVARIANT.
	DeletarPropVariantSafe(&vi_PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o modo em tempo real usado para a próxima chamada para SetSource ou Load.
/// </summary>
/// <param name="Param_Out_Habilitado">Recebe o modo em tempo real.</param>
CarenResult CarenMFMediaEngineEx::GetRealTimeMode([Out] Boolean% Param_Out_Habilitado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutHabilitado = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRealTimeMode(&vi_OutHabilitado);

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

	//Define o resultado no parametro de saida.
	Param_Out_Habilitado = vi_OutHabilitado ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recebe várias bandeiras que descrevem o recurso de mídia.
/// </summary>
/// <param name="Param_Out_Caracteristcas">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MFMEDIASOURCE_CHARACTERISTICS.</param>
CarenResult CarenMFMediaEngineEx::GetResourceCharacteristics([Out] CA_MFMEDIASOURCE_CHARACTERISTICS% Param_Out_Caracteristcas)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD vi_OutCaracteristicas = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetResourceCharacteristics(&vi_OutCaracteristicas);

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

	//Converte e define no parametro de saida o resultado.
	Param_Out_Caracteristcas = static_cast<CA_MFMEDIASOURCE_CHARACTERISTICS>(vi_OutCaracteristicas);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma estatística de reprodução do Media Engine.
/// </summary>
/// <param name="Param_TipoEstatistica">Um membro da enumeração CA_MF_MEDIA_ENGINE_STATISTIC que identifica a estatística a obter.</param>
/// <param name="Param_Out_ValorEstatistica">Retrona uma CA_PROPVARIANT com os dados da estatitisca requisitada.</param>
CarenResult CarenMFMediaEngineEx::GetStatistics(
CA_MF_MEDIA_ENGINE_STATISTIC Param_TipoEstatistica, 
[Out] CA_PROPVARIANT^% Param_Out_ValorEstatistica)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PropVariantManager UtilVariant = PropVariantManager();
	LPPROPVARIANT vi_PropVar = Nulo;

	//Inicializa a propvariant.
	IniciarPropVariant(&vi_PropVar);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStatistics(static_cast<MF_MEDIA_ENGINE_STATISTIC>(Param_TipoEstatistica), vi_PropVar);

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

	//Converte a propvariant e define no parametro de saida.
	Param_Out_ValorEstatistica = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_PropVar);

Done:;
	//Libera a propvariant.
	DeletarPropVariantSafe(&vi_PropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Para vídeo 3D estereoscópico, obtém o layout das duas visualizações dentro de um quadro de vídeo.
/// </summary>
/// <param name="Param_Out_ModoLayout">Recebe um membro da enumeração CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE com o modo de layout.</param>
CarenResult CarenMFMediaEngineEx::GetStereo3DFramePackingMode([Out] CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE% Param_Out_ModoLayout)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MF_MEDIA_ENGINE_S3D_PACKING_MODE vi_OutModeLayout = MF_MEDIA_ENGINE_S3D_PACKING_MODE::MF_MEDIA_ENGINE_S3D_PACKING_MODE_NONE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStereo3DFramePackingMode(&vi_OutModeLayout);

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

	//Converte e define no parametro de saida.
	Param_Out_ModoLayout = static_cast<CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE>(vi_OutModeLayout);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Para vídeo 3D estereoscópico, consulta como o Media Engine renderiza o conteúdo de vídeo 3D.
/// </summary>
/// <param name="Param_Out_TipoSaida">Recebe um membro da enumeração CA_MF3DVideoOutputType com o tipo de saida.</param>
CarenResult CarenMFMediaEngineEx::GetStereo3DRenderMode([Out] CA_MF3DVideoOutputType% Param_Out_TipoSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	MF3DVideoOutputType vi_OutTipoSaida = MF3DVideoOutputType::MF3DVideoOutputType_BaseView;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStereo3DRenderMode(&vi_OutTipoSaida);

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

	//Converte o resultado e define no parametro de saida.
	Param_Out_TipoSaida = static_cast<CA_MF3DVideoOutputType>(vi_OutTipoSaida);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém um atributo de nível de fluxo do recurso de mídia.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
/// <param name="Param_GuidMfAtributo">O atributo a ser consultado. Os valores possíveis estão presentes nas estruturas: GUIDs_MFAttributes_StreamDescriptor e GUIDs_MF_MEDIATYPE_ATTRIBUTES</param>
/// <param name="Param_Out_ValorAtributo">>Retrona uma CA_PROPVARIANT com os dados do atributo.</param>
CarenResult CarenMFMediaEngineEx::GetStreamAttribute(
UInt32 Param_IdFluxo, 
String^ Param_GuidMfAtributo, 
[Out] CA_PROPVARIANT^% Param_Out_ValorAtributo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	GUID vi_GuidAtributo = GUID_NULL;
	LPPROPVARIANT vi_OutValorAtributo = Nulo;

	//Converte a string para o guid.
	vi_GuidAtributo = Util.CreateGuidFromString(Param_GuidMfAtributo);

	//Inicializa a propvariant.
	IniciarPropVariant(&vi_OutValorAtributo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamAttribute(static_cast<DWORD>(Param_IdFluxo), vi_GuidAtributo, vi_OutValorAtributo);

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

	//Converte a propvariant e define no parametro de saida.
	Param_Out_ValorAtributo = UtilVariant.ConverterPropVariantUnmanaged_ToManaged(vi_OutValorAtributo);

Done:;
	//Libera a propvariant.
	DeletarPropVariantSafe(&vi_OutValorAtributo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Verifica se um fluxo está selecionado para reprodução.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
/// <param name="Param_Out_Selecionado">Retorna um valor booleano que indica o status da seleção de um fluxo para reprodução.</param>
CarenResult CarenMFMediaEngineEx::GetStreamSelection(
UInt32 Param_IdFluxo, 
[Out] Boolean% Param_Out_Selecionado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutSelected = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetStreamSelection(static_cast<DWORD>(Param_IdFluxo), &vi_OutSelected);

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

	//Define o resultado no parametro de saida.
	Param_Out_Selecionado = vi_OutSelected ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o tempo do próximo marcador de linha do tempo, se houver.
/// </summary>
/// <param name="Param_Out_TimeToFire">Retorna um valor com o tempo(em segundos) para o proximo marcador de linha do tempo. Se não houver, o retorno é NaN.</param>
CarenResult CarenMFMediaEngineEx::GetTimelineMarkerTimer([Out] double% Param_Out_TimeToFire)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	double vi_OutTimer = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTimelineMarkerTimer(&vi_OutTimer);

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

	//Define o resultado no parametro de saida.
	Param_Out_TimeToFire = vi_OutTimer;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a Handle de windowless Swap chain.
/// </summary>
/// <param name="Param_Out_Handle">Receber a handle para o swap chain.</param>
CarenResult CarenMFMediaEngineEx::GetVideoSwapchainHandle([Out] IntPtr% Param_Out_Handle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	HANDLE vi_OutHandle = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVideoSwapchainHandle(&vi_OutHandle);

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

	//Define o resultado no parametro de saida.
	Param_Out_Handle = IntPtr(vi_OutHandle);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Insere um efeito de áudio.
/// </summary>
/// <param name="Param_Efeito">Um ponteiro para uma interface que contém o efeito de Áudio. Essa interface pode ser uma: ICarenMFTransform ou ICarenMFActivate.</param>
/// <param name="Param_Opcional">Um valor Booleano para se o efeito a ser inserido é opcional ou não.</param>
CarenResult CarenMFMediaEngineEx::InsertAudioEffect(
ICaren^ Param_Efeito, 
Boolean Param_Opcional)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pEfeito = Nulo;

	//Recupera o ponteiro para a interface do efeito.
	CarenGetPointerFromICarenSafe(Param_Efeito, vi_pEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InsertAudioEffect(vi_pEfeito, Param_Opcional ? TRUE : FALSE);

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
/// Insere um efeito de vídeo.
/// </summary>
/// <param name="Param_Efeito">Um ponteiro para uma interface que contém o efeito de Vídeo. Essa interface pode ser uma: ICarenMFTransform ou ICarenMFActivate.</param>
/// <param name="Param_Opcional">Um valor Booleano para se o efeito a ser inserido é opcional ou não.</param>
CarenResult CarenMFMediaEngineEx::InsertVideoEffect(
ICaren^ Param_Efeito, 
Boolean Param_Opcional)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* vi_pEfeito = Nulo;

	//Recupera o ponteiro para a interface do efeito.
	CarenGetPointerFromICarenSafe(Param_Efeito, vi_pEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InsertVideoEffect(vi_pEfeito, Param_Opcional ? TRUE : FALSE);

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
/// Verifica se o Media Engine pode reproduzir a uma taxa de reprodução especificada.
/// </summary>
/// <param name="Param_Taxa">A taxa a ser verificado o suporte.</param>
/// <param name="Param_Out_Suporte">Retorna um valor Booleano para se a taxa é suportada pela Media Engine.</param>
void CarenMFMediaEngineEx::IsPlaybackRateSupported(
double Param_Taxa, 
[Out] Boolean% Param_Out_Suporte)
{
	//Chama o método para realizar a operação.
	Param_Out_Suporte = static_cast<Boolean>(PonteiroTrabalho->IsPlaybackRateSupported(Param_Taxa));
}

/// <summary>
/// Verifica se o recurso de mídia contém conteúdo protegido.
/// </summary>
/// <param name="Param_Out_Protegido">Retorna um valor Booleano para se o recurso de mídia contém conteúdo protegido.</param>
CarenResult CarenMFMediaEngineEx::IsProtected([Out] Boolean% Param_Out_Protegido)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutProtegido = FALSE;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->IsProtected(&vi_OutProtegido);

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

	//Define o resultado no parametro de saida.
	Param_Out_Protegido = vi_OutProtegido ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsStereo3D) - Verifica se o recurso de mídia contém vídeo 3D estereoscópico.
/// </summary>
/// <param name="Param_Out_Resultado">Retorna um valor Booleano para se a mídia contém video 3D estereoscópico.</param>
void CarenMFMediaEngineEx::IsStereo3D([Out] Boolean% Param_Out_Resultado)
{
	//Chama o método para realizar a operação.
	Param_Out_Resultado = static_cast<Boolean>(PonteiroTrabalho->IsStereo3D());
}

/// <summary>
/// Remove todos os efeitos de áudio e vídeo.
/// </summary>
CarenResult CarenMFMediaEngineEx::RemoveAllEffects()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveAllEffects();

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
/// Define o ponto final do dispositivo de áudio usado para a próxima chamada para DefinirFonte ou Load.
/// </summary>
/// <param name="Param_Role">Especifica a função de ponto final de áudio.</param>
CarenResult CarenMFMediaEngineEx::SetAudioEndpointRole(CA_ERole Param_Role)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAudioEndpointRole(static_cast<UINT32>(Param_Role));

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
/// Define a categoria fluxo de áudio para a próxima chamada para DefinirFonte ou Load.
/// </summary>
/// <param name="Param_Categoria">Especifica a categoria do fluxo de áudio.</param>
CarenResult CarenMFMediaEngineEx::SetAudioStreamCategory(CA_AUDIO_STREAM_CATEGORY Param_Categoria)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAudioStreamCategory(static_cast<AUDIO_STREAM_CATEGORY>(Param_Categoria));

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
/// Define o equilíbrio de áudio.
/// </summary>
/// <param name="Param_Balance">O valor do equilíbrio do áudio a ser definido. Os valores vaõ de -1 a 1, ZERO é o padrão.</param>
CarenResult CarenMFMediaEngineEx::SetBalance(double Param_Balance)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetBalance(Param_Balance);

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
/// Busca uma nova posição de reprodução usando o MF_MEDIA_ENGINE_SEEK_MODE especificado.
/// </summary>
/// <param name="Param_Posicao">A nova posição de reprodução, em segundos.</param>
/// <param name="Param_Modo">Especifica se a busca é uma busca normal ou uma busca aproximada.</param>
CarenResult CarenMFMediaEngineEx::SetCurrentTimeEx(
double Param_Posicao, 
CA_MF_MEDIA_ENGINE_SEEK_MODE Param_Modo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentTimeEx(Param_Posicao, static_cast<MF_MEDIA_ENGINE_SEEK_MODE>(Param_Modo));

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
/// Define o modo em tempo real usado para a próxima chamada para DefinirFonte ou Load.
/// </summary>
/// <param name="Param_Habilitar">Especifica o modo em tempo real.</param>
CarenResult CarenMFMediaEngineEx::SetRealTimeMode(Boolean Param_Habilitar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRealTimeMode(Param_Habilitar ? TRUE : FALSE);

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
/// Abre um recurso de mídia a partir de um fluxo de bytes.
/// </summary>
/// <param name="Param_FluxoBytes">Um ponteiro para a interface ICarenMFByteStream do fluxo de bytes.</param>
/// <param name="Param_Url">A URL do fluxo de bytes.</param>
CarenResult CarenMFMediaEngineEx::SetSourceFromByteStream(
ICarenMFByteStream^ Param_FluxoBytes, 
String^ Param_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pByteStream = Nulo;
	BSTR vi_pUrl = Nulo;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_FluxoBytes, vi_pByteStream);

	//Converte a url para o fluxo se valida.
	if (ObjetoGerenciadoValido(Param_Url))
		vi_pUrl = Util.ConverterStringToBSTR(Param_Url);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSourceFromByteStream(vi_pByteStream, vi_pUrl);

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
	//Libera a memória utilizada pela string.
	DeletarStringBSTRSafe(&vi_pUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Para vídeo 3D estereoscópico, define o layout das duas visualizações dentro de um quadro de vídeo.
/// </summary>
/// <param name="Param_ModoLayout">Um membro da enumeração CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE que especifica o layout. As duas vistas podem ser organizadas lado 
/// a lado, ou de cima para baixo.</param>
CarenResult CarenMFMediaEngineEx::SetStereo3DFramePackingMode(CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE Param_ModoLayout)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetStereo3DFramePackingMode(static_cast<MF_MEDIA_ENGINE_S3D_PACKING_MODE>(Param_ModoLayout));

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
/// Para vídeo 3D estereoscópico, especifica como o Media Engine renderiza o conteúdo de vídeo 3D.
/// </summary>
/// <param name="Param_TipoSaida">Um membro da enumeração MF3DVideoOutputType que especifica o modo de renderização de vídeo 3D.</param>
CarenResult CarenMFMediaEngineEx::SetStereo3DRenderMode(CA_MF3DVideoOutputType Param_TipoSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetStereo3DRenderMode(static_cast<MF3DVideoOutputType>(Param_TipoSaida));

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
/// Seleciona ou desmarca um fluxo para reprodução.
/// </summary>
/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
/// <param name="Param_Habilitar">Especifica se deve selecionar ou desmarcar o fluxo.</param>
CarenResult CarenMFMediaEngineEx::SetStreamSelection(
UInt32 Param_IdFluxo, 
Boolean Param_Habilitar)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetStreamSelection(static_cast<DWORD>(Param_IdFluxo), Param_Habilitar ? TRUE : FALSE);

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
/// Especifica um tempo de apresentação quando o Media Engine enviará um evento marcador.
/// </summary>
/// <param name="Param_TimeToFire">O tempo de apresentação para o evento marcador, em segundos.</param>
CarenResult CarenMFMediaEngineEx::SetTimelineMarkerTimer(double Param_TimeToFire)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTimelineMarkerTimer(Param_TimeToFire);

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
/// Atualiza o retângulo de origem, o retângulo de destino e a cor da borda do vídeo.
/// </summary>
/// <param name="Param_Origem">Uma estrutura CA_MFVideoNormalizedRect que especifica o retângulo de origem. O retângulo de origem define a área do quadro de vídeo exibido. 
/// Se este parâmetro for NULO,todo o quadro de vídeo será exibido.</param>
/// <param name="Param_Destino">Uma estrutura CA_RECT que especifica o retângulo de destino. O retângulo de destino define a área da janela ou o visual 
/// DirectComposition onde o vídeo é desenhado.</param>
/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
CarenResult CarenMFMediaEngineEx::UpdateVideoStream(
CA_MFVideoNormalizedRect^ Param_Origem,
CA_RECT^ Param_Destino, 
CA_MFARGB^ Param_CorBorda)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	MFVideoNormalizedRect* vi_pRectOrigem = Nulo;
	PRECT vi_pRectDestino = Nulo;
	MFARGB* vi_pCorBorda = Nulo;

	//Converte as estruturas.
	vi_pRectOrigem = Util.ConverterMFVideoNormalizedRectManaged_ToUnamaged(Param_Origem);
	vi_pRectDestino = Util.ConverterRECTManagedToUnmanaged(Param_Destino);
	vi_pCorBorda = Util.ConverterMFARGBManaged_ToUnamaged(Param_CorBorda);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UpdateVideoStream(vi_pRectOrigem, vi_pRectDestino, vi_pCorBorda);

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




// Métodos da interface (ICarenMFMediaEngine)


/// <summary>
/// Pergunta o quão provável é que o Media Engine possa reproduzir um tipo especificado de recurso de mídia.
/// </summary>
/// <param name="Param_TipoMime">Uma string que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
/// <param name="Param_Out_CanPlay">Recebe um valor de enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
CarenResult CarenMFMediaEngineEx::CanPlayType(
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
void CarenMFMediaEngineEx::GetAutoPlay([Out] Boolean% Param_Out_AutoPlay)
{
	//Chama o método para realizar a operação.
	Param_Out_AutoPlay = static_cast<Boolean>(PonteiroTrabalho->GetAutoPlay());
}

/// <summary>
/// Consulta quantos dados de recursos o mecanismo de mídia bufferou.
/// </summary>
/// <param name="Param_Out_Buffered">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineEx::GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered)
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
CarenResult CarenMFMediaEngineEx::GetCurrentSource([Out] String^% Param_Out_Url)
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
void CarenMFMediaEngineEx::GetCurrentTime([Out] double% Param_Out_PosicaoAtual)
{
	//Chama o método para realizar a operação.
	Param_Out_PosicaoAtual = PonteiroTrabalho->GetCurrentTime();
}

/// <summary>
/// Obtém a taxa de reprodução padrão.
/// </summary>
/// <param name="Param_Out_DefaultRate">Obtém o valor que indica a taxa de reprodução padrão.</param>
void CarenMFMediaEngineEx::GetDefaultPlaybackRate([Out] double% Param_Out_DefaultRate)
{
	//Chama o método para realizar a operação.
	Param_Out_DefaultRate = PonteiroTrabalho->GetDefaultPlaybackRate();
}

/// <summary>
/// Obtém a duração do recurso de mídia.
/// </summary>
/// <param name="Param_Out_Duracao">Recupera o valor da duração do recurso de mídia.</param>
void CarenMFMediaEngineEx::GetDuration([Out] double% Param_Out_Duracao)
{
	//Chama o método para realizar a operação.
	Param_Out_Duracao = PonteiroTrabalho->GetDuration();
}

/// <summary>
/// Obtém o status de erro mais recente.
/// </summary>
/// <param name="Param_Out_Error">Recebe um ponteiro para a interface ICarenMFMediaError ou para o valor NULO. Se o valor não for NULO, o chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineEx::GetError([Out] ICarenMFMediaError^% Param_Out_Error)
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
void CarenMFMediaEngineEx::GetLoop([Out] Boolean% Param_Out_Loop)
{
	//Chama o método para realizar a operação.
	Param_Out_Loop = static_cast<Boolean>(PonteiroTrabalho->GetLoop());
}

/// <summary>
/// Pergunta se o áudio está silenciado.
/// </summary>
/// <param name="Param_Out_Muted">Obtém um valor booleano que indica se o áudio está silenciado.</param>
void CarenMFMediaEngineEx::GetMuted([Out] Boolean% Param_Out_Muted)
{
	//Chama o método para realizar a operação.
	Param_Out_Muted = static_cast<Boolean>(PonteiroTrabalho->GetMuted());
}

/// <summary>
/// Obtém o tamanho do quadro de vídeo, ajustado para proporção.
/// </summary>
/// <param name="Param_Out_X">Retorna a Largura(X) do vídeo.</param>
/// <param name="Param_Out_Y">Retorna a Altura(Y) do vídeo.</param>
CarenResult CarenMFMediaEngineEx::GetNativeVideoSize(
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
void CarenMFMediaEngineEx::GetNetworkState([Out] CA_MF_MEDIA_ENGINE_NETWORK% Param_Out_StateNetwork)
{
	//Chama o método para realizar a operação.
	Param_Out_StateNetwork = static_cast<CA_MF_MEDIA_ENGINE_NETWORK>(PonteiroTrabalho->GetNetworkState());
}

/// <summary>
/// Obtém a taxa de reprodução atual.
/// </summary>
/// <param name="Param_Out_PlaybackRate">Obtém um valor que indica a taxa de reprodução atual.</param>
void CarenMFMediaEngineEx::GetPlaybackRate([Out] double% Param_Out_PlaybackRate)
{
	//Chama o método para realizar a operação.
	Param_Out_PlaybackRate = PonteiroTrabalho->GetPlaybackRate();
}

/// <summary>
/// Obtém os intervalos de tempo que foram prestados.
/// </summary>
/// <param name="Param_Out_Played">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineEx::GetPlayed([Out] ICarenMFMediaTimeRange^% Param_Out_Played)
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
void CarenMFMediaEngineEx::GetPreload([Out] CA_MF_MEDIA_ENGINE_PRELOAD% Param_Out_Preload)
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
void CarenMFMediaEngineEx::GetReadyState([Out] CA_MF_MEDIA_ENGINE_READY% Param_Out_RadyState)
{
	//Chama o método para realizar a operação.
	Param_Out_RadyState = static_cast<CA_MF_MEDIA_ENGINE_READY>(PonteiroTrabalho->GetReadyState());
}

/// <summary>
/// Obtém os intervalos de tempo aos quais o Media Engine pode procurar atualmente.
/// </summary>
/// <param name="Param_Out_Seekable">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
CarenResult CarenMFMediaEngineEx::GetSeekable([Out] ICarenMFMediaTimeRange^% Param_Out_Seekable)
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
void CarenMFMediaEngineEx::GetStartTime([Out] double% Param_Out_PosicaoInicial)
{
	//Chama o método para realizar a operação.
	Param_Out_PosicaoInicial = PonteiroTrabalho->GetStartTime();
}

/// <summary>
/// Obtém a proporção de imagem do fluxo de vídeo.
/// </summary>
/// <param name="Param_Out_X">Retonar o valor (X) do Aspect Ratio do fluxo do vídeo.</param>
/// <param name="Param_Out_Y">Retonar o valor (Y) do Aspect Ratio do fluxo do vídeo.</param>
CarenResult CarenMFMediaEngineEx::GetVideoAspectRatio(
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
void CarenMFMediaEngineEx::GetVolume([Out] double% Param_Out_Volume)
{
	//Chama o método para realizar a operação.
	Param_Out_Volume = PonteiroTrabalho->GetVolume();
}

/// <summary>
/// Pergunta se o recurso de mídia atual contém um fluxo de áudio.
/// </summary>
/// <param name="Param_Out_AudioPresente">Retornar um booleano TRUE se um fluxo de áudio estiver disponível na mídia. Caso contrario, FALSE.</param>
void CarenMFMediaEngineEx::HasAudio([Out] Boolean% Param_Out_AudioPresente)
{
	//Chama o método para realizar a operação.
	Param_Out_AudioPresente = static_cast<Boolean>(PonteiroTrabalho->HasAudio());
}

/// <summary>
/// Pergunta se o recurso de mídia atual contém um fluxo de vídeo.
/// </summary>
/// <param name="Param_Out_VideoPresente">Retornar um booleano TRUE se um fluxo de vídeo estiver disponível na mídia. Caso contrario, FALSE.</param>
void CarenMFMediaEngineEx::HasVideo([Out] Boolean% Param_Out_VideoPresente)
{
	//Chama o método para realizar a operação.
	Param_Out_VideoPresente = static_cast<Boolean>(PonteiroTrabalho->HasVideo());
}

/// <summary>
/// Verifica se a reprodução terminou.
/// </summary>
/// <param name="Param_Out_ReproducaoTerminada">Retornar um booleano TRUE se a reprodução tiver terminado. Caso contrario, FALSE.</param>
void CarenMFMediaEngineEx::IsEnded([Out] Boolean% Param_Out_ReproducaoTerminada)
{
	//Chama o método para realizar a operação.
	Param_Out_ReproducaoTerminada = static_cast<Boolean>(PonteiroTrabalho->IsEnded());
}

/// <summary>
/// Verifica se a reprodução está pausada no momento.
/// </summary>
/// <param name="Param_Out_PauseStatus">Retorna um valor booleano indicando se a reprodução está pausada.</param>
void CarenMFMediaEngineEx::IsPaused([Out] Boolean% Param_Out_PauseStatus)
{
	//Chama o método para realizar a operação.
	Param_Out_PauseStatus = static_cast<Boolean>(PonteiroTrabalho->IsPaused());
}

/// <summary>
/// Verifica se o Media Engine está atualmente buscando uma nova posição de reprodução.
/// </summary>
/// <param name="Param_Out_BuscandoPosicao">Retornar um valor booleano que indica se a Media Engine está buscando uma nova posição.</param>
void CarenMFMediaEngineEx::IsSeeking([Out] Boolean% Param_Out_BuscandoPosicao)
{
	//Chama o método para realizar a operação.
	Param_Out_BuscandoPosicao = static_cast<Boolean>(PonteiroTrabalho->IsSeeking());
}

/// <summary>
/// Carrega a fonte de mídia atual.
/// </summary>
CarenResult CarenMFMediaEngineEx::Load()
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
CarenResult CarenMFMediaEngineEx::OnVideoStreamTick([Out] Int64% Param_Out_TempoApresentacaoFrame)
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
CarenResult CarenMFMediaEngineEx::Pause()
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
CarenResult CarenMFMediaEngineEx::Play()
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
CarenResult CarenMFMediaEngineEx::SetAutoPlay(Boolean Param_AutoPlay)
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
CarenResult CarenMFMediaEngineEx::SetCurrentTime(double Param_NovaPosicao)
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
CarenResult CarenMFMediaEngineEx::SetDefaultPlaybackRate(double Param_TaxaReproducaoDefault)
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
CarenResult CarenMFMediaEngineEx::SetErrorCode(CA_MF_MEDIA_ENGINE_ERR Param_Error)
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
CarenResult CarenMFMediaEngineEx::SetLoop(Boolean Param_Loop)
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
CarenResult CarenMFMediaEngineEx::SetMuted(Boolean Param_Mudo)
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
CarenResult CarenMFMediaEngineEx::SetPlaybackRate(double Param_TaxaReproducaoAtual)
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
CarenResult CarenMFMediaEngineEx::SetPreload(CA_MF_MEDIA_ENGINE_PRELOAD Param_Preload)
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
CarenResult CarenMFMediaEngineEx::SetSource(String^ Param_Url)
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
CarenResult CarenMFMediaEngineEx::SetSourceElements(ICarenMFMediaEngineSrcElements^ Param_ElementosMidia)
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
CarenResult CarenMFMediaEngineEx::SetVolume(double Param_Volume)
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
CarenResult CarenMFMediaEngineEx::Shutdown()
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
CarenResult CarenMFMediaEngineEx::TransferVideoFrame(
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