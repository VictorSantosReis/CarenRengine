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
#include "CarenD2D1Ink.h"

//Destruidor.
CarenD2D1Ink::~CarenD2D1Ink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1Ink::CarenD2D1Ink()
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
CarenResult CarenD2D1Ink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Ink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (Param_PonteiroNativo == IntPtr::Zero)
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método.
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID2D1Ink*>(Param_PonteiroNativo.ToPointer());

	//Verifica o ponteiro
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Define que o ponteiro foi definido com sucesso.
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Define falha na operação
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;

}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Ink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o objeto é valido
	if (!ObjetoValido(Param_PonteiroNativo))
	{
		//O objeto não é valido
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Converte o ponteiro para o tipo especifico da classe.
	PonteiroTrabalho = reinterpret_cast<ID2D1Ink*>(Param_PonteiroNativo);

	//Verifica se o ponteiro é valido
	if (ObjetoValido(PonteiroTrabalho))
	{
		//Ponteiro convertido com sucesso!

		//Define sucesso na operação
		Resultado.AdicionarCodigo(ResultCode::SS_OK, true);
	}
	else
	{
		//Falhou ao converter o ponteiro vazio para sua real representação.

		//Define falha no ponteiro
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);
	}

Done:;
	//Retornao resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Ink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Cria e define o ponteiro gerenciado no parametro de saida.
	Param_Out_PonteiroNativo = IntPtr((LPVOID)PonteiroTrabalho);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Ink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Define o ponteiro de trabalho no parametro de saida.
	*Param_Out_PonteiroNativo = PonteiroTrabalho;

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado
	return Resultado;

}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1Ink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Verifica se o ponteiro é valido
	if (!ObjetoValido(PonteiroTrabalho))
	{
		//O ponteiro de trabalho é invalido.
		Resultado.AdicionarCodigo(ResultCode::ER_E_POINTER, false);

		//Sai do método
		goto Done;
	}

	//Adiciona uma referência ao ponteiro
	ULONG CountRefs = PonteiroTrabalho->AddRef();

	//Libera a referência adicional
	PonteiroTrabalho->Release();

	//Decrementa o valor da quantidade de referência retornada em (-1) e define no parametro de saida.
	Param_Out_Referencias = static_cast<UInt64>(CountRefs - 1);

	//Define o resultado
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1Ink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1Ink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Ink::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Ink::LiberarReferencia()
{
	//Libera a referência e obtém a quantidade atual.
	ULONG RefCount = PonteiroTrabalho->Release();

	//Verifica se a quantidade é zero e se o ponteiro ainda é valido.
	//Se sim, vai deletar o ponteiro.
	if (RefCount == 0 && ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro vazio.
		PonteiroTrabalho = NULL;
	}
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1Ink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Ink();
}



// Métodos da interface proprietária(ICarenD2D1Ink)


/// <summary>
/// Adiciona os segmentos dado ao final deste objeto de tinta. 
/// </summary>
/// <param name="Param_Segments">Uma matriz de segmentos a serem adicionados a este objeto de tinta.</param>
/// <param name="Param_Quantidade">O número de segmentos a serem adicionados a este objeto de tinta.</param>
CarenResult CarenD2D1Ink::AddSegments(
cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^ Param_Segments,
UInt32 Param_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_BEZIER_SEGMENT* pMatrizBezier = CriarMatrizEstruturas<D2D1_INK_BEZIER_SEGMENT>(Param_Quantidade);
	D2D1_INK_BEZIER_SEGMENT* pBezierAuxiliar = NULL;

	//Copia os dados para a matriz nativa.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte a estrutura.
		pBezierAuxiliar = Util.ConverterD2D1_INK_BEZIER_SEGMENTManagedToUnmanaged(Param_Segments[i]);

		//Define os dados.
		pMatrizBezier[i] = *pBezierAuxiliar;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pBezierAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->AddSegments(pMatrizBezier, Param_Quantidade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizBezier);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupere os limites da geometria, com uma transformação aplicada opcional. 
/// </summary>
/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação dos limites deste objeto de tinta.</param>
/// <param name="Param_WorldTransform">A Wolrd Transform para ser usado na determinação dos limites deste objeto de tinta.</param>
/// <param name="Param_Out_Bounds">Retorna os limites deste objeto de tinta.</param>
CarenResult CarenD2D1Ink::GetBounds(
ICarenD2D1InkStyle^ Param_InkStyle,
CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
[Out] CA_D2D1_RECT_F^% Param_Out_Bounds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1InkStyle* pInkStyle = NULL;
	D2D1_MATRIX_3X2_F* pWorldTransform = NULL;
	D2D1_RECT_F OutBounds = {};

	//Recupera o ponteiro para o estilo de tinta.
	Resultado = RecuperarPonteiroCaren(Param_InkStyle, &pInkStyle);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura
	pWorldTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBounds(pInkStyle, pWorldTransform, &OutBounds);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutBounds);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pWorldTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna o número de segmentos neste objeto de tinta. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número de segmentos neste objeto de tinta.</param>
void CarenD2D1Ink::GetSegmentCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetSegmentCount();
}

/// <summary>
/// Recupera o subconjunto especificado de segmentos armazenados neste objeto de tinta. 
/// </summary>
/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser recuperado.</param>
/// <param name="Param_Out_Segments">Retorna uma matriz de segmentos recuperados.</param>
/// <param name="Param_Quantidade">O número de segmentos para recuperar. Observe que o (Param_Quantidade) deve ser menor ou igual ao número de segmentos no objeto de tinta menos (Param_StartSegments).</param>
CarenResult CarenD2D1Ink::GetSegments(
UInt32 Param_StartSegments,
[Out] cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Out_Segments,
UInt32 Param_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_BEZIER_SEGMENT* pOutMatrizBezier = CriarMatrizEstruturas<D2D1_INK_BEZIER_SEGMENT>(Param_Quantidade);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSegments(Param_StartSegments, pOutMatrizBezier, Param_Quantidade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a matriz que vai ser retornada.
	Param_Out_Segments = gcnew cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>(Param_Quantidade);

	//Copia os dados para a matriz de saida
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte e define no index
		Param_Out_Segments[i] = Util.ConverterD2D1_INK_BEZIER_SEGMENTUnmanagedToManaged(&pOutMatrizBezier[i]);
	}

Done:;
	//libera a memória para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pOutMatrizBezier);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o ponto de partida para este objeto de tinta. 
/// </summary>
/// <param name="Param_Out_Point">Retorna o ponto de partida para este objeto de tinta.</param>
void CarenD2D1Ink::GetStartPoint([Out] CA_D2D1_INK_POINT^% Param_Out_Point)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_POINT OutStart = {};

	//Chama o método para realizar a operação.
	OutStart = PonteiroTrabalho->GetStartPoint();

	//Converte e define no parametro de saida.
	Param_Out_Point = Util.ConverterD2D1_INK_POINTUnmanagedToManaged(&OutStart);
}

/// <summary>
/// Remove o número dado de segmentos da extremidade deste objeto de tinta. 
/// </summary>
/// <param name="Param_QuantidadeSegments">O número de segmentos a serem removidos do final deste objeto de tinta. Observe que o (Param_QuantidadeSegments) deve ser menor ou igual ao número 
/// de segmentos no objeto de tinta.</param>
CarenResult CarenD2D1Ink::RemoveSegmentsAtEnd(UInt32 Param_QuantidadeSegments)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RemoveSegmentsAtEnd(Param_QuantidadeSegments);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza o último segmento neste objeto de tinta com novos pontos de controle. 
/// </summary>
/// <param name="Param_Segment">Uma estrutura que contém os dados do segmento com os quais substituir o último segmento deste objeto de tinta. Observe que se não houver atualmente segmentos 
/// no objeto de tinta, o SetSegmentsAtEnd retornará um erro.</param>
CarenResult CarenD2D1Ink::SetSegmentAtEnd(CA_D2D1_INK_BEZIER_SEGMENT^ Param_Segment)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_BEZIER_SEGMENT* pNewSegment = NULL;

	//Converte a estrutura
	pNewSegment = Util.ConverterD2D1_INK_BEZIER_SEGMENTManagedToUnmanaged(Param_Segment);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSegmentAtEnd(pNewSegment);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pNewSegment);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Atualiza os segmentos especificados neste objeto de tinta com novos pontos de controle. 
/// </summary>
/// <param name="Param_StartSegments">O índice do primeiro segmento neste objeto de tinta a ser atualizado.</param>
/// <param name="Param_Segments">Uma matriz com os dados do segmento a ser usado na atualização.</param>
/// <param name="Param_Quantidade">O número de segmentos neste objeto de tinta que será atualizado com novos dados. Observe que o segmentsCount deve ser menor ou igual ao número de segmentos 
/// no objeto de tinta menos (Param_StartSegments).</param>
CarenResult CarenD2D1Ink::SetSegments(
UInt32 Param_StartSegments,
cli::array<CA_D2D1_INK_BEZIER_SEGMENT^>^% Param_Segments,
UInt32 Param_Quantidade)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_BEZIER_SEGMENT* pMatrizBezier = CriarMatrizEstruturas<D2D1_INK_BEZIER_SEGMENT>(Param_Quantidade);
	D2D1_INK_BEZIER_SEGMENT* pBezierAuxiliar = NULL;

	//Copia os dados para a matriz
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte a estrutura no indice.
		pBezierAuxiliar = Util.ConverterD2D1_INK_BEZIER_SEGMENTManagedToUnmanaged(Param_Segments[i]);

		//Define na matriz.
		pMatrizBezier[i] = *pBezierAuxiliar;

		//Libera a memória para a matriz.
		DeletarEstruturaSafe(&pBezierAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetSegments(Param_StartSegments, pMatrizBezier, Param_Quantidade);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memóra para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizBezier);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o ponto de partida para este objeto de tinta. Isso determina onde este objeto de tinta começará a renderizar.
/// </summary>
/// <param name="Param_StartPoint">O novo ponto de partida para este objeto de tinta.</param>
void CarenD2D1Ink::SetStartPoint(CA_D2D1_INK_POINT^ Param_StartPoint)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_POINT *pStartPoint = NULL;

	//Converte a estrutura
	pStartPoint = Util.ConverterD2D1_INK_POINTManagedToUnmanaged(Param_StartPoint);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetStartPoint(pStartPoint);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pStartPoint);
}

/// <summary>
/// Recupera uma representação geométrica deste objeto de tinta. 
/// </summary>
/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica.</param>
/// <param name="Param_FlatteningTolerance">O Flattening Tolerance a ser usada na determinação da representação geométrica.</param>
/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
CarenResult CarenD2D1Ink::StreamAsGeometry(
ICarenD2D1InkStyle^ Param_InkStyle,
CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
float Param_FlatteningTolerance,
ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1InkStyle* pInkStyle = NULL;
	D2D1_MATRIX_3X2_F* pWorldTransform = NULL;
	ID2D1SimplifiedGeometrySink* pSimpliGeometrySink = NULL;

	//Recupera o ponteiro para a interface de estilo de tinta
	Resultado = RecuperarPonteiroCaren(Param_InkStyle, &pInkStyle);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface Geometry Sink.
	Resultado = RecuperarPonteiroCaren(Param_GeometrySink, &pSimpliGeometrySink);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pWorldTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StreamAsGeometry(pInkStyle, pWorldTransform, Param_FlatteningTolerance, pSimpliGeometrySink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pWorldTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma representação geométrica deste objeto de tinta. 
/// </summary>
/// <param name="Param_InkStyle">O estilo de tinta a ser usado na determinação da representação geométrica.</param>
/// <param name="Param_WorldTransform">O World Transform para ser usado na determinação da representação geométrica</param>
/// <param name="Param_GeometrySink">O Geometry Sink para a qual a representação da geometria será transmitida.</param>
CarenResult CarenD2D1Ink::StreamAsGeometry(
ICarenD2D1InkStyle^ Param_InkStyle,
CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1InkStyle* pInkStyle = NULL;
	D2D1_MATRIX_3X2_F* pWorldTransform = NULL;
	ID2D1SimplifiedGeometrySink* pSimpliGeometrySink = NULL;

	//Recupera o ponteiro para a interface de estilo de tinta
	Resultado = RecuperarPonteiroCaren(Param_InkStyle, &pInkStyle);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface Geometry Sink.
	Resultado = RecuperarPonteiroCaren(Param_GeometrySink, &pSimpliGeometrySink);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pWorldTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StreamAsGeometry(pInkStyle, pWorldTransform, pSimpliGeometrySink);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pWorldTransform);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1Ink::GetFactory(ICaren^ Param_Out_Factory)
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