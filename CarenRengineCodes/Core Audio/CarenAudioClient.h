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
#include "..\SDK_CoreAudio.h"
#include "..\Caren\Caren.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da WSAPI.
using namespace CarenRengine::CoreAudio;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por criar e inicializar um fluxo de áudio entre um aplicativo de áudio e o mecanismo de áudio (para um fluxo de modo compartilhado) ou o buffer de hardware de um dispositivo de ponto de 
/// extremidade de áudio (para um modo exclusivo fluxo)
/// </summary>
public ref class CarenAudioClient :public ICarenAudioClient
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IAudioClient).
	IAudioClient* PonteiroTrabalho = NULL;



	//Contrutor e destruidor da classe.
public:
	~CarenAudioClient();


	//Variaveis Internas.
internal:
	//Variavel que contém o valor da propriedade (DisposedClasse)
	Boolean Prop_DisposedClasse = false;

	//Variavel que vai conter o ultimo código HRESULT retornado.
	Int32 Var_Glob_LAST_HRESULT = 0;


	//Variaveis publicas
public:
	/// <summary>
	/// Propriedade que contém a varivel que define se a classe for descartada ou não.
	/// Por padrão, o valor é falso.
	/// </summary>
	property Boolean DisposedClasse
	{
		virtual Boolean get()
		{
			//Retorna o valor.
			return Prop_DisposedClasse;
		}
	}



	//Cria uma instância dessa classe (Estático)
public:
	/// <summary>
	/// Cria uma instância vazia do Audio Cliente.
	/// </summary>
	/// <param name="Param_Out_Interface">Retorna a interface vazia. Chamadas para está interface vai resultar em exceção
	/// se nenhum ponteiro for definido.</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenAudioClient^% Param_Out_Interface)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface vazia
		Param_Out_Interface = gcnew CarenAudioClient();

		//Define sucesso na operção.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado.
		return Resultado;
	}


	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface (ICaren)
public:
	/// <summary>
	/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
	/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
	/// interface depois de adicionar uma nova referência(AddRef).
	/// </summary>
	/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
	/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
	virtual CarenResult ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(IntPtr Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
	virtual CarenResult AdicionarPonteiro(LPVOID Param_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
	/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
	/// </summary>
	/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
	virtual CarenResult RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo);

	/// <summary>
	/// Método responsável por retornar a quantidade de referências do objeto COM atual.
	/// </summary>
	/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
	virtual CarenResult RecuperarReferencias([Out] UInt64% Param_Out_Referencias);

	/// <summary>
	/// Método responsável por indicar se o ponteiro COM atual é válido.
	/// </summary>
	virtual CarenResult StatusPonteiro();

	/// <summary>
	/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
	/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
	/// </summary>
	virtual Int32 ObterCodigoErro();

	/// <summary>
	/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
	/// você fazer uma cópia de um ponteiro de interface.
	/// </summary>
	virtual void AdicionarReferencia();

	/// <summary>
	/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
	/// </summary>
	virtual void LiberarReferencia();

	/// <summary>
	/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
	/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
	/// </summary>
	virtual void LimparDados();

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();




	//Métodos da interface(ICarenAudioClient)
public:
	/// <summary>
	/// (GetBufferSize) - O método recupera o tamanho (capacidade máxima) do buffer de ponto de extremidade.
	/// </summary>
	/// <param name="Param_Out_NumeroFramesBuffer">Retorna o número de quadros de áudio que o buffer pode conter.</param>
	virtual CarenResult ObterTamanhoBuffer([Out] UInt32% Param_Out_NumeroFramesBuffer);

	/// <summary>
	/// (GetCurrentPadding) - O método recupera o número de quadros de preenchimento no buffer de ponto de extremidade.
	/// </summary>
	/// <param name="Param_Out_NumeroQuadrosPreenchimento">Retorna a contagem de quadros (o número de quadros de áudio de preenchimento no buffer).</param>
	virtual CarenResult ObterQuadrosPreenchimentoBuffer([Out] UInt32% Param_Out_NumeroQuadrosPreenchimento);

	/// <summary>
	/// (GetDevicePeriod) - O método recupera o comprimento do intervalo periódico separando o processamento sucessivo passa pelo mecanismo de áudio nos dados no buffer de ponto de extremidade.
	/// </summary>
	/// <param name="Param_Out_IntervaloPeriodicoDefault">Retorna um valor de tempo especificando o intervalo padrão entre o processamento periódico passa pelo mecanismo de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
	/// <param name="Param_Out_IntervaloPeriodicoMinimo">Retorna um valor de tempo especificando o intervalo mínimo entre o processamento periódico passa pelo dispositivo de ponto de extremidade de áudio. O tempo é expresso em unidades de 100 nanossegundos.</param>
	virtual CarenResult ObterInterveloPeriodico([Out] Int64% Param_Out_IntervaloPeriodicoDefault, [Out] Int64% Param_Out_IntervaloPeriodicoMinimo);

	/// <summary>
	/// (GetMixFormat) - O método recupera o formato de fluxo que o mecanismo de áudio usa para seu processamento interno de fluxos de modo compartilhado.
	/// O formato de mixagem é o formato que o mecanismo de áudio usa internamente para processamento digital de fluxos de modo compartilhado. Este formato não é necessariamente um formato que suporta o 
	/// dispositivo de ponto final de áudio.
	/// </summary>
	/// <param name="Param_Out_FormatoDispositivo">Retorna uma estrutura que contém os dados do formato de mixagem. Se o método falhar, este parametro é nulo.</param>
	virtual CarenResult ObterMixFormato([Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoDispositivo);

	/// <summary>
	/// (GetService) - O método acessa serviços adicionais do objeto de cliente de áudio.
	/// </summary>
	/// <param name="Param_RIID">A identificação de interface para o serviço solicitado.</param>
	/// <param name="Param_Out_Interface">Retorna um ponteiro para a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetService(String^ Param_RIID, ICaren^ Param_Out_Interface);

	/// <summary>
	/// (GetStreamLatency) - O método recupera a latência máxima para o fluxo atual e pode ser chamado a qualquer momento depois que o fluxo foi inicializado.
	/// </summary>
	/// <param name="Param_Out_Latencia">Retorna um valor de tempo que representa a latência. O tempo é expresso em unidades de 100 nanosegundos.</param>
	virtual CarenResult ObterLatenciaFluxo([Out] Int64% Param_Out_Latencia);

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
	/// período do dispositivo para seu valor padrão. Para obter o período de dispositivo padrão, chame o método ICarenAudioClient::ObterInterveloPeriodico.</param>
	/// <param name="Param_Formato">Uma estrutura que é um descritor do formato de áudio a ser processado. Este parâmetro deve apontar para um descritor de formato válido do tipo CA_WAVEFORMATEXEXTENSIBLE</param>
	/// <param name="Param_GuidSessãoAudio">O guid da sessão audio. Este valor é um GUID que identifica a sessão de áudio que pertence o fluxo. Se o GUID identifica uma sessão que 
	/// foi aberta anteriormente, o método adiciona o fluxo para essa sessão. Se o GUID não identifica uma sessão existente, o método abre uma nova sessão e adiciona o fluxo para essa sessão. O fluxo 
	/// permanece um membro da mesma sessão para seu tempo de vida. Definindo esse parâmetro como NULO é equivalente a passar um ponteiro para um valor GUID_NULL.</param>
	virtual CarenResult Inicializar(
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
	virtual CarenResult VerificarFormatoSuportado(
		Enumeracoes::CA_AUDIOCLIENTE_SHAREMODE Param_ModoCompartilhamento,
		Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Formato,
		[Out] Estruturas::CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_FormatoMaisProximo);

	/// <summary>
	/// (Reset) - O método redefine o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
	/// Reset é um método de controle que o cliente chama para redefinir um fluxo de áudio interrompido. Redefinir o fluxo libera todos os dados pendentes e redefine a posição do fluxo de relógio de 
	/// áudio para 0. Esse método falhará se ele é chamado em um fluxo que não é interrompido.
	/// </summary>
	virtual CarenResult Redefinir();

	/// <summary>
	/// (SetEventHandle) - O método define o identificador de evento que o sistema sinaliza quando um buffer de áudio está pronto para ser processado pelo cliente.
	/// </summary>
	/// <param name="Param_EventHandle">O identificador de evento.</param>
	virtual CarenResult DefinirEventHandle(IntPtr Param_EventHandle);

	/// <summary>
	/// (Start) - O método inicia o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
	/// Start é um método de controle que o cliente chama para iniciar o fluxo de áudio. Iniciando o fluxo faz com que a ICarenAudioClient interface para iniciar o streaming de dados entre o buffer de 
	/// ponto de extremidade e o mecanismo de áudio. Ele também faz com que o fluxo de relógio de áudio para retomar a contagem de sua posição atual.
	/// </summary>
	virtual CarenResult Iniciar();

	/// <summary>
	/// (Stop) - O método interrompe o fluxo de áudio. Esse método requer inicialização anterior do Audio Cliente antes de ser chamado.
	/// Stop é um método de controle que interrompe um fluxo de áudio em execução. Esse método interrompe a transmissão de dados por meio da conexão do cliente com o mecanismo de áudio. Interromper o fluxo 
	/// congela o relógio de áudio do fluxo em sua posição atual do fluxo. Uma chamada subsequente para ICarenAudioClient::Iniciar faz com que o fluxo retomar a execução a partir dessa posição. 
	/// Se necessário, o cliente pode chamar o ICarenAudioClient::Redefinir método para redefinir a posição enquanto o fluxo é interrompido.
	/// </summary>
	virtual CarenResult Parar();
};