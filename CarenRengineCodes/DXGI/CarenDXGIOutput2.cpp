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
#include "CarenDXGIOutput2.h"

//Destruidor.
CarenDXGIOutput2::~CarenDXGIOutput2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGIOutput2::CarenDXGIOutput2()
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
CarenResult CarenDXGIOutput2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIOutput2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIOutput2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIOutput2**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIOutput2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIOutput2*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIOutput2**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIOutput2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIOutput2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIOutput2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIOutput2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenDXGIOutput2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIOutput2::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIOutput2::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIOutput2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIOutput2();
}


//
// Métodos da interface proprietária(ICarenDXGIOutput2)
//

/// <summary>
/// (SupportsOverlays) - Consulta uma saída de adaptador para suporte de sobreposição multiplano.
/// </summary>
/// <param name="Param_Out_Suporte">Recebe TRUE se o adaptador de saída é o adaptador primário e suporta sobreposições multiplanárias, caso 
/// contrário retorna FALSE.</param>
CarenResult CarenDXGIOutput2::SupportsOverlays([Out] Boolean Param_Out_Suporte)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::SupportsOverlays(PonteiroTrabalho,
		Param_Out_Suporte
	);
}




// Métodos da interface ICarenDXGIOutput1

/// <summary>
/// (DuplicateOutput) - Cria uma interface de duplicação de desktop a partir da interface ICarenDXGIOutput1 que representa uma saída de 
/// adaptador.
/// </summary>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que você pode usar para processar a imagem da área de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a saída está conectada.</param>
/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
CarenResult CarenDXGIOutput6::DuplicateOutput(
	ICaren^ Param_Dispositivo3D, 
	[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::DuplicateOutput(PonteiroTrabalho,
		Param_Dispositivo3D,
		Param_Out_SaidaDuplicada
	);
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
CarenResult CarenDXGIOutput2::FindClosestMatchingMode1(
	CA_DXGI_MODE_DESC1^ Param_DescCombine,
	ICaren^ Param_Dispositivo3D,
	[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::FindClosestMatchingMode1(PonteiroTrabalho,
		Param_DescCombine,
		Param_Dispositivo3D,
		Param_Out_DescCorrespondente
	);
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
/// para o qual o (Param_Out_MatrizDescModos) aponta. Defina (Param_Out_MatrizDescModos) para NULO para que o (Param_Ref_QuantidadeModos) 
/// retorne o número de modos de exibição que correspondam ao formato e às opções. Caso contrário, o (Param_Ref_QuantidadeModos) retorna o 
/// número de modos de exibição devolvidos no (Param_Out_MatrizDescModos).</param>
/// <param name="Param_Out_MatrizDescModos">Recebe uma lista de modos de exibição.</param>
CarenResult CarenDXGIOutput2::GetDisplayModeList1(
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDescModos)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetDisplayModeList1(PonteiroTrabalho,
		Param_Formato,
		Param_Flags,
		Param_RecuperaQuantidadeModos,
		Param_Ref_QuantidadeModos,
		Param_Out_MatrizDescModos
	);
}

/// <summary>
/// (GetDisplaySurfaceData1) - Copia a superfície do display(buffer frontal) para um recurso fornecido pelo usuário.
/// </summary>
/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
/// (GetDisplaySurfaceData1) copia a superfície do display. A interface não pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
CarenResult CarenDXGIOutput2::GetDisplaySurfaceData1(ICarenDXGIResource^ Param_SuperficeDestino)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetDisplaySurfaceData1(PonteiroTrabalho,
		Param_SuperficeDestino
	);
}




// Métodos da interface ICarenDXGIOutput

/// <summary>
/// (FindClosestMatchingMode) - Encontra o modo de exibição que mais se corresponde ao modo de exibição solicitado.
/// </summary>
/// <param name="Param_ModoDesc">O modo de exibição desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC não podem ser especificados indicando nenhuma preferência por esse membro. Um valor de 0 para largura ou altura indica 
/// que o valor não é especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que não é especificado. Outros membros da DXGI_MODE_DESC têm valores de enumeração indicando 
/// que o membro não é especificado. Se (Param_Dispositivo3D) é NULO, formatonão pode ser DXGI_FORMAT_UNKNOWN.</param>
/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este parâmetro é NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) serão devolvidos; caso contrário, apenas os formatos que 
/// são suportados para digitalização pelo dispositivo são devolvidos.</param>
CarenResult CarenDXGIOutput2::FindClosestMatchingMode(
	CA_DXGI_MODE_DESC^ Param_ModoDesc, 
	[Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, 
	ICaren^ Param_Dispositivo3D)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::FindClosestMatchingMode(PonteiroTrabalho,
		Param_ModoDesc,
		Param_Out_ModoMaisAproximado,
		Param_Dispositivo3D
	);
}

/// <summary>
/// (GetDesc) - Obter uma descrição da saída.
/// </summary>
/// <param name="Param_Out_DescSaida">Retorna uma estrutura que contém a descrição da saida.</param>
CarenResult CarenDXGIOutput2::GetDesc([Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida)
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
CarenResult CarenDXGIOutput2::GetDisplayModeList(
	CA_DXGI_FORMAT Param_Formato,
	CA_DXGI_ENUM_MODES Param_Flags,
	Boolean Param_RecuperaQuantidadeModos,
	UInt32% Param_Ref_QuantidadeModos,
	[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetDisplayModeList(PonteiroTrabalho,
		Param_Formato,
		Param_Flags,
		Param_RecuperaQuantidadeModos,
		Param_Ref_QuantidadeModos,
		Param_Out_MatrizDescModos
		);
}

/// <summary>
/// (GetDisplaySurfaceData) - Obtém uma cópia da superfície de exibição atual.
/// O método só pode ser chamado quando uma saída está no modo de tela cheia. Se o método for bem-sucedido, a DXGI preenche a superfície do destino.
/// </summary>
/// <param name="Param_SuperficeDestino">Um ponteiro para uma superfície de destino que vai receber a superfice.</param>
CarenResult CarenDXGIOutput2::GetDisplaySurfaceData(ICarenDXGISurface^% Param_SuperficeDestino)
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
CarenResult CarenDXGIOutput2::GetFrameStatistics([Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame)
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
CarenResult CarenDXGIOutput2::GetGammaControl([Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma)
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
CarenResult CarenDXGIOutput2::GetGammaControlCapabilities([Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::GetGammaControlCapabilities(PonteiroTrabalho,
		Param_Out_GammaCaps
	);
}

/// <summary>
/// (ReleaseOwnership) - Libera a propriedade da saída.
/// </summary>
CarenResult CarenDXGIOutput2::ReleaseOwnership()
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::ReleaseOwnership(PonteiroTrabalho);
}

/// <summary>
/// (SetDisplaySurface) - Altera o modo de exibição.
/// </summary>
/// <param name="Param_Superfice">Um ponteiro para uma superfície usado para renderizar uma imagem para a tela. A superfície deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
CarenResult CarenDXGIOutput2::SetDisplaySurface(ICarenDXGISurface^% Param_Superfice)
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
CarenResult CarenDXGIOutput2::SetGammaControl(CA_DXGI_GAMMA_CONTROL^ Param_ControleGama)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIOutput::SetGammaControl(PonteiroTrabalho,
		Param_ControleGama
	);
}

/// <summary>
/// (TakeOwnership) - Toma posse de uma saída. Quando você terminar com a saída, chame o método ICarenDXGIOutput::ReleaseOwnership().
/// Este método não deve ser chamado diretamente por aplicativos, uma vez que os resultados serão imprevisíveis. É chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transições em tela cheia, e não deve ser usado como 
/// um substituto para métodos de cadeia de swap.
/// </summary>
/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros tópicos ou aplicativos para assumir a propriedade do dispositivo; caso contrário, definido como FALSE.</param>
CarenResult CarenDXGIOutput2::TakeOwnership(
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
CarenResult CarenDXGIOutput2::WaitForVBlank()
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
CarenResult CarenDXGIOutput2::GetParent(
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
CarenResult CarenDXGIOutput2::SetPrivateData(
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
CarenResult CarenDXGIOutput2::GetPrivateData(
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
CarenResult CarenDXGIOutput2::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}