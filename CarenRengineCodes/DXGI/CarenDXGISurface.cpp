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
#include "CarenDXGISurface.h"

//Destruidor.
CarenDXGISurface::~CarenDXGISurface()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenDXGISurface::CarenDXGISurface()
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
CarenResult CarenDXGISurface::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISurface::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISurface*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISurface**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenDXGISurface::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<IDXGISurface*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<IDXGISurface**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISurface::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenDXGISurface::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenDXGISurface::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenDXGISurface::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenDXGISurface::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenDXGISurface::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenDXGISurface::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenDXGISurface();
}


//
// Métodos da interface proprietária(ICarenDXGISurface)
//

/// <summary>
/// (GetDesc) - Método responsável por obter uma descrição da superfície.
/// </summary>
/// <param name="Param_Out_DescSuperfice">Recebe uma estrutura descrevendo a superfice.</param>
CarenResult CarenDXGISurface::GetDesc([Out] CA_DXGI_SURFACE_DESC^% Param_Out_DescSuperfice)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::GetDesc(PonteiroTrabalho,
		Param_Out_DescSuperfice
	);
}

/// <summary>
/// (Map) - Método responsável por obter um ponteiro para os dados contidos na superfície e negue o acesso da GPU à superfície.
/// </summary>
/// <param name="Param_Flags">Bandeiras de leitura da CPU que definem o tipo de acesso ao dados da superfice.</param>
/// <param name="Param_Out_RectMapeado">Recebe uma estrutura que contém os dados mapeados da superfice.</param>
CarenResult CarenDXGISurface::Map(
	CA_DXGI_MAP_FLAGS Param_Flags, 
	[Out] CA_DXGI_MAPPED_RECT^% Param_Out_RectMapeado)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::Map(PonteiroTrabalho,
		Param_Flags,
		Param_Out_RectMapeado
	);
}

/// <summary>
/// (Unmap) - Método responsável por invalidar o ponteiro para a superfície recuperada pelo ICarenDXGISurface::Map e 
/// reativar o acesso GPU ao recurso.
/// </summary>
CarenResult CarenDXGISurface::Unmap()
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGISurface::Unmap(PonteiroTrabalho);
}




// Métodos da interface ICarenDXGIDeviceSubObject

/// <summary>
/// Recupera o dispositivo.
/// </summary>
/// <param name="Param_RIIDInterface">O ID de referência para o dispositivo.</param>
/// <param name="Param_Out_Objeto">Recebe um ponteiro para o dispositivo solictiado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISurface::GetDevice(
	String^ Param_RIIDInterface, 
	ICaren^ Param_Out_Objeto)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIDeviceSubObject::GetDevice(PonteiroTrabalho,
		Param_RIIDInterface,
		Param_Out_Objeto
	);
}




// Métodos da interface ICarenDXGIObject

/// <summary>
/// Recupera o objeto pai deste objeto.
/// </summary>
/// <param name="Param_RIIDInterface">A identificação da interface solicitada.</param>
/// <param name="Param_Out_ObjetoPai">Recebe o ponteiro para o objeto pai do objeto atual. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenDXGISurface::GetParent(
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
CarenResult CarenDXGISurface::SetPrivateData(
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
CarenResult CarenDXGISurface::GetPrivateData(
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
CarenResult CarenDXGISurface::SetPrivateDataInterface(
	String^ Param_GuidInterface, 
	ICaren^ Param_Interface)
{
	//Chama o método na classe de funções compartilhadas do DXGI.
	return Shared_DXGIObject::SetPrivateDataInterface(PonteiroTrabalho,
		Param_GuidInterface,
		Param_Interface
	);
}