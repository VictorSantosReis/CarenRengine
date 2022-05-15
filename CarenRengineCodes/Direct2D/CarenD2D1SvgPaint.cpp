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
#include "CarenD2D1SvgPaint.h"

//Destruidor.
CarenD2D1SvgPaint::~CarenD2D1SvgPaint()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgPaint::CarenD2D1SvgPaint()
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
CarenResult CarenD2D1SvgPaint::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgPaint::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgPaint*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgPaint**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgPaint::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgPaint*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgPaint**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgPaint::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgPaint::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1SvgPaint::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1SvgPaint::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgPaint::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgPaint::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1SvgPaint::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1SvgPaint();
}



// Métodos da interface proprietária(ICarenD2D1SvgPaint)


/// <summary>
/// Obtém a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR. 
/// </summary>
/// <param name="Param_Out_Color">Retorna a cor da tinta que é usada se o tipo de tinta é D2D1_SVG_PAINT_TYPE_COLOR.</param>
void CarenD2D1SvgPaint::GetColor([Out] CA_D2D1_COLOR_F^% Param_Out_Color)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F OutColor = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetColor(&OutColor);

	//Converte a estrutura e define no parametro de saida.
	Param_Out_Color = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&OutColor);
}

/// <summary>
/// Obtém o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
/// </summary>
/// <param name="Param_Out_Id">O elemento id que atua como o servidor de tinta.</param>
/// <param name="Param_IdCount">A largura do Id do elemento a ser retornado. Chame o método (GetIdLength) para obter esse valor.</param>
CarenResult CarenD2D1SvgPaint::GetId(
[Out] String^% Param_Out_Id,
UInt32 Param_IdCount)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pOutID = NULL;

	//Aloca a string
	pOutID = (PWSTR)CoTaskMemAlloc(static_cast<SIZE_T>(Param_IdCount + 1));

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetId(pOutID, Param_IdCount);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a string no parametro de saida
	Param_Out_Id = gcnew String(pOutID);

Done:;
	//Libera a memória para a string.
	DeletarStringCoTaskSafe(&pOutID);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o comprimento da sequência do id do elemento que age como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
/// </summary>
/// <param name="Param_Out_Largura">Retorna o comprimento da sequência do id elemento que age como o servidor de tinta. O comprimento da corda retornado não inclui 
/// espaço para o exterminador nulo.</param>
void CarenD2D1SvgPaint::GetIdLength([Out] UInt32% Param_Out_Largura)
{
	//Chama o método para realizar a operação.
	Param_Out_Largura = PonteiroTrabalho->GetIdLength();
}

/// <summary>
/// Obtém o tipo de tinta. 
/// </summary>
/// <param name="Param_Out_PaintType">Retorna um Enum para o tipo de tinta.</param>
void CarenD2D1SvgPaint::GetPaintType([Out] CA_D2D1_SVG_PAINT_TYPE% Param_Out_PaintType)
{
	//Variaveis a serem utilizadas.
	D2D1_SVG_PAINT_TYPE OutSvgPaintType;

	//Chama o método para realizar a operação.
	OutSvgPaintType = PonteiroTrabalho->GetPaintType();

	//Converte e define no parametro de saida.
	Param_Out_PaintType = static_cast<CA_D2D1_SVG_PAINT_TYPE>(OutSvgPaintType);
}

/// <summary>
/// Define a cor da tinta usada se o tipo de tinta estiver D2D1_SVG_PAINT_TYPE_COLOR. 
/// </summary>
/// <param name="Param_Color">Uma estrutura(CA_D2D1_COLOR_F) com a nova cor da tinta.</param>
CarenResult CarenD2D1SvgPaint::SetColor(CA_D2D1_COLOR_F^ Param_Color)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColor = NULL;

	//Converte a estrutura.
	pColor = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Color);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetColor(*pColor);

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
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pColor);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o id de elemento que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI. 
/// </summary>
/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
CarenResult CarenD2D1SvgPaint::SetId(String^ Param_Id)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pId = NULL;

	//Converte a string gerenciada para nativa.
	pId = Util.ConverterStringToWCHAR(Param_Id);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetId(pId);

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
	//Libera a memória para a string.
	DeletarStringAllocatedSafe(&pId);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o tipo de tinta. 
/// </summary>
/// <param name="Param_PaintType">Um enum que define o novo tipo de tinta.</param>
CarenResult CarenD2D1SvgPaint::SetPaintType(CA_D2D1_SVG_PAINT_TYPE Param_PaintType)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetPaintType(static_cast<D2D1_SVG_PAINT_TYPE>(Param_PaintType));

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




// Métodos da interface proprietária(ICarenD2D1SvgAttribute)


/// <summary>
/// Cria um clone desse valor de atributo. Na criação, o atributo clonado não é definido em nenhum elemento. 
/// </summary>
/// <param name="Param_Out_CloneInterface">Retorna uma interface(ICarenD2D1SvgAttribute) do atributo clonado.</param>
CarenResult CarenD2D1SvgPaint::Clone([Out] ICarenD2D1SvgAttribute^% Param_Out_CloneInterface)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgAttribute* pOutClone = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Clone(&pOutClone);
	;
	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_CloneInterface = gcnew CarenD2D1SvgAttribute();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutClone, Param_Out_CloneInterface, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna o elemento no qual este atributo é definido. Retorna nulo se o atributo não estiver definido em nenhum elemento. 
/// </summary>
/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém um ponteiro parao elemtno no qual este atributo é definido. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgPaint::GetElement(ICaren^ Param_Out_SvgElement)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetElement(&pOutSvgElement);

	//Define o ponteiro na interface inicializada pelo usuário.
	Param_Out_SvgElement->AdicionarPonteiro(pOutSvgElement);
}





// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgPaint::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}