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
#include "CarenAudioRenderClient.h"


//Destruidor.
CarenAudioRenderClient::~CarenAudioRenderClient()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioRenderClient::CarenAudioRenderClient()
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
CarenResult CarenAudioRenderClient::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioRenderClient::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioRenderClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioRenderClient**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioRenderClient::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioRenderClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioRenderClient**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioRenderClient::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioRenderClient::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioRenderClient::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioRenderClient::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioRenderClient::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioRenderClient::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioRenderClient::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioRenderClient();
}



//
//Métodos da interface proprietaria
//

/// <summary>
/// (GetBuffer) - Recupera um ponteiro para o próximo espaço disponível no buffer de ponto de extremidade de renderização no qual o chamador pode gravar um pacote de dados.
/// O chamador pode solicitar um tamanho de pacote que é menor ou igual à quantidade de espaço disponível no buffer (exceto no caso de um fluxo de modo exclusivo que usa o buffer orientado a eventos; 
/// para obter mais informações, consulte ICarenAudioClient::Initialize).
/// O espaço disponível é simplesmente o tamanho do buffer menos a quantidade de dados no buffer que já está Enfileirado até ser reproduzido. Se o chamador especifica um valor Param_NumeroFramesRequisitados
/// que excede o espaço disponível no buffer, a chamada falhará.
/// Atenção: O cliente deve chamar o método (ReleaseBuffer) após uma chamada (GetBuffer) que obtém com êxito um pacote de qualquer tamanho diferente de 0. O cliente tem a opção de chamar ou não 
/// chamar ReleaseBuffer para liberar um pacote de tamanho 0.
/// </summary>
/// <param name="Param_NumeroFramesRequisitados">O número de quadros de áudio no pacote de dados que o chamador planeja gravar no espaço solicitado no buffer. Se a chamada for bem-sucedida, o tamanho da 
/// área de buffer apontado pelo parametro (Param_BufferAudio) corresponde ao tamanho especificado no parametro (Param_NumeroFramesRequisitados).</param>
/// <param name="Param_TamanhoFrameInBytes">O tamanho de um Frame de (AUDIO) em bytes. Esse valor é utilizado para calcular o tamanho do buffer real de (ICarenBuffer).</param>
/// <param name="Param_Out_BufferAudio">Recebe a interface que contém um ponteiro de buffer onde será a área disponivel para escrever os dados de áudio.</param>
CarenResult CarenAudioRenderClient::GetBuffer(UInt32 Param_NumeroFramesRequisitados, UInt32 Param_TamanhoFrameInBytes, [Out] ICarenBuffer^% Param_Out_BufferAudio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas
	PBYTE pBufferData = NULL;
	UInt32 LarguraDisponivelBuffer = Param_TamanhoFrameInBytes * Param_NumeroFramesRequisitados;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBuffer(Param_NumeroFramesRequisitados, &pBufferData);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o buffer a ser retornado no paremtro.
	Param_Out_BufferAudio = gcnew CarenBuffer();

	//Associa o ponteiro de dados a classe.
	Resultado = Param_Out_BufferAudio->CreateBuffer(IntPtr(pBufferData), false, LarguraDisponivelBuffer, LarguraDisponivelBuffer);

	//Verifica se houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera o buffer novamente.
		PonteiroTrabalho->ReleaseBuffer(Param_NumeroFramesRequisitados, 0);

		//Limpa os dados.
		pBufferData = NULL;
		Param_Out_BufferAudio = nullptr;

		//Define o novo status de erro.
		Resultado.AdicionarCodigo(Resultado.StatusCode, false);

		//Sai do método
		Sair;
	}

	//Define o código da operação anterior novamente.
	Resultado.AdicionarCodigo(Hr, true);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseBuffer) - O método libera o espaço de buffer adquirido na chamada anterior para o método ICarenAudioRenderClient::GetBuffer.
/// </summary>
/// <param name="Param_NumeroFramesEscritos">O número de quadros de áudio gravados pelo cliente para o pacote de dados. O valor deste parâmetro deve ser menor ou igual ao tamanho do pacote de dados, 
/// conforme especificado no parâmetro Param_NumeroFramesRequisitados passado para o método ICarenAudioRenderClient::GetBuffer.</param>
/// <param name="Param_Flags">Os sinalizadores de configuração de buffer. O chamador pode definir esse parâmetro tanto para 0(Disponivel na enumeração) ou para o seguinte valor de enumeração CA_AUDIOCLIENTE_BUFFERFLAGS (um bit de sinalizador).</param>
CarenResult CarenAudioRenderClient::ReleaseBuffer(UInt32 Param_NumeroFramesEscritos, Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas
	_AUDCLNT_BUFFERFLAGS BuffFlags = static_cast<_AUDCLNT_BUFFERFLAGS>(Param_Flags);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReleaseBuffer(Param_NumeroFramesEscritos, BuffFlags);

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