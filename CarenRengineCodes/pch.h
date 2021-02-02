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


// pch.h: esse é um arquivo de cabeçalho pré-compilado.
// Os arquivos listados a seguir são compilados somente uma vez, melhorando o desempenho dos builds futuros.
// Isso também afeta o desempenho do IntelliSense, incluindo a conclusão de código e muitos recursos de navegação de código.
// No entanto, os arquivos listados aqui serão TODOS recompilados se qualquer um deles for atualizado entre builds.
// Não adicione aqui arquivos que você atualizará com frequência, pois isso anula a vantagem de desempenho.

#ifndef PCH_H
#define PCH_H

//Adicione os cabeçalhos que você deseja pré-compilar aqui
#include "Header.h"


//Funções globais
#include "FunctionClass/GlobalFuncs.h"


//Propvariant Manager
#include "PropVariantManager/PropVariantManager.h"


//Interfaces da Api base CAREN
#include "Caren/Caren.h"
#include "Caren/CarenBuffer.h"
#include "Caren/CarenWindowsEvent.h"
#include "Caren/CarenHMONITOR.h"
#include "Caren/CarenObjectState.h"


//Codigos de resultados da api
#include "CodeResults.h"


//Interface da MEDIA FOUNDATION
#include "Media Foundation/CarenMFActivate.h"
#include "Media Foundation/CarenMFAsyncCallback.h"
#include "Media Foundation/CarenMFAsyncResult.h"
#include "Media Foundation/CarenMFAttributes.h"
#include "Media Foundation/CarenMFAudioStreamVolume.h"
#include "Media Foundation/CarenMFByteStream.h"
#include "Media Foundation/CarenMFClock.h"
#include "Media Foundation/CarenMFClockStateSink.h"
#include "Media Foundation/CarenMFCollection.h"
#include "Media Foundation/CarenMFDXGIBuffer.h"
#include "Media Foundation/CarenMFDXGIDeviceManager.h"
#include "Media Foundation/CarenMFGetService.h"
#include "Media Foundation/CarenMF2DBuffer.h"
#include "Media Foundation/CarenMF2DBuffer2.h"
#include "Media Foundation/CarenMFMediaBuffer.h"
#include "Media Foundation/CarenMFMediaEvent.h"
#include "Media Foundation/CarenMFMediaEventGenerator.h"
#include "Media Foundation/CarenMFMediaSession.h"
#include "Media Foundation/CarenMFMediaSink.h"
#include "Media Foundation/CarenMFMediaSinkPreroll.h"
#include "Media Foundation/CarenMFSinkWriterCallback.h"
#include "Media Foundation/CarenMFMediaSource.h"
#include "Media Foundation/CarenMFMediaSourceEx.h"
#include "Media Foundation/CarenMFMediaStream.h"
#include "Media Foundation/CarenMFMediaType.h"
#include "Media Foundation/CarenMFMediaTypeHandler.h"
#include "Media Foundation/CarenMFPresentationClock.h"
#include "Media Foundation/CarenMFPresentationDescriptor.h"
#include "Media Foundation/CarenMFPresentationTimeSource.h"
#include "Media Foundation/CarenMFRateControl.h"
#include "Media Foundation/CarenMFRateSupport.h"
#include "Media Foundation/CarenMFSample.h"
#include "Media Foundation/CarenMFSimpleAudioVolume.h"
#include "Media Foundation/CarenMFSinkWriter.h"
#include "Media Foundation/CarenMFSourceReader.h"
#include "Media Foundation/CarenMFSourceReaderCallback.h"
#include "Media Foundation/CarenMFSourceResolver.h"
#include "Media Foundation/CarenMFStreamDescriptor.h"
#include "Media Foundation/CarenMFStreamSink.h"
#include "Media Foundation/CarenMFTopoLoader.h"
#include "Media Foundation/CarenMFTopology.h"
#include "Media Foundation/CarenMFTopologyNode.h"
#include "Media Foundation/CarenMFTopologyNodeAttributeEditor.h"
#include "Media Foundation/CarenMFTopologyServiceLookup.h"
#include "Media Foundation/CarenMFTopologyServiceLookupClient.h"
#include "Media Foundation/CarenMFTransform.h"
#include "Media Foundation/CarenMFVideoDisplayControl.h"
#include "Media Foundation/CarenMFMediaType.h"
#include "Media Foundation/CarenMFVideoPresenter.h"
#include "Media Foundation/CarenMFVideoRenderer.h"
#include "Media Foundation/CarenMFVideoSampleAllocator.h"


//Interfaces do DXGI
#include "DXGI/CarenDXGIAdapter.h"
#include "DXGI/CarenDXGIAdapter1.h"
#include "DXGI/CarenDXGIAdapter2.h"
#include "DXGI/CarenDXGIAdapter3.h"
#include "DXGI/CarenDXGIAdapter4.h"
#include "DXGI/CarenDXGIDevice.h"
#include "DXGI/CarenDXGIDevice1.h"
#include "DXGI/CarenDXGIDevice2.h"
#include "DXGI/CarenDXGIDevice3.h"
#include "DXGI/CarenDXGIDevice4.h"
#include "DXGI/CarenDXGIDeviceSubObject.h"
#include "DXGI/CarenDXGIFactory.h"
#include "DXGI/CarenDXGIFactory1.h"
#include "DXGI/CarenDXGIFactory2.h"
#include "DXGI/CarenDXGIFactory3.h"
#include "DXGI/CarenDXGIFactory4.h"
#include "DXGI/CarenDXGIFactory5.h"
#include "DXGI/CarenDXGIFactory6.h"
#include "DXGI/CarenDXGIFactory7.h"
#include "DXGI/CarenDXGIObject.h"
#include "DXGI/CarenDXGIOutput.h"
#include "DXGI/CarenDXGIOutput1.h"
#include "DXGI/CarenDXGIOutput2.h"
#include "DXGI/CarenDXGIOutput3.h"
#include "DXGI/CarenDXGIOutput4.h"
#include "DXGI/CarenDXGIOutput5.h"
#include "DXGI/CarenDXGIOutput6.h"
#include "DXGI/CarenDXGIOutputDuplication.h"
#include "DXGI/CarenDXGIResource.h"
#include "DXGI/CarenDXGIResource1.h"
#include "DXGI/CarenDXGISurface.h"
#include "DXGI/CarenDXGISurface1.h"
#include "DXGI/CarenDXGISurface2.h"
#include "DXGI/CarenDXGISwapChain.h"
#include "DXGI/CarenDXGISwapChain1.h"
#include "DXGI/CarenDXGISwapChain2.h"
#include "DXGI/CarenDXGISwapChain3.h"
#include "DXGI/CarenDXGISwapChain4.h"


//Interface do D3D9
#include "Direct3D/CarenDirect3DDeviceManager9.h"


//Interfaces do D3D10
#include "Direct3D/CarenD3D10Multithread.h"


//Interfaces do D3D11
#include "Direct3D/CarenD3D11Asynchronous.h"
#include "Direct3D/CarenD3D11BlendState.h"
#include "Direct3D/CarenD3D11BlendState1.h"
#include "Direct3D/CarenD3D11Buffer.h"
#include "Direct3D/CarenD3D11ClassInstance.h"
#include "Direct3D/CarenD3D11ClassLinkage.h"
#include "Direct3D/CarenD3D11CommandList.h"
#include "Direct3D/CarenD3D11ComputeShader.h"
#include "Direct3D/CarenD3D11Counter.h"
#include "Direct3D/CarenD3D11DepthStencilState.h"
#include "Direct3D/CarenD3D11DepthStencilView.h"
#include "Direct3D/CarenD3D11Device.h"
#include "Direct3D/CarenD3D11Device1.h"
#include "Direct3D/CarenD3D11Device2.h"
#include "Direct3D/CarenD3D11Device3.h"
#include "Direct3D/CarenD3D11Device4.h"
#include "Direct3D/CarenD3D11Device5.h"
#include "Direct3D/CarenD3D11DeviceChild.h"
#include "Direct3D/CarenD3D11DeviceContext.h"
#include "Direct3D/CarenD3D11DeviceContext1.h"
#include "Direct3D/CarenD3D11DeviceContext2.h"
#include "Direct3D/CarenD3D11DeviceContext3.h"
#include "Direct3D/CarenD3D11DeviceContext4.h"
#include "Direct3D/CarenD3D11DomainShader.h"
#include "Direct3D/CarenD3D11Fence.h"
#include "Direct3D/CarenD3D11GeometryShader.h"
#include "Direct3D/CarenD3D11HullShader.h"
#include "Direct3D/CarenD3D11InputLayout.h"
#include "Direct3D/CarenD3D11Multithread.h"
#include "Direct3D/CarenD3D11PixelShader.h"
#include "Direct3D/CarenD3D11Predicate.h"
#include "Direct3D/CarenD3D11Query.h"
#include "Direct3D/CarenD3D11Query1.h"
#include "Direct3D/CarenD3D11RasterizerState.h"
#include "Direct3D/CarenD3D11RasterizerState1.h"
#include "Direct3D/CarenD3D11RasterizerState2.h"
#include "Direct3D/CarenD3D11RenderTargetView.h"
#include "Direct3D/CarenD3D11RenderTargetView1.h"
#include "Direct3D/CarenD3D11Resource.h"
#include "Direct3D/CarenD3D11SamplerState.h"
#include "Direct3D/CarenD3D11ShaderResourceView.h"
#include "Direct3D/CarenD3D11ShaderResourceView1.h"
#include "Direct3D/CarenD3D11Texture1D.h"	
#include "Direct3D/CarenD3D11Texture2D.h"	
#include "Direct3D/CarenD3D11Texture2D1.h"
#include "Direct3D/CarenD3D11Texture3D.h"	
#include "Direct3D/CarenD3D11Texture3D1.h"
#include "Direct3D/CarenD3D11UnorderedAccessView.h"
#include "Direct3D/CarenD3D11UnorderedAccessView1.h"
#include "Direct3D/CarenD3D11VertexShader.h"
#include "Direct3D/CarenD3D11View.h"
#include "Direct3D/CarenD3DDeviceContextState.h"


//Interfaces Windows.
#include "Windows/CarenEnumString.h"
#include "Windows/CarenEnumUnknown.h"
#include "Windows/CarenPersist.h"
#include "Windows/CarenPersistStream.h"
#include "Windows/CarenPropertyBag2.h"
#include "Windows/CarenPropertyStore.h"
#include "Windows/CarenSequentialStream.h"
#include "Windows/CarenStream.h"

#endif//PCH_H