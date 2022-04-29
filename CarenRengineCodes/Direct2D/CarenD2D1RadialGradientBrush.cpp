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
#include "CarenD2D1RadialGradientBrush.h"

//Destruidor.
CarenD2D1RadialGradientBrush::~CarenD2D1RadialGradientBrush()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1RadialGradientBrush::CarenD2D1RadialGradientBrush()
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
CarenResult CarenD2D1RadialGradientBrush::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RadialGradientBrush::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1RadialGradientBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1RadialGradientBrush**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RadialGradientBrush::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1RadialGradientBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1RadialGradientBrush**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1RadialGradientBrush::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1RadialGradientBrush::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1RadialGradientBrush::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1RadialGradientBrush::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1RadialGradientBrush::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1RadialGradientBrush::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1RadialGradientBrush::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1RadialGradientBrush::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1RadialGradientBrush();
}



// Métodos da interface proprietária(ICarenD2D1RadialGradientBrush)


/// <summary>
/// Recupera o centro da elipse gradiente.
/// </summary>
/// <param name="Param_Out_Center">Retorna o centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::GetCenter([Out] CA_D2D1_POINT_2F^% Param_Out_Center)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F OutPoint2F;

	//Chama o método para realizar a operação.
	OutPoint2F = PonteiroTrabalho->GetCenter();

	//Converte a estrutura e define no parametro de saida.
	Param_Out_Center = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutPoint2F);
}

/// <summary>
/// Recupera o deslocamento da origem gradiente em relação ao centro da elipse gradiente. 
/// </summary>
/// <param name="Param_Out_GradientOriginOffset">Retorna A compensação da origem gradiente do centro da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::GetGradientOriginOffset([Out] CA_D2D1_POINT_2F^% Param_Out_GradientOriginOffset)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F OutGradientOrigin;

	//Chama o método para realizar a operação.
	OutGradientOrigin = PonteiroTrabalho->GetGradientOriginOffset();

	//Converte a estrutura e define no parametro de saida.
	Param_Out_GradientOriginOffset = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutGradientOrigin);
}

/// <summary>
/// Recupera a ICarenD2D1GradientStopCollection associada a este objeto do Brush de gradiente radial. 
/// </summary>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection associado a este objeto de pincel gradiente linear. Este parâmetro é passado unnitializado.</param>
CarenResult CarenD2D1RadialGradientBrush::GetGradientStopCollection(
[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1GradientStopCollection* pGradientStop = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetGradientStopCollection(&pGradientStop);
	
	//Verifica se o ponteiro é valido
	if (!ObjetoValido(pGradientStop))
	{
		//Ponteiro invalido

		//Define erro.
		SetCarenErro(Resultado, ResultCode::ER_E_POINTER);

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Adiciona o ponteiro a interface.
	Resultado = Param_Out_GradientStopCollection->AdicionarPonteiro(pGradientStop);

	//Verifica o resultado da operação.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao adicionar o ponteiro.

		//Libera o ponteiro para a interface recuperada.
		pGradientStop->Release();
		pGradientStop = NULL;

		//Libera a interface gerenciada.
		Param_Out_GradientStopCollection->Finalizar();
		Param_Out_GradientStopCollection = nullptr;

		//Deixa o método continuar.
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o raio X da elipse gradiente. 
/// </summary>
/// <param name="Param_Out_RadiusX">Retorna raio X da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::GetRadiusX([Out] float% Param_Out_RadiusX)
{
	//Chama o método para realizar a operação.
	Param_Out_RadiusX = PonteiroTrabalho->GetRadiusX();
}

/// <summary>
/// Recupera o raio Y da elipse gradiente. 
/// </summary>
/// <param name="Param_Out_RadiusY">Retorna raio Y da elipse gradiente. Este valor é expresso no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::GetRadiusY([Out] float% Param_Out_RadiusY)
{
	//Chama o método para realizar a operação.
	Param_Out_RadiusY = PonteiroTrabalho->GetRadiusY();
}

/// <summary>
/// Especifica o centro da elipse gradiente no espaço de coordenadas do Brush. 
/// </summary>
/// <param name="Param_Center">O centro da elipse gradiente, no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::SetCenter(CA_D2D1_POINT_2F^ Param_Center)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint2F = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pPoint2F = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Center);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetCenter(*pPoint2F);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pPoint2F);
}

/// <summary>
/// Especifica a compensação da origem gradiente em relação ao centro da elipse gradiente. 
/// </summary>
/// <param name="Param_GradientOriginOffset">A compensação da origem gradiente do centro da elipse gradiente.</param>
void CarenD2D1RadialGradientBrush::SetGradientOriginOffset(CA_D2D1_POINT_2F^ Param_GradientOriginOffset)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pGradientOrigin = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pGradientOrigin = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_GradientOriginOffset);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetGradientOriginOffset(*pGradientOrigin);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pGradientOrigin);
}

/// <summary>
/// Especifica o raio X da elipse gradiente, no espaço de coordenadas do Brush. 
/// </summary>
/// <param name="Param_RadiusX">O raio X da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::SetRadiusX(float Param_RadiusX)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetRadiusX(Param_RadiusX);
}

/// <summary>
/// Especifica o raio Y da elipse gradiente, no espaço de coordenadas da escova. 
/// </summary>
/// <param name="Param_RadiusY">O raio Y da elipse gradiente. Este valor está no espaço de coordenadas do pincel.</param>
void CarenD2D1RadialGradientBrush::SetRadiusY(float Param_RadiusY)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetRadiusY(Param_RadiusY);
}



// Métodos da interface (ICarenD2D1Brush)


/// <summary>
/// Obtém o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1RadialGradientBrush::GetOpacity([Out] float% Param_Out_Opacidade)
{
	//Chama o método para realizar a operação e define no parametro de saida.
	Param_Out_Opacidade = PonteiroTrabalho->GetOpacity();
}

/// <summary>
/// A transformação é aplicada a este pincel.
/// </summary>
/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
void CarenD2D1RadialGradientBrush::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F OutTransform;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTransform(&OutTransform);

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_Matrix = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutTransform);
}

/// <summary>
/// Define o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1RadialGradientBrush::SetOpacity(float Param_Opacidade)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetOpacity(Param_Opacidade);
}

/// <summary>
/// Define a transformação aplicada ao pincel.
/// </summary>
/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
void CarenD2D1RadialGradientBrush::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pTransform = NULL;

	//Converte a estrutura nativa para a gerenciada.
	pTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTransform(pTransform);

	//Libera a memória para a estrutura criada.
	DeletarEstruturaSafe(&pTransform);
}


// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1RadialGradientBrush::GetFactory(ICaren^ Param_Out_Factory)
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