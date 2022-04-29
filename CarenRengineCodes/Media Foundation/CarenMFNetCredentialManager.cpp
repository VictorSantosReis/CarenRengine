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
#include "CarenMFNetCredentialManager.h"

//Destruidor.
CarenMFNetCredentialManager::~CarenMFNetCredentialManager()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFNetCredentialManager::CarenMFNetCredentialManager()
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
CarenResult CarenMFNetCredentialManager::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredentialManager::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredentialManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredentialManager**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredentialManager::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredentialManager*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredentialManager**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredentialManager::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredentialManager::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetCredentialManager::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetCredentialManager::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFNetCredentialManager::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetCredentialManager::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetCredentialManager::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetCredentialManager::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetCredentialManager();
}



// Métodos da interface proprietária(ICarenMFNetCredentialManager)


/// <summary>
/// Começa uma solicitação assíncrona para recuperar as credenciais do usuário.
/// </summary>
/// <param name="Param_GetParam">Uma estrutura MFNetCredentialManagerGetParam.</param>
/// <param name="Param_Callback">Ponteiro para a interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface.</param>
/// <param name="Param_ObjetoEstado">Um ponteiro para um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. O objeto é devolvido ao chamador quando o retorno de 
/// chamada é invocado.</param>
CarenResult CarenMFNetCredentialManager::BeginGetCredentials(
CA_MFNetCredentialManagerGetParam^ Param_GetParam, 
ICarenMFAsyncCallback^ Param_Callback, 
ICaren^ Param_ObjetoEstado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	MFNetCredentialManagerGetParam* vi_pParams = Nulo;
	IMFAsyncCallback* vi_pCallback = Nulo;
	IUnknown* vi_pObjetoEstado = Nulo;

	//Converte a estrutura gerenciada
	vi_pParams = Util.ConverterMFNetCredentialManagerGetParamManaged_ToUnamaged(Param_GetParam);

	//Recupera um ponteiro para o Callback.
	CarenGetPointerFromICarenSafe(Param_Callback, vi_pCallback);

	//Recupera um ponteiro para o objeto de estado se valido.
	if (ObjetoGerenciadoValido(Param_ObjetoEstado))
		CarenGetPointerFromICarenSafe(Param_ObjetoEstado, vi_pObjetoEstado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->BeginGetCredentials(vi_pParams, vi_pCallback, vi_pObjetoEstado);

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
	//Libera a memória utilizada pela estrutura
	DeletarStringAllocatedSafe(&vi_pParams->pszUrl);
	DeletarStringAllocatedSafe(&vi_pParams->pszRealm);
	DeletarStringAllocatedSafe(&vi_pParams->pszPackage);
	DeletarStringAllocatedSafe(&vi_pParams->pszSite);
	DeletarEstruturaSafe(&vi_pParams);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Completa uma solicitação assíncrona para recuperar as credenciais do usuário.
/// </summary>
/// <param name="Param_Resultado">Ponteiro para uma interface ICarenMFAsyncResult que contém o resultado assíncrono.</param>
/// <param name="Param_Out_Credencial">Recebe um ponteiro para a interface ICarenMFNetCredential, que é usada para recuperar as credenciais. O chamador deve liberar a interface.</param>
CarenResult CarenMFNetCredentialManager::EndGetCredentials(
ICarenMFAsyncResult^ Param_Resultado, 
[Out] ICarenMFNetCredential^% Param_Out_Credencial)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFAsyncResult* vi_pResultado = Nulo;
	IMFNetCredential* vi_pOutCredential = Nulo;

	//Recupera o ponteiro para o resultado.
	CarenGetPointerFromICarenSafe(Param_Resultado, vi_pResultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndGetCredentials(vi_pResultado, &vi_pOutCredential);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Credencial = gcnew CarenMFNetCredential();

	//Define o ponteiro na interace 
	CarenSetPointerToICarenSafe(vi_pOutCredential, Param_Out_Credencial, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica se as credenciais do usuário tiveram sucesso no desafio de autenticação. A fonte da rede chama esse método para informar o aplicativo se as credenciais do 
/// usuário foram autenticadas.
/// </summary>
//// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential.</param>
/// <param name="Param_Resultado">Valor booleano. O valor é TRUE se as credenciais tiverem êxito no desafio de autenticação. Caso contrário, o valor é FALSE.</param>
CarenResult CarenMFNetCredentialManager::SetGood(
ICarenMFNetCredential^ Param_Credencial,
Boolean Param_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFNetCredential* vi_pCredencial = Nulo;

	//Recupera o ponteiro para a credencial.
	CarenGetPointerFromICarenSafe(Param_Credencial, vi_pCredencial);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGood(vi_pCredencial, Param_Resultado ? TRUE : FALSE);

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