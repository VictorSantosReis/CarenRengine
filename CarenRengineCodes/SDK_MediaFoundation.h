﻿/*
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


//////////////////////////////////////
// MFT - MICROSOFT MEDIA FOUNDATION //
//////////////////////////////////////

//Namespace principal do sistema.
namespace CarenRengine
{
	//Namespace da API do SDK.
	namespace MediaFoundation
	{
		/// <summary>
		/// (IMFGetService) - Está interface é responsável por consultar e obter um ponteiro para um serviço exposto pelo objeto a qual foi chamado.
		/// Um serviço é uma interface que é exposta por um objeto, mas pode ser implementada por outro objeto. O método (ObterServiço) é equivalente a (ConsultarInterface), 
		/// com a seguinte diferença: quando (ConsultarInterface) recupera um ponteiro para uma interface, é garantido que você pode consultar a interface e voltar a interface original. 
		/// O método GetService não faz esta garantia, porque a interface obtida pode ser implementada por um objeto separado.
		/// </summary>
		[CategoryAttribute("IMFGetService - Consultar objetos em interfaces")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFGetService.")]
		[Guid("7BF636C4-5B5C-4304-BAA1-86B712DEE90A")]
		public interface class ICarenMFGetService : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			/// <summary>
			/// (GetService) - Método responsável por consultar e obter um determinado serviço(Interface) em um Componente especificado.
			/// Pode retornar: SS_OK ou ER_SERVIÇO_NAO_SUPORTADO
			/// </summary>
			/// <param name="Param_SID">O GUID que expõe o (Identificador de Serviço) do serviço a ser obtido. Acesse (GUIDs_MFInterfacesServico) para obter esse GUID.</param>
			/// <param name="Param_IIDInterface">Define o GUID da interface que se quer obter do serviço solicitado.</param>
			/// <param name="Param_Out_InterfaceSolicitada">Retorna a interface solicitada se o método tiver sido bem sucedido. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterServiço(String^ Param_SID, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);
		};

		/// <summary>
		/// (IMFCollection) - Classe responsável por representar uma coleção genérica de ponteiros desconhecidos.
		/// </summary>
		[CategoryAttribute("Coleção - Armazena uma coleção de ponteiros.")]
		[DescriptionAttribute("Interface responsável por expor métodos da IMFCollection.")]
		[Guid("4C627299-4D4A-4948-BF0D-DA88D7A81AC0")]
		public interface class ICarenMFCollection : ICaren
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
			/// (AddElement) - Adiciona um objeto à coleção.
			/// </summary>
			/// <param name="Param_Elemento">O ponteiro a ser adicionado a coleção.</param>
			CarenResult AdicionarElemento(ICaren^ Param_Elemento);

			/// <summary>
			/// (GetElement) - Recupera um objeto na coleção. Este método não remove o objeto da coleção.
			/// </summary>
			/// <param name="Param_IndexElemento">O index do elemento a ser obtido.</param>
			/// <param name="Param_Out_Elemento">Retorna um ponteiro para o elemento especificado. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterElemento(UInt32 Param_IndexElemento, ICaren^ Param_Out_Elemento);

			/// <summary>
			/// (GetElementCount) - Obtém a quantidade de elementos na coleção.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de elementos.</param>
			CarenResult ObterQuantidadeElementos([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (InsertElementAt) - Adiciona um objeto no índice especificado na coleção.
			/// </summary>
			/// <param name="Param_Indice">O (Indice) onde será adicionado o elemento.</param>
			/// <param name="Param_Elemento">O objeto a ser inserido na coleção.</param>
			CarenResult InserirElemento(UInt32 Param_Indice, ICaren^ Param_Elemento);

			/// <summary>
			/// (RemoveAllElements) - Remove todos os itens da coleção.
			/// </summary>
			CarenResult RemoverTodosElementos();

			/// <summary>
			/// (RemoveElement) - Remove um objeto da coleção.
			/// </summary>
			/// <param name="Param_Indice">O (Indice) para o elemento que será removido da coleção.</param>
			/// <param name="Param_Out_Elemento">Recebe um ponteiro para o elemento removido da lista. O chamado que deve liberar
			/// a referência para o ponteiro. Esse parametro pode retornar NULO. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult RemoverElemento(UInt32 Param_Indice, ICaren^ Param_Out_Elemento);
		};

		/// <summary>
		/// (IMFMediaSinkPreroll) -  Falta documentar.
		/// </summary>
		[CategoryAttribute("IMFMediaSinkPreroll - Notifica o coletor para armazenar amostras de midia antes do relogio de apresentação começar.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaSinkPreroll.")]
		[Guid("CE735A9F-4B0C-4725-AD46-B0AEC9FD1172")]
		public interface class ICarenMFMediaSinkPreroll : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// (NotifyPreroll) - Notifica o coletor de mídia(ICarenMFMediaSink) que o relógio de apresentação está prestes a iniciar.
			/// </summary>
			/// <param name="Param_ProximaHoraInicio">A próxima hora de início para o relógio de apresentação, em unidades 100 nanosegundos. Este tempo é o mesmo valor que será dado ao método 
			/// (ICarenMFPresentationClock.Iniciar) quando o relógio de apresentação é iniciado.</param>
			CarenResult NotificarPreroll(Int64 Param_ProximaHoraInicio);
		};

		/// <summary>
		/// (IMFDXGIBuffer) - Interface responsável por representar um buffer que contém uma superfície DXGI(Microsoft DirectX Graphics Infrastructure).
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFDXGIBuffer")]
		[Guid("056177DE-2F4B-44BD-AA80-FEAA66638B37")]
		public interface class ICarenMFDXGIBuffer : ICaren
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
			/// (GetResource) - Consulta a superfície do Microsoft DirectX Graphics infra-estrutura (DXGI) para uma interface.
			/// Você pode usar esse método para obter um ponteiro para a interface de ID3D11Texture2D da superfície. Se o buffer estiver bloqueado, o método retorna ER_MF_REQUISICAO_INVALIDA.
			/// </summary>
			/// <param name="Param_Guid">O identificador de interface (IID) da interface requisitada.</param>
			/// <param name="Param_Out_InterfaceRecurso">Recebe um ponteiro para a interface. O chamador deve liberar a interface. O Usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterRecurso(String^ Param_Guid, ICaren^ Param_Out_InterfaceRecurso);

			/// <summary>
			/// (GetSubresourceIndex) - Obtém o índice do sub-recurso que está associado com esse buffer de mídia.
			/// </summary>
			/// <param name="Param_Out_SubResourceId">Recebe o índice baseado em zero do sub-recurso.</param>
			CarenResult ObterSubRecursoId([Out] UInt32% Param_Out_SubResourceId);

			/// <summary>
			/// (GetUnknown) - Obtém um ponteiro IUnknown que anteriormente foi armazenado no objeto de reserva de meios de comunicação.
			/// </summary>
			/// <param name="Param_GuidInterface">O identificador do ponteiro IUnknown.</param>
			/// <param name="Param_IID">O identificador de interface (IID) da interface requisitada.</param>
			/// <param name="Param_Out_InterfaceRequisitada">Recebe um ponteiro para a interface. O chamador deve liberar a interface.</param>
			CarenResult ObterPonteiroDesconhecido(String^ Param_GuidInterface, String^ Param_IID, ICaren^ Param_Out_InterfaceRequisitada);

			/// <summary>
			/// (SetUnknown) - Armazena um ponteiro IUnknown arbitrário em objeto de reserva de meios de comunicação. 
			/// </summary>
			/// <param name="Param_GuidInterface">O identificador para o ponteiro IUnknown. Esse identificador é usado como uma chave para recuperar o valor. Pode ser qualquer valor GUID.</param>
			/// <param name="Param_Interface">Um ponteiro para a interface IUnknown. Defina este parâmetro como NULO para limpar um ponteiro que foi previamente definido.</param>
			CarenResult DefinirPonteiroDesconhecido(String^ Param_GuidInterface, ICaren^ Param_Interface);
		};

		/// <summary>
		/// (IMFDXGIDeviceManager) - Permite que dois segmentos compartilhem o mesmo dispositivo Microsoft Direct3D 11. Está interface é utilizada para armazenar o ponteiro para o 
		/// Dispositivo Direct3D utilizado para habilitar o DXVA2.
		/// </summary>
		[CategoryAttribute("IMFDXGIDeviceManager  - Acesso ao DXVA (DirectX Video Acceleration)")]
		[Guid("1E2795CA-AC98-4481-A387-69AE862DB9CA")]
		public interface class ICarenMFDXGIDeviceManager : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// Fecha um identificador de dispositivo Direct3D.
			/// Chame o método quando você tiver chamado o método (AbirIdentificadorDispositivo3D).
			/// </summary>
			/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
			CarenResult FecharHandleDispositivo(IntPtr Param_Identificador);

			/// <summary>
			/// Obtém uma interface de serviço de aceleração de vídeo DirectX (DXVA).
			/// Obtenha o IID atravez da estrutura: GUIDs_MFDXVAInterfaces.
			/// </summary>
			/// <param name="Param_HandleDirect3D">Um identificador para um dispositivo Direct3D. Para obter um identificador dispositivo, chame o método: AbirIdentificadorDispositivo3D</param>
			/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Esse método suporta as seguintes interfaces: ID3D11Device, ID3D11VideoDevice</param>
			/// <param name="Param_Out_InterfaceSolicitada">Retorna a interface solicitada se o método tiver sido bem sucedido. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterVideoServiço(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

			/// <summary>
			/// Obtém acesso exclusivo ao dispositivo Direct3D.
			/// </summary>
			/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: AbirIdentificadorDispositivo3D</param>
			/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
			/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
			/// <param name="Param_IIDInterface">O identificador de interface (IID) da interface solicitada. O dispositivo Direct3D apoiará as seguintes interfaces: ID3D11Device, ID3D11VideoDevice, ID3D11VideoContext</param>
			/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface solicitada. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult LockDispositivo(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

			/// <summary>
			/// Obtém um identificador para o dispositivo Direct3D.
			/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (FecharHandleDispositivo) para finalizar.
			/// </summary>
			/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
			CarenResult AbirIdentificadorDispositivo3D([Out] IntPtr% Param_Out_Handle);

			/// <summary>
			/// Define o dispositivo Microsoft Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado..
			/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método, passando a interface (ICarenD3D11Device) do dispositivo Direct3D 11. 
			/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
			/// </summary>
			/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
			/// <param name="Param_Token">Token recebido no parâmetro Param_Out_ResetToken na criação deste gerenciador.</param>
			CarenResult ResetarDispositivo(ICaren^ Param_Dispostivo3D, UInt32 Param_Token);

			/// <summary>
			/// Testa se um identificador de dispositivo Direct3D é válido.
			/// Se o método retorna ER_MF_DXGI_HANDLE_INVALIDA, chame o método (FecharHandleDispositivo) para fechar o identificador e, em seguida, 
			/// chame (AbirIdentificadorDispositivo3D) novamente para obter um novo identificador. O método (ResetarDispositivo), invalida todos os identificadores de dispositivo aberto.
			/// </summary>
			/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: AbirIdentificadorDispositivo3D</param>
			CarenResult TestarIdentificadorDispositivo(IntPtr Param_HandleDispositivo3D);

			/// <summary>
			/// Desbloqueia o dispositivo Direct3D.
			/// </summary>
			/// <param name="Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: AbirIdentificadorDispositivo3D</param>
			/// <param name="Param_SalvarEstadoDispositivo">Define se deve salvar o estado do dispositivo.</param>
			CarenResult UnlockDispositivo(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo);
		};

		/// <summary>
		/// (IMFClock) - Fornece informações de temporização de um relógio no Microsoft Media Foundation.
		/// </summary>
		[CategoryAttribute("IMFClock - Informações de temporização.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFClock.")]
		[Guid("8CE7A5EE-9C2F-40C3-A394-CE0C542696FC")]
		public interface class ICarenMFClock : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}



			/// <summary>
			/// Recupera as características do relógio.
			/// </summary>
			/// <param name="Param_Out_CaracteristicasClock">Recebe os flags com as características do relógio.</param>
			CarenResult RecuperarCaracteristicas([Out] Enumeracoes::CA_CLOCK_CARACTERISTICAS% Param_Out_CaracteristicasClock);

			/// <summary>
			/// (Não Suportado Nativamente) - Recupera a chave de continuidade do relógio.
			/// </summary>
			/// <param name="Param_Out_Chave">Recebe a chave de continuidade.</param>
			CarenResult RecuperarChaveContinuidade([Out] UInt32% Param_Out_Chave);

			/// <summary>
			/// Recupera a hora do último relógio que foi correlacionada com a hora do sistema.
			/// </summary>
			/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
			/// <param name="Param_Out_ClockTime">Recebe o último tempo de relógio conhecido, em unidades de freqüência do relógio.</param>
			/// <param name="Param_Out_NsSystemTime">Recebe a hora do sistema que corresponde ao tempo de relógio retornado em Param_Out_ClockTime, em unidades de 100 nanosegundos.</param>
			CarenResult ObterHoraCorrelacionada(UInt32 Param_ValorReservado, [Out] Int64% Param_Out_ClockTime, [Out] Int64% Param_Out_NsSystemTime);

			/// <summary>
			/// Recupera as propriedades do relógio.
			/// </summary>
			/// <param name="Param_Out_PropriedadesRelogio">Retorna a estrutura que contém as propriedades do relógio atual.</param>
			CarenResult ObterPropriedades([Out] Estruturas::CA_RELOGIO_PROPRIEDADES^% Param_Out_PropriedadesRelogio);

			/// <summary>
			/// Recupera o estado atual do relógio.
			/// </summary>
			/// <param name="Param_ValorReservado">Valor reservado. Deve ser zero.</param>
			/// <param name="Param_Out_EstadoRelogio">Retorna o valor da enumeração que define o estado atual do relógio.</param>
			CarenResult ObterEstado(UInt32 Param_ValorReservado, [Out] Enumeracoes::CA_CLOCK_ESTADO% Param_Out_EstadoRelogio);
		};

		/// <summary>
		/// (IMFPresentationTimeSource) - Interface responsável por fornecer os tempos de relógio para o Tempo de apresentação(ICarenRelogioApresentaçãoMidia).
		/// Essa é a interface que retorna o relogio real para as interfaces de tempo.
		/// O relógio real é dado pela interface IMFClock -> ICarenMFClock.
		/// </summary>
		[CategoryAttribute("IMFPresentationTimeSource  - Fornece o tempo real do relógio.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFPresentationTimeSource.")]
		[Guid("93D71DA6-8431-4F8C-91E5-B323A165BA70")]
		public interface class ICarenMFPresentationTimeSource : ICarenMFClock
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			/// <summary>
			/// Recupera o relógio subjacente que a fonte de tempo de apresentação usa para 
			/// gerar seus tempos de relógio.
			/// </summary>
			/// <param name="Param_Out_Relogio">Recebe a interface ICarenMFClock que representa um Relógio. O chamador deve liberar a interface.</param>
			CarenResult ObterRelogioSubjacente([Out] ICarenMFClock^% Param_Out_Relogio);
		};

		/// <summary>
		/// (IMFClockStateSink) - Recebe notificações de alteração de estado do relógio de apresentação. Para receber notificações de alteração de estado do relógio de apresentação, implemente essa interface e 
		/// chame o método (ICarenMFPresentationClock.RegistarObjetoNotificação) no relógio de apresentação.
		/// </summary>
		[CategoryAttribute("IMFClockStateSink - Interface que recebe eventos do Relógio.")]
		[DescriptionAttribute("Interface responsável por expor os eventos da interface IMFClockStateSink.")]
		[Guid("A9FAE071-9C80-413F-AD9B-E71386810EA6")]
		public interface class ICarenMFClockStateSink : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}



			//Delegates

			delegate void Delegate_OnClockStart(Int64 Param_HoraSistema, Int64 Param_PosiçãoInicio);
			delegate void Delegate_OnClockStop(Int64 Param_HoraSistemaStop);
			delegate void Delegate_OnClockPause(Int64 Param_HoraSistemaPause);
			delegate void Delegate_OnClockRestart(Int64 Param_HoraSistemaRestart);
			delegate void Delegate_OnClockSetRate(Int64 Param_HoraSistemaRate, float Param_NovoRate);


			//Eventos

			/// <summary>
			/// Chamado quando o relógio de apresentação é iniciado.
			/// </summary>
			event Delegate_OnClockStart^ OnClockStart;

			/// <summary>
			/// Chamado quando o relógio de apresentação para.
			/// </summary>
			event Delegate_OnClockStop^ OnClockStop;

			/// <summary>
			/// Chamado quando o relógio de apresentação faz uma pausa.
			/// </summary>
			event Delegate_OnClockPause^ OnClockPause;

			/// <summary>
			/// Chamado quando o relógio de apresentação é reiniciado da mesma posição durante a pausa.
			/// </summary>
			event Delegate_OnClockRestart^ OnClockRestart;

			/// <summary>
			/// Chamado quando a taxa é alterada no relógio de apresentação.
			/// </summary>
			event Delegate_OnClockSetRate^ OnClockSetRate;



			//Métodos

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
		/// (IMFPresentationClock) - Interface responsável por representar uma relógio de apresentação que é usado para agendar
		/// quando as amostras de mídia devem ser processadas e para sincronizar vários fluxos.
		/// </summary>
		[CategoryAttribute("IMFPresentationClock  - Relógio da apresentação para agendamento de amostras.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFPresentationClock.")]
		[Guid("5D331E43-DA1F-44DE-81ED-DF5A7F61CA4D")]
		public interface class ICarenMFPresentationClock : ICarenMFClock
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// Registra um objeto para ser notificado sempre que o relógio inicia, para, ou faz uma pausa ou muda a taxa.
			/// </summary>
			/// <param name="Param_InterfaceNotification">A interface que contém o objeto de notificação de eventos do Relógio.</param>
			CarenResult RegistarObjetoNotificação(ICarenMFClockStateSink^ Param_InterfaceNotification);

			/// <summary>
			/// Recupera a hora mais recente. O valor retornado é representado em unidades de 100 nanosegundos, ou seja, 1 segundo é representado
			/// por 10^7(10 elevado a 7 potência), que equivale a 10Mhz.
			/// </summary>
			/// <param name="Param_Out_NsHoraRelogio">Recebe a hora do relógio atual em unidades de 100 nanosegundos.</param>
			CarenResult ObterHora([Out] Int64% Param_Out_NsHoraRelogio);

			/// <summary>
			/// Recupera a fonte de tempo de apresentação do relógio.
			/// </summary>
			/// <param name="Param_Out_TimeSource">Recebe a interface que contém a Fonte de apreentação do relógio.</param>
			CarenResult ObterFonteTempo([Out] ICarenMFPresentationTimeSource^% Param_Out_TimeSource);

			/// <summary>
			/// Pausa o tempo de apresentação. Enquanto o relógio está em pausa, o tempo do relógio não adianta,
			/// e (ObterHora) do relógio retorna o tempo em que o relógio foi pausado.
			/// </summary>
			CarenResult PausarRelogio();

			/// <summary>
			/// Cancela o registro de um objeto que está recebendo notificações de alteração de estado do relógio.
			/// </summary>
			/// <param name="Param_InterfaceNotification">Cancela o registro de notificação do relógio presente na interface de eventos.</param>
			CarenResult CancelarRegistroObjetoNotificação(ICarenMFClockStateSink^ Param_InterfaceNotification);

			/// <summary>
			/// Define a fonte de tempo para o tempo de apresentação. A fonte de tempo é o objeto que 
			/// impulsiona o relógio, fornecendo a hora atual.
			/// </summary>
			/// <param name="Param_TimeSource">Define o tempo na fonte de tempo do relógio de apresentação.</param>
			CarenResult DefinirFonteTempo(ICarenMFPresentationTimeSource^ Param_TimeSource);

			/// <summary>
			/// Começa o tempo de apresentação.
			/// </summary>
			/// <param name="Param_PosiçãoInicio">A posição ou tempo de partida inicial do relógio. O valor deve ser expressados em 
			/// unidades de 100 nanosegundos. Se (Param_PosiçãoAtual) for True, desconsidere esse valor.</param>
			/// <param name="Param_PosiçãoAtual">Define se deve iniciar a parti da posição atual. O valor de (Param_PosiçãoInicio) é desconsiderado
			/// se esse valor for True.</param>
			CarenResult IniciarRelogio(Int64 Param_PosiçãoInicio, Boolean Param_PosiçãoAtual);

			/// <summary>
			/// Para o relógio de apresentação. Enquanto o relógio estiver parado, não adianta a hora do relógio e 
			/// (ObterHora) método do relógio retorna zero.
			/// </summary>
			CarenResult PararRelogio();
		};

		/// <summary>
		/// Interface responsável por conter métodos que extendem as interfaces que gerenciam tipos de mídias.
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extensão")]
		[Guid("F3044D42-12B4-46C6-9B15-7E54A025242D")]
		public interface class ICarenMidiaExtensões
		{
			/// <summary>
			/// (Extensão) - Método responsável por obter o tipo principal da mídia. 
			/// </summary>
			/// <param name="Param_Out_TipoPrincipal">Recebe o tipo principal da mídia(Áudio ou Vídeo).</param>
			/// <param name="Param_Out_Guid">Recebe o Guid do formato principal.</param>
			CarenResult ObterTipoPrincipalMidia([Out] Enumeracoes::CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal, [Out] String^% Param_Out_Guid);

			/// <summary>
			/// (Extensão) - Método responsável por retornar o formato do tipo principal da mídia. 
			/// </summary>
			/// <param name="Param_Out_FormatoMidia">Recebe o subtipo(Formato) da mídia principal.</param>
			/// <param name="Param_Out_GuidFormato">Recebe o Guid do subtipo(Formato).</param>
			CarenResult ObterFormatoMidia([Out] Enumeracoes::CA_Midia_SubTipo% Param_Out_FormatoMidia, [Out] String^% Param_Out_GuidFormato);


		};

		/// <summary>
		/// Interface responsável por conter métodos que extendem a interface de leitura de mídia.
		/// </summary>
		[CategoryAttribute("MF Interface")]
		[DescriptionAttribute("Extensão")]
		[Guid("8E3B80BC-2993-4D7D-AAA0-D460B06ACE22")]
		public interface class ICarenLeitorMidiaExtensões
		{
			/// <summary>
			/// (Extensão) - Método responsável por retornar a quantidade de fluxos na mídia carregada pelo leitor.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Recebe a quantidade de fluxos na mídia carregada.</param>
			CarenResult ExRecuperarQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos);

			/// <summary>
			/// (Extensão) - Método responsável por retornar todos os tipos principais de mídia do arquivo carregado pelo leitor.
			/// </summary>
			/// <param name="Param_Out_TiposMidias">Recebe a lista, em ordem, com os tipos principais de mídia no fluxo carregado</param>
			CarenResult ExRecuperarTiposMidia([Out] List<Enumeracoes::CA_Midia_TipoPrincipal>^% Param_Out_TiposMidias);
		};

		/// <summary>
		/// (IMFAttributes) - Fornece uma maneira genérica para armazenar pares Chave/Valor em um objeto. As chaves são GUIDs, e os valores podem ser qualquer um dos seguintes tipos de dados: 
		/// UINT32, UINT64, Double, GUID, Cadeia de caracteres largos, Matriz de Byte.
		/// </summary>
		[CategoryAttribute("IMFAttributes - Armazenador de pares Chave/Valor em um objeto")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFAttributes")]
		[Guid("FA2D7457-E082-410A-A38D-9FBE47F62AC2")]
		public interface class ICarenMFAttributes : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			/// <summary>
			/// Compara os atributos neste objeto com os atributos em outro objeto.
			/// </summary>
			/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
			/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
			/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
			CarenResult Comparar(ICarenMFAttributes^ Param_InterfaceCompare, Enumeracoes::CA_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, [Out] Boolean% Param_Out_Resultado);

			/// <summary>
			/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PropVariant.
			/// CA_PropVariant é um Wrapper da PropVariant não gerenciada.
			/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PropVariant) é diferente do (Valor) no Atributo,
			/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
			/// </summary>
			/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
			/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
			/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
			CarenResult CompararItem(String^ Param_GuidChave, Estruturas::CA_PropVariant^ Param_Valor, [Out] Boolean% Param_Out_Resultado);

			/// <summary>
			/// (CopyAllItems) - Copia todos os atributos deste objeto em outro armazenamento de atributo.
			/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
			/// Atenção: Quando você chamar este método em um ICarenMFSample, que herda esse método, o (Tempo da amostra), (Duração) e (Sinalizadores) não são copiados 
			/// para a amostra de destino. Você deve copiar esses valores para a nova amostra manualmente.
			/// </summary>
			/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
			CarenResult CopiarTodosItens(ICarenMFAttributes^ Param_Out_InterfaceDestino);

			/// <summary>
			/// Remove todos os pares chave/valor da lista de atributos do objeto.
			/// </summary>
			CarenResult DeletarTodosItens();

			/// <summary>
			/// Remove um emparelhar chave/valor da lista de atributos do objeto.
			/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
			/// </summary>
			/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
			CarenResult DeletarItem(String^ Param_GuidChave);



			//Métodos (GET) da interface IMFAttributes.



			/// <summary>
			/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
			/// memória para a matriz.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
			/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
			CarenResult ObterAlocaçãoBlob(String^ Param_GuidChave, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer);

			/// <summary>
			/// Obtém uma seqüência de caracteres largos associada a uma chave. 
			/// Este método aloca a memória para a seqüência de caracteres.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
			/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
			/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
			CarenResult ObterAlocaçãoString(String^ Param_GuidChave, [Out] String^% Param_Out_String, [Out] UInt32% Param_Out_LarguraString);

			/// <summary>
			/// Recupera uma matriz de byte associada a uma chave. 
			/// Esse método copia a matriz em um buffer alocado pelo chamador.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
			/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
			/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (ObterBlobSize) para obter o valor para esse parametro.</param>
			CarenResult ObterBlob(String^ Param_GuidChave, UInt32 Param_TamanhoBuffer, [Out] Estruturas::CA_BlobData^% Param_Out_Buffer);

			/// <summary>
			/// Recupera o comprimento de uma matriz de byte associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
			/// <param name="Param_Out_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
			CarenResult ObterBlobSize(String^ Param_GuidChave, [Out] UInt32% Param_Out_TamanhoBuffer);

			/// <summary>
			/// Recupera o número de atributos que são definidos neste objeto.
			/// </summary>
			/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
			CarenResult ObterCountAtributos([Out] UInt32% Param_QuantidadeAtributos);

			/// <summary>
			/// Recupera um valor (Double) associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterDouble(String^ Param_GuidChave, [Out] Double% Param_Out_Valor);

			/// <summary>
			/// Recupera um valor GUID associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterGuid(String^ Param_GuidChave, [Out] String^% Param_Out_Valor);

			/// <summary>
			/// Recupera o valor desconhecido associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PropVariant) obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterItem(String^ Param_GuidChave, [Out] Estruturas::CA_PropVariant^% Param_Out_Valor);

			/// <summary>
			/// Recupera um atributo no índice especificado.
			/// </summary>
			/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
			/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterItemPorIndex(UInt32 Param_IdItem, [Out] String^% Param_Out_GuidChave, [Out] Estruturas::CA_PropVariant^% Param_Out_Valor);

			/// <summary>
			/// Recupera o tipo de dados do valor associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
			/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
			CarenResult ObterTipoDadosItem(String^ Param_GuidChave, [Out] Enumeracoes::CA_ATTRIBUTE_TYPE% Param_Out_TipoDado);

			/// <summary>
			/// Recupera uma sequência de caracteres largos associada a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
			/// <param name="Param_LarguraString">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: ObterLarguraString</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
			CarenResult ObterString(String^ Param_GuidChave, UInt32 Param_LarguraString, [Out] String^% Param_Out_Valor);

			/// <summary>
			/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
			/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
			/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
			CarenResult ObterLarguraString(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura);

			/// <summary>
			/// (GetUINT32) - Recupera um valor de UINT32 associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT32) obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterUINT32(String^ Param_GuidChave, [Out] UInt32% Param_Out_Valor);

			/// <summary>
			/// (GetUINT64) - Recupera um valor de UINT64 associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
			/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
			CarenResult ObterUINT64(String^ Param_GuidChave, [Out] UInt64% Param_Out_Valor);

			/// <summary>
			/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
			/// Ese método recuperar o Numerador e Denominador de uma chave.
			/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
			/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
			/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
			CarenResult ObterRatioAtribute(String^ Param_GuidChave, [Out] UInt32% Param_Out_Numerador, [Out] UInt32% Param_Out_Denominador);

			/// <summary>
			/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
			/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
			/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
			CarenResult ObterSizeAttribute(String^ Param_GuidChave, [Out] UInt32% Param_Out_Largura, [Out] UInt32% Param_Out_Altura);

			/// <summary>
			/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
			/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
			/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro para o objeto desconhecido. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterPonteiroDesconhecido(String^ Param_GuidChave, String^ Param_GuidInterfaceSolicitada, ICaren^ Param_Out_InterfaceDesconhecida);

			/// <summary>
			/// (LockStore) - Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
			/// </summary>
			CarenResult BloquearArmazenamento();




			//Métodos (SET) da interface IMFAttributes.




			/// <summary>
			/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Buffer">A matriz de bytes a ser associada a chave especificada.</param>
			CarenResult DefinirBlob(String^ Param_GuidChave, cli::array<Byte>^ Param_Buffer);

			/// <summary>
			/// Associa um valor duplo com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
			CarenResult DefinirDouble(String^ Param_GuidChave, Double Param_Valor);

			/// <summary>
			/// RAssocia um valor GUID com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
			CarenResult DefinirGUID(String^ Param_GuidChave, String^ Param_Valor);

			/// <summary>
			/// Adiciona um valor de atributo com uma chave especificada.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
			CarenResult DefinirItem(String^ Param_GuidChave, Estruturas::CA_PropVariant^ Param_PropVariantValor);

			/// <summary>
			/// Associa uma seqüência de caracteres largos com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
			CarenResult DefinirString(String^ Param_GuidChave, String^ Param_Valor);

			/// <summary>
			/// Associa um valor de UINT32 com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
			CarenResult DefinirUINT32(String^ Param_GuidChave, UInt32 Param_Valor);

			/// <summary>
			/// Associa um UInt64 valor com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
			CarenResult DefinirUINT64(String^ Param_GuidChave, UInt64 Param_Valor);

			/// <summary>
			/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
			/// Esse método define no valor da chave uma razão(Numerador e Denominador).
			/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
			/// <param name="Param_Numerador">Define o valor do: Numerador</param>
			/// <param name="Param_Denominador">Define o valor do: Denominador</param>
			CarenResult DefinirRatioAtribute(String^ Param_GuidChave, UInt32 Param_Numerador, UInt32 Param_Denominador);

			/// <summary>
			/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
			/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
			/// largura e altura em um único valor de UInt64 .
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
			/// <param name="Param_Largura">A Largura do vídeo em pixels.</param>
			/// <param name="Param_Altura">A Altura do vídeo em pixels.</param>
			CarenResult DefinirSizeAttribute(String^ Param_GuidChave, UInt32 Param_Largura, UInt32 Param_Altura);

			/// <summary>
			/// Associa um IUnknown ponteiro com uma chave.
			/// </summary>
			/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
			/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
			CarenResult DefinirPonteiroDesconhecido(String^ Param_GuidChave, ICaren^ Param_InterfaceDesconhecida);

			/// <summary>
			/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
			/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
			/// </summary>
			CarenResult DesbloquearAtributo();
		};

		/// <summary>
		/// (IMFAsyncResult) - Fornece informações sobre o resultado de uma operação assíncrona.
		/// </summary>
		[CategoryAttribute("IMFAsyncResult - Contém o resultado de uma operação assincrona.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFAsyncResult.")]
		[Guid("CAC9CAC9-B241-43DC-8DA8-94EB8A08EB78")]
		public interface class ICarenMFAsyncResult : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//
			// Métodos
			//


			/// <summary>
			/// (GetObject) - Retorna um objeto associado à operação assíncrona. O tipo de objeto, se houver, depende do método assíncrono que foi chamado.
			/// </summary>
			/// <param name="Param_Out_Objeto">Recebe a interface com o objeto desconhecido. Se nenhum objeto estiver associado à operação, esse parâmetro receberá o valor NULO. 
			/// Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterObjeto(ICaren^ Param_Out_Objeto);

			/// <summary>
			/// (GetState) - Retorna o objeto de estado especificado pelo chamador no método Begin assíncrono.
			/// O chamador do método assíncrono especifica o objeto de estado e pode usá-lo para qualquer finalidade definida pelo responsável da chamada. O objeto de estado pode ser NULO.
			/// </summary>
			/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterEstado(ICaren^ Param_Out_ObjetoEstado);

			/// <summary>
			/// (GetStateNoAddRef) - Retorna o objeto de estado especificado pelo chamador no método assíncrono Begin, sem incrementar a contagem de referência do objeto.
			/// </summary>
			/// <param name="Param_Out_ObjetoEstado">Recebe a interface com o objeto desconhecido. Se o valor não for NULO, o chamador deverá liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterEstadoNoAddRef(ICaren^ Param_Out_ObjetoEstado);

			/// <summary>
			/// (GetStatus) - Retorna o status da operação assíncrona.
			/// </summary>
			CarenResult ObterStatus();

			/// <summary>
			/// (SetStatus) - Define o status da operação assíncrona.
			/// </summary>
			/// <param name="Param_HRESULT">O código HRESULT que vai definir o status geral da operação.</param>
			CarenResult DefinirStatus(int Param_HRESULT);
		};

		/// <summary>
		/// (IMFAsyncCallback) - Interface de retorno de chamada para notificar o aplicativo quando um método assíncrono for concluído.
		/// </summary>
		[CategoryAttribute("IMFAsyncCallback - Interface de retorna de chamada para métodos assincronos.")]
		[DescriptionAttribute("Interface responsável por expor os eventos de IMFAsyncCallback.")]
		[Guid("A9EE4C92-7062-4D1A-8468-A9FCD269DDA1")]
		public interface class ICarenMFAsyncCallback : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Delegates

			/// <summary>
			/// Delegate que expõe a estrutura do evento (OnObterParametros).
			/// </summary>
			delegate int Delegate_RequisicaoParametros();

			/// <summary>
			/// Delegate que expõe a estrutura do evento (OnInvoke).
			/// </summary>
			/// <param name="Param_AsyncResult">A interface com o resultado do método assincrono.</param>
			delegate void Delegate_Invoke(ICarenMFAsyncResult^ Param_AsyncResult);


			//
			//Eventos
			//

			/// <summary>
			/// Evento chamado para indicar que uma chamada interna para o método (GetParameters) foi realizada e está requisitando as configurações para o segmento de 
			/// expedição para um retorno de chamada. Chame o método (DefinirConfigurações) na chamada deste evento para configurar os dados.
			/// Atenção: Retorne 1, se o evento tiver sido configurado, e 0 se o método não é implementado.
			/// </summary>
			event Delegate_RequisicaoParametros^ OnRequisiçãoParametros;

			/// <summary>
			/// Evento chamado quando uma operação assincrona é concluida.
			/// </summary>
			event Delegate_Invoke^ OnInvoke;



			//
			// Métodos
			//

			/// <summary>
			/// Fornece informações de configuração para o segmento de expedição para um retorno de chamada.
			/// Esse método deve ser chamado durante uma chamada do evento (OnRequisiçãoParametros).
			/// </summary>
			/// <param name="Param_Flags">Flags que definem o comportamente do método (Invoke) notificado pelo evento(OnInvoke).</param>
			/// <param name="Param_IdentificadorFilaTrabalho">Define o identificador da fila de trabalho na qual o retorno de chamada é despachado.</param>
			CarenResult DefinirConfigurações(Enumeracoes::CA_FLAGS_ASYNC_COMPORTAMENTO_INVOKE Param_Flags, Enumeracoes::CA_IDENTICADORES_FILA_TRABALHO Param_IdentificadorFilaTrabalho);

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
		/// (IMFMediaEvent) - Representa um evento gerado por um objeto do Media Foundation. Use essa interface para obter informações sobre o evento.
		/// </summary>
		[CategoryAttribute("IMFMediaEvent - Representa um evento gerado por um objeto do Media Event.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaEvent.")]
		[Guid("0EDC6D22-20F5-44D7-B6B9-EA8A2A321D49")]
		public interface class ICarenMFMediaEvent : ICaren, ICarenMFAttributes
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
			/// (GetStatus) - Recupera um HRESULT que especifica o status do evento.
			/// </summary>
			/// <param name="Param_Out_HResultCode">Recebe o código de status do evento.</param>
			CarenResult ObterStatus([Out] int% Param_Out_HResultCode);

			/// <summary>		
			/// (GetType) - Recupera o tipo de evento. O tipo de evento indica o que aconteceu para acionar o evento. Também define o significado do valor do evento.
			/// </summary>
			/// <param name="Param_Out_TipoEvento">Recebe a enumeração que define o tipo do evento gerado.</param>
			CarenResult ObterTipo([Out] Enumeracoes::CA_TIPO_MIDIA_EVENT% Param_Out_TipoEvento);

			/// <summary>
			/// (GetExtendedType) - Recupera o tipo estendido do evento. Utilizado para da suporte a eventos personalizados.
			/// </summary>
			/// <param name="Param_Out_GuidExtendedType">Recebe o guid para o tipo extendido do evento.</param>
			CarenResult ObterTipoExtendido([Out] String^% Param_Out_GuidExtendedType);

			/// <summary>
			/// (GetValue) - Recupera o valor associado ao evento, se houver. O valor é recuperado como uma estrutura CA_PropVariant. O tipo de dados real e o significado do valor 
			/// dependem do evento.
			/// </summary>
			/// <param name="Param_Out_ValorEvento">Recebe a PropVariant que contém o valor associado ao evento. Nem todos eventos possuem valores.</param>
			CarenResult ObterValor([Out] Estruturas::CA_PropVariant^% Param_Out_ValorEvento);
		};

		/// <summary>
		/// (IMFMediaEventGenerator) - Recupera eventos de qualquer objeto do Media Foundation que gera eventos.
		/// Um objeto que suporta essa interface mantém uma fila de eventos. O cliente do objeto pode recuperar os eventos de forma síncrona ou assíncrona. O método síncrono é (ObterEvento). 
		/// Os métodos assíncronos são SolicitarProximoEvento e ConcluirSolicitaçãoEvento.
		/// </summary>
		[CategoryAttribute("IMFMediaEventGenerator - Gerenciador de eventos de objetos do Media Foundation.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da interface IMFMediaEventGenerator.")]
		[Guid("266CD5F0-C874-4BCA-8CE4-1440A35CB816")]
		public interface class ICarenMFMediaEventGenerator : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			// Métodos


			/// <summary>
			/// (GetEvent) - Recupera o próximo evento na fila. Este método é (Síncrono).
			/// Se a fila já contiver um evento, o método retornará S_OK imediatamente. Se a fila não contiver um evento, o comportamento 
			/// dependerá do valor de Param_Flags.
			/// </summary>
			/// <param name="Param_Flags">Especifica como deve obter o evento.</param>
			/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
			CarenResult ObterEvento(Enumeracoes::CA_FLAGS_OBTER_EVENTO Param_Flags, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

			/// <summary>
			/// (BeginGetEvent) - Inicia uma solicitação assíncrona para o próximo evento na fila.
			/// Este método é responsável por solicitar o proximo evento na fila, passando o Callback responsável por receber a conclusão da chamada Assincrona.
			/// </summary>
			/// <param name="Param_Callback">A interface que vai receber os eventos que seram gerados pelas interfaces que derivam desta.</param>
			/// <param name="Param_ObjetoDesconhecido">Uma interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar esse objeto para armazenar 
			/// informações de estado. O objeto é retornado ao responsável pela chamada quando o retorno de chamada é invocado.</param>
			CarenResult SolicitarProximoEvento(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoDesconhecido);

			/// <summary>
			/// (EndGetEvent) - Conclui uma solicitação (Assíncrona) para o próximo evento na fila.
			/// </summary>
			/// <param name="Param_ResultAsync">A interface ICarenMFAsyncResult. Essa interface deve ser a retornada pelo Evento (OnInvoke).</param>
			/// <param name="Param_Out_MidiaEvent">Recebe a interface que contém as informações da operação assincrona para o evento notificado. O chamador deve liberar a interface.</param>
			CarenResult ConcluirSolicitaçãoEvento(ICarenMFAsyncResult^ Param_ResultAsync, [Out] ICarenMFMediaEvent^% Param_Out_MidiaEvent);

			/// <summary>
			/// (QueueEvent) - Coloca um novo evento na fila do objeto.
			/// </summary>
			/// <param name="Param_TipoEvento">Especifica o tipo do evento. O tipo do evento é retornado pelo método (ICarenMFMediaEvent.ObterTipo).</param>
			/// <param name="Param_GuidExtendedType">O tipo estendido. Se o evento não tiver um tipo estendido, defina como NULO. O tipo estendido é retornado pelo método (ICarenMFMediaEvent.ObterTipoExtendido) do evento.</param>
			/// <param name="Param_HResultCode">Um código de sucesso ou falha indicando o status do evento. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterStatus) do evento.</param>
			/// <param name="Param_Dados">uma CA_PropVariant que contém o valor do evento. Este parâmetro pode ser NULO. Esse valor é retornado pelo método (ICarenMFMediaEvent.ObterValor) do evento.</param>
			CarenResult InserirEventoFila(Enumeracoes::CA_TIPO_MIDIA_EVENT Param_TipoEvento, String^ Param_GuidExtendedType, Int32 Param_HResultCode, Estruturas::CA_PropVariant^ Param_Dados);
		};

		/// <summary>
		/// (IMFMediaType) - Interface responsável por representar um tipo de mídia que descreve o formato de um fluxo de mídia. Negocia formatos de mídia entre as interfaces do (Media Foundation) e descobre 
		/// o formato de um arquivo de mídia ou fluxo.
		/// </summary>
		[CategoryAttribute("IMFMediaType - Representa uma descrição de midia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaType.")]
		[Guid("B3D4DF6C-271E-4509-9E11-627518A65ED9")]
		public interface class ICarenMFMediaType : ICarenMFAttributes, ICarenMidiaExtensões
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}


			/// <summary>
			/// (GetMajorType) - Obtém o tipo principal da midia: Vídeo ou Áudio.
			/// </summary>
			/// <param name="Param_Out_GuidTipoMidia">Retorna o GUID do tipo principal da mídia.</param>
			/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração com o tipo principal da mídia.</param>
			CarenResult ObterTipoPrincipal([Out] String^% Param_Out_GuidTipoMidia, [Out] Enumeracoes::CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal);

			/// <summary>
			/// (IsCompressedFormat) - Consulta se o tipo de mídia é um formato compactado(CompressedFormat).
			/// </summary>
			/// <param name="Param_Out_FormatoCompactado">Retorna se o formato da mídia está compactado.</param>
			CarenResult FormatoCompactado([Out] Boolean% Param_Out_FormatoCompactado);

			/// <summary>
			/// (IsEqual) - Compara dois tipos de mídia e determina se eles são idênticos. 
			/// Se eles não forem idênticos, o método indica como os dois formatos diferem.
			/// </summary>
			/// <param name="Param_MidiaCompare">A interface a ser comparada com a atual.</param>
			/// <param name="Param_Out_ResultadoCompare">O resultado da comparação dos objetos.</param>
			CarenResult CompararMidiaTypes(ICarenMFMediaType^ Param_MidiaCompare, [Out] Enumeracoes::CA_MEDIA_TYPE_EQUAL% Param_Out_ResultadoCompare);
		};

		/// <summary>
		/// (IMFMediaTypeHandler) - Interface responsável por manipular os Tipos de midia entre as interfaces do Media Foundation.
		/// Essa interface é a responsável por definir um (ICarenMFMediaType) para Leituras, Gravações em fluxos de midia.
		/// </summary>
		[CategoryAttribute("IMFMediaTypeHandler - Manipula os tipos de midia")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaTypeHandler")]
		[Guid("4F53961B-71F3-4190-9530-63060FDBE567")]
		public interface class ICarenMFMediaTypeHandler : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}



			/// <summary>
			/// (GetCurrentMediaType) - Recupera o tipo de mídia atual do objeto.
			/// </summary>
			/// <param name="Param_Out_MidiaType">Retorna o Tipo de midia atual.</param>
			CarenResult ObterTipoMidiaAtual([Out] ICarenMFMediaType^% Param_Out_MidiaType);

			/// <summary>
			/// (GetMajorType) - Obtém o tipo de mídia principal do objeto.
			/// </summary>
			/// <param name="Param_Out_GuidMidiaPrincipal">Retorna o GUID do tipo da mídia principal.</param>
			/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração que define o tipo principal da mídia.</param>
			CarenResult ObterTipoMidiaPrincipal([Out] String^% Param_Out_GuidMidiaPrincipal, [Out] Enumeracoes::CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal);

			/// <summary>
			/// (GetMediaTypeByIndex) - Recupera um tipo de mídia da lista do objeto de tipos de mídia com suporte.
			/// </summary>
			/// <param name="Param_Id">Índice baseado em zero do tipo de mídia para recuperar. Para obter o número de tipos de mídia na lista, chame o método (ObterCountTiposMidia).</param>
			/// <param name="Param_Out_MidiaType">Retorna o tipo da mídia no Id especificado.</param>
			CarenResult ObterTipoMidiaPorIndex(UInt32 Param_Id, [Out] ICarenMFMediaType^% Param_Out_MidiaType);

			/// <summary>
			/// (GetMediaTypeCount) - Recupera o número de tipos de mídia na lista do objeto de tipos de mídia com suporte.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de tipos de mídia na interface.</param>
			CarenResult ObterCountTiposMidia([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (IsMediaTypeSupported) - Consulta se o objeto oferece suporte a um tipo de mídia especificado.
			///  Para uma fonte de mídia, isso significa que a fonte pode gerar dados que estejam de acordo com esse 
			/// tipo de mídia. Para um coletor de mídia, isso significa que o coletor pode receber dados que está de 
			/// acordo com esse tipo de mídia.
			/// NOTA: O método falha com (ER_MF_TIPO_MIDIA_INVALIDA) se o tipo da mídia não é suportado.
			/// </summary>
			/// <param name="Param_MidiaType">O Tipo de mídia a ser verificado se é suportado pela (Fonte de mídia ou Pelo Coletor de Mídia) que gerou essa interface.</param>
			/// <param name="Param_Out_MidiaAproximada">Recebe o tipo de mídia que pode se aproximar ou não da mídia verificada. 
			/// Se o método retorna sucesso, valor dessa parametro é (NULO).</param>
			CarenResult VerificarTipoMidiaSuportado(ICarenMFMediaType^ Param_MidiaType, [Out] ICarenMFMediaType^% Param_Out_MidiaAproximada);

			/// <summary>
			/// (SetCurrentMediaType) - Define o tipo de mídia do objeto.
			/// Para fontes de mídia, a configuração do tipo de mídia significa que a fonte gerará dados que estejam 
			/// de acordo com esse tipo de mídia. Para coletores de mídia, definindo o tipo de mídia significa que o 
			/// coletor pode receber dados que está de acordo com esse tipo de mídia.
			/// </summary>
			/// <param name="Param_MidiaType">O tipo de mídia a ser definido no objeto.</param>
			CarenResult DefinirTipoMidiaAtual(ICarenMFMediaType^ Param_MidiaType);
		};

		/// <summary>
		/// (IMFMediaBuffer) - Contém dados de midia. Os tipos podem ser Áudio ou Video.
		/// Se o buffer conter dados de Imagem 2D (Quadros de vídeo Descompactados), Consulte o Buffer
		/// para a interface (IDirect3DSurface9) ou (IMF2DBuffer), representada pela Interface (ICarenDirect3DSurface9) e (ICarenMFMedia2DBuffer). 
		/// Chamadas para Lock, sendo que o Buffer contém (Imagems 2D), pode gerar um aumento de memória interna desnecessária.
		/// </summary>
		[CategoryAttribute("IMFMediaBuffer - Contém buffers de dados de midia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaBuffer.")]
		[Guid("124E1685-0A18-442A-A0C7-6EA86C274F4D")]
		public interface class ICarenMFMediaBuffer : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			/// <summary>
			/// Recupera o comprimento dos dados válidos no buffer.
			/// </summary>
			/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos, em bytes. Se o buffer não contiver nenhum dado válido, o valor será zero.</param>
			CarenResult ObterLarguraAtual([Out] UInt32% Param_Out_LarguraAtual);


			/// <summary>
			/// Recupera o Dimensionar alocado do buffer. Esse o valor da largura total
			/// de dados que podem ser adicioandos. Se o buffer conter dados, a largura dos dados
			/// podem ser menor que a lagrura máxima. Consulte (ObterLarguraAtual) para obter o 
			/// valor real da largura dos dados neste Buffer.
			/// </summary>
			/// <param name="Param_Out_LarguraMaxima">Recebe a largura total de dados que esse buffer pode conter.</param>
			CarenResult ObterLarguraMaxima([Out] UInt32% Param_Out_LarguraMaxima);


			/// <summary>
			/// Force acesso aos dados que estão presentes neste buffer, para leitura ou gravação.
			/// Esse método fornece o acesso do chamador para o buffer inteiro, até o tamanho máximo retornado no Param_LarguraMaximaEscrita parâmetro. O valor retornado em Param_LarguraAtual 
			/// é o tamanho de todos os dados válidos já no buffer, que pode ser menor do que o tamanho do buffer total.
			/// </summary>
			/// <param name="Param_Out_BufferMidia">Recebe a interface responsável por gerenciar o buffer preso(Lock). Você poder: Escrever e Ler para o buffer.</param>
			/// <param name="Param_Out_LarguraMaximaEscrita">Recebe a quantidade máxima de dados que podem ser gravados para o buffer. Este parâmetro pode ser (NULO).</param>
			/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos no buffer, em bytes. Este parâmetro pode ser (NULO).</param>
			CarenResult Lock([Out] ICarenBuffer^% Param_Out_BufferMidia, [Out] UInt32% Param_Out_LarguraMaximaEscrita, [Out] UInt32% Param_Out_LarguraAtual);


			/// <summary>
			/// Desbloqueia um buffer que foi bloqueado anteriormente. Chame esse método uma vez para cada chamada no método (Lock).
			/// É um erro chamar Unlock se você não chamar Lock anteriormente. Depois de chamar esse método, (Não Use) a interface 
			/// retornada pelo Lock método. Não é mais garantido que o buffer que contenha nela seja valido.
			/// </summary>
			CarenResult Unlock();


			/// <summary>
			/// Define o comprimento dos dados válidos no buffer.
			/// ATENÇÃO: Chame esse método se você gravar dados no buffer.
			/// </summary>
			/// <param name="Param_LarguraAtual">Comprimento dos dados válidos, em bytes. Esse valor não pode ser maior do que o tamanho alocado do buffer,
			/// que é retornado pelo método (ObterLarguraMaxima).</param>
			CarenResult DefinirLarguraAtual(UInt32 Param_LarguraAtual);
		};

		/// <summary>
		/// (IMF2DBuffer) - Contém o Buffer que gerencia, exclusivamente, superfíces (Bidimensionais) -> Imagems 2D(Quadros de Vídeos).
		/// Consulte sempre o (ICarenMFMediaBuffer.ConsultarInterface) para essa interface, antes de chamar o método (Lock) para obter os dados.
		/// Para usar um buffer 2-D, é importante saber o (Stride), que é o número de bytes necessários para ir de uma linha de pixels para o próximo. 
		/// A passada pode ser maior do que a largura da imagem, porque a superfície pode conter bytes de preenchimento após cada linha de pixels.
		/// (Stride) também pode ser (Negativo), se os pixels são orientados (bottom-up) na memória
		/// </summary>
		[CategoryAttribute("IMF2DBuffer - Contém buffers 2D exclusivamente de Video.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMF2DBuffer.")]
		[Guid("B3902CBD-7049-4A7E-AA78-3E66CE9AA524")]
		public interface class ICarenMFMedia2DBuffer : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// (ContiguousCopyFrom) - Copia dados para esse buffer de um buffer que tem um formato contíguo(Único).
			/// </summary>
			/// <param name="Param_BufferContiguo">A interface que contém um buffer com os dados contiguou a serem copiados.</param>
			/// <param name="Param_LarguraBuffer">A largura do buffer a ser copiado.</param>
			CarenResult CopiarBufferContiguouDe(ICarenBuffer^ Param_BufferContiguo, UInt32 Param_LarguraBuffer);


			/// <summary>
			/// (ContiguousCopyTo) - Copia esse buffer no buffer do chamador, convertendo os dados em formato contíguo(Único).
			/// </summary>
			/// <param name="Param_DestinoBufferContiguou">A interface que vai receber o buffer de dados do objeto atual.</param>
			/// <param name="Param_LarguraBufferDestino">O tamanho do buffer de destino. Obtenha esse valor chamando o método (ObterLarguraContiguou).</param>
			CarenResult CopiarBufferContiguouPara(ICarenBuffer^% Param_DestinoBufferContiguou, UInt32 Param_LarguraBufferDestino);

			/// <summary>
			/// (GetContiguousLength) - Recupera o número de bytes necessários para armazenar os dados do buffer 
			/// em formato contíguo.
			/// </summary>
			/// <param name="Param_Out_LarguraBufferContiguou">Recebe a largura do Buffer Contiguou.</param>
			CarenResult ObterLarguraContiguou([Out] UInt32% Param_Out_LarguraBufferContiguou);


			/// <summary>
			/// (GetScanline0AndPitch) - Recupera um ponteiro para a memória de buffer e o Stride da superfície do quadro de vídeo.
			/// Antes de chamar esse método, você deve bloquear o buffer chamando (Lock2D). O valor retornado em (Param_Out_Stride) 
			/// é válido somente enquanto o buffer permanece bloqueado.
			/// </summary>
			/// <param name="Param_Out_ByteBufferPrimeiraLinha">Recebe uma Interface de buffer para o primeiro byte da linha superior de pixels na imagem..</param>
			/// <param name="Param_Out_Stride">Recebe o stride, em bytes.</param>
			CarenResult ObterBufferAndSuperficeStride([Out] ICarenBuffer^% Param_Out_ByteBufferPrimeiraLinha, [Out] Int64% Param_Out_Stride);


			/// <summary>
			/// (IsContiguousFormat) - Consulta se o buffer é contíguo em seu (formato nativo).
			/// </summary>
			/// <param name="Param_Out_BufferContiguou">Retorna true se o formato nativo deste buffer é: Contiguou.</param>
			CarenResult IsBufferFormatoContiguou([Out] Boolean% Param_Out_BufferContiguou);


			/// <summary>
			/// (Lock2D) - Fornece o acesso do chamador para a memória no buffer.
			/// </summary>
			/// <param name="Param_Out_Buffer">Recebe a interface com o buffer para o primeiro byte da linha superior de pixels na imagem. A linha superior é definida como a 
			/// linha superior quando a imagem é apresentada ao visualizador e pode não ser a primeira linha na memória.</param>
			/// <param name="Param_Out_Stride">Recebe a passada de superfície, em bytes. O passo pode ser negativo, indicando que a 
			/// imagem é orientada de baixo para cima na memória.</param>
			CarenResult Lock2D([Out] ICarenBuffer^% Param_Out_Buffer, [Out] Int64% Param_Out_Stride);


			/// <summary>
			/// (Unlock2D) - Desbloqueia um buffer que foi bloqueado anteriormente. 
			/// Chame esse método uma vez para cada chamada para o método Lock2D.
			/// </summary>
			CarenResult Unlock2D();
		};

		/// <summary>
		/// (IMF2DBuffer2) - Interface responsável por representar um buffer que contém uma superfície bidimensional, como um quadro de vídeo.
		/// Essa interface extende os métodos da interface base (ICarenMFMedia2DBuffer) e adiciona uma versão mais segura do método (Lock2D).
		/// </summary>
		[CategoryAttribute("IMF2DBuffer2 - Extende a interface IMF2DBuffer.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMF2DBuffer2.")]
		[Guid("5E6AA0AA-0E58-42E7-9FC3-EF516E52C134")]
		public interface class ICarenMFMedia2DBuffer2 : ICarenMFMedia2DBuffer
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
			/// (Copy2DTo) - Copia o buffer para outro objeto de buffer 2D.
			/// </summary>
			/// <param name="Param_Interface2DBufferDestino">A interface de destino que vai receber o buffer.</param>
			CarenResult Copiar2DBufferPara(ICarenMFMedia2DBuffer2^% Param_Interface2DBufferDestino);

			/// <summary>
			/// (Lock2DSize) - Fornece o acesso do chamador para a memória no buffer.
			/// </summary>
			/// <param name="Param_LockBufferFlags">Um membro da enumeração (CA_2DBUFFER_LOCK_FLAGS) que especifica se deseja bloquear o buffer para leitura, gravação ou ambos.</param>
			/// <param name="Param_Out_BufferPBScanline0">Recebe um ponteiro para o primeiro byte da linha superior de pixels na imagem. A linha superior é definida como a linha superior quando 
			/// a imagem é apresentada ao visualizador e pode não ser a primeira linha na memória.</param>
			/// <param name="Param_Out_StrideSuperfice">Recebe o passo de superfície, em bytes. A passada pode ser negativa, indicando que a imagem é orientada de baixo para cima na memória.</param>
			/// <param name="Param_Out_BufferStart">Recebe um ponteiro para o início do buffer acessível na memória.</param>
			/// <param name="Param_Out_LarguraBuffer">Recebe o comprimento do buffer, em bytes.</param>
			CarenResult Lock2DSize(
				Enumeracoes::CA_2DBUFFER_LOCK_FLAGS Param_LockBufferFlags,
				[Out] ICarenBuffer^% Param_Out_BufferPBScanline0,
				[Out] Int64% Param_Out_StrideSuperfice,
				[Out] ICarenBuffer^% Param_Out_BufferStart,
				[Out] UInt32% Param_Out_LarguraBuffer);
		};

		/// <summary>
		/// (IMFSample) - Representa uma amosta de midia. Pode ser Video ou Áudio. Utilize essa interface para obter e gerenciar as Amostras de midia do sistema. Amostras de Vídeo, devem 
		/// ter seus Buffers de midia (Consultados) para interfaces 2D ou Superfices do DirectX, antes de fazer chamadas para (Lock) na interface (ICarenMFMediaBuffer) .
		/// </summary>
		[CategoryAttribute("IMFSample - Contém amostras de dados de midia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFSample.")]
		[Guid("06BFA703-3BFF-4878-A2E9-C45EDCF4EB20")]
		public interface class ICarenMFSample : ICarenMFAttributes, ICarenMidiaExtensões
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			/// <summary>
			/// Adiciona um buffer ao final da lista de buffers no exemplo. O método cria uma copia do buffer.
			/// Atenção: Para dados de vídeo descompactados, cada buffer deve conter um único quadro de vídeo e amostras não devem conter vários quadros. 
			/// Em geral, armazenar vários buffers em uma amostra é desencorajado.
			/// </summary>
			/// <param name="Param_NovoBuffer">A interface que contém o novo buffer a ser adicionado.</param>
			CarenResult AdicionarMediaBuffer(ICarenMFMediaBuffer^ Param_NovoBuffer);

			/// <summary>
			/// Converte um exemplo com (Múltiplo Buffers) em um exemplo com um único buffer.
			/// O método retorna a Interface(ICarenMFMediaBuffer) com o único buffer convertido.
			/// Se o exemplo conter apenas 1 Buffer, o sistema vai retornar uma interface para o mesmo.
			/// </summary>
			/// <param name="Param_Out_SingleBuffer">Retorna a interface(ICarenMFMediaBuffer) que contém o (Single Buffer).</param>
			CarenResult ConverterParaSingleBuffer([Out] ICarenMFMediaBuffer^% Param_Out_SingleBuffer);

			/// <summary>
			/// Copia os dados de exemplo para um buffer. Este método conforma os 
			/// dados válidos de todos os buffers da amostra, em ordem.
			/// Obtenha a (Largura Total) do (Buffer de Destino) para saber se o mesmo tem (Capacidade) para alocar os dados a serem copiados.
			/// </summary>
			/// <param name="Param_BufferDestino">A interface que que vai receber o buffer a ser copiado.</param>
			CarenResult CopiarParaBuffer(ICarenMFMediaBuffer^% Param_BufferDestino);

			/// <summary>
			/// Obtém um buffer da amostra, por índice.
			/// Nota: Segundo a Microsoft, na maioria dos casos, é melhor converter todos os buffers da amostra é um único buffer e depois obter os dados através do método.
			/// </summary>
			/// <param name="Param_IdBuffer">O Id baseado em 0, do buffer que se quer obter na amostra.</param>
			/// <param name="Param_Out_Buffer">Recebe a interface(ICarenMFMediaBuffer) com o buffer no id requisitado.</param>
			CarenResult ObterBufferPorIndex(UInt32 Param_IdBuffer, [Out] ICarenMFMediaBuffer^% Param_Out_Buffer);

			/// <summary>
			/// Recupera o número de buffers na amostra.
			/// </summary>
			/// <param name="Param_Out_QuantidadeBuffers">Contém o valor com a quantidade de Buffers na Amostra.</param>
			CarenResult ObterCountBuffers([Out] UInt32% Param_Out_QuantidadeBuffers);

			/// <summary>
			/// Recupera a duração do exemplo.
			/// </summary>
			/// <param name="Param_Out_DuraçãoAmostra">Contém a duração da Amostra em: Unidades de 100 nanosegundos.</param>
			CarenResult ObterDuraçãoAmostra([Out] Int64% Param_Out_DuraçãoAmostra);

			/// <summary>
			/// Recupera os sinalizadores associados com o exemplo. Atualmente não há 
			/// sinalizadores definidos.
			/// </summary>
			/// <param name="Param_Out_Flags">Como não há atualmente nenhuma flags definida, o retorno é 0.</param>
			CarenResult ObterFlagsAmostra([Out] UInt32% Param_Out_Flags);

			/// <summary>
			/// Recupera o tempo de apresentação da amostra.
			/// </summary>
			/// <param name="Param_Out_TempoApresentacao">Contém o tempo de apresentação em: Unidades de 100 nanosegundos.</param>
			CarenResult ObterTempoApresentaçãoAmostra([Out] Int64% Param_Out_TempoApresentacao);

			/// <summary>
			/// Recupera o comprimento total dos dados válidos em todos os buffers na amostra. 
			/// O comprimento é calculado como a soma dos valores recuperados pelo método
			/// ICarenMFMediaBuffer.ObterLarguraAtual.
			/// </summary>
			/// <param name="Param_Out_LarguraTotal">Recebe o comprimento total dos dados válidos, em bytes.</param>
			CarenResult ObterTotalLength([Out] UInt32% Param_Out_LarguraTotal);

			/// <summary>
			/// Remove todos os buffers do exemplo.
			/// </summary>
			CarenResult RemoverTodosBuffers();

			/// <summary>
			/// Remove um buffer em um índice especificado da amostra.
			/// </summary>
			/// <param name="Param_IdBuffer">O Id para o buffer que será removido da amostra.</param>
			CarenResult RemoverBufferPorIndex(UInt32 Param_IdBuffer);

			/// <summary>
			/// Define a duração desta amostra.
			/// </summary>
			/// <param name="Param_Duração">A duração da amostra em unidades de 100 nanosegundos.</param>
			CarenResult DefinirDuraçãoAmostra(Int64 Param_Duração);

			/// <summary>
			/// Define o tempo de apresentação do exemplo.
			/// </summary>
			/// <param name="Param_TempoApresentação">O tempo da apresentação da amostra em unidades de 100 nanosegundos.</param>
			CarenResult DefinirTempoApresentaçãoAmostra(Int64 Param_TempoApresentação);

			/// <summary>
			/// Define os sinalizadores associados com o exemplo. Atualmente não há sinalizadores são definidos.
			/// </summary>
			/// <param name="Param_Flag">Esse valor é reservado. Deixe como 0</param>
			CarenResult DefinirFlagsAmostra(UInt32 Param_Flag);
		};

		/// <summary>
		/// (IMFVideoSampleAllocator) - Interface responsável por armazenar amostras de Vídeo para o coletor de mídia de Vídeo.
		/// Essa interface é exposta como um serviço pelos Dissipadores de Fluxos que estão no EVR.
		/// Os dissipadores de fluxo representa a interface (ICarenStreamSink).
		/// Use o guid (MR_VIDEO_ACCELERATION_SERVICE) para obter essa interface atravez da ICarenMFGetService::GetService.
		/// </summary>
		[CategoryAttribute("IMFVideoSampleAllocator - Armazena amostas de vídeo para o EVR.")]
		[Guid("E7093167-4C8E-45A1-AA82-FD2F1FD08AB0")]
		public interface class ICarenMFVideoSampleAllocator : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// (AllocateSample) - Obtém uma amostra de vídeo do alocador.
			/// </summary>
			/// <param name="Param_Out_AmostraVideo">Recebe a interface que contém a amostra de vídeo. O chamado deve liberar a interface.</param>
			CarenResult ObterAmostraVideo([Out] ICarenMFSample^% Param_Out_AmostraVideo);

			/// <summary>
			/// (InitializeSampleAllocator) - Inicializa o alocador informando a quantidade de amostras para alocar e o tipo de mídia
			/// para cada amostra.
			/// As amostras alocadas devem ser compativeis com o IDirect3DDeviceManager9 - (D3D9).
			/// </summary>
			/// <param name="Param_CountAmostra">A quantidade de amostas para alocar.</param>
			/// <param name="Param_TipoAmostraVideo">Uma interface que contém o Tipo de mídia de vídeo que será alocada.</param>
			CarenResult InicializarAlocadorAmostras(UInt32 Param_CountAmostra, ICarenMFMediaType^ Param_TipoAmostraVideo);

			/// <summary>
			/// (InitializeSampleAllocatorEx) - Inicializa o alocador informando a quantidade de amostras para alocar e o tipo de mídia
			/// para cada amostra.
			/// As amostras alocadas devem ser compativeis com o DXGI - (D3D11).
			/// </summary>
			/// <param name="Param_CountAmostra">A quantidade de amostas para alocar.</param>
			/// <param name="Param_TipoAmostraVideo">Uma interface que contém o Tipo de mídia de vídeo que será alocada.</param>
			CarenResult InicializarAlocadorAmostrasD3D11(UInt32 Param_CountAmostra, ICarenMFMediaType^ Param_TipoAmostraVideo);

			/// <summary>
			/// (SetDirectXManager) - Especifica o dispositivo do gerenciamento do Direct3D para o coletor de mídia de vídeo utilizar.
			/// O coletor de mídia usa o Gerenciador de dispositivos Direct3D para obter um ponteiro para o dispositivo Direct3D, que ele usa para alocar superfícies Direct3D. O Gerenciador de dispositivos 
			/// habilita vários objetos no pipeline (como um processador de vídeo e um decodificador de vídeo) para compartilhar o mesmo dispositivo Direct3D.
			/// </summary>
			/// <param name="Param_Interface">A interface que o gerenciador do Direct3D a ser usado.</param>
			CarenResult DefinirDirect3DDeviceManager(ICaren^ Param_Interface);

			/// <summary>
			/// (UninitializeSampleAllocator) - Libera Todas as amostras de vídeo que tenham sido alocadas.
			/// </summary>
			CarenResult LiberarTodasAmostras();
		};

		/// <summary>
		/// (IMFStreamSink) - Representa um fluxo em um objeto de coletor de mídia (ICarenMFMediaSink). Representado pela interface IMFMediaSink.
		/// </summary>
		[CategoryAttribute("IMFStreamSink - Coletor de fluxo.")]
		[Guid("4442A91B-3521-4E0A-9F65-2BEFB93DA6E4")]
		public interface class ICarenMFMediaStreamSink : ICaren, ICarenMFMediaEventGenerator
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			/// <summary>
			/// Recupera o (Coletor de Mídia) que possui esse (Coletor de Fluxo).
			/// </summary>
			/// <param name="Param_Out_MidiaSink">Recebe a interface(ICarenMFMediaSink) do (Coletor de Mídia) responsável por esse (Coletor de Fluxo). O usuário deve criar a interface antes de chamar o método.</param>
			CarenResult RecuperarMediaSink(ICaren^ Param_Out_MidiaSink);

			/// <summary>
			/// Fornece uma amostra para o fluxo. O coletor de mídia processa o exemplo.
			/// Esse método pode retornar (ER_MF_AMOSTRA_TIME_SPAN_INVALIDO) por vários motivos, dependendo da implementação do coletor de mídia:
			/// 1 > Carimbos de hora negativos.
			/// 2 > Carimbos de tempo que saltam para trás (dentro do mesmo fluxo).
			/// 3 > Os carimbos de hora de um fluxo se afastaram muito dos registros de tempo em outro fluxo no mesmo coletor de mídia 
			/// (por exemplo, um coletor de arquivamento que multiplexa os fluxos).
			/// </summary>
			/// <param name="Param_AmostraMidia">A amostra de mídia a ser processada.</param>
			CarenResult ProcessarAmostraMidia(ICarenMFSample^ Param_AmostraMidia);

			/// <summary>
			/// Recupera o identificador de fluxo para este coletor de fluxo.
			/// </summary>
			/// <param name="Param_Out_IdentificadorFluxo">Retorna o identificador deste fluxo.</param>
			CarenResult ObterIdentificador([Out] UInt32% Param_Out_IdentificadorFluxo);

			/// <summary>
			/// Recupera o manipulador de tipo de mídia para o coletor de fluxo. 
			/// Você pode usar o manipulador de tipo de mídia para localizar quais
			/// formatos o fluxo oferece suporte e para definir o tipo de mídia no fluxo.
			/// </summary>
			/// <param name="Param_Out_MidiaHandle">Recebe a interface que possui o (Manipulador de Mídia).</param>
			CarenResult ObterMediaTypeHandle([Out] ICarenMFMediaTypeHandler^% Param_Out_MidiaHandle);

			/// <summary>
			/// Coloca um marcador no fluxo.
			/// O método placemarker coloca um marcador no fluxo entre amostras. O MFSTREAMSINK_MARKER_TYPE enumeração define o 
			/// tipo de marcador e o tipo de informações associadas com o marcador.
			/// </summary>
			/// <param name="Param_Marcador">Especifica o tipo de marcador, como um membro da enumeração: CA_MIDIA_STREAM_SINK_MARCADORES</param>
			/// <param name="Param_ValorAdicional">Um valor que contém informações adicionais relacionadas ao marcador. Esse parâmetro pode ser (NULO).</param>
			/// <param name="Param_DadosAnexoEvento">Valor que é anexado junto ao evento(MEStreamSinkMarker). Chame o método (ObterValor) na interface 
			/// de evento para obter esse valor. Esse parâmetro pode ser (NULO).</param>
			CarenResult AdicionarMarcador(Enumeracoes::CA_MIDIA_STREAM_SINK_MARCADORES Param_Marcador, Estruturas::CA_PropVariant^ Param_ValorAdicional, Estruturas::CA_PropVariant^ Param_DadosAnexoEvento);

			/// <summary>
			/// Faz com que o coletor de fluxo para descartar todas as amostras que ele 
			/// recebeu e ainda não processado.
			/// </summary>
			CarenResult Flush();
		};

		/// <summary>
		/// (IMFMediaSink) - Implementado por objetos de coletor de mídia. Essa interface é a interface base para todos os Coletores de Mídia do Media Foundation. 
		/// Coletor de fluxo manipular o processamento real de dados em cada fluxo.
		/// </summary>
		[CategoryAttribute("IMFMediaSink - Coletor de mídia.")]
		[Guid("C8514E08-756F-4C42-AB65-C9FFEEACD7CD")]
		public interface class ICarenMFMediaSink : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// Adiciona um novo coletor de fluxo para o coletor de mídia.
			/// O método retorna uma interface para o StreamSink adicionado.
			/// </summary>
			/// <param name="Param_IdentificadorFluxo">Um (Identificador) para o fluxo. O valor é (Arbitrário), mas deve ser exclusivo.</param>
			/// <param name="Param_TipoMidia">Uma interface com o tipo de mídia do Stream a ser adicionado. Esse valor pode ser (NULO).</param>
			/// <param name="Param_Out_FluxoSink">Retorna uma interface para o fluxo adicionado.</param>
			CarenResult AdicionarStreamSink(UInt32 Param_IdentificadorFluxo, ICarenMFMediaType^ Param_TipoMidia, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

			/// <summary>
			/// Obtém as características do coletor de mídia.
			/// </summary>
			/// <param name="Param_Out_Caracteristicas">Retorna as características desse (Coletor de mídia).</param>
			CarenResult ObterCaracteristicas([Out] Enumeracoes::CA_MIDIA_SINK_CARACTERISTCAS% Param_Out_Caracteristicas);

			/// <summary>
			/// Obtém o relógio de apresentação que foi definido no coletor de mídia.
			/// </summary>
			/// <param name="Param_Out_RelogioApresentação">Recebe a interface que contém o Relogio de Apresentação(IMFPresentationClock)</param>
			CarenResult ObterRelogioApresentação([Out] ICarenMFPresentationClock^% Param_Out_RelogioApresentação);

			/// <summary>
			/// Obtém um coletor de fluxo, especificado pelo identificador de fluxo.
			/// </summary>
			/// <param name="Param_IdentificadorFluxo">O Identificador para o fluxo a ser obtido.</param>
			/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o Stream Sink requisitado pelo seu (Identificador)</param>
			CarenResult ObterStreamSinkPorIdentificador(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

			/// <summary>
			/// Obtém um coletor de fluxo, especificado por index.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o coletor de fluxo a ser obtido.</param>
			/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o coletor de fluxo requisitado.</param>
			CarenResult ObterStreamSinkPorIndex(UInt32 Param_IdFluxo, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

			/// <summary>
			/// Obtém o número de coletores de fluxo neste coletor de mídia.
			/// </summary>
			/// <param name="Param_Out_QuantidadeSinks">Retorna a quantidade de (Coletores de Fluxos) presente nesse (Coletor de mídia)</param>
			CarenResult ObterCountStreamSinks([Out] UInt32% Param_Out_QuantidadeSinks);

			/// <summary>
			/// Remove um coletor de fluxo do coletor de mídia.
			/// </summary>
			/// <param name="Param_IdentificadorFluxo">O Identificador do fluxo a ser removido.</param>
			CarenResult RemoverStreamSink(UInt32 Param_IdentificadorFluxo);

			/// <summary>
			/// Define o relógio de apresentação no coletor de mídia.
			/// </summary>
			/// <param name="Param_RelogioApresentação">A interface que contém o relógio de apresentação a ser definido.
			/// O valor pode ser (NULO). Se NULL, o (Coletor de Mídia) para de escutar o relógio de apresentação
			/// que foi definido anteriormente, se houver.</param>
			CarenResult DefinirRelogioApresentação(ICarenMFPresentationClock^ Param_RelogioApresentação);

			/// <summary>
			/// Desliga o coletor de mídia e libera os recursos que ele está usando.
			/// </summary>
			CarenResult DesligarColetor();
		};

		/// <summary>
		/// (IMFSinkWriterCallback) - Interface de retorno de chamada para o gravador de coletor(ICarenMFSinkWriter).
		/// </summary>
		[CategoryAttribute("IMFSinkWriterCallback - Interface de retorno de chamada para o gravador de coletor(ICarenMidiaSinkWriter).")]
		[Guid("1F2A9FB7-403A-477A-A781-A0F072FBE15C")]
		public interface class ICarenMFMediaSinkWriterCallback : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Delegates

			/// <summary>
			/// Delegate do evento OnFinalize.
			/// </summary>
			delegate void Delegate_OnFinalize(int Param_HResultCode);

			/// <summary>
			/// Delegate do evento OnMarker.
			/// </summary>
			delegate void Delegate_OnMarker(UInt32 Param_IdFluxo, ICaren^ Param_ObjetoContexto);




			//Eventos

			/// <summary>
			/// Evento chamado quando a operação assincrono do método (ICarenMFSinkWriter.Finalizar) é conlcuido.
			/// </summary>
			event Delegate_OnFinalize^ OnFinalize;

			/// <summary>
			/// Evento chamado quando a operação assincrono do método (ICarenMFSinkWriter.DefinirMarcadorFluxo) é conlcuido.
			/// </summary>
			event Delegate_OnMarker^ OnMarker;





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
		/// (IMFSinkWriter) - Implementado pelo objeto de gravador de coletor do Microsoft Media Foundation. Interface responsável por enviar os dados dos (Coletores de Mídia) para um Arquivo ou Hardware.
		/// Essa é a interface responsável por enviar amostras de Áudio para o Hardware de destino que vai reproduzir o Som.
		/// </summary>
		[CategoryAttribute("IMFSinkWriter - Gravador de coletor de dados de mídia.")]
		[Guid("37386B09-9CCD-4F48-B5D3-8A71C8B098F1")]
		public interface class ICarenMFSinkWriter : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// (AddStream) - Adiciona um fluxo para o gravador de coletor.
			/// </summary>
			/// <param name="Param_TipoMidia">Esse tipo de mídia especifica o formato das amostras que serão gravados no arquivo ou Hardware. 
			/// Ele não precisa corresponder ao formato de entrada. Para definir o formato de entrada, chame o método :
			/// DefinirTipoMidiaEntrada</param>
			/// <param name="Param_Out_IdFluxoAdicionado">Recebe o índice baseado em zero do novo fluxo.</param>
			CarenResult AdicionarFluxo(ICarenMFMediaType^ Param_TipoMidia, [Out] UInt32% Param_Out_IdFluxoAdicionado);

			/// <summary>
			/// (BeginWriting) - Inicializa o gravador de coletor para gravação.
			/// Chame esse método depois de configurar os fluxos de entrada e antes de enviar 
			/// os dados para o gravador de coletor.
			/// </summary>
			CarenResult InicializarEscrita();

			/// <summary>
			/// (Finalize) - Conclui todas as operações de gravação no gravador de coletor.
			/// </summary>
			CarenResult Concluir();

			/// <summary>
			/// (Flush) - Libera um ou mais fluxos.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo a ser liberado. Se (Param_TodosFluxos) for True, desconsidere esse valor.</param>
			/// <param name="Param_TodosFluxos">Define se deve liberar todos os fluxos deste escritor. Equivale ao valor: MF_SINK_WRITER_ALL_STREAMS</param>
			CarenResult Flush(UInt32 Param_IdFluxo, Boolean Param_TodosFluxos);

			/// <summary>
			/// (GetServiceForStream) - Consulta o coletor de mídia subjacente ou codificador para uma interface.
			/// </summary>
			/// <param name="Param_IdFluxo">Um Indice baseado em zero de um fluxo para a consulta. Desconsidere esse valor se o parâmetro (Param_Escritor)
			/// for True.</param>
			/// <param name="Param_ConsultarColetor">Define que o objeto de consulta é o Coletor de Mídia associado. Esse valor representa o: MF_SINK_WRITER_MEDIASINK</param>
			/// <param name="Param_GuidServiço">O Guid para o (Identificador de Serviço). Se o valor for (NULO), o método chama (QueryInterface) para obter
			/// interface solicitada.</param>
			/// <param name="Param_GuidInterfaceSolicitada">O Guid para a interface solicitada.</param>
			/// <param name="Param_Out_Interface">Recebe a interface solicitada. O usuário deve criar a interfaces antes de chamar este método.</param>
			CarenResult ObterServiçoParaStream(
				UInt32 Param_IdFluxo,
				Boolean Param_ConsultarColetor,
				String^ Param_GuidServiço,
				String^ Param_GuidInterfaceSolicitada,
				ICaren^ Param_Out_Interface);

			/// <summary>
			/// (GetStatistics) - Obtém estatísticas sobre o desempenho do gravador de coletor.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo de consulta. Se (Param_ConsularColetor) for True, desconsidere esse valor.</param>
			/// <param name="Param_ConsultarColetor">Define se deve obter as estatísticas do (Coletor de Mídia) propriamente dito.</param>
			/// <param name="Param_Out_StatusDesempenho">Retorna a estrutura que contém todas as informações de Desempenho </param>
			CarenResult ObterEstatisticasGravador(UInt32 Param_IdFluxo, Boolean Param_ConsultarColetor, [Out] Estruturas::CA_MIDIA_SINK_WRITER_ESTATISTICAS^% Param_Out_StatusDesempenho);

			/// <summary>
			/// (NotifyEndOfSegment) - Notifica o coletor de mídia que um fluxo atingiu o final de um segmento.
			/// </summary>
			/// <param name="Param_IdFluxo">O indica para o fluxo que vai ser notificado que foi atingido o final de um segmento. Desconsidere esse valor se (Param_NotificarTodos)
			/// for True.</param>
			/// <param name="Param_NotificarTodos">Indica que vai notificar que todos os fluxos atingiram o final de um segmento.</param>
			CarenResult NotificarFimSegmento(UInt32 Param_IdFluxo, Boolean Param_NotificarTodos);

			/// <summary>
			/// (TESTE)(PlaceMarker) - Coloca um marcador no fluxo especificado.
			/// Para usar esse método, você deve fornecer um retorno de chamada assíncrono quando você cria o Gravador de Coletor(ICarenMFSinkWriter).
			/// Caso contrario, o método retorna o código: ER_MF_REQUISICAO_INVALIDA
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo que vai ter o marcador adicionado.</param>
			/// <param name="Param_Valor">A interface que contém o valor desconhecido a ser definido.</param>
			CarenResult DefinirMarcadorFluxo(UInt32 Param_IdFluxo, ICaren^ Param_Valor);

			/// <summary>
			/// (SendStreamTick) - Indica uma lacuna em um fluxo de entrada.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
			/// <param name="Param_IdFluxo">A posição no fluxo onde ocorre a lacuna nos dados. O valor é fornecido em 100-nanosecond unidades, 
			/// em relação ao início do fluxo..</param>
			CarenResult EnviarLacunaFluxo(UInt32 Param_IdFluxo, Int64 Param_TimeStamp);

			/// <summary>
			/// (SetInputMediaType) - Define o Formatar de entrada para um fluxo no gravador de coletor.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo.</param>
			/// <param name="Param_TipoMidia">A interface que representa o tipo da mídia. O tipo de mídia especifica o 
			/// formato de entrada.</param>
			/// <param name="Param_ParametrosEncode">Use o repositório de atributos para configurar o codificador. 
			/// Este parâmetro pode ser nulo.</param>
			CarenResult DefinirTipoMidiaEntrada(UInt32 Param_IdFluxo, ICarenMFMediaType^ Param_TipoMidia, ICarenMFAttributes^ Param_ParametrosEncode);

			/// <summary>
			/// (WriteSample) - Fornece uma amostra para o gravador de coletor.
			/// Você deve chamar o método (InicializarEscrita) antes de chamar esse método. Caso contrário, o método retornará 
			/// o código: ER_MF_REQUISICAO_INVALIDA.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo para este exemplo.</param>
			/// <param name="Param_AmostraMidia">A interface que contém a amostra a ser escrita.</param>
			CarenResult EscreverAmostra(UInt32 Param_IdFluxo, ICarenMFSample^ Param_AmostraMidia);

		};

		/// <summary>
		/// (IMFSourceReaderCallback) - Representa a interface utilizada para receber os eventos gerados pelo Leitor de Midia e alguns eventos da Fonte de Midia.
		/// </summary>
		[CategoryAttribute("IMFSourceReaderCallback - Interface que recebe eventos do leitor de mídia.")]
		[Guid("B62DD692-4317-4D5C-8DDF-FB53E7C13A93")]
		public interface class ICarenMFSourceReaderCallback : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			/// <summary>
			/// Propriedade que vai força  o coletor de lixo agir para liberar interfaces em conclusões de eventos.
			/// Por padrão, o valor é falso.
			/// </summary>
			property Boolean ColetarLixoEvento
			{
				virtual Boolean get();
				virtual void set(Boolean value);
			}


			//Delegates utilizados pela Interface.

			/// <summary>
			/// Delegate do evento OnReadSample.
			/// </summary>
			delegate void Delegate_OnReadSample(int Param_HResult, ResultCode Param_ResultadoGeral, Enumeracoes::CA_AMOSTRA_RESULTADO Param_ResultadoLeitura, Enumeracoes::CA_SOURCE_READER_FLAGS Param_FlagsLeituraAmostra, UInt32 Param_IdFluxo, UInt64 Param_TimeSpan, ICarenMFSample^ Param_Amostra);

			/// <summary>
			/// Delegate do evento OnFlush.
			/// </summary>
			delegate void Delegate_OnFlush(UInt32 Param_FluxoID);

			/// <summary>
			/// Delegate do evento OnEvent.
			/// </summary>
			delegate void Delegate_OnEvent(UInt32 Param_FluxoID, ICarenMFMediaEvent^ Param_CarenMidiaEvent);


			//Define os eventos

			/// <summary>
			/// Evento chamado quando o método (ICarenMFSourceReader.LerAmostraAsync) é concluido.
			/// </summary>
			event Delegate_OnReadSample^ OnReadSample;

			/// <summary>
			/// Evento chamado quando o método (ICarenMFSourceReader.Flush) é completado.
			/// </summary>
			event Delegate_OnFlush^ OnFlush;

			/// <summary>
			/// Evento chamado quando o Leitor de Midia recebe determinados eventos da Fonte de Midia.
			/// </summary>
			event Delegate_OnEvent^ OnEvent;


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
		/// (IMFSourceReader) - Representa um leitor de midia. Essa interface é responsável por decodificar e ler as amostras de midia(IMFSample), que são representadas pela
		/// interface (ICarenMFSample).
		/// </summary>
		[CategoryAttribute("IMFSourceReader - Leitor de midia.")]
		[Guid("70F77178-5F15-4279-8322-979DE274790E")]
		public interface class ICarenMFSourceReader : ICaren, ICarenLeitorMidiaExtensões
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// Obtém o tipo de mídia atual para um fluxo.
			/// </summary>
			/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
			/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
			CarenResult ObterTipoMidiaAtual(UInt32 Param_IdFluxo, [Out] ICarenMFMediaType^% Param_Out_TipoMidia);

			/// <summary>
			/// Obtém um formato que é suportado nativamente pelo fonte de mídia.
			/// Este método consulta a fonte de mídia subjacente para seu (Formato) de (Saída Nativo). 
			/// Potencialmente, cada fluxo de origem pode produzir mais de um formato de saída. 
			/// Use o parâmetro Param_IdMediaTypeIndice para percorrer os formatos disponíveis
			/// </summary>
			/// <param name="Param_IdFluxo">O fluxo de consulta. Você pode utilizar a enumeração (CA_SOURCE_READER_ID) para força o Leitor a obter o primeiro fluxo de áudio ou vídeo na lista.</param>
			/// <param name="Param_IdMediaTypeIndice">O Id para o tipo de mídia na lista a ser obtida. O valor pode ser qualquer um dos seguintes. Indice baseado em 0 ou o valor: 0xffffffff que representa o tipo da mídia nativa atual. </param>
			/// <param name="Param_Out_TipoMidia">Retorna o tipo da midia no Id especificado.</param>
			CarenResult ObterTipoMidiaNativa(UInt32 Param_IdFluxo, UInt32 Param_IdMediaTypeIndice, [Out] ICarenMFMediaType^% Param_Out_TipoMidia);

			/// <summary>
			/// Obtém um determinado atributo da fonte de mídia atual.
			/// </summary>
			/// <param name="Param_IdFluxo">O fluxo ou objeto de consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID) para espeficar um valor padrão ao sistema.</param>
			/// <param name="Param_GuidAtributo">Um GUID que identifica o atributo para recuperar. Se o Param_IdFluxo parâmetro é igual a ID_FONTE_MIDIA, 
			/// Param_GuidAtributo pode especificar os atributos de: MFAtributos_DescritorApresentação, MF_SOURCE_READER_MEDIASOURCE_CHARACTERISTICS.
			/// Se Param_IdFluxo espeficifica um Fluxo, Param_GuidAtributo deve especificar um atributo do Descritor de Fluxo(GUIDs_MFAtributos_DescritorFluxo) </param>
			/// <param name="Param_Out_ValorAtributo">Retorna o valor do atributo solicitado</param>
			CarenResult ObterAtributoApresentacao(UInt32 Param_IdFluxo, String^ Param_GuidAtributo, [Out] Estruturas::CA_PropVariant^% Param_Out_ValorAtributo);

			/// <summary>
			/// () - Consulta a fonte subjacente de mídia ou decodificador para uma interface.
			/// </summary>
			/// <param name="Param_IdFluxo">O fluxo ou objeto para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID). Se o valor for ID_FONTE_MIDIA, 
			/// o método consultará a fonte de mídia. Caso contrário, ele consulta o decodificador que está associado com o fluxo especificado.</param>
			/// <param name="Param_GuidServiço">Um identificador de serviço GUID, consulte a estrutura(MFInterfacesServiço) para  obter um GUID. Se o valor for (NULO), 
			/// o método chama (ConsultarInterface) para obter a interface solicitada. Caso contrário, o método chama o ICarenMFGetService.ObterServiço.</param>
			/// <param name="Param_GuidInterface">O identificador de interface (IID) da interface que está sendo solicitada..</param>
			/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface que foi solicitada. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ObterServiceParaFluxo(UInt32 Param_IdFluxo, String^ Param_GuidServiço, String^ Param_GuidInterface, ICaren^ Param_Out_InterfaceDesconhecida);

			/// <summary>
			/// Consulta se um determinado fluxo, baseado em seu (Id) está selecionado.
			/// </summary>
			/// <param name="Param_IdFluxo">O Fluxo para consulta. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			/// <param name="Param_Out_ResultadoFluxoSelecionado">Recebe true se o fluxo é selecionado e irá gerar dados. Recebe false se o fluxo não está selecionado 
			/// e não irá gerar dados.</param>
			CarenResult ConsultarFluxoSelecionado(UInt32 Param_IdFluxo, [Out] Boolean% Param_Out_ResultadoFluxoSelecionado);

			/// <summary>
			/// Método responsável por ler a proxima amostra de mídia disponivel na fonte de mídia.
			/// Esse método pode retornar (Sucesso) e ainda assim retornar uma amostra de mídia (NULA).
			/// Consulte o resultado do parametro (Param_Out_FlagsLeituraAmostra) que vai indicar o resultado da leitura e o que se deve fazer.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id do fluxo que vai extrair os dados de mídia. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			/// <param name="Param_ControlFlag">Um flag para realizar a leitura da amostra de mídia. Pode deixar Zero, ou definir um valor da enumeração(CA_SOURCE_READER_CONTROL_FLAG)</param>
			/// <param name="Param_Out_ResultadoLeitura">Retorna o resultado da leitura de uma amostra.</param>
			/// <param name="Param_Out_IdFluxoLido">Retorna o Id do fluxo que foi extraido a amostra de mídia.</param>
			/// <param name="Param_Out_FlagsLeituraAmostra">Retorna um (Flag) que indca um resultado adicional a leitura da amostra. Utilize essa valor para decidir como deve processar o resultado do método.</param>
			/// <param name="Param_Out_TimSpanAmostra">Retorna o (TimeSpan) da amostra de mídia lida. TimeSpan indica a Data/Hora que deve iniciar uma amostra. Esse valor é dado em (unidades de 100 Nanosegundos).</param>
			/// <param name="Param_Out_Amostra">Retorna a interface que contém a amostra de mídia que foi lida.</param>
			CarenResult LerAmostra
			(
				UInt32 Param_IdFluxo,
				UInt32 Param_ControlFlag,
				[Out] Enumeracoes::CA_AMOSTRA_RESULTADO% Param_Out_ResultadoLeitura,
				[Out] UInt32% Param_Out_IdFluxoLido,
				[Out] Enumeracoes::CA_SOURCE_READER_FLAGS% Param_Out_FlagsLeituraAmostra,
				[Out] Int64% Param_Out_TimSpanAmostra,
				[Out] ICarenMFSample^% Param_Out_Amostra
			);

			/// <summary>
			/// Método responsável por ler a proxima amostra de mídia disponivel na fonte de mídia de modo assincrono.
			/// Esse método retorna imediatamente após a chamada.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id do fluxo que vai extrair os dados de mídia. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			/// <param name="Param_ControlFlag">Um flag para realizar a leitura da amostra de mídia. Pode deixar Zero, ou definir um valor da enumeração(CA_SOURCE_READER_CONTROL_FLAG)</param>
			CarenResult LerAmostraAsync
			(
				UInt32 Param_IdFluxo,
				UInt32 Param_ControlFlag
			);

			/// <summary>
			/// Define o tipo de mídia para um fluxo.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo a ter o tipo de mídia definido. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			/// <param name="Param_ValorReservado">Valor reservado. Define como: 0</param>
			/// <param name="Param_TipoMidia">A interface com o (Tipo Mídia) a ser definida como o tipo atual.</param>
			CarenResult DefinirTipoMidiaAtual(UInt32 Param_IdFluxo, UInt32 Param_ValorReservado, ICarenMFMediaType^ Param_TipoMidia);

			/// <summary>
			/// Define uma nova posição para ler as amostras de midia com base no tempo de apresentação.
			/// Como o valor da posição é em unidades de 100 nanosegundos, 1 segundo é representado por 10^7(10 elevado a 7 potência).
			/// </summary>
			/// <param name="Param_PosiçãoNanoSegundos">A posição para leitura dos dados. O valor é dado em unidades de 100 nanosegundos.</param>
			CarenResult DefinirPosicaoLeitura(Int64 Param_PosiçãoNanoSegundos);

			/// <summary>
			/// Seleciona ou Desseleciona um ou mais fluxos.
			/// [ATENÇÃO] - Se você (não vai precisar) de (dados) de um dos (Fluxos), é uma boa ideia para cancelar a seleção desse fluxo. Se o fluxo for 
			/// seleccionado, a fonte de mídia pode segurar uma fila de dados não lidos, e a fila pode crescer indefinidamente, consumindo memória,
			/// consequentemente, gerando um Vazamento de Memória(Memory Leak).
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo a ser selecionado. Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			/// <param name="Param_EstadoSeleção">Define se deve (Selecionar) ou (Desselecionar) o fluxo especificado.</param>
			CarenResult DefinirEstadoSelecaoFluxo(UInt32 Param_IdFluxo, Boolean Param_EstadoSeleção);

			/// <summary>
			/// Libera um ou mais fluxos.
			/// </summary>
			/// <param name="Param_IdFluxo">O Id para o fluxo a ser (Liberado). Você pode utilizar a enumeração(CA_SOURCE_READER_ID).</param>
			CarenResult Flush(UInt32 Param_IdFluxo);
		};

		/// <summary>
		/// (IMFTransform) - MFTs (Media Foundation Transforms) fornecem um modelo genérico para o processamento de dados de mídia. MFTs são usados para decodificadores, 
		/// codificadores e processadores de sinais digitais (DSPs). Em suma, tudo o que fica na mídia pipleine entre a fonte de mídia e o coletor de mídia é uma MFT.
		/// </summary>
		[CategoryAttribute("IMFTransform - Implementado por todos os objetos de tranformação de mídia do (Media Foundation).")]
		[Guid("D443AE42-007A-4866-8174-8EE4EAC215AF")]
		public interface class ICarenMFTransform : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}


			//Métodos.

			/// <summary>
			/// (AddInputStreams) - Adiciona um ou mais novos fluxos de entrada a esta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_Quantidade">Quantidade de fluxos a serem adicionados.</param> 
			/// <param name="Param_ArrayIdentificadores">Matriz de identificadores de fluxo. Os novos identificadores de fluxo não devem corresponder a nenhum fluxo de entrada existente.</param> 
			CarenResult AdicionarFluxosEntrada(UInt32 Param_Quantidade, cli::array<UInt32>^ Param_ArrayIdentificadores);

			/// <summary>
			/// (DeleteInputStream) - Remove um fluxo de entrada desta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_FluxoID"> O Id do fluxo a ser removido.</param>
			CarenResult DeletarFluxoEntrada(UInt32 Param_FluxoID);

			/// <summary>
			/// (GetAttributes ) - Recebe a loja global de atributos para esta transformação da Media Foundation (MFT).
			/// Use o ponteiro recuperado por este método para obter ou definir atributos que se aplicam a todo o MFT.
			/// </summary>
			/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface de atributos. O chamdor deve liberar a interface.</param>
			CarenResult ObterAtributos([Out] ICarenMFAttributes^% Param_Out_Atributos);

			/// <summary>
			/// (GetInputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
			/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
			CarenResult ObterTipoFluxoEntradaDisponivel(UInt32 Param_IDFluxoEntrada, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

			/// <summary>
			/// (GetInputCurrentType) - Obtém o tipo de mídia atual para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_InterfaceTipoMidia">Recebe um ponteiro para a interface ICarenMFMediaType.</param>
			CarenResult ObterTipoFluxoEntradaAtual(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

			/// <summary>
			/// (GetInputStatus) - Consulta se um fluxo de entrada nesta transformação da Media Foundation (MFT) pode aceitar mais dados.
			/// Se o método retornar a bandeira CA_MFT_INPUT_STATUS_ACCEPT_DATA, você pode fornecer uma amostra de entrada para o fluxo 
			/// especificado ligando para ICarenMFTransform::ProcessarEntrada. Se o método for bem sucedido, mas não devolver nenhuma 
			/// bandeira no parâmetro Param_Out_Flag, significa que o fluxo de entrada já tem o máximo de dados que pode aceitar.
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_INPUT_STATUS_FLAGS, ou zero. Se o valor for CA_MFT_INPUT_STATUS_ACCEPT_DATA, o fluxo especificado 
			/// no Param_IDFluxoEntrada pode aceitar mais dados de entrada.</param>
			CarenResult ObterStatusEntrada(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STATUS_FLAGS% Param_Out_Flag);

			/// <summary>
			/// (GetInputStreamAttributes) - Recebe a loja de atributos para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
			CarenResult ObterAtributosFluxoEntrada(UInt32 Param_IDFluxoEntrada, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo);

			/// <summary>
			/// (GetInputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_INPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de entrada.</param>
			CarenResult ObterInfoFluxoEntrada(UInt32 Param_IDFluxoEntrada, [Out] CA_MFT_INPUT_STREAM_INFO^% Param_Out_InfoFluxo);

			/// <summary>
			/// (GetOutputAvailableType) - Obtém um tipo de mídia disponível para um fluxo de saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_TipoID">Índice do tipo mídia para recuperar. Os tipos de mídia são indexados a partir de zero e devolvidos em ordem aproximada de preferência.</param>
			/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
			CarenResult ObterTipoFluxoSaidaDisponivel(UInt32 Param_IDFluxoSaida, UInt32 Param_TipoID, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

			/// <summary>
			/// (GetOutputCurrentType) - Obtém o tipo de mídia atual para um fluxo de saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_InterfaceTipoMidia">Recebe uma interface de tipo de midia. O chamador deve liberar a interface.</param>
			CarenResult ObterTipoFluxoSaidaAtual(UInt32 Param_IDFluxoSaida, [Out] ICarenMFMediaType^% Param_Out_InterfaceTipoMidia);

			/// <summary>
			/// (GetOutputStatus) - Questiona se a transformação da Media Foundation (MFT) está pronta para produzir dados de produção.
			/// Se o método devolver a bandeira CA_MFT_OUTPUT_STATUS_SAMPLE_READY, significa que você pode gerar uma ou mais amostras de produção ligando 
			/// para o ICarenMFTransform::ProcessarSaida.
			/// </summary>
			/// <param name="Param_Out_Flag">Recebe um membro da enumeração CA_MFT_OUTPUT_STATUS_FLAGS, ou zero. Se o valor for MFT_OUTPUT_STATUS_SAMPLE_READY, o MFT pode produzir 
			/// uma amostra de saída.</param>
			CarenResult ObterStatusSaida([Out] CA_MFT_OUTPUT_STATUS_FLAGS% Param_Out_Flag);

			/// <summary>
			/// (GetOutputStreamAttributes) - Recebe a loja de atributos para um fluxo de saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_AtributosFluxo">Retorna uma interface de atributos para o fluxo informado. O chamador é responsável por liberar a interface.</param>
			CarenResult ObterAtributosFluxoSaida(UInt32 Param_IDFluxoSaida, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxo);

			/// <summary>
			/// (GetOutputStreamInfo) - Obtém os requisitos de buffer e outras informações para um fluxo de saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Out_InfoFluxo">Recebe uma estrutura CA_MFT_OUTPUT_STREAM_INFO. O método preenche a estrutura com informações sobre o fluxo de saida.</param>
			CarenResult ObterInfoFluxoSaida(UInt32 Param_IDFluxoSaida, [Out] CA_MFT_OUTPUT_STREAM_INFO^% Param_Out_InfoFluxo);

			/// <summary>
			/// (GetStreamCount) - Obtém o número atual de fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_Out_FluxoEntrada">Retorna a quantidade de fluxos de entrada.</param>
			/// <param name="Param_Out_FluxoSaida">Retorna a quantidade de fluxos de saida.</param>
			CarenResult ObterQuantidadeFluxos([Out] UInt32% Param_Out_FluxoEntrada, [Out] UInt32% Param_Out_FluxoSaida);

			/// <summary>
			/// (GetStreamIDs) - Obtém os identificadores de fluxo para os fluxos de entrada e saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_SizeMatrizFluxosEntrada">O tamanho da matriz que vai conter os IDs dos fluxos de entrada.</param>
			/// <param name="Param_MatrizFluxosEntrada">Uma matriz que vai receber todos os identificadores de fluxos de Entrada. O chamador é responsável por criar a matriz. 
			/// Chame o método ICarenMFTransform::ObterQuantidadeFluxos para descobrir o tamanho que deve ser essa matriz.</param>
			/// <param name="Param_SizeMatrizFluxosSaida">O tamanho da matriz que vai conter os IDs dos fluxos de Saida.</param>
			/// <param name="Param_MatrizFluxosSaida">Uma matriz que vai receber todos os identificadores de fluxos de Saida. O chamador é responsável por criar a matriz. 
			/// Chame o método ICarenMFTransform::ObterQuantidadeFluxos para descobrir o tamanho que deve ser essa matriz.</param>
			CarenResult ObterIDsFluxo(
				UInt32 Param_SizeMatrizFluxosEntrada, 
				cli::array<UInt32>^% Param_MatrizFluxosEntrada,  //REF
				UInt32 Param_SizeMatrizFluxosSaida, 
				cli::array<UInt32>^% Param_MatrizFluxosSaida);   //REF

			/// <summary>
			/// (GetStreamLimits) - Obtém o número mínimo e máximo de fluxos de entrada e saída para esta transformação da Media Foundation (MFT).
			/// Se o MFT tiver um número fixo de fluxos, os valores mínimos e máximos são os mesmos.
			/// </summary>
			/// <param name="Param_Out_FluxoEntradaMinimo">Recebe o número mínimo de fluxos de entrada.</param>
			/// <param name="Param_Out_FluxoEntradaMaximo">Recebe o número máximo de fluxos de entrada. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
			/// <param name="Param_Out_FluxoSaidaMinimo">Recebe o número mínimo de fluxos de saída.</param>
			/// <param name="Param_Out_FluxoSaidaMaximo">Recebe o número máximo de fluxos de saída. Se não houver no máximo, recebe o valor MFT_STREAMS_UNLIMITED.</param>
			CarenResult ObterLimitesFluxos(
				[Out] UInt32% Param_Out_FluxoEntradaMinimo, 
				[Out] UInt32% Param_Out_FluxoEntradaMaximo,
				[Out] UInt32% Param_Out_FluxoSaidaMinimo,
				[Out] UInt32% Param_Out_FluxoSaidaMaximo);

			/// <summary>
			/// (ProcessEvent) - Envia um evento para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Evento">Um ponteiro para a interface de eventos(ICarenMFMediaEvent).</param>
			CarenResult ProcessarEvento(UInt32 Param_IDFluxoEntrada, ICarenMFMediaEvent^ Param_Evento);

			/// <summary>
			/// (ProcessInput) - Fornece dados para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// Na maioria dos casos, se o método for bem sucedido, o MFT armazena a amostra e mantém uma contagem de referência no ponteiro ICarenMFSample. 
			/// Não reutilize a amostra até que o MFT libere a amostra. Em vez de armazenar a amostra, no entanto, um MFT pode copiar os dados da amostra em um novo buffer. 
			/// Nesse caso, o MFT deve definir a bandeira MFT_INPUT_STREAM_DOES_NOT_ADDREF no método ICarenMFTransform::ObterInfoFluxoEntrada.
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_Amostra">Um ponteiro para a interface de amostra de midia. A amostra deve conter pelo menos um Buffer de mídia que contém dados de entrada válidos.</param>
			/// <param name="Param_Flags">Reservado. Deixe como zero.</param>
			CarenResult ProcessarEntrada(UInt32 Param_IDFluxoEntrada, ICarenMFSample^ Param_Amostra, UInt32 Param_Flags);

			/// <summary>
			/// (ProcessMessage) - Envia uma mensagem para a Transformação da Fundação de Mídia (MFT).
			/// </summary>
			/// <param name="Param_Mensagem">A mensagem a enviar, especificada como membro da enumeração CA_MFT_MESSAGE_TYPE.</param>
			/// <param name="Param_ulPram">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
			CarenResult ProcessarMensagem(CA_MFT_MESSAGE_TYPE Param_Mensagem, UInt32 Param_ulPram);
			
			/// <summary>
			/// (ProcessOutput) - Gera saída a partir dos dados de entrada atuais.
			/// </summary>
			/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_FLAGS.</param>
			/// <param name="Param_QuantidadeElementos">Número de elementos na matriz (Param_MatrizBuffersSaida). O valor deve ser de pelo menos 1.</param>
			/// <param name="Param_MatrizBuffersSaida">Uma matriz de estruturas CA_MFT_OUTPUT_DATA_BUFFER. O MFT usa este array para devolver dados de saída ao chamador.</param>
			/// <param name="Param_Out_Status">Recebe zero ou mais bandeiras da enumeração CA_MFT_PROCESS_OUTPUT_STATUS.</param>
			CarenResult ProcessarSaida(
				CA_MFT_PROCESS_OUTPUT_FLAGS Param_Flags, 
				UInt32 Param_QuantidadeElementos, 
				cli::array<CA_MFT_OUTPUT_DATA_BUFFER^>^% Param_MatrizBuffersSaida, //REF
				[Out] CA_MFT_PROCESS_OUTPUT_STATUS% Param_Out_Status);

			/// <summary>
			/// (SetInputType) - Define, testa ou limpa o tipo de mídia para um fluxo de entrada nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoEntrada">Identificador de fluxo de Entrada. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
			/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
			CarenResult DefinirTipoFluxoEntrada(
				UInt32 Param_IDFluxoEntrada, 
				ICarenMFMediaType^ Param_TipoMidiaFluxo, 
				CA_MFT_SET_TYPE_FLAGS Param_Flags);

			/// <summary>
			/// (SetOutputBounds) - Define a gama de carimbos de tempo que o cliente precisa para a saída.
			/// </summary>
			/// <param name="Param_HorarioAntigo">Especifica o carimbo de horário mais antigo. A Transformação da Media Foundation (MFT) aceitará a entrada até que possa produzir uma 
			/// amostra de saída que começa neste momento; ou até que possa produzir uma amostra que termina neste momento ou mais tarde. Se não houver limite inferior, use o 
			/// valor MFT_OUTPUT_BOUND_LOWER_UNBOUNDED(0).</param>
			/// <param name="Param_HorarioMaior">Especifica o último carimbo de tempo. O MFT não produzirá uma amostra de saída com carimbos de tempo mais tarde do que desta vez. Se 
			/// não houver limite superior, use o valor MFT_OUTPUT_BOUND_UPPER_UNBOUNDED(-1).</param>
			CarenResult DefinirLimiteSaida(Int64 Param_HorarioAntigo, Int64 Param_HorarioMaior);
			
			/// <summary>
			/// (SetOutputType) - Define, testa ou limpa o tipo de mídia para um fluxo de saída nesta transformação da Media Foundation (MFT).
			/// </summary>
			/// <param name="Param_IDFluxoSaida">Identificador de fluxo de Saida. Para obter a lista de identificadores de fluxo, ligue para ICarenMFTransform::ObterIDsFluxo.</param>
			/// <param name="Param_TipoMidiaFluxo">Um ponteiro para a interface ICarenMFMediaType ou NULO.</param>
			/// <param name="Param_Flags">Zero ou mais flags da enumeração CA_MFT_SET_TYPE_FLAGS.</param>
			CarenResult DefinirTipoFluxoSaida(
				UInt32 Param_IDFluxoSaida,
				ICarenMFMediaType^ Param_TipoMidiaFluxo,
				CA_MFT_SET_TYPE_FLAGS Param_Flags);
		};

		/// <summary>
		/// (IMFVideoMediaType)(Preterido) - Representa uma descrição de um formato de vídeo. Os aplicativos devem evitar o uso desta interface, exceto quando um método ou função requer um 
		/// ponteiro para ICarenMFVideoMediaType como parâmetro. Você pode obter todas as informações de formato de um tipo de mídia de vídeo através da interface ICarenMFAttributes, 
		/// que o ICarenMFMediaType herda.
		/// </summary>
		[CategoryAttribute("IMFVideoMediaType - Descreve um formato de video.")]
		[Guid("5C45B3A5-2B27-4C0D-AA9D-736AA765F9F0")]
		public interface class ICarenMFVideoMediaType : ICarenMFMediaType
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}


			//Os métodos desta interface estão preteridos.
			//Deve adicionar apenas os métodos herdados da ICarenMFMediaType
		};

		/// <summary>
		/// (IMFVideoPresenter) - Interface responsável por representar um apresentador de vídeo. Está interface recebe quadros de vídeo, normalmente de um mixer de 
		/// vídeo, e os apresenta de alguma forma, geralmente exibindo-os no visor. O renderizador de vídeo aprimorado (EVR) fornece um apresentador de vídeo padrão e os aplicativos podem 
		/// implementar apresentadores personalizados. Geralmente, o usuário não cria essa interface diretamente. Consulte essa interface no EVR.
		/// </summary>
		[CategoryAttribute("IMFVideoPresenter - Apresentado de vídeo utilizado pelo EVR.")]
		[Guid("C2FA308B-3962-4F6F-8CC7-C2D2641E3BFA")]
		public interface class ICarenMFVideoPresenter : ICarenMFClockStateSink
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}

			//Métodos

			/// <summary>
			/// Recupera o tipo de mídia do apresentador. 
			/// Este método retorna o tipo de mídia que o apresentador define para o tipo de saída do misturador. Descreve o formato da imagem composta.
			/// </summary>
			/// <param name="Param_Out_TipoVideo">Retorna uma interface para o tipo de midia de video do apresentador.</param>
			/// <returns></returns>
			CarenResult ObterTipoMidiaAtual([Out] ICarenMFVideoMediaType^% Param_Out_TipoVideo);

			/// <summary>
			/// Envia uma mensagem para o apresentador de vídeo. As mensagens são usadas para sinalizar ao apresentador que ele deve realizar alguma ação, ou que algum evento ocorreu.
			/// </summary>
			/// <param name="Param_Mensagem">Especifica a mensagem como membro da enumeração CA_MFVP_MESSAGE_TYPE.</param>
			/// <param name="Param_UlParam">Parâmetro de mensagem. O significado deste parâmetro depende do tipo de mensagem.</param>
			/// <returns></returns>
			CarenResult ProcessarMensagem(CA_MFVP_MESSAGE_TYPE Param_Mensagem, UInt64 Param_UlParam);
		};

		/// <summary>
		/// (IMFVideoRenderer) - Representa o EVR(Renderizador de Vídeo Aprimorado). Está é a interface responsável pelo processamento de Vídeo.
		/// Essa interface é geralmente adquiridada atravez do IMFMediaSink, representado pela interface (ICarenMFMediaSink).
		/// </summary>
		[CategoryAttribute("IMFVideoRenderer - (EVR)Renderizador de Video Aprimorado.")]
		[Guid("E23C9042-83C2-4B7F-B237-F888C3DE84E1")]
		public interface class ICarenMFVideoRenderer : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}


			/// <summary>
			/// Define um novo mixer ou apresentador para o EVR.
			/// Os parametros do método podem ser (nulos). Se nulos, o EVR usará os componentes padrões.
			/// </summary>
			/// <param name="Param_MFT">A interface IMFTransform, representa por (ICarenMFT) para o (Mixer) do EVR poder usar . Este parâmetro pode ser (NULO). Se este parâmetro for (NULO), o EVR usa seu (Mixer Padrão).</param>
			/// <param name="Param_ApresentadorVideo">A interface IMFVideoPresenter, representa por (ICarenMFVideoPresenter). Este parâmetro pode ser (NULO). Se este parâmetro for (NULO), o EVR usa seu (Apresentador Padrão).</param>
			CarenResult InicializarRenderizador(ICarenMFTransform^ Param_MFT, ICarenMFVideoPresenter^ Param_ApresentadorVideo);
		};

		/// <summary>
		/// (IMFVideoDisplayControl) - Interface responsável por controlar como o Vídeo é exbido pelo EVR (Renderizador de Vídeo Aprimorado).
		/// Essa interface é um Serviço do EVR, exposto para o usuário.
		/// </summary>
		[CategoryAttribute("IMFVideoDisplayControl  - Controla como o vídeo é exebido.")]
		[Guid("494723EC-8E10-4E29-BCF9-9A9F072ADE51")]
		public interface class ICarenMFVideoDisplayControl : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				Boolean get();
			}


			/// <summary>
			/// (GetAspectRatioMode) - Consulta como o processador de vídeo avançado (EVR) lida com a relação de aspecto da fonte de vídeo.
			/// </summary>
			/// <param name="Param_Out_AspectRatio">Recebe um ou mais bit de sinalizadores da enumeração: CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE</param>
			CarenResult ObterAspectRatio([Out] Enumeracoes::CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE% Param_Out_AspectRatio);

			/// <summary>
			/// (GetBorderColor) - Obtém a cor da borda para o vídeo.
			/// </summary>
			/// <param name="Param_Out_CorHexadecimalBorda">Recebe o valor que especifica em hexadecimal, uma cor RGB.</param>
			CarenResult ObterCorBorda([Out] UInt32% Param_Out_CorHexadecimalBorda);

			/// <summary>
			/// (GetCurrentImage) - Obtém uma cópia da imagem atual sendo exibida pelo processador de vídeo.
			/// </summary>
			/// <param name="Param_Out_BimapInfoHeader">Recebe uma estrutura que contém uma descrição do bitmap</param>
			/// <param name="Param_Out_BufferImagem">Interface que contém um buffer que contém um bitmap independente de dispositivo do Windows compactado (DIB).
			/// O chamador deve liberar a memória para o bitmap chamando: CoTaskMemFree </param>
			/// <param name="Param_Out_BufferLargura">Contém a largura do buffer retornado em: Param_Out_BufferImagem.</param>
			/// <param name="Param_Out_TimeStamp">Recebe o carimbo de data/hora da imagem capturada. O valor é em unidades de 100 nanosegundos.</param>
			CarenResult ObterCopiaImagemAtual(
				[Out] Estruturas::CA_BITMAP_INFO_HEADER^% Param_Out_BimapInfoHeader,
				[Out] ICarenBuffer^% Param_Out_BufferImagem,
				[Out] UInt32% Param_Out_BufferLargura,
				[Out] Int64% Param_Out_TimeStamp);

			/// <summary>
			/// (GetFullscreen) - Consulta se o processador de vídeo avançado (EVR) está atualmente no modo de tela cheia.
			/// </summary>
			/// <param name="Param_Out_FullScreen">Recebe o valor que define se o vídeo está sendo renderizado em FullScreen.</param>
			CarenResult ObterEstadoFullScreen([Out] Boolean% Param_Out_FullScreen);

			/// <summary>
			/// (GetIdealVideoSize) - Obtém o intervalo de tamanhos, que o processador de vídeo avançado (EVR) pode exibir sem degradar 
			/// significativamente a qualidade de imagem ou o desempenho.
			/// </summary>
			/// <param name="Param_Out_Minimo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Minimos) da Largura e Altura (Ideias) para o vídeo.</param>
			/// <param name="Param_Out_Maximo_VideoSizeIdeal">Recebe a estrutura que contém os valores (Maximos) da Largura e Altura (Ideias) para o vídeo.</param>
			CarenResult ObterSizeIdealVideo(
				[Out] Estruturas::CA_SIZE^% Param_Out_Minimo_VideoSizeIdeal,
				[Out] Estruturas::CA_SIZE^% Param_Out_Maximo_VideoSizeIdeal);

			/// <summary>
			/// (GetNativeVideoSize) - Obtém o tamanho e a taxa de proporção do vídeo, antes de qualquer alongamento pelo (Processador de Vídeo).
			/// </summary>
			/// <param name="Param_Out_VideoSize">Recebe a estrutura que contém a Largura e Altura (Nativas) para o vídeo.</param>
			/// <param name="Param_Out_TaxaProporcaoVideo">Recebe a estrutura que contém a (Taxa de proporção) do vídeo.</param>
			CarenResult ObterSizeNativoVideo(
				[Out] Estruturas::CA_SIZE^% Param_Out_VideoSize,
				[Out] Estruturas::CA_SIZE^% Param_Out_TaxaProporcaoVideo);

			/// <summary>
			/// (GetRenderingPrefs) - Obtém várias configurações de processamento de vídeo.
			/// </summary>
			/// <param name="Param_Out_Sinalizadores">Recebe um bit ou zero ou mais sinalizadores da enumeração: CA_VIDEO_RENDER_CONFIGURACOES</param>
			CarenResult ObterConfiguraçãoRenderização([Out] Enumeracoes::CA_VIDEO_RENDER_CONFIGURACOES% Param_Out_Sinalizadores);

			/// <summary>
			/// (GetVideoPosition) - Obtém os retângulos de origem e de destino para o Vídeo.
			/// </summary>
			/// <param name="Param_Out_RetanguloNormalized">Recebe uma estrutura que contém o retângulo de origem.</param>
			/// <param name="Param_Out_RetanguloDestino">Recebe uma estrutura com o retângulo de destino atual.</param>
			CarenResult ObterPosiçãoVideo(
				[Out] Estruturas::CA_Retangulo_Normalizado^% Param_Out_RetanguloNormalized,
				[Out] Estruturas::CA_Retangulo^% Param_Out_RetanguloDestino);

			/// <summary>
			/// (GetVideoWindow) - Obtém a janela de recorte para o vídeo. A janela de recorte é a (Handle) do componente que está
			/// hospedando a renderização do vídeo para o usuário.
			/// </summary>
			/// <param name="Param_Out_HandleJanela">Recebe a handle da janela que a qual o vídeo está sendo renderizado.</param>
			CarenResult ObterJanelaVideo([Out] IntPtr% Param_Out_HandleJanela);

			/// <summary>
			/// (RepaintSuperfice) - Redesenha o quadro de vídeo atual. Chame esse método sempre que a interface do usuário
			/// sofre uma atualização da interface.
			/// </summary>
			CarenResult RedesenharSuperfice();

			/// <summary>
			/// (SetAspectRatioMode) - Especifica como o processador de vídeo avançado (EVR) lida com a relação de aspecto 
			/// da fonte de vídeo.
			/// </summary>
			/// <param name="Param_AspectRatio">Bit a bit ou de um ou mais sinalizadores da enumeração: CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE</param>
			CarenResult DefinirModoAspectRatio(Enumeracoes::CA_VIDEO_DISPLAY_ASPECT_RATIO_MODE Param_AspectRatio);

			/// <summary>
			/// (SetBorderColor) - Define a cor da borda para o vídeo.
			/// </summary>
			/// <param name="Param_ColorRef">Especifica a cor da borda como um valor UInt32</param>
			CarenResult DefinirCorBorda(UInt32 Param_ColorRef);

			/// <summary>
			/// [Esta API não é suportada e pode ser alterada ou indisponível no futuro.]
			/// (SetFullScreen) - Define o modo de renderização de tela cheia.
			/// Para implementar a reprodução em tela inteira, um aplicativo deve simplesmente redimensionar a janela de vídeo para cobrir toda a área do monitor.Também definir a janela
			/// para ser uma (Janela Superior), para que o aplicativo possa receber todas as mensagens de clique do mouse.
			/// </summary>
			/// <param name="Param_EstadoFullScreen">Se true, o renderizador de vídeo aprimorado (EVR) usará o modo de tela inteira. Se false, o EVR desenha o vídeo na 
			/// janela de recorte fornecido pelo aplicativo.</param>
			CarenResult DefinirFullScreen(Boolean Param_EstadoFullScreen);

			/// <summary>
			/// (SetRenderingPrefs)Define preferências diversas, relacionadas com a processamento de vídeo.
			/// </summary>
			CarenResult DefinirConfiguraçãoRenderização(Enumeracoes::CA_VIDEO_RENDER_CONFIGURACOES Param_RenderConfigs);

			/// <summary>
			/// (SetVideoPosition) - Define os retângulos de origem e de destino para o vídeo.
			/// O retângulo de origem define qual parte do vídeo é exibida. Ele é especificado em coordenadas normalizadas. Para obter mais informações, 
			/// consulte estrutura MFVideoNormalizedRect. Para exibir a imagem de vídeo inteira, defina o retângulo de origem como {0, 0, 1, 1}. O retângulo de origem padrão é {0, 0, 1, 1}.
			/// O retângulo de destino define um retângulo dentro da janela de recorte onde o vídeo é exibido. Ele é especificado em pixels, em relação à área do cliente da janela.
			/// Para preencher a janela inteira, defina o retângulo de destino como {0, 0, Largura, Altura}, onde Largura e Altura são dimensões da área do cliente da janela. O retângulo 
			/// de destino padrão é {0, 0, 0, 0}.
			/// </summary>
			/// <param name="Param_RetanguloNormalized">Estrutura que especifica o retângulo origem. Este parâmetro pode ser NULO. Se este parâmetro é NULO, o 
			/// retângulo de origem não é alterado.</param>
			/// <param name="Param_RetanguloDestino">Especifica o retângulo de destino. Este parâmetro pode ser NULL. Se este parâmetro é NULL, o retângulo 
			/// de destino não é alterado.</param>
			CarenResult DefinirPosiçãoVideo(
				Estruturas::CA_Retangulo_Normalizado^ Param_RetanguloNormalized,
				Estruturas::CA_Retangulo^ Param_RetanguloDestino);

			/// <summary>
			/// (SetVideoWindow) - Define a janela de recorte para o vídeo. Está é a janela que vai hospedar o vídeo que será
			/// renderizado para visualização do usuário. A Janela refere-se a (Handle) de um componente na GUI
			/// do usuário.
			/// </summary>
			/// <param name="Param_JanelaVideo"></param>
			CarenResult DefinirJanelaVideo(IntPtr Param_JanelaVideo);
		};

		/// <summary>
		/// (IMFActivate) - Permite que um componente tenha sua criação Adiada. Essa interface é utilizada para criar objetos dos quais devem ser inicializados
		/// por outra interface.
		/// </summary>
		[CategoryAttribute("IMFActivate - Ativador de Objetos do Media Foundation")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFActivate.")]
		[Guid("A86D1E72-CD70-4602-B35C-DD3A0D5B57C3")]
		public interface class ICarenMFActivate : ICaren, ICarenMFAttributes
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			/// <summary>
			/// (ActivateObject) - Cria o objeto associado com esse objeto de ativação.
			/// O método só pode ser chamado se o objeto de ativação já tiver sido criado.
			/// Alguns objetos do Microsoft Media Foundation devem ser encerrados antes de serem liberados. Em caso afirmativo, o chamador é responsável 
			/// por desligar o objeto que é retornado em (Param_Out_InterfaceSolicitada).
			/// </summary>
			/// <param name="Param_IIDInterface">Identificador de interface (IID) da interface solicitada.</param>
			/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface que contém a interface solicitada. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult AtivarObjeto(String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);


			/// <summary>
			/// (DetachObject) - Desanexa o objeto criado a partir do objeto de ativação.
			/// O objeto de ativação libera Todas as suas referências internas para o objeto criado. Se você chamar (AtivarObjeto) novamente, o objeto 
			/// de ativação criará uma nova instância do outro objeto.
			/// O método não desliga o objeto criado. Se o método for bem-sucedido, o cliente deve desligar o objeto criado
			/// </summary>
			CarenResult DesanexarObjeto();


			/// <summary>
			/// (ShutdownObject) - Desliga o objeto criado.
			/// O componente que chama (AtivarObjeto) não o componente que cria o objeto de ativação  é responsável por chamar (DesligarObjeto). Por exemplo, 
			/// em um aplicativo de reprodução típica, o aplicativo cria objetos de ativação para os coletores de mídia, mas a sessão de mídia chama (AtivarObjeto). 
			/// Portanto, a sessão de mídia, não o aplicativo, chama (DesligarObjeto).
			/// </summary>
			CarenResult DesligarObjeto();

		};

		/// <summary>
		/// (IMFStreamDescriptor) - Interface responsável por obter informações sobre um fluxo em uma fonte de mídia.
		/// </summary>
		[CategoryAttribute("IMFStreamDescriptor - Obtém informações de um fluxo.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do .")]
		[Guid("AACE49BC-AF53-4AE9-A2BC-D0A58A33401F")]
		public interface class ICarenMFStreamDescriptor : ICarenMFAttributes
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
			/// (GetMediaTypeHandler) - Recupera um manipulador de tipo de mídia para o fluxo. O manipulador de tipo de mídia pode ser usado para enumerar tipos de mídia suportados para o fluxo, 
			/// obter o tipo de mídia atual e definir o tipo de mídia.
			/// </summary>
			/// <param name="Param_Out_TipoMidiaHandler">Recebe a interface do manipular de tipo de mídia.</param>
			CarenResult ObterManipuladorTipoMidia([Out] ICarenMFMediaTypeHandler^% Param_Out_TipoMidiaHandler);

			/// <summary>
			/// (GetStreamIdentifier) - Recupera um identificador para o fluxo.
			/// </summary>
			/// <param name="Param_Out_Identificador">Recebe o identificador do fluxo.</param>
			CarenResult ObterIdentificadorFluxo([Out] UInt32% Param_Out_Identificador);
		};

		/// <summary>
		/// (IMFPresentationDescriptor) - Interface responsável por descrever detalhes de uma apresentação. Uma apresentação é um conjunto de fluxos de mídia relacionados que
		/// compartilham um tempo de apresentação comum.
		/// Descritores de apresentação são usados para configurar fontes de mídia e afunda-se alguns meios de comunicação.
		/// </summary>
		[CategoryAttribute("IMFPresentationDescriptor - Descreve detalhes de uma apresentação.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFPresentationDescriptor.")]
		[Guid("D6085D8F-2AB7-4513-B464-68EF19270CE4")]
		public interface class ICarenMFPresentationDescriptor : ICarenMFAttributes
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
			/// (Clone) - Cria um copiar deste descritor de apresentação.
			/// </summary>
			/// <param name="Param_Out_ClonagemDescritor">Recebe uma clone da interface do descritor de apresentação atual.</param>
			CarenResult Clonar([Out] ICarenMFPresentationDescriptor^% Param_Out_ClonagemDescritor);

			/// <summary>
			/// (DeselectStream) - Cancela a seleção de um fluxo na apresentação.
			/// </summary>
			/// <param name="Param_IdFluxo">O número de fluxo para desmarcar, indexados a partir de zero. Para encontrar o número de fluxos na apresentação, chame o método 
			/// ICarenMFPresentationDescriptor::ObterQuantidadeDescritoresFluxo.</param>
			CarenResult CancelarFluxo(UInt32 Param_IdFluxo);

			/// <summary>
			/// (GetStreamDescriptorByIndex) - Recupera um descritor de fluxo para um fluxo na apresentação. O descritor de stream contém informação sobre o fluxo.
			/// </summary>
			/// <param name="Param_IdDescritorFluxo">Índice baseado em zero do fluxo. Para encontrar o número de fluxos na apresentação, chame o método ICarenMFPresentationDescriptor::ObterQuantidadeDescritoresFluxo.</param>
			/// <param name="Param_Out_FluxoSelecionado">Recebe um valor booleano que indica se o fluxo está selecionado.</param>
			/// <param name="Param_Out_DescritorFluxo">Recebe a interface do descritor de fluxo no id especificado.</param>
			CarenResult ObterDescritorFluxoPorId(UInt32 Param_IdDescritorFluxo, [Out] Boolean% Param_Out_FluxoSelecionado, [Out] ICarenMFStreamDescriptor^% Param_Out_DescritorFluxo);

			/// <summary>
			/// (GetStreamDescriptorCount) - Recupera o número de descritores de fluxo na apresentação. Cada descritor de stream contém informação sobre um córrego na fonte 
			/// de mídia. Para recuperar um descritor de fluxo, chame o método ICarenMFPresentationDescriptor::ObterDescritorFluxoPorId.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Recebe a quantidade de Descritores de fluxo na apresentação.</param>
			CarenResult ObterQuantidadeDescritoresFluxo([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (SelectStream) - Seleciona um fluxo na apresentação.
			/// </summary>
			/// <param name="Param_IdFluxo">O número do fluxo para selecionar, indexados a partir de zero. Para encontrar o número de fluxos na apresentação, chame o método 
			/// ICarenMFPresentationDescriptor::ObterQuantidadeDescritoresFluxo.</param>
			CarenResult SelecionarFluxo(UInt32 Param_IdFluxo);
		};

		/// <summary>
		/// (IMFByteStream) - Representa um fluxo de bytes de alguma fonte de dados, que pode ser um arquivo local, um arquivo de rede ou alguma outra fonte. 
		/// A interface ICarenMFByteStream suporta as operações de fluxo típicas, como leitura, gravação e busca.
		/// </summary>
		[CategoryAttribute("IMFByteStream - Representa um fluxo de bytes de alguma fonte de dados.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFByteStream.")]
		[Guid("6B3BB243-D012-4703-9C6E-4C7EE4B68C77")]
		public interface class ICarenMFByteStream :ICaren
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
			/// (BeginRead) - Inicia uma operação de leitura assíncrona do fluxo.
			/// Quando todos os dados forem lidos no buffer, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
			/// ICarenMFByteStream::ConcluirLeituraAsync para concluir a solicitação assíncrona.
			/// </summary>
			/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar o buffer.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
			/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
			/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
			/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
			CarenResult LerAsync(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_TamanhoBuffer,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (BeginWrite) - Inicia uma operação de gravação assíncrona no fluxo.
			/// Quando todos os dados foram gravados no fluxo, o método ICarenMFAsyncCallback::Invoke é chamado do objeto de retorno de chamada. Nesse ponto, o aplicativo deve chamar 
			/// ICarenMFByteStream::ConcluirEscritaAsync para concluir a solicitação assíncrona.
			/// </summary>
			/// <param name="Param_Buffer">Um ponteiro para o buffer a ser escrito no fluxo.</param>
			/// <param name="Param_TamanhoBuffer">O tamanho do buffer em bytes.</param>
			/// <param name="Param_Callback">Uma interface de retorno de chamada. O chamador que deve implementar a interface.</param>
			/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
			/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
			CarenResult EscreverAsync(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_TamanhoBuffer,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (Close) - Fecha o fluxo e libera todos os recursos associados ao fluxo, como soquetes ou identificadores de arquivo. Esse método também cancela todas as solicitações
			/// de E / S assíncronas pendentes.
			/// </summary>
			CarenResult Close();

			/// <summary>
			/// (EndRead) - Conclui uma operação de leitura assíncrona.
			/// </summary>
			/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
			/// ICarenMFAsyncCallback::Invoke.</param>
			/// <param name="Param_Out_TotalLido">Recebe o total de bytes que foi lido do fluxo.</param>
			CarenResult ConcluirLeituraAsync(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalLido);

			/// <summary>
			/// (EndWrite) - Conclui uma operação de gravação assíncrona.
			/// </summary>
			/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
			/// ICarenMFAsyncCallback::Invoke.</param>
			/// <param name="Param_Out_TotalEscrito">Recebe o número de bytes que foram escritos.</param>
			CarenResult ConcluirEscritaAsync(ICarenMFAsyncResult^ Param_Resultado, [Out] UInt64% Param_Out_TotalEscrito);

			/// <summary>
			/// (Flush) - Limpa todos os buffers internos usados pelo fluxo. Se você estiver gravando no fluxo, os dados em buffer serão gravados no arquivo ou dispositivo subjacente.
			/// </summary>
			CarenResult Flush();

			/// <summary>
			/// (GetCapabilities) - Recupera as características do fluxo de bytes.
			/// </summary>
			/// <param name="Param_Out_CaracteristicasFluxo">Retorna uma ou mais bandeiras da enumeração (CA_CARACTERISTICAS_BYTESTREAM) que definem as caracteristicas do fluxo de bytes.</param>
			CarenResult ObterCaracteristicas([Out] CA_CARACTERISTICAS_BYTESTREAM% Param_Out_CaracteristicasFluxo);

			/// <summary>
			/// (GetCurrentPosition) - Recupera a posição atual de leitura ou gravação no fluxo.
			/// </summary>
			/// <param name="Param_Out_Posicao">Retorna a posição atual, em bytes.</param>
			CarenResult ObterPosicaoAtual([Out] UInt64% Param_Out_Posicao);

			/// <summary>
			/// (GetLength) - Recupera o comprimento do fluxo.
			/// </summary>
			/// <param name="Param_Out_Largura">Recebe o comprimento do fluxo, em bytes. Se o comprimento for desconhecido, este valor é -1.</param>
			CarenResult ObterLargura([Out] UInt64% Param_Out_Largura);

			/// <summary>
			/// (IsEndOfStream) - Consulta se a posição atual atingiu o final do fluxo.
			/// </summary>
			/// <param name="Param_Out_FinalFluxo">Retorna o valor TRUE se a posiçao atual for o final do fluxo, caso contrário FALSE.</param>
			CarenResult VerificarFinalFluxo([Out] Boolean% Param_Out_FinalFluxo);

			/// <summary>
			/// (Read) - Lê dados do fluxo.
			/// </summary>
			/// <param name="Param_Buffer">Um ponteiro para o buffer que vai receber os dados. O chamador deve alocar esse buffer.</param>
			/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
			/// <param name="Param_Out_TotalLido">Recebe o número de bytes lidos no buffer.</param>
			CarenResult Ler(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_Tamanho,
				[Out] UInt64% Param_Out_TotalLido);

			/// <summary>
			/// (Seek) - Move a posição atual no fluxo por um deslocamento especificado.
			/// </summary>
			/// <param name="Param_Origem">Especifica a origem da busca como membro da enumeração CA_MFBYTESTREAM_SEEK_ORIGIN. O deslocamento é calculado em relação a esta posição.</param>
			/// <param name="Param_Offset">Especifica a nova posição, como um byte offset da origem da busca.</param>
			/// <param name="Param_Flags">Especifica zero ou mais bandeiras da enumeração CA_MFBYTESTREAM_SEEK_FLAGS.</param>
			/// <param name="Param_Out_NovaPosicao">Recebe a nova posição após a busca.</param>
			CarenResult Seek(
				CA_MFBYTESTREAM_SEEK_ORIGIN Param_Origem,
				Int64 Param_Offset,
				CA_MFBYTESTREAM_SEEK_FLAGS Param_Flags,
				[Out] UInt64% Param_Out_NovaPosicao);

			/// <summary>
			/// (SetCurrentPosition) - Define a posição atual de leitura ou gravação.
			/// </summary>
			/// <param name="Param_Posicao">Nova posição no fluxo, como um byte offset desde o início do fluxo.</param>
			CarenResult DefinirPosicaoAtual(UInt64 Param_Posicao);

			/// <summary>
			/// (SetLength) - Define o comprimento do fluxo.
			/// </summary>
			/// <param name="Param_LarguraFluxo">A largura do fluxo em bytes.</param>
			CarenResult DefinirLargura(UInt64 Param_LarguraFluxo);

			/// <summary>
			/// (Write) - Grava dados no fluxo.
			/// </summary>
			/// <param name="Param_Buffer">Um ponteiro para o buffer que contém os dados a serem escritos.</param>
			/// <param name="Param_Tamanho">O tamanho do buffer em bytes.</param>
			/// <param name="Param_Out_TotalEscrito">Recebe o numero de bytes que foram escritos no buffer.</param>
			CarenResult Escrever(
				ICarenBuffer^ Param_Buffer,
				UInt64 Param_Tamanho,
				[Out] UInt64% Param_Out_TotalEscrito);
		};

		/// <summary>
		/// (IMFMediaSource) - Fontes de mídia são objetos que geram dados de mídia. Por exemplo, os dados podem vir de um arquivo de vídeo, um fluxo de rede ou um dispositivo de hardware, como uma câmera. 
		/// Cada fonte de mídia contém um ou mais fluxos e cada fluxo fornece dados de um tipo, como áudio ou vídeo.
		/// </summary>
		[CategoryAttribute("IMFMediaSource - Representa uma fonte de midia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFMediaSource.")]
		[Guid("380D3681-BFE5-4408-BADC-D952A88EB52F")]
		public interface class ICarenMFMediaSource : ICaren, ICarenMFMediaEventGenerator
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
			/// (CreatePresentationDescriptor) - Recupera uma cópia do descritor de apresentação da fonte de mídia. Os aplicativos usam o descritor de apresentação para selecionar fluxos e obter informações sobre o conteúdo de origem.
			/// </summary>
			/// <param name="Param_Out_DescritorApresentação">Recebe a interface para o descritor de apresentação.</param>
			CarenResult CriarDescritorApresentação([Out] ICarenMFPresentationDescriptor^% Param_Out_DescritorApresentação);

			/// <summary>
			/// (GetCharacteristics) - Recupera as características da fonte de mídia.
			/// </summary>
			/// <param name="Param_Out_Caracteristicas">Recebe um OR de bit a bit de zero ou mais sinalizadores da enumeração (CA_CARACTERISTICAS_FONTE_MIDIA).</param>
			CarenResult ObterCaracteristicas([Out] Enumeracoes::CA_CARACTERISTICAS_FONTE_MIDIA% Param_Out_Caracteristicas);

			/// <summary>
			/// (Start) - Inicia, procura ou reinicia a fonte de mídia especificando onde iniciar a reprodução.
			/// </summary>
			/// <param name="Param_DescritorApresentação">A interface de ICarenMFPresentationDescriptor de descritor de apresentação da fonte de mídia. Para obter o descritor de apresentação, chamade o método (ICarenMFPresentationDescriptor::CriarDescritorApresentação). 
			/// Você pode modificar o descritor de apresentação antes de chamar Iniciar, para selecionar ou desmarcar fluxos ou alterar os tipos de mídia.</param>
			/// <param name="Param_GuidTimeFormato">Um GUID que especifica o formato de hora. O formato de hora define as unidades para o parâmetro Param_PosiçãoInicio. Se o valor é NULL, o formato é definido como unidades de 100 nanossegundos. Algumas fontes de 
			/// mídia podem oferecer suporte o formato de hora adicional. Este parâmetro pode ser nulo. Se o valor for nulo, é equivalente a GUID_NULL.</param>
			/// <param name="Param_PosiçãoInicio">Especifica onde iniciar a reprodução. As unidades deste parâmetro são indicadas pelo formato tempo dado em Param_GuidTimeFormato. Se o formato de hora é GUID_NULL, o tipo de variante deve ser VT_I8 ou VT_EMPTY. Use VT_I8 
			/// para especificar uma nova posição inicial, em unidades de 100 nanossegundos. Use VT_EMPTY para começar a partir da posição atual. Outros formatos de hora podem usar outros tipos CA_PropVariant.</param>
			CarenResult Iniciar(ICarenMFPresentationDescriptor^ Param_DescritorApresentação, String^ Param_GuidTimeFormato, Estruturas::CA_PropVariant^ Param_PosiçãoInicio);

			/// <summary>
			/// (Pause) - Pausa todos os fluxos ativos na fonte de mídia.
			/// </summary>
			CarenResult Pausar();

			/// <summary>
			/// (Stop) - Interrompe todos os fluxos ativos na fonte de mídia.
			/// </summary>
			CarenResult Parar();

			/// <summary>
			/// (Shutdown) - Desliga a fonte de mídia e libera os recursos que ela está usando.
			/// </summary>
			CarenResult Desligar();
		};

		/// <summary>
		/// (IMFMediaSourceEx) - Estende a interface IMFMediaSource para fornecer recursos adicionais para uma fonte de mídia.
		/// Para obter essa interface, Chame o método (ConsultarInterface) na interface ICarenMFMediaSource.
		/// </summary>
		[CategoryAttribute("IMFMediaSourceEx - Representa uma extensão para a fonte de midia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFMediaSourceEx.")]
		[Guid("B6073936-21AF-402C-96EE-FA56BB7E6BF8")]
		public interface class ICarenMFMediaSourceEx : ICarenMFMediaSource
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
			/// (GetSourceAttributes) - Obtém um armazenamento de atributo para a fonte de mídia.
			/// </summary>
			/// <param name="Param_Out_AtributosFonteMidia">Recebe a interface que contém os atributos para a fonte de midia.</param>
			CarenResult ObterAtributosFonteMidia([Out] ICarenMFAttributes^% Param_Out_AtributosFonteMidia);

			/// <summary>
			/// (GetStreamAttributes) - Obtém um armazenamento de atributo para um fluxo na fonte de mídia.
			/// </summary>
			/// <param name="Param_Out_AtributosFluxoFonte">Recebe a interface que contém os atributos para um fluxo na fonte de midia.</param>
			/// <param name="Param_IdentificadorFluxo">O identificador do fluxo. Para obter o identificador, chame ICarenMFStreamDescriptor::ObterIdentificadorFluxo no descritor de fluxo.</param>
			CarenResult ObterAtributosFluxoFonte(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFAttributes^% Param_Out_AtributosFluxoFonte);

			/// <summary>
			/// (SetD3DManager) - Define um ponteiro para o Gerenciador de dispositivos do Microsoft DirectX Graphics infra-estrutura (DXGI) na fonte de mídia.
			/// </summary>
			/// <param name="Param_DXGIManager">O Gerenciador do DXGI que será utilizado.</param>
			CarenResult DefinirGerenciadorDXGI(ICarenMFDXGIDeviceManager^ Param_DXGIManager);

		};

		/// <summary>
		/// (IMFMediaStream) - Representa um fluxo em uma fonte de mídia. Fluxos são criados quando uma fonte de mídia é iniciada. Para cada fluxo, a origem de mídia envia
		/// um evento MENewStream com um ponteiro para esta interface.
		/// </summary>
		[CategoryAttribute("IMFMediaStream - Representa uma fluxo em uma fonte de mídia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFMediaStream.")]
		[Guid("1B7C719B-C391-4C38-91C4-7D47E0BC669C")]
		public interface class ICarenMFMediaStream : ICarenMFMediaEventGenerator
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
			/// (GetMediaSource) - Recupera um ponteiro para a fonte de mídia que criou este fluxo de mídia.
			/// </summary>
			/// <param name="Param_Out_FonteMidia">Recebe a fonte de mídia responsável por esse fluxo.</param>
			CarenResult ObterFonteMidia([Out] ICarenMFMediaSource^% Param_Out_FonteMidia);

			/// <summary>
			/// (GetStreamDescriptor) - Recupera um descritor de stream para este fluxo de mídia.
			/// </summary>
			/// <param name="Param_Out_DescritorFluxo">Recebe o descritor deste fluxo.</param>
			CarenResult ObterDescritorFluxo([Out] ICarenMFStreamDescriptor^% Param_Out_DescritorFluxo);

			/// <summary>
			/// (RequestSample) - Solicite uma amostra da fonte de mídia.
			/// </summary>
			/// <param name="Param_Token">Um Objeto que é usado como símbolo para solicitação. O chamador deve implementar este objeto. Este parâmetro pode ser nulo.</param>
			CarenResult RequisitarAmostra(ICaren^ Param_Token);
		};

		/// <summary>
		/// (IMFAudioStreamVolume) - Controla os níveis de volume de canais de áudio individuais.
		/// O processador de áudio streaming (SAR) expõe essa interface como um serviço. Para obter um ponteiro para a interface, chame ICaren::ConsultarInterfaceServiço
		/// com o identificador de serviço MR_STREAM_VOLUME_SERVICE. Você pode chamar GetService diretamente sobre o SAR ou chamá-lo sobre a sessão de mídia.
		/// </summary>
		[CategoryAttribute("IMFAudioStreamVolume - Interface que controla o volume de audio em cada canal de audio.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFAudioStreamVolume.")]
		[Guid("CE0A8168-5D19-4A9B-A558-9F356C36EC51")]
		public interface class ICarenMFAudioStreamVolume : ICaren
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
			/// (GetAllVolumes) - Recupera os níveis de volume para todos os canais no fluxo de áudio.
			/// </summary>
			/// <param name="Param_TamanhoMatriz">O Tamanho da matriz no parmêtro (Param_Out_MatrizVolumes). Esse valor representa a quantidade de canais de áudio.
			/// Para obter esse valor, chame o método (ObterQuantidadeCanais).</param>
			/// <param name="Param_Out_MatrizVolumes">Recebe a matriz com o nível de volume de para cada canal no fluxo.</param>
			CarenResult ObterTodosVolumes(UInt32 Param_TamanhoMatriz, [Out] cli::array<float>^% Param_Out_MatrizVolumes);

			/// <summary>
			/// (GetChannelCount) - Recupera o número de canais no fluxo de áudio.
			/// </summary>
			/// <param name="Param_Out_QuantidadeCanais">Recebe o número de canais no fluxo de áudio.</param>
			CarenResult ObterQuantidadeCanais([Out] UInt32% Param_Out_QuantidadeCanais);

			/// <summary>
			/// (GetChannelVolume) - Recupera o nível de volume para um canal específico no fluxo de áudio.
			/// </summary>
			/// <param name="Param_IdCanal">Índice baseado em zero do canal de áudio. Para obter o número de canais, chame o método (ObterQuantidadeCanais).</param>
			/// <param name="Param_Out_NivelVolume">Recebe o nível de volume no canal especificado.</param>
			CarenResult ObterVolumeCanalEspecifico(UInt32 Param_IdCanal, [Out] float% Param_Out_NivelVolume);

			/// <summary>
			/// (SetAllVolumes) - Define os níveis de volume individual para todos os canais no fluxo de áudio.
			/// </summary>
			/// <param name="Param_TamanhoMatriz">O Tamanho da matriz no parmêtro (Param_NiveisVolume). Esse valor representa a quantidade de canais de áudio.
			/// Para obter esse valor, chame o método (ObterQuantidadeCanais).</param>
			/// <param name="Param_NiveisVolume"> A matriz sspecifica os níveis de volume para todos os canais. Antes de chamar o método, defina cada elemento da matriz para o
			/// nível de volume desejado para o canal.</param>
			CarenResult DefinirTodosVolumes(UInt32 Param_TamanhoMatriz, cli::array<float>^ Param_NiveisVolume);

			/// <summary>
			/// (SetChannelVolume) - Define o nível de volume para um canal específico no fluxo de áudio.
			/// </summary>
			/// <param name="Param_IdCanal">Índice baseado em zero do canal de áudio. Para obter o número de canais, chame o método (ObterQuantidadeCanais).</param>
			/// <param name="Param_NivelVolume">O nível de volume a ser definido no canal especificado.</param>
			CarenResult DefinirVolumeCanalEspecifico(UInt32 Param_IdCanal, float Param_NivelVolume);
		};

		/// <summary>
		/// (IMFSimpleAudioVolume) - Interface responsável por controlar o nível de volume principal da sessão de áudio associado ao renderizador de transmissão de áudio 
		/// (SAR) e à fonte de captura de áudio.
		/// Essa interface é exposta como uma serviço pelo SAR(Streaming Audio Render) e pelo sistema de captura de Audio. Para o SAR, utilize o o identificador de serviço
		/// (MR_POLICY_VOLUME_SERVICE) e para o sistema de captura o (MR_CAPTURE_POLICY_VOLUME_SERVICE).
		/// </summary>
		[CategoryAttribute("IMFSimpleAudioVolume - Interface que controla o nivel de audio principal.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFSimpleAudioVolume.")]
		[Guid("87D01DE6-1E2F-446E-B734-9B0FE5CAF540")]
		public interface class ICarenMFSimpleAudioVolume : ICaren
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
			/// (GetMasterVolume) - Recupera o nível de volume principal.
			/// </summary>
			/// <param name="Param_Out_VolumePrincipal">Retorna o volume principal do áudio.</param>
			CarenResult ObterVolumePrincipal([Out] float% Param_Out_VolumePrincipal);

			/// <summary>
			/// (GetMute) - Consulta se o áudio está sem áudio.
			/// </summary>
			/// <param name="Param_Out_AudioMudo">Retorna um valor boleano que indica se o áudio está mudo ou não.</param>
			CarenResult ConsultarAudioMudo([Out] Boolean% Param_Out_AudioMudo);

			/// <summary>
			/// (SetMasterVolume) - Define o nível de volume principal.
			/// </summary>
			/// <param name="Param_VolumePrincipal">Define o volume principal do áudio. O valor vai de 0.0(Mudo) a 1.0(Maximo).</param>
			CarenResult DefinirVolumePrincipal(float Param_VolumePrincipal);

			/// <summary>
			/// (SetMute) - Silencia ou repõe o áudio.
			/// </summary>
			/// <param name="Param_EstadoAudio">Define o estado de volume do áudio.</param>
			CarenResult DefinirEstadoAudio(Boolean Param_EstadoAudio);

		};

		/// <summary>
		/// (IMFSourceResolver) - Interface responsável por criar uma fonte de mídia a parti de uma URL ou um fluxo de bytes.
		/// </summary>
		[CategoryAttribute("IMFSourceResolver - Criação de fontes de mídia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFSourceResolver.")]
		[Guid("94A89CF7-7DE7-46B6-A9B6-4F74B9D7C02C")]
		public interface class ICarenMFSourceResolver : ICaren
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
			/// (BeginCreateObjectFromByteStream) - Inicia uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
			/// </summary>
			/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
			/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
			/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
			/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_ObjetoCancel">Recebe um ponteiro ICaren ou o valor nulo. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
			/// de ICarenMFSourceResolver::CancelarCriaçãoObjeto. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
			/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
			/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
			CarenResult CriarObjetoFromByteStreamAsync
			(
				ICarenMFByteStream^ Param_FluxoBytes,
				String^ Param_Url,
				Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
				ICarenPropertyStore^ Param_Propriedades,
				ICaren^ Param_ObjetoCancel,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado
			);

			/// <summary>
			/// (BeginCreateObjectFromURL) - Inicia uma solicitação assíncrona para criar uma fonte de mídia ou um fluxo de bytes de uma URL.
			/// </summary>
			/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
			/// <param name="Param_Flags">OR bit a bit dos sinalizadores.</param>
			/// <param name="Param_Propriedades">Ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o esquema manipulador ou 
			/// manipulador de fluxo de bytes que cria o objeto. O manipulador pode usar o armazenamento de propriedade para configurar o objeto. Este parâmetro pode ser nulo</param>
			/// <param name="Param_ObjetoCancel">Recebe um ponteiro ICaren ou o valor nulo. Se o valor não for NULO, você pode cancelar a operação assíncrona, passando esse ponteiro para o método 
			/// de ICarenMFSourceResolver::CancelarCriaçãoObjeto. O chamador deve liberar a interface. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Callback">Um ponteiro para a interface de ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar essa interface.</param>
			/// <param name="Param_ObjetoEstado">Um ponteiro para a interface ICaren de um objeto de estado, definido pelo chamador. Este parâmetro pode ser nulo. Você pode usar esse objeto para 
			/// armazenar informações de estado. O objeto é retornado ao chamador de quando o callback é invocado.</param>
			CarenResult CriarObjetoFromUrlAsync
			(
				String^ Param_Url,
				Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
				ICarenPropertyStore^ Param_Propriedades,
				ICaren^ Param_ObjetoCancel,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado
			);

			/// <summary>
			/// (CancelObjectCreation) - Cancela uma solicitação assíncrona para criar um objeto.
			/// </summary>
			/// <param name="Param_ObjetoCancel">Ponteiro para a interface ICaren que foi retornada no parâmetro Param_ObjetoCancel do método ICarenMFSourceResolver::CriarObjetoFromByteStreamAsync 
			/// ou ICarenMFSourceResolver::CriarObjetoFromUrlAsync. </param>
			CarenResult CancelarCriaçãoObjeto(ICaren^ Param_ObjetoCancel);

			/// <summary>
			/// (CreateObjectFromByteStream) - Cria uma fonte de mídia de um fluxo de bytes. Este método é síncrono.
			/// </summary>
			/// <param name="Param_FluxoBytes">Um Ponteiro para a interface ICarenMFByteStream que contém o fluxo de bytes.</param>
			/// <param name="Param_Url">Uma sequência de caracteres terminada com nulo que contém a URL original do fluxo de bytes. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Flags">Um bit a bit ou de uma ou mais bandeiras.</param>
			/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
			/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
			/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult CriarObjetoFromByteStream
			(
				ICarenMFByteStream^ Param_FluxoBytes,
				String^ Param_Url,
				Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
				ICarenPropertyStore^ Param_Propriedades,
				[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
				ICaren^ Param_Out_FonteMidia
			);

			/// <summary>
			/// (CreateObjectFromURL) - Cria uma fonte de mídia ou um fluxo de bytes de um URL. Este método é síncrono.
			/// </summary>
			/// <param name="Param_Url">Sequência de caracteres terminada com nulo que contém o URL para resolver.</param>
			/// <param name="Param_Flags">OR bit a bit de um ou mais bandeiras.</param>
			/// <param name="Param_Propriedades">Um ponteiro para a interface de ICarenPropertyStore de uma loja de propriedade. O método passa a loja de propriedade para o manipulador de fluxo de bytes.
			/// O manipulador de fluxo de bytes pode usar o armazenamento de propriedade para configurar a fonte de mídia. Este parâmetro pode ser nulo.</param>
			/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
			/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult CriarObjetoFromUrl
			(
				String^ Param_Url,
				Enumeracoes::CA_SOURCE_RESOLVER_FLAGS Param_Flags,
				ICarenPropertyStore^ Param_Propriedades,
				[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
				ICaren^ Param_Out_FonteMidia
			);

			/// <summary>
			/// (EndCreateObjectFromByteStream) - Conclui uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
			/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
			/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ConcluirCriaçãoObjetoFromByteStream
			(
				ICarenMFAsyncResult^ Param_Resultado,
				[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
				ICaren^ Param_Out_FonteMidia
			);

			/// <summary>
			/// (EndCreateObjectFromURL) - Conclui uma solicitação assíncrona para criar um objeto a partir de um URL.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passar o mesmo ponteiro que recebeu de seu objeto de retorno de chamada no método Invoke.</param>
			/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
			/// <param name="Param_Out_FonteMidia">Recebe a interface para a fonte de mídia criada. O chamador deve liberar a interface. O usuário deve criar a interface antes de chamar este método.</param>
			CarenResult ConcluirCriaçãoObjetoFromUrl
			(
				ICarenMFAsyncResult^ Param_Resultado,
				[Out] Enumeracoes::CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
				ICaren^ Param_Out_FonteMidia
			);
		};

		/// <summary>
		/// (IMFTopologyNode) - Interface responsável por representar um nó de topologia. Os tipos de nó suportado por essa interface são: Saida, Origem, Transformação(MFT), Tee.
		/// </summary>
		[CategoryAttribute("IMFTopologyNode - Nó de topologia.")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFTopologyNode.")]
		[Guid("313763D6-9C55-4879-8BC0-55B052436249")]
		public interface class ICarenMFTopologyNode : ICarenMFAttributes
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
			/// (CloneFrom) - Copia os dados de outro nó de topologia para este nó.
			/// </summary>
			/// <param name="Param_NodeClone">O nó que vai ter os dados copiados para esse.</param>
			CarenResult ClonarDe(ICarenMFTopologyNode^ Param_NodeClone);

			/// <summary>
			/// (ConnectOutput) - Conecta um fluxo de saída deste nó para o fluxo de entrada de outro nó.
			/// As conexões de nó representam o fluxo de dados de um nó para o próximo. Os fluxos são lógicos e são especificados pelo índice. Se o nó já estiver conectado na saída especificada, o método interrompe a conexão existente.
			/// </summary>
			/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de saída neste nó.</param>
			/// <param name="Param_NoConexao">Ponteiro para a interface ICarenMFTopologyNode do nó ao qual se conectar.</param>
			/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de entrada no outro nó.</param>
			CarenResult ConectarSaida(UInt32 Param_IndexFluxoSaida, ICarenMFTopologyNode^ Param_NoConexao, UInt32 Param_IndexFluxoEntrada);

			/// <summary>
			/// (DisconnectOutput) - Desconecta um fluxo de saída neste nó.
			/// </summary>
			/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de saída para se desconectar.</param>
			CarenResult DesconectarSaida(UInt32 Param_IndexSaida);

			/// <summary>
			/// (GetInput) - Recupera o nó que está conectado a um fluxo de entrada especificado neste nó.
			/// </summary>
			/// <param name="Param_IndexEntrada">Índice baseado em zero de um fluxo de entrada neste nó.</param>
			/// <param name="Param_Out_NoConectado">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de entrada especificado. O chamador deve liberar a interface.</param>
			/// <param name="Param_Out_IndexFluxoSaida">Recebe o índice do fluxo de saída que está conectado ao fluxo de entrada deste nó.</param>
			CarenResult ObterEntrada(UInt32 Param_IndexEntrada, [Out] ICarenMFTopologyNode^% Param_Out_NoConectado, [Out] UInt32% Param_Out_IndexFluxoSaida);

			/// <summary>
			/// (GetInputCount) - Recupera o número de fluxos de entrada que existem atualmente neste nó.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxosEntrada">Recebe o número de fluxos de entrada.</param>
			CarenResult ObterQuantidadeEntradas([Out] UInt32% Param_Out_QuantidadeFluxosEntrada);

			/// <summary>
			/// (GetInputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de entrada neste nó.
			/// </summary>
			/// <param name="Param_IndexEntrada">Índice baseado em zero do fluxo de Entrada.</param>
			/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para IMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
			CarenResult ObterTipoMidiaPreferencialEntrada(UInt32 Param_IndexEntrada, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial);

			/// <summary>
			/// (GetNodeType) - Recupera o tipo de nó.
			/// </summary>
			/// <param name="Param_Out_TipoNode">Recebe um valor de enumeração que define o tipo do nó na topologia.</param>
			CarenResult ObterTipoNode([Out] Enumeracoes::CA_TOPOLOGY_TYPE% Param_Out_TipoNode);

			/// <summary>
			/// (GetObject) - Obtém o objeto associado a este nó.
			/// </summary>
			/// <param name="Param_Out_Objeto">Recebe uma interface que está associada a esse nó. O usuário deve criar a interfaces antes de chamar este método.</param>
			CarenResult ObterObjeto(ICaren^ Param_Out_Objeto);

			/// <summary>
			/// (GetOutput) - Recupera o nó que está conectado a um fluxo de saída especificado neste nó.
			/// </summary>
			/// <param name="Param_IndexSaidaFluxo">Índice baseado em zero de um fluxo de saída neste nó.</param>
			/// <param name="Param_Out_NodeConexao">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de saída especificado. O chamador deve liberar a interface.</param>
			/// <param name="Param_Out_IndexEntradaFluxo">Recebe o índice do fluxo de entrada que está conectado ao fluxo de saída deste nó.</param>
			CarenResult ObterSaida(UInt32 Param_IndexSaidaFluxo, [Out] ICarenMFTopologyNode^% Param_Out_NodeConexao, [Out] UInt32% Param_Out_IndexEntradaFluxo);

			/// <summary>
			/// (GetOutputCount) - Recupera o número de fluxos de saída que existem atualmente neste nó.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxosSaida">Recebe o número de fluxos de saída.</param>
			CarenResult ObterQuantidadeSaidas([Out] UInt32% Param_Out_QuantidadeFluxosSaida);

			/// <summary>
			/// (GetOutputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de saída neste nó.
			/// </summary>
			/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de Saida.</param>
			/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para ICarenMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
			CarenResult ObterTipoMidiaPreferencialSaida(UInt32 Param_IndexSaida, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial);

			/// <summary>
			/// (GetTopoNodeID) - Recupera o identificador do nó.
			/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Os identificadores de nó são exclusivos dentro de uma topologia, mas podem ser reutilizados 
			/// em várias topologias.
			/// </summary>
			/// <param name="Param_Out_IdentificadorNode">Recebe o identificador deste nó.</param>
			CarenResult ObterTopoNodeID([Out] UInt64% Param_Out_IdentificadorNode);

			/// <summary>
			/// (SetInputPrefType) - Define o tipo de mídia preferencial para um fluxo de entrada neste nó.
			/// </summary>
			/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de Entrada.</param>
			/// <param name="Param_TipoMidia">Ponteiro para ICarenMFMediaType do tipo de mídia.</param>
			CarenResult DefinirTipoMidiaPreferencialEntrada(UInt32 Param_IndexFluxoEntrada, ICarenMFMediaType^ Param_TipoMidia);

			/// <summary>
			/// (SetObject) - Define o objeto associado a este nó.
			/// </summary>
			/// <param name="Param_Objeto">A interface a ser associada a este nó. Defina como NULO para limpar o objeto definido anteriormente.</param>
			CarenResult DefinirObjeto(ICaren^ Param_Objeto);

			/// <summary>
			/// (SetOutputPrefType) - Define o tipo de mídia preferencial para um fluxo de saída neste nó.
			/// </summary>
			/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de Saida.</param>
			/// <param name="Param_TipoMidia">A interface ICarenMFMediaType que contém o ponteiro para o tipo de midia..</param>
			CarenResult DefinirTipoMidiaPreferencialSaida(UInt32 Param_IndexFluxoSaida, ICarenMFMediaType^ Param_TipoMidia);

			/// <summary>
			/// (SetTopoNodeID) - Define o identificador para o nó.
			/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Normalmente, não há nenhuma razão para um aplicativo substituir o identificador.
			/// </summary>
			/// <param name="Param_IdentificadorNode">O novo identificador para este nó.</param>
			CarenResult DefinirTopoNodeID(UInt64 Param_IdentificadorNode);
		};

		/// <summary>
		/// (IMFTopology) - Interface responsável por representar uma topologia. Uma topologia descreve uma coleção de fontes de mídia, pias e transformações que estão conectadas em uma determinada ordem. Esses objetos são representados dentro da topologia por nós de 
		/// topologia, que expõem a interface ICarenMFTopologyNode. Uma topologia descreve o caminho dos dados multimídia por meio desses nós.
		/// </summary>
		[CategoryAttribute("IMFTopology - Topoloigia de Midia")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFTopology.")]
		[Guid("4A272C13-FDE3-489E-9FB2-9C1D2981E3F7")]
		public interface class ICarenMFTopology : ICarenMFAttributes
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
			/// (AddNode) - Adiciona um nó a topologia.
			/// </summary>
			/// <param name="Param_NoTopologia">Ponteiro para a interface de IMFTopologyNode do nó.</param>
			CarenResult AdicionarNode(ICarenMFTopologyNode^ Param_NoTopologia);

			/// <summary>
			/// (Clear) - Remove todos os nós da topologia.
			/// </summary>
			CarenResult Limpar();

			/// <summary>
			/// (CloneFrom) - Converte essa topologia em uma cópia de outra topologia.
			/// </summary>
			/// <param name="Param_TopologiaClone">Um ponteiro para a topologia que será clonada.</param>
			CarenResult ClonarDe(ICarenMFTopology^ Param_TopologiaClone);

			/// <summary>
			/// (GetNode) - Obtém um nó na topologia, especificado por um index.
			/// </summary>
			/// <param name="Param_Index">O índice baseado em zero do nó. Para obter o número de nós na topologia, chame o método ObterQuantidadeNode.</param>
			/// <param name="Param_Out_NodeTopologia">Retorna um ponteiro para o nó no index informado.</param>
			CarenResult ObterNode(UInt16 Param_Index, [Out] ICarenMFTopologyNode^% Param_Out_NodeTopologia);

			/// <summary>
			/// (GetNodeByID) - Obtém um nó na topologia, especificado pelo identificador de nó.
			/// </summary>
			/// <param name="Param_IdentificadorNode">O identificador do nó para recuperar. Para obter o identificador de um nó, chame o método ICarenMFTopologyNode::ObterTopoNodeID.</param>
			/// <param name="Param_Out_NodeTopologia">Retorna um ponteiro para o nó no indentificador informado.</param>
			CarenResult ObterNodePorID(UInt64 Param_IdentificadorNode, [Out] ICarenMFTopologyNode^% Param_Out_NodeTopologia);

			/// <summary>
			/// (GetNodeCount) - Obtém o número de nós na topologia.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de nó na topologia.</param>
			CarenResult ObterQuantidadeNode([Out] UInt16 Param_Out_Quantidade);

			/// <summary>
			/// (GetOutputNodeCollection) - Obtém os nós de saída na topologia.
			/// </summary>
			/// <param name="Param_Out_ColecaoNoSaida">Retorna um ponteiro para a coleção que contém os nó de saida. O chamador que deve liberar o ponteiro.
			/// A coleção pode conter 0 ou mais ponteiros. Todos os objetos dentro da coleção podem ser consultados para a interface ICarenMFTopologyNode.</param>
			CarenResult ObterColecaoNodeSaida([Out] ICarenMFCollection^% Param_Out_ColecaoNoSaida);

			/// <summary>
			/// (GetSourceNodeCollection) - Obtém os nós de origem na topologia.
			/// </summary>
			/// <param name="Param_Out_ColecaoNoOrigem">Retorna um ponteiro para a coleção que contém os nó de Origem. O chamador que deve liberar o ponteiro.
			/// A coleção pode conter 0 ou mais ponteiros. Todos os objetos dentro da coleção podem ser consultados para a interface ICarenMFTopologyNode.</param>
			CarenResult ObterColecaoNodeOrigem([Out] ICarenMFCollection^% Param_Out_ColecaoNoOrigem);

			/// <summary>
			/// (GetTopologyID) - Obtém o identificador da topologia.
			/// </summary>
			/// <param name="Param_Out_IdentificadorTopologia">Retorna o identificador desta topologia.</param>
			CarenResult ObterIDTopologia([Out] UInt64% Param_Out_IdentificadorTopologia);

			/// <summary>
			/// (RemoveNode) - Remove um nó da topologia.
			/// Esse método não destrói o nó, portanto, o ICarenMFTopologyNode ponteiro ainda é válido depois que o método retorna.
			/// O método interrompe todas as conexões entre o nó especificado e outros nós.
			/// </summary>
			/// <param name="Param_NodeRemove">O nó a ser removido da topologia.</param>
			CarenResult RemoverNode(ICarenMFTopologyNode^ Param_NodeRemove);
		};

		/// <summary>
		/// (IMFTopoLoader) - Interface responsável por converte uma topologia parcial em uma topologia completa. O carregador de topologia expõe essa interface.
		/// </summary>
		[CategoryAttribute("IMFTopoLoader - Conversor de Topologia")]
		[DescriptionAttribute("Interface responsável por expor os métodos do IMFTopoLoader.")]
		[Guid("FA3945D6-0F34-4EA4-AE63-567436B0B3E3")]
		public interface class ICarenMFTopoLoader : ICaren
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
			/// (Load) - Cria uma topologia totalmente carregada da topologia parcial de entrada.
			/// Esse método cria qualquer transformações intermediárias que são necessárias para concluir a topologia. Ele também define os tipos de mídia de entrada e saída em todos os objetos na topologia. 
			/// Se o método for bem-sucedido, a topologia completa será retornada no parâmetro Param_Out_TopologiaCompleta.
			/// </summary>
			/// <param name="Param_TopologiaParcial">Um ponteiro para a interface ICarenMFTopology da topologia parcial a ser resolvida.</param>
			/// <param name="Param_Out_TopologiaCompleta">Recebe um ponteiro para a interface ICarenMFTopology da topologia concluída. O chamador deve liberar a interface.</param>
			/// <param name="Param_TopologiaAnterior">Um ponteiro para a interface ICarenMFTopology da topologia completa anterior. O carregador de topologia pode reusar objetos dessa topologia na nova topologia. 
			/// Este parâmetro pode ser NULL.</param>
			CarenResult Carregar(ICarenMFTopology^ Param_TopologiaParcial, [Out] ICarenMFTopology^% Param_Out_TopologiaCompleta, ICarenMFTopology^ Param_TopologiaAnterior);
		};

		/// <summary>
		/// (IMFTopologyNodeAttributeEditor) - Interface responsável por atualiza os atributos de um ou mais nós na topologia atual da sessão de mídia.A sessão de mídia expõe essa interface como 
		/// um serviço. Para obter um ponteiro para a interface, chame ICaren::ConsultarServiço.O identificador de serviço é MF_TOPONODE_ATTRIBUTE_EDITOR_SERVICE.
		/// </summary>
		[CategoryAttribute("IMFTopologyNodeAttributeEditor - ")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFTopologyNodeAttributeEditor.")]
		[Guid("2E5FC788-616F-4D4F-BC4F-CACBE26071E0")]
		public interface class ICarenMFTopologyNodeAttributeEditor : ICaren
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
			/// (UpdateNodeAttributes) - Atualiza os atributos de um ou mais nós na topologia atual..
			/// </summary>
			/// <param name="Param_TopoId">Reservado.</param>
			/// <param name="Param_CountArray">A quantidade de elementos no array que contém as atualizações dos atributos.</param>
			/// <param name="Param_ArrayUpdates">Uma matriz que contém elementos que atualizam os atributos. Cada elemento atualiza (um) atributo no nó.</param>
			CarenResult AtualizarAtributosNode(UInt64 Param_TopoId, UInt32 Param_CountArray, cli::array<Estruturas::CA_MFTOPONODE_ATTRIBUTE_UPDATE^>^ Param_ArrayUpdates);
		};

		/// <summary>
		/// (IMFTopologyServiceLookup) - Interface responsável por recuperar uma interface do renderizador de vídeo aprimorado (EVR) ou do mixer de vídeo ou do apresentador de vídeo.
		/// </summary>
		[CategoryAttribute("IMFTopologyServiceLookup - Recupera interfaces de serviços do EVR.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFTopologyServiceLookup.")]
		[Guid("C81258EB-DA90-49DF-B965-956F17AD3E15")]
		public interface class ICarenMFTopologyServiceLookup : ICaren
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
			/// (LookupService) - Recupera uma interface do renderizador de vídeo aprimorado (EVR) ou do mixer de vídeo ou do apresentador de vídeo.
			/// </summary>
			/// <param name="Param_EscopoPesquisa">Especifica o escopo da pesquisa. Atualmente, esse parâmetro é ignorado. Use o valor MF_SERVICE_LOOKUP_GLOBAL.</param>
			/// <param name="Param_Indice">Reservado, deve ser zero.</param>
			/// <param name="Param_GuidServico">Serviço GUID da interface solicitada.</param>
			/// <param name="Param_IID">Identificador de interface da interface solicitada.</param>
			/// <param name="Param_Out_ArrayInterfaces">Matriz de ponteiros de interface. Se o método for bem-sucedido, cada membro da matriz contém um ponteiro de interface válido ou NULL. 
			/// O chamador deve liberar os ponteiros de interface quando o EVR chamar ICarenMFTopologyServiceLookupClient::LiberarPonteirosServicos, (ou anterior). Se o método falhar, cada membro da 
			/// matriz é nulo.</param>
			/// <param name="Param_TamanhoMatriz">Um valor que especifica o dimensionar do (Param_Out_ArrayInterfaces) matriz. O valor deve ser pelo menos 1. Na implementação atual, não há nenhum 
			/// motivo para especificar um Dimensionar de matriz maior que um elemento. O valor não é alterado na saída.</param>
			CarenResult PesquisarServico(
				Enumeracoes::CA_MF_SERVICE_LOOKUP_TYPE Param_EscopoPesquisa,
				UInt32 Param_Indice, String^ Param_GuidServico,
				String^ Param_IID,
				[Out] cli::array<ICaren^>^% Param_Out_ArrayInterfaces,
				[Out] UInt32% Param_TamanhoMatriz);
		};

		/// <summary>
		/// (IMFTopologyServiceLookupClient) - Interface responsável por inicializar um mixer de vídeo ou apresentador. Essa interface é implementada por misturadores e apresentadores e permite 
		/// que eles consultem o renderizador de vídeo aprimorado (EVR) para ponteiros de interface.
		/// </summary>
		[CategoryAttribute("IMFTopologyServiceLookupClient - ")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFTopologyServiceLookupClient.")]
		[Guid("5717881A-5013-4EB0-86A3-7354728AA877")]
		public interface class ICarenMFTopologyServiceLookupClient : ICaren
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
			/// (InitServicePointers) - Sinaliza o mixer ou apresentador para consultar o renderizador de vídeo aprimorado (EVR) para ponteiros de interface.
			/// </summary>
			/// <param name="Param_QueryInterface">Ponteiro para o ICarenMFTopologyServiceLookup interface. Para consultar o EVR para uma interface, 
			/// chame ICarenMFTopologyServiceLookup::PesquisarServico.</param>
			CarenResult IniciarServicosPonteiros(ICarenMFTopologyServiceLookup^ Param_QueryInterface);

			/// <summary>
			/// (ReleaseServicePointers) - Sinaliza o objeto para liberar os ponteiros de interface obtidos do renderizador de vídeo aprimorado (EVR).
			/// Depois que esse método é chamado, quaisquer ponteiros de interface obtidos durante a chamada anterior para ICarenMFTopologyServiceLookupClient::IniciarServicosPonteiros não 
			/// são mais válidos. O objeto deve liberá-los.
			/// </summary>
			CarenResult LiberarPonteirosServicos();
		};

		/// <summary>
		/// (IMFRateSupport) - Interface responsável por consultar o intervalo de taxas de reprodução que são suportadas, incluindo a reprodução inversa.
		/// Para obter um ponteiro para essa interface, chame ICaren::ObterServiço com o identificador de serviço MF_RATE_CONTROL_SERVICE ou utilize o método nativo.
		/// </summary>
		[CategoryAttribute("IMFRateSupport - Consulta taxas de reprodução e suporte.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFRateSupport.")]
		[Guid("8B12498B-5B50-4151-B550-B18CD0E0C6E2")]
		public interface class ICarenMFRateSupport : ICaren
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
			/// (GetFastestRate) - Obtém a taxa de reprodução mais rápida suportada pelo objeto.
			/// </summary>
			/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução de encaminhamento mais rápida ou a taxa de reprodução inversa.</param>
			/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução mais rápida diluído. Caso contrário, o método recupera o mais rápido não-diluído taxa de reprodução. 
			/// Para alguns formatos (como ASF), desbaste significa descartar todos os quadros que não são I-frames. Se um componente produz dados de fluxo, como uma fonte de mídia ou um 
			/// demultiplexer, ele deve prestar atenção para o (Param_Thin) parâmetro e retornar MF_E_THINNING_UNSUPPORTED se ele não é possível Thin o fluxo.</param>
			/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais rápida que o objeto oferece suporte.</param>
			CarenResult ObterTaxaReproduçãoMaisRapida(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao);

			/// <summary>
			/// (GetSlowestRate) - Recupera a taxa de reprodução mais lenta suportada pelo objeto.
			/// </summary>
			/// <param name="Param_Diracao">Especifica se a consulta para a taxa de reprodução direta mais lenta ou a taxa de reprodução inversa.</param>
			/// <param name="Param_Thin">Se true, o método recupera a taxa de reprodução diluído mais lenta. Caso contrário, o método recupera a taxa de reprodução mais lenta não Diluível. 
			/// O valor retornado em Plfrate representa um limite inferior. A reprodução a esta taxa não é garantida. Chame ICarenMFRateSupport::SuporteTaxa para verificar se a taxa de limite 
			/// é suportado. Por exemplo, um componente que ofereça suporte a taxas arbitrariamente lentas retornará zero em (Param_Out_TaxaReproducao), e os aplicativos devem chamar 
			/// (SuporteTaxa) separadamente para determinar se o componente oferece suporte à taxa 0.</param>
			/// <param name="Param_Out_TaxaReproducao">Recebe a taxa de reprodução mais lenta que o objeto oferece suporte.</param>
			CarenResult ObterTaxaReproduçãoMaisLenta(Enumeracoes::CA_MFRATE_DIRECTION Param_Diracao, Boolean Param_Thin, [Out] float% Param_Out_TaxaReproducao);

			/// <summary>
			/// (IsRateSupported) - Consulta se o objeto oferece suporte a uma taxa de reprodução especificada.
			/// </summary>
			/// <param name="Param_Thin">Se true, o método consulta se o objeto oferece suporte a taxa de reprodução com desbaste. Caso contrário, o método consultará se o objeto suporta a taxa de 
			/// reprodução sem desbaste.</param>
			/// <param name="Param_Taxa">A taxa de reprodução para consulta.</param>
			/// <param name="Param_Out_TaxaSuportada">Se o objeto não suportar a taxa de reprodução fornecida em (Param_Taxa), esse parâmetro receberá a taxa de reprodução suportada mais próxima. 
			/// Se o método retorna SS_OK, esse parâmetro recebe o valor fornecido em (Param_Taxa).</param>
			CarenResult SuporteTaxaEspecifica(Boolean Param_Thin, float Param_Taxa, [Out] float% Param_Out_TaxaSuportada);
		};

		/// <summary>
		/// (IMFRateControl) - Interface responsável por obter ou definir a taxa de reprodução.
		/// </summary>
		[CategoryAttribute("IMFRateControl - Controla taxas de reprodução.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFRateControl.")]
		[Guid("1BC89272-01B3-4342-B04D-057BE0EED163")]
		public interface class ICarenMFRateControl : ICaren
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
			/// (GetRate) - Obtém a taxa de reprodução atual.
			/// </summary>
			/// <param name="Param_Out_Thin">Recebe o valor true se o fluxo está sendo diluído no momento. Se o objeto não oferece suporte a desbaste, esse parâmetro sempre recebe
			/// o valor false.</param>
			/// <param name="Param_Out_Taxa">Recebe a taxa de reprodução atual.</param>
			CarenResult ObterTaxa([Out] Boolean% Param_Out_Thin, [Out] float% Param_Out_Taxa);

			/// <summary>
			/// (SetRate) - Define a taxa de reprodução.
			/// </summary>
			/// <param name="Param_Thin">Se true, os fluxos de mídia são diluídos. Caso contrário, o fluxo não é diluído. Para fontes de mídia e demultiplexers, o objeto deve Thin os fluxos 
			/// quando esse parâmetro é true. Para transformações downstream, como decodificadores e Multiplexers, esse parâmetro é informativo; Ele notifica o objeto que os fluxos de entrada 
			/// são diluídos.</param>
			/// <param name="Param_Taxa">A taxa de reprodução solicitada. Os valores postive indicam a reprodução direta, os valores negativos indicam a reprodução inversa, e zero indica 
			/// esfregando (a fonte entrega um único quadro).</param>
			CarenResult DefinirTaxa(Boolean Param_Thin, float Param_Taxa);
		};

		/// <summary>
		/// (IMFMediaSession) - Interface responsável por fornecer controles de reprodução para conteúdo protegido e desprotegido. A sessão de mídia e os objetos de sessão do caminho de mídia 
		/// protegida(PMP) expõem essa interface. Essa interface é a interface principal que os aplicativos usam para controlar o pipeline do Media Foundation.
		/// </summary>
		[CategoryAttribute("IMFMediaSession - Controles de reprodução de conteúdo.")]
		[DescriptionAttribute("Interface responsável por expor os métodos da IMFMediaSession.")]
		[Guid("6B506B17-C575-4D0E-AE80-C490199B3984")]
		public interface class ICarenMFMediaSession : ICarenMFMediaEventGenerator
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
			/// (ClearTopologies) - Limpa todas as apresentações que estão enfileiradas para reprodução na sessão de mídia.
			/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento (MESessionTopologiesCleared).
			/// </summary>
			CarenResult LimparTopologias();

			/// <summary>
			/// (Close) - Fecha a sessão de mídia e libera todos os recursos que ele está usando.
			/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento(MESessionClosed) .
			/// </summary>
			CarenResult Fechar();

			/// <summary>
			/// (GetClock) - Recupera o relógio de apresentação da sessão de mídia.
			/// </summary>
			/// <param name="Param_Out_Relogio">Recebe o ponteiro para o relogio de apresentação. O chamador deve liberar a interface.</param>
			CarenResult ObterRelogio([Out] ICarenMFClock^% Param_Out_Relogio);

			/// <summary>
			/// (GetFullTopology) - Obtém uma topologia da sessão de mídia.
			/// </summary>
			/// <param name="Param_Flags">Zero ou mais sinalizadores da enumeração CA_MESESSION_GETFULLTOPOLOGY_FLAGS .</param>
			/// <param name="Param_TopoId">O identificador da topologia. Este parâmetro será ignorado se o (Param_Flags) parâmetro contém o MFSESSION_GETFULLTOPOLOGY_CURRENT sinalizador.</param>
			/// <param name="Param_Out_TopologiaCompleta">Recebe um ponteiro para a topologia. O chamador deve liberar a interface.</param>
			CarenResult ObterTopologiaCompleta(Enumeracoes::CA_MFSESSION_GETFULLTOPOLOGY_FLAGS Param_Flags, UInt64 Param_TopoId, [Out] ICarenMFTopology^% Param_Out_TopologiaCompleta);

			/// <summary>
			/// (GetSessionCapabilities) - Recupera os recursos da sessão de mídia, com base na apresentação atual.
			/// </summary>
			/// <param name="Param_Out_Recursos">Recebe um OU de bit ou de ZERO ou mais dos sinalizadores da enumeração(CA_RECURSOS_SESSAO_MIDIA).</param>
			CarenResult RecuperarRecursosSessao([Out] Enumeracoes::CA_RECURSOS_SESSAO_MIDIA% Param_Out_Recursos);

			/// <summary>
			/// (Pause) - Pausa a sessão de mídia.
			/// Este método pausa o relógio de apresentação. Esse método é assíncrono.Quando a operação for concluída, a sessão de mídia enviará um evento MESessionPaused.
			/// </summary>
			CarenResult Pausar();

			/// <summary>
			/// (SetTopology) - Define uma topologia na sessão de mídia.
			/// </summary>
			/// <param name="Param_Flags">Os flags que determinam o comportamento do método.</param>
			/// <param name="Param_Topologia">Um ponteiro para a topologia a ser definida.</param>
			CarenResult DefinirTopologia(Enumeracoes::CA_MFSESSION_SETTOPOLOGY_FLAGS Param_Flags, ICarenMFTopology^ Param_Topologia);

			/// <summary>
			/// (Shutdown) - Desliga a sessão de mídia e libera todos os recursos usados pela sessão de mídia.
			/// Chame esse método quando você terminar de usar a sessão de mídia, antes da chamada final para ICaren::LiberarReferencia. Caso contrário, seu aplicativo irá vazar memória.
			/// </summary>
			CarenResult Desligar();

			/// <summary>
			/// (Start) - Inicia a sessão de mídia.
			/// Quando esse método é chamado, a sessão de mídia inicia o relógio de apresentação e começa a processar exemplos de mídia. Esse método é assíncrono. Quando o método for concluído, 
			/// a sessão de mídia envia o evento MESessionStarted.
			/// </summary>
			/// <param name="Param_GuidFormatoTempo">um GUID que especifica o formato de hora para o (Param_PosicaoInicio) parâmetro. Este parâmetro pode ser NULO. O valor NULO é equivalente 
			/// a passar em GUID_NULL.</param>
			/// <param name="Param_PosicaoInicio">Uma CA_PropVariant que especifica a posição inicial para reprodução. O significado e o tipo de dados desse parâmetro são indicados pelo 
			/// (Param_GuidFormatoTempo) parâmetro.</param>
			CarenResult Iniciar(String^ Param_GuidFormatoTempo, Estruturas::CA_PropVariant^ Param_PosicaoInicio);

			/// <summary>
			/// (Stop) - Interrompe a sessão de mídia.
			/// Esse método é assíncrono. Quando a operação for concluída, a sessão de mídia enviará o evento MESessionStopped. 
			/// </summary>
			CarenResult Parar();
		};










		//NOVAS INTERFACES

		/// <summary>
		/// (IMFFinalizableMediaSink) - Opcionalmente suportado por sinks de mídia para executar tarefas necessárias antes do desligamento. Essa interface é normalmente exposta por 
		/// sinks de arquivo  ou seja, a Media Sink que escreve em um arquivo. Ele é usado para executar tarefas como lavar dados para disco ou atualizar um cabeçalho de arquivo.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		[Guid("F47794CB-864D-419C-8504-CE822E1E3A4F")]
		public interface class ICarenMFFinalizableMediaSink : ICarenMFMediaSink
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
			/// (BeginFinalize) - Notifica a mídia para tomar as medidas assíncronas que precisa para terminar suas tarefas.
			/// </summary>
			/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto assíncrono. O chamador deve implementar esta interface.</param>
			/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. 
			/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
			CarenResult FinalizarAsync(ICarenMFAsyncCallback^ Param_Callback, ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (EndFinalize) - Completa uma operação de finalização assíncrona.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que o objeto de retorno de chamada recebeu no método 
			/// ICarenMFAsyncCallback::Invoke.</param>
			CarenResult CompletarFinalizarAsync(ICarenMFAsyncResult^ Param_Resultado);
		};
	
		/// <summary>
		/// (IMFTranscodeProfile) - Interface responsável por armazenar as configurações de configuração que o construtor de topologia usa para gerar a topologia de transcódigo 
		/// para o arquivo de saída. Essas configurações são especificadas pelo chamador e incluem propriedades de fluxo de áudio e vídeo, configurações do codificador e configurações 
		/// de contêiner especificadas pelo chamador.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("557D90D9-698C-4975-82A0-357B84E72E6E")]
		public interface class ICarenMFTranscodeProfile : ICaren
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
			/// (GetAudioAttributes) - Obtém as configurações de fluxo de áudio definidas no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém as configurações atuais do fluxo de Áudio. 
			/// O chamador deve liberar o ponteiro da interface.</param>
			CarenResult ObterAtributosAudio([Out] ICarenMFAttributes^% Param_Out_Atributos);

			/// <summary>
			/// (GetContainerAttributes) - Obtém as configurações do contêiner definidas no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém o tipo de contêiner atual para o arquivo 
			/// de saída. O chamador deve liberar o ponteiro da interface.</param>
			CarenResult ObterContainerAtributos([Out] ICarenMFAttributes^% Param_Out_Atributos);

			/// <summary>
			/// (GetVideoAttributes) - Obtém as configurações de fluxo de vídeo que estão atualmente definidas no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Out_Atributos">Recebe um ponteiro para a interface ICarenMFAttributes do armazenamento de atributos que contém as configurações atuais do fluxo de Vídeo. 
			/// O chamador deve liberar o ponteiro da interface.</param>
			CarenResult ObterAtributosVideo([Out] ICarenMFAttributes^% Param_Out_Atributos);

			/// <summary>
			/// (SetAudioAttributes) - Define as configurações de configuração do fluxo de áudio no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do fluxo de Áudio. Os valores de atributo 
			/// especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
			CarenResult DefinirAtributosAudio(ICarenMFAttributes^ Param_Atributos);

			/// <summary>
			/// (SetContainerAttributes) - Define as configurações de configuração do contêiner no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do contêiner no qual o arquivo 
			/// transcodificado será armazenado. Os valores de atributo especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
			CarenResult DefinirAtributosContainer(ICarenMFAttributes^ Param_Atributos);

			/// <summary>
			/// (SetVideoAttributes) - Define as configurações de configuração do fluxo de vídeo no (Perfil Transcode).
			/// </summary>
			/// <param name="Param_Atributos">Ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos que contém as configurações do fluxo de Vídeo. Os valores de atributo 
			/// especificados sobreescrevem quaisquer valores existentes armazenados no perfil transcódigo(Transcode).</param>
			CarenResult DefinirAtributosVideo(ICarenMFAttributes^ Param_Atributos);
		};

		/// <summary>
		/// (IMFTranscodeSinkInfoProvider) - Interface implementada pelo objeto de ativação do dissipador de transcodificação(Transcode).
		/// O objeto de ativação do dissipador de transcódigo pode ser usado para criar qualquer um dos seguintes dissipadores de arquivos: File Sink - 3GP, MP3, MP4.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("C40896FA-AB88-49C9-9F19-31026AC9AD7F")]
		public interface class ICarenMFTranscodeSinkInfoProvider : ICaren
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
			/// (GetSinkInfo) - Obtém os tipos de mídia para os fluxos de áudio e vídeo especificados no perfil de transcódigo.
			/// </summary>
			/// <param name="Param_Out_SinkInfo">Recebe uma estrutura CA_MF_TRANSCODE_SINK_INFO. Se o método for bem-sucedido, o método atribui ponteiros do ICarenMFMediaType aos membros 
			/// pAudioMediaType e pVideoMediaType desta estrutura. O método pode definir qualquer membro como NULO. Se um dos membros não for NULO após o retorno do método, o chamador deve 
			/// liberar os ponteiros das interfaces.</param>
			CarenResult ObterSinkInfo([Out] CA_MF_TRANSCODE_SINK_INFO^% Param_Out_SinkInfo);

			/// <summary>
			/// (SetOutputByteStream) - Define um fluxo de byte de saída para o dissipador de mídia transcodificado.
			/// </summary>
			/// <param name="Param_ByteStream">Um ponteiro para a interface ICarenMFActivate de um objeto de ativação de fluxo de bytes(Byte-Stream).</param>
			CarenResult DefinirFluxoBytesSaida(ICarenMFActivate^ Param_ByteStream);

			/// <summary>
			/// (SetOutputFile) - Define o nome do arquivo de saída codificado.
			/// </summary>
			/// <param name="Param_NomeArquivo">Uma string que contém o nome do arquivo de saida.</param>
			CarenResult DefinirArquivoSaida(String^ Param_NomeArquivo);

			/// <summary>
			/// (SetProfile) - Define o perfil de transcodificação no objeto de ativação do dissipador de transcódigo.
			/// </summary>
			/// <param name="Param_Profile">Um ponteiro para a interface ICarenMFTranscodeProfile.</param> 
			CarenResult DefinirProfile(ICarenMFTranscodeProfile^ Param_Profile);

		};

		/// <summary>
		/// (IMFMetadata) - Interface responsável por gerenciar metadados para um objeto. Metadados são informações que descrevem um arquivo de mídia, fluxo ou outro conteúdo. Metadados 
		/// consiste em propriedades individuais, onde cada propriedade contém um nome descritivo e um valor. Uma propriedade pode estar associada a uma linguagem específica.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("A80C7DDA-8BCF-466F-BCC3-171061C9453A")]
		public interface class ICarenMFMetadata : ICaren
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
			/// (DeleteProperty) - Exclui uma propriedade de metadados.
			/// </summary>
			/// <param name="Param_NomePropriedade">Uma string contendo o nome da propriedade a ser deletada.</param>
			CarenResult DeletarPropriedade(String^ Param_NomePropriedade);

			/// <summary>
			/// (GetAllLanguages) - Obtém uma lista dos idiomas em que os metadados estão disponíveis.
			/// </summary>
			/// <param name="Param_Out_ListaIdiomas">Retorna uma CA_PropVariant com uma lista de idiomas. A lista é devolvida como uma matriz de seqüência de sequências de caracteres amplos. Cada string na matriz é uma tag de idioma compatível com RFC 1766.</param>
			CarenResult ObterListaIdiomas([Out] CA_PropVariant^% Param_Out_ListaIdiomas);

			/// <summary>
			/// (GetAllPropertyNames) - Obtém uma lista de todos os nomes de propriedade de metadados neste objeto.
			/// </summary>
			/// <param name="Param_Out_ListaNomesProps">Retorna uma CA_PropVariant com os nomes de todas as propriedades. Se não houver propriedades disponíveis, o tipo CA_PropVariant será VT_EMPTY. Caso contrário, o tipo CA_PropVariant é VT_VECTOR | VT_LPWSTR. </param>
			CarenResult ObterTodosNomesPropriedade([Out] CA_PropVariant^% Param_Out_ListaNomesProps);

			/// <summary>
			/// (GetLanguage) - Obtém a configuração atual do idioma.
			/// </summary>
			/// <param name="Param_Out_IdiomaRFC1766">Recebe uma string contendo uma tag do idioma compatível com a RFC 1766.</param>
			CarenResult ObterIdioma([Out] String^% Param_Out_IdiomaRFC1766);

			/// <summary>
			/// (GetProperty) - Obtém o valor de uma propriedade de metadados.
			/// </summary>
			/// <param name="Param_NomePropriedade">Uma string que contém o nome da propriedade a ser recuperada o valor.</param>
			/// <param name="Param_Out_Valor">Recebe uma estrutura CA_PropVariant contendo o valor. O tipo CA_PropVariant depende da propriedade. Para propriedades multivalorizadas, o CA_PropVariant é um tipo VT_VECTOR.</param>
			CarenResult ObterPropriedade(String^ Param_NomePropriedade, [Out] CA_PropVariant^% Param_Out_Valor);

			/// <summary>
			/// (SetLanguage) - Define o idioma para definir e recuperar metadados.
			/// </summary>
			/// <param name="Param_IdiomaRFC1766">Uma string contendo uma tag de idioma compatível com o RFC 1766.</param>
			CarenResult DefinirIdioma(String^ Param_IdiomaRFC1766);

			/// <summary>
			/// (SetProperty) - Define o valor de uma propriedade de metadados.
			/// </summary>
			/// <param name="Param_NomePropriedade">Uma string com o nome da propriedade.</param>
			/// <param name="Param_Valor">Uma CA_PropVariant que contém o valor da propriedade. Para propriedades multivalorizadas, use um CA_PropVariant com um tipo de VT_VECTOR.</param>
			CarenResult DefinirPropriedade(String^ Param_NomePropriedade, CA_PropVariant^ Param_Valor);
		};

		/// <summary>
		/// (IMFMetadataProvider) - Interface responsável por recuperar metadados de uma fonte de mídia ou outro objeto. Se uma fonte de mídia suportar essa interface, ela deve expor a 
		/// interface como um serviço. Para obter um ponteiro para esta interface a partir de uma fonte de mídia, ligue para o ICarenMFGetService::ObterServico. O identificador de serviço 
		/// é MF_METADATA_PROVIDER_SERVICE. Outros tipos de objeto podem expor essa interface através do (ConsultarInterface). Use esta interface para obter um ponteiro para a interface 
		/// ICarenMFMetadata.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("A322D244-76A0-424C-A9CA-777A50206533")]
		public interface class ICarenMFMetadataProvider : ICaren
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
			/// (GetMFMetadata) - Obtém uma coleção de metadados, seja para uma apresentação inteira, ou para um fluxo na apresentação.
			/// </summary>
			/// <param name="Param_Descritor">Ponteiro para a interface do descritor de apresentação(ICarenMFPresentationDescriptor) da fonte de mídia.</param>
			/// <param name="Param_IdenticaoFluxo">Se esse parâmetro for zero, o método recuperará metadados que se aplicam a toda a apresentação. Caso contrário, este parâmetro especifica 
			/// um identificador de fluxo e o método recupera metadados para esse fluxo. Para obter o identificador de fluxo de um fluxo, ligue para o ICarenMFStreamDescriptor::ObterIdentificadorFluxo.</param>
			/// <param name="Param_Flags">Reservado. Deixe como ZERO.</param>
			/// <param name="Param_Out_Metadata">Recebe um ponteiro para a interface ICarenMFMetadata. Use esta interface para acessar os metadados. O chamador deve liberar a interface.</param>
			CarenResult ObterMFMetadados(ICarenMFPresentationDescriptor^ Param_Descritor, UInt32 Param_IdenticaoFluxo, UInt32 Param_Flags, [Out] ICarenMFMetadata^% Param_Out_Metadata);
		};

		/// <summary>
		/// (IMFNetCredential) - Interface responsável por definir e recuperar informações sobre o nome de usuário e senha para fins de autenticação.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("CA319950-D1A2-40A1-A0B1-A459AC38A028")]
		public interface class ICarenMFNetCredential : ICaren
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
			/// (GetPassword) - Recupera a senha.
			/// </summary>
			/// <param name="Param_Ref_Senha">Um buffer de bytes que recebe a (SENHA). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
			/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados.</param>
			/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Senha), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
			/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
			/// <param name="Param_Criptografada">Se TRUE, o método retorna uma sequência criptografada. Caso contrário, o método retorna uma sequência não criptografada.</param>
			CarenResult ObterPassword(
				cli::array<Byte>^% Param_Ref_Senha,
				UInt32% Param_Ref_LarguraDados,
				Boolean Param_Criptografada);

			/// <summary>
			/// (GetUser) - Recupera o nome de usuário.
			/// </summary>
			/// <param name="Param_Ref_Usuario">Um buffer de bytes que recebe o (USUÁRIO). Para encontrar o tamanho de buffer necessário, defina este parâmetro como NULO. Se Param_Criptografada 
			/// for FALSE, o buffer contém uma sequência de caracteres amplos. Caso contrário, o buffer contém dados criptografados.</param>
			/// <param name="Param_Ref_LarguraDados">Na entrada, especifica o tamanho do buffer (Param_Ref_Usuario), em bytes. Na saída, recebe o tamanho de buffer necessário. Se 
			/// Param_Criptografada for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
			/// <param name="Param_Criptografada">Se TRUE,o método retorna uma seqüência criptografada. Caso contrário, o método retorna uma seqüência não criptografada.</param>
			CarenResult ObterUsuario(
				cli::array<Byte>^% Param_Ref_Usuario,	
				UInt32% Param_Ref_LarguraDados,
				Boolean Param_Criptografada);

			/// <summary>
			/// (LoggedOnUser) - Verifica se as credenciais registradas devem ser usadas.
			/// </summary>
			/// <param name="Param_Out_Resultado">Recebe um valor booleano. Se as credenciais registradas devem ser usadas, o valor é TRUE. Caso contrário, o valor é FALSO.</param>
			CarenResult CredencialNecessaria([Out] Boolean% Param_Out_Resultado);

			/// <summary>
			/// (SetPassword) - Define a senha.
			/// </summary>
			/// <param name="Param_Senha">Um buffer de bytes que contém a (SENHA). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
			/// buffer contém dados criptografados.</param>
			/// <param name="Param_Ref_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
			/// <param name="Param_Criptografar">Se TRUE, a senha será criptografada. Caso contrário, a senha não é criptografada.</param>
			CarenResult DefinirPassword(
				cli::array<Byte>^ Param_Senha,
				UInt32% Param_Ref_LarguraDados,
				Boolean Param_Criptografar);

			/// <summary>
			/// (SetUser) - Define o nome de usuário.
			/// </summary>
			/// <param name="Param_Usuario">Um buffer de bytes que contém o (USUÁRIO). Se Param_Criptografar for FALSE, o buffer será uma sequência de caracteres amplos. Caso contrário, o 
			/// buffer contém dados criptografados.</param>
			/// <param name="Param_Ref_LarguraDados">Tamanho de Param_Senha, em bytes. Se Param_Criptografar for FALSE, o tamanho inclui o caractere nulo de terminação.</param>
			/// <param name="Param_Criptografar">Se TRUE, o usuário será criptografado. Caso contrário, o usuário não é criptografado.</param>
			CarenResult DefinirUsuario(
				cli::array<Byte>^ Param_Usuario,
				UInt32% Param_Ref_LarguraDados,
				Boolean Param_Criptografar);
		};

		/// <summary>
		/// (IMFNetCredentialCache) - Interface responsável por obter credenciais do cache de credenciais.
		/// Esta interface é implementada pelo objeto de cache credencial.
		/// Os aplicativos que implementam a interface IMFNetCredentialManager podem usar esse objeto para armazenar as credenciais do usuário.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("F00C8EC5-266C-41A6-BBDC-5C5388D1B839")]
		public interface class ICarenMFNetCredentialCache : ICaren
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
			/// (GetCredential) - Recupera o objeto de credencial para a URL especificada.
			/// </summary>
			/// <param name="Param_Url">Uma string contendo a URL para a qual a credencial é necessária.</param>
			/// <param name="Param_Realm">Uma string contendo o Realm(Define o espaço de proteção do servidor, é um dominio protegido que pode ser compartilhado) para a autenticação.</param>
			/// <param name="Param_FlagsAutenticacao">Bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetAuthenticationFlags.</param>
			/// <param name="Param_Out_Credencial">Recebe um ponteiro para a interface ICarenMFNetCredential. O chamador deve liberar a interface.</param>
			/// <param name="Param_Out_FlagsRequerimento">Recebe bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetCredentialRequirements.</param>
			CarenResult ObterCredencial(
				String^ Param_Url, 
				String^ Param_Realm, 
				CA_MFNetAuthenticationFlags Param_FlagsAutenticacao, 
				[Out] ICarenMFNetCredential^% Param_Out_Credencial, 
				[Out] CA_MFNetCredentialRequirements% Param_Out_FlagsRequerimento);

			/// <summary>
			/// (SetGood) - Relata se o objeto de credencial fornecido passou com sucesso no desafio de autenticação.
			/// </summary>
			/// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential.</param>
			/// <param name="Param_Resultado">TRUE se o objeto de credencial teve sucesso no desafio de autenticação; caso contrário, FALSE.</param>
			CarenResult DefinirResultadoCredencial(
				ICarenMFNetCredential^ Param_Credencial, 
				Boolean Param_Resultado);

			/// <summary>
			/// (SetUserOptions) - Especifica como as credenciais do usuário são armazenadas.
			/// </summary>
			/// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential. Obtenha este ponteiro ligando para ICarenMFNetCredentialCache::ObterCredencial.</param>
			/// <param name="Param_Opcoes">Bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetCredentialOptions.</param>
			CarenResult DefinirOpcoesArmazenamentoUsuario(
				ICarenMFNetCredential^ Param_Credencial, 
				CA_MFNetCredentialOptions Param_Opcoes);
		};

		/// <summary>
		/// (IMFNetCredentialManager) - Interface implementada por aplicativos para fornecer credenciais de usuário para uma fonte de rede.
		/// Para usar esta interface, implemente-a em seu aplicativo. Em seguida, crie um objeto de armazenamento de propriedades e defina a propriedade MFNETSOURCE_CREDENTIAL_MANAGER. 
		/// O valor da propriedade é um ponteiro para a interface ICarenMFNetCredentialManager do seu aplicativo. Em seguida, passe a loja de propriedades para uma das funções de criação 
		/// do resolvedor de origem, como ICarenMFSourceResolver::CriarObjetoFromUrl, no parâmetro (Param_Propriedades).
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("3D85FF23-E468-4710-89E5-C6A0C78F1BFC")]
		public interface class ICarenMFNetCredentialManager : ICaren
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
			/// (BeginGetCredentials) - Começa uma solicitação assíncrona para recuperar as credenciais do usuário.
			/// </summary>
			/// <param name="Param_GetParam">Uma estrutura MFNetCredentialManagerGetParam.</param>
			/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface.</param>
			/// <param name="Param_ObjetoEstado">Um ponteiro para um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. O objeto é devolvido ao chamador quando o retorno de 
			/// chamada é invocado.</param>
			CarenResult ObterCredenciaisAsync(
				CA_MFNetCredentialManagerGetParam^ Param_GetParam, 
				ICarenMFAsyncCallback^ Param_Callback, 
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (EndGetCredentials) - Completa uma solicitação assíncrona para recuperar as credenciais do usuário.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para uma interface ICarenMFAsyncResult que contém o resultado assíncrono.</param>
			/// <param name="Param_Out_Credencial">Recebe um ponteiro para a interface ICarenMFNetCredential, que é usada para recuperar as credenciais. O chamador deve liberar a interface.</param>
			CarenResult FinalizarCredenciaisAsync(
				ICarenMFAsyncResult^ Param_Resultado, 
				[Out] ICarenMFNetCredential^% Param_Out_Credencial);

			/// <summary>
			/// (SetGood) - Especifica se as credenciais do usuário tiveram sucesso no desafio de autenticação. A fonte da rede chama esse método para informar o aplicativo se as 
			/// credenciais do usuário foram autenticadas.
			/// </summary>
			//// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential.</param>
			/// <param name="Param_Resultado">Valor booleano. O valor é TRUE se as credenciais tiverem êxito no desafio de autenticação. Caso contrário, o valor é FALSE.</param>
			CarenResult DefinirResultadoCredencial(
				ICarenMFNetCredential^ Param_Credencial,
				Boolean Param_Resultado);
		};
		
		/// <summary>
		/// (IMFNetResourceFilter) - Interface responsável por notificar o aplicativo quando um fluxo de byte solicita uma URL e permite que o aplicativo bloqueie o redirecionamento da URL.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("21802177-3677-4A72-82C8-F893E6D5AC5E")]
		public interface class ICarenMFNetResourceFilter : ICaren
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
			/// Delegate do evento OnRedirect.
			/// </summary>
			delegate void Delegate_OnRedirect(String^ Param_Url, Boolean Param_Cancelar);

			/// <summary>
			/// Delegate do evento OnSendingRequest.
			/// </summary>
			delegate void Delegate_OnSendingRequest(String^ Param_Url);



			//Define os eventos

			/// <summary>
			/// Evento chamado quando o fluxo de byte redireciona para uma URL.
			/// </summary>
			event Delegate_OnRedirect^ OnRedirect;

			/// <summary>
			/// Evento chamado quando o fluxo de byte solicita uma URL.
			/// </summary>
			event Delegate_OnSendingRequest^ OnSendingRequest;



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
		/// (IMFSourceOpenMonitor) - Interface responsável por receber notificações de uma fonte de rede sobre o progresso de uma operação aberta assíncrona.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("848282D1-2754-4943-A617-8FBCBAA909F0")]
		public interface class ICarenMFSourceOpenMonitor : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			/// <summary>
			/// Delegate do evento OnRedirect.
			/// </summary>
			delegate void Delegate_OnSourceEvent(ICarenMFMediaEvent^ Param_Evento);


			//Define os eventos

			/// <summary>
			/// Evento chamado pela fonte de rede quando a operação aberta começa ou termina.
			/// </summary>
			event Delegate_OnSourceEvent^ OnSourceEvent;


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
		/// (IMFByteStreamHandler) - Interface responsável por criar uma fonte de mídia a partir de um fluxo de bytes.
		/// Os aplicativos não usam essa interface diretamente. Esta interface é exposta por manipuladores de fluxo de byte, que são usados pelo resolvedor de origem. Quando o manipulador 
		/// de fluxo de byte recebe um fluxo de bytes, ele analisa o fluxo e cria uma fonte de mídia. 
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]		
		[Guid("1D66FB2C-0C1E-4DE6-BA3A-E0BD399E85C7")]
		public interface class ICarenMFByteStreamHandler : ICaren
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
			/// (BeginCreateObject) - Começa uma solicitação assíncrona para criar uma fonte de mídia a partir de um fluxo de bytes.
			/// </summary>
			/// <param name="Param_FluxoBytes">Ponteiro para a interface ICarenMFByteStream do fluxo de byte.</param>
			/// <param name="Param_Url">String que contém a URL original do fluxo de bytes. Este parâmetro pode ser NULO.</param>
			/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_SOURCE_RESOLVER_FLAGS.</param>
			/// <param name="Param_Props">Ponteiro para a interface ICarenPropertyStore de uma loja de propriedades. O manipulador de fluxo de bytes pode usar esta loja de propriedades 
			/// para configurar o objeto. Este parâmetro pode ser NULO.</param>
			/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro IUnknown na interface ICaren ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona 
			/// passando este ponteiro para o método ICarenMFByteStreamHandler::CancelarCriacaoObjeto. O chamador deve liberar a interface. Este parâmetro pode ser NULO.</param>
			/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface.</param>
			/// <param name="Param_ObjetoEstado">Um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado.
			/// O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
			CarenResult CriarObjetoAsync(
				ICarenMFByteStream^ Param_FluxoBytes,
				String^ Param_Url,
				CA_SOURCE_RESOLVER_FLAGS Param_Flags,
				ICarenPropertyStore^ Param_Props,
				[Out] ICaren^% Param_Out_CookieCancelamento,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (CancelObjectCreation) - Cancela o pedido atual para criar uma fonte de mídia.
			/// </summary>
			/// <param name="Param_CookieCancelamento">Ponteiro para a interface ICaren que foi retornada no parâmetro (Param_Out_CookieCancelamento) do método 
			/// ICarenMFByteStreamHandler::CriarObjetoAsync.</param>
			CarenResult CancelarCriacaoObjeto(ICaren^ Param_CookieCancelamento);

			/// <summary>
			/// (EndCreateObject) - Completa um pedido assíncrono para criar uma fonte de mídia.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para a interface ICarenMFAsyncResult. Passe no mesmo ponteiro que seu objeto de retorno de chamada recebeu no método Invocar.</param>
			/// <param name="Param_Out_TipoObjeto">Recebe um membro da enumeração CA_TIPO_OBJETO_CRIADO, especificando o tipo de objeto que foi criado.</param>
			/// <param name="Param_Ref_InterfaceObjeto">Recebe um ponteiro para a interface da fonte de mídia. O chamador deve criar a interface que vai receber o ponteiro.
			/// O chamador deve liberar a interface quando não for mais utilizar.</param>
			CarenResult FinalizarObjetoAsync(
				ICarenMFAsyncResult^ Param_Resultado,
				[Out] CA_TIPO_OBJETO_CRIADO% Param_Out_TipoObjeto,
				ICaren^% Param_Ref_InterfaceObjeto);
			
			/// <summary>
			/// (GetMaxNumberOfBytesRequiredForResolution) - Recupera o número máximo de bytes necessários para criar a fonte de mídia ou determinar que o manipulador de fluxo de bytes não 
			/// pode analisar este fluxo.
			/// </summary>
			/// <param name="Param_Ref_MaximoNumeroBytes">Recebe o número máximo de bytes necessários.</param>
			CarenResult ObterNumerosBytesRequeridosParaResolucao(UInt64% Param_Ref_MaximoNumeroBytes);
		};

		/// <summary>
		/// (IMFNetProxyLocator) - Interface responsável por determinar o proxy a ser usado ao se conectar a um servidor. A fonte de rede usa essa interface.
		/// Os aplicativos podem criar o localizador proxy configurado pelo aplicativo implementando a interface ICarenMFNetProxyLocatorFactory e definindo a MFNETSOURCE_PROXYLOCATORFACTORY 
		/// propriedade no resolver de origem. Caso contrário, a fonte da rede usa a implementação padrão da Media Foundation.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("9810692C-9427-4071-9820-9A6C9DC58EC5")]
		public interface class ICarenMFNetProxyLocator : ICaren
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
			/// (Clone) - Cria uma nova instância do localizador proxy padrão.
			/// </summary>
			/// <param name="Param_Out_ProxyLocator">Recebe um ponteiro para a interface ICarenMFNetProxyLocator do novo proxy locator. O chamador deve liberar a interface.</param>
			CarenResult Clonar([Out] ICarenMFNetProxyLocator^% Param_Out_ProxyLocator);

			/// <summary>
			/// (FindFirstProxy) - Inicializa o objeto localizador proxy.
			/// </summary>
			/// <param name="Param_Host">Uma string contendo o nome de host do servidor de destino</param>
			/// <param name="Param_Url">Uma string contendo a URL de destino.</param>
			/// <param name="Param_Reservado">Reservados. Definido como FALSE.</param>
			CarenResult ProcurarPrimeiroProxy(
				String^ Param_Host, 
				String^ Param_Url, 
				Boolean Param_Reservado);

			/// <summary>
			/// (FindNextProxy) - Determina o próximo proxy a ser usado.
			/// </summary>
			CarenResult ProcurarProximoProxy();

			/// <summary>
			/// (GetCurrentProxy) - Recupera as informações de proxy atuais, incluindo nome de host e porta.
			/// </summary>
			/// <param name="Param_Ref_ProxyHostname">Recebe uma string contendo o nome do host proxy e a porta. Defina como NULO para receber a largura necessária para receber os dados.</param>
			/// <param name="Param_Ref_Largura">Na entrada, especifica o número de elementos em Param_Ref_ProxyHostname. Na saída, recebe o tamanho necessário do buffer.</param>
			CarenResult ObterProxyAtual(
				String^% Param_Ref_ProxyHostname, 
				UInt32% Param_Ref_Largura);

			/// <summary>
			/// (RegisterProxyResult) - Mantém um registro do sucesso ou falha do uso do proxy atual.
			/// </summary>
			/// <param name="Param_hrOp">HRESULT especificando o resultado do uso do proxy atual para conexão.</param>
			CarenResult RegistrarResultadoProxy(Int32 Param_hrOp);
		};
		
		/// <summary>
		/// (IMFNetProxyLocatorFactory) - Interface responsável por criar um objeto localizador proxy, que determina o proxy a ser usado.
		/// A fonte de rede usa essa interface para criar o objeto localizador proxy. Os aplicativos podem fornecer sua própria implementação desta interface definindo a propriedade 
		/// MFNETSOURCE_PROXYLOCATORFACTORY. sobre o resolvedor de fonte. Se o aplicativo não definir essa propriedade, a fonte da rede usará o localizador proxy padrão fornecido pela 
		/// Media Foundation.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("70B523A0-B948-4B29-9939-6A88A2708846")]
		public interface class ICarenMFNetProxyLocatorFactory : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Está classe serve de fabrica para o resolvedor de midia criar um proxy personalizado.
			//IMFNetProxyLocatorFactory não tem um inicializaodr default, a biblioteca de Caren que cria uma implmenetação essa interface.

			//Define os delegates

			/// <summary>
			/// Delegate do evento OnCreateProxyLocator.
			/// </summary>
			delegate void Delegate_OnCreateProxyLocator(String^ Param_Protocolo, ICarenMFNetProxyLocator^ Param_ProxyLocator);


			//Define os eventos

			/// <summary>
			/// Evento chamado quando a fonte de midia chama o método ICarenMFNetProxyLocatorFactory::CreateProxyLocator. Este evento é chamado para permitir o usuário configurar 
			/// o proxy locator.
			/// </summary>
			event Delegate_OnCreateProxyLocator^ OnCreateProxyLocator;


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
		/// (IMFDLNASinkInit) - Interface responsável por iniciar o Media Skink da Digital Living Network Alliance (DLNA).
		/// O dissipador de mídia DLNA expõe essa interface. Para obter um ponteiro para esta interface, chame CoCreateInstance ou CoCreateInstanceEx. O CLSID é CLSID_MPEG2DLNASink.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("B72AE7E7-A8B3-4088-A98A-8C6456F896E8")]
		public interface class ICarenMFDLNASinkInit : ICaren
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
			/// (Initialize) - Inicializa o Media Sink para Digital Living Network Alliance (DLNA).
			/// </summary>
			/// <param name="Param_FluxoBytes">Ponteiro para um fluxo de byte. O dissipador de mídia(Media Sink) DLNA escreve dados para este fluxo de bytes. O fluxo de byte deve ser escrito.</param>
			/// <param name="Param_SuportePALVideoFormat">Se TRUE, o Media Sink DLNA aceita formatos de vídeo PAL. Caso contrário, ele aceita formatos de vídeo NTSC.</param>
			CarenResult Inicializar(ICarenMFByteStream^ Param_FluxoBytes, Boolean Param_SuportePALVideoFormat);
		};

		/// <summary>
		/// (IMFLocalMFTRegistration ) - Interface responsável por registrar um Media Foundation Transforms(MFTs) no processo do chamador.
		/// A Sessão de Mídia expõe essa interface como um serviço. Para obter um ponteiro para esta interface, chame o método ICarenMFGetService::ObterServico na Sessão de Mídia com 
		/// o identificador de serviço MF_LOCAL_MFT_REGISTRATION_SERVICE.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("916B8078-1E54-4F44-9F0B-735E7C4C99AC")]
		public interface class ICarenMFLocalMFTRegistration : ICaren
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
			/// (RegisterMFTs) - Registra uma ou mais transformações da Media Foundation (MFTs) no processo do chamador.
			/// </summary>
			/// <param name="Param_MatrizMFTs">Uma matriz de estruturas MFT_REGISTRATION_INFO.</param>
			/// <param name="Param_CountElementos">O número de elementos na matriz (Param_MatrizMFTs).</param>
			CarenResult RegistrarMFTs(cli::array<CA_MFT_REGISTRATION_INFO^>^ Param_MatrizMFTs, UInt32 Param_CountElementos);
		};

		/// <summary>
		/// (IMFMediaEngineSrcElements) - Interface responsável por fornecer ao Media Engine uma lista de recursos de mídia.
		/// A interface ICarenMFMediaEngineSrcElements representa uma lista ordenada de recursos de mídia.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("3563E87E-3F57-45B2-BA9F-E57DB688B173")]
		public interface class ICarenMFMediaEngineSrcElements : ICaren
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
			/// (AddElement) - Adiciona um elemento de origem ao final da lista.
			/// </summary>
			/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
			/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
			/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
			CarenResult AdicionarElemento(
				String^ Param_Url, 
				String^ Param_Tipo, 
				String^ Param_Midia
				);

			/// <summary>
			/// (GetLength) - Obtém o número de elementos de origem na lista.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Recebe o numero de elementos presente na lista.</param>
			CarenResult ObterQuantidade([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (GetMedia) - Obtém o tipo de mídia pretendido de um elemento na lista.
			/// </summary>
			/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::ObterQuantidade.</param>
			/// <param name="Param_Ref_Midia">Recebe uma string que contém uma sequência de consulta de mídia. Se nenhum tipo de mídia for definido, este parâmetro receberá o valor NULO.</param>
			CarenResult ObterTipoMidia(
				UInt32 Param_Index, 
				String^% Param_Ref_Midia);

			/// <summary>
			/// (GetType) - Obtém o tipo MIME de um elemento na lista.
			/// </summary>
			/// <param name="Param_Index">O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::ObterQuantidade.</param>
			/// <param name="Param_Ref_MimeType">Recebe uma string que contém o MIME Type. Se nenhum tipo de MIME for definido, este parâmetro receberá o valor NULO.</param>
			CarenResult ObterTipoMIME(
				UInt32 Param_Index, 
				String^% Param_Ref_MimeType);

			/// <summary>
			/// (GetURL) - Obtém a URL de um elemento na lista.
			/// </summary>
			/// <param name="Param_Index">>O índice baseado em zero do elemento fonte. Para obter o número de elementos de origem, ligue para o ICarenMFMediaEngineSrcElements::ObterQuantidade.</param>
			/// <param name="Param_Ref_Url">Recebe uma string que contém a URL do elemento de origem. Se nenhuma URL for definida, este parâmetro receberá o valor NULO</param>
			CarenResult ObterURL(UInt32 Param_Index, String^% Param_Ref_Url);

			/// <summary>
			/// (RemoveAllElements) - Remove todos os elementos de origem da lista.
			/// </summary>
			CarenResult RemoverTodosElementos();
		};

		/// <summary>
		/// (IMFMediaEngineSrcElementsEx) - Interface responsável por ampliar a interface ICarenMFMediaEngineSrcElements para fornecer recursos adicionais.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("4C5363A2-2B26-4A91-BAC8-78E67759EE85")]
		public interface class ICarenMFMediaEngineSrcElementsEx : ICarenMFMediaEngineSrcElements
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
			/// (AddElementEx) - Fornece uma versão aprimorada do ICarenMFMediaEngineSrcElements::AdicionarElemento para adicionar o sistema-chave destinado a ser usado com conteúdo a um elemento.
			/// </summary>
			/// <param name="Param_Url">A URL do elemento de origem, ou NULO.</param>
			/// <param name="Param_Tipo">O tipo MIME do elemento de origem, ou NULO.</param>
			/// <param name="Param_Midia">Uma sequência de consulta de mídia que especifica o tipo de mídia pretendido ou NULO. Se especificado, a sequência deve estar em conformidade com a especificação W3C Media Queries.</param>
			/// <param name="Param_KeySystem">A Key(Chave) da sessão de mídia.</param>
			CarenResult AdicionarElementoEx(
				String^ Param_Url,
				String^ Param_Tipo,
				String^ Param_Midia,
				String^ Param_KeySystem);

			/// <summary>
			/// (GetKeySystem) - Obtém o sistema-chave para o índice de elemento de origem dado.
			/// </summary>
			/// <param name="Param_Index">O índice de elementos de origem.</param>
			/// <param name="Param_Ref_MimeType">Recebe o tipo MIME do elemento fonte.</param>
			CarenResult ObterKeySystem(
				UInt32 Param_Index, 
				String^% Param_Ref_MimeType);
		};

		/// <summary>
		/// (IMFMediaTimeRange) - Interface responsável por representar uma lista de intervalos de tempo, onde cada intervalo é definido por um tempo de início e fim.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("8C70AB1B-B446-47E5-B119-48FB0456A6C0")]
		public interface class ICarenMFMediaTimeRange : ICaren
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
			/// (AddRange) - Adiciona um novo intervalo à lista de intervalos de tempo.
			/// </summary>
			/// <param name="Param_InicioTime">A hora de partida, em segundos.</param>
			/// <param name="Param_FimTime">O tempo final, em segundos.</param>
			CarenResult AdicionarRange(
				double Param_InicioTime, 
				double Param_FimTime);

			/// <summary>
			/// (Clear) - Limpa a lista de intervalos de tempo.
			/// </summary>
			CarenResult Limpar();

			/// <summary>
			/// (ContainsTime) - Verifica se um tempo especificado está dentro de qualquer um dos intervalos de tempo.
			/// </summary>
			/// <param name="Param_Time">A hora, em segundos.</param>
			CarenResult ContemTime(double Param_Time);

			/// <summary>
			/// (GetEnd) - Obtém o tempo final para um intervalo de tempo especificado.
			/// </summary>
			/// <param name="Param_Index">O índice baseado em zero do intervalo de tempo para consulta. Para obter o número de intervalos de tempo, ligue para o 
			/// ICarenMFMediaTimeRange::ObterQuantidade.</param>
			/// <param name="Param_Out_TimeFinal">Recebe o tempo final, em segundos.</param>
			CarenResult ObterFinal(
				UInt32 Param_Index, 
				[Out] double% Param_Out_TimeFinal);

			/// <summary>
			/// (GetLength) - Obtém o número de intervalos de tempo contidos no objeto.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Recebe a quantidade de intervelos de tempo totais contidos no objeto.</param>
			CarenResult ObterQuantidade([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (GetStart) - Obtém a hora de início para um intervalo de tempo especificado.
			/// </summary>
			/// <param name="Param_Index">O índice baseado em zero do intervalo de tempo para consulta. Para obter o número de intervalos de tempo, ligue para o 
			/// ICarenMFMediaTimeRange::ObterQuantidade.</param>
			/// <param name="Param_Out_TimeInicial">Recebe o tempo de partida, em segundos.</param>
			CarenResult ObterInicio(
				UInt32 Param_Index, 
				[Out] double% Param_Out_TimeInicial);
		};

		/// <summary>
		/// (IMFMediaError) - Interface responsável por fornecer o status de erro atual para o Media Engine.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("120E6123-BB57-4B5E-817F-656AED1731E9")]
		public interface class ICarenMFMediaError : ICaren
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
			/// (GetErrorCode) - Obtém o código de erro.
			/// </summary>
			/// <param name="Param_Out_CodigoErro">Retorna um bandeira da enumeração CA_MF_MEDIA_ENGINE_ERR que vai indicar o erro.</param>
			CarenResult ObterCodigoErro([Out] CA_MF_MEDIA_ENGINE_ERR% Param_Out_CodigoErro);

			/// <summary>
			/// (GetExtendedErrorCode) - Obtém o código de erro estendido.
			/// </summary>
			/// <param name="Param_Out_CodigoErro">Retorna um inteiro de 32 bits assinado que corresponde a um código HRESULT.</param>
			CarenResult ObterCodigoErroEstendido([Out] Int32% Param_Out_CodigoErro);

			/// <summary>
			/// (SetErrorCode) - Define o código de erro.
			/// </summary>
			/// <param name="Param_CodigoErro">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_ERR que vai definir o código de erro.</param>
			CarenResult DefinirCodigoErro(CA_MF_MEDIA_ENGINE_ERR Param_CodigoErro);

			/// <summary>
			/// (SetExtendedErrorCode) - Define o código de erro estendido.
			/// </summary>
			/// <param name="Param_CodigoErro">Um inteiro de 32 bits assinado que corresponde a um HRESULT.</param>
			CarenResult DefinirCodigoErroEstendido(Int32 Param_CodigoErro);
		};

		/// <summary>
		/// (IMFMediaKeySessionNotify) - Interface responsável por fornecer um mecanismo para notificar o aplicativo sobre informações sobre a sessão-chave de mídia.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("CA97F67D-3657-46E8-957B-054D85A88131")]
		public interface class ICarenMFMediaKeySessionNotify : ICaren
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
			/// (KeyAdded) - Notifica a aplicação de que a chave foi adicionada.
			/// </summary>
			CarenResult ChaveAdicionada();

			/// <summary>
			/// (KeyError) - Notifica o aplicativo de que ocorreu um erro durante o processamento da chave.
			/// </summary>
			/// <param name="Param_ErroCode">O código de erro.</param>
			/// <param name="Param_SystemCode">O código especifico de plataforma para maiores informações.</param>
			CarenResult ErroChave(UInt16 Param_ErroCode, UInt32 Param_SystemCode);

			/// <summary>
			/// (KeyMessage) - Passa informações para o aplicativo para que ele possa iniciar uma aquisição chave.
			/// </summary>
			/// <param name="Param_Url">A URL para enviar a mensagem.</param>
			/// <param name="Param_Mensagem">A mensagem para enviar para o aplicativo.</param>
			/// <param name="Param_CoutDataMensagem">O comprimento em bytes de Param_Mensagem.</param>
			CarenResult MensagemChave(
				String^ Param_Url, 
				cli::array<Byte>^ Param_Mensagem, 
				UInt32 Param_CoutDataMensagem);
		};

		/// <summary>
		/// (IMFCdmSuspendNotify) -Interface responsável para permitir que o cliente notifique o Content Decryption Module (CDM) quando os recursos globais devem ser 
		/// colocados em um estado consistente antes da suspensão.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("4F487323-28F9-4E7E-84F3-87F3AAE4CE5A")]
		public interface class ICarenMFCdmSuspendNotify : ICaren
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
			/// (Begin) - Indica que o processo de suspensão está começando e os recursos devem ser trazidos para um estado consistente.
			/// </summary>
			CarenResult Inicio();

			/// <summary>
			/// (End) - A suspensão real está prestes a ocorrer e não serão feitas mais chamadas no Módulo de Descriptografia de Conteúdo (MDL).
			/// </summary>
			CarenResult End();
		};

		/// <summary>
		/// (IMFMediaKeySession) - Interface responsável representar uma sessão com o sistema-chave de Gestão de Direitos Digitais(DRM).
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("34B13645-A356-475A-8475-48201D3EE361")]
		public interface class ICarenMFMediaKeySession : ICaren
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
			/// (Close) - Fecha a sessão de tecla de mídia e deve ser chamada antes da sessão-chave ser liberada.
			/// </summary>
			CarenResult Fechar();

			/// <summary>
			/// (get_KeySystem) - Obtém o nome do sistema de chave com o nome das teclas de mídia com o que o objeto foi criado.
			/// </summary>
			/// <param name="Param_Out_KeySystem">Retorna uma string com o nome do sistema de chave.</param>
			CarenResult ObterKeySystem([Out] String^% Param_Out_KeySystem);

			/// <summary>
			/// (get_SessionId) - Obtém um id de sessão exclusivo criado para esta sessão.
			/// </summary>
			/// <param name="Param_Out_SessionId">Retorna a chave de comunicação da sessão de mídia.</param>
			CarenResult ObterIdSessao([Out] String^% Param_Out_SessionId);

			/// <summary>
			/// (GetError) - Obtém o estado de erro associado à sessão-chave da mídia.
			/// </summary>
			/// <param name="Param_Out_Code">Retorna o código de erro.</param>
			/// <param name="Param_Out_SystemCode">Retorna informações de erro específicas da plataforma.</param>
			CarenResult ObterErro([Out] UInt16% Param_Out_Code, [Out] UInt32% Param_Out_SystemCode);

			/// <summary>
			/// (Update) - Passa um valor-chave com todos os dados associados exigidos pelo Módulo de Descriptografia de Conteúdo para o sistema de tecla dado.
			/// </summary>
			/// <param name="Param_Key"></param>
			/// <param name="Param_CoutDataKey">A contagem em bytes em Param_Key.</param>
			CarenResult Update(cli::array<Byte>^ Param_Key, UInt32 Param_CoutDataKey);
		};
		
		/// <summary>
		/// (IMFMediaKeys) - Interface responsável por representar uma tecla de mídia usada para descriptografar dados de mídia usando um sistema-chave de 
		/// Gestão de Direitos Digitais (DRM).
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("97D22BD6-3F80-4672-A95C-AF0EB37A63ED")]
		public interface class ICarenMFMediaKeys : ICaren
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
			/// (CreateSession) - Cria um objeto de sessão de chave de mídia usando os dados de inicialização especificados e dados personalizados. .
			/// </summary>
			/// <param name="Param_MimeType">O tipo MIME do recipiente de mídia usado para o conteúdo.</param>
			/// <param name="Param_DadosIniciais">Os dados de inicialização do sistema chave.</param>
			/// <param name="Param_CountDadosInicias">A contagem em bytes em Param_DadosIniciais.</param>
			/// <param name="Param_DadosPersonalizados">Dados personalizados enviados para o sistema-chave.</param>
			/// <param name="Param_CountDadosPersonalizados">A contagem em bytes de Param_DadosPersonalizados.</param>
			/// <param name="Param_Notify">Um ponteiro para a interface de notificação.</param>
			/// <param name="Param_Out_KeySession">Retorna um ponteiro para a interface de sessão-chave da mídia.</param>
			CarenResult CriarSessao(
				String^ Param_MimeType,
				cli::array<Byte>^ Param_DadosIniciais,
				UInt32 Param_CountDadosInicias,
				cli::array<Byte>^ Param_DadosPersonalizados,
				UInt32 Param_CountDadosPersonalizados,
				ICarenMFMediaKeySessionNotify^ Param_Notify,
				[Out] ICarenMFMediaKeySession^% Param_Out_KeySession);

			/// <summary>
			/// (get_KeySystem) - Obtém uma string de teclas do sistema com qual o objeto ICarenMFMediaKeys foi criado.
			/// </summary>
			/// <param name="Param_Out_KeySystem">Retorna o nome da string do sistema de chaves.</param>
			CarenResult ObterKeySystem([Out] String^% Param_Out_KeySystem);

			/// <summary>
			/// (GetSuspendNotify) -  Obtém a interface de notificação de suspensão do Content Decryption Module(CDM).
			/// </summary>
			/// <param name="Param_Out_Notify">Retorna um ponteiro para a interface de notificação de suspensão do Content Decryption Module(CDM).</param>
			CarenResult ObterSuspendNotify([Out] ICarenMFCdmSuspendNotify^% Param_Out_Notify);

			/// <summary>
			/// (Shutdown) - O desligamento deve ser chamado pelo aplicativo antes do lançamento final. A referência do Content Decryption Module(CDM) e quaisquer outros 
			/// recursos são liberados neste momento. No entanto, as sessões relacionadas não são liberadas ou fechadas.
			/// </summary>
			CarenResult Desligar();
		};

		/// <summary>
		/// (IMFMediaEngine) - Interface responsável por habilitarque um aplicativo para reprodução de arquivos de áudio ou vídeo.
		/// Esta interface é estendida com a ICarenMFMediaEngineEx.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("4C05A0DF-FB34-402F-ACE0-9C1DDA5A5459")]
		public interface class ICarenMFMediaEngine : ICaren
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
			/// (CanPlayType) - Pergunta o quão provável é que o Media Engine possa reproduzir um tipo especificado de recurso de mídia.
			/// </summary>
			/// <param name="Param_TipoMime">Uma string que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
			/// <param name="Param_Out_CanPlay">Recebe um valor de enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
			CarenResult VerificarReproduçãoTipo(
				String^ Param_TipoMime,
				[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_CanPlay);

			/// <summary>
			/// (GetAutoPlay) - Pergunta se o Media Engine inicia automaticamente a reprodução.
			/// </summary>
			/// <param name="Param_Out_AutoPlay">Recebe um valor booleano que indica se a reprodução é iniciada automaticamente.</param>
			CarenResult ObterAutoPlay([Out] Boolean% Param_Out_AutoPlay);

			/// <summary>
			/// (GetBuffered) - Consulta a quantidade de dados de recursos que o mecanismo de mídia buffer.
			/// </summary>
			/// <param name="Param_Out_Buffered">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
			CarenResult ObterBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered);

			/// <summary>
			/// (GetCurrentSource) - Obtém a URL do recurso de mídia atual ou uma sequência vazia se nenhum recurso de mídia estiver presente.
			/// </summary>
			/// <param name="Param_Out_Url">Recebe uma String que contém a URL do recurso de mídia atual. Se não houver recurso de mídia, Param_Out_Url recebe uma String vazia.</param>
			CarenResult ObterFonteAtual([Out] String^% Param_Out_Url);

			/// <summary>
			/// (GetCurrentTime) - Obtém a posição de reprodução atual.
			/// </summary>
			/// <param name="Param_Out_PosicaoAtual">Obtém o valor da posição atual da reprodução.</param>
			CarenResult ObterPosicaoAtual([Out] double% Param_Out_PosicaoAtual);

			/// <summary>
			/// (GetDefaultPlaybackRate) - Obtém a taxa de reprodução padrão.
			/// </summary>
			/// <param name="Param_Out_DefaultRate">Obtém o valor que indica a taxa de reprodução padrão.</param>
			CarenResult ObterDefaultPlaybackRate([Out] double% Param_Out_DefaultRate);

			/// <summary>
			/// (GetDuration) - Obtém a duração do recurso de mídia.
			/// </summary>
			/// <param name="Param_Out_Duracao">Recupera o valor da duração do recurso de mídia.</param>
			CarenResult ObterDuracao([Out] double% Param_Out_Duracao);

			/// <summary>
			/// (GetError) - Obtém o status de erro mais recente.
			/// </summary>
			/// <param name="Param_Out_Error">Recebe um ponteiro para a interface ICarenMFMediaError ou para o valor NULO. Se o valor não for NULO, o chamador deve liberar a interface.</param>
			CarenResult ObterError([Out] ICarenMFMediaError^% Param_Out_Error);

			/// <summary>
			/// (GetLoop) - Pergunta se o Media Engine fará a reprodução em loop.
			/// </summary>
			/// <param name="Param_Out_Loop">Obtém o valor booleano que indica o status da reprodução em loop.</param>
			CarenResult ObterLoop([Out] Boolean% Param_Out_Loop);

			/// <summary>
			/// (GetMuted) - Pergunta se o áudio está silenciado.
			/// </summary>
			/// <param name="Param_Out_Muted">Obtém um valor booleano que indica se o áudio está silenciado.</param>
			CarenResult ObterMuted([Out] Boolean% Param_Out_Muted);

			/// <summary>
			/// (GetNativeVideoSize) - Obtém o tamanho do quadro de vídeo, ajustado para proporção.
			/// </summary>
			/// <param name="Param_Out_X">Retorna a Largura(X) do vídeo.</param>
			/// <param name="Param_Out_Y">Retorna a Altura(Y) do vídeo.</param>
			CarenResult ObterSizeNativoVideo(
				[Out] UInt32% Param_Out_X, 
				[Out] UInt32% Param_Out_Y);

			/// <summary>
			/// (GetNetworkState) - Obtém o estado atual da rede do mecanismo de mídia.
			/// </summary>
			/// <param name="Param_Out_StateNetwork">Retornar um valor da enumeração CA_MF_MEDIA_ENGINE_NETWORK que indica o status da rede.</param>
			CarenResult ObterStatusRede([Out] CA_MF_MEDIA_ENGINE_NETWORK% Param_Out_StateNetwork);

			/// <summary>
			/// (GetPlaybackRate) - Obtém a taxa de reprodução atual.
			/// </summary>
			/// <param name="Param_Out_PlaybackRate">Obtém um valor que indica a taxa de reprodução atual.</param>
			CarenResult ObterPlaybackRate([Out] double% Param_Out_PlaybackRate);

			/// <summary>
			/// (GetPlayed) - Obtém os intervalos de tempo que foram prestados.
			/// </summary>
			/// <param name="Param_Out_Played">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
			CarenResult ObterPlayed([Out] ICarenMFMediaTimeRange^% Param_Out_Played);

			/// <summary>
			/// (GetPreload) - Recebe a bandeira de pré-carga.
			/// </summary>
			/// <param name="Param_Out_Preload">Recebe um valor da enumeração CA_MF_MEDIA_ENGINE_PRELOAD.</param>
			CarenResult ObterPreCarga([Out] CA_MF_MEDIA_ENGINE_PRELOAD% Param_Out_Preload);

			/// <summary>
			/// (GetReadyState) - Obtém o estado pronto, o que indica se o recurso de mídia atual pode ser renderizado.
			/// </summary>
			/// <param name="Param_Out_RadyState">Obtém uma ou mais bandeiras da enumeração CA_MF_MEDIA_ENGINE_READY que indica se o recurso pode ser renderizado.</param>
			CarenResult ObterReadyState([Out] CA_MF_MEDIA_ENGINE_READY% Param_Out_RadyState);

			/// <summary>
			/// (GetSeekable) - Obtém os intervalos de tempo aos quais o Media Engine pode procurar atualmente.
			/// </summary>
			/// <param name="Param_Out_Seekable">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
			CarenResult ObterSeekable([Out] ICarenMFMediaTimeRange^% Param_Out_Seekable);

			/// <summary>
			/// (GetStartTime) - Obtém a posição inicial de reprodução.
			/// </summary>
			/// <param name="Param_Out_PosicaoInicial">Obtém um valor que indica a posição inicial de reprodução.</param>
			CarenResult ObterPosicaoInicio([Out] double% Param_Out_PosicaoInicial);

			/// <summary>
			/// (GetVideoAspectRatio) - Obtém a proporção de imagem do fluxo de vídeo.
			/// </summary>
			/// <param name="Param_Out_X">Retonar o valor da Largura(X) do fluxo de vídeo.</param>
			/// <param name="Param_Out_Y">Retonar o valor da Altura(Y) do fluxo de vídeo.</param>
			CarenResult ObterAspectRatioVideo(
				[Out] UInt32% Param_Out_X,
				[Out] UInt32% Param_Out_Y);

			/// <summary>
			/// (GetVolume) - Obtém o nível de volume de áudio.
			/// </summary>
			/// <param name="Param_Out_Volume">Obtém um valor que indica o nível de volume do áudio.</param>
			CarenResult ObterVolume([Out] double% Param_Out_Volume);

			/// <summary>
			/// (HasAudio) - Pergunta se o recurso de mídia atual contém um fluxo de áudio.
			/// </summary>
			/// <param name="Param_Out_AudioPresente">Retornar um booleano TRUE se um fluxo de áudio estiver disponível na mídia. Caso contrario, FALSE.</param>
			CarenResult AudioPresente([Out] Boolean% Param_Out_AudioPresente);

			/// <summary>
			/// (HasVideo) - Pergunta se o recurso de mídia atual contém um fluxo de vídeo.
			/// </summary>
			/// <param name="Param_Out_VideoPresente">Retornar um booleano TRUE se um fluxo de vídeo estiver disponível na mídia. Caso contrario, FALSE.</param>
			CarenResult VideoPresente([Out] Boolean% Param_Out_VideoPresente);

			/// <summary>
			/// (IsEnded) - Verifica se a reprodução terminou.
			/// </summary>
			/// <param name="Param_Out_ReproducaoTerminada">Retornar um booleano TRUE se a reprodução tiver terminado. Caso contrario, FALSE.</param>
			CarenResult IsEnded([Out] Boolean% Param_Out_ReproducaoTerminada);

			/// <summary>
			/// (IsPaused) - Verifica se a reprodução está pausada no momento.
			/// </summary>
			/// <param name="Param_Out_PauseStatus">Retorna um valor booleano indicando se a reprodução está pausada.</param>
			CarenResult IsPaused([Out] Boolean% Param_Out_PauseStatus);

			/// <summary>
			/// (IsSeeking) - Verifica se o Media Engine está atualmente buscando uma nova posição de reprodução.
			/// </summary>
			/// <param name="Param_Out_BuscandoPosicao">Retornar um valor booleano que indica se a Media Engine está buscando uma nova posição.</param>
			CarenResult IsSeeking([Out] Boolean% Param_Out_BuscandoPosicao);

			/// <summary>
			/// (Load) - Carrega a fonte de mídia atual.
			/// </summary>
			CarenResult Carregar();

			/// <summary>
			/// (OnVideoStreamTick) - Consulta o Media Engine para saber se um novo quadro de vídeo está pronto.
			/// </summary>
			/// <param name="Param_Out_TempoApresentacaoFrame">Retornar um valor valido e maior que 0 para o tempo de apresentação do frame se ele estiver pronto para renderização.</param>
			CarenResult OnVideoStreamTick([Out] Int64% Param_Out_TempoApresentacaoFrame);

			/// <summary>
			/// Pausa a reprodução.
			/// </summary>
			CarenResult Pause();

			/// <summary>
			/// Começa a reprodução.
			/// </summary>
			CarenResult Play();

			/// <summary>
			/// (SetAutoPlay) - Especifica se o Media Engine inicia automaticamente a reprodução.
			/// </summary>
			/// <param name="Param_AutoPlay">Um valor booleano que indica se vai reproduzir automaticamente.</param>
			CarenResult DefinirAutoPlay(Boolean Param_AutoPlay);

			/// <summary>
			/// (SetCurrentTime) - Busca uma nova posição de reprodução.
			/// </summary>
			/// <param name="Param_NovaPosicao">A novao posição a ser buscada.</param>
			CarenResult DefinirPosicaoAtual(double Param_NovaPosicao);

			/// <summary>
			/// (SetDefaultPlaybackRate) - Define a taxa de reprodução padrão.
			/// </summary>
			/// <param name="Param_TaxaReproducaoDefault">O novo valor para taxa de reprodução padrão.</param>
			CarenResult DefinirDefaultPlaybackRate(double Param_TaxaReproducaoDefault);

			/// <summary>
			/// (SetErrorCode) - Define o código de erro atual.
			/// </summary>
			/// <param name="Param_Error">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_ERR.</param>
			CarenResult DefinirCodeErro(CA_MF_MEDIA_ENGINE_ERR Param_Error);

			/// <summary>
			/// (SetLoop) - Especifica se o Media Engine faz loop de reprodução.
			/// </summary>
			/// <param name="Param_Loop">Um valor booleano que vai indicar o loop de reprodução.</param>
			CarenResult DefinirLoop(Boolean Param_Loop);

			/// <summary>
			/// (SetMuted) - Silencia ou ativar o áudio.
			/// </summary>
			/// <param name="Param_Mudo">Um valor booleano que vai definir se vai ou não silenciar o áudio.</param>
			CarenResult DefinirMudo(Boolean Param_Mudo);

			/// <summary>
			/// (SetPlaybackRate) - Define a taxa de reprodução atual.
			/// </summary>
			/// <param name="Param_TaxaReproducaoAtual">Um valor para a nova taxa de reprodução atual.</param>
			CarenResult DefinirPlaybackRate(double Param_TaxaReproducaoAtual);

			/// <summary>
			/// (SetPreload) - Defina o sinalizador de pré-carga.
			/// </summary>
			/// <param name="Param_Preload">Uma bandeira da enumeração CA_MF_MEDIA_ENGINE_PRELOAD que define o Preload da midia.</param>
			CarenResult DefinirPreCarga(CA_MF_MEDIA_ENGINE_PRELOAD Param_Preload);

			/// <summary>
			/// (SetSource) - Define a URL de um recurso de mídia.
			/// </summary>
			/// <param name="Param_Url">Uma string conténdo a URL para o recurso de mídia.</param>
			CarenResult DefinirFonte(String^ Param_Url);

			/// <summary>
			/// (SetSourceElements) - Define uma lista de fontes de mídia.
			/// </summary>
			/// <param name="Param_ElementosMidia">Um ponteiro para a interface ICarenMFMediaEngineSrcElements. O chamador deve implementar esta interface.</param>
			CarenResult DefinirListaFontesMidia(ICarenMFMediaEngineSrcElements^ Param_ElementosMidia);

			/// <summary>
			/// (SetVolume) - Define o nível de volume de áudio.
			/// </summary>
			/// <param name="Param_Volume">O novo valor para o nível de volume de áudio da mídia.</param>
			CarenResult DefinirVolume(double Param_Volume);

			/// <summary>
			/// (Shutdown) - Desliga o Media Engine e libera os recursos que está usando.
			/// </summary>
			CarenResult Desligar();

			/// <summary>
			/// (TransferVideoFrame) - Copia o quadro de vídeo atual para um DXGI ou WIC bitmap.
			/// No modo frame-server, chame este método para colocar o quadro de vídeo em uma superfície DXGI ou WIC. O aplicativo pode chamar esse método a qualquer momento após o 
			/// Media Engine carregar um recurso de vídeo. Normalmente, no entanto, o aplicativo chama O ICarenMFMediaEngine::OnVideoStreamTick primeiro, para determinar se um novo quadro 
			/// está disponível. Se o OnVideoStreamTick retornar SS_OK, o aplicativo então chamará TransferirFrameVideo.
			/// Para conteúdo protegido, ligue para o método ICarenMFMediaEngineProtectedContent::TransferirFrameVideo em vez deste método.
			/// </summary>
			/// <param name="Param_SuperficeDestino">Um ponteiro para a interface da superfície de destino.</param>
			/// <param name="Param_RetanguloOrigem">Uma estrutura MFVideoNormalizedRect(CA_RECT) que especifica o retângulo de origem</param>
			/// <param name="Param_RetanguloDestino">Uma estrutura CA_RECT que especifica o retângulo de destino.</param>
			/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
			CarenResult TransferirFrameVideo(
				ICaren^ Param_SuperficeDestino, 
				CA_RECT^ Param_RetanguloOrigem,
				CA_RECT^ Param_RetanguloDestino,
				CA_MFARGB^ Param_CorBorda);
			
		};

		/// <summary>
		/// (IMFMediaEngineEx) - Interface responsável por estender a interface ICarenMFMediaEngine.
		/// A interface ICarenMFMediaEngine contém métodos que mapeiam os elementos de mídia HTML5. A ICarenMFMediaEngineEx fornece funcionalidades adicionais que não correspondem
		/// diretamente ao HTML5.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("993C52B5-8A18-46BF-8D52-04599D869D0F")]
		public interface class ICarenMFMediaEngineEx : ICarenMFMediaEngine
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
			/// (ApplyStreamSelections) - Aplica as seleções de fluxo de chamadas anteriores para SetStreamSelection.
			/// </summary>
			CarenResult AplicarSelecaoFluxos();

			/// <summary>
			/// (CancelTimelineMarkerTimer) - Cancela o próximo marcador de linha do tempo pendente.
			/// </summary>
			CarenResult CancelarTimelineMarkerTimer();

			/// <summary>
			/// (EnableHorizontalMirrorMode) - Ativa ou desativa o espelhamento do vídeo.
			/// </summary>
			/// <param name="Param_Ativar">Se TRUE,o vídeo é espelhado horizontalmente. Caso contrário, o vídeo é exibido normalmente.</param>
			CarenResult HabilitarNodoHorizontalMirror(Boolean Param_Ativar);

			/// <summary>
			/// (EnableTimeUpdateTimer) - Ativa ou desativa o temporizador de atualização de tempo.
			/// </summary>
			/// <param name="Param_AtivarTime">Se TRUE, o temporizador de atualização estar ativado. Caso contrário, o temporizador está desativado.</param>
			CarenResult AtivarTimeAtualizacaoTempo(Boolean Param_AtivarTime);

			/// <summary>
			/// (EnableWindowlessSwapchainMode) - Ativa ou desativa o modo de cadeia de swap sem janelas.
			/// </summary>
			/// <param name="Param_Ativar">Se TRUE, o modo Windowless Swap-chain está ativado.</param>
			CarenResult HabilitarWindowlessSwapchainMode(Boolean Param_Ativar);

			/// <summary>
			/// (FrameStep) - Dá um passo para frente ou para trás.
			/// </summary>
			/// <param name="Param_Avancar">Especifique TRUE para dar um passo em FRENTE ou FALSE para dar um passo para TRÀS.</param>
			CarenResult FrameStep(Boolean Param_Avancar);

			/// <summary>
			/// (GetAudioEndpointRole) - Obtém a função de ponto final do dispositivo de áudio usada para a próxima chamada para SetSource ou Load.
			/// </summary>
			/// <param name="Param_Out_Role">Recebe a função de ponto final de áudio.</param>
			CarenResult ObterFuncaoPontoFinalAudio([Out] UInt32% Param_Out_Role);

			/// <summary>
			/// (GetAudioStreamCategory) - Obtém a categoria de fluxo de áudio usada para a próxima chamada para SetSource ou Load.
			/// </summary>
			/// <param name="Param_Out_Categoria">Recebe a categoria de fluxo de áudio.</param>
			CarenResult ObterCategoriaFluxoAudio([Out] UInt32% Param_Out_Categoria);

			/// <summary>
			/// (GetBalance) - Obtém o equilíbrio de áudio.
			/// </summary>
			/// <param name="Param_Out_Balance">Devolve o equilíbrio de áudio. O valor pode ser qualquer número na faixa seguinte faixa(-1 a 1). Se o valor for zero, 
			/// os canais esquerdo e direito estão em volumes iguais. O valor padrão é zero.</param>
			CarenResult ObterEquilibrioAudio([Out] double% Param_Out_Balance);

			/// <summary>
			/// (GetNumberOfStreams) - Obtém o número de fluxos no recurso de mídia.
			/// </summary>
			/// <param name="Param_Out_NumFluxos">Retorna o número de fluxos no recurso de mídia.</param>
			CarenResult ObterNumeroFluxos([Out] UInt32% Param_Out_NumFluxos);

			/// <summary>
			/// (GetPresentationAttribute) - Obtém um atributo de apresentação do recurso de mídia.
			/// </summary>
			/// <param name="Param_GuidMFAtributos">O atributo a ser consultado. Para obter uma lista de atributos de apresentação, consulte a estrutura: 
			/// GUIDs_MFAtributos_DescritorApresentacao</param>
			/// <param name="Param_Out_ValorAtributo">Retrona uma CA_PropVariant com os dados do atributo.</param>
			CarenResult ObterAtributosApresentacao(
				String^ Param_GuidMFAtributos, 
				[Out] CA_PropVariant^% Param_Out_ValorAtributo);

			/// <summary>
			/// (GetRealTimeMode) - Obtém o modo em tempo real usado para a próxima chamada para DefinirFonte ou Carregar.
			/// </summary>
			/// <param name="Param_Out_Habilitado">Recebe o modo em tempo real.</param>
			CarenResult ObterModoTempoReal([Out] Boolean% Param_Out_Habilitado);

			/// <summary>
			/// (GetResourceCharacteristics) - Recebe várias bandeiras que descrevem o recurso de mídia.
			/// </summary>
			/// <param name="Param_Out_Caracteristcas">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_CARACTERISTICAS_FONTE_MIDIA.</param>
			CarenResult ObterCaracteristicasRecurso([Out] CA_CARACTERISTICAS_FONTE_MIDIA% Param_Out_Caracteristcas);

			/// <summary>
			/// (GetStatistics) - Obtém uma estatística de reprodução do Media Engine.
			/// </summary>
			/// <param name="Param_TipoEstatistica">Um membro da enumeração CA_MF_MEDIA_ENGINE_STATISTIC que identifica a estatística a obter.</param>
			/// <param name="Param_Out_ValorEstatistica">Retrona uma CA_PropVariant com os dados da estatitisca requisitada.</param>
			CarenResult ObterEstatisticas(
				CA_MF_MEDIA_ENGINE_STATISTIC Param_TipoEstatistica, 
				[Out] CA_PropVariant^% Param_Out_ValorEstatistica);

			/// <summary>
			/// (GetStereo3DFramePackingMode) - Para vídeo 3D estereoscópico, obtém o layout das duas visualizações dentro de um quadro de vídeo.
			/// </summary>
			/// <param name="Param_Out_ModoLayout">Recebe um membro da enumeração CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE com o modo de layout.</param>
			CarenResult ObterStereo3DFramePackingMode([Out] CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE% Param_Out_ModoLayout);

			/// <summary>
			/// (GetStereo3DRenderMode) - Para vídeo 3D estereoscópico, consulta como o Media Engine renderiza o conteúdo de vídeo 3D.
			/// </summary>
			/// <param name="Param_Out_TipoSaida">Recebe um membro da enumeração CA_MF3DVideoOutputType com o tipo de saida.</param>
			CarenResult ObterStereo3DRenderMode([Out] CA_MF3DVideoOutputType% Param_Out_TipoSaida);

			/// <summary>
			/// (GetStreamAttribute) - Obtém um atributo de nível de fluxo do recurso de mídia.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
			/// <param name="Param_GuidMfAtributo">O atributo a ser consultado. Os valores possíveis estão presentes nas estruturas: GUIDs_MFAtributos_DescritorFluxo e GUIDs_MFAtributos_MediaType</param>
			/// <param name="Param_Out_ValorAtributo">>Retrona uma CA_PropVariant com os dados do atributo.</param>
			CarenResult ObterAtributosFluxo(
				UInt32 Param_IdFluxo, 
				String^ Param_GuidMfAtributo, 
				[Out] CA_PropVariant^% Param_Out_ValorAtributo);

			/// <summary>
			/// (GetStreamSelection) - Verifica se um fluxo está selecionado para reprodução.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
			/// <param name="Param_Out_Selecionado">Retorna um valor booleano que indica o status da seleção de um fluxo para reprodução.</param>
			CarenResult ObterSelecaoFluxo(
				UInt32 Param_IdFluxo, 
				[Out] Boolean% Param_Out_Selecionado);

			/// <summary>
			/// (GetTimelineMarkerTimer) - Obtém o tempo do próximo marcador de linha do tempo, se houver.
			/// </summary>
			/// <param name="Param_Out_TimeToFire">Retorna um valor com o tempo(em segundos) para o proximo marcador de linha do tempo. Se não houver, o retorno é NaN.</param>
			CarenResult ObterTimelineMarkerTimer([Out] double% Param_Out_TimeToFire);

			/// <summary>
			/// (GetVideoSwapchainHandle) - Obtém a Handle de windowless Swap chain.
			/// </summary>
			/// <param name="Param_Out_Handle">Receber a handle para o swap chain.</param>
			CarenResult ObterHandleVideoSwapChain([Out] IntPtr% Param_Out_Handle);

			/// <summary>
			/// (InsertAudioEffect) - Insere um efeito de áudio.
			/// </summary>
			/// <param name="Param_Efeito">Um ponteiro para uma interface que contém o efeito de Áudio. Essa interface pode ser uma: ICarenMFTransform ou ICarenMFActivate.</param>
			/// <param name="Param_Opcional">Um valor Booleano para se o efeito a ser inserido é opcional ou não.</param>
			CarenResult InserirEfeitoAudio(
				ICaren^ Param_Efeito, 
				Boolean Param_Opcional);

			/// <summary>
			/// (InsertVideoEffect) - Insere um efeito de vídeo.
			/// </summary>
			/// <param name="Param_Efeito">Um ponteiro para uma interface que contém o efeito de Vídeo. Essa interface pode ser uma: ICarenMFTransform ou ICarenMFActivate.</param>
			/// <param name="Param_Opcional">Um valor Booleano para se o efeito a ser inserido é opcional ou não.</param>
			CarenResult InserirEfeitoVideo(
				ICaren^ Param_Efeito, 
				Boolean Param_Opcional);

			/// <summary>
			/// (IsPlaybackRateSupported) - Verifica se o Media Engine pode reproduzir a uma taxa de reprodução especificada.
			/// </summary>
			/// <param name="Param_Taxa">A taxa a ser verificado o suporte.</param>
			/// <param name="Param_Out_Suporte">Retorna um valor Booleano para se a taxa é suportada pela Media Engine.</param>
			CarenResult VerificarSuporteTaxaPlayback(
				double Param_Taxa, 
				[Out] Boolean% Param_Out_Suporte);

			/// <summary>
			/// (IsProtected) - Verifica se o recurso de mídia contém conteúdo protegido.
			/// </summary>
			/// <param name="Param_Out_Protegido">Retorna um valor Booleano para se o recurso de mídia contém conteúdo protegido.</param>
			CarenResult VerificarConteudoProtegido([Out] Boolean% Param_Out_Protegido);

			/// <summary>
			/// (IsStereo3D) - Verifica se o recurso de mídia contém vídeo 3D estereoscópico.
			/// </summary>
			/// <param name="Param_Out_Resultado">Retorna um valor Booleano para se a mídia contém video 3D estereoscópico.</param>
			CarenResult VerificarStereo3D([Out] Boolean% Param_Out_Resultado);

			/// <summary>
			/// (RemoveAllEffects) - Remove todos os efeitos de áudio e vídeo.
			/// </summary>
			CarenResult RemoverTodosEfeitos();

			/// <summary>
			/// (SetAudioEndpointRole) - Define o ponto final do dispositivo de áudio usado para a próxima chamada para DefinirFonte ou Carregar.
			/// </summary>
			/// <param name="Param_Role">Especifica a função de ponto final de áudio.</param>
			CarenResult DefinirFuncaoPontoFinalAudio(UInt32 Param_Role);

			/// <summary>
			/// (SetAudioStreamCategory) - Define a categoria fluxo de áudio para a próxima chamada para DefinirFonte ou Carregar.
			/// </summary>
			/// <param name="Param_Categoria">>Especifica a categoria do fluxo de áudio.</param>
			CarenResult DefinirCategoriaFluxoAudio(UInt32 Param_Categoria);

			/// <summary>
			/// (SetBalance) - Define o equilíbrio de áudio.
			/// </summary>
			/// <param name="Param_Balance">O valor do equilíbrio do áudio a ser definido. Os valores vaõ de -1 a 1, ZERO é o padrão.</param>
			CarenResult DefinirEquilibrioAudio(double Param_Balance);

			/// <summary>
			/// (SetCurrentTimeEx) - Busca uma nova posição de reprodução usando o MF_MEDIA_ENGINE_SEEK_MODE especificado.
			/// </summary>
			/// <param name="Param_Posicao">A nova posição de reprodução, em segundos.</param>
			/// <param name="Param_Modo">Especifica se a busca é uma busca normal ou uma busca aproximada.</param>
			CarenResult DefinirPosicaoAtualEx(
				double Param_Posicao, 
				CA_MF_MEDIA_ENGINE_SEEK_MODE Param_Modo);

			/// <summary>
			/// (SetRealTimeMode) - Define o modo em tempo real usado para a próxima chamada para DefinirFonte ou Carregar.
			/// </summary>
			/// <param name="Param_Habilitar">Especifica o modo em tempo real.</param>
			CarenResult DefinirModoTempoReal(Boolean Param_Habilitar);

			/// <summary>
			/// (SetSourceFromByteStream) - Abre um recurso de mídia a partir de um fluxo de bytes.
			/// </summary>
			/// <param name="Param_FluxoBytes">Um ponteiro para a interface ICarenMFByteStream do fluxo de bytes.</param>
			/// <param name="Param_Url">A URL do fluxo de bytes.</param>
			CarenResult DefinirFonteFromByteStream(
				ICarenMFByteStream^ Param_FluxoBytes, 
				String^ Param_Url);

			/// <summary>
			/// (SetStereo3DFramePackingMode) - Para vídeo 3D estereoscópico, define o layout das duas visualizações dentro de um quadro de vídeo.
			/// </summary>
			/// <param name="Param_ModoLayout">Um membro da enumeração CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE que especifica o layout. As duas vistas podem ser organizadas lado 
			/// a lado, ou de cima para baixo.</param>
			CarenResult DefinirStereo3DFramePackingMode(CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE Param_ModoLayout);

			/// <summary>
			/// (SetStereo3DRenderMode) - Para vídeo 3D estereoscópico, especifica como o Media Engine renderiza o conteúdo de vídeo 3D.
			/// </summary>
			/// <param name="Param_TipoSaida">Um membro da enumeração MF3DVideoOutputType que especifica o modo de renderização de vídeo 3D.</param>
			CarenResult DefinirStereo3DRenderMode(CA_MF3DVideoOutputType Param_TipoSaida);

			/// <summary>
			/// (SetStreamSelection) - Seleciona ou desmarca um fluxo para reprodução.
			/// </summary>
			/// <param name="Param_IdFluxo">O índice baseado em zero do fluxo. Para obter o número de fluxos, ligue para ICarenMFMediaEngineEx::ObterNumeroFluxos.</param>
			/// <param name="Param_Habilitar">Especifica se deve selecionar ou desmarcar o fluxo.</param>
			CarenResult DefinirSelecaoFluxo(
				UInt32 Param_IdFluxo, 
				Boolean Param_Habilitar);

			/// <summary>
			/// (SetTimelineMarkerTimer) - Especifica um tempo de apresentação quando o Media Engine enviará um evento marcador.
			/// </summary>
			/// <param name="Param_TimeToFire">O tempo de apresentação para o evento marcador, em segundos.</param>
			CarenResult DefinirTimelineMarkerTimer(double Param_TimeToFire);

			/// <summary>
			/// (UpdateVideoStream) - Atualiza o retângulo de origem, o retângulo de destino e a cor da borda do vídeo.
			/// </summary>
			/// <param name="Param_Origem">Uma estrutura CA_RECT que especifica o retângulo de origem. O retângulo de origem define a área do quadro de vídeo exibido. 
			/// Se este parâmetro for NULO,todo o quadro de vídeo será exibido.</param>
			/// <param name="Param_Destino">Uma estrutura CA_RECT que especifica o retângulo de destino. O retângulo de destino define a área da janela ou o visual 
			/// DirectComposition onde o vídeo é desenhado.</param>
			/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
			CarenResult AtualizarFluxoVideo(
				CA_RECT^ Param_Origem, 
				CA_RECT^ Param_Destino, 
				CA_MFARGB^ Param_CorBorda);
		};
		
		/// <summary>
		/// (IMFSourceBuffer) - Interface responsável por representar um buffer que contém dados de mídia para um ICarenMFMediaSourceExtension.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("E328CE45-96E2-4DB0-866E-80EDC4F99BDD")]
		public interface class ICarenMFSourceBuffer : ICaren
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
			/// Aborta o processamento do segmento de mídia atual.
			/// </summary>
			CarenResult Abort();

			/// <summary>
			/// Anexa o segmento de mídia especificado ao ICarenMFSourceBuffer.
			/// </summary>
			/// <param name="Param_Buffer">Os dados da mídia para anexar.</param>
			/// <param name="Param_LarguraBuffer">O comprimento dos dados de mídia armazenados em Param_Buffer.</param>
			CarenResult Append(
				ICarenBuffer^ Param_Buffer, 
				UInt32 Param_LarguraBuffer);

			/// <summary>
			/// Anexa o segmento de mídia do fluxo de byte especificado para o ICarenMFSourceBuffer.
			/// </summary>
			/// <param name="Param_Fluxo">Os dados do fluxo de mídia.</param>
			/// <param name="Param_Ref_LarguraMaxima">A duração máxima dos dados do segmento de mídia.</param>
			CarenResult AppendByteStream(
				ICarenMFByteStream^ Param_Fluxo, 
				UInt64% Param_Ref_LarguraMaxima);

			/// <summary>
			/// Obtém o carimbo de tempo para o fim da janela de acrescimo.
			/// </summary>
			/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o fim.</param>
			CarenResult GetAppendWindowEnd([Out] double% Param_Out_Timestamp);

			/// <summary>
			/// Obtém o carimbo de tempo para o início da janela de acrescimo.
			/// </summary>
			/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o inicio.</param>
			CarenResult GetAppendWindowStart([Out] double% Param_Out_Timestamp);

			/// <summary>
			/// Obtém o intervalo de tempo em Buffer.
			/// </summary>
			/// <param name="Param_Out_Buffered">Retorna uma interface com o intervalo de tempo Buffered.</param>
			CarenResult GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered);

			/// <summary>
			/// Obtém a compensação de carimbo de tempo para fluxos de mídia anexados ao ICarenMFSourceBuffer.
			/// </summary>
			/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo compesado para fluxos anexados.</param>
			CarenResult GetTimeStampOffset([Out] double% Param_Out_Timestamp);

			/// <summary>
			/// Obtém um valor que indica se Append, AppendByteStream ou Remove está em processo.
			/// </summary>
			/// <param name="Param_Out_Valor">Retorna um valor booleano indicando se alguns dos métodos está em processo atualmente.</param>
			CarenResult GetUpdating([Out] Boolean% Param_Out_Valor);

			/// <summary>
			/// Remove os segmentos de mídia definidos pelo intervalo de tempo especificado do ICarenMFSourceBuffer.
			/// </summary>
			/// <param name="Param_Inicio">O início do intervalo de tempo.</param>
			/// <param name="Param_Fim">O fim do intervalo de tempo.</param>
			CarenResult Remove(double Param_Inicio, double Param_Fim);

			/// <summary>
			/// Define o carimbo de tempo para o fim da janela de acrescimo.
			/// </summary>
			/// <param name="Param_Time">O carimbo de data e hora para o fim da janela de acrescimo.</param>
			CarenResult SetAppendWindowEnd(double Param_Time);

			/// <summary>
			/// Define o carimbo de tempo para o início da janela de acrescimo.
			/// </summary>
			/// <param name="Param_Time">O carimbo de data e hora para o início da janela de acrescimo.</param>
			CarenResult SetAppendWindowStart(double Param_Time);

			/// <summary>
			/// Define a compensação de carimbo de tempo para segmentos de mídia anexados ao ICarenMFSourceBuffer.
			/// </summary>
			/// <param name="Param_Offset">O valor offset para o timestamp dos fluxos de mídia anexados.</param>
			CarenResult SetTimeStampOffset(double Param_Offset);
		};

		/// <summary>
		/// (IMFSourceBufferNotify) - Interface responsável por fornecer funcionalidades para chamar eventos associados ao ICarenMFSourceBuffer.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("04DC4EFB-60D2-4ACE-8A27-6396DDB18F14")]
		public interface class ICarenMFSourceBufferNotify : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}




			//Delegates

			/// <summary>
			/// Delegate do evento OnAbort.
			/// </summary>
			delegate void Delegate_OnAbort();

			/// <summary>
			/// Delegate do evento OnError.
			/// </summary>
			delegate void Delegate_OnError();

			/// <summary>
			/// Delegate do evento OnUpdate.
			/// </summary>
			delegate void Delegate_OnUpdate();

			/// <summary>
			/// Delegate do evento OnUpdateEnd.
			/// </summary>
			delegate void Delegate_OnUpdateEnd();

			/// <summary>
			/// Delegate do evento OnUpdateStart.
			/// </summary>
			delegate void Delegate_OnUpdateStart();



			//Eventos

			/// <summary>
			/// Evento chamado para indicar que o buffer de origem foi abortado.
			/// </summary>
			event Delegate_OnAbort^ OnAbort;

			/// <summary>
			/// Evento chamado para indicar que ocorreu um erro com o buffer de origem.
			/// </summary>
			event Delegate_OnError^ OnError;

			/// <summary>
			/// Evento chamado para indicar que o buffer de origem está sendo atualizado.
			/// </summary>
			event Delegate_OnUpdate^ OnUpdate;

			/// <summary>
			/// Evento chamado para indicar que o buffer de origem terminou de atualizar.
			/// </summary>
			event Delegate_OnUpdateEnd^ OnUpdateEnd;

			/// <summary>
			/// Evento chamado para indicar que o buffer de origem começou a ser atualizado.
			/// </summary>
			event Delegate_OnUpdateStart^ OnUpdateStart;


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
		/// (IMFSourceBufferList) - Interface responsável por representar uma coleção de objetos ICarenMFSourceBuffer.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("1D5058C9-2B97-4C08-987C-D27200BE5A21")]
		public interface class ICarenMFSourceBufferList : ICaren
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
			/// (GetLength) - Obtém o número de objetos ICarenMFSourceBuffer na lista.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de objetos presentes na lista.</param>
			CarenResult ObterQuantidade([Out] UInt32% Param_Out_Quantidade);


			/// <summary>
			/// (GetSourceBuffer) - Obtém o ICarenMFSourceBuffer no índice especificado na lista.
			/// </summary>
			/// <param name="Param_Index">O Iidex do buffer fonte a ser obtido da lista.</param>
			/// <param name="Param_Out_BufferFonte">Retorna um ponteiro para a interface(ICarenMFSourceBuffer) do index informado.</param>
			CarenResult ObterBufferFonte(UInt32 Param_Index, [Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte);
		};
		
		/// <summary>
		/// (IMFMediaSourceExtension) - Interface responsável por fornecer funcionalidade para o Media Source Extension (MSE).
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("2201752E-460F-47FC-9E90-D88DA9CFBD73")]
		public interface class ICarenMFMediaSourceExtension : ICaren
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
			/// (AddSourceBuffer) - Adiciona um ICarenMFSourceBuffer à coleção de buffers associados ao ICarenMFMediaSourceExtension.
			/// </summary>
			/// <param name="Param_Type">(NOT PRESENT DOCUMENTATION)</param>
			/// <param name="Param_Notify">(NOT PRESENT DOCUMENTATION)</param>
			/// <param name="Param_Out_BufferFonte">(NOT PRESENT DOCUMENTATION)</param>
			CarenResult AdicionarBufferFonte(
				String^ Param_Type, 
				ICarenMFSourceBufferNotify^ Param_Notify, 
				[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte);

			/// <summary>
			/// (GetActiveSourceBuffers) - Obtém os buffers de origem que estão fornecendo ativamente dados de mídia para a fonte de mídia.
			/// </summary>
			/// <param name="Param_Out_ListBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) que contém uma lista dos buffers ativos.</param>
			CarenResult ObterBuffersOrigemAtivos([Out] ICarenMFSourceBufferList^% Param_Out_ListBuffers);

			/// <summary>
			/// (GetDuration) - Obtém a duração da fonte de mídia em unidades de 100 nanossegundos.
			/// </summary>
			/// <param name="Param_Out_Duracao">Retorna a duração da midia em unidades de 100 nanossegundos.</param>
			CarenResult ObterDuracao([Out] double% Param_Out_Duracao);

			/// <summary>
			/// (GetReadyState) - Obtém o estado pronto da fonte da mídia.
			/// </summary>
			/// <param name="Param_Out_ReadyState">Retorna uma bandeira da enumeração(CA_MF_MSE_READY) que indica o estado pronto da fonte de mídia.</param>
			CarenResult ObterEstadoPronto([Out] CA_MF_MSE_READY% Param_Out_ReadyState);

			/// <summary>
			/// (GetSourceBuffer) - Obtém o ICarenMFSourceBuffer no índice especificado na coleção de buffers.
			/// </summary>
			/// <param name="Param_Index">O Index para o buffer na coleção.</param>
			/// <param name="Param_Out_BufferFonte">Retorna um ponteiro para a interface(ICarenMFSourceBuffer) da fonte do buffer no index especificado. </param>
			CarenResult ObterBufferFonte(
				UInt32 Param_Index, 
				[Out] ICarenMFSourceBuffer^% Param_Out_BufferFonte);

			/// <summary>
			/// (GetSourceBuffers) - Obtém a coleção de buffers de origem associados a esta fonte de mídia.
			/// </summary>
			/// <param name="Param_Out_ListaBuffers">Retorna um ponteiro para a interface(ICarenMFSourceBufferList) de coleção de buffers.</param>
			CarenResult ObterColecaoBuffersFonte([Out] ICarenMFSourceBufferList^% Param_Out_ListaBuffers);

			/// <summary>
			/// (IsTypeSupported) - Obtém um valor que indica se o tipo MIME especificado é suportado pela fonte de mídia.
			/// </summary>
			/// <param name="Param_Type">O tipo de mídia para verificar o suporte.</param>
			/// <param name="Param_Out_Resultado">TRUE se o tipo de mídia for suportado; caso contrário, FALSE.</param>
			CarenResult VerificarTipoSuportado(
				String^ Param_Type, 
				[Out] Boolean% Param_Out_Resultado);

			/// <summary>
			/// (RemoveSourceBuffer) - Remove o buffer de origem especificado da coleta de buffers de origem gerenciados pelo objeto IMFMediaSourceExtension.
			/// </summary>
			/// <param name="Param_BufferFonte">Um ponteiro para a interface do buffer fonte a ser removido</param>
			CarenResult RemoverBufferFonte(ICarenMFSourceBuffer^ Param_BufferFonte);

			/// <summary>
			/// (SetDuration) - Define a duração da fonte de mídia em unidades de 100 nanossegundos.
			/// </summary>
			/// <param name="Param_Duracao">A duração da fonte de mídia em unidades de 100 nanossegundos</param>
			CarenResult DefinirDuracao(double^ Param_Duracao);

			/// <summary>
			/// (SetEndOfStream) - Indique que o fim da transmissão de mídia foi alcançado.
			/// </summary>
			/// <param name="Param_Error">Usado para passar informações de erro.</param>
			CarenResult DefinirFinalFluxo(CA_MF_MSE_ERROR Param_Error);
		};

		/// <summary>
		/// (IMFMediaEngineExtension) - Interface responsável por habilitar um aplicativo para carregar recursos de mídia no Media Engine.
		/// Para usar esta interface, defina o atributo MF_MEDIA_ENGINE_EXTENSION quando você chamar o método ICarenMFMediaEngineClassFactory::CriarInstancia.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]	
		[Guid("8A621BB9-67DA-491C-9A4E-ECA8B0B994FD")]
		public interface class ICarenMFMediaEngineExtension : ICaren
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
			/// (BeginCreateObject) - Começa uma solicitação assíncrona para criar um fluxo de byteou uma fonte de mídia.
			/// </summary>
			/// <param name="Param_Url">A URL do recurso de mídia.</param>
			/// <param name="Param_FluxpBytes">Um ponteiro para a interface ICarenMFByteStream.</param>
			/// <param name="Param_Tipo">Um membro da enumeração CA_TIPO_OBJETO_CRIADO que especifica qual tipo de objeto criar.</param>
			/// <param name="Param_Out_CookieCancelamento">Recebe um ponteiro para a interface IUnknown. Este ponteiro pode ser usado para cancelar a operação assíncrona, 
			/// passando o ponteiro para o método ICarenMFMediaEngineExtension::CancelarCriacaoObjeto.</param>
			/// <param name="Param_Callback">Um ponteiro para a interface ICarenMFAsyncCallback. Esta interface é usada para sinalizar a conclusão da operação assíncrona.</param>
			/// <param name="Param_ObjetoEstado">Um ponteiro para um objeto de estado implementado pelo usuário. Você pode usar este objeto para conter informações do estado
			/// para o retorno de chamada. O objeto é devolvido ao chamador quando o retorno de chamada é invocado. Este parâmetro pode ser NULO.</param>
			CarenResult CriarObjetoAsync(
				String^ Param_Url,
				ICarenMFByteStream^ Param_FluxpBytes,
				CA_TIPO_OBJETO_CRIADO Param_Tipo,
				[Out] ICaren^% Param_Out_CookieCancelamento,
				ICarenMFAsyncCallback^ Param_Callback,
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (CancelCreateObject) - Cancela a solicitação atual para criar um objeto.
			/// </summary>
			/// <param name="Param_CookieCancelamento">O ponteiro que foi devolvido no parâmetro (Param_Out_CookieCancelamento) do método ICarenMFMediaEngineExtension::CriarObjetoAsync.</param>
			CarenResult CancelarCriacaoObjeto(ICaren^ Param_CookieCancelamento);

			/// <summary>
			/// (CanPlayType) - Verifica se o objeto pode carregar um tipo especificado de recurso de mídia.
			/// </summary>
			/// <param name="Param_AudioOnly">Se TRUE, o Media Engine será configurado para o modo somente áudio. Caso contrário, o Media Engine está configurado para o 
			/// modo áudio-vídeo.</param>
			/// <param name="Param_MimeType">Uma sequência que contém um tipo MIME com um parâmetro de codecs opcional, conforme definido no RFC 4281.</param>
			/// <param name="Param_Out_Resultado">Recebe um membro da enumeração CA_MF_MEDIA_ENGINE_CANPLAY.</param>
			CarenResult PlayTypeObjeto(
				Boolean Param_AudioOnly,
				String^ Param_MimeType,
				[Out] CA_MF_MEDIA_ENGINE_CANPLAY% Param_Out_Resultado);

			/// <summary>
			/// (EndCreateObject) - Completa uma solicitação assíncrona para criar um fluxo de byteou fonte de mídia.
			/// </summary>
			/// <param name="Param_Resultado">Um ponteiro para a interface ICarenMFAsyncResult.</param>
			/// <param name="Param_Ref_Objeto">Recebe um ponteiro para interface do Media Source ou Byte Stream de acordo com o solicitado. Esse paramêtro não pode ser NULO. 
			/// O usuário é responsável por liberar a interface.</param>
			CarenResult FinalizarCriarObjeto(
				ICarenMFAsyncResult^ Param_Resultado,
				ICaren^% Param_Ref_Objeto);
		};

		/// <summary>
		/// (IMFMediaengineClassFactory) - Interface responsável por criar uma instância do Media Engine.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("642392D3-EA4D-4A18-9F83-9AC601536796")]
		public interface class ICarenMFMediaEngineClassFactory : ICaren
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
			/// (CreateError) - Cria um objeto de erro de mídia.
			/// </summary>
			/// <param name="Param_Out_MediaError"></param>
			CarenResult CriarError([Out] ICarenMFMediaError^% Param_Out_MediaError);

			/// <summary>
			/// (CreateInstance) - Cria uma nova instância do Media Engine.
			/// </summary>
			/// <param name="Param_Flags">Um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_CREATEFLAGS.</param>
			/// <param name="Param_Atributos">Um ponteiro para a interface ICarenMFAttributes de um armazenamento de atributos. Consulte a estrutura GUIDs_MFAtributos_MediaEngine
			/// para os atributos disponiveis para a Media Engine.</param>
			/// <param name="Param_Out_MediaEngine">Recebe um ponteiro para a interface ICarenMFMediaEngine. O chamador deve liberar a interface.</param>
			CarenResult CriarInstancia(
				CA_MF_MEDIA_ENGINE_CREATEFLAGS Param_Flags, 
				ICarenMFAttributes^ Param_Atributos,
				[Out] ICarenMFMediaEngine^% Param_Out_MediaEngine);

			/// <summary>
			/// (CreateTimeRange) - Cria um objeto de intervalo de tempo.
			/// </summary>
			/// <param name="Param_Out_TimeRange">Recebe um ponteiro para a interface ICarenMFMediaTimeRange. O chamador deve liberar a interface.</param>
			CarenResult CriarTimeRange([Out] ICarenMFMediaTimeRange^% Param_Out_TimeRange);
		};

		/// <summary>
		/// (IMFMediaengineClassFactory2) - Interface responsável por criar uma instância do objeto ICarenMFMediaKeys.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("26A33BEB-0536-4052-8382-9166670A5971")]
		public interface class ICarenMFMediaEngineClassFactory2 : ICaren
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
			/// (CreateMediaKeys2) - Cria um objeto de teclas de mídia com base no sistema de teclas especificado.
			/// </summary>
			/// <param name="Param_SystemKey">O sistema de chave da mídia.</param>
			/// <param name="Param_DefaultCmdStorePath">Aponta para o local de arquivo padrão para os dados do Módulo de Descriptografia de Conteúdo (MDM) da loja.</param>
			/// <param name="Param_InprivateCmdStorePath">Aponta para um local inprivado para os dados do Módulo de Descriptografia de Conteúdo (MDL) da loja. Especificar 
			/// esse caminho permite que o MDL cumpra a política de privacidade do aplicativo colocando informações pessoais no local de arquivo indicado por esse caminho.</param>
			/// <param name="Param_Out_MediaKeys">Recebe um ponteiro para a interface ICarenMFMediaKeys com as chaves de mídia.</param>
			CarenResult CriarMediaKeys2(
				String^ Param_SystemKey,
				String^ Param_DefaultCmdStorePath,
				String^ Param_InprivateCmdStorePath,
				[Out] ICarenMFMediaKeys^% Param_Out_MediaKeys);
		};

		/// <summary>
		/// (IMFMediaengineClassFactoryEx) - Interface responsável por estender a interface ICarenMFMediaEngineClassFactory.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("A9354340-1BD2-47E1-BB60-0215D451BC9D")]
		public interface class ICarenMFMediaEngineClassFactoryEx : ICarenMFMediaEngineClassFactory
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
			/// (CreateMediaKeys) - Cria um objeto de teclas de mídia com base no sistema de teclas especificado.
			/// </summary>
			/// <param name="Param_SystemKey">O sistema de chaves de mídia.</param>
			/// <param name="Param_CmdStorePath">Uma string que aponta para um local para armazenar dados do Módulo de Descriptografia de Conteúdo (MDL) que podem ser 
			/// bloqueados por vários processos e, portanto, podem ser incompatíveis com a suspensão do aplicativo da loja.</param>
			/// <param name="Param_Out_MediaKeys">Retorna um ponteiro para a interface de chaves da mídia.</param>
			CarenResult CriarMediaKeys(
				String^ Param_SystemKey,
				String^ Param_CmdStorePath,
				[Out] ICarenMFMediaKeys^% Param_Out_MediaKeys);

			/// <summary>
			/// (CreateMediaSourceExtension) - Cria uma instância do ICarenMFMediaSourceExtension.
			/// </summary>
			/// <param name="Param_Flags">Este parâmetro é reservado e deve ser definido como 0.</param>
			/// <param name="Param_Atributos">Os atributos para criação da extensão da fonte de midia.</param>
			/// <param name="Param_Out_ExtensaoFonteMidia">Retorna um ponteiro para a interface de extensão da fonte de mídia criada.</param>
			CarenResult CriarExtensaoFonteMidia(
				UInt32 Param_Flags, 
				ICarenMFAttributes^ Param_Atributos, 
				[Out] ICarenMFMediaSourceExtension^% Param_Out_ExtensaoFonteMidia);

			/// <summary>
			/// (IsTypeSupported) - Obtém um valor que indica se o sistema de tecla especificado suporta o tipo de mídia especificado.
			/// </summary>
			/// <param name="Param_MIMEType">O tipo MIME para verificar o suporte.</param>
			/// <param name="Param_SystemKey">O sistema-chave para verificar o suporte.</param>
			/// <param name="Param_Out_Suporte">Retorna TRUE se o tipo for suportado por (Param_SystemKey); caso contrário, FALSE.</param>
			CarenResult VerificarTipoSuportado(
				String^ Param_MIMEType,
				String^ Param_SystemKey,
				[Out] Boolean% Param_Out_Suporte);
		};

		/// <summary>
		/// (IMFMediaEngineNeedKeyNotify) - Interface responsável por representar um retorno de chamada ao mecanismo de mídia para notificar os dados de solicitação de chave.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("B860682F-E26E-4C44-970C-57DDC61BB272")]
		public interface class ICarenMFMediaEngineNeedKeyNotify : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Define os Delegates.

			/// <summary>
			/// Delegate do evento OnNeedKeys.
			/// </summary>
			delegate void Delegate_OnNeedKeys(cli::array<Byte>^ Param_BufferInicial, UInt32 Param_Count);


			//Define os eventos

			/// <summary>
			/// Evento chamado para notificar o aplicativo de que uma chave ou chaves são necessárias juntamente com quaisquer dados de inicialização.
			/// </summary>
			event Delegate_OnNeedKeys^ OnNeedKeys;



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
		/// (IMFMediaEngineNotify) - Interface responsável por notificar o aplicativo quando ocorre um evento de reprodução.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("C6A87536-01A2-4013-877D-D88255953091")]
		public interface class ICarenMFMediaEngineNotify : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			
			/// <summary>
			/// Delegate do evento OnEventNotify.
			/// </summary>
			delegate void Delegate_OnEventNotify(CA_MF_MEDIA_ENGINE_EVENT Param_EventoMediaEngine, IntPtr Param_Parametro1, UInt32 Param_Parametro2);


			//Define os eventos

			/// <summary>
			/// Evento chamado para notificar o aplicativo quando ocorre um evento de reprodução.
			/// </summary>
			event Delegate_OnEventNotify^ OnEventNotify;



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
		/// (IMFContentProtectionManager) - Interface responsável por habilitar a reprodução de conteúdo protegido fornecendo ao aplicativo um ponteiro para um objeto 
		/// ativador de conteúdo. Aplicativos que reproduzam conteúdo protegido devem implementar essa interface.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("3CF2E59F-67BB-4D52-8EFA-76F82E2D23A7")]
		public interface class ICarenMFContentProtectionManager : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			/// <summary>
			/// (BeginEnableContent) - Começa uma solicitação assíncrona para executar uma ação de habilitação de conteúdo.
			/// Este método solicita que o aplicativo execute uma etapa específica necessária para adquirir direitos sobre o conteúdo, usando um objeto ativador de conteúdo.
			/// </summary>
			/// <param name="Param_Ativador">Ponteiro para a interface ICarenMFActivate de um objeto ativador de conteúdo. Para criar o ativador de conteúdo, ligue para 
			/// o método ICarenMFActivate::AtivarObjeto e solicite a interface IMFContentEnabler. O aplicativo deve usar os métodos no IMFContentEnabler para concluir 
			/// a ação de habilitação de conteúdo.</param>
			/// <param name="Param_Topologia">Ponteiro para a interface ICarenMFTopology da topologia pendente.</param>
			/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. Quando a operação estiver concluída, o aplicativo 
			/// deve chamar ICarenMFAsyncCallback::Invoke no retorno de chamada.</param>
			/// <param name="Param_ObjetoEstado">Reservado. Atualmente este parâmetro é sempre NULO.</param>
			CarenResult EnableContentAsync(
				ICarenMFActivate^ Param_Ativador, 
				ICarenMFTopology^ Param_Topologia, 
				ICarenMFAsyncCallback^ Param_Callback, 
				ICaren^ Param_ObjetoEstado);

			/// <summary>
			/// (EndEnableContent) - Termina uma solicitação assíncrona para executar uma ação de habilitação de conteúdo. Esse método é chamado pelo caminho de mídia 
			/// protegida (PMP) para concluir uma chamada assíncrona ao ICarenMFContentProtectionManager::EnableContentAsync.
			/// </summary>
			/// <param name="Param_Resultado">Ponteiro para a interface IMFAsyncResultado. Este ponteiro é o mesmo valor que o aplicativo passou para o método 
			/// ICarenMFAsyncCallback:::Invoke.</param>
			CarenResult FinalizarEnableContent(ICarenMFAsyncResult^ Param_Resultado);
		};

		/// <summary>
		/// (IMFMediaEngineProtectedContent) - Interface responsável por permitir que o Media Engine reproduzam conteúdo de vídeo protegido.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("4F1F1E15-DB13-4FB7-9C89-79A41CB0DB35")]
		public interface class ICarenMFMediaEngineProtectedContent : ICaren
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
			/// (GetRequiredProtections) - Obtém as proteções de conteúdo que devem ser aplicadas no modo frame-server.
			/// </summary>
			/// <param name="Param_Out_ProtecoesRequisitadasFlags">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS.</param>
			CarenResult ObterProtecaoRequerida([Out] CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS% Param_Out_ProtecoesRequisitadasFlags);

			/// <summary>
			/// (SetApplicationCertificate) - Define o certificado do aplicativo.
			/// </summary>
			/// <param name="Param_BufferCertificado">Um buffer que contém o certificado no formato X.509, seguido pelo identificador de aplicativo 
			/// assinado com uma assinatura SHA-256 usando a chave privada do certificado.</param>
			/// <param name="Param_CountData">O tamanho do Buffer (Param_BufferCertificado), em bytes.</param>
			CarenResult DefinirCertificadoAplicacao(cli::array<Byte>^ Param_BufferCertificado, UInt32 Param_CountData);

			/// <summary>
			/// (SetContentProtectionManager) - Define o CPM (Content Protection Manager).
			/// </summary>
			/// <param name="Param_CPM">Um ponteiro para a interface ICarenContentProtectionManager, implementado pelo chamador.</param>
			CarenResult DefinirGerenciadorProtecaoConteudo(ICarenMFContentProtectionManager^ Param_CPM);

			/// <summary>
			/// (SetOPMWindow) - Especifica a janela que deve receber proteções de link de saída.
			/// </summary>
			/// <param name="Param_WinHandle">A Handle para a janela a receber as proteções.</param>
			CarenResult DefinirOPMWindow(IntPtr Param_WinHandle);

			/// <summary>
			/// (ShareResources) - Permite que o Media Engine acesse conteúdo protegido enquanto estiver no modo frame-server.
			/// </summary>
			/// <param name="Param_D3D11DeviceContext">Um ponteiro para o conteúdo do dispositivo Direct3D 11. O Media Engine consulta este ponteiro para a interface 
			/// ID3D11VideoContext.</param>
			CarenResult CompartilharRecursos(ICaren^ Param_D3D11DeviceContext);

			/// <summary>
			/// (TransferVideoFrame) - Copia um quadro de vídeo protegido para uma superfície DXGI.
			/// </summary>
			/// <param name="Param_SuperficeDestino">Um ponteiro para a interface da superfície de destino.</param>
			/// <param name="Param_RetanguloOrigem">Uma estrutura MFVideoNormalizedRect(CA_RECT) que especifica o retângulo de origem</param>
			/// <param name="Param_RetanguloDestino">Uma estrutura CA_RECT que especifica o retângulo de destino.</param>
			/// <param name="Param_CorBorda">Uma estrutura CA_MFARGB que especifica a cor da borda.</param>
			/// <param name="Param_Out_FlagsProtecaoConteudo">Recebe um OR bit a bit de zero ou mais sinalizadores da enumeração CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS. 
			/// Esses sinalizadores indicam quais proteções de conteúdo o aplicativo deve aplicar antes de apresentar a superfície.</param>
			CarenResult TransferirFrameVideo(
				ICaren^ Param_SuperficeDestino,
				CA_RECT^ Param_RetanguloOrigem,
				CA_RECT^ Param_RetanguloDestino,
				CA_MFARGB^ Param_CorBorda,
				[Out] CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS% Param_Out_FlagsProtecaoConteudo);
		};

		/// <summary>
		/// (IMFMuxStreamAttributesManager) - Interface responsável por fornecer acesso aos atributos(ICarenMFAttributes) dos subfluxos de uma fonte de mídia multiplexada.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("B8A913DA-395A-41AD-BACD-3BF56EABBB54")]
		public interface class ICarenMFMuxStreamAttributesManager : ICaren
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
			/// (GetAttributes) - Obtém os ICarenMFAttributes para o substream com o índice especificado.
			/// </summary>
			/// <param name="Param_MuxStreamIndex">O índice do subfluxo para o qual os atributos são recuperados.</param>
			/// <param name="Param_Out_Atributos">Retorna os atributos para o subfluxo especificado.</param>
			CarenResult ObterAtributos(
				UInt32^ Param_MuxStreamIndex, 
				[Out] ICarenMFAttributes^% Param_Out_Atributos);

			/// <summary>
			/// (GetStreamCount) - Obtém a contagem de subfluxos gerenciados pela fonte de mídia multiplexada.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Retorna a contagem de subfluxos gerenciados pela fonte de mídia multiplexada.</param>
			CarenResult ObterQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos);
		};

		/// <summary>
		/// (IMFMuxStreamSampleManager) - Interface responsável por fornecer a capacidade de recuperar objetos ICarenMFSample para subfluxos individuais dentro da saída de uma fonte de mídia multiplexada.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("189EE827-3F9A-419D-A8CF-4BF9A57C9887")]
		public interface class ICarenMFMuxStreamSampleManager : ICaren
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
			/// (GetSample) -  Obtém a ICarenMFSample associado ao subfluxo com o índice especificado.
			/// </summary>
			/// <param name="Param_MuxStreamIndex">O índice do subfluxo para o qual uma amostra é recuperada.</param>
			/// <param name="Param_Out_Amostra">Retorna um ponteiro para a interface da amostra recuperada.</param>
			CarenResult ObterAmostra(
				UInt32 Param_MuxStreamIndex, 
				[Out] ICarenMFSample^% Param_Out_Amostra);

			/// <summary>
			/// (GetStreamConfiguration) - Obtém a configuração de fluxo ativo para a fonte de mídia, que define o conjunto de subfluxos que incluem a saída multiplexada.
			/// </summary>
			/// <param name="Param_Out_Config">Retorna a configuração do fluxo.</param>
			CarenResult ObterConfiguracoesFluxo([Out] UInt64% Param_Out_Config);

			/// <summary>
			/// (GetStreamCount) - Obtém a contagem de subfluxos gerenciados pela fonte de mídia multiplexada.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Retorna a quantidade de subfluxos.</param>
			CarenResult ObterQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos);
		};

		/// <summary>
		/// (IMFMuxStreamMediaTypeManager) - Interface responsável permitir o gerenciamento de configurações de fluxo para uma fonte de mídia multiplexada. Uma configuração de fluxo define um conjunto de 
		/// subfluxos que podem ser incluídos na saída multiplexada.
		/// </summary>
		[CategoryAttribute("Interface MediaFoundation")]
		
		[Guid("4032E631-C97A-4472-8ACF-A840205A347F")]
		public interface class ICarenMFMuxStreamMediaTypeManager : ICaren
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
			/// (AddStreamConfiguration) - Registra uma configuração de fluxo, que define um conjunto de subfluxos que podem ser incluídos na saída multiplexada.
			/// </summary>
			/// <param name="Param_ullStreamMask">Um valor de máscara de bits onde os bits que estão ligados representam os índices dos subfluxos incluídos na configuração do fluxo.</param>
			CarenResult AdicionarConfiguracaoFluxo(UInt64 Param_ullStreamMask);

			/// <summary>
			/// (GetMediaType) - Obtém a ICarenMFMediaType do subfluxo com o índice especificado.
			/// </summary>
			/// <param name="Param_MuxStreamIndex">O índice do subfluxo para o qual o tipo de mídia é recuperado.</param>
			/// <param name="Param_Out_MediaType">Retorna o tipo de mídia do subfluxo com o índice especificado.</param>
			CarenResult ObterMediaType(
				UInt32^ Param_MuxStreamIndex,
				[Out] ICarenMFMediaType^% Param_Out_MediaType);

			/// <summary>
			/// (GetStreamConfiguration) - Obtém a configuração do fluxo com o índice especificado, que define um conjunto de subfluxos que podem ser incluídos na saída multiplexada.
			/// </summary>
			/// <param name="Param_ulIndex">O índice da configuração para recuperar.</param>
			/// <param name="Param_Out_IndexStreamMask">Retorna índice da configuração recuperada.</param>
			CarenResult ObterConfiguracaoFluxo(
				UInt32 Param_ulIndex, 
				[Out] UInt64% Param_Out_IndexStreamMask);

			/// <summary>
			/// (GetStreamConfigurationCount) - Obtém a contagem de configurações de fluxo registradas, que definem conjunto de subfluxos que podem ser incluídos na saída multiplexada.
			/// </summary>
			/// <param name="Param_Out_Quantidade">Retorna a quantidade de configurações de fluxo registradas.</param>
			CarenResult ObterQuantidadeConfigsFluxo([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (GetStreamCount) - Obtém a contagem de subfluxos gerenciados pela fonte de mídia multiplexada.
			/// </summary>
			/// <param name="Param_Out_QuantidadeFluxos">Retorna a contagem de subfluxos gerenciados pela fonte de mídia multiplexada.</param>
			CarenResult ObterQuantidadeFluxos([Out] UInt32% Param_Out_QuantidadeFluxos);

			/// <summary>
			/// (RemoveStreamConfiguration) - Desregistra uma configuração de fluxo, que define um conjunto de subfluxos que podem ser incluídos na saída multiplexada.
			/// </summary>
			/// <param name="Param_ullStreamMask">Um valor de máscara de bits onde os bits que estão ligados representam os índices dos subfluxos incluídos na configuração do fluxo.</param>
			CarenResult RemoverConfiguracaoFluxo(UInt64 Param_ullStreamMask);
		};
	}
}