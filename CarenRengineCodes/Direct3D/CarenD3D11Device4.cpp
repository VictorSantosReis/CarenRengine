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
#include "CarenD3D11Device4.h"

//Destruidor.
CarenD3D11Device4::~CarenD3D11Device4()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD3D11Device4::CarenD3D11Device4()
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
CarenResult CarenD3D11Device4::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Device4::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Device4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Device4**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD3D11Device4::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID3D11Device4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID3D11Device4**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Device4::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD3D11Device4::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD3D11Device4::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD3D11Device4::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD3D11Device4::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD3D11Device4::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD3D11Device4::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD3D11Device4::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD3D11Device4();
}



//Métodos da interface ICarenD3D11Device4

/// <summary>
/// (RegisterDeviceRemovedEvent) - Registra o evento "dispositivo removido" e indica quando um dispositivo Direct3D foi removido por qualquer motivo, usando um mecanismo de notificação assíncrona.
/// </summary>
/// <param name="Param_HandleEvento">Uma Handle para ser utilizada pelo evento.</param>
/// <param name="Param_Out_Cookie">Recebe um valor para informações sobre o evento "dispositivo removido", que pode ser usado no (UnregisterDeviceRemoved) para cancelar o registro do evento.</param>
CarenResult CarenD3D11Device4::RegisterDeviceRemovedEvent(
	ICarenEvent^ Param_HandleEvento,
	[Out] UInt32 Param_Out_Cookie)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::RegisterDeviceRemovedEvent(PonteiroTrabalho,
		Param_HandleEvento,
		Param_Out_Cookie
	);
}

/// <summary>
/// (UnregisterDeviceRemoved) - Desregistra o evento "dispositivo removido".
/// </summary>
/// <param name="Param_Cookie">Um valor sobre o evento "dispositivo removido", recuperadas durante uma chamada de RegisterDeviceRemovedEvent bem sucedida.</param>
CarenResult CarenD3D11Device4::UnregisterDeviceRemoved(UInt32 Param_Cookie)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::UnregisterDeviceRemoved(PonteiroTrabalho,
		Param_Cookie
	);
}




//Métodos da interface ICarenD3D11Device3

/// <summary>
/// (CreateDeferredContext3) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_Flags">Reservado para uso futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface do contexto diferido 3.</param>
CarenResult CarenD3D11Device4::CreateDeferredContext3(
	UInt32 Param_Flags,
	[Out] ICarenD3D11DeviceContext3^% Param_Out_ContextoDiferido)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDeferredContext3(PonteiroTrabalho,
		Param_Flags,
		Param_Out_ContextoDiferido
	);
}

/// <summary>
/// (CreateQuery1) - Cria um objeto de consulta para consulta de informações da unidade de processamento gráfico (GPU).
/// </summary>
/// <param name="Param_DescQuery">Uma estrutura CA_D3D11_QUERY_DESC1 que representa uma descrição de consulta.</param>
/// <param name="Param_Ref_Query">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Query1 para o objeto de consulta criado. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateQuery1(
	CA_D3D11_QUERY_DESC1^ Param_DescQuery,
	ICarenD3D11Query1^% Param_Ref_Query)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateQuery1(PonteiroTrabalho,
		Param_DescQuery,
		Param_Ref_Query
	);
}

/// <summary>
/// (CreateRasterizerState2) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de amostras enquanto o UAV renderiza ou rasteriza.
/// </summary>
/// <param name="Param_DescRasterizador">Uma estrutura CA_D3D11_RASTERIZER_DESC2 que descreve o estado rasterizador.</param>
/// <param name="Param_Ref_Rasterizador">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RasterizerState2 para o objeto de estado rasterizador criado. Defina este parâmetro 
/// como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateRasterizerState2(
	CA_D3D11_RASTERIZER_DESC2^ Param_DescRasterizador,
	ICarenD3D11RasterizerState2^% Param_Ref_Rasterizador)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateRasterizerState2(PonteiroTrabalho,
		Param_DescRasterizador,
		Param_Ref_Rasterizador
	);
}

/// <summary>
/// (CreateRenderTargetView1) - Cria uma visão de destino renderizado para acessar dados de recursos.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para a interface ICarenD3D11Resource que representa um destino de renderização. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_RENDER_TARGET.</param>
/// <param name="Param_DescRenderTarget">Uma estrutura CA_D3D11_RENDER_TARGET_VIEW_DESC1 que representa uma descrição de exibição de destino de renderização. Defina este parâmetro como NULO para criar uma exibição que 
/// acesse todos os subrecursos no nível 0 do mipmap.</param>
/// <param name="Param_Ref_RenderTarget">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RenderTargetView1 para a exibição de destino de renderização criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateRenderTargetView1(
	ICarenD3D11Resource^ Param_Recurso,
	CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_DescRenderTarget,
	ICarenD3D11RenderTargetView1^% Param_Ref_RenderTarget)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateRenderTargetView1(PonteiroTrabalho,
		Param_Recurso,
		Param_DescRenderTarget,
		Param_Ref_RenderTarget
	);
}

/// <summary>
/// (CreateShaderResourceView1) - Cria uma visão de recursos sombreadores para acessar dados em um recurso.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para o recurso que servirá como entrada para um sombreador. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_SHADER_RESOURCE.</param>
/// <param name="Param_DescShader">Uma estrutura CA_D3D11_SHADER_RESOURCE_VIEW_DESC1 que descreve uma visão de recursos mais sombreados. Defina esse parâmetro como NULO para criar uma exibição que acesse todo o 
/// recurso (usando o formato com o que o recurso foi criado).</param>
/// <param name="Param_Ref_Shader">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11ShaderResourceView1 para a exibição de recursos de sombreamento criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateShaderResourceView1(
	ICarenD3D11Resource^ Param_Recurso,
	CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_DescShader,
	ICarenD3D11ShaderResourceView1^% Param_Ref_Shader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateShaderResourceView1(PonteiroTrabalho,
		Param_Recurso,
		Param_DescShader,
		Param_Ref_Shader
	);
}

/// <summary>
/// (CreateTexture2D1) - Método responsável por criar uma textura 2D.
/// </summary>
/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE2D_DESC1 que descreve um recurso de textura 2D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 2D. Os aplicativos não podem especificar NULO para 
/// (Param_DadosSubrecurso) ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
/// <param name="Param_Ref_Textura2D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture2D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateTexture2D1(
	CA_D3D11_TEXTURE2D_DESC1^ Param_DescTextura,
	cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
	ICarenD3D11Texture2D1^% Param_Ref_Textura2D)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateTexture2D1(PonteiroTrabalho,
		Param_DescTextura,
		Param_DadosSubrecurso,
		Param_Ref_Textura2D
	);
}

/// <summary>
/// (CreateTexture3D1) - Método responsável por criar uma textura 3D.
/// </summary>
/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE3D_DESC1 que descreve um recurso de textura 3D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 3D. Os aplicativos não podem especificar NULO para (Param_DadosSubrecurso)
/// ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
/// <param name="Param_Ref_Textura3D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture3D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateTexture3D1(
	CA_D3D11_TEXTURE3D_DESC1^ Param_DescTextura,
	cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
	ICarenD3D11Texture3D1^% Param_Ref_Textura3D)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateTexture3D1(PonteiroTrabalho,
		Param_DescTextura,
		Param_DadosSubrecurso,
		Param_Ref_Textura3D
	);
}

/// <summary>
/// (CreateUnorderedAccessView1) - Cria uma visão para acessar um recurso de acesso não ordenado.
/// </summary>
/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC1) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
/// <param name="Param_Ref_ViewUnordered">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11UnorderedAccessView1 para a exibição de acesso não ordenado criada. Defina este 
/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
CarenResult CarenD3D11Device4::CreateUnorderedAccessView1(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^% Param_DescSombreador,
	ICarenD3D11UnorderedAccessView1^% Param_Ref_ViewUnordered)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateUnorderedAccessView1(PonteiroTrabalho,
		Param_Recurso,
		Param_DescSombreador,
		Param_Ref_ViewUnordered
	);
}

/// <summary>
/// (GetImmediateContext3) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface do contexto imediato ICarenD3D11DeviceContext3.</param>
CarenResult CarenD3D11Device4::GetImmediateContext3([Out] ICarenD3D11DeviceContext3^% Param_Out_Contexto)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetImmediateContext3(PonteiroTrabalho,
		Param_Out_Contexto
	);
}

/// <summary>
/// (ReadFromSubresource) - Copia dados de uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
/// </summary>
/// <param name="Param_BufferDestino">Um ponteiro para os dados de destino na memória.</param>
/// <param name="Param_DestinoPassoLinha">O tamanho de uma linha dos dados de destino.</param>
/// <param name="Param_DestinoPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de destino.</param>
/// <param name="Param_RecursoOrigem">Um ponteiro para o recurso de origem.</param>
/// <param name="Param_IndiceSubrecursoOrigem">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
/// <param name="Param_CaixaOrigem">Uma caixa que define a parte do subrecurso de destino para copiar os dados de recurso. Se NULO, os dados são lidos do subrecurso destino sem deslocamento. As dimensões do destino 
/// devem se adequar ao destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, 
/// ou o valor frontal for maior ou igual ao valor de trás. Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
CarenResult CarenD3D11Device4::ReadFromSubresource(
	ICarenBuffer^ Param_BufferDestino,
	UInt32 Param_DestinoPassoLinha,
	UInt32 Param_DestinoPassoProfundidade,
	ICarenD3D11Resource^ Param_RecursoOrigem,
	UInt32 Param_IndiceSubrecursoOrigem,
	CA_D3D11_BOX^ Param_CaixaOrigem)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::ReadFromSubresource(PonteiroTrabalho,
		Param_BufferDestino,
		Param_DestinoPassoLinha,
		Param_DestinoPassoProfundidade,
		Param_RecursoOrigem,
		Param_IndiceSubrecursoOrigem,
		Param_CaixaOrigem
	);
}

/// <summary>
/// (WriteToSubresource) - Copia dados em uma textura CA_D3D11_USAGE_DEFAULT que foi mapeada usando ICarenD3D11DeviceContext3::Mapear enquanto fornece um parâmetro NULO CA_D3D11_MAPPED_SUBRESOURCE.
/// </summary>
/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
/// <param name="Param_IndiceSubrecursoDestino">Um índice baseado em zero, que identifica o subrecurso de destino. consulte D3D11CalcSubresource para mais detalhes.</param>
/// <param name="Param_CaixaDestino">Uma caixa que define a parte do subrecurso de destino para copiar os dados do recurso em. Se NULO, os dados são gravados no subrecurso destino sem deslocamento. As dimensões da fonte 
/// devem se encaixar no destino(D3D11_BOX). Uma caixa vazia resulta em um no-op. Uma caixa está vazia se o valor superior for maior ou igual ao valor inferior, ou o valor esquerdo for maior ou igual ao valor certo, ou 
/// o valor frontal for maior ou igual ao valor de trás.Quando a caixa está vazia, este método não realiza nenhuma operação.</param>
/// <param name="Param_BufferOrigem">Um ponteiro para os dados de origem na memória.</param>
/// <param name="Param_OrigemPassoLinha">O tamanho de uma linha dos dados de origem.</param>
/// <param name="Param_OrigemPassoProfundidade">O tamanho de uma fatia de profundidade dos dados de origem.</param>
CarenResult CarenD3D11Device4::WriteToSubresource(
	ICarenD3D11Resource^ Param_RecursoDestino,
	UInt32 Param_IndiceSubrecursoDestino,
	CA_D3D11_BOX^ Param_CaixaDestino,
	ICarenBuffer^ Param_BufferOrigem,
	UInt32 Param_OrigemPassoLinha,
	UInt32 Param_OrigemPassoProfundidade)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::WriteToSubresource(PonteiroTrabalho,
		Param_RecursoDestino,
		Param_IndiceSubrecursoDestino,
		Param_CaixaDestino,
		Param_BufferOrigem,
		Param_OrigemPassoLinha,
		Param_OrigemPassoProfundidade
	);
}




//Métodos da interface ICarenD3D11Device2

/// <summary>
/// (CheckMultisampleQualityLevels1) - Obtenha o número de níveis de qualidade disponíveis durante a multiamostragem.
/// </summary>
/// <param name="Param_Formato">O formato de textura durante a multiamostragem.</param>
/// <param name="Param_QuantidadeSample">O número de amostras durante a multiamostragem.</param>
/// <param name="Param_Flags">Uma combinação de D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAGS valores que são combinados usando uma operação ou bitwise. 
/// Atualmente, apenas D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE é suportado.</param>
/// <param name="Param_Out_NiveisQualidade">Recebe o número de níveis de qualidade suportados pelo adaptador</param>
CarenResult CarenD3D11Device4::CheckMultisampleQualityLevels1(
	CA_DXGI_FORMAT Param_Formato,
	UInt32 Param_QuantidadeSample,
	CA_D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG Param_Flags,
	[Out] UInt32% Param_Out_NiveisQualidade)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckMultisampleQualityLevels1(PonteiroTrabalho,
		Param_Formato,
		Param_QuantidadeSample,
		Param_Flags,
		Param_Out_NiveisQualidade
	);
}

/// <summary>
/// (CreateDeferredContext2) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto diferido.</param>
CarenResult CarenD3D11Device4::CreateDeferredContext2(
	UInt32 Param_ContextFlags,
	[Out] ICarenD3D11DeviceContext2^% Param_Out_ContextoDiferido)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDeferredContext2(PonteiroTrabalho,
		Param_ContextFlags,
		Param_Out_ContextoDiferido
	);
}

/// <summary>
/// (GetImmediateContext2) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto imediato.</param>
CarenResult CarenD3D11Device4::GetImmediateContext2([Out] ICarenD3D11DeviceContext2^% Param_Out_Contexto)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetImmediateContext2(PonteiroTrabalho,
		Param_Out_Contexto
	);
}

/// <summary>
/// (GetResourceTiling) - Obtém informações sobre como um recurso de Tiles é dividido em blocos.
/// </summary>
/// <param name="Param_Recurso">Um ponteiro para a interface de recurso ICarenD3D11Resource a ser obtida as informações.</param>
/// <param name="Param_Out_NumeroTilesParaRecurso">Uma variável que recebe o número de Tiles necessárias para armazenar todo o recurso de Tiles.</param>
/// <param name="Param_Out_DescPackedMip">Uma estrutura CA_D3D11_PACKED_MIP_DESC que o (GetResourceTiling) preenche com informações sobre como os 
/// mipmaps do recurso de Tiles estão embalados.</param>
/// <param name="Param_Out_DescTileShape">Recebe uma estrutura CA_D3D11_TILE_SHAPE que (GetResourceTiling) preenche com informações sobre a forma do bloco. 
/// São informações sobre como os pixels se encaixam nos blocos, independentemente das dimensões do recurso em Tiles, sem incluir os mipmaps compactados. 
/// Se todo o recurso lado a lado estiver embalado, esse parâmetro não terá sentido porque o recurso lado a lado não possui layout definido para 
/// mipmaps compactados. Nessa situação, (GetResourceTiling) define os membros de CA_D3D11_TILE_SHAPE como zeros.</param>
/// <param name="Param_Ref_CountSubrecursoTile">Uma variável que contém o número de Tiles no subrecurso. Na entrada, este é o número de subrecursos para 
/// consulta de Tiles; na saída, este é o número que foi realmente recuperado em (Param_Out_DescTileShape) (fixado ao que está disponível).</param>
/// <param name="Param_PrimeiroSubrecursoObter">O número da primeira Tile do subrecursos para obter. (GetResourceTiling) ignora este parâmetro se o número 
/// que o (Param_Ref_CountSubrecursoTile) aponta é 0.</param>
/// <param name="Param_Out_DescTileSubrecurso">Recebe uma estrutura CA_D3D11_SUBRESOURCE_TILING que o (GetResourceTiling) preenche com informações sobre Tile 
/// de subrecursos.</param>
CarenResult CarenD3D11Device4::GetResourceTiling(
	ICarenD3D11Resource^ Param_Recurso,
	[Out] UInt32% Param_Out_NumeroTilesParaRecurso,
	[Out] CA_D3D11_PACKED_MIP_DESC^% Param_Out_DescPackedMip,
	[Out] CA_D3D11_TILE_SHAPE^% Param_Out_DescTileShape,
	UInt32% Param_Ref_CountSubrecursoTile,
	UInt32 Param_PrimeiroSubrecursoObter,
	[Out] CA_D3D11_SUBRESOURCE_TILING^% Param_Out_DescTileSubrecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetResourceTiling(PonteiroTrabalho,
		Param_Recurso,
		Param_Out_NumeroTilesParaRecurso,
		Param_Out_DescPackedMip,
		Param_Out_DescTileShape,
		Param_Ref_CountSubrecursoTile,
		Param_PrimeiroSubrecursoObter,
		Param_Out_DescTileSubrecurso
	);
}




//Métodos da interface ICarenD3D11Device1

/// <summary>
/// (CreateBlendState1) - Cria um objeto de estado-mistura que encapsula o estado de mistura para o estágio de fusão de saída e permite a configuração 
/// de operações lógicas.
/// </summary>
/// <param name="Param_Out_DescBlend">Recebe uma estrutura CA_D3D11_BLEND_DESC1 que descreve o BlendSate(Misturador de estado).</param>
/// <param name="Param_Out_BlendState">Recebe um ponteiro para a interface ICarenD3D11BlendState1 do misturador de estado.</param>
CarenResult CarenD3D11Device4::CreateBlendState1(
	[Out] CA_D3D11_BLEND_DESC1^% Param_Out_DescBlend,
	[Out] ICarenD3D11BlendState1^% Param_Out_BlendState)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateBlendState1(PonteiroTrabalho,
		Param_Out_DescBlend,
		Param_Out_BlendState
	);
}

/// <summary>
/// (CreateDeferredContext1) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interfcace ICarenD3D11DeviceContext1 do contexto diferido.</param>
CarenResult CarenD3D11Device4::CreateDeferredContext1(
	UInt32 Param_ContextFlags,
	[Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoDiferido)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDeferredContext1(PonteiroTrabalho,
		Param_ContextFlags,
		Param_Out_ContextoDiferido
	);
}

/// <summary>
/// (CreateDeviceContextState) - Cria um objeto de estado de contexto que detém todo o estado Microsoft Direct3D e algum comportamento Direct3D.
/// </summary>
/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG que são combinados usando uma operação ou bitwise. 
/// O valor resultante especifica como criar o objeto de estado de contexto. A bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADEDé atualmente é 
/// a única bandeira definida. Se o dispositivo original foi criado com D3D11_CREATE_DEVICE_SINGLETHREADED, você deve criar todos os objetos de estado 
/// de contexto daquele dispositivo com a bandeira D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADED.</param>
/// <param name="Param_NiveisRecurso">Uma matriz de valores CA_D3D_FEATURE_LEVEL. A matriz pode conter elementos da lista a seguir e determina a ordem dos 
/// níveis de recurso para os quais a criação é tentada. Ao contrário do D3D11CreateDevice, você não pode definir (Param_NiveisRecurso) para NULO porque 
/// não há um array padrão de nível de recurso.</param>
/// <param name="Param_QuantidadeNiveisRecurso">O número de elementos em (Param_NiveisRecurso). Ao contrário do D3D11CreateDevice, você deve definir os 
/// Níveis de Recursos para maiores de 0, porque você não pode definir (Param_NiveisRecurso) para NULO.</param>
/// <param name="Param_VersaoSDK">A versão SDK. Você deve definir este parâmetro para D3D11_SDK_VERSION.</param>
/// <param name="Param_RIIDInterfaceEmulada">O identificador globalmente único (GUID) para a interface emulada. Esse valor especifica o comportamento do 
/// dispositivo quando o objeto de estado de contexto está ativo.</param>
/// <param name="Param_Out_NivelRecursoDefinido">Recebe o nivel de recurso que foi aceito.</param>
/// <param name="Param_Out_EstadoContextoDispositivo">Recebe um ponteiro para um objeto ICarenD3DDeviceContextState que representa o estado de um dispositivo Direct3D.</param>
CarenResult CarenD3D11Device4::CreateDeviceContextState(
	CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG Param_Flags,
	cli::array<CA_D3D_FEATURE_LEVEL>^ Param_NiveisRecurso,
	UInt32 Param_QuantidadeNiveisRecurso,
	UInt32 Param_VersaoSDK,
	String^ Param_RIIDInterfaceEmulada,
	[Out] CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecursoDefinido,
	[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoContextoDispositivo)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDeviceContextState(PonteiroTrabalho,
		Param_Flags,
		Param_NiveisRecurso,
		Param_QuantidadeNiveisRecurso,
		Param_VersaoSDK,
		Param_RIIDInterfaceEmulada,
		Param_Out_NivelRecursoDefinido,
		Param_Out_EstadoContextoDispositivo
	);
}

/// <summary>
/// (CreateRasterizerState1) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de 
/// amostras enquanto o UAV renderiza ou rasteriza.
/// </summary>
/// <param name="Param_Out_DescRasterizer">Recebe uma estrutura com a descrição do rasterizador.</param>
/// <param name="Param_Out_Rasterizador">Recebe um ponteiro para a interface do rasterizador de estado.</param>
CarenResult CarenD3D11Device4::CreateRasterizerState1(
	[Out] CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizer,
	[Out] ICarenD3D11RasterizerState1^% Param_Out_Rasterizador)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateRasterizerState1(PonteiroTrabalho,
		Param_Out_DescRasterizer,
		Param_Out_Rasterizador
	);
}

/// <summary>
/// (GetImmediateContext1) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_ContextoImediato">Recebe um ponteiro para a interface ICarenD3D11DeviceContext1 do contexto imediato.</param>
CarenResult CarenD3D11Device4::GetImmediateContext1([Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoImediato)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetImmediateContext1(PonteiroTrabalho,
		Param_Out_ContextoImediato
	);
}

/// <summary>
/// (OpenSharedResource1) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado por uma alça e que foi criado em um dispositivo diferente.
/// </summary>
/// <param name="Param_HandleRecurso">Uma Handle para abrir o recurso. </param>
/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
/// não pode ser NULO.</param>
CarenResult CarenD3D11Device4::OpenSharedResource1(
	IntPtr Param_HandleRecurso,
	String^ Param_RIIDInterface,
	ICaren^% Param_Ref_InterfaceRecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::OpenSharedResource1(PonteiroTrabalho,
		Param_HandleRecurso,
		Param_RIIDInterface,
		Param_Ref_InterfaceRecurso
	);
}

/// <summary>
/// (OpenSharedResourceByName) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado pelo nome e que foi criado em um dispositivo 
/// diferente.
/// </summary>
/// <param name="Param_Nome">O nome do recurso para abrir. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_TipoAcesso">Os direitos de acesso solicitados ao recurso. Você pode utilizar as enumerações CA_ACCESS_RIGHTS e 
/// CA_DXGI_SHARED_RESOURCE_RW para definir este valor.</param>
/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
/// não pode ser NULO.</param>
CarenResult CarenD3D11Device4::OpenSharedResourceByName(
	String^ Param_Nome,
	UInt32 Param_TipoAcesso,
	String^ Param_RIIDInterface,
	ICaren^% Param_Ref_InterfaceRecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::OpenSharedResourceByName(PonteiroTrabalho,
		Param_Nome,
		Param_TipoAcesso,
		Param_RIIDInterface,
		Param_Ref_InterfaceRecurso
	);
}




//Métodos da interface ICarenD3D11Device

/// <summary>
/// (CheckCounter) - Obtém o tipo, nome, unidades de medida e uma descrição de um contador existente.
/// </summary>
/// <param name="Param_DescContador">Ponteiro para uma descrição do contador (CA_D3D11_DESC_CONTADOR). Especifica qual contador informação é para ser obtida sobre.</param>
/// <param name="Param_Out_TipoDadoContador">Ponteiro para o tipo de dados de um contador (CA_D3D11_TIPO_DADO_CONTADOR). Especifica o tipo de dados do contador de ser obtido.</param>
/// <param name="Param_Out_NumeroContadores">Ponteiro para o número de contadores de hardware que são necessários para esse tipo de contador ser criado. Todas as instâncias do mesmo tipo contador usam os contadores de hardware mesmo.</param>
/// <param name="Param_Out_NomeContador">Sequência a ser preenchido com um nome breve para o contador. Pode ser NULL se o aplicativo não está interessado em nome do balcão.</param>
/// <param name="Param_Out_LarguraNomeContador">Comprimento da sequência de caracteres retornada para Param_Out_NomeContador. Pode ser nulo.</param>
/// <param name="Param_Out_NomeUnidadeMedidas">Nome das unidades de medidas um contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
/// <param name="Param_Out_LarguraNomeUnidade">Comprimento da sequência de caracteres retornado para o Param_Out_NomeUnidadeMedidas. Pode ser nulo.</param>
/// <param name="Param_Out_DescContador">Uma descrição do contador, desde que a memória o ponteiro aponte para tem espaço suficiente para armazenar a string. Pode ser nulo. A sequência de caracteres retornada será sempre em inglês.</param>
/// <param name="Param_Out_LarguraDescContador">Comprimento da sequência de caracteres retornada para Param_Out_DescContador. Pode ser nulo.</param>
CarenResult CarenD3D11Device4::CheckCounter(
	Estruturas::CA_D3D11_DESC_CONTADOR^ Param_DescContador,
	[Out] Enumeracoes::CA_D3D11_TIPO_DADO_CONTADOR% Param_Out_TipoDadoContador,
	[Out] UInt32% Param_Out_NumeroContadores,
	[Out] String^% Param_Out_NomeContador,
	[Out] UInt32% Param_Out_LarguraNomeContador,
	[Out] String^% Param_Out_NomeUnidadeMedidas,
	[Out] UInt32% Param_Out_LarguraNomeUnidade,
	[Out] String^% Param_Out_DescContador,
	[Out] UInt32% Param_Out_LarguraDescContador
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckCounter(PonteiroTrabalho,
		Param_DescContador,
		Param_Out_TipoDadoContador,
		Param_Out_NumeroContadores,
		Param_Out_NomeContador,
		Param_Out_LarguraNomeContador,
		Param_Out_NomeUnidadeMedidas,
		Param_Out_LarguraNomeUnidade,
		Param_Out_DescContador,
		Param_Out_LarguraDescContador
	);
}

/// <summary>
/// (CheckCounterInfo) - Obter informações de um contador.
/// </summary>
/// <param name="Param_Out_InfoContador">Recebe uma estrutura com as informações do contador.</param>
CarenResult CarenD3D11Device4::CheckCounterInfo([Out] Estruturas::CA_D3D11_INFO_CONTADOR^% Param_Out_InfoContador)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckCounterInfo(PonteiroTrabalho,
		Param_Out_InfoContador
	);
}

/// <summary>
/// (CheckFeatureSupport) - Obtém informações sobre os recursos que são suportados pelo driver de gráficos atuais.
/// </summary>
/// <param name="Param_RecursoPesquisa">Um membro do CA_D3D11_RECURSO tipo enumerado que descreve qual recurso de consulta para apoio.</param>
/// <param name="Param_Out_SuporteRecurso">Após a conclusão do método, a passado estrutura é preenchida com dados que descreve o suporte para o recurso.</param>
/// <param name="Param_Out_TamanhoEstrutura">O tamanho da estrutura passado para o parâmetro Param_Out_SuporteRecurso.</param>
CarenResult CarenD3D11Device4::CheckFeatureSupport(
	Enumeracoes::CA_D3D11_RECURSO Param_RecursoPesquisa,
	[Out] Estruturas::CA_D3D11_FEATURE_DATA_THREADING^% Param_Out_SuporteRecurso,
	[Out] UInt32% Param_Out_TamanhoEstrutura
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckFeatureSupport(PonteiroTrabalho,
		Param_RecursoPesquisa,
		Param_Out_SuporteRecurso,
		Param_Out_TamanhoEstrutura
	);
}

/// <summary>
/// (CheckFormatSupport) - Obter o apoio de um determinado formato do dispositivo de vídeo instalado.
/// </summary>
/// <param name="Param_Formato">Uma enumeração de CA_DXGI_FORMAT que descreve um formato para o qual deseja verificar se há suporte.</param>
/// <param name="Param_Out_RecursosSuportados">Um campo de bits de D3D11_FORMAT_SUPPORT valores de enumeração que descreve como o formato especificado 
/// é suportado no dispositivo instalado. Os valores são ORed juntos.</param>
CarenResult CarenD3D11Device4::CheckFormatSupport(
	Enumeracoes::CA_DXGI_FORMAT Param_Formato,
	[Out] Enumeracoes::CA_D3D11_FORMAT_SUPPORT% Param_Out_RecursosSuportados)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckFormatSupport(PonteiroTrabalho,
		Param_Formato,
		Param_Out_RecursosSuportados
	);
}

/// <summary>
/// (CheckMultisampleQualityLevels) - Obter o número de níveis de qualidade disponíveis durante multisampling completo.
/// Quando multisampling uma textura, o número de níveis de qualidade disponíveis para um adaptador é dependente do formato de textura usado e o número de amostras 
/// solicitadas. O número máximo de níveis de qualidade é definido pelo D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT em D3D11.h. Se esse método retorna 0, a combinação de 
/// contagem de formato e amostra não tem suporte para o adaptador instalado.
/// </summary>
/// <param name="Param_Formato">O formato de textura. Consulte CA_DXGI_FORMAT.</param>
/// <param name="Param_NumeroAmostras">O número de amostras durante multisampling completo.</param>
/// <param name="Param_Out_NumeroNiveisQualidade">Recebe o número de níveis de qualidade suportada pelo adaptador.</param>
CarenResult CarenD3D11Device4::CheckMultisampleQualityLevels(
	Enumeracoes::CA_DXGI_FORMAT Param_Formato,
	UInt32 Param_NumeroAmostras,
	[Out] UInt32% Param_Out_NumeroNiveisQualidade)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CheckMultisampleQualityLevels(PonteiroTrabalho,
		Param_Formato,
		Param_NumeroAmostras,
		Param_Out_NumeroNiveisQualidade
	);
}

/// <summary>
/// (CreateBlendState) - Crie um objeto de mistura-estado que encapsules o estado de combinação para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_DescMistura">Uma descrição do estado de mistura.</param>
/// <param name="Param_Out_BlendState">Recebe uma interface para o objeto de estado de mistura criado.</param>
CarenResult CarenD3D11Device4::CreateBlendState(
	Estruturas::CA_D3D11_BLEND_DESC^% Param_DescMistura,
	[Out] ICarenD3D11BlendState^% Param_Out_BlendState)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateBlendState(PonteiroTrabalho,
		Param_DescMistura,
		Param_Out_BlendState
	);
}

/// <summary>
/// (CreateBuffer) - Cria um buffer (buffer de vértice, buffer de índice ou constante de sombreador buffer).
/// </summary>
/// <param name="Param_DescBuffer">Uma estrutura(CA_D3D11_BUFFER_DESC) que descreve o buffer.</param>
/// <param name="Param_DescDadosInit">uma estrutura(CA_D3D11_SUBRESOURCE_DATA) que descreve os dados de inicialização; Use NULL para alocar espaço só(com a exceção que não pode ser NULL se o sinalizador de 
/// uso é D3D11_USAGE_IMMUTABLE). Se você não passar nada para este paramêtro, o conteúdo inicial da memória para o buffer é indefinido. Neste caso, você precisa escrever o conteúdo do buffer de outra 
/// maneira, antes que o recurso é lido.</param>
/// <param name="Param_ValidarPametros">Defina como TRUE para validar os paramêtros de entrada do método. Se TRUE, Param_Out_InterfaceBuffer retorna NULO.</param>
/// <param name="Param_Out_InterfaceBuffer">Recebe a interface ICarenD3D11Buffer para o objeto de buffer criado.</param>
CarenResult CarenD3D11Device4::CreateBuffer(
	Estruturas::CA_D3D11_BUFFER_DESC^% Param_DescBuffer,
	Estruturas::CA_D3D11_SUBRESOURCE_DATA^% Param_DescDadosInit,
	Boolean Param_ValidarPametros,
	[Out] ICarenD3D11Buffer^% Param_Out_InterfaceBuffer)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateBuffer(PonteiroTrabalho,
		Param_DescBuffer,
		Param_DescDadosInit,
		Param_ValidarPametros,
		Param_Out_InterfaceBuffer
	);
}

/// <summary>
/// (CreateClassLinkage) - Cria bibliotecas de enlace de classe para permitir a ligação de sombreador dinâmico.
/// </summary>
/// <param name="Param_Out_ClassLinkage">Recebe a interface(ICarenD3D11ClassLinkage) de ligação de classe.</param>
CarenResult CarenD3D11Device4::CreateClassLinkage([Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkage)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateClassLinkage(PonteiroTrabalho,
		Param_Out_ClassLinkage
	);
}

/// <summary>
/// (CreateComputeShader) - Crie um sombreador de computação.
/// </summary>
/// <param name="Param_SombreadorCompilado">Um ponteiro para um objeto que contém um sombreador compilado. Geralmente se obtém esse ponteiro através do método (ICarenD3D10Blod::ObterPonteiroBuffer).</param>
/// <param name="Param_TamanhoSombreador">O Tamanho do sombreador no paramêtro(Param_SombreadorCompilado). Se está compilado com o ICarenD3D10Blod, utilize o método (ObterTamanhoBuffer) para recuperar esse valor.</param>
/// <param name="Param_LinkageClass">Um ponteiro para um ICarenD3D11ClassLinkage, que representa a interface de ligação de classe; o valor pode ser NULO.</param>
/// <param name="Param_ValidarParametros">Se TRUE, o método vai validar os paramêtros de entrada. Se for validado com sucesso, o método retorna SS_FALSE em vez de S_OK.</param>
/// <param name="Param_Out_ComputeShader">Recebe a interface(ICarenD3D11ComputeShader). Se (Param_ValidarPametros) for TRUE, esse parametro retorna um objeto NULO.</param>
CarenResult CarenD3D11Device4::CreateComputeShader(
	ICaren^ Param_SombreadorCompilado,
	UInt64 Param_TamanhoSombreador,
	ICarenD3D11ClassLinkage^ Param_LinkageClass,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateComputeShader(PonteiroTrabalho,
		Param_SombreadorCompilado,
		Param_TamanhoSombreador,
		Param_LinkageClass,
		Param_ValidarParametros,
		Param_Out_ComputeShader
	);
}

/// <summary>
/// (CreateCounter) - Crie um objeto de contador para medir o desempenho de GPU.
/// </summary>
/// <param name="Param_DescContador">Uma estrutura que contém a descrição do contador a ser criado.</param>
/// <param name="Param_Out_ContadorGPU">Recebe a interface que contem uma descrição do contador.</param>
CarenResult CarenD3D11Device4::CreateCounter(
	Estruturas::CA_D3D11_DESC_CONTADOR^% Param_DescContador,
	[Out] ICarenD3D11Counter^% Param_Out_ContadorGPU)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateCounter(PonteiroTrabalho,
		Param_DescContador,
		Param_Out_ContadorGPU
	);
}

/// <summary>
/// (CreateDeferredContext) - Cria um contexto diferido, que pode gravar listas de comando.
/// </summary>
/// <param name="Param_FlagsContexto">Reservado. Use 0.</param>
/// <param name="Param_Out_D3D11Contexto">Recebe a interface ICarenD3D11DeviceContext.</param>
CarenResult CarenD3D11Device4::CreateDeferredContext(
	UInt32 Param_FlagsContexto,
	[Out] ICarenD3D11DeviceContext^% Param_Out_D3D11Contexto)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDeferredContext(PonteiroTrabalho,
		Param_FlagsContexto,
		Param_Out_D3D11Contexto
	);
}

/// <summary>
/// (CreateDepthStencilState) - Crie um objeto de estado de profundidade-estêncil que encapsula as informações de teste de profundidade-estêncil para o estágio de saída-fusão.
/// </summary>
/// <param name="Param_DepthStencil">Uma estrutura(CA_D3D11_DEPTH_STENCIL_DESC) que descreve o estado de profundidade do Stencil.</param>
/// <param name="Param_Out_InterfaceStencil">Recebe a interface (ICarenD3D11DepthStencilState) de estado de profundidade do Stencil.</param>
CarenResult CarenD3D11Device4::CreateDepthStencilState(
	Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_DepthStencil,
	[Out] ICarenD3D11DepthStencilState^% Param_Out_InterfaceStencil)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDepthStencilState(PonteiroTrabalho,
		Param_DepthStencil,
		Param_Out_InterfaceStencil
	);
}

/// <summary>
/// (CreateDepthStencilView) - Crie uma exibição de profundidade-estêncil para acessar dados de recurso.
/// </summary>
/// <param name="Param_Resource">Ponteiro para o recurso que irá servir como a profundidade-superfície estêncil. Este recurso deve ter sido criado com o sinalizador (D3D11_BIND_DEPTH_STENCIL).</param>
/// <param name="Param_DepthStencilView">Ponteiro para uma descrição de profundidade-estêncil-vista. Defina este parâmetro como NULL para criar uma exibição que acessa o mipmap nível 0 do recurso 
/// inteiro (usando o recurso foi criado com o formato).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_InterfaceStencilView retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_InterfaceStencilView">Recebe a interface do Depth Stencil View do D3D11.</param>
CarenResult CarenD3D11Device4::CreateDepthStencilView(
	ICarenD3D11Resource^ Param_Resource,
	Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_DepthStencilView,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11DepthStencilView^% Param_Out_InterfaceStencilView
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDepthStencilView(PonteiroTrabalho,
		Param_Resource,
		Param_DepthStencilView,
		Param_ValidarParametros,
		Param_Out_InterfaceStencilView
	);
}

/// <summary>
/// (CreateDomainShader) - Crie um sombreador de domínio.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_DomainShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_DomainShader">Recebe a interface do Domain Shader.</param>
CarenResult CarenD3D11Device4::CreateDomainShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11DomainShader^% Param_Out_DomainShader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateDomainShader(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Linkage,
		Param_ValidarParametros,
		Param_Out_DomainShader
	);
}

/// <summary>
/// (CreateGeometryShader) - Crie um sombreador de geometria.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
CarenResult CarenD3D11Device4::CreateGeometryShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateGeometryShader(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Linkage,
		Param_ValidarParametros,
		Param_Out_GeometryShader
	);
}

/// <summary>
/// (CreateGeometryShaderWithStreamOutput) - Cria um sombreador de geometria que pode gravar em streaming de buffers de saída.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_SODeclarationArray">Uma matriz de CA_D3D11_SO_DECLARATION_ENTRY. Não pode ser NULO se Param_NumeroEntradas > 0.</param>
/// <param name="Param_NumeroEntradas">O número de entradas no fluxo de saída declaração (varia de 0 a D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT).</param>
/// <param name="Param_BufferStrideArray">Uma matriz de passos de reserva; cada passo é do tamanho de um elemento para o buffer.</param>
/// <param name="Param_NumeroStrides">O número de passos (ou buffers) em Param_BufferStrideArray (varia de 0 a D3D11_SO_BUFFER_SLOT_COUNT(4)).</param>
/// <param name="Param_NumeroIndicesFluxo">O número de índice do fluxo a ser enviado para o palco do rasterizador (varia de 0 a D3D11_SO_STREAM_COUNT - 1). Conjunto para D3D11_SO_NO_RASTERIZED_STREAM se nenhum fluxo for ser rasterizada.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
CarenResult CarenD3D11Device4::CreateGeometryShaderWithStreamOutput
(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	cli::array<Estruturas::CA_D3D11_SO_DECLARATION_ENTRY^>^ Param_SODeclarationArray,
	UInt32 Param_NumeroEntradas,
	cli::array<UInt32>^ Param_BufferStrideArray,
	UInt32 Param_NumeroStrides,
	UInt32 Param_NumeroIndicesFluxo,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateGeometryShaderWithStreamOutput(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_SODeclarationArray,
		Param_NumeroEntradas,
		Param_BufferStrideArray,
		Param_NumeroStrides,
		Param_NumeroIndicesFluxo,
		Param_Linkage,
		Param_ValidarParametros,
		Param_Out_GeometryShader
	);
}

/// <summary>
/// (CreateHullShader) - Crie um sombreador de casco.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_Out_HullShader">Recebe a interface do Hull Shader.</param>
CarenResult CarenD3D11Device4::CreateHullShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	[Out] ICarenD3D11HullShader^% Param_Out_HullShader
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateHullShader(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Linkage,
		Param_Out_HullShader
	);
}

/// <summary>
/// (CreateInputLayout) - Crie um objeto de entrada-layout para descrever os dados do buffer de entrada para o estágio de entrada-montador.
/// </summary>
/// <param name="Param_ArrayTiposDadosEntrada">Uma matriz de tipos de dados de entrada do estágio de entrada-montador; cada tipo é descrito por uma descrição do elemento</param>
/// <param name="Param_CountElementos">O número de tipos de dados de entrada na matriz de elementos de entrada.</param>
/// <param name="Param_ShaderByteCode">Um ponteiro para o shader compilado. O código compilado de sombreador contém uma assinatura de entrada que é validada contra a matriz de elementos.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Out_InputLayout">Recebe a interface do Input Layout.</param>
CarenResult CarenD3D11Device4::CreateInputLayout(
	cli::array<Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^>^ Param_ArrayTiposDadosEntrada,
	UInt32 Param_CountElementos,
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout
)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateInputLayout(PonteiroTrabalho,
		Param_ArrayTiposDadosEntrada,
		Param_CountElementos,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Out_InputLayout
	);
}

/// <summary>
/// (CreatePixelShader) - Crie um sombreador de pixel.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_PixelShader retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_PixelShader">Recebe a interface do Hull Shader.</param>
CarenResult CarenD3D11Device4::CreatePixelShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11PixelShader^% Param_Out_PixelShader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreatePixelShader(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Linkage,
		Param_ValidarParametros,
		Param_Out_PixelShader
	);
}

/// <summary>
/// (CreatePredicate) - Cria um predicado.
/// </summary>
/// <param name="Param_DescPredicado">Ponteiro para uma descrição de consulta onde o tipo de consulta deve ser uma D3D11_QUERY_SO_OVERFLOW_PREDICATE ou D3D11_QUERY_OCCLUSION_PREDICATE</param>
/// <param name="Param_Out_Predicado">Recebe a interface do Predicado criado.</param>
CarenResult CarenD3D11Device4::CreatePredicate(
	Estruturas::CA_D3D11_QUERY_DESC^% Param_DescPredicado,
	[Out] ICarenD3D11Predicate^% Param_Out_Predicado)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreatePredicate(PonteiroTrabalho,
		Param_DescPredicado,
		Param_Out_Predicado
	);
}

/// <summary>
/// (CreateQuery) - Essa interface encapsula métodos para consultar informações da GPU.
/// </summary>
/// <param name="Param_DescQuery">Uma descrição da interface de consulta a ser criada.</param>
/// <param name="Param_Out_Query">Recebe a interface de consulta criada.</param>
CarenResult CarenD3D11Device4::CreateQuery(
	Estruturas::CA_D3D11_QUERY_DESC^% Param_DescQuery,
	[Out] ICarenD3D11Query^% Param_Out_Query)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateQuery(PonteiroTrabalho,
		Param_DescQuery,
		Param_Out_Query
	);
}

/// <summary>
/// (CreateRasterizerState) - Crie um objeto de estado rasterizador que informa o rasterizador de palco como se comportar.
/// </summary>
/// <param name="Param_DescRasterizador">Uma estrutura com a descrição do estado do rasterizador.</param>
/// <param name="Param_Out_Rasterizador">Recebe a interface de Rasterização criada.</param>
CarenResult CarenD3D11Device4::CreateRasterizerState(
	Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_DescRasterizador,
	[Out] ICarenD3D11RasterizerState^% Param_Out_Rasterizador)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateRasterizerState(PonteiroTrabalho,
		Param_DescRasterizador,
		Param_Out_Rasterizador
	);
}

/// <summary>
/// (CreateRenderTargetView) - Cria uma exibição de destino de processamento para acesso a dados de recurso.
/// </summary>
/// <param name="Param_Resource">Um ponteiro para interface ID3D11Resource que representa um destino de processamento. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_RENDER_TARGET .</param>
/// <param name="Param_DescRender">Uma estrutura D3D11_RENDER_TARGET_VIEW_DESC que representa uma descrição do modo de exibição render-alvo. Defina este parâmetro como NULL para criar uma exibição 
/// que acessa todos os sub-recursos mipmap nível 0.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ViewRender retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_ViewRender">Recebe a interface do visualizador de render.</param>
CarenResult CarenD3D11Device4::CreateRenderTargetView(
	ICarenD3D11Resource^ Param_Resource,
	Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11RenderTargetView^% Param_Out_ViewRender)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateRenderTargetView(PonteiroTrabalho,
		Param_Resource,
		Param_DescRender,
		Param_ValidarParametros,
		Param_Out_ViewRender
	);
}

/// <summary>
/// (CreateSamplerState) - Crie um objeto de sampler-estado que encapsula as informações de amostragem para uma textura.
/// </summary>
/// <param name="Param_DescSampler">Uma descrição do estado do amostrador</param>
/// <param name="Param_Out_SamplerState">Recebe a interface do Sampler Sate.</param>
CarenResult CarenD3D11Device4::CreateSamplerState(
	Estruturas::CA_D3D11_SAMPLER_DESC^% Param_DescSampler,
	[Out] ICarenD3D11SamplerState^% Param_Out_SamplerState)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateSamplerState(PonteiroTrabalho,
		Param_DescSampler,
		Param_Out_SamplerState
	);
}

/// <summary>
/// (CreateShaderResourceView) - Crie uma exibição de sombreador-recurso para acessar dados em um recurso.
/// </summary>
/// <param name="Param_Recurso">Ponteiro para o recurso que irá servir como entrada para um sombreador. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_SHADER_RESOURCE .</param>
/// <param name="Param_DescExbi">Ponteiro para uma descrição de exibição de sombreador-recurso (veja D3D11_SHADER_RESOURCE_VIEW_DESC). Defina este parâmetro como NULL para criar uma 
/// exibição que acessa o recurso inteiro (usando o recurso foi criado com o formato).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ShaderView retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_ShaderView">Recebe a interface para o visualizador de Shader.</param>
CarenResult CarenD3D11Device4::CreateShaderResourceView(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_DescExbi,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11ShaderResourceView^% Param_Out_ShaderView)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateShaderResourceView(PonteiroTrabalho,
		Param_Recurso,
		Param_DescExbi,
		Param_ValidarParametros,
		Param_Out_ShaderView
	);
}

/// <summary>
/// (CreateTexture1D) - Cria uma matriz de texturas 1D.
/// </summary>
/// <param name="Param_DescTextura1D">Uma estrutura CA_D3D11_TEXTURE1D_DESC que descreve um recurso de textura 1D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 1D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura1D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura1D">Recebe a interface que contém o buffer da interface de Textura 1D.</param>
CarenResult CarenD3D11Device4::CreateTexture1D(
	Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_DescTextura1D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture1D^% Param_Out_Textura1D)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateTexture1D(PonteiroTrabalho,
		Param_DescTextura1D,
		Param_ArrayDescSubRecursos,
		Param_TamanhoArraySubRecursos,
		Param_ValidarParametros,
		Param_Out_Textura1D
	);
}

/// <summary>
/// (CreateTexture2D) - Crie uma matriz de texturas 2D.
/// </summary>
/// <param name="Param_DescTextura2D">Uma estrutura CA_D3D11_TEXTURE2D_DESC que descreve um recurso de textura 2D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 2D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura2D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura2D">Recebe a interface que contém o buffer da interface de Textura 2D.</param>
CarenResult CarenD3D11Device4::CreateTexture2D(
	Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_DescTextura2D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture2D^% Param_Out_Textura2D)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateTexture2D(PonteiroTrabalho,
		Param_DescTextura2D,
		Param_ArrayDescSubRecursos,
		Param_TamanhoArraySubRecursos,
		Param_ValidarParametros,
		Param_Out_Textura2D
	);
}

/// <summary>
/// (CreateTexture3D) - Crie uma única textura 3D.
/// </summary>
/// <param name="Param_DescTextura3D">Uma estrutura CA_D3D11_TEXTURE3D_DESC que descreve um recurso de textura 3D. Para criar um recurso sem especificação de tipo que pode ser interpretado 
/// em tempo de execução em formatos diferentes, compatíveis, especifica um formato sem especificação de tipo na descrição de textura. Para gerar níveis mipmap automaticamente, defina o número de níveis 
/// mipmap para 0.</param>
/// <param name="Param_ArrayDescSubRecursos">Uma matriz de CA_D3D11_SUBRESOURCE_DATA estruturas que descrevem sub-recursos para o recurso de textura 3D. Aplicativos não é possível especificar NULL para 
/// Param_ArrayDescSubRecursos ao criar recursos imutáveis. Se o recurso for multisampled, Param_ArrayDescSubRecursos deve ser nulo , porque não é possível inicializar recursos multisampled com dados 
/// quando eles são criados.</param>
/// <param name="Param_TamanhoArraySubRecursos">Contém o valor que define o tamanho do array no parametro (Param_ArrayDescSubRecursos).</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_Textura3D retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_Textura3D">Recebe a interface que contém o buffer da interface de Textura 3D.</param>
CarenResult CarenD3D11Device4::CreateTexture3D(
	Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_DescTextura3D,
	cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
	UInt32 Param_TamanhoArraySubRecursos,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11Texture3D^% Param_Out_Textura3D)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateTexture3D(PonteiroTrabalho,
		Param_DescTextura3D,
		Param_ArrayDescSubRecursos,
		Param_TamanhoArraySubRecursos,
		Param_ValidarParametros,
		Param_Out_Textura3D
	);
}

/// <summary>
/// (CreateUnorderedAccessView) - Cria uma visão para acessar um recurso de acesso não ordenada.
/// </summary>
/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
/// <param name="Param_Out_Interface">Recebe a interface do Recurso de acesso não ordenado.</param>
CarenResult CarenD3D11Device4::CreateUnorderedAccessView(
	ICarenD3D11Resource^ Param_Recurso,
	Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_DescSombreador,
	[Out] ICarenD3D11UnorderedAccessView^% Param_Out_Interface)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateUnorderedAccessView(PonteiroTrabalho,
		Param_Recurso,
		Param_DescSombreador,
		Param_Out_Interface
	);
}

/// <summary>
/// (CreateVertexShader) - Crie um objeto shader de vértice de um sombreador compilado.
/// </summary>
/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_VertexShaderInterface retorna NULL se esse paramêtro for verdadeiro.</param>
/// <param name="Param_Out_VertexShader">Recebe a interface do Vertex Shader.</param>
CarenResult CarenD3D11Device4::CreateVertexShader(
	ICaren^ Param_ShaderByteCode,
	UInt64 Param_TamanhoByteCode,
	ICarenD3D11ClassLinkage^ Param_Linkage,
	Boolean Param_ValidarParametros,
	[Out] ICarenD3D11VertexShader^% Param_Out_VertexShader)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::CreateVertexShader(PonteiroTrabalho,
		Param_ShaderByteCode,
		Param_TamanhoByteCode,
		Param_Linkage,
		Param_ValidarParametros,
		Param_Out_VertexShader
	);
}

/// <summary>
/// (GetCreationFlags) - Se os sinalizadores usados durante a chamada para criar o dispositivo com D3D11CreateDevice.
/// </summary>
/// <param name="Param_Out_Flags">Recebe um flags de bit a bits da enumerção (CA_D3D11_CREATE_DEVICE_FLAG) que contém o modo de criaçã do dispositivo.</param>
CarenResult CarenD3D11Device4::GetCreationFlags([Out] Enumeracoes::CA_D3D11_CREATE_DEVICE_FLAG% Param_Out_Flags)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetCreationFlags(PonteiroTrabalho,
		Param_Out_Flags
	);
}

/// <summary>
/// (GetDeviceRemovedReason) - A razão por que o dispositivo foi removido. Esse método retorna um (ResultCode) informando o motivo.
/// </summary>
CarenResult CarenD3D11Device4::GetDeviceRemovedReason()
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetDeviceRemovedReason(PonteiroTrabalho);
}

/// <summary>
/// (GetExceptionMode) - Obter os sinalizadores de modo de exceção.
/// </summary>
/// <param name="Param_Out_Except">Um valor que contém um ou mais sinalizadores de exceção; Cada sinalizador especifica uma condição que fará com que uma exceção seja levantada. Os sinalizadores estão 
/// listados em D3D11_RAISE_FLAG. Um valor padrão de 0 significa que não há sinalizadores.</param>
CarenResult CarenD3D11Device4::GetExceptionMode([Out] Enumeracoes::CA_D3D11_RAISE_FLAG% Param_Out_Except)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetExceptionMode(PonteiroTrabalho,
		Param_Out_Except
	);
}

/// <summary>
/// (GetFeatureLevel) - Obtém o nível de funcionalidade de dispositivo de hardware.
/// </summary>
/// <param name="Param_Out_NivelRecurso">Recebe um flag de bits a bits de um ou mais sinlizadores de niveis de recuso do dispositivo de hardware.</param>
CarenResult CarenD3D11Device4::GetFeatureLevel([Out] Enumeracoes::CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecurso)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetFeatureLevel(PonteiroTrabalho,
		Param_Out_NivelRecurso
	);
}

/// <summary>
/// (GetImmediateContext) - Obtém um contexto imediato, que pode reproduzir listas de comando.
/// </summary>
/// <param name="Param_Out_ImediateContextInterface">Recebe a interface do contexto do dispositivo.</param>
CarenResult CarenD3D11Device4::GetImmediateContext([Out] ICarenD3D11DeviceContext^% Param_Out_ImediateContextInterface)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetImmediateContext(PonteiroTrabalho,
		Param_Out_ImediateContextInterface
	);
}

/// <summary>
/// (GetPrivateData) - Obtém dados application-defined de um dispositivo.
/// </summary>
/// <param name="Param_Guid">O Guid associado ao buffer.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer de saida.</param>
/// <param name="Param_Out_TamanhoBufferSaida">Recebe o tamanho que total do buffer no parametro (Param_Out_Buffer).</param>
/// <param name="Param_Out_Buffer">Recebe a interface que gerencia o buffer retornado.</param>
CarenResult CarenD3D11Device4::GetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	[Out] UInt32% Param_Out_TamanhoBufferSaida,
	[Out] ICarenBuffer^% Param_Out_Buffer)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::GetPrivateData(PonteiroTrabalho,
		Param_Guid,
		Param_TamanhoBuffer,
		Param_Out_TamanhoBufferSaida,
		Param_Out_Buffer
	);
}

/// <summary>
/// (OpenSharedResource) - Dar um dispositivo de acesso a um recurso compartilhado, criado em um dispositivo diferente.
/// </summary>
/// <param name="Param_Handle">Um identificador de recurso.</param>
/// <param name="Param_GuidInterface">O identificador globalmente exclusivo (GUID) para a interface do recurso.</param>
/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface do recurso que foi ganhado acesso. O usuário deve criar a interfaces antes de chamar este método.</param>
CarenResult CarenD3D11Device4::OpenSharedResource(
	IntPtr Param_Handle,
	String^ Param_GuidInterface,
	ICaren^ Param_Out_InterfaceSolicitada)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::OpenSharedResource(PonteiroTrabalho,
		Param_Handle,
		Param_GuidInterface,
		Param_Out_InterfaceSolicitada
	);
}

/// <summary>
/// (SetExceptionMode) - Obter os sinalizadores de modo de exceção.
/// </summary>
/// <param name="Param_RaiseFlags">Os flags de modo de exceção.</param>
CarenResult CarenD3D11Device4::SetExceptionMode(UInt32 Param_RaiseFlags)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::SetExceptionMode(PonteiroTrabalho,
		Param_RaiseFlags
	);
}

/// <summary>
/// (SetPrivateData) - Define os dados para um dispositivo e associa esses dados a um guid.
/// </summary>
/// <param name="Param_Guid">O Guid associado ao buffer.</param>
/// <param name="Param_TamanhoBuffer">O tamanho do buffer de entrada.</param>
/// <param name="Param_Buffer">Ponteiro para os dados sejam armazenados com este dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer dados anteriormente associados com o 
/// guid serão destruídos.</param>
CarenResult CarenD3D11Device4::SetPrivateData(
	String^ Param_Guid,
	UInt32 Param_TamanhoBuffer,
	ICarenBuffer^ Param_Buffer)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::SetPrivateData(PonteiroTrabalho,
		Param_Guid,
		Param_TamanhoBuffer,
		Param_Buffer
	);
}

/// <summary>
/// (SetPrivateDataInterface) - Associar uma interface IUnknown-derivado desta criança de dispositivo e associar essa interface com um guid definido pelo aplicativo.
/// </summary>
/// <param name="Param_Guid">O Guid associado a interface a ser definida.</param>
/// <param name="Param_Interface">Ponteiro para uma interface derivada de IUnknown para ser associado ao filho do dispositivo.</param>
CarenResult CarenD3D11Device4::SetPrivateDataInterface(
	String^ Param_Guid,
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do D3D11.
	return Shared_D3D11Device::SetPrivateDataInterface(PonteiroTrabalho,
		Param_Guid,
		Param_Interface
	);
}
