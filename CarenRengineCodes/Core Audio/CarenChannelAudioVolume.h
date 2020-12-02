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
/// (Concluido - Fase de Testes) - Classe responsável por permitir que um cliente controle e monitore os níveis de volume para todos os canais na sessão de áudio que pertence o fluxo.
/// </summary>
public ref class CarenChannelAudioVolume : public ICarenChannelAudioVolume
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IChannelAudioVolume).
	IChannelAudioVolume* PonteiroTrabalho = NULL;


	//Contrutor e destruidor da classe.
public:
	~CarenChannelAudioVolume();


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
	/// Método responsável por criar uma instância vazia da classe. Chamadas para os métodos sem um ponteiro de trabalho definido
	/// pode gerar comportamentos indefinidos.
	/// </summary>
	/// <param name="Param_Out_CarenAudioCanalVolume">Recebe um ponteiro para a interface (Vazia).</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenChannelAudioVolume^% Param_Out_CarenAudioCanalVolume)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface
		Param_Out_CarenAudioCanalVolume = gcnew CarenChannelAudioVolume();

		//Define sucesso
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

		//Retorna o resultado
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




	//Métodos da interface(ICarenChannelAudioVolume)
public:
	/// <summary>
	/// (GetAllVolumes) - O método recupera os níveis de volume para todos os canais na sessão de áudio.
	/// </summary>
	/// <param name="Param_QuantidadeCanais">A quantidade de canais no formato do fluxo. Chame o método (GetChannelCount) para obter a quantidade total.</param>
	/// <param name="Param_Out_ArrayVolumes">Retorna um array que contém o nivel de volume de cada canal na sessão de áudio. Os níveis de volume estão no intervalo 0,0 a 1,0.</param>
	virtual CarenResult GetAllVolumes(UInt32 Param_QuantidadeCanais, [Out] cli::array<float>^% Param_Out_ArrayVolumes);

	/// <summary>
	/// (GetChannelCount) - O método recupera o número de canais no formato de fluxo para a sessão de áudio.
	/// </summary>
	/// <param name="Param_QuantidadeCanais">Retorna a quantidade de canais.</param>
	virtual CarenResult GetChannelCount([Out] UInt32% Param_QuantidadeCanais);

	/// <summary>
	/// (GetChannelVolume) - O método recupera o nível de volume para o canal especificado na sessão de áudio.
	/// </summary>
	/// <param name="Param_NumeroCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N- 1.</param>
	/// <param name="Param_Out_NivelVolume">Retorna uma variável no qual o método grava o nível de volume do canal especificado. O nível de volume está no intervalo de 0.0 a 1.0.</param>
	virtual CarenResult GetChannelVolume(UInt32 Param_NumeroCanal, [Out] float% Param_Out_NivelVolume);

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
	virtual CarenResult SetAllVolumes(UInt32 Param_QuantidadeItens, cli::array<float>^ Param_ArrayVolumes, String^ Param_ContextoEvento);

	/// <summary>
	/// (SetChannelVolume) - O método define o nível de volume para o canal especificado na sessão de áudio.
	/// </summary>
	/// <param name="Param_IndexCanal">O número do canal. Se o formato de fluxo para a sessão de áudio tem N canais, em seguida, os canais são numerados de 0 a N- 1.</param>
	/// <param name="Param_Volume">O novo nivel de volume que será definido ao canal.</param>
	/// <param name="Param_ContextoEvento">Uma string que contém o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de volume de canal, o Gerenciador 
	/// de sessão envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String 
	/// (ContextoEvento) com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
	/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
	/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
	virtual CarenResult SetChannelVolume(UInt32 Param_IndexCanal, float Param_Volume, String^ Param_ContextoEvento);
};