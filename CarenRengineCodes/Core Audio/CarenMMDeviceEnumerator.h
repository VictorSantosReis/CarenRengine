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
#include "../Caren/Caren.h"
#include "../SDK_CoreAudio.h"
#include "CarenMMDeviceCollection.h"
#include "CarenMMDevice.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Core Audio Api
using namespace CarenRengine::CoreAudio;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável pela enumeração de dispositivos de multimedia do sistema.
/// </summary>
public ref class CarenMMDeviceEnumerator : public ICarenMMDeviceEnumerator
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMMDevice).
	IMMDeviceEnumerator* PonteiroTrabalho = NULL;

	//Construtores e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMMDeviceEnumerator();

	/// <summary>
	/// Inicializa e cria uma nova classe de enumeração de dispositivos multimedia do sistema.
	/// </summary>
	/// <param name="Param_Context">O contexto a qual o objeto vai ser criado.</param>
	CarenMMDeviceEnumerator(CA_CLSCTX Param_Context);

	~CarenMMDeviceEnumerator();


	//Conversões implicitas
public:
	static operator CarenMMDeviceEnumerator^ (IntPtr Param_Pointer)
	{
		//Variavel a ser retornada.
		CarenMMDeviceEnumerator^ ClassResultado = nullptr;

		//Verifica se o ponteiro não é invalido.
		if (Param_Pointer == IntPtr::Zero)
			Sair; // O ponteiro não é valido.

		//Cria a classe para definir o ponteiro.
		ClassResultado = gcnew CarenMMDeviceEnumerator();

		//Define o ponteiro na classe.
		ClassResultado->PonteiroTrabalho = reinterpret_cast<IMMDeviceEnumerator*>(Param_Pointer.ToPointer());

	Done:;

		//Retorna o resultado.
		return ClassResultado;
	}


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
	/// Método responsável por converter a interface atual em outra interface que impelemente ICaren.
	/// Retorna NULO se o ponteiro nativo atual for invalido ou a classe que implementa a interface de destino não poder ser criada.
	/// </summary>
	/// <typeparam name="TypeClass">A classe concreta que implementa a interface definida em (TypeInterface).</typeparam>
	/// <typeparam name="TypeInterface">A interface que será retornada ao chamador.</typeparam>
	/// <param name="Param_Args">Uma lista de objetos para a inicialização do construtor da classe concreta de destino. Se não houver, deixe este parametro como NULO.</param>
	generic <typename TypeClass, typename TypeInterface>
	virtual TypeInterface As(cli::array<Object^>^ Param_Args)
	{
		//Variavel que vai ser retornada.
		TypeInterface CastedInterface;

		//Variaveis a serem utilizadas.
		Type^ vi_TypeClassDest = nullptr; //Contém o tipo croncreto da interface para criar uma instância.
		Object^ vi_NewInstance = nullptr; //Vai conter a nova instância concreta da interface de destino.

		//Verifica se o ponteiro de trabalho da instância atual é valido, se não, não vai converter.
		if (!ObjetoValido(PonteiroTrabalho))
			Sair; //O ponteiro na interface atual não é valido.

		//Obtém o tipo da classe concreta da interface de destino.
		vi_TypeClassDest = TypeClass::typeid;

		//Abre um try para tentar criar uma instância do tipo solicitiado.
		try
		{
			//Tenta criar uma instância da classe de destino.
			vi_NewInstance = Activator::CreateInstance(vi_TypeClassDest, Param_Args);

			//Verifica se não é nula
			if (!ObjetoGerenciadoValido(vi_NewInstance))
				Sair; //O objeto não foi criado com sucesso.
		}
		catch (const std::exception&)
		{
			//Manda uma mensagem para o console.
			System::Console::WriteLine(String::Concat(ICarenMMDeviceEnumerator::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

			//Sai do método
			Sair;
		}

		//Tenta converter a nova instância da classe para sua interface representante.
		CastedInterface = reinterpret_cast<TypeInterface>(vi_NewInstance);

		//Define o ponteiro nativo na interface de saida.
		reinterpret_cast<ICaren^>(CastedInterface)->AdicionarPonteiro(PonteiroTrabalho);

	Done:;
		//Limpa.
		vi_TypeClassDest = nullptr;

		//Retorna o resultado.
		return CastedInterface;
	}

	/// <summary>
	/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
	/// Este método pode ser escrito de forma diferente para cada interface.
	/// </summary>
	virtual void Finalizar();





	//Métodos da interface Proprietaria
public:
	/// <summary>
	/// (EnumAudioEndpoints) - O método gera uma coleção de dispositivos de ponto de extremidade de áudio que atendem aos critérios especificados.
	/// </summary>
	/// <param name="Param_DireçãoFluxo">A direção do fluxo de dados para os dispositivos de ponto de extremidade na coleção. Se o chamador especifica eAll, o método inclui os pontos de extremidade de 
	/// renderização e captura na coleção.</param>
	/// <param name="Param_EstadosPontoExtremidade">O estado ou Estados dos pontos de extremidade que devem ser incluídos na coleção. O chamador deve definir esse parâmetro para o bit a OR de um ou mais da
	/// enumeração.</param>
	/// <param name="Param_Out_ColeçãoDispotivios">Recebe a coleção de dispositivos solicitados. Por meio desse método, o chamador obtém uma referência contada para a interface. O chamador é responsável por 
	/// liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	virtual CarenResult EnumAudioEndpoints(
		Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
		Enumeracoes::CA_DEVICE_STATE_XXX Param_EstadosPontoExtremidade,
		ICarenMMDeviceCollection^ Param_Out_ColeçãoDispotivios);

	/// <summary>
	/// (GetDefaultAudioEndpoint) - O método recupera o ponto de extremidade de áudio padrão para a direção de fluxo de dados especificado e a função.
	/// </summary>
	/// <param name="Param_DireçãoFluxo">A direção de fluxo de dados para o dispositivo de ponto de extremidade.</param>
	/// <param name="Param_FunçãoDispositivo">A direção do fluxo de dados para um dispositivo de renderização é eRender. A direção do fluxo de dados para um dispositivo de captura é eCapture.</param>
	/// <param name="Param_Out_DispositivoDefault">Retorna o dispositivo de Audio padrão do sistema de acordo com sua função e direção. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetDefaultAudioEndpoint(
		Enumeracoes::CA_EDataFlow Param_DireçãoFluxo,
		Enumeracoes::CA_ERole Param_FunçãoDispositivo,
		ICarenMMDevice^ Param_Out_DispositivoDefault);

	/// <summary>
	/// (GetDevice) - O método recupera um dispositivo de ponto de extremidade de áudio que é identificado por uma cadeia de caracteres de ID de ponto de extremidade.
	/// </summary>
	/// <param name="Param_IDPontoExtremidade">Ponteiro para uma seqüência de caracteres que contém o ID de ponto de extremidade. O chamador normalmente obtém essa seqüência de caracteres a partir de 
	/// ICarenMMDevice::ObterId método ou de um dos métodos na ICarenMMNotificationClient interface.</param>
	/// <param name="Param_Out_DispositivoSolicitado">Recebe um ponteiro para a interface do dispositivo solicitado. Por meio desse método, o chamador obtém uma referência contada para a interface. 
	/// O chamador é responsável por liberar a interface, quando ele não é mais necessário, chamando o método de Release da interface. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetDevice(String^ Param_IDPontoExtremidade, ICarenMMDevice^ Param_Out_DispositivoSolicitado);

	/// <summary>
	/// (RegisterEndpointNotificationCallback) - O método registra a interface de retorno de chamada de notificação do cliente.
	/// </summary>
	/// <param name="Param_Cliente">A interface que será registrada para receber as notificações.</param>
	virtual CarenResult RegisterEndpointNotificationCallback(ICarenMMNotificationClient^ Param_Cliente);

	/// <summary>
	/// (UnregisterEndpointNotificationCallback) - O método exclui o registro de uma interface de notificação que o cliente registrado em uma chamada anterior para o IMMDeviceEnumerator:: RegisterEndpointNotificationCallback método.
	/// </summary>
	/// <param name="Param_Cliente">A interface que será removida para não receber mais notificações.</param>
	virtual CarenResult UnregisterEndpointNotificationCallback(ICarenMMNotificationClient^ Param_Cliente);
};

