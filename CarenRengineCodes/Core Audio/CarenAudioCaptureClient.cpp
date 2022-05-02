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
#include "CarenAudioCaptureClient.h"


//Destruidor.
CarenAudioCaptureClient::~CarenAudioCaptureClient()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioCaptureClient::CarenAudioCaptureClient()
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
CarenResult CarenAudioCaptureClient::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioCaptureClient::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioCaptureClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioCaptureClient**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioCaptureClient::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioCaptureClient*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioCaptureClient**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioCaptureClient::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioCaptureClient::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioCaptureClient::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioCaptureClient::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioCaptureClient::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioCaptureClient::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioCaptureClient::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioCaptureClient();
}






//
// Métodos da interface proprietária(ICarenAudioCaptureClient)
//

/// <summary>
/// (GetBuffer) - Recupera um ponteiro para o próximo pacote disponível de dados no buffer de ponto de extremidade de captura.
///  Em um determinado momento, o buffer pode conter zero, um ou mais pacotes que estão prontos para leitura. Normalmente, um thread de processamento de buffer que lê dados de um buffer 
/// de ponto de extremidade de captura lê todos os pacotes disponíveis cada vez que o thread é executado.
/// </summary>
/// <param name="Param_Out_BufferData">Retorna um ponteiro com os proximos dados disponiveis para o cliente ler.</param>
/// <param name="Param_Out_NumeroFramesLidos">Retorna a quantidade de Quadros(FRAMES) de áudio disponiveis no pacote de dados. O cliente deve ler todo o pacote de dados ou nenhum deles.</param>
/// <param name="Param_Out_Flags">Retorna um sinalizador de status de buffer. O método pode gravar 0 ou um ou mais sinalizadores da enumeração (CA_AUDIOCLIENTE_BUFFERFLAGS).</param>
/// <param name="Param_Out_PosicaoDispositivo">Retorna a posição do dispositivo do primeiro quadro de áudio no pacote de dados. A posição do dispositivo é expressa como o número de 
/// quadros de áudio desde o início do fluxo.</param>
/// <param name="Param_Out_QPCPosicao">Retorna o valor do contador de desempenho no momento em que o dispositivo de ponto de extremidade de áudio gravou a posição do dispositivo do 
/// primeiro quadro de áudio no pacote de dados. O método converte o valor do contador para unidades de 100 nanossegundos antes de escrevê-lo para (Param_Out_QPCPosicao).</param>
CarenResult CarenAudioCaptureClient::GetBuffer(
					[Out] ICarenBuffer^% Param_Out_BufferData, 
					[Out] UInt32% Param_Out_NumeroFramesLidos, 
					[Out] Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS% Param_Out_Flags,
					[Out] UInt64% Param_Out_PosicaoDispositivo,
					[Out] UInt64% Param_Out_QPCPosicao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	PBYTE pBufferData = NULL;
	UINT32 NumeroFramesLidos = 0;
	DWORD FlagsBuffer;
	UINT64 PosicaoDispositivo = 0;
	UINT64 QPCPosicao = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBuffer(&pBufferData, &NumeroFramesLidos, &FlagsBuffer, &PosicaoDispositivo, &QPCPosicao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de buffer gerenciada
	Param_Out_BufferData = gcnew CarenBuffer();

	//Define o ponteiro de dados
	Param_Out_BufferData->CreateBuffer(IntPtr(pBufferData), false, 0, 0);

	//Define o restante dos parametros
	Param_Out_NumeroFramesLidos = NumeroFramesLidos;
	Param_Out_Flags = static_cast<Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS>(FlagsBuffer);
	Param_Out_PosicaoDispositivo = PosicaoDispositivo;
	Param_Out_QPCPosicao = QPCPosicao;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetNextPacketSize) - O método recupera o número de quadros(FRAMES) no próximo pacote de dados no buffer de ponto de extremidade de captura.
/// </summary>
/// <param name="Param_Out_FramesProximoPacote">Retorna a quantidade de FRAMES do proximo pacote a ser lido.</param>
CarenResult CarenAudioCaptureClient::GetNextPacketSize([Out] UInt32% Param_Out_FramesProximoPacote)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 ProximaQuantidadeFramesPacote = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNextPacketSize(&ProximaQuantidadeFramesPacote);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_FramesProximoPacote = ProximaQuantidadeFramesPacote;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseBuffer) - O método libera o espaço de buffer adquirido na chamada anterior para o método ICarenAudioCaptureClient::GetBuffer.
/// </summary>
/// <param name="Param_NumeroFramesLidos">O número de quadros de áudio que o cliente ler do buffer de captura. Esse parâmetro deve ser igual ao número de quadros no pacote de dados 
/// adquirido anteriormente ou 0. O valor desse paramêtro é em (FRAMES).</param>
CarenResult CarenAudioCaptureClient::ReleaseBuffer(UInt32 Param_NumeroFramesLidos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReleaseBuffer(Param_NumeroFramesLidos);

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