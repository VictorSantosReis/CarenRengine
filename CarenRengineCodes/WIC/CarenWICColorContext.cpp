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
#include "CarenWICColorContext.h"

//Destruidor.
CarenWICColorContext::~CarenWICColorContext()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenWICColorContext::CarenWICColorContext()
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
CarenResult CarenWICColorContext::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICColorContext::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICColorContext*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICColorContext**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenWICColorContext::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IWICColorContext*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IWICColorContext**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICColorContext::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenWICColorContext::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenWICColorContext::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenWICColorContext::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenWICColorContext::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenWICColorContext::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenWICColorContext::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenWICColorContext::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenWICColorContext();
}



// Métodos da interface proprietária(ICarenWICColorContext)


/// <summary>
/// Recupera o contexto de cor do Arquivo de Imagem Exchangeable (EXIF). 
/// Este método só deve ser usado quando o ICarenWICColorContext::GetType indica WICColorContextExifColorSpace.
/// </summary>
/// <param name="Param_Out_Valor">Recebe o contexto de cor exif de cores. 1 - Espaço de cores sRGB, 2 - Espaço de cores Adobe RGB, 3 a 65534 utilizadas.</param>
CarenResult CarenWICColorContext::GetExifColorSpace([Out] UInt32% Param_Out_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT32 OutValor = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetExifColorSpace(&OutValor);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define no parametro de saida.
	Param_Out_Valor = OutValor;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o perfil de contexto de cores. Use somente este método se o tipo de contexto for WICColorContextProfile.
/// Chamar este método com (Param_Ref_Buffer) definido para NULO fará com que ele retorne o tamanho do buffer necessário no (Param_Out_SizeAtual).
/// </summary>
/// <param name="Param_SizeBuffer">O tamanho do buffer em (Param_Ref_Buffer).</param>
/// <param name="Param_Ref_Buffer">Um ponteiro que recebe o perfil de contexto de cores.</param>
/// <param name="Param_Out_SizeAtual">Recebe o tamanho real do buffer necessário para recuperar todo o perfil do contexto de cores.</param>
CarenResult CarenWICColorContext::GetProfileBytes(
UInt32 Param_SizeBuffer,
ICarenBuffer^% Param_Ref_Buffer,
[Out] UInt32% Param_Out_SizeAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer pBufferDados = DefaultGenPointer; //Pode ser zero para recupera o tamanho do buffer necessário.
	UINT32 OutSizeAtual = 0;

	//Recupera o ponteiro para o buffer se ele tiver sido informado
	if (ObjetoGerenciadoValido(Param_Ref_Buffer))
		Param_Ref_Buffer->GetInternalPointer(pBufferDados);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetProfileBytes(Param_SizeBuffer, Param_Ref_Buffer == nullptr ? NULL : Util.ConverterIntPtrTo<PBYTE>(pBufferDados), &OutSizeAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor do buffer atual no parametro de saida.
	Param_Out_SizeAtual = OutSizeAtual;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o tipo de contexto de cor. 
/// </summary>
/// <param name="Param_Out_Type">Recebe o enum CA_WICColorContextType do contexto de cores.</param>
CarenResult CarenWICColorContext::GetType([Out] CA_WICColorContextType% Param_Out_Type)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	WICColorContextType OutColorcontextType;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetType(&OutColorcontextType);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_Type = static_cast<CA_WICColorContextType>(OutColorcontextType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o contexto de cores usando um espaço de cor EXIF (Exchangeable Image File, arquivo de imagem e imagem" do Arquivo de Imagem. 
/// Uma vez iniciado um contexto de cor, ele não pode ser reinicializado.
/// </summary>
/// <param name="Param_Valor">O valor do espaço de cores EXIF. 1 - Espaço de cores sRGB, 2 - Espaço de cores Adobe RGB.</param>
CarenResult CarenWICColorContext::InitializeFromExifColorSpace(UInt32 Param_Valor)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromExifColorSpace(Param_Valor);

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
/// Inicializa o contexto de cores a partir do arquivo dado. 
/// </summary>
/// <param name="Param_NomeArquivo">A url para o arquivo.</param>
CarenResult CarenWICColorContext::InitializeFromFilename(String^ Param_NomeArquivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pUrlArquivo = NULL;

	//Converte a string gerenciada.
	pUrlArquivo = Util.ConverterStringToWCHAR(Param_NomeArquivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromFilename(pUrlArquivo);

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
	//Libera a memória urilizada pela url.
	DeletarStringAllocatedSafe(&pUrlArquivo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Inicializa o contexto de cores a partir de um bloco de memória. 
/// </summary>
/// <param name="Param_Buffer">O buffer usado para inicializar o ICarenWICColorContext.</param>
/// <param name="Param_SizeBuffer">O tamanho do buffer em (Param_Buffer).</param>
CarenResult CarenWICColorContext::InitializeFromMemory(
ICarenBuffer^ Param_Buffer,
UInt32 Param_SizeBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer pBufferDados = DefaultGenPointer;

	//Recupera o ponteiro para o buffer.
	Resultado = Param_Buffer->GetInternalPointer(pBufferDados);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InitializeFromMemory(const_cast<BYTE*>(Util.ConverterIntPtrTo<PBYTE>(pBufferDados)), Param_SizeBuffer);

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