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
#include "CarenAudioSessionManager.h"


//Destruidor.
CarenAudioSessionManager::~CarenAudioSessionManager()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioSessionManager::CarenAudioSessionManager()
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
CarenResult CarenAudioSessionManager::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionManager::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionManager**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionManager::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionManager**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionManager::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionManager::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioSessionManager::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioSessionManager::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenAudioSessionManager::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioSessionManager::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioSessionManager::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioSessionManager::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioSessionManager();
}






//
// Métodos da interface proprietária(ICarenAudioSessionManager)
//

/// <summary>
/// (GetAudioSessionControl) - O método recupera um controle de sessão de áudio.
/// </summary>
/// <param name="Param_GuidSessaoAudio">Uma string que contém o GUID da sessão de áudio. Se o GUID não identificar uma sessão que foi aberta anteriormente, a chamada abrirá uma 
/// sessão nova, mas vazia. Se este parâmetro for NULO, o método atribui o fluxo para a sessão padrão.</param>
/// <param name="Param_FlagsFluxo">Especifica o status dos sinalizadores para o fluxo de áudio.</param>
/// <param name="Param_Out_ControleSessaoAudio">Retorna a interface de controle de sessão de áudio. O chamador é responsável por liberar a interface, quando ela não é 
/// mais necessária</param>
CarenResult CarenAudioSessionManager::GetAudioSessionControl(String^ Param_GuidSessaoAudio, UInt32 Param_FlagsFluxo, [Out] ICarenAudioSessionControl^% Param_Out_ControleSessaoAudio)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidSessaoAudio = GUID_NULL;
	IAudioSessionControl* pControleSessao = NULL;

	//Verifica se especificou um Guid
	if (String::IsNullOrEmpty(Param_GuidSessaoAudio))
	{
		//Cria o guid da sessão
		GuidSessaoAudio = Util.CreateGuidFromString(Param_GuidSessaoAudio);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAudioSessionControl(&GuidSessaoAudio, Param_FlagsFluxo, &pControleSessao);

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

	//Cria a interface que será retornada no parametro.
	Param_Out_ControleSessaoAudio = gcnew CarenAudioSessionControl();

	//Define o ponteiro de trabalho.
	Param_Out_ControleSessaoAudio->AdicionarPonteiro(pControleSessao);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetSimpleAudioVolume) - O método recupera um controle de volume de áudio simples.
/// </summary>
/// <param name="Param_GuidSessaoAudio">Uma string que contém o GUID da sessão de áudio. Se o GUID não identificar uma sessão que foi aberta anteriormente, a chamada abrirá uma 
/// sessão nova, mas vazia. Se este parâmetro for NULO, o método atribui o fluxo para a sessão padrão.</param>
/// <param name="Param_FlagsFluxo">Especifica se a solicitação é para uma sessão de processo cruzado. Definido como TRUE(1) se a sessão é processo cruzado. Definido como FALSE(0) se a 
/// sessão não é processo cruzado.</param>
/// <param name="Param_Out_ControladorSimplesVolume">Retorna a interface de controle de volume áudio. Essa interface representa o controle de volume de áudio simples para o processo atual. O chamador é responsável por 
/// liberar a interface, quando ela não é mais necessária.</param>
CarenResult CarenAudioSessionManager::GetSimpleAudioVolume(String^ Param_GuidSessaoAudio, UInt32 Param_FlagsFluxo, [Out] ICarenSimpleAudioVolume^% Param_Out_ControladorSimplesVolume)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidSessaoAudio = GUID_NULL;
	ISimpleAudioVolume* pSimpleAudioVolume = NULL;

	//Verifica se especificou um Guid
	if (String::IsNullOrEmpty(Param_GuidSessaoAudio))
	{
		//Cria o guid da sessão
		GuidSessaoAudio = Util.CreateGuidFromString(Param_GuidSessaoAudio);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSimpleAudioVolume(&GuidSessaoAudio, Param_FlagsFluxo, &pSimpleAudioVolume);

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

	//Cria a interface a ser retornada no parametro
	Param_Out_ControladorSimplesVolume = gcnew CarenSimpleAudioVolume();

	//Deifine o ponteiro de trabalho
	Param_Out_ControladorSimplesVolume->AdicionarPonteiro(pSimpleAudioVolume);

Done:;
	//Retorna o resultado.
	return Resultado;
}