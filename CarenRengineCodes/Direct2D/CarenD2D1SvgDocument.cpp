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
#include "CarenD2D1SvgDocument.h"

//Destruidor.
CarenD2D1SvgDocument::~CarenD2D1SvgDocument()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgDocument::CarenD2D1SvgDocument()
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
CarenResult CarenD2D1SvgDocument::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgDocument::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgDocument*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1SvgDocument::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1SvgDocument*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1SvgDocument::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SvgDocument::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1SvgDocument::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1SvgDocument::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1SvgDocument::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgDocument::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgDocument::LiberarReferencia()
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
void CarenD2D1SvgDocument::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1SvgDocument();
}



// Métodos da interface proprietária(ICarenD2D1SvgDocument)


/// <summary>
/// Cria um objeto de tinta que pode ser usado para definir as propriedades 'preenchimento' ou 'traçado'. 
/// </summary>
/// <param name="Param_PaintType">Especifica o tipo de objeto de tinta para criar.</param>
/// <param name="Param_Cor">A cor usada se o (Param_PaintType) estiver D2D1_SVG_PAINT_TYPE_COLOR.</param>
/// <param name="Param_Id">O elemento id que atua como o servidor de tinta. Este id é usado se o tipo de tinta é D2D1_SVG_PAINT_TYPE_URI.</param>
/// <param name="Param_Out_Paint">Retorna uma interface(ICarenD2D1SvgPaint) que contém um ponteiro para o objeto de pintura criado.</param>
CarenResult CarenD2D1SvgDocument::CreatePaint(
CA_D2D1_SVG_PAINT_TYPE Param_PaintType,
CA_D2D1_COLOR_F^ Param_Cor,
String^ Param_Id,
[Out] ICarenD2D1SvgPaint^% Param_Out_Paint)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_PAINT_TYPE PaintType = static_cast<D2D1_SVG_PAINT_TYPE>(Param_PaintType);
	D2D1_COLOR_F* pCor = NULL;
	PWSTR IdElemento = NULL;
	ID2D1SvgPaint* pOutPaint = NULL;

	//Converte a estrutura de cor.
	pCor = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Cor);

	//Cria o id do elemento a parti da string.
	IdElemento = Util.ConverterStringToWCHAR(Param_Id);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePaint(PaintType, pCor, IdElemento, &pOutPaint);

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

	//Cria a interface a ser retornada.
	Param_Out_Paint = gcnew CarenD2D1SvgPaint();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutPaint, Param_Out_Paint, true);

Done:;
	//Libera a memória para os dados.
	DeletarEstruturaSafe(&pCor);
	DeletarStringAllocatedSafe(&IdElemento);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de dados de caminho que pode ser usado para definir um atributo 'd' em um elemento 'path'. 
/// </summary>
/// <param name="Param_SegmentData">Uma série de dados do segmento.</param>
/// <param name="Param_QuantidadeSegments">Número de itens no (Param_SegmentData).</param>
/// <param name="Param_Comandos">Uma série de comandos de Path.</param>
/// <param name="Param_QuantidadeComandos">O número de itens em (Param_Comandos).</param>
/// <param name="Param_Out_PathData">Retorna uma interface(ICarenD2D1SvgPathData) que contém um ponteiro para os PathData criados.</param>
CarenResult CarenD2D1SvgDocument::CreatePathData(
cli::array<float>^ Param_SegmentData,
UInt32 Param_QuantidadeSegments,
cli::array<CA_D2D1_SVG_PATH_COMMAND>^ Param_Comandos,
UInt32 Param_QuantidadeComandos,
[Out] ICarenD2D1SvgPathData^% Param_Out_PathData)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	float* pMatrizSegmentos = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_QuantidadeSegments));
	D2D1_SVG_PATH_COMMAND* pMatrizSvgCommands = CriarMatrizUnidimensional<D2D1_SVG_PATH_COMMAND>(static_cast<DWORD>(Param_QuantidadeComandos));
	ID2D1SvgPathData* pOutPathData = NULL;

	//Copia os dados para a matriz de segmentos.
	Util.CopiarItensTo_ArrayNativo(&pMatrizSegmentos, Param_SegmentData, Param_QuantidadeSegments);

	//Copia os dados para a matriz de comandos svg.
	Util.CopiarItensTo_ArrayNativo(&pMatrizSvgCommands, Param_Comandos,  Param_QuantidadeComandos);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePathData(pMatrizSegmentos, Param_QuantidadeSegments, pMatrizSvgCommands, Param_QuantidadeComandos, &pOutPathData);

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

	//Cria a interface a ser retornada.
	Param_Out_PathData = gcnew CarenD2D1SvgPathData();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutPathData, Param_Out_PathData);

Done:;
	//Libera a memória para as matrizes.
	DeletarMatrizUnidimensionalSafe(&pMatrizSegmentos);
	DeletarMatrizUnidimensionalSafe(&pMatrizSvgCommands);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de pontos que pode ser usado para definir um atributo de pontos em um polígono ou elemento polilinha. 
/// </summary>
/// <param name="Param_Points">Os pontos na coleção de pontos.</param>
/// <param name="Param_QuantidadePoints">O numero de pontos em (Param_Points)</param>
/// <param name="Param_Out_PointCollection">Retorna uma interface(ICarenD2D1SvgPointCollection) que contém um ponteiro para o objeto criado.</param>
CarenResult CarenD2D1SvgDocument::CreatePointCollection(
cli::array<CA_D2D1_POINT_2F^>^ Param_Points,
UInt32 Param_QuantidadePoints,
[Out] ICarenD2D1SvgPointCollection^% Param_Out_PointCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMatrizPoints = CriarMatrizEstruturas<D2D1_POINT_2F>(Param_QuantidadePoints);
	ID2D1SvgPointCollection* pOutPointCollection = NULL;
	D2D1_POINT_2F* pPointAuxiliar = NULL;

	//Cria um for para criar os dados.
	for (UINT32 i = 0; i < Param_QuantidadePoints; i++)
	{
		//Converte a estrutura
		pPointAuxiliar = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Points[i]);

		//Define a estrutura na matriz.
		pMatrizPoints[i] = *pPointAuxiliar;

		//Libera a memória para a estrutura
		DeletarEstruturaSafe(&pPointAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePointCollection(pMatrizPoints, Param_QuantidadePoints, &pOutPointCollection);

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

	//Cria a interface a ser retornada.
	Param_Out_PointCollection = gcnew CarenD2D1SvgPointCollection();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutPointCollection, Param_Out_PointCollection);

Done:;
	//Libera a memória para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizPoints);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de matriz de traço que pode ser usado para definir a propriedade stroke-dasharray. 
/// </summary>
/// <param name="Param_Dashes">Uma série de traços(dashes).</param>
/// <param name="Param_QuantidadeDashes">A quantidade de dashes no array (Param_Dashes).</param>
/// <param name="Param_Out_StrokeDashArray">Retorna uma interface(ICarenD2D1SvgStrokeDashArray) que contém um ponteiro para o objeto criado.</param>
CarenResult CarenD2D1SvgDocument::CreateStrokeDashArray(
cli::array<CA_D2D1_SVG_LENGTH^>^ Param_Dashes,
UInt32 Param_QuantidadeDashes,
[Out] ICarenD2D1SvgStrokeDashArray^% Param_Out_StrokeDashArray)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SVG_LENGTH* pMatrizDashes = CriarMatrizEstruturas<D2D1_SVG_LENGTH>(Param_QuantidadeDashes);
	ID2D1SvgStrokeDashArray* pOutStrokeArray = NULL;
	D2D1_SVG_LENGTH* pSvgLength = NULL;

	//Cria um for para criar os dados.
	for (UINT32 i = 0; i < Param_QuantidadeDashes; i++)
	{
		//Converte a estrutura
		pSvgLength = Util.ConverterD2D1_SVG_LENGTHManagedToUnmanaged(Param_Dashes[i]);

		//Define a estrutura na matriz.
		pMatrizDashes[i] = *pSvgLength;

		//Libera a memória para a estrutura
		DeletarEstruturaSafe(&pSvgLength);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateStrokeDashArray(pMatrizDashes, Param_QuantidadeDashes, &pOutStrokeArray);

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

	//Cria a interface a ser retornada.
	Param_Out_StrokeDashArray = gcnew CarenD2D1SvgStrokeDashArray();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutStrokeArray, Param_Out_StrokeDashArray);

Done:;
	//Libera a memória para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pMatrizDashes);

    //Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Deserializa uma subarvore do Stream. O fluxo deve ter apenas um elemento raiz, mas esse elemento raiz não precisa ser um elemento 'svg'. O elemento de saída não está inserido nesta árvore de documento. 
/// </summary>
/// <param name="Param_InputXmlStream">Um fluxo de entrada contendo a subárvore SVG XML.</param>
/// <param name="Param_Out_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subárvore. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1SvgDocument::Deserialize(
ICarenStream^ Param_InputXmlStream,
ICaren^ Param_Out_SvgElementSubTree)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pInputXmlStream = NULL;
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Recupera o ponteiro para a interface de stream
	Resultado = RecuperarPonteiroCaren(Param_InputXmlStream, &pInputXmlStream);

	//Sai em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Deserialize(pInputXmlStream, &pOutSvgElement);

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

	//Define o ponteiro na itnerface de saida.
	Resultado = DefinirPonteiroInterface(pInputXmlStream, Param_InputXmlStream);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o elemento SVG com o ID especificado. 
/// </summary>
/// <param name="Param_Id">ID do elemento para recuperar.</param>
/// <param name="Param_Out_SvgElement">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento correspondente ao ID especificado. Se não for encontrado, esse valor será NULO. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1SvgDocument::FindElementById(
String^ Param_Id,
ICaren^ Param_Out_SvgElement)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PCWSTR pId = NULL;
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Cria o id do elemento
	pId = Util.ConverterStringToWCHAR(Param_Id);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FindElementById(pId, &pOutSvgElement);

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

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutSvgElement, Param_Out_SvgElement);

Done:;
	//Libera a memória para o id
	DeletarStringAllocatedSafe(&pId);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o elemento raiz do documento. 
/// </summary>
/// <param name="Param_Out_SvgElementRoot">Retorna uma interface(ICarenD2D1SvgElement) que contém o elemento raiz do documento. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgDocument::GetRoot(ICaren^ Param_Out_SvgElementRoot)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pOutSvgElement = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetRoot(&pOutSvgElement);

	//Define o ponteiro na interface.
	DefinirPonteiroInterface(pOutSvgElement, Param_Out_SvgElementRoot);
}

/// <summary>
/// Retorna o tamanho do viewport inicial. 
/// </summary>
/// <param name="Param_Out_Size">Retorna o tamanho do viewport inicial</param>
void CarenD2D1SvgDocument::GetViewportSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F OutSize = {};

	//Chama o método para realizar a operação.
	OutSize = PonteiroTrabalho->GetViewportSize();

	//Converte e define no parametro de saida.
	Param_Out_Size = Util.ConverterD2D1_SIZE_FUnmanagedToManaged(&OutSize);
}

/// <summary>
/// Serializa um elemento e sua subárvore para XML. O XML de saída é codificado como UTF-8.
/// </summary>
/// <param name="Param_OutputXmlStream">Um fluxo de saída para conter a subárvore SVG XML.</param>
/// <param name="Param_SvgElementSubTree">Uma interface(ICarenD2D1SvgElement) da raiz da subarvore. Se for NULO, todo o documento será serializado.</param>
CarenResult CarenD2D1SvgDocument::Serialize(
ICarenStream^ Param_OutputXmlStream,
ICaren^ Param_SvgElementSubTree)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pOutputStream = NULL;
	ID2D1SvgElement* pSvgElement = NULL;

	//Recupera o ponteiro para o Fluxo.
	Resultado = RecuperarPonteiroCaren(Param_OutputXmlStream, &pOutputStream);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o elemento SVG se informado.
	if (ObjetoGerenciadoValido(Param_SvgElementSubTree))
	{
		//Recupera o ponteiro.
		Resultado = RecuperarPonteiroCaren(Param_SvgElementSubTree, &pSvgElement);

		//Sai do método em caso de erro.
		SairOnError(Resultado);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Serialize(pOutputStream, pSvgElement);

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
/// Define o elemento raiz do documento. 
/// </summary>
/// <param name="Param_SvgElementRoot">Uma interface(ICarenD2D1SvgElement) que define o novo elemento raiz do documento.</param>
CarenResult CarenD2D1SvgDocument::SetRoot(ICaren^ Param_SvgElementRoot)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgElement* pSvgElement = NULL;

	//Recupera o ponteiro para o elemento svg.
	Resultado = RecuperarPonteiroCaren(Param_SvgElementRoot, &pSvgElement);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetRoot(pSvgElement);

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
/// Define o tamanho da configuração inicial. 
/// </summary>
/// <param name="Param_ViewportSize">O tamanho da viewport.</param>
CarenResult CarenD2D1SvgDocument::SetViewportSize(CA_D2D1_SIZE_F^ Param_ViewportSize)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeViewPort = NULL;

	//Covnerte a estrutura.
	pSizeViewPort = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_ViewportSize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetViewportSize(*pSizeViewPort);

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
	DeletarEstruturaSafe(&pSizeViewPort);

	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgDocument::GetFactory(ICaren^ Param_Out_Factory)
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