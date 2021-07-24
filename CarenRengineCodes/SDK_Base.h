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
#include "Header.h"
#include "Caren/CarenHMONITOR.h"
#include "CarenGuids.h"
#include "ParameterResolver/CarenParamResolver.h"

//Importa o namespace do sistema
using namespace System;

//Importa o namespace base
using namespace CarenRengine;

//Namespace principal do sistema.
namespace CarenRengine
{
	//SDK base que contém todas as estruturas, Enumerações e GUIDs utilizados por toda a biblioteca da CarenRengine.
	namespace SDKBase
	{
		//Namespace que contém todos os guids utilizadas pelas APIs presentes.
		namespace GUIDs
		{

			//MEDIA FOUNDATION API//


			//ATRIBUTOS.

			/// <summary>
			/// Contém todos os GUIDs utilizados pela interface IMFMediaType.
			/// </summary>
			public value struct GUIDs_MF_MEDIATYPE_ATTRIBUTES
			{

				////////////////////////////////////////////////////////////////////
				//TODOS OS GUIDS A PARTI DAQUI PERTENCEM A INTERFACE: IMFMediaType//
				////////////////////////////////////////////////////////////////////


				//-> Atributos de formatos em geral.


				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica se cada exemplo é independente de outros exemplos no fluxo.
				/// </summary>
				literal String^ MF_MT_ALL_SAMPLES_INDEPENDENT = "{C9173739-5E56-461C-B713-46FB995CB95F}";
				/// <summary>
				/// Tipo do valor: GUID.
				/// Formatar GUID.
				/// </summary>
				literal String^ MF_MT_AM_FORMAT_TYPE = "{73D1072D-1870-4174-A063-29FF4FF6C11E}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica se os dados de mídia são compactados
				/// </summary>
				literal String^ MF_MT_COMPRESSED = "{3AFD0CEE-18F2-4BA5-A110-8BEA502E1F92}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica se os exemplos têm um Dimensionar fixo.
				/// </summary>
				literal String^ MF_MT_FIXED_SIZE_SAMPLES = "{B8EBEFAF-B718-4E04-B0A9-116775E3321B}";
				/// <summary>
				/// Tipo do valor: GUID.
				/// O Tipo principal da mídia.
				/// </summary>
				literal String^ MF_MT_MAJOR_TYPE = "{48EBA18E-F8C9-4687-BF11-0A74C9F96A8F}";
				/// <summary>
				/// Tipo do valor: GUID.
				/// O subtipo da mídia. Define o formato do fluxo principal(MF_MT_MAJOR_TYPE).
				/// </summary>
				literal String^ MF_MT_SUBTYPE = "{F7E34C9A-42E8-4714-B74B-CB29D72C35E5}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Tamanho de cada amostra, em bytes.
				/// </summary>
				literal String^ MF_MT_SAMPLE_SIZE = "{DAD3AB78-1990-408B-BCE2-EBA673DACC10}";
				/// <summary>
				/// Tipo do valor: Byte Array(Blob).
				/// Contém dados de usuário para um tipo de mídia que foi convertido de uma estrutura de formato herdado.
				/// </summary>
				literal String^ MF_MT_USER_DATA = "{B6BC765F-4C3B-40A4-BD51-2535B66FE09D}";
				/// <summary>
				/// Tipo do valor: Byte Array(Blob).
				/// Contém um tipo de mídia que foi encapsulado em outro tipo de mídia.
				/// </summary>
				literal String^ MF_MT_WRAPPED_TYPE = "{4D3F7B23-D02F-4E6C-9BEE-E4BF2C6C695D}";
				/// <summary>
				/// Tipo do valor: String.
				/// Contém o Codec ID da midia especificada
				/// </summary>
				literal String^ MF_MT_MIDIA_CODEC_ID = "{9668DDE5-C869-4D6A-B02E-463B7C231B53}";



				//-> Atributos para os formatos de (Áudio)




				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica o perfil de áudio e o nível de um fluxo de codificação de áudio avançada (AAC).
				/// </summary>
				literal String^ MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION = "{7632F0E6-9538-4d61-ACDA-EA29C8C14456}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica o tipo de carga de um fluxo de codificação de áudio avançada (AAC).
				/// 0 -> O fluxo contém raw_data_block elementos somente.
				/// 1 -> Fluxo de transporte de dados de áudio (ADTS). O fluxo contém um adts_sequence, 
				/// conforme definido pelo MPEG-2.
				/// 2 -> Audio Data Interchange Format (ADIF). O fluxo contém um adif_sequence, conforme definido pelo MPEG-2.
				/// 3 -> O fluxo contém um fluxo de transporte de áudio MPEG-4 com uma camada de sincronização (LOAS)
				/// e uma camada Multiplex (LATM).
				/// </summary>
				literal String^ MF_MT_AAC_PAYLOAD_TYPE = "{BFBABE79-7434-4d1c-94F0-72A3B9E17188}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número médio de bytes por segundo em um tipo de mídia de áudio.
				/// Esse atributo corresponde do nAvgBytesPerSec membro das WAVEFORMATEX estrutura.
				/// </summary>
				literal String^ MF_MT_AUDIO_AVG_BYTES_PER_SECOND = "{1aab75c8-cfef-451c-ab95-ac034b8e1731}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número de bits por amostra de áudio em um tipo de mídia de áudio.
				/// Esse atributo corresponde do wBitsPerSample membro das WAVEFORMATEX estrutura.
				/// Se alguns bits contêm preenchimento, defina o atributo MF_MT_AUDIO_VALID_BITS_PER_SAMPLE para especificar o número de 
				/// bits de dados de áudio válidos em cada exemplo.
				/// </summary>
				literal String^ MF_MT_AUDIO_BITS_PER_SAMPLE = "{f2deb57f-40fa-4764-aa33-ed4f2d1ff669}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Alinhamento de bloco, em bytes, para um tipo de mídia de áudio. O alinhamento do bloco é a unidade atômica mínima de dados
				/// para o formato de áudio.
				/// Para formatos de áudio PCM, o alinhamento de bloco é igual ao número de canais de áudio multiplicado pelo número de bytes 
				/// por amostra de áudio.Esse atributo corresponde do nBlockAlign membro das WAVEFORMATEX estrutura.
				/// </summary>
				literal String^ MF_MT_AUDIO_BLOCK_ALIGNMENT = "{322de230-9eeb-43bd-ab7a-ff412251541d}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Em um tipo de mídia de áudio, especifica a atribuição de canais de áudio para posições de alto-falante.
				/// </summary>
				literal String^ MF_MT_AUDIO_CHANNEL_MASK = "{55fb5765-644a-4caf-8479-938983bb1588}";
				/// <summary>
				/// Tipo do valor: Double.
				/// Número de amostras de áudio por segundo em um tipo de mídia de áudio.
				/// </summary>
				literal String^ MF_MT_AUDIO_FLOAT_SAMPLES_PER_SECOND = "{fb3b724a-cfb5-4319-aefe-6e42b2406132}";
				/// <summary>
				/// {Não implementado}
				/// Tipo do valor: Byte Array(Blob).
				/// Especifica como um decodificador de áudio deve transformar áudio multicanal para saída estéreo. Este processo também é chamado de fold-down.
				/// </summary>
				literal String^ MF_MT_AUDIO_FOLDDOWN_MATRIX = "{9d62927c-36be-4cf2-b5c4-a3926e3e8711}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número de canais de áudio em um tipo de mídia de áudio.
				/// </summary>
				literal String^ MF_MT_AUDIO_NUM_CHANNELS = "{37e48bf5-645e-4c5b-89de-ada9e29b696a}";
				/// <summary>
				/// Tipo do valor: UInt32 > trate como um valor Booleano(0 ou 1).
				/// Especifica a estrutura de formato herdado preferencial para usar ao converter um tipo de mídia de áudio.
				/// </summary>
				literal String^ MF_MT_AUDIO_PREFER_WAVEFORMATEX = "{a901aaba-e037-458a-bdf6-545be2074042}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número de amostras de áudio contidas em um bloco compactado de dados de áudio. Esse atributo pode ser usado em 
				/// formatos de áudio compactados que têm um número fixo de amostras dentro de cada bloco.
				/// </summary>
				literal String^ MF_MT_AUDIO_SAMPLES_PER_BLOCK = "{aab15aac-e13a-4995-9222-501ea15c6877}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número de amostras de áudio por segundo em um tipo de mídia de áudio.
				/// </summary>
				literal String^ MF_MT_AUDIO_SAMPLES_PER_SECOND = "{5faeeae7-0290-4c31-9e8a-c534f68d9dba}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número de bits válidos de dados de áudio em cada amostra de áudio.
				/// Este atributo é usado para formatos de áudio que contêm preenchimento após cada amostra de áudio.
				/// O tamanho total de cada amostra de áudio, incluindo bits de preenchimento, é fornecido no atributo MF_MT_AUDIO_BITS_PER_SAMPLE.
				/// </summary>
				literal String^ MF_MT_AUDIO_VALID_BITS_PER_SAMPLE = "{d9bf8d6a-9530-4b7c-9ddf-ff6fd58bbd06}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Nível de volume médio de referência de um arquivo de áudio do Windows Media.
				/// Esse atributo se aplica a tipos de mídia de áudio para codecs de áudio do Windows Media. Ele especifica o nível de volume médio 
				/// original do conteúdo. O decodificador pode usar esse valor para executar o controle de intervalo dinâmico.
				/// </summary>
				literal String^ MF_MT_AUDIO_WMADRC_AVGREF = "{0x9d62927f-36be-4cf2-b5c4-a3926e3e8711}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Nível de volume médio de destino de um arquivo de áudio do Windows Media.
				/// Esse atributo se aplica a tipos de mídia de áudio para codecs de áudio do Windows Media.
				/// </summary>
				literal String^ MF_MT_AUDIO_WMADRC_AVGTARGET = "{0x9d629280-36be-4cf2-b5c4-a3926e3e8711}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Nível de volume de pico de referência de um arquivo de áudio do Windows Media.
				/// Esse atributo se aplica a tipos de mídia de áudio para codecs de áudio do Windows Media.
				/// </summary>
				literal String^ MF_MT_AUDIO_WMADRC_PEAKREF = "{0x9d62927d-36be-4cf2-b5c4-a3926e3e8711}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Nível de volume de pico de destino de um arquivo de áudio do Windows Media.
				/// Esse atributo se aplica a tipos de mídia de áudio para codecs de áudio do Windows Media.
				/// </summary>
				literal String^ MF_MT_AUDIO_WMADRC_PEAKTARGET = "{0x9d62927e-36be-4cf2-b5c4-a3926e3e8711}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Contém a marca de formato WAVE original para um fluxo de áudio.
				/// Dependendo do arquivo de origem, a fonte de mídia AVI pode definir esse atributo nos tipos de mídia que ele oferece.
				/// </summary>
				literal String^ MF_MT_ORIGINAL_WAVE_FORMAT_TAG = "{8cbbc843-9fd9-49c2-882f-a72586c408ad}";




				//-> Atributos para os formatos de (Vídeo)




				/// <summary>
				/// Tipo do valor: UInt32.
				/// Taxa de erro de dados, em erros de bits por segundo, para um tipo de mídia de vídeo.
				/// Esse atributo corresponde do dwBitErrorRate membro das estruturas de VIDEOINFOHEADER e VIDEOINFOHEADER2.
				/// </summary>
				literal String^ MF_MT_AVG_BIT_ERROR_RATE = "{799cabd6-3508-4db4-a3c7-569cd533deb1}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Taxa de dados aproximada do fluxo de vídeo, em bits por segundo, para um tipo de mídia de vídeo.
				/// Esse atributo corresponde ao dwBitRate membro das estruturas de VIDEOINFOHEADER e VIDEOINFOHEADER2.
				/// </summary>
				literal String^ MF_MT_AVG_BITRATE = "{20332624-fb0d-4d9e-bd0d-cbf6786c102e}";
				/// <summary>
				/// {Não implementado}
				/// Tipo do valor: UInt32.
				/// Especifica as (Cores Primárias) personalizadas para um tipo de mídia de vídeo.
				/// </summary>
				literal String^ MF_MT_CUSTOM_VIDEO_PRIMARIES = "{47537213-8cfb-4722-aa34-fbc9e24d77b8}";
				/// <summary>
				/// Tipo do valor: UInt32 > Trate como um valor Int32.
				/// Passo de superfície padrão, para um tipo de mídia de vídeo descompactado. Stride é o número de bytes necessários para 
				/// ir de uma linha de pixels para o próximo.
				/// O valor do atributo é armazenado como um UINT32, mas deve ser convertido em um valor inteiro assinado de 32 bits.
				/// Stride pode ser negativo.
				/// </summary>
				literal String^ MF_MT_DEFAULT_STRIDE = "{644b4e48-1e02-4516-b0eb-c01ca9d49ac6}";
				/// <summary>
				/// Tipo do valor: UInt32
				/// Especifica se um tipo de mídia de vídeo requer a imposição de proteção contra cópia.
				/// </summary>
				literal String^ MF_MT_DRM_FLAGS = "{8772f323-355a-4cc7-bb78-6d61a048ae82}";
				/// <summary>
				/// Tipo do valor: UInt64.
				/// Método:DefinirRatioAttribute | ObterRatioAttribute
				/// Taxa de quadros de um tipo de mídia de vídeo, em quadros por segundo.
				/// A taxa de quadros é expressa como uma razão. Os 32 bits superiores do valor do atributo contêm o numerador e os bits 
				/// 32 inferiores contêm o denominador. Por exemplo, se a taxa de quadros for 30 quadros por segundo (FPS), a proporção 
				/// será 30/1. Se a taxa de quadros é 29,97 fps, a proporção é 30000/1001.
				/// </summary>
				literal String^ MF_MT_FRAME_RATE = "{c459a2e8-3d2c-4e44-b132-fee5156c7bb0}";
				/// <summary>
				/// Tipo do valor: UInt64.
				/// Método: DefinirRatioAttribute | ObterRatioAttribute
				/// A taxa de quadros máxima que é suportada por um dispositivo de captura de vídeo, em quadros por segundo.
				/// </summary>
				literal String^ MF_MT_FRAME_RATE_RANGE_MAX = "{E3371D41-B4CF-4a05-BD4E-20B88BB2C4D6}";
				/// <summary>
				/// Tipo do valor: UInt64.
				/// Método: DefinirRatioAttribute | ObterRatioAttribute
				/// A taxa de quadros mínima que é suportada por um dispositivo de captura de vídeo, em quadros por segundo.
				/// A taxa de quadros é expressa como uma razão. Os 32 bits superiores do valor do atributo contêm o numerador, e os bits 
				/// 32 inferiores contêm o denominador. Por exemplo, se a taxa de quadros for 30 quadros por segundo (FPS), a proporção será 30/1.
				/// </summary>
				literal String^ MF_MT_FRAME_RATE_RANGE_MIN = "{D2E7558C-DC1F-403f-9A72-D28BB1EB3B5E}";
				/// <summary>
				/// Tipo do valor: UInt64.
				/// Método: MFGetAttributeSize | MFGetAttributeSize
				/// Largura e altura de um quadro de vídeo, em pixels.
				/// </summary>
				literal String^ MF_MT_FRAME_SIZE = "{1652c33d-d6b2-4012-b834-72030849a37d}";
				/// <summary>
				/// Tipo do valor: Byte Array (Blob).
				/// Define a abertura geométrica para um tipo de mídia de vídeo.
				/// O valor desse atributo é um Mfvideoarea estrutura.
				/// A relação de aspecto da imagem é calculada em relação à abertura geométrica, usando a seguinte fórmula : proporção de imagem = 
				/// (largura de abertura geométrica / altura de abertura geométrica) × proporção de pixel.
				/// Se esse atributo não estiver definido, a abertura geométrica será considerada o quadro de vídeo inteiro.Você deve definir esse 
				/// atributo somente quando o tipo de mídia descreve um padrão de vídeo com uma área ativa definida.
				/// </summary>
				literal String^ MF_MT_GEOMETRIC_APERTURE = "{66758743-7e5f-400d-980a-aa8596c85696}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Descreve como os quadros em um tipo de mídia de vídeo são entrelaçados.
				/// O valor desse atributo é membro da enumeração: CA_VIDEO_MODO_ENTRELACAMENTO
				/// </summary>
				literal String^ MF_MT_INTERLACE_MODE = "{e2724bb8-e676-4806-b4b2-a8d6efb44ccd";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Número máximo de quadros de um quadro-chave para o próximo, em um tipo de mídia de vídeo.
				/// </summary>
				literal String^ MF_MT_MAX_KEYFRAME_SPACING = "{c16eb52b-73a1-476f-8d62-839d6a020652}";
				/// <summary>
				/// Tipo do valor: Byte Array(Blob).
				/// Define a abertura de exibição, que é a região de um quadro de vídeo que contém dados de imagem válidos.
				/// A abertura mínima de exibição é a região que contém a parte válida do sinal. Os pixels fora da abertura contêm dados 
				/// inválidos e não devem ser exibidos.
				/// </summary>
				literal String^ MF_MT_MINIMUM_DISPLAY_APERTURE = "{d7388766-18fe-48c6-a177-ee894867c8c4}";
				/// <summary>
				/// Tipo do valor: Byte Array(Blob).
				/// Contém o cabeçalho de sequência MPEG-1 ou MPEG-2 para um tipo de mídia de vídeo.
				/// </summary>
				literal String^ MF_MT_MPEG_SEQUENCE_HEADER = "{3c036de7-3ad0-4c9e-9216-ee6d6ac21cb3}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Código de hora de início do grupo de imagens (GOP), para um tipo de mídia de vídeo MPEG-1 ou MPEG-2.
				/// </summary>
				literal String^ MF_MT_MPEG_START_TIME_CODE = "{91F67885-4333-4280-97CD-BD5A6C03A06E}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Contém diversos sinalizadores para um tipo de mídia de vídeo MPEG-2.
				/// </summary>
				literal String^ MF_MT_MPEG2_FLAGS = "{31E3991D-F701-4B2F-B426-8AE3BDA9E04B}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica o (Nível) MPEG-2 ou H.264 em um tipo de mídia de vídeo.
				/// Para vídeo MPEG-2, o valor desse atributo é um membro da enumeração:  CA_ENCODE_NIVEL_AM_MPEG2.
				/// Para vídeo H.264, o valor é um membro da enumeração: CA_ENCODE_NIVEL_eAVEncH264V .
				/// </summary>
				literal String^ MF_MT_MPEG2_LEVEL = "{96F66574-11C5-4015-8666-BFF516436DA7}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica o perfil MPEG-2 ou H.264 em um tipo de mídia de vídeo.
				/// Para vídeo MPEG-2, o valor desse atributo é um membro da enumeração AC_VIDEO_PERFIL_AM_MPEG2Profile.
				/// Para vídeo H. 264, o valor é um membro da enumeração AC_VIDEO_PERFIL_eAVEncH264VProfile.
				/// </summary>
				literal String^ MF_MT_MPEG2_PROFILE = "{AD76A80B-2D5C-4E0B-B375-64E520137036}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Contém o codec original FOURCC para um fluxo de vídeo.
				/// </summary>
				literal String^ MF_MT_ORIGINAL_4CC = "{D7BE3FE0-2BC7-492D-B843-61A1919B70C3}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica a taxa de proporção do retângulo de saída para um tipo de mídia de vídeo.
				/// O valor desse atributo corresponde a enumeração: CA_VIDEO_PAD_FLAGS
				/// </summary>
				literal String^ MF_MT_PAD_CONTROL_FLAGS = "{4D0E73E5-80EA-4354-A9D0-1176CEB028EA}";
				/// <summary>
				/// {Não disponível}
				/// Tipo do valor: Byte Array(Blob).
				/// Contém as entradas de paleta para um tipo de mídia de vídeo. Use este atributo para formatos de vídeo palettized, 
				/// como RGB 8.
				/// </summary>
				literal String^ MF_MT_PALETTE = "{6D283F42-9846-4410-AFD9-654D503B1A54}";
				/// <summary>
				/// {Não implementado}
				/// Tipo do valor: Byte Array(Blob).
				/// Define a abertura de Pan/Scan, que é a região de 4 × 3 de vídeo que deve ser exibida no modo Pan/Scan.
				/// </summary>
				literal String^ MF_MT_PAN_SCAN_APERTURE = "{79614DDE-9187-48FB-B8C7-4D52689DE649}";
				/// <summary>
				/// Tipo do valor: UInt32 > Deve ser tratado como valor booleano(0 ou 1).
				/// Especifica se o modo Pan/Scan está habilitado.
				/// Se esse atributo for true, somente a região de Pan/Scan do vídeo deve ser exibida. A região de Pan/Scan é especificada 
				/// pelo atributo MF_MT_PAN_SCAN_APERTURE .
				/// </summary>
				literal String^ MF_MT_PAN_SCAN_ENABLED = "{4B7F6BC3-8B13-40B2-A993-ABF630B8204E}";
				/// <summary>
				/// Tipo do valor: UInt64.
				/// Método: ObterRatioAttribute | DefinirRatioAttribute.
				/// Proporção de pixel para um tipo de mídia de vídeo.
				/// Os 32 bits superiores contêm o numerador da taxa de proporção de pixel e os bits 32 inferiores contêm o denominador. O numerador é o componente
				/// horizontal da relação de aspecto; o denominador é o componente vertical.
				/// </summary>
				literal String^ MF_MT_PIXEL_ASPECT_RATIO = "{c6376a1e-8d0a-4027-be45-6d9a0ad39bb6}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// O valor desse atributo é um membro da enumeração: CA_MFVideoSrcContentHintFlags.
				/// </summary>
				literal String^ MF_MT_SOURCE_CONTENT_HINT = "{68ACA3CC-22D0-44E6-85F8-28167197FA38}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica a função de conversão de RGB para R'G'B' para um tipo de mídia de vídeo.
				/// O valor desse atributo é um membro da enumeração: CA_MFVideoTransferFunction
				/// </summary>
				literal String^ MF_MT_TRANSFER_FUNCTION = "{5FB0FCE9-BE5C-4935-A811-EC838F8EED93}";
				/// <summary>
				/// Tipo do valor: UInt32 -> Trate como um valor Booleano(0 ou 1).
				/// Especifica se um fluxo de vídeo contém conteúdo 3D.
				/// Esse atributo se aplica a tipos de mídia de vídeo. Se esse atributo for true, o fluxo de vídeo conterá conteúdo 3D. 
				/// O valor padrão é false.
				/// </summary>
				literal String^ MF_MT_VIDEO_3D = "{CB5E88CF-7B5B-476B-85AA-1CA5AE187555}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Descreve como o croma foi amostrado para um tipo de mídia de vídeo de Y'Cb'Cr'.
				/// O valor desse atributo é um bit a bit ou de sinalizadores da enumeração: CA_MFVideoChromaSubsampling
				/// </summary>
				literal String^ MF_MT_VIDEO_CHROMA_SITING = "{65DF2370-C773-4C33-AA64-843E068EFB0C}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica as condições de iluminação ideais para um tipo de mídia de vídeo.
				///  O valor desse atributo é um membro da enumeração: CA_MFVideoLighting.
				/// </summary>
				literal String^ MF_MT_VIDEO_LIGHTING = "{53A0529C-890B-4216-8BF9-599367AD6D20}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica o intervalo nominal das informações de cor em um tipo de mídia de vídeo.
				/// O valor desse atributo é um membro da enumeração: CA_MFNominalRange
				/// Codificadores H. 264/AVC:
				/// No tipo de mídia de saída, MF_MT_VIDEO_NOMINAL_RANGE pode ser definido com MFNominalRange_0_255 e MFNominalRange_16_235.
				/// Codificador H. 264 / AVC deve tratar MFNominalRange_Unknown como MFNominalRange_16_235.
				/// Codificador H. 264 / AVC deve rejeitar um tipo de mídia de saída quando MF_MT_VIDEO_NOMINAL_RANGE é definido como MFNominalRange_48_208, 
				/// MFNominalRange_64_127, ou quaisquer outros valores não definidos em CA_MFNominalRange.
				/// </summary>
				literal String^ MF_MT_VIDEO_NOMINAL_RANGE = "{C21B8EE5-B956-4071-8DAF-325EDF5CAB11}";
				/// <summary>
				/// {Pendente} Tipo do valor: UInt32.
				/// Especifica as primárias de cores para um tipo de mídia de vídeo.
				/// O valor desse atributo é um membro da enumeração: CA_MFVideoPrimaries
				/// </summary>
				literal String^ MF_MT_VIDEO_PRIMARIES = "{DBFBE4D7-0740-4EE0-8192-850AB0E21935}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica a rotação de uma moldura de vídeo no sentido anti-horário.
				/// O valor desse atributo é um membro da enumeração: CA_MFVideoRotationFormat
				/// O vídeo de um dispositivo portátil, como um telemóvel, é frequentemente girado por 90, 180 ou 270 graus. Se a câmera armazena a orientação como 
				/// metadados no arquivo de vídeo, a imagem pode ser ajustada no momento da reprodução.
				/// Se este atributo definido como MFVideoRotationFormat_90, significa que o conteúdo foi girado 90 graus no sentido anti-horário. Se o conteúdo foi 
				/// girado 90 graus no sentido horário, o valor do atributo seria MFVideoRotationFormat_270.
				/// </summary>
				literal String^ MF_MT_VIDEO_ROTATION = "{C380465D-2271-428C-9B83-ECEA3B4A85C1}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Para tipos de mídia YUV, define a matriz de conversão do espaço de cores Y'Cb'Cr' para o espaço de cores R'G'B'.
				/// O valor desse atributo é um membro da enumeração: CA_MFVideoTransferMatrix
				/// </summary>
				literal String^ MF_MT_YUV_MATRIX = "{3E23D450-2C75-4D25-A00E-B91670D12327}";
				/// <summary>
				/// Tipo do valor: UInt32 > Trate como um valor booleano(0 ou 1).
				/// Especifica se o chamador alocará as texturas usadas para saída.
				/// Se esse atributo for true, o processador de vídeo espera que as texturas de saída sejam alocadas pelo chamador, mesmo quando operando no modo DXVA 
				/// (DirectX Video Acceleration). Se esse atributo for false, o processador de vídeo alocará as texturas de saída ao operar no modo DXVA e falhará se 
				/// as texturas de saída fornecidas pelo chamador forem fornecidas.
				/// Para definir esse atributo obtenha um (ICarenMFAttributes) da interface (ICarenMFTransform) no processador de vídeo.
				/// </summary>
				literal String^ MF_XVP_CALLER_ALLOCATES_OUTPUT = "{04A2CABC-0CAB-40B1-A1B9-75BC3658F000}";
				/// <summary>
				/// Tipo do valor: UInt32 > Trate como um valor booleano(0 ou 1).
				/// Desativa a conversão de taxa de quadros no (processador de vídeo MFT).
				/// Se esse atributo for true, o processador de vídeo não executará a conversão de taxa de quadros. Por padrão, o processador de vídeo converterá a 
				/// taxa de quadros para corresponder ao tipo de mídia de saída.
				/// Para definir esse atributo obtenha um (ICarenMFAttributes) da interface (ICarenMFTransform) no processador de vídeo.
				/// </summary>
				literal String^ MF_XVP_DISABLE_FRC = "{2C0AFA19-7A97-4D5A-9EE8-16D4FC518D8C}";




				//-> Atributos para os formatos de midia (ASF)




				/// <summary>
				/// Tipo do valor: Byte Array.
				/// Dados de formato adicionais para um fluxo binário em um arquivo de formato de sistemas avançados (ASF).
				/// Os aplicativos podem usar fluxos binários para armazenar tipos de dados personalizados. A fonte de mídia ASF trata o valor 
				/// desse atributo como um blob opaco
				/// </summary>
				literal String^ MF_MT_ARBITRARY_FORMAT = "{5A75B249-0D7D-49A1-A1C3-E0D87F0CADE5}";
				/// <summary>
				/// Tipo do valor: Byte Array armazenado como (MT_ARBITRARY_HEADER).
				/// Dados específicos do tipo para um fluxo binário em um arquivo de formato de sistemas avançados (ASF).
				/// Arquivos ASF podem conter fluxos com dados binários. O atributo MF_MT_ARBITRARY_HEADER no tipo de mídia contém uma estrutura 
				/// MT_ARBITRARY_HEADER que descreve o fluxo.
				/// </summary>
				literal String^ MF_MT_ARBITRARY_HEADER = "{9E6BD6F5-0109-4F95-84AC-9309153A19FC}";
				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica se um fluxo de imagem ASF é um tipo JPEG degradável.
				/// Esse atributo se aplica ao tipo de mídia para fluxos de imagem em ASF. Se o valor for true, o Stream é um tipo de imagem JPEG 
				/// degradável. Caso contrário, o fluxo é um tipo de imagem JFIF.
				/// </summary>
				literal String^ MF_MT_IMAGE_LOSS_TOLERANT = "{ED062CF4-E34E-4922-BE99-934032133D7C}";




				//-> Atributos para os formatos de midia para arquivos (MPEG-4)




				/// <summary>
				/// Tipo do valor: UInt32.
				/// Especifica a entrada atual na caixa de descrição de exemplo para um tipo de mídia MPEG-4.
				/// Em um arquivo MP4 ou 3GP, a caixa de descrição de exemplo descreve a codificação usada para um fluxo no arquivo. A caixa de 
				/// descrição de exemplo pode conter várias entradas. Esse atributo especifica qual entrada usar. O valor é um índice 
				/// baseado em zero na lista.
				/// </summary>
				literal String^ MF_MT_MPEG4_CURRENT_SAMPLE_ENTRY = "{9AA7E155-B64A-4C1D-A500-455D600B6560}";
				/// <summary>
				/// Tipo do valor: Byte Array.
				/// Contém a caixa de descrição de exemplo para um arquivo MP4 ou 3GP.
				/// A caixa de descrição de exemplo descreve a codificação usada para um fluxo no arquivo.
				/// </summary>
				literal String^ MF_MT_MPEG4_SAMPLE_DESCRIPTION = "{261E9D83-9529-4B8F-A111-8B9C950A81A9}";
			};

			/// <summary>
			/// Contém todos os GUIDs para os formatos de (Vídeo) identificaveis pelo Media Foundation.
			/// </summary>
			public value struct GUIDs_MF_VIDEO_SUBTYPES
			{
				/// <summary>
				/// Base.
				/// </summary>
				literal String^ MFVideoFormat_Base = "{00000000-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 8 bits por pixel (BPP). (Layout da mesma memória como D3DFMT_P8.)
				/// </summary>
				literal String^ MFVideoFormat_RGB8 = "{00000029-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 24 bpp.
				/// </summary>
				literal String^ MFVideoFormat_RGB24 = "{00000014-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB 555, 16 BPP. (Layout da mesma memória como D3DFMT_X1R5G5B5.)
				/// </summary>
				literal String^ MFVideoFormat_RGB555 = "{00000018-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB 565, 16 BPP. (Layout da mesma memória como D3DFMT_R5G6B5.)
				/// </summary>
				literal String^ MFVideoFormat_RGB565 = "{00000017-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 32 bpp.
				/// </summary>
				literal String^ MFVideoFormat_RGB32 = "{00000016-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 32 bpp com canal alfa.
				/// </summary>
				literal String^ MFVideoFormat_ARGB32 = "{00000015-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 10 bpp para cada cor e 2 bpp para Alpha. (Layout da mesma memória como D3DFMT_A2B10G10R10)
				/// </summary>
				literal String^ MFVideoFormat_A2R10G10B10 = "{0000001F-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (RBG - Descompactado). 
				/// Descrição: RGB, 16 bpp com canal alfa. (Layout da mesma memória como D3DFMT_A16B16G16R16F)
				/// </summary>
				literal String^ MFVideoFormat_A16B16G16R16F = "{00000071-0000-0010-8000-00AA00389B71}";




				//Tipos YUV de 8 Bits e (Palettized - apenas o primeiro)




				/// <summary>
				/// Tipo: YUV - Palettized. 
				/// Descrição: Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_AI44 = "{34344941-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_AYUV = "{56555941-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_I420 = "{30323449-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_IYUV = "{56555949-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:1:1 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_NV11 = "{3131564E-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_NV12 = "{3231564E-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_UYVY = "{59565955-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:1:1 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_Y41P = "{50313459-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:1:1 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y41T = "{54313459-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y42T = "{54323459-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_YUY2 = "{32595559-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 8:4:4 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_YVU9 = "{39555659-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_YV12 = "{32315659-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo:  YUV - 8 Bits. 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_YVYU = "{55595659-0000-0010-8000-00AA00389B71}";



				//Tipos YUV de: 10 Bits e 16 Bits.



				/// <summary>
				/// Tipo: (YUV - 10 Bits). 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_P010 = "{30313050-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: YUV - 16 Bits). 
				/// Descrição: Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_P016 = "{36313276-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 10 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_P210 = "{30313250-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 16 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Planar
				/// </summary>
				literal String^ MFVideoFormat_P216 = "{36313250-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: YUV - 10 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_v210 = "{30313276-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 16 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_v216 = "{36313276-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 10 Bits). 
				/// Descrição: Formato: v40 | Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_v410 = "{30313476-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 10 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y210 = "{30313259-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 16 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y216 = "{36313259-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 10 Bits). 
				/// Descrição: Formato: Y40 | Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y410 = "{30313459-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (YUV - 16 Bits). 
				/// Descrição: Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				literal String^ MFVideoFormat_Y416 = "{36313459-0000-0010-8000-00AA00389B71}";



				//Formatos de Luminância e Profundidade



				/// <summary>
				/// Apenas luminância de 8 bits. (BPP). (Layout da mesma memória como D3DFMT_L8).
				/// </summary>
				literal String^ MFVideoFormat_L8 = "{00000032-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Apenas luminância de 16 bits. (Layout da mesma memória como D3DFMT_L16).
				/// </summary>
				literal String^ MFVideoFormat_L16 = "{00000051-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Profundidade de buffer de 16 bits z. (Layout da mesma memória como D3DFMT_D16).
				/// </summary>
				literal String^ MFVideoFormat_D16 = "{00000050-0000-0010-8000-00AA00389B71}";



				//Tipos de formato Codificados.



				/// <summary>
				/// Tipo: (Codificado - DVCPRO 25 (525-60 ou 625-50))
				/// </summary>
				literal String^ MFVideoFormat_DV25 = "{35327664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - DVCPRO 50 (525-60 ou 625-50))
				/// </summary>
				literal String^ MFVideoFormat_DV50 = "{30357664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - DVC/vídeo DV)
				/// </summary>
				literal String^ MFVideoFormat_DVC = "{20637664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - DVCPRO 100 (1080/60i, 1080/50i ou 720/60P))
				/// </summary>
				literal String^ MFVideoFormat_DVH1 = "{31687664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - HD-DVCR (1125-60 ou 1250-50))
				/// </summary>
				literal String^ MFVideoFormat_DVHD = "{64687664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - SDL-DVCR (525-60 ou 625-50))
				/// </summary>
				literal String^ MFVideoFormat_DVSD = "{64737664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - SD-DVCR (525-60 ou 625-50))
				/// </summary>
				literal String^ MFVideoFormat_DVSL = "{6C737664-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - H.263 vídeo)
				/// </summary>
				literal String^ MFVideoFormat_H263 = "{33363248-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo H.264). 
				/// Descrição: As amostras de mídia contêm dados de Bitstream H.264 com códigos de início e 
				/// têm o SPS / PPS intercalados.Cada amostra contém uma imagem completa, ou um campo ou um quadro.
				/// </summary>
				literal String^ MFVideoFormat_H264 = "{34363248-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - H.264 fluxo elementar). 
				/// Descrição: Esse tipo de mídia é o mesmo que MFVideoFormat_H264, exceto exemplos de
				/// mídia contêm um fluxo de bits H.264 fragmentado. Cada amostra pode conter uma imagem parcial; 
				/// várias imagens completas; ou uma ou mais imagens completas mais uma imagem parcial.
				/// </summary>
				literal String^ MFVideoFormat_H264_ES = "{3F40F4F0-5622-4FF8-B6D8-A17A584BEE5E}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo H. 265)
				/// </summary>
				literal String^ MFVideoFormat_H265 = "{35363248-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: O perfil principal do HEVC e o perfil de imagem imóvel principal.Cada amostra contém uma imagem completa.
				///	Com suporte no Windows 8.1 e posterior.O perfil principal do HEVC e o principal Perfil de imagem ainda de fluxo elementar.
				/// </summary>
				literal String^ MFVideoFormat_HEVC = "{43564548-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Esse tipo de mídia é o mesmo que MFVideoFormat_HEVC, exceto amostras de mídia contêm um fluxo de bits 
				/// HEVC fragmentado. Cada amostra pode conter uma imagem parcial; várias imagens completas; ou uma ou mais 
				/// imagens completas mais uma imagem parcial. Com suporte no Windows 8.1 e posterior.
				/// </summary>
				literal String^ MFVideoFormat_HEVC_ES = "{53564548-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo MPEG-4 parte 2). 
				/// </summary>
				literal String^ MFVideoFormat_M4S2 = "{3253344D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Motion JPEG). 
				/// </summary>
				literal String^ MFVideoFormat_MJPG = "{47504A4D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Microsoft MPEG 4 codec versão 3. Esse codec não é mais suportado.
				/// </summary>
				literal String^ MFVideoFormat_MP43 = "{3334504D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - ISO MPEG 4 codec versão 1). 
				/// </summary>
				literal String^ MFVideoFormat_MP4S = "{5334504D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo MPEG-4 parte 2). 
				/// </summary>
				literal String^ MFVideoFormat_MP4V = "{5634504D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo MPEG-2). 
				/// </summary>
				literal String^ MFVideoFormat_MPEG2 = "{E06D8026-DB46-11CF-B4D1-00805F6CBBEA}";
				/// <summary>
				/// Tipo: (Codificado - VP8 vídeo). 
				/// </summary>
				literal String^ MFVideoFormat_VP80 = "{30385056-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - VP9 vídeo). 
				/// </summary>
				literal String^ MFVideoFormat_VP90 = "{30395056-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - Vídeo MPEG-1). 
				/// </summary>
				literal String^ MFVideoFormat_MPG1 = "{3147504D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Windows Media Screen codec versão 1.
				/// </summary>
				literal String^ MFVideoFormat_MSS1 = "{3153534D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Windows Media Video 9 Screen codec.
				/// </summary>
				literal String^ MFVideoFormat_MSS2 = "{3253534D-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Windows Media Video Codec versão 7.
				/// </summary>
				literal String^ MFVideoFormat_WMV1 = "{31564D57-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Codec Windows Media Video 8.
				/// </summary>
				literal String^ MFVideoFormat_WMV2 = "{32564D57-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: Codec Windows Media Video 9.
				/// </summary>
				literal String^ MFVideoFormat_WMV3 = "{33564D57-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado - SMPTE 421M ("VC-1")). 
				/// </summary>
				literal String^ MFVideoFormat_WVC1 = "{31435657-0000-0010-8000-00AA00389B71}";
				/// <summary>
				/// Tipo: (Codificado). 
				/// Descrição: 8-bit por canal planar YUV 4:2:0 vídeo
				/// </summary>
				literal String^ MFVideoFormat_420O = "{4F303234-0000-0010-8000-00AA00389B71}";
			};

			/// <summary>
			/// Contém todos os GUIDs para os formatos de (Áudio) identificaveis pelo Media Foundation.
			/// </summary>
			public value struct GUIDs_MF_AUDIO_SUBTYPES
			{
				/// <summary>
				/// Áudio base.
				/// </summary>
				literal String^ MFAudioFormat_Base = "{00000000-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Codificação avançada de áudio (AAC).
				/// Esse subtipo é usado para AAC contido em um arquivo AVI com uma marca de formato de áudio igual a 0x00FF.
				/// Código FOURCC: WAVE_FORMAT_RAW_AAC1 (0x00FF)
				///</summary>
				literal String^ MFAudioFormat_RAW_ACC1 = "{000000FF-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Codificação avançada de áudio (AAC).
				/// Nota: Equivalente a MEDIASUBTYPE_MPEG_HEAAC
				/// Código FOURCC: WAVE_FORMAT_MPEG_HEAAC (0x1610)
				/// </summary>
				literal String^ MFAudioFormat_AAC = "{00001610-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Apple Lossless Codec de áudio
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_ALAC (0x6C61)
				/// </summary>
				literal String^ MFAudioFormat_ALAC = "{00006C61-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Adaptativo multi-taxa de áudio
				/// (Com suporte no Windows 8.1 e posterior)
				/// Código FOURCC: WAVE_FORMAT_AMR_NB
				/// </summary>
				literal String^ MFAudioFormat_AMR_NB = "{00007361-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Adaptativo multi-taxa de banda larga de áudio
				/// (Com suporte no Windows 8.1 e posterior)
				/// Código FOURCC: WAVE_FORMAT_AMR_WB
				/// </summary>
				literal String^ MFAudioFormat_AMR_WB = "{00007362-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// (Com suporte no Windows 8.1 e posterior).
				/// Código FOURCC: WAVE_FORMAT_AMR_WP
				/// </summary>
				literal String^ MFAudioFormat_AMR_WP = "{00007363-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Dolby Digital (AC-3).
				/// Mesmo valor GUID como MEDIASUBTYPE_DOLBY_AC3.
				/// Código FOURCC: Nenhum.
				/// </summary>
				literal String^ MFAudioFormat_Dolby_AC3 = "{E06D802C-DB46-11CF-B4D1-00805F6CBBEA}";

				/// <summary>
				/// Áudio Dolby AC-3 através da interface digital Sony/Philips (S/PDIF).
				/// Código FOURCC: WAVE_FORMAT_DOLBY_AC3_SPDIF (0x0092)
				/// </summary>
				literal String^ MFAudioFormat_Dolby_AC3_SPDIF = "{00000092-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Dolby Digital Plus.
				/// Código FOURCC: Nenhum
				/// </summary>
				literal String^ MFAudioFormat_Dolby_DDPlus = "{A7FB87AF-2D02-42FB-A4D4-05CD93843BDD}";

				/// <summary>
				/// Dados de áudio criptografados usados com o caminho de áudio seguro.
				/// Código FOURCC: WAVE_FORMAT_DRM (0x0009)
				/// </summary>
				literal String^ MFAudioFormat_DRM = "{00000009-0000-0010-8000-00AA00389B71}";

				/// <summary>
				///	Digital Theater Systems (DTS) de áudio.
				/// Código FOURCC: WAVE_FORMAT_DTS (0x0008)
				/// </summary>
				literal String^ MFAudioFormat_DTS = "{00000008-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Free Lossless Codec de áudio
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_FLAC (0xF1AC)
				/// </summary>
				literal String^ MFAudioFormat_FLAC = "{0000F1AC-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Áudio de ponto flutuante IEEE descompactado.
				/// Código FOURCC: WAVE_FORMAT_IEEE_FLOAT (0x0003)
				/// </summary>
				literal String^ MFAudioFormat_Float = "{00000003-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Áudio de ponto flutuante IEEE descompactado.
				///  Código FOURCC: Nenhum
				/// </summary>
				literal String^ MFAudioFormat_Float_SpatialObjects = "{FA39CD94-BC64-4AB1-9B71-DCD09D5A7E7A}";

				/// <summary>
				/// MPEG Audio Layer-3 (MP3).
				/// Código FOURCC: WAVE_FORMAT_MPEGLAYER3 (0x0055)
				/// </summary>
				literal String^ MFAudioFormat_MP3 = "{00000055-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Payload de áudio MPEG-1.
				/// Código FOURCC: WAVE_FORMAT_MPEG (0x0050)
				/// </summary>
				literal String^ MFAudioFormat_MPEG = "{00000050-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Codec de voz do Windows Media Audio 9.
				/// Código FOURCC: WAVE_FORMAT_WMAVOICE9 (0x000A)
				/// </summary>
				literal String^ MFAudioFormat_MSP1 = "{0000000A-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Opus
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_OPUS (0x704F)
				/// </summary>
				literal String^ MFAudioFormat_Opus = "{0000704F-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Áudio PCM descompactado.
				/// Código FOURCC: WAVE_FORMAT_PCM (1)
				/// </summary>
				literal String^ MFAudioFormat_PCM = "{00000001-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// {Não disponível}
				/// QCELP (Qualcomm Code Excited Linear Prediction) de áudio.
				/// Nota: Não disponivel nessa plataforma.
				/// Código FOURCC: Nenhum
				/// </summary>
				literal String^ MFAudioFormat_QCELP = "";

				/// <summary>
				/// Windows Media Audio 9 Professional codec sobre S/PDIF.
				/// Código FOURCC: WAVE_FORMAT_WMASPDIF (0x0164)
				/// </summary>
				literal String^ MFAudioFormat_WMASPDIF = "{00000164-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Windows Media Audio 9 Lossless Codec ou Windows Media Audio 9.1 Codec.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO_LOSSLESS (0x0163)
				/// </summary>
				literal String^ MFAudioFormat_WMAudio_Lossless = "{00000163-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Codec do Windows Media Audio 8, codec do Windows Media Audio 9 ou codec 
				/// de 9.1 do Windows Media Audio.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO2 (0x0161)
				/// </summary>
				literal String^ MFAudioFormat_WMAudioV8 = "{00000161-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Codec Windows Media Audio 9 Professional ou codec Windows Media Audio 9.1 Professional.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO3 (0x0162)
				/// </summary>
				literal String^ MFAudioFormat_WMAudioV9 = "{00000162-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Não é usado.
				/// Código FOURCC: WAVE_FORMAT_DTS (0x0008)
				/// </summary>
				literal String^ MFAudioFormat_ADTS = "{00001600-0000-0010-8000-00AA00389B71}";
			};			

			/// <summary>
			/// Contém todos os GUIDs que definem categorias para Transformações da Media Foundation (MFTs). Essas categorias são usadas para registrar e enumerar MFTs.
			/// </summary>
			public value struct GUIDs_MFT_CATEGORY
			{
				/// <summary>
				/// Decodificadores de áudio.
				/// </summary>
				literal String^ MFT_CATEGORY_AUDIO_DECODER = "{9ea73fb4-ef7a-4559-8d5d-719d8f0426c7}";

				/// <summary>
				/// Efeitos de áudio.
				/// </summary>
				literal String^ MFT_CATEGORY_AUDIO_EFFECT = "{11064c48-3648-4ed0-932e-05ce8ac811b7}";

				/// <summary>
				/// Codificadores de áudio.
				/// </summary>
				literal String^ MFT_CATEGORY_AUDIO_ENCODER = "{91c64bd0-f91e-4d8c-9276-db248279d975}";

				/// <summary>
				/// Demultiplexers.
				/// </summary>
				literal String^ MFT_CATEGORY_DEMULTIPLEXER = "{a8700a7a-939b-44c5-99d7-76226b23b3f1}";

				/// <summary>
				/// Multiplexadores.
				/// </summary>
				literal String^ MFT_CATEGORY_MULTIPLEXER = "{059c561e-05ae-4b61-b69d-55b61ee54a7b}";

				/// <summary>
				/// MFTs diversos.
				/// </summary>
				literal String^ MFT_CATEGORY_OTHER = "{90175d57-b7ea-4901-aeb3-933a8747756f}";

				/// <summary>
				/// Decodificadores de vídeo.
				/// </summary>
				literal String^ MFT_CATEGORY_VIDEO_DECODER = "{d6c02d4b-6833-45b4-971a-05a4b04bab91}";

				/// <summary>
				/// Efeitos de vídeo.
				/// </summary>
				literal String^ MFT_CATEGORY_VIDEO_EFFECT = "{12e17c21-532c-4a6e-8a1c-40825a736397}";

				/// <summary>
				/// Efeitos de renderização de vídeo.
				/// </summary>
				literal String^ MFT_CATEGORY_VIDEO_RENDERER_EFFECT = "{145CD8B4-92F4-4b23-8AE7-E0DF06C2DA95}";

				/// <summary>
				/// Codificadores de vídeo.
				/// </summary>
				literal String^ MFT_CATEGORY_VIDEO_ENCODER = "{f79eac7d-e545-4387-bdee-d647d7bde42a}";

				/// <summary>
				/// Processadores de vídeo. Esta categoria é limitada a MFTs que executam conversões de formato em vídeo não comprimido, incluindo conversões de espaço de cor. Para efeitos 
				/// de vídeo que modificam a aparência da imagem(como um efeito de desfoque ou uma transformação em escala de cor para cinza), use a categoria MFT_CATEGORY_VIDEO_EFFECT.
				/// </summary>
				literal String^ MFT_CATEGORY_VIDEO_PROCESSOR = "{302EA3FC-AA5F-47f9-9F7A-C2188BB163021}";
			};
			
			/// <summary>
			/// Contém todos os GUIDs para os formatos principais suportados por essa biblioteca.
			/// </summary>
			public value struct GUIDs_MFAttributes_MAJOR_TYPES
			{
				/// <summary>
				/// Fluxo de Áudio.
				/// </summary>
				literal String^ MFMediaType_Audio = "{73647561-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Fluxo de Vídeo.
				/// </summary>
				literal String^ MFMediaType_Video = "{73646976-0000-0010-8000-00AA00389B71}";

				/// <summary>
				/// Fluxo de Image.
				/// </summary>
				literal String^ MFMediaType_Image = "{72178C23-E45B-11D5-BC2A-00B0D0F3F4AB}";

				/// <summary>
				/// Fluxo multiplexado ou fluxo elementar.
				/// </summary>
				literal String^ MFMediaType_Stream = "{e436eb83-524f-11ce-9f53-0020af0ba770}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pelas interfaces de eventos da media foundation.
			/// </summary>
			public value struct GUIDs_MFAttributes_Events
			{
				/// <summary>
				/// Quando uma fonte de mídia solicita uma nova taxa de reprodução, especifica se a fonte também solicita o afinamento.
				/// </summary>
				literal String^ MF_EVENT_DO_THINNING = "{321EA6FB-DAD9-46e4-B31D-D2EAE7090E30}";

				/// <summary>
				/// Identifica o nó de topologia para um Stream Sink.
				/// </summary>
				literal String^ MF_EVENT_OUTPUT_NODE = "{830f1a8b-c060-46dd-a801-1c95dec9b107}";

				/// <summary>
				/// Deslocamento entre o tempo de apresentação e os carimbos de hora da fonte de mídia.
				/// </summary>
				literal String^ MF_EVENT_PRESENTATION_TIME_OFFSET = "{5AD914D1-9B45-4a8d-A2C0-81D1E50BFB07}";

				/// <summary>
				/// Tempo de apresentação de uma amostra que foi renderizada durante a limpeza.
				/// </summary>
				literal String^ MF_EVENT_SCRUBSAMPLE_TIME = "{9AC712B3-DCB8-44d5-8D0C-37455A2782E3}";

				/// <summary>
				/// Contém bandeiras que definem os recursos da Sessão de Mídia, com base na apresentação atual.
				/// </summary>
				literal String^ MF_EVENT_SESSIONCAPS = "{7E5EBCD0-11B8-4abe-AFAD-10F6599A7F42}";

				/// <summary>
				/// Contém bandeiras que indicam quais recursos foram alterados na Sessão de Mídia, com base na apresentação atual.
				/// </summary>
				literal String^ MF_EVENT_SESSIONCAPS_DELTA = "{7E5EBCD1-11B8-4abe-AFAD-10F6599A7F42}";

				/// <summary>
				/// Contém o tempo de início quando uma fonte de mídia é reiniciada a partir de sua posição atual.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_ACTUAL_START = "{a8cc55a9-6b31-419f-845d-ffb351a2434b}";

				/// <summary>
				/// Especifica as características atuais da fonte de mídia.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_CHARACTERISTICS = "{47DB8490-8B22-4f52-AFDA-9CE1B2D3CFA8}";

				/// <summary>
				/// Especifica as características anteriores da fonte de mídia.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_CHARACTERISTICS_OLD = "{47DB8491-8B22-4f52-AFDA-9CE1B2D3CFA8}";

				/// <summary>
				/// Especifica se a topologia do segmento atual está vazia.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_FAKE_START = "{a8cc55a7-6b31-419f-845d-ffb351a2434b}";

				/// <summary>
				/// Especifica o tempo de início para uma topologia de segmento.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_PROJECTSTART = "{a8cc55a8-6b31-419f-845d-ffb351a2434b}";

				/// <summary>
				/// Especifica se a fonte do sequenciador cancelou uma topologia.
				/// </summary>
				literal String^ MF_EVENT_SOURCE_TOPOLOGY_CANCELED = "{}";

				/// <summary>
				/// O horário de início da apresentação, em unidades de 100 nanossegundos, medido pelo relógio de apresentação.
				/// </summary>
				literal String^ MF_EVENT_START_PRESENTATION_TIME = "{DB62F650-9A5E-4704-ACF3-563BC6A73364}";

				/// <summary>
				/// O tempo de apresentação em que a mídia afunda renderá a primeira amostra da nova topologia.
				/// </summary>
				literal String^ MF_EVENT_START_PRESENTATION_TIME_AT_OUTPUT = "{5AD914D2-9B45-4a8d-A2C0-81D1E50BFB07}";

				/// <summary>
				/// Especifica o status de uma topologia durante a reprodução.
				/// </summary>
				literal String^ MF_EVENT_TOPOLOGY_STATUS = "{30C5018D-9A53-454b-AD9E-6D5F8FA7C43B}";

				/// <summary>
				/// O momento aproximado em que a Media Session levantou um evento.
				/// </summary>
				literal String^ MF_SESSION_APPROX_EVENT_OCCURRENCE_TIME = "{190e852f-6238-42d1-b5af-69ea338ef850}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pela interface IMFSourceReader.
			/// </summary>
			public value struct GUIDs_MFAttributes_SourceReader
			{
				/// <summary>
				/// Permite o processamento de baixa latência.
				/// </summary>
				literal String^ MF_LOW_LATENCY = "{9C27891A-ED7A-40e1-88E8-B22727A024EE}";

				/// <summary>
				/// Habilita ou desabilita as conversões de formato pelo leitor de origem.
				/// </summary>
				literal String^ MF_READWRITE_DISABLE_CONVERTERS = "{98D5B065-1374-4847-8D5D-31520FEE7156}";


				/// <summary>
				/// Permite que o leitor de origem para usar o hardware-based Media Foundation transforma (MFTs).
				/// </summary>
				literal String^ MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS = "{A634A91C-822B-41B9-A494-4DE4643612B0}";


				/// <summary>
				/// Contém um ponteiro para a interface de retorno de chamada do aplicativo para o leitor de origem.
				/// </summary>
				literal String^ MF_SOURCE_READER_ASYNC_CALLBACK = "{1E3DBEAC-BB43-4C35-B507-CD644464C965}";


				/// <summary>
				/// Contém um ponteiro para o Microsoft Direct3D Device Manager.
				/// </summary>
				literal String^ MF_SOURCE_READER_D3D_MANAGER = "{EC822DA2-E1E9-4B29-A0D8-563C719F5269}";


				/// <summary>
				/// Especifica se o leitor de origem habilita o DirectX Video Acceleration (DXVA) no decodificador de vídeo.
				/// </summary>
				literal String^ MF_SOURCE_READER_DISABLE_DXVA = "{AA456CFD-3943-4A1E-A77D-1838C0EA2E35}";


				/// <summary>
				/// Especifica se o leitor de origem desliga a fonte de mídia. Aplica-se somente quando 
				/// o aplicativo cria o leitor de origem de um objeto de fonte de mídia existente.
				/// </summary>
				literal String^ MF_SOURCE_READER_DISCONNECT_MEDIASOURCE_ON_SHUTDOWN = "{56B67165-219E-456D-A22E-2D3004C7FE56}";


				/// <summary>
				/// Permite o processamento avançado de vídeo pelo leitor de origem, incluindo conversão de espaço de cor,
				/// desentrelaçamento, redimensionamento de vídeo e conversão de taxa de quadros.
				/// </summary>
				literal String^ MF_SOURCE_READER_ENABLE_ADVANCED_VIDEO_PROCESSING = "{0F81DA2C-B537-4672-A8B2-A681B17307A3}";


				/// <summary>
				/// Permite o processamento de vídeo limitado pelo leitor de origem.
				/// </summary>
				literal String^ MF_SOURCE_READER_ENABLE_VIDEO_PROCESSING = "{FB394F3D-CCF1-42EE-BBB3-F9B845D5681D}";


				/// <summary>
				/// Contém propriedades de configuração para a fonte de mídia.
				/// </summary>
				literal String^ MF_SOURCE_READER_MEDIASOURCE_CONFIG = "{9085ABEB-0354-48F9-ABB5-200DF838C68E}";
			};

			/// <summary>
			///  Contém todos os GUIDs utilizados pelas api de manipulação de fluxos de bytes da media foundation.
			/// </summary>
			public value struct GUIDs_MFAttributes_ByteStream
			{
				/// <summary>
				/// Especifica o tipo MIME de um fluxo de byte.
				/// </summary>
				literal String^ MF_BYTESTREAM_CONTENT_TYPE = "{fc358289-3cb6-460c-a424-b6681260375a}";

				/// <summary>
				/// Especifica a duração de um fluxo byte, em unidades de 100 nanossegundos.
				/// </summary>
				literal String^ MF_BYTESTREAM_DURATION = "{fc35828a-3cb6-460c-a424-b6681260375a}";

				/// <summary>
				/// Especifica a URL de um arquivo IFO associado.
				/// </summary>
				literal String^ MF_BYTESTREAM_IFO_FILE_URI = "{fc35828c-3cb6-460c-a424-b6681260375a}";

				/// <summary>
				/// Especifica quando um fluxo de byte foi modificado pela última vez.
				/// </summary>
				literal String^ MF_BYTESTREAM_LAST_MODIFIED_TIME = "{fc35828b-3cb6-460c-a424-b6681260375a}";

				/// <summary>
				/// Especifica a URL original para um fluxo byte.
				/// </summary>
				literal String^ MF_BYTESTREAM_ORIGIN_NAME = "{fc358288-3cb6-460c-a424-b6681260375a}";

				/// <summary>
				/// Especifica se um manipulador byte-stream pode usar um fluxo de byte que é aberto para escrever por outro segmento
				/// </summary>
				literal String^ MF_BYTESTREAMHANDLER_ACCEPTS_SHARE_WRITE = "{a6e1f733-3001-4915-8150-1558a2180ec8}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pela interface IMFSample.
			/// </summary>
			public value struct GUIDs_MFAttributes_Sample
			{
				/// <summary>
				/// Especifica se um exemplo de mídia contém um quadro de vídeo 3D.
				/// </summary>
				literal String^ MFSampleExtension_3DVideo = "{F86F97A4-DD54-4E2E-9A5E-55FC2D74A005}";


				/// <summary>
				/// Especifica como um quadro de vídeo 3D é armazenado em um exemplo de mídia.
				/// </summary>
				literal String^ MFSampleExtension_3DVideo_SampleFormat = "{08671772-E36F-4CFF-97B3-D72E20987A48}";


				/// <summary>
				/// Especifica a dominância de campo para um quadro de vídeo entrelaçado.
				/// </summary>
				literal String^ MFSampleExtension_BottomFieldFirst = "{941CE0A3-6AE3-4DDA-9A08-A64298340617}";


				/// <summary>
				/// A câmera extrínsecos para a amostra.
				/// </summary>
				literal String^ MFSampleExtension_CameraExtrinsics = "{6B761658-B7EC-4C3B-8225-8623CABEC31D}";


				/// <summary>
				/// O arquivo Imfattributes para todos os metadados relacionados ao pipeline de captura.
				/// </summary>
				literal String^ MFSampleExtension_CaptureMetadata = "{2EBE23A8-FAF5-444A-A6A2-EB810880AB5D}";


				/// <summary>
				/// Indica se uma amostra de vídeo é um quadro-chave.
				/// </summary>
				literal String^ MFSampleExtension_CleanPoint = "{9CDF01D8-A0F0-43BA-B077-EAA06CBD728A}";


				/// <summary>
				/// Define o ID de chave para o exemplo.
				/// </summary>
				literal String^ MFSampleExtension_Content_KeyID = "{C6C7F5B0-ACCA-415B-87D9-10441469EFC6}";


				/// <summary>
				/// Especifica se um quadro de vídeo desentrelaçado foi derivado do campo superior ou do campo inferior.
				/// </summary>
				literal String^ MFSampleExtension_DerivedFromTopField = "{6852465A-AE1C-4553-8E9B-C3420FCB1637}";


				/// <summary>
				/// O carimbo de data/hora do driver de dispositivo.
				/// </summary>
				literal String^ MFSampleExtension_DeviceTimestamp = "{8F3E35E7-2DCD-4887-8622-2A58BAA652B0}";


				/// <summary>
				/// Especifica se um exemplo de mídia é o primeiro exemplo após uma lacuna no fluxo.
				/// </summary>
				literal String^ MFSampleExtension_Discontinuity = "{9CDF01D9-A0F0-43BA-B077-EAA06CBD728A}";


				/// <summary>
				/// Especifica o tamanho de bloco de byte criptografado para criptografia de padrão baseado em exemplo.
				/// </summary>
				literal String^ MFSampleExtension_Encryption_CryptByteBlock = "{9D84289B-0C7F-4713-AB95-108AB42AD801}";


				/// <summary>
				/// Especifica o esquema de proteção para amostras criptografadas.
				/// </summary>
				literal String^ MFSampleExtension_Encryption_ProtectionScheme = "{D054D096-28BB-45DA-87EC-74F351871406}";


				/// <summary>
				/// Especifica a identificação de um exemplo criptografado.
				/// </summary>
				literal String^ MFSampleExtension_Encryption_SampleID = "{6698B84E-0AFA-4330-AEB2-1C0A98D7A44D}";


				/// <summary>
				/// Especifica o tamanho de bloco de byte Clear (não criptografado) para criptografia de 
				/// padrão baseado em exemplo.
				/// </summary>
				literal String^ MFSampleExtension_Encryption_SkipByteBlock = "{0D550548-8317-4AB1-845F-D06306E293E3}";


				/// <summary>
				/// Define o mapeamento de subamostra para o exemplo que indica os bytes claros e criptografados 
				/// nos dados de exemplo.
				/// </summary>
				literal String^ MFSampleExtension_Encryption_SubSampleMappingSplit = "{FE0254B9-2AA5-4EDC-99F7-17E89DBF9174}";


				/// <summary>
				/// Especifica se um quadro de vídeo está corrompido.
				/// </summary>
				literal String^ MFSampleExtension_FrameCorruption = "{B4DD4A8C-0BEB-44C4-8B75-B02B913B04F0}";


				/// <summary>
				/// Obtém um objeto do tipo Imfcollection contendo imfsample objetos que contêm unidades de camada de abstração 
				/// de rede (NALUS) e suplementar informações de aprimoramento (SEI) unidades encaminhadas por um decodificador.
				/// </summary>
				literal String^ MFSampleExtension_ForwardedDecodeUnits = "{424C754C-97C8-48D6-8777-FC41F7B60879}";


				/// <summary>
				/// Especifica o tipo, NALU ou SEI, de uma unidade anexada a um Imfsample em um 
				/// MFSampleExtension_ForwardedDecodeUnits coleção.
				/// </summary>
				literal String^ MFSampleExtension_ForwardedDecodeUnitType = "{089E57C7-47D3-4A26-BF9C-4B64FAFB5D1E}";


				/// <summary>
				/// Indica se um quadro de vídeo está entrelaçado ou progressivo.
				/// </summary>
				literal String^ MFSampleExtension_Interlaced = "{B1D5830A-DEB8-40E3-90FA-389943716461}";


				/// <summary>
				/// Especifica informações de quadro de referência de longo prazo (LTR) e é retornada no exemplo de saída.
				/// </summary>
				literal String^ MFSampleExtension_LongTermReferenceFrameInfo = "{9154733F-E1BD-41BF-81D3-FCD918F71332}";


				/// <summary>
				/// Esse atributo retorna a diferença absoluta média (MAD) em todos os blocos de macro no plano Y.
				/// </summary>
				literal String^ MFSampleExtension_MeanAbsoluteDifference = "{1CDBDE11-08B4-4311-A6DD-0F9F371907AA}";


				/// <summary>
				/// Especifica os limites de carga para um quadro. Isso se aplica a amostras criptografadas.
				/// </summary>
				literal String^ MFSampleExtension_PacketCrossOffsets = "{2789671D-389F-40BB-90D9-C282F77F9ABD}";


				/// <summary>
				/// Contém a miniatura da foto de um Imfsample.
				/// </summary>
				literal String^ MFSampleExtension_PhotoThumbnail = "{74BBC85C-C8BB-42DC-B586-DA17FFD35DCC}";


				/// <summary>
				/// Contém o Imfmediatype que descreve o tipo de formato de imagem contido no atributo MFSampleExtension_PhotoThumbnail.
				/// </summary>
				literal String^ MFSampleExtension_PhotoThumbnailMediaType = "{61AD5420-EBF8-4143-89AF-6BF25F672DEF}";


				/// <summary>
				/// A câmera pinhole intrínsecos para a amostra.
				/// </summary>
				literal String^ MFSampleExtension_PinholeCameraIntrinsics = "{4EE3B6C5-6A15-4E72-9761-70C1DB8B9FE3}";


				/// <summary>
				/// Especifica se deve repetir o primeiro campo em um quadro entrelaçado.
				/// </summary>
				literal String^ MFSampleExtension_RepeatFirstField = "{304D257C-7493-4FBD-B149-9228DE8D9A99}";


				/// <summary>
				/// Especifica os limites da região de interesse que indica a região do quadro que requer qualidade diferente.
				/// </summary>
				literal String^ MFSampleExtension_ROIRectangle = "{3414A438-4998-4D2C-BE82-BE3CA0B24D43}";


				/// <summary>
				/// Especifica se uma amostra de vídeo contém um único campo ou dois campos intercalados
				/// </summary>
				literal String^ MFSampleExtension_SingleField = "{9D85F816-658B-455A-BDE0-9FA7E15AB8F9}";


				/// <summary>
				/// O valor em nits que especifica a luminância de retroiluminação global direcionada para o 
				/// quadro de vídeo associado.
				/// </summary>
				literal String^ MFSampleExtension_TargetGlobalLuminance = "{3F60EF36-31EF-4DAF-8360-940397E41EF3}";


				/// <summary>
				/// Contém um ponteiro para o token que foi fornecido para o IMFMediaStream::RequestSample método.
				/// </summary>
				literal String^ MFSampleExtension_Token = "{8294DA66-F328-4805-B551-00DEB4C57A61}";


				/// <summary>
				/// Especifica os limites da região de interesse que indica a região do quadro que requer qualidade diferente.
				/// </summary>
				literal String^ MFSampleExtension_VideoEncodePictureType = "{973704E6-CD14-483C-8F20-C9FC0928BAD5}";


				/// <summary>
				/// Especifica o parâmetro de quantização (QP) que foi usado para codificar uma amostra de vídeo.
				/// </summary>
				literal String^ MFSampleExtension_VideoEncodeQP = "{B2EFE478-F979-4C66-B95E-EE2B82C82F36}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pela interface IMFPresentationDescriptor.
			/// </summary>
			public value struct GUIDs_MFAttributes_PresentationDescriptor
			{
				/// <summary>
				/// Contém um ponteiro para o descritor de apresentação do caminho de mídia protegido (PMP).
				/// </summary>
				literal String^ MF_PD_APP_CONTEXT = "{6C990D32-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Especifica a taxa de bits de codificação de áudio para a apresentação, em bits por segundo.
				/// </summary>
				literal String^ MF_PD_AUDIO_ENCODING_BITRATE = "{6C990D35-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Especifica se os fluxos de áudio na apresentação têm uma taxa de bits variável.
				/// </summary>
				literal String^ MF_PD_AUDIO_ISVARIABLEBITRATE = "{33026EE0-E387-4582-AE0A-34A2AD3BAA18}";

				/// <summary>
				/// Especifica a duração de uma apresentação, em unidades de 100 nanosegundos.
				/// </summary>
				literal String^ MF_PD_DURATION = "{6C990D33-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Especifica quando uma apresentação foi modificada pela última vez.
				/// </summary>
				literal String^ MF_PD_LAST_MODIFIED_TIME = "{6C990D38-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Especifica o tipo MIME do conteúdo.
				/// </summary>
				literal String^ MF_PD_MIME_TYPE = "{6C990D37-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// A hora em que a apresentação deve começar, em relação ao início da fonte de mídia.
				/// </summary>
				literal String^ MF_PD_PLAYBACK_BOUNDARY_TIME = "{6C990D3B-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// O identificador do elemento de lista de reprodução na apresentação.
				/// </summary>
				literal String^ MF_PD_PLAYBACK_ELEMENT_ID = "{6C990D39-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Contém um ponteiro para o objeto de proxy para o descritor de apresentação do aplicativo.
				/// </summary>
				literal String^ MF_PD_PMPHOST_CONTEXT = "{6C990D31-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Contém o idioma preferencial RFC 1766 da fonte de mídia.
				/// </summary>
				literal String^ MF_PD_PREFERRED_LANGUAGE = "{6C990D3A-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Contém o nome amigável do compatível sincronizado Media Interchange (SAMI) estilos. 
				/// Esse atributo se aplica somente a arquivos SAMI.
				/// </summary>
				literal String^ MF_PD_SAMI_STYLELIST = "{E0B73C7F-486D-484E-9872-4DE5192A7BF8}";

				/// <summary>
				/// Especifica o tamanho total do arquivo de origem, em bytes.
				/// </summary>
				literal String^ MF_PD_TOTAL_FILE_SIZE = "{6C990D34-BB8E-477A-8598-0D5D96FCD88A}";

				/// <summary>
				/// Especifica a taxa de bits de codificação de vídeo para a apresentação, em bits por segundo.
				/// </summary>
				literal String^ MF_PD_VIDEO_ENCODING_BITRATE = "{6C990D36-BB8E-477A-8598-0D5D96FCD88A}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pela interface IMFStreamDescriptor.
			/// </summary>
			public value struct GUIDs_MFAttributes_StreamDescriptor
			{
				/// <summary>
				/// Especifica o idioma para um fluxo.
				/// </summary>
				literal String^ MF_SD_LANGUAGE = "{00AF2180-BDC2-423C-ABCA-F503593BC121}";

				/// <summary>
				/// Especifica se um fluxo é mutuamente exclusivo com outros fluxos do mesmo tipo.
				/// </summary>
				literal String^ MF_SD_MUTUALLY_EXCLUSIVE = "{023EF79C-388D-487F-AC17-696CD6E3C6F5}";

				/// <summary>
				/// Especifica se um fluxo contém conteúdo protegido.
				/// </summary>
				literal String^ MF_SD_PROTECTED = "{00AF2181-BDC2-423C-ABCA-F503593BC121}";

				/// <summary>
				/// Contém o nome de um fluxo.
				/// </summary>
				literal String^ MF_SD_STREAM_NAME = "{4F1B099D-D314-41E5-A781-7FEFAA4C501F}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pelo SAR(Streaming Audio Render).
			/// </summary>
			public value struct GUIDs_MFAttributes_AudioRenderer
			{
				/// <summary>
				/// Especifica o identificador para o dispositivo de ponto de extremidade de áudio.
				/// </summary>
				literal String^ MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ID = "{B10AAEC3-EF71-4CC3-B873-05A9A08B9F8E}";


				/// <summary>
				/// Especifica a função de ponto de extremidade de áudio para o renderizador de áudio.
				/// </summary>
				literal String^ MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ROLE = "{6BA644FF-27C5-4D02-9887-C28619FDB91B}";


				/// <summary>
				/// Contém sinalizadores para configurar o renderizador de áudio.
				/// </summary>
				literal String^ MF_AUDIO_RENDERER_ATTRIBUTE_FLAGS = "{EDE4B5E0-F805-4D6C-99B3-DB01BF95DFAB}";


				/// <summary>
				/// Especifica a classe de diretiva de áudio para o renderizador de áudio.
				/// </summary>
				literal String^ MF_AUDIO_RENDERER_ATTRIBUTE_SESSION_ID = "{EDE4B5E3-F805-4D6C-99B3-DB01BF95DFAB}";


				/// <summary>
				/// Especifica a categoria de fluxo de áudio para o Streaming Audio Renderer (SAR).
				/// </summary>
				literal String^ MF_AUDIO_RENDERER_ATTRIBUTE_STREAM_CATEGORY = "{A9770471-92EC-4DF4-94FE-81C36F0C3A7A}";
			};

			/// <summary>
			/// Contém todos os GUIDs utilizados pelo EVR(Renderizador de Vídeo Aprimorado).
			/// </summary>
			public value struct GUIDs_MFAttributes_EVR
			{
				/// <summary>
				/// Permite que o EVR faça chamadas em lotes para o método IDirect3DDevice9::Present.
				/// </summary>
				literal String^ EVRConfig_AllowBatching = "{E447DF0A-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Permite que o EVR melhore o desempenho usando o desentrelaçamento de Bob.
				/// </summary>
				literal String^ EVRConfig_AllowDropToBob = "{E447DF02-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Permite que o EVR melhore o desempenho ignorando o segundo campo de cada quadro entrelaçado.
				/// </summary>
				literal String^ EVRConfig_AllowDropToHalfInterlace = "{E447DF06-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Permite que o EVR limite sua saída para corresponder à largura de banda da GPU.
				/// </summary>
				literal String^ EVRConfig_AllowDropToThrottle = "{E447DF04-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Permite que o EVR misturar o vídeo dentro de um retângulo que é menor do que o retângulo de saída e, em seguida, dimensionar o resultado.
				/// </summary>
				literal String^ EVRConfig_AllowScaling = "{E447DF08-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Força o EVR para chamadas em lotes para o método IDirect3D9Device::Preent.
				/// </summary>
				literal String^ EVRConfig_ForceBatching = "{E447DF09-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Força o EVR para usar Bob Deinterlacing.
				/// </summary>
				literal String^ EVRConfig_ForceBob = "{E447DF01-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Força o EVR para ignorar o segundo campo de cada quadro entrelaçado.
				/// </summary>
				literal String^ EVRConfig_ForceHalfInterlace = "{E447DF05-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Força o EVR para misturar o vídeo dentro de um retângulo que é menor do que o retângulo de saída e, em seguida, dimensionar o resultado.
				/// </summary>
				literal String^ EVRConfig_ForceScaling = "{E447DF07-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Força o EVR para limitar sua saída para corresponder à largura de banda da GPU.
				/// </summary>
				literal String^ EVRConfig_ForceThrottle = "{E447DF03-10CA-4D17-B17E-6A840F8A3A4C}";


				/// <summary>
				/// Especifica um objeto de ativação que cria um mixer de vídeo personalizado para o 
				/// renderizador de vídeo aprimorado (EVR).
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_MIXER_ACTIVATE = "{BA491361-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// CLSID de um misturador de vídeo personalizado para o EVR.
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_MIXER_CLSID = "{BA491360-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// Especifica como criar um mixer personalizado para o EVR.
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_MIXER_FLAGS = "{BA491362-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// Especifica um objeto de ativação que cria um apresentador de vídeo personalizado para o EVR.
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_ACTIVATE = "{BA491365-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// CLSID de um apresentador de vídeo personalizado para o EVR.
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_CLSID = "{BA491364-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// Especifica como criar um apresentador personalizado para o EVR.
				/// </summary>
				literal String^ MF_ACTIVATE_CUSTOM_VIDEO_PRESENTER_FLAGS = "{BA491366-BE50-451E-95AB-6D4ACCC7DAD8}";


				/// <summary>
				/// Identificador para a janela de recorte de vídeo.
				/// </summary>
				literal String^ MF_ACTIVATE_VIDEO_WINDOW = "{9A2DBBDD-F57E-4162-82B9-6831377682D3}";


				/// <summary>
				/// Indica o número de buffers descompactados que o coletor de mídia EVR requer para desentrelaçamento.
				/// </summary>
				literal String^ MF_SA_REQUIRED_SAMPLE_COUNT = "{18802C61-324B-4952-ABD0-176FF5C696FF}";


				/// <summary>
				/// Especifica o retângulo de zoom para o mixer EVR.
				/// </summary>
				literal String^ VIDEO_ZOOM_RECT = "{7AAA1638-1B7F-4C93-BD89-5B9C9FB6FCF0}";


				/// <summary>
				/// Falta documentar!
				/// </summary>
				literal String^ MR_VIDEO_ACCELERATION_SERVICE = "{EFEF5175-5C7D-4CE2-BBBD-34FF8BCA6554}";


				/// <summary>
				/// Falta documentar!
				/// </summary>
				literal String^ MR_VIDEO_RENDER_SERVICE = "{1092A86C-AB1A-459A-A336-831FBC4D11FF}";


				/// <summary>
				/// Falta documentar!
				/// </summary>
				literal String^ MR_VIDEO_MIXER_SERVICE = "{073CD2FC-6CF4-40B7-8859-E89552C841F8}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados na inicialização do IMFSinkWriter.
			/// </summary>
			public value struct GUIDs_MFAttributes_SinkWriter
			{
				/// <summary>
				/// Permite o processamento de baixa latência.
				/// </summary>
				literal String^ MF_LOW_LATENCY = "{9C27891A-ED7A-40E1-88E8-B22727A024EE}";

				/// <summary>
				/// Habilita ou desabilita as conversões de formato pelo gravador de coletor.
				/// </summary>
				literal String^ MF_READWRITE_DISABLE_CONVERTERS = "{98D5B065-1374-4847-8D5D-31520FEE7156}";

				/// <summary>
				/// Permite que o gravador de coletor usar transformações do Media Foundation baseadas em hardware (MFTs).
				/// </summary>
				literal String^ MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS = "{A634A91C-822B-41B9-A494-4DE4643612B0}";

				/// <summary>
				/// Contém um ponteiro para a interface de retorno de chamada do aplicativo para o gravador de coletor.
				/// </summary>
				literal String^ MF_SINK_WRITER_ASYNC_CALLBACK = "{48CB183E-7B0B-46F4-822E-5E1D2DDA4354}";

				/// <summary>
				/// Especifica se o gravador de coletor limita a taxa de dados de entrada.
				/// </summary>
				literal String^ MF_SINK_WRITER_DISABLE_THROTTLING = "{08B845D8-2B74-4AFE-9D53-BE16D2D5AE4F}";

				/// <summary>
				/// Especifica o tipo de contêiner do arquivo de saída.
				/// </summary>
				literal String^ MF_TRANSCODE_CONTAINERTYPE = "{150FF23F-4ABC-478B-AC4F-E1916FBA1CCA}";

				/// <summary>
				/// Contém um ponteiro IMFFieldOfUseMFTUnlock , que é usado para desbloquear um MFT com restrições de 
				/// campo de uso.
				/// </summary>
				literal String^ MFT_FIELDOFUSE_UNLOCK_Attribute = "{8EC2E9FD-9148-410D-831E-702439461A8E}";

				/// <summary>
				/// Use este atributo para fornecer um dispositivo Direct3D para qualquer codificadores de vídeo ou 
				/// coletores de mídia carregados pelo gravador de coletor.
				/// </summary>
				literal String^ MF_SINK_WRITER_D3D_MANAGER = "{EC822DA2-E1E9-4B29-A0D8-563C719F5269}";

			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela api de captura de dispositivos.
			/// </summary>
			public value struct GUIDs_MFAttributes_CaptureDevice
			{
				/// <summary>
				/// O nome de exibição do dispositivo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME = "{60d0e559-52f8-4fa2-bbce-acdb34a8ec01}";

				/// <summary>
				/// O formato de saída do dispositivo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_MEDIA_TYPE = "{56a819ca-0c78-4de4-a0a7-3ddaba0f24d4}";

				/// <summary>
				/// O tipo de dispositivo, como captura de áudio ou captura de vídeo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE = "{c60ac5fe-252a-478f-a0ef-bc8fa5f7cad3}";

				/// <summary>
				/// O ID de ponto final para um dispositivo de captura de áudio.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_ENDPOINT_ID = "{30da9258-feb9-47a7-a453-763a7a8e1c5f}";

				/// <summary>
				/// A função do dispositivo para um dispositivo de captura de áudio.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_ROLE = "{bc9d118e-8c67-4a18-85d4-12d300400552}";

				/// <summary>
				/// A categoria de dispositivo para um dispositivo de vídeo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_CATEGORY = "{77f0ae69-c3bd-4509-941d-467e4d24899e}";

				/// <summary>
				/// Especifica se uma fonte de captura de vídeo é um dispositivo de hardware ou um dispositivo de software.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_HW_SOURCE = "{de7046ba-54d6-4487-a2a4-ec7c0d1bd163}";

				/// <summary>
				/// Especifica o número máximo de frames que a fonte de captura de vídeo armazenará em buffer.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_MAX_BUFFERS = "{7dd9b730-4f2d-41d5-8f95-0cc9a912ba26}";

				/// <summary>
				/// O link simbólico para um driver de captura de vídeo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK = "{58f0aad8-22bf-4f8a-bb3d-d2c4978c6e2f}";

				/// <summary>
				/// ‎Especifica se a fonte do dispositivo usa o tempo do sistema para carimbos de hora.‎
				/// </summary>
				literal String^ MFT_HW_TIMESTAMP_WITH_QPC_Attribute = "{8d030fb8-cc43-4258-a22e-9210bef89be4}";

				/// <summary>
				/// Especifica que é um dispositivo de Áudio.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID = "{14dd9a1c-7cff-41be-b1b9-ba1ac6ecb571}";

				/// <summary>
				/// Especifica que é um dispositivo de Vídeo.
				/// </summary>
				literal String^ MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID = "{8ac3587a-4ae7-42d8-99e0-0a6013eef90f}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela engine de captura.
			/// </summary>
			public value struct GUIDs_MFAttributes_CaptureEngine
			{
				/// <summary>
				/// Sinais de que a captura de vídeo está sendo bloqueada pelo motorista.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_CAMERA_STREAM_BLOCKED = "{a4209417-8d39-46f3-b759-5912528f4207}";

				/// <summary>
				/// Sinais de que a captura de vídeo é restaurada após ser bloqueada.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_CAMERA_STREAM_UNBLOCKED = "{9be9eef0-cdaf-4717-8564-834aae66415c}";

				/// <summary>
				/// Define um ponteiro para o Gerenciador de Dispositivos DXGI no motor de captura.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_D3D_MANAGER = "{76e25e7b-d595-4283-962c-c594afd78ddf}";

				/// <summary>
				/// Permite que o mecanismo de captura use um decodificador que tenha restrições de campo de uso.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_DECODER_MFT_FIELDOFUSE_UNLOCK_ATTRIBUTE = "{2b8ad2e8-7acb-4321-a606-325c4249f4fc}";

				/// <summary>
				/// Especifica se o mecanismo de captura usa DXVA (DirectX Video Acceleration, aceleração de vídeo) para decodificação de vídeo.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_DISABLE_DXVA = "{f9818862-179d-433f-a32f-74cbcf74466d}";

				/// <summary>
				/// Desativa o uso de transformações baseadas em hardware media foundation (MFTs) no mecanismo de captura.
				/// </summary>
				literal String^ MF_CAPTURE_DISABLE_HARDWARE_TRANSFORMS = "{b7c42a6b-3207-4495-b4e7-81f9c35d5991}";

				/// <summary>
				/// Indica se as notificações do estado de fluxo devem ser ativadas.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_ENABLE_CAMERA_STREAMSTATE_NOTIFICATION = "{4c808e9d-aaed-4713-90fb-cb24064ab8da}";

				/// <summary>
				/// Permite que o mecanismo de captura use um codificador que tenha restrições de campo de uso.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_ENCODER_MFT_FIELDOFUSE_UNLOCK_ATTRIBUTE = "{54c63a00-78d5-422f-aa3e-5e99ac649269}";

				/// <summary>
				/// Identifica o componente que gerou um evento de captura.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_EVENT_GENERATOR_GUID = "{abfa8ad5-fc6d-4911-87e0-961945f8f7ce}";

				/// <summary>
				/// Identifica qual fluxo gerou um evento de captura.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_EVENT_STREAM_INDEX = "{82697f44-b1cf-42eb-9753-f86d649c8865}";

				/// <summary>
				/// Contém propriedades de configuração para a fonte de captura.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_MEDIASOURCE_CONFIG = "{bc6989d2-0fc1-46e1-a74f-efd36bc788de}";

				/// <summary>
				/// Define o número máximo de amostras processadas que podem ser tamponadas no caminho de áudio da pia de registro.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_RECORD_SINK_AUDIO_MAX_PROCESSED_SAMPLES = "{9896e12a-f707-4500-b6bd-db8eb810b50f}";

				/// <summary>
				/// Define o número máximo de amostras não processadas que podem ser tamponadas para processamento no caminho de áudio da pia de registro.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_RECORD_SINK_AUDIO_MAX_UNPROCESSED_SAMPLES = "{1cddb141-a7f4-4d58-9896-4d15a53c4efe}";

				/// <summary>
				/// Define o número máximo de amostras processadas que podem ser tamponadas no caminho de vídeo da pia de registro.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_RECORD_SINK_VIDEO_MAX_PROCESSED_SAMPLES = "{e7b4a49e-382c-4aef-a946-aed5490b7111}";

				/// <summary>
				/// Define o número máximo de amostras não processadas que podem ser tamponadas para processamento no caminho de vídeo do registro sink.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_RECORD_SINK_VIDEO_MAX_UNPROCESSED_SAMPLES = "{b467f705-7913-4894-9d42-a215fea23da9}";

				/// <summary>
				/// Especifica se o mecanismo de captura captura captura áudio, mas não vídeo.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_USE_AUDIO_DEVICE_ONLY = "{1c8077da-8466-4dc4-8b8e-276b3f85923b}";

				/// <summary>
				/// Especifica se o mecanismo de captura captura de vídeo, mas não áudio.
				/// </summary>
				literal String^ MF_CAPTURE_ENGINE_USE_VIDEO_DEVICE_ONLY = "{7e025171-cf32-4f2e-8f19-410577b73a66}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados no Media Foundation Transform(MFTs) ou nos ativadores de MFTs.
			/// </summary>
			public value struct GUIDs_MFAttributes_Transform
			{
				/// <summary>
				/// Especifica se o Carregador de Topologia mudará os tipos de mídia em um MFT.
				/// </summary>
				literal String^ MF_ACTIVATE_MFT_LOCKED = "{c1f6093c-7f65-4fbd-9e39-5faec3c4fbd7}";

				/// <summary>
				/// Especifica se uma transformação de mídia (MFT) suporta aceleração de vídeo DirectX.
				/// </summary>
				literal String^ MF_SA_D3D_AWARE = "{eaa35c29-775e-488e-9b61-b3283e49583b}";

				/// <summary>
				/// Especifica se um MFT realiza processamento assíncrono.
				/// </summary>
				literal String^ MF_TRANSFORM_ASYNC = "{f81a699a-649a-497d-8c73-29f8fed6ad7a}";
				
				/// <summary>
				/// Permite o uso de um MFT assíncroto.
				/// </summary>
				literal String^ MF_TRANSFORM_ASYNC_UNLOCK = "{e5666d6b-3422-4eb6-a421-da7db1f8e207}";
				
				/// <summary>
				/// Contém bandeiras para um objeto de ativação MFT.
				/// </summary>
				literal String^ MF_TRANSFORM_FLAGS_Attribute = "{9359bb7e-6275-46c4-a025-1c01e45f1a86}";
				
				/// <summary>
				/// Especifica a categoria para um MFT.
				/// </summary>
				literal String^ MF_TRANSFORM_CATEGORY_Attribute = "{ceabba49-506d-4757-a6ff-66c184987e4e}";
			
				/// <summary>
				/// Contém o identificador de classe (CLSID) de um MFT.
				/// </summary>
				literal String^ MFT_TRANSFORM_CLSID_Attribute = "{6821c42b-65a4-4e82-99bc-9a88205ecd0c}";
			
				/// <summary>
				/// Contém os tipos de entrada registrados para um MFT.
				/// </summary>
				literal String^ MFT_INPUT_TYPES_Attributes = "{4276c9b1-759d-4bf3-9cd0-0d723d138f96}";
				
				/// <summary>
				/// Contém os tipos de saída registrados para um MFT.
				/// </summary>
				literal String^ MFT_OUTPUT_TYPES_Attributes = "{8eae8cf3-a44f-4306-ba5c-bf5dda242818}";
			
				/// <summary>
				/// Contém o link simbólico para um MFT baseado em hardware.
				/// </summary>
				literal String^ MFT_ENUM_HARDWARE_URL_Attribute = "{2fb866ac-b078-4942-ab6c-003d05cda674}";
				
				/// <summary>
				/// Contém o nome de exibição de um MFT baseado em hardware.
				/// </summary>
				literal String^ MFT_FRIENDLY_NAME_Attribute = "{314ffbae-5b41-4c95-9c19-4e7d586face3}";
				
				/// <summary>
				/// Contém um ponteiro para os atributos de fluxo do fluxo conectado em um MFT baseado em hardware.
				/// </summary>
				literal String^ MFT_CONNECTED_STREAM_ATTRIBUTE = "{71eeb820-a59f-4de2-bcec-38db1dd611a4}";
				
				/// <summary>
				/// Especifica se um MFT baseado em hardware está conectado a outro MFT baseado em hardware.
				/// </summary>
				literal String^ MFT_CONNECTED_TO_HW_STREAM = "{34e6e728-06d6-4491-a553-4795650db912}";
				
				/// <summary>
				/// Especifica se um decodificador expõe os tipos de saída IYUV/I420 (adequado para transcodificação) antes de outros formatos.
				/// </summary>
				literal String^ MFT_DECODER_EXPOSE_OUTPUT_TYPES_IN_NATIVE_ORDER = "{ef80833f-f8fa-44d9-80d8-41ed6232670c}";

				/// <summary>
				/// Especifica a resolução final de saída da imagem decodificada, após o processamento do vídeo.
				/// </summary>
				literal String^ MFT_DECODER_FINAL_VIDEO_RESOLUTION_HINT = "{dc2f8496-15c4-407a-b6f0-1b66ab5fbf53}";

				/// <summary>
				/// Especifica que o codificador MFT suporta receber eventos MEEncodingParameter durante o streaming.
				/// </summary>
				literal String^ MFT_ENCODER_SUPPORTS_CONFIG_EVENT = "{86a355ae-3a77-4ec4-9f31-01149a4e92de}";

				/// <summary>
				/// Especifica um identificador exclusivo para um adaptador de vídeo. Use este atributo ao chamar MFTEnum2 para enumerar MFTs associados a um adaptador específico.
				/// </summary>
				literal String^ MFT_ENUM_ADAPTER_LUID = "{1d39518c-e220-4da8-a07f-ba172552d6b1}";

				/// <summary>
				/// Especifica a ID do fornecedor para uma transformação da Media Foundation baseada em hardware
				/// </summary>
				literal String^ MFT_ENUM_HARDWARE_VENDOR_ID_Attribute = "{3aecb0cc-035b-4bcc-8185-2b8d551ef3af}";

				/// <summary>
				/// Especifica o formato de saída preferido para um codificador.
				/// </summary>
				literal String^ MFT_PREFERRED_OUTPUTTYPE_Attribute = "{7e700499-396a-49ee-b1b4-f628021e8c9d}";
			
				/// <summary>
				/// Especifica se um MFT está registrado apenas no processo do aplicativo.
				/// </summary>
				literal String^ MFT_PROCESS_LOCAL_Attribute = "{543186e4-4649-4e65-b588-4aa352aff379}";

				/// <summary>
				/// Especifica se o vídeo H.264 remux MFT deve marcar imagens I como ponto limpo para uma melhor capacidade de busca. Isso tem o potencial de corrupção em buscas em arquivos MP4 finais não conformes.
				/// </summary>
				literal String^ MFT_REMUX_MARK_I_PICTURE_AS_CLEAN_POINT = "{364e8f85-3f2e-436c-b2a2-4440a012a9e8}";
			
				/// <summary>
				/// Contém propriedades de configuração para um codificador.
				/// </summary>
				literal String^ MFT_PREFERRED_ENCODER_PROFILE = "{53004909-1ef5-46d7-a18e-5a75f8b5905f}";

				/// <summary>
				/// Especifica se uma transformação de Media Foundation (MFT) suporta vídeo estereoscópico 3D.
				/// </summary>
				literal String^ MFT_SUPPORT_3DVIDEO = "{093f81b1-4f2e-4631-8168-7934032a01d3}";

				/// <summary>
				/// Especifica se uma transformação de Mídia Foundation (MFT) suporta mudanças dinâmicas de formato.
				/// </summary>
				literal String^ MFT_SUPPORT_DYNAMIC_FORMAT_CHANGE = "{53476a11-3f13-49fb-ac42-ee2733c96741}";
				
				/// <summary>
				/// Contém um ponteiro IMFFieldOfUseMFTUnlock, que pode ser usado para desbloquear o MFT.
				/// </summary>
				literal String^ MFT_FIELDOFUSE_UNLOCK_Attribute = "{8ec2e9fd-9148-410d-831e-702439461a8e}";
			
				/// <summary>
				/// Contém o valor de mérito de um codec de hardware.
				/// </summary>
				literal String^ MFT_CODEC_MERIT_Attribute = "{88a7cb15-7b07-4a34-9128-e64c6703c4d3}";
			
				/// <summary>
				/// Especifica se um decodificador é otimizado para transcodificação e não para reprodução.
				/// </summary>
				literal String^ MFT_ENUM_TRANSCODE_ONLY_ATTRIBUTE = "{111ea8cd-b62a-4bdb-89f6-67ffcdc2458b}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela api da Media Engine.
			/// </summary>
			public value struct GUIDs_MFAttributes_MediaEngine
			{
				/// <summary>
				/// ‎(UINT32) - ‎Especifica a categoria do fluxo de áudio.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_AUDIO_CATEGORY = "{c8d4c51d-350e-41f2-ba46-faebbb0857f6}";

				/// <summary>
				/// (UINT32) - ‎Especifica a função do dispositivo para o fluxo de áudio.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_AUDIO_ENDPOINT_ROLE = "{d2cb93d1-116a-44f2-9385-f7d0fda2fb46}";

				/// <summary>
				/// (GUID) - ‎Especifica o modo de compatibilidade do navegador.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_BROWSER_COMPATIBILITY_MODE = "{4e0212e2-e18f-41e1-95e5-c0e7e9235bc3}";

				/// <summary>
				/// NÃO POSSUI DOCUMENTAÇÃO.
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_COMPATIBILITY_MODE_WIN10 = "{5b25e089-6ca7-4139-a2cb-fcaab39552a3}";

				/// <summary>
				/// NÃO POSSUI DOCUMENTAÇÃO.
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_COMPATIBILITY_MODE_WWA_EDGE = "{15b29098-9f01-4e4d-b65a-c06c6c89da2a}";

				/// <summary>
				/// (IUNKNOWN - ICarenMFMediaEngineNotify) - ‎Contém um ponteiro para a interface de retorno de chamada para o Media Engine.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_CALLBACK = "{c60381b8-83a4-41f8-a3d0-de05076849a9}";

				/// <summary>
				/// (UINT32) - ‎Especifica se o Media Engine reproduzirá conteúdo protegido.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_CONTENT_PROTECTION_FLAGS = "{e0350223-5aaf-4d76-a7c3-06de70894db4}";

				/// <summary>
				/// (IUNKNOWN) - ‎Permite que o Media Engine reprodumente conteúdo protegido.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_CONTENT_PROTECTION_MANAGER = "{fdd6dfaa-bd85-4af3-9e0f-a01d539d876a}";

				/// <summary>
				/// (IUNKNOWN - ICoreWindow) - Uma interface Core Window.
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_COREWINDOW = "{fccae4dc-0b7f-41c2-9f96-4659948acddc}";

				/// <summary>
				/// (IUNKNOWN - ICarenMFDXGIDeviceManager) - ‎Define o Gerenciador de Dispositivos Microsoft DirectX Graphics Infrastructure (DXGI) no Media Engine.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_DXGI_MANAGER = "{065702da-1094-486d-8617-ee7cc4ee4648}";

				/// <summary>
				/// (IUNKNOWN - ICarenMFMediaEngineExtension) - ‎Contém um ponteiro para a interface ‎‎‎‎ICarenMFMediaEngineExtension.‎‎ ‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_EXTENSION = "{3109fd46-060d-4b62-8dcf-faff811318d2}";

				/// <summary>
				/// (UINT64) - ‎Especifica uma janela para que o Media Engine aplique proteções OPM ‎‎(Output Protection Manager, gerenciador‎‎ de proteção de saída).‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_OPM_HWND = "{a0be8ee7-0572-4f2c-a801-2a151bd3e726}";

				/// <summary>
				/// (UINT64) - ‎Defina uma Handle para uma janela de reprodução de vídeo para o Media Engine.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_PLAYBACK_HWND = "{d988879b-67c9-4d92-baa7-6eadd446039d}";

				/// <summary>
				/// (IUNKNOWN - IDCompositionVisual) - ‎Define um (Visual Microsoft DirectComposition) como a região de reprodução para o Media Engine.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_PLAYBACK_VISUAL = "{6debd26f-6ab9-4d7e-b0ee-c61a73ffad15}";

				/// <summary>
				/// (IUNKNOWN) - ‎Obtém as configurações do resolvedor de fonte.
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_SOURCE_RESOLVER_CONFIG_STORE = "{0ac0c497-b3c4-48c9-9cde-bb8ca2442ca3}";

				/// <summary>
				/// (BOOL) - ‎Especifica se o fluxo contém um canal alfa.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_STREAM_CONTAINS_ALPHA_CHANNEL = "{5cbfaf44-d2b2-4cfb-80a7-d429c74c789d}";

				/// <summary>
				/// (UINT32 - CA_DXGI_FORMAT)‎ - Define o formato de destino de renderização para o Media Engine.‎
				/// </summary>
				literal String^ MF_MEDIA_ENGINE_VIDEO_OUTPUT_FORMAT = "{5066893c-8cf9-42bc-8b8a-472212e52726}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela api da Media Session.
			/// </summary>
			public value struct GUIDs_MFAttributes_MediaSession
			{
				/// <summary>
				/// Fornece uma interface de retorno de chamada para que o aplicativo receba um objeto ativador de conteúdo da sessão PMP.
				/// </summary>
				literal String^ MF_SESSION_CONTENT_PROTECTION_MANAGER = "{1e83d482-1f1c-4571-8405-88f4b2181f74}";

				/// <summary>
				/// Especifica se as topologias terão um tempo global de início e parada.
				/// </summary>
				literal String^ MF_SESSION_GLOBAL_TIME = "{1e83d482-1f1c-4571-8405-88f4b2181f72}";

				/// <summary>
				/// Contém o CLSID de um gerenciador de qualidade para a Sessão de Mídia.
				/// </summary>
				literal String^ MF_SESSION_QUALITY_MANAGER = "{1e83d482-1f1c-4571-8405-88f4b2181f73}";

				/// <summary>
				/// Especifica que a fonte de mídia está sendo em execução em um processo remoto.
				/// </summary>
				literal String^ MF_SESSION_REMOTE_SOURCE_MODE = "{f4033ef4-9bb3-4378-941f-85a0856bc244}";

				/// <summary>
				/// Permite que duas instâncias da Sessão de Mídia compartilhem o mesmo processo pmp.
				/// </summary>
				literal String^ MF_SESSION_SERVER_CONTEXT = "{2f00c910-d2cf-4278-8b6a-d077fac3a25f}";

				/// <summary>
				/// Contém o CLSID de um carregador de topologia para a Sessão de Mídia.
				/// </summary>
				literal String^ MF_SESSION_TOPOLOADER = "{1e83d482-1f1c-4571-8405-88f4b2181f71}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pelos fluxos de mídia.
			/// </summary>
			public value struct GUIDs_MFAttributes_MediaStreamsExtension
			{
				/// <summary>
				/// A câmera extrínseca para o fluxo.
				/// </summary>
				literal String^ MFStreamExtension_CameraExtrinsics = "{686196d0-13e2-41d9-9638-ef032c272a52}";

				/// <summary>
				/// A câmera pinhole intrínseca ao fluxo.
				/// </summary>
				literal String^ MFStreamExtension_PinholeCameraIntrinsics = "{dbac0455-0ec8-4aef-9c32-7a3ee3456f53}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela api de Topologia.
			/// </summary>
			public value struct GUIDs_MFAttributes_Topology
			{
				/// <summary>
				/// Especifica se o carregador de topologia habilita o Microsoft DirectX Video Acceleration (DXVA) na topologia.
				/// </summary>
				literal String^ MF_TOPOLOGY_DXVA_MODE = "{1e8d34f6-f5ab-4e23-bb88-874aa3a1a74d}";

				/// <summary>
				/// NÃO POSSUI DOCUMENTAÇÃO.
				/// </summary>
				literal String^ MF_TOPOLOGY_ENABLE_XVP_FOR_PLAYBACK = "{1967731f-cd78-42fc-b026-0992a56e5693}";

				/// <summary>
				/// Especifica se a Sessão de Mídia tenta modificar a topologia quando o formato de um fluxo muda.
				/// </summary>
				literal String^ MF_TOPOLOGY_DYNAMIC_CHANGE_NOT_ALLOWED = "{d529950b-d484-4527-a9cd-b1909532b5b0}";

				/// <summary>
				/// Especifica se o carregador de topologia enumera os tipos de mídia fornecidos pela fonte de mídia.
				/// </summary>
				literal String^ MF_TOPOLOGY_ENUMERATE_SOURCE_TYPES = "{6248c36d-5d0b-4f40-a0bb-b0b305f77698}";

				/// <summary>
				/// Especifica se deve incluir transformações baseadas em hardware na topologia.
				/// </summary>
				literal String^ MF_TOPOLOGY_HARDWARE_MODE = "{d2d362fd-4e4f-4191-a579-c618b66706af}";

				/// <summary>
				/// Especifica se o pepiline apara amostras.
				/// </summary>
				literal String^ MF_TOPOLOGY_NO_MARKIN_MARKOUT = "{7ed3f804-86bb-4b3f-b7e4-7cb43afd4b80}";

				/// <summary>
				/// Especifica a taxa de atualização do monitor.
				/// </summary>
				literal String^ MF_TOPOLOGY_PLAYBACK_FRAMERATE = "{c164737a-c2b1-4553-83bb-5a526072448f}";

				/// <summary>
				/// Especifica o tamanho da janela de destino para reprodução de vídeo.
				/// </summary>
				literal String^ MF_TOPOLOGY_PLAYBACK_MAX_DIMS = "{5715cf19-5768-44aa-ad6e-8721f1b0f9bb}";

				/// <summary>
				/// Especifica o tempo de início da topologia dentro do segmento atual, em unidades de 100 nanossegundos.
				/// </summary>
				literal String^ MF_TOPOLOGY_PROJECTSTART = "{7ed3f802-86bb-4b3f-b7e4-7cb43afd4b80}";

				/// <summary>
				/// Especifica o tempo de parada da topologia dentro do segmento atual, em unidades de 100 nanossegundos.
				/// </summary>
				literal String^ MF_TOPOLOGY_PROJECTSTOP = "{7ed3f803-86bb-4b3f-b7e4-7cb43afd4b80}";

				/// <summary>
				/// Especifica o status de uma tentativa de resolver uma topologia.
				/// </summary>
				literal String^ MF_TOPOLOGY_RESOLUTION_STATUS = "{494bbcde-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// Especifica o horário de início das apresentações que estão na fila após a primeira apresentação.
				/// </summary>
				literal String^ MF_TOPOLOGY_START_TIME_ON_PRESENTATION_SWITCH = "{c8cc113f-7951-4548-aad6-9ed6202e62b3}";

				/// <summary>
				/// Permite otimizações estáticas no pipeline de vídeo.
				/// </summary>
				literal String^ MF_TOPOLOGY_STATIC_PLAYBACK_OPTIMIZATIONS = "{b86cac42-41a6-4b79-897a-1ab0e52b4a1b}";

				/// <summary>
				/// Contém um ponteiro IMFFieldOfUseMFTUnlock, que pode ser usado para desbloquear o MFT.
				/// </summary>
				literal String^ MFT_FIELDOFUSE_UNLOCK_Attribute = "{8ec2e9fd-9148-410d-831e-702439461a8e}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela interface de nós de topologia.
			/// </summary>
			public value struct GUIDs_MFAttributes_TopologyNode
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_CONNECT_METHOD = "{494bbcf7-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_DECODER = "{494bbd02-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_DECRYPTOR = "{494bbcfa-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_DISCARDABLE = "{494bbcfb-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_ERROR_MAJORTYPE = "{494bbcfd-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_ERROR_SUBTYPE = "{494bbcfe-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_ERRORCODE = "{494bbcee-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_LOCKED = "{494bbcf7-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_MARKIN_HERE = "{494bbd00-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_MARKOUT_HERE = "{494bbd01-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_MEDIASTART = "{835c58ea-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_MEDIASTOP = "{835c58eb-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_PRESENTATION_DESCRIPTOR = "{835c58ed-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_SEQUENCE_ELEMENTID = "{835c58ef-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_SOURCE = "{835c58ec-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_STREAM_DESCRIPTOR = "{835c58ee-e075-4bc7-bcba-4de000df9ae6}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_WORKQUEUE_ID = "{494bbcf8-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_WORKQUEUE_MMCSS_CLASS = "{494bbcf9-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_WORKQUEUE_MMCSS_TASKID = "{494bbcff-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_D3DAWARE = "{494bbced-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_DRAIN = "{494bbce9-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_FLUSH = "{494bbce8-b031-4e38-97c4-d5422dd618dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_TRANSFORM_OBJECTID = "{88dcc0c9-293e-4e8b-9aeb-0ad64cc016b0}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_DISABLE_PREROLL = "{14932f9e-9087-4bb4-8412-5167145cbe04}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_NOSHUTDOWN_ON_REMOVE = "{14932f9c-9087-4bb4-8412-5167145cbe04}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_RATELESS = "{14932f9d-9087-4bb4-8412-5167145cbe04}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_STREAMID = "{14932f9b-9087-4bb4-8412-5167145cbe04}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TOPONODE_PRIMARYOUTPUT = "{6304ef99-16b2-4ebe-9d67-e4c539b3a259}";
			};

			/// <summary>
			/// Contém todos os GUIDs que podem ser utilizados pela api de transcodificação.
			/// </summary>
			public value struct GUIDs_MFAttributes_Transcode
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_ADJUST_PROFILE = "{9c37c21b-060f-487c-a690-80d7f50d1c72}";

				/// <summary>
				/// Especifica o tipo de contêiner do arquivo de saída.
				/// </summary>
				literal String^ MF_TRANSCODE_CONTAINERTYPE = "{150FF23F-4ABC-478B-AC4F-E1916FBA1CCA}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_DONOT_INSERT_ENCODER = "{f45aa7ce-ab24-4012-a11b-dc8220201410}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_ENCODINGPROFILE = "{6947787c-f508-4ea9-b1e9-a1fe3a49fbc9}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_QUALITYVSSPEED = "{98332df8-03cd-476b-89fa-3f9e442dec9f}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_SKIP_METADATA_TRANSFER = "{4e4469ef-b571-4959-8f83-3dcfba33a393}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ MF_TRANSCODE_TOPOLOGYMODE = "{3e3df610-394a-40b2-9dea-3bab650bebf2}";
			};

			/// <summary>
			/// Estrutura que contém todos os GUIDs que especificam um tipo de contêiner e um arquivo codificado.
			/// </summary>
			public value struct GUIDs_MFTranscodeContainerType
			{
				/// <summary>
				/// Recipiente de arquivo ASF.
				/// </summary>
				literal String^ TranscodeContainerType_ASF = "{430f6f6e-b6bf-4fc1-a0bd-9ee46eee2afb}";

				/// <summary>
				/// Recipiente de arquivo MP4.
				/// </summary>
				literal String^ TranscodeContainerType_MPEG4 = "{dc6cd05d-b9d0-40ef-bd35-fa622c1ab28a}";

				/// <summary>
				/// Recipiente de arquivo MP3.
				/// </summary>
				literal String^ TranscodeContainerType_MP3 = "{e438b912-83f1-4de6-9e3a-9ffbc6dd24d1}";

				/// <summary>
				/// Recipiente de arquivo 3GP.
				/// </summary>
				literal String^ MFTranscodeContainerType_FLAC = "{31344aa3-05a9-42b5-901b-8e9d4257f705}";

				/// <summary>
				/// Recipiente de arquivo 3GP.
				/// </summary>
				literal String^ MFTranscodeContainerType_3GP = "{34c50167-4472-4f34-9ea0-c49fbacf037d}";

				/// <summary>
				/// Recipiente de arquivo AC3.
				/// </summary>
				literal String^ MFTranscodeContainerType_AC3 = "{6d8d91c3-8c91-4ed1-8742-8c347d5b44d0}";

				/// <summary>
				/// Recipiente de arquivo ADTS.
				/// </summary>
				literal String^ MFTranscodeContainerType_ADTS = "{132fd27d-0f02-43de-a301-38fbbbb3834e}";

				/// <summary>
				/// Recipiente de arquivo MPEG2.
				/// </summary>
				literal String^ MFTranscodeContainerType_MPEG2 = "{bfc2dbf9-7bb4-4f8f-afde-e112c44ba882}";

				/// <summary>
				/// Contêiner de arquivos FMPEG4.
				/// </summary>
				literal String^ MFTranscodeContainerType_FMPEG4 = "{9ba876f1-419f-4b77-a1e0-35959d9d4004}";

				/// <summary>
				/// Recipiente de arquivo WAVE. Suportado no Windows 8.1 e e posteriormente.
				/// </summary>
				literal String^ MFTranscodeContainerType_WAVE = "{64c3453c-0f26-4741-be63-87bdf8bb935b}";

				/// <summary>
				/// Recipiente de arquivo AVI. Suportado no Windows 8.1 e e posteriormente.
				/// </summary>
				literal String^ MFTranscodeContainerType_AVI = "{7edfe8af-402f-4d76-a33c-619fd157d0f1}";

				/// <summary>
				/// Recipiente de arquivo AMR.
				/// </summary>
				literal String^ MFTranscodeContainerType_AMR = "{025d5ad3-621a-475b-964d-66b1c824f079}";
			};

			/// <summary>
			/// Contém todos os GUIDs de serviço utilizado pela biblioteca da Media Foundation.
			/// </summary>
			public value struct GUIDs_MF_SERVICE_INTERFACES
			{
				/// <summary>
				/// Interfaces: IMFMetadataProvider
				/// </summary>
				literal String^ MF_METADATA_PROVIDER_SERVICE = "{DB214084-58A4-4D2E-B84F-6F755B2F7A0D}";
				/// <summary>
				/// Interfaces: IMFMediaSource
				/// </summary>
				literal String^ MF_MEDIASOURCE_SERVICE = "{F09992F7-9FBA-4C4A-A37F-8C47B4E1DFE7}";
				/// <summary>
				/// Interfaces: IMFPMPServer
				/// </summary>
				literal String^ MF_PMP_SERVER_CONTEXT = "{2F00C910-D2CF-4278-8B6A-D077FAC3A25F}";
				/// <summary>
				/// Interfaces: IMFQualityAdvise
				/// </summary>
				literal String^ MF_QUALITY_SERVICES = "{B7E2BE11-2F96-4640-B52C-282365BDF16C}";
				/// <summary>
				/// Interfaces: IMFRateControl | IMFRateSupport
				/// </summary>
				literal String^ MF_RATE_CONTROL_SERVICE = "{866FA297-B802-4BF8-9DC9-5E3B6A9F53C9}";
				/// <summary>
				/// Interfaces: IMFRemoteProxy
				/// </summary>
				literal String^ MF_REMOTE_PROXY = "{2F00C90E-D2CF-4278-8B6A-D077FAC3A25F}";
				/// <summary>
				/// Interfaces: IMFSAMIStyle
				/// </summary>
				literal String^ MF_SAMI_SERVICE = "{49A89AE7-B4D9-4EF2-AA5C-F65A3E05AE4E}";
				/// <summary>
				/// Interfaces: IMFMediaSourcePresentationProvider
				/// </summary>
				literal String^ MF_SOURCE_PRESENTATION_PROVIDER_SERVICE = "{E002AADC-F4AF-4EE5-9847-053EDF840426}";
				/// <summary>
				/// Interfaces: IMFTimecodeTranslate
				/// </summary>
				literal String^ MF_TIMECODE_SERVICE = "{A0D502A7-0EB3-4885-B1B9-9FEB0D083454}";
				/// <summary>
				/// Interfaces: IMFTopologyNodeAttributeEditor
				/// </summary>
				literal String^ MF_TOPONODE_ATTRIBUTE_EDITOR_SERVICE = "{65656E1A-077F-4472-83EF-316F11D5087A}";
				/// <summary>
				/// Interfaces: IMFByteStream
				/// </summary>
				literal String^ MF_WRAPPED_OBJECT = "{2B182C4C-D6AC-49F4-8915-F71887DB70CD}";
				/// <summary>
				/// Interfaces: Sem documentação!
				/// </summary>
				literal String^ MF_WRAPPED_BUFFER_SERVICE = "{AB544072-C269-4EBC-A552-1C3B32BED5CA}";
				/// <summary>
				/// Interfaces: Sem documentação!
				/// </summary>
				literal String^ MF_WRAPPED_SAMPLE_SERVICE = "{31F52BF2-D03E-4048-80D0-9C1046D87C61}";
				/// <summary>
				/// Interfaces: IMFWorkQueueServices
				/// </summary>
				literal String^ MF_WORKQUEUE_SERVICES = "{8E37D489-41E0-413A-9068-287C886D8DDA}";
				/// <summary>
				/// Interfaces: IMFSaveJob
				/// </summary>
				literal String^ MFNET_SAVEJOB_SERVICE = "{B85A587F-3D02-4E52-9565-55D3EC1E7FF7}";
				/// <summary>
				/// Interfaces: IPropertyStore
				/// </summary>
				literal String^ MFNETSOURCE_STATISTICS_SERVICE = "{3CB1F275-0505-4C5D-AE71-0A556344EFA1}";
				/// <summary>
				/// Interfaces: IMFSimpleAudioVolume
				/// </summary>
				literal String^ MR_CAPTURE_POLICY_VOLUME_SERVICE = "{24030ACD-107A-4265-975C-414E33E65F2A}";
				/// <summary>
				/// Interfaces: IDirect3DSurface9 | Superfices do DirectX
				/// </summary>
				literal String^ MR_BUFFER_SERVICE = "{A562248C-9AC6-4FFC-9FBA-3AF8F8AD1A4D}";
				/// <summary>
				/// Interfaces: IMFSimpleAudioVolume
				/// </summary>
				literal String^ MR_POLICY_VOLUME_SERVICE = "{1ABAA2AC-9D3B-47C6-AB48-C59506DE784D}";
				/// <summary>
				/// Interfaces: IMFAudioStreamVolume
				/// </summary>
				literal String^ MR_STREAM_VOLUME_SERVICE = "{F8B5FA2F-32EF-46F5-B172-1321212FB2C4}";
				/// <summary>
				/// Interfaces: IDirect3DDeviceManager9 | IDirectXVideoAccelerationService | IDirectXVideoMemoryConfiguration | 
				/// IMFVideoSampleAllocator
				/// </summary>
				literal String^ MR_VIDEO_ACCELERATION_SERVICE = "{EFEF5175-5C7D-4CE2-BBBD-34FF8BCA6554}";
				/// <summary>
				/// Interfaces: Várias interfaces expostas pelo misturador EVR.
				/// </summary>
				literal String^ MR_VIDEO_MIXER_SERVICE = "{073CD2FC-6CF4-40B7-8859-E89552C841F8}";
				/// <summary>
				/// Interfaces: Várias interfaces expostas pelo apresentador EVR
				/// </summary>
				literal String^ MR_VIDEO_RENDER_SERVICE = "{1092A86C-AB1A-459A-A336-831FBC4D11FF}";
			};

			/// <summary>
			/// Contém os GUIDs utilizados pelo DXVA.
			/// </summary>
			public value struct GUIDs_MFDXVAInterfaces
			{
				/// <summary>
				/// Guid da interface: IDirectXVideoProcessorService
				/// </summary>
				literal String^ GUID_IID_IDirectXVideoProcessorService = "{FC51A551-D5E7-11D9-AF55-00054E43FF02}";

				/// <summary>
				/// Guid da interface: ID3D11VideoDevice
				/// </summary>
				literal String^ GUID_IID_ID3D11VideoDevice = "{10EC4D5B-975A-4689-B9E4-D0AAC30FE333}";
			};


			
			// PROPRIEDADES

			/// <summary>
			/// [FALTA DOCUMENTAR E ADICIONAR OS PID`S] - Contém todas as propriedades utilizadas pela Media Foundation.
			/// </summary>
			public value struct GUIDs_MEDIAFOUNDATION_PROPERTIES
			{
				/// <summary>
				/// Tipo: UInt32 Desc: ‎Especifica o modo downmix estéreo para um decodificador de áudio Dolby Digital.‎ 
				/// </summary>
				literal String^ GUID_CODECAPI_AVDecDDStereoDownMixMode = "{6ce4122c-3ee9-4182-b4ae-c10fc088649d}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVDecNumWorkerThreads = "{9561c3e8-ea9e-4435-9b1e-a93e691894d8}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVDecSoftwareDynamicFormatChange = "{862e2f0a-507b-47ff-af47-01e2624298b7}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVDecVideoMaxCodedHeight = "{7262a16a-d2dc-4e75-9ba8-65c0c6d32b13}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVDecVideoMaxCodedWidth = "{5ae557b8-77af-41f5-9fa6-4db2fe1d4bca}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncAdaptiveMode = "{4419b185-da1f-4f53-bc76-097d0c1efb1e}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncCommonTranscodeEncodingProfile = "{6947787c-f508-4ea9-b1e9-a1fe3a49fbc9}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncH264CABACEnable = "{ee6cad62-d305-4248-a50e-e1b255f7caf8}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncH264PPSID = "{bfe29ec2-056c-4d68-a38d-ae5944c8582e}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncH264SPSID = "{50f38f51-2b79-40e3-b39c-7e9fa0770501}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncMaxFrameRate = "{b98e1b31-19fa-4d4f-9931-d6a5b8aab93c}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncNumWorkerThreads = "{b0c8bf60-16f7-4951-a30b-1db1609293d6}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncSliceControlMode = "{e9e782ef-5f18-44c9-a90b-e9c3c2c17b0b}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncSliceControlSize = "{92f51df3-07a5-4172-aefe-c69ca3b60e35}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoContentType = "{66117aca-eb77-459d-930c-a48d9d0683fc}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoEncodeFrameTypeQP = "{aa70b610-e03f-450c-ad07-07314e639ce7}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoEncodeQP = "{2cb5696b-23fb-4ce1-a0f9-ef5b90fd55ca}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoForceKeyFrame = "{398c1b98-8353-475a-9ef2-8f265d260345}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoLTRBufferControl = "{a4a0e93d-4cbc-444c-89f4-826d310e92a7}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoMarkLTRFrame = "{e42f4748-a06d-4ef9-8cea-3d05fde3bd3b}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoMaxNumRefFrame = "{964829ed-94f9-43b4-b74d-ef40944b69a0}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoMaxQP = "{3daf6f66-a6a7-45e0-a8e5-f2743f46a3a2}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoMeanAbsoluteDifference = "{e5c0c10f-81a4-422d-8c3f-b474a4581336}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoMinQP = "{0ee22c6a-a37c-4568-b5f1-9d4c2b3ab886}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoRateControlParams = "{87d43767-7645-44ec-b438-d3322fbca29f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoROIEnabled = "{d74f7f18-44dd-4b85-aba3-05d9f42a8280}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoSelectLayer = "{eb1084f5-6aaa-4914-bb2f-6147227f12e7}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoSupportedControls = "{d3f40fdd-77b9-473d-8196-061259e69cff}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoTemporalLayerCount = "{19caebff-b74d-4cfd-8c27-c2f9d97d5f52}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoUsage = "{1f636849-5dc1-49f1-b1d8-ce3cf62ea385}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVEncVideoUseLTRFrame = "{00752db8-55f7-4f80-895b-27639195f2ad}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_AVLowLatencyMode = "{9c27891a-ed7a-40e1-88e8-b22727a024ee}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_CODECAPI_VideoEncoderDisplayContentType = "{79b90b27-f4b1-42dc-9dd7-cdaf8135c400}";
				
				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ACCELERATEDSTREAMINGDURATION = "{3cb1f277-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_AUTORECONNECTLIMIT = "{3cb1f27a-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_AUTORECONNECTPROGRESS = "{3cb1f282-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_BROWSERUSERAGENT = "{3cb1f28b-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_BROWSERWEBPAGE = "{3cb1f28c-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_BUFFERINGTIME = "{3cb1f276-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_CACHEENABLED = "{3cb1f279-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_CLIENTGUID = "{60a2c4a6-f197-4c14-a5bf-88830d2458af}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_CONNECTIONBANDWIDTH = "{3cb1f278-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_CREDENTIAL_MANAGER = "{3cb1f280-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_DRMNET_LICENSE_REPRESENTATION = "{47eae1bd-bdfe-42e2-82f3-54a48c17962d}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_DOWNLOAD = "{3cb1f29d-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_HTTP = "{3cb1f299-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_MSB = "{3cb1f296-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_PRIVATEMODE = "{824779d8-f18b-4405-8cf1-464fb5aa8f71}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_RTSP = "{3cb1f298-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_STREAMING = "{3cb1f29c-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_TCP = "{3cb1f295-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_ENABLE_UDP = "{3cb1f294-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_FRIENDLYNAME = "{5b2a7757-bc6b-447e-aa06-0dda1c646e2f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_HOSTEXE = "{3cb1f28f-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_HOSTVERSION = "{3cb1f291-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_LOGPARAMS = "{64936ae8-9418-453a-8cda-3e0a668b353b}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_LOGURL = "{3cb1f293-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_MAXBUFFERTIMEMS = "{408b24e6-4038-4401-b5b2-fe701a9ebf10}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_MAXUDPACCELERATEDSTREAMINGDURATION = "{4aab2879-bbe1-4994-9ff0-5495bd250129}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PEERMANAGER = "{48b29adb-febf-45ee-a9bf-efb81c492efc}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PLAYERID = "{3cb1f28e-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PLAYERUSERAGENT = "{3cb1f292-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PLAYERVERSION = "{3cb1f28d-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PPBANDWIDTH = "{3cb1f281-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PREVIEWMODEENABLED = "{3cb1f27f-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROTOCOL = "{3cb1f27d-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYBYPASSFORLOCAL = "{3cb1f286-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYEXCEPTIONLIST = "{3cb1f285-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYHOSTNAME = "{3cb1f284-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYINFO = "{3cb1f29b-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYLOCATORFACTORY = "{3cb1f283-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYPORT = "{3cb1f288-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYRERUNAUTODETECTION = "{3cb1f289-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_PROXYSETTINGS = "{3cb1f287-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_RESENDSENABLED = "{3cb1f27b-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_RESOURCE_FILTER = "{815d0ff6-265a-4477-9e46-7b80ad80b5fb}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_SSLCERTIFICATE_MANAGER = "{55e6cb27-e69b-4267-940c-2d7ec5bb8a0f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_STATISTICS = "{3cb1f274-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_STREAM_LANGUAGE = "{9ab44318-f7cd-4f2d-8d6d-fa35b492cecb}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_THINNINGENABLED = "{3cb1f27c-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_TRANSPORT = "{3cb1f27e-0505-4c5d-ae71-0a556344efa1}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFNETSOURCE_UDP_PORT_RANGE = "{3cb1f29a-0505-4c5d-ae71-0a556344efa1}";
				
				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMEDIASINK_AUTOADJUST_BITRATE = "{cddcbc82-3411-4119-9135-8423c41b3957}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMEDIASINK_BASE_SENDTIME = "{cddcbc82-3411-4119-9135-8423c41b3957}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMEDIASINK_DRMACTION = "{a1db6f6c-1d0a-4cb6-8254-cb36beedbc48}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMediaSource_ApproxSeek = "{b4cd270f-244d-4969-bb92-3f0fb8316f10}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMediaSource_IterativeSeek_Max_Count = "{170b65dc-4a4e-407a-ac22-577f50e4a37c}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMediaSource_IterativeSeek_Tolerance_In_MilliSecond = "{170b65dc-4a4e-407a-ac22-577f50e4a37c}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFMediaSource_IterativeSeekIfNoIndex = "{170b65dc-4a4e-407a-ac22-577f50e4a37c}";
				
				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFOVERHEADPERFRAME = "{0eac7502-1957-4beb-914d-885f85e75436}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ASFSTREAMSINK_CORRECTED_LEAKYBUCKET = "{a2f152fb-8ad9-4a11-b345-2ce2fad8723d}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_AVDecVideoSWPowerLevel = "{fb5d2347-4dd8-4509-aed0-db5fa9aa93f4}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_AVGCONSTRAINED = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_AVGFRAMERATE = "{41d700d6-95b1-4e3f-b759-2d66d8c7ada2}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_BAVG = "{10174e76-e0ca-4a39-948c-8510c2323276}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_BDELTAQP = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_BMAX = "{ff365211-21b6-4134-ab7c-52393a8f80f6}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_BUFFERFULLNESSINFIRSTBYTE = "{b69dc3c5-64c4-4757-99cb-5d580fd5659e}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CATEGORY = "{c57a84c0-1a80-40a3-97b5-9272a403c8ae}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CHECKDATACONSISTENCY2P = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CLOSEDENTRYPOINT = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CLSID = "{c57a84c0-1a80-40a3-97b5-9272a403c8ae}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CODEDFRAMES = "{62872b55-fe0e-4930-a6d2-ccaa37e8f535}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CODEDNONZEROFRAMES = "{7adf5b69-1e3f-42d3-991d-f81e0cebe93e}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLOR_BRIGHTNESS = "{174fb0ec-2695-476c-88aa-d2b41ce75e67}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLOR_CONTRAST = "{174fb0ec-2695-476c-88aa-d2b41ce75e67}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLOR_HUE = "{174fb0ec-2695-476c-88aa-d2b41ce75e67}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLOR_SATURATION = "{174fb0ec-2695-476c-88aa-d2b41ce75e67}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_DSTLEFT = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_DSTTOP = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_HEIGHT = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_MODE = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_SRCLEFT = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_SRCTOP = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COLORCONV_WIDTH = "{dc9100be-1228-416c-9948-6f38f479654f}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COMPLEXITY = "{44fa08c7-92f5-45dc-8376-8d1d324c652a}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COMPLEXITYEX = "{d6e48f93-fd47-47a3-9262-8aefb5530332}";

				/// <summary>
				/// Tipo:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_COMPRESSIONOPTIMIZATIONTYPE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONSTRAIN_ENUMERATED_VBRQUALITY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONSTRAINDECLATENCY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONSTRAINENCCOMPLEXITY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONSTRAINENCLATENCY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_Content_DLNA_Profile_ID = "{cfa31b45-525d-4998-bb44-3f7d81542fa4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONV_INPUTFRAMERATE = "{52f8d29b-2e76-43f7-a4f6-1717904e35df}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CONV_OUTPUTFRAMERATE = "{52f8d29b-2e76-43f7-a4f6-1717904e35df}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_CRISP = "{2985f772-3af2-4d15-8cfa-8a962ff32040}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DATARATE = "{e0db0807-8003-4880-ac11-61b73f33dc60}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DECODER_DEINTERLACING = "{00c6281f-4be6-4e44-9ed8-9ec5422316e4}";

				/// <summary>
				/// [NÃO RECONHECIDO COMO UM GUID]
				/// </summary>
				literal String^ GUID_MFPKEY_Decoder_MaxNumPCMSamplesWithPaddedSilence = "{}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DECODERCOMPLEXITYPROFILE = "{c0d912d6-14da-4d31-8d83-d108915e8d77}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DECODERCOMPLEXITYREQUESTED = "{b0d7d4a7-422b-44c3-97b4-b9760cceeea9}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DELTAMVRANGEINDEX = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DENOISEOPTION = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID: 00 + 25 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DESIRED_VBRQUALITY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x1d Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DROPPEDFRAMES = "{bdb5afd3-4027-4882-806c-4162e4a7a3f0}";

				/// <summary>
				/// Tipo:  PID: 0x1 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DXVA_ENABLED = "{58e28605-1d51-48ed-a3eb-0f9baf785fbd}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 19 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_ALLOW_NOISESUB = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 +27 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_ALLOW_PCMRANGELIMITING = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 14 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_BANDTRUNC_BWCEIL = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 13 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_BANDTRUNC_BWFLOOR = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 12 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_BANDTRUNC_QCEIL = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 11 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_BANDTRUNC_QFLOOR = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 10 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_BANDTRUNCATION = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 15 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_SIMPLEMASK = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 16 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_STEREO_PREPROC = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 18 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_VBR_BAVG = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 9 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_DYN_VBR_RAVG = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ENCCOMPLEXITY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID: 0x08 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ENDOFPASS = "{b2030f2a-8bbc-46f8-a64b-a98ff7fcf02a}";

				/// <summary>
				/// Tipo:  PID: 0x00 + 20 Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ENHANCED_WMA = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_EXATTRIBUTE_SUPPORTED = "{456fe843-3c87-40c0-949d-1409c97dab2c}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FI_ENABLED = "{e020c4ca-3bdd-40ec-bcf4-4039b1450eb8}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FI_SUPPORTED = "{5ce18788-b992-49a7-a4f1-60ea21caa55f}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FORCEFRAMEHEIGHT = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FORCEFRAMEWIDTH = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FORCEMEDIANSETTING = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FOURCC = "{593e3f2e-f84d-4e85-b68d-f669400edabc}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FRAMECOUNT = "{75028eb4-4853-44d3-88a3-e499f89d227f}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_FULLFRAMERATE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_HTTP_ByteStream_Enable_Urlmon = "{eda8afdf-c171-417f-8d17-2e0918303292}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_HTTP_ByteStream_Urlmon_Bind_Flags = "{eda8afdf-c171-417f-8d17-2e0918303292}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_HTTP_ByteStream_Urlmon_Security_Id = "{eda8afdf-c171-417f-8d17-2e0918303292}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_HTTP_ByteStream_Urlmon_Window = "{eda8afdf-c171-417f-8d17-2e0918303292}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_INTERLACEDCODINGENABLED = "{56976073-06c3-4b3b-ad41-b7417fce8474}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_KEYDIST = "{18d6f8c5-2416-4d7b-90d7-9f3f21e752b4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_LIVEENCODE = "{3ffa1e60-5514-4634-86e6-1f3b7c545143}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_LOOKAHEAD = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_LOOPFILTER = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MACROBLOCKMODECOSTMETHOD = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MAXDECLATENCYMS = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MAXENCLATENCYMS = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaProtectionContainerGuid = "{42af3d7c-00cf-4a0f-81f0-adf524a5a5b5}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaProtectionSystemContext = "{636b271d-ddc7-49e9-a6c6-47385962e5bd}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaProtectionSystemContextsPerTrack = "{4454b092-d3da-49b0-8452-6850c7db764d}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaProtectionSystemId = "{636b271d-ddc7-49e9-a6c6-47385962e5bd}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaProtectionSystemIdMapping = "{636b271d-ddc7-49e9-a6c6-47385962e5bd}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MediaSource_DisableReadAhead = "{26366c14-c5bf-4c76-887b-9f1754db5f09}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MOST_RECENTLY_ENUMERATED_VBRQUALITY = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MOTIONMATCHMETHOD = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MOTIONSEARCHLEVEL = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_MOTIONSEARCHRANGE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_NOISEEDGEREMOVAL = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_NUMBFRAMES = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_NUMTHREADS = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_NUMTHREADSDEC = "{00c6281f-4be6-4e44-9ed8-9ec5422316e4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PASSESRECOMMENDED = "{38bdceea-393e-4f9a-8dc3-802cc405838f}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PASSESUSED = "{b1653ac1-cb7d-43ee-8454-3f9d811b0331}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PEAKCONSTRAINED = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PERCEPTUALOPTLEVEL = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PIXELASPECTRATIO = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PMP_Creation_Callback = "{28bb4de2-26a2-4870-b720-d26bbeb14942}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_POSTPROCESSMODE = "{00c6281f-4be6-4e44-9ed8-9ec5422316e4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PREFERRED_FRAMESIZE = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_PRODUCEDUMMYFRAMES = "{61714bc6-08a1-49d1-b827-a33aada95526}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_QPPERFRAME = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RANGEREDUX = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RAVG = "{14b2aae6-2987-460a-8b22-9c077c55d05e}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RDSUBPIXELSEARCH = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_REENCDURATION = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_REENCENDBUFFERSIZE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_REENCQPREF = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_REENCSTARTBUFFERSIZE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_REQUESTING_A_FRAMESIZE = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_DST_HEIGHT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_DST_LEFT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_DST_TOP = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_DST_WIDTH = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_GEOMAPHEIGHT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_GEOMAPWIDTH = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_GEOMAPX = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_GEOMAPY = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_INTERLACE = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_MINAPHEIGHT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_MINAPWIDTH = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_MINAPX = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_MINAPY = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_PANSCANAPHEIGHT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_PANSCANAPWIDTH = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_PANSCANAPX = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_PANSCANAPY = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_QUALITY = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_SRC_HEIGHT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_SRC_LEFT = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_SRC_TOP = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RESIZE_SRC_WIDTH = "{6612a6bc-e57d-407d-a958-285df0d9b400}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_RMAX = "{7d8dd246-aaf4-4a24-8166-19396b06ef69}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_SBESourceMode = "{3fae10bb-f859-4192-b562-1868d3da3a02}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_SourceOpenMonitor = "{074d4637-b5ae-465d-af17-1a538d2859dd}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_STAT_BAVG = "{036f6b60-ad43-485c-86c6-21a6db2c1ba3}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_STAT_BMAX = "{cd95e5b7-9143-47fb-a9d2-9db75f2e74be}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_STAT_RAVG = "{23a0e3b5-fc62-4ab8-b77c-6e0c28ab3016}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_STAT_RMAX = "{82ff7c67-6554-4749-a32b-3690dd1ae8de}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_TOTALFRAMES = "{ce5f1e3c-d3d4-4c3f-88c8-01e989d998d2}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VBRENABLED = "{e48d9459-6abe-4eb5-9211-60080c1ab984}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VBRQUALITY = "{f97b3f3a-9eff-4ac9-8247-35b30eb925f4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VIDEOSCALING = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VIDEOWINDOW = "{c1c96060-76f0-47d4-a875-5bdda90df5e9}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VOLHEADERFORREENCODE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_VTYPE = "{4e91bf89-665a-49da-bb94-88c550cfcd28}";

				/// <summary>
				/// [NÃO SUPORTADO]
				/// </summary>
				literal String^ GUID_MFPKEY_WMA_ELEMENTARY_STREAM = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_DEVICE_INDEXES = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_DEVICEPAIR_GUID = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_DMO_SOURCE_MODE = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_AES = "6f52c567-0360-4bd2-9617-ccbf1421c939{}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_AGC = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_CENTER_CLIP = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_ECHO_LENGTH = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_FRAME_SIZE = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_MICARR_BEAM = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_MICARR_MODE = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_MICARR_PREPROC = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_NOISE_FILL = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_NS = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATR_VAD = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_FEATURE_MODE = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_MIC_GAIN_BOUNDER = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_MICARRAY_DESCPTR = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_QUALITY_METRICS = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_RETRIEVE_TS_STATS = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAAECMA_SYSTEM_MODE = "{6f52c567-0360-4bd2-9617-ccbf1421c939}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADEC_DRCMODE = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADEC_FOLDDOWN_MATRIX = "{51647e9b-6a7f-4739-9e0b-294b278969eb}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADEC_HIRESOUTPUT = "{8d3fe592-eecc-4f4e-9aff-5af1679d38d2}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADEC_LTRTOUTPUT = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADEC_SPKRCFG = "{8fff67be-977f-41dc-8faf-23bac9a6df73}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADRC_AVGREF = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADRC_AVGTARGET = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADRC_PEAKREF = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMADRC_PEAKTARGET = "{7b613713-3d38-4cda-aa61-0478b1bcfc42}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAENC_AVGBYTESPERSEC = "{11caf780-921b-42ef-b755-f3a053ea1a41}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAENC_BUFFERLESSCBR = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAENC_GENERATE_DRC_PARAMS = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAENC_ORIGWAVEFORMAT = "{f5c760a2-3635-48e1-8fbd-0e498124e0a2}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAENC_RTSPDIF = "{6dbdf03b-b05c-4a03-8ec1-bbe63db10cb4}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAVOICE_ENC_BufferWindow = "{d9c8f5fe-8682-4347-8507-60a3f51f33f1}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAVOICE_ENC_DecoderDelay = "{d9c8f5fe-8682-4347-8507-60a3f51f33f1}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAVOICE_ENC_EDL = "{d9c8f5fe-8682-4347-8507-60a3f51f33f1}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMAVOICE_ENC_MusicSpeechClassMode = "{d9c8f5fe-8682-4347-8507-60a3f51f33f1}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMRESAMP_CHANNELMTX = "{af1adc73-a210-4b05-966e-5491cff48b1d}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMRESAMP_FILTERQUALITY = "{af1adc73-a210-4b05-966e-5491cff48b1d}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_WMRESAMP_LOWPASS_BANDWIDTH = "{af1adc73-a210-4b05-966e-5491cff48b1d}";

				/// <summary>
				/// Tipo:  PID:  Desc: 
				/// </summary>
				literal String^ GUID_MFPKEY_ZEROBYTEFRAMES = "{8f04aba4-313d-40fb-8031-31517813d9ef}";
			};
			



			//////////////////
			//CORE AUDIO API//
			//////////////////


			//PROPRIEDADES

			/// <summary>
			/// Contém todos os GUIDs e PIDs das propriedades de um dispositivo de Audio.
			/// </summary>
			public value struct GUIDs_CoreAudio_Propriedades
			{

				//Essa parte vai conter os Guids para as propriedades do DISPOSITIVO.

				/// <summary>
				/// Propriedade que representa o nome amigável do adaptador de áudio ao qual o dispositivo de ponto de extremidade está anexado (por exemplo, "XYZ Audio Adapter").
				/// </summary>
				literal String^ PKEY_DeviceInterface_FriendlyName = "{026e516e-b814-414b-83cd-856d6fef4822}";

				/// <summary>
				/// Propriedade que representa a descrição do dispositivo do dispositivo de ponto de extremidade (por exemplo, "alto-falantes"). 
				/// </summary>
				literal String^ PKEY_Device_DeviceDesc = "{a45c254e-df1c-4efd-8020-67d146a850e0}";

				/// <summary>
				/// Propriedade que representa o nome amigável do dispositivo de ponto de extremidade (por exemplo, "alto-falantes (adaptador de áudio XYZ)").
				/// </summary>
				literal String^ PKEY_Device_FriendlyName = "{a45c254e-df1c-4efd-8020-67d146a850e0}";









				//Essa parte vai conter os Pids dos guids acima.

				/// <summary>
				/// PID  da propriedade > PKEY_DeviceInterface_FriendlyName
				/// </summary>
				literal UInt32 PID_DeviceInterface_FriendlyName = 2;

				/// <summary>
				/// PID da propriedade > PKEY_Device_DeviceDesc
				/// </summary>
				literal UInt32 PID_Device_DeviceDesc = 2;

				/// <summary>
				/// PID da propriedade > PKEY_Device_FriendlyName
				/// </summary>
				literal UInt32 PID_Device_FriendlyName = 14;

			};
			
			/// <summary>
			/// Estrutura que define os subtypes(Subformatos) de áudio cru suportados pelo sistema.
			/// </summary>
			public value struct GUIDs_CoreAudio_KSDATAFORMAT_SUBTYPES
			{
				literal String^ CA_KSDATAFORMAT_SUBTYPE_ANALOG = "{6dba3190-67bd-11cf-a0f7-0020afd156e4}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_PCM = "{00000001-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_IEEE_FLOAT = "{00000003-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_DRM = "{00000009-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_ALAW = "{00000006-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_MULAW = "{00000007-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_ADPCM = "{00000002-0000-0010-8000-00aa00389b71}";

				literal String^ CA_KSDATAFORMAT_SUBTYPE_MPEG = "{00000050-0000-0010-8000-00aa00389b71}";
			};



			///////////
			//WIC API//
			///////////


			//CLSIDS DOS DECODIFICADORES E ENCODIFICADORES.

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_CLSIDs_DECODIFICADORES
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICAdngDecoder = "{981d9411-909e-42a7-8f5d-a747ff052edb}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICBmpDecoder = "{6b462062-7cbf-400d-9fdb-813dd10f2778}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICGifDecoder = "{381dda3c-9ce9-4834-a23e-1f98f8fc52be}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICHeifDecoder = "{e9a4a80a-44fe-4de4-8971-7150b10a5199}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICIcoDecoder = "{c61bfcdf-2e0f-4aad-a8d7-e06bafebcdfe}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICJpegDecoder = "{9456a480-e88b-43ea-9e73-0b2d9b71b1ca}";

				/// <summary>
				/// (CLSID_WICPngDecoder) 
				/// </summary>
				literal String^ CA_CLSID_WICPngDecoder = "{389ea17b-5078-4cde-b6ef-25c15175c751}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICPngDecoder1 = "{389ea17b-5078-4cde-b6ef-25c15175c751}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICPngDecoder2 = "{e018945b-aa86-4008-9bd4-6777a1e40c11}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICTiffDecoder = "{b54e85d9-fe23-499f-8b88-6acea713752b}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICWmpDecoder = "{a26cec36-234c-4950-ae16-e34aace71d0d}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_CLSIDs_ENCODIFICADORES
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICBmpEncoder = "{69be8bb4-d66d-47c8-865a-ed1589433782}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICGifEncoder = "{114f5598-0b22-40a0-86a1-c83ea495adbd}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICHeifEncoder = "{0dbecec1-9eb3-4860-9c6f-ddbe86634575}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICJpegEncoder = "{1a34f5c1-4a5a-46dc-b644-1f4567e7a676}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICPngEncoder = "{27949969-876a-41d7-9447-568f6a35a4dc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICTiffEncoder = "{0131be10-2001-4c5f-a9b0-cc88fab64ce8}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICWmpEncoder = "{ac4ce3cb-e1c1-44cd-8215-5a1665509ec2}";
			};



			//GUIDS DOS CONTAINERS DE FORMATOS SUPORTADOS.

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_CONTAINERS_FORMATOS
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatAdng = "{f3ff6d0d-38c0-41c4-b1fe-1f3824f17b84}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatBmp = "{0af1d87e-fcfe-4188-bdeb-a7906471cbe3}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatPng = "{1b7cfaf4-713f-473c-bbcd-6137425faeaf}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatIco = "{a3a860c4-338f-4c17-919a-fba4b5628f21}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatJpeg = "{19e4a5aa-5662-4fc5-a0c0-1758028e1057}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatTiff = "{163bcc30-e2e9-4f0b-961d-a3e9fdb788a3}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatGif = "{1f8a5601-7d4d-4cbd-9c82-1bc8d4eeb9a5}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatWmp = "{57a37caa-367a-4540-916b-f183c5093a4b}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatHeif = "{e1e62521-6787-405b-a339-500715b5763f}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_ContainerFormatWebp = "{e094b0e2-67f2-45b3-b0ea-115337ca7cf3}";
			};

			/// <summary>
			/// Estrutura que contém todos os formatos nativos de pixel suportado pela Windows Imaging Componenet (WIC).
			/// Essa estrutura se divide em outras para separar os tipos de pixels.
			/// </summary>
			public value struct GUIDs_WIC_NATIVE_PIXEL_FORMATS
			{
			
			};



			//GUIDs DOS VENDOR

			/// <summary>
			/// Estrutura que contém os GUIDs dos fornecedores de codificadores ou decodificadores suportados nativamente pelo sistema operacional.
			/// </summary>
			public value struct GUIDs_WIC_VENDORS
			{
				/// <summary>
				/// Prefira usar o codificador Microsoft.
				/// </summary>
				literal String^ GUID_VendorMicrosoft = "{f3ff6d0d-38c0-41c4-b1fe-1f3824f17b84}";

				/// <summary>
				/// Prefira usar o codificador nativo da Microsoft.
				/// </summary>
				literal String^ GUID_VendorMicrosoftBuiltIn = "{0af1d87e-fcfe-4188-bdeb-a7906471cbe3}";
			};


			//CLSIDS DOS COMPONENTES.

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_CLSIDs_COMPONENTES
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICImagingCategories = "{fae3d380-fea4-4623-8c75-c6b61110b681}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICBitmapDecoders = "{7ed96837-96f0-4812-b211-f13c24117ed3}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICBitmapEncoders = "{ac757296-3522-4e11-9862-c17be5a1767e}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICPixelFormats = "{2b46e70f-cda7-473e-89f6-dc9630a2390b}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICFormatConverters = "{7835eae8-bf14-49d1-93ce-533a407b2248}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICMetadataReader = "{05af94d8-7174-4cd2-be4a-4124b80ee4b8}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICMetadataWriter = "{abe3b9a4-257d-4b97-bd1a-294af496222e}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICHeifMetadataReader = "{acddfc3f-85ec-41bc-bdef-1bc262e4db05}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICHeifMetadataWriter = "{3ae45e79-40bc-4401-ace5-dd3cb16e6afe}";

				/// <summary>
				/// [DOCUMENTACAO NAO CONTÉM A QUANTIDADE DE CARACTERS ESPERADO PARA UM GUID.]
				/// </summary>
				literal String^ CLSID_WICWebpAnimMetadataReader = "{}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICWebpAnmfMetadataReader = "{85a10b03-c9f6-439f-be5e-c0fbef67807c}";
			};
		
			

			//CLSIDS DOS CONVERSORES DE FORMATOS.

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_CLSIDs_CONVERSORES_FORMATOS
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICDefaultFormatConverter = "{1a3f11dc-b514-4b17-8c5f-2154513852f1}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICFormatConverterHighColor = "{ac75d454-9f37-48f8-b972-4e19bc856011}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICFormatConverterNChannel = "{c17cabb2-d4a3-47d7-a557-339b2efbd4f1}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ CLSID_WICFormatConverterWMPhoto = "{9cb5172b-d600-46ba-ab77-77bb7e3a00d9}";
			};
		


			//GUIDS DO SISTEMA DE METADATA

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_WIC_METADA_HANDLERS
			{
				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatUnknown = "{a45e592f-9078-4a7c-adb5-4edc4fd61b1f}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatIfd = "{537396c6-2d8a-4bb6-9bf8-2f0a8e2a3adf}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatSubIfd = "{58a2e128-2db9-4e57-bb14-5177891ed331}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatExif = "{1c3c4f9d-b84a-467d-9493-36cfbd59ea57}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatGps = "{7134ab8a-9351-44ad-af62-448db6b502ec}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatInterop = "{ed686f8e-681f-4c8b-bd41-a8addbf6b3fc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatApp0 = "{79007028-268d-45d6-a3c2-354e6a504bc9}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatApp1 = "{8fd3dfc3-f951-492b-817f-69c2e6d9a5b0}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatApp13 = "{326556a2-f502-4354-9cc0-8e3f48eaf6b5}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatIPTC = "{4fab0914-e129-4087-a1d1-bc812d45a7b5}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatIRB = "{16100d66-8570-4bb9-b92d-fda4b23ece67}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormat8BIMIPTC = "{0010568c-0852-4e6a-b191-5c33ac5b0430}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormat8BIMResolutionInfo = "{739f305d-81db-43cb-ac5e-55013ef9f003}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormat8BIMIPTCDigest = "{1ca32285-9ccd-4786-8bd8-79539db6a006}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatXMP = "{bb5acc38-f216-4cec-a6c5-5f6e739763a9}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatThumbnail = "{243dcee9-8703-40ee-8ef0-22a600b8058c}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunktEXt = "{568d8936-c0a9-4923-905d-df2b38238fbc}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatXMPStruct = "{22383cf1-ed17-4e2e-af17-d85b8f6b30d0}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatXMPBag = "{833cca5f-dcb7-4516-806f-6596ab26dce4}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatXMPSeq = "{63e8df02-eb6c-456c-a224-b25e794fd648}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatXMPAlt = "{7b08a675-91aa-481b-a798-4da94908613b}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatLSD = "{e256031e-6299-4929-b98d-5ac884afba92}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatIMD = "{bd2bb086-4d52-48dd-9677-db483e85ae8f}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatGCE = "{2a25cad8-deeb-4c69-a788-0ec2266dcafd}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatAPE = "{2e043dc2-c967-4e05-875e-618bf67e85c3}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatJpegChrominance = "{f73d0dcf-cec6-4f85-9b0e-1c3956b1bef7}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatJpegLuminance = "{86908007-edfc-4860-8d4b-4ee6e83e6058}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatJpegComment = "{220e5f33-afd3-474e-9d31-7d4fe730f557}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatGifComment = "{c4b6e0e0-cfb4-4ad3-ab33-9aad2355a34a}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunkgAMA = "{f00935a5-1d5d-4cd1-81b2-9324d7eca781}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunkbKGD = "{e14d3571-6b47-4dea-b60a-87ce0a78dfb7}";

				/// <summary>
				/// [DOCUMENTACAO NAO CONTÉM A QUANTIDADE DE CARACTERS ESPERADO PARA UM GUID.]
				/// </summary>
				literal String^ GUID_MetadataFormatChunkiTXt = "{}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunkcHRM = "{9db3655b-2842-44b3-8067-12e9b375556a}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunkhIST = "{c59a82da-db74-48a4-bd6a-b69c4931ef95}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunkiCCP = "{eb4349ab-b685-450f-91b5-e802e892536c}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunksRGB = "{c115fd36-cc6f-4e3f-8363-524b87c6b0d9}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatChunktIME = "{6b00ae2d-e24b-460a-98b6-878bd03072fd}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatHeif = "{817ef3e1-1288-45f4-a852-260d9e7cce83}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatWebpANIM = "{6dc4fda6-78e6-4102-ae35-bcfa1edcc78b}";

				/// <summary>
				/// 
				/// </summary>
				literal String^ GUID_MetadataFormatWebpANMF = "{43c105ee-b93b-4abb-b003-a08c0d870471}";
			};




			//////////////////
			// Direct2D API //
			//////////////////


			//EFEITOS

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_COR
			{
				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1LookupTable3D = "{349e0eda-0088-4a79-9ca3-c7e300202020}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1ColorManagement = "{1a28524c-fdd6-4aa4-ae8f-837eb8267b37}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1ColorMatrix = "{921f03d6-641c-47df-852d-b4bb6153ae11}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1DiscreteTransfer = "{90866fcd-488e-454b-af06-e5041b66c36c}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1DpiCompensation = "{6c26c5c7-34e0-46fc-9cfd-e5823706e228}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1GammaTransfer = "{409444c4-c419-41a0-b0c1-8cd0c0a18e42}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1HdrToneMap = "{7b0b748d-4610-4486-a90c-999d9a2e2b11}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1HueToRgb = "{7b78a6bd-0141-4def-8a52-6356ee0cbdd5}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1HueRotation = "{0f4458ec-4b32-491b-9e85-bd73f44d3eb6}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1LinearTransfer = "{ad47c8fd-63ef-4acc-9b51-67979c036c06}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1OpacityMetadata = "{6c53006a-4450-4199-aa5b-ad1656fece5e}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Premultiply = "{06eab419-deed-4018-80d2-3e1d471adeb2}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1RgbToHue = "{23f3e5ec-91e8-4d3d-ad0a-afadc1004aa1}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Saturation = "{5cb2d9cf-327d-459f-a0ce-40c0b2086bf7}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1TableTransfer = "{5bf818c3-5e43-48cb-b631-868396d6a1d4}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Tint = "{36312b17-f7dd-4014-915d-ffca768cf211}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1UnPremultiply = "{fb9ac489-ad8d-41ed-9999-bb6347d110f7}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1WhiteLevelAdjustment = "{44a1cadb-6cdd-4818-8ff4-26c1cfe95bdb}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1YCbCr = "{99503cc1-66c7-45c9-a875-8ad8a7914401}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_COMPOSICAO
			{
				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1AlphaMask = "{c80ecff0-3fd5-4f05-8328-c5d1724b4f0a}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1ArithmeticComposite = "{fc151437-049a-4784-a24a-f1c4daf20987}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Blend = "{81c5b77b-13f8-4cdd-ad20-c890547ac65d}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Composite = "{48fc9f51-f6ac-48f1-8b58-3b28ac46f76d}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1CrossFade = "{12f575e8-4db1-485f-9a84-03a07dd3829f}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_FILTRO
			{
				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1ConvolveMatrix = "{407f8c08-5533-4331-a341-23cc3877843e}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1DirectionalBlur = "{174319a6-58e9-49b2-bb63-caf2c811a3db}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1EdgeDetection = "{eff583ca-cb07-4aa9-ac5d-2cc44c76460f}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1GaussianBlur = "{1feb6d69-2fe6-4ac9-8c58-1d7f93e7a6a5}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Morphology = "{eae6c40d-626a-4c2d-bfcb-391001abe202}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_ILUMINACAO_E_ESTILIZACAO
			{
				/// <summary>
				/// Guid estranho na documentação!
				/// </summary>
				literal String^ CLSID_D2D1DisplacementMap = "{}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1DistantDiffuse = "{3e7efd62-a32d-46d4-a83c-5278889ac954}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1DistantSpecular = "{428c1ee5-77b8-4450-8ab5-72219c21abda}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Emboss = "{b1c5eb2b-0348-43f0-8107-4957cacba2ae}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1PointDiffuse = "{b9e303c3-c08c-4f91-8b7b-38656bc48c20}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1PointSpecular = "{09c3ca26-3ae2-4f09-9ebc-ed3865d53f22}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Posterize = "{2188945e-33a3-4366-b7bc-086bd02d0884}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Shadow = "{c67ea361-1863-4e69-89db-695d3e9a5b6b}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1SpotDiffuse = "{818a1105-7932-44f4-aa86-08ae7b2f2c93}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1SpotSpecular = "{edae421e-7654-4a37-9db8-71acc1beb3c1}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_FOTO
			{
				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Brightness = "{8cea8d1e-77b0-4986-b3b9-2f0c0eae7887}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Contrast = "{b648a78a-0ed5-4f80-a94a-8e825aca6b77}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Exposure = "{b56c8cfa-f634-41ee-bee0-ffa617106004}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Grayscale = "{36dde0eb-3725-42e0-836d-52fb20aee644}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1HighlightsShadows = "{cadc8384-323f-4c7e-a361-2e2b24df6ee4}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Histogram = "{881db7d0-f7ee-4d4d-a6d2-4697acc66ee8}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Invert = "{e0c3784d-cb39-4e84-b6fd-6b72f0810263}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Sepia = "{3a1af410-5f1d-4dbe-84df-915da79b7153}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Sharpen = "{c9b887cb-c5ff-4dc5-9779-273dcf417c7d}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Straighten = "{4da47b12-79a3-4fb0-8237-bbc3b2a4de08}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1TemperatureTint = "{89176087-8af9-4a08-aeb1-895f38db1766}";

				/// <summary>
				///
				/// </summary>
				literal String^ CLSID_D2D1Vignette = "{c00c40be-5e67-4ca3-95b4-f4b02c115135}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_FONTE
			{
				/// <summary>
				/// Efeito fonte do Bitmap
				/// </summary>
				literal String^ CLSID_D2D1BitmapSource = "{0x5fb6c24d, 0xc6dd, 0x4231, 0x94, 0x4,  0x50, 0xf4, 0xd5, 0xc3, 0x25, 0x2d}";

				/// <summary>
				/// Efeito inundação
				/// </summary>
				literal String^ CLSID_D2D1Flood = "{61c23c20-ae69-4d8e-94cf-50078df638f2}";

				/// <summary>
				/// Efeito turbulência 
				/// </summary>
				literal String^ CLSID_D2D1Turbulence = "{cf2bb6ae-889a-4ad7-ba29-a2fd732c9fc9}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_TRANSFORMACAO
			{
				/// <summary>
				/// 2D efeito de transformação afim
				/// </summary>
				literal String^ CLSID_D2D12DAffineTransform = "{6aa97485-6354-4cfc-908c-e4a74f62c96c}";

				/// <summary>
				/// Efeito de transformação 3D
				/// </summary>
				literal String^ CLSID_D2D13DTransform = "{e8467b04-ec61-4b8a-b5de-d4d73debea5a}";

				/// <summary>
				/// Efeito de transformação de perspectiva 3D
				/// </summary>
				literal String^ CLSID_D2D13DPerspectiveTransform = "{c2844d0b-3d86-46e7-85ba-526c9240f3fb}";

				/// <summary>
				/// Efeito border
				/// </summary>
				literal String^ CLSID_D2D1Border = "{2a2d49c0-4acf-43c7-8c6a-7c4a27874d27}";

				/// <summary>
				/// Efeito crop
				/// </summary>
				literal String^ CLSID_D2D1Crop = "{e23f7110-0e9a-4324-af47-6a2c0c46f35b}";

				/// <summary>
				/// Efeito de escala
				/// </summary>
				literal String^ CLSID_D2D1Scale = "{9daf9369-3846-4d0e-a44e-0c607934a5d7}";

				/// <summary>
				/// Efeito tile
				/// </summary>
				literal String^ CLSID_D2D1Tile = "{b0784138-3b76-4bc5-b13b-0fa2ad02659f}";
			};

			/// <summary>
			/// 
			/// </summary>
			public value struct GUIDs_D2D_CLSIDs_EFEITOS_TRANSPARENCIA
			{
				/// <summary>
				/// Efeito chroma-key
				/// </summary>
				literal String^ CLSID_D2D1ChromaKey = "{74c01f5b-2a0d-408c-88e2-c7a3c7197742}";

				/// <summary>
				/// Luminância ao efeito alfa
				/// </summary>
				literal String^ CLSID_D2D1LuminanceToAlpha = "{41251ab7-0beb-46f8-9da7-59e93fcce5de}";

				/// <summary>
				/// Efeito opacidade
				/// </summary>
				literal String^ CLSID_D2D1Opacity = "{811d79a4-de28-4454-8094-c64685f8bd4c}";
			};








			/////////////////////////////////////////////////////////////
			//GUIDS DAS INTERFACES NATIVAS E GERENCIADAS DA BIBLIOTECA.//
			/////////////////////////////////////////////////////////////


			//NATIVAS

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API COM do Windows.
			/// </summary>
			public value struct GUIDs_InterfacesWindows
			{
				/// <summary>
				/// IID da interface base de todas as interfaces do Media Foundation e Apis diversas.
				/// </summary>
				literal String^ IID_IUnknown = "{00000000-0000-0000-C000-000000000046}";

				/// <summary>
				/// IID da interface nativa: IPropertyStore
				/// </summary>
				literal String^ IID_PropertyStore = "{886d8eeb-8cf2-4446-8d02-cdba1dbdcf99}";
			};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API do Media Foundation.
			/// </summary>
			public value struct GUIDs_InterfacesMediaFoundation
			{

				/// <summary>
				/// IID da interface nativa: IMFMediaSink
				/// </summary>
				literal String^ IID_IMFMediaSink = "{6ef2a660-47c0-4666-b13d-cbb717f2fa2c}";

				/// <summary>
				/// IID da interface nativa: IMFStreamSink
				/// </summary>
				literal String^ IID_IMFStreamSink = "{0A97B3CF-8E7C-4a3d-8F8C-0C843DC247FB}";

				/// <summary>
				/// IID da interface nativa: IMFSinkWriter
				/// </summary>
				literal String^ IID_IMFSinkWriter = "{3137f1cd-fe5e-4805-a5d8-fb477448cb3d}";

				/// <summary>
				/// IID da interface nativa: IMFSinkWriterCallback
				/// </summary>
				literal String^ IID_IMFSinkWriterCallback = "{666f76de-33d2-41b9-a458-29ed0a972c58}";

				/// <summary>
				/// IID da interface nativa: IMFClockStateSink
				/// </summary>
				literal String^ IID_IMFClockStateSink = "{F6696E82-74F7-4f3d-A178-8A5E09C3659F}";

				/// <summary>
				/// IID da interface nativa: IVideoRenderer
				/// </summary>
				literal String^ IID_IVideoRenderer = "{DFDFD197-A9CA-43d8-B341-6AF3503792CD}";

				/// <summary>
				/// IID da interface nativa: IMFGetService
				/// </summary>
				literal String^ IID_IMFGetService = "{fa993888-4383-415a-a930-dd472a8cf6f7}";

				/// <summary>
				/// IID da interface nativa: IMFVideoDisplayControl
				/// </summary>
				literal String^ IID_IMFVideoDisplayControl = "{a490b1e4-ab84-4d31-a1b2-181e03b1077a}";

				/// <summary>
				/// IID da interface nativa: IMFClock
				/// </summary>
				literal String^ IID_IMFClock = "{2eb1e945-18b8-4139-9b1a-d5d584818530}";

				/// <summary>
				/// IID da interface nativa: IMFPresentationClock
				/// </summary>
				literal String^ IID_IMFPresentationClock = "{868CE85C-8EA9-4f55-AB82-B009A910A805}";

				/// <summary>
				/// IID da interface nativa: IMFPresentationTimeSource
				/// </summary>
				literal String^ IID_IMFPresentationTimeSource = "{7FF12CCE-F76F-41c2-863B-1666C8E5E139}";

				/// <summary>
				/// IID da interface nativa: IMFActivate
				/// </summary>
				literal String^ IID_IMFActivate = "{7FEE9E9A-4A89-47a6-899C-B6A53A70FB67}";

				/// <summary>
				/// IID da interface nativa: IMFAttributes
				/// </summary>
				literal String^ IID_IMFAttributes = "{2cd2d921-c447-44a7-a13c-4adabfc247e3}";

				/// <summary>
				/// IID da interface nativa: IMFMediaType
				/// </summary>
				literal String^ IID_IMFMediaType = "{44ae0fa8-ea31-4109-8d2e-4cae4997c555}";

				/// <summary>
				/// IID da interface nativa: IMFMediaTypeHandler
				/// </summary>
				literal String^ IID_IMFMediaTypeHandler = "{e93dcf6c-4b07-4e1e-8123-aa16ed6eadf5}";

				/// <summary>
				/// IID da interface nativa: IMFMediaBuffer
				/// </summary>
				literal String^ IID_IMFMediaBuffer = "{045FA593-8799-42b8-BC8D-8968C6453507}";

				/// <summary>
				/// IID da interface nativa: IMF2DBuffer
				/// </summary>
				literal String^ IID_IMF2DBuffer = "{7DC9D5F9-9ED9-44ec-9BBF-0600BB589FBB}";

				/// <summary>
				/// IID da interface nativa: IMF2DBuffer2
				/// </summary>
				literal String^ IID_IMF2DBuffer2 = "{33ae5ea6-4316-436f-8ddd-d73d22f829ec}";

				/// <summary>
				/// IID da interface nativa: IMFDXGIBuffer
				/// </summary>
				literal String^ IID_IMFDXGIBuffer = "{e7174cfa-1c9e-48b1-8866-626226bfc258}";

				/// <summary>
				/// IID da interface nativa: IMFVideoSampleAllocator
				/// </summary>
				literal String^ IID_IMFVideoSampleAllocator = "{86cbc910-e533-4751-8e3b-f19b5b806a03}";

				/// <summary>
				/// IID da interface nativa: IMFVideoSampleAllocatorEx
				/// </summary>
				literal String^ IID_IMFVideoSampleAllocatorEx = "{545b3a48-3283-4f62-866f-a62d8f598f9f}";

				/// <summary>
				/// IID da interface nativa: IMFVideoSampleAllocatorCallback
				/// </summary>
				literal String^ IID_IMFVideoSampleAllocatorCallback = "{992388B4-3372-4f67-8B6F-C84C071F4751}";

				/// <summary>
				/// IID da interface nativa: IMFSample
				/// </summary>
				literal String^ IID_IMFSample = "{c40a00f2-b93a-4d80-ae8c-5a1c634f58e4}";

				/// <summary>
				/// IID da interface nativa: IMFSourceReader
				/// </summary>
				literal String^ IID_IMFSourceReader = "{70ae66f2-c809-4e4f-8915-bdcb406b7993}";

				/// <summary>
				/// IID da interface nativa: IMFSourceReaderCallback
				/// </summary>
				literal String^ IID_IMFSourceReaderCallback = "{deec8d99-fa1d-4d82-84c2-2c8969944867}";

				/// <summary>
				/// IID da interface nativa: IMFMediaSinkPreroll
				/// </summary>
				literal String^ IID_IMFMediaSinkPreroll = "{5dfd4b2a-7674-4110-a4e6-8a68fd5f3688}";

				/// <summary>
				/// IID da interface nativa: IMFAsyncCallback
				/// </summary>
				literal String^ IID_IMFAsyncCallback = "{a27003cf-2354-4f2a-8d6a-ab7cff15437e}";

				/// <summary>
				/// IID da interface nativa: IMFMediaEventGenerator
				/// </summary>
				literal String^ IID_IMFMediaEventGenerator = "{2CD0BD52-BCD5-4B89-B62C-EADC0C031E7D}";

				/// <summary>
				/// IID da interface nativa: IMFMediaSource
				/// </summary>
				literal String^ IID_IMFMediaSource = "{279a808d-aec7-40c8-9c6b-a6b492c78a66}";

				/// <summary>
				/// IID da interface nativa: IMFMediaSourceEx
				/// </summary>
				literal String^ IID_IMFMediaSourceEx = "{3C9B2EB9-86D5-4514-A394-F56664F9F0D8}";

				/// <summary>
				/// IID da interface nativa: IMFSourceResolver
				/// </summary>
				literal String^ IID_IMFSourceResolver = "{FBE5A32D-A497-4b61-BB85-97B1A848A6E3}";

				/// <summary>
				/// IID da interface nativa: IMFStreamDescriptor
				/// </summary>
				literal String^ IID_IMFStreamDescriptor = "{56c03d9c-9dbb-45f5-ab4b-d80f47c05938}";

				/// <summary>
				/// IID da interface nativa: IMFPresentationDescriptor
				/// </summary>
				literal String^ IID_IMFPresentationDescriptor = "{03cb2711-24d7-4db6-a17f-f3a7a479a536}";

				/// <summary>
				/// IID da interface nativa: IMFMediaStream
				/// </summary>
				literal String^ IID_IMFMediaStream = "{D182108F-4EC6-443f-AA42-A71106EC825F}";

				/// <summary>
				/// IID da interface nativa: IMFSimpleAudioVolume
				/// </summary>
				literal String^ IID_IMFSimpleAudioVolume = "{089EDF13-CF71-4338-8D13-9E569DBDC319}";

				/// <summary>
				/// IID da interface nativa: IMFAudioStreamVolume
				/// </summary>
				literal String^ IID_IMFAudioStreamVolume = "{76B1BBDB-4EC8-4f36-B106-70A9316DF593}";

				/// <summary>
				/// IID da interface nativa: IMFTopologyNode
				/// </summary>
				literal String^ IID_IMFTopologyNode = "{83CF873A-F6DA-4bc8-823F-BACFD55DC430}";

				/// <summary>
				/// IID da interface nativa: IMFTopology
				/// </summary>
				literal String^ IID_IMFTopology = "{83CF873A-F6DA-4bc8-823F-BACFD55DC433}";

				/// <summary>
				/// IID da interface nativa: IMFTopoLoader
				/// </summary>
				literal String^ IID_IMFTopoLoader = "{DE9A6157-F660-4643-B56A-DF9F7998C7CD}";

				/// <summary>
				/// IID da interface nativa: IMFCollection
				/// </summary>
				literal String^ IID_IMFCollection = "{5BC8A76B-869A-46a3-9B03-FA218A66AEBE}";

				/// <summary>
				/// IID da interface nativa: IMFTopologyNodeAttributeEditor
				/// </summary>
				literal String^ IID_IMFTopologyNodeAttributeEditor = "{676aa6dd-238a-410d-bb99-65668d01605a}";

				/// <summary>
				/// IID da interface nativa: IMFTopologyServiceLookup
				/// </summary>
				literal String^ IID_IMFTopologyServiceLookup = "{fa993889-4383-415a-a930-dd472a8cf6f7}";

				/// <summary>
				/// IID da interface nativa: IMFTopologyServiceLookupClient
				/// </summary>
				literal String^ IID_IMFTopologyServiceLookupClient = "{fa99388a-4383-415a-a930-dd472a8cf6f7}";

				/// <summary>
				/// IID da interface nativa: IMFRateSupport
				/// </summary>
				literal String^ IID_IMFRateSupport = "{0a9ccdbc-d797-4563-9667-94ec5d79292d}";

				/// <summary>
				/// IID da interface nativa: IMFRateControl
				/// </summary>
				literal String^ IID_IMFRateControl = "{88ddcd21-03c3-4275-91ed-55ee3929328f}";

				/// <summary>
				/// IID da interface nativa: IMFMediaSession
				/// </summary>
				literal String^ IID_IMFMediaSession = "{90377834-21D0-4dee-8214-BA2E3E6C1127}";

			};

			/// <summary>
			/// Estrutura que contém os IID que fazem parte da API do Direct3D 9. Nem todas as interfaces podem está disponiveis na biblioteca.
			/// </summary>
			public value struct GUIDs_InterfacesDirect3D9
			{
				/// <summary>
				/// IID da interface nativa: IDirect3DDeviceManager9
				/// </summary>
				literal String^ IID_IDirect3DDeviceManager9 = "{a0cade0f-06d5-4cf4-a1c7-f3cdd725aa75}";

				/// <summary>
				/// IID da interface nativa: IDirect3DDevice9
				/// </summary>
				literal String^ IID_IDirect3DDevice9 = "{D0223B96-BF7A-43fd-92BD-A43B0D82B9EB}";

				/// <summary>
				/// IID da interface nativa: IDirect3D9
				/// </summary>
				literal String^ IID_IDirect3D9 = "{81BDCBCA-64D4-426d-AE8D-AD0147F4275C}";

				/// <summary>
				/// IID da interface nativa: IDirect3DSurface9
				/// </summary>
				literal String^ IID_IDirect3DSurface9 = "{0CFBAF3A-9FF6-429a-99B3-A2796AF8B89B}";
			};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API do Direct3D 10.
			/// (Está estrutura só contem o IID para uma interface apenas).
			/// </summary>
			public value struct GUIDs_InterfacesDirect3D10
			{
				/// <summary>
				/// IID da interface nativa: ID3D10Multithread
				/// </summary>
				literal String^ IID_ID3D10Multithread = "{9B7E4E00-342C-4106-A19F-4F2704F689F0}";
			};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API do Direct3D 11.
			/// </summary>
			public value struct GUIDs_InterfacesDirect3D11
			{
				/// <summary>
				/// IID da interface nativa: ID3D11DeviceContext
				/// </summary>
				literal String^ IID_ID3D11DeviceContext = "{c0bfa96c-e089-44fb-8eaf-26f8796190da}";

				/// <summary>
				/// IID da interface nativa: ID3D11DeviceContext1
				/// </summary>
				literal String^ IID_ID3D11DeviceContext1 = "{bb2c6faa-b5fb-4082-8e6b-388b8cfa90e}";

				/// <summary>
				/// IID da interface nativa: ID3D11DeviceContext2
				/// </summary>
				literal String^ IID_ID3D11DeviceContext2 = "{420d5b32-b90c-4da4-bef0-359f6a24a83a}";

				/// <summary>
				/// IID da interface nativa: ID3D11DeviceContext3
				/// </summary>
				literal String^ IID_ID3D11DeviceContext3 = "{b4e3c01d-e79e-4637-91b2-510e9f4c9b8f}";

				/// <summary>
				/// IID da interface nativa: ID3D11DeviceContext4
				/// </summary>
				literal String^ IID_ID3D11DeviceContext4 = "{917600da-f58c-4c33-98d8-3e15b390fa24}";

				/// <summary>
				/// IID da interface nativa: IMFDXGIDeviceManager
				/// </summary>
				literal String^ IID_IMFDXGIDeviceManager = "{eb533d5d-2db6-40f8-97a9-494692014f07}";

				/// <summary>
				/// IID da interface nativa: IDXGISwapChain
				/// </summary>
				literal String^ IID_IDXGISwapChain = "{310d36a0-d2e7-4c0a-aa04-6a9d23b8886a}";

				/// <summary>
				/// IID da interface nativa: IID_ID3D11Fence
				/// </summary>
				literal String^ IID_ID3D11Fence = "{affde9d1-1df7-4bb7-8a34-0f46251dab80}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device
				/// </summary>
				literal String^ IID_ID3D11Device = "{db6f6ddb-ac77-4e88-8253-819df9bbf140}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device1
				/// </summary>
				literal String^ IID_ID3D11Device1 = "{a04bfb29-08ef-43d6-a49c-a9bdbdcbe686}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device2
				/// </summary>
				literal String^ IID_ID3D11Device2 = "{9d06dffa-d1e5-4d07-83a8-1bb123f2f841}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device3
				/// </summary>
				literal String^ IID_ID3D11Device3 = "{A05C8C37-D2C6-4732-B3A0-9CE0B0DC9AE6}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device4
				/// </summary>
				literal String^ IID_ID3D11Device4 = "{8992ab71-02e6-4b8d-ba48-b056dcda42c4}";

				/// <summary>
				/// IID da interface nativa: ID3D11Device5
				/// </summary>
				literal String^ IID_ID3D11Device5 = "{8ffde202-a0e7-45df-9e01-e837801b5ea0}";

				/// <summary>
				/// IID da interface nativa: ID3D11VertexShader
				/// </summary>
				literal String^ IID_ID3D11VertexShader = "{3b301d64-d678-4289-8897-22f8928b72f3}";

				/// <summary>
				/// IID da interface nativa: ID3D11Texture1D
				/// </summary>
				literal String^ IID_ID3D11Texture1D = "{f8fb5c27-c6b3-4f75-a4c8-439af2ef564c}";

				/// <summary>
				/// IID da interface nativa: ID3D11Texture2D
				/// </summary>
				literal String^ IID_ID3D11Texture2D = "{6f15aaf2-d208-4e89-9ab4-489535d34f9c}";

				/// <summary>
				/// IID da interface nativa: ID3D11Texture2D1
				/// </summary>
				literal String^ IID_ID3D11Texture2D1 = "{51218251-1E33-4617-9CCB-4D3A4367E7BB}";

				/// <summary>
				/// IID da interface nativa: ID3D11Texture3D
				/// </summary>
				literal String^ IID_ID3D11Texture3D = "{037e866e-f56d-4357-a8af-9dabbe6e250e}";

				/// <summary>
				/// IID da interface nativa: ID3D11Texture3D1
				/// </summary>
				literal String^ IID_ID3D11Texture3D1 = "{0C711683-2853-4846-9BB0-F3E60639E46A}";

				/// <summary>
				/// IID da interface nativa: ID3D11RasterizerState
				/// </summary>
				literal String^ IID_ID3D11RasterizerState = "{9bb4ab81-ab1a-4d8f-b506-fc04200b6ee7}";

				/// <summary>
				/// IID da interface nativa: ID3D11RasterizerState
				/// </summary>
				literal String^ IID_ID3D11RasterizerState1 = "{1217d7a6-5039-418c-b042-9cbe256afd6e}";

				/// <summary>
				/// IID da interface nativa: ID3D11RasterizerState
				/// </summary>
				literal String^ IID_ID3D11RasterizerState2 = "{6fbd02fb-209f-46c4-b059-2ed15586a6ac}";

				/// <summary>
				/// IID da interface nativa: ID3D11Query
				/// </summary>
				literal String^ IID_ID3D11Query = "{d6c00747-87b7-425e-b84d-44d108560afd}";

				/// <summary>
				/// IID da interface nativa: ID3D11Query1
				/// </summary>
				literal String^ IID_ID3D11Query1 = "{631b4766-36dc-461d-8db6-c47e13e60916}";

				/// <summary>
				/// IID da interface nativa: ID3D11Predicate
				/// </summary>
				literal String^ IID_ID3D11Predicate = "{9eb576dd-9f77-4d86-81aa-8bab5fe490e2}";

				/// <summary>
				/// IID da interface nativa: ID3D11PixelShader 
				/// </summary>
				literal String^ IID_ID3D11PixelShader = "{ea82e40d-51dc-4f33-93d4-db7c9125ae8c}";

				/// <summary>
				/// IID da interface nativa: ID3D11InputLayou
				/// </summary>
				literal String^ IID_ID3D11InputLayou = "{e4819ddc-4cf0-4025-bd26-5de82a3e07b7}";

				/// <summary>
				/// IID da interface nativa: ID3D11HullShader
				/// </summary>
				literal String^ IID_ID3D11HullShader = "{8e5c6061-628a-4c8e-8264-bbe45cb3d5dd}";

				/// <summary>
				/// IID da interface nativa: ID3D11GeometryShader
				/// </summary>
				literal String^ IID_ID3D11GeometryShader = "{38325b96-effb-4022-ba02-2e795b70275c}";

				/// <summary>
				/// IID da interface nativa: ID3D11DomainShader 
				/// </summary>
				literal String^ IID_ID3D11DomainShader = "{f582c508-0f36-490c-9977-31eece268cfa}";

				/// <summary>
				/// IID da interface nativa: ID3D11ShaderResourceView 
				/// </summary>
				literal String^ IID_ID3D11ShaderResourceView = "{b0e06fe0-8192-4e1a-b1ca-36d7414710b2}";

				/// <summary>
				/// IID da interface nativa: ID3D11SamplerState 
				/// </summary>
				literal String^ IID_ID3D11SamplerState = "{da6fea51-564c-4487-9810-f0d0f9b4e3a5}";

				/// <summary>
				/// IID da interface nativa: ID3D11UnorderedAccessView 
				/// </summary>
				literal String^ IID_ID3D11UnorderedAccessView = "{28acf509-7f5c-48f6-8611-f316010a6380}";

				/// <summary>
				/// IID da interface nativa: ID3D11UnorderedAccessView1 
				/// </summary>
				literal String^ IID_ID3D11UnorderedAccessView1 = "{7b3b6153-a886-4544-ab37-6537c8500403}";

				/// <summary>
				/// IID da interface nativa: ID3D11RenderTargetView 
				/// </summary>
				literal String^ IID_ID3D11RenderTargetView = "{dfdba067-0b8d-4865-875b-d7b4516cc164}";

				/// <summary>
				/// IID da interface nativa: ID3D11RenderTargetView1 
				/// </summary>
				literal String^ IID_ID3D11RenderTargetView1 = "{ffbe2e23-f011-418a-ac56-5ceed7c5b94b}";

				/// <summary>
				/// IID da interface nativa: ID3D11DepthStencilView 
				/// </summary>
				literal String^ IID_ID3D11DepthStencilView = "{9fdac92a-1876-48c3-afad-25b94f84a9b6}";

				/// <summary>
				/// IID da interface nativa: ID3D11DepthStencilState 
				/// </summary>
				literal String^ IID_ID3D11DepthStencilState = "{03823efb-8d8f-4e1c-9aa2-f64bb2cbfdf1}";

				/// <summary>
				/// IID da interface nativa: ID3D11Asynchronous 
				/// </summary>
				literal String^ IID_ID3D11Asynchronous = "{4b35d0cd-1e15-4258-9c98-1b1333f6dd3b}";

				/// <summary>
				/// IID da interface nativa: ID3D11Counter 
				/// </summary>
				literal String^ IID_ID3D11Counter = "{6e8c49fb-a371-4770-b440-29086022b741}";

				/// <summary>
				/// IID da interface nativa: ID3D11ComputeShader 
				/// </summary>
				literal String^ IID_ID3D11ComputeShader = "{4f5b196e-c2bd-495e-bd01-1fded38e4969}";

				/// <summary>
				/// IID da interface nativa: ID3D11ClassLinkage 
				/// </summary>
				literal String^ IID_ID3D11ClassLinkage = "{ddf57cba-9543-46e4-a12b-f207a0fe7fed}";

				/// <summary>
				/// IID da interface nativa: ID3D11ClassInstance 
				/// </summary>
				literal String^ IID_ID3D11ClassInstance = "{a6cd7faa-b0b7-4a2f-9436-8662a65797cb}";

				/// <summary>
				/// IID da interface nativa: ID3D11BlendState 
				/// </summary>
				literal String^ IID_ID3D11BlendState = "{75b68faa-347d-4159-8f45-a0640f01cd9a}";

				/// <summary>
				/// IID da interface nativa: ID3D11BlendState1 
				/// </summary>
				literal String^ IID_ID3D11BlendState1 = "{cc86fabe-da55-401d-85e7-e3c9de2877e9}";

				/// <summary>
				/// IID da interface nativa: ID3D11Buffer 
				/// </summary>
				literal String^ IID_ID3D11Buffer = "{48570b85-d1ee-4fcd-a250-eb350722b037}";

				/// <summary>
				/// IID da interface nativa: ID3D11Resource 
				/// </summary>
				literal String^ IID_ID3D11Resource = "{dc8e63f3-d12b-4952-b47b-5e45026a862d}";

				/// <summary>
				/// IID da interface nativa: 
				/// </summary>
				literal String^ IID_ID3D11View = "{839d1216-bb2e-412b-b7f4-a9dbebe08ed1}";

				/// <summary>
				/// IID da interface nativa: 
				/// </summary>
				literal String^ IID_ID3D11DeviceChild = "{1841e5c8-16b0-489b-bcc8-44cfb0d5deae}";

				/// <summary>
				/// IID da interface nativa: ID3D11CommandList
				/// </summary>
				literal String^ IID_ID3D11CommandList = "{a24bc4d1-769e-43f7-8013-98ff566c18e2}";

				/// <summary>
				/// IID da interface nativa: ID3D11Multithread
				/// </summary>
				literal String^ IID_ID3D11Multithread = "{9B7E4E00-342C-4106-A19F-4F2704F689F0}";
			};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API do Direct2D 11.
			/// </summary>
			public value struct GUIDs_InterfacesDirect2D
			{};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da API do DXGI.
			/// </summary>
			public value struct GUIDs_InterfacesDXGI
			{

			};

			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da MMDevice Api.
			/// </summary>
			public value struct GUIDs_InterfacesMMDevice
			{
				/// <summary>
				/// IID da interface nativa: IMMDevice 
				/// </summary>
				literal String^ IID_IMMDevice = "{D666063F-1587-4E43-81F1-B948E807363F}";

				/// <summary>
				/// IID da interface nativa: IMMDeviceCollection 
				/// </summary>
				literal String^ IID_IMMDeviceCollection = "{0BD7A1BE-7A1A-44DB-8397-CC5392387B5E}";

				/// <summary>
				/// IID da interface nativa: IMMDeviceEnumerator 
				/// </summary>
				literal String^ IID_IMMDeviceEnumerator = "{A95664D2-9614-4F35-A746-DE8DB63617E}";

				/// <summary>
				/// IID da interface nativa: IMMNotificationClient 
				/// </summary>
				literal String^ IID_IMMNotificationClient = "{7991EEC9-7E89-4D85-8390-6C703CEC60C0}";
			};
			
			/// <summary>
			/// Estrutura que contém os IID de todas as interfaces disponiveis nessa biblioteca que fazem parte da WASAPI Api.
			/// </summary>
			public value struct GUIDs_InterfacesWASAPI
			{
				/// <summary>
				/// IID da interface nativa: IAudioClient
				/// </summary>
				literal String^ IID_IAudioClient = "{1CB9AD4C-DBFA-4c32-B178-C2F568A703B2}";

				/// <summary>
				/// IID da interface nativa: IAudioClient2 
				/// </summary>
				literal String^ IID_IAudioClient2 = "{726778CD-F60A-4eda-82DE-E47610CD78AA}";

				/// <summary>
				/// IID da interface nativa: IAudioClient3  
				/// </summary>
				literal String^ IID_IAudioClient3 = "{7ED4EE07-8E67-4CD4-8C1A-2B7A5987AD4}";

				/// <summary>
				/// IID da interface nativa: IAudioRenderClient 
				/// </summary>
				literal String^ IID_IAudioRenderClient = "{F294ACFC-3146-4483-A7BF-ADDCA7C260E2}";

				/// <summary>
				/// IID da interface nativa: IAudioCaptureClient
				/// </summary>
				literal String^ IID_IAudioCaptureClient = "{C8ADBD64-E71E-48a0-A4DE-185C395CD317}";
				                                          
				/// <summary>
				/// IID da interface nativa: IAudioClock 
				/// </summary>
				literal String^ IID_IAudioClock = "{CD63314F-3FBA-4a1b-812C-EF96358728E7}";

				/// <summary>
				/// IID da interface nativa: IAudioClock2
				/// </summary>
				literal String^ IID_IAudioClock2 = "{6f49ff73-6727-49ac-a008-d98cf5e70048}";

				/// <summary>
				/// IID da interface nativa: IAudioSessionEvents
				/// </summary>
				literal String^ IID_IAudioSessionEvents = "{24918ACC-64B3-37C1-8CA9-74A66E9957A8}";

				/// <summary>
				/// IID da interface nativa: ISimpleAudioVolume
				/// </summary>
				literal String^ IID_ISimpleAudioVolume = "{87CE5498-68D6-44E5-9215-6DA47EF883D8}";

				/// <summary>
				/// IID da interface nativa: IChannelAudioVolume
				/// </summary>
				literal String^ IID_IChannelAudioVolume = "{1C158861-B533-4B30-B1CF-E853E51C59B8}";

				/// <summary>
				/// IID da interface nativa: IAudioSessionManager
				/// </summary>
				literal String^ IID_IAudioSessionManager = "{BFA971F1-4D5E-40BB-935E-967039BFBEE4}";
			};		
		}

		//Namespace que contém todas as contantes utilizadas pelas diversas bibliotecas presentes nesta biblioteca.
		namespace Constantes
		{

			//////////////
			// DXGI API //
			//////////////

			



			//////////////////
			// DIRECT2D API //
			//////////////////

			/// <summary> 
			/// (FALTA DOCUMENTAR) - Contém todas as constantes utilizadas pela api do Direct2D.
			/// </summary>
			public value struct CA_Direct2D
			{
				/// <summary>
				/// 
				/// </summary>
				literal Int32 CA_D2D1_APPEND_ALIGNED_ELEMENT = D2D1_APPEND_ALIGNED_ELEMENT;
			
				/// <summary>
				/// 
				/// </summary>
				literal float CA_D2D1_DEFAULT_FLATTENING_TOLERANCE = D2D1_DEFAULT_FLATTENING_TOLERANCE;
			
				/// <summary>
				/// 
				/// </summary>
				literal UInt32 CA_D2D1_INVALID_PROPERTY_INDEX = D2D1_INVALID_PROPERTY_INDEX;
				
				/// <summary>
				/// 
				/// </summary>
				literal float CA_D2D1_SCENE_REFERRED_SDR_WHITE_LEVEL = D2D1_SCENE_REFERRED_SDR_WHITE_LEVEL;
			};




			/////////////////////////////////////////
			// WIC - WINDOWS IMAGING COMPONENT API //
			/////////////////////////////////////////

			/// <summary> 
			/// (IWICJpegFrameDecode)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WIC_IWICJpegFrameDecode
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte das contantes originais.
				/// </summary>
				Zero = 0x0,



				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_MAX_COMPONENT_COUNT = 4,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_MAX_TABLE_INDEX = 3,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_SAMPLE_FACTORS_ONE = 0x11,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_SAMPLE_FACTORS_THREE_420 = 0x111122,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_SAMPLE_FACTORS_THREE_422 = 0x111121,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_SAMPLE_FACTORS_THREE_440 = 0x111112,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_SAMPLE_FACTORS_THREE_444 = 0x111111,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_QUANTIZATION_BASELINE_ONE = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_QUANTIZATION_BASELINE_THREE = 0x10100,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_HUFFMAN_BASELINE_ONE = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_WIC_JPEG_HUFFMAN_BASELINE_THREE = 0x111100
			};

			/// <summary> 
			/// (IWICDevelopRawNotificationCallback)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WIC_IWICDevelopRawNotificationCallback
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte das contantes originais.
				/// </summary>
				Zero = 0x0,



				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_ExposureCompensation = 0x00000001,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_NamedWhitePoint = 0x00000002,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_KelvinWhitePoint = 0x00000004,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_RGBWhitePoint = 0x00000008,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Contrast = 0x00000010,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Gamma = 0x00000020,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Sharpness = 0x00000040,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Saturation = 0x00000080,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Tint = 0x00000100,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_NoiseReduction = 0x00000200,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_DestinationColorContext = 0x00000400,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_ToneCurve = 0x00000800,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_Rotation = 0x00001000,
				/// <summary>
				/// 
				/// </summary>
				CA_WICRawChangeNotification_RenderMode = 0x00002000
			};




			////////////////////////////////////////
			// CORE AUDIO - WASAPI / MMDEVICE API //
			////////////////////////////////////////

			/// <summary> 
			/// (AUDCLNT_STREAMFLAGS_XXX)(FALTA DOCUMENTAR) - Constantes que especificam características que um cliente pode atribuir a um fluxo de áudio durante a inicialização do fluxo.
			/// </summary>
			public enum class CA_CoreAudio_AUDCLNT_STREAMFLAGS_XXX : Int64
			{

				CA_AUDCLNT_STREAMFLAGS_CROSSPROCESS = AUDCLNT_STREAMFLAGS_CROSSPROCESS,

				CA_AUDCLNT_STREAMFLAGS_LOOPBACK = AUDCLNT_STREAMFLAGS_LOOPBACK,

				CA_AUDCLNT_STREAMFLAGS_EVENTCALLBACK = AUDCLNT_STREAMFLAGS_EVENTCALLBACK,

				CA_AUDCLNT_STREAMFLAGS_NOPERSIST = AUDCLNT_STREAMFLAGS_NOPERSIST,

				CA_AUDCLNT_STREAMFLAGS_RATEADJUST = AUDCLNT_STREAMFLAGS_RATEADJUST,

				CA_AUDCLNT_STREAMFLAGS_PREVENT_LOOPBACK_CAPTURE = 0x01000000,

				CA_AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM = AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM,

				CA_AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY = AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY
			};

			/// <summary> 
			/// (AUDCLNT_STREAMFLAGS_XXX)(FALTA DOCUMENTAR) - Constantes que indicam características de uma sessão de áudio associada ao fluxo. Um cliente pode especificar essas opções durante a inicialização do fluxo através do parâmetro StreamFlags do método ICarenAudioClient::Inicializar.
			/// </summary>
			public enum class  CA_CoreAudio_AUDCLNT_SESSIONFLAGS_XXX
			{

				CA_AUDCLNT_SESSIONFLAGS_EXPIREWHENUNOWNED= AUDCLNT_SESSIONFLAGS_EXPIREWHENUNOWNED,

				CA_AUDCLNT_SESSIONFLAGS_DISPLAY_HIDE = AUDCLNT_SESSIONFLAGS_DISPLAY_HIDE,

				CA_AUDCLNT_SESSIONFLAGS_DISPLAY_HIDEWHENEXPIRED = AUDCLNT_SESSIONFLAGS_DISPLAY_HIDEWHENEXPIRED
			};

			/////////////////
			// WINDOWS API //
			/////////////////

			/// <summary>
			/// (ORIGINAL) - Essa estrutura contém valores do registro que definem o nome da Task para o método
			/// AvSetMmThreadCharacteristicsW.
			/// </summary>
			public value struct CA_Windows_MMCSS_Multimedia_Name_Tasks
			{
				literal String^ Audio = "Audio";

				literal String^ Capture = "Capture";

				literal String^ Distribution = "Distribution";

				literal String^ Games = "Games";

				literal String^ Playback = "Playback";

				literal String^ Pro_Audio = "Pro Audio";

				literal String^ Window_Manager = "Window Manager";
			};
		}

		//Namespace que contém todas as enumerações utilizadas pela diversas APIs presentes.
		namespace Enumeracoes
		{

			/// <summary>
			/// (Original)(Constantes) - Enumera bandeiras que fazem referência as constante de direito de acesso genéricos a recursos.
			/// Você pode usar direitos de acesso genéricos para especificar o tipo de acesso que você precisa quando estiver abrindo uma Handle para um objeto. 
			/// Isso é tipicamente mais simples do que especificar todos os direitos padrão e específicos correspondentes.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_ACCESS_RIGHTS : Int64
			{
				/// <summary>
				/// (GENERIC_READ) - tem o direito de acesso a ler.
				/// </summary>
				CA_ACR_GENERIC_READ = GENERIC_READ,

				/// <summary>
				/// (GENERIC_WRITE) - Tem o direito de acesso de escrever.
				/// </summary>
				CA_ACR_GENERIC_WRITE = GENERIC_WRITE,

				/// <summary>
				/// (GENERIC_EXECUTE) - Tem o direito de acesso de executar.
				/// </summary>
				CA_ACR_GENERIC_EXECUTE = GENERIC_EXECUTE,

				/// <summary>
				/// (GENERIC_ALL) - Todos os direitos de acesso possíveis
				/// </summary>
				CA_ACR_GENERIC_ALL = GENERIC_ALL,
			};
			
			/// <summary>
			/// (_MF_ATTRIBUTES_MATCH_TYPE) - Especifica como comparar os atributos em dois objetos.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_ATTRIBUTES_MATCH_TYPE
			{
				/// <summary>
				/// Verifique se todos os atributos da (Interface Atual) existem na (Interface No Parametro) e se possuem
				/// os mesmos dados, onde a (Interface Atual) é quem está chamando o método (Compare) e a (Interface No Parametro)
				/// é o objeto passado no parametro.
				/// </summary>
				MF_ATTRIBUTES_MATCH_OUR_ITEMS = 0,

				/// <summary>
				/// Verifique se todos os atributos da (Interface No Parametro) existem na (Interface Atual) e se possuem
				/// os mesmos dados, onde a (Interface Atual) é quem está chamando o método (Compare) e a (Interface No Parametro)
				/// é o objeto passado no parametro.
				/// </summary>
				MF_ATTRIBUTES_MATCH_THEIR_ITEMS,

				/// <summary>
				/// Verifique se ambos os objetos têm atributos idênticos com os mesmos dados.
				/// </summary>
				MF_ATTRIBUTES_MATCH_ALL_ITEMS,

				/// <summary>
				/// Verifique se os atributos que existem em ambos os objetos têm os mesmos dados.
				/// </summary>
				MF_ATTRIBUTES_MATCH_INTERSECTION,

				/// <summary>
				/// Localize o objeto com o menor número de atributos e verifique se esses atributos existem no 
				/// outro objeto e têm os mesmos dados.
				/// </summary>
				MF_ATTRIBUTES_MATCH_SMALLER
			};

			/// <summary>
			/// (tagSTATFLAG) - Os valores de enumeração indicam se o método deve tentar retornar um nome no membro pwcsName da estrutura CA_STATSTG. Os valores são usados nos 
			/// métodos ICarenStream::Stat métodos para salvar a memória quando o membro do nome pwcs não for necessário.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_STATFLAG
			{
				CA_STATFLAG_DEFAULT = 0,

				CA_STATFLAG_NONAME = 1,

				CA_STATFLAG_NOOPEN = 2
			};
			
			/// <summary>
			/// (ORIGINAL) - Enumera flags que são utilizadas por uma matriz segura(SAFEARRAY) que descreve os tipos de matrizes
			/// que a estrutura contém.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_FADF_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// Uma matriz que está alocada na Stack.
				/// </summary>
				CA_FADF_AUTO = 0x1,

				/// <summary>
				/// Uma matriz que está estaticamente alocada.
				/// </summary>
				CA_FADF_STATIC = 0x02,

				/// <summary>
				/// Uma matriz que está embutida em uma estrutura.
				/// </summary>
				CA_FADF_EMBEDDED = 0x04,

				/// <summary>
				/// Uma matriz que pode não ser redimensionada ou realocada.
				/// </summary>
				CA_FADF_FIXEDSIZE = 0x10,

				/// <summary>
				/// Uma matriz que contém registros. Quando definido, haverá um ponteiro para a interface IRecordInfo com deslocamento negativo 4 no descritor de matriz.
				/// </summary>
				CA_FADF_RECORD = 0x20,

				/// <summary>
				/// Uma matriz que tem uma interface de identificação IID. Quando definido, haverá um GUID em deslocamento negativo 16 no descritor de matriz segura. A bandeira é definida somente quando FADF_DISPATCH ou FADF_UNKNOWN também é definida.
				/// </summary>
				CA_FADF_HAVEIID = 0x40,

				/// <summary>
				/// Uma matriz que tem um tipo de variante.
				/// </summary>
				CA_FADF_HAVEVARTYPE = 0x80,

				/// <summary>
				/// Uma matriz de BSTRs.
				/// </summary>
				CA_FADF_BSTR = 0x100,

				/// <summary>
				/// Uma matriz de interfaces IUnknown representadas como ICaren.
				/// </summary>
				CA_FADF_UNKNOWN = 0x200,

				/// <summary>
				/// Uma matriz de interfaces IDispatch representadas como ICaren.
				/// </summary>
				CA_FADF_DISPATCH = 0x400,

				/// <summary>
				/// Uma matriz de variantes.
				/// </summary>
				CA_FADF_VARIANT = 0x800,

				/// <summary>
				/// Bits reservados para uso futuro.
				/// </summary>
				CA_FADF_RESERVED = 0xf008
			};

			/// <summary>
			/// (tagLOCKTYPE) - Enumera os tipos de bloqueio solicitado para a faixa especificada de bytes. Os valores são usados nos métodos ICarenStream::LockRegion.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_LOCKTYPE
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0,

				CA_LOCK_WRITE = 1,

				CA_LOCK_EXCLUSIVE = 2,

				CA_LOCK_ONLYONCE = 4
			};
			
			/// <summary>
			/// (tagSTGC) - Enumera constantes que especificam as condições para realizar a operação de (Commit) no método ICarenStream::Commit.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_STGC
			{
				CA_STGC_DEFAULT = 0,

				CA_STGC_OVERWRITE = 1,

				CA_STGC_ONLYIFCURRENT = 2,

				CA_STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4,

				CA_STGC_CONSOLIDATE = 8
			};
		
			/// <summary>
			/// (tagSTREAM_SEEK) - Enumera valores que especificam a origem a partir da qual calcular o novo local de ponto de busca. Eles são usados para o parâmetro (Param_Origem) 
			/// no método ICarenStream::Seek. A nova posição de busca é calculada usando esse valor e o parâmetro (Param_Deslocamento).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_STREAM_SEEK
			{
				CA_STREAM_SEEK_SET = 0,

				CA_STREAM_SEEK_CUR = 1,

				CA_STREAM_SEEK_END = 2
			};
			
			/// <summary>
			/// (tagSTGTY) - Enumera valoresque  são usados no tipo membro da estrutura CA_STATSTG para indicar o tipo do elemento de armazenamento. Um elemento de armazenamento 
			/// é um objeto de armazenamento, um objeto de fluxo ou um objeto de byte-array (LOCKBYTES).
			/// </summary>
			public enum class CA_STGTY
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0,

				CA_STGTY_STORAGE = 1,

				CA_STGTY_STREAM = 2,

				CA_STGTY_LOCKBYTES = 3,

				CA_STGTY_PROPERTY = 4
			};

			/// <summary>
			/// Enumera valores que especificam a tabela de codificação de uma String.
			/// </summary>
			public enum class CA_STRING_ENCODE
			{
				/// <summary>
				/// Vai alocar ou conver para a tabela de codificação ANSI.
				/// </summary>
				ANSI,

				/// <summary>
				/// Vai alocar ou conver para a tabela de codificação Unicode.
				/// </summary>
				Unicode,

				/// <summary>
				/// Vai alocar ou conver para a tabela de codificação UTF8.
				/// </summary>
				UTF8
			};
			
			/// <summary>
			/// (eAVDecDDStereoDownMixMode) - Enumera valores do modo downmix estéreo para um decodificador de áudio Dolby Digital. Esta enumeração é usada com a propriedade CODECAPI_AVDecDDStereoDownMixMode.			
			/// </summary>
			public enum class CA_eAVDecDDStereoDownMixMode
			{
				/// <summary>
				/// 
				/// </summary>
				eAVDecDDStereoDownMixMode_Auto = 0,
				/// <summary>
				/// 
				/// </summary>
				eAVDecDDStereoDownMixMode_LtRt = 1,
				/// <summary>
				/// 
				/// </summary>
				eAVDecDDStereoDownMixMode_LoRo = 2 
			};

			/// <summary>
			/// (ORIGINAL) - Especifica o Resultado de uma comparação das interfaces: ICarenMFMediaType
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_MEDIATYPE_EQUAL
			{
				/// <summary>
				/// Os tipos principais são os mesmos. O tipo principal é especificado 
				/// pelo atributo MF_MT_MAJOR_TYPE .
				/// </summary>
				CA_MF_MEDIATYPE_EQUAL_MAJOR_TYPES = 0x00000001,

				/// <summary>
				/// Os subtipos são iguais, ou nenhum tipo de mídia tem um subtipo. 
				/// O subtipo é especificado pelo atributo MF_MT_SUBTYPE.
				/// </summary>
				CA_MF_MEDIATYPE_EQUAL_FORMAT_TYPES = 0x00000002,

				/// <summary>
				/// Especificamente, o método usa o tipo de mídia com o menor número de atributos e 
				/// verifica se cada atributo desse tipo está presente no outro tipo de mídia e tem o 
				/// mesmo valor (não incluindo MF_MT_USER_DATA, MF_MT_FRAME_RATE_RANGE_MIN, e MF_MT_FRAME_RATE_RANGE_MAX).
				/// </summary>
				CA_MF_MEDIATYPE_EQUAL_FORMAT_DATA = 0x00000004,

				/// <summary>
				/// Os dados do usuário são idênticos ou nenhum tipo de mídia contém dados do usuário. Dados do usuário são 
				/// especificados pelo atributo MF_MT_USER_DATA.
				/// </summary>
				CA_MF_MEDIATYPE_EQUAL_FORMAT_USER_DATA = 0x00000008
			};

			/// <summary>
			/// (MF_ATTRIBUTE_SERIALIZE_OPTIONS) - Enumera valores que definem bandeiras para serializar e deseralizar lojas de atributos.
			/// </summary>	
			public enum class CA_MF_ATTRIBUTE_SERIALIZE_OPTIONS
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Se esta bandeira estiver definida, os ponteiros IUnknown na loja de atributos ão empacotados de e para o fluxo. Se esta bandeira 
				/// estiver ausente, os ponteiros IUnknown na loja de atributos não ão empacotados ou serializados.
				/// </summary>
				MF_ATTRIBUTE_SERIALIZE_UNKNOWN_BYREF = 0x1
			};
			
			/// <summary>
			/// (_MF_ATTRIBUTE_TYPE) - Enumera valores que definem o tipo de dados para (Emparelhar) uma Chave/Valor.
			/// </summary>
			public enum class CA_MF_ATTRIBUTE_TYPE
			{
				/// <summary>
				/// Valor inteiro não assinado de 32 Bits.
				/// </summary>
				MF_ATTRIBUTE_UINT32 = VT_UI4,

				/// <summary>
				/// Valor inteiro não assinado de 64 Bits.
				/// </summary>
				MF_ATTRIBUTE_UINT64 = VT_UI8,

				/// <summary>
				/// Número de ponto flutuante.
				/// </summary>
				MF_ATTRIBUTE_DOUBLE = VT_R8,

				/// <summary>
				/// Representa um GUID.
				/// </summary>
				MF_ATTRIBUTE_GUID = VT_CLSID,

				/// <summary>
				/// Sequência de caracteres largos terminada por caractere nulo.
				/// </summary>
				MF_ATTRIBUTE_STRING = VT_LPWSTR,

				/// <summary>
				/// Matriz de byte.
				/// </summary>
				MF_ATTRIBUTE_BLOB = (VT_VECTOR | VT_UI1),

				/// <summary>
				/// Ponteiro desconhecido para um objeto.
				/// </summary>
				MF_ATTRIBUTE_IUNKNOWN = VT_UNKNOWN
			};

			/// <summary>
			/// (ORIGINAL) - Enumera valores que definem com será a inicialização e criação da interface (ICarenMFQualityManager).
			/// </summary>
			public enum class CA_MF_QUALITY_MANAGER_CREATE_TYPE
			{
				/// <summary>
				/// Indica que deve inicializar a classe mais não associar nenhum ponteiro a ela.
				/// </summary>
				MF_NULL = 0x0,

				/// <summary>
				/// Inidica que vai inicializar e criar um ponteiro default para o gerenciador de qualidade através do método (MFCreateStandardQualityManager ).
				/// </summary>
				MF_CREATE_TYPE_STANDARD,

				/// <summary>
				/// Inidica que vai inicializar e criar um ponteiro interno gerenciado pela biblioteca para receber eventos da interface.
				/// </summary>
				MF_CREATE_TYPE_INTERNAL
			};
			
			/// <summary>
			/// (MFPMPSESSION_CREATION_FLAGS) - Enumera bandeiras que definem o comportamento da função MFCreatePMPMediaSession e MFCreatePMPServer.
			/// </summary>
			public enum class CA_MFPMPSESSION_CREATION_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte das contantes originais.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Se essa bandeira estiver definida, a Sessão de Mídia do Caminho de Mídia Protegida (PMP) será criada em um processo desprotegido. Você pode usar o processo desprotegido para reproduzir conteúdo claro, 
				/// mas não protegido. Se essa bandeira não for definida, a Sessão de Mídia PMP será criada em um processo protegido. Nesse caso, o processo protegido é usado para conteúdo protegido e conteúdo claro.
				/// </summary>
				MFPMPSESSION_UNPROTECTED_PROCESS = 0x1,

				/// <summary>
				/// NÃO POSSUI DOCUMENTAÇÃO.
				/// </summary>
				MFPMPSESSION_IN_PROCESS = 0x2
			};
			
			/// <summary>
			/// (MF_FILE_ACCESSMODE) - Enumera valores que são utilizados para especificar o modo de acesso durante a abertura de um arquivo.
			/// </summary>
			public enum class CA_MF_FILE_ACCESSMODE
			{
				/// <summary>
				/// Modo de leitura.
				/// </summary>
				MF_ACCESSMODE_READ = 1,

				/// <summary>
				/// Modo de gravação.
				/// </summary>
				MF_ACCESSMODE_WRITE = 2,

				/// <summary>
				/// Modo de leitura e gravação.
				/// </summary>
				MF_ACCESSMODE_READWRITE = 3
			};
	
			/// <summary>
			/// (CA_MF_FILE_OPENMODE) - Enumera valores que especificam como abrir ou criar um arquivo.
			/// </summary>
			public enum class CA_MF_FILE_OPENMODE
			{
				/// <summary>
				/// Abra um arquivo existente. Falha se o arquivo não existir.
				/// </summary>
				MF_OPENMODE_FAIL_IF_NOT_EXIST = 0,

				/// <summary>
				/// Crie um novo arquivo. Falha se o arquivo já existir.
				/// </summary>
				MF_OPENMODE_FAIL_IF_EXIST = 1,

				/// <summary>
				/// Abra um arquivo existente e trunque-o, de modo que o tamanho seja zero bytes. Falha se o arquivo ainda não existir.
				/// </summary>
				MF_OPENMODE_RESET_IF_EXIST = 2,

				/// <summary>
				/// Se o arquivo não existir, crie um novo arquivo. Se o arquivo existir, abra-o.
				/// </summary>
				MF_OPENMODE_APPEND_IF_EXIST = 3,

				/// <summary>
				/// Crie um novo arquivo. Se o arquivo existir, substitua o arquivo.
				/// </summary>
				MF_OPENMODE_DELETE_IF_EXIST = 4
			};
			
			/// <summary>
			/// (MF_FILE_FLAGS) - Enumera valores que especificam o comportamento ao abrir um arquivo.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_FILE_FLAGS
			{
				/// <summary>
				/// Use o comportamento padrão.
				/// </summary>
				MF_FILEFLAGS_NONE = 0,

				/// <summary>
				/// Abra o arquivo sem cache de sistema.
				/// </summary>
				MF_FILEFLAGS_NOBUFFERING = 0x1,

				/// <summary>
				/// Operações abertas subsequentes podem ter acesso à gravação ao arquivo.
				/// </summary>
				MF_FILEFLAGS_ALLOW_WRITE_SHARING = 0x2
			};

			/// <summary>
			/// (ORIGINAL)(FALTA DOCUMENTAR) - Enumera valores que especificam o alinhamento de memória para um buffer.
			/// </summary>
			public enum class CA_MF_BYTE_ALIGNMENT
			{
				/// <summary>
				/// 
				/// </summary>
				CA_MF_1_BYTE_ALIGNMENT = 0x00000000,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_2_BYTE_ALIGNMENT = 0x00000001,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_4_BYTE_ALIGNMENT = 0x00000003,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_8_BYTE_ALIGNMENT = 0x00000007,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_16_BYTE_ALIGNMENT = 0x0000000f,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_32_BYTE_ALIGNMENT = 0x0000001f,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_64_BYTE_ALIGNMENT = 0x0000003f,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_128_BYTE_ALIGNMENT = 0x0000007f,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_256_BYTE_ALIGNMENT = 0x000000ff,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_512_BYTE_ALIGNMENT = 0x000001ff,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_1024_BYTE_ALIGNMENT = 0x000003ff,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_2048_BYTE_ALIGNMENT = 0x000007ff,
				/// <summary>
				/// 
				/// </summary>
				CA_MF_4096_BYTE_ALIGNMENT = 0x00000fff
			};
		
			/// <summary>
			/// (VARTYPE) - Enumera valores que especificam o tipo de dados que está armazenado na PROPVARIANT.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_VARTYPE
			{
				/// <summary>
				/// 
				/// </summary>
				VT_EMPTY = 0,
				/// <summary>
				/// Tipo: 
				/// Armazena dados na variavel: 
				/// </summary>
				VT_NULL = 1,
				/// <summary>
				/// Tipo: 
				/// </summary>
				VT_I2 = 2,
				/// <summary>
				/// Tipo: 
				/// </summary>
				VT_I4 = 3,
				/// <summary>
				/// 
				/// </summary>
				VT_R4 = 4,
				/// <summary>
				/// 
				/// </summary>
				VT_R8 = 5,
				/// <summary>
				/// 
				/// </summary>
				VT_CY = 6,
				/// <summary>
				/// 
				/// </summary>
				VT_DATE = 7,
				/// <summary>
				/// 
				/// </summary>
				VT_BSTR = 8,
				/// <summary>
				/// Tipo: IDispatch NATIVAMENTE. A biblioteca ler como IntPtr.
				/// </summary>
				VT_DISPATCH = 9,
				/// <summary>
				/// 
				/// </summary>
				VT_ERROR = 10,
				/// <summary>
				/// Tipo: SHORT NATIVAMENTE. A biblioteca ler como Boolean.
				/// </summary>
				VT_BOOL = 11,
				/// <summary>
				/// Tipo: CA_VARIANT
				/// </summary>
				VT_VARIANT = 12,
				/// <summary>
				/// Tipo: IUnkown NATIVAMENTE. A biblioteca ler como IntPtr.
				/// </summary>
				VT_UNKNOWN = 13,
				/// <summary>
				/// Tipo: CA_DEC
				/// </summary>
				VT_DECIMAL = 14,
				/// <summary>
				/// 
				/// </summary>
				VT_I1 = 16,
				/// <summary>
				/// 
				/// </summary>
				VT_UI1 = 17,
				/// <summary>
				/// 
				/// </summary>
				VT_UI2 = 18,
				/// <summary>
				/// 
				/// </summary>
				VT_UI4 = 19,
				/// <summary>
				/// 
				/// </summary>
				VT_I8 = 20,
				/// <summary>
				/// 
				/// </summary>
				VT_UI8 = 21,
				/// <summary>
				/// 
				/// </summary>
				VT_INT = 22,
				/// <summary>
				/// 
				/// </summary>
				VT_UINT = 23,
				/// <summary>
				/// 
				/// </summary>
				VT_VOID = 24,
				/// <summary>
				/// 
				/// </summary>
				VT_HRESULT = 25,
				/// <summary>
				/// 
				/// </summary>
				VT_PTR = 26,
				/// <summary>
				/// 
				/// </summary>
				VT_SAFEARRAY = 27,
				/// <summary>
				/// 
				/// </summary>
				VT_CARRAY = 28,
				/// <summary>
				/// 
				/// </summary>
				VT_USERDEFINED = 29,
				/// <summary>
				/// 
				/// </summary>
				VT_LPSTR = 30,
				/// <summary>
				/// 
				/// </summary>
				VT_LPWSTR = 31,
				/// <summary>
				/// 
				/// </summary>
				VT_RECORD = 36,
				/// <summary>
				/// 
				/// </summary>
				VT_INT_PTR = 37,
				/// <summary>
				/// 
				/// </summary>
				VT_UINT_PTR = 38,
				/// <summary>
				/// 
				/// </summary>
				VT_FILETIME = 64,
				/// <summary>
				/// 
				/// </summary>
				VT_BLOB = 65,
				/// <summary>
				/// 
				/// </summary>
				VT_STREAM = 66,
				/// <summary>
				/// 
				/// </summary>
				VT_STORAGE = 67,
				/// <summary>
				/// 
				/// </summary>
				VT_STREAMED_OBJECT = 68,
				/// <summary>
				/// 
				/// </summary>
				VT_STORED_OBJECT = 69,
				/// <summary>
				/// 
				/// </summary>
				VT_BLOB_OBJECT = 70,
				/// <summary>
				/// 
				/// </summary>
				VT_CF = 71,
				/// <summary>
				/// 
				/// </summary>
				VT_CLSID = 72,
				/// <summary>
				/// 
				/// </summary>
				VT_VERSIONED_STREAM = 73,
				/// <summary>
				/// 
				/// </summary>
				VT_BSTR_BLOB = 0xfff,
				/// <summary>
				/// 
				/// </summary>
				VT_VECTOR = 0x1000,
				/// <summary>
				/// 
				/// </summary>
				VT_ARRAY = 0x2000,
				/// <summary>
				/// 
				/// </summary>
				VT_BYREF = 0x4000,
				/// <summary>
				/// 
				/// </summary>
				VT_RESERVED = 0x8000,
				/// <summary>
				/// 
				/// </summary>
				VT_ILLEGAL = 0xffff,
				/// <summary>
				/// 
				/// </summary>
				VT_ILLEGALMASKED = 0xfff,
				/// <summary>
				/// 
				/// </summary>
				VT_TYPEMASK = 0xfff
			};

			/// <summary>
			/// Enumera o (Tipos Principais) de mídia. Essa biblioteca suporta apenas: Áudio e Vídeo. 
			/// </summary>
			public enum class CA_MAJOR_MEDIA_TYPES
			{

				/// <summary>
				/// Indica que o tipo principal da midia é: Áudio.
				/// </summary>
				TP_Audio = 0,

				/// <summary>
				/// Indica que o tipo principal da midia é: Vídeo.
				/// </summary>
				TP_Video,

				/// <summary>
				/// Indica que o tipo principal da mídia não é reconhecido pela biblioteca.
				/// Está biblioteca suporta apenas Áudio e Vídeo.
				/// </summary>
				TP_Desconhecido,
			};

			/// <summary>
			/// Enumera o (Subtipo) de mídia. Subtipo contém o formato do tipo principal.
			/// Essa enumeração só contém os subtipos dos (Tipos Principais) suportados por essa biblioteca.
			/// </summary>
			public enum class CA_MEDIA_SUBTYPES
			{

				//Essa parte contém os formatios de Áudio.

				/// <summary>
				/// Codificação avançada de áudio (AAC).
				/// Esse subtipo é usado para AAC contido em um arquivo AVI com uma marca de formato de áudio igual a 0x00FF.
				/// Código FOURCC: WAVE_FORMAT_RAW_AAC1 (0x00FF)
				///</summary>
				MFAudioFormat_RAW_ACC1 = 0,

				/// <summary>
				/// Codificação avançada de áudio (AAC).
				/// Nota: Equivalente a MEDIASUBTYPE_MPEG_HEAAC
				/// Código FOURCC: WAVE_FORMAT_MPEG_HEAAC (0x1610)
				/// </summary>
				MFAudioFormat_AAC,

				/// <summary>
				/// Apple Lossless Codec de áudio
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_ALAC (0x6C61)
				/// </summary>
				MFAudioFormat_ALAC,

				/// <summary>
				/// Adaptativo multi-taxa de áudio
				/// (Com suporte no Windows 8.1 e posterior)
				/// Código FOURCC: WAVE_FORMAT_AMR_NB
				/// </summary>
				MFAudioFormat_AMR_NB,

				/// <summary>
				/// Adaptativo multi-taxa de banda larga de áudio
				/// (Com suporte no Windows 8.1 e posterior)
				/// Código FOURCC: WAVE_FORMAT_AMR_WB
				/// </summary>
				MFAudioFormat_AMR_WB,

				/// <summary>
				/// (Com suporte no Windows 8.1 e posterior)
				/// Código FOURCC: WAVE_FORMAT_AMR_WP
				/// </summary>
				MFAudioFormat_AMR_WP,

				/// <summary>
				/// Dolby Digital (AC-3).
				/// Mesmo valor GUID como MEDIASUBTYPE_DOLBY_AC3.
				/// Código FOURCC: Nenhum.
				/// </summary>
				MFAudioFormat_Dolby_AC3,

				/// <summary>
				/// Áudio Dolby AC-3 através da interface digital Sony/Philips (S/PDIF).
				/// Código FOURCC: WAVE_FORMAT_DOLBY_AC3_SPDIF (0x0092)
				/// </summary>
				MFAudioFormat_Dolby_AC3_SPDIF,

				/// <summary>
				/// Dolby Digital Plus.
				/// Código FOURCC: Nenhum
				/// </summary>
				MFAudioFormat_Dolby_DDPlus,

				/// <summary>
				/// Dados de áudio criptografados usados com o caminho de áudio seguro.
				/// Código FOURCC: WAVE_FORMAT_DRM (0x0009)
				/// </summary>
				MFAudioFormat_DRM,

				/// <summary>
				///	Digital Theater Systems (DTS) de áudio.
				/// Código FOURCC: WAVE_FORMAT_DTS (0x0008)
				/// </summary>
				MFAudioFormat_DTS,

				/// <summary>
				/// Free Lossless Codec de áudio
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_FLAC (0xF1AC)
				/// </summary>
				MFAudioFormat_FLAC,

				/// <summary>
				/// Áudio de ponto flutuante IEEE descompactado.
				///  Código FOURCC: WAVE_FORMAT_IEEE_FLOAT (0x0003)
				/// </summary>
				MFAudioFormat_Float,

				/// <summary>
				/// Áudio de ponto flutuante IEEE descompactado.
				///  Código FOURCC: Nenhum
				/// </summary>
				MFAudioFormat_Float_SpatialObjects,

				/// <summary>
				/// MPEG Audio Layer-3 (MP3).
				/// Código FOURCC: WAVE_FORMAT_MPEGLAYER3 (0x0055)
				/// </summary>
				MFAudioFormat_MP3,

				/// <summary>
				/// Payload de áudio MPEG-1.
				/// Código FOURCC: WAVE_FORMAT_MPEG (0x0050)
				/// </summary>
				MFAudioFormat_MPEG,

				/// <summary>
				/// Codec de voz do Windows Media Audio 9.
				/// Código FOURCC: WAVE_FORMAT_WMAVOICE9 (0x000A)
				/// </summary>
				MFAudioFormat_MSP1,

				/// <summary>
				/// Opus
				/// (Com suporte no Windows 10 e posterior)
				/// Código FOURCC: WAVE_FORMAT_OPUS (0x704F)
				/// </summary>
				MFAudioFormat_Opus,

				/// <summary>
				/// Áudio PCM descompactado.
				/// Código FOURCC: WAVE_FORMAT_PCM (1)
				/// </summary>
				MFAudioFormat_PCM,

				/// <summary>
				/// QCELP (Qualcomm Code excitação linear Prediction) de áudio.
				/// Nota: Não disponivel nessa plataforma.
				/// Código FOURCC: Nenhum
				/// </summary>
				MFAudioFormat_QCELP,

				/// <summary>
				/// Windows Media Audio 9 Professional codec sobre S/PDIF.
				/// Código FOURCC: WAVE_FORMAT_WMASPDIF (0x0164)
				/// </summary>
				MFAudioFormat_WMASPDIF,

				/// <summary>
				/// Windows Media Audio 9 Lossless Codec ou Windows Media Audio 9.1 Codec.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO_LOSSLESS (0x0163)
				/// </summary>
				MFAudioFormat_WMAudio_Lossless,

				/// <summary>
				/// Codec do Windows Media Audio 8, codec do Windows Media Audio 9 ou codec 
				/// de 9.1 do Windows Media Audio.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO2 (0x0161)
				/// </summary>
				MFAudioFormat_WMAudioV8,

				/// <summary>
				/// Codec Windows Media Audio 9 Professional ou codec Windows Media Audio 9.1 Professional.
				/// Código FOURCC: WAVE_FORMAT_WMAUDIO3 (0x0162)
				/// </summary>
				MFAudioFormat_WMAudioV9,

				/// <summary>
				/// Não é usado.
				/// Código FOURCC: WAVE_FORMAT_DTS (0x0008)
				/// </summary>
				MFAudioFormat_ADTS,



				//Essa parte contém os formatos de Vídeo.



				//Tipos RGB Descompactados.


				/// <summary>
				/// (RBG - Descompactado) - RGB, 8 bits por pixel (BPP). (Layout da mesma memória como D3DFMT_P8.)
				/// </summary>
				MFVideoFormat_RGB8,

				/// <summary>
				/// (RBG - Descompactado) - RGB 555, 16 BPP. (Layout da mesma memória como D3DFMT_X1R5G5B5).
				/// </summary>
				MFVideoFormat_RGB555,

				/// <summary>
				/// (RBG - Descompactado) - RGB 565, 16 BPP. (Layout da mesma memória como D3DFMT_R5G6B5).
				/// </summary>
				MFVideoFormat_RGB565,

				/// <summary>
				/// (RBG - Descompactado) - RGB, 24 bpp.
				/// </summary>
				MFVideoFormat_RGB24,

				/// <summary>
				/// (RBG - Descompactado) - RGB, 32 bpp.
				/// </summary>
				MFVideoFormat_RGB32,

				/// <summary>
				/// (RBG - Descompactado) - RGB, 32 bpp com canal alfa.
				/// </summary>
				MFVideoFormat_ARGB32,

				/// <summary>
				/// (RBG - Descompactado) - RGB, 10 bpp para cada cor e 2 bpp para Alpha. (Layout da mesma 
				/// memória como D3DFMT_A2B10G10R10).
				/// </summary>
				MFVideoFormat_A2R10G10B10,

				/// <summary>
				/// (RBG - Descompactado) - RGB, 16 bpp com canal alfa. (Layout da mesma memória como 
				/// D3DFMT_A16B16G16R16F).
				/// </summary>
				MFVideoFormat_A16B16G16R16F,


				//Tipos YUV de 8 Bits e (Palettized - apenas o primeiro)


				/// <summary>
				/// (YUV - Palettized) - Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_AI44,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_AYUV,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_I420,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_IYUV,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:1:1 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_NV11,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_NV12,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_UYVY,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:1:1 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_Y41P,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:1:1 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y41T,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y42T,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_YUY2,

				/// <summary>
				/// (YUV - 9 Bits) - Amostragem: 8:4:4 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_YVU9,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_YV12,

				/// <summary>
				/// (YUV - 8 Bits) - Amostragem: 4:2:0 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_YVYU,



				//Tipos YUV de: 10 Bits e 16 Bits.


				/// <summary>
				/// (YUV - 10 Bits) Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_P010,

				/// <summary>
				/// (YUV - 16 Bits) Amostragem: 4:2:0 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_P016,

				/// <summary>
				/// (YUV - 10 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_P210,

				/// <summary>
				/// (YUV - 16 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Planar
				/// </summary>
				MFVideoFormat_P216,

				/// <summary>
				/// (YUV - 10 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_v210,

				/// <summary>
				/// (YUV - 16 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_v216,

				/// <summary>
				/// (YUV - 10 Bits) Formato: v40 | Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_v410,

				/// <summary>
				/// (YUV - 10 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y210,

				/// <summary>
				/// (YUV - 16 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y216,

				/// <summary>
				/// (YUV - 10 Bits) Formato: Y40 | Amostragem: 4:4:4 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y410,

				/// <summary>
				/// (YUV - 16 Bits) Amostragem: 4:2:2 | Embalado ou Planar? Embalado
				/// </summary>
				MFVideoFormat_Y416,




				//Formatos de Luminância e Profundidade




				/// <summary>
				/// Apenas luminância de 8 bits. (BPP). (Layout da mesma memória como D3DFMT_L8).
				/// </summary>
				MFVideoFormat_L8,

				/// <summary>
				/// Apenas luminância de 16 bits. (Layout da mesma memória como D3DFMT_L16).
				/// </summary>
				MFVideoFormat_L16,

				/// <summary>
				/// Profundidade de buffer de 16 bits z. (Layout da mesma memória como D3DFMT_D16).
				/// </summary>
				MFVideoFormat_D16,




				//Tipos de formato Codificados.



				/// <summary>
				/// DVCPRO 25 (525-60 ou 625-50).
				/// Código FOURCC: 'dv25' 
				/// </summary>
				MFVideoFormat_DV25,

				/// <summary>
				/// DVCPRO 50 (525-60 ou 625-50).
				/// Código FOURCC: 'dv50' 
				/// </summary>
				MFVideoFormat_DV50,

				/// <summary>
				/// DVC/vídeo DV.
				/// Código FOURCC: 'dvc' 
				/// </summary>
				MFVideoFormat_DVC,

				/// <summary>
				/// DVCPRO 100 (1080/60i, 1080/50i ou 720/60P).
				/// Código FOURCC: 'dvh1'
				/// </summary>
				MFVideoFormat_DVH1,

				/// <summary>
				/// HD-DVCR (1125-60 ou 1250-50).
				/// Código FOURCC: 'dvhd'
				/// </summary>
				MFVideoFormat_DVHD,

				/// <summary>
				/// SDL-DVCR (525-60 ou 625-50).
				/// Código FOURCC: 'dvsd'  
				/// </summary>
				MFVideoFormat_DVSD,

				/// <summary>
				/// SD-DVCR (525-60 ou 625-50).
				/// Código FOURCC: 'dvsl' 
				/// </summary>
				MFVideoFormat_DVSL,

				/// <summary>
				/// H. 263 vídeo.
				/// Código FOURCC: 'H263' 
				/// </summary>
				MFVideoFormat_H263,

				/// <summary>
				/// Vídeo H.264. As amostras de mídia contêm dados de Bitstream H.264 com códigos de início e 
				/// têm o SPS / PPS intercalados.Cada amostra contém uma imagem completa, ou um campo ou um quadro.
				/// Código FOURCC: 'H264'  
				/// </summary>
				MFVideoFormat_H264,

				/// <summary>
				/// H.264 fluxo elementar. Esse tipo de mídia é o mesmo que MFVideoFormat_H264, exceto exemplos de
				/// mídia contêm um fluxo de bits H.264 fragmentado. Cada amostra pode conter uma imagem parcial; 
				/// várias imagens completas; ou uma ou mais imagens completas mais uma imagem parcial.
				/// Código FOURCC: Não Aplicável
				/// </summary>
				MFVideoFormat_H264_ES,

				/// <summary>
				/// Vídeo H. 265.
				/// Código FOURCC: 'H265' 
				/// </summary>
				MFVideoFormat_H265,

				/// <summary>
				/// O perfil principal do HEVC e o perfil de imagem imóvel principal.Cada amostra contém uma imagem completa.
				///	Com suporte no Windows 8.1 e posterior.O perfil principal do HEVC e o principal Perfil de imagem ainda de fluxo elementar.
				/// Código FOURCC: 'HEVC'  
				/// </summary>
				MFVideoFormat_HEVC,

				/// <summary>
				/// Esse tipo de mídia é o mesmo que MFVideoFormat_HEVC, exceto amostras de mídia contêm um fluxo de bits 
				/// HEVC fragmentado. Cada amostra pode conter uma imagem parcial; várias imagens completas; ou uma ou mais 
				/// imagens completas mais uma imagem parcial. Com suporte no Windows 8.1 e posterior.
				/// Código FOURCC: 'HEVS'  
				/// </summary>
				MFVideoFormat_HEVC_ES,

				/// <summary>
				/// Vídeo MPEG-4 parte 2.
				/// Código FOURCC: 'M4S2' 
				/// </summary>
				MFVideoFormat_M4S2,

				/// <summary>
				/// Motion JPEG.
				/// Código FOURCC: 'MJPG' 
				/// </summary>
				MFVideoFormat_MJPG,

				/// <summary>
				/// Microsoft MPEG 4 codec versão 3. Esse codec não é mais suportado.
				/// Código FOURCC: 'MP43' 
				/// </summary>
				MFVideoFormat_MP43,

				/// <summary>
				/// ISO MPEG 4 codec versão 1.
				/// Código FOURCC: 'MP4S'	
				/// </summary>
				MFVideoFormat_MP4S,

				/// <summary>
				/// Vídeo MPEG-4 parte 2.
				/// Código FOURCC: 'MP4V'
				/// </summary>
				MFVideoFormat_MP4V,

				/// <summary>
				/// Vídeo MPEG-2.
				/// Código FOURCC: Não Aplicável
				/// </summary>
				MFVideoFormat_MPEG2,

				/// <summary>
				/// VP8 vídeo.
				/// Código FOURCC: 'MPG1'
				/// </summary>
				MFVideoFormat_VP80,

				/// <summary>
				/// VP9 vídeo.
				/// Código FOURCC: 'MPG1'
				/// </summary>
				MFVideoFormat_VP90,

				/// <summary>
				/// Vídeo MPEG-1.
				/// Código FOURCC: 'MPG1'
				/// </summary>
				MFVideoFormat_MPG1,

				/// <summary>
				/// Windows Media Screen codec versão 1.
				/// Código FOURCC: 'MSS1'
				/// </summary>
				MFVideoFormat_MSS1,

				/// <summary>
				/// Windows Media Video 9 Screen codec.
				/// Código FOURCC: 'MSS2'
				/// </summary>
				MFVideoFormat_MSS2,

				/// <summary>
				/// Windows Media Video Codec versão 7.
				/// Código FOURCC:'WMV1'
				/// </summary>
				MFVideoFormat_WMV1,

				/// <summary>
				/// Codec Windows Media Video 8.
				/// Código FOURCC: 'WMV2'
				/// </summary>
				MFVideoFormat_WMV2,

				/// <summary>
				/// Codec Windows Media Video 9.
				/// Código FOURCC:'WMV3'
				/// </summary>
				MFVideoFormat_WMV3,

				/// <summary>
				/// SMPTE 421M ("VC-1").
				/// Código FOURCC: 'WVC1'
				/// </summary>
				MFVideoFormat_WVC1,

				/// <summary>
				/// 8-bit por canal planar YUV 4:2:0 vídeo.
				/// Código FOURCC: '420O'
				/// </summary>
				MFVideoFormat_420O,

				/// <summary>
				/// Formato da mídia é desconhecido.
				/// </summary>
				FormatoMidia_Desconhecido
			};

			/// <summary>
			/// Enumera valores para o resultado de leitura de uma amostra de mídia.
			/// </summary>
			public enum class CA_SAMPLE_READ_RESULT
			{
				/// <summary>
				/// Determina que uma amostra de mídia foi obtida com sucesso.
				/// </summary>
				Sucesso = 0,

				/// <summary>
				/// Determina que um novo fluxo de midia foi adicionado e que é necessário selecionar o fluxo pretendido a ser decodificado novamente.
				/// </summary>
				NovoFluxo,

				/// <summary>
				/// Determina que o tipo(MediaType) foi modificado.
				/// </summary>
				TipoModificado,

				/// <summary>
				/// O formato da mídia (Nativo) foi modificado. O formato nativo é entregue pela fonte de midia antes de qualquer decodificador agir.
				/// </summary>
				TipoNativoModificado,

				/// <summary>
				/// Indica que o decodificador do fluxo foi removido manualmente ou devido alguma modificação no tipo de midia.
				/// </summary>
				DecodificadorRemovido,

				/// <summary>
				/// Determina que não há dados na Sample. Indica que deve ler a proxima Sample.
				/// </summary>
				NoData,

				/// <summary>
				/// Determina que alcançou o final do fluxo. Não há nenhuma Sample para ser lida.
				/// </summary>
				FimFluxo,

				/// <summary>
				/// Determina que há uma lacuna no fluxo.
				/// </summary>
				LacunaFluxo,

				/// <summary>
				/// Indica que a solicitação para leitura de amostra é invalida.
				/// </summary>
				SolicitaçãoInvalida,

				/// <summary>
				/// Determina que o Id de fluxo da midia que foi definido é invalido para a midia atual.
				/// </summary>
				IdFluxoMidiaInvalido,

				/// <summary>
				/// Determina que uma operação está pendente e que não pode realizar está operação no momento.
				/// </summary>
				OperaçãoPendente,

				/// <summary>
				/// Determina que houve um erro ao tentar ler a Sample.
				/// </summary>
				Erro
			};

			/// <summary>
			/// (ORIGINAL) - Enumera bandeiras que definem as caracteristicas do fluxo de bytes(ICarenMFByteStream).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFBYTESTREAM_CHARACTERISTICS
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte das contantes originais.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// O fluxo de bytes pode ser lido.
				/// </summary>
				CA_MFBYTESTREAM_IS_READABLE = 0x00000001,
				/// <summary>
				/// O fluxo de bytes pode ser escrito para.
				/// </summary>
				CA_MFBYTESTREAM_IS_WRITABLE = 0x00000002,
				/// <summary>
				/// O fluxo de bytes pode ser procurado.
				/// </summary>
				CA_MFBYTESTREAM_IS_SEEKABLE = 0x00000004,
				/// <summary>
				/// O fluxo de bytes é de uma fonte remota, como uma rede.
				/// </summary>
				CA_MFBYTESTREAM_IS_REMOTE = 0x00000008,
				/// <summary>
				/// O fluxo de byte representa um diretório de arquivos.
				/// </summary>
				CA_MFBYTESTREAM_IS_DIRECTORY = 0x00000080,
				/// <summary>
				/// Procurar dentro deste fluxo pode ser lento. Por exemplo, o fluxo de bytes pode ser baixado de uma rede.
				/// </summary>
				CA_MFBYTESTREAM_HAS_SLOW_SEEK = 0x00000100,
				/// <summary>
				/// O fluxo de bytes está atualmente baixando dados para um cache local. As operações de leitura no fluxo de bytes podem levar mais tempo até que os dados sejam completamente baixados.
				/// Esta bandeira é limpa depois que todos os dados foram baixados. Se a bandeira MFBYTESTREAM_HAS_SLOW_SEEK também estiver definida, significa que o fluxo de bytes deve baixar todo o 
				/// arquivo sequencialmente. Caso contrário, o fluxo de bytes pode responder a solicitações de busca reiniciando o download a partir de um novo ponto no fluxo.
				/// </summary>
				CA_MFBYTESTREAM_IS_PARTIALLY_DOWNLOADED = 0x00000200,
				/// <summary>
				/// Outro segmento ou processo pode abrir este fluxo de byte para gravação. Se esta bandeira estiver presente, o comprimento do fluxo de bytepode mudar enquanto está sendo lido.
				/// Esta bandeira pode afetar o comportamento dos manipuladores de fluxo de bytes. Para obter mais informações, consulte o atributo (MF_BYTESTREAMHANDLER_ACCEPTS_SHARE_WRITE).
				/// </summary>
				CA_MFBYTESTREAM_SHARE_WRITE = 0x00000400,
				/// <summary>
				/// O fluxo de byte saem atualmente usando a rede para receber o conteúdo. O hardware de rede pode entrar em um estado de economia de energia quando este bit estiver definido.
				/// </summary>
				CA_MFBYTESTREAM_DOES_NOT_USE_NETWORK = 0x00000800
			};
			
			/// <summary>
			/// (MFBYTESTREAM_SEEK_ORIGIN) - Enumera bandeiras que especificam a origem de uma solicitação de busca.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFBYTESTREAM_SEEK_ORIGIN
			{
				/// <summary>
				/// A posição de busca é especificada em relação ao início do fluxo.
				/// </summary>
				Posicao_Inical = 0,

				/// <summary>
				/// A posição de busca é especificada em relação à posição atual de leitura/gravação no fluxo.
				/// </summary>
				Posicao_Atual = (Posicao_Inical + 1)
			};

			/// <summary>
			/// (ORIGINAL) - Enumera bandeiras que seram utilizadas durante uma chamada para ICarenMFByteStream::Seek
			/// </summary>
			public enum class CA_MFBYTESTREAM_SEEK_FLAGS
			{
				/// <summary>
				/// Não representa nada. Utilizada para da suporte apenas.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Todas as solicitações de I/O pendentes são canceladas após a solicitação de solicitação ser concluída com sucesso.
				/// </summary>
				CA_MFBYTESTREAM_SEEK_FLAG_CANCEL_PENDING_IO = 0x00000001
			};
			
			/// <summary>
			/// (Original) - Enumera os (Valores) que podem ser usado para acessar um Stream no Leitor de mídia(ICarenMFSourceReader).
			/// Você pode usar os valores abaixo, convertendo para (uint) para obter o valor da enumeração.
			/// </summary>
			public enum class CA_SOURCE_READER_ID : UInt32
			{
				/// <summary>
				/// Indica que deve obter o (Primeiro Fluxo de Áudio) na lista de Streams.
				/// </summary>
				ID_MF_SOURCE_READER_FIRST_AUDIO_STREAM = 0xFFFFFFFD,

				/// <summary>
				/// Indica que deve obter o (Primeiro Fluxo de Vídeo) na lista de Streams.
				/// </summary>
				ID_MF_SOURCE_READER_FIRST_VIDEO_STREAM = 0xFFFFFFFC,

				/// <summary>
				/// Indica que deve obter ou ler qual quer fluxo que estiver disponível.
				/// </summary>
				ID_MF_SOURCE_READER_ANY_STREAM = 0xFFFFFFFE,

				/// <summary>
				/// Indica que deve obter a (Fonte de mídia).
				/// </summary>
				ID_MF_SOURCE_READER_MEDIASOURCE = 0xFFFFFFFF,

				/// <summary>
				/// Indica que deve ler ou selecionar todos os fluxos.
				/// </summary>
				ID_MF_SOURCE_READER_ALL_STREAMS = 0xFFFFFFFE,

			};

			/// <summary>
			/// (MF_SOURCE_READER_CONTROL_FLAG) - Contém sinalizadores para o método ICarenMFSample.ReadSample.
			/// </summary>
			public enum class CA_MF_SOURCE_READER_CONTROL_FLAG
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// Recupere quaisquer amostras pendentes, mas não solicite mais amostras da fonte de mídia. 
				/// Para obter todos as amostras pendentes, chame (ReadSample) com esse sinalizador até que o método 
				/// retorna uma amostra (NULA).
				/// </summary>
				MF_SOURCE_READER_CONTROLF_DRAIN = 0x1
			};
			
			/// <summary>
			/// (MF_SOURCE_READER_FLAG) - Contém sinalizadores que indcam o status de uma chamada para o método ICarenMFSample.ReadSample.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_SOURCE_READER_FLAG
			{
				/// <summary>
				/// Indica que não houve nenhum erro, e que não é necessário nenhuma ação para esse flag.
				/// </summary>
				NONE = 0,


				/// <summary>
				/// Ocorreu um erro durante a realização da chamada para a interface (ICarenMFSourceReader). Não chame novamente o método para ler uma proxima amostra.
				/// </summary>
				MF_SOURCE_READERF_ERROR = 0x1,

				/// <summary>
				/// O leitor de mídia alcançou o final do fluxo.
				/// </summary>
				MF_SOURCE_READERF_ENDOFSTREAM = 0x2,

				/// <summary>
				/// Um ou mais novos fluxos foram criados. Responda a esse sinalizador fazendo pelo menos um dos seguintes procedimentos: 
				/// > Defina os tipos de saída nos novos fluxos.
				/// > Atualize a seleção de fluxo selecionando ou desmarcando fluxos.
				/// </summary>
				MF_SOURCE_READERF_NEWSTREAM = 0x4,

				/// <summary>
				/// O (Formato Nativo) foi alterado para um ou mais fluxos. O (Formato Nativo) é o formato fornecido pela fonte de mídia 
				/// antes de qualquer decodificadores serem inseridos.
				/// </summary>
				MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED = 0x10,

				/// <summary>
				/// A mídia atual tem o tipo alterado para um ou mais fluxos. Para obter o tipo de mídia atual, chame o  método ICarenMFSourceReader.GetCurrentMediaType.
				/// </summary>
				MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED = 0x20,

				/// <summary>
				/// Há uma lacuna no fluxo. Este sinalizador corresponde a um evento MEStreamTick da (Fonte de Mídia).
				/// </summary>
				MF_SOURCE_READERF_STREAMTICK = 0x100,

				/// <summary>
				/// Todas as transformações inseridas pelo aplicativo foram removidas para um fluxo específico. Isso pode ser devido a uma alteração de 
				/// formato dinâmico de uma fonte ou decodificador que impede que as transformações personalizadas sejam usadas porque eles não podem 
				/// manipular o novo tipo de mídia.
				/// </summary>
				MF_SOURCE_READERF_ALLEFFECTSREMOVED = 0x200
			};

			/// <summary>
			/// (Original) - Define o comportamento do resolvedor de origem(ICarenMFSourceResolver). Esses sinalizadores também são usados por manipuladores de esquema e manipuladores de fluxo de bytes.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_SOURCE_RESOLVER_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Tentativa de criar uma fonte de mídia.
				/// </summary>
				MF_RESOLUTION_MEDIASOURCE = 0x00000001,

				/// <summary>
				/// Tentativa de criar um fluxo de bytes.
				/// </summary>
				MF_RESOLUTION_BYTESTREAM = 0x00000002,

				/// <summary>
				/// Se a resolução de origem falhar usando o manipulador de fluxo de bytes registrado para o tipo MIME ou extensão de nome de arquivo, o resolvedor de origem enumera todos 
				/// os manipuladores de fluxo de bytes registrados.
				/// Os manipuladores de fluxo de bytes são registrados por extensão de nome de arquivo ou tipo MIME. Inicialmente, o resolvedor de origem tenta usar um manipulador que 
				/// corresponda à extensão de nome de arquivo ou ao tipo MIME.
				/// Se isso falhar, por padrão, toda a resolução da fonte falhará e o resolvedor de origem retornará um código de erro para o aplicativo. Se esse sinalizador for especificado, 
				/// no entanto, o resolvedor de origem continuará a enumerar todos os manipuladores de fluxo de bytes registrados.
				/// Possivelmente, um manipulador com correspondência incorreta pode criar com êxito a fonte de mídia. Este sinalizador não pode ser combinado com o sinalizador 
				/// (MF_RESOLUTION_KEEP_BYTE_STREAM_ALIVE_ON_FAIL).
				/// </summary>
				MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE = 0x00000010,

				/// <summary>
				/// Se a resolução da fonte falhar, o resolvedor de origem não fecha o fluxo de bytes. Por padrão, o resolvedor de origem fecha o fluxo de bytes na falha. 
				/// Se esse sinalizador for usado e a resolução da fonte falhar, o chamador deverá chamar o método novamente e definir o sinalizador 
				/// MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE.
				/// Este sinalizador não pode ser combinado com o sinalizador MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE.Veja Observações para mais informações.
				/// </summary>
				MF_RESOLUTION_KEEP_BYTE_STREAM_ALIVE_ON_FAIL = 0x00000020,

				/// <summary>
				/// Solicita acesso de leitura à origem.
				/// </summary>
				MF_RESOLUTION_READ = 0x00010000,

				/// <summary>
				/// Solicita acesso de gravação à origem.
				/// </summary>
				MF_RESOLUTION_WRITE = 0x00020000,

				/// <summary>
				/// (REQUER WINDOWS 8) O resolvedor de origem não usará plug-ins registrados localmente ou plug-ins de manipulador bytestream
				/// </summary>
				MF_RESOLUTION_DISABLE_LOCAL_PLUGINS = 0x00000040
			};

			/// <summary>
			/// (MF_CAPTURE_ENGINE_SINK_TYPE) - Enumera valores que especificam um tipo de coletor de captura.
			/// </summary>
			public enum class CA_MF_CAPTURE_ENGINE_SINK_TYPE
			{
				/// <summary>
				/// Um sink de gravação, para capturar áudio e vídeo em um arquivo.
				/// </summary>
				MF_CAPTURE_ENGINE_SINK_TYPE_RECORD = 0,

				/// <summary>
				/// Um sink de visualização, para visualização de áudio ou vídeo ao vivo.
				/// </summary>
				MF_CAPTURE_ENGINE_SINK_TYPE_PREVIEW = 0x1,

				/// <summary>
				/// Um sink de fotos, para capturar imagens paradas.
				/// </summary>
				MF_CAPTURE_ENGINE_SINK_TYPE_PHOTO = 0x2
			};
			
			/// <summary>
			/// (ORIGINAL) - Enumera valores utilizados para definir um fluxo de captura. As Apis da Capture engine utilizam essa enumeração.
			/// </summary>
			public enum class CA_MF_CAPTURE_ENGINE_FIRST_SOURCE_INDEX : UInt32
			{
				/// <summary>
				/// O primeiro fluxo de imagem.
				/// </summary>
				MF_CAPTURE_ENGINE_FIRST_SOURCE_PHOTO_STREAM = 0xFFFFFFFB,

				/// <summary>
				/// O primeiro vídeo stream.
				/// </summary>
				MF_CAPTURE_ENGINE_FIRST_SOURCE_VIDEO_STREAM = 0xFFFFFFFC,

				/// <summary>
				/// O primeiro fluxo de áudio.
				/// </summary>
				MF_CAPTURE_ENGINE_FIRST_SOURCE_AUDIO_STREAM = 0xFFFFFFFD
			};
			
			/// <summary>
			/// (MF_CAPTURE_ENGINE_STREAM_CATEGORY) - Enumera os valores para a categoria de fluxo de origem.
			/// </summary>
			public enum class CA_MF_CAPTURE_ENGINE_STREAM_CATEGORY
			{
				/// <summary>
				/// Especifica um fluxo de visualização de vídeo.
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_VIDEO_PREVIEW = 0,

				/// <summary>
				/// Especifica um fluxo de captura de vídeo.
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_VIDEO_CAPTURE = 0x1,

				/// <summary>
				/// Especifica um fluxo de fotos independente.
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_PHOTO_INDEPENDENT = 0x2,

				/// <summary>
				/// Especifica um fluxo de fotos dependente.
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_PHOTO_DEPENDENT = 0x3,

				/// <summary>
				/// Especifica um fluxo de áudio.
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_AUDIO = 0x4,

				/// <summary>
				/// Especifica um fluxo sem suporte. 
				/// </summary>
				MF_CAPTURE_ENGINE_STREAM_CATEGORY_UNSUPPORTED = 0x5
			};

			/// <summary>
			/// (MF_CAPTURE_ENGINE_DEVICE_TYPE) - Enumera valores para que especificam um tipo de dispositivo de captura.
			/// </summary>
			public enum class CA_MF_CAPTURE_ENGINE_DEVICE_TYPE
			{
				/// <summary>
				/// Um dispositivo de captura de áudio, como um microfone.
				/// </summary>
				MF_CAPTURE_ENGINE_DEVICE_TYPE_AUDIO = 0,

				/// <summary>
				/// Um dispositivo de captura de vídeo, como uma webcam.
				/// </summary>
				MF_CAPTURE_ENGINE_DEVICE_TYPE_VIDEO = 0x1
			};
			
			/// <summary>
			/// (_MF_QUALITY_DROP_MODE)(FALTA DOCUMENTAR) - Enumeração que especifica o quão agressivamente um componente do gasoduto deve soltar(drop) amostras.
			/// </summary>
			public enum class CA_MF_QUALITY_DROP_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_1 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_2 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_3 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_4 = 0x4,
				/// <summary>
				/// 
				/// </summary>
				MF_DROP_MODE_5 = 0x5,
				/// <summary>
				/// 
				/// </summary>
				MF_NUM_DROP_MODES = 0x6
			};

			/// <summary>
			/// (MF_QUALITY_LEVEL)(FALTA DOCUMENTAR) - Enumeração que especifica o nível de qualidade de um componente de tubulação. O nível de qualidade determina como o componente consome ou produz amostras.
			/// </summary>
			public enum class CA_MF_QUALITY_LEVEL
			{
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL_MINUS_1 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL_MINUS_2 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL_MINUS_3 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL_MINUS_4 = 0x4,
				/// <summary>
				/// 
				/// </summary>
				MF_QUALITY_NORMAL_MINUS_5 = 0x5,
				/// <summary>
				/// 
				/// </summary>
				MF_NUM_QUALITY_LEVELS = 0x6
			};

			/// <summary>
			/// (MF_QUALITY_ADVISE_FLAGS) - Enumerção que contém bandeiras para o método ICarenMFQualityAdvise2::NotifyQualityEvent.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_QUALITY_ADVISE_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O decodificador fez tudo o que pode para reduzir a latência amostral, e as amostras ainda estão atrasadas.
				/// </summary>
				MF_QUALITY_CANNOT_KEEP_UP = 0x1
			};
			
			/// <summary>
			/// (Original) - Enumera as possiveis características de um Coletor de Midia.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MEDIASINK_CHARACTERISTICS
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte das contantes originais.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O coletor de mídia tem um número fixo de fluxos. Ele não oferece suporte aos métodos: 
				/// AddStreamSink e RemoveStreamSink no Coletor de mídia.
				/// </summary>
				CA_MEDIASINK_FIXED_STREAMS = 0x00000001,

				/// <summary>
				/// O coletor de mídia não pode corresponder às taxas com um relógio externo.
				/// </summary>
				CA_MEDIASINK_CANNOT_MATCH_CLOCK = 0x00000002,

				/// <summary>
				/// O coletor de mídia não tem sinal. Ele consome amostras o mais rápido possível e não se sincroniza com um relógio de apresentação.
				/// A maioria dos coletores de arquivamento não tem identificação.
				/// </summary>
				CA_MEDIASINK_RATELESS = 0x00000004,

				/// <summary>
				/// O coletor de mídia requer um relógio de apresentação. O relógio de apresentação é definido chamando o 
				/// o método (DefinirRelogioApresentação) no coletor de mídia.
				/// </summary>
				CA_MEDIASINK_CLOCK_REQUIRED = 0x00000008,

				/// <summary>
				///  O coletor de mídia pode aceitar exemplos de (Preroll) antes que o relógio de apresentação seja iniciado. 
				/// O coletor de mídia expõe o IMFMediaSinkPreroll interface.
				/// </summary>
				CA_MEDIASINK_CAN_PREROLL = 0x00000010,

				/// <summary>
				/// O primeiro coletor de fluxo (índice 0) é um fluxo de referência. O fluxo de referência deve
				/// ter um tipo de mídia antes que os tipos de mídia podem ser definidos em outros coletores de fluxo.
				/// </summary>
				CA_MEDIASINK_REQUIRE_REFERENCE_MEDIATYPE = 0x00000020,

			};

			/// <summary>
			/// (MFSTREAMSINK_MARKER_TYPE) - Enumera as possiveis características de um Coletor de Midia.
			/// </summary>
			public enum class CA_MFSTREAMSINK_MARKER_TYPE
			{
				/// <summary>
				/// Este marcador é para uso do aplicativo e não transmite qualquer informação 
				/// para o coletor de fluxo.
				/// </summary>
				MFSTREAMSINK_MARKER_DEFAULT = 0,

				/// <summary>
				/// Este marcador indica o fim de um segmento dentro de uma apresentação. Pode haver uma 
				/// lacuna no fluxo até que o próximo segmento seja iniciado. Não há nenhum dado associado 
				/// a este marcador.
				/// </summary>
				MFSTREAMSINK_MARKER_ENDOFSEGMENT = (MFSTREAMSINK_MARKER_DEFAULT + 1),

				/// <summary>
				/// Esse marcador indica que há uma lacuna no fluxo. Os dados do marcador são um valor (Int64 - VT_I8) 
				/// que especifica o tempo para a amostra ausente. A próxima amostra recebida após este marcador terá o
				/// sinalizador de descontinuidade. Este marcador corresponde a um evento Mestreamtick do fluxo.
				/// </summary>
				MFSTREAMSINK_MARKER_TICK = (MFSTREAMSINK_MARKER_ENDOFSEGMENT + 1),

				/// <summary>
				/// Este marcador contém um evento de mídia. Os dados do marcador são um ponteiro para a interface 
				/// IMFMediaEvent do evento (VT_UNKNOWN).
				/// </summary>
				MFSTREAMSINK_MARKER_EVENT = (MFSTREAMSINK_MARKER_TICK + 1)

			};

			/// <summary>
			/// (_MFCLOCK_CHARACTERISTICS_FLAGS) - Enumera as possiveis caracteristicas da (ICarenMFClock)
			/// </summary>
			public enum class CA_MFCLOCK_CHARACTERISTICS_FLAGS
			{
				/// <summary>
				/// Os tempos de relógio retornados pelo método (ICarenMFClock.GetCorrelatedTime) estão em unidades de 100 nanoseconds. Se este sinalizador estiver 
				/// ausente, chame o método (ICarenMFClock.GetProperties) para obter a freqüência de clock. A freqüência de Clock é fornecida na (RL_FREQUENCIA_RELOGIO)
				/// membro da estrutura CA_MFCLOCK_PROPERTIES.
				/// </summary>
				MFCLOCK_CHARACTERISTICS_FLAG_FREQUENCY_10MHZ = 0x2,
				/// <summary>
				/// O relógio está sempre em execução. Se este sinalizador estiver presente, o relógio não pode ser
				/// pausado ou interrompido. Se este sinalizador estiver ausente, chame o método (ICarenMFClock.GetState) para obter o estado atual.
				/// </summary>
				MFCLOCK_CHARACTERISTICS_FLAG_ALWAYS_RUNNING = 0x4,
				/// <summary>
				/// Os tempos de relógio são gerados a partir do relógio do sistema.
				/// </summary>
				MFCLOCK_CHARACTERISTICS_FLAG_IS_SYSTEM_CLOCK = 0x8,
			};

			/// <summary>
			/// Enumera possveis flags relacionais para o Relógio.
			/// </summary>
			public enum class CA_MFCLOCK_RELATIONAL_FLAG
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da numeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Os valores de jitter são sempre negativos. Em outras palavras, o tempo retornado por (ICarenMFClock.GetCorrelatedTime) pode jitter por trás do tempo 
				/// real do relógio, mas nunca tremulará antes do tempo real. Se este sinalizador não estiver presente, o relógio pode jitter em qualquer direção.
				/// </summary>
				MFCLOCK_RELATIONAL_FLAG_JITTER_NEVER_AHEAD = 0x1
			};

			/// <summary>
			/// (MFCLOCK_STATE) - Enumera os possiveis estados do Relógio.
			/// </summary>
			public enum class CA_MFCLOCK_STATE
			{
				/// <summary>
				/// O relógio é inválido. Um relógio pode ser inválido por vários motivos. Alguns relógios retornam esse estado
				/// antes do primeiro início. Esse estado também pode ocorrer se o dispositivo subjacente for perdido.
				/// </summary>
				MFCLOCK_STATE_INVALID = 0,

				/// <summary>
				/// O relógio está em execução. Enquanto o relógio está em execução, o tempo avança na frequência do relógio 
				/// e a taxa atual.
				/// </summary>
				MFCLOCK_STATE_RUNNING = (MFCLOCK_STATE_INVALID + 1),

				/// <summary>
				/// O relógio está parado. Enquanto parado, o relógio relata um tempo de 0.
				/// </summary>
				MFCLOCK_STATE_STOPPED = (MFCLOCK_STATE_RUNNING + 1),

				/// <summary>
				/// O relógio está em pausa. Enquanto pausado, o relógio informa o tempo em que foi pausado.
				/// </summary>
				MFCLOCK_STATE_PAUSED = (MFCLOCK_STATE_STOPPED + 1)
			};

			/// <summary>
			/// (MFVideoAspectRatioMode) - Enumera os modos de relação de aspecto do vídeo.
			/// </summary>
			public enum class CA_MFVideoAspectRatioMode
			{
				/// <summary>
				/// Não mantenha a proporção do vídeo. Alongue o vídeo para caber no retângulo de saída.
				/// </summary>
				MFVideoARMode_None = 0,

				/// <summary>
				/// Preserve a taxa de proporção do vídeo por Letterboxing ou dentro do retângulo de saída.
				/// </summary>
				MFVideoARMode_PreservePicture = 0x1,

				/// <summary>
				/// (EVR Ignora esse sinalizador).
				/// Corrija a taxa de proporção se o tamanho físico do dispositivo de exibição não corresponder à resolução de exibição. 
				/// Por exemplo, se a resolução nativa do monitor for 1600 por 1200 (4:3), mas a resolução de exibição for 1280 por 1024 
				/// (5:4), o monitor exibirá pixels não quadrados.
				/// </summary>
				MFVideoARMode_PreservePixel = 0x2,

				/// <summary>
				/// Aplique um trecho horizontal não linear se a taxa de proporção do retângulo de destino não corresponder à taxa de 
				/// proporção do retângulo de origem.
				/// O algoritmo de estiramento não-linear preserva a taxa de proporção no meio da imagem e se estende (ou encolhe) a 
				/// imagem progressivamente mais para a esquerda e direita. Este modo é útil ao Visualizar 4:3 conteúdo em tela cheia
				/// em um display 16:9, em vez de pilar-boxing. Não-linear esticar vertical não é suportada, porque os resultados 
				/// visuais são geralmente pobres.
				/// Esse modo pode causar degradação do desempenho.
				/// Se este sinalizador estiver definido, você também deve definir o MFVideoARMode_PreservePixel e MFVideoARMode_PreservePicture sinalizadores.
				/// </summary>
				MFVideoARMode_NonLinearStretch = 0x4,

				/// <summary>
				/// Bitmask para validar valores de sinalizador. Esse valor não é um sinalizador válido.
				/// </summary>
				MFVideoARMode_Mask = 0x7
			};

			/// <summary>
			/// (MFVideoRenderPrefs) Enumera sinalizadores que definem como o renderizador de vídeo aprimorado (EVR) exibe o vídeo.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFVideoRenderPrefs
			{
				/// <summary>
				/// Se este sinalizador estiver definido, o EVR não desenha a cor da borda. Por padrão, o EVR desenha uma borda em áreas do 
				/// retângulo de destino que não têm nenhum vídeo. Consulte o método: ICarenMFVideoDisplayControl.SetBorderColor
				/// </summary>
				VR_NO_RENDER_BORDER = 0x1,

				/// <summary>
				/// Se este sinalizador estiver definido, o EVR não clip o vídeo quando a janela de vídeo atravessa dois monitores. Por padrão, 
				/// se a janela de vídeo estiver em dois monitores, o EVR clipes o vídeo para o monitor que contém a maior área de vídeo.
				/// </summary>
				VR_NO_VIDEOCLIP_TO_DEVICE = 0x2,

				/// <summary>
				/// Permita que o EVR limite sua saída para combinar a largura de banda GPU.
				/// </summary>
				VR_EVR_PERMITIR_LIMITAR_SAIDA_COMBINAR_GPU = 0x4,

				/// <summary>
				/// Force o EVR para limitar sua saída para corresponder à largura de banda da GPU.
				/// </summary>
				VR_EVR_FORCE_LIMITAR_SAIDA_COMBINAR_GPU = 0x8,

				/// <summary>
				/// Forçar o EVR para chamadas de (Present) no Direct3D em lotes. Essa otimização permite que o sistema entre em Estados ociosos 
				/// com mais frequência, o que pode reduzir o consumo de energia.
				/// </summary>
				VR_EVR_FORCE_CALL_PRESENT_D3D = 0x10,

				/// <summary>
				/// Permitir que o EVR batch chamadas Direct3D presentes.
				/// </summary>
				VR_EVR_PERMITIR_CALL_PRESENT_D3D = 0x20,

				/// <summary>
				/// Forçar o EVR para misturar o vídeo dentro de um retângulo que é menor do que o retângulo de saída. O EVR dimensionará o resultado 
				/// para o tamanho de saída correto. A resolução efetiva será menor se essa configuração for aplicada.
				/// </summary>
				VR_EVR_FORCE_SCALING = 0x40,

				/// <summary>
				/// Permitir que o EVR misturar o vídeo dentro de um retângulo que é menor do que o retângulo de saída.
				/// </summary>
				VR_EVR_PERMITIR_SCALING = 0x80,

				/// <summary>
				/// Impeça que o EVR redesenho a janela de vídeo após um comando Stop. Por padrão, o EVR repinta a janela de vídeo em preto 
				/// após um comando Stop.
				/// </summary>
				VR_EVR_DO_NOT_REPAINT_ON_STOP = 0x100,

				/// <summary>
				/// Máscara de bits para validar valores de sinalizador. Esse valor não é um sinalizador válido.
				/// </summary>
				VR_MASK = 0x1ff
			};
			
			/// <summary>
			/// (MF_TOPOSTATUS) - enumera valores que especificam o status de uma topologia durante a reprodução.
			/// </summary>
			public enum class CA_MF_TOPOSTATUS
			{
				/// <summary>
				/// Este valor não é usado.
				/// </summary>
				MF_TOPOSTATUS_INVALID = 0,

				/// <summary>
				/// A topologia está pronta para começar. Depois que essa bandeira de status for recebida, você pode usar o método (GetService) para consultar a topologia para serviços, como controle de taxa(Rate Control).
				/// </summary>
				MF_TOPOSTATUS_READY = 100,

				/// <summary>
				/// A Media Session começou a ler dados das fontes de mídia na topologia.
				/// </summary>
				MF_TOPOSTATUS_STARTED_SOURCE = 200,

				/// <summary>
				/// A Media Session modificou a topologia, porque o formato de um fluxo mudou.
				/// </summary>
				MF_TOPOSTATUS_DYNAMIC_CHANGED = 210,
				
				/// <summary>
				/// Os Sinks de midia mudaram da topologia anterior para esta topologia. Este valor de status não é enviado para a primeira topologia que é reproduzida. Para a primeira topologia, o evento MESessionStarted 
				/// indica que os dissipadores de mídia começaram a receber dados.
				/// </summary>
				MF_TOPOSTATUS_SINK_SWITCHED = 300,
				
				/// <summary>
				/// A reprodução desta topologia está completa. A Sessão de Mídia ainda pode usar a topologia internamente. A Media Session não libera completamente a topologia até que envie o próximo evento de status 
				/// MF_TOPOSTATUS_STARTED_SOURCE ou o evento MESessionEnded.
				/// </summary>
				MF_TOPOSTATUS_ENDED = 400
			};

			/// <summary>
			/// Enumera como um fluxo de vídeo é entrelaçado. Nas descrições que se seguem, o campo superior 
			/// refere-se ao campo que contém a linha de digitalização da metade à esquerda. Campo inferior refere-se 
			/// ao campo que contém a primeira linha de verificação completa.
			/// </summary>
			public enum class CA_VIDEO_MODO_ENTRELACAMENTO
			{

				/// <summary>
				/// O tipo de entrelaçamento não é conhecido.
				/// </summary>
				Desconhecido = 0,

				/// <summary>
				/// Quadros progressivos.
				/// </summary>
				Progressivo = 2,

				/// <summary>
				/// Molduras entrelaçadas. Cada quadro contém dois campos. As linhas de campo são intercaladas, com o 
				/// campo superior aparecendo na primeira linha.
				/// </summary>
				FieldInterleavedUpperFirst = 3,

				/// <summary>
				/// Molduras entrelaçadas. Cada quadro contém dois campos. As linhas de campo são intercaladas, com o 
				/// campo inferior aparecendo na primeira linha.
				/// </summary>
				FieldInterleavedLowerFirst = 4,

				/// <summary>
				/// Molduras entrelaçadas. Cada quadro contém um campo, com o campo superior aparecendo primeiro.
				/// </summary>
				FieldSingleUpper = 5,

				/// <summary>
				/// Molduras entrelaçadas. Cada quadro contém um campo, com o campo inferior aparecendo primeiro.
				/// </summary>
				FieldSingleLower = 6,

				/// <summary>
				/// O fluxo contém uma mistura de modos entrelaçado e progressivo.
				/// </summary>
				MixedInterlaceOrProgressive = 7,

				/// <summary>
				/// Reservado.
				/// </summary>
				Last = (MixedInterlaceOrProgressive + 1),

				/// <summary>
				/// Reservado. Este membro força o tipo de enumeração para compilar como um valor DWORD.
				/// </summary>
				ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// Enumera o level de encodificação de video MPEG-2 - standard (ISO13818-2).
			/// Os decodificadores de vídeo DVD MPEG-2 devem suportar AM_MPEG2Level_Low ou AM_MPEG2Level_Main.
			/// </summary>
			public enum class CA_ENCODE_NIVEL_AM_MPEG2
			{
				/// <summary>
				/// Nível baixo.
				/// </summary>
				AM_MPEG2Level_Low = 1,
				/// <summary>
				/// Nível principal.
				/// </summary>
				AM_MPEG2Level_Main,
				/// <summary>
				/// Nível 1440 alto.
				/// </summary>
				AM_MPEG2Level_High1440,
				/// <summary>
				/// Alto nível.
				/// </summary>
				AM_MPEG2Level_High
			};

			/// <summary>
			/// Enumera o level de encodificação de video H.264.
			/// Esses valores são usados com o atributo MF_MT_MPEG2_LEVEL.
			/// </summary>
			public enum class  CA_ENCODE_NIVEL_eAVEncH264V
			{
				/// <summary>
				/// Nível 1.
				/// </summary>
				eAVEncH264VLevel1 = 10,
				/// <summary>
				/// Nível 1B.
				/// </summary>
				eAVEncH264VLevel1_b = 11,
				/// <summary>
				/// Nível 1,1.
				/// </summary>
				eAVEncH264VLevel1_1 = 11,
				/// <summary>
				/// Nível 1,2.
				/// </summary>
				eAVEncH264VLevel1_2 = 12,
				/// <summary>
				/// Nível 1,3.
				/// </summary>
				eAVEncH264VLevel1_3 = 13,
				/// <summary>
				/// Nível 2.
				/// </summary>
				eAVEncH264VLevel2 = 20,
				/// <summary>
				/// Nível 2,1.
				/// </summary>
				eAVEncH264VLevel2_1 = 21,
				/// <summary>
				/// Nível 2,2.
				/// </summary>
				eAVEncH264VLevel2_2 = 22,
				/// <summary>
				/// Nível 3.
				/// </summary>
				eAVEncH264VLevel3 = 30,
				/// <summary>
				/// Nível 3,1.
				/// </summary>
				eAVEncH264VLevel3_1 = 31,
				/// <summary>
				/// Nível 3,2.
				/// </summary>
				eAVEncH264VLevel3_2 = 32,
				/// <summary>
				/// Nível 4.
				/// </summary>
				eAVEncH264VLevel4 = 40,
				/// <summary>
				/// Nível 4,1.
				/// </summary>
				eAVEncH264VLevel4_1 = 41,
				/// <summary>
				/// Nível 4,2.
				/// </summary>
				eAVEncH264VLevel4_2 = 42,
				/// <summary>
				/// Nível 5.
				/// </summary>
				eAVEncH264VLevel5 = 50,
				/// <summary>
				/// Nível 5,1.
				/// </summary>
				eAVEncH264VLevel5_1 = 51,
				/// <summary>
				/// Nível 5,2.
				/// </summary>
				eAVEncH264VLevel5_2 = 52
			};

			/// <summary>
			/// Enumera os perfils de vídeo H.264.
			/// Esses valores são usados com o atributo MF_MT_MPEG2_PROFILE.
			/// Esses valores também são usados com codificadores de câmera H.264 UVC 1.5.
			/// </summary>
			public enum class CA_VIDEO_PERFIL_eAVEncH264VProfile
			{
				/// <summary>
				/// O perfil é desconhecido ou não especificado.
				/// </summary>
				eAVEncH264VProfile_unknown = 0,
				/// <summary>
				/// Perfil simples.
				/// </summary>
				eAVEncH264VProfile_Simple = 66,
				/// <summary>
				/// Perfil de linha de base.
				/// </summary>
				eAVEncH264VProfile_Base = 66,
				/// <summary>
				/// Perfil principal.
				/// </summary>
				eAVEncH264VProfile_Main = 77,
				/// <summary>
				/// Alto perfil.
				/// </summary>
				eAVEncH264VProfile_High = 100,
				/// <summary>
				/// Perfil elevado da 4:2:2.
				/// </summary>
				eAVEncH264VProfile_422 = 122,
				/// <summary>
				/// Perfil alto de 10.
				/// </summary>
				eAVEncH264VProfile_High10 = 110,
				/// <summary>
				/// Perfil elevado da 4:4:4.
				/// </summary>
				eAVEncH264VProfile_444 = 244,
				/// <summary>
				/// Perfil estendido.
				/// </summary>
				eAVEncH264VProfile_Extended = 88,


				// UVC 1.2 H.264 extension


				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Perfil de base escalável.
				/// </summary>
				eAVEncH264VProfile_ScalableBase = 83,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Alto perfil escalável.
				/// </summary>
				eAVEncH264VProfile_ScalableHigh = 86,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// MultiView alto perfil.
				/// </summary>
				eAVEncH264VProfile_MultiviewHigh = 118,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Alto perfil estéreo.
				/// </summary>
				eAVEncH264VProfile_StereoHigh = 128,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Perfil de base restrito.
				/// </summary>
				eAVEncH264VProfile_ConstrainedBase = 256,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Alto perfil restrito
				/// </summary>
				eAVEncH264VProfile_UCConstrainedHigh = 257,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// Perfil de base restrito UC.
				/// </summary>
				eAVEncH264VProfile_UCScalableConstrainedBase = 258,
				/// <summary>
				/// UVC 1.2 H.264 extension
				/// UC restrito de alto perfil.
				/// </summary>
				eAVEncH264VProfile_UCScalableConstrainedHigh = 259
			};

			/// <summary>
			/// Indica um perfil de vídeo MPEG-2, conforme especificado no padrão de vídeo MPEG-2 (ISO13818-2).
			/// Os decodificadores de vídeo em DVD devem suportar AM_MPEG2Profile_Simple ou AM_MPEG2Profile_Main.
			/// </summary>
			public enum class CA_VIDEO_PERFIL_AM_MPEG2Profile
			{
				/// <summary>
				/// Perfil simples.
				/// </summary>
				AM_MPEG2Profile_Simple = 1,
				/// <summary>
				/// Perfil principal.
				/// </summary>
				AM_MPEG2Profile_Main,
				/// <summary>
				/// Perfil escalonável de relação sinal-ruído (SNR)
				/// </summary>
				AM_MPEG2Profile_SNRScalable,
				/// <summary>
				/// Perfil escalonável espacialmente.
				/// </summary>
				AM_MPEG2Profile_SpatiallyScalable,
				/// <summary>
				/// Alto perfil.
				/// </summary>
				AM_MPEG2Profile_High
			};

			/// <summary>
			/// Enumera como deve ser uma imagem de vídeo para que ele se encaixa dentro de uma 
			/// proporção especificada.
			/// Use esses sinalizadores com o atributo MF_MT_PAD_CONTROL_FLAGS.
			/// </summary>
			public enum class CA_VIDEO_PAD_FLAGS
			{
				/// <summary>
				/// Não pad a imagem.
				/// </summary>
				MFVideoPadFlag_PAD_TO_None = 0,
				/// <summary>
				/// Pad a imagem para que ele possa ser exibido em uma área de 4×3.
				/// </summary>
				MFVideoPadFlag_PAD_TO_4x3,
				/// <summary>
				/// Pad a imagem para que ele possa ser exibido em uma área de 16×9.
				/// </summary>
				MFVideoPadFlag_PAD_TO_16x9
			};

			/// <summary>
			/// Enumera os valores que definem o perfil de audio AAC e o seu nivel.
			/// </summary>
			public enum class CA_AUDIO_AAC_PROFILE_LEVEL_INDICATION
			{
				/// <summary>
				/// Perfil AAC L2
				/// </summary>
				PerfilAAC_L2 = 0x29,
				/// <summary>
				/// AAC Profile L4
				/// </summary>
				PerfilAAC_L4 = 0x2A,
				/// <summary>
				/// AAC Profile L5
				/// </summary>
				PerfilAAC_L5 = 0x2B,
				/// <summary>
				/// High Efficiency v1 Perfil AAC L2
				/// </summary>
				PerfilAAC_HighEfficiency_V1_L2 = 0x2C,
				/// <summary>
				/// High Efficiency v1 Perfil AAC L4
				/// </summary>
				PerfilAAC_HighEfficiency_V1_L4 = 0x2E,
				/// <summary>
				/// High Efficiency v1 AAC Profile L5
				/// </summary>
				PerfilAAC_HighEfficiency_V1_Profile_L5 = 0x2F,
				/// <summary>
				/// High Efficiency v2 AAC Profile L2
				/// </summary>
				PerfilAAC_HighEfficiency_V2_Profile_L2 = 0x30,
				/// <summary>
				/// High Efficiency v2 AAC Profile L3
				/// </summary>
				PerfilAAC_HighEfficiency_V2_Profile_L3 = 0x31,
				/// <summary>
				/// High Efficiency v2 AAC Profile L4
				/// </summary>
				PerfilAAC_HighEfficiency_V2_Profile_L4 = 0x32,
				/// <summary>
				/// High Efficiency v2 AAC Profile L5
				/// </summary>
				PerfilAAC_HighEfficiency_V2_Profile_L5 = 0x33,
			};

			/// <summary>
			/// (_MFVideoSrcContentHintFlags) - Enumera como deve ser uma imagem de vídeo para que ele se encaixa dentro de uma 
			/// proporção especificada.
			/// Use esses sinalizadores com o atributo MF_MT_SOURCE_CONTENT_HINT.
			/// </summary>
			public enum class CA_MFVideoSrcContentHintFlags
			{
				/// <summary>
				/// A proporção é desconhecida.
				/// </summary>
				MFVideoSrcContentHintFlag_None = 0,
				/// <summary>
				/// A fonte é o conteúdo de 16×9 codificado dentro de uma área de 4×3.
				/// </summary>
				MFVideoSrcContentHintFlag_16x9,
				/// <summary>
				/// A fonte é o índice 2.35:1 codificado dentro de uma área 16×9 ou 4×3.
				/// </summary>
				MFVideoSrcContentHintFlag_235_1
			};

			/// <summary>
			/// (MFVideoTransferFunction) - Enumera as funções de conversão de RGB linear para RGB não linear(R'G'B').
			/// Esses sinalizadores são usados com o atributo MF_MT_TRANSFER_FUNCTION.
			/// </summary>
			public enum class CA_MFVideoTransferFunction
			{
				/// <summary>
				/// Desconhecido. Trate como MFVideoTransFunc_709.
				/// </summary>
				MFVideoTransFunc_Unknown = 0,
				/// <summary>
				/// RGB linear (gama = 1.0).
				/// </summary>
				MFVideoTransFunc_10 = 1,
				/// <summary>
				/// True 1.8 Gamma, L ' = L ^ 1/1.8.
				/// </summary>
				MFVideoTransFunc_18 = 2,
				/// <summary>
				/// True 2.0 Gamma, L ' = L ^ 1/2.0.
				/// </summary>
				MFVideoTransFunc_20 = 3,
				/// <summary>
				/// True 2.2 Gamma, L ' = L ^ 1/2.2. Esta função de transferência é usada em ITU-R BT.
				/// 470-2 sistema M (NTSC).
				/// </summary>
				MFVideoTransFunc_22 = 4,
				/// <summary>
				/// Função de transferência de ITU-R BT. 709. Curva gama 2.2 com um segmento linear na faixa
				/// inferior. Esta função de transferência é usada em BT. 709, BT. 601, SMPTE 296M, SMPTE 170M, 
				/// BT. 470, e SPMTE 274M. Além disso BT-1361 usa esta função dentro do intervalo [0... 1].
				/// </summary>
				MFVideoTransFunc_709 = 5,
				/// <summary>
				/// Função de transferência de SPMTE 240M. Curva gama 2.2 com um segmento linear na faixa inferior.
				/// </summary>
				MFVideoTransFunc_240M = 6,
				/// <summary>
				/// função de transferência sRGB. Curva gama 2.4 com um segmento linear na faixa inferior.
				/// </summary>
				MFVideoTransFunc_sRGB = 7,
				/// <summary>
				/// True 2.8 gama. L ' = L ^ 1/2.8. Esta função de transferência é usada em ITU-R BT. 470-2 
				/// sistema B, G (PAL).
				/// </summary>
				MFVideoTransFunc_28 = 8,
				/// <summary>
				/// Transferência logarítmica (100:1 gama); por exemplo, como usado no vídeo H 264.
				/// </summary>
				MFVideoTransFunc_Log_100 = 9,
				/// <summary>
				/// Transferência logarítmica (316.22777:1 intervalo); por exemplo, como usado no vídeo H.264.
				/// </summary>
				MFVideoTransFunc_Log_316 = 10,
				/// <summary>
				/// Simétrico ITU-R BT. 709.
				/// </summary>
				MFVideoTransFunc_709_sym = 11,
				/// <summary>
				/// Luminância constante ITU-R BT. 2020
				/// </summary>
				MFVideoTransFunc_2020_const = 12,
				/// <summary>
				/// Não-constante luminância ITU-R BT. 2020
				/// </summary>
				MFVideoTransFunc_2020 = 13,
				/// <summary>
				/// True 2.6 Gamma, L ' = L ^ 1/2.6
				/// </summary>
				MFVideoTransFunc_26 = 14,
				/// <summary>
				/// SMPTE ST. 2084 também conhecido como PQ. Também definido em ITU-R BT. 2100
				/// {Requer o Windows 10, versão 1703 ou posterior.}
				/// </summary>
				MFVideoTransFunc_2084 = 15,
				/// <summary>
				/// Híbrido log-Gamma, ARIB STD-B67
				/// {Requer o Windows 10, versão 1703 ou posterior.}
				/// </summary>
				MFVideoTransFunc_HLG = 16,
				/// <summary>
				/// Sem documentação.
				/// </summary>
				MFVideoTransFunc_10_rel = 17,
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoTransFunc_Last = (MFVideoTransFunc_10_rel + 1),
				/// <summary>
				/// Reservados. Este membro força o tipo de enumeração para compilar como um valor DWORD .
				/// </summary>
				MFVideoTransFunc_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (MFVideoChromaSubsampling) - Enumera os sinalizadores que definem o esquema de codificação de 
			/// Chroma para Y'Cb'Cr' dados.
			/// Esses sinalizadores são usados com o atributo MF_MT_VIDEO_CHROMA_SITING.
			/// </summary>
			public enum class CA_MFVideoChromaSubsampling
			{
				/// <summary>
				/// Esquema de codificação desconhecido.
				/// </summary>
				MFVideoChromaSubsampling_Unknown = 0,
				/// <summary>
				/// O croma deve ser reconstruído como se o vídeo subjacente fosse conteúdo progressivo, em vez de pular 
				/// campos ou aplicar filtragem de croma para minimizar artefatos de reconstrução de croma entrelaçado 4:2:0.
				/// </summary>
				MFVideoChromaSubsampling_ProgressiveChroma = 0x8,
				/// <summary>
				/// As amostras de Chroma são alinhadas horizontalmente com as amostras de Luma, ou com múltiplos das amostras 
				/// de Luma. Se este sinalizador não estiver definido, as amostras de Chroma estão localizadas 1/2 pixel à direita 
				/// da amostra Luma correspondente.
				/// </summary>
				MFVideoChromaSubsampling_Horizontally_Cosited = 0x4,
				/// <summary>
				/// As amostras de Chroma são alinhadas verticalmente com as amostras de Luma, ou com múltiplos das amostras de Luma.
				/// Se este sinalizador não estiver definido, as amostras de Chroma estão localizadas 1/2 pixel para baixo do exemplo
				/// Luma correspondente.
				/// </summary>
				MFVideoChromaSubsampling_Vertically_Cosited = 0x2,
				/// <summary>
				/// Os planos você e V estão alinhados verticalmente. Se este sinalizador não estiver definido, os planos de croma são 
				/// considerados fora de fase por 1/2 amostra de croma, alternando entre uma linha de U seguido por uma linha de V.
				/// </summary>
				MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes = 0x1,
				/// <summary>
				/// Especifica o esquema de codificação de croma para vídeo MPEG-2. As amostras de Chroma são alinhadas horizontalmente 
				/// com as amostras de Luma, mas não são alinhadas verticalmente. Os planos você e V estão alinhados verticalmente.
				/// </summary>
				MFVideoChromaSubsampling_MPEG2 = (MFVideoChromaSubsampling_Horizontally_Cosited | MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes),
				/// <summary>
				/// Especifica o esquema de codificação de croma para vídeo MPEG-1.
				/// </summary>
				MFVideoChromaSubsampling_MPEG1 = MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes,
				/// <summary>
				/// Especifica o esquema de codificação de croma para vídeo PAL DV.
				/// </summary>
				MFVideoChromaSubsampling_DV_PAL = (MFVideoChromaSubsampling_Horizontally_Cosited | MFVideoChromaSubsampling_Vertically_Cosited),
				/// <summary>
				/// As amostras de Chroma são alinhadas verticalmente e horizontalmente com as amostras de Luma. Formatos YUV como 
				/// 4:4:4, 4:2:2 e 4:1:1 são sempre cosited em ambas as direções e deve usar este sinalizador.
				/// </summary>
				MFVideoChromaSubsampling_Cosited = ((MFVideoChromaSubsampling_Horizontally_Cosited | MFVideoChromaSubsampling_Vertically_Cosited) | MFVideoChromaSubsampling_Vertically_AlignedChromaPlanes),
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoChromaSubsampling_Last = (MFVideoChromaSubsampling_Cosited + 1),
				/// <summary>
				/// Reservados. Este membro força o tipo de enumeração para compilar como um valor DWORD.
				/// </summary>
				MFVideoChromaSubsampling_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (MFVideoLighting) - Enumera a iluminação ideal para exibir um determinado conjunto de conteúdo de vídeo.
			/// Essa enumeração é usada com o atributo MF_MT_VIDEO_LIGHTING.
			/// </summary>
			public enum class CA_MFVideoLighting
			{
				/// <summary>
				/// A iluminação ideal é desconhecida.
				/// </summary>
				MFVideoLighting_Unknown = 0,
				/// <summary>
				/// Iluminação brilhante; por exemplo, ao ar livre.
				/// </summary>
				MFVideoLighting_bright = 1,
				/// <summary>
				/// Brilho médio; por exemplo, iluminação normal do escritório.
				/// </summary>
				MFVideoLighting_office = 2,
				/// <summary>
				/// Dim; por exemplo, uma sala de estar com uma televisão e iluminação baixa adicional.
				/// </summary>
				MFVideoLighting_dim = 3,
				/// <summary>
				/// Escuro; por exemplo, um cinema.
				/// </summary>
				MFVideoLighting_dark = 4,
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoLighting_Last = (MFVideoLighting_dark + 1),
				/// <summary>
				/// Reservados. Este membro força o tipo de enumeração para compilar como um valor DWORD .
				/// </summary>
				MFVideoLighting_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (MFNominalRange) - Enumera se os dados de cores incluem altura livre e toeroom. O headroom permite valores 
			/// além do branco 1,0 ("mais branco do que a branca"), e o toeroom permite valores abaixo da referência 0,0 preto 
			/// ("mais negro do que o preto").
			/// Essa enumeração é usada com o atributo MF_MT_VIDEO_NOMINAL_RANGE.
			/// </summary>
			public enum class CA_MFNominalRange
			{
				/// <summary>
				/// Faixa nominal desconhecida.
				/// </summary>
				MFNominalRange_Unknown = 0,
				/// <summary>
				/// Equivalente a MFNominalRange_0_255.
				/// </summary>
				MFNominalRange_Normal = 1,
				/// <summary>
				/// Equivalente a MFNominalRange_16_235.
				/// </summary>
				MFNominalRange_Wide = 2,
				/// <summary>
				/// O intervalo normalizado [0... 1] mapeia para [0... 255] para amostras de 8 bits ou [0... 1023] 
				/// para amostras de 10 bits.
				/// </summary>
				MFNominalRange_0_255 = 1,
				/// <summary>
				/// O intervalo normalizado [0... 1] mapeia para [16... 235] para amostras de 8 bits ou [64... 940] 
				/// para amostras de 10 bits.
				/// </summary>
				MFNominalRange_16_235 = 2,
				/// <summary>
				/// O intervalo normalizado [0.. 1] mapeia para [48... 208] para amostras de 8 bits ou [64... 940] 
				/// para amostras de 10 bits.
				/// </summary>
				MFNominalRange_48_208 = 3,
				/// <summary>
				/// O intervalo normalizado [0.. 1] mapeia para [64... 127] para amostras de 8 bits ou [256... 508] 
				/// para amostras de 10 bits. Esse intervalo é usado no espaço de cores xRGB.
				/// {Requer o Windows 7 ou posterior.}
				/// </summary>
				MFNominalRange_64_127 = 4,
				/// <summary>
				/// Sem documentação.
				/// </summary>
				MFNominalRange_Last = (MFNominalRange_64_127 + 1),
				/// <summary>
				/// Sem documentação.
				/// </summary>
				MFNominalRange_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (_MFVideoPrimaries) - Enumera as cores primárias de uma fonte de vídeo. As cores primárias definem como 
			/// converter cores do espaço de cores RGB para o espaço de cores CIE XYZ.
			/// Essa enumeração é usada com o atributo MF_MT_VIDEO_PRIMARIES.
			/// </summary>
			public enum class CA_MFVideoPrimaries
			{
				/// <summary>
				/// As cores primárias são desconhecidas.
				/// </summary>
				MFVideoPrimaries_Unknown = 0,
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoPrimaries_reserved = 1,
				/// <summary>
				/// ITU-R BT. 709. Também usado para sRGB e scRGB.
				/// </summary>
				MFVideoPrimaries_BT709 = 2,
				/// <summary>
				/// ITU-R BT. 470-4 sistema M (NTSC).
				/// </summary>
				MFVideoPrimaries_BT470_2_SysM = 3,
				/// <summary>
				/// ITU-R BT. 470-4 sistema B, G (NTSC).
				/// </summary>
				MFVideoPrimaries_BT470_2_SysBG = 4,
				/// <summary>
				/// SMPTE 170M.
				/// </summary>
				MFVideoPrimaries_SMPTE170M = 5,
				/// <summary>
				/// SMPTE 240M.
				/// </summary>
				MFVideoPrimaries_SMPTE240M = 6,
				/// <summary>
				/// EBU 3213.
				/// </summary>
				MFVideoPrimaries_EBU3213 = 7,
				/// <summary>
				/// SMPTE C (SMPTE RP 145).
				/// </summary>
				MFVideoPrimaries_SMPTE_C = 8,
				/// <summary>
				/// Primárias de cores ITU-R BT. 2020.
				/// {Requer o Windows 8 ou posterior.}
				/// </summary>
				MFVideoPrimaries_BT2020 = 9,
				/// <summary>
				/// CIE 1931 XYZ (veja: cie 1931 espaço de cor). Observe que esse espaço de cores só é 
				/// bem definido para representações de ponto flutuante.
				/// {Requer o Windows 8 ou posterior.}
				/// </summary>
				MFVideoPrimaries_XYZ = 10,
				/// <summary>
				/// DCI-P3.
				/// {Requer o Windows 10, versão 1703 ou posterior.}
				/// </summary>
				MFVideoPrimaries_DCI_P3 = 11,
				/// <summary>
				/// Sistema de codificação de cores da Academia.
				/// {Requer o Windows 10, versão 1703 ou posterior.}
				/// </summary>
				MFVideoPrimaries_ACES = 12,
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoPrimaries_Last = (MFVideoPrimaries_ACES + 1),
				/// <summary>
				/// Reservados. Este membro força o tipo de enumeração para compilar como um valor DWORD.
				/// </summary>
				MFVideoPrimaries_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (_MFVideoRotationFormat) - Enumera as rotações da imagem de vídeo no sentido anti-horário.
			/// Essa enumeração é usada com o atributo MF_MT_VIDEO_ROTATION.
			/// </summary>
			public enum class CA_MFVideoRotationFormat
			{
				/// <summary>
				/// A imagem não é girada.
				/// </summary>
				MFVideoRotationFormat_0 = 0,
				/// <summary>
				/// A imagem é girada 90 graus no sentido anti-horário.
				/// </summary>
				MFVideoRotationFormat_90 = 90,
				/// <summary>
				/// A imagem é girada 180 graus.
				/// </summary>
				MFVideoRotationFormat_180 = 180,
				/// <summary>
				/// A imagem é girada 270 graus no sentido anti-horário.
				/// </summary>
				MFVideoRotationFormat_270 = 270
			};

			/// <summary>
			/// (MFVideoTransferMatrix) - Enumera as matrizes de conversão entre Y'PbPr(Component Video) 
			/// e Studio R'G'B'.
			/// Essa enumeração é usada com o atributo MF_MT_YUV_MATRIX.
			/// </summary>
			public enum class CA_MFVideoTransferMatrix
			{
				/// <summary>
				/// Matriz de transferência desconhecida. Trate como MFVideoTransferMatrix_BT709.
				/// </summary>
				MFVideoTransferMatrix_Unknown = 0,
				/// <summary>
				/// Matriz de transferência de ITU-R BT. 709.
				/// </summary>
				MFVideoTransferMatrix_BT709 = 1,
				/// <summary>
				/// Matriz de transferência de ITU-R BT. 601. Também usado para SMPTE 170 e ITU-R BT. 470-2 sistema B,G.
				/// </summary>
				MFVideoTransferMatrix_BT601 = 2,
				/// <summary>
				/// Matriz de transferência de SMPTE 240M.
				/// </summary>
				MFVideoTransferMatrix_SMPTE240M = 3,
				/// <summary>
				/// Sem documentação!
				/// </summary>
				MFVideoTransferMatrix_BT2020_10 = 4,
				/// <summary>
				/// Sem documentação!
				/// </summary>
				MFVideoTransferMatrix_BT2020_12 = 5,
				/// <summary>
				/// Reservados.
				/// </summary>
				MFVideoTransferMatrix_Last = (MFVideoTransferMatrix_BT2020_12 + 1),
				/// <summary>
				/// Reservados. Este membro força o tipo de enumeração para compilar como um valor DWORD .
				/// </summary>
				MFVideoTransferMatrix_ForceDWORD = 0x7fffffff
			};
			
			/// <summary>
			/// (MediaEventType)[FALTA DOCUMENTAR] - Enumera todos os tipos de eventos do Media Foundation. Alguns eventos podem não ter suporte.
			/// </summary>
			public enum class CA_MediaEventType
			{
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEUnknown = 0,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEError = 1,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEExtendedType = 2,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MENonFatalError = 3,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEGenericV1Anchor = MENonFatalError,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionUnknown = 100,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionTopologySet = 101,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionTopologiesCleared = 102,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionStarted = 103,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionPaused = 104,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionStopped = 105,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionClosed = 106,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionEnded = 107,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionRateChanged = 108,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionScrubSampleComplete = 109,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionCapabilitiesChanged = 110,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionTopologyStatus = 111,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionNotifyPresentationTime = 112,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MENewPresentation = 113,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MELicenseAcquisitionStart = 114,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MELicenseAcquisitionCompleted = 115,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEIndividualizationStart = 116,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEIndividualizationCompleted = 117,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEnablerProgress = 118,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEnablerCompleted = 119,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEPolicyError = 120,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEPolicyReport = 121,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEBufferingStarted = 122,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEBufferingStopped = 123,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEConnectStart = 124,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEConnectEnd = 125,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEReconnectStart = 126,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEReconnectEnd = 127,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MERendererEvent = 128,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionStreamSinkFormatChanged = 129,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESessionV1Anchor = MESessionStreamSinkFormatChanged,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceUnknown = 200,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceStarted = 201,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamStarted = 202,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceSeeked = 203,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSeeked = 204,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MENewStream = 205,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEUpdatedStream = 206,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceStopped = 207,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamStopped = 208,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourcePaused = 209,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamPaused = 210,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEndOfPresentation = 211,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEndOfStream = 212,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEMediaSample = 213,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamTick = 214,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamThinMode = 215,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamFormatChanged = 216,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceRateChanged = 217,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEndOfPresentationSegment = 218,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceCharacteristicsChanged = 219,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceRateChangeRequested = 220,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceMetadataChanged = 221,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESequencerSourceTopologyUpdated = 222,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESourceV1Anchor = MESequencerSourceTopologyUpdated,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESinkUnknown = 300,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkStarted = 301,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkStopped = 302,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkPaused = 303,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkRateChanged = 304,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkRequestSample = 305,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkMarker = 306,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkPrerolled = 307,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkScrubSampleComplete = 308,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkFormatChanged = 309,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkDeviceChanged = 310,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEQualityNotify = 311,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESinkInvalidated = 312,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionNameChanged = 313,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionVolumeChanged = 314,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionDeviceRemoved = 315,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionServerShutdown = 316,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionGroupingParamChanged = 317,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionIconChanged = 318,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionFormatChanged = 319,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionDisconnected = 320,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEAudioSessionExclusiveModeOverride = 321,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESinkV1Anchor = MEAudioSessionExclusiveModeOverride,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionVolumeChanged = 322,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionDeviceRemoved = 323,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionFormatChanged = 324,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionDisconnected = 325,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionExclusiveModeOverride = 326,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MECaptureAudioSessionServerShutdown = 327,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MESinkV2Anchor = MECaptureAudioSessionServerShutdown,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METrustUnknown = 400,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEPolicyChanged = 401,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEContentProtectionMessage = 402,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEPolicySet = 403,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METrustV1Anchor = MEPolicySet,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseBackupCompleted = 500,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseBackupProgress = 501,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseRestoreCompleted = 502,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseRestoreProgress = 503,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseAcquisitionCompleted = 506,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMIndividualizationCompleted = 508,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMIndividualizationProgress = 513,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMProximityCompleted = 514,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMLicenseStoreCleaned = 515,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMRevocationDownloadCompleted = 516,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEWMDRMV1Anchor = MEWMDRMRevocationDownloadCompleted,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformUnknown = 600,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformNeedInput = (METransformUnknown + 1),
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformHaveOutput = (METransformNeedInput + 1),
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformDrainComplete = (METransformHaveOutput + 1),
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformMarker = (METransformDrainComplete + 1),
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				METransformInputStreamStateChanged = (METransformMarker + 1),
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEByteStreamCharacteristicsChanged = 700,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEVideoCaptureDeviceRemoved = 800,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEVideoCaptureDevicePreempted = 801,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEStreamSinkFormatInvalidated = 802,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEEncodingParameters = 803,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEContentProtectionMetadata = 900,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEDeviceThermalStateChanged = 950,
				/// <summary>
				/// Tipo do valor no evento: 
				/// Descrição: 
				/// </summary>
				MEReservedMax = 10000
			};

			/// <summary>
			/// (Original) - Enumera as possibilidades para se recuperar um evento do gerador de eventos de forma síncrona.
			/// </summary>
			public enum class CA_MF_GET_FLAGS_EVENT
			{
				/// <summary>
				/// O método bloqueia até que o gerador de eventos enfileire um evento.
				/// </summary>
				Block = 0,

				/// <summary>
				/// O método retorna imediatamente.
				/// </summary>
				CA_MF_EVENT_FLAG_NO_WAIT = MF_EVENT_FLAG_NO_WAIT,
			};

			/// <summary>
			/// Enumera o comportamento do método de conclusão de chamada Assincrona (Invoke) notificado pelo evento OnInvoke
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFASYNC_BEHAVIOR
			{
				/// <summary>
				/// O retorno de chamada não demora muito para ser concluído, mas não possui restrições específicas sobre quais chamadas do sistema ele faz. 
				/// O retorno de chamada geralmente leva menos de 30 milissegundos para ser concluído.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// O retorno de chamada faz um processamento muito mínimo. Demora menos de 1 milissegundo para ser concluído.
				/// O retorno de chamada deve ser chamado a partir de uma das seguintes filas de trabalho:
				/// MFASYNC_CALLBACK_QUEUE_IO Ou MFASYNC_CALLBACK_QUEUE_TIMER				
				/// </summary>
				Flags_MFASYNC_FAST_IO_PROCESSING_CALLBACK = MFASYNC_FAST_IO_PROCESSING_CALLBACK,

				/// <summary>
				/// Implica MFASYNC_FAST_IO_PROCESSING_CALLBACK , com a restrição adicional de que o retorno de chamada não processe (menos de 50 microssegundos) 
				/// e a única chamada de sistema que ele faz é SetEvent. O retorno de chamada deve ser chamado a partir de uma das seguintes filas de trabalho:
				/// MFASYNC_CALLBACK_QUEUE_IO Ou MFASYNC_CALLBACK_QUEUE_TIMER
				/// </summary>
				Flags_MFASYNC_SIGNAL_CALLBACK = MFASYNC_SIGNAL_CALLBACK,

				/// <summary>
				/// Bloqueio de retorno de chamada.
				/// </summary>
				Flags_MFASYNC_BLOCKING_CALLBACK = MFASYNC_BLOCKING_CALLBACK,

				/// <summary>
				/// Resposta de retorno
				/// </summary>
				Flags_MFASYNC_REPLY_CALLBACK = MFASYNC_REPLY_CALLBACK,
			};

			/// <summary>
			/// Enumera todos os identificadores de fila de trabalho padrão do Media Foundation.
			/// </summary>
			public enum class CA_MFASYNC_CALLBACK_QUEUE : UINT32
			{
				/// <summary>
				/// Fila de trabalho indefinida.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_UNDEFINED = MFASYNC_CALLBACK_QUEUE_UNDEFINED,

				/// <summary>
				/// Na maioria dos casos, os aplicativos devem usar MFASYNC_CALLBACK_QUEUE_MULTITHREADED . 
				/// Esta fila de trabalho é usada para operações síncronas. Usando a fila de trabalho padrão pode correr o risco de deadlocking
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_STANDARD = MFASYNC_CALLBACK_QUEUE_STANDARD,

				/// <summary>
				/// Não é para uso geral de aplicativos.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_RT = MFASYNC_CALLBACK_QUEUE_RT,

				/// <summary>
				/// Não para uso geral de aplicativos. 
				/// Essa fila de trabalho é usada internamente para operações de E / S, como leitura de arquivos e leitura da rede.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_IO = MFASYNC_CALLBACK_QUEUE_IO,

				/// <summary>
				/// Não para uso geral de aplicativos. 
				/// Essa fila de trabalho é usada para retornos periódicos e itens de trabalho planejados.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_TIMER = MFASYNC_CALLBACK_QUEUE_TIMER,

				/// <summary>
				/// Esta fila de trabalho multithread deve ser usada na maioria dos casos. 
				/// Essa fila de trabalho é usada para operações assíncronas em toda a Media Foundation.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_MULTITHREADED = MFASYNC_CALLBACK_QUEUE_MULTITHREADED,

				/// <summary>
				/// Não para uso geral de aplicativos. Os aplicativos devem usar (MFASYNC_CALLBACK_QUEUE_MULTITHREADED).
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_LONG_FUNCTION = MFASYNC_CALLBACK_QUEUE_LONG_FUNCTION,

				/// <summary>
				/// Máscara de bits para distinguir filas de trabalho de plataforma daquelas criadas chamando MFAllocateWorkQueue. 
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_PRIVATE_MASK = MFASYNC_CALLBACK_QUEUE_PRIVATE_MASK,

				/// <summary>
				/// Todas as filas de trabalho da plataforma.
				/// </summary>
				CA_MFASYNC_CALLBACK_QUEUE_ALL = MFASYNC_CALLBACK_QUEUE_ALL

			};

			/// <summary>
			/// (MF_OBJECT_TYPE) - Enumera todos os tipos de objeto que o resolvedor de mídia(ICarenMFSourceResolver) pode criar.
			/// </summary>
			public enum class CA_MF_OBJECT_TYPE
			{
				/// <summary>
				/// Fonte de mídia. Você pode consultar o objeto para a interface (ICarenMFMediaSource).
				/// </summary>
				MF_OBJECT_MEDIASOURCE = 0,

				/// <summary>
				/// Fluxo de bytes. Você pode consultar o objeto para a interface (ICarenMFByteStream).
				/// </summary>
				MF_OBJECT_BYTESTREAM = (MF_OBJECT_MEDIASOURCE + 1),

				/// <summary>
				/// Tipo inválido.
				/// </summary>
				MF_OBJECT_INVALID = (MF_OBJECT_BYTESTREAM + 1)
			};
			
			/// <summary>
			/// (D3DFORMAT) - Enumera os vários tipos de formatos de superfície(D3D9).
			/// </summary>
			public enum class CA_D3DFORMAT
			{
				D3DFMT_UNKNOWN = 0,

				D3DFMT_R8G8B8 = 20,
				D3DFMT_A8R8G8B8 = 21,
				D3DFMT_X8R8G8B8 = 22,
				D3DFMT_R5G6B5 = 23,
				D3DFMT_X1R5G5B5 = 24,
				D3DFMT_A1R5G5B5 = 25,
				D3DFMT_A4R4G4B4 = 26,
				D3DFMT_R3G3B2 = 27,
				D3DFMT_A8 = 28,
				D3DFMT_A8R3G3B2 = 29,
				D3DFMT_X4R4G4B4 = 30,
				D3DFMT_A2B10G10R10 = 31,
				D3DFMT_A8B8G8R8 = 32,
				D3DFMT_X8B8G8R8 = 33,
				D3DFMT_G16R16 = 34,
				D3DFMT_A2R10G10B10 = 35,
				D3DFMT_A16B16G16R16 = 36,

				D3DFMT_A8P8 = 40,
				D3DFMT_P8 = 41,

				D3DFMT_L8 = 50,
				D3DFMT_A8L8 = 51,
				D3DFMT_A4L4 = 52,

				D3DFMT_V8U8 = 60,
				D3DFMT_L6V5U5 = 61,
				D3DFMT_X8L8V8U8 = 62,
				D3DFMT_Q8W8V8U8 = 63,
				D3DFMT_V16U16 = 64,
				D3DFMT_A2W10V10U10 = 67,

				D3DFMT_UYVY = MAKEFOURCC('U', 'Y', 'V', 'Y'),
				D3DFMT_R8G8_B8G8 = MAKEFOURCC('R', 'G', 'B', 'G'),
				D3DFMT_YUY2 = MAKEFOURCC('Y', 'U', 'Y', '2'),
				D3DFMT_G8R8_G8B8 = MAKEFOURCC('G', 'R', 'G', 'B'),
				D3DFMT_DXT1 = MAKEFOURCC('D', 'X', 'T', '1'),
				D3DFMT_DXT2 = MAKEFOURCC('D', 'X', 'T', '2'),
				D3DFMT_DXT3 = MAKEFOURCC('D', 'X', 'T', '3'),
				D3DFMT_DXT4 = MAKEFOURCC('D', 'X', 'T', '4'),
				D3DFMT_DXT5 = MAKEFOURCC('D', 'X', 'T', '5'),

				D3DFMT_D16_LOCKABLE = 70,
				D3DFMT_D32 = 71,
				D3DFMT_D15S1 = 73,
				D3DFMT_D24S8 = 75,
				D3DFMT_D24X8 = 77,
				D3DFMT_D24X4S4 = 79,
				D3DFMT_D16 = 80,

				D3DFMT_D32F_LOCKABLE = 82,
				D3DFMT_D24FS8 = 83,
				D3DFMT_D32_LOCKABLE = 84,
				D3DFMT_S8_LOCKABLE = 85,
				D3DFMT_L16 = 81,
				D3DFMT_VERTEXDATA = 100,
				D3DFMT_INDEX16 = 101,
				D3DFMT_INDEX32 = 102,
				D3DFMT_Q16W16V16U16 = 110,
				D3DFMT_MULTI2_ARGB8 = MAKEFOURCC('M', 'E', 'T', '1'),
				D3DFMT_R16F = 111,
				D3DFMT_G16R16F = 112,
				D3DFMT_A16B16G16R16F = 113,
				D3DFMT_R32F = 114,
				D3DFMT_G32R32F = 115,
				D3DFMT_A32B32G32R32F = 116,
				D3DFMT_CxV8U8 = 117,
				D3DFMT_A1 = 118,
				D3DFMT_A2B10G10R10_XR_BIAS = 119,
				D3DFMT_BINARYBUFFER = 199,
			};

			/// <summary>
			/// (D3D_DRIVER_TYPE) - Enumera todas as opções de tipo de Driver para criação de um dispositovo D3D 11.
			/// </summary>
			public enum class CA_D3D_DRIVER_TYPE
			{
				/// <summary>
				/// O tipo de driver é desconhecido.
				/// </summary>
				D3D_DRIVER_TYPE_UNKNOWN = 0,

				/// <summary>
				/// Um driver de hardware, que implementa recursos de Direct3D no hardware. Este é o principal driver que você deve usar em seus aplicativos Direct3D, 
				/// porque ele fornece o melhor desempenho. Um driver de hardware usa aceleração de hardware (Hardware Suportado), mas também pode usar o software para 
				/// as peças do encanamento que não são suportadas no hardware. Este tipo de driver é muitas vezes referido como uma camada de abstração de hardware ou o HAL.
				/// </summary>
				D3D_DRIVER_TYPE_HARDWARE = (D3D_DRIVER_TYPE_UNKNOWN + 1),

				/// <summary>
				/// Um driver de referência, que é uma implementação de software que suporta cada recurso Direct3D. Um driver de referência é projetado para precisão ao invés 
				/// da velocidade e como resultado é lenta mas precisos. A porção do rasterizador do driver faz uso de CPU especial instruções sempre que pode, mas não se destina 
				/// para aplicações de varejo; usá-lo apenas para o recurso de testes, demonstração de funcionalidade, depuração ou verificação de erros em outros motoristas. 
				/// O dispositivo de referência para esse driver é instalado o Windows SDK 8.0 ou mais tarde e destina-se apenas como uma ajuda de depuração para fins de desenvolvimento. 
				/// Este driver pode ser referido como um driver REF, um driver de referência ou um rasterizador de referência.
				/// </summary>
				D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1),

				/// <summary>
				/// Um driver NULL, que é um driver de referência sem capacidade de processar. Este driver é comumente usado para depuração chamadas de API de renderização-não, 
				/// não é apropriado para aplicações de varejo. Esse driver é instalado pelo SDK do DirectX.
				/// </summary>
				D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),

				/// <summary>
				/// Um driver de software, que é um driver totalmente implementado no software. A implementação de software não se destina a uma aplicação de alto desempenho devido ao 
				/// seu desempenho muito lento.
				/// </summary>
				D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1),

				/// <summary>
				/// Um driver de dobra, que é um rasterizador de software de alto desempenho. O rasterizador suporta níveis de recurso 9_1 através de 10_1 nível com uma implementação de 
				/// software de alto desempenho. Para obter mais informações sobre limitações criando um dispositivo de dobra em certos níveis de recurso, consulte limitações criando 
				/// WARP e dispositivos de referência. Para obter mais informações sobre como usar um driver de dobra, consulte Guia de Windows Advanced Rasterization Platform (WARP) 
				/// em profundidade.
				/// </summary>
				D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)
			};

			/// <summary>
			/// (D3D_FEATURE_LEVEL) - Descreve o conjunto de recursos orientados por um dispositivo Direct3D.
			/// </summary>
			public enum class CA_D3D_FEATURE_LEVEL
			{
				/// <summary>
				/// Características de alvos suportadas pelo [recurso level](/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro) 9.1, incluindo (Shader Model 2.
				/// </summary>
				D3D_FEATURE_LEVEL_9_1 = 0x9100,

				/// <summary>
				/// Características de alvos suportadas pelo [recurso level](/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro) 9.2, incluindo (Shader Model 2).
				/// </summary>
				D3D_FEATURE_LEVEL_9_2 = 0x9200,

				/// <summary>
				/// Características de alvos suportadas pelo [recurso level](/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro) 9.3, incluindo o (Shader Model 2.0b).
				/// </summary>
				D3D_FEATURE_LEVEL_9_3 = 0x9300,

				/// <summary>
				/// Características de alvos suportadas pelo Direct3D 10.0, incluindo (Shader Model 4).
				/// </summary>
				D3D_FEATURE_LEVEL_10_0 = 0xa000,

				/// <summary>
				/// Recursos de alvos suportados pelo Direct3D 10.1, incluindo (Shader Model 4).
				/// </summary>
				D3D_FEATURE_LEVEL_10_1 = 0xa100,

				/// <summary>
				/// Características de alvos suportadas pelo Direct3D 11.0, incluindo (Shader Model 5).
				/// </summary>
				D3D_FEATURE_LEVEL_11_0 = 0xb000,

				/// <summary>
				/// Características de alvos suportadas pelo Direct3D 11.1, incluindo (Shader Model 5) e lógico misturam operações. Este nível de recurso requer um driver de exibição 
				/// que é implementado pelo menos a WDDM para Windows 8 (WDDM 1.2).
				/// </summary>
				D3D_FEATURE_LEVEL_11_1 = 0xb100,

				/// <summary>
				/// Características de alvos suportadas pelo Direct3D 12.0, incluindo (Shader Model 5).
				/// </summary>
				D3D_FEATURE_LEVEL_12_0 = 0xc000,

				/// <summary>
				/// Características de alvos suportadas pelo Direct3D 12.1, incluindo (Shader Model 5).
				/// </summary>
				D3D_FEATURE_LEVEL_12_1 = 0xc100
			};

			/// <summary>
			/// (D3D11_CREATE_DEVICE_FLAG) - Descreve os parâmetros que são usados para criar um dispositivo.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_CREATE_DEVICE_FLAG
			{
				/// <summary>
				/// Define que não vai utilizar nenhum flag dessa enumeração.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Use esse sinalizador se seu aplicativo só irá chamar métodos de Direct3D 11 interfaces de um único segmento. Por padrão, o objeto ID3D11Device é thread-safe. Ao usar esse sinalizador, 
				/// você pode aumentar o desempenho. No entanto, se você usar este sinalizador e o aplicativo chama métodos de Direct3D 11 interfaces de vários threads, comportamento indefinido pode resultar.
				/// </summary>
				D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,

				/// <summary>
				/// Cria um dispositivo que ofereça suporte a depuração de camada.
				/// Para usar esse sinalizador, você deve ter o D3D11* SDKLayers.dll instalado; caso contrário, falha na criação do dispositivo.Para obter D3D11_1SDKLayers.dll, instale o SDK para Windows 8.
				/// </summary>
				D3D11_CREATE_DEVICE_DEBUG = 0x2,

				/// <summary>
				/// (NÂO SUPORTADO PELO D3D 11)
				/// </summary>
				D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,

				/// <summary>
				/// Impede que vários threads sendo criado. Quando este sinalizador é usado com um dispositivo de Windows Advanced Rasterization Platform (WARP), sem segmentos adicionais serão criados pela 
				/// dobra e todos rasterization ocorrerá no thread de chamada. Este sinalizador não é recomendado para uso geral.
				/// </summary>
				D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,

				/// <summary>
				/// Cria um dispositivo que suporta formatos BGRA (DXGI_FORMAT_B8G8R8A8_UNORM e DXGI_FORMAT_B8G8R8A8_UNORM_SRGB). Todos os 10level9 e hardware superior com WDDM 1.1 + drivers suporte BGRA formatos.
				/// [ATENCAO] - Necessária para a interoperabilidade de Direct2D com recursos de Direct3D.
				/// </summary>
				D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,

				/// <summary>
				/// Faz com que o dispositivo e o driver para manter a informação que você pode usar para depuração de shader. O impacto exato desta bandeira irá variar de motorista para motorista.
				/// Para usar esse sinalizador, você deve ter o D3D11_1SDKLayers.dll instalado; caso contrário, falha na criação do dispositivo.O dispositivo criado oferece suporte a camada de depurar. 
				/// Para obter D3D11_1SDKLayers.dll, instale o SDK para Windows 8.
				/// Se você usar este sinalizador e o driver atual não oferece suporte a sombreador de depuração, falha de criação do dispositivo. Depuração de sombreador requer um driver que é 
				/// implementado para o WDDM para o Windows 8 (WDDM 1.2).
				/// [ATENCAO] - Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,

				/// <summary>
				/// Faz com que o runtime Direct3D ignorar as configurações do registro que por sua vez sobre a camada de depurar. Você pode ativar a camada de depurar usando o Painel de 
				/// controle do DirectX que foi incluído como parte do SDK do DirectX. Tivemos a última versão do DirectX SDK de junho de 2010; Você pode baixá-lo do Centro de Download 
				/// da Microsoft. Você pode definir esse sinalizador em seu aplicativo, normalmente em compilações de versão só, para impedir que os usuários finais usando o Painel de 
				/// controle do DirectX para monitorar como o aplicativo usa o Direct3D.
				/// [ATENCAO] - Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,

				/// <summary>
				/// Uso este Sinalizar se o dispositivo irá produzir GPU cargas de trabalho que levam mais de dois segundos para completar e você deseja que o sistema operacional para
				/// permitir que terminem com sucesso. Se este sinalizador não estiver definido, o sistema operacional realiza recuperação e deteção de tempo limite quando ele detecta 
				/// um pacote GPU que levou mais de dois segundos para executar. Se este sinalizador estiver definido, o sistema operacional permite que um pacote de longa duração 
				/// executar sem resetar o GPU. Nós recomendamos não defina esse Sinalizar se o seu dispositivo precisa ser altamente sensível para que o sistema operacional pode detectar 
				/// e recuperar de tempos limite GPU. Recomendamos que defina esse Sinalizar se o seu dispositivo precisa executar tarefas em segundo plano demorado como computação, 
				/// reconhecimento de imagem e vídeo, codificação para permitir que tais tarefas concluir com êxito.
				/// </summary>
				D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,

				/// <summary>
				/// Força a criação do dispositivo Direct3D para falhar se o driver de exibição não é implementado para o WDDM para o Windows 8 (WDDM 1.2). Quando o driver de exibição 
				/// não é implementado para 1.2 WDDM, apenas um dispositivo Direct3D é criado com nível de recurso 9.1, 9.2 ou 9,3 suporta vídeo; Portanto, se este sinalizador estiver 
				/// definido, o tempo de execução cria o dispositivo Direct3D só para nível de recurso, 9.1, 9.2 ou 9.3. Recomendamos para não especificar esse sinalizador para aplicativos 
				/// que deseja favorecer capacidade Direct3D sobre vídeo. Se recurso nível 10 e superior está disponível, o runtime irá usar esse nível de recurso, independentemente do 
				/// suporte de vídeo. 
				/// Se você tentar criar um dispositivo Direct3D com tipo de driver, D3D_DRIVER_TYPE_NULL, D3D_DRIVER_TYPE_REFERENCE ou D3D_DRIVER_TYPE_SOFTWARE, 
				/// A criação do dispositivo vai falhar em qualquer nível de recurso, porque nenhum do drivers associados fornecem capacidade de vídeo. Se você tentar criar um dispositivo Direct3D 
				/// com tipo de driver D3D_DRIVER_TYPE_WARP, a criação de dispositivo for bem-sucedido para permitir que o software de fallback para o vídeo.
				/// </summary>
				D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800
			};

			/// <summary>
			/// (D3D11_COUNTER) - Opções para os contadores de desempenho.
			/// </summary>
			public enum class CA_D3D11_CONTADOR
			{
				/// <summary>
				/// Defina um contador de desempenho que é dependente do dispositivo de hardware.
				/// </summary>
				D3D11_COUNTER_DEVICE_DEPENDENT_0 = 0x40000000
			};

			/// <summary>
			/// (D3D11_COUNTER_TYPE) - Opções para os contadores de desempenho.
			/// </summary>
			public enum class CA_D3D11_TIPO_DADO_CONTADOR
			{
				/// <summary>
				/// 32-bit ponto flutuante.
				/// </summary>
				D3D11_COUNTER_TYPE_FLOAT32 = 0,
				/// <summary>
				/// 16-bit inteiro não assinado.
				/// </summary>
				D3D11_COUNTER_TYPE_UINT16 = (D3D11_COUNTER_TYPE_FLOAT32 + 1),
				/// <summary>
				/// 32-bit inteiro não assinado.
				/// </summary>
				D3D11_COUNTER_TYPE_UINT32 = (D3D11_COUNTER_TYPE_UINT16 + 1),
				/// <summary>
				/// 64-bit inteiro não assinado.
				/// </summary>
				D3D11_COUNTER_TYPE_UINT64 = (D3D11_COUNTER_TYPE_UINT32 + 1)
			};

			/// <summary>
			/// (D3D11_FEATURE) - Enumera as opções de recurso do Direct3D 11.
			/// Essa enumeração é usada ao consultar um motorista sobre o suporte para esses recursos.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_RECURSO
			{
				/// <summary>
				/// O driver oferece suporte multithreading. Para ver um exemplo de teste de um driver para suporte a multitarefa, consulte How To: verificar se há Driver Suporte. Consulte D3D11_FEATURE_DATA_THREADING.
				/// </summary>
				D3D11_FEATURE_THREADING = 0,
				/// <summary>
				/// Suporta o uso de shaders a precisão dupla em HLSL. Consulte D3D11_FEATURE_DATA_DOUBLES.
				/// </summary>
				D3D11_FEATURE_DOUBLES = (D3D11_FEATURE_THREADING + 1),
				/// <summary>
				/// Suporta os formatos em D3D11_FORMAT_SUPPORT. Consulte D3D11_FEATURE_DATA_FORMAT_SUPPORT.
				/// </summary>
				D3D11_FEATURE_FORMAT_SUPPORT = (D3D11_FEATURE_DOUBLES + 1),
				/// <summary>
				/// Suporta os formatos em D3D11_FORMAT_SUPPORT2. Consulte D3D11_FEATURE_DATA_FORMAT_SUPPORT2.
				/// </summary>
				D3D11_FEATURE_FORMAT_SUPPORT2 = (D3D11_FEATURE_FORMAT_SUPPORT + 1),
				/// <summary>
				/// Suporta compute shaders e buffers de crus e estruturados. Consulte D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS.
				/// </summary>
				D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS = (D3D11_FEATURE_FORMAT_SUPPORT2 + 1),
				/// <summary>
				/// Suporta Direct3D 11.1 opções de recurso. Consulte D3D11_FEATURE_DATA_D3D11_OPTIONS.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS = (D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS + 1),
				/// <summary>
				/// Oferece suporte à arquitetura de adaptador específico. Consulte D3D11_FEATURE_DATA_ARCHITECTURE_INFO.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_FEATURE_ARCHITECTURE_INFO = (D3D11_FEATURE_D3D11_OPTIONS + 1),
				/// <summary>
				/// Suporta Direct3D 9 opções de recurso. Consulte D3D11_FEATURE_DATA_D3D9_OPTIONS.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_FEATURE_D3D9_OPTIONS = (D3D11_FEATURE_ARCHITECTURE_INFO + 1),
				/// <summary>
				/// Oferece suporte a precisão mínima de shaders. Para mais informação sobre precisão mínima de HLSL, consulte usando precisão mínima de HLSL. Consulte D3D11_FEATURE_DATA_SHADER_MIN_PRECISION_SUPPORT.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT = (D3D11_FEATURE_D3D9_OPTIONS + 1),
				/// <summary>
				/// Suporta Direct3D 9 sombreamento recurso. Consulte D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.1.
				/// </summary>
				D3D11_FEATURE_D3D9_SHADOW_SUPPORT = (D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT + 1),
				/// <summary>
				/// Suporta Direct3D 11.2 opções de recurso. Consulte D3D11_FEATURE_DATA_D3D11_OPTIONS1.
				/// Direct3D 11: Este valor não é suportado até 11.2 Direct3D.
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS1 = (D3D11_FEATURE_D3D9_SHADOW_SUPPORT + 1),
				/// <summary>
				/// Suporta Direct3D 11.2 opções de instância. Consulte D3D11_FEATURE_DATA_D3D9_SIMPLE_INSTANCING_SUPPORT.
				/// Direct3D 11: Este valor não é suportado até 11.2 Direct3D.
				/// </summary>
				D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT = (D3D11_FEATURE_D3D11_OPTIONS1 + 1),
				/// <summary>
				/// Suporta Direct3D 11.2 opções de marcador. Consulte D3D11_FEATURE_DATA_MARKER_SUPPORT.
				/// Direct3D 11: Este valor não é suportado até 11.2 Direct3D.
				/// </summary>
				D3D11_FEATURE_MARKER_SUPPORT = (D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT + 1),
				/// <summary>
				/// Suporta Direct3D 9 opções de recurso, que inclui o Direct3D 9 sombreamento recurso e uma instância de apoio. Consulte D3D11_FEATURE_DATA_D3D9_OPTIONS1.
				/// Direct3D 11: Este valor não é suportado até 11.2 Direct3D.
				/// </summary>
				D3D11_FEATURE_D3D9_OPTIONS1 = (D3D11_FEATURE_MARKER_SUPPORT + 1),
				/// <summary>
				/// Suporta opções de recurso Direct3D 11.3 rasterization conservador. Consulte D3D11_FEATURE_DATA_D3D11_OPTIONS2.
				/// Direct3D 11: Este valor não é suportado até Direct3D 11.3.
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS2 = (D3D11_FEATURE_D3D9_OPTIONS1 + 1),
				/// <summary>
				/// Suporta opções de recurso Direct3D 11.4 rasterization conservador. Consulte D3D11_FEATURE_DATA_D3D11_OPTIONS3.
				/// Direct3D 11: Este valor não é suportado até 11, 4 Direct3D
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS3 = (D3D11_FEATURE_D3D11_OPTIONS2 + 1),
				/// <summary>
				/// Oferece suporte a endereços virtuais de GPU. Consulte D3D11_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT.
				/// </summary>
				D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT = (D3D11_FEATURE_D3D11_OPTIONS3 + 1),
				/// <summary>
				/// Suporta um único valor booleano para NV12 compartilhado texturas. Consulte D3D11_FEATURE_DATA_D3D11_OPTIONS4.
				/// Direct3D 11: Este valor não é suportado até 11,4 Direct3D.
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS4 = (D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT + 1),
				/// <summary>
				/// Oferece suporte a cache de sombreador, descrito em D3D11_FEATURE_DATA_SHADER_CACHE.
				/// </summary>
				D3D11_FEATURE_SHADER_CACHE = (D3D11_FEATURE_D3D11_OPTIONS4 + 1),
				/// <summary>
				/// Não possui documentação.
				/// </summary>
				D3D11_FEATURE_D3D11_OPTIONS5 = (D3D11_FEATURE_SHADER_CACHE + 1)
			};

			/// <summary>
			/// (DXGI_MEMORY_SEGMENT_GROUP)(FALTA DOCUMENTAR) - Enumera o grupo do segmento de memória para usar.
			/// </summary>
			public enum class CA_DXGI_MEMORY_SEGMENT_GROUP
			{
				/// <summary>
				/// O agrupamento de segmentos considerados locais para o adaptador de vídeo, e representa a memória mais rápida disponível para a GPU. 
				/// As aplicações devem atingir o grupo local do segmento como o tamanho-alvo para seu conjunto de trabalho.
				/// </summary>
				DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0,

				/// <summary>
				/// O agrupamento de segmentos considerados não locais para o adaptador de vídeo, podendo ter desempenho mais lento do que o grupo local.
				/// </summary>
				DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
			};

			/// <summary>
			/// (DXGI_FORMAT)(FALTA DOCUMENTAR) - Enumera formatos de dados de recursos, incluindo totalmente tipado e formatos sem especificação de tipo.
			/// </summary>
			public enum class CA_DXGI_FORMAT
			{
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_UNKNOWN = 0,
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_R32G32B32A32_UINT = 3,
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_R32G32B32A32_SINT = 4,
				DXGI_FORMAT_R32G32B32_TYPELESS = 5,
				DXGI_FORMAT_R32G32B32_FLOAT = 6,
				DXGI_FORMAT_R32G32B32_UINT = 7,
				DXGI_FORMAT_R32G32B32_SINT = 8,
				DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
				DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
				DXGI_FORMAT_R16G16B16A16_UNORM = 11,
				DXGI_FORMAT_R16G16B16A16_UINT = 12,
				DXGI_FORMAT_R16G16B16A16_SNORM = 13,
				DXGI_FORMAT_R16G16B16A16_SINT = 14,
				DXGI_FORMAT_R32G32_TYPELESS = 15,
				DXGI_FORMAT_R32G32_FLOAT = 16,
				DXGI_FORMAT_R32G32_UINT = 17,
				DXGI_FORMAT_R32G32_SINT = 18,
				DXGI_FORMAT_R32G8X24_TYPELESS = 19,
				DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
				DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
				DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
				DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
				DXGI_FORMAT_R10G10B10A2_UNORM = 24,
				DXGI_FORMAT_R10G10B10A2_UINT = 25,
				DXGI_FORMAT_R11G11B10_FLOAT = 26,
				DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
				DXGI_FORMAT_R8G8B8A8_UNORM = 28,
				DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
				DXGI_FORMAT_R8G8B8A8_UINT = 30,
				DXGI_FORMAT_R8G8B8A8_SNORM = 31,
				DXGI_FORMAT_R8G8B8A8_SINT = 32,
				DXGI_FORMAT_R16G16_TYPELESS = 33,
				DXGI_FORMAT_R16G16_FLOAT = 34,
				DXGI_FORMAT_R16G16_UNORM = 35,
				DXGI_FORMAT_R16G16_UINT = 36,
				DXGI_FORMAT_R16G16_SNORM = 37,
				DXGI_FORMAT_R16G16_SINT = 38,
				DXGI_FORMAT_R32_TYPELESS = 39,
				DXGI_FORMAT_D32_FLOAT = 40,
				DXGI_FORMAT_R32_FLOAT = 41,
				DXGI_FORMAT_R32_UINT = 42,
				DXGI_FORMAT_R32_SINT = 43,
				DXGI_FORMAT_R24G8_TYPELESS = 44,
				DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
				DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
				DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
				DXGI_FORMAT_R8G8_TYPELESS = 48,
				DXGI_FORMAT_R8G8_UNORM = 49,
				DXGI_FORMAT_R8G8_UINT = 50,
				DXGI_FORMAT_R8G8_SNORM = 51,
				DXGI_FORMAT_R8G8_SINT = 52,
				DXGI_FORMAT_R16_TYPELESS = 53,
				DXGI_FORMAT_R16_FLOAT = 54,
				DXGI_FORMAT_D16_UNORM = 55,
				DXGI_FORMAT_R16_UNORM = 56,
				DXGI_FORMAT_R16_UINT = 57,
				DXGI_FORMAT_R16_SNORM = 58,
				DXGI_FORMAT_R16_SINT = 59,
				DXGI_FORMAT_R8_TYPELESS = 60,
				DXGI_FORMAT_R8_UNORM = 61,
				DXGI_FORMAT_R8_UINT = 62,
				DXGI_FORMAT_R8_SNORM = 63,
				DXGI_FORMAT_R8_SINT = 64,
				DXGI_FORMAT_A8_UNORM = 65,
				DXGI_FORMAT_R1_UNORM = 66,
				DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
				DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
				DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
				DXGI_FORMAT_BC1_TYPELESS = 70,
				DXGI_FORMAT_BC1_UNORM = 71,
				DXGI_FORMAT_BC1_UNORM_SRGB = 72,
				DXGI_FORMAT_BC2_TYPELESS = 73,
				DXGI_FORMAT_BC2_UNORM = 74,
				DXGI_FORMAT_BC2_UNORM_SRGB = 75,
				DXGI_FORMAT_BC3_TYPELESS = 76,
				DXGI_FORMAT_BC3_UNORM = 77,
				DXGI_FORMAT_BC3_UNORM_SRGB = 78,
				DXGI_FORMAT_BC4_TYPELESS = 79,
				DXGI_FORMAT_BC4_UNORM = 80,
				DXGI_FORMAT_BC4_SNORM = 81,
				DXGI_FORMAT_BC5_TYPELESS = 82,
				DXGI_FORMAT_BC5_UNORM = 83,
				DXGI_FORMAT_BC5_SNORM = 84,
				DXGI_FORMAT_B5G6R5_UNORM = 85,
				DXGI_FORMAT_B5G5R5A1_UNORM = 86,
				DXGI_FORMAT_B8G8R8A8_UNORM = 87,
				DXGI_FORMAT_B8G8R8X8_UNORM = 88,
				DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
				DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
				DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
				DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
				DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
				DXGI_FORMAT_BC6H_TYPELESS = 94,
				DXGI_FORMAT_BC6H_UF16 = 95,
				DXGI_FORMAT_BC6H_SF16 = 96,
				DXGI_FORMAT_BC7_TYPELESS = 97,
				DXGI_FORMAT_BC7_UNORM = 98,
				DXGI_FORMAT_BC7_UNORM_SRGB = 99,
				DXGI_FORMAT_AYUV = 100,
				DXGI_FORMAT_Y410 = 101,
				DXGI_FORMAT_Y416 = 102,
				DXGI_FORMAT_NV12 = 103,
				DXGI_FORMAT_P010 = 104,
				DXGI_FORMAT_P016 = 105,
				DXGI_FORMAT_420_OPAQUE = 106,
				DXGI_FORMAT_YUY2 = 107,
				DXGI_FORMAT_Y210 = 108,
				DXGI_FORMAT_Y216 = 109,
				DXGI_FORMAT_NV11 = 110,
				DXGI_FORMAT_AI44 = 111,
				DXGI_FORMAT_IA44 = 112,
				DXGI_FORMAT_P8 = 113,
				DXGI_FORMAT_A8P8 = 114,
				DXGI_FORMAT_B4G4R4A4_UNORM = 115,

				DXGI_FORMAT_P208 = 130,
				DXGI_FORMAT_V208 = 131,
				/// <summary>
				/// 
				/// </summary>
				DXGI_FORMAT_V408 = 132,


				DXGI_FORMAT_FORCE_UINT = -1
			};

			/// <summary>
			/// (DXGI_USAGE)(FALTA DOCUMENTAR) - Enumera as opções de criação de recursos e superfície.
			/// </summary>
			public enum class CA_DXGI_USAGE
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_BACK_BUFFER = DXGI_USAGE_BACK_BUFFER,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_DISCARD_ON_PRESENT = DXGI_USAGE_DISCARD_ON_PRESENT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_READ_ONLY = DXGI_USAGE_READ_ONLY,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_RENDER_TARGET_OUTPUT = DXGI_USAGE_RENDER_TARGET_OUTPUT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_SHADER_INPUT = DXGI_USAGE_SHADER_INPUT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_SHARED = DXGI_USAGE_SHARED,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_USAGE_UNORDERED_ACCESS = DXGI_USAGE_UNORDERED_ACCESS,
			};

			/// <summary>
			/// (DXGI_SWAP_EFFECT)(FALTA DOCUMENTAR) - Enumera as opções para lidar com pixels em uma superfície de exibição depos de chamar ICarenDXGISwapChain1::Present1.
			/// </summary>
			public enum class CA_DXGI_SWAP_EFFECT
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_EFFECT_DISCARD = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_EFFECT_FLIP_DISCARD = 4
			};

			/// <summary>
			/// (DXGI_MODE_SCANLINE_ORDER)(FALTA DOCUMENTAR) - Enumera sinalizadores que indicando o método usado pela varredura para criar uma imagem em uma superfície.
			/// </summary>
			public enum class CA_DXGI_MODE_SCANLINE_ORDER
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
			};
		
			/// <summary>
			/// (DXGI_MODE_SCALING)(FALTA DOCUMENTAR) - Enumera sinalizadores que indicam como uma imagem é esticada para se ajustar à resolução de um determinado monitor.
			/// </summary>
			public enum class CA_DXGI_MODE_SCALING
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCALING_UNSPECIFIED = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCALING_CENTERED = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_MODE_SCALING_STRETCHED = 2
			};

			/// <summary>
			/// (DXGI_SCALING) - Enumera o comportamento de redimensionamento quando o tamanho do amortecedor traseiro(BackBuffer) não corresponde ao tamanho da saída do alvo.
			/// </summary>
			public enum class CA_DXGI_SCALING
			{
				/// <summary>
				/// Direciona a DXGI para fazer a escala de conteúdo de reserva para se adequar ao tamanho do alvo da apresentação.
				/// </summary>
				DXGI_SCALING_STRETCH = 0,
				/// <summary>
				/// Direciona dxgi para fazer o back-buffer conteúdo sem qualquer escala quando o tamanho do alvo de apresentação não é igual ao tamanho back-buffer. As bordas superiores do buffer traseiro e o alvo da apresentação são alinhadas junto. Se o estilo WS_EX_LAYOUTRTL é associado com o punho de HWND à janela de saída do alvo, as bordas direitas do tampão traseiro e o alvo da apresentação são alinhadas junto; caso contrário, as bordas esquerdas estão alinhadas juntas. Toda a área de alvo fora do tampão traseiro é enchida com a cor do fundo da janela.
				/// Este valor especifica que todas as áreas-alvo fora do buffer traseiro de uma cadeia de swap são preenchidos com a cor de fundo que você especifica em uma chamada para IDXGISwapChain1::SetBackgroundColor.
				/// </summary>
				DXGI_SCALING_NONE = 1,
				/// <summary>
				/// Direciona a DXGI para fazer a escala de conteúdo de reserva para se adequar ao tamanho da meta de apresentação, preservando a proporção de aspecto do buffer traseiro. Se o reserva reduzido não preencher a área de apresentação, ele será centrado com bordas pretas.
				/// Note-se que, com legado Win32 janela swapchains, isso funciona o mesmo que DXGI_SCALING_STRETCH.
				/// </summary>
				DXGI_SCALING_ASPECT_RATIO_STRETCH = 2
			};

			/// <summary>
			/// (DXGI_ALPHA_MODE )(FALTA DOCUMENTAR) - Enumera como identificar o valor alfa, comportamento de transparência de uma superfície.
			/// </summary>
			public enum class CA_DXGI_ALPHA_MODE : Int64
			{
				/// <summary>
				/// 
				/// </summary>
				DXGI_ALPHA_MODE_UNSPECIFIED = 0,
				/// <summary>
				/// 
				/// </summary>
				DXGI_ALPHA_MODE_PREMULTIPLIED = 1,
				/// <summary>
				/// 
				/// </summary>
				DXGI_ALPHA_MODE_STRAIGHT = 2,
				/// <summary>
				/// 
				/// </summary>
				DXGI_ALPHA_MODE_IGNORE = 3,
			};

			/// <summary>
			/// (DXGI_PRESENT Constantes)(FALTA DOCUMENTAR) - Enumera sinalizadores que especificam as opções para apresentar quadros à saída.
			/// </summary>
			public enum class CA_DXGI_PRESENT
			{
				/// <summary>
				/// 
				/// </summary>
				Zero = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_DO_NOT_SEQUENCE = DXGI_PRESENT_DO_NOT_SEQUENCE,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_TEST = DXGI_PRESENT_TEST,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_RESTART = DXGI_PRESENT_RESTART,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_DO_NOT_WAIT = DXGI_PRESENT_DO_NOT_WAIT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_RESTRICT_TO_OUTPUT = DXGI_PRESENT_RESTRICT_TO_OUTPUT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_STEREO_PREFER_RIGHT = DXGI_PRESENT_STEREO_PREFER_RIGHT,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_STEREO_TEMPORARY_MONO = DXGI_PRESENT_STEREO_TEMPORARY_MONO,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_USE_DURATION = DXGI_PRESENT_USE_DURATION,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_PRESENT_ALLOW_TEARING = DXGI_PRESENT_ALLOW_TEARING
			};

			/// <summary>
			/// (DXGI_SWAP_CHAIN_FLAG)(FALTA DOCUMENTAR) - Enumera sinalizadores que definem o comportamento da cadeia de swaps.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_DXGI_SWAP_CHAIN_FLAG
			{
				/// <summary>
				/// 
				/// </summary>
				CA_Zero = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_NONPREROTATED = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH = 2,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE = 4,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT = 8,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER = 16,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY = 32,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT = 64,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER = 128,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO = 256,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO = 512,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED = 1024,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING = 2048,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS = 4096
			};
			
			/// <summary>
			/// (ORIGINAL) - Enumera bandeiras de leitura da CPU. Essas bandeiras podem ser combinadas com um OR lógico.
			/// </summary>			
			[FlagsAttribute]
			[DataContractAttribute]
			public enum class CA_DXGI_MAP_FLAGS
			{
				/// <summary>
				/// (CONSTANTE) - Permitir o acesso à leitura da CPU.
				/// </summary>
				[EnumMemberAttribute]
				CA_DXGI_MAP_READ = DXGI_MAP_READ,

				/// <summary>
				/// (CONSTANTE) - Permitir o acesso à gravação da CPU.
				/// </summary>
				[EnumMemberAttribute]
				CA_DXGI_MAP_WRITE = DXGI_MAP_WRITE,

				/// <summary>
				/// (CONSTANTE) - Descarte o conteúdo anterior de um recurso quando for mapeado.
				/// </summary>
				[EnumMemberAttribute]
				CA_DXGI_MAP_DISCARD = DXGI_MAP_DISCARD
			};

			/// <summary>
			/// (DXGI_OVERLAY_SUPPORT_FLAG) - Enumera bandeiras que especificam suporte de sobreposição para verificar em uma 
			/// chamada para ICarenDXGIOutput3::ChecarSuporteOverlay.
			/// </summary>			
			[FlagsAttribute]
			[DataContractAttribute]
			public enum class CA_DXGI_OVERLAY_SUPPORT_FLAG
			{
				/// <summary>
				/// Não representa nada.
				/// </summary>
				[EnumMemberAttribute]
				CA_Zero = 0x0,

				/// <summary>
				/// Suporte direto sobreposição.
				/// </summary>
				[EnumMemberAttribute]
				CA_DXGI_OVERLAY_SUPPORT_FLAG_DIRECT = 0x1,

				/// <summary>
				/// Dimensionar o suporte de sobreposição.
				/// </summary>
				[EnumMemberAttribute]
				CA_DXGI_OVERLAY_SUPPORT_FLAG_SCALING = 0x2
			};

			/// <summary>
			/// (DXGI_COLOR_SPACE_TYPE)(FALTA DOCUMENTAR) - Enumera bandeiras que especificam tipos de espaço de cores(Color Space).
			/// </summary>	
			public enum class CA_DXGI_COLOR_SPACE_TYPE : Int64
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709 = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709 = 2,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020 = 3,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RESERVED = 4,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601 = 5,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601 = 6,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601 = 7,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709 = 8,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709 = 9,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020 = 10,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020 = 11,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 = 12,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020 = 13,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020 = 14,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020 = 15,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020 = 16,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020 = 17,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020 = 18,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 = 19,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709 = 20,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020 = 21,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709 = 22,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020 = 23,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020 = 24,
			};

			/// <summary>
			/// (DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG)- Enumera bandeiras que especificam suporte ao espaço de cores para a cadeia de swap.
			/// </summary>	
			public enum class CA_DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG
			{
				/// <summary>
				/// Não representa nada.
				/// </summary>
				CA_Zero = 0x0,

				/// <summary>
				/// O suporte ao espaço colorido está presente.
				/// </summary>
				DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x1,

				/// <summary>
				/// O suporte ao espaço de cores sobreposição está presente.
				/// </summary>
				DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_OVERLAY_PRESENT = 0x2

			};

			/// <summary>
			/// (DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG)- Enumera bandeiras que especificam suporte para espaço de cores sobreposição.
			/// </summary>	
			public enum class CA_DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG
			{
				/// <summary>
				/// Não represeneta nada.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O suporte ao espaço de cores sobreposição está presente.
				/// </summary>
				DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x1,
			};

			/// <summary>
			/// (DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS)- Enumera bandeiras que descrevem quais níveis de composição de hardware são suportados.
			/// </summary>	
			[FlagsAttribute]
			[DataContractAttribute]
			public enum class CA_DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS
			{
				/// <summary>
				/// Não represeneta nada.
				/// </summary>
				[EnumMemberAttribute]
				Zero = 0x0,

				/// <summary>
				/// Esta bandeira especifica que a composição do swapchain pode ser facilitada de forma performante usando 
				/// hardware para aplicativos de tela cheia.
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_FULLSCREEN = 1,

				/// <summary>
				/// Esta bandeira especifica que a composição do swapchain pode ser facilitada de forma performante usando 
				/// hardware para aplicativos janelas.
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_WINDOWED = 2,

				/// <summary>
				/// Esta bandeira especifica que a composição do swapchain facilitada usando hardware pode fazer com que o 
				/// cursor apareça esticado.
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_CURSOR_STRETCHED = 4
			};

			/// <summary>
			/// (DXGI_HDR_METADATA_TYPE)- Enumera bandeiras que especificam o tipo de metadados de cabeçalho.
			/// </summary>	
			[FlagsAttribute]
			[DataContractAttribute]
			public enum class CA_DXGI_HDR_METADATA_TYPE
			{
				/// <summary>
				/// Indica que não há metadados de cabeçalho.
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HDR_METADATA_TYPE_NONE = 0,

				/// <summary>
				/// Indica que os metadados de cabeçalho são mantidos pela estrutura DXGI_HDR_METADATA_HDR10.
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HDR_METADATA_TYPE_HDR10 = 1,

				/// <summary>
				/// Não possui documentação!
				/// </summary>
				[EnumMemberAttribute]
				DXGI_HDR_METADATA_TYPE_HDR10PLUS = 2
			};

			/// <summary>
			/// (DXGI_OUTDUPL_POINTER_SHAPE_TYPE)(FALTA DOCUMENTAR) - Enumera bandeiras que identificam o tipo de forma de ponteiro.
			/// </summary>
			public enum class CA_DXGI_OUTDUPL_POINTER_SHAPE_TYPE
			{
				Zero = 0x0,

				DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MONOCHROME = 0x1,

				DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR = 0x2,

				DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MASKED_COLOR = 0x4
			};

			/// <summary>
			/// (D3D11_FORMAT_SUPPORT)(FALTA DOCUMENTAR) - Enumera quais recursos são suportados por um determinado formato e dados dispositivo.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_FORMAT_SUPPORT
			{
				D3D11_FORMAT_SUPPORT_BUFFER = 0x1,
				D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER = 0x2,
				D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER = 0x4,
				D3D11_FORMAT_SUPPORT_SO_BUFFER = 0x8,
				D3D11_FORMAT_SUPPORT_TEXTURE1D = 0x10,
				D3D11_FORMAT_SUPPORT_TEXTURE2D = 0x20,
				D3D11_FORMAT_SUPPORT_TEXTURE3D = 0x40,
				D3D11_FORMAT_SUPPORT_TEXTURECUBE = 0x80,
				D3D11_FORMAT_SUPPORT_SHADER_LOAD = 0x100,
				D3D11_FORMAT_SUPPORT_SHADER_SAMPLE = 0x200,
				D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_COMPARISON = 0x400,
				D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_MONO_TEXT = 0x800,
				D3D11_FORMAT_SUPPORT_MIP = 0x1000,
				D3D11_FORMAT_SUPPORT_MIP_AUTOGEN = 0x2000,
				D3D11_FORMAT_SUPPORT_RENDER_TARGET = 0x4000,
				D3D11_FORMAT_SUPPORT_BLENDABLE = 0x8000,
				D3D11_FORMAT_SUPPORT_DEPTH_STENCIL = 0x10000,
				D3D11_FORMAT_SUPPORT_CPU_LOCKABLE = 0x20000,
				D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE = 0x40000,
				D3D11_FORMAT_SUPPORT_DISPLAY = 0x80000,
				D3D11_FORMAT_SUPPORT_CAST_WITHIN_BIT_LAYOUT = 0x100000,
				D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET = 0x200000,
				D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD = 0x400000,
				D3D11_FORMAT_SUPPORT_SHADER_GATHER = 0x800000,
				D3D11_FORMAT_SUPPORT_BACK_BUFFER_CAST = 0x1000000,
				D3D11_FORMAT_SUPPORT_TYPED_UNORDERED_ACCESS_VIEW = 0x2000000,
				D3D11_FORMAT_SUPPORT_SHADER_GATHER_COMPARISON = 0x4000000,
				D3D11_FORMAT_SUPPORT_DECODER_OUTPUT = 0x8000000,
				D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT = 0x10000000,
				D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_INPUT = 0x20000000,
				D3D11_FORMAT_SUPPORT_VIDEO_ENCODER = 0x40000000
			};

			/// <summary>
			/// (D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG) - Enumera bandeiras que 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG
			{
				/// <summary>
				/// Utilizado para da suporte.
				///</summary>
				Zero = 0x0,
				
				/// <summary>
				/// Indica verificar os níveis de qualidade multiamostrais de um recurso de azulejo.
				///</summary>
				D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE = 0x1
			};
			/// <summary>
			/// (D3D11_BLEND)(FALTA DOCUMENTAR) - Enumera misturas de fatores, que modulam os valores para o shader de pixel e alvo de renderização. 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_BLEND
			{
				D3D11_BLEND_ZERO = 1,

				D3D11_BLEND_ONE = 2,

				D3D11_BLEND_SRC_COLOR = 3,

				D3D11_BLEND_INV_SRC_COLOR = 4,

				D3D11_BLEND_SRC_ALPHA = 5,

				D3D11_BLEND_INV_SRC_ALPHA = 6,

				D3D11_BLEND_DEST_ALPHA = 7,

				D3D11_BLEND_INV_DEST_ALPHA = 8,

				D3D11_BLEND_DEST_COLOR = 9,

				D3D11_BLEND_INV_DEST_COLOR = 10,

				D3D11_BLEND_SRC_ALPHA_SAT = 11,

				D3D11_BLEND_BLEND_FACTOR = 14,

				D3D11_BLEND_INV_BLEND_FACTOR = 15,

				D3D11_BLEND_SRC1_COLOR = 16,

				D3D11_BLEND_INV_SRC1_COLOR = 17,

				D3D11_BLEND_SRC1_ALPHA = 18,

				D3D11_BLEND_INV_SRC1_ALPHA = 19
			};

			/// <summary>
			/// (D3D11_BLEND_OP)(FALTA DOCUMENTAR) - Enumera Operação de mesclagem RGB ou alfa.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_BLEND_OP
			{
				D3D11_BLEND_OP_ADD = 1,

				D3D11_BLEND_OP_SUBTRACT = 2,

				D3D11_BLEND_OP_REV_SUBTRACT = 3,

				D3D11_BLEND_OP_MIN = 4,

				D3D11_BLEND_OP_MAX = 5
			};

			/// <summary>
			/// (D3D11_LOGIC_OP)(FALTA DOCUMENTAR) - Enumera bandeiras que especificam operações lógicas para configurar para um alvo de renderização.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_LOGIC_OP
			{
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_CLEAR = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_SET = (CA_D3D11_LOGIC_OP_CLEAR + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_COPY = (CA_D3D11_LOGIC_OP_SET + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_COPY_INVERTED = (CA_D3D11_LOGIC_OP_COPY + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_NOOP = (CA_D3D11_LOGIC_OP_COPY_INVERTED + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_INVERT = (CA_D3D11_LOGIC_OP_NOOP + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_AND = (CA_D3D11_LOGIC_OP_INVERT + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_NAND = (CA_D3D11_LOGIC_OP_AND + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_OR = (CA_D3D11_LOGIC_OP_NAND + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_NOR = (CA_D3D11_LOGIC_OP_OR + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_XOR = (CA_D3D11_LOGIC_OP_NOR + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_EQUIV = (CA_D3D11_LOGIC_OP_XOR + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_AND_REVERSE = (CA_D3D11_LOGIC_OP_EQUIV + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_AND_INVERTED = (CA_D3D11_LOGIC_OP_AND_REVERSE + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_OR_REVERSE = (CA_D3D11_LOGIC_OP_AND_INVERTED + 1),
				/// <summary>
				/// 
				/// </summary>
				CA_D3D11_LOGIC_OP_OR_INVERTED = (CA_D3D11_LOGIC_OP_OR_REVERSE + 1)
			};

			/// <summary>
			/// (D3D11_USAGE)(FALTA DOCUMENTAR) - Identifica o uso de recursos esperados durante o processamento. O uso reflete diretamente se um recurso é acessível pela CPU e/ou a unidade de processamento gráfico (GPU).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_USAGE
			{
				/// <summary>
				/// 
				/// </summary>
				D3D11_USAGE_DEFAULT = 0,
				/// <summary>
				/// 
				/// </summary>
				D3D11_USAGE_IMMUTABLE = 1,
				/// <summary>
				/// 
				/// </summary>
				D3D11_USAGE_DYNAMIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D3D11_USAGE_STAGING = 3
			};

			/// <summary>
			/// (D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG) - Enumera bandeiras que são usadas para criar um objeto de estado de contexto de 
			/// dispositivo (ICarenD3DDeviceContextState).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG
			{
				/// <summary>
				/// Utilizado para da suporte.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Você usa esta bandeira se o seu aplicativo ligar ás apenas métodos das interfaces Direct3D 11 e Direct3D 10 de um único segmento. Por padrão, 
				/// Direct3D 11 e Direct3D 10 são seguros para thread. Usando esta bandeira, você pode aumentar o desempenho. No entanto, se você usar esta bandeira 
				/// e seu aplicativo chama métodos de vários segmentos, pode resultar em um comportamento indefinido.
				/// </summary>
				D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADED = 0x1
			};
			
			/// <summary>
			/// (D3D11_BIND_FLAG)(FALTA DOCUMENTAR) - Identifica como vincular um recurso ao pipeline.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_BIND_FLAG
			{
				D3D11_BIND_VERTEX_BUFFER = 0x1L,
				D3D11_BIND_INDEX_BUFFER = 0x2L,
				D3D11_BIND_CONSTANT_BUFFER = 0x4L,
				D3D11_BIND_SHADER_RESOURCE = 0x8L,
				D3D11_BIND_STREAM_OUTPUT = 0x10L,
				D3D11_BIND_RENDER_TARGET = 0x20L,
				D3D11_BIND_DEPTH_STENCIL = 0x40L,
				D3D11_BIND_UNORDERED_ACCESS = 0x80L,
				D3D11_BIND_DECODER = 0x200L,
				D3D11_BIND_VIDEO_ENCODER = 0x400L
			};

			/// <summary>
			/// (D3D11_CPU_ACCESS_FLAG)(FALTA DOCUMENTAR) - Enumera os tipos de acesso da CPU permitidos para um recurso.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_CPU_ACCESS_FLAG
			{
				NOREQUIRED = 0,
				D3D11_CPU_ACCESS_WRITE = 0x10000L,
				D3D11_CPU_ACCESS_READ = 0x20000L
			};

			/// <summary>
			/// (D3D11_RESOURCE_MISC_FLAG)(FALTA DOCUMENTAR) - Especifica dados para inicializar um sub-recurso.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_RESOURCE_MISC_FLAG
			{
				NOREQUIRED = 0,
				D3D11_RESOURCE_MISC_GENERATE_MIPS = 0x1L,
				D3D11_RESOURCE_MISC_SHARED = 0x2L,
				D3D11_RESOURCE_MISC_TEXTURECUBE = 0x4L,
				D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10L,
				D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20L,
				D3D11_RESOURCE_MISC_BUFFER_STRUCTURED = 0x40L,
				D3D11_RESOURCE_MISC_RESOURCE_CLAMP = 0x80L,
				D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX = 0x100L,
				D3D11_RESOURCE_MISC_GDI_COMPATIBLE = 0x200L,
				D3D11_RESOURCE_MISC_SHARED_NTHANDLE = 0x800L,
				D3D11_RESOURCE_MISC_RESTRICTED_CONTENT = 0x1000L,
				D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE = 0x2000L,
				D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER = 0x4000L,
				D3D11_RESOURCE_MISC_GUARDED = 0x8000L,
				D3D11_RESOURCE_MISC_TILE_POOL = 0x20000L,
				D3D11_RESOURCE_MISC_TILED = 0x40000L,
				D3D11_RESOURCE_MISC_HW_PROTECTED = 0x80000L
			};

			/// <summary>
			/// (D3D11_DEPTH_WRITE_MASK)(FALTA DOCUMENTAR) - Identifique a parte de um buffer de estêncil de profundidade para gravar dados de profundidade.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_DEPTH_WRITE_MASK
			{
				D3D11_DEPTH_WRITE_MASK_ZERO = 0,
				D3D11_DEPTH_WRITE_MASK_ALL = 1
			};

			/// <summary>
			/// (D3D11_COMPARISON_FUNC)(FALTA DOCUMENTAR) - Opções de comparação.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_COMPARISON_FUNC
			{
				D3D11_COMPARISON_NEVER = 1,
				D3D11_COMPARISON_LESS = 2,
				D3D11_COMPARISON_EQUAL = 3,
				D3D11_COMPARISON_LESS_EQUAL = 4,
				D3D11_COMPARISON_GREATER = 5,
				D3D11_COMPARISON_NOT_EQUAL = 6,
				D3D11_COMPARISON_GREATER_EQUAL = 7,
				D3D11_COMPARISON_ALWAYS = 8
			};

			/// <summary>
			/// (D3D11_STENCIL_OP)(FALTA DOCUMENTAR) - As operações de estêncil que podem ser executadas durante o teste de estêncil de profundidade.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D3D11_STENCIL_OP
			{
				D3D11_STENCIL_OP_KEEP = 1,
				D3D11_STENCIL_OP_ZERO = 2,
				D3D11_STENCIL_OP_REPLACE = 3,
				D3D11_STENCIL_OP_INCR_SAT = 4,
				D3D11_STENCIL_OP_DECR_SAT = 5,
				D3D11_STENCIL_OP_INVERT = 6,
				D3D11_STENCIL_OP_INCR = 7,
				D3D11_STENCIL_OP_DECR = 8
			};

			/// <summary>
			/// (D3D11_DSV_DIMENSION)(FALTA DOCUMENTAR) - Especifica como acessar um recurso usado em uma exibição de estêncil de profundidade.
			/// </summary>
			public enum class CA_D3D11_DSV_DIMENSION
			{
				D3D11_DSV_DIMENSION_UNKNOWN = 0,
				D3D11_DSV_DIMENSION_TEXTURE1D = 1,
				D3D11_DSV_DIMENSION_TEXTURE1DARRAY = 2,
				D3D11_DSV_DIMENSION_TEXTURE2D = 3,
				D3D11_DSV_DIMENSION_TEXTURE2DARRAY = 4,
				D3D11_DSV_DIMENSION_TEXTURE2DMS = 5,
				D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY = 6
			};

			/// <summary>
			/// (D3D11_DSV_FLAG)(FALTA DOCUMENTAR) - Opções de visualização de estêncil de profundidade.
			/// </summary>
			public enum class CA_D3D11_DSV_FLAG
			{
				NOREQUIRED = 0,
				D3D11_DSV_READ_ONLY_DEPTH = 0x1L,
				D3D11_DSV_READ_ONLY_STENCIL = 0x2L
			};

			/// <summary>
			/// (D3D11_INPUT_CLASSIFICATION)(FALTA DOCUMENTAR) - Enumera os tipos de dados contidos em um slot de entrada.
			/// </summary>
			public enum class CA_D3D11_INPUT_CLASSIFICATION
			{
				D3D11_INPUT_PER_VERTEX_DATA = 0,
				D3D11_INPUT_PER_INSTANCE_DATA = 1
			};

			/// <summary>
			/// (D3D11_QUERY)(FALTA DOCUMENTAR) - Enumera os tipos de consulta.
			/// </summary>
			public enum class CA_D3D11_QUERY
			{
				D3D11_QUERY_EVENT = 0,
				D3D11_QUERY_OCCLUSION = (D3D11_QUERY_EVENT + 1),
				D3D11_QUERY_TIMESTAMP = (D3D11_QUERY_OCCLUSION + 1),
				D3D11_QUERY_TIMESTAMP_DISJOINT = (D3D11_QUERY_TIMESTAMP + 1),
				D3D11_QUERY_PIPELINE_STATISTICS = (D3D11_QUERY_TIMESTAMP_DISJOINT + 1),
				D3D11_QUERY_OCCLUSION_PREDICATE = (D3D11_QUERY_PIPELINE_STATISTICS + 1),
				D3D11_QUERY_SO_STATISTICS = (D3D11_QUERY_OCCLUSION_PREDICATE + 1),
				D3D11_QUERY_SO_OVERFLOW_PREDICATE = (D3D11_QUERY_SO_STATISTICS + 1),
				D3D11_QUERY_SO_STATISTICS_STREAM0 = (D3D11_QUERY_SO_OVERFLOW_PREDICATE + 1),
				D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0 = (D3D11_QUERY_SO_STATISTICS_STREAM0 + 1),
				D3D11_QUERY_SO_STATISTICS_STREAM1 = (D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0 + 1),
				D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1 = (D3D11_QUERY_SO_STATISTICS_STREAM1 + 1),
				D3D11_QUERY_SO_STATISTICS_STREAM2 = (D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1 + 1),
				D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2 = (D3D11_QUERY_SO_STATISTICS_STREAM2 + 1),
				D3D11_QUERY_SO_STATISTICS_STREAM3 = (D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2 + 1),
				D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3 = (D3D11_QUERY_SO_STATISTICS_STREAM3 + 1)
			};

			/// <summary>
			/// (D3D11_FILL_MODE)(FALTA DOCUMENTAR) - Determina o modo de preenchimento a ser usado ao renderizar triângulos.
			/// </summary>
			public enum class CA_D3D11_FILL_MODE
			{
				D3D11_FILL_WIREFRAME = 2,
				D3D11_FILL_SOLID = 3
			};

			/// <summary>
			/// (D3D11_CULL_MODE)(FALTA DOCUMENTAR) - Indica que os triângulos voltados para uma determinada direção não são desenhados.
			/// </summary>
			public enum class CA_D3D11_CULL_MODE
			{
				D3D11_CULL_NONE = 1,
				D3D11_CULL_FRONT = 2,
				D3D11_CULL_BACK = 3
			};

			/// <summary>
			/// (D3D11_RTV_DIMENSION)(FALTA DOCUMENTAR) - Esses sinalizadores identificam o tipo de recurso que será visualizado como um destino de renderização..
			/// </summary>
			public enum class CA_D3D11_RTV_DIMENSION
			{
				D3D11_RTV_DIMENSION_UNKNOWN = 0,
				D3D11_RTV_DIMENSION_BUFFER = 1,
				D3D11_RTV_DIMENSION_TEXTURE1D = 2,
				D3D11_RTV_DIMENSION_TEXTURE1DARRAY = 3,
				D3D11_RTV_DIMENSION_TEXTURE2D = 4,
				D3D11_RTV_DIMENSION_TEXTURE2DARRAY = 5,
				D3D11_RTV_DIMENSION_TEXTURE2DMS = 6,
				D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY = 7,
				D3D11_RTV_DIMENSION_TEXTURE3D = 8
			};

			/// <summary>
			/// (D3D11_FILTER)(FALTA DOCUMENTAR) - Enumera as opções de filtragem durante a amostragem de textura.
			/// </summary>
			public enum class CA_D3D11_FILTER
			{
				D3D11_FILTER_MIN_MAG_MIP_POINT = 0,
				D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x1,
				D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
				D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
				D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
				D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
				D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,
				D3D11_FILTER_MIN_MAG_MIP_LINEAR = 0x15,
				D3D11_FILTER_ANISOTROPIC = 0x55,
				D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT = 0x80,
				D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
				D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
				D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
				D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
				D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
				D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
				D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
				D3D11_FILTER_COMPARISON_ANISOTROPIC = 0xd5,
				D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT = 0x100,
				D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x101,
				D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x104,
				D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x105,
				D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x110,
				D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x111,
				D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x114,
				D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR = 0x115,
				D3D11_FILTER_MINIMUM_ANISOTROPIC = 0x155,
				D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT = 0x180,
				D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR = 0x181,
				D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x184,
				D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR = 0x185,
				D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT = 0x190,
				D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x191,
				D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT = 0x194,
				D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR = 0x195,
				D3D11_FILTER_MAXIMUM_ANISOTROPIC = 0x1d5
			};

			/// <summary>
			/// (D3D11_TEXTURE_ADDRESS_MODE)(FALTA DOCUMENTAR) - Identifique uma técnica para resolver coordenadas de textura que estão fora dos limites de uma textura.
			/// </summary>
			public enum class CA_D3D11_TEXTURE_ADDRESS_MODE
			{
				D3D11_TEXTURE_ADDRESS_WRAP = 1,
				D3D11_TEXTURE_ADDRESS_MIRROR = 2,
				D3D11_TEXTURE_ADDRESS_CLAMP = 3,
				D3D11_TEXTURE_ADDRESS_BORDER = 4,
				D3D11_TEXTURE_ADDRESS_MIRROR_ONCE = 5
			};

			/// <summary>
			/// (D3D11_TEXTURE_LAYOUT)(FALTA DOCUMENTAR) - Enmera bandeiras que sspecificam opções de layout de textura.
			/// Esta enumeração controla o padrão de swizzle de texturas padrão e permite suporte ao mapa em texturas padrão.
			/// </summary>
			public enum class CA_D3D11_TEXTURE_LAYOUT
			{
				/// <summary>
				/// O layout de textura é indefinido e é selecionado pelo motorista.
				/// </summary>
				D3D11_TEXTURE_LAYOUT_UNDEFINED = 0,

				/// <summary>
				/// Os dados para a textura são armazenados em linha principal (às vezes chamado de pitch-linear).
				/// </summary>
				D3D11_TEXTURE_LAYOUT_ROW_MAJOR = 1,

				/// <summary>
				/// Uma textura padrão usa o padrão de swizzle padronizado.
				/// </summary>
				D3D11_TEXTURE_LAYOUT_64K_STANDARD_SWIZZLE = 2
			};

			/// <summary>
			/// (D3D11_SRV_DIMENSION)(FALTA DOCUMENTAR) - Esses sinalizadores identificam o tipo de recurso que será exibido como um recurso de sombreador.
			/// </summary>
			public enum class CA_D3D11_SRV_DIMENSION
			{
				D3D11_SRV_DIMENSION_UNKNOWN = 0,
				D3D11_SRV_DIMENSION_BUFFER = 1,
				D3D11_SRV_DIMENSION_TEXTURE1D = 2,
				D3D11_SRV_DIMENSION_TEXTURE1DARRAY = 3,
				D3D11_SRV_DIMENSION_TEXTURE2D = 4,
				D3D11_SRV_DIMENSION_TEXTURE2DARRAY = 5,
				D3D11_SRV_DIMENSION_TEXTURE2DMS = 6,
				D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY = 7,
				D3D11_SRV_DIMENSION_TEXTURE3D = 8,
				D3D11_SRV_DIMENSION_TEXTURECUBE = 9,
				D3D11_SRV_DIMENSION_TEXTURECUBEARRAY = 10,
				D3D11_SRV_DIMENSION_BUFFEREX = 11
			};

			/// <summary>
			/// (D3D11_UAV_DIMENSION)(FALTA DOCUMENTAR) - Opções de visualização de acesso não ordenado.
			/// </summary>
			public enum class CA_D3D11_UAV_DIMENSION
			{
				D3D11_UAV_DIMENSION_UNKNOWN = 0,
				D3D11_UAV_DIMENSION_BUFFER = 1,
				D3D11_UAV_DIMENSION_TEXTURE1D = 2,
				D3D11_UAV_DIMENSION_TEXTURE1DARRAY = 3,
				D3D11_UAV_DIMENSION_TEXTURE2D = 4,
				D3D11_UAV_DIMENSION_TEXTURE2DARRAY = 5,
				D3D11_UAV_DIMENSION_TEXTURE3D = 8
			};

			/// <summary>
			/// (D3D11_RAISE_FLAG) - Opção(s) para aumentar um erro para uma exceção não continuável.
			/// </summary>
			public enum class CA_D3D11_RAISE_FLAG
			{
				/// <summary>
				/// Suporte.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Levante um erro de driver interno para uma exceção não contínua.
				/// </summary>
				D3D11_RAISE_FLAG_DRIVER_INTERNAL_ERROR = 0x1L
			};

			/// <summary>
			/// (CLSCTX)(FALTA DOCUMENTAR) - Valores que são usados em chamadas de ativação para indicar os contextos de execução em que um objeto está a ser executado. Estes valores também são usados em chamadas
			/// para CoRegisterClassObject para indicar o conjunto de contextos de execução em que um objeto de classe é para ser feito disponível para solicitações construir instâncias.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_CLSCTX
			{
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_INPROC_SERVER = 0x1,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_INPROC_HANDLER = 0x2,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_LOCAL_SERVER = 0x4,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_INPROC_SERVER16 = 0x8,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_REMOTE_SERVER = 0x10,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_INPROC_HANDLER16 = 0x20,
				CLSCTX_RESERVED1 = 0x40,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_RESERVED2 = 0x80,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_RESERVED3 = 0x100,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_RESERVED4 = 0x200,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_NO_CODE_DOWNLOAD = 0x400,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_RESERVED5 = 0x800,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_NO_CUSTOM_MARSHAL = 0x1000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_NO_FAILURE_LOG = 0x4000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_DISABLE_AAA = 0x8000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ENABLE_AAA = 0x10000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_FROM_DEFAULT_CONTEXT = 0x20000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ACTIVATE_X86_SERVER = 0x40000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ACTIVATE_32_BIT_SERVER = CLSCTX_ACTIVATE_X86_SERVER,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ACTIVATE_64_BIT_SERVER = 0x80000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ENABLE_CLOAKING = 0x100000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_APPCONTAINER = 0x400000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ACTIVATE_AAA_AS_IU = 0x800000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_RESERVED6 = 0x1000000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_ACTIVATE_ARM32_SERVER = 0x2000000,
				/// <summary>
				/// 
				/// </summary>
				CLSCTX_PS_DLL = 0x80000000,
				/// <summary>
				/// 
				/// </summary>
				CA_CLSCTX_ALL = CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER
			};

			/// <summary>
			/// (DEVICE_STATE_XXX) - Enumera as constantes que indicam o estado atual de um dispositivo de áudio de ponto de extremidade.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_DEVICE_STATE_XXX
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// O dispositivo de ponto de extremidade de áudio está ativo. Ou seja, o adaptador de áudio que se conecta ao dispositivo de ponto de extremidade está presente e habilitado. Além disso, se o dispositivo 
				/// de ponto de extremidade se conecta a uma tomada no adaptador, o dispositivo de ponto de extremidade é conectado.
				/// </summary>
				CA_DEVICE_STATE_ACTIVE = 0x00000001,

				/// <summary>
				/// O dispositivo de ponto final de áudio está desactivado. O usuário desabilitou o dispositivo no painel de controle multimídia do Windows, mmsys. cpl. Para obter mais informações, consulte comentários.
				/// </summary>
				CA_DEVICE_STATE_DISABLED = 0x00000002,

				/// <summary>
				/// O dispositivo de ponto de extremidade de áudio não está presente porque o adaptador de áudio que se conecta ao dispositivo de ponto de extremidade foi removido do sistema ou o usuário desabilitou o
				/// dispositivo de adaptador no Gerenciador de dispositivos.
				/// </summary>
				CA_DEVICE_STATE_NOTPRESENT = 0x00000004,

				/// <summary>
				/// O dispositivo de ponto final de áudio está desligado. O adaptador de áudio que contém a tomada para o dispositivo de ponto de extremidade está presente e habilitado, mas o dispositivo de ponto de 
				/// extremidade não está conectado à tomada. Somente um dispositivo com detecção de presença de Jack pode estar nesse estado. Para obter mais informações sobre detecção de presença de Jack, consulte 
				/// dispositivos de ponto de extremidade de áudio.
				/// </summary>
				CA_DEVICE_STATE_UNPLUGGED = 0x00000008,

				/// <summary>
				/// Inclui dispositivos de ponto de extremidade de áudio em todos os Estados ativos, desabilitados, não presentes e desconectados.
				/// </summary>
				CA_DEVICE_STATEMASK_ALL = 0x0000000F

			};

			/// <summary>
			/// (ERole) - Enumera constantes que indicam a função que o sistema atribuiu a um dispositivo de ponto de extremidade de áudio.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_ERole
			{
				/// <summary>
				/// Jogos, sons de notificação do sistema e comandos de voz.
				/// </summary>
				eConsole = 0,

				/// <summary>
				/// Música, filmes, narração e gravação de música ao vivo.
				/// </summary>
				eMultimedia = (eConsole + 1),

				/// <summary>
				/// Comunicações de voz (conversando com outra pessoa).
				/// </summary>
				eCommunications = (eMultimedia + 1),

				/// <summary>
				/// O número de membros na enumeração Erole (sem contar o membro ERole_enum_count).
				/// </summary>
				ERole_enum_count = (eCommunications + 1)
			};

			/// <summary>
			/// (_MF2DBuffer_LockFlags) - Enumera os sinalizadores para o método de IMF2DBuffer2::Lock2DSize.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF2DBuffer_LockFlags
			{
				/// <summary>
				/// Reservado.
				/// </summary>
				MF2DBuffer_LockFlags_LockTypeMask = ((0x1 | 0x2) | 0x3),

				/// <summary>
				/// Bloquear o buffer para leitura.
				/// </summary>
				MF2DBuffer_LockFlags_Read = 0x1,

				/// <summary>
				/// Bloquear o buffer para a escrita.
				/// </summary>
				MF2DBuffer_LockFlags_Write = 0x2,

				/// <summary>
				/// Bloquear o buffer para leitura e escrita.
				/// </summary>
				MF2DBuffer_LockFlags_ReadWrite = 0x3,

				/// <summary>
				/// Reservado. Este membro obriga o tipo de enumeração para compilar como um valor DWORD.
				/// </summary>
				MF2DBuffer_LockFlags_ForceDWORD = 0x7fffffff
			};

			/// <summary>
			/// (_MFMEDIASOURCE_CHARACTERISTICS) - Enumera as características de uma fonte de mídia.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFMEDIASOURCE_CHARACTERISTICS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Este sinalizador indica uma fonte de dados que executa constantemente, como uma apresentação ao vivo. Se a fonte for parada e reiniciada em seguida, haverá uma lacuna no conteúdo.
				/// </summary>
				MFMEDIASOURCE_IS_LIVE = 0x1,

				/// <summary>
				/// A origem de mídia oferece suporte à busca.
				/// </summary>
				MFMEDIASOURCE_CAN_SEEK = 0x2,

				/// <summary>
				/// A fonte pode pausar.
				/// </summary>
				MFMEDIASOURCE_CAN_PAUSE = 0x4,

				/// <summary>
				/// A origem de mídia downloads de conteúdo. Demora muito tempo para procurar a partes do conteúdo que não tenham sido baixadas.
				/// </summary>
				MFMEDIASOURCE_HAS_SLOW_SEEK = 0x8,

				/// <summary>
				/// A origem de mídia oferece uma lista de reprodução, que pode conter mais de uma entrada. Após concluída a primeira entrada da lista de reprodução, a fonte de mídia sinaliza o início 
				/// de cada nova entrada de lista de reprodução através do envio de um evento MENewPresentation . O evento contém um descritor de apresentação para a entrada.
				/// </summary>
				MFMEDIASOURCE_HAS_MULTIPLE_PRESENTATIONS = 0x10,

				/// <summary>
				/// A origem de mídia pode pular para a frente na lista de reprodução. Aplica-se somente se o sinalizador MFMEDIASOURCE_HAS_MULTIPLE_PRESENTATIONS está presente.
				/// </summary>
				MFMEDIASOURCE_CAN_SKIPFORWARD = 0x20,

				/// <summary>
				/// A origem de mídia pode pular para trás na lista de reprodução.
				/// </summary>
				MFMEDIASOURCE_CAN_SKIPBACKWARD = 0x40,

				/// <summary>
				/// A origem de mídia não está usando atualmente a rede para receber o conteúdo. Hardware de rede pode introduzir uma economia de energia estado quando este bit for definido.
				/// </summary>
				MFMEDIASOURCE_DOES_NOT_USE_NETWORK = 0x80
			};

			/// <summary>
			/// (D3D11_CLEAR_FLAG)(FALTA DOCUMENTAR) - Especifica as partes do estêncil de profundidade para limpar.
			/// </summary>
			public enum class CA_D3D11_CLEAR_FLAG
			{
				/// <summary>
				/// 
				/// </summary>
				D3D11_CLEAR_DEPTH = 0x1L,

				/// <summary>
				/// 
				/// </summary>
				D3D11_CLEAR_STENCIL = 0x2L
			};

			/// <summary>
			/// (D3D11_COPY_FLAGS)(FALTA DOCUMENTAR) - Especifica como lidar com o conteúdo existente de um recurso durante uma operação de cópia ou atualização de uma região dentro desse recurso.
			/// </summary>
			public enum class CA_D3D11_COPY_FLAGS
			{
				/// <summary>
				/// Não representa nada.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O conteúdo existente do recurso não pode ser substituído.
				/// </summary>
				D3D11_COPY_NO_OVERWRITE = 0x1,

				/// <summary>
				/// O conteúdo existente do recurso é indefinido e pode ser descartado.
				/// </summary>
				D3D11_COPY_DISCARD = 0x2
			};

			/// <summary>
			/// (Original) - Enumera as possiveis prioridades de um Recurso. Essa enumeração é utilizada pela interface ICarenD3D11Resource.
			/// </summary>
			public enum class CA_DXGI_PRIORIDADE_RECURSO : Int64
			{
				/// <summary>
				/// O Recurso tem uma prioridade: Minima
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_MINIMUM = 0x28000000,

				/// <summary>
				/// O Recurso tem uma prioridade: Baixa
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_LOW = 0x50000000,

				/// <summary>
				/// O Recurso tem uma prioridade: Normal
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_NORMAL = 0x78000000,

				/// <summary>
				/// O Recurso tem uma prioridade: Alta
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_HIGH = 0xa0000000,

				/// <summary>
				/// O Recurso tem uma prioridade: Maxima
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_MAXIMUM = 0xc8000000,
			};

			/// <summary>
			/// (D3D11_RESOURCE_DIMENSION) - Enumera os tipos possiveis de um recurso que está sendo utilizado.
			/// </summary>
			public enum class CA_D3D11_TIPO_RECURSO
			{
				/// <summary>
				/// Recurso é de tipo desconhecido.
				/// </summary>
				D3D11_RESOURCE_DIMENSION_UNKNOWN = 0,

				/// <summary>
				/// Recurso é um buffer.
				/// </summary>
				D3D11_RESOURCE_DIMENSION_BUFFER = 1,

				/// <summary>
				/// Recurso é uma textura 1D.
				/// </summary>
				D3D11_RESOURCE_DIMENSION_TEXTURE1D = 2,

				/// <summary>
				/// Recurso é uma textura 2D.
				/// </summary>
				D3D11_RESOURCE_DIMENSION_TEXTURE2D = 3,

				/// <summary>
				/// Recurso é uma textura 3D.
				/// </summary>
				D3D11_RESOURCE_DIMENSION_TEXTURE3D = 4
			};

			/// <summary>
			/// (D3D11_ASYNC_GETDATA_FLAG) - Enumera sinalizadores opcionais que controlam o comportamento de ICarenD3D11DeviceContext::GetData.
			/// </summary>
			public enum class CA_D3D11_ASYNC_GETDATA_FLAG
			{
				/// <summary>
				/// Não implementada NADA.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Não liberar o buffer de comando. Este pode potencialmente causa um loop infinito se (GetData) chama-se continuamente até que ela retorna SS_OK como lá ainda pode ser comandos no buffer de comandos que 
				/// precisam ser processadas em ordem para GetData retornar SS_OK. Desde que os comandos no buffer de comandos não são liberados eles não serão processados e, portanto, GetData nunca irá retornar SS_OK.
				/// </summary>
				D3D11_ASYNC_GETDATA_DONOTFLUSH = 0x1
			};

			/// <summary>
			/// (D3D11_DEVICE_CONTEXT_TYPE) - Enumera as opções de contexto de dispositivo.
			/// </summary>
			public enum class CA_D3D11_DEVICE_CONTEXT_TYPE
			{
				/// <summary>
				/// O contexto de dispositivo é um contexto imediato.
				/// </summary>
				D3D11_DEVICE_CONTEXT_IMMEDIATE = 0,

				/// <summary>
				/// O contexto de dispositivo é um contexto diferido.
				/// </summary>
				D3D11_DEVICE_CONTEXT_DEFERRED = (D3D11_DEVICE_CONTEXT_IMMEDIATE + 1)
			};

			/// <summary>
			/// (D3D11_CONTEXT_TYPE) - Enumera os contextos em que ocorre uma consulta.
			/// </summary>
			public enum class CA_D3D11_CONTEXT_TYPE
			{
				/// <summary>
				/// A consulta pode ocorrer em todos os contextos.
				/// </summary>
				D3D11_CONTEXT_TYPE_ALL = 0,

				/// <summary>
				/// A consulta ocorre no contexto de uma fila de comando 3D.
				/// </summary>
				D3D11_CONTEXT_TYPE_3D = 1,

				/// <summary>
				/// A consulta ocorre no contexto de uma fila de computação 3D.
				/// </summary>
				D3D11_CONTEXT_TYPE_COMPUTE = 2,

				/// <summary>
				/// A consulta ocorre no contexto de uma fila de cópias 3D.
				/// </summary>
				D3D11_CONTEXT_TYPE_COPY = 3,

				/// <summary>
				/// A consulta ocorre no contexto do vídeo.
				/// </summary>
				D3D11_CONTEXT_TYPE_VIDEO = 4
			};

			/// <summary>
			/// (D3D11_PRIMITIVE_TOPOLOGY)(FALTA DOCUMENTAR) - Como o pipeline interpreta dados de vértices que estão ligados ao estágio de entrada-assembler. Esses valores de topologia primitivos determinam como os dados de vértice são 
			/// renderizados na tela.
			/// </summary>
			public enum class CA_D3D11_PRIMITIVE_TOPOLOGY
			{
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_POINTLIST = 1,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_LINELIST = 2,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = 33,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = 34,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = 35,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = 36,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = 37,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = 38,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = 39,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = 40,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = 41,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = 42,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = 43,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = 44,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = 45,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = 46,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = 47,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = 48,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = 49,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = 50,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = 51,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = 52,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = 53,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = 54,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = 55,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = 56,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = 57,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = 58,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = 59,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = 60,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = 61,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = 62,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = 63,
				/// <summary>
				/// 
				/// </summary>
				D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64
			};

			/// <summary>
			/// (D3D11_MAP) - Identifica um recurso para ser acessado para leitura e escrita pela CPU. Aplicativos podem combinar um ou mais desses sinalizadores.
			/// </summary>
			public enum class CA_D3D11_MAP
			{
				/// <summary>
				///  Recurso é mapeado para a leitura. O recurso deve ter sido criado com acesso de leitura (ver D3D11_CPU_ACCESS_READ).
				/// </summary>
				D3D11_MAP_READ = 1,

				/// <summary>
				/// Recurso é mapeado para a escrita. O recurso deve ter sido criado com acesso de gravação (ver D3D11_CPU_ACCESS_WRITE).
				/// </summary>
				D3D11_MAP_WRITE = 2,

				/// <summary>
				/// Recurso é mapeado para a leitura e escrita. O recurso deve ter sido criado com acesso de leitura e gravação (ver D3D11_CPU_ACCESS_READ e D3D11_CPU_ACCESS_WRITE).
				/// </summary>
				D3D11_MAP_READ_WRITE = 3,

				/// <summary>
				/// Recurso é mapeado para a escrita; o conteúdo anterior do recurso será indefinido. O recurso deve ter sido criado com acesso de gravação e uso dinâmico (ver D3D11_CPU_ACCESS_WRITE e D3D11_USAGE_DYNAMIC).
				/// </summary>
				D3D11_MAP_WRITE_DISCARD = 4,

				/// <summary>
				/// Recurso é mapeado para a escrita; o conteúdo existente do recurso não pode ser substituído. Este sinalizador é apenas válido em buffers de vértice e índice. O recurso deve ter sido 
				/// criado com acesso de gravação (ver D3D11_CPU_ACCESS_WRITE). Não pode ser usado em um recurso criado com o sinalizador D3D11_BIND_CONSTANT_BUFFER.
				/// NOTA: O runtime Direct3D 11.1, que está disponível iniciando com o Windows 8, permite o mapeamento dinâmicos buffers constantes e vistas do recurso de sombreador (SRVs) de dinâmicos buffers com 
				/// D3D11_MAP_WRITE_NO_OVERWRITE. O Direct3D 11 e runtimes anteriores limitada mapeamento para buffers de vértice ou índice.
				/// </summary>
				D3D11_MAP_WRITE_NO_OVERWRITE = 5
			};

			/// <summary>
			/// (D3D11_MAP_FLAG) - Especifica como a CPU deve responder quando um aplicativo chama o método ICarenD3D11DeviceContext::Map em um recurso que está sendo usado pela GPU.
			/// </summary>
			public enum class CA_D3D11_MAP_FLAG
			{
				/// <summary>
				/// Enumeração usada para da suporte em conversões.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Especifica que o ICarenD3D11DeviceContext::Map deve retornar DXGI_ERROR_WAS_STILL_DRAWING quando a GPU bloqueia a CPU acessar um recurso. Para obter mais informações sobre este código de erro, 
				/// consulte DXGI_ERROR.
				/// </summary>
				D3D11_MAP_FLAG_DO_NOT_WAIT = 0x100000L
			};

			/// <summary>
			/// (D3D11_TILE_MAPPING_FLAG) - Identifica como realizar uma operação de mapeamento de Tiles.
			/// </summary>
			public enum class CA_D3D11_TILE_MAPPING_FLAGS
			{
				/// <summary>
				/// Enumeração usada para da suporte em conversões.
				/// </summary>
				Zero = 0x0,
				
				/// <summary>
				/// Indica que não ocorre uma substituição de tiles na operação de mapeamento de tiles.
				/// </summary>
				D3D11_TILE_MAPPING_NO_OVERWRITE = 0x1
			};

			/// <summary>
			/// (D3D11_TILE_COPY_FLAG)(FALTA DOCUMENTAR) - Enumera bandeiras que determinam como copiar uma Tile.
			/// </summary>
			public enum class CA_D3D11_TILE_COPY_FLAG
			{
				/// <summary>
				/// Enumeração usada para da suporte em conversões.
				/// </summary>
				Zero = 0x0,
				/// <summary>
				/// 
				/// </summary>
				D3D11_TILE_COPY_NO_OVERWRITE = 0x1,
				/// <summary>
				/// 
				/// </summary>
				D3D11_TILE_COPY_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE = 0x2,
				/// <summary>
				/// 
				/// </summary>
				D3D11_TILE_COPY_SWIZZLED_TILED_RESOURCE_TO_LINEAR_BUFFER = 0x4
			};

			/// <summary>
			/// (D3D11_TILE_RANGE_FLAG) - Enumera bandeiras que especificam uma gama de mapeamentos de Tiles. 
			/// </summary>
			public enum class CA_D3D11_TILE_RANGE_FLAG
			{
				/// <summary>
				/// Enumeração usada para da suporte em conversões.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// A faixa do Tile é NULO.
				/// </summary>
				D3D11_TILE_RANGE_NULL = 0x1,

				/// <summary>
				/// Pule o alcance da Tile.
				/// </summary>
				D3D11_TILE_RANGE_SKIP = 0x2,

				/// <summary>
				/// Reutilize uma única Tile na faixa de Tiles.
				/// </summary>
				D3D11_TILE_RANGE_REUSE_SINGLE_TILE = 0x4
			};

			/// <summary>
			/// (D3D11_CONSERVATIVE_RASTERIZATION_MODE) - Enumera bandeiras que identificam se a rasterização conservadora está dentro ou fora.
			/// </summary>
			public enum class CA_D3D11_CONSERVATIVE_RASTERIZATION_MODE
			{
				/// <summary>
				/// Rasterização conservadora está desligada.
				/// </summary>
				D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF = 0,

				/// <summary>
				/// Rasterização conservadora está acontecendo.
				/// </summary>
				D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON = 1
			};

			/// <summary>
			/// (D3D11_FENCE_FLAG) - Enumera bandeiras que especificam opções de cerca(Fence).
			/// </summary>
			public enum class CA_D3D11_FENCE_FLAG
			{
				/// <summary>
				/// Nenhuma opção é especificada.
				/// </summary>
				D3D11_FENCE_FLAG_NONE = 0,

				/// <summary>
				/// A cerca é compartilhada.
				/// </summary>
				D3D11_FENCE_FLAG_SHARED = 0x2,

				/// <summary>
				/// A cerca é compartilhada com outro adaptador de GPU.
				/// </summary>
				D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER = 0x4,

				/// <summary>
				/// NAO CONTÉM DOCUMENTACAO.
				/// </summary>
				D3D11_FENCE_FLAG_NON_MONITORED = 0x8
			};
			
			/// <summary>
			/// (MF_TOPOLOGY_TYPE) - Enumera os tipos de nó em uma topologia.
			/// </summary>
			public enum class CA_MF_TOPOLOGY_TYPE
			{
				/// <summary>
				/// Nó de saída. Representa um Media Sink na topologia.
				/// </summary>
				MF_TOPOLOGY_OUTPUT_NODE = 0,

				/// <summary>
				/// Nó fonte. Representa um fluxo de mídia na topologia.
				/// </summary>
				MF_TOPOLOGY_SOURCESTREAM_NODE = (MF_TOPOLOGY_OUTPUT_NODE + 1),

				/// <summary>
				/// Nó de transformação. Representa uma Transformação de Mídia (MFT) na topologia.?
				/// </summary>
				MF_TOPOLOGY_TRANSFORM_NODE = (MF_TOPOLOGY_SOURCESTREAM_NODE + 1),

				/// <summary>
				/// Nó Tee. Um nó tee não contém um ponteiro para um objeto. Em vez disso, representa uma bifurcação no fluxo. Um nó tee tem uma entrada e várias saídas, e as amostras do nó upstream são entregues a todos os nós downstream.
				/// </summary>
				MF_TOPOLOGY_TEE_NODE = (MF_TOPOLOGY_TRANSFORM_NODE + 1),

				/// <summary>
				/// Reservado.
				/// </summary>
				MF_TOPOLOGY_MAX
			};

			/// <summary>
			/// (_AUDCLNT_SHAREMODE) - Enumera como um fluxo de áudio será executado no modo compartilhado.
			/// </summary>
			public enum class CA_AUDIOCLIENTE_SHAREMODE
			{
				/// <summary>
				/// O fluxo de áudio será executado no modo compartilhado.
				/// </summary>
				AUDCLNT_SHAREMODE_SHARED = 0,

				/// <summary>
				/// O fluxo de áudio será executado em modo exclusivo.
				/// </summary>
				AUDCLNT_SHAREMODE_EXCLUSIVE = 1
			};

			/// <summary>
			/// (_AUDCLNT_BUFFERFLAGS) - Enumera sinalizadores que indicam o status de um buffer de ponto de extremidade de áudio.
			/// </summary>
			public enum class CA_AUDIOCLIENTE_BUFFERFLAGS
			{
				/// <summary>
				/// Enumeração não pertencente a enumeração real. Utilizado para da suporte.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Os dados no pacote não estão correlacionados com a posição do dispositivo do pacote anterior; Isso é possivelmente devido a uma transição de estado de fluxo ou falha de tempo.
				/// </summary>
				AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY = 0x1,

				/// <summary>
				/// Trate todos os dados no pacote como silêncio e ignore os valores de dados reais. Para obter mais informações sobre o uso desse sinalizador.
				/// </summary>
				AUDCLNT_BUFFERFLAGS_SILENT = 0x2,

				/// <summary>
				/// A hora em que a posição do fluxo do dispositivo foi gravada é incerto. Assim, o cliente pode não conseguir definir com precisão o carimbo de data/hora para o pacote de dados atual.
				/// </summary>
				AUDCLNT_BUFFERFLAGS_TIMESTAMP_ERROR = 0x4
			};

			/// <summary>
			/// (_AUDIO_STREAM_CATEGORY) - Enumera sinalizadores que especificam a categoria de um fluxo de áudio.
			/// </summary>
			public enum class CA_AUDIO_STREAM_CATEGORY
			{
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Other = 0,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_ForegroundOnlyMedia = 1,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_BackgroundCapableMedia = 2,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Communications = 3,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Alerts = 4,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_SoundEffects = 5,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_GameEffects = 6,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_GameMedia = 7,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_GameChat = 8,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Speech = 9,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Movie = 10,
				/// <summary>
				/// 
				/// </summary>
				AudioCategory_Media = 11,
			};
			
			/// <summary>
			/// (AUDCLNT_STREAMOPTIONS ) - Enumera sinalizadores que definem valores que descrevem as características de um fluxo de áudio.
			/// </summary>
			public enum class CA_AUDCLNT_STREAMOPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				AUDCLNT_STREAMOPTIONS_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				AUDCLNT_STREAMOPTIONS_RAW = 0x1,
				/// <summary>
				/// 
				/// </summary>
				AUDCLNT_STREAMOPTIONS_MATCH_FORMAT = 0x2,
				/// <summary>
				/// 
				/// </summary>
				AUDCLNT_STREAMOPTIONS_AMBISONICS = 0x4
			};

			/// <summary>
			/// (__MIDL___MIDL_itf_mmdeviceapi_0000_0000_0001) - Enumera constantes que indicam a direção na qual os fluxos de dados de áudio entre um dispositivo de ponto de extremidade de áudio e um aplicativo.
			/// </summary>
			public enum class CA_EDataFlow
			{
				/// <summary>
				/// Fluxo de renderização de áudio. Fluxos de dados de áudio do aplicativo para o dispositivo de ponto de extremidade de áudio, que processa o fluxo.
				/// </summary>
				eRender = 0,

				/// <summary>
				/// Fluxo de captura de áudio. Fluxos de dados de áudio do dispositivo de ponto de extremidade de áudio que captura o fluxo, para o aplicativo.
				/// </summary>
				eCapture = (eRender + 1),

				/// <summary>
				/// Renderização de áudio ou fluxo de captura. Os dados de áudio podem fluir do aplicativo para o dispositivo de ponto de extremidade de áudio ou do dispositivo de ponto de extremidade de áudio para o aplicativo.
				/// </summary>
				eAll = (eCapture + 1),

				/// <summary>
				/// O número de membros na enumeração Edataflow (sem contar o membro EDataFlow_enum_count).
				/// </summary>
				EDataFlow_enum_count = (eAll + 1)
			};

			/// <summary>
			/// (STGM Constants) - Enumera constantes que indicam condições para criar e excluir os modos de objeto e de acesso para o objeto.
			/// </summary>
			public enum class CA_STGMs
			{
				/// <summary>
				/// Indica que o objeto é somente leitura, significando que as modificações não podem ser feitas.
				/// </summary>
				CA_STGM_READ = STGM_READ,

				/// <summary>
				/// Permite que você salve as alterações no objeto, mas não permite o acesso aos seus dados.
				/// </summary>
				CA_STGM_WRITE = STGM_WRITE,

				/// <summary>
				/// Habilita o acesso e a modificação de dados do objeto. Por exemplo, se um objeto de fluxo é criado ou aberto nesse modo, é possível chamar metodos de (Leitura) e (Escrita).
				/// </summary>
				CA_STGM_READWRITE = STGM_READWRITE,
			};

			/// <summary>
			/// (ORIGINAL) - Enumera constantes que são utilizadas na criação de arquivos ou fluxos com base em arquivo em disco.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_FILE_ATTRIBUTES
			{
				/// <summary>
				/// O arquivo deve ser arquivado. Os aplicativos usam esse atributo para marcar arquivos para backup ou remoção.
				/// </summary>
				CA_FILE_ATTRIBUTE_ARCHIVE = FILE_ATTRIBUTE_ARCHIVE,
				/// <summary>
				/// O arquivo ou diretório está criptografado. Para um arquivo, isso significa que todos os dados no arquivo são criptografados. Para um diretório, isso significa que a criptografia é o padrão para arquivos e subdireções recém-criados. 
				/// </summary>
				CA_FILE_ATTRIBUTE_ENCRYPTED = FILE_ATTRIBUTE_ENCRYPTED,
				/// <summary>
				/// O arquivo está escondido. Não o inclua em uma lista de diretórios ordinário.
				/// </summary>
				CA_FILE_ATTRIBUTE_HIDDEN = FILE_ATTRIBUTE_HIDDEN,
				/// <summary>
				/// O arquivo não tem outros atributos definidos. Este atributo só é válido se usado sozinho.
				/// </summary>
				CA_FILE_ATTRIBUTE_NORMAL = FILE_ATTRIBUTE_NORMAL,
				/// <summary>
				/// Os dados de um arquivo não estão disponíveis imediatamente. Esse atributo indica que os dados do arquivo são fisicamente movidos para armazenamento off-line. Este atributo é usado pelo Remote Storage, o software hierárquico de gerenciamento de armazenamento. As aplicações não devem alterar arbitrariamente esse atributo.
				/// </summary>
				CA_FILE_ATTRIBUTE_OFFLINE = FILE_ATTRIBUTE_OFFLINE,
				/// <summary>
				/// O arquivo é lido apenas. Os aplicativos podem ler o arquivo, mas não podem gravá-lo ou excluí-lo.
				/// </summary>
				CA_FILE_ATTRIBUTE_READONLY = FILE_ATTRIBUTE_READONLY,
				/// <summary>
				/// O arquivo faz parte ou é usado exclusivamente por um sistema operacional.
				/// </summary>
				CA_FILE_ATTRIBUTE_SYSTEM = FILE_ATTRIBUTE_SYSTEM,
				/// <summary>
				/// O arquivo está sendo usado para armazenamento temporário.
				/// </summary>
				CA_FILE_ATTRIBUTE_TEMPORARY = FILE_ATTRIBUTE_TEMPORARY
			};
					
			/// <summary>
			/// (ORIGINAL) - Enumera constantes que são utilizadas na criação de arquivos ou fluxos com base em um arquivo em disco.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_FILE_FLAGS
			{
				/// <summary>
				/// Esse valor é utilizado apenas para dar suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0,

				CA_FILE_FLAG_BACKUP_SEMANTICS = FILE_FLAG_BACKUP_SEMANTICS,

				CA_FILE_FLAG_DELETE_ON_CLOSE = FILE_FLAG_DELETE_ON_CLOSE,

				CA_FILE_FLAG_NO_BUFFERING = FILE_FLAG_NO_BUFFERING,

				CA_FILE_FLAG_OPEN_NO_RECALL = FILE_FLAG_OPEN_NO_RECALL,

				CA_FILE_FLAG_OPEN_REPARSE_POINT = FILE_FLAG_OPEN_REPARSE_POINT,

				CA_FILE_FLAG_OVERLAPPED = FILE_FLAG_OVERLAPPED,

				CA_FILE_FLAG_POSIX_SEMANTICS = FILE_FLAG_POSIX_SEMANTICS,

				CA_FILE_FLAG_RANDOM_ACCESS = FILE_FLAG_RANDOM_ACCESS,

				CA_FILE_FLAG_SESSION_AWARE = FILE_FLAG_SESSION_AWARE,

				CA_FILE_FLAG_SEQUENTIAL_SCAN = FILE_FLAG_SEQUENTIAL_SCAN,

				CA_FILE_FLAG_WRITE_THROUGH = FILE_FLAG_WRITE_THROUGH
			};

			/// <summary>
			/// (MFWaveFormatExConvertFlags) - Enumera sinalizadores que especificam como converter um tipo de mídia de áudio.
			/// </summary>
			public enum class CA_MFWaveFormatExConvertFlags
			{
				/// <summary>
				/// Converta o tipo de mídia para um WAVEFORMATEX estrutura se possível, ou um WAVEFORMATEXTENSIBLE estrutura caso contrário.
				/// </summary>
				MFWaveFormatExConvertFlag_Normal = 0,

				/// <summary>
				/// Converta o tipo de mídia para um WAVEFORMATEXTENSIBLE estrutura.
				/// </summary>
				MFWaveFormatExConvertFlag_ForceExtensible = 1
			};

			/// <summary>
			/// (_MF_SERVICE_LOOKUP_TYPE) - Não possui documentação.
			/// </summary>
			public enum class CA_MF_SERVICE_LOOKUP_TYPE
			{
				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_UPSTREAM = 0,

				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_UPSTREAM_DIRECT = (MF_SERVICE_LOOKUP_UPSTREAM + 1),

				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_DOWNSTREAM = (MF_SERVICE_LOOKUP_UPSTREAM_DIRECT + 1),

				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_DOWNSTREAM_DIRECT = (MF_SERVICE_LOOKUP_DOWNSTREAM + 1),

				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_ALL = (MF_SERVICE_LOOKUP_DOWNSTREAM_DIRECT + 1),

				/// <summary>
				/// 
				/// </summary>
				MF_SERVICE_LOOKUP_GLOBAL = (MF_SERVICE_LOOKUP_ALL + 1)
			};

			/// <summary>
			/// (_MFRATE_DIRECTION) - Enumera as possiveis direções da reprodução (AVANCAR ou REVERTER).
			/// </summary>
			public enum class CA_MFRATE_DIRECTION
			{
				/// <summary>
				/// Avançar reprodução.
				/// </summary>
				MFRATE_FORWARD = 0,

				/// <summary>
				/// Inverter a reprodução.
				/// </summary>
				MFRATE_REVERSE = (MFRATE_FORWARD + 1)
			};

			/// <summary>
			/// (MFSESSION_GETFULLTOPOLOGY_FLAGS) - Enumera os Flags para o método ICarenMFMediaSession::GetFullTopology.
			/// </summary>
			public enum class CA_MFSESSION_GETFULLTOPOLOGY_FLAGS
			{
				/// <summary>
				/// Suporte.
				/// </summary>
				Zero = 0,

				/// <summary>
				/// Obtenha a topologia completa para a apresentação que a sessão de mídia está sendo reproduzida no momento.
				/// </summary>
				MFSESSION_GETFULLTOPOLOGY_CURRENT = 0x1
			};

			/// <summary>
			/// (MFSESSION_SETTOPOLOGY_FLAGS) - Enumera os Flags para o comportamento do método ICarenMFMediaSession::SetTopology.
			/// </summary>
			public enum class CA_MFSESSION_SETTOPOLOGY_FLAGS
			{
				/// <summary>
				/// Suporte.
				/// </summary>
				Zero = 0,



				/// <summary>
				/// Pare a apresentação atual, desmarque todas as apresentações pendentes e enfileire imediatamente a nova topologia (especificada pelo parâmetro Param_Topologia).
				/// Se o Param_Topologia parâmetro é NULO, este sinalizador não tem efeito.
				/// </summary>
				MFSESSION_SETTOPOLOGY_IMMEDIATE = 0x1,

				/// <summary>
				/// A topologia não precisa ser resolvida. Use este sinalizador se você estiver definindo uma topologia completa.
				/// </summary>
				MFSESSION_SETTOPOLOGY_NORESOLUTION = 0x2,

				/// <summary>
				/// Desmarca a topologia atual seguindo criterios especificos(Consulte a documentação). As topologias pendentes não são removidas da fila de reprodução. Se houver uma topologia pendente 
				/// na fila, essa topologia será carregada após a topologia atual ser desmarcada. Caso contrário, a reprodução simplesmente para.Para remover todas as topologias pendentes da fila, 
				/// chame ICarenMFMediaSession::ClearTopologies.
				/// </summary>
				MFSESSION_SETTOPOLOGY_CLEAR_CURRENT = 0x4
			};

			/// <summary>
			/// (Original) - Enumera os recursos de uma sessão de midia.
			/// </summary>
			public enum class CA_MFSESSIONCAP
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				CA_Zero = 0,

				/// <summary>
				/// A sessão de mídia pode ser iniciada.
				/// </summary>
				CA_MFSESSIONCAP_START = 0x00000001,

				/// <summary>
				/// A sessão de mídia pode ser pesquisada.
				/// </summary>
				CA_MFSESSIONCAP_SEEK = 0x00000002,

				/// <summary>
				/// A sessão de mídia pode ser pausada.
				/// </summary>
				CA_MFSESSIONCAP_PAUSE = 0x00000004,

				/// <summary>
				/// A sessão de mídia oferece suporte à reprodução direta em taxas mais rápidas que 1,0.
				/// </summary>
				CA_MFSESSIONCAP_RATE_FORWARD = 0x00000010,

				/// <summary>
				/// A sessão de mídia suporta a reprodução inversa.
				/// </summary>
				CA_MFSESSIONCAP_RATE_REVERSE = 0x00000020,
			};

			/// <summary>
			/// (MFPMPSESSION_CREATION_FLAGS) - Enumera os sinalizadores que definem o comportamento da função (CarenMFMediaSession::CriarInstanciaPMP).
			/// </summary>
			public enum class CA_PMPSESSION_CREATION_FLAGS
			{
				/// <summary>
				/// Se esse sinalizador estiver definido, a sessão de mídia do caminho de mídia protegido (PMP) é criada em um processo desprotegido. Você pode usar o processo desprotegido para
				/// reproduzir conteúdo claro, mas não protegido. Se esse sinalizador não estiver definido, a sessão de mídia PMP é criada em um processo protegido. Nesse caso, o processo protegido 
				/// é usado para conteúdo protegido e conteúdo claro.
				/// </summary>
				MFPMPSESSION_UNPROTECTED_PROCESS = 0x1,

				/// <summary>
				/// Cria a sessão para o processo atual.
				/// </summary>
				MFPMPSESSION_IN_PROCESS = 0x2
			};

			/// <summary>
			/// (_AudioSessionState) - Enumera constantes que indicam o estado atual de uma sessão de áudio.
			/// </summary>
			public enum class CA_ESTADO_SESSAO_AUDIO
			{
				/// <summary>
				/// A sessão de áudio está inativa. (Ele contém pelo menos um fluxo, mas nenhum dos fluxos na sessão está em execução no momento.)
				/// </summary>
				AudioSessionStateInactive = 0,

				/// <summary>
				/// A sessão de áudio está ativa. (Pelo menos um dos fluxos na sessão está em execução.)
				/// </summary>
				AudioSessionStateActive = 1,

				/// <summary>
				/// A sessão de áudio expirou. (Ele não contém fluxos.)
				/// </summary>
				AudioSessionStateExpired = 2
			};

			/// <summary>
			/// (AudioSessionDisconnectReason) - Enumera constantes que indicam o motivo da sessão de áudio ter sido desligada.
			/// </summary>
			public enum class CA_RAZAO_DESCONEXAO_SESSAO_AUDIO
			{
				/// <summary>
				/// O usuário removeu o dispositivo de ponto de extremidade de áudio.
				/// </summary>
				DisconnectReasonDeviceRemoval = 0,

				/// <summary>
				/// O serviço de áudio do Windows foi interrompido.
				/// </summary>
				DisconnectReasonServerShutdown = (DisconnectReasonDeviceRemoval + 1),

				/// <summary>
				/// O formato de fluxo alterado para o dispositivo que a sessão de áudio está conectada.
				/// </summary>
				DisconnectReasonFormatChanged = (DisconnectReasonServerShutdown + 1),

				/// <summary>
				/// O usuário fez logoff da sessão dos serviços de terminal do Windows (WTS) em que a sessão de áudio estava sendo executada.
				/// </summary>
				DisconnectReasonSessionLogoff = (DisconnectReasonFormatChanged + 1),

				/// <summary>
				/// A sessão de WTS que a sessão de áudio estava em execução foi desligada.
				/// </summary>
				DisconnectReasonSessionDisconnected = (DisconnectReasonSessionLogoff + 1),

				/// <summary>
				/// A sessão de áudio (modo compartilhado) foi desconectada para tornar o dispositivo de ponto de extremidade de áudio disponível para uma conexão de modo exclusivo.
				/// </summary>
				DisconnectReasonExclusiveModeOverride = (DisconnectReasonSessionDisconnected + 1)
			};

			/// <summary>
			/// (DXGI_MODE_ROTATION)(FALTA DOCUMENTAR) - Enumera sinalizadores que indicam como os buffers traseiros devem ser girados para se ajustarem à rotação física de um monitor.
			/// </summary>
			public enum class CA_DXGI_MODE_ROTATION
			{
				CA_DXGI_MODE_ROTATION_UNSPECIFIED = 0,

				CA_DXGI_MODE_ROTATION_IDENTITY = 1,

				CA_DXGI_MODE_ROTATION_ROTATE90 = 2,

				CA_DXGI_MODE_ROTATION_ROTATE180 = 3,

				CA_DXGI_MODE_ROTATION_ROTATE270 = 4
			};

			/// <summary>
			/// (DXGI_MODE_ROTATION)(FALTA DOCUMENTAR) - Enumera opções para os modos de exibição.
			/// </summary>
			public enum class CA_DXGI_ENUM_MODES
			{
				Zero = 0,

				CA_DXGI_ENUM_MODES_INTERLACED = DXGI_ENUM_MODES_INTERLACED,

				CA_DXGI_ENUM_MODES_SCALING = DXGI_ENUM_MODES_SCALING,

				CA_DXGI_ENUM_MODES_STEREO = DXGI_ENUM_MODES_STEREO,

				CA_DXGI_ENUM_MODES_DISABLED_STEREO = DXGI_ENUM_MODES_DISABLED_STEREO
			};

			/// <summary>
			/// (ORIGINAL)(FALTA DOCUMENTAR) - Enumera possiveis bandeira para o método de monitoramente de janelas em uma cadeia de Swap.
			/// </summary>
			public enum class CA_DXGI_MWA_FLAGS
			{
				Zero = 0,

				CA_DXGI_MWA_NO_WINDOW_CHANGES = DXGI_MWA_NO_WINDOW_CHANGES,

				CA_DXGI_MWA_NO_ALT_ENTER = DXGI_MWA_NO_ALT_ENTER,

				CA_DXGI_MWA_NO_PRINT_SCREEN = DXGI_MWA_NO_PRINT_SCREEN,

				CA_DXGI_MWA_VALID = DXGI_MWA_VALID
			};

			/// <summary>
			/// (DXGI_FEATURE)(FALTA DOCUMENTAR) - Enumera uma gama de recursos de hardware, a serem usados ao verificar o suporte ao recurso.
			/// </summary>
			public enum class CA_DXGI_FEATURE
			{
				/// <summary>
				/// O display suporta (Tearing), um requisito de displays de taxa de atualização variável.
				/// </summary>
				CA_DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0
			};
		
			/// <summary>
			/// (DXGI_GPU_PREFERENCE)) - Enumera preferências da GPU para o aplicativo funcionar.
			/// ATENCAO:     
			/// [Algumas informações se relacionam com o produto pré-lançado que pode ser substancialmente modificado antes de ser lançado comercialmente. A Microsoft não faz nenhuma 
			/// garantia, expressa ou implícita, com relação às informações aqui fornecidas.]
			/// </summary>
			public enum class CA_DXGI_GPU_PREFERENCE
			{
				/// <summary>
				/// Nenhuma preferência da GPU.
				/// </summary>
				CA_DXGI_GPU_PREFERENCE_UNSPECIFIED = 0,

				/// <summary>
				/// Preferência pela GPU de potência mínima (como um processador gráfico integrado, ou iGPU).
				/// </summary>
				CA_DXGI_GPU_PREFERENCE_MINIMUM_POWER = (DXGI_GPU_PREFERENCE_UNSPECIFIED + 1),

				/// <summary>
				/// Preferência pela GPU de maior desempenho, como um processador gráfico discreto (dGPU) ou processador gráfico externo (xGPU).
				/// </summary>
				CA_DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE = (DXGI_GPU_PREFERENCE_MINIMUM_POWER + 1)
			};

			/// <summary>
			/// (DXGI_RESIDENCY) - Enumera bandeiras que indicando a localização da memória de um recurso.
			/// </summary>
			public enum class CA_DXGI_RESIDENCY
			{
				/// <summary>
				/// O recurso está localizado na memória de vídeo.
				/// </summary>
				CA_DXGI_RESIDENCY_FULLY_RESIDENT = 1,

				/// <summary>
				/// Pelo menos parte do recurso está localizado na memória da CPU.
				/// </summary>
				CA_DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY = 2,

				/// <summary>
				/// Pelo menos parte do recurso foi chamado para o disco rígido.
				/// </summary>
				CA_DXGI_RESIDENCY_EVICTED_TO_DISK = 3
			};

			/// <summary>
			/// (DXGI_OFFER_RESOURCE_PRIORITY) - Enumera bandeiras que identificam a importância do conteúdo de um recurso quando você chama o método
			/// ICarenDXGIDevice2::OfertarRecurso para oferecer o recurso.
			/// </summary>
			public enum class CA_DXGI_OFFER_RESOURCE_PRIORITY
			{
				/// <summary>
				/// O recurso é de baixa prioridade. O sistema operacional descarta um recurso de baixa prioridade antes de outros recursos oferecidos com maior prioridade. 
				/// É uma boa prática de programação marcar um recurso de baixa prioridade se não tiver conteúdo útil.
				/// </summary>
				CA_DXGI_OFFER_RESOURCE_PRIORITY_LOW = 1,

				/// <summary>
				/// O recurso é prioridade normal. Você marca um recurso como prioridade normal se ele tiver conteúdo fácil de regenerar.
				/// </summary>
				CA_DXGI_OFFER_RESOURCE_PRIORITY_NORMAL = (DXGI_OFFER_RESOURCE_PRIORITY_LOW + 1),
				
				/// <summary>
				/// O recurso é de alta prioridade. O sistema operacional descarta outros recursos oferecidos com menor prioridade antes de descartar um recurso de alta prioridade. 
				/// Você marca um recurso como alta prioridade se ele tiver conteúdo útil que é difícil de regenerar.
				/// </summary>
				CA_DXGI_OFFER_RESOURCE_PRIORITY_HIGH = (DXGI_OFFER_RESOURCE_PRIORITY_NORMAL + 1)
			};

			/// <summary>
			/// (_DXGI_OFFER_RESOURCE_FLAGS) - Enumera bandeiras para serem utilizadas pelo método ICarenDXGIDevice4::OfferResources.
			/// </summary>
			public enum class CA_DXGI_OFFER_RESOURCE_FLAGS
			{
				/// <summary>
				/// Não representa nada.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Indica a capacidade de permitir a desempenhão de memória pelo Kernel Gráfico DirectX.
				/// </summary>
				CA_DXGI_OFFER_RESOURCE_FLAG_ALLOW_DECOMMIT = 0x1
			};

			/// <summary>
			/// (DXGI_RECLAIM_RESOURCE_RESULTS) - Enumera bandeiras de resultados para o método ICarenDXGIDevice4::ReclaimResources1.
			/// </summary>
			public enum class CA_DXGI_RECLAIM_RESOURCE_RESULTS
			{
				/// <summary>
				/// A superfície foi recuperada com sucesso e tem conteúdo válido. Este resultado é idêntico ao valor falso devolvido pelo antigo método (ReclaimResources).
				/// </summary>
				CA_DXGI_RECLAIM_RESOURCE_RESULT_OK = 0,

				/// <summary>
				/// A superfície foi recuperada, mas o conteúdo antigo foi perdido e deve ser regenerado. Este resultado é idêntico ao verdadeiro valor devolvido 
				/// pelo antigo método (ReclaimResources).
				/// </summary>
				CA_DXGI_RECLAIM_RESOURCE_RESULT_DISCARDED = 1,

				/// <summary>
				/// Tanto a superfície quanto seu conteúdo são perdidos e inválidos. A superfície deve ser recriada e o conteúdo se regenerado para ser usado.Todo o uso 
				/// futuro desse recurso é inválido.As tentativas de ligá - lo ao gasoduto ou mapear um recurso que retorna esse valor nunca terão sucesso, e o recurso não 
				/// pode ser recuperado novamente.
				/// </summary>
				CA_DXGI_RECLAIM_RESOURCE_RESULT_NOT_COMMITTED = 2
			};

			/// <summary>
			/// (Original) - Enumera bandeiras que contém as prioridades de despejo, onde determinam quando um recurso pode ser despejado da memória.
			/// </summary>
			public enum class CA_DXGI_RESOURCE_PRIORITY : Int64
			{
				/// <summary>
				/// Apenas para da suporte.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// O recurso não é utilizado e pode ser despejado assim que outro recurso exigir a memória que o recurso ocupa.
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_MINIMUM = 0x28000000,

				/// <summary>
				/// A prioridade de despejo do recurso é baixa. A colocação do recurso não é crítica, e o trabalho mínimo é realizado para encontrar um local para o recurso. Por exemplo, se uma GPU pode renderizar com um tampão vértice de memória local ou não local com pouca diferença de desempenho, esse tampão de vértice é de baixa prioridade. Outros recursos mais críticos (por exemplo, um alvo ou textura de renderização) podem então ocupar a memória mais rápida.
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_LOW = 0x50000000,

				/// <summary>
				/// A prioridade de despejo do recurso é normal. A colocação do recurso é importante, mas não crítica, para o desempenho. O recurso é colocado em sua localização preferida em vez de um recurso de baixa prioridade.
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_NORMAL = 0x78000000,

				/// <summary>
				/// A prioridade de despejo do recurso é alta. O recurso é colocado em sua localização preferida em vez de um recurso de baixa prioridade ou prioridade normal.
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_HIGH = 0xa0000000,

				/// <summary>
				/// O recurso é despejado da memória apenas se não houver outra maneira de resolver o requisito de memória.
				/// </summary>
				CA_DXGI_RESOURCE_PRIORITY_MAXIMUM = 0xc8000000,
			};
			
			/// <summary>
			/// (Original)(Constantes) - Enumera bandeiras constante do (DXGI_SHARED_RESOURCE_RW).
			/// </summary>
			public enum class CA_DXGI_SHARED_RESOURCE_RW : Int64
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O recurso compartilhado é somente leitura.
				/// </summary>
				CA_DXGI_SHARED_RESOURCE_READ = DXGI_SHARED_RESOURCE_READ,

				/// <summary>
				/// O recurso compartilhado pode ser modificado(escrito).
				/// </summary>
				CA_DXGI_SHARED_RESOURCE_WRITE = DXGI_SHARED_RESOURCE_WRITE
			};

			/// <summary>
			/// (DXGI_ADAPTER_FLAG)(FALTA DOCUMENTAR) - Enumera os tipos de adaptador DXGI.
			/// </summary>
			public enum class CA_DXGI_ADAPTER_FLAG
			{
				CA_DXGI_ADAPTER_FLAG_NONE = 0,

				CA_DXGI_ADAPTER_FLAG_REMOTE = 1,

				CA_DXGI_ADAPTER_FLAG_SOFTWARE = 2,
			};

			/// <summary>
			/// (DXGI_ADAPTER_FLAG)(FALTA DOCUMENTAR) - Enumera os tipos de adaptador DXGI.
			/// </summary>
			public enum class CA_DXGI_ADAPTER_FLAG3 : UInt64
			{
				CA_DXGI_ADAPTER_FLAG3_NONE = 0,

				CA_DXGI_ADAPTER_FLAG3_REMOTE = 1,

				CA_DXGI_ADAPTER_FLAG3_SOFTWARE = 2,

				CA_DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE = 4,

				CA_DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES = 8,

				CA_DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES = 0x10,

				CA_DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE = 0x20,
			};
	
			/// <summary>
			/// (DXGI_GRAPHICS_PREEMPTION_GRANULARITY)(FALTA DOCUMENTAR) - Enumera a granularidade na qual a unidade de processamento gráfico (GPU) pode 
			/// ser impedida de realizar sua atual tarefa de renderização gráfica.
			/// </summary>
			public enum class CA_DXGI_GRAPHICS_PREEMPTION_GRANULARITY
			{
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY = 1,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY = 2,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY = 3,
				/// <summary>
				/// 
				/// </summary>
				CA_DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY = 4
			};

			/// <summary>
			/// (DXGI_COMPUTE_PREEMPTION_GRANULARITY) - Enumera a granularidade na qual a unidade de processamento gráfico (GPU) pode 
			/// ser impedida de realizar sua atual tarefa de computação.
			/// </summary>
			public enum class CA_DXGI_COMPUTE_PREEMPTION_GRANULARITY
			{
				/// <summary>
				/// Indica a granularidade preventiva como um pacote de computação.
				/// </summary>
				CA_DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,

				/// <summary>
				/// Indica a granularidade preventiva como um Dispatch(por exemplo, uma chamada para o método ICarenD3D11DeviceContext::Despachar).
				/// Um Dispatch é parte de um pacote de computação.
				/// </summary>
				CA_DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY = 1,

				/// <summary>
				/// Indica a granularidade preventiva como um grupo de Threads. Um grupo de Thread é parte de um (Dispatch).
				/// </summary>
				CA_DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY = 2,

				/// <summary>
				/// Indica a granularidade preventiva como uma Thread em um grupo de Threads. Uma Thread faz parte de um grupo de Threads.
				/// </summary>
				CA_DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY = 3,

				/// <summary>
				/// Indica a granularidade preventiva como uma instrução computacional em um tópico.
				/// </summary>
				CA_DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY = 4

			};


			/// <summary>
			/// (PROPRIA)(FALTA DOCUMENTAR) - Enumera os flags que podem ser utilizados durante a criação de um evento do Windows.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WIN_EVENT_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_CREATE_EVENT_MANUAL_RESET = CREATE_EVENT_MANUAL_RESET,

				CA_CREATE_EVENT_INITIAL_SET = CREATE_EVENT_INITIAL_SET
			};

			/// <summary>
			/// (_MFT_INPUT_STATUS_FLAGS)(FALTA DOCUMENTAR) - Enumera os status de um fluxo de entrada em uma transformação da Media Foundation (MFT).
			/// </summary>
			public enum class CA_MFT_INPUT_STATUS_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_MFT_INPUT_STATUS_ACCEPT_DATA = MFT_INPUT_STATUS_ACCEPT_DATA
			};

			/// <summary>
			/// (_MFT_INPUT_STATUS_FLAGS) - Enumera se uma transformação da Media Foundation (MFT) pode produzir dados de produção.
			/// </summary>
			public enum class CA_MFT_OUTPUT_STATUS_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// (MFT_OUTPUT_STATUS_SAMPLE_READY) - Há uma amostra disponível para pelo menos um fluxo de saída. Para recuperar as amostras de produção disponíveis, ligue para o ICarenMFTransform::ProcessOutput.
				/// </summary>
				CA_MFT_OUTPUT_STATUS_SAMPLE_READY = MFT_OUTPUT_STATUS_SAMPLE_READY
			};

			/// <summary>
			/// (_MFT_INPUT_STREAM_INFO_FLAGS)(FALTA DOCUMENTAR) - Enumera as descrições de um fluxo de entrada em uma transformação da Media Foundation (MFT).
			/// </summary>
			public enum class CA_MFT_INPUT_STREAM_INFO_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_MFT_INPUT_STREAM_WHOLE_SAMPLES = MFT_INPUT_STREAM_WHOLE_SAMPLES,

				CA_MFT_INPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER = MFT_INPUT_STREAM_SINGLE_SAMPLE_PER_BUFFER,

				CA_MFT_INPUT_STREAM_FIXED_SAMPLE_SIZE = MFT_INPUT_STREAM_FIXED_SAMPLE_SIZE,

				CA_MFT_INPUT_STREAM_HOLDS_BUFFERS = MFT_INPUT_STREAM_HOLDS_BUFFERS,

				CA_MFT_INPUT_STREAM_DOES_NOT_ADDREF = MFT_INPUT_STREAM_DOES_NOT_ADDREF,

				CA_MFT_INPUT_STREAM_REMOVABLE = MFT_INPUT_STREAM_REMOVABLE,

				CA_MFT_INPUT_STREAM_OPTIONAL = MFT_INPUT_STREAM_OPTIONAL,

				CA_MFT_INPUT_STREAM_PROCESSES_IN_PLACE = MFT_INPUT_STREAM_PROCESSES_IN_PLACE
			};
			
			/// <summary>
			/// (MFT_MESSAGE_TYPE)(FALTA DOCUMENTAR) - Enumera as mensagens para uma transformação da Media Foundation (MFT). Para enviar uma mensagem a um MFT, ligue para o ICarenMFTransform::ProcessMessage.
			/// </summary>
			public enum class CA_MFT_MESSAGE_TYPE
			{
				CA_MFT_MESSAGE_COMMAND_FLUSH = 0,

				CA_MFT_MESSAGE_COMMAND_DRAIN = 0x1,

				CA_MFT_MESSAGE_SET_D3D_MANAGER = 0x2,

				CA_MFT_MESSAGE_DROP_SAMPLES = 0x3,

				CA_MFT_MESSAGE_COMMAND_TICK = 0x4,

				CA_MFT_MESSAGE_NOTIFY_BEGIN_STREAMING = 0x10000000,

				CA_MFT_MESSAGE_NOTIFY_END_STREAMING = 0x10000001,

				CA_MFT_MESSAGE_NOTIFY_END_OF_STREAM = 0x10000002,

				CA_MFT_MESSAGE_NOTIFY_START_OF_STREAM = 0x10000003,

				CA_MFT_MESSAGE_NOTIFY_RELEASE_RESOURCES = 0x10000004,

				CA_MFT_MESSAGE_NOTIFY_REACQUIRE_RESOURCES = 0x10000005,
				
				CA_MFT_MESSAGE_NOTIFY_EVENT = 0x10000006,

				CA_MFT_MESSAGE_COMMAND_SET_OUTPUT_STREAM_STATE = 0x10000007,

				CA_MFT_MESSAGE_COMMAND_FLUSH_OUTPUT_STREAM = 0x10000008,

				CA_MFT_MESSAGE_COMMAND_MARKER = 0x20000000
			};
			
			/// <summary>
			/// (MFVP_MESSAGE_TYPE)(FALTA DOCUMENTAR) - Enumera mensagens para um apresentador de renderização de vídeo aprimorado (EVR). Esta enumeração é usada com o método ICarenMFVideoPresenter::ProcessMessage.
			/// </summary>
			public enum class CA_MFVP_MESSAGE_TYPE
			{
				MFVP_MESSAGE_FLUSH = 0,

				MFVP_MESSAGE_INVALIDATEMEDIATYPE = 0x1,

				MFVP_MESSAGE_PROCESSINPUTNOTIFY = 0x2,

				MFVP_MESSAGE_BEGINSTREAMING = 0x3,

				MFVP_MESSAGE_ENDSTREAMING = 0x4,

				MFVP_MESSAGE_ENDOFSTREAM = 0x5,

				MFVP_MESSAGE_STEP = 0x6,

				MFVP_MESSAGE_CANCELSTEP = 0x7
			};

			/// <summary>
			/// (_MFT_PROCESS_OUTPUT_FLAGS)(FALTA DOCUMENTAR) - Enumera as bandeiras para o processamento de amostras de produção em uma transformação da Media Foundation (MFT).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFT_PROCESS_OUTPUT_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_MFT_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER	= 0x1,
				 
				CA_MFT_PROCESS_OUTPUT_REGENERATE_LAST_OUTPUT	= 0x2
			};

			/// <summary>
			/// (_MFT_OUTPUT_DATA_BUFFER_FLAGS)(FALTA DOCUMENTAR) - Enumera bandeiras para o método ICarenMFTransform::ProcessOutput
			/// </summary>
			public enum class CA_MFT_OUTPUT_DATA_BUFFER_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_MFT_OUTPUT_DATA_BUFFER_INCOMPLETE = 0x1000000,

				CA_MFT_OUTPUT_DATA_BUFFER_FORMAT_CHANGE = 0x100,

				CA_MFT_OUTPUT_DATA_BUFFER_STREAM_END = 0x200,

				CA_MFT_OUTPUT_DATA_BUFFER_NO_SAMPLE = 0x300
			};

			/// <summary>
			/// (_MFT_PROCESS_OUTPUT_STATUS)(FALTA DOCUMENTAR) - Enumera o status de uma chamada para ICarenMFTransform::ProcessOutput.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFT_PROCESS_OUTPUT_STATUS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				CA_MFT_PROCESS_OUTPUT_STATUS_NEW_STREAMS = 0x100
			};

			/// <summary>
			/// (_MFT_SET_TYPE_FLAGS)(FALTA DOCUMENTAR) - Enumera bandeiras para a configuração ou teste do tipo de mídia em uma transformação da Media Foundation (MFT).
			/// </summary>
			public enum class CA_MFT_SET_TYPE_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				MFT_SET_TYPE_TEST_ONLY = 0x1,
			};

			/// <summary>
			/// (_MFNetAuthenticationFlags)(FALTA DOCUMENTAR) - Enumera bandeiras que especificam como as credenciais do usuário serão usadas.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFNetAuthenticationFlags
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// As credenciais serão usadas para autenticar com um proxy.
				/// </summary>
				MFNET_AUTHENTICATION_PROXY = 0x1,

				/// <summary>
				/// As credenciais serão enviadas pela rede não criptografadas.
				/// </summary>
				MFNET_AUTHENTICATION_CLEAR_TEXT = 0x2,

				/// <summary>
				/// As credenciais devem ser de um usuário que está conectado no momento.
				/// </summary>
				MFNET_AUTHENTICATION_LOGGED_ON_USER = 0x4
			};

			/// <summary>
			/// (MFNetCredentialRequirements) - Enumera bandeiras que especificam como o gerenciador de credenciais deve obter credenciais do usuário.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFNetCredentialRequirements
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// O gerenciador de credenciais deve solicitar ao usuário que forneça as credenciais.
				/// </summary>
				REQUIRE_PROMPT = 0x1,

				/// <summary>
				/// As credenciais são salvas para armazenamento persistente. Esta bandeira funciona como uma dica para a interface do id do aplicativo. Se o aplicativo solicitar 
				/// credenciais ao usuário, a interface do usuário pode indicar que as credenciais já foram salvas.
				/// </summary>
				REQUIRE_SAVE_SELECTED = 0x2
			};

			/// <summary>
			/// (MFNetCredentialOptions) - Enumera bandeiras que descrevem opções para as credenciais da rede de cache.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFNetCredentialOptions
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// Permitir que o objeto de cache de credencial salve credenciais no armazenamento persistente.
				/// </summary>
				MFNET_CREDENTIAL_SAVE = 0x1,

				/// <summary>
				/// Não permita que o objeto de cache credencial faça cache das credenciais na memória. Esta bandeira não pode ser combinada com a bandeira MFNET_CREDENTIAL_SAVE.
				/// </summary>
				MFNET_CREDENTIAL_DONT_CACHE = 0x2,

				/// <summary>
				/// O usuário permite que credenciais sejam enviadas pela rede em texto claro. Por padrão, ICarenMFNetCredentialCache::ObterCredencial sempre retorna o REQUIRE_PROMPT flag 
				/// quando os sinalizadores de autenticação incluem MFNET_AUTHENTICATION_CLEAR_TEXT, mesmo que as credenciais em cache estejam disponíveis.
				/// </summary>
				MFNET_CREDENTIAL_ALLOW_CLEAR_TEXT = 0x4
			};

			/// <summary>
			/// (_MFT_ENUM_FLAG)(FALTA DOCUMENTAR) - Enumera bandeiras para registro e enumeração de transformações da Media Foundation (MFTs).
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MFT_ENUM_FLAG
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_SYNCMFT = 0x00000001,
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_ASYNCMFT = 0x00000002, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_HARDWARE = 0x00000004, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_FIELDOFUSE = 0x00000008, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_LOCALMFT = 0x00000010, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_TRANSCODE_ONLY = 0x00000020, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_SORTANDFILTER = 0x00000040,
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_SORTANDFILTER_APPROVED_ONLY = 0x000000C0, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_SORTANDFILTER_WEB_ONLY = 0x00000140, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_SORTANDFILTER_WEB_ONLY_EDGEMODE = 0x00000240, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_UNTRUSTED_STOREMFT = 0x00000400, 
				/// <summary>
				/// 
				/// </summary>
				MFT_ENUM_FLAG_ALL = 0x0000003F,
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_NETWORK)(FALTA DOCUMENTAR) - Enumera bandeiras
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_NETWORK
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_NETWORK_EMPTY = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_NETWORK_IDLE = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_NETWORK_LOADING = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_NETWORK_NO_SOURCE = 3
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_READY)(FALTA DOCUMENTAR) - Enumera bandeiras
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_READY
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_READY_HAVE_NOTHING = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_READY_HAVE_METADATA = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_READY_HAVE_CURRENT_DATA = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_READY_HAVE_FUTURE_DATA = 3,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_READY_HAVE_ENOUGH_DATA = 4
			};
			
			/// <summary>
			/// (MF_MEDIA_ENGINE_CANPLAY)(FALTA DOCUMENTAR) - Enumera bandeiras que especificam a probabilidade de que o Media Engine possa reproduzir um tipo especificado de recurso de mídia.
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_CANPLAY
			{
				/// <summary>
				/// O Media Engine não pode reproduzir o recurso.
				/// </summary>
				MF_MEDIA_ENGINE_CANPLAY_NOT_SUPPORTED = 0,

				/// <summary>
				/// O Media Engine pode ser capaz de reproduzir o recurso.
				/// </summary>
				MF_MEDIA_ENGINE_CANPLAY_MAYBE = 1,

				/// <summary>
				/// O Media Engine provavelmente pode reproduzir o recurso.
				/// </summary>
				MF_MEDIA_ENGINE_CANPLAY_PROBABLY = 2
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_PRELOAD)(FALTA DOCUMENTAR) - Enumera bandeiras
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_PRELOAD
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_PRELOAD_MISSING = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_PRELOAD_EMPTY = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_PRELOAD_NONE = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_PRELOAD_METADATA = 3,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_PRELOAD_AUTOMATIC = 4
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_ERR)(FALTA DOCUMENTAR) - Enumera bandeiras
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_ERR
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_NOERROR = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_ABORTED = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_NETWORK = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_DECODE = 3,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_SRC_NOT_SUPPORTED = 4,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_ERR_ENCRYPTED = 5
			};
			
			/// <summary>
			/// (MF_MEDIA_ENGINE_STATISTIC) - Enumera bandeiras que identificam estatísticas que o Media Engine rastreia durante a reprodução. 
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_STATISTIC
			{
				/// <summary>
				/// O número de quadros de vídeo renderizados. (ULONG, VT_UI4)
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_FRAMES_RENDERED = 0,

				/// <summary>
				/// O número de quadros de vídeo descartados. (ULONG, VT_UI4)
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_FRAMES_DROPPED = 1,

				/// <summary>
				/// O número de bytes que foram baixados desde a última solicitação de faixa HTTP. ULARGE_INTEGER, VT_UI8).
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_BYTES_DOWNLOADED = 2,

				/// <summary>
				/// A porcentagem do buffer de playout preenchido durante o buffer. O valor é um inteiro na faixa de 0-100. (LONG, VT_I4)
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_BUFFER_PROGRESS = 3,

				/// <summary>
				/// Os quadros por segundo. (FLOAT, VT_R4)
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_FRAMES_PER_SECOND = 4,

				/// <summary>
				/// A quantidade de jitter de reprodução. (DUPLO, VT_R8). Suportado no Windows 8.1 e posterior.
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_PLAYBACK_JITTER = 5,

				/// <summary>
				/// O número de quadros corrompidos. (ULONG, VT_UI4). Suportado no Windows 8.1 e posterior.
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_FRAMES_CORRUPTED = 6,

				/// <summary>
				/// A quantidade total de atraso do quadro. (DUPLO, VT_R8). Suportado no Windows 8.1 e posterior.
				/// </summary>
				MF_MEDIA_ENGINE_STATISTIC_TOTAL_FRAME_DELAY = 7
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_S3D_PACKING_MODE) - Enumera bandeiras que especificam o layout para um quadro de vídeo 3D embalado(Packed).
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_S3D_PACKING_MODE
			{
				/// <summary>
				/// Nenhum.
				/// </summary>
				MF_MEDIA_ENGINE_S3D_PACKING_MODE_NONE = 0,

				/// <summary>
				/// As vistas são embaladas lado a lado em um único quadro.
				/// </summary>
				MF_MEDIA_ENGINE_S3D_PACKING_MODE_SIDE_BY_SIDE = 1,

				/// <summary>
				/// As vistas são embaladas de cima para baixo em um único quadro.
				/// </summary>
				MF_MEDIA_ENGINE_S3D_PACKING_MODE_TOP_BOTTOM = 2
			};

			/// <summary>
			/// (MF3DVideoOutputType) - Enumera bandeiras que especificam como produzir uma transmissão de vídeo estereoscópica 3D.
			/// </summary>
			public enum class CA_MF3DVideoOutputType
			{
				/// <summary>
				/// Apenas para a exibição base. Descarte a outra vista.
				/// </summary>
				MF3DVideoOutputType_BaseView = 0,

				/// <summary>
				/// Saída uma visualização estéreo (dois buffers).
				/// </summary>
				MF3DVideoOutputType_Stereo = 1
			};
			
			/// <summary>
			/// (MF_MEDIA_ENGINE_SEEK_MODE) - Enumera bandeiras que definem valores para o modo de busca do motor de mídia.
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_SEEK_MODE
			{
				/// <summary>
				/// Especifica a busca normal.
				/// </summary>
				MF_MEDIA_ENGINE_SEEK_MODE_NORMAL = 0,

				/// <summary>
				/// Especifica uma busca aproximada.
				/// </summary>
				MF_MEDIA_ENGINE_SEEK_MODE_APPROXIMATE = 1
			};
			
			/// <summary>
			/// (MF_MEDIA_ENGINE_CREATEFLAGS)(FALTA DOCUMENTAR) - Enumera bandeiras para o método ICarenMFMediaEngineClassFactory::CreateInstance.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_MEDIA_ENGINE_CREATEFLAGS
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_AUDIOONLY = 0x1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_WAITFORSTABLE_STATE = 0x2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_FORCEMUTE = 0x4,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_REAL_TIME_MODE = 0x8,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_DISABLE_LOCAL_PLUGINS = 0x10,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_CREATEFLAGS_MASK = 0x1f
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_EVENT)(FALTA DOCUMENTAR) - Enumera códigos de eventos para o Media Engine.
			/// </summary>
			public enum class CA_MF_MEDIA_ENGINE_EVENT
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_LOADSTART = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_PROGRESS = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_SUSPEND = 3,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_ABORT = 4,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_ERROR = 5,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_EMPTIED = 6,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_STALLED = 7,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_PLAY = 8,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_PAUSE = 9,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_LOADEDMETADATA = 10,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_LOADEDDATA = 11,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_WAITING = 12,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_PLAYING = 13,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_CANPLAY = 14,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_CANPLAYTHROUGH = 15,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_SEEKING = 16,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_SEEKED = 17,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_TIMEUPDATE = 18,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_ENDED = 19,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_RATECHANGE = 20,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_DURATIONCHANGE = 21,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_VOLUMECHANGE = 22,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_FORMATCHANGE = 1000,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_PURGEQUEUEDEVENTS = 1001,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_TIMELINE_MARKER = 1002,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_BALANCECHANGE = 1003,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_DOWNLOADCOMPLETE = 1004,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_BUFFERINGSTARTED = 1005,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_BUFFERINGENDED = 1006,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_FRAMESTEPCOMPLETED = 1007,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_NOTIFYSTABLESTATE = 1008,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_FIRSTFRAMEREADY = 1009,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_TRACKSCHANGE = 1010,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_OPMINFO = 1011,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_RESOURCELOST = 1012,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_DELAYLOADEVENT_CHANGED = 1013,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_STREAMRENDERINGERROR = 1014,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_SUPPORTEDRATES_CHANGED = 1015,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_EVENT_AUDIOENDPOINTCHANGE = 1016
			};

			/// <summary>
			/// (MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS)(FALTA DOCUMENTAR) - Enumera bandeiras que especificam os requisitos de proteção de conteúdo para um quadro de vídeo.
			/// </summary>
			[FlagsAttribute]
			public enum class CA_MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAGS
			{
				/// <summary>
				/// Utilizado para suporte, não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAG_PROTECTED = 0x1,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAG_REQUIRES_SURFACE_PROTECTION = 0x2,
				/// <summary>
				/// 
				/// </summary>
				MF_MEDIA_ENGINE_FRAME_PROTECTION_FLAG_REQUIRES_ANTI_SCREEN_SCRAPE_PROTECTION = 0x4
			};

			/// <summary>
			/// (MF_MSE_ERROR)(FALTA DOCUMENTAR) - Enumera bandeiras que definem os diferentes estados de erro da ICarenMFMediaSourceExtension.
			/// </summary>
			public enum class CA_MF_MSE_ERROR
			{
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_ERROR_NOERROR = 0,
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_ERROR_NETWORK = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_ERROR_DECODE = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_ERROR_UNKNOWN_ERROR = 3
			};

			/// <summary>
			/// (MF_MSE_READY)(FALTA DOCUMENTAR) - Enumera bandeiras que definem os diferentes estados prontos da ICarenMFMediaSourceExtension.
			/// </summary>
			public enum class CA_MF_MSE_READY
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				MF_MSE_READY_CLOSED = 1,
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_READY_OPEN = 2,
				/// <summary>
				/// 
				/// </summary>
				MF_MSE_READY_ENDED = 3
			};





			//WIC Enumerações

			/// <summary> 
			/// (WIC8BIMIptcDigestProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WIC8BIMIptcDigestProperties
			{

				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcDigestPString = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcDigestIptcDigest = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcDigestProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WIC8BIMIptcProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WIC8BIMIptcProperties
			{
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcPString = 0,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcEmbeddedIPTC = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMIptcProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WIC8BIMResolutionInfoProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WIC8BIMResolutionInfoProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoPString = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoHResolution = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoHResolutionUnit = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoWidthUnit = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoVResolution = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoVResolutionUnit = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoHeightUnit = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WIC8BIMResolutionInfoProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapAlphaChannelOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapAlphaChannelOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapUseAlpha = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapUsePremultipliedAlpha = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapIgnoreAlpha = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPALPHACHANNELOPTIONS_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapCreateCacheOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapCreateCacheOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapNoCache = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapCacheOnDemand = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapCacheOnLoad = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPCREATECACHEOPTION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapDecoderCapabilities)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WICBitmapDecoderCapabilities
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICBitmapDecoderCapabilitySameEncoder = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDecoderCapabilityCanDecodeAllImages = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDecoderCapabilityCanDecodeSomeImages = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDecoderCapabilityCanEnumerateMetadata = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDecoderCapabilityCanDecodeThumbnail = 0x10,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPDECODERCAPABILITIES_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapDitherType)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapDitherType
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeNone = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeSolid = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeOrdered4x4 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeOrdered8x8 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeOrdered16x16 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeSpiral4x4 = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeSpiral8x8 = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeDualSpiral4x4 = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeDualSpiral8x8 = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapDitherTypeErrorDiffusion = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPDITHERTYPE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapEncoderCacheOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapEncoderCacheOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapEncoderCacheInMemory = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapEncoderCacheTempFile = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapEncoderNoCache = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPENCODERCACHEOPTION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapInterpolationMode)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapInterpolationMode
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapInterpolationModeNearestNeighbor = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapInterpolationModeLinear = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapInterpolationModeCubic = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapInterpolationModeFant = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapInterpolationModeHighQualityCubic = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPINTERPOLATIONMODE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapLockFlags)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapLockFlags
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICBitmapLockRead = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapLockWrite = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPLOCKFLAGS_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapPaletteType)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICBitmapPaletteType
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeCustom = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeMedianCut = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedBW = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone8 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone27 = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone64 = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone125 = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone216 = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedWebPalette = WICBitmapPaletteTypeFixedHalftone216,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone252 = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedHalftone256 = 0x9,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedGray4 = 0xa,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedGray16 = 0xb,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapPaletteTypeFixedGray256 = 0xc,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPPALETTETYPE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICBitmapTransformOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WICBitmapTransformOptions
			{
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformRotate0 = 0,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformRotate90 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformRotate180 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformRotate270 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformFlipHorizontal = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICBitmapTransformFlipVertical = 0x10,
				/// <summary>
				/// 
				/// </summary>
				WICBITMAPTRANSFORMOPTIONS_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICColorContextType)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICColorContextType
			{
				/// <summary>
				/// 
				/// </summary>
				WICColorContextUninitialized = 0,
				/// <summary>
				/// 
				/// </summary>
				WICColorContextProfile = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICColorContextExifColorSpace = 0x2
			};

			/// <summary> 
			/// (WICComponentEnumerateOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICComponentEnumerateOptions : Int64
			{
				/// <summary>
				/// 
				/// </summary>
				WICComponentEnumerateDefault = 0,
				/// <summary>
				/// 
				/// </summary>
				WICComponentEnumerateRefresh = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICComponentEnumerateDisabled = 0x80000000,
				/// <summary>
				/// 
				/// </summary>
				WICComponentEnumerateUnsigned = 0x40000000,
				/// <summary>
				/// 
				/// </summary>
				WICComponentEnumerateBuiltInOnly = 0x20000000,
				/// <summary>
				/// 
				/// </summary>
				WICCOMPONENTENUMERATEOPTIONS_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICComponentSigning)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICComponentSigning : Int64
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICComponentSigned = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICComponentUnsigned = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICComponentSafe = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICComponentDisabled = 0x80000000,
				/// <summary>
				/// 
				/// </summary>
				WICCOMPONENTSIGNING_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICComponentType)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICComponentType
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICDecoder = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICEncoder = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatConverter = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICMetadataReader = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICMetadataWriter = 0x10,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormat = 0x20,
				/// <summary>
				/// 
				/// </summary>
				WICAllComponents = 0x3f,
				/// <summary>
				/// 
				/// </summary>
				WICCOMPONENTTYPE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICDecodeOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICDecodeOptions
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICDecodeMetadataCacheOnDemand = 0,
				/// <summary>
				/// 
				/// </summary>
				WICDecodeMetadataCacheOnLoad = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICMETADATACACHEOPTION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICGifApplicationExtensionProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICGifApplicationExtensionProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICGifApplicationExtensionApplication = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICGifApplicationExtensionData = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICGifApplicationExtensionProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICGifCommentExtensionProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICGifCommentExtensionProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICGifCommentExtensionText = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICGifCommentExtensionProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICGifGraphicControlExtensionProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICGifGraphicControlExtensionProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionDisposal = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionUserInputFlag = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionTransparencyFlag = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionDelay = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionTransparentColorIndex = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICGifGraphicControlExtensionProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICGifImageDescriptorProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICGifImageDescriptorProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorLeft = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorTop = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorWidth = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorHeight = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorLocalColorTableFlag = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorInterlaceFlag = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorSortFlag = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorLocalColorTableSize = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICGifImageDescriptorProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICGifLogicalScreenDescriptorProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICGifLogicalScreenDescriptorProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenSignature = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorWidth = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorHeight = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorGlobalColorTableFlag = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorColorResolution = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorSortFlag = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorGlobalColorTableSize = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorBackgroundColorIndex = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorPixelAspectRatio = 0x9,
				/// <summary>
				/// 
				/// </summary>
				WICGifLogicalScreenDescriptorProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegCommentProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegCommentProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICJpegCommentText = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegCommentProperties_FORCE_DWORD = 0x7fffffff
			};
	
			/// <summary> 
			/// (WICJpegChrominanceProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegChrominanceProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICJpegChrominanceTable = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegChrominanceProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegIndexingOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegIndexingOptions
			{
				/// <summary>
				/// 
				/// </summary>
				WICJpegIndexingOptionsGenerateOnDemand = 0,
				/// <summary>
				/// 
				/// </summary>
				WICJpegIndexingOptionsGenerateOnLoad = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegIndexingOptions_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegLuminanceProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegLuminanceProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICJpegLuminanceTable = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegLuminanceProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegYCrCbSubsamplingOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegYCrCbSubsamplingOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICJpegYCrCbSubsamplingDefault = 0,
				/// <summary>
				/// 
				/// </summary>
				WICJpegYCrCbSubsampling420 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegYCrCbSubsampling422 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICJpegYCrCbSubsampling444 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICJpegYCrCbSubsampling440 = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICJPEGYCRCBSUBSAMPLING_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICMetadataCreationOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICMetadataCreationOptions
			{
				/// <summary>
				/// 
				/// </summary>
				WICMetadataCreationDefault = 0,
				/// <summary>
				/// 
				/// </summary>
				WICMetadataCreationAllowUnknown = WICMetadataCreationDefault,
				/// <summary>
				/// 
				/// </summary>
				WICMetadataCreationFailUnknown = 0x10000,
			};

			/// <summary> 
			/// (WICNamedWhitePoint)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WICNamedWhitePoint
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICWhitePointDefault = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointDaylight = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointCloudy = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointShade = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointTungsten = 0x10,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointFluorescent = 0x20,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointFlash = 0x40,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointUnderwater = 0x80,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointCustom = 0x100,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointAutoWhiteBalance = 0x200,
				/// <summary>
				/// 
				/// </summary>
				WICWhitePointAsShot = WICWhitePointDefault,
				/// <summary>
				/// 
				/// </summary>
				WICNAMEDWHITEPOINT_FORCE_DWORD = 0x7fffffff
			};
			
			/// <summary> 
			/// (WICPersistOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPersistOptions
			{
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionDefault = 0,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionLittleEndian = 0,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionBigEndian = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionStrictFormat = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionNoCacheStream = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionPreferUTF8 = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICPersistOptionMask = 0xffff
			};
			
			/// <summary> 
			/// (WICPixelFormatNumericRepresentation)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPixelFormatNumericRepresentation
			{
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationUnspecified = 0,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationIndexed = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationUnsignedInteger = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationSignedInteger = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationFixed = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentationFloat = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICPixelFormatNumericRepresentation_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPlanarOptions)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPlanarOptions
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPlanarOptionsDefault = 0,
				/// <summary>
				/// 
				/// </summary>
				WICPlanarOptionsPreserveSubsampling = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPLANAROPTIONS_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICProgressOperation)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WICProgressOperation
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICProgressOperationCopyPixels = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICProgressOperationWritePixels = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICProgressOperationAll = 0xffff,
				/// <summary>
				/// 
				/// </summary>
				WICPROGRESSOPERATION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngBkgdProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngBkgdProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngBkgdBackgroundColor = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngBkgdProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngChrmProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngChrmProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				WICPngChrmWhitePointX = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmWhitePointY = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmRedX = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmRedY = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmGreenX = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmGreenY = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmBlueX = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmBlueY = 0x8,
				/// <summary>
				/// 
				/// </summary>
				WICPngChrmProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngFilterOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngFilterOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterUnspecified = 0,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterNone = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterSub = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterUp = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterAverage = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterPaeth = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICPngFilterAdaptive = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICPNGFILTEROPTION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngGamaProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngGamaProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngGamaGamma = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngGamaProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngHistProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngHistProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngHistFrequencies = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngHistProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngIccpProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngIccpProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngIccpProfileName = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngIccpProfileData = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPngIccpProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngItxtProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngItxtProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngItxtKeyword = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngItxtCompressionFlag = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPngItxtLanguageTag = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICPngItxtTranslatedKeyword = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPngItxtText = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICPngItxtProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngSrgbProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngSrgbProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngSrgbRenderingIntent = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngSrgbProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICPngTimeProperties)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICPngTimeProperties
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICPngTimeYear = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeMonth = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeDay = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeHour = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeMinute = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeSecond = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICPngTimeProperties_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICProgressNotification)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_WICProgressNotification : Int64
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICProgressNotificationBegin = 0x10000,
				/// <summary>
				/// 
				/// </summary>
				WICProgressNotificationEnd = 0x20000,
				/// <summary>
				/// 
				/// </summary>
				WICProgressNotificationFrequent = 0x40000,
				/// <summary>
				/// 
				/// </summary>
				WICProgressNotificationAll = 0xffff0000,
				/// <summary>
				/// 
				/// </summary>
				WICPROGRESSNOTIFICATION_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICRawParameterSet)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICRawParameterSet
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICAsShotParameterSet = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICUserAdjustedParameterSet = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICAutoAdjustedParameterSet = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICRAWPARAMETERSET_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICSectionAccessLevel)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICSectionAccessLevel
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				WICSectionAccessLevelRead = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICSectionAccessLevelReadWrite = 0x3,
			};

			/// <summary> 
			/// (WICTiffCompressionOption)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICTiffCompressionOption
			{
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionDontCare = 0,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionNone = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionCCITT3 = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionCCITT4 = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionLZW = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionRLE = 0x5,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionZIP = 0x6,
				/// <summary>
				/// 
				/// </summary>
				WICTiffCompressionLZWHDifferencing = 0x7,
				/// <summary>
				/// 
				/// </summary>
				WICTIFFCOMPRESSIONOPTION_FORCE_DWORD = 0x7fffffff
			};
			
			/// <summary> 
			/// (WICDdsDimension)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICDdsDimension
			{
				/// <summary>
				/// 
				/// </summary>
				WICDdsTexture1D = 0,
				/// <summary>
				/// 
				/// </summary>
				WICDdsTexture2D = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICDdsTexture3D = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICDdsTextureCube = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICDDSTEXTURE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICDdsAlphaMode)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICDdsAlphaMode
			{
				/// <summary>
				/// 
				/// </summary>
				WICDdsAlphaModeUnknown = 0,
				/// <summary>
				/// 
				/// </summary>
				WICDdsAlphaModeStraight = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICDdsAlphaModePremultiplied = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICDdsAlphaModeOpaque = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICDdsAlphaModeCustom = 0x4,
				/// <summary>
				/// 
				/// </summary>
				WICDDSALPHAMODE_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegScanType)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegScanType
			{
				/// <summary>
				/// 
				/// </summary>
				WICJpegScanTypeInterleaved = 0,
				/// <summary>
				/// 
				/// </summary>
				WICJpegScanTypePlanarComponents = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegScanTypeProgressive = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICJpegScanType_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICJpegTransferMatrix)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICJpegTransferMatrix
			{
				/// <summary>
				/// 
				/// </summary>
				WICJpegTransferMatrixIdentity = 0,
				/// <summary>
				/// 
				/// </summary>
				WICJpegTransferMatrixBT601 = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICJpegTransferMatrix_FORCE_DWORD = 0x7fffffff
			};

			/// <summary> 
			/// (WICRawCapabilities)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICRawCapabilities
			{
				/// <summary>
				/// 
				/// </summary>
				WICRawCapabilityNotSupported = 0,
				/// <summary>
				/// 
				/// </summary>
				WICRawCapabilityGetSupported = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICRawCapabilityFullySupported = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICRAWCAPABILITIES_FORCE_DWORD = 0x7fffffff
			};
			
			/// <summary> 
			/// (WICRawRotationCapabilities)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICRawRotationCapabilities
			{
				/// <summary>
				/// 
				/// </summary>
				WICRawRotationCapabilityNotSupported = 0x0,
				/// <summary>
				/// 
				/// </summary>
				WICRawRotationCapabilityGetSupported = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICRawRotationCapabilityNinetyDegreesSupported = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICRawRotationCapabilityFullySupported = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICRAWROTATIONCAPABILITIES_FORCE_DWORD = 0x7fffffff

			};
		
			/// <summary> 
			/// (WICRawRenderMode)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_WICRawRenderMode
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				WICRawRenderModeDraft = 0x1,
				/// <summary>
				/// 
				/// </summary>
				WICRawRenderModeNormal = 0x2,
				/// <summary>
				/// 
				/// </summary>
				WICRawRenderModeBestQuality = 0x3,
				/// <summary>
				/// 
				/// </summary>
				WICRAWRENDERMODE_FORCE_DWORD = 0x7fffffff
			};




			//Direct2D Enumerações.

			/// <summary> 
			/// (D2D1_ALPHA_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ALPHA_MODE : Int64
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_ALPHA_MODE_UNKNOWN = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_ALPHA_MODE_PREMULTIPLIED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_ALPHA_MODE_STRAIGHT = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_ALPHA_MODE_IGNORE = 3,
			};	

			/// <summary> 
			/// (D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_ANISOTROPIC = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = 5,
			};
			
			/// <summary> 
			/// (D2D1_2DAFFINETRANSFORM_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_2DAFFINETRANSFORM_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_PROP_BORDER_MODE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_2DAFFINETRANSFORM_PROP_SHARPNESS = 3,
			};
			
			/// <summary> 
			/// (D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_INTERPOLATION_MODE_ANISOTROPIC = 4,
			};

			/// <summary> 
			/// (D2D1_3DPERSPECTIVETRANSFORM_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_3DPERSPECTIVETRANSFORM_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_INTERPOLATION_MODE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_BORDER_MODE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_DEPTH = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_PERSPECTIVE_ORIGIN = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_LOCAL_OFFSET = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_GLOBAL_OFFSET = 5,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_ROTATION_ORIGIN = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DPERSPECTIVETRANSFORM_PROP_ROTATION = 7,
			};
			
			/// <summary> 
			/// (D2D1_3DTRANSFORM_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_3DTRANSFORM_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_INTERPOLATION_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_INTERPOLATION_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_INTERPOLATION_MODE_ANISOTROPIC = 4,
			};
			
			/// <summary> 
			/// (D2D1_3DTRANSFORM_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_3DTRANSFORM_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_PROP_INTERPOLATION_MODE = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_PROP_BORDER_MODE = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_3DTRANSFORM_PROP_TRANSFORM_MATRIX = 2,
			};
			
			/// <summary> 
			/// (D2D1_ANTIALIAS_MODE.)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ANTIALIAS_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_ANTIALIAS_MODE_PER_PRIMITIVE = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_ANTIALIAS_MODE_ALIASED = 1,
			};
			
			/// <summary> 
			/// (D2D1_ARC_SIZE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ARC_SIZE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_ARC_SIZE_SMALL = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_ARC_SIZE_LARGE = 1,
			};
			
			/// <summary> 
			/// (D2D1_ARITHMETICCOMPOSITE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ARITHMETICCOMPOSITE_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_ARITHMETICCOMPOSITE_PROP_COEFFICIENTS = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_ARITHMETICCOMPOSITE_PROP_CLAMP_OUTPUT = 1,
			};
			
			/// <summary> 
			/// (D2D1_ATLAS_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ATLAS_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_ATLAS_PROP_INPUT_RECT = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_ATLAS_PROP_INPUT_PADDING_RECT = 1,
			};
			
			/// <summary> 
			/// (D2D1_BITMAPSOURCE_ALPHA_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAPSOURCE_ALPHA_MODE
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ALPHA_MODE_PREMULTIPLIED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ALPHA_MODE_STRAIGHT = 2,
			};
			
			/// <summary> 
			/// (D2D1_BITMAPSOURCE_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAPSOURCE_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_INTERPOLATION_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_INTERPOLATION_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_INTERPOLATION_MODE_FANT = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_INTERPOLATION_MODE_MIPMAP_LINEAR = 7,
			};
			
			/// <summary> 
			/// (D2D1_BITMAPSOURCE_ORIENTATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAPSOURCE_ORIENTATION
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_DEFAULT = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_FLIP_HORIZONTAL = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE180 = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE180_FLIP_HORIZONTAL = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE270_FLIP_HORIZONTAL = 5,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE90 = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE90_FLIP_HORIZONTAL = 7,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_ORIENTATION_ROTATE_CLOCKWISE270 = 8,
			};
			
			/// <summary> 
			/// (D2D1_BITMAPSOURCE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAPSOURCE_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_WIC_BITMAP_SOURCE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_SCALE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_INTERPOLATION_MODE = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_ENABLE_DPI_CORRECTION = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_ALPHA_MODE = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAPSOURCE_PROP_ORIENTATION = 5,
			};
			
			/// <summary> 
			/// (D2D1_BITMAP_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAP_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = D2D1_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_LINEAR,
			};
			
			/// <summary> 
			/// (D2D1_BITMAP_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BITMAP_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_OPTIONS_NONE = 0x00000000,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_OPTIONS_TARGET = 0x00000001,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_OPTIONS_CANNOT_DRAW = 0x00000002,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_OPTIONS_CPU_READ = 0x00000004,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BITMAP_OPTIONS_GDI_COMPATIBLE = 0x00000008,
			};
			
			/// <summary> 
			/// (D2D1_BLEND)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BLEND
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_ZERO = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_ONE = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_SRC_COLOR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_INV_SRC_COLOR = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_SRC_ALPHA = 5,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_INV_SRC_ALPHA = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_DEST_ALPHA = 7,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_INV_DEST_ALPHA = 8,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_DEST_COLOR = 9,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_INV_DEST_COLOR = 10,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_SRC_ALPHA_SAT = 11,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_BLEND_FACTOR = 14,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_INV_BLEND_FACTOR = 15,
			};
			
			/// <summary> 
			/// (D2D1_BLEND_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BLEND_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_MULTIPLY = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_SCREEN = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_DARKEN = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LIGHTEN = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_DISSOLVE = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_COLOR_BURN = 5,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LINEAR_BURN = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_DARKER_COLOR = 7,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LIGHTER_COLOR = 8,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_COLOR_DODGE = 9,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LINEAR_DODGE = 10,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_OVERLAY = 11,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_SOFT_LIGHT = 12,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_HARD_LIGHT = 13,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_VIVID_LIGHT = 14,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LINEAR_LIGHT = 15,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_PIN_LIGHT = 16,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_HARD_MIX = 17,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_DIFFERENCE = 18,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_EXCLUSION = 19,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_HUE = 20,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_SATURATION = 21,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_COLOR = 22,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_LUMINOSITY = 23,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_SUBTRACT = 24,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_MODE_DIVISION = 25,
			};
			
			/// <summary> 
			/// (D2D1_BLEND_OPERATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BLEND_OPERATION
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_OPERATION_ADD = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_OPERATION_SUBTRACT = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_OPERATION_REV_SUBTRACT = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_OPERATION_MIN = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_OPERATION_MAX = 5,
			};
			
			/// <summary> 
			/// (D2D1_BLEND_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BLEND_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BLEND_PROP_MODE = 0,
			};
			
			/// <summary> 
			/// (D2D1_BORDER_EDGE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BORDER_EDGE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_EDGE_MODE_CLAMP = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_EDGE_MODE_WRAP = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_EDGE_MODE_MIRROR = 2,
			};
			
			/// <summary> 
			/// (D2D1_BORDER_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BORDER_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_MODE_SOFT = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_MODE_HARD = 1,
			};
			
			/// <summary> 
			/// (D2D1_BORDER_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BORDER_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_PROP_EDGE_MODE_X = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BORDER_PROP_EDGE_MODE_Y = 1,
			};
			
			/// <summary> 
			/// (D2D1_BRIGHTNESS_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BRIGHTNESS_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BRIGHTNESS_PROP_WHITE_POINT = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BRIGHTNESS_PROP_BLACK_POINT = 1,
			};
			
			/// <summary> 
			/// (D2D1_BUFFER_PRECISION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_BUFFER_PRECISION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_UNKNOWN = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_8BPC_UNORM = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_8BPC_UNORM_SRGB = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_16BPC_UNORM = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_16BPC_FLOAT = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_BUFFER_PRECISION_32BPC_FLOAT = 5,
			};
			
			/// <summary> 
			/// (D2D1_CAP_STYLE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CAP_STYLE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CAP_STYLE_FLAT = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CAP_STYLE_SQUARE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CAP_STYLE_ROUND = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CAP_STYLE_TRIANGLE = 3,
			};
			
			/// <summary> 
			/// (D2D1_CHANGE_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CHANGE_TYPE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANGE_TYPE_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANGE_TYPE_PROPERTIES = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANGE_TYPE_CONTEXT = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANGE_TYPE_GRAPH = 3,
			};
			
			/// <summary> 
			/// (D2D1_CHANNEL_DEPTH)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CHANNEL_DEPTH
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_DEPTH_DEFAULT = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_DEPTH_1 = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_DEPTH_4 = 4,
			};
			
			/// <summary> 
			/// (D2D1_CHANNEL_SELECTOR)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CHANNEL_SELECTOR
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_SELECTOR_R = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_SELECTOR_G = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_SELECTOR_B = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHANNEL_SELECTOR_A = 3,
			};
			
			/// <summary> 
			/// (D2D1_CHROMAKEY_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CHROMAKEY_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CHROMAKEY_PROP_COLOR = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_CHROMAKEY_PROP_TOLERANCE = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_CHROMAKEY_PROP_INVERT_ALPHA = 2,

				/// <summary>
				/// 
				/// </summary>
				D2D1_CHROMAKEY_PROP_FEATHER = 3,
			};
			
			/// <summary> 
			/// (D2D1_COLORMANAGEMENT_ALPHA_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMANAGEMENT_ALPHA_MODE
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_ALPHA_MODE_PREMULTIPLIED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_ALPHA_MODE_STRAIGHT = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLORMANAGEMENT_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMANAGEMENT_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_SOURCE_COLOR_CONTEXT = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_SOURCE_RENDERING_INTENT = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_DESTINATION_COLOR_CONTEXT = 2,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_DESTINATION_RENDERING_INTENT = 3,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_ALPHA_MODE = 4,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_PROP_QUALITY = 5,
			};
			
			/// <summary> 
			/// (D2D1_COLORMANAGEMENT_QUALITY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMANAGEMENT_QUALITY
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_QUALITY_PROOF = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_QUALITY_NORMAL = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_QUALITY_BEST = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLORMANAGEMENT_RENDERING_INTENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMANAGEMENT_RENDERING_INTENT
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_RENDERING_INTENT_PERCEPTUAL = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_RENDERING_INTENT_RELATIVE_COLORIMETRIC = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_RENDERING_INTENT_SATURATION = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMANAGEMENT_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC = 3,
			};
			
			/// <summary> 
			/// (D2D1_COLORMATRIX_ALPHA_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMATRIX_ALPHA_MODE
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMATRIX_ALPHA_MODE_PREMULTIPLIED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMATRIX_ALPHA_MODE_STRAIGHT = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLORMATRIX_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLORMATRIX_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMATRIX_PROP_COLOR_MATRIX = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMATRIX_PROP_ALPHA_MODE = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DEFAULT = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DISABLE = 1,
			};

			/// <summary> 
			/// (D2D1_COLOR_CONTEXT_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLOR_CONTEXT_TYPE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_CONTEXT_TYPE_ICC = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_CONTEXT_TYPE_SIMPLE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_CONTEXT_TYPE_DXGI = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLOR_SPACE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLOR_SPACE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_SPACE_CUSTOM = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_SPACE_SRGB = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_SPACE_SCRGB = 2,
			};
			
			/// <summary> 
			/// (D2D1_COLOR_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COLOR_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_INTERPOLATION_MODE_STRAIGHT = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED = 1,
			};
			
			/// <summary> 
			/// (D2D1_COMBINE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COMBINE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMBINE_MODE_UNION = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COMBINE_MODE_INTERSECT = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COMBINE_MODE_XOR = 2,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COMBINE_MODE_EXCLUDE = 3,
			};
			
			/// <summary> 
			/// (D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE = 0x00000000,

				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE = 0x00000001,
			};
			
			/// <summary> 
			/// (D2D1_COMPOSITE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COMPOSITE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_SOURCE_OVER = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_DESTINATION_OVER = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_SOURCE_IN = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_DESTINATION_IN = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_SOURCE_OUT = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_DESTINATION_OUT = 5,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_SOURCE_ATOP = 6,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_DESTINATION_ATOP = 7,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_XOR = 8,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_PLUS = 9,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_SOURCE_COPY = 10,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_BOUNDED_SOURCE_COPY = 11,
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_MODE_MASK_INVERT = 12,
			};
			
			/// <summary> 
			/// (D2D1_COMPOSITE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_COMPOSITE_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_COMPOSITE_PROP_MODE = 0,
			};
			
			/// <summary> 
			/// (D2D1_CONTRAST_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CONTRAST_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONTRAST_PROP_CONTRAST = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_CONTRAST_PROP_CLAMP_INPUT = 1,
			};
			
			/// <summary> 
			/// (D2D1_CONVOLVEMATRIX_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CONVOLVEMATRIX_PROP
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_KERNEL_UNIT_LENGTH = 0,

				/// <summary>
				/// Nome Propriedade: "ScaleMode"
				/// Tipo Propriedade: D2D1_CONVOLVEMATRIX_SCALE_MODE
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_SCALE_MODE = 1,

				/// <summary>
				/// Property Name: "KernelSizeX"
				/// Property Type: UINT32
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X = 2,

				/// <summary>
				/// Property Name: "KernelSizeY"
				/// Property Type: UINT32
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y = 3,

				/// <summary>
				/// Property Name: "KernelMatrix"
				/// Property Type: (blob)
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX = 4,

				/// <summary>
				/// Property Name: "Divisor"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_DIVISOR = 5,

				/// <summary>
				/// Property Name: "Bias"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_BIAS = 6,

				/// <summary>
				/// Property Name: "KernelOffset"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_KERNEL_OFFSET = 7,

				/// <summary>
				/// Property Name: "PreserveAlpha"
				/// Property Type: BOOL
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_PRESERVE_ALPHA = 8,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_BORDER_MODE = 9,

				/// <summary>
				/// Property Name: "ClampOutput"
				/// Property Type: BOOL
				/// </summary>
				D2D1_CONVOLVEMATRIX_PROP_CLAMP_OUTPUT = 10,
			};
			
			/// <summary> 
			/// (D2D1_CONVOLVEMATRIX_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CONVOLVEMATRIX_SCALE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_ANISOTROPIC = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_CONVOLVEMATRIX_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,

			};
			
			/// <summary> 
			/// (D2D1_CROP_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_CROP_PROP
			{
				/// <summary>
				/// Property Name: "Rect"
				/// Property Type: D2D1_VECTOR_4F
				/// </summary>
				D2D1_CROP_PROP_RECT = 0,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_CROP_PROP_BORDER_MODE = 1,

			};
			
			/// <summary> 
			/// (D2D1_DASH_STYLE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DASH_STYLE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_SOLID = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_DASH = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_DOT = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_DASH_DOT = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_DASH_DOT_DOT = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DASH_STYLE_CUSTOM = 5,
			};
			
			/// <summary> 
			/// (D2D1_DC_INITIALIZE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DC_INITIALIZE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DC_INITIALIZE_MODE_COPY = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_DC_INITIALIZE_MODE_CLEAR = 1,
			};
			
			/// <summary> 
			/// (D2D1_DEBUG_LEVEL)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DEBUG_LEVEL
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DEBUG_LEVEL_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DEBUG_LEVEL_ERROR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DEBUG_LEVEL_WARNING = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DEBUG_LEVEL_INFORMATION = 3,
			};
			
			/// <summary> 
			/// (D2D1_DEVICE_CONTEXT_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DEVICE_CONTEXT_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DEVICE_CONTEXT_OPTIONS_NONE = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS = 1,
			};
			
			/// <summary> 
			/// (D2D1_DIRECTIONALBLUR_OPTIMIZATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DIRECTIONALBLUR_OPTIMIZATION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DIRECTIONALBLUR_OPTIMIZATION_SPEED = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DIRECTIONALBLUR_OPTIMIZATION_BALANCED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DIRECTIONALBLUR_OPTIMIZATION_QUALITY = 2,
			};
			
			/// <summary> 
			/// (D2D1_DIRECTIONALBLUR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DIRECTIONALBLUR_PROP
			{
				/// <summary>
				/// Property Name: "StandardDeviation"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION = 0,

				/// <summary>
				/// Property Name: "Angle"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DIRECTIONALBLUR_PROP_ANGLE = 1,

				/// <summary>
				/// Property Name: "Optimization"
				/// Property Type: D2D1_DIRECTIONALBLUR_OPTIMIZATION
				/// </summary>
				D2D1_DIRECTIONALBLUR_PROP_OPTIMIZATION = 2,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_DIRECTIONALBLUR_PROP_BORDER_MODE = 3,
			};
			
			/// <summary> 
			/// (D2D1_DISCRETETRANSFER_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISCRETETRANSFER_PROP
			{
				/// <summary>
				/// Property Name: "RedTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_RED_TABLE = 0,

				/// <summary>
				/// Property Name: "RedDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_RED_DISABLE = 1,

				/// <summary>
				/// Property Name: "GreenTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_GREEN_TABLE = 2,

				/// <summary>
				/// Property Name: "GreenDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_GREEN_DISABLE = 3,

				/// <summary>
				/// Property Name: "BlueTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_BLUE_TABLE = 4,

				/// <summary>
				/// Property Name: "BlueDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_BLUE_DISABLE = 5,

				/// <summary>
				/// Property Name: "AlphaTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_ALPHA_TABLE = 6,

				/// <summary>
				/// Property Name: "AlphaDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_ALPHA_DISABLE = 7,

				/// <summary>
				/// Property Name: "ClampOutput"
				/// Property Type: BOOL
				/// </summary>
				D2D1_DISCRETETRANSFER_PROP_CLAMP_OUTPUT = 8,
			};
			
			/// <summary> 
			/// (D2D1_DISPLACEMENTMAP_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISPLACEMENTMAP_PROP
			{
				/// <summary>
				/// Property Name: "Scale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISPLACEMENTMAP_PROP_SCALE = 0,

				/// <summary>
				/// Property Name: "XChannelSelect"
				/// Property Type: D2D1_CHANNEL_SELECTOR
				/// </summary>
				D2D1_DISPLACEMENTMAP_PROP_X_CHANNEL_SELECT = 1,

				/// <summary>
				/// Property Name: "YChannelSelect"
				/// Property Type: D2D1_CHANNEL_SELECTOR
				/// </summary>
				D2D1_DISPLACEMENTMAP_PROP_Y_CHANNEL_SELECT = 2,
			};
			
			/// <summary> 
			/// (D2D1_DISTANTDIFFUSE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISTANTDIFFUSE_PROP
			{
				/// <summary>
				/// Property Name: "Azimuth"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_AZIMUTH = 0,

				/// <summary>
				/// Property Name: "Elevation"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_ELEVATION = 1,

				/// <summary>
				/// Property Name: "DiffuseConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_DIFFUSE_CONSTANT = 2,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_SURFACE_SCALE = 3,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_COLOR = 4,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_KERNEL_UNIT_LENGTH = 5,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_DISTANTDIFFUSE_SCALE_MODE
				/// </summary>
				D2D1_DISTANTDIFFUSE_PROP_SCALE_MODE = 6,
			};
			
			/// <summary> 
			/// (D2D1_DISTANTDIFFUSE_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISTANTDIFFUSE_SCALE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_ANISOTROPIC = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTDIFFUSE_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};
			
			/// <summary> 
			/// (D2D1_DISTANTSPECULAR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISTANTSPECULAR_PROP
			{
				/// <summary>
				/// Property Name: "Azimuth"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_AZIMUTH = 0,

				/// <summary>
				/// Property Name: "Elevation"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_ELEVATION = 1,

				/// <summary>
				/// Property Name: "SpecularExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_SPECULAR_EXPONENT = 2,

				/// <summary>
				/// Property Name: "SpecularConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_SPECULAR_CONSTANT = 3,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_SURFACE_SCALE = 4,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_COLOR = 5,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_KERNEL_UNIT_LENGTH = 6,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_DISTANTSPECULAR_SCALE_MODE
				/// </summary>
				D2D1_DISTANTSPECULAR_PROP_SCALE_MODE = 7,
			};
			
			/// <summary> 
			/// (D2D1_DISTANTSPECULAR_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DISTANTSPECULAR_SCALE_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_ANISOTROPIC = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DISTANTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};
			
			/// <summary> 
			/// (D2D1_DPICOMPENSATION_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DPICOMPENSATION_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_LINEAR = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_CUBIC = 2,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_ANISOTROPIC = 4,
				/// <summary>
				/// 
				/// </summary>
				D2D1_DPICOMPENSATION_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = 5,
			};
			
			/// <summary> 
			/// (D2D1_DPICOMPENSATION_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DPICOMPENSATION_PROP
			{
				/// <summary>
				/// Property Name: "InterpolationMode"
				/// Property Type: D2D1_DPICOMPENSATION_INTERPOLATION_MODE
				/// </summary>
				D2D1_DPICOMPENSATION_PROP_INTERPOLATION_MODE = 0,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_DPICOMPENSATION_PROP_BORDER_MODE = 1,

				/// <summary>
				/// Property Name: "InputDpi"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_DPICOMPENSATION_PROP_INPUT_DPI = 2,
			};
			
			/// <summary> 
			/// (D2D1_DRAW_TEXT_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_DRAW_TEXT_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001,

				/// <summary>
				/// 
				/// </summary>
				D2D1_DRAW_TEXT_OPTIONS_CLIP = 0x00000002,

				/// <summary>
				/// 
				/// </summary>
				D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT = 0x00000004,

				/// <summary>
				/// 
				/// </summary>
				D2D1_DRAW_TEXT_OPTIONS_DISABLE_COLOR_BITMAP_SNAPPING = 0x00000008,
				D2D1_DRAW_TEXT_OPTIONS_NONE = 0x00000000,
			};
			
			/// <summary> 
			/// (D2D1_EDGEDETECTION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_EDGEDETECTION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_EDGEDETECTION_MODE_SOBEL = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_EDGEDETECTION_MODE_PREWITT = 1,
			};
			
			/// <summary> 
			/// (D2D1_EDGEDETECTION_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_EDGEDETECTION_PROP
			{
				/// <summary>
				/// Property Name: "Strength"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_EDGEDETECTION_PROP_STRENGTH = 0,

				/// <summary>
				/// Property Name: "BlurRadius"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_EDGEDETECTION_PROP_BLUR_RADIUS = 1,

				/// <summary>
				/// Property Name: "Mode"
				/// Property Type: D2D1_EDGEDETECTION_MODE
				/// </summary>
				D2D1_EDGEDETECTION_PROP_MODE = 2,

				/// <summary>
				/// Property Name: "OverlayEdges"
				/// Property Type: BOOL
				/// </summary>
				D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES = 3,

				/// <summary>
				/// Property Name: "AlphaMode"
				/// Property Type: D2D1_ALPHA_MODE
				/// </summary>
				D2D1_EDGEDETECTION_PROP_ALPHA_MODE = 4,
			};
			
			/// <summary> 
			/// (D2D1_EMBOSS_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_EMBOSS_PROP
			{
				/// <summary>
				/// Property Name: "Height"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_EMBOSS_PROP_HEIGHT = 0,

				/// <summary>
				/// Property Name: "Direction"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_EMBOSS_PROP_DIRECTION = 1,
			};
			
			/// <summary> 
			/// (D2D1_EXPOSURE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_EXPOSURE_PROP
			{
				/// <summary>
				/// Property Name: "ExposureValue"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_EXPOSURE_PROP_EXPOSURE_VALUE = 0,
			};
			
			/// <summary> 
			/// (D2D1_EXTEND_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_EXTEND_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_EXTEND_MODE_CLAMP = 0,

				/// <summary>
				/// 
				/// </summary>
				D2D1_EXTEND_MODE_WRAP = 1,

				/// <summary>
				/// 
				/// </summary>
				D2D1_EXTEND_MODE_MIRROR = 2,
			};
			
			/// <summary> 
			/// (D2D1_FACTORY_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FACTORY_TYPE
			{
				/// <summary>
				/// The resulting factory and derived resources may only be invoked serially.
				/// Reference counts on resources are interlocked, however, resource and render
				/// target state is not protected from multi-threaded access.
				/// </summary>
				D2D1_FACTORY_TYPE_SINGLE_THREADED = 0,

				/// <summary>
				/// The resulting factory may be invoked from multiple threads. Returned resources
				/// use interlocked reference counting and their state is protected.
				/// </summary>
				D2D1_FACTORY_TYPE_MULTI_THREADED = 1,
			};
			
			/// <summary> 
			/// (D2D1_FEATURE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FEATURE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_FEATURE_DOUBLES = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FEATURE_D3D10_X_HARDWARE_OPTIONS = 1,
			};
			
			/// <summary> 
			/// (D2D1_FEATURE_LEVEL)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FEATURE_LEVEL
			{
				/// <summary>
				/// The caller does not require a particular underlying D3D device level.
				/// </summary>
				D2D1_FEATURE_LEVEL_DEFAULT = 0,

				/// <summary>
				/// The D3D device level is DX9 compatible.
				/// </summary>
				D2D1_FEATURE_LEVEL_9 = D3D_FEATURE_LEVEL_9_1,

				/// <summary>
				/// The D3D device level is DX10 compatible.
				/// </summary>
				D2D1_FEATURE_LEVEL_10 = D3D_FEATURE_LEVEL_10_0,
			};
			
			/// <summary> 
			/// (D2D1_FIGURE_BEGIN)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FIGURE_BEGIN
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_FIGURE_BEGIN_FILLED = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FIGURE_BEGIN_HOLLOW = 1,
			};
			
			/// <summary> 
			/// (D2D1_FIGURE_END)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FIGURE_END
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_FIGURE_END_OPEN = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FIGURE_END_CLOSED = 1,
			};
			
			/// <summary> 
			/// (D2D1_FILL_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FILL_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILL_MODE_ALTERNATE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILL_MODE_WINDING = 1,
			};
			
			/// <summary> 
			/// (D2D1_FILTER)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FILTER
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_MAG_MIP_POINT = 0x00,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x01,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x04,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x05,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_MIN_MAG_MIP_LINEAR = 0x15,
				/// <summary>
				/// 
				/// </summary>
				D2D1_FILTER_ANISOTROPIC = 0x55,
			};
			
			/// <summary> 
			/// (D2D1_FLOOD_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_FLOOD_PROP
			{
				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_4F
				/// </summary>
				D2D1_FLOOD_PROP_COLOR = 0,
			};
			
			/// <summary> 
			/// (D2D1_GAMMA)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAMMA
			{
				/// <summary>
				/// Colors are manipulated in 2.2 gamma color space.
				/// </summary>
				D2D1_GAMMA_2_2 = 0,

				/// <summary>
				/// Colors are manipulated in 1.0 gamma color space.
				/// </summary>
				D2D1_GAMMA_1_0 = 1,
			};
			
			/// <summary> 
			/// (D2D1_GAMMA1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAMMA1
			{
				/// <summary>
				/// Colors are manipulated in 2.2 gamma color space.
				/// </summary>
				D2D1_GAMMA1_G22 = D2D1_GAMMA_2_2,

				/// <summary>
				/// Colors are manipulated in 1.0 gamma color space.
				/// </summary>
				D2D1_GAMMA1_G10 = D2D1_GAMMA_1_0,

				/// <summary>
				/// Colors are manipulated in ST.2084 PQ gamma color space.
				/// </summary>
				D2D1_GAMMA1_G2084 = 2,
			};
			
			/// <summary> 
			/// (D2D1_GAMMATRANSFER_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAMMATRANSFER_PROP
			{
				/// <summary>
				/// Property Name: "RedAmplitude"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_RED_AMPLITUDE = 0,

				/// <summary>
				/// Property Name: "RedExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_RED_EXPONENT = 1,

				/// <summary>
				/// Property Name: "RedOffset"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_RED_OFFSET = 2,

				/// <summary>
				/// Property Name: "RedDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_RED_DISABLE = 3,

				/// <summary>
				/// Property Name: "GreenAmplitude"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_GREEN_AMPLITUDE = 4,

				/// <summary>
				/// Property Name: "GreenExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_GREEN_EXPONENT = 5,

				/// <summary>
				/// Property Name: "GreenOffset"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_GREEN_OFFSET = 6,

				/// <summary>
				/// Property Name: "GreenDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_GREEN_DISABLE = 7,

				/// <summary>
				/// Property Name: "BlueAmplitude"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_BLUE_AMPLITUDE = 8,

				/// <summary>
				/// Property Name: "BlueExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_BLUE_EXPONENT = 9,

				/// <summary>
				/// Property Name: "BlueOffset"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_BLUE_OFFSET = 10,

				/// <summary>
				/// Property Name: "BlueDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_BLUE_DISABLE = 11,

				/// <summary>
				/// Property Name: "AlphaAmplitude"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_ALPHA_AMPLITUDE = 12,

				/// <summary>
				/// Property Name: "AlphaExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_ALPHA_EXPONENT = 13,

				/// <summary>
				/// Property Name: "AlphaOffset"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_ALPHA_OFFSET = 14,

				/// <summary>
				/// Property Name: "AlphaDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_ALPHA_DISABLE = 15,

				/// <summary>
				/// Property Name: "ClampOutput"
				/// Property Type: BOOL
				/// </summary>
				D2D1_GAMMATRANSFER_PROP_CLAMP_OUTPUT = 16,
			};
			
			/// <summary> 
			/// (D2D1_GAUSSIANBLUR_OPTIMIZATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAUSSIANBLUR_OPTIMIZATION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAUSSIANBLUR_OPTIMIZATION_SPEED = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY = 2,
			};
			
			/// <summary> 
			/// (D2D1_GAUSSIANBLUR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAUSSIANBLUR_PROP
			{
				/// <summary>
				/// Property Name: "StandardDeviation"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION = 0,

				/// <summary>
				/// Property Name: "Optimization"
				/// Property Type: D2D1_GAUSSIANBLUR_OPTIMIZATION
				/// </summary>
				D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION = 1,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_GAUSSIANBLUR_PROP_BORDER_MODE = 2,

			};
			
			/// <summary> 
			/// (D2D1_GAMMA_CONVERSION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GAMMA_CONVERSION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAMMA_CONVERSION_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAMMA_CONVERSION_2_2_TO_1_0 = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_GAMMA_CONVERSION_1_0_TO_2_2 = 2
			};
			
			/// <summary> 
			/// (D2D1_GEOMETRY_RELATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D2D1_GEOMETRY_RELATION
			{
				/// <summary>
				/// The relation between the geometries couldn't be determined. This value is never
				/// returned by any D2D method.
				/// </summary>
				D2D1_GEOMETRY_RELATION_UNKNOWN = 0,

				/// <summary>
				/// The two geometries do not intersect at all.
				/// </summary>
				D2D1_GEOMETRY_RELATION_DISJOINT = 1,

				/// <summary>
				/// The passed in geometry is entirely contained by the object.
				/// </summary>
				D2D1_GEOMETRY_RELATION_IS_CONTAINED = 2,

				/// <summary>
				/// The object entirely contains the passed in geometry.
				/// </summary>
				D2D1_GEOMETRY_RELATION_CONTAINS = 3,

				/// <summary>
				/// The two geometries overlap but neither completely contains the other.
				/// </summary>
				D2D1_GEOMETRY_RELATION_OVERLAP = 4,
			};
			
			/// <summary> 
			/// (D2D1_GEOMETRY_SIMPLIFICATION_OPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES = 1,
			};
			
			/// <summary> 
			/// (D2D1_HDRTONEMAP_DISPLAY_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HDRTONEMAP_DISPLAY_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_HDRTONEMAP_DISPLAY_MODE_SDR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_HDRTONEMAP_DISPLAY_MODE_HDR = 1,
			};
			
			/// <summary> 
			/// (D2D1_HDRTONEMAP_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HDRTONEMAP_PROP
			{
				/// <summary>
				/// Property Name: "InputMaxLuminance"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HDRTONEMAP_PROP_INPUT_MAX_LUMINANCE = 0,

				/// <summary>
				/// Property Name: "OutputMaxLuminance"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HDRTONEMAP_PROP_OUTPUT_MAX_LUMINANCE = 1,

				/// <summary>
				/// Property Name: "DisplayMode"
				/// Property Type: D2D1_HDRTONEMAP_DISPLAY_MODE
				/// </summary>
				D2D1_HDRTONEMAP_PROP_DISPLAY_MODE = 2,
			};
			
			/// <summary> 
			/// (D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA_LINEAR = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA_SRGB = 1,
			};
			
			/// <summary> 
			/// (D2D1_HIGHLIGHTSANDSHADOWS_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HIGHLIGHTSANDSHADOWS_PROP
			{
				/// <summary>
				/// Property Name: "Highlights"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_PROP_HIGHLIGHTS = 0,

				/// <summary>
				/// Property Name: "Shadows"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_PROP_SHADOWS = 1,

				/// <summary>
				/// Property Name: "Clarity"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_PROP_CLARITY = 2,

				/// <summary>
				/// Property Name: "InputGamma"
				/// Property Type: D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_PROP_INPUT_GAMMA = 3,

				/// <summary>
				/// Property Name: "MaskBlurRadius"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HIGHLIGHTSANDSHADOWS_PROP_MASK_BLUR_RADIUS = 4,
			};
			
			/// <summary> 
			/// (D2D1_HISTOGRAM_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HISTOGRAM_PROP
			{
				/// <summary>
				/// Property Name: "NumBins"
				/// Property Type: UINT32
				/// </summary>
				D2D1_HISTOGRAM_PROP_NUM_BINS = 0,

				/// <summary>
				/// Property Name: "ChannelSelect"
				/// Property Type: D2D1_CHANNEL_SELECTOR
				/// </summary>
				D2D1_HISTOGRAM_PROP_CHANNEL_SELECT = 1,

				/// <summary>
				/// Property Name: "HistogramOutput"
				/// Property Type: (blob)
				/// </summary>
				D2D1_HISTOGRAM_PROP_HISTOGRAM_OUTPUT = 2,
			};
			
			/// <summary> 
			/// (D2D1_HUEROTATION_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HUEROTATION_PROP
			{
				/// <summary>
				/// Property Name: "Angle"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_HUEROTATION_PROP_ANGLE = 0,
			};
			
			/// <summary> 
			/// (D2D1_HUETORGB_INPUT_COLOR_SPACE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HUETORGB_INPUT_COLOR_SPACE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_HUETORGB_INPUT_COLOR_SPACE_HUE_SATURATION_VALUE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_HUETORGB_INPUT_COLOR_SPACE_HUE_SATURATION_LIGHTNESS = 1,
			};
			
			/// <summary> 
			/// (D2D1_HUETORGB_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_HUETORGB_PROP
			{
				/// <summary>
				/// /// Property Name: "InputColorSpace"
				/// /// Property Type: D2D1_HUETORGB_INPUT_COLOR_SPACE
				/// /// </summary>
				D2D1_HUETORGB_PROP_INPUT_COLOR_SPACE = 0,
			};
			
			/// <summary> 
			/// (D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS_LOW_QUALITY_PRIMARY_CONVERSION = 1,
			};
			
			/// <summary> 
			/// (D2D1_IMAGE_SOURCE_LOADING_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_IMAGE_SOURCE_LOADING_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_IMAGE_SOURCE_LOADING_OPTIONS_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_IMAGE_SOURCE_LOADING_OPTIONS_RELEASE_SOURCE = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_IMAGE_SOURCE_LOADING_OPTIONS_CACHE_ON_DEMAND = 2,
			};
			
			/// <summary> 
			/// (D2D1_INK_NIB_SHAPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_INK_NIB_SHAPE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_INK_NIB_SHAPE_ROUND = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INK_NIB_SHAPE_SQUARE = 1,
			};
			
			/// <summary> 
			/// (D2D1_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_INTERPOLATION_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR = D2D1_INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_LINEAR,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_CUBIC,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = D2D1_INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_ANISOTROPIC = D2D1_INTERPOLATION_MODE_DEFINITION_ANISOTROPIC,
				/// <summary>
				/// 
				/// </summary>
				D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = D2D1_INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC,
			};
			
			/// <summary> 
			/// (D2D1_LAYER_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_LAYER_OPTIONS
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_LAYER_OPTIONS_NONE = 0x00000000,

				/// <summary>
				/// 
				/// </summary>
				D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 0x00000001,
			};
			
			/// <summary> 
			/// (D2D1_LAYER_OPTIONS1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_LAYER_OPTIONS1
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_LAYER_OPTIONS1_NONE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_LAYER_OPTIONS1_INITIALIZE_FROM_BACKGROUND = 1,
				/// <summary>
				/// 
				/// </summary>
				D2D1_LAYER_OPTIONS1_IGNORE_ALPHA = 2,
			};

			/// <summary> 
			/// (D2D1_LINEARTRANSFER_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_LINEARTRANSFER_PROP
			{
				/// <summary>
				/// Property Name: "RedYIntercept"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_RED_Y_INTERCEPT = 0,

				/// <summary>
				/// Property Name: "RedSlope"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_RED_SLOPE = 1,

				/// <summary>
				/// Property Name: "RedDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_RED_DISABLE = 2,

				/// <summary>
				/// Property Name: "GreenYIntercept"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_GREEN_Y_INTERCEPT = 3,

				/// <summary>
				/// Property Name: "GreenSlope"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_GREEN_SLOPE = 4,

				/// <summary>
				/// Property Name: "GreenDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_GREEN_DISABLE = 5,

				/// <summary>
				/// Property Name: "BlueYIntercept"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_BLUE_Y_INTERCEPT = 6,

				/// <summary>
				/// Property Name: "BlueSlope"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_BLUE_SLOPE = 7,

				/// <summary>
				/// Property Name: "BlueDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_BLUE_DISABLE = 8,

				/// <summary>
				/// Property Name: "AlphaYIntercept"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_ALPHA_Y_INTERCEPT = 9,

				/// <summary>
				/// Property Name: "AlphaSlope"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_ALPHA_SLOPE = 10,

				/// <summary>
				/// Property Name: "AlphaDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_ALPHA_DISABLE = 11,

				/// <summary>
				/// Property Name: "ClampOutput"
				/// Property Type: BOOL
				/// </summary>
				D2D1_LINEARTRANSFER_PROP_CLAMP_OUTPUT = 12,
			};

			/// <summary> 
			/// (D2D1_LINE_JOIN)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_LINE_JOIN
			{
				/// <summary>
				/// Miter join.
				/// </summary>
				D2D1_LINE_JOIN_MITER = 0,

				/// <summary>
				/// Bevel join.
				/// </summary>
				D2D1_LINE_JOIN_BEVEL = 1,

				/// <summary>
				/// Round join.
				/// </summary>
				D2D1_LINE_JOIN_ROUND = 2,

				/// <summary>
				/// Miter/Bevel join.
				/// </summary>
				D2D1_LINE_JOIN_MITER_OR_BEVEL = 3,
			};

			/// <summary> 
			/// (D2D1_LOOKUPTABLE3D_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_LOOKUPTABLE3D_PROP
			{
				/// <summary>
				/// Property Name: "Lut"
				/// Property Type: IUnknown *
				/// </summary>
				D2D1_LOOKUPTABLE3D_PROP_LUT = 0,

				/// <summary>
				/// Property Name: "AlphaMode"
				/// Property Type: D2D1_ALPHA_MODE
				/// </summary>
				D2D1_LOOKUPTABLE3D_PROP_ALPHA_MODE = 1,
			};

			/// <summary> 
			/// (D2D1_MORPHOLOGY_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_MORPHOLOGY_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				D2D1_MORPHOLOGY_MODE_ERODE = 0,
				/// <summary>
				/// 
				/// </summary>
				D2D1_MORPHOLOGY_MODE_DILATE = 1,
			};

			/// <summary> 
			/// (D2D1_MORPHOLOGY_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_MORPHOLOGY_PROP
			{
				/// <summary>
				/// Property Name: "Mode"
				/// Property Type: D2D1_MORPHOLOGY_MODE
				/// </summary>
				D2D1_MORPHOLOGY_PROP_MODE = 0,

				/// <summary>
				/// Property Name: "Width"
				/// Property Type: UINT32
				/// </summary>
				D2D1_MORPHOLOGY_PROP_WIDTH = 1,

				/// <summary>
				/// Property Name: "Height"
				/// Property Type: UINT32
				/// </summary>
				D2D1_MORPHOLOGY_PROP_HEIGHT = 2,
			};

			/// <summary> 
			/// (D2D1_MAP_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			[FlagsAttribute]
			public enum class CA_D2D1_MAP_OPTIONS
			{
				/// <summary>
				/// The mapped pointer has undefined behavior.
				/// </summary>
				D2D1_MAP_OPTIONS_NONE = 0,

				/// <summary>
				/// The mapped pointer can be read from.
				/// </summary>
				D2D1_MAP_OPTIONS_READ = 1,

				/// <summary>
				/// The mapped pointer can be written to.
				/// </summary>
				D2D1_MAP_OPTIONS_WRITE = 2,

				/// <summary>
				/// The previous contents of the bitmap are discarded when it is mapped.
				/// </summary>
				D2D1_MAP_OPTIONS_DISCARD = 4,
			};

			/// <summary> 
			/// (D2D1_OPACITYMETADATA_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_OPACITYMETADATA_PROP
			{
				/// <summary>
				/// Property Name: "InputOpaqueRect"
				/// Property Type: D2D1_VECTOR_4F
				/// </summary>
				D2D1_OPACITYMETADATA_PROP_INPUT_OPAQUE_RECT = 0,
			};

			/// <summary> 
			/// (D2D1_OPACITY_MASK_CONTENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_OPACITY_MASK_CONTENT
			{
				/// <summary> 
				/// The mask contains geometries or bitmaps.	   
				/// </summary>
				D2D1_OPACITY_MASK_CONTENT_GRAPHICS = 0,

				/// <summary>
				/// The mask contains text rendered using one of the natural text modes.
				/// </summary>
				D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL = 1,

				/// <summary>
				/// The mask contains text rendered using one of the GDI compatible text modes.
				/// </summary>
				D2D1_OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2,
			};

			/// <summary> 
			/// (D2D1_ORIENTATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_ORIENTATION
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,

				D2D1_ORIENTATION_DEFAULT = 1,
				D2D1_ORIENTATION_FLIP_HORIZONTAL = 2,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE180 = 3,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE180_FLIP_HORIZONTAL = 4,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE90_FLIP_HORIZONTAL = 5,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE270 = 6,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE270_FLIP_HORIZONTAL = 7,
				D2D1_ORIENTATION_ROTATE_CLOCKWISE90 = 8,
			};

			/// <summary> 
			/// (D2D1_PATCH_EDGE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PATCH_EDGE_MODE
			{
				/// <summary>  
				/// Render this edge aliased.   
				/// </summary>
				D2D1_PATCH_EDGE_MODE_ALIASED = 0,

				/// <summary>
				/// Render this edge antialiased.
				/// </summary>
				D2D1_PATCH_EDGE_MODE_ANTIALIASED = 1,

				/// <summary>
				/// Render this edge aliased and inflated out slightly.
				/// </summary>
				D2D1_PATCH_EDGE_MODE_ALIASED_INFLATED = 2,
			};

			/// <summary> 
			/// (D2D1_PATH_SEGMENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PATH_SEGMENT
			{
				D2D1_PATH_SEGMENT_NONE = 0x00000000,
				D2D1_PATH_SEGMENT_FORCE_UNSTROKED = 0x00000001,
				D2D1_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN = 0x00000002,
			};

			/// <summary> 
			/// (D2D1_PIXEL_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PIXEL_OPTIONS
			{
				/// <summary>
   /// Default pixel processing.
   /// </summary>
				D2D1_PIXEL_OPTIONS_NONE = 0,

				/// <summary>
				/// Indicates that the shader samples its inputs only at exactly the same scene
				/// coordinate as the output pixel, and that it returns transparent black whenever
				/// the input pixels are also transparent black.
				/// </summary>
				D2D1_PIXEL_OPTIONS_TRIVIAL_SAMPLING = 1,
			};

			/// <summary> 
			/// (D2D1_POINTDIFFUSE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_POINTDIFFUSE_PROP
			{
				/// <summary>
	/// Property Name: "LightPosition"
	/// Property Type: D2D1_VECTOR_3F
	/// </summary>
				D2D1_POINTDIFFUSE_PROP_LIGHT_POSITION = 0,

				/// <summary>
				/// Property Name: "DiffuseConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_POINTDIFFUSE_PROP_DIFFUSE_CONSTANT = 1,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_POINTDIFFUSE_PROP_SURFACE_SCALE = 2,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_POINTDIFFUSE_PROP_COLOR = 3,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_POINTDIFFUSE_PROP_KERNEL_UNIT_LENGTH = 4,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_POINTDIFFUSE_SCALE_MODE
				/// </summary>
				D2D1_POINTDIFFUSE_PROP_SCALE_MODE = 5,
			};

			/// <summary> 
			/// (D2D1_POINTDIFFUSE_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_POINTDIFFUSE_SCALE_MODE
			{
				D2D1_POINTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_POINTDIFFUSE_SCALE_MODE_LINEAR = 1,
				D2D1_POINTDIFFUSE_SCALE_MODE_CUBIC = 2,
				D2D1_POINTDIFFUSE_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_POINTDIFFUSE_SCALE_MODE_ANISOTROPIC = 4,
				D2D1_POINTDIFFUSE_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_POINTSPECULAR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_POINTSPECULAR_PROP
			{
				/// <summary>
   /// Property Name: "LightPosition"
   /// Property Type: D2D1_VECTOR_3F
   /// </summary>
				D2D1_POINTSPECULAR_PROP_LIGHT_POSITION = 0,

				/// <summary>
				/// Property Name: "SpecularExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_POINTSPECULAR_PROP_SPECULAR_EXPONENT = 1,

				/// <summary>
				/// Property Name: "SpecularConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_POINTSPECULAR_PROP_SPECULAR_CONSTANT = 2,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_POINTSPECULAR_PROP_SURFACE_SCALE = 3,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_POINTSPECULAR_PROP_COLOR = 4,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_POINTSPECULAR_PROP_KERNEL_UNIT_LENGTH = 5,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_POINTSPECULAR_SCALE_MODE
				/// </summary>
				D2D1_POINTSPECULAR_PROP_SCALE_MODE = 6,
			};

			/// <summary> 
			/// (D2D1_POINTSPECULAR_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_POINTSPECULAR_SCALE_MODE
			{
				D2D1_POINTSPECULAR_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_POINTSPECULAR_SCALE_MODE_LINEAR = 1,
				D2D1_POINTSPECULAR_SCALE_MODE_CUBIC = 2,
				D2D1_POINTSPECULAR_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_POINTSPECULAR_SCALE_MODE_ANISOTROPIC = 4,
				D2D1_POINTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_POSTERIZE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_POSTERIZE_PROP
			{
				/// <summary>
				/// Property Name: "RedValueCount"
				/// Property Type: UINT32
				/// /// </summary>
				D2D1_POSTERIZE_PROP_RED_VALUE_COUNT = 0,

				/// <summary>
				/// Property Name: "GreenValueCount"
				/// Property Type: UINT32
				/// </summary>
				D2D1_POSTERIZE_PROP_GREEN_VALUE_COUNT = 1,

				/// <summary>
				/// Property Name: "BlueValueCount"
				/// Property Type: UINT32
				/// </summary>
				D2D1_POSTERIZE_PROP_BLUE_VALUE_COUNT = 2,
			};

			/// <summary> 
			/// (D2D1_PRESENT_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PRESENT_OPTIONS
			{
				D2D1_PRESENT_OPTIONS_NONE = 0x00000000,

				/// <summary>
				/// Keep the target contents intact through present.
				/// </summary>
				D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS = 0x00000001,

				/// <summary>
				/// Do not wait for display refresh to commit changes to display.
				/// </summary>
				D2D1_PRESENT_OPTIONS_IMMEDIATELY = 0x00000002,
			};

			/// <summary> 
			/// (D2D1_PRIMITIVE_BLEND)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PRIMITIVE_BLEND
			{
				D2D1_PRIMITIVE_BLEND_SOURCE_OVER = 0,
				D2D1_PRIMITIVE_BLEND_COPY = 1,
				D2D1_PRIMITIVE_BLEND_MIN = 2,
				D2D1_PRIMITIVE_BLEND_ADD = 3,
				D2D1_PRIMITIVE_BLEND_MAX = 4,
			};

			/// <summary> 
			/// (D2D1_PRINT_FONT_SUBSET_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PRINT_FONT_SUBSET_MODE
			{
				/// <summary>
				/// Subset for used glyphs, send and discard font resource after every five pages
				/// </summary>
				D2D1_PRINT_FONT_SUBSET_MODE_DEFAULT = 0,

				/// <summary>
				/// Subset for used glyphs, send and discard font resource after each page
				/// </summary>
				D2D1_PRINT_FONT_SUBSET_MODE_EACHPAGE = 1,

				/// <summary>
				/// Do not subset, reuse font for all pages, send it after first page
				/// </summary>
				D2D1_PRINT_FONT_SUBSET_MODE_NONE = 2,
			};

			/// <summary> 
			/// (D2D1_PROPERTY_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PROPERTY_TYPE
			{
				D2D1_PROPERTY_TYPE_UNKNOWN = 0,
				D2D1_PROPERTY_TYPE_STRING = 1,
				D2D1_PROPERTY_TYPE_BOOL = 2,
				D2D1_PROPERTY_TYPE_UINT32 = 3,
				D2D1_PROPERTY_TYPE_INT32 = 4,
				D2D1_PROPERTY_TYPE_FLOAT = 5,
				D2D1_PROPERTY_TYPE_VECTOR2 = 6,
				D2D1_PROPERTY_TYPE_VECTOR3 = 7,
				D2D1_PROPERTY_TYPE_VECTOR4 = 8,
				D2D1_PROPERTY_TYPE_BLOB = 9,
				D2D1_PROPERTY_TYPE_IUNKNOWN = 10,
				D2D1_PROPERTY_TYPE_ENUM = 11,
				D2D1_PROPERTY_TYPE_ARRAY = 12,
				D2D1_PROPERTY_TYPE_CLSID = 13,
				D2D1_PROPERTY_TYPE_MATRIX_3X2 = 14,
				D2D1_PROPERTY_TYPE_MATRIX_4X3 = 15,
				D2D1_PROPERTY_TYPE_MATRIX_4X4 = 16,
				D2D1_PROPERTY_TYPE_MATRIX_5X4 = 17,
				D2D1_PROPERTY_TYPE_COLOR_CONTEXT = 18,
			};

			/// <summary> 
			/// (D2D1_PROPERTY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_PROPERTY : Int64
			{
				D2D1_PROPERTY_CLSID = 0x80000000,
				D2D1_PROPERTY_DISPLAYNAME = 0x80000001,
				D2D1_PROPERTY_AUTHOR = 0x80000002,
				D2D1_PROPERTY_CATEGORY = 0x80000003,
				D2D1_PROPERTY_DESCRIPTION = 0x80000004,
				D2D1_PROPERTY_INPUTS = 0x80000005,
				D2D1_PROPERTY_CACHED = 0x80000006,
				D2D1_PROPERTY_PRECISION = 0x80000007,
				D2D1_PROPERTY_MIN_INPUTS = 0x80000008,
				D2D1_PROPERTY_MAX_INPUTS = 0x80000009,
			};

			/// <summary> 
			/// (D2D1_RENDERING_PRIORITY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RENDERING_PRIORITY
			{
				D2D1_RENDERING_PRIORITY_NORMAL = 0,
				D2D1_RENDERING_PRIORITY_LOW = 1,
			};

			/// <summary> 
			/// (D2D1_RENDER_TARGET_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RENDER_TARGET_TYPE
			{
				/// <summary>
				/// D2D is free to choose the render target type for the caller.
				///  /// </summary>
				D2D1_RENDER_TARGET_TYPE_DEFAULT = 0,

				/// <summary>
				/// The render target will render using the CPU.
				/// </summary>
				D2D1_RENDER_TARGET_TYPE_SOFTWARE = 1,

				/// <summary>
				/// The render target will render using the GPU.
				/// </summary>
				D2D1_RENDER_TARGET_TYPE_HARDWARE = 2,
			};

			/// <summary> 
			/// (D2D1_RENDER_TARGET_USAGE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RENDER_TARGET_USAGE
			{
				D2D1_RENDER_TARGET_USAGE_NONE = 0x00000000,

				/// <summary>
				/// Rendering will occur locally, if a terminal-services session is established, the
				/// bitmap updates will be sent to the terminal services client.
				/// </summary>
				D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING = 0x00000001,

				/// <summary>
				/// The render target will allow a call to GetDC on the ID2D1GdiInteropRenderTarget
				/// interface. Rendering will also occur locally.
				/// </summary>
				D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE = 0x00000002,
			};

			/// <summary> 
			/// (D2D1_RESOURCE_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RESOURCE_TYPE
			{
				D2D1_RESOURCE_TYPE_NONE = 0,
				D2D1_RESOURCE_TYPE_SHADER = 1,
				D2D1_RESOURCE_TYPE_BUFFER = 2
			};
			
			/// <summary> 
			/// (D2D1_RGBTOHUE_OUTPUT_COLOR_SPACE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RGBTOHUE_OUTPUT_COLOR_SPACE
			{
				D2D1_RGBTOHUE_OUTPUT_COLOR_SPACE_HUE_SATURATION_VALUE = 0,
				D2D1_RGBTOHUE_OUTPUT_COLOR_SPACE_HUE_SATURATION_LIGHTNESS = 1,
			};

			/// <summary> 
			/// (D2D1_RGBTOHUE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_RGBTOHUE_PROP
			{
				/// <summary>
	/// Property Name: "OutputColorSpace"
	/// Property Type: D2D1_RGBTOHUE_OUTPUT_COLOR_SPACE
	/// </summary>
				D2D1_RGBTOHUE_PROP_OUTPUT_COLOR_SPACE = 0,
			};

			/// <summary> 
			/// (D2D1_SATURATION_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SATURATION_PROP
			{
				/// <summary>
   /// Property Name: "Saturation"
   /// Property Type: FLOAT
   /// </summary>
				D2D1_SATURATION_PROP_SATURATION = 0,
			};

			/// <summary> 
			/// (D2D1_SCALE_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SCALE_INTERPOLATION_MODE
			{
				D2D1_SCALE_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_SCALE_INTERPOLATION_MODE_LINEAR = 1,
				D2D1_SCALE_INTERPOLATION_MODE_CUBIC = 2,
				D2D1_SCALE_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_SCALE_INTERPOLATION_MODE_ANISOTROPIC = 4,
				D2D1_SCALE_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_SCALE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SCALE_PROP
			{
				/// <summary>
	/// Property Name: "Scale"
	/// Property Type: D2D1_VECTOR_2F
	/// </summary>
				D2D1_SCALE_PROP_SCALE = 0,

				/// <summary>
				/// Property Name: "CenterPoint"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_SCALE_PROP_CENTER_POINT = 1,

				/// <summary>
				/// Property Name: "InterpolationMode"
				/// Property Type: D2D1_SCALE_INTERPOLATION_MODE
				/// </summary>
				D2D1_SCALE_PROP_INTERPOLATION_MODE = 2,

				/// <summary>
				/// Property Name: "BorderMode"
				/// Property Type: D2D1_BORDER_MODE
				/// </summary>
				D2D1_SCALE_PROP_BORDER_MODE = 3,

				/// <summary>
				/// Property Name: "Sharpness"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SCALE_PROP_SHARPNESS = 4,
			};

			/// <summary> 
			/// (D2D1_SEPIA_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SEPIA_PROP
			{
				/// <summary>
	/// Property Name: "Intensity"
	/// Property Type: FLOAT
	/// </summary>
				D2D1_SEPIA_PROP_INTENSITY = 0,

				/// <summary>
				/// Property Name: "AlphaMode"
				/// Property Type: D2D1_ALPHA_MODE
				/// </summary>
				D2D1_SEPIA_PROP_ALPHA_MODE = 1,
			};

			/// <summary> 
			/// (D2D1_SHADOW_OPTIMIZATION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SHADOW_OPTIMIZATION
			{
				D2D1_SHADOW_OPTIMIZATION_SPEED = 0,
				D2D1_SHADOW_OPTIMIZATION_BALANCED = 1,
				D2D1_SHADOW_OPTIMIZATION_QUALITY = 2,
			};

			/// <summary> 
			/// (D2D1_SHADOW_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SHADOW_PROP
			{
				/// <summary>
   /// Property Name: "BlurStandardDeviation"
   /// Property Type: FLOAT
   /// </summary>
				D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION = 0,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_4F
				/// </summary>
				D2D1_SHADOW_PROP_COLOR = 1,

				/// <summary>
				/// Property Name: "Optimization"
				/// Property Type: D2D1_SHADOW_OPTIMIZATION
				/// </summary>
				D2D1_SHADOW_PROP_OPTIMIZATION = 2,
			};

			/// <summary> 
			/// (D2D1_SHARPEN_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SHARPEN_PROP
			{
				/// <summary>
	/// Property Name: "Sharpness"
	/// Property Type: FLOAT
	/// </summary>
				D2D1_SHARPEN_PROP_SHARPNESS = 0,

				/// <summary>
				/// Property Name: "Threshold"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SHARPEN_PROP_THRESHOLD = 1,
			};

			/// <summary> 
			/// (D2D1_SPOTDIFFUSE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SPOTDIFFUSE_PROP
			{
				/// <summary>
	/// Property Name: "LightPosition"
	/// Property Type: D2D1_VECTOR_3F
	/// </summary>
				D2D1_SPOTDIFFUSE_PROP_LIGHT_POSITION = 0,

				/// <summary>
				/// Property Name: "PointsAt"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_POINTS_AT = 1,

				/// <summary>
				/// Property Name: "Focus"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_FOCUS = 2,

				/// <summary>
				/// Property Name: "LimitingConeAngle"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_LIMITING_CONE_ANGLE = 3,

				/// <summary>
				/// Property Name: "DiffuseConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_DIFFUSE_CONSTANT = 4,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_SURFACE_SCALE = 5,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_COLOR = 6,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_KERNEL_UNIT_LENGTH = 7,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_SPOTDIFFUSE_SCALE_MODE
				/// </summary>
				D2D1_SPOTDIFFUSE_PROP_SCALE_MODE = 8,
			};

			/// <summary> 
			/// (D2D1_SPOTDIFFUSE_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SPOTDIFFUSE_SCALE_MODE
			{
				D2D1_SPOTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_SPOTDIFFUSE_SCALE_MODE_LINEAR = 1,
				D2D1_SPOTDIFFUSE_SCALE_MODE_CUBIC = 2,
				D2D1_SPOTDIFFUSE_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_SPOTDIFFUSE_SCALE_MODE_ANISOTROPIC = 4,
				D2D1_SPOTDIFFUSE_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_SPOTSPECULAR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SPOTSPECULAR_PROP
			{
				/// <summary>
   /// Property Name: "LightPosition"
   /// Property Type: D2D1_VECTOR_3F
   /// </summary>
				D2D1_SPOTSPECULAR_PROP_LIGHT_POSITION = 0,

				/// <summary>
				/// Property Name: "PointsAt"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_POINTS_AT = 1,

				/// <summary>
				/// Property Name: "Focus"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_FOCUS = 2,

				/// <summary>
				/// Property Name: "LimitingConeAngle"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_LIMITING_CONE_ANGLE = 3,

				/// <summary>
				/// Property Name: "SpecularExponent"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_SPECULAR_EXPONENT = 4,

				/// <summary>
				/// Property Name: "SpecularConstant"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_SPECULAR_CONSTANT = 5,

				/// <summary>
				/// Property Name: "SurfaceScale"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_SURFACE_SCALE = 6,

				/// <summary>
				/// Property Name: "Color"
				/// Property Type: D2D1_VECTOR_3F
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_COLOR = 7,

				/// <summary>
				/// Property Name: "KernelUnitLength"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_KERNEL_UNIT_LENGTH = 8,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_SPOTSPECULAR_SCALE_MODE
				/// </summary>
				D2D1_SPOTSPECULAR_PROP_SCALE_MODE = 9,
			};

			/// <summary> 
			/// (D2D1_SPOTSPECULAR_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SPOTSPECULAR_SCALE_MODE
			{
				D2D1_SPOTSPECULAR_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_SPOTSPECULAR_SCALE_MODE_LINEAR = 1,
				D2D1_SPOTSPECULAR_SCALE_MODE_CUBIC = 2,
				D2D1_SPOTSPECULAR_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_SPOTSPECULAR_SCALE_MODE_ANISOTROPIC = 4,
				D2D1_SPOTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_SPRITE_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SPRITE_OPTIONS
			{
				/// <summary>
	/// Use default sprite rendering behavior.
	/// </summary>
				D2D1_SPRITE_OPTIONS_NONE = 0,

				/// <summary>
				/// Bitmap interpolation will be clamped to the sprite's source rectangle.
				/// </summary>
				D2D1_SPRITE_OPTIONS_CLAMP_TO_SOURCE_RECTANGLE = 1,
			};

			/// <summary> 
			/// (D2D1_STRAIGHTEN_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_STRAIGHTEN_PROP
			{
				/// <summary>
   /// Property Name: "Angle"
   /// Property Type: FLOAT
   /// </summary>
				D2D1_STRAIGHTEN_PROP_ANGLE = 0,

				/// <summary>
				/// Property Name: "MaintainSize"
				/// Property Type: BOOL
				/// </summary>
				D2D1_STRAIGHTEN_PROP_MAINTAIN_SIZE = 1,

				/// <summary>
				/// Property Name: "ScaleMode"
				/// Property Type: D2D1_STRAIGHTEN_SCALE_MODE
				/// </summary>
				D2D1_STRAIGHTEN_PROP_SCALE_MODE = 2,
			};

			/// <summary> 
			/// (D2D1_STRAIGHTEN_SCALE_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_STRAIGHTEN_SCALE_MODE
			{
				D2D1_STRAIGHTEN_SCALE_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_STRAIGHTEN_SCALE_MODE_LINEAR = 1,
				D2D1_STRAIGHTEN_SCALE_MODE_CUBIC = 2,
				D2D1_STRAIGHTEN_SCALE_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_STRAIGHTEN_SCALE_MODE_ANISOTROPIC = 4,
			};

			/// <summary> 
			/// (D2D1_STROKE_TRANSFORM_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_STROKE_TRANSFORM_TYPE
			{
				/// <summary>
				/// The stroke respects the world transform, the DPI, and the stroke width.
				/// </summary>
				D2D1_STROKE_TRANSFORM_TYPE_NORMAL = 0,

				/// <summary>
				/// The stroke does not respect the world transform, but it does respect the DPI and
				/// the stroke width.
				/// </summary>
				D2D1_STROKE_TRANSFORM_TYPE_FIXED = 1,

				/// <summary>
				/// The stroke is forced to one pixel wide.
				/// </summary>
				D2D1_STROKE_TRANSFORM_TYPE_HAIRLINE = 2,
			};

			/// <summary> 
			/// (D2D1_SUBPROPERTY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SUBPROPERTY : Int64
			{
				D2D1_SUBPROPERTY_DISPLAYNAME = 0x80000000,
				D2D1_SUBPROPERTY_ISREADONLY = 0x80000001,
				D2D1_SUBPROPERTY_MIN = 0x80000002,
				D2D1_SUBPROPERTY_MAX = 0x80000003,
				D2D1_SUBPROPERTY_DEFAULT = 0x80000004,
				D2D1_SUBPROPERTY_FIELDS = 0x80000005,
				D2D1_SUBPROPERTY_INDEX = 0x80000006,
			};

			/// <summary> 
			/// (D2D1_SVG_ASPECT_ALIGN)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_ASPECT_ALIGN
			{
				/// <summary>
	/// The alignment is set to SVG's 'none' value.
	/// </summary>
				D2D1_SVG_ASPECT_ALIGN_NONE = 0,

				/// <summary>
				/// The alignment is set to SVG's 'xMinYMin' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MIN_Y_MIN = 1,

				/// <summary>
				/// The alignment is set to SVG's 'xMidYMin' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MID_Y_MIN = 2,

				/// <summary>
				/// The alignment is set to SVG's 'xMaxYMin' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MAX_Y_MIN = 3,

				/// <summary>
				/// The alignment is set to SVG's 'xMinYMid' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MIN_Y_MID = 4,

				/// <summary>
				/// The alignment is set to SVG's 'xMidYMid' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MID_Y_MID = 5,

				/// <summary>
				/// The alignment is set to SVG's 'xMaxYMid' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MAX_Y_MID = 6,

				/// <summary>
				/// The alignment is set to SVG's 'xMinYMax' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MIN_Y_MAX = 7,

				/// <summary>
				/// The alignment is set to SVG's 'xMidYMax' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MID_Y_MAX = 8,

				/// <summary>
				/// The alignment is set to SVG's 'xMaxYMax' value.
				/// </summary>
				D2D1_SVG_ASPECT_ALIGN_X_MAX_Y_MAX = 9,
			};

			/// <summary> 
			/// (D2D1_SVG_ASPECT_SCALING)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_ASPECT_SCALING
			{
				/// <summary>
	/// Scale the viewBox up as much as possible such that the entire viewBox is visible
	/// within the viewport.
	/// </summary>
				D2D1_SVG_ASPECT_SCALING_MEET = 0,

				/// <summary>
				/// Scale the viewBox down as much as possible such that the entire viewport is
				/// covered by the viewBox.
				/// </summary>
				D2D1_SVG_ASPECT_SCALING_SLICE = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_ATTRIBUTE_POD_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_ATTRIBUTE_POD_TYPE
			{
				/// <summary>
   /// The attribute is a FLOAT.
   /// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_FLOAT = 0,

				/// <summary>
				/// The attribute is a D2D1_COLOR_F.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_COLOR = 1,

				/// <summary>
				/// The attribute is a D2D1_FILL_MODE.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_FILL_MODE = 2,

				/// <summary>
				/// The attribute is a D2D1_SVG_DISPLAY.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_DISPLAY = 3,

				/// <summary>
				/// The attribute is a D2D1_SVG_OVERFLOW.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_OVERFLOW = 4,

				/// <summary>
				/// The attribute is a D2D1_SVG_LINE_CAP.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_CAP = 5,

				/// <summary>
				/// The attribute is a D2D1_SVG_LINE_JOIN.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_LINE_JOIN = 6,

				/// <summary>
				/// The attribute is a D2D1_SVG_VISIBILITY.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_VISIBILITY = 7,

				/// <summary>
				/// The attribute is a D2D1_MATRIX_3X2_F.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_MATRIX = 8,

				/// <summary>
				/// The attribute is a D2D1_SVG_UNIT_TYPE.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_UNIT_TYPE = 9,

				/// <summary>
				/// The attribute is a D2D1_EXTEND_MODE.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_EXTEND_MODE = 10,

				/// <summary>
				/// The attribute is a D2D1_SVG_PRESERVE_ASPECT_RATIO.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_PRESERVE_ASPECT_RATIO = 11,

				/// <summary>
				/// The attribute is a D2D1_SVG_VIEWBOX.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_VIEWBOX = 12,

				/// <summary>
				/// The attribute is a D2D1_SVG_LENGTH.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_POD_TYPE_LENGTH = 13,
			};

			/// <summary> 
			/// (D2D1_SVG_ATTRIBUTE_STRING_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_ATTRIBUTE_STRING_TYPE
			{
				/// <summary>
	/// The attribute is a string in the same form as it would appear in the SVG XML.
	/// 
	/// Note that when getting values of this type, the value returned may not exactly
	/// match the value that was set. Instead, the output value is a normalized version
	/// of the value. For example, an input color of 'red' may be output as '#FF0000'.
	/// </summary>
				D2D1_SVG_ATTRIBUTE_STRING_TYPE_SVG = 0,

				/// <summary>
				/// The attribute is an element ID.
				/// </summary>
				D2D1_SVG_ATTRIBUTE_STRING_TYPE_ID = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_DISPLAY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_DISPLAY
			{
				/// <summary>
	/// The element uses the default display behavior.
	/// </summary>
				D2D1_SVG_DISPLAY_INLINE = 0,

				/// <summary>
				/// The element and all children are not rendered directly.
				/// </summary>
				D2D1_SVG_DISPLAY_NONE = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_LENGTH_UNITS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_LENGTH_UNITS
			{
				/// <summary>
   /// The length is unitless.
   /// </summary>
				D2D1_SVG_LENGTH_UNITS_NUMBER = 0,

				/// <summary>
				/// The length is a percentage value.
				/// </summary>
				D2D1_SVG_LENGTH_UNITS_PERCENTAGE = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_LINE_CAP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_LINE_CAP
			{
				/// <summary>
	/// The property is set to SVG's 'butt' value.
	/// </summary>
				D2D1_SVG_LINE_CAP_BUTT = D2D1_CAP_STYLE_FLAT,

				/// <summary>
				/// The property is set to SVG's 'square' value.
				/// </summary>
				D2D1_SVG_LINE_CAP_SQUARE = D2D1_CAP_STYLE_SQUARE,

				/// <summary>
				/// The property is set to SVG's 'round' value.
				/// </summary>
				D2D1_SVG_LINE_CAP_ROUND = D2D1_CAP_STYLE_ROUND,
			};

			/// <summary> 
			/// (D2D1_SVG_LINE_JOIN)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_LINE_JOIN
			{
				/// <summary>
				/// Utilizado para suporte. Não faz parte da enumeração original.
				/// </summary>
				Zero = 0x0,


				D2D1_SVG_LINE_JOIN_BEVEL = D2D1_LINE_JOIN_BEVEL,


				D2D1_SVG_LINE_JOIN_MITER = D2D1_LINE_JOIN_MITER_OR_BEVEL,


				D2D1_SVG_LINE_JOIN_ROUND = D2D1_LINE_JOIN_ROUND,
			};

			/// <summary> 
			/// (D2D1_SVG_OVERFLOW)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_OVERFLOW
			{
				/// <summary>
   /// The element is not clipped to its viewport.
   /// </summary>
				D2D1_SVG_OVERFLOW_VISIBLE = 0,

				/// <summary>
				/// The element is clipped to its viewport.
				/// </summary>
				D2D1_SVG_OVERFLOW_HIDDEN = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_PAINT_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_PAINT_TYPE
			{
				/// <summary>
				/// The fill or stroke is not rendered.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_NONE = 0,

				/// <summary>
				/// A solid color is rendered.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_COLOR = 1,

				/// <summary>
				/// The current color is rendered.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_CURRENT_COLOR = 2,

				/// <summary>
				/// A paint server, defined by another element in the SVG document, is used.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_URI = 3,

				/// <summary>
				/// A paint server, defined by another element in the SVG document, is used. If the
				/// paint server reference is invalid, fall back to D2D1_SVG_PAINT_TYPE_NONE.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_URI_NONE = 4,

				/// <summary>
				/// A paint server, defined by another element in the SVG document, is used. If the
				/// paint server reference is invalid, fall back to D2D1_SVG_PAINT_TYPE_COLOR.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_URI_COLOR = 5,

				/// <summary>
				/// A paint server, defined by another element in the SVG document, is used. If the
				/// paint server reference is invalid, fall back to
				/// D2D1_SVG_PAINT_TYPE_CURRENT_COLOR.
				/// </summary>
				D2D1_SVG_PAINT_TYPE_URI_CURRENT_COLOR = 6,
			};

			/// <summary> 
			/// (D2D1_SVG_PATH_COMMAND)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_PATH_COMMAND
			{
				/// <summary>
	/// Closes the current subpath. Uses no segment data.
	/// </summary>
				D2D1_SVG_PATH_COMMAND_CLOSE_PATH = 0,

				/// <summary>
				/// Starts a new subpath at the coordinate (x y). Uses 2 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_MOVE_ABSOLUTE = 1,

				/// <summary>
				/// Starts a new subpath at the coordinate (x y). Uses 2 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_MOVE_RELATIVE = 2,

				/// <summary>
				/// Draws a line to the coordinate (x y). Uses 2 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_LINE_ABSOLUTE = 3,

				/// <summary>
				/// Draws a line to the coordinate (x y). Uses 2 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_LINE_RELATIVE = 4,

				/// <summary>
				/// Draws a cubic Bezier curve (x1 y1 x2 y2 x y). The curve ends at (x, y) and is
				/// defined by the two control points (x1, y1) and (x2, y2). Uses 6 floats of
				/// segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_CUBIC_ABSOLUTE = 5,

				/// <summary>
				/// Draws a cubic Bezier curve (x1 y1 x2 y2 x y). The curve ends at (x, y) and is
				/// defined by the two control points (x1, y1) and (x2, y2). Uses 6 floats of
				/// segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_CUBIC_RELATIVE = 6,

				/// <summary>
				/// Draws a quadratic Bezier curve (x1 y1 x y). The curve ends at (x, y) and is
				/// defined by the control point (x1 y1). Uses 4 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_QUADRADIC_ABSOLUTE = 7,

				/// <summary>
				/// Draws a quadratic Bezier curve (x1 y1 x y). The curve ends at (x, y) and is
				/// defined by the control point (x1 y1). Uses 4 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_QUADRADIC_RELATIVE = 8,

				/// <summary>
				/// Draws an elliptical arc (rx ry x-axis-rotation large-arc-flag sweep-flag x y).
				/// The curve ends at (x, y) and is defined by the arc parameters. The two flags are
				/// considered set if their values are non-zero. Uses 7 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_ARC_ABSOLUTE = 9,

				/// <summary>
				/// Draws an elliptical arc (rx ry x-axis-rotation large-arc-flag sweep-flag x y).
				/// The curve ends at (x, y) and is defined by the arc parameters. The two flags are
				/// considered set if their values are non-zero. Uses 7 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_ARC_RELATIVE = 10,

				/// <summary>
				/// Draws a horizontal line to the coordinate (x). Uses 1 float of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_HORIZONTAL_ABSOLUTE = 11,

				/// <summary>
				/// Draws a horizontal line to the coordinate (x). Uses 1 float of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_HORIZONTAL_RELATIVE = 12,

				/// <summary>
				/// Draws a vertical line to the coordinate (y). Uses 1 float of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_VERTICAL_ABSOLUTE = 13,

				/// <summary>
				/// Draws a vertical line to the coordinate (y). Uses 1 float of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_VERTICAL_RELATIVE = 14,

				/// <summary>
				/// Draws a smooth cubic Bezier curve (x2 y2 x y). The curve ends at (x, y) and is
				/// defined by the control point (x2, y2). Uses 4 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_CUBIC_SMOOTH_ABSOLUTE = 15,

				/// <summary>
				/// Draws a smooth cubic Bezier curve (x2 y2 x y). The curve ends at (x, y) and is
				/// defined by the control point (x2, y2). Uses 4 floats of segment data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_CUBIC_SMOOTH_RELATIVE = 16,

				/// <summary>
				/// Draws a smooth quadratic Bezier curve ending at (x, y). Uses 2 floats of segment
				/// data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_QUADRADIC_SMOOTH_ABSOLUTE = 17,

				/// <summary>
				/// Draws a smooth quadratic Bezier curve ending at (x, y). Uses 2 floats of segment
				/// data.
				/// </summary>
				D2D1_SVG_PATH_COMMAND_QUADRADIC_SMOOTH_RELATIVE = 18,
			};

			/// <summary> 
			/// (D2D1_SVG_UNIT_TYPE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_UNIT_TYPE
			{
				/// <summary>
   /// The property is set to SVG's 'userSpaceOnUse' value.
   /// </summary>
				D2D1_SVG_UNIT_TYPE_USER_SPACE_ON_USE = 0,

				/// <summary>
				/// The property is set to SVG's 'objectBoundingBox' value.
				/// </summary>
				D2D1_SVG_UNIT_TYPE_OBJECT_BOUNDING_BOX = 1,
			};

			/// <summary> 
			/// (D2D1_SVG_VISIBILITY)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SVG_VISIBILITY
			{
				/// <summary>
  /// The element is visible.
  /// </summary>
				D2D1_SVG_VISIBILITY_VISIBLE = 0,

				/// <summary>
				/// The element is invisible.
				/// </summary>
				D2D1_SVG_VISIBILITY_HIDDEN = 1,
			};

			/// <summary> 
			/// (D2D1_SWEEP_DIRECTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_SWEEP_DIRECTION
			{
				D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,
				D2D1_SWEEP_DIRECTION_CLOCKWISE = 1,
			};

			/// <summary> 
			/// (D2D1_TABLETRANSFER_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TABLETRANSFER_PROP
			{
				/// <summary>
   /// Property Name: "RedTable"
   /// Property Type: (blob)
   /// </summary>
				D2D1_TABLETRANSFER_PROP_RED_TABLE = 0,

				/// <summary>
				/// Property Name: "RedDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TABLETRANSFER_PROP_RED_DISABLE = 1,

				/// <summary>
				/// Property Name: "GreenTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_TABLETRANSFER_PROP_GREEN_TABLE = 2,

				/// <summary>
				/// Property Name: "GreenDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TABLETRANSFER_PROP_GREEN_DISABLE = 3,

				/// <summary>
				/// Property Name: "BlueTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_TABLETRANSFER_PROP_BLUE_TABLE = 4,

				/// <summary>
				/// Property Name: "BlueDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TABLETRANSFER_PROP_BLUE_DISABLE = 5,

				/// <summary>
				/// Property Name: "AlphaTable"
				/// Property Type: (blob)
				/// </summary>
				D2D1_TABLETRANSFER_PROP_ALPHA_TABLE = 6,

				/// <summary>
				/// Property Name: "AlphaDisable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TABLETRANSFER_PROP_ALPHA_DISABLE = 7,

				/// <summary>
				/// Property Name: "ClampOutput"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TABLETRANSFER_PROP_CLAMP_OUTPUT = 8,
			};

			/// <summary> 
			/// (D2D1_TEMPERATUREANDTINT_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TEMPERATUREANDTINT_PROP
			{
				/// <summary>
	/// Property Name: "Temperature"
	/// Property Type: FLOAT
	/// </summary>
				D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE = 0,

				/// <summary>
				/// Property Name: "Tint"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_TEMPERATUREANDTINT_PROP_TINT = 1,
			};

			/// <summary> 
			/// (D2D1_TEXT_ANTIALIAS_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TEXT_ANTIALIAS_MODE
			{
				/// <summary>
	/// Render text using the current system setting.
	/// </summary>
				D2D1_TEXT_ANTIALIAS_MODE_DEFAULT = 0,

				/// <summary>
				/// Render text using ClearType.
				/// </summary>
				D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE = 1,

				/// <summary>
				/// Render text using gray-scale.
				/// </summary>
				D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE = 2,

				/// <summary>
				/// Render text aliased.
				/// </summary>
				D2D1_TEXT_ANTIALIAS_MODE_ALIASED = 3,
			};

			/// <summary> 
			/// (D2D1_THREADING_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_THREADING_MODE
			{
				/// <summary>
   /// Resources may only be invoked serially.  Reference counts on resources are
   /// interlocked, however, resource and render target state is not protected from
   /// multi-threaded access
   /// </summary>
				D2D1_THREADING_MODE_SINGLE_THREADED = D2D1_FACTORY_TYPE_SINGLE_THREADED,

				/// <summary>
				/// Resources may be invoked from multiple threads. Resources use interlocked
				/// reference counting and their state is protected.
				/// </summary>
				D2D1_THREADING_MODE_MULTI_THREADED = D2D1_FACTORY_TYPE_MULTI_THREADED,
			};

			/// <summary> 
			/// (D2D1_TILE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TILE_PROP
			{
				/// <summary>
   /// Property Name: "Rect"
   /// Property Type: D2D1_VECTOR_4F
   /// </summary>
				D2D1_TILE_PROP_RECT = 0,
			};

			/// <summary> 
			/// (D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS
			{
				D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS_NONE = 0,

				/// <summary>
				/// Prevents the image source from being automatically scaled (by a ratio of the
				/// context DPI divided by 96) while drawn.
				/// </summary>
				D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS_DISABLE_DPI_SCALE = 1,
			};

			/// <summary> 
			/// (D2D1_TURBULENCE_NOISE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TURBULENCE_NOISE
			{
				D2D1_TURBULENCE_NOISE_FRACTAL_SUM = 0,
				D2D1_TURBULENCE_NOISE_TURBULENCE = 1,			
			};

			/// <summary> 
			/// (D2D1_TURBULENCE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_TURBULENCE_PROP
			{
				/// <summary>
	/// Property Name: "Offset"
	/// Property Type: D2D1_VECTOR_2F
	/// </summary>
				D2D1_TURBULENCE_PROP_OFFSET = 0,

				/// <summary>
				/// Property Name: "Size"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_TURBULENCE_PROP_SIZE = 1,

				/// <summary>
				/// Property Name: "BaseFrequency"
				/// Property Type: D2D1_VECTOR_2F
				/// </summary>
				D2D1_TURBULENCE_PROP_BASE_FREQUENCY = 2,

				/// <summary>
				/// Property Name: "NumOctaves"
				/// Property Type: UINT32
				/// </summary>
				D2D1_TURBULENCE_PROP_NUM_OCTAVES = 3,

				/// <summary>
				/// Property Name: "Seed"
				/// Property Type: INT32
				/// </summary>
				D2D1_TURBULENCE_PROP_SEED = 4,

				/// <summary>
				/// Property Name: "Noise"
				/// Property Type: D2D1_TURBULENCE_NOISE
				/// </summary>
				D2D1_TURBULENCE_PROP_NOISE = 5,

				/// <summary>
				/// Property Name: "Stitchable"
				/// Property Type: BOOL
				/// </summary>
				D2D1_TURBULENCE_PROP_STITCHABLE = 6,
			};

			/// <summary> 
			/// (D2D1_UNIT_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_UNIT_MODE
			{
				D2D1_UNIT_MODE_DIPS = 0,
				D2D1_UNIT_MODE_PIXELS = 1,
			};

			/// <summary> 
			/// (D2D1_VERTEX_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_VERTEX_OPTIONS
			{
				/// <summary>
	/// Default vertex processing.
	/// </summary>
				D2D1_VERTEX_OPTIONS_NONE = 0,

				/// <summary>
				/// Indicates that the output rectangle does not need to be cleared before drawing
				/// custom vertices. This must only be used by transforms whose custom vertices
				/// completely cover their output rectangle.
				/// </summary>
				D2D1_VERTEX_OPTIONS_DO_NOT_CLEAR = 1,

				/// <summary>
				/// Causes a depth buffer to be used while drawing custom vertices. This impacts
				/// drawing behavior when primitives overlap one another.
				/// </summary>
				D2D1_VERTEX_OPTIONS_USE_DEPTH_BUFFER = 2,

				/// <summary>
				/// Indicates that custom vertices do not form primitives which overlap one another.
				/// </summary>
				D2D1_VERTEX_OPTIONS_ASSUME_NO_OVERLAP = 4,
			};

			/// <summary> 
			/// (D2D1_VERTEX_USAGE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_VERTEX_USAGE
			{
				/// <summary>
   /// The vertex buffer content do not change frequently from frame to frame.
   /// </summary>
				D2D1_VERTEX_USAGE_STATIC = 0,

				/// <summary>
				/// The vertex buffer is intended to be updated frequently.
				/// </summary>
				D2D1_VERTEX_USAGE_DYNAMIC = 1,
			};

			/// <summary> 
			/// (D2D1_VIGNETTE_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_VIGNETTE_PROP
			{
				/// <summary>
	/// Property Name: "Color"
	/// Property Type: D2D1_VECTOR_4F
	/// </summary>
				D2D1_VIGNETTE_PROP_COLOR = 0,

				/// <summary>
				/// Property Name: "TransitionSize"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_VIGNETTE_PROP_TRANSITION_SIZE = 1,

				/// <summary>
				/// Property Name: "Strength"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_VIGNETTE_PROP_STRENGTH = 2,
			};

			/// <summary> 
			/// (D2D1_WHITELEVELADJUSTMENT_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_WHITELEVELADJUSTMENT_PROP
			{
				/// <summary>
	/// Property Name: "InputWhiteLevel"
	/// Property Type: FLOAT
	/// </summary>
				D2D1_WHITELEVELADJUSTMENT_PROP_INPUT_WHITE_LEVEL = 0,

				/// <summary>
				/// Property Name: "OutputWhiteLevel"
				/// Property Type: FLOAT
				/// </summary>
				D2D1_WHITELEVELADJUSTMENT_PROP_OUTPUT_WHITE_LEVEL = 1,
			};

			/// <summary> 
			/// (D2D1_WINDOW_STATE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_WINDOW_STATE
			{
				D2D1_WINDOW_STATE_NONE = 0x0000000,
				D2D1_WINDOW_STATE_OCCLUDED = 0x0000001,
			};

			/// <summary> 
			/// (D2D1_YCBCR_CHROMA_SUBSAMPLING)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_YCBCR_CHROMA_SUBSAMPLING
			{
				D2D1_YCBCR_CHROMA_SUBSAMPLING_AUTO = 0,
				D2D1_YCBCR_CHROMA_SUBSAMPLING_420 = 1,
				D2D1_YCBCR_CHROMA_SUBSAMPLING_422 = 2,
				D2D1_YCBCR_CHROMA_SUBSAMPLING_444 = 3,
				D2D1_YCBCR_CHROMA_SUBSAMPLING_440 = 4,
			};

			/// <summary> 
			/// (D2D1_YCBCR_INTERPOLATION_MODE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_YCBCR_INTERPOLATION_MODE
			{
				D2D1_YCBCR_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
				D2D1_YCBCR_INTERPOLATION_MODE_LINEAR = 1,
				D2D1_YCBCR_INTERPOLATION_MODE_CUBIC = 2,
				D2D1_YCBCR_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
				D2D1_YCBCR_INTERPOLATION_MODE_ANISOTROPIC = 4,
				D2D1_YCBCR_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = 5,
			};

			/// <summary> 
			/// (D2D1_YCBCR_PROP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public enum class CA_D2D1_YCBCR_PROP
			{
				/// <summary>
				/// Property Name: "ChromaSubsampling"
				/// Property Type: D2D1_YCBCR_CHROMA_SUBSAMPLING
				/// </summary>
				D2D1_YCBCR_PROP_CHROMA_SUBSAMPLING = 0,

				/// <summary>
				/// Property Name: "TransformMatrix"
				/// Property Type: D2D1_MATRIX_3X2_F
				/// </summary>
				D2D1_YCBCR_PROP_TRANSFORM_MATRIX = 1,

				/// <summary>
				/// Property Name: "InterpolationMode"
				/// Property Type: D2D1_YCBCR_INTERPOLATION_MODE
				/// </summary>
				D2D1_YCBCR_PROP_INTERPOLATION_MODE = 2,
			};

			/// <summary> 
			/// (Original) - Enumeração responsável por conter os tipos possiveis para reamapear os genericos para templete em linguagem nativa.
			/// </summary>
			public enum class CA_D2D1_MAPA_TIPOS_TEMPLATE
			{
				/// <summary>
				/// Mapeado para INT16
				/// </summary>
				CA_Int16,
				/// <summary>
				/// Mapeado para UINT16
				/// </summary>
				CA_UInt16,
				/// <summary>
				/// Mapeado para INT32.
				/// </summary>
				CA_Int32,
				/// <summary>
				/// Mapeado para UINT32.
				/// </summary>
				CA_UInt32,
				/// <summary>
				/// Mapeado para INT64.
				/// </summary>
				CA_Int64,
				/// <summary>
				/// Mapeado para UINT64.
				/// </summary>
				CA_UInt64,
				/// <summary>
				/// Mapeado para PWSTR.
				/// </summary>
				CA_String,
				/// <summary>
				/// Mapeado para Char.
				/// </summary>
				CA_Byte,
				/// <summary>
				/// Mapeado para Uchar
				/// </summary>
				CA_SByte,
				/// <summary>
				/// Mapeado para um ponteiro nativo (void*).
				/// </summary>
				CA_ICaren
			};


			//Windows Enumerações

			/// <summary>
			/// (TrustLevel) - Enumera valores que represetam o nível de confiança de uma classe ativavel.
			/// </summary>
			public enum class CA_TrustLevel
			{
				/// <summary>
				/// O componente tem acesso a recursos que não estão protegidos.
				/// </summary>
				BaseTrust = 0,
				/// <summary>
				/// O componente tem acesso aos recursos solicitados no manifesto do aplicativo e aprovados pelo usuário.
				/// </summary>
				PartialTrust = (BaseTrust + 1),
				/// <summary>
				/// O componente requer todos os privilégios do usuário.
				/// </summary>
				FullTrust = (PartialTrust + 1)
			};


			///DirectWrite Enumerações (API PENDENTE)

			public enum class CA_DWRITE_MEASURING_MODE
			{
				/// <summary>
				/// 
				/// </summary>
				DWRITE_MEASURING_MODE_NATURAL,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_MEASURING_MODE_GDI_CLASSIC,

				/// <summary>
				// 
				/// </summary>
				DWRITE_MEASURING_MODE_GDI_NATURAL
			};
			
			public enum class CA_DWRITE_GLYPH_IMAGE_FORMATS
			{
				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_NONE = 0x00000000,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE = 0x00000001,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_CFF = 0x00000002,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_COLR = 0x00000004,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_SVG = 0x00000008,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_PNG = 0x00000010,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_JPEG = 0x00000020,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_TIFF = 0x00000040,

				/// <summary>
				/// 
				/// </summary>
				DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8 = 0x00000080,
			};
		}

		//Estruturas ultizadas pelos usuários em código gerenciado.
		namespace Estruturas
		{
			/// <summary>
			/// (RECT - D3D11_RECT) - A estrutura RECT define as coordenadas dos cantos superior esquerdo e inferior direito de um retângulo.
			/// Essa estrutura é utilizada para definir o retângulo de apresentação para a renderização do vídeo.
			/// </summary>
			public ref struct CA_RECT
			{
				/// <summary>
				/// (Left) - A coordenada X do canto (Superior Esquerdo) do retângulo.
				/// </summary>
				Int32 Left;

				/// <summary>
				/// (Top) - A coordenada Y do canto (Superior Esquerdo) do retângulo.
				/// </summary>
				Int32 Top;

				/// <summary>
				/// (Rigth) - A coordenada X do canto (Inferior Direito) do retângulo.
				/// </summary>
				Int32 Rigth;

				/// <summary>
				/// (Bottom) - A coordenada Y do canto (Inferior Direito) do retângulo.
				/// </summary>
				Int32 Bottom;
			};

			/// <summary>
			/// (POINT)(FALTA DOCUMENTAR) -  
			/// </summary>
			public ref struct CA_POINT
			{
				/// <summary>
				/// 
				/// </summary>
				long X;

				/// <summary>
				/// 
				/// </summary>
				long Y;
			};

			/// <summary>
			/// (_FILETIME)(FALTA DOCUMENTAR) -  
			/// </summary>
			public value struct CA_FILETIME
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32 dwLowDateTime;
				/// <summary>
				/// 
				/// </summary>
				UInt32 dwHighDateTime;
			};

			/// <summary>
			/// (tagSTATSTG)(FALTA DOCUMENTAR) -  
			/// </summary>
			public ref struct CA_STATSTG
			{
				/// <summary>
				/// 
				/// </summary>
				String^                   pwcsName;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_STGTY     type;
				/// <summary>
				/// 
				/// </summary>
				UInt64                    cbSize;
				/// <summary>
				/// 
				/// </summary>
				CA_FILETIME^              mtime;
				/// <summary>
				/// 
				/// </summary>
				CA_FILETIME^              ctime;
				/// <summary>
				/// 
				/// </summary>
				CA_FILETIME^              atime;
				/// <summary>
				/// 
				/// </summary>
				UInt32                    grfMode;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_LOCKTYPE  grfLocksSupported;
				/// <summary>
				/// 
				/// </summary>
				String^                   clsid;
				/// <summary>
				/// 
				/// </summary>
				UInt32                    grfStateBits;
			};

			/// <summary>
			/// (tagBLOB) - Estrutura que contém um Blob(Byte Array) com os dados requisitados.
			/// </summary>
			public value struct CA_BlobData
			{
				/// <summary>
				/// Contém a largura do buffer de dados.
				/// </summary>
				UInt32 SizeData;

				/// <summary>
				/// O buffer com os dados. Esse membro deve ser do tipo (ICarenBuffer).
				/// </summary>
				Object^ BufferDados;
			};

			/// <summary>
			/// (tagCY) - 
			/// </summary>
			public value struct CA_CY
			{
				UInt32      Lo;
				Int32       Hi;
				Int64       int64;
			};
			
			/// <summary>
			/// (tagDEC)
			/// </summary>
			public value struct CA_DEC
			{
				USHORT        signscale;
				BYTE          scale;
				BYTE          sign;
				UInt32        Hi32;
				UInt32        Mid32;
				UInt32        Lo32;
				UInt64        Lo64;
			};		
			
			/// <summary>
			/// (tagVARIANT)(AUTO-IMPLEMENTADA) - Estrutura que 
			/// </summary>
			public ref struct CA_VARIANT
			{
				//Ponteiro nativo gerenciado pela estrutura.
				VARIANT* PonteiroTrabalho = Nulo;

				//Construtor & Destruidor
			public:
				CA_VARIANT() 
				{
					//Construtor Default
				}
				CA_VARIANT(IntPtr Param_Pointer, Boolean Param_Copiar)
				{
					//Verifica se deve fazer uma copia dois dados.
					if (Param_Copiar)
					{
						//Inicializa a variante.
						VariantInit(PonteiroTrabalho);

						//Chama o método para criar uma cópia.
						VariantCopy(PonteiroTrabalho, static_cast<VARIANT*>(Param_Pointer.ToPointer()));
					}
					else
					{
						//Define a variante no ponteiro de trabalho.
						PonteiroTrabalho = static_cast<VARIANT*>(Param_Pointer.ToPointer());
					}
				}
				CA_VARIANT(Enumeracoes::CA_VARTYPE Param_Vartype)
				{
					//Inicializa a variante.
					VariantInit(PonteiroTrabalho);

					//Verifica se não houve erro ao criar.
					if (!ObjetoValido(PonteiroTrabalho))
						throw gcnew Exception("Ocorreu uma falha desconhecida ao tentar criar uma variante.");

					//Define o tipo da variante.
					PonteiroTrabalho->vt = static_cast<VARTYPE>(Param_Vartype);
				}
				CA_VARIANT(const LPVARIANT& Param_Variant, Boolean Param_Copiar)
				{
					//Verifica se deve fazer uma copia dois dados.
					if (Param_Copiar)
					{
						//Inicializa a variante.
						VariantInit(PonteiroTrabalho);

						//Chama o método para criar uma cópia.
						VariantCopy(PonteiroTrabalho, const_cast<VARIANT*>(Param_Variant));
					}
					else
					{
						//Define a variante no ponteiro de trabalho.
						PonteiroTrabalho = const_cast<VARIANT*>(Param_Variant);
					}
				}
				~CA_VARIANT()
				{
					//Verifica se o objeto é valido e libera.
					if(ObjetoValido(PonteiroTrabalho))
						VariantClear(PonteiroTrabalho);

					//Nula
					PonteiroTrabalho = Nulo;
				}

				//Conversão implicita por IntPtr.
			public:
				static operator CA_VARIANT^ (IntPtr Param_Pointer)
				{
					//Variavel a ser retornada.
					CA_VARIANT^ Resultado = nullptr;

					//Ponteiro Nativo.
					VARIANT* vi_pVariant = Nulo;

					//Verifica se o ponteiro é valido
					if (Param_Pointer == IntPtr::Zero)
						Sair; //Ponteiro Invalido.

					//Tenta converter o ponteiro para uma VARIANT.
					vi_pVariant = reinterpret_cast<VARIANT*>(Param_Pointer.ToPointer());

					//Verifica se converteu com sucesso.
					if (!ObjetoValido(vi_pVariant))
						Sair; // Conversão falhou

					//Cria a variante
					Resultado = gcnew CA_VARIANT();

					//Define o ponteiro.
					Resultado->PonteiroTrabalho = vi_pVariant;

				Done:;
					//Retorna a estrutura.
					return Resultado;
				}

				//Métodos
			public:
				/// <summary>
				/// Método responsável por realizar uma cópia de uma variante de origem para a estrutura atual.
				/// O método já inicializa os dados necessários.
				/// </summary>
				/// <param name="Param_VariantOrigem">Um ponteiro que leva a um endereço onde está localizado a variante a ser cópiada.</param>
				/// <returns></returns>
				CarenResult CopyFrom(LPVARIANT* Param_VariantOrigem)
				{
					//Variavel a ser retornada.
					CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

					//Resultado COM.
					HRESULT Hr = E_FAIL;

					//Verifica se a variante atual é valida
					if (!ObjetoValido(PonteiroTrabalho))
					{
						//O ponteiro da variante atual não é valido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Verifica se o ponteiro leva a um destino válido onde está a variante de origem.
					if (!ObjetoValido(Param_VariantOrigem))
					{
						//O ponteiro não leva a um local válido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Inicia a variante que vai receber os dados.
					PonteiroTrabalho = new VARIANT(); //Essa inicialização é igual ao método (IniciarVariant) em GlobaFuncs

					//Preenche os bytes com 0 da propvariant.
					memset(PonteiroTrabalho, 0, sizeof(tagVARIANT));

					//Cria uma cópia da variante atual.
					Hr = VariantCopy(PonteiroTrabalho, const_cast<VARIANT*>(*Param_VariantOrigem));

					//Processa o código.
					Resultado.ProcessarCodigoOperacao(Hr);

				Done:;

					//Retorna o resultado
					return Resultado;
				}

				/// <summary>
				/// Método responsável por realizar uma copia da variante atual para uma de destino especificada.
				/// O método já é responsável por iniciar a VARIANT de destino corretamente.
				/// </summary>
				/// <param name="Param_VariantDestino">Um ponteiro que leva ao endereço de destino onde vai receber uma cópia da variante atual.</param>
				/// <returns></returns>
				CarenResult CopyTo(LPVARIANT* Param_VariantDestino)
				{
					//Variavel a ser retornada.
					CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

					//Resultado COM.
					HRESULT Hr = E_FAIL;

					//Verifica se a variante atual é valida
					if (!ObjetoValido(PonteiroTrabalho))
					{
						//O ponteiro da variante atual não é valido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Verifica se o ponteiro leva a um destino válido para armazenar a variante.
					if (!ObjetoValido(Param_VariantDestino))
					{
						//O ponteiro não leva a um local válido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}
			
					//Inicia a variante.
					*Param_VariantDestino = new VARIANT();
					
					//Preenche os bytes com 0 da propvariant.
					memset(*Param_VariantDestino, 0, sizeof(tagVARIANT));

					//Cria uma cópia da variante atual.
					 Hr = VariantCopy(*Param_VariantDestino, const_cast<VARIANT*>(PonteiroTrabalho));

					 //Processa o código.
					 Resultado.ProcessarCodigoOperacao(Hr);

				Done:;

					//Retorna o resultado
					return Resultado;
				}

				//Propriedades
			public:

				//TIPO DA VARIANT.

				/// <summary>
				/// Propriedade que indica o tipo de dados nesta VARIANTE.
				/// </summary>
				property Enumeracoes::CA_VARTYPE vt
				{
					Enumeracoes::CA_VARTYPE get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna o vartype
						return static_cast<Enumeracoes::CA_VARTYPE>(PonteiroTrabalho->vt);
					}
					void set(Enumeracoes::CA_VARTYPE Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define o novo valor.
						PonteiroTrabalho->vt = static_cast<VARTYPE>(Param_Value);
					}
				}



				//TIPOS SIMPLES

				/// <summary>
				/// (VT_I8) - Propriedade que armazena um valor simples de 8 bytes assinado.
				/// </summary>
				property Int64 llVal
				{
					Int64 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->llVal;
					}
					void set(Int64 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->llVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_I4) - Propriedade que armazena um valor simples de 4 bytes assinado.
				/// </summary>
				property Int32 lVal
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->lVal;
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->lVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_UI1) - Propriedade que armazena um valor simples de 1 byte não assinado.
				/// </summary>
				property Byte bVal
				{
					Byte get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						return PonteiroTrabalho->bVal;
					}
					void set(Byte Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->bVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_I2) - Propriedade que armazena um valor simples de 2 bytes assinado.
				/// </summary>
				property Int16 iVal
				{
					Int16 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->iVal;
					}
					void set(Int16 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->iVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_R4) - Propriedade que armazena um valor simples de 4 bytes reais.
				/// </summary>
				property float fltVal
				{
					float get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->fltVal;
					}
					void set(float Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->fltVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_R8) - Propriedade que armazena um valor simples de 8 bytes reais.
				/// </summary>
				property double dblVal
				{
					double get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->dblVal;
					}
					void set(double Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");
						
						//Define os dados.
						PonteiroTrabalho->dblVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BOOL) - Propriedade que armazena um valor simples do tipo Booleano.
				/// </summary>
				property Boolean boolVal
				{
					Boolean get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->boolVal == -1? true: false;
					}
					void set(Boolean Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");
						
						//Define os dados.
						PonteiroTrabalho->boolVal = Param_Value == true ? -1 : 0;
					}
				}
				/// <summary>
				/// (VT_ERROR) - Propriedade que armazena um valor simples de 4 bytes assinado.
				/// </summary>
				property Int32 scode
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->scode;
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->scode = static_cast<LONG>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_CY) - Propriedade que armazena uma estrutura CA_CY.
				/// </summary>
				property CA_CY cyVal
				{
					CA_CY get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Variavel a ser retornada.
						CA_CY vi_Dados = CA_CY();

						//Define os dados.
						vi_Dados.Hi = PonteiroTrabalho->cyVal.Hi;
						vi_Dados.Lo = PonteiroTrabalho->cyVal.Lo;
						vi_Dados.int64 = PonteiroTrabalho->cyVal.int64;

						//Retorna os dados.
						return vi_Dados;
					}
					void set(CA_CY Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->cyVal.Hi = Param_Value.Hi;
						PonteiroTrabalho->cyVal.Lo = Param_Value.Lo;
						PonteiroTrabalho->cyVal.int64 = Param_Value.int64;
					}
				}
				/// <summary>
				/// (VT_DATE) - Propriedade que armazena um valor simples de de 8 bytes reais.
				/// </summary>
				property double date
				{
					double get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->date;
					}
					void set(double Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->date = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BSTR) - Propriedade que armazena um valor simples do tipo String.
				/// </summary>
				property String^ bstrVal
				{
					String^ get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Variavel a ser retornada.
						String^ vi_DadosBstr = nullptr;

						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho->bstrVal))
							Sair; //A BSTR é invalida.

					Done:;
						//Retorna os dados.
						return vi_DadosBstr;
					}
					void set(String^ Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Libera o antigo valor se válido
						if (ObjetoValido(PonteiroTrabalho->bstrVal))
							DeletarStringBSTRSafe(&PonteiroTrabalho->bstrVal);

						//Define os novos dados.
						PonteiroTrabalho->bstrVal = reinterpret_cast<BSTR>(Marshal::StringToBSTR(Param_Value).ToPointer());
					}
				}
				/// <summary>
				/// (VT_UNKNOWN) - Propriedade que armazena um ponteiro para uma interface IUnknown.
				/// </summary>
				property IntPtr punkVal
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->punkVal))
							throw gcnew NullReferenceException("O membro (punkVal) não é um objeto válido.");

						//Retorna os dados.
						return IntPtr(PonteiroTrabalho->punkVal);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->punkVal = reinterpret_cast<IUnknown*>(Param_Value.ToPointer());
					}
				}
				/// <summary>
				/// (VT_DISPATCH) - Propriedade que armazena um ponteiro para uma interface IDispatch.
				/// </summary>
				property IntPtr pdispVal
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pdispVal))
							throw gcnew NullReferenceException("O membro (pdispVal) não é um objeto válido.");

						//Retorna os dados.
						return IntPtr(PonteiroTrabalho->pdispVal);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->pdispVal = reinterpret_cast<IDispatch*>(Param_Value.ToPointer());
					}
				}
				/// <summary>
				/// (VT_ARRAY) - Propriedade que armazena um ponteiro para uma estrutura SAFEARRAY que pode ser gerenciada pela CA_SAFEARRAY.
				/// </summary>
				property IntPtr parray
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->parray))
							throw gcnew NullReferenceException("O membro (parray) não é um objeto válido.");

						//Retorna os dados.
						return IntPtr(static_cast<void*>(PonteiroTrabalho->parray));
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->parray = reinterpret_cast<SAFEARRAY*>(Param_Value.ToPointer());
					}
				}



				//TIPOS DE REFERÊNCIA ASSINADOS = VT_BYREF|TIPO DADO

				/// <summary>
				/// (VT_BYREF | VT_UI1) - Propriedade que armzena uma referência para um valor de 1 Byte não assinado.
				/// </summary>
				property Byte pbVal
				{
					Byte get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pbVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pbVal;
					}
					void set(Byte Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pbVal))
							PonteiroTrabalho->pbVal = new BYTE();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pbVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_I2) - Propriedade que armzena uma referência para um valor de 2 Bytes assinado. 
				/// </summary>
				property Int16 piVal
				{
					Int16 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->piVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->piVal;
					}
					void set(Int16 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->piVal))
							PonteiroTrabalho->piVal = new SHORT();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->piVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_I4) - Propriedade que armzena uma referência para um valor de 4 Bytes assinado.
				/// </summary>
				property Int32 plVal
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->plVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->plVal;
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->plVal))
							PonteiroTrabalho->plVal = new LONG();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->plVal = static_cast<LONG>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_I8) - Propriedade que armzena uma referência para um valor de 8 Bytes assinado.
				/// </summary>
				property Int64 pllVal
				{
					Int64 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pllVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pllVal;
					}
					void set(Int64 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pllVal))
							PonteiroTrabalho->pllVal = new LONGLONG();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pllVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_R4) - Propriedade que armzena uma referência para um valor de 4 Bytes reais.
				/// </summary>
				property float pfltVal
				{
					float get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pfltVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pfltVal;
					}
					void set(float Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pfltVal))
							PonteiroTrabalho->pfltVal = new FLOAT();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pfltVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_R8) - Propriedade que armzena uma referência para um valor de 8 Bytes reais.
				/// </summary>
				property double pdblVal
				{
					double get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pdblVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pdblVal;
					}
					void set(double Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pdblVal))
							PonteiroTrabalho->pdblVal = new DOUBLE();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pdblVal = Param_Value;
					}
					
				}
				/// <summary>
				/// (VT_BYREF | VT_BOOL) - Propriedade que armzena uma referência para um valor Booleano.
				/// </summary>
				property Boolean pboolVal
				{
					Boolean get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pboolVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return (*PonteiroTrabalho->pboolVal) == -1 ? true : false;
					}
					void set(Boolean Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pboolVal))
							PonteiroTrabalho->pboolVal = new VARIANT_BOOL();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pboolVal = Param_Value == true ? -1 : 0;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_ERROR) - Propriedade que armzena uma referência para um valor de 4 Bytes assinado.
				/// </summary>
				property Int32 pscode
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pscode))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pscode;
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pscode))
							PonteiroTrabalho->pscode = new SCODE();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pscode = static_cast<SCODE>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_CY) - Propriedade que armzena uma referência para uma estrutura CA_CY.
				/// </summary>
				property CA_CY pcyVal
				{
					CA_CY get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pcyVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Variavel a ser retornada.
						CA_CY vi_CY = CA_CY();

						//Define os dados.
						vi_CY.Hi = PonteiroTrabalho->pcyVal->Hi;
						vi_CY.Lo = PonteiroTrabalho->pcyVal->Lo;
						vi_CY.int64 = PonteiroTrabalho->pcyVal->int64;

						//Retorna os dados.
						return vi_CY;
					}
					void set(CA_CY Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pcyVal))
							PonteiroTrabalho->pcyVal = new CY();

						//Define os dados.
						PonteiroTrabalho->pcyVal->Hi = Param_Value.Hi;
						PonteiroTrabalho->pcyVal->Lo = Param_Value.Lo;
						PonteiroTrabalho->pcyVal->int64 = Param_Value.int64;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_DATE) - Propriedade que armzena uma referência para um valor de 8 bytes reais.
				/// </summary>
				property double pdate
				{
					double get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pdate))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pdate;
					}
					void set(double Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pdate))
							PonteiroTrabalho->pdate = new DOUBLE();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pdate = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_BSTR) - Propriedade que armzena uma referência para uma String.
				/// </summary>
				property String^ pbstrVal
				{
					String^ get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pbstrVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return gcnew String((*PonteiroTrabalho->pbstrVal));
					}
					void set(String^ Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pbstrVal))
							PonteiroTrabalho->pbstrVal = new BSTR();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pbstrVal = static_cast<BSTR>(Marshal::StringToBSTR(Param_Value).ToPointer());
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_UNKNOWN) - Propriedade que armzena uma referência para um ponteiro da interface IUnknown.
				/// </summary>
				property IntPtr ppunkVal
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->ppunkVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return IntPtr(*PonteiroTrabalho->ppunkVal);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Variavel que vai conter o ponteiro.
						IUnknown* vi_pPointerOfPointer = static_cast<IUnknown*>(Param_Value.ToPointer());

						//Define o dado no ponteiro.
						PonteiroTrabalho->ppunkVal = static_cast<IUnknown**>(&vi_pPointerOfPointer);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_DISPATCH) - Propriedade que armzena uma referência para um ponteiro da interface IDispatch.
				/// </summary>
				property IntPtr ppdispVal
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->ppdispVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return IntPtr(*PonteiroTrabalho->ppdispVal);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Variavel que vai conter o ponteiro.
						IDispatch* vi_pPointerOfPointer = static_cast<IDispatch*>(Param_Value.ToPointer());

						//Define o dado no ponteiro.
						PonteiroTrabalho->ppdispVal = static_cast<IDispatch**>(&vi_pPointerOfPointer);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_ARRAY) - Propriedade que armzena uma referência para um ponteiro que representa uma estrutura SAFEARRAY.
				/// </summary>
				property IntPtr pparray
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pparray))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return IntPtr(*PonteiroTrabalho->pparray);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Variavel que vai conter o ponteiro.
						SAFEARRAY* vi_pPointerOfPointer = static_cast<SAFEARRAY*>(Param_Value.ToPointer());

						//Define o dado no ponteiro.
						PonteiroTrabalho->pparray = static_cast<SAFEARRAY**>(&vi_pPointerOfPointer);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_VARIANT) - Propriedade que armzena uma referência para uma estrutura CA_VARIANT.
				/// </summary>
				property IntPtr pvarVal
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pvarVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return IntPtr(PonteiroTrabalho->pvarVal);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Define o dado no ponteiro.
						PonteiroTrabalho->pvarVal = static_cast<VARIANT*>(Param_Value.ToPointer());
					}
				}
				/// <summary>
				/// (VT_BYREF | Generic ByRef) - Propriedade que armzena uma referência para um valor generico (VOID).
				/// </summary>
				property IntPtr byref
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->byref))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return IntPtr(PonteiroTrabalho->byref);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Define o dado no ponteiro.
						PonteiroTrabalho->byref = Param_Value.ToPointer();
					}
				}



				//TIPOS SIMPLES NÃO ASSINADOS

				/// <summary>
				/// (VT_I1) - Propriedade que armazena um valor simples de 1 byte assinado.
				/// </summary>
				property char cVal
				{
					char get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->cVal;
					}
					void set(char Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->cVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_UI2) - Propriedade que armazena um valor simples de 2 bytes não assinado.
				/// </summary>
				property UInt16 uiVal
				{
					UInt16 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->uiVal;
					}
					void set(UInt16 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->uiVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_UI4) - Propriedade que armazena um valor simples de 4 bytes não assinado.
				/// </summary>
				property UInt32 ulVal
				{
					UInt32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return static_cast<UInt32>(PonteiroTrabalho->ulVal);
					}
					void set(UInt32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->ulVal = static_cast<ULONG>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_UI8) - Propriedade que armazena um valor simples de 8 bytes não assinado.
				/// </summary>
				property UInt64 ullVal
				{
					UInt64 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return PonteiroTrabalho->ullVal;
					}
					void set(UInt64 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->ullVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_INT) - Propriedade que armazena um valor simples de 4 bytes assinado.
				/// </summary>
				property Int32 intVal
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return static_cast<Int32>(PonteiroTrabalho->intVal);
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->intVal = static_cast<INT>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_UINT) - Propriedade que armazena um valor simples de 4 bytes não assinado.
				/// </summary>
				property UInt32 uintVal
				{
					UInt32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Retorna os dados.
						return static_cast<UInt32>(PonteiroTrabalho->uintVal);
					}
					void set(UInt32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro válido.");

						//Define os dados.
						PonteiroTrabalho->uintVal = static_cast<UINT>(Param_Value);
					}
				}



				//TIPOS DE REFERÊNCIA NÃO ASSINADOS = VT_BYREF|TIPO DADO

				/// <summary>
				/// (VT_BYREF | VT_DECIMAL) - Propriedade que armzena uma referência para uma estrutura CA_DEC.
				/// </summary>
				property CA_DEC pdecVal
				{
					CA_DEC get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pdecVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Variavel a ser retornada.
						CA_DEC vi_DEC = CA_DEC();

						//Define os dados.
						vi_DEC.Hi32 = PonteiroTrabalho->pdecVal->Hi32;
						vi_DEC.Mid32 = PonteiroTrabalho->pdecVal->Mid32;
						vi_DEC.Lo32 = PonteiroTrabalho->pdecVal->Lo32;
						vi_DEC.Lo64 = PonteiroTrabalho->pdecVal->Lo64;
						vi_DEC.scale = PonteiroTrabalho->pdecVal->scale;
						vi_DEC.sign = PonteiroTrabalho->pdecVal->sign;
						vi_DEC.signscale = PonteiroTrabalho->pdecVal->signscale;

						//Retorna os dados.
						return vi_DEC;
					}
					void set(CA_DEC Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pcyVal))
							PonteiroTrabalho->pdecVal = new DECIMAL();

						//Define os dados.
						PonteiroTrabalho->pdecVal->Hi32 = Param_Value.Hi32;
						PonteiroTrabalho->pdecVal->Mid32 = Param_Value.Mid32;
						PonteiroTrabalho->pdecVal->Lo32 = Param_Value.Lo32;
						PonteiroTrabalho->pdecVal->Lo64 = Param_Value.Lo64;
						PonteiroTrabalho->pdecVal->scale = Param_Value.scale;
						PonteiroTrabalho->pdecVal->sign = Param_Value.sign;
						PonteiroTrabalho->pdecVal->signscale = Param_Value.signscale;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_I1) - Propriedade que armzena uma referência para um valor de 1 byte.
				/// </summary>
				property char pcVal
				{
					char get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pcVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->pcVal;
					}
					void set(char Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pcVal))
							PonteiroTrabalho->pcVal = new CHAR();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pcVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_UI2) - Propriedade que armzena uma referência para um valor de 2 bytes não assinado.
				/// </summary>
				property UInt16 puiVal
				{
					UInt16 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->puiVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return *PonteiroTrabalho->puiVal;
					}
					void set(UInt16 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->puiVal))
							PonteiroTrabalho->puiVal = new USHORT();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->puiVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_UI4) - Propriedade que armzena uma referência para um valor de 4 bytes não assinado.
				/// </summary>
				property UInt32 pulVal
				{
					UInt32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pulVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return static_cast<UInt32>(*PonteiroTrabalho->pulVal);
					}
					void set(UInt32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pulVal))
							PonteiroTrabalho->pulVal = new ULONG();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pulVal = static_cast<ULONG>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_UI8) - Propriedade que armzena uma referência para um valor de 8 bytes não assinado.
				/// </summary>
				property UInt64 pullVal
				{
					UInt64 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pullVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return static_cast<UInt32>(*PonteiroTrabalho->pullVal);
					}
					void set(UInt64 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pullVal))
							PonteiroTrabalho->pullVal = new ULONGLONG();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pullVal = Param_Value;
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_INT) - Propriedade que armzena uma referência para um valor de 4 bytes assinado.
				/// </summary>
				property Int32 pintVal
				{
					Int32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pintVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return static_cast<Int32>(*PonteiroTrabalho->pintVal);
					}
					void set(Int32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->pintVal))
							PonteiroTrabalho->pintVal = new INT();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->pintVal = static_cast<INT>(Param_Value);
					}
				}
				/// <summary>
				/// (VT_BYREF | VT_UINT) - Propriedade que armzena uma referência para um valor de 4 bytes não assinado.
				/// </summary>
				property UInt32 puintVal
				{
					UInt32 get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->puintVal))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna os dados.
						return static_cast<Int32>(*PonteiroTrabalho->puintVal);
					}
					void set(UInt32 Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é invalido e cria.
						if (!ObjetoValido(PonteiroTrabalho->puintVal))
							PonteiroTrabalho->puintVal = new UINT();

						//Define o dado no ponteiro.
						*PonteiroTrabalho->puintVal = static_cast<UINT>(Param_Value);
					}
				}
				/// <summary>
				/// Propriedade que armazena um ponteiro para um reegistro de banco de dados.
				/// </summary>
				property IntPtr pvRecord
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pvRecord))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna o dado.
						return IntPtr(PonteiroTrabalho->pvRecord);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Define o dado.
						PonteiroTrabalho->pvRecord = Param_Value.ToPointer();
					}
				}
				/// <summary>
				/// Propriedade que armazena um ponteiro para uma interface IRecordInfo.
				/// </summary>
				property IntPtr pRecInfo
				{
					IntPtr get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Verifica se o ponteiro é valido
						if (!ObjetoValido(PonteiroTrabalho->pRecInfo))
							throw gcnew NullReferenceException("O ponteiro para o dado não era valido.");

						//Retorna o dado.
						return IntPtr(PonteiroTrabalho->pRecInfo);
					}
					void set(IntPtr Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Define o dado.
						PonteiroTrabalho->pRecInfo = reinterpret_cast<IRecordInfo*>(Param_Value.ToPointer());
					}
				}


				//TIPO SIMPLES

				/// <summary>
				/// (VT_DECIMAL) - Propriedade que armazena uma estrutura CA_DEC.
				/// </summary>
				property CA_DEC decVal
				{
					CA_DEC get()
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Variavel a ser retornada.
						CA_DEC vi_DEC = CA_DEC();

						//Define os dados.
						vi_DEC.Hi32 = PonteiroTrabalho->decVal.Hi32;
						vi_DEC.Mid32 = PonteiroTrabalho->decVal.Mid32;
						vi_DEC.Lo32 = PonteiroTrabalho->decVal.Lo32;
						vi_DEC.Lo64 = PonteiroTrabalho->decVal.Lo64;
						vi_DEC.scale = PonteiroTrabalho->decVal.scale;
						vi_DEC.sign = PonteiroTrabalho->decVal.sign;
						vi_DEC.signscale = PonteiroTrabalho->decVal.signscale;

						//Retorna os dados.
						return vi_DEC;
					}
					void set(CA_DEC Param_Value)
					{
						//Verifica se o ponteiro não é invalido
						if (!ObjetoValido(PonteiroTrabalho))
							throw gcnew NullReferenceException("A variante atual não tem um ponteiro valido.");

						//Define os dados.
						PonteiroTrabalho->decVal.Hi32 = Param_Value.Hi32;
						PonteiroTrabalho->decVal.Mid32 = Param_Value.Mid32;
						PonteiroTrabalho->decVal.Lo32 = Param_Value.Lo32;
						PonteiroTrabalho->decVal.Lo64 = Param_Value.Lo64;
						PonteiroTrabalho->decVal.scale = Param_Value.scale;
						PonteiroTrabalho->decVal.sign = Param_Value.sign;
						PonteiroTrabalho->decVal.signscale = Param_Value.signscale;
					}
				}
			};

			/// <summary>
			/// (tagSAFEARRAYBOUND) - Estrutura responsável por descrever os limites de uma matriz segura(CA_SAFEARRAY).
			/// Utiliza-se essa estrutura para informar os limites de cada dimensão em um array.
			/// </summary>
			public value struct CA_SAFEARRAYBOUND
			{
				/// <summary>
				/// Esse membro representa a quantidade de elementos na matriz.
				/// </summary>
				UInt32              cElements;

				/// <summary>
				/// Esse membro armazena o limite inferior da matriz segura, ou seja, o índice do primeiro elemento da matriz.
				/// </summary>
				Int32               lLbound;
			};
			
			/// <summary>
			/// (tagSAFEARRAY)(AUTO-IMPLEMENTADA) - 
			/// </summary>
			public ref struct CA_SAFEARRAY
			{
				//Ponteiro nativo para os dados.
				SAFEARRAY* PonteiroTrabalho = Nulo;

				//Construtor & Destruidor
			public:
				CA_SAFEARRAY() {}
				CA_SAFEARRAY(IntPtr Param_Pointer) 
				{
					//Converte o ponteiro gerenciado para a estrutura SAFEARRAY.
					PonteiroTrabalho = static_cast<SAFEARRAY*>(Param_Pointer.ToPointer());
				}
				CA_SAFEARRAY(const SAFEARRAY* Param_SafeArray)
				{
					//Define o safe array no ponteiro de trabalho.
					PonteiroTrabalho = const_cast<SAFEARRAY*>(Param_SafeArray);
				}
				CA_SAFEARRAY(const LPSAFEARRAY &Param_SafeArray, Boolean Param_Copiar)
				{
					//Variaveis
					SAFEARRAY* vi_pSafeArrayOut = Nulo;
					HRESULT Hr = E_FAIL;

					//Verifica se deve copiar o safearray.
					if (Param_Copiar)
					{
						//Cria uma copia do safe array.
						Hr = SafeArrayCopy(const_cast<SAFEARRAY*>(Param_SafeArray), &vi_pSafeArrayOut);

						//Verifica se ocorreu algum erro.
						if (!Sucesso(Hr))
							throw gcnew Exception("Ocorreu uma falha ao tentar criar uma copia do SAFEARRAY.");

						//Define no ponteiro de trabalho.
						PonteiroTrabalho = vi_pSafeArrayOut;
					}
					else
					{
						//Define o safe array no ponteiro de trabalho.
						PonteiroTrabalho = const_cast<SAFEARRAY*>(Param_SafeArray);
					}
				}
				CA_SAFEARRAY(Enumeracoes::CA_VARTYPE Param_vt, UInt32 Param_CountDim, cli::array<CA_SAFEARRAYBOUND>^ Param_Limites)
				{
					//Variaveis a serem utilizadas.
					SAFEARRAYBOUND *vi_pSafeBound = CriarMatrizEstruturas<SAFEARRAYBOUND>(Param_CountDim);

					//Faz um for para preencher a matriz de estruturas descritivas.
					for (UINT32 i = 0; i < Param_CountDim; i++)
					{
						//Inicializa
						vi_pSafeBound[i] = { };

						//Define os dados na estrutura.
						vi_pSafeBound[i].cElements = Param_Limites[i].cElements;
						vi_pSafeBound[i].lLbound = Param_Limites[i].lLbound;
					}

					//Cria o safe array.
					PonteiroTrabalho = SafeArrayCreate(static_cast<VARTYPE>(Param_vt), Param_CountDim, vi_pSafeBound);

					//Libera a memória utilizada para criar o SafeArrayBound.
					DeletarMatrizEstruturasSafe(&vi_pSafeBound);
				}
				~CA_SAFEARRAY()
				{
					//Destroi os dados do safe array se valido.
					if (ObjetoValido(PonteiroTrabalho))
					{
						///Destroi o safearray
						SafeArrayDestroy(PonteiroTrabalho);

						//Nula o ponteiro
						PonteiroTrabalho = Nulo;
					}
				}

				//Conversão implicita por IntPtr.
			public:
				static operator CA_SAFEARRAY^ (IntPtr Param_Pointer)
				{
					//Variavel a ser retornada.
					CA_SAFEARRAY^ Resultado = nullptr;

					//Ponteiro Nativo.
					SAFEARRAY* vi_pSafeArray = Nulo;

					//Verifica se o ponteiro é valido
					if (Param_Pointer == IntPtr::Zero)
						Sair; //Ponteiro Invalido.

					//Tenta converter o ponteiro para um SAFEARRAY.
					vi_pSafeArray = reinterpret_cast<SAFEARRAY*>(Param_Pointer.ToPointer());

					//Verifica se converteu com sucesso.
					if (!ObjetoValido(vi_pSafeArray))
						Sair; // Conversão falhou

					//Cria a variante
					Resultado = gcnew CA_SAFEARRAY();

					//Define o ponteiro.
					Resultado->PonteiroTrabalho = vi_pSafeArray;

				Done:;
					//Retorna a estrutura.
					return Resultado;
				}

				//Propriedades publicas.
			public:
				/// <summary>
				/// Membro responsável por conter a quantidade de dimensões do array.
				/// esse valor representa a quantidade de elementos no membro (rgsabound).
				/// </summary>
				property USHORT                         cDims
				{
					USHORT get() 
					{
						return PonteiroTrabalho->cDims;
					}
				}

				/// <summary>
				/// Um conjunto de flags ou ZERO que descrevem como a matriz foi lançada, alocada e o seu tipo de dado.
				/// </summary>
				property Enumeracoes::CA_FADF_FLAGS     fFeatures
				{
					Enumeracoes::CA_FADF_FLAGS get()
					{
						return static_cast<Enumeracoes::CA_FADF_FLAGS>(PonteiroTrabalho->fFeatures);
					}

					void set(Enumeracoes::CA_FADF_FLAGS Param_Value)
					{
						PonteiroTrabalho->fFeatures = static_cast<USHORT>(Param_Value);
					}
				}

				/// <summary>
				/// Membro que define o tamanho de apenas um elemento na matriz.
				/// </summary>
				property ULONG                           cbElements
				{
					ULONG get()
					{
						return PonteiroTrabalho->cbElements;
					}

					void set(ULONG Param_value)
					{
						PonteiroTrabalho->cbElements = Param_value;
					}
				}
				
				/// <summary>
				/// O número de vezes que a matriz foi bloqueada sem um desbloqueio correspondente.
				/// </summary>
				property ULONG                           cLocks
				{
					ULONG get()
					{
						return PonteiroTrabalho->cLocks;
					}
				}

				/// <summary>
				/// Um array com a descrição de cada dimensão.
				/// </summary>
				property cli::array<CA_SAFEARRAYBOUND>^ rgsabound
				{
					cli::array<CA_SAFEARRAYBOUND>^ get() 
					{
						//Variavel a ser retornada.
						cli::array<CA_SAFEARRAYBOUND>^ vi_SafeBoundArray = nullptr;

						//Variaveis a serem utilizadas
						USHORT vi_CountDim = 0; //Quantidade de dimensões.

						//Verifica se o ponteiro para o safe array não é invalido.
						if (!ObjetoValido(PonteiroTrabalho))
							Sair;				

						//Obtém a quantidade de dimensoes
						vi_CountDim = PonteiroTrabalho->cDims;

						//Cria a matriz que vai conter os dados.
						vi_SafeBoundArray = gcnew cli::array<CA_SAFEARRAYBOUND>(vi_CountDim);

						//Faz um for para definir os dados no array
						for (int i = 0; i < vi_CountDim; i++)
						{
							//Cria a estrutura de valor.
							vi_SafeBoundArray[i] = CA_SAFEARRAYBOUND();

							//Define os dados na estrutura.
							vi_SafeBoundArray[i].cElements = PonteiroTrabalho->rgsabound[i].cElements;
							vi_SafeBoundArray[i].lLbound = PonteiroTrabalho->rgsabound[i].lLbound;
						}

					Done:;

						//Retorna o array.
						return vi_SafeBoundArray;
					}
				}

				//Métodos.
			public:
				/// <summary>
				/// Método responsável por retornar os dados do ponteiro (pvData) como um array.
				/// </summary>
				/// <typeparam name="BufferType">O tipo do buffer que está armazenado no safearray.</typeparam>
				/// <returns></returns>
				generic <typename BufferType>
					cli::array<BufferType>^ GetPvData()
					{
						//Variavel a ser retornada.
						cli::array<BufferType>^ BufferPvData = nullptr;

						//Variaveis utilizadas.
						HRESULT Hr = E_FAIL;
						VARENUM vi_TipoVar = VARENUM::VT_NULL;

						//Recupera o tipo do safe array.
						Hr = SafeArrayGetVartype(PonteiroTrabalho, reinterpret_cast<VARTYPE*>(&vi_TipoVar));

						//Verifica se não houve erro.
						if (!Sucesso(Hr))
							Sair; //Falhou ao obter o tipo do SAFEARRAY.

						//Abre um swtich para verifica o tipo do SAFEARRAY. Os valores informados aqui são tirados da documentação do PROPVARIANT sobre os tipos que um SafeArray carrega a parti
						//de uma PROPVARIANT.
						//https://docs.microsoft.com/en-us/windows/win32/api/propidlbase/ns-propidlbase-propvariant
						//https://docs.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum
						switch (vi_TipoVar)
						{
						//Tipo : CHAR - 1 Caracter
						case VARENUM::VT_I1:
						{
							//Cria um array com o tipo especificado para ser retornado.

							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<WCHAR>^ vi_ArrayDados = nullptr;
							CHAR* vi_pBufferOrigem = Nulo; //Buffer origem do SAFEARRAY
							WCHAR* vi_pBufferOrigemCovnertedToUTF8 = Nulo;

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<WCHAR>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Char> vi_PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o buffer em ANSI para UTF8.
							vi_pBufferOrigemCovnertedToUTF8 = ReinterpretarCharsToUTF8_W(const_cast<char*>(vi_pBufferOrigem));

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferOrigemCovnertedToUTF8))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-UI1) - Houve uma falha ao tentar converter o buffer ANSI para UTF8.");
						
							//Copia os dados para o buffer gerenciado.
							std::copy(vi_pBufferOrigemCovnertedToUTF8, vi_pBufferOrigemCovnertedToUTF8 + vi_CountItens, reinterpret_cast<WCHAR*>(vi_PinToIndexZeroBuffer));

							//Libera a memória utilizada pelo buffer convertido.
							DeletarStringAllocatedSafe(&vi_pBufferOrigemCovnertedToUTF8);

							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : BYTE - 1 Caracter não assinado.
						case VARENUM::VT_UI1:
						{
							//Cria um array com o tipo especificado para ser retornado.

							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Byte>^ vi_ArrayDados = nullptr;
							BYTE* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							BYTE* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Byte>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Byte> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<BYTE*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-UI1) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem) + vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : Int16 - 2 Bytes assinados
						case VARENUM::VT_I2:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Int16>^ vi_ArrayDados = nullptr;
							INT16* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							INT16* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Int16>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int16> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<INT16*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : UInt16 - 2 Bytes não assinado
						case VARENUM::VT_UI2:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<UInt16>^ vi_ArrayDados = nullptr;
							UINT16* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							UINT16* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<UInt16>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt16> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<UINT16*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : Int32 - 4 Bytes assinados.
						case VARENUM::VT_I4:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Int32>^ vi_ArrayDados = nullptr;
							INT32* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							INT32* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Int32>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<INT32*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : UInt32 - 4 Bytes não assinados.
						case VARENUM::VT_UI4:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<UInt32>^ vi_ArrayDados = nullptr;
							UINT32* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							UINT32* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<UInt32>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt32> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<UINT32*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : INT -> Int32
						case VARENUM::VT_INT:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Int32>^ vi_ArrayDados = nullptr;
							INT* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							INT32* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Int32>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<INT32*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : UINT -> UInt32
						case VARENUM::VT_UINT:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<UInt32>^ vi_ArrayDados = nullptr;
							UINT* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							UINT32* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<UInt32>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt32> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<UINT32*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);

							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : FLOAT - 4 Bytes reais
						case VARENUM::VT_R4:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<float>^ vi_ArrayDados = nullptr;
							FLOAT* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							FLOAT* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<float>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<float> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<FLOAT*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : DOUBLE - 8 Bytes reais
						case VARENUM::VT_R8:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<double>^ vi_ArrayDados = nullptr;
							DOUBLE* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							DOUBLE* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<double>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<double> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<DOUBLE*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : BOOLEAN -> SHORT (-1 = TRUE) | (0 = FALSE)
						case VARENUM::VT_BOOL:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Boolean>^ vi_ArrayDados = nullptr;
							SHORT* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							
							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Boolean>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Faz um laço para definir os dados.
							for (UINT32 i = 0; i < vi_CountItens; i++)
							{
								//Converte e define no array.
								vi_ArrayDados[i] = vi_pBufferOrigem[i] == -1 ? true : false;
							}


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : tagDEC -> 16 Bytes fixed
						case VARENUM::VT_DECIMAL:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<CA_DEC>^ vi_ArrayDados = nullptr;
							DECIMAL* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<CA_DEC>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Abre um for para converter e definir no array.
							for (UINT32 i = 0; i < vi_CountItens; i++)
							{
								//Cria a estrutura no id especificado.
								vi_ArrayDados[i] = CA_DEC();

								//Define os dados na estrutura.
								vi_ArrayDados[i].Hi32 = vi_pBufferOrigem[i].Hi32;
								vi_ArrayDados[i].Mid32 = vi_pBufferOrigem[i].Mid32;
								vi_ArrayDados[i].Lo32 = vi_pBufferOrigem[i].Lo32;
								vi_ArrayDados[i].Lo64 = vi_pBufferOrigem[i].Lo64;
								vi_ArrayDados[i].scale = vi_pBufferOrigem[i].scale;
								vi_ArrayDados[i].sign = vi_pBufferOrigem[i].sign;
								vi_ArrayDados[i].signscale = vi_pBufferOrigem[i].signscale;
							}


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : SCODE -> 4 Bytes assinados (Int32)
						case VARENUM::VT_ERROR:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<Int32>^ vi_ArrayDados = nullptr;
							SCODE* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							INT32* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<Int32>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<INT32*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : CA_CY -> 2 dados de 8 Bytes.
						case VARENUM::VT_CY:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<CA_CY>^ vi_ArrayDados = nullptr;
							CY* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<CA_CY>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Abre um for para converter e definir no array.
							for (UINT32 i = 0; i < vi_CountItens; i++)
							{
								//Cria a estrutura no id especificado.
								vi_ArrayDados[i] = CA_CY();

								//Define os dados na estrutura.
								vi_ArrayDados[i].Hi = vi_pBufferOrigem[i].Hi;
								vi_ArrayDados[i].Lo = vi_pBufferOrigem[i].Lo;
								vi_ArrayDados[i].int64 = vi_pBufferOrigem[i].int64;
							}


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : DOUBLE -> 8 Bytes Reais
						case VARENUM::VT_DATE:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<double>^ vi_ArrayDados = nullptr;
							DOUBLE* vi_pBufferOrigem = Nulo; //Buffer do SAFEARRAY.
							DOUBLE* vi_pBufferDestino = Nulo; //Buffer nativo que se liga ao gerenciado.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<double>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferOrigem));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<double> PinToIndexZeroBuffer = &vi_ArrayDados[0];

							//Converte o pinptr para um buffer do tipo de destino.
							vi_pBufferDestino = reinterpret_cast<DOUBLE*>(PinToIndexZeroBuffer);

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferDestino))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I2) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

							//Copia os dados do nativo para o gerenciado.
							std::copy(vi_pBufferOrigem, (vi_pBufferOrigem)+vi_CountItens, vi_pBufferDestino);


							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : String
						case VARENUM::VT_BSTR:
						{
							//Cria um array com o tipo especificado para ser retornado.

							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<String^>^ vi_ArrayDados = nullptr;
							BSTR vi_pTempBSTR = Nulo;
							long lb, ub = 0; //Variaveis para pecorrer o safearray.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<String^>(vi_CountItens);

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Faz um for para acessar os dados.
							for (long i = lb; i < ub; i++)
							{
								//Recupera o ponteiro para o BSTR.
								Hr = SafeArrayGetElement(PonteiroTrabalho, &i, &vi_pTempBSTR);

								//Verifica se não houve erro
								if (!Sucesso(Hr))
									continue; //Pula para o proximo.

								//Verifica se o BSTR é valido
								if (!ObjetoValido(vi_pTempBSTR))
									continue; //Pula para o proximo.

								//Converte o BSTR para uma string gerenciada e define no array.
								vi_ArrayDados[i] = gcnew String(vi_pTempBSTR);

								//Libere a copia da BSTR obtida pelo método (SafeArrayGetElement).
								DeletarStringBSTRSafe(&vi_pTempBSTR);
							}

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : IDispath Interface (Representado por IntPtr)
						case VARENUM::VT_DISPATCH:
						{
							//Cria um array com o tipo especificado para ser retornado.

							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<IntPtr>^ vi_ArrayDados = nullptr;
							IDispatch *vi_pDispatchTemp = Nulo;
							long lb, ub = 0; //Variavel que indica a dimensão e o id.

							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<IntPtr>(vi_CountItens);

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Faz um for para acessar os dados.
							for (long i = lb; i < ub; i++)
							{
								//Recupera o ponteiro para o BSTR.
								Hr = SafeArrayGetElement(PonteiroTrabalho, &i, vi_pDispatchTemp);

								//Verifica se não houve erro
								if (!Sucesso(Hr))
									continue; //Pula para o proximo.

								//Verifica se o BSTR é valido
								if (!ObjetoValido(vi_pDispatchTemp))
									continue; //Pula para o proximo.

								//Obtém um ponteiro gerenciado para a interface e define no array.
								vi_ArrayDados[i] = IntPtr(vi_pDispatchTemp);
							}

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : IUnknown Interface (Representado por IntPtr)
						case VARENUM::VT_UNKNOWN:
						{
							//Cria um array com o tipo especificado para ser retornado.

							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<IntPtr>^ vi_ArrayDados = nullptr;
							IUnknown* vi_pUnkownTemp = Nulo;
							long lb, ub = 0; //Variavel que indica a dimensão e o id.
							
							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<IntPtr>(vi_CountItens);

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Faz um for para acessar os dados.
							for (long i = lb; i < ub; i++)
							{
								//Recupera o ponteiro para o BSTR.
								Hr = SafeArrayGetElement(PonteiroTrabalho, &i, vi_pUnkownTemp);

								//Verifica se não houve erro
								if (!Sucesso(Hr))
									continue; //Pula para o proximo.

								//Verifica se o BSTR é valido
								if (!ObjetoValido(vi_pUnkownTemp))
									continue; //Pula para o proximo.

								//Obtém um ponteiro gerenciado para a interface e define no array.
								vi_ArrayDados[i] = IntPtr(vi_pUnkownTemp);
							}

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						//Tipo : CA_VARIANT
						case VARENUM::VT_VARIANT:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_CountItens = PonteiroTrabalho->rgsabound[0].cElements;
							cli::array<CA_VARIANT^>^ vi_ArrayDados = nullptr;
							VARIANT* vi_pArrayVariants = Nulo; //Buffer do SAFEARRAY.
							
							//Cria a matriz gerenciada a ser retornada.
							vi_ArrayDados = gcnew cli::array<CA_VARIANT^>(vi_CountItens);

							//Abre um lock para copiar os dados.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pArrayVariants));

							//Verifica se não houve erro e sai do método.
							if (!Sucesso(Hr))
								Sair;

							//Faz um for para pecorrer todas as variantes e definir na estrutura.
							for (UINT32 i = 0; i < vi_CountItens; i++)
							{
								//Cria a variante gerenciada.
								vi_ArrayDados[i] = gcnew CA_VARIANT();

								//Define a variante no ponteiro de trabalho.
								vi_ArrayDados[i]->PonteiroTrabalho = &vi_pArrayVariants[i];
							}

							//Libera o SAFEARRAY.
							SafeArrayUnaccessData(PonteiroTrabalho);

							//Define o array criado no array que será retornado.
							BufferPvData = (cli::array<BufferType>^)vi_ArrayDados;
						}
						break;

						default:
							//Tipo desconhecido ou não suportado.
							Sair;
							break;
						}

					Done:;

						//Retorna o buffer.
						return BufferPvData;
					}

				/// <summary>
				/// Método responsável por retornar os dados ponteiro (pvData) em um ReadOnlySpan com o tipo definido pelo usuário.
				/// Estruturas, Interfaces e Strings não são suportados por esse método.
				/// </summary>
				/// <typeparam name="BufferType">O tipo do buffer que está armazenado no safearray.</typeparam>
				/// <returns></returns>
				generic<typename BufferType> 
					ReadOnlySpan<BufferType> GetReadOnlyPvData()
					{
						//Variavel a ser retornada.
						ReadOnlySpan<BufferType> BufferPvData = nullptr;

						//Verifica se os dados são validos.
						if (!(ObjetoValido(PonteiroTrabalho) && ObjetoValido(PonteiroTrabalho->pvData)))
							Sair; //O SAFEARRAY ou os seus dados associados não são validos.

						//Associa um ReadOnlySpan ao Index 0 do buffer no safe array.
						BufferPvData = ReadOnlySpan<BufferType>(PonteiroTrabalho->pvData, PonteiroTrabalho->rgsabound[0].cElements);

					Done:;

						//Retorna o buffer.
						return BufferPvData;
					}

				/// <summary>
				/// Método responsável por retornar os dados ponteiro (pvData) em um Span com o tipo definido pelo usuário que pode ser modificado.
				/// Estruturas, Interfaces e Strings não são suportados por esse método.
				/// </summary>
				/// <typeparam name="BufferType">O tipo do buffer que está armazenado no safearray.</typeparam>
				/// <returns></returns>
				generic<typename BufferType>
					Span<BufferType> GetSpanPvData()
					{
						//Variavel a ser retornada.
						Span<BufferType> BufferPvData = nullptr;

						//Variaveis utilizadas.
						HRESULT Hr = E_FAIL;
						VARENUM vi_TipoVar = VARENUM::VT_NULL;

						//Recupera o tipo do safe array.
						Hr = SafeArrayGetVartype(PonteiroTrabalho, reinterpret_cast<VARTYPE*>(&vi_TipoVar));

						//Verifica se não houve erro.
						if (!Sucesso(Hr))
							Sair; //Falhou ao obter o tipo do SAFEARRAY.

						//Associa um Span ao Index 0 do buffer no safe array.
						BufferPvData = Span<BufferType>(PonteiroTrabalho->pvData, PonteiroTrabalho->rgsabound[0].cElements);

					Done:;

						//Retorna o buffer.
						return BufferPvData;
					}

				/// <summary>
				/// (VT_VARIANT PENDENTE) - Método responsável por adicionar um novo dado unico em um index especificado ao SafeArray. O dado deve ser do mesmo que o Vartype do SAFEARRAY.
				/// Chame o método (GetVarType) para saber o tipo dos dados no SAFEARRAY.
				/// </summary>
				/// <typeparam name="BufferType">o tipo do dado a ser adicionado no safearray.</typeparam>
				/// <param name="Param_Dados">Os dados a serem definidos.</param>
				generic<typename BufferType>
					CarenResult SetDataOnPvDataIndex(BufferType Param_Dados, UInt32 Param_Id)
					{
						//Variavel que vai retornar o resultado.
						CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

						//Variaveis a serem utilizadas.
						HRESULT Hr = E_FAIL;
						VARENUM vi_TipoVar = VARENUM::VT_NULL;
						LONG vi_Id[1] = { static_cast<LONG>(Param_Id) }; //Vai trabalhar apenas com uma dimensão.

						//Recupera o tipo do safe array.
						Hr = SafeArrayGetVartype(PonteiroTrabalho, reinterpret_cast<VARTYPE*>(&vi_TipoVar));

						//Verifica se não houve erro.
						if (!Sucesso(Hr))
							Sair; //Falhou ao obter o tipo do SAFEARRAY.

						//Abre um swtich para verifica o tipo do SAFEARRAY. Os valores informados aqui são tirados da documentação do PROPVARIANT sobre os tipos que um SafeArray carrega a parti
						//de uma PROPVARIANT.
						//https://docs.microsoft.com/en-us/windows/win32/api/propidlbase/ns-propidlbase-propvariant
						//https://docs.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum
						switch (vi_TipoVar)
						{
						//Tipo : CHAR - 1 Caracter
						case VARENUM::VT_I1:
						{
							//Variaveis a serem utilizadas.
							short vi_Dado = Convert::ToInt16(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : BYTE - 1 Caracter não assinado.
						case VARENUM::VT_UI1:
						{
							//Variaveis a serem utilizadas.
							BYTE vi_Dado = Convert::ToByte(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : Int16 - 2 Bytes assinados
						case VARENUM::VT_I2:
						{
							//Variaveis a serem utilizadas.
							INT16 vi_Dado = Convert::ToInt16(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : UInt16 - 2 Bytes não assinado
						case VARENUM::VT_UI2:
						{
							//Variaveis a serem utilizadas.
							UINT16 vi_Dado = Convert::ToUInt16(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : Int32 - 4 Bytes assinados.
						case VARENUM::VT_I4:
						{
							//Variaveis a serem utilizadas.
							INT32 vi_Dado = Convert::ToInt32(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : UInt32 - 4 Bytes não assinados.
						case VARENUM::VT_UI4:
						{
							//Variaveis a serem utilizadas.
							UINT32 vi_Dado = Convert::ToUInt32(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : INT -> Int32
						case VARENUM::VT_INT:
						{
							//Variaveis a serem utilizadas.
							INT vi_Dado = Convert::ToInt32(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : UINT -> UInt32
						case VARENUM::VT_UINT:
						{
							//Variaveis a serem utilizadas.
							UINT vi_Dado = Convert::ToUInt32(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : FLOAT - 4 Bytes reais
						case VARENUM::VT_R4:
						{
							//Variaveis a serem utilizadas.
							FLOAT vi_Dado = Convert::ToSingle(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : DOUBLE - 8 Bytes reais
						case VARENUM::VT_R8:
						{
							//Variaveis a serem utilizadas.
							DOUBLE vi_Dado = Convert::ToDouble(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : BOOLEAN -> SHORT (-1 = TRUE) | (0 = FALSE)
						case VARENUM::VT_BOOL:
						{
							//Variaveis a serem utilizadas.
							short vi_Dado = Convert::ToBoolean(Param_Dados) == true ? -1 : 0;

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : DECIMAL -> 16 Bytes fixed
						case VARENUM::VT_DECIMAL:
						{
							//Variaveis a serem utilizadas.
							DECIMAL vi_Dado = { 0 }; //Variavel nativa.
							CA_DEC vi_DadoGen = (CA_DEC)((Object^)Param_Dados);

							//Define os dados na estrutura nativa.
							vi_Dado.Hi32 = vi_DadoGen.Hi32;
							vi_Dado.Lo32 = vi_DadoGen.Lo32;
							vi_Dado.Lo64 = vi_DadoGen.Lo64;
							vi_Dado.Mid32 = vi_DadoGen.Mid32;
							vi_Dado.scale = vi_DadoGen.scale;
							vi_Dado.sign = vi_DadoGen.sign;
							vi_Dado.signscale = vi_DadoGen.signscale;

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : SCODE -> 4 Bytes assinados (Int32)
						case VARENUM::VT_ERROR:
						{
							//Variaveis a serem utilizadas.
							INT32 vi_Dado = Convert::ToInt32(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : CA_CY -> 2 dados de 8 Bytes.
						case VARENUM::VT_CY:
						{
							//Variaveis a serem utilizadas.
							CY vi_Dado = { 0 }; //Variavel nativa.
							CA_CY vi_DadoGen = (CA_CY)((Object^)Param_Dados);

							//Define os dados na estrutura nativa.
							vi_Dado.Hi = vi_DadoGen.Hi;
							vi_Dado.Lo = vi_DadoGen.Lo;
							vi_Dado.int64 = vi_DadoGen.int64;

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : DOUBLE -> 8 Bytes Reais
						case VARENUM::VT_DATE:
						{
							//Variaveis a serem utilizadas.
							DOUBLE vi_Dado = Convert::ToDouble(Param_Dados);

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : String
						case VARENUM::VT_BSTR:
						{
							//Variaveis a serem utilizadas.
							BSTR vi_Dado = Nulo;
							String^ vi_DadosGen = Convert::ToString(Param_Dados);

							//Aloca os dados na BSTR.
							vi_Dado = static_cast<BSTR>(Marshal::StringToBSTR(vi_DadosGen).ToPointer());

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, &vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : IDispath Interface (Representado por IntPtr)
						case VARENUM::VT_DISPATCH:
						{
							//Variaveis a serem utilizadas.
							void* vi_Dado = Nulo;
							IntPtr vi_DadosGen = (IntPtr)((Object^)Param_Dados);

							//Define o ponteiro.
							vi_Dado = vi_DadosGen.ToPointer();

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : IUnknown Interface (Representado por IntPtr)
						case VARENUM::VT_UNKNOWN:
						{
							//Variaveis a serem utilizadas.
							void* vi_Dado = Nulo;
							IntPtr vi_DadosGen = (IntPtr)((Object^)Param_Dados);

							//Define o ponteiro.
							vi_Dado = vi_DadosGen.ToPointer();

							//Chama o método para definir os dados. 
							Hr = SafeArrayPutElement(PonteiroTrabalho, vi_Id, vi_Dado); //Já chama um Lock internamente.

							//Processo o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);
						}
						break;

						//Tipo : CA_VARIANT
						case VARENUM::VT_VARIANT:
						{
							//PENDENTE.
						}
						break;

						default:
							//Tipo desconhecido ou não suportado.
							Sair;
							break;
						}

					Done:;
						//Retorna o resultado
						return Resultado;
					}

				/// <summary>
				/// (VT_VARIANT PENDENTE) - 
				/// </summary>
				/// <typeparam name="BufferType">o tipo do dado a ser adicionado no safearray.</typeparam>
				/// <param name="Param_BufferDados">O Array com os dados a serem adicionados.</param>
				/// <param name="Param_CountData">A quantidade de dados.</param>
				/// <returns></returns>
				generic<typename BufferType>
					CarenResult SetDataArrayOnPvData(cli::array<BufferType>^ Param_BufferDados, UInt32 Param_CountData)
					{
						//Variavel que vai retornar o resultado.
						CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

						//Variaveis a serem utilizadas.
						HRESULT Hr = E_FAIL;
						VARENUM vi_TipoVar = VARENUM::VT_NULL;
						ULONG vi_CountElementsInSafeArray = PonteiroTrabalho->rgsabound[0].cElements;

						//Verifica se a quantidade fornecida não é maior do que a do SafeArray.
						if (Param_CountData > vi_CountElementsInSafeArray)
							throw gcnew IndexOutOfRangeException("A quantidade de dados informado ultrapssava o limite permitido pelo SafeArray.");

						//Recupera o tipo do safe array.
						Hr = SafeArrayGetVartype(PonteiroTrabalho, reinterpret_cast<VARTYPE*>(&vi_TipoVar));

						//Verifica se não houve erro.
						if (!Sucesso(Hr))
							Sair; //Falhou ao obter o tipo do SAFEARRAY.

						//Abre um swtich para verifica o tipo do SAFEARRAY.Os valores informados aqui são tirados da documentação do PROPVARIANT sobre os tipos que um SafeArray carrega a parti
						//de uma PROPVARIANT.
						//https://docs.microsoft.com/en-us/windows/win32/api/propidlbase/ns-propidlbase-propvariant
						//https://docs.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum
						switch (vi_TipoVar)
						{
							//Tipo : CHAR - 1 Caracter
						case VARENUM::VT_I1:
						{
							//Variaveis a serem utilizadas.
							CHAR* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<wchar_t>^ vi_BufferGen = (cli::array<wchar_t>^)Param_BufferDados; //Variavel com o buffer gerenciado.
							CHAR* vi_pBufferGenConvertedToAnsi = Nulo;

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<wchar_t> vi_PinToIndex0BufferGen = &vi_BufferGen[0];
							
							//Converte o buffer de dados para um buffer Ansi.
							vi_pBufferGenConvertedToAnsi = ReinterpretarCharsToANSI_A(const_cast<WCHAR*>(reinterpret_cast<WCHAR*>(vi_PinToIndex0BufferGen)));

							//Verifica se é valido
							if (!ObjetoValido(vi_pBufferGenConvertedToAnsi))
								throw gcnew NullReferenceException("(CA_SAFEARRAY->GetPvData-I1) - Houve uma falha ao tentar converter o buffer UTF8 para ANSI.");
							
							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferGenConvertedToAnsi, vi_pBufferGenConvertedToAnsi + vi_CountElementsInSafeArray, vi_pBufferDestino);

							//Libera a memória utilizada pelo buffer convertido.
							DeletarStringAllocatedSafe(&vi_pBufferGenConvertedToAnsi);

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : BYTE - 1 Caracter não assinado.
						case VARENUM::VT_UI1:
						{
							//Variaveis a serem utilizadas.
							BYTE* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Byte>^ vi_BufferGen = (cli::array<Byte>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Byte> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<BYTE*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : Int16 - 2 Bytes assinados
						case VARENUM::VT_I2:
						{
							//Variaveis a serem utilizadas.
							INT16* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Int16>^ vi_BufferGen = (cli::array<Int16>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int16> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<INT16*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : UInt16 - 2 Bytes não assinado
						case VARENUM::VT_UI2:
						{
							//Variaveis a serem utilizadas.
							UINT16* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<UInt16>^ vi_BufferGen = (cli::array<UInt16>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt16> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<UINT16*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : Int32 - 4 Bytes assinados.
						case VARENUM::VT_I4:
						{
							//Variaveis a serem utilizadas.
							INT32* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Int32>^ vi_BufferGen = (cli::array<Int32>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<INT32*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : UInt32 - 4 Bytes não assinados.
						case VARENUM::VT_UI4:
						{
							//Variaveis a serem utilizadas.
							UINT32* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<UInt32>^ vi_BufferGen = (cli::array<UInt32>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt32> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<UINT32*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : INT -> Int32
						case VARENUM::VT_INT:
						{
							//Variaveis a serem utilizadas.
							INT32* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Int32>^ vi_BufferGen = (cli::array<Int32>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<INT32*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : UINT -> UInt32
						case VARENUM::VT_UINT:
						{
							//Variaveis a serem utilizadas.
							UINT32* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<UInt32>^ vi_BufferGen = (cli::array<UInt32>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<UInt32> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<UINT32*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : FLOAT - 4 Bytes reais
						case VARENUM::VT_R4:
						{
							//Variaveis a serem utilizadas.
							FLOAT* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<float>^ vi_BufferGen = (cli::array<float>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<float> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<FLOAT*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : DOUBLE - 8 Bytes reais
						case VARENUM::VT_R8:
						{
							//Variaveis a serem utilizadas.
							DOUBLE* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<double>^ vi_BufferGen = (cli::array<double>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<double> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<DOUBLE*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : BOOLEAN -> SHORT (-1 = TRUE) | (0 = FALSE)
						case VARENUM::VT_BOOL:
						{
							//Variaveis a serem utilizadas.
							SHORT* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Boolean>^ vi_BufferGen = (cli::array<Boolean>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Faz um for para converter de Boolean para Short como é interpretado internamente.
							for (ULONG i = 0; i < vi_CountElementsInSafeArray; i++)
							{
								//Define e converte no array de destino.
								vi_pBufferDestino[i] = vi_BufferGen[i] == true ? -1 : 0;
							}

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : DECIMAL -> 16 Bytes fixed
						case VARENUM::VT_DECIMAL:
						{
							//Variaveis a serem utilizadas.
							DECIMAL* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<CA_DEC>^ vi_BufferGen = (cli::array<CA_DEC>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Faz um for para converter de Boolean para Short como é interpretado internamente.
							for (ULONG i = 0; i < vi_CountElementsInSafeArray; i++)
							{
								//Inicializa os dados.
								vi_pBufferDestino[i] = {};

								//Define no safearray.
								vi_pBufferDestino[i].Hi32 = vi_BufferGen[i].Hi32;
								vi_pBufferDestino[i].Mid32 = vi_BufferGen[i].Mid32;
								vi_pBufferDestino[i].Lo32 = vi_BufferGen[i].Lo32;
								vi_pBufferDestino[i].Lo64 = vi_BufferGen[i].Lo64;
								vi_pBufferDestino[i].scale = vi_BufferGen[i].scale;
								vi_pBufferDestino[i].sign = vi_BufferGen[i].sign;
								vi_pBufferDestino[i].signscale = vi_BufferGen[i].signscale;
							}

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : SCODE -> 4 Bytes assinados (Int32)
						case VARENUM::VT_ERROR:
						{
							//Variaveis a serem utilizadas.
							INT32* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<Int32>^ vi_BufferGen = (cli::array<Int32>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<Int32> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<INT32*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : CA_CY -> 2 dados de 8 Bytes.
						case VARENUM::VT_CY:
						{
							//Variaveis a serem utilizadas.
							CY* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<CA_CY>^ vi_BufferGen = (cli::array<CA_CY>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Faz um for para converter de Boolean para Short como é interpretado internamente.
							for (ULONG i = 0; i < vi_CountElementsInSafeArray; i++)
							{
								//Inicializa os dados.
								vi_pBufferDestino[i] = {};

								//Define no safearray.
								vi_pBufferDestino[i].Hi = vi_BufferGen[i].Hi;
								vi_pBufferDestino[i].int64 = vi_BufferGen[i].int64;
								vi_pBufferDestino[i].Lo = vi_BufferGen[i].Lo;
							}

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : DOUBLE -> 8 Bytes Reais
						case VARENUM::VT_DATE:
						{
							//Variaveis a serem utilizadas.
							DOUBLE* vi_pBufferDestino = Nulo; //Buffer do SAFEARRAY.
							cli::array<double>^ vi_BufferGen = (cli::array<double>^)Param_BufferDados;  //Variavel com o buffer gerenciado.

							//Tenta acessar os dados no safearray para definir.
							Hr = SafeArrayAccessData(PonteiroTrabalho, reinterpret_cast<void**>(&vi_pBufferDestino));

							//Processa o resultado.
							Resultado.ProcessarCodigoOperacao(Hr);

							//Verifica se não houve erro
							if (Resultado.StatusCode != ResultCode::SS_OK)
								Sair;

							//Cria um pin para o buffer gerenciado.
							pin_ptr<double> vi_PinToIndex0BufferGen = &vi_BufferGen[0];

							//Realiza a copia dos dados para o SAFEARRAY.
							std::copy(vi_pBufferDestino, vi_pBufferDestino + vi_CountElementsInSafeArray, reinterpret_cast<DOUBLE*>(vi_PinToIndex0BufferGen));

							//Libera o acesso ao array.
							SafeArrayUnaccessData(PonteiroTrabalho);
						}
						break;

						//Tipo : String
						case VARENUM::VT_BSTR:
						{
							//Variaveis a serem utilizadas.
							cli::array<String^>^ vi_BufferGen = (cli::array<String^>^)Param_BufferDados;  //Variavel com o buffer gerenciado.
							BSTR vi_pBSTRTemp = Nulo; //Ponteiro que vai conter a BSTR temporaria.
							long lb, ub = 0;

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Cria um for para definir os ponteiros BSTR.
							for (long i = lb; i < ub; i++)
							{
								//O método abaixo é responsável por criar uma copia da BSTR passada.
								//O método também libera os dados já existente, se houverem.


								//Cria a BSTR que será passada para o método.
								vi_pBSTRTemp = static_cast<BSTR>(Marshal::StringToBSTR(vi_BufferGen[i]).ToPointer());

								//Chama um método para definir os dados no index.
								SafeArrayPutElement(PonteiroTrabalho, &i, vi_pBSTRTemp);

								//Libera a BSTR temporaria.
								DeletarStringBSTRSafe(&vi_pBSTRTemp);

								//Nula
								vi_pBSTRTemp = Nulo;
							}			
						}
						break;

						//Tipo : IDispath Interface (Representado por IntPtr)
						case VARENUM::VT_DISPATCH:
						{
							//Variaveis a serem utilizadas.
							cli::array<IntPtr>^ vi_BufferGen = (cli::array<IntPtr>^)Param_BufferDados;  //Variavel com o buffer gerenciado.
							long lb, ub = 0;

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Cria um for para definir os ponteiros.
							for (long i = lb; i < ub; i++)
							{
								//O método abaixo já é responsável por incriementar a contagem de referencias da interface(AddRef).

								//Chama o método para definir o ponteiro no index.
								SafeArrayPutElement(PonteiroTrabalho, &i, vi_BufferGen[i].ToPointer());
							}
						}
						break;

						//Tipo : IUnknown Interface (Representado por IntPtr)
						case VARENUM::VT_UNKNOWN:
						{
							//Variaveis a serem utilizadas.
							cli::array<IntPtr>^ vi_BufferGen = (cli::array<IntPtr>^)Param_BufferDados;  //Variavel com o buffer gerenciado.
							long lb, ub = 0;

							//Obtém os dados dos: lb & ub
							SafeArrayGetLBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &lb);
							SafeArrayGetUBound(PonteiroTrabalho, PonteiroTrabalho->cDims, &ub);

							//Cria um for para definir os ponteiros.
							for (long i = lb; i < ub; i++)
							{
								//O método abaixo já é responsável por incriementar a contagem de referencias da interface(AddRef).

								//Chama o método para definir o ponteiro no index.
								SafeArrayPutElement(PonteiroTrabalho, &i, vi_BufferGen[i].ToPointer());
							}
						}
						break;

						//Tipo : CA_VARIANT
						case VARENUM::VT_VARIANT:
						{
							//PENDENTE.
						}
						break;

						default:
							//Tipo desconhecido ou não suportado.
							Sair;
							break;
						}

					Done:;
						//Retorna o resultado
						return Resultado;
					}

				/// <summary>
				/// Retorna um IntPtr que é um ponteiro para os dados do safearray (void**)
				/// </summary>
				/// <returns></returns>
				IntPtr GetPointerBuffer()
				{
					return IntPtr(PonteiroTrabalho->pvData);
				}

				/// <summary>
				/// Método responsável por retornar um valor booleano que indica se o SafeArray na estrutura é valido.
				/// </summary>
				/// <returns></returns>
				Boolean GetStatusSafeArray()
				{
					return ObjetoValido(PonteiroTrabalho) ? true : false;
				}

				/// <summary>
				/// Retorna o tipo de dados armazenados por essa instância do SAFEARRAY.
				/// </summary>
				/// <returns></returns>
				Enumeracoes::CA_VARTYPE GetVarType()
				{
					//Variavel a ser retornada.
					Enumeracoes::CA_VARTYPE Resultado = Enumeracoes::CA_VARTYPE::VT_EMPTY;

					//Variaveis a serem utilizadas.
					HRESULT Hr = E_FAIL;
					VARTYPE vi_TypeSafeArray = 0;

					//Chama o método para obter o tipo de dados do safe array.
					Hr = SafeArrayGetVartype(PonteiroTrabalho, &vi_TypeSafeArray);

					//Verifica se não houve erro
					if (!Sucesso(Hr))
						Sair;

					//Define o resultado na variavel de saida.
					Resultado = static_cast<Enumeracoes::CA_VARTYPE>(vi_TypeSafeArray);

				Done:;
					//Retorna o resultado.
					return Resultado;
				}

				/// <summary>
				/// Cópia o safe array atual para um de destino. O método é responsável por inicializar o SAFEARRAY de destino.
				/// </summary>
				/// <param name="Param_Out_SafeArrayDestino">O ponteiro para o safe array de DESTINO.</param>
				/// <returns></returns>
				CarenResult CopyTo(LPSAFEARRAY* Param_Out_SafeArrayDestino)
				{
					//Variavel a ser retornada.
					CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

					//Variaveis
					HRESULT Hr = E_FAIL;
					VARTYPE vi_vt = VT_EMPTY;

					//Verifica se o SAFEARRAY atual é valida
					if (!ObjetoValido(PonteiroTrabalho))
					{
						//O ponteiro da variante atual não é valido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Verifica se o ponteiro leva a um destino válido para armazenar a PROPVARIANT.
					if (!ObjetoValido(Param_Out_SafeArrayDestino))
					{
						//O ponteiro não leva a um local válido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Obtém o tipo do safearray.
					vi_vt = static_cast<VARTYPE>(GetVarType());
					
					//Cria o SAFEARRAY.
					*Param_Out_SafeArrayDestino = SafeArrayCreate(vi_vt, PonteiroTrabalho->cDims, PonteiroTrabalho->rgsabound);

					//Cria uma cópia da SAFEARRAY atual.
					Hr = SafeArrayCopy(PonteiroTrabalho, Param_Out_SafeArrayDestino);

					//Processa o código.
					Resultado.ProcessarCodigoOperacao(Hr);

					//Verifica se teve sucesso na cópia, se não deleta os dados.
					if (Resultado.StatusCode != ResultCode::SS_OK)
					{
						//Deleta o SAFEARRAY.
						SafeArrayDestroy(*Param_Out_SafeArrayDestino);

						//Nula o ponteiro.
						*Param_Out_SafeArrayDestino = Nulo;
					}

				Done:;

					//Retorna o resultado
					return Resultado;
				}

				/// <summary>
				/// Cópia um SAFEARRAY de destino para o SAFEARRAY atual. O método já responsável por inicializar os dados necessários.
				/// </summary>
				/// <param name="Param_SafeArraySource">O ponteiro para o safe array de ORIGEM.</param>
				/// <returns></returns>
				CarenResult CopyFrom(LPSAFEARRAY* Param_SafeArraySource)
				{
					//Variavel a ser retornada.
					CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

					//Variaveis
					HRESULT Hr = E_FAIL;
					VARTYPE vi_vt = VT_EMPTY;
					LPSAFEARRAY vi_pOutSafeArray = Nulo;

					//Verifica se o ponteiro leva a um destino válido para poder cópiar.
					if (!ObjetoValido(Param_SafeArraySource) )
					{
						//O ponteiro não leva a um local válido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Verifica se o endereço principal onde está o SAFEARRAY é válido.
					if (!ObjetoValido(*Param_SafeArraySource))
					{
						//O ponteiro não leva a um local válido.

						//Define erro.
						Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

						//Sai do método
						Sair;
					}

					//Chama o método para obter o tipo de dados do safe array.
					SafeArrayGetVartype(*Param_SafeArraySource, &vi_vt);

					//Cria o safearray atual que vai receber os dados.
					vi_pOutSafeArray = SafeArrayCreate(vi_vt, (*Param_SafeArraySource)->cDims, (*Param_SafeArraySource)->rgsabound);

					//Cria uma cópia do SAFEARRAY de origem para o de destino.
					Hr = SafeArrayCopy(*Param_SafeArraySource, &vi_pOutSafeArray);

					//Verifica se teve sucesso na cópia, se não deleta os dados.
					if (Resultado.StatusCode != ResultCode::SS_OK)
					{
						//Deleta o SAFEARRAY.
						SafeArrayDestroy(PonteiroTrabalho);

						//Nula o ponteiro.
						PonteiroTrabalho = Nulo;
					}

					//Define o SAFEARRAY no ponteiro de trabalho.
					PonteiroTrabalho = vi_pOutSafeArray;

				Done:;

					//Retorna o resultado
					return Resultado;
				}
			};

			/// <summary>
			/// (tagCLIPDATA) - 
			/// </summary>
			public value struct CA_CLIPDATA
			{
				UInt32          cbSize;
				Int32           ulClipFmt;
				
				/// <summary>
				/// Deve representar uma interface ICarenBuffer.
				/// </summary>
				Object^         pClipData;
			};
			
			/// <summary>
			/// (tagVersionedStream) - 
			/// </summary>
			public value struct CA_VersionedStream
			{
				String^ guidVersion;
			
				/// <summary>
				/// Deve representar uma interface ICarenStream
				/// </summary>
				Object^ pStream;
			};

			/// <summary>
			/// (LARGE_INTEGER) - 
			/// </summary>
			public value struct CA_LARGE_INTEGER
			{
				UInt32 LowPart;
				Int32 HighPart;
				Int64 QuadPart;
			};
			
			/// <summary>
			/// (ULARGE_INTEGER) - 
			/// </summary>
			public value struct CA_ULARGE_INTEGER
			{
				UInt32 LowPart;
				UInt32 HighPart;
				UInt64 QuadPart;
			};

			/// <summary>
			/// (tagCAC) - Estrutura que representa uma matriz contada do tipo: CHAR
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAC
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<char>^ pElems;
			};

			/// <summary>
			/// (tagCAUB) - Estrutura que representa uma matriz contada do tipo: UCHAR
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAUB
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<Byte>^ pElems;
			};

			/// <summary>
			/// (tagCAI) - Estrutura que representa uma matriz contada do tipo: SHORT
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAI
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<Int16>^ pElems;
			};

			/// <summary>
			/// (tagCAUI) - Estrutura que representa uma matriz contada do tipo: USHORT
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAUI
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<UInt16>^ pElems;
			};

			/// <summary>
			/// (tagCAL) - Estrutura que representa uma matriz contada do tipo: Int32
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAL
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<Int32>^ pElems;
			};

			/// <summary>
			/// (tagCAUL) - Estrutura que representa uma matriz contada do tipo: UInt32
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAUL
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<UInt32>^ pElems;
			};

			/// <summary>
			/// (tagCAFLT) - Estrutura que representa uma matriz contada do tipo: FLOAT
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAFLT
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<float>^ pElems;
			};

			/// <summary>
			/// (tagCADBL) - Estrutura que representa uma matriz contada do tipo: DOUBLE
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CADBL
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<double>^ pElems;
			};

			/// <summary>
			/// (tagCACY) - Estrutura que representa uma matriz contada do tipo: CA_CY
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CACY
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_CY>^ pElems;
			};

			/// <summary>
			/// (tagCADATE) - Estrutura que representa uma matriz contada do tipo: DATA - DOUBLE
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CADATE
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<double>^ pElems;
			};

			/// <summary>
			/// (tagCABSTR) - Estrutura que representa uma matriz contada do tipo: STRING
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CABSTR
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<String^>^ pElems;
			};

			/// <summary>
			/// (tagCABSTRBLOB) - Estrutura que representa uma matriz contada do tipo: CA_BlobData
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CABSTRBLOB
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_BlobData>^ pElems;
			};

			/// <summary>
			/// (tagCABOOL) - Estrutura que representa uma matriz contada do tipo: BOOLEAN
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CABOOL
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<Boolean>^ pElems;
			};

			/// <summary>
			/// (tagCASCODE) - Estrutura que representa uma matriz contada do tipo: Int32 - HRESULTs
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CASCODE
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<Int32>^ pElems;
			};			

			/// <summary>
			/// (tagCAH) - Estrutura que representa uma matriz contada do tipo: CA_LARGE_INTEGER
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAH
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_LARGE_INTEGER>^ pElems;
			};

			/// <summary>
			/// (tagCAUH) - Estrutura que representa uma matriz contada do tipo: CA_ULARGE_INTEGER
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAUH
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_ULARGE_INTEGER>^ pElems;
			};
			
			/// <summary>
			/// (tagCALPSTR) - Estrutura que representa uma matriz contada do tipo: STRING
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CALPSTR
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<String^>^ pElems;
			};

			/// <summary>
			/// (tagCALPWSTR) - Estrutura que representa uma matriz contada do tipo: STRING
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CALPWSTR
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<String^>^ pElems;
			};

			/// <summary>
			/// (tagCAFILETIME) - Estrutura que representa uma matriz contada do tipo: CA_FILETIME
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CAFILETIME
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_FILETIME>^ pElems;
			};

			/// <summary>
			/// (tagCACLIPDATA) - Estrutura que representa uma matriz contada do tipo: CA_CLIPDATA
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CACLIPDATA
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_CLIPDATA>^ pElems;
			};

			/// <summary>
			/// (tagCACLSID) - Estrutura que representa uma matriz contada do tipo: STRING - CLSID
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public value struct CA_CACLSID
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<String^>^ pElems;
			};

			/// <summary>
			/// (PROPVARIANT) - 
			/// </summary>
			public ref struct CA_PROPVARIANT
			{
				/// <summary>
				/// Especifica o tipo de valor que essa estrutua está contendo.
				/// </summary>
				Enumeracoes::CA_VARTYPE vt;

				//Tipos simples.

				char cVal;
				Byte bVal;
				Int16 iVal;
				UInt16 uiVal;
				Int32 lVal;
				UInt32 ulVal;
				Int32 intVal;
				UInt32 uintVal;
				CA_LARGE_INTEGER hVal;
				CA_ULARGE_INTEGER uhVal;
				float fltVal;
				double dblVal;
				Boolean boolVal;
				Int32 scode;
				CA_CY cyVal;
				DOUBLE date;
				CA_FILETIME filetime;
				String^ puuid;
				CA_CLIPDATA pclipdata;
				String^ bstrVal;
				CA_BlobData blob;
				String^ pszVal;
				String^ pwszVal;
				Object^ punkVal;
				Object^ pdispVal;
				Object^ pStream;
				Object^ pStorage;
				CA_VersionedStream pVersionedStream;
				CA_SAFEARRAY^ parray;
				CA_DEC decVal;


				//Matrizes Contadas | VT_VECTOR

				CA_CAC cac;
				CA_CAUB caub;
				CA_CAI cai;
				CA_CAUI caui;
				CA_CAL cal;
				CA_CAUL caul;
				CA_CAH cah;
				CA_CAUH cauh;
				CA_CAFLT caflt;
				CA_CADBL cadbl;
				CA_CABOOL cabool;
				CA_CASCODE cascode;
				CA_CACY cacy;
				CA_CADATE cadate;
				CA_CAFILETIME cafiletime;
				CA_CACLSID cauuid;
				CA_CACLIPDATA caclipdata;
				CA_CABSTR cabstr;
				CA_CABSTRBLOB cabstrblob;
				CA_CALPSTR calpstr;
				CA_CALPWSTR calpwstr;
			
				/// <summary>
				/// Este membro representa a estrutura (CA_CAPROPVARIANT).
				/// </summary>
				Object^ capropvar;



				//Ponteiros | VT_BYREF
				
				CHAR pcVal;
				Byte pbVal;
				Int16 piVal;
				UInt16 puiVal;
				Int32 plVal;
				UInt32 pulVal;
				Int32 pintVal;
				UInt32 puintVal;
				float pfltVal;
				double pdblVal;
				Boolean pboolVal;
				CA_DEC pdecVal;
				Int32 pscode;
				CA_CY pcyVal;
				double pdate;
				String^ pbstrVal;
				IntPtr ppunkVal;
				IntPtr ppdispVal;
				CA_SAFEARRAY^ pparray;
				CA_PROPVARIANT^ pvarVal;		
			};		

			/// <summary>
			/// (tagCAPROPVARIANT) - Estrutura que representa uma matriz contada do tipo: CA_PROPVARIANT
			/// Essa estrutura é utilizada pela estrutura (CA_PROPVARIANT).
			/// </summary>
			public ref struct CA_CAPROPVARIANT
			{
				/// <summary>
				/// Variavel que informa a quantidade de items no membro (pElems).
				/// </summary>
				UInt32 cElems;

				/// <summary>
				/// Array que contém os elementos contados da estrutura.
				/// </summary>
				cli::array<CA_PROPVARIANT^>^ pElems;
			};

			/// <summary>
			/// (MF_SINK_WRITER_STATISTICS) - Contém as estátisticas sobre o desempenho do do Gravador de Coletor.
			/// </summary>
			public ref struct CA_MF_SINK_WRITER_STATISTICS
			{
				/// <summary>
				/// (cb) O dimensionar da estrutura, em bytes. o valor da estrutura na memória não gerenciada.
				///</summary>
				UInt32 ES_DIMENSIONAR;

				/// <summary>
				/// (llLastTimestampReceived) O carimbo de data/hora da amostra mais recente dada ao gravador de coletor. O gravador de coletor atualiza esse valor
				/// sempre que o aplicativo chama o método (WriteSample).
				///</summary>
				Int64 ES_TIMESPAN_AMOSTRA_RECENTE_ENVIADA;

				/// <summary>
				/// (llLastTimestampEncoded) O carimbo de data/hora da amostra mais recente a ser codificado. O gravador de coletor atualiza esse valor sempre que 
				/// ele chama o método (ProcessOutput) no MFT do codificador.
				///</summary>
				Int64 ES_TIMESPAN_AMOSTRA_RECENTE_CODIFICADA;

				/// <summary>
				/// (llLastTimestampProcessed) O carimbo de data/hora da amostra mais recente fornecida para o coletor de mídia. O gravador de coletor atualiza esse 
				/// valor sempre que ele chama o método (ProcessSample) no coletor de mídia(ICarenMFStreamSink).
				///</summary>
				Int64 ES_TIMESPAN_AMOSTRA_RECENTE_PROCESSADA;

				/// <summary>
				/// (llLastStreamTickReceived) O carimbo de hora do Tick de fluxo mais recente. O gravador de coletor atualiza esse valor sempre que o aplicativo chama
				/// o método (SendStreamTick) no Gravador de Coletor(ICarenMFSinkWriter).
				///</summary>
				Int64 ES_TIMESPAN_TICK_FLUXO_RECENTE;

				/// <summary>
				/// (llLastSinkSampleRequest) A hora do sistema da solicitação de exemplo mais recente do coletor de mídia. O gravador de coletor atualiza esse valor 
				/// sempre que ele recebe um evento (MEStreamSinkRequestSample) do coletor de mídia. O valor é a hora atual do sistema.
				///</summary>
				Int64 ES_TIMESPAN_AMOSTRA_SOLICITACAO_RECENTE;

				/// <summary>
				/// (qwNumSamplesReceived) O número de amostras recebidas.
				///</summary>
				UInt64 ES_NUM_AMOSTRAS_RECEBIDAS;

				/// <summary>
				/// (qwNumSamplesEncoded) O número de amostras codificadas.
				///</summary>
				UInt64 ES_NUM_AMOSTRAS_CODIFICADAS;

				/// <summary>
				/// (qwNumSamplesProcessed) O número de amostras fornecidas para o coletor de mídia.
				///</summary>
				UInt64 ES_NUM_AMOSTRAS_PROCESSADAS;

				/// <summary>
				/// (qwNumStreamTicksReceived) O número de Ticks de fluxo recebidos.
				///</summary>
				UInt64 ES_NUM_TICKS_FLUXO_RECEBIDOS;

				/// <summary>
				/// (dwByteCountQueued) A quantidade de dados, em bytes, aguardando atualmente para ser processado.
				///</summary>
				UInt32 ES_BYTES_AGURDANDO;

				/// <summary>
				/// (qwByteCountProcessed) A quantidade total de dados, em bytes, que foi enviada para o coletor de mídia.
				///</summary>
				UInt64 ES_BYTES_TOTAL_ENVIDO;

				/// <summary>
				/// (dwNumOutstandingSinkSampleRequests) O número de solicitações de amostras pendentes.
				///</summary>
				UInt64 ES_NUM_SOLICITACOES_PENDENTES;

				/// <summary>
				/// (dwAverageSampleRateReceived) A taxa média, em amostras de mídia por 100-nanosegundos, em que o aplicativo enviado 
				/// amostras para o (Gravador de Coletor).
				///</summary>
				UInt64 ES_TAXA_MEDIA_AMOSTRAS_ENVIADAS;

				/// <summary>
				/// (dwAverageSampleRateEncoded) A taxa média, em amostras de mídia por 100-nanosegundos, em que o gravador de coletor 
				/// enviou amostras para o (Codificador).
				///</summary>
				UInt64 ES_TAXA_MEDIA_AMOSTRAS_CODIFICADS;

				/// <summary>
				/// (dwAverageSampleRateProcessed) A taxa média, em amostras de mídia por 100-nanosegundos, na qual o gravador de coletor 
				/// enviou amostras para o (Coletor de Mídia).
				///</summary>
				UInt64 ES_TAXA_MEDIA_AMOSTRAS_ENVIDAS_COLETOR_MIDIA;
			};
			
			/// <summary>
			/// (MFCLOCK_PROPERTIES) - Contém as propriedades de um Relógio.
			/// </summary>
			public ref struct CA_MFCLOCK_PROPERTIES
			{
				/// <summary>
				/// O intervalo no qual o relógio correlaciona seu tempo de clock com a hora do sistema, em unidades de 100-nanosecond. 
				/// Se o valor for zero, a correlação é feita sempre que o ICarenMFClock::GetCorrelatedTime método é chamado.
				///</summary>
				UInt64 qwCorrelationRate;
		
				/// <summary>
				/// O identificador exclusivo do dispositivo subjacente que fornece a hora. Se dois relógios têm o mesmo identificador 
				/// exclusivo, eles são baseados no mesmo dispositivo. Se o dispositivo subjacente não é compartilhado entre dois relógios, 
				/// o valor pode ser (NULO).
				///</summary>
				String^ guidClockId;
			
				/// <summary>
				/// Um bit a bit or dos sinalizadores do CA_MFCLOCK_RELATIONAL_FLAG enumeração.
				///</summary>
				Enumeracoes::CA_MFCLOCK_RELATIONAL_FLAG dwClockFlags;
		
				/// <summary>
				/// A frequência do relógio em Hz. Um valor de MFCLOCK_FREQUENCY_HNS significa que o relógio tem uma frequência de 10 MHz 
				/// (ticks de 100 nanossegundos), que é a unidade de tempo (MFTIME -> Int64) padrão no Media Foundation. Se o
				/// o método (ICarenMFClock::GetClockCharacteristics) devolver o sinalizador MFCLOCK_CHARACTERISTICS_FLAG_FREQUENCY_10MHZ , o valor
				/// deste campo deve ser MFCLOCK_FREQUENCY_HNS.
				///</summary>
				UInt64 qwClockFrequency;
		
				/// <summary>
				/// A quantidade de imprecisão que pode estar presente no relógio, em partes por bilhão (ppb). Por exemplo, uma imprecisão de 50 ppb 
				/// significa que o relógio pode derivar até 50 segundos por bilhão de segundos de tempo real. Se a tolerância não for conhecida, 
				/// o valor é MFCLOCK_TOLERANCE_UNKNOWN. Essa constante é igual a 50 partes por milhão (ppm).
				///</summary>
				UInt32 dwClockTolerance;
		
				/// <summary>
				/// A quantidade de jitter que pode estar presente, em unidades de 100 nanossegundos. Jitter é a variação na frequência devido à 
				/// amostragem do relógio subjacente. Jitter não inclui imprecisões causadas por deriva, que é refletido no valor de RL_TOLERANCIA_CLOCK.
				/// Para relógios com base em um único dispositivo, o jitter mínimo é o comprimento do período de escala (o inverso da freqüência). 
				/// Por exemplo, se a freqüência é de 10 Hz, o jitter é 0,1 segundo, que é 1 milhão em unidades (MFTIME -> Int64) . Esse valor reflete o fato de que 
				/// o relógio pode ser amostrado pouco antes do próximo Tick, resultando em uma hora de relógio que é um período menor do que o tempo real. 
				/// Se a frequência for maior que 10 MHz, o jitter deve ser definido como 1 (o valor mínimo).
				/// Se o dispositivo de hardware subjacente de um relógio não carimbo de hora diretamente os dados de entrada, o jitter também inclui o tempo 
				/// necessário para despachar a rotina de serviço de interrupção do driver (ISR). Nesse caso, o jitter esperado deve incluir os seguintes valores:
				/// MFCLOCK_JITTER_ISR -> Jitter devido ao carimbo de hora durante ISR do driver de dispositivo.
				/// MFCLOCK_JITTER_DPC -> Jitter devido ao carimbo de hora durante o processamento de chamada de procedimento diferido (DPC).
				/// MFCLOCK_JITTER_PASSIVE -> Jitter devido a queda para a execução do thread normal antes do carimbo de hora.
				///</summary>
				UInt32 dwClockJitter;

			};

			/// <summary>
			/// (BITMAPINFOHEADER) - A estrtura contém informações sobre as dimensões e o formato de cores de um bitmap (DIB) independente do dispositivo.
			/// </summary>
			public ref struct CA_BITMAPINFOHEADER
			{
				/// <summary>
				/// O número de bytes requeridos pela estrutura.
				///</summary>
				UInt32 biSize;

				/// <summary>
				/// A largura do bitmap, em pixels.
				/// Se biCompression for BI_JPEG ou BI_PNG, o membro biWidth especificará a largura do arquivo de imagem JPEG ou PNG descompactado, respectivamente.
				///</summary>
				Int32 biWidth;

				/// <summary>
				/// A altura do bitmap, em pixels. Se biHeight for positivo, o bitmap será um DIB ascendente e sua origem será o canto inferior esquerdo. Se biHeight for 
				/// negativo, o bitmap será um DIB de cima para baixo e sua origem será o canto superior esquerdo.
				/// Se biHeight for negativo, indicando um DIB de cima para baixo, o biCompression deve ser BI_RGB ou BI_BITFIELDS .DIBs descendentes não podem ser compactados.
				/// Se biCompression for BI_JPEG ou BI_PNG, o membro biHeight especificará a altura do arquivo de imagem JPEG ou PNG descompactado, respectivamente.
				///</summary>
				Int32 biHeight;

				/// <summary>
				/// O número de planos para o dispositivo de destino. Este valor deve ser definido como 1.
				///</summary>
				Int16 biPlanes;

				/// <summary>
				/// O número de bits por pixel. O membro biBitCount da estrutura BITMAPINFOHEADER determina o número de bits que definem cada pixel e o número máximo de cores no bitmap. 
				/// Este membro deve ser um dos seguintes valores:
				/// (0 - 1 - 4 - 8 - 16 - 24 - 32).
				/// Veja os segifcados de vada valor na url: docs.microsoft.com/en-us/previous-versions/dd183376(v=vs.85)
				///</summary>
				Int16 biBitCount;

				/// <summary>
				/// O tipo de compactação para um bitmap de baixo para cima compactado (DIBs de cima para baixo não podem ser compactados). 
				/// Esse membro pode ser um dos seguintes valores.
				/// (BI_RGB - BI_RLE8 - BI_RLE4 - BI_BITFILEDS - BI_JPEG - BI_PNG).
				/// Veja os significados de vada valor na url: docs.microsoft.com/en-us/previous-versions/dd183376(v=vs.85)
				/// </summary>
				UInt32 biCompression;

				/// <summary>
				/// O tamanho, em bytes, da imagem. Isso pode ser definido como zero para os bitmaps BI_RGB.
				/// Se biCompression for BI_JPEG ou BI_PNG, biSizeImage indicará o tamanho do buffer de imagem JPEG ou PNG, respectivamente.
				///</summary>
				UInt32 biSizeImage;

				/// <summary>
				/// A resolução horizontal, em pixels por metro, do dispositivo de destino para o bitmap. Um aplicativo pode usar esse valor para selecionar um bitmap de um grupo de 
				/// recursos que melhor corresponda às características do dispositivo atual.
				///</summary>
				Int32 biXPelsPerMeter;

				/// <summary>
				/// A resolução vertical, em pixels por metro, do dispositivo de destino para o bitmap.
				///</summary>
				Int32 biYPelsPerMeter;

				/// <summary>
				/// O número de índices de cores na tabela de cores que são realmente usados pelo bitmap. Se esse valor for zero, o bitmap usará o número máximo de cores correspondente ao valor 
				/// do membro biBitCount para o modo de compactação especificado por biCompression.
				/// Se biClrUsed for diferente de zero e o membro biBitCount for menor que 16, o membro biClrUsed especificará o número real de cores acessadas pelo mecanismo de elementos 
				/// gráficos ou pelo driver de dispositivo. Se biBitCount tiver 16 ou mais, o membro biClrUsed especificará o tamanho da tabela de cores usada para otimizar o desempenho das paletas de cores do sistema. 
				/// Se biBitCount for igual a 16 ou 32, a paleta de cores ideal será iniciada imediatamente após as três máscaras UInt32 .
				/// Quando a matriz de bitmap segue imediatamente a estrutura BITMAPINFO , é um bitmap compactado. Bitmaps compactados são referenciados por um único ponteiro. Os bitmaps compactados exigem que o membro 
				/// biClrUsed seja zero ou o tamanho real da tabela de cores.
				///</summary>
				UInt32 biClrUsed;

				/// <summary>
				/// O número de índices de cores necessários para exibir o bitmap. Se esse valor for zero, todas as cores serão necessárias.
				///</summary>
				UInt32 biClrImportant;

			};

			/// <summary>
			/// Estrtura que contém o Size de uma vídeo ou imagem.
			/// A estrutura pode representa a taxa de proporção do vídeo também.
			/// </summary>
			public ref struct CA_SIZE
			{
				/// <summary>
				/// Contém o valor em Y.
				///</summary>
				UInt32 SZ_Y;

				/// <summary>
				/// Contém o valor em X.
				///</summary>
				UInt32 SZ_X;
			};

			/// <summary>
			/// (MFVideoNormalizedRect) - Define um retângulo normalizado, que é usado para especificar subretângulos em um retângulo de vídeo. Quando um retângulo N 
			/// é normalizado em relação a algum outro retângulo R, isso significa o seguinte:
			/// 1) A coordenada (0,0, 0,0) em N é mapeada para o canto superior esquerdo de R.
			/// 2) A coordenada (1,0, 1,0) em N é mapeada para o canto inferior direito de R.
			/// Todas as coordenadas de N que caem fora do intervalo [0... 1] são mapeadas para posições fora do retângulo R. Um retângulo normalizado
			/// pode ser usado para especificar uma região dentro de um retângulo de vídeo sem saber a resolução ou até mesmo a taxa de proporção do vídeo
			///  Por exemplo, o quadrante superior esquerdo é definido como {0,0, 0,0, 0,5, 0,5}.
			/// </summary>
			public ref struct CA_MFVideoNormalizedRect
			{
				/// <summary>
				/// A coordenada X do canto (Superior Esquerdo) do retângulo.
				///</summary>
				float left;

				/// <summary>
				/// A coordenada X do canto (Inferior Direito) do retângulo.
				///</summary>
				float right;

				/// <summary>
				/// A coordenada Y do canto (Superior Esquerdo) do retângulo.
				///</summary>
				float top;

				/// <summary>
				/// A coordenada Y do canto (Inferior Direito) do retângulo.
				///</summary>
				float bottom;
			};

			/// <summary>
			/// (PROPERTYKEY) - Especifica o identificador de FMTID / PID que identifica programaticamente uma propriedade.
			/// </summary>
			public ref struct CA_PROPERTYKEY
			{
				/// <summary>
				/// Um GUID exclusivo para a propriedade.
				///</summary>
				String^ GUIDProp;

				/// <summary>
				/// Um identificador de propriedade (PID). Este parâmetro não é usado como em SHCOLUMNID . Recomenda-se que você defina esse valor como PID_FIRST_USABLE. 
				/// Qualquer valor maior ou igual a 2 é aceitável.
				/// ATENCÂO: Valores de 0 e 1 são reservados e não devem ser usados.
				///</summary>
				UInt32 PID;
			};

			/// <summary>
			/// (_LUID)(FALTA DOCUMENTAR) - O identificador localmente original (LUID) é um valor de 64 bits garantido para ser único apenas no sistema em que foi gerado. A singularidade de um LUID é garantida apenas até que o sistema seja reiniciado.
			/// Um LUID não é para manipulação direta. Os motoristas devem usar rotinas e estruturas de suporte para manipular os valores do LUID.
			/// </summary>
			public ref struct CA_LUID
			{
				UInt32  LowPart;
				Int32   HighPart;
			};

			/// <summary>
			/// (MF_BYTE_STREAM_CACHE_RANGE) - Especifica uma gama de bytes.
			/// </summary>
			public ref struct CA_MF_BYTE_STREAM_CACHE_RANGE
			{
				/// <summary>
				/// O offset, em bytes, do início do intervalo.
				/// </summary>
				Int64 qwStartOffset;

				/// <summary>
				/// O offset, em bytes, do fim do intervalo.
				/// </summary>
				Int64 qwEndOffset;
			};

			/// <summary>
			/// (MF_LEAKY_BUCKET_PAIR) - Especifica os requisitos de buffering de um arquivo.
			/// Esta estrutura descreve os requisitos de buffering para conteúdo codificado na taxa de bits especificada no dwBitrate. O membro msBufferWindow indica quantos dados devem ser bufferados antes de iniciar a reprodução. 
			/// O tamanho do buffer em bytes é msBufferWinow×dwBitrate / 8000.
			/// </summary>
			public ref struct CA_MF_LEAKY_BUCKET_PAIR
			{
				/// <summary>
				/// Taxa de bits, em bits por segundo.
				/// </summary>
				UInt32 dwBitrate;

				/// <summary>
				/// Tamanho do buffer window, em milissegundos.
				/// </summary>
				UInt32 msBufferWindow;
			};

			/// <summary>
			/// (MFBYTESTREAM_BUFFERING_PARAMS)(FALTA DOCUMENTAR) - Especifica os parâmetros de buffering para um fluxo de byte de rede.
			/// </summary>
			public ref struct CA_MFBYTESTREAM_BUFFERING_PARAMS
			{
				UInt64                                 cbTotalFileSize;
				UInt64                                 cbPlayableDataSize;
				cli::array<CA_MF_LEAKY_BUCKET_PAIR^>^  prgBuckets;
				UInt32                                  cBuckets;
				UInt64                                 qwNetBufferingTime;
				UInt64                                 qwExtraBufferingTimeDuringSeek;
				UInt64                                 qwPlayDuration;
				float                                  dRate;
			};

			/// <summary>
			/// (D3D11_COUNTER_DESC) - Descreve UM CONTADOR.
			/// </summary>
			public ref struct CA_D3D11_DESC_CONTADOR
			{
				/// <summary>
				/// O tipo do contador.
				/// </summary>
				Enumeracoes::CA_D3D11_CONTADOR ContadorType;

				/// <summary>
				/// Reservado.
				/// </summary>
				UInt32 MiscFlags;
			};

			/// <summary>
			/// (D3D11_COUNTER_INFO) - Informações sobre recursos de contador de desempenho da placa de vídeo.
			/// </summary>
			public ref struct CA_D3D11_INFO_CONTADOR
			{
				/// <summary>
				/// ID do maior contador dependente do dispositivo que o dispositivo suporta. Se não houver suporte, esse valor será 0. Caso contrário será maior ou igual a D3D11_COUNTER_DEVICE_DEPENDENT_0. 
				/// Consulte D3D11_COUNTER.
				/// </summary>
				Enumeracoes::CA_D3D11_CONTADOR IDMaiorContadorDependente;

				/// <summary>
				/// Número de contadores que podem ser suportados simultaneamente.
				/// </summary>
				UInt32 NumeroContadoresSimultaneos;

				/// <summary>
				/// Número de unidades paralelas detectáveis que o contador é capaz de discernir. Os valores são 1 ~ 4. Use NumeroUnidadesParalelasDetectaveis para interpretar os valores dos contadores de VERTEX_PROCESSING, 
				/// GEOMETRY_PROCESSING, PIXEL_PROCESSING e OTHER_GPU_PROCESSING.
				/// </summary>
				Byte NumeroUnidadesParalelasDetectaveis; //UINT8
			};

			/// <summary>
			/// (D3D11_FEATURE_DATA_THREADING) - Descreve os recursos de vários segmentos que são suportados pelo driver de gráficos atuais.
			/// </summary>
			public ref struct CA_D3D11_FEATURE_DATA_THREADING
			{
				/// <summary>
				/// TRUE significa que recursos podem ser criados simultaneamente em vários segmentos enquanto desenho; FALSE significa que a presença de sincronização grossa impedirá a simultaneidade.
				/// </summary>
				Boolean DriverConcurrentCreates;

				/// <summary>
				/// TRUE significa comando listas são suportadas pelo driver atual; Falso significa que a API irá emular contextos diferidos e comando lista com software.
				/// </summary>
				Boolean DriverCommandLists;

				/// <summary>
				/// Contém o tamanho da estrutura nativa.
				/// </summary>
				UInt32 TamanhoEstrutura;
			};

			/// <summary>
			/// (D3D11_PACKED_MIP_DESC)(FALTA DOCUMENTAR) - Descreve a estrutura de Tile de um recurso lado a lado com mipmaps.
			/// </summary>
			public ref struct CA_D3D11_PACKED_MIP_DESC
			{
				/// <summary>
				/// 
				/// </summary>
				Byte NumStandardMips;
				/// <summary>
				/// 
				/// </summary>
				Byte NumPackedMips;
				/// <summary>
				/// 
				/// </summary>
				UInt32  NumTilesForPackedMips;
				/// <summary>
				/// 
				/// </summary>
				UInt32  StartTileIndexInOverallResource;
			};

			/// <summary>
			/// (D3D11_PACKED_MIP_DESC)(FALTA DOCUMENTAR) - Descreve a estrutura de Tile de um recurso lado a lado com mipmaps.
			/// </summary>
			public ref struct CA_D3D11_TILE_SHAPE
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32 WidthInTexels;
				/// <summary>
				/// 
				/// </summary>
				UInt32 HeightInTexels;
				/// <summary>
				/// 
				/// </summary>
				UInt32 DepthInTexels;
			};

			/// <summary>
			/// (D3D11_SUBRESOURCE_TILING)(FALTA DOCUMENTAR) - Descreve 
			/// </summary>
			public ref struct CA_D3D11_SUBRESOURCE_TILING
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32   WidthInTiles;
				/// <summary>
				/// 
				/// </summary>
				UInt16 HeightInTiles;
				/// <summary>
				/// 
				/// </summary>
				UInt16 DepthInTiles;
				/// <summary>
				/// 
				/// </summary>
				UInt32   StartTileIndexInOverallResource;
			};

			/// <summary>
			/// (D3D11_RENDER_TARGET_BLEND_DESC) -Descreve o estado de combinação para um destino de processamento.
			/// </summary>
			public ref struct CA_D3D11_RENDER_TARGET_BLEND_DESC
			{
				/// <summary>
				/// (BlendEnable) - Ativar (ou desativar) mistura.
				/// </summary>
				Boolean HabilitarMistura;

				/// <summary>
				/// (SrcBlend) - Esta mistura de opção especifica a operação a ser executada no valor RGB que produz o sombreador de pixel. O membro BlendOp define como combinar as 
				/// operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND MisturaOrigem;
				/// <summary>
				/// (DestBlend) - Esta mistura de opção especifica a operação a ser executada no valor RGB atual no destino de processamento. O membro BlendOp define como combinar as 
				/// operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND MisturaDestino;
				/// <summary>
				/// (BlendOp) - Esta mistura de operação define como combinar as operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND_OP DefMisturasOp;
				/// <summary>
				/// (SrcBlendAlpha) - Esta mistura de opção especifica a operação a ser executada no valor alfa que produz o sombreador de pixel. Opções de mistura que terminam em _COLOR não 
				/// são permitidas. O membro BlendOpAlpha define como combinar as operações de SrcBlendAlpha e DestBlendAlpha.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND OrigemOperaçõesMisturaValorAlfa;
				/// <summary>
				/// (DestBlendAlpha) - Esta mistura de opção especifica a operação a ser executada no atual valor alfa o destino de processamento. Opções de mistura que terminam em _COLOR não 
				/// são permitidas. O membro BlendOpAlpha define como combinar as operações de SrcBlendAlpha e DestBlendAlpha.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND DestinoOperaçõesMisturaAtualAlfa;
				/// <summary>
				/// (BlendOpAlpha) - Esta mistura de operação define como combinar as operações de SrcBlendAlpha e DestBlendAlpha .
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND_OP DefMisturasOpAlfa;
				/// <summary>
				/// (RenderTargetWriteMask) - Uma máscara de gravação.
				/// </summary>
				Byte MascaraGravação;
			};

			/// <summary>
			/// (D3D11_RENDER_TARGET_BLEND_DESC1) -Descreve o estado de combinação para um destino de processamento.
			/// </summary>
			public ref struct CA_D3D11_RENDER_TARGET_BLEND_DESC1
			{
				/// <summary>
				/// (BlendEnable) - Ativar (ou desativar) mistura.
				/// </summary>
				Boolean HabilitarMistura;

				/// <summary>
				/// (LogicOpEnable) - Ativar (ou desativar) uma operação logica.
				/// </summary>
				Boolean HabilitarOperacaoLogica;

				/// <summary>
				/// (SrcBlend) - Esta mistura de opção especifica a operação a ser executada no valor RGB que produz o sombreador de pixel. O membro BlendOp define como combinar as 
				/// operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND MisturaOrigem;
				/// <summary>
				/// (DestBlend) - Esta mistura de opção especifica a operação a ser executada no valor RGB atual no destino de processamento. O membro BlendOp define como combinar as 
				/// operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND MisturaDestino;
				/// <summary>
				/// (BlendOp) - Esta mistura de operação define como combinar as operações de SrcBlend e DestBlend.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND_OP DefMisturasOp;
				/// <summary>
				/// (SrcBlendAlpha) - Esta mistura de opção especifica a operação a ser executada no valor alfa que produz o sombreador de pixel. Opções de mistura que terminam em _COLOR não 
				/// são permitidas. O membro BlendOpAlpha define como combinar as operações de SrcBlendAlpha e DestBlendAlpha.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND OrigemOperaçõesMisturaValorAlfa;
				/// <summary>
				/// (DestBlendAlpha) - Esta mistura de opção especifica a operação a ser executada no atual valor alfa o destino de processamento. Opções de mistura que terminam em _COLOR não 
				/// são permitidas. O membro BlendOpAlpha define como combinar as operações de SrcBlendAlpha e DestBlendAlpha.
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND DestinoOperaçõesMisturaAtualAlfa;
				/// <summary>
				/// (BlendOpAlpha) - Esta mistura de operação define como combinar as operações de SrcBlendAlpha e DestBlendAlpha .
				/// </summary>
				Enumeracoes::CA_D3D11_BLEND_OP DefMisturasOpAlfa;
				/// <summary>
				/// (LogicOp) - Um valor CA_D3D11_LOGIC_OP que especifica a operação lógica para configurar para o alvo de renderização.
				/// </summary>
				Enumeracoes::CA_D3D11_LOGIC_OP OpLogica;
				/// <summary>
				/// (RenderTargetWriteMask) - Uma máscara de gravação.
				/// </summary>
				Byte MascaraGravação;
			};

			/// <summary>
			/// (D3D11_BLEND_DESC) - Descreve o estado de combinação que você usar em uma chamada para ICarenD3D11Device::CreateBlendState para criar um objeto de estado da 
			/// mistura.
			/// </summary>
			public ref struct CA_D3D11_BLEND_DESC
			{
				/// <summary>
				/// (AlphaToCoverageEnable) - Especifica se deve usar alfa-para-cobertura como uma técnica multisampling, ao definir um pixel para um destino de processamento. 
				/// Para mais informações sobre o uso de alfa-de-cobertura.
				/// </summary>
				Boolean HabilitarAlphaCobertura;

				/// <summary>
				/// (IndependentBlendEnable) - Especifica se a mistura independente em destinos de processamento simultâneo. Defina como TRUE para habilitar a mistura independente.
				/// Se definido como FALSE, somente os membros do RenderTarget [0] são usados; RenderTarget [1..7] são ignorados.
				/// </summary>
				Boolean BlendIndependente;

				/// <summary>
				/// (RenderTarget) - Uma matriz de CA_D3D11_RENDER_TARGET_BLEND_DESC estruturas que descrevem os Estados de mistura para destinos de processamento; Estas correspondem 
				/// os oito destinos de processamento que podem ser vinculados para o estágio de saída-fusão de uma só vez.
				/// ATENCAO - Você pode ligar até 8(OITO) destinos de processamento para o estágio de saída-fusão de uma só vez.
				/// </summary>
				cli::array<CA_D3D11_RENDER_TARGET_BLEND_DESC^>^ RenderTarget;
			};

			/// <summary>
			/// (D3D11_BLEND_DESC1) - Descreve o estado de combinação que você usar em uma chamada para ICarenD3D11Device::CreateBlendState para criar um objeto de estado da 
			/// mistura.
			/// </summary>
			public ref struct CA_D3D11_BLEND_DESC1
			{
				/// <summary>
				/// (AlphaToCoverageEnable) - Especifica se deve usar alfa-para-cobertura como uma técnica multisampling, ao definir um pixel para um destino de processamento. 
				/// Para mais informações sobre o uso de alfa-de-cobertura.
				/// </summary>
				Boolean HabilitarAlphaCobertura;

				/// <summary>
				/// (IndependentBlendEnable) - Especifica se a mistura independente em destinos de processamento simultâneo. Defina como TRUE para habilitar a mistura independente.
				/// Se definido como FALSE, somente os membros do RenderTarget [0] são usados; RenderTarget [1..7] são ignorados.
				/// </summary>
				Boolean BlendIndependente;

				/// <summary>
				/// (RenderTarget) - Uma matriz de CA_D3D11_RENDER_TARGET_BLEND_DESC1 estruturas que descrevem os Estados de mistura para destinos de processamento; Estas correspondem 
				/// os oito destinos de processamento que podem ser vinculados para o estágio de saída-fusão de uma só vez.
				/// ATENCAO - Você pode ligar até 8(OITO) destinos de processamento para o estágio de saída-fusão de uma só vez.
				/// </summary>
				cli::array<CA_D3D11_RENDER_TARGET_BLEND_DESC1^>^ RenderTarget;
			};

			/// <summary>
			/// (D3D11_SUBRESOURCE_DATA) - Especifica dados para inicializar um sub-recurso.
			/// </summary>
			public ref struct CA_D3D11_SUBRESOURCE_DATA
			{
				/// <summary>
				/// (pSysMem) - Contém um ponteiro para os dados de inicialização.
				/// </summary>
				Object^ SysMemoria;

				/// <summary>
				/// (SysMemPitch) - A distância (em bytes) desde o início de uma linha de uma textura para a próxima linha. Passo de memória do sistema é usado apenas para 2D e dados de textura 3D como é não 
				/// tem nenhum significado para os outros tipos de recurso.Especifica a distância entre o primeiro pixel de uma fatia 2D de uma textura 3D para o primeiro pixel da próxima fatia 2D em que a 
				/// textura no membro (StrideProfundidadeMemoria).
				/// </summary>
				UInt32 StrideMemoria;

				/// <summary>
				/// (SysMemSlicePitch) - A distância (em bytes) do início do nível de profundidade de um para o outro. Sistema - memória - fatia passo só é usado para dados de textura 3D como ele não tem sentido 
				/// para os outros tipos de recurso.
				/// </summary>
				UInt32 StrideProfundidadeMemoria;
			};

			/// <summary>
			/// (D3D11_BUFFER_DESC) - Descreve um recurso de reserva.
			/// </summary>
			public ref struct CA_D3D11_BUFFER_DESC
			{
				/// <summary>
				/// (ByteWidth) - Tamanho do buffer em bytes.
				/// </summary>
				UInt32 TamanhoBuffer;

				/// <summary>
				/// (Usage) - Identifica como o buffer é esperado para ser lidos e gravados. Frequência de atualização é um fator-chave. O valor mais comum é, geralmente, D3D11_USAGE_DEFAULT.
				/// </summary>
				Enumeracoes::CA_D3D11_USAGE DescBufferUse;

				/// <summary>
				/// (BindFlags) - Identifica como o buffer será ligado ao pipeline. Sinalizadores (ver CA_D3D11_BIND_FLAG) podem ser combinados com um OR lógico.
				/// </summary>
				Enumeracoes::CA_D3D11_BIND_FLAG BindFlags;

				/// <summary>
				/// (CPUAccessFlags) - Sinalizadores de acesso CPU (ver CA_D3D11_CPU_ACCESS_FLAG), ou 0 se nenhum acesso de CPU é necessário. Sinalizadores podem ser combinados com um OR lógico.
				/// </summary>
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG CpuAcessoFlags;

				/// <summary>
				/// (MiscFlags) - Diversos sinalizadores (ver CA_D3D11_RESOURCE_MISC_FLAG), ou 0 se não for utilizada. Sinalizadores podem ser combinados com um OR lógico.
				/// </summary>
				Enumeracoes::CA_D3D11_RESOURCE_MISC_FLAG MiscFlags;

				/// <summary>
				/// (StructureByteStride) - O tamanho de cada elemento na estrutura de buffer (em bytes) quando o buffer representa um buffer estruturado.
				/// O valor de tamanho na StructureByteStride deve corresponder ao tamanho do formato que você usar para vistas do buffer. Por exemplo, se você usar um sombreador recurso (SRV) para ler 
				/// um buffer em um sombreador de pixel, o tamanho do formato SRV deve corresponder ao valor de tamanho em StructureByteStride.
				/// </summary>
				UInt32 TamanhoElementosEstruturaBufferStride;
			};

			/// <summary>
			/// (D3D11_DEPTH_STENCILOP_DESC)(FALTA DOCUMENTAR) - Operações estêncil que podem ser executadas com base nos resultados do teste de estêncil..
			/// </summary>
			public ref struct CA_D3D11_DEPTH_STENCILOP_DESC
			{
				Enumeracoes::CA_D3D11_STENCIL_OP StencilFailOp;
				Enumeracoes::CA_D3D11_STENCIL_OP StencilDepthFailOp;
				Enumeracoes::CA_D3D11_STENCIL_OP StencilPassOp;
				Enumeracoes::CA_D3D11_COMPARISON_FUNC StencilFunc;
			};

			/// <summary>
			/// (D3D11_DEPTH_STENCIL_DESC)(FALTA DOCUMENTAR) - Descreve o estado de profundidade-estêncil.
			/// </summary>
			public ref struct CA_D3D11_DEPTH_STENCIL_DESC
			{
				Boolean HabilitarDepth;
				Enumeracoes::CA_D3D11_DEPTH_WRITE_MASK DepthWriterMask;
				Enumeracoes::CA_D3D11_COMPARISON_FUNC DepthFunc;
				Boolean HabilitarStencil;
				Byte StencilReadMask;
				Byte StencilWriteMask;
				CA_D3D11_DEPTH_STENCILOP_DESC^ FrontFace;
				CA_D3D11_DEPTH_STENCILOP_DESC^ BackFace;

			};

			/// <summary>
			/// (D3D11_TEX1D_DSV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 1D acessível a uma exibição de estêncil de profundidade.
			/// </summary>
			public ref struct CA_D3D11_TEX1D_DSV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX2D_DSV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 2D acessível a uma exibição de estêncil de profundidade.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_DSV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX2DMS_DSV) - Especifica o sub-recurso de uma textura 2D multisampled acessível a uma visão de profundidade-estêncil.
			/// [ATENCAO] -> Porque uma textura 2D multisampled contém um subtexture único, não há nada para especificar; Este membro não utilizado está incluído para que essa estrutura será compilado em C.
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_DSV
			{

			};

			/// <summary>
			/// (D3D11_TEX2DMS_ARRAY_DSV )(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D multisampled para uma exibição de estêncil de profundidade.
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_ARRAY_DSV
			{
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX1D_ARRAY_DSV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 1D para usar em uma exibição de estêncil de profundidade.
			/// </summary>
			public ref struct CA_D3D11_TEX1D_ARRAY_DSV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_ARRAY_DSV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D para usar em uma exibição de estêncil de profundidade.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_DSV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_DEPTH_STENCIL_VIEW_DESC)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma textura que são acessíveis a partir de uma visão de profundidade-estêncil.
			/// </summary>
			public ref struct CA_D3D11_DEPTH_STENCIL_VIEW_DESC
			{
				Enumeracoes::CA_DXGI_FORMAT Formato;
				Enumeracoes::CA_D3D11_DSV_DIMENSION ViewDimensao;
				Enumeracoes::CA_D3D11_DSV_FLAG Flags;

				CA_D3D11_TEX1D_DSV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_DSV^ Textura1DArray;
				CA_D3D11_TEX2D_DSV^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_DSV^ Textura2DArray;
				CA_D3D11_TEX2DMS_DSV^ Textura2DMS;
				CA_D3D11_TEX2DMS_ARRAY_DSV^ Textura2DMSArray;
			};

			/// <summary>
			/// (D3D11_SO_DECLARATION_ENTRY)(FALTA DOCUMENTAR) - Descrição de um elemento de vértice em um buffer de vértice em um slot de saída.
			/// </summary>
			public ref struct CA_D3D11_SO_DECLARATION_ENTRY
			{
				UInt32   Stream;
				String^ SemanticName;
				UInt32   SemanticIndex;
				Byte     StartComponent;
				Byte     ComponentCount;
				Byte     OutputSlot;
			};

			/// <summary>
			/// (D3D11_INPUT_ELEMENT_DESC)(FALTA DOCUMENTAR) - Uma descrição de um único elemento para o estágio input-assembler.
			/// </summary>
			public ref struct CA_D3D11_INPUT_ELEMENT_DESC
			{
				String^ SemanticName;
				UInt32                                            SemanticIndex;
				Enumeracoes::CA_DXGI_FORMAT                      Format;
				UInt32                                            InputSlot;
				UInt32                                            AlignedByteOffset;
				Enumeracoes::CA_D3D11_INPUT_CLASSIFICATION        InputSlotClass;
				UInt32                                            InstanceDataStepRate;
			};

			/// <summary>
			/// (D3D11_QUERY_DESC)(FALTA DOCUMENTAR) - Descreve uma consulta.
			/// </summary>
			public ref struct CA_D3D11_QUERY_DESC
			{
				Enumeracoes::CA_D3D11_QUERY Query;

				UInt32 MiscFlags;
			};

			/// <summary>
			/// (D3D11_QUERY_DESC1)(FALTA DOCUMENTAR) - Descreve uma consulta.
			/// </summary>
			public ref struct CA_D3D11_QUERY_DESC1
			{
				Enumeracoes::CA_D3D11_QUERY Query;

				UInt32 MiscFlags;

				Enumeracoes::CA_D3D11_CONTEXT_TYPE ContextType;
			};
			
			/// <summary>
			/// (D3D11_RASTERIZER_DESC)(FALTA DOCUMENTAR) - Descreve o estado do rasterizador.
			/// </summary>
			public ref struct CA_D3D11_RASTERIZER_DESC
			{
				Enumeracoes::CA_D3D11_FILL_MODE FillMode;
				Enumeracoes::CA_D3D11_CULL_MODE CullMode;
				Boolean                         FrontCounterClockwise;
				Int32                           DepthBias;
				float                           DepthBiasClamp;
				float                           SlopeScaledDepthBias;
				Boolean                         DepthClipEnable;
				Boolean                         ScissorEnable;
				Boolean                         MultisampleEnable;
				Boolean                         AntialiasedLineEnable;
			};

			/// <summary>
			/// (D3D11_RASTERIZER_DESC1)(FALTA DOCUMENTAR) - Descreve o estado do rasterizador.
			/// </summary>
			public ref struct CA_D3D11_RASTERIZER_DESC1
			{
				Enumeracoes::CA_D3D11_FILL_MODE FillMode;
				Enumeracoes::CA_D3D11_CULL_MODE CullMode;
				Boolean                         FrontCounterClockwise;
				Int32                           DepthBias;
				float                           DepthBiasClamp;
				float                           SlopeScaledDepthBias;
				Boolean                         DepthClipEnable;
				Boolean                         ScissorEnable;
				Boolean                         MultisampleEnable;
				Boolean                         AntialiasedLineEnable;
				UInt32                          ForcedSampleCount;
			};

			/// <summary>
			/// (D3D11_RASTERIZER_DESC2)(FALTA DOCUMENTAR) - Descreve o estado do rasterizador.
			/// </summary>
			public ref struct CA_D3D11_RASTERIZER_DESC2
			{
				Enumeracoes::CA_D3D11_FILL_MODE FillMode;
				Enumeracoes::CA_D3D11_CULL_MODE CullMode;
				Boolean                         FrontCounterClockwise;
				Int32                           DepthBias;
				float                           DepthBiasClamp;
				float                           SlopeScaledDepthBias;
				Boolean                         DepthClipEnable;
				Boolean                         ScissorEnable;
				Boolean                         MultisampleEnable;
				Boolean                         AntialiasedLineEnable;
				UInt32                          ForcedSampleCount;
				Enumeracoes::CA_D3D11_CONSERVATIVE_RASTERIZATION_MODE ConservativeRaster;
			};

			/// <summary>
			/// (D3D11_BUFFER_RTV)(FALTA DOCUMENTAR) - Especifica os elementos em um recurso de buffer para usar em uma visualização de destino de renderização..
			/// </summary>
			public ref struct CA_D3D11_BUFFER_RTV
			{
				UInt32 FirstElement;
				UInt32 ElementOffset;
				UInt32 NumElements;
				UInt32 ElementWidth;
			};

			/// <summary>
			/// (D3D11_TEX1D_RTV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 1D para usar em uma visualização de destino de renderização..
			/// </summary>
			public ref struct CA_D3D11_TEX1D_RTV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX1D_ARRAY_RTV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 1D para usar em uma exibição de destino de renderização..
			/// </summary>
			public ref struct CA_D3D11_TEX1D_ARRAY_RTV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_RTV)(FALTA DOCUMENTAR) - Especifica o subrecurso de uma textura 2D para usar em uma RenderTargetView.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_RTV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX2D_RTV1)(FALTA DOCUMENTAR) - Descreve o subrecurso de uma textura 2D para usar em uma RenderTargetView.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_RTV1
			{
				UInt32 MipSlice;

				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_TEX2D_ARRAY_RTV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D para usar em uma exibição de destino de renderização..
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_RTV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_ARRAY_RTV1)(FALTA DOCUMENTAR) - Descreve os subrecursos de uma matriz de texturas 2D para usar em uma visão de destino.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_RTV1
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_TEX2DMS_RTV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 2D multisampled para usar em uma exibição de destino de processamento.
			/// [ATENCAO] -> Desde uma textura 2D multisampled contém um sub-recurso único, não há realmente nada para especificar em D3D11_TEX2DMS_RTV.
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_RTV
			{

			};

			/// <summary>
			/// (D3D11_TEX2DMS_ARRAY_RTV)(FALTA DOCUMENTAR) -Especifica os sub-recursos de uma uma matriz de 2D multisampled texturas para usar em uma exibição de destino de processamento. .
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_ARRAY_RTV
			{
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX3D_RTV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma textura 3D para usar em uma exibição de destino de renderização..
			/// </summary>
			public ref struct CA_D3D11_TEX3D_RTV
			{
				UInt32 MipSlice;
				UInt32 FirstWSlice;
				UInt32 WSize;
			};

			/// <summary>
			/// (D3D11_RENDER_TARGET_VIEW_DESC)(FALTA DOCUMENTAR) - Especifica as sub-fontes de um recurso que são acessíveis usando uma exibição de destino de renderização. 
			/// </summary>
			public ref struct CA_D3D11_RENDER_TARGET_VIEW_DESC
			{
				Enumeracoes::CA_DXGI_FORMAT         Formato;
				Enumeracoes::CA_D3D11_RTV_DIMENSION  ViewDimensao;
				CA_D3D11_BUFFER_RTV^ Buffer;
				CA_D3D11_TEX1D_RTV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_RTV^ Textura1DArray;
				CA_D3D11_TEX2D_RTV^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_RTV^ Textura2DArray;
				CA_D3D11_TEX2DMS_RTV^ Textura2DMS;
				CA_D3D11_TEX2DMS_ARRAY_RTV^ Textura2DMSArray;
				CA_D3D11_TEX3D_RTV^ Textura3D;
			};

			/// <summary>
			/// (D3D11_RENDER_TARGET_VIEW_DESC1)(FALTA DOCUMENTAR) - Descreve os subrecursos de um recurso acessível usando uma visão de destino.
			/// </summary>
			public ref struct CA_D3D11_RENDER_TARGET_VIEW_DESC1
			{
				Enumeracoes::CA_DXGI_FORMAT         Formato;
				Enumeracoes::CA_D3D11_RTV_DIMENSION  ViewDimensao;
				CA_D3D11_BUFFER_RTV^ Buffer;
				CA_D3D11_TEX1D_RTV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_RTV^ Textura1DArray;
				CA_D3D11_TEX2D_RTV1^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_RTV1^ Textura2DArray;
				CA_D3D11_TEX2DMS_RTV^ Textura2DMS;
				CA_D3D11_TEX2DMS_ARRAY_RTV^ Textura2DMSArray;
				CA_D3D11_TEX3D_RTV^ Textura3D;
			};

			/// <summary>
			/// (D3D11_SAMPLER_DESC)(FALTA DOCUMENTAR) - Descreve um estado de amostrador. 
			/// </summary>
			public ref struct CA_D3D11_SAMPLER_DESC
			{
				Enumeracoes::CA_D3D11_FILTER               Filter;
				Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE AddressU;
				Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE AddressV;
				Enumeracoes::CA_D3D11_TEXTURE_ADDRESS_MODE AddressW;
				float                                      MipLODBias;
				UInt32                                     MaxAnisotropy;
				Enumeracoes::CA_D3D11_COMPARISON_FUNC      ComparisonFunc;
				cli::array<float>^ BorderColor;
				float                                      MinLOD;
				float                                      MaxLOD;

			};

			/// <summary>
			/// (D3D11_BUFFER_SRV)(FALTA DOCUMENTAR) - Especifica os elementos em um recurso de buffer a ser usado em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_BUFFER_SRV
			{
				UInt32 FirstElement;
				UInt32 ElementOffset;
				UInt32 NumElements;
				UInt32 ElementWidth;
			};

			/// <summary>
			/// (D3D11_TEX1D_SRV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 1D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX1D_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
			};

			/// <summary>
			/// (D3D11_TEX1D_ARRAY_SRV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 1D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX1D_ARRAY_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_SRV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 2D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
			};

			/// <summary>
			/// (D3D11_TEX2D_SRV1)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura 2D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_SRV1
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_BUFFER_SRV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_BUFFER_SRV1)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_SRV1
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_TEX2DMS_SRV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma textura 2D multisampled para usar em uma exibição de sombreador-recurso.
			/// [ATAENCAO] -> Desde uma textura 2D multisampled contém um sub-recurso único, não há realmente nada para especificar em D3D11_TEX2DMS_RTV
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_SRV
			{

			};

			/// <summary>
			/// (D3D11_TEX2DMS_ARRAY_SRV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma matriz de texturas 2D multisampled para usar em uma exibição de recurso de sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEX2DMS_ARRAY_SRV
			{
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX3D_SRV)(FALTA DOCUMENTAR) - Especifica os sub-recursos de uma textura 3D para usar em uma visualização de recursos do sombreador. 
			/// </summary>
			public ref struct CA_D3D11_TEX3D_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
			};

			/// <summary>
			/// (D3D11_TEXCUBE_SRV)(FALTA DOCUMENTAR) - Especifica o sub-recurso de uma textura de cubo para usar em uma visualização de recursos do sombreador. 
			/// </summary>
			public ref struct CA_D3D11_TEXCUBE_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
			};

			/// <summary>
			/// (D3D11_TEXCUBE_ARRAY_SRV)(FALTA DOCUMENTAR) - Especifica as sub-fontes de uma matriz de texturas de cubo para usar em uma visualização de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_TEXCUBE_ARRAY_SRV
			{
				UInt32 MostDetailedMip;
				UInt32 MipLevels;
				UInt32 First2DArrayFace;
				UInt32 NumCubes;
			};

			/// <summary>
			/// (D3D11_BUFFEREX_SRV)(FALTA DOCUMENTAR) - Descreve os elementos em um recurso de buffer bruto a ser usado em uma exibição de recurso de sombreador. 
			/// </summary>
			public ref struct CA_D3D11_BUFFEREX_SRV
			{
				UInt32 FirstElement;
				UInt32 NumElements;
				UInt32 Flags;
			};

			/// <summary>
			/// (D3D11_SHADER_RESOURCE_VIEW_DESC)(FALTA DOCUMENTAR) - Descreve uma exibição de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_SHADER_RESOURCE_VIEW_DESC
			{
				Enumeracoes::CA_DXGI_FORMAT        Formato;
				Enumeracoes::CA_D3D11_SRV_DIMENSION ViewDimensao;

				CA_D3D11_BUFFER_SRV^ Buffer;
				CA_D3D11_TEX1D_SRV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_SRV^ Textura1DArray;
				CA_D3D11_TEX2D_SRV^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_SRV^ Textura2DArray;
				CA_D3D11_TEX2DMS_SRV^ Textura2DMS;
				CA_D3D11_TEX2DMS_ARRAY_SRV^ Textura2DMSArray;
				CA_D3D11_TEX3D_SRV^ Textura3D;
				CA_D3D11_TEXCUBE_SRV^ TexturaCube;
				CA_D3D11_TEXCUBE_ARRAY_SRV^ TexturaCubeArray;
				CA_D3D11_BUFFEREX_SRV^ BufferEx;
			};

			/// <summary>
			/// (D3D11_SHADER_RESOURCE_VIEW_DESC1)(FALTA DOCUMENTAR) - Descreve uma exibição de recursos do sombreador.
			/// </summary>
			public ref struct CA_D3D11_SHADER_RESOURCE_VIEW_DESC1
			{
				Enumeracoes::CA_DXGI_FORMAT        Formato;
				Enumeracoes::CA_D3D11_SRV_DIMENSION ViewDimensao;

				CA_D3D11_BUFFER_SRV^ Buffer;
				CA_D3D11_TEX1D_SRV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_SRV^ Textura1DArray;
				CA_D3D11_TEX2D_SRV1^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_SRV1^ Textura2DArray;
				CA_D3D11_TEX2DMS_SRV^ Textura2DMS;
				CA_D3D11_TEX2DMS_ARRAY_SRV^ Textura2DMSArray;
				CA_D3D11_TEX3D_SRV^ Textura3D;
				CA_D3D11_TEXCUBE_SRV^ TexturaCube;
				CA_D3D11_TEXCUBE_ARRAY_SRV^ TexturaCubeArray;
				CA_D3D11_BUFFEREX_SRV^ BufferEx;
			};

			/// <summary>
			/// (D3D11_TILED_RESOURCE_COORDINATE)(FALTA DOCUMENTAR) - Descreve as coordenadas de um Recurso Tiled.
			/// </summary>
			public ref struct CA_D3D11_TILED_RESOURCE_COORDINATE
			{
				UInt32 X;
				UInt32 Y;
				UInt32 Z;
				UInt32 Subresource;
			};

			/// <summary>
			/// (D3D11_TILE_REGION_SIZE)(FALTA DOCUMENTAR) - Descreve o tamanho de uma região Tiled.
			/// </summary>
			public ref struct CA_D3D11_TILE_REGION_SIZE
			{
				UInt32 NumTiles;
				bool   bUseBox;
				UInt32 Width;
				UInt16 Height;
				UInt16 Depth;
			};

			/// <summary>
			/// (DXGI_SAMPLE_DESC)(FALTA DOCUMENTAR) - Descreve parâmetros de multi-amostragem para um recurso.
			/// </summary>
			public ref struct CA_DXGI_SAMPLE_DESC
			{
				UInt32 Count;
				UInt32 Quality;
			};

			/// <summary>
			/// (DXGI_SURFACE_DESC) - Descreve uma superfície do DXGI.
			/// </summary>
			public ref struct CA_DXGI_SURFACE_DESC
			{
				/// <summary>
				/// (Width) - Um valor descrevendo a largura da superfície.
				///</summary>
				UInt32                           Largura;

				/// <summary>
				/// (Height) - Um valor descrevendo a altura da superfície.
				///</summary>
				UInt32                           Altura;

				/// <summary>
				/// (Format) - Um membro da enumeração CA_DXGI_FORMAT que descreve o formato de superfície.
				///</summary>
				Enumeracoes::CA_DXGI_FORMAT     Formato;

				/// <summary>
				/// (SampleDesc) - Um membro da estrutura CA_DXGI_SAMPLE_DESC que descreve parâmetros de multiamostragem para a 
				/// superfície.
				///</summary>
				CA_DXGI_SAMPLE_DESC^             DescParametrosMultiamostragem;
			};

			/// <summary>
			/// (DXGI_MAPPED_RECT) - Descreve um retângulo mapeado que é usado para acessar uma superfície.
			/// </summary>
			public ref struct CA_DXGI_MAPPED_RECT
			{
				/// <summary>
				/// (Pitch) - Um valor que descreve a largura, em bytes, da superfície.
				///</summary>
				Int32 Largura;

				/// <summary>
				/// (pBits) - Um ponteiro para o buffer que contém a superfice da imagem para leitura ou gravação.
				///</summary>
				Object^ Buffer;
			};

			/// <summary>
			/// (DXGI_QUERY_VIDEO_MEMORY_INFO) - Descreve os parâmetros atuais de orçamento da memória de vídeo.
			/// </summary>
			public ref struct CA_DXGI_QUERY_VIDEO_MEMORY_INFO
			{
				/// <summary>
				/// Especifica o orçamento de memória de vídeo fornecido pelo SISTEMA OPERACIONAL, em bytes, que o aplicativo deve ser alvo. Se o Uso Atual for maior que o 
				/// Orçamento,o aplicativo pode incorrer em gagueira ou penalidades de desempenho devido à atividade de fundo pelo SO para fornecer outros aplicativos com um 
				/// uso justo da memória de vídeo.
				///</summary>
				UInt64 Budget;

				/// <summary>
				/// Especifica o uso atual da memória de vídeo do aplicativo, em bytes.
				///</summary>
				UInt64 CurrentUsage;

				/// <summary>
				/// A quantidade de memória de vídeo, em bytes, que o aplicativo tem disponível para reserva. Para reservar essa memória de vídeo, o aplicativo deve ligar 
				/// para ICarenDXGIAdapter3::SetVideoMemoryReservation.
				///</summary>
				UInt64 AvailableForReservation;

				/// <summary>
				/// A quantidade de memória de vídeo, em bytes, que é reservada pelo aplicativo. O Sistema Operacional usa a reserva como uma dica para determinar o conjunto 
				/// de trabalho mínimo do aplicativo. Os aplicativos devem tentar garantir que seu uso de memória de vídeo possa ser aparado para atender a esse requisito.
				///</summary>
				UInt64 CurrentReservation;
			};

			/// <summary>
			/// (DXGI_HDR_METADATA_HDR10) - Descreve os metadados do HDR10, usados quando o vídeo é comprimido usando codificação de vídeo de alta eficiência (HEVC). Isso é 
			/// usado para descrever os recursos do display usado para dominar o conteúdo e os valores de luminância do conteúdo.
			/// </summary>
			public ref struct CA_DXGI_HDR_METADATA_HDR10
			{
				cli::array<UInt16>^ RedPrimary;
				cli::array<UInt16>^ GreenPrimary;
				cli::array<UInt16>^ BluePrimary;
				cli::array<UInt16>^ WhitePoint;
				UInt32   MaxMasteringLuminance;
				UInt32   MinMasteringLuminance;
				UInt16 MaxContentLightLevel;
				UInt16 MaxFrameAverageLightLevel;
			};

			/// <summary>
			/// (D3D11_TEXTURE1D_DESC)(FALTA DOCUMENTAR) - Descreve uma textura 1D.
			/// </summary>
			public ref struct CA_D3D11_TEXTURE1D_DESC
			{
				UInt32                                 Width;
				UInt32                                 MipLevels;
				UInt32                                 ArraySize;
				Enumeracoes::CA_DXGI_FORMAT           Formato;
				Enumeracoes::CA_D3D11_USAGE            Usage;
				Enumeracoes::CA_D3D11_BIND_FLAG        BindFlags;
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG  CPUAccessFlags;
				UInt32                                 MiscFlags;
			};

			/// <summary>
			/// (D3D11_TEXTURE2D_DESC)(FALTA DOCUMENTAR) - Descreve uma textura 2D.
			/// </summary>
			public ref struct CA_D3D11_TEXTURE2D_DESC
			{
				UInt32                                 Width;
				UInt32                                 Height;
				UInt32                                 MipLevels;
				UInt32                                 ArraySize;
				Enumeracoes::CA_DXGI_FORMAT           Formato;
				CA_DXGI_SAMPLE_DESC^ SampleDesc;
				Enumeracoes::CA_D3D11_USAGE            Usage;
				Enumeracoes::CA_D3D11_BIND_FLAG        BindFlags;
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG  CPUAccessFlags;
				UInt32                                 MiscFlags;
			};

			/// <summary>
			/// (D3D11_TEXTURE2D_DESC1)(FALTA DOCUMENTAR) - Descreve uma textura 2D.
			/// </summary>
			public ref struct CA_D3D11_TEXTURE2D_DESC1
			{
				UInt32                                 Width;
				UInt32                                 Height;
				UInt32                                 MipLevels;
				UInt32                                 ArraySize;
				Enumeracoes::CA_DXGI_FORMAT           Formato;
				CA_DXGI_SAMPLE_DESC^ SampleDesc;
				Enumeracoes::CA_D3D11_USAGE            Usage;
				Enumeracoes::CA_D3D11_BIND_FLAG        BindFlags;
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG  CPUAccessFlags;
				UInt32                                 MiscFlags;
				Enumeracoes::CA_D3D11_TEXTURE_LAYOUT   TextureLayout;
			};

			/// <summary>
			/// (D3D11_TEXTURE3D_DESC)(FALTA DOCUMENTAR) - Descreve uma textura 3D.
			/// </summary>
			public ref struct CA_D3D11_TEXTURE3D_DESC
			{
				UInt32                                       Width;
				UInt32                                       Height;
				UInt32                                       Depth;
				UInt32                                       MipLevels;
				Enumeracoes::CA_DXGI_FORMAT                 Formato;
				Enumeracoes::CA_D3D11_USAGE                  Usage;
				Enumeracoes::CA_D3D11_BIND_FLAG              BindFlags;
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG        CPUAccessFlags;
				UInt32                                       MiscFlags;
			};

			/// <summary>
			/// (D3D11_TEXTURE3D_DESC1)(FALTA DOCUMENTAR) - Descreve uma textura 3D.
			/// </summary>
			public ref struct CA_D3D11_TEXTURE3D_DESC1
			{
				UInt32                                       Width;
				UInt32                                       Height;
				UInt32                                       Depth;
				UInt32                                       MipLevels;
				Enumeracoes::CA_DXGI_FORMAT                 Formato;
				Enumeracoes::CA_D3D11_USAGE                  Usage;
				Enumeracoes::CA_D3D11_BIND_FLAG              BindFlags;
				Enumeracoes::CA_D3D11_CPU_ACCESS_FLAG        CPUAccessFlags;
				UInt32                                       MiscFlags;
				Enumeracoes::CA_D3D11_TEXTURE_LAYOUT         TextureLayout;
			};

			/// <summary>
			/// (D3D11_BUFFER_UAV)(FALTA DOCUMENTAR) - Descreve os elementos em um buffer para usar em uma exibição de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_BUFFER_UAV
			{
				UInt32 FirstElement;
				UInt32 NumElements;
				UInt32 Flags;
			};

			/// <summary>
			/// (D3D11_TEX1D_UAV)(FALTA DOCUMENTAR) - Descreve um recurso de textura 1D de acesso não ordenado. 
			/// </summary>
			public ref struct CA_D3D11_TEX1D_UAV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX1D_ARRAY_UAV)(FALTA DOCUMENTAR) - Descreve uma matriz de recursos de textura 1D de acesso não ordenado. 
			/// </summary>
			public ref struct CA_D3D11_TEX1D_ARRAY_UAV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_UAV)(FALTA DOCUMENTAR) - Descreve um recurso de textura 2D de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_UAV
			{
				UInt32 MipSlice;
			};

			/// <summary>
			/// (D3D11_TEX2D_UAV1)(FALTA DOCUMENTAR) - Descreve um recurso de textura 2D de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_UAV1
			{
				UInt32 MipSlice;
				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_TEX2D_ARRAY_UAV)(FALTA DOCUMENTAR) - Descreve uma matriz de recursos de textura 2D de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_UAV
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
			};

			/// <summary>
			/// (D3D11_TEX2D_ARRAY_UAV1)(FALTA DOCUMENTAR) - Descreve uma série de recursos de textura 2D de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_TEX2D_ARRAY_UAV1
			{
				UInt32 MipSlice;
				UInt32 FirstArraySlice;
				UInt32 ArraySize;
				UInt32 PlaneSlice;
			};

			/// <summary>
			/// (D3D11_TEX3D_UAV)(FALTA DOCUMENTAR) - Descreve um recurso de textura 3D de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_TEX3D_UAV
			{
				UInt32 MipSlice;
				UInt32 FirstWSlice;
				UInt32 WSize;
			};

			/// <summary>
			/// (D3D11_UNORDERED_ACCESS_VIEW_DESC)(FALTA DOCUMENTAR) - Especifica os sub-recursos de um recurso que são acessíveis usando uma exibição de acesso não ordenado.
			/// </summary>
			public ref struct CA_D3D11_UNORDERED_ACCESS_VIEW_DESC
			{
				Enumeracoes::CA_DXGI_FORMAT         Formato;
				Enumeracoes::CA_D3D11_UAV_DIMENSION  ViewDimensao;

				CA_D3D11_BUFFER_UAV^ Buffer;
				CA_D3D11_TEX1D_UAV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_UAV^ Textura1DArray;
				CA_D3D11_TEX2D_UAV^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_UAV^ Textura2DArray;
				CA_D3D11_TEX3D_UAV^ Textura3D;
			};

			/// <summary>
			/// (D3D11_UNORDERED_ACCESS_VIEW_DESC1)(FALTA DOCUMENTAR) - Descreve os subrecursos de um recurso acessível usando uma visão de acesso não ordenada.
			/// </summary>
			public ref struct CA_D3D11_UNORDERED_ACCESS_VIEW_DESC1
			{
				Enumeracoes::CA_DXGI_FORMAT         Formato;
				Enumeracoes::CA_D3D11_UAV_DIMENSION  ViewDimensao;

				CA_D3D11_BUFFER_UAV^ Buffer;
				CA_D3D11_TEX1D_UAV^ Textura1D;
				CA_D3D11_TEX1D_ARRAY_UAV^ Textura1DArray;
				CA_D3D11_TEX2D_UAV1^ Textura2D;
				CA_D3D11_TEX2D_ARRAY_UAV1^ Textura2DArray;
				CA_D3D11_TEX3D_UAV^ Textura3D;
			};
			
			/// <summary>
			/// (D3D11_BOX)(FALTA DOCUMENTAR) - Define uma caixa 3D.
			/// Os valores para a DIREITA, INFERIOR e VOLTA são cada um pixel ultrapassou o fim dos pixels que são incluídos na região da caixa. Ou seja, os valores para a ESQUERDA, SUPERIOR e FRONTAL são incluídos na região
			/// enquanto os valores para a DIREITA, PARTE INFERIOR da caixa e VOLTA são excluídos da região de caixa. Por exemplo, para uma caixa que é um pixel de LARGURA, (DIREITA - ESQUERDA) = = 1; a região de caixa 
			/// inclui o pixel ESQUERDO mas NAO o pixel DIREITO.
			/// </summary>
			public ref struct CA_D3D11_BOX
			{
				UInt32 left;

				UInt32 top;

				UInt32 front;

				UInt32 right;

				UInt32 bottom;

				UInt32 back;
			};

			/// <summary>
			/// (D3D11_CLASS_INSTANCE_DESC) - Descreve uma instância da classe HLSL.
			/// </summary>
			public ref struct CA_D3D11_CLASS_INSTANCE_DESC
			{
				/// <summary>
				/// (InstanceId) - O ID da instância de uma classe HLSL; o valor padrão é 0.
				/// </summary>
				UInt32 IDInstancia;

				/// <summary>
				/// (InstanceIndex) - O índice da instância de uma classe HLSL; o valor padrão é 0. 
				/// </summary>
				UInt32 IndiceInstancia;

				/// <summary>
				/// (TypeId) - O Tipo do ID de uma classe HLSL; o valor padrão é 0.
				/// </summary>
				UInt32 TipoID;

				/// <summary>
				/// (ConstantBuffer) - Descreve o buffer constante associado a uma classe HLSL; o valor padrão é 0.
				/// </summary>
				UInt32 BufferConstante;

				/// <summary>
				/// (BaseConstantBufferOffset) - O deslocamento de buffer constante de base associado a uma classe HLSL; o valor padrão é 0.
				/// </summary>
				UInt32 DeslocamentoBaseBufferConstante;

				/// <summary>
				/// (BaseTexture) - A textura base associada a uma classe HLSL; o valor padrão é 127.
				/// </summary>
				UInt32 TexturaBase;

				/// <summary>
				/// (BaseSampler) - O amostrador de base associado a uma classe HLSL; o valor padrão é 15.
				/// </summary>
				UInt32 AmostradorBase;

				/// <summary>
				/// (Created) - Verdadeiro se a turma foi criada; O valor padrão é falso.
				/// </summary>
				Boolean Criado;
			};

			/// <summary>
			/// (D3D11_VIEWPORT) - Define as dimensões de uma viewport.
			/// </summary>
			public ref struct CA_D3D11_VIEWPORT
			{
				/// <summary>
				/// (TopLeftX) - X posição do lado esquerdo do visor. Varia entre D3D11_VIEWPORT_BOUNDS_MIN e D3D11_VIEWPORT_BOUNDS_MAX.
				/// </summary>
				float CantoSuperiorEsquerdoX;

				/// <summary>
				/// (TopLeftY) - Posição Y da parte superior do visor. Varia entre D3D11_VIEWPORT_BOUNDS_MIN e D3D11_VIEWPORT_BOUNDS_MAX.
				/// </summary>
				float CantoSuperiorEsquerdoY;

				/// <summary>
				/// (Width) - Largura do viewport.
				/// </summary>
				float Largura;

				/// <summary>
				/// (Height) - Altura da porta de visualização.
				/// </summary>
				float Altura;

				/// <summary>
				/// (MinDepth) - Profundidade mínima da viewport. Varia entre 0 e 1.
				/// </summary>
				float ProfundidadeMinima;

				/// <summary>
				/// (MaxDepth) - Profundidade máxima da viewport. Varia entre 0 e 1.
				/// </summary>
				float ProfundidadeMaxima;
			};

			/// <summary>
			/// (D3D11_MAPPED_SUBRESOURCE) - Fornece acesso a dados sub-recurso.
			/// </summary>
			public ref struct CA_D3D11_MAPPED_SUBRESOURCE
			{
				/// <summary>
				/// (pData) - [Este Objeto deve é um ICarenBuffer] Ponteiro para os dados. Quando ICarenD3D11DeviceContext::Map fornece o ponteiro, o runtime garante que o ponteiro tem um alinhamento específico, 
				/// dependendo dos níveis de recurso a seguir:
				/// Para D3D_FEATURE_LEVEL_10_0 e (SUPERIOR), o ponteiro é alinhado com (16 bytes).
				/// Para (MENOR) que D3D_FEATURE_LEVEL_10_0, o ponteiro é alinhado com (4 bytes).
				/// </summary>
				Object^ Param_BufferDados;

				/// <summary>
				/// (RowPitch) - O campo de linha, ou largura ou físico tamanho (em bytes) dos dados.
				/// </summary>
				UInt32 LinhaPasso;

				/// <summary>
				/// (DepthPitch) - O campo de profundidade, ou largura ou físico tamanho (em bytes) dos dados.
				/// </summary>
				UInt32 ProfundidadePasso;
			};

			/// <summary>
			/// (WAVEFORMATEX) - A estrutura define o formato de dados de áudio de forma de onda. Somente as informações de formato comuns a todos os formatos de dados de forma de onda-áudio estão 
			/// incluídas nessa estrutura. Para formatos que exigem informações adicionais, essa estrutura é incluída como o primeiro membro em outra estrutura, juntamente com as informações adicionais.
			/// Os formatos que oferecem suporte a mais de dois canais ou tamanhos de amostra de mais de 16 bits podem ser descritos em uma estrutura CA_WAVEFORMATEXEXTENSIBLE, que inclui a estrutura CA_WAVEFORMATEX.
			/// </summary>
			public ref struct CA_WAVEFORMATEX
			{
				/// <summary>
				/// O formato do áudio. Esse essa estrutura estiver dentro de uma (CA_WAVEFORMATEXEXTENSIBLE) esse valor é igual a WAVE_FORMAT_EXTENSIBLE.
				/// </summary>
				UInt16 wFormatTag;

				/// <summary>
				///  A quantidade de canais nos dados de áudio. Áudio Mono utiliza 1 canal, áudio estereo utiliza 2 canais.
				/// </summary>
				UInt16 nChannels;

				/// <summary>
				/// Quantidade de amostras por segundo, taxa de amostragem(Hertz). os valores comuns para ‎‎nSamplesPerSec‎‎ são de 8,0 kHz, 11.025 kHz, 22,05 kHz e 44,1 kHz.
				/// </summary>
				UInt32 nSamplesPerSec;

				/// <summary>
				///  ‎Taxa média de transferência de dados necessária, em bytes por segundo, para a tag de formato. Se ‎‎o wFormatTag‎‎ estiver WAVE_FORMAT_PCM, ‎‎o nAvgBytesPerSec‎‎ deve ser igual ao produto do ‎‎nSamplesPerSec‎‎ e ‎‎nBlockAlign‎‎. 
				/// Para formatos não PCM, este membro deve ser computado de acordo com a especificação do fabricante da tag de formato.‎
				/// </summary>
				UInt32 nAvgBytesPerSec;

				/// <summary>
				///  ‎Alinhamento de blocos, em bytes. O alinhamento do bloco é a unidade atômica mínima de dados para o tipo de formato ‎‎wFormatTag.‎‎ Se ‎‎o wFormatTag‎‎ estiver WAVE_FORMAT_PCM ou WAVE_FORMAT_EXTENSIBLE, ‎‎o nBlockAlign‎‎ deve ser 
				/// igual ao produto de ‎‎nChannels‎‎ e ‎‎wBitsPerSample‎‎ divididos por 8 (bits por byte). Para formatos não PCM, este membro deve ser computado de acordo com a especificação do fabricante da tag de formato.‎
				/// </summary>
				UInt16 nBlockAlign;

				/// <summary>
				/// ‎Bits por amostra para o tipo de formato ‎‎wFormatTag.‎‎ Se ‎‎o wFormatTag‎‎ estiver WAVE_FORMAT_PCM, então ‎‎o wBitsPerSample‎‎ deve ser igual a 8 ou 16. Para formatos não-PCM, este membro deve ser definido de acordo com a especificação do 
				/// fabricante da tag de formato. Se ‎‎o wFormatTag‎‎ é WAVE_FORMAT_EXTENSIBLE, esse valor pode ser qualquer múltiplo inteiro de 8 e representa o tamanho do recipiente, não necessariamente o tamanho da amostra; por exemplo, um tamanho 
				/// amostral de 20 bits está em um recipiente de 24 bits. Alguns esquemas de compressão não podem definir um valor para ‎‎wBitsPerSample‎‎, para que este membro possa ser 0.‎
				/// </summary>
				UInt16 wBitsPerSample;

				/// <summary>
				/// ‎Tamanho, em bytes, de informações de formato extra anexadas ao final da estrutura ‎‎WAVEFORMATEX.‎‎ Essas informações podem ser usadas por formatos não-PCM para armazenar atributos extras para o ‎‎wFormatTag‎‎. 
				/// Se nenhuma informação extra for necessária pela ‎‎wFormatTag,‎‎este membro deve ser definido como 0. Para WAVE_FORMAT_PCM formatos (e apenas WAVE_FORMAT_PCM formatos), este membro é ignorado. Quando esta estrutura é incluída 
				/// em uma estrutura ‎‎ ‎‎WAVEFORMATEXTENSIBLE,‎‎ ‎‎ esse valor deve ser de pelo menos 22.‎
				/// </summary>
				UInt16 cbSize;

				/// <summary>
				/// Contém o tamanho da estrutura atual.
				/// </summary>
				UINT16 TamanhoEstrutura;
			};

			/// <summary>
			/// (WAVEFORMATEXTENSIBLE) - a estrutura define o formato de dados de forma de onda-áudio para formatos com mais de dois canais ou resoluções de exemplo mais altas do que o permitido por 
			/// CA_WAVEFORMATEX. Ele também pode ser usado para definir qualquer formato que pode ser definido por CA_WAVEFORMATEX.
			/// </summary>
			public ref struct CA_WAVEFORMATEXEXTENSIBLE
			{
				/// <summary>
				/// Representa uma estrutrua CA_WAVEFORMATEX que especifica o formato básico. O membro wFormatTag deve ser WAVE_FORMAT_EXTENSIBLE. O membro do CBSize deve ter pelo menos o tamanho de 22.
				/// </summary>
				CA_WAVEFORMATEX^ Format;

				/// <summary>
				/// Número de amostras(samples) de precisão no sinal. Normalmente igual a CA_WAVEFORMATEX.wBitsPerSample. No entanto, wBitsPerSample é o tamanho do contêiner e deve ser um múltiplo de 8, enquanto wValidBitsPerSample
				/// pode ser qualquer valor que não exceda o tamanho do contêiner. Por exemplo, se o formato usa amostras de 20 bits, o wBitsPerSample deve ter pelo menos 24, mas o wValidBitsPerSample é de 20.
				/// </summary>
				UInt16 wValidBitsPerSample;

				/// <summary>
				/// Número de amostras contidas em um bloco comprimido de dados de áudio. Este valor é usado na estimativa de buffer. Este valor é usado com formatos comprimidos que têm um número fixo de amostras dentro de cada bloco. 
				/// Esse valor pode ser definido como 0 se um número variável de amostras estiver contido em cada bloco de dados de áudio comprimidos. Neste caso, a estimativa de buffer e informações de posição precisam ser obtidas de outras formas.
				/// </summary>
				UInt16 wSamplesPerBlock;

				/// <summary>
				/// (wReserved) - 
				/// </summary>
				UInt16 Reservado;

				/// <summary>
				/// Bitmask especificando a atribuição de canais no fluxo para posições de alto-falantes.
				/// </summary>
				UInt32 dwChannelMask;

				/// <summary>
				/// O subformato dos dados, como KSDATAFORMAT_SUBTYPE_PCM da estrutura GUIDs_CoreAudio_KSDATAFORMAT_SUBTYPES. As informações de subformat são semelhantes às fornecidas pela tag no membro wFormatTag da estrutura CA_WAVEFORMATEX.
				/// </summary>
				String^ SubFormato;

				/// <summary>
				/// Contém o tamanho da estrutura atual.
				/// </summary>
				UINT16 TamanhoEstrutura;
			};

			/// <summary>
			/// (AudioClientProperties) - A estrutura é usada para definir os parâmetros que descrevem as propriedades do fluxo de áudio do cliente.
			/// </summary>
			public ref struct CA_AudioClientProperties
			{
				UInt32                cbSize;
				Boolean               bIsOffload;
				Enumeracoes::CA_AUDIO_STREAM_CATEGORY eCategory;
				Enumeracoes::CA_AUDCLNT_STREAMOPTIONS Options;
			};

			/// <summary>
			/// (_MFTOPONODE_ATTRIBUTE_UPDATE) - Especifica um novo valor de atributo para um nó de topologia.
			/// </summary>
			public ref struct CA_MFTOPONODE_ATTRIBUTE_UPDATE
			{
				/// <summary>
				/// O identificador do nó de topologia para atualizar. Para obter o identificador de um nó de topologia.
				/// </summary>
				UInt64 NodeId;

				/// <summary>
				/// GUID que especifica o atributo para atualizar.
				/// </summary>
				String^ guidAttributeKey;

				/// <summary>
				/// Tipo de atributo, especificado como um membro da enumeração(CA_MF_ATTRIBUTE_TYPE).
				/// </summary>
				Enumeracoes::CA_MF_ATTRIBUTE_TYPE attrType;

				/// <summary>
				/// Valor do atributo (unsigned 32-bit inteiro). Esse membro é usado quando (TipoAtributo) é igual a MF_ATTRIBUTE_UINT32.
				/// </summary>
				UInt32 u32;

				/// <summary>
				/// Valor do atributo (unsigned 32-bit inteiro). Esse membro é usado quando Attrtype é igual a MF_ATTRIBUTE_UINT64.
				/// [ATENCAO] - Devido a um erro na declaração de estrutura, o membro u64 é declarado como um inteiro de 32 bits, não um inteiro 
				/// de 64 bits. Portanto, qualquer valor de 64 bits passado para o método ICarenMFTopologyNodeAttributeEditor::UpdateNodeAttributes 
				/// é truncado para 32 bits.
				/// </summary>
				UInt64 u64;

				/// <summary>
				/// Valor do atributo (ponto flutuante). Esse membro é usado quando (attrType) é igual a MF_ATTRIBUTE_DOUBLE.
				/// </summary>
				double d;
			};

			/// <summary>
			/// (DXGI_RGB)(FALTA DOCUMENTAR) - Representa uma cor RGBA. Os valores devem ir de 0.0 a 1.0
			/// </summary>
			public ref struct CA_DXGI_RGBA
			{
				float Vermelho;

				float Verde;

				float Azul;

				float Alfa;
			};

			/// <summary>
			/// (DXGI_RGB)(FALTA DOCUMENTAR) - Representa uma cor RGB. Os valores devem ir de 0.0 a 1.0
			/// </summary>
			public ref struct CA_DXGI_RGB
			{
				float Vermelho;

				float Verde;

				float Azul;
			};

			/// <summary>
			/// (DXGI_RATIONAL)(FALTA DOCUMENTAR) - Descreve um número racional.
			/// </summary>
			public ref struct CA_DXGI_RATIONAL
			{
				UInt32 Numerador;
				UInt32 Denominador;
			};

			/// <summary>
			/// (DXGI_MODE_DESC)(FALTA DOCUMENTAR) - Descreve um modo de exibição. 
			/// </summary>
			public ref struct CA_DXGI_MODE_DESC
			{
				UINT Width;

				UINT Height;

				CA_DXGI_RATIONAL^ RefreshRate;

				Enumeracoes::CA_DXGI_FORMAT Format;

				Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;

				Enumeracoes::CA_DXGI_MODE_SCALING Scaling;
			};

			/// <summary>
			/// (DXGI_MODE_DESC1)(FALTA DOCUMENTAR) - Descreve um modo de exibição e se o modo de exibição suporta estéreo.
			/// </summary>
			public ref struct CA_DXGI_MODE_DESC1
			{
				UINT Width;

				UINT Height;

				CA_DXGI_RATIONAL^ RefreshRate;

				Enumeracoes::CA_DXGI_FORMAT Format;

				Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;

				Enumeracoes::CA_DXGI_MODE_SCALING Scaling;

				Boolean Stereo;
			};

			/// <summary>
			/// (DXGI_SWAP_CHAIN_DESC)(FALTA DOCUMENTAR) - Descreve uma cadeia de Swap.
			/// </summary>
			public ref struct CA_DXGI_SWAP_CHAIN_DESC
			{
				CA_DXGI_MODE_DESC^ BufferDesc;

				CA_DXGI_SAMPLE_DESC^ SampleDesc;

				Enumeracoes::CA_DXGI_USAGE BufferUsage;

				UInt32 BufferCount;

				IntPtr OutputWindow;

				Boolean Windowed;

				Enumeracoes::CA_DXGI_SWAP_EFFECT SwapEffect;

				Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Flags;
			};

			/// <summary>
			/// (DXGI_SWAP_CHAIN_DESC1)(FALTA DOCUMENTAR) - Descreve uma cadeia de Swap.
			/// </summary>
			public ref struct CA_DXGI_SWAP_CHAIN_DESC1
			{
				UInt32                               Width;
				UInt32                               Height;
				Enumeracoes::CA_DXGI_FORMAT         Format;
				Boolean                              Stereo;
				CA_DXGI_SAMPLE_DESC^ SampleDesc;
				Enumeracoes::CA_DXGI_USAGE           BufferUsage;
				UInt32                               BufferCount;
				Enumeracoes::CA_DXGI_SCALING         Scaling;
				Enumeracoes::CA_DXGI_SWAP_EFFECT     SwapEffect;
				Enumeracoes::CA_DXGI_ALPHA_MODE      AlphaMode;
				Enumeracoes::CA_DXGI_SWAP_CHAIN_FLAG Flags;
			};

			/// <summary>
			/// (DXGI_SWAP_CHAIN_FULLSCREEN_DESC)(FALTA DOCUMENTAR) - Descreve o modo FullScreen de uma cadeia de Swap.
			/// </summary>
			public ref struct CA_DXGI_SWAP_CHAIN_FULLSCREEN_DESC
			{
				CA_DXGI_RATIONAL^ RefreshRate;
				Enumeracoes::CA_DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
				Enumeracoes::CA_DXGI_MODE_SCALING        Scaling;
				Boolean                                  Windowed;
			};

			/// <summary>
			/// (DXGI_FRAME_STATISTICS)(FALTA DOCUMENTAR) - Descreve as estatísticas de tempo e apresentação para um quadro.
			/// </summary>
			public ref struct CA_DXGI_FRAME_STATISTICS
			{
				UInt32          PresentCount;
				UInt32          PresentRefreshCount;
				UInt32          SyncRefreshCount;
				Int64           SyncQPCTime;
				Int64           SyncGPUTime;
			};

			/// <summary>
			/// (DXGI_OUTDUPL_DESC)(FALTA DOCUMENTAR) - A estrutura descreve a dimensão da saída e da superfície que contém a imagem da área de trabalho. 
			/// O formato da imagem desktop é sempre DXGI_FORMAT_B8G8R8A8_UNORM.
			/// </summary>
			public ref struct CA_DXGI_OUTDUPL_DESC
			{
				CA_DXGI_MODE_DESC^     ModeDesc;
				Enumeracoes::CA_DXGI_MODE_ROTATION Rotation;
				bool DesktopImageInSystemMemory;
			};

			/// <summary>
			/// (DXGI_OUTDUPL_MOVE_RECT)(FALTA DOCUMENTAR) - A estrutura descreve o movimento de um retângulo.
			/// </summary>
			public ref struct CA_DXGI_OUTDUPL_MOVE_RECT
			{
				CA_POINT^ SourcePoint;
				CA_RECT^  DestinationRect;
			};

			/// <summary>
			/// (DXGI_OUTDUPL_POINTER_SHAPE_INFO)(FALTA DOCUMENTAR) - A estrutura descreve informações sobre a forma do cursor. 
			/// </summary>
			public ref struct CA_DXGI_OUTDUPL_POINTER_SHAPE_INFO
			{
				Enumeracoes::CA_DXGI_OUTDUPL_POINTER_SHAPE_TYPE  Type;
				UInt32  Width;
				UInt32  Height;
				UInt32  Pitch;
				CA_POINT^ HotSpot;
			};

			/// <summary>
			/// (DXGI_OUTPUT_DESC)(FALTA DOCUMENTAR) - Descreve uma saída ou conexão física entre o adaptador (placa de vídeo) e 
			/// um dispositivo.
			/// </summary>
			public ref struct CA_DXGI_OUTPUT_DESC
			{
				String^ DeviceName;
				CA_RECT^ DesktopCoordinates;
				Boolean                            AttachedToDesktop;
				Enumeracoes::CA_DXGI_MODE_ROTATION Rotation;
				/// <summary>
				/// Uma i
				/// </summary>
				CarenHMONITOR^ Monitor;
			};

			/// <summary>
			/// (DXGI_OUTPUT_DESC1)(FALTA DOCUMENTAR) - Descreve uma saída ou conexão física entre o adaptador (placa de vídeo) e 
			/// um dispositivo, incluindo informações adicionais sobre recursos de cores e tipo de conexão.
			/// </summary>
			public ref struct CA_DXGI_OUTPUT_DESC1
			{
				String^                               DeviceName;
				CA_RECT^                              DesktopCoordinates;
				Boolean                               AttachedToDesktop;
				Enumeracoes::CA_DXGI_MODE_ROTATION    Rotation;
				CarenHMONITOR^                        Monitor;
				UInt32                                BitsPerColor;
				Enumeracoes::CA_DXGI_COLOR_SPACE_TYPE ColorSpace;
				cli::array<float>^                    RedPrimary;
				cli::array<float>^                    GreenPrimary;
				cli::array<float>^                    BluePrimary;
				cli::array<float>^                    WhitePoint;
				float                                 MinLuminance;
				float                                 MaxLuminance;
				float                                 MaxFullFrameLuminance;
			};

			/// <summary>
			/// (DXGI_GAMMA_CONTROL)(FALTA DOCUMENTAR) - Controla as configurações de uma curva gama.
			/// </summary>
			public ref struct CA_DXGI_GAMMA_CONTROL
			{
				CA_DXGI_RGB^ Scale;

				CA_DXGI_RGB^ Offset;

				cli::array<CA_DXGI_RGB^>^ GammaCurve;
			};

			/// <summary>
			/// (DXGI_GAMMA_CONTROL_CAPABILITIES)(FALTA DOCUMENTAR) - Controla os recursos gama de um adaptador.
			/// </summary>
			public ref struct CA_DXGI_GAMMA_CONTROL_CAPABILITIES
			{
				Boolean  ScaleAndOffsetSupported;

				float MaxConvertedValue;

				float MinConvertedValue;

				UInt32  NumGammaControlPoints;

				cli::array<float>^ ControlPointPositions;
			};

			/// <summary>
			/// (DXGI_PRESENT_PARAMETERS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_DXGI_PRESENT_PARAMETERS
			{
				UInt32                 DirtyRectsCount;

				cli::array<CA_RECT^>^ pDirtyRects;

				CA_RECT^ pScrollRect;

				CA_POINT^ pScrollOffset;
			};

			/// <summary>
			/// (DXGI_ADAPTER_DESC)(FALTA DOCUMENTAR) - Descreve um adaptador (ou cartão de vídeo) usando DXGI 1.0.
			/// </summary>
			public ref struct CA_DXGI_ADAPTER_DESC
			{
				String^ Description;
				UInt32   VendorId;
				UInt32   DeviceId;
				UInt32   SubSysId;
				UInt32   Revision;
				UInt64   DedicatedVideoMemory;
				UInt64   DedicatedSystemMemory;
				UInt64   SharedSystemMemory;
				CA_LUID^ AdapterLuid;
			};

			/// <summary>
			/// (DXGI_ADAPTER_DESC1)(FALTA DOCUMENTAR) - Descreve um adaptador (ou cartão de vídeo) usando DXGI 1.1.
			/// </summary>
			public ref struct CA_DXGI_ADAPTER_DESC1
			{
				String^ Description;
				UInt32   VendorId;
				UInt32   DeviceId;
				UInt32   SubSysId;
				UInt32   Revision;
				UInt64   DedicatedVideoMemory;
				UInt64   DedicatedSystemMemory;
				UInt64   SharedSystemMemory;
				CA_LUID^ AdapterLuid;
				Enumeracoes::CA_DXGI_ADAPTER_FLAG Flags;
			};

			/// <summary>
			/// (DXGI_ADAPTER_DESC2)(FALTA DOCUMENTAR) - Descreve um adaptador (ou placa de vídeo) que usa a Microsoft DirectX Graphics Infrastructure (DXGI) 1.2.
			/// </summary>
			public ref struct CA_DXGI_ADAPTER_DESC2
			{
				String^ Description;
				UInt32   VendorId;
				UInt32   DeviceId;
				UInt32   SubSysId;
				UInt32   Revision;
				UInt64   DedicatedVideoMemory;
				UInt64   DedicatedSystemMemory;
				UInt64   SharedSystemMemory;
				CA_LUID^ AdapterLuid;
				Enumeracoes::CA_DXGI_GRAPHICS_PREEMPTION_GRANULARITY GraphicsPreemptionGranularity;
				Enumeracoes::CA_DXGI_COMPUTE_PREEMPTION_GRANULARITY  ComputePreemptionGranularity;
				Enumeracoes::CA_DXGI_ADAPTER_FLAG Flags;
			};

			/// <summary>
			/// (DXGI_ADAPTER_DESC3)(FALTA DOCUMENTAR) - Descreve um adaptador (ou placa de vídeo) que usa a Microsoft DirectX Graphics Infrastructure (DXGI) 1.6.
			/// </summary>
			public ref struct CA_DXGI_ADAPTER_DESC3
			{
				String^ Description;
				UInt32   VendorId;
				UInt32   DeviceId;
				UInt32   SubSysId;
				UInt32   Revision;
				UInt64   DedicatedVideoMemory;
				UInt64   DedicatedSystemMemory;
				UInt64   SharedSystemMemory;
				CA_LUID^ AdapterLuid;
				Enumeracoes::CA_DXGI_GRAPHICS_PREEMPTION_GRANULARITY GraphicsPreemptionGranularity;
				Enumeracoes::CA_DXGI_COMPUTE_PREEMPTION_GRANULARITY  ComputePreemptionGranularity;
				Enumeracoes::CA_DXGI_ADAPTER_FLAG3 Flags;
			};

			/// <summary>
			/// (DXGI_MATRIX_3X2_F) - Representa uma matriz 3x2. Usado com GetMatrixTransform e SetMatrixTransform para indicar a transformação de escala e tradução para cadeias de swap em SwapChainPanel.
			/// </summary>
			public ref struct CA_DXGI_MATRIX_3X2_F
			{
				/// <summary>
				/// O valor na primeira fila e primeira coluna da matriz.
				/// </summary>
				float _11;

				/// <summary>
				/// O valor na primeira fila e segunda coluna da matriz.
				/// </summary>
				float _12;

				/// <summary>
				/// O valor na segunda fila e primeira coluna da matriz.
				/// </summary>
				float _21;

				/// <summary>
				/// O valor na segunda fila e segunda coluna da matriz.
				/// </summary>
				float _22;

				/// <summary>
				/// O valor na terceira fila e primeira coluna da matriz.
				/// </summary>
				float _31;

				/// <summary>
				/// O valor na terceira fila e segunda coluna da matriz.
				/// </summary>
				float _32;
			};

			/// <summary>
			/// (DXGI_OUTDUPL_POINTER_POSITION)(FALTA DOCUMENTAR) - Estrutura responsável por descrever a posição do cursor de hardware.
			/// </summary>
			public ref struct CA_DXGI_OUTDUPL_POINTER_POSITION
			{
				CA_POINT^ Position;
				bool  Visible;
			};

			/// <summary>
			/// (_DXGI_OUTDUPL_FRAME_INFO)(FALTA DOCUMENTAR) - Estrutura responsável por descrever a imagem atual da área de trabalho.
			/// </summary>
			public ref struct CA_DXGI_OUTDUPL_FRAME_INFO
			{
				Int64      LastPresentTime;
				Int64      LastMouseUpdateTime;
				UInt32     AccumulatedFrames;
				bool       RectsCoalesced;
				bool       ProtectedContentMaskedOut;
				CA_DXGI_OUTDUPL_POINTER_POSITION^ PointerPosition;
				UInt32     TotalMetadataBufferSize;
				UInt32     PointerShapeBufferSize;
			};

			/// <summary>
			/// (DXGI_JPEG_AC_HUFFMAN_TABLE)(FALTA DOCUMENTAR) - Estrutura responsável por descrever 
			/// </summary>
			public ref struct CA_DXGI_JPEG_AC_HUFFMAN_TABLE
			{
				cli::array<Byte>^ ArrayCodeCounts;

				cli::array<Byte>^ ArrayCodeValues;
			};

			/// <summary>
			/// (DXGI_JPEG_DC_HUFFMAN_TABLE)(FALTA DOCUMENTAR) - Estrutura responsável por descrever 
			/// </summary>
			public ref struct CA_DXGI_JPEG_DC_HUFFMAN_TABLE
			{
				cli::array<Byte>^ ArrayCodeCounts;

				cli::array<Byte>^ ArrayCodeValues;
			};
			
			/// <summary>
			/// (DXGI_JPEG_QUANTIZATION_TABLE)(FALTA DOCUMENTAR) - Estrutura responsável por descrever 
			/// </summary>
			public ref struct CA_DXGI_JPEG_QUANTIZATION_TABLE
			{
				cli::array<Byte>^ ArrayElementos;
			};




			/// <summary>
			/// (_ACL)(FALTA DOCUMENTAR) - A estrutura do ACL é o cabeçalho de uma lista de controle de acesso(ACL). Um ACL completo consiste em uma estrutura do ACL seguida por uma lista ordenada de zero ou mais entradas de controle de acesso(ACEs).
			/// </summary>
			public ref struct CA_ACL
			{
				/// <summary>
				/// (AclRevision) - 
				/// </summary>
				Byte AclRevision;

				/// <summary>
				/// (Sbz1) - 
				/// </summary>
				Byte Sbz1;

				/// <summary>
				/// (AclSize) - 
				/// </summary>
				UInt16 AclSize;

				/// <summary>
				/// (AceCount) - 
				/// </summary>
				UInt16 AceCount;

				/// <summary>
				/// (Sbz2) - 
				/// </summary>
				UInt16 Sbz2;
			};

			/// <summary>
			/// (SECURITY_DESCRIPTOR)(FALTA DOCUMENTAR) - ontém as informações de segurança associadas a um objeto. Os aplicativos usam essa estrutura para definir e consultar o status de segurança de um objeto.
			/// </summary>
			public ref struct CA_SECURITY_DESCRIPTOR
			{
				/// <summary>
				/// (Revision) - 
				/// </summary>
				Byte        Revisao;

				/// <summary>
				/// (Sbz1) - 
				/// </summary>
				Byte        Sbz1;

				/// <summary>
				/// (Control) - 
				/// </summary>
				UInt16      Control;

				/// <summary>
				/// (Owner) - 
				/// </summary>
				IntPtr Owner;//Deve ser um ponteiro para o objeto.

				/// <summary>
				/// (Group) - 
				/// </summary>
				IntPtr Group; //Deve ser um ponteiro para o objeto.

				/// <summary>
				/// (Sacl) - 
				/// </summary>
				CA_ACL^ Sacl;

				/// <summary>
				/// (Dacl) - 
				/// </summary>
				CA_ACL^ Dacl;
			};

			/// <summary>
			/// (SECURITY_ATTRIBUTES)(FALTA DOCUMENTAR) - Contém o descritor de segurança para um objeto e especifica se o identificador recuperado especificando essa estrutura é hereditário. Esta estrutura fornece configurações de segurança para objetos criados por várias funções.
			/// </summary>
			public ref struct CA_SECURITY_ATTRIBUTES
			{
				/// <summary>
				/// (nLength) - Contém o Size(Tamanho) da estrutura nativa. Esse valor é definido internamente e não precisa ser preenchido.
				/// </summary>
				UInt32  SizeEstrutura;

				/// <summary>
				/// (lpSecurityDescriptor) - 
				/// </summary>
				CA_SECURITY_DESCRIPTOR^ lpSecurityDescriptor;

				/// <summary>
				/// (bInheritHandle) - 
				/// </summary>
				Boolean   bInheritHandle;
			};

			/// <summary>
			/// (_MFT_INPUT_STREAM_INFO) - Contém informações sobre um fluxo de entrada em uma transformação da Media Foundation (MFT).
			/// </summary>
			public ref struct CA_MFT_INPUT_STREAM_INFO
			{

				/// <summary>
				/// (hnsMaxLatency) - O tempo máximo entre uma amostra de entrada e a amostra de saída correspondente, em unidades de 100 nanossegundos. 
				/// Por exemplo, um MFT que tampona duas amostras, cada uma com uma duração de 1 segundo, tem uma latência máxima de dois segundos. Se o 
				/// MFT sempre transforma amostras de entrada diretamente em amostras de saída, sem buffering, a latência é zero.
				/// </summary>
				Int64 LatenciaMaxima;
			
				/// <summary>
				/// (dwFlags) - Bitwise OR de zero ou mais bandeiras do CA_MFT_INPUT_STREAM_INFO_FLAGS enumeração.
				/// </summary>
				UInt32 Flags;

				/// <summary>
				/// (cbSize) - O tamanho mínimo de cada buffer de entrada, em bytes. Se o tamanho for variável ou o MFT não exigir um tamanho específico, 
				/// o valor é zero. Para áudio não compactado, o valor deve ser o tamanho do quadro de áudio, que você pode obter do atributo 
				/// MF_MT_AUDIO_BLOCK_ALIGNMENT no tipo de mídia.
				/// </summary>
				UInt32 Size;

				/// <summary>
				/// (cbMaxLookahead) - Quantidade máxima de dados de entrada, em bytes, que o MFT mantém para realizar o visual. O Lookahead é a ação de 
				/// olhar para frente nos dados antes de processá-los. Esse valor deve ser o pior valor. Se o MFT não mantiver um buffer de olhar para 
				/// frente, o valor é zero.
				/// </summary>
				UInt32 MaxLookahead;

				/// <summary>
				/// (cbAlignment) - O alinhamento de memória necessário para buffers de entrada. Se o MFT não exigir um alinhamento específico, o valor é zero.
				/// </summary>
				UInt32 Alinhamento;
			};

			/// <summary>
			/// (_MFT_OUTPUT_STREAM_INFO) - Contém informações sobre um fluxo de saída em uma transformação da Media Foundation (MFT).
			/// </summary>
			public ref struct CA_MFT_OUTPUT_STREAM_INFO
			{
				/// <summary>
				/// (dwFlags) - Bitwise OR de zero ou mais bandeiras do _MFT_OUTPUT_STREAM_INFO_FLAGS enumeração.
				/// </summary>
				UInt32 Flags;

				/// <summary>
				/// (cbSize) - O tamanho mínimo de cada buffer de entrada, em bytes. Se o tamanho for variável ou o MFT não exigir um tamanho específico, 
				/// o valor é zero. Para áudio não compactado, o valor deve ser o tamanho do quadro de áudio, que você pode obter do atributo 
				/// MF_MT_AUDIO_BLOCK_ALIGNMENT no tipo de mídia.
				/// </summary>
				UInt32 Size;

				/// <summary>
				/// (cbAlignment) - O alinhamento de memória necessário para buffers de saída. Se o MFT não exigir um alinhamento específico, o valor é zero. 
				/// Se o membro Flags contém a bandeira CA_MFT_OUTPUT_STREAM_PROVIDES_SAMPLES, este valor é o alinhamento que o MFT usa internamente quando aloca amostras.
				/// </summary>
				UInt32 Alinhamento;
			};

			/// <summary>
			/// (_MFT_OUTPUT_DATA_BUFFER) - Contém informações sobre um Buffer de saída para uma transformação da Media Foundation. Esta estrutura é usada no método ICarenMFTransform::ProcessOutput.
			/// </summary>
			public ref struct CA_MFT_OUTPUT_DATA_BUFFER
			{
				/// <summary>
				/// (dwStreamID) - Identificador de fluxo de saída. Antes de ligar para o ProcessOutput, coloque este membro em um identificador de fluxo válido.
				/// Exceção: Se o método ICarenMFTransform::GetStreamIDs retorna E_NOTIMPL, o MFT ignora este membro e usa os índices do conjunto (Param_MatrizAmostra) 
				/// no método ProcessOutput como identificadores de fluxo. Em outras palavras, ele usa o primeiro elemento na matriz para o fluxo 0, o segundo para o fluxo 1, 
				/// e assim por diante. Recomenda-se (mas não necessário) que o chamador configure (FluxoID) igual ao índice array neste caso.
				/// </summary>
				UInt32 FluxoID;

				/// <summary>
				/// (pSample)(Representa a interface ICarenMFSample) - Ponteiro para a interface ICarenMFSample. Antes de chamar o ProcessOutput, defina este membro igual a um ponteiro de amostra ou NULO.
				/// </summary>
				Object^ AmostraMidia;

				/// <summary>
				/// (dwStatus) - Antes de ligar para o ProcessOutput, defina este membro para zero. Quando o método retorna, o MFT pode definir o membro igual a um valor 
				/// do CA_MFT_OUTPUT_DATA_BUFFER_FLAGS enumeração. Caso contrário, o MFT deixa este membro igual a zero.
				/// </summary>
				Enumeracoes::CA_MFT_OUTPUT_DATA_BUFFER_FLAGS Status;

				/// <summary>
				/// (pEvents)(Representa a interface ICarenMFCollection) - Antes de ligar para o Processar, defina este membro como NULO. Na saída, o MFT pode definir este membro para um ponteiro de interface de 
				/// memória da ICarenMFCollection válido. O ponteiro representa uma (Coleção) que contém zero ou mais eventos. Para obter cada evento, ligue para a 
			    /// ICarenMFCollection:GetElement e obtenha o ponteiro para ICarenMFMediaEvent. Quando o método ProcessOutput retorna, o chamador é responsável 
				/// por liberar o ponteiro ICarenMFCollection se o ponteiro não for NULO.
				/// </summary>
				Object^ ColecaoEventos;
			};

			/// <summary>
			/// (_MF_TRANSCODE_SINK_INFO)(FALTA DOCUMENTAR) - Contém informações sobre as transmissões de áudio e vídeo para o objeto de ativação do dissipador de transcódigo(Transcode).
			/// </summary>
			public ref struct CA_MF_TRANSCODE_SINK_INFO
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32  dwVideoStreamID;
				/// <summary>
				/// Uma interface ICarenMFMediaType que contém o tipo de mídia para a fluxo de vídeo. Este membro pode ser NULO.
				/// </summary>
				Object^ pVideoMediaType;
				/// <summary>
				/// 
				/// </summary>
				UInt32  dwAudioStreamID;
				/// <summary>
				/// Uma interface ICarenMFMediaType que contém o tipo de mídia para a fluxo de áudio. Este membro pode ser NULO.
				/// </summary>
				Object^ pAudioMediaType;
			};

			/// <summary>
			/// (MFNetCredentialManagerGetParam)(FALTA DOCUMENTAR) - Contém as informações de autenticação para o gerenciador de credenciais.
			/// </summary>
			public ref struct CA_MFNetCredentialManagerGetParam
			{
				long hrOp;
				Boolean fAllowLoggedOnUser;
				Boolean fClearTextPackage;
				String^ pszUrl;
				String^ pszSite;
				String^ pszRealm;
				String^ pszPackage;
				long    nRetries;
			};

			/// <summary>
			/// (MFT_REGISTER_TYPE_INFO)(FALTA DOCUMENTAR) - Contém informações do tipo de mídia(Media Type) para registrar uma transformação da Media Foundation (MFT).
			/// </summary>
			public ref struct CA_MFT_REGISTER_TYPE_INFO
			{
				/// <summary>
				/// Um GUID para o tipo de midia principal. Consulte a estrutura GUIDs_MFAttributes_MAJOR_TYPES
				/// </summary>
				String^ guidMajorType;

				/// <summary>
				/// Um GUID para o subtipo da midia. Consulte as estruturas GUIDs_MF_VIDEO_SUBTYPES e GUIDs_MF_AUDIO_SUBTYPES para obter esse guid.
				/// </summary>
				String^ guidSubtype;
			};

			/// <summary>
			/// (_MFT_REGISTRATION_INFO) - Contém parâmetros para o método ICarenMFLocalMFTRegistration::RegistrarMFTs.
			/// </summary>
			public ref struct CA_MFT_REGISTRATION_INFO
			{
				/// <summary>
				/// CLSID da Media Foundation transform (MFT) para registro.
				/// </summary>
				String^                clsid;

				/// <summary>
				/// GUID que especifica a categoria do MFT. Para obter uma lista de categorias MFT, consulte GUIDs_MFT_CATEGORY.
				/// </summary>
				String^                guidCategory;

				/// <summary>
				/// Bitwise OR de zero ou mais bandeiras da enumeração CA_MFT_ENUM_FLAG.
				/// </summary>
				Enumeracoes::CA_MFT_ENUM_FLAG       uiFlags;

				/// <summary>
				/// Uma string que contém um nome amigavel para o MFT.
				/// </summary>
				String^                pszName;

				/// <summary>
				/// Número de elementos na matriz pInTypes.
				/// </summary>
				UInt32                 cInTypes;

				/// <summary>
				/// Uma matriz de estruturas MFT_REGISTER_TYPE_INFO. Cada membro da matriz especifica um formato de entrada que o MFT suporta. Se este membro for NULO, o membro cInTypes 
				/// deve ser zero.
				/// </summary>
				cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ pInTypes;

				/// <summary>
				/// Número de elementos na matriz pOutTypes.
				/// </summary>
				UInt32                                  cOutTypes;

				/// <summary>
				/// Uma matriz de estruturas MFT_REGISTER_TYPE_INFO. Cada membro da matriz define um formato de saída que o MFT suporta. Se este membro for NULO, o membro cOutTypes deve 
				/// ser zero.
				/// </summary>
				cli::array<CA_MFT_REGISTER_TYPE_INFO^>^ pOutTypes;
			};

			/// <summary>
			/// (_MFARGB) - Descreve um valor de cor ARGB.
			/// </summary>
			public ref struct CA_MFARGB
			{
				/// <summary>
				/// Valor azul.
				/// </summary>
				Byte rgbBlue;

				/// <summary>
				/// Valor verde.
				/// </summary>
				Byte rgbGreen;

				/// <summary>
				/// Valor vermelho.
				/// </summary>
				Byte rgbRed;

				/// <summary>
				/// Valor alfa.
				/// </summary>
				Byte rgbAlpha;
			};




			//Direct2D Estruturas.


			/// <summary> 
			/// (D2D1_PIXEL_FORMAT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_PIXEL_FORMAT
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_DXGI_FORMAT format;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_ALPHA_MODE alphaMode;
			};

			/// <summary> 
			/// (D2D_COLOR_F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D_COLOR_F
			{
				// <summary>
				// 
				// </summary>
				float r;
				// <summary>
				// 
				// </summary>
				float g;
				// <summary>
				// 
				// </summary>
				float b;
				// <summary>
				// 
				// </summary>
				float a;
			};

			/// <summary> 
			/// (D2D1_MATRIX_3X2_F)(FALTA DOCUMENTAR) - 
			/// Utilize a classe Direct2DFunctions para pode criar e gerenciar Matrix.
			/// </summary>
			public ref struct CA_D2D1_MATRIX_3X2_F
			{
				// <summary>
				// 
				// </summary>
				float m11;
				// <summary>
				// 
				// </summary>  
				float m12;
				// <summary>
				// 
				// </summary>  
				float m21;
				// <summary>
				// 
				// </summary>  
				float m22;
				// <summary>
				// 
				// </summary>  
				float dx;
				// <summary>
				// 
				// </summary>  
				float dy;
				// <summary>
			   // 
			   // </summary> 
				float _11;
				// <summary>
				// 
				// </summary>  
				float _12;
				// <summary>
				// 
				// </summary>  
				float _21;
				// <summary>
				// 
				// </summary>  
				float _22;
				// <summary>
				// 
				// </summary>  
				float _31;
				// <summary>
				// 
				// </summary>  
				float _32;
				// <summary>
				// 
				// </summary>  
				cli::array<cli::array<float>^>^ m;

			};

			/// <summary> 
			/// (D2D_MATRIX_4X3_F)(FALTA DOCUMENTAR) - 
			/// Utilize a classe Direct2DFunctions para pode criar e gerenciar Matrix.
			/// </summary>
			public ref struct CA_D2D1_MATRIX_4X3_F
			{
				// <summary>
				// 
				// </summary>
				float _11;
				// <summary>
				// 
				// </summary>  
				float _12;
				// <summary>
				// 
				// </summary>  
				float _13;
				// <summary>
				// 
				// </summary>  
				float _21;
				// <summary>
				// 
				// </summary>  
				float _22;
				// <summary>
				// 
				// </summary>  
				float _23;
				// <summary>
				// 
				// </summary>  
				float _31;
				// <summary>
				// 
				// </summary>  
				float _32;
				// <summary>
				// 
				// </summary>  
				float _33;
				// <summary>
				// 
				// </summary>  
				float _41;
				// <summary>
				// 
				// </summary>  
				float _42;
				// <summary>
				// 
				// </summary>  
				float _43;
				// <summary>
				// 
				// </summary>  
				cli::array<cli::array<float>^>^ m;

			};

			/// <summary> 
			/// (D2D1_MATRIX_4X4_F)(FALTA DOCUMENTAR) - 
			/// Utilize a classe Direct2DFunctions para pode criar e gerenciar Matrix.
			/// </summary>
			public ref struct CA_D2D1_MATRIX_4X4_F
			{
				// <summary>
				// 
				// </summary>
				float _11;
				// <summary>
				// 
				// </summary> 
				float _12;
				// <summary>
				// 
				// </summary>   
				float _13;
				// <summary>
				// 
				// </summary>   
				float _14;
				// <summary>
				// 
				// </summary>   
				float _21;
				// <summary>
				// 
				// </summary>   
				float _22;
				// <summary>
				// 
				// </summary>   
				float _23;
				// <summary>
				// 
				// </summary>   
				float _24;
				// <summary>
				// 
				// </summary>   
				float _31;
				// <summary>
				// 
				// </summary>   
				float _32;
				// <summary>
				// 
				// </summary>   
				float _33;
				// <summary>
				// 
				// </summary>   
				float _34;
				// <summary>
				// 
				// </summary>   
				float _41;
				// <summary>
				// 
				// </summary>   
				float _42;
				// <summary>
				// 
				// </summary>   
				float _43;
				// <summary>
				// 
				// </summary>   
				float _44;
				// <summary>
				// 
				// </summary>  
				cli::array<cli::array<float>^>^ m;
			};

			/// <summary> 
			/// (D2D1_MATRIX_5X4_F)(FALTA DOCUMENTAR) - 
			/// Utilize a classe Direct2DFunctions para pode criar e gerenciar Matrix.
			/// </summary>
			public ref struct CA_D2D1_MATRIX_5X4_F
			{
				// <summary>
				// 
				// </summary>
				float _11;
				// <summary>
				// 
				// </summary
				float _12;
				// <summary>
				// 
				// </summary  
				float _13;
				// <summary>
				// 
				// </summary  
				float _14;
				// <summary>
				// 
				// </summary  
				float _21;
				// <summary>
				// 
				// </summary  
				float _22;
				// <summary>
				// 
				// </summary  
				float _23;
				// <summary>
				// 
				// </summary  
				float _24;
				// <summary>
				// 
				// </summary  
				float _31;
				// <summary>
				// 
				// </summary  
				float _32;
				// <summary>
				// 
				// </summary  
				float _33;
				// <summary>
				// 
				// </summary  
				float _34;
				// <summary>
				// 
				// </summary  
				float _41;
				// <summary>
				// 
				// </summary  
				float _42;
				// <summary>
			   // 
			   // </summary 
				float _43;
				// <summary>
				// 
				// </summary  
				float _44;
				// <summary>
				// 
				// </summary  
				float _51;
				// <summary>
				// 
				// </summary  
				float _52;
				// <summary>
			   // 
			   // </summary 
				float _53;
				// <summary>
			  // 
			  // </summary>
				float _54;
				// <summary>
			   // 
			   // </summary>  
				cli::array<cli::array<float>^>^ m;
			};

			/// <summary> 
			/// (D2D1_POINT_2F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_POINT_2F
			{
				// <summary>
				// 
				// </summary>
				float x;

				// <summary>
				// 
				// </summary>
				float y;

			};

			/// <summary> 
			/// (D2D1_POINT_2L)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_POINT_2L
			{
				// <summary>
				// 
				// </summary>
				Int32 x;

				// <summary>
				// 
				// </summary>
				Int32 y;

			};

			/// <summary> 
			/// (D2D1_POINT_2U)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_POINT_2U
			{
				// <summary>
				// 
				// </summary>
				UInt32 x;

				// <summary>
				// 
				// </summary>
				UInt32 y;
			};

			/// <summary> 
			/// (D2D1_RECT_F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RECT_F
			{
				// <summary>
				// 
				// </summary>
				float left;

				// <summary>
				// 
				// </summary>
				float top;

				// <summary>
				// 
				// </summary>
				float right;

				// <summary>
				// 
				// </summary>
				float bottom;

			};

			/// <summary> 
			/// (D2D1_RECT_L)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RECT_L
			{
				// <summary>
				// 
				// </summary>
				Int32 left;

				// <summary>
				// 
				// </summary>
				Int32 top;

				// <summary>
				// 
				// </summary>
				Int32 right;

				// <summary>
				// 
				// </summary>
				Int32 bottom;
			};

			/// <summary> 
			/// (D2D1_RECT_U)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RECT_U
			{
				// <summary>
				// 
				// </summary>
				UInt32 left;

				// <summary>
				// 
				// </summary>
				UInt32 top;

				// <summary>
				// 
				// </summary>
				UInt32 right;

				// <summary>
				// 
				// </summary>
				UInt32 bottom;
			};

			/// <summary> 
			/// (D2D1_SIZE_F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SIZE_F
			{
				// <summary>
				// 
				// </summary>
				float width;
				// <summary>
				// 
				// </summary>
				float height;
			};

			/// <summary> 
			/// (D2D1_SIZE_U)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SIZE_U
			{
				// <summary>
				// 
				// </summary>
				UInt32 width;

				// <summary>
				// 
				// </summary>
				UInt32 height;

			};

			/// <summary> 
			/// (D2D1_VECTOR_2F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_VECTOR_2F
			{
				// <summary>
				// 
				// </summary>
				float x;

				// <summary>
				// 
				// </summary>
				float y;

			};

			/// <summary> 
			/// (D2D1_VECTOR_3F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_VECTOR_3F
			{
				// <summary>
				// 
				// </summary>
				float x;

				// <summary>
				// 
				// </summary>
				float y;

				// <summary>
				// 
				// </summary>
				float z;

			};

			/// <summary> 
			/// (D2D1_VECTOR_4F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_VECTOR_4F
			{
				// <summary>
				// 
				// </summary>
				float x;

				// <summary>
				// 
				// </summary>
				float y;

				// <summary>
				// 
				// </summary>
				float z;

				// <summary>
				// 
				// </summary>
				float w;

			};

			/// <summary> 
			/// (D2D1_ARC_SEGMENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_ARC_SEGMENT
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point;
				CA_D2D1_SIZE_F^ size;
				float                rotationAngle;
				Enumeracoes::CA_D2D1_SWEEP_DIRECTION sweepDirection;
				Enumeracoes::CA_D2D1_ARC_SIZE        arcSize;
			};

			/// <summary> 
			/// (D2D1_BEZIER_SEGMENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BEZIER_SEGMENT
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point1;

				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point2;

				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point3;
			};

			/// <summary> 
			/// (D2D1_BITMAP_BRUSH_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BITMAP_BRUSH_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE               extendModeX;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE               extendModeY;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BITMAP_INTERPOLATION_MODE interpolationMode;
			};

			/// <summary> 
			/// (D2D1_BITMAP_BRUSH_PROPERTIES1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BITMAP_BRUSH_PROPERTIES1
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE        extendModeX;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE        extendModeY;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_INTERPOLATION_MODE interpolationMode;
			};

			/// <summary> 
			/// (D2D1_BITMAP_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BITMAP_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_PIXEL_FORMAT^ pixelFormat;
				// <summary>
				// 
				// </summary>
				float             dpiX;
				// <summary>
				// 
				// </summary>
				float             dpiY;

			};

			/// <summary> 
			/// (D2D1_BITMAP_PROPERTIES1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BITMAP_PROPERTIES1
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_PIXEL_FORMAT^   pixelFormat;
				// <summary>
				// 
				// </summary>
				float               dpiX;
				// <summary>
				// 
				// </summary>
				float               dpiY;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BITMAP_OPTIONS bitmapOptions;
				// <summary>
				// 
				// </summary>
				Object^ colorContext;
			};

			/// <summary> 
			/// (D2D1_BLEND_DESCRIPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BLEND_DESCRIPTION
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND           sourceBlend;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND           destinationBlend;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND_OPERATION blendOperation;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND           sourceBlendAlpha;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND           destinationBlendAlpha;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BLEND_OPERATION blendOperationAlpha;
				// <summary>
				// Parâmetros para as operações de mistura. A mistura deve usar D2D1_BLEND_BLEND_FACTOR para que isso seja usado.
				// [ATENÇÃO] - ESSE É UM ARRAY QUE TEM UM VALOR MAXIMO E FIXO DE 4.
				// </summary>
				cli::array<float>^ blendFactor;
			};

			/// <summary> 
			/// (D2D1_BRUSH_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_BRUSH_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				float             opacity;

				// <summary>
				// 
				// </summary>
				CA_D2D1_MATRIX_3X2_F^ transform;

			};

			/// <summary> 
			/// (D2D1_COLOR_F)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_COLOR_F
			{
				// <summary>
				// 
				// </summary>
				float r;

				// <summary>
				// 
				// </summary>
				float g;

				// <summary>
				// 
				// </summary>
				float b;

				// <summary>
				// 
				// </summary>
				float a;
			};

			/// <summary> 
			/// (D2D1_CREATION_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_CREATION_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_THREADING_MODE         threadingMode;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_DEBUG_LEVEL            debugLevel;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_DEVICE_CONTEXT_OPTIONS options;
			};

			/// <summary> 
			/// (D2D1_INPUT_ELEMENT_DESC)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_INPUT_ELEMENT_DESC
			{
				// <summary>
				// 
				// </summary>
				String^ semanticName;

				// <summary>
				// 
				// </summary>
				UInt32      semanticIndex;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_DXGI_FORMAT format;

				// <summary>
				// 
				// </summary>
				UInt32      inputSlot;

				// <summary>
				// 
				// </summary>
				UInt32      alignedByteOffset;

			};

			/// <summary> 
			/// (D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				cli::array<Byte>^ shaderBufferWithInputSignature;
				UInt32                        shaderBufferSize;
				cli::array<CA_D2D1_INPUT_ELEMENT_DESC^>^ inputElements;
				UInt32                        elementCount;
				UInt32                        stride;
			};

			/// <summary> 
			/// (D2D1_DRAWING_STATE_DESCRIPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_DRAWING_STATE_DESCRIPTION
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_ANTIALIAS_MODE      antialiasMode;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode;
				// <summary>
				// 
				// </summary>
				UInt64                 tag1;
				// <summary>
				// 
				// </summary>
				UInt64                 tag2;
				// <summary>
				// 
				// </summary>
				CA_D2D1_MATRIX_3X2_F^ transform;
			};

			/// <summary> 
			/// (D2D1_DRAWING_STATE_DESCRIPTION1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_DRAWING_STATE_DESCRIPTION1
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_ANTIALIAS_MODE      antialiasMode;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode;
				// <summary>
				// 
				// </summary>
				UInt64                 tag1;
				// <summary>
				// 
				// </summary>
				UInt64                 tag2;
				// <summary>
				// 
				// </summary>
				CA_D2D1_MATRIX_3X2_F^ transform;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PRIMITIVE_BLEND     primitiveBlend;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_UNIT_MODE           unitMode;

			};

			/// <summary> 
			/// (D2D1_EFFECT_INPUT_DESCRIPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_EFFECT_INPUT_DESCRIPTION
			{
				// <summary>
				// 
				// </summary>
				Object^ effect;

				// <summary>
				// 
				// </summary>
				UInt32 inputIndex;

				// <summary>
				// 
				// </summary>
				CA_D2D1_RECT_F^ inputRectangle;
			};

			/// <summary> 
			/// (D2D1_ELLIPSE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_ELLIPSE
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point;

				// <summary>
				// 
				// </summary>
				float         radiusX;

				// <summary>
				// 
				// </summary>
				float         radiusY;
			};

			/// <summary> 
			/// (D2D1_FACTORY_OPTIONS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_FACTORY_OPTIONS
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_DEBUG_LEVEL debugLevel;

			};

			/// <summary> 
			/// (D2D1_FEATURE_DATA_DOUBLES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_FEATURE_DATA_DOUBLES
			{
				// <summary>
				// 
				// </summary>
				Boolean doublePrecisionFloatShaderOps;
			};

			/// <summary> 
			/// (D2D1_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS)(FALTA DOCUMENTAR) - Descreve o suporte a sombreamento de computação, que é uma opção no nível de recurso D3D10.
			/// </summary>
			public ref struct CA_D2D1_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS
			{
				// <summary>
				// 
				// </summary>
				Boolean computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
			};

			/// <summary> 
			/// (D2D1_GRADIENT_MESH_PATCH)(FALTA DOCUMENTAR) - Representa um patch tensor com 16 pontos de controle, 4 cores de canto e bandeiras de limite. Um ID2D1GradientMesh é composto por 1 ou mais patches de malha gradiente.
			/// </summary>
			public ref struct CA_D2D1_GRADIENT_MESH_PATCH
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point00;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point01;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point02;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point03;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point10;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point11;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point12;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point13;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point20;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point21;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point22;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point23;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point30;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point31;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point32;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point33;
				// <summary>
				// 
				// </summary>
				CA_D2D1_COLOR_F^ color00;
				// <summary>
				// 
				// </summary>
				CA_D2D1_COLOR_F^ color03;
				// <summary>
				// 
				// </summary>
				CA_D2D1_COLOR_F^ color30;
				// <summary>
				// 
				// </summary>
				CA_D2D1_COLOR_F^ color33;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PATCH_EDGE_MODE topEdgeMode;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PATCH_EDGE_MODE leftEdgeMode;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PATCH_EDGE_MODE bottomEdgeMode;
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PATCH_EDGE_MODE rightEdgeMode;

			};

			/// <summary> 
			/// (D2D1_GRADIENT_STOP)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_GRADIENT_STOP
			{
				// <summary>
				// 
				// </summary>
				float        position;

				// <summary>
				// 
				// </summary>
				CA_D2D1_COLOR_F^ color;
			};

			/// <summary> 
			/// (D2D1_HWND_RENDER_TARGET_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_HWND_RENDER_TARGET_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				IntPtr                 hwnd;

				// <summary>
				// 
				// </summary>
				CA_D2D1_SIZE_U^ pixelSize;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PRESENT_OPTIONS presentOptions;

			};

			/// <summary> 
			/// (D2D1_INK_STYLE_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_INK_STYLE_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_INK_NIB_SHAPE nibShape;

				// <summary>
				// 
				// </summary>
				CA_D2D1_MATRIX_3X2_F^ nibTransform;

			};

			/// <summary> 
			/// (D2D1_IMAGE_BRUSH_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_IMAGE_BRUSH_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_RECT_F^ sourceRectangle;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE        extendModeX;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_EXTEND_MODE        extendModeY;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_INTERPOLATION_MODE interpolationMode;
			};

			/// <summary> 
			/// (D2D1_INK_POINT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_INK_POINT
			{
				// <summary>
				// 
				// </summary>
				float x;
				// <summary>
				// 
				// </summary>
				float y;
				// <summary>
				  // 
				  // </summary>
				float radius;
			};

			/// <summary> 
			/// (D2D1_INK_BEZIER_SEGMENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_INK_BEZIER_SEGMENT
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_INK_POINT^ point1;

				// <summary>
				// 
				// </summary>
				CA_D2D1_INK_POINT^ point2;

				// <summary>
				// 
				// </summary>
				CA_D2D1_INK_POINT^ point3;

			};

			/// <summary> 
			/// (D2D1_INPUT_DESCRIPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_INPUT_DESCRIPTION
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_FILTER filter;

				// <summary>
				// 
				// </summary>
				UInt32      levelOfDetailCount;
			};

			/// <summary> 
			/// (D2D1_LAYER_PARAMETERS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_LAYER_PARAMETERS
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_RECT_F^ contentBounds;

				// <summary>
				// 
				// </summary>
				Object^ geometricMask;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_ANTIALIAS_MODE maskAntialiasMode;

				// <summary>
				  // 
				  // </summary>
				CA_D2D1_MATRIX_3X2_F^ maskTransform;

				// <summary>
				  // 
				  // </summary>
				float               opacity;

				// <summary>
				  // 
				  // </summary>
				Object^ opacityBrush;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_LAYER_OPTIONS  layerOptions;
			};

			/// <summary> 
			/// (D2D1_LAYER_PARAMETERS1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_LAYER_PARAMETERS1
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_RECT_F^ contentBounds;
				// <summary>
				// 
				// </summary>
				Object^ geometricMask;
				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_ANTIALIAS_MODE maskAntialiasMode;
				// <summary>
				  // 
				  // </summary>
				CA_D2D1_MATRIX_3X2_F^ maskTransform;
				// <summary>
				  // 
				  // </summary>
				float               opacity;
				// <summary>
				  // 
				  // </summary>
				Object^ opacityBrush;
				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_LAYER_OPTIONS1  layerOptions;

			};

			/// <summary> 
			/// (D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ startPoint;

				// <summary>
			   // 
			   // </summary>
				CA_D2D1_POINT_2F^ endPoint;
			};

			/// <summary> 
			/// (D2D1_MAPPED_RECT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_MAPPED_RECT
			{
				// <summary>
				// 
				// </summary>
				UInt32 pitch;

				// <summary>
				// 
				// </summary>
				Object^ bits;
			};

			/// <summary> 
			/// (D2D1_POINT_DESCRIPTION)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_POINT_DESCRIPTION
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point;
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ unitTangentVector;
				// <summary>
				  // 
				  // </summary>
				UInt32        endSegment;
				// <summary>
				  // 
				  // </summary>
				UInt32        endFigure;
				// <summary>
				  // 
				  // </summary>
				float         lengthToEndSegment;
			};

			/// <summary> 
			/// (D2D1_PRINT_CONTROL_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_PRINT_CONTROL_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_PRINT_FONT_SUBSET_MODE fontSubset;

				// <summary>
			   // 
			   // </summary>
				float                       rasterDPI;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_COLOR_SPACE            colorSpace;
			};

			/// <summary> 
			/// (D2D1_PROPERTY_BINDING)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_PROPERTY_BINDING
			{
				// <summary>
				// 
				// </summary>
				String^ propertyName;

				// <summary>
				// Este objeto representa a classe(CarenPD2D1_PROPERTY_FUNCTIONS) que armazena os ponteiros para as funções (setfunction & getfunction).
				// </summary>
				Object^ setFunction_and_getFunction;
			};

			/// <summary> 
			/// (D2D1_QUADRATIC_BEZIER_SEGMENT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_QUADRATIC_BEZIER_SEGMENT
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point1;

				// <summary>
			   // 
			   // </summary>
				CA_D2D1_POINT_2F^ point2;
			};

			/// <summary> 
			/// (D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ center;

				// <summary>
			   // 
			   // </summary>
				CA_D2D1_POINT_2F^ gradientOriginOffset;

				// <summary>
				  // 
				  // </summary>
				float         radiusX;

				// <summary>
				  // 
				  // </summary>
				float         radiusY;

			};

			/// <summary> 
			/// (D2D1_RESOURCE_TEXTURE_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RESOURCE_TEXTURE_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				cli::array<UInt32>^ extents;

				// <summary>
			   // 
			   // </summary>
				UInt32                 dimensions;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_BUFFER_PRECISION  bufferPrecision;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_CHANNEL_DEPTH     channelDepth;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_FILTER            filter;

				// <summary>
				  // 
				  // </summary>
				cli::array<Enumeracoes::CA_D2D1_EXTEND_MODE>^ extendModes;
			};

			/// <summary> 
			/// (D2D1_RESOURCE_USAGE)(ABSOLETA)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RESOURCE_USAGE
			{
				// <summary>
				// 
				// </summary>
				UInt64 workingTextureAreaMemory;

				// <summary>
				// 
				// </summary>
				UInt64 cachingTextureAreaMemory;

				// <summary>
				  // 
				  // </summary>
				UInt64 shaderCacheMemory;
			};

			/// <summary> 
			/// (D2D1_RENDER_TARGET_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RENDER_TARGET_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_RENDER_TARGET_TYPE  type;

				// <summary>
				// 
				// </summary>
				CA_D2D1_PIXEL_FORMAT^ pixelFormat;

				// <summary>
				  // 
				  // </summary>
				float                    dpiX;

				// <summary>
				  // 
				  // </summary>
				float                    dpiY;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_RENDER_TARGET_USAGE usage;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_FEATURE_LEVEL       minLevel;
			};

			/// <summary> 
			/// (D2D1_RENDERING_CONTROLS)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_RENDERING_CONTROLS
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_BUFFER_PRECISION bufferPrecision;

				// <summary>
				// 
				// </summary>
				CA_D2D1_SIZE_U^ tileSize;
			};

			/// <summary> 
			/// (D2D1_ROUNDED_RECT)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_ROUNDED_RECT
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_RECT_F^ rect;

				// <summary>
				// 
				// </summary>
				float       radiusX;

				// <summary>
				  // 
				  // </summary>
				float       radiusY;
			};

			/// <summary> 
			/// (D2D1_SIMPLE_COLOR_PROFILE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SIMPLE_COLOR_PROFILE
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ redPrimary;

				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ greenPrimary;

				// <summary>
				  // 
				  // </summary>
				CA_D2D1_POINT_2F^ bluePrimary;

				// <summary>
				  // 
				  // </summary>
				CA_D2D1_POINT_2F^ whitePointXZ;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_GAMMA1   gamma;
			};

			/// <summary> 
			/// (D2D1_STROKE_STYLE_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_STROKE_STYLE_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  startCap;

				// <summary>
			   // 
			   // </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  endCap;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  dashCap;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_LINE_JOIN  lineJoin;

				// <summary>
				  // 
				  // </summary>
				float           miterLimit;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_DASH_STYLE dashStyle;

				// <summary>
				  // 
				  // </summary>
				float           dashOffset;
			};

			/// <summary> 
			/// (D2D1_STROKE_STYLE_PROPERTIES1)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_STROKE_STYLE_PROPERTIES1
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  startCap;

				// <summary>
			   // 
			   // </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  endCap;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_CAP_STYLE  dashCap;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_LINE_JOIN  lineJoin;

				// <summary>
				  // 
				  // </summary>
				float           miterLimit;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_DASH_STYLE dashStyle;

				// <summary>
				  // 
				  // </summary>
				float           dashOffset;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_STROKE_TRANSFORM_TYPE transformType;

			};

			/// <summary> 
			/// (D2D1_SVG_LENGTH)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SVG_LENGTH
			{
				// <summary>
				// 
				// </summary>
				float                 value;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_SVG_LENGTH_UNITS units;
			};

			/// <summary> 
			/// (D2D1_SVG_PRESERVE_ASPECT_RATIO)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SVG_PRESERVE_ASPECT_RATIO
			{
				// <summary>
				// 
				// </summary>
				Boolean                    defer;

				// <summary>
			   // 
			   // </summary>
				Enumeracoes::CA_D2D1_SVG_ASPECT_ALIGN   align;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_SVG_ASPECT_SCALING meetOrSlice;
			};

			/// <summary> 
			/// (D2D1_SVG_VIEWBOX)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_SVG_VIEWBOX
			{
				// <summary>
				// 
				// </summary>
				float x;

				// <summary>
			   // 
			   // </summary>
				float y;

				// <summary>
				  // 
				  // </summary>
				float width;

				// <summary>
				  // 
				  // </summary>
				float height;
			};

			/// <summary> 
			/// (D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_ORIENTATION                      orientation;

				// <summary>
				// 
				// </summary>
				float                                 scaleX;

				// <summary>
				  // 
				  // </summary>
				float                                 scaleY;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_INTERPOLATION_MODE               interpolationMode;

				// <summary>
				  // 
				  // </summary>
				Enumeracoes::CA_D2D1_TRANSFORMED_IMAGE_SOURCE_OPTIONS options;
			};

			/// <summary> 
			/// (D2D1_TRIANGLE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_TRIANGLE
			{
				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point1;

				// <summary>
				// 
				// </summary>
				CA_D2D1_POINT_2F^ point2;

				// <summary>
				  // 
				  // </summary>
				CA_D2D1_POINT_2F^ point3;
			};

			/// <summary> 
			/// (D2D1_VERTEX_BUFFER_PROPERTIES)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_VERTEX_BUFFER_PROPERTIES
			{
				// <summary>
				// 
				// </summary>
				UInt32            inputCount;

				// <summary>
				// 
				// </summary>
				Enumeracoes::CA_D2D1_VERTEX_USAGE usage;

				// <summary>
				  // 
				  // </summary>
				Object^ data;

				// <summary>
				  // 
				  // </summary>
				UInt32           byteWidth;
			};

			/// <summary> 
			/// (D2D1_VERTEX_RANGE)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_D2D1_VERTEX_RANGE
			{
				// <summary>
				// 
				// </summary>
				UINT32 startVertex;

				// <summary>
				// 
				// </summary>
				UINT32 vertexCount;

			};
			





			//WIC Estruturas.

			/// <summary> 
			/// (WICRect)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICRect
			{
				/// <summary>
				/// 
				/// </summary>
				Int32 X;
				/// <summary>
				/// 
				/// </summary>
				Int32 Y;
				/// <summary>
				/// 
				/// </summary>
				Int32 Width;
				/// <summary>
				/// 
				/// </summary>
				Int32 Height;
			};

			/// <summary> 
			/// (WICBitmapPlaneDescription)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICBitmapPlaneDescription
			{
				/// <summary>
				/// 
				/// </summary>
				String^ Format;
				/// <summary>
				/// 
				/// </summary>
				UInt32  Width;
				/// <summary>
				/// 
				/// </summary>
				UInt32  Height;
			};

			/// <summary> 
			/// (WICBitmapPattern)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICBitmapPattern
			{
				/// <summary>
				/// 
				/// </summary>
				UInt64                 Position;
				/// <summary>
				/// 
				/// </summary>  
				UInt64                 Length;
				/// <summary>
				/// 
				/// </summary>  
				Object^ Pattern;
				/// <summary>
				/// 
				/// </summary>  
				Object^ Mask;
				/// <summary>
				/// 
				/// </summary>  
				Boolean                EndOfStream;
			};

			/// <summary> 
			/// (WICBitmapPlane)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICBitmapPlane
			{
				/// <summary>
				/// 
				/// </summary>	
				String^ Format;
				/// <summary>
				/// 
				/// </summary>  
				Object^ pbBuffer;
				/// <summary>
				/// 
				/// </summary>  
				UInt32               cbStride;
				/// <summary>
				/// 
				/// </summary>  
				UInt32               cbBufferSize;
			};

			/// <summary> 
			/// (WICDdsFormatInfo)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICDdsFormatInfo
			{
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_DXGI_FORMAT DxgiFormat;
				/// <summary>
				/// 
				/// </summary>
				UInt32        BytesPerBlock;
				/// <summary>
				/// 
				/// </summary>
				UInt32        BlockWidth;
				/// <summary>
				/// 
				/// </summary>
				UInt32        BlockHeight;
			};

			/// <summary> 
			/// (WICDdsParameters)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICDdsParameters
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32            Width;
				/// <summary>
				/// 
				/// </summary>
				UInt32            Height;
				/// <summary>
				/// 
				/// </summary>
				UInt32            Depth;
				/// <summary>
				/// 
				/// </summary>
				UInt32            MipLevels;
				/// <summary>
				/// 
				/// </summary>
				UInt32            ArraySize;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_DXGI_FORMAT DxgiFormat;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICDdsDimension Dimension;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICDdsAlphaMode AlphaMode;
			};

			/// <summary> 
			/// (WICImageParameters)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICImageParameters
			{
				/// <summary>
				/// 
				/// </summary>
				CA_D2D1_PIXEL_FORMAT^ PixelFormat;
				/// <summary>
				/// 
				/// </summary>
				float             DpiX;
				/// <summary>
				/// 
				/// </summary>
				float             DpiY;
				/// <summary>
				/// 
				/// </summary>
				float             Top;
				/// <summary>
				/// 
				/// </summary>
				float             Left;
				/// <summary>
				/// 
				/// </summary>
				UInt32            PixelWidth;
				/// <summary>
				/// 
				/// </summary>
				UInt32            PixelHeight;
			};

			/// <summary> 
			/// (WICJpegFrameHeader)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICJpegFrameHeader
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     Width;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     Height;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICJpegTransferMatrix      TransferMatrix;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICJpegScanType            ScanType;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     cComponents;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     ComponentIdentifiers;
				/// <summary>
				/// 
				/// </summary>
				Constantes::CA_WIC_IWICJpegFrameDecode  SampleFactors;
				/// <summary>
				/// 
				/// </summary>
				Constantes::CA_WIC_IWICJpegFrameDecode  QuantizationTableIndices;
			};

			/// <summary> 
			/// (WICJpegScanHeader)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICJpegScanHeader
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32  cComponents;
				/// <summary>
				/// 
				/// </summary>
				UInt32  RestartInterval;
				/// <summary>
				/// 
				/// </summary>
				UInt32 ComponentSelectors;
				/// <summary>
				/// 
				/// </summary>
				Constantes::CA_WIC_IWICJpegFrameDecode HuffmanTableIndices;
				/// <summary>
				/// 
				/// </summary>
				Byte  StartSpectralSelection;
				/// <summary>
				/// 
				/// </summary>
				Byte  EndSpectralSelection;
				/// <summary>
				/// 
				/// </summary>
				Byte  SuccessiveApproximationHigh;
				/// <summary>
				/// 
				/// </summary>
				Byte  SuccessiveApproximationLow;
			};

			/// <summary> 
			/// (WICMetadataHeader)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICMetadataHeader
			{
				/// <summary>
				/// 
				/// </summary>
				UInt64               Position;
				/// <summary>
				/// 
				/// </summary>
				UInt64               Length;
				/// <summary>
				/// 
				/// </summary>
				cli::array<Byte>^ Header;
				/// <summary>
				/// 
				/// </summary>
				UInt64               DataOffset;
			};

			/// <summary> 
			/// (WICMetadataPattern)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICMetadataPattern
			{
				/// <summary>
				/// 
				/// </summary>
				UInt64               Position;
				/// <summary>
				/// 
				/// </summary>
				UInt64               Length;
				/// <summary>
				/// 
				/// </summary>
				cli::array<Byte>^ Pattern;
				/// <summary>
				/// 
				/// </summary>
				cli::array<Byte>^ Mask;
				/// <summary>
				/// 
				/// </summary>
				UInt64               DataOffset;
			};

			/// <summary> 
			/// (WICRawCapabilitiesInfo)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICRawCapabilitiesInfo
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     cbSize;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     CodecMajorVersion;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     CodecMinorVersion;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         ExposureCompensationSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         ContrastSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         RGBWhitePointSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         NamedWhitePointSupport;
				/// <summary>
				/// 
				/// </summary>
				UInt32                                     NamedWhitePointSupportMask;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         KelvinWhitePointSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         GammaSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         TintSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         SaturationSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         SharpnessSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         NoiseReductionSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         DestinationColorProfileSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         ToneCurveSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawRotationCapabilities RotationSupport;
				/// <summary>
				/// 
				/// </summary>
				Enumeracoes::CA_WICRawCapabilities         RenderModeSupport;
			};

			/// <summary> 
			/// (WICRawToneCurvePoint)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICRawToneCurvePoint
			{
				/// <summary>
				/// 
				/// </summary>
				double Input;

				/// <summary>
				/// 
				/// </summary>
				double Output;
			};

			/// <summary> 
			/// (WICRawToneCurve)(FALTA DOCUMENTAR) - 
			/// </summary>
			public ref struct CA_WICRawToneCurve
			{
				/// <summary>
				/// 
				/// </summary>
				UInt32                                cPoints;

				/// <summary>
				/// 
				/// </summary>
				cli::array<CA_WICRawToneCurvePoint^>^ aPoints;
			};




			//DirectWrite Estruturas (API PENDENTE)

			public ref struct CA_DWRITE_GLYPH_OFFSET
			{
				float advanceOffset;
				float ascenderOffset;
			};

			public ref struct CA_DWRITE_GLYPH_RUN
			{
				/// <summary>
				/// Uma interface base que contém o ponteiro para a (IDWriteFontFace).
				/// </summary>
				Object^ fontFace;
				float                     fontEmSize;
				UInt32                    glyphCount;
				cli::array<UInt16>^  glyphIndices;
				cli::array<float>^  glyphAdvances;
				cli::array<CA_DWRITE_GLYPH_OFFSET^>^ glyphOffsets;
				Boolean                      isSideways;
				UInt32                    bidiLevel;
			};
			
			public ref struct CA_DWRITE_GLYPH_RUN_DESCRIPTION
			{
				String^ localeName;
				String^ string;
				UInt32  stringLength;
				cli::array<UInt16>^  clusterMap;
				UInt32  textPosition;
			};




			//Windows(ActiveX) Estruturas (SUPORTE)

			/// <summary> 
			/// (PROPBAG2)(FALTA DOCUMENTAR) - Contém ou recebe informações de propriedade.
			/// </summary>
			public ref struct CA_PROPBAG2
			{
				UInt32 dwType;
				UInt16 vt;
				UInt16 cfType;
				UInt32 dwHint;
				String^ pstrName;
				String^ clsid;
			};
		}
	}
}