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
#include "CarenD2D1RenderInfo.h"

//Destruidor.
CarenD2D1RenderInfo::~CarenD2D1RenderInfo()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1RenderInfo::CarenD2D1RenderInfo()
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
CarenResult CarenD2D1RenderInfo::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RenderInfo::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1RenderInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1RenderInfo**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RenderInfo::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1RenderInfo*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1RenderInfo**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1RenderInfo::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1RenderInfo::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1RenderInfo::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1RenderInfo::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1RenderInfo::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1RenderInfo::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1RenderInfo::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1RenderInfo::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1RenderInfo();
}



// Métodos da interface proprietária(ICarenD2D1RenderInfo)


/// <summary>
/// Especifica que a saída da transformação na qual as informações de renderização estão encapsuladas é ou não armazenada em cache. 
/// </summary>
/// <param name="Param_IsCached">TRUE se a saída da transformação for armazenada em cache; caso contrário, FALSO.</param>
void CarenD2D1RenderInfo::SetCached(Boolean Param_IsCached)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetCached(Param_IsCached? TRUE: FALSE);
}

/// <summary>
/// Define como uma entrada específica para a transformação deve ser tratada pelo renderizador em termos de amostragem. 
/// </summary>
/// <param name="Param_InputIndex">O índice da entrada que terá a descrição de entrada aplicada.</param>
/// <param name="Param_InputDescription">A descrição da entrada a ser aplicada à transformação.</param>
CarenResult CarenD2D1RenderInfo::SetInputDescription(
UInt32 Param_InputIndex,
CA_D2D1_INPUT_DESCRIPTION^ Param_InputDescription)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INPUT_DESCRIPTION* pInputDesc = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pInputDesc = Util.ConverterD2D1_INPUT_DESCRIPTIONManagedToUnmanaged(Param_InputDescription);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetInputDescription(Param_InputIndex, *pInputDesc);

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
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pInputDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Fornece uma sugestão estimada de custo de execução do sombreador para D2D. 
/// A contagem de instruções pode ser definida de acordo com o número de instruções no sombreador. Essas informações são usadas como uma dica ao renderizar imagens extremamente grandes. Chamar esta API é opcional, 
/// mas pode melhorar o desempenho se você fornecer um número preciso.
/// [NOTA] As instruções que ocorrem em um loop devem ser contadas de acordo com o número de iterações em loop.
/// </summary>
/// <param name="Param_InstructionCount">Uma contagem aproximada de instruções do sombreador associado.</param>
void CarenD2D1RenderInfo::SetInstructionCountHint(UInt32 Param_InstructionCount)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetInstructionCountHint(Param_InstructionCount);
}

/// <summary>
/// Permite que um chamador controle a precisão de saída e a profundidade do canal da transformação em que as informações de renderização são encapsuladas. 
/// Se a precisão de saída da transformação não for especificada, ela será padrão para a precisão especificada no contexto do dispositivo Direct2D. O máximo de 16bpc UNORM e 16bpc FLOAT é 32bpc FLOAT.
/// A profundidade do canal de saída corresponderá ao máximo das profundidades do canal de entrada se a profundidade do canal estiver D2D1_CHANNEL_DEPTH_DEFAULT.
/// Não há profundidade de canal de saída global, isso é sempre deixado para o controle das transformações.
/// </summary>
/// <param name="Param_BufferPrecision">O tipo de buffer que deve ser usado como saída a partir desta transformação.</param>
/// <param name="Param_ChannelDepth">O número de canais que serão usados no buffer de saída.</param>
CarenResult CarenD2D1RenderInfo::SetOutputBuffer(
CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION BuffPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	D2D1_CHANNEL_DEPTH ChannelDep = static_cast<D2D1_CHANNEL_DEPTH>(Param_ChannelDepth);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputBuffer(BuffPrecision, ChannelDep);

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