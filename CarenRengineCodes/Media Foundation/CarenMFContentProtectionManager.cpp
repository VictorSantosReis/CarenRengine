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
#include "CarenMFContentProtectionManager.h"

//Destruidor.
CarenMFContentProtectionManager::~CarenMFContentProtectionManager()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFContentProtectionManager::CarenMFContentProtectionManager()
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
CarenResult CarenMFContentProtectionManager::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFContentProtectionManager::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFContentProtectionManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFContentProtectionManager**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFContentProtectionManager::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFContentProtectionManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFContentProtectionManager**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFContentProtectionManager::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFContentProtectionManager::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFContentProtectionManager::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFContentProtectionManager::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFContentProtectionManager::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFContentProtectionManager::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFContentProtectionManager::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFContentProtectionManager::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFContentProtectionManager();
}





// Métodos da interface proprietária(ICarenMFContentProtectionManager)


/// <summary>
/// Começa uma solicitação assíncrona para executar uma ação de habilitação de conteúdo.
/// Este método solicita que o aplicativo execute uma etapa específica necessária para adquirir direitos sobre o conteúdo, usando um objeto ativador de conteúdo.
/// </summary>
/// <param name="Param_Ativador">Ponteiro para a interface ICarenMFActivate de um objeto ativador de conteúdo. Para criar o ativador de conteúdo, ligue para 
/// o método ICarenMFActivate::ActivateObject e solicite a interface IMFContentEnabler. O aplicativo deve usar os métodos no IMFContentEnabler para concluir 
/// a ação de habilitação de conteúdo.</param>
/// <param name="Param_Topologia">Ponteiro para a interface ICarenMFTopology da topologia pendente.</param>
/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. Quando a operação estiver concluída, o aplicativo 
/// deve chamar ICarenMFAsyncCallback::Invoke no retorno de chamada.</param>
/// <param name="Param_ObjetoEstado">Reservado. Atualmente este parâmetro é sempre NULO.</param>
CarenResult CarenMFContentProtectionManager::BeginEnableContent(
ICarenMFActivate^ Param_Ativador, 
ICarenMFTopology^ Param_Topologia, 
ICarenMFAsyncCallback^ Param_Callback, 
ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFActivate* vi_pAtivador = Nulo;
	IMFTopology* vi_pTopologia = Nulo;
	IMFAsyncCallback* vi_pCallback = Nulo;
	//IUnknown* vi_pObjetoEstado = Nulo; 

	//Recupera o ponteiro para a interface de ativação.
	CarenGetPointerFromICarenSafe(Param_Ativador, vi_pAtivador);
	//Recupera o ponteiro para a topologia
	CarenGetPointerFromICarenSafe(Param_Topologia, vi_pTopologia);
	//Recupera o ponteiro para o callback
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginEnableContent(vi_pAtivador, vi_pTopologia, vi_pCallback, Nulo);

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
/// Termina uma solicitação assíncrona para executar uma ação de habilitação de conteúdo. Esse método é chamado pelo caminho de mídia 
/// protegida (PMP) para concluir uma chamada assíncrona ao ICarenMFContentProtectionManager::EnableContentAsync.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para a interface IMFAsyncResultado. Este ponteiro é o mesmo valor que o aplicativo passou para o método 
/// ICarenMFAsyncCallback:::Invoke.</param>
CarenResult CarenMFContentProtectionManager::EndEnableContent(ICarenMFAsyncResult^ Param_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* vi_pResultado = Nulo;

	//Recupera o ponteiro para a interface do resultado.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pResultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndEnableContent(vi_pResultado);

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