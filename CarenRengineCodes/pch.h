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

//Interfaces do DXGI
#include "CarenDXGIAdapter.h"
#include "CarenDXGIAdapter1.h"
#include "CarenDXGIAdapter2.h"
#include "CarenDXGIAdapter3.h"
#include "CarenDXGIAdapter4.h"
#include "CarenDXGIDevice.h"
#include "CarenDXGIDevice1.h"
#include "CarenDXGIDevice2.h"
#include "CarenDXGIDevice3.h"
#include "CarenDXGIDevice4.h"
#include "CarenDXGIDeviceSubObject.h"
#include "CarenDXGIFactory.h"
#include "CarenDXGIFactory1.h"
#include "CarenDXGIFactory2.h"
#include "CarenDXGIFactory3.h"
#include "CarenDXGIFactory4.h"
#include "CarenDXGIFactory5.h"
#include "CarenDXGIFactory6.h"
#include "CarenDXGIFactory7.h"
#include "CarenDXGIObject.h"
#include "CarenDXGIOutput.h"
#include "CarenDXGIOutput1.h"
#include "CarenDXGIOutput2.h"
#include "CarenDXGIOutput3.h"
#include "CarenDXGIOutput4.h"
#include "CarenDXGIOutput5.h"
#include "CarenDXGIOutput6.h"
#include "CarenDXGIOutputDuplication.h"
#include "CarenDXGIResource.h"
#include "CarenDXGIResource1.h"
#include "CarenDXGISurface.h"
#include "CarenDXGISurface1.h"
#include "CarenDXGISurface2.h"
#include "..\DXGI\CarenDXGISwapChain.h"
#include "..\DXGI\CarenDXGISwapChain1.h"
#include "..\DXGI\CarenDXGISwapChain2.h"
#include "..\DXGI\CarenDXGISwapChain3.h"
#include "..\DXGI\CarenDXGISwapChain4.h"



//Interface do D3D9
#include "CarenDirect3DDeviceManager9.h"



//Interfaces do D3D10
#include "CarenD3D10Multithread.h"



//Interfaces do D3D11
#include "CarenD3D11Asynchronous.h"
#include "CarenD3D11BlendState.h"
#include "CarenD3D11BlendState1.h"
#include "CarenD3D11Buffer.h"
#include "CarenD3D11ClassInstance.h"
#include "CarenD3D11ClassLinkage.h"
#include "CarenD3D11CommandList.h"
#include "CarenD3D11ComputeShader.h"
#include "CarenD3D11Counter.h"
#include "CarenD3D11DepthStencilState.h"
#include "CarenD3D11DepthStencilView.h"
#include "CarenD3D11Device.h"
#include "CarenD3D11Device1.h"
#include "CarenD3D11Device2.h"
#include "CarenD3D11Device3.h"
#include "CarenD3D11Device4.h"
#include "CarenD3D11Device5.h"
#include "CarenD3D11DeviceChild.h"
#include "CarenD3D11DeviceContext.h"
#include "CarenD3D11DeviceContext1.h"
#include "CarenD3D11DeviceContext2.h"
#include "CarenD3D11DeviceContext3.h"
#include "CarenD3D11DeviceContext4.h"
#include "CarenD3D11DomainShader.h"
#include "CarenD3D11Fence.h"
#include "CarenD3D11GeometryShader.h"
#include "CarenD3D11HullShader.h"
#include "CarenD3D11InputLayout.h"
#include "CarenD3D11Multithread.h"
#include "CarenD3D11PixelShader.h"
#include "CarenD3D11Predicate.h"
#include "CarenD3D11Query.h"
#include "CarenD3D11Query1.h"
#include "CarenD3D11RasterizerState.h"
#include "CarenD3D11RasterizerState1.h"
#include "CarenD3D11RasterizerState2.h"
#include "CarenD3D11RenderTargetView.h"
#include "CarenD3D11RenderTargetView1.h"
#include "CarenD3D11Resource.h"
#include "CarenD3D11SamplerState.h"
#include "CarenD3D11ShaderResourceView.h"
#include "CarenD3D11ShaderResourceView1.h"
#include "CarenD3D11Texture1D.h"	
#include "CarenD3D11Texture2D.h"	
#include "CarenD3D11Texture2D1.h"
#include "CarenD3D11Texture3D.h"	
#include "CarenD3D11Texture3D1.h"
#include "CarenD3D11UnorderedAccessView.h"
#include "CarenD3D11UnorderedAccessView1.h"
#include "CarenD3D11VertexShader.h"
#include "CarenD3D11View.h"
#include "CarenD3DDeviceContextState.h"
#endif //PCH_H