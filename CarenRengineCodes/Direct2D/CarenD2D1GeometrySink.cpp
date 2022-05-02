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
#include "CarenD2D1GeometrySink.h"

//Destruidor.
CarenD2D1GeometrySink::~CarenD2D1GeometrySink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1GeometrySink::CarenD2D1GeometrySink()
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
CarenResult CarenD2D1GeometrySink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GeometrySink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GeometrySink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GeometrySink**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1GeometrySink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1GeometrySink*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1GeometrySink**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GeometrySink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1GeometrySink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1GeometrySink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1GeometrySink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1GeometrySink::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1GeometrySink::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1GeometrySink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1GeometrySink();
}



// Métodos da interface proprietária(ICarenD2D1GeometrySink)


/// <summary>
/// Adiciona um único arco à geometria do caminho. 
/// </summary>
/// <param name="Param_Arc">O segmento de arco para adicionar à figura.</param>
void CarenD2D1GeometrySink::AddArc(CA_D2D1_ARC_SEGMENT^ Param_Arc)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ARC_SEGMENT* pArcSegment = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pArcSegment = Util.ConverterD2D1_ARC_SEGMENTManagedToUnmanaged(Param_Arc);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddArc(pArcSegment);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pArcSegment);
}

/// <summary>
/// Cria uma curva bezier cúbica entre o ponto atual e o ponto final especificado.
/// </summary>
/// <param name="Param_Bezier">Uma estrutura que descreve os pontos de controle e o ponto final da curva Bezier para adicionar.</param>
void CarenD2D1GeometrySink::AddBezier(CA_D2D1_BEZIER_SEGMENT^ Param_Bezier)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BEZIER_SEGMENT* pBezier = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pBezier = Util.ConverterD2D1_BEZIER_SEGMENTManagedToUnmanaged(Param_Bezier);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddBezier(pBezier);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pBezier);
}

/// <summary>
/// Cria um segmento de linha entre o ponto atual e o ponto final especificado e adiciona-o à pia de geometria. 
/// </summary>
/// <param name="Param_Point">O ponto final da linha para desenhar.</param>
void CarenD2D1GeometrySink::AddLine(CA_D2D1_POINT_2F^ Param_Point)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddLine(*pPoint);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pPoint);
}

/// <summary>
/// Cria uma curva bezier quadrática entre o ponto atual e o ponto final especificado. 
/// </summary>
/// <param name="Param_Bezier">Uma estrutura que descreve o ponto de controle e o ponto final da curva quadrática de Bezier para adicionar.</param>
void CarenD2D1GeometrySink::AddQuadraticBezier(CA_D2D1_QUADRATIC_BEZIER_SEGMENT^ Param_Bezier)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_QUADRATIC_BEZIER_SEGMENT* pQuadraticBezier = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddQuadraticBezier(pQuadraticBezier);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pQuadraticBezier);
}

/// <summary>
/// Adiciona uma sequência de segmentos de Bezier quadráticos como uma matriz em uma única chamada. 
/// </summary>
/// <param name="Param_ArrayBeziers">Uma matriz de uma sequência de segmentos quadráticos de Bezier.</param>
/// <param name="Param_QuantidadeBeziers">Um valor indicando o número de segmentos de Bezier quadráticos em beziers.</param>
void CarenD2D1GeometrySink::AddQuadraticBeziers(
cli::array<CA_D2D1_QUADRATIC_BEZIER_SEGMENT^>^ Param_ArrayBeziers,
UInt32 Param_QuantidadeBeziers)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_QUADRATIC_BEZIER_SEGMENT* pMatrizBezier = CriarMatrizEstruturas<D2D1_QUADRATIC_BEZIER_SEGMENT>(Param_QuantidadeBeziers);
	D2D1_QUADRATIC_BEZIER_SEGMENT* pBezier = NULL;

	//Faz um for para converter de definir os dados.
	for (UINT32 i = 0; i < Param_QuantidadeBeziers; i++)
	{
		//Converte a estrutura gerenciada.
		pBezier = Util.ConverterD2D1_QUADRATIC_BEZIER_SEGMENTManagedToUnmanaged(Param_ArrayBeziers[i]);

		//Define na matriz de estruturas.
		pMatrizBezier[i] = *pBezier;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pBezier);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddQuadraticBeziers(pMatrizBezier, Param_QuantidadeBeziers);

	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizBezier);
}




// Métodos da interface (ICarenD2D1SimplifiedGeometrySink)


/// <summary>
/// Cria uma sequência de curvas Cubicas de Bezier e as adiciona ao Geometry Sink.
/// </summary>
/// <param name="Param_ArrayBeziers">Uma matriz de segmentos Bezier que descreve as curvas bezier para criar. Uma curva é extraída do ponto atual do Geometry Sink (o ponto final do último segmento 
/// desenhado ou o local especificado pela BeginFigure) até o ponto final do primeiro segmento Bezier na matriz. se a matriz contiver segmentos bezier adicionais, cada segmento Bezier subsequente usa
/// o ponto final do segmento Bezier anterior como seu ponto de partida.</param>
/// <param name="Param_QuantidadeBeziers">O número de segmentos Bezier na matriz (Param_ArrayBeziers).</param>
void CarenD2D1GeometrySink::AddBeziers(
	cli::array<CA_D2D1_BEZIER_SEGMENT^>^ Param_ArrayBeziers,
	UInt32 Param_QuantidadeBeziers)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BEZIER_SEGMENT* pMatrizBezier = CriarMatrizEstruturas<D2D1_BEZIER_SEGMENT>(Param_QuantidadeBeziers);
	D2D1_BEZIER_SEGMENT* pBezier = NULL;

	//Faz um for para converter de definir os dados.
	for (UINT32 i = 0; i < Param_QuantidadeBeziers; i++)
	{
		//Converte a estrutura gerenciada.
		pBezier = Util.ConverterD2D1_BEZIER_SEGMENTManagedToUnmanaged(Param_ArrayBeziers[i]);

		//Define na matriz de estruturas.
		pMatrizBezier[i] = *pBezier;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pBezier);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddBeziers(pMatrizBezier, Param_QuantidadeBeziers);

	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizBezier);
}

/// <summary>
/// Cria uma sequência de linhas usando os pontos especificados e adiciona-os ao Geometry Sink. 
/// </summary>
/// <param name="Param_ArrayPoints">uma matriz de um ou mais pontos que descrevem as linhas a desenhar. Uma linha é desenhada do ponto atual do Geometry Sink (o ponto final do último segmento desenhado 
/// ou o local especificado pela BeginFigure) até o primeiro ponto da matriz. se a matriz contiver pontos adicionais, uma linha é desenhada do primeiro ponto para o segundo ponto na matriz, do segundo ponto 
/// ao terceiro ponto, e assim por diante.</param>
/// <param name="Param_QuantidadePontos">O número de pontos na matriz (Param_ArrayPoints).</param>
void CarenD2D1GeometrySink::AddLines(
	cli::array<CA_D2D1_POINT_2F^>^ Param_ArrayPoints,
	UInt32 Param_QuantidadePontos)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMatrizPoints = CriarMatrizEstruturas<D2D1_POINT_2F>(Param_QuantidadePontos);
	D2D1_POINT_2F* pPoint = NULL;

	//Faz um for para converter de definir os dados.
	for (UINT32 i = 0; i < Param_QuantidadePontos; i++)
	{
		//Converte a estrutura gerenciada.
		pPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_ArrayPoints[i]);

		//Define na matriz de estruturas.
		pMatrizPoints[i] = *pPoint;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pPoint);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->AddLines(pMatrizPoints, Param_QuantidadePontos);

	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizPoints);
}

/// <summary>
/// Inicia uma nova figura no ponto especificado. 
/// Se esse método for chamado enquanto uma figura estiver em andamento, a interface será invalidada e todos os métodos futuros falharão.
/// </summary>
/// <param name="Param_StartPoint">O ponto para começar a nova figura.</param>
/// <param name="Param_InicioFigura">Se a nova figura deve ser oca ou preenchida.</param>
void CarenD2D1GeometrySink::BeginFigure(
	CA_D2D1_POINT_2F^ Param_StartPoint,
	CA_D2D1_FIGURE_BEGIN Param_InicioFigura)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pStartPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_StartPoint);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->BeginFigure(*pStartPoint, static_cast<D2D1_FIGURE_BEGIN>(Param_InicioFigura));

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pStartPoint);
}

/// <summary>
/// Fecha o Geometry Sink, indica se está em estado de erro e redefine o estado de erro do Sink.
/// Não feche o Geometry Sink enquanto uma figura ainda está em andamento; fazendo isso coloca o Geometry Sink em um estado de erro. Para que a operação seja bem sucedida, deve haver uma chamada EndFigure 
/// para cada chamada para BeginFigure.
/// </summary>
CarenResult CarenD2D1GeometrySink::Close()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Close();

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

/// <summary>
/// Termina a figura atual; opcionalmente, fecha-o.
/// Chamar este método sem uma chamada correspondente ao BeginFigure coloca o Geometry Sink em um estado de erro; chamadas subsequentes são ignoradas, e a falha geral será devolvida quando o método 
/// Close for chamado.
/// </summary>
/// <param name="Param_FinalFigura">Um valor que indica se o valor atual está fechado. Se o valor for fechado, uma linha será traçada entre o ponto atual e o ponto de partida especificado 
/// pela BeginFigure.</param>
void CarenD2D1GeometrySink::EndFigure(CA_D2D1_FIGURE_END Param_FinalFigura)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->EndFigure(static_cast<D2D1_FIGURE_END>(Param_FinalFigura));
}

/// <summary>
/// Especifica o método usado para determinar quais pontos estão dentro da geometria descrita por esta Geometry Sink e quais pontos estão fora. 
/// O modo de preenchimento é padrão para D2D1_FILL_MODE_ALTERNATE. Para definir o modo de preenchimento, ligue para SetFillMode antes da primeira chamada para BeginFigure. Não fazer vai colocar o 
/// Geometry Sink em um estado de erro.
/// </summary>
/// <param name="Param_ModoPreencher">O método utilizado para determinar se um determinado ponto faz parte da geometria.</param>
void CarenD2D1GeometrySink::SetFillMode(CA_D2D1_FILL_MODE Param_ModoPreencher)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetFillMode(static_cast<D2D1_FILL_MODE>(Param_ModoPreencher));
}

/// <summary>
/// Especifica as opções de traçado e de adesão a serem aplicadas a novos segmentos adicionados ao Geometry Sink. 
/// Após a chamada esse método, as bandeiras do segmento especificadas são aplicadas a cada segmento posteriormente adicionadas ao Sink. As bandeiras do segmento são aplicadas a cada segmento adicional até que 
/// este método seja chamado novamente e um conjunto diferente de bandeiras do segmento seja especificado.
/// </summary>
/// <param name="Param_FlagsVertex">As opções do Stroke e o Join a serem aplicadas a novos segmentos adicionados ao Geometry Sink.</param>
void CarenD2D1GeometrySink::SetSegmentFlags(CA_D2D1_PATH_SEGMENT Param_FlagsVertex)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetSegmentFlags(static_cast<D2D1_PATH_SEGMENT>(Param_FlagsVertex));
}