﻿/*
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
#include "CarenDXGIFactory1.h"

//Destruidor.
CarenDXGIFactory1::~CarenDXGIFactory1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor
CarenDXGIFactory1::CarenDXGIFactory1(Boolean Param_CriarInterface)
{
	//Verifica se deve ou não criar uma interface.
	if (Param_CriarInterface)
	{
		//Variavel que vai conter o resultado COM.
		HRESULT Hr = E_FAIL;

		//Variaveis utilizadas.
		Utilidades Util;
		IDXGIFactory1* vi_pOutFactory = Nulo;

		//Chama o método para criar a interface.
		Hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&vi_pOutFactory));

		//Verifica se não ocorreu erro no processo.
		if (!Sucesso(Hr))
		{
			//Chama uma exceção para informar o error.
			throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
		}

		//Define a interface criada no ponteiro de trabalho
		PonteiroTrabalho = vi_pOutFactory;
	}
	else
	{
		//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
	}
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenDXGIFactory1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGIFactory1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGIFactory1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGIFactory1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGIFactory1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGIFactory1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGIFactory1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGIFactory1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGIFactory1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGIFactory1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGIFactory1();
}






// Métodos da interface ICarenDXGIFactory1

/// <summary>
/// (EnumAdapters1) - Enumera ambos os adaptadores (cartões de vídeo) com ou sem saídas.
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto ICarenDXGIFactory1. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory1::EnumAdapters1(
	UInt32 Param_IdAdaptador, 
	[Out] ICarenDXGIAdapter1^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumAdapters1(PonteiroTrabalho,
		Param_IdAdaptador,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (IsCurrent) - Informa uma aplicação da possível necessidade de reenumerar adaptadores.
/// </summary>
/// <param name="Param_Out_Atual">Retorna FALSO para informar o aplicativo de chamada para re-enumerar adaptadores.</param>
CarenResult CarenDXGIFactory1::IsCurrent(
	[Out] Boolean% Param_Out_Atual)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::IsCurrent(PonteiroTrabalho,
		Param_Out_Atual
	);
}



// Métodos da interface ICarenDXGIFactory

/// <summary>
/// (CreateSoftwareAdapter) - Crie uma interface de adaptação que represente um adaptador de software.
/// </summary>
/// <param name="Param_ModuleHandle">Uma handle para a (.dll) do adaptador de software.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para o adaptador criado.</param>
CarenResult CarenDXGIFactory1::CreateSoftwareAdapter(
	IntPtr Param_ModuleHandle, 
	[Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSoftwareAdapter(PonteiroTrabalho,
		Param_ModuleHandle,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (CreateSwapChain) - Cria uma cadeia de swaps.
/// [Começando com o Direct3D 11.1, recomendamos não usar mais o CreateSwapChain para criar uma cadeia de swaps. Em vez disso, use CreateSwapChainForHwnd, CreateSwapChainForCoreWindow, ou 
/// CreateSwapChainForComposition dependendo de como você quer criar a cadeia de swap.]
/// </summary>
/// <param name="Param_Dispositivo3D">Para Direct3D 11, e versões anteriores do Direct3D, este é um ponteiro para o dispositivo Direct3D para a cadeia de swap. Para Direct3D 12 este é 
/// um ponteiro para uma fila de comando direto(D3D12CommandQueue). Este parâmetro não pode ser NULO.</param>
/// <param name="Param_Desc">Uma estrutura CA_DXGI_SWAP_CHAIN_DESC para a descrição da cadeia de swap. Este parâmetro não pode ser NULO.</param>
/// <param name="Param_Out_SwapChain">Recebe um ponteiro para a interface do SwapChain.</param>
CarenResult CarenDXGIFactory1::CreateSwapChain(
	ICaren^ Param_Dispositivo3D, 
	CA_DXGI_SWAP_CHAIN_DESC^ Param_Desc, 
	[Out] ICarenDXGISwapChain^% Param_Out_SwapChain)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::CreateSwapChain(PonteiroTrabalho,
		Param_Dispositivo3D,
		Param_Desc,
		Param_Out_SwapChain
	);
}

/// <summary>
/// (EnumAdapters) - Enumera os adaptadores (Placas Graficas).
/// Quando você cria uma fábrica, a fábrica enumera o conjunto de adaptadores que estão disponíveis no sistema. Portanto, se você alterar os adaptadores em um sistema, você deve destruir e 
/// recriar o objeto IDXGIFactory. O número de adaptadores em um sistema muda quando você adiciona ou remove um cartão de exibição, ou atraca ou desatraca um laptop.
/// </summary>
/// <param name="Param_IdAdaptador">O Indice para o adaptador a ser enumerado.</param>
/// <param name="Param_Out_Adaptador">Recebe um ponteiro para a interface do adaptador no indice especificado. O chamador é responsável por liberar a interface.</param>
CarenResult CarenDXGIFactory1::EnumAdapters(
	UInt32 Param_IdAdaptador, 
	[Out] ICarenDXGIAdapter^% Param_Out_Adaptador)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::EnumAdapters(PonteiroTrabalho,
		Param_IdAdaptador,
		Param_Out_Adaptador
	);
}

/// <summary>
/// (GetWindowAssociation) - Obtenha a janela através da qual o usuário controla a transição de e para a tela cheia.
/// </summary>
/// <param name="Param_HandleJanela">Retorna um ponteiro para a alça da janela.</param>
CarenResult CarenDXGIFactory1::GetWindowAssociation(
	[Out] IntPtr% Param_HandleJanela)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::GetWindowAssociation(PonteiroTrabalho,
		Param_HandleJanela
	);
}

/// <summary>
/// (MakeWindowAssociation) - Permite que a DXGI monitore a fila de mensagens de um aplicativo para a sequência de chave de entrada em alt (que faz com que o aplicativo mude de janelas 
/// para tela cheia ou vice-versa).
/// </summary>
/// <param name="Param_HandleJanela">A handle da janela que deve ser monitorada. Este parâmetro pode ser NULO; mas somente se as bandeiras também forem 0.</param>
/// <param name="Param_Flags"></param>
CarenResult CarenDXGIFactory1::MakeWindowAssociation(
	IntPtr Param_HandleJanela, 
	CA_DXGI_MWA_FLAGS Param_Flags)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIFactory::MakeWindowAssociation(PonteiroTrabalho,
		Param_HandleJanela,
		Param_Flags
	);
}



// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGIFactory1::GetParent(
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
CarenResult CarenDXGIFactory1::SetPrivateData(
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
CarenResult CarenDXGIFactory1::GetPrivateData(
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
CarenResult CarenDXGIFactory1::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}