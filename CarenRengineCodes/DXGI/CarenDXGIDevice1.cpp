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
#include "CarenDXGIDevice1.h"

//Destruidor.
CarenDXGIDevice1::~CarenDXGIDevice1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenDXGIDevice1::CarenDXGIDevice1()
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
CarenResult CarenDXGIDevice1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIDevice1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIDevice1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIDevice1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIDevice1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIDevice1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIDevice1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIDevice1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIDevice1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIDevice1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIDevice1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIDevice1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIDevice1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIDevice1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIDevice1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIDevice1();
}


//
// Métodos da interface proprietária(ICarenDXGIDevice1)
//

/// <summary>
/// (GetMaximumFrameLatency) - Obtém o número de quadros(Frames) que o sistema pode fazer fila para renderização.
/// </summary>
/// <param name="Param_Out_LatenciaMaxima">Esse valor é definido para o número de quadros que podem ser enfileirados para renderização. Esse valor está 
/// inadimplente em 3, mas pode variar de 1 a 16.</param>
CarenResult CarenDXGIDevice1::GetMaximumFrameLatency([Out] UInt32% Param_Out_LatenciaMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT OutFrameLatenciaMaxima = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetMaximumFrameLatency(&OutFrameLatenciaMaxima);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define a latencia maxima do frame no parametro de saida.
	Param_Out_LatenciaMaxima = OutFrameLatenciaMaxima;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetMaximumFrameLatency) - Define o número de quadros que o sistema pode fazer fila para renderização.
/// </summary>
/// <param name="Param_LatenciaMaxima">O número máximo de quadros de buffer traseiro que um motorista pode fazer fila. O valor está inadimplente a 3, mas pode 
/// variar de 1 a 16. Um valor de 0 redefinirá a latência ao padrão. Para dispositivos (per-head), esse valor é especificado por cabeça(Head).</param>
CarenResult CarenDXGIDevice1::SetMaximumFrameLatency(UInt32 Param_LatenciaMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetMaximumFrameLatency(Param_LatenciaMaxima);

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



//
// Métodos da interface ICarenDXGIDevice
//

/// <summary>
/// (CreateSurface)(Não é implementado) - Este método é usado internamente e você não deve chamá-lo diretamente em sua aplicação.
/// </summary>
CarenResult CarenDXGIDevice1::CreateSurface()
{
	return CarenResult(ResultCode::ER_E_NOTIMPL, false);
}

/// <summary>
/// (GetAdapter) - Retorna o adaptador para o dispositivo especificado.
/// </summary>
/// <param name="Param_Out_Adaptador">Retorna um ponteiro para a interface(ICarenDXGIAdapter) do adaptador.</param>
CarenResult CarenDXGIDevice1::GetAdapter([Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIAdapter* pAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetAdapter(&pAdaptador);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser devolvida no parametro de saida.
	Param_Out_Adaptador = gcnew CarenDXGIAdapter();

	//Adiciona o ponteiro na interface
	Param_Out_Adaptador->AdicionarPonteiro(pAdaptador);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGPUThreadPriority) - Retorna a prioridade da Thread GPU.
/// </summary>
/// <param name="Param_Out_Prioridade">recebe um valor que indica a prioridade atual da Thread GPU. O valor será entre -7 e 7, inclusive, onde 0 representa prioridade normal.</param>
CarenResult CarenDXGIDevice1::GetGPUThreadPriority([Out] int% Param_Out_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	int OutPrioridade = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGPUThreadPriority(&OutPrioridade);

	//Verifica se a operação obteve sucesso.
	if (Sucesso(Hr))
	{
		//Deixa o método continuar.
	}
	else if (Hr == E_POINTER)
	{
		//Define o código de erro.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}
	else
	{
		//Define falha
		Resultado.AdicionarCodigo(ResultCode::ER_FAIL, false);

		//Define o código HRESULT.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método.
		goto Done;
	}

	//Define o valor da prioridade no parametro de saida.
	Param_Out_Prioridade = OutPrioridade;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (QueryResourceResidency) - Obtém o status de residência de uma série de recursos.
/// As informações devolvidas pelo conjunto de argumentos (Param_Ref_StatusResidencia) descrevem o status de residência no momento em que o método 
/// (QueryResourceResidency) foi chamado. 
/// [O status de residência mudará constantemente.]
/// Se você ligar para o método (QueryResourceResidency) durante um estado removido do dispositivo, o argumento (Param_Ref_StatusResidencia) devolverá 
/// a bandeira CA_DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY.
/// </summary>
/// <param name="Param_ArrayRecursos">Um array que contém uma série de interfaces(ICarenDXGIResource) a serem obtido o status de residência.</param>
/// <param name="Param_Ref_StatusResidencia">Um Array que vai conter o status de residência(ResidencyStatus) de cada recurso no parametro(Param_ArrayRecursos).</param>
/// <param name="Param_QuantidadeRecursos">A quantidade de elementos no array de recursos.</param>
CarenResult CarenDXGIDevice1::QueryResourceResidency(
	cli::array<ICarenDXGIResource^>^ Param_ArrayRecursos,
	cli::array<CA_DXGI_RESIDENCY>^% Param_Ref_StatusResidencia,
	UInt32 Param_QuantidadeRecursos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown** ppMatrizRecursos = CriarMatrizUnidimensional<IUnknown*>(Param_QuantidadeRecursos);
	DXGI_RESIDENCY* pMatrizResidencia = CriarMatrizUnidimensional<DXGI_RESIDENCY>(Param_QuantidadeRecursos);
	IDXGIResource* pResource = NULL;

	//Obtém os ponteiros de recurso para adicionar na matriz.
	for (UINT i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Obtém o ponteiro para o recurso
		Param_ArrayRecursos[i]->RecuperarPonteiro((LPVOID*)&pResource);

		//Define o ponteiro na matriz.
		ppMatrizRecursos[i] = pResource;

		//NULA
		pResource = NULL;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->QueryResourceResidency(ppMatrizRecursos, pMatrizResidencia, Param_QuantidadeRecursos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Passa os valores de residencia dos recursos para a matriz de referencia.
	for (UINT i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Converte e define o valor da enumeração da residencia na matriz.
		Param_Ref_StatusResidencia[i] = static_cast<CA_DXGI_RESIDENCY>(pMatrizResidencia[i]);
	}

Done:;
	//Libera a memoria para as matrizes.
	DeletarMatrizDePonteirosUnidimensionalSafe(ppMatrizRecursos, Param_QuantidadeRecursos);
	DeletarMatrizUnidimensionalSafe(&pMatrizResidencia);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetGPUThreadPriority) - Define a prioridade da Thread GPU.
/// </summary>
/// <param name="Param_Prioridade">Um valor que especifica a prioridade necessária da Thread da GPU. Esse valor deve ser entre -7 e 7, inclusive, onde 0 representa 
/// prioridade normal.</param>
CarenResult CarenDXGIDevice1::SetGPUThreadPriority(int Param_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGPUThreadPriority(Param_Prioridade);

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



// Métodos da interface ICarenDXGIObject


/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIDevice1::GetParent(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_ObjetoPai)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetParent(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_ObjetoPai
	);
}

/// <summary>
/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGIDevice1::SetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32 Param_TamanhoDados, 
	ICaren^ Param_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_TamanhoDados,
		Param_Dados
	);
}

/// <summary>
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIDevice1::GetPrivateData(
	String^ Param_GuidIdentificao, 
	UInt32% Param_Ref_TamanhoDados, 
	ICaren^ Param_Out_Dados)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::GetPrivateData(PonteiroTrabalho,
		Param_GuidIdentificao,
		Param_Ref_TamanhoDados,
		Param_Out_Dados
	);
}

/// <summary>
/// Define uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGIDevice1::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}