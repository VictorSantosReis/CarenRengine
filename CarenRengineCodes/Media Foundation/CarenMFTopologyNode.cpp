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
#include "CarenMFTopologyNode.h"


//Destruidor.
CarenMFTopologyNode::~CarenMFTopologyNode()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//Cosntrutores
CarenMFTopologyNode::CarenMFTopologyNode()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenMFTopologyNode::CarenMFTopologyNode(CA_MF_TOPOLOGY_TYPE Param_TypeNode)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Variaveis utilizadas.
	Utilidades Util;
	MF_TOPOLOGY_TYPE vi_TypeNode = static_cast<MF_TOPOLOGY_TYPE>(Param_TypeNode);
	IMFTopologyNode* vi_pOutNode = Nulo;

	//Chama o método para criar a interface.
	Hr = MFCreateTopologyNode(vi_TypeNode, &vi_pOutNode);

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutNode;
}



// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenMFTopologyNode::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTopologyNode::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTopologyNode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTopologyNode**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenMFTopologyNode::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IMFTopologyNode*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IMFTopologyNode**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTopologyNode::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenMFTopologyNode::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenMFTopologyNode::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenMFTopologyNode::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenMFTopologyNode::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenMFTopologyNode::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenMFTopologyNode::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenMFTopologyNode();
}





//Métodos da interface proprietaria (ICarenMFTopologyNode)


/// <summary>
/// (CloneFrom) - Copia os dados de outro nó de topologia para este nó.
/// </summary>
/// <param name="Param_NodeClone">O nó que vai ter os dados copiados para esse.</param>
CarenResult CarenMFTopologyNode::CloneFrom(ICarenMFTopologyNode^ Param_NodeClone)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFTopologyNode* vi_pNoClone = Nulo;

	//Recupera o ponteiro para o nó a ser clonado.
	CarenGetPointerFromICarenSafe(Param_NodeClone, vi_pNoClone);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CloneFrom(vi_pNoClone);

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
/// (ConnectOutput) - Conecta um fluxo de saída deste nó para o fluxo de entrada de outro nó.
/// As conexões de nó representam o fluxo de dados de um nó para o próximo. Os fluxos são lógicos e são especificados pelo índice. Se o nó já estiver conectado na saída especificada, o método interrompe a conexão existente.
/// </summary>
/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de saída neste nó.</param>
/// <param name="Param_NoConexao">Ponteiro para a interface ICarenMFTopologyNode do nó ao qual se conectar.</param>
/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de entrada no outro nó.</param>
CarenResult CarenMFTopologyNode::ConnectOutput(UInt32 Param_IndexFluxoSaida, ICarenMFTopologyNode^ Param_NoConexao, UInt32 Param_IndexFluxoEntrada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFTopologyNode* vi_pNoConexao = Nulo;

	//Recupera o ponteiro para o nó de conexao.
	CarenGetPointerFromICarenSafe(Param_NoConexao, vi_pNoConexao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ConnectOutput(Param_IndexFluxoSaida, vi_pNoConexao, Param_IndexFluxoEntrada);

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
/// (DisconnectOutput) - Desconecta um fluxo de saída neste nó.
/// </summary>
/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de saída para se desconectar.</param>
CarenResult CarenMFTopologyNode::DisconnectOutput(UInt32 Param_IndexSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DisconnectOutput(Param_IndexSaida);

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
/// (GetInput) - Recupera o nó que está conectado a um fluxo de entrada especificado neste nó.
/// </summary>
/// <param name="Param_IndexEntrada">Índice baseado em zero de um fluxo de entrada neste nó.</param>
/// <param name="Param_Out_NoConectado">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de entrada especificado. O chamador deve liberar a interface.</param>
/// <param name="Param_Out_IndexFluxoSaida">Recebe o índice do fluxo de saída que está conectado ao fluxo de entrada deste nó.</param>
CarenResult CarenMFTopologyNode::GetInput(UInt32 Param_IndexEntrada, [Out] ICarenMFTopologyNode^% Param_Out_NoConectado, [Out] UInt32% Param_Out_IndexFluxoSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	DWORD vi_OutIndexOutput = 0;
	IMFTopologyNode* vi_pOutUpstreamNode = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInput(Param_IndexEntrada, &vi_pOutUpstreamNode, &vi_OutIndexOutput);

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
	Param_Out_NoConectado = gcnew CarenMFTopologyNode();

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutUpstreamNode, Param_Out_NoConectado, true);

	//Define o Index do fluxo de saida
	Param_Out_IndexFluxoSaida = vi_OutIndexOutput;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputCount) - Recupera o número de fluxos de entrada que existem atualmente neste nó.
/// </summary>
/// <param name="Param_Out_QuantidadeFluxosEntrada">Recebe o número de fluxos de entrada.</param>
CarenResult CarenMFTopologyNode::GetInputCount([Out] UInt32% Param_Out_QuantidadeFluxosEntrada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	DWORD vi_OutInputCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputCount(&vi_OutInputCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a quanitdade de nos de entrada no parametro de saida.
	Param_Out_QuantidadeFluxosEntrada = vi_OutInputCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetInputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de entrada neste nó.
/// </summary>
/// <param name="Param_IndexEntrada">Índice baseado em zero do fluxo de Entrada.</param>
/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para IMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
CarenResult CarenMFTopologyNode::GetInputPrefType(UInt32 Param_IndexEntrada, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputPrefType(Param_IndexEntrada, &vi_pOutMediaType);

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
	Param_Out_TipoMidiaPreferencial = gcnew CarenMFMediaType(false);

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_TipoMidiaPreferencial, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetNodeType) - Recupera o tipo de nó.
/// </summary>
/// <param name="Param_Out_TipoNode">Recebe um valor de enumeração que define o tipo do nó na topologia.</param>
CarenResult CarenMFTopologyNode::GetNodeType([Out] Enumeracoes::CA_MF_TOPOLOGY_TYPE% Param_Out_TipoNode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	MF_TOPOLOGY_TYPE vi_OutNodeType;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetNodeType(&vi_OutNodeType);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o tipo da topologia.
	Param_Out_TipoNode = static_cast<CA_MF_TOPOLOGY_TYPE>(vi_OutNodeType);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetObject) - Obtém o objeto associado a este nó.
/// </summary>
/// <param name="Param_Out_Objeto">Recebe uma interface que está associada a esse nó. O usuário deve criar a interfaces antes de chamar este método.</param>
CarenResult CarenMFTopologyNode::GetObject(ICaren^ Param_Out_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IUnknown* vi_pOutObject = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetObject(&vi_pOutObject);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutObject, Param_Out_Objeto, true);
	
Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutput) - Recupera o nó que está conectado a um fluxo de saída especificado neste nó.
/// </summary>
/// <param name="Param_IndexSaidaFluxo">Índice baseado em zero de um fluxo de saída neste nó.</param>
/// <param name="Param_Out_NodeConexao">Recebe um ponteiro para ICarenMFTopologyNode do nó que está conectado ao fluxo de saída especificado. O chamador deve liberar a interface.</param>
/// <param name="Param_Out_IndexEntradaFluxo">Recebe o índice do fluxo de entrada que está conectado ao fluxo de saída deste nó.</param>
CarenResult CarenMFTopologyNode::GetOutput(UInt32 Param_IndexSaidaFluxo, [Out] ICarenMFTopologyNode^% Param_Out_NodeConexao, [Out] UInt32% Param_Out_IndexEntradaFluxo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFTopologyNode* vi_pOutDownstreamNode = Nulo;
	DWORD vi_OutIndexInputStream = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutput(Param_IndexSaidaFluxo, &vi_pOutDownstreamNode, &vi_OutIndexInputStream);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada
	Param_Out_NodeConexao = gcnew CarenMFTopologyNode();

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutDownstreamNode, Param_Out_NodeConexao, true);

	//Define o index de entrada
	Param_Out_IndexEntradaFluxo = vi_OutIndexInputStream;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputCount) - Recupera o número de fluxos de saída que existem atualmente neste nó.
/// </summary>
/// <param name="Param_Out_QuantidadeFluxosSaida">Recebe o número de fluxos de saída.</param>
CarenResult CarenMFTopologyNode::GetOutputCount([Out] UInt32% Param_Out_QuantidadeFluxosSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	DWORD vi_OutCount = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetOutputCount(&vi_OutCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a quantidade de nos de saida
	Param_Out_QuantidadeFluxosSaida = vi_OutCount;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetOutputPrefType) - Recupera o tipo de mídia preferencial para um fluxo de saída neste nó.
/// </summary>
/// <param name="Param_IndexSaida">Índice baseado em zero do fluxo de Saida.</param>
/// <param name="Param_Out_TipoMidiaPreferencial">Recebe um ponteiro para ICarenMFMediaType do tipo de mídia. O chamador deve liberar a interface.</param>
CarenResult CarenMFTopologyNode::GetOutputPrefType(UInt32 Param_IndexSaida, [Out] ICarenMFMediaType^% Param_Out_TipoMidiaPreferencial)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizadas no método.
	IMFMediaType* vi_pOutMediaType = Nulo;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetInputPrefType(Param_IndexSaida, &vi_pOutMediaType);

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
	Param_Out_TipoMidiaPreferencial = gcnew CarenMFMediaType(false);

	//Define o ponteiro na interface de saida.
	CarenSetPointerToICarenSafe(vi_pOutMediaType, Param_Out_TipoMidiaPreferencial, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetTopoNodeID) - Recupera o identificador do nó.
/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Os identificadores de nó são exclusivos dentro de uma topologia, mas podem ser reutilizados 
/// em várias topologias.
/// </summary>
/// <param name="Param_Out_IdentificadorNode">Recebe o identificador deste nó.</param>
CarenResult CarenMFTopologyNode::GetTopoNodeID([Out] UInt64% Param_Out_IdentificadorNode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	TOPOID vi_OutID = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetTopoNodeID(&vi_OutID);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o id no parametro de saida.
	Param_Out_IdentificadorNode = vi_OutID;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetInputPrefType) - Define o tipo de mídia preferencial para um fluxo de entrada neste nó.
/// </summary>
/// <param name="Param_IndexFluxoEntrada">Índice baseado em zero do fluxo de Entrada.</param>
/// <param name="Param_TipoMidia">Ponteiro para ICarenMFMediaType do tipo de mídia.</param>
CarenResult CarenMFTopologyNode::SetInputPrefType(UInt32 Param_IndexFluxoEntrada, ICarenMFMediaType^ Param_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFMediaType* vi_pMediaType = Nulo;

	//Recupera o ponteiro para o tipo de midia a ser definido.
	CarenGetPointerFromICarenSafe(Param_TipoMidia, vi_pMediaType);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetInputPrefType(Param_IndexFluxoEntrada, vi_pMediaType);

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
/// (SetObject) - Define o objeto associado a este nó.
/// </summary>
/// <param name="Param_Objeto">A interface a ser associada a este nó. Defina como NULO para limpar o objeto definido anteriormente.</param>
CarenResult CarenMFTopologyNode::SetObject(ICaren^ Param_Objeto)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IUnknown* vi_pObject = Nulo;

	//Recupera o ponteiro para o objeto a ser definido.
	CarenGetPointerFromICarenSafe(Param_Objeto, vi_pObject);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetObject(vi_pObject);

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
/// (SetOutputPrefType) - Define o tipo de mídia preferencial para um fluxo de saída neste nó.
/// </summary>
/// <param name="Param_IndexFluxoSaida">Índice baseado em zero do fluxo de Saida.</param>
/// <param name="Param_TipoMidia">A interface ICarenMFMediaType que contém o ponteiro para o tipo de midia..</param>
CarenResult CarenMFTopologyNode::SetOutputPrefType(UInt32 Param_IndexFluxoSaida, ICarenMFMediaType^ Param_TipoMidia)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis utilizada no método.
	IMFMediaType* vi_pMediaType = Nulo;

	//Recupera o ponteiro para o tipo de midia a ser definido.
	CarenGetPointerFromICarenSafe(Param_TipoMidia, vi_pMediaType);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetInputPrefType(Param_IndexFluxoSaida, vi_pMediaType);

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
/// (SetTopoNodeID) - Define o identificador para o nó.
/// Quando um nó é criado pela primeira vez, é atribuído um identificador. Normalmente, não há nenhuma razão para um aplicativo substituir o identificador.
/// </summary>
/// <param name="Param_IdentificadorNode">O novo identificador para este nó.</param>
CarenResult CarenMFTopologyNode::SetTopoNodeID(UInt64 Param_IdentificadorNode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetTopoNodeID(Param_IdentificadorNode);

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





// Métodos da interface (ICarenMFAttributes)


/// <summary>
/// Compara os atributos neste objeto com os atributos em outro objeto.
/// </summary>
/// <param name="Param_InterfaceCompare">A interface que vai ter todos os atributos comparado com a interface atual.</param>
/// <param name="Param_TipoComparação">O tipo de comparação a ser realizada.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação segundo o parametro (Param_TipoComparação).</param>
CarenResult CarenMFTopologyNode::Compare(
		ICarenMFAttributes^ Param_InterfaceCompare, 
		CA_MF_ATTRIBUTES_MATCH_TYPE Param_TipoComparação, 
		[Out] Boolean% Param_Out_Resultado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::Compare(PonteiroTrabalho,
		Param_InterfaceCompare,
		Param_TipoComparação,
		Param_Out_Resultado
	);
}

/// <summary>
/// Consulta se um valor de atributo armazenado é igual ao valor que está armazenado numa CA_PROPVARIANT.
/// CA_PROPVARIANT é um Wrapper da PropVariant não gerenciada.
/// O método pode retornar (False) para comparação nos seguintes casos: Atributo Não Encontrado, O Tipo do (Valor) na (CA_PROPVARIANT) é diferente do (Valor) no Atributo,
/// O (Valor) do (Atributo) não coincide com o (Valor) passado, método falha.
/// </summary>
/// <param name="Param_GuidChave">Define o Guid do atributo a ter seu valor comparado com o valor da PropVariant informada.</param>
/// <param name="Param_Valor">O valor a ser comparado com o Atributo especificado.</param>
/// <param name="Param_Out_Resultado">O resultado da comparação do atributo.</param>
CarenResult CarenMFTopologyNode::CompareItem(
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_Valor, 
		[Out] Boolean% Param_Out_Resultado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::CompareItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor,
		Param_Out_Resultado
	);
}

/// <summary>
/// Copia todos os atributos deste objeto em outro armazenamento de atributo.
/// Este método exclui todos os atributos originalmente armazenados em (Param_Out_InterfaceDestino).
/// Atenção: Quando você chamar CopyAllItems em um IMFSample , que herda esse método, o tempo de exemplo, duração e sinalizadores não são copiados 
/// para o exemplo de destino. Você deve copiar esses valores para a nova amostra manualmente.
/// </summary>
/// <param name="Param_Out_InterfaceDestino">A interface de destino que vai receber os itens dessa interface.</param>
CarenResult CarenMFTopologyNode::CopyAllItems(ICarenMFAttributes^ Param_Out_InterfaceDestino)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::CopyAllItems(PonteiroTrabalho,
		Param_Out_InterfaceDestino
	);
}

/// <summary>
/// Remove todos os pares chave/valor da lista de atributos do objeto.
/// </summary>
CarenResult CarenMFTopologyNode::DeleteAllItems()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::DeleteAllItems(PonteiroTrabalho);
}

/// <summary>
/// Remove um emparelhar chave/valor da lista de atributos do objeto.
/// Se a chave especificada não existir, o método retornar (SS_OK) da mesma forma.
/// </summary>
/// <param name="Param_GuidChave">O Guid da chave a ser deletada.</param>
CarenResult CarenMFTopologyNode::DeleteItem(String^ Param_GuidChave)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::DeleteItem(PonteiroTrabalho,
		Param_GuidChave
	);
}


// GET METHODS


/// <summary>
/// Recupera uma matriz de byte associada a uma chave. Este método aloca a 
/// memória para a matriz.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
CarenResult CarenMFTopologyNode::GetAllocatedBlob(
		String^ Param_GuidChave, 
		[Out] CA_BlobData% Param_Out_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetAllocatedBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Buffer
	);
}

/// <summary>
/// Obtém uma sequência de caracteres largos associada a uma chave. 
/// Este método aloca a memória para a seqüência de caracteres.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_String">Retorna a string com os dados do valor da chave solicitada.</param>
/// <param name="Param_Out_LarguraString">Retorna a largura em bytes da matriz que continha a String.</param>
CarenResult CarenMFTopologyNode::GetAllocatedString(
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_String, 
		[Out] UInt32% Param_Out_LarguraString)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetAllocatedString(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_String,
		Param_Out_LarguraString
	);
}

/// <summary>
/// Recupera uma matriz de byte associada a uma chave. 
/// Esse método copia a matriz em um buffer alocado pelo chamador.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido.</param>
/// <param name="Param_Out_Buffer">O buffer que contém os dados da matriz bytes do valor da chave solicitada.</param>
/// <param name="Param_TamanhoBuffer">Define o tamanho da matriz em bytes do valor da chave a ser obtido. Chame o método (GetBlobSize) para obter o valor para esse parametro.</param>
CarenResult CarenMFTopologyNode::GetBlob(
		String^ Param_GuidChave, 
		UInt32 Param_TamanhoBuffer, 
		[Out] CA_BlobData% Param_Out_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_TamanhoBuffer,
		Param_Out_Buffer
	);
}

/// <summary>
/// Recupera o comprimento de uma matriz de byte associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para chave que contém o Blob a ser obtido. O tipo de atributo deve ser MF_ATTRIBUTE_BLOB.</param>
/// <param name="Param_TamanhoBuffer">Recebe o tamanho da matriz que contem o valor da chave solicitada.</param>
CarenResult CarenMFTopologyNode::GetBlobSize(
	String^ Param_GuidChave, 
	[Out] UInt32% Param_Out_TamanhoBuffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetBlobSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_TamanhoBuffer
	);
}

/// <summary>
/// Recupera o número de atributos que são definidos neste objeto.
/// </summary>
/// <param name="Param_QuantidadeAtributos">Recebe a quantidade de atributos na interface.</param>
CarenResult CarenMFTopologyNode::GetCount([Out] UInt32% Param_QuantidadeAtributos)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetCount(PonteiroTrabalho,
		Param_QuantidadeAtributos
	);
}

/// <summary>
/// Recupera um valor (Double) associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Double) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetDouble(
		String^ Param_GuidChave, 
		[Out] Double% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetDouble(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um valor GUID associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (GUID) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetGUID(
		String^ Param_GuidChave, 
		[Out] String^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetGUID(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o valor desconhecido associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (CA_PROPVARIANT) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetItem(
		String^ Param_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um atributo no índice especificado.
/// </summary>
/// <param name="Param_Out_GuidChave">Recebe o guid associado a chave obtida pelo id.</param>
/// <param name="Param_IdItem">O Id do item a ter o seu valor obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetItemByIndex(
		UInt32 Param_IdItem, 
		[Out] String^% Param_Out_GuidChave, 
		[Out] CA_PROPVARIANT^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItemByIndex(PonteiroTrabalho,
		Param_IdItem,
		Param_Out_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o tipo de dados do valor associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser verificado o tipo do valor.</param>
/// <param name="Param_Out_TipoDado">O tipo do dado contido na chave solicitada.</param>
CarenResult CarenMFTopologyNode::GetItemType(
		String^ Param_GuidChave, 
		[Out] CA_MF_ATTRIBUTE_TYPE% Param_Out_TipoDado)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetItemType(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_TipoDado
	);
}

/// <summary>
/// Recupera uma sequência de caracteres largos associada a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (String) obtido. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Valor">A largura da string a ser recebida. Some +1 a esse valor. Para obter esse valor, chame o método: GetStringLength</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada.</param>
CarenResult CarenMFTopologyNode::GetString(
		String^ Param_GuidChave, 
		UInt32 Param_LagruraString, 
		[Out] String^% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetString(PonteiroTrabalho,
		Param_GuidChave,
		Param_LagruraString,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera o comprimento de um valor de cadeia de caracteres associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ser consultada a largura da String. O tipo de atributo deve ser MF_ATTRIBUTE_STRING.</param>
/// <param name="Param_Out_Largura">Se a chave for encontrada e o valor é um tipo de sequência de caracteres, esse parâmetro recebe o número de caracteres na 
/// sequência de caracteres, não incluindo o caractere nulo de terminação</param>
CarenResult CarenMFTopologyNode::GetStringLength(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetStringLength(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Largura
	);
}

/// <summary>
/// Recupera um valor de UInt32 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt32) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetUINT32(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUINT32(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// Recupera um valor de UInt64 associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UInt64) obtido.</param>
/// <param name="Param_Out_Valor">Recebe o valor referente ao valor da chave solicitada</param>
CarenResult CarenMFTopologyNode::GetUINT64(
		String^ Param_GuidChave, 
		[Out] UInt64% Param_Out_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUINT64(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Valor
	);
}

/// <summary>
/// (MFGetAttributeRatio) - Recupera um valor UINT64 associado a uma chave.
/// Ese método recuperar o Numerador e Denominador de uma chave.
/// Apesar do Numerado e Denominador serem do tipo (UInt32), a chave a ser consultada deve ser: UInt64.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (UINT64) obtido.</param>
/// <param name="Param_Out_Numerador">Recebe o valor referente ao: Numerador</param>
/// <param name="Param_Out_Denominador">Recebe o valor referente ao: Denominador</param>
CarenResult CarenMFTopologyNode::_MFGetAttributeRatio(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Numerador, 
		[Out] UInt32% Param_Out_Denominador)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFGetAttributeRatio(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Numerador,
		Param_Out_Denominador
	);
}

/// <summary>
/// (MFGetAttributeSize) - Recupera um atributo cujo valor é um tamanho, expresso como uma largura e altura.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor obtido. O atribute deve ser do tipo: UInt64</param>
/// <param name="Param_Out_Largura">Recebe a largura em pixels.</param>
/// <param name="Param_Out_Altura">Recebe a altura em pixels.</param>
CarenResult CarenMFTopologyNode::_MFGetAttributeSize(
		String^ Param_GuidChave, 
		[Out] UInt32% Param_Out_Largura, 
		[Out] UInt32% Param_Out_Altura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFGetAttributeSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Out_Largura,
		Param_Out_Altura
	);
}

/// <summary>
/// (GetUnknown) - Recupera um ponteiro de interface associado a uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave a ter o seu valor (Desconhecido) obtido.</param>
/// <param name="Param_GuidInterfaceSolicitada">O GUID para a interface a ser obtida da chave. Este GUID é um (IID).</param>
/// <param name="Param_Out_InterfaceDesconhecida">Recebe a interface com o ponteiro par ao objeto desconhecido. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenMFTopologyNode::GetUnknown(
		String^ Param_GuidChave, 
		String^ Param_GuidInterfaceSolicitada, 
		ICaren^ Param_Out_InterfaceDesconhecida)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::GetUnknown(PonteiroTrabalho,
		Param_GuidChave,
		Param_GuidInterfaceSolicitada,
		Param_Out_InterfaceDesconhecida
	);
}

/// <summary>
/// Bloqueia o armazenamento de atributo para que nenhum outro thread possa acessá-lo.
/// </summary>
CarenResult CarenMFTopologyNode::LockStore()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::LockStore(PonteiroTrabalho);
}


//SET METHODS


/// <summary>
/// (SetBlob) - Associa uma (Matriz de Byte) com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Buffer">Uma interface (ICarenBuffer) que contém os dados a serem associados a chave especificada.</param>
CarenResult CarenMFTopologyNode::SetBlob(
		String^ Param_GuidChave, 
		ICarenBuffer^ Param_Buffer)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetBlob(PonteiroTrabalho,
		Param_GuidChave,
		Param_Buffer
	);
}

/// <summary>
/// Associa um valor duplo com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetDouble(
		String^ Param_GuidChave, 
		Double Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetDouble(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um valor GUID com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetGUID(
		String^ Param_GuidChave, 
		String^ Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetGUID(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Adiciona um valor de atributo com uma chave especificada.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_PropVariantValor">A PropVariant que contém o valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetItem(
		String^ Param_GuidChave, 
		CA_PROPVARIANT^ Param_PropVariantValor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetItem(PonteiroTrabalho,
		Param_GuidChave,
		Param_PropVariantValor
	);
}

/// <summary>
/// Associa uma seqüência de caracteres largos com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetString(
		String^ Param_GuidChave, 
		String^ Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetString(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um valor de UINT32 com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetUINT32(
		String^ Param_GuidChave, 
		UInt32 Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUINT32(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// Associa um UINT64 valor com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_Valor">O valor a ser definido na chave especificada.</param>
CarenResult CarenMFTopologyNode::SetUINT64(
		String^ Param_GuidChave, 
		UInt64 Param_Valor)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUINT64(PonteiroTrabalho,
		Param_GuidChave,
		Param_Valor
	);
}

/// <summary>
/// (MFSetAttributeRatio) - Associa um valor UInt64 com uma chave.
/// Esse método define no valor da chave uma razão(Numerador e Denominador).
/// Alguns atributos especificam uma taxa como um valor UINT64 compactado. Essa função empacota o numerador e denominador em um único UINT64 valor.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Numerador">Define o valor do: Numerador</param>
/// <param name="Param_Denominador">Define o valor do: Denominador</param>
CarenResult CarenMFTopologyNode::_MFSetAttributeRatio(
		String^ Param_GuidChave, 
		UInt32 Param_Numerador, 
		UInt32 Param_Denominador)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFSetAttributeRatio(PonteiroTrabalho,
		Param_GuidChave,
		Param_Numerador,
		Param_Denominador
	);
}

/// <summary>
/// (MFSetAttributeSize) - Define a largura e a altura como um único valor de atributo de 64 bits.
/// Alguns atributos especificam uma largura e uma altura como um valor UINT64 compactado. Essa função empacota os valores de 
/// largura e altura em um único valor de UInt64 .
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor. O tipo do atributo deve ser: UInt64</param>
/// <param name="Param_Largura">A Largura do vídeo em pixels.</param>
/// <param name="Param_Altura">A Altura do vídeo em pixels.</param>
CarenResult CarenMFTopologyNode::_MFSetAttributeSize(
		String^ Param_GuidChave, 
		UInt32 Param_Largura, 
		UInt32 Param_Altura)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::_MFSetAttributeSize(PonteiroTrabalho,
		Param_GuidChave,
		Param_Largura,
		Param_Altura
	);
}

/// <summary>
/// (TESTE) - Associa um IUnknown ponteiro com uma chave.
/// </summary>
/// <param name="Param_GuidChave">O GUID para a chave que vai receber o valor.</param>
/// <param name="Param_InterfaceDesconhecida">A interface desconhecida a ser definida no valor da chave solicitada.</param>
CarenResult CarenMFTopologyNode::SetUnknown(
		String^ Param_GuidChave, 
		ICaren^ Param_InterfaceDesconhecida)
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::SetUnknown(PonteiroTrabalho,
		Param_GuidChave,
		Param_InterfaceDesconhecida
	);
}

/// <summary>
/// (UnlockStore) - Desbloqueia o armazenamento de atributo após uma chamada para o método (BloquearAtributo). 
/// Enquanto o objeto é desbloqueado, Múltiplos threads podem acessar atributos do objeto.
/// </summary>
CarenResult CarenMFTopologyNode::UnlockStore()
{
	//Chama o método na classe de funções compartilhadas da Media Foundation.
	return Shared_MFAttributes::UnlockStore(PonteiroTrabalho);
}