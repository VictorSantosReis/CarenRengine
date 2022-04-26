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
#include "CarenD2D1Device2.h"

//Destruidor.
CarenD2D1Device2::~CarenD2D1Device2()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtores
CarenD2D1Device2::CarenD2D1Device2()
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
CarenResult CarenD2D1Device2::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1Device2::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1Device2*>(Param_PonteiroNativo.ToPointer());

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
CarenResult CarenD2D1Device2::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
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
	PonteiroTrabalho = reinterpret_cast<ID2D1Device2*>(Param_PonteiroNativo);

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
CarenResult CarenD2D1Device2::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1Device2::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
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
CarenResult CarenD2D1Device2::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
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
CarenResult CarenD2D1Device2::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1Device2::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1Device2::AdicionarReferencia()
{
	//Adiciona uma referência ao ponteiro
	PonteiroTrabalho->AddRef();
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1Device2::LiberarReferencia()
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
void CarenD2D1Device2::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1Device2();
}



// Métodos da interface proprietária(ICarenD2D1Device2)


/// <summary>
/// Cria um novo ICarenD2D1DeviceContext2 a partir de um dispositivo Direct2D.
/// </summary>
/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
/// <param name="Param_Out_ContextoDispositivo2">Retorna uma interface(ICarenD2D1DeviceContext2) que contém um ponteiro para o novo contexto do dispositivo.</param>
CarenResult CarenD2D1Device2::CreateDeviceContext(
CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
[Out] ICarenD2D1DeviceContext2^% Param_Out_ContextoDispositivo2)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DeviceContext2* pOutContexto = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeviceContext(static_cast<D2D1_DEVICE_CONTEXT_OPTIONS>(Param_Opcoes), &pOutContexto);

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
	Param_Out_ContextoDispositivo2 = gcnew CarenD2D1DeviceContext2();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutContexto, Param_Out_ContextoDispositivo2);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Limpa todos os contextos do dispositivo que fazem referência a um determinado bitmap.
/// </summary>
/// <param name="Param_Bitmap">O bitmap, criado neste dispositivo, para o qual todos os contextos do dispositivo de referência serão limpos.</param>
void CarenD2D1Device2::FlushDeviceContexts(ICarenD2D1Bitmap^ Param_Bitmap)
{
	//Variaveis a serem utilizadas.
	ID2D1Bitmap* pBitmap = NULL;

	//Recupera o ponteiro para a interface do bitmap.
	RecuperarPonteiroCaren(Param_Bitmap, &pBitmap);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->FlushDeviceContexts(pBitmap);
}

/// <summary>
/// Retorna o dispositivo DXGI associado a este dispositivo Direct2D.
/// </summary>
/// <param name="Param_Out_DxgiDevice">Retorna uma interface(ICarenDXGIDevice) que contém um ponteiro para o dispositivo DXGI associado a este dispositivo Direct2D.</param>
CarenResult CarenD2D1Device2::GetDxgiDevice([Out] ICarenDXGIDevice^% Param_Out_DxgiDevice)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	IDXGIDevice* pOutDxgi = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->GetDxgiDevice(&pOutDxgi);

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
	Param_Out_DxgiDevice = gcnew CarenDXGIDevice();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutDxgi, Param_Out_DxgiDevice);

Done:;
	//Retorna o resultado.
	return Resultado;
}




// Métodos da interface (ICarenD2D1Device1)

/// <summary>
/// Cria um novo ICarenD2D1DeviceContext1 a partir de um dispositivo Direct2D.
/// </summary>
/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
/// <param name="Param_Out_ContextoDispositivo1">Retorna uma interface(ICarenD2D1DeviceContext1) que contém um ponteiro para o novo contexto do dispositivo.</param>
CarenResult CarenD2D1Device2::CreateDeviceContext(CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes, [Out] ICarenD2D1DeviceContext1^% Param_Out_ContextoDispositivo1)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DeviceContext1* pOutContexto = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeviceContext(static_cast<D2D1_DEVICE_CONTEXT_OPTIONS>(Param_Opcoes), &pOutContexto);

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
	Param_Out_ContextoDispositivo1 = gcnew CarenD2D1DeviceContext1();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutContexto, Param_Out_ContextoDispositivo1);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Recupera a prioridade de renderização atual do dispositivo.
/// </summary>
/// <param name="Param_Out_Prioridade">Retorna a prioridade de renderização atual do dispositivo.</param>
void CarenD2D1Device2::GetRenderingPriority(
	[Out] CA_D2D1_RENDERING_PRIORITY% Param_Out_Prioridade)
{
	//Variaveis a serem utilizadas.
	D2D1_RENDERING_PRIORITY OutRenderingPriority;

	//Chama o método para realizar a operação.
	OutRenderingPriority = PonteiroTrabalho->GetRenderingPriority();

	//Converte e define no parametro de saida.
	Param_Out_Prioridade = static_cast<CA_D2D1_RENDERING_PRIORITY>(OutRenderingPriority);
}

/// <summary>
/// Define a prioridade das operações de renderização Direct2D realizadas em qualquer contexto de dispositivo associado ao dispositivo.
/// </summary>
/// <param name="Param_Prioridade">A prioridade de renderização desejada para o dispositivo e contextos associados.</param>
void CarenD2D1Device2::SetRenderingPriority(CA_D2D1_RENDERING_PRIORITY Param_Prioridade)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetRenderingPriority(static_cast<D2D1_RENDERING_PRIORITY>(Param_Prioridade));
}




// Métodos da interface (ICarenD2D1Device)


/// <summary>
/// Libera todos os recursos de renderização utilizados pelo Direct2D.
/// </summary>
/// <param name="Param_Miliseconds">Descarta apenas recursos que não foram usados por mais do que o tempo especificado em milissegundos. O padrão é de 0 milissegundos.</param>
void CarenD2D1Device2::ClearResources(UInt32 Param_Miliseconds)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->ClearResources(Param_Miliseconds);
}

/// <summary>
/// Cria um novo contexto de dispositivo a partir de um dispositivo Direct2D.
/// O novo contexto do dispositivo não terá um bitmap de destino selecionado. O chamador deve criar e selecionar um bitmap como a superfície alvo do contexto.
/// </summary>
/// <param name="Param_Opcoes">As opções a serem aplicadas ao contexto do dispositivo criado.</param>
/// <param name="Param_Out_ContextoDispositivo">Retorna uma interface(ICarenD2D1DeviceContext) que contém um ponteiro para o novo contexto do dispositivo. </param>
CarenResult CarenD2D1Device2::CreateDeviceContext(
	CA_D2D1_DEVICE_CONTEXT_OPTIONS Param_Opcoes,
	[Out] ICarenD2D1DeviceContext^% Param_Out_ContextoDispositivo)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	ID2D1DeviceContext* pOutContexto = NULL;

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreateDeviceContext(static_cast<D2D1_DEVICE_CONTEXT_OPTIONS>(Param_Opcoes), &pOutContexto);

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
	Param_Out_ContextoDispositivo = gcnew CarenD2D1DeviceContext();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutContexto, Param_Out_ContextoDispositivo);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Cria um objeto ICarenD2D1PrintControl que converte primitivos Direct2D armazenados no ICarenD2D1CommandList em uma representação de página fixa. O subsistema de impressão então consome os primitivos.
/// </summary>
/// <param name="Param_WicImagingFactory">Uma interface(ICarenWICImagingFactory) que representa a fábrica de imagens WIC.</param>
/// <param name="Param_PrintDocumentPackage">Uma interface(IPrintDocumentPackageTarget)[NAO IMPLEMENTADA POR ESSA API] que representa o alvo de trabalho de impressão.</param>
/// <param name="Param_PropsControlPrint">As opções a serem aplicadas ao controle de impressão.</param>
/// <param name="Param_Out_PrintControl">Retorna uma interface(ICarenD2D1PrintControl) que contém um ponteiro para o objeto D2D1PrintControl.</param>
CarenResult CarenD2D1Device2::CreatePrintControl(
	ICaren^ Param_WicImagingFactory,
	ICaren^ Param_PrintDocumentPackage,
	CA_D2D1_PRINT_CONTROL_PROPERTIES^ Param_PropsControlPrint,
	[Out] ICarenD2D1PrintControl^% Param_Out_PrintControl)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Resultado COM.
	ResultadoCOM Hr = E_FAIL;

	//Variaveis a serem utilizadas.
	Utilidades Util;
	IWICImagingFactory* pWicImagingFactory = NULL;
	IPrintDocumentPackageTarget* pPrintDocumentTarget = NULL;
	D2D1_PRINT_CONTROL_PROPERTIES* pPrintControlProps = NULL;
	ID2D1PrintControl* pOutPrintControl = NULL;

	//Recupera o ponteiro para a fabrica do WIC.
	Resultado = RecuperarPonteiroCaren(Param_WicImagingFactory, &pWicImagingFactory);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Recupera o ponteiro para o documento de destino de impressão.
	Resultado = RecuperarPonteiroCaren(Param_PrintDocumentPackage, &pPrintDocumentTarget);

	//Sai do método em caso de erro
	SairOnError(Resultado);

	//Converte a estrutura
	pPrintControlProps = Util.ConverterD2D1_PRINT_CONTROL_PROPERTIESManagedToUnmanaged(Param_PropsControlPrint);

	//Chama o método para realizar a operação.
	Hr = PonteiroTrabalho->CreatePrintControl(pWicImagingFactory, pPrintDocumentTarget, pPrintControlProps, &pOutPrintControl);

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
	Param_Out_PrintControl = gcnew CarenD2D1PrintControl();

	//Define o ponteiro na interface.
	Resultado = DefinirPonteiroInterface(pOutPrintControl, Param_Out_PrintControl);

Done:;
	//Libera a memória utilizada pela estrutura
	DeletarEstruturaSafe(&pPrintControlProps);

	//Retorna o resultado.
	return Resultado;
}


/// <summary>
/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
/// </summary>
/// <param name="Param_Out_MaxSizeMemory">Retorna a quantidade máxima de memória de textura em bytes.</param>
void CarenD2D1Device2::GetMaximumTextureMemory([Out] UInt64% Param_Out_MaxSizeMemory)
{
	//Chama o método para realizar a operação.
	Param_Out_MaxSizeMemory = PonteiroTrabalho->GetMaximumTextureMemory();
}

/// <summary>
/// Define a quantidade máxima de memória de textura que o Direct2D acumula antes de purgar os caches de imagem e alocações de textura em cache.
///  O Direct2D pode exceder a memória de textura máxima que você define com este método para um único quadro, se necessário, para renderizar o quadro.
/// </summary>
/// <param name="Param_MaxSizeMemory">A nova quantidade máxima de memória em bytes para a textura.</param>
void CarenD2D1Device2::SetMaximumTextureMemory(UInt64 Param_MaxSizeMemory)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetMaximumTextureMemory(Param_MaxSizeMemory);
}




// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1Device2::GetFactory(ICaren^ Param_Out_Factory)
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