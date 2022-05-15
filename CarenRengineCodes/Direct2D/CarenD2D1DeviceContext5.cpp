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
#include "CarenD2D1DeviceContext5.h"

//Destruidor.
CarenD2D1DeviceContext5::~CarenD2D1DeviceContext5()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1DeviceContext5::CarenD2D1DeviceContext5()
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
CarenResult CarenD2D1DeviceContext5::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DeviceContext5::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DeviceContext5*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DeviceContext5**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1DeviceContext5::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1DeviceContext5*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1DeviceContext5**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DeviceContext5::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1DeviceContext5::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1DeviceContext5::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1DeviceContext5::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1DeviceContext5::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1DeviceContext5::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1DeviceContext5::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1DeviceContext5();
}



// Métodos da interface proprietária(ICarenD2D1DeviceContext5)


/// <summary>
/// Cria um contexto de cor a partir de um tipo de espaço de cor DXGI. Só é válido usá-lo com o efeito de gerenciamento de cores no modo 'Melhor'.
/// </summary>
/// <param name="Param_EspacoCor">O espaço de cores para criar o contexto de cores a partir de.</param>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
CarenResult CarenD2D1DeviceContext5::CreateColorContextFromDxgiColorSpace(
CA_DXGI_COLOR_SPACE_TYPE Param_EspacoCor,
[Out] ICarenD2D1ColorContext1^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1ColorContext1* pOutColorContext1 = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromDxgiColorSpace(static_cast<DXGI_COLOR_SPACE_TYPE>(Param_EspacoCor), &pOutColorContext1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext1, Param_Out_ColorContext);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cores a partir de um perfil de cor simples. Só é válido usá-lo com o efeito de gerenciamento de cores no modo 'Melhor'.
/// </summary>
/// <param name="Param_SimpleProfile">O perfil de cor simples para criar o contexto de cores a partir de.</param>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
CarenResult CarenD2D1DeviceContext5::CreateColorContextFromSimpleColorProfile(
CA_D2D1_SIMPLE_COLOR_PROFILE^ Param_SimpleProfile,
[Out] ICarenD2D1ColorContext1^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIMPLE_COLOR_PROFILE* pSimpleProfile = NULL;
	ID2D1ColorContext1* pOutColorContext1 = NULL;

	//Converte a estrutura.
	pSimpleProfile = Util.ConverterD2D1_SIMPLE_COLOR_PROFILEManagedToUnmanaged(Param_SimpleProfile);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromSimpleColorProfile(pSimpleProfile, &pOutColorContext1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext1, Param_Out_ColorContext);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pSimpleProfile);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um documento SVG a partir de um fluxo. 
/// </summary>
/// <param name="Param_InputXmlStream">Um fluxo de entrada contendo o documento SVG XML. Se for nulo, um documento vazio será criado.</param>
/// <param name="Param_Viewportsize">Tamanho da visualização inicial do documento.</param>
/// <param name="Param_Out_SvgDocumento">Retorna uma interface(ICarenD2D1SvgDocument) que contém um ponteiro para o novo documento SVG criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateSvgDocument(
ICarenStream^ Param_InputXmlStream,
CA_D2D1_SIZE_F^ Param_Viewportsize,
[Out] ICarenD2D1SvgDocument^% Param_Out_SvgDocumento)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IStream *pInputXmlStream = NULL; //Pode ser NULO.
	D2D1_SIZE_F* pViewPortSize = NULL;
	ID2D1SvgDocument* pOutDocSvg = NULL;

	//Recupera a interface para o stream se fornecido.
	if (ObjetoGerenciadoValido(Param_InputXmlStream))
	{
		//Recupera o ponteiro para o stream
		Resultado = RecuperarPonteiroCaren(Param_InputXmlStream, &pInputXmlStream);

		//Sai do método em caso de erro
		SairOnError(Resultado);
	}

	//Converte a estrutura
	pViewPortSize = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_Viewportsize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSvgDocument(pInputXmlStream, *pViewPortSize, &pOutDocSvg);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_SvgDocumento = gcnew CarenD2D1SvgDocument();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutDocSvg, Param_Out_SvgDocumento);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pViewPortSize);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha um documento SVG. 
/// </summary>
/// <param name="Param_SvgDocumento">O documento SVG para desenhar.</param>
void CarenD2D1DeviceContext5::DrawSvgDocument(ICarenD2D1SvgDocument^ Param_SvgDocumento)
{
	//Variaveis a serem utilizadas.
	ID2D1SvgDocument* pSvgDoc = NULL;

	//Recupera o ponteiro para o documento svg.
	RecuperarPonteiroCaren(Param_SvgDocumento, &pSvgDoc);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawSvgDocument(pSvgDoc);
}




// Métodos da interface (ICarenD2D1DeviceContext4)


/// <summary>
/// Cria um objeto estilo glifo SVG.
/// </summary>
/// <param name="Param_Out_SvgGlyphStyle">Retorna uma interface(ICarenD2D1SvgGlyphStyle) que contém um ponteiro para o novo Glyph Style.</param>
CarenResult CarenD2D1DeviceContext5::CreateSvgGlyphStyle(
	[Out] ICarenD2D1SvgGlyphStyle^% Param_Out_SvgGlyphStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SvgGlyphStyle* pMyOutSvgStyle = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSvgGlyphStyle(&pMyOutSvgStyle);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_SvgGlyphStyle = gcnew CarenD2D1SvgGlyphStyle();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutSvgStyle, Param_Out_SvgGlyphStyle);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha uma cor bitmap glifo executado usando um dos formatos bitmap.
/// </summary>
/// <param name="Param_GlyphImageFormat">Especifica o formato da imagem glifo. Os formatos suportados são DWRITE_GLYPH_IMAGE_FORMATS_PNG, DWRITE_GLYPH_IMAGE_FORMATS_JPEG, DWRITE_GLYPH_IMAGE_FORMATS_TIFF ou DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8. Este método resultará em um erro se a execução do glifo de cor não contiver o formato solicitado.
/// Apenas um formato pode ser especificado de cada vez, combinações de bandeiras não são entradas válidas.</param>
/// <param name="Param_BaselineOrigin">A origem da linha de base para a corrida do glifo.</param>
/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
/// <param name="Param_MeasuringMode">Indica o método de medição.</param>
/// <param name="Param_BitmapSnapOption">Especifica a política de estalo de pixels ao renderizar glifos bitmap de cor.</param>
void CarenD2D1DeviceContext5::DrawColorBitmapGlyphRun(
	CA_DWRITE_GLYPH_IMAGE_FORMATS Param_GlyphImageFormat,
	CA_D2D1_POINT_2F^ Param_BaselineOrigin,
	CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode,
	CA_D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION Param_BitmapSnapOption)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMyBaseLine = NULL;
	DWRITE_GLYPH_RUN* pMyGlyphRun = NULL;

	//Converte as estruturas
	pMyBaseLine = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaselineOrigin);
	pMyGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlyphRun);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawColorBitmapGlyphRun(
		static_cast<DWRITE_GLYPH_IMAGE_FORMATS>(Param_GlyphImageFormat),
		*pMyBaseLine,
		pMyGlyphRun,
		static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode),
		static_cast<D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION>(Param_BitmapSnapOption)
	);

	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pMyBaseLine);
	DeletarEstruturaSafe(&pMyGlyphRun);
}

/// <summary>
/// Desenha uma tira glifo colorida que tem o formato de DWRITE_GLYPH_IMAGE_FORMATS_SVG. 
/// </summary>
/// <param name="Param_BaselineOrigin">A origem da linha de base para a corrida do glifo.</param>
/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
/// <param name="Param_DefaultFillBrush">O pincel usado para pintar os glifos especificados.</param>
/// <param name="Param_SvgGlyphStyle">Valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor. Observe que isso não é o mesmo que a paletaIndex na estrutura DWRITE_COLOR_GLYPH_RUN, o que não é relevante para os glifos SVG.</param>
/// <param name="Param_MeasuringMode">Indica o método de medição usado para layout de texto.</param>
void CarenD2D1DeviceContext5::DrawSvgGlyphRun(
	CA_D2D1_POINT_2F^ Param_BaselineOrigin,
	CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
	UInt32 Param_ColorPaletteIndex,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMyBaseLine = NULL;
	DWRITE_GLYPH_RUN* pMyGlyphRun = NULL;
	ID2D1Brush* pMyFillBrush = NULL;
	ID2D1SvgGlyphStyle* pMySvgStyle = NULL;

	//Converte as estruturas
	pMyBaseLine = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaselineOrigin);
	pMyGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlyphRun);

	//Recupera os ponteiros para as interfaces
	RecuperarPonteiroCaren(Param_DefaultFillBrush, &pMyFillBrush);
	RecuperarPonteiroCaren(Param_SvgGlyphStyle, &pMySvgStyle);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawSvgGlyphRun
	(
		*pMyBaseLine,
		pMyGlyphRun,
		pMyFillBrush,
		pMySvgStyle,
		Param_ColorPaletteIndex,
		static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode)
	);

	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pMyBaseLine);
	DeletarEstruturaSafe(&pMyGlyphRun);
}

/// <summary>
/// Desenha o texto dentro do retângulo de layout dado. Por padrão, este método executa o snapping da linha de base e torna as versões coloridas de glifos em fontes coloridas.
/// </summary>
/// <param name="Param_Texto">Uma string que contém a sequencia para desenhar.</param>
/// <param name="Param_LarguraTexto">O número de caracteres em (Param_Texto).</param>
/// <param name="Param_FormatoTexto">Uma interface(IDWriteTextFormat)[SDK PENDENTE] que descreve a formatação de detalhes do texto para desenhar, como a fonte, o tamanho da fonte e a direção do fluxo.</param>
/// <param name="Param_LayoutRect">O tamanho e a posição da área em que o texto é desenhado.</param>
/// <param name="Param_DefaultFillBrush">O pincel usado para pintar o texto.</param>
/// <param name="Param_SvgGlyphStyle">Valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor.</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
void CarenD2D1DeviceContext5::DrawText(
	String^ Param_Texto,
	UInt32 Param_LarguraTexto,
	ICaren^ Param_FormatoTexto,
	CA_D2D1_RECT_F^ Param_LayoutRect,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
	UInt32 Param_ColorPaletteIndex,
	CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pMyTexto = NULL;
	IDWriteTextFormat* pMyTextFormato = NULL;
	D2D1_RECT_F* pMyLayoutRect = NULL;
	ID2D1Brush* pMyFillBrush = NULL;
	ID2D1SvgGlyphStyle* pMySvgStyle = NULL;

	//Converte a string
	pMyTexto = Util.ConverterStringToWCHAR(Param_Texto);

	//Converte a estrutura
	pMyLayoutRect = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_LayoutRect);

	//Recupera os ponteiros para as interfaces
	RecuperarPonteiroCaren(Param_FormatoTexto, &pMyTextFormato);
	RecuperarPonteiroCaren(Param_DefaultFillBrush, &pMyFillBrush);
	RecuperarPonteiroCaren(Param_SvgGlyphStyle, &pMySvgStyle);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawText
	(
		pMyTexto,
		Param_LarguraTexto,
		pMyTextFormato,
		pMyLayoutRect,
		pMyFillBrush,
		pMySvgStyle,
		Param_ColorPaletteIndex,
		static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes),
		static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode)
	);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyLayoutRect);
	//Libera a memória para o texto
	DeletarStringAllocatedSafe(&pMyTexto);
}

/// <summary>
/// Desenha um objeto de layout de texto. Se o layout não for alterado posteriormente, isso pode ser mais eficiente do que o DrawText ao desenhar o mesmo layout repetidamente. 
/// </summary>
/// <param name="Param_Origin">O ponto, descrito em pixels independentes do dispositivo, no qual o canto superior esquerdo do texto descrito pelo (Param_TextLayout) é desenhado.</param>
/// <param name="Param_TextLayout">Uma interface(IDWriteTextLayout)[SDK PENDENTE] que representa o texto formatado para desenhar. Quaisquer efeitos de desenho que não herdem do ICarenD2D1Resource são ignorados. Se houver efeitos de desenho que herdam do ICarenD2D1Resource que não são pincéis, este método falhará e o alvo de renderização é colocado em um estado de erro.</param>
/// <param name="Param_DefaultFillBrush">O pincel usado para pintar o texto.</param>
/// <param name="Param_SvgGlyphStyle">Os valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor.</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
void CarenD2D1DeviceContext5::DrawTextLayout(
	CA_D2D1_POINT_2F^ Param_Origin,
	ICaren^ Param_TextLayout,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
	UInt32 Param_ColorPaletteIndex,
	CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMyOrigin = NULL;
	IDWriteTextLayout* pMyTextLayout = NULL;
	ID2D1Brush* pMyFillBrush = NULL;
	ID2D1SvgGlyphStyle* pMySvgStyle = NULL;

	//Converte a estrutura.
	pMyOrigin = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Origin);

	//Recupera o ponteiro para as interfaces.
	RecuperarPonteiroCaren(Param_TextLayout, &pMyTextLayout);
	RecuperarPonteiroCaren(Param_DefaultFillBrush, &pMyFillBrush);
	RecuperarPonteiroCaren(Param_SvgGlyphStyle, &pMySvgStyle);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawTextLayout
	(
		*pMyOrigin,
		pMyTextLayout,
		pMyFillBrush,
		pMySvgStyle,
		Param_ColorPaletteIndex,
		static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes)
	);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyOrigin);
}

/// <summary>
/// Recupera uma imagem do glifo bitmap de cor do cache glifo de cor. Se o cache ainda não contiver o recurso solicitado, ele será criado. Este método pode ser usado para estender a vida útil de uma imagem glifo mesmo depois de ser despejado do cache glifo de cor.
/// </summary>
/// <param name="Param_GlyphImageFormat">O formato da imagem glifo. Se não houver dados de imagem no formato solicitado para o glifo solicitado, este método retornará um erro.</param>
/// <param name="Param_GlyphOrigin">A origem do glifo.</param>
/// <param name="Param_FontFace">Uma interface(IDWriteFontFace)[SDK PENDENTE] que faz referência a uma face de fonte que contém o tipo de fonte, referências de arquivo apropriadas, dados de identificação de faces e vários dados de fontes, como métricas, nomes e contornos de glifos.</param>
/// <param name="Param_FontSize">O tamanho da fonte especificado afeta a escolha de qual bitmap usar a partir da fonte. Também afeta o glifo de saídaTransforme, fazendo com que ele dimensione adequadamente o glifo.</param>
/// <param name="Param_GlyphIndex">Índice do glifo.</param>
/// <param name="Param_IsSideways">Se for verdade, especifica que os glifos são girados 90 graus para a esquerda e as métricas verticais são usadas. A escrita vertical é obtida especificando isSideways como verdadeiro e girando toda a corrida 90 graus para a direita através de uma transformação rotativa.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à imagem. Essa transformação de entrada afeta a escolha de qual bitmap usar a partir da fonte. Também é levado em conta o glifo de saídaTransform.</param>
/// <param name="Param_DpiX">Pontos por polegada ao longo do eixo X.</param>
/// <param name="Param_DpiY">Pontos por polegada ao longo do eixo Y.</param>
/// <param name="Param_Out_GlyphTransform">Retorna a transformação de saída, que se transforma do espaço do glifo para o mesmo espaço de saída que o mundoTransforme. Isso inclui o gliforgin de entrada, o deslocamento do glifo do glifo e quaisquer outras transformações necessárias.</param>
/// <param name="Param_Out_GlyphImage">Retorna uma interface(ICarenD2D1Image) que contém um ponteiro para a image glifo recuperada.</param>
CarenResult CarenD2D1DeviceContext5::GetColorBitmapGlyphImage(
	CA_DWRITE_GLYPH_IMAGE_FORMATS Param_GlyphImageFormat,
	CA_D2D1_POINT_2F^ Param_GlyphOrigin,
	ICaren^ Param_FontFace,
	float Param_FontSize,
	UInt16 Param_GlyphIndex,
	Boolean Param_IsSideways,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	float Param_DpiX,
	float Param_DpiY,
	[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_GlyphTransform,
	[Out] ICarenD2D1Image^% Param_Out_GlyphImage)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pGlyphOrigin = NULL;
	IDWriteFontFace* pFontFace = NULL;
	D2D1_MATRIX_3X2_F* pWorldTransform = NULL;
	D2D1_MATRIX_3X2_F OutGlyphTransform = {};
	ID2D1Image* pOutGlyphImage = NULL;

	//Converte as estrturas
	pGlyphOrigin = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_GlyphOrigin);
	pWorldTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform);

	//Recupera o ponteiro para a interface de tipo da fonte.
	Resultado = RecuperarPonteiroCaren(Param_FontFace, &pFontFace);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetColorBitmapGlyphImage
	(
		static_cast<DWRITE_GLYPH_IMAGE_FORMATS>(Param_GlyphImageFormat),
		*pGlyphOrigin,
		pFontFace,
		Param_FontSize,
		Param_GlyphIndex,
		Param_IsSideways ? TRUE : FALSE,
		pWorldTransform,
		Param_DpiX,
		Param_DpiY,
		&OutGlyphTransform,
		&pOutGlyphImage
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a estrutura a ser retornada.
	Param_Out_GlyphTransform = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutGlyphTransform);

	//Cria a interface a ser retronada.
	Param_Out_GlyphImage = gcnew CarenD2D1Image();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutGlyphImage, Param_Out_GlyphImage);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pGlyphOrigin);
	DeletarEstruturaSafe(&pWorldTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera uma imagem do glifo SVG do cache glifo de cor. Se o cache ainda não contiver o recurso solicitado, ele será criado. Este método pode ser usado para estender a vida útil de uma imagem glifo mesmo depois de ser despejado do cache glifo de cor.
/// </summary>
/// <param name="Param_GlyphOrigin">Origem do glifo.</param>
/// <param name="Param_FontFace">Uma interface(IDWriteFontFace)[SDK PENDENTE] que faz referência a uma face de fonte que contém o tipo de fonte, referências de arquivo apropriadas, dados de identificação de faces e vários dados de fontes, como métricas, nomes e contornos de glifos.</param>
/// <param name="Param_FontSize">O tamanho da fonte especificado afeta o glifo de saídaTransforme, fazendo com que ele dimensione corretamente o glifo.</param>
/// <param name="Param_GlyphIndex">Índice do glifo para recuperar.</param>
/// <param name="Param_IsSideways">Se for verdade, especifica que os glifos são girados 90 graus para a esquerda e as métricas verticais são usadas. A escrita vertical é obtida especificando isSideways como verdadeiro e girando toda a corrida 90 graus para a direita através de uma transformação rotativa.</param>
/// <param name="Param_WorldTransform">A transformação para aplicar à imagem.</param>
/// <param name="Param_DefaultFillBrush">Descreve como a área é pintada.</param>
/// <param name="Param_SvgGlyphStyle">Os valores para preenchimento de contexto, contexto-traçado e valor de contexto que são usados ao renderizar glifos SVG.</param>
/// <param name="Param_ColorPaletteIndex">O índice usado para selecionar uma paleta de cores dentro de uma fonte de cor. Observe que isso não é o mesmo que a paletaIndex na estrutura DWRITE_COLOR_GLYPH_RUN, o que não é relevante para os glifos SVG.</param>
/// <param name="Param_Out_GlyphTransform">Retorna transformação de saída, que se transforma do espaço do glifo para o mesmo espaço de saída que o mundoTransforme. Isso inclui o gliforgin de entrada, o deslocamento do glifo do glifo e quaisquer outras transformações necessárias.</param>
/// <param name="Param_Out_GlyphImage">Retorna uma interface(ICarenD2D1CommandList) que contém um ponteiro para a imagem glifo recuperada.</param>
CarenResult CarenD2D1DeviceContext5::GetSvgGlyphImage(
	CA_D2D1_POINT_2F^ Param_GlyphOrigin,
	ICaren^ Param_FontFace,
	float Param_FontSize,
	UInt16 Param_GlyphIndex,
	Boolean Param_IsSideways,
	CA_D2D1_MATRIX_3X2_F^ Param_WorldTransform,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	ICarenD2D1SvgGlyphStyle^ Param_SvgGlyphStyle,
	UInt32 Param_ColorPaletteIndex,
	[Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_GlyphTransform,
	[Out] ICarenD2D1CommandList^% Param_Out_GlyphImage)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pGlyphOrigin = NULL;
	IDWriteFontFace* pFontFace = NULL;
	D2D1_MATRIX_3X2_F* pWorldTransform = NULL;
	ID2D1Brush* pFillBrush = NULL;
	ID2D1SvgGlyphStyle* pSvgStyle = NULL;
	D2D1_MATRIX_3X2_F OutGlyphTransform = {};
	ID2D1CommandList* pOutCommandList = NULL;

	//Converte as estrturas
	pGlyphOrigin = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_GlyphOrigin);
	pWorldTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_WorldTransform);

	//Recupera o ponteiro para a interface de tipo da fonte.
	Resultado = RecuperarPonteiroCaren(Param_FontFace, &pFontFace);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do brush.
	Resultado = RecuperarPonteiroCaren(Param_DefaultFillBrush, &pFillBrush);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface estilo do glifo.
	Resultado = RecuperarPonteiroCaren(Param_SvgGlyphStyle, &pSvgStyle);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetSvgGlyphImage
	(
		*pGlyphOrigin,
		pFontFace,
		Param_FontSize,
		Param_GlyphIndex,
		Param_IsSideways ? TRUE : FALSE,
		pWorldTransform,
		pFillBrush,
		pSvgStyle,
		Param_ColorPaletteIndex,
		&OutGlyphTransform,
		&pOutCommandList
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define a estrutura a ser retornada.
	Param_Out_GlyphTransform = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutGlyphTransform);

	//Cria a interface a ser retronada.
	Param_Out_GlyphImage = gcnew CarenD2D1CommandList();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutCommandList, Param_Out_GlyphImage);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pGlyphOrigin);
	DeletarEstruturaSafe(&pWorldTransform);

	//Retorna o resultado.
	return Resultado;
}



// Métodos da interface (ICarenD2D1DeviceContext3)


/// <summary>
/// Cria um novo lote de sprite vazio. Depois de criar um lote sprite, use ICarenD2D1SpriteBatch::AddSprites para adicionar sprites a ele e, em seguida, use ICarenD2D1DeviceContext3::DrawSpriteBatch para desenhá-lo.
/// </summary>
/// <param name="Param_Out_SpriteBatch">Retorna uma interface(ICarenD2D1SpriteBatch) que contém um ponteiro para o novo lote de sprites vazio para ser preenchido.</param>
CarenResult CarenD2D1DeviceContext5::CreateSpriteBatch(
	[Out] ICarenD2D1SpriteBatch^% Param_Out_SpriteBatch)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1SpriteBatch* pMyOutSprite = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSpriteBatch(&pMyOutSprite);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_SpriteBatch = gcnew CarenD2D1SpriteBatch();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutSprite, Param_Out_SpriteBatch);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Renderiza todos os sprites no lote sprite dado ao contexto do dispositivo usando as opções de desenho especificadas.
/// </summary>
/// <param name="Param_SpriteBatch">>O lote de sprite para desenhar.</param>
/// <param name="Param_StartIndex">O índice do primeiro sprite no lote sprite para desenhar.</param>
/// <param name="Param_QuantidadeSprite">O número de sprites para desenhar.</param>
/// <param name="Param_Bitmap">O bitmap do qual os sprites devem ser originários. O retângulo de cada fonte de sprite refere-se a uma parte deste bitmap.</param>
/// <param name="Param_ModoInterpolacao">O modo de interpolação a ser usado ao desenhar este lote sprite. Isso determina como o Direct2D interpola os pixels dentro dos sprites desenhados se o dimensionamento for realizado.</param>
/// <param name="Param_OpcoesSprite">As opções adicionais de desenho, se houver, a serem usadas para este lote sprite.</param>
void CarenD2D1DeviceContext5::DrawSpriteBatch(
	ICarenD2D1SpriteBatch^ Param_SpriteBatch,
	UInt32 Param_StartIndex,
	UInt32 Param_QuantidadeSprite,
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_INTERPOLATION_MODE Param_ModoInterpolacao,
	CA_D2D1_SPRITE_OPTIONS Param_OpcoesSprite
)
{
	//Variaveis a serem utilizadas.
	ID2D1SpriteBatch* pMySprite = NULL;
	ID2D1Bitmap* pMyBitmap = NULL;

	//Recupera o ponteiro para as interfaces.
	RecuperarPonteiroCaren(Param_SpriteBatch, &pMySprite);
	RecuperarPonteiroCaren(Param_Bitmap, &pMyBitmap);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawSpriteBatch(
		pMySprite,
		Param_StartIndex,
		Param_QuantidadeSprite,
		pMyBitmap,
		static_cast<D2D1_BITMAP_INTERPOLATION_MODE>(Param_ModoInterpolacao),
		static_cast<D2D1_SPRITE_OPTIONS>(Param_OpcoesSprite)
	);
}

/// <summary>
/// Renderiza parte ou todo o lote sprite dado ao contexto do dispositivo usando as opções de desenho especificadas.
/// </summary>
/// <param name="Param_SpriteBatch">O lote de sprite para desenhar.</param>
/// <param name="Param_Bitmap">O bitmap do qual os sprites devem ser originários. O retângulo de cada fonte de sprite refere-se a uma parte deste bitmap.</param>
/// <param name="Param_ModoInterpolacao">O modo de interpolação a ser usado ao desenhar este lote sprite. Isso determina como o Direct2D interpola os pixels dentro dos sprites desenhados se o dimensionamento for realizado.</param>
/// <param name="Param_OpcoesSprite">As opções adicionais de desenho, se houver, a serem usadas para este lote sprite.</param>
void CarenD2D1DeviceContext5::DrawSpriteBatch(
	ICarenD2D1SpriteBatch^ Param_SpriteBatch,
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_INTERPOLATION_MODE Param_ModoInterpolacao,
	CA_D2D1_SPRITE_OPTIONS Param_OpcoesSprite)
{
	//Variaveis a serem utilizadas.
	ID2D1SpriteBatch* pMySprite = NULL;
	ID2D1Bitmap* pMyBitmap = NULL;

	//Recupera o ponteiro para as interfaces.
	RecuperarPonteiroCaren(Param_SpriteBatch, &pMySprite);
	RecuperarPonteiroCaren(Param_Bitmap, &pMyBitmap);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawSpriteBatch(
		pMySprite,
		pMyBitmap,
		static_cast<D2D1_BITMAP_INTERPOLATION_MODE>(Param_ModoInterpolacao),
		static_cast<D2D1_SPRITE_OPTIONS>(Param_OpcoesSprite)
	);
}



// Métodos da interface (ICarenD2D1DeviceContext2)


/// <summary>
/// Cria uma nova instância ID2D1GradientMesh usando a matriz dada de patches.
/// </summary>
/// <param name="Param_Patches">Uma matriz contendo as manchas a serem usadas nesta malha.</param>
/// <param name="Param_QuantidadePatches">O número de patches nos patches argumenta para ler.</param>
/// <param name="Param_Out_GradientMesh">Retorna uma interface(ICarenD2D1GradientMesh) que contém um ponteiro para a nova malha de gradiente.</param>
CarenResult CarenD2D1DeviceContext5::CreateGradientMesh(
	cli::array<CA_D2D1_GRADIENT_MESH_PATCH^>^ Param_Patches,
	UInt32 Param_QuantidadePatches,
	[Out] ICarenD2D1GradientMesh^% Param_Out_GradientMesh
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_MESH_PATCH* pMyMatrizPatches = CriarMatrizEstruturas<D2D1_GRADIENT_MESH_PATCH>(Param_QuantidadePatches);
	D2D1_GRADIENT_MESH_PATCH* pMyMeshPathAuxiliar = NULL;
	ID2D1GradientMesh* pMyOutGradientMesh = NULL;

	//Abre um for para copiar os dados para a matriz nativa.
	for (UINT32 i = 0; i < Param_QuantidadePatches; i++)
	{
		//Converte a estrutura o index.
		pMyMeshPathAuxiliar = Util.ConverterD2D1_GRADIENT_MESH_PATCHManagedToUnmanaged(Param_Patches[i]);

		//Define na matriz nativa.
		pMyMatrizPatches[i] = *pMyMeshPathAuxiliar;

		//Libera a memória para a estrutura
		DeletarEstruturaSafe(&pMyMeshPathAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientMesh(pMyMatrizPatches, Param_QuantidadePatches, &pMyOutGradientMesh);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_GradientMesh = gcnew CarenD2D1GradientMesh();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutGradientMesh, Param_Out_GradientMesh);

Done:;
	//Libera a memória para a matriz de estruturas
	DeletarMatrizEstruturasSafe(&pMyMatrizPatches);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma fonte de imagem a partir de um conjunto de superfícies DXGI. As superfícies YCbCr são convertidas automaticamente para RGBA durante o desenho subsequente.
/// A GPU também deve ter suporte suficiente para que um formato de pixel seja suportado por D2D. Para determinar se o D2D suporta um formato, ligue para o IsDxgiFormatSupported.
/// Esta API converte formatos YCbCr em sRGB usando o tipo e as opções de espaço de cores fornecidas. Presume-se que os dados RGBA estejam no espaço desejado e o D2D não aplique nenhuma conversão.
/// </summary>
/// <param name="Param_DxgiSurfaces">Uma matriz superfices do DXGI para serem usadas.</param>
/// <param name="Param_QuantidadeSuperficesDXGI">O número de superfícies fornecidas; deve ser entre um e três.</param>
/// <param name="Param_EspacoCor">O espaço de cor da entrada.</param>
/// <param name="Param_Opcoes">Opções controlando conversões de espaço de cores.</param>
/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSource) que contém um ponteiro para a nova fonte de imagem.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageSourceFromDxgi(
	cli::array<ICaren^>^ Param_DxgiSurfaces,
	UInt32 Param_QuantidadeSuperficesDXGI,
	CA_DXGI_COLOR_SPACE_TYPE Param_EspacoCor,
	CA_D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS Param_Opcoes,
	[Out] ICarenD2D1ImageSource^% Param_Out_ImageSource
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGISurface** pMyMatrizSurfaces = CriarMatrizPonteiros<IDXGISurface>(Param_QuantidadeSuperficesDXGI);
	DXGI_COLOR_SPACE_TYPE MyDxgiColorSpace = static_cast<DXGI_COLOR_SPACE_TYPE>(Param_EspacoCor);
	D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS MyOptions = static_cast<D2D1_IMAGE_SOURCE_FROM_DXGI_OPTIONS>(Param_Opcoes);
	ID2D1ImageSource* pMyOutImageSource = NULL;

	//Faz um for para definir os ponteiros na matriz nativa.
	for (UINT32 i = 0; i < Param_QuantidadeSuperficesDXGI; i++)
	{
		//Recupera o ponteiro e define no index da matriz nativa.
		RecuperarPonteiroCaren(Param_DxgiSurfaces[i], &(pMyMatrizSurfaces[i]));
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageSourceFromDxgi(
		pMyMatrizSurfaces,
		Param_QuantidadeSuperficesDXGI,
		MyDxgiColorSpace,
		MyOptions,
		&pMyOutImageSource);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ImageSource = gcnew CarenD2D1ImageSource();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutImageSource, Param_Out_ImageSource);

Done:;
	//Libera a memória para a matriz de ponteiros
	DeletarMatrizPonteirosSafe(&pMyMatrizSurfaces); //Vai apenas liberar a memória, não libera os ponteiros.

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
/// Este método cria uma fonte de imagem que pode ser usada para desenhar a imagem.
/// Este método suporta imagens que excedem o tamanho máximo da textura. Grandes imagens são armazenadas internamente dentro de um cache de ladrilhos esparsos.
/// </summary>
/// <param name="Param_WicBitmapSource">A fonte de bitmap WIC para criar a fonte de imagem.</param>
/// <param name="Param_OpcoesCarregamento">Opções para criar a fonte de imagem. As opções padrão são usadas se NULO.</param>
/// <param name="Param_ModoAlfa">O modo alfa da imagem; isso é determinado automaticamente a partir do formato de pixel da fonte se D2D1_ALPHA_MODE_UNKNOWN for aprovada.</param>
/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageSourceFromWic(
	ICaren^ Param_WicBitmapSource,
	CA_D2D1_IMAGE_SOURCE_LOADING_OPTIONS Param_OpcoesCarregamento,
	CA_D2D1_ALPHA_MODE Param_ModoAlfa,
	[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pMyBitmapSource = NULL;
	D2D1_IMAGE_SOURCE_LOADING_OPTIONS MySourceLoadOptions = static_cast<D2D1_IMAGE_SOURCE_LOADING_OPTIONS>(Param_OpcoesCarregamento);
	D2D1_ALPHA_MODE MyAlphaMode = static_cast<D2D1_ALPHA_MODE>(Param_ModoAlfa);
	ID2D1ImageSourceFromWic* pMyOutImageSource = NULL;

	//Recupera o ponteiro para o bitmap source.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapSource, &pMyBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageSourceFromWic(pMyBitmapSource, MySourceLoadOptions, MyAlphaMode, &pMyOutImageSource);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ImageSource = gcnew CarenD2D1ImageSourceFromWic();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutImageSource, Param_Out_ImageSource);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) que representa a fonte de bitmap WIC para criar a fonte de imagem.</param>
/// <param name="Param_OpcoesCarregamento">Opções para criar a fonte de imagem. As opções padrão são usadas se NULO.</param>
/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageSourceFromWic(
	ICaren^ Param_WicBitmapSource,
	CA_D2D1_IMAGE_SOURCE_LOADING_OPTIONS Param_OpcoesCarregamento,
	[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pMyBitmapSource = NULL;
	D2D1_IMAGE_SOURCE_LOADING_OPTIONS MySourceLoadOptions = static_cast<D2D1_IMAGE_SOURCE_LOADING_OPTIONS>(Param_OpcoesCarregamento);
	ID2D1ImageSourceFromWic* pMyOutImageSource = NULL;

	//Recupera o ponteiro para o bitmap source.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapSource, &pMyBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageSourceFromWic(pMyBitmapSource, MySourceLoadOptions, &pMyOutImageSource);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ImageSource = gcnew CarenD2D1ImageSourceFromWic();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutImageSource, Param_Out_ImageSource);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto de origem de imagem a partir de uma fonte de bitmap WIC, enquanto preenche toda a memória de pixel dentro da fonte de imagem. A imagem é carregada e armazenada enquanto usa uma quantidade mínima de memória.
/// Este método cria uma fonte de imagem que pode ser usada para desenhar a imagem.
/// Este método suporta imagens que excedem o tamanho máximo da textura. Grandes imagens são armazenadas internamente dentro de um cache de ladrilhos esparsos.
/// Esta API suporta o mesmo conjunto de formatos de pixels e modos alfa suportados pelo CreateBitmapFromWicBitmap.
/// </summary>
/// <param name="Param_WicBitmapSource">A fonte de bitmap WIC para criar a fonte de imagem.</param>
/// <param name="Param_Out_ImageSource">Retorna uma interface(ICarenD2D1ImageSourceFromWic) que contém um ponteiro para a nova fonte de imagem.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageSourceFromWic(
	ICaren^ Param_WicBitmapSource,
	[Out] ICarenD2D1ImageSourceFromWic^% Param_Out_ImageSource
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pMyBitmapSource = NULL;
	ID2D1ImageSourceFromWic* pMyOutImageSource = NULL;

	//Recupera o ponteiro para o bitmap source.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapSource, &pMyBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageSourceFromWic(pMyBitmapSource, &pMyOutImageSource);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_ImageSource = gcnew CarenD2D1ImageSourceFromWic();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutImageSource, Param_Out_ImageSource);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo objeto ICarenD2D1Ink que começa no ponto determinado.
/// </summary>
/// <param name="Param_StartPoint"> O ponto de partida do primeiro segmento do primeiro curso no novo objeto de tinta.</param>
/// <param name="Param_Out_Ink">Retorna uma interface(ICarenD2D1Ink) que contém um ponteiro para um novo objeto de tinta.</param>
CarenResult CarenD2D1DeviceContext5::CreateInk(
	CA_D2D1_INK_POINT^ Param_StartPoint,
	[Out] ICarenD2D1Ink^% Param_Out_Ink
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_POINT* pMyInkPoint = NULL;
	ID2D1Ink* pMyOutInk = NULL;

	//Converte a estrutura.
	pMyInkPoint = Util.ConverterD2D1_INK_POINTManagedToUnmanaged(Param_StartPoint);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInk(pMyInkPoint, &pMyOutInk);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_Ink = gcnew CarenD2D1Ink();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutInk, Param_Out_Ink);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyInkPoint);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo objeto ICarenD2D1InkStyle, para uso com métodos de renderização de tinta, como o DrawInk.
/// </summary>
/// <param name="Param_PropsInkStyle">As propriedades do estilo de tinta a serem criadas.</param>
/// <param name="Param_Out_InkStyle">Retorna uma interface(ICarenD2D1InkStyle) que contém um ponteiro para um novo objeto de estilo de tinta.</param>
CarenResult CarenD2D1DeviceContext5::CreateInkStyle(
	CA_D2D1_INK_STYLE_PROPERTIES^ Param_PropsInkStyle,
	[Out] ICarenD2D1InkStyle^% Param_Out_InkStyle
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_INK_STYLE_PROPERTIES* pMyInkStyleProps = NULL;
	ID2D1InkStyle* pMyOutInkStyle = NULL;

	//Converte a estrutura
	pMyInkStyleProps = Util.ConverterD2D1_INK_STYLE_PROPERTIESManagedToUnmanaged(Param_PropsInkStyle);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateInkStyle(pMyInkStyleProps, &pMyOutInkStyle);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_InkStyle = gcnew CarenD2D1InkStyle();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutInkStyle, Param_Out_InkStyle);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyInkStyleProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma tabela de pesquisa 3D para mapear uma entrada de 3 canais para uma saída de 3 canais. Os dados da tabela devem ser fornecidos em formato de 4 canais.
/// </summary>
/// <param name="Param_BufferPrecision">Precisão dos dados da tabela de pesquisa de entrada.</param>
/// <param name="Param_Extents">Número de elementos de tabela de procuração por dimensão (X, Y, Z).</param>
/// <param name="Param_Data">Buffer segurando os dados da tabela de pesquisa.</param>
/// <param name="Param_BufferSize">Tamanho do buffer de dados da tabela de pesquisa.</param>
/// <param name="Param_Strides">Uma matriz contendo dois valores. O primeiro valor é o tamanho em bytes de uma linha (dimensão X) de dados LUT para a próxima. O segundo valor é o tamanho em bytes de um plano de dados LUT (dimensões X e Y) para o próximo.</param>
/// <param name="Param_Out_LookupTable">Retorna uma interface(ICarenD2D1LookupTable3D) que contém um ponteiro para a nova tabela de procuração.</param>
CarenResult CarenD2D1DeviceContext5::CreateLookupTable3D(
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	cli::array<UInt32>^ Param_Extents,
	ICarenBuffer^ Param_Data,
	UInt32 Param_BufferSize,
	cli::array<UInt32>^ Param_Strides,
	[Out] ICarenD2D1LookupTable3D^% Param_Out_LookupTable
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_BUFFER_PRECISION MyBufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	UINT32* pMyMatrizExtents = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Extents->Length));
	GenPointer pMyBufferData = IntPtr::Zero;
	UINT32* pMyMatrizStrides = CriarMatrizUnidimensional<UINT32>(static_cast<DWORD>(Param_Strides->Length));
	ID2D1LookupTable3D* pMyOutLookupTable = NULL;

	//Copia os dados para as matrizes nativas.
	Util.CopiarItensTo_ArrayNativo(&pMyMatrizExtents, Param_Extents, static_cast<UINT32>(Param_Extents->Length));
	Util.CopiarItensTo_ArrayNativo(&pMyMatrizStrides, Param_Strides, static_cast<UINT32>(Param_Strides->Length));

	//Recupera o ponteiro para o buffer de dados.
	Resultado = Param_Data->GetInternalPointer(pMyBufferData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CreateLookupTable3D(
		MyBufferPrecision,
		pMyMatrizExtents,
		Util.ConverterIntPtrTo<PBYTE>(pMyBufferData),
		Param_BufferSize,
		pMyMatrizStrides,
		&pMyOutLookupTable
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_LookupTable = gcnew CarenD2D1LookupTable3D();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutLookupTable, Param_Out_LookupTable);

Done:;
	//Libera a memória para as matrizes
	DeletarMatrizUnidimensionalSafe(&pMyMatrizExtents);
	DeletarMatrizUnidimensionalSafe(&pMyMatrizStrides);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma fonte de imagem que compartilha recursos com um original.
/// </summary>
/// <param name="Param_FonteImagem">A imagem original.</param>
/// <param name="Param_Propriedades">Propriedades para a imagem de origem.</param>
/// <param name="Param_Out_TransformedImageSource">Retorna uma interface(ICarenD2D1TransformedImageSource) que contém um ponteiro para a nova fonte de imagem.</param>
CarenResult CarenD2D1DeviceContext5::CreateTransformedImageSource(
	ICarenD2D1ImageSource^ Param_FonteImagem,
	CA_D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES^ Param_Propriedades,
	[Out] ICarenD2D1TransformedImageSource^% Param_Out_TransformedImageSource
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1ImageSource* pMyImageSource = NULL;
	D2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIES* pMyProps = NULL;
	ID2D1TransformedImageSource* pMyOutTransformedImage = NULL;

	//Recupera o ponteiro para a interface da imagem.
	Resultado = RecuperarPonteiroCaren(Param_FonteImagem, &pMyImageSource);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura.
	pMyProps = Util.ConverterD2D1_TRANSFORMED_IMAGE_SOURCE_PROPERTIESManagedToUnmanaged(Param_Propriedades);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTransformedImageSource(pMyImageSource, pMyProps, &pMyOutTransformedImage);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_TransformedImageSource = gcnew CarenD2D1TransformedImageSource();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutTransformedImage, Param_Out_TransformedImageSource);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha um metafile para o contexto do dispositivo usando os retângulos de origem e destino dado.
/// </summary>
/// <param name="Param_GdiMetafile">O metafile para desenhar.</param>
/// <param name="Param_RetanguloDestino">O retângulo no alvo onde o metafile será desenhado, em relação ao canto superior esquerdo (definido em DIPs) do alvo render. Se null for especificado, o retângulo de destino é {0, 0, w, h}, onde w e h são a largura e altura do metafile conforme relatado pelo ICarenD2D1GdiMetafile::GetBounds.</param>
/// <param name="Param_RetanguloOrigem">O retângulo do metafile de origem que será desenhado, em relação ao canto superior esquerdo (definido em DIPs) do metafile. Se null for especificado, o retângulo de origem é o valor devolvido pelo ICarenD2D1GdiMetafile1::GetSourceBounds.</param>
void CarenD2D1DeviceContext5::DrawGdiMetafile(
	ICaren^ Param_GdiMetafile,
	CA_D2D1_RECT_F^ Param_RetanguloDestino,
	CA_D2D1_RECT_F^ Param_RetanguloOrigem
)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1GdiMetafile* pMyGdiDraw = NULL;
	D2D1_RECT_F* pMyRectDestino = NULL; //Pode ser NULO.
	D2D1_RECT_F* pMyRectOrigem = NULL; //Pode ser NULO.

	//Recupera o ponteiro para o gdi meta file.
	RecuperarPonteiroCaren(Param_GdiMetafile, &pMyGdiDraw);

	//Converte as estruturas se forem especificadas.
	pMyRectDestino = ObjetoGerenciadoValido(Param_RetanguloDestino) ? Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino) : NULL;
	pMyRectOrigem = ObjetoGerenciadoValido(Param_RetanguloOrigem) ? Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem) : NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGdiMetafile(pMyGdiDraw, pMyRectDestino, pMyRectOrigem);

	//Libera a memória para as estrututas
	DeletarEstruturaSafe(&pMyRectDestino);
	DeletarEstruturaSafe(&pMyRectOrigem);
}

/// <summary>
/// Renderiza uma determinada malha gradiente ao alvo.
/// </summary>
/// <param name="Param_GradientMesh">A malha de gradiente a ser renderizada.</param>
void CarenD2D1DeviceContext5::DrawGradientMesh(
	ICarenD2D1GradientMesh^ Param_GradientMesh
)
{
	//Variaveis a serem utilizadas.
	ID2D1GradientMesh* pMyGradientMesh = NULL;

	//Recupera o ponteiro para o gradient
	RecuperarPonteiroCaren(Param_GradientMesh, &pMyGradientMesh);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGradientMesh(pMyGradientMesh);
}

/// <summary>
/// Renderiza o objeto de tinta dado usando o estilo pincel e tinta dado.
/// </summary>
/// <param name="Param_Ink">O objeto de tinta a ser renderizado.</param>
/// <param name="Param_Brush">O pincel com o qual renderizar o objeto de tinta.</param>
/// <param name="Param_InkStyle">O estilo de tinta a ser usado ao renderizar o objeto de tinta.</param>
void CarenD2D1DeviceContext5::DrawInk(
	ICarenD2D1Ink^ Param_Ink,
	ICarenD2D1Brush^ Param_Brush,
	ICarenD2D1InkStyle^ Param_InkStyle
)
{
	//Variaveis a serem utilizadas.
	ID2D1Ink* pMyInk = NULL;
	ID2D1Brush* pMyBrush = NULL;
	ID2D1InkStyle* pMyInkStyle = NULL;

	//Recupera o ponteiro para as interfaces.
	RecuperarPonteiroCaren(Param_Ink, &pMyInk);
	RecuperarPonteiroCaren(Param_Brush, &pMyBrush);
	RecuperarPonteiroCaren(Param_InkStyle, &pMyInkStyle);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawInk(pMyInk, pMyBrush, pMyInkStyle);
}

/// <summary>
/// Obtém o World de uma determinada malha gradiente.
/// </summary>
/// <param name="Param_GradientMesh">A malha de gradiente cujos limites mundiais serão calculados.</param>
/// <param name="Param_Out_Bounds">Retorna uma estrutura que contém os limites da malha gradiente, em pixels independentes do dispositivo (DIPs).</param>
CarenResult CarenD2D1DeviceContext5::GetGradientMeshWorldBounds(
	ICarenD2D1GradientMesh^ Param_GradientMesh,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1GradientMesh* pMyGradientMesh = NULL;
	D2D1_RECT_F MyOutWorldBounds = {};

	//Recupera o ponteiro para a interface do gradient mesh.
	Resultado = RecuperarPonteiroCaren(Param_GradientMesh, &pMyGradientMesh);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGradientMeshWorldBounds(pMyGradientMesh, &MyOutWorldBounds);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte a estrutura e define no parametro de saida.
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&MyOutWorldBounds);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1DeviceContext1)


/// <summary>
/// Cria uma representação dependente do dispositivo do preenchimento da geometria que pode ser posteriormente renderizada.
/// </summary>
/// <param name="Param_Geometria">A geometria para realizar.</param>
/// <param name="Param_FlatterningTolerance">A tolerância de achatamento para usar ao converter Beziers em segmentos de linha. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
/// <param name="Param_Out_GeometryRealization">Retorna uma interface(ICarenD2D1GeometryRealization) que contém um ponteiro para o novo objeto de realização.</param>
CarenResult CarenD2D1DeviceContext5::CreateFilledGeometryRealization(
	ICarenD2D1Geometry^ Param_Geometria,
	float Param_FlatterningTolerance,
	[Out] ICarenD2D1GeometryRealization^% Param_Out_GeometryRealization)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Geometry* pMyGeometry = NULL;
	ID2D1GeometryRealization* pMyOutGeometryRealization = NULL;

	//Recupera o ponteiro para a interface de geometria
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pMyGeometry);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateFilledGeometryRealization(pMyGeometry, Param_FlatterningTolerance, &pMyOutGeometryRealization);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_GeometryRealization = gcnew CarenD2D1GeometryRealization();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutGeometryRealization, Param_Out_GeometryRealization);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma representação dependente do dispositivo do curso de uma geometria que pode ser posteriormente renderizada.
/// </summary>
/// <param name="Param_Geometria">A geometria para realizar.</param>
/// <param name="Param_FlatterningTolerance">A tolerância de achatamento para usar ao converter Beziers em segmentos de linha. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
/// <param name="Param_StrokeWidth">A largura do traçado. Este parâmetro compartilha as mesmas unidades que as coordenadas da geometria.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado (opcional).</param>
/// <param name="Param_Out_GeometryRealization">Retorna uma interface(ICarenD2D1GeometryRealization) que contém um ponteiro para o novo objeto de realização.</param>
CarenResult CarenD2D1DeviceContext5::CreateStrokedGeometryRealization(
	ICarenD2D1Geometry^ Param_Geometria,
	float Param_FlatterningTolerance,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle,
	[Out] ICarenD2D1GeometryRealization^% Param_Out_GeometryRealization)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Geometry* pMyGeometry = NULL;
	ID2D1StrokeStyle* pMyStrokeStyle = NULL; //Pode ser NULO.
	ID2D1GeometryRealization* pMyOutGeometryRealization = NULL;

	//Recupera o ponteiro para a interface de geometria
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pMyGeometry);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro para a interface do Stroke
		Resultado = RecuperarPonteiroCaren(Param_StrokeStyle, &pMyStrokeStyle);

		//Sai do método em caso de erro.
		SairOnError(Resultado);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateStrokedGeometryRealization(pMyGeometry, Param_FlatterningTolerance, Param_StrokeWidth, pMyStrokeStyle, &pMyOutGeometryRealization);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_GeometryRealization = gcnew CarenD2D1GeometryRealization();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pMyOutGeometryRealization, Param_Out_GeometryRealization);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém uma dada realização de geometria ao alvo com o pincel especificado.
/// Este método respeita todo o estado definido atualmente (transformação, DPI, modo de unidade, imagem de destino, clipes, camadas); no entanto, artefatos como faceta podem aparecer ao renderizar as realizações com uma escala efetiva grande (por meio da transformação ou do DPI). Os chamadores devem criar suas realizações com uma tolerância de nivelamento apropriada usando D2D1_DEFAULT_FLATTENING_TOLERANCE ou ComputeFlatteningTolerance para compensar isso.
/// </summary>
/// <param name="Param_GeometryRealization">A realização da geometria a ser feita.</param>
/// <param name="Param_Brush">O pincel para renderizar a realização.</param>
void CarenD2D1DeviceContext5::DrawGeometryRealization(
	ICarenD2D1GeometryRealization^ Param_GeometryRealization,
	ICarenD2D1Brush^ Param_Brush)
{
	//Variaveis a serem utilizadas.
	ID2D1GeometryRealization* pMyGeometryRealization = NULL;
	ID2D1Brush* pMyBrush = NULL;

	//Recupera o ponteiro para a geometria
	RecuperarPonteiroCaren(Param_GeometryRealization, &pMyGeometryRealization);

	//Recupera o ponteiro para o brush
	RecuperarPonteiroCaren(Param_Brush, &pMyBrush);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGeometryRealization(pMyGeometryRealization, pMyBrush);
}




// Métodos da interface (ICarenD2D1DeviceContext)


/// <summary>
/// Cria um bitmap que pode ser usado como uma superfície de destino, para leitura de volta para a CPU, ou como uma fonte para os APIs ICarenD2D1DeviceContext::DrawBitmap e ICarenD2D1BitmapBrush. Além disso, informações de contexto de cores podem ser passadas para o bitmap.
/// O novo bitmap pode ser usado como um alvo para ICarenD2D1DeviceContext::SetTarget se for criado com D2D1_BITMAP_OPTIONS_TARGET.
/// </summary>
/// <param name="Param_Size">O tamanho do pixel do bitmap a ser criado.</param>
/// <param name="Param_SourceData">Os dados iniciais que serão carregados no bitmap.</param>
/// <param name="Param_Pitch">O Pitch dos dados de origem, se especificado.</param>
/// <param name="Param_PropsBitmap">As propriedades do bitmap a serem criados.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para o novo objeto bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmap(
	CA_D2D1_SIZE_U^ Param_Size,
	ICarenBuffer^ Param_SourceData,
	UInt32 Param_Pitch,
	CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
	[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U* pSize = NULL;
	IntPtr pBufferSourceData = IntPtr::Zero;
	D2D1_BITMAP_PROPERTIES1* pBitmapProps = NULL;
	ID2D1Bitmap1* pOutBitmap1 = NULL;

	//Converte a estrutura do size
	pSize = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Size);

	//Recupera o ponteiro para o buffer.
	Resultado = Param_SourceData->GetInternalPointer(pBufferSourceData);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura de propriedades
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIES1ManagedToUnmanaged(Param_PropsBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(*pSize, Util.ConverterIntPtrTo<PBYTE>(pBufferSourceData), Param_Pitch, pBitmapProps, &pOutBitmap1);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que vai ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutBitmap1, Param_Out_Bitmap);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pSize);
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D. 
/// </summary>
/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
/// <param name="Param_PropsBitmapBrush">Uma estrutura de propriedades de pincel bitmap.</param>
/// <param name="Param_PropsBrush">Uma estrutura de propriedades do Brush.</param>
/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ Param_PropsBitmapBrush,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropsBrush,
	[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES1* pBitmapBrusProps = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1BitmapBrush1* pOutBitmapBrush = NULL;

	//Recupera o ponteiro para o bitmap
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas
	pBitmapBrusProps = Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIES1ManagedToUnmanaged(Param_PropsBitmapBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropsBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, pBitmapBrusProps, pBrushProps, &pOutBitmapBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmapBrush, Param_Out_BitmapBrush);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pBitmapBrusProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D.
/// </summary>
/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmap = NULL;
	ID2D1BitmapBrush1* pOutBitmapBrush = NULL;

	//Recupera o ponteiro para o bitmap
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, &pOutBitmapBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmapBrush, Param_Out_BitmapBrush);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um pincel bitmap(BrushBitmap), a imagem de entrada é um objeto de bitmap Direct2D. 
/// </summary>
/// <param name="Param_Bitmap">O bitmap para usar como pincel.</param>
/// <param name="Param_PropsBrush">Uma estrutura de propriedades de pincel bitmap.</param>
/// <param name="Param_Out_BitmapBrush">Retorna uma interface(ICarenD2D1BitmapBrush1) que contém um ponteiro para o objeto de pincel bitmap recém-criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_BRUSH_PROPERTIES1^ Param_PropsBrush,
	[Out] ICarenD2D1BitmapBrush1^% Param_Out_BitmapBrush
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES1* pBitmapBrusProps = NULL;
	ID2D1BitmapBrush1* pOutBitmapBrush = NULL;

	//Recupera o ponteiro para o bitmap
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura agerenciada.
	pBitmapBrusProps = Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIES1ManagedToUnmanaged(Param_PropsBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, *pBitmapBrusProps, &pOutBitmapBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmapBrush, Param_Out_BitmapBrush);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pBitmapBrusProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um bitmap a partir de uma superfície DXGI que pode ser definida como uma superfície alvo ou ter informações adicionais de contexto de cores especificadas.
/// </summary>
/// <param name="Param_DxgiSurface">A superfície DXGI a partir da qual o bitmap pode ser criado. [NOTA] A superfície DXGI deve ter sido criada a partir do mesmo dispositivo Direct3D com o que o contexto do dispositivo Direct2D está associado. </param>
/// <param name="Param_PropsBitmap">As propriedades do bitmap especificadas além da superfície.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapFromDxgiSurface(
	ICarenDXGISurface^ Param_DxgiSurface,
	CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
	ICarenD2D1Bitmap1^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pDXGISurface = NULL;
	D2D1_BITMAP_PROPERTIES1* pBitmapProps = NULL;
	ID2D1Bitmap1* pOutBitmap = NULL;

	//Recupera o ponteiro para a superfice DXGI.
	Resultado = RecuperarPonteiroCaren(Param_DxgiSurface, &pDXGISurface);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura gerenciada
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIES1ManagedToUnmanaged(Param_PropsBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromDxgiSurface(pDXGISurface, pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmap, Param_Out_Bitmap);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um bitmap Direct2D copiando um bitmap WIC.
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) da fonte de bitmap WIC para copiar.</param>
/// <param name="Param_PropsBitmap">Uma estrutura de propriedades bitmap que especifica opções de criação de bitmap.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapFromWicBitmap(
	ICaren^ Param_WicBitmapSource,
	CA_D2D1_BITMAP_PROPERTIES1^ Param_PropsBitmap,
	[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource* pWICBitmapSource = NULL;
	D2D1_BITMAP_PROPERTIES1* pBitmapProps = NULL;
	ID2D1Bitmap1* pOutBitmap = NULL;

	//Recupera o ponteiro para a superfice DXGI.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapSource, &pWICBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura gerenciada
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIES1ManagedToUnmanaged(Param_PropsBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWICBitmapSource, pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmap, Param_Out_Bitmap);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1Bitmap1 copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface(ICarenWICBitmapSource) da fonte de bitmap WIC para copiar.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface(ICarenD2D1Bitmap1) que contém um ponteiro para um novo objeto bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapFromWicBitmap(
	ICaren^ Param_WicBitmapSource,
	[Out] ICarenD2D1Bitmap1^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pWICBitmapSource = NULL;
	ID2D1Bitmap1* pOutBitmap = NULL;

	//Recupera o ponteiro para a superfice DXGI.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapSource, &pWICBitmapSource);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWICBitmapSource, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutBitmap, Param_Out_Bitmap);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cores. O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado.
/// Quando o espaço é D2D1_COLOR_SPACE_CUSTOM, o (Param_Profile) e o (Param_ProfileSize) devem ser especificados. Caso contrário, esses parâmetros devem ser definidos como NULO e zero, respectivamente. 
/// Quando o espaço é D2D1_COLOR_SPACE_CUSTOM, o campo modelo do cabeçalho do (Param_Profile) é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço permanece personalizado.
/// </summary>
/// <param name="Param_EspacoCor">O espaço do contexto de cores para criar.</param>
/// <param name="Param_Profile">Um buffer contendo os bytes de perfil ICC usados para inicializar o contexto de cor quando o espaço é D2D1_COLOR_SPACE_CUSTOM. Para outros tipos, o parâmetro é ignorado e deve ser definido como NULO.</param>
/// <param name="Param_ProfileSize">O tamanho em bytes de (Param_Profile).</param>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
CarenResult CarenD2D1DeviceContext5::CreateColorContext(
	CA_D2D1_COLOR_SPACE Param_EspacoCor,
	ICarenBuffer^ Param_Profile,
	UInt32 Param_ProfileSize,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_SPACE SpaceColor = static_cast<D2D1_COLOR_SPACE>(Param_EspacoCor);
	IntPtr pBufferProfile = IntPtr::Zero; //Pode ser NULO.
	ID2D1ColorContext* pOutColorContext = NULL;

	//Verifica se forneceu o buffer do profile de cor.
	if (ObjetoGerenciadoValido(Param_Profile))
	{
		//Recupera o ponteiro.
		Resultado = Param_Profile->GetInternalPointer(pBufferProfile);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContext(SpaceColor, pBufferProfile == IntPtr::Zero ? NULL : Util.ConverterIntPtrTo<PBYTE>(pBufferProfile), Param_ProfileSize, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o potneiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cor carregando-o a partir do nome de arquivo especificado. Os bytes de perfil são o conteúdo do arquivo especificado pelo (Param_UrlArquivo).
/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
/// </summary>
/// <param name="Param_UrlArquivo">O caminho para o arquivo contendo os bytes de perfil para inicializar o contexto de cores com.</param>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
CarenResult CarenD2D1DeviceContext5::CreateColorContextFromFilename(
	String^ Param_UrlArquivo,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWSTR pUrlArquivo = NULL;
	ID2D1ColorContext* pOutColorContext = NULL;

	//Converte a string para o arquivo com o profile de cor.
	pUrlArquivo = Util.ConverterStringToWCHAR(Param_UrlArquivo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromFilename(pUrlArquivo, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o potneiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext);

Done:;
	//Libera a memória para a string
	DeletarStringAllocatedSafe(&pUrlArquivo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um contexto de cores a partir de um ICarenWICColorContext.
/// O novo contexto de cores pode ser usado em D2D1_BITMAP_PROPERTIES1 para inicializar o contexto de cores de um bitmap criado. O campo modelo do cabeçalho do perfil é inspecionado para determinar se esse perfil é sRGB ou scRGB e o espaço de cor é atualizado respectivamente. Caso contrário, o espaço é personalizado.
/// </summary>
/// <param name="Param_WicColorContext">Uma interface(ICarenWICColorContext) usado para inicializar o contexto de cores.</param>
/// <param name="Param_Out_ColorContext">Retorna uma interface(ICarenD2D1ColorContext) que contém um ponteiro para o novo objeto de contexto de cores.</param>
CarenResult CarenD2D1DeviceContext5::CreateColorContextFromWicColorContext(
	ICaren^ Param_WicColorContext,
	[Out] ICarenD2D1ColorContext^% Param_Out_ColorContext)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICColorContext* pWicColorContext = NULL;
	ID2D1ColorContext* pOutColorContext = NULL;

	//Recuper ao ponteiro para a interface de contexto de cor da WIC.
	Resultado = RecuperarPonteiroCaren(Param_WicColorContext, &pWicColorContext);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateColorContextFromWicColorContext(pWicColorContext, &pOutColorContext);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ColorContext = gcnew CarenD2D1ColorContext();

	//Define o potneiro na interface.
	Resultado = DefinirPonteiroInterface(pOutColorContext, Param_Out_ColorContext);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto ICarenD2D1CommandList que representa uma lista de comandos.
/// Um ID2D1CommandList pode armazenar comandos Direct2D a serem exibidos posteriormente através do ICarenD2D1DeviceContext::DrawImage ou através de um pincel de imagem.
/// </summary>
/// <param name="Param_Out_CommandList">Retorna uma interface(ICarenD2D1CommandList) que contém um ponteiro para a nova lista de comandos criadas.</param>
CarenResult CarenD2D1DeviceContext5::CreateCommandList(
	[Out] ICarenD2D1CommandList^% Param_Out_CommandList)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1CommandList* pOutCommandList = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCommandList(&pOutCommandList);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_CommandList = gcnew CarenD2D1CommandList();

	//Define o potneiro na interface.
	Resultado = DefinirPonteiroInterface(pOutCommandList, Param_Out_CommandList);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um efeito para o ID de classe especificado.
/// </summary>
/// <param name="Param_IdEfeito">A ID de classe do efeito para criar. Consulte (GUIDs::GUIDs_D2D_CLSIDs_EFEITOS) para obter uma lista de IDs de efeitos disponiveis.</param>
/// <param name="Param_Out_Efeito">Retorna uma interface(ICarenD2D1Effect) que contém um ponteiro para o novo efeito criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateEffect(
	String^ Param_IdEfeito,
	[Out] ICarenD2D1Effect^% Param_Out_Efeito)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdEfeito = GUID_NULL;
	ID2D1Effect* pOutEfeito = NULL;

	//Cria o guid do efeito.
	IdEfeito = Util.CreateGuidFromString(Param_IdEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateEffect(IdEfeito, &pOutEfeito);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Efeito = gcnew CarenD2D1Effect();

	//Define o potneiro na interface.
	Resultado = DefinirPonteiroInterface(pOutEfeito, Param_Out_Efeito);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um Gradient Stop Collection, permitindo que o gradiente contenha canais de cores com valores fora de [0,1] e também permitindo renderização para um alvo de renderização de alta cor com interpolação no espaço sRGB.
/// Este método interpola linearmente entre as paradas de cor. Uma conversão de espaço de cor opcional é aplicada após a interpolação. Se e como essa conversão gama é aplicada é determinada pela pré e pós-interpolação. Este método falhará se o contexto do dispositivo não suportar a precisão do buffer solicitada.
/// Para obter o resultado desejado, você precisa garantir que as entradas sejam especificadas no espaço de cores correto.
/// Você sempre deve especificar cores em alfa reto, independentemente do modo de interpolação ser pré - multiplicado ou reto.O modo de interpolação afeta apenas os valores interpolados.Da mesma forma, as paradas retornadas por ID2D1GradientStopCollection::GetGradientStops sempre terão alfa direto.
/// </summary>
/// <param name="Param_AlphaGradientStops">Uma matriz de valores de cor e compensações.</param>
/// <param name="Param_Quantidade">A quantidade de elementos em (Param_AlphaGradientStops).</param>
/// <param name="Param_PreInterpolationSpace">Especifica tanto o espaço de cor de entrada quanto o espaço em que ocorre a interpolação de cores.</param>
/// <param name="Param_PosInterpolationSpace">O espaço de cor para o qual as cores serão convertidas após a interpolação ocorre.</param>
/// <param name="Param_BufferPrecision">A precisão da textura usada para conter valores interpolados.  Este método falhará se o dispositivo Direct3D subjacente não suportar a precisão do buffer solicitada. Use ICarenD2D1DeviceContext::IsBufferPrecisionSupported para determinar o que é suportado.</param>
/// <param name="Param_ExtendMode">Define como são determinadas cores fora do intervalo definidas pela coleção stop.</param>
/// <param name="Param_ColorInterPolationMode">Define como as cores são interpoladas. D2D1_COLOR_INTERPOLATION_MODE_PREMULTIPLIED é o padrão.</param>
/// <param name="Param_Out_GradientStopCollection">Retorna uma interface(ICarenD2D1GradientStopCollection1) que contém um ponteiro para o novo GradientStopCollection criado.</param>
CarenResult CarenD2D1DeviceContext5::CreateGradientStopCollection(
	cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_AlphaGradientStops,
	UInt32 Param_Quantidade,
	CA_D2D1_COLOR_SPACE Param_PreInterpolationSpace,
	CA_D2D1_COLOR_SPACE Param_PosInterpolationSpace,
	CA_D2D1_BUFFER_PRECISION Param_BufferPrecision,
	CA_D2D1_EXTEND_MODE Param_ExtendMode,
	CA_D2D1_COLOR_INTERPOLATION_MODE Param_ColorInterPolationMode,
	[Out] ICarenD2D1GradientStopCollection1^% Param_Out_GradientStopCollection
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_STOP* pMatrizAlphaGradientStops = CriarMatrizEstruturas<D2D1_GRADIENT_STOP>(Param_Quantidade);
	ID2D1GradientStopCollection1* pOutGradientStopCollection = NULL;
	D2D1_GRADIENT_STOP* pStopAuxiliar = NULL;

	//Faz um for para copiar os dados para a matriz nativa.
	for (UINT32 i = 0; i < Param_Quantidade; i++)
	{
		//Converte a estrutura.
		pStopAuxiliar = Util.ConverterD2D1_GRADIENT_STOPManagedToUnmanaged(Param_AlphaGradientStops[i]);

		//Define na matriz nativa.
		pMatrizAlphaGradientStops[i] = *pStopAuxiliar;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pStopAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientStopCollection(
		pMatrizAlphaGradientStops,
		Param_Quantidade,
		static_cast<D2D1_COLOR_SPACE>(Param_PreInterpolationSpace),
		static_cast<D2D1_COLOR_SPACE>(Param_PosInterpolationSpace),
		static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision),
		static_cast<D2D1_EXTEND_MODE>(Param_ExtendMode),
		static_cast<D2D1_COLOR_INTERPOLATION_MODE>(Param_ColorInterPolationMode),
		&pOutGradientStopCollection
	);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutGradientStopCollection, Param_Out_GradientStopCollection);

Done:;
	//Libera a memória para a matriz nativa.
	DeletarMatrizEstruturasSafe(&pMatrizAlphaGradientStops);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um pincel de imagem. A imagem de entrada pode ser qualquer tipo de imagem, incluindo um bitmap, efeito ou uma lista de comando.
/// O pincel de imagem pode ser usado para preencher uma geometria arbitrária, uma máscara de opacidade ou texto.
/// </summary>
/// <param name="Param_Image">A imagem a ser usada como fonte para o pincel de imagem.</param>
/// <param name="Param_PropsImageBrush">As propriedades específicas de um pincel de imagem.</param>
/// <param name="Param_PropsBrush">Propriedades comuns a todos os pincéis.</param>
/// <param name="Param_Out_ImageBrush">Retorna uma interface(ICarenD2D1ImageBrush) que contém um ponteiro para o novo Image Brush.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageBrush(
	ICarenD2D1Image^ Param_Image,
	CA_D2D1_IMAGE_BRUSH_PROPERTIES^ Param_PropsImageBrush,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropsBrush,
	[Out] ICarenD2D1ImageBrush^% Param_Out_ImageBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pImage = NULL;
	D2D1_IMAGE_BRUSH_PROPERTIES* pImageBrush = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1ImageBrush* pOutImageBrush = NULL;

	//Recupera o ponteiro para a imagem.
	Resultado = RecuperarPonteiroCaren(Param_Image, &pImage);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas
	pImageBrush = Util.ConverterD2D1_IMAGE_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropsImageBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropsBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageBrush(pImage, pImageBrush, pBrushProps, &pOutImageBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ImageBrush = gcnew CarenD2D1ImageBrush();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutImageBrush, Param_Out_ImageBrush);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pBrushProps);
	DeletarEstruturaSafe(&pImageBrush);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um pincel de imagem. A imagem de entrada pode ser qualquer tipo de imagem, incluindo um bitmap, efeito ou uma lista de comando.
/// O pincel de imagem pode ser usado para preencher uma geometria arbitrária, uma máscara de opacidade ou texto.
/// </summary>
/// <param name="Param_Image"> imagem a ser usada como fonte para o pincel de imagem.</param>
/// <param name="Param_PropsImageBrush">As propriedades específicas de um pincel de imagem.</param>
/// <param name="Param_Out_ImageBrush">Retorna uma interface(ICarenD2D1ImageBrush) que contém um ponteiro para o novo Image Brush.</param>
CarenResult CarenD2D1DeviceContext5::CreateImageBrush(
	ICarenD2D1Image^ Param_Image,
	CA_D2D1_IMAGE_BRUSH_PROPERTIES^ Param_PropsImageBrush,
	[Out] ICarenD2D1ImageBrush^% Param_Out_ImageBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pImage = NULL;
	D2D1_IMAGE_BRUSH_PROPERTIES* pImageBrush = NULL;
	ID2D1ImageBrush* pOutImageBrush = NULL;

	//Recupera o ponteiro para a imagem.
	Resultado = RecuperarPonteiroCaren(Param_Image, &pImage);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas
	pImageBrush = Util.ConverterD2D1_IMAGE_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropsImageBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateImageBrush(pImage, *pImageBrush, &pOutImageBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_ImageBrush = gcnew CarenD2D1ImageBrush();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutImageBrush, Param_Out_ImageBrush);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pImageBrush);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha um bitmap para o alvo de renderização.
/// O parâmetro (Param_RetanguloDestino) define o retângulo no alvo onde o bitmap aparecerá (em pixels independentes do dispositivo (DIPs)). Isso é afetado pela transformação atualmente definida e pela transformação da perspectiva, se definida. Se NULO for especificado, então o retângulo de destino é (esquerda=0, top=0, direita = largura (Param_RetanguloOrigem), inferior = altura (Param_RetanguloOrigem)).
/// O parâmetro (Param_RetanguloOrigem) define o sub-retângulo do bitmap de origem (em DIPs). DrawBitmap irá cortar este retângulo para o tamanho do bitmap de origem, tornando assim impossível a amostra fora do bitmap. Se NULO for especificado, então o retângulo de origem será considerado o tamanho do bitmap de origem.
/// </summary>
/// <param name="Param_Bitmap">O bitmap para desenhar.</param>
/// <param name="Param_RetanguloDestino">O retângulo de destino. O padrão é o tamanho do bitmap e o local é o canto superior esquerdo do alvo de renderização.</param>
/// <param name="Param_Opacidade">A opacidade do bitmap.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação para usar.</param>
/// <param name="Param_RetanguloOrigem">Um retângulo de origem opcional.</param>
/// <param name="Param_PerspectiveTransform">Uma transformação opcional de perspectiva.</param>
CarenResult CarenD2D1DeviceContext5::DrawBitmap(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_RECT_F^ Param_RetanguloDestino,
	float Param_Opacidade,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_RECT_F^ Param_RetanguloOrigem,
	CA_D2D1_MATRIX_4X4_F^ Param_PerspectiveTransform
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	D2D1_RECT_F* pRectDestino = NULL;
	D2D1_RECT_F* pRectOrigem = NULL; //Pode ser NULO.
	D2D1_MATRIX_4X4_F* pPespectiveTransform = NULL; //Pode ser NULO.

	//Recupera o ponteiro para o bitmap.
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pRectDestino = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pRectOrigem = ObjetoGerenciadoValido(Param_RetanguloOrigem) ? Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem) : nullptr;
	pPespectiveTransform = ObjetoGerenciadoValido(Param_PerspectiveTransform) ? Util.ConverterD2D1_MATRIX_4X4_FManagedToUnmanaged(Param_PerspectiveTransform) : nullptr;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawBitmap(
		pBitmap,
		pRectDestino,
		Param_Opacidade,
		static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode),
		pRectOrigem,
		pPespectiveTransform);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRectDestino);
	DeletarEstruturaSafe(&pRectOrigem);
	DeletarEstruturaSafe(&pPespectiveTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha um metafile para o contexto do dispositivo.
/// </summary>
/// <param name="Param_GdiMetafile">Uma interface(ID2D1GdiMetafile)[NAO IMPLEMENTADA PELA DLL] metafile para desenhar.</param>
/// <param name="Param_TargetOffset">O deslocamento do canto superior esquerdo do alvo render.</param>
void CarenD2D1DeviceContext5::DrawGdiMetafile(
	ICaren^ Param_GdiMetafile,
	CA_D2D1_POINT_2F^ Param_TargetOffset)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1GdiMetafile* pGdiMetafile = NULL;
	D2D1_POINT_2F* pTargetOffset = NULL;

	//Recupera o ponteiro para a interface a ser renderizada.
	RecuperarPonteiroCaren(Param_GdiMetafile, &pGdiMetafile);

	//Converte a estrutura
	pTargetOffset = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_TargetOffset);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGdiMetafile(pGdiMetafile, pTargetOffset);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pTargetOffset);
}

/// <summary>
/// Desenha uma série de glifos(Glyphs) para o contexto do dispositivo.
/// O (Param_GlyphRunDesc) é ignorado na prestação de serviços, mas pode ser útil para impressão e serialização de comandos de renderização, como em um arquivo XPS ou SVG. Isso estende o ICarenD2D1RenderTarget::DrawGlyphRun, que não tinha a descrição de execução do glifo.
/// </summary>
/// <param name="Param_BaseLineOrigin">Origem do primeiro glifo da série.</param>
/// <param name="Param_GlyphRun">Os glifos para renderizar.</param>
/// <param name="Param_GlyphRunDesc">Informações da série glifo suplementar.</param>
/// <param name="Param_ForegroundBrush">O pincel que define a cor do texto.</param>
/// <param name="Param_ModoMedicao">O modo de medição da série glifo, usado para determinar os avanços e deslocamentos. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
void CarenD2D1DeviceContext5::DrawGlyphRun(
	CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
	CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
	CA_DWRITE_GLYPH_RUN_DESCRIPTION^ Param_GlyphRunDesc,
	ICarenD2D1Brush^ Param_ForegroundBrush,
	CA_DWRITE_MEASURING_MODE Param_ModoMedicao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMyBaseLineOrigin = NULL;
	DWRITE_GLYPH_RUN* pMyGlyphRun = NULL;
	DWRITE_GLYPH_RUN_DESCRIPTION* pMyGlyphDesc = NULL;
	ID2D1Brush* pMyForegroundBrush = NULL;

	//Converte as estruturas
	pMyBaseLineOrigin = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaseLineOrigin);
	pMyGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlyphRun);
	pMyGlyphDesc = Util.ConverterDWRITE_GLYPH_RUN_DESCRIPTIONManagedToUnmanaged(Param_GlyphRunDesc);

	//Recupera o ponteiro para a interface do brush
	RecuperarPonteiroCaren(Param_ForegroundBrush, &pMyForegroundBrush);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGlyphRun(*pMyBaseLineOrigin, pMyGlyphRun, pMyGlyphDesc, pMyForegroundBrush, static_cast<DWRITE_MEASURING_MODE>(Param_ModoMedicao));

	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pMyBaseLineOrigin);
	DeletarEstruturaSafe(&pMyGlyphRun);
	DeletarEstruturaSafe(&pMyGlyphDesc);
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// </summary>
/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
/// <param name="Param_RetanguloImagem">O retângulo correspondente no espaço da imagem será mapeado para as origens dadas ao processar a imagem. Este valor padrão é NULO.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Image^ Param_Image,
	CA_D2D1_POINT_2F^ Param_TargetOffset,
	CA_D2D1_RECT_F^ Param_RetanguloImagem,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao
)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pMyImage = NULL;
	D2D1_POINT_2F* pMyTargetOffset = NULL; //Pode ser NULO.
	D2D1_RECT_F* pMyRectImage = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface.
	RecuperarPonteiroCaren(Param_Image, &pMyImage);

	//Converte as estruturas se fornecidas.
	pMyTargetOffset = ObjetoGerenciadoValido(Param_TargetOffset) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_TargetOffset) : NULL;
	pMyRectImage = ObjetoGerenciadoValido(Param_RetanguloImagem) ? Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloImagem) : NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyImage, pMyTargetOffset, pMyRectImage, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));

	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMyTargetOffset);
	DeletarEstruturaSafe(&pMyRectImage);
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// </summary>
/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
/// <param name="Param_RetanguloImagem">O retângulo correspondente no espaço da imagem será mapeado para as origens dadas ao processar a imagem. Este valor padrão é NULO.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Effect^ Param_Efeito,
	CA_D2D1_POINT_2F^ Param_TargetOffset,
	CA_D2D1_RECT_F^ Param_RetanguloImagem,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Effect* pMyEffect = NULL;
	D2D1_POINT_2F* pMyTargetOffset = NULL; //Pode ser NULO.
	D2D1_RECT_F* pMyRectImage = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface.
	RecuperarPonteiroCaren(Param_Efeito, &pMyEffect);

	//Converte as estruturas se fornecidas.
	pMyTargetOffset = ObjetoGerenciadoValido(Param_TargetOffset) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_TargetOffset) : NULL;
	pMyRectImage = ObjetoGerenciadoValido(Param_RetanguloImagem) ? Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloImagem) : NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyEffect, pMyTargetOffset, pMyRectImage, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));

	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMyTargetOffset);
	DeletarEstruturaSafe(&pMyRectImage);
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// Se a (CA_D2D1_INTERPOLATION_MODE) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
/// </summary>
/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Image^ Param_Image,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao
)
{
	//Variaveis a serem utilizadas.
	ID2D1Image* pMyImage = NULL;

	//Recupera o ponteiro para a imagem.
	RecuperarPonteiroCaren(Param_Image, &pMyImage);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyImage, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
/// </summary>
/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Effect^ Param_Efeito,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao)
{
	//Variaveis a serem utilizadas.
	ID2D1Image* pMyEffect = NULL;

	//Recupera o ponteiro para a imagem.
	RecuperarPonteiroCaren(Param_Efeito, &pMyEffect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyEffect, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
/// </summary>
/// <param name="Param_Image">A imagem a ser desenhada para o contexto do dispositivo.</param>
/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER.</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Image^ Param_Image,
	CA_D2D1_POINT_2F^ Param_TargetOffset,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pMyImage = NULL;
	D2D1_POINT_2F* pMyTargetOffset = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface.
	RecuperarPonteiroCaren(Param_Image, &pMyImage);

	//Converte a estrutura se fornecida.
	pMyTargetOffset = ObjetoGerenciadoValido(Param_TargetOffset) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_TargetOffset) : NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyImage, *pMyTargetOffset, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));

	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMyTargetOffset);
}

/// <summary>
/// Desenha uma imagem para o contexto do dispositivo.
/// Se a (Param_InterpolationMode) for D2D1_INTERPOLATION_MODE_HIGH_QUALITY, diferentes scalers serão usados dependendo do fator de escala implícito pela transformação mundial.
/// Retângulos inválidos acumulados em qualquer efeito que for desenhado por esta chamada serão descartados independentemente de qual parte do retângulo de imagem seja desenhada.
/// Se o (Param_ModoComposicao) estiver D2D1_COMPOSITE_MODE_SOURCE_OVER, o DrawImage usará a mistura primitiva selecionada atualmente especificada por ICarenD2D1DeviceContext::SetPrimitiveBlend. Se o (Param_ModoComposicao) não estiver D2D1_COMPOSITE_MODE_SOURCE_OVER,a imagem será estendida para transparente até o clipe alinhado ao eixo atual.
/// </summary>
/// <param name="Param_Efeito">O efeito a ser desenhado para o contexto do dispositivo.</param>
/// <param name="Param_TargetOffset">O deslocamento no espaço de destino ao que a imagem será renderizada. Toda a extensão lógica da imagem será entregue ao destino correspondente. Se não for especificado, a origem do destino será (0,0). O canto superior esquerdo da imagem será mapeado para o deslocamento do alvo. Esta não será necessariamente a origem. Este valor padrão é NULO.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação que será usado para dimensionar a imagem, se necessário.</param>
/// <param name="Param_ModoComposicao">O modo composto que será aplicado aos limites do clipe selecionado atualmente. O valor padrão é D2D1_COMPOSITE_MODE_SOURCE_OVER.</param>
void CarenD2D1DeviceContext5::DrawImage(
	ICarenD2D1Effect^ Param_Efeito,
	CA_D2D1_POINT_2F^ Param_TargetOffset,
	CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_COMPOSITE_MODE Param_ModoComposicao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pMyEffect = NULL;
	D2D1_POINT_2F* pMyTargetOffset = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface.
	RecuperarPonteiroCaren(Param_Efeito, &pMyEffect);

	//Converte a estrutura se fornecida.
	pMyTargetOffset = ObjetoGerenciadoValido(Param_TargetOffset) ? Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_TargetOffset) : NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawImage(pMyEffect, *pMyTargetOffset, static_cast<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode), static_cast<D2D1_COMPOSITE_MODE>(Param_ModoComposicao));

	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMyTargetOffset);
}

/// <summary>
/// Preencha usando o canal alfa do bitmap da máscara de opacidade fornecido.A opacidade do pincel será modulada pela máscara.O modo de antialiasing do destino de renderização deve ser definido como alias.
/// </summary>
/// <param name="Param_MascaraOpacidade">O bitmap que age como a máscara de opacidade</param>
/// <param name="Param_Brush">O pincel a ser usado para preencher o primitivo.</param>
/// <param name="Param_RetanguloDestino">O retângulo de destino para saída para dentro do alvo renderização</param>
/// <param name="Param_RetanguloOrigem">O retângulo de origem do bitmap da máscara de opacidade.</param>
void CarenD2D1DeviceContext5::FillOpacityMask(
	ICarenD2D1Bitmap^ Param_MascaraOpacidade,
	ICarenD2D1Brush^ Param_Brush,
	CA_D2D1_RECT_F^ Param_RetanguloDestino,
	CA_D2D1_RECT_F^ Param_RetanguloOrigem)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pMyMask = NULL;
	ID2D1Brush* pMyBrush = NULL;
	D2D1_RECT_F* pMyRectDestino = NULL;
	D2D1_RECT_F* pMyRectOrigem = NULL;

	//Recupera o ponteiro para a interface do bitmap.
	RecuperarPonteiroCaren(Param_MascaraOpacidade, &pMyMask);
	RecuperarPonteiroCaren(Param_Brush, &pMyBrush);

	//Converte as estruturas
	pMyRectDestino = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pMyRectOrigem = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillOpacityMask(pMyMask, pMyBrush, pMyRectDestino, pMyRectOrigem);

	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pMyRectDestino);
	DeletarEstruturaSafe(&pMyRectOrigem);
}

/// <summary>
/// Obtém o dispositivo associado a um contexto de dispositivo.
/// O aplicativo pode recuperar o dispositivo mesmo que ele seja criado a partir de um caminho de código de destino de renderização anterior. O aplicativo deve usar uma interface ICarenD2D1DeviceContext e, em seguida, chamar GetDevice. Algumas funcionalidades para controlar todos os recursos para um conjunto de contextos de dispositivos são mantidas apenas em um objeto ICarenD2D1Device.
/// </summary>
/// <param name="Param_Out_Dispositivo">Retorna uma interface(ICarenD2D1Device) que contém um ponteiro para um dispositivo Direct2D associado a este contexto do dispositivo.  O usuário deve inicializar a interface antes de chamar o método.</param>
void CarenD2D1DeviceContext5::GetDevice(ICaren^ Param_Out_Dispositivo)
{
	//Variaveis a serem utilizadas.
	ID2D1Device* pMyOutDevice = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDevice(&pMyOutDevice);

	//Define no ponteiro da interface fornecida pelo usuário.
	Param_Out_Dispositivo->AdicionarPonteiro(pMyOutDevice);
}

/// <summary>
/// Obtém o número de retângulos de saída inválidos que se acumularam sobre o efeito.
/// </summary>
/// <param name="Param_Efeito">O efeito para contar os retângulos inválidos.</param>
/// <param name="Param_Out_QuantidadeRetangulos">Retorna a contagem de retângulos devolvidos.</param>
CarenResult CarenD2D1DeviceContext5::GetEffectInvalidRectangleCount(
	ICarenD2D1Effect^ Param_Efeito,
	[Out] UInt32% Param_Out_QuantidadeRetangulos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Effect* pMyEfeito = NULL;
	UINT32 MyOutCountRects = 0;

	//Recupera o ponteiro para o efeito.
	Resultado = RecuperarPonteiroCaren(Param_Efeito, &pMyEfeito);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetEffectInvalidRectangleCount(pMyEfeito, &MyOutCountRects);

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
/// Obtém os retângulos inválidos que se acumularam desde a última vez que o efeito foi desenhado e o EndDraw foi então chamado no contexto do dispositivo.
/// </summary>
/// <param name="Param_Efeito">O efeito para obter os retângulos inválidos.</param>
/// <param name="Param_Out_ArrayRetangulos">Retorna uma matriz de estruturas D2D1_RECT_F.</param>
/// <param name="Param_QuantidadeRetangulos">O número de retângulos a serem devolvidos em (Param_Out_ArrayRetangulos).</param>
CarenResult CarenD2D1DeviceContext5::GetEffectInvalidRectangles(
	ICarenD2D1Effect^ Param_Efeito,
	[Out] cli::array<CA_D2D1_RECT_F^>^% Param_Out_ArrayRetangulos,
	UInt32 Param_QuantidadeRetangulos)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Effect* pMyEfeito = NULL;
	D2D1_RECT_F* pMyOutMatrizRetangulos = CriarMatrizEstruturas<D2D1_RECT_F>(Param_QuantidadeRetangulos);

	//Recupera o ponteiro para o efeito.
	Resultado = RecuperarPonteiroCaren(Param_Efeito, &pMyEfeito);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetEffectInvalidRectangles(pMyEfeito, pMyOutMatrizRetangulos, Param_QuantidadeRetangulos);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria o array gerenciado que vai receber os dados.
	Param_Out_ArrayRetangulos = gcnew cli::array<CA_D2D1_RECT_F^>(Param_QuantidadeRetangulos);

	//Abre um for para copiar os dados para o array gerenciado.
	for (UINT32 i = 0; i < Param_QuantidadeRetangulos; i++)
	{
		//Converte e define no index informado no array
		Param_Out_ArrayRetangulos[i] = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&pMyOutMatrizRetangulos[i]);
	}

Done:;
	//Libera a memória para a matriz.
	DeletarMatrizEstruturasSafe(&pMyOutMatrizRetangulos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna os retângulos de entrada que são necessários para serem fornecidos pelo chamador para produzir o retângulo de saída dado.
/// O chamador deve ter muito cuidado para não confiar nos retângulos de entrada necessários devolvidos. Pequenas alterações para correção do comportamento de um efeito podem resultar em diferentes retângulos sendo devolvidos. Além disso, diferentes tipos de otimização aplicada dentro da renderização também podem influenciar o resultado.
/// </summary>
/// <param name="Param_Efeito">A imagem cuja saída está sendo renderizada.</param>
/// <param name="Param_RenderImageRectangle">A porção da imagem de saída cujos inputs estão sendo inspecionados.</param>
/// <param name="Param_DescInputs">Uma lista dos insumos que os retângulos estão sendo consultados.</param>
/// <param name="Param_Out_InputRects">Retorna uma matriz com os retângulos de entrada.</param>
/// <param name="Param_QuantidadeInput">O número de entradas.</param>
CarenResult CarenD2D1DeviceContext5::GetEffectRequiredInputRectangles(
	ICarenD2D1Effect^ Param_Efeito,
	CA_D2D1_RECT_F^ Param_RenderImageRectangle,
	cli::array<CA_D2D1_EFFECT_INPUT_DESCRIPTION^>^ Param_DescInputs,
	[Out] cli::array <CA_D2D1_RECT_F^>^% Param_Out_InputRects,
	UInt32 Param_QuantidadeInput
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Effect* pMyEfeito = NULL;
	D2D1_RECT_F* pMyRenderImageRect = NULL;
	D2D1_EFFECT_INPUT_DESCRIPTION* pMyMatrizDescInputs = CriarMatrizEstruturas<D2D1_EFFECT_INPUT_DESCRIPTION>(Param_QuantidadeInput);
	D2D1_RECT_F* pMyOutMatrizInputRects = CriarMatrizEstruturas<D2D1_RECT_F>(Param_QuantidadeInput);
	D2D1_EFFECT_INPUT_DESCRIPTION* pMyDecAuxiliar = NULL;

	//Recupera o ponteiro para o efeito
	Resultado = RecuperarPonteiroCaren(Param_Efeito, &pMyEfeito);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura
	pMyRenderImageRect = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RenderImageRectangle);

	//Abre um for para copiar os dados para a matriz de descrição.
	for (UINT32 i = 0; i < Param_QuantidadeInput; i++)
	{
		//Converte a estrutura no index informado.
		pMyDecAuxiliar = Util.ConverterD2D1_EFFECT_INPUT_DESCRIPTIONManagedToUnmanaged(Param_DescInputs[i]);

		//Define na matriz nativa.
		pMyMatrizDescInputs[i] = *pMyDecAuxiliar;

		//Libera a memória para a estrutura.
		DeletarEstruturaSafe(&pMyDecAuxiliar);
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEffectRequiredInputRectangles(pMyEfeito, pMyRenderImageRect, pMyMatrizDescInputs, pMyOutMatrizInputRects, Param_QuantidadeInput);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria o array que será retornado.
	Param_Out_InputRects = gcnew cli::array<CA_D2D1_RECT_F^>(Param_QuantidadeInput);

	//Abre um for para copiar os dados para a matriz de saida.
	for (UINT32 i = 0; i < Param_QuantidadeInput; i++)
	{
		//Converte e define no index na matriz.
		Param_Out_InputRects[i] = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&pMyOutMatrizInputRects[i]);
	}

Done:;
	//Libera a memória para as estruturas e matrizes
	DeletarEstruturaSafe(&pMyRenderImageRect);
	DeletarMatrizEstruturasSafe(&pMyMatrizDescInputs);
	DeletarMatrizEstruturasSafe(&pMyOutMatrizInputRects);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os limites do espaço do mundo(World-space Bounds) nos DIPs da execução do glifo usando o DPI do contexto do dispositivo.
/// Os limites de imagem refletem o DPI atual, o modo unitário e a transformação mundial do contexto.
/// </summary>
/// <param name="Param_BaseLineOrigin">A origem da linha de base para a execução do glifo.</param>
/// <param name="Param_GlypRun">O glifo que é executado para renderizar.</param>
/// <param name="Param_MeasuringMode">O modo de medição DirectWrite que indica como as métricas de glifo são usadas para medir o texto quando ele é formatado.</param>
/// <param name="Param_Out_Bounds">Retorna os limites do glifo são executados nos DIPs e no espaço do mundo(World-space Bounds).</param>
CarenResult CarenD2D1DeviceContext5::GetGlyphRunWorldBounds(
	CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
	CA_DWRITE_GLYPH_RUN^ Param_GlypRun,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode,
	[Out] CA_D2D1_RECT_F^% Param_Out_Bounds
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pMyBaseLine = NULL;
	DWRITE_GLYPH_RUN* pMyGlyphRun = NULL;
	D2D1_RECT_F MyOutBounds = {};

	//Converte as estruturas
	pMyBaseLine = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaseLineOrigin);
	pMyGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlypRun);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetGlyphRunWorldBounds(*pMyBaseLine, pMyGlyphRun, static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode), &MyOutBounds);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_Bounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&MyOutBounds);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pMyBaseLine);
	DeletarEstruturaSafe(&pMyGlyphRun);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém os limites de uma imagem sem a transformação mundial do contexto aplicado.
/// Os limites de imagem não incluem multiplicação pelo Wolrd Transform. Eles refletem o DPI atual, o modo unitário e o modo de interpolação do contexto.
/// Para obter os limites que incluem a World Transform, use ICarenD2D1DeviceContext::GetImageWorldBounds.
/// Os limites retornados refletem quais pixels seriam impactados chamando DrawImage com um deslocamento de alvo de (0,0) e uma matriz de World Transform da identidade. Eles não refletem o retângulo de clipe atual definido no contexto do dispositivo ou a extensão da imagem alvo atual do contexto.
/// </summary>
/// <param name="Param_Image">A imagem cujos limites serão calculados.</param>
/// <param name="Param_Out_LocalBounds">Retorna os limites da imagem em pixels independentes do dispositivo (DIPs) e no espaço local.</param>
CarenResult CarenD2D1DeviceContext5::GetImageLocalBounds(
	ICarenD2D1Image^ Param_Image,
	[Out] CA_D2D1_RECT_F^% Param_Out_LocalBounds
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pMyImage = NULL;
	D2D1_RECT_F MyOutLocalBounds = {};

	//Recupera o ponteiro para a imagem.
	Resultado = RecuperarPonteiroCaren(Param_Image, &pMyImage);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetImageLocalBounds(pMyImage, &MyOutLocalBounds);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_LocalBounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&MyOutLocalBounds);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém com os limites de uma imagem com a World Transform do contexto aplicado.
/// Os limites de imagem refletem o DPI atual, o modo unitário e a World Transform do contexto. Para obter limites que não incluem a World Transform, use ICarenD2D1DeviceContext::GetImageLocalBounds.
/// Os limites retornados refletem quais pixels seriam impactados chamando DrawImage com a mesma imagem e um deslocamento de alvo de (0,0). Eles não refletem o retângulo de clipe atual definido no contexto do dispositivo ou a extensão da imagem alvo atual do contexto.
/// </summary>
/// <param name="Param_Image">A imagem cujos limites serão calculados.</param>
/// <param name="Param_Out_WorldBounds">Retorna os limites da imagem em pixels independentes do dispositivo (DIPs).</param>
CarenResult CarenD2D1DeviceContext5::GetImageWorldBounds(
	ICarenD2D1Image^ Param_Image,
	[Out] CA_D2D1_RECT_F^% Param_Out_WorldBounds
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Image* pMyImage = NULL;
	D2D1_RECT_F MyOutWorldBounds = {};

	//Recupera o ponteiro para a imagem.
	Resultado = RecuperarPonteiroCaren(Param_Image, &pMyImage);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetImageWorldBounds(pMyImage, &MyOutWorldBounds);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Converte e define no parametro de saida.
	Param_Out_WorldBounds = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&MyOutWorldBounds);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna a mistura primitiva(PrimitiveBlend) atualmente definida usada pelo contexto do dispositivo.
/// </summary>
/// <param name="Param_Out_PrimitiveBlend">Retorna A mistura primitiva atual. O valor padrão é D2D1_PRIMITIVE_BLEND_SOURCE_OVER.</param>
void CarenD2D1DeviceContext5::GetPrimitiveBlend(
	[Out] CA_D2D1_PRIMITIVE_BLEND% Param_Out_PrimitiveBlend
)
{
	//Chama o método para realizar a operação.
	D2D1_PRIMITIVE_BLEND OutPrimitiveBlend = PonteiroTrabalho->GetPrimitiveBlend();

	//Converte e define no parametro de saida.
	Param_Out_PrimitiveBlend = static_cast<CA_D2D1_PRIMITIVE_BLEND>(OutPrimitiveBlend);
}

/// <summary>
/// Obtém os controles de renderização que foram aplicados ao contexto.
/// </summary>
/// <param name="Param_Out_ControlesRenderizacao">Retorna os controles de renderização para este contexto.</param>
void CarenD2D1DeviceContext5::GetRenderingControls(
	[Out] CA_D2D1_RENDERING_CONTROLS^% Param_Out_ControlesRenderizacao
)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDERING_CONTROLS MyOutRenderingControls = {};

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetRenderingControls(&MyOutRenderingControls);

	//Converte e define no parametro de saida.
	Param_Out_ControlesRenderizacao = Util.ConverterD2D1_RENDERING_CONTROLSUnmanagedToManaged(&MyOutRenderingControls);
}

/// <summary>
/// Obtém o alvo atualmente associado ao contexto do dispositivo.
/// Se um alvo não estiver associado ao contexto do dispositivo, o alvo retornado será NULO.
/// Não é possível que uma aplicação destrua esses bitmaps. Todos esses bitmaps são vinculáveis como alvos bitmap. No entanto, nem todos esses bitmaps podem ser usados como fontes de bitmap para métodos ICarenD2D1RenderTarget.
/// </summary>
/// <param name="Param_Out_Image">Retorna uma interface(ICarenD2D1Image) que contém um ponteiro para o alvo atualmente associado ao contexto do dispositivo.</param>
CarenResult CarenD2D1DeviceContext5::GetTarget(
	[Out] ICarenD2D1Image^% Param_Out_Image
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Image* pMyOutImage = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTarget(&pMyOutImage);

	//Cria a interface que vai ser retornada.
	Param_Out_Image = gcnew CarenD2D1Image();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pMyOutImage, Param_Out_Image);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o modo que está sendo usado para interpretar valores pelo contexto do dispositivo.
/// </summary>
/// <param name="Param_Out_Unit">Retorna O modo unitário.</param>
void CarenD2D1DeviceContext5::GetUnitMode([Out] CA_D2D1_UNIT_MODE Param_Out_Unit)
{
	//Chama o método para realizar a operação.
	Param_Out_Unit = static_cast<CA_D2D1_UNIT_MODE>(PonteiroTrabalho->GetUnitMode());
}

/// <summary>
/// Define que uma parte da entrada de um efeito é inválida. Este método pode ser chamado muitas vezes.
/// Você pode usar este método para propagar retângulos inválidos através de um gráfico de efeito. Você pode consultar o Direct2D usando o método GetEffectInvalidRectangles.
/// Você também pode usar este método para invalidar caches que acumularam ao renderizar efeitos que têm a propriedade D2D1_PROPERTY_CACHED definida como verdadeira.
/// </summary>
/// <param name="Param_Efeito">O efeito para invalidar.</param>
/// <param name="Param_InputIndex">O índice de entrada.</param>
/// <param name="Param_InputRectangle">O retangulo para invalidar.</param>
CarenResult CarenD2D1DeviceContext5::InvalidateEffectInputRectangle(
	ICarenD2D1Effect^ Param_Efeito,
	UInt32 Param_InputIndex,
	CA_D2D1_RECT_F^ Param_InputRectangle
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Effect* pMyEfeito = NULL;
	D2D1_RECT_F* pMyInputRect = NULL;

	//Recupera o ponteiro para o efeito.
	Resultado = RecuperarPonteiroCaren(Param_Efeito, &pMyEfeito);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura
	pMyInputRect = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_InputRectangle);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->InvalidateEffectInputRectangle(pMyEfeito, Param_InputIndex, pMyInputRect);

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
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pMyInputRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Indica se a precisão do buffer é suportada pelo dispositivo Direct3D subjacente.
/// </summary>
/// <param name="Param_BufferPrecision">A precisão do buffer para verificar.</param>
/// <param name="Param_Out_Suporte">Retorna TRUE se a precisão do buffer for suportada. Retorna FALSE se a precisão do buffer não for suportada.</param>
void CarenD2D1DeviceContext5::IsBufferPrecisionSupported(
	CA_D2D1_BUFFER_PRECISION  Param_BufferPrecision,
	[Out] Boolean% Param_Out_Suporte
)
{
	//Variaveis a serem utilizadas.
	D2D1_BUFFER_PRECISION BufferPrecision = static_cast<D2D1_BUFFER_PRECISION>(Param_BufferPrecision);
	BOOL OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	OutSuporte = PonteiroTrabalho->IsBufferPrecisionSupported(BufferPrecision);

	//Define no parametro de saida o resultado.
	Param_Out_Suporte = OutSuporte ? true : false;
}

/// <summary>
/// Verifica se o formato é suportado pelo contexto do dispositivo. Os formatos suportados geralmente são determinados pelo hardware subjacente.
/// Você pode usar formatos suportados na estrutura D2D1_PIXEL_FORMAT para criar bitmaps e renderizar alvos.
/// O Direct2D não suporta todos os formatos DXGI, embora eles possam ter algum nível de suporte Direct3D pelo hardware.
/// </summary>
/// <param name="Param_DxgiFormato">O formato DXGI para verificar.</param>
/// <param name="Param_Out_Suporte">Retorna TRUE se o formato for suportado. Retorna FALSE se o formato não for suportado.</param>
void CarenD2D1DeviceContext5::IsDxgiFormatSupported(
	CA_DXGI_FORMAT  Param_DxgiFormato,
	[Out] Boolean% Param_Out_Suporte
)
{
	//Variaveis a serem utilizadas.
	DXGI_FORMAT DxgiFormato = static_cast<DXGI_FORMAT>(Param_DxgiFormato);
	BOOL OutSuporte = FALSE;

	//Chama o método para realizar a operação.
	OutSuporte = PonteiroTrabalho->IsDxgiFormatSupported(DxgiFormato);

	//Define no parametro de saida o resultado.
	Param_Out_Suporte = OutSuporte ? true : false;
}

/// <summary>
/// Empurre uma camada sobre o clipe e a pilha de camadas do contexto do dispositivo.
/// </summary>
/// <param name="Param_ParametrosLayer">Os parâmetros que definem a camada.</param>
/// <param name="Param_Layer">O recurso de camada para empurrar o contexto do dispositivo que recebe operações de desenho subsequentes. [Nota] Se uma camada não for especificada, o Direct2D gerencia automaticamente o recurso de camada.</param>
void CarenD2D1DeviceContext5::PushLayer(
	CA_D2D1_LAYER_PARAMETERS1^ Param_ParametrosLayer,
	ICarenD2D1Layer^ Param_Layer)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LAYER_PARAMETERS1* pMyLayerParams = NULL;
	ID2D1Layer* pMyCamada = NULL;

	//Converte a estrutura
	pMyLayerParams = Util.ConverterD2D1_LAYER_PARAMETERS1ManagedToUnmanaged(Param_ParametrosLayer);

	//Recupera o ponteiro para a interface da camada.
	RecuperarPonteiroCaren(Param_Layer, &pMyCamada);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PushLayer(pMyLayerParams, pMyCamada);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyLayerParams);
}

/// <summary>
/// Altera o modo de mistura primitiva que é usado para todas as operações de renderização no contexto do dispositivo.
/// </summary>
/// <param name="Param_PrimitiveBlend">A mistura primitiva para usar.</param>
void CarenD2D1DeviceContext5::SetPrimitiveBlend(CA_D2D1_PRIMITIVE_BLEND Param_PrimitiveBlend)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetPrimitiveBlend(static_cast<D2D1_PRIMITIVE_BLEND>(Param_PrimitiveBlend));
}

/// <summary>
/// Define os controles de renderização para o contexto do dispositivo dado.
/// Os controles de renderização permitem que o aplicativo ajuste a precisão, o desempenho e o uso de recursos das operações de renderização.
/// </summary>
/// <param name="Param_ControlesRenderizacao">Os controles de renderização a serem aplicados.</param>
void CarenD2D1DeviceContext5::SetRenderingControls(CA_D2D1_RENDERING_CONTROLS^ Param_ControlesRenderizacao)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDERING_CONTROLS* pMyRenderingControls = NULL;

	//Converte a estrutura
	pMyRenderingControls = Util.ConverterD2D1_RENDERING_CONTROLSManagedToUnmanaged(Param_ControlesRenderizacao);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetRenderingControls(pMyRenderingControls);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMyRenderingControls);
}

/// <summary>
/// Define o bitmap ou lista de comando para a qual o contexto do dispositivo Direct2D será renderizado agora.
/// O alvo pode ser alterado a qualquer momento, inclusive enquanto o contexto estiver desenhando.
/// O alvo pode ser um bitmap criado com a bandeira D2D1_BITMAP_OPTIONS_TARGET, ou pode ser uma lista de comando. Outros tipos de imagens não podem ser definidas como um alvo. Por exemplo, você não pode definir a saída de um efeito como alvo. Se o alvo não for válido, o contexto entrará no estado de erro D2DERR_INVALID_TARGET.
/// Você não pode usar o SetTarget para renderizar a uma lista de bitmap/comando a partir de vários contextos de dispositivo simultaneamente. Uma imagem é considerada "sendo renderizada" se alguma vez foi definida em um contexto de dispositivo dentro de um timespan BeginDraw/EndDraw.
/// Se uma tentativa for feita para renderizar uma imagem através de vários contextos de dispositivo, todos os contextos subsequentes do dispositivo após o primeiro entrarão em um estado de erro.
/// </summary>
/// <param name="Param_Imagem">A superfície ou lista de comandos na qual o contexto do dispositivo Direct2D será renderizado.</param>
void CarenD2D1DeviceContext5::SetTarget(ICarenD2D1Image^ Param_Imagem)
{
	//Variaveis a serem utilizadas.
	ID2D1Image* pMyImage = NULL;

	//Recupera o ponteiro para a imagem.
	RecuperarPonteiroCaren(Param_Imagem, &pMyImage);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTarget(pMyImage);
}

/// <summary>
/// Define quais unidades serão usadas para interpretar valores passados no contexto do dispositivo.
/// Este método afetará todas as propriedades e parâmetros afetados pelo ICarenD2D1RenderTarget::SetDpi e ICarenD2D1RenderTarget::GetDpi. Isso afeta todas as coordenadas, comprimentos e outras propriedades que não são explicitamente definidas como sendo em outra unidade.
/// SetUnitMode afetará uma coordenada passada em ICarenD2D1DeviceContext::DrawLine, e o dimensionamento de uma geometria passou para ICarenD2D1DeviceContext::FillGeometry.
/// SetUnitMode não afetará o valor devolvido pelo ICarenD2D1Bitmap::GetPixelSize.
/// </summary>
/// <param name="Param_UnitMode">Uma enumeração definindo como as unidades de passagem serão interpretadas pelo contexto do dispositivo.</param>
void CarenD2D1DeviceContext5::SetUnitMode(CA_D2D1_UNIT_MODE Param_UnitMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetUnitMode(static_cast<D2D1_UNIT_MODE>(Param_UnitMode));
}






// Métodos da interface (ICarenD2D1RenderTarget)


/// <summary>
/// Inicia o desenho deste alvo de renderização. 
/// </summary>
void CarenD2D1DeviceContext5::BeginDraw()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->BeginDraw();
}

/// <summary>
/// Limpa a área de desenho para a cor especificada. 
/// </summary>
/// <param name="Param_ClearColor"></param>
void CarenD2D1DeviceContext5::Clear(CA_D2D1_COLOR_F^ Param_ClearColor)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;

	//Converte a estrutura gerenciada para a nativa.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_ClearColor);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->Clear(pColorF);


	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pColorF);
}

/// <summary>
/// Cria um bitmap do Direct2D de um ponteiro para dados de origem na memória. 
/// </summary>
/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
/// <param name="Param_DadosOrigem">Um ponteiro para a localização da memória dos dados da imagem ou NULO para criar um bitmap não inicializado.</param>
/// <param name="Param_Pitch">A contagem de bytes de cada linha de varredura, que é igual a (a largura da imagem em pixels × o número de bytes por pixel) + preenchimento de memória. Se (Param_DadosOrigem) é NULO, este valor é ignorado. (Note que o tom também é às vezes chamado de pitch.)</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmap(
	CA_D2D1_SIZE_U^ Param_Size,
	ICarenBuffer^ Param_DadosOrigem,
	UInt32 Param_Pitch,
	CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL;
	IntPtr pBufferOrigem = IntPtr::Zero;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Converte as estruturas gerenciadas para as nativas.
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Size);
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap);

	//Obtém o ponteiro para a memória de origem.
	Resultado = Param_DadosOrigem->GetInternalPointer(pBufferOrigem);

	//Verifica se não falhou.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recupera o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(*pSizeU, pBufferOrigem.ToPointer(), Param_Pitch, pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro na interface de saida.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera o ponteiro
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um bitmap do Direct2D não inicializado. 
/// </summary>
/// <param name="Param_Size">As dimensões em pixels do bitmap a ser criado.</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e pontos por polegada (DPI) do bitmap a ser criado.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface (ICarenD2D1Bitmap) que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmap(
	CA_D2D1_SIZE_U^ Param_Size,
	CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Converte as estruturas gerenciadas para as nativas.
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_Size);
	pBitmapProps = Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmap(*pSizeU, *pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro na interface de saida.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera o ponteiro
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. 
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel(Brush).</param>
/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,a escova padrão para o D2D1_EXTEND_MODE_CLAMP 
/// modos de extensão horizontal e vertical e o modo de interpolação D2D1_BITMAP_INTERPOLATION_MODE_LINEAR.</param>
/// <param name="Param_PropriedadesBrush">Uma estrutura que contenha a opacidade e a transformação do novo pincel, ou NULO. Se você definir este parâmetro como NULO,o pincel define o membro da opacidade 
/// para 1.0F e o membro de transformação para a matriz de identidade.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
	[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES* pBitmapBrushProps = NULL; //Pode ser NULO.
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL; //Pode ser NULO.
	ID2D1BitmapBrush* pOutBrush = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte as estruturas gerenciadas para a nativa se validas.
	pBitmapBrushProps = ObjetoGerenciadoValido(Param_PropriedadesBitmapBrush) ? Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmapBrush) : NULL;
	pBrushProps = ObjetoGerenciadoValido(Param_PropriedadesBrush) ? Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, pBitmapBrushProps, pBrushProps, &pOutBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pBitmapBrushProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para seu modo de extensão, modo de interpolação, opacidade e transformação.
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmap = NULL;
	ID2D1BitmapBrush* pOutBrush = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, &pOutBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ID2D1BitmapBrush a partir do bitmap especificado. O pincel usa os valores padrão para sua opacidade e transformação. 
/// O Brush bitmap criado por este método tem uma opacidade de 1.0f e a matriz de identidade como sua transformação.
/// </summary>
/// <param name="Param_Bitmap">O conteúdo do bitmap do novo pincel.</param>
/// <param name="Param_PropriedadesBitmapBrush">Os modos de extensão e o modo de interpolação do novo pincel.</param>
/// <param name="Param_Out_BitmapBrush">Retorna a interface (ICarenD2D1BitmapBrush) que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapBrush(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_BITMAP_BRUSH_PROPERTIES^ Param_PropriedadesBitmapBrush,
	[Out] ICarenD2D1BitmapBrush^% Param_Out_BitmapBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmap = NULL;
	ID2D1BitmapBrush* pOutBrush = NULL;
	D2D1_BITMAP_BRUSH_PROPERTIES* pBitmapBrushProps = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_Bitmap->RecuperarPonteiro((LPVOID*)&pBitmap);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte as estruturas gerenciadas para a nativa se validas.
	pBitmapBrushProps = Util.ConverterD2D1_BITMAP_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmapBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapBrush(pBitmap, *pBitmapBrushProps, &pOutBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a classe a ser retornada.
	Param_Out_BitmapBrush = gcnew CarenD2D1BitmapBrush();

	//Define o ponteiro da interface.
	Resultado = Param_Out_BitmapBrush->AdicionarPonteiro(pOutBrush);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBrush->Release();
		pOutBrush = NULL;
		Param_Out_BitmapBrush->Finalizar();
		Param_Out_BitmapBrush = nullptr;
	}

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC). 
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. O formato pixel deve corresponder ao formato de pixel do wicBitmapSource, ou o método falhará. Para evitar uma 
/// incompatibilidade, você pode passar NULO ou passar o valor obtido ligando para a função de ajudante D2D1::PixelFormat sem especificar nenhum valor de parâmetro. Se o dpiX e o dpiY forem 0,0f, o 
/// DPI padrão, 96, será usado. As informações de DPI incorporadas no (Param_WicBitmapSource) são ignoradas.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapFromWicBitmap(
	ICaren^ Param_WicBitmapSource,
	CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmapSource* pWicBitmapSource = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL; //Pode ser NULO.
	ID2D1Bitmap* pOutBitmap = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_WicBitmapSource->RecuperarPonteiro((LPVOID*)&pWicBitmapSource);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Converte a estrutura gerenciada para a nativa se valida.
	pBitmapProps = ObjetoGerenciadoValido(Param_PropriedadesBitmap) ? Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap) : NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWicBitmapSource, pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a classe a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ID2D1Bitmap copiando o bitmap especificado do Microsoft Windows Imaging Component (WIC).
/// </summary>
/// <param name="Param_WicBitmapSource">Uma interface ICarenWICBitmapSource que contém os dados a serem copiados.</param>
/// <param name="Param_Out_Bitmap">Retorna a interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateBitmapFromWicBitmap(
	ICaren^ Param_WicBitmapSource,
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IWICBitmapSource* pWicBitmapSource = NULL;
	ID2D1Bitmap* pOutBitmap = NULL;

	//Recupera o ponteiro para o bitmap.
	Resultado = Param_WicBitmapSource->RecuperarPonteiro((LPVOID*)&pWicBitmapSource);

	//Verifica se não houve erro.
	if (!CarenSucesso(Resultado))
	{
		//Falhou. O ponteiro é invalido.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateBitmapFromWicBitmap(pWicBitmapSource, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a classe a ser retornada.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface.
	Resultado = Param_Out_Bitmap->AdicionarPonteiro(pOutBitmap);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao definir o ponteiro.

		//Libera os dados.
		pOutBitmap->Release();
		pOutBitmap = NULL;
		Param_Out_Bitmap->Finalizar();
		Param_Out_Bitmap = nullptr;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará 
/// o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
/// <param name="Param_Opcoes">Um valor que especifica se o novo alvo de renderização deve ser compatível com o GDI.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DeviceContext5::CreateCompatibleRenderTarget(
	CA_D2D1_SIZE_F^ Param_DesiredSize,
	CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
	CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
	CA_D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS Param_Opcoes,
	ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_PIXEL_FORMAT* pPixelFormat = NULL;
	D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS OptonsRender = static_cast<D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS>(Param_Opcoes);
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);
	pPixelFormat = Util.ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(DesiredFormat);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, *pPixelFormat, &pOutRenderTarget);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget, true));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pPixelFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo alvo de renderização bitmap para uso durante o desenho offscreen intermediário que é compatível com o alvo de renderização atual e tem o mesmo tamanho, DPI e formato de pixel 
/// (mas não o modo alfa) como o alvo de renderização atual. 
/// O alvo de renderização bitmap criado por este método não é compatível com o GDI, e tem um modo alfa de D2D1_ALPHA_MODE_PREMULTIPLIED.
/// </summary>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DeviceContext5::CreateCompatibleRenderTarget(ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->CreateCompatibleRenderTarget(&pOutRenderTarget);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget, true));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// O alvo de renderização bitmap criado por este método não é compatível com o GDI.
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo destino de renderização em pixels independentes do dispositivo. O tamanho do pixel é calculado a partir do tamanho desejado usando o DPI pai de destino. 
/// Se o tamanho desejado for mapeado para um tamanho de pixel inteiro, o DPI do destino de renderização compatível será o mesmo que o DPI pai do destino. Se o Tamanho desejado é mapeado para um tamanho de pixel 
/// fracionário, o tamanho do pixel é arredondado para o número inteiro mais próximo e o DPI para o destino de renderização compatível é um pouco maior que o DPI do destino de renderização pai. Em todos os casos, 
/// a coordenada (Param_DesiredSize.width, Param_DesiredSize.height) é mapeada para o canto inferior direito do destino de renderização compatível.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DeviceContext5::CreateCompatibleRenderTarget(
	CA_D2D1_SIZE_F^ Param_DesiredSize,
	ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte a estrutura.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, &pOutRenderTarget);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DeviceContext5::CreateCompatibleRenderTarget(
	CA_D2D1_SIZE_F^ Param_DesiredSize,
	CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
	ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, &pOutRenderTarget);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização bitmap para uso durante o desenho offscreen intermediário compatível com o alvo de renderização atual. 
/// </summary>
/// <param name="Param_DesiredSize">O tamanho desejado do novo alvo de renderização (em pixels independentes do dispositivo), se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="Param_DesiredPixelSize">O tamanho desejado do novo alvo de renderização em pixels se ele deve ser diferente do alvo de renderização original.</param>
/// <param name="DesiredFormat">O formato de pixel desejado e o modo alfa do novo alvo de renderização. Se o formato do pixel for definido para DXGI_FORMAT_UNKNOWN, o novo alvo de renderização usará o mesmo formato de pixel que o alvo original da renderização. Se o modo alfa estiver D2D1_ALPHA_MODE_UNKNOWN,o modo alfa do novo destino renderizante padrão para D2D1_ALPHA_MODE_PREMULTIPLIED.</param>
/// <param name="Param_Out_BitmapRenderTarget">Retorna a interface (ICarenD2D1BitmapRenderTarget) que contém um ponteiro para um novo alvo de renderização bitmap. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1DeviceContext5::CreateCompatibleRenderTarget(
	CA_D2D1_SIZE_F^ Param_DesiredSize,
	CA_D2D1_SIZE_U^ Param_DesiredPixelSize,
	CA_D2D1_PIXEL_FORMAT^ DesiredFormat,
	ICaren^ Param_Out_BitmapRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	D2D1_SIZE_U* pSizeU = NULL;
	D2D1_PIXEL_FORMAT* pPixelFormat = NULL;
	ID2D1BitmapRenderTarget* pOutRenderTarget = NULL;

	//Converte as estruturas.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_DesiredSize);
	pSizeU = Util.ConverterD2D1_SIZE_UManagedToUnmanaged(Param_DesiredPixelSize);
	pPixelFormat = Util.ConverterD2D1_PIXEL_FORMATManagedToUnmanaged(DesiredFormat);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateCompatibleRenderTarget(*pSizeF, *pSizeU, *pPixelFormat, &pOutRenderTarget);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define o ponteiro da interface inicializada pelo usuário. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRenderTarget, Param_Out_BitmapRenderTarget));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pSizeF);
	DeletarEstruturaSafe(&pSizeU);
	DeletarEstruturaSafe(&pPixelFormat);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma interface de coleção ICarenD2D1GradientStop a partir do conjunto especificado de estruturas CA_D2D1_GRADIENT_STOP. 
/// </summary>
/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
/// <param name="Param_ColorInterpolationGamma">O espaço em que a interpolação de cores entre as paradas gradientes é realizada.</param>
/// <param name="Param_ModoExtendido">O comportamento do gradiente fora da faixa [0,1] normalizada.</param>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
CarenResult CarenD2D1DeviceContext5::CreateGradientStopCollection(
	cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
	UInt32 Param_QuantidadeGradientes,
	CA_D2D1_GAMMA Param_ColorInterpolationGamma,
	CA_D2D1_EXTEND_MODE Param_ModoExtendido,
	[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	D2D1_GRADIENT_STOP* pMatrizGradientes = CriarMatrizEstruturas<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);
	D2D1_GAMMA Gamma = static_cast<D2D1_GAMMA>(Param_ColorInterpolationGamma);
	D2D1_EXTEND_MODE ExtendMode = static_cast<D2D1_EXTEND_MODE>(Param_ModoExtendido);
	ID2D1GradientStopCollection* pOutGradientCollection = NULL;

	//Copia os dados da matriz gerenciada para a nativa.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		//Inicializa a estrutura no index especifico.
		ZeroMemory(&pMatrizGradientes[i], sizeof(D2D1_GRADIENT_STOP));

		//Define os dados.
		pMatrizGradientes[i].position = Param_MatrizGraientStops[i]->position;

		//Define os dados ARGB.
		pMatrizGradientes->color.a = Param_MatrizGraientStops[i]->color->a;
		pMatrizGradientes->color.r = Param_MatrizGraientStops[i]->color->r;
		pMatrizGradientes->color.g = Param_MatrizGraientStops[i]->color->g;
		pMatrizGradientes->color.b = Param_MatrizGraientStops[i]->color->b;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientStopCollection(pMatrizGradientes, Param_QuantidadeGradientes, Gamma, ExtendMode, &pOutGradientCollection);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutGradientCollection, Param_Out_GradientStopCollection));

Done:;
	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizGradientes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
///  Cria uma interface de coleção ICarenD2D1GradientStop a partir das estruturas GradientStops especificadas que usa o gama de interpolação de cores D2D1_GAMMA_2_2 e o modo de extensão do Clamp. 
/// </summary>
/// <param name="Param_MatrizGraientStops">Uma matriz de estruturas CA_D2D1_GRADIENT_STOP.</param>
/// <param name="Param_QuantidadeGradientes">Um valor maior ou igual a 1 que especifica o número de estruturas(CA_D2D1_GRADIENT_STOP) na matriz (Param_MatrizGraientStops).</param>
/// <param name="Param_Out_GradientStopCollection">Retorna a interface ICarenD2D1GradientStopCollection que contém um ponteiro para a nova GradientStopCollection.</param>
CarenResult CarenD2D1DeviceContext5::CreateGradientStopCollection(
	cli::array<CA_D2D1_GRADIENT_STOP^>^ Param_MatrizGraientStops,
	UInt32 Param_QuantidadeGradientes,
	[Out] ICarenD2D1GradientStopCollection^% Param_Out_GradientStopCollection)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_GRADIENT_STOP* pMatrizGradientes = CriarMatrizEstruturas<D2D1_GRADIENT_STOP>(Param_QuantidadeGradientes);
	ID2D1GradientStopCollection* pOutGradientCollection = NULL;

	//Copia os dados da matriz gerenciada para a nativa.
	for (UInt32 i = 0; i < Param_QuantidadeGradientes; i++)
	{
		//Inicializa a estrutura no index especifico.
		ZeroMemory(&pMatrizGradientes[i], sizeof(D2D1_GRADIENT_STOP));

		//Define os dados.
		pMatrizGradientes[i].position = Param_MatrizGraientStops[i]->position;

		//Define os dados ARGB.
		pMatrizGradientes->color.a = Param_MatrizGraientStops[i]->color->a;
		pMatrizGradientes->color.r = Param_MatrizGraientStops[i]->color->r;
		pMatrizGradientes->color.g = Param_MatrizGraientStops[i]->color->g;
		pMatrizGradientes->color.b = Param_MatrizGraientStops[i]->color->b;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGradientStopCollection(pMatrizGradientes, Param_QuantidadeGradientes, &pOutGradientCollection);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_GradientStopCollection = gcnew CarenD2D1GradientStopCollection();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutGradientCollection, Param_Out_GradientStopCollection));

Done:;
	//Libera a memória para a matriz de estruturas.
	DeletarMatrizEstruturasSafe(&pMatrizGradientes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis.
/// </summary>
/// <param name="Param_Size">Se (0, 0) for especificado, nenhuma loja de backup será criada por trás do recurso de camada. O recurso de camada é alocado para o tamanho mínimo quando o PushLayer é chamado.</param>
/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
CarenResult CarenD2D1DeviceContext5::CreateLayer(
	CA_D2D1_SIZE_F^ Param_Size,
	[Out] ICarenD2D1Layer^% Param_Out_Layer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F* pSizeF = NULL;
	ID2D1Layer* pOutLayer = NULL;

	//Converte a estrutura.
	pSizeF = Util.ConverterD2D1_SIZE_FManagedToUnmanaged(Param_Size);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLayer(pSizeF, &pOutLayer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_Layer = gcnew CarenD2D1Layer();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLayer, Param_Out_Layer));

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pSizeF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um recurso de camada que pode ser usado com este alvo de renderização e seus alvos de renderização compatíveis. 
/// </summary>
/// <param name="Param_Out_Layer">Retorna a interface ICarenD2D1Layer que contém um ponteiro para a nova camada(Layer).</param>
CarenResult CarenD2D1DeviceContext5::CreateLayer([Out] ICarenD2D1Layer^% Param_Out_Layer)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Layer* pOutLayer = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLayer(&pOutLayer);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_Layer = gcnew CarenD2D1Layer();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLayer, Param_Out_Layer));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1LinearGradientBrush que contém as GradientStops especificadas e tem a opacidade de transformação e base especificada. 
/// </summary>
/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateLinearGradientBrush(
	CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
	ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
	[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* pLinearGradientProps = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1LinearGradientBrush* pOutLinearGradientBrush = NULL;

	//Converte as estruturas.
	pLinearGradientProps = Util.ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesLinerarGradientBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLinearGradientBrush(pLinearGradientProps, pBrushProps, pGradientStopCollection, &pOutLinearGradientBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_LinearGradientBrush = gcnew CarenD2D1LinearGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLinearGradientBrush, Param_Out_LinearGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pLinearGradientProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1LinearGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
/// </summary>
/// <param name="Param_PropriedadesLinerarGradientBrush">Os pontos de partida e fim do gradiente.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo da linha gradiente.</param>
/// <param name="Param_Out_LinearGradientBrush">Retorna uma interface ICarenD2D1LinearGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateLinearGradientBrush(
	CA_D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesLinerarGradientBrush,
	ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
	[Out] ICarenD2D1LinearGradientBrush^% Param_Out_LinearGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* pLinearGradientProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1LinearGradientBrush* pOutLinearGradientBrush = NULL;

	//Converte a estrutura.
	pLinearGradientProps = Util.ConverterD2D1_LINEAR_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesLinerarGradientBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateLinearGradientBrush(*pLinearGradientProps, pGradientStopCollection, &pOutLinearGradientBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_LinearGradientBrush = gcnew CarenD2D1LinearGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutLinearGradientBrush, Param_Out_LinearGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pLinearGradientProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Crie uma malha(Mesh) que usa triângulos para descrever uma forma. 
/// </summary>
/// <param name="Param_Out_Mesh">Retorna uma interface ICarenD2D1Mesh que contém um ponteiro para a nova malha(Mesh).</param>
CarenResult CarenD2D1DeviceContext5::CreateMesh([Out] ICarenD2D1Mesh^% Param_Out_Mesh)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1Mesh* pOutMesh = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateMesh(&pOutMesh);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_Mesh = gcnew CarenD2D1Mesh();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutMesh, Param_Out_Mesh));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados e tem a opacidade de transformação e base especificada.
/// </summary>
/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
/// <param name="Param_PropriedadesBrush">A opacidade de transformação e base do novo pincel(Brush).</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateRadialGradientBrush(
	CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
	ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
	[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* pRadialGradientProps = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1RadialGradientBrush* pOutRadialGradientBrush = NULL;

	//Converte as estruturas.
	pRadialGradientProps = Util.ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesRadialGradientBrush);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRadialGradientBrush(pRadialGradientProps, pBrushProps, pGradientStopCollection, &pOutRadialGradientBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_RadialGradientBrush = gcnew CarenD2D1RadialGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRadialGradientBrush, Param_Out_RadialGradientBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRadialGradientProps);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1RadialGradientBrush que contém os GradientStops especificados, não tem transformação e tem uma opacidade base de 1.0. 
/// </summary>
/// <param name="Param_PropriedadesRadialGradientBrush">O centro, a origem gradiente compensada, e raio x e raio y do gradiente do Brush.</param>
/// <param name="Param_GradientStopCollection">Uma interface que contém uma coleção de estruturas D2D1_GRADIENT_STOP que descrevem as cores no Brush Gradient e suas localizações ao longo do gradiente.</param>
/// <param name="Param_Out_RadialGradientBrush">Retorna uma interface ICarenD2D1RadialGradientBrush que contém um ponteiro para o novo Pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateRadialGradientBrush(
	CA_D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES^ Param_PropriedadesRadialGradientBrush,
	ICarenD2D1GradientStopCollection^ Param_GradientStopCollection,
	[Out] ICarenD2D1RadialGradientBrush^% Param_Out_RadialGradientBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* pRadialGradientProps = NULL;
	ID2D1GradientStopCollection* pGradientStopCollection = NULL;
	ID2D1RadialGradientBrush* pOutRadialGradientBrush = NULL;

	//Converte a estrutura.
	pRadialGradientProps = Util.ConverterD2D1_RADIAL_GRADIENT_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesRadialGradientBrush);

	//Recupera o ponteiro para a coleção de gradientes.
	Resultado = RecuperarPonteiroCaren(Param_GradientStopCollection, &pGradientStopCollection);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRadialGradientBrush(*pRadialGradientProps, pGradientStopCollection, &pOutRadialGradientBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_RadialGradientBrush = gcnew CarenD2D1RadialGradientBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutRadialGradientBrush, Param_Out_RadialGradientBrush));

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1Bitmap cujos dados são compartilhados com outro recurso. 
/// </summary>
/// <param name="Param_Riid">O ID de interface do objeto que fornece os dados de origem.</param>
/// <param name="Param_InterfaceDados">Uma ICarenD2D1Bitmap, ICarenDXGISurface ou uma ICarenWICBitmapLock que contém os dados para compartilhar com o novo ICarenD2D1Bitmap. </param>
/// <param name="Param_PropriedadesBitmap">O formato de pixel e DPI do bitmap para criar. A DXGI_FORMAT parte do formato pixel deve corresponder à DXGI_FORMAT de dados ou o método falhará, mas os modos alfa 
/// não precisam coincidir. Para evitar uma incompatibilidade, você pode passar NULO ou o valor obtido da função auxiliar D2D1::PixelFormat. As configurações de DPI não têm que coincidir com as dos dados. 
/// Se o dpiX e o dpiY forem 0,0f, o DPI do alvo de renderização será usado.</param>
/// <param name="Param_Out_Bitmap">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo bitmap.</param>
CarenResult CarenD2D1DeviceContext5::CreateSharedBitmap(
	String^ Param_Riid,
	ICaren^ Param_InterfaceDados,
	CA_D2D1_BITMAP_PROPERTIES^ Param_PropriedadesBitmap,
	[Out] ICarenD2D1Bitmap^% Param_Out_Bitmap)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID Riid = GUID_NULL;
	PVOID pInterfaceDados = NULL;
	D2D1_BITMAP_PROPERTIES* pBitmapProps = NULL; //Poder ser NULO.
	ID2D1Bitmap* pOutBitmap = NULL;

	//Cria e converte os dados necessários.
	Riid = Util.CreateGuidFromString(Param_Riid);
	pBitmapProps = ObjetoGerenciadoValido(Param_PropriedadesBitmap) ? Util.ConverterD2D1_BITMAP_PROPERTIESManagedToUnmanaged(Param_PropriedadesBitmap) : NULL;

	//Recupera o ponteiro para a interface de dados.
	Resultado = RecuperarPonteiroCaren(Param_InterfaceDados, &pInterfaceDados);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSharedBitmap(Riid, pInterfaceDados, pBitmapProps, &pOutBitmap);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_Bitmap = gcnew CarenD2D1Bitmap();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutBitmap, Param_Out_Bitmap));

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pBitmapProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor e a opacidade especificados.
/// </summary>
/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel.</param>
/// <param name="Param_PropriedadesBrush">A opacidade base do pincel.</param>
/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateSolidColorBrush(
	CA_D2D1_COLOR_F^ Param_Cor,
	CA_D2D1_BRUSH_PROPERTIES^ Param_PropriedadesBrush,
	[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;
	D2D1_BRUSH_PROPERTIES* pBrushProps = NULL;
	ID2D1SolidColorBrush* pOutSolidColorBrush = NULL;

	//Converte as estruturas.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Cor);
	pBrushProps = Util.ConverterD2D1_BRUSH_PROPERTIESManagedToUnmanaged(Param_PropriedadesBrush);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSolidColorBrush(pColorF, pBrushProps, &pOutSolidColorBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_SolidColorBrush = gcnew CarenD2D1SolidColorBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutSolidColorBrush, Param_Out_SolidColorBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pColorF);
	DeletarEstruturaSafe(&pBrushProps);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo ICarenD2D1SolidColorBrush que tem a cor especificada e uma opacidade base de 1.0f.
/// </summary>
/// <param name="Param_Cor">Os valores vermelho, verde, azul e alfa da cor do pincel(Brush).</param>
/// <param name="Param_Out_SolidColorBrush">Retorna uma interface ICarenD2D1Bitmap que contém um ponteiro para o novo pincel(Brush).</param>
CarenResult CarenD2D1DeviceContext5::CreateSolidColorBrush(
	CA_D2D1_COLOR_F^ Param_Cor,
	[Out] ICarenD2D1SolidColorBrush^% Param_Out_SolidColorBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_COLOR_F* pColorF = NULL;
	ID2D1SolidColorBrush* pOutSolidColorBrush = NULL;

	//Converte a estrutura.
	pColorF = Util.ConverterD2D1_COLOR_FManagedToUnmanaged(Param_Cor);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateSolidColorBrush(*pColorF, &pOutSolidColorBrush);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Cria a interface de saida.
	Param_Out_SolidColorBrush = gcnew CarenD2D1SolidColorBrush();

	//Define o ponteiro da interface. Libera a interface nativa em caso de erro.
	SairOnError(DefinirPonteiroInterface(pOutSolidColorBrush, Param_Out_SolidColorBrush));

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pColorF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o bitmap especificado depois de dimensioná-lo para o tamanho do retângulo especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawBitmap) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw 
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Bitmap">O bitmap para renderizar.</param>
/// <param name="Param_RetanguloDestino">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do alvo de renderização, da área para a qual o bitmap é desenhado. 
/// Se o retângulo não for bem ordenado, nada é desenhado, mas o alvo de renderização não entra em um estado de erro.</param>
/// <param name="Param_Opacidade">Um valor entre 0,0f e 1,0f, inclusive, que especifica um valor de opacidade para aplicar ao bitmap; este valor é multiplicado em relação aos valores alfa do 
/// conteúdo do bitmap.</param>
/// <param name="Param_InterpolationMode">O modo de interpolação a ser usado se o bitmap for dimensionado ou girado pela operação de desenho.</param>
/// <param name="Param_RetanguloOrigem">O tamanho e a posição, em pixels independentes do dispositivo no espaço de coordenadas do bitmap, da área dentro do bitmap para desenhar.</param>
CarenResult CarenD2D1DeviceContext5::DrawBitmap(
	ICarenD2D1Bitmap^ Param_Bitmap,
	CA_D2D1_RECT_F^ Param_RetanguloDestino,
	float Param_Opacidade,
	CA_D2D1_BITMAP_INTERPOLATION_MODE Param_InterpolationMode,
	CA_D2D1_RECT_F^ Param_RetanguloOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pBitmapRender = NULL;
	D2D1_RECT_F* pRectDestinoF = NULL;
	D2D1_RECT_F* pRectOrigemF = NULL;
	D2D1_BITMAP_INTERPOLATION_MODE BitmapInterpolationMode = static_cast<D2D1_BITMAP_INTERPOLATION_MODE>(Param_InterpolationMode);

	//Recupera o ponteiro para o bitmap
	Resultado = RecuperarPonteiroCaren(Param_Bitmap, &pBitmapRender);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pRectDestinoF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pRectOrigemF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawBitmap(pBitmapRender, pRectDestinoF, Param_Opacidade, BitmapInterpolationMode, pRectOrigemF);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRectDestinoF);
	DeletarEstruturaSafe(&pRectOrigemF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) da elipse especificada usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Ellipse">A posição e o raio da elipse para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno da elipse.</param>
/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão 
/// para 1.0f. O golpe está centrado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do Stroke para aplicar ao contorno(Outline) da elipse, ou NULO para pintar um traço sólido.</param>
CarenResult CarenD2D1DeviceContext5::DrawEllipse(
	CA_D2D1_ELLIPSE^ Param_Ellipse,
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ELLIPSE* pEllipse = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL; //Pode ser NULO.

	//Recupera o ponteiro para o Brush.
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Converte a estrutura.
	pEllipse = Util.ConverterD2D1_ELLIPSEManagedToUnmanaged(Param_Ellipse);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawEllipse(pEllipse, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pEllipse);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno da geometria especificada usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Geometria">A geometria para desenhar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o traço(Stroke) da geometria.</param>
/// <param name="Param_StrokeWidth">A largura do traçado, em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se este parâmetro não for especificado, ele será padrão
/// para 1.0f. O golpe está centrado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo de traçado(Stroke) para aplicar ao contorno(Outline) da geometria, ou NULO para pintar um traço(Stroke) sólido.</param>
CarenResult CarenD2D1DeviceContext5::DrawGeometry(
	ICarenD2D1Geometry^ Param_Geometria,
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometryRender = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a gemetria.
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pGeometryRender);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Brush.
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGeometry(pGeometryRender, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha os glifos(Glyph) especificados.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawGlyphRun) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_BaseLineOrigin">A origem, em pixels independentes de dispositivos, da linha de base dos glifos(Glyph).</param>
/// <param name="Param_GlyphRun">Os glifos(Glyph) para renderizar.</param>
/// <param name="Param_ForegroundBrush">O pincel(Brush) usado para pintar os glifos(Glyph) especificados.</param>
/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
CarenResult CarenD2D1DeviceContext5::DrawGlyphRun(
	CA_D2D1_POINT_2F^ Param_BaseLineOrigin,
	CA_DWRITE_GLYPH_RUN^ Param_GlyphRun,
	ICarenD2D1Brush^ Param_ForegroundBrush,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint = NULL;
	DWRITE_GLYPH_RUN* pGlyphRun = NULL;
	ID2D1Brush* pBrush = NULL;
	DWRITE_MEASURING_MODE DWriteMeasuringMode = static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode);

	//Converte as estruturas.
	pPoint = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_BaseLineOrigin);
	pGlyphRun = Util.ConverterDWRITE_GLYPH_RUNManagedToUnmanaged(Param_GlyphRun);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_ForegroundBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawGlyphRun(*pPoint, pGlyphRun, pBrush, DWriteMeasuringMode);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as matrizes.
	DeletarEstruturaSafe(&pPoint);
	if (ObjetoValido(pGlyphRun))
	{
		//Libera as matrizes internas da estrutura.
		DeletarMatrizUnidimensionalSafe(&pGlyphRun->glyphIndices);
		DeletarMatrizUnidimensionalSafe(&pGlyphRun->glyphAdvances);
		DeletarMatrizEstruturasSafe(&pGlyphRun->glyphOffsets);
	}
	DeletarEstruturaSafe(&pGlyphRun);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha uma linha entre os pontos especificados usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawLine) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Point0">O ponto de partida da linha, em pixels independentes de dispositivos.</param>
/// <param name="Param_Point1">O ponto final da linha, em pixels independentes de dispositivos.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o traço da linha.</param>
/// <param name="Param_StrokeWidth">A largura do Stroke, em pixels independentes do dispositivo.O valor deve ser maior ou igual a 0, 0f.Se esse parâmetro não for especificado, o padrão será 1.0f. 
/// O Stroke é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo de Stroke para pintar, ou NULO para pintar uma linha sólida.</param>
CarenResult CarenD2D1DeviceContext5::DrawLine(
	CA_D2D1_POINT_2F^ Param_Point0,
	CA_D2D1_POINT_2F^ Param_Point1,
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPoint0 = NULL;
	D2D1_POINT_2F* pPoint1 = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte as estruturas.
	pPoint0 = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point0);
	pPoint1 = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Point1);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawLine(*pPoint0, *pPoint1, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pPoint0);
	DeletarEstruturaSafe(&pPoint1);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) de um retângulo que tem as dimensões especificadas e o estilo de traçado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">As dimensões do retângulo para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o curso do retângulo.</param>
/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, 
/// o padrão será 1.0f. O traço(Stroke) é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do traço(Stroke) para pintar ou NULO para pintar um traçado sólido.</param>
CarenResult CarenD2D1DeviceContext5::DrawRectangle(
	CA_D2D1_RECT_F^ Param_Rect,
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pRectF = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte a estrutura.
	pRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_Rect);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawRectangle(pRectF, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o contorno(Outline) do retângulo arredondado especificado usando o estilo de traçado especificado. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_RoundedRect">As dimensões do retângulo arredondado para desenhar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o contorno do retângulo arredondado.</param>
/// <param name="Param_StrokeWidth">A largura do traçado(Stroke), em pixels independentes do dispositivo. O valor deve ser maior ou igual a 0,0f. Se esse parâmetro não for especificado, o padrão 
/// será 1.0f. O traço(Stroke) é centralizado na linha.</param>
/// <param name="Param_StrokeStyle">O estilo do traçado do retângulo arredondado, ou NULO para pintar um traço sólido. O valor padrão é NULO.</param>
CarenResult CarenD2D1DeviceContext5::DrawRoundedRectangle(
	CA_D2D1_ROUNDED_RECT^ Param_RoundedRect,
	ICarenD2D1Brush^ Param_Brush,
	float Param_StrokeWidth,
	ICarenD2D1StrokeStyle^ Param_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ROUNDED_RECT* pRoundedRect = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1StrokeStyle* pStrokeStyle = NULL;

	//Converte a estrutura.
	pRoundedRect = Util.ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(Param_RoundedRect);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o Stroke se informado.
	if (ObjetoGerenciadoValido(Param_StrokeStyle))
	{
		//Recupera o ponteiro.
		RecuperarPonteiroCaren(Param_StrokeStyle, &pStrokeStyle);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawRoundedRectangle(pRoundedRect, pBrush, Param_StrokeWidth, pStrokeStyle);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRoundedRect);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o texto especificado usando as informações de formato fornecidas por um objeto ICarenDWriteTextFormat. 
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawText) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Texto">Uma string de caracteres Unicode para desenhar.</param>
/// <param name="Param_TamanhoTexto">O número de caracteres em (Param_Texto).</param>
/// <param name="Param_TextFormat">Uma interface(ICarenDWriteTextFormat) que descreve a formatação de detalhes do texto para desenhar, como a fonte, o tamanho da fonte e a direção do fluxo.</param>
/// <param name="Param_LayoutRect">O tamanho e a posição da área em que o texto é desenhado.</param>
/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar o texto.</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
/// <param name="Param_MeasuringMode">Um valor que indica como as métricas do glifo(Glyph) são usadas para medir o texto quando ele é formatado. O valor padrão é DWRITE_MEASURING_MODE_NATURAL.</param>
CarenResult CarenD2D1DeviceContext5::DrawText(
	String^ Param_Texto,
	UInt32 Param_TamanhoTexto,
	ICaren^ Param_TextFormat,
	CA_D2D1_RECT_F^ Param_LayoutRect,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes,
	CA_DWRITE_MEASURING_MODE Param_MeasuringMode)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	PWCHAR pTexto = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	D2D1_RECT_F* pLayoutRectF = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_DRAW_TEXT_OPTIONS DrawTextOptions = static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes);
	DWRITE_MEASURING_MODE MeasuringMode = static_cast<DWRITE_MEASURING_MODE>(Param_MeasuringMode);

	//Verifica se a string é valida
	if (!ObjetoGerenciadoValido(Param_Texto))
		throw gcnew NullReferenceException("O texto a ser desenhado não pode ser NULO!");

	//Converte a string para wchar
	pTexto = Util.ConverterStringToWCHAR(Param_Texto);

	//Recupera o ponteiro para a interface de formato do texto.
	Resultado = RecuperarPonteiroCaren(Param_TextFormat, &pTextFormat);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_DefaultFillBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pLayoutRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_LayoutRect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawText(pTexto, Param_TamanhoTexto, pTextFormat, pLayoutRectF, pBrush, DrawTextOptions, MeasuringMode);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para os dados.
	DeletarStringAllocatedSafe(&pTexto);
	DeletarEstruturaSafe(&pLayoutRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desenha o texto formatado descrito pelo objeto ICarenDWriteTextLayout especificado.
/// Ao desenhar o mesmo texto repetidamente, o uso do método DrawTextLayout é mais eficiente do que usar o método DrawText porque o texto não precisa ser formatado e o layout processado a cada chamada.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como DrawTextLayout) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Origem">O ponto, descrito em pixels independentes do dispositivo, no qual o canto superior esquerdo do texto descrito pelo (Param_TextLayout) é desenhado.</param>
/// <param name="Param_TextLayout">Uma interface(ICarenDWriteTextLayout) com o texto formatado para desenhar. Quaisquer efeitos de desenho que não herdem do ID2D1Resource são ignorados. Se houver 
/// efeitos de desenho que herdam do ICarenD2D1Resource que não são pincéis, este método falhará e o alvo de renderização é colocado em um estado de erro.</param>
/// <param name="Param_DefaultFillBrush">O pincel(Brush) usado para pintar qualquer texto no (Param_TextLayout) que ainda não tenha um pincel associado a ele como efeito de desenho (especificado pelo 
/// método ICarenDWriteTextLayout::SetDrawingEffect).</param>
/// <param name="Param_Opcoes">Um valor que indica se o texto deve ser encaixado nos limites do pixel e se o texto deve ser cortado no retângulo de layout. O valor padrão é D2D1_DRAW_TEXT_OPTIONS_NONE, 
/// o que indica que o texto deve ser encaixado nos limites do pixel e não deve ser cortado para o retângulo de layout.</param>
CarenResult CarenD2D1DeviceContext5::DrawTextLayout(
	CA_D2D1_POINT_2F^ Param_Origem,
	ICaren^ Param_TextLayout,
	ICarenD2D1Brush^ Param_DefaultFillBrush,
	CA_D2D1_DRAW_TEXT_OPTIONS Param_Opcoes)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_POINT_2F* pPointOrigem = NULL;
	IDWriteTextLayout* pDwriterTextLayout = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_DRAW_TEXT_OPTIONS DrawTextOptions = static_cast<D2D1_DRAW_TEXT_OPTIONS>(Param_Opcoes);

	//Recupera o ponteiro para a interface de formato do texto.
	Resultado = RecuperarPonteiroCaren(Param_TextLayout, &pDwriterTextLayout);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_DefaultFillBrush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pPointOrigem = Util.ConverterD2D1_POINT_2FManagedToUnmanaged(Param_Origem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->DrawTextLayout(*pPointOrigem, pDwriterTextLayout, pBrush, DrawTextOptions);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pPointOrigem);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Termina as operações de desenho no alvo de renderização e indica o estado de erro atual e as tags associadas. 
/// </summary>
/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
CarenResult CarenD2D1DeviceContext5::EndDraw(
	[Out] UInt64% Param_Out_Tag1,
	[Out] UInt64% Param_Out_Tag2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 OutTag1 = 0;
	UINT64 OutTag2 = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->EndDraw(&OutTag1, &OutTag2);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os valores nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da elipse especificada.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillEllipse) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Ellipse">A posição e o raio, em pixels independentes do dispositivo, da elipse para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior da elipse.</param>
CarenResult CarenD2D1DeviceContext5::FillEllipse(
	CA_D2D1_ELLIPSE^ Param_Ellipse,
	ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ELLIPSE* pEllipse = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pEllipse = Util.ConverterD2D1_ELLIPSEManagedToUnmanaged(Param_Ellipse);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillEllipse(pEllipse, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pEllipse);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da geometria especificada.
/// Se o parâmetro (Param_OpacityBrush) não for NULO, o valor alfa de cada pixel da opacidade mapeadaBrush é usado para determinar a opacidade resultante de cada pixel correspondente da geometria. 
/// Apenas o valor alfa de cada cor no Brush é usado para este processamento; todas as outras informações de cores são ignoradas.
/// O valor alfa especificado pelo Brush é multiplicado pelo valor alfa da geometria após a geometria ter sido pintada pelo Brush.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillGeometry) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Geometria">A geometria para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar o interior da geometria.</param>
/// <param name="Param_OpacityBrush">A máscara de opacidade para aplicar à geometria, ou NULO para nenhuma máscara de opacidade. Se uma máscara de opacidade (o parâmetro Param_OpacityBrush) for especificada, 
/// o (Param_Brush) deve ser um ICarenD2D1BitmapBrush que tem seus modos x e y-extend definidos para D2D1_EXTEND_MODE_CLAMP.</param>
CarenResult CarenD2D1DeviceContext5::FillGeometry(
	ICarenD2D1Geometry^ Param_Geometria,
	ICarenD2D1Brush^ Param_Brush,
	ICarenD2D1Brush^ Param_OpacityBrush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Geometry* pGeometry = NULL;
	ID2D1Brush* pBrush = NULL;
	ID2D1Brush* pOpacityBrush = NULL; //Pode ser NULO.

	//Recupera o ponteiro para a interface de Geometria.
	Resultado = RecuperarPonteiroCaren(Param_Geometria, &pGeometry);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Verifica se forneceu o Brush de opacidade
	if (ObjetoGerenciadoValido(Param_OpacityBrush))
	{
		//Recupera o ponteiro para a interface do Brush de opacidade.
		RecuperarPonteiroCaren(Param_OpacityBrush, &pOpacityBrush);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillGeometry(pGeometry, pBrush, pOpacityBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior da malha especificada.
/// O modo antialias atual do alvo de renderização deve ser D2D1_ANTIALIAS_MODE_ALIASED quando FillMesh é chamado. Para alterar o modo antialias do alvo de renderização, use o método SetAntialiasMode.
/// FillMesh não espera uma ordem de enrolamento específica para os triângulos no ID2D1Mesh; tanto no sentido horário quanto no sentido anti-horário funcionará.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillMesh) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Mesh">A malha para pintar.</param>
/// <param name="Param_Brush">O pincel(Brush) para pintar a malha.</param>
CarenResult CarenD2D1DeviceContext5::FillMesh(
	ICarenD2D1Mesh^ Param_Mesh,
	ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Mesh* pMesh = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Mesh
	Resultado = RecuperarPonteiroCaren(Param_Mesh, &pMesh);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillMesh(pMesh, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Aplica a máscara de opacidade descrita pelo bitmap especificado em um pincel e usa esse pincel para pintar uma região do alvo de renderização.
/// Para que este método funcione corretamente, o alvo de renderização deve estar usando o modo D2D1_ANTIALIAS_MODE_ALIASED antialiasing. Você pode definir o modo antialiasing chamando o método 
/// ICarenD2D1RenderTarget::SetAntialiasMode método.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillOpacityMask) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_OpacityMask">A máscara de opacidade para aplicar no pincel. O valor alfa de cada pixel na região especificado pelo (Param_RetanguloOrigem) é multiplicado com o valor alfa do 
/// Brush após o pincel(Brush) ter sido mapeado para a área definida pelo (Param_RetanguloDestino).</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar a região do alvo de render especificado pelo (Param_RetanguloDestino).</param>
/// <param name="Param_Content">O tipo de conteúdo que a máscara de opacidade contém. O valor é usado para determinar o espaço de cor no qual a máscara de opacidade é misturada.
/// A partir do Windows 8, o D2D1_OPACITY_MASK_CONTENT não é necessário. Consulte o método ICarenD2D1DeviceContext::FillOpacityMask, que não tem parâmetro D2D1_OPACITY_MASK_CONTENT.</param>
/// <param name="Param_RetanguloDestino">A região do alvo de renderização para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_RetanguloOrigem">A região do bitmap para usar como máscara de opacidade, em pixels independentes de dispositivos.</param>
CarenResult CarenD2D1DeviceContext5::FillOpacityMask(
	ICarenD2D1Bitmap^ Param_OpacityMask,
	ICarenD2D1Brush^ Param_Brush,
	CA_D2D1_OPACITY_MASK_CONTENT Param_Content,
	CA_D2D1_RECT_F^ Param_RetanguloDestino,
	CA_D2D1_RECT_F^ Param_RetanguloOrigem)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Bitmap* pOpacityMaskBitmap = NULL;
	ID2D1Brush* pBrush = NULL;
	D2D1_OPACITY_MASK_CONTENT OpacityMask = static_cast<D2D1_OPACITY_MASK_CONTENT>(Param_Content);
	D2D1_RECT_F* pRectDestinoF = NULL;
	D2D1_RECT_F* pRectOrigemF = NULL;

	//Recupera o ponteiro para a interface do Opacity Mask
	Resultado = RecuperarPonteiroCaren(Param_OpacityMask, &pOpacityMaskBitmap);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte as estruturas.
	pRectDestinoF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloDestino);
	pRectOrigemF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_RetanguloOrigem);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillOpacityMask(pOpacityMaskBitmap, pBrush, OpacityMask, pRectDestinoF, pRectOrigemF);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para as estruturas.
	DeletarEstruturaSafe(&pRectDestinoF);
	DeletarEstruturaSafe(&pRectOrigemF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior do retângulo especificado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">A dimensão do retângulo para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo.</param>
CarenResult CarenD2D1DeviceContext5::FillRectangle(
	CA_D2D1_RECT_F^ Param_Rect,
	ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pRectF = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_Rect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillRectangle(pRectF, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Pinta o interior do retângulo arredondado especificado.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como FillRoundedRectangle) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_Rect">As dimensões do retângulo arredondado para pintar, em pixels independentes do dispositivo.</param>
/// <param name="Param_Brush">O pincel(Brush) usado para pintar o interior do retângulo arredondado.</param>
CarenResult CarenD2D1DeviceContext5::FillRoundedRectangle(
	CA_D2D1_ROUNDED_RECT^ Param_Rect,
	ICarenD2D1Brush^ Param_Brush)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ROUNDED_RECT* pRoundedRectF = NULL;
	ID2D1Brush* pBrush = NULL;

	//Recupera o ponteiro para a interface do Brush
	Resultado = RecuperarPonteiroCaren(Param_Brush, &pBrush);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura.
	pRoundedRectF = Util.ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(Param_Rect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FillRoundedRectangle(pRoundedRectF, pBrush);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRoundedRectF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Executa todos os comandos de desenho pendentes.
/// Este comando não libera o contexto do dispositivo Direct3D que está associado ao alvo de renderização.
/// Chamar este método redefine o estado de erro do alvo de renderização.
/// Se o método for bem sucedido, ele retorna SS_OK. Caso contrário, ele retorna um código de erro HRESULT e define Tag1 e Tag2 para as tags que estavam ativas quando o erro ocorreu. Se não ocorreu nenhum erro, 
/// este método define o estado de Tags de erro (0,0).
/// </summary>
/// <param name="Param_Out_Tag1">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
/// <param name="Param_Out_Tag2">Quando este método retorna, contém a tag para operações de desenho que causaram erros ou 0 se não houver erros.</param>
CarenResult CarenD2D1DeviceContext5::Flush(
	[Out] UInt64% Param_Out_Tag1,
	[Out] UInt64% Param_Out_Tag2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	UINT64 OutTag1 = 0;
	UINT64 OutTag2 = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->Flush(&OutTag1, &OutTag2);

	//Processa o resultado da chamada.
	Resultado.ProcessarCodigoOperacao(Hr);

	//Verifica se obteve sucesso na operação.
	if (!Sucesso(static_cast<HRESULT>(Resultado.HResult)))
	{
		//Falhou ao realizar a operação.

		//Sai do método
		Sair;
	}

	//Define os valores nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera o modo antialiasing atual para operações de desenho sem texto. 
/// </summary>
/// <param name="Param_Out_AntialiasMode">Retorna o modo antialiasing atual para operações de desenho sem texto.</param>
void CarenD2D1DeviceContext5::GetAntialiasMode([Out] CA_D2D1_ANTIALIAS_MODE% Param_Out_AntialiasMode)
{
	//Variaveis a serem utilizadas.
	D2D1_ANTIALIAS_MODE OutAliasMode;

	//Chama o método para realizar a operação.
	OutAliasMode = PonteiroTrabalho->GetAntialiasMode();

	//Define no parametro de saida.
	Param_Out_AntialiasMode = static_cast<CA_D2D1_ANTIALIAS_MODE>(OutAliasMode);
}

/// <summary>
/// Retorne os pontos do alvo de renderização por polegada (DPI). 
/// </summary>
/// <param name="Param_Out_DpiX">Retorna o DPI horizontal do alvo de renderização.</param>
/// <param name="Param_Out_DpiY">Retorna o DPI vertical do alvo de renderização. </param>
void CarenD2D1DeviceContext5::GetDpi(
	[Out] float% Param_Out_DpiX,
	[Out] float% Param_Out_DpiY)
{
	//Variaveis a serem utilizadas.
	FLOAT OutDpiX;
	FLOAT OutDpiY;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDpi(&OutDpiX, &OutDpiY);

	//Define nos parametros de saida.
	Param_Out_DpiX = OutDpiX;
	Param_Out_DpiY = OutDpiY;
}

/// <summary>
/// Obtém o tamanho máximo, em unidades dependentes de dispositivos (pixels), de qualquer dimensão de bitmap suportada pelo alvo de renderização.
/// Este método retorna o tamanho máximo da textura do dispositivo Direct3D.
/// O renderizador de software e os dispositivos WARP retornam o valor de 16 megapixels (16* 1024 * 1024). Você pode criar uma textura Direct2D que é deste tamanho, mas não uma textura Direct3D que 
/// é deste tamanho.
/// </summary>
/// <param name="Param_Out_MaximumSize">Retorna o tamanho máximo, em pixels, de qualquer dimensão de bitmap suportada pelo alvo de renderização.</param>
void CarenD2D1DeviceContext5::GetMaximumBitmapSize([Out] UInt32% Param_Out_MaximumSize)
{
	//Chama o método para realizar a operação.
	Param_Out_MaximumSize = PonteiroTrabalho->GetMaximumBitmapSize();
}

/// <summary>
/// Recupera o formato de pixel e o modo alfa do alvo de renderização. 
/// </summary>
/// <param name="Param_Out_PixelFormat">Retorna o formato pixel e o modo alfa do alvo de renderização.</param>
void CarenD2D1DeviceContext5::GetPixelFormat([Out] CA_D2D1_PIXEL_FORMAT^% Param_Out_PixelFormat)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_PIXEL_FORMAT OutPixelFormat;

	//Chama o método para realizar a operação.
	OutPixelFormat = PonteiroTrabalho->GetPixelFormat();

	//Converte e define no parametro de saida.
	Param_Out_PixelFormat = Util.ConverterD2D1_PIXEL_FORMATUnmanagedToManaged(&OutPixelFormat);
}

/// <summary>
/// Retorna o tamanho do alvo de renderização em pixels do dispositivo. 
/// </summary>
/// <param name="Param_Out_PixelSize">Retorna tamanho do alvo de renderização em pixels do dispositivo.</param>
void CarenD2D1DeviceContext5::GetPixelSize([Out] CA_D2D1_SIZE_U^% Param_Out_PixelSize)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_U OutSizeU;

	//Chama o método para realizar a operação.
	OutSizeU = PonteiroTrabalho->GetPixelSize();

	//Converte e define no parametro de saida.
	Param_Out_PixelSize = Util.ConverterD2D1_SIZE_UUnmanagedToManaged(&OutSizeU);
}

/// <summary>
/// Retorna o tamanho do alvo de renderização em pixels independentes do dispositivo.
/// </summary>
/// <param name="Param_Out_Size">Retorna tamanho atual do alvo de renderização em pixels independentes do dispositivo.</param>
void CarenD2D1DeviceContext5::GetSize([Out] CA_D2D1_SIZE_F^% Param_Out_Size)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_SIZE_F OutSizeF;

	//Chama o método para realizar a operação.
	OutSizeF = PonteiroTrabalho->GetSize();

	//Converte e define no parametro de saida.
	Param_Out_Size = Util.ConverterD2D1_SIZE_FUnmanagedToManaged(&OutSizeF);
}

/// <summary>
/// Obtém o rótulo(Tags) para operações de desenho subsequentes. 
/// </summary>
/// <param name="Param_Out_Tag1">Retorna o primeiro rótulo para operações de desenho subsequentes.</param>
/// <param name="Param_Out_Tag2">Retorna o segundo rótulo para operações de desenho subsequentes.</param>
void CarenD2D1DeviceContext5::GetTags(
	[Out] UInt64% Param_Out_Tag1,
	[Out] UInt64% Param_Out_Tag2)
{
	//Variaveis a serem utilizadas.
	UINT64 OutTag1;
	UINT64 OutTag2;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTags(&OutTag1, &OutTag2);

	//Define nos parametros de saida.
	Param_Out_Tag1 = OutTag1;
	Param_Out_Tag2 = OutTag2;
}

/// <summary>
/// Obtém o modo antialiasing atual para operações de desenho de texto e glifo(Glyph). 
/// </summary>
/// <param name="Param_Out_TextAntialiasMode">Retorna o modo antialiasing atual para operações de desenho de texto e glifo(Glyph).</param>
void CarenD2D1DeviceContext5::GetTextAntialiasMode([Out] CA_D2D1_TEXT_ANTIALIAS_MODE% Param_Out_TextAntialiasMode)
{
	//Variaveis a serem utilizadas.
	D2D1_TEXT_ANTIALIAS_MODE OutTextAliasMode;

	//Chama o método para realizar a operação.
	OutTextAliasMode = PonteiroTrabalho->GetTextAntialiasMode();

	//Converte e define no parametro de saida.
	Param_Out_TextAntialiasMode = static_cast<CA_D2D1_TEXT_ANTIALIAS_MODE>(OutTextAliasMode);
}

/// <summary>
/// Recupera as opções de renderização de texto atual do alvo. 
/// </summary>
/// <param name="Param_Out_TextRenderingParams">Retorna a interface (IDWriteRenderingParams) que contém um ponteiro para as opções de renderização de texto atuais do destino. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1DeviceContext5::GetTextRenderingParams(ICaren^ Param_Out_TextRenderingParams)
{
	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pDWriteRendParams = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTextRenderingParams(&pDWriteRendParams);

	//Define na interface de destino no parametro.
	Param_Out_TextRenderingParams->AdicionarPonteiro(pDWriteRendParams);
}

/// <summary>
/// Obtém a transformação atual do alvo render. 
/// </summary>
/// <param name="Param_Out_Transform">Retorna a transformação atual do alvo de renderização.</param>
void CarenD2D1DeviceContext5::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F OutMatrix = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTransform(&OutMatrix);

	//Converte e define no parametro de saida.
	Param_Out_Transform = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutMatrix);
}

/// <summary>
/// Indica se o alvo de renderização suporta as propriedades especificadas.
/// Este método não avalia as configurações de DPI especificadas pelo parâmetro (Param_ProppriedadesRenderTarget).
/// </summary>
/// <param name="Param_ProppriedadesRenderTarget">As propriedades de destino de renderização para testar.</param>
/// <param name="Param_Out_Suporta">Retorna um valor Booleano TRUE se as propriedades de destino de renderização especificadas forem suportadas por este alvo de renderização; caso contrário, FALSO.</param>
void CarenD2D1DeviceContext5::IsSupported(
	CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_ProppriedadesRenderTarget,
	[Out] Boolean% Param_Out_Suporta)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDER_TARGET_PROPERTIES* pRenderTargetProps = NULL;
	BOOL IsSuported = FALSE;

	//Converte a estrutura.
	pRenderTargetProps = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_ProppriedadesRenderTarget);

	//Chama o método para realizar a operação.
	IsSuported = PonteiroTrabalho->IsSupported(pRenderTargetProps);

	//Define no parametro de saida.
	Param_Out_Suporta = IsSuported ? true : false;

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pRenderTargetProps);
}

/// <summary>
/// Remove o último clipe alinhado ao eixo do alvo de renderização. Depois que este método é chamado, o clipe não é mais aplicado às operações de desenho subsequentes.
/// PopAxisAlignedClip deve ser chamado uma vez para cada chamada para PushAxisAlignedClip.
/// Um par PushAxisAlignedClip/PopAxisAlignedClip pode ocorrer ao redor ou dentro de um par PushLayer/PopLayer, mas pode não se sobrepor. Por exemplo, uma sequência PushAxisAlignedClip, PushLayer, PopLayer, 
/// PopAxisAlignedClip é válida, mas uma sequência PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer não é.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
void CarenD2D1DeviceContext5::PopAxisAlignedClip()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->PopAxisAlignedClip();
}

/// <summary>
/// Interrompe o redirecionamento das operações de desenho para a camada especificada pela última chamada do PushLayer.
/// Um PopLayer deve corresponder a uma chamada pushlayer anterior.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PopLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
void CarenD2D1DeviceContext5::PopLayer()
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->PopLayer();
}

/// <summary>
/// Especifica um retângulo ao qual todas as operações de desenho subsequentes são cortadas.
/// O PushAxisAlignedClip e o PopAxisAlignedClip devem coincidir. Caso contrário, o estado de erro está definido. Para que o alvo de renderização continue recebendo novos comandos, você pode chamar 
/// Flush para limpar o erro.
/// Um par PushAxisAlignedClip e PopAxisAlignedClip pode ocorrer em torno ou dentro de um PushLayer e PopLayer, mas não pode se sobrepor. Por exemplo, a sequência de PushAxisAlignedClip, PushLayer, 
/// PopLayer, PopAxisAlignedClip é válida, mas a sequência de PushAxisAlignedClip, PushLayer, PopAxisAlignedClip, PopLayer é inválida.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushAxisAlignedClip) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_ClipRect">O tamanho e a posição da área de recorte, em pixels independentes do dispositivo.</param>
/// <param name="Param_AntialiasMode">O modo antialiasing que é usado para desenhar as bordas das retagens de clipe que têm limites de subpixel, e para misturar o clipe com o conteúdo da cena. A mistura 
/// é realizada uma vez quando o método PopAxisAlignedClip é chamado, e não se aplica a cada primitivo dentro da camada.</param>
void CarenD2D1DeviceContext5::PushAxisAlignedClip(
	CA_D2D1_RECT_F^ Param_ClipRect,
	CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pClipRect = NULL;
	D2D1_ANTIALIAS_MODE AliasMode = static_cast<D2D1_ANTIALIAS_MODE>(Param_AntialiasMode);

	//Converte a estrutura.
	pClipRect = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_ClipRect);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PushAxisAlignedClip(pClipRect, AliasMode);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pClipRect);
}

/// <summary>
/// Adicione a camada especificada ao destino renderização para que ela receba todas as operações de desenho subsequentes até que o PopLayer seja chamado. 
/// O método PushLayer permite que um chamador comece a redirecionar a renderização para uma camada. Todas as operações de renderização são válidas em uma camada. A localização da camada é afetada 
/// pela transformação mundial definida na meta de renderização.
/// Cada PushLayer deve ter uma chamada PopLayer correspondente. Se houver mais chamadas do PopLayer do que chamadas PushLayer, o alvo de renderização será colocado em um estado de erro. Se flush 
/// for chamado antes de todas as camadas pendentes serem estouradas, o alvo de renderização será colocado em um estado de erro e um erro será retornado. O estado de erro pode ser liberado por uma chamada para EndDraw.
/// Este método não retorna um código de erro se falhar. Para determinar se uma operação de desenho (como PushLayer) falhou, verifique o resultado retornado pelo ICarenD2D1RenderTarget::EndDraw
/// ou ICarenD2D1RenderTarget::Flush.
/// </summary>
/// <param name="Param_ParametrosLayer">Os limites de conteúdo, máscara geométrica, opacidade, máscara de opções de opções de opções antialiasing para a camada.</param>
/// <param name="Param_Layer">A camada que recebe operações de desenho subsequentes. Começando pelo Windows 8, este parâmetro é opcional. Se uma camada não for especificada, o Direct2D gerencia 
/// automaticamente o recurso de camada.</param>
void CarenD2D1DeviceContext5::PushLayer(
	CA_D2D1_LAYER_PARAMETERS^ Param_ParametrosLayer,
	ICarenD2D1Layer^ Param_Layer)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_LAYER_PARAMETERS* pLayerParams = NULL;
	ID2D1Layer* pLayer = NULL; //Pode ser NULO.

	//Converte a estrutura.
	pLayerParams = Util.ConverterD2D1_LAYER_PARAMETERSManagedToUnmanaged(Param_ParametrosLayer);

	//Verifica se forneceu a camada
	if (ObjetoGerenciadoValido(Param_Layer))
	{
		//Recupera o ponteiro para a interface da Layer
		RecuperarPonteiroCaren(Param_Layer, &pLayer);
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->PushLayer(pLayerParams, pLayer);

	//Libera a memória para a estrutura.
	DeletarEstruturaSafe(&pLayerParams);
}

/// <summary>
/// Define o estado de desenho do alvo de renderização ao do ID2D1DrawingStateBlock especificado.
/// </summary>
/// <param name="Param_DrawingStateBlock">O novo estado de desenho do alvo render.</param>
CarenResult CarenD2D1DeviceContext5::RestoreDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock* pStateBlock = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_DrawingStateBlock, &pStateBlock);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->RestoreDrawingState(pStateBlock);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Salva o estado de desenho atual para o ID2D1DrawingStateBlock especificado. 
/// </summary>
/// <param name="Param_DrawingStateBlock">Retorna uma interface para o estado de desenho atual do alvo de renderização. Este parâmetro deve ser inicializado antes de passá-lo para o método.</param>
CarenResult CarenD2D1DeviceContext5::SaveDrawingState(ICarenD2D1DrawingStateBlock^ Param_DrawingStateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock* pStateBlock = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_DrawingStateBlock, &pStateBlock);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SaveDrawingState(pStateBlock);

	//Define sucesso
	Resultado.AdicionarCodigo(ResultCode::SS_OK, true);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o modo de antialiasing do alvo de renderização. O modo antialiasing aplica-se a todas as operações de desenho subsequentes, excluindo as operações de desenho de texto e glifo(Glyph). 
/// Para especificar o modo antialiasing para operações de texto e glifos(Glyph), use o método SetTextAntialiasMode.
/// </summary>
/// <param name="Param_AntialiasMode">O modo antialiasing para futuras operações de desenho.</param>
void CarenD2D1DeviceContext5::SetAntialiasMode(CA_D2D1_ANTIALIAS_MODE Param_AntialiasMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetAntialiasMode(static_cast<D2D1_ANTIALIAS_MODE>(Param_AntialiasMode));
}

/// <summary>
/// Define os pontos por polegada (DPI) do alvo de renderização.
/// Este método especifica o mapeamento do espaço pixel para o espaço independente do dispositivo para o alvo de renderização. Se tanto o DpiX quanto o DpiY forem 0, o DPI do sistema de leitura 
/// de fábrica será escolhido. Se um parâmetro for zero e o outro não especificado, o DPI não será alterado.
/// Para ICarenD2D1HwndRenderTarget, o DPI é padrão para o DPI mais recentemente do sistema de leitura de fábrica. O valor padrão para todas as outras metas de renderização é de 96 DPI.
/// </summary>
/// <param name="Param_DpiX">Um valor maior ou igual a zero que especifica o DPI horizontal do alvo de renderização.</param>
/// <param name="Param_DpiY">Um valor maior ou igual a zero que especifica o DPI vertical do alvo de renderização.</param>
void CarenD2D1DeviceContext5::SetDpi(
	float Param_DpiX,
	float Param_DpiY)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetDpi(Param_DpiX, Param_DpiY);
}

/// <summary>
/// Especifica um rótulo(Tag) para operações de desenho subsequentes.
/// As etiquetas(Tags) especificadas por este método são impressas por mensagens de erro depuração. Se nenhuma tag for definida, o valor padrão de cada tag é 0.
/// </summary>
/// <param name="Param_Tag1">Um rótulo para aplicar às operações de desenho subsequentes.</param>
/// <param name="Param_Tag2">Um rótulo para aplicar às operações de desenho subsequentes.</param>
void CarenD2D1DeviceContext5::SetTags(
	UInt64 Param_Tag1,
	UInt64 Param_Tag2)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTags(Param_Tag1, Param_Tag2);
}

/// <summary>
/// Especifica o modo antialiasing a ser usado para operações subsequentes de desenho de texto e glifo(Glyph). 
/// </summary>
/// <param name="Param_TextAntialiasMode">O modo antialiasing para usar para operações subsequentes de desenho de texto e glifo(Glyph).</param>
void CarenD2D1DeviceContext5::SetTextAntialiasMode(CA_D2D1_TEXT_ANTIALIAS_MODE Param_TextAntialiasMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTextAntialiasMode(static_cast<D2D1_TEXT_ANTIALIAS_MODE>(Param_TextAntialiasMode));
}

/// <summary>
/// Especifica as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho de texto e glifo(Glyph).
/// Se as configurações especificadas por textRenderingParams forem incompatíveis com o modo antialiasing de texto do alvo de renderização (especificado por SetTextAntialiasMode), as operações 
/// subsequentes de desenho de texto e glifo(Glyph) falharão e colocarão o alvo de renderização em um estado de erro.
/// </summary>
/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) para as opções de renderização de texto a serem aplicadas a todas as operações subsequentes de desenho 
/// de texto e glifoGlyph); NULO para limpar as opções atuais de renderização de texto.</param>
CarenResult CarenD2D1DeviceContext5::SetTextRenderingParams(ICaren^ Param_TextRenderingParams)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	IDWriteRenderingParams* pDwriteParams = NULL;

	//Recupera o ponteiro para a interface da StateBlock
	Resultado = RecuperarPonteiroCaren(Param_TextRenderingParams, &pDwriteParams);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTextRenderingParams(pDwriteParams);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Aplica a transformação especificada ao alvo de renderização, substituindo a transformação existente. Todas as operações subsequentes de desenho ocorrem no espaço transformado. 
/// </summary>
/// <param name="Param_Transform">A transformação para aplicar ao alvo de renderização.</param>
void CarenD2D1DeviceContext5::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pMatrix = NULL;

	//Converte a estrutura.
	pMatrix = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTransform(pMatrix);

	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pMatrix);
}





// Métodos da interface (ICarenD2D1Resource)

/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void  CarenD2D1DeviceContext5::GetFactory(ICaren^ Param_Out_Factory)
{
	//Chama o método na classe de funções compartilhadas do D2D1.
	Shared_D2D1Resource::GetFactory(PonteiroTrabalho,
		Param_Out_Factory
	);
}