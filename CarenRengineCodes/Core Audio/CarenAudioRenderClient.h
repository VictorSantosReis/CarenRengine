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
#include "../SDK_CoreAudio.h"
#include "../Caren/Caren.h"
#include "../Caren/CarenBuffer.h"
#include "../SDK_Utilidades.h"

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
/// (Concluido - Fase de Testes) - Classe responsável por gravar dados de saída para um buffer de ponto de extremidade de renderização.
/// </summary>
public ref class CarenAudioRenderClient :public ICarenAudioRenderClient
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IAudioRenderClient).
	IAudioRenderClient* PonteiroTrabalho = NULL;


	//Construtor e destruidor da classe.
public:
	~CarenAudioRenderClient();


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
	/// Cria uma instância vazia do Renderizador de audio do cliente.
	/// </summary>
	/// <param name="Param_Out_Interface">Retorna a interface vazia. Chamadas para está interface vai resultar em exceção
	/// se nenhum ponteiro for definido.</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenAudioRenderClient^% Param_Out_Interface)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface vazia
		Param_Out_Interface = gcnew CarenAudioRenderClient();

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




	//Métodos da interface(ICarenAudioRenderClient)
public:
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
	virtual CarenResult GetBuffer(UInt32 Param_NumeroFramesRequisitados, UInt32 Param_TamanhoFrameInBytes, [Out] ICarenBuffer^% Param_Out_BufferAudio);

	/// <summary>
	/// (ReleaseBuffer) - O método libera o espaço de buffer adquirido na chamada anterior para o método ICarenAudioRenderClient::GetBuffer.
	/// </summary>
	/// <param name="Param_NumeroFramesEscritos">O número de quadros de áudio gravados pelo cliente para o pacote de dados. O valor deste parâmetro deve ser menor ou igual ao tamanho do pacote de dados, 
	/// conforme especificado no parâmetro Param_NumeroFramesRequisitados passado para o método ICarenAudioRenderClient::GetBuffer.</param>
	/// <param name="Param_Flags">Os sinalizadores de configuração de buffer. O chamador pode definir esse parâmetro tanto para 0(Disponivel na enumeração) ou para o seguinte valor de enumeração CA_AUDIOCLIENTE_BUFFERFLAGS (um bit de sinalizador).</param>
	virtual CarenResult ReleaseBuffer(UInt32 Param_NumeroFramesEscritos, Enumeracoes::CA_AUDIOCLIENTE_BUFFERFLAGS Param_Flags);
};

