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
#include "CarenMFMediaBuffer.h"


//Destruidor.
CarenMFMediaBuffer::~CarenMFMediaBuffer()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Construtores
CarenMFMediaBuffer::CarenMFMediaBuffer()
{
	
}
CarenMFMediaBuffer::CarenMFMediaBuffer(UInt32 Param_Lenght)
{
	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Chama o método para realizar a operação
	Hr = MFCreateMemoryBuffer(static_cast<DWORD>(Param_Lenght), &vi_pOutMediaBuffer);

	//Verifica se não ocorreu algum erro
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao tentar criar o buffer. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutMediaBuffer;
}
CarenMFMediaBuffer::CarenMFMediaBuffer(UInt32 Param_Lenght, Enumeracoes::CA_MF_BYTE_ALIGNMENT Param_Alignment)
{
	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Chama o método para realizar a operação
	Hr = MFCreateAlignedMemoryBuffer(static_cast<DWORD>(Param_Lenght), static_cast<DWORD>(Param_Alignment), &vi_pOutMediaBuffer);

	//Verifica se não ocorreu algum erro
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao tentar criar o buffer. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutMediaBuffer;
}
CarenMFMediaBuffer::CarenMFMediaBuffer(UInt32 Param_Width, UInt32 Param_Height, CA_D3DFORMAT Param_D3DFormat, Boolean Param_BottomUp)
{
	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DWORD vi_D3DFormat = static_cast<DWORD>(Param_D3DFormat);
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Chama o método para realizar a operação
	Hr = MFCreate2DMediaBuffer(static_cast<DWORD>(Param_Width), static_cast<DWORD>(Param_Height), vi_D3DFormat, Param_BottomUp? TRUE: FALSE, &vi_pOutMediaBuffer);

	//Verifica se não ocorreu algum erro
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao tentar criar o buffer. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutMediaBuffer;
}
CarenMFMediaBuffer::CarenMFMediaBuffer(UInt32 Param_Width, UInt32 Param_Height, UInt32 Param_FourCC, Boolean Param_BottomUp)
{
	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Chama o método para realizar a operação
	Hr = MFCreate2DMediaBuffer(static_cast<DWORD>(Param_Width), static_cast<DWORD>(Param_Height), static_cast<DWORD>(Param_FourCC), Param_BottomUp ? TRUE : FALSE, &vi_pOutMediaBuffer);

	//Verifica se não ocorreu algum erro
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao tentar criar o buffer. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutMediaBuffer;
}
CarenMFMediaBuffer::CarenMFMediaBuffer(ICarenMFMediaBuffer^ Param_Buffer, UInt32 Param_Offset, UInt32 Param_Lenght)
{
	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFMediaBuffer* vi_pMediaBufferOriginal = Nulo;
	IMFMediaBuffer* vi_pOutMediaBuffer = Nulo;

	//Recupera o ponteiro para o buffer original se valido
	if (!ObjetoGerenciadoValido(Param_Buffer))
		throw gcnew NullReferenceException("O parametro (Param_Buffer) não pode ser NULO.");

	//Recupera o ponteiro.
	CarenResult Resultado = RecuperarPonteiroCaren(Param_Buffer, &vi_pMediaBufferOriginal);

	//Verifica se obteve com sucesso.
	if(Resultado.StatusCode != ResultCode::SS_OK)
		throw gcnew NullReferenceException("O ponteiro da interface (ICarenMFMediaBuffer) no parametro (Param_Buffer) não é válido.");

	//Chama o método para realizar a operação
	Hr = MFCreateMediaBufferWrapper(vi_pMediaBufferOriginal, static_cast<DWORD>(Param_Offset), static_cast<DWORD>(Param_Lenght), &vi_pOutMediaBuffer);

	//Verifica se não ocorreu algum erro
	if (!Sucesso(Hr))
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao tentar criar um Wrapper do buffer. Mensagem de erro -> ", Util.TranslateCodeResult(Hr)));

	//Define a interface criada no ponteiro de trabalho da classe.
	PonteiroTrabalho = vi_pOutMediaBuffer;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFMediaBuffer::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaBuffer::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaBuffer**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFMediaBuffer::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFMediaBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFMediaBuffer**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaBuffer::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFMediaBuffer::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFMediaBuffer::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFMediaBuffer::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFMediaBuffer::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFMediaBuffer::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFMediaBuffer::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFMediaBuffer::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFMediaBuffer();
}





// Métodos da interface proprietária (ICarenMFMediaBuffer)


/// <summary>
/// Recupera o comprimento dos dados válidos no buffer.
/// </summary>
/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos, em bytes. Se o buffer não contiver nenhum dado válido, o valor será zero.</param>
CarenResult CarenMFMediaBuffer::GetCurrentLength([Out] UInt32% Param_Out_LarguraAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel que contém os resultados COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	DWORD vi_OutLarguraAtual = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetCurrentLength(&vi_OutLarguraAtual);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor de retorno
	Param_Out_LarguraAtual = static_cast<UInt32>(vi_OutLarguraAtual);

Done:;
	//Retorna o resultado geral
	return Resultado;
}

/// <summary>
/// Recupera o Dimensionar alocado do buffer. Esse o valor da largura total
/// de dados que podem ser adicioandos. Se o buffer conter dados, a largura dos dados
/// podem ser menor que a lagrura máxima. Consulte (GetCurrentLength) para obter o 
/// valor real da largura dos dados neste Buffer.
/// </summary>
/// <param name="Param_Out_LarguraMaxima">Recebe a largura total de dados que esse buffer pode conter.</param>
CarenResult CarenMFMediaBuffer::GetMaxLength([Out] UInt32 % Param_Out_LarguraMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel que contém os resultados COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	DWORD vi_OutMaxLengthBuffer = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMaxLength(&vi_OutMaxLengthBuffer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o valor de retorno
	Param_Out_LarguraMaxima = static_cast<UInt32>(vi_OutMaxLengthBuffer);

Done:;
	//Retorna o resultado geral
	return Resultado;
}

/// <summary>
/// Force acesso aos dados que estão presentes neste buffer, para leitura ou gravação.
/// Esse método fornece o acesso do chamador para o buffer inteiro, até o tamanho máximo retornado no Param_LarguraMaximaEscrita parâmetro. O valor retornado em Param_LarguraAtual 
/// é o tamanho de todos os dados válidos já no buffer, que pode ser menor do que o tamanho do buffer total.
/// </summary>
/// <param name="Param_Out_BufferMidia">Recebe a interface responsável por gerenciar o buffer preso(Lock). Você poder: Write e Read para o buffer.</param>
/// <param name="Param_Out_LarguraMaximaEscrita">Recebe a quantidade máxima de dados que podem ser gravados para o buffer. Este parâmetro pode ser (NULO).</param>
/// <param name="Param_Out_LarguraAtual">Recebe o comprimento dos dados válidos no buffer, em bytes. Este parâmetro pode ser (NULO).</param>
CarenResult CarenMFMediaBuffer::Lock([Out] ICarenBuffer^% Param_Out_BufferMidia, [Out] UInt32% Param_Out_LarguraMaximaEscrita, [Out] UInt32% Param_Out_LarguraAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel que contém os resultados COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas pelo método
	PBYTE vi_pBufferLocked = NULL;
	DWORD vi_OutMaxLenghtBuffer = 0;
	DWORD vi_OutActualLenght = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Lock(&vi_pBufferLocked, &vi_OutMaxLenghtBuffer, &vi_OutActualLenght);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o buffer de dados.
	Param_Out_BufferMidia = gcnew CarenBuffer();

	//Chama o método que vai criar o buffer da classe com base no buffer retornado pelo método Lock
	Resultado = Param_Out_BufferMidia->CreateBuffer(IntPtr(vi_pBufferLocked), false, vi_OutMaxLenghtBuffer, vi_OutActualLenght);

	//Verifica se obteve sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao definir o ponteiro.
		
		//Define o erro no sistema principal.
		Resultado.AdicionarCodigo(Resultado.StatusCode, false);

		//Libera o buffer capturado.
		PonteiroTrabalho->Unlock();

		//Libera a interface
		Param_Out_BufferMidia = nullptr;

		//Sai do método
		Sair;
	}

	//Define os dados de largura.
	Param_Out_LarguraMaximaEscrita = vi_OutMaxLenghtBuffer;
	Param_Out_LarguraAtual = vi_OutActualLenght;

Done:;

	//Retorna o resultado geral
	return Resultado;
}

/// <summary>
/// Desbloqueia um buffer que foi bloqueado anteriormente. Chame esse método uma vez para cada chamada no método (Lock).
/// É um erro chamar Unlock se você não chamar Lock anteriormente. Depois de chamar esse método, (Não Use) a interface 
/// retornada pelo Lock método. Não é mais garantido que o buffer que contenha nela seja valido.
/// </summary>
CarenResult CarenMFMediaBuffer::Unlock()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel que contém os resultados COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Unlock();

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
	//Retorna o resultado geral
	return Resultado;
}

/// <summary>
/// Define o comprimento dos dados válidos no buffer.
/// ATENCAO: Chame esse método se você gravar dados no buffer.
/// </summary>
/// <param name="Param_LarguraAtual">Comprimento dos dados válidos, em bytes. Esse valor não pode ser maior do que o tamanho alocado do buffer,
/// que é retornado pelo método (GetMaxLength).</param>
CarenResult CarenMFMediaBuffer::SetCurrentLength(UInt32 Param_LarguraAtual)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variavel que contém os resultados COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCurrentLength(Param_LarguraAtual);

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
	//Retorna o resultado geral
	return Resultado;
}
