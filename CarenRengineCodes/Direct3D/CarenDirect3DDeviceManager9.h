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
#include "../SDK_Direct3D11.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"

//Importa o namespace que contém as interfaces do Microsoft Direct 3D.
using namespace CarenRengine::Direct3D11;

//Enumeração de retorno de função.


//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;


/// <summary>
/// (Concluido - Fase de Testes) - Classe responsável por permitir que dois encadeamentos compartilhem o mesmo dispositivo Direct3D9 e fornece acesso aos recursos DXVA (DirectX Video Acceleration) do dispositivo.
/// </summary>
public ref class CarenDirect3DDeviceManager9 : public ICarenDirect3DDeviceManager9
{
	/////////////////////////////////////////
	//Objeto gerenciado por essa interface.//
	/////////////////////////////////////////

	//Ponteiro para a interface (IDirect3DDeviceManager9).
	IDirect3DDeviceManager9* PonteiroTrabalho = NULL;

	//Contrutor e destruidor da classe.
public:
	~CarenDirect3DDeviceManager9();


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
	/// Fecha um identificador de dispositivo Direct3D.
	/// Chame o método quando você tiver chamado o método (OpenDeviceHandle).
	/// </summary>
	/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
	virtual CarenResult CloseDeviceHandle(IntPtr Param_Identificador);

	/// <summary>
	/// (TESTE) - Obtém uma interface de serviço de aceleração de vídeo DirectX (DXVA).
	/// Obtenha o IID atravez da estrutura: GUIDs_MFDXVAInterfaces.
	/// </summary>
	/// <param name="Param_HandleDirect3D">Um identificador para um dispositivo Direct3D. Para obter um identificador dispositivo, chame o método: OpenDeviceHandle</param>
	/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Essa interface suporta os Seguintes IDs: IID_IDirectXVideoDecoderService, IID_IDirectXVideoProcessorService</param>
	/// <param name="Param_Out_InterfaceSolicitada">Objeto que contém a interface solicitada se o método tiver sido bem sucedido. O usuário deve criar a interface antes de chamar este método.</param>
	virtual CarenResult GetVideoService(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada);

	/// <summary>
	/// Obtém acesso exclusivo ao dispositivo Direct3D.
	/// </summary>
	/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: OpenDeviceHandle</param>
	/// <param name="Param_Out_Dispositivo">Recebe a interface IDirect3DDevice9[NAO IMPLEMENTADA PELA BIBLIOTECA]. O usuário deve criar a interface antes de chamar este método.</param>
	/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
	/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
	virtual CarenResult LockDevice(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, ICaren^ Param_Out_Dispositivo);

	/// <summary>
	/// Obtém um identificador para o dispositivo Direct3D.
	/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (CloseDeviceHandle) para finalizar.
	/// </summary>
	/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
	virtual CarenResult OpenDeviceHandle([Out] IntPtr% Param_Out_Handle);

	/// <summary>
	/// Define o dispositivo Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado.
	/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método com a interface(ICarenDirect3DDevice9) para o dispositivo Direct3D. 
	/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
	/// </summary>
	/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
	/// <param name="Param_Token">Token recebido no parâmetro pResetToken da função DXVA2CreateDirect3DDeviceManager9.</param>
	virtual CarenResult ResetDevice(ICaren^ Param_Dispostivo3D, UInt32 Param_Token);

	/// <summary>
	/// Testa se um identificador de dispositivo Direct3D é válido.
	/// Se o método retorna ER_DXVA2_HANDLE_INVALIDA, chame o método (CloseDeviceHandle) para fechar o identificador e, em seguida, 
	/// chame (OpenDeviceHandle) novamente para obter um novo identificador. O (ResetDevice) método invalida todos os identificadores de dispositivo aberto.
	/// </summary>
	/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
	virtual CarenResult TestDevice(IntPtr Param_HandleDispositivo3D);

	/// <summary>
	/// Desbloqueia o dispositivo Direct3D.
	/// </summary>
	/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
	/// <param name = "Param_SalvarEstadoDispositivo">Se true, o método salva o estado do dispositivo Direct3D em um bloco de estado. Internamente, o método usa o Direct3D IDirect3DStateBlock9 interface para salvar o estado dispositivo. 
	/// Na próxima vez que você chamar lockdevice com o mesmo identificador de dispositivo, o bloco de estado é restaurado.</param>
	virtual CarenResult UnlockDevice(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo);
};

