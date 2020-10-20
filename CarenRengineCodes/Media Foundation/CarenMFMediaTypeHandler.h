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
#include "CarenMFMediaType.h"
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
public ref class CarenMFMediaTypeHandler : public ICarenMFMediaTypeHandler
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFMediaBuffer).
	IMFMediaTypeHandler* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMFMediaTypeHandler();

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

public:
	/// <summary>
	/// Cria uma instância do gerenciador de tipo de mídia (IMFMediaTypeHandler), para definir os tipos em determinados objetos.
	/// Essa classe é muito utilizada pelo ICarenMFMediaStreamSink para reprodução de Vídeo ou Áudio.
	/// </summary>
	/// <param name="Param_Out_MidiaTypeHandler">Recebe o ponteiro para o ICarenMFMediaTypeHandler.</param>
	static CarenResult CriarInstancia([Out] ICarenMFMediaTypeHandler^% Param_Out_MidiaTypeHandler)
	{
		//Variavel a ser retornada.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Variavel que vai conter o resultado COM.
		ResultadoCOM Hr;

		//Variavel que vai conter o IMFMediaTypeHandler.
		IMFMediaTypeHandler *pMediaTypeHand = NULL;

		//Interface responsável pela classe atual.
		ICarenMFMediaTypeHandler^ InterfaceMidiaTypeHand = nullptr;

		//Chama o método para criar o IMFMediaTypeHandler.
		Hr = MFCreateSimpleTypeHandler(&pMediaTypeHand);

		//Verifica o resultado
		if (Sucesso(Hr))
		{
			//Deixa o método continuar.
		}
		else
		{
			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

			//Sai do método
			goto Done;
		}

		//Cria a instância da classe
		InterfaceMidiaTypeHand = gcnew CarenMFMediaTypeHandler();

		//Chama o método para definir o ponteiro de trabalho na interface a ser retornada.
		Resultado = InterfaceMidiaTypeHand->AdicionarPonteiro(pMediaTypeHand);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//Houve uma falha.

			//Falhou ao definir o ponteiro.
			InterfaceMidiaTypeHand->LimparDados();
			InterfaceMidiaTypeHand->Finalizar();
			InterfaceMidiaTypeHand = nullptr;

			//Descarta o ponteiro não gerenciado criado.
			SafeReleasePointer(&pMediaTypeHand);

			//Sai do método
			goto Done;
		}
		else
		{
			//Deixa o método continuar.
		}

		//Define a interface de retorno.
		Param_Out_MidiaTypeHandler = InterfaceMidiaTypeHand;

		//Define sucesso
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

	//Métodos da interface IMFMediaTypeHandler
public:
	/// <summary>
	/// (GetCurrentMediaType) - Recupera o tipo de mídia atual do objeto.
	/// </summary>
	/// <param name="Param_Out_MidiaType">Retorna o Tipo de midia atual.</param>
	virtual CarenResult ObterTipoMidiaAtual([Out] ICarenMFMediaType^% Param_Out_MidiaType);

	/// <summary>
	/// (GetMajorType) - Obtém o tipo de mídia principal do objeto.
	/// </summary>
	/// <param name="Param_Out_GuidMidiaPrincipal">Retorna o GUID do tipo da mídia principal.</param>
	/// <param name="Param_Out_TipoPrincipal">Retorna a enumeração que define o tipo principal da mídia.</param>
	virtual CarenResult ObterTipoMidiaPrincipal([Out] String^% Param_Out_GuidMidiaPrincipal, [Out] Enumeracoes::CA_Midia_TipoPrincipal% Param_Out_TipoPrincipal);

	/// <summary>
	/// (GetMediaTypeByIndex) - Recupera um tipo de mídia da lista do objeto de tipos de mídia com suporte.
	/// </summary>
	/// <param name="Param_Id">Índice baseado em zero do tipo de mídia para recuperar. Para obter o número de tipos de mídia na lista, chame o método (ObterCountTiposMidia).</param>
	/// <param name="Param_Out_MidiaType">Retorna o tipo da mídia no Id especificado.</param>
	virtual CarenResult ObterTipoMidiaPorIndex(UInt32 Param_Id, [Out] ICarenMFMediaType^% Param_Out_MidiaType);

	/// <summary>
	/// (GetMediaTypeCount) - Recupera o número de tipos de mídia na lista do objeto de tipos de mídia com suporte.
	/// </summary>
	/// <param name="Param_Out_Quantidade">Retorna a quantidade de tipos de mídia na interface.</param>
	virtual CarenResult ObterCountTiposMidia([Out] UInt32% Param_Out_Quantidade);

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
	virtual CarenResult VerificarTipoMidiaSuportado(ICarenMFMediaType^ Param_MidiaType, [Out] ICarenMFMediaType^% Param_Out_MidiaAproximada);

	/// <summary>
	/// (SetCurrentMediaType) - Define o tipo de mídia do objeto.
	/// Para fontes de mídia, a configuração do tipo de mídia significa que a fonte gerará dados que estejam 
	/// de acordo com esse tipo de mídia. Para coletores de mídia, definindo o tipo de mídia significa que o 
	/// coletor pode receber dados que está de acordo com esse tipo de mídia.
	/// </summary>
	/// <param name="Param_MidiaType">O tipo de mídia a ser definido no objeto.</param>
	virtual CarenResult DefinirTipoMidiaAtual(ICarenMFMediaType^ Param_MidiaType);
};

