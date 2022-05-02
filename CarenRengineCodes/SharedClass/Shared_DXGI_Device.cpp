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
#include "Shared_DXGI.h"


//MÉTODOS DA CLASSE COMPARTILHADA (Shared_DXGIDevice)

//
// Métodos da interface proprietária(ICarenDXGIDevice4)
//

/// <summary>
/// (OfferResources1) - Permite que o sistema operacional liberte a memória de vídeo dos recursos, incluindo tanto descartar o conteúdo quanto descomprometer a memória.
/// </summary>
/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
/// <param name="Param_Flags">Especifica o DXGI_OFFER_RESOURCE_FLAGS.</param>
CarenResult Shared_DXGIDevice::OfferResources1(
	IDXGIDevice4* Param_MyPointerWork,
	UInt32 Param_QuantidadeRecursos,
	cli::array<ICarenDXGIResource^>^ Param_Recursos,
	CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade,
	CA_DXGI_OFFER_RESOURCE_FLAGS Param_Flags)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIResource** ppMatrizRecursos = CriarMatrizUnidimensional<IDXGIResource*>(Param_QuantidadeRecursos);
	DXGI_OFFER_RESOURCE_PRIORITY Prioridade = static_cast<DXGI_OFFER_RESOURCE_PRIORITY>(Param_Prioridade);
	DXGI_OFFER_RESOURCE_FLAGS Flags = static_cast<DXGI_OFFER_RESOURCE_FLAGS>(Param_Flags);
	PVOID pPonteiroRecurso = NULL;

	//Abri um for para obter os ponteiros e definir na matriz de ponteiros nativo.
	for (UINT32 i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Obtém o ponteiro para o id especificado
		Param_Recursos[i]->RecuperarPonteiro(&pPonteiroRecurso);

		//Define o ponteiro nativo na matriz.
		ppMatrizRecursos[i] = (IDXGIResource*)pPonteiroRecurso;

		//Nula
		pPonteiroRecurso = NULL;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->OfferResources1(Param_QuantidadeRecursos, ppMatrizRecursos, Prioridade, Flags);

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
	//Libera a memoria da matriz.
	DeletarMatrizDePonteirosUnidimensionalSafe(ppMatrizRecursos, Param_QuantidadeRecursos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice4::OfferResources.
/// </summary>
/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Resultado) conjuntos de argumentos.</param>
/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
/// <param name="Param_Ref_Resultado">Uma matriz que recebe valores da enumeração CA_DXGI_RECLAIM_RESOURCE_RESULTS. Cada valor na matriz corresponde a um recurso 
/// no mesmo índice que o parâmetro (Param_Recursos) especifica. O chamador pode passar em NULO, se o chamador pretende preencher os recursos com novos conteúdos, 
/// independentemente de o conteúdo antigo ter sido descartado.</param>
CarenResult Shared_DXGIDevice::ReclaimResources1(
	IDXGIDevice4* Param_MyPointerWork,
	Int32 Param_QuantidadeRecursos,
	cli::array<ICarenDXGIResource^>^ Param_Recursos,
	cli::array<CA_DXGI_RECLAIM_RESOURCE_RESULTS>^% Param_Ref_Resultado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIResource** ppMatrizRecursos = CriarMatrizUnidimensional<IDXGIResource*>(Param_QuantidadeRecursos);
	DXGI_RECLAIM_RESOURCE_RESULTS* pMatrizResultRecurso = CriarMatrizUnidimensional<DXGI_RECLAIM_RESOURCE_RESULTS>(Param_QuantidadeRecursos);
	PVOID pPonteiroRecurso = NULL;

	//Abri um for para obter os ponteiros e definir na matriz de ponteiros nativo.
	for (int i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Obtém o ponteiro para o id especificado
		Param_Recursos[i]->RecuperarPonteiro(&pPonteiroRecurso);

		//Define o ponteiro nativo na matriz.
		ppMatrizRecursos[i] = (IDXGIResource*)pPonteiroRecurso;

		//Nula
		pPonteiroRecurso = NULL;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->ReclaimResources1(Param_QuantidadeRecursos, ppMatrizRecursos, pMatrizResultRecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os resultados no array criado pelo usuário para indicar se o recurso foi recuperado.
	for (int i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Converte e define no array criado pelo usuário.
		Param_Ref_Resultado[i] = static_cast<CA_DXGI_RECLAIM_RESOURCE_RESULTS>(pMatrizResultRecurso[i]);
	}

Done:;
	//Libera a memoria para as matrizes.
	DeletarMatrizDePonteirosUnidimensionalSafe(ppMatrizRecursos, Param_QuantidadeRecursos);
	DeletarMatrizUnidimensionalSafe(&pMatrizResultRecurso);

	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIDevice3
//

/// <summary>
/// (Trim) - Apara a memória gráfica alocada pelo dispositivo DXGI ICarenDXGIDevice3 em nome do aplicativo.
/// Para aplicativos que renderizam com o DirectX, os drivers gráficos alocam periodicamente buffers de memória interna, a fim de acelerar as solicitações de 
/// renderização subsequentes. Essas alocações de memória contam com o uso de memória do aplicativo para PLM e, em geral, levam ao aumento do uso da memória pelo 
/// sistema geral.
/// A partir do Windows 8.1, os aplicativos que renderizam com Direct2D e/ou Direct3D (incluindo interop CoreWindow e XAML) devem ligar para trim em resposta ao 
/// (PLM suspend callback.). O tempo de execução Direct3D e o driver gráfico descartarão buffers de memória interna alocados para o aplicativo, reduzindo sua pegada 
/// de memória.
/// Semelhante ao ICarenD3D11DeviceContext::Flush, os aplicativos devem ligar para ICarenD3D11DeviceContext::ClearState antes de ligar para (Trim). ClearState limpa as 
/// ligações de gasodutos Direct3D, garantindo que o Direct3D não tenha referências aos objetos Direct3D que você está tentando liberar.
/// </summary>
CarenResult Shared_DXGIDevice::Trim(IDXGIDevice3* Param_MyPointerWork)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Chama o método para realizar a operação.
	Param_MyPointerWork->Trim();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIDevice2
//

/// <summary>
/// (EnqueueSetEvent) - Libera quaisquer comandos de renderização pendentes e define o objeto de evento especificado para o estado sinalizado depois de todos os 
/// comandos de renderização previamente enviados completos.
/// </summary>
/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento. Todos os tipos de objetos de evento (manual-reset, auto-reset e assim por diante) são suportados. 
/// A Handle deve ter a bandeira de direito de acesso (EVENT_MODIFY_STATE).</param>
CarenResult Shared_DXGIDevice::EnqueueSetEvent(IDXGIDevice2* Param_MyPointerWork, ICarenEvent^ Param_HandleEvento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	HANDLE pHandEvento = NULL;

	//Recupera o ponteiro para a handle.
	Resultado = Param_HandleEvento->RecuperarEvento(&pHandEvento);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->EnqueueSetEvent(pHandEvento);

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
/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos descartando seu conteúdo.
/// </summary>
/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
CarenResult Shared_DXGIDevice::OfferResources(
	IDXGIDevice2* Param_MyPointerWork,
	UInt32 Param_QuantidadeRecursos,
	cli::array<ICarenDXGIResource^>^ Param_Recursos,
	CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIResource** ppMatrizRecursos = CriarMatrizUnidimensional<IDXGIResource*>(Param_QuantidadeRecursos);
	DXGI_OFFER_RESOURCE_PRIORITY Prioridade = static_cast<DXGI_OFFER_RESOURCE_PRIORITY>(Param_Prioridade);
	PVOID pPonteiroRecurso = NULL;

	//Abri um for para obter os ponteiros e definir na matriz de ponteiros nativo.
	for (UINT32 i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Obtém o ponteiro para o id especificado
		Param_Recursos[i]->RecuperarPonteiro(&pPonteiroRecurso);

		//Define o ponteiro nativo na matriz.
		ppMatrizRecursos[i] = (IDXGIResource*)pPonteiroRecurso;

		//Nula
		pPonteiroRecurso = NULL;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->OfferResources(Param_QuantidadeRecursos, ppMatrizRecursos, Prioridade);

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
	//Libera a memoria para a matriz.
	DeletarMatrizDePonteirosUnidimensionalSafe(ppMatrizRecursos, Param_QuantidadeRecursos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice2::OfferResources.
/// </summary>
/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Descartado) conjuntos de argumentos.</param>
/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
/// <param name="Param_Ref_Descartado">Uma matriz que recebe valores booleanos. Cada valor na matriz corresponde a um recurso no mesmo índice que o parâmetro 
/// (Param_Recursos) especifica. O tempo de execução define cada valor booleano para TRUE se o conteúdo do recurso correspondente foi descartado e agora estiver 
/// indefinido, ou para FALSE se o conteúdo antigo do recurso correspondente ainda estiver intacto. O chamador pode passar NULO, se o chamador pretende preencher 
/// os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
CarenResult Shared_DXGIDevice::ReclaimResources(
	IDXGIDevice2* Param_MyPointerWork,
	Int32 Param_QuantidadeRecursos,
	cli::array<ICarenDXGIResource^>^ Param_Recursos,
	cli::array<bool>^% Param_Ref_Descartado)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIResource** ppMatrizRecursos = CriarMatrizUnidimensional<IDXGIResource*>(Param_QuantidadeRecursos);
	BOOL* pMatrizResultRecurso = CriarMatrizUnidimensional<BOOL>(Param_QuantidadeRecursos);
	PVOID pPonteiroRecurso = NULL;

	//Abri um for para obter os ponteiros e definir na matriz de ponteiros nativo.
	for (int i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Obtém o ponteiro para o id especificado
		Param_Recursos[i]->RecuperarPonteiro(&pPonteiroRecurso);

		//Define o ponteiro nativo na matriz.
		ppMatrizRecursos[i] = (IDXGIResource*)pPonteiroRecurso;

		//Nula
		pPonteiroRecurso = NULL;
	}

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->ReclaimResources(Param_QuantidadeRecursos, ppMatrizRecursos, pMatrizResultRecurso);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os resultados booleanos no array criado pelo usuário para indicar se o recurso foi recuperado.
	for (int i = 0; i < Param_QuantidadeRecursos; i++)
	{
		//Converte e define no array criado pelo usuário.
		Param_Ref_Descartado[i] = static_cast<bool>(pMatrizResultRecurso[i]);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para as matrizes.
	DeletarMatrizDePonteirosUnidimensionalSafe(ppMatrizRecursos, Param_QuantidadeRecursos);
	DeletarMatrizUnidimensionalSafe(&pMatrizResultRecurso);

	//Retorna o resultado.
	return Resultado;
}



//
// Métodos da interface ICarenDXGIDevice1
//

/// <summary>
/// (GetMaximumFrameLatency) - Obtém o número de quadros(Frames) que o sistema pode fazer fila para renderização.
/// </summary>
/// <param name="Param_Out_LatenciaMaxima">Esse valor é definido para o número de quadros que podem ser enfileirados para renderização. Esse valor está 
/// inadimplente em 3, mas pode variar de 1 a 16.</param>
CarenResult Shared_DXGIDevice::GetMaximumFrameLatency(IDXGIDevice1* Param_MyPointerWork, [Out] UInt32% Param_Out_LatenciaMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT OutFrameLatenciaMaxima = 0;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetMaximumFrameLatency(&OutFrameLatenciaMaxima);

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
CarenResult Shared_DXGIDevice::SetMaximumFrameLatency(IDXGIDevice1* Param_MyPointerWork, UInt32 Param_LatenciaMaxima)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetMaximumFrameLatency(Param_LatenciaMaxima);

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
CarenResult Shared_DXGIDevice::CreateSurface()
{
	return CarenResult(ResultCode::ER_E_NOTIMPL, false);
}

/// <summary>
/// (GetAdapter) - Retorna o adaptador para o dispositivo especificado.
/// </summary>
/// <param name="Param_Out_Adaptador">Retorna um ponteiro para a interface(ICarenDXGIAdapter) do adaptador.</param>
CarenResult Shared_DXGIDevice::GetAdapter(IDXGIDevice* Param_MyPointerWork, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIAdapter* pAdaptador = NULL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetAdapter(&pAdaptador);

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
CarenResult Shared_DXGIDevice::GetGPUThreadPriority(IDXGIDevice* Param_MyPointerWork, [Out] int% Param_Out_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	int OutPrioridade = 0;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->GetGPUThreadPriority(&OutPrioridade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
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
CarenResult Shared_DXGIDevice::QueryResourceResidency(
	IDXGIDevice* Param_MyPointerWork,
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
	Hr = Param_MyPointerWork->QueryResourceResidency(ppMatrizRecursos, pMatrizResidencia, Param_QuantidadeRecursos);

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
CarenResult Shared_DXGIDevice::SetGPUThreadPriority(IDXGIDevice* Param_MyPointerWork, int Param_Prioridade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = Param_MyPointerWork->SetGPUThreadPriority(Param_Prioridade);

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