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
#include "CarenD2D1GradientStopCollection.h"

//Destruidor.
CarenD2D1GradientStopCollection::~CarenD2D1GradientStopCollection()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1GradientStopCollection::CarenD2D1GradientStopCollection()
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
CarenResult CarenD2D1GradientStopCollection::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GradientStopCollection::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GradientStopCollection*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GradientStopCollection**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GradientStopCollection::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GradientStopCollection*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GradientStopCollection**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GradientStopCollection::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GradientStopCollection::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1GradientStopCollection::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1GradientStopCollection::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1GradientStopCollection::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1GradientStopCollection::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1GradientStopCollection::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1GradientStopCollection::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1GradientStopCollection();
}



// Métodos da interface proprietária(ICarenD2D1GradientStopCollection)


/// <summary>
/// Indica o espaço gama em que as paradas gradientes são interpoladas.
/// </summary>
/// <param name="Param_Out_GammaSpace">Retorna o espaço gama em que as paradas gradientes são interpoladas.</param>
void CarenD2D1GradientStopCollection::GetColorInterpolationGamma([Out] CA_D2D1_GAMMA% Param_Out_GammaSpace)
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
void CarenD2D1GradientStopCollection::GetExtendMode([Out] CA_D2D1_EXTEND_MODE% Param_Out_ExtendMode)
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
void CarenD2D1GradientStopCollection::GetGradientStopCount([Out] UInt32% Param_Out_CountGradientes)
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
void CarenD2D1GradientStopCollection::GetGradientStops(
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
void CarenD2D1GradientStopCollection::GetFactory(ICaren^ Param_Out_Factory)
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