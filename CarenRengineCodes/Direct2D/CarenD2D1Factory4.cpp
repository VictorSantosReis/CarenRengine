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
#include "CarenD2D1Factory4.h"

//Destruidor.
CarenD2D1Factory4::~CarenD2D1Factory4()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1Factory4::CarenD2D1Factory4()
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
CarenResult CarenD2D1Factory4::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Factory4::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Factory4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Factory4**>(p)));
}
/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Factory4::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1Factory4*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1Factory4**>(p)));
}
/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Factory4::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1Factory4::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1Factory4::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1Factory4::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1Factory4::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Factory4::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Factory4::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1Factory4::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Factory4();
}



// Métodos da interface proprietária(ICarenD2D1Factory4)


/// <summary>
/// Cria um objeto ICarenD2D1Device3.
/// </summary>
/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device3.</param>
/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device3) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>
CarenResult CarenD2D1Factory4::CreateDevice(
ICarenDXGIDevice^ Param_DxgiDevice,
[Out] ICarenD2D1Device3^% Param_Out_D2DDispositivo
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIDevice* pDxgiDevice = NULL;
	ID2D1Device3* pOutD2DDevice = NULL;

	//Recupera o ponteiro para o dispositivo dxgi
	Resultado = RecuperarPonteiroCaren(Param_DxgiDevice, &pDxgiDevice);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDevice(pDxgiDevice, &pOutD2DDevice);

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

	//Cria a interface que será retornada.
	Param_Out_D2DDispositivo = gcnew CarenD2D1Device3();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutD2DDevice, Param_Out_D2DDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Factory3)


/// <summary>
/// Cria um objeto ICarenD2D1Device2.
/// </summary>
/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device2.</param>
/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device2) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>
CarenResult CarenD2D1Factory4::CreateDevice(
	ICarenDXGIDevice^ Param_DxgiDevice,
	[Out] ICarenD2D1Device2^% Param_Out_D2DDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIDevice* pDxgiDevice = NULL;
	ID2D1Device2* pOutD2DDevice = NULL;

	//Recupera o ponteiro para o dispositivo dxgi
	Resultado = RecuperarPonteiroCaren(Param_DxgiDevice, &pDxgiDevice);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDevice(pDxgiDevice, &pOutD2DDevice);

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

	//Cria a interface que será retornada.
	Param_Out_D2DDispositivo = gcnew CarenD2D1Device2();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutD2DDevice, Param_Out_D2DDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Factory2)


/// <summary>
/// Cria um objeto ICarenD2D1Device1.
/// O dispositivo Direct2D define um domínio de recursos no qual um conjunto de objetos Direct2D e contextos de dispositivo Direct2D podem ser usados em conjunto. Cada chamada para CreateDevice retorna um objeto ICarenD2D1Device1 exclusivo, mesmo que você passe o mesmo ICarenDXGIDevice várias vezes.
/// </summary>
/// <param name="Param_DxgiDevice">O objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device1.</param>
/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device1) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>
CarenResult CarenD2D1Factory4::CreateDevice(
	ICarenDXGIDevice^ Param_DxgiDevice,
	[Out] ICarenD2D1Device1^% Param_Out_D2DDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIDevice* pDxgiDevice = NULL;
	ID2D1Device1* pOutD2DDevice = NULL;

	//Recupera o ponteiro para o dispositivo dxgi
	Resultado = RecuperarPonteiroCaren(Param_DxgiDevice, &pDxgiDevice);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDevice(pDxgiDevice, &pOutD2DDevice);

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

	//Cria a interface que será retornada.
	Param_Out_D2DDispositivo = gcnew CarenD2D1Device1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutD2DDevice, Param_Out_D2DDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Factory1)


/// <summary>
/// Cria um objeto ICarenD2D1Device.
/// O dispositivo Direct2D define um domínio de recursos no qual um conjunto de objetos Direct2D e contextos de dispositivo Direct2D podem ser usados em conjunto. Cada chamada para CreateDevice retorna um objeto ICarenD2D1Device exclusivo, mesmo que você passe o mesmo ICarenDXGIDevice várias vezes.
/// </summary>
/// <param name="Param_DxgiDevice">Um objeto ICarenDXGIDevice usado ao criar o ICarenD2D1Device.</param>
/// <param name="Param_Out_D2DDispositivo">Retorna uma interface(ICarenD2D1Device) que contém um ponteiro para o novo dispositivo Direct2D criado.</param>
CarenResult CarenD2D1Factory4::CreateDevice(
	ICarenDXGIDevice^ Param_DxgiDevice,
	[Out] ICarenD2D1Device^% Param_Out_D2DDispositivo
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIDevice* pDxgiDevice = NULL;
	ID2D1Device* pOutD2DDevice = NULL;

	//Recupera o ponteiro para o dispositivo dxgi
	Resultado = RecuperarPonteiroCaren(Param_DxgiDevice, &pDxgiDevice);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDevice(pDxgiDevice, &pOutD2DDevice);

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

	//Cria a interface que será retornada.
	Param_Out_D2DDispositivo = gcnew CarenD2D1Device();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutD2DDevice, Param_Out_D2DDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
/// </summary>
/// <param name="Param_DescDrawingState">A estrutura de descrição do estado de desenho.</param>
/// <param name="Param_TextRenderingParams">Uma ponteiro para a interface(IDWriteRenderingParams)[SDK PENDENTE] que contém os parametros de renderização do DirectWrite.</param>
/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock(
	CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescDrawingState,
	ICaren^ Param_TextRenderingParams,
	[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION1* pDescDrawingState = NULL;
	IDWriteRenderingParams* pWriteRendering = NULL;
	ID2D1DrawingStateBlock1* pOutDrawingBlock = NULL;

	//Converte a estrutura.
	pDescDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTION1ManagedToUnmanaged(Param_DescDrawingState);

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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pDescDrawingState);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
/// </summary>
/// <param name="Param_DescDrawingState">A estrutura de descrição do estado de desenho.</param>
/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock(
	CA_D2D1_DRAWING_STATE_DESCRIPTION1^ Param_DescDrawingState,
	[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_DRAWING_STATE_DESCRIPTION1* pDescDrawingState = NULL;
	ID2D1DrawingStateBlock1* pOutDrawingBlock = NULL;

	//Converte a estrutura.
	pDescDrawingState = Util.ConverterD2D1_DRAWING_STATE_DESCRIPTION1ManagedToUnmanaged(Param_DescDrawingState);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDrawingStateBlock(*pDescDrawingState, &pOutDrawingBlock);

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

	//Cria a interface que será retornada.
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;
	//Libera a memória utilizada pela estrutura.
	DeletarEstruturaSafe(&pDescDrawingState);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo bloco de estado de desenho, isso pode ser usado nas operações subsequentes SaveDrawingState e RestoreDrawingState no alvo de renderização.
/// </summary>
/// <param name="Param_Out_StateBlock">Retorna uma interface(ICarenD2D1DrawingStateBlock1) que contém um ponteiro para o novo bloco de estado de desenho.</param>
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock(
	[Out] ICarenD2D1DrawingStateBlock1^% Param_Out_StateBlock)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DrawingStateBlock1* pOutDrawingBlock = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDrawingStateBlock(&pOutDrawingBlock);

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

	//Cria a interface que será retornada.
	Param_Out_StateBlock = gcnew CarenD2D1DrawingStateBlock1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutDrawingBlock, Param_Out_StateBlock);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um novo objeto ID2D1GdiMetafile que você pode usar para reproduzir conteúdo metafilado.
/// </summary>
/// <param name="Param_MetaFileStream">Um objeto de fluxo que tem os dados do metafile.</param>
/// <param name="Param_Out_GdiMetafile">Retorna uma interface(ID2D1GdiMetafile)[NAO IMPLEMENTADA PELA DLL] que contém um ponteiro para o novo objeto de metafile GDI recém-criado. O usuário deve inicializar a interface antes de chamar este método.</param>
CarenResult CarenD2D1Factory4::CreateGdiMetafile(
	ICarenStream^ Param_MetaFileStream,
	ICaren^ Param_Out_GdiMetafile
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IStream* pFluxoMetafile = NULL;
	ID2D1GdiMetafile* pOutGdiMetaFile = NULL;

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_MetaFileStream, &pFluxoMetafile);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateGdiMetafile(pFluxoMetafile, &pOutGdiMetaFile);

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
	Resultado = DefinirPonteiroInterface(pOutGdiMetaFile, Param_Out_GdiMetafile);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto ICarenD2D1PathGeometry1.
/// </summary>
/// <param name="Param_Out_PathGeometry">Retorna uma interface(ICarenD2D1PathGeometry1) que contém um ponteiro para o nova Path Geometry criada.</param>
CarenResult CarenD2D1Factory4::CreatePathGeometry(
	[Out] ICarenD2D1PathGeometry1^% Param_Out_PathGeometry
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1PathGeometry1* pOutPathGeometry = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePathGeometry(&pOutPathGeometry);

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

	//Cria a interface que será retornada.
	Param_Out_PathGeometry = gcnew CarenD2D1PathGeometry1();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutPathGeometry, Param_Out_PathGeometry);

Done:;

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto ICarenD2D1StrokeStyle1.
/// </summary>
/// <param name="Param_PropsStrokeStyle">As propriedades de estilo de traçado para serem aplicadas.</param>
/// <param name="Param_Dashes">Uma variedade de larguras para os traços e lacunas.</param>
/// <param name="Param_QuantidadeDashes">A quantidade de itens na matriz(Param_Dashes).</param>
/// <param name="Param_Out_StrokeStyle">Retorna uma interface(ICarenD2D1StrokeStyle1) que contém um ponteiro para o novo Stroke Style criado.</param>
CarenResult CarenD2D1Factory4::CreateStrokeStyle(
	CA_D2D1_STROKE_STYLE_PROPERTIES1^ Param_PropsStrokeStyle,
	cli::array<float>^ Param_Dashes,
	UInt32 Param_QuantidadeDashes,
	[Out] ICarenD2D1StrokeStyle1^% Param_Out_StrokeStyle
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_STROKE_STYLE_PROPERTIES1* pPropsStrokeStyle = NULL;
	float* pArrayDashes = CriarMatrizUnidimensional<float>(static_cast<DWORD>(Param_QuantidadeDashes));
	ID2D1StrokeStyle1* pOutStrokeStyle = NULL;

	//Converte a estrutura
	pPropsStrokeStyle = Util.ConverterD2D1_STROKE_STYLE_PROPERTIES1ManagedToUnmanaged(Param_PropsStrokeStyle);

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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

	//Cria a interface que será retornada.
	Param_Out_StrokeStyle = gcnew CarenD2D1StrokeStyle1();

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
/// Recupera as propriedades de um efeito.
/// Este método não pode ser usado para retornar as propriedades para qualquer efeito não visível ao ICarenD2D1DeviceContext::CreateEffect.
/// </summary>
/// <param name="Param_IdEfeito">A ID do efeito para recuperar propriedades de.</param>
/// <param name="Param_Out_Propriedades">Retorna uma interface(ICarenD2D1Properties) que contém um ponteiro para a interface de propriedade que pode ser usado para consultar os metadados do efeito.</param>
CarenResult CarenD2D1Factory4::GetEffectProperties(
	String^ Param_IdEfeito,
	[Out] ICarenD2D1Properties^% Param_Out_Propriedades
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID IdEfeito = GUID_NULL;
	ID2D1Properties* pOutProps = NULL;

	//Cria o id
	IdEfeito = Util.CreateGuidFromString(Param_IdEfeito);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetEffectProperties(IdEfeito, &pOutProps);

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

	//Cria a interface que será retornada.
	Param_Out_Propriedades = gcnew CarenD2D1Properties();

	//Define o ponteiro na interface
	Resultado = DefinirPonteiroInterface(pOutProps, Param_Out_Propriedades);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Retorna as IDs de classe dos efeitos atualmente registrados e efeitos globais nesta Factory.
/// O conjunto de IDs de classe será devolvido atomicamente pela API. O conjunto não será interrompido por outros tópicos que registram ou não registram efeitos.
/// Se os (Param_Out_QuantidadeEfeitosRegistrados) for maior que o (Param_QuantidadeEfeitos), a matriz fornecida ainda será preenchida à capacidade com o conjunto atual de efeitos registrados. Este método retorna os CLSIDs para todos os efeitos globais e todos os efeitos registrados nesta fábrica.
/// </summary>
/// <param name="Param_Out_Efeitos">Retorna uma matriz com os CLSID dos efeitos. NULO se nenhum efeito for recuperado.</param>
/// <param name="Param_QuantidadeEfeitos">A quantidade de itens que a matriz(Param_Out_Efeitos) vai retornar.</param>
/// <param name="Param_Out_QuantidadeEfeitosRetornados">Retorna a quantidade real de efeitos retornados.</param>
/// <param name="Param_Out_QuantidadeEfeitosRegistrados">Retorna a quantidade de efeitos atualmente registrados no sistema.</param>
CarenResult CarenD2D1Factory4::GetRegisteredEffects(
	[Out] cli::array<String^>^% Param_Out_Efeitos,
	UInt32 Param_QuantidadeEfeitos,
	[Out] UInt32% Param_Out_QuantidadeEfeitosRetornados,
	[Out] UInt32% Param_Out_QuantidadeEfeitosRegistrados
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	CLSID* pOutArrayIdEfeitos = CriarMatrizUnidimensional<CLSID>(Param_QuantidadeEfeitos);
	UINT32 OutCountEfeitosRetornados = 0;
	UINT32 OutCountEfeitosRegistrados = 0;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetRegisteredEffects(pOutArrayIdEfeitos, Param_QuantidadeEfeitos, &OutCountEfeitosRetornados, &OutCountEfeitosRegistrados);

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

	//Cria o array que será retornado.
	Param_Out_Efeitos = gcnew cli::array<String^>(Param_QuantidadeEfeitos);

	//Faz um for para criar os guids
	for (UINT32 i = 0; i < Param_QuantidadeEfeitos; i++)
	{
		//Converte o CLSID para String e define no array.
		Param_Out_Efeitos[i] = Util.ConverterGuidToString(pOutArrayIdEfeitos[i]);
	}

	//Define as quantidades registradas e retornadas.
	Param_Out_QuantidadeEfeitosRetornados = OutCountEfeitosRetornados;
	Param_Out_QuantidadeEfeitosRegistrados = OutCountEfeitosRegistrados;

Done:;
	//Libera a memória utilizada pela matriz 
	DeletarMatrizUnidimensionalSafe(&pOutArrayIdEfeitos);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Registra um efeito dentro da instância de fábrica com a propriedade XML especificada como um fluxo.
/// Os efeitos Direct2D devem definir suas propriedades no momento do registro via XML de registro. Um efeito declara várias propriedades necessárias do sistema, e também pode declarar propriedades personalizadas.
/// Além dos efeitos incorporados(built-in effects) registrados globalmente, esta API registra efeitos apenas para esta Factory e interfaces de contexto de dispositivos e dispositivos derivados.
/// </summary>
/// <param name="Param_ClassId">O identificador do efeito a ser registrado.</param>
/// <param name="Param_StreamPropertyXml">Um Stream para a lista das propriedades de efeito, tipos e metadados.</param>
/// <param name="Param_Bindings">Uma variedade de propriedades e métodos. Isso vincula uma propriedade por nome a um método específico implementado pelo autor do efeito para lidar com a propriedade. O nome deve ser encontrado na (Param_StreamPropertyXml)</param>
/// <param name="Param_QuantidadeBindings">O número de Bindings na matriz(Param_Bindings).</param>
/// <param name="Param_CallbackEffectFactory">Um ponteiro para um Factory estatico para criar oefeito correspondente.</param>
CarenResult CarenD2D1Factory4::RegisterEffectFromStream(
	String^ Param_ClassId,
	ICarenStream^ Param_StreamPropertyXml,
	cli::array<CA_D2D1_PROPERTY_BINDING^>^ Param_Bindings,
	UInt32 Param_QuantidadeBindings,
	ICaren^ Param_CallbackEffectFactory
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID ClassId = GUID_NULL;
	IStream* pfluxoPropertyXml = NULL;
	D2D1_PROPERTY_BINDING* pArrayBindings = CriarMatrizEstruturas<D2D1_PROPERTY_BINDING>(Param_QuantidadeBindings);
	D2D1_PROPERTY_BINDING* pBindingAuxiliar = NULL;
	CarenPD2D1_PROPERTY_FUNCTIONS^ PropFuncAuxiliar = nullptr;
	PD2D1_EFFECT_FACTORY* pCallbackEffectFactory = NULL;

	//Cria o guid
	ClassId = Util.CreateGuidFromString(Param_ClassId);

	//Recupera o ponteiro para o fluxo.
	Resultado = RecuperarPonteiroCaren(Param_StreamPropertyXml, &pfluxoPropertyXml);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Recupera o ponteiro para o Callback responsável pela criação do efeito.
	Resultado = RecuperarPonteiroCaren(Param_CallbackEffectFactory, &pCallbackEffectFactory);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Faz um for para converter o array gerenciado para o nativo.
	for (UINT32 i = 0; i < Param_QuantidadeBindings; i++)
	{
		//Obtém a classe que contém as funções.
		PropFuncAuxiliar = safe_cast<CarenPD2D1_PROPERTY_FUNCTIONS^>(Param_Bindings[i]->setFunction_and_getFunction);

		//Converte a estrutura
		pBindingAuxiliar = Util.ConverterD2D1_PROPERTY_BINDINGManagedToUnmanaged(
			Param_Bindings[i],
			PropFuncAuxiliar->RecuperarSetFunction(),
			PropFuncAuxiliar->RecuperarGetFunction());

		//Define na matriz nativa.
		pArrayBindings[i] = *pBindingAuxiliar;

		//Libera a memória utilizada pela estrutura.
		DeletarEstruturaSafe(&pBindingAuxiliar);

		//Limpa
		pBindingAuxiliar = NULL;
		PropFuncAuxiliar = nullptr;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterEffectFromStream(ClassId, pfluxoPropertyXml, pArrayBindings, Param_QuantidadeBindings, const_cast<PD2D1_EFFECT_FACTORY>(*pCallbackEffectFactory));

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
	//Libera a memória utilizada para matriz de estruturas
	DeletarMatrizEstruturasSafe(&pArrayBindings);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Registra um efeito dentro da instância de fábrica com a propriedade XML especificada como uma sequência.
/// Os efeitos Direct2D devem definir suas propriedades no momento do registro via XML de registro. Um efeito declara várias propriedades necessárias do sistema, e também pode declarar propriedades personalizadas.
/// Além dos efeitos incorporados(built-in effects) registrados globalmente, esta API registra efeitos apenas para esta Factory e interfaces de contexto de dispositivos e dispositivos derivados.
/// </summary>
/// <param name="Param_ClassId">O identificador do efeito a ser registrado.</param>
/// <param name="Param_PropertyXml">Uma String para uma lista das propriedades de efeito, tipos e metadados.</param>
/// <param name="Param_Bindings">Uma variedade de propriedades e métodos. Isso vincula uma propriedade por nome a um método específico implementado pelo autor do efeito para lidar com a propriedade. O nome deve ser encontrado na (Param_PropertyXml)</param>
/// <param name="Param_QuantidadeBindings">O número de Bindings na matriz(Param_Bindings).</param>
/// <param name="Param_CallbackEffectFactory">Um ponteiro para um Factory estatico para criar oefeito correspondente.</param>
CarenResult CarenD2D1Factory4::RegisterEffectFromString(
	String^ Param_ClassId,
	String^ Param_PropertyXml,
	cli::array<CA_D2D1_PROPERTY_BINDING^>^ Param_Bindings,
	UInt32 Param_QuantidadeBindings,
	ICaren^ Param_CallbackEffectFactory
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID ClassId = GUID_NULL;
	PWSTR pStringPropertyXml = NULL;
	D2D1_PROPERTY_BINDING* pArrayBindings = CriarMatrizEstruturas<D2D1_PROPERTY_BINDING>(Param_QuantidadeBindings);
	D2D1_PROPERTY_BINDING* pBindingAuxiliar = NULL;
	CarenPD2D1_PROPERTY_FUNCTIONS^ PropFuncAuxiliar = nullptr;
	PD2D1_EFFECT_FACTORY* pCallbackEffectFactory = NULL;

	//Cria o guid
	ClassId = Util.CreateGuidFromString(Param_ClassId);

	//Converte a string.
	pStringPropertyXml = Util.ConverterStringToWCHAR(Param_PropertyXml);

	//Recupera o ponteiro para o Callback responsável pela criação do efeito.
	Resultado = RecuperarPonteiroCaren(Param_CallbackEffectFactory, &pCallbackEffectFactory);

	//Sai do método em caso de erro.
	SairOnError(Resultado);

	//Faz um for para converter o array gerenciado para o nativo.
	for (UINT32 i = 0; i < Param_QuantidadeBindings; i++)
	{
		//Obtém a classe que contém as funções.
		PropFuncAuxiliar = safe_cast<CarenPD2D1_PROPERTY_FUNCTIONS^>(Param_Bindings[i]->setFunction_and_getFunction);

		//Converte a estrutura
		pBindingAuxiliar = Util.ConverterD2D1_PROPERTY_BINDINGManagedToUnmanaged(
			Param_Bindings[i],
			PropFuncAuxiliar->RecuperarSetFunction(),
			PropFuncAuxiliar->RecuperarGetFunction());

		//Define na matriz nativa.
		pArrayBindings[i] = *pBindingAuxiliar;

		//Libera a memória utilizada pela estrutura.
		DeletarEstruturaSafe(&pBindingAuxiliar);

		//Limpa
		pBindingAuxiliar = NULL;
		PropFuncAuxiliar = nullptr;
	}

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->RegisterEffectFromString(ClassId, const_cast<PCWSTR>(pStringPropertyXml), pArrayBindings, Param_QuantidadeBindings, const_cast<PD2D1_EFFECT_FACTORY>(*pCallbackEffectFactory));

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
	//Libera a memória utilizada para matriz de estruturas
	DeletarMatrizEstruturasSafe(&pArrayBindings);

	//Libera a memória para a string.
	DeletarStringAllocatedSafe(&pStringPropertyXml);

	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Desfaz o registro de um efeito dentro da instância da Factory que corresponde ao (Param_ClassId) fornecido.
/// Para que o efeito seja totalmente cancelado, você deve chamar o (UnregisterEffect) do mesmo número de vezes que você registrou o efeito.
/// O método (UnregisterEffect) cancela o registro apenas dos efeitos registrados na mesma Factory. Não pode ser usado para cancelar o registro de um efeito interno.
/// </summary>
/// <param name="Param_ClassId">O identificador do efeito não está registrado.</param>
CarenResult CarenD2D1Factory4::UnregisterEffect(
	String^ Param_ClassId
)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	GUID ClassId = GUID_NULL;

	//Cria o guid
	ClassId = Util.CreateGuidFromString(Param_ClassId);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->UnregisterEffect(ClassId);

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




// Métodos da interface (ICarenD2D1Factory)


/// <summary>
/// Cria um alvo de renderização que atrai o contexto do dispositivo GDI (Windows Graphics Device Interface, interface do dispositivo gráfico do Windows).
/// </summary>
/// <param name="Param_PropsRenderTarget">O modo de renderização, o formato de pixel, as opções de remoção, as informações de DPI e o suporte mínimo directx necessário para renderização de hardware. Para habilitar o objetivo 
/// de renderização do contexto do dispositivo (DC) para funcionar com o GDI, defina o formato DXGI para DXGI_FORMAT_B8G8R8A8_UNORM e o modo alfa para D2D1_ALPHA_MODE_PREMULTIPLIED ou D2D1_ALPHA_MODE_IGNORE</param>
/// <param name="Param_Out_DcRenderTarget">Retorna uma interface(ICarenD2D1DCRenderTarget) que contém um ponteiro para o novo alvo de renderização DC.</param>
CarenResult CarenD2D1Factory4::CreateDCRenderTarget(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateDrawingStateBlock([Out] ICarenD2D1DrawingStateBlock^% Param_Out_StateBlock)
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateDxgiSurfaceRenderTarget(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateEllipseGeometry(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateGeometryGroup(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateHwndRenderTarget(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreatePathGeometry(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateRectangleGeometry(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateRoundedRectangleGeometry(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateStrokeStyle(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateTransformedGeometry(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
CarenResult CarenD2D1Factory4::CreateWicBitmapRenderTarget(
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

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
void CarenD2D1Factory4::GetDesktopDpi(
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
CarenResult CarenD2D1Factory4::ReloadSystemMetrics()
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

		//Define o código na classe.
		Var_Glob_LAST_HRESULT = Hr;

		//Sai do método
		Sair;
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}