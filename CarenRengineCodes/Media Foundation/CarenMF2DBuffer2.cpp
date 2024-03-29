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
#include "CarenMF2DBuffer2.h"


//Destruidor.
CarenMF2DBuffer2::~CarenMF2DBuffer2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenMF2DBuffer2::CarenMF2DBuffer2()
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
CarenResult CarenMF2DBuffer2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (!String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//A operação falhou.
		

		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}


	//Retorna o resultado
	return Resultado;}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMF2DBuffer2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMF2DBuffer2*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMF2DBuffer2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<IMF2DBuffer2*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMF2DBuffer2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMF2DBuffer2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMF2DBuffer2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK,true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMF2DBuffer2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenMF2DBuffer2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMF2DBuffer2::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMF2DBuffer2::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMF2DBuffer2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMF2DBuffer2();
}





// Métodos da interface proprietaria (ICarenMF2DBuffer2)


/// <summary>
/// (Lock2DSize) - Fornece o acesso do chamador para a memória no buffer.
/// </summary>
/// <param name="Param_LockBufferFlags">Um membro da enumeração (CA_MF2DBuffer_LockFlags) que especifica se deseja bloquear o buffer para leitura, gravação ou ambos.</param>
/// <param name="Param_Out_BufferPBScanline0">Recebe um ponteiro para o primeiro byte da linha superior de pixels na imagem. A linha superior é definida como a linha superior quando 
/// a imagem é apresentada ao visualizador e pode não ser a primeira linha na memória.</param>
/// <param name="Param_Out_StrideSuperfice">Recebe o passo de superfície, em bytes. A passada pode ser negativa, indicando que a imagem é orientada de baixo para cima na memória.</param>
/// <param name="Param_Out_BufferStart">Recebe um ponteiro para o início do buffer acessível na memória.</param>
/// <param name="Param_Out_LarguraBuffer">Recebe o comprimento do buffer, em bytes.</param>
CarenResult CarenMF2DBuffer2::Lock2DSize(Enumeracoes::CA_MF2DBuffer_LockFlags Param_LockBufferFlags, [Out] ICarenBuffer^% Param_Out_BufferPBScanline0, [Out] Int64% Param_Out_StrideSuperfice, [Out] ICarenBuffer^% Param_Out_BufferStart, [Out] UInt32% Param_Out_LarguraBuffer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método
	PBYTE vi_pOutPBScanLine0 = NULL;
	PBYTE vi_pOutBufferData = NULL;
	LONG vi_OutStrideBuffer = 0;
	DWORD vi_OutLarguraBuffer = 0;
	MF2DBuffer_LockFlags LockFlags = (MF2DBuffer_LockFlags)Param_LockBufferFlags;

	//Chama o método para prender o buffer.
	Hr = PonteiroTrabalho->Lock2DSize(
		LockFlags, 
		&vi_pOutPBScanLine0, 
		&vi_OutStrideBuffer,
		&vi_pOutBufferData, 
		&vi_OutLarguraBuffer);

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
	Param_Out_BufferPBScanline0 = gcnew CarenBuffer();
	Param_Out_BufferStart = gcnew CarenBuffer();

	//Define os buffers em cada interface de saida.
	Param_Out_BufferPBScanline0->CreateBuffer(IntPtr(vi_pOutPBScanLine0), false, 0, 0);
	Param_Out_BufferStart->CreateBuffer(IntPtr(vi_pOutBufferData), false, 0, 0);

	//Define os dados nos parametros de saida
	Param_Out_StrideSuperfice = vi_OutStrideBuffer;
	Param_Out_LarguraBuffer = vi_OutLarguraBuffer;

Done:;
	//Retorna o resultado.
	return Resultado;
}


/// <summary>
/// (Copy2DTo) - Copia o buffer para outro objeto de buffer 2D.
/// </summary>
/// <param name="Param_Interface2DBufferDestino">A interface de destino que vai receber o buffer.</param>
CarenResult CarenMF2DBuffer2::Copy2DTo(ICarenMF2DBuffer2^% Param_Interface2DBufferDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Variavel COM
	ResultadoCOM Hr = E_FAIL;

	//Variaveis que seram utilizadas no método.
	IMF2DBuffer2* vi_pBufferDest = Nulo;

	//Chama o m~etodo para recuperar o ponteiro para o buffer de destino.
	CarenGetPointerFromICarenSafe(Param_Interface2DBufferDestino, vi_pBufferDest);	

	//Chama o método para copiar os dados.
	Hr = PonteiroTrabalho->Copy2DTo(vi_pBufferDest);

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





// Métodos da interface (ICarenMF2DBuffer)


/// <summary>
/// (ContiguousCopyFrom) - Copia dados para esse buffer de um buffer que tem um formato contíguo(Único).
/// </summary>
/// <param name="Param_BufferContiguo">A interface que contém um buffer com os dados contiguou a serem copiados.</param>
/// <param name="Param_LarguraBuffer">A largura do buffer a ser copiado.</param>
CarenResult CarenMF2DBuffer2::ContiguousCopyFrom(ICarenBuffer^ Param_BufferContiguo, UInt32 Param_LarguraBuffer)
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
CarenResult CarenMF2DBuffer2::ContiguousCopyTo(ICarenBuffer^% Param_DestinoBufferContiguou, UInt32 Param_LarguraBufferDestino)
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
CarenResult CarenMF2DBuffer2::GetContiguousLength([Out] UInt32% Param_Out_LarguraBufferContiguou)
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
CarenResult CarenMF2DBuffer2::GetScanline0AndPitch([Out] ICarenBuffer^% Param_Out_ByteBufferPrimeiraLinha, [Out] Int64% Param_Out_Stride)
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
CarenResult CarenMF2DBuffer2::IsContiguousFormat([Out] Boolean% Param_Out_BufferContiguou)
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
CarenResult CarenMF2DBuffer2::Lock2D([Out] ICarenBuffer^% Param_Out_Buffer, [Out] Int64% Param_Out_Stride)
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
CarenResult CarenMF2DBuffer2::Unlock2D()
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