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
#include "..\SDK_MediaFoundation.h"
#include "CarenMFMediaStreamSink.h"
#include "CarenMFPresentationClock.h"
#include "CarenMFActivate.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// [Concluido - Fase de testes] - Falta documentar.
/// </summary>
public ref class CarenMFMediaSink : ICarenMFMediaSink
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaSink).
	IMFMediaSink* PonteiroTrabalho = NULL;

	//Destruidor.
public:
	~CarenMFMediaSink();

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
	/// Método responsável por criar uma instância do Renderizador de Áudio.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface com os atributos para criação do Renderizador de Áudio. Esse parametro pode ser NULO.</param>
	/// <param name="Param_Out_AudioRender">Recebe a interface com o coletor de mídia do Renderiazador de Audio.</param>
	static CarenResult CriarInstanciaAudioRender(ICarenMFAttributes^ Param_Atributos, [Out] ICarenMFMediaSink^% Param_Out_AudioRender)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas pelo método
		IMFAttributes *pAtributoCreate = NULL;
		IMFMediaSink *pAudioRender = NULL;
		ICarenMFMediaSink^ InterfaceAudioRender = nullptr;

		//Chama o método para obter o ponteiro de trabalho para os atributos.
		if (Param_Atributos != nullptr)
		{
			//Recupera o ponteiro de trabalho.
			Param_Atributos->RecuperarPonteiro((LPVOID*)&pAtributoCreate);
		}

		//Chama o método que vai criar o renderizador de Áudio.
		Hr = MFCreateAudioRenderer(pAtributoCreate ? pAtributoCreate : NULL, &pAudioRender);

		//Verifica o resultado do método
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define que houve falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro.
		InterfaceAudioRender = gcnew CarenMFMediaSink();

		//Chama o método para definir o ponteiro de trablho.
		InterfaceAudioRender->AdicionarPonteiro(pAudioRender);

		//Define a interface criada no parametro de saida.
		Param_Out_AudioRender = InterfaceAudioRender;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
		//Retorna o resultado.
		return Resultado;
	}

	/// <summary>
	/// Método responsável por criar um objeto de ativação do Renderizador de Áudio.
	/// </summary>
	/// <param name="Param_Out_AudioRenderActivate">Recebe o ativador de objeto do Renderiazador de Áudio.</param>
	static CarenResult CriarInstanciaAudioRenderActivate([Out] ICarenMFActivate^% Param_Out_AudioRenderActivate)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel COM
		ResultadoCOM Hr = E_FAIL;

		//Variaveis utilizadas pelo método
		IMFActivate* pAudioRenderActivate = NULL;
		ICarenMFActivate^ InterfaceAudioRenderActivate = nullptr;

		//Chama o método que vai criar o ativador do renderizador de audio.
		Hr = MFCreateAudioRendererActivate(&pAudioRenderActivate);

		//Verifica o resultado do método
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define que houve falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a interface que vai conter o ponteiro.
		InterfaceAudioRenderActivate = gcnew CarenMFActivate();

		//Chama o método para definir o ponteiro de trablho.
		InterfaceAudioRenderActivate->AdicionarPonteiro(pAudioRenderActivate);

		//Define a interface criada no parametro de saida.
		Param_Out_AudioRenderActivate = InterfaceAudioRenderActivate;

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	Done:;
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





	//Métodos da interface (ICarenMFMediaSink)
public:
	/// <summary>
	/// Adiciona um novo coletor de fluxo para o coletor de mídia.
	/// O método retorna uma interface para o StreamSink adicionado.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">Um (Identificador) para o fluxo. O valor é (Arbitrário), mas deve ser exclusivo.</param>
	/// <param name="Param_TipoMidia">Uma interface com o tipo de mídia do Stream a ser adicionado. Esse valor pode ser (NULO).</param>
	/// <param name="Param_Out_FluxoSink">Retorna uma interface para o fluxo adicionado.</param>
	virtual CarenResult AdicionarStreamSink(UInt32 Param_IdentificadorFluxo, ICarenMFMediaType^ Param_TipoMidia, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém as características do coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_Caracteristicas">Retorna as características desse (Coletor de mídia).</param>
	virtual CarenResult ObterCaracteristicas([Out] Enumeracoes::CA_MIDIA_SINK_CARACTERISTCAS% Param_Out_Caracteristicas);

	/// <summary>
	/// Obtém o relógio de apresentação que foi definido no coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_RelogioApresentação">Recebe a interface que contém o Relogio de Apresentação(IMFPresentationClock)</param>
	virtual CarenResult ObterRelogioApresentação([Out] ICarenMFPresentationClock^% Param_Out_RelogioApresentação);

	/// <summary>
	/// Obtém um coletor de fluxo, especificado pelo identificador de fluxo.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">O Identificador para o fluxo a ser obtido.</param>
	/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o Stream Sink requisitado pelo seu (Identificador)</param>
	virtual CarenResult ObterStreamSinkPorIdentificador(UInt32 Param_IdentificadorFluxo, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém um coletor de fluxo, especificado por index.
	/// </summary>
	/// <param name="Param_IdFluxo">O Id para o coletor de fluxo a ser obtido.</param>
	/// <param name="Param_Out_FluxoSink">Recebe a interface que contém o coletor de fluxo requisitado.</param>
	virtual CarenResult ObterStreamSinkPorIndex(UInt32 Param_IdFluxo, [Out] ICarenMFMediaStreamSink^% Param_Out_FluxoSink);

	/// <summary>
	/// Obtém o número de coletores de fluxo neste coletor de mídia.
	/// </summary>
	/// <param name="Param_Out_QuantidadeSinks">Retorna a quantidade de (Coletores de Fluxos) presente nesse (Coletor de mídia)</param>
	virtual CarenResult ObterCountStreamSinks([Out] UInt32% Param_Out_QuantidadeSinks);

	/// <summary>
	/// Remove um coletor de fluxo do coletor de mídia.
	/// </summary>
	/// <param name="Param_IdentificadorFluxo">O Identificador do fluxo a ser removido.</param>
	virtual CarenResult RemoverStreamSink(UInt32 Param_IdentificadorFluxo);

	/// <summary>
	/// Define o relógio de apresentação no coletor de mídia.
	/// </summary>
	/// <param name="Param_RelogioApresentação">A interface que contém o relógio de apresentação a ser definido.
	/// O valor pode ser (NULO). Se NULL, o (Coletor de Mídia) para de escutar o relógio de apresentação
	/// que foi definido anteriormente, se houver.</param>
	virtual CarenResult DefinirRelogioApresentação(ICarenMFPresentationClock^ Param_RelogioApresentação);

	/// <summary>
	/// Desliga o coletor de mídia e libera os recursos que ele está usando.
	/// </summary>
	virtual CarenResult DesligarColetor();
};

