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


#pragma once
#include "../SDK_Direct3D11.h"
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"


//Importa o namespace que contém as interfaces da API primária.
using namespace CarenRengine::Direct3D11;

//Importa o namesspace do DXGI.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
///
/// </summary>
class Shared_D3D11Resource
{
public:
	/// <summary>
	/// (GetEvictionPriority) - Obtém a prioridade de despejo de um recurso.
	/// </summary>
	/// <param name="Param_Out_Prioridade">Retorna a prioridade do recurso que está sendo usado.</param>
	static CarenResult GetEvictionPriority(
		ID3D11Resource* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO% Param_Out_Prioridade);

	/// <summary>
	/// (GetType) - Obtém o tipo de recurso.
	/// </summary>
	/// <param name="Param_Out_TipoRecurso">Retorna o tipo do recurso usado.</param>
	static CarenResult GetType(
		ID3D11Resource* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D11_TIPO_RECURSO% Param_Out_TipoRecurso);

	/// <summary>
	/// (SetEvictionPriority) - Define a prioridade de despejo de um recurso.
	/// Prioridades de recursos determinam qual recurso despejo de memória de vídeo quando o sistema ficou sem memória de vídeo. O recurso não será perdido; será removido da memória de vídeo e colocado na 
	/// memória do sistema ou possivelmente colocado no disco rígido. O recurso será carregado volta na memória de vídeo quando for necessário.
	/// </summary>
	/// <param name="Param_PrioridadeRecurso">Define o tipo do recurso sendo usado.</param>
	static CarenResult SetEvictionPriority(
		ID3D11Resource* Param_MyPointerWork, 
		Enumeracoes::CA_DXGI_PRIORIDADE_RECURSO Param_PrioridadeRecurso);
};

/// <summary>
/// 
/// </summary>
class Shared_D3D11Device
{
	//Métodos da interface(ICarenD3D11Device5)
public:
	/// <summary>
	/// (CreateFence) - Cria um objeto de cerca. 
	/// Essa função de membro é equivalente ao Direct3D 12 ID3D12Device::CreateFence função, e se aplica entre Direct3D 11 e Direct3D 12 em cenários interop.
	/// </summary>
	/// <param name="Param_DadosInicias">O valor inicial da cerca.</param>
	/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_FENCE_FLAG que são combinados usando uma operação or bitwise. O valor resultante especifica opções para a vedação.</param>
	/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface de cerca(ICarenD3D11Fence).</param>
	/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence que é usado para acessar a cerca.</param>
	static CarenResult CreateFence(
		ID3D11Device5* Param_MyPointerWork,
		UInt64 Param_DadosInicias,
		CA_D3D11_FENCE_FLAG Param_Flags,
		String^ Param_RIIDInterface,
		ICarenD3D11Fence^% Param_Ref_FenceInterface);

	/// <summary>
	/// (OpenSharedFence) - Abre uma alça para uma cerca compartilhada usando HANDLE e REFIID. Esta função de membro é uma versão limitada do Direct3D 12 ID3D12Device::OpenSharedHandle função membro, e se aplica entre 
	/// Direct3D 11 e Direct3D 12 em cenários interop.Ao contrário do ID3D12Device::OpenSharedHandle que opera com recursos, montes e cercas, a função ICarenD3D11Device5::OpenSharedFence só funciona em cercas; 
	/// no Direct3D 11, os recursos compartilhados são abertos com a função de membro ICarenD3D11Device1::OpenSharedResource1.
	/// </summary>
	/// <param name="Param_Handle">A handle que foi devolvida por uma chamada para ICarenD3D11Fence::CreateSharedHandle ou ID3D12Device::CreateSharedHandle.</param>
	/// <param name="Param_RIIDInterface">O identificador globalmente único(GUID) para a interface ICarenD3D11Fence</param>
	/// <param name="Param_Ref_FenceInterface">Um ponteiro para um bloco de memória que recebe um ponteiro para a interface ICarenD3D11Fence.</param>
	static CarenResult OpenSharedFence(
		ID3D11Device5* Param_MyPointerWork,
		IntPtr Param_Handle,
		String^ Param_RIIDInterface,
		ICarenD3D11Fence^% Param_Ref_FenceInterface);




	//Métodos da interface(ICarenD3D11Device4)
public:
	/// <summary>
	/// (RegisterDeviceRemovedEvent) - Registra o evento "dispositivo removido" e indica quando um dispositivo Direct3D foi removido por qualquer motivo, usando um mecanismo de notificação assíncrona.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para ser utilizada pelo evento.</param>
	/// <param name="Param_Out_Cookie">Recebe um valor para informações sobre o evento "dispositivo removido", que pode ser usado no (UnregisterDeviceRemoved) para cancelar o registro do evento.</param>
	static CarenResult RegisterDeviceRemovedEvent(
		ID3D11Device4* Param_MyPointerWork,
		ICarenEvent^ Param_HandleEvento,
		[Out] UInt32 Param_Out_Cookie);

	/// <summary>
	/// (UnregisterDeviceRemoved) - Desregistra o evento "dispositivo removido".
	/// </summary>
	/// <param name="Param_Cookie">Um valor sobre o evento "dispositivo removido", recuperadas durante uma chamada de RegisterDeviceRemovedEvent bem sucedida.</param>
	static CarenResult UnregisterDeviceRemoved(ID3D11Device4* Param_MyPointerWork, UInt32 Param_Cookie);



	//Métodos da interface(ICarenD3D11Device3)
public:
	/// <summary>
	/// (CreateDeferredContext3) - Cria um contexto diferido, que pode gravar listas de comando.
	/// </summary>
	/// <param name="Param_Flags">Reservado para uso futuro. Deixe como ZERO(0).</param>
	/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface do contexto diferido 3.</param>
	static CarenResult CreateDeferredContext3(
		ID3D11Device3* Param_MyPointerWork,
		UInt32 Param_Flags,
		[Out] ICarenD3D11DeviceContext3^% Param_Out_ContextoDiferido);

	/// <summary>
	/// (CreateQuery1) - Cria um objeto de consulta para consulta de informações da unidade de processamento gráfico (GPU).
	/// </summary>
	/// <param name="Param_DescQuery">Uma estrutura CA_D3D11_QUERY_DESC1 que representa uma descrição de consulta.</param>
	/// <param name="Param_Ref_Query">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Query1 para o objeto de consulta criado. Defina este parâmetro como NULO para validar os outros 
	/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateQuery1(
		ID3D11Device3* Param_MyPointerWork,
		CA_D3D11_QUERY_DESC1^ Param_DescQuery,
		ICarenD3D11Query1^% Param_Ref_Query);

	/// <summary>
	/// (CreateRasterizerState2) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de amostras enquanto o UAV renderiza ou rasteriza.
	/// </summary>
	/// <param name="Param_DescRasterizador">Uma estrutura CA_D3D11_RASTERIZER_DESC2 que descreve o estado rasterizador.</param>
	/// <param name="Param_Ref_Rasterizador">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RasterizerState2 para o objeto de estado rasterizador criado. Defina este parâmetro 
	/// como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateRasterizerState2(
		ID3D11Device3* Param_MyPointerWork,
		CA_D3D11_RASTERIZER_DESC2^ Param_DescRasterizador,
		ICarenD3D11RasterizerState2^% Param_Ref_Rasterizador);

	/// <summary>
	/// (CreateRenderTargetView1) - Cria uma visão de destino renderizado para acessar dados de recursos.
	/// </summary>
	/// <param name="Param_Recurso">Ponteiro para a interface ICarenD3D11Resource que representa um destino de renderização. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_RENDER_TARGET.</param>
	/// <param name="Param_DescRenderTarget">Uma estrutura CA_D3D11_RENDER_TARGET_VIEW_DESC1 que representa uma descrição de exibição de destino de renderização. Defina este parâmetro como NULO para criar uma exibição que 
	/// acesse todos os subrecursos no nível 0 do mipmap.</param>
	/// <param name="Param_Ref_RenderTarget">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11RenderTargetView1 para a exibição de destino de renderização criada. Defina este 
	/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateRenderTargetView1(
		ID3D11Device3* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		CA_D3D11_RENDER_TARGET_VIEW_DESC1^ Param_DescRenderTarget,
		ICarenD3D11RenderTargetView1^% Param_Ref_RenderTarget);

	/// <summary>
	/// (CreateShaderResourceView1) - Cria uma visão de recursos sombreadores para acessar dados em um recurso.
	/// </summary>
	/// <param name="Param_Recurso">Ponteiro para o recurso que servirá como entrada para um sombreador. Esse recurso deve ter sido criado com a bandeira D3D11_BIND_SHADER_RESOURCE.</param>
	/// <param name="Param_DescShader">Uma estrutura CA_D3D11_SHADER_RESOURCE_VIEW_DESC1 que descreve uma visão de recursos mais sombreados. Defina esse parâmetro como NULO para criar uma exibição que acesse todo o 
	/// recurso (usando o formato com o que o recurso foi criado).</param>
	/// <param name="Param_Ref_Shader">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11ShaderResourceView1 para a exibição de recursos de sombreamento criada. Defina este 
	/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateShaderResourceView1(
		ID3D11Device3* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		CA_D3D11_SHADER_RESOURCE_VIEW_DESC1^ Param_DescShader,
		ICarenD3D11ShaderResourceView1^% Param_Ref_Shader);

	/// <summary>
	/// (CreateTexture2D1) - Método responsável por criar uma textura 2D.
	/// </summary>
	/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE2D_DESC1 que descreve um recurso de textura 2D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
	/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
	/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 2D. Os aplicativos não podem especificar NULO para 
	/// (Param_DadosSubrecurso) ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
	/// <param name="Param_Ref_Textura2D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture2D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
	/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateTexture2D1(
		ID3D11Device3* Param_MyPointerWork,
		CA_D3D11_TEXTURE2D_DESC1^ Param_DescTextura,
		cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
		ICarenD3D11Texture2D1^% Param_Ref_Textura2D);

	/// <summary>
	/// (CreateTexture3D1) - Método responsável por criar uma textura 3D.
	/// </summary>
	/// <param name="Param_DescTextura">Uma estrutura CA_D3D11_TEXTURE3D_DESC1 que descreve um recurso de textura 3D. Para criar um recurso sem digitar que pode ser interpretado em tempo de execução em diferentes 
	/// formatos compatíveis, especifique um formato sem digite na descrição da textura. Para gerar níveis de mipmap automaticamente, defina o número de níveis de mipmap como 0.</param>
	/// <param name="Param_DadosSubrecurso">Uma matriz de estruturas CA_D3D11_SUBRESOURCE_DATA que descrevem subrecursos para o recurso de textura 3D. Os aplicativos não podem especificar NULO para (Param_DadosSubrecurso)
	/// ao criar recursos IMMUTABLE. Se o recurso for multiamostrado, (Param_DadosSubrecurso) deve ser NULO porque os recursos multiamostrados não podem ser inicializados com dados quando são criados.</param>
	/// <param name="Param_Ref_Textura3D">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11Texture3D1 para a textura criada. Defina este parâmetro como NULO para validar os outros 
	/// parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateTexture3D1(
		ID3D11Device3* Param_MyPointerWork,
		CA_D3D11_TEXTURE3D_DESC1^ Param_DescTextura,
		cli::array<CA_D3D11_SUBRESOURCE_DATA^>^ Param_DadosSubrecurso,
		ICarenD3D11Texture3D1^% Param_Ref_Textura3D);

	/// <summary>
	/// (CreateUnorderedAccessView1) - Cria uma visão para acessar um recurso de acesso não ordenado.
	/// </summary>
	/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
	/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC1) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
	/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
	/// <param name="Param_Ref_ViewUnordered">Um ponteiro para um bloco de memória que recebe um ponteiro para uma interface ICarenD3D11UnorderedAccessView1 para a exibição de acesso não ordenado criada. Defina este 
	/// parâmetro como NULO para validar os outros parâmetros de entrada (o método retornará SS_FALSE se os outros parâmetros de entrada passarem pela validação).</param>
	static CarenResult CreateUnorderedAccessView1(
		ID3D11Device3* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1^% Param_DescSombreador,
		ICarenD3D11UnorderedAccessView1^% Param_Ref_ViewUnordered);

	/// <summary>
	/// (GetImmediateContext3) - Obtém um contexto imediato, que pode reproduzir listas de comando.
	/// </summary>
	/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface do contexto imediato ICarenD3D11DeviceContext3.</param>
	static CarenResult GetImmediateContext3(ID3D11Device3* Param_MyPointerWork, [Out] ICarenD3D11DeviceContext3^% Param_Out_Contexto);

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
	static CarenResult ReadFromSubresource(
		ID3D11Device3* Param_MyPointerWork,
		ICarenBuffer^ Param_BufferDestino,
		UInt32 Param_DestinoPassoLinha,
		UInt32 Param_DestinoPassoProfundidade,
		ICarenD3D11Resource^ Param_RecursoOrigem,
		UInt32 Param_IndiceSubrecursoOrigem,
		CA_D3D11_BOX^ Param_CaixaOrigem);

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
	static CarenResult WriteToSubresource(
		ID3D11Device3* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoDestino,
		UInt32 Param_IndiceSubrecursoDestino,
		CA_D3D11_BOX^ Param_CaixaDestino,
		ICarenBuffer^ Param_BufferOrigem,
		UInt32 Param_OrigemPassoLinha,
		UInt32 Param_OrigemPassoProfundidade);



	//Métodos da interface(ICarenD3D11Device2)
public:
	/// <summary>
	/// (CheckMultisampleQualityLevels1) - Obtenha o número de níveis de qualidade disponíveis durante a multiamostragem.
	/// </summary>
	/// <param name="Param_Formato">O formato de textura durante a multiamostragem.</param>
	/// <param name="Param_QuantidadeSample">O número de amostras durante a multiamostragem.</param>
	/// <param name="Param_Flags">Uma combinação de D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAGS valores que são combinados usando uma operação ou bitwise. 
	/// Atualmente, apenas D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE é suportado.</param>
	/// <param name="Param_Out_NiveisQualidade">Recebe o número de níveis de qualidade suportados pelo adaptador</param>
	static CarenResult CheckMultisampleQualityLevels1(
		ID3D11Device2* Param_MyPointerWork,
		CA_DXGI_FORMAT Param_Formato,
		UInt32 Param_QuantidadeSample,
		CA_D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG Param_Flags,
		[Out] UInt32% Param_Out_NiveisQualidade);

	/// <summary>
	/// (CreateDeferredContext2) - Cria um contexto diferido, que pode gravar listas de comando.
	/// </summary>
	/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
	/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto diferido.</param>
	static CarenResult CreateDeferredContext2(
		ID3D11Device2* Param_MyPointerWork,
		UInt32 Param_ContextFlags,
		[Out] ICarenD3D11DeviceContext2^% Param_Out_ContextoDiferido);

	/// <summary>
	/// (GetImmediateContext2) - Obtém um contexto imediato, que pode reproduzir listas de comando.
	/// </summary>
	/// <param name="Param_Out_Contexto">Recebe um ponteiro para a interface ICarenD3D11DeviceContext2 do contexto imediato.</param>
	static CarenResult GetImmediateContext2(ID3D11Device2* Param_MyPointerWork, [Out] ICarenD3D11DeviceContext2^% Param_Out_Contexto);

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
	static CarenResult GetResourceTiling(
		ID3D11Device2* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		[Out] UInt32% Param_Out_NumeroTilesParaRecurso,
		[Out] CA_D3D11_PACKED_MIP_DESC^% Param_Out_DescPackedMip,
		[Out] CA_D3D11_TILE_SHAPE^% Param_Out_DescTileShape,
		UInt32% Param_Ref_CountSubrecursoTile,
		UInt32 Param_PrimeiroSubrecursoObter,
		[Out] CA_D3D11_SUBRESOURCE_TILING^% Param_Out_DescTileSubrecurso);





	//Métodos da interface(ICarenD3D11Device1)
public:
	/// <summary>
	/// (CreateBlendState1) - Cria um objeto de estado-mistura que encapsula o estado de mistura para o estágio de fusão de saída e permite a configuração 
	/// de operações lógicas.
	/// </summary>
	/// <param name="Param_Out_DescBlend">Recebe uma estrutura CA_D3D11_BLEND_DESC1 que descreve o BlendSate(Misturador de estado).</param>
	/// <param name="Param_Out_BlendState">Recebe um ponteiro para a interface ICarenD3D11BlendState1 do misturador de estado.</param>
	static CarenResult CreateBlendState1(
		ID3D11Device1* Param_MyPointerWork, 
		[Out] CA_D3D11_BLEND_DESC1^% Param_Out_DescBlend, 
		[Out] ICarenD3D11BlendState1^% Param_Out_BlendState);

	/// <summary>
	/// (CreateDeferredContext1) - Cria um contexto diferido, que pode gravar listas de comando.
	/// </summary>
	/// <param name="Param_ContextFlags">Valor reservado para o futuro. Deixe como ZERO(0).</param>
	/// <param name="Param_Out_ContextoDiferido">Recebe um ponteiro para a interfcace ICarenD3D11DeviceContext1 do contexto diferido.</param>
	static CarenResult CreateDeferredContext1(
		ID3D11Device1* Param_MyPointerWork,
		UInt32 Param_ContextFlags, 
		[Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoDiferido);

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
	static CarenResult CreateDeviceContextState(
		ID3D11Device1* Param_MyPointerWork,
		CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG Param_Flags,
		cli::array<CA_D3D_FEATURE_LEVEL>^ Param_NiveisRecurso,
		UInt32 Param_QuantidadeNiveisRecurso,
		UInt32 Param_VersaoSDK,
		String^ Param_RIIDInterfaceEmulada,
		[Out] CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecursoDefinido,
		[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoContextoDispositivo);

	/// <summary>
	/// (CreateRasterizerState1) - Cria um objeto de estado rasterizador que informa o estágio de rasterizador como se comportar e força a contagem de 
	/// amostras enquanto o UAV renderiza ou rasteriza.
	/// </summary>
	/// <param name="Param_Out_DescRasterizer">Recebe uma estrutura com a descrição do rasterizador.</param>
	/// <param name="Param_Out_Rasterizador">Recebe um ponteiro para a interface do rasterizador de estado.</param>
	static CarenResult CreateRasterizerState1(
		ID3D11Device1* Param_MyPointerWork,
		[Out] CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizer,
		[Out] ICarenD3D11RasterizerState1^% Param_Out_Rasterizador);

	/// <summary>
	/// (GetImmediateContext1) - Obtém um contexto imediato, que pode reproduzir listas de comando.
	/// </summary>
	/// <param name="Param_Out_ContextoImediato">Recebe um ponteiro para a interface ICarenD3D11DeviceContext1 do contexto imediato.</param>
	static CarenResult GetImmediateContext1(
		ID3D11Device1* Param_MyPointerWork, 
		[Out] ICarenD3D11DeviceContext1^% Param_Out_ContextoImediato);

	/// <summary>
	/// (OpenSharedResource1) - Dá a um dispositivo acesso a um recurso compartilhado que é referenciado por uma alça e que foi criado em um dispositivo diferente.
	/// </summary>
	/// <param name="Param_HandleRecurso">Uma Handle para abrir o recurso. </param>
	/// <param name="Param_RIIDInterface">O identificador globalmente único (GUID) para a interface de recursos a ser retornada.</param>
	/// <param name="Param_Ref_InterfaceRecurso">Retorna um ponteiro para a interface de recurso requisitada no (Param_RIIDInterface). Este parametro 
	/// não pode ser NULO.</param>
	static CarenResult OpenSharedResource1(
		ID3D11Device1* Param_MyPointerWork,
		IntPtr Param_HandleRecurso,
		String^ Param_RIIDInterface,
		ICaren^% Param_Ref_InterfaceRecurso);

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
	static CarenResult OpenSharedResourceByName(
		ID3D11Device1* Param_MyPointerWork,
		String^ Param_Nome,
		UInt32 Param_TipoAcesso,
		String^ Param_RIIDInterface,
		ICaren^% Param_Ref_InterfaceRecurso);



	//Métodos da interface(ICarenD3D11Device)
public:
	/// <summary>
	/// (CheckCounter) - Obter o tipo, nome, unidades de medida e uma descrição de um contador existente.
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
	static CarenResult CheckCounter(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_DESC_CONTADOR^ Param_DescContador,
		[Out] Enumeracoes::CA_D3D11_TIPO_DADO_CONTADOR% Param_Out_TipoDadoContador,
		[Out] UInt32% Param_Out_NumeroContadores,
		[Out] String^% Param_Out_NomeContador,
		[Out] UInt32% Param_Out_LarguraNomeContador,
		[Out] String^% Param_Out_NomeUnidadeMedidas,
		[Out] UInt32% Param_Out_LarguraNomeUnidade,
		[Out] String^% Param_Out_DescContador,
		[Out] UInt32% Param_Out_LarguraDescContador
	);

	/// <summary>
	/// (CheckCounterInfo) - Obter informações de um contador.
	/// </summary>
	/// <param name="Param_Out_InfoContador">Recebe uma estrutura com as informações do contador.</param>
	static CarenResult CheckCounterInfo(
		ID3D11Device* Param_MyPointerWork, 
		[Out] Estruturas::CA_D3D11_INFO_CONTADOR^% Param_Out_InfoContador);

	/// <summary>
	/// (CheckFeatureSupport) - Obtém informações sobre os recursos que são suportados pelo driver de gráficos atuais.
	/// </summary>
	/// <param name="Param_RecursoPesquisa">Um membro do CA_D3D11_RECURSO tipo enumerado que descreve qual recurso de consulta para apoio.</param>
	/// <param name="Param_Out_SuporteRecurso">Após a conclusão do método, a passado estrutura é preenchida com dados que descreve o suporte para o recurso.</param>
	/// <param name="Param_Out_TamanhoEstrutura">O tamanho da estrutura passado para o parâmetro Param_Out_SuporteRecurso.</param>
	static CarenResult CheckFeatureSupport(
		ID3D11Device* Param_MyPointerWork,
		Enumeracoes::CA_D3D11_RECURSO Param_RecursoPesquisa,
		[Out] Estruturas::CA_D3D11_FEATURE_DATA_THREADING^% Param_Out_SuporteRecurso,
		[Out] UInt32% Param_Out_TamanhoEstrutura
	);

	/// <summary>
	/// (CheckFormatSupport) - Obter o apoio de um determinado formato do dispositivo de vídeo instalado.
	/// </summary>
	/// <param name="Param_Formato">Uma enumeração de CA_DXGI_FORMAT que descreve um formato para o qual deseja verificar se há suporte.</param>
	/// <param name="Param_Out_RecursosSuportados">Um campo de bits de D3D11_FORMAT_SUPPORT valores de enumeração que descreve como o formato especificado 
	/// é suportado no dispositivo instalado. Os valores são ORed juntos.</param>
	static CarenResult CheckFormatSupport(
		ID3D11Device* Param_MyPointerWork,
		Enumeracoes::CA_DXGI_FORMAT Param_Formato,
		[Out] Enumeracoes::CA_D3D11_FORMAT_SUPPORT% Param_Out_RecursosSuportados);

	/// <summary>
	/// (CheckMultisampleQualityLevels) - Obter o número de níveis de qualidade disponíveis durante multisampling completo.
	/// Quando multisampling uma textura, o número de níveis de qualidade disponíveis para um adaptador é dependente do formato de textura usado e o número de amostras 
	/// solicitadas. O número máximo de níveis de qualidade é definido pelo D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT em D3D11.h. Se esse método retorna 0, a combinação de 
	/// contagem de formato e amostra não tem suporte para o adaptador instalado.
	/// </summary>
	/// <param name="Param_Formato">O formato de textura. Consulte CA_DXGI_FORMAT.</param>
	/// <param name="Param_NumeroAmostras">O número de amostras durante multisampling completo.</param>
	/// <param name="Param_Out_NumeroNiveisQualidade">Recebe o número de níveis de qualidade suportada pelo adaptador.</param>
	static CarenResult CheckMultisampleQualityLevels(
		ID3D11Device* Param_MyPointerWork,
		Enumeracoes::CA_DXGI_FORMAT Param_Formato,
		UInt32 Param_NumeroAmostras, [Out] UInt32% Param_Out_NumeroNiveisQualidade);

	/// <summary>
	/// (CreateBlendState) - Crie um objeto de mistura-estado que encapsules o estado de combinação para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_DescMistura">Uma descrição do estado de mistura.</param>
	/// <param name="Param_Out_BlendState">Recebe uma interface para o objeto de estado de mistura criado.</param>
	static CarenResult CreateBlendState(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_BLEND_DESC^% Param_DescMistura,
		[Out] ICarenD3D11BlendState^% Param_Out_BlendState);

	/// <summary>
	/// (CreateBuffer) - Cria um buffer (buffer de vértice, buffer de índice ou constante de sombreador buffer).
	/// </summary>
	/// <param name="Param_DescBuffer">Uma estrutura(CA_D3D11_BUFFER_DESC) que descreve o buffer.</param>
	/// <param name="Param_DescDadosInit">uma estrutura(CA_D3D11_SUBRESOURCE_DATA) que descreve os dados de inicialização; Use NULL para alocar espaço só(com a exceção que não pode ser NULL se o sinalizador de 
	/// uso é D3D11_USAGE_IMMUTABLE). Se você não passar nada para este paramêtro, o conteúdo inicial da memória para o buffer é indefinido. Neste caso, você precisa escrever o conteúdo do buffer de outra 
	/// maneira, antes que o recurso é lido.</param>
	/// <param name="Param_ValidarPametros">Defina como TRUE para validar os paramêtros de entrada do método. Se TRUE, Param_Out_InterfaceBuffer retorna NULO.</param>
	/// <param name="Param_Out_InterfaceBuffer">Recebe a interface ICarenD3D11Buffer para o objeto de buffer criado.</param>
	static CarenResult CreateBuffer(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_BUFFER_DESC^% Param_DescBuffer,
		Estruturas::CA_D3D11_SUBRESOURCE_DATA^% Param_DescDadosInit,
		Boolean Param_ValidarPametros,
		[Out] ICarenD3D11Buffer^% Param_Out_InterfaceBuffer);

	/// <summary>
	/// (CreateClassLinkage) - Cria bibliotecas de enlace de classe para permitir a ligação de sombreador dinâmico.
	/// </summary>
	/// <param name="Param_Out_ClassLinkage">Recebe a interface(ICarenD3D11ClassLinkage) de ligação de classe.</param>
	static CarenResult CreateClassLinkage(
		ID3D11Device* Param_MyPointerWork, 
		[Out] ICarenD3D11ClassLinkage^% Param_Out_ClassLinkage);

	/// <summary>
	/// (CreateComputeShader) - Crie um sombreador de computação.
	/// </summary>
	/// <param name="Param_SombreadorCompilado">Um ponteiro para um objeto que contém um sombreador compilado. Geralmente se obtém esse ponteiro através do método (ICarenD3D10Blod::ObterPonteiroBuffer)</param>
	/// <param name="Param_TamanhoSombreador">O Tamanho do sombreador no paramêtro(Param_SombreadorCompilado). Se está compilado com o ICarenD3D10Blod, utilize o método (ObterTamanhoBuffer) para recuperar esse valor.</param>
	/// <param name="Param_LinkageClass">Um ponteiro para um ICarenD3D11ClassLinkage, que representa a interface de ligação de classe; o valor pode ser NULO.</param>
	/// <param name="Param_ValidarParametros">Se TRUE, o método vai validar os paramêtros de entrada. Se for validado com sucesso, o método retorna SS_FALSE em vez de S_OK.</param>
	/// <param name="Param_Out_ComputeShader">Recebe a interface(ICarenD3D11ComputeShader). Se (Param_ValidarPametros) for TRUE, esse parametro retorna um objeto NULO.</param>
	static CarenResult CreateComputeShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_SombreadorCompilado,
		UInt64 Param_TamanhoSombreador,
		ICarenD3D11ClassLinkage^ Param_LinkageClass,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader);

	/// <summary>
	/// (CreateCounter) - Crie um objeto de contador para medir o desempenho de GPU.
	/// </summary>
	/// <param name="Param_DescContador">Uma estrutura que contém a descrição do contador a ser criado.</param>
	/// <param name="Param_Out_ContadorGPU">Recebe a interface que contem uma descrição do contador.</param>
	static CarenResult CreateCounter(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_DESC_CONTADOR^% Param_DescContador,
		[Out] ICarenD3D11Counter^% Param_Out_ContadorGPU);

	/// <summary>
	/// (CreateDeferredContext) - Cria um contexto diferido, que pode gravar listas de comando.
	/// </summary>
	/// <param name="Param_FlagsContexto">Reservado. Use 0.</param>
	/// <param name="Param_Out_D3D11Contexto">Recebe a interface ICarenD3D11DeviceContext.</param>
	static CarenResult CreateDeferredContext(
		ID3D11Device* Param_MyPointerWork,
		UInt32 Param_FlagsContexto,
		[Out] ICarenD3D11DeviceContext^% Param_Out_D3D11Contexto);

	/// <summary>
	/// (CreateDepthStencilState) - Crie um objeto de estado de profundidade-estêncil que encapsula as informações de teste de profundidade-estêncil para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_DepthStencil">Uma estrutura(CA_D3D11_DEPTH_STENCIL_DESC) que descreve o estado de profundidade do Stencil.</param>
	/// <param name="Param_Out_InterfaceStencil">Recebe a interface (ICarenD3D11DepthStencilState) de estado de profundidade do Stencil.</param>
	static CarenResult CreateDepthStencilState(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_DEPTH_STENCIL_DESC^% Param_DepthStencil,
		[Out] ICarenD3D11DepthStencilState^% Param_Out_InterfaceStencil);

	/// <summary>
	/// (CreateDepthStencilView) - Crie uma exibição de profundidade-estêncil para acessar dados de recurso.
	/// </summary>
	/// <param name="Param_Resource">Ponteiro para o recurso que irá servir como a profundidade-superfície estêncil. Este recurso deve ter sido criado com o sinalizador (D3D11_BIND_DEPTH_STENCIL).</param>
	/// <param name="Param_DepthStencilView">Ponteiro para uma descrição de profundidade-estêncil-vista. Defina este parâmetro como NULL para criar uma exibição que acessa o mipmap nível 0 do recurso 
	/// inteiro (usando o recurso foi criado com o formato).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_InterfaceStencilView retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_InterfaceStencilView">Recebe a interface do Depth Stencil View do D3D11.</param>
	static CarenResult CreateDepthStencilView(
		ID3D11Device* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Resource,
		Estruturas::CA_D3D11_DEPTH_STENCIL_VIEW_DESC^% Param_DepthStencilView,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11DepthStencilView^% Param_Out_InterfaceStencilView
	);

	/// <summary>
	/// (CreateDomainShader) - Crie um sombreador de domínio.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_DomainShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_DomainShader">Recebe a interface do Domain Shader.</param>
	static CarenResult CreateDomainShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		ICarenD3D11ClassLinkage^ Param_Linkage,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11DomainShader^% Param_Out_DomainShader);

	/// <summary>
	/// (CreateGeometryShader) - Crie um sombreador de geometria.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
	static CarenResult CreateGeometryShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		ICarenD3D11ClassLinkage^ Param_Linkage,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11GeometryShader^% Param_Out_GeometryShader);

	/// <summary>
	/// (CreateGeometryShaderWithStreamOutput) - Cria um sombreador de geometria que pode gravar em streaming de buffers de saída.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_SODeclarationArray">Uma matriz de CA_D3D11_SO_DECLARATION_ENTRY. Não pode ser NULO se Param_NumeroEntradas > 0.</param>
	/// <param name="Param_NumeroEntradas">O número de entradas no fluxo de saída declaração (varia de 0 a D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT).</param>
	/// <param name="Param_BufferStrideArray">Uma matriz de passos de reserva; cada passo é do tamanho de um elemento para o buffer.</param>
	/// <param name="Param_NumeroStrides">O número de passos (ou buffers) em Param_BufferStrideArray (varia de 0 a D3D11_SO_BUFFER_SLOT_COUNT).</param>
	/// <param name="Param_NumeroIndicesFluxo">O número de índice do fluxo a ser enviado para o palco do rasterizador (varia de 0 a D3D11_SO_STREAM_COUNT - 1). Conjunto para D3D11_SO_NO_RASTERIZED_STREAM se nenhum fluxo for ser rasterizada.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface; o valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_GeometryShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_GeometryShader">Recebe a interface do Geometry Shader.</param>
	static CarenResult CreateGeometryShaderWithStreamOutput
	(
		ID3D11Device* Param_MyPointerWork,
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
	);

	/// <summary>
	/// (CreateHullShader) - Crie um sombreador de casco.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_Out_HullShader">Recebe a interface do Hull Shader.</param>
	static CarenResult CreateHullShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		ICarenD3D11ClassLinkage^ Param_Linkage,
		[Out] ICarenD3D11HullShader^% Param_Out_HullShader
	);

	/// <summary>
	/// (CreateInputLayout) - Crie um objeto de entrada-layout para descrever os dados do buffer de entrada para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_ArrayTiposDadosEntrada">Uma matriz de tipos de dados de entrada do estágio de entrada-montador; cada tipo é descrito por uma descrição do elemento</param>
	/// <param name="Param_CountElementos">O número de tipos de dados de entrada na matriz de elementos de entrada.</param>
	/// <param name="Param_ShaderByteCode">Um ponteiro para o shader compilado. O código compilado de sombreador contém uma assinatura de entrada que é validada contra a matriz de elementos.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Out_InputLayout">Recebe a interface do Input Layout.</param>
	static CarenResult CreateInputLayout(
		ID3D11Device* Param_MyPointerWork,
		cli::array<Estruturas::CA_D3D11_INPUT_ELEMENT_DESC^>^ Param_ArrayTiposDadosEntrada,
		UInt32 Param_CountElementos,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout
	);

	/// <summary>
	/// (CreatePixelShader) - Crie um sombreador de pixel.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_PixelShader retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_PixelShader">Recebe a interface do Hull Shader.</param>
	static CarenResult CreatePixelShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		ICarenD3D11ClassLinkage^ Param_Linkage,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11PixelShader^% Param_Out_PixelShader);

	/// <summary>
	/// (CreatePredicate) - Cria um predicado.
	/// </summary>
	/// <param name="Param_DescPredicado">Ponteiro para uma descrição de consulta onde o tipo de consulta deve ser uma D3D11_QUERY_SO_OVERFLOW_PREDICATE ou D3D11_QUERY_OCCLUSION_PREDICATE</param>
	/// <param name="Param_Out_Predicado">Recebe a interface do Predicado criado.</param>
	static CarenResult CreatePredicate(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_QUERY_DESC^% Param_DescPredicado,
		[Out] ICarenD3D11Predicate^% Param_Out_Predicado);

	/// <summary>
	/// (CreateQuery) - Essa interface encapsula métodos para consultar informações da GPU.
	/// </summary>
	/// <param name="Param_DescQuery">Uma descrição da interface de consulta a ser criada.</param>
	/// <param name="Param_Out_Query">Recebe a interface de consulta criada.</param>
	static CarenResult CreateQuery(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_QUERY_DESC^% Param_DescQuery,
		[Out] ICarenD3D11Query^% Param_Out_Query);

	/// <summary>
	/// (CreateRasterizerState) - Crie um objeto de estado rasterizador que informa o rasterizador de palco como se comportar.
	/// </summary>
	/// <param name="Param_DescRasterizador">Uma estrutura com a descrição do estado do rasterizador.</param>
	/// <param name="Param_Out_Rasterizador">Recebe a interface de Rasterização criada.</param>
	static CarenResult CreateRasterizerState(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_DescRasterizador,
		[Out] ICarenD3D11RasterizerState^% Param_Out_Rasterizador);

	/// <summary>
	/// (CreateRenderTargetView) - Cria uma exibição de destino de processamento para acesso a dados de recurso.
	/// </summary>
	/// <param name="Param_Resource">Um ponteiro para interface ID3D11Resource que representa um destino de processamento. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_RENDER_TARGET .</param>
	/// <param name="Param_DescRender">Uma estrutura D3D11_RENDER_TARGET_VIEW_DESC que representa uma descrição do modo de exibição render-alvo. Defina este parâmetro como NULL para criar uma exibição 
	/// que acessa todos os sub-recursos mipmap nível 0.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ViewRender retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_ViewRender">Recebe a interface do visualizador de render.</param>
	static CarenResult CreateRenderTargetView(
		ID3D11Device* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Resource,
		Estruturas::CA_D3D11_RENDER_TARGET_VIEW_DESC^ Param_DescRender,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11RenderTargetView^% Param_Out_ViewRender);

	/// <summary>
	/// (CreateSamplerState) - Crie um objeto de sampler-estado que encapsula as informações de amostragem para uma textura.
	/// </summary>
	/// <param name="Param_DescSampler">Uma descrição do estado do amostrador</param>
	/// <param name="Param_Out_SamplerState">Recebe a interface do Sampler Sate.</param>
	static CarenResult CreateSamplerState(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_SAMPLER_DESC^% Param_DescSampler,
		[Out] ICarenD3D11SamplerState^% Param_Out_SamplerState);

	/// <summary>
	/// (CreateShaderResourceView) - Crie uma exibição de sombreador-recurso para acessar dados em um recurso.
	/// </summary>
	/// <param name="Param_Recurso">Ponteiro para o recurso que irá servir como entrada para um sombreador. Este recurso deve ter sido criado com o sinalizador D3D11_BIND_SHADER_RESOURCE .</param>
	/// <param name="Param_DescExbi">Ponteiro para uma descrição de exibição de sombreador-recurso (veja D3D11_SHADER_RESOURCE_VIEW_DESC). Defina este parâmetro como NULL para criar uma 
	/// exibição que acessa o recurso inteiro (usando o recurso foi criado com o formato).</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_ShaderView retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_ShaderView">Recebe a interface para o visualizador de Shader.</param>
	static CarenResult CreateShaderResourceView(
		ID3D11Device* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		Estruturas::CA_D3D11_SHADER_RESOURCE_VIEW_DESC^% Param_DescExbi,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11ShaderResourceView^% Param_Out_ShaderView);

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
	static CarenResult CreateTexture1D(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_TEXTURE1D_DESC^% Param_DescTextura1D,
		cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
		UInt32 Param_TamanhoArraySubRecursos,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11Texture1D^% Param_Out_Textura1D);

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
	static CarenResult CreateTexture2D(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_TEXTURE2D_DESC^% Param_DescTextura2D,
		cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
		UInt32 Param_TamanhoArraySubRecursos,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11Texture2D^% Param_Out_Textura2D);

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
	static CarenResult CreateTexture3D(
		ID3D11Device* Param_MyPointerWork,
		Estruturas::CA_D3D11_TEXTURE3D_DESC^% Param_DescTextura3D,
		cli::array<Estruturas::CA_D3D11_SUBRESOURCE_DATA^>^ Param_ArrayDescSubRecursos,
		UInt32 Param_TamanhoArraySubRecursos,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11Texture3D^% Param_Out_Textura3D);

	/// <summary>
	/// (CreateUnorderedAccessView) - Cria uma visão para acessar um recurso de acesso não ordenada.
	/// </summary>
	/// <param name="Param_Recurso">Uma interface que representa um recurso que servirá como entrada para um sombreador.</param>
	/// <param name="Param_DescSombreador">Uma estrutura(D3D11_UNORDERED_ACCESS_VIEW_DESC) que contém uma descrição de exibição de recurso do sombreador. Configure este parâmetro como NULO para criar uma 
	/// visualização que acesse todo o recurso (usando o formato com o qual o recurso foi criado). </param>
	/// <param name="Param_Out_Interface">Recebe a interface do Recurso de acesso não ordenado.</param>
	static CarenResult CreateUnorderedAccessView(
		ID3D11Device* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		Estruturas::CA_D3D11_UNORDERED_ACCESS_VIEW_DESC^% Param_DescSombreador,
		[Out] ICarenD3D11UnorderedAccessView^% Param_Out_Interface);

	/// <summary>
	/// (CreateVertexShader) - Crie um objeto shader de vértice de um sombreador compilado.
	/// </summary>
	/// <param name="Param_ShaderByteCode">Um ponteiro para um sombreador compilado.</param>
	/// <param name="Param_TamanhoByteCode">Tamanho do sombreador compilado.</param>
	/// <param name="Param_Linkage">Um ponteiro para um enlace de classe interface. O valor pode ser nulo.</param>
	/// <param name="Param_ValidarParametros">Defina True para validar os outros parmetros. Param_Out_VertexShaderInterface retorna NULL se esse paramêtro for verdadeiro.</param>
	/// <param name="Param_Out_VertexShader">Recebe a interface do Vertex Shader.</param>
	static CarenResult CreateVertexShader(
		ID3D11Device* Param_MyPointerWork,
		ICaren^ Param_ShaderByteCode,
		UInt64 Param_TamanhoByteCode,
		ICarenD3D11ClassLinkage^ Param_Linkage,
		Boolean Param_ValidarParametros,
		[Out] ICarenD3D11VertexShader^% Param_Out_VertexShader);

	/// <summary>
	/// (GetCreationFlags) - Se os sinalizadores usados durante a chamada para criar o dispositivo com D3D11CreateDevice.
	/// </summary>
	/// <param name="Param_Out_Flags">Recebe um flags de bit a bits da enumerção (CA_D3D11_CREATE_DEVICE_FLAG) que contém o modo de criaçã do dispositivo.</param>
	static CarenResult GetCreationFlags(
		ID3D11Device* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D11_CREATE_DEVICE_FLAG% Param_Out_Flags);

	/// <summary>
	/// (GetDeviceRemovedReason) - A razão por que o dispositivo foi removido. Esse método retorna um (ResultCode) informando o motivo.
	/// </summary>
	static CarenResult GetDeviceRemovedReason(ID3D11Device* Param_MyPointerWork);

	/// <summary>
	/// (GetExceptionMode) - Obter os sinalizadores de modo de exceção.
	/// </summary>
	/// <param name="Param_Out_Except">Um valor que contém um ou mais sinalizadores de exceção; Cada sinalizador especifica uma condição que fará com que uma exceção seja levantada. Os sinalizadores estão 
	/// listados em D3D11_RAISE_FLAG. Um valor padrão de 0 significa que não há sinalizadores.</param>
	static CarenResult GetExceptionMode(
		ID3D11Device* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D11_RAISE_FLAG% Param_Out_Except);

	/// <summary>
	/// (GetFeatureLevel) - Obtém o nível de funcionalidade de dispositivo de hardware.
	/// </summary>
	/// <param name="Param_Out_NivelRecurso">Recebe um flag de bits a bits de um ou mais sinlizadores de niveis de recuso do dispositivo de hardware.</param>
	static CarenResult GetFeatureLevel(
		ID3D11Device* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D_FEATURE_LEVEL% Param_Out_NivelRecurso);

	/// <summary>
	/// (GetImmediateContext) - Obtém um contexto imediato, que pode reproduzir listas de comando.
	/// </summary>
	/// <param name="Param_Out_ImediateContextInterface">Recebe a interface do contexto do dispositivo.</param>
	static CarenResult GetImmediateContext(
		ID3D11Device* Param_MyPointerWork, 
		[Out] ICarenD3D11DeviceContext^% Param_Out_ImediateContextInterface);

	/// <summary>
	/// (GetPrivateData) - Obtém os dados definidos pelo aplicativo de um dispositivo.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado ao buffer.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer de saida.</param>
	/// <param name="Param_Out_TamanhoBufferSaida">Recebe o tamanho que total do buffer no parametro (Param_Out_Buffer).</param>
	/// <param name="Param_Out_Buffer">Recebe a interface que gerencia o buffer retornado.</param>
	static CarenResult GetPrivateData(
		ID3D11Device* Param_MyPointerWork,
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		[Out] UInt32% Param_Out_TamanhoBufferSaida,
		[Out] ICarenBuffer^% Param_Out_Buffer);

	/// <summary>
	/// (OpenSharedResource) - Dar um dispositivo de acesso a um recurso compartilhado, criado em um dispositivo diferente.
	/// </summary>
	/// <param name="Param_Handle">Um identificador de recurso.</param>
	/// <param name="Param_GuidInterface">O identificador globalmente exclusivo (GUID) para a interface do recurso.</param>
	/// <param name="Param_Out_InterfaceSolicitada">Recebe a interface do recurso que foi ganhado acesso. O usuário deve criar a interfaces antes de chamar este método.</param>
	static CarenResult OpenSharedResource(
		ID3D11Device* Param_MyPointerWork,
		IntPtr Param_Handle,
		String^ Param_GuidInterface,
		ICaren^ Param_Out_InterfaceSolicitada);

	/// <summary>
	/// (SetExceptionMode) - Obter os sinalizadores de modo de exceção.
	/// </summary>
	/// <param name="Param_RaiseFlags">Os flags de modo de exceção.</param>
	static CarenResult SetExceptionMode(
		ID3D11Device* Param_MyPointerWork, 
		UInt32 Param_RaiseFlags);

	/// <summary>
	/// (SetPrivateData) - Define os dados para um dispositivo e associa esses dados a um guid.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado ao buffer.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer de entrada.</param>
	/// <param name="Param_Buffer">Ponteiro para os dados sejam armazenados com este dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer dados anteriormente associados com o 
	/// guid serão destruídos.</param>
	static CarenResult SetPrivateData(
		ID3D11Device* Param_MyPointerWork,
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// (SetPrivateDataInterface) - Associar uma interface IUnknown-derivado desta criança de dispositivo e associar essa interface com um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">O Guid associado a interface a ser definida.</param>
	/// <param name="Param_Interface">Ponteiro para uma interface derivada de IUnknown para ser associado ao filho do dispositivo.</param>
	static CarenResult SetPrivateDataInterface(
		ID3D11Device* Param_MyPointerWork,
		String^ Param_Guid,
		ICaren^ Param_Interface);
};

/// <summary>
/// 
/// </summary>
class Shared_D3D11DeviceChild
{

	//Métodos da interface ICarenD3D11DeviceChild
public:
	/// <summary>
	/// (GetDevice) - Obtém um ponteiro para o dispositivo que criou essa interface.
	/// </summary>
	/// <param name="Param_Out_DispositivoD3D11">Retorna o dispositivo D3D11 que criou essa interface. A interface retornada é uma (ICarenD3D11Device). Utilize a classe (CastInterface)
	/// para transforma em sua interface original.</param>
	static CarenResult GetDevice(
		ID3D11DeviceChild* Param_MyPointerWork, 
		ICaren^ Param_Out_DispositivoD3D11);

	/// <summary>
	/// (GetPrivateData) - 	Obtém os dados definidos pelo aplicativo de um filho de dispositivo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com os dados.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer que será retornado.</param>
	/// <param name="Param_Out_TamanhoBufferSaida">O valor real do buffer retornado pelo parametro (Param_Out_BufferDados).</param>
	/// <param name="Param_Out_BufferDados">Um ponteiro para um buffer que (GetPrivateData) preenche com dados da criança dispositivo se (Param_TamanhoBuffer) aponta para um valor 
	/// que especifica um buffer grande o suficiente para armazenar os dados.</param>
	static CarenResult GetPrivateData(
		ID3D11DeviceChild* Param_MyPointerWork,
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		[Out] UInt32% Param_Out_TamanhoBufferSaida,
		[Out] ICarenBuffer^% Param_Out_BufferDados);

	/// <summary>
	/// (SetPrivateData) - Define dados definidos pelo aplicativo para um filho de dispositivo e associe esses dados a um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com os dados.</param>
	/// <param name="Param_TamanhoBuffer">O tamanho do buffer no parametro (Param_Buffer).</param>
	/// <param name="Param_Buffer">Ponteiro para os dados a serem armazenados com essa criança de dispositivo. Se Param_Buffer é NULO, Param_TamanhoBuffer também deve ser 0, e quaisquer 
	/// dados anteriormente associados com o especificado GUID serão destruídos.</param>
	static CarenResult SetPrivateData(
		ID3D11DeviceChild* Param_MyPointerWork,
		String^ Param_Guid,
		UInt32 Param_TamanhoBuffer,
		ICarenBuffer^ Param_Buffer);

	/// <summary>
	/// (SetPrivateDataInterface) - Associa uma interface derivada de IUnknown a esse filho de dispositivo e associe essa interface a um guid definido pelo aplicativo.
	/// </summary>
	/// <param name="Param_Guid">GUID associado com a interface a ser definida.</param>
	/// <param name="Param_Interface">Ponteiro para uma interface IUnknown-derivado a ser associado com a criança do dispositivo.</param>
	static CarenResult SetPrivateDataInterface(
		ID3D11DeviceChild* Param_MyPointerWork,
		String^ Param_Guid,
		ICaren^ Param_Interface);
};

/// <summary>
/// 
/// </summary>
class Shared_D3D11View
{
public:
	/// <summary>
	/// (GetResource) - Obtém o recurso que é acessado por meio dessa visualização.
	/// </summary>
	/// <param name="Param_Out_Recurso">Retorna um ponteiro para o recurso que é acessado através desta vista.</param>
	static CarenResult GetResource(ID3D11View* Poaram_MyPointerWork, [Out] ICarenD3D11Resource^% Param_Out_Recurso);
};

/// <summary>
/// 
/// </summary>
class Shared_D3D11RasterizerState
{

	//Métodos da interface(ICarenD3D11RasterizerState2)
public:
	/// <summary>
	/// (GetDesc2) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
	/// </summary>
	/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
	static CarenResult GetDesc2(
		ID3D11RasterizerState2* Param_MyPointerWork, 
		[Out] Estruturas::CA_D3D11_RASTERIZER_DESC2^% Param_Out_DescRasterizador);


	//Métodos da interface ICarenD3D11RasterizerState1
public:
	/// <summary>
	/// (GetDesc1) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
	/// </summary>
	/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
	static CarenResult GetDesc1(
		ID3D11RasterizerState1* Param_MyPointerWork, 
		[Out] Estruturas::CA_D3D11_RASTERIZER_DESC1^% Param_Out_DescRasterizador);



	//Métodos da interface ICarenD3D11RasterizerState
public:
	/// <summary>
	/// (GetDesc) - Obtém a descrição para o rasterizador de estado que você usou para criar o objeto rasterizador-estado.
	/// </summary>
	/// <param name="Param_Out_DescRasterizador">Retorna uma estrutura que contém a descrição do rasterizador de estado.</param>
	static CarenResult GetDesc(
		ID3D11RasterizerState* Param_MyPointerWork, 
		[Out] Estruturas::CA_D3D11_RASTERIZER_DESC^% Param_Out_DescRasterizador);

};

/// <summary>
/// 
/// </summary>
class Shared_Direct3D11DeviceContext
{
	///////////////////////////////////////////////////////
	//A parti daqui vai conter os métodos das interfaces.//
	///////////////////////////////////////////////////////


	//Métodos da interface(ICarenD3D11DeviceContext4)
public:
	/// <summary>
	/// (Signal) - Atualiza uma Fence para um valor especificado depois que todos os trabalhos anteriores terminarem.
	/// Este método só se aplica a contextos de modo imediato.
	/// </summary>
	/// <param name="Param_Fence">Um ponteiro para a interface do objeto ICarenD3D11Fence.</param>
	/// <param name="Param_Valor">Um valor para definir o Fence.</param>
	static CarenResult Signal(ID3D11DeviceContext4* Param_MyPointerWork, ICarenD3D11Fence^ Param_Fence, UInt64 Param_Valor);

	/// <summary>
	/// (Wait) - Espera até que uma Fence especificada atinja ou exceda o valor especificado antes que o trabalho futuro possa começar.
	/// Este método só se aplica a contextos de modo imediato.
	/// </summary>
	/// <param name="Param_Fence">Um ponteiro para a interface do objeto ICarenD3D11Fence.</param>
	/// <param name="Param_Valor">O valor que o contexto do dispositivo está esperando a cerca alcançar ou exceder. Então, quando o ICarenD3D11Fence::ObterValorCompletado
	/// é maior do que ou igual ao (Param_Valor), a espera é encerrada.</param>
	static CarenResult Wait(ID3D11DeviceContext4* Param_MyPointerWork, ICarenD3D11Fence^ Param_Fence, UInt64 Param_Valor);




	//Métodos da interface(ICarenD3D11DeviceContext3)
public:
	/// <summary>
	/// (Flush1) - 	Envia comandos enfileirados no buffer de comando para a unidade de processamento gráfico (GPU), com um tipo de contexto especificado e uma alça opcional 
	/// de eventos para criar uma consulta de eventos.
	/// </summary>
	/// <param name="Param_TypeContexto">Um valor CA_D3D11_CONTEXT_TYPE que especifica o contexto em que ocorre uma consulta, como uma fila de comando 3D, fila de computação 3D, 
	/// fila de cópia 3D, vídeo ou imagem.</param>
	/// <param name="Param_Handle">Uma Handle opcional de eventos. Quando especificado, este método cria uma consulta de eventos. Flush1 opera de forma assíncrona, portanto, 
	/// pode retornar antes ou depois que a GPU terminar executando os comandos gráficos enfileirados, que eventualmente serão concluídos.</param>
	static CarenResult Flush1(ID3D11DeviceContext3* Param_MyPointerWork, CA_D3D11_CONTEXT_TYPE Param_TypeContexto, ICarenEvent^ Param_Handle);

	/// <summary>
	/// (GetHardwareProtectionState) - Obtém um valor que define se a proteção de hardware está ativada.
	/// </summary>
	/// <param name="Param_Out_ProtecaoHardwareHabilitada">Retorna TRUE se a proteção de hardware estiver habilitada, caso contrario, FALSE.</param>
	static CarenResult GetHardwareProtectionState(ID3D11DeviceContext3* Param_MyPointerWork, [Out] bool% Param_Out_ProtecaoHardwareHabilitada);

	/// <summary>
	/// (SetHardwareProtectionState) - Define o estado de proteção de hardware.
	/// </summary>
	/// <param name="Param_EstadoProtecao">Um valor booleano que define o estado da proteção de Hardware.</param>
	static CarenResult SetHardwareProtectionState(ID3D11DeviceContext3* Param_MyPointerWork, bool Param_EstadoProtecao);



	//Métodos da interface(ICarenD3D11DeviceContext2)
public:
	/// <summary>
	/// (BeginEventInt) - Permite que as aplicações anotem o início de uma gama de comandos gráficos,  fim de fornecer mais contexto ao que a GPU está executando. Quando o registro ETW (ou uma ferramenta suportada) é ativado, um marcador adicional está correlacionado entre os cronogramas da CPU e GPU.
	/// </summary>
	/// <param name="Param_Label">Uma sequência opcional que será registrada na ETW quando o registro ETW estiver ativo. Se '#d' aparecer na sequência, ele será substituído pelo valor do parâmetro Param_Data semelhante à forma como o printf funciona.</param>
	/// <param name="Param_Data">Um valor de dados assinado que será registrado na ETW quando o registro ETW estiver ativo.</param>
	static CarenResult BeginEventInt(
		ID3D11DeviceContext2* Param_MyPointerWork,
		String^ Param_Label,
		Int32 Param_Data);

	/// <summary>
	/// (CopyTileMappings) - Copia mapeamentos de um recurso de ladrilhos de origem para um recurso de revestimento de destino.
	/// </summary>
	/// <param name="Param_DestinoRecursoTiled">Um ponteiro para o recurso de Tiled de destino.</param>
	/// <param name="Param_DestinoCoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tiles de destino.</param>
	/// <param name="Param_OrigemRecursoTiled">Um ponteiro para o recurso de Tiled de origem.</param>
	/// <param name="Param_OrigemCoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tiles de origem.</param>
	/// <param name="Param_TamanhoRegiaoTiled">Uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região de Tiles.</param>
	/// <param name="Param_Flags">Uma combinação de valores D3D11_TILE_MAPPING_FLAGS que são combinados usando uma operação ou bitwise. O único valor válido é D3D11_TILE_MAPPING_NO_OVERWRITE,o que indica que 
	/// os comandos anteriormente enviados ao dispositivo que ainda podem estar sendo executados não fazem referência a nenhuma das regiões de Tiles que estão sendo atualizadas. O dispositivo pode então evitar 
	/// ter que lavar o trabalho anteriormente enviado para realizar a atualização de mapeamento de Tiles.</param>
	static CarenResult CopyTileMappings(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_DestinoRecursoTiled,
		CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_DestinoCoordenadasInicio,
		ICarenD3D11Resource^ Param_OrigemRecursoTiled,
		CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_OrigemCoordenadasInicio,
		CA_D3D11_TILE_REGION_SIZE^ Param_TamanhoRegiaoTiled,
		CA_D3D11_TILE_MAPPING_FLAGS Param_Flags);

	/// <summary>
	/// (CopyTiles) - Copia Tiles do buffer ao recurso de ladrilhos ou vice-versa.
	/// </summary>
	/// <param name="Param_RecursoTiled">Um ponteiro para o recurso da Tile.</param>
	/// <param name="Param_CoordenadasInicio">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso de Tile.</param>
	/// <param name="Param_TamanhoRegiaoTile">Uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região do Tile.</param>
	/// <param name="Param_Buffer">Um ponteiro para uma ICarenD3D11Buffer que representa um buffer padrão, dinâmico ou de encenação.</param>
	/// <param name="Param_BufferStartOffsetInBytes">O Offset, em bytes no (Param_Buffer) para iniciar a operação.</param>
	/// <param name="Param_CopyFlags">Uma combinação de valores CA_D3D11_TILE_COPY_FLAG que são combinados usando uma operação OU bitwise e que identifica como copiar Tiles.</param>
	static CarenResult CopyTiles(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoTiled,
		CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_CoordenadasInicio,
		CA_D3D11_TILE_REGION_SIZE^ Param_TamanhoRegiaoTile,
		ICarenD3D11Buffer^ Param_Buffer,
		UInt64 Param_BufferStartOffsetInBytes,
		CA_D3D11_TILE_COPY_FLAG Param_CopyFlags);

	/// <summary>
	/// (EndEvent) - Permite que as aplicações anotem o fim de uma gama de comandos gráficos.
	/// </summary>
	static CarenResult EndEvent(ID3D11DeviceContext2* Param_MyPointerWork);

	/// <summary>
	/// (IsAnnotationEnabled) - Permite que os aplicativos determinem quando uma solicitação de captura ou perfil está ativada.
	/// </summary>
	/// <param name="Param_Out_Estado">Retorna TRUE se a captura ou o perfil for ativado e FALSO de outra forma.</param>
	static CarenResult IsAnnotationEnabled(ID3D11DeviceContext2* Param_MyPointerWork, [Out] bool% Param_Out_Estado);

	/// <summary>
	/// (ResizeTilePool) - Redimensiona uma Tile Pool.
	/// </summary>
	/// <param name="Param_TilePool">Um ponteiro para a interface ICarenD3D11Buffer que contém o Tile a ser redimensionado.</param>
	/// <param name="Param_NovoSizeBytes">O novo tamanho em bytes do Pool de Tiles. O tamanho deve ser um múltiplo de 64 KB ou 0.</param>
	static CarenResult ResizeTilePool(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11Buffer^ Param_TilePool,
		UInt64 Param_NovoSizeBytes);

	/// <summary>
	/// (SetMarkerInt) - Permite que aplicativos anotem comandos gráficos.
	/// </summary>
	/// <param name="Param_Label">Uma sequência opcional que será registrada na ETW quando o registro ETW estiver ativo. Se '#d' aparecer na sequência, ele será substituído pelo valor do parâmetro Param_Data semelhante à forma como o printf funciona.</param>
	/// <param name="Param_Data">Um valor de dados assinado que será registrado na ETW quando o registro ETW estiver ativo.</param>
	static CarenResult SetMarkerInt(
		ID3D11DeviceContext2* Param_MyPointerWork,
		String^ Param_Label,
		Int32 Param_Data);

	/// <summary>
	/// (TiledResourceBarrier) - Especifica uma restrição de pedidos de acesso de dados entre múltiplos recursos ladrilhos.
	/// </summary>
	/// <param name="Param_TiledResourceOrViewAccessBeforeBarrier">Um ponteiro para uma ICarenD3D11Resource ou ICarenD3D11View para um recurso que foi criado com a bandeira D3D11_RESOURCE_MISC_TILED. As operações de 
	/// acesso neste objeto devem ser concluídas antes das operações de acesso no objeto que especifica o (Param_TiledResourceOrViewAccessAfterBarrier).</param>
	/// <param name="Param_TiledResourceOrViewAccessAfterBarrier">Um ponteiro para uma ICarenD3D11Resource ou ICarenD3D11View para um recurso que foi criado com a bandeira D3D11_RESOURCE_MISC_TILED. As operações de acesso neste objeto devem começar após as operações de acesso no objeto que especifica o PTiledResourceOrViewAccessBeforeBarrier.</param>
	static CarenResult TiledResourceBarrier(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11DeviceChild^ Param_TiledResourceOrViewAccessBeforeBarrier,
		ICarenD3D11DeviceChild^ Param_TiledResourceOrViewAccessAfterBarrier);

	/// <summary>
	/// (UpdateTileMappings) - Atualiza mapeamentos de locais de ladrilhos em recursos ladrilhos para locais de memória em um pool de Tiles.
	/// </summary>
	/// <param name="Param_RecursoTiled">Um ponteiro para o recurso de Tiles.</param>
	/// <param name="Param_QuantidadeReigoesRecursoTiled">O número de regiões de recursos de Tiles.</param>
	/// <param name="Param_MatrizCoordernadasInicioRecursoTiled">Uma matriz de estruturas CA_D3D11_TILED_RESOURCE_COORDINATE que descrevem as coordenadas iniciais das regiões de recursos ladrilhos. O parâmetro 
	/// (Param_QuantidadeReigoesRecursoTiled) especifica o número de estruturas CA_D3D11_TILED_RESOURCE_COORDINATE na matriz.</param>
	/// <param name="Param_MatrizSizeReigoesRecursoTiled">Uma matriz de estruturas CA_D3D11_TILE_REGION_SIZE que descrevem os tamanhos das regiões de recursos tiles. O parâmetro (Param_QuantidadeReigoesRecursoTiled) 
	/// especifica o número de estruturas CA_D3D11_TILE_REGION_SIZE na matriz.</param>
	/// <param name="Param_TilePool">Um ponteiro para um Pool de Tiles.</param>
	/// <param name="Param_NumeroRanges">O número de faixas de Tiles.</param>
	/// <param name="Param_MatrizFlagsRange">Uma matriz de CA_D3D11_TILE_RANGE_FLAG que descrevem cada faixa de Tile-Pool. O parâmetro (Param_NumeroRanges) especifica o número de valores na matriz.</param>
	/// <param name="Param_MatrizOffsetStartTiledPool">Uma série de deslocamentos no pool de tiles. São compensações de tiles baseadas em 0, contando em tiles (não bytes).</param>
	/// <param name="Param_MatrizQuantidadeRangesTile">Uma matriz de valores que especificam o número de tiles em cada faixa de Tile-Pool. O parâmetro (Param_NumeroRanges) especifica o número de valores na matriz.</param>
	/// <param name="Param_Flags">Uma combinação de valores CA_D3D11_TILE_MAPPING_FLAGS que são combinados usando uma operação ou bitwise.</param>
	static CarenResult UpdateTileMappings(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoTiled,
		UInt32 Param_QuantidadeReigoesRecursoTiled,
		cli::array<CA_D3D11_TILED_RESOURCE_COORDINATE^>^ Param_MatrizCoordernadasInicioRecursoTiled,
		cli::array<CA_D3D11_TILE_REGION_SIZE^>^ Param_MatrizSizeReigoesRecursoTiled,
		ICarenD3D11Buffer^ Param_TilePool,
		UInt32 Param_NumeroRanges,
		cli::array<CA_D3D11_TILE_RANGE_FLAG>^ Param_MatrizFlagsRange,
		cli::array<UInt32>^ Param_MatrizOffsetStartTiledPool,
		cli::array<UInt32>^ Param_MatrizQuantidadeRangesTile,
		CA_D3D11_TILE_MAPPING_FLAGS Param_Flags);

	/// <summary>
	/// (UpdateTiles) - Atualiza as Tiles copiando da memória do aplicativo para o recurso de ladrilhos.
	/// </summary>
	/// <param name="Param_DestRecursoTiled">Um ponteiro para o recurso tiled a ser atualizado.</param>
	/// <param name="Param_CoordernadasInicioRecursoTiled">Uma estrutura CA_D3D11_TILED_RESOURCE_COORDINATE que descreve as coordenadas iniciais do recurso Tiled.</param>
	/// <param name="Param_SizeReigoesRecursoTiled">uma estrutura CA_D3D11_TILE_REGION_SIZE que descreve o tamanho da região do Tile.</param>
	/// <param name="Param_OrigemDadosTile">Um ponteiro para a memória que contém os dados do Tile de origem que o UpdateTiles usa para atualizar o recurso de Tiles.</param>
	/// <param name="Param_CopyFlags">Uma combinação de valores D3D11_TILE_COPY_FLAG que são combinados usando uma operação ou bitwise. O único valor válido é 
	/// D3D11_TILE_COPY_NO_OVERWRITE. Os outros valores não são significativos aqui, embora por definição o valor D3D11_TILE_COPY_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE 
	/// é basicamente o que o UpdateTiles faz, mas fontes da memória do aplicativo.</param>
	static CarenResult UpdateTiles(
		ID3D11DeviceContext2* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_DestRecursoTiled,
		CA_D3D11_TILED_RESOURCE_COORDINATE^ Param_CoordernadasInicioRecursoTiled,
		CA_D3D11_TILE_REGION_SIZE^ Param_SizeReigoesRecursoTiled,
		ICarenBuffer^ Param_OrigemDadosTile,
		CA_D3D11_TILE_COPY_FLAG Param_CopyFlags);


	//Métodos da interface(ICarenD3D11DeviceContext1)
public:
	/// <summary>
	/// (ClearView) - Define todos os elementos em uma visão de recurso para um valor.
	/// </summary>
	/// <param name="Param_View">Um ponteiro para uma interface ICarenD3D11View que representa a visão de recurso a ser limpa.</param>
	/// <param name="Param_Cor">Um conjunto de 4 componentes(RGBA) que representa a cor para usar para limpar a visão de recurso.</param>
	/// <param name="Param_ArrayRetangulos">Um array de estruturas (CA_RECT) para os retângulos na visão de recursos para limpar. Se NULO, o (ClearView) limpa toda a superfície.</param>
	/// <param name="Param_QuantidadeItems">O número de retângulos no array (Param_ArrayRetangulos).</param>
	static CarenResult ClearView(
		ID3D11DeviceContext1* Param_MyPointerWork,
		ICarenD3D11View^ Param_View,
		cli::array<float>^ Param_Cor,
		cli::array<CA_RECT^>^ Param_ArrayRetangulos,
		UInt32 Param_QuantidadeItems);

	/// <summary>
	/// (CopySubresourceRegion1) - Copia uma região de um recurso de origem para um recurso de destino.
	/// </summary>
	/// <param name="Param_DestinoRecurso">Um ponteiro para o recurso de destino.</param>
	/// <param name="Param_IndiceSubrecrusoDestino">Índice de sub-recurso de destino.</param>
	/// <param name="Param_DestX">A coordenada X do canto superior esquerdo da região de destino.</param>
	/// <param name="Param_DestY">A coordenada Y do canto superior esquerdo da região de destino. Para um sub-recurso 1D, isto deve ser zero.</param>
	/// <param name="Param_DestZ">A coordenada Z do canto superior esquerdo da região de destino. Para um sub-recurso 1D ou 2D, isto deve ser zero.</param>
	/// <param name="Param_FonteRecurso">Um ponteiro para o recurso de fonte</param>
	/// <param name="Param_IndiceSubrecrusoFonte">Índice de sub-recurso da fonte.</param>
	/// <param name="Param_OrigemBox">Uma estrutura(CAIXA 3D) que define o sub-recurso de fonte que pode ser copiado. Se nulo, o sub-recurso fonte inteiro é copiado. A caixa deve caber dentro da fonte 
	/// de recurso.</param>
	/// <param name="Param_CopyFlags">Um valor CA_D3D11_COPY_FLAGS que especifica como realizar a operação de cópia. Se você especificar zero para nenhuma opção de cópia, CopySubresourceRegion1 se comporta como ICarenD3D11DeviceContext::CopiarSubRecursoRegiao. Para os drivers de exibição existentes que não podem processar essas bandeiras, o tempo de execução não as usa.</param>
	static CarenResult CopySubresourceRegion1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_DestinoRecurso,
		UInt32 Param_IndiceSubrecrusoDestino,
		UInt32 Param_DestX,
		UInt32 Param_DestY,
		UInt32 Param_DestZ,
		ICarenD3D11Resource^ Param_FonteRecurso,
		UInt32 Param_IndiceSubrecrusoFonte,
		Estruturas::CA_D3D11_BOX^ Param_OrigemBox,
		CA_D3D11_COPY_FLAGS Param_CopyFlags);

	/// <summary>
	/// (CSGetConstantBuffers1) - Obtém os buffers constantes que o estágio de sombreador de computação usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Recebe uma matriz com os ponteiros para os buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_MatrizBuffers) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_MatrizBuffers) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult CSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (CSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador de computação usa.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult CSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (DiscardResource) - Descarta um recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para a interface de recurso a ser dercartada. O recurso deve ter sido criado com uso D3D11_USAGE_DEFAULT ou D3D11_USAGE_DYNAMIC, 
	/// caso contrário, o tempo de execução derruba a chamada para o (DiscardResource); se a camada de depuração estiver ativada, o tempo de execução retorna uma mensagem de erro.</param>
	static CarenResult DiscardResource(ID3D11DeviceContext1* Param_MyPointerWork, ICarenD3D11Resource^ Param_Recurso);

	/// <summary>
	/// (DiscardView) - Descarta uma visão de recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
	/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
	/// retorna uma mensagem de erro.</param>
	static CarenResult DiscardView(ID3D11DeviceContext1* Param_MyPointerWork, ICarenD3D11View^ Param_Visão);

	/// <summary>
	/// (DiscardView1) - Descarta os elementos especificados em uma visão de recurso do contexto do dispositivo.
	/// </summary>
	/// <param name="Param_Visão">Um ponteiro para a interface de visão a ser descartada. O recurso que desmente a visão deve ter sido criado com uso D3D11_USAGE_DEFAULT ou 
	/// D3D11_USAGE_DYNAMIC, caso contrário, o tempo de execução derruba a chamada para o DiscardView; se a camada de depuração estiver ativada, o tempo de execução 
	/// retorna uma mensagem de erro.</param>
	/// <param name="Param_MatrizRetangulos">Uma matriz de estruturas CA_RECT para os retângulos na visão de recurso para descartar. Se NULO, o DiscardView1 descarta toda a 
	/// visualização e se comporta da mesma forma que o DiscardView.</param>
	/// <param name="Param_NumeroRetangulos">A quantidade de retangulos no array (Param_MatrizRetangulos).</param>
	static CarenResult DiscardView1(ID3D11DeviceContext1* Param_MyPointerWork, ICarenD3D11View^ Param_Visão, cli::array<CA_RECT^>^ Param_MatrizRetangulos, UInt32 Param_NumeroRetangulos);

	/// <summary>
	/// (DSGetConstantBuffers1) - Obtém os buffers constantes que o estágio de sombreador de domínio usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult DSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (DSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador de domínio usa.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult DSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (GSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do duto de sombreia de geometria usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult GSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (GSSetConstantBuffers1) - Define os buffers constantes que o estágio do duto de sombreia de geometria usa.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult GSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (HSGetConstantBuffers1) - Recebe os buffers constantes que o palco do sombreador do casco usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult HSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (HSSetConstantBuffers1) - Define os buffers constantes que o estágio de sombreador do casco do gasoduto usa.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult HSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (PSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do gasoduto shader pixel usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult PSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (PSSetConstantBuffers1) - Define os buffers constantes que o estágio do duto de sombreador de pixels usa e permite que o sombreador acesse outras partes do buffer.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult PSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);

	/// <summary>
	/// (SwapDeviceContextState) - Ativa o objeto de estado de contexto dado e altera o comportamento atual do dispositivo para Direct3D 11, Direct3D 10.1 ou Direct3D 10.
	/// </summary>
	/// <param name="Param_Estado">Um ponteiro para a interface ICarenD3DDeviceContextState para o objeto de estado de contexto que foi criado anteriormente através do método 
	/// ICarenD3D11Device1::CreateDeviceContextState. Se o SwapDeviceContextState for chamado com o (Param_Estado) definido como NULO,a chamada não tem efeito.</param>
	/// <param name="Param_Out_EstadoAnterior">Recebe um ponteiro para a interface ICarenD3DDeviceContextState com o estado do objeto anteriormente ativado.</param>
	static CarenResult SwapDeviceContextState(
		ID3D11DeviceContext1* Param_MyPointerWork,
		ICarenD3DDeviceContextState^ Param_Estado,
		[Out] ICarenD3DDeviceContextState^% Param_Out_EstadoAnterior);

	/// <summary>
	/// (UpdateSubresource1) - A CPU copia dados da memória para um subrecurso criado em memória não mappável.
	/// </summary>
	/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
	/// <param name="Param_SubrecursoDestino">Um índice baseado em zero, que identifica o sub-destino do destino.</param>
	/// <param name="Param_Caixa">Uma caixa que define a parte do sub-destino de destino para copiar os dados do recurso. Coordenadas são em bytes para buffers e em texels para texturas. Se NULO, os dados são
	/// gravados no subfonte de destino sem nenhum deslocamento. As dimensões da fonte devem caber no destino</param>
	/// <param name="Param_DadosOrigemMemoria">Um ponteiro para os dados de origem na memória.</param>
	/// <param name="Param_TamanhoLinhaOrigem">(SrcRowPitch) - O tamanho de uma linha dos dados de origem.</param>
	/// <param name="Param_TamhoFatiaProdundidade">(SrcDepthPitch) - O tamanho de uma fatia de profundidade dos dados de origem.</param>
	/// <param name="Param_CopyFlags">Um valor D3D11_COPY_FLAGS que especifica como realizar a operação de atualização. Se você especificar zero para nenhuma opção de atualização,
	/// o (UpdateSubresource1) se comporta como ICarenD3D11DeviceContext::UpdateSubresource. Para os drivers de exibição existentes que não podem processar essas bandeiras, 
	/// o tempo de execução não as usa.</param>
	static CarenResult UpdateSubresource1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoDestino,
		UInt32 Param_SubrecursoDestino,
		Estruturas::CA_D3D11_BOX^ Param_Caixa,
		ICarenBuffer^ Param_DadosOrigemMemoria,
		UInt32 Param_TamanhoLinhaOrigem,
		UInt32 Param_TamhoFatiaProdundidade,
		CA_D3D11_COPY_FLAGS Param_CopyFlags);

	/// <summary>
	/// (VSGetConstantBuffers1) - Obtém os buffers constantes que o estágio do gasoduto de shader de vértice usa.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	/// <param name="Param_Out_MatrizInicioConstante">Recebe uma matriz que recebe as compensações nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// deslocamento especifica onde, do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes 
	/// (componentes de 4*32 bits). Portanto, uma compensação de 2 indica que o início do buffer constante associado é de 32 bytes no buffer constante. O tempo de execução 
	/// define (Param_Out_MatrizInicioConstante) para NULO se os buffers não tiverem deslocamentos.</param>
	/// <param name="Param_Out_MatrizNumeroConstantes">Recebe uma matriz que recebe o número de constantes nos buffers que o (Param_Out_BuffersConstantes) especifica. Cada 
	/// número especifica o número de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação 
	/// que é especificada na matriz (Param_Out_MatrizInicioConstante). O tempo de execução define (Param_Out_MatrizNumeroConstantes) para NULO se não especificar o número de 
	/// constantes em cada buffer.</param>
	static CarenResult VSGetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizInicioConstante,
		[Out] cli::array<UInt32>^% Param_Out_MatrizNumeroConstantes);

	/// <summary>
	/// (VSSetConstantBuffers1) - Define os buffers constantes que o estágio do gasoduto de shader de vértice usa.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	/// <param name="Param_MatrizInicioConstante">Uma matriz que contém as compensações nos buffers que o (Param_MatrizBuffers) especifica. Cada deslocamento especifica onde, 
	/// do ponto de vista do sombreador, cada buffer constante começa. Cada compensação é medida em constantes sombreadas, que são 16 bytes (componentes de 4*32 bits). Portanto, 
	/// uma compensação de 16 indica que o início do buffer constante associado é de 256 bytes no buffer constante. Cada deslocamento deve ser um múltiplo de 16 constantes.</param>
	/// <param name="Param_MatrizNumeroConstantes">Uma matriz que contém o número de constantes nos buffers que o (Param_MatrizBuffers) especifica. Cada número especifica o número
	/// de constantes que estão contidas no buffer constante que o sombreador usa. Cada número de constantes parte de sua respectiva compensação que é especificada na matriz 
	/// (Param_MatrizInicioConstante). Cada número de constantes deve ser um múltiplo de 16 constantes, na faixa [0..4096].</param>
	static CarenResult VSSetConstantBuffers1(
		ID3D11DeviceContext1* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_MatrizInicioConstante,
		cli::array<UInt32>^ Param_MatrizNumeroConstantes);



	//Métodos da interface(ICarenD3D11DeviceContext)
public:
	/// <summary>
	/// (Begin) - Marca o início de uma série de comandos.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para a interface de sincronização.</param>
	static CarenResult Begin(
		ID3D11DeviceContext* Param_MyPointerWork, 
		ICarenD3D11Asynchronous^ Param_Async);

	/// <summary>
	/// (ClearDepthStencilView) - Limpa o recurso de profundidade-estêncil.
	/// </summary>
	/// <param name="Param_DepthStencil">Ponteiro para o estêncil de profundidade a ser apurados.</param>
	/// <param name="Param_ClearFlags">Identifica o tipo de dados para limpar </param>
	/// <param name="Param_Depth">Limpe o buffer de profundidade com esse valor. Este valor irá ser fixada entre 0 e 1.</param>
	/// <param name="Param_Stencil">Limpe o buffer de estêncil com esse valor.</param>
	static CarenResult ClearDepthStencilView(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11DepthStencilView^ Param_DepthStencil,
		Enumeracoes::CA_D3D11_CLEAR_FLAG Param_ClearFlags,
		float Param_Depth,
		Byte Param_Stencil);

	/// <summary>
	/// (ClearRenderTargetView) - Defina todos os elementos em um destino de processamento para um valor.
	/// </summary>
	/// <param name="Param_RenderTarget">Ponteiro para o destino de processamento.</param>
	/// <param name="Param_Cor">Uma estrutura de 4 componentes que representam a cor para preencher o destino de processamento.</param>
	static CarenResult ClearRenderTargetView(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11RenderTargetView^ Param_RenderTarget,
		Estruturas::CA_DXGI_RGBA^ Param_Cor);

	/// <summary>
	/// (ClearState) - Restaure todas as configurações padrão. 
	/// </summary>
	static CarenResult ClearState(ID3D11DeviceContext* Param_MyPointerWork);

	/// <summary>
	/// (ClearUnorderedAccessViewFloat) - Limpa um recurso de acesso não ordenada, com um valor float.
	/// Essa API funciona em FLOAT, UNORM e SNORM não ordenada acesso visualizações (UAVs), com formato de conversão de FLOAT para * norma se for caso disso. Em outros UAVs, a operação é inválida e a chamada 
	/// não atingirá o driver.
	/// </summary>
	/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
	/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
	static CarenResult ClearUnorderedAccessViewFloat(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
		cli::array<float>^ Param_Valores);

	/// <summary>
	/// (ClearUnorderedAccessViewUint) - Limpa um recurso de acesso não ordenada com valores de bit de precisão.
	/// Essa API copia o menor n bits de cada elemento da matriz para o correspondente canalizo, onde n é o número de bits no canal ith do formato de recurso (por exemplo, R8G8B8_FLOAT tem 8 bits para os 3 
	/// primeiros canais). Isto funciona em qualquer UAV com nenhuma conversão de formato. Para uma visão de buffer CRU ou estruturados, somente o primeiro valor de elemento matriz é usado.
	/// </summary>
	/// <param name="Param_UnorderedAccess">O ID3D11UnorderedAccessView para limpar.</param>
	/// <param name="Param_Valores">Valores para copiar para canais correspondentes.</param>
	static CarenResult ClearUnorderedAccessViewUint(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11UnorderedAccessView^ Param_UnorderedAccess,
		cli::array<UInt32>^ Param_Valores);

	/// <summary>
	/// (CopyResource) - Copie todo o conteúdo do recurso de fonte para o recurso de destino usando o GPU.
	/// </summary>
	/// <param name="Param_DestinoRecurso">Um ponteiro para a interface ID3D11Resource que representa o DESTINO do recurso.</param>
	/// <param name="Param_OrigemRecurso">Um ponteiro para a interface ID3D11Resource que representa a FONTE de recursos.</param>
	static CarenResult CopyResource(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_DestinoRecurso,
		ICarenD3D11Resource^ Param_OrigemRecurso);

	/// <summary>
	/// (CopyStructureCount) - Copia dados de um buffer de dados de comprimento variável a segurar.
	/// </summary>
	/// <param name="Param_DestinoBuffer">Ponteiro para ID3D11Buffer. Isso pode ser qualquer recurso de buffer que outros comandos de cópia, tais como ICarenD3D11DeviceContext::CopiarRecurso ou 
	/// ICarenD3D11DeviceContext::CopiarSubRecursoRegiao, são capazes de gravar.</param>
	/// <param name="Param_DestinoAlignedOffsetByte">Offset do início do Param_DestinoBuffer para gravar contagem de estrutura(vértice) UINT 32 bits de Param_OrigemView.</param>
	/// <param name="Param_OrigemView">Ponteiro para um ID3D11UnorderedAccessView de um recurso de Buffer estruturado criado com D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER especificado 
	/// quando o UAV foi criado. Esses tipos de recursos tem escondido os contadores foram escritos "Quantos" registros de rastreamento.</param>
	static CarenResult CopyStructureCount(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Buffer^ Param_DestinoBuffer,
		UInt32 Param_DestinoAlignedOffsetByte,
		ICarenD3D11UnorderedAccessView^ Param_OrigemView);

	/// <summary>
	/// (CopySubresourceRegion) - Copie uma região de uma fonte de recursos para um recurso de destino.
	/// </summary>
	/// <param name="Param_DestinoRecurso">Um ponteiro para o recurso de destino.</param>
	/// <param name="Param_IndiceSubrecrusoDestino">Índice de sub-recurso de destino.</param>
	/// <param name="Param_DestX">A coordenada X do canto superior esquerdo da região de destino.</param>
	/// <param name="Param_DestY">A coordenada Y do canto superior esquerdo da região de destino. Para um sub-recurso 1D, isto deve ser zero.</param>
	/// <param name="Param_DestZ">A coordenada Z do canto superior esquerdo da região de destino. Para um sub-recurso 1D ou 2D, isto deve ser zero.</param>
	/// <param name="Param_FonteRecurso">Um ponteiro para o recurso de fonte</param>
	/// <param name="Param_IndiceSubrecrusoFonte">Índice de sub-recurso da fonte.</param>
	/// <param name="Param_OrigemBox">Uma estrutura(CAIXA 3D) que define o sub-recurso de fonte que pode ser copiado. Se nulo, o sub-recurso fonte inteiro é copiado. A caixa deve caber dentro da fonte 
	/// de recurso.</param>
	static CarenResult CopySubresourceRegion(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_DestinoRecurso,
		UInt32 Param_IndiceSubrecrusoDestino,
		UInt32 Param_DestX,
		UInt32 Param_DestY,
		UInt32 Param_DestZ,
		ICarenD3D11Resource^ Param_FonteRecurso,
		UInt32 Param_IndiceSubrecrusoFonte,
		Estruturas::CA_D3D11_BOX^ Param_OrigemBox
	);

	/// <summary>
	/// (CSGetConstantBuffers) - Obtém os buffers constantes usados pelo estágio de computação do Shader(Sombreamento).
	/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar IUnknown:: Release sobre as interfaces retornadas quando eles não são mais necessários 
	/// para evitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumerosBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_BuffersConstantes">Recebe uma matriz com os ponteiros para os buffers constantes.</param>
	static CarenResult CSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumerosBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_BuffersConstantes);

	/// <summary>
	/// (CSGetSamplers) - Obtém uma variedade de interfaces de estado do amostrador desde a fase de computação-shader. 
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroSamplers">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
	/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot).</param>
	/// <param name="Param_Out_SamplersState">Recebe uma matriz com os ponteiros para os amostradores de estado(Samplers States).</param>
	static CarenResult CSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroSamplers,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_SamplersState);

	/// <summary>
	/// (CSGetShader) - Se o sombreador de computação atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_ComputeShader">Retorna uma ponteiro para a interface de Shader Compute.</param>
	/// <param name="Param_Out_ArrayClassInstance">Retorna um Array que contém ponteiros para Instâncias de Classe.</param>
	/// <param name="Param_Out_QuantidadeClass">Retorna a quantidade de itens no array do parametro (Param_Out_ArrayClassInstance).</param>
	static CarenResult CSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11ComputeShader^% Param_Out_ComputeShader,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_ArrayClassInstance,
		[Out] UInt32% Param_Out_QuantidadeClass);

	/// <summary>
	/// (CSGetShaderResources) - Obter os recursos de computação-shader.
	/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
	/// necessários para evitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
	/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizShaderRecursoSombreador">Retorna uma Matriz com ponteiros de exibição de recurso de sombreador retornado pelo Dispositivo.</param>
	static CarenResult CSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroRecursos,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizShaderRecursoSombreador);

	/// <summary>
	/// (CSGetUnorderedAccessViews) - Obtém uma matriz de pontos de vista de um recurso não-ordenado.
	/// Qualquer retornado interfaces terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
	/// necessários para evitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para retornar (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroUAVs">Número de pontos de vista para obter (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizInterfacesNaoOrdenadas">Retorna uma Matriz que contém ponteiros para as interfaces ID3D11UnorderedAccessView.</param>
	static CarenResult CSGetUnorderedAccessViews(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroUAVs,
		[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizInterfacesNaoOrdenadas);

	/// <summary>
	/// (CSSetConstantBuffers) - Define os constantes buffers usados pela fase computação-shader.
	/// O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
	/// Se o aplicativo deseja o sombreador para acessar outras partes da reserva, ele deve chamar o método CSSetConstantBuffers1 em vez disso.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	static CarenResult CSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (CSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de computação-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroSamplers">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
	/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizSamplers">Uma matriz de interfaces do amostrador de estado a serem definidas no dispositivo.</param>
	static CarenResult CSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroSamplers,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizSamplers);

	/// <summary>
	/// (CSSetShader) - Defina um sombreador de computação para o dispositivo.
	/// O número máximo de instâncias que pode ter um sombreador é 256.
	/// </summary>
	/// <param name="Param_ComputeShader">Ponteiro para um sombreador de computação. Passando NULO (DESABILITA) o sombreador para este estágio de pipeline.</param>
	/// <param name="Param_MatrizClassInstance">Um ponteiro para uma matriz que contem as interfaces de instâncias de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader 
	/// vai ser desativado. Definir Param_MatrizClassInstance para NULO se o sombreador não usa quaisquer interfaces.</param>
	/// <param name="Param_QuantidadeClassInstances">A quantidade de itens no array do parametro (Param_MatrizClassInstance).</param>
	static CarenResult CSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11ComputeShader^ Param_ComputeShader,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizClassInstance,
		UInt32 Param_QuantidadeClassInstances);

	/// <summary>
	/// (CSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de computação-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Indexar na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
	/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot).</param>
	/// <param name="Param_MatrizShaderRecursoSombreador">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
	static CarenResult CSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroRecursos,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizShaderRecursoSombreador);

	/// <summary>
	/// (CSSetUnorderedAccessViews) - Define uma matriz de pontos de vista para um recurso não-ordenada.
	/// </summary>
	/// <param name="Param_StartSlot">Índice do primeiro elemento na matriz baseada em zero para começar a configuração (varia de 0 a D3D11_1_UAV_SLOT_COUNT - 1). D3D11_1_UAV_SLOT_COUNT é definido como 64.</param>
	/// <param name="Param_NumeroUAVs">Número de pontos de vista para definir (varia de 0 a D3D11_1_UAV_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizInterfacesNaoOrdenadas">Um ponteiro para uma matriz de ponteiros de ID3D11UnorderedAccessView a ser definido pelo método.</param>
	/// <param name="Param_MatrizInitialUAVsCount">Uma matriz de acrescentar e consumir deslocamentos de reserva. Um valor de -1 indica que para manter o atual deslocamento. Quaisquer outros valores definir o 
	/// contador oculto para aquele UAV (APPENDABLE) e consumíveis. Param_MatrizInitialUAVsCount só é relevante para UAVs que foram criados com qualquer D3D11_BUFFER_UAV_FLAG_APPEND ou 
	/// D3D11_BUFFER_UAV_FLAG_COUNTER especificado quando o UAV foi criado; caso contrário, o argumento é ignorado.</param>
	static CarenResult CSSetUnorderedAccessViews(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroUAVs,
		cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizInterfacesNaoOrdenadas,
		cli::array<UInt32>^ Param_MatrizInitialUAVsCount);

	/// <summary>
	/// (Dispatch) - Execute uma lista de comando de um grupo de discussão.
	/// </summary>
	/// <param name="Param_NumeroGrupoExpedidoX">O número de grupos expedidos na direção X. NumeroGrupoExpedidoX deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
	/// <param name="Param_NumeroGrupoExpedidoY">O número de grupos expedidos na direção Y. NumeroGrupoExpedidoY deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).</param>
	/// <param name="Param_NumeroGrupoExpedidoZ">O número de grupos expedidos na direção Z. NumeroGrupoExpedidoZ deve ser menor ou igual a D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535). 
	/// Em nível de recurso 10 o valor para NumeroGrupoExpedidoZ deve ser 1.</param>
	static CarenResult Dispatch(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroGrupoExpedidoX,
		UInt32 Param_NumeroGrupoExpedidoY,
		UInt32 Param_NumeroGrupoExpedidoZ);

	/// <summary>
	/// (DispatchIndirect) - Execute uma lista de comando por um ou mais grupos de discussão.
	/// Você chamar este método para executar comandos em um (Compute Shader).
	/// </summary>
	/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que deve ser carregado com os dados que corresponde à lista de argumento para ICarenD3D11DeviceContext::Dispatch.</param>
	/// <param name="Param_AlinhamentoBytesOffsetForArgs">Um deslocamento de byte alinhado entre o início do buffer e os argumentos.</param>
	static CarenResult DispatchIndirect(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Buffer^ Param_BufferForArgs,
		UInt32 Param_AlinhamentoBytesOffsetForArgs);

	/// <summary>
	/// (Draw) - Desenhe não-indexados, instância não primitivos.
	/// O Draw envia trabalhos para o pipeline de renderização. Os dados de vértice para uma chamada de desenho normalmente vêm de um buffer de vértice que está vinculado ao pipeline. Mesmo sem qualquer buffer 
	/// de vértices vinculado ao pipeline, você pode gerar seus próprios dados de vértice em seu sombreador de vértice usando a semântica do valor do sistema SV_VertexID para determinar o vértice atual que o 
	/// tempo de execução está processando.
	/// </summary>
	/// <param name="Param_NumeroVertices">Número de vértices para desenhar.</param>
	/// <param name="Param_LocalizacaoVertice">Índice do primeiro vértice, que é geralmente um deslocamento em um buffer de vértice.</param>
	static CarenResult Draw(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroVertices,
		UInt32 Param_LocalizacaoVertice);

	/// <summary>
	/// (DrawAuto) - Desenhe a geometria de um tamanho desconhecido.
	/// Uma API de desenho envia trabalho para o pipeline de renderização. Esta API submete o trabalho de um tamanho desconhecido que foi processado pelos estágios montador de entrada, sombreador de vértice e 
	/// fluxo-saída; o trabalho pode ou não ter passado pelo estágio de sombreamento de geometria.
	/// </summary>
	static CarenResult DrawAuto(ID3D11DeviceContext* Param_MyPointerWork);

	/// <summary>
	/// (DrawIndexed) - Sorteio indexado, não-instanced primitivos.
	/// Se a soma dos dois índices é negativa, o resultado da chamada de função é indefinido.
	/// </summary>
	/// <param name="Param_NumeroIndices">Número de índices para desenhar.</param>
	/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
	/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
	static CarenResult DrawIndexed(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroIndices,
		UInt32 Param_StartIndexLocalizacao,
		Int32 Param_BaseVerticeLocalizacao);

	/// <summary>
	/// (DrawIndexedInstanced) - Desenhe indexados, instanciados primitivos.
	/// </summary>
	/// <param name="Param_QuantidadeIndicesPorInstancia">Número de índices de ler o buffer de índice para cada instância.</param>
	/// <param name="Param_QuantidadeInstancias">Número de instâncias para desenhar.</param>
	/// <param name="Param_StartIndexLocalizacao">A localização do índice primeiro ler pela GPU do buffer do índice.</param>
	/// <param name="Param_BaseVerticeLocalizacao">Um valor acrescentado para cada índice antes de ler um vértice de buffer vértice.</param>
	/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>
	static CarenResult DrawIndexedInstanced(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_QuantidadeIndicesPorInstancia,
		UInt32 Param_QuantidadeInstancias,
		UInt32 Param_StartIndexLocalizacao,
		Int32 Param_BaseVerticeLocalizacao,
		UInt32 Param_StartInstanciaLocalizacao);

	/// <summary>
	/// (DrawIndexedInstancedIndirect) - Desenhe primitivos indexados, instanciado, gerado pelo GPU.
	/// </summary>
	/// <param name="Param_BufferForArgs">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
	/// <param name="Param_AlinhamentoBytesOffsetForArgs">Deslocamento em Param_BufferForArgs para o início da GPU gerado primitivos.</param>
	static CarenResult DrawIndexedInstancedIndirect(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Buffer^ Param_BufferForArgs,
		UInt32 Param_AlinhamentoBytesOffsetForArgs);

	/// <summary>
	/// (DrawInstanced) - Desenhe não-indexados, instanciado primitivos.
	/// Instância pode prolongar o desempenho, reutilizando a mesma geometria para desenhar vários objetos em uma cena. Um exemplo de criação de instância pode ser desenhar o mesmo objeto com posições 
	/// diferentes e cores.
	/// </summary>
	/// <param name="Param_QuantidadeVerticiesPorInstancia">Número de vértices para desenhar.</param>
	/// <param name="Param_QuantidadeInstancias">Número de instâncias para desenhar.</param>
	/// <param name="Param_StartVerticeLocalizacao">Índice do primeiro vértice.</param>
	/// <param name="Param_StartInstanciaLocalizacao">Um valor acrescentado para cada índice antes de ler dados por instância de um buffer de vértice.</param>			
	static CarenResult DrawInstanced(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_QuantidadeVerticiesPorInstancia,
		UInt32 Param_QuantidadeInstancias,
		UInt32 Param_StartVerticeLocalizacao,
		UInt32 Param_StartInstanciaLocalizacao);

	/// <summary>
	/// (DrawInstancedIndirect) - Desenhe primitivos instanciado, gerado pelo GPU.
	/// </summary>
	/// <param name="Param_BufferDadosPrimitivos">Um ponteiro para um ID3D11Buffer, que é um buffer contendo o GPU gerado primitivos.</param>
	/// <param name="Param_DeslocamentoDados">Deslocamento em (Param_BufferDadosPrimitivos) para o início da GPU gerado primitivos.</param>
	static CarenResult DrawInstancedIndirect(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Buffer^% Param_BufferDadosPrimitivos,
		UInt32 Param_DeslocamentoDados);

	/// <summary>
	/// (DSGetConstantBuffers) - Obtém os buffers constantes usados por fase de domínio-shader.
	/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar os buffers de constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para recuperar (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz que contém as interfaces para o Buffers constantes.</param>
	static CarenResult DSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (DSGetSamplers) - Obtém uma variedade de interfaces de estado amostrador desde a fase de domínio-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar ficando amostradores de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_Amostradores">Número dos amostradores para obter um contexto de dispositivo. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
	/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizAmostradoresEstado">Uma matriz para as interfaces com amostradores de estado.</param>
	static CarenResult DSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_Amostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizAmostradoresEstado);

	/// <summary>
	/// (DSGetShader) - Se o sombreador de domínio atualmente definido no dispositivo.
	/// Qualquer retorno de interfaces terão sua contagem de referência, incrementada por um. Os aplicativos devem liberar a referência para a interface.
	/// </summary>
	/// <param name="Param_Out_SombreadorDominio">Retorna a interface para o sombreador de dominio.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz que contém interface de instâncias de classe.</param>
	/// <param name="Param_Out_ElementosMatriz">Retorna a quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult DSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11DomainShader^% Param_Out_SombreadorDominio,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_ElementosMatriz);

	/// <summary>
	/// (DSGetShaderResources) - Obter os recursos de domínio-shader. 
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a receber recursos de sombreamento de (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_QuantidadeRecursos">O número de recursos para obter a partir do dispositivo. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
	/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador a ser retornado pelo dispositivo.</param>
	static CarenResult DSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_QuantidadeRecursos,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizRecursoShader);

	/// <summary>
	/// (DSSetConstantBuffers) - Define os constantes buffers usados pela fase de domínio-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice para a matriz baseada em zero para começar a definir buffers constantes (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers para definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes a ser dada ao dispositivo.</param>
	static CarenResult DSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (DSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de domínio-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Indice na matriz baseada em zero do dispositivo para iniciar a configuração amostradores para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_Amostradores">Número dos amostradores na matriz. Cada estágio do pipeline tem um total de 16 amostrador vagas disponíveis 
	/// (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces amostrador-estado a ser dado ao dispositivo.</param>
	static CarenResult DSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_Amostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (DSSetShader) - Defina um sombreador de domínio para o dispositivo.
	/// </summary>
	/// <param name="Param_SombreadorDominio">Ponteiro para um sombreador de domínio. Passando NULO desabilita o sombreador para este estágio de pipeline.</param>
	/// <param name="Param_MatrizInstanciasClasse">Um ponteiro para uma matriz de instância da classe interfaces. Cada interface usada por um sombreador deve ter uma instância de 
	/// classe correspondente ou o shader vai ser desativado. Definir Param_MatrizInstanciasClasse para NULO se o sombreador não usa quaisquer interfaces.</param>
	/// <param name="Param_ElementosMatriz">A quantidade de elementos na matriz(Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult DSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11DomainShader^ Param_SombreadorDominio,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciasClasse,
		UInt32 Param_ElementosMatriz);

	/// <summary>
	/// (DSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de domínio-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para iniciar a configuração de recursos de sombreador para (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_QuantidadeRecursos">Número de recursos de sombreador definir. Até um máximo de 128 vagas estão disponíveis para recursos de sombreamento 
	/// (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizRecursoShader">Matriz de interfaces de exibição de recurso de sombreador definir para o dispositivo.</param>
	static CarenResult DSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizRecursoShader);

	/// <summary>
	/// (End) - Marca o fim de uma série de comandos.
	/// Use ICarenD3D11DeviceContext::Begin para marcar o início de uma série de comandos.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para uma interface de ID3D11Asynchronous .</param>
	static CarenResult End(
		ID3D11DeviceContext* Param_MyPointerWork, 
		ICarenD3D11Asynchronous^ Param_Async);

	/// <summary>
	/// (ExecuteCommandList) - Comandos de filas de uma lista de comandos para um dispositivo.
	/// </summary>
	/// <param name="Param_FilaComandos">Um ponteiro para uma interface ID3D11CommandList que encapsula uma lista de comandos graficos.</param>
	/// <param name="Param_RestaurarEstadoContexto">Um sinalizador booleano que determina se o estado do contexto de destino é salvo antes e restaurado após a execução de uma lista de comandos. Use TRUE para indicar que o tempo de 
	/// execução precisa salvar e restaurar o estado. Use FALSE para indicar que nenhum estado deve ser salvo ou restaurado, o que faz com que o contexto de destino retorne ao seu estado padrão após a 
	/// execução da lista de comandos. Normalmente, os aplicativos devem usar FALSE, a menos que restaurem o estado para ser quase equivalente ao estado que o tempo de execução restauraria se TRUE fosse 
	/// passado. Quando os aplicativos usam FALSE , eles podem evitar transições de estado desnecessárias e ineficientes.</param>
	static CarenResult ExecuteCommandList(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11CommandList^ Param_FilaComandos,
		Boolean Param_RestaurarEstadoContexto);

	/// <summary>
	/// (FinishCommandList) - Crie um comando lista e registro gráficos comandos nele.
	/// </summary>
	/// <param name="Param_RestDeferidoEstadoContexto">Um sinalizador booleano que determina se o tempo de execução salva o estado de contexto adiado antes de executar FinishCommandList e restaurá-lo posteriormente. 
	/// Use TRUE para indicar que o tempo de execução precisa salvar e restaurar o estado. Use FALSE para indicar que o tempo de execução não salvará nem restaurará nenhum estado. Nesse caso, o contexto deferido 
	/// retornará ao seu estado padrão após a conclusão desta chamada. Para obter informações sobre o estado padrão, consulte ICarenD3D11DeviceContext::ClearState. Normalmente, use FALSE, a menos que você restaure 
	/// o estado para ser quase equivalente ao estado que o tempo de execução restauraria se você passasse por TRUE . Quando você usa FALSE, você pode evitar transições de estado desnecessárias e ineficientes.</param>
	/// <param name="Param_Out_FilaComandos">Retorna um ponteiro da interface ICarenD3D11CommandList que é inicializado com as informações da lista de comandos gravados. O objeto ICarenD3D11CommandList 
	/// resultante é imutável e só pode ser usado com ICarenD3D11DeviceContext::ExecutarListaComandos.</param>
	static CarenResult FinishCommandList(
		ID3D11DeviceContext* Param_MyPointerWork,
		Boolean Param_RestDeferidoEstadoContexto,
		[Out] ICarenD3D11CommandList^% Param_Out_FilaComandos);

	/// <summary>
	/// (Flush) - Envia comandos de cima enfileirado no buffer de comandos para a unidade de processamento gráfico (GPU).
	/// </summary>
	static CarenResult Flush(ID3D11DeviceContext* Param_MyPointerWork);

	/// <summary>
	/// (GenerateMips) - Gera mipmaps para o recurso de sombreador determinado.
	/// </summary>
	/// <param name="Param_RecursoSombreador">Um ponteiro para uma interface ICarenD3D11ShaderResourceView que representa o recurso de sombreador.</param>
	static CarenResult GenerateMips(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11ShaderResourceView^ Param_RecursoSombreador);

	/// <summary>
	/// (GetContextFlags) - Obtém os sinalizadores de inicialização associados com o atual contexto diferido.
	/// </summary>
	/// <param name="Param_Out_ContextFlags">recebe as bandeiras que foram fornecidos à ContextFlags parâmetro de ICarenD3D11Device::CreateDeferredContext; no entanto, o sinalizador de contexto é reservado para 
	/// uso futuro.</param>
	static CarenResult GetContextFlags(
		ID3D11DeviceContext* Param_MyPointerWork, 
		[Out] UInt32% Param_Out_ContextFlags);

	/// <summary>
	/// (GetData) - Obter dados a partir da unidade de processamento gráfico (GPU) de forma assíncrona.
	/// </summary>
	/// <param name="Param_Async">Um ponteiro para uma interface ICarenD3D11Asynchronous para o objeto sobre o qual (GetData) recupera dados.</param>
	/// <param name="Param_Dados">Ponteiro para uma interface de buffer que receberá os dados. Se NULO, (GetData) será usado apenas para verificar o estado. O tipo de saída de dados depende do tipo de interface assíncrona.</param>
	/// <param name="Param_TamanhoDados">Tamanho dos dados a serem recuperados ou 0. Deve ser 0 quando (Param_Dados) for NULO.</param>
	/// <param name="Param_FlagsGetData">Bandeiras opcionais. Pode ser 0 ou qualquer combinação das bandeiras enumeradas por CA_D3D11_ASYNC_GETDATA_FLAG.</param>
	static CarenResult GetData(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Asynchronous^ Param_Async,
		ICarenBuffer^% Param_Dados,
		UInt32 Param_TamanhoDados,
		Enumeracoes::CA_D3D11_ASYNC_GETDATA_FLAG Param_FlagsGetData);

	/// <summary>
	/// (GetPredication) - Obtém o estado do predicado de renderização.
	/// </summary>
	/// <param name="Param_Out_Predicado">Recebe um ponteiro para um predicado. O valor armazenado aqui será NULO na criação do dispositivo.</param> 
	/// <param name="Param_Out_ValuePredicado">Recebe um valor booleano para preencher o valor de comparação de predicado. FALSE na criação do dispositivo.</param>
	static CarenResult GetPredication(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11Predicate^% Param_Out_Predicado,
		[Out] Boolean% Param_Out_ValuePredicado);

	/// <summary>
	/// (GetResourceMinLOD) - Obtém o mínimo nível de detalhe(LOD).
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para uma interface que represnta um recurso.</param> 
	/// <param name="Param_Out_LODMinimo">Retorna o LOD mínimo.</param> 
	static CarenResult GetResourceMinLOD(
		ID3D11DeviceContext* Param_MyPointerWork, 
		ICarenD3D11Resource^ Param_Recurso, 
		[Out] float% Param_Out_LODMinimo);

	/// <summary>
	/// (GetType) - Obtém o tipo de contexto de dispositivo.
	/// </summary>
	/// <param name="Param_Out_ContextoDispositivo">Retorna as opções de contexto do dispositivo.</param> 
	static CarenResult GetType(
		ID3D11DeviceContext* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D11_DEVICE_CONTEXT_TYPE% Param_Out_ContextoDispositivo);

	/// <summary>
	/// (GSGetConstantBuffers) - Se os buffers constantes usados pela fase geometria shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	static CarenResult GSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (GSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de gasoduto de sombreamento de geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	static CarenResult GSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (GSGetShader) - Obtém o sombreador de geometria atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorGeometria">Retorna uma interface para o sombreador de Geometria.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult GSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11GeometryShader^% Param_Out_SombreadorGeometria,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (GSGetShaderResources) - Obtém os recursos de geometria obscuros.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	static CarenResult GSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (GSSetConstantBuffers) - Define os constantes buffers usados pela fase geometria shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	static CarenResult GSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (GSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline de sombreador geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	static CarenResult GSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (GSSetShader) - Defina um sombreador de geometria para o dispositivo.
	/// </summary>
	/// <param name="Param_SombreadorGeometria">Ponteiro para um sombreador de Geometria. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	static CarenResult GSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11GeometryShader^ Param_SombreadorGeometria,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (GSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreamento de geometria.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	static CarenResult GSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (HSGetConstantBuffers) - Se os buffers constantes usados pela fase casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	static CarenResult HSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (HSGetSamplers) - Obter uma variedade de interfaces de estado amostrador desde a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	static CarenResult HSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (HSGetShader) - Obtém o Sombreador de Casco atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorCasco">Retorna uma interface para o Sombreador de Casco.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult HSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11HullShader^% Param_Out_SombreadorCasco,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (HSGetShaderResources) - Obtém os recursos do sombreador de casco(Hull).
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	static CarenResult HSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (HSSetConstantBuffers) - Defina os constantes buffers usados pelo palco casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	static CarenResult HSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (HSSetSamplers) - Defina uma matriz de Estados amostrador para a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	static CarenResult HSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (HSSetShader) - Defina um sombreador de casco para o dispositivo.
	/// </summary>
	/// <param name="Param_SombreadorCasco">Ponteiro para um Sombreador de Casco(Hull). Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	static CarenResult HSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11HullShader^ Param_SombreadorCasco,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (HSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de casco-shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	static CarenResult HSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (IAGetIndexBuffer) - Obter um ponteiro para o buffer de índice que é vinculado à fase de entrada-montador.
	/// </summary>
	/// <param name="Param_Out_Buffer">Retorna um ponteiro para o buffer.</param>
	/// <param name="Param_Out_Formato">Retorna uma especificação do formato dos dados no buffer de índice. Esses formatos oferecem o tamanho e o tipo de dados no buffer. Os formatos só permitidos para dados 
	/// de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
	/// <param name="Param_Out_Deslocamento">Retorna o Deslocamento(Offset) (em bytes) desde o início do buffer de índice, o primeiro índice para usar.</param>
	static CarenResult IAGetIndexBuffer(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11Buffer^% Param_Out_Buffer,
		[Out] Enumeracoes::CA_DXGI_FORMAT% Param_Out_Formato,
		[Out] UInt32% Param_Out_Deslocamento);

	/// <summary>
	/// (IAGetInputLayout) - Obter um ponteiro para o objeto de entrada-layout que está vinculado para o estágio de entrada-montador.
	/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
	/// necessários para vitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_Out_InputLayout">Reretorna um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
	static CarenResult IAGetInputLayout(
		ID3D11DeviceContext* Param_MyPointerWork, 
		[Out] ICarenD3D11InputLayout^% Param_Out_InputLayout);

	/// <summary>
	/// (IAGetPrimitiveTopology) - Obter informações sobre o tipo primitivo e a ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
	/// </summary>
	/// <param name="Param_Out_TipoPrimitivo"></param>
	static CarenResult IAGetPrimitiveTopology(
		ID3D11DeviceContext* Param_MyPointerWork, 
		[Out] Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY% Param_Out_TipoPrimitivo);

	/// <summary>
	/// (IAGetVertexBuffers) - Se os buffers de vértice ligados para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_StartSlot">O slot de entrada do primeiro buffer vértice para chegar. O primeiro buffer de vértice é explicitamente vinculado ao slot de início; Isso faz com que cada buffer de 
	/// vértice adicional na matriz para ser implicitamente ligado a cada slot de entrada subsequente. O máximo de 16 ou 32 slots de entrada (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) 
	/// estão disponíveis; o número máximo de slots de entrada depende do nível de recurso.</param>
	/// <param name="Param_NumeroBuffers">O número de buffers de vértice para obter começando em deslocamento. O número de buffers (mais o slot de partida) não pode exceder o número total de slots de entrada IA-estágio.</param>
	/// <param name="Param_Out_MatrizVertexBuffers">Retorna uma matriz de buffers de vertex.</param>
	/// <param name="Param_Out_MatrizStrides">Retorna uma matriz de valores de (Stride) retornado pelo método; um (Stride) valor para cada buffer na matriz de buffer de vértice. Cada valor de stride é o tamanho (em bytes) 
	/// dos elementos que devem ser usados desse buffer de vértice.</param>
	/// <param name="Param_Out_MatrizDeslocamentos">uma matriz de valores de deslocamento retornado pelo método; um valor para cada buffer na matriz de buffer de vértice de deslocamento. Cada deslocamento é o 
	/// número de bytes entre o primeiro elemento de um buffer de vértice e o primeiro elemento que será usado.</param>
	static CarenResult IAGetVertexBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizVertexBuffers,
		[Out] cli::array<UInt32>^% Param_Out_MatrizStrides,
		[Out] cli::array<UInt32>^% Param_Out_MatrizDeslocamentos);

	/// <summary>
	/// (IASetIndexBuffer) - Vincule um buffer do índice para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_Buffer">Um ponteiro para um objeto ICarenD3D11Buffer, que contém os índices. O buffer do índice deve ter sido criado com o sinalizador D3D11_BIND_INDEX_BUFFER .</param>
	/// <param name="Param_Formato">Um CA_D3D11_DXGI_FORMAT que especifica o formato dos dados no buffer de índice. Os formatos só permitidos para dados de reserva de índice são (DXGI_FORMAT_R16_UINT) de 16-bit e 32-bit inteiros (DXGI_FORMAT_R32_UINT).</param>
	/// <param name="Param_Deslocamento">Offset (em bytes) do início do buffer de índice para o primeiro índice para usar.</param>
	static CarenResult IASetIndexBuffer(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Buffer^ Param_Buffer,
		Enumeracoes::CA_DXGI_FORMAT Param_Formato,
		UInt32 Param_Deslocamento);

	/// <summary>
	/// (IASetInputLayout) - Vincule um objeto de layout de entrada para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_InputLayout">Um ponteiro para o layout de entrada de objeto, que descreve os buffers de entrada que serão lido pelo palco IA.</param>
	static CarenResult IASetInputLayout(
		ID3D11DeviceContext* Param_MyPointerWork, 
		ICarenD3D11InputLayout^ Param_InputLayout);

	/// <summary>
	/// (IASetPrimitiveTopology) - Vincule informações sobre o tipo primitivo e ordem de dados que descreve os dados de entrada para o estágio de entrada da montadora.
	/// </summary>
	/// <param name="Param_TipoPrimitivo">O tipo de primitivo e ordenação dos dados primitivos.</param>
	static CarenResult IASetPrimitiveTopology(
		ID3D11DeviceContext* Param_MyPointerWork, 
		Enumeracoes::CA_D3D11_PRIMITIVE_TOPOLOGY Param_TipoPrimitivo);

	/// <summary>
	/// (IASetVertexBuffers) - Ligar a uma matriz de buffers de vértice para o estágio de entrada-montador.
	/// </summary>
	/// <param name="Param_StartSlot">O primeiro slot de entrada para ligação. O primeiro buffer de vértice é explicitamente vinculado ao slot de início; Isso faz com que cada buffer de vértice adicional na 
	/// matriz para ser implicitamente ligado a cada slot de entrada subsequente. O máximo de 16 ou 32 slots de entrada (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1) estão disponíveis; o número
	/// máximo de slots de entrada depende do nível de recurso.</param>
	/// <param name="Param_NumeroBuffers">O número de buffers de vértice na matriz. O número de buffers (mais o slot de partida) não pode exceder o número total de slots de entrada IA-estágio 
	/// (varia de 0 a D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVertexBuffers">Uma matriz de buffers de vértice. Os buffers de vértice devem ter sido criados com o sinalizador D3D11_BIND_VERTEX_BUFFER .</param>
	/// <param name="Param_MatrizStrides">Uma matriz de valores de stride; um passo valor para cada buffer na matriz de buffer de vértice. Cada passo é o tamanho (em bytes) dos elementos que devem ser 
	/// usados desse buffer de vértice.</param>
	/// <param name="Param_MatrizDeslocamentos">uma matriz de valores de deslocamento; um valor para cada buffer na matriz de buffer de vértice de deslocamento. Cada deslocamento é o número de bytes entre o 
	/// primeiro elemento de um buffer de vértice e o primeiro elemento que será usado.</param>
	static CarenResult IASetVertexBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizVertexBuffers,
		cli::array<UInt32>^ Param_MatrizStrides,
		cli::array<UInt32>^ Param_MatrizDeslocamentos);

	/// <summary>
	/// (Map) - Obtém um ponteiro para os dados contidos em um sub-recurso e nega o acesso GPU para aquele sub-recurso.
	/// Esse método também retorna DXGI_ERROR_WAS_STILL_DRAWING se MapFlags especifica D3D11_MAP_FLAG_DO_NOT_WAIT e a GPU ainda não está terminado com o recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para uma interface de ID3D11Resource .</param>
	/// <param name="Param_IndiceSubRecurso">O Indice para o sub-recruso.</param>
	/// <param name="Param_PermissõesAcessoRecurso">Um D3D11_MAP valor digitado que especifica a CPU ler e escrever permissões para um recurso.</param>
	/// <param name="Param_MapFlags">Sinalizador que especifica que a CPU faz quando a GPU está ocupado. Este sinalizador é opcional. Define como (CA_D3D11_MAP_FLAG::Zero) para deixar como opcional.</param>
	/// <param name="Param_Out_RecrusoMapeado">Uma estrutura de CA_D3D11_MAPPED_SUBRESOURCE para o sub-recurso mapeado. Essa estrutura pode ser NULA as vezes. Consulte a documentação.</param>
	static CarenResult Map(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		UInt32 Param_IndiceSubRecurso,
		Enumeracoes::CA_D3D11_MAP Param_PermissõesAcessoRecurso,
		Enumeracoes::CA_D3D11_MAP_FLAG Param_MapFlags,
		[Out] Estruturas::CA_D3D11_MAPPED_SUBRESOURCE^% Param_Out_RecrusoMapeado);

	/// <summary>
	/// (OMGetBlendState) - Obter o estado de mistura da fase de saída-fusão.
	/// </summary>
	/// <param name="Param_Out_EstadoMistura">Retorna um ponteiro para a interface de estado de mistura.</param>
	/// <param name="Param_Out_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA.</param>
	/// <param name="Param_Out_SampleMask">Retorna um valor para uma máscara de amostra.</param>
	static CarenResult OMGetBlendState(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11BlendState^% Param_Out_EstadoMistura,
		[Out] cli::array<float>^% Param_Out_MatrizFatoresMistura,
		[Out] UInt32% Param_Out_SampleMask);

	/// <summary>
	/// (OMGetDepthStencilState) - Obtém o estado de profundidade-estêncil da fase de saída-fusão.
	/// </summary>
	/// <param name="Param_Out_DepthStencilState">Retorna um ponteiro para interface de estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
	/// <param name="Param_Out_StencilRef">Retorna um valor para um estado de profundidade-estêncil para ser preenchido com informações do dispositivo.</param>
	static CarenResult OMGetDepthStencilState(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11DepthStencilState^% Param_Out_DepthStencilState,
		[Out] UInt32% Param_Out_StencilRef);

	/// <summary>
	/// (OMGetRenderTargets) - Obter ponteiros para os recursos vinculados para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_NumeroViews">Número de destinos de processamento para recuperar.</param>
	/// <param name="Param_IgnorarRecuperaçãoDestino">Defina (TRUE) para esse parâmetro quando a recuperação de um destino de processamento não é necessária.
	/// O parametro (Param_Out_MatrizRenderTargetViews) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_MatrizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam processar exibições de alvo.</param>
	/// <param name="Param_IgnorarRecuperaçãoModoExibição">Defina (TRUE) para esse parâmetro quando a recuperação do modo de exibição de profundidade-estêncil não é necessária.
	/// O parametro (Param_Out_DepthStencilView) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_DepthStencilView">Ponteiro para um ID3D11DepthStencilView, que representa uma visão de profundidade-estêncil.</param>
	static CarenResult OMGetRenderTargets(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroViews,
		Boolean Param_IgnorarRecuperaçãoDestino,
		[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTargetViews,
		Boolean Param_IgnorarRecuperaçãoModoExibição,
		[Out] ICarenD3D11DepthStencilView^% Param_Out_DepthStencilView);

	/// <summary>
	/// (OMGetRenderTargetsAndUnorderedAccessViews) - Obter ponteiros para os recursos vinculados para o estágio de saída-fusão.
	/// Qualquer interface retornada terão sua contagem de referência, incrementada por um. Aplicativos devem chamar ICaren::LiberarReferencia sobre as interfaces retornadas quando eles não são mais 
	/// necessários para vitar vazamentos de memória.
	/// </summary>
	/// <param name="Param_NumeroRTVs">O número de pontos de vista de renderização-destino para recuperar.</param>
	/// <param name="Param_IgnorarRenderTargetView">Defina (TRUE) para esse parâmetro quando a recuperação de pontos de vista de destino de processamento não é necessária.
	/// O parametro (Param_Out_MatrizRenderTarget) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_MatrizRenderTarget">Retorna uma matriz de ID3D11RenderTargetViews, que representam vistas de destino de processamento.</param>
	/// <param name="Param_Out_DepthStencilView">Defina (TRUE) para esse parâmetro quando a recuperação do modo de exibição de profundidade-estêncil não é necessária.
	/// O parametro (Param_DepthStencilView) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_DepthStencilView">Retorna um ponteiro para um ICarenD3D11DepthStencilView, que representa uma visão de profundidade-estêncil.</param>
	/// <param name="Param_UAVStartSlot">ndice em uma matriz baseada em zero para começar a recuperar acesso não ordenada visualizações (varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - 1). 
	/// Para sombreamentos de pixel (Param_UAVStartSlot) deve ser igual ao número de pontos de vista de destino de processamento que estão vinculados.</param>
	/// <param name="Param_NumeroUAVs">Número de pontos de vista de acesso não-ordenados para retornar no ppUnorderedAccessViews. Este número varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - Param_UAVStartSlot.</param>
	/// <param name="Param_IgnorarUnorderedAccessView">Defina (TRUE) para esse parâmetro quando a recuperação de pontos de vista de acesso não-ordenados não é necessária.
	///  O parametro (Param_Out_MatrizUnorderedAccessViews) retorna NULO se esse valor for verdadeiro.</param>
	/// <param name="Param_Out_MatrizUnorderedAccessViews">Retorna uma matriz de ICarenD3D11UnorderedAccessViews, que representam vistas de acesso não ordenada que são recuperadas.</param>
	static CarenResult OMGetRenderTargetsAndUnorderedAccessViews(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroRTVs,
		Boolean Param_IgnorarRenderTargetView,
		[Out] cli::array<ICarenD3D11RenderTargetView^>^% Param_Out_MatrizRenderTarget,
		Boolean Param_IgnorarDepthStencilView,
		[Out] ICarenD3D11DepthStencilView^ Param_Out_DepthStencilView,
		UInt32  Param_UAVStartSlot,
		UInt32  Param_NumeroUAVs,
		Boolean Param_IgnorarUnorderedAccessView,
		[Out] cli::array<ICarenD3D11UnorderedAccessView^>^% Param_Out_MatrizUnorderedAccessViews);

	/// <summary>
	/// (OMSetBlendState) - Defina o estado de mistura da fase de saída-fusão.
	/// Para criar uma interface de mistura-estado, chamade o método ICarenD3D11Device::CreateBlendState.
	/// </summary>
	/// <param name="Param_EstadoMistura">Ponteiro para um estado de mistura interface. Passe nulo para um estado de mistura padrão.</param>
	/// <param name="Param_MatrizFatoresMistura">Matriz de mistura de fatores, um para cada componente RGBA. Os fatores de mistura modulate valores para o shader de pixel, processar o alvo, ou ambos. Se você 
	/// tiver criado o objeto de mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, a fase de mistura usa a matriz não-nulos de mistura fatores. Se você não criar o objeto de 
	/// mistura-estado com D3D11_BLEND_BLEND_FACTOR ou D3D11_BLEND_INV_BLEND_FACTOR, fase de mesclagem não usa a matriz não-nulos de misturam fatores; o tempo de execução armazena os mistura de fatores, 
	/// e mais tarde pode chamar ICarenD3D11DeviceContext::OMGetBlendState para recuperar os fatores de mistura. Se você transmitir NULO, o tempo de execução usa ou armazena um fator de mistura igual 
	/// a {1, 1, 1, 1}.</param>
	/// <param name="Param_SampleMask">cobertura de amostra de 32 bits. O valor padrão é 0xffffffff. Uma máscara de amostra determina quais amostras atualizadas em todos os destinos de processamento ativo. 
	/// O mapeamento de bits em uma máscara de amostra para amostras em um destino processar multisample é da responsabilidade de um aplicativo individual. Sempre é aplicada uma máscara de amostra; 
	/// é independente de se multisampling é habilitado e não depende de se um aplicativo usa multisample render destinos.</param>
	static CarenResult OMSetBlendState(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11BlendState^ Param_EstadoMistura,
		cli::array<float>^ Param_MatrizFatoresMistura,
		UInt32 Param_SampleMask);

	/// <summary>
	/// (OMSetDepthStencilState) - Define o estado de profundidade-estêncil da fase de saída-fusão.
	/// [Atenção] -> O método armazenará uma referência às interfaces do passado. Isso difere do comportamento de estado do dispositivo em Direct3D 10.
	/// </summary>
	/// <param name="Param_DepthStencilState">Ponteiro para um estado de profundidade-estêncil interface para ligar o dispositivo. Defina NULO para usar o estado padrão listado em D3D11_DEPTH_STENCIL_DESC.</param>
	/// <param name="Param_StencilRef">Valor de referência para executar contra ao fazer um teste de profundidade-estêncil.</param>
	static CarenResult OMSetDepthStencilState(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11DepthStencilState^ Param_DepthStencilState,
		UInt32 Param_StencilRef);

	/// <summary>
	/// (OMSetRenderTargets) - Ligar um ou mais destinos de processamento atomicamente e a profundidade-estêncil buffer para o estágio de saída-fusão.
	/// </summary>
	/// <param name="Param_NumeroViews">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas 
	/// na matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro.</param>
	/// <param name="Param_MatizRenderTargetViews">Uma matriz de ICarenD3D11RenderTargetView que representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumViews é 0, não render destinos são vinculados.</param>
	/// <param name="Param_DepthStencilView">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
	static CarenResult OMSetRenderTargets(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11RenderTargetView^>^ Param_MatizRenderTargetViews,
		ICarenD3D11DepthStencilView^ Param_DepthStencilView);

	/// <summary>
	/// (OMSetRenderTargetsAndUnorderedAccessViews) - Vincula recursos para a fase de saída-fusão.
	/// Para sombreamentos de pixel, os destinos de processamento e acesso não-ordenados vistas compartilhar os slots de recurso mesmo quando sendo escritos para fora. Isto significa que UAVs devem ser dado 
	/// um deslocamento, para que eles são colocados nos slots após as vistas de destino de render que estão sendo vinculadas.
	/// Nota:  CSC, DSV e UAVs não podem ser definidos de forma independente; todos eles precisam ser definidas ao mesmo tempo.
	/// </summary>
	/// <param name="Param_NumeroRTVs">Número de destinos de processamento para bind (varia entre 0 e D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT). Se este parâmetro for diferente de zero, o número de entradas na 
	/// matriz a quais pontos de ppRenderTargetViews deve ser igual o número neste parâmetro. Se você definir NumRTVs para D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL (0xffffffff), esse método não modifica as 
	/// vistas atualmente ligados render-alvo (CSC) e também não modifica vista profundidade-estêncil (DSV).</param>
	/// <param name="Param_MatrizRenderTargetViews">Uma matriz de s de ID3D11RenderTargetViewque representam as metas de render para ligar o dispositivo. Se este parâmetro for NULO, e NumRTVs 
	/// é 0, não render destinos são vinculados.</param>
	/// <param name="Param_DepthStencil">Ponteiro para um ICarenD3D11DepthStencilView que representa a exibição de profundidade-estêncil para ligar o dispositivo. 
	/// Se este parâmetro for NULO, o estado de profundidade-estêncil não está ligado.</param>
	/// <param name="Param_UAVStartSlot">Índice em uma matriz baseada em zero para começar a definir vistas não ordenada-acesso (varia de 0 a D3D11_PS_CS_UAV_REGISTER_COUNT - 1).Para o runtime Direct3D 11.1, 
	/// que está disponível iniciando com o Windows 8, esse valor pode variar de 0 a D3D11_1_UAV_SLOT_COUNT - 1. D3D11_1_UAV_SLOT_COUNT é definido como 64. Para sombreamentos de pixel, Param_UAVStartSlot deve ser 
	/// igual ao número de pontos de vista de renderização - destino sendo ligado.</param>
	/// <param name="Param_NumeroUAVs">Número de pontos de vista de acesso não ordenada (UAVs) em Param_MatrizUnorderedAccessViews. Se você definir NumUAVs para D3D11_KEEP_UNORDERED_ACCESS_VIEWS (0xffffffff), 
	/// esse método não modifica os pontos de vista não ordenada-acesso atualmente ligados.Para o runtime Direct3D 11.1, que está disponível iniciando com o Windows 8, esse valor pode variar de 0 a 
	/// D3D11_1_UAV_SLOT_COUNT - Param_UAVStartSlot.</param>
	/// <param name="Param_MatrizUnorderedAccessViews">Uma matriz de s de ICarenD3D11UnorderedAccessViewque representam os pontos de vista de acesso não-ordenados para ligar o dispositivo. Se este parâmetro for 
	/// NULO, e Param_NumeroUAVs é 0, não ordenada-acesso opiniões é vinculado.</param>
	/// <param name="Param_MatrizUAVInitialCounts">Uma matriz de acrescentar e consumir deslocamentos de reserva. Um valor de -1 indica que para manter o atual deslocamento. Quaisquer outros valores definir o 
	/// contador oculto para aquele UAV appendable e consumíveis. Param_MatrizUAVInitialCounts é relevante apenas para UAVs que foram criados com qualquer D3D11_BUFFER_UAV_FLAG_APPEND ou D3D11_BUFFER_UAV_FLAG_COUNTER 
	/// especificado quando o UAV foi criado; caso contrário, o argumento é ignorado.</param>
	static CarenResult OMSetRenderTargetsAndUnorderedAccessViews(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroRTVs,
		cli::array <ICarenD3D11RenderTargetView^>^ Param_MatrizRenderTargetViews,
		ICarenD3D11DepthStencilView^ Param_DepthStencil,
		UInt32 Param_UAVStartSlot,
		UInt32 Param_NumeroUAVs,
		cli::array<ICarenD3D11UnorderedAccessView^>^ Param_MatrizUnorderedAccessViews,
		cli::array<UInt32>^ Param_MatrizUAVInitialCounts);

	/// <summary>
	/// (PSGetConstantBuffers) - Se os buffers constantes usados por fase de gasoduto do sombreador de pixel. 
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	static CarenResult PSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (PSGetSamplers) - Obtém uma matriz de Estados amostrador desde a fase de gasoduto de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	static CarenResult PSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (PSGetShader) -  Obtém o sombreador de pixel atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorPixel">Retorna uma interface para o Sombreador de Pixel.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult PSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11PixelShader^% Param_Out_SombreadorPixel,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (PSGetShaderResources) - Obter o pixel sombreador recursos.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	static CarenResult PSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (PSSetConstantBuffers) - Define os constantes buffers usados pela fase de gasoduto do sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Índice na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param>
	static CarenResult PSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (PSSetSamplers) - Defina uma matriz de Estados amostrador à fase de gasoduto de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	static CarenResult PSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (PSSetShader) - Define um sombreador de pixel para o dispositivo.
	/// </summary>
	/// <param name="Param_ShaderPixel">Ponteiro para um Sombreador de Pixel. Passar NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	static CarenResult PSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11PixelShader^ Param_ShaderPixel,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (PSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de pixel.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	static CarenResult PSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (ResolveSubresource) - Copie um recurso multisampled para um recurso não-multisampled.
	/// </summary>
	/// <param name="Param_RecursoDestino">Recurso de destino. Deve ser um criado com o sinalizador D3D11_USAGE_DEFAULT e single-amostrados.</param>
	/// <param name="Param_IndiceSubRecursoDestino">Um índice baseado em zero, que identifica o sub-recurso de destino. Use D3D11CalcSubresource para calcular o índice.</param>
	/// <param name="Param_RecursoOrigem">Fonte de recursos. Deve ser multisampled.</param>
	/// <param name="Param_IndiceSubRecursoOrigem">O sub-recurso fonte de fonte de recursos.</param>
	/// <param name="Param_DXGIFormato">Um CA_DXGI_FORMAT que indica como o recurso multisampled será resolvido para um recurso único-amostrados.</param>
	static CarenResult ResolveSubresource(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoDestino,
		UInt32 Param_IndiceSubRecursoDestino,
		ICarenD3D11Resource^ Param_RecursoOrigem,
		UInt32 Param_IndiceSubRecursoOrigem,
		Enumeracoes::CA_DXGI_FORMAT Param_DXGIFormato);

	/// <summary>
	/// (RSGetScissorRects) - Obtém a matriz de scissor retângulos vinculado à fase rasterizer.
	/// </summary>
	/// <param name="Param_Out_NumeroRects">O número de retângulos de tesoura (intervalos entre 0 e D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE) ligados; defina Param_ChecarQuantidade para TRUE para usar 
	/// Param_Out_NumeroRects para ver quantos retângulos seriam retornados.</param>
	/// <param name="Param_ChecarQuantidade">Define como (TRUE) para obter a quantidade de retangulos que seriam retornados. Se esse valor for TRUE, o parametro (Param_Out_Rects) não retorna nada.</param>
	/// <param name="Param_Out_Rects">Uma matriz de retângulos scissor. Se Param_NumeroRects for maior que o número de (Scissor Rects) atualmente vinculada, membros não utilizados da matriz conterá 0.</param>
	static CarenResult RSGetScissorRects(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] UInt32% Param_Out_NumeroRects,
		Boolean Param_ChecarQuantidade,
		[Out] cli::array<Estruturas::CA_RECT^>^% Param_Out_Rects);

	/// <summary>
	/// (RSGetState) - Obtém o estado do rasterizador do rasterizador estágio do pipeline.
	/// </summary>
	/// <param name="Param_Out_EstadoRasterizador">Um ponteiro para um estado de rasterizador interface para preencher com as informações do dispositivo.</param>
	static CarenResult RSGetState(ID3D11DeviceContext* Param_MyPointerWork, [Out] ICarenD3D11RasterizerState^% Param_Out_EstadoRasterizador);

	/// <summary>
	/// (RSGetViewports) - Obtém a matriz de viewports vinculadas à fase rasterizer.
	/// </summary>
	/// <param name="Param_ObterQuantidadeViewports">Define para (TRUE) para obter o número de viewports atualmente definidas. Se (TRUE), Param_Out_MatrizViewports retorna NULO.</param>
	/// <param name="Param_Ref_NumeroViewports">.Na entrada deve definir a quantidade de viewports que seram obtidas. Na saida, ela retorna a quantidade real de viewports retornadas pelo
	/// parametro (Param_Out_MatrizViewports).</param>
	/// <param name="Param_Out_MatrizViewports">Uma matriz de estruturas CA_D3D11_VIEWPORT para as viewports que estão vinculadas à fase do rasterizador.</param>
	static CarenResult RSGetViewports(
		ID3D11DeviceContext* Param_MyPointerWork,
		Boolean Param_ObterQuantidadeViewports,
		UInt32% Param_Ref_NumeroViewports,
		[Out] cli::array<Estruturas::CA_D3D11_VIEWPORT^>^% Param_Out_MatrizViewports);

	/// <summary>
	/// (RSSetScissorRects) - Vincule uma matriz de retângulos de tesoura para o rasterizador de palco.
	/// </summary>
	/// <param name="Param_NumeroRects">Número de retângulos de tesoura para ligar.</param>
	/// <param name="Param_MatrizRects">Uma matriz de retângulos scissor.</param>
	static CarenResult RSSetScissorRects(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroRects,
		cli::array<Estruturas::CA_RECT^>^ Param_MatrizRects);

	/// <summary>
	/// (RSSetState) - Defina o estado do rasterizador para o rasterizador de estágio do pipeline.
	/// </summary>
	/// <param name="Param_EstadoRasterizador">Ponteiro para uma interface de estado rasterizador para vincular ao pipeline.</param>
	static CarenResult RSSetState(ID3D11DeviceContext* Param_MyPointerWork, ICarenD3D11RasterizerState^ Param_EstadoRasterizador);

	/// <summary>
	/// (RSSetViewports) - Ligar a uma matriz de viewports para o rasterizador de estágio do pipeline.
	/// </summary>
	/// <param name="Param_NumeroViewports">Número de viewports para vincular.</param>
	/// <param name="Param_MatrizViewports">Uma matriz de estruturas D3D11_VIEWPORT para vincular ao dispositivo. Consulte a página de estrutura para obter detalhes sobre como o tamanho da viewport depende do nível de recurso do dispositivo que foi alterado 
	/// entre o Direct3D 11 e o Direct3D 10.</param>
	static CarenResult RSSetViewports(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroViewports,
		cli::array<Estruturas::CA_D3D11_VIEWPORT^>^ Param_MatrizViewports);

	/// <summary>
	/// (SetPredication) - Defina um predicado de renderização.
	/// </summary>
	/// <param name="Param_Predicate">Um ponteiro para a interface ICarenD3D11Predicate que representa o predicado de renderização. Um valor NULO indica predicação "não"; Nesse caso, o valor de 
	/// (Param_ValorPredicado) é irrelevante, mas será preservado para ICarenD3D11DeviceContext::GetPredication.</param>
	/// <param name="Param_ValorPredicado">Se TRUE, a renderização será afetada quando as condições do predicado forem cumpridas. Se FALSE, a renderização será afetada quando as condições não forem atendidas.</param>
	static CarenResult SetPredication(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Predicate^ Param_Predicate,
		Boolean Param_ValorPredicado);

	/// <summary>
	/// (SetResourceMinLOD) - Define o mínimo nível-de-detalhe (LOD) para um recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para um ID3D11Resource que representa o recurso.</param>
	/// <param name="Param_MinLOD">O nível de detalhamento, que varia entre 0 e o número máximo de níveis de mipmap do recurso. Por exemplo, o número máximo de níveis mipmap de uma textura 1D é especificado na 
	/// MipLevels membro do D3D11_TEXTURE1D_DESC estrutura.</param>
	static CarenResult SetResourceMinLOD(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		float Param_MinLOD);

	/// <summary>
	/// (SOGetTargets) - Obtém os amortecedores de saída alvo para a fase de saída de fluxo do gasoduto.
	/// </summary>
	/// <param name="Param_NumeroBuffers">O número de Buffers a serem obtidos.</param>
	/// <param name="Param_Out_MatrizBuffers">Recebe a matriz com os buffers de saida retornado do dispositivo.</param>
	static CarenResult SOGetTargets(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (SOSetTargets) - Defina os buffers de saída de destino para o fluxo de saída estágio do pipeline.
	/// </summary>
	/// <param name="Param_NumeroBuffers">O número de buffer para ligar ao dispositivo. Um máximo de quatro buffers de saída pode ser definido. Se menos de quatro forem definidos pela chamada, 
	/// os slots de buffer restantes serão definidos como NULO.</param>
	/// <param name="Param_MatrizBuffers">A matriz de buffers de saída para ligar ao dispositivo. Os buffers devem ter sido criados com o sinalizador D3D11_BIND_STREAM_OUTPUT.</param>  
	/// <param name="Param_DeslocamentosBuffers">Matriz de deslocamentos para os buffers de saída de (Param_MatrizBuffers), um deslocamento para cada buffer. Os valores de deslocamento devem estar 
	/// em bytes.</param>
	static CarenResult SOSetTargets(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers,
		cli::array<UInt32>^ Param_DeslocamentosBuffers);

	/// <summary>
	/// (unmap) - Invalida o ponteiro para um recurso e reabilita o acesso da GPU para esse recurso.
	/// </summary>
	/// <param name="Param_Recurso">Um ponteiro para o recurso a ser invalido.</param>
	/// <param name="Param_SubrecursoInvalidado">O Id do subrecurso a ser (Desmapeado).</param>
	static CarenResult Unmap(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_Recurso,
		UInt32 Param_SubrecursoInvalidado);

	/// <summary>
	/// (UpdateSubresource) -  A CPU copia dados da memória para um sub-recurso criado na memória não-mapeável.
	/// </summary>
	/// <param name="Param_RecursoDestino">Um ponteiro para o recurso de destino.</param>
	/// <param name="Param_SubrecursoDestino">Um índice baseado em zero, que identifica o sub-destino do destino.</param>
	/// <param name="Param_Caixa">Uma caixa que define a parte do sub-destino de destino para copiar os dados do recurso. Coordenadas são em bytes para buffers e em texels para texturas. Se NULO, os dados são
	/// gravados no subfonte de destino sem nenhum deslocamento. As dimensões da fonte devem caber no destino</param>
	/// <param name="Param_DadosOrigemMemoria">Um ponteiro para os dados de origem na memória.</param>
	/// <param name="Param_TamanhoLinhaOrigem">(SrcRowPitch) - O tamanho de uma linha dos dados de origem.</param>
	/// <param name="Param_TamhoFatiaProdundidade">(SrcDepthPitch) - O tamanho de uma fatia de profundidade dos dados de origem.</param>
	static CarenResult UpdateSubresource(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11Resource^ Param_RecursoDestino,
		UInt32 Param_SubrecursoDestino,
		Estruturas::CA_D3D11_BOX^ Param_Caixa,
		ICarenBuffer^ Param_DadosOrigemMemoria,
		UInt32 Param_TamanhoLinhaOrigem,
		UInt32 Param_TamhoFatiaProdundidade);

	/// <summary>
	/// (VSGetConstantBuffers) - Se os buffers constantes usados pela fase vértice shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a recuperar buffers constantes de (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a serem recuperados (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizBuffers">Retorna uma matriz de ponteiros de interface de buffer constante.</param>
	static CarenResult VSGetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		[Out] cli::array<ICarenD3D11Buffer^>^% Param_Out_MatrizBuffers);

	/// <summary>
	/// (VSGetSamplers) - Obter uma matriz de Estados amostrador desde a fase de gasoduto de shader de vértice.
	/// </summary>
	/// <param name="Param_StartSlot">Index em uma matriz baseada em zero para começar a obter samplers de (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de (Samplers) para obter de um contexto de dispositivo. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizEstadoAmostrado">Retorna uma matriz com interfaces do amostrador de estado.</param>
	static CarenResult VSGetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		[Out] cli::array<ICarenD3D11SamplerState^>^% Param_Out_MatrizEstadoAmostrado);

	/// <summary>
	/// (VSGetShader) - Obtém o vértice shader atualmente definido no dispositivo.
	/// </summary>
	/// <param name="Param_Out_SombreadorVertice">Retorna uma interface para o sombreador de vertice.</param>
	/// <param name="Param_Out_MatrizInstanciasClasse">Retorna uma matriz com interfaces de Instancias de classe.</param>
	/// <param name="Param_Out_QuantidadeInstancias">Retorna a quantidade de de instancias de classe na matriz do parametro (Param_Out_MatrizInstanciasClasse).</param>
	static CarenResult VSGetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		[Out] ICarenD3D11VertexShader^% Param_Out_SombreadorVertice,
		[Out] cli::array<ICarenD3D11ClassInstance^>^% Param_Out_MatrizInstanciasClasse,
		[Out] UInt32% Param_Out_QuantidadeInstancias);

	/// <summary>
	/// (VSGetShaderResources) - Obter o vértice shader recursos.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a obter recursos do shader (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">O número de recursos para obter do dispositivo. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (varia de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_Out_MatrizVisualizadoresSombreador">Matriz de interfaces de visualização de recursos do sombreador a serem retornadas pelo dispositivo.</param>
	static CarenResult VSGetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		[Out] cli::array<ICarenD3D11ShaderResourceView^>^% Param_Out_MatrizVisualizadoresSombreador);

	/// <summary>
	/// (VSSetConstantBuffers) - Define os constantes buffers usados pela fase vértice shader pipeline.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a definir buffers constantes para (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroBuffers">Número de buffers a definir (varia de 0 a D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - Param_StartSlot).</param> 
	/// <param name="Param_MatrizBuffers">Matriz de buffers constantes sendo fornecidos ao dispositivo.</param> 
	static CarenResult VSSetConstantBuffers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroBuffers,
		cli::array<ICarenD3D11Buffer^>^ Param_MatrizBuffers);

	/// <summary>
	/// (VSSetSamplers) - Defina uma matriz de Estados amostrador para o estágio de pipeline vértice shader.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os samplers para (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroAmostradores">Número de amostradores na matriz. Cada estágio de pipeline tem um total de 16 slots disponíveis (varia de 0 a D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizAmostradoresEstado">Uma matriz de interfaces de estado do amostrador.</param>
	static CarenResult VSSetSamplers(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroAmostradores,
		cli::array<ICarenD3D11SamplerState^>^ Param_MatrizAmostradoresEstado);

	/// <summary>
	/// (VSSetShader) - Defina um sombreador de vértices para o dispositivo.
	/// </summary>
	/// <param name="Param_ShaderVertice">Ponteiro para um sombreador de vértice. Passar em NULO desativa o shader para este estágio de pipeline.</param>  
	/// <param name="Param_MatrizInstanciaClasse">Uma matriz de interfaces de instância de classe. Cada interface usada por um sombreador deve ter uma instância de classe correspondente ou o shader será desativado. Defina como NULO se o sombreador não usar nenhuma interface.</param>
	/// <param name="Param_NumeroInstanciasClasse">O numero de (ICarenD3D11ClassInstance) dentro da matriz (Param_MatrizInstanciaClasse).</param>
	static CarenResult VSSetShader(
		ID3D11DeviceContext* Param_MyPointerWork,
		ICarenD3D11VertexShader^ Param_ShaderVertice,
		cli::array<ICarenD3D11ClassInstance^>^ Param_MatrizInstanciaClasse,
		UInt32 Param_NumeroInstanciasClasse);

	/// <summary>
	/// (VSSetShaderResources) - Vincule uma matriz de recursos de sombreamento para a fase de sombreador de vértices.
	/// </summary>
	/// <param name="Param_StartSlot">Index na matriz baseada em zero do dispositivo para começar a configurar os recursos do shader para (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).</param>
	/// <param name="Param_NumeroViews">Número de recursos do shader a serem definidos. Até um máximo de 128 slots estão disponíveis para recursos de sombreador (o intervalo é de 0 a D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - Param_StartSlot).</param>
	/// <param name="Param_MatrizVisualizadoresSombreador">Uma matriz que contém os Visualizadores de recurso do sombreador para serem definidos no Disposiivo.</param>
	static CarenResult VSSetShaderResources(
		ID3D11DeviceContext* Param_MyPointerWork,
		UInt32 Param_StartSlot,
		UInt32 Param_NumeroViews,
		cli::array<ICarenD3D11ShaderResourceView^>^ Param_MatrizVisualizadoresSombreador);
};