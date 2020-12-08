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

using namespace System;

//Declara o namespace principal.
namespace CarenRengine
{
	//Namespace que contém o sistema de status utilizado pela biblioca.
	namespace CarenCodesStatus
	{
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//ATENCAO: QUALQUER MODIFICACAO OU ADICAO DE UM NOVO ENUM NA ENUMERACAO ABIAXO(ResultCode) DEVE SER ADICIONADO AOS MÉTODOS DA CLASSE (ResultCodeState)//
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Enumera os códigos de retorno para a plataforma. Esses códios refletem os erros HRESULT das plataformas nativas implementadas aqui.
		/// </summary>
		[System::FlagsAttribute]
		public enum class ResultCode
		{
			/////////////////////////////////////////////
			//ENUMS DE SUCESSO BASE DO SISTEMA WINDOWS.//
			////////////////////////////////////////////

			/// <summary>
			/// (S_OK) - O método foi bem sucedido.
			/// </summary>
			SS_OK,

			/// <summary>
			/// (E_FALSE) - O método foi bem sucedido, mais o resultado da operação pode não ter sido.
			/// </summary>
			SS_FALSE,






			//////////////////////////////////////////////
			//ENUMS PROPRIOS UTILIZADOS PELA BIBLIOTECA.//
			//////////////////////////////////////////////

			/// <summary>
			/// Indica que não foi possível traduzir um HRESULT para está enumeração. Obtenha o código de erro na interface onde o erro ocorreu ou acesse o método GetLastError.
			/// </summary>
			ER_CONVERSAO_HRESULT,

			/// <summary>
			/// Indica que houve uma falha ao converter os dados de uma provariant Gerenciada ou Nativa.
			/// </summary>
			ER_CONVERSAO_PROPVARIANT,

			/// <summary>
			/// Indica que ao tentar converter a estrutura (Gerenciada ou Nativa) ocorreu uma falha.
			/// </summary>
			ER_CONVERSAO_ESTRUTURA,

			/// <summary>
			/// Indica que o tipo informado não pode ser convertido para uma representação nativa ou não há suporte para o tipo.
			/// </summary>
			ER_CONVERSAO_TIPO_NAO_SUPORTADO,

			/// <summary>
			/// Indica que a largura(Total) a ser escrito em um buffer é invalida. O valor deve ser diferente de 0 e menor ou igual ao tamanho maximo do buffer.
			/// </summary>
			ER_CARENBUFFER_LARGURA_ESCRITA_INVALIDA,

			/// <summary>
			/// Indica que o ponto a qual iria ser iniciado uma escrita ou copia é invalido. O index deve ser maior ou igual a 0 e menor ou igual a largura maxima do buffer.
			/// </summary>
			ER_CARENBUFFER_START_INDEX_INVALIDO,

			/// <summary>
			/// Indica que houve uma falha ao converter possiveis dados de um matriz gerenciada para a nativa.
			/// </summary>
			ER_CARENBUFFER_FALHA_CONVERSAO,

			/// <summary>
			/// O ponteiro do buffer atual é invalido.
			/// </summary>
			ER_CARENBUFFER_POINTER,

			/// <summary>
			/// O GUID de identifciação é invalido.
			/// </summary>
			ER_GUID_INVALIDO,

			/// <summary>
			/// Não foi possivel criar ou converter uma PropVariant nativa ou gerenciada.
			/// </summary>
			ER_PROPVARIANT_CREATE_OR_CONVERSION,

			/// <summary>
			/// O tipo da PropVariant não é suportado por essa biblioteca.
			/// </summary>
			ER_PROPVARIANT_TYPE_NO_SUPPORTED,



			///////////////////////////////////////////////////////////////////////////////////////////////////
			//ENUMS DE ERROS COMUNS EM CHAMADAS `COM` E DE API`S NĂO ULTILIZADAS DIRETAMENTE PELA BIBLIOTECA.//
			///////////////////////////////////////////////////////////////////////////////////////////////////


			/// <summary>
			/// (E_NOT_SUFFICIENT_BUFFER) - O Buffer é insuficiente para a função requisitada.
			/// </summary>
			ER_E_NOT_SUFFICIENT_BUFFER,

			/// <summary>
			/// (E_ABORT) - O aplicativo cancelou a operação.
			/// </summary>
			ER_E_ABORT,

			/// <summary>
			/// (E_NOTIMPL) - O método ou função não está implementado.
			/// </summary>
			ER_E_NOTIMPL,

			/// <summary>
			/// (E_INVALIDARG) - Um argumento passado é invalido, ou alguma configuração não é valida.
			/// </summary>
			ER_E_INVALIDARG,

			/// <summary>
			/// (E_OUTOFMEMORY) - Não há memória suficiente no sistema para realizar a operação.
			/// </summary>
			ER_E_OUTOFMEMORY,

			/// <summary>
			/// (STG_E_ACCESSDENIED) - O fluxo ou arquivo é somente leitura; o método não foi capaz de definir o valor.
			/// </summary>
			ER_STG_E_ACCESSDENIED,
				
			/// <summary>
			/// (STG_E_CANTSAVE) - Não é possível salvar.
			/// </summary>
			ER_STG_E_CANTSAVE,

			/// <summary>
			/// (STG_E_MEDIUMFULL) - Não há espaço em disco suficiente para concluir a operação.
			/// </summary>
			ER_STG_E_MEDIUMFULL,

			/// <summary>
			/// (ERROR_INVALID_FUNCTION) - A chamada para a função é invalida no estado atual.
			/// </summary>
			ER_ERROR_INVALID_FUNCTION,

			/// <summary>
			/// (ERROR_OBJECT_ALREADY_EXISTS) - Um Item, Chave ou Interface já existe com os dados informados.
			/// </summary>
			ER_ERROR_OBJECT_ALREADY_EXISTS,

			/// <summary>
			/// (E_HANDLE) - A handle é invalida ou não é um identificador valido para o componente esperado pelo método.
			/// </summary>
			ER_E_HANDLE,

			/// <summary>
			/// (E_NOINTERFACE) - A interface solicitada não está disponivel ou não existe.
			/// </summary>
			ER_E_NOINTERFACE,

			/// <summary>
			/// (E_POINTER) - Indica que um ponteiro solicitado ou atual é invalido.
			/// </summary>
			ER_E_POINTER,

			/// <summary>
			/// (ERROR_ALREADY_EXISTS) - O arquivo, evento ou registro de entrada já existe.
			/// </summary>
			ER_ERROR_ALREADY_EXISTS,

			/// <summary>
			/// (E_NOTFOUND) - Objeto não está disponivel ou não foi encontrado.
			/// </summary>
			ER_E_NOTFOUND,

			/// <summary>
			/// (E_ACCESSDENIED) - Erro genérico de acesso negado.
			/// </summary>
			ER_E_ACCESSDENIED,

			/// <summary>
			/// (E_UNEXPECTED) - Falha catastrófica.
			/// </summary>
			ER_E_UNEXPECTED,

			/// <summary>
			/// (E_PENDING) - 
			/// </summary>
			ER_E_PENDING,

			/// <summary>
			/// (E_FAIL) - Representa uma falha não identificada.
			/// </summary>
			ER_FAIL,




			////////////////////////////
			//ENUMS DA CORE AUDIO APIs//
			////////////////////////////

			// -> Sucessos

			/// <summary>
			/// (AUDCLNT_S_BUFFER_EMPTY | SS_FALSE) - A chamada foi bem sucedida e o número de frames lidos é 0, indicando que nenhum dado de captura está disponivel para ser lido. 
			/// </summary>
			SS_AUDCLNT_S_BUFFER_EMPTY = SS_FALSE,

			/// <summary>
			/// 
			/// </summary>
			SS_AUDCLNT_S_THREAD_ALREADY_REGISTERED = ER_FAIL + 1,

			/// <summary>
			/// 
			/// </summary>
			SS_AUDCLNT_S_POSITION_STALLED,


			// -> Erros

			/// <summary>
			/// (AUDCLNT_E_DEVICE_INVALIDATED) - O usuário removeu o dispositivo de ponto de extremidade de áudio ou o dispositivo de adaptador ao qual o dispositivo de ponto de extremidade se conecta.
			/// </summary>
			ER_AUDCLNT_E_DEVICE_INVALIDATED,

			/// <summary>
			/// (AUDCLNT_E_NOT_INITIALIZED) - O fluxo de áudio não foi inicializado com éxito.
			/// </summary>
			ER_AUDCLNT_E_NOT_INITIALIZED,

			/// <summary>
			/// (AUDCLNT_E_SERVICE_NOT_RUNNING) - O serviço de áudio do Windows não está em execução.
			/// </summary>
			ER_AUDCLNT_E_SERVICE_NOT_RUNNING,

			/// <summary>
			/// (AUDCLNT_E_WRONG_ENDPOINT_TYPE) - O chamador tentou acessar um IAudioCaptureClient interface em um ponto de extremidade de renderização ou um IAudioRenderClient interface em um ponto de extremidade de captura.
			/// </summary>
			ER_AUDCLNT_E_WRONG_ENDPOINT_TYPE,

			/// <summary>
			/// (AUDCLNT_E_NOT_STOPPED) - O fluxo de áudio não foi interrompido no momento em que a chamada foi feita.
			/// </summary>
			ER_AUDCLNT_E_NOT_STOPPED,

			/// <summary>
			/// (AUDCLNT_E_EVENTHANDLE_NOT_SET) - O fluxo de áudio é configurado para usar o buffer orientado a eventos, mas o chamador não chamou ICarenAudioClient::SetEventHandle para definir o identificador de evento no fluxo.
			/// </summary>
			ER_AUDCLNT_E_EVENTHANDLE_NOT_SET,

			/// <summary>
			/// (AUDCLNT_E_ALREADY_INITIALIZED) - O objeto IAudioClient já está inicializado.
			/// </summary>
			ER_AUDCLNT_E_ALREADY_INITIALIZED,

			/// <summary>
			/// (AUDCLNT_E_BUFFER_OPERATION_PENDING) - O cliente está atualmente gravando ou lendo a partir do buffer.
			/// </summary>
			ER_AUDCLNT_E_BUFFER_OPERATION_PENDING,

			/// <summary>
			/// (AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED) - O tamanho do buffer solicitado não está alinhado. Esse código pode ser retornado para um render ou um dispositivo de captura se o chamador especificado AUDCLNT_SHAREMODE_EXCLUSIVE e o 
			/// AUDCLNT_STREAMFLAGS_EVENTCALLBACK sinalizadores.
			/// </summary>
			ER_AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED,

			/// <summary>
			/// (AUDCLNT_E_BUFFER_SIZE_ERROR) - Indica que o valor de duração do buffer solicitado por um cliente de modo exclusivo está fora do intervalo. O valor de duração solicitada para o modo de pull não deve ser maior que 500 
			/// milissegundos; para o modo de push o valor de duração não deve ser maior que 2 segundos.
			/// </summary>
			ER_AUDCLNT_E_BUFFER_SIZE_ERROR,

			/// <summary>
			/// (AUDCLNT_E_BUFFER_ERROR) - Houve uma falha interna do método (ICarenAudioRenderClient::GetBuffer) ao recuperar um ponteiro para os dados.
			/// </summary>
			ER_AUDCLNT_E_BUFFER_ERROR,

			/// <summary>
			/// (AUDCLNT_E_BUFFER_TOO_LARGE) - O valor de Param_NumeroFramesRequisitados excede o espaço de buffer disponível (tamanho do buffer menos tamanho de preenchimento).
			/// </summary>
			ER_AUDCLNT_E_BUFFER_TOO_LARGE,

			/// <summary>
			/// (AUDCLNT_E_INVALID_SIZE) - O valor Param_NumeroFramesEscritos excede o valor Param_NumeroFramesRequisitados especificado na chamada (ICarenAudioRenderClient::GetBuffer) anterior.
			/// </summary>
			ER_AUDCLNT_E_INVALID_SIZE,

			/// <summary>
			/// (AUDCLNT_E_OUT_OF_ORDER) - Uma chamada para o método ICarenAudioRenderClient::GetBuffer ainda está em vigor.
			/// </summary>
			ER_AUDCLNT_E_OUT_OF_ORDER,

			/// <summary>
			/// (AUDCLNT_E_CPUUSAGE_EXCEEDED) - Indica que a duração da passagem do processo excedeu o uso máximo da CPU. O mecanismo de áudio mantém o controle do uso da CPU, mantendo o número de vezes que a duração da passagem do processo 
			/// excede o uso máximo da CPU. O uso máximo da CPU é calculado como uma porcentagem da periodicidade do mecanismo. O valor percentual é o valor do acelerador de CPU do sistema (dentro do intervalo de 10% e 90%). Se esse valor 
			/// não for encontrado, o valor padrão de 40% será usado para calcular o uso máximo da CPU.
			/// </summary>
			ER_AUDCLNT_E_CPUUSAGE_EXCEEDED,

			/// <summary>
			/// (AUDCLNT_E_DEVICE_IN_USE) - O dispositivo de ponto de extremidade já está em uso. O dispositivo está sendo usado no modo exclusivo, ou o dispositivo está sendo usado no modo compartilhado e o chamador pediu para usar o 
			/// dispositivo no modo exclusivo.
			/// </summary>
			ER_AUDCLNT_E_DEVICE_IN_USE,

			/// <summary>
			/// (AUDCLNT_E_ENDPOINT_CREATE_FAILED) - O método falhou ao criar o ponto de extremidade de áudio para a renderização ou o dispositivo de captura. Isso pode ocorrer se o dispositivo de ponto de extremidade de áudio tiver sido 
			/// desconectado ou o hardware de áudio ou recursos de hardware associados tiverem sido reconfigurados, desabilitados, removidos ou de outra forma disponibilizados para uso.
			/// </summary>
			ER_AUDCLNT_E_ENDPOINT_CREATE_FAILED,

			/// <summary>
			/// (AUDCLNT_E_INVALID_DEVICE_PERIOD) - Indica que o período de dispositivo solicitado por um cliente de modo exclusivo é maior que 500 milissegundos.
			/// </summary>
			ER_AUDCLNT_E_INVALID_DEVICE_PERIOD,

			/// <summary>
			/// (AUDCLNT_E_UNSUPPORTED_FORMAT) - O mecanismo de áudio (modo compartilhado) ou dispositivo de ponto de extremidade de áudio (modo exclusivo) não suporta o formato especificado.
			/// </summary>
			ER_AUDCLNT_E_UNSUPPORTED_FORMAT,

			/// <summary>
			/// (AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED) - O chamador está solicitando o uso de modo exclusivo do dispositivo de ponto de extremidade, mas o usuário desabilitou o uso de modo exclusivo do dispositivo.
			/// </summary>
			ER_AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED,

			/// <summary>
			/// (AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL) - O sinalizador AUDCLNT_STREAMFLAGS_EVENTCALLBACK é definido, mas os parâmetros BufferDuration e PeriodoDispositivo não são iguais.
			/// </summary>
			ER_AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL,



			//////////////////////////
			//ENUMS API WAIT SyncApi//
			//////////////////////////

			// -> Sucessos

			/// <summary>
			/// (WAIT_TIMEOUT) - O intervalo de tempo limite transcorreu e o estado do objeto não está sinalizado.
			/// </summary>
			SS_WAIT_TIMEOUT,

			/// <summary>
			/// (WAIT_OBJECT_0) - O estado do objeto especificado é sinalizado.
			/// </summary>
			SS_WAIT_OBJECT_0 = SS_OK,

			/// <summary>
			/// (WAIT_ABANDONED) - O objeto especificado é um objeto mutex que não foi liberado pelo segmento que possuía o objeto mutex antes do thread terminar. 
			/// A propriedade do objeto mutex é concedida ao segmento de chamada e o mutex é definido como não sinalizado.
			/// Se o mutex estava protegendo informações persistentes do estado, você deve verificá-lo para a consisténcia.
			/// </summary>
			SS_WAIT_ABANDONED = SS_WAIT_TIMEOUT + 1,

			/// <summary>
			/// (WAIT_IO_COMPLETION) - A espera foi encerrada por uma ou mais chamadas de procedimento assíncrono do modo de usuário (APC) na fila para o segmento.
			/// </summary>
			SS_WAIT_IO_COMPLETION,


			// -> Erros

			/// <summary>
			/// (WAIT_FAILED) - A função falhou. Para obter informações de erro estendidas, ligue para GetLastError.
			/// </summary>
			ER_WAIT_FAILED,



			///////////////////////
			//ENUMS DA API (TIME)//
			///////////////////////

			// -> Sucessos

			/// <summary>
			/// (MMSYSERR_NOERROR | SS_OK) - A operação foi bem sucedida.
			/// </summary>
			SS_MMSYSERR_NOERROR = SS_OK,

			/// <summary>
			/// (TIMERR_NOERROR | SS_OK) - A operação foi bem sucedida.
			/// </summary>
			SS_TIMERR_NOERROR = SS_OK,


			// -> Erros

			/// <summary>
			/// (TIMERR_NOCANDO | SS_FALSE) - Houve um erro ao completar a requisição.
			/// </summary>
			ER_TIMERR_NOCANDO = SS_FALSE,



			///////////////////////////
			//ENUMS D3DERR(Direct3D9)//
			///////////////////////////


			// -> Sucessos

			/// <summary>
			/// (D3DOK_NOAUTOGEN) - Este é um código de sucesso. No entanto, a autogeração de mipmaps não é suportada para este formato. Isso significa que a criação de 
			/// recursos terá sucesso, mas os níveis de mipmap não serão gerados automaticamente.
			/// </summary>
			SS_D3DOK_NOAUTOGEN = ER_WAIT_FAILED + 1,

			/// <summary>
			/// (D3D_OK | SS_OK) - Não houve erro.
			/// </summary>
			SS_D3D_OK = SS_OK,

			/// <summary>
			/// (S_NOT_RESIDENT) - Pelo menos uma alocação que compõe os recursos está em disco. Direct3D 9Ex apenas.
			/// </summary>
			SS_S_NOT_RESIDENT = SS_D3DOK_NOAUTOGEN + 1,

			/// <summary>
			/// (S_RESIDENT_IN_SHARED_MEMORY) - Nenhuma alocação que componha os recursos estão em disco. No entanto, pelo menos uma alocação não está na memória acessível á GPU. Direct3D 9Ex apenas.
			/// </summary>
			SS_S_RESIDENT_IN_SHARED_MEMORY,

			/// <summary>
			/// (S_PRESENT_MODE_CHANGED) - O modo de exibição da área de trabalho foi alterado. O aplicativo pode continuar renderizando, mas pode haver conversão/alongamento de cores. Escolha um formato de buffer traseiro semelhante ao modo de exibição atual e ligue para o Reset para recriar as cadeias de swap. O dispositivo deixará este estado depois que um Reset for chamado. Direct3D 9Ex apenas.
			/// </summary>
			SS_S_PRESENT_MODE_CHANGED,

			/// <summary>
			/// (S_PRESENT_OCCLUDED) - A área de apresentação é ocluída. A oclusão significa que a janela de apresentação é minimizada ou outro dispositivo entrou no modo fullscreen no mesmo monitor que a janela de apresentação e a janela de apresentação está completamente naquele monitor. A oclusão não ocorrerá se a área do cliente for coberta por outra Janela. Os aplicativos occluded podem continuar renderizando e todas as chamadas terão sucesso, mas a janela de apresentação ocluída não será atualizada.
			/// </summary>
			SS_S_PRESENT_OCCLUDED,


			// -> Erros

			/// <summary>
			/// (D3DERR_INVALIDCALL) - A chamada do método é inválida. Por exemplo, o parâmetro de um método pode não ser um ponteiro válido.
			/// </summary>
			ER_D3DERR_INVALIDCALL,

			/// <summary>
			/// (D3DERR_CONFLICTINGRENDERSTATE) - Os estados de renderização atualmente definidos não podem ser usados juntos.
			/// </summary>
			ER_D3DERR_CONFLICTINGRENDERSTATE,

			/// <summary>
			/// (D3DERR_CONFLICTINGTEXTUREFILTER) - Os filtros de textura atuais não podem ser usados juntos.
			/// </summary>
			ER_D3DERR_CONFLICTINGTEXTUREFILTER,

			/// <summary>
			/// (D3DERR_CONFLICTINGTEXTUREPALETTE) - As texturas atuais não podem ser usadas simultaneamente.
			/// </summary>
			ER_D3DERR_CONFLICTINGTEXTUREPALETTE,

			/// <summary>
			/// (D3DERR_DEVICEHUNG) - O dispositivo que devolveu este código fez com que o adaptador de hardware fosse redefinido pelo Sistema Operacional. A maioria das aplicações deve destruir o dispositivo e sair. Os aplicativos que devem continuar devem destruir todos os objetos de memória de vídeo (superfícies, texturas, blocos de estado etc) e ligar para o Reset() para colocar o dispositivo em um estado padrão. Se o aplicativo continuar renderizando da mesma forma, o dispositivo voltará a este estado. Aplica - se apenas ao Direct3D 9Ex.
			/// </summary>
			ER_D3DERR_DEVICEHUNG,

			/// <summary>
			/// (D3DERR_DEVICELOST) - O dispositivo foi perdido, mas não pode ser redefinido neste momento. Portanto, renderização não é possível. Um objeto do dispositivo Direct3D diferente do que devolveu este código fez com que o adaptador de hardware fosse redefinido pelo Sistema Operacional. Exclua todos os objetos de memória de vídeo (superfícies, texturas, blocos de estado) e ligue para o Reset() para devolver o dispositivo a um estado padrão. Se o aplicativo continuar renderizando sem um reset, as chamadas de renderização terão sucesso.
			/// </summary>
			ER_D3DERR_DEVICELOST,

			/// <summary>
			/// (D3DERR_DEVICENOTRESET) - O dispositivo foi perdido, mas pode ser redefinido neste momento.
			/// </summary>
			ER_D3DERR_DEVICENOTRESET,

			/// <summary>
			/// (D3DERR_DEVICEREMOVED) - O adaptador de hardware foi removido. O aplicativo deve destruir o dispositivo, fazer enumeração de adaptadores e criar outro dispositivo Direct3D. Se o aplicativo continuar renderizando sem ligar para o Reset, as chamadas de renderização terão sucesso. Aplica - se apenas ao Direct3D 9Ex.
			/// </summary>
			ER_D3DERR_DEVICEREMOVED,

			/// <summary>
			/// (D3DERR_DRIVERINTERNALERROR) - Erro interno do motorista. Os aplicativos devem destruir e recriar o dispositivo ao receber esse erro.
			/// </summary>
			ER_D3DERR_DRIVERINTERNALERROR,

			/// <summary>
			/// (D3DERR_DRIVERINVALIDCALL) - Não é usado.
			/// </summary>
			ER_D3DERR_DRIVERINVALIDCALL,

			/// <summary>
			/// (D3DERR_INVALIDDEVICE) - O tipo de dispositivo solicitado não é válido.
			/// </summary>
			ER_D3DERR_INVALIDDEVICE,

			/// <summary>
			/// (D3DERR_MOREDATA) - Há mais dados disponíveis do que o tamanho do buffer especificado pode conter.
			/// </summary>
			ER_D3DERR_MOREDATA,

			/// <summary>
			/// (D3DERR_NOTAVAILABLE) - Este dispositivo não suporta a técnica questionada.
			/// </summary>
			ER_D3DERR_NOTAVAILABLE,

			/// <summary>
			/// (D3DERR_NOTFOUND) - O item solicitado não foi encontrado.
			/// </summary>
			ER_D3DERR_NOTFOUND,

			/// <summary>
			/// (D3DERR_OUTOFVIDEOMEMORY) - Direct3D não tem memória de exibição suficiente para realizar a operação. O dispositivo está usando mais recursos em uma única cena do que pode caber simultaneamente na memória de vídeo.
			/// </summary>
			ER_D3DERR_OUTOFVIDEOMEMORY,

			/// <summary>
			/// (D3DERR_TOOMANYOPERATIONS) - O aplicativo está solicitando mais operações de filtragem de textura do que o dispositivo suporta.
			/// </summary>
			ER_D3DERR_TOOMANYOPERATIONS,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDALPHAARG) - O dispositivo não suporta um argumento especificado de mistura de textura para o canal alfa.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDALPHAARG,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDALPHAOPERATION) - O dispositivo não suporta uma operação especificada de mistura de textura para o canal alfa.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDALPHAOPERATION,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDCOLORARG) - O dispositivo não suporta um argumento especificado de mistura de textura para valores de cores.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDCOLORARG,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDCOLOROPERATION) - O dispositivo não suporta uma operação especificada de mistura de textura para valores de cores.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDCOLOROPERATION,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDFACTORVALUE) - O dispositivo não suporta o valor do fator textura especificado. Não utilizado; fornecido apenas para apoiar motoristas mais velhos.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDFACTORVALUE,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDTEXTUREFILTER) - O dispositivo não suporta o filtro de textura especificado.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDTEXTUREFILTER,

			/// <summary>
			/// (D3DERR_WASSTILLDRAWING) - A operação blit anterior que está transferindo informações para ou para esta superfície está incompleta.
			/// </summary>
			ER_D3DERR_WASSTILLDRAWING,

			/// <summary>
			/// (D3DERR_WRONGTEXTUREFORMAT) - O formato de pixel da superfície da textura não é válido.
			/// </summary>
			ER_D3DERR_WRONGTEXTUREFORMAT,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDOVERLAY) - O dispositivo não suporta sobreposição para o tamanho ou modo de exibição especificado. Direct3D 9Ex apenas no Windows 7.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDOVERLAY,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDOVERLAYFORMAT) - O dispositivo não suporta sobreposição para o formato de superfície especificado. Direct3D 9Ex apenas no Windows 7.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDOVERLAYFORMAT,

			/// <summary>
			/// (D3DERR_CANNOTPROTECTCONTENT) - O conteúdo especificado não pode ser protegido. Direct3D 9Ex apenas no Windows 7.
			/// </summary>
			ER_D3DERR_CANNOTPROTECTCONTENT,

			/// <summary>
			/// (D3DERR_UNSUPPORTEDCRYPTO) - O algoritmo criptográfico especificado não é suportado. Direct3D 9Ex apenas no Windows 7.
			/// </summary>
			ER_D3DERR_UNSUPPORTEDCRYPTO,

			/// <summary>
			/// (D3DERR_PRESENT_STATISTICS_DISJOINT) - As estatísticas atuais não tém sequéncia ordenada. Direct3D 9Ex apenas no Windows 7.
			/// </summary>
			ER_D3DERR_PRESENT_STATISTICS_DISJOINT,






			////////////////////////
			//ENUMS DA API DO DXGI//
			////////////////////////


			// -> Sucessos

			/// <summary>
			/// (DXGI_STATUS_OCCLUDED) - O conteúdo da janela não é visível. Ao receber esse status, um aplicativo pode parar de renderizar e usar DXGI_PRESENT_TEST para determinar quando retomar a renderização.
			/// </summary>
			SS_DXGI_STATUS_OCCLUDED,

			/// <summary>
			/// (DXGI_STATUS_MODE_CHANGED) - O modo de exibição de desktop foi alterado, pode haver conversão de cores/ alongamento. O aplicativo deve chamar ICarenDXGISwapChain::AlterarTamanhoBuffers para coincidir com o novo modo de exibição.
			/// </summary>
			SS_DXGI_STATUS_MODE_CHANGED,

			/// <summary>
			/// (DXGI_STATUS_MODE_CHANGE_IN_PROGRESS) - ICarenDXGISwapChain::ResizeTarget e ICarenDXGISwapChain::SetFullscreenState retornará DXGI_STATUS_MODE_CHANGE_IN_PROGRESS se uma transição de modo fullscreen/windowed estiver ocorrendo 
			/// quando qualquer API for chamada.
			/// </summary>
			SS_DXGI_STATUS_MODE_CHANGE_IN_PROGRESS,

			/// <summary>
			/// (DXGI_STATUS_CLIPPED) - 
			/// </summary>
			SS_DXGI_STATUS_CLIPPED,

			/// <summary>
			/// (DXGI_STATUS_NO_REDIRECTION) - 
			/// </summary>
			SS_DXGI_STATUS_NO_REDIRECTION,

			/// <summary>
			/// (DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE) - 
			/// </summary>
			SS_DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE,

			/// <summary>
			/// (DXGI_STATUS_NO_DESKTOP_ACCESS) - 
			/// </summary>
			SS_DXGI_STATUS_NO_DESKTOP_ACCESS,



			// -> Erros

			/// <summary>
			/// (DXGI_ERROR_WAS_STILL_DRAWING) - A operação de blit de cores anterior que transfere as informações para ou a partir desta superfície é incompleta.
			/// </summary>
			ER_DXGI_ERROR_WAS_STILL_DRAWING,

			/// <summary>
			/// (DXGI_ERROR_INVALID_CALL) - A chamada de método é inválida. Por exemplo, o parâmetro do método não pode ser um ponteiro válido.
			/// </summary>
			ER_DXGI_ERROR_INVALID_CALL,

			/// <summary>
			/// (DXVA2_E_VIDEO_DEVICE_LOCKED) - O dispositivo está bloqueado e Param_AguardarBloqueio é: Falso.
			/// </summary>
			ER_DXVA2_E_VIDEO_DEVICE_LOCKED,

			/// <summary>
			/// (DXVA2_E_NEW_VIDEO_DEVICE) - O identificador do dispositivo é inválido.
			/// </summary>
			ER_DXVA2_E_NEW_VIDEO_DEVICE,

			/// <summary>
			/// (DXVA2_E_NOT_AVAILABLE) - O dispositivo Direct3D não oferece suporte a aceleração de vídeo.
			/// </summary>
			ER_DXVA2_E_NOT_AVAILABLE,

			/// <summary>
			/// (DXVA2_E_NOT_INITIALIZED) - O Gerenciador de dispositivos Direct3D não foi inicializado. O proprietário do dispositivo deve chamar o método (ICarenDirect3DDeviceManager9::ResetDevice).
			/// </summary>
			ER_DXVA2_E_NOT_INITIALIZED,

			/// <summary>
			/// (DXGI_ERROR_NONEXCLUSIVE) - indica que outro objeto do dispositivo está usando o objeto requisitado, então eles não podem ser usados por este dispositivo no momento.
			/// </summary>
			ER_DXGI_ERROR_NONEXCLUSIVE,

			/// <summary>
			/// (DXGI_ERROR_UNSUPPORTED) - A funcionalidade solicitada não é suportada pelo dispositivo ou pelo motorista.
			/// </summary>
			ER_DXGI_ERROR_UNSUPPORTED,

			/// <summary>
			/// (DXGI_ERROR_DEVICE_REMOVED) - A carta de vídeo foi fisicamente removida do sistema, ou uma atualização do motorista para a cartão de vídeo ocorreu. O aplicativo deve destruir e recriar o dispositivo.
			/// </summary>
			ER_DXGI_ERROR_DEVICE_REMOVED,

			/// <summary>
			/// (DXGI_ERROR_DEVICE_HUNG) - O dispositivo do aplicativo falhou devido a comandos mal formados enviados pelo aplicativo. Esta é uma questão de design-tempo que deve ser investigado e corrigido.
			/// </summary>
			ER_DXGI_ERROR_DEVICE_HUNG,

			/// <summary>
			/// (DXGI_ERROR_DEVICE_RESET) - O dispositivo falhou devido a um comando mal formado. Esta é uma questão de tempo de execução; O aplicativo deve destruir e recriar o dispositivo.
			/// </summary>
			ER_DXGI_ERROR_DEVICE_RESET,

			/// <summary>
			/// (DXGI_ERROR_DRIVER_INTERNAL_ERROR) - O motorista encontrou um problema e foi colocado no estado removido do dispositivo.
			/// </summary>
			ER_DXGI_ERROR_DRIVER_INTERNAL_ERROR,

			/// <summary>
			/// (DXGI_ERROR_WAIT_TIMEOUT) - O intervalo de intervalo decorrido antes do próximo quadro de desktop estar disponível.
			/// </summary>
			ER_DXGI_ERROR_WAIT_TIMEOUT,

			/// <summary>
			/// (DXGI_ERROR_SESSION_DISCONNECTED) - A sessão de Serviços de Desktop Remoto está desconectada no momento.
			/// </summary>
			ER_DXGI_ERROR_SESSION_DISCONNECTED,

			/// <summary>
			/// (DXGI_ERROR_SDK_COMPONENT_MISSING) - A operação depende de um componente SDK que está faltando ou incompatível.
			/// </summary>
			ER_DXGI_ERROR_SDK_COMPONENT_MISSING,

			/// <summary>
			/// (DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE) - A saída (monitor) DXGI á qual o conteúdo da cadeia de swap foi restringido agora está desconectada ou alterada.
			/// </summary>
			ER_DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE,

			/// <summary>
			/// (DXGI_ERROR_REMOTE_OUTOFMEMORY) - Reservados
			/// </summary>
			ER_DXGI_ERROR_REMOTE_OUTOFMEMORY,

			/// <summary>
			/// (DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED) - Reservados
			/// </summary>
			ER_DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED,

			/// <summary>
			/// (DXGI_ERROR_NOT_FOUND) - Ao ligar para O ICarenDXGIObject::GetPrivateData,o GUID passou não é reconhecido como um anteriormente passado para ICarenDXGIObject::SetPrivateData ou ICarenDXGIObject::SetPrivateDataInterface. Ao chamar ICarenDXGIFactory::EnumAdapters ou ICarenDXGIAdapter::EnumOutputs, o ordinal enumerado está fora de alcance.
			/// </summary>
			ER_DXGI_ERROR_NOT_FOUND,

			/// <summary>
			/// (DXGI_ERROR_NOT_CURRENTLY_AVAILABLE) - O recurso ou solicitação não está disponível no momento, mas pode ficar disponível mais tarde.
			/// </summary>
			ER_DXGI_ERROR_NOT_CURRENTLY_AVAILABLE,

			/// <summary>
			/// (DXGI_ERROR_NAME_ALREADY_EXISTS) - O nome fornecido de um recurso em uma chamada para ICarenDXGIResource1::CreateSharedHandle já está associado a algum outro recurso.
			/// </summary>
			ER_DXGI_ERROR_NAME_ALREADY_EXISTS,

			/// <summary>
			/// (DXGI_ERROR_MORE_DATA) - O buffer fornecido pelo aplicativo não é grande o suficiente para armazenar os dados solicitados.
			/// </summary>
			ER_DXGI_ERROR_MORE_DATA,

			/// <summary>
			/// (DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE) - O aplicativo tentou adquirir a propriedade exclusiva de uma saída, mas falhou porque algum outro aplicativo (ou dispositivo dentro do aplicativo) já adquiriu a propriedade.
			/// </summary>
			ER_DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE,

			/// <summary>
			/// (DXGI_ERROR_FRAME_STATISTICS_DISJOINT) - Um evento (por exemplo, um ciclo de poder) interrompeu o encontro de estatísticas de apresentação.
			/// </summary>
			ER_DXGI_ERROR_FRAME_STATISTICS_DISJOINT,

			/// <summary>
			/// (DXGI_ERROR_CANNOT_PROTECT_CONTENT) - A DXGI não pode fornecer proteção de conteúdo na cadeia de swaps. Esse erro geralmente é causado por um motorista mais velho ou quando você usa uma cadeia de swaps incompatível com a proteção de conteúdo.
			/// </summary>
			ER_DXGI_ERROR_CANNOT_PROTECT_CONTENT,

			/// <summary>
			/// (DXGI_ERROR_ALREADY_EXISTS) - O elemento desejado já existe. Isso é devolvido por DXGIDeclareAdapterRemovalSupport se não for a primeira vez que a função é chamada.
			/// </summary>
			ER_DXGI_ERROR_ALREADY_EXISTS,

			/// <summary>
			/// (DXGI_ERROR_ACCESS_LOST) - A interface de duplicação de desktop é inválida. A interface de duplicação de desktop normalmente se torna inválida quando um tipo diferente de imagem é exibido na área de trabalho.
			/// </summary>
			ER_DXGI_ERROR_ACCESS_LOST,

			/// <summary>
			/// (DXGI_ERROR_ACCESS_DENIED) - Vocé tentou usar um recurso para o qual você não tinha os privilégios de acesso necessários. Esse erro geralmente é causado quando você escreve para um recurso compartilhado com acesso apenas para leitura.
			/// </summary>
			ER_DXGI_ERROR_ACCESS_DENIED,

			/// <summary>
			/// (DXGI_STATUS_DDA_WAS_STILL_DRAWING) -
			/// /// </summary>
			ER_DXGI_STATUS_DDA_WAS_STILL_DRAWING,

			/// <summary>
			/// (DXGI_ERROR_NOT_CURRENT) - 
			/// </summary>
			ER_DXGI_ERROR_NOT_CURRENT,

			/// <summary>
			/// (DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY) - 
			/// </summary>
			ER_DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY,

			/// <summary>
			/// (DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION) - 
			/// </summary>
			ER_DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION,

			/// <summary>
			/// (DXGI_ERROR_NON_COMPOSITED_UI) - 
			/// </summary>
			ER_DXGI_ERROR_NON_COMPOSITED_UI,

			/// <summary>
			/// (DXGI_ERROR_CACHE_CORRUPT) - 
			/// </summary>
			ER_DXGI_ERROR_CACHE_CORRUPT,

			/// <summary>
			/// (DXGI_ERROR_CACHE_FULL) - 
			/// </summary>
			ER_DXGI_ERROR_CACHE_FULL,

			/// <summary>
			/// (DXGI_ERROR_CACHE_HASH_COLLISION) - 
			/// </summary>
			ER_DXGI_ERROR_CACHE_HASH_COLLISION,

			/// <summary>
			/// (DXGI_DDI_ERR_WASSTILLDRAWING) - 
			/// </summary>
			ER_DXGI_DDI_ERR_WASSTILLDRAWING,

			/// <summary>
			/// (DXGI_DDI_ERR_UNSUPPORTED) - 
			/// </summary>
			ER_DXGI_DDI_ERR_UNSUPPORTED,

			/// <summary>
			/// (DXGI_DDI_ERR_NONEXCLUSIVE) - 
			/// </summary>
			ER_DXGI_DDI_ERR_NONEXCLUSIVE,







			/////////////////////////////
			//ENUMS DA API DO DIRECT 2D//
			/////////////////////////////


			// -> Erros

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_WRONG_STATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_NOT_INITIALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_UNSUPPORTED_OPERATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_SCANNER_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_SCREEN_ACCESS_DENIED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_DISPLAY_STATE_INVALID,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_ZERO_VECTOR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INTERNAL_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_CALL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_NO_HARDWARE_DEVICE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_RECREATE_TARGET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_TOO_MANY_SHADER_ELEMENTS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_SHADER_COMPILE_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_MAX_TEXTURE_SIZE_EXCEEDED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_UNSUPPORTED_VERSION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_BAD_NUMBER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_WRONG_FACTORY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_LAYER_ALREADY_IN_USE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_POP_CALL_DID_NOT_MATCH_PUSH,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_WRONG_RESOURCE_DOMAIN,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_PUSH_POP_UNBALANCED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INCOMPATIBLE_BRUSH_TYPES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_WIN32_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_TARGET_NOT_GDI_COMPATIBLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_TEXT_EFFECT_IS_WRONG_TYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_TEXT_RENDERER_NOT_RELEASED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_EXCEEDS_MAX_BITMAP_SIZE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_GRAPH_CONFIGURATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_INTERNAL_GRAPH_CONFIGURATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_CYCLIC_GRAPH,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_BITMAP_CANNOT_DRAW,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_OUTSTANDING_BITMAP_REFERENCES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_ORIGINAL_TARGET_NOT_BOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_TARGET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_BITMAP_BOUND_AS_TARGET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INTERMEDIATE_TOO_LARGE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_EFFECT_IS_NOT_REGISTERED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_PROPERTY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_NO_SUBPROPERTIES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_PRINT_JOB_CLOSED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_PRINT_FORMAT_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_TOO_MANY_TRANSFORM_INPUTS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_D2DERR_INVALID_GLYPH_IMAGE,







			////////////////////////////////
			//ENUMS DA API DO DIRECT 3D 11//
			////////////////////////////////


			/// <summary>
			/// (D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD) - A primeira chamada para ID3D11DeviceContext::Map após ou ID3D11Device::CreateDeferredContext ou ID3D11DeviceContext::FinishCommandList por recurso não foi D3D11_MAP_WRITE_ DESCARTE.
			/// </summary>
			ER_D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD,

			/// <summary>
			/// (D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS) - Existem também muitos casos exclusivos de um determinado tipo de objeto de exibição.
			/// </summary>
			ER_D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS,

			/// <summary>
			/// (D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS) - Existem também muitos casos exclusivos de um determinado tipo de objeto de estado.
			/// </summary>
			ER_D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS,

			/// <summary>
			/// (D3D11_ERROR_FILE_NOT_FOUND) - O arquivo não foi encontrado.
			/// </summary>
			ER_D3D11_ERROR_FILE_NOT_FOUND,






			/////////////////////////////////////////////////
			//ENUMS DAS API`S DO MICROSOFT MEDIA FOUNDATION//
			/////////////////////////////////////////////////


			// -> Sucessos

			/// <summary>
			/// (MF_S_MULTIPLE_BEGIN) - Há uma solicitação pendente com o mesmo ponteiro de retorno de chamada e objeto de estado.
			/// </summary>
			SS_MF_S_MULTIPLE_BEGIN,

			/// <summary>
			///  (MF_S_ASF_PARSEINPROGRESS) - 
			/// </summary>
			SS_MF_S_ASF_PARSEINPROGRESS,

			/// <summary>
			/// (MF_I_MANUAL_PROXY) - 
			/// </summary>
			SS_MF_I_MANUAL_PROXY,

			/// <summary>
			/// (MF_S_PROTECTION_NOT_REQUIRED) - 
			/// </summary>
			SS_MF_S_PROTECTION_NOT_REQUIRED,

			/// <summary>
			/// (MF_S_WAIT_FOR_POLICY_SET) - 
			/// </summary>
			SS_MF_S_WAIT_FOR_POLICY_SET,

			/// <summary>
			/// (MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT) - 
			/// </summary>
			SS_MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT,

			/// <summary>
			/// () - 
			/// </summary>
			SS_MF_S_SINK_NOT_FINALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			SS_MF_S_PE_TRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			SS_MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT,

			/// <summary>
			/// () - 
			/// </summary>
			SS_MF_S_SEQUENCER_CONTEXT_CANCELED,

			/// <summary>
			/// () - 
			/// </summary>
			SS_MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM,		


			// -> Erros

			/// <summary>
			/// (MF_E_NOT_FOUND) - Objeto não está disponivel ou não foi encontrado.
			/// </summary>
			ER_MF_E_NOT_FOUND,

			/// <summary>
			/// (MF_E_TOPO_INVALID_TIME_ATTRIBUTES) - A topologia tem valores inválidos para um ou mais dos seguintes atributos:
			///	MF_TOPONODE_MEDIASTART >
			///	MF_TOPONODE_MEDIASTOP >
			///	MF_TOPOLOGY_PROJECTSTART >
			///	MF_TOPOLOGY_PROJECTSTOP
			/// </summary>
			ER_MF_E_TOPO_INVALID_TIME_ATTRIBUTES,

			/// <summary>
			/// (MF_E_SESSION_PAUSEWHILESTOPPED) - A sessão de mídia não pode pausar enquanto parou.
			/// </summary>
			ER_MF_E_SESSION_PAUSEWHILESTOPPED,

			/// <summary>
			/// (MF_E_NOTACCEPTING) - O receptor atualmente não está aceitando mais entrada
			/// </summary>
			ER_MF_E_NOTACCEPTING,

			/// <summary>
			/// (MF_E_INVALIDREQUEST) - Uma chamada para um método não podia ser realizada devido a uma outra operação ou porque um componente não estava pronto.
			/// Esse erro pode ser gerado por varios motivos, consulte o método para entender o porque desse retorno.
			/// </summary>
			ER_MF_E_INVALIDREQUEST,

			/// <summary>
			/// (MF_E_SAMPLEALLOCATOR_EMPTY) - O alocador de amostra está vazio no momento, devido a solicitações pendentes.
			/// </summary>
			ER_MF_E_SAMPLEALLOCATOR_EMPTY,

			/// <summary>
			/// (MF_E_UNSUPPORTED_RATE) - O objeto não oferece suporte a taxa especificada.
			/// </summary>
			ER_MF_E_UNSUPPORTED_RATE,

			/// <summary>
			/// (MF_E_UNSUPPORTED_RATE_TRANSITION) - O objeto não pode ser alterado para a nova taxa enquanto estiver no estado de execução. .
			/// </summary>
			ER_MF_E_UNSUPPORTED_RATE_TRANSITION,

			/// <summary>
			/// (MF_E_REVERSE_UNSUPPORTED) - O objeto não oferece suporte á reprodução reversa.
			/// </summary>
			ER_MF_E_REVERSE_UNSUPPORTED,

			/// <summary>
			/// (MF_E_THINNING_UNSUPPORTED) - O objeto não suporta desbaste.
			/// </summary>
			ER_MF_E_THINNING_UNSUPPORTEDE,

			/// <summary>
			/// (MF_E_INVALIDINDEX) - O index informado não é valido ou não existe.
			/// </summary>
			ER_MF_E_INVALIDINDEX,

			/// <summary>
			///(MF_E_UNSUPPORTED_SERVICE) - O serviço requisitado não é suportado.
			/// </summary>
			ER_MF_E_UNSUPPORTED_SERVICE,

			/// <summary>
			/// (MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED) - Um ou mais nós de saída contém ponteiros IMFActivate . O chamador deve vincular os nós de saída para pias de mídia.
			/// </summary>
			ER_MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED,

			/// <summary>
			/// (MF_E_MEDIA_SOURCE_WRONGSTATE) - A origem de mídia está parada.
			/// </summary>
			ER_MF_E_MEDIA_SOURCE_WRONGSTATE,

			/// <summary>
			/// (MF_E_END_OF_STREAM) - O fim do fluxo foi alcançado.
			/// </summary>
			ER_MF_E_END_OF_STREAM,

			/// <summary>
			/// (MF_E_UNSUPPORTED_SCHEME) - O esquema de URL não é suportado.
			/// </summary>
			ER_MF_E_UNSUPPORTED_SCHEME,

			/// <summary>
			/// (MF_E_BYTESTREAM_NOT_SEEKABLE) - O fluxo de bytes não suporta busca.
			/// </summary>
			ER_MF_E_BYTESTREAM_NOT_SEEKABLE,

			/// <summary>
			/// (MF_E_UNSUPPORTED_BYTESTREAM_TYPE) - O fluxo de bytes não é suportado.
			/// </summary>
			ER_MF_E_UNSUPPORTED_BYTESTREAM_TYPE,

			/// <summary>
			/// (MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS) - O parâmetro Param_Flags contém sinalizadores mutuamente exclusivas.
			/// </summary>
			ER_MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS,

			/// <summary>
			/// (MF_E_ASF_OUTOFRANGE) - A posição inicial é após o final da apresentação (fonte de mídia ASF).
			/// </summary>
			ER_MF_E_ASF_OUTOFRANGE,

			/// <summary>
			/// (MF_E_HW_MFT_FAILED_START_STREAMING) - Um dispositivo de hardware não pôde iniciar a transmissão. Este código de erro pode ser retornado por uma fonte de mídia que representa 
			/// um dispositivo de hardware, como uma câmera. 
			/// </summary>
			ER_MF_E_HW_MFT_FAILED_START_STREAMING,

			/// <summary>
			/// (MF_E_UNSUPPORTED_TIME_FORMAT) - A origem de mídia não suporta o formato de hora especificado.
			/// </summary>
			ER_MF_E_UNSUPPORTED_TIME_FORMAT,

			/// <summary>
			/// (MF_E_INVALID_STATE_TRANSITION) - Transição de estado inválido. A fonte de mídia deve ser no estado começou.
			/// </summary>
			ER_MF_E_INVALID_STATE_TRANSITION,

			/// <summary>
			/// (MF_E_INVALID_WORKQUEUE) - Fila de trabalho inválida. Para mais informações, consulte a documentação do método IMFAsyncCallback::GetParameters que é representado
			/// pela interface ICarenMFAsyncCallback.
			/// </summary>
			ER_MF_E_INVALID_WORKQUEUE,

			/// <summary>
			/// (MF_E_NO_EVENTS_AVAILABLE) - Não há eventos na fila.
			/// </summary>
			ER_MF_E_NO_EVENTS_AVAILABLE,

			/// <summary>
			/// (MF_E_MULTIPLE_SUBSCRIBERS) - Há uma solicitação pendente com um ponteiro de retorno de chamada diferente.
			/// </summary>
			ER_MF_E_MULTIPLE_SUBSCRIBERS,

			/// <summary>
			/// (MF_E_MULTIPLE_BEGIN) - Há uma solicitação pendente com o mesmo ponteiro de retorno de chamada e um objeto de estado diferente.
			/// </summary>
			ER_MF_E_MULTIPLE_BEGIN,

			/// <summary>
			/// (MF_E_STREAMSINK_REMOVED) - Esse fluxo foi removido do (Coletor de Mídia) e não é mais válido.
			/// </summary>
			ER_MF_E_STREAMSINK_REMOVED,

			/// <summary>
			/// (MF_E_CLOCK_NOT_SIMPLE) - A fonte de tempo não tem uma frequéncia de 10 MHz. 
			/// </summary>
			ER_MF_E_CLOCK_NOT_SIMPLE,

			/// <summary>
			/// (MF_E_NO_CLOCK) - Nenhum relógio foi ajustado. Para definir o relógio de apresentação, chame o método (DefinirRelogioApresentação).
			/// </summary>
			ER_MF_E_NO_CLOCK,

			/// <summary>
			/// (MF_E_CLOCK_NO_TIME_SOURCE) - O relógio de apresentação não tem uma (Origem de Tempo). Chame o método (ICarenRelogioApresentação.SetTimeSource)
			/// para definir um fonte de tempo para o Relógio atual.
			/// </summary>
			ER_MF_E_CLOCK_NO_TIME_SOURCE,

			/// <summary>
			/// (MF_E_CLOCK_STATE_ALREADY_SET) - O relógio já está no estado solicitado
			/// </summary>
			ER_MF_E_CLOCK_STATE_ALREADY_SET,

			/// <summary>
			/// (MF_E_SHUTDOWN) - A função não pode ser executada porque uma chamda para (Shutdown) no componente foi realizada.
			/// </summary>
			ER_MF_E_SHUTDOWN,

			/// <summary>
			/// (MF_E_INVALIDSTREAMNUMBER) - O Id informado é invalido ou está além dos limites possiveis.
			/// </summary>
			ER_MF_E_INVALIDSTREAMNUMBER,

			/// <summary>
			/// (MF_E_TRANSFORM_INPUT_REMAINING) - A transformação tem buffers de entrada não processados para o fluxo especificado.
			/// </summary>
			ER_MF_E_TRANSFORM_INPUT_REMAINING,

			/// <summary>
			/// (MF_E_NO_MORE_TYPES) - O indice informado já está fora de alcance.
			/// </summary>
			ER_MF_E_NO_MORE_TYPES,

			/// <summary>
			/// (MF_E_TRANSFORM_TYPE_NOT_SET) - Um tipo válido não foi definido para este fluxo ou um fluxo do qual depende
			/// </summary>
			ER_MF_E_TRANSFORM_TYPE_NOT_SET,

			/// <summary>
			/// (MF_E_TRANSFORM_NEED_MORE_INPUT) - A transformação não pode produzir saída até obter mais amostras de entrada.
			/// </summary>
			ER_MF_E_TRANSFORM_NEED_MORE_INPUT,

			/// <summary>
			/// (MF_E_TRANSFORM_STREAM_CHANGE) - Ocorreu uma alteração no fluxo.A saída não pode ser produzida até que os fluxos tenham sido renegociados
			/// </summary>
			ER_MF_E_TRANSFORM_STREAM_CHANGE,

			/// <summary>
			/// (MF_E_STREAMSINK_EXISTS) - Já existe um Stream Sink como o mesmo identificador fornecido.
			/// </summary>
			ER_MF_E_STREAMSINK_EXISTS,

			/// <summary>
			/// (MF_E_STREAMSINKS_FIXED) - O coletor de mídia(MidiaSink), possui coletores de fluxos(StreamSink) fixos. Portanto, não é possivel remover ou adicionar um novo coletor de fluxo. 
			/// </summary>
			ER_MF_E_STREAMSINKS_FIXED,

			/// <summary>
			/// (MF_E_NOT_INITIALIZED) - Indica que a houve falha porque um componente não foi inicializado ou não foi definido os seus valores.
			/// </summary>
			ER_MF_E_NOT_INITIALIZED,

			/// <summary>
			/// (MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING) - A transformação não pode aceitar alterações de tipo de mídia no meio do processamento.
			/// </summary>
			ER_MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING,

			/// <summary>
			/// (MF_E_INVALIDTYPE) - O tipo do valor não é compativel com o esperado.ER_MF_TIPO_INVALIDO
			/// </summary>
			ER_MF_E_INVALIDTYPE,

			/// <summary>
			/// (MF_E_ATTRIBUTENOTFOUND) - A chave especificada para o atributo não foi encontrada.
			/// </summary>
			ER_MF_E_ATTRIBUTENOTFOUND,

			/// <summary>
			/// (MF_E_BUFFERTOOSMALL) - O Buffer é muito pequeno.
			/// </summary>
			ER_MF_E_BUFFERTOOSMALL,

			/// <summary>
			/// (MF_E_TOPO_CODEC_NOT_FOUND) - Não foi possível localizar um (Decodificador) para o tipo de fluxo nativo.
			/// </summary>
			ER_MF_E_TOPO_CODEC_NOT_FOUND,

			/// <summary>
			/// (MF_E_INVALIDMEDIATYPE) - Pelo menos um decodificador foi encontrado para o tipo de fluxo nativo, mas o tipo especificado por ICarenMFMediaType foi rejeitado.
			/// </summary>
			ER_MF_E_INVALIDMEDIATYPE,

			/// <summary>
			/// (MF_E_NO_SAMPLE_DURATION) - A amostra de mídia não tem uma duração especificada.
			/// </summary>
			ER_MF_E_NO_SAMPLE_DURATION,

			/// <summary>
			/// (MF_E_NO_SAMPLE_TIMESTAMP) - A amostra de mídia não tem um tempo de apresentação.
			/// </summary>
			ER_MF_E_NO_SAMPLE_TIMESTAMP,

			/// <summary>
			/// (MF_E_INVALID_TIMESTAMP) - A amostra de mídia contém um TimeSpan invalido.
			/// </summary>
			ER_MF_E_INVALID_TIMESTAMP,

			/// <summary>
			/// (MF_E_UNSUPPORTED_D3D_TYPE) - O tipo de entrada não é suportado pelo dispositivo D3D.
			/// </summary>
			ER_MF_E_UNSUPPORTED_D3D_TYPE,

			/// <summary>
			/// (MF_E_DXGI_VIDEO_DEVICE_LOCKED) - O dispositivo está bloqueado e Param_AguardarBloqueio é: Falso.
			/// </summary>
			ER_MF_E_DXGI_VIDEO_DEVICE_LOCKED,

			/// <summary>
			/// (MF_E_DXGI_NEW_VIDEO_DEVICE) - O identificador do dispositivo é inválido.
			/// </summary>
			ER_MF_E_DXGI_NEW_VIDEO_DEVICE,

			/// <summary>
			/// (MF_E_DXGI_DEVICE_NOT_INITIALIZED) - O Gerenciador de dispositivo DXGI não foi inicializado. O proprietário do aparelho deve chamar o método (ICarenMFDXGIDeviceManager::ResetDevice).
			/// </summary>
			ER_MF_E_DXGI_DEVICE_NOT_INITIALIZED,

			/// <summary>
			/// (MF_E_LICENSE_INCORRECT_RIGHTS) - O conteúdo é protegido e a licença não permite capturar a imagem. 
			/// </summary>
			ER_MF_E_LICENSE_INCORRECT_RIGHTS,

			/// <summary>
			/// (MF_E_PLATFORM_NOT_INITIALIZED) - 
			/// </summary>
			ER_MF_E_PLATFORM_NOT_INITIALIZED,

			/// <summary>
			/// (MF_E_UNSUPPORTED_REPRESENTATION) - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_REPRESENTATION,

			/// <summary>
			/// (MF_E_UNEXPECTED) - 
			/// </summary>
			ER_MF_E_UNEXPECTED,

			/// <summary>
			/// (MF_E_INVALIDNAME) - 
			/// </summary>
			ER_MF_E_INVALIDNAME,

			/// <summary>
			/// (MF_E_INVALID_FILE_FORMAT) - 
			/// </summary>
			ER_MF_E_INVALID_FILE_FORMAT,

			/// <summary>
			/// (MF_E_INVALID_STREAM_DATA) - 
			/// </summary>
			ER_MF_E_INVALID_STREAM_DATA,

			/// <summary>
			/// (MF_E_RT_UNAVAILABLE) - 
			/// </summary>
			ER_MF_E_RT_UNAVAILABLE,

			/// <summary>
			/// (MF_E_THINNING_UNSUPPORTED) - 
			/// </summary>
			ER_MF_E_THINNING_UNSUPPORTED,

			/// <summary>
			/// (MF_E_RATE_CHANGE_PREEMPTED) - 
			/// </summary>
			ER_MF_E_RATE_CHANGE_PREEMPTED,

			/// <summary>
			/// (MF_E_NOT_AVAILABLE) - 
			/// </summary>
			ER_MF_E_NOT_AVAILABLE,

			/// <summary>
			/// (MF_E_TIMER_ORPHANED) - 
			/// </summary>
			ER_MF_E_TIMER_ORPHANED,

			/// <summary>
			/// (MF_E_STATE_TRANSITION_PENDING) - 
			/// </summary>
			ER_MF_E_STATE_TRANSITION_PENDING,

			/// <summary>
			/// (MF_E_UNSUPPORTED_STATE_TRANSITION) - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_STATE_TRANSITION,

			/// <summary>
			/// (MF_E_UNRECOVERABLE_ERROR_OCCURRED) - 
			/// </summary>
			ER_MF_E_UNRECOVERABLE_ERROR_OCCURRED,

			/// <summary>
			/// (MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS) - 
			/// </summary>
			ER_MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS,

			/// <summary>
			/// (MF_E_SAMPLE_NOT_WRITABLE) - 
			/// </summary>
			ER_MF_E_SAMPLE_NOT_WRITABLE,

			/// <summary>
			/// (MF_E_INVALID_KEY) - 
			/// </summary>
			ER_MF_E_INVALID_KEY,

			/// <summary>
			/// (MF_E_BAD_STARTUP_VERSION) - 
			/// </summary>
			ER_MF_E_BAD_STARTUP_VERSION,

			/// <summary>
			/// (MF_E_UNSUPPORTED_CAPTION) - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_CAPTION,

			/// <summary>
			/// (MF_E_INVALID_POSITION) - 
			/// </summary>
			ER_MF_E_INVALID_POSITION,

			/// <summary>
			/// (MF_E_PROPERTY_TYPE_NOT_ALLOWED) - 
			/// </summary>
			ER_MF_E_PROPERTY_TYPE_NOT_ALLOWED,

			/// <summary>
			/// (MF_E_PROPERTY_TYPE_NOT_SUPPORTED) - 
			/// </summary>
			ER_MF_E_PROPERTY_TYPE_NOT_SUPPORTED,

			/// <summary>
			/// (MF_E_PROPERTY_EMPTY) - 
			/// </summary>
			ER_MF_E_PROPERTY_EMPTY,

			/// <summary>
			/// (MF_E_PROPERTY_NOT_EMPTY) - 
			/// </summary>
			ER_MF_E_PROPERTY_NOT_EMPTY,

			/// <summary>
			/// (MF_E_PROPERTY_VECTOR_NOT_ALLOWED) - 
			/// </summary>
			ER_MF_E_PROPERTY_VECTOR_NOT_ALLOWED,

			/// <summary>
			/// (MF_E_PROPERTY_VECTOR_REQUIRED) - 
			/// </summary>
			ER_MF_E_PROPERTY_VECTOR_REQUIRED,

			/// <summary>
			/// (MF_E_OPERATION_CANCELLED) - 
			/// </summary>
			ER_MF_E_OPERATION_CANCELLED,

			/// <summary>
			/// (MF_E_DISABLED_IN_SAFEMODE) - 
			/// </summary>
			ER_MF_E_DISABLED_IN_SAFEMODE,

			/// <summary>
			/// (MF_E_CANNOT_PARSE_BYTESTREAM) - 
			/// </summary>
			ER_MF_E_CANNOT_PARSE_BYTESTREAM,

			/// <summary>
			/// (MF_E_MEDIAPROC_WRONGSTATE) - 
			/// </summary>
			ER_MF_E_MEDIAPROC_WRONGSTATE,

			/// <summary>
			/// (MF_E_RT_THROUGHPUT_NOT_AVAILABLE) - 
			/// </summary>
			ER_MF_E_RT_THROUGHPUT_NOT_AVAILABLE,

			/// <summary>
			/// (MF_E_RT_TOO_MANY_CLASSES) - 
			/// </summary>
			ER_MF_E_RT_TOO_MANY_CLASSES,

			/// <summary>
			/// (MF_E_RT_WOULDBLOCK) - 
			/// </summary>
			ER_MF_E_RT_WOULDBLOCK,

			/// <summary>
			/// (MF_E_NO_BITPUMP) - 
			/// </summary>
			ER_MF_E_NO_BITPUMP,

			/// <summary>
			/// (MF_E_RT_OUTOFMEMORY) - 
			/// </summary>
			ER_MF_E_RT_OUTOFMEMORY,

			/// <summary>
			/// (MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED) - 
			/// </summary>
			ER_MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED,

			/// <summary>
			/// (MF_E_INSUFFICIENT_BUFFER) - 
			/// </summary>
			ER_MF_E_INSUFFICIENT_BUFFER,

			/// <summary>
			/// (MF_E_CANNOT_CREATE_SINK) - 
			/// </summary>
			ER_MF_E_CANNOT_CREATE_SINK,

			/// <summary>
			/// (MF_E_BYTESTREAM_UNKNOWN_LENGTH) - 
			/// </summary>
			ER_MF_E_BYTESTREAM_UNKNOWN_LENGTH,

			/// <summary>
			/// (MF_S_ACTIVATE_REPLACED) - 
			/// </summary>
			ER_MF_S_ACTIVATE_REPLACED,

			/// <summary>
			/// (MF_E_FORMAT_CHANGE_NOT_SUPPORTED) - 
			/// </summary>
			ER_MF_E_FORMAT_CHANGE_NOT_SUPPORTED,

			/// <summary>
			/// (MF_E_DRM_UNSUPPORTED) - 
			/// </summary>
			ER_MF_E_DRM_UNSUPPORTED,

			/// <summary>
			/// (MF_E_UNAUTHORIZED) - 
			/// </summary>
			ER_MF_E_UNAUTHORIZED,

			/// <summary>
			/// (MF_E_OUT_OF_RANGE) - 
			/// </summary>
			ER_MF_E_OUT_OF_RANGE,

			/// <summary>
			/// (MF_E_INVALID_CODEC_MERIT) - 
			/// </summary>
			ER_MF_E_INVALID_CODEC_MERIT,

			/// <summary>
			/// (MF_E_OPERATION_IN_PROGRESS) - 
			/// </summary>
			ER_MF_E_OPERATION_IN_PROGRESS,

			/// <summary>
			/// (MF_E_HARDWARE_DRM_UNSUPPORTED) - 
			/// </summary>
			ER_MF_E_HARDWARE_DRM_UNSUPPORTED,

			/// <summary>
			/// (MF_E_DURATION_TOO_LONG) - 
			/// </summary>
			ER_MF_E_DURATION_TOO_LONG,

			/// <summary>
			/// (MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL) - 
			/// </summary>
			ER_MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL,

			/// <summary>
			/// (MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL) - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_PARSINGINCOMPLETE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_MISSINGDATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_INVALIDDATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_OPAQUEPACKET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_NOINDEX,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_INDEXNOTLOADED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_TOO_MANY_PAYLOADS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_UNSUPPORTED_STREAM_TYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_DROPPED_PACKET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MP3_NOTFOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MP3_OUTOFDATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MP3_NOTMP3,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MP3_NOTSUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_DURATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INVALID_FORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PROPERTY_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PROPERTY_READ_ONLY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PROPERTY_NOT_ALLOWED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_SOURCE_NOT_STARTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_FORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MP3_BAD_CRC,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NOT_PROTECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CANNOT_FIND_KEYFRAME_SAMPLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_CHARACTERISTICS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_AUDIO_RECORDING_DEVICE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_RECORDING_DEVICE_IN_USE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NETWORK_RESOURCE_FAILURE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_WRITE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_READ,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_REQUIRE_NETWORK,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_REQUIRE_ASYNC,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_BWLEVEL_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_STREAMGROUPS_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_MANUALSS_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_CACHESTREAM_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_REQUIRE_INPUT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_REDIRECT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_REDIRECT_TO_PROXY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_TOO_MANY_REDIRECTS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_TIMEOUT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_CLIENT_CLOSE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_BAD_CONTROL_DATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INCOMPATIBLE_SERVER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_UNSAFE_URL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_CACHE_NO_DATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_EOL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_BAD_REQUEST,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INTERNAL_SERVER_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_SESSION_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_NOCONNECTION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_CONNECTION_FAILURE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INCOMPATIBLE_PUSHSERVER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_SERVER_ACCESSDENIED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_PROXY_ACCESSDENIED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_CANNOTCONNECT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INVALID_PUSH_TEMPLATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_INVALID_PUSH_PUBLISHING_POINT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_BUSY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_RESOURCE_GONE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_ERROR_FROM_PROXY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_PROXY_TIMEOUT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_SERVER_UNAVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_TOO_MUCH_DATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_SESSION_INVALID,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_OFFLINE_MODE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_UDP_BLOCKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_UNSUPPORTED_CONFIGURATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_PROTOCOL_DISABLED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NET_COMPANION_DRIVER_DISCONNECT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ALREADY_INITIALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_BANDWIDTH_OVERRUN,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_LATE_SAMPLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_FLUSH_NEEDED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INVALID_PROFILE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INDEX_NOT_COMMITTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_INDEX,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CANNOT_INDEX_IN_PLACE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MISSING_ASF_LEAKYBUCKET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INVALID_ASF_STREAMID,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_STREAMSINKS_OUT_OF_SYNC,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SAMPLEALLOCATOR_CANCELED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SINK_ALREADYSTOPPED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ASF_FILESINK_BITRATE_UNKNOWN,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SINK_NO_STREAMS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_METADATA_TOO_LONG,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SINK_NO_SAMPLES_PROCESSED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SINK_HEADERS_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_REN_NO_PROCAMP_HW,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_REN_NO_DEINTERLACE_HW,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_REN_COPYPROT_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_REN_SURFACE_NOT_SHARED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_VIDEO_DEVICE_LOCKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NEW_VIDEO_DEVICE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_VIDEO_SAMPLE_AVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_AUDIO_PLAYBACK_DEVICE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_SERVICE_NOT_RUNNING,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_BUFFER_SIZE_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_INVALID_OPTIONAL_NODE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_CANNOT_FIND_DECRYPTOR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_CANNOT_CONNECT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_UNSUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_LOOPS_IN_TOPOLOGY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_MISSING_STREAM_DESCRIPTOR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPO_MISSING_SOURCE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_SOURCE_IN_CACHE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROFILE_MISSING,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROFILE_TRUNCATED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_ASYNC_LOCKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_LICENSE_OUTOFDATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_LICENSE_REQUIRED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_DRM_HARDWARE_INCONSISTENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_CONTENT_PROTECTION_MANAGER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_LICENSE_RESTORE_NO_RIGHTS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_BACKUP_RESTRICTED_LICENSE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_COMPONENT_REVOKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRUST_DISABLED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_NO_ACTION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_ACTION_ALREADY_SET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_ACTION_MISMATCH,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_WMDRMOTA_INVALID_POLICY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_POLICY_UNSUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_OPL_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TOPOLOGY_VERIFICATION_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_SIGNATURE_VERIFICATION_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_DEBUGGING_NOT_ALLOWED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CODE_EXPIRED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_VERSION_TOO_LOW,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_RENEWAL_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_KERNEL_UNTRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PEAUTH_UNTRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NON_PE_PROCESS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_REBOOT_REQUIRED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_INVALID_FORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_UNRECOGNIZED_FORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ALL_PROCESS_RESTART_REQUIRED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PROCESS_RESTART_REQUIRED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_USERMODE_UNTRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PEAUTH_SESSION_NOT_STARTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PEAUTH_PUBLICKEY_REVOKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_GRL_ABSENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_S_PE_TRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PE_UNTRUSTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PEAUTH_NOT_STARTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INCOMPATIBLE_SAMPLE_PROTECTION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_PE_SESSIONS_MAXED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_UNSUPPORTED_ACTION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_BAD_OPL_STRUCTURE_FORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_PMP_HOST,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_OPL_DATA_NOT_INITIALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INVALID_AKE_CHANNEL_PARAMETERS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_DRM_MIGRATION_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_HDCP_AUTHENTICATION_FAILURE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_HDCP_LINK_FAILURE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CLOCK_INVALID_CONTINUITY_KEY,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_S_CLOCK_STOPPED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_MORE_DROP_MODES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_MORE_QUALITY_LEVELS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_DROPTIME_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_QUALITYKNOB_WAIT_LONGER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_QM_INVALIDSTATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSCODE_NO_CONTAINERTYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSCODE_NO_MATCHING_ENCODER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TRANSCODE_INVALID_PROFILE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ALLOCATOR_NOT_INITIALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ALLOCATOR_NOT_COMMITED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_ALLOCATOR_ALREADY_COMMITED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_STREAM_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_INVALID_STREAM_STATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_HW_STREAM_NOT_CONNECTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_NO_CAPTURE_DEVICES_AVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SINK_OUTPUT_NOT_SET,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SINK_MIRROR_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SINK_ROTATE_ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_ENGINE_INVALID_OP,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TIMELINECONTROLLER_NOT_ALLOWED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_TIMELINECONTROLLER_CANNOT_ATTACH,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID,

			/// <summary>
			/// (MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT) - 
			/// </summary>
			ER_MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT,




			///////////////////////////////////////////
			//ENUMS DA WINDOWS IMAGING COMPONENT(WIC)//
			///////////////////////////////////////////


			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_WRONGSTATE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_VALUEOUTOFRANGE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_UNKNOWNIMAGEFORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_NOTINITIALIZED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_ALREADYLOCKED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_PROPERTYNOTFOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_PROPERTYNOTSUPPORTED,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_PROPERTYSIZE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_CODECPRESENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_CODECNOTHUMBNAIL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_PALETTEUNAVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_CODECTOOMANYSCANLINES,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INTERNALERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_COMPONENTNOTFOUND,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_IMAGESIZEOUTOFRANGE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_TOOMUCHMETADATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_BADIMAGE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_BADHEADER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_FRAMEMISSING,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_BADMETADATAHEADER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_BADSTREAMDATA,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_STREAMWRITE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_STREAMREAD,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_STREAMNOTAVAILABLE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_UNSUPPORTEDOPERATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INVALIDREGISTRATION,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_COMPONENTINITIALIZEFAILURE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INSUFFICIENTBUFFER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_DUPLICATEMETADATAPRESENT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_UNEXPECTEDSIZE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INVALIDQUERYREQUEST,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_UNEXPECTEDMETADATATYPE,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INVALIDQUERYCHARACTER,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_WIN32ERROR,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INVALIDPROGRESSIVELEVEL,

			/// <summary>
			/// () - 
			/// </summary>
			ER_WINCODEC_ERR_INVALIDJPEGSCANINDEX,

			/// <summary>
			/// (WINCODEC_ERR_ABORTED = E_ABORT) - 
			/// </summary>
			ER_WINCODEC_ERR_ABORTED = ER_E_ABORT
		};

		/// <summary>
		/// Classe responsável por verificar o status de uma operação nativa e converter os valores entre HRESULT e ResultCode.
		/// </summary>
		class ResultCodeState
		{
			//Contrução da classe.
		public:
			ResultCodeState() {}
			~ResultCodeState() {}

			//Métodos.
		public:
			/// <summary>
			/// Método responsável por verificar o status geral de um HRESULT e converter o valor para um (ResultCode) de destino.
			/// </summary>
			/// <param name="Param_Resultado">O código HRESULT a ser verificar e traduzido.</param>
			/// <param name="Param_Out_Status">A tradução do código em (Param_Resultado). Se não for encontrado um ResultCode que represente o HRESULT, o valor retornado será ER_FAIL.</param>
			/// <returns></returns>
			bool VerificarStatus(HRESULT Param_Resultado, [Out] ResultCode% Param_Out_Status)
			{
				//Variaveis
				bool Resultado = false; //Variavel que retorna o resultado geral do método.
				ResultCode OutStatus = ResultCode::ER_FAIL; //Variavel que retorna um (ResultCode) do código HRESULT fornecido em (Param_Resultado).


				//----VERIFICA DE IMEDIATO SE NAO É UM CÓDIGO DE SUCESSO.

				//Verifica se não é um código de sucesso.
				if (Param_Resultado == S_OK)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_OK; //-> SS_OK | WAIT_OBJECT_0, | D3D_OK | SS_MMSYSERR_NOERROR 

					//Pula para o final do método.
					Sair;
				}



				//----ESSA PARTE VERIFICA OS STATUS DE SUCESSO EXCLUSIVOS OU CASOS ESPECIAIS COMO O (S_FALSE)

				//Verifica o caso especial do codigo de 'erro' S_FALSE
				if (Param_Resultado == S_FALSE)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_FALSE; //-> ER_TIMERR_NOCANDO | SS_AUDCLNT_S_BUFFER_EMPTY 

					//Pula para o final do método.
					Sair;
				}

				else if (Param_Resultado == AUDCLNT_S_POSITION_STALLED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_AUDCLNT_S_POSITION_STALLED;

					//Pula para o final do método.
					Sair;
				}

				else if (Param_Resultado == AUDCLNT_S_THREAD_ALREADY_REGISTERED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_AUDCLNT_S_THREAD_ALREADY_REGISTERED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_OCCLUDED
				else if (Param_Resultado == DXGI_STATUS_OCCLUDED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_OCCLUDED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_CLIPPED
				else if (Param_Resultado == DXGI_STATUS_CLIPPED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_CLIPPED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_NO_REDIRECTION
				else if (Param_Resultado == DXGI_STATUS_NO_REDIRECTION)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_NO_REDIRECTION;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_NO_DESKTOP_ACCESS
				else if (Param_Resultado == DXGI_STATUS_NO_DESKTOP_ACCESS)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_NO_DESKTOP_ACCESS;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE
				else if (Param_Resultado == DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_MODE_CHANGED
				else if (Param_Resultado == DXGI_STATUS_MODE_CHANGED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_OCCLUDED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' DXGI_STATUS_MODE_CHANGE_IN_PROGRESS
				else if (Param_Resultado == DXGI_STATUS_MODE_CHANGE_IN_PROGRESS)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_DXGI_STATUS_MODE_CHANGE_IN_PROGRESS;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' D3DOK_NOAUTOGEN
				else if (Param_Resultado == D3DOK_NOAUTOGEN)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_D3DOK_NOAUTOGEN;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' S_NOT_RESIDENT
				else if (Param_Resultado == S_NOT_RESIDENT)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_S_NOT_RESIDENT;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' S_RESIDENT_IN_SHARED_MEMORY
				else if (Param_Resultado == S_RESIDENT_IN_SHARED_MEMORY)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_S_RESIDENT_IN_SHARED_MEMORY;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' S_PRESENT_MODE_CHANGED
				else if (Param_Resultado == S_PRESENT_MODE_CHANGED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_S_PRESENT_MODE_CHANGED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' S_PRESENT_OCCLUDED
				else if (Param_Resultado == S_PRESENT_OCCLUDED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_S_PRESENT_OCCLUDED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_MULTIPLE_BEGIN
				else if (Param_Resultado == MF_S_MULTIPLE_BEGIN)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_MULTIPLE_BEGIN;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_SINK_NOT_FINALIZED
				else if (Param_Resultado == MF_S_SINK_NOT_FINALIZED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_SINK_NOT_FINALIZED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_ASF_PARSEINPROGRESS
				else if (Param_Resultado == MF_S_ASF_PARSEINPROGRESS)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_ASF_PARSEINPROGRESS;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_I_MANUAL_PROXY
				else if (Param_Resultado == MF_S_ASF_PARSEINPROGRESS)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_I_MANUAL_PROXY;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_PROTECTION_NOT_REQUIRED
				else if (Param_Resultado == MF_S_PROTECTION_NOT_REQUIRED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_PROTECTION_NOT_REQUIRED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_WAIT_FOR_POLICY_SET
				else if (Param_Resultado == MF_S_WAIT_FOR_POLICY_SET)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_WAIT_FOR_POLICY_SET;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT
				else if (Param_Resultado == MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_PE_TRUSTED
				else if (Param_Resultado == MF_S_PE_TRUSTED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_PE_TRUSTED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT
				else if (Param_Resultado == MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_SEQUENCER_CONTEXT_CANCELED
				else if (Param_Resultado == MF_S_SEQUENCER_CONTEXT_CANCELED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_SEQUENCER_CONTEXT_CANCELED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM
				else if (Param_Resultado == MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM;

					//Pula para o final do método.
					Sair;
				}


				//Verifica o caso especial do codigo de 'sucesso' WAIT_TIMEOUT
				else if (Param_Resultado == WAIT_TIMEOUT)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_WAIT_TIMEOUT;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' WAIT_ABANDONED
				else if (Param_Resultado == WAIT_ABANDONED)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_WAIT_ABANDONED;

					//Pula para o final do método.
					Sair;
				}

				//Verifica o caso especial do codigo de 'sucesso' WAIT_IO_COMPLETION
				else if (Param_Resultado == WAIT_IO_COMPLETION)
				{
					//Define o resultado geral como true.
					Resultado = true;

					//Define o status do (ResultCode) manualmente.
					OutStatus = ResultCode::SS_WAIT_IO_COMPLETION;

					//Pula para o final do método.
					Sair;
				}

				//----FIM



				//----VERIFICA OS DEMAIS HRESULTS DENTRO DE UM SWITCH
				switch (Param_Resultado)
				{

					//VERIFICA OS HRESULTS COMUNS DO WINDOWS.


				case E_ABORT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_ABORT;
					break;

				case E_ACCESSDENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_ACCESSDENIED;
					break;

				case E_FAIL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_FAIL;
					break;

				case E_HANDLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_HANDLE;
					break;

				case E_INVALIDARG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_INVALIDARG;
					break;

				case E_NOINTERFACE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_NOINTERFACE;
					break;

				case E_NOTIMPL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_NOTIMPL;
					break;

				case E_OUTOFMEMORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_OUTOFMEMORY;
					break;

				case E_POINTER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_POINTER;
					break;

				case E_UNEXPECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_UNEXPECTED;
					break;

				case E_PENDING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_PENDING;
					break;

				case ERROR_INVALID_FUNCTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_ERROR_INVALID_FUNCTION;
					break;

				case STG_E_ACCESSDENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_STG_E_ACCESSDENIED;
					break;

				case STG_E_CANTSAVE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_STG_E_CANTSAVE;
					break;

				case STG_E_MEDIUMFULL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_STG_E_MEDIUMFULL;
					break;

				case ERROR_ALREADY_EXISTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_ERROR_ALREADY_EXISTS;
					break;

				case ERROR_OBJECT_ALREADY_EXISTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_ERROR_OBJECT_ALREADY_EXISTS;
					break;

				case E_NOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_NOTFOUND;
					break;

				case E_NOT_SUFFICIENT_BUFFER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_E_NOT_SUFFICIENT_BUFFER;
					break;



					

					////////////////////////////////////
					//VERIFICA OS HRESULTS DA WAIT API//
					////////////////////////////////////
				case HRESULT_FROM_WIN32(WAIT_FAILED):
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WAIT_FAILED;
					break;





					////////////////////////////////////
					//VERIFICA OS HRESULTS DO SDK DXGI//
					////////////////////////////////////
				case DXGI_ERROR_ACCESS_DENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_ACCESS_DENIED;
					break;

				case DXGI_ERROR_ACCESS_LOST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_ACCESS_LOST;
					break;

				case DXGI_ERROR_ALREADY_EXISTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_ALREADY_EXISTS;
					break;

				case DXGI_ERROR_CANNOT_PROTECT_CONTENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_CANNOT_PROTECT_CONTENT;
					break;

				case DXGI_ERROR_DEVICE_HUNG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_DEVICE_HUNG;
					break;

				case DXGI_ERROR_DEVICE_REMOVED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_DEVICE_REMOVED;
					break;

				case DXGI_ERROR_DEVICE_RESET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_DEVICE_RESET;
					break;

				case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_DRIVER_INTERNAL_ERROR;
					break;

				case DXGI_ERROR_FRAME_STATISTICS_DISJOINT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_FRAME_STATISTICS_DISJOINT;
					break;

				case DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE;
					break;

				case DXGI_ERROR_INVALID_CALL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_INVALID_CALL;
					break;

				case DXGI_ERROR_MORE_DATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_MORE_DATA;
					break;

				case DXGI_ERROR_NAME_ALREADY_EXISTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NAME_ALREADY_EXISTS;
					break;

				case DXGI_ERROR_NONEXCLUSIVE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NONEXCLUSIVE;
					break;

				case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;
					break;

				case DXGI_ERROR_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NOT_FOUND;
					break;

				case DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED;
					break;

				case DXGI_ERROR_REMOTE_OUTOFMEMORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_REMOTE_OUTOFMEMORY;
					break;

				case DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE;
					break;

				case DXGI_ERROR_SDK_COMPONENT_MISSING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_SDK_COMPONENT_MISSING;
					break;

				case DXGI_ERROR_SESSION_DISCONNECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_SESSION_DISCONNECTED;
					break;

				case DXGI_ERROR_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_UNSUPPORTED;
					break;

				case DXGI_ERROR_WAIT_TIMEOUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_WAIT_TIMEOUT;
					break;

				case DXGI_ERROR_WAS_STILL_DRAWING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_WAS_STILL_DRAWING;
					break;

				case DXGI_STATUS_DDA_WAS_STILL_DRAWING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_STATUS_DDA_WAS_STILL_DRAWING;
					break;
				case DXGI_ERROR_NOT_CURRENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NOT_CURRENT;
					break;

				case DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY;
					break;

				case DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION;
					break;

				case DXGI_ERROR_NON_COMPOSITED_UI:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_NON_COMPOSITED_UI;
					break;

				case DXGI_ERROR_CACHE_CORRUPT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_CACHE_CORRUPT;
					break;

				case DXGI_ERROR_CACHE_FULL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_CACHE_FULL;
					break;

				case DXGI_ERROR_CACHE_HASH_COLLISION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_ERROR_CACHE_HASH_COLLISION;
					break;

				case DXGI_DDI_ERR_WASSTILLDRAWING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_DDI_ERR_WASSTILLDRAWING;
					break;

				case DXGI_DDI_ERR_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_DDI_ERR_UNSUPPORTED;
					break;

				case DXGI_DDI_ERR_NONEXCLUSIVE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXGI_DDI_ERR_NONEXCLUSIVE;
					break;


					//DXVA2

				case DXVA2_E_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXVA2_E_NOT_INITIALIZED;
					break;

				case DXVA2_E_NEW_VIDEO_DEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXVA2_E_NEW_VIDEO_DEVICE;
					break;

				case DXVA2_E_VIDEO_DEVICE_LOCKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXVA2_E_VIDEO_DEVICE_LOCKED;
					break;

				case DXVA2_E_NOT_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_DXVA2_E_NOT_AVAILABLE;
					break;






					//////////////////////////////////////////////
					//VERIFICA OS HRESULTS DO SDK DIRECT 3D 9 EX//
					//////////////////////////////////////////////
				case D3DERR_DEVICEHUNG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DEVICEHUNG;
					break;

				case D3DERR_UNSUPPORTEDOVERLAY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDOVERLAY;
					break;

				case D3DERR_UNSUPPORTEDOVERLAYFORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDOVERLAYFORMAT;
					break;

				case D3DERR_CANNOTPROTECTCONTENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_CANNOTPROTECTCONTENT;
					break;

				case D3DERR_UNSUPPORTEDCRYPTO:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDCRYPTO;
					break;

				case D3DERR_PRESENT_STATISTICS_DISJOINT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_PRESENT_STATISTICS_DISJOINT;
					break;

				case D3DERR_DEVICEREMOVED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DEVICEREMOVED;
					break;

				case D3DERR_WRONGTEXTUREFORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_WRONGTEXTUREFORMAT;
					break;

				case D3DERR_UNSUPPORTEDCOLOROPERATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDCOLOROPERATION;
					break;

				case D3DERR_UNSUPPORTEDCOLORARG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDCOLORARG;
					break;

				case D3DERR_UNSUPPORTEDALPHAOPERATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDALPHAOPERATION;
					break;

				case D3DERR_UNSUPPORTEDALPHAARG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDALPHAARG;
					break;

				case D3DERR_TOOMANYOPERATIONS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_TOOMANYOPERATIONS;
					break;

				case D3DERR_CONFLICTINGTEXTUREFILTER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_CONFLICTINGTEXTUREFILTER;
					break;

				case D3DERR_UNSUPPORTEDFACTORVALUE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDFACTORVALUE;
					break;

				case D3DERR_CONFLICTINGRENDERSTATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_CONFLICTINGRENDERSTATE;
					break;

				case D3DERR_UNSUPPORTEDTEXTUREFILTER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_UNSUPPORTEDTEXTUREFILTER;
					break;

				case D3DERR_CONFLICTINGTEXTUREPALETTE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_CONFLICTINGTEXTUREPALETTE;
					break;

				case D3DERR_DRIVERINTERNALERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DRIVERINTERNALERROR;
					break;

				case D3DERR_NOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_NOTFOUND;
					break;

				case D3DERR_MOREDATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_MOREDATA;
					break;

				case D3DERR_DEVICELOST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DEVICELOST;
					break;

				case D3DERR_DEVICENOTRESET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DEVICENOTRESET;
					break;

				case D3DERR_NOTAVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_NOTAVAILABLE;
					break;

				case D3DERR_OUTOFVIDEOMEMORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_OUTOFVIDEOMEMORY;
					break;

				case D3DERR_INVALIDDEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_INVALIDDEVICE;
					break;

				case D3DERR_INVALIDCALL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_INVALIDCALL;
					break;

				case D3DERR_DRIVERINVALIDCALL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_DRIVERINVALIDCALL;
					break;

				case D3DERR_WASSTILLDRAWING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3DERR_WASSTILLDRAWING;
					break;





					////////////////////////////////////////////
					//VERIFICA OS HRESULTS DO SDK DIRECT 3D 11//
					////////////////////////////////////////////
				case D3D11_ERROR_FILE_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3D11_ERROR_FILE_NOT_FOUND;
					break;

				case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS;
					break;

				case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS;
					break;

				case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD;
					break;








					/////////////////////////////////////////
					//VERIFICA OS HRESULTS DO SDK DIRECT 2D//
					/////////////////////////////////////////
				case D2DERR_WRONG_STATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_WRONG_STATE;
					break;

				case D2DERR_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_NOT_INITIALIZED;
					break;

				case D2DERR_UNSUPPORTED_OPERATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_UNSUPPORTED_OPERATION;
					break;

				case D2DERR_SCANNER_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_SCANNER_FAILED;
					break;

				case D2DERR_SCREEN_ACCESS_DENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_SCREEN_ACCESS_DENIED;
					break;

				case D2DERR_DISPLAY_STATE_INVALID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_DISPLAY_STATE_INVALID;
					break;

				case D2DERR_ZERO_VECTOR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_ZERO_VECTOR;
					break;

				case D2DERR_INTERNAL_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INTERNAL_ERROR;
					break;

				case D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED;
					break;

				case D2DERR_INVALID_CALL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_CALL;
					break;

				case D2DERR_NO_HARDWARE_DEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_NO_HARDWARE_DEVICE;
					break;

				case D2DERR_RECREATE_TARGET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_RECREATE_TARGET;
					break;

				case D2DERR_TOO_MANY_SHADER_ELEMENTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_TOO_MANY_SHADER_ELEMENTS;
					break;

				case D2DERR_SHADER_COMPILE_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_SHADER_COMPILE_FAILED;
					break;

				case D2DERR_MAX_TEXTURE_SIZE_EXCEEDED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_MAX_TEXTURE_SIZE_EXCEEDED;
					break;

				case D2DERR_UNSUPPORTED_VERSION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_UNSUPPORTED_VERSION;
					break;

				case D2DERR_BAD_NUMBER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_BAD_NUMBER;
					break;

				case D2DERR_WRONG_FACTORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_WRONG_FACTORY;
					break;

				case D2DERR_LAYER_ALREADY_IN_USE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_LAYER_ALREADY_IN_USE;
					break;

				case D2DERR_POP_CALL_DID_NOT_MATCH_PUSH:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_POP_CALL_DID_NOT_MATCH_PUSH;
					break;

				case D2DERR_WRONG_RESOURCE_DOMAIN:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_WRONG_RESOURCE_DOMAIN;
					break;

				case D2DERR_PUSH_POP_UNBALANCED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_PUSH_POP_UNBALANCED;
					break;

				case D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT;
					break;

				case D2DERR_INCOMPATIBLE_BRUSH_TYPES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INCOMPATIBLE_BRUSH_TYPES;
					break;

				case D2DERR_WIN32_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_WIN32_ERROR;
					break;

				case D2DERR_TARGET_NOT_GDI_COMPATIBLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_TARGET_NOT_GDI_COMPATIBLE;
					break;

				case D2DERR_TEXT_EFFECT_IS_WRONG_TYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_TEXT_EFFECT_IS_WRONG_TYPE;
					break;

				case D2DERR_TEXT_RENDERER_NOT_RELEASED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_TEXT_RENDERER_NOT_RELEASED;
					break;

				case D2DERR_EXCEEDS_MAX_BITMAP_SIZE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_EXCEEDS_MAX_BITMAP_SIZE;
					break;

				case D2DERR_INVALID_GRAPH_CONFIGURATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_GRAPH_CONFIGURATION;
					break;

				case D2DERR_INVALID_INTERNAL_GRAPH_CONFIGURATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_INTERNAL_GRAPH_CONFIGURATION;
					break;

				case D2DERR_CYCLIC_GRAPH:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_CYCLIC_GRAPH;
					break;

				case D2DERR_BITMAP_CANNOT_DRAW:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_BITMAP_CANNOT_DRAW;
					break;

				case D2DERR_OUTSTANDING_BITMAP_REFERENCES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_OUTSTANDING_BITMAP_REFERENCES;
					break;

				case D2DERR_ORIGINAL_TARGET_NOT_BOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_ORIGINAL_TARGET_NOT_BOUND;
					break;

				case D2DERR_INVALID_TARGET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_TARGET;
					break;

				case D2DERR_BITMAP_BOUND_AS_TARGET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_BITMAP_BOUND_AS_TARGET;
					break;

				case D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES;
					break;

				case D2DERR_INTERMEDIATE_TOO_LARGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INTERMEDIATE_TOO_LARGE;
					break;

				case D2DERR_EFFECT_IS_NOT_REGISTERED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_EFFECT_IS_NOT_REGISTERED;
					break;

				case D2DERR_INVALID_PROPERTY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_PROPERTY;
					break;

				case D2DERR_NO_SUBPROPERTIES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_NO_SUBPROPERTIES;
					break;

				case D2DERR_PRINT_JOB_CLOSED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_PRINT_JOB_CLOSED;
					break;

				case D2DERR_PRINT_FORMAT_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_PRINT_FORMAT_NOT_SUPPORTED;
					break;

				case D2DERR_TOO_MANY_TRANSFORM_INPUTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_TOO_MANY_TRANSFORM_INPUTS;
					break;

				case D2DERR_INVALID_GLYPH_IMAGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_D2DERR_INVALID_GLYPH_IMAGE;
					break;





					///////////////////////////////////
					//WINDOWS IMAGING COMPONENT (WIC)//
					///////////////////////////////////
				case WINCODEC_ERR_WRONGSTATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_WRONGSTATE;
					break;

				case WINCODEC_ERR_VALUEOUTOFRANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_VALUEOUTOFRANGE;
					break;

				case WINCODEC_ERR_UNKNOWNIMAGEFORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_UNKNOWNIMAGEFORMAT;
					break;

				case WINCODEC_ERR_NOTINITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_NOTINITIALIZED;
					break;

				case WINCODEC_ERR_ALREADYLOCKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_ALREADYLOCKED;
					break;

				case WINCODEC_ERR_PROPERTYNOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_PROPERTYNOTFOUND;
					break;

				case WINCODEC_ERR_PROPERTYNOTSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_PROPERTYNOTSUPPORTED;
					break;

				case WINCODEC_ERR_PROPERTYSIZE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_PROPERTYSIZE;
					break;

				case WINCODEC_ERR_CODECPRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_CODECPRESENT;
					break;

				case WINCODEC_ERR_CODECNOTHUMBNAIL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_CODECNOTHUMBNAIL;
					break;

				case WINCODEC_ERR_PALETTEUNAVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_PALETTEUNAVAILABLE;
					break;

				case WINCODEC_ERR_CODECTOOMANYSCANLINES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_CODECTOOMANYSCANLINES;
					break;

				case WINCODEC_ERR_INTERNALERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INTERNALERROR;
					break;

				case WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS;
					break;

				case WINCODEC_ERR_COMPONENTNOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_COMPONENTNOTFOUND;
					break;

				case WINCODEC_ERR_IMAGESIZEOUTOFRANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_IMAGESIZEOUTOFRANGE;
					break;

				case WINCODEC_ERR_TOOMUCHMETADATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_TOOMUCHMETADATA;
					break;

				case WINCODEC_ERR_BADIMAGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_BADIMAGE;
					break;

				case WINCODEC_ERR_BADHEADER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_BADHEADER;
					break;

				case WINCODEC_ERR_FRAMEMISSING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_FRAMEMISSING;
					break;

				case WINCODEC_ERR_BADMETADATAHEADER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_BADMETADATAHEADER;
					break;

				case WINCODEC_ERR_BADSTREAMDATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_BADSTREAMDATA;
					break;

				case WINCODEC_ERR_STREAMWRITE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_STREAMWRITE;
					break;

				case WINCODEC_ERR_STREAMREAD:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_STREAMREAD;
					break;

				case WINCODEC_ERR_STREAMNOTAVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_STREAMNOTAVAILABLE;
					break;

				case WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;
					break;

				case WINCODEC_ERR_UNSUPPORTEDOPERATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_UNSUPPORTEDOPERATION;
					break;

				case WINCODEC_ERR_INVALIDREGISTRATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INVALIDREGISTRATION;
					break;

				case WINCODEC_ERR_COMPONENTINITIALIZEFAILURE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_COMPONENTINITIALIZEFAILURE;
					break;

				case WINCODEC_ERR_INSUFFICIENTBUFFER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INSUFFICIENTBUFFER;
					break;

				case WINCODEC_ERR_DUPLICATEMETADATAPRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_DUPLICATEMETADATAPRESENT;
					break;

				case WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE;
					break;

				case WINCODEC_ERR_UNEXPECTEDSIZE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_UNEXPECTEDSIZE;
					break;

				case WINCODEC_ERR_INVALIDQUERYREQUEST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INVALIDQUERYREQUEST;
					break;

				case WINCODEC_ERR_UNEXPECTEDMETADATATYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_UNEXPECTEDMETADATATYPE;
					break;

				case WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT;
					break;

				case WINCODEC_ERR_INVALIDQUERYCHARACTER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INVALIDQUERYCHARACTER;
					break;

				case WINCODEC_ERR_WIN32ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_WIN32ERROR;
					break;

				case WINCODEC_ERR_INVALIDPROGRESSIVELEVEL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INVALIDPROGRESSIVELEVEL;
					break;

				case WINCODEC_ERR_INVALIDJPEGSCANINDEX:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_WINCODEC_ERR_INVALIDJPEGSCANINDEX;
					break;




					////////////////////////////////////////////////
					//VERIFICA OS HRESULTS DO SDK MEDIA FOUNDATION//
					////////////////////////////////////////////////
				case MF_E_PLATFORM_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PLATFORM_NOT_INITIALIZED;
					break;

				case MF_E_BUFFERTOOSMALL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BUFFERTOOSMALL;
					break;

				case MF_E_INVALIDREQUEST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDREQUEST;
					break;

				case MF_E_INVALIDSTREAMNUMBER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDSTREAMNUMBER;
					break;

				case MF_E_INVALIDMEDIATYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDMEDIATYPE;
					break;

				case MF_E_NOTACCEPTING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NOTACCEPTING;
					break;

				case MF_E_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NOT_INITIALIZED;
					break;

				case MF_E_UNSUPPORTED_REPRESENTATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_REPRESENTATION;
					break;

				case MF_E_NO_MORE_TYPES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_MORE_TYPES;
					break;

				case MF_E_UNSUPPORTED_SERVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_SERVICE;
					break;

				case MF_E_UNEXPECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNEXPECTED;
					break;

				case MF_E_INVALIDNAME:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDNAME;
					break;

				case MF_E_INVALIDTYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDTYPE;
					break;

				case MF_E_INVALID_FILE_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_FILE_FORMAT;
					break;

				case MF_E_INVALIDINDEX:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALIDINDEX;
					break;

				case MF_E_INVALID_TIMESTAMP:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_TIMESTAMP;
					break;

				case MF_E_UNSUPPORTED_SCHEME:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_SCHEME;
					break;

				case MF_E_UNSUPPORTED_BYTESTREAM_TYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_BYTESTREAM_TYPE;
					break;

				case MF_E_UNSUPPORTED_TIME_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_TIME_FORMAT;
					break;

				case MF_E_NO_SAMPLE_TIMESTAMP:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_SAMPLE_TIMESTAMP;
					break;

				case MF_E_NO_SAMPLE_DURATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_SAMPLE_DURATION;
					break;

				case MF_E_INVALID_STREAM_DATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_STREAM_DATA;
					break;

				case MF_E_RT_UNAVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_UNAVAILABLE;
					break;

				case MF_E_UNSUPPORTED_RATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_RATE;
					break;

				case MF_E_THINNING_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_THINNING_UNSUPPORTED;
					break;

				case MF_E_REVERSE_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_REVERSE_UNSUPPORTED;
					break;

				case MF_E_UNSUPPORTED_RATE_TRANSITION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_RATE_TRANSITION;
					break;

				case MF_E_RATE_CHANGE_PREEMPTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RATE_CHANGE_PREEMPTED;
					break;

				case MF_E_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NOT_FOUND;
					break;

				case MF_E_NOT_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NOT_AVAILABLE;
					break;

				case MF_E_NO_CLOCK:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_CLOCK;
					break;

				case MF_E_MULTIPLE_SUBSCRIBERS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MULTIPLE_SUBSCRIBERS;
					break;

				case MF_E_TIMER_ORPHANED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TIMER_ORPHANED;
					break;

				case MF_E_STATE_TRANSITION_PENDING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STATE_TRANSITION_PENDING;
					break;

				case MF_E_UNSUPPORTED_STATE_TRANSITION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_STATE_TRANSITION;
					break;

				case MF_E_UNRECOVERABLE_ERROR_OCCURRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNRECOVERABLE_ERROR_OCCURRED;
					break;

				case MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS;
					break;

				case MF_E_SAMPLE_NOT_WRITABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SAMPLE_NOT_WRITABLE;
					break;

				case MF_E_INVALID_KEY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_KEY;
					break;

				case MF_E_BAD_STARTUP_VERSION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BAD_STARTUP_VERSION;
					break;

				case MF_E_UNSUPPORTED_CAPTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_CAPTION;
					break;

				case MF_E_INVALID_POSITION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_POSITION;
					break;

				case MF_E_ATTRIBUTENOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ATTRIBUTENOTFOUND;
					break;

				case MF_E_PROPERTY_TYPE_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_TYPE_NOT_ALLOWED;
					break;

				case MF_E_PROPERTY_TYPE_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_TYPE_NOT_SUPPORTED;
					break;

				case MF_E_PROPERTY_EMPTY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_EMPTY;
					break;

				case MF_E_PROPERTY_NOT_EMPTY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_NOT_EMPTY;
					break;

				case MF_E_PROPERTY_VECTOR_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_VECTOR_NOT_ALLOWED;
					break;

				case MF_E_PROPERTY_VECTOR_REQUIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_VECTOR_REQUIRED;
					break;

				case MF_E_OPERATION_CANCELLED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OPERATION_CANCELLED;
					break;


				case MF_E_BYTESTREAM_NOT_SEEKABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BYTESTREAM_NOT_SEEKABLE;
					break;

				case MF_E_DISABLED_IN_SAFEMODE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DISABLED_IN_SAFEMODE;
					break;

				case MF_E_CANNOT_PARSE_BYTESTREAM:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CANNOT_PARSE_BYTESTREAM;
					break;

				case MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS;
					break;

				case MF_E_MEDIAPROC_WRONGSTATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIAPROC_WRONGSTATE;
					break;

				case MF_E_RT_THROUGHPUT_NOT_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_THROUGHPUT_NOT_AVAILABLE;
					break;

				case MF_E_RT_TOO_MANY_CLASSES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_TOO_MANY_CLASSES;
					break;

				case MF_E_RT_WOULDBLOCK:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_WOULDBLOCK;
					break;

				case MF_E_NO_BITPUMP:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_BITPUMP;
					break;

				case MF_E_RT_OUTOFMEMORY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_OUTOFMEMORY;
					break;

				case MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED;
					break;

				case MF_E_INSUFFICIENT_BUFFER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INSUFFICIENT_BUFFER;
					break;

				case MF_E_CANNOT_CREATE_SINK:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CANNOT_CREATE_SINK;
					break;

				case MF_E_BYTESTREAM_UNKNOWN_LENGTH:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BYTESTREAM_UNKNOWN_LENGTH;
					break;

				case MF_E_SESSION_PAUSEWHILESTOPPED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SESSION_PAUSEWHILESTOPPED;
					break;

				case MF_S_ACTIVATE_REPLACED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_S_ACTIVATE_REPLACED;
					break;

				case MF_E_FORMAT_CHANGE_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_FORMAT_CHANGE_NOT_SUPPORTED;
					break;

				case MF_E_INVALID_WORKQUEUE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_WORKQUEUE;
					break;

				case MF_E_DRM_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DRM_UNSUPPORTED;
					break;

				case MF_E_UNAUTHORIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNAUTHORIZED;
					break;

				case MF_E_OUT_OF_RANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OUT_OF_RANGE;
					break;

				case MF_E_INVALID_CODEC_MERIT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_CODEC_MERIT;
					break;

				case MF_E_HW_MFT_FAILED_START_STREAMING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HW_MFT_FAILED_START_STREAMING;
					break;

				case MF_E_OPERATION_IN_PROGRESS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OPERATION_IN_PROGRESS;
					break;

				case MF_E_HARDWARE_DRM_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HARDWARE_DRM_UNSUPPORTED;
					break;

				case MF_E_DURATION_TOO_LONG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DURATION_TOO_LONG;
					break;

				case MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL;
					break;

				case MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL;
					break;



					//////////////////////////////
					//MEDIA FOUNDATION ASF Erros//
					//////////////////////////////



				case MF_E_ASF_PARSINGINCOMPLETE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_PARSINGINCOMPLETE;
					break;


				case MF_E_ASF_MISSINGDATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_MISSINGDATA;
					break;


				case MF_E_ASF_INVALIDDATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_INVALIDDATA;
					break;


				case MF_E_ASF_OPAQUEPACKET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_OPAQUEPACKET;
					break;


				case MF_E_ASF_NOINDEX:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_NOINDEX;
					break;


				case MF_E_ASF_OUTOFRANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_OUTOFRANGE;
					break;

				case MF_E_ASF_INDEXNOTLOADED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_INDEXNOTLOADED;
					break;

				case MF_E_ASF_TOO_MANY_PAYLOADS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_TOO_MANY_PAYLOADS;
					break;

				case MF_E_ASF_UNSUPPORTED_STREAM_TYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_UNSUPPORTED_STREAM_TYPE;
					break;

				case MF_E_ASF_DROPPED_PACKET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_DROPPED_PACKET;
					break;



					////////////////////////////////////////
					//MEDIA FOUNDATION Media Source Errors//
					////////////////////////////////////////



				case MF_E_NO_EVENTS_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_EVENTS_AVAILABLE;
					break;


				case MF_E_INVALID_STATE_TRANSITION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_STATE_TRANSITION;
					break;


				case MF_E_END_OF_STREAM:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_END_OF_STREAM;
					break;

				case MF_E_SHUTDOWN:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SHUTDOWN;
					break;

				case MF_E_MP3_NOTFOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MP3_NOTFOUND;
					break;

				case MF_E_MP3_OUTOFDATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MP3_OUTOFDATA;
					break;

				case MF_E_MP3_NOTMP3:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MP3_NOTMP3;
					break;

				case MF_E_MP3_NOTSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MP3_NOTSUPPORTED;
					break;

				case MF_E_NO_DURATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_DURATION;
					break;

				case MF_E_INVALID_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_FORMAT;
					break;

				case MF_E_PROPERTY_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_NOT_FOUND;
					break;

				case MF_E_PROPERTY_READ_ONLY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_READ_ONLY;
					break;

				case MF_E_PROPERTY_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROPERTY_NOT_ALLOWED;
					break;

				case MF_E_MEDIA_SOURCE_NOT_STARTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_SOURCE_NOT_STARTED;
					break;

				case MF_E_UNSUPPORTED_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_FORMAT;
					break;

				case MF_E_MP3_BAD_CRC:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MP3_BAD_CRC;
					break;

				case MF_E_NOT_PROTECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NOT_PROTECTED;
					break;

				case MF_E_MEDIA_SOURCE_WRONGSTATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_SOURCE_WRONGSTATE;
					break;

				case MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED;
					break;

				case MF_E_CANNOT_FIND_KEYFRAME_SAMPLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CANNOT_FIND_KEYFRAME_SAMPLE;
					break;

				case MF_E_UNSUPPORTED_CHARACTERISTICS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_CHARACTERISTICS;
					break;

				case MF_E_NO_AUDIO_RECORDING_DEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_AUDIO_RECORDING_DEVICE;
					break;

				case MF_E_AUDIO_RECORDING_DEVICE_IN_USE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_RECORDING_DEVICE_IN_USE;
					break;

				case MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED;
					break;

				case MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED;
					break;

				case MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED;
					break;




					///////////////////////////////////
					//MEDIA FOUNDATION Network Errors//
					///////////////////////////////////



				case MF_E_NETWORK_RESOURCE_FAILURE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NETWORK_RESOURCE_FAILURE;
					break;

				case MF_E_NET_WRITE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_WRITE;
					break;

				case MF_E_NET_READ:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_READ;
					break;

				case MF_E_NET_REQUIRE_NETWORK:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_REQUIRE_NETWORK;
					break;

				case MF_E_NET_REQUIRE_ASYNC:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_REQUIRE_ASYNC;
					break;

				case MF_E_NET_BWLEVEL_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_BWLEVEL_NOT_SUPPORTED;
					break;

				case MF_E_NET_STREAMGROUPS_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_STREAMGROUPS_NOT_SUPPORTED;
					break;

				case MF_E_NET_MANUALSS_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_MANUALSS_NOT_SUPPORTED;
					break;

				case MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR;
					break;

				case MF_E_NET_CACHESTREAM_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_CACHESTREAM_NOT_FOUND;
					break;

				case MF_E_NET_REQUIRE_INPUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_REQUIRE_INPUT;
					break;

				case MF_E_NET_REDIRECT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_REDIRECT;
					break;

				case MF_E_NET_REDIRECT_TO_PROXY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_REDIRECT_TO_PROXY;
					break;

				case MF_E_NET_TOO_MANY_REDIRECTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_TOO_MANY_REDIRECTS;
					break;

				case MF_E_NET_TIMEOUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_TIMEOUT;
					break;

				case MF_E_NET_CLIENT_CLOSE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_CLIENT_CLOSE;
					break;

				case MF_E_NET_BAD_CONTROL_DATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_BAD_CONTROL_DATA;
					break;

				case MF_E_NET_INCOMPATIBLE_SERVER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INCOMPATIBLE_SERVER;
					break;

				case MF_E_NET_UNSAFE_URL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_UNSAFE_URL;
					break;

				case MF_E_NET_CACHE_NO_DATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_CACHE_NO_DATA;
					break;

				case MF_E_NET_EOL:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_EOL;
					break;

				case MF_E_NET_BAD_REQUEST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_BAD_REQUEST;
					break;

				case MF_E_NET_INTERNAL_SERVER_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INTERNAL_SERVER_ERROR;
					break;

				case MF_E_NET_SESSION_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_SESSION_NOT_FOUND;
					break;

				case MF_E_NET_NOCONNECTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_NOCONNECTION;
					break;

				case MF_E_NET_CONNECTION_FAILURE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_CONNECTION_FAILURE;
					break;

				case MF_E_NET_INCOMPATIBLE_PUSHSERVER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INCOMPATIBLE_PUSHSERVER;
					break;

				case MF_E_NET_SERVER_ACCESSDENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_SERVER_ACCESSDENIED;
					break;

				case MF_E_NET_PROXY_ACCESSDENIED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_PROXY_ACCESSDENIED;
					break;

				case MF_E_NET_CANNOTCONNECT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_CANNOTCONNECT;
					break;

				case MF_E_NET_INVALID_PUSH_TEMPLATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INVALID_PUSH_TEMPLATE;
					break;

				case MF_E_NET_INVALID_PUSH_PUBLISHING_POINT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_INVALID_PUSH_PUBLISHING_POINT;
					break;

				case MF_E_NET_BUSY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_BUSY;
					break;

				case MF_E_NET_RESOURCE_GONE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_RESOURCE_GONE;
					break;

				case MF_E_NET_ERROR_FROM_PROXY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_ERROR_FROM_PROXY;
					break;

				case MF_E_NET_PROXY_TIMEOUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_PROXY_TIMEOUT;
					break;

				case MF_E_NET_SERVER_UNAVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_SERVER_UNAVAILABLE;
					break;

				case MF_E_NET_TOO_MUCH_DATA:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_TOO_MUCH_DATA;
					break;

				case MF_E_NET_SESSION_INVALID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_SESSION_INVALID;
					break;

				case MF_E_OFFLINE_MODE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OFFLINE_MODE;
					break;

				case MF_E_NET_UDP_BLOCKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_UDP_BLOCKED;
					break;

				case MF_E_NET_UNSUPPORTED_CONFIGURATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_UNSUPPORTED_CONFIGURATION;
					break;

				case MF_E_NET_PROTOCOL_DISABLED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_PROTOCOL_DISABLED;
					break;

				case MF_E_NET_COMPANION_DRIVER_DISCONNECT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NET_COMPANION_DRIVER_DISCONNECT;
					break;



					/////////////////////////////////////////////
					//MEDIA FOUNDATION WMContainer Error Events//
					/////////////////////////////////////////////


				case MF_E_ALREADY_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ALREADY_INITIALIZED;
					break;

				case MF_E_BANDWIDTH_OVERRUN:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BANDWIDTH_OVERRUN;
					break;

				case MF_E_LATE_SAMPLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LATE_SAMPLE;
					break;

				case MF_E_FLUSH_NEEDED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_FLUSH_NEEDED;
					break;

				case MF_E_INVALID_PROFILE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_PROFILE;
					break;

				case MF_E_INDEX_NOT_COMMITTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INDEX_NOT_COMMITTED;
					break;

				case MF_E_NO_INDEX:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_INDEX;
					break;

				case MF_E_CANNOT_INDEX_IN_PLACE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CANNOT_INDEX_IN_PLACE;
					break;

				case MF_E_MISSING_ASF_LEAKYBUCKET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MISSING_ASF_LEAKYBUCKET;
					break;

				case MF_E_INVALID_ASF_STREAMID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_ASF_STREAMID;
					break;




					/////////////////////////////////////////////
					// MEDIA FOUNDATION Media Sink Error Events//
					/////////////////////////////////////////////




				case MF_E_STREAMSINK_REMOVED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STREAMSINK_REMOVED;
					break;

				case MF_E_STREAMSINKS_OUT_OF_SYNC:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STREAMSINKS_OUT_OF_SYNC;
					break;

				case MF_E_STREAMSINKS_FIXED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STREAMSINKS_FIXED;
					break;

				case MF_E_STREAMSINK_EXISTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STREAMSINK_EXISTS;
					break;

				case MF_E_SAMPLEALLOCATOR_CANCELED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SAMPLEALLOCATOR_CANCELED;
					break;

				case MF_E_SAMPLEALLOCATOR_EMPTY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SAMPLEALLOCATOR_EMPTY;
					break;

				case MF_E_SINK_ALREADYSTOPPED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SINK_ALREADYSTOPPED;
					break;

				case MF_E_ASF_FILESINK_BITRATE_UNKNOWN:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ASF_FILESINK_BITRATE_UNKNOWN;
					break;

				case MF_E_SINK_NO_STREAMS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SINK_NO_STREAMS;
					break;

				case MF_E_METADATA_TOO_LONG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_METADATA_TOO_LONG;
					break;

				case MF_E_SINK_NO_SAMPLES_PROCESSED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SINK_NO_SAMPLES_PROCESSED;
					break;

				case MF_E_SINK_HEADERS_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SINK_HEADERS_NOT_FOUND;
					break;




					//////////////////////////////////////////
					//MEDIA FOUNDATION Renderer Error Events//
					//////////////////////////////////////////



				case MF_E_VIDEO_REN_NO_PROCAMP_HW:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_REN_NO_PROCAMP_HW;
					break;

				case MF_E_VIDEO_REN_NO_DEINTERLACE_HW:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_REN_NO_DEINTERLACE_HW;
					break;

				case MF_E_VIDEO_REN_COPYPROT_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_REN_COPYPROT_FAILED;
					break;

				case MF_E_VIDEO_REN_SURFACE_NOT_SHARED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_REN_SURFACE_NOT_SHARED;
					break;

				case MF_E_VIDEO_DEVICE_LOCKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_VIDEO_DEVICE_LOCKED;
					break;

				case MF_E_NEW_VIDEO_DEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NEW_VIDEO_DEVICE;
					break;

				case MF_E_NO_VIDEO_SAMPLE_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_VIDEO_SAMPLE_AVAILABLE;
					break;

				case MF_E_NO_AUDIO_PLAYBACK_DEVICE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_AUDIO_PLAYBACK_DEVICE;
					break;

				case MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE;
					break;

				case MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED;
					break;

				case MF_E_AUDIO_SERVICE_NOT_RUNNING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_SERVICE_NOT_RUNNING;
					break;

				case MF_E_AUDIO_BUFFER_SIZE_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_BUFFER_SIZE_ERROR;
					break;

				case MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR;
					break;




					//////////////////////////////////////////
					//MEDIA FOUNDATION Topology Error Events//
					//////////////////////////////////////////



				case MF_E_TOPO_INVALID_OPTIONAL_NODE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_INVALID_OPTIONAL_NODE;
					break;

				case MF_E_TOPO_CANNOT_FIND_DECRYPTOR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_CANNOT_FIND_DECRYPTOR;
					break;

				case MF_E_TOPO_CODEC_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_CODEC_NOT_FOUND;
					break;

				case MF_E_TOPO_CANNOT_CONNECT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_CANNOT_CONNECT;
					break;

				case MF_E_TOPO_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_UNSUPPORTED;
					break;

				case MF_E_TOPO_INVALID_TIME_ATTRIBUTES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_INVALID_TIME_ATTRIBUTES;
					break;

				case MF_E_TOPO_LOOPS_IN_TOPOLOGY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_LOOPS_IN_TOPOLOGY;
					break;

				case MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR;
					break;

				case MF_E_TOPO_MISSING_STREAM_DESCRIPTOR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_MISSING_STREAM_DESCRIPTOR;
					break;

				case MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED;
					break;

				case MF_E_TOPO_MISSING_SOURCE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_MISSING_SOURCE;
					break;

				case MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED;
					break;




					//////////////////////////////////////////
					//MEDIA FOUNDATION Timeline Error Events//
					//////////////////////////////////////////




				case MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID;
					break;

				case MF_E_NO_SOURCE_IN_CACHE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_SOURCE_IN_CACHE;
					break;




					//////////////////////////////////////
					//MEDIA FOUNDATION  Transform errors//
					//////////////////////////////////////




				case MF_E_TRANSFORM_TYPE_NOT_SET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_TYPE_NOT_SET;
					break;

				case MF_E_TRANSFORM_STREAM_CHANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_STREAM_CHANGE;
					break;

				case MF_E_TRANSFORM_INPUT_REMAINING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_INPUT_REMAINING;
					break;

				case MF_E_TRANSFORM_PROFILE_MISSING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROFILE_MISSING;
					break;

				case MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT;
					break;

				case MF_E_TRANSFORM_PROFILE_TRUNCATED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROFILE_TRUNCATED;
					break;

				case MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED;
					break;

				case MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG;
					break;

				case MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE;
					break;

				case MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM;
					break;

				case MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG;
					break;

				case MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE;
					break;

				case MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE;
					break;

				case MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE;
					break;

				case MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE;
					break;

				case MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION;
					break;

				case MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES;
					break;

				case MF_E_TRANSFORM_NEED_MORE_INPUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_NEED_MORE_INPUT;
					break;

				case MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG;
					break;

				case MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING;
					break;

				case MF_E_UNSUPPORTED_D3D_TYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_D3D_TYPE;
					break;

				case MF_E_TRANSFORM_ASYNC_LOCKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_ASYNC_LOCKED;
					break;

				case MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER;
					break;

				case MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION;
					break;

				case MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED;
					break;

				case MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED;
					break;




					//////////////////////////////////////////////
					//MEDIA FOUNDATION Content Protection errors//
					//////////////////////////////////////////////




				case MF_E_LICENSE_INCORRECT_RIGHTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LICENSE_INCORRECT_RIGHTS;
					break;

				case MF_E_LICENSE_OUTOFDATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LICENSE_OUTOFDATE;
					break;

				case MF_E_LICENSE_REQUIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LICENSE_REQUIRED;
					break;

				case MF_E_DRM_HARDWARE_INCONSISTENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DRM_HARDWARE_INCONSISTENT;
					break;

				case MF_E_NO_CONTENT_PROTECTION_MANAGER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_CONTENT_PROTECTION_MANAGER;
					break;

				case MF_E_LICENSE_RESTORE_NO_RIGHTS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LICENSE_RESTORE_NO_RIGHTS;
					break;

				case MF_E_BACKUP_RESTRICTED_LICENSE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BACKUP_RESTRICTED_LICENSE;
					break;

				case MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION;
					break;

				case MF_E_COMPONENT_REVOKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_COMPONENT_REVOKED;
					break;

				case MF_E_TRUST_DISABLED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRUST_DISABLED;
					break;

				case MF_E_WMDRMOTA_NO_ACTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_NO_ACTION;
					break;

				case MF_E_WMDRMOTA_ACTION_ALREADY_SET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_ACTION_ALREADY_SET;
					break;

				case MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE;
					break;

				case MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED;
					break;

				case MF_E_WMDRMOTA_ACTION_MISMATCH:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_ACTION_MISMATCH;
					break;

				case MF_E_WMDRMOTA_INVALID_POLICY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_WMDRMOTA_INVALID_POLICY;
					break;

				case MF_E_POLICY_UNSUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_POLICY_UNSUPPORTED;
					break;

				case MF_E_OPL_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_OPL_NOT_SUPPORTED;
					break;

				case MF_E_TOPOLOGY_VERIFICATION_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TOPOLOGY_VERIFICATION_FAILED;
					break;

				case MF_E_SIGNATURE_VERIFICATION_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_SIGNATURE_VERIFICATION_FAILED;
					break;

				case MF_E_DEBUGGING_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DEBUGGING_NOT_ALLOWED;
					break;

				case MF_E_CODE_EXPIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CODE_EXPIRED;
					break;

				case MF_E_GRL_VERSION_TOO_LOW:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_VERSION_TOO_LOW;
					break;

				case MF_E_GRL_RENEWAL_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_RENEWAL_NOT_FOUND;
					break;

				case MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND;
					break;

				case MF_E_KERNEL_UNTRUSTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_KERNEL_UNTRUSTED;
					break;

				case MF_E_PEAUTH_UNTRUSTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PEAUTH_UNTRUSTED;
					break;

				case MF_E_NON_PE_PROCESS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NON_PE_PROCESS;
					break;

				case MF_E_REBOOT_REQUIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_REBOOT_REQUIRED;
					break;

				case MF_E_GRL_INVALID_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_INVALID_FORMAT;
					break;

				case MF_E_GRL_UNRECOGNIZED_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_UNRECOGNIZED_FORMAT;
					break;

				case MF_E_ALL_PROCESS_RESTART_REQUIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ALL_PROCESS_RESTART_REQUIRED;
					break;

				case MF_E_PROCESS_RESTART_REQUIRED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PROCESS_RESTART_REQUIRED;
					break;

				case MF_E_USERMODE_UNTRUSTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_USERMODE_UNTRUSTED;
					break;

				case MF_E_PEAUTH_SESSION_NOT_STARTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PEAUTH_SESSION_NOT_STARTED;
					break;

				case MF_E_PEAUTH_PUBLICKEY_REVOKED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PEAUTH_PUBLICKEY_REVOKED;
					break;

				case MF_E_GRL_ABSENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_GRL_ABSENT;
					break;

				case MF_E_PE_UNTRUSTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PE_UNTRUSTED;
					break;

				case MF_E_PEAUTH_NOT_STARTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PEAUTH_NOT_STARTED;
					break;

				case MF_E_INCOMPATIBLE_SAMPLE_PROTECTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INCOMPATIBLE_SAMPLE_PROTECTION;
					break;

				case MF_E_PE_SESSIONS_MAXED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_PE_SESSIONS_MAXED;
					break;

				case MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED;
					break;

				case MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED;
					break;

				case MF_E_ITA_UNSUPPORTED_ACTION:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_UNSUPPORTED_ACTION;
					break;

				case MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS;
					break;

				case MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS;
					break;

				case MF_E_BAD_OPL_STRUCTURE_FORMAT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_BAD_OPL_STRUCTURE_FORMAT;
					break;

				case MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID;
					break;

				case MF_E_NO_PMP_HOST:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_PMP_HOST;
					break;

				case MF_E_ITA_OPL_DATA_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_OPL_DATA_NOT_INITIALIZED;
					break;

				case MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT;
					break;

				case MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT;
					break;

				case MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK;
					break;

				case MF_E_INVALID_AKE_CHANNEL_PARAMETERS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_AKE_CHANNEL_PARAMETERS;
					break;

				case MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED;
					break;

				case MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM;
					break;

				case MF_E_DRM_MIGRATION_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DRM_MIGRATION_NOT_SUPPORTED;
					break;

				case MF_E_HDCP_AUTHENTICATION_FAILURE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HDCP_AUTHENTICATION_FAILURE;
					break;

				case MF_E_HDCP_LINK_FAILURE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HDCP_LINK_FAILURE;
					break;





					/////////////////////////////////
					//MEDIA FOUNDATION Clock errors//
					/////////////////////////////////




				case MF_E_CLOCK_INVALID_CONTINUITY_KEY:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_INVALID_CONTINUITY_KEY;
					break;

				case MF_E_CLOCK_NO_TIME_SOURCE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_NO_TIME_SOURCE;
					break;

				case MF_E_CLOCK_STATE_ALREADY_SET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_STATE_ALREADY_SET;
					break;

				case MF_E_CLOCK_NOT_SIMPLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_NOT_SIMPLE;
					break;

				case MF_S_CLOCK_STOPPED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_S_CLOCK_STOPPED;
					break;

				case MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED;
					break;

				case MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED;
					break;

				case MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED;
					break;




					//////////////////////////////////////////////
					//MEDIA FOUNDATION Quality Management errors//
					//////////////////////////////////////////////



				case MF_E_NO_MORE_DROP_MODES:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_MORE_DROP_MODES;
					break;

				case MF_E_NO_MORE_QUALITY_LEVELS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_MORE_QUALITY_LEVELS;
					break;

				case MF_E_DROPTIME_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_DROPTIME_NOT_SUPPORTED;
					break;

				case MF_E_QUALITYKNOB_WAIT_LONGER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_QUALITYKNOB_WAIT_LONGER;
					break;

				case MF_E_QM_INVALIDSTATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_QM_INVALIDSTATE;
					break;





					/////////////////////////////////////
					//MEDIA FOUNDATION Transcode errors//
					/////////////////////////////////////




				case MF_E_TRANSCODE_NO_CONTAINERTYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSCODE_NO_CONTAINERTYPE;
					break;

				case MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS;
					break;

				case MF_E_TRANSCODE_NO_MATCHING_ENCODER:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSCODE_NO_MATCHING_ENCODER;
					break;

				case MF_E_TRANSCODE_INVALID_PROFILE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TRANSCODE_INVALID_PROFILE;
					break;





					///////////////////////////////////////////
					//MEDIA FOUNDATION HW Device Proxy errors//
					///////////////////////////////////////////




				case MF_E_ALLOCATOR_NOT_INITIALIZED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ALLOCATOR_NOT_INITIALIZED;
					break;

				case MF_E_ALLOCATOR_NOT_COMMITED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ALLOCATOR_NOT_COMMITED;
					break;

				case MF_E_ALLOCATOR_ALREADY_COMMITED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_ALLOCATOR_ALREADY_COMMITED;
					break;

				case MF_E_STREAM_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_STREAM_ERROR;
					break;

				case MF_E_INVALID_STREAM_STATE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_INVALID_STREAM_STATE;
					break;

				case MF_E_HW_STREAM_NOT_CONNECTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HW_STREAM_NOT_CONNECTED;
					break;





					///////////////////////////////////////////////////////////
					//MEDIA FOUNDATION Capture Engine and MediaCapture errors//
					///////////////////////////////////////////////////////////




				case MF_E_NO_CAPTURE_DEVICES_AVAILABLE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_NO_CAPTURE_DEVICES_AVAILABLE;
					break;

				case MF_E_CAPTURE_SINK_OUTPUT_NOT_SET:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SINK_OUTPUT_NOT_SET;
					break;

				case MF_E_CAPTURE_SINK_MIRROR_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SINK_MIRROR_ERROR;
					break;

				case MF_E_CAPTURE_SINK_ROTATE_ERROR:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SINK_ROTATE_ERROR;
					break;

				case MF_E_CAPTURE_ENGINE_INVALID_OP:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_ENGINE_INVALID_OP;
					break;

				case MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED;
					break;

				case MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT;
					break;

				case MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT;
					break;

				case MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT;
					break;

				case MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS;
					break;

				case MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO;
					break;

				case MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE;
					break;

				case MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED;
					break;





					/////////////////////////////////////////////////////
					//MEDIA FOUNDATION Media Timeline Controller errors//
					/////////////////////////////////////////////////////




				case MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE;
					break;

				case MF_E_TIMELINECONTROLLER_NOT_ALLOWED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TIMELINECONTROLLER_NOT_ALLOWED;
					break;

				case MF_E_TIMELINECONTROLLER_CANNOT_ATTACH:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_TIMELINECONTROLLER_CANNOT_ATTACH;
					break;





					////////////////////////////////////////////////////////
					//MEDIA FOUNDATION MediaExtension as AppService errors//
					////////////////////////////////////////////////////////




				case MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED;
					break;

				case MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED;
					break;

				case MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED;
					break;

				case MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID;
					break;

				case MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT;
					break;


				default:
					//Define o status geral do método como ERRO.
					Resultado = false;

					//Define o ResultCode a ser retornado.
					OutStatus = ResultCode::ER_CONVERSAO_HRESULT;
					break;
				}



			Done:;
				//Define o status do enum (ResultCode)
				Param_Out_Status = OutStatus;

				//Retorna o resultado
				return Resultado;
			}

			/// <summary>
			/// Converte um código de status (ResultCode) para um (HRESULT) nativo se disponível.
			/// Caso uma tradução não esteja disponível, o valor retornado será um (E_FAIL). Para os (ResultCodes) especificos da biblioteca, o valor retornado será sempre (E_FAIL).
			/// </summary>
			/// <param name="Param_Status">O ResultCode a ser traduzido para um HRESULT.</param>
			/// <returns></returns>
			HRESULT ConverterResultCode(ResultCode Param_Status)
			{
				//Variavel que vai retornar o resultado geral da função.
				HRESULT Resultado = E_FAIL;

				//-> VERIFICA SE INICIO SE NÃO É UM CÓDIGO DE SUCESSO.

				//Verifica se é um código de sucesso.
				if (Param_Status == ResultCode::SS_OK)
				{
					//Define o código correspondente.
					Resultado = S_OK;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_FALSE)
				{
					//Define o código correspondente.
					Resultado = S_FALSE; //ER_TIMERR_NOCANDO | SS_AUDCLNT_S_BUFFER_EMPTY

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_MMSYSERR_NOERROR)
				{
					//Define o código correspondente.
					Resultado = MMSYSERR_NOERROR;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_TIMERR_NOERROR)
				{
					//Define o código correspondente.
					Resultado = TIMERR_NOERROR;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_WAIT_TIMEOUT)
				{
					//Define o código correspondente.
					Resultado = WAIT_TIMEOUT;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_WAIT_OBJECT_0)
				{
					//Define o código correspondente.
					Resultado = WAIT_OBJECT_0;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_WAIT_ABANDONED)
				{
					//Define o código correspondente.
					Resultado = WAIT_ABANDONED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_WAIT_IO_COMPLETION)
				{
					//Define o código correspondente.
					Resultado = WAIT_IO_COMPLETION;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_D3DOK_NOAUTOGEN)
				{
					//Define o código correspondente.
					Resultado = D3DOK_NOAUTOGEN;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_D3D_OK)
				{
					//Define o código correspondente.
					Resultado = D3D_OK;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_S_NOT_RESIDENT)
				{
					//Define o código correspondente.
					Resultado = S_NOT_RESIDENT;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_S_RESIDENT_IN_SHARED_MEMORY)
				{
					//Define o código correspondente.
					Resultado = S_RESIDENT_IN_SHARED_MEMORY;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_S_PRESENT_MODE_CHANGED)
				{
					//Define o código correspondente.
					Resultado = S_PRESENT_MODE_CHANGED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_S_PRESENT_OCCLUDED)
				{
					//Define o código correspondente.
					Resultado = S_PRESENT_OCCLUDED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_AUDCLNT_S_POSITION_STALLED)
				{
					//Define o código correspondente.
					Resultado = AUDCLNT_S_POSITION_STALLED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_AUDCLNT_S_THREAD_ALREADY_REGISTERED)
				{
					//Define o código correspondente.
					Resultado = AUDCLNT_S_THREAD_ALREADY_REGISTERED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_OCCLUDED)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_OCCLUDED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_MODE_CHANGED)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_MODE_CHANGED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_MODE_CHANGE_IN_PROGRESS)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_MODE_CHANGE_IN_PROGRESS;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_CLIPPED)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_CLIPPED;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_NO_REDIRECTION)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_NO_REDIRECTION;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE;

					//Sai do método
					goto Done;
				}
				else if (Param_Status == ResultCode::SS_DXGI_STATUS_NO_DESKTOP_ACCESS)
				{
					//Define o código correspondente.
					Resultado = DXGI_STATUS_NO_DESKTOP_ACCESS;

					//Sai do método
					goto Done;
				}
				else
				{
				//Deixa continuar para verificar os status de erros.
				}



				//FAZ UM SWITCH PARA VERIFICAR OS ENUMS DE ERROS DENTRO DA ENUMERAÇÃO (ResultCode)			
				switch (Param_Status)
				{
					//VALORES PROPRIOS DA BIBLIOTECA QUE SEMPRE RETORNAM - E_FAIL

				case CarenRengine::CarenCodesStatus::ResultCode::ER_CONVERSAO_HRESULT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CONVERSAO_PROPVARIANT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CONVERSAO_ESTRUTURA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CARENBUFFER_LARGURA_ESCRITA_INVALIDA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CARENBUFFER_START_INDEX_INVALIDO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CARENBUFFER_FALHA_CONVERSAO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CARENBUFFER_POINTER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_CONVERSAO_TIPO_NAO_SUPORTADO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;




				case CarenRengine::CarenCodesStatus::ResultCode::ER_GUID_INVALIDO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_PROPVARIANT_CREATE_OR_CONVERSION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_PROPVARIANT_TYPE_NO_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_NOT_SUFFICIENT_BUFFER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_NOT_SUFFICIENT_BUFFER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_ABORT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_ABORT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_NOTIMPL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_NOTIMPL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_INVALIDARG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_INVALIDARG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_OUTOFMEMORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_OUTOFMEMORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_STG_E_ACCESSDENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = STG_E_ACCESSDENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_STG_E_CANTSAVE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = STG_E_CANTSAVE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_STG_E_MEDIUMFULL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = STG_E_MEDIUMFULL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_ERROR_INVALID_FUNCTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = ERROR_INVALID_FUNCTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_ERROR_OBJECT_ALREADY_EXISTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = ERROR_OBJECT_ALREADY_EXISTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_HANDLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_HANDLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_NOINTERFACE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_NOINTERFACE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_POINTER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_POINTER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_ERROR_ALREADY_EXISTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = ERROR_ALREADY_EXISTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_NOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_NOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_ACCESSDENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_ACCESSDENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_UNEXPECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_UNEXPECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_E_PENDING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_PENDING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_FAIL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = E_FAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_DEVICE_INVALIDATED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_DEVICE_INVALIDATED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_SERVICE_NOT_RUNNING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_SERVICE_NOT_RUNNING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_WRONG_ENDPOINT_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_WRONG_ENDPOINT_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_NOT_STOPPED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_NOT_STOPPED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_EVENTHANDLE_NOT_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_EVENTHANDLE_NOT_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_ALREADY_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_ALREADY_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFFER_OPERATION_PENDING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFFER_OPERATION_PENDING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFFER_SIZE_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFFER_SIZE_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFFER_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFFER_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFFER_TOO_LARGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFFER_TOO_LARGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_INVALID_SIZE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_INVALID_SIZE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_OUT_OF_ORDER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_OUT_OF_ORDER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_CPUUSAGE_EXCEEDED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_CPUUSAGE_EXCEEDED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_DEVICE_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_DEVICE_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_ENDPOINT_CREATE_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_ENDPOINT_CREATE_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_INVALID_DEVICE_PERIOD:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_INVALID_DEVICE_PERIOD;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_UNSUPPORTED_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_UNSUPPORTED_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WAIT_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WAIT_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_TIMERR_NOCANDO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = TIMERR_NOCANDO;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_INVALIDCALL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_INVALIDCALL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_CONFLICTINGRENDERSTATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_CONFLICTINGRENDERSTATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_CONFLICTINGTEXTUREFILTER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_CONFLICTINGTEXTUREFILTER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_CONFLICTINGTEXTUREPALETTE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_CONFLICTINGTEXTUREPALETTE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DEVICEHUNG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DEVICEHUNG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DEVICELOST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DEVICELOST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DEVICENOTRESET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DEVICENOTRESET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DEVICEREMOVED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DEVICEREMOVED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DRIVERINTERNALERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DRIVERINTERNALERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_DRIVERINVALIDCALL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_DRIVERINVALIDCALL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_INVALIDDEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_INVALIDDEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_MOREDATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_MOREDATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_NOTAVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_NOTAVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_NOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_NOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_OUTOFVIDEOMEMORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_OUTOFVIDEOMEMORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_TOOMANYOPERATIONS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_TOOMANYOPERATIONS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDALPHAARG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDALPHAARG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDALPHAOPERATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDALPHAOPERATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDCOLORARG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDCOLORARG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDCOLOROPERATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDCOLOROPERATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDFACTORVALUE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDFACTORVALUE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDTEXTUREFILTER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDTEXTUREFILTER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_WASSTILLDRAWING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_WASSTILLDRAWING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_WRONGTEXTUREFORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_WRONGTEXTUREFORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDOVERLAY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDOVERLAY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDOVERLAYFORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDOVERLAYFORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_CANNOTPROTECTCONTENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_CANNOTPROTECTCONTENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_UNSUPPORTEDCRYPTO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_UNSUPPORTEDCRYPTO;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3DERR_PRESENT_STATISTICS_DISJOINT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3DERR_PRESENT_STATISTICS_DISJOINT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_WAS_STILL_DRAWING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_WAS_STILL_DRAWING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_INVALID_CALL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_INVALID_CALL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_OCCLUDED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_OCCLUDED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_MODE_CHANGED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_MODE_CHANGED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_MODE_CHANGE_IN_PROGRESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_MODE_CHANGE_IN_PROGRESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_CLIPPED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_CLIPPED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_NO_REDIRECTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_NO_REDIRECTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_DXGI_STATUS_NO_DESKTOP_ACCESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_NO_DESKTOP_ACCESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXVA2_E_VIDEO_DEVICE_LOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXVA2_E_VIDEO_DEVICE_LOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXVA2_E_NEW_VIDEO_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXVA2_E_NEW_VIDEO_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXVA2_E_NOT_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXVA2_E_NOT_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXVA2_E_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXVA2_E_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NONEXCLUSIVE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NONEXCLUSIVE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_DEVICE_REMOVED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_DEVICE_REMOVED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_DEVICE_HUNG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_DEVICE_HUNG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_DEVICE_RESET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_DEVICE_RESET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_DRIVER_INTERNAL_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_DRIVER_INTERNAL_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_WAIT_TIMEOUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_WAIT_TIMEOUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_SESSION_DISCONNECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_SESSION_DISCONNECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_SDK_COMPONENT_MISSING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_SDK_COMPONENT_MISSING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_REMOTE_OUTOFMEMORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_REMOTE_OUTOFMEMORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NOT_CURRENTLY_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NAME_ALREADY_EXISTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NAME_ALREADY_EXISTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_MORE_DATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_MORE_DATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_FRAME_STATISTICS_DISJOINT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_FRAME_STATISTICS_DISJOINT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_CANNOT_PROTECT_CONTENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_CANNOT_PROTECT_CONTENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_ALREADY_EXISTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_ALREADY_EXISTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_ACCESS_LOST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_ACCESS_LOST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_ACCESS_DENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_ACCESS_DENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_STATUS_DDA_WAS_STILL_DRAWING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_STATUS_DDA_WAS_STILL_DRAWING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NOT_CURRENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NOT_CURRENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_HW_PROTECTION_OUTOFMEMORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_DYNAMIC_CODE_POLICY_VIOLATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_NON_COMPOSITED_UI:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_NON_COMPOSITED_UI;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_CACHE_CORRUPT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_CACHE_CORRUPT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_CACHE_FULL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_CACHE_FULL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_ERROR_CACHE_HASH_COLLISION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_ERROR_CACHE_HASH_COLLISION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_DDI_ERR_WASSTILLDRAWING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_DDI_ERR_WASSTILLDRAWING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_DDI_ERR_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_DDI_ERR_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_DXGI_DDI_ERR_NONEXCLUSIVE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = DXGI_DDI_ERR_NONEXCLUSIVE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_WRONG_STATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_WRONG_STATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_UNSUPPORTED_OPERATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_UNSUPPORTED_OPERATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_SCANNER_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_SCANNER_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_SCREEN_ACCESS_DENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_SCREEN_ACCESS_DENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_DISPLAY_STATE_INVALID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_DISPLAY_STATE_INVALID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_ZERO_VECTOR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_ZERO_VECTOR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INTERNAL_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INTERNAL_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_CALL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_CALL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_NO_HARDWARE_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_NO_HARDWARE_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_RECREATE_TARGET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_RECREATE_TARGET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_TOO_MANY_SHADER_ELEMENTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_TOO_MANY_SHADER_ELEMENTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_SHADER_COMPILE_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_SHADER_COMPILE_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_MAX_TEXTURE_SIZE_EXCEEDED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_MAX_TEXTURE_SIZE_EXCEEDED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_UNSUPPORTED_VERSION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_UNSUPPORTED_VERSION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_BAD_NUMBER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_BAD_NUMBER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_WRONG_FACTORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_WRONG_FACTORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_LAYER_ALREADY_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_LAYER_ALREADY_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_POP_CALL_DID_NOT_MATCH_PUSH:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_POP_CALL_DID_NOT_MATCH_PUSH;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_WRONG_RESOURCE_DOMAIN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_WRONG_RESOURCE_DOMAIN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_PUSH_POP_UNBALANCED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_PUSH_POP_UNBALANCED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INCOMPATIBLE_BRUSH_TYPES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INCOMPATIBLE_BRUSH_TYPES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_WIN32_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_WIN32_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_TARGET_NOT_GDI_COMPATIBLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_TARGET_NOT_GDI_COMPATIBLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_TEXT_EFFECT_IS_WRONG_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_TEXT_EFFECT_IS_WRONG_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_TEXT_RENDERER_NOT_RELEASED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_TEXT_RENDERER_NOT_RELEASED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_EXCEEDS_MAX_BITMAP_SIZE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_EXCEEDS_MAX_BITMAP_SIZE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_GRAPH_CONFIGURATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_GRAPH_CONFIGURATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_INTERNAL_GRAPH_CONFIGURATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_INTERNAL_GRAPH_CONFIGURATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_CYCLIC_GRAPH:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_CYCLIC_GRAPH;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_BITMAP_CANNOT_DRAW:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_BITMAP_CANNOT_DRAW;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_OUTSTANDING_BITMAP_REFERENCES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_OUTSTANDING_BITMAP_REFERENCES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_ORIGINAL_TARGET_NOT_BOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_ORIGINAL_TARGET_NOT_BOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_TARGET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_TARGET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_BITMAP_BOUND_AS_TARGET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_BITMAP_BOUND_AS_TARGET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INSUFFICIENT_DEVICE_CAPABILITIES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INTERMEDIATE_TOO_LARGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INTERMEDIATE_TOO_LARGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_EFFECT_IS_NOT_REGISTERED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_EFFECT_IS_NOT_REGISTERED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_PROPERTY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_PROPERTY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_NO_SUBPROPERTIES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_NO_SUBPROPERTIES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_PRINT_JOB_CLOSED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_PRINT_JOB_CLOSED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_PRINT_FORMAT_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_PRINT_FORMAT_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_TOO_MANY_TRANSFORM_INPUTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_TOO_MANY_TRANSFORM_INPUTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D2DERR_INVALID_GLYPH_IMAGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D2DERR_INVALID_GLYPH_IMAGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_D3D11_ERROR_FILE_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = D3D11_ERROR_FILE_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_MULTIPLE_BEGIN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_MULTIPLE_BEGIN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_ASF_PARSEINPROGRESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_ASF_PARSEINPROGRESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_I_MANUAL_PROXY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_I_MANUAL_PROXY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_PROTECTION_NOT_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_PROTECTION_NOT_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_WAIT_FOR_POLICY_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_WAIT_FOR_POLICY_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_SINK_NOT_FINALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_SINK_NOT_FINALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_PE_TRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_PE_TRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_SEQUENCER_CONTEXT_CANCELED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_SEQUENCER_CONTEXT_CANCELED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::SS_MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_INVALID_TIME_ATTRIBUTES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_INVALID_TIME_ATTRIBUTES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SESSION_PAUSEWHILESTOPPED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SESSION_PAUSEWHILESTOPPED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NOTACCEPTING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NOTACCEPTING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDREQUEST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDREQUEST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SAMPLEALLOCATOR_EMPTY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SAMPLEALLOCATOR_EMPTY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_RATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_RATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_RATE_TRANSITION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_RATE_TRANSITION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_REVERSE_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_REVERSE_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_THINNING_UNSUPPORTEDE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_THINNING_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDINDEX:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDINDEX;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_SERVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_SERVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_SOURCE_WRONGSTATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_SOURCE_WRONGSTATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_END_OF_STREAM:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_END_OF_STREAM;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_SCHEME:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_SCHEME;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BYTESTREAM_NOT_SEEKABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BYTESTREAM_NOT_SEEKABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_BYTESTREAM_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_BYTESTREAM_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_OUTOFRANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_OUTOFRANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HW_MFT_FAILED_START_STREAMING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HW_MFT_FAILED_START_STREAMING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_TIME_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_TIME_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_STATE_TRANSITION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_STATE_TRANSITION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_WORKQUEUE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_WORKQUEUE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_EVENTS_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_EVENTS_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MULTIPLE_SUBSCRIBERS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MULTIPLE_SUBSCRIBERS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MULTIPLE_BEGIN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MULTIPLE_BEGIN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STREAMSINK_REMOVED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STREAMSINK_REMOVED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_NOT_SIMPLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_NOT_SIMPLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_CLOCK:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_CLOCK;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_NO_TIME_SOURCE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_NO_TIME_SOURCE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_STATE_ALREADY_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_STATE_ALREADY_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SHUTDOWN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SHUTDOWN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDSTREAMNUMBER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDSTREAMNUMBER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_INPUT_REMAINING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_INPUT_REMAINING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_MORE_TYPES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_MORE_TYPES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_TYPE_NOT_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_TYPE_NOT_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_NEED_MORE_INPUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_NEED_MORE_INPUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_STREAM_CHANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_STREAM_CHANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STREAMSINK_EXISTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STREAMSINK_EXISTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STREAMSINKS_FIXED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STREAMSINKS_FIXED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDTYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDTYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ATTRIBUTENOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ATTRIBUTENOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BUFFERTOOSMALL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BUFFERTOOSMALL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_CODEC_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_CODEC_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDMEDIATYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDMEDIATYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_SAMPLE_DURATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_SAMPLE_DURATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_SAMPLE_TIMESTAMP:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_SAMPLE_TIMESTAMP;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_TIMESTAMP:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_TIMESTAMP;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_D3D_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_D3D_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DXGI_VIDEO_DEVICE_LOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DXGI_VIDEO_DEVICE_LOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DXGI_NEW_VIDEO_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DXGI_NEW_VIDEO_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DXGI_DEVICE_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DXGI_DEVICE_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LICENSE_INCORRECT_RIGHTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LICENSE_INCORRECT_RIGHTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PLATFORM_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PLATFORM_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_REPRESENTATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_REPRESENTATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNEXPECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNEXPECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALIDNAME:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALIDNAME;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_FILE_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_FILE_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_STREAM_DATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_STREAM_DATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_UNAVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_UNAVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_THINNING_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_THINNING_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RATE_CHANGE_PREEMPTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RATE_CHANGE_PREEMPTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NOT_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NOT_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TIMER_ORPHANED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TIMER_ORPHANED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STATE_TRANSITION_PENDING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STATE_TRANSITION_PENDING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_STATE_TRANSITION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_STATE_TRANSITION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNRECOVERABLE_ERROR_OCCURRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNRECOVERABLE_ERROR_OCCURRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SAMPLE_NOT_WRITABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SAMPLE_NOT_WRITABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_KEY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_KEY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BAD_STARTUP_VERSION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BAD_STARTUP_VERSION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_CAPTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_CAPTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_POSITION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_POSITION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_TYPE_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_TYPE_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_TYPE_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_TYPE_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_EMPTY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_EMPTY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_NOT_EMPTY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_NOT_EMPTY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_VECTOR_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_VECTOR_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_VECTOR_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_VECTOR_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OPERATION_CANCELLED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OPERATION_CANCELLED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DISABLED_IN_SAFEMODE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DISABLED_IN_SAFEMODE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CANNOT_PARSE_BYTESTREAM:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CANNOT_PARSE_BYTESTREAM;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIAPROC_WRONGSTATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIAPROC_WRONGSTATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_THROUGHPUT_NOT_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_THROUGHPUT_NOT_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_TOO_MANY_CLASSES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_TOO_MANY_CLASSES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_WOULDBLOCK:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_WOULDBLOCK;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_BITPUMP:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_BITPUMP;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_OUTOFMEMORY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_OUTOFMEMORY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INSUFFICIENT_BUFFER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INSUFFICIENT_BUFFER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CANNOT_CREATE_SINK:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CANNOT_CREATE_SINK;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BYTESTREAM_UNKNOWN_LENGTH:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BYTESTREAM_UNKNOWN_LENGTH;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_S_ACTIVATE_REPLACED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_ACTIVATE_REPLACED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_FORMAT_CHANGE_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_FORMAT_CHANGE_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DRM_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DRM_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNAUTHORIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNAUTHORIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OUT_OF_RANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OUT_OF_RANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_CODEC_MERIT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_CODEC_MERIT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OPERATION_IN_PROGRESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OPERATION_IN_PROGRESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HARDWARE_DRM_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HARDWARE_DRM_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DURATION_TOO_LONG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DURATION_TOO_LONG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_PARSINGINCOMPLETE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_PARSINGINCOMPLETE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_MISSINGDATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_MISSINGDATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_INVALIDDATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_INVALIDDATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_OPAQUEPACKET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_OPAQUEPACKET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_NOINDEX:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_NOINDEX;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_INDEXNOTLOADED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_INDEXNOTLOADED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_TOO_MANY_PAYLOADS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_TOO_MANY_PAYLOADS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_UNSUPPORTED_STREAM_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_UNSUPPORTED_STREAM_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_DROPPED_PACKET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_DROPPED_PACKET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MP3_NOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MP3_NOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MP3_OUTOFDATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MP3_OUTOFDATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MP3_NOTMP3:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MP3_NOTMP3;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MP3_NOTSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MP3_NOTSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_DURATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_DURATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_READ_ONLY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_READ_ONLY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROPERTY_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROPERTY_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_SOURCE_NOT_STARTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_SOURCE_NOT_STARTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MP3_BAD_CRC:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MP3_BAD_CRC;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NOT_PROTECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NOT_PROTECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CANNOT_FIND_KEYFRAME_SAMPLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CANNOT_FIND_KEYFRAME_SAMPLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_CHARACTERISTICS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_CHARACTERISTICS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_AUDIO_RECORDING_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_AUDIO_RECORDING_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_RECORDING_DEVICE_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_RECORDING_DEVICE_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NETWORK_RESOURCE_FAILURE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NETWORK_RESOURCE_FAILURE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_WRITE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_WRITE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_READ:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_READ;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_REQUIRE_NETWORK:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_REQUIRE_NETWORK;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_REQUIRE_ASYNC:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_REQUIRE_ASYNC;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_BWLEVEL_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_BWLEVEL_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_STREAMGROUPS_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_STREAMGROUPS_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_MANUALSS_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_MANUALSS_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_CACHESTREAM_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_CACHESTREAM_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_REQUIRE_INPUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_REQUIRE_INPUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_REDIRECT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_REDIRECT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_REDIRECT_TO_PROXY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_REDIRECT_TO_PROXY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_TOO_MANY_REDIRECTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_TOO_MANY_REDIRECTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_TIMEOUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_TIMEOUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_CLIENT_CLOSE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_CLIENT_CLOSE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_BAD_CONTROL_DATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_BAD_CONTROL_DATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INCOMPATIBLE_SERVER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INCOMPATIBLE_SERVER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_UNSAFE_URL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_UNSAFE_URL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_CACHE_NO_DATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_CACHE_NO_DATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_EOL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_EOL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_BAD_REQUEST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_BAD_REQUEST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INTERNAL_SERVER_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INTERNAL_SERVER_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_SESSION_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_SESSION_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_NOCONNECTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_NOCONNECTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_CONNECTION_FAILURE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_CONNECTION_FAILURE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INCOMPATIBLE_PUSHSERVER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INCOMPATIBLE_PUSHSERVER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_SERVER_ACCESSDENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_SERVER_ACCESSDENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_PROXY_ACCESSDENIED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_PROXY_ACCESSDENIED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_CANNOTCONNECT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_CANNOTCONNECT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INVALID_PUSH_TEMPLATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INVALID_PUSH_TEMPLATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_INVALID_PUSH_PUBLISHING_POINT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_INVALID_PUSH_PUBLISHING_POINT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_BUSY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_BUSY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_RESOURCE_GONE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_RESOURCE_GONE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_ERROR_FROM_PROXY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_ERROR_FROM_PROXY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_PROXY_TIMEOUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_PROXY_TIMEOUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_SERVER_UNAVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_SERVER_UNAVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_TOO_MUCH_DATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_TOO_MUCH_DATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_SESSION_INVALID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_SESSION_INVALID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OFFLINE_MODE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OFFLINE_MODE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_UDP_BLOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_UDP_BLOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_UNSUPPORTED_CONFIGURATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_UNSUPPORTED_CONFIGURATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_PROTOCOL_DISABLED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_PROTOCOL_DISABLED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NET_COMPANION_DRIVER_DISCONNECT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NET_COMPANION_DRIVER_DISCONNECT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ALREADY_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ALREADY_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BANDWIDTH_OVERRUN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BANDWIDTH_OVERRUN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LATE_SAMPLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LATE_SAMPLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_FLUSH_NEEDED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_FLUSH_NEEDED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_PROFILE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_PROFILE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INDEX_NOT_COMMITTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INDEX_NOT_COMMITTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_INDEX:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_INDEX;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CANNOT_INDEX_IN_PLACE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CANNOT_INDEX_IN_PLACE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MISSING_ASF_LEAKYBUCKET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MISSING_ASF_LEAKYBUCKET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_ASF_STREAMID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_ASF_STREAMID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STREAMSINKS_OUT_OF_SYNC:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STREAMSINKS_OUT_OF_SYNC;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SAMPLEALLOCATOR_CANCELED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SAMPLEALLOCATOR_CANCELED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SINK_ALREADYSTOPPED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SINK_ALREADYSTOPPED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ASF_FILESINK_BITRATE_UNKNOWN:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ASF_FILESINK_BITRATE_UNKNOWN;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SINK_NO_STREAMS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SINK_NO_STREAMS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_METADATA_TOO_LONG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_METADATA_TOO_LONG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SINK_NO_SAMPLES_PROCESSED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SINK_NO_SAMPLES_PROCESSED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SINK_HEADERS_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SINK_HEADERS_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_REN_NO_PROCAMP_HW:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_REN_NO_PROCAMP_HW;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_REN_NO_DEINTERLACE_HW:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_REN_NO_DEINTERLACE_HW;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_REN_COPYPROT_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_REN_COPYPROT_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_REN_SURFACE_NOT_SHARED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_REN_SURFACE_NOT_SHARED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_VIDEO_DEVICE_LOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_VIDEO_DEVICE_LOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NEW_VIDEO_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NEW_VIDEO_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_VIDEO_SAMPLE_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_VIDEO_SAMPLE_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_AUDIO_PLAYBACK_DEVICE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_AUDIO_PLAYBACK_DEVICE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_SERVICE_NOT_RUNNING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_SERVICE_NOT_RUNNING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_BUFFER_SIZE_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_BUFFER_SIZE_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_INVALID_OPTIONAL_NODE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_INVALID_OPTIONAL_NODE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_CANNOT_FIND_DECRYPTOR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_CANNOT_FIND_DECRYPTOR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_CANNOT_CONNECT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_CANNOT_CONNECT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_LOOPS_IN_TOPOLOGY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_LOOPS_IN_TOPOLOGY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_MISSING_STREAM_DESCRIPTOR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_MISSING_STREAM_DESCRIPTOR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPO_MISSING_SOURCE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPO_MISSING_SOURCE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_SOURCE_IN_CACHE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_SOURCE_IN_CACHE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROFILE_MISSING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROFILE_MISSING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROFILE_TRUNCATED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROFILE_TRUNCATED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_ASYNC_LOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_ASYNC_LOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LICENSE_OUTOFDATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LICENSE_OUTOFDATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LICENSE_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LICENSE_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DRM_HARDWARE_INCONSISTENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DRM_HARDWARE_INCONSISTENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_CONTENT_PROTECTION_MANAGER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_CONTENT_PROTECTION_MANAGER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LICENSE_RESTORE_NO_RIGHTS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LICENSE_RESTORE_NO_RIGHTS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BACKUP_RESTRICTED_LICENSE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BACKUP_RESTRICTED_LICENSE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_COMPONENT_REVOKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_COMPONENT_REVOKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRUST_DISABLED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRUST_DISABLED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_NO_ACTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_NO_ACTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_ACTION_ALREADY_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_ACTION_ALREADY_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_ACTION_MISMATCH:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_ACTION_MISMATCH;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_WMDRMOTA_INVALID_POLICY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_WMDRMOTA_INVALID_POLICY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_POLICY_UNSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_POLICY_UNSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_OPL_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_OPL_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TOPOLOGY_VERIFICATION_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TOPOLOGY_VERIFICATION_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_SIGNATURE_VERIFICATION_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_SIGNATURE_VERIFICATION_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DEBUGGING_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DEBUGGING_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CODE_EXPIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CODE_EXPIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_VERSION_TOO_LOW:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_VERSION_TOO_LOW;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_RENEWAL_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_RENEWAL_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_KERNEL_UNTRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_KERNEL_UNTRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PEAUTH_UNTRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PEAUTH_UNTRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NON_PE_PROCESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NON_PE_PROCESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_REBOOT_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_REBOOT_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_INVALID_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_INVALID_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_UNRECOGNIZED_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_UNRECOGNIZED_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ALL_PROCESS_RESTART_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ALL_PROCESS_RESTART_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PROCESS_RESTART_REQUIRED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PROCESS_RESTART_REQUIRED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_USERMODE_UNTRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_USERMODE_UNTRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PEAUTH_SESSION_NOT_STARTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PEAUTH_SESSION_NOT_STARTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PEAUTH_PUBLICKEY_REVOKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PEAUTH_PUBLICKEY_REVOKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_GRL_ABSENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_GRL_ABSENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_S_PE_TRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_PE_TRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PE_UNTRUSTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PE_UNTRUSTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PEAUTH_NOT_STARTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PEAUTH_NOT_STARTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INCOMPATIBLE_SAMPLE_PROTECTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INCOMPATIBLE_SAMPLE_PROTECTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_PE_SESSIONS_MAXED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_PE_SESSIONS_MAXED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_UNSUPPORTED_ACTION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_UNSUPPORTED_ACTION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_BAD_OPL_STRUCTURE_FORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_BAD_OPL_STRUCTURE_FORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_PMP_HOST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_PMP_HOST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_OPL_DATA_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_OPL_DATA_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_AKE_CHANNEL_PARAMETERS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_AKE_CHANNEL_PARAMETERS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DRM_MIGRATION_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DRM_MIGRATION_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HDCP_AUTHENTICATION_FAILURE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HDCP_AUTHENTICATION_FAILURE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HDCP_LINK_FAILURE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HDCP_LINK_FAILURE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_INVALID_CONTINUITY_KEY:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_INVALID_CONTINUITY_KEY;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_S_CLOCK_STOPPED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_S_CLOCK_STOPPED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_MORE_DROP_MODES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_MORE_DROP_MODES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_MORE_QUALITY_LEVELS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_MORE_QUALITY_LEVELS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_DROPTIME_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_DROPTIME_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_QUALITYKNOB_WAIT_LONGER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_QUALITYKNOB_WAIT_LONGER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_QM_INVALIDSTATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_QM_INVALIDSTATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSCODE_NO_CONTAINERTYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSCODE_NO_CONTAINERTYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSCODE_NO_MATCHING_ENCODER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSCODE_NO_MATCHING_ENCODER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TRANSCODE_INVALID_PROFILE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TRANSCODE_INVALID_PROFILE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ALLOCATOR_NOT_INITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ALLOCATOR_NOT_INITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ALLOCATOR_NOT_COMMITED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ALLOCATOR_NOT_COMMITED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_ALLOCATOR_ALREADY_COMMITED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_ALLOCATOR_ALREADY_COMMITED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_STREAM_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_STREAM_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_INVALID_STREAM_STATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_INVALID_STREAM_STATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HW_STREAM_NOT_CONNECTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HW_STREAM_NOT_CONNECTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_NO_CAPTURE_DEVICES_AVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_NO_CAPTURE_DEVICES_AVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SINK_OUTPUT_NOT_SET:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SINK_OUTPUT_NOT_SET;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SINK_MIRROR_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SINK_MIRROR_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SINK_ROTATE_ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SINK_ROTATE_ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_ENGINE_INVALID_OP:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_ENGINE_INVALID_OP;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TIMELINECONTROLLER_NOT_ALLOWED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TIMELINECONTROLLER_NOT_ALLOWED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_TIMELINECONTROLLER_CANNOT_ATTACH:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_TIMELINECONTROLLER_CANNOT_ATTACH;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT;
					break;

					

					//WIC ERROS



				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_WRONGSTATE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_WRONGSTATE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_VALUEOUTOFRANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_VALUEOUTOFRANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_UNKNOWNIMAGEFORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_UNKNOWNIMAGEFORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_NOTINITIALIZED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_NOTINITIALIZED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_ALREADYLOCKED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_ALREADYLOCKED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_PROPERTYNOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_PROPERTYNOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_PROPERTYNOTSUPPORTED:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_PROPERTYNOTSUPPORTED;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_PROPERTYSIZE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_PROPERTYSIZE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_CODECPRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_CODECPRESENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_CODECNOTHUMBNAIL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_CODECNOTHUMBNAIL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_PALETTEUNAVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_PALETTEUNAVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_CODECTOOMANYSCANLINES:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_CODECTOOMANYSCANLINES;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INTERNALERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INTERNALERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_COMPONENTNOTFOUND:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_COMPONENTNOTFOUND;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_IMAGESIZEOUTOFRANGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_IMAGESIZEOUTOFRANGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_TOOMUCHMETADATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_TOOMUCHMETADATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_BADIMAGE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_BADIMAGE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_BADHEADER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_BADHEADER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_FRAMEMISSING:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_FRAMEMISSING;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_BADMETADATAHEADER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_BADMETADATAHEADER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_BADSTREAMDATA:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_BADSTREAMDATA;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_STREAMWRITE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_STREAMWRITE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_STREAMREAD:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_STREAMREAD;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_STREAMNOTAVAILABLE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_STREAMNOTAVAILABLE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_UNSUPPORTEDOPERATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_UNSUPPORTEDOPERATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INVALIDREGISTRATION:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INVALIDREGISTRATION;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_COMPONENTINITIALIZEFAILURE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_COMPONENTINITIALIZEFAILURE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INSUFFICIENTBUFFER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INSUFFICIENTBUFFER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_DUPLICATEMETADATAPRESENT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_DUPLICATEMETADATAPRESENT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_UNEXPECTEDSIZE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_UNEXPECTEDSIZE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INVALIDQUERYREQUEST:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INVALIDQUERYREQUEST;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_UNEXPECTEDMETADATATYPE:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_UNEXPECTEDMETADATATYPE;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INVALIDQUERYCHARACTER:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INVALIDQUERYCHARACTER;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_WIN32ERROR:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_WIN32ERROR;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INVALIDPROGRESSIVELEVEL:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INVALIDPROGRESSIVELEVEL;
					break;
				case CarenRengine::CarenCodesStatus::ResultCode::ER_WINCODEC_ERR_INVALIDJPEGSCANINDEX:
					//Define o código HRESULT referente ao ResultCode informado.
					Resultado = WINCODEC_ERR_INVALIDJPEGSCANINDEX;
					break;
				default:
					//Como o erro não foi reconhecido, vai definir como (E_FAIL.)
					Resultado = E_FAIL;
					break;
				}

			Done:;
				//Retorna o resultado
				return Resultado;
			}
		};

		/// <summary>
		/// Estrutura responsável por representar o sistema de status utilizado para retornar o resultado das operações nas interfaces da biblioteca.
		/// </summary>
		public value struct CarenResult
		{
			//Variaveis que guardam os valores das propriedades. 
		private:
			ResultCode Glob_PropValue_StatusCode;
			HRESULT Glob_PropValue_HRESULT;
			Boolean Glob_PropValue_Resultado;

			//Inicialização da estrutura.
		public:
			/// <summary>
			/// Inicializa a estrutura passando informações sobre o resultado de uma operação.
			/// </summary>
			/// <param name="Param_StatusCode">O status do método.</param>
			/// <param name="Param_Resultado">Um valor booleano que define o status geral da operação.</param>
			CarenResult(ResultCode Param_StatusCode, Boolean Param_Resultado)
			{
				//Variavel que realiza as operações no código de status.
				ResultCodeState CheckStatus;

				//Define os valores.
				Glob_PropValue_StatusCode = Param_StatusCode;
				Glob_PropValue_Resultado = Param_Resultado;

				//Converte o ResultCode para um HRESULT.
				Glob_PropValue_HRESULT = CheckStatus.ConverterResultCode(Param_StatusCode);
			}
			/// <summary>
			/// Inicializa a estrutura passando informações sobre o resultado de uma operação.
			/// </summary>
			/// <param name="Param_StatusCode">Um código(HRESULT) a ser definido como o status da operação.</param>
			/// <param name="Param_Resultado">Um valor booleano que define o status geral da operação.</param>
			CarenResult(Int64 Param_StatusCode, Boolean Param_Resultado)
			{
				//Variavel que realiza as operações no código de status.
				ResultCodeState CheckStatus;

				//Define os valores.
				Glob_PropValue_Resultado = Param_Resultado;

				//Define o HRESULT e obtém o ResultCode que representa o código.
				Glob_PropValue_HRESULT = CheckStatus.VerificarStatus(static_cast<HRESULT>(Param_StatusCode), Glob_PropValue_StatusCode);
			}


			//Propriedades.
		public:
			/// <summary>
			/// Propriedade que retorna uma enumeração indicando o status do resultado da operação.
			/// </summary>
			property ResultCode StatusCode
			{
				ResultCode get() { return Glob_PropValue_StatusCode; }
			}

			/// <summary>
			/// Propriedade que armazena o código(HRESULT) gerado pelo método nativo na chamada.
			/// </summary>
			property Int64 HResult
			{
				Int64 get() { return static_cast<Int64>(Glob_PropValue_HRESULT); }
			}

			/// <summary>
			/// Propriedade que armazena um valor Booleano que define se o método foi executado com sucesso. Atenção, esse valor indica somente o sucesso da execução de um método, apenas 
			/// as propriedades (StatusCode e HResult)podem informar se a execução da operação foi como o esperado.
			/// </summary>
			property Boolean Resultado
			{
				Boolean get() { return Glob_PropValue_Resultado; }
			}

			//Métodos privados e auxiliares.
		private:
			//Método responsável por traduzir em mensagem o código de erro.
			String^ TranslateCodeResult(HRESULT Param_HResultCode)
			{
				//Variavel que vai conter a mensagem.
				LPCTSTR MensagemHResult = NULL;;
				String^ MsgHResult = nullptr;

				//Variavel que vai ser utilizada para obter a mensagem.
				_com_error Err = (Param_HResultCode);

				//Verifica se existe algum erro
				if (Param_HResultCode == 0)
				{
					//Sai do método.
					goto Done;
				}

				//Obtém a mensagem de erro.
				MensagemHResult = Err.ErrorMessage();

				//Verifica se é valida
				if (MensagemHResult != NULL)
				{
					//Define a mensagem de retorno.
					MsgHResult = gcnew String(MensagemHResult);
				}
				else
				{
					//Mensagem não disponivel.
				}

			Done:;
				//Retorna o resultado.
				return MsgHResult;
			}


			//Métodos publicos
		public:
			/// <summary>
			/// Associa um código HRESULT a estrutura.
			/// </summary>
			/// <param name="Param_HRESULT">O código da operação a ser definido.</param>
			/// <param name="Param_Resultado">Um valor Booleano que indica se o método foi executado com sucesso. O valor não indica diretamente se o resultado foi o esperado.</param>
			void AdicionarCodigo(Int64 Param_HRESULT, Boolean Param_Resultado)
			{
				//Define os dados nos valores das propriedades
				Glob_PropValue_HRESULT = static_cast<HRESULT>(Param_HRESULT);
				Glob_PropValue_Resultado = Param_Resultado;

				//Verifica se o resultado é true.. Se for vai definir o HResult como sucesso.
				if (Param_Resultado)
				{
					//Define como sucesso.
					Glob_PropValue_HRESULT = S_OK;
				}
			}

			/// <summary>
			/// Associa um código (ResultCode) a estrutura.
			/// </summary>
			/// <param name="Param_StatusCode">O Status Code a ser definido.</param>
			/// <param name="Param_Resultado">Um valor Booleano que indica se o método foi executado com sucesso. O valor não indica diretamente se o resultado foi o esperado.</param>
			void AdicionarCodigo(ResultCode Param_StatusCode, Boolean Param_Resultado)
			{
				//Define os dados nos valores das propriedades
				Glob_PropValue_StatusCode = Param_StatusCode;
				Glob_PropValue_Resultado = Param_Resultado;

				//Verifica se o resultado é true.. Se for vai definir o HResult como sucesso.
				if (Param_Resultado)
				{
					//Define como sucesso.
					Glob_PropValue_HRESULT = S_OK;
				}
			}

			/// <summary>
			/// Processa um código HRESULT e traduz os seu valor para um (ResultCode) se disponível e define o valor da propriedade (Resultado) automaticamente.
			/// </summary>
			/// <param name="Param_HRESULT">>O código da operação a ser definido.</param>
			void ProcessarCodigoOperacao(Int64 Param_HRESULT)
			{
				//Classe de verificação dos códigos de Status.
				ResultCodeState CheckStatus;

				//Define o HRESULT na variavel de valor da propriedade.
				Glob_PropValue_HRESULT = static_cast<HRESULT>(Param_HRESULT);

				//Processa o código HRESULT e obtém um valor da enumeração (ResultCode) para a propriedade (StatusCode).
				Glob_PropValue_Resultado = CheckStatus.VerificarStatus(Glob_PropValue_HRESULT, Glob_PropValue_StatusCode);
			}

			/// <summary>
			/// Método responsável por tentar traduzir o código HRESULT da propriedade (HResult) para uma representação da enumeração (ResultCode) para a propriedade (StatusCode).
			/// </summary>
			void TraduzirHRESULT()
			{
				//Classe de verificação dos códigos de Status.
				ResultCodeState CheckStatus;

				//Chama o método para tentar realizar a operação.
				CheckStatus.VerificarStatus(Glob_PropValue_HRESULT, Glob_PropValue_StatusCode);
			}

			/// <summary>
			/// Método responsável por tentar traduzir o ResultCode da propriedade (StatusCode) para uma representação nativa (HRESULT) para a propriedade (HResult).
			/// </summary>
			void TraduzirStatusCode()
			{
				//Classe de verificação dos códigos de Status.
				ResultCodeState CheckStatus;

				//Chama o método para tentar realizar a operação.
				Glob_PropValue_HRESULT = CheckStatus.ConverterResultCode(Glob_PropValue_StatusCode);
			}

			/// <summary>
			/// Método responsável por tentar obter uma mensagem associada a um código de erro da plataforma.
			/// </summary>
			/// <param name="Param_CodigoHResult">O código de erro a ser obtido a mensagem associada.</param>
			/// <returns></returns>
			String^ ObterMensagem(long Param_CodigoHResult)
			{
				//Tenta obter a mensagem e retorna ao chamador.
				return TranslateCodeResult(Param_CodigoHResult);
			}

			/// <summary>
			/// Limpa todos os códigos e mensagens da instancia atual.
			/// </summary>
			void Resetar()
			{
				Glob_PropValue_StatusCode = ResultCode::ER_FAIL;
				Glob_PropValue_HRESULT = E_FAIL;
				Glob_PropValue_Resultado = false;
			}
		};
	}
}