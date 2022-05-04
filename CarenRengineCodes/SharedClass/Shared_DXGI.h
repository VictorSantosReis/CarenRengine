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

/// <summary>
/// 
/// </summary>
class Shared_DXGISwapChain
{
	//Métodos da interface(ICarenDXGISwapChain4)
public:
	/// <summary>
	/// (SetHDRMetaData) - Este método estabelece metadados de cabeçalho High Dynamic Range (HDR) e Wide Color Gamut (WCG).
	/// </summary>
	/// <param name="Param_MetadataType">Especifica um membro da enumeração CA_DXGI_HDR_METADATA_TYPE.</param>
	/// <param name="Param_Size">Especifica o tamanho do (Param_Metadata), em bytes.</param>
	/// <param name="Param_Metadata">Especifica um ponteiro vazio que faz referência aos metadados, se ele existe.</param>
	static CarenResult SetHDRMetaData(
		IDXGISwapChain4* Param_MyPointerWork,
		CA_DXGI_HDR_METADATA_TYPE Param_MetadataType,
		UInt32 Param_Size,
		ICaren^ Param_Metadata);


	//Métodos da interface(ICarenDXGISwapChain3)
public:
	/// <summary>
	/// (CheckColorSpaceSupport) - Verifica o suporte da cadeia de swap para espaço de cores.
	/// </summary>
	/// <param name="Param_ColorSpace">Um valor CA_DXGI_COLOR_SPACE_TYPE que especifica o tipo de espaço de cor para verificar o suporte.</param>
	/// <param name="Param_Out_ColorSpaceSuporte">Recebe Zero ou mais bandeiras da enumeração CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG são combinados usando uma operação ou 
	/// bitwise. O valor resultante especifica opções de suporte ao espaço colorido.</param>
	static CarenResult CheckColorSpaceSupport(
		IDXGISwapChain3* Param_MyPointerWork, 
		CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace, 
		[Out] CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG% Param_Out_ColorSpaceSuporte);

	/// <summary>
	/// (GetCurrentBackBufferIndex) - Obtém o índice do buffer atual da cadeia de swap.
	/// </summary>
	/// <param name="Param_Out_IndexBackBuffer">Retorna o indice do buffer traseiro(BackBuffer) atual.</param>
	static CarenResult GetCurrentBackBufferIndex(
		IDXGISwapChain3* Param_MyPointerWork, 
		[Out] UInt32% Param_Out_IndexBackBuffer);

	/// <summary>
	/// (ResizeBuffers1) - Altera o tamanho do buffer traseiro da cadeia de swap, formato e número de buffers, onde a cadeia de swap foi criada usando uma fila de 
	/// comando D3D12 como um dispositivo de entrada. Isso deve ser chamado quando a janela de aplicação for redimensionada.
	/// </summary>
	/// <param name="Param_CountBuffer">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e frontais). Este número pode ser diferente do número de 
	/// buffers com os quais você criou a cadeia de swap. Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o 
	/// número existente de buffers na cadeia de swap. Você não pode especificar menos de dois buffers para o modelo de apresentação flip.</param>
	/// <param name="Param_Largura">A nova largura do buffer traseiro. Se você especificar zero, o DXGI usará a largura da área do cliente da janela de destino. Você não pode 
	/// especificar a largura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
	/// <param name="Param_Altura">A nova altura do tampão traseiro. Se você especificar zero, o DXGI usará a altura da área do cliente da janela de destino. Você não pode 
	/// especificar a altura como zero se você chamou o método ICarenDXGIFactory2::CreateSwapChainForComposition para criar a cadeia de swap para uma superfície de composição.</param>
	/// <param name="Param_Formato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN preservar o formato existente do buffer traseiro. O modelo 
	/// de apresentação flip suporta um conjunto mais restrito de formatos do que o modelo de transferência de bit-block (bitblt).</param>
	/// <param name="Param_SwapChainFlags">Uma combinação de valores da enumeração CA_valoresDXGI_SWAP_CHAIN_FLAG que são combinados usando uma operação ou bitwise. O valor 
	/// resultante especifica opções para comportamento em cadeia de swap.</param>
	/// <param name="Param_ArrayNodeMask">Uma matriz de UInt32, de tamanho total Param_CountBuffer, onde o valor indica em qual nó o buffer traseiro deve ser criado. Buffers 
	/// criados usando ResizeBuffers1 com um conjunto (Param_ArrayNodeMask) não-nulo são visíveis para todos os nós.</param>
	/// <param name="Param_ArrayD3D12CommandQueue">Uma série de filas de comando (ID3D12CommandQueue), de tamanho total Param_CountBuffer. Cada fila fornecida deve coincidir com a 
	/// máscara de nó de criação correspondente especificada na matriz Param_ArrayNodeMask. Quando o (ICarenDXGISwapChain::Apresentar) é chamado, além de girar para o próximo 
	/// buffer para o próximo quadro, a cadeia de swap também girará através dessas filas de comando. Isso permite que o aplicativo controle qual fila requer sincronização para 
	/// uma determinada operação presente.</param>
	static CarenResult ResizeBuffers1(
		IDXGISwapChain3* Param_MyPointerWork,
		UInt32 Param_CountBuffer,
		UInt32 Param_Largura,
		UInt32 Param_Altura,
		CA_DXGI_FORMAT Param_Formato,
		CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags,
		cli::array<UInt32>^ Param_ArrayNodeMask,
		cli::array<ICaren^>^ Param_ArrayD3D12CommandQueue);

	/// <summary>
	/// (SetColorSpace1) - Define o espaço de cores usado pela cadeia de swap.
	/// </summary>
	/// <param name="Param_ColorSpace">Um valor de CA_DXGI_COLOR_SPACE_TYPE que especifica o espaço de cores para definir.</param>
	static CarenResult SetColorSpace1(
		IDXGISwapChain3* Param_MyPointerWork, 
		CA_DXGI_COLOR_SPACE_TYPE Param_ColorSpace);



	//Métodos da interface(ICarenDXGISwapChain2)
public:
	/// <summary>
	/// (GetFrameLatencyWaitableObject) - Retorna uma Handle aguardavel que sinaliza quando o adaptador DXGI terminar de apresentar um novo quadro.
	/// O Windows 8.1 introduz novas APIs que permitem renderização de menor latência esperando até que o quadro anterior seja apresentado ao display antes de desenhar o 
	/// quadro seguinte. Para usar este método, primeiro crie a cadeia de swap DXGI com o conjunto de bandeiras CA_DXGI_SWAP_CHAIN_FLAG::CA_DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT, 
	/// em seguida, ligue para GetFrameLatencyWaitableObject para recuperar a handle aguardavel. Chame o método ICarenEvent::AguardarObjetoUnicoEx para sincronizar a 
	/// renderização de cada novo quadro com o final do quadro anterior. Para cada quadro que renderiza, o aplicativo deve esperar por essa alça antes de iniciar qualquer operação 
	/// de renderização.
	/// </summary>
	/// <param name="Param_Out_HandleEvento">Recebe a interface que gerencia a Handle aguardavel.</param>
	static CarenResult GetFrameLatencyWaitableObject(
		IDXGISwapChain2* Param_MyPointerWork, 
		[Out] ICarenEvent^% Param_Out_HandleEvento);

	/// <summary>
	/// (GetMatrixTransform) - Obtém a matriz de transformação que será aplicada a uma cadeia de troca de composição no proximo (Present).
	/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel,
	/// que pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
	/// Os métodos GetMatrixTransform e SetMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
	/// Apenas elementos simples de escala/tradução na matriz são permitidos - a chamada falhará se a matriz contiver elementos de distorção/rotação.
	/// </summary>
	/// <param name="Param_Out_Matriz_32"></param>
	static CarenResult GetMatrixTransform(
		IDXGISwapChain2* Param_MyPointerWork, 
		[Out] CA_DXGI_MATRIX_3X2_F^% Param_Out_Matriz_32);

	/// <summary>
	/// (GetMaximumFrameLatency) - Obtém o número de quadros que a cadeia de swap pode enfileirar para renderização.
	/// </summary>
	/// <param name="Param_Out_LatenciaMaxima">Recebe o número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Esse valor é 1 por padrão, 
	/// mas deve ser definido para 2 se a cena demorar mais do que leva para uma atualização vertical (normalmente cerca de 16ms) para desenhar.</param>
	static CarenResult GetMaximumFrameLatency(
		IDXGISwapChain2* Param_MyPointerWork, 
		[Out] UInt32% Param_Out_LatenciaMaxima);

	/// <summary>
	/// (GetSourceSize) - Obtém a região de origem é usada para a cadeia de swap.
	/// Use o (GetSourceSize) para obter a parte da cadeia de swap da qual o sistema operacional apresenta. O retângulo de origem é sempre definido pela região 
	/// [0, 0, Largura, Altura]. Use o (SetSourceSize) para definir esta parte da cadeia de swap.
	/// </summary>
	/// <param name="Param_Out_Largura">Recebe a largura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 até a largura geral da cadeia de swap.</param>
	/// <param name="Param_Out_Altura">Recebe a altura atual da região de origem da cadeia de swap. Esse valor pode variar de 1 a altura global da cadeia de swap.</param>
	static CarenResult GetSourceSize(
		IDXGISwapChain2* Param_MyPointerWork, 
		[Out] UInt32% Param_Out_Largura, 
		[Out] UInt32% Param_Out_Altura);

	/// <summary>
	/// (SetMatrixTransform) - Define a matriz de transformação que será aplicada a uma cadeia de troca de composição no próximo (Present).
	/// A partir do Windows 8.1, os aplicativos da Windows Store são capazes de colocar os visuais da cadeia de swap DirectX em páginas XAML usando o elemento SwapChainPanel, que 
	/// pode ser colocado e dimensionado arbitrariamente. Isso expõe os visuais da cadeia de swap DirectX a cenários de dimensionamento e tradução usando UI sensível ao toque. 
	/// Os métodos GetMatrixTransform e SetMatrixTransform são usados para sincronizar o dimensionamento da cadeia de swap DirectX com seu elemento SwapChainPanel associado. 
	/// Apenas elementos simples de escala/tradução na matriz são permitidos - a chamada falhará se a matriz contiver elementos de distorção/rotação.
	/// </summary>
	/// <param name="Param_Matriz_32">A matriz de transformação para usar para o dimensionamento e tradução em cadeia de swap. Esta função só pode ser usada com cadeias de troca de 
	/// composição(Composition) criadas por ICarenDXGIFactory2::CreateSwapChainForComposition. Somente componentes de escala e tradução são permitidos na matriz.</param>
	static CarenResult SetMatrixTransform(
		IDXGISwapChain2* Param_MyPointerWork, 
		CA_DXGI_MATRIX_3X2_F^ Param_Matriz_32);

	/// <summary>
	/// (SetMaximumFrameLatency) - Define o número de quadros que a cadeia de swap pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_MaximoBackBufferLatencia">O número máximo de quadros de buffer traseiros que serão enfileirados para a cadeia de swap. Este valor é 1 por padrão.</param>
	static CarenResult SetMaximumFrameLatency(
		IDXGISwapChain2* Param_MyPointerWork, 
		UInt32 Param_MaximoBackBufferLatencia);

	/// <summary>
	/// (SetSourceSize) - Define a região de origem para ser usada para a cadeia de swap.
	/// Use o SetSourceSize para especificar a parte da cadeia de swap da qual o sistema operacional apresenta. Isso permite um redimensionamento eficaz sem chamar o método 
	/// (ICarenDXGISwapChain::AlterarTamanhoBuffers) que é mais caro. Antes do Windows 8.1, ligar para ICarenDXGISwapChain::AlterarTamanhoBuffers era a única maneira de 
	/// redimensionar a cadeia de swap. O retângulo de origem é sempre definido pela região [0, 0, Largura, Altura].
	/// </summary>
	/// <param name="Param_Largura">Largura de fonte para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à largura global 
	/// da cadeia de swap.</param>
	/// <param name="Param_Altura">Altura de origem para usar para a cadeia de swap. Esse valor deve ser maior que zero, e deve ser menor ou igual à altura global da 
	/// cadeia de swap.</param>
	static CarenResult SetSourceSize(
		IDXGISwapChain2* Param_MyPointerWork, 
		UInt32 Param_Largura, 
		UInt32 Param_Altura);


	//Métodos da interface(ICarenDXGISwapChain1)
public:
	/// <summary>
	/// (GetBackgroundColor) - Recupera a cor de fundo da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Cor">Retorna uma estrutura que contém as informações de cor do Background.</param>
	static CarenResult GetBackgroundColor(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] CA_DXGI_RGBA^% Param_Out_Cor);

	/// <summary>
	/// (GetCoreWindow) - Recupera o objeto CoreWindow subjacente para este objeto de cadeia de swap.
	/// </summary>
	/// <param name="Param_RIID">Um ponteiro para o identificador globalmente único(GUID) do objeto CoreWindow que é referenciado pelo parâmetro Param_Out_CoreWindow.</param>
	/// <param name="Param_Out_CoreWindow">Retorna o ponteiro do objeto para a CoreWindow.  O usuário deve inicializar a interface antes de chamar este método.</param>
	static CarenResult GetCoreWindow(
		IDXGISwapChain1* Param_MyPointerWork, 
		String^ Param_RIID, 
		ICaren^ Param_Out_CoreWindow);

	/// <summary>
	/// (GetDesc1) - Obtém uma descrição da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Desc">Retorna uma estrutura que contém a descrição da cadeia de Swap.</param>
	static CarenResult GetDesc1(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] CA_DXGI_SWAP_CHAIN_DESC1^% Param_Out_Desc);

	/// <summary>
	/// (GetFullscreenDesc) - Obtém uma descrição de uma cadeia de troca em tela cheia.
	/// </summary>
	/// <param name="Param_Out_DescFullScreenSwap">Retorna uma estrutura que contém a descrição no modo FullScreen na cadeia de Swap.</param>
	static CarenResult GetFullscreenDesc(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^% Param_Out_DescFullScreenSwap);

	/// <summary>
	/// (GetHwnd) - Recupera o HWND subjacente para este objeto de cadeia de swap.
	/// </summary>
	/// <param name="Param_Out_HWND">Retorna um ponteiro para o HWND do objeto de cadeia de Swap.</param>
	static CarenResult GetHwnd(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] IntPtr% Param_Out_HWND);

	/// <summary>
	/// (GetRestrictToOutput) - Obtém a saída (o monitor de exibição) ao qual você pode restringir o conteúdo de uma operação atual.
	/// </summary>
	/// <param name="Param_Out_Saida">Um ponteiro para um buffer que recebe um ponteiro para a interface IDXGIOutput para a saída de restrição.  Um aplicativo passa este ponteiro para 
	/// ICarenDXGIOutput em uma chamada para o ICarenDXGIFactory2::CreateSwapChainForHwnd, ICarenDXGIFactory2::CreateSwapChainForCoreWindow, ou ICarenDXGIFactory2::CreateSwapChainForComposition</param>
	static CarenResult GetRestrictToOutput(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] ICarenDXGIOutput^% Param_Out_Saida);

	/// <summary>
	/// (GetRotation) - Obtém a rotação dos buffers traseiros para a cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_Rotacao">Retorna uma enumeração que define a rotação do Buffer Traseiro(BackBuffer).</param>
	static CarenResult GetRotation(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] CA_DXGI_MODE_ROTATION% Param_Out_Rotacao);

	/// <summary>
	/// (IsTemporaryMonoSupported) - Determina se uma cadeia de swap suporta "mono temporário".
	/// </summary>
	/// <param name="Param_Out_Suporte">Retorna um Booleano que define o suporte ao mono.</param>
	static CarenResult IsTemporaryMonoSupported(
		IDXGISwapChain1* Param_MyPointerWork, 
		[Out] Boolean% Param_Out_Suporte);

	/// <summary>
	/// (Present1) - Apresenta um Frame a tela de exibição.
	/// </summary>
	/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
	/// <param name="Param_FlagsApresentacao">Um valor inteiro que contém opções de apresentação em cadeia de swaps.</param>
	/// <param name="Param_ParametrosApresentacao">uma estrutura CA_DXGI_PRESENT_PARAMETERS que descreve retângulos atualizados e rolar informações do quadro para apresentar.</param>
	static CarenResult Present1(
		IDXGISwapChain1* Param_MyPointerWork, 
		UInt32 Param_IntervaloSincronizacao, 
		CA_DXGI_PRESENT Param_FlagsApresentacao, 
		CA_DXGI_PRESENT_PARAMETERS^ Param_ParametrosApresentacao);

	/// <summary>
	/// (SetBackgroundColor) - Muda a cor de fundo da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Cor">A nova cor para o Background do buffer traseiro.</param>
	static CarenResult SetBackgroundColor(
		IDXGISwapChain1* Param_MyPointerWork, 
		CA_DXGI_RGBA^ Param_Cor);

	/// <summary>
	/// (SetRotation) - Define a rotação dos buffers de volta para a cadeia de swap.
	/// </summary>
	/// <param name="Param_Rotacao">A nova rotação dos Buffers Traseiro(BackBuffers).</param>
	static CarenResult SetRotation(
		IDXGISwapChain1* Param_MyPointerWork, 
		CA_DXGI_MODE_ROTATION Param_Rotacao);



	//Métodos da interface(ICarenDXGISwapChain)
public:
	/// <summary>
	/// (GetBuffer) - Acessa um dos buffers de volta da cadeia de swaps.
	/// </summary>
	/// <param name="Param_IndexBuffer">O Indince para o buffer de volta(Back-Buffer).</param>
	/// <param name="Param_RiidInterface">O tipo de interface usada para manipular o buffer.</param>
	/// <param name="Param_Out_InterfaceBuffer">Retorna a interface que gerencia o Buffer de volta(Back-Buffer). O Usuário é responsável por criar a interface que será retornada.</param>
	static CarenResult GetBuffer(
		IDXGISwapChain* Param_MyPointerWork, 
		UInt32 Param_IndexBuffer, 
		String^ Param_RiidInterface, 
		ICaren^ Param_Out_InterfaceBuffer);

	/// <summary>
	/// (GetContainingOutput) - Obtém a saída (o monitor de exibição) que contém a maior parte da área do cliente da janela alvo.
	/// Se o método for bem-sucedido, a interface de saída será preenchida e sua contagem de referência incrementada. Quando você terminar com ele, não se esqueça de liberar a interface para evitar um vazamento de memória.
	/// </summary>
	/// <param name="Param_Out_MonitorSaida">Retorna a interface para o monitor de exbicão de saida.</param>
	static CarenResult GetContainingOutput(
		IDXGISwapChain* Param_MyPointerWork, 
		[Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

	/// <summary>
	/// (GetDesc) - Obtém uma descrição da cadeia de swaps.
	/// </summary>
	/// <param name="Param_Out_DescricaoCadeiaSwap">Retorna uma estrutura com a descrição da cadeia de troca.</param>
	static CarenResult GetDesc(
		IDXGISwapChain* Param_MyPointerWork, 
		[Out] Estruturas::CA_DXGI_SWAP_CHAIN_DESC^% Param_Out_DescricaoCadeiaSwap);

	/// <summary>
	/// (GetFrameStatistics) - Obtém estatísticas de desempenho sobre o último quadro render.
	/// </summary>
	/// <param name="Param_Out_FrameEstatisticas">Retorna uma estrutura com as estatiticas do frame.</param>
	static CarenResult GetFrameStatistics(
		IDXGISwapChain* Param_MyPointerWork, 
		[Out] Estruturas::CA_DXGI_FRAME_STATISTICS^% Param_Out_FrameEstatisticas);

	/// <summary>
	/// (GetFullscreenState) - Associe o estado ao modo de tela cheia.
	/// </summary>
	/// <param name="Param_Out_EstadoFullScreen">Retorna o estado do FullScreen. Se TRUE, a cadeia de swap está no modo de tela cheia. Se FALSE, a cadeia de swap está em modo de janela.</param>
	/// <param name="Param_Out_MonitorSaida">Retorna um ponteiro para o monitor de saida quando em modo de Tela Cheia(FullScreen); caso contrario retorna NULO.</param>
	static CarenResult GetFullscreenState(
		IDXGISwapChain* Param_MyPointerWork, 
		[Out] Boolean% Param_Out_EstadoFullScreen, 
		[Out] ICarenDXGIOutput^% Param_Out_MonitorSaida);

	/// <summary>
	/// (GetLastPresentCount) - Obtém o número de vezes que o método ICarenDXGISwapChain::Apresentar ou ICarenDXGISwapChain1::Present1 foi chamado.
	/// </summary>
	/// <param name="Param_Out_QuantidadeChamadas">Retorna a quantidade de chamadas para o método Apresentar ou Present1.</param>
	static CarenResult GetLastPresentCount(
		IDXGISwapChain* Param_MyPointerWork, 
		[Out] UInt32% Param_Out_QuantidadeChamadas);

	/// <summary>
	/// (Present) - Apresenta uma imagem renderizada ao usuário.
	/// </summary>
	/// <param name="Param_IntervaloSincronizacao">Um inteiro que especifica como sincronizar a apresentação de um quadro com o espaço em branco vertical.</param>
	/// <param name="Param_Flags">Um valor inteiro que contém opções de apresentação em cadeia de swaps. Essas opções são definidas pela enumeração (CA_DXGI_PRESENT).</param>
	static CarenResult Present(
		IDXGISwapChain* Param_MyPointerWork, 
		UInt32 Param_IntervaloSincronizacao, 
		Enumeracoes::CA_DXGI_PRESENT Param_Flags);

	/// <summary>
	/// (ResizeBuffers) - Altera o tamanho, o formato e o número de buffers da cadeia de swap. Isso deve ser chamado quando a janela do aplicativo é redimensionada.
	/// Você não pode redimensionar uma cadeia de swap sem que libere todas as referências pendentes aos seus buffers traseiros. Você deve liberar todas as suas referências diretas e indiretas nos buffers de volta para que 
	/// o (AlterarTamanhoBuffers) tenha sucesso.
	/// </summary>
	/// <param name="Param_NumeroBuffers">O número de buffers na cadeia de swap (incluindo todos os buffers traseiros e dianteiros). Este número pode ser diferente do número de buffers com os quais você criou a cadeia de swap. 
	/// Este número não pode ser maior do que DXGI_MAX_SWAP_CHAIN_BUFFERS. Defina este número a zero para preservar o número existente de amortecedores na cadeia de swaps.</param>
	/// <param name="Param_Largura">A nova largura do amortecedor traseiro. Se você especificar zero, DXGI usará a largura da área do cliente da janela do alvo.</param>
	/// <param name="Param_Altura">A nova altura do amortecedor traseiro. Se você especificar zero, DXGI usará a altura da área do cliente da janela do alvo. </param>
	/// <param name="Param_NovoFormato">O novo formato do buffer traseiro. Defina esse valor para DXGI_FORMAT_UNKNOWN para preservar o formato existente do buffer traseiro.</param>
	/// <param name="Param_SwapChainFlags">Uma combinação de CA_DXGI_SWAP_CHAIN_FLAG- digitado valores que são combinados usando um bitwise ou operação. O valor resultante especifica opções para o comportamento da cadeia de swaps</param>
	static CarenResult ResizeBuffers(
		IDXGISwapChain* Param_MyPointerWork, 
		UInt32 Param_NumeroBuffers,
		UInt32 Param_Largura, 
		UInt32 Param_Altura, 
		Enumeracoes::CA_DXGI_FORMAT Param_NovoFormato, 
		Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Param_SwapChainFlags);

	/// <summary>
	/// (ResizeTarget) - Redimensiona a meta de saída.
	/// </summary>
	/// <param name="Param_NovaDesc">A estrutura CA_DXGI_MODE_DESC que descreve o modo, que especifica a nova largura, altura, formato e taxa de atualização do alvo. Se o formato for DXGI_FORMAT_UNKNOWN, o método (ResizeTarget)
	/// utilizara o formato existente. Recomendamos apenas que você use DXGI_FORMAT_UNKNOWN quando a cadeia de swap está em modo de tela cheia, pois este método não é seguro para o segmento.</param>
	static CarenResult ResizeTarget(
		IDXGISwapChain* Param_MyPointerWork, 
		Estruturas::CA_DXGI_MODE_DESC^ Param_NovaDesc);

	/// <summary>
	/// (SetFullscreenState) - Define o estado de exibição para janelas ou tela cheia.
	/// </summary>
	/// <param name="Param_EstadoFullScreen">Um valor booleano que especifica se deve definir o estado de exibição para janelas ou tela cheia. VERDADE para tela cheia, e FALSO para janelas.</param>
	/// <param name="Param_MonitorSaida">Se você passar o TRUE para o parâmetro (Param_EstadoFullScreen) para definir o estado de exibição para tela cheia, você pode definir opcionalmente este parâmetro para um ponteiro para uma interface
	/// IDXGIOutput para o alvo de saída que contém a cadeia de swap. Se você definir este parâmetro para NULO, DXGI escolherá a saída com base no dispositivo da cadeia de swap e na colocação da janela de saída. Se você passar FALSE 
	/// para (Param_EstadoFullScreen), você deve definir este parâmetro para NULO.</param>
	static CarenResult SetFullscreenState(
		IDXGISwapChain* Param_MyPointerWork, 
		Boolean Param_EstadoFullScreen, 
		ICarenDXGIOutput^ Param_MonitorSaida);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIDevice
{
	//Métodos da interface(ICarenDXGIDevice4)
public:
	/// <summary>
	/// (OfferResources1) - Permite que o sistema operacional liberte a memória de vídeo dos recursos, incluindo tanto descartar o conteúdo quanto descomprometer a memória.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
	/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
	/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
	/// <param name="Param_Flags">Especifica o DXGI_OFFER_RESOURCE_FLAGS.</param>
	static  CarenResult OfferResources1(
		IDXGIDevice4* Param_MyPointerWork,
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade,
		CA_DXGI_OFFER_RESOURCE_FLAGS Param_Flags);

	/// <summary>
	/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice4::OfferResources.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Resultado) conjuntos de argumentos.</param>
	/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
	/// <param name="Param_Ref_Resultado">Uma matriz que recebe valores da enumeração CA_DXGI_RECLAIM_RESOURCE_RESULTS. Cada valor na matriz corresponde a um recurso 
	/// no mesmo índice que o parâmetro (Param_Recursos) especifica. O chamador pode passar em NULO, se o chamador pretende preencher os recursos com novos conteúdos, 
	/// independentemente de o conteúdo antigo ter sido descartado.</param>
	static  CarenResult ReclaimResources1(
		IDXGIDevice4* Param_MyPointerWork,
		Int32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		cli::array<CA_DXGI_RECLAIM_RESOURCE_RESULTS>^% Param_Ref_Resultado);


	//Métodos da interface(ICarenDXGIDevice3)
public:
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
	static  CarenResult Trim(IDXGIDevice3* Param_MyPointerWork);


	//Métodos da interface(ICarenDXGIDevice2)
public:
	/// <summary>
	/// (EnqueueSetEvent) - Libera quaisquer comandos de renderização pendentes e define o objeto de evento especificado para o estado sinalizado depois de todos os 
	/// comandos de renderização previamente enviados completos.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento. Todos os tipos de objetos de evento (manual-reset, auto-reset e assim por diante) são suportados. 
	/// A Handle deve ter a bandeira de direito de acesso (EVENT_MODIFY_STATE).</param>
	static  CarenResult EnqueueSetEvent(IDXGIDevice2* Param_MyPointerWork, ICarenEvent^ Param_HandleEvento);

	/// <summary>
	/// (OfferResources) - Permite que o sistema operacional liberte a memória de vídeo dos recursos descartando seu conteúdo.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos na matriz de argumentos (Param_Recursos).</param>
	/// <param name="Param_Recursos">Um array de interfaces ICarenDXGIResource para os recursos a serem oferecidos.</param>
	/// <param name="Param_Prioridade">Um valor CA_DXGI_OFFER_RESOURCE_PRIORITY que indica o quão valiosos os dados são.</param>
	static  CarenResult OfferResources(
		IDXGIDevice2* Param_MyPointerWork,
		UInt32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		CA_DXGI_OFFER_RESOURCE_PRIORITY Param_Prioridade);

	/// <summary>
	/// (ReclaimResources) - Restaura o acesso a recursos que foram oferecidos anteriormente ligando para ICarenDXGIDevice2::OfferResources.
	/// </summary>
	/// <param name="Param_QuantidadeRecursos">O número de recursos no argumento (Param_Recursos) e (Param_Ref_Descartado) conjuntos de argumentos.</param>
	/// <param name="Param_Recursos">>Um array de interfaces ICarenDXGIResource para os recursos a serem recuperados.</param>
	/// <param name="Param_Ref_Descartado">Uma matriz que recebe valores booleanos. Cada valor na matriz corresponde a um recurso no mesmo índice que o parâmetro 
	/// (Param_Recursos) especifica. O tempo de execução define cada valor booleano para TRUE se o conteúdo do recurso correspondente foi descartado e agora estiver 
	/// indefinido, ou para FALSE se o conteúdo antigo do recurso correspondente ainda estiver intacto. O chamador pode passar NULO, se o chamador pretende preencher 
	/// os recursos com novos conteúdos, independentemente de o conteúdo antigo ter sido descartado.</param>
	static  CarenResult ReclaimResources(
		IDXGIDevice2* Param_MyPointerWork,
		Int32 Param_QuantidadeRecursos,
		cli::array<ICarenDXGIResource^>^ Param_Recursos,
		cli::array<bool>^% Param_Ref_Descartado);


	//Métodos da interface(ICarenDXGIDevice1)
public:
	/// <summary>
	/// (GetMaximumFrameLatency) - Obtém o número de quadros(Frames) que o sistema pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_Out_LatenciaMaxima">Esse valor é definido para o número de quadros que podem ser enfileirados para renderização. Esse valor está 
	/// inadimplente em 3, mas pode variar de 1 a 16.</param>
	static  CarenResult GetMaximumFrameLatency(IDXGIDevice1* Param_MyPointerWork, [Out] UInt32% Param_Out_LatenciaMaxima);

	/// <summary>
	/// (SetMaximumFrameLatency) - Define o número de quadros que o sistema pode fazer fila para renderização.
	/// </summary>
	/// <param name="Param_LatenciaMaxima">O número máximo de quadros de buffer traseiro que um motorista pode fazer fila. O valor está inadimplente a 3, mas pode 
	/// variar de 1 a 16. Um valor de 0 redefinirá a latência ao padrão. Para dispositivos (per-head), esse valor é especificado por cabeça(Head).</param>
	static  CarenResult SetMaximumFrameLatency(IDXGIDevice1* Param_MyPointerWork, UInt32 Param_LatenciaMaxima);

	//Métodos da interface(ICarenDXGIDevice)
public:
	/// <summary>
	/// (CreateSurface)(Não é implementado) - Este método é usado internamente e você não deve chamá-lo diretamente em sua aplicação.
	/// </summary>
	static  CarenResult CreateSurface();

	/// <summary>
	/// (GetAdapter) - Retorna o adaptador para o dispositivo especificado.
	/// </summary>
	/// <param name="Param_Out_Adaptador">Retorna um ponteiro para a interface(ICarenDXGIAdapter) do adaptador.</param>
	static  CarenResult GetAdapter(IDXGIDevice* Param_MyPointerWork, [Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (GetGPUThreadPriority) - Retorna a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Out_Prioridade">recebe um valor que indica a prioridade atual da Thread GPU. O valor será entre -7 e 7, inclusive, onde 0 representa prioridade normal.</param>
	static  CarenResult GetGPUThreadPriority(IDXGIDevice* Param_MyPointerWork, [Out] int% Param_Out_Prioridade);

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
	static  CarenResult QueryResourceResidency(
		IDXGIDevice* Param_MyPointerWork,
		cli::array<ICarenDXGIResource^>^ Param_ArrayRecursos,
		cli::array<CA_DXGI_RESIDENCY>^% Param_Ref_StatusResidencia,
		UInt32 Param_QuantidadeRecursos);

	/// <summary>
	/// (SetGPUThreadPriority) - Define a prioridade da Thread GPU.
	/// </summary>
	/// <param name="Param_Prioridade">Um valor que especifica a prioridade necessária da Thread da GPU. Esse valor deve ser entre -7 e 7, inclusive, onde 0 representa 
	/// prioridade normal.</param>
	static  CarenResult SetGPUThreadPriority(IDXGIDevice* Param_MyPointerWork, int Param_Prioridade);
};

/// <summary>
/// 
/// </summary>
class Shared_DXGIFactory
{
	//Métodos da interface(ICarenDXGIFactory7)
public:
	/// <summary>
	/// (RegisterAdaptersChangedEvent) - Registra-se para receber notificação de alterações sempre que o estado de enumeração do adaptador muda.
	/// </summary>
	/// <param name="Param_HandleEvento">Uma Handle para o objeto do evento.</param>
	/// <param name="Param_Out_Cookie">Recebe um valor da chave para o evento registrado.</param>
	static CarenResult RegisterAdaptersChangedEvent(
		IDXGIFactory7* Param_MyPointerWork,
		ICarenEvent^ Param_HandleEvento,
		[Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (UnregisterAdaptersChangedEvent) - Cancela o registro do evento para parar de receber notificações quando o estado de enumeração do adaptador muda.
	/// </summary>
	/// <param name="Param_Cookie">O valor da chave do evento registrado para ser cancelado. Esse valor é obtido do método (RegisterAdaptersChangedEvent).</param>
	static CarenResult UnregisterAdaptersChangedEvent(
		IDXGIFactory7* Param_MyPointerWork,
		UInt32 Param_Cookie);



	//Métodos da interface(ICarenDXGIFactory6)
public:
	/// <summary>
	/// (EnumAdapterByGpuPreference) - Enumera adaptadores gráficos com base em uma determinada preferência de GPU.
	/// </summary>
	/// <param name="Param_IndexAdaptador">O índice do adaptador para enumerar. Os índices estão por ordem da preferência especificada no CA_DXGI_GPU_PREFERENCE - por exemplo, 
	/// se CA_DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE for especificado, então o adaptador de maior desempenho está no índice 0, o segundo mais alto está no índice 1, e assim 
	/// por diante.</param>
	/// <param name="Param_PreferenciaGPU">A preferência da GPU pelo aplicativo</param>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro Param_Out_Adaptador.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface ICarenDXGIAdapter do adaptador.</param>
	static CarenResult EnumAdapterByGpuPreference(
		IDXGIFactory6* Param_MyPointerWork,
		UInt32 Param_IndexAdaptador,
		CA_DXGI_GPU_PREFERENCE Param_PreferenciaGPU,
		String^ Param_RIID,
		ICaren^ Param_Out_Adaptador);



	//Métodos da interface(ICarenDXGIFactory5)
public:
	/// <summary>
	/// (CheckFeatureSupport) - Usado para verificar se há suporte ao recurso de hardware.
	/// </summary>
	/// <param name="Param_Recurso">Especifica um membro da CA_DXGI_FEATURE para consultar o suporte.</param>
	/// <param name="Param_SizeBuffer">O tamanho de Param_Ref_BufferDescFeature, em bytes.</param>
	/// <param name="Param_Ref_BufferDescFeature">Especifica um ponteiro para um buffer que será preenchido com dados que descrevem o suporte ao recurso.</param>
	static CarenResult CheckFeatureSupport(
		IDXGIFactory5* Param_MyPointerWork,
		CA_DXGI_FEATURE Param_Recurso,
		UInt32 Param_SizeBuffer,
		ICarenBuffer^% Param_Ref_BufferDescFeature);



	//Métodos da interface(ICarenDXGIFactory4)
public:
	/// <summary>
	/// (EnumAdapterByLuid) - Enumera saídas do ICarenDXGIAdapter para o LUID especificado.
	/// </summary>
	/// <param name="Param_LUID">Um valor único que identifica o adaptador.</param>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
	/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador.</param>
	static CarenResult EnumAdapterByLuid(
		IDXGIFactory4* Param_MyPointerWork,
		CA_LUID^ Param_LUID,
		String^ Param_RIID,
		[Out] ICaren^ Param_Out_InterfaceAdapter);

	/// <summary>
	/// (EnumWarpAdapter) - Fornece um adaptador que pode ser fornecido a função D3D12CreateDevice para usar o renderizador WARP.
	/// </summary>
	/// <param name="Param_RIID">O identificador globalmente único (GUID) do objeto ICarenDXGIAdapter referenciado pelo parâmetro (Param_InterfaceAdapter).</param>
	/// <param name="Param_Out_InterfaceAdapter">Recebe um ponteiro de interface ICarenDXGIAdapter para o adaptador. </param>
	static CarenResult EnumWarpAdapter(
		IDXGIFactory4* Param_MyPointerWork,
		String^ Param_RIID, 
		[Out] ICaren^ Param_Out_InterfaceAdapter);


	//Métodos da interface(ICarenDXGIFactory3)
public:
	/// <summary>
	/// (GetCreationFlags) - Recebe as bandeiras que foram usadas quando um objeto Microsoft DirectX Graphics Infrastructure (DXGI) foi criado.
	/// </summary>
	/// <param name="Param_Out_Flags">Retorna o flag utilizada na criação da fabrica(DXGIFactory).</param>
	static CarenResult GetCreationFlags(
		IDXGIFactory3* Param_MyPointerWork,
		[Out] UInt32% Param_Out_Flags);


	//Métodos da interface(ICarenDXGIFactory2)
public:
	/// <summary>
	/// (CreateSwapChainForComposition) - Cria uma cadeia de swaps que você pode usar para enviar conteúdo Direct3D para a API de Composição Direta ou a estrutura Windows.UI.Xaml para compor em uma janela.
	/// </summary>
	/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
	/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
	/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
	/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.
	/// Você deve especificar o valor DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL no membro SwapEffect da CA_DXGI_SWAP_CHAIN_DESC1 porque o método (CreateSwapChainForComposition) suporta 
	/// apenas um modelo de apresentação de flip.
	/// Você também deve especificar o valor DXGI_SCALING_STRETCH no membro de Scale de CA_DXGI_SWAP_CHAIN_DESC1.</param>
	/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
	/// quiser restringir o conteúdo a uma meta de saída.
	/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Present1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
	/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
	/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
	/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForComposition) cria.</param>
	static CarenResult CreateSwapChainForComposition(
		IDXGIFactory2* Param_MyPointerWork,
		ICaren^ Param_DispositivoDirect3D,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

	/// <summary>
	/// (CreateSwapChainForCoreWindow) - Cria uma cadeia de swaps que está associada ao objeto CoreWindow para a janela de saída para a cadeia de swap.
	/// </summary>
	/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
	/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
	/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
	/// <param name="Param_CoreWindow">Um ponteiro para o objeto CoreWindow que está associado com a cadeia de swap que (CreateSwapChainForCoreWindow) cria.</param>
	/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput que a cadeia de swap é restrito. Se a cadeia de swaps for movida para uma saída diferente, 
	/// o conteúdo é preto. Você pode definir opcionalmente este parâmetro para uma meta de saída que usa DXGI_PRESENT_RESTRICT_TO_OUTPUT para restringir o conteúdo dessa saída. 
	/// Se você não definir este parâmetro para restringir o conteúdo em uma meta de saída, você pode defini-lo para NULO.</param>
	/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForCoreWindow) cria.</param>
	static CarenResult CreateSwapChainForCoreWindow(
		IDXGIFactory2* Param_MyPointerWork,
		ICaren^ Param_DispositivoDirect3D,
		ICaren^ Param_CoreWindow,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

	/// <summary>
	/// (CreateSwapChainForHwnd) - Cria uma cadeia de swap que esteja associada a uma alça HWND à janela de saída para a cadeia de swaps.
	/// </summary>
	/// <param name="Param_DispositivoDirect3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. 
	/// Para Direct3D 12 este é um ponteiro para uma fila de comando direto (consulte ID3D12CommandQueue). Este parâmetro não pode ser NULO. Os drivers de software, 
	/// como D3D_DRIVER_TYPE_REFERENCE, não são suportados para cadeias de troca de composição.</param>
	/// <param name="Param_Handle">A alça(HWND - HANDLE) que está associado com a cadeia de swap que (CreateSwapChainForHwnd) cria. Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_DescSwap">Uma estrutura DXGI_SWAP_CHAIN_DESC1 que descreve a cadeia de swap. Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_DescFullScreen">Uma estrutura CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC para a descrição de uma cadeia de swap de tela cheia. Você pode definir opcionalmente 
	/// este parâmetro para criar uma cadeia de swap de tela cheia. Configurá-lo para NULO para criar uma cadeia de swap em modo Janela.</param>
	/// <param name="Param_SaidaRestrita">Um ponteiro para a interface ICarenDXGIOutput para a saída para restringir o conteúdo. Defina este parâmetro para NULO se você não 
	/// quiser restringir o conteúdo a uma meta de saída.
	/// Você também deve passar a bandeira DXGI_PRESENT_RESTRICT_TO_OUTPUT em uma chamada ICarenDXGISwapChain1::Present1 para forçar o conteúdo a aparecer apagado em qualquer outra saída. Se você quiser 
	/// restringir o conteúdo a uma saída diferente, você deve criar uma nova cadeia de swaps. No entanto, você pode restringir condicionalmente o conteúdo com base na bandeira 
	/// DXGI_PRESENT_RESTRICT_TO_OUTPUT.</param>
	/// <param name="Param_Out_SwapChain">Retorna um ponteiro para a interface ICarenDXGISwapChain1 que o método (CreateSwapChainForHwnd) cria.</param>
	static CarenResult CreateSwapChainForHwnd(
		IDXGIFactory2* Param_MyPointerWork,
		ICaren^ Param_DispositivoDirect3D,
		IntPtr Param_Handle,
		CA_DXGI_SWAP_CHAIN_DESC1^ Param_DescSwap,
		CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC^ Param_DescFullScreen,
		ICarenDXGIOutput^ Param_SaidaRestrita,
		[Out] ICarenDXGISwapChain1^% Param_Out_SwapChain);

	/// <summary>
	/// (GetSharedResourceAdapterLuid) - Identifica o adaptador no qual um objeto de recurso compartilhado foi criado.
	/// </summary>
	/// <param name="Param_HandleRecurso">Uma alça para um objeto de recurso compartilhado. O método ICarenDXGIResource1::CreateSharedHandle devolve essa alça.</param>
	/// <param name="Param_Out_Luid">Retorna uma variavel que recebe um identificador localmente único(LUID). Valor que identifica o adaptador. Um CA_LUID é um valor de 64 bits 
	/// que é garantido para ser único apenas no sistema operacional em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema operacional seja 
	/// reiniciado.</param>
	static CarenResult GetSharedResourceAdapterLuid(
		IDXGIFactory2* Param_MyPointerWork,
		IntPtr Param_HandleRecurso,
		[Out] CA_LUID^% Param_Out_Luid);

	/// <summary>
	/// (IsWindowedStereoEnabled) - Determina se deve usar o modo estéreo.
	/// </summary>
	/// <param name="Param_Out_ModoEstereoHabilitado">Retorna um valor que indica se deve usar o modo estéreo. TRUE indica que você pode usar o modo estéreo; se não, FALSO.</param>
	static CarenResult IsWindowedStereoEnabled(
		IDXGIFactory2* Param_MyPointerWork,
		[Out] Boolean% Param_Out_ModoEstereoHabilitado);

	/// <summary>
	/// (RegisterOcclusionStatusEvent) - Registra-se para receber notificação de alterações no status de oclusão usando a sinalização do evento.
	/// </summary>
	/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status de oclusão. 
	/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o 
	/// registro do evento de notificação que (Param_Evento) especifica.</param>
	static CarenResult RegisterOcclusionStatusEvent(
		IDXGIFactory2* Param_MyPointerWork,
		ICarenEvent^ Param_Evento,
		[Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterOcclusionStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações do status de oclusão.
	/// </summary>
	/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração de status de oclusão.</param>
	/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterOcclusionStatus para cancelar o registro da mensagem 
	/// de notificação que (Param_WinMensagemCode) especifica.</param>
	static CarenResult RegisterOcclusionStatusWindow(
		IDXGIFactory2* Param_MyPointerWork,
		IntPtr Param_HandleJanela,
		UInt32 Param_WinMensagemCode,
		[Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterStereoStatusEvent) - Registra-se para receber notificação de alterações no status estéreo usando a sinalização do evento.
	/// </summary>
	/// <param name="Param_Evento">Uma alça para o objeto do evento que o sistema operacional define quando ocorre a notificação de alteração de status do modo Stereo. 
	/// A função CriarEvento ou AbrirEvento retorna essa alça.</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o 
	/// registro do evento de notificação que (Param_Evento) especifica.</param>
	static CarenResult RegisterStereoStatusEvent(
		IDXGIFactory2* Param_MyPointerWork,
		ICarenEvent^ Param_Evento,
		[Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (RegisterStereoStatusWindow) - Registra uma janela de inscrição para receber mensagens de notificação de alterações de status estéreo.
	/// </summary>
	/// <param name="Param_HandleJanela">A alça(Handle) para a janela que vai receber a mensagem de notificação para quando ocorre a alteração do modo Stereo.</param>
	/// <param name="Param_WinMensagemCode">Especifica a mensagem de notificação para enviar para a janela define em (Param_HandleJanela).</param>
	/// <param name="Param_Out_Cookie">Retorna um valor-chave que um aplicativo pode passar para o método ICarenDXGIFactory2::UnregisterStereoStatus para cancelar o registro da mensagem 
	/// de notificação que (Param_WinMensagemCode) especifica.</param>
	static CarenResult RegisterStereoStatusWindow(
		IDXGIFactory2* Param_MyPointerWork,
		IntPtr Param_HandleJanela,
		UInt32 Param_WinMensagemCode,
		[Out] UInt32% Param_Out_Cookie);

	/// <summary>
	/// (UnregisterOcclusionStatus) - Remove o registro feito por uma chamada (RegisterOcclusionStatusWindow) para uma janela ou um evento para impedi-lo de receber notificação quando o status de oclusão muda.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
	static CarenResult UnregisterOcclusionStatus(
		IDXGIFactory2* Param_MyPointerWork,
		UInt32 Param_Cookie);

	/// <summary>
	/// (UnregisterStereoStatus) - Remove o registro feito por uma chamada (RegisterOcclusionStatusWindow) para uma janela ou um evento para impedi-lo de receber notificação quando o status estéreo muda.
	/// </summary>
	/// <param name="Param_Cookie">Um valor-chave para a janela ou evento para cancelar o registro. Esse valor é retornado nos métodos de registro de evento e janela desta interface.</param>
	static CarenResult UnregisterStereoStatus(
		IDXGIFactory2* Param_MyPointerWork,
		UInt32 Param_Cookie);


	//Métodos da interface(ICarenDXGIFactory1)
public:
	/// <summary>
	/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
	/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
	/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
	/// </summary>
	/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
	static CarenResult EnumAdapters1(
		IDXGIFactory1* Param_MyPointerWork,
		UInt32 Param_IdAdaptador,
		[Out] ICarenDXGIAdapter1^% Param_Out_Adaptador);

	/// <summary>
	/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
	/// </summary>
	/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
	static CarenResult IsCurrent(
		IDXGIFactory1* Param_MyPointerWork,
		[Out] Boolean% Param_Out_Atual);


	//Métodos da interface(ICarenDXGIFactory)
public:
	/// <summary>
	/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
	/// </summary>
	/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
	static CarenResult CreateSoftwareAdapter(
		IDXGIFactory* Param_MyPointerWork,
		IntPtr Param_ModuleHandle,
		[Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (CreateSwapChain) - Cria uma cadeia de swaps.
	/// [Começando com o Direct3D 11.1, recomendamos não usar mais o CreateSwapChain para criar uma cadeia de swaps. Em vez disso, use CreateSwapChainForHwnd, CreateSwapChainForCoreWindow, ou 
	/// CreateSwapChainForComposition dependendo de como você quer criar a cadeia de swap.]
	/// </summary>
	/// <param name="Param_Dispositivo3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. Para Direct3D 12 este é 
	/// um ponteiro para uma fila de comando direto(D3D12CommandQueue). Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_Desc">Uma estrutura CA_DXGI_SWAP_CHAIN_DESC para a descrição da cadeia de swap. Este parâmetro não pode ser NULO.</param>
	/// <param name="Param_Out_SwapChain">Recebe um ponteiro para a interface do SwapChain.</param>
	static CarenResult CreateSwapChain(
		IDXGIFactory* Param_MyPointerWork,
		ICaren^ Param_Dispositivo3D,
		CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc,
		[Out] ICarenDXGISwapChain^% Param_Out_SwapChain);

	/// <summary>
	/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
	/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
	/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
	/// </summary>
	/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
	/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
	static CarenResult EnumAdapters(
		IDXGIFactory* Param_MyPointerWork,
		UInt32 Param_IdAdaptador,
		[Out] ICarenDXGIAdapter^% Param_Out_Adaptador);

	/// <summary>
	/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
	/// </summary>
	/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
	static CarenResult GetWindowAssociation(
		IDXGIFactory* Param_MyPointerWork,
		[Out] IntPtr% Param_HandleJanela);

	/// <summary>
	/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
	/// para tela cheia ou vice-versa).
	/// </summary>
	/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
	/// <param name="Param_Flags"></param>
	static CarenResult MakeWindowAssociation(
		IDXGIFactory* Param_MyPointerWork,
		IntPtr Param_HandleJanela,
		CA_DXGI_MWA_FLAGS Param_Flags);
};