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
#include "CarenMFNetProxyLocatorFactory.h"


//Destruidor.
CarenMFNetProxyLocatorFactory::~CarenMFNetProxyLocatorFactory()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMFNetProxyLocatorFactory::CarenMFNetProxyLocatorFactory(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar a classe
	if (Param_CriarInterface)
		PonteiroTrabalho = new CLN_IMFNetProxyLocatorFactory();
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFNetProxyLocatorFactory::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetProxyLocatorFactory::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetProxyLocatorFactory*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetProxyLocatorFactory**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetProxyLocatorFactory::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetProxyLocatorFactory*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetProxyLocatorFactory**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetProxyLocatorFactory::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetProxyLocatorFactory::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetProxyLocatorFactory::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetProxyLocatorFactory::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFNetProxyLocatorFactory::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetProxyLocatorFactory::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetProxyLocatorFactory::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetProxyLocatorFactory::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetProxyLocatorFactory();
}



// Métodos da interface proprietária(ICarenMFNetProxyLocatorFactory)


/// <summary>
/// Método responsável por registrar os eventos da interface.
/// </summary>
void CarenMFNetProxyLocatorFactory::RegistrarCallback()
{
	//Variaveis utilizadas no método
	Utilidades Util;

	//Configura os delegates.

	//Cria todos os delegates.
	Callback_OnCreateProxyLocator = gcnew DelegateNativo_Evento_OnCreateProxyLocator(this, &CarenMFNetProxyLocatorFactory::EncaminharEvento_OnCreateProxyLocator);

	//Converte os delegates para ponteiros do IntPtr
	IntPtr Pointer_OnCreateProxyLocator = Util.ConverterDelegateToPointer(Callback_OnCreateProxyLocator);

	//Aloca a Handle para cada delegate que fornece o método de chamado do evento.
	gHandle_Delegate_OnCreateProxyLocator = Util.AlocarPointerDelegate(Pointer_OnCreateProxyLocator);

	//Registra os delegates criados para os delegates nativo na classe CLN_IMFNetProxyLocatorFactory que envia os eventos.
	((CLN_IMFNetProxyLocatorFactory*)PonteiroTrabalho)->Evento_OnCreateProxyLocator = Util.ConverterPointerDelegateToNativeDelegate<CLN_IMFNetProxyLocatorFactory_EventoNativo_OnCreateProxyLocator>(Pointer_OnCreateProxyLocator);
}

/// <summary>
/// Método responsável por liberar todos os registros de eventos resgistrados anteriormente. Chame esse método após uma chamada para (RegistrarCallback).
/// </summary>
void CarenMFNetProxyLocatorFactory::UnRegisterCallback()
{
	//Libera o ponteiro para todos os eventos
	gHandle_Delegate_OnCreateProxyLocator.Free();

	//Libera os ponteiro da classe nativa

	//Verifica se é valido e exlui o ponteiro.
	if (ObjetoValido(((CLN_IMFNetProxyLocatorFactory*)PonteiroTrabalho)->Evento_OnCreateProxyLocator))
	{
		//Descarta o delegate.
		((CLN_IMFNetProxyLocatorFactory*)PonteiroTrabalho)->Evento_OnCreateProxyLocator = NULL;
	}
}

//Métodos que encaminham os eventos nativos gerado pela implementação da classe nativa.

HRESULT CarenMFNetProxyLocatorFactory::EncaminharEvento_OnCreateProxyLocator(LPCWSTR pszProtocol, _Outptr_ IMFNetProxyLocator** ppProxyLocator)
{
	//ESTE EVENTO É CHAMADO PELA CLASSE NATIVA (CLN_IMFNetProxyLocatorFactory) PARA O USUÁRIO
	//CRIA E CONFIGURAR O PROXY LOCATOR. O USUÁRIO DEVE CRIAR A INTERFACE IMFNetProxyLocator E RETORNAR
	//SUA REPRESENTAÇÃO GERENCIADA PARA ENTÃO ESTE MÉTODO TRADUZIR PARA SUA NATIVA E RETORNAR A FONTE DE MIDIA.

	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis.
	ICarenMFNetProxyLocator^ vi_GerenciadoProxyLocator = nullptr; //Interface gerenciada que vai ser retornada com o proxy locator.
	IMFNetProxyLocator* vi_pNativeProxyLocator = Nulo; //O proxy locator nativo criado pelo usuário.
	String^ vi_Protocolo = nullptr; // O protocolo desejado pela fonte de midia.

	//Verifica se informou o protocolo e cria a string com os dados.
	if (ObjetoValido(pszProtocol))
		vi_Protocolo = gcnew String(pszProtocol);

	//Chama o evento da classe para notificar o usuário e ele criar os dados.
	Resultado = OnCreateProxyLocator(vi_Protocolo, vi_GerenciadoProxyLocator);

	//Verifica se não houve erro e sai do método.
	if (!CarenSucesso(Resultado))
		Sair;

	//Recupera o ponteiro nativo para o proxy locator criado pelo usuário.
	CarenGetPointerFromICarenSafe(vi_GerenciadoProxyLocator, vi_pNativeProxyLocator);

	//Define o Proxy locator criado pelo usuário no parametro de saida para a fonte de midia.
	*ppProxyLocator = vi_pNativeProxyLocator;

Done:;
	//Retorna o resultado geral.
	return static_cast<HRESULT>(Resultado.HResult);
}
