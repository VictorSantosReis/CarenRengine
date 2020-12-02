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


#pragma once
#include "SDK_Base.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;


////////////////////////////////////////
// Windows Audio Session API (WASAPI) //
////////////////////////////////////////


//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace CoreAudio
	{
		/// <summary>
		/// (IAudioClient) - Interface responsável por permitir que um cliente criar e inicializar um fluxo de áudio entre um aplicativo de áudio e o mecanismo de áudio (para um fluxo de modo compartilhado) ou o 
		/// buffer de hardware de um dispositivo de ponto de extremidade de áudio (para um modo exclusivo fluxo). Um cliente obtém uma referência a uma interface Iaudioclient para um dispositivo de ponto de 
		/// extremidade de áudio.
		/// Nota: No Windows 8, o primeiro uso dessa interface para acessar o dispositivo de áudio deve estar no thread STA. Chamadas de um thread MTA podem resultar em comportamento indefinido.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Inicializador de fluxo de áudio.")]
		[Guid("74DCD6D6-9B5E-4660-A183-77038A11DFCE")]
		public interface class ICarenAudioClient : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetBufferSize) - O método recupera o tamanho (capacidade máxima) do buffer de ponto de extremidade.
			/// </summary>
			/// <param name="Param_Out_NumeroFramesBuffer">Retorna o número de quadros de áudio que o buffer pode conter.</param>
			CarenResult GetBufferSize([Out] UInt32% Param_Out_NumeroFramesBuffer);

			/// <summary>
			/// (GetCurrentPadding) - O método recupera o número de quadros de preenchimento no buffer de ponto de extremidade.
			/// </summary>
			/// <param name="Param_Out_NumeroQuadrosPreenchimento">Retorna a contagem de quadros (o número de quadros de áudio de preenchimento no buffer).</param>
			CarenResult GetCurrentPadding([Out] UInt32% Param_Out_NumeroQuadrosPreenchimento);

			/// <summary>
			/// (GetDevicePeriod) - O método recupera o comprimento do intervalo periódico separando o processamento sucessivo passa pelo mecanismo de áudio nos dados no buffer de ponto de extremidade.
			/// </summary>
			/// <param name="Param_Out_IntervaloPeriodicoDefault">Retorna um valor de tempo especificando o intervalo padrão entre o processamento periódico passa pelo mecanismo de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
			/// <param name="Param_Out_IntervaloPeriodicoMinimo">Retorna um valor de tempo especificando o intervalo mínimo entre o processamento periódico passa pelo dispositivo de ponto de extremidade de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
			CarenResult GetDevicePeriod([Out] Int64% Param_Out_IntervaloPeriodicoDefault, [Out] Int64% Param_Out_IntervaloPeriodicoMinimo);

			/// <summary>
			/// (GetMixFormat) - O método recupera o formato de fluxo que o mecanismo de áudio usa para seu processamento interno de fluxos de modo compartilhado.
			/// O formato de mixagem é o formato que o mecanismo de áudio usa internamente para processamento digital de fluxos de modo compartilhado. Este formato não é necessariamente um formato que suporta o 
			/// dispositivo de ponto final de áudio.
			/// </summary>
			/// <param name="Param_Out_FormatoDispositivo">Retorna uma estrutura que contém os dados do formato de mixagem. Se o método falhar, este parametro é nulo.</param>
			CarenResult GetMixFormat([Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoDispositivo);

			/// <summary>
			/// (GetService) - O método acessa serviços adicionais do objeto de cliente de áudio.
			/// </summary>
			/// <param name="Param_RIID">A identificação de interface para o serviço solicitado.</param>
			/// <param name="Param_Out_Interface">Retorna um ponteiro para a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
			CarenResult GetService(String^ Param_RIID, ICaren^ Param_Out_Interface);

			/// <summary>
			/// (GetStreamLatency) - O método recupera a latência máxima para o fluxo atual e pode ser chamado a qualquer momento depois que o fluxo foi inicializado.
			/// </summary>
			/// <param name="Param_Out_Latencia">Retorna um valor de tempo que representa a latência. O tempo é expresso em unidades de 100 nanosegundos.</param>
			CarenResult GetStreamLatency([Out] Int64% Param_Out_Latencia);

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
			CarenResult Initialize(
				Enumeracoes::CA_AUDIOCLIENTE_SHAREMODE Param_ModoCompartilhamento,
				UInt32 Param_FlagsFluxo,
				Int64 Param_DuraçãoBuffer,
				Int64 Param_PeriodoDispositivo,
				Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Formato,
				String^ Param_GuidSessãoAudio);

			/// <summary>
			/// (IsFormatSupported) - Método indica se o dispositivo de ponto de extremidade de áudio oferece suporte a um formato de fluxo específico.
			/// </summary>
			/// <param name="Param_ModoCompartilhamento">O modo de compartilhamento para o Formatar de fluxo. Por meio desse parâmetro, o cliente indica se deseja usar o formato especificado no modo exclusivo ou no modo compartilhado.</param>
			/// <param name="Param_Formato">O formato de fluxo especificado a ser verificado.</param>
			/// <param name="Param_Out_FormatoMaisProximo">Retorna o formato mais proximo do formato especificado no paramêtro (Param_Formato).</param>
			CarenResult IsFormatSupported(
				Enumeracoes::CA_AUDIOCLIENTE_SHAREMODE Param_ModoCompartilhamento,
				Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Formato,
				[Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoMaisProximo);

			/// <summary>
			/// (Reset) - O método redefine o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
			/// Reset é um método de controle que o cliente chama para redefinir um fluxo de áudio interrompido. Reset o fluxo libera todos os dados pendentes e redefine a posição do fluxo de relógio de 
			/// áudio para 0. Esse método falhará se ele é chamado em um fluxo que não é interrompido.
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// (SetEventHandle) - O método define o identificador de evento que o sistema sinaliza quando um buffer de áudio está pronto para ser processado pelo cliente.
			/// </summary>
			/// <param name="Param_EventHandle">O identificador de evento.</param>
			CarenResult SetEventHandle(IntPtr Param_EventHandle);

			/// <summary>
			/// (Start) - O método inicia o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
			/// Start é um método de controle que o cliente chama para iniciar o fluxo de áudio. Iniciando o fluxo faz com que a ICarenAudioClient interface para iniciar o streaming de dados entre o buffer de 
			/// ponto de extremidade e o mecanismo de áudio. Ele também faz com que o fluxo de relógio de áudio para retomar a contagem de sua posição atual.
			/// </summary>
			CarenResult Start();

			/// <summary>
			/// (Stop) - O método interrompe o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
			/// Stop é um método de controle que interrompe um fluxo de áudio em execução. Esse método interrompe a transmissão de dados por meio da conexão do cliente com o mecanismo de áudio. Interromper o fluxo 
			/// congela o relógio de áudio do fluxo em sua posição atual do fluxo. Uma chamada subsequente para ICarenAudioClient::Start faz com que o fluxo retomar a execução a partir dessa posição. 
			/// Se necessário, o cliente pode chamar o ICarenAudioClient::Reset método para redefinir a posição enquanto o fluxo é interrompido.
			/// </summary>
			CarenResult Stop();
		};

		/// <summary>
		/// (IAudioClient2) - A interface ICarenAudioClient2 é derivada da interface IAudioClient, com um conjunto de métodos adicionais que permitem que um cliente de áudio da Windows Audio Session API (WASAPI) 
		/// faça o seguinte: opte por descarregar, consultar propriedades de fluxo e obtenha informações do hardware que lida com a descarga.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Inicializador de fluxo de áudio.")]
		[Guid("CDBEB9FD-C9F2-4CAB-B9D6-61301D8D92DC")]
		public interface class ICarenAudioClient2 : ICarenAudioClient
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetBufferSizeLimits) - Retorna os limites de tamanho de buffer do mecanismo de áudio de hardware em unidades de 100 nanossegundos.
			/// </summary>
			/// <param name="Param_Formato">Uma estrutura CA_WAVEFORMATEXEXTENSIBLE que descreve o formato de destino que está sendo consultado para o limite de tamanho do buffer.</param>
			/// <param name="Param_EventDriven">Valor booleano para indicar se o fluxo pode ou não ser orientado por eventos.</param>
			/// <param name="Param_Out_MinBufferDuration">Retorna o tamanho mínimo de buffer (em unidades de 100 nanossegundos) que é necessário para que o mecanismo de áudio de hardware subjacente funcione no formato especificado no parâmetro Param_Formato, sem falhas de áudio frequentes.</param>
			/// <param name="Param_Out_MaxBufferDuration">Retorna o tamanho máximo do buffer (em unidades de 100 nanossegundos) que o mecanismo de áudio de hardware subjacente pode suportar para o formato especificado no parâmetro Param_Formato.</param>
			CarenResult GetBufferSizeLimits(
				CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato,
				Boolean Param_EventDriven,
				[Out] Int64% Param_Out_MinBufferDuration,
				[Out] Int64% Param_Out_MaxBufferDuration);
		
		
			/// <summary>
			/// Recupera informações sobre se o ponto final no qual um fluxo é criado é capaz de suportar um fluxo de áudio descarregado.
			/// </summary>
			/// <param name="Param_Categoria">Uma enumeração que especifica a categoria de um fluxo de áudio.</param>
			/// <param name="Param_Out_OffloadCapable">Retorna um valor booleano. TRUE indica que o ponto final é capaz de descarregar. FALSE indica que o ponto final não é capaz de descarregar.</param>
			CarenResult IsOffloadCapable(
				CA_AUDIO_STREAM_CATEGORY Param_Categoria, 
				[Out] Boolean% Param_Out_OffloadCapable);

			/// <summary>
			/// (SetClientProperties) -  Define as propriedades do fluxo de áudio povoando uma estrutura CA_AudioClientProperties.
			/// </summary>
			/// <param name="Param_Propriedades">Uma estrutura CA_AudioClientProperties.</param>
			CarenResult DefinirPropriedadesCliente(CA_AudioClientProperties^ Param_Propriedades);
		};

		/// <summary>
		/// (IAudioClient3) - A interface ICarenAudioClient3 é derivada da interface ICarenAudioClient2, com um conjunto de métodos adicionais que permitem que um cliente de áudio da Windows Audio Session API (WASAPI) 
		/// consulte as periodicidades suportadas e a periodicidade atual do mecanismo de áudio, bem como solicite a inicialização de um fluxo de áudio compartilhado com uma periodicidade especificada.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Inicializador de fluxo de áudio.")]
		[Guid("F9976109-03BE-4EF3-B146-568D7E06091E")]
		public interface class ICarenAudioClient3 : ICarenAudioClient2
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos
			
			/// <summary>
			/// (GetCurrentSharedModeEnginePeriod) - Retorna o formato atual e a periodicidade do motor de áudio. Este método permite que os clientes de áudio correspondam ao período atual do mecanismo de áudio. 
			/// </summary>
			/// <param name="Param_Out_Formato">Retorna o formato atual do dispositivo que está sendo usado pelo motor de áudio.</param>
			/// <param name="Param_Out_PeriodoAtualEmFrames">Retorna o período atual do motor de áudio, em molduras de áudio.</param>
			CarenResult GetCurrentSharedModeEnginePeriod(
				[Out] CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_Formato, 
				[Out] UInt32% Param_Out_PeriodoAtualEmFrames);

			/// <summary>
			/// (GetSharedModeEnginePeriod) - Retorna a gama de periodicidades suportadas pelo motor para o formato de fluxo especificado. A periodicidade do motor é a taxa na qual o motor acorda um cliente de 
			/// áudio orientado por eventos para transferir dados de áudio para ou do motor. Os valores retornados dependem das características do cliente de áudio especificadas através de uma chamada anterior 
			/// para ICarenAudioClient2::DefinirPropriedadesCliente. 
			/// </summary>
			/// <param name="Param_Formato">O formato de fluxo para o qual as periodicidades suportadas são consultadas.</param>
			/// <param name="Param_Out_PeriodoPadraoEmFrames">Retorna o período padrão com o qual o motor acordará o cliente para a transferência de amostras de áudio</param>
			/// <param name="Param_Out_PeriodoFundamentalEmFrames">Retorna o período fundamental com o qual o motor acordará o cliente para a transferência de amostras de áudio. Ao definir a periodicidade do mecanismo
			/// de áudio, você deve usar um múltiplo integral deste valor.</param>
			/// <param name="Param_Out_PeriodoMinEmFrames">Retorna o menor período, em quadros de áudio, com o qual o motor de áudio acordará o cliente para a transferência de amostras de áudio.</param>
			/// <param name="Param_Out_PeriodoMaxEmFrames">Retorna o período mais longo, em quadros de áudio, com o qual o motor de áudio acordará o cliente para a transferência de amostras de áudio.</param>
			CarenResult GetSharedModeEnginePeriod(
				CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato, 
				[Out] UInt32% Param_Out_PeriodoPadraoEmFrames,
				[Out] UInt32% Param_Out_PeriodoFundamentalEmFrames,
				[Out] UInt32% Param_Out_PeriodoMinEmFrames,
				[Out] UInt32% Param_Out_PeriodoMaxEmFrames);

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
			CarenResult InitializeSharedAudioStream(
				UInt32 Param_FlagsFluxo, 
				UInt32 Param_PeriodoEmFrames, 
				CA_WAVEFORMATEXEXTENSIBLE^ Param_Formato, 
				String^ Param_GuidSessaoAudio);	
		};

		/// <summary>
		/// (IAudioRenderClient) - Interface responsável por permitir que um cliente gravar dados de saída para um buffer de ponto de extremidade de renderização. O cliente obtém uma referência à interface 
		/// ICarenAudioRenderClient de um objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro RIID definido como IID_IAudioRenderClient.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Grava dados na saida do dispositivo de Audio.")]
		[Guid("A45F14E9-05F9-497A-91E1-E2903B0DFAC0")]
		public interface class ICarenAudioRenderClient : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

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
			CarenResult GetBuffer(UInt32 Param_NumeroFramesRequisitados, UInt32 Param_TamanhoFrameInBytes, [Out] ICarenBuffer^% Param_Out_BufferAudio);

			/// <summary>
			/// (ReleaseBuffer) - O método libera o espaço de buffer adquirido na chamada anterior para o método ICarenAudioRenderClient::GetBuffer.
			/// </summary>
			/// <param name="Param_NumeroFramesEscritos">O número de quadros de áudio gravados pelo cliente para o pacote de dados. O valor deste parâmetro deve ser menor ou igual ao tamanho do pacote de dados, 
			/// conforme especificado no parâmetro Param_NumeroFramesRequisitados passado para o método ICarenAudioRenderClient::GetBuffer.</param>
			/// <param name="Param_Flags">Os sinalizadores de configuração de buffer. O chamador pode definir esse parâmetro tanto para 0(Disponivel na enumeração) ou para o seguinte valor de enumeração CA_AUDIOCLIENTE_BUFFERFLAGS (um bit de sinalizador).</param>
			CarenResult ReleaseBuffer(UInt32 Param_NumeroFramesEscritos, Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS Param_Flags);
		};

		/// <summary>
		/// (IAudioCaptureClient) - Interface responsável por permitir que um cliente leia os dados de entrada de um buffer de ponto de extremidade de captura.
		/// Os métodos nesta interface gerenciam o movimento de pacotes de dados que contêm dados de captura. O comprimento de um pacote de dados é expresso como o número de frames audio no pacote. 
		/// O tamanho de um quadro de áudio é especificado pelo AlinhamentoDeBloco(nBlockAlign) membro da estrutura WAVEFORMATEX (ou WAVEFORMATEXTENSIBLE) que o cliente obtém chamando o método 
		/// ICarenAudioClient::GetMixFormat.
		/// O cliente obtém uma referência à interface ICarenAudioCaptureClient de um objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro RIID definido como 
		/// IID_IAudioCaptureClient.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Captura dados da saida do dispositivo de Audio.")]
		[Guid("C7E7CBD3-4090-4C06-BBA8-FD209BD34DA1")]
		public interface class ICarenAudioCaptureClient : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos

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
			CarenResult GetBuffer(
				[Out] ICarenBuffer^% Param_Out_BufferData,
				[Out] UInt32% Param_Out_NumeroFramesLidos,
				[Out] Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS% Param_Out_Flags,
				[Out] UInt64% Param_Out_PosicaoDispositivo,
				[Out] UInt64% Param_Out_QPCPosicao);

			/// <summary>
			/// (GetNextPacketSize) - O método recupera o número de quadros(FRAMES) no próximo pacote de dados no buffer de ponto de extremidade de captura.
			/// </summary>
			/// <param name="Param_Out_FramesProximoPacote">Retorna a quantidade de FRAMES do proximo pacote a ser lido.</param>
			CarenResult GetNextPacketSize([Out] UInt32% Param_Out_FramesProximoPacote);

			/// <summary>
			/// (ReleaseBuffer) - O método libera o espaço de buffer adquirido na chamada anterior para o método ICarenAudioCaptureClient::GetBuffer.
			/// </summary>
			/// <param name="Param_NumeroFramesLidos">O número de quadros de áudio que o cliente ler do buffer de captura. Esse parâmetro deve ser igual ao número de quadros no pacote de dados 
			/// adquirido anteriormente ou 0. O valor desse paramêtro é em (FRAMES).</param>
			CarenResult ReleaseBuffer(UInt32 Param_NumeroFramesLidos);
		};

		/// <summary>
		/// (IAudioClock) - Interface responsável por permitir que um cliente monitore a taxa de dados de um fluxo e a posição atual no fluxo. O cliente obtém uma referência a interface ICarenAudioClock 
		/// de um objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro RIID definido como REFIID IID_IAudioClock.
		/// Ao liberar uma instância da interface ICarenAudioClock, o cliente deve chamar o método (LiberarReferencia) da interface do mesmo thread que a chamada para 
		/// ICarenAudioClient::GetService que criou o objeto.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Monitora a taxa de dados e a posição atual no fluxo.")]
		[Guid("DE941B25-B610-4698-9303-DCBE7D37AE74")]
		public interface class ICarenAudioClock : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos

			/// <summary>
			/// (GetCharacteristics) - Método é reservado para uso futuro.
			/// </summary>
			/// <param name="Param_Out_Caracteristicas">Retorna um valor que indica as características do relógio de áudio.</param>
			CarenResult GetCharacteristics([Out] UInt32% Param_Out_Caracteristicas);

			/// <summary>
			/// (GetFrequency ) - Obtém a frequência do dispositivo.
			/// A frequência do dispositivo é a frequência gerada pelo relógio de hardware no dispositivo de áudio. Esse método informa a frequência do dispositivo em unidades que são compatíveis 
			/// com os da posição do dispositivo que o do método (GetPosition) utiliza.
			/// </summary>
			/// <param name="Param_Out_Frequencia">Retorna o valor da frequência do dispositivo.</param>
			CarenResult GetFrequency([Out] UInt64% Param_Out_Frequencia);

			/// <summary>
			/// (GetPosition) - Obtém a posição do dispositivo atual.
			/// </summary>
			/// <param name="Param_Out_Posicao">Retorna a posição do dispositivo. A posição do dispositivo é o deslocamento do início do fluxo para a posição atual no fluxo. No entanto, as unidades 
			/// em que esse deslocamento é expresso são indefinidas  o valor de posição do dispositivo tem significado somente em relação à frequência relatada pelo método (GetFrequency).</param>
			/// <param name="Param_Out_QPCPosicao">Retorna o valor do contador de desempenho no momento em que o dispositivo de ponto de extremidade de áudio ler a posição do dispositivo 
			/// (Param_Out_Posicao) em resposta a chamada (GetPosition). O método converte o valor do contador para unidades de 100 nanossegundos de tempo antes de escrevê-lo para 
			/// (Param_Out_QPCPosicao).</param>
			CarenResult GetPosition([Out] UInt64% Param_Out_Posicao, [Out] UInt64% Param_Out_QPCPosicao);
		};

		/// <summary>
		/// (IAudioClock2) - Interface responsável por obter a posição atual do dispositivo.
		/// Para obter uma referência para o ICarenAudioClock2 interface, o aplicativo deve chamar ICarenAudioClock::ConsultarInterface para solicitar o ponteiro interface do objeto 
		/// transmitir ICarenAudioClock interface.
		/// O cliente obtém uma referência à interface ICarenAudioClock de um objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro RIID definido como 
		/// REFIID IID_IAudioClock.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Obtém a posição atual do dispositivo.")]
		[Guid("525FB789-3E55-4677-90A0-84E779B9B6F2")]
		public interface class ICarenAudioClock2 : ICarenAudioClock
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos

			/// <summary>
			/// (GetDevicePosition) - O método obtém a posição do dispositivo atual, em quadros(FRAMES), diretamente do hardware.
			/// </summary>
			/// <param name="Param_Out_PosicaoDispositivo">Recebe a posição do dispositivo, em quadros. A posição recebida é um valor não processado que o método obtém diretamente do hardware.</param>
			/// <param name="Param_Out_QPCPosicao">Recebe o valor do contador de desempenho no momento em que o dispositivo de ponto de extremidade de áudio ler a posição do dispositivo recuperada 
			/// no parâmetro Param_Out_PosicaoDispositivo em resposta à chamada (GetDevicePosition).</param>
			CarenResult GetDevicePosition([Out] UInt64% Param_Out_PosicaoDispositivo, [Out] UInt64% Param_Out_QPCPosicao);
		};

		/// <summary>
		/// (IAudioSessionEvents) - Interface responsável por fornecer notificações de eventos relacionados à sessão, como alterações no nível de volume, nome para exibição e estado da sessão. 
		/// Ao contrário das outras interfaces nesta seção, que são implementadas pelo componente de sistema WASAPI, um cliente WASAPI implementa a interface IAudioSessionEvents.
		/// Para receber notificações de evento, o cliente passa um ponteiro para sua interface ICarenAudioSessionEvents para o método ICarenAudioSessionControl::RegisterAudioSessionNotification.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Fornece notificações de eventos relacionados à sessão de áudio.")]
		[Guid("5F54DD3A-B886-4DCA-BB24-10C7A93E2FAE")]
		public interface class ICarenAudioSessionEvents : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates utilizados pela Interface.

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnChannelVolumeChanged(UInt32 Param_QuantidadeCanais, cli::array<float>^ Param_NovoArrayVolumesCanais, UInt32 Param_CanalModificado, String^ Param_ContextoEvento);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnDisplayNameChanged(String^ Param_NovoNomeExibicao, String^ Param_ContextoEvento);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnGroupingParamChanged(String^ Param_GuidParametroAgrupamento, String^ Param_ContextoEvento);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnIconPathChanged(String^ Param_UrlNovoIcone, String^ Param_ContextoEvento);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnSessionDisconnected(Enumeracoes::CA_RAZAO_DESCONEXAO_SESSAO_AUDIO Param_RazaoDesconexao);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnSimpleVolumeChanged(float Param_NovoVolume, Boolean Param_EstadoMudo, String^ Param_ContextoEvento);

			/// <summary>
			/// 
			/// </summary>
			delegate int Delegate_OnStateChanged(Enumeracoes::CA_ESTADO_SESSAO_AUDIO Param_NovoEstadoSessao);




			//Define os eventos

			/// <summary>
			/// O evento notifica o cliente que o nível de volume de um canal de áudio no submix de sessão foi alterado.
			/// </summary>
			event Delegate_OnChannelVolumeChanged^ OnChannelVolumeChanged;

			/// <summary>
			/// O evento notifica o cliente que o nome de exibição para a sessão foi alterado.
			/// </summary>
			event Delegate_OnDisplayNameChanged^ OnDisplayNameChanged;

			/// <summary>
			/// O evento notifica o cliente que o parâmetro de agrupamento para a sessão foi alterado.
			/// </summary>
			event Delegate_OnGroupingParamChanged^ OnGroupingParamChanged;

			/// <summary>
			/// O evento notifica o cliente que o ícone de exibição para a sessão foi alterado.
			/// </summary>
			event Delegate_OnIconPathChanged^ OnIconPathChanged;

			/// <summary>
			/// O evento notifica o cliente que a sessão de áudio foi desconectado.
			/// </summary>
			event Delegate_OnSessionDisconnected^ OnSessionDisconnected;

			/// <summary>
			/// O evento notifica o cliente que o nível de volume ou o estado muting da sessão de áudio foi alterado.
			/// </summary>
			event Delegate_OnSimpleVolumeChanged^ OnSimpleVolumeChanged;

			/// <summary>
			/// O evento notifica o cliente que o estado de atividade de fluxo da sessão foi alterado.
			/// </summary>
			event Delegate_OnStateChanged^ OnStateChanged;





			//Métodos que registram e deletam os dados dos eventos.

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarEventos();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarEventos).
			/// </summary>
			void CancelarRegistro();
		};

		/// <summary>
		/// (IAudioSessionControl) - Interface responsável por permitir que um cliente configure os parâmetros de controle para uma sessão de áudio e para monitorar eventos na sessão.
		/// Essa interface controla uma sessão de áudio. Uma sessão de áudio é uma coleção de fluxos de modo compartilhado. Essa interface não funciona com fluxos de modo (EXCLUSIVO).
		/// O método (ICarenAudioClient::Initialize) inicializa um objeto de fluxo e atribui o fluxo para uma sessão de áudio. O cliente obtém uma referência para o (ICarenAudioSessionControl) 
		/// interface em um objeto de fluxo chamando o ICarenAudioClient::GetService método com o parâmetro RIID definido como IID_IAudioSessionControl.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Controla uma sessão de áudio.")]
		[Guid("525FB789-3E55-4677-90A0-84E779B9B6F2")]
		public interface class ICarenAudioSessionControl : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetDisplayName) - O método recupera o nome de exibição para a sessão de áudio.
			/// Se o cliente não tiver chamado (ICarenAudioSessionControl::SetDisplayName) para definir o nome de exibição, a sequência de caracteres estará vazia. 
			/// </summary>
			/// <param name="Param_Out_Nome">Retorna o nome de exbição da sessão de áudio.</param>
			CarenResult GetDisplayName([Out] String^% Param_Out_Nome);

			/// <summary>
			/// (GetGroupingParam) - O método recupera o parâmetro de agrupamento da sessão de áudio.
			/// </summary>
			/// <param name="Param_Out_GUID">Retorna um GUID do paramêtro de agrupamento.</param>
			CarenResult GetGroupingParam([Out] String^% Param_Out_GUID);

			/// <summary>
			/// (GetIconPath) - O método recupera o caminho para o ícone de exibição para a sessão de áudio.
			/// </summary>
			/// <param name="Param_Out_Url">Retorna o caminho completo completo para o .ico, .exe, .dll que contenha um icone para a sessão de áudio.</param>
			CarenResult GetIconPath([Out] String^% Param_Out_Url);

			/// <summary>
			/// (GetState) - O método recupera o estado atual da sessão de áudio.
			/// </summary>
			/// <param name="Param_Out_Estado">Retorna o estado da sessão de áudio atual.</param>
			CarenResult GetState([Out] Enumeracoes::CA_ESTADO_SESSAO_AUDIO% Param_Out_Estado);

			/// <summary>
			/// (RegisterAudioSessionNotification) - O método registra o cliente para receber notificações de eventos de sessão, incluindo as alterações no estado de fluxo.
			/// </summary>
			/// <param name="Param_Notificador">Ponteiro para uma interface IAudioSessionEvents, implementada pelo cliente. Se o método for bem-sucedido, ele chama o AddRef método na interface do 
			/// cliente IAudioSessionEvents.</param>
			CarenResult RegisterAudioSessionNotification(ICarenAudioSessionEvents^ Param_Notificador);

			/// <summary>
			/// (SetDisplayName) - O método atribui um nome de exibição para a sessão atual.
			/// </summary>
			/// <param name="Param_Nome">O novo nome para exibição da sessão de áudio.</param>
			/// <param name="Param_GuidContextoEvento">Uma string para o evento-contexto GUID. Se uma chamada para esse método gera um evento de alteração de nome, o Gerenciador de sessão envia 
			/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
			/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de ContextoEvento.
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult SetDisplayName(String^ Param_Nome, String^ Param_GuidContextoEvento);

			/// <summary>
			/// (SetGroupingParam) - O método atribui uma sessão a um agrupamento de sessões.
			/// </summary>
			/// <param name="Param_GuidNovoParametro">O novo GUID para o parâmetro de agrupamento.</param>
			/// <param name="Param_ContextoEvento">Uma string com o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de agrupamento, o Gerenciador de sessão 
			/// envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
			/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult SetGroupingParam(String^ Param_GuidNovoParametro, String^ Param_ContextoEvento);

			/// <summary>
			/// (SetIconPath) - O método atribui um ícone de exibir para a sessão atual.
			/// </summary>
			/// <param name="Param_UrlCompletaIco">Sequência de caracteres largos que especifica o caminho e nome de arquivo de um arquivo .ico, .dll ou .exe que contém o ícone.</param>
			/// <param name="Param_ContextoEvento">Uma string para o GUID do (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de ícone, o Gerenciador de sessão envia 
			/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) com 
			/// cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro,
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult SetIconPath(String^ Param_UrlCompletaIco, String^ Param_ContextoEvento);

			/// <summary>
			/// (UnregisterAudioSessionNotification) - O método exclui um registro anterior pelo cliente para receber notificações.
			/// </summary>
			/// <param name="Param_Notificador">Ponteiro para a interface IAudioSessionEvents implementada pelo cliente. O cliente passou esse mesmo ponteiro de interface para o Gerenciador de sessão 
			/// em uma chamada anterior para o método ICarenAudioSessionControl::RegisterAudioSessionNotification. Se o (UnregisterAudioSessionNotification) método for bem-sucedido, ele chama o 
			/// método Release na interface IAudioSessionEvents do cliente.</param>
			CarenResult UnregisterAudioSessionNotification(ICarenAudioSessionEvents^% Param_Notificador);
		};

		/// <summary>
		/// (ISimpleAudioVolume) - Interface responsável por permitir que um cliente controle o nível de volume mestre de uma sessão de áudio.
		/// O cliente obtém uma referência à interface ICarenSimpleAudioVolume em um objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro riid definido como REFIID 
		/// IID_ISimpleAudioVolume.
		/// Como alternativa, um cliente pode obter a interface ICarenSimpleAudioVolume de uma sessão existente sem ter que primeiro criar um objeto de fluxo e adicionar o fluxo para a sessão.
		/// Em vez disso, o cliente chama o método ICarenAudioSessionManager::ObterAudioSimplesVolume com a sessão GUID.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Permite que um cliente controle o nível de volume mestre de uma sessão de áudio.")]
		[Guid("933A6F1F-5FF4-4143-9073-EF71819CE384")]
		public interface class ICarenSimpleAudioVolume : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetMasterVolume) - O método recupera o nível de volume do cliente para a sessão de áudio.
			/// </summary>
			/// <param name="Param_Out_NivelVolume">Retorna uma variável no qual o método grava o nível de volume do cliente. O nível de volume é um valor no intervalo de 0.0 a 1.0.</param>
			CarenResult GetMasterVolume([Out] float% Param_Out_NivelVolume);

			/// <summary>
			/// (GetMute) - O método recupera o atual muting estado para a sessão de áudio.
			/// </summary>
			/// <param name="Param_Out_EstadoMudo">Retorna uma variável no qual o método grava o estado (MUTING). True indica que o (MUTING) está habilitado. False indica que ele está desabilitado.</param>
			CarenResult GetMute([Out] Boolean% Param_Out_EstadoMudo);

			/// <summary>
			/// (SetMasterVolume) - O método define o nível de volume principal para a sessão de áudio.
			/// </summary>
			/// <param name="Param_NivelVolume">O novo nível de volume mestre. Os níveis de volume válidos estão no intervalo 0.0 a 1.0.</param>
			/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume, o Gerenciador de 
			/// sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
			/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult SetMasterVolume(float Param_NivelVolume, String^ Param_ContextoEvento);

			/// <summary>
			/// (SetMute) - O método define o estado muting para a sessão de áudio.
			/// </summary>
			/// <param name="Param_EstadoMudo">O novo valor para o estado mudo(MUTING). True habilita o muting. False desabilita muting.</param>
			/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume, o Gerenciador de 
			/// sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
			/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult SetMute(Boolean Param_EstadoMudo, String^ Param_ContextoEvento);
		};

		/// <summary>
		/// (IChannelAudioVolume) - Interface responsável por permitir que um cliente controle e monitore os níveis de volume para todos os canais na sessão de áudio que pertence o fluxo. 
		/// Esta é a sessão que o cliente atribuiu o fluxo durante a chamada para o método ICarenAudioClient::Initialize. O cliente obtém uma referência à interface ICarenChannelAudioVolume em um 
		/// objeto de fluxo chamando o método ICarenAudioClient::GetService com o parâmetro RIID definido como IID_IChannelAudioVolume.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Permite que um cliente controle e monitore os níveis de volume para todos os canais.")]
		[Guid("9ADFEBCF-FED0-4AB3-9F00-CF6B63D04C32")]
		public interface class ICarenChannelAudioVolume : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetAllVolumes) - O método recupera os níveis de volume para todos os canais na sessão de áudio.
			/// </summary>
			/// <param name="Param_QuantidadeCanais">A quantidade de canais no formato do fluxo. Chame o método (ObterQuantidadeCanais) para obter a quantidade total.</param>
			/// <param name="Param_Out_ArrayVolumes">Retorna um array que contém o nivel de volume de cada canal na sessão de áudio. Os níveis de volume estão no intervalo 0,0 a 1,0.</param>
			CarenResult ObterTodosVolumes(UInt32 Param_QuantidadeCanais, [Out] cli::array<float>^% Param_Out_ArrayVolumes);

			/// <summary>
			/// (GetChannelCount) - O método recupera o número de canais no formato de fluxo para a sessão de áudio.
			/// </summary>
			/// <param name="Param_QuantidadeCanais">Retorna a quantidade de canais.</param>
			CarenResult ObterQuantidadeCanais([Out] UInt32% Param_QuantidadeCanais);

			/// <summary>
			/// (GetChannelVolume) - O método recupera o nível de volume para o canal especificado na sessão de áudio.
			/// </summary>
			/// <param name="Param_NumeroCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N 1.</param>
			/// <param name="Param_Out_NivelVolume">Retorna uma variável no qual o método grava o nível de volume do canal especificado. O nível de volume está no intervalo de 0.0 a 1.0.</param>
			CarenResult ObterVolumeCanal(UInt32 Param_NumeroCanal, [Out] float% Param_Out_NivelVolume);

			/// <summary>
			/// (SetAllVolumes) - O método define os níveis de volume individuais para todos os canais na sessão de áudio.
			/// </summary>
			/// <param name="Param_QuantidadeItens">A quantidade de itens no array(Param_ArrayVolumes).</param>
			/// <param name="Param_ArrayVolumes">Um array que contém o nivel de volume para cada canal do fluxo na sessão de áudio.</param>
			/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume de canal, o Gerenciador 
			/// de sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
			/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult DefinirTodosVolumes(UInt32 Param_QuantidadeItens, cli::array<float>^ Param_ArrayVolumes, String^ Param_ContextoEvento);

			/// <summary>
			/// (SetChannelVolume) - O método define o nível de volume para o canal especificado na sessão de áudio.
			/// </summary>
			/// <param name="Param_IndexCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N 1.</param>
			/// <param name="Param_Volume">O novo nivel de volume que será definido ao canal.</param>
			/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume de canal, o Gerenciador 
			/// de sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
			/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
			/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
			/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
			CarenResult DefinirVolumeCanal(UInt32 Param_IndexCanal, float Param_Volume, String^ Param_ContextoEvento);
		};

		/// <summary>
		/// (IAudioSessionManager) - Interface responsável por permitir que um cliente acessar os controles de sessão e controles de volume para ambas as sessões de áudio de processo e processo 
		/// específico. O cliente obtém uma referência a uma interface ICarenAudioSessionManager chamando o método ICarenMMDevice::Ativar com o parâmetro IID definido como 
		/// REFIID IID_IAudioSessionManager.
		/// Essa interface permite que os clientes acessem os controles para uma sessão existente sem primeiro abrir um fluxo. Esse recurso é útil para clientes de APIs de nível superior que são 
		/// criados na parte superior do WASAPI e usam controles de sessão internamente, mas não dão a seus clientes acesso a controles de sessão.
		/// </summary>
		[CategoryAttribute("Interface WASAPI")]
		[DescriptionAttribute("Permite ao cliente acessar os controles de sessão e controles de volume.")]
		[Guid("14BBF8B3-68FE-42A5-8E3E-D0576F4BBA26")]
		public interface class ICarenAudioSessionManager : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetAudioSessionControl) - O método recupera um controle de sessão de áudio.
			/// </summary>
			/// <param name="Param_GuidSessaoAudio">Uma string que contém o GUID da sessão de áudio. Se o GUID não identificar uma sessão que foi aberta anteriormente, a chamada abrirá uma 
			/// sessão nova, mas vazia. Se este parâmetro for NULO, o método atribui o fluxo para a sessão padrão.</param>
			/// <param name="Param_FlagsFluxo">Especifica o status dos sinalizadores para o fluxo de áudio.</param>
			/// <param name="Param_Out_ControleSessaoAudio">Retorna a interface de controle de sessão de áudio. O chamador é responsável por liberar a interface, quando ela não é 
			/// mais necessária</param>
			CarenResult ObterAudioControleSessao(String^ Param_GuidSessaoAudio, UInt32 Param_FlagsFluxo, [Out] ICarenAudioSessionControl^% Param_Out_ControleSessaoAudio);

			/// <summary>
			/// (GetSimpleAudioVolume) - O método recupera um controle de volume de áudio simples.
			/// </summary>
			/// <param name="Param_GuidSessaoAudio">Uma string que contém o GUID da sessão de áudio. Se o GUID não identificar uma sessão que foi aberta anteriormente, a chamada abrirá uma 
			/// sessão nova, mas vazia. Se este parâmetro for NULO, o método atribui o fluxo para a sessão padrão.</param>
			/// <param name="Param_FlagsFluxo">Especifica se a solicitação é para uma sessão de processo cruzado. Definido como TRUE(1) se a sessão é processo cruzado. Definido como FALSE(0) se a 
			/// sessão não é processo cruzado.</param>
			/// <param name="Param_Out_ControladorSimplesVolume">Retorna a interface de controle de volume áudio. Essa interface representa o controle de volume de áudio simples para o processo atual. O chamador é responsável por 
			/// liberar a interface, quando ela não é mais necessária.</param>
			CarenResult ObterAudioSimplesVolume(String^ Param_GuidSessaoAudio, UInt32 Param_FlagsFluxo, [Out] ICarenSimpleAudioVolume^% Param_Out_ControladorSimplesVolume);
		};




		



		//////////////////////////////////////
		// Multimedia Device (MMDevice) API //
		//////////////////////////////////////


		/// <summary>
		/// (IMMDevice) - Interface responsável por encapsular as características genéricas de um recurso de multimídia do dispositivo.
		/// Na implementação atual da API MMDevice, suporta apenas a enumeração de dispositios de audio de ponto de extremidade.
		/// </summary>
		[CategoryAttribute("Interface MMDevice")]
		[DescriptionAttribute("Responsável por encapsular as caracteristicas de recursos multimedia.")]
		[Guid("B7FD481F-1413-47F9-887D-3D78E98AAEC8")]
		public interface class ICarenMMDevice : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos


			/// <summary>
			/// (Activate) - O método cria um objeto da interface especificada.
			/// </summary>
			/// <param name="Param_GuidInterface">O identificador de interface. Este parâmetro é uma referência a um GUID que identifica a interface que as solicitações chamador ser ativado. O chamador usará essa 
			/// interface para se comunicar com o objeto COM.</param>
			/// <param name="Param_ContextoEx">O contexto de execução no qual o código que gerencia o objeto recém-criado será executado. O chamador pode restringir o contexto, definindo esse parâmetro para o bit 
			/// ou de um ou mais CLSCTX valores de enumeração. Como alternativa, o cliente pode evitar impor quaisquer restrições de contexto especificando CLSCTX_ALL.</param>
			/// <param name="Param_ParmetrosActive">Definido como nulo para ativar um IAudioClient, IAudioEndpointVolume, IAudioMeterInformation, IAudioSessionManager, ou IDeviceTopology interface em um dispositivo 
			/// de ponto de extremidade de áudio. </param>
			/// <param name="Param_Out_InterfaceRequisitada">Recebe a interface requisitada. Por meio desse método, o chamador obtém uma referência contada para a interface. O chamador é responsável por liberar a 
			/// interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
			CarenResult AtivarObjeto(String^ Param_GuidInterface, Enumeracoes::CA_CLSCTX Param_ContextoEx, Estruturas::CA_PropVariant^ Param_ParmetrosActive, ICaren^ Param_Out_InterfaceRequisitada);

			/// <summary>
			/// (GetId) - O método recupera uma cadeia de caracteres de ID de ponto de extremidade que identifica o dispositivo de ponto de extremidade de áudio.
			/// </summary>
			/// <param name="Param_Out_EndpointId">Retorna o endereço de uma sequência de caracteres largos terminada por caractere nulo que contém o ID do dispositivo de ponto 
			/// de extremidade.</param>
			CarenResult ObterId([Out] String^% Param_Out_EndpointId);

			/// <summary>
			/// (GetState) - O método recupera o estado atual do dispositivo.
			/// </summary>
			/// <param name="Param_Out_EstadoDispositivo">Retorna o estado do dispositivo atual.</param>
			CarenResult GetState([Out] Enumeracoes::CA_DEVICE_STATE_XXX% Param_Out_EstadoDispositivo);

			/// <summary>
			/// (OpenPropertyStore) - O método recupera uma interface para o armazenamento de Propriedade do dispositivo.
			/// </summary>
			/// <param name="Param_TipoAcesso">O modo de acesso de armazenamento. Este parâmetro especifica se deve abrir o armazenamento de propriedade no modo de leitura, modo de gravação ou modo de 
			/// leitura/gravação.</param>
			/// <param name="Param_Out_Store">Rece uma interface que contém o armazenamento de propriedades do dispositivo. O chamador é responsável por liberar a interface, quando ele não é mais necessário, 
			/// chamando o método de Release da interface.</param>
			CarenResult AbrirPropertyStore(Enumeracoes::CA_STGMs Param_TipoAcesso, [Out] ICarenPropertyStore^% Param_Out_Store);
		};

		/// <summary>
		/// (IMMDeviceCollection) - Interface responsável por conter uma coleção de recursos de multimídia do dispositivo.
		/// Na implementação atual da API MMDevice, suporta apenas a enumeração de dispositios de audio de ponto de extremidade.
		/// </summary>
		[CategoryAttribute("Interface MMDevice")]
		[DescriptionAttribute("Contém uma colecação de dispositivos de audio.")]
		[Guid("71718D05-C46B-4543-B2FA-38C8BD603493")]
		public interface class ICarenMMDeviceCollection : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (GetCount) - O método recupera uma contagem dos dispositivos na coleção de dispositivo.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de dispositivos na coleção.</param>
			CarenResult ObterQuantidade([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (Item) - O método recupera um ponteiro para o item especificado na coleção de dispositivos.
			/// </summary>
			/// <param name="Param_IdDispositivo">O Id do disposito na coleção a ser obtido.</param>
			/// <param name="Param_Out_Dispositivo">Retorna o dispositivo solicitado no id especificado. Por meio desse método, o chamador obtém uma referência contada para a interface. O chamador é responsável 
			/// por liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
			CarenResult Item(UInt32 Param_IdDispositivo, [Out] ICarenMMDevice^% Param_Out_Dispositivo);
		};

		/// <summary>
		/// (IMMNotificationClient) - interface fornece notificações quando um dispositivo de ponto de extremidade de áudio é adicionado ou removido, quando o estado ou propriedades de um dispositivo de ponto de 
		/// extremidade alterar, ou quando há uma alteração na função padrão atribuída a um ponto de extremidade Dispositivo. Ao contrário das outras interfaces nesta seção, que são implementadas pelo componente de 
		/// sistema da API MMDevice, um cliente de API MMDevice implementa a interface ICarenMMNotificationClient.
		/// </summary>
		[CategoryAttribute("Interface MMDevice")]
		[DescriptionAttribute("Notificação de dispositivos de audio.")]
		[Guid("A9336FC5-E130-4300-81FC-3421A7D22C57")]
		public interface class ICarenMMNotificationClient : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates utilizados pela Interface.

			/// <summary>
			/// 
			/// </summary>
			delegate void Delegate_OnDefaultDeviceChanged(Enumeracoes::CA_EDataFlow Param_DirecaoFluxo, Enumeracoes::CA_ERole Param_FuncaoDispositivo, String^ Param_IdDispositivo);

			/// <summary>
			/// 
			/// </summary>
			delegate void Delegate_OnDeviceAdded(String^ Param_IdDispositivo);

			/// <summary>
			/// 
			/// </summary>
			delegate void Delegate_OnDeviceRemoved(String^ Param_IdDispositivo);

			/// <summary>
			/// 
			/// </summary>
			delegate void Delegate_OnDeviceStateChanged(String^ Param_IdDispositivo, Enumeracoes::CA_DEVICE_STATE_XXX Param_EstadoDispositivoAtual);

			/// <summary>
			/// 
			/// </summary>
			delegate void Delegate_OnPropertyValueChanged(String^ Param_IdDispositivo, Estruturas::CA_PROPERTYKEY^ Param_KeyPropriedade);


			//Define os eventos

			/// <summary>
			/// O evento notifica o cliente que o dispositivo de ponto de extremidade de áudio padrão para uma função de dispositivo específico foi alterado.
			/// </summary>
			event Delegate_OnDefaultDeviceChanged^ OnDefaultDeviceChanged;

			/// <summary>
			/// O evento notifica que um novo dispositivo de ponto de extremidade de áudio foi adicionado.
			/// </summary>
			event Delegate_OnDeviceAdded^ OnDeviceAdded;

			/// <summary>
			/// O evento notifica que um dispositivo de ponto de extremidade de áudio foi removido.
			/// </summary>
			event Delegate_OnDeviceRemoved^ OnDeviceRemoved;

			/// <summary>
			/// O evento notifica que o estado de um dispositivo de ponto de extremidade de áudio foi alterado.
			/// </summary>
			event Delegate_OnDeviceStateChanged^ OnDeviceStateChanged;

			/// <summary>
			/// O evento notifica que o valor de uma propriedade pertencente a um dispositivo de ponto de extremidade de áudio foi alterado.
			/// </summary>
			event Delegate_OnPropertyValueChanged^ OnPropertyValueChanged;





			//Métodos que registram e deletam os dados dos eventos.

			/// <summary>
			/// Método responsável por registrar os eventos da interface.
			/// </summary>
			void RegistrarCallback();

			/// <summary>
			/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
			/// </summary>
			void UnRegisterCallback();
		};

		/// <summary>
		/// (IMMDeviceEnumerator) - Interface responsável por enumerar os recursos de multimedia do dispositivo.
		/// Na implementação atual da API MMDevice, suporta apenas a enumeração de dispositios de audio de ponto de extremidade. 
		/// </summary>
		[CategoryAttribute("Interface MMDevice")]
		[DescriptionAttribute("Enumera recursos de multimedia do dispositivo de Audio.")]
		[Guid("EF8A8894-93C7-42D2-B629-D8C7696844A2")]
		public interface class ICarenMMDeviceEnumerator : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// (EnumAudioEndpoints) - O método gera uma coleção de dispositivos de ponto de extremidade de áudio que atendem aos critérios especificados.
			/// </summary>
			/// <param name="Param_DireçãoFluxo">A direção do fluxo de dados para os dispositivos de ponto de extremidade na coleção. Se o chamador especifica eAll, o método inclui os pontos de extremidade de 
			/// renderização e captura na coleção.</param>
			/// <param name="Param_EstadosPontoExtremidade">O estado ou Estados dos pontos de extremidade que devem ser incluídos na coleção. O chamador deve definir esse parâmetro para o bit a OR de um ou mais da
			/// enumeração.</param>
			/// <param name="Param_Out_ColeçãoDispotivios">Recebe a coleção de dispositivos solicitados. Por meio desse método, o chamador obtém uma referência contada para a interface. O chamador é responsável por 
			/// liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
			CarenResult ObterColeçãoDispositivosAudio(
				Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
				Enumeracoes::CA_DEVICE_STATE_XXX Param_EstadosPontoExtremidade,
				[Out] ICarenMMDeviceCollection^% Param_Out_ColeçãoDispotivios);

			/// <summary>
			/// (GetDefaultAudioEndpoint) - O método recupera o ponto de extremidade de áudio padrão para a direção de fluxo de dados especificado e a função.
			/// </summary>
			/// <param name="Param_DireçãoFluxo">A direção de fluxo de dados para o dispositivo de ponto de extremidade.</param>
			/// <param name="Param_FunçãoDispositivo">A direção do fluxo de dados para um dispositivo de renderização é eRender. A direção do fluxo de dados para um dispositivo de captura é eCapture.</param>
			/// <param name="Param_Out_DispositivoDefault">Retorna o dispositivo de Audio padrão do sistema de acordo com sua função e direção.</param>
			CarenResult ObterDispositivoAudioDefault(
				Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
				Enumeracoes::CA_ERole Param_FunçãoDispositivo,
				[Out] ICarenMMDevice^% Param_Out_DispositivoDefault);

			/// <summary>
			/// (GetDevice) - O método recupera um dispositivo de ponto de extremidade de áudio que é identificado por uma cadeia de caracteres de ID de ponto de extremidade.
			/// </summary>
			/// <param name="Param_IDPontoExtremidade">Ponteiro para uma seqüência de caracteres que contém o ID de ponto de extremidade. O chamador normalmente obtém essa seqüência de caracteres a partir de 
			/// ICarenMMDevice::ObterId método ou de um dos métodos na ICarenMMNotificationClient interface.</param>
			/// <param name="Param_Out_DispositivoSolicitado">Recebe um ponteiro para a interface do dispositivo solicitado. Por meio desse método, o chamador obtém uma referência contada para a interface. 
			/// O chamador é responsável por liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface.</param>
			CarenResult ObterDispositivo(String^ Param_IDPontoExtremidade, [Out] ICarenMMDevice^% Param_Out_DispositivoSolicitado);

			/// <summary>
			/// (RegisterEndpointNotificationCallback) - O método registra a interface de retorno de chamada de notificação do cliente.
			/// </summary>
			/// <param name="Param_Cliente">A interface que será registrada para receber as notificações.</param>
			CarenResult RegistrarInterfaceNotificação(ICarenMMNotificationClient^ Param_Cliente);

			/// <summary>
			/// (UnregisterEndpointNotificationCallback) - O método exclui o registro de uma interface de notificação que o cliente registrado em uma chamada anterior para o IMMDeviceEnumerator:: RegisterEndpointNotificationCallback método.
			/// </summary>
			/// <param name="Param_Cliente">A interface que será removida para não receber mais notificações.</param>
			CarenResult RemoverRegistroInterfaceNotificação(ICarenMMNotificationClient^ Param_Cliente);
		};









		////////////////////////
		// EndpointVolume API //
		////////////////////////
	}
}