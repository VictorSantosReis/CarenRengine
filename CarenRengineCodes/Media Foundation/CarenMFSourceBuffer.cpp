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
#include "CarenMFSourceBuffer.h"

//Destruidor.
CarenMFSourceBuffer::~CarenMFSourceBuffer()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFSourceBuffer::CarenMFSourceBuffer()
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
CarenResult CarenMFSourceBuffer::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceBuffer::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceBuffer**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFSourceBuffer::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFSourceBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFSourceBuffer**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceBuffer::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFSourceBuffer::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFSourceBuffer::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFSourceBuffer::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMFSourceBuffer::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFSourceBuffer::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFSourceBuffer::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFSourceBuffer::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFSourceBuffer();
}



// Métodos da interface proprietária(ICarenMFSourceBuffer)


/// <summary>
/// Aborta o processamento do segmento de mídia atual.
/// </summary>
CarenResult CarenMFSourceBuffer::Abort()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Abort();

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

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Anexa o segmento de mídia especificado ao ICarenMFSourceBuffer.
/// </summary>
/// <param name="Param_Buffer">Os dados da mídia para anexar.</param>
/// <param name="Param_LarguraBuffer">O comprimento dos dados de mídia armazenados em Param_Buffer.</param>
CarenResult CarenMFSourceBuffer::Append(
ICarenBuffer^ Param_Buffer, 
UInt32 Param_LarguraBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_Buffer = DefaultGenPointer;

	//Recupera o ponteiro para o buffer.
	CarenGetPointerFromICarenBufferSafe(Param_Buffer, vi_Buffer);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Append(Util.ConverterIntPtrTo<PBYTE>(vi_Buffer), static_cast<DWORD>(Param_LarguraBuffer));

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

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Anexa o segmento de mídia do fluxo de byte especificado para o ICarenMFSourceBuffer.
/// </summary>
/// <param name="Param_Fluxo">Os dados do fluxo de mídia.</param>
/// <param name="Param_Ref_LarguraMaxima">A duração máxima dos dados do segmento de mídia.</param>
CarenResult CarenMFSourceBuffer::AppendByteStream(
ICarenMFByteStream^ Param_Fluxo, 
UInt64% Param_Ref_LarguraMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IMFByteStream* vi_pFluxo = Nulo;
	UINT64 vi_InOutLagruraMaxima = Param_Ref_LarguraMaxima;

	//Recupera o ponteiro para o fluxo de bytes.
	CarenGetPointerFromICarenSafe(Param_Fluxo, vi_pFluxo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AppendByteStream(vi_pFluxo, &vi_InOutLagruraMaxima);

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

	//Define a largura maxima no parametro de saida.
	Param_Ref_LarguraMaxima = vi_InOutLagruraMaxima;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o carimbo de tempo para o fim da janela de acrescimo.
/// </summary>
/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o fim.</param>
void CarenMFSourceBuffer::GetAppendWindowEnd([Out] double% Param_Out_Timestamp)
{
	//Chama o método para realizar a operação.
	Param_Out_Timestamp = PonteiroTrabalho->GetAppendWindowEnd();
}

/// <summary>
/// Obtém o carimbo de tempo para o início da janela de acrescimo.
/// </summary>
/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo para o inicio.</param>
void CarenMFSourceBuffer::GetAppendWindowStart([Out] double% Param_Out_Timestamp)
{
	//Chama o método para realizar a operação.
	Param_Out_Timestamp = PonteiroTrabalho->GetAppendWindowStart();
}

/// <summary>
/// Obtém o intervalo de tempo em Buffer.
/// </summary>
/// <param name="Param_Out_Buffered">Retorna uma interface com o intervalo de tempo Buffered.</param>
CarenResult CarenMFSourceBuffer::GetBuffered([Out] ICarenMFMediaTimeRange^% Param_Out_Buffered)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IMFMediaTimeRange* vi_pOutTimeRange = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBuffered(&vi_pOutTimeRange);

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

	//Cria a interface a ser retornada.
	Param_Out_Buffered = gcnew CarenMFMediaTimeRange();

	//Define o ponteiro na interface.
	CarenSetPointerToICarenSafe(vi_pOutTimeRange, Param_Out_Buffered, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém a compensação de carimbo de tempo para fluxos de mídia anexados ao ICarenMFSourceBuffer.
/// </summary>
/// <param name="Param_Out_Timestamp">Retorna o carimbo de tempo compesado para fluxos anexados.</param>
void CarenMFSourceBuffer::GetTimeStampOffset([Out] double% Param_Out_Timestamp)
{
	//Chama o método para realizar a operação.
	Param_Out_Timestamp = PonteiroTrabalho->GetTimeStampOffset();
}

/// <summary>
/// Obtém um valor que indica se Append, AppendByteStream ou Remove está em processo.
/// </summary>
/// <param name="Param_Out_Valor">Retorna um valor booleano indicando se alguns dos métodos está em processo atualmente.</param>
void CarenMFSourceBuffer::GetUpdating([Out] Boolean% Param_Out_Valor)
{
	//Chama o método para realizar a operação.
	Param_Out_Valor = static_cast<Boolean>(PonteiroTrabalho->GetUpdating());
}

/// <summary>
/// Remove os segmentos de mídia definidos pelo intervalo de tempo especificado do ICarenMFSourceBuffer.
/// </summary>
/// <param name="Param_Inicio">O início do intervalo de tempo.</param>
/// <param name="Param_Fim">O fim do intervalo de tempo.</param>
CarenResult CarenMFSourceBuffer::Remove(double Param_Inicio, double Param_Fim)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Remove(Param_Inicio, Param_Fim);

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

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o carimbo de tempo para o fim da janela de acrescimo.
/// </summary>
/// <param name="Param_Time">O carimbo de data e hora para o fim da janela de acrescimo.</param>
CarenResult CarenMFSourceBuffer::SetAppendWindowEnd(double Param_Time)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAppendWindowEnd(Param_Time);

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

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o carimbo de tempo para o início da janela de acrescimo.
/// </summary>
/// <param name="Param_Time">O carimbo de data e hora para o início da janela de acrescimo.</param>
CarenResult CarenMFSourceBuffer::SetAppendWindowStart(double Param_Time)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetAppendWindowStart(Param_Time);

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

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define a compensação de carimbo de tempo para segmentos de mídia anexados ao ICarenMFSourceBuffer.
/// </summary>
/// <param name="Param_Offset">O valor offset para o timestamp dos fluxos de mídia anexados.</param>
CarenResult CarenMFSourceBuffer::SetTimeStampOffset(double Param_Offset)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTimeStampOffset(Param_Offset);

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

Done:;
	//Retorna o resultado.
	return Resultado;
}