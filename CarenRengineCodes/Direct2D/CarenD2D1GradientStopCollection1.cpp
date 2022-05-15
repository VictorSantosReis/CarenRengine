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
#include "CarenD2D1GradientStopCollection1.h"

//Destruidor.
CarenD2D1GradientStopCollection1::~CarenD2D1GradientStopCollection1()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1GradientStopCollection1::CarenD2D1GradientStopCollection1()
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
CarenResult CarenD2D1GradientStopCollection1::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GradientStopCollection1::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GradientStopCollection1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GradientStopCollection1**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GradientStopCollection1::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GradientStopCollection1*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GradientStopCollection1**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GradientStopCollection1::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GradientStopCollection1::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1GradientStopCollection1::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1GradientStopCollection1::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1GradientStopCollection1::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1GradientStopCollection1::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1GradientStopCollection1::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1GradientStopCollection1();
}



// Métodos da interface proprietária(ICarenD2D1GradientStopCollection1)


/// <summary>
/// Obtém a precisão do Buffer de gradiente. 
/// Se esse objeto foi criado usando ICarenD2D1RenderTarget::CreateGradientStopCollection, este método retorna D2D1_BUFFER_PRECISION_8BPC_UNORM.
/// </summary>
/// <param name="Param_Out_PrecisaoBuffer">Retorna o Buffer de precisão do Gradiente.</param>
void CarenD2D1GradientStopCollection1::GetBufferPrecision([Out] CA_D2D1_BUFFER_PRECISION% Param_Out_PrecisaoBuffer)
{
	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION OutBufferPrecision;

	//Chama o método para realizar a operação.
	OutBufferPrecision = PonteiroTrabalho->GetBufferPrecision();

	//Converte e define no parametro de saida.
	Param_Out_PrecisaoBuffer = ConverterPara<CA_D2D1_BUFFER_PRECISION>(OutBufferPrecision);
}

/// <summary>
/// Recupera o modo de interpolação de cores que a coleção de parada de gradiente usa.
/// </summary>
/// <param name="Param_Out_InterpolationMode">Retorna o modo de interpolação de cores.</param>
void CarenD2D1GradientStopCollection1::GetColorInterpolationMode([Out] CA_D2D1_COLOR_INTERPOLATION_MODE% Param_Out_InterpolationMode)
{
	//Variaveis a serem utilizadas.
	D2D1_COLOR_INTERPOLATION_MODE OutColorInterpolationMode;

	//Chama o método para realizar a operação.
	OutColorInterpolationMode = PonteiroTrabalho->GetColorInterpolationMode();

	//Converte e define no parametro de saida.
	Param_Out_InterpolationMode = ConverterPara<CA_D2D1_COLOR_INTERPOLATION_MODE>(OutColorInterpolationMode);
}

/// <summary>
/// Copia as paradas de gradiente da coleção para a memória. 
/// </summary>
/// <param name="Param_Out_ArrayGradientStop">Retorna uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP.</param>
/// <param name="Param_QuantidadeGradientes">O número de gradientes para copiar. Se for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes sao omitidas. 
/// Se Param_QuantidadeGradientes for maior do que o número de paradas gradientes na coleção, as paradas de gradiente extra são definidas como NULO.</param>
void CarenD2D1GradientStopCollection1::GetGradientStops1(
[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
UInt32 Param_QuantidadeGradientes)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_STOP* pMatrizGradient = NULL;

	//Cria a Matriz unidimensional que vai receber os dados.
	pMatrizGradient = CriarMatrizUnidimensional<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetGradientStops1(pMatrizGradient, Param_QuantidadeGradientes);

	//Cria a matriz gerenciada que vai retornar os dados.
	Param_Out_ArrayGradientStop = gcnew cli::array<CA_D2D1_GRADIENT_STOP^>(Param_QuantidadeGradientes);

	//Copia os dados para a matriz.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		Param_Out_ArrayGradientStop[i]->position = pMatrizGradient[i].position;
		Param_Out_ArrayGradientStop[i]->color = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&pMatrizGradient[i].color);
	}

	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pMatrizGradient);
}

/// <summary>
/// Obtém o espaço de cores após a interpolação. 
/// </summary>
/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
void CarenD2D1GradientStopCollection1::GetPostInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor)
{
	//Variaveis a serem utilizadas.
	D2D1_COLOR_SPACE OutPostColorSpace;

	//Chama o método para realizar a operação.
	OutPostColorSpace = PonteiroTrabalho->GetPostInterpolationSpace();

	//Converte e define no parametro de saida.
	Param_Out_EspacoCor = ConverterPara<CA_D2D1_COLOR_SPACE>(OutPostColorSpace);
}

/// <summary>
/// Obtém o espaço de cores das cores de entrada, bem como o espaço em que as paradas gradientes são interpoladas. 
/// </summary>
/// <param name="Param_Out_EspacoCor">Retorna o espaço de cores.</param>
void CarenD2D1GradientStopCollection1::GetPreInterpolationSpace([Out] CA_D2D1_COLOR_SPACE% Param_Out_EspacoCor)
{
	//Variaveis a serem utilizadas.
	D2D1_COLOR_SPACE OutPreColorSpace;

	//Chama o método para realizar a operação.
	OutPreColorSpace = PonteiroTrabalho->GetPreInterpolationSpace();

	//Converte e define no parametro de saida.
	Param_Out_EspacoCor = ConverterPara<CA_D2D1_COLOR_SPACE>(OutPreColorSpace);
}



// Métodos da interface (ICarenD2D1GradientStopCollection)


/// <summary>
/// Indica o espaço gama em que as paradas gradientes são interpoladas.
/// </summary>
/// <param name="Param_Out_GammaSpace">Retorna o espaço gama em que as paradas gradientes são interpoladas.</param>
void CarenD2D1GradientStopCollection1::GetColorInterpolationGamma([Out] CA_D2D1_GAMMA% Param_Out_GammaSpace)
{
	//Variaveis a serem utilizadas.
	D2D1_GAMMA OutGamma;

	//Chama o método para realizar a operação.
	OutGamma = PonteiroTrabalho->GetColorInterpolationGamma();

	//Converte e define no parametro de saida.
	Param_Out_GammaSpace = ConverterPara<CA_D2D1_GAMMA>(OutGamma);
}

/// <summary>
/// Indica o comportamento do gradiente fora da faixa de gradiente normalizada. 
/// </summary>
/// <param name="Param_Out_ExtendMode">Retorna o comportamento do gradiente fora da faixa de gradiente normalizada.</param>
void CarenD2D1GradientStopCollection1::GetExtendMode([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendMode)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = PonteiroTrabalho->GetExtendMode();

	//Converte e define no parametro de saida.
	Param_Out_ExtendMode = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Recupera o número de paradas gradientes na coleção. 
/// </summary>
/// <param name="Param_Out_CountGradientes">Retorna o número de gradientes para na coleção.</param>
void CarenD2D1GradientStopCollection1::GetGradientStopCount([Out] UInt32% Param_Out_CountGradientes)
{
	//Chama o método para realizar a operação.
	Param_Out_CountGradientes = PonteiroTrabalho->GetGradientStopCount();
}

/// <summary>
/// Copia as paradas gradientes da coleção em uma matriz de estruturas D2D1_GRADIENT_STOP. 
/// </summary>
/// <param name="Param_Out_ArrayGradientStop">Uma matriz unidimensional de estruturas CA_D2D1_GRADIENT_STOP. Quando este método retorna, a matriz contém cópias do gradiente da coleção de parada.</param>
/// <param name="Param_QuantidadeGradientes">Um valor indicando o número de paradas gradientes para copiar. Se o valor for menor do que o número de paradas gradientes na coleção, as paradas de gradiente restantes 
/// são omitidas. Se o valor for maior do que o número de paradas de gradiente na coleção, as paradas de gradiente extra são definidas como NULO. Para obter o número de paradas gradientes na coleção, use o método 
/// GetGradientStopCount.</param>
void CarenD2D1GradientStopCollection1::GetGradientStops(
	[Out] cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_Out_ArrayGradientStop,
	UInt32 Param_QuantidadeGradientes)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_STOP* pMatrizGradient = NULL;

	//Cria a Matriz unidimensional que vai receber os dados.
	pMatrizGradient = CriarMatrizUnidimensional<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetGradientStops(pMatrizGradient, Param_QuantidadeGradientes);

	//Cria a matriz gerenciada que vai retornar os dados.
	Param_Out_ArrayGradientStop = gcnew cli::array<CA_D2D1_GRADIENT_STOP^>(Param_QuantidadeGradientes);

	//Copia os dados para a matriz.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		Param_Out_ArrayGradientStop[i]->position = pMatrizGradient[i].position;
		Param_Out_ArrayGradientStop[i]->color = Util.ConverterD2D1_COLOR_FUnmanagedToManaged(&pMatrizGradient[i].color);
	}

	//Libera a memória para a matriz.
	DeletarMatrizUnidimensionalSafe(&pMatrizGradient);
}





// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1GradientStopCollection1::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}