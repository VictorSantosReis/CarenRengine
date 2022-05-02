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
#include "CarenMMDevice.h"


//Destruidor.
CarenMMDevice::~CarenMMDevice()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMMDevice::CarenMMDevice()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMMDevice::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMDevice::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMDevice*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMDevice**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMMDevice::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMMDevice*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMMDevice**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMDevice::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMMDevice::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMMDevice::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMMDevice::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMMDevice::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMMDevice::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMMDevice::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMMDevice();
}

//
// Métodos da interface proprietaria
//

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
CarenResult CarenMMDevice::Activate(String^ Param_GuidInterface, Enumeracoes::CA_CLSCTX Param_ContextoEx, Estruturas::CA_PROPVARIANT^ Param_ParmetrosActive, ICaren^ Param_Out_InterfaceRequisitada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PropVariantManager UtilVariant = PropVariantManager();
	LPVOID pInterfaceSolcitada = NULL;
	GUID GuidInterface = GUID_NULL;
	DWORD clsctxvalue = (DWORD)Param_ContextoEx;
	LPPROPVARIANT vi_pPropVar = Nulo;	
	
	//Cria o guid da interface solicitada.
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Verifica se o usuário especificou uma PropertyStore
	if (Param_ParmetrosActive != nullptr)
	{
		//Converte a PropVariant gerenciada para a nativa.
		vi_pPropVar = static_cast<LPPROPVARIANT>(UtilVariant.ConverterPropVariantManaged_ToUnmanaged(Param_ParmetrosActive));

		//Verifica se não ocorreu um erro na conversão.
		if (!ObjetoValido(vi_pPropVar))
		{
			//Falhou ao converter a propvariant.

			//Define falha.
			Resultado.AdicionarCodigo(ResultCode::ER_CONVERSAO_PROPVARIANT, false);

			//Sai do método
			Sair;
		}
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Activate(GuidInterface, clsctxvalue, Param_ParmetrosActive != nullptr ? vi_pPropVar : NULL, &pInterfaceSolcitada);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Chama o método para deifinir o ponteiro
	Param_Out_InterfaceRequisitada->AdicionarPonteiro(pInterfaceSolcitada);

Done:;
	//Libera a propvariant inicializada
	DeletarPropVariantSafe(&vi_pPropVar);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetId) - O método recupera uma cadeia de caracteres de ID de ponto de extremidade que identifica o dispositivo de ponto de extremidade de áudio.
/// </summary>
/// <param name="Param_Out_EndpointId">>Retorna o endereço de uma sequência de caracteres largos terminada por caractere nulo que contém o ID do dispositivo de ponto de extremidade.</param>
CarenResult CarenMMDevice::GetId([Out] String^% Param_Out_EndpointId)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LPWSTR pEndpointID = NULL;
	Utilidades Util;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetId(&pEndpointID);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a string que vai ser retornada ao usuário.
	Param_Out_EndpointId = gcnew String(pEndpointID);

Done:;
	//Libera a LPWSTR se valida
	if (ObjetoValido(pEndpointID))
	{
		//Libera os dados
		CoTaskMemFree(pEndpointID);
	}

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetState) - O método recupera o estado atual do dispositivo.
/// </summary>
/// <param name="Param_Out_EstadoDispositivo">Retorna o estado do dispositivo atual.</param>
CarenResult CarenMMDevice::GetState([Out] Enumeracoes::CA_DEVICE_STATE_XXX% Param_Out_EstadoDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	DWORD StateDevice = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetState(&StateDevice);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor na variavel de saida
	Param_Out_EstadoDispositivo = (Enumeracoes::CA_DEVICE_STATE_XXX)StateDevice;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (OpenPropertyStore) - O método recupera uma interface para o armazenamento de Propriedade do dispositivo.
/// </summary>
/// <param name="Param_TipoAcesso">O modo de acesso de armazenamento. Este parâmetro especifica se deve abrir o armazenamento de propriedade no modo de leitura, modo de gravação ou modo de 
/// leitura/gravação.</param>
/// <param name="Param_Out_Store">Rece uma interface que contém o armazenamento de propriedades do dispositivo. O chamador é responsável por liberar a interface, quando ele não é mais necessário, 
/// chamando o método de Release da interface.</param>
CarenResult CarenMMDevice::OpenPropertyStore(Enumeracoes::CA_STGMs Param_TipoAcesso, [Out] ICarenPropertyStore^% Param_Out_Store)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IPropertyStore* pPropStore = NULL;
	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->OpenPropertyStore((DWORD)Param_TipoAcesso, &pPropStore);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada
	Param_Out_Store = gcnew CarenPropertyStore();

	//Chama o método para definir o ponteiro de trabalho
	Param_Out_Store->AdicionarPonteiro(pPropStore);

Done:;
	//Retorna o resultado.
	return Resultado;
}
