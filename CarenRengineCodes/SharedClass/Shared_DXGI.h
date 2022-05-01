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
#include "../SDK_DXGI.h"
#include "../SDK_Caren.h"
#include "../SDK_Utilidades.h"


//Importa o namespace que cont�m as interfaces da API prim�ria.
using namespace CarenRengine::DXGI;

//Importa o namespace (BASE) e suas demais depend�ncias
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

//Importa o namespace de utilidades utilizado pelas classes
using namespace CarenRengine::SDKUtilidades;

/// <summary>
/// 
/// </summary>
class Shared_DXGIObject
{
	//M�todos da interface(ICarenDXGIObject)
public:
	/// <summary>
	/// Recupera o objeto pai deste objeto.
	/// </summary>
	/// <param name="Param_RIIDInterface">A identifica��o da interface solicitada.</param>
	/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usu�rio deve inicializar a interface antes de chamar este m�todo.</param>
	static CarenResult GetParent(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_RIIDInterface, 
		ICaren^ Param_Out_ObjetoPai);

	/// <summary>
	/// Define dados definidos pelo aplicativo para o objeto e associa esses dados a um GUID.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID que identifica os dados. Use esse GUID em uma chamada para o GetPrivateData para obter os dados.</param>
	/// <param name="Param_TamanhoDados">O tamanho dos dados.</param>
	/// <param name="Param_Dados">Ponteiro para os dados.</param>
	static CarenResult SetPrivateData(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidIdentificao, 
		UInt32 Param_TamanhoDados, 
		ICaren^ Param_Dados);

	/// <summary>
	/// Obt�m um ponteiro para os dados do objeto.
	/// </summary>
	/// <param name="Param_GuidIdentificao">Um GUID identificando os dados.</param>
	/// <param name="Param_Ref_TamanhoDados">Retorna o tamanho dos dados.</param>
	/// <param name="Param_Out_Dados">Retorna um ponteiro para os dados. Esse ponteiro pode e n�o pode ser uma interface IUnknown. Sendo uma (IUnknown), o chamador � respons�vel por liberar
	/// a refer�ncia para a interface. O usu�rio deve inicializar a interface antes de chamar este m�todo.</param>
	static CarenResult GetPrivateData(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidIdentificao, 
		UInt32% Param_Ref_TamanhoDados, 
		ICaren^ Param_Out_Dados);

	/// <summary>
	/// Define uma interface nos dados privados do objeto.
	/// </summary>
	/// <param name="Param_GuidInterface">Guid de identifica��o da interface.</param>
	/// <param name="Param_Interface">Um ponteiro para a interface a ser definida.</param>
	static CarenResult SetPrivateDataInterface(
		IDXGIObject* Param_MyPointerWork, 
		String^ Param_GuidInterface, 
		ICaren^ Param_Interface);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIDeviceSubObject
{
	//M�todos da interface(ICarenDXGIDeviceSubObject)
public:
	/// <summary>
	/// Recupera o dispositivo.
	/// </summary>
	/// <param name="Param_RIIDInterface">O ID de refer�ncia para o dispositivo.</param>
	/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usu�rio deve inicializar a interface antes de chamar este m�todo.</param>
	static CarenResult GetDevice(
		IDXGIDeviceSubObject* Param_MyPointerWork, 
		String^ Param_RIIDInterface, 
		ICaren^ Param_Out_Objeto);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIResource
{
	//M�todos da interface(ICarenDXGIResource1)
public:
	/// <summary>
	/// (CreateSharedHandle) - Cria uma Handle para um recurso compartilhado. Em seguida, voc� pode usar a Handle devolvida com v�rios dispositivos Direct3D.
	/// </summary>
	/// <param name="Param_Atributos">Uma estrutura CA_SECURITY_ATTRIBUTES que cont�m dois membros de dados separados, mas relacionados: um descritor de seguran�a opcional e 
	/// um valor booleano que determina se os processos crian�as podem herdar a Handle devolvida.
	/// Defina esse par�metro para NULO se desejar que os processos filhos que o aplicativo possa criar n�o herdem a Handle retornado por CreateSharedHandle e se 
	/// desejar que o recurso associado ao identificador retornado obtenha um descritor de seguran�a padr�o.</param>
	/// <param name="Param_Acesso">Os direitos de acesso solicitados ao recurso. Voc� pode realizar um bitwise entre as enumera��es CA_ACCESS_RIGHTS e CA_DXGI_SHARED_RESOURCE_RW 
	/// para definir esse parametro.</param>
	/// <param name="Param_Nome">O nome do recurso para compartilhar. O nome se limita a constante MAX_PATH. A compara��o de nomes � sens�vel ao caso(CaseSensitive).
	/// Voc� precisar� do nome de recurso se ligar para o m�todo ICarenD3D11Device1::AbrirRecursoCompartilhadoPorNome para acessar o recurso compartilhado pelo nome. Se voc�, 
	/// em vez disso, ligar para o m�todo ICarenD3D11Device1::AbrirRecursoCompartilhado1 para acessar o recurso compartilhado por cabo, defina este par�metro para NULO.</param>
	/// <param name="Param_Out_Handle">Recebe o ponteiro para uma vari�vel que recebe o valor NT HANDLE para o recurso para compartilhar. Voc� pode usar esta Handle em 
	/// chamadas para acessar o recurso.</param>
	static CarenResult CreateSharedHandle(
		IDXGIResource1* Param_MyPointerWork,
		CA_SECURITY_ATTRIBUTES^ Param_Atributos,
		UInt64 Param_Acesso,
		String^ Param_Nome,
		[Out] IntPtr% Param_Out_Handle);

	/// <summary>
	/// (CreateSubresourceSurface) - Cria um objeto de superf�cie subrecurso.
	/// </summary>
	/// <param name="Param_Index">O �ndice do objeto de superf�cie do subrecurso a ser enumerado.</param>
	/// <param name="Param_Out_DXGISurface2">Recebe um ponteiro para uma interface ICarenDXGISurface2 que representa o objeto de superf�cie do subrecurso criado na posi��o 
	/// especificada pelo par�metro (Param_Index).  O usu�rio deve inicializar a interface antes de chamar este m�todo. </param>
	static CarenResult CreateSubresourceSurface(
		IDXGIResource1* Param_MyPointerWork, 
		UInt32 Param_Index, 
		ICaren^ Param_Out_DXGISurface2);



	//M�todos da interface(ICarenDXGIResource)
public:
	/// <summary>
	/// (GetEvictionPriority) - Obtenha a prioridade de despejo.
	/// </summary>
	/// <param name="Param_Out_PrioridadeDespejo">Recebe valores da enumera��o CA_DXGI_RESOURCE_PRIORITY, que determinam quando o recurso pode ser despejado.</param>
	static CarenResult GetEvictionPriority(
		IDXGIResource* Param_MyPointerWork, 
		[Out] CA_DXGI_RESOURCE_PRIORITY% Param_Out_PrioridadeDespejo);

	/// <summary>
	/// (GetSharedHandle) - Obt�m a Handle para um recurso compartilhado.
	/// [A partir do Direct3D 11.1, recomendamos n�o usar o (GetSharedHandle) mais para recuperar a al�a a um recurso compartilhado. Em vez disso, use o 
	/// ICarenDXGIResource1::CreateSharedHandle para obter uma Handle para compartilhar. Para usar o ICarenDXGIResource1::CreateSharedHandle deve especificar 
	/// que ele usa Handle NT (ou seja, voc� define a bandeira CA_D3D11_RESOURCE_MISC_SHARED_NTHANDLE). Tamb�m recomendamos que voc� crie recursos compartilhados que 
	/// usam Handles NT para que voc� possa usar CloseHandle, DuplicateHandle, e assim por diante esses recursos compartilhados.]
	/// </summary>
	/// <param name="Param_Out_SharedHandle">Retorna um ponteiro para a Handle compartilhada.</param>
	static CarenResult GetSharedHandle(
		IDXGIResource* Param_MyPointerWork, 
		[Out] IntPtr% Param_Out_SharedHandle);

	/// <summary>
	/// (GetUsage) - Obtenha o uso esperado de recursos.
	/// </summary>
	/// <param name="Param_Out_Usage">Recebe uma bandeira de uso(DXGI_USAGE). Para direct3D 10, uma superf�cie pode ser usada como entrada sombreadora ou uma sa�da de 
	/// destino renderizado.</param>
	static CarenResult GetUsage(
		IDXGIResource* Param_MyPointerWork, 
		[Out] CA_DXGI_USAGE% Param_Out_Usage);

	/// <summary>
	/// (SetEvictionPriority) - Defina a prioridade para despejar o recurso da mem�ria.
	/// </summary>
	/// <param name="Param_PrioridadeDespejo">Um valor da enumera��o CA_DXGI_RESOURCE_PRIORITY que define a prioridade do despejo.</param>
	static CarenResult SetEvictionPriority(
		IDXGIResource* Param_MyPointerWork, 
		CA_DXGI_RESOURCE_PRIORITY Param_PrioridadeDespejo);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGISurface
{
	//M�todos da interface(ICarenDXGISurface2)
public:
	/// <summary>
	/// (GetResource) - Obt�m o �ndice de recursos parentais e subrecursos que suportam uma superf�cie de subrecursos.
	/// Os objetos atuais que implementam o IDXGISurface s�o recursos ou visualiza��es. GetResource para esses objetos retorna "this" ou o 
	/// recurso que suporta a exibi��o, respectivamente. Nesta situa��o, o �ndice de subrecursos � 0.
	/// </summary>
	/// <param name="Param_RIID">O identificador globalmente �nico (GUID) do tipo de interface solicitado.</param>
	/// <param name="Param_Out_ObjetoRecurso">Recebe um ponteiro para um buffer que recebe um ponteiro para o objeto de recurso pai para a superf�cie do subrecurso.  O usu�rio deve inicializar a interface antes de chamar este m�todo.</param>
	/// <param name="Param_Ref_IndexSubrecurso">Recebe o �ndice da superf�cie do subrecurso.</param>
	static CarenResult GetResource(IDXGISurface2* Param_MyPointerWork, String^ Param_RIID, ICaren^ Param_Out_ObjetoRecurso, UInt32% Param_Ref_IndexSubrecurso);



	//M�todos da interface(ICarenDXGISurface1)
public:
	/// <summary>
	/// (GetDC) - Retorna um contexto de dispositivo (DC) que permite que voc� se torne uma superf�cie de Infraestrutura Gr�fica Microsoft DirectX (DXGI) usando a Interface do Dispositivo Gr�fico windows (GDI).
	/// </summary>
	/// <param name="Param_Descartar">Um valor booleano que especifica se deve preservar o conte�do Direct3D no GDI DC. 
	/// TRUE direciona o tempo de execu��o para n�o preservar o conte�do Direct3D no GDI DC; ou seja, o tempo de execu��o 
	/// descarta o conte�do Direct3D. False garante que o conte�do Direct3D esteja dispon�vel no GDI DC.</param>
	/// <param name="Param_Out_HDCHandle">Recebe um ponteiro para uma Handle(Al�a) HDC que representa o contexto atual do dispositivo para renderiza��o GDI.</param>
	static CarenResult GetDC(IDXGISurface1* Param_MyPointerWork, Boolean Param_Descartar, [Out] IntPtr% Param_Out_HDCHandle);

	/// <summary>
	/// (ReleaseDC) - Libera o contexto do dispositivo GDI (DC) que est� associado � superf�cie atual e permite que voc� use o Direct3D para renderizar.
	/// </summary>
	/// <param name="Param_Regiao">Um ponteiro para uma estrutura rect que identifica a regi�o suja da superf�cie. Uma regi�o suja � qualquer 
	/// parte da superf�cie que voc� usou para renderiza��o GDI e que voc� quer preservar.Esta �rea � usada como uma dica de desempenho para 
	/// subsistema gr�fico em certos cen�rios.N�o utilize este par�metro para restringir a renderiza��o � regi�o retangular especificada. 
	/// Se voc� passar NULO, ReleaseDC considera toda a superf�cie como suja. Caso contr�rio, o (ReleaseDC) usa a �rea especificada pelo CA_RECT
	/// como uma dica de desempenho para indicar quais �reas foram manipuladas pela renderiza��o GDI. Voc� pode passar um ponteiro para uma 
	/// estrutura rect vazia(um ret�ngulo sem posi��o ou �rea) se voc� n�o alterar qualquer conte�do.</param>
	static CarenResult ReleaseDC(IDXGISurface1* Param_MyPointerWork, CA_RECT^ Param_Regiao);



	//M�todos da interface(ICarenDXGISurface)
public:
	/// <summary>
	/// (GetDesc) - M�todo respons�vel por obter uma descri��o da superf�cie.
	/// </summary>
	/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
	static CarenResult GetDesc(IDXGISurface* Param_MyPointerWork, [Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice);

	/// <summary>
	/// (Map) - M�todo respons�vel por obter um ponteiro para os dados contidos na superf�cie e negue o acesso da GPU � superf�cie.
	/// </summary>
	/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
	/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que cont�m os dados mapeados da superfice.</param>
	static CarenResult Map(IDXGISurface* Param_MyPointerWork, CA_DXGI_MAP_FLAGS Param_Flags, [Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado);

	/// <summary>
	/// (Unmap) - M�todo respons�vel por invalidar o ponteiro para a superf�cie recuperada pelo ICarenDXGISurface::Map e 
	/// reativar o acesso GPU ao recurso.
	/// </summary>
	static CarenResult Unmap(IDXGISurface* Param_MyPointerWork);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIOutput
{
	//M�todos da interface(ICarenDXGIOutput6)
public:
	/// <summary>
	/// (CheckHardwareCompositionSupport) - Notifica aplicativos de que o alongamento de hardware � suportado.
	/// </summary>
	/// <param name="Param_Out_FlagsSuporte">Retorna um bitfield de CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS valores de 
	/// enumera��o descrevendo quais tipos de composi��o de hardware s�o suportados. Os valores s�o bitwise OR juntos.</param>
	static CarenResult CheckHardwareCompositionSupport(
		IDXGIOutput6* Param_MyPointerWork,
		[Out] CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS% Param_Out_FlagsSuporte);

	/// <summary>
	/// (GetDesc1) - Obt�m uma descri��o estendida da sa�da que inclui caracter�sticas de cores e tipo de conex�o.
	/// </summary>
	/// <param name="Param_Out_Desc">Retorna uma estrutura com a descri��o da saida.</param>
	static CarenResult GetDesc1(
		IDXGIOutput6* Param_MyPointerWork, 
		[Out] CA_DXGI_OUTPUT_DESC1^% Param_Out_Desc);



	//M�todos da interface(ICarenDXGIOutput5)
public:
	/// <summary>
	/// Permite especificar uma lista de formatos suportados para superf�cies fullscreen que podem ser devolvidas pelo objeto ICarenDXGIOutputDuplication.
	/// </summary>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que voc� pode usar para 
	/// processar a imagem da �rea de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a sa�da 
	/// est� conectada.</param>
	/// <param name="Param_Flags">Reservado para uso futuro. Deixe como 0.</param>
	/// <param name="Param_QuantidadeFormatosSuportados">Especifica o n�mero de formatos suportados.</param>
	/// <param name="Param_ListaFormatosSuportados">Uma matriz de formatos suportados que tem como contagem igual a (Param_QuantidadeFormatosSuportados).</param>
	/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
	static CarenResult DuplicateOutput1(
		IDXGIOutput5* Param_MyPointerWork,
		ICaren^ Param_Dispositivo3D,
		UInt32 Param_Flags,
		UInt32 Param_QuantidadeFormatosSuportados,
		cli::array<CA_DXGI_FORMAT>^ Param_ListaFormatosSuportados,
		[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada);



	//M�todos da interface(ICarenDXGIOutput4)
public:
	/// <summary>
	/// (CheckOverlayColorSpaceSupport) - Verifica se h� suporte ao espa�o de cores.
	/// </summary>
	/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
	/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE digitado que especifica o tipo de espa�o de cor 
	/// para verificar o suporte de sobreposi��o.</param>
	/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O 
	/// (CheckOverlayColorSpaceSupport) retorna apenas informa��es de suporte sobre este dispositivo de varredura.</param>
	/// <param name="Param_Out_Flags">Recebe uma vari�vel que recebe uma combina��o de valores tipo tipo de 
	/// CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG que s�o combinados usando uma opera��o ou bitwise. O valor resultante 
	/// especifica op��es para suporte ao espa�o de cores sobreposi��o.</param>
	static CarenResult CheckOverlayColorSpaceSupport(
		IDXGIOutput4* Param_MyPointerWork,
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace,
		ICaren^ Param_DispositivoD3D,
		[Out] CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG% Param_Out_Flags);



	//M�todos da interface(ICarenDXGIOutput3)
public:
	/// <summary>
	/// (CheckOverlaySupport) - Verifica o apoio ao Overlay(Sobrepor).
	/// </summary>
	/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
	/// <param name="Param_DispositivoD3D">Um ponteiro para a interface do dispositivo Direct3D. O (CheckOverlaySupport)
	/// retorna apenas informa��es de suporte sobre este dispositivo de varredura.</param>
	/// <param name="Param_Out_Flags">Recebe uma vari�vel que recebe uma combina��o de valores digitados 
	/// CA_DXGI_OVERLAY_SUPPORT_FLAGque s�o combinados usando uma opera��o ou bitwise. O valor resultante especifica 
	/// op��es de suporte sobreposi��o.</param>
	static CarenResult CheckOverlaySupport(
		IDXGIOutput3* Param_MyPointerWork,
		CA_DXGI_FORMAT Param_Formato,
		ICaren^ Param_DispositivoD3D,
		[Out] CA_DXGI_OVERLAY_SUPPORT_FLAG% Param_Out_Flags);



	//M�todos da interface(ICarenDXGIOutput2)
public:
	/// <summary>
	/// (SupportsOverlays) - Consulta uma sa�da de adaptador para suporte de sobreposi��o multiplano.
	/// </summary>
	/// <param name="Param_Out_Suporte">Recebe TRUE se o adaptador de sa�da � o adaptador prim�rio e suporta sobreposi��es multiplan�rias, caso 
	/// contr�rio retorna FALSE.</param>
	static CarenResult SupportsOverlays(
		IDXGIOutput2* Param_MyPointerWork, 
		[Out] Boolean Param_Out_Suporte);


	//M�todos da interface(ICarenDXGIOutput1)
public:
	/// <summary>
	/// (DuplicateOutput) - Cria uma interface de duplica��o de desktop a partir da interface ICarenDXGIOutput1 que representa uma sa�da de 
	/// adaptador.
	/// </summary>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D que voc� pode usar para processar a imagem da �rea de trabalho. Este dispositivo deve ser criado a partir do adaptador ao qual a sa�da est� conectada.</param>
	/// <param name="Param_Out_SaidaDuplicada">Recebe um ponteiro da interface para a nova saida duplicada.</param>
	static CarenResult DuplicateOutput(
		IDXGIOutput1* Param_MyPointerWork, 
		ICaren^ Param_Dispositivo3D, 
		[Out] ICarenDXGIOutputDuplication^% Param_Out_SaidaDuplicada);

	/// <summary>
	/// (FindClosestMatchingMode1) - Encontra o modo de exibi��o que mais combina com o modo de exibi��o solicitado.
	/// </summary>
	/// <param name="Param_DescCombine">Uma estrutura CA_DXGI_MODE_DESC1 que descreve o modo de exibi��o para combinar. Os membros da CA_DXGI_MODE_DESC1 
	/// podem ser n�o especificados, o que indica que n�o h� prefer�ncia por esse membro. Um valor de 0 para Largura ou Altura indica que o valor
	/// n�o est� especificado. Se largura ou altura for 0, ambos devem ser 0. Um numerador e denominador de 0 no RefreshRate indicam que ele n�o 
	/// est� especificado. Outros membros do CA_DXGI_MODE_DESC1 possuem valores de enumera��o que indicam que o membro n�o est� especificado. 
	/// Se o (Param_Dispositivo3D) for NULO, o membro (Formato) em CA_DXGI_MODE_DESC1 n�o pode ser CA_DXGI_FORMAT_UNKNOWN.</param>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este par�metro for NULO, o (FindClosestMatchingMode1) 
	/// retorna apenas modos cujo formato corresponde ao do Param_DescCombine; caso contr�rio, o (FindClosestMatchingMode1) retorna apenas 
	/// aos formatos suportados para escaneamento pelo dispositivo.</param>
	/// <param name="Param_Out_DescCorrespondente"> Recebe uma estrutura CA_DXGI_MODE_DESC1 que cont�m uma descri��o do modo de exibi��o que 
	/// mais corresponde ao modo de exibi��o descrito no Param_DescCombine.</param>
	static CarenResult FindClosestMatchingMode1(
		IDXGIOutput1* Param_MyPointerWork,
		CA_DXGI_MODE_DESC1^ Param_DescCombine,
		ICaren^ Param_Dispositivo3D,
		[Out] CA_DXGI_MODE_DESC1^% Param_Out_DescCorrespondente);

	/// <summary>
	/// (GetDisplayModeList1) - Obt�m os modos de exibi��o que correspondem ao formato solicitado e outras op��es de entrada.
	/// </summary>
	/// <param name="Param_Formato">Um valor CA_DXGI_FORMAT digitado para o formato de cor.</param>
	/// <param name="Param_Flags">Uma combina��o de valores CA_DXGI_ENUM_MODES digitados que s�o combinados usando uma opera��o ou bitwise. O valor 
	/// resultante especifica op��es para modos de exibi��o para incluir. Voc� deve especificar CA_DXGI_ENUM_MODES_SCALING para expor os modos 
	/// de exibi��o que requerem dimensionamento. Os modos centrados que n�o requerem escala e correspondem diretamente � sa�da do display s�o 
	/// enumerados por padr�o.</param>
	/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o n�mero de modos de exibi��o. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
	/// <param name="Param_Ref_QuantidadeModos">Recebe o n�mero de modos de exibi��o que o (GetDisplayModeList1) retorna no bloco de mem�ria
	/// para o qual o (Param_Out_MatrizDescModos) aponta. Defina (Param_Out_MatrizDescModos) para NULO para que o (Param_Ref_QuantidadeModos) 
	/// retorne o n�mero de modos de exibi��o que correspondam ao formato e �s op��es. Caso contr�rio, o (Param_Ref_QuantidadeModos) retorna o 
	/// n�mero de modos de exibi��o devolvidos no (Param_Out_MatrizDescModos).</param>
	/// <param name="Param_Out_MatrizDescModos">Recebe uma lista de modos de exibi��o.</param>
	static CarenResult GetDisplayModeList1(
		IDXGIOutput1* Param_MyPointerWork,
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_ENUM_MODES Param_Flags,
		Boolean Param_RecuperaQuantidadeModos,
		UInt32% Param_Ref_QuantidadeModos,
		[Out] cli::array<CA_DXGI_MODE_DESC1^>^% Param_Out_MatrizDescModos);

	/// <summary>
	/// (GetDisplaySurfaceData1) - Copia a superf�cie do display(buffer frontal) para um recurso fornecido pelo usu�rio.
	/// </summary>
	/// <param name="Param_SuperficeDestino">Um interface de recurso que representa o recurso para o qual o 
	/// (GetDisplaySurfaceData1) copia a superf�cie do display. A interface n�o pode ser NULA e deve reprentar uma textura 2D da interface( ICarenD3D11Texture2D)</param>
	static CarenResult GetDisplaySurfaceData1(
		IDXGIOutput1* Param_MyPointerWork, 
		ICarenDXGIResource^ Param_SuperficeDestino);



	//M�todos da interface(ICarenDXGIOutput)
public:
	/// <summary>
	/// (FindClosestMatchingMode) - Encontra o modo de exibi��o que mais se corresponde ao modo de exibi��o solicitado.
	/// </summary>
	/// <param name="Param_ModoDesc">O modo de exibi��o desejado (veja DXGI_MODE_DESC). Os membros do CA_DXGI_MODE_DESC n�o podem ser especificados indicando nenhuma prefer�ncia por esse membro. Um valor de 0 para largura ou altura indica 
	/// que o valor n�o � especificado. Se a largura ou a altura forem 0, ambas devem ser 0. Um numerador e denominador de 0 em RefreshRate indicam que n�o � especificado. Outros membros da DXGI_MODE_DESC t�m valores de enumera��o indicando 
	/// que o membro n�o � especificado. Se (Param_Dispositivo3D) � NULO, formaton�o pode ser DXGI_FORMAT_UNKNOWN.</param>
	/// <param name="Param_Out_ModoMaisAproximado">O modo que mais se aproxima do (Param_ModoDesc).</param>
	/// <param name="Param_Dispositivo3D">Um ponteiro para a interface do dispositivo Direct3D. Se este par�metro � NULO, apenas modos cujo formato corresponde ao do (Param_ModoDesc) ser�o devolvidos; caso contr�rio, apenas os formatos que 
	/// s�o suportados para digitaliza��o pelo dispositivo s�o devolvidos.</param>
	static CarenResult FindClosestMatchingMode(
		IDXGIOutput* Param_MyPointerWork, 
		CA_DXGI_MODE_DESC^ Param_ModoDesc, 
		[Out] CA_DXGI_MODE_DESC^% Param_Out_ModoMaisAproximado, 
		ICaren^ Param_Dispositivo3D);

	/// <summary>
	/// (GetDesc) - Obter uma descri��o da sa�da.
	/// </summary>
	/// <param name="Param_Out_DescSaida">Retorna uma estrutura que cont�m a descri��o da saida.</param>
	static CarenResult GetDesc(
		IDXGIOutput* Param_MyPointerWork, 
		[Out] CA_DXGI_OUTPUT_DESC^% Param_Out_DescSaida);

	/// <summary>
	/// (GetDisplayModeList) - Obt�m os modos de exibi��o que correspondem ao formato solicitado e outras op��es de entrada.
	/// </summary>
	/// <param name="Param_Formato">O formato de cor.</param>
	/// <param name="Param_Flags">Op��es para os modos de incluir. DXGI_ENUM_MODES_SCALING precisa ser especificado para expor os modos de exibi��o que exigem escala. Os modos centrados, que n�o exigem escala e correspondentes diretamente � 
	/// sa�da da tela, s�o enumerados por padr�o.</param>
	/// <param name="Param_Ref_QuantidadeModos">Na entrada define a quantidade de dados que seram retornadados na matriz (Param_Out_MatrizDescModos). Na saida cont�m a quantidade de dados de (Param_Out_MatrizDescModos).</param>
	/// <param name="Param_RecuperaQuantidadeModos">Defina para TRUE para obter o n�mero de modos de exibi��o. Se TRUE, Param_Out_MatrizDescModos retorna NULO e (Param_QuantidadeModos) retorna a quantidade total de modos.</param>
	/// <param name="Param_Out_MatrizDescModos">Retorna uma lista de modos de exibi��o.</param>
	static CarenResult GetDisplayModeList(
		IDXGIOutput* Param_MyPointerWork,
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_ENUM_MODES Param_Flags,
		Boolean Param_RecuperaQuantidadeModos,
		UInt32% Param_Ref_QuantidadeModos,
		[Out] cli::array<CA_DXGI_MODE_DESC^>^% Param_Out_MatrizDescModos);

	/// <summary>
	/// (GetDisplaySurfaceData) - Obt�m uma c�pia da superf�cie de exibi��o atual.
	/// O m�todo s� pode ser chamado quando uma sa�da est� no modo de tela cheia. Se o m�todo for bem-sucedido, a DXGI preenche a superf�cie do destino.
	/// </summary>
	/// <param name="Param_SuperficeDestino">Um ponteiro para uma superf�cie de destino que vai receber a superfice.</param>
	static CarenResult GetDisplaySurfaceData(
		IDXGIOutput* Param_MyPointerWork, 
		ICarenDXGISurface^% Param_SuperficeDestino);

	/// <summary>
	/// (GetFrameStatistics) - Obt�m estat�sticas sobre quadros recentemente renderizados.
	/// </summary>
	/// <param name="Param_Out_EstatisticasFrame">Retorna uma estrutura com as informa��es.</param>
	static CarenResult GetFrameStatistics(
		IDXGIOutput* Param_MyPointerWork, 
		[Out] CA_DXGI_FRAME_STATISTICS^% Param_Out_EstatisticasFrame);

	/// <summary>
	/// (GetGammaControl) - Obt�m as configura��es de controle gama.
	/// </summary>
	/// <param name="Param_Out_ControleGamma">Retorna uma estrutura que cont�m as informa��es do controle gamma.</param>
	static CarenResult GetGammaControl(
		IDXGIOutput* Param_MyPointerWork, 
		[Out] CA_DXGI_GAMMA_CONTROL^% Param_Out_ControleGamma);

	/// <summary>
	/// (GetGammaControlCapabilities) - Obt�m uma descri��o das capacidades de controle gama.
	/// </summary>
	/// <param name="Param_Out_GammaCaps">Retorna uma estrutura que cont�m as descri��es das capcidades do controle Gamma.</param>
	static CarenResult GetGammaControlCapabilities(
		IDXGIOutput* Param_MyPointerWork, 
		[Out] CA_DXGI_GAMMA_CONTROL_CAPABILITIES^% Param_Out_GammaCaps);

	/// <summary>
	/// (ReleaseOwnership) - Libera a propriedade da sa�da.
	/// </summary>
	static CarenResult ReleaseOwnership(IDXGIOutput* Param_MyPointerWork);

	/// <summary>
	/// (SetDisplaySurface) - Altera o modo de exibi��o.
	/// </summary>
	/// <param name="Param_Superfice">Um ponteiro para uma superf�cie usado para renderizar uma imagem para a tela. A superf�cie deve ter sido criada como um amortecedor traseiro (DXGI_USAGE_BACKBUFFER).</param>
	static CarenResult SetDisplaySurface(
		IDXGIOutput* Param_MyPointerWork, 
		ICarenDXGISurface^% Param_Superfice);

	/// <summary>
	/// (SetGammaControl) - Define os controles gama.
	/// </summary>
	/// <param name="Param_ControleGama">Uma estrutura CA_DXGI_GAMMA_CONTROL que descreve a curva gama a ser definida.</param>
	static CarenResult SetGammaControl(
		IDXGIOutput* Param_MyPointerWork, 
		CA_DXGI_GAMMA_CONTROL^ Param_ControleGama);

	/// <summary>
	/// (TakeOwnership) - Toma posse de uma sa�da. Quando voc� terminar com a sa�da, chame o m�todo ICarenDXGIOutput::ReleaseOwnership().
	/// Este m�todo n�o deve ser chamado diretamente por aplicativos, uma vez que os resultados ser�o imprevis�veis. � chamado implicitamente pelo objeto da cadeia de swap DXGI durante as transi��es em tela cheia, e n�o deve ser usado como 
	/// um substituto para m�todos de cadeia de swap.
	/// </summary>
	/// <param name="Param_DispositivoD3D">Um ponteiro para a interface IUnknown de um dispositivo do Direct3D.</param>
	/// <param name="Param_Exclusivo">Definido para TRUE para permitir que outros t�picos ou aplicativos para assumir a propriedade do dispositivo; caso contr�rio, definido como FALSE.</param>
	static CarenResult TakeOwnership(
		IDXGIOutput* Param_MyPointerWork, 
		ICaren^ Param_DispositivoD3D, 
		Boolean Param_Exclusivo);

	/// <summary>
	/// (WaitForVBlank ) - Pare um Thread at� que o pr�ximo espa�o em branco vertical ocorra.
	/// </summary>
	static CarenResult WaitForVBlank(IDXGIOutput* Param_MyPointerWork);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIAdapter
{
	//Métodos da interface(ICarenDXGIAdapter4)
public:
	/// <summary>
	/// (GetDesc3) - Obtém uma descrição 1.6 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. Esta descrição inclui 
	/// informações sobre compatibilidade com ACG.
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Recebe uma estrutura CA_DXGI_ADAPTER_DESC3 que descreve o adaptador. Este parâmetro não deve ser NULO. No hardware gráfico nível 9, 
	/// versões iniciais do GetDesc3(GetDesc1 GetDesc) retornam zeros para o ID PCI em (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do 
	/// adaptador e "Adaptador de Software" para a string de descrição no membro (Description). GetDesc3 e GetDesc2 retornam os valores reais de hardware nível 9 
	/// nesses membros.</param>
	static CarenResult GetDesc3(IDXGIAdapter4* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC3^% Param_Out_DescAdaptador);



	//Métodos da interface(ICarenDXGIAdapter3)
public:
	/// <summary>
	/// (QueryVideoMemoryInfo) - Este método informa o processo de uso do orçamento e do processo atual.
	/// </summary>
	/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações da memória de vídeo são consultadas. Para operação de GPU única, coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de vídeo são consultadas.</param>
	/// <param name="Param_GrupoSegmento">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
	/// <param name="Param_Out_InfoMemoria">Recebe uma estrutura CA_DXGI_QUERY_VIDEO_MEMORY_INFO com os valores atuais.</param>
	static CarenResult QueryVideoMemoryInfo(
		IDXGIAdapter3* Param_MyPointerWork,
		UInt32 Param_NodeId,
		CA_DXGI_MEMORY_SEGMENT_GROUP Param_GrupoSegmento,
		[Out] CA_DXGI_QUERY_VIDEO_MEMORY_INFO^% Param_Out_InfoMemoria);

	/// <summary>
	/// (RegisterHardwareContentProtectionTeardownStatusEvent) - Se registra para receber notificação de eventos de proteção de proteção de conteúdo de hardware.
	/// </summary>
	/// <param name="Param_Evento">Uma Handle para o objeto de evento que o sistema operacional define quando ocorre o (TearDown) de proteção de conteúdo de hardware. </param>
	/// <param name="Param_Out_Cookie">um valor-chave que um aplicativo pode passar para o método ICarenDXGIAdapter3:::UnregisterHardwareContentProtectionTeardownStatus para 
	/// descadastrar o evento de notificação que o Param_Evento especifica.</param>
	static CarenResult RegisterHardwareContentProtectionTeardownStatusEvent(IDXGIAdapter3* Param_MyPointerWork, ICarenEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

	/// <summary>
	/// (RegisterVideoMemoryBudgetChangeNotificationEvent) - Este método estabelece uma correlação entre um objeto de sincronização da CPU e o evento de mudança orçamentária.
	/// </summary>
	/// <param name="Param_Evento">Uma Handle para o objeto de evento.</param>
	/// <param name="Param_Out_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent
	/// retorna esse valor.</param>
	static CarenResult RegisterVideoMemoryBudgetChangeNotificationEvent(IDXGIAdapter3* Param_MyPointerWork, ICarenEvent^ Param_Evento, [Out] UInt32 Param_Out_Cookie);

	/// <summary>
	/// (SetVideoMemoryReservation) - Este método envia a memória física mínima necessária para uma aplicação, para o Sistema Operacional.
	/// </summary>
	/// <param name="Param_NodeId">Especifica o adaptador físico do dispositivo para o qual as informações de memória de vídeo estão sendo definidas. Para operação de GPU única, 
	/// coloque isso em zero. Se houver vários nós da GPU, coloque isso no índice do nó (adaptador físico do dispositivo) para o qual as informações de memória de 
	/// vídeo estão sendo definidas.</param>
	/// <param name="Param_SegmentoGrupoMemoria">Especifica uma CA_DXGI_MEMORY_SEGMENT_GROUP que identifica o grupo como local ou não local.</param>
	/// <param name="Param_ReversaMemoria">Especifica um UInt64 que define a memória física mínima necessária, em bytes.</param>
	static CarenResult SetVideoMemoryReservation(
		IDXGIAdapter3* Param_MyPointerWork,
		UInt32 Param_NodeId,
		CA_DXGI_MEMORY_SEGMENT_GROUP Param_SegmentoGrupoMemoria,
		UInt64 Param_ReversaMemoria);

	/// <summary>
	/// (UnregisterHardwareContentProtectionTeardownStatus) - O Desregistra(Cancelar) um evento para impedi-lo de receber a notificação de eventos de proteção de 
	/// conteúdo de hardware.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
	/// retorna esse valor.</param>
	static CarenResult UnregisterHardwareContentProtectionTeardownStatus(IDXGIAdapter3* Param_MyPointerWork, UInt32 Param_Cookie);

	/// <summary>
	/// (UnregisterVideoMemoryBudgetChangeNotification) - Este método deixa de notificar um objeto de sincronização da CPU sempre que ocorre uma mudança orçamentária. Um aplicativo pode mudar para a votação regular das informações.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para descadastrar. O método ICarenDXGIAdapter3::RegisterHardwareContentProtectionTeardownStatusEvent 
	/// retorna esse valor.</param>
	static CarenResult UnregisterVideoMemoryBudgetChangeNotification(IDXGIAdapter3* Param_MyPointerWork, UInt32 Param_Cookie);


	//Métodos da interface(ICarenDXGIAdapter2)
public:
	/// <summary>
	/// (GetDesc2) - Obtém uma descrição 1.2 da Microsoft DirectX Graphics Infrastructure (DXGI) de um adaptador ou placa de vídeo. 
	/// Esta descrição inclui informações sobre a granularidade em que a unidade de processamento gráfico (GPU) pode ser impedida de realizar 
	/// sua tarefa atual.
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC2 que descreve o adaptador. Este parâmetro não deve ser 
	/// NULO.No hardware gráfico nível 9, versões anteriores do GetDesc2(GetDesc e GetDesc1) retorna zero para o 
	/// PCI ID em e (VendorId, DeviceId, SubSysId, e Revision) da estrutura de descrição do adaptador e "Adaptador de Software" para a descrição 
	/// do membro (Description). O GetDesc2 retorna os valores reais de hardware nível 9 nesses membros.</param>
	static CarenResult GetDesc2(IDXGIAdapter2* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC2^% Param_Out_DescAdaptador);


	//Métodos da interface(ICarenDXGIAdapter1)
public:
	/// <summary>
	/// (GetDesc1) - Obtém uma descrição DXGI 1.1 de um adaptador (ou cartão de vídeo).
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC1 que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc1) retorna zeros para o 
	/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC1 e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
	static CarenResult GetDesc1(IDXGIAdapter1* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC1^% Param_Out_DescAdaptador);



	//Métodos da interface(ICarenDXGIAdapter)
public:
	/// <summary>
	/// (CheckInterfaceSupport) - Verifica se o sistema suporta uma interface do dispositivo para um componente gráfico.
	/// </summary>
	/// <param name="Param_GuidInterface">O GUID da interface da versão do dispositivo para a qual o suporte está sendo verificado.</param>
	/// <param name="Param_Out_UMDVersion">A versão do motorista do modo de usuário do (Param_GuidInterface). Isso só é devolvido se a interface for suportada, caso contrário, este parâmetro será -12354.</param>
	static CarenResult CheckInterfaceSupport(IDXGIAdapter* Param_MyPointerWork, String^ Param_GuidInterface, [Out] Int64% Param_Out_UMDVersion);

	/// <summary>
	/// (EnumOutputs) - Saídas de adaptador enumerado (cartão de vídeo).
	/// </summary>
	/// <param name="Param_IndexSaida">O índice da saída.</param>
	/// <param name="Param_Out_Saida">O endereço de um ponteiro para uma interface ICarenDXGIOutput na posição especificada pelo parâmetro (Param_IndexSaida).</param>
	static CarenResult EnumOutputs(IDXGIAdapter* Param_MyPointerWork, UInt32 Param_IndexSaida, [Out] ICarenDXGIOutput^% Param_Out_Saida);

	/// <summary>
	/// (GetDesc) - Obtém uma descrição DXGI 1.0 de um adaptador (ou cartão de vídeo).
	/// </summary>
	/// <param name="Param_Out_DescAdaptador">Retorna uma estrutura CA_DXGI_ADAPTER_DESC que descreve o adaptador. No hardware gráfico de nível 9 de recurso, o (GetDesc) retorna zeros para o 
	/// PCI ID no VendorId, DeviceId, SubSysId e membros de revisão de CA_DXGI_ADAPTER_DESC e "Adaptador de Software" para a sequencia de descrição no membro Description.</param>
	static CarenResult GetDesc(IDXGIAdapter* Param_MyPointerWork, [Out] CA_DXGI_ADAPTER_DESC^% Param_Out_DescAdaptador);
};