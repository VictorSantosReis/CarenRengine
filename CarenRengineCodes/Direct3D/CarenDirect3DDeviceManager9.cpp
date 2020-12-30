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
#include "CarenDirect3DDeviceManager9.h"


//Destruidor.
CarenDirect3DDeviceManager9::~CarenDirect3DDeviceManager9()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenDirect3DDeviceManager9::CarenDirect3DDeviceManager9()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenDirect3DDeviceManager9::CarenDirect3DDeviceManager9(OutParam UInt32% Param_Out_Resetoken)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	UINT vi_OutResetToken = 0;
	IDirect3DDeviceManager9* vi_pOutDirect3D9 = Nulo;

	//Chama o método para realizar a operação.
	Hr = DXVA2CreateDirect3DDeviceManager9(&vi_OutResetToken, &vi_pOutDirect3D9);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutDirect3D9;

	//Define o Token no parametro de saida.
	Param_Out_Resetoken = vi_OutResetToken;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenDirect3DDeviceManager9::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A operação falhou.
		

		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}


	//Retorna o resultado
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDirect3DDeviceManager9::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IDirect3DDeviceManager9*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDirect3DDeviceManager9::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IDirect3DDeviceManager9*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDirect3DDeviceManager9::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDirect3DDeviceManager9::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDirect3DDeviceManager9::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDirect3DDeviceManager9::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDirect3DDeviceManager9::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDirect3DDeviceManager9::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDirect3DDeviceManager9::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenDirect3DDeviceManager9::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDirect3DDeviceManager9::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenDirect3DDeviceManager9();
}



//
// Métodos da interface proprietaria
//



/// <summary>
/// Fecha um identificador de dispositivo Direct3D.
/// Chame o método quando você tiver chamado o método (OpenDeviceHandle).
/// </summary>
/// <param name="Param_Identificador">O identificador para o Dispositivo Direct3D a ser finalizado.</param>
CarenResult CarenDirect3DDeviceManager9::CloseDeviceHandle(IntPtr Param_Identificador)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE HandClose = NULL;

	//Converte o parametro.
	HandClose = Util.ConverterIntPtrToHWND(Param_Identificador);

	//Chama o método para finalizar a handle
	Hr = PonteiroTrabalho->CloseDeviceHandle(HandClose);

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
/// <param name="Param_IIDInterface">O GUID da interface a ser obtida. Essa interface suporta os Seguintes IDs: IID_IDirectXVideoDecoderService, IID_IDirectXVideoProcessorService</param>
/// <param name="Param_Out_InterfaceSolicitada">Objeto que contém a interface solicitada se o método tiver sido bem sucedido. O usuário deve criar a interface antes de chamar este método.</param>
CarenResult CarenDirect3DDeviceManager9::GetVideoService(IntPtr Param_HandleDirect3D, String^ Param_IIDInterface, ICaren^ Param_Out_InterfaceSolicitada)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	HANDLE HandleDirect3D = 0;
	GUID GuidInterfaceSolicitada = GUID_NULL;
	void* pInterface = NULL;

	//Obtém a handle do Direct3D
	HandleDirect3D = Util.ConverterIntPtrToHWND(Param_HandleDirect3D);

	//Obtém o guid da interface solicitada
	GuidInterfaceSolicitada = Util.CreateGuidFromString(Param_IIDInterface);

	//Verifica e o Guid é valido
	if (GuidInterfaceSolicitada == GUID_NULL)
	{
		//O guid informado é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Consulta o serviço
	Hr = PonteiroTrabalho->GetVideoService(HandleDirect3D, GuidInterfaceSolicitada, &pInterface);

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

	//Define o ponteiro de trabalho
	Param_Out_InterfaceSolicitada->AdicionarPonteiro(pInterface);


Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém acesso exclusivo ao dispositivo Direct3D.
/// </summary>
/// <param name="Param_Handle">Um identificador para o dispositivo Direct3D. Para obter o identificador do dispositivo, chame o método: OpenDeviceHandle</param>
/// <param name="Param_Out_Dispositivo">Recebe a interface IDirect3DDevice9[NAO IMPLEMENTADA PELA BIBLIOTECA]. O usuário deve criar a interface antes de chamar este método.</param>
/// <param name="Param_AguardarBloqueio">Especifica se deve aguardar o bloqueio do dispositivo. Se o dispositivo já está bloqueado e esse parâmetro é true, 
/// o método bloqueia até que o dispositivo é desbloqueado. Caso contrário, se o dispositivo está bloqueado e este bloco é false, o método retorna imediatamente com o código de erro ER_DXVA2_VIDEO_DEVICE_LOCKED.</param>
CarenResult CarenDirect3DDeviceManager9::LockDevice(IntPtr Param_Handle, Boolean Param_AguardarBloqueio, ICaren^ Param_Out_Dispositivo)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	Utilidades Util;
	HANDLE HandleDirect3D = 0;
	BOOL fAguardarBloqueio = Param_AguardarBloqueio ? TRUE : FALSE;
	IDirect3DDevice9* pInterface = NULL;

	//Obtém a handle do Direct3D
	HandleDirect3D = Util.ConverterIntPtrToHWND(Param_Handle);

	//Chama o método para obter o acesso exclusivo ao dispositivo.
	Hr = PonteiroTrabalho->LockDevice(HandleDirect3D, &pInterface, fAguardarBloqueio);

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

	//Define o ponteiro de trabalho para a interface.
	Param_Out_Dispositivo->AdicionarPonteiro(pInterface);


Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Obtém um identificador para o dispositivo Direct3D.
/// Você deve fechar o Identificador do dispositivo após o seu uso, chame o método (CloseDeviceHandle) para finalizar.
/// </summary>
/// <param name="Param_Out_Handle">Recebe a Handle para o dispositivo.</param>
CarenResult CarenDirect3DDeviceManager9::OpenDeviceHandle([Out] IntPtr% Param_Out_Handle)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;
	
	//Variaveis utilizadas no método.
	Utilidades Util;
	HANDLE HandDeviceOpened = NULL;

	//Chama o método para abrir o identificador do dispositivo.
	Hr = PonteiroTrabalho->OpenDeviceHandle(&HandDeviceOpened);

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
	Param_Out_Handle = Util.ConverterHandleToIntPtr(HandDeviceOpened);

Done:;
	//retorna o resultado
	return Resultado;
}

/// <summary>
/// Define o dispositivo Direct3D ou notifica o Gerenciador de dispositivo que o dispositivo Direct3D foi zerado.
/// Quando você cria o Gerenciador de dispositivos Direct3D pela primeira vez, chame esse método com a interface(ICarenDirect3DDevice9) para o dispositivo Direct3D. 
/// O Gerenciador de dispositivos não cria o dispositivo; o chamador deve fornecer o ponteiro do dispositivo inicialmente.
/// </summary>
/// <param name="Param_Dispostivo3D">A interface do dispositivo Direct3D.</param>
/// <param name="Param_Token">Token recebido no parâmetro pResetToken da função DXVA2CreateDirect3DDeviceManager9</param>
CarenResult CarenDirect3DDeviceManager9::ResetDevice(ICaren^ Param_Dispostivo3D, UInt32 Param_Token)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;
	
	//Variaveis utilizadas no método.
	IDirect3DDevice9* pDispositivo3D9 = NULL;

	//Recupera o ponteiro para o dispositivo 3D.
	Resultado = Param_Dispostivo3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D9);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Sai do método
		goto Done;
	}

	//Chama o método para resetar o dispositivo.
	Hr = PonteiroTrabalho->ResetDevice(pDispositivo3D9, Param_Token);

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
/// Se o método retorna ER_DXVA2_HANDLE_INVALIDA, chame o método (CloseDeviceHandle) para fechar o identificador e, em seguida, 
/// chame (OpenDeviceHandle) novamente para obter um novo identificador. O (ResetDevice) método invalida todos os identificadores de dispositivo aberto.
/// </summary>
/// <param name = "Param_HandleDispositivo3D">A handle para o Dispotivo do Direct3D. Para obter essa handle, chame o método: OpenDeviceHandle</param>
CarenResult CarenDirect3DDeviceManager9::TestDevice(IntPtr Param_HandleDispositivo3D)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE HandTeste = NULL;

	//Converte o parametro.
	HandTeste = Util.ConverterIntPtrToHWND(Param_HandleDispositivo3D);

	//Testa o identificador.
	Hr = PonteiroTrabalho->TestDevice(HandTeste);

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
/// <param name = "Param_SalvarEstadoDispositivo">Se true, o método salva o estado do dispositivo Direct3D em um bloco de estado. Internamente, o método usa o Direct3D IDirect3DStateBlock9 interface para salvar o estado dispositivo. 
/// Na próxima vez que você chamar lockdevice com o mesmo identificador de dispositivo, o bloco de estado é restaurado.</param>
CarenResult CarenDirect3DDeviceManager9::UnlockDevice(IntPtr Param_HandleDispositivo3D, Boolean Param_SalvarEstadoDispositivo)
{
	//Variavel que vai ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_E_NOINTERFACE, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Vaiaveis utilizadas no método
	Utilidades Util;
	HANDLE HandDevice = NULL;

	//Converte o parametro.
	HandDevice = Util.ConverterIntPtrToHWND(Param_HandleDispositivo3D);

	//Chama o método para desbloquear o dispositivo.
	Hr = PonteiroTrabalho->UnlockDevice(HandDevice, Param_SalvarEstadoDispositivo ? TRUE : FALSE);

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