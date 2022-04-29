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

#include "../pch.h"
#include "CarenD2D1DrawingStateBlock1.h"

//Destruidor.
CarenD2D1DrawingStateBlock1::~CarenD2D1DrawingStateBlock1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1DrawingStateBlock1::CarenD2D1DrawingStateBlock1()
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
CarenResult CarenD2D1DrawingStateBlock1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DrawingStateBlock1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DrawingStateBlock1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DrawingStateBlock1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DrawingStateBlock1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DrawingStateBlock1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DrawingStateBlock1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DrawingStateBlock1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DrawingStateBlock1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1DrawingStateBlock1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1DrawingStateBlock1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1DrawingStateBlock1::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1DrawingStateBlock1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1DrawingStateBlock1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1DrawingStateBlock1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1DrawingStateBlock1();
}



// Métodos da interface proprietária(ICarenD2D1DrawingStateBlock1)


/// <summary>
/// Obtém o modo antialiasing, transformar, tags, mistura primitiva e parte do modo unitário do estado de desenho. 
/// </summary>
/// <param name="Param_Out_DescEstado">Retorna uma estrutura que contém o modo antialiasing, transformar, tags, mistura primitiva e parte do modo unitário do estado de desenho.</param>
void CarenD2D1DrawingStateBlock1::GetDescription([Out] CA_D2D1_DRAWING_STATE_DESCRIPTION1^% Param_Out_DescEstado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION1 OutDrawingState = {};

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDescription(&OutDrawingState);

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_DescEstado = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTION1UnmanagedToManaged(&OutDrawingState);
}

/// <summary>
/// Define a CA_D2D1_DRAWING_STATE_DESCRIPTION1 associada a este bloco de estado de desenho. 
/// </summary>
/// <param name="Param_DescEstado">Uma estrutura D2D1_DRAWING_STATE_DESCRIPTION1 a ser definida associada a este bloco de estado de desenho.</param>
void CarenD2D1DrawingStateBlock1::SetDescription(CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescEstado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION1* pDrawingState = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTION1ManagedToUnmanaged(Param_DescEstado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetDescription(pDrawingState);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pDrawingState);
}




// Métodos da interface proprietária(ICarenD2D1DrawingStateBlock)


/// <summary>
/// Recupera o modo antialiasing, transforma e marca parte do estado de desenho. 
/// </summary>
/// <param name="Param_Out_DescEstado">Retorna uma estrutura que contém o modo antialiasing, transforma e marca parte do estado de desenho.</param>
void CarenD2D1DrawingStateBlock1::GetDescription([Out] CA_D2D1_DRAWING_STATE_DESCRIPTION^% Param_Out_DescEstado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION OutDrawingState = {};

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDescription(&OutDrawingState);

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_DescEstado = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTIONUnmanagedToManaged(&OutDrawingState);
}

/// <summary>
/// Recupera a configuração de renderização de texto do estado de desenho.
/// </summary>
/// <param name="Param_Out_TextRenderingParams">Retorna um ponteiro para a interface (IDWriteRenderingParams) que descreve a configuração de renderização de texto do estado de desenho. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DrawingStateBlock1::GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pOutDwriteParams = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTextRenderingParams(&pOutDwriteParams);

	//Define na interface de saida.
	Resultado = Param_Out_TextRenderingParams->AdicionarPonteiro(pOutDwriteParams);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera a interface recuperada.
		pOutDwriteParams->Release();
		pOutDwriteParams = NULL;
	}

	//Define sucesso
	SetCarenSucesso(Resultado);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Especifica o modo antialiasing, transforma e marca parte do estado de desenho.
/// </summary>
/// <param name="Param_DescEstado">Uma estrutura que descreve o modo antialiasing, transformar e tags do estado de desenho.</param>
void CarenD2D1DrawingStateBlock1::SetDescription(CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescEstado)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION* pDrawingState = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTIONManagedToUnmanaged(Param_DescEstado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetDescription(pDrawingState);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pDrawingState);
}

/// <summary>
/// Especifica a configuração de renderização de texto do estado de desenho.
/// </summary>
/// <param name="Param_TextRenderingParams">Uma interface (IDWriteRenderingParams) para a configuração de renderização de texto do estado de desenho ou NULO para usar as configurações padrão.</param>
CarenResult CarenD2D1DrawingStateBlock1::SetTextRenderingParams(ICaren^ Param_TextRenderingParams)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pDwriteParams = NULL;

	//Verifica se a interface é valida.
	if (!ObjetoGerenciadoValido(Param_TextRenderingParams))
	{
		//Objeto NULO.

		//Define erro na operação.
		SetCarenErro(Resultado, ResultCode::ER_E_INVALIDARG);

		//Sai do método
		Sair;
	}

	//Recupera o ponteiro para a interface nativa.
	Resultado = RecuperarPonteiroCaren(Param_TextRenderingParams, &pDwriteParams);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTextRenderingParams(pDwriteParams);

	//Define sucesso na operação.
	SetCarenSucesso(Resultado);

Done:;
	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1DrawingStateBlock1::GetFactory(ICaren^ Param_Out_Factory)
{
	//Variaveis a serem utilizadas.
	ID2D1Factory* pFactory = NULL;

	//Variavel de resultados.
	CarenResult Resultado;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFactory(&pFactory);

	//Verifica se o ponteiro é válido
	if (!ObjetoValido(pFactory))
		Sair;

	//Adiciona o ponteiro na interface informada.
	Resultado = Param_Out_Factory->AdicionarPonteiro(pFactory);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera o ponteiro recuperado anteriormente.
		pFactory->Release();
		pFactory = NULL;

		//Chama uma execeção para indicar o erro.
		throw gcnew Exception(String::Format("Ocorreu uma falha ao definir o ponteiro nativo na interface gerenciada. Código de erro > {0}", Resultado.StatusCode));
	}

Done:;
}