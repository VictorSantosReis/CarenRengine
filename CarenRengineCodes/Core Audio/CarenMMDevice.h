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
#include "..\Caren\Caren.h"
#include "..\SDK_CoreAudio.h"
#include "CarenPropertyStore.h"
#include "..\FunctionClass\PropVariantManager.h"
#include "..\SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Core Audio Api
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
/// (Concluida - Fase de Testes) - Classe responsável por encapsular as características genéricas de um recurso de multimídia do dispositivo de Áudio.
/// </summary>
public ref class CarenMMDevice :public ICarenMMDevice
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMMDevice).
	IMMDevice* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenMMDevice();


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


	//Cria uma instância da classe
public:
	/// <summary>
	/// Cria uma instância vazia do dispositivo de audio.
	/// </summary>
	/// <param name="Param_Out_Interface">Retorna a interface vazia. Chamadas para está interface vai resultar em exceção
	/// se nenhum ponteiro for definido.</param>
	static CarenResult CriarInstanciaVazia([Out] ICarenMMDevice^%  Param_Out_Interface)
	{
		//Variavel que vai retornar o resultado.
		CarenResult Resultado = CarenResult(E_FAIL, false);

		//Cria a interface e retorna ao usuário.
		Param_Out_Interface = gcnew CarenMMDevice();

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





	//Métodos da interface Proprietaria
public:

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
	virtual CarenResult AtivarObjeto(String^ Param_GuidInterface, Enumeracoes::CA_CLSCTX Param_ContextoEx, Estruturas::CA_PropVariant^ Param_ParmetrosActive, ICaren^ Param_Out_InterfaceRequisitada);

	/// <summary>
	/// (GetId) - O método recupera uma cadeia de caracteres de ID de ponto de extremidade que identifica o dispositivo de ponto de extremidade de áudio.
	/// </summary>
	/// <param name="Param_Out_EndpointId">>Retorna o endereço de uma sequência de caracteres largos terminada por caractere nulo que contém o ID do dispositivo de ponto de extremidade.</param>
	virtual CarenResult ObterId([Out] String^% Param_Out_EndpointId);

	/// <summary>
	/// (GetState) - O método recupera o estado atual do dispositivo.
	/// </summary>
	/// <param name="Param_Out_EstadoDispositivo">Retorna o estado do dispositivo atual.</param>
	virtual CarenResult ObterEstado([Out] Enumeracoes::CA_ESTADO_DISPOSITIVO_AUDIO% Param_Out_EstadoDispositivo);

	/// <summary>
	/// (OpenPropertyStore) - O método recupera uma interface para o armazenamento de Propriedade do dispositivo.
	/// </summary>
	/// <param name="Param_TipoAcesso">O modo de acesso de armazenamento. Este parâmetro especifica se deve abrir o armazenamento de propriedade no modo de leitura, modo de gravação ou modo de 
	/// leitura/gravação.</param>
	/// <param name="Param_Out_Store">Rece uma interface que contém o armazenamento de propriedades do dispositivo. O chamador é responsável por liberar a interface, quando ele não é mais necessário, 
	/// chamando o método de Release da interface.</param>
	virtual CarenResult AbrirPropertyStore(Enumeracoes::CA_STGMs Param_TipoAcesso, [Out] ICarenPropertyStore^% Param_Out_Store);
};

