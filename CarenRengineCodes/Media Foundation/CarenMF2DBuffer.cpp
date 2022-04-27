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
#include "CarenMF2DBuffer.h"



//Destruidor.
CarenMF2DBuffer::~CarenMF2DBuffer()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenMF2DBuffer::CarenMF2DBuffer()
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
CarenResult CarenMF2DBuffer::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMF2DBuffer::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMF2DBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMF2DBuffer**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMF2DBuffer::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMF2DBuffer*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMF2DBuffer**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMF2DBuffer::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMF2DBuffer::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMF2DBuffer::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMF2DBuffer::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMF2DBuffer::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMF2DBuffer::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMF2DBuffer::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMF2DBuffer::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMF2DBuffer();
}




// Métodos da interface proprietaria (ICarenMF2DBuffer)


/// <summary>
/// (ContiguousCopyFrom) - Copia dados para esse buffer de um buffer que tem um formato contíguo(Único).
/// </summary>
/// <param name="Param_BufferContiguo">A interface que contém um buffer com os dados contiguou a serem copiados.</param>
/// <param name="Param_LarguraBuffer">A largura do buffer a ser copiado.</param>
CarenResult CarenMF2DBuffer::ContiguousCopyFrom(ICarenBuffer^ Param_BufferContiguo, UInt32 Param_LarguraBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	GenPointer vi_BufferSource = DefaultGenPointer;
	
	//Chama o método para recuperar o ponteiro para o buffer de origem.
	CarenGetPointerFromICarenBufferSafe(Param_BufferContiguo, vi_BufferSource);

	//Chama o método para copiar os dados do buffer para este.
	Hr = PonteiroTrabalho->ContiguousCopyFrom(
		static_cast<PBYTE>(vi_BufferSource.ToPointer()),
		Param_LarguraBuffer);

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
/// (ContiguousCopyTo) - Copia esse buffer no buffer do chamador, convertendo os dados em formato contíguo(Único).
/// </summary>
/// <param name="Param_DestinoBufferContiguou">A interface que vai receber o buffer de dados do objeto atual.</param>
/// <param name="Param_LarguraBufferDestino">O tamanho do buffer de destino. Obtenha esse valor chamando o método (GetContiguousLength).</param>
CarenResult CarenMF2DBuffer::ContiguousCopyTo(ICarenBuffer^% Param_DestinoBufferContiguou, UInt32 Param_LarguraBufferDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis que seram utilizadas no método.
	GenPointer vi_BufferDest = DefaultGenPointer;

	//Chama o método para recuperar o ponteiro para o buffer de destino.
	CarenGetPointerFromICarenBufferSafe(Param_DestinoBufferContiguou, vi_BufferDest);

	//Chama o método que vai copiar os dados para o buffer de destino.
	Hr = PonteiroTrabalho->ContiguousCopyTo(
		static_cast<PBYTE>(vi_BufferDest.ToPointer()),
		Param_LarguraBufferDestino);

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
/// (GetContiguousLength) - Recupera o número de bytes necessários para armazenar os dados do buffer 
/// em formato contíguo.
/// </summary>
/// <param name="Param_Out_LarguraBufferContiguou">Recebe a largura do Buffer Contiguou.</param>
CarenResult CarenMF2DBuffer::GetContiguousLength([Out] UInt32% Param_Out_LarguraBufferContiguou)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	DWORD vi_OutLenghtBuffer = 0;

	//Chama o método para obter a largura contigua do buffer.
	Hr = PonteiroTrabalho->GetContiguousLength(&vi_OutLenghtBuffer);

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

	//Define a largura do buffer no parametro de saida.
	Param_Out_LarguraBufferContiguou = vi_OutLenghtBuffer;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetScanline0AndPitch) - Recupera um ponteiro para a memória de buffer e o Stride da superfície do quadro de vídeo.
/// Antes de chamar esse método, você deve bloquear o buffer chamando (Lock2D). O valor retornado em (Param_Out_Stride) 
/// é válido somente enquanto o buffer permanece bloqueado.
/// </summary>
/// <param name="Param_Out_ByteBufferPrimeiraLinha">Recebe uma Interface de buffer para o primeiro byte da linha superior de pixels na imagem.</param>
/// <param name="Param_Out_Stride">Recebe o stride, em bytes.</param>
CarenResult CarenMF2DBuffer::GetScanline0AndPitch([Out] ICarenBuffer^% Param_Out_ByteBufferPrimeiraLinha, [Out] Int64% Param_Out_Stride)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	PBYTE vi_pOutBufferScanline = NULL;
	LONG vi_OutStrideValue = 0;

	//Chama o método para obter a superfice e o stride.
	Hr = PonteiroTrabalho->GetScanline0AndPitch(&vi_pOutBufferScanline, &vi_OutStrideValue);

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

	//Cria a interface que vai conter o buffer obtido
	Param_Out_ByteBufferPrimeiraLinha = gcnew CarenBuffer();

	//Define o ponteiro de trabalho na interface.
	Param_Out_ByteBufferPrimeiraLinha->CreateBuffer(IntPtr(vi_pOutBufferScanline), false, 0, 0);

	//Define o Stride no parametro de saida.
	Param_Out_Stride = vi_OutStrideValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (IsContiguousFormat) - Consulta se o buffer é contíguo em seu (formato nativo).
/// </summary>
/// <param name="Param_Out_BufferContiguou">Retorna true se o formato nativo deste buffer é: Contiguou.</param>
CarenResult CarenMF2DBuffer::IsContiguousFormat([Out] Boolean% Param_Out_BufferContiguou)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	BOOL vi_OutIsContiguou = FALSE;

	//Chama o método que vai verificar se é um buffer contiguou.
	Hr = PonteiroTrabalho->IsContiguousFormat(&vi_OutIsContiguou);

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

	//Define o resultado no parametro de saida.
	Param_Out_BufferContiguou = vi_OutIsContiguou ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Lock2D) - Fornece o acesso do chamador para a memória no buffer.
/// </summary>
/// <param name="Param_Out_Buffer">Recebe a interface com o buffer para o primeiro byte da linha superior de pixels na imagem. A linha superior é definida como a 
/// linha superior quando a imagem é apresentada ao visualizador e pode não ser a primeira linha na memória.</param>
/// <param name="Param_Out_Stride">Recebe a passada de superfície, em bytes. O passo pode ser negativo, indicando que a 
/// imagem é orientada de baixo para cima na memória.</param>
CarenResult CarenMF2DBuffer::Lock2D([Out] ICarenBuffer^% Param_Out_Buffer, [Out] Int64% Param_Out_Stride)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	PBYTE vi_pOutBufferLocked = NULL;
	LONG vi_OutStrideValue = 0;

	//Chama o método para prender o buffer.
	Hr = PonteiroTrabalho->Lock2D(&vi_pOutBufferLocked, &vi_OutStrideValue);

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

	//Cria a interface que vai conter o buffer obtido
	Param_Out_Buffer = gcnew CarenBuffer();

	//Define o ponteiro de trabalho na interface.
	Param_Out_Buffer->CreateBuffer(IntPtr(vi_pOutBufferLocked), false, 0, 0);

	//Define o Stride no parametro de saida.
	Param_Out_Stride = vi_OutStrideValue;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (Unlock2D) - Desbloqueia um buffer que foi bloqueado anteriormente. 
/// Chame esse método uma vez para cada chamada para o método Lock2D.
/// </summary>
CarenResult CarenMF2DBuffer::Unlock2D()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para liberar o Buffer
	Hr = PonteiroTrabalho->Unlock2D();

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