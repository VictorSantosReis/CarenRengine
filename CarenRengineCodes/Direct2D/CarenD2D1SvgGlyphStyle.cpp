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
#include "CarenD2D1SvgGlyphStyle.h"

//Destruidor.
CarenD2D1SvgGlyphStyle::~CarenD2D1SvgGlyphStyle()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1SvgGlyphStyle::CarenD2D1SvgGlyphStyle()
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
CarenResult CarenD2D1SvgGlyphStyle::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgGlyphStyle::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgGlyphStyle*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgGlyphStyle**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1SvgGlyphStyle::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1SvgGlyphStyle*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1SvgGlyphStyle**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgGlyphStyle::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1SvgGlyphStyle::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1SvgGlyphStyle::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1SvgGlyphStyle::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1SvgGlyphStyle::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1SvgGlyphStyle::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1SvgGlyphStyle::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1SvgGlyphStyle();
}



// Métodos da interface proprietária(ICarenD2D1SvgGlyphStyle)


/// <summary>
/// Retorna os parâmetros de preenchimento solicitados. 
/// </summary>
/// <param name="Param_Out_Brush">Retorna o Brush que desve como a área é pintada.</param>
void CarenD2D1SvgGlyphStyle::GetFill([Out] ICarenD2D1Brush^% Param_Out_Brush)
{
	//Variaveis a serem utilizadas.
	ID2D1Brush* pOutBrush = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetFill(&pOutBrush);

	//Cria a interface.
	Param_Out_Brush = gcnew CarenD2D1Brush();

	//Define o ponteiro na interface.
	Param_Out_Brush->AdicionarPonteiro(pOutBrush);
}

/// <summary>
/// Retorna os parâmetros de curso solicitados. Quaisquer parâmetros que não sejam nulos receberão o valor do parâmetro solicitado.
/// </summary>
/// <param name="Param_Out_Brush">Retorna o Brush que indica como o Stroke é pintado.</param>
/// <param name="Param_Out_StrokeWidth">O "valor de contexto" para a propriedade 'largura de traçado'.</param>
/// <param name="Param_Out_Dashes">O "valor de contexto" para a propriedade 'stroke-dasharray'.</param>
/// <param name="Param_QuantidadeDashes">O número de Dasges na matriz (Param_Out_Dashes).</param>
/// <param name="Param_Out_DashOffset">O "valor de contexto" para a propriedade 'stroke-dashoffset'.</param>
void CarenD2D1SvgGlyphStyle::GetStroke(
[Out] ICarenD2D1Brush^% Param_Out_Brush,
[Out] float% Param_Out_StrokeWidth,
[Out] cli::array<float>^% Param_Out_Dashes,
UInt32 Param_QuantidadeDashes,
[Out] float% Param_Out_DashOffset)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Brush* pOutBrush = NULL;
	FLOAT OutStrokeWidth = 0;
	FLOAT* pOutMatrizDashes = CriarMatrizUnidimensional<FLOAT>(static_cast<DWORD>(Param_QuantidadeDashes));
	FLOAT OutDashOffset = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetStroke(&pOutBrush, &OutStrokeWidth, pOutMatrizDashes, Param_QuantidadeDashes, &OutDashOffset);

	//Cria a interface de saida.
	Param_Out_Brush = gcnew CarenD2D1Brush();

	//Define ponteiro para a interface.
	Param_Out_Brush->AdicionarPonteiro(pOutBrush);

	//Define os valores simples
	Param_Out_StrokeWidth = OutStrokeWidth;
	Param_Out_DashOffset = OutDashOffset;

	//Cria a matriz gerenciada.
	Param_Out_Dashes = gcnew cli::array<float>(Param_QuantidadeDashes);

	//Copia os dados para a matriz de dashes.
	Util.CopiarBufferNativo_ToGerenciado(&pOutMatrizDashes, Param_Out_Dashes, Param_QuantidadeDashes);

	//Libera a memória para a matriz nativa.
	DeletarMatrizUnidimensionalSafe(&pOutMatrizDashes);
}

/// <summary>
/// Retorna o número de traços(Dashes) na matriz de traços. 
/// </summary>
/// <param name="Param_Out_Quantidade">Retorna o número dashes na matriz.</param>
void CarenD2D1SvgGlyphStyle::GetStrokeDashesCount([Out] UInt32% Param_Out_Quantidade)
{
	//Chama o método para realizar a operação.
	Param_Out_Quantidade = PonteiroTrabalho->GetStrokeDashesCount();
}

/// <summary>
/// Fornece valores a um glifo SVG para preenchimento. 
/// </summary>
/// <param name="Param_Brush">O Brush que descreve como a área é pintada. Um pincel nulo fará com que o valor de preenchimento de contexto venha do ICarenD2D1DeviceContext4::DrawText. 
/// Se o (ICarenD2D1DeviceContext4::DrawText) Também ser nulo, o valor de preenchimento de contexto será 'nenhum'. Para definir o valor de "preenchimento de contexto", este método usa 
/// o pincel fornecido com sua opacidade definida para 1. Para definir o valor "contexto-preenchimento-opacidade", este método utiliza a opacidade do pincel fornecido.</param>
CarenResult CarenD2D1SvgGlyphStyle::SetFill(ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Brush* pFillBrush = NULL;//Pode ser NULO.

	//Verifica se forneceu a interface.
	if (ObjetoGerenciadoValido(Param_Brush))
	{
		//Recupera o ponteiro para a interface
		Resultado = RecuperarPonteiroCaren(Param_Brush, &pFillBrush);

		//Sai do método em caso de erro.
		SairOnError(Resultado);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetFill(pFillBrush);

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
/// Fornece valores a um glifo SVG para propriedades de traçado. O pincel com opacidade definido para 1 é usado como o "traçado de contexto". A opacidade do pincel é usada como o valor 
/// "contexto-traçado-opacidade". 
/// </summary>
/// <param name="Param_Brush">O Brush que descreve como o Stroke é pintado. Um pincel nulo fará com que o valor do traçado do contexto não seja nenhum.</param>
/// <param name="Param_StrokeWidth">Especifica o 'valor de contexto' para a propriedade 'largura de traçado'.</param>
/// <param name="Param_Dashes">Especifica o 'valor de contexto' para a propriedade 'stroke-dasharray'. Um valor nulo fará com que o traçado-dasharray seja definido como "nenhum".</param>
/// <param name="Param_QuantidadeDashes">O número de Dashes na matriz (Param_Dashes).</param>
/// <param name="Param_DashOffset">Especifica o 'valor de contexto' para a propriedade 'stroke-dashoffset'.</param>
CarenResult CarenD2D1SvgGlyphStyle::SetStroke(
ICarenD2D1Brush^ Param_Brush,
float Param_StrokeWidth,
cli::array<float>^ Param_Dashes,
UInt32 Param_QuantidadeDashes,
float Param_DashOffset)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Brush* pBrush; //Pode ser NULO.
	FLOAT* pMatrizDashes = CriarMatrizUnidimensional<FLOAT>(static_cast<DWORD>(Param_QuantidadeDashes));

	//Verifica se forneceu a interface do brush.
	if (ObjetoGerenciadoValido(Param_Brush))
	{
		//Recupera o ponteiro para a interface
		Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

		//Sai do método em caso de erro.
		SairOnError(Resultado);
	}

	//Copia os dados para a matriz nativa.
	Util.CopiarItensTo_ArrayNativo(&pMatrizDashes, Param_Dashes, Param_QuantidadeDashes);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->SetStroke(pBrush, Param_StrokeWidth, pMatrizDashes, Param_QuantidadeDashes, Param_DashOffset);

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
	//Libera a memória para a matriz 
	DeletarMatrizUnidimensionalSafe(&pMatrizDashes);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1SvgGlyphStyle::GetFactory(ICaren^ Param_Out_Factory)
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