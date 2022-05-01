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
#include "CarenDXGIOutput.h"


//Destruidor.
CarenDXGIOutput::~CarenDXGIOutput()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGIOutput::CarenDXGIOutput()
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
CarenResult CarenDXGIOutput::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIOutput::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIOutput*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIOutput**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIOutput::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIOutput*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIOutput**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIOutput::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIOutput::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIOutput::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIOutput::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIOutput::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIOutput::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIOutput::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIOutput::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIOutput();
}



//
// Métodos da interface proprietária ICarenDXGIOutput
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
CarenResult CarenDXGIOutput::FindClosestMatchingMode(CA_DXGI_MODE_DESC^ Param_ModoDesc, [Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, ICaren^ Param_Dispositivo3D)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_MODE_DESC *pDxgiDesc;
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
	Hr = PonteiroTrabalho->FindClosestMatchingMode(pDxgiDesc, &dxgiDescAproxaimado, pDispositivo3D? pDispositivo3D: NULL);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

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
CarenResult CarenDXGIOutput::GetDesc([Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetDesc(PonteiroTrabalho,
		Param_Out_DescSaida
	);
}

/// <summary>
/// (GetDisplayModeList) - Obtém os modos de exibição que correspondem ao formato solicitado e outras opções de entrada.
/// </summary>
/// <param name="Param_Formato">O formato de cor.</param>
/// <param name="Param_Flags">Opções para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibição que exigem escala. Os modos centrados, que não exigem escala e correspondentes diretamente à 
/// saída da tela, são enumerados por padrão.</param>
/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDescModos). Na saida contém a quantidade de dados de (Param_Out_MatrizDescModos).</param>
/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o número de modos de exibição. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibição.</param>
CarenResult CarenDXGIOutput::GetDisplayModeList(
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
CarenResult CarenDXGIOutput::GetDisplaySurfaceData(ICarenDXGISurface^% Param_SuperficeDestino)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetDisplaySurfaceData(PonteiroTrabalho,
		Param_SuperficeDestino
	);
}

/// <summary>
/// (GetFrameStatistics) - Obtém estatísticas sobre quadros recentemente renderizados.
/// </summary>
/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informações.</param>
CarenResult CarenDXGIOutput::GetFrameStatistics([Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetFrameStatistics(PonteiroTrabalho,
		Param_Out_EstatisticasFrame
	);
}

/// <summary>
/// (GetGammaControl) - Obtém as configurações de controle gama.
/// </summary>
/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que contém as informações do controle gamma.</param>
CarenResult CarenDXGIOutput::GetGammaControl([Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetGammaControl(PonteiroTrabalho,
		Param_Out_ControleGamma
	);
}

/// <summary>
/// (GetGammaControlCapabilities) - Obtém uma descrição das capacidades de controle gama.
/// </summary>
/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que contém as descrições das capcidades do controle Gamma.</param>
CarenResult CarenDXGIOutput::GetGammaControlCapabilities([Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetGammaControlCapabilities(PonteiroTrabalho,
		Param_Out_GammaCaps
	);
}

/// <summary>
/// (ReleaseOwnership) - Libera a propriedade da saída.
/// </summary>
CarenResult CarenDXGIOutput::ReleaseOwnership()
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::ReleaseOwnership(PonteiroTrabalho);
}

/// <summary>
/// (SetDisplaySurface) - Altera o modo de exibição.
/// </summary>
/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
CarenResult CarenDXGIOutput::SetDisplaySurface(ICarenDXGISurface^% Param_Superfice)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::SetDisplaySurface(PonteiroTrabalho,
		Param_Superfice
	);
}

/// <summary>
/// (SetGammaControl) - Define os controles gama.
/// </summary>
/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
CarenResult CarenDXGIOutput::SetGammaControl(CA_DXGI_GAMMA_CONTROL^ Param_ControleGama)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(E_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	DXGI_GAMMA_CONTROL *pGControl;

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
CarenResult CarenDXGIOutput::TakeOwnership(
	ICaren^ Param_DispositivoD3D, 
	Boolean Param_Exclusivo)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::TakeOwnership(PonteiroTrabalho,
		Param_DispositivoD3D,
		Param_Exclusivo
	);
}

/// <summary>
/// (WaitForVBlank ) - Pare um Thread até que o próximo espaço em branco vertical ocorra.
/// </summary>
CarenResult CarenDXGIOutput::WaitForVBlank()
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::WaitForVBlank(PonteiroTrabalho);
}


// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIOutput::GetParent(
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
CarenResult CarenDXGIOutput::SetPrivateData(
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
CarenResult CarenDXGIOutput::GetPrivateData(
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
CarenResult CarenDXGIOutput::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}
