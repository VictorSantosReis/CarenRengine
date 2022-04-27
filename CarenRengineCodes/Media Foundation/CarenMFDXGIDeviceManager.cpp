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


#include "../pch.h"
#include "CarenMFDXGIDeviceManager.h"


//Destruidor.
CarenMFDXGIDeviceManager::~CarenMFDXGIDeviceManager()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Construtores
CarenMFDXGIDeviceManager::CarenMFDXGIDeviceManager()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenMFDXGIDeviceManager::CarenMFDXGIDeviceManager(OutParam UInt32% Param_Out_ResetToken)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	UINT vi_OutResetToken = 0;
	IMFDXGIDeviceManager* vi_pOutDXGIManager = Nulo;

	//Chama o método para criar a interface.
	Hr = MFCreateDXGIDeviceManager(&vi_OutResetToken, &vi_pOutDXGIManager);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define o ponteiro criado no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutDXGIManager;

	//Define o Token no parametro de saida.
	Param_Out_ResetToken = vi_OutResetToken;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFDXGIDeviceManager::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFDXGIDeviceManager::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFDXGIDeviceManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFDXGIDeviceManager**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFDXGIDeviceManager::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFDXGIDeviceManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFDXGIDeviceManager**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFDXGIDeviceManager::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFDXGIDeviceManager::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFDXGIDeviceManager::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFDXGIDeviceManager::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFDXGIDeviceManager::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFDXGIDeviceManager::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFDXGIDeviceManager::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFDXGIDeviceManager::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFDXGIDeviceManager();
}





// Métodos da interface proprietaria (ICarenMFDXGIDeviceManager)


/// <summary>
/// Fecha um identificador de dispositivo Direct3D.
/// Chame o método quando você tiver chamado o método (OpenDeviceHandle).
/// </summary>
/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
CarenResult CarenMFDXGIDeviceManager::CloseDeviceHandle(IntPtr Param_Identificador)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE vi_HandleDeviceClose = NULL;

	//Converte o parametro.
	vi_HandleDeviceClose = Util.ConverterIntPtrToHWND(Param_Identificador);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CloseDeviceHandle(vi_HandleDeviceClose);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém uma interface de serviço de aceleração de vídeo DirectX (DXVA).
/// Obtenha o IID atravez da estrutura: GUIDs_MFDXVAInterfaces.
/// </summary>
/// <param name="Param_HandleDirect3D">Um identificador para um dispositivo Direct3D. Para obter um identificador dispositivo, chame o método: OpenDeviceHandle</param>
/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Esse método suporta as seguintes interfaces: ID3D11Device, ID3D11VideoDevice</param>
/// <param name="Param_Out_InterfaceSolicitada">Objeto que contém a interface solicitada se o método tiver sido bem sucedido.</param>
CarenResult CarenMFDXGIDeviceManager::GetVideoService(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	HANDLE vi_HandleDirect3D = Nulo;
	GUID vi_GuidInterface = GUID_NULL;
	IUnknown* vi_pOutInterface = Nulo;

	//Obtém a handle do Direct3D
	vi_HandleDirect3D = Util.ConverterIntPtrToHWND(Param_HandleDirect3D);

	//Obtém o guid da interface solicitada
	CarenCreateGuidFromStringSafe(Param_IIDInterface, vi_GuidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetVideoService(vi_HandleDirect3D, vi_GuidInterface, reinterpret_cast<LPVOID*>(&vi_pOutInterface));

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutInterface, Param_Out_InterfaceSolicitada, true);

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém acesso exclusivo ao dispositivo Direct3D.
/// </summary>
/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: OpenDeviceHandle</param>
/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
/// <param name="Param_IIDInterface">O identificador de interface (IID) da interface solicitada. O dispositivo Direct3D apoiará as seguintes interfaces: ID3D11Device, ID3D11VideoDevice, ID3D11VideoContext</param>
/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface solicitada.</param>
CarenResult CarenMFDXGIDeviceManager::LockDevice(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	HANDLE vi_HandleDevice = Nulo;
	GUID vi_GuidInterface = GUID_NULL;
	IUnknown* vi_pOutInterface = Nulo;

	//Obtém a handle do Direct3D
	vi_HandleDevice = Util.ConverterIntPtrToHWND(Param_Handle);

	//Obtém o guid da interface solicitada
	CarenCreateGuidFromStringSafe(Param_IIDInterface, vi_GuidInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->LockDevice(
		vi_HandleDevice, 
		vi_GuidInterface, 
		reinterpret_cast<LPVOID*>(&vi_pOutInterface), //OUT
		Param_AguardarBloqueio ? TRUE : FALSE);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutInterface, Param_Out_InterfaceSolicitada, true);

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um identificador para o dispositivo Direct3D.
/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (CloseDeviceHandle) para finalizar.
/// </summary>
/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
CarenResult CarenMFDXGIDeviceManager::OpenDeviceHandle([Out] IntPtr% Param_Out_Handle)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	Utilidades Util;
	HANDLE vi_HandleDeviceOpened = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenDeviceHandle(&vi_HandleDeviceOpened);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte de define a handle no parametro de saida.
	Param_Out_Handle = Util.ConverterHandleToIntPtr(vi_HandleDeviceOpened);

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Define o dispositivo Microsoft Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado..
/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método, passando a interface (ICarenD3D11Device) do dispositivo Direct3D 11. 
/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
/// </summary>
/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
/// <param name="Param_Token">Token recebido no parâmetro Param_Out_ResetToken na criação deste gerenciador.</param>
CarenResult CarenMFDXGIDeviceManager::ResetDevice(ICaren^ Param_Dispostivo3D, UInt32 Param_Token)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IUnknown* vi_pDevice3D = NULL;

	//Recupera o ponteiro para o dispositivo 3D.
	CarenGetPointerFromICarenSafe(Param_Dispostivo3D, vi_pDevice3D);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ResetDevice(vi_pDevice3D, Param_Token);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Testa se um identificador de dispositivo Direct3D é válido.
/// Se o método retorna ER_MF_DXGI_HANDLE_INVALIDA, chame o método (CloseDeviceHandle) para fechar o identificador e, em seguida, 
/// chame (OpenDeviceHandle) novamente para obter um novo identificador. O método (ResetDevice), invalida todos os identificadores de dispositivo aberto.
/// </summary>
/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
CarenResult CarenMFDXGIDeviceManager::TestDevice(IntPtr Param_HandleDispositivo3D)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE vi_HandleDeviceTest = Nulo;

	//Converte o parametro.
	vi_HandleDeviceTest = Util.ConverterIntPtrToHWND(Param_HandleDispositivo3D);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TestDevice(vi_HandleDeviceTest);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Desbloqueia o dispositivo Direct3D.
/// </summary>
/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
/// <param name = "Param_SalvarEstadoDispositivo">Reservado.</param>
CarenResult CarenMFDXGIDeviceManager::UnlockDevice(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE vi_HandleDevice = Nulo;

	//Converte o parametro.
	vi_HandleDevice = Util.ConverterIntPtrToHWND(Param_HandleDispositivo3D);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnlockDevice(vi_HandleDevice, Param_SalvarEstadoDispositivo ? TRUE : FALSE);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//retorna o resultado
	return Resultado;
}