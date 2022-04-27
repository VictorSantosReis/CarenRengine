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
#include "CarenSequentialStream.h"

//Destruidor.
CarenSequentialStream::~CarenSequentialStream()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenSequentialStream::CarenSequentialStream()
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
CarenResult CarenSequentialStream::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenSequentialStream::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ISequentialStream*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ISequentialStream**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenSequentialStream::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ISequentialStream*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ISequentialStream**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenSequentialStream::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenSequentialStream::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenSequentialStream::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenSequentialStream::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenSequentialStream::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenSequentialStream::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenSequentialStream::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenSequentialStream::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenSequentialStream();
}



// Métodos da interface proprietária(ICarenSequentialStream)


/// <summary>
/// Lê um número especificado de bytes do objeto de fluxo para a memória, começando pelo ponteiro de busca atual.
/// Este método lê bytes deste objeto de fluxo para a memória. O objeto de fluxo deve ser aberto no modo STGM_READ. Este método ajusta o ponteiro de busca pelo número real de bytes lidos.
/// </summary>
/// <param name="Param_Out_BufferDest">Uma interface ICarenBuffer que contém o ponteiro de destino dos dados a serem lidos. O usuário é responsável por criar esse buffer.</param>
/// <param name="Param_CountRead">O número de bytes de dados para ler a partir do objeto de fluxo.</param>
/// <param name="Param_Ref_TotalReadBytes">Na saída retorna o valor que representa a quantidade de bytes realmente lidos aparti do fluxo.
/// O número real de bytes lidos pode ser menor do que o número de bytes solicitados se ocorrer um erro ou se o final do fluxo for atingido durante a operação de leitura.</param>
/// <returns></returns>
CarenResult CarenSequentialStream::Read(ICarenBuffer^ Param_Out_BufferDest, UInt64 Param_CountRead, UInt64% Param_Ref_TotalReadBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pOutBufferDest = DefaultGenPointer;
	ULONG vi_OutCountReaded = 0;

	//Chama o método para recuperar o buffer de destino.
	Resultado = Param_Out_BufferDest->GetInternalPointer(vi_pOutBufferDest);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		Sair; //Pula para o fim do método.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Read(
		Util.ConverterIntPtrTo<void*>(vi_pOutBufferDest),  //Pointer Buffer.
		static_cast<ULONG>(Param_CountRead),  //Count Read
		&vi_OutCountReaded); //Total Readed.

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

	//Define a quantidade total de bytes lidos no parametro de saida.
	Param_Ref_TotalReadBytes = static_cast<UInt64>(vi_OutCountReaded);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Grava um número especificado de bytes no objeto de fluxo começando no ponteiro de busca atual.
/// Write grava os dados especificados em um objeto de fluxo. O ponteiro de busca é ajustado para o número de bytes realmente escritos. O número de bytes realmente escritos é devolvido 
/// no parâmetro (Param_Ref_TotalWrittenBytes). Se a contagem de bytes é zero bytes, a operação de gravação não tem efeito.
/// </summary>
/// <param name="Param_BufferWrite">Uma interface ICarenBuffer que contém um ponteiro para os dados a serem escritos no buffer atual.</param>
/// <param name="Param_CountWrite">O número de bytes de dados para tentar escrever no fluxo. Esse valor pode ser zero.</param>
/// <param name="Param_Ref_TotalWrittenBytes">Na saída retorna o valor que representa a quantiade de bytes realmente escritas no fluxo. O parâmetro pode retornar um valor mesmo se ocorrer um erro.</param>
/// <returns></returns>
CarenResult CarenSequentialStream::Write(ICarenBuffer^ Param_BufferWrite, UInt64 Param_CountWrite, UInt64% Param_Ref_TotalWrittenBytes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GenPointer vi_pBufferSource = DefaultGenPointer;
	ULONG vi_OutCountWritten = 0;

	//Chama o método para recuperar o buffer de origem.
	Resultado = Param_BufferWrite->GetInternalPointer(vi_pBufferSource);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
		Sair; //Pula para o fim do método.

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Write(
		const_cast<void*>(Util.ConverterIntPtrTo<void*>(vi_pBufferSource)),
		static_cast<ULONG>(Param_CountWrite),
		&vi_OutCountWritten
	);

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

	//Define a quantidade total de dados escritos no fluxo no parametro de saida.
	Param_Ref_TotalWrittenBytes = static_cast<UInt64>(vi_OutCountWritten);

Done:;
	//Retorna o resultado.
	return Resultado;
}