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
#include "CarenD2D1ImageBrush.h"

//Destruidor.
CarenD2D1ImageBrush::~CarenD2D1ImageBrush()
{
	//Define que a classe foi descartada
	Prop_DisposedClasse = true;
}
//Construtor.
CarenD2D1ImageBrush::CarenD2D1ImageBrush()
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
CarenResult CarenD2D1ImageBrush::ConsultarInterface(String^ Param_Guid, ICaren^ Param_InterfaceSolicitada)
{
	//Chama o método de QueryInterface na classe base(Caren).
	return Caren::Shared_ConsultarInterface(PonteiroTrabalho, Param_Guid, Param_InterfaceSolicitada);
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (GERENCIADA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ImageBrush::AdicionarPonteiro(IntPtr Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ImageBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ImageBrush**>(p)));
}

/// <summary>
/// Método responsável por adicionar um novo ponteiro nativo a classe atual.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_PonteiroNativo">Variável (NATIVA) para o ponteiro nativo a ser adicionado.</param>
CarenResult CarenD2D1ImageBrush::AdicionarPonteiro(LPVOID Param_PonteiroNativo)
{
	//Fixa o ponteiro.
	cli::pin_ptr<ID2D1ImageBrush*> p = &PonteiroTrabalho;

	//Chama o método de ADICIONAR PONTEIRO na classe base(Caren).
	return Caren::Shared_AdicionarPonteiro(Param_PonteiroNativo, reinterpret_cast<IUnknown**>(static_cast<ID2D1ImageBrush**>(p)));
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (GERENCIADA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ImageBrush::RecuperarPonteiro([Out] IntPtr% Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por recuperar o ponteiro atual da classe. Se o ponteiro não for valido, o método retornar ResultCode::ER_PONTEIRO.
/// Este método não é responsável por adicionar uma nova referência ao objeto COM.
/// </summary>
/// <param name="Param_Out_PonteiroNativo">Variável (NATIVA) que vai receber o ponteiro nativo.</param>
CarenResult CarenD2D1ImageBrush::RecuperarPonteiro(LPVOID* Param_Out_PonteiroNativo)
{
	//Chama o método para recuperar o ponteiro de trabalho da classe atual.
	return Caren::Shared_RecuperarPonteiro(Param_Out_PonteiroNativo, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por retornar a quantidade de referências do objeto COM atual.
/// </summary>
/// <param name="Param_Out_Referencias">Variável que vai receber a quantidade de referências do objeto.</param>
CarenResult CarenD2D1ImageBrush::RecuperarReferencias([Out] UInt64% Param_Out_Referencias)
{
	//Chama o método para recuperar a quantidade de referencias atuais da interface.
	return Caren::Shared_RecuperarReferencias(Param_Out_Referencias, PonteiroTrabalho);
}

/// <summary>
/// Método responsável por indicar se o ponteiro COM atual é válido.
/// </summary>
CarenResult CarenD2D1ImageBrush::StatusPonteiro()
{
	return (ObjetoValido(PonteiroTrabalho) ? CarenResult(ResultCode::SS_OK, true) : CarenResult(ResultCode::ER_E_POINTER, false));
}

/// <summary>
/// Método responsável por retornar a variável que armazena o último código de erro desconhecido ou não documentado gerado pela classe.
/// Esse método não chama o método nativo (GetLastError), apenas retorna o código de erro que foi armazenado na classe.
/// </summary>
Int32 CarenD2D1ImageBrush::ObterCodigoErro()
{
	return Var_Glob_LAST_HRESULT;
}

/// <summary>
/// (AddRef) - Incrementa a contagem de referência para o ponteiro do objeto COM atual. Você deve chamar este método sempre que 
/// você fazer uma cópia de um ponteiro de interface.
/// </summary>
void CarenD2D1ImageBrush::AdicionarReferencia()
{
	//Chama o método para incrementar a quantidade de referencias atuais da interface.
	Caren::Shared_IncrementarReferencia(PonteiroTrabalho);
}

/// <summary>
/// (Release) - 'Decrementa' a contagem de referência do objeto COM atual.
/// </summary>
void CarenD2D1ImageBrush::LiberarReferencia()
{
	//Chama o método para liberar em UM (1) a quantidade de referencias atuais da interface.
	Caren::Shared_LiberarReferencia(PonteiroTrabalho);
}

/// <summary>
/// Método responsável por chamar o finalizador da interface para realizar a limpeza e descarte de dados pendentes.
/// Este método pode ser escrito de forma diferente para cada interface.
/// </summary>
void CarenD2D1ImageBrush::Finalizar()
{
	//////////////////////
	//Código de descarte//
	//////////////////////

	//Informa ao GC que a classe já foi limpa e pode ser descartada.
	GC::SuppressFinalize(this);
	
	//Nula o ponteiro de trabalho da classe.
	PonteiroTrabalho = Nulo;

	//Chama o finalizador da classe
	this->~CarenD2D1ImageBrush();
}



// Métodos da interface proprietária(ICarenD2D1ImageBrush)


/// <summary>
/// Obtém o modo de extensão do pincel de imagem no eixo x. 
/// </summary>
/// <param name="Param_Out_ModeExtendidoX">Retorna o modo extendido no eixo X.</param>
void CarenD2D1ImageBrush::GetExtendModeX([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoX)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = PonteiroTrabalho->GetExtendModeX();

	//Define no parametro de saida do método.
	Param_Out_ModeExtendidoX = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém o modo de extensão do pincel de imagem no eixo y da imagem. 
/// </summary>
/// <param name="Param_Out_ModeExtendidoY">Retorna o modo extendido no eixo Y.</param>
void CarenD2D1ImageBrush::GetExtendModeY([Out] CA_D2D1_EXTEND_MODE% Param_Out_ModeExtendidoY)
{
	//Variaveis a serem utilizadas.
	D2D1_EXTEND_MODE OutExtendMode;

	//Chama o método para realizar a operação.
	OutExtendMode = PonteiroTrabalho->GetExtendModeY();

	//Define no parametro de saida do método.
	Param_Out_ModeExtendidoY = ConverterPara<CA_D2D1_EXTEND_MODE>(OutExtendMode);
}

/// <summary>
/// Obtém a imagem associada ao pincel de imagem. 
/// </summary>
/// <param name="Param_Out_Image">Quando este método retorna, contém o endereço de um ponteiro para a imagem associada a este pincel.</param>
CarenResult CarenD2D1ImageBrush::GetImage([Out] ICarenD2D1Image^% Param_Out_Image)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Image* pD2D1Image = NULL;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetImage(&pD2D1Image);

	//Verifica a se a interface é valida
	if (!ObjetoValido(pD2D1Image))
	{
		//A interface não é valida.

		//Define erro na operação.
		SetCarenErro(Resultado, ResultCode::ER_E_POINTER);

		//Sai do método
		Sair;
	}

	//Cria a interface a ser retornada.
	Param_Out_Image = gcnew CarenD2D1Image();

	//Define o ponteiro na interface.
	Resultado = Param_Out_Image->AdicionarPonteiro(pD2D1Image);

	//Verifica se não houve erro
	if (!CarenSucesso(Resultado)) 
	{
		//Falhou ao definir o ponteiro.

		//Libera a interface.
		pD2D1Image->Release();
		pD2D1Image = NULL;

		//Libera a interface gerenciada.
		Param_Out_Image->Finalizar();
		Param_Out_Image = nullptr;

		//Deixa continuar para retorna o erro.
	}

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Obtém o modo de interpolação do pincel de imagem.
/// </summary>
/// <param name="Param_Out_InterpolatonMode">Retorna o modo de interpolação.</param>
void CarenD2D1ImageBrush::GetInterpolationMode([Out] CA_D2D1_INTERPOLATION_MODE% Param_Out_InterpolatonMode)
{
	//Variaveis a serem utilizadas.
	D2D1_INTERPOLATION_MODE OutInterpolationMode;

	//Chama o método para realizar a operação.
	OutInterpolationMode = PonteiroTrabalho->GetInterpolationMode();

	//Define no parametro de saida do método.
	Param_Out_InterpolatonMode = ConverterPara<CA_D2D1_INTERPOLATION_MODE>(OutInterpolationMode);
}

/// <summary>
/// Obtém o retângulo que será usado como os limites da imagem quando desenhado como um pincel de imagem. 
/// </summary>
/// <param name="Param_Out_RetanguloOrigem">Quando este método retorna, contém a estrutura do retângulo de origem de saída.</param>
void CarenD2D1ImageBrush::GetSourceRectangle([Out] CA_D2D1_RECT_F^% Param_Out_RetanguloOrigem)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F OutSourceRect = { };

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetSourceRectangle(&OutSourceRect);

	//Converte e define no parametro de saida.
	Param_Out_RetanguloOrigem = Util.ConverterD2D1_RECT_FUnmanagedToManaged(&OutSourceRect);
}

/// <summary>
/// Define como o conteúdo dentro do retângulo de origem no Brush de imagem será estendido no eixo X. 
/// </summary>
/// <param name="Param_ModeExtendidoX">O modo de extensão no eixo X da imagem.</param>
void CarenD2D1ImageBrush::SetExtendModeX(CA_D2D1_EXTEND_MODE Param_ModeExtendidoX)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetExtendModeX(ConverterPara<D2D1_EXTEND_MODE>(Param_ModeExtendidoX));
}

/// <summary>
/// Define o modo de extensão no eixo Y. 
/// </summary>
/// <param name="Param_ModeExtendidoY">O modo de extensão no eixo Y da imagem.</param>
void CarenD2D1ImageBrush::SetExtendModeY(CA_D2D1_EXTEND_MODE Param_ModeExtendidoY)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetExtendModeY(ConverterPara<D2D1_EXTEND_MODE>(Param_ModeExtendidoY));
}

/// <summary>
/// Define a imagem associada à escova de imagem fornecida. 
/// </summary>
/// <param name="Param_Image">A imagem a ser associada com o pincel de imagem.</param>
CarenResult CarenD2D1ImageBrush::SetImage(ICarenD2D1Image^ Param_Image)
{
	//Variavel a ser retornada.
	CarenResult Resultado = CarenResult(ResultCode::ER_FAIL, false);

	//Variaveis a serem utilizadas.
	ID2D1Image* pD2D1Image = NULL;

	//Recupera o ponteiro para a imagem.
	Resultado = RecuperarPonteiroCaren(Param_Image, &pD2D1Image);

	//Verifica se obteve com sucesso
	if (!CarenSucesso(Resultado))
	{
		//Falhou ao recuperar o ponteiro.

		//Sai do método
		Sair;
	}

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetImage(pD2D1Image);

	//Define sucesso na operação.
	SetCarenSucesso(Resultado);

Done:;
	//Retorna o resultado.
	return Resultado;
}

/// <summary>
/// Define o modo de interpolação para o pincel de imagem. 
/// </summary>
/// <param name="Param_InterpolationMode">Define como o conteúdo da imagem será interpolado para lidar com a transformação do pincel.</param>
void CarenD2D1ImageBrush::SetInterpolationMode(CA_D2D1_INTERPOLATION_MODE Param_InterpolationMode)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetInterpolationMode(ConverterPara<D2D1_INTERPOLATION_MODE>(Param_InterpolationMode));
}

/// <summary>
/// Define o retângulo de origem na escova de imagem. 
/// </summary>
/// <param name="Param_OrigemRetangulo">O retângulo de origem que define a parte da imagem para ladrilho(Tile).</param>
void CarenD2D1ImageBrush::SetSourceRectangle(CA_D2D1_RECT_F^ Param_OrigemRetangulo)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_RECT_F *pRectF = NULL;

	//Converte a estrutura
	pRectF = Util.ConverterD2D1_RECT_FManagedToUnmanaged(Param_OrigemRetangulo);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetSourceRectangle(pRectF);

	//Libera a memória utilizada
	DeletarEstruturaSafe(&pRectF);
}




// Métodos da interface proprietária(ICarenD2D1Brush)


/// <summary>
/// Obtém o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Out_Opacidade">Retorna um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1ImageBrush::GetOpacity([Out] float% Param_Out_Opacidade)
{
	//Chama o método para realizar a operação e define no parametro de saida.
	Param_Out_Opacidade = PonteiroTrabalho->GetOpacity();
}

/// <summary>
/// A transformação é aplicada a este pincel.
/// </summary>
/// <param name="Param_Out_Matrix">Retorna a transformação aplicada a este pincel.</param>
void CarenD2D1ImageBrush::GetTransform([Out] CA_D2D1_MATRIX_3X2_F^% Param_Out_Matrix)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F OutTransform;

	//Chama o método para realizar a operação.
	PonteiroTrabalho->GetTransform(&OutTransform);

	//Converte a estrutura nativa e define no parametro de saida.
	Param_Out_Matrix = Util.ConverterD2D1_MATRIX_3X2_FUnmanagedToManaged(&OutTransform);
}

/// <summary>
/// Define o grau de opacidade deste pincel.
/// </summary>
/// <param name="Param_Opacidade">Um valor entre zero e 1 que indica a opacidade do pincel. Este valor é um multiplicador constante que escala linearmente o valor alfa de todos os pixels preenchidos pelo pincel. 
/// Os valores de opacidade são fixados na faixa 0-1 antes de serem múltiplos juntos.</param>
void CarenD2D1ImageBrush::SetOpacity(float Param_Opacidade)
{
	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetOpacity(Param_Opacidade);
}

/// <summary>
/// Define a transformação aplicada ao pincel.
/// </summary>
/// <param name="Param_Transform">A transformação a ser aplicada a este pincel.</param>
void CarenD2D1ImageBrush::SetTransform(CA_D2D1_MATRIX_3X2_F^ Param_Transform)
{
	//Variaveis a serem utilizadas.
	Utilidades Util;
	D2D1_MATRIX_3X2_F* pTransform = NULL;

	//Converte a estrutura nativa para a gerenciada.
	pTransform = Util.ConverterD2D1_MATRIX_3X2_FManagedToUnmanaged(Param_Transform);

	//Chama o método para realizar a operação.
	PonteiroTrabalho->SetTransform(pTransform);

	//Libera a memória para a estrutura criada.
	DeletarEstruturaSafe(&pTransform);
}


// Métodos da interface (ICarenD2D1Resource)


/// <summary>
/// Recupera a fábrica associada a este recurso.
/// </summary>
/// <param name="Param_Out_Factory">Retorna uma interface(ICarenD2D1Factory) que contém um ponteiro para a fabrica que criou esse recurso. O usuário deve inicializar a interface antes de chamar este método.</param>
void CarenD2D1ImageBrush::GetFactory(ICaren^ Param_Out_Factory)
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