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
#include "CarenD2D1StrokeStyle1.h"

//Destruidor.
CarenD2D1StrokeStyle1::~CarenD2D1StrokeStyle1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1StrokeStyle1::CarenD2D1StrokeStyle1()
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
CarenResult CarenD2D1StrokeStyle1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1StrokeStyle1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1StrokeStyle1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1StrokeStyle1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1StrokeStyle1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1StrokeStyle1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1StrokeStyle1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1StrokeStyle1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1StrokeStyle1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1StrokeStyle1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1StrokeStyle1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1StrokeStyle1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1StrokeStyle1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1StrokeStyle1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1StrokeStyle1();
}



// Métodos da interface proprietária(ICarenD2D1StrokeStyle1)


/// <summary>
/// Recebe o tipo de transformação do Stroke.
/// </summary>
/// <param name="Param_Out_StrokeTransformType">Retorna o tipo de transformação de traçado.</param>
void CarenD2D1StrokeStyle1::GetStrokeTransformType(
[Out] CA_D2D1_STROKE_TRANSFORM_TYPE% Param_Out_StrokeTransformType)
{
	//Variaveis a serem utilizadas.
	D2D1_STROKE_TRANSFORM_TYPE StrokeTransform;

	//Chama o método para realizar a operação.
	StrokeTransform = PonteiroTrabalho->GetStrokeTransformType();

	//Converte e define no parametro de saida.
	Param_Out_StrokeTransformType = static_cast<CA_D2D1_STROKE_TRANSFORM_TYPE>(StrokeTransform);
}




// Métodos da interface proprietária(ICarenD2D1StrokeStyle)


/// <summary>
/// Obtém um valor que especifica como as extremidades de cada traço são desenhadas.
/// </summary>
/// <param name="Param_Out_EndDashStyle">Retorna um valor que especifica como as extremidades de cada traço são desenhadas.</param>
void CarenD2D1StrokeStyle1::GetDashCap([Out] CA_D2D1_CAP_STYLE% Param_Out_EndDashStyle)
{
	//Variaveis a serem utilizadas.
	D2D1_CAP_STYLE CapStyle;

	//Chama o método para realizar a operação.
	CapStyle = PonteiroTrabalho->GetDashCap();

	//Converte e define no parametro de saida.
	Param_Out_EndDashStyle = static_cast<CA_D2D1_CAP_STYLE>(CapStyle);
}

/// <summary>
/// Copia o padrão do painel para a matriz especificada. 
/// Os traços(Dashes) são especificados em unidades que são um múltiplo da largura do traçado, com membros subsequentes da matriz indicando os traços e lacunas entre traços: a primeira entrada indica 
/// um traço preenchido, o segundo uma lacuna, e assim por diante.
/// </summary>
/// <param name="Param_Out_ArrayDashes">Retorna uma matriz que receberá o padrão de traço. A matriz deve ser capaz de conter pelo menos tantos elementos quanto especificado pelo Param_Quantidade.</param>
/// <param name="Param_Quantidade">O número de traços para copiar. Se esse valor for menor do que o número de traços na matriz de traços de Stroke Style, os traços retornados são truncados para Param_Quantidade. 
/// Se esse valor for maior do que o número de traços na matriz de Stroke Styles, os traços extras são definidos como 0.0f. Para obter o número real de traços na matriz de traços do estilo de traçado, 
/// use o método GetDashesCount.</param>
void CarenD2D1StrokeStyle1::GetDashes(
	[Out] cli::array<float>^% Param_Out_ArrayDashes,
	UInt32 Param_Quantidade)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	float* pMatrizDashes = CriarMatrizUnidimensional<float>(Param_Quantidade);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDashes(pMatrizDashes, Param_Quantidade);

	//Cria a matriz gerenciada que vai conter os dados.
	Param_Out_ArrayDashes = gcnew cli::array<float>(Param_Quantidade);

	//Chama o método para copiar os dados para a matriz gerenciada.
	Util.CopiarBufferNativo_ToGerenciado(&pMatrizDashes, Param_Out_ArrayDashes, Param_Quantidade);

	//Libera a memória para a matriz gerenciada.
	DeletarMatrizUnidimensionalSafe(&pMatrizDashes);
}

/// <summary>
/// Recupera o número de entradas na matriz de traços. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de entradas na matriz de traços se o traçado for tracejado; caso contrário, 0.</param>
void CarenD2D1StrokeStyle1::GetDashesCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetDashesCount();
}

/// <summary>
/// Recupera um valor que especifica até que ponto na sequência do painel o traçado começará. 
/// </summary>
/// <param name="Param_Out_Offset">Recupera um valor que especifica até que ponto na sequência do traço o traçado começará.</param>
void CarenD2D1StrokeStyle1::GetDashOffset([Out] float% Param_Out_Offset)
{
	//Chama o método para realizar a operação.
	Param_Out_Offset = PonteiroTrabalho->GetDashOffset();
}

/// <summary>
/// Obtém um valor que descreve o padrão de traço do traçado. 
/// </summary>
/// <param name="Param_Out_DashStyleUsado">Recupera um valor que descreve o padrão de traço predefinido usado ou D2D1_DASH_STYLE_CUSTOM de (CA_D2D1_DASH_STYLE) se um estilo de painel personalizado for usado.</param>
void CarenD2D1StrokeStyle1::GetDashStyle([Out] CA_D2D1_DASH_STYLE% Param_Out_DashStyleUsado)
{
	//Variaveis a serem utilizadas.
	D2D1_DASH_STYLE DashStyle;

	//Chama o método para realizar a operação.
	DashStyle = PonteiroTrabalho->GetDashStyle();

	//Converte e define no parametro de saida.
	Param_Out_DashStyleUsado = static_cast<CA_D2D1_DASH_STYLE>(DashStyle);
}

/// <summary>
/// Recupera o tipo de forma usada no final de um curso. 
/// </summary>
/// <param name="Param_Out_TipoEndShape">Retorna o tipo de forma usada no final de um curso.</param>
void CarenD2D1StrokeStyle1::GetEndCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoEndShape)
{
	//Variaveis a serem utilizadas.
	D2D1_CAP_STYLE CapStyle;

	//Chama o método para realizar a operação.
	CapStyle = PonteiroTrabalho->GetEndCap();

	//Converte e define no parametro de saida.
	Param_Out_TipoEndShape = static_cast<CA_D2D1_CAP_STYLE>(CapStyle);
}

/// <summary>
/// Recupera o tipo de articulação usada nos vértices do contorno de uma forma. 
/// </summary>
/// <param name="Param_Out_TipoJoint">Recupera um valor que especifica o tipo de articulação usada nos vértices do contorno de uma forma.</param>
void CarenD2D1StrokeStyle1::GetLineJoin([Out] CA_D2D1_LINE_JOIN% Param_Out_TipoJoint)
{
	//Variaveis a serem utilizadas.
	D2D1_LINE_JOIN LineJoin;

	//Chama o método para realizar a operação.
	LineJoin = PonteiroTrabalho->GetLineJoin();

	//Converte e define no parametro de saida.
	Param_Out_TipoJoint = static_cast<CA_D2D1_LINE_JOIN>(LineJoin);
}

/// <summary>
/// Recupera o limite na razão do comprimento do miter para metade da espessura do traçado. 
/// </summary>
/// <param name="Param_Out_Limite">Recupera um número positivo maior ou igual a 1.0f que descreve o limite na razão do comprimento do miter para metade da espessura do traçado.</param>
void CarenD2D1StrokeStyle1::GetMiterLimit([Out] float% Param_Out_Limite)
{
	//Chama o método para realizar a operação.
	Param_Out_Limite = PonteiroTrabalho->GetMiterLimit();
}

/// <summary>
/// Recupera o tipo de forma usada no início de um Stroke. 
/// </summary>
/// <param name="Param_Out_TipoStartShape">Retorna o tipo de forma usada no início de um Stroke.</param>
void CarenD2D1StrokeStyle1::GetStartCap([Out] CA_D2D1_CAP_STYLE% Param_Out_TipoStartShape)
{
	//Variaveis a serem utilizadas.
	D2D1_CAP_STYLE CapStyle;

	//Chama o método para realizar a operação.
	CapStyle = PonteiroTrabalho->GetStartCap();

	//Converte e define no parametro de saida.
	Param_Out_TipoStartShape = static_cast<CA_D2D1_CAP_STYLE>(CapStyle);
}




// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1StrokeStyle1::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}