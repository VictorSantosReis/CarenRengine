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
#include "../Media Foundation/CarenMFMediaType.h"

//Importa o SDK Base da Media Foundation.
using namespace CarenRengine::MediaFoundation;

//Importa o namespace (BASE) e suas demais dependências
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

/// <summary>
/// Classe responsável por conter os métodos nativos utilizados pela Api do Media Foundation.
/// </summary>
public ref class MediaFoundationFunctions
{
	//Destruidor da classe.
public:
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
	/// Aloca a memória do sistema com um alinhamento de byte especificado e cria um buffer de mídia para gerenciar a memória.
	/// </summary>
	/// <param name="Param_MaxLenght">O tamanho do buffer, em bytes.</param>
	/// <param name="Param_Aligment">Especifica o alinhamento de memória para o buffer.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateAlignedMemoryBuffer(UInt32 Param_MaxLenght, CA_MF_BYTE_ALIGNMENT Param_Aligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um buffer de mídia para gerenciar uma superfície DXGI (Microsoft DirectX Graphics Infrastructure).
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície DXGI. Este valor deve ser IID_ID3D11Texture2D.</param>
	/// <param name="Param_SuperficeDXGI">Uma interface IUnknown da superfície DXGI.</param>
	/// <param name="Param_SubresourceIndex">O índice baseado em zero de uma subrefonte da superfície. O objeto buffer de mídia está associado a essa subrefonte.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXGISurfaceBuffer(String^ Param_RIID, ICaren^ Param_SuperficeDXGI, UInt32 Param_SubresourceIndex, Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia uma superfície Direct3D 9.
	/// </summary>
	/// <param name="Param_RIID">Identifica o tipo de superfície Direct3D 9. Atualmente esse valor deve ser IID_IDirect3DSurface9.</param>
	/// <param name="Param_SurfaceDX">Uma interface IUnknown da superfície DirectX.</param>
	/// <param name="Param_BottomUpWhenLinear">Se TRUE, o método ICarenMF2DBuffer::ContiguousCopyTo copia o buffer em um formato de baixo para cima. O formato de baixo para cima é compatível com GDI para imagens RGB não compactadas. Se este parâmetro for FALSE, o método ContiguousCopyTo copia o buffer em um formato de cima para baixo, compatível com o Direct3D.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDXSurfaceBuffer(String^ Param_RIID, ICaren^ Param_SurfaceDX,  Boolean Param_BottomUpWhenLinear, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Aloca um buffer de memória do sistema que é ideal para um tipo de mídia especificado.
	/// </summary>
	/// <param name="Param_MediaType">Uma interface ICarenMFMediaType do tipo de mídia.</param>
	/// <param name="Param_Duration">A duração da amostra. Este valor é necessário para formatos de áudio.</param>
	/// <param name="Param_MinLenght">O tamanho mínimo do buffer, em bytes. O tamanho real do buffer pode ser maior. Especifique zero para alocar o tamanho padrão do buffer para o tipo de mídia.</param>
	/// <param name="Param_MinAligment">O alinhamento mínimo da memória para o buffer. Especifique zero para usar o alinhamento de memória padrão.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateMediaBufferFromMediaType(ICarenMFMediaType^ Param_MediaType, Int64 Param_Duration, UInt32 Param_MinLenght, UInt32 Param_MinAligment, ICarenMFMediaBuffer^ Param_Out_Buffer);

	/// <summary>
	/// Cria um objeto buffer de mídia que gerencia um bitmap do Windows Imaging Component (WIC).
	/// </summary>
	/// <param name="Param_RIID">O identificador da interface. Atualmente este parametro deve ser IID_IWICBitmap</param>
	/// <param name="Param_Surface">Uma interface IUnknown da superfície bitmap. A superfície bitmap deve ser um bitmap WIC que expõe a interface ICarenWICBitmap.</param>
	/// <param name="Param_Out_Buffer">Retorna uma interface (ICarenMFMediaBuffer) do buffer de mídia. usuário deve inicializar a interface antes de chamar este método.</param>
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
	/// Cria um objeto de ativação que representa um dispositivo de captura de hardware.
	/// </summary>
	/// <param name="Param_Atributos">Uma interface ICarenMFAttributes de uma loja de atributos, que é usada para selecionar o dispositivo de captura.</param>
	/// <param name="Param_Out_DispositivoCaptura">Retorna a interface (ICarenMFActivate) de ativação do dispositivo de captura. O usuário deve inicializar a interface antes de chamar este método.</param>
	/// <returns></returns>
	CarenResult _MFCreateDeviceSourceActivate(ICarenMFAttributes^ Param_Atributos, ICarenMFActivate^ Param_Out_DispositivoCaptura);

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
	/// <param name="Param_Out_TipoMidia">Retorna o tipo de midia convertida da estrutura Wav.</param>
	CarenResult CA_MFInitMediaTypeFromWaveFormatEx(
		CA_WAVEFORMATEXEXTENSIBLE^% Param_WavFormato, 
		UInt32 Param_SizeEstrutura, 
		[Out] ICarenMFMediaType^% Param_Out_TipoMidia);
};

