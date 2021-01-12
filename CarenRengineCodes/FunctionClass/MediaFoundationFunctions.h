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
#include "../SDK_Base.h"
#include "../Caren/Caren.h"
#include "../SDK_Utilidades.h"
#include "../Media Foundation/CarenMFActivate.h"

//Importa o SDK Base da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;

/// <summary>
/// Classe responsável por conter funções nativas utilizada pela Api do Microsoft Media Foundation.
/// </summary>
public ref class MediaFoundationFunctions
{
	//Destruidor da classe.
public:
	MediaFoundationFunctions() {}
	~MediaFoundationFunctions()
	{
	}


	//Métodos da Media Foundation.
public:
	/// <summary>
	/// Método responsável por inicia a Api do Media Foundation.
	/// </summary>
	CarenResult _MFStartup();
	
	/// <summary>
	/// Método responsável por desligar a Api do Media Foundation.
	/// </summary>
	CarenResult _MFShutdown();

	/// <summary>
	/// Define uma função de retorno de chamada a ser chamada em um intervalo fixo.
	/// </summary>
	/// <param name="Param_Callback">A função que será chamada periodicamente. A função deve ser do tipo: MFPERIODICCALLBACK.</param>
	/// <param name="Param_Context">Um objeto fornecido por chamadas que implemente IUnknown, ou NULO. Este parâmetro é passado para a função de retorno de chamada.</param>
	/// <param name="Param_Out_Key">Recebe uma chave que pode ser usada para cancelar o retorno de chamada. Para cancelar o retorno de chamada, ligue para 
	/// MFRemovePeriodicCallback e passe esta key como parâmetro (Param_Key).</param>
	/// <returns></returns>
	CarenResult _MFAddPeriodicCallback(IntPtr Param_Callback, ICaren^ Param_Context, OutParam UInt32% Param_Out_Key);

	/// <summary>
	/// ‎Cancela uma função de retorno de chamada que foi definida pela função ‎‎MFAddPeriodicCallback.‎
	/// </summary>
	/// <param name="Param_Key">‎Chave que identifica o retorno da chamada. Este valor é recuperado pela função ‎‎MFAddPeriodicCallback.‎</param>
	/// <returns></returns>
	CarenResult _MFRemovePeriodicCallback(UInt32 Param_Key);

	/// <summary>
	/// ‎Calcula a taxa de frames, em frames por segundo, a partir da duração média de um quadro de vídeo.‎
	/// </summary>
	/// <param name="Param_AverageTimePerFrame">‎A duração média de um frame de vídeo, em unidades de 100 nanossegundos.‎</param>
	/// <param name="Param_Out_Numerator">‎Recebe o numerador da taxa de frames.‎</param>
	/// <param name="Param_Out_Denominator">‎Recebe o denominador da taxa de frames.</param>
	/// <returns></returns>
	CarenResult _MFAverageTimePerFrameToFrameRate(UInt64 Param_AverageTimePerFrame, OutParam UInt32% Param_Out_Numerator, OutParam UInt32% Param_Out_Denominator);

	/// <summary>
	/// ‎Converte uma taxa de frame de vídeo em uma duração de frame.‎
	/// </summary>
	/// <param name="Param_Numerator">‎O numerador da taxa de frames.‎</param>
	/// <param name="Param_Denominator">‎O denominador da taxa de frames.‎</param>
	/// <param name="Param_Out_AverageTimePerFrame">‎Recebe a duração média de um frame de vídeo, em unidades de 100 nanossegundos.‎</param>
	/// <returns></returns>
	CarenResult _MFFrameRateToAverageTimePerFrame(UInt32 Param_Numerator, UInt32 Param_Denominator, OutParam UInt64% Param_Out_AverageTimePerFrame);
	
	/// <summary>
	/// ‎Recupera o tamanho da imagem para um formato de vídeo. Dada uma estrutura ‎‎CA_BITMAPINFOHEADER,‎‎ esta função calcula o valor correto do membro ‎‎(CA_BITMAPINFOHEADER->biSizeImage).‎
	/// </summary>
	/// <param name="Param_BmpHeader">Uma estrutura ‎‎BITMAPINFOHEADER‎‎ que descreve o formato.‎</param>
	/// <param name="Param_Size">Defina como 0. Esse valor é definido internamente.</param>
	/// <param name="Param_Out_SizeImage">Recebe o tamanho da imagem, em bytes.</param>
	/// <param name="Param_Out_Known">‎Recebe o valor ‎‎TRUE‎‎ se a função reconhecer o formato de vídeo. Caso contrário, recebe o valor ‎‎FALSE‎‎.‎</param>
	/// <returns></returns>
	CarenResult _MFCalculateBitmapImageSize(CA_BITMAPINFOHEADER^ Param_BmpHeader, UInt32 Param_Size, OutParam UInt32% Param_Out_SizeImage, OutParam Boolean% Param_Out_Known);

	/// <summary>
	/// ‎Recupera o tamanho da imagem, em bytes, para um formato de vídeo não comprimido.‎
	/// </summary>
	/// <param name="Param_GuidSubtypeVideo">‎Subtipo de mídia para o formato de vídeo. Para obter uma lista de subtipos, consulta a estrutura: GUIDs_MF_AUDIO_SUBTYPES‎</param>
	/// <param name="Param_Width">A Largura da imagem, em pixels.</param>
	/// <param name="Param_Height">A Altura da imagem, em pixels.</param>
	/// <param name="Param_Out_SizeImage">‎Recebe o tamanho de cada frame, em bytes. Se o formato for comprimido ou não for reconhecido, o valor é zero.‎</param>
	/// <returns></returns>
	CarenResult _MFCalculateImageSize(String^ Param_GuidSubtypeVideo, UInt32 Param_Width, UInt32 Param_Height, OutParam UInt32% Param_Out_SizeImage);
	
	/// <summary>
	/// ‎Compara um tipo de mídia completo a um tipo de mídia parcial.‎
	/// </summary>
	/// <param name="Param_TypeFull">Uma interface (ICarenMFMediaType) para o tipo de mídia completo.</param>
	/// <param name="Param_PartialType">Uma interface (ICarenMFMediaType) para o tipo de mídia parcial.</param>
	/// <returns></returns>
	Boolean _MFCompareFullToPartialMediaType(ICarenMFMediaType^ Param_TypeFull, ICarenMFMediaType^ Param_PartialType);

	/// <summary>
	/// Converte uma matriz de números de pontos flutuantes de 16 bits em uma matriz de números de pontos flutuantes de 32 bits.
	/// </summary>
	/// <param name="Param_Ref_Dest">Uma matriz de valores flutuantes. A matriz deve conter pelo menos elementos (Param_Count).</param>
	/// <param name="Param_Source">Uma matriz de valores de ponto flutuante de 16 bits, digitado como valores WORD. A matriz deve conter pelo menos elementos (Param_Count).</param>
	/// <param name="Param_Count">Número de elementos na matriz (Param_Src) para converter.</param>
	/// <returns></returns>
	CarenResult _MFConvertFromFP16Array(cli::array<float>^% Param_Ref_Dest, cli::array<UInt16>^ Param_Source, UInt32 Param_Count);

	/// <summary>
	/// Converte uma matriz de números de pontos flutuantes de 32 bits em uma matriz de números de pontos flutuantes de 16 bits.
	/// </summary>
	/// <param name="Param_Ref_Dest">Uma matriz de valores de ponto flutuante de 16 bits, digitado como valores WORD. A matriz deve conter pelo menos elementos (Param_Count).</param>
	/// <param name="Param_Source">Uma matriz de valores flutuantes. A matriz deve conter pelo menos elementos (Param_Count).</param>
	/// <param name="Param_Count">Número de elementos na matriz (Param_Src) para converter.</param>
	/// <returns></returns>
	CarenResult _MFConvertToFP16Array(cli::array<UInt16>^% Param_Ref_Dest, cli::array<float>^ Param_Source, UInt32 Param_Count);

	/// <summary>
	/// Copia uma imagem ou plano de imagem de um buffer para outro.
	/// </summary>
	/// <param name="Param_BufferDestino">Um ponteiro para o início da primeira linha de pixels no buffer de destino.‎</param>
	/// <param name="Param_DestStride">‎O Stride do buffer de destino, em bytes.‎</param>
	/// <param name="Param_BufferOrigem">‎Um ponteiro para o início da primeira linha de pixels na imagem de origem.‎</param>
	/// <param name="Param_SrcStride">‎O Stride do buffer de origem, em bytes.‎</param>
	/// <param name="Param_WidthInBytes">‎Largura da imagem, em bytes.‎</param>
	/// <param name="Param_Lines">‎Número de linhas de pixels para copiar.‎</param>
	/// <returns></returns>
	CarenResult _MFCopyImage(
		ICarenBuffer^ Param_BufferDestino,
		Int32 Param_DestStride,
		ICarenBuffer^ Param_BufferOrigem,
		Int32 Param_SrcStride, 
		UInt32 Param_WidthInBytes, 
		UInt32 Param_Lines);

	/// <summary>
	/// ‎Cria propriedades a partir de uma interface ‎‎ICarenMFMediaType‎‎.‎
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType.</param>
	/// <param name="Param_RIID">‎O identificador de interface (IID) da interface que está sendo solicitada.‎</param>
	/// <param name="Param_Out_Object">Retorna uma interface base (ICaren) para a interface solicitada. O usuário deve incializar a interface antes de chamar este método.</param>
	/// <returns></returns> 
	CarenResult _MFCreatePropertiesFromMediaType(ICarenMFMediaType^ Param_MediaType, String^ Param_RIID, ICaren^ Param_Out_Object);

	/// <summary>
	/// Obtém uma lista de formatos de saída de um codificador de áudio.
	/// Esta função pressupõe que o codificador será usado em seu modo de codificação padrão, que é tipicamente codificação de taxa de bits constante (CBR). 
	/// Portanto, os tipos retornados pela função podem não funcionar com outros modos, como codificação de taxa de bits variáveis (VBR).
	/// </summary>
	/// <param name="Param_GuidSubtype">Especifica o subtipo da mídia de saída. O codificador usa esse valor como filtro quando está enumerando os tipos de saída disponíveis. 
	/// Consulte a estrutura (GUIDs_MF_AUDIO_SUBTYPES) para obter um valor para este parametro.</param>
	/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG.</param>
	/// <param name="Param_Atributos">Uma interface IMFAttributes de uma loja de atributos. A loja de atributos especifica as configurações do 
	/// codificador. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_Availebletypes">Recebe uma interface ICarenMFCollection de um objeto de coleta que contém uma lista de tipos de 
	/// mídia de áudio preferidos. A coleção contém ponteiros ICarenMFMediaType. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFTranscodeGetAudioOutputAvailableTypes(String^ Param_GuidSubtype, CA_MFT_ENUM_FLAG Param_Flags, ICarenMFAttributes^ Param_Atributos, ICarenMFCollection^ Param_Out_Availebletypes);

	/// <summary>
	/// ‎Escreve o conteúdo de uma loja de atributos em um fluxo.‎
	/// </summary>
	/// <param name="Param_AtributosSerialize">Uma interface de atributos que será serializada para o fluxo.</param>
	/// <param name="Param_Flags">‎Bitwise ‎‎OR‎‎ de zero ou mais bandeiras da enumeração ‎‎CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS.‎</param>
	/// <param name="Param_Stream">Uma interface ‎‎ICarenStream‎‎ do fluxo onde os atributos são salvos.‎</param>
	/// <returns></returns>
	CarenResult _MFSerializeAttributesToStream(ICarenMFAttributes^ Param_AtributosSerialize, CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS Param_Flags, ICarenStream^ Param_StreamDestino);

	/// <summary>
	/// ‎Serializa um descritor de apresentação para uma matriz byte.‎
	/// </summary>
	/// <param name="Param_PD">Uma interface ‎‎ICarenMFPresentationDescriptor‎‎ do descritor de apresentação que será serializado. Esse parametro não pode ser NULO.‎</param>
	/// <param name="Param_Out_SizeBuffer">Retorna o tamanho do buffer em (Param_Out_Buffer).</param>
	/// <param name="Param_Out_Buffer">Retorna um buffer que contém o descritor de apresetação serializado. O usuário deve chamar (ReleaseBufferWithCoTaskMemFree) no buffer retornado quando não for mais usar.</param>
	/// <returns></returns>
	CarenResult _MFSerializePresentationDescriptor(ICarenMFPresentationDescriptor^ Param_PD, OutParam UInt32% Param_Out_SizeBuffer, OutParam ICarenBuffer^% Param_Out_Buffer);

	/// <summary>
	/// Carrega atributos de um fluxo em uma loja de atributos.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface (ICarenMFAttributes) que ira receber os atributos deserializados. Esse parametro não pode ser NULO.</param>
	/// <param name="Param_Flags">Bitwise OR de zero ou mais bandeiras da enumeração CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS.</param>
	/// <param name="Param_Stream">Um fluxo a parti do qual será lidos os atributos.</param>
	/// <returns></returns>
	CarenResult _MFDeserializeAttributesFromStream(ICarenMFAttributes^ Param_Atributos, CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS Param_Flags, ICarenStream^ Param_Stream);

	/// <summary>
	/// Deserializa um descritor de apresentação de uma matriz byte.
	/// </summary>
	/// <param name="Param_BufferSize">O tamanho do buffer (Param_Buffer), em bytes.</param>
	/// <param name="Param_Buffer">Um buffer que contém o descritor de apresetação serializado.</param>
	/// <param name="Param_Out_PresentationDescriptor">Retorna a interface (ICarenMFPresentationDescriptor) do descritor de apresetação deserializado. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFDeserializePresentationDescriptor(UInt32 Param_BufferSize, ICarenBuffer^ Param_Buffer, ICarenMFPresentationDescriptor^ Param_Out_PresentationDescriptor);

	/// <summary>
	/// Enumera uma lista de dispositivos de captura de áudio ou vídeo.
	/// </summary>
	/// <param name="Param_Atributos">uma interface (ICarenMFAttributes) para a loja de atributos que contém critérios de pesquisa. Este parametro não pode ser NULO.</param>
	/// <param name="Param_Out_ArraySourceActivate">Recebe uma matriz de interface (ICarenMFActivate). Cada interface representa um objeto de ativação para uma fonte de mídia.</param>
	/// <param name="Param_Out_SizeArray">Recebe o número de elementos no array (Param_Out_ArraySourceActivate). Se nenhum dispositivo de captura corresponder aos critérios de pesquisa, este parâmetro receberá o valor 0.</param>
	/// <returns></returns>
	CarenResult _MFEnumDeviceSources(ICarenMFAttributes^ Param_Atributos, OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArraySourceActivate, OutParam UInt32% Param_Out_SizeArray);

	/// <summary>
	/// Calcula o stride mínimo da superfície para um formato de vídeo.
	/// Esta função calcula o stride mínimo necessário para manter a imagem na memória. Use esta função se estiver alocando buffers na memória do sistema. 
	/// Superfícies alocadas na memória de vídeo podem exigir um stride maior, dependendo da placa gráfica.
	/// </summary>
	/// <param name="Param_Format">Um valor CA_D3DFORMAT que especifica o formato de vídeo.</param>
	/// <param name="Param_Width">Largura da imagem, em pixels.</param>
	/// <param name="Param_Out_Stride">Recebe o stride mínimo da superfície, em pixels.</param>
	/// <returns></returns>
	CarenResult _MFGetStrideForBitmapInfoHeader(CA_D3DFORMAT Param_Format, UInt32 Param_Width, OutParam Int32% Param_Out_Stride);

	/// <summary>
	/// ‎Recupera os tipos MIME registrados para o Source Resolver.
	/// </summary>
	/// <param name="Param_Out_Mimes">Retorna uma (CA_PROPVARIANT) que contém uma lista dos MIME Types.</param>
	/// <returns></returns>
	CarenResult _MFGetSupportedMimeTypes(OutParam CA_PROPVARIANT^% Param_Out_Mimes);

	/// <summary>
	/// ‎Recupera os esquemas de URL registrados para o Source Resolver.
	/// </summary>
	/// <param name="Param_Out_Schemes">Retorna uma (CA_PROPVARIANT) que contém uma lista das URL Schemes suportados.</param>
	/// <returns></returns>
	CarenResult _MFGetSupportedSchemes(OutParam CA_PROPVARIANT^% Param_Out_Schemes);

	/// <summary>
	/// ‎Retorna o tempo do sistema, em unidades de 100 nanossegundos.‎
	/// </summary>
	/// <returns></returns>
	Int64 _MFGetSystemTime();

	/// <summary>
	/// ‎Obtém o tipo de mídia para um fluxo associado a um nó de topologia.‎
	/// ‎Esta função obtém o tipo de mídia real do objeto que está associado ao nó de topologia. O ‎‎parâmetro (Param_Node)‎‎ deve especificar um nó que pertence a uma topologia 
	/// totalmente resolvida. Se o nó pertencer a uma topologia parcial, a função provavelmente falhará.‎
	/// </summary>
	/// <param name="Param_Node">Uma interface (ICarenMFTopologyNode) para o nó na topologia.</param>
	/// <param name="Param_StreamIndex">O identificador do fluxo para consulta. Este parâmetro é interpretado da seguinte forma: 
	/// Transform Nodes-> ‎O valor é o índice baseado em zero do fluxo de entrada ou saída.‎ | ‎Todos os outros tipos de nó‎-> ‎O valor deve ser zero.‎</param>
	/// <param name="Param_Output">‎Se TRUE, ‎‎a função recebe um tipo de saída‎‎. Se FALSE, ‎‎a função recebe um tipo de entrada. ‎Este parâmetro é interpretado da seguinte forma:‎
	/// Ouput Node: Valor deve ser TRUE | Source Node: Valor deve ser FALSE | Tee Node: Valor é ignorado | Transform Node: Se o valor for ‎‎TRUE, ‎‎o parâmetro ‎‎(Param_StreamIndex)‎‎ é o 
	/// índice de um fluxo de saída. Caso contrário, ‎‎(Param_StreamIndex)‎‎ é o índice de um fluxo de entrada.‎</param>
	/// <param name="Param_Out_MediaType">Retora a interface (ICarenMFMediaType) para o tipo de mídia no fluxo. O usuário é responsável por inicializar a interfaces antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFGetTopoNodeCurrentType(ICarenMFTopologyNode^ Param_Node, UInt32 Param_StreamIndex, Boolean Param_Output, ICarenMFMediaType^ Param_Out_MediaType);

	/// <summary>
	/// ‎Recupera o tamanho do buffer necessário para a função _‎‎MFGetAttributesAsBlob.‎
	/// </summary>
	/// <param name="Param_Atributos">A interface de atributos a ser verificada o tamanho necessário para o buffer.</param>
	/// <param name="Param_Out_SizeBuffer">Recebe o tamanho do buffer necessário, em bytes.</param>
	/// <returns></returns>
	CarenResult _MFGetAttributesAsBlobSize(ICarenMFAttributes^ Param_Atributos, OutParam UInt32% Param_Out_SizeBuffer);

	/// <summary>
	/// Converte o conteúdo de uma loja de atributos em uma matriz byte.
	/// </summary>
	/// <param name="Param_AtributosToBlob">A interface (ICarenMFAttributes) que será convertida em uma matriz de bytes.</param>
	/// <param name="Param_BufferDest">Uma interface de buffer que contém um ponteiro para a matriz de bytes de destino. Esse parametro não pode ser NULO.</param>
	/// <param name="Param_SizeBuffer">O tamanho do buffer (Param_BufferDest), em bytes. Para obter esse tamanho ligue para o método (_MFGetAttributesAsBlobSize).</param>
	/// <returns></returns>
	CarenResult _MFGetAttributesAsBlob(ICarenMFAttributes^ Param_AtributosToBlob, ICarenBuffer^ Param_BufferDest, UInt32 Param_SizeBuffer);

	/// <summary>
	/// ‎Inicializa o conteúdo de uma loja de atributos a partir de uma matriz byte.‎
	/// </summary>
	/// <param name="Param_Atributos">A interface de atributos que vai receber os dados. O usuário deve criar a interface com ZERO atributos iniciais.</param>
	/// <param name="Param_Buffer">O buffer que contém os dados serializados dos atributos.</param>
	/// <param name="Param_SizeBuffer">O tamanho do buffer em (Param_Buffer), em bytes.</param>
	/// <returns></returns>
	CarenResult _MFInitAttributesFromBlob(ICarenMFAttributes^ Param_Atributos, ICarenBuffer^ Param_Buffer, UInt32 Param_SizeBuffer);

	/// <summary>
	/// Obtém a ID do sistema local.
	/// </summary>
	/// <param name="Param_Verifier">Um buffer com o valor do verificador específico do aplicativo.</param>
	/// <param name="Param_Size">Comprimento em bytes de verificador.</param>
	/// <param name="Param_Out_ID">Retorna uma string com o ID do sistema local.</param>
	/// <returns></returns>
	CarenResult _MFGetLocalId(ICarenBuffer^ Param_Verifier, UInt32 Param_Size, OutParam String^% Param_Out_ID);

	/// <summary>
	/// Recupera o tamanho da imagem, em bytes, para um formato de vídeo não comprimido.
	/// </summary>
	/// <param name="Param_VideoFormat">Um valor CA_D3DFORMAT que especifica o formato de vídeo.</param>
	/// <param name="Param_Width">Largura da imagem, em pixels.</param>
	/// <param name="Param_Height">Altura da imagem, em pixels</param>
	/// <param name="Param_Out_PlaneSize">Recebe o tamanho de um frame, em bytes. Se o formato for comprimido ou não for reconhecido, esse valor é zero.</param>
	/// <returns></returns>
	CarenResult _MFGetPlaneSize(CA_D3DFORMAT Param_VideoFormat, UInt32 Param_Width, UInt32 Param_Height, OutParam UInt32% Param_Out_PlaneSize);

	/// <summary>
	/// ‎Verifica se um processador de segurança de hardware é suportado para o sistema de proteção de mídia especificado.‎
	/// </summary>
	/// <param name="Param_ProtectionSystemID">‎O identificador do sistema de proteção que você deseja verificar.‎</param>
	/// <param name="Param_Out_Suporte">Recebe ‎TRUE‎‎ se o processador de segurança de hardware for suportado para o sistema de proteção especificado; caso contrário ‎‎FALSE‎‎.‎</param>
	/// <returns></returns>
	CarenResult _MFIsContentProtectionDeviceSupported(String^ Param_ProtectionSystemID, OutParam Boolean% Param_Out_Suporte);

	/// <summary>
	/// C‎onverte um identificador de formato Microsoft DirectX Graphics Infrastructure (DXGI) para um identificador de formato Microsoft Direct3D 9.‎
	/// </summary>
	/// <param name="Param_Format">‎Um valor ‎‎CA_DXGI_FORMAT‎‎ para converter.‎</param>
	/// <returns></returns>
	CA_D3DFORMAT _MFMapDXGIFormatToDX9Format(CA_DXGI_FORMAT Param_Format);

	/// <summary>
	/// ‎Registra um manipulador de byte-stream no processo do chamador.‎
	/// </summary>
	/// <param name="Param_FileExtension">Uma String que contém a extensão do nome do arquivo para este manipulador.</param>
	/// <param name="Param_MIMEType">Uma String que contém o tipo MIME para este manipulador.</param>
	/// <param name="Param_Activate">Uma interface ICarenMFActivate de um objeto de ativação. O chamador implementa esta interface. ‎O ‎‎método ICarenMFActivate::ActivateObject‎‎ deve 
	/// criar um manipulador de fluxo de byte. O manipulador byte-stream expõe a interface ‎‎ICarenMFByteStreamHandler.‎</param>
	/// <returns></returns>
	CarenResult _MFRegisterLocalByteStreamHandler(String^ Param_FileExtension, String^ Param_MIMEType, ICarenMFActivate^ Param_Activate);

	/// <summary>
	/// ‎Registra um manipulador de esquemas no processo do chamador.‎
	/// </summary>
	/// <param name="Param_Scheme">‎Uma String que contém o esquema. O esquema inclui o caractere ':'; por exemplo, "http:".‎</param>
	/// <param name="Param_Activate">Uma interface ICarenMFActivate de um objeto de ativação. O chamador implementa esta interface. ‎O ‎‎método ICarenMFActivate::ActivateObject‎‎ deve 
	/// criar um manipulador de esquema. O manipulador de esquema expõe a interface ‎‎IMFSchemeHandler[NÃO IMPLEMENTADA PELA DLL].</param>
	/// <returns></returns>
	CarenResult _MFRegisterLocalSchemeHandler(String^ Param_Scheme, ICarenMFActivate^ Param_Activate);

	/// <summary>
	/// Verifica se uma apresentação de mídia requer o PMP (Protected Media Path, Caminho de Mídia Protegida).
	/// </summary>
	/// <param name="Param_PresentationDesc">Uma interface ICarenMFPresentationDescriptor de um descritor de apresentação. O descritor de apresentação é criado pela fonte 
	/// de mídia e descreve a apresentação.</param>
	/// <returns></returns>
	CarenResult _MFRequireProtectedEnvironment(ICarenMFPresentationDescriptor^ Param_PresentationDesc);

	/// <summary>
	/// ‎Empacota dois valores UINT32, que representam uma razão, em um valor UINT64.‎
	/// </summary>
	/// <param name="Param_Numerador">O valor do numerador para ser armazenado como UINT32.‎</param>
	/// <param name="Param_Denominador">O valor do denominador ‎‎UINT32 para ser armazenado</param>
	/// <returns></returns>
	UInt64 _PackRatio(Int32 Param_Numerador, UInt32 Param_Denominador);

	/// <summary>
	/// ‎Empacota um valor de largura UINT32 e um valor de altura UINT32 em um valor UINT64 que representa um tamanho.‎
	/// </summary>
	/// <param name="Param_Width">O valor UINT32 da largura a ser armazenada.</param>
	/// <param name="Param_Height">O valor UINT32 da altura a ser armazenada.</param>
	/// <returns></returns>
	UInt64 _PackSize(UInt32 Param_Width, UInt32 Param_Height);

	/// <summary>
	/// ‎Obtém os valores ‎‎UINT32‎‎ de baixa ordem e alta ordem a partir de um valor ‎‎UINT64‎‎ que representa uma razão.‎
	/// </summary>
	/// <param name="Param_UnPacked">O valor a ser convertido.</param>
	/// <param name="Param_Out_Numerador">‎Recebe o valor de alta ordem de 32 bits.‎</param>
	/// <param name="Param_Out_Denominador">‎Recebe o valor de baixa ordem de 32 bits.‎</param>
	void _UnpackRatio(UInt64 Param_UnPacked, OutParam Int32% Param_Out_Numerador, OutParam UInt32% Param_Out_Denominador);

	/// <summary>
	/// ‎Obtém os valores ‎‎UINT32‎‎ de baixa ordem e alta ordem a partir de um valor ‎‎UINT64‎‎ que representa um tamanho.‎
	/// </summary>
	/// <param name="Param_UnPacked">O valor a ser convertido.</param>
	/// <param name="Param_Out_Width">‎Recebe o valor de alta ordem de 32 bits.‎</param>
	/// <param name="Param_Out_Height">‎Recebe o valor de baixa ordem de 32 bits.</param>
	void _UnpackSize(UInt64 Param_UnPacked, OutParam UInt32% Param_Out_Width, OutParam UInt32% Param_Out_Height);

	/// <summary>
	/// ‎Obtém os valores ‎‎UINT32‎‎ de baixa ordem e alta ordem a partir de um valor ‎‎UINT64.‎
	/// </summary>
	/// <param name="Param_UnPacked">O valor a ser convertido.</param>
	/// <param name="Param_Out_High">Recebe o valor de alta ordem de 32 bits.</param>
	/// <param name="Param_Out_Low">‎Recebe o valor de baixa ordem de 32 bits.</param>
	/// <returns></returns>
	void _Unpack2UINT32AsUINT64(UInt64 Param_UnPacked, OutParam UInt32% Param_Out_High, OutParam UInt32% Param_Out_Low);

	/// <summary>
	/// ‎Desliga um objeto da Media Foundation e libera todos os recursos associados ao objeto.‎
	/// ‎Esta função é uma função de ajudante que envolve o método ‎‎IMFShutdown::Shutdown.‎‎ A função consulta o objeto para a interface ‎‎IMFShutdown‎‎ e,
	/// se bem-sucedida, chama ‎‎de Shutdown‎‎ no objeto.‎
	/// </summary>
	/// <param name="Param_Objeto">Uma interface base que contém um ponteiro para a interface a ser desligada.</param>
	/// <returns></returns>
	CarenResult _MFShutdownObject(ICaren^ Param_Objeto);

	/// <summary>
	/// Obtém informações do registro sobre uma transformação da Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_ClsidMFT">O CLSID do MFT.</param>
	/// <param name="Param_Out_NomeMFT">Recebe uma string contendo o nome amigável do MFT. Este parametro é opcional.</param>
	/// <param name="Param_Out_ArrayInputTypes">Recebe uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz descreve um formato de entrada que o MFT suporta. Este parametro é opcional.</param>
	/// <param name="Param_Out_CountArrayInputTypes">Recebe a quantidadede entradas na matriz (Param_Out_ArrayInputTypes). Retorna (0) se (Param_Out_ArrayInputTypes) for ignorado.</param>
	/// <param name="Param_Out_ArrayOutputTypes">Recebe uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz descreve um formato de saída que o MFT suporta. Este parametro é opcional.</param>
	/// <param name="Param_Out_CountArrayOutputTypes">Recebe a quantidadede entradas na matriz (Param_Out_ArrayOutputTypes). Retorna (0) se (Param_Out_ArrayOutputTypes) for ignorado.</param>
	/// <param name="Param_Out_Atributos">Recebe uma interface ICarenMFAttributes de uma loja de atributos. A loja de atributos pode conter atributos armazenados no registro para o 
	/// MFT especificado. Este parametro pode ser NULO. O usuário é responsável por inicializar a interfaces antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFTGetInfo(
		String^ Param_ClsidMFT,
		CarenParameterResolver<String^>% Param_Out_NomeMFT, //Ref Value
		CarenParameterResolver<cli::array<CA_MFT_REGISTER_TYPE_INFO^>^>% Param_Out_ArrayInputTypes, //Ref Value
		OutParam UInt32% Param_Out_CountArrayInputTypes,
		CarenParameterResolver<cli::array<CA_MFT_REGISTER_TYPE_INFO^>^>% Param_Out_ArrayOutputTypes, //Ref Value
		OutParam UInt32% Param_Out_CountArrayOutputTypes,
		ICarenMFAttributes^ Param_Out_Atributos
	);

	/// <summary>
	/// Recebe uma lista de transformações (MFTs) da Microsoft Media Foundation que correspondem aos critérios de pesquisa especificados. Essa 
	/// função amplia a função _MFTEnumEx para permitir que aplicativos externos e componentes internos descubram os MFTs de hardware que 
	/// correspondem a um adaptador de vídeo específico.
	/// </summary>
	/// <param name="Param_GuidCategory">Um GUID que especifica a categoria de CMTs para enumerar. Para obter uma lista de categorias MFT, 
	/// consulte a estrutura (GUIDs::GUIDs_MFT_CATEGORY).</param>
	/// <param name="Param_Flags">Um OR bitwise de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG.</param>
	/// <param name="Param_InputType">uma estrutura CA_MFT_REGISTER_TYPE_INFO que especifica um tipo de mídia de entrada para combinar.
	/// Este parâmetro pode ser NULO. Se NULO, todos os tipos de saída são combinados.</param>
	/// <param name="Param_OutputType">Uma estrutura MFT_REGISTER_TYPE_INFO que especifica um tipo de mídia de saída para combinar.
	/// Este parâmetro pode ser NULO. Se NULO, todos os tipos de saída ão combinados.</param>
	/// <param name="Param_Atributos">Uma interface (ICarenMFAttributes) que permite o acesso à loja de atributos padrão. Para especificar um 
	/// adaptador de hardware específico para o qual os MFTs são consultados, defina o atributo MFT_ENUM_ADAPTER_LUID ao LUID do adaptador. Se 
	/// você fizer isso, você também deve especificar a MFT_ENUM_FLAG_HARDWARE bandeira ou ER_E_INVALIDARG é devolvida.</param>
	/// <param name="Param_Out_ArrayMFTActivate">Recebe uma matriz de ponteiros de interface DO FMIActivate. Cada ponteiro representa um objeto de ativação de um MFT que corresponde aos critérios de pesquisa. A função aloca a memória para a matriz.</param>
	/// <param name="Param_Out_CountMFTs">Retorna a quantidade de MFTs no array (Param_Out_ArrayMFTActivate). Se nenhum MFTs corresponder aos critérios de pesquisa, este parâmetro receberá o valor zero.‎</param>
	/// <returns></returns>
	CarenResult _MFTEnum2(
		String^ Param_GuidCategory,
		CA_MFT_ENUM_FLAG Param_Flags,
		CA_MFT_REGISTER_TYPE_INFO^ Param_InputType,
		CA_MFT_REGISTER_TYPE_INFO^ Param_OutputType,
		ICarenMFAttributes^ Param_Atributos,
		OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArrayMFTActivate,
		OutParam UInt32% Param_Out_CountMFTs
	);

	/// <summary>
	/// ‎Recebe uma lista de transformações (MFTs) da Microsoft Media Foundation que correspondem aos critérios de pesquisa especificados. Esta função estende a função ‎‎MFTEnum.‎
	/// </summary>
	/// <param name="Param_GuidCategory">Um GUID que especifica a categoria de CMTs para enumerar. Para obter uma lista de categorias MFT, consulte a estrutura 
	/// (GUIDs::GUIDs_MFT_CATEGORY).</param>
	/// <param name="Param_Flags">Um OR bitwise de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG.</param>
	/// <param name="Param_InputType">uma estrutura CA_MFT_REGISTER_TYPE_INFO que especifica um tipo de mídia de entrada para combinar.
	/// Este parâmetro pode ser NULO. Se NULO, todos os tipos de saída são combinados.</param>
	/// <param name="Param_OutputType">Uma estrutura MFT_REGISTER_TYPE_INFO que especifica um tipo de mídia de saída para combinar.
	/// Este parâmetro pode ser NULO. Se NULO, todos os tipos de saída ão combinados.</param>
	/// <param name="Param_Out_ArrayMFTActivate">Recebe uma matriz de ponteiros de interface DO FMIActivate. Cada ponteiro representa um objeto de ativação de um MFT que corresponde aos critérios de pesquisa. A função aloca a memória para a matriz.</param>
	/// <param name="Param_Out_CountMFTs"></param>
	/// <returns></returns>
	CarenResult _MFTEnumEx(
		String^ Param_GuidCategory,
		CA_MFT_ENUM_FLAG Param_Flags,
		CA_MFT_REGISTER_TYPE_INFO^ Param_InputType,
		CA_MFT_REGISTER_TYPE_INFO^ Param_OutputType,
		OutParam cli::array<ICarenMFActivate^>^% Param_Out_ArrayMFTActivate,
		OutParam UInt32% Param_Out_CountMFTs
	);

	/// <summary>
	/// Adiciona informações sobre uma transformação da Media Foundation (MFT) ao registro.
	/// </summary>
	/// <param name="Param_ClsidMFT">O CLSID do MFT. O MFT também deve ser registrado como um objeto COM usando o mesmo CLSID.</param>
	/// <param name="Param_GuidCategory">GUID que especifica a categoria do MFT. Para obter uma lista de categorias MFT, consulte a estrutura (GUIDs::GUIDs_MFT_CATEGORY).</param>
	/// <param name="Param_Name">O nome amigável do MFT.</param>
	/// <param name="Param_Flags">Um OR bitwise de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG. Definir bandeiras a zero é equivalente à configuração da bandeira 
	/// MFT_ENUM_FLAG_SYNCMFT. O modelo de processamento padrão para MFTs é o processamento síncrocro.</param>
	/// <param name="Param_CountInputTypes">Número de elementos na matriz (Param_ArrayInputTypes).</param>
	/// <param name="Param_ArrayInputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz especifica um formato de entrada que o MFT suporta. 
	/// Este parâmetro pode ser NULO.</param>
	/// <param name="Param_CountOutputTypes">Número de elementos na matriz (Param_ArrayOutputTypes).</param>
	/// <param name="Param_ArrayOutputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz define um formato de saída que o MFT suporta.
	/// Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Atributos">Uma interface ICarenMFAttributes de uma loja de atributos que contém informações adicionais de registro. Este parâmetro pode ser NULO. 
	/// Se o parâmetro não for NULO, os atributos são escritos no registro como uma matriz de byte. Você pode usar a função _MFTGetInfo para recuperar os atributos.</param>
	/// <returns></returns>
	CarenResult _MFTRegister(
		String^ Param_ClsidMFT,
		String^ Param_GuidCategory,
		String^ Param_Name,
		CA_MFT_ENUM_FLAG Param_Flags,
		UInt32 Param_CountInputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes,
		UInt32 Param_CountOutputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes,
		ICarenMFAttributes^ Param_Atributos
	);

	/// <summary>
	/// Registra uma transformação da Media Foundation (MFT) no processo do chamador.
	/// </summary>
	/// <param name="Param_ClassFactoryMFT">Uma interface base (ICaren) que contém um ponteiro para a interface IClassFactory de um objeto de fábrica de classe. A fábrica de classes cria o MFT.</param>
	/// <param name="Param_GuidCategory">GUID que especifica a categoria do MFT. Para obter uma lista de categorias MFT, consulte a estrutura (GUIDs::GUIDs_MFT_CATEGORY).</param>
	/// <param name="Param_Name">O nome amigável do MFT.</param>
	/// <param name="Param_Flags">Um OR bitwise de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG. Definir bandeiras a zero é equivalente à configuração da bandeira 
	/// MFT_ENUM_FLAG_SYNCMFT. O modelo de processamento padrão para MFTs é o processamento síncrocro.</param>
	/// <param name="Param_CountInputTypes">Número de elementos na matriz (Param_ArrayInputTypes).</param>
	/// <param name="Param_ArrayInputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz especifica um formato de entrada que o MFT suporta. 
	/// Este parâmetro pode ser NULO.</param>
	/// <param name="Param_CountOutputTypes">Número de elementos na matriz (Param_ArrayOutputTypes).</param>
	/// <param name="Param_ArrayOutputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz define um formato de saída que o MFT suporta.
	/// Este parâmetro pode ser NULO.</param>
	/// <returns></returns>
	CarenResult _MFTRegisterLocal(
		ICaren^ Param_ClassFactoryMFT,
		String^ Param_GuidCategory,
		String^ Param_Name,
		CA_MFT_ENUM_FLAG Param_Flags,
		UInt32 Param_CountInputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes,
		UInt32 Param_CountOutputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes
	);

	/// <summary>
	/// Registra uma transformação da Media Foundation (MFT) no processo do chamador.
	/// </summary>
	/// <param name="Param_ClsidMFT">O CLSID do MFT.</param>
	/// <param name="Param_GuidCategory">GUID que especifica a categoria do MFT. Para obter uma lista de categorias MFT, consulte a estrutura (GUIDs::GUIDs_MFT_CATEGORY).</param>
	/// <param name="Param_Name">O nome amigável do MFT.</param>
	/// <param name="Param_Flags">Um OR bitwise de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG. Definir bandeiras a zero é equivalente à configuração da bandeira 
	/// MFT_ENUM_FLAG_SYNCMFT. O modelo de processamento padrão para MFTs é o processamento síncrocro.</param>
	/// <param name="Param_CountInputTypes">Número de elementos na matriz (Param_ArrayInputTypes).</param>
	/// <param name="Param_ArrayInputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz especifica um formato de entrada que o MFT suporta. 
	/// Este parâmetro pode ser NULO.</param>
	/// <param name="Param_CountOutputTypes">Número de elementos na matriz (Param_ArrayOutputTypes).</param>
	/// <param name="Param_ArrayOutputTypes">Uma matriz de estruturas CA_MFT_REGISTER_TYPE_INFO. Cada membro da matriz define um formato de saída que o MFT suporta.
	/// Este parâmetro pode ser NULO.</param>
	/// <returns></returns>
	CarenResult _MFTRegisterLocalByCLSID(
		String^ Param_ClsidMFT,
		String^ Param_GuidCategory,
		String^ Param_Name,
		CA_MFT_ENUM_FLAG Param_Flags,
		UInt32 Param_CountInputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayInputTypes,
		UInt32 Param_CountOutputTypes,
		cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ Param_ArrayOutputTypes
	);

	/// <summary>
	/// Remove o registro de uma transformação da Media Foundation (MFT).
	/// Esta função remove as entradas de registro criadas pela função _MFTRegister.
	/// </summary>
	/// <param name="Param_ClsidMFT">O CLSID do MFT.</param>
	/// <returns></returns>
	CarenResult _MFTUnregister(String^ Param_ClsidMFT);

	/// <summary>
	/// Remove o registro de uma ou mais transformações da Media Foundation (MFTs) do processo do chamador.
	/// Use esta função para não registrar um MFT local que foi previamente registrado através da função _MFTRegisterLocal.
	/// </summary>
	/// <param name="Param_ClassFactoryMFT">Uma interface base (ICaren) que contém um ponteiro para a interface IClassFactory de um objeto de fábrica de classe. 
	/// Este parâmetro pode ser NULO.</param>
	/// <returns></returns>
	CarenResult _MFTUnregisterLocal(ICaren^ Param_ClassFactoryMFT);
	
	/// <summary>
	/// Remove o registro de uma ou mais transformações da Media Foundation (MFTs) do processo do chamador.
	/// </summary>
	/// <param name="Param_ClsidMFT">O CLSID do MFT.</param>
	/// <returns></returns>
	CarenResult _MFTUnregisterLocalByCLSID(String^ Param_ClsidMFT);

	/// <summary>
	/// Cria o mix de vídeo padrão e o apresentador de vídeo para o renderizador de vídeo aprimorado (EVR).
	/// </summary>
	/// <param name="Param_MixerOwner">Uma interface base (ICaren) para o dono do Mixer. Se o mixer for agregado, passe uma interface IUnknown do objeto agregador. 
	/// Caso contrário, defina este parâmetro para NULO.</param>
	/// <param name="Param_PresenterOwner">Uma interface base (ICaren) para o dono do apresentador de video. Se o apresentador for agregado, passe uma interface IUnknown do objeto 
	/// agregador. Caso contrário, defina este parâmetro para NULO.</param>
	/// <param name="Param_RiidMixer">Identificador de interface (IID) da interface solicitada no mixador de vídeo. O mixer de vídeo expõe a interface ICarenMFTransform.</param>
	/// <param name="Param_Out_Mixer">Retorna a interface solicitada do Mixer. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <param name="Param_RiidPresenter">IID da interface solicitada no apresentador de vídeo. O apresentador de vídeo expõe a interface ICarenMFVideoPresenter.</param>
	/// <param name="Param_Out_Presenter">Retorna a interface solicitada do apresentador. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoMixerAndPresenter(
		ICaren^ Param_MixerOwner, 
		ICaren^ Param_PresenterOwner, 
		String^ Param_RiidMixer,
		ICaren^ Param_Out_Mixer,
		String^ Param_RiidPresenter,
		ICaren^ Param_Out_Presenter
		);

	/// <summary>
	/// ‎Cria uma fila de eventos.‎
	/// </summary>
	/// <param name="Param_Out_EventQueue">Retorna uma interface base (ICaren) para a interface (IMFMediaEventQueue[NÃO IMPLEMENTADA PELA DLL]). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateEventQueue(ICaren^ Param_Out_EventQueue);
	
	/// <summary>
	/// ‎Cria um objeto que aloca amostras de vídeo compatíveis com o Direct3D 9.
	/// </summary>
	/// <param name="Param_RIID">‎O identificador da interface para recuperar. Especifique um dos seguintes valores: IID_IUnknown, IID_IMFVideoSampleAllocator, IID_IMFVideoSampleAllocatorCallback.</param>
	/// <param name="Param_Out_SampleAllocator">Recebe uma interface base (ICaren) para a interface requisitada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoSampleAllocator(String^ Param_RIID, ICaren^ Param_Out_SampleAllocator);

	/// <summary>
	/// ‎Cria um objeto que aloca amostras de vídeo compatíveis com o Microsoft DirectX Graphics Infrastructure (DXGI).‎
	/// </summary>
	/// <param name="Param_RIID">‎O identificador da interface para recuperar. Especifique um dos seguintes valores: IID_IUnknown, IID_IMFVideoSampleAllocator, IID_IMFVideoSampleAllocatorEx, IID_IMFVideoSampleAllocatorCallback.</param>
	/// <param name="Param_Out_SampleAllocator">Recebe uma interface base (ICaren) para a interface requisitada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoSampleAllocatorEx(String^ Param_RIID, ICaren^ Param_Out_SampleAllocator);

	/// <summary>
	/// ‎Cria um objeto ‎‎IRandomAccessStream‎‎ que envolve um fluxo byte da Microsoft Media Foundation.‎
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream para o fluxode bytes da Media Foundation.</param>
	/// <param name="Param_RIID">‎O identificador de interface (IID) da interface que está sendo solicitada.‎</param>
	/// <param name="Param_Out_Stream">Retorna uma interface base (ICaren) para a interface IRandomAccessStream do fluxo de bytes para a (ICarenMFByteStream). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateStreamOnMFByteStreamEx(ICarenMFByteStream^ Param_ByteStream, String^ Param_RIID, ICaren^ Param_Out_Stream);

	/// <summary>
	/// Cria a fonte do sequenciador.
	/// </summary>
	/// <param name="Param_Reservado">Reservado. Deve ser NULO.</param>
	/// <param name="Param_Out_SequencerSource">Retorna a interface base (ICaren) para a interface (IMFSequencerSource[NÃO IMPLEMENTADA PELA DLL]) da fonte do sequenciador. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSequencerSource(ICaren^ Param_Reservado, ICaren^ Param_Out_SequencerSource);

	/// <summary>
	/// Cria um objeto de ativação para o Sample Grabber Media Sink(Sink de captura de amostras).
	/// </summary>
	/// <param name="Param_MediaType">Um interface ICarenMFMediaType, definindo o tipo de mídia para o fluxo de entrada do Sample Grabber(Capturador de amostras).</param>
	/// <param name="Param_SampleGrabberCallback">Uma interface IMFSampleGrabberSinkCallback[INTERFACE PENDENTE] para o callback. O usuário deve implementar esta interface.</param>
	/// <param name="Param_Out_Activate">Retorna uma interface (ICarenMFActivate) para o ativador. Use esta interface para completar a criação do Sample Grabber(Capturador de amostras). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSampleGrabberSinkActivate(ICarenMFMediaType^ Param_MediaType, ICaren^ Param_SampleGrabberCallback, ICarenMFActivate^ Param_Out_Activate);

	/// <summary>
	/// A copiadora de amostras é uma transformação da Media Foundation (MFT) que copia dados de amostras de entrada para amostras de saída sem modificar os dados. Os seguintes dados são copiados da amostra:
	/// Todos os atributos da amostra | O carimbo de tempo e duração | Bandeiras de amostra (ver ICarenMFSample::SetSampleFlags) | Os dados nos buffers de mídia. Se a amostra de entrada contiver vários buffers, 
	/// os dados são copiados em um único buffer na amostra de saída.
	/// </summary>
	/// <param name="Param_Out_CopierMFT">Recebe uma interface (ICarenMFTransform) para a transformação. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateSampleCopierMFT(ICarenMFTransform^ Param_Out_CopierMFT);

	/// <summary>
	/// Cria um objeto de ativação genérico para transformações da Media Foundation (MFTs).
	/// </summary>
	/// <param name="Param_Out_Activate">Recebe uma interface (ICarenMFActivate) para o ativador da transformação. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTransformActivate(ICarenMFActivate^ Param_Out_Activate);

	/// <summary>
	/// Cria a misturadora de vídeo padrão para o renderizador de vídeo aprimorado (EVR).
	/// </summary>
	/// <param name="Param_Owner">Ponteiro para o dono deste objeto. Se o objeto for agregado, passe um ponteiro para a interface IUnknown do objeto agregador. Caso contrário, defina este parâmetro para NULO.</param>
	/// <param name="Param_RIIDDevice">Identificador de interface (IID) da interface do dispositivo de vídeo que será usado para processar o vídeo. Atualmente, o único valor suportado é IID_IDirect3DDevice9.</param>
	/// <param name="Param_RIID">IID da interface solicitada na mixer de vídeo. O mixer de vídeo expõe a interface ICarenMFTransform.</param>
	/// <param name="Param_Out_Objeto">Recebe a interface solicitada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoMixer(ICaren^ Param_Owner, String^ Param_RIIDDevice, String^ Param_RIID, ICaren^ Param_Out_Objeto);

	/// <summary>
	/// Cria um objeto IMFProtectedEnvironmentAccess[NÃO IMPLEMENTADA PELA DLL] que permite que sistemas de proteção de conteúdo realizem um handshake(aperto de mão) com o ambiente protegido.
	/// </summary>
	/// <param name="Param_Out_Access">Retorna uma interface base (ICaren) para a interface (IMFProtectedEnvironmentAccess[NÃO IMPLEMENTADA PELA DLL]). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateProtectedEnvironmentAccess(ICaren^ Param_Out_Access);

	/// <summary>
	/// Cria o objeto PMP (Protected Media Path, Caminho de Mídia Protegida (PMP).
	/// </summary>
	/// <param name="Param_Flags">Um membro da enumeração CA_MFPMPSESSION_CREATION_FLAGS que especifica como criar a sessão PMP.</param>
	/// <param name="Param_Out_PMPServer">Retorna uma interface base (ICaren) para a interface (IMFPMPServer[NÃO IMPLEMENTADA PELA DLL]). O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreatePMPServer(CA_MFPMPSESSION_CREATION_FLAGS Param_Flags, ICaren^ Param_Out_PMPServer);
	
	/// <summary>
	/// Consulta um objeto para uma interface de serviço especificada.
	/// Esta função é uma função de ajudante que envolve o método ICarenMFGetService::GetService. A função consulta o objeto para a interface ICarenMFGetService e, se bem-sucedida, chama o GetService no objeto.
	/// </summary>
	/// <param name="Param_Objeto">A interface do objeto a ser consultado.</param>
	/// <param name="Param_GuidService">O identificador de serviço (SID) do serviço. Para obter uma lista de identificadores de serviço, consulte a estrutura (GUIDs::GUIDs_MF_SERVICE_INTERFACES)</param>
	/// <param name="Param_RIID">O identificador de interface (IID) da interface que está sendo solicitada.</param>
	/// <param name="Param_Out_InterfaceRequested">Retorna a interface solicitada se encontrada. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFGetService(
		ICaren^ Param_Objeto, 
		String^ Param_GuidService,
		String^ Param_RIID, 
		ICaren^ Param_Out_InterfaceRequested);

	/// <summary>
	/// Cria um fluxo byte que é apoiado por um arquivo local temporário.
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado do arquivo temporário. O usuário é responsável por inicializar a interace antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTempFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode,
		CA_MF_FILE_OPENMODE Param_OpenMode,
		CA_MF_FILE_FLAGS Param_Flags,
		ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Cria um fluxo byte de um arquivo de forma sincrona.
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Url">Uma string que contém a url para o arquivo.</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado do arquivo. O usuário é responsável por inicializar a interace antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode,
		CA_MF_FILE_OPENMODE Param_OpenMode,
		CA_MF_FILE_FLAGS Param_Flags,
		String^ Param_Url,
		ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Começa uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// Quando a solicitação for concluída, o método ICarenMFAsyncCallback do objeto de chamada é chamado. O objeto de retorno de chamada deve então chamar a função _MFEndCreateFile para obter a interface para o fluxo byte(ICarenMFByteStream).
	/// </summary>
	/// <param name="Param_AccessMode">O modo de acesso solicitado, especificado como membro da enumeração CA_MF_FILE_ACCESSMODE.</param>
	/// <param name="Param_OpenMode">O comportamento da função se o arquivo já existe ou não existe, especificado como membro da enumeração CA_MF_FILE_OPENMODE.</param>
	/// <param name="Param_Flags">Bitwise OR de valores da enumeração MF_FILE_FLAGS.</param>
	/// <param name="Param_Url">Uma string que contém a url para o arquivo.</param>
	/// <param name="Param_Callback">Uma interface ICarenMFAsyncCallback de um objeto de retorno de chamada. O chamador deve implementar esta interface</param>
	/// <param name="Param_ObjectState">Uma interface IUnknown de um objeto de estado, definido pelo chamador. Este parâmetro pode ser NULO. Você pode usar este objeto para conter informações do estado. O objeto é devolvido ao chamador quando o retorno de chamada é invocado.</param>
	/// <param name="Param_Out_CancelCookie">Recebe uma interface IUnknown ou o valor NULO. Se o valor não for NULO, você pode cancelar a operação assíncrona passando esta interface para a função _MFCancelCreateFile. O chamador deve liberar a interface. Este parâmetro é opcional e pode ser NULO.</param>
	/// <returns></returns>
	CarenResult _MFBeginCreateFile(
		CA_MF_FILE_ACCESSMODE Param_AccessMode, 
		CA_MF_FILE_OPENMODE Param_OpenMode, 
		CA_MF_FILE_FLAGS Param_Flags, 
		String^ Param_Url, 
		ICarenMFAsyncCallback^ Param_Callback,
		ICaren^ Param_ObjectState,
		ICaren^ Param_Out_CancelCookie);

	/// <summary>
	/// Completa uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// </summary>
	/// <param name="Param_Result">Uma interface ICarenMFAsyncResult. Passe a mesma interface que seu objeto de retorno de chamada recebeu no método (Invoke).</param>
	/// <param name="Param_Out_ByteStream">Recebe a interface (ICarenMFByteStream) para o fluxo de bytes criado. O usuário é responsável por inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFEndCreateFile(ICarenMFAsyncResult^ Param_Result, ICarenMFByteStream^ Param_Out_ByteStream);

	/// <summary>
	/// Cancela uma solicitação assíncrona para criar um fluxo de byte a partir de um arquivo.
	/// </summary>
	/// <param name="Param_CancelCookie">Uma interface IUnknown do objeto de cancelamento. Esta interface é recebida no parâmetro (Param_Out_CancelCookie) da função _MFBeginCreateFile.</param>
	/// <returns></returns>
	CarenResult _MFCancelCreateFile(ICaren^ Param_CancelCookie);

	/// <summary>
	/// Cria um objeto de ativação para uma classe do Windows Runtime.
	/// </summary>
	/// <param name="Param_ActivatableClassId">O identificador de classe que está associado à classe de tempo de execução ativável.</param>
	/// <param name="Param_Configuration">Um ponteiro para um objeto IPropertySet opcional, que é usado para configurar a classe do Windows Runtime. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_RIID">O identificador de interface(IID) da interface solicitada.O objeto de ativação criado por esta função suporta as seguintes interfaces: IClassFactory, ICarenMFActivate, ICarenPersisStream</param>
	/// <param name="Param_Out_Objeto">Recebe a interface que foi solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMediaExtensionActivate(String^ Param_ActivatableClassId, ICaren^ Param_Configuration, String^ Param_RIID, ICaren^ Param_Out_Objeto);

	/// <summary>
	/// Cria uma interface IMFContentDecryptorContext para o sistema de proteção de mídia especificado.
	/// </summary>
	/// <param name="Param_GuidMediaProtectionSystem">O identificador do sistema de proteção de mídia para o qual você deseja criar uma interface IMFContentDecryptorContext.</param>
	/// <param name="Param_DXGIManager">Uma interface ICarenMFDXGIDeviceManager que você deseja usar para compartilhar o dispositivo Direct3D 11.</param>
	/// <param name="Param_ProtectionDevice">A interface IMFContentProtectionDevice para o sistema de proteção de mídia especificado.</param>
	/// <param name="Param_Out_ContentDecryptorContext">Retorna um pontiro para a interface (IMFContentDecryptorContext) criada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateContentDecryptorContext(String^ Param_GuidMediaProtectionSystem, ICarenMFDXGIDeviceManager^ Param_DXGIManager, ICaren^ Param_ProtectionDevice, ICaren^ Param_Out_ContentDecryptorContext);

	/// <summary>
	/// Cria uma interface IMFContentProtectionDevice para o sistema de proteção de mídia especificado.
	/// </summary>
	/// <param name="Param_GuidMediaProtectionSystem">O identificador do sistema de proteção de mídia para o qual você deseja criar a interface IMFContentProtectionDevice.</param>
	/// <param name="Param_Out_ContentProtectionDevice">Retorna um pontiro para a interface (IMFContentProtectionDevice) criada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateContentProtectionDevice(String^ Param_GuidMediaProtectionSystem, ICaren^ Param_Out_ContentProtectionDevice);

	/// <summary>
	/// Cria um objeto de serviços DXVA (DirectX Video Acceleration, aceleração de vídeo directx). Ligue para esta função se o aplicativo usar O DXVA diretamente, sem usar o DirectShow ou a Media Foundation.
	/// </summary>
	/// <param name="Param_Direct3DDevice9">Umaa interface IDirect3DDevice9 de um dispositivo Direct3D.</param>
	/// <param name="Param_RIID">O identificador de interface (IID) da interface solicitada. Qualquer uma das seguintes interfaces pode ser suportada pelo dispositivo Direct3D: IDirectXVideoAcacelerationService | 
	/// IDirectXVideoDecoderService | IDirectXVideoProcessorService</param>
	/// <param name="Param_Out_VideoService">Recebe o ponteiro para a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _DXVA2CreateVideoService(ICaren^ Param_Direct3DDevice9, String^ Param_RIID, ICaren^ Param_Out_VideoService);

	/// <summary>
	/// Aloca a memória do sistema com um alinhamento de byte especificado e cria um buffer de mídia para gerenciar a memória.
	/// </summary>
	/// <param name="Param_MaxLenght">O tamanho do buffer, em bytes.</param>
	/// <param name="Param_Aligment">Especifica o alinhamento de memória para o buffer.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAlignedMemoryBuffer(UInt32 Param_MaxLenght, CA_MF_BYTE_ALIGNMENT Param_Aligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um buffer de mídia para gerenciar uma superfície DXGI (Microsoft DirectX Graphics Infrastructure).
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície DXGI. Este valor deve ser IID_ID3D11Texture2D.</param>
	/// <param name="Param_SuperficeDXGI">Uma interface IUnknown da superfície DXGI.</param>
	/// <param name="Param_SubresourceIndex">O índice baseado em zero de uma subrefonte da superfície. O objeto buffer de mídia está associado a essa subrefonte.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. Este objeto suporta as seguintes interfaces de buffer: ICarenMF2DBuffer, ICarenMF2DBuffer2, ICarenMFDXGIBuffer e ICarenMFMediaBuffer. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXGISurfaceBuffer(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_SubresourceIndex, Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia uma superfície Direct3D 9.
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície Direct3D 9. Atualmente esse valor deve ser IID_IDirect3DSurface9.</param>
	/// <param name="Param_SurfaceDX">Uma interface IUnknown da superfície DirectX.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXSurfaceBuffer(String^ Param_RIID, ICaren^ Param_SurfaceDX,  Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Aloca um buffer de memória do sistema que é ideal para um tipo de mídia especificado.
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType do tipo de mídia.</param>
	/// <param name="Param_Duration">A duração da amostra. Este valor é necessário para formatos de áudio.</param>
	/// <param name="Param_MinLenght">O tamanho mínimo do buffer, em bytes. O tamanho real do buffer pode ser maior. Especifique zero para alocar o tamanho padrão do buffer para o tipo de mídia.</param>
	/// <param name="Param_MinAligment">O alinhamento mínimo da memória para o buffer. Especifique zero para usar o alinhamento de memória padrão.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMediaBufferFromMediaType(ICarenMFMediaType^ Param_MediaType, Int64 Param_Duration, UInt32 Param_MinLenght, UInt32 Param_MinAligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia um bitmap do Windows Imaging Component (WIC).
	/// </summary>
	/// <param name="Param_RIID">O identificador da interface. Atualmente este parametro deve ser IID_IWICBitmap</param>
	/// <param name="Param_Surface">Uma interface IUnknown da superfície bitmap. A superfície bitmap deve ser um bitmap WIC que expõe a interface ICarenWICBitmap.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWICBitmapBuffer(String^ Param_RIID, ICaren^ Param_Surface, ICarenMFMediaBuffer^ Param_Out_Buffer);
	
	/// <summary>
	/// Invoca um método de retorno para completar uma operação assíncrona.
	/// </summary>
	/// <param name="Param_AsyncResult">Uma interface ICarenMFAsyncResult para completar a operação.</param>
	/// <returns></returns>
	CarenResult _MFInvokeCallback(ICarenMFAsyncResult^ Param_AsyncResult);

	/// <summary>
	/// Cria um ICarenMFAttributes descrevendo o conteúdo de substreams multiplexados.
	/// </summary>
	/// <param name="Param_ColecaoAtributosMuxStream">A coleção contendo os (IMFAttributes) para cada substream multiplexado.</param>
	/// <param name="Param_Out_Atribtuos">Retorna a interface contendo os atributos para os substreams multiplexados. O usuário deve inicializar a interface antes de chamar este método.</param>
	CarenResult _MFCreateMuxStreamAttributes(ICarenMFCollection^ Param_ColecaoAtributosMuxStream, ICarenMFAttributes^ Param_Out_Atribtuos);

	/// <summary>
	/// Cria um objeto de ativação para o (Streaming Audio Render).
	/// </summary>
	/// <param name="Param_Out_StreamingAudioRender">Retorna a interface (ICarenMFActivate) de ativação do (Streaming Audio Render). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAudioRendererActivate(ICarenMFActivate^ Param_Out_StreamingAudioRender);

	/// <summary>
	/// Cria um objeto de ativação para o (Enhanced Video Renderer (EVR)).
	/// </summary>
	/// <param name="Param_Hwnd">A handle para a janela que vai exibir o vídeo.</param>
	/// <param name="Param_Out_EnhancedVideoRenderer">Retorna a interface (ICarenMFActivate) de ativação do (Enhanced Video Renderer). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoRendererActivate(IntPtr Param_Hwnd, ICarenMFActivate^ Param_Out_EnhancedVideoRenderer);

	/// <summary>
	/// Cria uma nova instância do Media Sink para o SAR (Streaming Audio Render).
	/// </summary>
	/// <param name="Param_AudioAtributos">Uma interface ICarenMFAttributes, que é usada para configurar o renderizador de áudio. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) para o SAR. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAudioRenderer(ICarenMFAttributes^ Param_AudioAtributos, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do Media Sink do processador de vídeo aprimorado (EVR).
	/// </summary>
	/// <param name="Param_RIID">Identificador de interface (IID) da interface solicitada no EVR.</param>
	/// <param name="Param_Out_VideoRenderer">Recebe a interface solicitada. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateVideoRenderer(String^ Param_RIID, ICaren^ Param_Out_VideoRenderer);

	/// <summary>
	/// Cria um media sink para criar arquivos 3GP.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo 3GP para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia 3GP(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreate3GPMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do AC-3 media sink.
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo AC-3 para este fluxo de byte. O fluxo de byte deve ser escrito.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo de áudio AC-3. O tipo de mídia deve conter os seguintes atributos: MF_MT_MAJOR_TYPE & MF_MT_SUBTYPE</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia 3GP(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAC3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma instância do media sink do fluxo de transporte de dados de áudio (ADTS).
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o fluxo ADTS para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo ADTS. O tipo de mídia deve conter os seguintes atributos: MF_MT_MAJOR_TYPE & MF_MT_SUBTYPE & MF_MT_AAC_PAYLOAD_TYPE</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateADTSMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor de arquivos WAVE. O coletor de arquivos WAVE pega o áudio e o grava em um arquivo .wav.
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o fluxo WAVE para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType. Este parâmetro especifica o tipo de mídia para o fluxo WAVE.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia WAVE(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWAVEMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria uma nova instância do coletor de midia MP3(Media Sink).
	/// </summary>
	/// <param name="Param_ByteStream">Um a interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo mp3 para este fluxo byte. O fluxo de byte deve ter permissão de escrita.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMP3MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um media sink para a criação de arquivos MP4 fragmentados.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo MP4 para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia MP4(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateFMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um media sink para a criação de arquivos MP4.
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo AVI para este fluxo byte.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia AVI(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMPEG4MediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor Audio-Video Interleaved (AVI).
	/// </summary>
	/// <param name="Param_ByteStream">Uma interface ICarenMFByteStream de um fluxo byte. O Media Sink grava o arquivo MP4 para este fluxo byte. O fluxo byte deve ser escrito e apoiar a busca.</param>
	/// <param name="Param_VideoType">Uma interface ICarenMFMediaType de um tipo de mídia de vídeo. Este tipo especifica o formato da transmissão de vídeo. Este parâmetro pode ser NULO, mas não se (Param_AudioType) for NULO.</param>
	/// <param name="Param_AudioType">Uma interface ICarenMFMediaType de um tipo de mídia de áudio. Este tipo especifica o formato do fluxo de áudio. Este parâmetro pode ser NULO, mas não se (Param_VideoType) for NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia MP4(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAVIMediaSink(ICarenMFByteStream^ Param_ByteStream, ICarenMFMediaType^ Param_VideoType, ICarenMFMediaType^ Param_AudioType, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um coletor de mídia(Media Sink) genérico que envolve uma transformação multiplexadora do Microsoft Media Foundation (MFT).
	/// </summary>
	/// <param name="Param_GuidOutputSubtype">O GUID do subtipo do tipo de saída para o MFT.</param>
	/// <param name="Param_OutputAttributes">Uma lista de atributos de formato para o tipo de saída MFT. Este parâmetro é opcional e pode ser NULO.</param>
	/// <param name="Param_OutputByteStream">uma interface ICarenMFByteStream de um fluxo de bytes. A saída do MFT é gravada neste fluxo de bytes. Este parâmetro pode ser NULO.</param>
	/// <param name="Param_Out_MediaSink">Retorna a interface (ICarenMFMediaSink) do coletor de mídia(Media Sink). O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMuxSink(String^ Param_GuidOutputSubtype, ICarenMFAttributes^ Param_OutputAttributes, ICarenMFByteStream^ Param_OutputByteStream, ICarenMFMediaSink^ Param_Out_MediaSink);

	/// <summary>
	/// Cria um objeto de ativação que representa um dispositivo de captura de hardware.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface ICarenMFAttributes de uma loja de atributos, que é usada para selecionar o dispositivo de captura.</param>
	/// <param name="Param_Out_DispositivoCaptura">Retorna a interface (ICarenMFActivate) de ativação do dispositivo de captura. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDeviceSourceActivate(ICarenMFAttributes^ Param_Atributos, ICarenMFActivate^ Param_Out_DispositivoCaptura);

	/// <summary>
	/// Cria o objeto de ativação para um Sink de Transcodificação.
	/// O objeto de ativação do coletor de transcodificação pode ser usado para criar qualquer um dos seguintes coletores de arquivo: Coletor de arquivo 3GP, MP3 ou MP4.
	/// </summary>
	/// <param name="Param_Out_Transcode">Retorna uma interface ICarenMFActivate. Esta interface é usada para criar a instância do coletor de arquivos a partir do objeto de ativação. Antes de fazer isso, consulte o 
	/// ponteiro retornado para a interface ICarenMFTranscodeSinkInfoProvider e use essa interface para inicializar o objeto.  O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateTranscodeSinkActivate(CarenMFActivate^ Param_Out_Transcode);

	/// <summary>
	/// Cria um objeto de ativação que pode ser usado para criar um codificador WMA (Windows Media Audio).
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType. Este parâmetro especifica o formato de saída codificado.</param>
	/// <param name="Param_EncodingProperties">Uma interface ICarenPropertyStore de uma loja de propriedades que contém parâmetros de codificação. Os parâmetros de codificação do codificador WMV são definidos no arquivo de cabeçalho wmcodecdsp.h. Se você tiver um objeto ASF ContentInfo que contenha um objeto de perfil ASF com todos os fluxos para o arquivo de saída, você pode obter a loja de propriedades ligando para IMFASFContentInfo::GetEncodingConfigurationPropertyStore.</param>
	/// <param name="Param_Out_Codificador">Retorna uma interface (ICarenMFActivate) do objeto de ativação para o codificador de áudio WMA. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWMAEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador);

	/// <summary>
	/// Cria um objeto de ativação que pode ser usado para criar um codificador WMV (Windows Media Video).
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType. Este parâmetro especifica o formato de saída codificado.</param>
	/// <param name="Param_EncodingProperties">Uma interface ICarenPropertyStore de uma loja de propriedades que contém parâmetros de codificação. Os parâmetros de codificação do codificador WMV são definidos no arquivo de cabeçalho wmcodecdsp.h. Se você tiver um objeto ASF ContentInfo que contenha um objeto de perfil ASF com todos os fluxos para o arquivo de saída, você pode obter a loja de propriedades ligando para IMFASFContentInfo::GetEncodingConfigurationPropertyStore.</param>
	/// <param name="Param_Out_Codificador">Retorna uma interface (ICarenMFActivate) do objeto de ativação para o codificador de áudio WMA. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateWMVEncoderActivate(ICarenMFMediaType^ Param_MediaType, ICarenPropertyStore^ Param_EncodingProperties, ICarenMFActivate^ Param_Out_Codificador);

	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult _MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEXEXTENSIBLE^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	
	/// <summary>
	/// Converte um tipo de mídia de áudio do Media Foundation para uma estrutura Wav.
	/// </summary>
	/// <param name="Param_TipoMidia">O tipo de mídia que será convertida para uma estrutura Wav.</param>
	/// <param name="Param_FlagsConversão">Os flags utilizados para conversão.</param>
	/// <param name="Param_Out_WavFormato">Recebe a estrutura wav com os dados do formato.</param>
	/// <param name="Param_Out_Size">Recebe o tamanho da estrutura em bytes.</param>
	CarenResult _MFCreateWaveFormatExFromMFMediaType(
		ICarenMFMediaType^ Param_TipoMidia,
		CA_MFWaveFormatExConvertFlags Param_FlagsConversão,
		[Out] CA_WAVEFORMATEX^% Param_Out_WavFormato,
		[Out] UInt32% Param_Out_Size);
	
	/// <summary>
	/// Inicializa um tipo de mídia de um WAVEFORMATEX estrutura.
	/// </summary>
	/// <param name="Param_WavFormato">Uma estrutura wav que contém as informações do tipo de midia a ser criado.</param>
	/// <param name="Param_SizeEstrutura">O tamanho da estrutura em bytes.</param>
	/// <param name="Param_Out_TipoMidia">Retorna o tipo de midia convertida da estrutura Wav. O usuário é responsável por inicializar a classe antes de chamar este método.</param>
	CarenResult CA_MFInitMediaTypeFromWaveFormatEx(
		CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, 
		UInt32 Param_SizeEstrutura, 
		ICarenMFMediaType^ Param_Out_TipoMidia);
};

