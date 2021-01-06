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
#include "../SDK_MediaFoundation.h"
#include "../Caren/Caren.h"
#include "../Direct3D/CarenD3D11Device.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por permitir que dois segmentos(Threads) de compartilhar o mesmo dispositivo Microsoft Direct3D 11.
/// </summary>
public ref class CarenMFDXGIDeviceManager :public ICarenMFDXGIDeviceManager
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IMFDXGIDeviceManager).
	IMFDXGIDeviceManager* PonteiroTrabalho = NULL;

	//Construtor e destruidor da classe.
public:
	/// <summary>
	/// Inicializa a classe sem nenhum ponteiro de trabalho vinculado.
	/// </summary>
	CarenMFDXGIDeviceManager();

	/// <summary>
	/// Inicializa e cria uma nova instância do Gerenciador de Dispositivos Microsoft DirectX Graphics Infrastructure (DXGI). 
	/// </summary>
	/// <param name="Param_Out_ResetToken">Recebe um token que identifica esta instância do DXGI Device Manager. Use este token ao chamar IMFDXGIDeviceManager::ResetDevice.</param>
	CarenMFDXGIDeviceManager(OutParam UInt32% Param_Out_ResetToken);

	~CarenMFDXGIDeviceManager();


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
			System::Console::WriteLine(String::Concat(ICarenMFDXGIDeviceManager::typeid->Name, " - O método (As<>) falhou ao tentar criar uma instância para o tipo de destino solicitado => ", TypeInterface::typeid->Name));

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
	/// Fecha um identificador de dispositivo Direct3D.
	/// Chame o método quando você tiver chamado o método (OpenDeviceHandle).
	/// </summary>
	/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
	virtual CarenResult CloseDeviceHandle(IntPtr Param_Identificador);

	/// <summary>
	/// Obtém uma interface de serviço de aceleração de vídeo DirectX (DXVA).
	/// Obtenha o IID atravez da estrutura: GUIDs_MFDXVAInterfaces.
	/// </summary>
	/// <param name="Param_HandleDirect3D">Um identificador para um dispositivo Direct3D. Para obter um identificador dispositivo, chame o método: OpenDeviceHandle</param>
	/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Esse método suporta as seguintes interfaces: ID3D11Device, ID3D11VideoDevice</param>
	/// <param name="Param_Out_InterfaceSolicitada">Retorna a interface solicitada se o método tiver sido bem sucedido. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult GetVideoService(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

	/// <summary>
	/// Obtém acesso exclusivo ao dispositivo Direct3D.
	/// </summary>
	/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: OpenDeviceHandle</param>
	/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
	/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
	/// <param name="Param_IIDInterface">O identificador de interface (IID) da interface solicitada. O dispositivo Direct3D apoiará as seguintes interfaces: ID3D11Device, ID3D11VideoDevice, ID3D11VideoContext</param>
	/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	virtual CarenResult LockDevice(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

	/// <summary>
	/// Obtém um identificador para o dispositivo Direct3D.
	/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (CloseDeviceHandle) para finalizar.
	/// </summary>
	/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
	virtual CarenResult OpenDeviceHandle([Out] IntPtr% Param_Out_Handle);

	/// <summary>
	/// Define o dispositivo Microsoft Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado..
	/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método, passando a interface (ICarenD3D11Device) do dispositivo Direct3D 11. 
	/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
	/// </summary>
	/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
	/// <param name="Param_Token">Token recebido no parâmetro Param_Out_ResetToken na criação deste gerenciador.</param>
	virtual CarenResult ResetDevice(ICaren^ Param_Dispostivo3D, UInt32 Param_Token);

	/// <summary>
	/// Testa se um identificador de dispositivo Direct3D é válido.
	/// Se o método retorna ER_MF_DXGI_HANDLE_INVALIDA, chame o método (CloseDeviceHandle) para fechar o identificador e, em seguida, 
	/// chame (OpenDeviceHandle) novamente para obter um novo identificador. O método (ResetDevice), invalida todos os identificadores de dispositivo aberto.
	/// </summary>
	/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
	virtual CarenResult TestDevice(IntPtr Param_HandleDispositivo3D);

	/// <summary>
	/// Desbloqueia o dispositivo Direct3D.
	/// </summary>
	/// <param name="Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
	/// <param name="Param_SalvarEstadoDispositivo">Define se deve salvar o estado do dispositivo.</param>
	virtual CarenResult UnlockDevice(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo);
};

