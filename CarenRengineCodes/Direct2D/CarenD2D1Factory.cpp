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
#include "CarenD2D1Factory.h"


//Destruidor.
CarenD2D1Factory::~CarenD2D1Factory()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1Factory::CarenD2D1Factory()
{
	//INICIALIZA SEM NENHUM PONTEIRO VINCULADO.
}
CarenD2D1Factory::CarenD2D1Factory(CA_D2D1_FACTORY_TYPE Param_FactoryType, String^ Param_RIID, CA_D2D1_FACTORY_OPTIONS^ Param_FactoryOptions)
{
	//Variavel que vai conter o resultado COM.
	HRESULT Hr = E_FAIL;

	//Resultados de Caren.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis utilizadas.
	Utilidades Util;
	GUID vi_RIID = GUID_NULL;
	D2D1_FACTORY_OPTIONS* vi_pFactoryOptions = Nulo;
	ID2D1Factory* vi_pOutFactory = Nulo;

	//Cria o RIID para a interface solicitada.
	vi_RIID = Util.CreateGuidFromString(Param_RIID);

	//Converte a estrutura gerenciada para a nativa.
	vi_pFactoryOptions = Util.ConverterD2D1_FACTORY_OPTIONSManagedToUnmanaged(Param_FactoryOptions);

	//Chama o método para criar a interface.
	Hr = D2D1CreateFactory(
		static_cast<D2D1_FACTORY_TYPE>(Param_FactoryType), 
		vi_RIID, 
		const_cast<D2D1_FACTORY_OPTIONS*>(vi_pFactoryOptions), 
		reinterpret_cast<void**>(&vi_pOutFactory));

	//Verifica se não ocorreu erro no processo.
	if (!Sucesso(Hr))
	{
		//Libera a memória utilizada pela estrutura.
		DeletarEstruturaSafe(&vi_pFactoryOptions);

		//Chama uma exceção para informar o error.
		throw gcnew Exception(String::Concat("Ocorreu uma falha ao criar a interface. Mensagem associado ao ERROR -> ", Util.TranslateCodeResult(Hr)));
	}

	//Define a interface criada no ponteiro de trabalho
	PonteiroTrabalho = vi_pOutFactory;

	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&vi_pFactoryOptions);
}

// Métodos da interface ICaren


/// <summary>
/// (QueryInterface) - Consulta o objeto COM atual para um ponteiro para uma de suas interfaces; identificando a interface por uma 
/// referência ao identificador de interface (IID). Se o objeto COM implementar a interface, o método retorna um ponteiro para essa
/// interface depois de adicionar uma nova referência(AddRef).
/// </summary>
/// <param name="Param_Guid">O IID(Identificador de Interface) ou GUID para a interface desejada.</param>
/// <param name="Param_InterfaceSolicitada">A interface que vai receber o ponteiro nativo. O usuário deve inicializar a interface antes de chamar o método. Libere a interface quando não for mais usá-la.</param>
CarenResult CarenD2D1Factory::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Factory::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Factory*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Factory**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Factory::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Factory*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Factory**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Factory::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Factory::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1Factory::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1Factory::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Factory::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_AdicionarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Factory::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1Factory::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Factory();
}



// Métodos da interface proprietária(ICarenD2D1Factory)


/// <summary>
/// Cria um alvo de renderização que atrai o contexto do dispositivo GDI (Windows Graphics Device Interface, interface do dispositivo gráfico do Windows).
/// </summary>
/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware. Para habilitar o objetivo 
/// de renderização do contexto do dispositivo (DC) para funcionar com o GDI, defina o formato DXGI para DXGI_FORMAT_B8G8R8A8_UNORM e o modo alfa para D2D1_ALPHA_MODE_PREMULTIPLIED ou D2D1_ALPHA_MODE_IGNORE</param>
/// <param name="Param_Out_DcRenderTarget">Retorna uma interface(ICarenD2D1DCRenderTarget) que contém um ponteiro para o novo alvo de renderização DC.</param>
CarenResult CarenD2D1Factory::CreateDCRenderTarget(
CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
[Out] ICarenD2D1DCRenderTarget^% Param_Out_DcRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDER_TARGET_PROPERTIES* pPropsRenderTarget = NULL;
	ID2D1DCRenderTarget* pOutDcRenderTarget = NULL;

	//Converte a estrutura
	pPropsRenderTarget = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_PropsRenderTarget);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDCRenderTarget(pPropsRenderTarget, &pOutDcRenderTarget);

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
	Param_Out_DcRenderTarget = gcnew CarenD2D1DCRenderTarget();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDcRenderTarget, Param_Out_DcRenderTarget);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pPropsRenderTarget);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
/// </summary>
/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
/// <param name="Param_TextRenderingParams">Uma interface(IDWriteRenderingParams) que contém parâmetros de texto opcionais que indicam como o texto deve ser renderizado.</param>
/// <param name="Param_Out_StateBlock">>Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
CarenResult CarenD2D1Factory::CreateDrawingStateBlock(
	CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
	ICaren^ Param_TextRenderingParams,
	[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION* pDescDrawingState = NULL;
	IDWriteRenderingParams* pWriteRendering = NULL; //Pode ser NULO.
	ID2D1DrawingStateBlock* pOutDrawingBlock = NULL;

	//Converte a estrutura.
	pDescDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTIONManagedToUnmanaged(Param_DescDrawingState);

	//Recupera o ponteiro para a interface.
	Resultado = RecuperarPonteiroCaren(Param_TextRenderingParams, &pWriteRendering);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDrawingStateBlock(pDescDrawingState, pWriteRendering, &pOutDrawingBlock);

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
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pDescDrawingState);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
/// </summary>
/// <param name="Param_DescDrawingState">Uma estrutura que contém informações antialias, transformações e tags.</param>
/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
CarenResult CarenD2D1Factory::CreateDrawingStateBlock(
CA_D2D1_DRAWING_STATE_DESCRIPTION^ Param_DescDrawingState,
[Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION* pDescDrawingState = NULL;
	ID2D1DrawingStateBlock* pOutDrawingBlock = NULL;

	//Converte a estrutura.
	pDescDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTIONManagedToUnmanaged(Param_DescDrawingState);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDrawingStateBlock(*pDescDrawingState, &pOutDrawingBlock);

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
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pDescDrawingState);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1DrawingStateBlock que pode ser usado com os métodos SaveDrawingState e RestoreDrawingState de um alvo de renderização.
/// </summary>
/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock) que contém um ponteiro para o novo bloco de estado de desenhado criado.</param>
CarenResult CarenD2D1Factory::CreateDrawingStateBlock([Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock* pOutDrawingBlock = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDrawingStateBlock(&pOutDrawingBlock);

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
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização que atrai uma superfície DXGI (DirectX Graphics Infrastructure, infraestrutura gráfica do DirectX).
/// </summary>
/// <param name="Param_DxgiSurface">Uma interface(ICarenDXGISurface) para o qual o alvo de renderização irá desenhar.</param>
/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
/// <param name="Param_Out_RenderTarget">Retorna uma interface(ICarenD2D1RenderTarget) que contém um ponteiro para o objeto criado.</param>
CarenResult CarenD2D1Factory::CreateDxgiSurfaceRenderTarget(
[Out] ICarenDXGISurface^% Param_DxgiSurface,
CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IDXGISurface* pDxgiSurface = NULL;
	D2D1_RENDER_TARGET_PROPERTIES* pPropsRenderTarget = NULL;
	ID2D1RenderTarget* pOutRenderTarget = NULL;

	//Recupera o ponteiro para a superfice DXGI
	Resultado = RecuperarPonteiroCaren(Param_DxgiSurface, &pDxgiSurface);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura
	pPropsRenderTarget = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_PropsRenderTarget);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDxgiSurfaceRenderTarget(pDxgiSurface, pPropsRenderTarget, &pOutRenderTarget);

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
	Param_Out_RenderTarget = gcnew CarenD2D1DCRenderTarget();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutRenderTarget, Param_Out_RenderTarget);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pPropsRenderTarget);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma ICarenD2D1EllipseGeometry.
/// </summary>
/// <param name="Param_Ellipse">Um valor que descreve o ponto central, raio x e raio y da geometria da elipse.</param>
/// <param name="Param_Out_EllipseGeometry">Retorna uma interface(ICarenD2D1EllipseGeometry) que contém um ponteiro para a nova geometria de elipse criada.</param>
CarenResult CarenD2D1Factory::CreateEllipseGeometry(
CA_D2D1_ELLIPSE^ Param_Ellipse,
[Out] ICarenD2D1EllipseGeometry^% Param_Out_EllipseGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ELLIPSE* pEllipse = NULL;
	ID2D1EllipseGeometry* pOutEllipsedGeometry = NULL;

	//Converte a estrutura
	pEllipse = Util.ConverterD2D1_ELLIPSEManagedToUnmanaged(Param_Ellipse);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateEllipseGeometry(pEllipse, &pOutEllipsedGeometry);

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
	Param_Out_EllipseGeometry = gcnew CarenD2D1EllipseGeometry();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutEllipsedGeometry, Param_Out_EllipseGeometry);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pEllipse);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1GeometryGroup, que é um objeto que contém outras geometrias.
/// Grupos de geometria são uma maneira conveniente de agrupar várias geometrias simultaneamente para que todas as figuras de várias geometrias distintas sejam concatenadas em uma.
/// </summary>
/// <param name="Param_FiilMode">Um valor que especifica a regra que uma forma composta usa para determinar se um determinado ponto faz parte da geometria.</param>
/// <param name="Param_Geometrias">Uma matriz contendo os objetos de geometria para adicionar ao grupo de geometria. O número de elementos nesta matriz é indicado pelo parâmetro (Param_QuantidadeGeometrias).</param>
/// <param name="Param_QuantidadeGeometrias">O número de elementos em (Param_Geometrias).</param>
/// <param name="Param_Out_GeometryGroup">Retorna uma interface(ICarenD2D1GeometryGroup) que contém um ponteiro para o novo grupo de geometria.</param>
CarenResult CarenD2D1Factory::CreateGeometryGroup(
CA_D2D1_FILL_MODE Param_FiilMode,
cli::array<ICarenD2D1Geometry^>^ Param_Geometrias,
UInt32 Param_QuantidadeGeometrias,
[Out] ICarenD2D1GeometryGroup^% Param_Out_GeometryGroup)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_FILL_MODE FillMode = static_cast<D2D1_FILL_MODE>(Param_FiilMode);
	ID2D1Geometry** pArrayGeometrias = CriarMatrizPonteiros<ID2D1Geometry>(Param_QuantidadeGeometrias);
	ID2D1GeometryGroup* pOutGeometryGroup = NULL;

	//Copia os ponteiros nativos das interfaces gerenciadas e define na matriz nativa.
	Util.CopiarPonteirosGerenciado_ToNativo(pArrayGeometrias, Param_Geometrias, Param_QuantidadeGeometrias);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGeometryGroup(FillMode, pArrayGeometrias, Param_QuantidadeGeometrias, &pOutGeometryGroup);

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
	Param_Out_GeometryGroup = gcnew CarenD2D1GeometryGroup();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutGeometryGroup, Param_Out_GeometryGroup);

Done:;
	//Libera a memória para a matriz de ponteiros.
	DeletarMatrizPonteirosSafe(&pArrayGeometrias);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1HwndRenderTarget, um alvo de renderização que renderiza uma janela.
/// Quando você cria um alvo de renderização e a aceleração de hardware está disponível, você aloca recursos na GPU do computador. Ao criar um alvo de renderização uma vez e retê-lo o maior tempo possível, você ganha benefícios 
/// de desempenho. Seu aplicativo deve criar metas de renderização uma vez e segurá-los durante a vida útil do aplicativo ou até que o erro D2DERR_RECREATE_TARGET seja recebido. Quando você recebe esse erro, você precisa recriar o 
/// destino render (e quaisquer recursos que ele criou).
/// </summary>
/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
/// <param name="Param_PropsHwndRenderTarget">A handle da janela, tamanho inicial (em pixels) e as opções atuais.</param>
/// <param name="Param_Out_HwndRenderTarget">Retorna uma interface(ICarenD2D1HwndRenderTarget) que contém um ponteiro para o objeto criado.</param>
CarenResult CarenD2D1Factory::CreateHwndRenderTarget(
CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
CA_D2D1_HWND_RENDER_TARGET_PROPERTIES^ Param_PropsHwndRenderTarget,
[Out] ICarenD2D1HwndRenderTarget^% Param_Out_HwndRenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RENDER_TARGET_PROPERTIES* pPropsRenderTarget = NULL;
	D2D1_HWND_RENDER_TARGET_PROPERTIES* pPropsHwndRenderTarget = NULL;
	ID2D1HwndRenderTarget* pOutHwndRenderTarget = NULL;

	//Converte as estruturas
	pPropsRenderTarget = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_PropsRenderTarget);
	pPropsHwndRenderTarget = Util.ConverterD2D1_HWND_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_PropsHwndRenderTarget);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateHwndRenderTarget(pPropsRenderTarget, pPropsHwndRenderTarget, &pOutHwndRenderTarget);

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
	Param_Out_HwndRenderTarget = gcnew CarenD2D1HwndRenderTarget();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutHwndRenderTarget, Param_Out_HwndRenderTarget);

Done:;
	//Libera a memória para as estruturas
	DeletarEstruturaSafe(&pPropsHwndRenderTarget);
	DeletarEstruturaSafe(&pPropsRenderTarget);
	
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma ICarenD2D1PathGeometry vazio.
/// </summary>
/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry) que contém um ponteiro para o Path Geometry criado pelo método.</param>
CarenResult CarenD2D1Factory::CreatePathGeometry(
[Out] ICarenD2D1PathGeometry^% Param_Out_PathGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1PathGeometry* pOutPathGeometry = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePathGeometry(&pOutPathGeometry);

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
	Param_Out_PathGeometry = gcnew CarenD2D1PathGeometry();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutPathGeometry, Param_Out_PathGeometry);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma ICarenD2D1RectangleGeometry.
/// </summary>
/// <param name="Param_Retangulo">As coordenadas da geometria do retângulo.</param>
/// <param name="Param_Out_RectangleGeometry">Retorna uma interface(ICarenD2D1RectangleGeometry) que contém um ponteiro para a geometria retângulo criada.</param>
CarenResult CarenD2D1Factory::CreateRectangleGeometry(
CA_D2D1_RECT_F^ Param_Retangulo,
[Out] ICarenD2D1RectangleGeometry^% Param_Out_RectangleGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F* pRetanguloF = NULL;
	ID2D1RectangleGeometry* pOutRectangleGeometry = NULL;

	//Converte a estrutura
	pRetanguloF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_Retangulo);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRectangleGeometry(pRetanguloF, &pOutRectangleGeometry);

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
	Param_Out_RectangleGeometry = gcnew CarenD2D1RectangleGeometry();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutRectangleGeometry, Param_Out_RectangleGeometry);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pRetanguloF);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria uma ID2D1RoundedRectangleGeometry.
/// </summary>
/// <param name="Param_RoundedRectangle">As coordenadas e os raios de canto da geometria do retângulo arredondado.</param>
/// <param name="Param_Out_RoundedRectangleGeometry">Retorna uma interface(ICarenD2D1RoundedRectangleGeometry) que contém um ponteiro  para a geometria do retângulo arredondado criada.</param>
CarenResult CarenD2D1Factory::CreateRoundedRectangleGeometry(
CA_D2D1_ROUNDED_RECT^ Param_RoundedRectangle,
[Out] ICarenD2D1RoundedRectangleGeometry^% Param_Out_RoundedRectangleGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_ROUNDED_RECT* pRoundedRetangulo = NULL;
	ID2D1RoundedRectangleGeometry* pOutRoundedRect = NULL;

	//Converte a estrutura
	pRoundedRetangulo = Util.ConverterD2D1_ROUNDED_RECTManagedToUnmanaged(Param_RoundedRectangle);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateRoundedRectangleGeometry(pRoundedRetangulo, &pOutRoundedRect);

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
	Param_Out_RoundedRectangleGeometry = gcnew CarenD2D1RoundedRectangleGeometry();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutRoundedRect, Param_Out_RoundedRectangleGeometry);

Done:;
	//Libera a memória para a estrutura
	DeletarEstruturaSafe(&pRoundedRetangulo);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um ICarenD2D1StrokeStyle que descreve tampa inicial, padrão de traço e outras características de um traçado.
/// </summary>
/// <param name="Param_PropsStrokeStyle">Uma estrutura que descreve o limite de linha do traçado, o deslocamento do traço e outros detalhes de um traçado.</param>
/// <param name="Param_Dashes">Uma matriz cujos elementos são definidos para o comprimento de cada traço e espaço no padrão de traço.O primeiro elemento define o comprimento de um traço, o segundo elemento define o comprimento 
/// de um espaço, o terceiro elemento define o comprimento de um traço e assim por diante.O comprimento de cada traço e espaço no padrão de traço é o produto do valor do elemento na matriz e a largura do traço.</param>
/// <param name="Param_QuantidadeDashes">A quantidade de elementos na matriz (Param_Dashes).</param>
/// <param name="Param_Out_StrokeStyle">Retorna uma interface(ICarenD2D1StrokeStyle) que contém um ponteiro para o estilo de traçado criado.</param>
CarenResult CarenD2D1Factory::CreateStrokeStyle(
CA_D2D1_STROKE_STYLE_PROPERTIES^ Param_PropsStrokeStyle,
cli::array<float>^ Param_Dashes,
UInt32 Param_QuantidadeDashes,
[Out] ICarenD2D1StrokeStyle^% Param_Out_StrokeStyle)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_STROKE_STYLE_PROPERTIES* pPropsStrokeStyle = NULL;
	float* pArrayDashes = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_QuantidadeDashes));
	ID2D1StrokeStyle* pOutStrokeStyle = NULL;

	//Converte a estrutura
	pPropsStrokeStyle = Util.ConverterD2D1_STROKE_STYLE_PROPERTIESManagedToUnmanaged(Param_PropsStrokeStyle);

	//Copia o array gerenciado
	Util.CopiarItensTo_ArrayNativo(&pArrayDashes, Param_Dashes, Param_QuantidadeDashes);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateStrokeStyle(pPropsStrokeStyle, pArrayDashes, Param_QuantidadeDashes, &pOutStrokeStyle);

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
	Param_Out_StrokeStyle = gcnew CarenD2D1StrokeStyle();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutStrokeStyle, Param_Out_StrokeStyle);

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&pPropsStrokeStyle);

	//Libera a memória utilizada pela matriz
	DeletarMatrizUnidimensionalSafe(&pArrayDashes);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Transforma a geometria especificada e armazena o resultado como um objeto ICarenD2D1TransformedGeometry.
/// </summary>
/// <param name="Param_GeometriaOrigem">A geometria para transformar.</param>
/// <param name="Param_Transform">A transformação para aplicar.</param>
/// <param name="Param_Out_TransformedGeometry">Retorna uma interface(ICarenD2D1TransformedGeometry) que contém um ponteiro para o novo objeto de geometria transformado. A geometria transformada armazena o resultado da 
/// transformação da (Param_GeometriaOrigem) por (Param_Transform).</param>
CarenResult CarenD2D1Factory::CreateTransformedGeometry(
ICarenD2D1Geometry^ Param_GeometriaOrigem,
CA_D2D1_MATRIX_3X2_F^ Param_Transform,
[Out] ICarenD2D1TransformedGeometry^% Param_Out_TransformedGeometry)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	ID2D1Geometry* pGeometriaOrigem = NULL;
	D2D1_MATRIX_3X2_F* pTransform = NULL;
	ID2D1TransformedGeometry* pOutTransformedGeometry = NULL;

	//Recupera o ponteiro para a interface da geometria
	Resultado = RecuperarPonteiroCaren(Param_GeometriaOrigem, &pGeometriaOrigem);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura
	pTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateTransformedGeometry(pGeometriaOrigem, pTransform, &pOutTransformedGeometry);

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
	Param_Out_TransformedGeometry = gcnew CarenD2D1TransformedGeometry();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutTransformedGeometry, Param_Out_TransformedGeometry);

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&pTransform);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um alvo de renderização que renderiza um bitmap do WIC(Microsoft Windows Imaging Component).
/// Você deve usar D2D1_FEATURE_LEVEL_DEFAULT para o membro minLevel do parâmetro (CA_D2D1_RENDER_TARGET_PROPERTIES) com este método.
/// </summary>
/// <param name="Param_WicBitmapTarget">O bitmap que recebe a saída de renderização do alvo renderizador.</param>
/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware.</param>
/// <param name="Param_Out_RenderTarget">Retorna uma interface(ICarenD2D1RenderTarget) que contém um ponteiro para o objeto criado.</param>
CarenResult CarenD2D1Factory::CreateWicBitmapRenderTarget(
ICaren^ Param_WicBitmapTarget,
CA_D2D1_RENDER_TARGET_PROPERTIES^ Param_PropsRenderTarget,
[Out] ICarenD2D1RenderTarget^% Param_Out_RenderTarget)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICBitmap* pBitmapTarget = NULL;
	D2D1_RENDER_TARGET_PROPERTIES* pPropsRenderTarget = NULL;
	ID2D1RenderTarget* pOutRenderTarget = NULL;
	
	//Recupera o ponteiro para o bitmap wic.
	Resultado = RecuperarPonteiroCaren(Param_WicBitmapTarget, &pBitmapTarget);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Converte a estrutura
	pPropsRenderTarget = Util.ConverterD2D1_RENDER_TARGET_PROPERTIESManagedToUnmanaged(Param_PropsRenderTarget);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateWicBitmapRenderTarget(pBitmapTarget, pPropsRenderTarget, &pOutRenderTarget);

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
	Param_Out_RenderTarget = gcnew CarenD2D1RenderTarget();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutRenderTarget, Param_Out_RenderTarget);

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&pPropsRenderTarget);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera os pontos de desktop atuais por polegada (DPI). Para atualizar esse valor, ligue para o ReloadSystemMetrics.
/// Use este método para obter o DPI do sistema ao definir valores de pixels físicos, como quando você especifica o tamanho de uma janela.
/// </summary>
/// <param name="Param_Out_DpiX">Retorna o DPI Horizontal da área de trabalho.</param>
/// <param name="Param_Out_DpiY">Retorna o DPI Vertical da área de trabalho.</param>
void CarenD2D1Factory::GetDesktopDpi(
[Out] float% Param_Out_DpiX,
[Out] float% Param_Out_DpiY)
{
	//Variaveis a serem utilizadas.
	float OutDpiX = 0;
	float OutDpiY = 0;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetDesktopDpi(&OutDpiX, &OutDpiY);
}

/// <summary>
/// Força o Factory a atualizar quaisquer padrões do sistema que possa ter mudado desde a criação do Factory.
/// Você deve chamar este método antes de chamar o método GetDesktopDpi, para garantir que o DPI do sistema esteja atualizado.
/// </summary>
CarenResult CarenD2D1Factory::ReloadSystemMetrics()
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->ReloadSystemMetrics();

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