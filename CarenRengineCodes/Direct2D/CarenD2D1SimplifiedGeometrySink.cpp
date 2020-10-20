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

#include "..\pch.h"
#include "CarenD2D1SimplifiedGeometrySink.h"

//Destruidor.
CarenD2D1SimplifiedGeometrySink::~CarenD2D1SimplifiedGeometrySink()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}


// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD2D1SimplifiedGeometrySink::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Variavel que vai retornar o resultado.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM
	HRESULT Hr = E_FAIL;

	//Variaveis a serem utilizadas
	GUID GuidInterface = GUID_NULL;
	wchar_t* DadosGuid = NULL;
	LPVOID* pInterfaceSolcitada = NULL;

	//Setor onde será criado o GUID para realizar a operação.
	{
		//Context Marshal.
		marshal_context ctx;
		//Lagrura da string
		int LarguraString = 0;
		//Variavel que vai conter os dados da String para o tipo não gerenciado.
		const char* DadosConvertidos = NULL;

		//Verifica se a string é valida.
		if (Param_Guid != nullptr && !String::IsNullOrEmpty(Param_Guid))
		{
			//Obtém a largura da String.
			LarguraString = Param_Guid->Length + 1;

			//Converte os dados para um buffer de char.
			//O Proprio marshal_context destroi o buffer.
			DadosConvertidos = ctx.marshal_as<const char*>(Param_Guid);

			//Aloca memoria para o Dados do Guid.
			DadosGuid = new wchar_t[LarguraString];

			//Copia os dados para o OLECHAR.
			mbstowcs_s(NULL, DadosGuid, LarguraString, DadosConvertidos, LarguraString - 1);

			//Chama o método que vai criar o CLSID adequado a aparti do guid
			Hr = CLSIDFromString(DadosGuid, (LPCLSID)&GuidInterface);
		}
		else
		{
			//Falhou ao criar o GUID
			Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

			//A string não é valida
			goto Done;
		}
	}

	//Verifica se o guid foi criado com sucesso.
	if (GuidInterface == GUID_NULL)
	{
		//Falhou ao criar o GUID
		Resultado.AdicionarCodigo(ResultCode::ER_GUID_INVALIDO, false);

		//Sai do método
		goto Done;
	}

	//Chama o método para realizara operação
	Hr = PonteiroTrabalho->QueryInterface(GuidInterface, (LPVOID*)&pInterfaceSolcitada);

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

	//Define o ponteiro na interface solicitada.
	//A interface deve ter sido incializada pelo usuário.
	Resultado = Param_InterfaceSolicitada->AdicionarPonteiro(pInterfaceSolcitada);

	//Verifica o resultado da operação.
	if (Resultado.StatusCode != ResultCode::SS_OK)
	{
		//Libera a referência obtida a parti do QueryInterface.
		((IUnknown*)pInterfaceSolcitada)->Release();
		pInterfaceSolcitada = NULL;
	}

Done:;
	//Verifica se o OLECHAR é valido e destroi
	if (ObjetoValido(DadosGuid))
	{
		//Libera os dados.
		delete[] DadosGuid;
	}

	//Retorna o resultado
	return Resultado;
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SimplifiedGeometrySink::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SimplifiedGeometrySink*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1SimplifiedGeometrySink::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SimplifiedGeometrySink*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1SimplifiedGeometrySink::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SimplifiedGeometrySink::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SimplifiedGeometrySink::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1SimplifiedGeometrySink::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SimplifiedGeometrySink::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SimplifiedGeometrySink::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SimplifiedGeometrySink::LiberarReferencia()
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
/// Método responsável por limpar os dados do objeto COM e códigos de erros gerados pelos métodos da classe.
/// Este método não libera a referência do objeto COM atual, vai apenas anular o ponteiro.
/// </summary>
void CarenD2D1SimplifiedGeometrySink::LimparDados()
{
	//Verifica se o ponteiro é um objeto valido e limpa.
	if (ObjetoValido(PonteiroTrabalho))
	{
		//NULA o ponteiro.
		PonteiroTrabalho = NULL;
	}

	//Zera o código de erro
	Var_Glob_LAST_HRESULT = 0;
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1SimplifiedGeometrySink::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);

	//Chama o finalizador da classe
	this->~CarenD2D1SimplifiedGeometrySink();
}



// Métodos da interface proprietária(ICarenD2D1SimplifiedGeometrySink)


/// <summary>
/// Cria uma sequência de curvas Cubicas de Bezier e as adiciona ao Geometry Sink.
/// </summary>
/// <param name="Param_ArrayBeziers">Uma matriz de segmentos Bezier que descreve as curvas bezier para criar. Uma curva é extraída do ponto atual do Geometry Sink (o ponto final do último segmento 
/// desenhado ou o local especificado pela BeginFigure) até o ponto final do primeiro segmento Bezier na matriz. se a matriz contiver segmentos bezier adicionais, cada segmento Bezier subsequente usa
/// o ponto final do segmento Bezier anterior como seu ponto de partida.</param>
/// <param name="Param_QuantidadeBeziers">O número de segmentos Bezier na matriz (Param_ArrayBeziers).</param>
void CarenD2D1SimplifiedGeometrySink::AddBeziers(
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
void CarenD2D1SimplifiedGeometrySink::AddLines(
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
void CarenD2D1SimplifiedGeometrySink::BeginFigure(
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
CarenResult CarenD2D1SimplifiedGeometrySink::Close()
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
/// Termina a figura atual; opcionalmente, fecha-o.
/// Chamar este método sem uma chamada correspondente ao BeginFigure coloca o Geometry Sink em um estado de erro; chamadas subsequentes são ignoradas, e a falha geral será devolvida quando o método 
/// Close for chamado.
/// </summary>
/// <param name="Param_FinalFigura">Um valor que indica se o valor atual está fechado. Se o valor for fechado, uma linha será traçada entre o ponto atual e o ponto de partida especificado 
/// pela BeginFigure.</param>
void CarenD2D1SimplifiedGeometrySink::EndFigure(CA_D2D1_FIGURE_END Param_FinalFigura)
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
void CarenD2D1SimplifiedGeometrySink::SetFillMode(CA_D2D1_FILL_MODE Param_ModoPreencher)
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
void CarenD2D1SimplifiedGeometrySink::SetSegmentFlags(CA_D2D1_PATH_SEGMENT Param_FlagsVertex)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetSegmentFlags(static_cast<D2D1_PATH_SEGMENT>(Param_FlagsVertex));
}