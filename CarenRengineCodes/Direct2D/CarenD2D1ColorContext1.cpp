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
#include "CarenD2D1ColorContext1.h"

//Destruidor.
CarenD2D1ColorContext1::~CarenD2D1ColorContext1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1ColorContext1::CarenD2D1ColorContext1()
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
CarenResult CarenD2D1ColorContext1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ColorContext1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ColorContext1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ColorContext1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ColorContext1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ColorContext1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ColorContext1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ColorContext1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ColorContext1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1ColorContext1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1ColorContext1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1ColorContext1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1ColorContext1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1ColorContext1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1ColorContext1();
}



// Métodos da interface (ICarenD2D1ColorContext1)

/// <summary>
/// Recupera o tipo de contexto de cor.
/// </summary>
/// <param name="Param_Out_ColorContext">Retorna o tipo de contexto de cores.</param>
void CarenD2D1ColorContext1::GetColorContextType([Out] CA_D2D1_COLOR_CONTEXT_TYPE% Param_Out_ColorContext)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1ColorContext::GetColorContextType(PonteiroTrabalho,
		Param_Out_ColorContext
	);
}

/// <summary>
/// Recupera o espaço de cores DXGI deste contexto. Retorna DXGI_COLOR_SPACE_CUSTOM quando o tipo de contexto de cor é ICC.
/// </summary>
/// <param name="Param_Out_DXGIColorSpace">Retorna o espaço de cor DXGI deste contexto.</param>
void CarenD2D1ColorContext1::GetDXGIColorSpace([Out] CA_DXGI_COLOR_SPACE_TYPE% Param_Out_DXGIColorSpace)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1ColorContext::GetDXGIColorSpace(PonteiroTrabalho,
		Param_Out_DXGIColorSpace
	);
}

/// <summary>
/// Recupera um perfil de cor simples.
/// </summary>
/// <param name="Param_Out_ColorProfile">Retorna uma estrutura CA_D2D1_SIMPLE_COLOR_PROFILE que conterá o perfil de cor simples quando o método retornar.</param>
CarenResult CarenD2D1ColorContext1::GetSimpleColorProfile([Out] CA_D2D1_SIMPLE_COLOR_PROFILE^% Param_Out_ColorProfile)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	return Shared_D2D1ColorContext::GetSimpleColorProfile(PonteiroTrabalho,
		Param_Out_ColorProfile
	);
}





// Métodos da interface (ICarenD2D1ColorContext)

/// <summary>
/// Obtém o espaço de cores do contexto de cores.
/// </summary>
/// <param name="Param_Out_EspacoCor">Retorna uma enumeração que contém o espaço de cores do contexto.</param>
void CarenD2D1ColorContext1::GetColorSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1ColorContext::GetColorSpace(PonteiroTrabalho,
		Param_Out_EspacoCor
	);
}

/// <summary>
/// Obtém o bytes de perfil de cor para um ICarenD2D1ColorContext1.
/// </summary>
/// <param name="Param_Out_ColorProfile">Retorna um buffer que contém o perfil de cores.</param>
/// <param name="Param_ProfileSize">O tamanho do buffer de perfil.</param>
CarenResult CarenD2D1ColorContext1::GetProfile(
	[Out] cli::array<Byte>^% Param_Out_ColorProfile,
	UInt32 Param_ProfileSize)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	return Shared_D2D1ColorContext::GetProfile(PonteiroTrabalho,
		Param_Out_ColorProfile,
		Param_ProfileSize
	);
}

/// <summary>
/// Obtém o tamanho do perfil de cor associado ao bitmap.
/// </summary>
/// <param name="Param_Out_ProfileSize">Retorna o tamanho do perfil em bytes.</param>
void CarenD2D1ColorContext1::GetProfileSize([Out] UInt32% Param_Out_ProfileSize)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1ColorContext::GetProfileSize(PonteiroTrabalho,
		Param_Out_ProfileSize
	);
}





// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1ColorContext1::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}