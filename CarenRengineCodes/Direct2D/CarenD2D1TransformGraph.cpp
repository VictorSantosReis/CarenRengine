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
#include "CarenD2D1TransformGraph.h"

//Destruidor.
CarenD2D1TransformGraph::~CarenD2D1TransformGraph()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1TransformGraph::CarenD2D1TransformGraph()
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
CarenResult CarenD2D1TransformGraph::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1TransformGraph::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1TransformGraph*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1TransformGraph**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1TransformGraph::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1TransformGraph*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1TransformGraph**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1TransformGraph::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1TransformGraph::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1TransformGraph::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1TransformGraph::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1TransformGraph::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1TransformGraph::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1TransformGraph::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1TransformGraph::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1TransformGraph();
}



// Métodos da interface proprietária(ICarenD2D1TransformGraph)


/// <summary>
/// Adiciona o nó fornecido ao gráfico de transformação.
/// Um nó deve ser adicionado ao gráfico de transformação antes que ele possa ser interligado de qualquer forma.
/// Um gráfico de transformação não pode ser adicionado diretamente a outro gráfico de transformação. Somente interfaces derivadas do ICarenD2D1TransformNode podem 
/// ser adicionadas ao gráfico de transformação.
/// </summary>
/// <param name="Param_Node">O nó que será adicionado ao gráfico de transformação.</param>
CarenResult CarenD2D1TransformGraph::AddNode(ICarenD2D1TransformNode^ Param_Node)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pTranformNode = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Node, &pTranformNode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddNode(pTranformNode);

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
/// Limpa os nós de transformação e todas as conexões do gráfico de transformação. 
/// </summary>
void CarenD2D1TransformGraph::Clear()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->Clear();
}

/// <summary>
/// Conecta dois nós dentro do gráfico de transformação. Ambos os nós já devem existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
/// </summary>
/// <param name="Param_FromNode">O nó a partir do qual a conexão será feita.</param>
/// <param name="Param_ToNode">O nó para o qual a conexão será feita.</param>
/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
CarenResult CarenD2D1TransformGraph::ConnectNode(
ICarenD2D1TransformNode^ Param_FromNode,
ICarenD2D1TransformNode^ Param_ToNode,
UInt32 Param_ToNodeInputIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pFromNode = NULL;
	ID2D1TransformNode* pToNode = NULL;

	//Recupera o ponteiro para a interface do nó de origem
	Resultado = RecuperarPonteiroCaren(Param_FromNode, &pFromNode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do nó de destino
	Resultado = RecuperarPonteiroCaren(Param_ToNode, &pToNode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ConnectNode(pFromNode, pToNode, Param_ToNodeInputIndex);

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
/// Conecta um nó de transformação dentro do gráfico à entrada de efeito correspondente do efeito encapsulamento. 
/// </summary>
/// <param name="Param_ToEffectInputIndex">A entrada de efeito à qual o nó de transformação será vinculado.</param>
/// <param name="Param_Node">O nó para o qual a conexão será feita.</param>
/// <param name="Param_ToNodeInputIndex">A entrada do nó que será conectada.</param>
CarenResult CarenD2D1TransformGraph::ConnectToEffectInput(
UInt32 Param_ToEffectInputIndex,
ICarenD2D1TransformNode^ Param_Node,
UInt32 Param_ToNodeInputIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pTranformNode = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Node, &pTranformNode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ConnectToEffectInput(Param_ToEffectInputIndex, pTranformNode, Param_ToNodeInputIndex);

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
/// Retorna o número de entradas ao gráfico de transformação. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este gráfico de transformação.</param>
void CarenD2D1TransformGraph::GetInputCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetInputCount();
}

/// <summary>
/// Remove o nó fornecido do gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
/// Quaisquer conexões com este nó serão removidas quando o nó for removido. Depois que o nó é removido, ele não pode ser usado pela interface até que tenha sido 
/// adicionado ao gráfico por AddNode.
/// </summary>
/// <param name="Param_Node">O nó que será removido do gráfico de transformação.</param>
CarenResult CarenD2D1TransformGraph::RemoveNode(ICarenD2D1TransformNode^ Param_Node)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pNodeRemove = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Node, &pNodeRemove);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveNode(pNodeRemove);

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
/// Define o nó de saída para o gráfico de transformação. O nó já deve existir no gráfico; caso contrário, a chamada falha com D2DERR_NOT_FOUND.
/// </summary>
/// <param name="Param_Node">O nó que será considerado a saída do nó de transformação.</param>
CarenResult CarenD2D1TransformGraph::SetOutputNode(ICarenD2D1TransformNode^ Param_Node)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pNodeOutput = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Node, &pNodeOutput);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputNode(pNodeOutput);

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
/// Usa a entrada especificada como saída de efeito. 
/// </summary>
/// <param name="Param_EffectInputIndex">O índice da entrada para o efeito.</param>
CarenResult CarenD2D1TransformGraph::SetPassthroughGraph(UInt32 Param_EffectInputIndex)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPassthroughGraph(Param_EffectInputIndex);

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
/// Define um único nó de transformação como sendo equivalente a todo o gráfico. 
/// Isso equivale a chamar ICarenD2D1TransformGraph::Clear, adicionar um único nó, conectar todas as entradas de nó às entradas de efeito em ordem e definir a 
/// transformação não como saída de gráfico.
/// </summary>
/// <param name="Param_Node">O nó a ser definido.</param>
CarenResult CarenD2D1TransformGraph::SetSingleTransformNode(ICarenD2D1TransformNode^ Param_Node)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1TransformNode* pTranformNode = NULL;

	//Recupera o ponteiro para a interface
	Resultado = RecuperarPonteiroCaren(Param_Node, &pTranformNode);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSingleTransformNode(pTranformNode);

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