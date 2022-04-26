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
#include "CarenD2D1RectangleGeometry.h"

//Destruidor.
CarenD2D1RectangleGeometry::~CarenD2D1RectangleGeometry()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1RectangleGeometry::CarenD2D1RectangleGeometry()
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
CarenResult CarenD2D1RectangleGeometry::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1RectangleGeometry::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1RectangleGeometry*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1RectangleGeometry::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1RectangleGeometry*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1RectangleGeometry::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1RectangleGeometry::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1RectangleGeometry::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1RectangleGeometry::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1RectangleGeometry::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1RectangleGeometry::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1RectangleGeometry::LiberarReferencia()
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
void CarenD2D1RectangleGeometry::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1RectangleGeometry();
}



// Métodos da interface proprietária(ICarenD2D1RectangleGeometry)


/// <summary>
/// Recupera o retângulo que descreve as dimensões da geometria do retângulo. 
/// </summary>
/// <param name="Param_Out_Rect">Retorna uma estrutura (CA_D2D1_RECT_F) que descreve as dimensões da geometria do retângulo quando este método retorna.</param>
void CarenD2D1RectangleGeometry::GetRect([Out] CA_D2D1_RECT_F^% Param_Out_Rect)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F OutRectF = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetRect(&OutRectF);

	//Converte a estrutura nativa para a gerenciada.
	Param_Out_Rect = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutRectF);
}




// Métodos da interface (ICarenD2D1Geometry)


/// <summary>
/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
/// </summary>
/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
CarenResult CarenD2D1RectangleGeometry::CombineWithGeometry(
	ICarenD2D1Geometry^ Param_GeometriaEntrada,
	CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
	CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
	float Param_FlatteningTolerance,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometriaEntrada = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_COMBINE_MODE CombineMode = static_cast<D2D1_COMBINE_MODE>(Param_ModoCombinacao);

	//Recupera o ponteiro para a geometria de entrada.
	Resultado = Param_GeometriaEntrada->RecuperarPonteiro((void**)&pGeometriaEntrada);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Recupera o ponteiro para a geometria sink que vai armazenar o resultado desta combinação.
	Resultado = Param_GeomtrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_InputGeometryTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_InputGeometryTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CombineWithGeometry(pGeometriaEntrada, CombineMode, pMatrixTransformacao, Param_FlatteningTolerance, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Combina essa geometria com a geometria especificada e armazena o resultado em um ICarenD2D1SimplifiedGeometrySink. 
/// </summary>
/// <param name="Param_GeometriaEntrada">A geometria para combinar com este exemplo.</param>
/// <param name="Param_ModoCombinacao">O tipo de operação combinada para realizar.</param>
/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada) antes de combinar.</param>
/// <param name="Param_GeomtrySink">A interface que vai armazena o resultado da combinação das geometrias.</param>
CarenResult CarenD2D1RectangleGeometry::CombineWithGeometry(
	ICarenD2D1Geometry^ Param_GeometriaEntrada,
	CA_D2D1_COMBINE_MODE Param_ModoCombinacao,
	CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeomtrySink
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometriaEntrada = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_COMBINE_MODE CombineMode = static_cast<D2D1_COMBINE_MODE>(Param_ModoCombinacao);

	//Recupera o ponteiro para a geometria de entrada.
	Resultado = Param_GeometriaEntrada->RecuperarPonteiro((void**)&pGeometriaEntrada);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Recupera o ponteiro para a geometria sink que vai armazenar o resultado desta combinação.
	Resultado = Param_GeomtrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_InputGeometryTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_InputGeometryTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CombineWithGeometry(pGeometriaEntrada, CombineMode, pMatrixTransformacao, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada utilizando-se a tolerância de achatamento especificada. 
/// Ao interpretar o valor da relação retornada, é importante lembrar que o membro D2D1_GEOMETRY_RELATION_IS_CONTAINED do tipo de enumeração D2D1_GEOMETRY_RELATION significa que essa geometria está 
/// contida dentro da (Param_GeometriaEntrada), não que esta geometria contenha (Param_GeometriaEntrada).
/// </summary>
/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
CarenResult CarenD2D1RectangleGeometry::CompareWithGeometry(
	ICarenD2D1Geometry^ Param_GeometriaEntrada,
	CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
	float Param_FlatteningTolerance,
	[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometriaEntrada = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_GEOMETRY_RELATION OutRelation = { };

	//Recupera o ponteiro para a geometria de entrada.
	Resultado = Param_GeometriaEntrada->RecuperarPonteiro((void**)&pGeometriaEntrada);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_InputGeometryTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_InputGeometryTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CompareWithGeometry(pGeometriaEntrada, pMatrixTransformacao, Param_FlatteningTolerance, &OutRelation);

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

	//Converte o resultado e define no parametro de saida.
	Param_Out_Relacao = static_cast<CA_D2D1_GEOMETRY_RELATION>(OutRelation);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Descreve a intersecção entre esta geometria e a geometria especificada. A comparação é realizada usando a tolerância de achatamento padrão. 
/// </summary>
/// <param name="Param_GeometriaEntrada">A geometria para testar.</param>
/// <param name="Param_InputGeometryTransform">A transformação para aplicar à (Param_GeometriaEntrada).</param>
/// <param name="Param_Out_Relacao">Retorna um valor que descreve como essa geometria está relacionada à (Param_GeometriaEntrada).</param>
CarenResult CarenD2D1RectangleGeometry::CompareWithGeometry(
	ICarenD2D1Geometry^ Param_GeometriaEntrada,
	CA_D2D1_MATRIX_3X2_F^ Param_InputGeometryTransform,
	[Out] CA_D2D1_GEOMETRY_RELATION% Param_Out_Relacao)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometriaEntrada = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_GEOMETRY_RELATION OutRelation = { };

	//Recupera o ponteiro para a geometria de entrada.
	Resultado = Param_GeometriaEntrada->RecuperarPonteiro((void**)&pGeometriaEntrada);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_InputGeometryTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_InputGeometryTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CompareWithGeometry(pGeometriaEntrada, pMatrixTransformacao, &OutRelation);

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

	//Converte o resultado e define no parametro de saida.
	Param_Out_Relacao = static_cast<CA_D2D1_GEOMETRY_RELATION>(OutRelation);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância especificada. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais
/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
CarenResult CarenD2D1RectangleGeometry::ComputeArea(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	[Out] float% Param_Out_Area)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	float OutArea = 0;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputeArea(pMatrixTransformacao, Param_FlatteningTolerance, &OutArea);

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

	//Define no parametro de saida.
	Param_Out_Area = OutArea;

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula a área da geometria depois de ter sido transformada pela matriz especificada e achatada usando a tolerância padrão. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação a ser aplicada a essa geometria antes de calcular sua área.</param>
/// <param name="Param_Out_Area">Retorna a área da versão achatada e transformada desta geometria.</param>
CarenResult CarenD2D1RectangleGeometry::ComputeArea(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] float% Param_Out_Area)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	float OutArea = 0;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputeArea(pMatrixTransformacao, &OutArea);

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

	//Define no parametro de saida.
	Param_Out_Area = OutArea;

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
CarenResult CarenD2D1RectangleGeometry::ComputeLength(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	[Out] float% Param_Out_Length)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	float OutLargura = 0;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputeLength(pMatrixTransformacao, Param_FlatteningTolerance, &OutLargura);

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

	//Define no parametro de saida.
	Param_Out_Length = OutLargura;

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o comprimento da geometria como se cada segmento fosse desenrolado em uma linha. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular seu comprimento.</param>
/// <param name="Param_Out_Length">Retorna o comprimento da geometria. Para geometrias fechadas, o comprimento inclui um segmento de fechamento implícito.</param>
CarenResult CarenD2D1RectangleGeometry::ComputeLength(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] float% Param_Out_Length)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	float OutLargura = 0;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputeLength(pMatrixTransformacao, &OutLargura);

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

	//Define no parametro de saida.
	Param_Out_Length = OutLargura;

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada.
/// </summary>
/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
CarenResult CarenD2D1RectangleGeometry::ComputePointAtLength(
	float Param_Length,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
	CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_POINT_2F OutOpcionalPoint = { };
	D2D1_POINT_2F OutOpcionalUnitTangent = { };
	BOOL RequestPoint0, RequestPoint1 = FALSE;

	//Verifica se os dados de saida foram definidos como nulo. Se sim, eles não seram solicitados a função.
	RequestPoint0 = ObjetoGerenciadoValido(Param_Ref_Opcional_Point);
	RequestPoint1 = ObjetoGerenciadoValido(Param_Ref_Opcional_UnitTangentVector);

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputePointAtLength(
		Param_Length,
		pMatrixTransformacao,
		Param_FlatteningTolerance,
		RequestPoint0 ? &OutOpcionalPoint : NULL,
		RequestPoint1 ? &OutOpcionalPoint : NULL);

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

	//Converte os dados se tiver sido solicitado e define nos parametros.
	Param_Ref_Opcional_Point = RequestPoint0 ? Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutOpcionalPoint) : nullptr;
	Param_Ref_Opcional_UnitTangentVector = RequestPoint1 ? Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutOpcionalUnitTangent) : nullptr;

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o vetor de ponto e tangente na distância especificada ao longo da geometria depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
/// </summary>
/// <param name="Param_Length">A distância ao longo da geometria do ponto e tangente para encontrar. Se essa distância for inferior a 0, este método calcula o primeiro ponto da geometria. Se essa 
/// distância for maior que o comprimento da geometria, este método calcula o último ponto da geometria.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes de calcular o ponto especificado e a tangente.</param>
/// <param name="Param_Ref_Opcional_Point">Retorna a localização na distância especificada ao longo da geometria. Se a geometria estiver vazia, este ponto contém NaN como seus valores x e y.</param>
/// <param name="Param_Ref_Opcional_UnitTangentVector">Retorna o vetor tangente na distância especificada ao longo da geometria. Se a geometria estiver vazia, este vetor contém NaN como seus valores x e y.</param>
CarenResult CarenD2D1RectangleGeometry::ComputePointAtLength(
	float Param_Length,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	CA_D2D1_POINT_2F^% Param_Ref_Opcional_Point,
	CA_D2D1_POINT_2F^% Param_Ref_Opcional_UnitTangentVector)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_POINT_2F OutOpcionalPoint = { };
	D2D1_POINT_2F OutOpcionalUnitTangent = { };
	BOOL RequestPoint0, RequestPoint1 = FALSE;

	//Verifica se os dados de saida foram definidos como nulo. Se sim, eles não seram solicitados a função.
	RequestPoint0 = ObjetoGerenciadoValido(Param_Ref_Opcional_Point);
	RequestPoint1 = ObjetoGerenciadoValido(Param_Ref_Opcional_UnitTangentVector);

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ComputePointAtLength(
		Param_Length,
		pMatrixTransformacao,
		RequestPoint0 ? &OutOpcionalPoint : NULL,
		RequestPoint1 ? &OutOpcionalPoint : NULL);

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

	//Converte os dados se tiver sido solicitado e define nos parametros.
	Param_Ref_Opcional_Point = RequestPoint0 ? Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutOpcionalPoint) : nullptr;
	Param_Ref_Opcional_UnitTangentVector = RequestPoint1 ? Util.ConverterD2D1_POINT_2FUnmanagedToManaged(&OutOpcionalUnitTangent) : nullptr;

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Indica se a área preenchida pela geometria conteria o ponto especificado dada a tolerância de achatamento especificada. 
/// </summary>
/// <param name="Param_Point">O ponto para testar.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam o preenchimento por menos do 
/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
CarenResult CarenD2D1RectangleGeometry::FillContainsPoint(
	CA_D2D1_POINT_2F^ Param_Point,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	[Out] Boolean% Param_Out_Contem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	BOOL OutContem = FALSE;

	//Converte o point se for valido.
	pPoint = ObjetoGerenciadoValido(Param_Point) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point) : NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FillContainsPoint(*pPoint, pMatrixTransformacao, Param_FlatteningTolerance, &OutContem);

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

	//Define o valor no parametro de saida.
	Param_Out_Contem = OutContem ? true : false;
Done:;
	//Libera a memória pra as estruturas.
	DeletarEstruturaSafe(&pPoint);
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Indica se a área preenchida pela geometria conteria o ponto especificado. 
/// </summary>
/// <param name="Param_Point">O ponto para testar.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria antes do teste para contenção.</param>
/// <param name="Param_Out_Contem">Retorna um valor Boleano que é verdadeiro se a área preenchida pela geometria contiver ponto; caso contrário, falso.</param>
CarenResult CarenD2D1RectangleGeometry::FillContainsPoint(
	CA_D2D1_POINT_2F^ Param_Point,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] Boolean% Param_Out_Contem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	BOOL OutContem = FALSE;

	//Converte o point se for valido.
	pPoint = ObjetoGerenciadoValido(Param_Point) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point) : NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->FillContainsPoint(*pPoint, pMatrixTransformacao, &OutContem);

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

	//Define o valor no parametro de saida.
	Param_Out_Contem = OutContem ? true : false;
Done:;
	//Libera a memória pra as estruturas.
	DeletarEstruturaSafe(&pPoint);
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera os limites da geometria. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria antes de calcular seus limites.</param>
/// <param name="Param_Out_Bounds">Retorna os limites desta geometria. Se os limites estiverem vazios, este parâmetro será um recamto onde os Bounds.Left > Bounds.Right.</param>
CarenResult CarenD2D1RectangleGeometry::GetBounds(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_RECT_F OutBound = {};

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetBounds(pMatrixTransformacao, &OutBound);

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
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutBound);
Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
/// </summary>
/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais 
/// do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
CarenResult CarenD2D1RectangleGeometry::GetWidenedBounds(
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_RECT_F OutBound = {};

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWidenedBounds(Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, Param_FlatteningTolerance, &OutBound);

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
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutBound);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os limites da geometria depois de ter sido ampliada pela largura e estilo de traçado especificados e transformada pela matriz especificada. 
/// </summary>
/// <param name="Param_StrokeWidth">A quantidade pela qual ampliar a geometria acariciando seu contorno.</param>
/// <param name="Param_StrokeStyle">O estilo do traçado que amplia a geometria.</param>
/// <param name="Param_WorldTransform">Uma transformação para aplicar à geometria após a geometria é transformada e depois que a geometria foi acariciada.</param>
/// <param name="Param_Out_Bounds">Retorna os limites da geometria ampliada.</param>
CarenResult CarenD2D1RectangleGeometry::GetWidenedBounds(
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	D2D1_RECT_F OutBound = {};

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetWidenedBounds(Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, &OutBound);

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
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutBound);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink. 
/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
/// para criar sindicatos entre várias geometrias simultaneamente.
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por 
/// mais do que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
CarenResult CarenD2D1RectangleGeometry::Outline(
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
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do geometry Sink.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Outline(pMatrixTransformacao, Param_FlatteningTolerance, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Calcula o contorno(Outline) da geometria e escreve o resultado para um ICarenD2D1SimplifiedGeometrySink.
/// O método Outline permite que o chamador produza uma geometria com um preenchimento equivalente à geometria de entrada. 
/// Além disso, o método Contorno(Outline) pode ser útil na remoção de porções redundantes dessas geometrias para simplificar geometrias complexas. Também pode ser útil em combinação com o ICarenD2D1GeometryGroup 
/// para criar sindicatos entre várias geometrias simultaneamente.
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar ao contorno de geometria.</param>
/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual o contorno transformado em geometria é anexado.</param>
CarenResult CarenD2D1RectangleGeometry::Outline(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do geometry Sink.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Outline(pMatrixTransformacao, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) Curvas Cubicas Bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
/// </summary>
/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
CarenResult CarenD2D1RectangleGeometry::Simplify(
	CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
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
	D2D1_GEOMETRY_SIMPLIFICATION_OPTION SimplifyOption = static_cast<D2D1_GEOMETRY_SIMPLIFICATION_OPTION>(Param_OpcaoSimplificacao);
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do geometry Sink.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Simplify(SimplifyOption, pMatrixTransformacao, Param_FlatteningTolerance, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma versão simplificada da geometria que contém apenas linhas e (opcionalmente) curvas búbicas bezier e grava o resultado para um ICarenD2D1SimplifiedGeometrySink. 
/// </summary>
/// <param name="Param_OpcaoSimplificacao">Um valor que especifica se a geometria simplificada deve conter curvas.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria simplificada.</param>
/// <param name="Param_GeometrySink">Uma interface (ICarenD2D1SimplifiedGeometrySink) ao qual a geometria simplificada é anexada.</param>
CarenResult CarenD2D1RectangleGeometry::Simplify(
	CA_D2D1_GEOMETRY_SIMPLIFICATION_OPTION Param_OpcaoSimplificacao,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GEOMETRY_SIMPLIFICATION_OPTION SimplifyOption = static_cast<D2D1_GEOMETRY_SIMPLIFICATION_OPTION>(Param_OpcaoSimplificacao);
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1SimplifiedGeometrySink* pGeometriaSink = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do geometry Sink.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pGeometriaSink);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Simplify(SimplifyOption, pMatrixTransformacao, pGeometriaSink);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado.
/// </summary>
/// <param name="Param_Point">O ponto para testar a contenção.</param>
/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
/// <param name="Param_FlatteningTolerance">A precisão numérica com a qual o caminho geométrico preciso e a intersecção de caminho são calculados. Pontos que faltam ao derrame por menos do
/// que a tolerância ainda são considerados dentro. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
CarenResult CarenD2D1RectangleGeometry::StrokeContainsPoint(
	CA_D2D1_POINT_2F^ Param_Point,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	[Out] Boolean% Param_Out_Contem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	BOOL OutContem = FALSE;

	//Converte as estruturas gerenciadas para nativas.
	pPoint = ObjetoGerenciadoValido(Param_Point) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point) : NULL;
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StrokeContainsPoint(*pPoint, Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, Param_FlatteningTolerance, &OutContem);

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

	//Define o resultado no parametro de saida.
	Param_Out_Contem = OutContem ? true : false;

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPoint);
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Determina se o traçado da geometria contém o ponto especificado dada a espessura, estilo e transformação especificada do traçado. 
/// </summary>
/// <param name="Param_Point">O ponto para testar a contenção.</param>
/// <param name="Param_StrokeWidth">A espessura do Stroke para aplicar.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria acariciada.</param>
/// <param name="Param_Out_Contem">Retorna um valor booleano definido como verdadeiro se o traçado da geometria contiver o ponto especificado; caso contrário, falso.</param>
CarenResult CarenD2D1RectangleGeometry::StrokeContainsPoint(
	CA_D2D1_POINT_2F^ Param_Point,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	[Out] Boolean% Param_Out_Contem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	BOOL OutContem = FALSE;

	//Converte as estruturas gerenciadas para nativas.
	pPoint = ObjetoGerenciadoValido(Param_Point) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point) : NULL;
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->StrokeContainsPoint(*pPoint, Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, &OutContem);

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

	//Define o resultado no parametro de saida.
	Param_Out_Contem = OutContem ? true : false;

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPoint);
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância especificada.
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do
/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
CarenResult CarenD2D1RectangleGeometry::Tessellate(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_FlatteningTolerance,
	ICarenD2D1TessellationSink^ Param_TelassellationSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1TessellationSink* pTesselateAnex = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface onde vai ser anexado o Tessellated
	Resultado = Param_TelassellationSink->RecuperarPonteiro((void**)&pTesselateAnex);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método.
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Tessellate(pMatrixTransformacao, Param_FlatteningTolerance, pTesselateAnex);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um conjunto de triângulos no sentido horário que cobrem a geometria depois que ela foi transformada usando a matriz especificada e achatada usando a tolerância padrão. 
/// </summary>
/// <param name="Param_WorldTransform">A transformação para aplicar a esta geometria.</param>
/// <param name="Param_TelassellationSink">Uma interface (ICarenD2D1TessellationSink) ao qual o Tessellated é anexado.</param>
CarenResult CarenD2D1RectangleGeometry::Tessellate(
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1TessellationSink^ Param_TelassellationSink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1TessellationSink* pTesselateAnex = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface onde vai ser anexado o Tessellated
	Resultado = Param_TelassellationSink->RecuperarPonteiro((void**)&pTesselateAnex);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método.
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Tessellate(pMatrixTransformacao, pTesselateAnex);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância especificada. 
/// </summary>
/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
/// <param name="Param_FlatteningTolerance">O erro máximo permitido ao construir uma aproximação poligonal da geometria. Nenhum ponto na representação poligonal divergirá da geometria original por mais do 
/// que a tolerância ao achatamento. Valores menores produzem resultados mais precisos, mas causam uma execução mais lenta.</param>
/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
CarenResult CarenD2D1RectangleGeometry::Widen(
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
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
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	ID2D1SimplifiedGeometrySink* pSimplifiedGeometry = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Recupera o ponteiro para a interface simplificada de geometria.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pSimplifiedGeometry);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Widen(Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, Param_FlatteningTolerance, pSimplifiedGeometry);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Amplia a geometria pelo traçado especificado e grava o resultado para um ID2D1SimplifiedGeometrySink depois de ter sido transformado pela matriz especificada e achatado usando a tolerância padrão. 
/// </summary>
/// <param name="Param_StrokeWidth">A quantidade pela qual vai ampliar a geometria.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado para aplicar à geometria, ou NULO.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à geometria depois de ampliá-la.</param>
/// <param name="Param_GeometrySink">Uma interface (ID2D1SimplifiedGeometrySink) ao qual a geometria ampliada é anexada.</param>
CarenResult CarenD2D1RectangleGeometry::Widen(
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1SimplifiedGeometrySink^ Param_GeometrySink)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrixTransformacao = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;
	ID2D1SimplifiedGeometrySink* pSimplifiedGeometry = NULL;

	//Converte a Matrix gerenciada para a nativa se ela for valida.
	pMatrixTransformacao = ObjetoGerenciadoValido(Param_WorldTransform) ? Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform) : NULL;

	//Recupera o ponteiro para a interface do Stroke.
	Resultado = Param_StrokeStyle->RecuperarPonteiro((void**)&pStrokeStyle);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Recupera o ponteiro para a interface simplificada de geometria.
	Resultado = Param_GeometrySink->RecuperarPonteiro((void**)&pSimplifiedGeometry);

	//Verifica se obteve sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera a interface do Stroke

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Widen(Param_StrokeWidth, pStrokeStyle, pMatrixTransformacao, pSimplifiedGeometry);

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
	DeletarEstruturaSafe(&pMatrixTransformacao);

	//Retorna o resultado.
	return Resultado;
}





// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1RectangleGeometry::GetFactory(ICaren^ Param_Out_Factory)
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