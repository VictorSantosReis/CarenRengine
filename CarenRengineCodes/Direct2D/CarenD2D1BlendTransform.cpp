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
#include "CarenD2D1BlendTransform.h"

//Destruidor.
CarenD2D1BlendTransform::~CarenD2D1BlendTransform()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1BlendTransform::CarenD2D1BlendTransform()
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
CarenResult CarenD2D1BlendTransform::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1BlendTransform::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1BlendTransform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1BlendTransform**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1BlendTransform::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1BlendTransform*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1BlendTransform**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1BlendTransform::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1BlendTransform::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1BlendTransform::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1BlendTransform::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1BlendTransform::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1BlendTransform::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1BlendTransform::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1BlendTransform::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1BlendTransform();
}



// Métodos da interface proprietária(ICarenD2D1BlendTransform)


/// <summary>
/// Obtém a descrição da mistura do objeto de transformação de mistura correspondente.
/// </summary>
/// <param name="Param_Out_Descricao">Retorna  a descrição da mistura especificada para a transformação da mistura.</param>
void CarenD2D1BlendTransform::GetDescription([Out] CA_D2D1_BLEND_DESCRIPTION^% Param_Out_Descricao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BLEND_DESCRIPTION BlendDesc = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDescription(&BlendDesc);

	//Converte e define no parametro de saida.
	Param_Out_Descricao = Util.ConverterD2D1_BLEND_DESCRIPTIONUnmanagedToManaged(&BlendDesc);
}

/// <summary>
/// Altera a descrição da mistura do objeto de transformação de mistura correspondente.
/// </summary>
/// <param name="Param_Descricao">A nova descrição da mistura especificada para a transformação da mistura.</param>
void CarenD2D1BlendTransform::SetDescription(CA_D2D1_BLEND_DESCRIPTION^ Param_Descricao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BLEND_DESCRIPTION* pDescBlend = NULL;

	//Converte a estrutura
	pDescBlend = Util.ConverterD2D1_BLEND_DESCRIPTIONManagedToUnmanaged(Param_Descricao);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetDescription(pDescBlend);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pDescBlend);
}



// Métodos da interface (ICarenD2D1ConcreteTransform)


/// <summary>
/// Define se a saída da transformação especificada está armazenada em cache. 
/// </summary>
/// <param name="Param_IsCached">TRUE se a saída deve ser armazenada em cache; caso contrário, FALSO.</param>
void CarenD2D1BlendTransform::SetCached(Boolean Param_IsCached)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetCached(Param_IsCached ? TRUE : FALSE);
}

/// <summary>
/// Define as propriedades do buffer de saída do nó de transformação especificado. 
/// </summary>
/// <param name="Param_BufferPrecision">O número de bits e o tipo de buffer de saída.</param>
/// <param name="Param_ChannelDepth">O número de canais no buffer de saída (1 ou 4).</param>
CarenResult CarenD2D1BlendTransform::SetOutputBuffer(
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	CA_D2D1_CHANNEL_DEPTH Param_ChannelDepth)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION BufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	D2D1_CHANNEL_DEPTH ChannelDepth = static_cast<D2D1_CHANNEL_DEPTH>(Param_ChannelDepth);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetOutputBuffer(BufferPrecision, ChannelDepth);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1TransformNode)


/// <summary>
/// Obtém o número de entradas para o nó de transformação. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de entradas para este nó de transformação.</param>
void CarenD2D1BlendTransform::GetInputCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetInputCount();
}