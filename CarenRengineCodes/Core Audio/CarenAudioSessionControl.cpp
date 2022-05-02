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
#include "CarenAudioSessionControl.h"


//Destruidor.
CarenAudioSessionControl::~CarenAudioSessionControl()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenAudioSessionControl::CarenAudioSessionControl()
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
CarenResult CarenAudioSessionControl::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionControl::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionControl*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionControl**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenAudioSessionControl::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IAudioSessionControl*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IAudioSessionControl**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionControl::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenAudioSessionControl::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenAudioSessionControl::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenAudioSessionControl::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenAudioSessionControl::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenAudioSessionControl::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenAudioSessionControl::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenAudioSessionControl();
}





//
// Métodos da interface proprietária(ICarenAudioSessionControl)
//

/// <summary>
/// (GetDisplayName) - O método recupera o nome de exibição para a sessão de áudio.
/// Se o cliente não tiver chamado (ICarenAudioSessionControl::SetDisplayName) para definir o nome de exibição, a sequência de caracteres estará vazia. 
/// </summary>
/// <param name="Param_Out_Nome">Retorna o nome de exbição da sessão de áudio.</param>
CarenResult CarenAudioSessionControl::GetDisplayName([Out] String^% Param_Out_Nome)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LPWSTR pDisplayName = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDisplayName(&pDisplayName);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o ponteiro de char para a String gerenciada.
	Param_Out_Nome = gcnew String(pDisplayName);

Done:;
	//Libera a memória do peonteiro.
	if (ObjetoValido(pDisplayName))
	{
		//Libera a memória da String.
		CoTaskMemFree(pDisplayName);
	}


	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGroupingParam) - O método recupera o parâmetro de agrupamento da sessão de áudio.
/// </summary>
/// <param name="Param_Out_GUID">Retorna um GUID do paramêtro de agrupamento.</param>
CarenResult CarenAudioSessionControl::GetGroupingParam([Out] String^% Param_Out_GUID)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidParmetro = GUID_NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGroupingParam(&GuidParmetro);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte o guid para string no parametro de saida.
	Param_Out_GUID = Util.ConverterGuidToString(GuidParmetro);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetIconPath) - O método recupera o caminho para o ícone de exibição para a sessão de áudio.
/// </summary>
/// <param name="Param_Out_Url">Retorna o caminho completo completo para o .ico, .exe, .dll que contenha um icone para a sessão de áudio.</param>
CarenResult CarenAudioSessionControl::GetIconPath([Out] String^% Param_Out_Url)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	LPWSTR pUrlIcon = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetIconPath(&pUrlIcon);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os dados no paremtro de saida.
	Param_Out_Url = gcnew String(pUrlIcon);

	//Libera a memoria alocada.
	CoTaskMemFree(pUrlIcon);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetState) - O método recupera o estado atual da sessão de áudio.
/// </summary>
/// <param name="Param_Out_Estado">Retorna o estado da sessão de áudio atual.</param>
CarenResult CarenAudioSessionControl::GetState([Out] Enumeracoes::CA_ESTADO_SESSAO_AUDIO% Param_Out_Estado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	AudioSessionState EstadoSessao;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetState(&EstadoSessao);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a enumeração e define no paremetro de saida.
	Param_Out_Estado = static_cast<Enumeracoes::CA_ESTADO_SESSAO_AUDIO>(EstadoSessao);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (RegisterAudioSessionNotification) - O método registra o cliente para receber notificações de eventos de sessão, incluindo as alterações no estado de fluxo.
/// </summary>
/// <param name="Param_Notificador">Ponteiro para uma interface IAudioSessionEvents, implementada pelo cliente. Se o método for bem-sucedido, ele chama o AddRef método na interface do 
/// cliente IAudioSessionEvents.</param>
CarenResult CarenAudioSessionControl::RegisterAudioSessionNotification(ICarenAudioSessionEvents^ Param_Notificador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IAudioSessionEvents* pSessaoEventos = NULL;

	//Obtém um ponteiro para a sessão de eventos.
	Resultado = Param_Notificador->RecuperarPonteiro((LPVOID*)&pSessaoEventos);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha..

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterAudioSessionNotification(pSessaoEventos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetDisplayName) - O método atribui um nome de exibição para a sessão atual.
/// </summary>
/// <param name="Param_Nome">O novo nome para exibição da sessão de áudio.</param>
/// <param name="Param_GuidContextoEvento">Uma string para o evento-contexto GUID. Se uma chamada para esse método gera um evento de alteração de nome, o Gerenciador de sessão envia 
/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de ContextoEvento.
/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
CarenResult CarenAudioSessionControl::SetDisplayName(String^ Param_Nome, String^ Param_GuidContextoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCWSTR pNomeDisplay = NULL;
	GUID GuidContextoEvento = GUID_NULL;

	//Converte o nome para um ponteiro WCHAR
	pNomeDisplay = Util.ConverterStringToConstWCHAR(Param_Nome);

	//Verifica se especificou um guid de contexto de evento.
	if (!String::IsNullOrEmpty(Param_GuidContextoEvento))
	{
		//Cria o guid do contexto de evento.
		GuidContextoEvento = Util.CreateGuidFromString(Param_GuidContextoEvento);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDisplayName(pNomeDisplay, &GuidContextoEvento);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Libera a memoria para o ponteiro do nome
	delete pNomeDisplay;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetGroupingParam) - O método atribui uma sessão a um agrupamento de sessões.
/// </summary>
/// <param name="Param_GuidNovoParametro">O novo GUID para o parâmetro de agrupamento.</param>
/// <param name="Param_ContextoEvento">Uma string com o GUID para o (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de agrupamento, o Gerenciador de sessão 
/// envia notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) 
/// com cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro, 
/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
CarenResult CarenAudioSessionControl::SetGroupingParam(String^ Param_GuidNovoParametro, String^ Param_ContextoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidNovoParametro = GUID_NULL;
	GUID GuidContextoEvento = GUID_NULL;

	//Cria o novo GUID para o parametro de agrupamento.
	GuidNovoParametro = Util.CreateGuidFromString(Param_GuidNovoParametro);

	//Verifica se especificou um guid de contexto de evento.
	if (!String::IsNullOrEmpty(Param_ContextoEvento))
	{
		//Cria o guid do contexto de evento.
		GuidContextoEvento = Util.CreateGuidFromString(Param_ContextoEvento);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGroupingParam(&GuidNovoParametro, &GuidContextoEvento);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetIconPath) - O método atribui um ícone de exibir para a sessão atual.
/// </summary>
/// <param name="Param_UrlCompletaIco">Sequência de caracteres largos que especifica o caminho e nome de arquivo de um arquivo .ico, .dll ou .exe que contém o ícone.</param>
/// <param name="Param_ContextoEvento">Uma string para o GUID do (ContextoEvento). Se uma chamada para esse método gera um evento de alteração de ícone, o Gerenciador de sessão envia 
/// notificações para todos os clientes que registraram a interface IAudioSessionEvents com o Gerenciador de sessão. O Gerenciador de sessão inclui o valor da String (ContextoEvento) com 
/// cada notificação. Ao receber uma notificação, um cliente pode determinar se ele ou outro cliente é a origem do evento inspecionando o valor de (ContextoEvento).
/// Esse esquema depende do cliente selecionando um valor para esse parâmetro que é exclusivo entre todos os clientes na sessão. Se o chamador fornece uma String NULA para este parâmetro,
/// o método de notificação do cliente recebe NULO ou VAZIO na string de contexto.</param>
CarenResult CarenAudioSessionControl::SetIconPath(String^ Param_UrlCompletaIco, String^ Param_ContextoEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	LPCWSTR pUrlIcone = NULL;
	GUID GuidContextoEvento = GUID_NULL;

	//Chama o método para converter a String.
	pUrlIcone = Util.ConverterStringToConstWCHAR(Param_UrlCompletaIco);

	//Verifica se especificou um guid de contexto de evento.
	if (!String::IsNullOrEmpty(Param_ContextoEvento))
	{
		//Cria o guid do contexto de evento.
		GuidContextoEvento = Util.CreateGuidFromString(Param_ContextoEvento);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetIconPath(pUrlIcone, &GuidContextoEvento);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (UnregisterAudioSessionNotification) - O método exclui um registro anterior pelo cliente para receber notificações.
/// </summary>
/// <param name="Param_Notificador">Ponteiro para a interface IAudioSessionEvents implementada pelo cliente. O cliente passou esse mesmo ponteiro de interface para o Gerenciador de sessão 
/// em uma chamada anterior para o método ICarenAudioSessionControl::RegisterAudioSessionNotification. Se o (UnregisterAudioSessionNotification) método for bem-sucedido, ele chama o 
/// método Release na interface IAudioSessionEvents do cliente.</param>
CarenResult CarenAudioSessionControl::UnregisterAudioSessionNotification(ICarenAudioSessionEvents^% Param_Notificador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IAudioSessionEvents* pSessaoEventos = NULL;

	//Obtém um ponteiro para a sessão de eventos.
	Resultado = Param_Notificador->RecuperarPonteiro((LPVOID*)&pSessaoEventos);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falha..

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnregisterAudioSessionNotification(pSessaoEventos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}