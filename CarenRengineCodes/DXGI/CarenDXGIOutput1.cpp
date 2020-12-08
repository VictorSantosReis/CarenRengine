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
#include "CarenDXGIOutput1.h"

//Destruidor.
CarenDXGIOutput1::~CarenDXGIOutput1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}

//
// Métodos da interface ICaren
//

/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenDXGIOutput1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
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
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
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
	Hr = (reinterpret_cast<IDXGIOutput1*>(PonteiroTrabalho))->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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
	Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

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
CarenResult CarenDXGIOutput1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIOutput1*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenDXGIOutput1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<IDXGIOutput1*>(Param_PonteiroNativo);

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
CarenResult CarenDXGIOutput1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIOutput1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenDXGIOutput1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Ponteiro de trabalho convertido.
	IUnknown* pInterface = NULL;

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte para a interface COM base.
	pInterface = reinterpret_cast<IUnknown*>(PonteiroTrabalho);

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = pInterface->AddRef();

	//Libera a referência adicional
	pInterface->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Nula a conversão
	if (ObjetoValido(pInterface))
	{
		//Zera.
		pInterface = NULL;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIOutput1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIOutput1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIOutput1::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	(reinterpret_cast<IDXGIOutput1*>(PonteiroTrabalho))->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIOutput1::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = (reinterpret_cast<IDXGIOutput1*>(PonteiroTrabalho))->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenDXGIOutput1::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIOutput1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenDXGIOutput1();
}




//
// Métodos da interface proprietária(ICarenDXGIOutput1)
//

/// <summary>
/// (DuplicateOutput) - Cria uma interface de duplicação de desktop a partir da interface ICarenDXGIOutput1 que representa uma saída de 
/// adaptador.
/// </summary>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída está conectada.</param>
/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
CarenResult CarenDXGIOutput1::DuplicateOutput(ICaren^ Param_Dispositivo3D, [Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IUnknown* pDispositivoD3D = NULL;
	IDXGIOutputDuplication* pOutputDuplication = NULL;

	//Recupera o ponteiro para o dispositivo
	Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

	//Verifica se recuperou com sucesso
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Error.. A interface não é valida.

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->DuplicateOutput(pDispositivoD3D, &pOutputDuplication);

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

	//Cria a interface que vai ser retornada pelo parametro
	Param_Out_SaidaDuplicada = gcnew CarenDXGIOutputDuplication();

	//Define o ponteiro de trabalho na interface.
	Param_Out_SaidaDuplicada->AdicionarPonteiro(pOutputDuplication);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (FindClosestMatchingMode1) - Encontra o modo de exibição que mais combina com o modo de exibição solicitado.
/// </summary>
/// <param name="Param_DescCombine">Uma estrutura CA_DXGI_MODE_DESC1 que descreve o modo de exibição para combinar. Os membros da CA_DXGI_MODE_DESC1 
/// podem ser não especificados, o que indica que não há preferência por esse membro. Um valor de 0 para Largura ou Altura indica que o valor
/// não está especificado. Se largura ou altura for 0, ambos devem ser 0. Um numerador e denominador de 0 no RefreshRate indicam que ele não 
/// está especificado. Outros membros do CA_DXGI_MODE_DESC1 possuem valores de enumeração que indicam que o membro não está especificado. 
/// Se o (Param_Dispositivo3D) for NULO, o membro (Formato) em CA_DXGI_MODE_DESC1 não pode ser CA_DXGI_FORMAT_UNKNOWN.</param>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro for NULO, o (FindClosestMatchingMode1) 
/// retorna apenas modos cujo formato corresponde ao do Param_DescCombine; caso contrário, o (FindClosestMatchingMode1) retorna apenas 
/// aos formatos suportados para escaneamento pelo dispositivo.</param>
/// <param name="Param_Out_DescCorrespondente"> Recebe uma estrutura CA_DXGI_MODE_DESC1 que contém uma descrição do modo de exibição que 
/// mais corresponde ao modo de exibição descrito no Param_DescCombine.</param>
CarenResult CarenDXGIOutput1::FindClosestMatchingMode1(
				CA_DXGI_MODE_DESC1^ Param_DescCombine, 
				ICaren^ Param_Dispositivo3D, 
				[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositivoD3D = NULL;
	DXGI_MODE_DESC1 *pDescCombine;
	DXGI_MODE_DESC1 OutDescCorrespondente = { 0 };

	//Obtém um ponteiro para o dispositivo D3D se ele for valido.
	if (ObjetoGerenciadoValido(Param_Dispositivo3D))
	{
		//Obtém um ponteiro para o dispositivo.
		Resultado = Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivoD3D);

		//Verifica se não houve erro
		if (Resultado.StatusCode != ResultCode::SS_OK)
		{
			//O usuário especificou um dispositivo mais o seu ponteiro era invalido.
			//Vai sair do método para notificar.
			
			//Sai do método
			goto Done;
		}
	}

	//Converte a estrutura que será usada para verificar o modo de exibição.
	pDescCombine = Util.ConverterDXGI_MODE_DESC1Managed_ToUnManaged(Param_DescCombine);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindClosestMatchingMode1(pDescCombine, &OutDescCorrespondente, pDispositivoD3D);

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

	//Converte a estrutura nativa retornada pelo método e define no parametro de saida.
	Param_Out_DescCorrespondente = Util.ConverterDXGI_MODE_DESC1UnManaged_ToManaged(&OutDescCorrespondente);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplayModeList1) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
/// </summary>
/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
/// <param name="Param_Flags">Uma combinação de valores CA_DXGI_ENUM_MODES digitados que são combinados usando uma operação ou bitwise. O valor 
/// resultante especifica opções para modos de exibição para incluir. Você deve especificar CA_DXGI_ENUM_MODES_SCALING para expor os modos 
/// de exibição que requerem dimensionamento. Os modos centrados que não requerem escala e correspondem diretamente à saída do display são 
/// enumerados por padrão.</param>
/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
/// <param name="Param_Ref_QuantidadeModos">Recebe o número de modos de exibição que o (GetDisplayModeList1) retorna no bloco de memória
/// para o qual o (Param_Out_MatrizDecModos) aponta. Defina (Param_Out_MatrizDecModos) para NULO para que o (Param_Ref_QuantidadeModos) 
/// retorne o número de modos de exibição que correspondam ao formato e às opções. Caso contrário, o (Param_Ref_QuantidadeModos) retorna o 
/// número de modos de exibição devolvidos no (Param_Out_MatrizDecModos).</param>
/// <param name="Param_Out_MatrizDecModos">Recebe uma lista de modos de exibição.</param>
CarenResult CarenDXGIOutput1::GetDisplayModeList1(
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDecModos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT FlagsEnumMode = static_cast<UINT>(Param_Flags);
	UINT CountModos = static_cast<UINT>(Param_Ref_QuantidadeModos);
	DXGI_MODE_DESC1* pArrayDXGIMode = NULL;

	//Verifica se está recuperando a quantidade de modos
	if (Param_RecuperaQuantidadeModos)
	{
		//Está recuperando a quantidade de modos.
		//O array de modos é NULO.

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->GetDisplayModeList1(FormatoDXGI, FlagsEnumMode, &CountModos, NULL);
	}
	else
	{
		//Cria a matriz que vai conter os dados.
		pArrayDXGIMode = CriarMatrizUnidimensional<DXGI_MODE_DESC1>(CountModos);

		//Chama o método para realizar a operação.
		Hr = PonteiroTrabalho->GetDisplayModeList1(FormatoDXGI, FlagsEnumMode, &CountModos, pArrayDXGIMode);
	}

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

	//Verifica se está recuperando a quantidade de modos e define só os parametros necessários.
	if (Param_RecuperaQuantidadeModos)
	{
		//Está recuperando a quantidade de modos.

		//Define a quantidade de modos no parametro REF do método.
		Param_Ref_QuantidadeModos = static_cast<UInt32>(CountModos);
	}
	else
	{
		//Está recuperando tudo.

		//Cria a matriz que vai conter os dados de cada matriz.
		Param_Out_MatrizDecModos = gcnew cli::array<CA_DXGI_MODE_DESC1^>(CountModos);

		//Faz um for para adicionar cada estrutura na matriz do parametro de saida.
		for (UINT i = 0; i < CountModos; i++)
		{
			//Converte a estrutura nativa para gerenciada e define no indice.
			Param_Out_MatrizDecModos[i] = Util.ConverterDXGI_MODE_DESC1UnManaged_ToManaged(&pArrayDXGIMode[i]);
		}

		//Define a quantidade de modos no parametro REF do método.
		Param_Ref_QuantidadeModos = static_cast<UInt32>(CountModos);
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Chama o método para liberar a memoria para a matriz.
	DeletarMatrizUnidimensionalSafe(&pArrayDXGIMode);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplaySurfaceData1) - Copia a superfície do display(buffer frontal) para um recurso fornecido pelo usuário.
/// </summary>
/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
/// (GetDisplaySurfaceData1) copia a superfície do display. A interface não pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
CarenResult CarenDXGIOutput1::GetDisplaySurfaceData1(ICarenDXGIResource^ Param_SuperficeDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGIResource* pRecurso = NULL;

	//Recupera o ponteiro para o recurso
	Resultado = Param_SuperficeDestino->RecuperarPonteiro((LPVOID*)&pRecurso);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//O ponteiro para o recurso não é valido

		//Sai do método
		goto Done;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDisplaySurfaceData1(pRecurso);

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




//
// Métodos da interface ICarenDXGIOutput
//

/// <summary>
/// (FindClosestMatchingMode) - Encontra o modo de exibição que mais se corresponde ao modo de exibição solicitado.
/// </summary>
/// <param name="Param_ModoDesc">O modo de exibição desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC não podem ser especificados indicando nenhuma preferência por esse membro. Um valor de 0 para largura ou altura indica 
/// que o valor não é especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que não é especificado. Outros membros da DXGI_MODE_DESC têm valores de enumeração indicando 
/// que o membro não é especificado. Se (Param_Dispositivo3D) é NULO, formatonão pode ser DXGI_FORMAT_UNKNOWN.</param>
/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro é NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) serão devolvidos; caso contrário, apenas os formatos que 
/// são suportados para digitalização pelo dispositivo são devolvidos.</param>
CarenResult CarenDXGIOutput1::FindClosestMatchingMode(CA_DXGI_MODE_DESC^ Param_ModoDesc, [Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, ICaren^ Param_Dispositivo3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_MODE_DESC* pDxgiDesc;
	DXGI_MODE_DESC dxgiDescAproxaimado = {};
	IUnknown* pDispositivo3D = NULL; //Pode ser NULO.

	//Converte a estrutura.
	pDxgiDesc = Util.ConverterDXGI_MODE_DESCManaged_ToUnManaged(Param_ModoDesc);

	//Verifica se forneceu um dispositivo.
	if (ObjetoGerenciadoValido(Param_Dispositivo3D))
	{
		//Recupera o ponteiro para o dispositivo.
		Param_Dispositivo3D->RecuperarPonteiro((LPVOID*)&pDispositivo3D);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindClosestMatchingMode(pDxgiDesc, &dxgiDescAproxaimado, pDispositivo3D ? pDispositivo3D : NULL);

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

	//Converte a estrutura do modo aproximado se valido
	Param_Out_ModoMaisAproximado = Util.ConverterDXGI_MODE_DESCUnManaged_ToManaged(&dxgiDescAproxaimado);

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a estrutura.
	DeletarEstruturaSafe(&pDxgiDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDesc) - Obter uma descrição da saída.
/// </summary>
/// <param name="Param_Out_DescSaida">Retorna uma estrutura que contém a descrição da saida.</param>
CarenResult CarenDXGIOutput1::GetDesc([Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_OUTPUT_DESC OutDesc = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDesc(&OutDesc);

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

	//Converte e define no parametro de saida.
	Param_Out_DescSaida = Util.ConverterDXGI_OUTPUT_DESCUnManaged_ToManaged(&OutDesc);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplayModeList) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
/// </summary>
/// <param name="Param_Formato">O formato de cor.</param>
/// <param name="Param_Flags">Opções para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibição que exigem escala. Os modos centrados, que não exigem escala e correspondentes diretamente à 
/// saída da tela, são enumerados por padrão.</param>
/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDecModos). Na saida contém a quantidade de dados de (Param_Out_MatrizDecModos).</param>
/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibição.</param>
CarenResult CarenDXGIOutput1::GetDisplayModeList(
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FORMAT FormatoDXGI = static_cast<DXGI_FORMAT>(Param_Formato);
	UINT Flags = static_cast<UINT>(Param_Flags);
	UINT QuantidadeModos = Param_Ref_QuantidadeModos; //Valor que é usado na entrada e na saida.
	DXGI_MODE_DESC* pArrayModeDesc = NULL;

	//Verifica como vai ser chamado o método
	if (Param_RecuperaQuantidadeModos)
	{
		//Neste caso o array é NULO e se obtém apenas a quantidade de modos.

		//Chama o método para realizar a operação
		Hr = PonteiroTrabalho->GetDisplayModeList(FormatoDXGI, Flags, &QuantidadeModos, NULL);
	}
	else
	{
		//Neste caso o array é valido e se obtém o array e a quantidade de itens no array.

		//Cria a matriz com a quantidade informada pelo usuário.
		pArrayModeDesc = CriarMatrizEstruturas<DXGI_MODE_DESC>(QuantidadeModos);

		//Chama o método para realizar a operação
		Hr = PonteiroTrabalho->GetDisplayModeList(FormatoDXGI, Flags, &QuantidadeModos, pArrayModeDesc);
	}

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

	//Define os valores de saida.
	Param_Ref_QuantidadeModos = QuantidadeModos;

	//Verifica se vai retornar a matriz de modos.
	if (!Param_RecuperaQuantidadeModos)
	{
		//Vai retornar a matriz também.

		//Cria a matriz que vai conter os modos
		Param_Out_MatrizDescModos = gcnew cli::array<CA_DXGI_MODE_DESC^>(QuantidadeModos);

		//Converte os dados da estrutura nativa para a gerenciada
		for (UINT i = 0; i < QuantidadeModos; i++)
		{
			//Converte e define na matriz.
			Param_Out_MatrizDescModos[i] = Util.ConverterDXGI_MODE_DESCUnManaged_ToManaged(&pArrayModeDesc[i]);
		}
	}

	//Define sucesso na operação
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memoria para a matriz se valida
	DeletarMatrizEstruturasSafe(&pArrayModeDesc);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetDisplaySurfaceData) - Obtém uma cópia da superfície de exibição atual.
/// O método só pode ser chamado quando uma saída está no modo de tela cheia. Se o método for bem-sucedido, a DXGI preenche a superfície do destino.
/// </summary>
/// <param name="Param_SuperficeDestino">Um ponteiro para uma superfície de destino que vai receber a superfice.</param>
CarenResult CarenDXGIOutput1::GetDisplaySurfaceData(ICarenDXGISurface^% Param_SuperficeDestino)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pSuperfice = NULL;

	//Recupera o ponteiro para a superfice que ira receber os dados.
	Resultado = Param_SuperficeDestino->RecuperarPonteiro((LPVOID*)&pSuperfice);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou..

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDisplaySurfaceData(pSuperfice);

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
/// (GetFrameStatistics) - Obtém estatísticas sobre quadros recentemente renderizados.
/// </summary>
/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informações.</param>
CarenResult CarenDXGIOutput1::GetFrameStatistics([Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_FRAME_STATISTICS FrameStatistics = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetFrameStatistics(&FrameStatistics);

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

	//Converte e define na estrutura de saida.
	Param_Out_EstatisticasFrame = Util.ConverterDXGI_FRAME_STATISTICSUnManaged_ToManaged(&FrameStatistics);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGammaControl) - Obtém as configurações de controle gama.
/// </summary>
/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que contém as informações do controle gamma.</param>
CarenResult CarenDXGIOutput1::GetGammaControl([Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL ControleGamma = DXGI_GAMMA_CONTROL();

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGammaControl(&ControleGamma);

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

	//Converte e define no parametro de saida.
	Param_Out_ControleGamma = Util.ConverterDXGI_GAMMA_CONTROLUnManaged_ToManaged(&ControleGamma);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (GetGammaControlCapabilities) - Obtém uma descrição das capacidades de controle gama.
/// </summary>
/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que contém as descrições das capcidades do controle Gamma.</param>
CarenResult CarenDXGIOutput1::GetGammaControlCapabilities([Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL_CAPABILITIES CapGammaControl = {};

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGammaControlCapabilities(&CapGammaControl);

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

	//Converte a estrutura e define no parametro de saida
	Param_Out_GammaCaps = Util.ConverterDXGI_GAMMA_CONTROL_CAPABILITIESUnManaged_ToManaged(&CapGammaControl);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (ReleaseOwnership) - Libera a propriedade da saída.
/// </summary>
CarenResult CarenDXGIOutput1::ReleaseOwnership()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->ReleaseOwnership();

	//Define sucesso por default a operação.
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (SetDisplaySurface) - Altera o modo de exibição.
/// </summary>
/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
CarenResult CarenDXGIOutput1::SetDisplaySurface(ICarenDXGISurface^% Param_Superfice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGISurface* pSuperfice = NULL;

	//Recupera o ponteiro para a superfice
	Resultado = Param_Superfice->RecuperarPonteiro((LPVOID*)&pSuperfice);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetDisplaySurface(pSuperfice);

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
/// (SetGammaControl) - Define os controles gama.
/// </summary>
/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
CarenResult CarenDXGIOutput1::SetGammaControl(CA_DXGI_GAMMA_CONTROL^ Param_ControleGama)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL* pGControl;

	//Converte a estrutura.
	pGControl = Util.ConverterDXGI_GAMMA_CONTROLManaged_ToUnManaged(Param_ControleGama);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetGammaControl(pGControl);

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
	//Libera a memoria para o ponteiro
	DeletarEstruturaSafe(&pGControl);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// (TakeOwnership) - Toma posse de uma saída. Quando você terminar com a saída, chame o método ICarenDXGIOutput::ReleaseOwnership().
/// Este método não deve ser chamado diretamente por aplicativos, uma vez que os resultados serão imprevisíveis. É chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transições em tela cheia, e não deve ser usado como 
/// um substituto para métodos de cadeia de swap.
/// </summary>
/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros tópicos ou aplicativos para assumir a propriedade do dispositivo; caso contrário, definido como FALSE.</param>
CarenResult CarenDXGIOutput1::TakeOwnership(ICaren^ Param_DispositivoD3D, Boolean Param_Exclusivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IUnknown* pDispositovo3D = NULL;
	BOOL Exclusivo = Param_Exclusivo ? TRUE : FALSE;

	//Recupera o dispositivo.
	Resultado = Param_DispositivoD3D->RecuperarPonteiro((LPVOID*)&pDispositovo3D);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->TakeOwnership(pDispositovo3D, Exclusivo);

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
/// (WaitForVBlank ) - Pare um Thread até que o próximo espaço em branco vertical ocorra.
/// </summary>
CarenResult CarenDXGIOutput1::WaitForVBlank()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->WaitForVBlank();

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


// Métodos da interface ICarenDXGIObject


/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIOutput1::GetParent(String^ Param_RIIDInterface, ICaren^ Param_Out_ObjetoPai)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID RiidInterface = GUID_NULL;
	LPVOID pInterfaceReturn = NULL;

	//Cria o guid da interface.
	RiidInterface = Util.CreateGuidFromString(Param_RIIDInterface);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetParent(RiidInterface, &pInterfaceReturn);

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

	//Define o ponteiro de trabalho na interface de saida.
	Param_Out_ObjetoPai->AdicionarPonteiro(pInterfaceReturn);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
/// <param name="Param_Dados">Ponteiro para os dados.</param>
CarenResult CarenDXGIOutput1::SetPrivateData(String^ Param_GuidIdentificao, UInt32 Param_TamanhoDados, ICaren^ Param_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;

	//Cria o guid
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Recupera o ponteiro para os dados.
	Resultado = Param_Dados->RecuperarPonteiro(&pDados);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou. O ponteiro não era valido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateData(GuidIndent, Param_TamanhoDados, pDados);

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
/// Obtém um ponteiro para os dados do objeto.
/// </summary>
/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e não pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador é responsável por liberar a 
/// referência para a interface. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIOutput1::GetPrivateData(String^ Param_GuidIdentificao, UInt32% Param_Ref_TamanhoDados, ICaren^ Param_Out_Dados)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidIndent = GUID_NULL;
	LPVOID pDados = NULL;
	UINT SizeDados = NULL;

	//Cria o guid a parti da string.
	GuidIndent = Util.CreateGuidFromString(Param_GuidIdentificao);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetPrivateData(GuidIndent, &SizeDados, &pDados);

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

	//Define o ponteiro para os dados.
	Param_Out_Dados->AdicionarPonteiro(pDados);

	//Adiciona o tamanho dos dados
	Param_Ref_TamanhoDados = SizeDados;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define uma interface nos dados privados do objeto.
/// </summary>
/// <param name="Param_GuidInterface">Guid de identificação da interface.</param>
/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
CarenResult CarenDXGIOutput1::SetPrivateDataInterface(String^ Param_GuidInterface, ICaren^ Param_Interface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID GuidInterface = GUID_NULL;
	IUnknown* pInterface = NULL;

	//Cria o guid
	GuidInterface = Util.CreateGuidFromString(Param_GuidInterface);

	//Recupera a interface a ser definida.
	Resultado = Param_Interface->RecuperarPonteiro((LPVOID*)&pInterface);

	//Verifica se não houve erro
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Falhou.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPrivateDataInterface(GuidInterface, pInterface);

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