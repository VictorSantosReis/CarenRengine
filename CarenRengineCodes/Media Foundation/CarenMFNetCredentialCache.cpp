﻿/*
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
#include "CarenMFNetCredentialCache.h"


//Destruidor.
CarenMFNetCredentialCache::~CarenMFNetCredentialCache()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFNetCredentialCache::CarenMFNetCredentialCache(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IMFNetCredentialCache* vi_pOutCredentialCache = Nulo;

		//Chama o método para criar a interface.
		Hr = MFCreateCredentialCache(&vi_pOutCredentialCache);

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define o ponteiro criado no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutCredentialCache;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFNetCredentialCache::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredentialCache::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredentialCache*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredentialCache**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetCredentialCache::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetCredentialCache*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetCredentialCache**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredentialCache::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetCredentialCache::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetCredentialCache::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetCredentialCache::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetCredentialCache::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetCredentialCache::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetCredentialCache::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetCredentialCache();
}



// Métodos da interface proprietária(ICarenMFNetCredentialCache)


/// <summary>
/// Recupera o objeto de credencial para a URL especificada.
/// </summary>
/// <param name="Param_Url">Uma string contendo a URL para a qual a credencial é necessária.</param>
/// <param name="Param_Realm">Uma string contendo o Realm(Define o espaço de proteção do servidor, é um dominio protegido que pode ser compartilhado) para a autenticação.</param>
/// <param name="Param_FlagsAutenticacao">Bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetAuthenticationFlags.</param>
/// <param name="Param_Out_Credencial">Recebe um ponteiro para a interface ICarenMFNetCredential. O chamador deve liberar a interface.</param>
/// <param name="Param_Out_FlagsRequerimento">Recebe bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetCredentialRequirements.</param>
CarenResult CarenMFNetCredentialCache::GetCredential(
String^ Param_Url, 
String^ Param_Realm, 
CA_MFNetAuthenticationFlags Param_FlagsAutenticacao, 
[Out] ICarenMFNetCredential^% Param_Out_Credencial, 
[Out] CA_MFNetCredentialRequirements% Param_Out_FlagsRequerimento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pUrl = Nulo;
	PWSTR vi_pRealm = Nulo;
	DWORD vi_FlagsAuth = static_cast<DWORD>(Param_FlagsAutenticacao);
	IMFNetCredential* vi_pOutCredential = Nulo;
	DWORD vi_OutCredentialRequires;

	//Converte as strings para representações nativas.
	vi_pUrl = Util.ConverterStringToWCHAR(Param_Url);
	vi_pRealm = Util.ConverterStringToWCHAR(Param_Realm);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCredential(vi_pUrl, vi_pRealm, vi_FlagsAuth, &vi_pOutCredential, &vi_OutCredentialRequires);

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

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_pOutCredential, Param_Out_Credencial, true);

	//Define os flags no parametro de saida.
	Param_Out_FlagsRequerimento = static_cast<CA_MFNetCredentialRequirements>(vi_OutCredentialRequires);

Done:;
	//Libera a memória utilizada pelas strings.
	DeletarStringAllocatedSafe(&vi_pUrl);
	DeletarStringAllocatedSafe(&vi_pRealm);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Relata se o objeto de credencial fornecido passou com sucesso no desafio de autenticação.
/// </summary>
/// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential.</param>
/// <param name="Param_Resultado">TRUE se o objeto de credencial teve sucesso no desafio de autenticação; caso contrário, FALSE.</param>
CarenResult CarenMFNetCredentialCache::SetGood(
ICarenMFNetCredential^ Param_Credencial, 
Boolean Param_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFNetCredential* vi_pCredential = Nulo;

	//Recupera o ponteiro para a interface de credencial.
	CarenGetPointerFromICarenSafe(Param_Credencial, vi_pCredential);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGood(vi_pCredential, Param_Resultado ? TRUE : FALSE);

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
/// Especifica como as credenciais do usuário são armazenadas.
/// </summary>
/// <param name="Param_Credencial">Ponteiro para a interface ICarenMFNetCredential. Obtenha este ponteiro ligando para ICarenMFNetCredentialCache::ObterCredencial.</param>
/// <param name="Param_Opcoes">Bitwise OU de zero ou mais bandeiras da enumeração CA_MFNetCredentialOptions.</param>
CarenResult CarenMFNetCredentialCache::SetUserOptions(
ICarenMFNetCredential^ Param_Credencial, 
CA_MFNetCredentialOptions Param_Opcoes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFNetCredential* vi_pCredential = Nulo;

	//Recupera o ponteiro para a interface de credencial.
	CarenGetPointerFromICarenSafe(Param_Credencial, vi_pCredential);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetUserOptions(vi_pCredential, static_cast<DWORD>(Param_Opcoes));

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