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
#include "CarenMFNetProxyLocator.h"


//Destruidor.
CarenMFNetProxyLocator::~CarenMFNetProxyLocator()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFNetProxyLocator::CarenMFNetProxyLocator()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}

CarenMFNetProxyLocator::CarenMFNetProxyLocator(String^ Param_Protocol, ICarenPropertyStore^ Param_ProxyConfig)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	PWSTR vi_pProtocolName = Nulo;
	IPropertyStore* vi_pStoreConfig = Nulo;
	IMFNetProxyLocator* vi_pOutNetProxyLocator = Nulo;

	//Converte a string para o nome do protocolo.
	vi_pProtocolName = Util.ConverterStringToWCHAR(Param_Protocol);

	//Verfifica se a interface da loja de propriedades é valida.
	if (!ObjetoGerenciadoValido(Param_ProxyConfig))
		throw gcnew NullReferenceException("A interface no parametro (Param_ProxyConfig) não pode ser NULA!");

	//Tenta recuperar o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_ProxyConfig, &vi_pStoreConfig);

	//Verifica se não houve algum erro
	if (!CarenSucesso(Resultado))
		throw gcnew Exception("Falhou ao tentar recuperar o ponteiro para a interface da loja de propriedades.");

	//Chama o método para criar a interface.
	Hr = MFCreateProxyLocator(const_cast<PWSTR>(vi_pProtocolName), vi_pStoreConfig, &vi_pOutNetProxyLocator);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutNetProxyLocator;

	//Libera a memória utilizada pela string.
	DeletarStringAllocatedSafe(&vi_pProtocolName);
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFNetProxyLocator::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetProxyLocator::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetProxyLocator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetProxyLocator**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFNetProxyLocator::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFNetProxyLocator*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFNetProxyLocator**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetProxyLocator::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFNetProxyLocator::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFNetProxyLocator::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFNetProxyLocator::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFNetProxyLocator::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFNetProxyLocator::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFNetProxyLocator::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFNetProxyLocator::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFNetProxyLocator();
}



// Métodos da interface proprietária(ICarenMFNetProxyLocator)


/// <summary>
/// Cria uma nova instância do localizador proxy padrão.
/// </summary>
/// <param name="Param_Out_ProxyLocator">Recebe um ponteiro para a interface ICarenMFNetProxyLocator do novo proxy locator. O chamador deve liberar a interface.</param>
CarenResult CarenMFNetProxyLocator::Clone([Out] ICarenMFNetProxyLocator^% Param_Out_ProxyLocator)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFNetProxyLocator* vi_OutProxyLocator = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Clone(&vi_OutProxyLocator);

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
	Param_Out_ProxyLocator = gcnew CarenMFNetProxyLocator();

	//Define o ponteiro na interface
	CarenSetPointerToICarenSafe(vi_OutProxyLocator, Param_Out_ProxyLocator, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o objeto localizador proxy.
/// </summary>
/// <param name="Param_Host">Uma string contendo o nome de host do servidor de destino</param>
/// <param name="Param_Url">Uma string contendo a URL de destino.</param>
/// <param name="Param_Reservado">Reservados. Definido como FALSE.</param>
CarenResult CarenMFNetProxyLocator::FindFirstProxy(
String^ Param_Host, 
String^ Param_Url, 
Boolean Param_Reservado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pHost = Nulo;
	PWSTR vi_pUrl = Nulo;

	//Converte as strings.
	vi_pHost = Util.ConverterStringToWCHAR(Param_Host);
	vi_pUrl = Util.ConverterStringToWCHAR(Param_Url);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindFirstProxy(vi_pHost, vi_pUrl, Param_Reservado ? TRUE : FALSE);

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
	//Libera a memória utilizada pelas strings.
	DeletarStringAllocatedSafe(&vi_pHost);
	DeletarStringAllocatedSafe(&vi_pUrl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina o próximo proxy a ser usado.
/// </summary>
CarenResult CarenMFNetProxyLocator::FindNextProxy()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindNextProxy();

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
/// Recupera as informações de proxy atuais, incluindo nome de host e porta.
/// </summary>
/// <param name="Param_Ref_ProxyHostname">Recebe uma string contendo o nome do host proxy e a porta. Defina como NULO para receber a largura necessária para receber os dados.</param>
/// <param name="Param_Ref_Largura">Na entrada, especifica o número de elementos em Param_Ref_ProxyHostname. Na saída, recebe o tamanho necessário do buffer.</param>
CarenResult CarenMFNetProxyLocator::GetCurrentProxy(
String^% Param_Ref_ProxyHostname, 
UInt32% Param_Ref_Largura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR vi_pOutProxy = Nulo; //Pode ser NULO para o usuário obter a largura necessária.
	DWORD vi_InOutLargura = static_cast<DWORD>(Param_Ref_Largura);

	//Verifica se vai obter a string e aloca memória
	if (ObjetoGerenciadoValido(Param_Ref_ProxyHostname))
		vi_pOutProxy = CriarStringCoTask<WCHAR>(Param_Ref_Largura);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentProxy(ObjetoGerenciadoValido(Param_Ref_ProxyHostname) ? vi_pOutProxy: Nulo, &vi_InOutLargura);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Verifica se vai retornar a string com os dados.
	if (ObjetoValido(vi_pOutProxy))
		Param_Ref_ProxyHostname = gcnew String(vi_pOutProxy);

	//Define a largura da string no parametro de saida.
	Param_Ref_Largura = static_cast<UInt32>(vi_InOutLargura);

Done:;
	//Libera a memória utilizada pela string.
	DeletarStringCoTaskSafe(&vi_pOutProxy);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Mantém um registro do sucesso ou falha do uso do proxy atual.
/// </summary>
/// <param name="Param_hrOp">HRESULT especificando o resultado do uso do proxy atual para conexão.</param>
CarenResult CarenMFNetProxyLocator::RegisterProxyResult(Int32 Param_hrOp)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterProxyResult(static_cast<HRESULT>(Param_hrOp));

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