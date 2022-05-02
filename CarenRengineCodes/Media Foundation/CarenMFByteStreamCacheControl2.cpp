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
#include "CarenMFByteStreamCacheControl2.h"

//Destruidor.
CarenMFByteStreamCacheControl2::~CarenMFByteStreamCacheControl2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenMFByteStreamCacheControl2::CarenMFByteStreamCacheControl2()
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
CarenResult CarenMFByteStreamCacheControl2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFByteStreamCacheControl2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFByteStreamCacheControl2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFByteStreamCacheControl2**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFByteStreamCacheControl2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFByteStreamCacheControl2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFByteStreamCacheControl2**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFByteStreamCacheControl2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFByteStreamCacheControl2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFByteStreamCacheControl2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFByteStreamCacheControl2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFByteStreamCacheControl2::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFByteStreamCacheControl2::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFByteStreamCacheControl2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFByteStreamCacheControl2();
}



// Métodos da interface proprietária(ICarenMFByteStreamCacheControl2)


/// <summary>
/// Obtém as faixas de bytes que estão armazenadas no cache atualmente.
/// </summary>
/// <param name="Param_Out_QuantidadeRanges">Recebe o número de intervalos retornados na matriz (Param_Out_Ranges).</param>
/// <param name="Param_Out_Ranges">Recebe uma série de estruturas MF_BYTE_STREAM_CACHE_RANGE. Cada estrutura especifica uma gama de bytes armazenados no cache.</param>
CarenResult CarenMFByteStreamCacheControl2::GetByteRanges(
[Out] UInt32% Param_Out_QuantidadeRanges,
[Out] cli::array<CA_MF_BYTE_STREAM_CACHE_RANGE^>^% Param_Out_Ranges)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DWORD vi_OutQuantidade = 0;
	MF_BYTE_STREAM_CACHE_RANGE* vi_pOutMatrizRanges = Nulo; //Liberada com CoTaskMemFree.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetByteRanges(&vi_OutQuantidade, &vi_pOutMatrizRanges);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a matriz a ser retornada com os dados.
	Param_Out_Ranges = gcnew cli::array<CA_MF_BYTE_STREAM_CACHE_RANGE^>(vi_OutQuantidade);

	//Faz um for para converter e definir na matriz gerenciada.
	for (DWORD i = 0; i < vi_OutQuantidade; i++)
	{
		//Converte e define no index especificado.
		Param_Out_Ranges[i] = Util.ConverterMF_BYTE_STREAM_CACHE_RANGEUnamaged_ToManaged(&vi_pOutMatrizRanges[i]);
	}

	//Define a quantidade de itens da matriz no parametro de saida.
	Param_Out_QuantidadeRanges = static_cast<UInt32>(vi_OutQuantidade);

Done:;
	//Libera a memória utilizada pela estrutura
	if (ObjetoValido(&vi_pOutMatrizRanges))
		CoTaskMemFree(vi_pOutMatrizRanges);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Consulta se a transferência em segundo plano está ativa.
/// A transferência em segundo plano pode ser interrompida porque o limite do cache foi atingido (consulte IMFByteStreamCacheControl2 :: SetCacheLimit) ou porque o método IMFByteStreamCacheControl :: StopBackgroundTransfer foi chamado.
/// </summary>
/// <param name="Param_Out_Ativo">Recebe o valor TRUE se a transferência em segundo plano estiver ativa no momento ou FALSE caso contrário.</param>
CarenResult CarenMFByteStreamCacheControl2::IsBackgroundTransferActive([Out] Boolean% Param_Out_Ativo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	BOOL vi_OutAtivo = FALSE;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->IsBackgroundTransferActive(&vi_OutAtivo);

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
	Param_Out_Ativo = vi_OutAtivo ? true : false;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Defeine o limite do cache.
/// </summary>
/// <param name="Param_MaximoBytes">O número máximo de bytes para armazenar no cache ou (18446744073709551615) para nenhum limite. O valor padrão é sem limite.</param>
CarenResult CarenMFByteStreamCacheControl2::SetCacheLimit(Int64 Param_MaximoBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetCacheLimit(Param_MaximoBytes);

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




// Métodos da interface (ICarenMFByteStreamCacheControl)


/// <summary>
///  Interrompe a transferência de dados em segundo plano para o cache local.
/// </summary>
CarenResult CarenMFByteStreamCacheControl2::StopBackgroundTransfer()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StopBackgroundTransfer();

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