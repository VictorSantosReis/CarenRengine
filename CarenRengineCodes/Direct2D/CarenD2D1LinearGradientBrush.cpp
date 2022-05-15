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
#include "CarenD2D1LinearGradientBrush.h"

//Destruidor.
CarenD2D1LinearGradientBrush::~CarenD2D1LinearGradientBrush()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1LinearGradientBrush::CarenD2D1LinearGradientBrush()
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
CarenResult CarenD2D1LinearGradientBrush::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1LinearGradientBrush::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1LinearGradientBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1LinearGradientBrush**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1LinearGradientBrush::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1LinearGradientBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1LinearGradientBrush**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1LinearGradientBrush::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1LinearGradientBrush::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1LinearGradientBrush::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1LinearGradientBrush::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1LinearGradientBrush::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1LinearGradientBrush::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1LinearGradientBrush::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1LinearGradientBrush();
}



// Métodos da interface proprietária(ICarenD2D1LinearGradientBrush)


/// <summary>
/// Recupera as coordenadas finais do gradiente linear. 
/// </summary>
/// <param name="Param_Out_EndPoint">Retorna as coordenadas bidimensionais finais do gradiente linear, no espaço de coordenadas do pincel.</param>
void CarenD2D1LinearGradientBrush::GetEndPoint([Out] CA_D2D1_POINT_2F^% Param_Out_EndPoint)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F OutPoint2F = { };

	//Chama o método para realizar a operação.
	OutPoint2F = PonteiroTrabalho->GetEndPoint();

	//Converte e define no parametro de saida.
	Param_Out_EndPoint = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutPoint2F);
}

/// <summary>
/// Recupera a ICarenD2D1GradientStopCollection associada a este pincel gradiente linear. 
/// ICarenD2D1GradientStopCollection contém uma série de estruturas e informações CA_D2D1_GRADIENT_STOP, como o modo de extensão e o modo de interpolação de cores.
/// </summary>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ID2D1GradientStopCollection associado a este objeto de pincel gradiente linear.</param>
CarenResult CarenD2D1LinearGradientBrush::GetGradientStopCollection(
[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1GradientStopCollection* pGradientStop = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetGradientStopCollection(&pGradientStop);

	//Verifica se a interface é valida.
	if (!ObjetoValido(pGradientStop))
	{
		//A interface não é valida.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		Sair;
	}

	//Cria a interface que vai conter o ponteiro.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Adiciona o ponteiro a interface
	Resultado = Param_Out_GradientStopCollection->AdicionarPonteiro(pGradientStop);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado)) {
		//Falhou ao definir o ponteiro.

		//Libera a interface
		pGradientStop->Release();
		pGradientStop = NULL;
		Param_Out_GradientStopCollection->Finalizar();
		Param_Out_GradientStopCollection = nullptr;

		//Deixa continuar para sair.
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera as coordenadas iniciais do gradiente linear.
/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
/// o ponto de partida e o ponto final do pincel também serão transformados.
/// </summary>
/// <param name="Param_Out_StartPoint">Retorna as coordenadas bidimensionais iniciais do gradiente linear, no espaço de coordenadas da escova.</param>
void CarenD2D1LinearGradientBrush::GetStartPoint([Out] CA_D2D1_POINT_2F^% Param_Out_StartPoint)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F OutPoint2F = { };

	//Chama o método para realizar a operação.
	OutPoint2F = PonteiroTrabalho->GetStartPoint();

	//Converte e define no parametro de saida.
	Param_Out_StartPoint = Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutPoint2F);
}

/// <summary>
/// Define as coordenadas finais do gradiente linear no espaço de coordenadas do Brush.
/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
/// o ponto de partida e o ponto final do pincel também serão transformados.
/// </summary>
/// <param name="Param_EndPoint">As coordenadas bidimensionais finais do gradiente linear, no espaço de coordenadas do pincel.</param>
void CarenD2D1LinearGradientBrush::SetEndPoint(CA_D2D1_POINT_2F^ Param_EndPoint)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F *pEndPointSet;

	//Converte a estrutura gerenciada para nativa.
	pEndPointSet = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_EndPoint);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetEndPoint(*pEndPointSet);

	//Libera a memória para a matriz.
	DeletarEstruturaSafe(&pEndPointSet);
}

/// <summary>
/// Define as coordenadas iniciais do gradiente linear no espaço de coordenadas do Brush.
/// O ponto de partida e o ponto final são descritos no espaço do Brush e são mapeados para o alvo de renderização quando o pincel é usado. Se houver uma transformação de pincel não-identidade ou transformação de alvo, 
/// o ponto de partida e o ponto final do pincel também serão transformados.
/// </summary>
/// <param name="Param_StartPoint">As coordenadas bidimensionais iniciais do gradiente linear, no espaço de coordenadas da escova.</param>
void CarenD2D1LinearGradientBrush::SetStartPoint(CA_D2D1_POINT_2F^ Param_StartPoint)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pStartPointSet;

	//Converte a estrutura gerenciada para nativa.
	pStartPointSet = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_StartPoint);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetStartPoint(*pStartPointSet);

	//Libera a memória para a matriz.
	DeletarEstruturaSafe(&pStartPointSet);
}



// Métodos da interface proprietária(ICarenD2D1Brush)

/// <summary>
/// Obtém o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1LinearGradientBrush::GetOpacity([Out] float% Param_Out_Opacidade)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Brush::GetOpacity(PonteiroTrabalho,
		Param_Out_Opacidade
	);
}

/// <summary>
/// A transformação é aplicada a este pincel.
/// </summary>
/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
void CarenD2D1LinearGradientBrush::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Brush::GetTransform(PonteiroTrabalho,
		Param_Out_Matrix
	);
}

/// <summary>
/// Define o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1LinearGradientBrush::SetOpacity(float Param_Opacidade)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Brush::SetOpacity(PonteiroTrabalho,
		Param_Opacidade
	);
}

/// <summary>
/// Define a transformação aplicada ao pincel.
/// </summary>
/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
void CarenD2D1LinearGradientBrush::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Brush::SetTransform(PonteiroTrabalho,
		Param_Transform
	);
}





// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1LinearGradientBrush::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}